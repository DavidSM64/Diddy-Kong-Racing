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

/* Unknown size */
typedef struct unk8005D048 {
    u8 pad0[0x1F7];
    u8 unk1F7;
} unk8005D048;

extern s16 D_800DCDE0[16];

s32 get_random_number_from_range(s32, s32); //?

void func_8005C2F0(Object *object, unk8005C2F0 *arg1);
void func_8005CA78(s32 arg0);
void func_8005CA84(f32 x, f32 y, f32 z, s32 arg3);
void func_8005CB04(s32 arg0);
void func_8005D048(Object *object, unk8005D048 *arg1, s32 arg2);

#endif
