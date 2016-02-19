#include <string.h> // string function definitions
#include <fcntl.h> // File control definitions
#include <errno.h> // Error number definitions
#include <termios.h> // POSIX terminal control definitions
#include <time.h> // time calls

//#define Serial1_TIMEOUT 10 // timeout waiting for messages from the serial device
#define Serial1_INPUT_BUFFER_SIZE 30 // for possible future optimizations
#define Serial1_MAX_MSG_LENGTH 3
#define Serial1_START_BYTE 18
#define Serial1_STOP_BYTE 19
#define Serial1_ESCAPE_BYTE 125

#define Serial1_LISTENER_STATE_IDLE 0
#define Serial1_LISTENER_STATE_READING 1
#define Serial1_LISTENER_STATE_ESCAPE 2
#define Serial1_LISTENER_STATE_ERROR 3
int Serial1_device_id;


struct Serial1_instance_type {
    uint16_t listener_id;
    //Connector// Pointer to receiver list
struct Msg_Handler ** cmd_receiver_list_head;
struct Msg_Handler ** cmd_receiver_list_tail;
// Handler Array
struct Msg_Handler * cmd_handlers;

};

extern struct Serial1_instance_type Serial1_instance;

void Serial1_set_listener_id(uint16_t id) {
	Serial1_instance.listener_id = id;
}

void Serial1_parser(char * msg, int size, int listener_id) {
    externalMessageEnqueue((uint8_t *) msg, size, listener_id);
}


int Serial1_setup() {
        char * device = "/dev/ttyATH0";
        uint32_t baudrate = 115200;
        printf("[Serial1] Opening Serial device %s at %ibps...\n", device, baudrate);
	int result;
	struct termios port_settings;
	result = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
	if (result < 0) {
                printf("[Serial1] Error opening Serial port\n");
		perror("Error opening Serial port");
	}
	else if (tcgetattr(result, &port_settings) < 0) {// try to get current options
                printf("[Serial1] Error opening Serial port: could not get serial port attributes\n");
		perror("Error opening Serial port: could not get serial port attributes");
	}
	else {
		//printf("Configuring port %s...\n", device);
		switch(baudrate) {
			case 115200:
				cfsetispeed(&port_settings, B115200);    // set baud rates to 115200 ---------- Test with 57600
				cfsetospeed(&port_settings, B115200);
			break;
			
			case 57600:
				cfsetispeed(&port_settings, B57600);    // set baud rates to 115200 ---------- Test with 57600
				cfsetospeed(&port_settings, B57600);
			break;
			
			case 38400:
				cfsetispeed(&port_settings, B38400);    // set baud rates to 38400 ---------- Test with 57600
				cfsetospeed(&port_settings, B38400);
			break;
			
			case 19200:
				cfsetispeed(&port_settings, B19200);    // set baud rates to 19200 ---------- Test with 57600
				cfsetospeed(&port_settings, B19200);
			break;
			
			case 9600:
				cfsetispeed(&port_settings, B9600);    // set baud rates to 115200 ---------- Test with 57600
				cfsetospeed(&port_settings, B9600);
			break;
			
			default:
				cfsetispeed(&port_settings, B115200);    // set baud rates to 115200 ---------- Test with 57600
				cfsetospeed(&port_settings, B115200);
			break;
		}
		// 8N1
		port_settings.c_cflag &= ~PARENB;
		port_settings.c_cflag &= ~CSTOPB;
		port_settings.c_cflag &= ~CSIZE;
		port_settings.c_cflag |= CS8;
		// no flow control
		port_settings.c_cflag &= ~CRTSCTS;
		port_settings.c_cflag |= CREAD | CLOCAL; // turn on READ & ignore ctrl lines
		port_settings.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl
		port_settings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
		port_settings.c_oflag &= ~OPOST; // make raw
		// see: http://unixwiz.net/techtips/termios-vmin-vtime.html
		port_settings.c_cc[VMIN] = 0;
		port_settings.c_cc[VTIME] = 20;
		if (tcsetattr(result, TCSANOW, &port_settings) < 0 ) {
                    printf("[Serial1] Error opening Serial port: could not set serial port attributes\n");
                    perror("Error opening Serial port: could not set serial port attributes");
		}
		sleep(1); // wait a bit
	}

	Serial1_device_id = result;
        //printf("[Serial1] Serial Port %s open\n", device);
}
	
int send_byte(int device, uint8_t byte) {
	int n;
	unsigned char data[1];
	data[0] = byte;
	n = write(device, data, 1);
	
        //printf("[Serial1] forwarding %i with result %i\n", data[0], n);
	if (n < 0) {
            perror("Error writing to Serial device");
            return -1;
	}
	return 0;
}

