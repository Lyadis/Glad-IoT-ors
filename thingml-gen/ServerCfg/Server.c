/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *        Implementation for Thing Server
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#include "Server.h"

/*****************************************************************************
 * Implementation for type : Server
 *****************************************************************************/

// Declaration of prototypes:
void Server_S_OnExit(int state, struct Server_Instance *_instance);
void Server_send_arena_assignID(struct Server_Instance *_instance, uint8_t ID, uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4);
void Server_send_arena_gameStart(struct Server_Instance *_instance);
void Server_send_arena_gameStop(struct Server_Instance *_instance);
void Server_send_gui_gameStatus(struct Server_Instance *_instance, uint8_t playing);
void Server_send_gui_secondsLeft(struct Server_Instance *_instance, uint16_t secs);
void Server_send_gui_teamStatus(struct Server_Instance *_instance, uint8_t ID, uint8_t registered, int16_t score, int16_t shots, int16_t hits, uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4);
void f_Server_sendTeamStatus(struct Server_Instance *_instance, uint8_t ID);
// Declaration of functions:
// Definition of function sendTeamStatus
void f_Server_sendTeamStatus(struct Server_Instance *_instance, uint8_t ID) {
Server_send_gui_teamStatus(_instance, ID, _instance->Server_registered__var[ID]
, _instance->Server_scores__var[ID]
, _instance->Server_shots__var[ID]
, _instance->Server_hits__var[ID]
, _instance->Server_ips1__var[ID]
, _instance->Server_ips2__var[ID]
, _instance->Server_ips3__var[ID]
, _instance->Server_ips4__var[ID]
);
}

// On Entry Actions:
void Server_S_OnEntry(int state, struct Server_Instance *_instance) {
switch(state) {
case SERVER_S_STATE:
_instance->Server_S_State = SERVER_S_INIT_STATE;
Server_S_OnEntry(_instance->Server_S_State, _instance);
break;
case SERVER_S_RUNNING_STATE:
_instance->Server_S_Running_State = SERVER_S_RUNNING_LOUNGE_STATE;
Server_S_OnEntry(_instance->Server_S_Running_State, _instance);
break;
case SERVER_S_INIT_STATE:
fprintf(stdout, "Init server\n");
break;
case SERVER_S_RUNNING_LOUNGE_STATE:
Server_send_gui_gameStatus(_instance, 0);
Server_send_gui_secondsLeft(_instance, _instance->Server_playTime__var);
Server_send_arena_gameStop(_instance);
break;
case SERVER_S_RUNNING_PLAYING_STATE:
_instance->Server_n__var = 1;
while(_instance->Server_n__var < _instance->Server_nextId__var) {
if(_instance->Server_registered__var[_instance->Server_n__var]
 == 1) {
_instance->Server_scores__var[_instance->Server_n__var] = 0;
_instance->Server_shots__var[_instance->Server_n__var] = 0;
_instance->Server_hits__var[_instance->Server_n__var] = 0;
f_Server_sendTeamStatus(_instance, _instance->Server_n__var);

}
_instance->Server_n__var = _instance->Server_n__var + 1;

}
Server_send_gui_gameStatus(_instance, 1);
Server_send_gui_secondsLeft(_instance, _instance->Server_playTime__var);
Server_send_arena_gameStart(_instance);
_instance->Server_timeLeft__var = _instance->Server_playTime__var;
break;
default: break;
}
}

// On Exit Actions:
void Server_S_OnExit(int state, struct Server_Instance *_instance) {
switch(state) {
case SERVER_S_STATE:
Server_S_OnExit(_instance->Server_S_State, _instance);
break;
case SERVER_S_RUNNING_STATE:
Server_S_OnExit(_instance->Server_S_Running_State, _instance);
break;
case SERVER_S_INIT_STATE:
break;
case SERVER_S_RUNNING_LOUNGE_STATE:
break;
case SERVER_S_RUNNING_PLAYING_STATE:
break;
default: break;
}
}

