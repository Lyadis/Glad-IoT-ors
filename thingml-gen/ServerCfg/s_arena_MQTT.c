

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <mosquitto.h>

static char *MQTT_topic = "arena";
static int MQTT_topic_qos = 0;
static char *MQTT_username = NULL;
static char *MQTT_password = NULL;
static int MQTT_qos = 0;
static int MQTT_retain = 0;
static uint16_t MQTT_mid_sent = 0;
struct mosquitto *MQTT_mosq = NULL;
static int MQTT_connected = 0;


struct MQTT_instance_type {
    uint16_t listener_id;
    //Connector// Pointer to receiver list
struct Msg_Handler ** arena_receiver_list_head;
struct Msg_Handler ** arena_receiver_list_tail;
// Handler Array
struct Msg_Handler * arena_handlers;

};

extern struct MQTT_instance_type MQTT_instance;

void MQTT_set_listener_id(uint16_t id) {
	MQTT_instance.listener_id = id;
}

void MQTT_parser(char * in_msg, int size, int listener_id) {
int len = strlen((char *) in_msg);
            //printf("[/*PORT_NAME*/] l:%i\n", len);
            if ((len % 3) == 0) {
                unsigned char msg[len % 3];
                unsigned char * p = in_msg;
                int buf = 0;
                int index = 0;
                bool everythingisfine = true;
                while ((index < len) && everythingisfine) {
                    if((*p - 48) < 10) {
                        buf = (*p - 48) + 10 * buf;
                    } else {
                        everythingisfine = false;
                    }
                    if ((index % 3) == 2) {
                        if(buf < 256) {
                                msg[(index-2) / 3] =  (uint8_t) buf;
                        } else {
                                everythingisfine = false;
                        }
                        buf = 0;
                    }
                    index++;
                    p++;
                }
                if(everythingisfine) {
                    externalMessageEnqueue(msg, (len / 3), listener_id);
                } else {
                }
}
}



void MQTT_publish_callback(void *obj, uint16_t mid)
{
	struct mosquitto *mosq = obj;

	
}

void MQTT_message_callback(void *obj, const struct mosquitto_message *message)
{
    printf("%s %s\n", message->topic, message->payload);
    int len = strlen(message->payload);
    //printf("[MQTT] receveid l:%i\n", len);
    MQTT_parser(message->payload, len, MQTT_instance.listener_id);
}

void MQTT_connect_callback(void *obj, int result)
{
    struct mosquitto *mosq = obj;

    int i;
    if(!result){
        mosquitto_subscribe(MQTT_mosq, NULL, MQTT_topic, MQTT_topic_qos);
    }else{
        switch(result){
            case 1:
                fprintf(stderr, "[MQTT] Connection Refused: unacceptable protocol version\n");
                break;
            case 2:
                fprintf(stderr, "[MQTT] Connection Refused: identifier rejected\n");
                break;
            case 3:
                fprintf(stderr, "[MQTT] Connection Refused: broker unavailable\n");
                break;
            case 4:
                fprintf(stderr, "[MQTT] Connection Refused: bad user name or password\n");
                break;
            case 5:
                fprintf(stderr, "[MQTT] Connection Refused: not authorised\n");
                break;
            default:
                fprintf(stderr, "[MQTT] Connection Refused: unknown reason\n");
                break;
        }
    }
}

void MQTT_subscribe_callback(void *obj, uint16_t mid, int qos_count, const uint8_t *granted_qos)
{
	int i;

	printf("[MQTT] Subscribed (mid: %d): %d", mid, granted_qos[0]);
	for(i=1; i<qos_count; i++){
		printf(", %d", granted_qos[i]);
	}
	printf("\n");
}

