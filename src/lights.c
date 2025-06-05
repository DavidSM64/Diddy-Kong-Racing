#include "lights.h"

#include "memory.h"
#include "types.h"
#include "macros.h"
#include "objects.h"
#include "game.h"
#include "math_util.h"

/************ .data ************/

ObjectLight **gActiveLights = NULL;
ObjectLight *D_800DC954 = NULL;
s32 gMaxLights = 0;
s32 gNumActiveLights = 0;
unk800DC960 *D_800DC960 = NULL;
Vec3f *gLightDirs = NULL;
s32 numLights = 0; // Currently unknown, might be a different type.

/*******************************/

/************ .bss ************/

f32 gLightDistance;
f32 gLightDiffX;
f32 gLightDiffY;
f32 gLightDiffZ;

/*******************************/

/**
 * Free all lights from RAM.
 * Official Name: freeLights
 */
void free_lights(void) {
    if (gActiveLights != NULL) {
        mempool_free(gActiveLights);
        gActiveLights = NULL;
        D_800DC954 = NULL;
        D_800DC960 = NULL;
        gLightDirs = NULL;
    }
    gNumActiveLights = 0;
    gMaxLights = 0;
}

/**
 * Official Name: setupLights
 */
void setup_lights(s32 count) {
    s32 i;
    u8 *buffer;
    s32 temp;

    free_lights();
    gMaxLights = count;
    buffer = (u8 *) mempool_alloc_safe(
        gMaxLights * (sizeof(s32 *) + sizeof(ObjectLight) + sizeof(unk800DC960) + sizeof(Vec3f)), COLOUR_TAG_MAGENTA);

    temp = gMaxLights;
    gActiveLights = (ObjectLight **) buffer;
    buffer += temp * sizeof(ObjectLight *);
    D_800DC954 = (ObjectLight *) buffer;
    D_800DC960 = (unk800DC960 *) ((u32) D_800DC954 + temp * sizeof(ObjectLight));
    gLightDirs = (Vec3f *) ((u32) D_800DC960 + temp * sizeof(unk800DC960));
    for (i = 0; i < gMaxLights; i++) {
        gActiveLights[i] = &D_800DC954[i];
    }
}

ObjectLight *func_80031CAC(Object *obj, LevelObjectEntry_RgbaLight *lightEntry) {
    s32 i;
    ObjectLight *light;
    LevelHeader *levelHeader;
    MiscAssetObjectHeader24 *miscAsset;

    light = NULL;
    if (gNumActiveLights < gMaxLights) {
        light = gActiveLights[gNumActiveLights++];
        light->unk0 = (lightEntry->unk8 & 0xF0) >> 4;
        light->type = lightEntry->unk8 & 0xF;
        light->unk1 = (lightEntry->unk9 & 0xE0) >> 5;
        light->unk2 = lightEntry->unk9 & 0x1F;
        light->enabled = TRUE;
        light->owner = NULL;
        light->homeX = 0;
        light->homeY = 0;
        light->homeZ = 0;
        if (obj != NULL) {
            light->pos.x = obj->segment.trans.x_position;
            light->pos.y = obj->segment.trans.y_position;
            light->pos.z = obj->segment.trans.z_position;
        } else {
            light->pos.x = lightEntry->common.x;
            light->pos.y = lightEntry->common.y;
            light->pos.z = lightEntry->common.z;
        }
        light->colourR = lightEntry->unkA << 16;
        light->unk2C = 0;
        light->unk3C = 0;
        light->colourG = lightEntry->unkB << 16;
        light->unk30 = 0;
        light->unk3E = 0;
        light->colourB = lightEntry->unkC << 16;
        light->unk34 = 0;
        light->unk40 = 0;
        light->intensity = lightEntry->unkD << 16;
        light->unk38 = 0;
        light->unk42 = 0;
        light->unk44 = NULL;
        if (lightEntry->unk1C < 7) {
            levelHeader = get_current_level_header();
            if (((s32) levelHeader->unk74[lightEntry->unk1C]) != -1) {
                light->unk44_asset = (MiscAssetObjectHeader24 *) levelHeader->unk74[lightEntry->unk1C];
                light->unk48 = light->unk44_asset->unk0;
                light->unk4A = 0;
                light->unk4C = 0;
                light->unk4E = 0;
                light->unk44 = light->unk44_asset->unk14;
                // clang-format off
                for (i = 0; i < light->unk48; i++) { light->unk4E += light->unk44[i].unk4; } // Must be on one line!
                // clang-format on
            }
        }
        light->radius = lightEntry->unkE;
        light->unk60 = lightEntry->unk10;
        light->unk64 = lightEntry->unk12;
        light->radiusSquare = light->radius * light->radius;
        light->radiusMag = 1 / light->radius;
        light->unk70 = lightEntry->unk14;
        light->unk74 = lightEntry->unk18;
        light->unk78 = (lightEntry->unk18) ? 0xFFFF : 0;
        light->unk72 = lightEntry->unk16;
        light->unk76 = lightEntry->unk1A;
        light->unk7A = (lightEntry->unk1A) ? 0xFFFF : 0;
        light->unk7A = 0;
        light->unk5 = 1;
        func_80032424(light, 0);
    }
    return light;
}

