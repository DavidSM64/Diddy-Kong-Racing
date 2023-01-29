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
#include "objects.h"
#include "game_text.h"
#include "object_models.h"
#include "unknown_0255E0.h"
#include "unknown_078050.h"
#include "unknown_003260.h"
#include "printf.h"
#include "unknown_008C40.h"

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

//!@bug Not every attribute is initialised, but since bss is initialised as 0, nothing happens.
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

s8 gHudToggleSettings[4] = {
    1, 1, 1, 1
};

s8 D_800E27A8 = 1;

s8 D_800E27AC[12] = {
    -1, 40, 40, -2,
    40, -1, 40, -2,
    40, 40, -1, -2,
};

u8 D_800E27B8 = 0;

ByteColour gHudMinimapColours[40] = {
 { 255, 160, 0 }, 
 { 255, 255, 0 }, 
 { 0, 128, 255 }, 
 { 255, 255, 255 }, 
 { 0, 175, 0 }, 
 { 0, 255, 128 }, 
 { 255, 0, 0 }, 
 { 255, 128, 190 },
 { 128, 128, 128 }, 
 { 0, 0, 255 }, 
 { 0, 0, 0 }, 
 { 0, 0, 0 },
 { 0, 0, 0 },
 { 0, 0, 0 },
 { 0, 0, 0 },
 { 32, 0, 0 },
 { 0, 0, 0 },
 { 0, 0, 64 },
 { 0, 0, 0 },
 { 0, 0, 0 },
 { 0, 96, 0 },
 { 0, 0, 0 },
 { 0, 0, 0 },
 { 128, 0, 0 },
 { 0, 0, 0 },
 { 0, 0, 0 },
 { 0, 64, 0 },
 { 0, 0, 0 },
 { 0, 32, 0 },
 { 64, 0, 0 },
 { 0, 0, 0 },
 { 64, 0, 64 }, 
 { 0, 0, 0 }, 
 { 0, 0, 96 }, 
 { 0, 64, 0 }, 
 { 0, 0, 0 }, 
 { 0, 128, 0 }, 
 { 64, 0, 0 }, 
 { 0, 0, 0 }, 
 { 0, 0, 0 },
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
s8 gShowHUD;
s8 D_80126CD3;

/**
 * gRaceStartShowHudStep counts up from 0->5 on race start, and is used to
 * coordinate when certain hud actions & audio clips play/happen:
 *   - set to 0 on loading of new race
 *   - 0->1 when camera shutter open animation occurs
 *   - 1->2 when hud slides into screen with "whoosh" sound
 *   - 2->3 on the "Get Ready!" voice play
 *   - 3->4 on the "Go" voice and text
 *   - 4->5 on the "Go" sliding off screen
 *   - stays 5 until the next race starts
*/
s8 gRaceStartShowHudStep;

s8 D_80126CD5;
u8 *D_80126CD8;
unk80126CDC *D_80126CDC;
unk80126CDC *D_80126CE0[3];
unk80126CDC *D_80126CEC;
s16 *D_80126CF0;
s32 *D_80126CF4;
s32 D_80126CF8;
Gfx *gHUDCurrDisplayList;
MatrixS *gHUDCurrMatrix;
Vertex *gHUDCurrVertex;
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
u8 gNumActivePlayers;
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
LevelHeader *gHudLevelHeader;
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
DrawTexture gHudSprites[128];
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
void render_hud(Gfx **dList, MatrixS **mtx, Vertex **vertexList, Object *arg3, s32 updateRate) {
    s32 sp2C;
    Object_64* racer;

    D_80126D08 = get_current_viewport();
    if (D_8012718A) {
        arg3 = get_racer_object_by_port(1 - D_80126D08);
    }
    gHudLevelHeader = get_current_level_header();
    if (arg3 == NULL) {
        if (func_8001E440() == 10) {
            arg3 = get_racer_object_by_port(0);
        }
    }
    if (arg3 != NULL && !(gHudLevelHeader->unkBC & 2)) {
        if (get_render_context() != DRAW_MENU) {
            gHUDCurrDisplayList = *dList;
            gHUDCurrMatrix = *mtx;
            gHUDCurrVertex = *vertexList;
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
            if (gShowHUD == 0) {
                racer = arg3->unk64;
                if (D_8012718A) {
                    D_80126D10 = 1 - racer->racer.playerIndex;
                } else {
                    D_80126D10 = racer->racer.playerIndex;
                }
                D_80126CDC = D_80126CE0[D_80126D08];
                if (func_8001E440() != 10) {
                    if (gHUDNumPlayers == ONE_PLAYER) {
                        if (get_buttons_pressed_from_player(D_80126D10) & D_CBUTTONS && racer->racer.raceFinished == FALSE && ((gHudLevelHeader->race_type == RACETYPE_DEFAULT) || gHudLevelHeader->race_type == RACETYPE_HORSESHOE_GULCH) && D_80126D34) {
                            D_800E2790 = 1 - D_800E2790;
                            play_sound_global((SOUND_TING_HIGHER + D_800E2790), NULL);
                            if (D_800E2790) {
                                D_800E27B8 = 0x78;
                            } else {
                                D_800E27B8 = 0;
                            }
                        }
                    } else if (get_buttons_pressed_from_player(D_80126D10) & D_CBUTTONS && racer->racer.raceFinished == FALSE && !(gHudLevelHeader->race_type & RACETYPE_CHALLENGE) && D_80126D34) {
                        if (D_800E2794[gHUDNumPlayers][racer->racer.playerIndex] < PLAYER_FOUR) {
                             D_800E2794[gHUDNumPlayers][racer->racer.playerIndex]++;
                        } else {
                             D_800E2794[gHUDNumPlayers][racer->racer.playerIndex] = PLAYER_ONE;
                        }
                        play_sound_global((SOUND_TING_HIGHEST - (D_800E2794[gHUDNumPlayers][racer->racer.playerIndex] == 0)), NULL);
                    }
                    if (get_buttons_pressed_from_player(D_80126D10) & R_CBUTTONS && racer->racer.raceFinished == FALSE && D_80126D34 && D_80126CD0 == 0) {
                        gHudToggleSettings[gHUDNumPlayers] = 1 - gHudToggleSettings[gHUDNumPlayers];
                        if (gHudToggleSettings[gHUDNumPlayers] == 0) {
                            play_sound_global(SOUND_TING_LOW, NULL);
                        } else {
                            play_sound_global(SOUND_TING_HIGH, NULL);
                        }
                    }
                }
                if (gRaceStartShowHudStep == 0) {
                    if (gHudLevelHeader->race_type & RACETYPE_CHALLENGE || gHudLevelHeader->race_type == RACETYPE_DEFAULT || gHudLevelHeader->race_type == RACETYPE_HORSESHOE_GULCH || gHudLevelHeader->race_type == RACETYPE_BOSS) {
                        D_800E2770[0].unk2 = 0x7F;
                        D_800E2770[1].unk2 = 0x7F;
                        func_80001844();
                        func_800012E8();
                        play_music(SEQUENCE_RACE_START_FANFARE);
                        set_sound_channel_count(12);
                    } else {
                        func_8006BD10(1.0f);
                    }
                    gRaceStartShowHudStep += 1;
                }
                gDPPipeSync(gHUDCurrDisplayList++);
                init_rsp(&gHUDCurrDisplayList);
                init_rdp_and_framebuffer(&gHUDCurrDisplayList);
                texEnableModes(0xFFFFFFFF);
                texDisableModes(RENDER_Z_COMPARE);
                func_8007BF1C(FALSE);
                if (check_if_showing_cutscene_camera() == FALSE && D_80126D34 == 0 && racer->racer.playerIndex == PLAYER_ONE) {
                    if (D_80126D35 != 0) {
                        D_80126D28 = sins_f(D_80126D2C) * D_80126D30 * 8.0f;
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
                        if (gRaceStartShowHudStep == 1) {
                            play_sound_global(SOUND_WHOOSH1, NULL);
                            gRaceStartShowHudStep += 1;
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
                set_ortho_matrix_view(&gHUDCurrDisplayList, &gHUDCurrMatrix);
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
                                if (is_taj_challenge() != 0) {
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
                                goto showFinish;
                            }
                            goto block_95;
                        }
showFinish:
                        render_race_finish_position(racer, updateRate);
                    } else {
block_95:
                        func_800A6254(racer, updateRate);
                    }
                    func_80068508(0);
                }
                D_80126CD1 = 0;
                func_8007BF1C(TRUE);
                if (D_80127180) {
                    gHudSprites[D_80127180].texture = NULL;
                    render_textured_rectangle(&gHUDCurrDisplayList, (DrawTexture *) &gHudSprites, 0, 0, 255, 255, 255, 255);
                }
                *dList = gHUDCurrDisplayList;
                *mtx = gHUDCurrMatrix;
                *vertexList = gHUDCurrVertex;
                texEnableModes(0xFFFFFFFF);
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
    render_race_start(arg0, updateRate);

    if (gHudLevelHeader->race_type == RACETYPE_DEFAULT) {
        render_lap_count(racer, updateRate);
    }

    render_racer_bananas(racer, updateRate);
    render_race_time(racer, updateRate);
    func_800A4C44(racer, updateRate);
    render_speedometer(arg1, updateRate);

    if (D_80127188 && racer->raceFinished == FALSE) {
        func_800A47A0(racer, updateRate);
    }

    render_weapon_hud(arg1, updateRate);
    func_80068508(0);
}

/**
 * Render the onscreen course arrows that show the player where to go.
*/
void render_course_indicator_arrows(Object_Racer *racer, s32 updateRate) {
    s32 timer;
    s32 type;
    IndicatorArrow *indicator;

    if (D_800E2790) {
        timer = racer->indicator_timer;
        if (timer > 0) {
            type = racer->indicator_type;
            racer->indicator_timer = timer - updateRate;
            if (type) {
                indicator = (IndicatorArrow *) &D_80126CDC->courseIndicator;
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
                if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS && racer->indicator_type < ASSET_TEX2D_30) {
                    indicator->unk0 = (s16) (0x8000 - indicator->unk0);
                }
                if (gHUDNumPlayers == ONE_PLAYER && racer->raceFinished == FALSE && racer->indicator_type && D_800E27B8 == 0) {
                    gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC **) indicator);
                    indicator->unkC = -indicator->unkC;
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC **) indicator);
                    indicator->unkC = -indicator->unkC;
                    indicator->unk2 = 0;
                    gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
                }
            }
        } else {
            racer->indicator_timer = 0;
        }
        if (D_800E27B8) {
            if (D_800E27B8 & 0x20) {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                indicator = (IndicatorArrow *) &D_80126CDC->courseIndicator;
                indicator->unk0 = 0;
                indicator->unk2 = 0;
                indicator->textureID = ASSET_TEX2D_29;
                if ((get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) && ((s32) racer->indicator_type < ASSET_TEX2D_30)) {
                    indicator->unk0 = (s16) (0x8000 - indicator->unk0);
                }
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC **) indicator);
                indicator->unkC = (f32) -indicator->unkC;
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC **) indicator);
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
        render_race_start(arg0, updateRate);
        render_weapon_hud(arg1, updateRate);
        if ((127 - (updateRate * 2)) >= D_80126CDC->unk67A) {
            D_80126CDC->unk67A += updateRate * 2;
        } else {
            D_80126CDC->unk67A = (D_80126CDC->unk67A + (updateRate * 2)) - 255;
        }
        if (gNumActivePlayers != 2) {
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
void render_hud_race_boss(s32 arg0, Object *obj, s32 updateRate) {
    LevelHeader *level;
    Object_Racer *racer = (Object_Racer *) obj->unk64;

    func_80068508(1);
    render_wrong_way_text(racer, updateRate);
    render_race_start(arg0, updateRate);
    render_race_time(racer, updateRate);
    render_weapon_hud(obj, updateRate);

    level = get_current_level_header();
    if (level->laps > 1) {
        render_lap_count(racer, updateRate);
    }

    render_speedometer(obj, updateRate);
    func_800A4C44(racer, updateRate);
    func_80068508(0);
}

void func_800A263C(s32 arg0, Object *obj, s32 updateRate) {
    Object_Racer *racer = (Object_Racer *) obj->unk64;

    func_80068508(1);
    render_wrong_way_text(racer, updateRate);
    render_lap_count(racer, updateRate);
    func_800A4C44(racer, updateRate);
    render_race_time(racer, updateRate);
    render_race_start(arg0, updateRate);
    render_speedometer(obj, updateRate);
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
        render_speedometer(obj, updateRate);
        if (is_in_two_player_adventure()) {
            temp_a3 = &D_80126CDC[1];
            temp_a3->unk6 = (get_settings()->racers[1].character + 0x38);
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC **) temp_a3);
        }
        func_80068508(0);
    }
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800A277C.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A36CC.s")

