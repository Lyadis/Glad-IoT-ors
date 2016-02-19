/*****************************************************************************
 * Headers for type : MCU
 *****************************************************************************/

// Definition of the instance stuct:
struct MCU_Instance {
// Variables for the ID of the ports of the instance
uint16_t id_control;
uint16_t id_clock;
// Variables for the current instance state
int MCU_C_State;
// Variables for the properties of the instance
uint8_t MCU_ledPin__var;
uint8_t MCU_receiverPin__var;

};
// Declaration of prototypes outgoing messages:
void MCU_C_OnEntry(int state, struct MCU_Instance *_instance);
void MCU_handle_control_shootCmd(struct MCU_Instance *_instance, uint8_t ID);
void MCU_handle_control_timer_cancel(struct MCU_Instance *_instance, uint8_t id);
void MCU_handle_control_timer_start(struct MCU_Instance *_instance, uint8_t id, uint32_t time);
void MCU_handle_clock_timeout(struct MCU_Instance *_instance, uint8_t id);
void MCU_handle_clock_50ms_tic(struct MCU_Instance *_instance);
// Declaration of callbacks for incoming messages:
void register_MCU_send_control_beenHit_listener(void (*_listener)(struct MCU_Instance *, uint8_t));
void register_external_MCU_send_control_beenHit_listener(void (*_listener)(struct MCU_Instance *, uint8_t));
void register_MCU_send_control_timeout_listener(void (*_listener)(struct MCU_Instance *, uint8_t));
void register_external_MCU_send_control_timeout_listener(void (*_listener)(struct MCU_Instance *, uint8_t));
void register_MCU_send_control_ready_listener(void (*_listener)(struct MCU_Instance *));
void register_external_MCU_send_control_ready_listener(void (*_listener)(struct MCU_Instance *));
void register_MCU_send_clock_timer_start_listener(void (*_listener)(struct MCU_Instance *, uint8_t, uint32_t));
void register_external_MCU_send_clock_timer_start_listener(void (*_listener)(struct MCU_Instance *, uint8_t, uint32_t));
void register_MCU_send_clock_timer_cancel_listener(void (*_listener)(struct MCU_Instance *, uint8_t));
void register_external_MCU_send_clock_timer_cancel_listener(void (*_listener)(struct MCU_Instance *, uint8_t));

// Definition of the states:
#define MCU_C_STATE 0
#define MCU_C_SETUP_STATE 1
#define MCU_C_ACTIVE_STATE 2


//#ifndef ArduinoSerialForward_h
//
//#define ArduinoSerialForward_h
//#include <Arduino.h>
//#include "ArduinoSerialForward.c"
//
//void Serial1_setup(long bps);
//void Serial1_setListenerID(uint16_t id);
//void Serial1_forwardMessage(byte * msg, uint8_t size);
//void Serial1_read();

//#endif
//timer2

/* Adds and instance to the runtime and returns its id */
uint16_t add_instance(void * instance_struct);
/* Returns the instance with id */
void * instance_by_id(uint16_t id);

/* Returns the number of byte currently in the fifo */
int fifo_byte_length();
/* Returns the number of bytes currently available in the fifo */
int fifo_byte_available();
/* Returns true if the fifo is empty */
int fifo_empty();
/* Return true if the fifo is full */
int fifo_full();
/* Enqueue 1 byte in the fifo if there is space
   returns 1 for sucess and 0 if the fifo was full */
int fifo_enqueue(byte b);
/* Enqueue 1 byte in the fifo without checking for available space
   The caller should have checked that there is enough space */
int _fifo_enqueue(byte b);
/* Dequeue 1 byte in the fifo.
   The caller should check that the fifo is not empty */
byte fifo_dequeue();

#define MAX_INSTANCES 4
#define FIFO_SIZE 256

/*********************************
 * Instance IDs and lookup
 *********************************/

void * instances[MAX_INSTANCES];
uint16_t instances_count = 0;

void * instance_by_id(uint16_t id) {
  return instances[id];
}