/**
 * Official Name: addObjectLight
 */
ObjectLight *add_object_light(Object *obj, ObjectHeader24 *arg1) {
    s32 i;
    ObjectLight *light;

    light = NULL;
    if (gNumActiveLights < gMaxLights) {
        light = gActiveLights[gNumActiveLights++];
        light->unk0 = arg1->unk8 >> 0x1C;
        light->unk1 = arg1->unk9;
        light->unk2 = arg1->unkB;
        light->type = arg1->unkA;
        light->enabled = arg1->unk8A & 0xF;
        light->owner = obj;
        light->homeX = arg1->homeX;
        light->homeY = arg1->homeY;
        light->homeZ = arg1->homeZ;
        light->pos.x = light->homeX;
        light->pos.y = light->homeY;
        light->pos.z = light->homeZ;
        light->colourR = arg1->unk2 << 16;
        light->unk2C = 0;
        light->unk3C = 0;
        light->colourG = arg1->unk3 << 16;
        light->unk30 = 0;
        light->unk3E = 0;
        light->colourB = arg1->unk4 << 16;
        light->unk34 = 0;
        light->unk40 = 0;
        light->intensity = arg1->unk5 << 16;
        light->unk38 = 0;
        light->unk42 = 0;
        if (arg1->unk6 != 0xFFFF) {
            light->unk44_asset = (MiscAssetObjectHeader24 *) get_misc_asset(arg1->unk6);
            light->unk48 = light->unk44_asset->unk0;
            light->unk4A = 0;
            light->unk4C = 0;
            light->unk4E = 0;
            light->unk44 = light->unk44_asset->unk14;
            // clang-format off
            for (i = 0; i < light->unk48; i++) { light->unk4E += light->unk44[i].unk4; } // Must be on one line!
            // clang-format on
        } else {
            light->unk44 = 0;
        }
        light->radius = arg1->radius;
        light->unk60 = arg1->unk14;
        light->unk64 = arg1->unk16;
        light->radiusSquare = light->radius * light->radius;
        light->radiusMag = 1.0f / light->radius;
        light->unk70 = arg1->unk0 << 8;
        light->unk74 = 0;
        light->unk78 = 0;
        light->unk72 = arg1->unk1 << 8;
        light->unk76 = 0;
        light->unk7A = 0;
        light->unk5 = 1;
        func_80032424(light, 0);
    }
    return light;
}

/**
 * Disable this objects light data.
 * Official Name: turnLightOff?
 */
UNUSED void disable_object_light(ObjectLight *light) {
    light->enabled = FALSE;
}

/**
 * Enable this objects light data.
 * Official Name: turnLightOn?
 */
UNUSED void enable_object_light(ObjectLight *light) {
    light->enabled = TRUE;
}

/**
 * Toggle this objects light data on or off.
 */
UNUSED void toggle_object_light(ObjectLight *light) {
    if (light->enabled == TRUE) {
        light->enabled = FALSE;
    } else {
        light->enabled = TRUE;
    }
}

UNUSED void func_80032248(ObjectLight *light, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    if (arg2 > 0) {
        light->unk3C = arg2;
        light->unk2C = ((arg1 << 0x10) - light->colourR) / arg2;
    }
    if (arg4 > 0) {
        light->unk3E = arg4;
        light->unk30 = ((arg3 << 0x10) - light->colourG) / arg4;
    }
    if (arg6 > 0) {
        light->unk34 = ((arg5 << 0x10) - light->colourB) / arg6;
        light->unk40 = arg6;
    }
}

