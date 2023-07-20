/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80004B40 */

#include "unknown_005740.h"

#include "types.h"
#include "macros.h"
#include "unknown_008C40.h"
#include "audiosfx.h"
#include "objects.h"
#include "controller.h"
#include "racer.h"
#include "PR/libaudio.h"
#include "game_ui.h"

/************ .data ************/

u8 D_800DC6D0 = 1;
s32 D_800DC6D4 = 0; // Currently unknown, might be a different type.
s32 D_800DC6D8 = 1; // Currently unknown, might be a different type.

/*******************************/

/************ .bss ************/

unk80119C38 *D_80119C30[2];
unk80119C38 *D_80119C38;
Object_Racer *D_80119C3C;
unk80115D18 *D_80119C40; // This should be in unknown_008C40?
unk80119C50 **D_80119C44;
unk80119C48 **D_80119C48; //0x24 struct size - 0x5A0 total size - should be 40 elements
u8 D_80119C4C;
unk80119C50 **D_80119C50;
s32 D_80119C54; //Padding?
unk80119C58 **D_80119C58; //Struct of size in func_8000A184 = 0x180 = 384 bytes
unk80119C58 **D_80119C5C; //Struct of size in func_8000A184 = 0x180 = 384 bytes Likely the same as above
f32 D_80119C60[670]; //array size of 672 looks to be required for func_80008174
unk8011A6D8 *D_8011A6D8; //unk8011A6D8[]
unk8011A6D8 **D_8011A6DC; // Struct of size 0xC0
f32 D_8011A6E0[334];
s32 D_8011AC18;
s32 D_8011AC1C;

/******************************/

