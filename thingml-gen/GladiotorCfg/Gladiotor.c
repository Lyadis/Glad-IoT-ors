/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *        Implementation for Thing Gladiotor
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#include "Gladiotor.h"

/*****************************************************************************
 * Implementation for type : Gladiotor
 *****************************************************************************/

// Declaration of prototypes:
void Gladiotor_C_OnExit(int state, struct Gladiotor_Instance *_instance);
void Gladiotor_send_cmd_beenHit(struct Gladiotor_Instance *_instance, uint8_t IDshooter);
void Gladiotor_send_control_shootCmd(struct Gladiotor_Instance *_instance, uint8_t ID);
void Gladiotor_send_control_timer_start(struct Gladiotor_Instance *_instance, uint8_t id, uint32_t time);
void Gladiotor_send_control_timer_cancel(struct Gladiotor_Instance *_instance, uint8_t id);
void Gladiotor_send_arena_register(struct Gladiotor_Instance *_instance);
void Gladiotor_send_arena_unregister(struct Gladiotor_Instance *_instance, uint8_t ID);
void Gladiotor_send_arena_shooting(struct Gladiotor_Instance *_instance, uint8_t ID, uint8_t time0, uint8_t time1);
void Gladiotor_send_arena_hitInfo(struct Gladiotor_Instance *_instance, uint8_t ID, uint8_t IDshutter);
// Declaration of functions:

// On Entry Actions:
void Gladiotor_C_OnEntry(int state, struct Gladiotor_Instance *_instance) {
switch(state) {
case GLADIOTOR_C_STATE:
_instance->Gladiotor_C_State = GLADIOTOR_C_INIT_STATE;
Gladiotor_C_OnEntry(_instance->Gladiotor_C_State, _instance);
break;
case GLADIOTOR_C_GAME_STATE:
_instance->Gladiotor_C_Game_State = GLADIOTOR_C_GAME_IDENTIFICATION_STATE;
Gladiotor_C_OnEntry(_instance->Gladiotor_C_Game_State, _instance);
break;
case GLADIOTOR_C_INIT_STATE:
fprintf(stdout, "Init\n");
break;
case GLADIOTOR_C_GAME_IDENTIFICATION_STATE:
Gladiotor_send_control_timer_start(_instance, 1, 3000);
Gladiotor_send_arena_register(_instance);
break;
case GLADIOTOR_C_GAME_WAIT_STATE:
break;
case GLADIOTOR_C_GAME_ACTIVE_STATE:
break;
case GLADIOTOR_C_GAME_INACTIVE_STATE:
break;
default: break;
}
}

// On Exit Actions:
void Gladiotor_C_OnExit(int state, struct Gladiotor_Instance *_instance) {
switch(state) {
case GLADIOTOR_C_STATE:
Gladiotor_C_OnExit(_instance->Gladiotor_C_State, _instance);
break;
case GLADIOTOR_C_GAME_STATE:
Gladiotor_C_OnExit(_instance->Gladiotor_C_Game_State, _instance);
break;
case GLADIOTOR_C_INIT_STATE:
break;
case GLADIOTOR_C_GAME_IDENTIFICATION_STATE:
break;
case GLADIOTOR_C_GAME_WAIT_STATE:
break;
case GLADIOTOR_C_GAME_ACTIVE_STATE:
break;
case GLADIOTOR_C_GAME_INACTIVE_STATE:
break;
default: break;
}
}