UNUSED void func_80032344(ObjectLight *light, s32 arg1, s32 arg2) {
    if (arg2 > 0) {
        light->unk42 = arg2;
        light->unk38 = ((arg1 << 0x10) - light->intensity) / arg2;
    }
}

/**
 * Loops through all active lights and updates their properties.
 */
void lightUpdateLights(s32 updateRate) {
    s32 i;
    for (i = 0; i < gNumActiveLights; i++) {
        func_80032424(gActiveLights[i], updateRate);
    }
}

void func_80032424(ObjectLight *light, s32 updateRate) {
    Vec3s rotation;
    SubMiscAssetObjectHeader24 *var_a3;
    s32 temp_v0;
    SubMiscAssetObjectHeader24 *temp_v1;

    if (light->owner != NULL) {
        light->pos.x = light->homeX;
        light->pos.y = light->homeY;
        light->pos.z = light->homeZ;
        vec3f_rotate(&light->owner->segment.trans.rotation, &light->pos);
        light->pos.x += light->owner->segment.trans.x_position;
        light->pos.y += light->owner->segment.trans.y_position;
        light->pos.z += light->owner->segment.trans.z_position;
        light->unk5 = 1;
    }
    if (light->unk44 != NULL) {
        light->unk4C += updateRate;
        while (light->unk4C >= light->unk44[light->unk4A].unk4) {
            light->unk4C -= light->unk44[light->unk4A].unk4;
            light->unk4A++;
            if (light->unk48 < light->unk4A) {
                light->unk4A = 0;
            }
        }
        temp_v1 = &light->unk44[light->unk4A];
        if (light->unk4A < (light->unk48 - 1)) {
            var_a3 = &light->unk44[light->unk4A + 1];
        } else {
            var_a3 = light->unk44;
        }
        temp_v0 = (0x10000 / temp_v1->unk4);
        light->colourR = ((var_a3->unk0 - temp_v1->unk0) * light->unk4C * temp_v0) + (temp_v1->unk0 << 0x10);
        light->colourG = ((var_a3->unk1 - temp_v1->unk1) * light->unk4C * temp_v0) + (temp_v1->unk1 << 0x10);
        light->colourB = ((var_a3->unk2 - temp_v1->unk2) * light->unk4C * temp_v0) + (temp_v1->unk2 << 0x10);
        light->intensity = ((var_a3->unk3 - temp_v1->unk3) * light->unk4C * temp_v0) + (temp_v1->unk3 << 0x10);
    } else {
        if (light->unk3C != 0) {
            temp_v0 = light->unk3C;
            if (updateRate < light->unk3C) {
                light->colourR += light->unk2C * updateRate;
                light->unk3C -= updateRate;
            } else {
                light->unk3C = 0;
                light->colourR += light->unk2C * temp_v0;
            }
        }
        if (light->unk3E != 0) {
            temp_v0 = light->unk3E;
            if (updateRate < light->unk3E) {
                light->colourG += light->unk30 * updateRate;
                light->unk3E -= updateRate;
            } else {
                light->unk3E = 0;
                light->colourG += light->unk30 * temp_v0;
            }
        }
        if (light->unk40 != 0) {
            temp_v0 = light->unk40;
            if (updateRate < light->unk40) {
                light->colourB += light->unk34 * updateRate;
                light->unk40 -= updateRate;
            } else {
                light->unk40 = 0;
                light->colourB += light->unk34 * temp_v0;
            }
        }
        if (light->unk42 != 0) {
            temp_v0 = light->unk42;
            if (updateRate < light->unk42) {
                light->intensity += light->unk38 * updateRate;
                light->unk42 -= updateRate;
            } else {
                light->unk42 = 0;
                light->intensity += light->unk38 * temp_v0;
            }
        }
    }
    if (light->unk78 != 0) {
        temp_v0 = light->unk78;
        if (light->unk78 == 0xFFFF) {
            light->unk70 += light->unk74 * updateRate;
        } else if (updateRate < temp_v0) {
            light->unk70 += light->unk74 * updateRate;
            light->unk78 = temp_v0 - updateRate;
        } else {
            light->unk78 = 0;
            light->unk70 += light->unk74 * temp_v0;
        }
        light->unk5 = 1;
    }
    if (light->unk7A != 0) {
        temp_v0 = light->unk7A;
        if (light->unk7A == 0xFFFF) {
            light->unk72 += light->unk76 * updateRate;
        } else if (updateRate < temp_v0) {
            light->unk72 += light->unk76 * updateRate;
            light->unk7A = temp_v0 - updateRate;
        } else {
            light->unk7A = 0;
            light->unk72 += light->unk76 * temp_v0;
        }
        light->unk5 = 1;
    }
    if (light->unk5) {
        light->unk50 = light->pos.x - light->radius;
        light->unk56 = light->pos.x + light->radius;
        if (light->unk0 == 1) {
            light->unk52 = light->pos.y - light->radius;
            light->unk58 = light->pos.y + light->radius;
        } else {
            light->unk52 = light->pos.y - light->unk60;
            light->unk58 = light->pos.y + light->unk60;
        }
        if (light->unk0 == 0) {
            light->unk54 = light->pos.z - light->unk64;
            light->unk5A = light->pos.z + light->unk64;
        } else {
            light->unk54 = light->pos.z - light->radius;
            light->unk5A = light->pos.z + light->radius;
        }
        if (light->unk1 == 2) {
            light->direction.z = -1.0f;
            rotation.y_rotation = light->unk70;
            rotation.x_rotation = light->unk72;
            rotation.z_rotation = 0;
            vec3f_rotate_py(&rotation, &light->direction);
            if (light->owner != NULL) {
                vec3f_rotate(&light->owner->segment.trans.rotation, &light->direction);
            }
            light->direction.x = -light->direction.x;
            light->direction.y = -light->direction.y;
            light->direction.z = -light->direction.z;
        }
        light->unk5 = 0;
    }
}

