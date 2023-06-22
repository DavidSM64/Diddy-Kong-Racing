#ifndef _LIGHTS_H_
#define _LIGHTS_H_

#include "types.h"
#include "structs.h"
#include "libc/math.h"

typedef struct SubMiscAssetObjectHeader24 {
    s32 unk0;
    s32 unk4;
} SubMiscAssetObjectHeader24;

typedef struct MiscAssetObjectHeader24 {
    s32 unk0;
    u8 pad2[16];
    SubMiscAssetObjectHeader24 *unk14;
} MiscAssetObjectHeader24;

/* Size: 0x88 bytes */
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
    Object *unkC;
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
    SubMiscAssetObjectHeader24 *unk44;
    u16 unk48;
    s16 unk4A;
    s16 unk4C;
    u16 unk4E;
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

f32 coss_f(s16); //?

void free_lights(void);
void func_80032210(unk800DC950 *arg0);
void func_80032218(unk800DC950 *arg0);
void func_80032224(unk800DC950 *arg0);
void func_80032248(unk800DC950 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_80032344(unk800DC950 *arg0, s32 arg1, s32 arg2);
void lightUpdateLights(s32 arg0);
void func_80032BAC(unk800DC950 *arg0);
s32 func_80032C6C(void);
f32 light_distance_calc(unk800DC950 *arg0);
f32 light_direction_calc(unk800DC950 *arg0);
Object_64 *func_80031CAC(Object *, LevelObjectEntry_RgbaLight *entry);

//Non Matching
void setup_lights(s32 count);
void func_80032C7C(Object *object);
void func_800337E4(void);
void func_80032424(unk800DC950 *arg0, s32 arg1);

#endif
