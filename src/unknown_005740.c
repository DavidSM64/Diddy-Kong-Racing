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

/************ .data ************/

u8 D_800DC6D0 = 1;
s32 D_800DC6D4 = 0; // Currently unknown, might be a different type.
s32 D_800DC6D8 = 1; // Currently unknown, might be a different type.

/*******************************/

/************ .bss ************/

typedef struct unk80119C38 {
    u16 unk0[2];
    u8 pad4[0x32];
    u8 unk36;
    u8 unk37;
    u8 unk38;
    u8 unk39;
    u8 pad3A[0x2];
    f32 unk3C;
    u8 pad40[0x4];
    u8 unk44[4];
    u8 *unk48[2]; //soundMask / soundState?
    u8 *unk50;
    f32 unk54[2];
    f32 unk5C[3];
    f32 unk68;
    u8 pad6C[0x8];
    u8 unk74;
    f32 unk78; // X
    f32 unk7C; // Y
    f32 unk80; // Z
    f32 unk84;
    u8 unk88; // Volume?
    f32 unk8C; // Volume?
    u8 pad90;
    u8 unk91[3];
    f32 unk94;
    u8 pad98[0x8];
    u8 unkA0;
    u8 padA1[0x7];
    s32 unkA8;
} unk80119C38;

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

GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80004B40.s")

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

GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80005254.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80005D08.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800063EC.s")

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

GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80006BFC.s")

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
