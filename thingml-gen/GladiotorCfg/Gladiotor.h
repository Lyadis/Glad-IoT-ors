/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *           Header for Thing Gladiotor
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#ifndef Gladiotor_H_
#define Gladiotor_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "thingml_typedefs.h"

/*****************************************************************************
 * Headers for type : Gladiotor
 *****************************************************************************/

// Definition of the instance stuct:
struct Gladiotor_Instance {
// Variables for the ID of the ports of the instance
uint16_t id_cmd;
uint16_t id_control;
uint16_t id_arena;
// Variables for the current instance state
int Gladiotor_C_State;
int Gladiotor_C_Game_State;
// Variables for the properties of the instance
uint8_t Gladiotor_ID__var;
uint32_t Gladiotor_InactiveTime__var;
uint8_t * Gladiotor_ip__var;

};
// Declaration of prototypes outgoing messages:
void Gladiotor_C_OnEntry(int state, struct Gladiotor_Instance *_instance);
void Gladiotor_handle_control_timeout(struct Gladiotor_Instance *_instance, uint8_t id);
void Gladiotor_handle_control_ready(struct Gladiotor_Instance *_instance);
void Gladiotor_handle_control_beenHit(struct Gladiotor_Instance *_instance, uint8_t IDshooter);
void Gladiotor_handle_arena_gameStart(struct Gladiotor_Instance *_instance);
void Gladiotor_handle_arena_gameStop(struct Gladiotor_Instance *_instance);
void Gladiotor_handle_arena_assignID(struct Gladiotor_Instance *_instance, uint8_t ID, uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4);
void Gladiotor_handle_cmd_shootCmd(struct Gladiotor_Instance *_instance, uint8_t ID);
// Declaration of callbacks for incoming messages:
void register_Gladiotor_send_cmd_beenHit_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t));
void register_external_Gladiotor_send_cmd_beenHit_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t));
void register_Gladiotor_send_control_shootCmd_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t));
void register_external_Gladiotor_send_control_shootCmd_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t));
void register_Gladiotor_send_control_timer_start_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t, uint32_t));
void register_external_Gladiotor_send_control_timer_start_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t, uint32_t));
void register_Gladiotor_send_control_timer_cancel_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t));
void register_external_Gladiotor_send_control_timer_cancel_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t));
void register_Gladiotor_send_arena_register_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t, uint8_t, uint8_t, uint8_t));
void register_external_Gladiotor_send_arena_register_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t, uint8_t, uint8_t, uint8_t));
void register_Gladiotor_send_arena_unregister_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t));
void register_external_Gladiotor_send_arena_unregister_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t));
void register_Gladiotor_send_arena_shooting_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t, uint8_t, uint8_t));
void register_external_Gladiotor_send_arena_shooting_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t, uint8_t, uint8_t));
void register_Gladiotor_send_arena_hitInfo_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t, uint8_t));
void register_external_Gladiotor_send_arena_hitInfo_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t, uint8_t));

// Definition of the states:
#define GLADIOTOR_C_STATE 0
#define GLADIOTOR_C_INIT_STATE 1
#define GLADIOTOR_C_GAME_STATE 2
#define GLADIOTOR_C_GAME_IDENTIFICATION_STATE 3
#define GLADIOTOR_C_GAME_WAIT_STATE 4
#define GLADIOTOR_C_GAME_ACTIVE_STATE 5
#define GLADIOTOR_C_GAME_INACTIVE_STATE 6



#ifdef __cplusplus
}
#endif

#endif //Gladiotor_H_
