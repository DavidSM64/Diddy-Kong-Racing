#include "ctx.c"

? func_8007CDC0(Sprite *, MemoryPoolSlot *, s32, s32 *); /* extern */

MemoryPoolSlot *func_8007C12C(s32 arg0, s32 arg1) {
    s32 sp44;
    s8 sp33;
    s8 sp32;
    MemoryPoolSlot *temp_v0;
    MemoryPoolSlot *temp_v0_2;
    MemoryPoolSlot *var_s1_3;
    Sprite *temp_s4;
    TextureHeader *temp_a0_2;
    s16 temp_a1;
    s32 *temp_v0_3;
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_t0;
    s32 var_t6;
    s32 var_t8;
    s8 var_t1;
    s8 var_v1;
    u8 *temp_s1;
    u8 temp_s5;
    void *temp_t5;
    void *temp_t5_2;
    void *temp_t7;
    void *temp_v1;

    D_8012635C = arg1;
    if ((arg0 < 0) || (arg0 >= D_80126354)) {
        return NULL;
    }
    var_s0 = 0;
    var_t1 = 0;
    if (D_80126358 > 0) {
        var_t8 = 0 * 8;
loop_5:
        temp_v1 = gSpriteCache + var_t8;
        var_s0 += 1;
        if (arg0 == temp_v1->unk0) {
            temp_v0_2 = temp_v1->unk4;
            temp_v0_2->unk4 = (s16) (temp_v0_2->unk4 + 1);
            return temp_v0_2;
        }
        var_t8 = var_s0 * 8;
        if (var_s0 >= D_80126358) {
            var_s0 = 0;
            goto block_9;
        }
        goto loop_5;
    }
block_9:
    var_t0 = -1;
    if (D_80126358 > 0) {
        var_t6 = 0 * 8;
        do {
            if (*(gSpriteCache + var_t6) == -1) {
                var_t0 = var_s0;
            }
            var_s0 += 1;
            var_t6 = var_s0 * 8;
        } while (var_s0 < D_80126358);
    }
    if (var_t0 == -1) {
        var_t1 = 1;
        var_t0 = D_80126358;
        D_80126358 += 1;
    }
    temp_v0_3 = &gSpriteOffsetTable[arg0];
    temp_a2 = temp_v0_3->unk0;
    temp_s4 = gCurrentSprite;
    sp32 = var_t1;
    sp44 = var_t0;
    load_asset_to_address(0xCU, (u32) temp_s4, temp_a2, temp_v0_3->unk4 - temp_a2);
    temp_a1 = temp_s4->numberOfFrames;
    temp_s5 = (temp_s4 + temp_a1)->unkC;
    temp_s0 = (temp_s5 * 0x48) + (temp_a1 * 8) + (temp_s5 << 5) + (temp_s5 * 4);
    temp_s0_2 = temp_s0 + align16((u8 *)0x10);
    temp_v0 = allocate_from_main_pool(temp_s0_2 + align16((u8 *) (temp_s4->numberOfFrames * 4)), 0xFF00FFFFU);
    if (temp_v0 == NULL) {
        if (sp32 != 0) {
            D_80126358 -= 1;
        }
        return NULL;
    }
    var_s0_2 = 0;
    temp_s1 = align16((u8 *)0x10);
    temp_t5 = align16((u8 *) (temp_s4->numberOfFrames * 4)) + temp_v0 + temp_s1;
    temp_a0 = temp_s5 << 5;
    temp_t7 = temp_t5 + temp_a0;
    D_80126368 = (s32) temp_t5;
    D_80126364 = (s32) temp_t7;
    temp_t5_2 = temp_t7 + temp_a0 + (temp_s4->numberOfFrames * 8);
    D_80126360 = (s32) temp_t5_2;
    temp_v0->unk8 = (void *) (temp_t5_2 + (temp_s5 * 0x28));
    var_v1 = 0;
    if ((s32) temp_s5 > 0) {
        var_s1 = 0;
        do {
            gTexColourTag = 0xFF0163;
            sp33 = var_v1;
            *(temp_v0->unk8 + var_s1) = load_texture(temp_s4->baseTextureId + var_s0_2);
            if (*(temp_v0->unk8 + var_s1) == 0) {
                var_v1 = 1;
            }
            var_s0_2 += 1;
            gTexColourTag = 0xFF00FFFF;
            var_s1 += 4;
            D_80126344 = 1;
        } while (var_s0_2 != temp_s5);
        var_s0_2 = 0;
    }
    D_80126344 = 0;
    if (var_v1 != 0) {
        var_s1_2 = 0;
        if ((s32) temp_s5 > 0) {
            do {
                temp_a0_2 = *(temp_v0->unk8 + var_s1_2);
                if (temp_a0_2 != NULL) {
                    free_texture(temp_a0_2);
                }
                var_s0_2 += 1;
                var_s1_2 += 4;
            } while (var_s0_2 != temp_s5);
        }
        if (sp32 != 0) {
            D_80126358 -= 1;
        }
        free_from_memory_pool(temp_v0);
        return NULL;
    }
    temp_v0->unk2 = (s16) temp_s5;
    var_s1_3 = temp_v0;
    temp_v0->unk0 = (s16) temp_s4->numberOfFrames;
    if (temp_s4->numberOfFrames > 0) {
        do {
            var_s1_3->unkC = (s32) D_80126364;
            func_8007CDC0(temp_s4, temp_v0, var_s0_2, &D_80126364);
            var_s0_2 += 1;
            var_s1_3 += 4;
        } while (var_s0_2 < temp_s4->numberOfFrames);
    }
    if (D_80126358 >= 0x64) {
        return NULL;
    }
    gSpriteCache[sp44].id = arg0;
    gSpriteCache[sp44].sprite = (Sprite *) temp_v0;
    temp_v0->unk4 = 1;
    return temp_v0;
}
