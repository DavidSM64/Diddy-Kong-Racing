#include "lights.h"

#include "game.h"
#include "libc/math.h"
#include "macros.h"
#include "math_util.h"
#include "memory.h"
#include "objects.h"
#include "types.h"

/************ .data ************/

ObjectLight **gActiveLights = NULL;
ObjectLight *gActiveLightAttrs = NULL;
s32 gMaxLights = 0;
s32 gNumActiveLights = 0;
ObjectLightShadeProperties *gShadeBuffer = NULL;
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
void lights_free(void) {
    if (gActiveLights != NULL) {
        mempool_free(gActiveLights);
        gActiveLights = NULL;
        gActiveLightAttrs = NULL;
        gShadeBuffer = NULL;
        gLightDirs = NULL;
    }
    gNumActiveLights = 0;
    gMaxLights = 0;
}

/**
 * Allocates RAM for all buffers containing light source properties.
 * Official Name: setupLights
 */
void lights_init(s32 count) {
    s32 i;
    u8 *buffer;
    s32 temp;

    lights_free();
    gMaxLights = count;
    buffer = (u8 *) mempool_alloc_safe(
        gMaxLights * (sizeof(s32 *) + sizeof(ObjectLight) + sizeof(ObjectLightShadeProperties) + sizeof(Vec3f)),
        COLOUR_TAG_MAGENTA);

    temp = gMaxLights;
    gActiveLights = (ObjectLight **) buffer;
    buffer += temp * sizeof(ObjectLight *);
    gActiveLightAttrs = (ObjectLight *) buffer;
    gShadeBuffer = (ObjectLightShadeProperties *) ((u32) gActiveLightAttrs + temp * sizeof(ObjectLight));
    gLightDirs = (Vec3f *) ((u32) gShadeBuffer + temp * sizeof(ObjectLightShadeProperties));
    for (i = 0; i < gMaxLights; i++) {
        gActiveLights[i] = &gActiveLightAttrs[i];
    }
}

/**
 * Adds a light source from a level object entry.
 */
ObjectLight *light_add_from_level_object_entry(Object *obj, LevelObjectEntry_RgbaLight *lightEntry) {
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
            light->pos.x = obj->trans.x_position;
            light->pos.y = obj->trans.y_position;
            light->pos.z = obj->trans.z_position;
        } else {
            light->pos.x = lightEntry->common.x;
            light->pos.y = lightEntry->common.y;
            light->pos.z = lightEntry->common.z;
        }
        light->colourR = lightEntry->colourR << 16;
        light->targetColourChangeRateR = 0;
        light->targetColourDiffR = 0;
        light->colourG = lightEntry->colourG << 16;
        light->targetColourChangeRateG = 0;
        light->targetColourDiffG = 0;
        light->colourB = lightEntry->colourB << 16;
        light->targetColourChangeRateB = 0;
        light->targetColourDiffB = 0;
        light->intensity = lightEntry->intensity << 16;
        light->targetIntensityChangeRate = 0;
        light->targetIntensityDiff = 0;
        light->unk44 = NULL;
        if (lightEntry->unk1C < 7) {
            levelHeader = level_header();
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
        light->radius = lightEntry->radius;
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
        light_update(light, 0);
    }
    return light;
}

/**
 * Official Name: addObjectLight
 */
ObjectLight *light_add_from_object_header(Object *obj, ObjectHeader24 *arg1) {
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
        light->targetColourChangeRateR = 0;
        light->targetColourDiffR = 0;
        light->colourG = arg1->unk3 << 16;
        light->targetColourChangeRateG = 0;
        light->targetColourDiffG = 0;
        light->colourB = arg1->unk4 << 16;
        light->targetColourChangeRateB = 0;
        light->targetColourDiffB = 0;
        light->intensity = arg1->unk5 << 16;
        light->targetIntensityChangeRate = 0;
        light->targetIntensityDiff = 0;
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
        light_update(light, 0);
    }
    return light;
}

/**
 * Disable this objects light data.
 * Official Name: turnLightOff?
 */
UNUSED void light_disable(ObjectLight *light) {
    light->enabled = FALSE;
}

/**
 * Enable this objects light data.
 * Official Name: turnLightOn?
 */
UNUSED void light_enable(ObjectLight *light) {
    light->enabled = TRUE;
}

