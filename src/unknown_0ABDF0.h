#ifndef _UNKNOWN_0ABDF0_H_
#define _UNKNOWN_0ABDF0_H_

#include "types.h"
#include "textures_sprites.h"

/* Size: 0x2C Bytes */
typedef struct unk800E2850 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
} unk800E2850;

/* Size: 0x10 Bytes */
typedef struct unk800E2980 {
    s32 unk0;
    u16 unk4;
    u16 unk6;
    f32 unk8;
    f32 unkC;
} unk800E2980;

/* Size: 0x1C Bytes */
typedef struct unk800E2B4C {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    s16 unk1A;
} unk800E2B4C;

/* Size: 0x18 Bytes */
typedef struct unk800E2C2C {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s32 unk8;
    TextureHeader *unkC;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
} unk800E2C2C;

typedef struct {
    s16 unk0;
    s16 unk2;
} unk80127BF8;

extern u32 osTvType;

void func_800AB308(s16 arg0, s16 arg1);
void func_800AC880(s32 arg0);
void func_800ACF60(Object *arg0);
void func_800AD220(void);
void func_800AD2C4(s32 arg0, s32 arg1, f32 arg2);
void func_800AD40C(void);

#endif