void func_800A3870(void) {
    D_80126CDC->unk4C4 = 0x6490;
}

/**
 * When enabled, displays speed of the player in the bottom right corner, replacing the minimap.
 * Speed is calculated by normalising racer velocity. then scaling the angle of the needle with that number.
*/
void render_speedometer(Object *obj, UNUSED s32 updateRate) {
    f32 vel;
    Object_64* racer64;
    s32 opacity;

    if (gNumActivePlayers == 1) {
        if (!check_if_showing_cutscene_camera()) {
            racer64 = obj->unk64;
            if (racer64->racer.raceFinished == FALSE) {
                if (racer64->racer.vehicleID == VEHICLE_PLANE) {
                    vel = sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) + (obj->segment.y_velocity * obj->segment.y_velocity) + (obj->segment.z_velocity * obj->segment.z_velocity));
                } else {
                    vel = sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) + (obj->segment.z_velocity * obj->segment.z_velocity));
                }
                if (D_800E2838 < vel) {
                    D_800E2838 = vel;
                }
                vel *= 4.0f;
                if (racer64->racer.drift_direction != 0) {
                    vel += 7.0f;
                }
                if (vel > 100.0f) {
                    vel = 100.0f;
                }
                if (racer64->racer.velocity > 0.0f) {
                    vel = 0.0f;
                }
                vel = 100.0f - vel;
                vel *= 300.0f;
                if (vel > 25744.0f) {
                    vel = 25744.0f;
                }
                if (!is_game_paused()) {
                    if (vel < D_80126CDC->unk4C4) {
                        D_80126CDC->unk4C4 += ((vel - D_80126CDC->unk4C4) / 2);
                    } else {
                        D_80126CDC->unk4C4 += ((vel - D_80126CDC->unk4C4) / 8);
                    }
                }
                if (gHudToggleSettings[gHUDNumPlayers] == 0) {
                    if (D_80126CD3 & 2) {
                        opacity = 255.0f - ((D_80126CD0 * 255.0f) / D_8012718B);
                    } else {
                        opacity = 255;
                    }
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk5A0);
                    reset_render_settings(&gHUDCurrDisplayList);
                    func_8007BF1C(TRUE);
                    gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, opacity);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk4C0);
                    func_8007BF1C(FALSE);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk4E0);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk500);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk520);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk540);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk560);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk580);
                }
            }
        }
    }
}


