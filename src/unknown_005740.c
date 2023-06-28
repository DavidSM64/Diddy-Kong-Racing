/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80004B40 */

#include "unknown_005740.h"

#include "types.h"
#include "macros.h"
#include "unknown_008C40.h"
#include "audiosfx.h"
#include "objects.h"

/************ .data ************/

u8 D_800DC6D0 = 1;
s32 D_800DC6D4 = 0; // Currently unknown, might be a different type.
s32 D_800DC6D8 = 1; // Currently unknown, might be a different type.

/*******************************/

/************ .bss ************/

//ALSeqPlayer?
//ALCSPlayer?
//ALCSPlayer_Custom?
typedef struct unk80119C38 {
    u16 unk0;
    u16 pad2;
    u8 pad4[0x32];
    u8 unk36;
    u8 unk37;
    u8 unk38;
    u8 unk39;
    u8 pad3A[0x2];
    u8 unk3C;
    u8 pad3D[0x7];
    u8 unk44;
    u8 *unk48; //soundMask / soundState?
    u8 pad4C[0x4];
    u8 *unk50;
    f32 unk54;
    f32 unk58;
    f32 unk5C;
    u8 pad60[0x8];
    f32 unk68;
    u8 pad6C[0x8];
    u32 unk74;
    f32 unk78; // X?
    f32 unk7C; // Y?
    f32 unk80; // Z?
    f32 unk84;
    u8 unk88; // Volume?
    f32 unk8C; // Volume?
    u8 pad90;
    u8 unk91;
    u8 pad92[0x2];
    u8 unk94;
    u8 pad95[0xB];
    u8 unkA0;
} unk80119C38;

unk80119C38 *D_80119C30[2];
unk80119C38 *D_80119C38;
s32 D_80119C3C;
unk80115D18 *D_80119C40; // This should be in unknown_008C40?
unk80119C50 **D_80119C44;
unk80119C50 **D_80119C48; //0x24 struct size - 0x5A0 total size - should be 40 elements
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
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800050D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80005254.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80005D08.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800063EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80006AC8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80006BFC.s")
/*
static f64 D_800E4CC8 = 0.05;
static f64 D_800E4CD8 = 0.05;
static f64 D_800E4CE8 = 0.8;

//void func_80006FC8(Object **objs, s32 numRacers, ObjectSegment *arg2, u8 arg3, s32 updateRate) {
*/

