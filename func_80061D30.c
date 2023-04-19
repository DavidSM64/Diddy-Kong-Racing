#include "ctx.c"

? func_80061D30(void *arg0) {
    s16 *temp_s1;
    s16 *var_t5;
    s16 *var_t5_2;
    s16 *var_t5_3;
    s16 *var_t5_5;
    s16 temp_t0;
    s16 temp_t0_2;
    s16 temp_t0_3;
    s16 temp_v0;
    s16 temp_v0_5;
    s16 var_s0;
    s16 var_t2;
    s16 var_t9;
    s32 temp_t0_4;
    s32 temp_t1_3;
    s32 temp_t2_2;
    s32 temp_t3;
    s32 temp_t3_2;
    s32 temp_t3_4;
    s32 temp_t3_5;
    s32 temp_t4;
    s32 temp_t8;
    s32 temp_v0_2;
    s32 temp_v0_6;
    s32 var_t5_4;
    s8 *var_t6_3;
    s8 temp_t1;
    s8 temp_t1_2;
    s8 temp_t2;
    s8 temp_v0_4;
    s8 var_a3;
    s8 var_t0;
    u32 temp_lo;
    u32 var_a0;
    void *temp_a1;
    void *temp_a2;
    void *temp_t0_5;
    void *temp_t1_4;
    void *temp_t3_3;
    void *temp_t3_6;
    void *temp_v0_3;
    void *temp_v1;
    void *var_t2_2;
    void *var_t2_3;
    void *var_t6;
    void *var_t6_2;
    void *var_t6_4;
    void *var_t6_5;
    void *var_t6_6;
    void *var_t7;

    var_t0 = arg0->unk3A;
    if (var_t0 < 0) {
        var_t0 = 0;
    }
    temp_t2 = arg0->unk40->unk55;
    if (var_t0 >= temp_t2) {
        var_t0 = temp_t2;
    }
    temp_a1 = *(arg0->unk68 + (var_t0 * 4));
    temp_a2 = temp_a1->unk0;
    if (temp_a2->unk44 == 0) {
        return 0;
    }
    var_t9 = arg0->unk18;
    var_a3 = arg0->unk3B;
    if ((var_t9 == temp_a1->unk14) && (var_a3 == temp_a1->unk10)) {
        return 0;
    }
    if (var_a3 < 0) {
        var_a3 = 0;
    }
    temp_t0 = temp_a2->unk48;
    if (var_a3 >= temp_t0) {
        var_a3 = temp_t0 - 1;
    }
    var_t2 = 0;
    if (temp_t0 > 0) {
        var_t2 = (temp_a2->unk44 + (var_a3 * 8))->unk4 - 2;
    }
    var_a0 = (u32) var_t9 >> 4;
    if ((s32) var_a0 < 0) {
        var_t9 = var_t2;
        var_a0 = (u32) var_t2 >> 4;
    }
    if (var_t2 < (s32) var_a0) {
        var_t9 = 0;
        var_a0 = 0;
        temp_a1->unk10 = -1;
    }
    temp_s1 = temp_a1->unkC;
    if (var_a3 != temp_a1->unk10) {
        var_s0 = -1;
    } else {
        var_s0 = temp_a1->unk12;
    }
    temp_a1->unk10 = (s16) var_a3;
    temp_a1->unk14 = var_t9;
    temp_a1->unk12 = (s16) var_a0;
    temp_t8 = var_t9 & 0xF;
    if ((var_a0 != 0) && (var_s0 != -1)) {

    } else {
        var_t5 = temp_a2->unk4C;
        var_t7 = temp_a2->unk4;
        temp_t3 = var_t5 + (temp_a2->unk24 * 2);
        do {
            temp_v0 = *var_t5;
            if (temp_v0 != -1) {
                temp_v0_2 = temp_v0 * 6;
                temp_v1 = temp_s1 + temp_v0_2;
                temp_v0_3 = *(temp_a2->unk44 + (var_a3 * 8)) + 0xC + temp_v0_2;
                temp_v1->unk0 = (s16) (var_t7->unk0 + temp_v0_3->unk0);
                temp_v1->unk2 = (s16) (var_t7->unk2 + temp_v0_3->unk2);
                temp_v1->unk4 = (s16) (var_t7->unk4 + temp_v0_3->unk4);
            }
            var_t5 += 2;
            var_t7 += 0xA;
        } while ((s32) var_t5 < temp_t3);
        var_s0 = 0;
    }
    temp_t4 = (temp_a2->unk4A * 3) + 0xC;
    if (var_s0 < (s32) var_a0) {
        var_t2_2 = *(temp_a2->unk44 + (var_a3 * 8)) + (temp_t4 * (var_s0 + 2));
        do {
            var_t6 = var_t2_2;
            var_t5_2 = temp_s1;
            var_t2_2 += temp_t4;
            temp_t3_2 = var_t5_2 + (temp_a2->unk4A * 6);
loop_33:
            temp_t0_2 = *var_t5_2;
            var_t5_2 += 6;
            var_t5_2->unk-6 = (s16) (temp_t0_2 + var_t6->unk0);
            temp_t1 = var_t6->unk1;
            var_t6 += 3;
            var_t5_2->unk-4 = (s16) (var_t5_2->unk-4 + temp_t1);
            var_t5_2->unk-2 = (s16) (var_t5_2->unk-2 + var_t6->unk-1);
            if ((s32) var_t5_2 < temp_t3_2) {
                goto loop_33;
            }
            var_s0 += 1;
        } while (var_s0 < (s32) var_a0);
    }
    if ((s32) var_a0 < var_s0) {
        var_t2_3 = *(temp_a2->unk44 + (var_a3 * 8)) + (temp_t4 * (var_s0 + 2));
        do {
            var_t2_3 -= temp_t4;
            var_t5_3 = temp_s1;
            var_s0 -= 1;
            var_t6_2 = var_t2_3;
            temp_t3_3 = var_t5_3 + (temp_a2->unk4A * 6);
loop_38:
            temp_t0_3 = *var_t5_3;
            var_t5_3 += 6;
            var_t5_3->unk-6 = (s16) (temp_t0_3 - var_t6_2->unk0);
            temp_t1_2 = var_t6_2->unk1;
            var_t6_2 += 3;
            var_t5_3->unk-4 = (s16) (var_t5_3->unk-4 - temp_t1_2);
            var_t5_3->unk-2 = (s16) (var_t5_3->unk-2 - var_t6_2->unk-1);
            if ((s32) var_t5_3 < (s32) temp_t3_3) {
                goto loop_38;
            }
        } while ((s32) var_a0 < var_s0);
    }
    var_t5_4 = D_8011D644;
    var_t6_3 = *(temp_a2->unk44 + (var_a3 * 8)) + (temp_t4 * (var_s0 + 2));
    temp_t3_4 = var_t5_4 + (temp_a2->unk4A * 6);
    do {
        var_t5_4 += 6;
        temp_lo = *var_t6_3 * temp_t8;
        var_t6_3 += 3;
        var_t5_4->unk-6 = (s16) (temp_lo >> 4);
        var_t5_4->unk-4 = (s16) ((u32) (var_t6_3->unk-2 * temp_t8) >> 4);
        var_t5_4->unk-2 = (s16) ((u32) (var_t6_3->unk-1 * temp_t8) >> 4);
    } while (var_t5_4 < temp_t3_4);
    var_t6_4 = *(temp_a2->unk44 + (var_a3 * 8));
    if (var_a0 != 0) {
        var_t6_4 = (var_t6_4 + (temp_t4 * (var_a0 + 1))) - 0xC;
    }
    temp_t0_4 = (var_t6_4->unk0 << 8) | var_t6_4->unk1;
    temp_t1_3 = (var_t6_4->unk2 << 8) | var_t6_4->unk3;
    temp_t2_2 = (var_t6_4->unk4 << 8) | var_t6_4->unk5;
    var_t6_5 = var_t6_4 + temp_t4;
    temp_t3_5 = (var_t6_4->unkA << 8) | var_t6_4->unkB;
    if (var_a0 == 0) {
        var_t6_5 = (var_t6_5 + temp_t4) - 0xC;
    }
    temp_a1->unk16 = (s16) (temp_t0_4 + ((u32) ((((var_t6_5->unk0 << 8) | var_t6_5->unk1) - temp_t0_4) * temp_t8) >> 4));
    temp_a1->unk18 = (s16) (temp_t1_3 + ((u32) ((((var_t6_5->unk2 << 8) | var_t6_5->unk3) - temp_t1_3) * temp_t8) >> 4));
    temp_a1->unk1A = (s16) (temp_t2_2 + ((u32) ((((var_t6_5->unk4 << 8) | var_t6_5->unk5) - temp_t2_2) * temp_t8) >> 4));
    temp_a1->unk1C = (s16) (temp_t3_5 + ((u32) ((((var_t6_5->unkA << 8) | var_t6_5->unkB) - temp_t3_5) * temp_t8) >> 4));
    temp_v0_4 = temp_a1->unk1F ^ 1;
    temp_a1->unk1F = temp_v0_4;
    var_t5_5 = temp_a2->unk4C;
    var_t6_6 = *(temp_a1 + 4 + (temp_v0_4 * 4));
    temp_t3_6 = var_t5_5 + (temp_a2->unk24 * 2);
    do {
        temp_v0_5 = *var_t5_5;
        var_t5_5 += 2;
        if (temp_v0_5 != -1) {
            temp_v0_6 = temp_v0_5 * 6;
            temp_t1_4 = D_8011D644 + temp_v0_6;
            temp_t0_5 = temp_s1 + temp_v0_6;
            var_t6_6->unk0 = (s16) (temp_t0_5->unk0 + temp_t1_4->unk0);
            var_t6_6->unk2 = (s16) (temp_t0_5->unk2 + temp_t1_4->unk2);
            var_t6_6->unk4 = (s16) (temp_t0_5->unk4 + temp_t1_4->unk4);
        }
        var_t6_6 += 0xA;
    } while ((s32) var_t5_5 < (s32) temp_t3_6);
    return 1;
}
