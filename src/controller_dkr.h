#ifndef _CONTROLLER_DKR_H_
#define _CONTROLLER_DKR_H_

#include "types.h"
#include "macros.h"
#include "structs.h"
#include <ultra64.h>

#define CONTROLLER_MISSING -1
#define CONTROLLER_EXISTS   0

#define JOYSTICK_DEADZONE 8
#define JOYSTICK_MAX_RANGE 70

OSMesgQueue *get_si_mesg_queue(void);
s32 init_controllers(void);
s32 handle_save_data_and_read_controller(s32 saveDataFlags, s32 updateRate);
void initialise_player_ids(void);
void charselect_assign_players(s8 *activePlayers);
u8 get_player_id(s32 player);
void swap_player_1_and_2_ids(void);
u16 get_buttons_held_from_player(s32 player);
u32 get_buttons_pressed_from_player(s32 player);
u16 get_buttons_released_from_player(s32 player);
s32 clamp_joystick_x_axis(s32 player);
s32 clamp_joystick_y_axis(s32 player);
s8 clamp_joystick(s8 stickMag);
void disable_button_mask(void);

#endif