uint16_t add_instance(void * instance_struct) {
  instances[instances_count] = instance_struct;
  return instances_count++;
}

/******************************************
 * Simple byte FIFO implementation
 ******************************************/

byte fifo[FIFO_SIZE];
int fifo_head = 0;
int fifo_tail = 0;

// Returns the number of byte currently in the fifo
int fifo_byte_length() {
  if (fifo_tail >= fifo_head)
    return fifo_tail - fifo_head;
  return fifo_tail + FIFO_SIZE - fifo_head;
}

// Returns the number of bytes currently available in the fifo
int fifo_byte_available() {
  return FIFO_SIZE - 1 - fifo_byte_length();
}

// Returns true if the fifo is empty
int fifo_empty() {
  return fifo_head == fifo_tail;
}

// Return true if the fifo is full
int fifo_full() {
  return fifo_head == ((fifo_tail + 1) % FIFO_SIZE);
}

// Enqueue 1 byte in the fifo if there is space
// returns 1 for sucess and 0 if the fifo was full
int fifo_enqueue(byte b) {
  int new_tail = (fifo_tail + 1) % FIFO_SIZE;
  if (new_tail == fifo_head) return 0; // the fifo is full
  fifo[fifo_tail] = b;
  fifo_tail = new_tail;
  return 1;
}

// Enqueue 1 byte in the fifo without checking for available space
// The caller should have checked that there is enough space
int _fifo_enqueue(byte b) {
  fifo[fifo_tail] = b;
  fifo_tail = (fifo_tail + 1) % FIFO_SIZE;
}

// Dequeue 1 byte in the fifo.
// The caller should check that the fifo is not empty
byte fifo_dequeue() {
  if (!fifo_empty()) {
    byte result = fifo[fifo_head];
    fifo_head = (fifo_head + 1) % FIFO_SIZE;
    return result;
  }
  return 0;
}


/*SOFTWARE_SERIAL*/

#define Serial1_LISTENER_STATE_IDLE 0
#define Serial1_LISTENER_STATE_READING 1
#define Serial1_LISTENER_STATE_ESCAPE 2
#define Serial1_LISTENER_STATE_ERROR 3


#define Serial1_START_BYTE 18
#define Serial1_STOP_BYTE 19
#define Serial1_ESCAPE_BYTE 125

#define Serial1_LIMIT_BYTE_PER_LOOP 14
#define Serial1_MAX_MSG_SIZE 7
#define Serial1_MSG_BUFFER_SIZE 14


byte Serial1_serialBuffer[Serial1_MSG_BUFFER_SIZE];
uint8_t Serial1_serialMsgSize = 0;
byte Serial1_incoming = 0;
uint8_t Serial1_serialListenerState = Serial1_LISTENER_STATE_IDLE;


struct Serial1_instance_type {
    uint16_t listener_id;
    //Connector// Pointer to receiver list
struct Msg_Handler ** control_receiver_list_head;
struct Msg_Handler ** control_receiver_list_tail;
// Handler Array
struct Msg_Handler * control_handlers;

} Serial1_instance;

int fifo_byte_available();
int _fifo_enqueue(byte b);

void Serial1_setup() {
	Serial1.begin(115200);
}

void Serial1_set_listener_id(uint16_t id) {
	Serial1_instance.listener_id = id;
}


void Serial1_forwardMessage(byte * msg, uint8_t size) {
  
  Serial1.write(Serial1_START_BYTE);
  for(uint8_t i = 0; i < size; i++) {
    if((msg[i] == Serial1_START_BYTE) 
		|| (msg[i] == Serial1_STOP_BYTE) 
		|| (msg[i] == Serial1_ESCAPE_BYTE)) {
      Serial1.write(Serial1_ESCAPE_BYTE);
    }
    Serial1.write(msg[i]);
  }
  Serial1.write(Serial1_STOP_BYTE);
}

void Serial1_parser(char * msg, int size, int listener_id) {
    externalMessageEnqueue((uint8_t *) msg, size, listener_id);
}


