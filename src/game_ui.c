/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8009ECF0 */

#include "game_ui.h"
#include "types.h"
#include "macros.h"
#include "structs.h"
#include "f3ddkr.h"
#include "camera.h"
#include "game.h"
#include "audio.h"
#include "textures_sprites.h"
#include "racer.h"

extern u32 osTvType;

/************ .data ************/

// Unused?
s32 D_800E1E60 = 0;

unk800E1E64 D_800E1E64[59] = {
    { 0, 0, 1.0f, 53.0f, 16.0f, 0, 127, 0 },
    { 0, 3, 1.0f, 54.0f, 18.0f, 0, 0, 0 },
    { 0, 1, 0.4f, -120.0f, -68.0f, 0, 0, 0 },
    { 0, 6, 1.0f, 104.0f, 16.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 93.0f, 31.0f, 0, 0, 0 },
    { 0, 4, 1.0f, 104.0f, 32.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 114.0f, 31.0f, 0, 0, 0 },
    { 0, 8, 0.5f, -3.0f, 73.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 182.0f, 22.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 192.0f, 22.0f, 0, 0, 0 },
    { 0, 13, 1.0f, 239.0f, 16.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 206.0f, 31.0f, 0, 0, 0 },
    { 0, 7, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 22, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 5, 1.0f, -200.0f, 30.0f, 0, 0, 0 },
    { 0, 14, 1.0f, 0.0f, 0.0f, 0, 0, 0 },
    { 0, 16, 1.0f, -50.0f, 87.0f, 0, 0, 0 },
    { 0, 17, 2.0f, -50.0f, 87.0f, 0, 0, 0 },
    { 0, 18, 1.0f, 167.0f, 22.0f, 0, 0, 0 },
    { 0, 19, 1.0f, -127.0f, 88.0f, 0, 0, 0 },
    { 0, 18, 1.0f, 52.0f, 27.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 67.0f, 27.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 77.0f, 27.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 221.0f, 48.0f, 0, 0, 0 },
    { 0, 6, 1.0f, 188.0f, 48.0f, 0, 0, 0 },
    { 0, 10, 1.0f, 206.0f, 48.0f, 0, 0, 0 },
    { 0, 20, 0.4f, -105.0f, -98.0f, 0, 0, 0 },
    { 0, 21, 0.5f, -3.0f, 73.0f, 0, 0, 0 },
    { 0, 23, 1.0f, -8.0f, 97.0f, 0, 0, 0 },
    { 0, 24, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 25, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 26, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 2, 1.0f, 25.0f, 48.0f, 0, 0, 0 },
    { 0, 32, 1.0f, -120.0f, 30.0f, 0, 0, 0 },
    { 0, 34, 0.4f, -105.0f, -98.0f, 0, 0, 0 },
    { 0, 35, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 36, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 40, 1.0f, 80.0f, -60.0f, 0, 0, 0 },
    { 0, 1687158830, 0.5f, 122.0f, -71.0f, 0, 0, 0 },
    { 0, 47, 0.75f, 247.0f, 212.0f, 0, 0, 0 },
    { 0, 48, 1.0f, 234.0f, 196.0f, 0, 0, 0 },
    { 0, 49, 1.0f, 232.0f, 177.0f, 0, 0, 0 },
    { 0, 50, 1.0f, 240.0f, 159.0f, 0, 0, 0 },
    { 0, 51, 1.0f, 256.0f, 146.0f, 0, 0, 0 },
    { 0, 52, 1.0f, 275.0f, 143.0f, 0, 0, 0 },
    { 0, 53, 1.0f, 246.0f, 156.0f, 0, 0, 0 },
    { 0, 54, 0.7272f, 27.0f, 142.0f, 0, 0, 0 },
    { 0, 0, 1.0f, -200.0f, 70.0f, 0, 129, 0 },
    { 0, 3, 1.0f, -175.0f, 72.0f, 0, 0, 0 },
    { 0, 55, 1.0f, -99.0f, -89.0f, 0, 0, 0 },
    { 0, 56, 0.76f, 43.0f, 20.0f, 0, 0, 0 },
    { 0, 66, 1.0f, 40.0f, 54.0f, 0, 0, 0 },
    { 0, 8, 0.375f, -117.0f, 46.0f, 0, 0, 0 },
    { 0, 28, 1.0f, 51.0f, 56.0f, 0, 0, 0 },
    { 0, 10, 1.0f, 60.0f, 57.0f, 0, 0, 0 },
    { 0, 10, 1.0f, 69.0f, 57.0f, 0, 0, 0 },
    { 0, 67, 1.0f, -160.0f, 5.0f, 0, 0, 0 },
    { 0, 56, 1.0f, 260.0f, 16.0f, 0, 0, 0 },
    { 0, 68, 1.0f, 160.0f, 5.0f, 0, 0, 0 },
};