// Event Handlers for incoming messages:
void Server_handle_clock_clock_tick(struct Server_Instance *_instance) {
uint8_t Server_S_State_event_consumed = 0;
if (_instance->Server_S_State == SERVER_S_RUNNING_STATE) {
uint8_t Server_S_Running_State_event_consumed = 0;
if (_instance->Server_S_Running_State == SERVER_S_RUNNING_PLAYING_STATE) {
if (Server_S_Running_State_event_consumed == 0 && (_instance->Server_timeLeft__var == 1)) {
Server_S_OnExit(SERVER_S_RUNNING_PLAYING_STATE, _instance);
_instance->Server_S_Running_State = SERVER_S_RUNNING_LOUNGE_STATE;
_instance->Server_timeLeft__var = 0;
Server_send_gui_secondsLeft(_instance, 0);
Server_S_OnEntry(SERVER_S_RUNNING_LOUNGE_STATE, _instance);
Server_S_Running_State_event_consumed = 1;
}
else if (Server_S_Running_State_event_consumed == 0 && (_instance->Server_timeLeft__var > 1)) {
_instance->Server_timeLeft__var = _instance->Server_timeLeft__var - 1;
Server_send_gui_secondsLeft(_instance, _instance->Server_timeLeft__var);
Server_S_Running_State_event_consumed = 1;
}
}
Server_S_State_event_consumed = 0 | Server_S_Running_State_event_consumed ;
}
}
void Server_handle_arena_register(struct Server_Instance *_instance, uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4) {
uint8_t Server_S_State_event_consumed = 0;
if (_instance->Server_S_State == SERVER_S_RUNNING_STATE) {
uint8_t Server_S_Running_State_event_consumed = 0;
Server_S_State_event_consumed = 0 | Server_S_Running_State_event_consumed ;
if (Server_S_State_event_consumed == 0 && 1) {
_instance->Server_registered__var[_instance->Server_nextId__var] = 1;
_instance->Server_scores__var[_instance->Server_nextId__var] = 0;
_instance->Server_shots__var[_instance->Server_nextId__var] = 0;
_instance->Server_hits__var[_instance->Server_nextId__var] = 0;
_instance->Server_ips1__var[_instance->Server_nextId__var] = ip1;
_instance->Server_ips2__var[_instance->Server_nextId__var] = ip2;
_instance->Server_ips3__var[_instance->Server_nextId__var] = ip3;
_instance->Server_ips4__var[_instance->Server_nextId__var] = ip4;
Server_send_arena_assignID(_instance, _instance->Server_nextId__var, ip1, ip2, ip3, ip4);
f_Server_sendTeamStatus(_instance, _instance->Server_nextId__var);
_instance->Server_nextId__var = _instance->Server_nextId__var + 1;
Server_S_State_event_consumed = 1;
}
}
}
void Server_handle_arena_shooting(struct Server_Instance *_instance, uint8_t ID, uint8_t time0, uint8_t time1) {
uint8_t Server_S_State_event_consumed = 0;
if (_instance->Server_S_State == SERVER_S_RUNNING_STATE) {
uint8_t Server_S_Running_State_event_consumed = 0;
if (_instance->Server_S_Running_State == SERVER_S_RUNNING_PLAYING_STATE) {
if (Server_S_Running_State_event_consumed == 0 && 1) {
_instance->Server_shots__var[ID] = _instance->Server_shots__var[ID]
 + 1;
f_Server_sendTeamStatus(_instance, ID);
Server_S_Running_State_event_consumed = 1;
}
}
Server_S_State_event_consumed = 0 | Server_S_Running_State_event_consumed ;
}
}
void Server_handle_arena_unregister(struct Server_Instance *_instance, uint8_t ID) {
uint8_t Server_S_State_event_consumed = 0;
if (_instance->Server_S_State == SERVER_S_RUNNING_STATE) {
uint8_t Server_S_Running_State_event_consumed = 0;
Server_S_State_event_consumed = 0 | Server_S_Running_State_event_consumed ;
if (Server_S_State_event_consumed == 0 && 1) {
_instance->Server_registered__var[ID] = 0;
_instance->Server_scores__var[ID] = 0;
_instance->Server_shots__var[ID] = 0;
_instance->Server_hits__var[ID] = 0;
_instance->Server_ips1__var[ID] = 0;
_instance->Server_ips2__var[ID] = 0;
_instance->Server_ips3__var[ID] = 0;
_instance->Server_ips4__var[ID] = 0;
f_Server_sendTeamStatus(_instance, ID);
Server_S_State_event_consumed = 1;
}
}
}
void Server_handle_arena_hitInfo(struct Server_Instance *_instance, uint8_t ID, uint8_t IDshooter) {
uint8_t Server_S_State_event_consumed = 0;
if (_instance->Server_S_State == SERVER_S_RUNNING_STATE) {
uint8_t Server_S_Running_State_event_consumed = 0;
if (_instance->Server_S_Running_State == SERVER_S_RUNNING_PLAYING_STATE) {
if (Server_S_Running_State_event_consumed == 0 && 1) {
_instance->Server_hits__var[ID] = _instance->Server_hits__var[ID]
 + 1;
f_Server_sendTeamStatus(_instance, ID);
Server_S_Running_State_event_consumed = 1;
}
}
Server_S_State_event_consumed = 0 | Server_S_Running_State_event_consumed ;
}
}
void Server_handle_gui_getGameStatus(struct Server_Instance *_instance) {
uint8_t Server_S_State_event_consumed = 0;
if (_instance->Server_S_State == SERVER_S_RUNNING_STATE) {
uint8_t Server_S_Running_State_event_consumed = 0;
if (_instance->Server_S_Running_State == SERVER_S_RUNNING_LOUNGE_STATE) {
if (Server_S_Running_State_event_consumed == 0 && 1) {
Server_send_gui_gameStatus(_instance, 0);
Server_S_Running_State_event_consumed = 1;
}
}
else if (_instance->Server_S_Running_State == SERVER_S_RUNNING_PLAYING_STATE) {
if (Server_S_Running_State_event_consumed == 0 && 1) {
Server_send_gui_gameStatus(_instance, 0);
Server_S_Running_State_event_consumed = 1;
}
}
Server_S_State_event_consumed = 0 | Server_S_Running_State_event_consumed ;
}
}
void Server_handle_gui_listStatuses(struct Server_Instance *_instance) {
uint8_t Server_S_State_event_consumed = 0;
if (_instance->Server_S_State == SERVER_S_RUNNING_STATE) {
uint8_t Server_S_Running_State_event_consumed = 0;
Server_S_State_event_consumed = 0 | Server_S_Running_State_event_consumed ;
if (Server_S_State_event_consumed == 0 && 1) {
_instance->Server_n__var = 1;
while(_instance->Server_n__var < _instance->Server_nextId__var) {
if(_instance->Server_registered__var[_instance->Server_n__var]
 == 1) {
f_Server_sendTeamStatus(_instance, _instance->Server_n__var);

}
_instance->Server_n__var = _instance->Server_n__var + 1;

}
Server_S_State_event_consumed = 1;
}
}
}
int Server_handle_empty_event(struct Server_Instance *_instance) {
if (_instance->Server_S_State == SERVER_S_INIT_STATE) {
if (1) {
Server_S_OnExit(SERVER_S_INIT_STATE, _instance);
_instance->Server_S_State = SERVER_S_RUNNING_STATE;
Server_S_OnEntry(SERVER_S_RUNNING_STATE, _instance);
return 1;
}
}
return 0;
}

