/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *      Implementation for Application ServerCfg
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
#include "Server.h"
#include "ClockLinux.h"
#include "s_arena_MQTT.h"
#include "s_gui_Websocket.h"





/*****************************************************************************
 * Definitions for configuration : ServerCfg
 *****************************************************************************/

//Declaration of instance variables
//Instance c
// Variables for the properties of the instance
struct ClockLinux_Instance c_var;
//Instance s
// Variables for the properties of the instance
uint8_t array_s_Server_registered__var[256];
int16_t array_s_Server_scores__var[256];
int16_t array_s_Server_shots__var[256];
int16_t array_s_Server_hits__var[256];
uint8_t array_s_Server_ips1__var[256];
uint8_t array_s_Server_ips2__var[256];
uint8_t array_s_Server_ips3__var[256];
uint8_t array_s_Server_ips4__var[256];
struct Server_Instance s_var;

// Enqueue of messages ClockLinux::signal::clock_tick
void enqueue_ClockLinux_send_signal_clock_tick(struct ClockLinux_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (3 >> 8) & 0xFF );
_fifo_enqueue( 3 & 0xFF );

// ID of the source port of the instance
_fifo_enqueue( (_instance->id_signal >> 8) & 0xFF );
_fifo_enqueue( _instance->id_signal & 0xFF );
}
fifo_unlock_and_notify();
}


//New dispatcher for messages
void dispatch_clock_tick(uint16_t sender) {
if (sender == c_var.id_signal) {
Server_handle_clock_clock_tick(&s_var);

}

}


//New dispatcher for messages
void dispatch_listStatuses(uint16_t sender) {
if (sender == Websocket_instance.listener_id) {
Server_handle_gui_listStatuses(&s_var);

}

}


//New dispatcher for messages
void dispatch_register(uint16_t sender, uint8_t param_ip1, uint8_t param_ip2, uint8_t param_ip3, uint8_t param_ip4) {
if (sender == MQTT_instance.listener_id) {
Server_handle_arena_register(&s_var, param_ip1, param_ip2, param_ip3, param_ip4);

}

}


//New dispatcher for messages
void dispatch_hitInfo(uint16_t sender, uint8_t param_ID, uint8_t param_IDshooter) {
if (sender == MQTT_instance.listener_id) {
Server_handle_arena_hitInfo(&s_var, param_ID, param_IDshooter);

}

}


//New dispatcher for messages
void dispatch_gui_gameStop(uint16_t sender) {
if (sender == Websocket_instance.listener_id) {

}

}


//New dispatcher for messages
void dispatch_getGameStatus(uint16_t sender) {
if (sender == Websocket_instance.listener_id) {
Server_handle_gui_getGameStatus(&s_var);

}

}


//New dispatcher for messages
void dispatch_shooting(uint16_t sender, uint8_t param_ID, uint8_t param_time0, uint8_t param_time1) {
if (sender == MQTT_instance.listener_id) {
Server_handle_arena_shooting(&s_var, param_ID, param_time0, param_time1);

}

}


//New dispatcher for messages
void dispatch_gui_gameStart(uint16_t sender) {
if (sender == Websocket_instance.listener_id) {

}

}


//New dispatcher for messages
void dispatch_unregister(uint16_t sender, uint8_t param_ID) {
if (sender == MQTT_instance.listener_id) {
Server_handle_arena_unregister(&s_var, param_ID);

}

}


