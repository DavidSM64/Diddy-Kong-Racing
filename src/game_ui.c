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
#include "math_util.h"

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

u8 D_800E2794[4][4] = {
    {1, 1, 1, 1}, 
    {2, 2, 2, 2}, 
    {2, 2, 2, 2}, 
    {2, 2, 2, 2}
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

s8 D_80126CD0;
s8 D_80126CD1;
s8 D_80126CD2;
s8 D_80126CD3;
s8 D_80126CD4;
s8 D_80126CD5;
s32 D_80126CD8;
unk80126CDC *D_80126CDC;
unk80126CDC *D_80126CE0[1];
s32 D_80126CE4;
s32 D_80126CE8;
s32 D_80126CEC;
s32 D_80126CF0;
s32 D_80126CF4;
s32 D_80126CF8;
Gfx *gHUDCurrDisplayList;
Matrix *gHUDCurrMatrix;
TriangleList *gHUDCurrTriList;
s32 D_80126D08;
s32 gHUDNumPlayers;
s32 D_80126D10;
s32 D_80126D14;
s32 D_80126D18;
s32 D_80126D1C;
s32 D_80126D20;
s32 D_80126D24;
s32 D_80126D28;
u16 D_80126D2C;
f32 D_80126D30;
u8 D_80126D34;
u8 D_80126D35;
u8 gHideRaceTimer;
u8 D_80126D37;
u8 gWrongWayNagPrefix;
s32 D_80126D3C;
s32 gHUDVoiceSoundMask;
s32 D_80126D44;
s32 D_80126D48;
s32 D_80126D4C;
s32 D_80126D50;
u8 gMinimapRed;
u8 gMinimapGreen;
u8 gMinimapBlue;
s32 D_80126D58;
s32 D_80126D5C;
LevelHeader *D_80126D60;
u8 D_80126D64;
u8 D_80126D65;
u8 D_80126D66;
u8 D_80126D67;
u8 D_80126D68;
u8 D_80126D69;
s32 gWrongWayNagTimer;
u8 D_80126D70;
u8 D_80126D71;
s32 D_80126D74;
s32 D_80126D78;
u16 D_80126D7C;
DrawTexture D_80126D80;
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

/**
 * The root function for all of the heads up display during an active event.
 * Branches off to its own function for each race type, but overridden completely in time trial.
*/
void render_hud(Gfx **dList, Matrix **mtx, TriangleList **tris, Object *arg3, s32 updateRate) {
    s32 sp2C;
    Object_64* racer;

    D_80126D08 = func_80066220();
    if (D_8012718A) {
        arg3 = func_8001BB18(1 - D_80126D08);
    }
    D_80126D60 = get_current_level_header();
    if (arg3 == NULL) {
        if (func_8001E440() == 10) {
            arg3 = func_8001BB18(0);
        }
    }
    if (arg3 != NULL && !(D_80126D60->unkBC & 2)) {
        if (get_render_context() != DRAW_MENU) {
            gHUDCurrDisplayList = *dList;
            gHUDCurrMatrix = *mtx;
            gHUDCurrTriList = *tris;
            D_80127180 = 0;
            if (D_80126CD1 != 0) {
                D_80126CD0 += updateRate;
                if (D_8012718B < D_80126CD0) {
                    D_80126CD0 = D_8012718B;
                }
            } else {
                D_80126CD0 -= updateRate;
                if (D_80126CD0 < 0) {
                    D_80126CD0 = 0;
                }
            }
            if (D_80126CD2 == 0) {
                racer = arg3->unk64;
                if (D_8012718A) {
                    D_80126D10 = 1 - racer->racer.playerIndex;
                } else {
                    D_80126D10 = racer->racer.playerIndex;
                }
                D_80126CDC = D_80126CE0[D_80126D08];
                if (func_8001E440() != 10) {
                    if (gHUDNumPlayers == 0) {
                        if (get_buttons_pressed_from_player(D_80126D10) & D_CBUTTONS && racer->racer.raceFinished == FALSE && ((D_80126D60->race_type == RACETYPE_DEFAULT) || D_80126D60->race_type == RACETYPE_HORSESHOE_GULCH) && D_80126D34) {
                            D_800E2790 = 1 - D_800E2790;
                            play_sound_global((SOUND_TING_HIGHER + D_800E2790), NULL);
                            if (D_800E2790) {
                                D_800E27B8 = 0x78;
                            } else {
                                D_800E27B8 = 0;
                            }
                        }
                    } else if (get_buttons_pressed_from_player(D_80126D10) & D_CBUTTONS && racer->racer.raceFinished == FALSE && !(D_80126D60->race_type & RACETYPE_CHALLENGE) && D_80126D34) {
                        if (D_800E2794[gHUDNumPlayers][racer->racer.playerIndex] < PLAYER_FOUR) {
                             D_800E2794[gHUDNumPlayers][racer->racer.playerIndex]++;
                        } else {
                             D_800E2794[gHUDNumPlayers][racer->racer.playerIndex] = PLAYER_ONE;
                        }
                        play_sound_global((SOUND_TING_HIGHEST - (D_800E2794[gHUDNumPlayers][racer->racer.playerIndex] == 0)), NULL);
                    }
                    if (get_buttons_pressed_from_player(D_80126D10) & R_CBUTTONS && racer->racer.raceFinished == FALSE && D_80126D34 && D_80126CD0 == 0) {
                        D_800E27A4[gHUDNumPlayers] = 1 - D_800E27A4[gHUDNumPlayers];
                        if (D_800E27A4[gHUDNumPlayers] == 0) {
                            play_sound_global(SOUND_TING_LOW, NULL);
                        } else {
                            play_sound_global(SOUND_TING_HIGH, NULL);
                        }
                    }
                }
                if (D_80126CD4 == 0) {
                    if (D_80126D60->race_type & RACETYPE_CHALLENGE || D_80126D60->race_type == RACETYPE_DEFAULT || D_80126D60->race_type == RACETYPE_HORSESHOE_GULCH || D_80126D60->race_type == RACETYPE_BOSS) {
                        D_800E2770[0].unk2 = 0x7F;
                        D_800E2770[1].unk2 = 0x7F;
                        func_80001844();
                        func_800012E8();
                        play_music(SEQUENCE_RACE_START_FANFARE);
                        set_sound_channel_count(12);
                    } else {
                        func_8006BD10(1.0f);
                    }
                    D_80126CD4 += 1;
                }
                gDPPipeSync(gHUDCurrDisplayList++);
                init_rsp(&gHUDCurrDisplayList);
                init_rdp_and_framebuffer(&gHUDCurrDisplayList);
                func_8007AE28(-1);
                func_8007AE0C(2);
                func_8007BF1C(0);
                if (check_if_showing_cutscene_camera() == FALSE && D_80126D34 == 0 && racer->racer.playerIndex == PLAYER_ONE) {
                    if (D_80126D35 != 0) {
                        D_80126D28 = cosine_s(D_80126D2C) * D_80126D30 * 8.0f;
                        D_80126D2C += updateRate << 0xB;
                        if (D_80126D2C >= 0x8000) {
                            D_80126D2C -= 0x8000;
                            D_80126D30 = D_80126D30 / 2;
                            if (D_80126D30 <= 0.125) {
                                D_80126D34 = 1;
                                D_80126D24 = 0;
                            }
                        }
                    } else {
                        if (D_80126CD4 == 1) {
                            play_sound_global(SOUND_WHOOSH1, NULL);
                            D_80126CD4 += 1;
                        }
                        D_80126D24 -= updateRate * 13;
                        if (D_80126D24 < 0) {
                            D_80126D24 = 0;
                        }
                        if (D_80126D24 == 0) {
                            D_80126D35 = 1;
                            play_sound_global(SOUND_EXPLOSION2, NULL);
                            D_80126D28 = 0;
                        }
                    }
                }
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
                func_800A7A60(arg3, &gHUDCurrDisplayList);
                func_80067F2C(&gHUDCurrDisplayList, (Mtx** ) &gHUDCurrMatrix);
                gDPSetEnvColor(gHUDCurrDisplayList++, 255, 255, 255, 0);
                sp2C = func_8001139C(&gHUDCurrDisplayList) >> 1;
                if (func_8000E4D8()) {
                    func_800A277C(sp2C, arg3, updateRate);
                } else {
                    if (func_8001E440(sp2C) == 10) {
                        func_80068508(1);
                        func_800A718C(racer);
                        func_80068508(0);
                    } else {
                        switch (get_current_level_race_type()) {
                            case RACETYPE_DEFAULT:
                            case RACETYPE_HORSESHOE_GULCH:
                                if (func_8002341C() != 0) {
                                    func_800A263C(sp2C, arg3, updateRate);
                                } else {
                                    func_800A0DC0(sp2C, arg3, updateRate);
                                }
                                break;
                            case RACETYPE_BOSS:
                                render_hud_race_boss(sp2C, arg3, updateRate);
                                break;
                            case RACETYPE_CHALLENGE_BANANAS:
                                func_800A1248(sp2C, arg3, updateRate);
                                break;
                            case RACETYPE_CHALLENGE_BATTLE:
                                func_800A1C04(sp2C, arg3, updateRate);
                                break;
                            case RACETYPE_CHALLENGE_EGGS:
                                render_hud_challenge_eggs(sp2C, arg3, updateRate);
                                break;
                            default:
                                render_hud_hubworld(arg3, updateRate);
                                break;
                        }
                    }
                }
                if (racer->racer.raceFinished == 1) {
                    func_80068508(1);
                    if (func_8000E4D8()) {
                        func_800A6E30(racer, updateRate);
                    } else if (get_viewport_count() == VIEWPORTS_COUNT_1_PLAYER && racer->racer.unk1AC == 1) {
                        if (is_in_two_player_adventure()) {
                            if (get_current_level_race_type() == RACETYPE_BOSS) {
                                goto block_93;
                            }
                            goto block_95;
                        }
block_93:
                        func_800A497C(racer, updateRate);
                    } else {
block_95:
                        func_800A6254(racer, updateRate);
                    }
                    func_80068508(0);
                }
                D_80126CD1 = 0;
                func_8007BF1C(1);
                if (D_80127180) {
                    (&D_80126D80)[D_80127180].texture = NULL;
                    render_textured_rectangle(&gHUDCurrDisplayList, &D_80126D80, 0, 0, 255, 255, 255, 255);
                }
                *dList = gHUDCurrDisplayList;
                *mtx = gHUDCurrMatrix;
                *tris = gHUDCurrTriList;
                func_8007AE28(-1);
            }
        }
    }
}

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

void func_800A0DC0(s32 arg0, Object *arg1, s32 updateRate) {
    Object_Racer *racer = &arg1->unk64->racer;

    func_80068508(1);
    render_course_indicator_arrows(racer, updateRate);
    render_wrong_way_text(racer, updateRate);
    func_800A3CE4(arg0, updateRate);

    if (D_80126D60->race_type == RACETYPE_DEFAULT) {
        func_800A4F50(racer, updateRate);
    }

    func_800A4154(racer, updateRate);
    render_race_time(racer, updateRate);
    func_800A4C44(racer, updateRate);
    func_800A3884(arg1, updateRate);

    if (D_80127188 && racer->raceFinished == FALSE) {
        func_800A47A0(racer, updateRate);
    }

    render_weapon_hud(arg1, updateRate);
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
                if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS && racer->racer.indicator_type < ASSET_TEX2D_30) {
                    indicator->unk0 = (s16) (0x8000 - indicator->unk0);
                }
                if (gHUDNumPlayers == 0 && racer->racer.raceFinished == FALSE && racer->racer.indicator_type && D_800E27B8 == 0) {
                    gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrTriList, indicator);
                    indicator->unkC = -indicator->unkC;
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrTriList, indicator);
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
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrTriList, indicator);
                indicator->unkC = (f32) -indicator->unkC;
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrTriList, indicator);
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