// Observers for outgoing messages:
void (*external_Server_send_arena_assignID_listener)(struct Server_Instance *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t)= 0x0;
void (*Server_send_arena_assignID_listener)(struct Server_Instance *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t)= 0x0;
void register_external_Server_send_arena_assignID_listener(void (*_listener)(struct Server_Instance *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t)){
external_Server_send_arena_assignID_listener = _listener;
}
void register_Server_send_arena_assignID_listener(void (*_listener)(struct Server_Instance *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t)){
Server_send_arena_assignID_listener = _listener;
}
void Server_send_arena_assignID(struct Server_Instance *_instance, uint8_t ID, uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4){
if (Server_send_arena_assignID_listener != 0x0) Server_send_arena_assignID_listener(_instance, ID, ip1, ip2, ip3, ip4);
if (external_Server_send_arena_assignID_listener != 0x0) external_Server_send_arena_assignID_listener(_instance, ID, ip1, ip2, ip3, ip4);
;
}
void (*external_Server_send_arena_gameStart_listener)(struct Server_Instance *)= 0x0;
void (*Server_send_arena_gameStart_listener)(struct Server_Instance *)= 0x0;
void register_external_Server_send_arena_gameStart_listener(void (*_listener)(struct Server_Instance *)){
external_Server_send_arena_gameStart_listener = _listener;
}
void register_Server_send_arena_gameStart_listener(void (*_listener)(struct Server_Instance *)){
Server_send_arena_gameStart_listener = _listener;
}
void Server_send_arena_gameStart(struct Server_Instance *_instance){
if (Server_send_arena_gameStart_listener != 0x0) Server_send_arena_gameStart_listener(_instance);
if (external_Server_send_arena_gameStart_listener != 0x0) external_Server_send_arena_gameStart_listener(_instance);
;
}
void (*external_Server_send_arena_gameStop_listener)(struct Server_Instance *)= 0x0;
void (*Server_send_arena_gameStop_listener)(struct Server_Instance *)= 0x0;
void register_external_Server_send_arena_gameStop_listener(void (*_listener)(struct Server_Instance *)){
external_Server_send_arena_gameStop_listener = _listener;
}
void register_Server_send_arena_gameStop_listener(void (*_listener)(struct Server_Instance *)){
Server_send_arena_gameStop_listener = _listener;
}
void Server_send_arena_gameStop(struct Server_Instance *_instance){
if (Server_send_arena_gameStop_listener != 0x0) Server_send_arena_gameStop_listener(_instance);
if (external_Server_send_arena_gameStop_listener != 0x0) external_Server_send_arena_gameStop_listener(_instance);
;
}
void (*external_Server_send_gui_gameStatus_listener)(struct Server_Instance *, uint8_t)= 0x0;
void (*Server_send_gui_gameStatus_listener)(struct Server_Instance *, uint8_t)= 0x0;
void register_external_Server_send_gui_gameStatus_listener(void (*_listener)(struct Server_Instance *, uint8_t)){
external_Server_send_gui_gameStatus_listener = _listener;
}
void register_Server_send_gui_gameStatus_listener(void (*_listener)(struct Server_Instance *, uint8_t)){
Server_send_gui_gameStatus_listener = _listener;
}
void Server_send_gui_gameStatus(struct Server_Instance *_instance, uint8_t playing){
if (Server_send_gui_gameStatus_listener != 0x0) Server_send_gui_gameStatus_listener(_instance, playing);
if (external_Server_send_gui_gameStatus_listener != 0x0) external_Server_send_gui_gameStatus_listener(_instance, playing);
;
}
void (*external_Server_send_gui_secondsLeft_listener)(struct Server_Instance *, uint16_t)= 0x0;
void (*Server_send_gui_secondsLeft_listener)(struct Server_Instance *, uint16_t)= 0x0;
void register_external_Server_send_gui_secondsLeft_listener(void (*_listener)(struct Server_Instance *, uint16_t)){
external_Server_send_gui_secondsLeft_listener = _listener;
}
void register_Server_send_gui_secondsLeft_listener(void (*_listener)(struct Server_Instance *, uint16_t)){
Server_send_gui_secondsLeft_listener = _listener;
}
void Server_send_gui_secondsLeft(struct Server_Instance *_instance, uint16_t secs){
if (Server_send_gui_secondsLeft_listener != 0x0) Server_send_gui_secondsLeft_listener(_instance, secs);
if (external_Server_send_gui_secondsLeft_listener != 0x0) external_Server_send_gui_secondsLeft_listener(_instance, secs);
;
}
void (*external_Server_send_gui_teamStatus_listener)(struct Server_Instance *, uint8_t, uint8_t, int16_t, int16_t, int16_t, uint8_t, uint8_t, uint8_t, uint8_t)= 0x0;
void (*Server_send_gui_teamStatus_listener)(struct Server_Instance *, uint8_t, uint8_t, int16_t, int16_t, int16_t, uint8_t, uint8_t, uint8_t, uint8_t)= 0x0;
void register_external_Server_send_gui_teamStatus_listener(void (*_listener)(struct Server_Instance *, uint8_t, uint8_t, int16_t, int16_t, int16_t, uint8_t, uint8_t, uint8_t, uint8_t)){
external_Server_send_gui_teamStatus_listener = _listener;
}
void register_Server_send_gui_teamStatus_listener(void (*_listener)(struct Server_Instance *, uint8_t, uint8_t, int16_t, int16_t, int16_t, uint8_t, uint8_t, uint8_t, uint8_t)){
Server_send_gui_teamStatus_listener = _listener;
}
void Server_send_gui_teamStatus(struct Server_Instance *_instance, uint8_t ID, uint8_t registered, int16_t score, int16_t shots, int16_t hits, uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4){
if (Server_send_gui_teamStatus_listener != 0x0) Server_send_gui_teamStatus_listener(_instance, ID, registered, score, shots, hits, ip1, ip2, ip3, ip4);
if (external_Server_send_gui_teamStatus_listener != 0x0) external_Server_send_gui_teamStatus_listener(_instance, ID, registered, score, shots, hits, ip1, ip2, ip3, ip4);
;
}