int processMessageQueue() {
fifo_lock();
while (fifo_empty()) fifo_wait();
byte mbuf[6];
uint8_t mbufi = 0;

// Read the code of the next port/message in the queue
uint16_t code = fifo_dequeue() << 8;

code += fifo_dequeue();

// Switch to call the appropriate handler
switch(code) {
case 3:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_clock_tick((mbuf[0] << 8) + mbuf[1] /* instance port*/);
break;
case 4:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_listStatuses((mbuf[0] << 8) + mbuf[1] /* instance port*/);
break;
case 100:
while (mbufi < 6) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
union u_register_ip1_t {
uint8_t p;
byte bytebuffer[1];
} u_register_ip1;
u_register_ip1.bytebuffer[0] = mbuf[2];
union u_register_ip2_t {
uint8_t p;
byte bytebuffer[1];
} u_register_ip2;
u_register_ip2.bytebuffer[0] = mbuf[3];
union u_register_ip3_t {
uint8_t p;
byte bytebuffer[1];
} u_register_ip3;
u_register_ip3.bytebuffer[0] = mbuf[4];
union u_register_ip4_t {
uint8_t p;
byte bytebuffer[1];
} u_register_ip4;
u_register_ip4.bytebuffer[0] = mbuf[5];
dispatch_register((mbuf[0] << 8) + mbuf[1] /* instance port*/,
 u_register_ip1.p /* ip1 */ ,
 u_register_ip2.p /* ip2 */ ,
 u_register_ip3.p /* ip3 */ ,
 u_register_ip4.p /* ip4 */ );
break;
case 2:
while (mbufi < 4) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
union u_hitInfo_ID_t {
uint8_t p;
byte bytebuffer[1];
} u_hitInfo_ID;
u_hitInfo_ID.bytebuffer[0] = mbuf[2];
union u_hitInfo_IDshooter_t {
uint8_t p;
byte bytebuffer[1];
} u_hitInfo_IDshooter;
u_hitInfo_IDshooter.bytebuffer[0] = mbuf[3];
dispatch_hitInfo((mbuf[0] << 8) + mbuf[1] /* instance port*/,
 u_hitInfo_ID.p /* ID */ ,
 u_hitInfo_IDshooter.p /* IDshooter */ );
break;
case 1:
while (mbufi < 5) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
union u_shooting_ID_t {
uint8_t p;
byte bytebuffer[1];
} u_shooting_ID;
u_shooting_ID.bytebuffer[0] = mbuf[2];
union u_shooting_time0_t {
uint8_t p;
byte bytebuffer[1];
} u_shooting_time0;
u_shooting_time0.bytebuffer[0] = mbuf[3];
union u_shooting_time1_t {
uint8_t p;
byte bytebuffer[1];
} u_shooting_time1;
u_shooting_time1.bytebuffer[0] = mbuf[4];
dispatch_shooting((mbuf[0] << 8) + mbuf[1] /* instance port*/,
 u_shooting_ID.p /* ID */ ,
 u_shooting_time0.p /* time0 */ ,
 u_shooting_time1.p /* time1 */ );
break;
case 5:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_gui_gameStop((mbuf[0] << 8) + mbuf[1] /* instance port*/);
break;
case 6:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_gui_gameStart((mbuf[0] << 8) + mbuf[1] /* instance port*/);
break;
case 7:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_getGameStatus((mbuf[0] << 8) + mbuf[1] /* instance port*/);
break;
case 102:
while (mbufi < 3) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
union u_unregister_ID_t {
uint8_t p;
byte bytebuffer[1];
} u_unregister_ID;
u_unregister_ID.bytebuffer[0] = mbuf[2];
dispatch_unregister((mbuf[0] << 8) + mbuf[1] /* instance port*/,
 u_unregister_ID.p /* ID */ );
break;
}
return 1;
}

// Forwarding of messages MQTT::Server::arena::assignID
void forward_MQTT_Server_send_arena_assignID(struct Server_Instance *_instance, uint8_t ID, uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4){
byte forward_buf[22];
sprintf((unsigned char *) &forward_buf[0], "%03i", (unsigned char) ((101 >> 8) & 0xFF));
sprintf((unsigned char *) &forward_buf[3], "%03i", (unsigned char) (101 & 0xFF));

// parameter ID
union u_ID_t {
uint8_t p;
byte bytebuffer[1];
} u_ID;
u_ID.p = ID;
sprintf((unsigned char *) &forward_buf[6], "%03i", (unsigned char) (u_ID.bytebuffer[0] & 0xFF));

// parameter ip1
union u_ip1_t {
uint8_t p;
byte bytebuffer[1];
} u_ip1;
u_ip1.p = ip1;
sprintf((unsigned char *) &forward_buf[9], "%03i", (unsigned char) (u_ip1.bytebuffer[0] & 0xFF));

// parameter ip2
union u_ip2_t {
uint8_t p;
byte bytebuffer[1];
} u_ip2;
u_ip2.p = ip2;
sprintf((unsigned char *) &forward_buf[12], "%03i", (unsigned char) (u_ip2.bytebuffer[0] & 0xFF));

// parameter ip3
union u_ip3_t {
uint8_t p;
byte bytebuffer[1];
} u_ip3;
u_ip3.p = ip3;
sprintf((unsigned char *) &forward_buf[15], "%03i", (unsigned char) (u_ip3.bytebuffer[0] & 0xFF));

// parameter ip4
union u_ip4_t {
uint8_t p;
byte bytebuffer[1];
} u_ip4;
u_ip4.p = ip4;
sprintf((unsigned char *) &forward_buf[18], "%03i", (unsigned char) (u_ip4.bytebuffer[0] & 0xFF));

//Forwarding with specified function 
MQTT_forwardMessage(forward_buf, 22);
}

