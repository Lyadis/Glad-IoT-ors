/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *           Header for Thing Server
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#ifndef Server_H_
#define Server_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "thingml_typedefs.h"

/*****************************************************************************
 * Headers for type : Server
 *****************************************************************************/

// Definition of the instance stuct:
struct Server_Instance {
// Variables for the ID of the ports of the instance
uint16_t id_arena;
uint16_t id_gui;
uint16_t id_clock;
// Variables for the current instance state
int Server_S_State;
int Server_S_Running_State;
// Variables for the properties of the instance
uint8_t Server_nextId__var;
uint8_t * Server_registered__var;
int16_t * Server_scores__var;
int16_t * Server_shots__var;
int16_t * Server_hits__var;
uint8_t * Server_ips1__var;
uint8_t * Server_ips2__var;
uint8_t * Server_ips3__var;
uint8_t * Server_ips4__var;
uint16_t Server_playTime__var;
uint16_t Server_timeLeft__var;
uint8_t Server_n__var;

};
// Declaration of prototypes outgoing messages:
void Server_S_OnEntry(int state, struct Server_Instance *_instance);
void Server_handle_clock_clock_tick(struct Server_Instance *_instance);
void Server_handle_arena_register(struct Server_Instance *_instance, uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4);
void Server_handle_arena_shooting(struct Server_Instance *_instance, uint8_t ID, uint8_t time0, uint8_t time1);
void Server_handle_arena_unregister(struct Server_Instance *_instance, uint8_t ID);
void Server_handle_arena_hitInfo(struct Server_Instance *_instance, uint8_t ID, uint8_t IDshooter);
void Server_handle_gui_getGameStatus(struct Server_Instance *_instance);
void Server_handle_gui_listStatuses(struct Server_Instance *_instance);
// Declaration of callbacks for incoming messages:
void register_Server_send_arena_assignID_listener(void (*_listener)(struct Server_Instance *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t));
void register_external_Server_send_arena_assignID_listener(void (*_listener)(struct Server_Instance *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t));
void register_Server_send_arena_gameStart_listener(void (*_listener)(struct Server_Instance *));
void register_external_Server_send_arena_gameStart_listener(void (*_listener)(struct Server_Instance *));
void register_Server_send_arena_gameStop_listener(void (*_listener)(struct Server_Instance *));
void register_external_Server_send_arena_gameStop_listener(void (*_listener)(struct Server_Instance *));
void register_Server_send_gui_gameStatus_listener(void (*_listener)(struct Server_Instance *, uint8_t));
void register_external_Server_send_gui_gameStatus_listener(void (*_listener)(struct Server_Instance *, uint8_t));
void register_Server_send_gui_secondsLeft_listener(void (*_listener)(struct Server_Instance *, uint16_t));
void register_external_Server_send_gui_secondsLeft_listener(void (*_listener)(struct Server_Instance *, uint16_t));
void register_Server_send_gui_teamStatus_listener(void (*_listener)(struct Server_Instance *, uint8_t, uint8_t, int16_t, int16_t, int16_t, uint8_t, uint8_t, uint8_t, uint8_t));
void register_external_Server_send_gui_teamStatus_listener(void (*_listener)(struct Server_Instance *, uint8_t, uint8_t, int16_t, int16_t, int16_t, uint8_t, uint8_t, uint8_t, uint8_t));

// Definition of the states:
#define SERVER_S_STATE 0
#define SERVER_S_INIT_STATE 1
#define SERVER_S_RUNNING_STATE 2
#define SERVER_S_RUNNING_LOUNGE_STATE 3
#define SERVER_S_RUNNING_PLAYING_STATE 4



#ifdef __cplusplus
}
#endif

#endif //Server_H_