/**
 * Call the functions that render the "Get Ready" and "GO!" as well as their countdowns to control fade.
 * This function will also call to begin the background music for 1 and 2 player. 3 and 4 are treated with silence.
*/
void render_race_start(s32 arg0, s32 updateRate) {

    if (!is_game_paused()) {
        if (arg0 == 0 && D_800E2770[0].unkC == -1) {
            D_800E2770[0].unk3 = -1;
            D_800E2770[1].unk3 = -1;
        }
        if (gHUDNumPlayers == TWO_PLAYERS) {
            func_8007BF1C(TRUE);
        }
        if (arg0 > 0) {
            if (D_80126D34) {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, (arg0 * 255) / 40);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk1A0);
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
                if (gRaceStartShowHudStep == 2) {
                    play_sound_global(SOUND_VOICE_TT_GET_READY, &gHUDVoiceSoundMask);
                    gRaceStartShowHudStep++;
                }
            }
            if (D_80126D3C == 0 && func_80023568() == 0) {
                f32 sp4C;
                UNUSED s32 pad;
                Object** racerGroup;
                Object* randomRacer;
                Object_Racer* racer;
                s32 numRacerObjects;
                racerGroup = get_racer_objects(&numRacerObjects);
                randomRacer = racerGroup[get_random_number_from_range(1, numRacerObjects) - 1];
                racer = (Object_Racer*)randomRacer->unk64;
                if (racer->vehicleID == VEHICLE_CAR) {
                    if (get_random_number_from_range(0, 100) >= 96) {
                        sp4C = 1.25 - ((get_random_number_from_range(0, 7) * 0.5) / 7.0);
                        func_800095E8(76, randomRacer->segment.trans.x_position, randomRacer->segment.trans.y_position, randomRacer->segment.trans.z_position, 4, ((get_random_number_from_range(0, 7) * 63) / 7) + 24, sp4C * 100.0f, &D_80126D3C);
                    }
                }
            }
        } else if (D_80126CDC->unk18C > -200.0f) {
            gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk180);
            gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            D_80126CDC->unk19A[D_80126D08] += updateRate;
            if (D_80126CDC->unk19A[D_80126D08] >= 60) {
                if (gRaceStartShowHudStep == 4) {
                    // Mute background music in 3/4 player.
                    if (get_viewport_count() > TWO_PLAYERS) {
                        play_music(SEQUENCE_NONE);
                    } else {
                        func_8006BD10(1.0f);
                    }
                    play_sound_global(SOUND_WHOOSH1, NULL);
                    gRaceStartShowHudStep++;
                }
                D_80126CDC->unk18C -= (updateRate * 8);
            }
            if (gRaceStartShowHudStep == 3) {
                play_sound_global(SOUND_VOICE_TT_GO, &gHUDVoiceSoundMask);
                if ((func_8001B640() != 0) && (func_8001B650() == 0)) {
                    func_800A7484(0x24B, 1.7f, 0);
                    func_800C3158(0x52, 1.7f);
                }
                D_80126D70 = 1;
                gRaceStartShowHudStep++;
            }
        }
        func_8007BF1C(FALSE);
    }
}

/**
 * Renders the banana counter on screen.
 * When a banana is collected, render sparkles and animate the banana. for a brief moment.
*/
void render_racer_bananas(Object_Racer *racer, s32 updateRate) {
    s32 bananas;
    UNUSED s16 pad;
    s32 temp_lo;
    u8 var_v1;
    if(racer->playerIndex == PLAYER_COMPUTER || (((gHUDNumPlayers < TWO_PLAYERS || D_800E2794[gHUDNumPlayers][racer->playerIndex] == PLAYER_THREE || gHudLevelHeader->race_type == RACETYPE_CHALLENGE_BANANAS || gHudLevelHeader->race_type == RACETYPE_CHALLENGE_BATTLE) && racer->raceFinished == FALSE) && (gHUDNumPlayers < TWO_PLAYERS || (racer->lap < 1) || racer->lap_times[racer->lap] >= 180 || gHudLevelHeader->race_type & RACETYPE_CHALLENGE))) {
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk240);
        bananas = racer->bananas;
        var_v1 = D_80126CDC->unkF8;
        if ((D_80126CDC->unkFA == 0) && (D_80126CDC->unkFB != racer->bananas)) {
            D_80126CDC->unkFA = 2;
            D_80126CDC->unkFB = racer->bananas;
        } else if (D_80126CDC->unkFA) {
            D_80126CDC->unk388 = 2.0f;
            var_v1 += updateRate * 13;
            if (var_v1 < (D_80126CDC->unkF8 & 0xFF)) {
                D_80126CDC->unkFA--;
                if (D_80126CDC->unkFA == 0) {
                    D_80126CDC->unk39B = 1;
                    D_80126CDC->unk39A = 6;
                    var_v1 = 0;
                    D_80126CDC->unk398 = 1;
                }
            }
        }
        if (var_v1 == 0) {
            func_8007BF1C(TRUE);
            set_viewport_tv_type(TV_TYPE_NTSC);
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk360);
            set_viewport_tv_type(TV_TYPE_PAL);
            func_8007BF1C(FALSE);
            D_80126CDC->unkF8 = var_v1;
            if (D_80126CDC->unk39B) {
                D_80126CDC->unk39A -= updateRate;
                if (D_80126CDC->unk39A < 0) {
                    D_80126CDC->unk39A = 6;
                    if (D_80126CDC->unk398 == 6) {
                        D_80126CDC->unk398 = 0;
                        D_80126CDC->unk39B--;
                    } else {
                        D_80126CDC->unk398++;
                    }
                }
                set_viewport_tv_type(TV_TYPE_NTSC);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk380);
                set_viewport_tv_type(TV_TYPE_PAL);
            }
        } else {
            D_80126CDC->unkF8 = var_v1 + 128;
            func_80068508(0);
            func_8007BF1C(TRUE);
            set_viewport_tv_type(TV_TYPE_NTSC);
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unkE0);
            func_8007BF1C(FALSE);
            set_viewport_tv_type(TV_TYPE_PAL);
            func_80068508(1);
            D_80126CDC->unkF8 -= 128;
        }
        temp_lo = bananas / 10;
        if (temp_lo) {
            D_80126CDC->unk118 = temp_lo;
            D_80126CDC->unk138 = bananas % 10;
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk120);
        } else {
            D_80126CDC->unk118 = bananas % 10;
        }
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk100);
        gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
    }
}

/**
 * Renders the icons and secured treasure in Smokey's castle.
 * In 4 player, all icons are skipped and in 3 player, player 4's icon is shown on their quadrant.
*/
void render_treasure_hud(Object_Racer *racer) {
    s32 i;
    s32 sp48;

    sp48 = D_80126CDC->unk410;
    if (gNumActivePlayers < 3 || (gNumActivePlayers == 3 && racer->playerIndex == PLAYER_COMPUTER)) {
        D_80126CDC->unk646 = racer->characterId + 56;
        D_80126CD5 = TRUE;
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk640);
        D_80126CD5 = FALSE;
    }
    for (i = 0; i < 10; i++) {
        if (i >= racer->lap) {
            D_800E2834 = 0x80808080;
        }
        D_80126CD5 = TRUE;
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk400);
        D_80126CD5 = FALSE;
        D_80126CDC->unk410 -= 3.0f;
    }
    D_80126CDC->unk410 = sp48;
    D_800E2834 = -2;
    D_80126CD5 = 0;
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800A47A0.s")