u16 D_800E25C4[96] = {
    0x0000, 0x0035, 0x0010, 0x0001, 0x0036, 0x0012, 0x0004, 0x00CB,
    0x0013, 0x0005, 0x00D3, 0x0013, 0x0006, 0x00DC, 0x0013, 0x0002,
    0xFF88, 0xFFE1, 0x001B, 0x0021, 0x0016, 0x0008, 0x00D3, 0x0013,
    0x0009, 0x00DC, 0x0013, 0x000B, 0x00A7, 0x0013, 0x000E, 0x0000,
    0x000A, 0x0010, 0x003B, 0x0023, 0x0011, 0x003B, 0x0023, 0x0007,
    0x0021, 0x0016, 0x001C, 0x001E, 0x002A, 0x0012, 0x00CA, 0x0013,
    0x000D, 0x0000, 0x000A, 0x000C, 0x0000, 0x000A, 0x0023, 0x0000, 
    0x000A, 0x0024, 0x0000, 0x000A, 0x001E, 0x0000, 0x000A, 0x001F,
    0x0000, 0x000A, 0x001D, 0x0000, 0x000A, 0x002F, 0xFF38, 0x0023,
    0x0030, 0xFF51, 0x0025, 0x0031, 0xFF96, 0xFFD3, 0x0003, 0x00B4,
    0x0013, 0x0032, 0x0107, 0x0011, 0x0020, 0x00F7, 0x002D, 0x0033,
    0x0103, 0x0031, 0x002E, 0x0022, 0x0047, 0xFFFF, 0xFFFF, 0xFFFF,
};

u16 D_800E2684[118] = {
    0x0000, 0x002D, 0x0010, 0x0087, 0x0004, 0x005E, 0x0013, 0x004E,
    0x0005, 0x0066, 0x0013, 0x0056, 0x0006, 0x006F, 0x0013, 0x005F,
    0x0002, 0xFFD1, 0xFFDC, 0x0024, 0x001B, 0x0000, 0x0016, 0xFFE3,
    0x0007, 0x0000, 0x0016, 0xFFE3, 0x0008, 0x0061, 0x0013, 0x0044,
    0x0009, 0x006A, 0x0013, 0x004D, 0x000B, 0x0037, 0x0013, 0x001A,
    0x000C, 0x0000, 0x000A, 0x0000, 0x000D, 0x0000, 0x000A, 0x0000,
    0x000E, 0xFF60, 0x000A, 0xFF60, 0x0010, 0x0066, 0x0013, 0x0056,
    0x0011, 0x0066, 0x0013, 0x0056, 0x0012, 0x0058, 0x0013, 0x003B,
    0x001C, 0xFFFD, 0x002A, 0xFFE0, 0x0020, 0x0012, 0x002D, 0x0078,
    0x001E, 0xFFEA, 0x000A, 0xFFEA, 0x001F, 0x000C, 0x000A, 0x0010,
    0x001D, 0x0000, 0x000A, 0xFFD9, 0x0023, 0x0000, 0x000A, 0x0000,
    0x0024, 0x0000, 0x000A, 0x0000, 0x002F, 0xFF38, 0x0019, 0xFFD8,
    0x0030, 0xFF51, 0x001B, 0xFFF1, 0x0031, 0xFFDF, 0xFFCE, 0x0032,
    0x0003, 0x0047, 0x0013, 0x0037, 0x0033, 0x003C, 0x0014, 0x003C,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
};
unk800E2770 D_800E2770[2] = {
    { 0, 0xFD, 0, 0, 0, 0, 0 },
    { 0, 0xFF, 0, 0, 0, 0, 0 },
};

