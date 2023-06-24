/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80031B60 */

#include "lights.h"

#include "memory.h"
#include "types.h"
#include "macros.h"
#include "objects.h"

/************ .data ************/

ObjectLight **gActiveLights = NULL;
ObjectLight *D_800DC954 = NULL;
s32 gMaxLights = 0;
s32 gNumActiveLights = 0;
unk800DC960 *D_800DC960 = NULL;
unk800DC964 *D_800DC964 = NULL;
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
        free_from_memory_pool(gActiveLights);
        gActiveLights = NULL;
        D_800DC954 = NULL;
        D_800DC960 = NULL;
        D_800DC964 = NULL;
    }
    gNumActiveLights = 0;
    gMaxLights = 0;
}

// Regalloc issues
#ifdef NON_MATCHING
/**
 * Official Name: setupLights
 */
void setup_lights(s32 count) {
    s32 i;
    s32 newCount;
    ObjectLight **temp_v0;

    free_lights();
    gMaxLights = count;
    temp_v0 = (ObjectLight **) allocate_from_main_pool_safe(gMaxLights * (sizeof(s32 *) + sizeof(ObjectLight) + sizeof(unk800DC960) + sizeof(unk800DC964)), COLOUR_TAG_MAGENTA);
    newCount = gMaxLights;
    gActiveLights = temp_v0;
    D_800DC954 = (ObjectLight *) &temp_v0[newCount];
    D_800DC960 = (unk800DC960 *) &D_800DC954[newCount];
    D_800DC964 = (unk800DC964 *) &D_800DC960[newCount];
    for (i = 0; i < gMaxLights; i++) {
        gActiveLights[i] = &D_800DC954[i];
    }
}
#else
GLOBAL_ASM("asm/non_matchings/lights/setup_lights.s")
#endif

GLOBAL_ASM("asm/non_matchings/lights/func_80031CAC.s")

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
        light->x = light->homeX;
        light->y = light->homeY;
        light->z = light->homeZ;
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
            for (i = 0; i < light->unk48 ; i++) { \
                light->unk4E += light->unk44[i].unk4; //Must be on one line!
            }
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
void lightUpdateLights(s32 arg0) {
    s32 i;
    for (i = 0; i < gNumActiveLights; i++) {
        func_80032424(gActiveLights[i], arg0);
    }
}