/**
 * Official Name: killLight?
 */
void func_80032BAC(ObjectLight *light) {
    ObjectLight *entry = NULL;
    s32 i;
    for (i = 0; (i < gNumActiveLights) && (entry == NULL); i++) {
        if (light == gActiveLights[i]) {
            entry = gActiveLights[i];
        }
    }
    if (entry != NULL) {
        gNumActiveLights--;
        for (i--; i < gNumActiveLights; i++) {
            gActiveLights[i] = gActiveLights[i + 1];
        }
        gActiveLights[gNumActiveLights] = entry;
    }
}

/**
 * Return the number of active lights.
 * Official Name: lightGetLights?
 */
s32 get_light_count(void) {
    return gNumActiveLights;
}

void func_80032C7C(Object *object) {
    ObjectLight *light;
    s16 primIndex, secIndex;
    f32 intensity;
    s16 objX;
    s16 objY;
    s16 objZ;
    u8 sp64;
    s32 i;

    if (object->segment.header->unk3D == 0) {
        switch (object->segment.header->modelType) {
            case OBJECT_MODEL_TYPE_3D_MODEL:
                sp64 = 2;
                break;
            case OBJECT_MODEL_TYPE_SPRITE_BILLBOARD:
                sp64 = 4;
                break;
            case OBJECT_MODEL_TYPE_VEHICLE_PART:
                sp64 = 4;
                break;
            case OBJECT_MODEL_TYPE_UNKNOWN3:
                sp64 = 4;
                break;
            default:
                sp64 = 0;
                break;
        }

        objX = object->segment.trans.x_position;
        objY = object->segment.trans.y_position;
        objZ = object->segment.trans.z_position;

        numLights = 0;

        for (i = 0; i < gNumActiveLights; i++) {
            light = gActiveLights[i];
            if ((light->unk2 & sp64) && (light->enabled == TRUE) && (objX >= light->unk50) && (light->unk56 >= objX) &&
                (objY >= light->unk52) && (light->unk58 >= objY) && (objZ >= light->unk54) && (light->unk5A >= objZ)) {
                if (light->unk0 == 0) {
                    if (light->intensity >= 0x10000) {
                        D_800DC960[numLights].lightObj = light;
                        D_800DC960[numLights].colourR = light->colourR >> 0x10;
                        D_800DC960[numLights].colourG = light->colourG >> 0x10;
                        D_800DC960[numLights].colourB = light->colourB >> 0x10;
                        D_800DC960[numLights].intensity = light->intensity >> 0x10;
                        numLights++;
                    }
                } else {
                    gLightDiffX = light->pos.x - object->segment.trans.x_position;
                    gLightDiffY = light->pos.y - object->segment.trans.y_position;
                    gLightDiffZ = light->pos.z - object->segment.trans.z_position;
                    if (light->unk0 == 2) {
                        gLightDiffY = 0.0f;
                    }
                    gLightDistance =
                        (gLightDiffX * gLightDiffX) + (gLightDiffY * gLightDiffY) + (gLightDiffZ * gLightDiffZ);
                    if (gLightDistance < light->radiusSquare) {
                        if (light->unk1 == 2) {
                            intensity = light_direction_calc(light);
                        } else {
                            intensity = 1.0f;
                        }
                        if (intensity > 0.0f) {
                            intensity *= light_distance_calc(light);
                            if (intensity > 0.0f) {
                                if (object->segment.header->directionalPointLighting) {
                                    if (gLightDistance > 0.0f) {
                                        f32 temp = 1.0f / sqrtf(gLightDistance);
                                        gLightDiffX *= temp;
                                        gLightDiffY *= temp;
                                        gLightDiffZ *= temp;
                                    } else {
                                        gLightDiffX = 0;
                                        gLightDiffY = 0;
                                        gLightDiffZ = -1.0f;
                                    }
                                    gLightDirs[numLights].x = gLightDiffX;
                                    gLightDirs[numLights].y = gLightDiffY;
                                    gLightDirs[numLights].z = gLightDiffZ;
                                }
                                D_800DC960[numLights].lightObj = light;
                                D_800DC960[numLights].colourR = light->colourR >> 0x10;
                                D_800DC960[numLights].colourG = light->colourG >> 0x10;
                                D_800DC960[numLights].colourB = light->colourB >> 0x10;
                                D_800DC960[numLights].intensity = (u8) intensity;
                                numLights++;
                            }
                        }
                    }
                }
            }
        }

        if (object->segment.header->directionalPointLighting) {
            // find two brightest light sources
            if (numLights == 0) {
                object->shading->lightIntensity = 0;
                object->shading->secondaryLightIntensity = 0;
            } else if (numLights == 1) {
                object->shading->lightR = D_800DC960[0].colourR;
                object->shading->lightG = D_800DC960[0].colourG;
                object->shading->lightB = D_800DC960[0].colourB;
                object->shading->lightIntensity = D_800DC960[0].intensity;
                object->shading->secondaryLightIntensity = 0;
                object->shading->lightDirX = gLightDirs[0].x * 8192.0f;
                object->shading->lightDirY = gLightDirs[0].y * 8192.0f;
                object->shading->lightDirZ = gLightDirs[0].z * 8192.0f;
            } else {
                if (D_800DC960[1].intensity < D_800DC960[0].intensity) {
                    primIndex = 0;
                    secIndex = 1;
                } else {
                    primIndex = 1;
                    secIndex = 0;
                }
                for (i = 2; i < numLights; i++) {
                    if (D_800DC960[secIndex].intensity < D_800DC960[i].intensity) {
                        if (D_800DC960[primIndex].intensity < D_800DC960[i].intensity) {
                            secIndex = primIndex;
                            primIndex = i;
                        } else {
                            secIndex = i;
                        }
                    }
                }
                object->shading->lightR = D_800DC960[primIndex].colourR;
                object->shading->lightG = D_800DC960[primIndex].colourG;
                object->shading->lightB = D_800DC960[primIndex].colourB;
                object->shading->lightIntensity = D_800DC960[primIndex].intensity;
                object->shading->lightDirX = gLightDirs[primIndex].x * 8192.0f;
                object->shading->lightDirY = gLightDirs[primIndex].y * 8192.0f;
                object->shading->lightDirZ = gLightDirs[primIndex].z * 8192.0f;

                object->shading->secondaryLightR = D_800DC960[secIndex].colourR;
                object->shading->secondaryLightG = D_800DC960[secIndex].colourG;
                object->shading->secondaryLightB = D_800DC960[secIndex].colourB;
                object->shading->secondaryLightIntensity = D_800DC960[secIndex].intensity;
                object->shading->secondaryLightDirX = gLightDirs[secIndex].x * 8192.0f;
                object->shading->secondaryLightDirY = gLightDirs[secIndex].y * 8192.0f;
                object->shading->secondaryLightDirZ = gLightDirs[secIndex].z * 8192.0f;
            }
        } else {
            if (numLights > 0) {
                if (numLights >= 2) {
                    func_800337E4();
                }
                object->shading->lightR = D_800DC960[0].colourR;
                object->shading->lightG = D_800DC960[0].colourG;
                object->shading->lightB = D_800DC960[0].colourB;
                object->shading->lightIntensity = D_800DC960[0].intensity;
            } else {
                object->shading->lightR = 255;
                object->shading->lightG = 255;
                object->shading->lightB = 255;
                object->shading->lightIntensity = 0;
            }
        }
    }
}