void Serial1_read() {
  byte limit = 0;
  while ((Serial1.available()) && (limit < Serial1_LIMIT_BYTE_PER_LOOP)) {
   limit++;
    Serial1_incoming = Serial1.read();
    
    switch(Serial1_serialListenerState) {
      case Serial1_LISTENER_STATE_IDLE:
        if(Serial1_incoming == Serial1_START_BYTE) {
          Serial1_serialListenerState = Serial1_LISTENER_STATE_READING;
          Serial1_serialMsgSize = 0;
        }
      break;
      
      case Serial1_LISTENER_STATE_READING:
        if (Serial1_serialMsgSize > Serial1_MAX_MSG_SIZE) {
          Serial1_serialListenerState = Serial1_LISTENER_STATE_ERROR;
        } else {
          if(Serial1_incoming == Serial1_STOP_BYTE) {
            Serial1_serialListenerState = Serial1_LISTENER_STATE_IDLE;
            Serial1_parser((char *) Serial1_serialBuffer, Serial1_serialMsgSize, Serial1_instance.listener_id);
            //externalMessageEnqueue(Serial1_serialBuffer, Serial1_serialMsgSize, Serial1_instance.listener_id);
            
          } else if (Serial1_incoming == Serial1_ESCAPE_BYTE) {
            Serial1_serialListenerState = Serial1_LISTENER_STATE_ESCAPE;
          } else {
            Serial1_serialBuffer[Serial1_serialMsgSize] = Serial1_incoming;
            Serial1_serialMsgSize++;
          }
        }
      break;
      
      case Serial1_LISTENER_STATE_ESCAPE:
        if (Serial1_serialMsgSize >= Serial1_MAX_MSG_SIZE) {
          Serial1_serialListenerState = Serial1_LISTENER_STATE_ERROR;
        } else {
          Serial1_serialBuffer[Serial1_serialMsgSize] = Serial1_incoming;
          Serial1_serialMsgSize++;
          Serial1_serialListenerState = Serial1_LISTENER_STATE_READING;
        }
      break;
      
      case Serial1_LISTENER_STATE_ERROR:
        Serial1_serialListenerState = Serial1_LISTENER_STATE_IDLE;
        Serial1_serialMsgSize = 0;
      break;
    }
  }
  
}
/*****************************************************************************
 * Implementation for type : MCU
 *****************************************************************************/

// Declaration of prototypes:
void MCU_C_OnExit(int state, struct MCU_Instance *_instance);
void MCU_send_control_beenHit(struct MCU_Instance *_instance, uint8_t IDshooter);
void MCU_send_control_timeout(struct MCU_Instance *_instance, uint8_t id);
void MCU_send_control_ready(struct MCU_Instance *_instance);
void MCU_send_clock_timer_start(struct MCU_Instance *_instance, uint8_t id, uint32_t time);
void MCU_send_clock_timer_cancel(struct MCU_Instance *_instance, uint8_t id);
void f_MCU_refresh(struct MCU_Instance *_instance);
void f_MCU_shoot(struct MCU_Instance *_instance, uint8_t id);
// Declaration of functions:
// Definition of function refresh
void f_MCU_refresh(struct MCU_Instance *_instance) {
if(digitalRead(_instance->MCU_receiverPin__var)) {
MCU_send_control_beenHit(_instance, 0);

}
}
// Definition of function shoot
void f_MCU_shoot(struct MCU_Instance *_instance, uint8_t id) {
digitalWrite(_instance->MCU_receiverPin__var, HIGH);
		delay(50);
		digitalWrite(_instance->MCU_receiverPin__var, LOW);
}

// On Entry Actions:
void MCU_C_OnEntry(int state, struct MCU_Instance *_instance) {
switch(state) {
case MCU_C_STATE:
_instance->MCU_C_State = MCU_C_SETUP_STATE;
MCU_C_OnEntry(_instance->MCU_C_State, _instance);
break;
case MCU_C_SETUP_STATE:
pinMode(_instance->MCU_receiverPin__var, INPUT);
pinMode(_instance->MCU_ledPin__var, OUTPUT);
break;
case MCU_C_ACTIVE_STATE:
break;
default: break;
}
}