#if 1
void func_80006FC8(Object **arg0, s32 arg1, ObjectSegment *arg2, u8 arg3, s32 arg4) {
    f32 sp8C;
    Object **var_s2_6;
    Object **var_s6;
    Object *temp_s0;
    Object_Racer *racer;
    Object_64 *temp_s1_7;
    f32 tempyPos;
    f32 temp_f0_3;
    f32 tempxPos;
    f32 temp_f20_2;
    f32 tempzPos;
    f32 temp_f8;
    f32 var_f26;
    s32 *temp_a0_2;
    u8 temp_s3;
    unk80119C38 *temp_t2;
    u8 temp_t3;
    u8 temp_t6_2;
    s32 temp_t8_2;
    s32 temp_v0_7;
    s32 var_a0_2;
    s32 var_a2;
    s32 var_s5_2;
    s32 var_s5_3;
    s32 var_v1;
    u16 temp_a2_2;
    u8 *temp_a0_7;
    u8 *var_a0;
    s32 i, j;

    for (i = 0; i < arg3; i++) {
        var_s6 = arg0[i];
        racer = &arg0[i]->unk64->racer;
        if (racer != NULL) {
            D_80119C38 = (unk80119C38 *) racer->unk118;
        } else {
            D_80119C38 = NULL;
        }
        if ((D_80119C38 != NULL) && (D_80119C38->unk0 != 0)) {
            if (racer->raceFinished == 0 || check_if_showing_cutscene_camera()) {
                var_f26 = 1.0f;
                D_80119C38->unk91 = 64;
                D_80119C38->unk68 = 0.0f;
            } else {
                tempyPos = var_s6[0]->segment.trans.y_position - arg2[i].trans.y_position;
                tempxPos = var_s6[0]->segment.trans.x_position - arg2[i].trans.x_position;
                tempzPos = var_s6[0]->segment.trans.z_position - arg2[i].trans.z_position;
                func_80006BFC(var_s6[0], arg2, var_s6[0], arg4);
                D_80119C38->unk84 = sqrtf((tempxPos * tempxPos) + (tempyPos * tempyPos) + (tempzPos * tempzPos));
                if (D_80119C38->unk84 < 1500.0f) {
                    //2250000.0f = (1500.0f * 1500.0f)
                    var_f26 = (2250000.0f - (D_80119C38->unk84 * D_80119C38->unk84)) / 2250000.0f;
                    var_f26 *= var_f26;
                    D_80119C38->unk91 = func_800090C0(tempxPos, tempzPos, arg2[i].trans.y_rotation);
                } else {
                    var_f26 = 0.0f;
                }
                if (racer->raceFinished == 0) {
                    var_f26 *= 0.5;
                }
            }
            if ((D_80119C38->unkA0 < 70) && (D_80119C38->unk36) && (arg3 < 3) && (var_f26 != 0.0) && !(D_80119C38->unk44 & 1)) {
                temp_f20_2 = D_80119C38->unkA0 / 70.0f;
                temp_s3 = (D_80119C38->unk37 - (D_80119C38->unk37 * temp_f20_2)) * var_f26;
                if (temp_s3 >= 16) {
                    if (D_80119C38->unk50 == NULL) {
                        func_80001F14((u16) D_80119C38->unk36, D_80119C38 + 0x50);
                    }
                    temp_f0_3 = D_80119C38->unk38 / 100.0f;
                    sp8C = temp_f0_3 + ((((f32) D_80119C38->unk39 / 100.0f) - temp_f0_3) * temp_f20_2);
                    temp_a0_2 = D_80119C38->unk50;
                    if (temp_a0_2 != NULL) {
                        temp_s0 = *var_s6;
                        func_80009B7C(temp_a0_2, temp_s0->segment.trans.x_position, temp_s0->segment.trans.y_position, temp_s0->segment.trans.z_position);
                        func_800049F8(D_80119C38->unk50, 8, temp_s3 << 8);
                        func_800049F8(D_80119C38->unk50, 16, sp8C);
                        func_80004604((u8 *) D_80119C38->unk50, 80);
                        func_800049F8(D_80119C38->unk50, 4, D_80119C38->unk91);
                    }
                } else {
                    if (D_80119C38->unk50 != NULL) {
                        func_8000488C(D_80119C38->unk50);
                        D_80119C38->unk50 = 0;
                    }
                }
            } else {
                if (D_80119C38->unk50 != NULL) {
                    func_8000488C(D_80119C38->unk50);
                    D_80119C38->unk50 = 0;
                }
            }
            for (j = 0; j < 2; j++) {
                if (var_f26 != 0.0) {
                    temp_t6_2 =  D_80119C38[j].unk54 * var_f26;
                    temp_f8 = D_80119C38[j].unk5C + D_80119C38->unk3C + D_80119C38->unk94 + D_80119C38->unk68;
                    if (temp_f8 < 0.05) {
                        temp_f8 = 0.05f;
                    }
                    if ((j == 0) && (D_80119C38[j].unk44 & 1)) {
                        if (D_80119C38[j].unk48 != NULL) {
                            func_8000488C(D_80119C38[j].unk48);
                            D_80119C38[j].unk48 = 0;
                        }
                    } else {
                        var_a0 = D_80119C38[j].unk48;
                        if ((var_a0 != NULL) && (temp_t6_2 == 0)) {
                            func_8000488C(var_a0);
                            D_80119C38[j].unk48 = 0;
                        } else {
                            if (var_a0 == NULL) {
                                func_80001F14(D_80119C38[j].unk0, D_80119C38[j].unk48);
                                var_a0 = D_80119C38[j].unk48;
                            }
                            if (var_a0 != NULL) {
                                temp_s0 = *var_s6;
                                func_80009B7C((s32 *) var_a0, temp_s0->segment.trans.x_position, temp_s0->segment.trans.y_position, temp_s0->segment.trans.z_position);
                                func_800049F8(D_80119C38[j].unk48, 8, temp_t6_2 << 8);
                                func_800049F8(D_80119C38[j].unk48, 16, temp_f8);
                                func_80004604(D_80119C38[j].unk48, 80);
                                if (arg3 != 1) {
                                    D_80119C38->unk91 = 64;
                                }
                                func_800049F8(D_80119C38[j].unk48, 4, D_80119C38[j].unk91);
                            }
                        }
                    }
                }
            }
        }
    }
    if (arg3 < 3) {
        for (var_s5_2 = arg3; var_s5_2 < arg1; var_s5_2++) {
            racer = &arg0[var_s5_2]->unk64->racer;
            if (arg0[var_s5_2]->unk64 != NULL) {
                D_80119C38 = (unk80119C38 *) racer->unk118;
                if (D_80119C38 != 0) {
                    D_80119C38->unk88 = 0;
                }
            }
        }
        for (i = 0; i < arg3; i++) {
            temp_s1_7 = arg0[i]->unk64;
            for (var_s5_3 = arg3; var_s5_3 < arg1; var_s5_3++) {
                racer = &arg0[var_s5_3]->unk64->racer;
                if (racer != NULL) {
                    temp_t8_2 = racer->unk118;
                    D_80119C38 = (unk80119C38 *) temp_t8_2;
                    if (temp_t8_2 != 0) {
                        if (temp_s1_7->racer.raceFinished != 0) {              
                            tempyPos = arg0[var_s5_3]->segment.trans.y_position - arg2[i].trans.y_position;     
                            tempxPos = arg0[var_s5_3]->segment.trans.x_position - arg2[i].trans.x_position;       
                            tempzPos = arg0[var_s5_3]->segment.trans.z_position - arg2[i].trans.z_position;
                        } else {
                            tempyPos = arg0[var_s5_3]->segment.trans.y_position - arg0[i]->segment.trans.y_position;
                            tempxPos = arg0[var_s5_3]->segment.trans.x_position - arg0[i]->segment.trans.x_position;
                            tempzPos = arg0[var_s5_3]->segment.trans.z_position - arg0[i]->segment.trans.z_position;
                        }
                        D_80119C38->unk84 = sqrtf((tempxPos * tempxPos) + (tempyPos * tempyPos) + (tempzPos * tempzPos));
                        if (D_80119C38->unk84 < 1500.0f) {
                            //2250000.0f = (1500.0f * 1500.0f)
                            temp_t3 = D_80119C38->unk54 * ((2250000.0f - (D_80119C38->unk84 * D_80119C38->unk84)) / 2250000.0f);
                            if (temp_t3 > 127) {
                                temp_t3 = 127;
                            }
                            temp_t3 *= 0.8;
                            if (D_80119C38->unk88 < temp_t3) {
                                D_80119C38->unk88 = temp_t3;
                                D_80119C38->unk91 = func_800090C0(tempxPos, tempzPos, arg2->trans.y_rotation);
                                if (temp_s1_7->racer.raceFinished != 0) {
                                    func_80006BFC(arg0[i], arg2, arg0[var_s5_3], arg4);
                                } else {
                                    func_80006BFC(arg0[i], NULL, arg0[var_s5_3], arg4);
                                }
                                D_80119C38->unk8C = D_80119C38->unk68 + D_80119C38->unk5C;
                                if (D_80119C38->unk8C < 0.05) {
                                    D_80119C38->unk8C = 0.05f;
                                }
                            }
                        }
                    }
                }
            }
        }
        for (i = 0; i < ARRAY_COUNT(D_80119C30); i++) {
            if (D_80119C30[i] != NULL) {
                if (D_80119C30[i]->unk48 != NULL && D_80119C30[i]->unk88 < 8) {
                    func_8000488C(D_80119C30[i]->unk48);
                    D_80119C30[i]->unk48 = NULL;
                    D_80119C30[i]->unk74 = 0;
                    D_80119C30[i] = NULL;
                }
            }
        }
        if (arg4 < D_800DC6D4) {
            D_800DC6D4 -= arg4;
        } else {
            D_800DC6D4 = 0;
        }
        for (i = 1; i < arg1; i++) {
            if (var_s2_6[i]->unk64 != NULL) {
                temp_t2 = (unk80119C38 *) var_s2_6[i]->unk64->racer.unk118;
                D_80119C38 = (unk80119C38 **) &temp_t2;
                if (temp_t2 != 0) {
                    if (temp_t2->unk74 == 0) {
                        var_a2 = 20;
                        var_a0_2 = -1;
                        if (temp_t2->unk0 != 0) {
                            for (var_v1 = 0; var_v1 < 2; var_v1++) {
                                if (D_80119C30[var_v1] != NULL) {
                                    temp_v0_7 = temp_t2->unk88 - D_80119C30[var_v1]->unk88;
                                    if ((var_a2 < temp_v0_7) && (D_800DC6D4 == 0)) {
                                        var_a0_2 = var_v1;
                                        var_a2 = temp_v0_7;
                                    }
                                } else if (temp_t2->unk88 >= 9) {
                                    var_a0_2 = var_v1;
                                }
                            }
                            if (var_a0_2 != -1) {
                                temp_t2->unk74 = 2;
                                if (D_80119C30[var_a0_2] != NULL) {
                                    temp_a0_7 = D_80119C30[var_a0_2]->unk48;
                                    if (temp_a0_7 != NULL) {
                                        func_8000488C(temp_a0_7);
                                        D_80119C30[var_a0_2]->unk48 = NULL;
                                        D_80119C38->unk74 = 1;
                                    }
                                    D_800DC6D4 = 60;
                                    D_80119C30[var_a0_2]->unk74 = 0;
                                }
                                D_80119C30[var_a0_2] = (unk80119C38 *) D_80119C38;
                            }
                        }
                    }
                }
            }
        }
        if (func_8001139C() <= 0) {
            for (i = 0; i < ARRAY_COUNT(D_80119C30); i++) {
                if (D_80119C30[i] != NULL) {
                    temp_a2_2 = D_80119C30[i]->unk0;
                    if (temp_a2_2 != 0) {
                        if (D_80119C30[i]->unk74 == 1) {
                            D_80119C30[i]->unk74 = 2;
                        } else {
                            if (D_80119C30[i]->unk48 == NULL) {
                                func_80001F14(temp_a2_2,  D_80119C30[i]->unk48);
                            }
                            if (D_80119C30[i]->unk48 != NULL) {
                                func_80009B7C(D_80119C30[i]->unk48, D_80119C30[i]->unk80, D_80119C30[i]->unk84, D_80119C30[i]->unk80);
                                func_800049F8(D_80119C30[i]->unk48, 8, D_80119C30[i]->unk88 << 8);
                                func_800049F8(D_80119C30[i]->unk48, 16, D_80119C30[i]->unk8C);
                                if (arg3 != 1) {
                                    D_80119C30[i]->unk91 = 64;
                                }
                                func_800049F8(D_80119C30[i]->unk48, 4, (u32) D_80119C30[i]->unk91);
                                func_80004604(D_80119C30[i]->unk48, 70);
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