/**
 * Plays the race finish fanfare and displays what position you finished
 * in the middle of the screen.
 * Uses a 3 step process to play the sounds, display the position, then slide it offscreen.
*/
void render_race_finish_position(Object_64 *obj, s32 updateRate) {
    unk800A497C* temp_a3;
    unk800A497C* temp_s0;
    s8 drawPosition;

    temp_a3 = (unk800A497C *) &D_80126CDC->unk700;
    temp_s0 = (unk800A497C *) (&D_80126CDC->unk700 + 16); // Hacky workaround to the struct being assumed to be 0x720 bytes.
    //temp_s0 = &D_80126CDC->unk740;
    drawPosition = FALSE;
    switch (temp_a3->unk1A) {
        case 0:
            set_music_player_voice_limit(24);
            play_music(SEQUENCE_FIRST_PLACE);
            play_sound_global(SOUND_WHOOSH1, NULL);
            play_sound_global(SOUND_VOICE_TT_FINISH, &gHUDVoiceSoundMask);
            D_800E2770->unk2 = 127;
            D_800E2770->unk3 = 0;
            D_800E2770->unkC = obj->racer.playerIndex;
            temp_a3->unk1A = 1;
            break;
        case 1:
            temp_a3->unkC += updateRate * 13;
            if (temp_a3->unkC > -23.0f) {
                temp_a3->unkC = -23.0f;
            }
            temp_s0->unkC -= updateRate * 13;
            if (temp_s0->unkC < 22.0f) {
                temp_s0->unkC = 22.0f;
            }
            drawPosition = TRUE;
            if (temp_s0->unkC == 22.0f) {
                temp_a3->unk1B += updateRate;
                if (temp_a3->unk1B >= 120) {
                    temp_a3->unk1B = -120;
                    temp_a3->unk1C = temp_a3->unk1C + 1;
                }
                if (temp_a3->unk1C == 2) {
                    temp_a3->unk1A = 2;
                    play_sound_global(SOUND_WHOOSH1, NULL);
                    if (D_800E2770->unkC == obj->racer.playerIndex) {
                        D_800E2770->unk3 = -1;
                    }
                }
            }
            break;
        case 2:
            temp_a3->unkC += updateRate * 13;
            temp_s0->unkC += updateRate * 13;
            drawPosition = TRUE;
            if (temp_a3->unkC > 200.0f) {
                temp_a3->unk1A = 3;
            }
            break;
        case 3:
            temp_a3->unk1A = 3;
            break;
    }
    if (drawPosition) {
        gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 210);
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC **) temp_a3);
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC **) temp_s0);
        gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
    }
}


UNUSED void func_800A4C34(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2) {}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800A4C44.s")

/**
 * Displays the current lap number onscreen.
 * Also displays the "Lap 2" and "Final Lap" messages when the line is crossed.
 * In multiplayer, shows a cut down display, if the display setting is set to show laps.
*/
void render_lap_count(Object_Racer *racer, s32 updateRate) {
    if (racer->raceFinished == FALSE && (gHUDNumPlayers <= ONE_PLAYER || racer->lap <= 0 || racer->lap_times[racer->lap] >= 180) 
            && (gHUDNumPlayers <= ONE_PLAYER || D_800E2794[gHUDNumPlayers][racer->playerIndex] == 3)) {
        if (gHudLevelHeader->laps == (0, racer->unk194 + 1) && gHUDNumPlayers < THREE_PLAYERS) {
            D_80126CDC->unk21A += updateRate;
            if (D_80126CDC->unk21A > 6) {
                D_80126CDC->unk218++;
                D_80126CDC->unk21A -= 6;
                if (D_80126CDC->unk218 > 4) {
                    D_80126CDC->unk218 = 0;
                }
            }
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk200);
        }
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk60);
        if (racer->unk194 >= gHudLevelHeader->laps - 1) {
            D_80126CDC->unk98 = gHudLevelHeader->laps;
        } else {
            D_80126CDC->unk98 = racer->unk194 + 1;
        }
        D_80126CDC->unkD8 = gHudLevelHeader->laps;
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk80);
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unkA0);
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unkC0);
    }
    if (gHUDNumPlayers == TWO_PLAYERS) {
        func_8007BF1C(TRUE);
    }
    if (is_game_paused() == FALSE) {
        if (racer->lap_times[racer->lap] < 30 && D_80126CDC->unk3DA == 0 && racer->raceFinished == FALSE) {
            if ((racer->lap == 1) && gHudLevelHeader->laps >= 3) {
                D_80126CDC->unk3DA = 2;
                D_80126CDC->unk3DB = 1;
                D_80126CDC->unk3DD = 0;
                play_sound_global(SOUND_WHOOSH1, NULL);
                switch (gHUDNumPlayers) {
                case ONE_PLAYER:
                    D_80126CDC->unk3DC = -21;
                    D_80126CDC->unk3FC = 32;
                    D_80126CDC->unk3CC = -200.0f;
                    D_80126CDC->unk3EC = 211.0f;
                    break;
                case TWO_PLAYERS:
                    D_80126CDC->unk3DC = -16;
                    D_80126CDC->unk3FC = 27;
                    D_80126CDC->unk3CC = -200.0f;
                    D_80126CDC->unk3EC = 211.0f;
                    break;
                default:
                    if (racer->playerIndex != PLAYER_ONE && racer->playerIndex != PLAYER_THREE) {
                        D_80126CDC->unk3DC = 60;
                        D_80126CDC->unk3FC = 91;
                        D_80126CDC->unk3CC = -70.0f;
                        D_80126CDC->unk3EC = 221.0f;
                    } else {
                        D_80126CDC->unk3DC = -90;
                        D_80126CDC->unk3FC = -59;
                        D_80126CDC->unk3CC = -220.0f;
                        D_80126CDC->unk3EC = 71.0f;
                    }
                    break;
                }
            } else if (gHudLevelHeader->laps == (0, racer->lap + 1) && racer->lap != 0) {
                D_80126CDC->unk3DA = 3;
                D_80126CDC->unk3DB = -1;
                D_80126CDC->unk3DD = 0;
                play_sound_global(SOUND_WHOOSH1, NULL);
                switch (gHUDNumPlayers) {
                case ONE_PLAYER:
                    D_80126CDC->unk3DC = 51;
                    D_80126CDC->unk3BC = -41;
                    D_80126CDC->unk3CC = 210.0f;
                    D_80126CDC->unk3AC = -200.0f;
                    break;
                case TWO_PLAYERS:
                    D_80126CDC->unk3DC = 41;
                    D_80126CDC->unk3BC = -31;
                    D_80126CDC->unk3CC = 210.0f;
                    D_80126CDC->unk3AC = -200.0f;
                    break;
                default:
                    if (racer->playerIndex != PLAYER_ONE && racer->playerIndex != PLAYER_THREE) {
                        D_80126CDC->unk3DC = 100;
                        D_80126CDC->unk3BC = 50;
                        D_80126CDC->unk3CC = 100.0f;
                        D_80126CDC->unk3AC = -50.0f;
                    } else {
                        D_80126CDC->unk3DC = -50;
                        D_80126CDC->unk3BC = -100;
                        D_80126CDC->unk3CC = 50.0f;
                        D_80126CDC->unk3AC = -200.0f;
                    }
                    break;
                }
            }
        }
        if (D_80126CDC->unk3DA != 0) {
            if (D_80126CDC->unk3DA == 2) {
                if (D_80126CDC->unk3DB == 1) {
                    if (D_80126CDC->unk3CC < D_80126CDC->unk3DC - (updateRate * 13)) {
                        D_80126CDC->unk3CC = D_80126CDC->unk3CC + (updateRate * 13);
                    } else {
                        D_80126CDC->unk3CC = D_80126CDC->unk3DC;
                    }
                    if (D_80126CDC->unk3EC > D_80126CDC->unk3FC + (updateRate * 13)) {
                        D_80126CDC->unk3EC = D_80126CDC->unk3EC - (updateRate * 13);
                    } else {
                        D_80126CDC->unk3EC = D_80126CDC->unk3FC;
                    }
                    if (racer->lap_times[racer->lap] >= 60) {
                        D_80126CDC->unk3DB = -1;
                        play_sound_global(SOUND_WHOOSH1, NULL);
                    }
                    if (D_80126CDC->unk3CC == ((0, D_80126CDC))->unk3DC && D_80126CDC->unk3EC == ((0, D_80126CDC))->unk3FC && D_80126CDC->unk3DD == 0) {
                        if (gHUDVoiceSoundMask == NULL) {
                            play_sound_global(SOUND_VOICE_TT_LAP2, &gHUDVoiceSoundMask);
                        }
                        D_80126CDC->unk3DD = 1;
                    }
                } else if (D_80126CDC->unk3DB == -1) {
                    D_80126CDC->unk3CC = D_80126CDC->unk3CC - (updateRate * 13);
                    D_80126CDC->unk3EC = D_80126CDC->unk3EC + (updateRate * 13);
                    if (D_80126CDC->unk3CC < -200.0f) {
                        D_80126CDC->unk3DA = 0;
                    }
                }
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk3E0);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk3C0);
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            } else if (D_80126CDC->unk3DA == 3) {
                if (D_80126CDC->unk3DB == -1) {
                    if (D_80126CDC->unk3CC > D_80126CDC->unk3DC + (updateRate * 13)) {
                        D_80126CDC->unk3CC = D_80126CDC->unk3CC - (updateRate * 13);
                    } else {
                        D_80126CDC->unk3CC = D_80126CDC->unk3DC;
                    }
                    if (D_80126CDC->unk3AC < D_80126CDC->unk3BC - (updateRate * 13)) {
                        D_80126CDC->unk3AC = D_80126CDC->unk3AC + (updateRate * 13);
                    } else {
                        D_80126CDC->unk3AC = D_80126CDC->unk3BC;
                    }
                    if (racer->lap_times[racer->lap] >= 60) {
                        D_80126CDC->unk3DB = 1;
                        play_sound_global(SOUND_WHOOSH1, NULL);
                    }
                    if (D_80126CDC->unk3CC == ((0, D_80126CDC))->unk3DC && D_80126CDC->unk3AC == ((0, D_80126CDC))->unk3BC && D_80126CDC->unk3DD == 0) {
                        if (gHUDVoiceSoundMask == NULL) {
                            play_sound_global(SOUND_VOICE_TT_FINAL_LAP, &gHUDVoiceSoundMask);
                        }
                        D_80126CDC->unk3DD = 1;
                    }
                } else if (D_80126CDC->unk3DB == 1) {
                    D_80126CDC->unk3CC = D_80126CDC->unk3CC + (updateRate * 13);
                    D_80126CDC->unk3AC = D_80126CDC->unk3AC - (updateRate * 13);
                    if (D_80126CDC->unk3CC > 200.0f) {
                        D_80126CDC->unk3DA = 0;
                    }
                }
                
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk3A0);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk3C0);
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            }
        }
    }
    func_8007BF1C(FALSE);
}