// On Exit Actions:
void MCU_C_OnExit(int state, struct MCU_Instance *_instance) {
switch(state) {
case MCU_C_STATE:
MCU_C_OnExit(_instance->MCU_C_State, _instance);
break;
case MCU_C_SETUP_STATE:
break;
case MCU_C_ACTIVE_STATE:
break;
default: break;
}
}

// Event Handlers for incoming messages:
void MCU_handle_control_shootCmd(struct MCU_Instance *_instance, uint8_t ID) {
uint8_t MCU_C_State_event_consumed = 0;
if (_instance->MCU_C_State == MCU_C_ACTIVE_STATE) {
if (MCU_C_State_event_consumed == 0 && 1) {
f_MCU_shoot(_instance, ID);
MCU_C_State_event_consumed = 1;
}
}
}
void MCU_handle_control_timer_cancel(struct MCU_Instance *_instance, uint8_t id) {
uint8_t MCU_C_State_event_consumed = 0;
if (_instance->MCU_C_State == MCU_C_ACTIVE_STATE) {
if (MCU_C_State_event_consumed == 0 && 1) {
MCU_send_clock_timer_cancel(_instance, id);
MCU_C_State_event_consumed = 1;
}
}
}
void MCU_handle_control_timer_start(struct MCU_Instance *_instance, uint8_t id, uint32_t time) {
uint8_t MCU_C_State_event_consumed = 0;
if (_instance->MCU_C_State == MCU_C_ACTIVE_STATE) {
if (MCU_C_State_event_consumed == 0 && 1) {
MCU_send_clock_timer_start(_instance, id, time);
MCU_C_State_event_consumed = 1;
}
}
}
void MCU_handle_clock_timeout(struct MCU_Instance *_instance, uint8_t id) {
uint8_t MCU_C_State_event_consumed = 0;
if (_instance->MCU_C_State == MCU_C_ACTIVE_STATE) {
if (MCU_C_State_event_consumed == 0 && 1) {
MCU_send_control_timeout(_instance, id);
MCU_C_State_event_consumed = 1;
}
}
}
void MCU_handle_clock_50ms_tic(struct MCU_Instance *_instance) {
uint8_t MCU_C_State_event_consumed = 0;
if (_instance->MCU_C_State == MCU_C_ACTIVE_STATE) {
if (MCU_C_State_event_consumed == 0 && 1) {
f_MCU_refresh(_instance);
MCU_C_State_event_consumed = 1;
}
}
}
int MCU_handle_empty_event(struct MCU_Instance *_instance) {
if (_instance->MCU_C_State == MCU_C_SETUP_STATE) {
if (1) {
MCU_C_OnExit(MCU_C_SETUP_STATE, _instance);
_instance->MCU_C_State = MCU_C_ACTIVE_STATE;
MCU_send_control_ready(_instance);
MCU_C_OnEntry(MCU_C_ACTIVE_STATE, _instance);
return 1;
}
}
return 0;
}

