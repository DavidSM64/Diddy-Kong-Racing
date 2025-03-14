/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80031B60 */

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
Vec3f *D_800DC964 = NULL;
s32 D_800DC968 = 0; // Currently unknown, might be a different type.

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
        D_800DC964 = NULL;
    }
    gNumActiveLights = 0;
    gMaxLights = 0;
}

/**
 * Official Name: setupLights
 */
void setup_lights(s32 count) {
    s32 i;
    s32 newCount;
    ObjectLight **temp_v0;

    free_lights();
    gMaxLights = count;
    temp_v0 = (ObjectLight **) mempool_alloc_safe(
        gMaxLights * (sizeof(s32 *) + sizeof(ObjectLight) + sizeof(unk800DC960) + sizeof(Vec3f)), COLOUR_TAG_MAGENTA);
    newCount = gMaxLights;
    gActiveLights = temp_v0;
    D_800DC954 = (ObjectLight *) (newCount + (0, temp_v0));    // fakematch
    D_800DC960 = (unk800DC960 *) (newCount + (0, D_800DC954)); // fakematch
    D_800DC964 = (Vec3f *) (newCount + (0, D_800DC960));       // fakematch
    for (i = 0; i < gMaxLights; i++) {
        gActiveLights[i] = &D_800DC954[i];
    }
}

