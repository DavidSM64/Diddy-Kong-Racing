#ifndef _WAVES_H_
#define _WAVES_H_

#include "types.h"
#include "structs.h"

typedef struct{
    LevelModelSegment *unk00;
    u8 pad04[0x8];
    u32 unk0C;
    u8 pad10[0xC];
} LevelModel_Alternate;

typedef struct unk800E3190 {
    u8 pad0[0x1A];
    u16 unk1A;
    u32 unk1C;
    u8 pad20[0x20];
} unk800E3190;

void func_800B7D20(void);
void func_800B8B8C(void);
s32 func_800B9228(LevelModelSegment *arg0);
void func_800BBDDC(s32 arg0);
void func_800BFE98(s32 arg0);

Object_64 *func_800BE654(s16, f32, f32); // Non Matching
f32 func_800BEEB4(Object_64 *); // Non Matching
void func_800BBE08(void); // Non Matching
void func_800BBF78(s32 arg0); // Non Matching
f32 func_800BB2F4(s32, f32, f32, f32*);
void func_800B8C04(s32, s32, s32, s32, s32);
void func_800BF524(Object *);
void *func_800BF634(Object *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, s32 arg8);

#endif
