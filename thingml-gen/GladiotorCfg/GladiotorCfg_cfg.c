/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *      Implementation for Application GladiotorCfg
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <pthread.h>
#include "thingml_typedefs.h"
#include "runtime.h"
#include "Gladiotor.h"
#include "g_control_Serial1.h"
#include "g_cmd_Websocket.h"
#include "g_arena_MQTT.h"





/*****************************************************************************
 * Definitions for configuration : GladiotorCfg
 *****************************************************************************/

//Declaration of instance variables
//Instance g
// Variables for the properties of the instance
uint8_t array_g_Gladiotor_ip__var[4];
struct Gladiotor_Instance g_var;



//New dispatcher for messages
void dispatch_gameStart(uint16_t sender) {
if (sender == MQTT_instance.listener_id) {
Gladiotor_handle_arena_gameStart(&g_var);

}

}


//New dispatcher for messages
void dispatch_shootCmd(uint16_t sender, uint8_t param_ID) {
if (sender == Websocket_instance.listener_id) {
Gladiotor_handle_cmd_shootCmd(&g_var, param_ID);

}

}


//New dispatcher for messages
void dispatch_ready(uint16_t sender) {
if (sender == Serial1_instance.listener_id) {
Gladiotor_handle_control_ready(&g_var);

}

}


//New dispatcher for messages
void dispatch_assignID(uint16_t sender, uint8_t param_ID, uint8_t param_ip1, uint8_t param_ip2, uint8_t param_ip3, uint8_t param_ip4) {
if (sender == MQTT_instance.listener_id) {
Gladiotor_handle_arena_assignID(&g_var, param_ID, param_ip1, param_ip2, param_ip3, param_ip4);

}

}


//New dispatcher for messages
void dispatch_beenHit(uint16_t sender, uint8_t param_IDshooter) {
if (sender == Serial1_instance.listener_id) {
Gladiotor_handle_control_beenHit(&g_var, param_IDshooter);

}

}


//New dispatcher for messages
void dispatch_gameStop(uint16_t sender) {
if (sender == MQTT_instance.listener_id) {
Gladiotor_handle_arena_gameStop(&g_var);

}

}


int processMessageQueue() {
fifo_lock();
while (fifo_empty()) fifo_wait();
byte mbuf[7];
uint8_t mbufi = 0;

// Read the code of the next port/message in the queue
uint16_t code = fifo_dequeue() << 8;

code += fifo_dequeue();

// Switch to call the appropriate handler
switch(code) {
case 101:
while (mbufi < 7) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
union u_assignID_ID_t {
uint8_t p;
byte bytebuffer[1];
} u_assignID_ID;
u_assignID_ID.bytebuffer[0] = mbuf[2];
union u_assignID_ip1_t {
uint8_t p;
byte bytebuffer[1];
} u_assignID_ip1;
u_assignID_ip1.bytebuffer[0] = mbuf[3];
union u_assignID_ip2_t {
uint8_t p;
byte bytebuffer[1];
} u_assignID_ip2;
u_assignID_ip2.bytebuffer[0] = mbuf[4];
union u_assignID_ip3_t {
uint8_t p;
byte bytebuffer[1];
} u_assignID_ip3;
u_assignID_ip3.bytebuffer[0] = mbuf[5];
union u_assignID_ip4_t {
uint8_t p;
byte bytebuffer[1];
} u_assignID_ip4;
u_assignID_ip4.bytebuffer[0] = mbuf[6];
dispatch_assignID((mbuf[0] << 8) + mbuf[1] /* instance port*/,
 u_assignID_ID.p /* ID */ ,
 u_assignID_ip1.p /* ip1 */ ,
 u_assignID_ip2.p /* ip2 */ ,
 u_assignID_ip3.p /* ip3 */ ,
 u_assignID_ip4.p /* ip4 */ );
break;
case 103:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_gameStart((mbuf[0] << 8) + mbuf[1] /* instance port*/);
break;
case 201:
while (mbufi < 3) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
union u_shootCmd_ID_t {
uint8_t p;
byte bytebuffer[1];
} u_shootCmd_ID;
u_shootCmd_ID.bytebuffer[0] = mbuf[2];
dispatch_shootCmd((mbuf[0] << 8) + mbuf[1] /* instance port*/,
 u_shootCmd_ID.p /* ID */ );
break;
case 202:
while (mbufi < 3) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
union u_beenHit_IDshooter_t {
uint8_t p;
byte bytebuffer[1];
} u_beenHit_IDshooter;
u_beenHit_IDshooter.bytebuffer[0] = mbuf[2];
dispatch_beenHit((mbuf[0] << 8) + mbuf[1] /* instance port*/,
 u_beenHit_IDshooter.p /* IDshooter */ );
break;
case 104:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_gameStop((mbuf[0] << 8) + mbuf[1] /* instance port*/);
break;
case 200:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_ready((mbuf[0] << 8) + mbuf[1] /* instance port*/);
break;
}
return 1;
}

