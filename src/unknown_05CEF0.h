#ifndef _UNKNOWN_05CEF0_H_
#define _UNKNOWN_05CEF0_H_

#include "types.h"
#include "structs.h"

/* Unknown size */
typedef struct unk8005C2F0 {
    u8 pad0[0xC];
    f32 unkC;
    u8 pad10[0x108];
    s32 unk118;
} unk8005C2F0;

extern u16 D_800DCDE0[16];
extern f32 D_8011D5C0;
extern s8 D_8011D5C4;
extern s8 D_8011D5CC;

s32 get_random_number_from_range(s32, s32); //?

void func_8005C2F0(Object *object, unk8005C2F0 *arg1);
void func_8005CA78(u16 *arg0);
void func_8005CA84(f32 x, f32 y, f32 z, s32 arg3);
void func_8005CB04(s32 arg0);
void func_8005D048(Object *object, Object_Racer *arg1, s32 arg2);
void func_8005CB68(Object_Racer *racer, s8 *arg1); // Non Matching
void func_8005C364(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, u32 *buttonsPressed, s32 *startTimer); /* extern */

#endif