void func_800337E4(void) {
    s32 temp_lo;
    s32 i;

    for (i = 1; i < numLights; i++) {
        if (D_800DC960[i].intensity >= 2) {
            if (D_800DC960[0].intensity >= D_800DC960[i].intensity) {
                temp_lo = (D_800DC960[i].intensity << 16) / D_800DC960[0].intensity;
                D_800DC960[0].colourR += (D_800DC960[i].colourR * temp_lo) >> 16;
                D_800DC960[0].colourG += (D_800DC960[i].colourG * temp_lo) >> 16;
                D_800DC960[0].colourB += (D_800DC960[i].colourB * temp_lo) >> 16;
            } else {
                temp_lo = (D_800DC960[0].intensity << 16) / D_800DC960[i].intensity;
                D_800DC960[0].colourR = ((D_800DC960[0].colourR * temp_lo) >> 16) + D_800DC960[i].colourR;
                D_800DC960[0].colourG = ((D_800DC960[0].colourG * temp_lo) >> 16) + D_800DC960[i].colourG;
                D_800DC960[0].colourB = ((D_800DC960[0].colourB * temp_lo) >> 16) + D_800DC960[i].colourB;
                D_800DC960[0].intensity = D_800DC960[i].intensity;
            }
            if (D_800DC960[0].colourR >= 256) {
                D_800DC960[0].colourR = 255;
            }
            if (D_800DC960[0].colourG >= 256) {
                D_800DC960[0].colourG = 255;
            }
            if (D_800DC960[0].colourB >= 256) {
                D_800DC960[0].colourB = 255;
            }
        }
    }
}