void Serial1_forwardMessage(byte * msg, uint8_t size) {
        //printf("[Serial1] forwarding message\n");
	send_byte(Serial1_device_id, Serial1_START_BYTE);
	uint8_t i;
	for(i = 0; i < size; i++) {
		if((msg[i] == Serial1_START_BYTE) || (msg[i] == Serial1_STOP_BYTE) || (msg[i] == Serial1_ESCAPE_BYTE)) {
	  		send_byte(Serial1_device_id, Serial1_ESCAPE_BYTE);
		}
		send_byte(Serial1_device_id, msg[i]);
	}
	send_byte(Serial1_device_id, Serial1_STOP_BYTE);
}
	
void Serial1_start_receiver_process()
{
        printf("[Serial1] Starting receiver process\n");
	int device = Serial1_device_id;
	int serialListenerState = Serial1_LISTENER_STATE_IDLE;
	char serialBuffer[Serial1_MAX_MSG_LENGTH];
	int serialMsgSize = 0;
	char buffer[Serial1_INPUT_BUFFER_SIZE]; // Data read from the ESUSMS device
	int n; // used to store the results of select and read
	int i; // loop index
	while (1) {
		fd_set rdfs; // The file descriptor to wait on
		FD_ZERO( &rdfs );
		FD_SET(device, &rdfs ); // set to the esusms fd
		n = select(device + 1, &rdfs, NULL, NULL, NULL); // NO Timeout here (last parameter)
		if (n < 0) {
                    printf("[Serial1] Error waiting for incoming data from Serial device\n");
                    perror("Error waiting for incoming data from Serial device");
                    break;
		}
		else if (n == 0) { // timeout
                    printf("[Serial1] Timeout waiting for incoming data from Serial device\n");
                    break;
		}
		else { // there is something to read
			n = read(device, &buffer, Serial1_INPUT_BUFFER_SIZE * sizeof(char));
			//printf(" n=<%i>\n", n);
			if (n<0) {
                            printf("[Serial1] Error reading from Serial device\n");
                            perror("Error reading from Serial device");
                            break;
			}
			else if (n==0) {
                            printf("[Serial1] Nothing to read from Serial device\n");
                            break;
			}
			else { // There are n incoming bytes in buffer
				for (i = 0; i<n; i++) {
					
                                        //printf("[Serial1] byte received:%i\n", buffer[i]);
					switch(serialListenerState) {
						case Serial1_LISTENER_STATE_IDLE:
                                                        //printf("[Serial1] State:IDLE\n");
							if(buffer[i] == Serial1_START_BYTE) {
							  serialListenerState = Serial1_LISTENER_STATE_READING;
							  serialMsgSize = 0;
							}
						break;

						case Serial1_LISTENER_STATE_READING:
                                                        //printf("[Serial1] State:READING\n");
							if (serialMsgSize > Serial1_MAX_MSG_LENGTH) {
							  serialListenerState = Serial1_LISTENER_STATE_ERROR;
							} else {
							  if(buffer[i] == Serial1_STOP_BYTE) {
								serialListenerState = Serial1_LISTENER_STATE_IDLE;

                                                                //printf("[Serial1] Message received\n");
                                                                Serial1_parser(serialBuffer, serialMsgSize, Serial1_instance.listener_id);
                                                                //externalMessageEnqueue(serialBuffer, serialMsgSize, Serial1_instance.listener_id);

							  } else if (buffer[i] == Serial1_ESCAPE_BYTE) {
								serialListenerState = Serial1_LISTENER_STATE_ESCAPE;
							  } else {
								serialBuffer[serialMsgSize] = buffer[i];
								serialMsgSize++;
							  }
							}
						break;

						case Serial1_LISTENER_STATE_ESCAPE:
                                                        //printf("[Serial1] State:ESCAPE\n");
							if (serialMsgSize > Serial1_MAX_MSG_LENGTH) {
							  serialListenerState = Serial1_LISTENER_STATE_ERROR;
							} else {
							  serialBuffer[serialMsgSize] = buffer[i];
							  serialMsgSize++;
							  serialListenerState = Serial1_LISTENER_STATE_READING;
							}
						break;

						case Serial1_LISTENER_STATE_ERROR:
                                                        printf("[Serial1] Message error: Too long\n");
							serialListenerState = Serial1_LISTENER_STATE_IDLE;
							serialMsgSize = 0;
						break;
					}
				}
			}
		}
	}
}