#ifdef NON_EQUIVALENT
unk80119C38 *func_80004B40(s8 characterId, s8 vehicleId) {
    unk80119C38 *sp44;
    u32 *sp3C;
    f32 temp_f0;
    f32 temp_f18;
    f32 var_f10;
    f32 var_f16;
    f32 var_f16_2;
    f32 var_f18;
    u16 temp_a1;
    s32 temp_s1;
    s32 temp_s6;
    s32 temp_t7_2;
    u16 temp_v1;
    u16 var_a0_2;
    s32 var_a3;
    s32 var_a3_2;
    s32 var_s0_2;
    s32 var_v1_3;
    s8 var_s0;
    u16 *var_a2;
    u16 temp_a2;
    u16 temp_t8_2;
    u32 *temp_v0;
    u32 temp_v0_2;
    u32 var_s1;
    u32 var_s3;
    u32 var_t2;
    u32 var_t3;
    u32 var_t4;
    u8 temp_a3;
    u8 temp_t7;
    u8 temp_t8;
    u8 temp_t9;
    unk80119C38 **var_v0;
    unk80119C38 *temp_v0_3;
    unk80119C38 *var_ra;
    unk80119C38 *var_s2;
    unk80119C38 *var_s4;
    unk80119C38 *var_t1;
    unk80119C38 *var_t5;
    unk80119C38 *var_v1;
    void *var_a0;
    void *var_a1;
    void *var_v1_2;

    var_s0 = characterId;
    if (characterId >= 11) {
        var_s0 = 11;
    }
//     if (D_800DC6D8 != 0) {
//         var_v0 = D_80119C30;
//         do {
//             var_v0 += 4;
//             var_v0->unk-4 = 0;
//         } while (var_v0 != &D_80119C38);
//         D_800DC6D8 = 0;
//     }
//     temp_v0 = load_asset_section_from_rom(ASSET_AUDIO_TABLE);
//     temp_s6 = vehicleId * 10;
//     sp3C = temp_v0;
//     temp_s1 = temp_v0->unk1C + ((temp_s6 + var_s0) * 0x4C); //ALSynth?
//     temp_v0_2 = allocate_from_main_pool_safe(0x4C, COLOUR_TAG_CYAN);
//     load_asset_to_address(0x27U, temp_v0_2, temp_s1, 0x4C);
//     temp_v0_3 = allocate_from_main_pool_safe(sizeof(unk80119C38), COLOUR_TAG_CYAN);
//     sp44 = temp_v0_3;
//     var_v1 = temp_v0_3;
//     var_a3 = 0;
//     do {
//         var_a3 += 4;
//         var_v1->unk1 = 0;
//         var_v1->unk2 = 0;
//         var_v1->unk3 = 0;
//         var_v1 += 4;
//         var_v1->unk-4 = 0;
//     } while (var_a3 != 0xE0);
//     temp_v0_3->unk36 = temp_v0_2->unk36;
//     var_s0_2 = 0;
//     temp_v0_3->unk37 = temp_v0_2->unk37;
//     var_s1 = temp_v0_2;
//     temp_v0_3->unk38 = temp_v0_2->unk38;
//     var_t3 = temp_v0_2;
//     temp_v0_3->unk39 = temp_v0_2->unk39;
//     var_t4 = temp_v0_2;
//     temp_v0_3->unk64 = (u8) temp_v0_2->unk3A;
//     var_t5 = temp_v0_3;
//     var_ra = temp_v0_3;
//     var_t1 = temp_v0_3;
//     var_t2 = temp_v0_2;
//     var_s2 = temp_v0_3;
//     var_s3 = temp_v0_2;
//     var_s4 = temp_v0_3;
//     temp_v0_3->unkC8 = (f32) temp_v0_2->unk46 / 10000.0f;
//     temp_v0_3->unkB0 = (f32) temp_v0_2->unk3E / 10000.0f;
//     temp_v0_3->unkB4 = (f32) temp_v0_2->unk40 / 10000.0f;
//     temp_v0_3->unkC0 = (f32) temp_v0_2->unk42 / 10000.0f;
//     temp_v0_3->unkC4 = (f32) temp_v0_2->unk44 / 10000.0f;
//     temp_v0_3->unkBC = (f32) temp_v0_2->unk3C / 10000.0f;
//     temp_v0_3->unkB8 = temp_v0_2->unk3B;
//     temp_v0_3->unkD8 = 0;
//     temp_v0_3->unkCC = (f32) temp_v0_2->unk48 / 10000.0f;
//     do {
//         var_a3_2 = 1;
//         var_s4->unk0[0] = *var_s1;
//         var_v1_2 = var_t3 + 1;
//         var_t1->unk4[0] = var_t2->unk4;
//         var_a1 = var_t4 + 2;
//         var_s2->unk18[0] = var_s3->unk18;
//         var_a0 = var_t5 + 1;
//         var_t1->unkE[0] = var_t2->unkE;
//         var_a2 = &var_ra->unk0[1];
//         var_t1->unk2C[0] = var_t2->unk2C;
// loop_10:
//         var_a3_2 += 2;
//         var_a0->unk4 = (u8) var_v1_2->unk4;
//         var_v1_2 += 2;
//         var_a2->unk18 = (u16) var_a1->unk18;
//         var_a1 += 4;
//         var_a0->unkE = (u8) var_v1_2->unkC;
//         var_a0 += 2;
//         var_a0->unk2A = (u8) var_v1_2->unk2A;
//         var_a2 += 4;
//         var_a0->unk3 = (u8) var_v1_2->unk3;
//         var_a2->unk16 = (u16) var_a1->unk16;
//         var_a0->unkD = (u8) var_v1_2->unkD;
//         var_a0->unk2B = (u8) var_v1_2->unk2B;
//         if (var_a3_2 != 5) {
//             goto loop_10;
//         }
//         var_s0_2 += 2;
//         var_s1 += 2;
//         var_t3 += 5;
//         var_t4 += 0xA;
//         var_t5 += 5;
//         var_ra += 0xA;
//         var_t1 += 5;
//         var_t2 += 5;
//         var_s2 += 0xA;
//         var_s3 += 0xA;
//         var_s4 += 2;
//     } while (var_s0_2 < 4);
//     temp_v0_3->unk74 = 0;
//     temp_v0_3->unk6C[0] = 0.0f;
//     temp_v0_3->unkD4 = temp_v0_2->unk4A / 100.0f;
    if (temp_s6 == 0) {
        temp_v0_3->unk54[0] = temp_v0_3->unk2C[0];
        temp_v0_3->unk5C[0] = (f32) temp_v0_3->unk18[0] / 10000.0f;
        temp_v0_3->unk54[1] = temp_v0_3->unk31;
        temp_v0_3->unk5C[1] = (f32) temp_v0_3->unk22 / 10000.0f;
    } else {
        temp_f0 = temp_v0_3->unkD4;
        temp_f18 = temp_f0 * 10000.0f;
        temp_v0_3->unk5C[0] = temp_f0;
        temp_a1 = temp_f18;
        var_a0_2 = 0;
        if (temp_a1 >= (s32) temp_v0_3->unk18[0]) {
loop_26:
            temp_t7_2 = (var_a0_2 + 1) & 0xFFFF;
            temp_t8_2 = temp_v0_3->unk18[temp_t7_2];
            var_a0_2 = temp_t7_2;
            if (temp_a1 >= (s32) temp_t8_2) {
                if (temp_t7_2 < 4) {
                    goto loop_26;
                }
            }
        }
        var_a0_2--;
        temp_v0_3->unk54[0] = ((f32) (temp_v0_3->unk2C[var_a0_2 + 1] - temp_v0_3->unk2C[var_a0_2]) * ((f32) (temp_a1 - temp_v0_3->unk18[var_a0_2]) / (f32) (temp_v0_3->unk18[var_a0_2 + 1] - temp_v0_3->unk18[var_a0_2]))) + temp_v0_3->unk2C[var_a0_2];
    }
    free_from_memory_pool(sp3C);
    free_from_memory_pool((void *) temp_v0_2);
    return sp44;
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80004B40.s")
#endif

void func_800050D0(Object *obj, u32 buttonsPressed, u32 buttonsHeld, s32 updateRate) {
    if ((D_800DC6D0 != 0)) {
        D_80119C3C = &obj->unk64->racer;
        D_80119C38 = (unk80119C38 *) D_80119C3C->unk118;
        if (D_80119C38 != NULL) {
            if (func_8001139C()) {
                if (D_80119C3C->playerIndex != PLAYER_COMPUTER) {
                    buttonsHeld = get_buttons_held_from_player(D_80119C3C->playerIndex);
                    buttonsPressed = get_buttons_pressed_from_player(D_80119C3C->playerIndex);
                }
            }
            if (D_80119C38->unk0[0] == 0) {
                D_80119C38->unk78 = -32000.0f;
                D_80119C38->unk7C = -32000.0f;
                D_80119C38->unk80 = -32000.0f;
            } else {
                D_80119C38->unk78 = obj->segment.trans.x_position;
                D_80119C38->unk7C = obj->segment.trans.y_position;
                D_80119C38->unk80 = obj->segment.trans.z_position;
                switch (D_80119C3C->vehicleIDPrev) {
                    case 1:
                        func_80005D08(obj, buttonsPressed, buttonsHeld, updateRate);
                        break;
                    case 2:
                        func_800063EC(obj, buttonsPressed, buttonsHeld, updateRate);
                        break;
                    default:
                        func_80005254(obj, buttonsPressed, buttonsHeld, updateRate);
                        break;
                }
            }
        }
    }
}

#ifdef NON_EQUIVALENT
void func_80005254(Object *obj, u32 buttonsPressed, u32 buttonsHeld, s32 updateRate) {
    f32 sp6C;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    u8 temp_f4;
    f32 var_f0;
    f32 var_f12;
    f32 var_f14;
    f32 var_f20;
    f32 var_f2;
    s32 temp_a0_4;
    s32 var_s0;
    s32 outerLoop;
    s32 innerLoop;
    s32 var_v1_3;

    if (D_80119C3C->unk1FB != 0) {
        var_f0 = 12.0f;
    } else {
        var_f0 = D_80119C3C->velocity;
    }
    if (var_f0 < 0.0f) {
        var_f0 = -var_f0;
    }
    var_s0 = (var_f0 / 16) * 100;
    var_s0 += 5;
    if (var_s0 > 100) {
        var_s0 = 100;
    }
    for (outerLoop = 0; outerLoop < 1; outerLoop++) {
        if ((D_80119C38->unk0[outerLoop]) != 0) {
            innerLoop = 0;
            while ((var_s0 < D_80119C38->unkE[innerLoop] || var_s0 > D_80119C38->unkE[innerLoop + 1]) && innerLoop < 4) {
                innerLoop++;
            }
            
            temp_f14 = (var_s0 - D_80119C38->unkE[innerLoop]) / ((f32) (D_80119C38->unkE[innerLoop + 1] - D_80119C38->unkE[innerLoop]));
            temp_f4 = D_80119C38->unk2C[innerLoop] + (D_80119C38->unk2C[innerLoop + 1] - D_80119C38->unk2C[innerLoop]) * temp_f14;
            
            innerLoop = 0;
            while ((var_s0 < D_80119C38->unk4[innerLoop] || var_s0 > D_80119C38->unk4[innerLoop + 1]) && innerLoop < 4) {
                innerLoop++;
            }
            
            temp_f14 = (var_s0 - D_80119C38->unk4[innerLoop]) / ((f32) (D_80119C38->unk4[innerLoop + 1] - D_80119C38->unk4[innerLoop]));
            temp_f16 = D_80119C38->unk18[innerLoop] / 10000.0f;
            temp_f18 = D_80119C38->unk18[innerLoop + 1] / 10000.0f;
            if (var_s0 > 50 && D_80119C3C->bananas != 0) {
                if (D_80119C3C->bananas <= 10) {
                    var_v1_3 = D_80119C3C->bananas;
                } else {                    
                    var_v1_3 = 10;
                }
                if (D_80119C38->unk3C < (0.05 * var_v1_3)) {
                    D_80119C38->unk3C += ((0.05 * var_v1_3) / (var_v1_3 * 64));
                } else if (D_80119C38->unk3C > (0.05 * var_v1_3)) {
                    D_80119C38->unk3C = (0.05 * var_v1_3);
                }
                var_f2 = ((temp_f18 - temp_f16) * temp_f14) + temp_f16 + D_80119C38->unk3C;
            } else {
                D_80119C38->unk3C *= 0.95;
                var_f2 = ((temp_f18 - temp_f16) * temp_f14) + temp_f16 + D_80119C38->unk3C;
            }
            if (D_80119C3C->drift_direction != 0) {
                D_80119C38->unk40 += ((0.13 - D_80119C38->unk40) / 8);
            } else {
                D_80119C38->unk40 /= 4;
            }
            var_f2 += D_80119C38->unk40;
            if ((D_80119C3C->groundedWheels == 0) && (D_80119C3C->playerIndex != PLAYER_COMPUTER)) {
                var_f2 += 0.3;
            }
            var_f12 = (var_f2 - D_80119C38->unk5C[outerLoop]) / 2;
            var_f14 = (temp_f4 - D_80119C38->unk54[outerLoop]) / 2;
            if (D_80119C3C->playerIndex != PLAYER_COMPUTER) {
                if (get_random_number_from_range(0, 10) < 7) {
                    D_80119C38->unk90 = (D_80119C38->unk90 + get_random_number_from_range(0, 10)) - 5;
                    if (D_80119C38->unk90 > 5) {
                        D_80119C38->unk90 = 5;
                    } else if (D_80119C38->unk90 < -5) {
                        D_80119C38->unk90 = -5;
                    }
                }
                var_f12 += 0.02 * (D_80119C38->unk90 / 5.0f);
                var_f14 += 5.0f * (D_80119C38->unk90 / 5.0f);
            }
            if ((buttonsHeld & A_BUTTON) && (D_80119C38->unk94 < 0.4)) {
                D_80119C38->unk94 += ((f32) updateRate * 0.01);
                if (D_80119C38->unk94 > 0.4) {
                    D_80119C38->unk94 = 0.4f;
                }
            }
            if (!(buttonsHeld & A_BUTTON) && (D_80119C38->unk94 > 0.0f)) {
                D_80119C38->unk94 -= ((f32) updateRate * 0.005);
                if (D_80119C38->unk94 < 0.0f) {
                    D_80119C38->unk94 = 0.0f;
                }
            }
            D_80119C38->unk5C[outerLoop] += var_f12;
            if (buttonsHeld & A_BUTTON) {
                D_80119C38->unk54[outerLoop] += var_f14;
            } else {
                D_80119C38->unk54[outerLoop] = 35.0f;
            }
        }
    }
    if (((D_80119C3C->unk10 != 0) || (D_80119C3C->unk14 != 0) || 
        !(buttonsHeld & B_BUTTON) || (D_80119C3C->velocity > -0.1) || 
        (D_80119C3C->vehicleID == 4)) && (D_80119C38->unkA8 != 0)
    ) {
            func_8000488C(D_80119C38->unkA8);
            D_80119C38->unkA8 = 0;
    } else if ((buttonsPressed & B_BUTTON) && (D_80119C38->unkA8 == 0) && (D_80119C3C->playerIndex >= 0)) {
        if (D_80119C3C->velocity < 0.0f) {
            var_f20 = -D_80119C3C->velocity;
        } else {
            var_f20 = D_80119C3C->velocity;
        }
        if (var_f20 > 12.0f) {
            var_f20 = 12.0f;
        }
        func_80001F14(25, &D_80119C38->unkA8);
        sp6C = (((var_f20 * 0.5) / 12.0) + 0.5);
        temp_a0_4 = D_80119C38->unkA8;
        if (temp_a0_4 != 0) {
            func_800049F8(temp_a0_4, 16, *((u32*) &sp6C));
        }
        D_80119C38->unkAC = 110;
        D_80119C38->unkD0 = 0;
    }
    if (D_80119C38->unkA8 != 0) {
        if (D_80119C3C->groundedWheels == 0) {
            D_80119C38->unkD0 += updateRate;
        } else {
            D_80119C38->unkD0 = 0;
        }
        if (D_80119C38->unkD0 >= 10) {
            func_800049F8(D_80119C38->unkA8, 8, 0);
        } else {
            func_800049F8(D_80119C38->unkA8, 8, D_80119C38->unkAC << 8);
            func_80009B7C((s32 *) D_80119C38->unkA8, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
        }
    }
    D_80119C38->unkA0 = var_s0;
    if ((buttonsHeld & A_BUTTON) != 0) {
        D_80119C38->unk98 = D_80119C38->unk54[0];
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80005254.s")
#endif

void func_80005D08(Object *arg0, UNUSED u32 buttonsPressed, u32 buttonsHeld, s32 updateRate) {
    UNUSED s32 pad;
    f32 var_f16;
    f32 new_var;
    u16 temp_f10;
    f32 var_f2;
    f32 var_f18;
    f32 var_f14;
    f32 temp_f14;
    s32 var_v0;
    s32 var_a1;
    u8 var_t0;
    u8 i;

    if (func_8001139C() == 0) {
        temp_f14 = arg0->segment.x_velocity;
        var_f2 = arg0->segment.z_velocity;
        var_f16 = sqrtf((temp_f14 * temp_f14) + (var_f2 * var_f2));
    } else {
        var_f16 = 0.0f;
    }
    var_f14 = D_80119C38->unkD4;
    if (buttonsHeld & A_BUTTON) {
        D_80119C38->unkA4 += D_80119C38->unkB0 * (f32) updateRate;
        if (D_80119C38->unkC8 < D_80119C38->unkA4) {
            D_80119C38->unkA4 = D_80119C38->unkC8;
        }
    } else {
        D_80119C38->unkA4 -= D_80119C38->unkB4 * (f32) updateRate;
    }
    if (D_80119C38->unkA4 < 0.0f) {
        D_80119C38->unkA4 = 0.0f;
    }
    var_v0 = (-D_80119C3C->unk196 - (D_80119C3C->steerVisualRotation & 0xFFFF)) + 0x8000;
    if (var_v0 > 0x8000) {
        var_v0 -= 0xFFFF;
    }
    if (var_v0 < -0x8000) {
        var_v0 += 0xFFFF;
    }
    var_f2 = sins_f(var_v0);
    if (var_f2 < 0.0f) {
        var_f2 = -var_f2;
    }
    if (check_if_showing_cutscene_camera() == 0 && func_8001139C() == 0) {
        var_f18 = ((D_80119C38->unkBC * var_f2 * var_f16) / 15.0);
    } else {
        var_f18 = 0.0f;
    }
    if (func_800A0190() == FALSE) {
        D_80119C38->unkA4 = 0.0f;
    }
    if (var_f16 > 10.0) {
        var_f16 -= 10.0;
    } else {
        var_f16 = 0.0f;
    }
    if (var_f16 != 0.0 && D_80119C3C->bananas != 0) {
        if (D_80119C3C->bananas <= 10) {
            var_a1 = D_80119C3C->bananas;
        } else {
            var_a1 = 10;
        }
        if (D_80119C38->unk3C < (0.05 * var_a1)) {
            D_80119C38->unk3C += ((0.05 * var_a1) / (var_a1 * 64));
        } else if (D_80119C38->unk3C > (0.05 * var_a1)) {
            D_80119C38->unk3C = (0.05 * var_a1);
        }
        var_f14 += D_80119C38->unk3C;
    } else {
        D_80119C38->unk3C *= 0.95;
        var_f14 += D_80119C38->unk3C;
    }
    var_f14 += ((var_f16 * D_80119C38->unkCC) + var_f18 + D_80119C38->unkA4);
    if ((D_80119C3C->playerIndex != -1) && (D_80119C3C->groundedWheels == 0) && (D_80119C3C->waterTimer < 4)) {
        if (func_8001139C() == 0) {
            var_f14 += 0.3;
        }
    }
    D_80119C38->unk5C[0] += ((var_f14 - D_80119C38->unk5C[0]) / 8);
    if (D_80119C38->unk5C[0] > (0x7FFF / 5000.0)) {
        D_80119C38->unk5C[0] = (0x7FFF / 5000.0); //6.5534
    }
    temp_f10 = D_80119C38->unk5C[0] * 10000.0f;
    for (i = 0; temp_f10 >= D_80119C38->unk18[i] && i < 4; i++) { }
    if (i == 4) {
        var_t0 = D_80119C38->unk2C[i];
    } else {
        if (i != 0) {
            i--;
        }
        new_var = (temp_f10 - D_80119C38->unk18[i]) / ((f32) (D_80119C38->unk18[i + 1] - D_80119C38->unk18[i]));
        var_t0 = D_80119C38->unk2C[i] + (D_80119C38->unk2C[i + 1] - D_80119C38->unk2C[i]) * new_var;
    }
    D_80119C38->unk54[0] += ((var_t0 - D_80119C38->unk54[0]) / 8);
    D_80119C38->unk5C[1] = 1.0f;
    D_80119C38->unk54[1] = 0.0f;
}

#ifdef NON_EQUIVALENT
void func_800063EC(Object *obj, UNUSED u32 buttonsPressed, u32 buttonsHeld, s32 updateRate) {
    f32 sp28;
    f32 var_f2;    
    u16 temp_f10;
    f32 var_f14;
    f32 temp_f8;
    f32 var_f18;
    u8 i;
    s32 var_a0;
    u8 var_t0;
    f32 xVel;
    f32 yVel;
    f32 zVel;

    if (func_8001139C() == 0) {
        xVel = obj->segment.x_velocity;
        zVel = obj->segment.z_velocity;
        yVel = obj->segment.y_velocity;
        var_f18 = sqrtf((xVel * xVel) + (zVel * zVel) + (yVel * yVel));
        //var_f18 = sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) + (obj->segment.z_velocity * obj->segment.z_velocity) + (obj->segment.y_velocity * obj->segment.y_velocity));
    } else {
        var_f18 = 0.0f;
    }
    if (var_f18 < 2.0f) {
        D_80119C38->unk54[0] += ((D_80119C38->unk37 - D_80119C38->unk54[0]) / 8);
    } else {
        temp_f10 = D_80119C38->unk5C[0] * 10000.0f;
        for (i = 0; temp_f10 >= D_80119C38->unk18[i] && i < 4; i++) { }
        if (i == 4) {
            var_t0 = D_80119C38->unk2C[i];
        } else {
            if (i != 0) {
                i--;
            }
            temp_f8 = (temp_f10 - D_80119C38->unk18[i]) / ((f32) (D_80119C38->unk18[i + 1] - D_80119C38->unk18[i]));
            var_t0 = D_80119C38->unk2C[i] + (D_80119C38->unk2C[i + 1] - D_80119C38->unk2C[i]) * temp_f8;
        }
        D_80119C38->unk54[0] += ((var_t0 - D_80119C38->unk54[0]) / 8);
    }
    var_f14 = D_80119C38->unkD4;
    if (buttonsHeld & A_BUTTON) {
        D_80119C38->unkA4 += D_80119C38->unkB0 * (f32) updateRate;
        if (D_80119C38->unkC8 < D_80119C38->unkA4) {
            D_80119C38->unkA4 = D_80119C38->unkC8;
        }
    } else {
        D_80119C38->unkA4 -= D_80119C38->unkB4 * (f32) updateRate;
    }
    if (D_80119C38->unkA4 < 0) {
        D_80119C38->unkA4 = 0;
    }
    if (func_800A0190() == 0) {
        D_80119C38->unkA4 = 0.0f;
    }
    var_f14 += D_80119C38->unkA4;
    sp28 = sins_f(obj->segment.trans.x_rotation);
    var_f2 = sins_f(obj->segment.trans.z_rotation) * D_80119C38->unkC0;
    if (var_f2 < 0.0f) {
        var_f2 = -var_f2;
    }
    if (var_f18 > 10.0) {
        var_f18 -= 10.0;
    } else {
        var_f18 = 0.0;
    }
    var_f14 += ((D_80119C38->unkC4 * sp28) + var_f2);
    var_f14 += (var_f18 * D_80119C38->unkCC);
    if ((var_f18 != 0.0) && (D_80119C3C->bananas != 0)) {
        if (D_80119C3C->bananas <= 10) {
            var_a0 = D_80119C3C->bananas;
        } else {
            var_a0 = 10;
        }
        if (D_80119C38->unk3C < (0.05 * var_a0)) {
            D_80119C38->unk3C += ((0.05 * var_a0) / (var_a0 * 64));
        } else if (D_80119C38->unk3C > (0.05 * var_a0)) {
            D_80119C38->unk3C = (0.05 * var_a0);
        }
        var_f14 += D_80119C38->unk3C;
    } else {
        D_80119C38->unk3C *= 0.95;
        var_f14 += D_80119C38->unk3C;
    }
    D_80119C38->unk5C[0] += ((var_f14 - D_80119C38->unk5C[0]) / 8);
    if (D_80119C38->unk5C[0] > (0x7FFF / 5000.0)) {
        D_80119C38->unk5C[0] = (0x7FFF / 5000.0); //6.5534
    }
    D_80119C38->unk5C[1] = 1.0f;
    D_80119C38->unk54[1] = 0.0f;
    if ((D_80119C3C->playerIndex != PLAYER_COMPUTER) && (D_80119C3C->spinout_timer != 0) && !D_80119C38->unkD8) {
        D_80119C38->unkD8 = TRUE;
        play_sound_global(SOUND_UNK_13D, &D_80119C38->unkDC);
    } else if (D_80119C3C->spinout_timer == 0) {
        D_80119C38->unkD8 = FALSE;
        if (D_80119C38->unkDC != NULL) {
            func_8000488C(D_80119C38->unkDC);
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800063EC.s")
#endif

void func_80006AC8(Object *obj) {
    s32 i;

    D_80119C38 = (unk80119C38 *) obj->unk64->racer.unk118;
    if (D_80119C38 != NULL) {
        for (i = 0; i != 2; i++) {
            if (D_80119C38->unk48[i] != NULL) {
                func_8000488C(D_80119C38->unk48[i]);
                D_80119C38->unk48[i] = 0;
            }
        }
        if (D_80119C38->unk50 != NULL) {
            func_8000488C(D_80119C38->unk50);
            D_80119C38->unk50 = NULL;
        }
        if (D_80119C38->unkA8 != NULL) {
            func_8000488C(D_80119C38->unkA8);
            D_80119C38->unkA8 = 0;
        }
        for (i = 0; i < ARRAY_COUNT(D_80119C30); i++) {
            if (D_80119C30[i] == D_80119C38) {
                D_80119C30[i] = NULL;
            }
        }
        free_from_memory_pool(D_80119C38);
        obj->unk64->racer.unk118 = NULL;
    }
}

void func_80006BFC(Object *obj, ObjectSegment *segment, Object *obj2, s32 updateRate) {
    Object_Racer *racer;
    f32 velocity;
    f32 xPos;
    f32 yPos;
    f32 zPos;
    f32 new_xPos;
    f32 new_zPos;
    f32 new_yPos;
    f32 var_f2_2;
    f32 posSquared;
    f32 sp1C;
    Object_Racer *racer2;
    s32 new_var;

    racer = &obj->unk64->racer;
    racer2 = &obj2->unk64->racer;
    D_80119C38 = (unk80119C38 *) racer2->unk118;
    if (D_80119C38 != NULL) {
        if (segment != NULL) {
            xPos = segment[racer->playerIndex].trans.x_position;
            yPos = segment[racer->playerIndex].trans.y_position;
            zPos = segment[racer->playerIndex].trans.z_position;
            sp1C = 1.0f;
        } else {
            xPos = obj->segment.trans.x_position;
            yPos = obj->segment.trans.y_position;
            zPos = obj->segment.trans.z_position;
            switch (racer->vehicleID) {
                case VEHICLE_CAR:
                    if (racer->velocity >= 0.0f) {
                        velocity = racer->velocity;
                    } else {
                        velocity = -racer->velocity;
                    }
                    break;
                case VEHICLE_HOVERCRAFT:
                    velocity = sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) + (obj->segment.z_velocity * obj->segment.z_velocity));
                    break;
                default:
                    velocity = sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) + (obj->segment.z_velocity * obj->segment.z_velocity) + (obj->segment.y_velocity * obj->segment.y_velocity));
                    break;
            }
            if (velocity > 15.0f) {
                velocity = 15.0f;
            }
            sp1C = 1.0f - (velocity / 15.0f);
        }
        new_xPos = obj2->segment.trans.x_position - xPos;
        new_yPos = obj2->segment.trans.y_position - yPos;
        new_zPos = obj2->segment.trans.z_position - zPos;
        posSquared = sqrtf(((new_xPos * new_xPos) + (new_yPos * new_yPos)) + (new_zPos * new_zPos));
        var_f2_2 = (D_80119C38->unk6C[racer->playerIndex] - posSquared) / updateRate;
        if (var_f2_2 > 15.0f) {
            var_f2_2 = 15.0f;
        } else if (var_f2_2 < -15.0f) {
            var_f2_2 = -15.0f;
        }
        new_var = func_80007FA4(D_80119C38->unk5C[0]) * 1731.23404;
        D_80119C38->unk68 += (((alCents2Ratio((((70.0f + var_f2_2) / (70.0f - var_f2_2)) * new_var)) - D_80119C38->unk5C[0]) - D_80119C38->unk68) / 2);
        D_80119C38->unk68 *= sp1C;
        if (D_80119C38->unk68 > 0.8) {
            D_80119C38->unk68 = 0.8;
        } else if (D_80119C38->unk68 < -0.8) {
            D_80119C38->unk68 = -0.8;
        }
        D_80119C38->unk6C[racer->playerIndex] = posSquared;
    }
}

#ifdef NON_EQUIVALENT
//https://decomp.me/scratch/utYpK
void func_80006FC8(Object **objs, s32 numRacers, ObjectSegment *segment, u8 arg3, s32 updateRate) {
    f32 tempxPos;
    f32 tempyPos;
    f32 tempzPos;
    Object_Racer *racer;
    f32 temp_f20_2;
    s32 loopCount2;
    s32 loopCount1;
    f32 temp_f0_3;
    f32 var_f26;
    u8 temp_s3;
    s32 curVal;
    s32 loopCount3;
    s32 maxVal;
    s32 curIndex;
    f32 sp8C;
    s32 pad;
    unk80119C38 *temp;

    for (loopCount1 = 0; loopCount1 < arg3; loopCount1++) {
        racer = &objs[loopCount1]->unk64->racer;
        if (racer != NULL) {
            D_80119C38 = (unk80119C38 *) racer->unk118;
        } else {
            D_80119C38 = NULL;
        }
        
        if (D_80119C38 != NULL && D_80119C38->unk0[0] != 0) {
            if (racer->raceFinished || check_if_showing_cutscene_camera()) {
                tempxPos = objs[loopCount1]->segment.trans.x_position - segment[loopCount1].trans.x_position;
                tempyPos = objs[loopCount1]->segment.trans.y_position - segment[loopCount1].trans.y_position;
                tempzPos = objs[loopCount1]->segment.trans.z_position - segment[loopCount1].trans.z_position;
                func_80006BFC(objs[loopCount1], segment, objs[loopCount1], updateRate);
                D_80119C38->unk84 = sqrtf((tempxPos * tempxPos) + (tempyPos * tempyPos) + (tempzPos * tempzPos));
                if (D_80119C38->unk84 < 1500.0f) {
                    var_f26 = 2250000.0f; //(1500.0f * 1500.0f)
                    var_f26 = (var_f26 - (D_80119C38->unk84 * D_80119C38->unk84)) / var_f26;
                    var_f26 *= var_f26;
                    D_80119C38->unk91[0] = func_800090C0(tempxPos, tempzPos, segment[loopCount1].trans.y_rotation);
                } else {
                    var_f26 = 0.0f;
                }
                if (racer->raceFinished == 0) {
                    var_f26 *= 0.5;
                }
            } else {
                var_f26 = 1.0f;
                D_80119C38->unk91[0] = 64;
                D_80119C38->unk68 = 0.0f;
            }
            if ((D_80119C38->unkA0 < 70) && (D_80119C38->unk36) && (arg3 < 3) && (var_f26 != 0.0) && !(D_80119C38->unk44[0] & 1)) {
                temp_f20_2 = D_80119C38->unkA0 / 70.0f;
                temp_s3 = (D_80119C38->unk37 - (D_80119C38->unk37 * temp_f20_2)) * var_f26;
                if (temp_s3 >= 16) {
                    if (D_80119C38->unk50 == NULL) {
                        func_80001F14(D_80119C38->unk36, (s32 *) &D_80119C38->unk50);
                    }
                    temp_f0_3 = D_80119C38->unk38 / 100.0f;
                    sp8C = temp_f0_3 + ((((f32) D_80119C38->unk39 / 100.0f) - temp_f0_3) * temp_f20_2);
                    if (D_80119C38->unk50 != NULL) {
                        func_80009B7C((s32 *) D_80119C38->unk50, objs[loopCount1]->segment.trans.x_position, objs[loopCount1]->segment.trans.y_position, objs[loopCount1]->segment.trans.z_position);
                        func_800049F8(D_80119C38->unk50, 8, temp_s3 << 8);
                        func_800049F8(D_80119C38->unk50, 16, *((u32*) &sp8C));
                        func_80004604(D_80119C38->unk50, 80);
                        func_800049F8(D_80119C38->unk50, 4, D_80119C38->unk91[0]);
                    }
                } else if (D_80119C38->unk50 != NULL) {
                    func_8000488C(D_80119C38->unk50);
                    D_80119C38->unk50 = 0;
                }
            } else if (D_80119C38->unk50 != NULL) {
                func_8000488C(D_80119C38->unk50);
                D_80119C38->unk50 = 0;
            }
            for (loopCount2 = 0; loopCount2 < 2 && D_80119C38->unk0[loopCount2] != 0 && var_f26 != 0.0; loopCount2++) {
                temp_s3 =  D_80119C38->unk54[loopCount2] * var_f26;
                sp8C = D_80119C38->unk5C[loopCount2] + D_80119C38->unk3C + D_80119C38->unk94 + D_80119C38->unk68;
                if (sp8C < 0.05) {
                    sp8C = 0.05f;
                }
                if ((loopCount2 == 0) && (D_80119C38->unk44[0] & 1)) {
                    if (D_80119C38->unk48[0] != NULL) {
                        func_8000488C(D_80119C38->unk48[0]);
                        D_80119C38->unk48[0] = NULL;
                    }
                } else {
                    if ((D_80119C38->unk48[loopCount2] != NULL) && (temp_s3 == 0)) {
                        func_8000488C(D_80119C38->unk48[loopCount2]);
                        D_80119C38->unk48[loopCount2] = NULL;
                    } else {
                        if (D_80119C38->unk48[loopCount2] == NULL) {
                            func_80001F14(D_80119C38->unk0[loopCount2], (s32 *) &D_80119C38->unk48[loopCount2]);
                        }
                        if (D_80119C38->unk48[loopCount2] != NULL) {
                            func_80009B7C((s32 *) D_80119C38->unk48[loopCount2], objs[loopCount1]->segment.trans.x_position, objs[loopCount1]->segment.trans.y_position, objs[loopCount1]->segment.trans.z_position);
                            func_800049F8(D_80119C38->unk48[loopCount2], 8, temp_s3 << 8);
                            func_800049F8(D_80119C38->unk48[loopCount2], 16, *((u32*) &sp8C));
                            func_80004604(D_80119C38->unk48[loopCount2], 80);
                            if (arg3 != 1) {
                                D_80119C38->unk91[0] = 64;
                            }
                            func_800049F8(D_80119C38->unk48[loopCount2], 4, D_80119C38->unk91[0]);
                        }
                    }
                }
            }
        }
    }
    if (arg3 < 3) {
        for (loopCount2 = arg3; loopCount2 < numRacers; loopCount2++) {
            racer = &objs[loopCount2]->unk64->racer;
            if (racer != NULL) {
                D_80119C38 = (unk80119C38 *) racer->unk118;
                if (D_80119C38 != NULL) {
                    D_80119C38->unk88 = 0;
                }
            }
        }
        for (loopCount1 = 0; loopCount1 < arg3; loopCount1++) {
            racer = &objs[loopCount1]->unk64->racer;
            for (loopCount2 = arg3; loopCount2 < numRacers; loopCount2++) {
                if (objs[loopCount2]->unk64 != NULL) {
                    D_80119C38 = (unk80119C38 *) objs[loopCount2]->unk64->racer.unk118;
                    if (D_80119C38 != 0) {
                        if (racer->raceFinished != 0) {              
                            tempxPos = objs[loopCount2]->segment.trans.x_position - segment[loopCount1].trans.x_position;       
                            tempyPos = objs[loopCount2]->segment.trans.y_position - segment[loopCount1].trans.y_position;     
                            tempzPos = objs[loopCount2]->segment.trans.z_position - segment[loopCount1].trans.z_position;
                        } else {
                            tempxPos = objs[loopCount2]->segment.trans.x_position - objs[loopCount1]->segment.trans.x_position;
                            tempyPos = objs[loopCount2]->segment.trans.y_position - objs[loopCount1]->segment.trans.y_position;
                            tempzPos = objs[loopCount2]->segment.trans.z_position - objs[loopCount1]->segment.trans.z_position;
                        }
                        D_80119C38->unk84 = sqrtf((tempxPos * tempxPos) + (tempyPos * tempyPos) + (tempzPos * tempzPos));
                        if (D_80119C38->unk84 < 1500.0f) {
                            var_f26 = 2250000.0f; //(1500.0f * 1500.0f)
                            var_f26 = (var_f26 - (D_80119C38->unk84 * D_80119C38->unk84)) / var_f26;
                            temp_s3 = D_80119C38->unk54[0] * var_f26;
                            if (temp_s3 > 127) {
                                temp_s3 = 127;
                            }
                            temp_s3 *= 0.8;
                            if (D_80119C38->unk88 < temp_s3) {
                                D_80119C38->unk88 = temp_s3;
                                D_80119C38->unk91[0] = func_800090C0(tempxPos, tempzPos, segment->trans.y_rotation);
                                if (racer->raceFinished != 0) {
                                    func_80006BFC(objs[loopCount1], segment, objs[loopCount2], updateRate);
                                } else {
                                    func_80006BFC(objs[loopCount1], NULL, objs[loopCount2], updateRate);
                                }
                                D_80119C38->unk8C = D_80119C38->unk5C[0] + D_80119C38->unk68;
                                if (D_80119C38->unk8C < 0.05) {
                                    D_80119C38->unk8C = 0.05f;
                                }
                            }
                        }
                    }
                }
            }
        }
        for (loopCount3 = 0; loopCount3 < ARRAY_COUNT(D_80119C30); loopCount3++) {
            if (D_80119C30[loopCount3] != NULL) {
                if (D_80119C30[loopCount3]->unk48[0] != NULL && D_80119C30[loopCount3]->unk88 < 8) {
                    func_8000488C(D_80119C30[loopCount3]->unk48[0]);
                    D_80119C30[loopCount3]->unk48[0] = NULL;
                    D_80119C30[loopCount3]->unk74 = 0;
                    D_80119C30[loopCount3] = NULL;
                }
            }
        }
        if (updateRate < D_800DC6D4) {
            D_800DC6D4 -= updateRate;
        } else {
            D_800DC6D4 = 0;
        }
        for (loopCount1 = 1; loopCount1 < numRacers; loopCount1++) {
            racer = &objs[loopCount1]->unk64->racer;
            if (objs[loopCount1]->unk64 != NULL) {
                D_80119C38 = (unk80119C38 *) racer->unk118;
                if (D_80119C38 != NULL) {
                    if (D_80119C38->unk74 == 0) {
                        maxVal = 20;
                        if (D_80119C38->unk0[0] != 0) {
                            loopCount3 = -1;
                            for (loopCount2 = 0; loopCount2 < ARRAY_COUNT(D_80119C30); loopCount2++) {
                                if (D_80119C30[loopCount2] != NULL) {
                                    curVal = D_80119C38->unk88;
                                    curVal -= D_80119C30[loopCount2]->unk88;
                                    if ((maxVal < curVal) && (D_800DC6D4 == 0)) {
                                        loopCount3 = loopCount2;
                                        maxVal = curVal;
                                    }
                                } else if (D_80119C38->unk88 >= 9) {
                                    loopCount3 = loopCount2;
                                }
                            }
                            if (loopCount3 != -1) {
                                D_80119C38->unk74 = 2;
                                if (D_80119C30[loopCount3] != NULL) {
                                    if (D_80119C30[loopCount3]->unk48[0] != NULL) {
                                        func_8000488C(D_80119C30[loopCount3]->unk48[0]);
                                        D_80119C30[loopCount3]->unk48[0] = NULL;
                                        D_80119C38->unk74 = 1;
                                    }
                                    D_800DC6D4 = 60;
                                    D_80119C30[loopCount3]->unk74 = 0;
                                }
                                D_80119C30[loopCount3] = D_80119C38;
                            }
                        }
                    }
                }
            }
        }
        if (func_8001139C() <= 0) {
            for (loopCount2 = 0; loopCount2 < ARRAY_COUNT(D_80119C30); loopCount2++) {
                temp = D_80119C30[loopCount2];
                if (temp != NULL) {
                    if (temp->unk0[0] != 0) {
                        if (temp->unk74 == 1) {
                            temp->unk74 = 2;
                        } else {
                            if (temp->unk48[0] == NULL) {
                                func_80001F14(temp->unk0[0], (s32 *) &temp->unk48[0]);
                            }
                            if (temp->unk48[0] != NULL) {
                                func_80009B7C((s32 *) temp->unk48[0], temp->unk78, temp->unk7C, temp->unk80);
                                func_800049F8(temp->unk48[0], 8, temp->unk88 << 8);
                                func_800049F8(temp->unk48[0], 16, *((u32*) &temp->unk8C));
                                if (arg3 != 1) {
                                    temp->unk91[0] = 64;
                                }
                                func_800049F8(temp->unk48[0], 4, temp->unk91[0]);
                                func_80004604(temp->unk48[0], 70);
                            }
                        }
                    }
                }
            }
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80006FC8.s")
#endif

UNUSED void func_80007F78(void) {
    D_800DC6D0 = 1;
}

UNUSED void func_80007F88(void) {
    D_800DC6D0 = 0;
}

UNUSED u8 func_80007F94(void) {
    return D_800DC6D0;
}

// This is likely an arctanh function.
f32 func_80007FA4(f32 arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 var_f14;
    f32 var_f2;
    s32 var_v0;

    var_f2 = 0.0f;
    temp_f0 = -1.0f;
    arg0 = (arg0 - 1.0f) / (1.0f + arg0);
    var_f14 = arg0;
    temp_f12 = arg0 * arg0;
    for (var_v0 = 1; (var_f2 - temp_f0) > 0.001; var_v0 += 2) {
        temp_f0 = var_f2;
        var_f2 += var_f14 / var_v0;
        var_f14 *= temp_f12;
    }
    return var_f2 * 2;
}