/**
 * Official Name: lightDistanceCalc
 */
f32 light_distance_calc(ObjectLight *light) {
    f32 dist;
    f32 mag;

    dist = light->intensity / 65536.0f;
    switch (light->type) {
        case LIGHT_UNK1:
            mag = 1.0f - (sqrtf(gLightDistance) * light->radiusMag);
            dist *= mag;
            break;
        case LIGHT_UNK2:
            mag = 1.0f - sqrtf(sqrtf(gLightDistance) * light->radiusMag);
            dist *= mag;
            break;
        case LIGHT_UNK3:
            mag = coss_f(sqrtf(gLightDistance) * light->radiusMag * 16384.0f);
            dist *= mag;
            break;
        case LIGHT_UNK4:
            mag = coss_f(sqrtf(gLightDistance) * light->radiusMag * 16384.0f);
            mag *= mag;
            dist *= mag;
            break;
        case LIGHT_UNK5:
            mag = 1.0f - (sqrtf(gLightDistance) * light->radiusMag);
            mag *= mag;
            dist *= mag;
            break;
    }
    return dist;
}

/**
 * Official Name: lightDirectionCalc
 */
f32 light_direction_calc(ObjectLight *light) {
    f32 invDist;
    f32 distance;

    distance = gLightDistance;
    if (distance > 0.0f) {
        invDist = 1.0f / sqrtf(distance);
        distance = (gLightDiffX * invDist * light->direction.x) + (gLightDiffY * invDist * light->direction.y) +
                   (gLightDiffZ * invDist * light->direction.z);
        if (distance < 0.0f) {
            distance = 0.0f;
        }
    } else {
        distance = 1.0f;
    }
    return distance;
}