// Observers for outgoing messages:
void (*external_MCU_send_control_beenHit_listener)(struct MCU_Instance *, uint8_t)= 0x0;
void (*MCU_send_control_beenHit_listener)(struct MCU_Instance *, uint8_t)= 0x0;
void register_external_MCU_send_control_beenHit_listener(void (*_listener)(struct MCU_Instance *, uint8_t)){
external_MCU_send_control_beenHit_listener = _listener;
}
void register_MCU_send_control_beenHit_listener(void (*_listener)(struct MCU_Instance *, uint8_t)){
MCU_send_control_beenHit_listener = _listener;
}
void MCU_send_control_beenHit(struct MCU_Instance *_instance, uint8_t IDshooter){
if (MCU_send_control_beenHit_listener != 0x0) MCU_send_control_beenHit_listener(_instance, IDshooter);
if (external_MCU_send_control_beenHit_listener != 0x0) external_MCU_send_control_beenHit_listener(_instance, IDshooter);
;
}
void (*external_MCU_send_control_timeout_listener)(struct MCU_Instance *, uint8_t)= 0x0;
void (*MCU_send_control_timeout_listener)(struct MCU_Instance *, uint8_t)= 0x0;
void register_external_MCU_send_control_timeout_listener(void (*_listener)(struct MCU_Instance *, uint8_t)){
external_MCU_send_control_timeout_listener = _listener;
}
void register_MCU_send_control_timeout_listener(void (*_listener)(struct MCU_Instance *, uint8_t)){
MCU_send_control_timeout_listener = _listener;
}
void MCU_send_control_timeout(struct MCU_Instance *_instance, uint8_t id){
if (MCU_send_control_timeout_listener != 0x0) MCU_send_control_timeout_listener(_instance, id);
if (external_MCU_send_control_timeout_listener != 0x0) external_MCU_send_control_timeout_listener(_instance, id);
;
}
void (*external_MCU_send_control_ready_listener)(struct MCU_Instance *)= 0x0;
void (*MCU_send_control_ready_listener)(struct MCU_Instance *)= 0x0;
void register_external_MCU_send_control_ready_listener(void (*_listener)(struct MCU_Instance *)){
external_MCU_send_control_ready_listener = _listener;
}
void register_MCU_send_control_ready_listener(void (*_listener)(struct MCU_Instance *)){
MCU_send_control_ready_listener = _listener;
}
void MCU_send_control_ready(struct MCU_Instance *_instance){
if (MCU_send_control_ready_listener != 0x0) MCU_send_control_ready_listener(_instance);
if (external_MCU_send_control_ready_listener != 0x0) external_MCU_send_control_ready_listener(_instance);
;
}
void (*external_MCU_send_clock_timer_start_listener)(struct MCU_Instance *, uint8_t, uint32_t)= 0x0;
void (*MCU_send_clock_timer_start_listener)(struct MCU_Instance *, uint8_t, uint32_t)= 0x0;
void register_external_MCU_send_clock_timer_start_listener(void (*_listener)(struct MCU_Instance *, uint8_t, uint32_t)){
external_MCU_send_clock_timer_start_listener = _listener;
}
void register_MCU_send_clock_timer_start_listener(void (*_listener)(struct MCU_Instance *, uint8_t, uint32_t)){
MCU_send_clock_timer_start_listener = _listener;
}
void MCU_send_clock_timer_start(struct MCU_Instance *_instance, uint8_t id, uint32_t time){
if (MCU_send_clock_timer_start_listener != 0x0) MCU_send_clock_timer_start_listener(_instance, id, time);
if (external_MCU_send_clock_timer_start_listener != 0x0) external_MCU_send_clock_timer_start_listener(_instance, id, time);
;
}
void (*external_MCU_send_clock_timer_cancel_listener)(struct MCU_Instance *, uint8_t)= 0x0;
void (*MCU_send_clock_timer_cancel_listener)(struct MCU_Instance *, uint8_t)= 0x0;
void register_external_MCU_send_clock_timer_cancel_listener(void (*_listener)(struct MCU_Instance *, uint8_t)){
external_MCU_send_clock_timer_cancel_listener = _listener;
}
void register_MCU_send_clock_timer_cancel_listener(void (*_listener)(struct MCU_Instance *, uint8_t)){
MCU_send_clock_timer_cancel_listener = _listener;
}
void MCU_send_clock_timer_cancel(struct MCU_Instance *_instance, uint8_t id){
if (MCU_send_clock_timer_cancel_listener != 0x0) MCU_send_clock_timer_cancel_listener(_instance, id);
if (external_MCU_send_clock_timer_cancel_listener != 0x0) external_MCU_send_clock_timer_cancel_listener(_instance, id);
;
}



#define timer2_NB_SOFT_TIMER 4
uint32_t timer2_timer[timer2_NB_SOFT_TIMER];
uint32_t  timer2_prev_1sec = 0;

uint8_t timer2_interrupt_counter = 0;
SIGNAL(TIMER2_OVF_vect) {
TCNT2 = 5;
timer2_interrupt_counter++;
if((timer2_interrupt_counter % 50) == 0) {
timer2_50ms_tic();
}
if(timer2_interrupt_counter >= 50) {
timer2_interrupt_counter = 0;
}
}