u8 D_800E2790 = 1;

u8 D_800E2794[16] = {
    1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

s8 D_800E27A4[4] = {
    1, 1, 1, 1
};

s8 D_800E27A8 = 1;

s8 D_800E27AC[12] = {
    -1, 40, 40, -2,
    40, -1, 40, -2,
    40, 40, -1, -2,
};

u8 D_800E27B8 = 0;

u8 D_800E27BC[120] = {
    0xFF, 0xA0, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x80,
    0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xAF, 0x00, 0x00,
    0xFF, 0x80, 0xFF, 0x00, 0x00, 0xFF, 0x80, 0xBE,
    0x80, 0x80, 0x80, 0x00, 0x00, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

s32 D_800E2834 = -2;

f32 D_800E2838 = 0.0f;

// Unused?
s32 D_800E283C[5] = {
    0x06FFFFFF, 0x000FFFFF, 0x06000000, 0x0014FFFF, 0x00000000
};

/*******************************/

/************ .bss ************/

u8 D_80126CD0;
u8 D_80126CD1;
u8 D_80126CD2;
u8 D_80126CD3;
u8 D_80126CD4;
u8 D_80126CD5;
s32 D_80126CD8;
unk80126CDC *D_80126CDC;
s32 D_80126CE0;
s32 D_80126CE4;
s32 D_80126CE8;
s32 D_80126CEC;
s32 D_80126CF0;
s32 D_80126CF4;
s32 D_80126CF8;
Gfx *gHUDCurrDisplayList;
u32 D_80126D00;
u32 D_80126D04;
s32 D_80126D08;
s32 D_80126D0C; //Number of Players?
s32 D_80126D10;
s32 D_80126D14;
s32 D_80126D18;
s32 D_80126D1C;
s32 D_80126D20;
s32 D_80126D24;
s32 D_80126D28;
s32 D_80126D2C;
s32 D_80126D30;
u8 D_80126D34;
u8 D_80126D35;
u8 D_80126D36;
u8 D_80126D37;
u8 D_80126D38;
s32 D_80126D3C;
s32 D_80126D40;
s32 D_80126D44;
s32 D_80126D48;
s32 D_80126D4C;
s32 D_80126D50;
u8 gMinimapRed;
u8 gMinimapGreen;
u8 gMinimapBlue;
s32 D_80126D58;
s32 D_80126D5C;
unk80126D60 *D_80126D60;
u8 D_80126D64;
u8 D_80126D65;
u8 D_80126D66;
u8 D_80126D67;
u8 D_80126D68;
u8 D_80126D69;
s32 D_80126D6C;
u8 D_80126D70;
u8 D_80126D71;
s32 D_80126D74;
s32 D_80126D78;
u16 D_80126D7C;
s32 D_80126D80;
s32 D_80126D84;
s32 D_80126D88[254];
s32 D_80127180;
s32 D_80127184;
u8 D_80127188;
u8 D_80127189;
u8 D_8012718A;
u8 D_8012718B;
s32 D_8012718C;
s32 D_80127190;
s32 D_80127194;
s32 D_80127198[6];

// ????
u8 gGfxTaskYieldData[0xA00];

/******************************/

GLOBAL_ASM("asm/non_matchings/game_ui/func_8009ECF0.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_8009F034.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A003C.s")

u8 func_800A0190(void) {
    return D_80126D34;
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800A01A0.s")

void func_800A0B74(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        if (D_800E2770[i].unk4 != 0) {
            func_8000488C(D_800E2770[i].unk4);
            D_800E2770[i].unk4 = 0;
            D_800E2770[i].unk2 = 0;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800A0BD4.s")

void func_800A0DC0(s32 arg0, Object *arg1, s32 arg2) {
    Object_Racer *temp = &arg1->unk64->racer;

    func_80068508(1);
    render_course_indicator_arrows(temp, arg2);
    render_wrong_way_text(temp, arg2);
    func_800A3CE4(arg0, arg2);

    if (D_80126D60->unk4C == 0) {
        func_800A4F50(temp, arg2);
    }

    func_800A4154(temp, arg2);
    render_race_time(temp, arg2);
    func_800A4C44(temp, arg2);
    func_800A3884(arg1, arg2);

    if (D_80127188 != 0 && temp->raceStatus == STATUS_RACING) {
        func_800A47A0(temp, arg2);
    }

    func_800A7520(arg1, arg2);
    func_80068508(0);
}

/**
 * Render the onscreen course arrows that show the player where to go.
*/
void render_course_indicator_arrows(Object_64 *racer, s32 updateRate) {
    s32 timer;
    s32 type;
    IndicatorArrow *indicator;

    if (D_800E2790) {
        timer = racer->racer.indicator_timer;
        if (timer > 0) {
            type = racer->racer.indicator_type;
            racer->racer.indicator_timer = timer - updateRate;
            if (type) {
                indicator = &D_80126CDC->courseIndicator;
                switch (type) {
                case INDICATOR_LEFT:
                    indicator->textureID = ASSET_TEX2D_33;
                    indicator->unk0 = 0;
                    break;
                case INDICATOR_LEFT_SHARP:
                    indicator->textureID = ASSET_TEX2D_32;
                    indicator->unk0 = 0;
                    break;
                case INDICATOR_LEFT_UTURN:
                    indicator->textureID = ASSET_TEX2D_31;
                    indicator->unk0 = 0;
                    break;
                case INDICATOR_RIGHT:
                    indicator->textureID = ASSET_TEX2D_33;
                    indicator->unk0 = -0x8000;
                    break;
                case INDICATOR_RIGHT_SHARP:
                    indicator->textureID = ASSET_TEX2D_32;
                    indicator->unk0 = -0x8000;
                    break;
                case INDICATOR_RIGHT_UTURN:
                    indicator->textureID = ASSET_TEX2D_31;
                    indicator->unk0 = -0x8000;
                    break;
                case INDICATOR_UP:
                    indicator->textureID = ASSET_TEX2D_30;
                    indicator->unk0 = -0x8000;
                    indicator->unk2 = -0x8000;
                    break;
                case INDICATOR_DOWN:
                    indicator->textureID = ASSET_TEX2D_30;
                    indicator->unk0 = 0;
                    break;
                default: // INDICATOR_EXCLAMATION
                    indicator->textureID = ASSET_TEX2D_29;
                    indicator->unk0 = 0;
                    break;
                }
                // Flip the arrow direction on adventure 2.
                if ((get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) && ((s32) racer->racer.indicator_type < ASSET_TEX2D_30)) {
                    indicator->unk0 = (s16) (0x8000 - indicator->unk0);
                }
                if ((D_80126D0C == 0) && (racer->racer.raceStatus == STATUS_RACING) && (racer->racer.indicator_type) && (D_800E27B8 == 0)) {
                    gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                    func_800AA600(&gHUDCurrDisplayList, &D_80126D00, &D_80126D04, indicator);
                    indicator->unkC = -indicator->unkC;
                    func_800AA600(&gHUDCurrDisplayList, &D_80126D00, &D_80126D04, indicator);
                    indicator->unkC = -indicator->unkC;
                    indicator->unk2 = 0;
                    gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
                }
            }
        } else {
            racer->racer.indicator_timer = 0;
        }
        if (D_800E27B8) {
            if (D_800E27B8 & 0x20) {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                indicator = (IndicatorArrow *) &D_80126CDC->courseIndicator;
                indicator->unk0 = 0;
                indicator->unk2 = 0;
                indicator->textureID = ASSET_TEX2D_29;
                if ((get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) && ((s32) racer->racer.indicator_type < ASSET_TEX2D_30)) {
                    indicator->unk0 = (s16) (0x8000 - indicator->unk0);
                }
                func_800AA600(&gHUDCurrDisplayList, &D_80126D00, &D_80126D04, indicator);
                indicator->unkC = (f32) -indicator->unkC;
                func_800AA600(&gHUDCurrDisplayList, &D_80126D00, &D_80126D04, indicator);
                indicator->unkC = (f32) -indicator->unkC;
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            }
            if (updateRate < D_800E27B8) {
                D_800E27B8 -= updateRate;
                return;
            }
            D_800E27B8 = 0;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800A1248.s")

void func_800A1428(s32 arg0, Object *arg1, s32 arg2) {
    Object_Racer *temp = &arg1->unk64->racer;
    if (temp->raceStatus == STATUS_RACING) {
        func_80068508(1);
        func_800A3CE4(arg0, arg2);
        func_800A7520(arg1, arg2);
        if ((0x7F - (arg2 * 2)) >= D_80126CDC->unk67A) {
            D_80126CDC->unk67A += (arg2 * 2);
        } else {
            D_80126CDC->unk67A = (D_80126CDC->unk67A + (arg2 * 2)) - 0xFF;
        }
        if (D_80126D37 != 2) {
            func_800A14F0(arg1, arg2);
        }
        func_80068508(0);
    }
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800A14F0.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A19A4.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A1C04.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A1E48.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A22F4.s")

void func_800A258C(s32 arg0, Object *arg1, s32 arg2) {
    LevelHeader *level;
    Object_64 *temp = arg1->unk64;

    func_80068508(1);
    render_wrong_way_text(temp, arg2);
    func_800A3CE4(arg0, arg2);
    render_race_time(temp, arg2);
    func_800A7520(arg1, arg2);

    level = get_current_level_header();
    if (level->laps > 1) {
        func_800A4F50(temp, arg2);
    }

    func_800A3884(arg1, arg2);
    func_800A4C44(temp, arg2);
    func_80068508(0);
}

void func_800A263C(s32 arg0, Object *arg1, s32 arg2) {
    Object_64 *temp = arg1->unk64;

    func_80068508(1);
    render_wrong_way_text(temp, arg2);
    func_800A4F50(temp, arg2);
    func_800A4C44(temp, arg2);
    render_race_time(temp, arg2);
    func_800A3CE4(arg0, arg2);
    func_800A3884(arg1, arg2);
    func_80068508(0);
}

void func_800A26C8(Object *obj, s32 arg1) {
    Object_64 *obj64;
    unk80126CDC *temp_a3;

    if (get_viewport_count() == 0) {
        obj64 = obj->unk64;
        func_80068508(1);
        func_800A718C(obj64);
        func_800A3884(obj, arg1);
        if (is_in_two_player_adventure()) {
            temp_a3 = &D_80126CDC[1];
            temp_a3->unk6 = (get_settings()->racers[1].character + 0x38);
            func_800AA600(&gHUDCurrDisplayList, &D_80126D00, &D_80126D04, temp_a3);
        }
        func_80068508(0);
    }
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800A277C.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A36CC.s")

void func_800A3870(void) {
    D_80126CDC->unk4C4 = 0x6490;
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800A3884.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A3CE4.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A4154.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A45F0.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A47A0.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A497C.s")
UNUSED void func_800A4C34(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2) {}
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A4C44.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A4F50.s")

/**
 * Players going the wrong way will be nagged by T.T to turn around.
 * This function plays the audio, and makes the text fly in.
*/
void render_wrong_way_text(Object_64* obj, s32 updateRate) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f2;
    f32 temp_f2_2;
    s8 temp_v1;
    s8 temp_v1_2;
    u8 var_t9;

    if (D_80126D0C == 1) {
        func_8007BF1C(1);
    }
    if (obj->racer.unk1FC > 120 && (D_80126D0C || D_80126CDC->unk46C == D_80126CDC->unk47A[2]) && !is_game_paused()) {
        if ((D_80126D38 || D_80126D6C == 0) && D_80126D40 == 0) {
            if (D_80126D38 || (get_random_number_from_range(1, 10) >= 8)) {
                D_80126D38 = 0;
                play_sound_global(SOUND_VOICE_TT_WRONG_WAY, &D_80126D40);
                D_80126D6C = get_random_number_from_range(1, 480) + 120;
            } else {
                D_80126D38 = 1;
                play_sound_global(SOUND_VOICE_TT_NONONO, &D_80126D40);
            }
        }
        D_80126D6C -= updateRate;
        if (D_80126D6C < 0) {
            D_80126D6C = 0;
        }
    }
    if (D_80126CDC->unk47A[0]) {
        if (D_80126CDC->unk47A[0] == 1) {
            if (D_80126CDC->unk47A[1] == 1) {
                temp_f0 = updateRate * 13;
                D_80126CDC->unk46C = D_80126CDC->unk46C + temp_f0;
                temp_f2 = D_80126CDC->unk47A[2];
                if (temp_f2 < D_80126CDC->unk46C) {
                    D_80126CDC->unk46C = temp_f2;
                }
                D_80126CDC->unk48C = (f32) (D_80126CDC->unk48C - temp_f0);
                temp_f2_2 = D_80126CDC->unk49C;
                if (D_80126CDC->unk48C < temp_f2_2) {
                    D_80126CDC->unk48C = temp_f2_2;
                }
                if (obj->racer.unk1FC <= 90) {
                    D_80126CDC->unk47A[1] = -1;
                    play_sound_global(SOUND_WHOOSH1, NULL);
                }
            } else if (D_80126CDC->unk47A[1] == -1) {
                temp_f0_2 = (f32) (updateRate * 13);
                D_80126CDC->unk46C -= temp_f0_2;
                D_80126CDC->unk48C += temp_f0_2;
                if (D_80126CDC->unk46C < -200.0f) {
                    D_80126CDC->unk47A[0] = 0;
                }
            }
            if (!is_game_paused()) {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                func_800AA600(&gHUDCurrDisplayList, &D_80126D00, &D_80126D04, (unk80126CDC* ) &D_80126CDC->unk454[0xC]);
                func_800AA600(&gHUDCurrDisplayList, &D_80126D00, &D_80126D04, (unk80126CDC* ) &D_80126CDC->unk454[0x2C]);
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            }
        }
    } else if (obj->racer.unk1FC > 120) {
        D_80126CDC->unk47A[0] = 1;
        D_80126CDC->unk47A[1] = 1;
        D_80126CDC->unk47A[2] = -31;
        D_80126CDC->unk49C = 52;
        D_80126CDC->unk47A[3] = 0;
        if (D_80126D0C == 1) {
            D_80126CDC->unk47A[2] = -21;
            D_80126CDC->unk49C = 42;
        } else  if (D_80126D0C >= 2) {
            if (obj->racer.playerIndex == PLAYER_ONE || obj->racer.playerIndex == PLAYER_THREE) {
                D_80126CDC->unk47A[2] = -100;
                D_80126CDC->unk49C = -55;
            } else {
                D_80126CDC->unk47A[2] = 59;
                D_80126CDC->unk49C = 104;
            }
        }
        D_80126CDC->unk48C = D_80126CDC->unk49C + 200;
        D_80126CDC->unk46C =  D_80126CDC->unk49C - 200;
        play_sound_global(0x16U, NULL);
    }
    func_8007BF1C(0);
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800A5F18.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A6254.s")

void func_800A6DB4(s16 *arg0) {
    Settings *settings = get_settings();

    if (arg0 != NULL) {
        if (settings->racers[*arg0].best_times & 0x80) {
            play_sound_global(SOUND_VOICE_TT_RACE_RECORD, &D_80126D40);
        } else {
            play_sound_global(SOUND_VOICE_TT_FINISH, &D_80126D40);
        }
    }
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800A6E30.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A718C.s")

UNUSED void func_800A7440(u16 soundId) {
    if ((D_80126D40 == 0) && (!is_game_paused())) {
        play_sound_global(soundId, &D_80126D40);
    }
}

void func_800A7484(u16 arg0, f32 arg1, s32 arg2) {
    if (D_80126D74 == 0) {
        D_80126D7C = arg0;
        D_80126D74 = arg1 * 60.0f;
        D_80126D78 = arg2;
    }
}

void func_800A74EC(u16 arg0, s32 arg1) {
    if (arg0 == D_80126D7C && D_80126D78 == arg1) {
        D_80126D74 = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800A7520.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A7A60.s")

/**
 * Render the lap time on the top right.
 * When the player begins a new lap, start flashing the previous lap time below instead.
*/
void render_race_time(Object_64* obj, s32 updateRate) {
    s32 i;
    s32 stopwatchTimer;
    s32 minutes;
    s32 seconds;
    s32 hundredths;
    s32 countingDown;
    s32 timerHideCounter;

    if (!(D_80126D0C && D_800E2794[(D_80126D0C * 4) + obj->racer.playerIndex] != 1) || (D_80126D0C > 0 && obj->racer.lapCount > 0 && obj->racer.lap_times[obj->racer.lapCount] < 180)) {
        if (obj->racer.raceStatus == STATUS_RACING) {
            timerHideCounter = D_80126CDC->unk15A + 127;
            if (obj->racer.lapCount > 0 && obj->racer.lap_times[obj->racer.lapCount] < 180 && obj->racer.lapCount < D_80126D60->numLaps) {
                stopwatchTimer = obj->racer.lap_times[obj->racer.lapCount - 1];
                countingDown = TRUE;
                if (timerHideCounter == 0) {
                    timerHideCounter = 180;
                }
            } else {
                stopwatchTimer = 0;
                for (i = 0; obj->racer.unk194 >= i && i < D_80126D60->numLaps; i++) {
                    stopwatchTimer += obj->racer.lap_times[i];
                }
                countingDown = stopwatchTimer == 0 || obj->racer.raceStatus != STATUS_RACING || is_game_paused();
                D_80126CDC->unk15A = -127;
                timerHideCounter = 0;
            }
            if (D_80126D0C == 0) {
                func_800AA600(&gHUDCurrDisplayList, &D_80126D00, &D_80126D04, (unk80126CDC* ) &D_80126CDC->unk140);
            }
            if (normalise_time(36000) < stopwatchTimer) {
                stopwatchTimer = normalise_time(36000);
            }
            get_timestamp_from_frames(stopwatchTimer, &minutes, &seconds, &hundredths);
            if (countingDown || (normalise_time(36000) == stopwatchTimer)) {
                if((timerHideCounter > updateRate)) {
                    timerHideCounter -= updateRate;
                } else {
                    timerHideCounter = 0;
                }
                D_80126CDC->unk15A = timerHideCounter - 127;
                if ((timerHideCounter % 30) > 20) {
                    D_80126D36 = TRUE;
                    return;
                } else {
                    if (D_80126D36) {
                        if (D_80126D0C == 0) {
                            play_sound_global(SOUND_HUD_LAP_TICK, NULL);
                        }
                        D_80126D36 = 0;
                    }
                }
            } else {
                hundredths = D_80126CDC->unk15B + ((hundredths / 10) * 10);
                D_80126CDC->unk15B = D_80126CDC->unk15B + 1;
                if (D_80126CDC->unk15B >= 10) {
                    D_80126CDC->unk15B = 0;
                }
            }
            
            if (D_80126D37 == 1) {
                func_800A7FBC(D_80126CDC->unk16C, D_80126CDC->unk170, minutes, seconds, hundredths, 0);
            } else {
                func_800A7FBC(D_80126CDC->unk16C, D_80126CDC->unk170, minutes, seconds, hundredths, 1);
            }
            gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
        }
    }
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800A7FBC.s")

void func_800A83B4(LevelModel *model) {
    s32 sp2C;
#ifdef PUPPYPRINT_DEBUG
    u32 first =  osGetTime();
#endif
    gMinimapRed = (model->minimapColor >> 16) & 0xFF;
    gMinimapGreen = (model->minimapColor >> 8) & 0xFF;
    gMinimapBlue = model->minimapColor & 0xFF;
    load_sprite_info(model->unk20, &D_80126D1C, &D_80126D20, &sp2C, &sp2C, &sp2C);
    func_8007CA68(model->unk20, 0, &D_80126D14, &D_80126D18, &sp2C);
    model->unk20 = (s32)func_8007C12C(model->unk20, 1);
#ifdef PUPPYPRINT_DEBUG
    profiler_add(gPuppyTimers.hudTime, osGetTime() - first);
#endif
}

s8 func_800A8458(void) {
    return D_800E27A4[D_80126D0C];
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800A8474.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800AA3EC.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800AA600.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800AAFD0.s")

void func_800AB194(s32 arg0) {
    D_80126CD1 = 1;
    D_80126CD3 = arg0;
}

void func_800AB1AC(s32 arg0) {
    D_80126CD0 = D_8012718B;
    D_80126CD3 = arg0;
}

/* Unused? */
void func_800AB1C8(void) {
    D_80126CD4 = 0;
}

void func_800AB1D4(u8 arg0) {
    D_80126CD2 = 1 - arg0;
}
