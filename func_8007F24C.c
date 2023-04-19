#include "ctx.c"

void func_8007F24C(s8 *arg0, s32 arg1) {
    s32 sp8;
    s32 sp4;
    s32 sp0;
    s32 temp_a1;
    s32 temp_lo;
    s32 temp_t9;
    s32 temp_t9_2;
    s32 temp_v1;
    s32 var_a1;
    s32 var_a3;
    s32 var_v0;
    s32 var_v1;
    u8 temp_t0;
    u8 temp_t1;
    u8 temp_t2;
    u8 temp_t3;
    void *temp_t5;
    void *temp_v1_2;

    if (arg0->unk0 >= 2) {
        temp_v1 = arg0->unkC;
        var_v0 = arg0->unk8 + arg1;
        arg0->unk8 = var_v0;
        if (var_v0 >= temp_v1) {
            do {
                temp_t9 = var_v0 - temp_v1;
                arg0->unk8 = temp_t9;
                var_v0 = temp_t9;
            } while (temp_t9 >= temp_v1);
        }
        var_v1 = arg0->unk4;
        var_a1 = (arg0 + (var_v1 * 8))->unk18;
        if (var_v0 >= var_a1) {
            do {
                temp_t9_2 = var_v1 + 1;
                arg0->unk8 = (s32) (var_v0 - var_a1);
                arg0->unk4 = temp_t9_2;
                var_v1 = temp_t9_2;
                if (temp_t9_2 >= arg0->unk0) {
                    arg0->unk4 = 0;
                    var_v1 = 0;
                }
                var_a1 = (arg0 + (var_v1 * 8))->unk18;
                var_v0 = arg0->unk8;
            } while (var_v0 >= var_a1);
        }
        temp_a1 = var_v1 + 1;
        var_a3 = temp_a1;
        if (temp_a1 >= arg0->unk0) {
            var_a3 = 0;
        }
        temp_v1_2 = arg0 + (var_v1 * 8);
        temp_lo = (s32) (var_v0 << 0x10) / (s32) temp_v1_2->unk18;
        temp_t5 = arg0 + (var_a3 * 8);
        temp_t0 = temp_v1_2->unk14;
        temp_t1 = temp_v1_2->unk15;
        temp_t2 = temp_v1_2->unk16;
        temp_t3 = temp_v1_2->unk17;
        sp8 = (s32) temp_t5->unk15;
        sp4 = (s32) temp_t5->unk16;
        sp0 = (s32) temp_t5->unk17;
        arg0->unk10 = (s8) (((u32) ((temp_t5->unk14 - temp_t0) * temp_lo) >> 0x10) + temp_t0);
        arg0->unk11 = (s8) (((u32) ((sp8 - temp_t1) * temp_lo) >> 0x10) + temp_t1);
        arg0->unk12 = (s8) (((u32) ((sp4 - temp_t2) * temp_lo) >> 0x10) + temp_t2);
        arg0->unk13 = (s8) (((u32) ((sp0 - temp_t3) * temp_lo) >> 0x10) + temp_t3);
    }
}