// Forwarding of messages MQTT::Server::arena::gameStart
void forward_MQTT_Server_send_arena_gameStart(struct Server_Instance *_instance){
byte forward_buf[7];
sprintf((unsigned char *) &forward_buf[0], "%03i", (unsigned char) ((103 >> 8) & 0xFF));
sprintf((unsigned char *) &forward_buf[3], "%03i", (unsigned char) (103 & 0xFF));

//Forwarding with specified function 
MQTT_forwardMessage(forward_buf, 7);
}

// Forwarding of messages MQTT::Server::arena::gameStop
void forward_MQTT_Server_send_arena_gameStop(struct Server_Instance *_instance){
byte forward_buf[7];
sprintf((unsigned char *) &forward_buf[0], "%03i", (unsigned char) ((104 >> 8) & 0xFF));
sprintf((unsigned char *) &forward_buf[3], "%03i", (unsigned char) (104 & 0xFF));

//Forwarding with specified function 
MQTT_forwardMessage(forward_buf, 7);
}

// Forwarding of messages Websocket::Server::gui::gameStatus
void forward_Websocket_Server_send_gui_gameStatus(struct Server_Instance *_instance, uint8_t playing){
byte forward_buf[10];
sprintf((unsigned char *) &forward_buf[0], "%03i", (unsigned char) ((8 >> 8) & 0xFF));
sprintf((unsigned char *) &forward_buf[3], "%03i", (unsigned char) (8 & 0xFF));

// parameter playing
union u_playing_t {
uint8_t p;
byte bytebuffer[1];
} u_playing;
u_playing.p = playing;
sprintf((unsigned char *) &forward_buf[6], "%03i", (unsigned char) (u_playing.bytebuffer[0] & 0xFF));

//Forwarding with specified function 
Websocket_forwardMessage(forward_buf, 10);
}

// Forwarding of messages Websocket::Server::gui::secondsLeft
void forward_Websocket_Server_send_gui_secondsLeft(struct Server_Instance *_instance, uint16_t secs){
byte forward_buf[13];
sprintf((unsigned char *) &forward_buf[0], "%03i", (unsigned char) ((9 >> 8) & 0xFF));
sprintf((unsigned char *) &forward_buf[3], "%03i", (unsigned char) (9 & 0xFF));

// parameter secs
union u_secs_t {
uint16_t p;
byte bytebuffer[2];
} u_secs;
u_secs.p = secs;
sprintf((unsigned char *) &forward_buf[6], "%03i", (unsigned char) (u_secs.bytebuffer[1] & 0xFF));
sprintf((unsigned char *) &forward_buf[9], "%03i", (unsigned char) (u_secs.bytebuffer[0] & 0xFF));

//Forwarding with specified function 
Websocket_forwardMessage(forward_buf, 13);
}