// Forwarding of messages Serial1::Gladiotor::control::shootCmd
void forward_Serial1_Gladiotor_send_control_shootCmd(struct Gladiotor_Instance *_instance, uint8_t ID){
byte forward_buf[3];
forward_buf[0] = (201 >> 8) & 0xFF;
forward_buf[1] =  201 & 0xFF;


// parameter ID
union u_ID_t {
uint8_t p;
byte bytebuffer[1];
} u_ID;
u_ID.p = ID;
forward_buf[2] =  (u_ID.bytebuffer[0] & 0xFF);

//Forwarding with specified function 
Serial1_forwardMessage(forward_buf, 3);
}

// Forwarding of messages Websocket::Gladiotor::cmd::beenHit
void forward_Websocket_Gladiotor_send_cmd_beenHit(struct Gladiotor_Instance *_instance, uint8_t IDshooter){
byte forward_buf[10];
sprintf((unsigned char *) &forward_buf[0], "%03i", (unsigned char) ((202 >> 8) & 0xFF));
sprintf((unsigned char *) &forward_buf[3], "%03i", (unsigned char) (202 & 0xFF));

// parameter IDshooter
union u_IDshooter_t {
uint8_t p;
byte bytebuffer[1];
} u_IDshooter;
u_IDshooter.p = IDshooter;
sprintf((unsigned char *) &forward_buf[6], "%03i", (unsigned char) (u_IDshooter.bytebuffer[0] & 0xFF));

//Forwarding with specified function 
Websocket_forwardMessage(forward_buf, 10);
}

// Forwarding of messages MQTT::Gladiotor::arena::register
void forward_MQTT_Gladiotor_send_arena_register(struct Gladiotor_Instance *_instance, uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4){
byte forward_buf[19];
sprintf((unsigned char *) &forward_buf[0], "%03i", (unsigned char) ((100 >> 8) & 0xFF));
sprintf((unsigned char *) &forward_buf[3], "%03i", (unsigned char) (100 & 0xFF));

// parameter ip1
union u_ip1_t {
uint8_t p;
byte bytebuffer[1];
} u_ip1;
u_ip1.p = ip1;
sprintf((unsigned char *) &forward_buf[6], "%03i", (unsigned char) (u_ip1.bytebuffer[0] & 0xFF));

// parameter ip2
union u_ip2_t {
uint8_t p;
byte bytebuffer[1];
} u_ip2;
u_ip2.p = ip2;
sprintf((unsigned char *) &forward_buf[9], "%03i", (unsigned char) (u_ip2.bytebuffer[0] & 0xFF));

// parameter ip3
union u_ip3_t {
uint8_t p;
byte bytebuffer[1];
} u_ip3;
u_ip3.p = ip3;
sprintf((unsigned char *) &forward_buf[12], "%03i", (unsigned char) (u_ip3.bytebuffer[0] & 0xFF));

// parameter ip4
union u_ip4_t {
uint8_t p;
byte bytebuffer[1];
} u_ip4;
u_ip4.p = ip4;
sprintf((unsigned char *) &forward_buf[15], "%03i", (unsigned char) (u_ip4.bytebuffer[0] & 0xFF));

//Forwarding with specified function 
MQTT_forwardMessage(forward_buf, 19);
}

// Forwarding of messages MQTT::Gladiotor::arena::unregister
void forward_MQTT_Gladiotor_send_arena_unregister(struct Gladiotor_Instance *_instance, uint8_t ID){
byte forward_buf[10];
sprintf((unsigned char *) &forward_buf[0], "%03i", (unsigned char) ((102 >> 8) & 0xFF));
sprintf((unsigned char *) &forward_buf[3], "%03i", (unsigned char) (102 & 0xFF));

// parameter ID
union u_ID_t {
uint8_t p;
byte bytebuffer[1];
} u_ID;
u_ID.p = ID;
sprintf((unsigned char *) &forward_buf[6], "%03i", (unsigned char) (u_ID.bytebuffer[0] & 0xFF));

//Forwarding with specified function 
MQTT_forwardMessage(forward_buf, 10);
}

