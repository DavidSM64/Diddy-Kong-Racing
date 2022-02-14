#ifndef _GAME_UI_H_
#define _GAME_UI_H_

#include "types.h"
#include "structs.h"

typedef struct {
    u8 unk0[0x6];
    s16 unk6;
    u8 unk8[0x4BC];
    u16 unk4C4;
    u8 unk4C6[0x1B4];
    s8 unk67A;
    s8 unk67B[0xA4];
    s8 unk720;
} unk80126CDC;

typedef struct {
    u8 unk0[0x4C];
    s8 unk4C;
} unk80126D60;

typedef struct unk800E1E64 {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
} unk800E1E64;

/* Size: 0x10 bytes */
typedef struct unk800E2770 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} unk800E2770;

typedef struct {
    u8 unk0[0x1D8];
    s8 unk1D8;
} unk800A0DC0_2;

//Probably Object
typedef struct {
    u8 unk0[0x64];
    unk800A0DC0_2 *unk64;
} unk800A0DC0;

u8 func_800A0190(void);
void func_800A0B74(void);
void func_800A0DC0(s32 arg0, unk800A0DC0 *arg1, s32 arg2);
void func_800A1428(s32 arg0, unk800A0DC0 *arg1, s32 arg2);
void func_800A258C(s32 arg0, unk800A0DC0 *arg1, s32 arg2);
void func_800A263C(s32 arg0, unk800A0DC0 *arg1, s32 arg2);
void func_800A3870(void);
void func_800A6DB4(s16 *arg0);
void func_800A7484(u16 arg0, f32 arg1, s32 arg2);
void func_800A74EC(u16 arg0, s32 arg1);
void func_800A83B4(LevelModel *model);
s8 func_800A8458(void);
void func_800AB194(s32 arg0);
void func_800AB1AC(s32 arg0);
void func_800AB1C8(void);
void func_800AB1D4(u8 arg0);

// Non Matching
void func_800A14F0(unk800A0DC0 *, s32);
void func_800A3CE4(s32, s32);
void func_800A7520(unk800A0DC0 *, s32);

#endif
