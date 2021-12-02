/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C29F0 */

#include "game_text.h"
#include "menu.h"
#include "unknown_00BC20.h"
#include "unknown_043920.h"
#include "unknown_06B2B0.h"

/************ .data ************/

s8 D_800E3670 = 0;
s16 D_800E3674 = 0;
s32 D_800E3678 = 0;
s32 D_800E367C = 0;
s32 D_800E3680 = 1;

/*******************************/

/************ .bss ************/

u8 *D_8012A780;
s8 D_8012A784;
s8 D_8012A785;
s8 D_8012A786;
s8 D_8012A787;
s8 D_8012A788;
u8 D_8012A789;
s8 D_8012A78A;
s16 D_8012A78C;
s16 D_8012A78E;
s16 D_8012A790;
s16 D_8012A792;
unk8012A798 D_8012A798;
s32 D_8012A7A0;
s32 D_8012A7A4;
s16 D_8012A7A8;
s16 D_8012A7AA;
s16 D_8012A7AC;
s16 D_8012A7AE;
s16 D_8012A7B0;
s16 D_8012A7B2;
s16 D_8012A7B4;
s16 D_8012A7B6;
s16 D_8012A7B8;
s16 D_8012A7BA;
s16 D_8012A7BE;
s32 D_8012A7C0;
unk8012A7C8 D_8012A7C8;
s32 D_8012A7D0;
s32 D_8012A7D4;
s32 D_8012A7D8;
s32 D_8012A7DC;

/*****************************/

void func_800C29F0(void) {
    D_8012A7C8.unk0 = (u8 *)allocate_from_main_pool_safe(0x780, COLOR_TAG_GREEN);
    D_8012A7C8.unk4 = D_8012A7C8.unk0 + 0x3C0;
    D_8012A7D4 = 0;
    D_8012A7B6 = 0;
    D_8012A7A8 = 0;
    D_8012A7AA = 0x20;
    D_8012A7BA = 0;
    D_8012A7AE = 0x20;
    D_8012A7B2 = 0x120;
    if (osTvType == TV_TYPE_PAL) {
        D_8012A7B0 = 0xE0;
        D_8012A7B4 = 0xF8;
    } else {
        D_8012A7B0 = 0xCA;
        D_8012A7B4 = 0xDE;
    }
    func_800C56D0(6);
}

void func_800C2AB4(void) {
    free_from_memory_pool(D_8012A7C8.unk0);
    D_8012A7B6 = 0;
    close_dialogue_box(6);
    func_800C5494(6);
}

void func_800C2AF4(s32 arg0) {
    D_800E3680 = arg0;
}

GLOBAL_ASM("asm/non_matchings/game_text/func_800C2B00.s")
GLOBAL_ASM("asm/non_matchings/game_text/func_800C2D6C.s")

void func_800C2F1C(s32 arg0) {
    if (D_800E3680 == 0) {
        D_8012A7B6 = 0;
    }
    if (D_8012A7B6 != 0) {
        if (D_8012A7AC <= 0) {
            D_8012A7A8 -= arg0 * D_8012A7AA;
            if ((s32)D_8012A7A8 < 0) {
                D_8012A7A8 = 0;
                D_8012A7B6 = 0;
                close_dialogue_box(6);
                func_800C5494(6);
            }
        } else {
            D_8012A7A8 += arg0 * D_8012A7AA;
            if (D_8012A7A8 >= 0x101) {
                D_8012A7A8 = 0x100;
            }
            D_8012A7AC -= arg0;
            if (D_8012A7AC <= 0) {
                func_800C2D6C(D_8012A7B6);
            }
        }
    }
    if (D_8012A7B6 != 0) {
        func_800C2B00(D_8012A7B6);
    }
}

void func_800C3048(void) {
    D_8012A78C = -1;
    D_8012A780 = (u8 *)allocate_from_main_pool_safe(0x800, COLOR_TAG_GREEN);
    D_8012A798.unk0 = D_8012A780 + 0x80;
    D_8012A798.unk4 = D_8012A798.unk0 + 0x3C0;
    D_8012A7A4 = 0;
    func_800C29F0();
    D_8012A790 = (get_size_of_asset_section(ASSET_GAME_TEXT_TABLE) >> 2) - 2;
    D_800E3670 = 1;
}

void func_800C30CC(void) {
    s32 i;
    if (D_800E3670) {
        free_from_memory_pool(D_8012A780);
        D_800E3670 = 0;
        D_8012A789 = 0;
        for (i = 0; i < 10; i++) {
            func_8009CFB0();
        };
        func_800C2AB4();
    }
}

void func_800C3140(s32 arg0) {
    D_800E3674 = arg0;
}

void func_800C314C(void) {
    D_800E3678 = 0;
}

void func_800C3158(s32 arg0, f32 arg1) {
    if (osTvType == TV_TYPE_PAL) {
        D_800E3678 = arg1 * 50.0;
    } else {
        D_800E3678 = arg1 * 60.0;
    }
    D_800E367C = arg0;
}

GLOBAL_ASM("asm/non_matchings/game_text/func_800C31EC.s")

s32 func_800C3400(void) {
    s32 result = 0;
    if (D_800E3670 != 0) {
        if (D_8012A789 != 0) {
            result = 1;
            if (D_8012A788 != 0) {
                result = 2;
            }
        }
    }
    return result;
}

void func_800C3440(s32 arg0) {
    if (D_800E3670 != 0) {
        if (!is_game_paused()) {
            if (D_800E3678 > 0) {
                D_800E3678 -= arg0;
                if (D_800E3678 <= 0) {
                    func_800C31EC(D_800E367C);
                    D_800E3678 = 0;
                }
            }
        }
        func_800C2F1C(arg0);
        if (D_8012A789 != 0) {
            func_8005A3B0();
            if (D_8012A786 != 0) {
                D_8012A785 -= arg0;
                while (D_8012A785 < 0) {
                    D_8012A785 += func_8000C8B4(0x3C);
                    D_8012A786--;
                }
                if (D_8012A786 <= 0) {
                    D_8012A784 = 1;
                }
            }
            func_8009CFEC(3);
        }
    }
}

GLOBAL_ASM("asm/non_matchings/game_text/func_800C3564.s")
GLOBAL_ASM("asm/non_matchings/game_text/func_800C38B4.s")
