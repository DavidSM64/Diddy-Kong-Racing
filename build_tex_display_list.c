#include "ctx.c"

void build_tex_display_list(TextureHeader *tex, Gfx *dlist) {
    s32 sp27C;
    s32 sp278;
    s32 sp274;
    s32 sp26C;
    s32 sp268;
    s32 sp264;
    s32 sp260;
    Gfx *sp248;
    u32 *sp21C;
    u32 *sp1CC;
    u32 *sp1B0;
    u32 *sp178;
    TextureHeader *sp48;
    u32 sp34;
    s32 sp30;
    u32 sp2C;
    u32 sp28;
    s32 sp24;
    Gfx *temp_a3;
    Gfx *temp_a3_100;
    Gfx *temp_a3_101;
    Gfx *temp_a3_102;
    Gfx *temp_a3_103;
    Gfx *temp_a3_104;
    Gfx *temp_a3_105;
    Gfx *temp_a3_106;
    Gfx *temp_a3_107;
    Gfx *temp_a3_108;
    Gfx *temp_a3_10;
    Gfx *temp_a3_11;
    Gfx *temp_a3_12;
    Gfx *temp_a3_13;
    Gfx *temp_a3_14;
    Gfx *temp_a3_15;
    Gfx *temp_a3_16;
    Gfx *temp_a3_17;
    Gfx *temp_a3_18;
    Gfx *temp_a3_19;
    Gfx *temp_a3_20;
    Gfx *temp_a3_21;
    Gfx *temp_a3_22;
    Gfx *temp_a3_23;
    Gfx *temp_a3_24;
    Gfx *temp_a3_25;
    Gfx *temp_a3_26;
    Gfx *temp_a3_27;
    Gfx *temp_a3_28;
    Gfx *temp_a3_29;
    Gfx *temp_a3_2;
    Gfx *temp_a3_30;
    Gfx *temp_a3_31;
    Gfx *temp_a3_32;
    Gfx *temp_a3_33;
    Gfx *temp_a3_34;
    Gfx *temp_a3_35;
    Gfx *temp_a3_36;
    Gfx *temp_a3_37;
    Gfx *temp_a3_38;
    Gfx *temp_a3_39;
    Gfx *temp_a3_3;
    Gfx *temp_a3_40;
    Gfx *temp_a3_41;
    Gfx *temp_a3_42;
    Gfx *temp_a3_43;
    Gfx *temp_a3_44;
    Gfx *temp_a3_45;
    Gfx *temp_a3_46;
    Gfx *temp_a3_47;
    Gfx *temp_a3_48;
    Gfx *temp_a3_49;
    Gfx *temp_a3_4;
    Gfx *temp_a3_50;
    Gfx *temp_a3_51;
    Gfx *temp_a3_52;
    Gfx *temp_a3_53;
    Gfx *temp_a3_54;
    Gfx *temp_a3_55;
    Gfx *temp_a3_56;
    Gfx *temp_a3_57;
    Gfx *temp_a3_58;
    Gfx *temp_a3_59;
    Gfx *temp_a3_5;
    Gfx *temp_a3_60;
    Gfx *temp_a3_61;
    Gfx *temp_a3_62;
    Gfx *temp_a3_63;
    Gfx *temp_a3_64;
    Gfx *temp_a3_65;
    Gfx *temp_a3_66;
    Gfx *temp_a3_67;
    Gfx *temp_a3_68;
    Gfx *temp_a3_69;
    Gfx *temp_a3_6;
    Gfx *temp_a3_70;
    Gfx *temp_a3_71;
    Gfx *temp_a3_72;
    Gfx *temp_a3_73;
    Gfx *temp_a3_74;
    Gfx *temp_a3_75;
    Gfx *temp_a3_76;
    Gfx *temp_a3_77;
    Gfx *temp_a3_78;
    Gfx *temp_a3_79;
    Gfx *temp_a3_7;
    Gfx *temp_a3_80;
    Gfx *temp_a3_81;
    Gfx *temp_a3_82;
    Gfx *temp_a3_83;
    Gfx *temp_a3_84;
    Gfx *temp_a3_85;
    Gfx *temp_a3_86;
    Gfx *temp_a3_87;
    Gfx *temp_a3_88;
    Gfx *temp_a3_89;
    Gfx *temp_a3_8;
    Gfx *temp_a3_90;
    Gfx *temp_a3_91;
    Gfx *temp_a3_92;
    Gfx *temp_a3_93;
    Gfx *temp_a3_94;
    Gfx *temp_a3_95;
    Gfx *temp_a3_96;
    Gfx *temp_a3_97;
    Gfx *temp_a3_98;
    Gfx *temp_a3_99;
    Gfx *temp_a3_9;
    Gfx *var_a3;
    s32 temp_a1;
    s32 temp_a1_10;
    s32 temp_a1_11;
    s32 temp_a1_12;
    s32 temp_a1_13;
    s32 temp_a1_14;
    s32 temp_a1_15;
    s32 temp_a1_16;
    s32 temp_a1_2;
    s32 temp_a1_3;
    s32 temp_a1_4;
    s32 temp_a1_5;
    s32 temp_a1_6;
    s32 temp_a1_7;
    s32 temp_a1_8;
    s32 temp_a1_9;
    s32 temp_a2;
    s32 temp_a2_10;
    s32 temp_a2_2;
    s32 temp_a2_3;
    s32 temp_a2_4;
    s32 temp_a2_5;
    s32 temp_a2_6;
    s32 temp_a2_7;
    s32 temp_a2_8;
    s32 temp_a2_9;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_t0;
    s32 temp_t0_10;
    s32 temp_t0_11;
    s32 temp_t0_12;
    s32 temp_t0_13;
    s32 temp_t0_14;
    s32 temp_t0_15;
    s32 temp_t0_16;
    s32 temp_t0_2;
    s32 temp_t0_3;
    s32 temp_t0_4;
    s32 temp_t0_5;
    s32 temp_t0_6;
    s32 temp_t0_7;
    s32 temp_t0_8;
    s32 temp_t0_9;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t1_3;
    s32 temp_t3;
    s32 temp_t3_2;
    s32 temp_t3_3;
    s32 temp_t3_4;
    s32 temp_t4;
    s32 temp_t4_2;
    s32 temp_t4_3;
    s32 temp_t6;
    s32 temp_t6_2;
    s32 temp_t6_3;
    s32 temp_t6_4;
    s32 temp_t7;
    s32 temp_t8;
    s32 temp_t8_2;
    s32 temp_t9_2;
    s32 temp_v0;
    s32 temp_v0_10;
    s32 temp_v0_11;
    s32 temp_v0_12;
    s32 temp_v0_13;
    s32 temp_v0_14;
    s32 temp_v0_15;
    s32 temp_v0_16;
    s32 temp_v0_17;
    s32 temp_v0_18;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 temp_v1_10;
    s32 temp_v1_11;
    s32 temp_v1_12;
    s32 temp_v1_13;
    s32 temp_v1_14;
    s32 temp_v1_15;
    s32 temp_v1_16;
    s32 temp_v1_17;
    s32 temp_v1_18;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 temp_v1_8;
    s32 temp_v1_9;
    s32 var_a0;
    s32 var_a0_10;
    s32 var_a0_11;
    s32 var_a0_12;
    s32 var_a0_13;
    s32 var_a0_14;
    s32 var_a0_15;
    s32 var_a0_16;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    s32 var_a0_5;
    s32 var_a0_6;
    s32 var_a0_7;
    s32 var_a0_8;
    s32 var_a0_9;
    s32 var_a2;
    s32 var_at;
    s32 var_ra;
    s32 var_ra_2;
    s32 var_ra_3;
    s32 var_ra_4;
    s32 var_ra_5;
    s32 var_t0;
    s32 var_t1;
    s32 var_t2;
    s32 var_t2_2;
    s32 var_t2_3;
    s32 var_t2_4;
    s32 var_t2_5;
    s32 var_t2_6;
    s32 var_t3;
    s32 var_v0;
    u32 temp_t7_2;
    u32 temp_t9;
    u8 temp_s0;
    u8 temp_t5;
    u8 temp_v1;

    temp_v1 = tex->format;
    tex->cmd = (s32 *) dlist;
    sp278 = ((s32) temp_v1 >> 4) & 0xF;
    temp_s0 = tex->height;
    temp_t5 = tex->width;
    var_a3 = dlist;
    var_v0 = 1;
    var_t2 = 1;
    var_t3 = 1;
    var_t0 = 1;
    var_t1 = 1;
    var_a2 = 0;
    temp_t4 = temp_v1 & 0xF;
    do {
        if (var_v0 < (s32) temp_t5) {
            var_t2 = var_a2 + 1;
            goto block_5;
        }
        var_at = var_v0 < (s32) temp_s0;
        if (var_v0 == temp_t5) {
            var_t0 = 0;
block_5:
            var_at = var_v0 < (s32) temp_s0;
        }
        temp_v1_2 = var_a2 + 1;
        if (var_at != 0) {
            var_t3 = temp_v1_2;
            goto block_10;
        }
        var_a2 = temp_v1_2;
        if (var_v0 == temp_s0) {
            var_t1 = 0;
block_10:
            var_a2 = temp_v1_2;
        }
        var_v0 *= 2;
    } while (temp_v1_2 != 7);
    if ((var_t0 != 0) || (tex->flags & 0x40)) {
        sp26C = 2;
        var_t2 = 0;
    } else {
        sp26C = 0;
    }
    if ((var_t1 != 0) || (tex->flags & 0x80)) {
        sp268 = 2;
        var_t3 = 0;
    } else {
        sp268 = 0;
    }
    if (!(tex->flags & 0x400)) {
        sp264 = var_t2;
        sp260 = var_t3;
        sp27C = temp_t4;
        if (temp_t4 == 0) {
            temp_a3 = dlist + 8;
            dlist->words.w0 = 0xFD180000;
            dlist->words.w1 = (u32) (tex + 0x80000020);
            temp_a3->words.w0 = 0xF5180000;
            temp_v0 = (sp268 & 3) << 0x12;
            temp_v1_3 = (sp260 & 0xF) << 0xE;
            temp_a1 = (sp26C & 3) << 8;
            temp_a2 = (sp264 & 0xF) * 0x10;
            temp_a3_2 = temp_a3 + 8;
            temp_a3->words.w1 = temp_v0 | 0x07000000 | temp_v1_3 | temp_a1 | temp_a2;
            temp_t0 = (temp_t5 * temp_s0) - 1;
            temp_a3_3 = temp_a3_2 + 8;
            temp_a3_2->words.w0 = 0xE6000000;
            temp_a3_2->words.w1 = 0;
            temp_a3_3->words.w0 = 0xF3000000;
            temp_a3_4 = temp_a3_3 + 8;
            if (temp_t0 < 0x7FF) {
                var_ra = temp_t0;
            } else {
                var_ra = 0x7FF;
            }
            temp_t6 = (s32) (temp_t5 * 4) / 8;
            if (temp_t6 <= 0) {
                var_t2_2 = 1;
            } else {
                var_t2_2 = temp_t6;
            }
            if (temp_t6 <= 0) {
                var_a0 = 1;
            } else {
                var_a0 = temp_t6;
            }
            temp_a3_5 = temp_a3_4 + 8;
            temp_a3_6 = temp_a3_5 + 8;
            var_a3 = temp_a3_6 + 8;
            temp_a3_3->words.w1 = (((s32) (var_t2_2 + 0x7FF) / var_a0) & 0xFFF) | 0x07000000 | ((var_ra & 0xFFF) << 0xC);
            temp_a3_4->words.w0 = 0xE7000000;
            temp_a3_4->words.w1 = 0;
            temp_a3_5->words.w1 = temp_v0 | temp_v1_3 | temp_a1 | temp_a2;
            temp_a3_5->words.w0 = ((((s32) ((temp_t5 * 2) + 7) >> 3) & 0x1FF) << 9) | 0xF5180000;
            temp_a3_6->words.w0 = 0xF2000000;
            temp_a3_6->words.w1 = ((((temp_t5 - 1) * 4) & 0xFFF) << 0xC) | (((temp_s0 - 1) * 4) & 0xFFF);
            if ((sp278 == 0) || (sp278 == 2)) {
                tex->flags |= 4;
            }
        }
        if (sp27C == 1) {
            var_a3->words.w1 = (u32) (tex + 0x80000020);
            temp_a3_7 = var_a3 + 8;
            var_a3->words.w0 = 0xFD100000;
            temp_a3_7->words.w0 = 0xF5100000;
            temp_v0_2 = (sp268 & 3) << 0x12;
            temp_v1_4 = (sp260 & 0xF) << 0xE;
            temp_a1_2 = (sp26C & 3) << 8;
            temp_t6_2 = (sp264 & 0xF) * 0x10;
            temp_a3_8 = temp_a3_7 + 8;
            temp_a3_7->words.w1 = temp_v0_2 | 0x07000000 | temp_v1_4 | temp_a1_2 | temp_t6_2;
            temp_t4_2 = temp_t5 * 2;
            temp_a3_8->words.w0 = 0xE6000000;
            temp_a3_9 = temp_a3_8 + 8;
            temp_a3_8->words.w1 = 0;
            temp_a3_9->words.w0 = 0xF3000000;
            sp30 = (((s32) (temp_t4_2 + 7) >> 3) & 0x1FF) << 9;
            sp2C = temp_v0_2 | temp_v1_4 | temp_a1_2 | temp_t6_2;
            temp_t0_2 = (temp_t5 * temp_s0) - 1;
            sp28 = ((((temp_t5 - 1) * 4) & 0xFFF) << 0xC) | (((temp_s0 - 1) * 4) & 0xFFF);
            sp21C = &temp_a3_9->words.w0;
            temp_a3_10 = temp_a3_9 + 8;
            if (temp_t0_2 < 0x7FF) {
                var_ra_2 = temp_t0_2;
            } else {
                var_ra_2 = 0x7FF;
            }
            temp_t3 = temp_t4_2 / 8;
            var_t2_3 = temp_t3;
            if (temp_t3 <= 0) {
                var_t2_3 = 1;
            }
            if (temp_t3 <= 0) {
                var_a0_2 = 1;
            } else {
                var_a0_2 = temp_t3;
            }
            temp_a3_11 = temp_a3_10 + 8;
            temp_a3_12 = temp_a3_11 + 8;
            var_a3 = temp_a3_12 + 8;
            sp21C->unk4 = (s32) ((((s32) (var_t2_3 + 0x7FF) / var_a0_2) & 0xFFF) | 0x07000000 | ((var_ra_2 & 0xFFF) << 0xC));
            temp_a3_10->words.w0 = 0xE7000000;
            temp_a3_10->words.w1 = 0;
            temp_a3_11->words.w0 = sp30 | 0xF5100000;
            temp_a3_11->words.w1 = sp2C;
            temp_a3_12->words.w0 = 0xF2000000;
            temp_a3_12->words.w1 = sp28;
            if ((sp278 == 0) || (sp278 == 2)) {
                tex->flags |= 4;
            }
        }
        if (sp27C == 7) {
            temp_v0_3 = (sp268 & 3) << 0x12;
            temp_lo = temp_t5 * temp_s0;
            temp_a1_3 = (sp26C & 3) << 8;
            temp_v1_5 = (sp260 & 0xF) << 0xE;
            temp_a2_2 = (sp264 & 0xF) * 0x10;
            sp48 = tex + 0x80000020;
            temp_t9 = temp_v0_3 | 0x07000000 | temp_v1_5 | temp_a1_3 | temp_a2_2;
            sp34 = temp_t9;
            sp2C = temp_v0_3 | temp_v1_5 | temp_a1_3 | temp_a2_2;
            sp30 = temp_lo;
            sp28 = ((((temp_t5 - 1) * 4) & 0xFFF) << 0xC) | (((temp_s0 - 1) * 4) & 0xFFF);
            sp274 = (s32) temp_t5;
            sp248 = var_a3;
            temp_v0_4 = func_8007EF64(tex->ciPaletteOffset);
            var_a3->words.w0 = 0xFD500000;
            temp_a3_13 = var_a3 + 8;
            var_a3->words.w1 = (u32) sp48;
            temp_a3_13->words.w0 = 0xF5500000;
            temp_a3_14 = temp_a3_13 + 8;
            temp_a3_13->words.w1 = temp_t9;
            temp_t0_3 = ((s32) (temp_lo + 3) >> 2) - 1;
            temp_a3_15 = temp_a3_14 + 8;
            temp_a3_14->words.w0 = 0xE6000000;
            temp_a3_14->words.w1 = 0;
            temp_a3_15->words.w0 = 0xF3000000;
            temp_a3_16 = temp_a3_15 + 8;
            if (temp_t0_3 < 0x7FF) {
                var_a0_3 = temp_t0_3;
            } else {
                var_a0_3 = 0x7FF;
            }
            temp_t1 = (s32) temp_t5 / 16;
            temp_a3_17 = temp_a3_16 + 8;
            temp_a3_18 = temp_a3_17 + 8;
            temp_a3_19 = temp_a3_18 + 8;
            temp_a3_15->words.w1 = ((var_a0_3 & 0xFFF) << 0xC) | 0x07000000 | (((s32) (temp_t1 + 0x7FF) / temp_t1) & 0xFFF);
            temp_a3_16->words.w0 = 0xE7000000;
            temp_a3_16->words.w1 = 0;
            temp_a3_17->words.w0 = ((((s32) (((s32) temp_t5 >> 1) + 7) >> 3) & 0x1FF) << 9) | 0xF5400000;
            temp_a3_17->words.w1 = sp2C;
            temp_a3_18->words.w0 = 0xF2000000;
            temp_a3_18->words.w1 = sp28;
            temp_a3_20 = temp_a3_19 + 8;
            temp_a3_19->words.w0 = 0xFD100000;
            temp_a3_19->words.w1 = (u32) temp_v0_4;
            temp_a3_21 = temp_a3_20 + 8;
            temp_a3_20->words.w0 = 0xE8000000;
            temp_a3_20->words.w1 = 0;
            temp_a3_22 = temp_a3_21 + 8;
            temp_a3_21->words.w1 = 0x07000000;
            temp_a3_21->words.w0 = 0xF5000100;
            temp_a3_23 = temp_a3_22 + 8;
            temp_a3_22->words.w0 = 0xE6000000;
            temp_a3_22->words.w1 = 0;
            temp_a3_24 = temp_a3_23 + 8;
            temp_a3_23->words.w0 = 0xF0000000;
            temp_a3_23->words.w1 = 0x0703C000;
            temp_a3_24->words.w0 = 0xE7000000;
            temp_a3_24->words.w1 = 0;
            var_a3 = temp_a3_24 + 8;
            tex->flags |= 0x20;
            if ((sp278 == 0) || (sp278 == 2)) {
                tex->flags |= 4;
            }
        }
        if (sp27C == 4) {
            var_a3->words.w1 = (u32) (tex + 0x80000020);
            temp_a3_25 = var_a3 + 8;
            var_a3->words.w0 = 0xFD700000;
            temp_a3_25->words.w0 = 0xF5700000;
            temp_v0_5 = (sp268 & 3) << 0x12;
            temp_v1_6 = (sp260 & 0xF) << 0xE;
            temp_a1_4 = (sp26C & 3) << 8;
            temp_t7 = (sp264 & 0xF) * 0x10;
            temp_a3_26 = temp_a3_25 + 8;
            temp_a3_25->words.w1 = temp_v0_5 | 0x07000000 | temp_v1_6 | temp_a1_4 | temp_t7;
            temp_t4_3 = temp_t5 * 2;
            temp_a3_26->words.w0 = 0xE6000000;
            temp_a3_27 = temp_a3_26 + 8;
            temp_a3_26->words.w1 = 0;
            temp_a3_27->words.w0 = 0xF3000000;
            sp30 = (((s32) (temp_t4_3 + 7) >> 3) & 0x1FF) << 9;
            sp2C = temp_v0_5 | temp_v1_6 | temp_a1_4 | temp_t7;
            temp_t0_4 = (temp_t5 * temp_s0) - 1;
            sp28 = ((((temp_t5 - 1) * 4) & 0xFFF) << 0xC) | (((temp_s0 - 1) * 4) & 0xFFF);
            sp1CC = &temp_a3_27->words.w0;
            temp_a3_28 = temp_a3_27 + 8;
            temp_t3_2 = temp_t4_3 / 8;
            var_t2_4 = temp_t3_2;
            if (temp_t0_4 < 0x7FF) {
                var_ra_3 = temp_t0_4;
            } else {
                var_ra_3 = 0x7FF;
            }
            var_a0_4 = temp_t3_2;
            if (temp_t3_2 <= 0) {
                var_t2_4 = 1;
            }
            if (temp_t3_2 <= 0) {
                var_a0_4 = 1;
            }
            temp_a3_29 = temp_a3_28 + 8;
            temp_a3_30 = temp_a3_29 + 8;
            var_a3 = temp_a3_30 + 8;
            sp1CC->unk4 = (s32) ((((s32) (var_t2_4 + 0x7FF) / var_a0_4) & 0xFFF) | 0x07000000 | ((var_ra_3 & 0xFFF) << 0xC));
            temp_a3_28->words.w0 = 0xE7000000;
            temp_a3_28->words.w1 = 0;
            temp_a3_29->words.w0 = sp30 | 0xF5700000;
            temp_a3_29->words.w1 = sp2C;
            temp_a3_30->words.w0 = 0xF2000000;
            temp_a3_30->words.w1 = sp28;
            tex->flags |= 4;
        }
        if (sp27C == 5) {
            var_a3->words.w1 = (u32) (tex + 0x80000020);
            temp_a3_31 = var_a3 + 8;
            var_a3->words.w0 = 0xFD700000;
            temp_a3_31->words.w0 = 0xF5700000;
            temp_v0_6 = (sp268 & 3) << 0x12;
            temp_v1_7 = (sp260 & 0xF) << 0xE;
            temp_a1_5 = (sp26C & 3) << 8;
            temp_t9_2 = (sp264 & 0xF) * 0x10;
            temp_a3_32 = temp_a3_31 + 8;
            temp_a3_31->words.w1 = temp_v0_6 | 0x07000000 | temp_v1_7 | temp_a1_5 | temp_t9_2;
            temp_a3_33 = temp_a3_32 + 8;
            temp_a3_32->words.w0 = 0xE6000000;
            temp_a3_32->words.w1 = 0;
            temp_a3_33->words.w0 = 0xF3000000;
            sp2C = temp_v0_6 | temp_v1_7 | temp_a1_5 | temp_t9_2;
            temp_t0_5 = ((s32) ((temp_t5 * temp_s0) + 1) >> 1) - 1;
            sp28 = ((((temp_t5 - 1) * 4) & 0xFFF) << 0xC) | (((temp_s0 - 1) * 4) & 0xFFF);
            sp1B0 = &temp_a3_33->words.w0;
            temp_a3_34 = temp_a3_33 + 8;
            if (temp_t0_5 < 0x7FF) {
                var_ra_4 = temp_t0_5;
            } else {
                var_ra_4 = 0x7FF;
            }
            temp_t3_3 = (s32) temp_t5 / 8;
            var_t2_5 = temp_t3_3;
            if (temp_t3_3 <= 0) {
                var_t2_5 = 1;
            }
            if (temp_t3_3 <= 0) {
                var_a0_5 = 1;
            } else {
                var_a0_5 = temp_t3_3;
            }
            temp_a3_35 = temp_a3_34 + 8;
            temp_a3_36 = temp_a3_35 + 8;
            var_a3 = temp_a3_36 + 8;
            sp1B0->unk4 = (s32) ((((s32) (var_t2_5 + 0x7FF) / var_a0_5) & 0xFFF) | 0x07000000 | ((var_ra_4 & 0xFFF) << 0xC));
            temp_a3_34->words.w0 = 0xE7000000;
            temp_a3_34->words.w1 = 0;
            temp_a3_35->words.w0 = ((((s32) (temp_t5 + 7) >> 3) & 0x1FF) << 9) | 0xF5680000;
            temp_a3_35->words.w1 = sp2C;
            temp_a3_36->words.w0 = 0xF2000000;
            temp_a3_36->words.w1 = sp28;
            tex->flags |= 4;
        }
        if (sp27C == 6) {
            var_a3->words.w1 = (u32) (tex + 0x80000020);
            temp_a3_37 = var_a3 + 8;
            var_a3->words.w0 = 0xFD700000;
            temp_a3_37->words.w0 = 0xF5700000;
            temp_v0_7 = (sp268 & 3) << 0x12;
            temp_v1_8 = (sp260 & 0xF) << 0xE;
            temp_a1_6 = (sp26C & 3) << 8;
            temp_t6_3 = (sp264 & 0xF) * 0x10;
            temp_a3_38 = temp_a3_37 + 8;
            temp_a3_37->words.w1 = temp_v0_7 | 0x07000000 | temp_v1_8 | temp_a1_6 | temp_t6_3;
            temp_a3_39 = temp_a3_38 + 8;
            temp_a3_38->words.w0 = 0xE6000000;
            temp_a3_38->words.w1 = 0;
            temp_a3_39->words.w0 = 0xF3000000;
            sp2C = temp_v0_7 | temp_v1_8 | temp_a1_6 | temp_t6_3;
            temp_t0_6 = ((s32) ((temp_t5 * temp_s0) + 3) >> 2) - 1;
            sp28 = ((((temp_t5 - 1) * 4) & 0xFFF) << 0xC) | (((temp_s0 - 1) * 4) & 0xFFF);
            temp_a3_40 = temp_a3_39 + 8;
            temp_t1_2 = (s32) temp_t5 / 16;
            temp_a3_41 = temp_a3_40 + 8;
            var_a0_6 = 0x7FF;
            sp30 = ((s32) (temp_t1_2 + 0x7FF) / temp_t1_2) & 0xFFF;
            if (temp_t0_6 < 0x7FF) {
                var_a0_6 = temp_t0_6;
            }
            temp_a3_39->words.w1 = ((var_a0_6 & 0xFFF) << 0xC) | 0x07000000 | sp30;
            temp_a3_40->words.w0 = 0xE7000000;
            temp_a3_40->words.w1 = 0;
            temp_a3_41->words.w0 = ((((s32) (((s32) temp_t5 >> 1) + 7) >> 3) & 0x1FF) << 9) | 0xF5600000;
            temp_a3_42 = temp_a3_41 + 8;
            temp_a3_41->words.w1 = sp2C;
            temp_a3_42->words.w0 = 0xF2000000;
            var_a3 = temp_a3_42 + 8;
            temp_a3_42->words.w1 = sp28;
            tex->flags |= 4;
        }
        if (sp27C == 2) {
            var_a3->words.w1 = (u32) (tex + 0x80000020);
            temp_a3_43 = var_a3 + 8;
            var_a3->words.w0 = 0xFD900000;
            temp_a3_43->words.w0 = 0xF5900000;
            temp_v0_8 = (sp268 & 3) << 0x12;
            temp_v1_9 = (sp260 & 0xF) << 0xE;
            temp_a1_7 = (sp26C & 3) << 8;
            temp_t6_4 = (sp264 & 0xF) * 0x10;
            temp_a3_44 = temp_a3_43 + 8;
            temp_a3_43->words.w1 = temp_v0_8 | 0x07000000 | temp_v1_9 | temp_a1_7 | temp_t6_4;
            temp_a3_45 = temp_a3_44 + 8;
            temp_a3_44->words.w0 = 0xE6000000;
            temp_a3_44->words.w1 = 0;
            temp_a3_45->words.w0 = 0xF3000000;
            sp2C = temp_v0_8 | temp_v1_9 | temp_a1_7 | temp_t6_4;
            temp_t0_7 = ((s32) ((temp_t5 * temp_s0) + 1) >> 1) - 1;
            sp28 = ((((temp_t5 - 1) * 4) & 0xFFF) << 0xC) | (((temp_s0 - 1) * 4) & 0xFFF);
            temp_t8 = (((s32) (temp_t5 + 7) >> 3) & 0x1FF) << 9;
            sp24 = temp_t8;
            sp178 = &temp_a3_45->words.w0;
            temp_a3_46 = temp_a3_45 + 8;
            temp_t3_4 = (s32) temp_t5 / 8;
            if (temp_t0_7 < 0x7FF) {
                var_ra_5 = temp_t0_7;
            } else {
                var_ra_5 = 0x7FF;
            }
            var_t2_6 = temp_t3_4;
            if (temp_t3_4 <= 0) {
                var_t2_6 = 1;
            }
            if (temp_t3_4 <= 0) {
                var_a0_7 = 1;
            } else {
                var_a0_7 = temp_t3_4;
            }
            temp_a3_47 = temp_a3_46 + 8;
            temp_a3_48 = temp_a3_47 + 8;
            var_a3 = temp_a3_48 + 8;
            sp178->unk4 = (s32) ((((s32) (var_t2_6 + 0x7FF) / var_a0_7) & 0xFFF) | 0x07000000 | ((var_ra_5 & 0xFFF) << 0xC));
            temp_a3_46->words.w0 = 0xE7000000;
            temp_a3_46->words.w1 = 0;
            temp_a3_47->words.w0 = temp_t8 | 0xF5880000;
            temp_a3_47->words.w1 = sp2C;
            temp_a3_48->words.w0 = 0xF2000000;
            temp_a3_48->words.w1 = sp28;
        }
        if (sp27C == 3) {
            var_a3->words.w1 = (u32) (tex + 0x80000020);
            temp_a3_49 = var_a3 + 8;
            var_a3->words.w0 = 0xFD900000;
            temp_a3_49->words.w0 = 0xF5900000;
            temp_v0_9 = (sp268 & 3) << 0x12;
            temp_v1_10 = (sp260 & 0xF) << 0xE;
            temp_a1_8 = (sp26C & 3) << 8;
            temp_t8_2 = (sp264 & 0xF) * 0x10;
            temp_a3_50 = temp_a3_49 + 8;
            temp_a3_49->words.w1 = temp_v0_9 | 0x07000000 | temp_v1_10 | temp_a1_8 | temp_t8_2;
            temp_a3_51 = temp_a3_50 + 8;
            temp_a3_50->words.w0 = 0xE6000000;
            temp_a3_50->words.w1 = 0;
            temp_a3_51->words.w0 = 0xF3000000;
            sp2C = temp_v0_9 | temp_v1_10 | temp_a1_8 | temp_t8_2;
            temp_t0_8 = ((s32) ((temp_t5 * temp_s0) + 3) >> 2) - 1;
            sp28 = ((((temp_t5 - 1) * 4) & 0xFFF) << 0xC) | (((temp_s0 - 1) * 4) & 0xFFF);
            temp_a3_52 = temp_a3_51 + 8;
            temp_t1_3 = (s32) temp_t5 / 16;
            temp_a3_53 = temp_a3_52 + 8;
            var_a0_8 = 0x7FF;
            sp30 = ((s32) (temp_t1_3 + 0x7FF) / temp_t1_3) & 0xFFF;
            if (temp_t0_8 < 0x7FF) {
                var_a0_8 = temp_t0_8;
            }
            temp_a3_51->words.w1 = ((var_a0_8 & 0xFFF) << 0xC) | 0x07000000 | sp30;
            temp_a3_52->words.w0 = 0xE7000000;
            temp_a3_52->words.w1 = 0;
            temp_a3_53->words.w0 = ((((s32) (((s32) temp_t5 >> 1) + 7) >> 3) & 0x1FF) << 9) | 0xF5800000;
            temp_a3_54 = temp_a3_53 + 8;
            temp_a3_53->words.w1 = sp2C;
            temp_a3_54->words.w0 = 0xF2000000;
            var_a3 = temp_a3_54 + 8;
            temp_a3_54->words.w1 = sp28;
        }
        tex->numberOfCommands = (s16) ((s32) (var_a3 - tex->cmd) >> 3);
        return;
    }
    sp264 = var_t2;
    sp260 = var_t3;
    sp27C = temp_t4;
    if (temp_t4 == 0) {
        temp_a3_55 = dlist + 8;
        dlist->words.w0 = 0xFD180000;
        dlist->words.w1 = (u32) (tex + 0x80000020);
        temp_a3_55->words.w0 = 0xF5180000;
        temp_v0_10 = (sp268 & 3) << 0x12;
        temp_v1_11 = (sp260 & 0xF) << 0xE;
        temp_a1_9 = (sp26C & 3) << 8;
        temp_a2_3 = (sp264 & 0xF) * 0x10;
        temp_a3_56 = temp_a3_55 + 8;
        temp_a3_55->words.w1 = temp_v0_10 | 0x07000000 | temp_v1_11 | temp_a1_9 | temp_a2_3;
        temp_t0_9 = (temp_t5 * temp_s0) - 1;
        temp_a3_57 = temp_a3_56 + 8;
        temp_a3_56->words.w0 = 0xE6000000;
        temp_a3_56->words.w1 = 0;
        temp_a3_57->words.w0 = 0xF3000000;
        temp_a3_58 = temp_a3_57 + 8;
        if (temp_t0_9 < 0x7FF) {
            var_a0_9 = temp_t0_9;
        } else {
            var_a0_9 = 0x7FF;
        }
        temp_a3_57->words.w1 = ((var_a0_9 & 0xFFF) << 0xC) | 0x07000000;
        temp_a3_58->words.w0 = 0xE7000000;
        temp_a3_59 = temp_a3_58 + 8;
        temp_a3_58->words.w1 = 0;
        temp_a3_59->words.w1 = temp_v0_10 | temp_v1_11 | temp_a1_9 | temp_a2_3;
        temp_a3_59->words.w0 = ((((s32) ((temp_t5 * 2) + 7) >> 3) & 0x1FF) << 9) | 0xF5180000;
        temp_a3_60 = temp_a3_59 + 8;
        temp_a3_60->words.w0 = 0xF2000000;
        temp_a3_60->words.w1 = ((((temp_t5 - 1) * 4) & 0xFFF) << 0xC) | (((temp_s0 - 1) * 4) & 0xFFF);
        var_a3 = temp_a3_60 + 8;
        if ((sp278 == 0) || (sp278 == 2)) {
            tex->flags |= 4;
        }
    }
    if (sp27C == 1) {
        temp_a3_61 = var_a3 + 8;
        var_a3->words.w0 = 0xFD100000;
        var_a3->words.w1 = (u32) (tex + 0x80000020);
        temp_a3_61->words.w0 = 0xF5100000;
        temp_v0_11 = (sp268 & 3) << 0x12;
        temp_v1_12 = (sp260 & 0xF) << 0xE;
        temp_a1_10 = (sp26C & 3) << 8;
        temp_a2_4 = (sp264 & 0xF) * 0x10;
        temp_a3_62 = temp_a3_61 + 8;
        temp_a3_61->words.w1 = temp_v0_11 | 0x07000000 | temp_v1_12 | temp_a1_10 | temp_a2_4;
        temp_a3_62->words.w0 = 0xE6000000;
        temp_a3_63 = temp_a3_62 + 8;
        temp_a3_62->words.w1 = 0;
        temp_a3_63->words.w0 = 0xF3000000;
        sp30 = (((s32) ((temp_t5 * 2) + 7) >> 3) & 0x1FF) << 9;
        sp2C = temp_v0_11 | temp_v1_12 | temp_a1_10 | temp_a2_4;
        temp_t0_10 = (temp_t5 * temp_s0) - 1;
        sp28 = ((((temp_t5 - 1) * 4) & 0xFFF) << 0xC) | (((temp_s0 - 1) * 4) & 0xFFF);
        temp_a3_64 = temp_a3_63 + 8;
        if (temp_t0_10 < 0x7FF) {
            var_a0_10 = temp_t0_10;
        } else {
            var_a0_10 = 0x7FF;
        }
        temp_a3_63->words.w1 = ((var_a0_10 & 0xFFF) << 0xC) | 0x07000000;
        temp_a3_64->words.w0 = 0xE7000000;
        temp_a3_64->words.w1 = 0;
        temp_a3_65 = temp_a3_64 + 8;
        temp_a3_65->words.w0 = sp30 | 0xF5100000;
        temp_a3_66 = temp_a3_65 + 8;
        temp_a3_65->words.w1 = sp2C;
        temp_a3_66->words.w0 = 0xF2000000;
        var_a3 = temp_a3_66 + 8;
        temp_a3_66->words.w1 = sp28;
        if ((sp278 == 0) || (sp278 == 2)) {
            tex->flags |= 4;
        }
    }
    if (sp27C == 7) {
        temp_v0_12 = (sp268 & 3) << 0x12;
        temp_lo_2 = temp_t5 * temp_s0;
        temp_a1_11 = (sp26C & 3) << 8;
        temp_v1_13 = (sp260 & 0xF) << 0xE;
        temp_a2_5 = (sp264 & 0xF) * 0x10;
        sp48 = tex + 0x80000020;
        temp_t7_2 = temp_v0_12 | 0x07000000 | temp_v1_13 | temp_a1_11 | temp_a2_5;
        sp34 = temp_t7_2;
        sp2C = temp_v0_12 | temp_v1_13 | temp_a1_11 | temp_a2_5;
        sp30 = temp_lo_2;
        sp28 = ((((temp_t5 - 1) * 4) & 0xFFF) << 0xC) | (((temp_s0 - 1) * 4) & 0xFFF);
        sp274 = (s32) temp_t5;
        sp248 = var_a3;
        temp_v0_13 = func_8007EF64(tex->ciPaletteOffset);
        var_a3->words.w0 = 0xFD500000;
        temp_a3_67 = var_a3 + 8;
        var_a3->words.w1 = (u32) sp48;
        temp_a3_67->words.w0 = 0xF5500000;
        temp_a3_68 = temp_a3_67 + 8;
        temp_a3_67->words.w1 = temp_t7_2;
        temp_t0_11 = ((s32) (temp_lo_2 + 3) >> 2) - 1;
        temp_a3_69 = temp_a3_68 + 8;
        temp_a3_68->words.w0 = 0xE6000000;
        temp_a3_68->words.w1 = 0;
        temp_a3_69->words.w0 = 0xF3000000;
        temp_a3_70 = temp_a3_69 + 8;
        if (temp_t0_11 < 0x7FF) {
            var_a0_11 = temp_t0_11;
        } else {
            var_a0_11 = 0x7FF;
        }
        temp_a3_69->words.w1 = ((var_a0_11 & 0xFFF) << 0xC) | 0x07000000;
        temp_a3_70->words.w0 = 0xE7000000;
        temp_a3_71 = temp_a3_70 + 8;
        temp_a3_70->words.w1 = 0;
        temp_a3_71->words.w0 = ((((s32) (((s32) temp_t5 >> 1) + 7) >> 3) & 0x1FF) << 9) | 0xF5400000;
        temp_a3_72 = temp_a3_71 + 8;
        temp_a3_71->words.w1 = sp2C;
        temp_a3_72->words.w0 = 0xF2000000;
        temp_a3_73 = temp_a3_72 + 8;
        temp_a3_72->words.w1 = sp28;
        temp_a3_74 = temp_a3_73 + 8;
        temp_a3_73->words.w0 = 0xFD100000;
        temp_a3_75 = temp_a3_74 + 8;
        temp_a3_73->words.w1 = (u32) temp_v0_13;
        temp_a3_74->words.w0 = 0xE8000000;
        temp_a3_74->words.w1 = 0;
        temp_a3_76 = temp_a3_75 + 8;
        temp_a3_75->words.w1 = 0x07000000;
        temp_a3_75->words.w0 = 0xF5000100;
        temp_a3_77 = temp_a3_76 + 8;
        temp_a3_76->words.w0 = 0xE6000000;
        temp_a3_76->words.w1 = 0;
        temp_a3_78 = temp_a3_77 + 8;
        temp_a3_77->words.w0 = 0xF0000000;
        temp_a3_77->words.w1 = 0x0703C000;
        temp_a3_78->words.w0 = 0xE7000000;
        temp_a3_78->words.w1 = 0;
        var_a3 = temp_a3_78 + 8;
        tex->flags |= 0x20;
        if ((sp278 == 0) || (sp278 == 2)) {
            tex->flags |= 4;
        }
    }
    if (sp27C == 4) {
        temp_a3_79 = var_a3 + 8;
        var_a3->words.w0 = 0xFD700000;
        var_a3->words.w1 = (u32) (tex + 0x80000020);
        temp_a3_79->words.w0 = 0xF5700000;
        temp_v0_14 = (sp268 & 3) << 0x12;
        temp_v1_14 = (sp260 & 0xF) << 0xE;
        temp_a1_12 = (sp26C & 3) << 8;
        temp_a2_6 = (sp264 & 0xF) * 0x10;
        temp_a3_80 = temp_a3_79 + 8;
        temp_a3_79->words.w1 = temp_v0_14 | 0x07000000 | temp_v1_14 | temp_a1_12 | temp_a2_6;
        temp_a3_80->words.w0 = 0xE6000000;
        temp_a3_81 = temp_a3_80 + 8;
        temp_a3_80->words.w1 = 0;
        temp_a3_81->words.w0 = 0xF3000000;
        sp30 = (((s32) ((temp_t5 * 2) + 7) >> 3) & 0x1FF) << 9;
        sp2C = temp_v0_14 | temp_v1_14 | temp_a1_12 | temp_a2_6;
        temp_t0_12 = (temp_t5 * temp_s0) - 1;
        sp28 = ((((temp_t5 - 1) * 4) & 0xFFF) << 0xC) | (((temp_s0 - 1) * 4) & 0xFFF);
        temp_a3_82 = temp_a3_81 + 8;
        if (temp_t0_12 < 0x7FF) {
            var_a0_12 = temp_t0_12;
        } else {
            var_a0_12 = 0x7FF;
        }
        temp_a3_81->words.w1 = ((var_a0_12 & 0xFFF) << 0xC) | 0x07000000;
        temp_a3_82->words.w0 = 0xE7000000;
        temp_a3_82->words.w1 = 0;
        temp_a3_83 = temp_a3_82 + 8;
        temp_a3_83->words.w0 = sp30 | 0xF5700000;
        temp_a3_84 = temp_a3_83 + 8;
        temp_a3_83->words.w1 = sp2C;
        temp_a3_84->words.w0 = 0xF2000000;
        var_a3 = temp_a3_84 + 8;
        temp_a3_84->words.w1 = sp28;
        tex->flags |= 4;
    }
    if (sp27C == 5) {
        temp_a3_85 = var_a3 + 8;
        var_a3->words.w0 = 0xFD700000;
        var_a3->words.w1 = (u32) (tex + 0x80000020);
        temp_a3_85->words.w0 = 0xF5700000;
        temp_v0_15 = (sp268 & 3) << 0x12;
        temp_v1_15 = (sp260 & 0xF) << 0xE;
        temp_a1_13 = (sp26C & 3) << 8;
        temp_a2_7 = (sp264 & 0xF) * 0x10;
        temp_a3_86 = temp_a3_85 + 8;
        temp_a3_85->words.w1 = temp_v0_15 | 0x07000000 | temp_v1_15 | temp_a1_13 | temp_a2_7;
        temp_a3_87 = temp_a3_86 + 8;
        temp_a3_86->words.w0 = 0xE6000000;
        temp_a3_86->words.w1 = 0;
        temp_a3_87->words.w0 = 0xF3000000;
        sp2C = temp_v0_15 | temp_v1_15 | temp_a1_13 | temp_a2_7;
        temp_t0_13 = ((s32) ((temp_t5 * temp_s0) + 1) >> 1) - 1;
        sp28 = ((((temp_t5 - 1) * 4) & 0xFFF) << 0xC) | (((temp_s0 - 1) * 4) & 0xFFF);
        temp_a3_88 = temp_a3_87 + 8;
        if (temp_t0_13 < 0x7FF) {
            var_a0_13 = temp_t0_13;
        } else {
            var_a0_13 = 0x7FF;
        }
        temp_a3_87->words.w1 = ((var_a0_13 & 0xFFF) << 0xC) | 0x07000000;
        temp_a3_88->words.w0 = 0xE7000000;
        temp_a3_89 = temp_a3_88 + 8;
        temp_a3_88->words.w1 = 0;
        temp_a3_89->words.w0 = ((((s32) (temp_t5 + 7) >> 3) & 0x1FF) << 9) | 0xF5680000;
        temp_a3_90 = temp_a3_89 + 8;
        temp_a3_89->words.w1 = sp2C;
        temp_a3_90->words.w0 = 0xF2000000;
        var_a3 = temp_a3_90 + 8;
        temp_a3_90->words.w1 = sp28;
        tex->flags |= 4;
    }
    if (sp27C == 6) {
        temp_a3_91 = var_a3 + 8;
        var_a3->words.w0 = 0xFD700000;
        var_a3->words.w1 = (u32) (tex + 0x80000020);
        temp_a3_91->words.w0 = 0xF5700000;
        temp_v0_16 = (sp268 & 3) << 0x12;
        temp_v1_16 = (sp260 & 0xF) << 0xE;
        temp_a1_14 = (sp26C & 3) << 8;
        temp_a2_8 = (sp264 & 0xF) * 0x10;
        temp_a3_92 = temp_a3_91 + 8;
        temp_a3_91->words.w1 = temp_v0_16 | 0x07000000 | temp_v1_16 | temp_a1_14 | temp_a2_8;
        temp_a3_93 = temp_a3_92 + 8;
        temp_a3_92->words.w0 = 0xE6000000;
        temp_a3_92->words.w1 = 0;
        temp_a3_93->words.w0 = 0xF3000000;
        sp2C = temp_v0_16 | temp_v1_16 | temp_a1_14 | temp_a2_8;
        temp_t0_14 = ((s32) ((temp_t5 * temp_s0) + 3) >> 2) - 1;
        sp28 = ((((temp_t5 - 1) * 4) & 0xFFF) << 0xC) | (((temp_s0 - 1) * 4) & 0xFFF);
        temp_a3_94 = temp_a3_93 + 8;
        if (temp_t0_14 < 0x7FF) {
            var_a0_14 = temp_t0_14;
        } else {
            var_a0_14 = 0x7FF;
        }
        temp_a3_93->words.w1 = ((var_a0_14 & 0xFFF) << 0xC) | 0x07000000;
        temp_a3_95 = temp_a3_94 + 8;
        temp_a3_94->words.w0 = 0xE7000000;
        temp_a3_94->words.w1 = 0;
        temp_a3_95->words.w0 = ((((s32) (((s32) temp_t5 >> 1) + 7) >> 3) & 0x1FF) << 9) | 0xF5600000;
        temp_a3_96 = temp_a3_95 + 8;
        temp_a3_95->words.w1 = sp2C;
        temp_a3_96->words.w0 = 0xF2000000;
        var_a3 = temp_a3_96 + 8;
        temp_a3_96->words.w1 = sp28;
        tex->flags |= 4;
    }
    if (sp27C == 2) {
        temp_a3_97 = var_a3 + 8;
        var_a3->words.w0 = 0xFD900000;
        var_a3->words.w1 = (u32) (tex + 0x80000020);
        temp_a3_97->words.w0 = 0xF5900000;
        temp_v0_17 = (sp268 & 3) << 0x12;
        temp_v1_17 = (sp260 & 0xF) << 0xE;
        temp_a1_15 = (sp26C & 3) << 8;
        temp_a2_9 = (sp264 & 0xF) * 0x10;
        temp_a3_98 = temp_a3_97 + 8;
        temp_a3_97->words.w1 = temp_v0_17 | 0x07000000 | temp_v1_17 | temp_a1_15 | temp_a2_9;
        temp_a3_99 = temp_a3_98 + 8;
        temp_a3_98->words.w0 = 0xE6000000;
        temp_a3_98->words.w1 = 0;
        temp_a3_99->words.w0 = 0xF3000000;
        sp2C = temp_v0_17 | temp_v1_17 | temp_a1_15 | temp_a2_9;
        temp_t0_15 = ((s32) ((temp_t5 * temp_s0) + 1) >> 1) - 1;
        sp28 = ((((temp_t5 - 1) * 4) & 0xFFF) << 0xC) | (((temp_s0 - 1) * 4) & 0xFFF);
        temp_a3_100 = temp_a3_99 + 8;
        if (temp_t0_15 < 0x7FF) {
            var_a0_15 = temp_t0_15;
        } else {
            var_a0_15 = 0x7FF;
        }
        temp_a3_99->words.w1 = ((var_a0_15 & 0xFFF) << 0xC) | 0x07000000;
        temp_a3_101 = temp_a3_100 + 8;
        temp_a3_100->words.w0 = 0xE7000000;
        temp_a3_100->words.w1 = 0;
        temp_a3_101->words.w0 = ((((s32) (temp_t5 + 7) >> 3) & 0x1FF) << 9) | 0xF5880000;
        temp_a3_102 = temp_a3_101 + 8;
        temp_a3_101->words.w1 = sp2C;
        temp_a3_102->words.w0 = 0xF2000000;
        var_a3 = temp_a3_102 + 8;
        temp_a3_102->words.w1 = sp28;
    }
    if (sp27C == 3) {
        temp_a3_103 = var_a3 + 8;
        var_a3->words.w0 = 0xFD900000;
        var_a3->words.w1 = (u32) (tex + 0x80000020);
        temp_a3_103->words.w0 = 0xF5900000;
        temp_v0_18 = (sp268 & 3) << 0x12;
        temp_v1_18 = (sp260 & 0xF) << 0xE;
        temp_a1_16 = (sp26C & 3) << 8;
        temp_a2_10 = (sp264 & 0xF) * 0x10;
        temp_a3_104 = temp_a3_103 + 8;
        temp_a3_103->words.w1 = temp_v0_18 | 0x07000000 | temp_v1_18 | temp_a1_16 | temp_a2_10;
        temp_a3_105 = temp_a3_104 + 8;
        temp_a3_104->words.w0 = 0xE6000000;
        temp_a3_104->words.w1 = 0;
        temp_a3_105->words.w0 = 0xF3000000;
        sp2C = temp_v0_18 | temp_v1_18 | temp_a1_16 | temp_a2_10;
        temp_t0_16 = ((s32) ((temp_t5 * temp_s0) + 3) >> 2) - 1;
        sp28 = ((((temp_t5 - 1) * 4) & 0xFFF) << 0xC) | (((temp_s0 - 1) * 4) & 0xFFF);
        temp_a3_106 = temp_a3_105 + 8;
        if (temp_t0_16 < 0x7FF) {
            var_a0_16 = temp_t0_16;
        } else {
            var_a0_16 = 0x7FF;
        }
        temp_a3_105->words.w1 = ((var_a0_16 & 0xFFF) << 0xC) | 0x07000000;
        temp_a3_107 = temp_a3_106 + 8;
        temp_a3_106->words.w0 = 0xE7000000;
        temp_a3_106->words.w1 = 0;
        temp_a3_107->words.w0 = ((((s32) (((s32) temp_t5 >> 1) + 7) >> 3) & 0x1FF) << 9) | 0xF5800000;
        temp_a3_108 = temp_a3_107 + 8;
        temp_a3_107->words.w1 = sp2C;
        temp_a3_108->words.w0 = 0xF2000000;
        var_a3 = temp_a3_108 + 8;
        temp_a3_108->words.w1 = sp28;
    }
    tex->numberOfCommands = (s16) ((s32) (var_a3 - tex->cmd) >> 3);
}
