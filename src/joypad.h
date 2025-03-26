#ifndef _JOYPAD_H_
#define _JOYPAD_H_

#include "types.h"
#include "macros.h"
#include "structs.h"
#include <ultra64.h>

#define CONTROLLER_MISSING -1
#define CONTROLLER_EXISTS   0

#define JOYSTICK_DEADZONE 8
#define JOYSTICK_MAX_RANGE 70

OSMesgQueue *si_mesg(void);
s32 input_init(void);
s32 input_update(s32 saveDataFlags, s32 updateRate);
void input_assign_players(void);
void charselect_assign_players(s8 *activePlayers);
u8 input_player_id(s32 player);
void input_swap_id(void);
u16 input_held(s32 player);
u32 input_pressed(s32 player);
u16 input_released(s32 player);
s32 input_clamp_stick_x(s32 player);
s32 input_clamp_stick_y(s32 player);
s8 input_clamp_stick_mag(s8 stickMag);
void drm_disable_input(void);

#endif
