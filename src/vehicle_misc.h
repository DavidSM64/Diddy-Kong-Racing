#ifndef _VEHICLE_MISC_H_
#define _VEHICLE_MISC_H_

#include "types.h"
#include "structs.h"

extern u16 D_800DCDE0[16];
extern u16 D_800DCE20[16];
extern u16 D_800DCE40[16];
extern s16 D_800DCE60[14];
extern s16 D_800DCE80[14];

typedef struct unk8005C2F0 {
    u8 pad0[0xC];
    f32 unkC;
    u8 pad10[0x108];
    s32 unk118;
} unk8005C2F0;

void update_tricky(s32 updateRate, f32 updateRateF, Object* obj, Object_Racer* racer, u32* input, u32* buttonsPressed, s32* startTimer);
void update_bluey(s32 updateRate, f32 updateRateF, Object* obj, Object_Racer* racer, u32* input, u32* buttonsPressed, s32* startTimer);
void update_bubbler(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, u32 *buttonsPressed, s32 *startTimer);
void update_smokey(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, s32 *stickMag, s32 *startTimer);
void update_wizpig(s32 updateRate, f32 updateRateF, Object* obj, Object_Racer* racer, u32* input, u32* buttonsPressed, s32* startTimer);
void update_rocket(s32 updateRate, f32 updateRateF, Object* obj, Object_Racer* racer, u32* input, u32* buttonsPressed, s32* startTimer);
void func_8005E204(Object *obj, Object_Racer *racer, f32 arg2, s32 objectID, s32 arg4);
void func_8005C2F0(Object *object, unk8005C2F0 *arg1);
void set_boss_voice_clip_offset(u16 *soundID);
void func_8005CA84(f32 x, f32 y, f32 z, s32 arg3);
void func_8005CB04(s32 arg0);
void fade_when_near_camera(Object *object, Object_Racer *racer, s32 distance);

void func_8005CB68(Object_Racer *racer, s8 *arg1); // Non Matching

#endif