// Forwarding of messages Websocket::Server::gui::teamStatus
void forward_Websocket_Server_send_gui_teamStatus(struct Server_Instance *_instance, uint8_t ID, uint8_t registered, int16_t score, int16_t shots, int16_t hits, uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4){
byte forward_buf[43];
sprintf((unsigned char *) &forward_buf[0], "%03i", (unsigned char) ((10 >> 8) & 0xFF));
sprintf((unsigned char *) &forward_buf[3], "%03i", (unsigned char) (10 & 0xFF));

// parameter ID
union u_ID_t {
uint8_t p;
byte bytebuffer[1];
} u_ID;
u_ID.p = ID;
sprintf((unsigned char *) &forward_buf[6], "%03i", (unsigned char) (u_ID.bytebuffer[0] & 0xFF));

// parameter registered
union u_registered_t {
uint8_t p;
byte bytebuffer[1];
} u_registered;
u_registered.p = registered;
sprintf((unsigned char *) &forward_buf[9], "%03i", (unsigned char) (u_registered.bytebuffer[0] & 0xFF));

// parameter score
union u_score_t {
int16_t p;
byte bytebuffer[2];
} u_score;
u_score.p = score;
sprintf((unsigned char *) &forward_buf[12], "%03i", (unsigned char) (u_score.bytebuffer[1] & 0xFF));
sprintf((unsigned char *) &forward_buf[15], "%03i", (unsigned char) (u_score.bytebuffer[0] & 0xFF));

// parameter shots
union u_shots_t {
int16_t p;
byte bytebuffer[2];
} u_shots;
u_shots.p = shots;
sprintf((unsigned char *) &forward_buf[18], "%03i", (unsigned char) (u_shots.bytebuffer[1] & 0xFF));
sprintf((unsigned char *) &forward_buf[21], "%03i", (unsigned char) (u_shots.bytebuffer[0] & 0xFF));

// parameter hits
union u_hits_t {
int16_t p;
byte bytebuffer[2];
} u_hits;
u_hits.p = hits;
sprintf((unsigned char *) &forward_buf[24], "%03i", (unsigned char) (u_hits.bytebuffer[1] & 0xFF));
sprintf((unsigned char *) &forward_buf[27], "%03i", (unsigned char) (u_hits.bytebuffer[0] & 0xFF));

// parameter ip1
union u_ip1_t {
uint8_t p;
byte bytebuffer[1];
} u_ip1;
u_ip1.p = ip1;
sprintf((unsigned char *) &forward_buf[30], "%03i", (unsigned char) (u_ip1.bytebuffer[0] & 0xFF));

// parameter ip2
union u_ip2_t {
uint8_t p;
byte bytebuffer[1];
} u_ip2;
u_ip2.p = ip2;
sprintf((unsigned char *) &forward_buf[33], "%03i", (unsigned char) (u_ip2.bytebuffer[0] & 0xFF));

// parameter ip3
union u_ip3_t {
uint8_t p;
byte bytebuffer[1];
} u_ip3;
u_ip3.p = ip3;
sprintf((unsigned char *) &forward_buf[36], "%03i", (unsigned char) (u_ip3.bytebuffer[0] & 0xFF));

// parameter ip4
union u_ip4_t {
uint8_t p;
byte bytebuffer[1];
} u_ip4;
u_ip4.p = ip4;
sprintf((unsigned char *) &forward_buf[39], "%03i", (unsigned char) (u_ip4.bytebuffer[0] & 0xFF));

//Forwarding with specified function 
Websocket_forwardMessage(forward_buf, 43);
}

void forward_Server_send_arena_gameStop(struct Server_Instance *_instance){
if(_instance->id_arena == s_var.id_arena) {
forward_MQTT_Server_send_arena_gameStop(_instance);
}
}
void forward_Server_send_gui_secondsLeft(struct Server_Instance *_instance, uint16_t secs){
if(_instance->id_gui == s_var.id_gui) {
forward_Websocket_Server_send_gui_secondsLeft(_instance, secs);
}
}
void forward_Server_send_gui_gameStatus(struct Server_Instance *_instance, uint8_t playing){
if(_instance->id_gui == s_var.id_gui) {
forward_Websocket_Server_send_gui_gameStatus(_instance, playing);
}
}
void forward_Server_send_gui_teamStatus(struct Server_Instance *_instance, uint8_t ID, uint8_t registered, int16_t score, int16_t shots, int16_t hits, uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4){
if(_instance->id_gui == s_var.id_gui) {
forward_Websocket_Server_send_gui_teamStatus(_instance, ID, registered, score, shots, hits, ip1, ip2, ip3, ip4);
}
}
void forward_Server_send_arena_gameStart(struct Server_Instance *_instance){
if(_instance->id_arena == s_var.id_arena) {
forward_MQTT_Server_send_arena_gameStart(_instance);
}
}
void forward_Server_send_arena_assignID(struct Server_Instance *_instance, uint8_t ID, uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4){
if(_instance->id_arena == s_var.id_arena) {
forward_MQTT_Server_send_arena_assignID(_instance, ID, ip1, ip2, ip3, ip4);
}
}

