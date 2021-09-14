#ifndef _UNKNOWN_032760_H_
#define _UNKNOWN_032760_H_

#include "types.h"
#include "structs.h"

typedef struct unk800DC950 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s16 unk3C;
    s16 unk3E;
    s16 unk40;
    s16 unk42;
    s32 unk44;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    s16 unk4E;
    s16 unk50;
    s16 unk52;
    s16 unk54;
    s16 unk56;
    s16 unk58;
    s16 unk5A;
    f32 unk5C;
    f32 unk60;
    f32 unk64;
    f32 unk68;
    f32 unk6C;
    s16 unk70;
    s16 unk72;
    s16 unk74;
    s16 unk76;
    s16 unk78;
    s16 unk7A;
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} unk800DC950;

/* Size: 0x88 bytes */
typedef struct unk800DC954 {
    unk800DC950 unk0;
    u8 unk20[0x68];
} unk800DC954;

/* Size: 0x14 bytes */
typedef struct unk800DC960 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} unk800DC960;

/* Size: 12 bytes */
typedef struct unk800DC964 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} unk800DC964;

extern unk800DC950 **D_800DC950;

void func_80031B60(void);

#endif