struct timer2_instance_type {
    uint16_t listener_id;
    /*INSTANCE_INFORMATION*/
} timer2_instance;

void timer2_setup() {
	// Run timer2 interrupt up counting at 250kHz 
		 TCCR2A = 0;
		 TCCR2B = 1<<CS22 | 0<<CS21 | 0<<CS20;
		
		 //Timer2 Overflow Interrupt Enable
		 TIMSK2 |= 1<<TOIE2;


	timer2_prev_1sec = millis() + 1000;
}

void timer2_set_listener_id(uint16_t id) {
	timer2_instance.listener_id = id;
}

void timer2_timer_start(uint8_t id, uint32_t ms) {
if(id <timer2_NB_SOFT_TIMER) {
timer2_timer[id] = ms + millis();
}
}

void timer2_timer_cancel(uint8_t id) {
if(id <timer2_NB_SOFT_TIMER) {
timer2_timer[id] = 0;
}
}

void timer2_timeout(uint8_t id) {
uint8_t enqueue_buf[3];
enqueue_buf[0] = (1 >> 8) & 0xFF;
enqueue_buf[1] = 1 & 0xFF;
enqueue_buf[2] = id;
externalMessageEnqueue(enqueue_buf, 3, timer2_instance.listener_id);
}

void timer2_50ms_tic() {
uint8_t enqueue_buf[2];
enqueue_buf[0] = (2 >> 8) & 0xFF;
enqueue_buf[1] = 2 & 0xFF;
externalMessageEnqueue(enqueue_buf, 2, timer2_instance.listener_id);
}





void timer2_read() {
	uint32_t tms = millis();
	uint8_t t;
for(t = 0; t < 4; t++) {
if((timer2_timer[t] > 0) && (timer2_timer[t] < tms)) {
timer2_timer[t] = 0;
timer2_timeout(t);
}
}

	if (timer2_prev_1sec < tms) {
		timer2_prev_1sec += 1000;
	}
}



/*****************************************************************************
 * Definitions for configuration : GladiotorCfg
 *****************************************************************************/

//Declaration of instance variables
//Instance mc
// Variables for the properties of the instance
struct MCU_Instance mc_var;



//New dispatcher for messages
void dispatch_shootCmd(uint16_t sender, uint8_t param_ID) {
if (sender == Serial1_instance.listener_id) {
MCU_handle_control_shootCmd(&mc_var, param_ID);

}

}


//New dispatcher for messages
void dispatch_timer_cancel(uint16_t sender, uint8_t param_id) {
if (sender == Serial1_instance.listener_id) {
MCU_handle_control_timer_cancel(&mc_var, param_id);

}

}


//New dispatcher for messages
void dispatch_timeout(uint16_t sender, uint8_t param_id) {
if (sender == timer2_instance.listener_id) {
MCU_handle_clock_timeout(&mc_var, param_id);

}

}


//New dispatcher for messages
void dispatch_50ms_tic(uint16_t sender) {
if (sender == timer2_instance.listener_id) {
MCU_handle_clock_50ms_tic(&mc_var);

}

}


//New dispatcher for messages
void dispatch_timer_start(uint16_t sender, uint8_t param_id, uint32_t param_time) {
if (sender == Serial1_instance.listener_id) {
MCU_handle_control_timer_start(&mc_var, param_id, param_time);

}

}