//external Message enqueue
void externalMessageEnqueue(uint8_t * msg, uint8_t msgSize, uint16_t listener_id) {
if ((msgSize >= 2) && (msg != NULL)) {
uint8_t msgSizeOK = 0;
switch(msg[0] * 256 + msg[1]) {
case 4:
if(msgSize == 2) {
msgSizeOK = 1;}
break;
case 100:
if(msgSize == 6) {
msgSizeOK = 1;}
break;
case 2:
if(msgSize == 4) {
msgSizeOK = 1;}
break;
case 1:
if(msgSize == 5) {
msgSizeOK = 1;}
break;
case 5:
if(msgSize == 2) {
msgSizeOK = 1;}
break;
case 6:
if(msgSize == 2) {
msgSizeOK = 1;}
break;
case 7:
if(msgSize == 2) {
msgSizeOK = 1;}
break;
case 102:
if(msgSize == 3) {
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

void initialize_configuration_ServerCfg() {
// Initialize connectors
register_external_Server_send_arena_assignID_listener(&forward_Server_send_arena_assignID);
register_external_Server_send_arena_gameStart_listener(&forward_Server_send_arena_gameStart);
register_external_Server_send_arena_gameStop_listener(&forward_Server_send_arena_gameStop);
register_external_Server_send_gui_gameStatus_listener(&forward_Server_send_gui_gameStatus);
register_external_Server_send_gui_secondsLeft_listener(&forward_Server_send_gui_secondsLeft);
register_external_Server_send_gui_teamStatus_listener(&forward_Server_send_gui_teamStatus);
register_ClockLinux_send_signal_clock_tick_listener(&enqueue_ClockLinux_send_signal_clock_tick);

// Init the ID, state variables and properties for external connector MQTT
// Init the ID, state variables and properties for external connector Websocket

// Network Initilization 


Websocket_instance.listener_id = add_instance(&Websocket_instance);

//Websocket:
Websocket_setup();
pthread_t thread_s_gui_Websocket;
pthread_create( &thread_s_gui_Websocket, NULL, Websocket_start_receiver_process, NULL);


MQTT_instance.listener_id = add_instance(&MQTT_instance);

//MQTT:
MQTT_setup();
pthread_t thread_s_arena_MQTT;
pthread_create( &thread_s_arena_MQTT, NULL, MQTT_start_receiver_process, NULL);


// End Network Initilization 

// Init the ID, state variables and properties for instance c
c_var.id_signal = add_instance( (void*) &c_var);
c_var.ClockLinux_ClockImpl_State = CLOCKLINUX_CLOCKIMPL_TICKING_STATE;
c_var.Clock_period__var = 1000;

ClockLinux_ClockImpl_OnEntry(CLOCKLINUX_CLOCKIMPL_STATE, &c_var);
// Init the ID, state variables and properties for instance s
s_var.id_arena = add_instance( (void*) &s_var);
s_var.id_gui = add_instance( (void*) &s_var);
s_var.id_clock = add_instance( (void*) &s_var);
s_var.Server_S_State = SERVER_S_INIT_STATE;
s_var.Server_S_Running_State = SERVER_S_RUNNING_LOUNGE_STATE;
s_var.Server_nextId__var = 1;
s_var.Server_playTime__var = 300;
s_var.Server_timeLeft__var = 0;
s_var.Server_registered__var = array_s_Server_registered__var;
s_var.Server_scores__var = array_s_Server_scores__var;
s_var.Server_shots__var = array_s_Server_shots__var;
s_var.Server_hits__var = array_s_Server_hits__var;
s_var.Server_ips1__var = array_s_Server_ips1__var;
s_var.Server_ips2__var = array_s_Server_ips2__var;
s_var.Server_ips3__var = array_s_Server_ips3__var;
s_var.Server_ips4__var = array_s_Server_ips4__var;

Server_S_OnEntry(SERVER_S_STATE, &s_var);
}




int main(int argc, char *argv[]) {
  init_runtime();
  
  initialize_configuration_ServerCfg();

  while (1) {
    
// Network Listener
int emptyEventConsumed = 1;
while (emptyEventConsumed != 0) {
emptyEventConsumed = 0;
emptyEventConsumed += Server_handle_empty_event(&s_var);
}

    processMessageQueue();
  }
}