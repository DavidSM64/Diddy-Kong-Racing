#include "ctx.c"

static ? D_800E4CC8;                                /* unable to generate initializer; const */
static ? D_800E4CD8;                                /* unable to generate initializer; const */
static ? D_800E4CE8;                                /* unable to generate initializer; const */

void func_80006FC8(Object **arg0, s32 arg1, ObjectSegment *arg2, u8 arg3, s32 arg4) {
    f32 spC0;
    s32 spAC;
    f32 sp8C;
    s32 sp7C;
    ObjectSegment *sp70;
    Object **var_s2_3;
    Object **var_s2_4;
    Object **var_s2_5;
    Object **var_s2_6;
    Object **var_s6;
    Object **var_s6_2;
    Object *temp_a2;
    Object *temp_s0;
    Object *temp_s0_2;
    Object *temp_s0_3;
    Object *temp_v0_3;
    Object *temp_v0_4;
    ObjectSegment *temp_v1;
    ObjectSegment *temp_v1_2;
    Object_64 *temp_s1;
    Object_64 *temp_s1_2;
    Object_64 *temp_s1_3;
    Object_64 *temp_s1_7;
    Object_64 *temp_v0_2;
    Object_64 *temp_v0_6;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f26;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f4;
    f32 temp_f6;
    f32 temp_f8;
    f32 var_f0;
    f32 var_f16;
    f32 var_f18;
    f32 var_f20;
    f32 var_f26;
    f32 var_f6;
    f64 temp_f20_3;
    f64 temp_f24;
    f64 temp_f28;
    f64 temp_f28_2;
    f64 temp_f4_2;
    f64 var_f16_2;
    s32 *temp_a0_2;
    s32 *temp_a0_3;
    s32 *temp_a0_4;
    s32 temp_s3;
    s32 temp_t0;
    s32 temp_t2;
    s32 temp_t3;
    s32 temp_t4;
    s32 temp_t5;
    s32 temp_t5_2;
    s32 temp_t6;
    s32 temp_t6_2;
    s32 temp_t7_2;
    s32 temp_t8_2;
    s32 temp_t9;
    s32 temp_v0_7;
    s32 var_a0_2;
    s32 var_a2;
    s32 var_s1;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s5;
    s32 var_s5_2;
    s32 var_s5_3;
    s32 var_s5_4;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v1;
    u16 temp_a2_2;
    u8 *temp_a0_5;
    u8 *temp_a0_6;
    u8 *temp_a0_7;
    u8 *var_a0;
    u8 temp_a0;
    u8 temp_a1;
    u8 temp_t7;
    u8 temp_v0;
    unk80119C38 **temp_s1_9;
    unk80119C38 **var_s3;
    unk80119C38 **var_s3_2;
    unk80119C38 **var_s3_3;
    unk80119C38 *temp_s1_10;
    unk80119C38 *temp_s1_8;
    unk80119C38 *temp_t1;
    unk80119C38 *temp_t6_3;
    unk80119C38 *temp_t8;
    unk80119C38 *temp_v0_5;
    unk80119C38 *temp_v0_8;
    void *temp_s1_4;
    void *temp_s1_5;
    void *temp_s1_6;
    void *temp_t9_2;
    void *var_v0;

    temp_t6 = arg3 & 0xFF;
    sp7C = temp_t6;
    spAC = 0;
    if (temp_t6 > 0) {
        temp_f28 = *(&D_800E4CC8 + 4);
        var_s6 = arg0;
        do {
            temp_s1 = (*var_s6)->unk64;
            if (temp_s1 != NULL) {
                D_80119C38 = (unk80119C38 *) temp_s1->racer.unk118;
            } else {
                D_80119C38 = NULL;
            }
            if ((D_80119C38 != NULL) && (D_80119C38->unk0 != 0)) {
                var_s5 = 0;
                if (temp_s1->racer.raceFinished == 0) {
                    if (check_if_showing_cutscene_camera() != 0) {
                        goto block_10;
                    }
                    D_80119C38->unk91 = 0x40;
                    var_f26 = 1.0f;
                    D_80119C38->unk68 = 0.0f;
                } else {
block_10:
                    temp_a2 = *var_s6;
                    temp_v1 = &arg2[spAC];
                    temp_f0 = temp_a2->segment.trans.y_position - temp_v1->trans.y_position;
                    sp70 = temp_v1;
                    spC0 = temp_f0;
                    temp_f20 = temp_a2->segment.trans.x_position - temp_v1->trans.x_position;
                    temp_f22 = temp_a2->segment.trans.z_position - temp_v1->trans.z_position;
                    func_80006BFC(temp_a2, arg2, temp_a2, arg4);
                    D_80119C38->unk84 = sqrtf((temp_f20 * temp_f20) + (temp_f0 * temp_f0) + (temp_f22 * temp_f22));
                    temp_f2 = D_80119C38->unk84;
                    if (temp_f2 < 1500.0f) {
                        temp_f26 = (2250000.0f - (temp_f2 * temp_f2)) / 2250000.0f;
                        var_f26 = temp_f26 * temp_f26;
                        D_80119C38->unk91 = func_800090C0(temp_f20, temp_f22, (s32) temp_v1->trans.y_rotation);
                    } else {
                        var_f26 = 0.0f;
                    }
                    if (temp_s1->racer.raceFinished == 0) {
                        var_f26 = (f32) ((f64) var_f26 * 0.5);
                    }
                }
                temp_v0 = D_80119C38->unkA0;
                if (((s32) temp_v0 < 0x46) && (temp_a0 = D_80119C38->unk36, (temp_a0 != 0)) && (sp7C < 3) && ((f64) var_f26 != 0.0) && !(D_80119C38->unk44 & 1)) {
                    temp_f20_2 = (f32) temp_v0 / 70.0f;
                    temp_f0_2 = (f32) D_80119C38->unk37;
                    temp_f6 = (temp_f0_2 - (temp_f0_2 * temp_f20_2)) * var_f26;
                    if (M2C_ERROR(/* cfc1 */) & 0x78) {
                        if (!(M2C_ERROR(/* cfc1 */) & 0x78)) {
                            var_s2 = (s32) (temp_f6 - 2.1474836e9f) | 0x80000000;
                        } else {
                            goto block_24;
                        }
                    } else {
                        var_s2 = (s32) temp_f6;
                        if (var_s2 < 0) {
block_24:
                            var_s2 = -1;
                        }
                    }
                    temp_s3 = var_s2 & 0xFF;
                    if (temp_s3 >= 0x10) {
                        if (D_80119C38->unk50 == NULL) {
                            func_80001F14((u16) temp_a0, D_80119C38 + 0x50);
                        }
                        temp_t7 = D_80119C38->unk38;
                        var_f18 = (f32) temp_t7;
                        if ((s32) temp_t7 < 0) {
                            var_f18 += 4294967296.0f;
                        }
                        temp_f0_3 = var_f18 / 100.0f;
                        sp8C = temp_f0_3 + ((((f32) D_80119C38->unk39 / 100.0f) - temp_f0_3) * temp_f20_2);
                        temp_a0_2 = D_80119C38->unk50;
                        if (temp_a0_2 != NULL) {
                            temp_s0 = *var_s6;
                            func_80009B7C(temp_a0_2, temp_s0->segment.trans.x_position, temp_s0->segment.trans.y_position, temp_s0->segment.trans.z_position);
                            func_800049F8((s32) D_80119C38->unk50, 8, temp_s3 << 8);
                            func_800049F8((s32) D_80119C38->unk50, 0x10, (bitwise u32) sp8C);
                            func_80004604((u8 *) D_80119C38->unk50, 0x50U);
                            func_800049F8((s32) D_80119C38->unk50, 4, (u32) D_80119C38->unk91);
                        }
                    } else {
                        temp_a0_3 = D_80119C38->unk50;
                        if (temp_a0_3 != NULL) {
                            func_8000488C((u8 *) temp_a0_3);
                            D_80119C38->unk50 = NULL;
                        }
                    }
                } else {
                    temp_a0_4 = D_80119C38->unk50;
                    if (temp_a0_4 != NULL) {
                        func_8000488C((u8 *) temp_a0_4);
                        D_80119C38->unk50 = NULL;
                    }
                }
                if (D_80119C38->unk0 != 0) {
                    temp_f20_3 = (f64) var_f26;
                    var_s1 = 0 * 4;
                    var_v0 = D_80119C38 + var_s1;
                    if (temp_f20_3 != 0.0) {
loop_39:
                        temp_f4 = var_v0->unk54 * var_f26;
                        if (M2C_ERROR(/* cfc1 */) & 0x78) {
                            if (!(M2C_ERROR(/* cfc1 */) & 0x78)) {
                                var_s2_2 = (s32) (temp_f4 - 2.1474836e9f) | 0x80000000;
                            } else {
                                goto block_42;
                            }
                        } else {
                            var_s2_2 = (s32) temp_f4;
                            if (var_s2_2 < 0) {
block_42:
                                var_s2_2 = -1;
                            }
                        }
                        temp_t6_2 = var_s2_2 & 0xFF;
                        temp_f8 = var_v0->unk5C + D_80119C38->unk3C + D_80119C38->unk94 + D_80119C38->unk68;
                        sp8C = temp_f8;
                        if ((f64) temp_f8 < temp_f28) {
                            sp8C = 0.05f;
                        }
                        if ((var_s5 == 0) && (D_80119C38->unk44 & 1)) {
                            temp_a0_5 = D_80119C38->unk48;
                            if (temp_a0_5 != NULL) {
                                func_8000488C(temp_a0_5);
                                D_80119C38->unk48 = NULL;
                            }
                        } else {
                            var_a0 = var_v0->unk48;
                            if ((var_a0 != NULL) && (temp_t6_2 == 0)) {
                                func_8000488C(var_a0);
                                (D_80119C38 + var_s1)->unk48 = 0;
                            } else {
                                if (var_a0 == NULL) {
                                    func_80001F14(*(D_80119C38 + (var_s5 * 2)), var_v0 + 0x48);
                                    var_a0 = (D_80119C38 + var_s1)->unk48;
                                }
                                if (var_a0 != NULL) {
                                    temp_s0_2 = *var_s6;
                                    func_80009B7C((s32 *) var_a0, temp_s0_2->segment.trans.x_position, temp_s0_2->segment.trans.y_position, temp_s0_2->segment.trans.z_position);
                                    func_800049F8((D_80119C38 + var_s1)->unk48, 8, temp_t6_2 << 8);
                                    func_800049F8((D_80119C38 + var_s1)->unk48, 0x10, (bitwise u32) sp8C);
                                    func_80004604((D_80119C38 + var_s1)->unk48, 0x50U);
                                    if (sp7C != 1) {
                                        D_80119C38->unk91 = 0x40;
                                    }
                                    func_800049F8((D_80119C38 + var_s1)->unk48, 4, (u32) D_80119C38->unk91);
                                }
                            }
                        }
                        var_s5 += 1;
                        var_s1 += 4;
                        if (var_s5 < 2) {
                            if (*(D_80119C38 + (var_s5 * 2)) != 0) {
                                var_v0 = D_80119C38 + var_s1;
                                if (temp_f20_3 == 0.0) {

                                } else {
                                    goto loop_39;
                                }
                            }
                        }
                    }
                }
            }
            temp_t0 = spAC + 1;
            spAC = temp_t0;
            var_s6 += 4;
        } while (temp_t0 != sp7C);
    }
    temp_f28_2 = *(&D_800E4CD8 + 4);
    if (sp7C < 3) {
        var_s5_2 = sp7C;
        spAC = 0;
        if (sp7C < arg1) {
            temp_t5 = (arg1 - sp7C) & 3;
            if (temp_t5 != 0) {
                var_s2_3 = &arg0[sp7C];
                do {
                    var_s5_2 += 1;
                    temp_s1_2 = (*var_s2_3)->unk64;
                    if (temp_s1_2 != NULL) {
                        temp_t9 = temp_s1_2->racer.unk118;
                        D_80119C38 = (unk80119C38 *) temp_t9;
                        if (temp_t9 != 0) {
                            temp_t9->unk88 = 0;
                        }
                    }
                    var_s2_3 += 4;
                } while ((temp_t5 + sp7C) != var_s5_2);
                if (var_s5_2 != arg1) {
                    goto block_73;
                }
            } else {
block_73:
                var_s2_4 = &arg0[var_s5_2];
                do {
                    temp_s1_3 = var_s2_4->unk0->unk64;
                    if (temp_s1_3 != NULL) {
                        temp_t5_2 = temp_s1_3->racer.unk118;
                        D_80119C38 = (unk80119C38 *) temp_t5_2;
                        if (temp_t5_2 != 0) {
                            temp_t5_2->unk88 = 0;
                        }
                    }
                    temp_s1_4 = var_s2_4->unk4->unk64;
                    if (temp_s1_4 != NULL) {
                        temp_t6_3 = temp_s1_4->unk118;
                        D_80119C38 = temp_t6_3;
                        if (temp_t6_3 != NULL) {
                            temp_t6_3->unk88 = 0;
                        }
                    }
                    temp_s1_5 = var_s2_4->unk8->unk64;
                    if (temp_s1_5 != NULL) {
                        temp_t8 = temp_s1_5->unk118;
                        D_80119C38 = temp_t8;
                        if (temp_t8 != NULL) {
                            temp_t8->unk88 = 0;
                        }
                    }
                    temp_t9_2 = var_s2_4->unkC;
                    var_s2_4 += 0x10;
                    temp_s1_6 = temp_t9_2->unk64;
                    if (temp_s1_6 != NULL) {
                        temp_t1 = temp_s1_6->unk118;
                        D_80119C38 = temp_t1;
                        if (temp_t1 != NULL) {
                            temp_t1->unk88 = 0;
                        }
                    }
                } while (var_s2_4 != &arg0[arg1]);
            }
        }
        var_s6_2 = arg0;
        if (sp7C > 0) {
            temp_f24 = *(&D_800E4CE8 + 4);
            do {
                temp_s1_7 = (*var_s6_2)->unk64;
                var_s5_3 = sp7C;
                if (sp7C < arg1) {
                    var_s2_5 = &arg0[sp7C];
                    do {
                        temp_v0_2 = (*var_s2_5)->unk64;
                        if (temp_v0_2 != NULL) {
                            temp_t8_2 = temp_v0_2->racer.unk118;
                            D_80119C38 = (unk80119C38 *) temp_t8_2;
                            if (temp_t8_2 != 0) {
                                if (temp_s1_7->racer.raceFinished != 0) {
                                    temp_v0_3 = *var_s2_5;
                                    temp_v1_2 = &arg2[spAC];
                                    var_f16 = temp_v1_2->trans.z_position;
                                    var_f6 = temp_v0_3->segment.trans.z_position;
                                    var_f20 = temp_v0_3->segment.trans.x_position - temp_v1_2->trans.x_position;
                                    var_f0 = temp_v0_3->segment.trans.y_position - temp_v1_2->trans.y_position;
                                } else {
                                    temp_v0_4 = *var_s2_5;
                                    temp_s0_3 = *var_s6_2;
                                    var_f6 = temp_v0_4->segment.trans.z_position;
                                    var_f16 = temp_s0_3->segment.trans.z_position;
                                    var_f20 = temp_v0_4->segment.trans.x_position - temp_s0_3->segment.trans.x_position;
                                    var_f0 = temp_v0_4->segment.trans.y_position - temp_s0_3->segment.trans.y_position;
                                }
                                temp_f22_2 = var_f6 - var_f16;
                                D_80119C38->unk84 = sqrtf((var_f20 * var_f20) + (var_f0 * var_f0) + (temp_f22_2 * temp_f22_2));
                                temp_f2_2 = D_80119C38->unk84;
                                if (temp_f2_2 < 1500.0f) {
                                    temp_f18 = D_80119C38->unk54 * ((2250000.0f - (temp_f2_2 * temp_f2_2)) / 2250000.0f);
                                    if (M2C_ERROR(/* cfc1 */) & 0x78) {
                                        if (!(M2C_ERROR(/* cfc1 */) & 0x78)) {
                                            var_v0_2 = (s32) (temp_f18 - 2.1474836e9f) | 0x80000000;
                                        } else {
                                            goto block_101;
                                        }
                                    } else {
                                        var_v0_2 = (s32) temp_f18;
                                        if (var_v0_2 < 0) {
block_101:
                                            var_v0_2 = -1;
                                        }
                                    }
                                    temp_t3 = var_v0_2 & 0xFF;
                                    var_v0_3 = temp_t3;
                                    if (temp_t3 >= 0x80) {
                                        var_v0_3 = 0x7F;
                                    }
                                    var_f16_2 = (f64) var_v0_3;
                                    if (var_v0_3 < 0) {
                                        var_f16_2 += 4294967296.0;
                                    }
                                    temp_f4_2 = var_f16_2 * temp_f24;
                                    if (M2C_ERROR(/* cfc1 */) & 0x78) {
                                        if (!(M2C_ERROR(/* cfc1 */) & 0x78)) {
                                            var_v0_4 = (s32) (temp_f4_2 - 2147483648.0) | 0x80000000;
                                        } else {
                                            goto block_110;
                                        }
                                    } else {
                                        var_v0_4 = (s32) temp_f4_2;
                                        if (var_v0_4 < 0) {
block_110:
                                            var_v0_4 = -1;
                                        }
                                    }
                                    temp_t7_2 = var_v0_4 & 0xFF;
                                    if ((s32) D_80119C38->unk88 < temp_t7_2) {
                                        D_80119C38->unk88 = (u8) temp_t7_2;
                                        D_80119C38->unk91 = func_800090C0(var_f20, temp_f22_2, (s32) arg2->trans.y_rotation);
                                        if (temp_s1_7->racer.raceFinished != 0) {
                                            func_80006BFC(*var_s6_2, arg2, *var_s2_5, arg4);
                                        } else {
                                            func_80006BFC(*var_s6_2, NULL, *var_s2_5, arg4);
                                        }
                                        D_80119C38->unk8C = D_80119C38->unk5C + D_80119C38->unk68;
                                        if ((f64) D_80119C38->unk8C < temp_f28_2) {
                                            D_80119C38->unk8C = 0.05f;
                                        }
                                    }
                                }
                            }
                        }
                        var_s5_3 += 1;
                        var_s2_5 += 4;
                    } while (var_s5_3 != arg1);
                }
                temp_t4 = spAC + 1;
                spAC = temp_t4;
                var_s6_2 += 4;
            } while (temp_t4 != sp7C);
        }
        var_s3 = D_80119C30;
        do {
            temp_v0_5 = *var_s3;
            if (temp_v0_5 != NULL) {
                temp_a0_6 = temp_v0_5->unk48;
                if ((temp_a0_6 != NULL) && ((s32) temp_v0_5->unk88 < 8)) {
                    func_8000488C(temp_a0_6);
                    (*var_s3)->unk48 = NULL;
                    (*var_s3)->unk74 = 0;
                    *var_s3 = NULL;
                }
            }
            var_s3 += 4;
        } while (var_s3 != &D_80119C38);
        if (arg4 < D_800DC6D4) {
            D_800DC6D4 -= arg4;
        } else {
            D_800DC6D4 = 0;
        }
        var_s5_4 = 1;
        if (arg1 >= 2) {
            var_s2_6 = arg0 + 4;
            do {
                temp_v0_6 = (*var_s2_6)->unk64;
                if (temp_v0_6 != NULL) {
                    temp_t2 = temp_v0_6->racer.unk118;
                    D_80119C38 = (unk80119C38 *) temp_t2;
                    if (temp_t2 != 0) {
                        if (temp_t2->unk74 == 0) {
                            var_a2 = 0x14;
                            var_a0_2 = -1;
                            if (temp_t2->unk0 != 0) {
                                temp_a1 = temp_t2->unk88;
                                var_s3_2 = D_80119C30;
                                var_v1 = 0;
                                do {
                                    temp_s1_8 = *var_s3_2;
                                    if (temp_s1_8 != NULL) {
                                        temp_v0_7 = temp_a1 - temp_s1_8->unk88;
                                        if ((var_a2 < temp_v0_7) && (D_800DC6D4 == 0)) {
                                            var_a0_2 = var_v1;
                                            var_a2 = temp_v0_7;
                                        }
                                    } else if ((s32) temp_a1 >= 9) {
                                        var_a0_2 = var_v1;
                                    }
                                    var_v1 += 1;
                                    var_s3_2 += 4;
                                } while (var_v1 != 2);
                                if (var_a0_2 != -1) {
                                    temp_t2->unk74 = 2U;
                                    temp_s1_9 = &D_80119C30[var_a0_2];
                                    temp_v0_8 = *temp_s1_9;
                                    if (temp_v0_8 != NULL) {
                                        temp_a0_7 = temp_v0_8->unk48;
                                        if (temp_a0_7 != NULL) {
                                            func_8000488C(temp_a0_7);
                                            (*temp_s1_9)->unk48 = NULL;
                                            D_80119C38->unk74 = 1;
                                        }
                                        D_800DC6D4 = 0x3C;
                                        (*temp_s1_9)->unk74 = 0;
                                    }
                                    *temp_s1_9 = D_80119C38;
                                }
                            }
                        }
                    }
                }
                var_s5_4 += 1;
                var_s2_6 += 4;
            } while (var_s5_4 != arg1);
        }
        if (func_8001139C() <= 0) {
            var_s3_3 = D_80119C30;
            do {
                temp_s1_10 = *var_s3_3;
                if (temp_s1_10 != NULL) {
                    temp_a2_2 = temp_s1_10->unk0;
                    if (temp_a2_2 != 0) {
                        if (temp_s1_10->unk74 == 1) {
                            temp_s1_10->unk74 = 2U;
                        } else {
                            if (temp_s1_10->unk48 == NULL) {
                                func_80001F14(temp_a2_2 & 0xFFFF, (s32 *) &temp_s1_10->unk48);
                            }
                            if ((s32 *) temp_s1_10->unk48 != NULL) {
                                func_80009B7C((s32 *) temp_s1_10->unk48, temp_s1_10->unk78, temp_s1_10->unk7C, temp_s1_10->unk80);
                                func_800049F8((s32) temp_s1_10->unk48, 8, temp_s1_10->unk88 << 8);
                                func_800049F8((s32) temp_s1_10->unk48, 0x10, (bitwise u32) temp_s1_10->unk8C);
                                if (sp7C != 1) {
                                    temp_s1_10->unk91 = 0x40;
                                }
                                func_800049F8((s32) temp_s1_10->unk48, 4, (u32) temp_s1_10->unk91);
                                func_80004604(temp_s1_10->unk48, 0x46U);
                            }
                        }
                    }
                }
                var_s3_3 += 4;
            } while (var_s3_3 != &D_80119C38);
        }
    }
}