// Event Handlers for incoming messages:
void Gladiotor_handle_arena_assignID(struct Gladiotor_Instance *_instance, uint8_t ID) {
uint8_t Gladiotor_C_State_event_consumed = 0;
if (_instance->Gladiotor_C_State == GLADIOTOR_C_GAME_STATE) {
uint8_t Gladiotor_C_Game_State_event_consumed = 0;
if (_instance->Gladiotor_C_Game_State == GLADIOTOR_C_GAME_IDENTIFICATION_STATE) {
if (Gladiotor_C_Game_State_event_consumed == 0 && 1) {
Gladiotor_C_OnExit(GLADIOTOR_C_GAME_IDENTIFICATION_STATE, _instance);
_instance->Gladiotor_C_Game_State = GLADIOTOR_C_GAME_WAIT_STATE;
fprintf(stdout, "received ID\n");
_instance->Gladiotor_ID__var = ID;
Gladiotor_send_control_timer_cancel(_instance, 1);
Gladiotor_C_OnEntry(GLADIOTOR_C_GAME_WAIT_STATE, _instance);
Gladiotor_C_Game_State_event_consumed = 1;
}
}
Gladiotor_C_State_event_consumed = 0 | Gladiotor_C_Game_State_event_consumed ;
}
}
void Gladiotor_handle_arena_gameStart(struct Gladiotor_Instance *_instance) {
uint8_t Gladiotor_C_State_event_consumed = 0;
if (_instance->Gladiotor_C_State == GLADIOTOR_C_GAME_STATE) {
uint8_t Gladiotor_C_Game_State_event_consumed = 0;
if (_instance->Gladiotor_C_Game_State == GLADIOTOR_C_GAME_WAIT_STATE) {
if (Gladiotor_C_Game_State_event_consumed == 0 && 1) {
Gladiotor_C_OnExit(GLADIOTOR_C_GAME_WAIT_STATE, _instance);
_instance->Gladiotor_C_Game_State = GLADIOTOR_C_GAME_ACTIVE_STATE;
Gladiotor_C_OnEntry(GLADIOTOR_C_GAME_ACTIVE_STATE, _instance);
Gladiotor_C_Game_State_event_consumed = 1;
}
}
Gladiotor_C_State_event_consumed = 0 | Gladiotor_C_Game_State_event_consumed ;
}
}
void Gladiotor_handle_arena_gameStop(struct Gladiotor_Instance *_instance) {
uint8_t Gladiotor_C_State_event_consumed = 0;
if (_instance->Gladiotor_C_State == GLADIOTOR_C_GAME_STATE) {
uint8_t Gladiotor_C_Game_State_event_consumed = 0;
Gladiotor_C_State_event_consumed = 0 | Gladiotor_C_Game_State_event_consumed ;
if (Gladiotor_C_State_event_consumed == 0 && 1) {
Gladiotor_C_OnExit(GLADIOTOR_C_GAME_STATE, _instance);
_instance->Gladiotor_C_State = GLADIOTOR_C_GAME_STATE;
Gladiotor_C_OnEntry(GLADIOTOR_C_GAME_STATE, _instance);
Gladiotor_C_State_event_consumed = 1;
}
}
}
void Gladiotor_handle_cmd_shootCmd(struct Gladiotor_Instance *_instance, uint8_t ID) {
uint8_t Gladiotor_C_State_event_consumed = 0;
if (_instance->Gladiotor_C_State == GLADIOTOR_C_GAME_STATE) {
uint8_t Gladiotor_C_Game_State_event_consumed = 0;
if (_instance->Gladiotor_C_Game_State == GLADIOTOR_C_GAME_ACTIVE_STATE) {
if (Gladiotor_C_Game_State_event_consumed == 0 && 1) {
Gladiotor_send_control_shootCmd(_instance, _instance->Gladiotor_ID__var);
Gladiotor_C_Game_State_event_consumed = 1;
}
}
Gladiotor_C_State_event_consumed = 0 | Gladiotor_C_Game_State_event_consumed ;
}
}
void Gladiotor_handle_control_timeout(struct Gladiotor_Instance *_instance, uint8_t id) {
uint8_t Gladiotor_C_State_event_consumed = 0;
if (_instance->Gladiotor_C_State == GLADIOTOR_C_GAME_STATE) {
uint8_t Gladiotor_C_Game_State_event_consumed = 0;
if (_instance->Gladiotor_C_Game_State == GLADIOTOR_C_GAME_IDENTIFICATION_STATE) {
if (Gladiotor_C_Game_State_event_consumed == 0 && 1) {
Gladiotor_C_OnExit(GLADIOTOR_C_GAME_IDENTIFICATION_STATE, _instance);
_instance->Gladiotor_C_Game_State = GLADIOTOR_C_GAME_IDENTIFICATION_STATE;
Gladiotor_C_OnEntry(GLADIOTOR_C_GAME_IDENTIFICATION_STATE, _instance);
Gladiotor_C_Game_State_event_consumed = 1;
}
}
else if (_instance->Gladiotor_C_Game_State == GLADIOTOR_C_GAME_INACTIVE_STATE) {
if (Gladiotor_C_Game_State_event_consumed == 0 && 1) {
Gladiotor_C_OnExit(GLADIOTOR_C_GAME_INACTIVE_STATE, _instance);
_instance->Gladiotor_C_Game_State = GLADIOTOR_C_GAME_ACTIVE_STATE;
Gladiotor_C_OnEntry(GLADIOTOR_C_GAME_ACTIVE_STATE, _instance);
Gladiotor_C_Game_State_event_consumed = 1;
}
}
Gladiotor_C_State_event_consumed = 0 | Gladiotor_C_Game_State_event_consumed ;
}
}
void Gladiotor_handle_control_beenHit(struct Gladiotor_Instance *_instance, uint8_t IDshooter) {
uint8_t Gladiotor_C_State_event_consumed = 0;
if (_instance->Gladiotor_C_State == GLADIOTOR_C_GAME_STATE) {
uint8_t Gladiotor_C_Game_State_event_consumed = 0;
if (_instance->Gladiotor_C_Game_State == GLADIOTOR_C_GAME_ACTIVE_STATE) {
if (Gladiotor_C_Game_State_event_consumed == 0 && 1) {
Gladiotor_C_OnExit(GLADIOTOR_C_GAME_ACTIVE_STATE, _instance);
_instance->Gladiotor_C_Game_State = GLADIOTOR_C_GAME_INACTIVE_STATE;
fprintf(stdout, "beenHit\n");
Gladiotor_send_arena_hitInfo(_instance, _instance->Gladiotor_ID__var, IDshooter);
Gladiotor_send_cmd_beenHit(_instance, IDshooter);
Gladiotor_send_control_timer_start(_instance, 1, _instance->Gladiotor_InactiveTime__var);
Gladiotor_C_OnEntry(GLADIOTOR_C_GAME_INACTIVE_STATE, _instance);
Gladiotor_C_Game_State_event_consumed = 1;
}
}
Gladiotor_C_State_event_consumed = 0 | Gladiotor_C_Game_State_event_consumed ;
}
}
void Gladiotor_handle_control_ready(struct Gladiotor_Instance *_instance) {
uint8_t Gladiotor_C_State_event_consumed = 0;
if (_instance->Gladiotor_C_State == GLADIOTOR_C_INIT_STATE) {
if (Gladiotor_C_State_event_consumed == 0 && 1) {
Gladiotor_C_OnExit(GLADIOTOR_C_INIT_STATE, _instance);
_instance->Gladiotor_C_State = GLADIOTOR_C_GAME_STATE;
Gladiotor_C_OnEntry(GLADIOTOR_C_GAME_STATE, _instance);
Gladiotor_C_State_event_consumed = 1;
}
}
else if (_instance->Gladiotor_C_State == GLADIOTOR_C_GAME_STATE) {
uint8_t Gladiotor_C_Game_State_event_consumed = 0;
Gladiotor_C_State_event_consumed = 0 | Gladiotor_C_Game_State_event_consumed ;
if (Gladiotor_C_State_event_consumed == 0 && 1) {
Gladiotor_C_OnExit(GLADIOTOR_C_GAME_STATE, _instance);
_instance->Gladiotor_C_State = GLADIOTOR_C_GAME_STATE;
if( !((_instance->Gladiotor_ID__var == 0))) {
Gladiotor_send_arena_unregister(_instance, _instance->Gladiotor_ID__var);

}
Gladiotor_C_OnEntry(GLADIOTOR_C_GAME_STATE, _instance);
Gladiotor_C_State_event_consumed = 1;
}
}
}