/**
 * Players going the wrong way will be nagged by T.T to turn around.
 * This function plays the audio, and makes the text fly in.
*/
void render_wrong_way_text(Object_Racer *obj, s32 updateRate) { 
    f32 textMoveSpeed;
    f32 textPosTarget;

    if (gHUDNumPlayers == TWO_PLAYERS) {
        func_8007BF1C(TRUE);
    }
    if (obj->unk1FC > 120 && (gHUDNumPlayers || D_80126CDC->unk46C == D_80126CDC->unk47A[2]) && !is_game_paused()) {
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
                if (obj->unk1FC <= 90) {
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
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk460);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk480);
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            }
        }
    } else if (obj->unk1FC > 120) {
        D_80126CDC->unk47A[0] = 1;
        D_80126CDC->unk47A[1] = 1;
        D_80126CDC->unk47A[2] = -31;
        D_80126CDC->unk49C = 52;
        D_80126CDC->unk47A[3] = 0;
        if (gHUDNumPlayers == TWO_PLAYERS) {
            D_80126CDC->unk47A[2] = -21;
            D_80126CDC->unk49C = 42;
        } else  if (gHUDNumPlayers > TWO_PLAYERS) {
            if (obj->playerIndex == PLAYER_ONE || obj->playerIndex == PLAYER_THREE) {
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
    func_8007BF1C(FALSE);
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
            } else if (gNumActivePlayers == 1) {
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
                } else if (gHUDNumPlayers == ONE_PLAYER) {
                    D_80126CDC->unk48 += 0.18 * sins_f(((f32) D_80126CDC->unk5C * 682.6583 * 4.0));
                }
            }
            if (gHUDNumPlayers > ONE_PLAYER) {
                D_80126CDC->unk48 *= 0.75;
            }
            if (D_80126CDC->unk48 != 1.0) {
                func_8007BF1C(TRUE);
            }
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk40);
            func_8007BF1C(FALSE);
            if (racerObj->racer.balloon_quantity > 3) {
                D_80126CDC->unk63A = -128;
            }
            if (racerObj->racer.balloon_quantity < 3) {
                D_80126CDC->unk63A -= updateRate;
            }
            if (racerObj->racer.balloon_quantity >= 3 || ((((D_80126CDC->unk63A + 128) % 32) < 20) && racerObj->racer.balloon_quantity != 1)) {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                D_80126CDC->unk638 = racerObj->racer.balloon_quantity - 1;
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk620);
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
                if (gHUDNumPlayers != ONE_PLAYER) {
                    D_80126CDC->unk48 /= 2;
                }
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk40);
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
void render_race_time(Object_Racer *racer, s32 updateRate) {
    s32 i;
    s32 stopwatchTimer;
    s32 minutes;
    s32 seconds;
    s32 hundredths;
    s32 countingDown;
    s32 timerHideCounter;

    if (!(gHUDNumPlayers != ONE_PLAYER && D_800E2794[gHUDNumPlayers][racer->playerIndex] != 1) || (gHUDNumPlayers > ONE_PLAYER && racer->lap > 0 && racer->lap_times[racer->lap] < 180)) {
        if (racer->raceFinished == FALSE) {
            timerHideCounter = D_80126CDC->unk15A + 127;
            if (racer->lap > 0 && racer->lap_times[racer->lap] < 180 && racer->lap < gHudLevelHeader->laps) {
                stopwatchTimer = racer->lap_times[racer->lap - 1];
                countingDown = TRUE;
                if (timerHideCounter == 0) {
                    timerHideCounter = 180;
                }
            } else {
                stopwatchTimer = 0;
                for (i = 0; racer->unk194 >= i && i < gHudLevelHeader->laps; i++) {
                    stopwatchTimer += racer->lap_times[i];
                }
                countingDown = stopwatchTimer == 0 || racer->raceFinished || is_game_paused();
                D_80126CDC->unk15A = -127;
                timerHideCounter = 0;
            }
            if (gHUDNumPlayers == ONE_PLAYER) {
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk140);
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
                        if (gHUDNumPlayers == ONE_PLAYER) {
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
            
            if (gNumActivePlayers == 1) {
                func_800A7FBC(D_80126CDC->unk16C, D_80126CDC->unk170, minutes, seconds, hundredths, 0);
            } else {
                func_800A7FBC(D_80126CDC->unk16C, D_80126CDC->unk170, minutes, seconds, hundredths, 1);
            }
            gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
        }
    }
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800A7FBC.s")

/**
 * Loads the minimap sprite from the level data, then sets the global colours for the minimap.
*/
void minimap_init(LevelModel *model) {
    s32 sp2C;
    gMinimapRed = (model->minimapColor >> 16) & 0xFF;
    gMinimapGreen = (model->minimapColor >> 8) & 0xFF;
    gMinimapBlue = model->minimapColor & 0xFF;
    load_sprite_info(model->minimapSprite, &D_80126D1C, &D_80126D20, &sp2C, &sp2C, &sp2C);
    func_8007CA68(model->minimapSprite, 0, &D_80126D14, &D_80126D18, &sp2C);
    model->minimapSprite = (s32) func_8007C12C(model->minimapSprite, 1);
}

/**
 * Returns the hud settings value for the mumber of active players.
 * For player 1, it's switching between the minimap and speedometre.
 * For 2 players, it's for toggling the minimap
 * For 3 players, it's for toggling between the minimap and a spectator cam in viewport 4.
 * For 4 players, it's for toggling the minimap.
*/
s8 get_hud_setting(void) {
    return gHudToggleSettings[gHUDNumPlayers];
}

/**
 * Renders the minimap in all modes as well as a few other random pieces of HUD.
 * This function also handles the HUD in 3 or 4 player, instead of the normal dedicated functions it has.
*/
void render_minimap_and_misc_hud(Gfx **dList, MatrixS **mtx, Vertex **vtx, s32 updateRate) {
    Object_Racer *curRacerObj;
    LevelModel *lvlMdl;
    Sprite *minimap;
    Object **objectGroup;
    Object_Racer *tempVar4;
    Object_Racer *someRacer;
    s32 i;
    s32 objectCount;
    UNUSED s32 tempVar3;
    ObjectTransform_800A8474 objTrans;
    f32 sp11C;
    f32 sp118;
    f32 sp114;
    u8 sp113;
    s32 mapOpacity;
    s32 opacity;
    UNUSED s32 pad[2];
    s32 temp_s1_2;
    s32 var_a0_5;
    s32 spF4;
    s32 spF0;
    s32 tempVar1;
    s32 temp_s1_3;
    s32 spE4;
    s32 spE0;
    UNUSED s32 pad9;
    Object *temp_v0_8;
    s32 tempVar2;
    s32 sp144;
    s32 racerCount;
    UNUSED s32 pad2;
    ObjectSegment *someObjSeg;
    Object **racerGroup;
    s32 spBC;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s1;
    s32 temp_s0;
    s32 temp_f16;
    s32 temp_f6;
    s32 temp_s3;
    s32 temp;
    UNUSED s32 pad3[4];
    
    func_800A0BD4(updateRate);
    
    D_80126CD8[1] = 0;
    D_80126CD8[23] = 0;
    D_80126CD8[8] = 0;
    D_80126CD8[17] = 0;
    D_80127180 = 0;
    
    if (D_80126CD3 & 2) {
        mapOpacity = 255.0f - ((D_80126CD0 * 255.0f) / D_8012718B);
    } else {
        mapOpacity = 255;
    }
    
    for (i = 0; i < D_80126CF8; i++) {
        if (D_80126CF4[i] && i != 40) {
            if (++D_80126CD8[i] > 60) {
                if ((D_80126CF0[i] & (0x4000 | 0x8000)) == (0x4000 | 0x8000)) {
                    free_texture((TextureHeader *)D_80126CF4[i]);
                } else if (D_80126CF0[i] & 0x8000) {
                    free_sprite((Sprite *) D_80126CF4[i]);
                } else if (D_80126CF0[i] & 0x4000) {
                    gParticlePtrList_addObject((Object *) D_80126CF4[i]);
                } else {
                    func_8005FF40((ObjectModel **) D_80126CF4[i]);
                }
                D_80126CF4[i] = 0;
            }
        }
    }
    
    gHudLevelHeader = get_current_level_header();
    objectGroup = get_racer_objects_by_port(&objectCount);
    gHUDCurrDisplayList = *dList;
    gHUDCurrMatrix = *mtx;
    gHUDCurrVertex = *vtx;
    if (gHudLevelHeader->race_type == RACETYPE_CHALLENGE_EGGS) {
        if (gNumActivePlayers == 2 && gHudToggleSettings[gHUDNumPlayers] == 0) {
            func_800A14F0(NULL, updateRate);
            reset_render_settings(&gHUDCurrDisplayList);
        } else {
            if (gNumActivePlayers == 3) {
                tempVar4 = NULL;
                for(tempVar2 = 0; tempVar2 < objectCount; tempVar2++) {
                    if (objectGroup[tempVar2]->unk64->racer.playerIndex == PLAYER_COMPUTER) {
                        tempVar4 = &objectGroup[tempVar2]->unk64->racer;
                    }
                }
                if (tempVar4 != NULL) {
                    temp_s0 = D_80126CDC->unk64C;
                    temp_s1 = D_80126CDC->unk650;
                    spF4 = D_80126CDC->unk66C;
                    spF0 = D_80126CDC->unk670;
                    D_80126CDC->unk64C = 225.0f;
                    D_80126CDC->unk66C = 221.0f;
                    D_80126CDC->unk670 = 197.0f;
                    D_80126CDC->unk650 = 165.0f;
                    if (osTvType == TV_TYPE_PAL) {
                        D_80126CDC->unk64C -= 4.0f;
                        D_80126CDC->unk66C -= 4.0f;
                        D_80126CDC->unk650 *= 1.1;
                        D_80126CDC->unk670 *= 1.1;
                    }
                    func_800A19A4(tempVar4, updateRate);
                    D_800E2834 = -2;
                    D_80126CDC->unk64C = temp_s0;
                    D_80126CDC->unk650 = temp_s1;
                    D_80126CDC->unk66C = spF4;
                    D_80126CDC->unk670 = spF0;
                }
            }
        }
    } else if (gHudLevelHeader->race_type == RACETYPE_CHALLENGE_BATTLE) {
        // Show life counter and icons in 2 player.
        if (gNumActivePlayers == 2 && gHudToggleSettings[gHUDNumPlayers] == 0) {
            func_80068508(TRUE);
            func_8007BF1C(FALSE);
            set_ortho_matrix_view(&gHUDCurrDisplayList, &gHUDCurrMatrix);
            func_800A1E48(0, updateRate);
            func_80068508(FALSE);
            reset_render_settings(&gHUDCurrDisplayList);
            func_8007BF1C(TRUE);
        } else {
            // In 3/4 player, just show the life counter.
            if (gNumActivePlayers == 3) {
                curRacerObj = NULL;
                for(tempVar2 = 0; tempVar2 < objectCount; tempVar2++) {
                    if (objectGroup[tempVar2]->unk64->racer.playerIndex == PLAYER_COMPUTER) { 
                        curRacerObj = &objectGroup[tempVar2]->unk64->racer;
                    }
                }
                if (curRacerObj != NULL) {
                    D_80126CDC = D_80126CEC;
                    spE4 = D_80126CDC->unk64C;
                    spE0 = D_80126CDC->unk650;
                    func_8007BF1C(FALSE);
                    set_ortho_matrix_view(&gHUDCurrDisplayList, &gHUDCurrMatrix);
                    func_80068508(TRUE);
                    D_80126CDC->unk64C = 225.0f;
                    if (osTvType == TV_TYPE_PAL) {
                        D_80126CDC->unk650 = 181.5f;
                    } else {
                        D_80126CDC->unk650 = 165.0f;
                    }
                    if (osTvType == TV_TYPE_PAL) {
                        var_a0_5 = (66.0f - D_80126CDC->unk36C) - 4.0f;
                        temp = -114.0f - D_80126CDC->unk370;
                    } else {
                        var_a0_5 = 66.0f - D_80126CDC->unk36C;
                        temp = -100.0f - D_80126CDC->unk370;
                    }
                    D_80126CDC->unk36C += var_a0_5;
                    D_80126CDC->unk370 += temp; 
                    D_80126CDC->unkEC += var_a0_5;
                    D_80126CDC->unkF0 += temp;
                    D_80126CDC->unk38C += var_a0_5;
                    D_80126CDC->unk390 += temp;
                    D_80126CDC->unk10C += var_a0_5;
                    D_80126CDC->unk110 -= temp + 1;
                    D_80126CDC->unk12C += var_a0_5;
                    D_80126CDC->unk130 -= temp + 1;
                    D_80126CDC->unk24C += var_a0_5;
                    D_80126CDC->unk250 -= temp;
                    D_80126CDC->unk646 = curRacerObj->characterId + 56;
                    if (osTvType == TV_TYPE_PAL) {
                        D_80126CDC->unk64C -= 4.0f;
                        D_80126CDC->unk66C -= 4.0f;
                    }
                    D_80126CD5 = TRUE;
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk640);
                    D_80126CD5 = FALSE;
                    if (D_80126CDC->unkFB == 0 && curRacerObj->bananas == 10) {
                        D_80126CDC->unkFB = curRacerObj->bananas;
                    }
                    render_racer_bananas(curRacerObj, updateRate);
                    D_80126CDC->unk36C -= var_a0_5;
                    D_80126CDC->unk370 -= temp;
                    D_80126CDC->unkEC -= var_a0_5;
                    D_80126CDC->unkF0 -= temp;
                    D_80126CDC->unk38C -= var_a0_5;
                    D_80126CDC->unk390 -= temp;
                    D_80126CDC->unk10C -= var_a0_5;
                    D_80126CDC->unk110 += temp + 1;
                    D_80126CDC->unk12C -= var_a0_5;
                    D_80126CDC->unk130 += temp + 1;
                    D_80126CDC->unk24C -= var_a0_5;
                    D_80126CDC->unk250 += temp;
                    D_80126CDC->unk64C = spE4;
                    D_80126CDC->unk650 = spE0;
                    func_8007BF1C(TRUE);
                    reset_render_settings(&gHUDCurrDisplayList);
                    func_80068508(FALSE);
                }
            }
        }
    } else if (gHudLevelHeader->race_type == RACETYPE_CHALLENGE_BANANAS) {
        if (gNumActivePlayers == 2 && gHudToggleSettings[gHUDNumPlayers] == 0) {
            temp_s0_2 = D_80126CDC->unk64C;
            temp_s1_2 = D_80126CDC->unk650;
            temp_s3 = D_80126CDC->unk40C;
            spBC = D_80126CDC->unk410;
            racerGroup = get_racer_objects(&racerCount);
            for (sp144 = 0; sp144 < racerCount; sp144++) {
                someRacer = (Object_Racer *) racerGroup[sp144]->unk64;
                render_treasure_hud(someRacer);
                if (osTvType == TV_TYPE_PAL) {
                    D_80126CDC->unk650 += 66.0;
                    D_80126CDC->unk410 += 66.0;
                } else {
                    D_80126CDC->unk650 += 55.0f;
                    D_80126CDC->unk410 += 55.0f;
                }
            }
            D_80126CDC->unk64C = temp_s0_2;
            D_80126CDC->unk650 = temp_s1_2;
            D_80126CDC->unk40C = temp_s3;
            D_80126CDC->unk410 = spBC;
        } else if (gNumActivePlayers == 3) {
            tempVar4 = NULL;
            for(tempVar2 = 0; tempVar2 < objectCount; tempVar2++) {
                if (objectGroup[tempVar2]->unk64->racer.playerIndex == PLAYER_COMPUTER) {
                    tempVar4 = &objectGroup[tempVar2]->unk64->racer;
                }
            }
            if (tempVar4 != NULL) {
                temp_s0_3 = D_80126CDC->unk64C;
                temp_s1_3 = D_80126CDC->unk650;
                temp_f16 = D_80126CDC->unk40C;
                temp_f6 = D_80126CDC->unk410;
                D_80126CDC->unk64C = 225.0f;
                D_80126CDC->unk650 = 165.0f;
                D_80126CDC->unk40C = 209.0f;
                D_80126CDC->unk410 = 193.0f;
                if (osTvType == TV_TYPE_PAL) {
                    D_80126CDC->unk64C -= 4.0f;
                    D_80126CDC->unk40C -= 4.0f;
                    D_80126CDC->unk650 *= 1.1;
                    D_80126CDC->unk410 *= 1.1;
                    D_80126CDC->unk650 = (s32) D_80126CDC->unk650;
                    D_80126CDC->unk410 = (s32) D_80126CDC->unk410;
                }
                render_treasure_hud(tempVar4);
                D_80126CDC->unk64C = temp_s0_3;
                D_80126CDC->unk650 = temp_s1_3;
                D_80126CDC->unk40C = temp_f16;
                D_80126CDC->unk410 = temp_f6;
            }
        }
    }
    if (D_80127180 != 0) {
        gHudSprites[D_80127180].texture = NULL;
        render_textured_rectangle(&gHUDCurrDisplayList, gHudSprites, 0, 0, 255, 255, 255, 255);
    }
    *dList = gHUDCurrDisplayList;
    *mtx = gHUDCurrMatrix;
    *vtx = gHUDCurrVertex;
    if (!(gHudLevelHeader->unkBC & 1)) {
        sp113 = TRUE;
        for(i = 0; i < objectCount; i++) {
            someRacer = (Object_Racer *) objectGroup[i]->unk64;
            if (someRacer != NULL && 
                someRacer->playerIndex != PLAYER_COMPUTER && 
                someRacer->raceFinished == FALSE) {
                sp113 = FALSE;
            }
        }
        if((gHUDNumPlayers == THREE_PLAYERS && is_postrace_viewport_active()) || check_if_showing_cutscene_camera() || sp113) {
            goto test;
        } else if(gHudToggleSettings[gHUDNumPlayers] != 1) {
        test:
            return;
        } else {
            reset_render_settings(&gHUDCurrDisplayList);
            set_ortho_matrix_view(&gHUDCurrDisplayList, &gHUDCurrMatrix);
            lvlMdl = get_current_level_model();
            if (lvlMdl == NULL) {
                return;
            }
            someObjSeg = get_active_camera_segment();
            func_80068508(TRUE);
            minimap = (Sprite *) lvlMdl->minimapSprite;
            switch (gHUDNumPlayers) {
                case TWO_PLAYERS:
                    D_80126D58 = 135;
                    D_80126D5C = -D_80126D20 / 2;
                    break;
                case THREE_PLAYERS:
                    if (get_current_level_race_type() == RACETYPE_CHALLENGE_EGGS || 
                        get_current_level_race_type() == RACETYPE_CHALLENGE_BATTLE || 
                        get_current_level_race_type() == RACETYPE_CHALLENGE_BANANAS) {
                        D_80126D58 = (D_80126D1C / 2) - 8;
                        D_80126D5C =  -D_80126D20 / 2;
                    } else {
                        D_80126D58 = ( D_80126D1C / 2) + 72;
                        D_80126D5C = -60 - (D_80126D20 / 2);
                    }
                    break;
                case FOUR_PLAYERS:
                    D_80126D58 = (D_80126D1C / 2) - 8;
                    D_80126D5C = -D_80126D20 / 2;
                    break;
                default:
                    D_80126D58 = 135;
                    D_80126D5C = -98;
                    break;
            }
            if (osTvType == TV_TYPE_PAL) {
                D_80126D5C *= 1.2;
            }
            func_8007BF1C(FALSE);
            objTrans.trans.x_position = D_80126D58 + D_80126D24 + D_80126D28;
            objTrans.trans.y_position = D_80126D5C;
            if (osTvType == TV_TYPE_PAL) {
                objTrans.trans.x_position -= 4.0f;
            }
            objTrans.trans.z_rotation = -someObjSeg->trans.z_rotation;
            objTrans.trans.x_rotation = 0;
            if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
                objTrans.trans.y_rotation = -0x8000;
                objTrans.trans.x_position -= D_80126D1C;
            } else {
                objTrans.trans.y_rotation = 0;
            }
            objTrans.unk18 = 0;
            objTrans.trans.z_position = 0.0f;
            objTrans.trans.scale = 1.0f;
            opacity = mapOpacity;
            if (mapOpacity > 160) {
                mapOpacity = 160;
            }
            if (gNumActivePlayers == 3) {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, mapOpacity);
            } else {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, gMinimapRed, gMinimapGreen, gMinimapBlue, mapOpacity);
            }
            render_ortho_triangle_image(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (ObjectSegment* ) &objTrans.trans, minimap, 0);
            sp11C = (lvlMdl->upperXBounds - lvlMdl->lowerXBounds) / (f32) (lvlMdl->upperZBounds - lvlMdl->lowerZBounds);
            sp118 = coss_f((lvlMdl->unk24 * 0xFFFF) / 360);
            sp114 = sins_f((lvlMdl->unk24 * 0xFFFF) / 360);
            if (func_8000E4D8() && func_8001B288()) {
                temp_v0_8 = func_8001B2E0();
                if (temp_v0_8 != NULL) {
                    func_800AA3EC(temp_v0_8->segment.trans.x_position, temp_v0_8->segment.trans.z_position, sp114, sp118, sp11C);
                    D_80126CDC->unk1E6 = 14;
                    D_80126CDC->unk1E4 = 0;
                    D_80126CDC->unk1E8 = 1.0f;
                    tempVar1 = (opacity * (f32) temp_v0_8->segment.unk38.byte.unk39) * 0.0078125;
                    gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 60, 60, 60, tempVar1);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk1E0);
                }
            }
            temp_v0_8 = func_8001B640();
            if (temp_v0_8 != NULL) {
                func_800AA3EC(temp_v0_8->segment.trans.x_position, temp_v0_8->segment.trans.z_position, sp114, sp118, sp11C);
                D_80126CDC->unk1E4 = 0;
                tempVar1 = (opacity * (f32) temp_v0_8->segment.unk38.byte.unk39) * 0.0078125;
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, gHudMinimapColours[8].red, gHudMinimapColours[8].green, gHudMinimapColours[8].blue, tempVar1);
                D_80126CDC->unk1E8 = 1.0f;
                D_80126CDC->unk1E6 = 14;
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk1E0);
            }
            // Draw Taj's minimap icon.
            if (gHudLevelHeader->race_type == RACETYPE_HUBWORLD) {
                temp_v0_8 = find_taj_object();
                if (temp_v0_8 != NULL) {
                    D_80126CDC->unk1E6 = 14;
                    func_800AA3EC(temp_v0_8->segment.trans.x_position, temp_v0_8->segment.trans.z_position, sp114, sp118, sp11C);
                    D_80126CDC->unk1E4 = 0;
                    gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 0, 255, opacity);
                    D_80126CDC->unk1E8 = 1.0f;
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk1E0);
                }
            }
            // Draw racer minimap icons.
            // Non AI players get an arrow instead of a blob that rotates.
            for (i = objectCount - 1; i >= 0; i--) {
                temp_v0_8 = objectGroup[i];
                someRacer = (Object_Racer *) objectGroup[i]->unk64;
                if (someRacer != NULL) {
                    func_800AA3EC(objectGroup[i]->segment.trans.x_position, objectGroup[i]->segment.trans.z_position, sp114, sp118, sp11C);
                    if (someRacer->playerIndex != PLAYER_COMPUTER) {
                        D_80126CDC->unk1F0 -= 1.0f;
                        D_80126CDC->unk1E6 = 27;
                        D_80126CDC->unk1E4 = (objectGroup[i]->segment.trans.y_rotation - ((lvlMdl->unk24 * 0xFFFF) / 360)) & 0xFFFF;
                        
                        if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
                            D_80126CDC->unk1E4 = 0xFFFF - D_80126CDC->unk1E4;
                        }
                        func_8007BF1C(TRUE);
                    } else {
                        D_80126CDC->unk1E4 = 0;
                        D_80126CDC->unk1E6 = 14;
                    }
                    if (is_taj_challenge() && someRacer->vehicleID == VEHICLE_CARPET) {
                        gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 0, 255, opacity);
                    } else {
                        gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, gHudMinimapColours[someRacer->characterId].red, gHudMinimapColours[someRacer->characterId].green, gHudMinimapColours[someRacer->characterId].blue, opacity);
                    }
                    if (!(get_current_level_race_type() & RACETYPE_CHALLENGE) || (!someRacer->raceFinished)) {
                        if (osTvType == TV_TYPE_PAL) {
                            D_80126CDC->unk1EC -= 4.0f;
                        }
                        if (get_current_level_race_type() == RACETYPE_CHALLENGE_BATTLE) {
                            switch (someRacer->unk212) {
                                case 0:
                                    D_80126CDC->unk1E8 = 0.8f;
                                    break;
                                case 1:
                                    D_80126CDC->unk1E8 = 1.0f;
                                    break;
                                case 2:
                                case 3:
                                    D_80126CDC->unk1E8 = 1.2f;
                                    break;
                            }
                        } else {
                            D_80126CDC->unk1E8 = 1.0f;
                        }
                        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &D_80126CDC->unk1E0);
                    }
                    func_8007BF1C(FALSE);
                }
            }
            gDPPipeSync(gHUDCurrDisplayList++);
            func_80068508(FALSE);
            func_8007BF1C(TRUE);
            *dList = gHUDCurrDisplayList;
            *mtx = gHUDCurrMatrix;
            *vtx = gHUDCurrVertex;
        }
    }
}


