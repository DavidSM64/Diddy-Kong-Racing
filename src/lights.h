#ifndef _LIGHTS_H_
#define _LIGHTS_H_

#include "types.h"
#include "structs.h"
#include "libc/math.h"

enum LightType {
    LIGHT_UNK0,
    LIGHT_UNK1,
    LIGHT_UNK2,
    LIGHT_UNK3,
    LIGHT_UNK4,
    LIGHT_UNK5,
};

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
typedef struct ObjectLight {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 type;
    u8 enabled;
    u8 unk5;
    s16 homeX;
    s16 homeY;
    s16 homeZ;
    Object *owner;
    f32 x;
    f32 y;
    f32 z;
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
    f32 radius;
    f32 unk60;
    f32 unk64;
    f32 radiusSquare;
    f32 radiusMag;
    s16 unk70;
    s16 unk72;
    s16 unk74;
    s16 unk76;
    s16 unk78;
    s16 unk7A;
    f32 unk7C; // Think this might be scale.
    f32 unk80; // Ditto.
    f32 unk84; // The evolved form of ditto.
} ObjectLight;

/* Size: 0x14 bytes */
typedef struct unk800DC960 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} unk800DC960;

void free_lights(void);
void lightUpdateLights(s32 updateRate);
void func_80032BAC(ObjectLight *light);
s32 get_light_count(void);
f32 light_distance_calc(ObjectLight *light);
f32 light_direction_calc(ObjectLight *light);
ObjectLight *func_80031CAC(Object *light, LevelObjectEntry_RgbaLight *lightEntry);
ObjectLight *add_object_light(Object *obj, ObjectHeader24 *arg1);

//Non Matching
void setup_lights(s32 count);
void func_80032C7C(Object *object);
void func_800337E4(void);
void func_80032424(ObjectLight *light, s32 arg1);

#endif