GLOBAL_ASM("asm/non_matchings/lights/func_80032424.s")

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
            case OBJECT_MODEL_TYPE_VEHICLE_PART: // Vehicle Part
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
            if ((entry->unk2 & sp64) && (entry->enabled == 1) && (sp82 >= entry->unk50) &&
                (entry->unk56 >= sp82) && (sp80 >= entry->unk52) && (entry->unk58 >= sp80) &&
                (sp7E >= entry->unk54) && (entry->unk5A >= sp7E)) {
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
                    gLightDiffX = entry->x - object->segment.trans.x_position;
                    gLightDiffY = entry->y - object->segment.trans.y_position;
                    gLightDiffZ = entry->z - object->segment.trans.z_position;
                    if (entry->unk0 == 2) {
                        gLightDiffY = 0.0f;
                    }
                    gLightDistance = (gLightDiffX * gLightDiffX) + (gLightDiffY * gLightDiffY) + (gLightDiffZ * gLightDiffZ);
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
                                    D_800DC964[D_800DC968].unk0 = gLightDiffX;
                                    D_800DC964[D_800DC968].unk4 = gLightDiffY;
                                    D_800DC964[D_800DC968].unk8 = gLightDiffZ;
                                }
                                D_800DC960[D_800DC968].unk0 = entry;
                                D_800DC960[D_800DC968].unk4 = entry->unk1C >> 0x10;
                                D_800DC960[D_800DC968].unk8 = entry->unk20 >> 0x10;
                                D_800DC960[D_800DC968].unkC = entry->unk24 >> 0x10;
                                D_800DC960[D_800DC968].unk10 = (u8)f20;
                                D_800DC968++;
                            }
                        }
                    }
                }
            }
        }

        if (object->segment.header->unk71 != 0) {
            if (D_800DC968 == 0) {
                object->unk54->unk7 = 0;
                object->unk54->unk11 = 0;
            } else if (D_800DC968 == 1) {
                object->unk54->unk4 = D_800DC960[0].unk4;
                object->unk54->unk5 = D_800DC960[0].unk8;
                object->unk54->unk6 = D_800DC960[0].unkC;
                object->unk54->unk7 = D_800DC960[0].unk10;
                object->unk54->unk11 = 0;
                object->unk54->unk8 = D_800DC964[0].unk0 * 8192.0f;
                object->unk54->unkA = D_800DC964[0].unk4 * 8192.0f;
                object->unk54->unkC = D_800DC964[0].unk8 * 8192.0f;
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
                object->unk54->unk4 = D_800DC960[phi_a0].unk4;
                object->unk54->unk5 = D_800DC960[phi_a0].unk8;
                object->unk54->unk6 = D_800DC960[phi_a0].unkC;
                object->unk54->unk7 = D_800DC960[phi_a0].unk10;
                object->unk54->unk8 = D_800DC964[phi_a0].unk0 * 8192.0f;
                object->unk54->unkA = D_800DC964[phi_a0].unk4 * 8192.0f;
                object->unk54->unkC = D_800DC964[phi_a0].unk8 * 8192.0f;
                object->unk54->unkE = D_800DC960[phi_a1].unk4;
                object->unk54->unkF = D_800DC960[phi_a1].unk8;
                object->unk54->unk10 = D_800DC960[phi_a1].unkC;
                object->unk54->unk11 = D_800DC960[phi_a1].unk10;
                object->unk54->unk12 = D_800DC964[phi_a1].unk0 * 8192.0f;
                object->unk54->unk14 = D_800DC964[phi_a1].unk4 * 8192.0f;
                object->unk54->unk16 = D_800DC964[phi_a1].unk8 * 8192.0f;
            }
        } else {
            if (D_800DC968 > 0) {
                if (D_800DC968 >= 2) {
                    func_800337E4();
                }
                object->unk54->unk4 = D_800DC960[0].unk4;
                object->unk54->unk5 = D_800DC960[0].unk8;
                object->unk54->unk6 = D_800DC960[0].unkC;
                object->unk54->unk7 = D_800DC960[0].unk10;
            } else {
                object->unk54->unk4 = 0xFF;
                object->unk54->unk5 = 0xFF;
                object->unk54->unk6 = 0xFF;
                object->unk54->unk7 = 0;
            }
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/lights/func_80032C7C.s")
#endif

#ifdef NON_EQUIVALENT
// Has regalloc issues
void func_800337E4(void) {
    s32 i;
    s32 temp;

    for (i = 1; i < D_800DC968; i++) {
        if (D_800DC960[i].unk10 >= 2) {
            if (D_800DC960[0].unk10 >= D_800DC960[i].unk10) {
                temp = (D_800DC960[i].unk10 << 0x10);
                temp /= D_800DC960[0].unk10;
                D_800DC960[0].unk4 = D_800DC960[0].unk4 + ((D_800DC960[i].unk4 * temp) >> 0x10);
                D_800DC960[0].unk8 = D_800DC960[0].unk8 + ((D_800DC960[i].unk8 * temp) >> 0x10);
                D_800DC960[0].unkC = D_800DC960[0].unkC + ((D_800DC960[i].unkC * temp) >> 0x10);
            } else {
                temp = (D_800DC960[0].unk10 << 0x10);
                temp /= D_800DC960[i].unk10;
                D_800DC960[0].unk4 = D_800DC960[i].unk4 + ((D_800DC960[0].unk4 * temp) >> 0x10);
                D_800DC960[0].unk8 = D_800DC960[i].unk8 + ((D_800DC960[0].unk8 * temp) >> 0x10);
                D_800DC960[0].unkC = D_800DC960[i].unkC + ((D_800DC960[0].unkC * temp) >> 0x10);
                D_800DC960[0].unk10 = D_800DC960[i].unk10;
            }
            if (D_800DC960[0].unk4 >= 0x100) {
                D_800DC960[0].unk4 = 0xFF;
            }
            if (D_800DC960[0].unk8 >= 0x100) {
                D_800DC960[0].unk8 = 0xFF;
            }
            if (D_800DC960[0].unkC >= 0x100) {
                D_800DC960[0].unkC = 0xFF;
            }
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/lights/func_800337E4.s")
#endif

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
        distance = (gLightDiffX * mag * light->unk7C) + (gLightDiffY * mag * light->unk80) + (gLightDiffZ * mag * light->unk84);
        if (distance < 0.0f) {
            distance = 0.0f;
        }
    } else {
        distance = 1.0f;
    }
    return distance;
}
