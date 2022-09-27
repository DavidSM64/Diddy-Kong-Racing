/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C29F0 */

#include "game_text.h"
#include "menu.h"
#include "objects.h"
#include "racer.h"
#include "game.h"

/************ .data ************/

s8 D_800E3670 = 0;
s16 D_800E3674 = 0;
s32 D_800E3678 = 0;
s32 D_800E367C = 0;
s32 D_800E3680 = 1;

/*******************************/

/************ .bss ************/

u8 *gGameTextTable; //128 bytes?
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
u8 *D_8012A798[2]; //960 x2 bytes
s32 D_8012A7A0;
s32 D_8012A7A4;
s16 sDialogueAlpha;
s16 D_8012A7AA;
s16 D_8012A7AC;
s16 sDialogueXPos1; // The Upper Left X Coord of the Dialogue Box.
s16 sDialogueYPos1; // The Upper Left Y Coord of the Dialogue Box. Changes for PAL / NTSC
s16 sDialogueXPos2; // The Lower Right X Coord of the Dialogue Box.
s16 sDialogueYPos2; // The Lower Right Y Coord of the Dialogue Box. Changes for PAL / NTSC
s16 D_8012A7B6;     // A Boolean value
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
    D_8012A7C8.unk0 = (u8 *)allocate_from_main_pool_safe(0x780, COLOUR_TAG_GREEN);
    D_8012A7C8.unk4 = D_8012A7C8.unk0 + 0x3C0;
    D_8012A7D4 = 0;
    D_8012A7B6 = 0;
    sDialogueAlpha = 0;
    D_8012A7AA = 32;
    D_8012A7BA = 0;
    sDialogueXPos1 = 32;
    sDialogueXPos2 = 288;
    if (osTvType == TV_TYPE_PAL) {
        sDialogueYPos1 = 224;
        sDialogueYPos2 = 248;
    } else {
        sDialogueYPos1 = 202;
        sDialogueYPos2 = 222;
    }
    func_800C56D0(6);
}

void func_800C2AB4(void) {
    free_from_memory_pool(D_8012A7C8.unk0);
    D_8012A7B6 = 0;
    close_dialogue_box(6);
    assign_dialogue_box_id(6);
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
            sDialogueAlpha -= arg0 * D_8012A7AA;
            if ((s32)sDialogueAlpha < 0) {
                sDialogueAlpha = 0;
                D_8012A7B6 = 0;
                close_dialogue_box(6);
                assign_dialogue_box_id(6);
            }
        } else {
            sDialogueAlpha += arg0 * D_8012A7AA;
            if (sDialogueAlpha > 256) {
                sDialogueAlpha = 256;
            }
            D_8012A7AC -= arg0;
            if (D_8012A7AC <= 0) {
                func_800C2D6C();
            }
        }
    }
    if (D_8012A7B6 != 0) {
        func_800C2B00();
    }
}

void func_800C3048(void) {
    D_8012A78C = -1;
    gGameTextTable = (u8 *)allocate_from_main_pool_safe(2048, COLOUR_TAG_GREEN);
    D_8012A798[0] = &gGameTextTable[128];
    D_8012A798[1] = &D_8012A798[0][960];
    D_8012A7A4 = 0;
    func_800C29F0();
    D_8012A790 = (get_size_of_asset_section(ASSET_GAME_TEXT_TABLE) >> 2) - 2;
    D_800E3670 = 1;
}

void func_800C30CC(void) {
    s32 i;
    if (D_800E3670) {
        free_from_memory_pool(gGameTextTable);
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
        D_800E3678 = arg1 * 50.0f;
    } else {
        D_800E3678 = arg1 * 60.0f;
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
                    D_8012A785 += normalise_time(60);
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
