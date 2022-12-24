#ifndef _UNKNOWN_05DCD0_H_
#define _UNKNOWN_05DCD0_H_

#include "types.h"
#include "structs.h"

extern s16 D_800DCE00[16];
extern s16 D_800DCE20[16];


void func_8005D820(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, s32 *currentStickX, s32 *startTimer); /* extern */
void func_8005D0D0(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, u32 *buttonsPressed, s32 *startTimer); /* extern */
void func_8005E204(Object *obj, Object_Racer *racer, f32 arg2, s32 objectID, s32 arg4);

#endif