GLOBAL_ASM("asm/non_matchings/game_ui/func_800AA3EC.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800AA600.s")

void func_800AAFD0(ObjectModel *objModel) {
    UNUSED s32 pad;
    TextureHeader *texPtr;
    s32 triOffset;
    s32 vertOffset;
    s32 numBatches;
    s32 numVerts;
    s32 numTris;
    Vertex *verts;
    Triangle *tris;
    s32 textureEnabled;
    s32 i;
    s32 texIndex;
    s32 flags;

    numBatches = objModel->numberOfBatches;
    
    for (i = 0; i < numBatches; i++) {
        flags = objModel->batches[i].flags;
        if (!(flags & RENDER_Z_UPDATE)) {
            vertOffset = objModel->batches[i].verticesOffset;
            triOffset = objModel->batches[i].facesOffset;
            numVerts = objModel->batches[i + 1].verticesOffset - vertOffset;
            numTris = objModel->batches[i + 1].facesOffset - triOffset;
            verts = &objModel->vertices[vertOffset];
            tris = &objModel->triangles[triOffset];
            texIndex = objModel->batches[i].textureIndex; // 0xFF = No Texture 
            textureEnabled = TRIN_ENABLE_TEXTURE;
            if (texIndex == 0xFF) {
                texPtr = NULL;
            } else {
                texPtr = objModel->textures[texIndex].texture;
            }
            load_and_set_texture_no_offset(&gHUDCurrDisplayList, texPtr, flags & ~RENDER_Z_COMPARE);
            gSPVertexDKR(gHUDCurrDisplayList++, OS_PHYSICAL_TO_K0(verts), numVerts, 0);
            if (texPtr == NULL) {
                textureEnabled = TRIN_DISABLE_TEXTURE;
            }
            gSPPolygon(gHUDCurrDisplayList++, OS_PHYSICAL_TO_K0(tris), numTris, textureEnabled);
            numBatches = objModel->numberOfBatches;
        }
    } 
}

void func_800AB194(s32 arg0) {
    D_80126CD1 = 1;
    D_80126CD3 = arg0;
}

void func_800AB1AC(s32 arg0) {
    D_80126CD0 = D_8012718B;
    D_80126CD3 = arg0;
}

/**
 * Sets the race start HUD procedure to the first step.
*/
UNUSED void reset_race_start_hud(void) {
    gRaceStartShowHudStep = 0;
}

/**
 * Sets the visibility of the hud, hiding almost everything, leaving only the minimap.
*/
void set_hud_visibility(u8 setting) {
    gShowHUD = 1 - setting;
}
