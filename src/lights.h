#ifndef _LIGHTS_H_
#define _LIGHTS_H_

#include "types.h"
#include "structs.h"

enum LightType {
    LIGHT_UNK0,
    LIGHT_UNK1,
    LIGHT_UNK2,
    LIGHT_UNK3,
    LIGHT_UNK4,
    LIGHT_UNK5,
};

typedef struct SubMiscAssetObjectHeader24 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    s32 unk4;
} SubMiscAssetObjectHeader24;

typedef struct MiscAssetObjectHeader24 {
    s32 unk0;
    u8 pad2[16];
    SubMiscAssetObjectHeader24 unk14[1];
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
    Vec3f pos;
    s32 colourR;
    s32 colourG;
    s32 colourB;
    s32 intensity;
    s32 targetColourChangeRateR;
    s32 targetColourChangeRateG;
    s32 targetColourChangeRateB;
    s32 targetIntensityChangeRate;
    u16 targetColourDiffR;
    u16 targetColourDiffG;
    u16 targetColourDiffB;
    u16 targetIntensityDiff;
    union {
        SubMiscAssetObjectHeader24 *unk44;
        MiscAssetObjectHeader24 *unk44_asset;
    };    
    u16 unk48;
    u16 unk4A;
    u16 unk4C;
    u16 unk4E;
    s16 minX;
    s16 minY;
    s16 minZ;
    s16 maxX;
    s16 maxY;
    s16 maxZ;
    f32 radius;
    f32 unk60;
    f32 unk64;
    f32 radiusSquare;
    f32 radiusMag;
    s16 unk70;
    s16 unk72;
    s16 unk74;
    s16 unk76;
    u16 unk78;
    u16 unk7A;
    Vec3f direction; // Think this might be scale.
} ObjectLight;

/* Size: 0x14 bytes */
typedef struct ObjectLightShadeProperties {
    ObjectLight* lightObj;
    s32 colourR;
    s32 colourG;
    s32 colourB;
    s32 intensity;
} ObjectLightShadeProperties;

void free_lights(void);
void lightUpdateLights(s32 updateRate);
void destroy_object_light(ObjectLight *light);
s32 get_light_count(void);
f32 light_distance_calc(ObjectLight *light);
f32 light_direction_calc(ObjectLight *light);
ObjectLight *add_level_object_light(Object *obj, LevelObjectEntry_RgbaLight *lightEntry);
ObjectLight *add_object_light(Object *obj, ObjectHeader24 *arg1);
void light_update(ObjectLight *light, s32 updateRate);

//Non Matching
void setup_lights(s32 count);
void update_object_shading(Object *object);
void update_ambient_light(void);

#endif
