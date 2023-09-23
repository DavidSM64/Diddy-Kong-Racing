#ifndef _WAVES_H_
#define _WAVES_H_

#include "types.h"
#include "structs.h"

typedef struct{
    LevelModelSegment *unk00;
    u8 pad04[0x6];
    u8 unkA;
    u8 unkB;
    u32 unk0C;
    u8 pad10[0xC];
} LevelModel_Alternate;

typedef struct unk800E3190 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 pad18[0x2];
    u16 unk1A;
    u32 unk1C;
    f32 unk20;
    f32 unk24;
    u8 pad28[0x8];
    u8 unk31;
    u8 unk32;
    u8 pad33[0xE];
} unk800E3190;

typedef struct unk800E3184 {
    u8 unk0[8];
} unk800E3184;

typedef struct unk800B8134 {
    u8 pad0[0x56];
    u8 unk56;
    u8 unk57;
    u8 unk58;
    u8 unk59;
    s16 unk5A;
    u8 unk5C;
    u8 unk5D;
    s16 unk5E;
    s16 unk60;
    s16 unk62;
    s16 unk64;
    s16 unk66;
    s16 unk68;
    u8 unk6A;
    u8 unk6B;
    s8 unk6C;
    s8 unk6D;
    s16 unk6E;
    u8 unk70;
    u8 unk71;
} unk800B8134;

typedef struct unk80129FC8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    f32 unkC;
    s32 unk10;
    s32 unk14;
    f32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    s32 unk4C;
} unk80129FC8;

typedef struct unk800BBE08_arg1 {
    u8 pad[0x70];
    s32 unk70[1]; // Unknown length.
} unk800BBE08_arg1;

typedef struct unk800BFC54_arg0 {
    f32 unk0;
    f32 unk4;
    u8 pad8[0x4];
    f32 unkC;
    f32 unk10;
    u8 pad14[0x8];
    u32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
} unk800BFC54_arg0;

void func_800B7D20(void);
void func_800B8B8C(void);
s32 func_800B9228(LevelModelSegment *arg0);
void func_800BBDDC(LevelModel *level, LevelHeader *header);
void func_800BFE98(s32 arg0);
void func_800B8134(unk800B8134 *arg0);
void func_800BBE08(LevelModel *level, unk800BBE08_arg1 *arg1);
void obj_loop_wavepower(Object *obj);
void func_800BFC54(unk800BFC54_arg0 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_800BF3E4(s32 arg0);
f32 get_wave_height(Object_Log *log, s32 updateRate);

Object_64 *func_800BE654(s16, f32, f32); // Non Matching
void func_800BBF78(LevelModel *arg0); // Non Matching
f32 func_800BB2F4(s32, f32, f32, f32*);
void func_800B8C04(s32, s32, s32, s32, s32);
void func_800BF524(Object *);
void *func_800BF634(Object *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, s32 arg8);
f32 func_800BEFC4(s32, s32, s32);

#endif