int processMessageQueue() {
if (fifo_empty()) return 0; // return 0 if there is nothing to do

byte mbuf[7];
uint8_t mbufi = 0;

// Read the code of the next port/message in the queue
uint16_t code = fifo_dequeue() << 8;

code += fifo_dequeue();

// Switch to call the appropriate handler
switch(code) {
case 201:
while (mbufi < 3) mbuf[mbufi++] = fifo_dequeue();
union u_shootCmd_ID_t {
uint8_t p;
byte bytebuffer[1];
} u_shootCmd_ID;
u_shootCmd_ID.bytebuffer[0] = mbuf[2];
dispatch_shootCmd((mbuf[0] << 8) + mbuf[1] /* instance port*/,
 u_shootCmd_ID.p /* ID */ );
break;
case 1:
while (mbufi < 3) mbuf[mbufi++] = fifo_dequeue();
union u_timeout_id_t {
uint8_t p;
byte bytebuffer[1];
} u_timeout_id;
u_timeout_id.bytebuffer[0] = mbuf[2];
dispatch_timeout((mbuf[0] << 8) + mbuf[1] /* instance port*/,
 u_timeout_id.p /* id */ );
break;
case 3:
while (mbufi < 3) mbuf[mbufi++] = fifo_dequeue();
union u_timer_cancel_id_t {
uint8_t p;
byte bytebuffer[1];
} u_timer_cancel_id;
u_timer_cancel_id.bytebuffer[0] = mbuf[2];
dispatch_timer_cancel((mbuf[0] << 8) + mbuf[1] /* instance port*/,
 u_timer_cancel_id.p /* id */ );
break;
case 2:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
dispatch_50ms_tic((mbuf[0] << 8) + mbuf[1] /* instance port*/);
break;
case 4:
while (mbufi < 7) mbuf[mbufi++] = fifo_dequeue();
union u_timer_start_id_t {
uint8_t p;
byte bytebuffer[1];
} u_timer_start_id;
u_timer_start_id.bytebuffer[0] = mbuf[2];
union u_timer_start_time_t {
uint32_t p;
byte bytebuffer[4];
} u_timer_start_time;
u_timer_start_time.bytebuffer[3] = mbuf[3];
u_timer_start_time.bytebuffer[2] = mbuf[4];
u_timer_start_time.bytebuffer[1] = mbuf[5];
u_timer_start_time.bytebuffer[0] = mbuf[6];
dispatch_timer_start((mbuf[0] << 8) + mbuf[1] /* instance port*/,
 u_timer_start_id.p /* id */ ,
 u_timer_start_time.p /* time */ );
break;
}
return 1;
}

// Forwarding of messages timer2::MCU::clock::timer_start
void forward_timer2_MCU_send_clock_timer_start(struct MCU_Instance *_instance, uint8_t id, uint32_t time){
timer2_timer_start(id, time);}

// Forwarding of messages timer2::MCU::clock::timer_cancel
void forward_timer2_MCU_send_clock_timer_cancel(struct MCU_Instance *_instance, uint8_t id){
timer2_timer_cancel(id);}

// Forwarding of messages Serial1::MCU::control::beenHit
void forward_Serial1_MCU_send_control_beenHit(struct MCU_Instance *_instance, uint8_t IDshooter){
byte forward_buf[3];
forward_buf[0] = (202 >> 8) & 0xFF;
forward_buf[1] =  202 & 0xFF;


// parameter IDshooter
union u_IDshooter_t {
uint8_t p;
byte bytebuffer[1];
} u_IDshooter;
u_IDshooter.p = IDshooter;
forward_buf[2] =  (u_IDshooter.bytebuffer[0] & 0xFF);

//Forwarding with specified function 
Serial1_forwardMessage(forward_buf, 3);
}

// Forwarding of messages Serial1::MCU::control::timeout
void forward_Serial1_MCU_send_control_timeout(struct MCU_Instance *_instance, uint8_t id){
byte forward_buf[3];
forward_buf[0] = (1 >> 8) & 0xFF;
forward_buf[1] =  1 & 0xFF;


// parameter id
union u_id_t {
uint8_t p;
byte bytebuffer[1];
} u_id;
u_id.p = id;
forward_buf[2] =  (u_id.bytebuffer[0] & 0xFF);

//Forwarding with specified function 
Serial1_forwardMessage(forward_buf, 3);
}

// Forwarding of messages Serial1::MCU::control::ready
void forward_Serial1_MCU_send_control_ready(struct MCU_Instance *_instance){
byte forward_buf[2];
forward_buf[0] = (200 >> 8) & 0xFF;
forward_buf[1] =  200 & 0xFF;


//Forwarding with specified function 
Serial1_forwardMessage(forward_buf, 2);
}

