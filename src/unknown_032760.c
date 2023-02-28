/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80031B60 */

#include "unknown_032760.h"

#include "memory.h"
#include "types.h"
#include "macros.h"

/************ .data ************/

unk800DC950 **D_800DC950 = NULL;
unk800DC954 *D_800DC954 = NULL;
s32 D_800DC958 = 0;
s32 D_800DC95C = 0;
unk800DC960 *D_800DC960 = NULL;
unk800DC964 *D_800DC964 = NULL;
s32 D_800DC968 = 0; // Currently unknown, might be a different type.

/*******************************/

/************ .bss ************/

f32 D_8011D4C0;
f32 D_8011D4C4;
f32 D_8011D4C8;
f32 D_8011D4CC;

/*******************************/

void func_80031B60(void) {
    if (D_800DC950 != NULL) {
        free_from_memory_pool(D_800DC950);
        D_800DC950 = NULL;
        D_800DC954 = NULL;
        D_800DC960 = NULL;
        D_800DC964 = NULL;
    }
    D_800DC95C = 0;
    D_800DC958 = 0;
}

#ifdef NON_EQUIVALENT
// Regalloc issues
void func_80031BB8(s32 count) {
    s32 i;
    func_80031B60();
    D_800DC958 = count;
    D_800DC950 = allocate_from_main_pool_safe(D_800DC958 * (sizeof(s32 *) + sizeof(unk800DC954) + sizeof(unk800DC960) + sizeof(unk800DC964)), COLOUR_TAG_MAGENTA);
    D_800DC954 = &D_800DC950[D_800DC958];
    D_800DC960 = &D_800DC954[D_800DC958];
    D_800DC964 = &D_800DC960[D_800DC958];
    for (i = 0; i < D_800DC958; i++) {
        D_800DC950[i] = &D_800DC954[i].unk0;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80031BB8.s")
#endif

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80031CAC.s")

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80031F88.s")

void lightUpdateLights(s32 arg0) {
    s32 i;
    for (i = 0; i < D_800DC95C; i++) {
        func_80032424(D_800DC950[i], arg0);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80032424.s")

void func_80032BAC(unk800DC950 *arg0) {
    unk800DC950 *entry = NULL;
    s32 i;
    for (i = 0; (i < D_800DC95C) && (entry == NULL); i++) {
        if (arg0 == D_800DC950[i]) {
            entry = D_800DC950[i];
        }
    }
    if (entry != NULL) {
        D_800DC95C--;
        for (i--; i < D_800DC95C; i++) {
            D_800DC950[i] = D_800DC950[i + 1];
        }
        D_800DC950[D_800DC95C] = entry;
    }
}

s32 func_80032C6C(void) {
    return D_800DC95C;
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
    unk800DC950 *entry;

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
        for (i = 0; i < D_800DC95C; i++) {
            entry = D_800DC950[i];
            if ((entry->unk2 & sp64) && (entry->unk4 == 1) && (sp82 >= entry->unk50) &&
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
                    D_8011D4C4 = entry->unk10 - object->segment.trans.x_position;
                    D_8011D4C8 = entry->unk14 - object->segment.trans.y_position;
                    D_8011D4CC = entry->unk18 - object->segment.trans.z_position;
                    if (entry->unk0 == 2) {
                        D_8011D4C8 = 0.0f;
                    }
                    D_8011D4C0 = (D_8011D4C4 * D_8011D4C4) + (D_8011D4C8 * D_8011D4C8) + (D_8011D4CC * D_8011D4CC);
                    if (D_8011D4C0 < entry->unk68) {
                        if (entry->unk1 == 2) {
                            f20 = func_80033C08(entry);
                        } else {
                            f20 = 1.0f;
                        }
                        if (f20 > 0.0f) {
                            f20 *= func_80033A14(entry);
                            if (f20 > 0.0f) {
                                if (object->segment.header->unk71 != 0) {
                                    if (D_8011D4C0 > 0.0f) {
                                        temp = 1.0f / sqrtf(D_8011D4C0);
                                        D_8011D4C4 *= temp;
                                        D_8011D4C8 *= temp;
                                        D_8011D4CC *= temp;
                                    } else {
                                        D_8011D4C4 = 0.0f;
                                        D_8011D4C8 = 0.0f;
                                        D_8011D4CC = -1.0f;
                                    }
                                    D_800DC964[D_800DC968].unk0 = D_8011D4C4;
                                    D_800DC964[D_800DC968].unk4 = D_8011D4C8;
                                    D_800DC964[D_800DC968].unk8 = D_8011D4CC;
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
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80032C7C.s")
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
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_800337E4.s")
#endif

f32 func_80033A14(unk800DC950 *arg0) {
    f32 out;
    f32 temp;

    out = arg0->unk28 / 65536.0f;
    switch (arg0->unk3) {
        case 1:
            temp = 1.0f - ((D_8011D4C0) * (arg0->unk6C * arg0->unk6C));
            out *= temp;
            break;
        case 2:
            temp = 1.0f - sqrtf((D_8011D4C0) * (arg0->unk6C * arg0->unk6C));
            out *= temp;
            break;
        case 3:
            temp = coss_f((D_8011D4C0) * (arg0->unk6C * arg0->unk6C) * (16384.0f));
            out *= temp;
            break;
        case 4:
            temp = coss_f((D_8011D4C0) * (arg0->unk6C * arg0->unk6C) * (16384.0f));
            temp *= temp;
            out *= temp;
            break;
        case 5:
            temp = 1.0f - ((D_8011D4C0) * (arg0->unk6C * arg0->unk6C));
            temp *= temp;
            out *= temp;
            break;
    }
    return out;
}

f32 func_80033C08(unk800DC950 *arg0) {
    f32 temp_f2;
    f32 phi_f12;

    phi_f12 = D_8011D4C0;
    if (phi_f12 > 0.0f) {
        temp_f2 = 1.0f / sqrtf(phi_f12);
        phi_f12 = (D_8011D4C4 * temp_f2 * arg0->unk7C) + (D_8011D4C8 * temp_f2 * arg0->unk80) + (D_8011D4CC * temp_f2 * arg0->unk84);
        if (phi_f12 < 0.0f) {
            phi_f12 = 0.0f;
        }
    } else {
        phi_f12 = 1.0f;
    }
    return phi_f12;
}
