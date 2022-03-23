#ifndef _GAME_UI_H_
#define _GAME_UI_H_

#include "types.h"
#include "structs.h"
#include "libultra_internal.h"

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

u8 func_800A0190(void);
void func_800A0B74(void);
void func_800A0DC0(s32 arg0, Object *arg1, s32 arg2);
void func_800A1428(s32 arg0, Object *arg1, s32 arg2);
void func_800A258C(s32 arg0, Object *arg1, s32 arg2);
void func_800A263C(s32 arg0, Object *arg1, s32 arg2);
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
void func_800A14F0(Object *, s32);
void func_800A3CE4(s32, s32);
void func_800A7520(Object *, s32);
void func_800A0EB4(Object_64 *arg0, s32 arg1);
void func_800A5A64(Object_64 *arg0, s32 arg1);
void func_800A4F50(Object_64 *arg0, s32 arg1);
void func_800A4154(Object_64 *arg0, s32 arg1);
void func_800A7B68(Object_64 *arg0, s32 arg1);
void func_800A4C44(Object_64 *arg0, s32 arg1);
void func_800A3884(Object *arg0, s32 arg1);
void func_800A47A0(Object_64 *arg0, s32 arg1);
void func_800A718C(Object_64 *);
void func_800AA600(Gfx **arg0, u32 *arg1, u32 *arg2, unk80126CDC *arg3);
void func_8009ECF0(s32 viewPortCount);
void func_800A003C(void);

#endif
