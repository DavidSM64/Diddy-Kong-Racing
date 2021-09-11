#ifndef _FADE_TRANSITION_H_
#define _FADE_TRANSITION_H_

#include "types.h"
#include "camera.h"

#define FADE_FULLSCREEN          0
#define FADE_BARNDOOR_HORIZONTAL 1
#define FADE_BARNDOOR_VERTICAL   2
#define FADE_CIRCLE              3
#define FADE_WAVES               4
#define FADE_BARNDOOR_DIAGONAL   5
#define FADE_DISABLED            6

#define FADE_COLOR(red, green, blue) red, green, blue
#define FADE_COLOR_BLACK FADE_COLOR(0, 0, 0)
#define FADE_COLOR_WHITE FADE_COLOR(255, 255, 255)

#define FADE_TRANSITION(type, color, duration, unk6) { type, color, duration, unk6 }

/* Size: 8 bytes */
typedef struct FadeTransition {
    u8 type; // top 2 bits also act as flags
    u8 red;
    u8 green;
    u8 blue;
    u16 duration;
    u16 unk6;
} FadeTransition;

extern u32 osTvType;

void func_800C0170(void);
void func_800C0180(void);
void func_800C0724(void);
s32 func_800C0494(s32 arg0);
void render_fade_transition(s32 dlist, s32 arg1, s32 arg2);
void render_fade_fullscreen(Gfx **dlist, s32 arg1, s32 arg2);
void render_fade_barndoor_horizontal(Gfx **dlist, s32 arg1, s32 arg2);
void render_fade_barndoor_vertical(Gfx **dlist, s32 arg1, s32 arg2);
void render_fade_barndoor_diagonal(Gfx **dlist, s32 arg1, s32 arg2);
void render_fade_disabled(Gfx **dlist, s32 arg1, s32 arg2);
void func_800C0780(FadeTransition *transition);

void render_fade_circle(Gfx **dlist, s32 arg1, s32 arg2); //Non Matching
void render_fade_waves(Gfx **dlist, s32 arg1, s32 arg2); //Non Matching
void func_800C0834(s32); //Non Matching
void func_800C1130(s32); //Non Matching
void func_800C1EE8(s32); //Non Matching
void func_800C27A0(s32 arg0); //Non Matching
void func_800C0B00(FadeTransition *transition, s32, s32, s16*, s8*, s8*, s8*, s8*, s8*); //Non Matching
void func_800C15D4(FadeTransition *transition); //Non Matching
void func_800C2640(FadeTransition *transition); //Non Matching
s32 func_800C018C(void); //Non Matching
s32 func_800C01D8(FadeTransition *transition); //Non Matching

#endif