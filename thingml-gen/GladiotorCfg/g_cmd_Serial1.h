#ifndef PosixSerialForward_h

#define PosixSerialForward_h

#include "g_cmd_Serial1.c"Serial1_instance;

struct Serial1_instance_type Serial1_instance;

void Serial1_set_listener_id(uint16_t id);
int Serial1_setup();
void Serial1_forwardMessage(byte * msg, uint8_t size);
void Serial1_start_receiver_process();

#endif
