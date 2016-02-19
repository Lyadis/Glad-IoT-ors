#ifndef MQTT_PosixMQTT_Client_h
#define  MQTT_PosixMQTT_Client_h



#include "s_arena_MQTT.c"MQTT_instance;

struct MQTT_instance_type MQTT_instance;


void MQTT_set_listener_id(uint16_t id);


void MQTT_setup();

void MQTT_start_receiver_process();

void MQTT_forwardMessage(uint8_t * msg, int size);

#endif