/**
 * The Egg Collector challenge mode displays the icons of each player and their score.
*/
void render_hud_challenge_eggs(s32 arg0, Object *arg1, s32 updateRate) {
    Object_Racer *racer = &arg1->unk64->racer;
    if (racer->raceFinished == FALSE) {
        func_80068508(1);
        func_800A3CE4(arg0, updateRate);
        render_weapon_hud(arg1, updateRate);
        if ((127 - (updateRate * 2)) >= D_80126CDC->unk67A) {
            D_80126CDC->unk67A += updateRate * 2;
        } else {
            D_80126CDC->unk67A = (D_80126CDC->unk67A + (updateRate * 2)) - 255;
        }
        if (D_80126D37 != 2) {
            func_800A14F0(arg1, updateRate);
        }
        func_80068508(0);
    }
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800A14F0.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A19A4.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A1C04.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A1E48.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A22F4.s")

/**
 * When racing the boss, render the essentials, but skip the bananas.
*/
void render_hud_race_boss(s32 arg0, Object *arg1, s32 updateRate) {
    LevelHeader *level;
    Object_64 *temp = arg1->unk64;

    func_80068508(1);
    render_wrong_way_text(temp, updateRate);
    func_800A3CE4(arg0, updateRate);
    render_race_time(temp, updateRate);
    render_weapon_hud(arg1, updateRate);

    level = get_current_level_header();
    if (level->laps > 1) {
        func_800A4F50(temp, updateRate);
    }

    func_800A3884(arg1, updateRate);
    func_800A4C44(temp, updateRate);
    func_80068508(0);
}

void func_800A263C(s32 arg0, Object *arg1, s32 updateRate) {
    Object_64 *temp = arg1->unk64;

    func_80068508(1);
    render_wrong_way_text(temp, updateRate);
    func_800A4F50(temp, updateRate);
    func_800A4C44(temp, updateRate);
    render_race_time(temp, updateRate);
    func_800A3CE4(arg0, updateRate);
    func_800A3884(arg1, updateRate);
    func_80068508(0);
}

/**
 * The hub world displays the player's balloon count.
 * In two player adventure, the icon of the character of the player sitting out is displayed.
*/
void render_hud_hubworld(Object *obj, s32 updateRate) {
    Object_64 *obj64;
    unk80126CDC *temp_a3;

    if (get_viewport_count() == 0) {
        obj64 = obj->unk64;
        func_80068508(1);
        func_800A718C(obj64);
        func_800A3884(obj, updateRate);
        if (is_in_two_player_adventure()) {
            temp_a3 = &D_80126CDC[1];
            temp_a3->unk6 = (get_settings()->racers[1].character + 0x38);
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrTriList, temp_a3);
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
    f32 textMoveSpeed;
    f32 textPosTarget;

    if (gHUDNumPlayers == 1) {
        func_8007BF1C(1);
    }
    if (obj->racer.unk1FC > 120 && (gHUDNumPlayers || D_80126CDC->unk46C == D_80126CDC->unk47A[2]) && !is_game_paused()) {
        if ((gWrongWayNagPrefix || gWrongWayNagTimer == 0) && gHUDVoiceSoundMask == NULL) {
            // 20% chance that T.T decides not to precede his nagging with "No no no!"
            if (gWrongWayNagPrefix || (get_random_number_from_range(1, 10) >= 8)) {
                gWrongWayNagPrefix = FALSE;
                play_sound_global(SOUND_VOICE_TT_WRONG_WAY, &gHUDVoiceSoundMask);
                gWrongWayNagTimer = get_random_number_from_range(1, 480) + 120;
            } else {
                gWrongWayNagPrefix = TRUE;
                play_sound_global(SOUND_VOICE_TT_NONONO, &gHUDVoiceSoundMask);
            }
        }
        gWrongWayNagTimer -= updateRate;
        if (gWrongWayNagTimer < 0) {
            gWrongWayNagTimer = 0;
        }
    }
    if (D_80126CDC->unk47A[0]) {
        if (D_80126CDC->unk47A[0] == 1) {
            if (D_80126CDC->unk47A[1] == 1) {
                textMoveSpeed = updateRate * 13;
                D_80126CDC->unk46C += textMoveSpeed;
                textPosTarget = D_80126CDC->unk47A[2];
                if (D_80126CDC->unk46C > textPosTarget) {
                    D_80126CDC->unk46C = textPosTarget;
                }
                D_80126CDC->unk48C -= textMoveSpeed;
                textPosTarget = D_80126CDC->unk49C;
                if (D_80126CDC->unk48C < textPosTarget) {
                    D_80126CDC->unk48C = textPosTarget;
                }
                if (obj->racer.unk1FC <= 90) {
                    D_80126CDC->unk47A[1] = -1;
                    play_sound_global(SOUND_WHOOSH1, NULL);
                }
            } else if (D_80126CDC->unk47A[1] == -1) {
                textMoveSpeed = updateRate * 13;
                D_80126CDC->unk46C -= textMoveSpeed;
                D_80126CDC->unk48C += textMoveSpeed;
                if (D_80126CDC->unk46C < -200.0f) {
                    D_80126CDC->unk47A[0] = 0;
                }
            }
            if (!is_game_paused()) {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrTriList, (unk80126CDC* ) &D_80126CDC->unk460);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrTriList, (unk80126CDC* ) &D_80126CDC->unk480);
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            }
        }
    } else if (obj->racer.unk1FC > 120) {
        D_80126CDC->unk47A[0] = 1;
        D_80126CDC->unk47A[1] = 1;
        D_80126CDC->unk47A[2] = -31;
        D_80126CDC->unk49C = 52;
        D_80126CDC->unk47A[3] = 0;
        if (gHUDNumPlayers == 1) {
            D_80126CDC->unk47A[2] = -21;
            D_80126CDC->unk49C = 42;
        } else  if (gHUDNumPlayers > 1) {
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
        play_sound_global(SOUND_WHOOSH1, NULL);
    }
    func_8007BF1C(0);
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800A5F18.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A6254.s")

/**
 * Play the normal race finish message, unless you beat your time record,
 * then T.T will say "Race Record" instead.
*/
void play_time_trial_end_message(s16 *playerID) {
    Settings *settings = get_settings();

    if (playerID != NULL) {
        if (settings->racers[*playerID].best_times & 0x80) {
            play_sound_global(SOUND_VOICE_TT_RACE_RECORD, &gHUDVoiceSoundMask);
        } else {
            play_sound_global(SOUND_VOICE_TT_FINISH, &gHUDVoiceSoundMask);
        }
    }
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800A6E30.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A718C.s")

/**
 * Unused function that plays whichever T.T voice line is passed through.
 * Only if the game is currently running and no voice line is already playing.
*/
UNUSED void play_hud_voice_line(u16 soundId) {
    if (gHUDVoiceSoundMask == NULL && !(is_game_paused())) {
        play_sound_global(soundId, &gHUDVoiceSoundMask);
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

/**
 * Renders the icon in the bottom left of the current weapon.
 * The icon will spin and grow as it appears, then spins and shrinks as it disappears.
*/
void render_weapon_hud(Object *obj, s32 updateRate) {
    Object_64 *racerObj;
    s32 temp_a0;

    racerObj = obj->unk64;
    if (racerObj->racer.raceFinished == FALSE) {
        set_viewport_tv_type(TV_TYPE_NTSC);
        temp_a0 = (racerObj->racer.balloon_type * 3) + (racerObj->racer.balloon_level);
        if (D_80126CDC->unk5D != racerObj->racer.balloon_level) {
            if (racerObj->racer.balloon_level == 0) {
                D_80126CDC->unk5C = 120;
            } else if (D_80126D37 == 1) {
                D_80126CDC->unk5C = 0;
            } else {
                D_80126CDC->unk5C = 120;
            }
            D_80126CDC->unk5D = racerObj->racer.balloon_level;
        }
        if (racerObj->racer.balloon_quantity > 0) {
            if (D_80126CDC->unk5B < 16 && racerObj->racer.unk170 == 0) {
                D_80126CDC->unk44 = D_80126CDC->unk5B << 12;
                D_80126CDC->unk48 = (D_80126CDC->unk5B * 0.04687) + 0.25;
            } else {
                D_80126CDC->unk44 = 0;
                D_80126CDC->unk48 = 1.0f;
            }
            D_80126CDC->unk58 = temp_a0;
            D_80126CDC->unk5B += updateRate;
            if (D_80126CDC->unk5B > 16) {
                D_80126CDC->unk5B = 16;
                D_80126CDC->unk5C += updateRate;
                if (D_80126CDC->unk5C > 120) {
                    D_80126CDC->unk5C = 120;
                } else if (gHUDNumPlayers == 0) {
                    D_80126CDC->unk48 += 0.18 * cosine_s(((f32) D_80126CDC->unk5C * 682.6583 * 4.0));
                }
            }
            if (gHUDNumPlayers > 0) {
                D_80126CDC->unk48 *= 0.75;
            }
            if (D_80126CDC->unk48 != 1.0) {
                func_8007BF1C(1);
            }
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrTriList, &D_80126CDC->unk40);
            func_8007BF1C(0);
            if (racerObj->racer.balloon_quantity > 3) {
                D_80126CDC->unk63A = -128;
            }
            if (racerObj->racer.balloon_quantity < 3) {
                D_80126CDC->unk63A -= updateRate;
            }
            if (racerObj->racer.balloon_quantity >= 3 || (((D_80126CDC->unk63A + 128) % 32) < 20) && racerObj->racer.balloon_quantity != 1) {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                D_80126CDC->unk638 = racerObj->racer.balloon_quantity - 1;
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrTriList, &D_80126CDC->unk620);
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            }
        } else {
            if (D_80126CDC->unk5B > 0) {
                D_80126CDC->unk44 = D_80126CDC->unk5B << 12;
                D_80126CDC->unk48 = (D_80126CDC->unk5B * 0.04687) + 0.25;
                D_80126CDC->unk5B -= updateRate;
                D_80126CDC->unk58 = temp_a0;
                if (D_80126CDC->unk5B < 0) {
                    D_80126CDC->unk5B = 0;
                }
                if (gHUDNumPlayers) {
                    D_80126CDC->unk48 /= 2;
                }
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrTriList, &D_80126CDC->unk40);
            }
        }
        gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
        set_viewport_tv_type(TV_TYPE_PAL);
    }
}

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

    if (!(gHUDNumPlayers && D_800E2794[gHUDNumPlayers][obj->racer.playerIndex] != 1) || (gHUDNumPlayers > 0 && obj->racer.lapCount > 0 && obj->racer.lap_times[obj->racer.lapCount] < 180)) {
        if (obj->racer.raceFinished == FALSE) {
            timerHideCounter = D_80126CDC->unk15A + 127;
            if (obj->racer.lapCount > 0 && obj->racer.lap_times[obj->racer.lapCount] < 180 && obj->racer.lapCount < D_80126D60->laps) {
                stopwatchTimer = obj->racer.lap_times[obj->racer.lapCount - 1];
                countingDown = TRUE;
                if (timerHideCounter == 0) {
                    timerHideCounter = 180;
                }
            } else {
                stopwatchTimer = 0;
                for (i = 0; obj->racer.unk194 >= i && i < D_80126D60->laps; i++) {
                    stopwatchTimer += obj->racer.lap_times[i];
                }
                countingDown = stopwatchTimer == 0 || obj->racer.raceFinished || is_game_paused();
                D_80126CDC->unk15A = -127;
                timerHideCounter = 0;
            }
            if (gHUDNumPlayers == 0) {
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrTriList, (unk80126CDC* ) &D_80126CDC->unk140);
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
                    gHideRaceTimer = TRUE;
                    return;
                } else {
                    if (gHideRaceTimer) {
                        if (gHUDNumPlayers == 0) {
                            play_sound_global(SOUND_HUD_LAP_TICK, NULL);
                        }
                        gHideRaceTimer = FALSE;
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
    gMinimapRed = (model->minimapColor >> 16) & 0xFF;
    gMinimapGreen = (model->minimapColor >> 8) & 0xFF;
    gMinimapBlue = model->minimapColor & 0xFF;
    load_sprite_info(model->unk20, &D_80126D1C, &D_80126D20, &sp2C, &sp2C, &sp2C);
    func_8007CA68(model->unk20, 0, &D_80126D14, &D_80126D18, &sp2C);
    model->unk20 = (s32)func_8007C12C(model->unk20, 1);
}

s8 func_800A8458(void) {
    return D_800E27A4[gHUDNumPlayers];
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