#ifdef NON_EQUIVALENT
ObjectLight *func_80031CAC(Object *light, LevelObjectEntry_RgbaLight *lightEntry) {
    s32 i;
    ObjectLight *newLight;
    LevelHeader_70 *test;
    s32 temp_a0;

    newLight = NULL;
    if (gNumActiveLights < gMaxLights) {
        newLight = gActiveLights[gNumActiveLights++];
        newLight->unk0 = (lightEntry->unk8 & 0xF0) >> 4;
        newLight->type = lightEntry->unk8 & 0xF;
        newLight->unk1 = (lightEntry->unk9 & 0xE0) >> 5;
        newLight->unk2 = lightEntry->unk9 & 0x1F;
        newLight->enabled = TRUE;
        newLight->owner = NULL;
        newLight->homeX = 0;
        newLight->homeY = 0;
        newLight->homeZ = 0;
        if (light != NULL) {
            newLight->pos.x = light->segment.trans.x_position;
            newLight->pos.y = light->segment.trans.y_position;
            newLight->pos.z = light->segment.trans.z_position;
        } else {
            newLight->pos.x = lightEntry->common.x;
            newLight->pos.y = lightEntry->common.y;
            newLight->pos.z = lightEntry->common.z;
        }
        newLight->unk1C = lightEntry->unkA << 16;
        newLight->unk2C = 0;
        newLight->unk3C = 0;
        newLight->unk20 = lightEntry->unkB << 16;
        newLight->unk30 = 0;
        newLight->unk3E = 0;
        newLight->unk24 = lightEntry->unkC << 16;
        newLight->unk34 = 0;
        newLight->unk40 = 0;
        newLight->unk28 = lightEntry->unkD << 16;
        newLight->unk38 = 0;
        newLight->unk42 = 0;
        newLight->unk44 = NULL;
        if (lightEntry->unk1C < 7) {
            test = (LevelHeader_70 *) get_current_level_header()->unk74[lightEntry->unk1C];
            if (((s32) test) != -1) {
                newLight->unk44 = &test->unk4;
                newLight->unk44 = &test->unk0;
                newLight->unk4A = 0;
                if (lightEntry && lightEntry && lightEntry) {}
                newLight->unk4C = 0;
                newLight->unk4E = 0;
                newLight->unk48 = (u16) &test->red2;
                temp_a0 = (u16) &test->red2;
                for (i = 0; i < temp_a0;) {
                    newLight->unk4E += test->unk18[i++].unk0;
                }
            }
        }
        newLight->radius = lightEntry->unkE;
        newLight->unk60 = lightEntry->unk10;
        newLight->unk64 = lightEntry->unk12;
        newLight->radiusSquare = newLight->radius * newLight->radius;
        newLight->radiusMag = 1 / newLight->radius;
        newLight->unk70 = lightEntry->unk14;
        newLight->unk74 = lightEntry->unk18;
        newLight->unk78 = (lightEntry->unk18) ? 0xFFFF : 0;
        newLight->unk72 = lightEntry->unk16;
        newLight->unk76 = lightEntry->unk1A;
        newLight->unk7A = (lightEntry->unk1A) ? 0xFFFF : 0;
        newLight->unk7A = 0;
        newLight->unk5 = 1;
        func_80032424(newLight, 0);
    }
    return newLight;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/lights/func_80031CAC.s")
#endif

/**
 * Official Name: addObjectLight
 */
ObjectLight *add_object_light(Object *obj, ObjectHeader24 *arg1) {
    s32 i;
    ObjectLight *light;
    MiscAssetObjectHeader24 *miscAsset;

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
        light->unk1C = arg1->unk2 << 16;
        light->unk2C = 0;
        light->unk3C = 0;
        light->unk20 = arg1->unk3 << 16;
        light->unk30 = 0;
        light->unk3E = 0;
        light->unk24 = arg1->unk4 << 16;
        light->unk34 = 0;
        light->unk40 = 0;
        light->unk28 = arg1->unk5 << 16;
        light->unk38 = 0;
        light->unk42 = 0;
        if (arg1->unk6 != 0xFFFF) {
            miscAsset = (MiscAssetObjectHeader24 *) get_misc_asset(arg1->unk6);
            light->unk44 = (SubMiscAssetObjectHeader24 *) miscAsset;
            light->unk48 = miscAsset->unk0;
            light->unk4A = 0;
            light->unk4C = 0;
            light->unk4E = 0;
            light->unk44 = (SubMiscAssetObjectHeader24 *) &miscAsset->unk14;
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
        return;
    }
    light->enabled = TRUE;
}

UNUSED void func_80032248(ObjectLight *light, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    if (arg2 > 0) {
        light->unk3C = arg2;
        light->unk2C = ((arg1 << 0x10) - light->unk1C) / arg2;
    }
    if (arg4 > 0) {
        light->unk3E = arg4;
        light->unk30 = ((arg3 << 0x10) - light->unk20) / arg4;
    }
    if (arg6 > 0) {
        light->unk34 = ((arg5 << 0x10) - light->unk24) / arg6;
        light->unk40 = arg6;
    }
}

UNUSED void func_80032344(ObjectLight *light, s32 arg1, s32 arg2) {
    if (arg2 > 0) {
        light->unk42 = arg2;
        light->unk38 = ((arg1 << 0x10) - light->unk28) / arg2;
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
        f32_vec3_apply_object_rotation(&light->owner->segment.trans, (f32 *) &light->pos);
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
        light->unk1C = ((var_a3->unk0 - temp_v1->unk0) * light->unk4C * temp_v0) + (temp_v1->unk0 << 0x10);
        light->unk20 = ((var_a3->unk1 - temp_v1->unk1) * light->unk4C * temp_v0) + (temp_v1->unk1 << 0x10);
        light->unk24 = ((var_a3->unk2 - temp_v1->unk2) * light->unk4C * temp_v0) + (temp_v1->unk2 << 0x10);
        light->unk28 = ((var_a3->unk3 - temp_v1->unk3) * light->unk4C * temp_v0) + (temp_v1->unk3 << 0x10);
    } else {
        if (light->unk3C != 0) {
            temp_v0 = light->unk3C;
            if (updateRate < light->unk3C) {
                light->unk1C += light->unk2C * updateRate;
                light->unk3C -= updateRate;
            } else {
                light->unk3C = 0;
                light->unk1C += light->unk2C * temp_v0;
            }
        }
        if (light->unk3E != 0) {
            temp_v0 = light->unk3E;
            if (updateRate < light->unk3E) {
                light->unk20 += light->unk30 * updateRate;
                light->unk3E -= updateRate;
            } else {
                light->unk3E = 0;
                light->unk20 += light->unk30 * temp_v0;
            }
        }
        if (light->unk40 != 0) {
            temp_v0 = light->unk40;
            if (updateRate < light->unk40) {
                light->unk24 += light->unk34 * updateRate;
                light->unk40 -= updateRate;
            } else {
                light->unk40 = 0;
                light->unk24 += light->unk34 * temp_v0;
            }
        }
        if (light->unk42 != 0) {
            temp_v0 = light->unk42;
            if (updateRate < light->unk42) {
                light->unk28 += light->unk38 * updateRate;
                light->unk42 -= updateRate;
            } else {
                light->unk42 = 0;
                light->unk28 += light->unk38 * temp_v0;
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
    if (light->unk5 != 0) {
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
            light->unk84 = -1.0f;
            rotation.y_rotation = light->unk70;
            rotation.x_rotation = light->unk72;
            rotation.z_rotation = 0;
            f32_vec3_apply_object_rotation3(&rotation, &light->unk7C);
            if (light->owner != NULL) {
                f32_vec3_apply_object_rotation(&light->owner->segment.trans, &light->unk7C);
            }
            light->unk7C = -light->unk7C;
            light->unk80 = -light->unk80;
            light->unk84 = -light->unk84;
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

#ifdef NON_EQUIVALENT
// Close to matching. Should be functionally equivalent.
void func_80032C7C(Object *object) {
    s16 sp82;
    s16 sp80;
    s16 sp7E;
    s32 i; // sp68
    s32 sp64;
    f32 f20;
    f32 temp;
    s16 phi_a0, phi_a1;
    ObjectLight *entry;

    if (object->segment.header->unk3D == 0) {
        switch (object->segment.header->modelType) {
            case OBJECT_MODEL_TYPE_3D_MODEL: // 3D Model
                sp64 = 2;
                break;
            case OBJECT_MODEL_TYPE_SPRITE_BILLBOARD: // 2D Billboard
            case OBJECT_MODEL_TYPE_VEHICLE_PART:     // Vehicle Part
            case OBJECT_MODEL_TYPE_UNKNOWN3:
                sp64 = 4;
                break;
            default:
                sp64 = 0;
                break;
        }

        sp82 = object->segment.trans.x_position;
        sp80 = object->segment.trans.y_position;
        sp7E = object->segment.trans.z_position;
        D_800DC968 = 0;
        for (i = 0; i < gNumActiveLights; i++) {
            entry = gActiveLights[i];
            if ((entry->unk2 & sp64) && (entry->enabled == 1) && (sp82 >= entry->unk50) && (entry->unk56 >= sp82) &&
                (sp80 >= entry->unk52) && (entry->unk58 >= sp80) && (sp7E >= entry->unk54) && (entry->unk5A >= sp7E)) {
                if (entry->unk0 == 0) {
                    if (entry->unk28 >= 0x10000) {
                        D_800DC960[D_800DC968].unk0 = entry->unk0;
                        D_800DC960[D_800DC968].unk4 = entry->unk1C >> 0x10;
                        D_800DC960[D_800DC968].unk8 = entry->unk20 >> 0x10;
                        D_800DC960[D_800DC968].unkC = entry->unk24 >> 0x10;
                        D_800DC960[D_800DC968].unk10 = entry->unk28 >> 0x10;
                        D_800DC968 = D_800DC968 + 1;
                    }
                } else {
                    gLightDiffX = entry->pos.x - object->segment.trans.x_position;
                    gLightDiffY = entry->pos.y - object->segment.trans.y_position;
                    gLightDiffZ = entry->pos.z - object->segment.trans.z_position;
                    if (entry->unk0 == 2) {
                        gLightDiffY = 0.0f;
                    }
                    gLightDistance =
                        (gLightDiffX * gLightDiffX) + (gLightDiffY * gLightDiffY) + (gLightDiffZ * gLightDiffZ);
                    if (gLightDistance < entry->radiusSquare) {
                        if (entry->unk1 == 2) {
                            f20 = light_direction_calc(entry);
                        } else {
                            f20 = 1.0f;
                        }
                        if (f20 > 0.0f) {
                            f20 *= light_distance_calc(entry);
                            if (f20 > 0.0f) {
                                if (object->segment.header->unk71 != 0) {
                                    if (gLightDistance > 0.0f) {
                                        temp = 1.0f / sqrtf(gLightDistance);
                                        gLightDiffX *= temp;
                                        gLightDiffY *= temp;
                                        gLightDiffZ *= temp;
                                    } else {
                                        gLightDiffX = 0.0f;
                                        gLightDiffY = 0.0f;
                                        gLightDiffZ = -1.0f;
                                    }
                                    D_800DC964[D_800DC968].x = gLightDiffX;
                                    D_800DC964[D_800DC968].y = gLightDiffY;
                                    D_800DC964[D_800DC968].z = gLightDiffZ;
                                }
                                D_800DC960[D_800DC968].unk0 = entry;
                                D_800DC960[D_800DC968].unk4 = entry->unk1C >> 0x10;
                                D_800DC960[D_800DC968].unk8 = entry->unk20 >> 0x10;
                                D_800DC960[D_800DC968].unkC = entry->unk24 >> 0x10;
                                D_800DC960[D_800DC968].unk10 = (u8) f20;
                                D_800DC968++;
                            }
                        }
                    }
                }
            }
        }

        if (object->segment.header->unk71 != 0) {
            if (D_800DC968 == 0) {
                object->shading->unk7 = 0;
                object->shading->unk11 = 0;
            } else if (D_800DC968 == 1) {
                object->shading->unk4 = D_800DC960[0].unk4;
                object->shading->unk5 = D_800DC960[0].unk8;
                object->shading->unk6 = D_800DC960[0].unkC;
                object->shading->unk7 = D_800DC960[0].unk10;
                object->shading->unk11 = 0;
                object->shading->unk8 = D_800DC964[0].x * 8192.0f;
                object->shading->unkA = D_800DC964[0].y * 8192.0f;
                object->shading->unkC = D_800DC964[0].z * 8192.0f;
            } else {
                if (D_800DC960[1].unk10 < D_800DC960[0].unk10) {
                    phi_a0 = 0;
                    phi_a1 = 1;
                } else {
                    phi_a0 = 1;
                    phi_a1 = 0;
                }
                for (i = 2; i < D_800DC968; i++) {
                    if (D_800DC960[phi_a1].unk10 < D_800DC960[i + 2].unk10) {
                        if (D_800DC960[phi_a0].unk10 < D_800DC960[i + 2].unk10) {
                            phi_a1 = phi_a0;
                            phi_a0 = i;
                        } else {
                            phi_a1 = i;
                        }
                    }
                }
                object->shading->unk4 = D_800DC960[phi_a0].unk4;
                object->shading->unk5 = D_800DC960[phi_a0].unk8;
                object->shading->unk6 = D_800DC960[phi_a0].unkC;
                object->shading->unk7 = D_800DC960[phi_a0].unk10;
                object->shading->unk8 = D_800DC964[phi_a0].x * 8192.0f;
                object->shading->unkA = D_800DC964[phi_a0].y * 8192.0f;
                object->shading->unkC = D_800DC964[phi_a0].z * 8192.0f;
                object->shading->unkE = D_800DC960[phi_a1].unk4;
                object->shading->unkF = D_800DC960[phi_a1].unk8;
                object->shading->unk10 = D_800DC960[phi_a1].unkC;
                object->shading->unk11 = D_800DC960[phi_a1].unk10;
                object->shading->unk12 = D_800DC964[phi_a1].x * 8192.0f;
                object->shading->unk14 = D_800DC964[phi_a1].y * 8192.0f;
                object->shading->unk16 = D_800DC964[phi_a1].z * 8192.0f;
            }
        } else {
            if (D_800DC968 > 0) {
                if (D_800DC968 >= 2) {
                    func_800337E4();
                }
                object->shading->unk4 = D_800DC960[0].unk4;
                object->shading->unk5 = D_800DC960[0].unk8;
                object->shading->unk6 = D_800DC960[0].unkC;
                object->shading->unk7 = D_800DC960[0].unk10;
            } else {
                object->shading->unk4 = 0xFF;
                object->shading->unk5 = 0xFF;
                object->shading->unk6 = 0xFF;
                object->shading->unk7 = 0;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/lights/func_80032C7C.s")
#endif

void func_800337E4(void) {
    s32 temp_a2;
    s32 index;
    s32 temp_a3;
    s32 temp_lo;
    s32 i;
    unk800DC960 *temp_a1;

    for (i = 1; i < D_800DC968; i++) {
        index = i;                          // Needed?
        if ((&D_800DC960[index])->unk10) {} // Fakematch
        temp_a1 = (0, D_800DC960) + index;
        temp_a2 = temp_a1->unk10;
        if (temp_a2 >= 2) {
            temp_a3 = D_800DC960->unk10;
            if (temp_a3 >= temp_a2) {
                temp_lo = ((s32) (temp_a2 << 16)) / temp_a3;
                D_800DC960->unk4 = D_800DC960->unk4 + (((s32) (temp_a1->unk4 * temp_lo)) >> 16);
                D_800DC960->unk8 += ((s32) ((&D_800DC960[index])->unk8 * temp_lo)) >> 16;
                D_800DC960->unkC += ((s32) ((&D_800DC960[index])->unkC * temp_lo)) >> 16;
            } else {
                temp_lo = ((s32) (temp_a3 << 16)) / temp_a2;
                D_800DC960->unk4 = temp_a1->unk4 + (((s32) (D_800DC960->unk4 * temp_lo)) >> 16);
                D_800DC960->unk8 = (&D_800DC960[index])->unk8 + (((s32) ((D_800DC960->unk8 * temp_lo) ^ 0)) >> 16);
                D_800DC960->unkC = (&D_800DC960[index])->unkC + (((s32) (D_800DC960->unkC * temp_lo)) >> 16);
                D_800DC960->unk10 = (&D_800DC960[index])->unk10;
            }
            if (D_800DC960->unk4 >= 256) {
                D_800DC960->unk4 = 255;
            }
            if (D_800DC960->unk8 >= 256) {
                D_800DC960->unk8 = 255;
            }
            if (D_800DC960->unkC >= 256) {
                D_800DC960->unkC = 255;
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

    dist = light->unk28 / 65536.0f;
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
    f32 mag;
    f32 distance;

    distance = gLightDistance;
    if (distance > 0.0f) {
        mag = 1.0f / sqrtf(distance);
        distance = (gLightDiffX * mag * light->unk7C) + (gLightDiffY * mag * light->unk80) +
                   (gLightDiffZ * mag * light->unk84);
        if (distance < 0.0f) {
            distance = 0.0f;
        }
    } else {
        distance = 1.0f;
    }
    return distance;
}