// Forwarding of messages MQTT::Gladiotor::arena::shooting
void forward_MQTT_Gladiotor_send_arena_shooting(struct Gladiotor_Instance *_instance, uint8_t ID, uint8_t time0, uint8_t time1){
byte forward_buf[16];
sprintf((unsigned char *) &forward_buf[0], "%03i", (unsigned char) ((1 >> 8) & 0xFF));
sprintf((unsigned char *) &forward_buf[3], "%03i", (unsigned char) (1 & 0xFF));

// parameter ID
union u_ID_t {
uint8_t p;
byte bytebuffer[1];
} u_ID;
u_ID.p = ID;
sprintf((unsigned char *) &forward_buf[6], "%03i", (unsigned char) (u_ID.bytebuffer[0] & 0xFF));

// parameter time0
union u_time0_t {
uint8_t p;
byte bytebuffer[1];
} u_time0;
u_time0.p = time0;
sprintf((unsigned char *) &forward_buf[9], "%03i", (unsigned char) (u_time0.bytebuffer[0] & 0xFF));

// parameter time1
union u_time1_t {
uint8_t p;
byte bytebuffer[1];
} u_time1;
u_time1.p = time1;
sprintf((unsigned char *) &forward_buf[12], "%03i", (unsigned char) (u_time1.bytebuffer[0] & 0xFF));

//Forwarding with specified function 
MQTT_forwardMessage(forward_buf, 16);
}

// Forwarding of messages MQTT::Gladiotor::arena::hitInfo
void forward_MQTT_Gladiotor_send_arena_hitInfo(struct Gladiotor_Instance *_instance, uint8_t ID, uint8_t IDshooter){
byte forward_buf[13];
sprintf((unsigned char *) &forward_buf[0], "%03i", (unsigned char) ((2 >> 8) & 0xFF));
sprintf((unsigned char *) &forward_buf[3], "%03i", (unsigned char) (2 & 0xFF));

// parameter ID
union u_ID_t {
uint8_t p;
byte bytebuffer[1];
} u_ID;
u_ID.p = ID;
sprintf((unsigned char *) &forward_buf[6], "%03i", (unsigned char) (u_ID.bytebuffer[0] & 0xFF));

// parameter IDshooter
union u_IDshooter_t {
uint8_t p;
byte bytebuffer[1];
} u_IDshooter;
u_IDshooter.p = IDshooter;
sprintf((unsigned char *) &forward_buf[9], "%03i", (unsigned char) (u_IDshooter.bytebuffer[0] & 0xFF));

//Forwarding with specified function 
MQTT_forwardMessage(forward_buf, 13);
}

void forward_Gladiotor_send_arena_register(struct Gladiotor_Instance *_instance, uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4){
if(_instance->id_arena == g_var.id_arena) {
forward_MQTT_Gladiotor_send_arena_register(_instance, ip1, ip2, ip3, ip4);
}
}
void forward_Gladiotor_send_control_shootCmd(struct Gladiotor_Instance *_instance, uint8_t ID){
if(_instance->id_control == g_var.id_control) {
forward_Serial1_Gladiotor_send_control_shootCmd(_instance, ID);
}
}
void forward_Gladiotor_send_arena_unregister(struct Gladiotor_Instance *_instance, uint8_t ID){
if(_instance->id_arena == g_var.id_arena) {
forward_MQTT_Gladiotor_send_arena_unregister(_instance, ID);
}
}
void forward_Gladiotor_send_arena_shooting(struct Gladiotor_Instance *_instance, uint8_t ID, uint8_t time0, uint8_t time1){
if(_instance->id_arena == g_var.id_arena) {
forward_MQTT_Gladiotor_send_arena_shooting(_instance, ID, time0, time1);
}
}
void forward_Gladiotor_send_cmd_beenHit(struct Gladiotor_Instance *_instance, uint8_t IDshooter){
if(_instance->id_cmd == g_var.id_cmd) {
forward_Websocket_Gladiotor_send_cmd_beenHit(_instance, IDshooter);
}
}
void forward_Gladiotor_send_arena_hitInfo(struct Gladiotor_Instance *_instance, uint8_t ID, uint8_t IDshooter){
if(_instance->id_arena == g_var.id_arena) {
forward_MQTT_Gladiotor_send_arena_hitInfo(_instance, ID, IDshooter);
}
}