/**
 * Toggle this objects light data on or off.
 */
UNUSED void light_toggle(ObjectLight *light) {
    if (light->enabled == TRUE) {
        light->enabled = FALSE;
    } else {
        light->enabled = TRUE;
    }
}

/**
 * Initialises a gradual change of colour for a light source.
 */
UNUSED void light_setup_colour_change(ObjectLight *light, s32 targetR, s32 diffR, s32 targetG, s32 diffG, s32 targetB,
                                      s32 diffB) {
    if (diffR > 0) {
        light->targetColourDiffR = diffR;
        light->targetColourChangeRateR = ((targetR << 0x10) - light->colourR) / diffR;
    }
    if (diffG > 0) {
        light->targetColourDiffG = diffG;
        light->targetColourChangeRateG = ((targetG << 0x10) - light->colourG) / diffG;
    }
    if (diffB > 0) {
        light->targetColourChangeRateB = ((targetB << 0x10) - light->colourB) / diffB;
        light->targetColourDiffB = diffB;
    }
}

/**
 * Initialises a gradual change of intensity for a light source.
 */
UNUSED void light_setup_intensity_change(ObjectLight *light, s32 target, s32 diff) {
    if (diff > 0) {
        light->targetIntensityDiff = diff;
        light->targetIntensityChangeRate = ((target << 0x10) - light->intensity) / diff;
    }
}

/**
 * Loops through all active lights and updates their properties.
 * Official Name: lightUpdateLights
 */
void light_update_all(s32 updateRate) {
    s32 i;
    for (i = 0; i < gNumActiveLights; i++) {
        light_update(gActiveLights[i], updateRate);
    }
}

/**
 * Updates an active light's properties.
 */