void MQTT_setup() {
	char *id = NULL;
	char *id_prefix = NULL;
	int i;
	char *host = "127.0.0.1";
	int port = 1883;
	int keepalive = 60;
	bool clean_session = true;
	bool debug = false;
	int rc, rc2;
	char hostname[21];
	char err[1024];
	
	uint8_t *will_payload = NULL;
	long will_payloadlen = 0;
	int will_qos = 0;
	bool will_retain = false;
	char *will_topic = NULL;

        /*MULTI_TOPIC_INIT*/

        printf("[MQTT] Initialization MQTT at %s:%i\n", host, port);
	
	if(clean_session == false && (id_prefix || !id)){
		fprintf(stderr, "[MQTT] Error: You must provide a client id if you are using the -c option.\n");
		return 1;
	}
	if(id_prefix){
		id = malloc(strlen(id_prefix)+10);
		if(!id){
			fprintf(stderr, "[MQTT] Error: Out of memory.\n");
			return 1;
		}
		snprintf(id, strlen(id_prefix)+10, "%s%d", id_prefix, getpid());
	}else if(!id){
		id = malloc(30);
		if(!id){
			fprintf(stderr, "[MQTT] Error: Out of memory.\n");
			return 1;
		}
		memset(hostname, 0, 21);
		gethostname(hostname, 20);
		snprintf(id, 23, "mosq_sub_%d_%s", getpid(), hostname);
	}

	if(will_payload && !will_topic){
		fprintf(stderr, "[MQTT] Error: Will payload given, but no will topic given.\n");
		return 1;
	}
	if(will_retain && !will_topic){
		fprintf(stderr, "[MQTT] Error: Will retain given, but no will topic given.\n");
		return 1;
	}
	if(MQTT_password && !MQTT_username){
		fprintf(stderr, "[MQTT] Warning: Not using password since username not set.\n");
	}
	mosquitto_lib_init();
	MQTT_mosq = mosquitto_new(id, NULL);
	if(!MQTT_mosq){
		fprintf(stderr, "[MQTT] Error: Out of memory.\n");
		return 1;
	}
	if(will_topic && mosquitto_will_set(MQTT_mosq, true, will_topic, will_payloadlen, will_payload, will_qos, will_retain)){
		fprintf(stderr, "[MQTT] Error: Problem setting will.\n");
		return 1;
	}
	if(MQTT_username && mosquitto_username_pw_set(MQTT_mosq, MQTT_username, MQTT_password)){
		fprintf(stderr, "[MQTT] Error: Problem setting username and password.\n");
		return 1;
	}
	mosquitto_connect_callback_set(MQTT_mosq, MQTT_connect_callback);
	mosquitto_message_callback_set(MQTT_mosq, MQTT_message_callback);
	
	mosquitto_subscribe_callback_set(MQTT_mosq, MQTT_subscribe_callback);

	rc = mosquitto_connect(MQTT_mosq, host, port, keepalive, clean_session);
	if(rc){
		if(rc == MOSQ_ERR_ERRNO){
			strerror_r(errno, err, 1024);
			fprintf(stderr, "[MQTT] Error: %s\n", err);
		}else{
			fprintf(stderr, "[MQTT] Unable to connect (%d).\n", rc);
		}
		//return rc;
	}

}

void MQTT_start_receiver_process() {
        int rc;	

	do{
		rc = mosquitto_loop(MQTT_mosq, -1);
	}while(rc == MOSQ_ERR_SUCCESS);

        printf("[MQTT] Error :%i\n", rc);
	mosquitto_destroy(MQTT_mosq);
	mosquitto_lib_cleanup();

}

void MQTT_forwardMessage(uint8_t * msg, int size) {
    int n, m, i;
    int length = size;
    unsigned char buf[length];
    unsigned char *p = &buf[0];	
    unsigned char *q = p;
    n = 0;
    for(i = 0; i < length; i++) {
        *q = msg[i];
        q++;
        n++;
    }
    
    //printf("[MQTT] publish:\"%s\"\n", p);
mosquitto_publish(MQTT_mosq, &MQTT_mid_sent, MQTT_topic, length, p, MQTT_qos, MQTT_retain);

    
}