// Observers for outgoing messages:
void (*external_Gladiotor_send_cmd_beenHit_listener)(struct Gladiotor_Instance *, uint8_t)= 0x0;
void (*Gladiotor_send_cmd_beenHit_listener)(struct Gladiotor_Instance *, uint8_t)= 0x0;
void register_external_Gladiotor_send_cmd_beenHit_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t)){
external_Gladiotor_send_cmd_beenHit_listener = _listener;
}
void register_Gladiotor_send_cmd_beenHit_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t)){
Gladiotor_send_cmd_beenHit_listener = _listener;
}
void Gladiotor_send_cmd_beenHit(struct Gladiotor_Instance *_instance, uint8_t IDshooter){
if (Gladiotor_send_cmd_beenHit_listener != 0x0) Gladiotor_send_cmd_beenHit_listener(_instance, IDshooter);
if (external_Gladiotor_send_cmd_beenHit_listener != 0x0) external_Gladiotor_send_cmd_beenHit_listener(_instance, IDshooter);
;
}
void (*external_Gladiotor_send_control_shootCmd_listener)(struct Gladiotor_Instance *, uint8_t)= 0x0;
void (*Gladiotor_send_control_shootCmd_listener)(struct Gladiotor_Instance *, uint8_t)= 0x0;
void register_external_Gladiotor_send_control_shootCmd_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t)){
external_Gladiotor_send_control_shootCmd_listener = _listener;
}
void register_Gladiotor_send_control_shootCmd_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t)){
Gladiotor_send_control_shootCmd_listener = _listener;
}
void Gladiotor_send_control_shootCmd(struct Gladiotor_Instance *_instance, uint8_t ID){
if (Gladiotor_send_control_shootCmd_listener != 0x0) Gladiotor_send_control_shootCmd_listener(_instance, ID);
if (external_Gladiotor_send_control_shootCmd_listener != 0x0) external_Gladiotor_send_control_shootCmd_listener(_instance, ID);
;
}
void (*external_Gladiotor_send_control_timer_start_listener)(struct Gladiotor_Instance *, uint8_t, uint32_t)= 0x0;
void (*Gladiotor_send_control_timer_start_listener)(struct Gladiotor_Instance *, uint8_t, uint32_t)= 0x0;
void register_external_Gladiotor_send_control_timer_start_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t, uint32_t)){
external_Gladiotor_send_control_timer_start_listener = _listener;
}
void register_Gladiotor_send_control_timer_start_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t, uint32_t)){
Gladiotor_send_control_timer_start_listener = _listener;
}
void Gladiotor_send_control_timer_start(struct Gladiotor_Instance *_instance, uint8_t id, uint32_t time){
if (Gladiotor_send_control_timer_start_listener != 0x0) Gladiotor_send_control_timer_start_listener(_instance, id, time);
if (external_Gladiotor_send_control_timer_start_listener != 0x0) external_Gladiotor_send_control_timer_start_listener(_instance, id, time);
;
}
void (*external_Gladiotor_send_control_timer_cancel_listener)(struct Gladiotor_Instance *, uint8_t)= 0x0;
void (*Gladiotor_send_control_timer_cancel_listener)(struct Gladiotor_Instance *, uint8_t)= 0x0;
void register_external_Gladiotor_send_control_timer_cancel_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t)){
external_Gladiotor_send_control_timer_cancel_listener = _listener;
}
void register_Gladiotor_send_control_timer_cancel_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t)){
Gladiotor_send_control_timer_cancel_listener = _listener;
}
void Gladiotor_send_control_timer_cancel(struct Gladiotor_Instance *_instance, uint8_t id){
if (Gladiotor_send_control_timer_cancel_listener != 0x0) Gladiotor_send_control_timer_cancel_listener(_instance, id);
if (external_Gladiotor_send_control_timer_cancel_listener != 0x0) external_Gladiotor_send_control_timer_cancel_listener(_instance, id);
;
}
void (*external_Gladiotor_send_arena_register_listener)(struct Gladiotor_Instance *)= 0x0;
void (*Gladiotor_send_arena_register_listener)(struct Gladiotor_Instance *)= 0x0;
void register_external_Gladiotor_send_arena_register_listener(void (*_listener)(struct Gladiotor_Instance *)){
external_Gladiotor_send_arena_register_listener = _listener;
}
void register_Gladiotor_send_arena_register_listener(void (*_listener)(struct Gladiotor_Instance *)){
Gladiotor_send_arena_register_listener = _listener;
}
void Gladiotor_send_arena_register(struct Gladiotor_Instance *_instance){
if (Gladiotor_send_arena_register_listener != 0x0) Gladiotor_send_arena_register_listener(_instance);
if (external_Gladiotor_send_arena_register_listener != 0x0) external_Gladiotor_send_arena_register_listener(_instance);
;
}
void (*external_Gladiotor_send_arena_unregister_listener)(struct Gladiotor_Instance *, uint8_t)= 0x0;
void (*Gladiotor_send_arena_unregister_listener)(struct Gladiotor_Instance *, uint8_t)= 0x0;
void register_external_Gladiotor_send_arena_unregister_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t)){
external_Gladiotor_send_arena_unregister_listener = _listener;
}
void register_Gladiotor_send_arena_unregister_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t)){
Gladiotor_send_arena_unregister_listener = _listener;
}
void Gladiotor_send_arena_unregister(struct Gladiotor_Instance *_instance, uint8_t ID){
if (Gladiotor_send_arena_unregister_listener != 0x0) Gladiotor_send_arena_unregister_listener(_instance, ID);
if (external_Gladiotor_send_arena_unregister_listener != 0x0) external_Gladiotor_send_arena_unregister_listener(_instance, ID);
;
}
void (*external_Gladiotor_send_arena_shooting_listener)(struct Gladiotor_Instance *, uint8_t, uint8_t, uint8_t)= 0x0;
void (*Gladiotor_send_arena_shooting_listener)(struct Gladiotor_Instance *, uint8_t, uint8_t, uint8_t)= 0x0;
void register_external_Gladiotor_send_arena_shooting_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t, uint8_t, uint8_t)){
external_Gladiotor_send_arena_shooting_listener = _listener;
}
void register_Gladiotor_send_arena_shooting_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t, uint8_t, uint8_t)){
Gladiotor_send_arena_shooting_listener = _listener;
}
void Gladiotor_send_arena_shooting(struct Gladiotor_Instance *_instance, uint8_t ID, uint8_t time0, uint8_t time1){
if (Gladiotor_send_arena_shooting_listener != 0x0) Gladiotor_send_arena_shooting_listener(_instance, ID, time0, time1);
if (external_Gladiotor_send_arena_shooting_listener != 0x0) external_Gladiotor_send_arena_shooting_listener(_instance, ID, time0, time1);
;
}
void (*external_Gladiotor_send_arena_hitInfo_listener)(struct Gladiotor_Instance *, uint8_t, uint8_t)= 0x0;
void (*Gladiotor_send_arena_hitInfo_listener)(struct Gladiotor_Instance *, uint8_t, uint8_t)= 0x0;
void register_external_Gladiotor_send_arena_hitInfo_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t, uint8_t)){
external_Gladiotor_send_arena_hitInfo_listener = _listener;
}
void register_Gladiotor_send_arena_hitInfo_listener(void (*_listener)(struct Gladiotor_Instance *, uint8_t, uint8_t)){
Gladiotor_send_arena_hitInfo_listener = _listener;
}
void Gladiotor_send_arena_hitInfo(struct Gladiotor_Instance *_instance, uint8_t ID, uint8_t IDshutter){
if (Gladiotor_send_arena_hitInfo_listener != 0x0) Gladiotor_send_arena_hitInfo_listener(_instance, ID, IDshutter);
if (external_Gladiotor_send_arena_hitInfo_listener != 0x0) external_Gladiotor_send_arena_hitInfo_listener(_instance, ID, IDshutter);
;
}