//external Message enqueue
void externalMessageEnqueue(uint8_t * msg, uint8_t msgSize, uint16_t listener_id) {
if ((msgSize >= 2) && (msg != NULL)) {
uint8_t msgSizeOK = 0;
switch(msg[0] * 256 + msg[1]) {
case 101:
if(msgSize == 7) {
msgSizeOK = 1;}
break;
case 103:
if(msgSize == 2) {
msgSizeOK = 1;}
break;
case 201:
if(msgSize == 3) {
msgSizeOK = 1;}
break;
case 202:
if(msgSize == 3) {
msgSizeOK = 1;}
break;
case 104:
if(msgSize == 2) {
msgSizeOK = 1;}
break;
case 200:
if(msgSize == 2) {
msgSizeOK = 1;}
break;
}

if(msgSizeOK == 1) {
fifo_lock();
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
fifo_unlock_and_notify();
}
}
}

void initialize_configuration_GladiotorCfg() {
// Initialize connectors
register_external_Gladiotor_send_control_shootCmd_listener(&forward_Gladiotor_send_control_shootCmd);
register_external_Gladiotor_send_cmd_beenHit_listener(&forward_Gladiotor_send_cmd_beenHit);
register_external_Gladiotor_send_arena_register_listener(&forward_Gladiotor_send_arena_register);
register_external_Gladiotor_send_arena_unregister_listener(&forward_Gladiotor_send_arena_unregister);
register_external_Gladiotor_send_arena_shooting_listener(&forward_Gladiotor_send_arena_shooting);
register_external_Gladiotor_send_arena_hitInfo_listener(&forward_Gladiotor_send_arena_hitInfo);

// Init the ID, state variables and properties for external connector Serial1
// Init the ID, state variables and properties for external connector Websocket
// Init the ID, state variables and properties for external connector MQTT

// Network Initilization 


Websocket_instance.listener_id = add_instance(&Websocket_instance);

//Websocket:
Websocket_setup();
pthread_t thread_g_cmd_Websocket;
pthread_create( &thread_g_cmd_Websocket, NULL, Websocket_start_receiver_process, NULL);


MQTT_instance.listener_id = add_instance(&MQTT_instance);

//MQTT:
MQTT_setup();
pthread_t thread_g_arena_MQTT;
pthread_create( &thread_g_arena_MQTT, NULL, MQTT_start_receiver_process, NULL);


Serial1_instance.listener_id = add_instance(&Serial1_instance);

//Serial1:
Serial1_setup();
pthread_t thread_g_control_Serial1;
pthread_create( &thread_g_control_Serial1, NULL, Serial1_start_receiver_process, NULL);


// End Network Initilization 

// Init the ID, state variables and properties for instance g
g_var.id_cmd = add_instance( (void*) &g_var);
g_var.id_control = add_instance( (void*) &g_var);
g_var.id_arena = add_instance( (void*) &g_var);
g_var.Gladiotor_C_State = GLADIOTOR_C_INIT_STATE;
g_var.Gladiotor_C_Game_State = GLADIOTOR_C_GAME_IDENTIFICATION_STATE;
g_var.Gladiotor_ID__var = 0;
g_var.Gladiotor_InactiveTime__var = 1000;
g_var.Gladiotor_ip__var = array_g_Gladiotor_ip__var;
g_var.Gladiotor_ip__var[1] = 168;
g_var.Gladiotor_ip__var[0] = 192;
g_var.Gladiotor_ip__var[2] = 43;
g_var.Gladiotor_ip__var[3] = 101;

Gladiotor_C_OnEntry(GLADIOTOR_C_STATE, &g_var);
}




int main(int argc, char *argv[]) {
  init_runtime();
  
  initialize_configuration_GladiotorCfg();

  while (1) {
    
// Network Listener
int emptyEventConsumed = 1;
while (emptyEventConsumed != 0) {
emptyEventConsumed = 0;
emptyEventConsumed += Gladiotor_handle_empty_event(&g_var);
}

    processMessageQueue();
  }
}