void forward_MCU_send_control_ready(struct MCU_Instance *_instance){
if(_instance->id_control == mc_var.id_control) {
forward_Serial1_MCU_send_control_ready(_instance);
}
}
void forward_MCU_send_control_timeout(struct MCU_Instance *_instance, uint8_t id){
if(_instance->id_control == mc_var.id_control) {
forward_Serial1_MCU_send_control_timeout(_instance, id);
}
}
void forward_MCU_send_clock_timer_cancel(struct MCU_Instance *_instance, uint8_t id){
if(_instance->id_clock == mc_var.id_clock) {
forward_timer2_MCU_send_clock_timer_cancel(_instance, id);
}
}
void forward_MCU_send_control_beenHit(struct MCU_Instance *_instance, uint8_t IDshooter){
if(_instance->id_control == mc_var.id_control) {
forward_Serial1_MCU_send_control_beenHit(_instance, IDshooter);
}
}
void forward_MCU_send_clock_timer_start(struct MCU_Instance *_instance, uint8_t id, uint32_t time){
if(_instance->id_clock == mc_var.id_clock) {
forward_timer2_MCU_send_clock_timer_start(_instance, id, time);
}
}

//external Message enqueue
void externalMessageEnqueue(uint8_t * msg, uint8_t msgSize, uint16_t listener_id) {
if ((msgSize >= 2) && (msg != NULL)) {
uint8_t msgSizeOK = 0;
switch(msg[0] * 256 + msg[1]) {
case 201:
if(msgSize == 3) {
msgSizeOK = 1;}
break;
case 3:
if(msgSize == 3) {
msgSizeOK = 1;}
break;
case 1:
if(msgSize == 3) {
msgSizeOK = 1;}
break;
case 2:
if(msgSize == 2) {
msgSizeOK = 1;}
break;
case 4:
if(msgSize == 7) {
msgSizeOK = 1;}
break;
}

if(msgSizeOK == 1) {
if ( fifo_byte_available() > (msgSize + 2) ) {
	uint8_t i;
	for (i = 0; i < 2; i++) {
		_fifo_enqueue(msg[i]);
	}
	_fifo_enqueue((listener_id >> 8) & 0xFF);
	_fifo_enqueue(listener_id & 0xFF);
	for (i = 2; i < msgSize; i++) {
		_fifo_enqueue(msg[i]);
	}
}
}
}
}

void initialize_configuration_GladiotorCfg() {
// Initialize connectors
register_external_MCU_send_control_beenHit_listener(&forward_MCU_send_control_beenHit);
register_external_MCU_send_control_timeout_listener(&forward_MCU_send_control_timeout);
register_external_MCU_send_control_ready_listener(&forward_MCU_send_control_ready);
register_external_MCU_send_clock_timer_start_listener(&forward_MCU_send_clock_timer_start);
register_external_MCU_send_clock_timer_cancel_listener(&forward_MCU_send_clock_timer_cancel);

// Init the ID, state variables and properties for external connector Serial1
// Init the ID, state variables and properties for external connector timer2

// Network Initilization 


Serial1_instance.listener_id = add_instance(&Serial1_instance);

Serial1_setup();


timer2_instance.listener_id = add_instance(&timer2_instance);

timer2_setup();


// End Network Initilization 

// Init the ID, state variables and properties for instance mc
mc_var.id_control = add_instance( (void*) &mc_var);
mc_var.id_clock = add_instance( (void*) &mc_var);
mc_var.MCU_C_State = MCU_C_SETUP_STATE;
mc_var.MCU_ledPin__var = 7;
mc_var.MCU_receiverPin__var = 8;

MCU_C_OnEntry(MCU_C_STATE, &mc_var);
}




void setup() {
initialize_configuration_GladiotorCfg();

}

void loop() {

// Network Listener

Serial1_read();

timer2_read();
MCU_handle_empty_event(&mc_var);

    processMessageQueue();
}