void light_update(ObjectLight *light, s32 updateRate) {
    Vec3s rotation;
    SubMiscAssetObjectHeader24 *var_a3;
    s32 temp_v0;
    SubMiscAssetObjectHeader24 *temp_v1;

    if (light->owner != NULL) {
        light->pos.x = light->homeX;
        light->pos.y = light->homeY;
        light->pos.z = light->homeZ;
        vec3f_rotate(&light->owner->trans.rotation, &light->pos);
        light->pos.x += light->owner->trans.x_position;
        light->pos.y += light->owner->trans.y_position;
        light->pos.z += light->owner->trans.z_position;
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
        if (light->targetColourDiffR != 0) {
            temp_v0 = light->targetColourDiffR;
            if (updateRate < light->targetColourDiffR) {
                light->colourR += light->targetColourChangeRateR * updateRate;
                light->targetColourDiffR -= updateRate;
            } else {
                light->targetColourDiffR = 0;
                light->colourR += light->targetColourChangeRateR * temp_v0;
            }
        }
        if (light->targetColourDiffG != 0) {
            temp_v0 = light->targetColourDiffG;
            if (updateRate < light->targetColourDiffG) {
                light->colourG += light->targetColourChangeRateG * updateRate;
                light->targetColourDiffG -= updateRate;
            } else {
                light->targetColourDiffG = 0;
                light->colourG += light->targetColourChangeRateG * temp_v0;
            }
        }
        if (light->targetColourDiffB != 0) {
            temp_v0 = light->targetColourDiffB;
            if (updateRate < light->targetColourDiffB) {
                light->colourB += light->targetColourChangeRateB * updateRate;
                light->targetColourDiffB -= updateRate;
            } else {
                light->targetColourDiffB = 0;
                light->colourB += light->targetColourChangeRateB * temp_v0;
            }
        }
        if (light->targetIntensityDiff != 0) {
            temp_v0 = light->targetIntensityDiff;
            if (updateRate < light->targetIntensityDiff) {
                light->intensity += light->targetIntensityChangeRate * updateRate;
                light->targetIntensityDiff -= updateRate;
            } else {
                light->targetIntensityDiff = 0;
                light->intensity += light->targetIntensityChangeRate * temp_v0;
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
        light->minX = light->pos.x - light->radius;
        light->maxX = light->pos.x + light->radius;
        if (light->unk0 == 1) {
            light->minY = light->pos.y - light->radius;
            light->maxY = light->pos.y + light->radius;
        } else {
            light->minY = light->pos.y - light->unk60;
            light->maxY = light->pos.y + light->unk60;
        }
        if (light->unk0 == 0) {
            light->minZ = light->pos.z - light->unk64;
            light->maxZ = light->pos.z + light->unk64;
        } else {
            light->minZ = light->pos.z - light->radius;
            light->maxZ = light->pos.z + light->radius;
        }
        if (light->unk1 == 2) {
            light->direction.z = -1.0f;
            rotation.y_rotation = light->unk70;
            rotation.x_rotation = light->unk72;
            rotation.z_rotation = 0;
            vec3f_rotate_py(&rotation, &light->direction);
            if (light->owner != NULL) {
                vec3f_rotate(&light->owner->trans.rotation, &light->direction);
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
void light_remove(ObjectLight *light) {
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
s32 light_count(void) {
    return gNumActiveLights;
}

/**
 * Updates the shading on an object based on nearby high-intensity light sources.
 */
void light_update_shading(Object *object) {
    ObjectLight *light;
    s16 primIndex, secIndex;
    f32 intensity;
    s16 objX;
    s16 objY;
    s16 objZ;
    u8 objTypeMask;
    s32 i;

    if (object->header->shadeIntensityy == 0) {
        switch (object->header->modelType) {
            case OBJECT_MODEL_TYPE_3D_MODEL:
                objTypeMask = LIGHT_MASK_UNK2;
                break;
            case OBJECT_MODEL_TYPE_SPRITE_BILLBOARD:
                objTypeMask = LIGHT_MASK_UNK4;
                break;
            case OBJECT_MODEL_TYPE_VEHICLE_PART:
                objTypeMask = LIGHT_MASK_UNK4;
                break;
            case OBJECT_MODEL_TYPE_UNKNOWN3:
                objTypeMask = LIGHT_MASK_UNK4;
                break;
            default:
                objTypeMask = LIGHT_MASK_NONE;
                break;
        }

        objX = object->trans.x_position;
        objY = object->trans.y_position;
        objZ = object->trans.z_position;

        numLights = 0;

        for (i = 0; i < gNumActiveLights; i++) {
            light = gActiveLights[i];
            if ((light->unk2 & objTypeMask) && (light->enabled == TRUE) && (objX >= light->minX) &&
                (light->maxX >= objX) && (objY >= light->minY) && (light->maxY >= objY) && (objZ >= light->minZ) &&
                (light->maxZ >= objZ)) {
                if (light->unk0 == 0) {
                    if (light->intensity >= 0x10000) {
                        gShadeBuffer[numLights].lightObj = light;
                        gShadeBuffer[numLights].colourR = light->colourR >> 0x10;
                        gShadeBuffer[numLights].colourG = light->colourG >> 0x10;
                        gShadeBuffer[numLights].colourB = light->colourB >> 0x10;
                        gShadeBuffer[numLights].intensity = light->intensity >> 0x10;
                        numLights++;
                    }
                } else {
                    gLightDiffX = light->pos.x - object->trans.x_position;
                    gLightDiffY = light->pos.y - object->trans.y_position;
                    gLightDiffZ = light->pos.z - object->trans.z_position;
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
                                if (object->header->directionalPointLighting) {
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
                                gShadeBuffer[numLights].lightObj = light;
                                gShadeBuffer[numLights].colourR = light->colourR >> 0x10;
                                gShadeBuffer[numLights].colourG = light->colourG >> 0x10;
                                gShadeBuffer[numLights].colourB = light->colourB >> 0x10;
                                gShadeBuffer[numLights].intensity = (u8) intensity;
                                numLights++;
                            }
                        }
                    }
                }
            }
        }

        if (object->header->directionalPointLighting) {
            // find two brightest light sources
            if (numLights == 0) {
                object->shading->lightIntensity = 0;
                object->shading->secondaryLightIntensity = 0;
            } else if (numLights == 1) {
                object->shading->lightR = gShadeBuffer[0].colourR;
                object->shading->lightG = gShadeBuffer[0].colourG;
                object->shading->lightB = gShadeBuffer[0].colourB;
                object->shading->lightIntensity = gShadeBuffer[0].intensity;
                object->shading->secondaryLightIntensity = 0;
                object->shading->lightDirX = gLightDirs[0].x * 8192.0f;
                object->shading->lightDirY = gLightDirs[0].y * 8192.0f;
                object->shading->lightDirZ = gLightDirs[0].z * 8192.0f;
            } else {
                if (gShadeBuffer[1].intensity < gShadeBuffer[0].intensity) {
                    primIndex = 0;
                    secIndex = 1;
                } else {
                    primIndex = 1;
                    secIndex = 0;
                }
                for (i = 2; i < numLights; i++) {
                    if (gShadeBuffer[secIndex].intensity < gShadeBuffer[i].intensity) {
                        if (gShadeBuffer[primIndex].intensity < gShadeBuffer[i].intensity) {
                            secIndex = primIndex;
                            primIndex = i;
                        } else {
                            secIndex = i;
                        }
                    }
                }
                object->shading->lightR = gShadeBuffer[primIndex].colourR;
                object->shading->lightG = gShadeBuffer[primIndex].colourG;
                object->shading->lightB = gShadeBuffer[primIndex].colourB;
                object->shading->lightIntensity = gShadeBuffer[primIndex].intensity;
                object->shading->lightDirX = gLightDirs[primIndex].x * 8192.0f;
                object->shading->lightDirY = gLightDirs[primIndex].y * 8192.0f;
                object->shading->lightDirZ = gLightDirs[primIndex].z * 8192.0f;

                object->shading->secondaryLightR = gShadeBuffer[secIndex].colourR;
                object->shading->secondaryLightG = gShadeBuffer[secIndex].colourG;
                object->shading->secondaryLightB = gShadeBuffer[secIndex].colourB;
                object->shading->secondaryLightIntensity = gShadeBuffer[secIndex].intensity;
                object->shading->secondaryLightDirX = gLightDirs[secIndex].x * 8192.0f;
                object->shading->secondaryLightDirY = gLightDirs[secIndex].y * 8192.0f;
                object->shading->secondaryLightDirZ = gLightDirs[secIndex].z * 8192.0f;
            }
        } else {
            // Ambient light shading
            if (numLights > 0) {
                if (numLights >= 2) {
                    light_update_ambience();
                }
                object->shading->lightR = gShadeBuffer[0].colourR;
                object->shading->lightG = gShadeBuffer[0].colourG;
                object->shading->lightB = gShadeBuffer[0].colourB;
                object->shading->lightIntensity = gShadeBuffer[0].intensity;
            } else {
                object->shading->lightR = 255;
                object->shading->lightG = 255;
                object->shading->lightB = 255;
                object->shading->lightIntensity = 0;
            }
        }
    }
}

/**
 * In the case of ambient lighting for object shading, mix ambient light sources based on
 * their intensity into the first entry in the shading buffer.
 */
void light_update_ambience(void) {
    s32 intensityRatio;
    s32 i;

    for (i = 1; i < numLights; i++) {
        if (gShadeBuffer[i].intensity >= 2) {
            if (gShadeBuffer[0].intensity >= gShadeBuffer[i].intensity) {
                intensityRatio = (gShadeBuffer[i].intensity << 16) / gShadeBuffer[0].intensity;
                gShadeBuffer[0].colourR += (gShadeBuffer[i].colourR * intensityRatio) >> 16;
                gShadeBuffer[0].colourG += (gShadeBuffer[i].colourG * intensityRatio) >> 16;
                gShadeBuffer[0].colourB += (gShadeBuffer[i].colourB * intensityRatio) >> 16;
            } else {
                intensityRatio = (gShadeBuffer[0].intensity << 16) / gShadeBuffer[i].intensity;
                gShadeBuffer[0].colourR = ((gShadeBuffer[0].colourR * intensityRatio) >> 16) + gShadeBuffer[i].colourR;
                gShadeBuffer[0].colourG = ((gShadeBuffer[0].colourG * intensityRatio) >> 16) + gShadeBuffer[i].colourG;
                gShadeBuffer[0].colourB = ((gShadeBuffer[0].colourB * intensityRatio) >> 16) + gShadeBuffer[i].colourB;
                gShadeBuffer[0].intensity = gShadeBuffer[i].intensity;
            }
            if (gShadeBuffer[0].colourR >= 256) {
                gShadeBuffer[0].colourR = 255;
            }
            if (gShadeBuffer[0].colourG >= 256) {
                gShadeBuffer[0].colourG = 255;
            }
            if (gShadeBuffer[0].colourB >= 256) {
                gShadeBuffer[0].colourB = 255;
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
