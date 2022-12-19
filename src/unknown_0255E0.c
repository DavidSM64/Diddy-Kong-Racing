/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800249E0 */

#include "unknown_0255E0.h"

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "f3ddkr.h"
#include "PR/gu.h"
#include "textures_sprites.h"
#include "objects.h"
#include "game.h"
#include "memory.h"
#include "racer.h"
#include "camera.h"
#include "waves.h"
#include "game_ui.h"
#include "weather.h"
#include "particles.h"
#include "lib/src/libc/rmonPrintf.h"
#include "objects.h"
#include "math_util.h"

// Maximum size for a level model is 522.5 KiB
#define LEVEL_MODEL_MAX_SIZE 0x82A00

/************ .data ************/

s32 D_800DC870 = 0; // Currently unknown, might be a different type.
unknown800DC874 D_800DC874 = { { -128 }, 40, -1 };
unknown800DC874 D_800DC87C = { { -125 }, 70, -1 };

f32 D_800DC884[10] = {
    0.0f, 0.125f, 0.25f, 0.375f, 0.5f, 0.625f, 0.75f, 0.875f
};

f32 D_800DC8AC[27] = {
    50.0f, 0.0f, 32.0f, -50.0f,
    0.0f, 32.0f, -50.0f, 100.0f,
    32.0f, 0.0f, 0.0f, 32.0f,
    130.0f, 60.0f, -68.0f, 130.0f,
    -60.0f, -68.0f, 0.0f, 0.0f,
    32.0f, -130.0f, -60.0f, -68.0f,
    -130.0f, 60.0f, -68.0f,
};

LevelModel *gCurrentLevelModel = NULL;
LevelHeader *gCurrentLevelHeader2 = NULL;

s32 D_800DC920 = -1;
s32 *D_800DC924 = NULL;
s32 D_800DC928 = 0; // Currently unknown, might be a different type.

s8 D_800DC92C[24] = {
    0, 1, 4, 1, 2, 4, 2, 3, 4, 3, 0, 4, 5, 6, 1, 1, 0, 5, 3, 2, 7, 7, 8, 3
    // There may or may not be extra zeroes here.
};

/*******************************/

/************ .rodata ************/

const char D_800E5DF0[] = "TT CAM";
const char D_800E5DF8[] = "Solid Clipping x0=x1 Error!!!\n";
const char D_800E5E10[] = "TrackGetHeight() - Overflow!!!\n";

/*********************************/

/************ .bss ************/

Gfx *gSceneCurrDisplayList;
MatrixS *gSceneCurrMatrix;
Vertex *gSceneCurrVertexList;
TriangleList *gSceneCurrTriList;

ObjectSegment *D_8011B0B0; // Camera Object?

s32 D_8011B0B4;
Object *D_8011B0B8;
UNUSED s32 gIsNearCurrBBox; // Set to true if the current visible segment is close to the camera. Never actually used though.
s32 D_8011B0C0;
s32 D_8011B0C4;
s32 D_8011B0C8;
s32 D_8011B0CC;
s32 D_8011B0D0;
s32 D_8011B0D4;
s32 D_8011B0D8;
s32 D_8011B0DC;
s8 D_8011B0E0;
u8 D_8011B0E1;
u8 D_8011B0E2;
u8 D_8011B0E3;
f32 D_8011B0E4;
f32 D_8011B0E8;
f32 D_8011B0EC;
s32 D_8011B0F0;
s32 D_8011B0F4;
s32 D_8011B0F8;
s32 D_8011B0FC;
s32 D_8011B100;
s32 D_8011B104;
s32 D_8011B108;
s32 D_8011B10C;
s32 D_8011B110;
u32 D_8011B114;
s32 D_8011B118;
s32 D_8011B11C;
s32 D_8011B120[128];
s32 D_8011B320[4];
s32 D_8011B330[960];
s32 D_8011C230[2];
s32 D_8011C238[96];
s32 D_8011C3B8[320];
s32 D_8011C8B8[512];
s32 D_8011D0B8;
s32 D_8011D0BC;
s32 D_8011D0C0;
s32 D_8011D0C4;
s32 D_8011D0C8;
s16 D_8011D0CC;
s16 D_8011D0CE;
s32 D_8011D0D0;
f32 D_8011D0D4;
s32 D_8011D0D8;
s32 D_8011D0DC;
s32 D_8011D0E0;
s32 D_8011D0E4;
s32 D_8011D0E8;
s32 D_8011D0EC;
s32 D_8011D0F0;
s32 D_8011D0F4;
unk8011D0F8 D_8011D0F8[3];
unk8011D0F8 D_8011D128[3];
s32 D_8011D158[3]; // Unused? Or part of something bigger above?
s32 D_8011D164;
s32 D_8011D168[84];
s32 D_8011D2B8[20];
s32 D_8011D308;
LevelModel *D_8011D30C;
s32 *D_8011D310;
f32 D_8011D314;
f32 D_8011D318;
f32 D_8011D31C;
s32 *D_8011D320[4];
unk8011D330 *D_8011D330;
s32 D_8011D334;
s32 *D_8011D338[4];
unk8011D348 *D_8011D348;
s32 D_8011D34C;
s32 *D_8011D350[4];
unk8011D360 *D_8011D360;
s32 D_8011D364;
s32 D_8011D368;
s32 D_8011D36C;
s32 *D_8011D370;
s32 *D_8011D374;
s32 D_8011D378;
s32 D_8011D37C;
UNUSED f32 gCurrBBoxDistanceToCamera; // Used in a comparison check, but functionally unused.
u32 D_8011D384;
unk8011D388 D_8011D388[4];
unk8011D468 D_8011D468;
s32 *D_8011D474;
s32 D_8011D478;
s32 D_8011D47C;
s32 D_8011D480[2];
Vertex **D_8011D488;
s32 D_8011D48C;
s32 D_8011D490[2];
Vertex **D_8011D498;
s16 D_8011D49C;
s16 D_8011D49E;
f32 D_8011D4A0;
f32 D_8011D4A4;
f32 D_8011D4A8;
f32 D_8011D4AC;
f32 D_8011D4B0;
s8 D_8011D4B4;
s16 D_8011D4B6;
s16 D_8011D4B8;
s16 D_8011D4BA;
s32 D_8011D4BC;

/******************************/

s32 func_800249E0(s32 arg0) {
    D_8011D37C = arg0;
    return 0;
}

#ifdef NON_EQUIVALENT
void func_8002C0C4(s32 modelId);
void func_800249F0(u32 arg0, u32 arg1, s32 arg2, Vehicle vehicle, u32 arg4, u32 arg5, u32 arg6) {
    s32 i;
    s32 tmp_a2;

    gCurrentLevelHeader2 = get_current_level_header();
    D_8011B0F8 = 0;
    D_8011B100 = 0;
    D_8011B104 = 0;
    D_8011B108 = 0;
    D_8011B10C = 0;
    if (gCurrentLevelHeader2->race_type == RACETYPE_CUTSCENE_1 || gCurrentLevelHeader2->race_type == RACETYPE_CUTSCENE_2) {
        D_8011B0F8 = 1;
    }
    func_8002C0C4(arg0);

    if (arg2 < 2) {
        D_8011D384 = 0;
        for (i = 0; i < gCurrentLevelModel->numberOfSegments; i++) {
            if (gCurrentLevelModel->segments[i].unk2B != 0) {
                D_8011D384++;
                gCurrentLevelModel->segments[i].unk2B = 1;
            }
        }
    }
    if (is_in_two_player_adventure() && (gCurrentLevelHeader2->race_type == RACETYPE_DEFAULT || gCurrentLevelHeader2->race_type & RACETYPE_CHALLENGE)) {
        tmp_a2 = 2;
    } else {
        tmp_a2 = arg2;
        tmp_a2++;
    }
    if (D_8011D384) {
        func_800B82B4(gCurrentLevelModel, gCurrentLevelHeader2, tmp_a2);
    }
    set_active_viewports_and_object_stack_cap(arg2);
    func_80027FC4(arg1);
    D_8011B110 = 0;
    D_8011B114 = 0x10000;
    func_80011390();
    func_8000C8F8(arg6, 0);
    func_8000C8F8(arg5, 1);
    D_8011D37C = arg2;
    func_8000CC7C(vehicle, arg4, arg2);
    func_8000B020(72, 64);
    if (arg0 == 0 && arg4 == 0) {
        func_800C01D8(&D_800DC87C);
    } else {
        func_800C01D8(&D_800DC874);
    }
    set_active_viewports_and_object_stack_cap(D_8011D37C);
    D_8011B0FC = 0;
    i = 0;
    do {
        D_8011D350[i] = allocate_from_main_pool_safe(3200, COLOUR_TAG_YELLOW);
        D_8011D320[i] = allocate_from_main_pool_safe(12800, COLOUR_TAG_YELLOW);
        D_8011D338[i] = allocate_from_main_pool_safe(20000, COLOUR_TAG_YELLOW);
    } while ((s32)&D_8011D338[++i] != (s32)&D_8011D348);

    D_8011B0C8 = 0;
    func_8002D8DC(1, 1, 0);
    func_8002D8DC(2, 2, 0);
    D_8011B0C8 = 1;
    func_8002D8DC(1, 1, 0);
    func_8002D8DC(2, 2, 0);
    D_8011B0C8 = 0;
    if (gCurrentLevelHeader2->unkB7) {
        D_8011B0E1 = gCurrentLevelHeader2->unkB4;
        D_8011B0E2 = gCurrentLevelHeader2->unkB5;
        D_8011B0E3 = gCurrentLevelHeader2->unkB6;
        func_80025510(arg2 + 1);
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800249F0.s")
#endif

// Regalloc
#ifdef NON_MATCHING
extern u32 D_A0000200;
/**
 * The root function for rendering the entire scene
*/
void render_scene(Gfx** dList, MatrixS** mtx, Vertex** vtx, s8** tris, s32 updateRate) {
    s32 i;
    s32 numViewports;
    s32 delta;
    s8 flip;
    s32 posX;
    s32 posY;
    UNUSED s32 pad;

    gSceneCurrDisplayList = *dList;
    gSceneCurrMatrix = *mtx;
    gSceneCurrVertexList = *vtx;
    gSceneCurrTriList = *tris;
    D_8011B0DC = 1;
    D_8011B0C4 = 0;
    D_8011B0C0 = 0;
    gIsNearCurrBBox = 0;
    numViewports = set_active_viewports_and_object_stack_cap(D_8011D37C);
    if (is_game_paused()) {
        delta = 0;
    } else {
        delta = updateRate;
    }
    if (D_8011D384) {
        func_800B9C18(delta);
    }
    func_8002D8DC(2, 2, updateRate);
    for (i = 0; i < 7; i++) {
        if ((s32) gCurrentLevelHeader2->unk74[i] != -1) {
            func_8007F24C(gCurrentLevelHeader2->unk74[i], delta);
        }
    }
    if (gCurrentLevelHeader2->pulseLightData != (PulsatingLightData* ) -1) {
        update_pulsating_light_data(gCurrentLevelHeader2->pulseLightData, delta);
    }
    D_8011B0E0 = 1;
    if (gCurrentLevelHeader2->race_type == 7) {
        D_8011B0E0 = 0;
        D_8011B0FC = 1;
    }
    if (gCurrentLevelHeader2->race_type == 6 || gCurrentLevelHeader2->unkBD) {
        D_8011B0FC = 1;
    }
    if (gCurrentLevelHeader2->unk49 == -1) {
        gCurrentLevelHeader2->unkA8 = (gCurrentLevelHeader2->unkA8 + (gCurrentLevelHeader2->unkA2 * delta)) & ((gCurrentLevelHeader2->unkA4->width << 9) - 1);
        gCurrentLevelHeader2->unkAA = (gCurrentLevelHeader2->unkAA + (gCurrentLevelHeader2->unkA3 * delta)) & ((gCurrentLevelHeader2->unkA4->height << 9) - 1);
        func_8007EF80(gCurrentLevelHeader2->unkA4, &D_8011B114, &D_8011B110, delta);
    }
    flip = FALSE;
    if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
        flip = TRUE;
    }
    if (D_A0000200 != 0xAC290000) {
        flip = TRUE;
    }
    reset_render_settings(&gSceneCurrDisplayList);
    gDkrDisableBillboard(gSceneCurrDisplayList++);
    gSPClearGeometryMode(gSceneCurrDisplayList++, CVG_X_ALPHA);
    gDPSetBlendColor(gSceneCurrDisplayList++, 0, 0, 0, 0x64);
    gDPSetPrimColor(gSceneCurrDisplayList++, 0, 0, 255, 255, 255, 255);
    gDPSetEnvColor(gSceneCurrDisplayList++, 255, 255, 255, 0);
    func_800AD40C();
    func_80030838(numViewports, delta);
    func_800AF404(delta);
    if (gCurrentLevelModel->unk1E > 0) {
        func_80027E24(delta);
    }
    for (i = D_8011B0B4 = 0; i < numViewports;  D_8011B0B4++, i = D_8011B0B4) {
        if (i == 0) {
            if ((func_8000E184()) && (numViewports == 1)) {
                D_8011B0B4 = 1;
            }
        }
        if (flip) {
            gSPSetGeometryMode(gSceneCurrDisplayList++, CVG_X_ALPHA);
        }
        func_8003093C(D_8011B0B4);
        gDPPipeSync(gSceneCurrDisplayList++);
        set_object_stack_pos(D_8011B0B4);
        func_80066CDC(&gSceneCurrDisplayList, &gSceneCurrMatrix);
        func_8002A31C();
        if (numViewports < 2) {
            func_80068408(&gSceneCurrDisplayList, &gSceneCurrMatrix);
            if (gCurrentLevelHeader2->unk49 == -1) {
                func_80028050();
            } else {
                render_skydome();
            }
        } else {
            func_8006807C(&gSceneCurrDisplayList, &gSceneCurrMatrix);
            draw_gradient_background();
            func_80067D3C(&gSceneCurrDisplayList, &gSceneCurrMatrix);
            func_80068408(&gSceneCurrDisplayList, &gSceneCurrMatrix);
        }
        gDPPipeSync(gSceneCurrDisplayList++);
        func_80028CD0(updateRate);
        func_800AB308(-1, -512);
        if (gCurrentLevelHeader2->weatherEnable > 0 && numViewports < 2) {
            process_weather(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, &gSceneCurrTriList, delta);
        }
        func_800AD030(get_active_camera_segment());
        func_800ACA20(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, get_active_camera_segment());
        render_hud(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, get_racer_object_by_port(D_8011B0B4), updateRate);
    }
    if ((numViewports == 3) && 
        (get_current_level_race_type() != RACETYPE_CHALLENGE_EGGS) &&
        (get_current_level_race_type() != RACETYPE_CHALLENGE_BATTLE) &&
        (get_current_level_race_type() != RACETYPE_CHALLENGE_BANANAS)) {
        if (get_multiplayer_hud_setting() == 0) {
            if (flip) {
                gSPSetGeometryMode(gSceneCurrDisplayList++, CVG_X_ALPHA);
            }
            func_8003093C(3);
            gDPPipeSync(gSceneCurrDisplayList++);
            set_object_stack_pos(3);
            disable_cutscene_camera();
            func_800278E8(updateRate);
            func_80066CDC(&gSceneCurrDisplayList, &gSceneCurrMatrix);
            func_8002A31C();
            func_8006807C(&gSceneCurrDisplayList, &gSceneCurrMatrix);
            draw_gradient_background();
            func_80067D3C(&gSceneCurrDisplayList, &gSceneCurrMatrix);
            func_80068408(&gSceneCurrDisplayList, &gSceneCurrMatrix);
            
            gDPPipeSync(gSceneCurrDisplayList++);
            func_80028CD0(updateRate);
            func_800AB308(-1, -512);
            func_800AD030(get_active_camera_segment());
            func_800ACA20(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, get_active_camera_segment());
            set_text_font(0);
            if (osTvType == 0) {
                posX = 166;
                posY = 138;
            } else {
                posX = 170;
                posY = 125;
            }
            draw_text(&gSceneCurrDisplayList, posX, posY, (char *) &D_800E5DF0, ALIGN_TOP_LEFT);
        } else {
            set_object_stack_pos(3);
            func_800278E8(updateRate);
        }
    }
    func_800682AC(&gSceneCurrDisplayList);
    gDPPipeSync(gSceneCurrDisplayList++);
    gDkrDisableBillboard(gSceneCurrDisplayList++);
    D_8011B0C8 = 1 - D_8011B0C8;
    *dList = gSceneCurrDisplayList;
    *mtx = gSceneCurrMatrix;
    *vtx = gSceneCurrVertexList;
    *tris = gSceneCurrTriList;
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/render_scene.s")
#endif

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80025510.s")

void func_800257D0(void) {
    if (D_800DC924 != 0) {
        free_from_memory_pool(D_8011D474);
        free_from_memory_pool(D_800DC924);
        D_800DC924 = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002581C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80026070.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80026430.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80026C14.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80026E54.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80027184.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80027568.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800278E8.s")

void func_80027E24(s32 arg0) {
    s32 segmentNumber, batchNumber;
    LevelModelSegment *segment;
    TextureHeader *texture;
    TriangleBatchInfo *batch;
    s32 temp;

    segment = gCurrentLevelModel->segments;
    for (segmentNumber = 0; segmentNumber < gCurrentLevelModel->numberOfSegments; segmentNumber++) {
        batch = segment[segmentNumber].batches;
        for (batchNumber = 0; batchNumber < segment[segmentNumber].numberOfBatches; batchNumber++) {
            if (batch[batchNumber].flags & 0x10000) {
                if (batch[batchNumber].textureIndex != 0xFF) {
                    texture = gCurrentLevelModel->textures[batch[batchNumber].textureIndex].texture;
                    if ((texture->numOfTextures != 0x100) && (texture->frameAdvanceDelay != 0)) {
                        temp = batch[batchNumber].unk7 << 6;
                        if (batch[batchNumber].flags & 0x80000000) {
                            temp |= batch[batchNumber].unk6;
                            func_8007EF80(texture, &batch[batchNumber].flags, &temp, arg0);
                            batch[batchNumber].unk6 = temp & 0x3F;
                        } else {
                            func_8007EF80(texture, &batch[batchNumber].flags, &temp, arg0);
                        }
                        batch[batchNumber].unk7 = (temp >> 6) & 0xFF;
                    }
                }
            }
        }
    }
}

void func_80027FC4(s32 arg0) {
    LevelObjectEntryCommon sp20;

    func_8005A3D0();
    if (arg0 == -1) {
        D_8011B0B8 = NULL;
        return;
    }
    sp20.x = 0;
    sp20.y = 0;
    sp20.z = 0;
    sp20.size = 8;
    sp20.objectID = arg0;
    D_8011B0B8 = spawn_object(&sp20, 2);
    if (D_8011B0B8 != 0) {
        D_8011B0B8->segment.unk3C_a.level_entry = NULL;
        D_8011B0B8->unk4A = -1;
    }
}

void func_80028044(s32 arg0) {
    D_8011B0DC = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80028050.s")

/**
 * Instead of drawing the skydome with textures, draw a solid coloured background.
 * Using different colours set in the level header, the vertices are coloured and
 * it gives the background a gradient effect.
*/
void draw_gradient_background(void) {
    s32 set_zero;
    s16 y0;
    s16 y1;
    u8 headerRed0;
    u8 headerGreen0;
    u8 headerBlue0;
    u8 headerRed1;
    u8 headerGreen1;
    u8 headerBlue1;
    Vertex *verts;
    Triangle *tris;
    s32 also_one;
    s64 set_twenty;
        
    verts = (Vertex *) gSceneCurrVertexList;
    tris = (Triangle *) gSceneCurrTriList;
    headerRed0 = gCurrentLevelHeader2->unkC1;
    also_one = 1;
    headerGreen0 = gCurrentLevelHeader2->unkC2;
    headerBlue0 = gCurrentLevelHeader2->unkC3;
    headerRed1 = gCurrentLevelHeader2->unkBE;
    headerGreen1 = gCurrentLevelHeader2->unkBF;
    headerBlue1 = gCurrentLevelHeader2->unkC0;
    reset_render_settings(&gSceneCurrDisplayList);
    load_and_set_texture_no_offset(&gSceneCurrDisplayList, 0, RENDER_FOG_ACTIVE);
    gSPVertexDKR(gSceneCurrDisplayList++, OS_PHYSICAL_TO_K0(verts), 4, 0);
    gSPPolygon(gSceneCurrDisplayList++, OS_PHYSICAL_TO_K0(tris), 2, 0);
    set_twenty = 20;
    if (osTvType == TV_TYPE_PAL) {
        y0 = -180;
        y1 = 180;
    } else {
        y0 = -150;
        y1 = 150;
    }
    if (get_viewport_count() == TWO_PLAYERS) {
        y0 >>= 1;
        y1 >>= 1;
    }
    verts[0].x = -200;
    verts[0].y = y0;
    verts[0].z = set_twenty;
    verts[0].r = headerRed0;
    verts[0].g = headerGreen0;
    verts[0].b = headerBlue0;
    verts[0].a = 255;
    verts[also_one].x = 200;
    verts[1].y = y0;
    verts[1].z = set_twenty;
    verts[1].r = headerRed0;
    verts[1].g = headerGreen0;
    verts[1].b = headerBlue0;
    verts[1].a = 255;
    verts[2].x = -200;
    verts[2].y = y1;
    verts[2].z = set_twenty;
    verts[2].r = headerRed1;
    verts[2].g = headerGreen1;
    verts[2].b = headerBlue1;
    verts[2].a = 255;
    verts[3].x = 200;
    set_zero = 0;
    verts[3].y = y1;
    verts[3].z = set_twenty;
    verts[3].r = headerRed1;
    verts[3].g = headerGreen1;
    verts[3].b = headerBlue1;
    verts[3].a = 255;
    tris[0].flags = 0x40;
    tris[0].vi0 = 2;
    tris[0].vi1 = 1;
    tris[0].vi2 = 0;
    tris[0].uv0.u = 0;
    tris[0].uv0.v = set_zero;
    tris[set_zero].uv1.u = set_zero;
    tris[set_zero].uv1.v = set_zero;
    tris[set_zero].uv2.u = set_zero;
    tris[0].uv2.v = 0;
    tris[1].flags = 0x40;
    tris[1].vi0 = 3;
    tris[1].vi1 = 2;
    tris[1].vi2 = 1;
    tris[1].uv0.u = 0;
    tris[1].uv0.v = 0;
    tris[1].uv1.u = 0;
    tris[1].uv1.v = 0;
    tris[1].uv2.u = 0;
    tris[1].uv2.v = 0;
    verts += 4;
    gSceneCurrVertexList = verts;
    tris += 2;
    gSceneCurrTriList = (TriangleList *) tris;
}

void render_skydome(void) {
    ObjectSegment *v0_some_struct;
    if (D_8011B0B8 == NULL)
        return;

    v0_some_struct = get_active_camera_segment();
    if (gCurrentLevelHeader2->unk49 == 0) {
        D_8011B0B8->segment.trans.x_position = v0_some_struct->trans.x_position;
        D_8011B0B8->segment.trans.y_position = v0_some_struct->trans.y_position;
        D_8011B0B8->segment.trans.z_position = v0_some_struct->trans.z_position;
    }

    func_80068408(&gSceneCurrDisplayList, &gSceneCurrMatrix);
    if (D_8011B0DC) {
        func_80012D5C(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, D_8011B0B8);
    }
}

void func_800B8C04(s32, s32, s32, s32, s32); 

void func_80028CD0(s32 updateRate) {
    s32 i;
    s32 numRacers;
    s32 sp3C;
    Object** racers; // sp38?
    s32 temp_v0;
    Object_Racer *racer;

    D_8011B0B0 = get_active_camera_segment();
    sp3C = get_current_viewport();
    func_80031018();
    set_and_normalize_D_8011AFE8((f32) D_8011D468.x / 65536.0f, (f32) D_8011D468.y / 65536.0f, (f32) D_8011D468.z / 65536.0f);
    temp_v0 = D_8011B0B0->unk34_a.levelSegmentIndex;
    if ((temp_v0 >= 0) && (temp_v0 < gCurrentLevelModel->numberOfSegments)) {
        D_8011B0D4 = (s32) gCurrentLevelModel->segments[temp_v0].unk28;
    } else {
        D_8011B0D4 = -1;
    }
    D_8011D314 = D_8011B0B0->trans.x_position;
    D_8011D318 = D_8011B0B0->trans.y_position;
    D_8011D31C = D_8011B0B0->trans.z_position;
    if (D_8011D384 != 0) {
        func_800B8B8C();
        racers = get_racer_objects(&numRacers);
        if ((D_8011B0B0->unk34_a.unk36 != 7) && (numRacers > 0) && (!check_if_showing_cutscene_camera())) {
            i = -1; 
            do {
                i++;
                racer = &racers[i]->unk64->racer;
            } while((i < (numRacers - 1)) && (sp3C != (racer->playerIndex)));
            func_800B8C04(racers[i]->segment.trans.x_position, racers[i]->segment.trans.y_position, racers[i]->segment.trans.z_position, get_current_viewport(), updateRate);
        } else {
            func_800B8C04((s32) D_8011B0B0->trans.x_position, (s32) D_8011B0B0->trans.y_position, (s32) D_8011B0B0->trans.z_position, get_current_viewport(), updateRate);
        }
    }
    get_current_level_header()->unk3 = 1;
    render_level_geometry_and_objects();
}


void func_80028FA0(s32 arg0) {
    D_8011B0FC = arg0;
}

void render_level_geometry_and_objects(void) {
    s32 sp16C;
    s32 numberOfSegments;
    s32 objFlags;
    s32 sp160;
    s32 i;
    s32 sp158;
    u8 segmentIds[128];
    u8 sp58[128];
    s32 s0;
    Object *obj;

    func_80012C30();

    if (get_settings()->courseId == ASSET_LEVEL_OPENINGSEQUENCE) {
        D_8011B0FC = 1;
    }

    sp160 = func_80014814(&sp16C);

    if (gCurrentLevelModel->numberOfSegments > 1) {
        numberOfSegments = 0;
        traverse_segments_bsp_tree(0, 0, gCurrentLevelModel->numberOfSegments - 1, segmentIds, &numberOfSegments);
    } else {
        numberOfSegments = 1;
        segmentIds[0] = 0;
    }

    for (i = 1; i <= gCurrentLevelModel->numberOfSegments; i++) {
        sp58[i] = FALSE;
    }

    sp58[0] = TRUE;

    if (D_8011B0E0 != 0) {
        for (i = 0; i < numberOfSegments; i++) {
            render_level_segment(segmentIds[i], 0); // Render opaque segments
            sp58[segmentIds[i] + 1] = TRUE;
        }
    }

    if (gCurrentLevelModel->numberOfSegments < 2) {
        sp58[1] = TRUE;
    }

    reset_render_settings(&gSceneCurrDisplayList);
    func_80015348(sp160, sp16C - 1);
    sp158 = 0x200 << (get_current_viewport() & 1);

    for (i = sp160; i < sp16C; i++) {
        obj = get_object(i);
        s0 = 0xFF;
        objFlags = obj->segment.trans.unk6;
        if (objFlags & 0x80) {
            s0 = 0;
        } else if (!(objFlags & 0x8000)) {
            s0 = obj->segment.unk38.half.lower;
        }
        if (objFlags & sp158) {
            s0 = 0;
        }
        if ((obj != NULL) && (s0 == 0xFF) && (check_if_in_draw_range(obj)) && ((sp58[obj->segment.unk2C.half.lower + 1]) || (1000.0 < obj->segment.unk34_a.unk34))) {
            if (obj->segment.trans.unk6 & 0x8000) {
                func_80012D5C(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, obj);
                continue;
            } else if (obj->unk50 != NULL) {
                render_floor_decal(obj, obj->unk50);
            }
            func_80012D5C(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, obj);
            if ((obj->unk58 != NULL) && (obj->segment.header->unk30 & 0x10)) {
                func_8002D670(obj, obj->unk58);
            }
        }
    }

    for (i = sp16C - 1; i >= sp160; i--) {
        obj = get_object(i);
        objFlags = obj->segment.trans.unk6;
        if (objFlags & sp158) {
            s0 = FALSE;
        } else {
            s0 = TRUE;
        }
        if (obj != NULL && s0 && (objFlags & 0x100) && (sp58[obj->segment.unk2C.half.lower + 1]) && (check_if_in_draw_range(obj) != 0)) {
            if (obj->segment.trans.unk6 & 0x8000) {
                func_80012D5C(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, obj);
                continue;
            } else if (obj->unk50 != NULL) {
                render_floor_decal(obj, obj->unk50);
            }
            func_80012D5C(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, obj);
            if ((obj->unk58 != NULL) && (obj->segment.header->unk30 & 0x10)) {
                func_8002D670(obj, obj->unk58);
            }
        }
    }

    if (D_8011B0E0 != 0) {
        for (i = numberOfSegments - 1; i >= 0; i--) {
            render_level_segment(segmentIds[i], 1); // Render transparent segments
        }
    }

    if (D_8011D384 != 0) {
        func_800BA8E4(&gSceneCurrDisplayList, &gSceneCurrMatrix, get_current_viewport());
    }

    reset_render_settings(&gSceneCurrDisplayList);
    load_and_set_texture_no_offset(&gSceneCurrDisplayList, 0, RENDER_FOG_ACTIVE | RENDER_Z_COMPARE);
    func_80012C3C(&gSceneCurrDisplayList);

    for (i = sp16C - 1; i >= sp160; i--) {
        obj = get_object(i);
        s0 = 0xFF;
        objFlags = obj->segment.trans.unk6;
        if (objFlags & 0x80) {
            s0 = 1;
        } else if (!(objFlags & 0x8000)) {
            s0 = obj->segment.unk38.half.lower;
        }
        if (objFlags & sp158) {
            s0 = 0;
        }
        if ((obj->behaviorId == BHV_RACER) && (s0 >= 0xFF)) {
            s0 = 0;
        }
        if (obj != NULL && s0 < 0xFF && sp58[obj->segment.unk2C.half.lower + 1] && check_if_in_draw_range(obj)) {
            if (s0 > 0) {
                if (obj->segment.trans.unk6 & 0x8000) {
                    func_80012D5C(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, obj);
                    goto skip;
                } else if (obj->unk50 != NULL) {
                    render_floor_decal(obj, obj->unk50);
                }
                func_80012D5C(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, obj);
                if ((obj->unk58 != 0) && (obj->segment.header->unk30 & 0x10)) {
                    func_8002D670(obj, obj->unk58);
                }
            }
skip:
            if (obj->behaviorId == BHV_RACER) {
                render_racer_shield(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, obj);
                render_racer_magnet(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, obj);
            }
        }
    }

    if (D_800DC924 && func_80027568()) {
        func_8002581C(segmentIds, numberOfSegments, get_current_viewport());
    }
    D_8011B0FC = 0;
}

#ifdef NON_MATCHING
// nonOpaque: 0 for solid geometry, 1 for transparent geometry.
void render_level_segment(s32 segmentId, s32 nonOpaque) {
    LevelModelSegment *segment;
    s32 i;
    TriangleBatchInfo *batchInfo;
    TextureHeader *texture;
    s32 renderBatch;
    s32 numberVertices;
    s32 numberTriangles;
    s32 vertices;
    s32 triangles;
    s32 color;
    //s32 hasTexture;
    UNUSED s32 unused;
    s32 levelHeaderIndex;
    s32 texOffset;
    s32 sp78;
    s32 startPos;
    s32 endPos;
    s32 batchFlags;
    s32 textureFlags;

    segment = &gCurrentLevelModel->segments[segmentId];
    sp78 = (nonOpaque && D_8011D384) ? func_800B9228(segment) : FALSE;

    if (nonOpaque) {
        startPos = segment->unk40;
        endPos = segment->numberOfBatches;
    } else {
        startPos = 0;
        endPos = segment->unk40; // unk40 = Number of opaque batches.
    }
    
    for (i = startPos; i < endPos; i++) {
        batchInfo = &segment->batches[i];
        textureFlags = 0; // Texture flags
        batchFlags = batchInfo->flags;
        if (!(batchInfo->flags & RENDER_Z_UPDATE)) {
            renderBatch = FALSE;
            if (batchInfo->textureIndex == 0xFF) {
                texture = NULL; // Solid color only
            } else 
                if(1) // Probably fake.
            {
                texture = gCurrentLevelModel->textures[batchInfo->textureIndex].texture;
                textureFlags = texture->flags;
            }

            batchFlags |= 10;
            if (!(batchFlags & RENDER_UNK_0000010) && !(batchFlags & RENDER_DECAL)) { // 0x10 = Depth write
                batchFlags |= D_8011B0FC;
            }
            // temp & 0x04 = Is interlaced texture
            if ((!(textureFlags & 4) && !(batchFlags & RENDER_UNK_0002000)) || (batchFlags & 0x800)) {
                renderBatch = TRUE;
            }
            if (nonOpaque) {
                renderBatch = (renderBatch + 1) & 1; // Why not just do `renderBatch ^= 1;` or `renderBatch = !renderBatch`?
            }
            if (sp78 && (batchFlags & RENDER_UNK_0002000)) {
                renderBatch = FALSE;
            }
            if (renderBatch) {
                // Problem with this section.
                numberVertices = (batchInfo + 1)->verticesOffset - batchInfo->verticesOffset;
                numberTriangles =  batchInfo->facesOffset;
                numberTriangles = (batchInfo + 1)->facesOffset - numberTriangles;
                vertices = (s32) &segment->vertices[batchInfo->verticesOffset];
                triangles = (s32) &segment->triangles[batchInfo->facesOffset];
                
                texOffset = batchInfo->unk7 << 14;
                
                levelHeaderIndex = (batchFlags >> 28) & 7;
                if (levelHeaderIndex != 0) { // This is unused, so this should always be false.
                    // Got to get that match, even if it costs me my dignity. 
                    gDPSetEnvColor(gSceneCurrDisplayList++, 
                        ((LevelHeader_70*)(((u8**)(&((LevelHeader **)(gCurrentLevelHeader2))[levelHeaderIndex]))[0x1C]))->red,
                        ((LevelHeader_70*)(((u8**)(&((LevelHeader **)(gCurrentLevelHeader2))[levelHeaderIndex]))[0x1C]))->green,
                        ((LevelHeader_70*)(((u8**)(&((LevelHeader **)(gCurrentLevelHeader2))[levelHeaderIndex]))[0x1C]))->blue, 
                        ((LevelHeader_70*)(((u8**)(&((LevelHeader **)(gCurrentLevelHeader2))[levelHeaderIndex]))[0x1C]))->alpha
                    );
                } else {
                    gDPSetEnvColor(gSceneCurrDisplayList++, 255, 255, 255, 0);
                }
                if (batchFlags & RENDER_UNK_0040000) { // Only gets used in Spaceport alpha for the pulsating lights in the outside section.
                    color = gCurrentLevelHeader2->pulseLightData->outColorValue & 0xFF;
                    gDPSetPrimColor(gSceneCurrDisplayList++, 0, 0, color, color, color, color);
                    func_8007BA5C(&gSceneCurrDisplayList, texture, batchFlags, texOffset);
                    gSPVertexDKR(gSceneCurrDisplayList++, OS_PHYSICAL_TO_K0(vertices), numberVertices, 0);
                    gSPPolygon(gSceneCurrDisplayList++, OS_PHYSICAL_TO_K0(triangles), numberTriangles, TRIN_ENABLE_TEXTURE);
                    gDPSetPrimColor(gSceneCurrDisplayList++, 0, 0, 255, 255, 255, 255); // Reset the primitive color
                } else {
                    load_and_set_texture(&gSceneCurrDisplayList, texture, batchFlags, texOffset);
                    batchFlags = TRIN_ENABLE_TEXTURE;
                    if(texture == NULL) {
                        batchFlags = TRIN_DISABLE_TEXTURE;
                    }
                    gSPVertexDKR(gSceneCurrDisplayList++, OS_PHYSICAL_TO_K0(vertices), numberVertices, 0);
                    gSPPolygon(gSceneCurrDisplayList++, OS_PHYSICAL_TO_K0(triangles), numberTriangles, batchFlags);
                }
            }
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/render_level_segment.s")
#endif

void traverse_segments_bsp_tree(s32 nodeIndex, s32 segmentIndex, s32 segmentIndex2, u8 *segmentsOrder, s32 *segmentsOrderIndex) {
    BspTreeNode *curNode;
    s32 camValue;

    curNode = &gCurrentLevelModel->segmentsBspTree[nodeIndex];
    if (curNode->splitType == 0) {
        camValue = D_8011B0B0->trans.x_position; // Camera X
    } else if (curNode->splitType == 1) {
        camValue = D_8011B0B0->trans.y_position; // Camera Y
    } else {
        camValue = D_8011B0B0->trans.z_position; // Camera Z
    }

    if (camValue < curNode->splitValue) {
        if (curNode->leftNode != -1) {
            traverse_segments_bsp_tree(curNode->leftNode, segmentIndex, curNode->segmentIndex - 1, segmentsOrder, segmentsOrderIndex);
        } else {
            add_segment_to_order(segmentIndex, segmentsOrderIndex, segmentsOrder);
        }

        if (curNode->rightNode != -1) {
            traverse_segments_bsp_tree(curNode->rightNode, curNode->segmentIndex, segmentIndex2, segmentsOrder, segmentsOrderIndex);
        } else {
            add_segment_to_order(segmentIndex2, segmentsOrderIndex, segmentsOrder);
        }
    } else {
        if (curNode->rightNode != -1) {
            traverse_segments_bsp_tree(curNode->rightNode, curNode->segmentIndex, segmentIndex2, segmentsOrder, segmentsOrderIndex);
        } else {
            add_segment_to_order(segmentIndex2, segmentsOrderIndex, segmentsOrder);
        }

        if (curNode->leftNode != -1) {
            traverse_segments_bsp_tree(curNode->leftNode, segmentIndex, curNode->segmentIndex - 1, segmentsOrder, segmentsOrderIndex);
        } else {
            add_segment_to_order(segmentIndex, segmentsOrderIndex, segmentsOrder);
        }
    }
}

void add_segment_to_order(s32 segmentIndex, s32 *segmentsOrderIndex, u8 *segmentsOrder) {
    u32 temp;
    if (segmentIndex < gCurrentLevelModel->numberOfSegments) {
        if (D_8011B0D4 != -1) {
            temp = gCurrentLevelModel->segmentsBitfields[D_8011B0D4 + (segmentIndex >> 3)];
            temp >>= segmentIndex & 7;
            temp &= 0xFF;
        } else {
            temp = 1;
        }
        if ((temp & 1) && should_segment_be_visible(&gCurrentLevelModel->segmentsBoundingBoxes[segmentIndex])) {
            segmentsOrder[(*segmentsOrderIndex)++] = segmentIndex;
        }
    }
}

/**
 * Checks if the active camera is currently inside this segment.
 * Has a small inner margin where it doesn't consider the camera inside.
 * Goes unused.
*/
UNUSED s32 check_if_inside_segment(Object *obj, s32 segmentIndex) {
    LevelModelSegmentBoundingBox *bb;
    s32 x, y, z;
    if (segmentIndex >= gCurrentLevelModel->numberOfSegments) {
        return FALSE;
    }
    bb = &gCurrentLevelModel->segmentsBoundingBoxes[segmentIndex];
    x = obj->segment.trans.x_position;
    y = obj->segment.trans.y_position;
    z = obj->segment.trans.z_position;
    if ((x < (bb->x2 + 25)) && ((bb->x1 - 25) < x) &&
        (z < (bb->z2 + 25)) && ((bb->z1 - 25) < z) &&
        (y < (bb->y2 + 25)) && ((bb->y1 - 25) < y)) {
        return TRUE;
    }

    return FALSE;
}

/**
 * Iterates through every existing segment to see which one the active camera is inside.
 * Uses mainly a two dimensional axis check here, instead of the function above.
 * Returns the segment currently inside.
*/
s32 get_level_segment_index_from_position(f32 xPos, f32 yPos, f32 zPos) {
    LevelModelSegmentBoundingBox *bb;
    s32 i;
    s32 z = zPos;
    s32 x = xPos;
    s32 y = yPos;
    s32 minVal;
    s32 result;
    s32 heightDiff;

    if (gCurrentLevelModel == NULL) {
        return -1;
    }

    minVal = 1000000;
    result = -1;

    for (i = 0; i < gCurrentLevelModel->numberOfSegments; i++) {
        bb = &gCurrentLevelModel->segmentsBoundingBoxes[i];
        if ((x < bb->x2) && (bb->x1 < x) && (z < bb->z2) && (bb->z1 < z)) {
            heightDiff = (bb->y2 + bb->y1) >> 1; // Couldn't get / 2 to match, but >> 1 does.
            heightDiff = y - heightDiff;
            if (heightDiff < 0) {
                heightDiff = -heightDiff;
            }
            if (heightDiff < minVal) {
                minVal = heightDiff;
                result = i;
            }
        }
    }

    return result;
}

/**
 * Iterates through every existing segment to see which one the active camera is inside.
 * Uses mainly a two dimensional axis check here, instead of the function above.
 * Increments a counter based on if it's got a camera inside.
 * Because there's a tiny margin, multiple segments can be considered populated,
 * meaning that sometimes it will 2 instead of 1.
*/
s32 get_inside_segment_count(s32 x, s32 z, s32 *arg2) {
    s32 i;
    s32 cnt = 0;
    LevelModelSegmentBoundingBox *bb;
    for (i = 0; i < gCurrentLevelModel->numberOfSegments; i++) {
        bb = gCurrentLevelModel->segmentsBoundingBoxes + i;
        if (x < bb->x2 + 4 && bb->x1 - 4 < x
         && z < bb->z2 + 4 && bb->z1 - 4 < z) {
            *arg2 = i;
            cnt++;
            arg2++;
        }
    }
    return cnt;
}

s32 func_8002A134(s32 *arg0, s16 xPos1, s16 yPos1, s16 zPos1, s16 xPos2, s16 yPos2, s16 zPos2) {
    s32 ret;
    s32 i;
    LevelModelSegmentBoundingBox *bb;

    xPos1 -= 4;
    yPos1 -= 4;
    zPos1 -= 4;
    xPos2 += 4;
    yPos2 += 4;
    zPos2 += 4;

    i = 0;
    ret = 0;

    while (i < gCurrentLevelModel->numberOfSegments) {
        bb = &gCurrentLevelModel->segmentsBoundingBoxes[i];
        if ((bb->x2 >= xPos1) && (xPos2 >= bb->x1) &&
            (bb->z2 >= zPos1) && (zPos2 >= bb->z1) &&
            (bb->y2 >= yPos1) && (yPos2 >= bb->y1)) {
            ret++;
            *arg0++ = i;
        }
        i++;
    }

    return ret;
}

LevelModelSegment *func_8002A2C8(s32 arg0) {
    if (arg0 < 0 || gCurrentLevelModel->numberOfSegments < arg0)
        return NULL;

    return &gCurrentLevelModel->segments[arg0];
}

LevelModelSegmentBoundingBox *func_8002A2DC(s32 arg0) {
    if (arg0 < 0 || gCurrentLevelModel->numberOfSegments < arg0)
        return NULL;

    return &gCurrentLevelModel->segmentsBoundingBoxes[arg0];
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002A31C.s")

/**
 * Takes a normalised (0-1) face direction of the active camera, then adds together a magnitude
 * to a total figure to determine whether or not a segment should be visible.
 * There's a large unused portion at the bottom writing to two vars, that are never later read.
*/
s32 should_segment_be_visible(LevelModelSegmentBoundingBox *bb) {
    UNUSED u8 unknown[0x28];
    s64 sp48;
    s32 i, j;
    s32 isVisible;
    f32 dirX, dirY, dirZ, dirW;
    f32 x, y, z;
    
    for (j = 0; j < 3; j++) {
        dirX = D_8011D0F8[j].unk0;
        dirY = D_8011D0F8[j].unk4;
        dirZ = D_8011D0F8[j].unk8;
        dirW = D_8011D0F8[j].unkC;
        
        for (i = 0, isVisible = FALSE; (i < 8) && (!isVisible); i++) {
            if (i & 1) {
                sp48 = bb->x1 * dirX;
            } else {
                sp48 = bb->x2 * dirX;
            }
            if (i & 2) {
                sp48 += bb->y1 * dirY;
            } else {
                sp48 += bb->y2 * dirY;
            }
            if (i & 4) {
                sp48 += bb->z1 * dirZ;
            } else {
                sp48 += bb->z2 * dirZ;
            }
            sp48 += dirW;
            if (sp48 > 0) {
                isVisible = TRUE;
            }
        }
        if (i == 8 && !isVisible) {
            return FALSE;
        }
    }
    // From here until the "return TRUE" goes completely unused, functionally.
    x = (bb->x2 + bb->x1) >> 1;
    y = (bb->y2 + bb->y1) >> 1;
    z = (bb->z2 + bb->z1) >> 1;
    gCurrBBoxDistanceToCamera = get_distance_to_active_camera(x, y, z);
    if (gCurrBBoxDistanceToCamera < 1000.0) {
        gIsNearCurrBBox = TRUE;
    } else {
        gIsNearCurrBBox = FALSE;
    }
    return TRUE;
}

/**
 * Get the draw distance of the object, then compare it to the active camera position.
 * At the edge of its view distance, it will set its alpha based on distance, giving it a fade in or out effect.
 * Objects in range return true, objects out of range return false.
*/
s32 check_if_in_draw_range(Object *obj) {
    f32 w;
    f32 y;
    f32 fadeDist;
    f32 z;
    f32 x;
    s32 viewDistance;
    s32 alpha;
    s32 i;
    Object_64 *obj64;
    f32 accum;
    s32 temp2;
    f32 dist;

    if (!(obj->segment.trans.unk6 & 0x8000)) {
        alpha = 255;
        viewDistance = obj->segment.header->drawDistance;
        if (obj->segment.header->drawDistance) {
            if (D_8011D37C == 3) {
                viewDistance *= 0.5;
            }

            dist = get_distance_to_active_camera(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
            
            if (viewDistance < dist) {
                return FALSE;
            }
            
            fadeDist = viewDistance * 0.8;
            if (fadeDist < dist) {
                temp2 = viewDistance - fadeDist;
                if (temp2 > 0) {
                    fadeDist = dist - fadeDist;
                    alpha = ((f64) (f32) (1.0f - (f64) ((fadeDist) / temp2)) * 255.0f);
                }
                if (alpha == 0) {
                    alpha = 1;
                }
            }
        }
        switch (obj->behaviorId) {
            case BHV_RACER:
                obj64 = obj->unk64;
                obj->segment.unk38.half.lower = ((obj64->racer.transparency + 1) * alpha) >> 8;
                break;
            case BHV_UNK_3A:
                obj64 = obj->unk64;
                obj->segment.unk38.half.lower = obj64->racer.transparency;
                break;
            case BHV_ANIMATED_OBJECT: // Cutscene object?
            case BHV_CAMERA_ANIMATION:
            case BHV_CAR_ANIMATION:
            case BHV_CHARACTER_SELECT:
            case BHV_VEHICLE_ANIMATION: // Title screen actor
            case BHV_HIT_TESTER: // hittester
            case BHV_HIT_TESTER_2: // animated objects?
            case BHV_ANIMATED_OBJECT_2: // space ships
                obj64 = obj->unk64;
                obj->segment.unk38.half.lower = obj64->effect_box.pad0[0x42];
                break;
            case BHV_PARK_WARDEN:
            case BHV_GOLDEN_BALLOON:
            case BHV_PARK_WARDEN_2: // GBParkwarden
                break;
            default:
                obj->segment.unk38.half.lower = alpha;
                break;
        }
        for (i = 0; i < 3; i++) {
            x = D_8011D0F8[i].unk0;
            z = D_8011D0F8[i].unk8;
            w = D_8011D0F8[i].unkC;
            y = D_8011D0F8[i].unk4;
            accum = (x * obj->segment.trans.x_position) + (y * obj->segment.trans.y_position) + (z * obj->segment.trans.z_position) + w + obj->segment.unk34_a.unk34;
            if (accum < 0.0f) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

UNUSED void func_8002AC00(s32 arg0, s32 arg1, s32 arg2) {
    s32 index;
    s32 index2;
    u8 temp;

    if (arg0 < gCurrentLevelModel->numberOfSegments && arg1 < gCurrentLevelModel->numberOfSegments) {
        index = gCurrentLevelModel->segments[arg0].unk28;
        index2 = arg1 >> 3;
        temp = 1 << (arg1 & 7);
        if (arg2 != 0) {
            (&gCurrentLevelModel->segmentsBitfields[index])[index2] |= temp;
        } else {
            (&gCurrentLevelModel->segmentsBitfields[index])[index2] &= ~temp;
        }
    }
}

// These types are probably wrong because the vars are likely still unidentified structs, but the code matches still.
UNUSED void func_8002ACA0(s32 *arg0, s32 *arg1, s32 *arg2) {
    *arg0 = (unsigned) D_8011D378;
    *arg1 = (unsigned) D_8011D370;
    *arg2 = (unsigned) D_8011D374;
}

void func_8002ACC8(s32 arg0) {
    D_8011B0F4 = arg0;
}

s32 func_8002ACD4(f32 *arg0, f32 *arg1, f32 *arg2) {
    *arg0 = D_8011B0E4;
    *arg1 = D_8011B0E8;
    *arg2 = D_8011B0EC;
    return D_8011B0F0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002AD08.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002B0F4.s")

s32 func_8002B9BC(Object *obj, f32 *arg1, f32 *arg2, s32 arg3) {
    LevelModelSegment *seg;

    if (arg2 != NULL) {
        arg2[0] = 0.0f;
        arg2[2] = 0.0f;
        arg2[1] = 1.0f;
    }
    if ((obj->segment.unk2C.half.lower < 0) || (obj->segment.unk2C.half.lower >= gCurrentLevelModel->numberOfSegments)) {
        return FALSE;
    }
    seg = &gCurrentLevelModel->segments[obj->segment.unk2C.half.lower];
    if ((seg->unk2B != 0) && (D_8011D384 != 0) && (arg3 == 1)) {
        *arg1 = func_800BB2F4(obj->segment.unk2C.half.lower, obj->segment.trans.x_position, obj->segment.trans.z_position, arg2);
        return TRUE;
    } else {
        *arg1 = seg->unk38;
        return TRUE;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002BAB0.s")

#ifdef NON_MATCHING
// Loads a level track from the index in the models table.
// Has regalloc issues.
void func_8002C0C4(s32 modelId) {
    s32 i, j, k;
    s32 temp_s4;
    s32 temp;
    LevelModel *mdl;
    
    set_texture_colour_tag(COLOUR_TAG_GREEN);
    D_8011D30C = allocate_from_main_pool_safe(LEVEL_MODEL_MAX_SIZE, COLOUR_TAG_YELLOW);
    gCurrentLevelModel = D_8011D30C;
    D_8011D370 = allocate_from_main_pool_safe(0x7D0, COLOUR_TAG_YELLOW);
    D_8011D374 = allocate_from_main_pool_safe(0x1F4, COLOUR_TAG_YELLOW);
    D_8011D378 = 0;
    D_8011D310 = (s32*)load_asset_section_from_rom(ASSET_LEVEL_MODELS_TABLE);
    
    for(i = 0; D_8011D310[i] != -1; i++);
    i--;
    if (modelId >= i) {
        modelId = 0;
    }
    
    //offset = D_8011D310[modelId];
    temp_s4 = D_8011D310[modelId + 1] - D_8011D310[modelId];

    // temp = compressedRamAddr
    temp = (s32) gCurrentLevelModel;
    temp +=  (LEVEL_MODEL_MAX_SIZE - temp_s4);
    temp -= ((s32)temp % 16); // Align to 16-byte boundary.
    
    load_asset_to_address(ASSET_LEVEL_MODELS, temp, D_8011D310[modelId], temp_s4);
    gzip_inflate((u8*) temp, (u8*) gCurrentLevelModel);
    free_from_memory_pool(D_8011D310); // Done with the level models table, so free it.
    
    mdl = gCurrentLevelModel;
    
    LOCAL_OFFSET_TO_RAM_ADDRESS(TextureInfo *, gCurrentLevelModel->textures);
    LOCAL_OFFSET_TO_RAM_ADDRESS(LevelModelSegment *, gCurrentLevelModel->segments);
    LOCAL_OFFSET_TO_RAM_ADDRESS(LevelModelSegmentBoundingBox *, gCurrentLevelModel->segmentsBoundingBoxes);
    LOCAL_OFFSET_TO_RAM_ADDRESS(s32, gCurrentLevelModel->unkC);
    LOCAL_OFFSET_TO_RAM_ADDRESS(u8 *, gCurrentLevelModel->segmentsBitfields);
    LOCAL_OFFSET_TO_RAM_ADDRESS(BspTreeNode *, gCurrentLevelModel->segmentsBspTree);
    
    if(1){}if(1){}if(1){}if(1){}if(1){}if(1){} // Fakematch
    
    for(k = 0; k < gCurrentLevelModel->numberOfSegments; k++) {
        LOCAL_OFFSET_TO_RAM_ADDRESS(Vertex *, gCurrentLevelModel->segments[k].vertices);
        LOCAL_OFFSET_TO_RAM_ADDRESS(Triangle *, gCurrentLevelModel->segments[k].triangles);
        LOCAL_OFFSET_TO_RAM_ADDRESS(TriangleBatchInfo *, gCurrentLevelModel->segments[k].batches);
        LOCAL_OFFSET_TO_RAM_ADDRESS(u8 *, gCurrentLevelModel->segments[k].unk14);
    }
    for(k = 0; k < gCurrentLevelModel->numberOfTextures; k++) {
        gCurrentLevelModel->textures[k].texture = load_texture(((s32)gCurrentLevelModel->textures[k].texture) | 0x8000);
    }
    j = (s32)gCurrentLevelModel + gCurrentLevelModel->modelSize;
    for(k = 0; k < gCurrentLevelModel->numberOfSegments; k++) {
        gCurrentLevelModel->segments[k].unk10 = (s16 *) j;
        j = (s32) align16(((u8 *) (gCurrentLevelModel->segments[k].numberOfTriangles * 2)) + j);
        gCurrentLevelModel->segments[k].unk18 = (s16 *) j;
        j = (s32) &((u8*)j)[func_8002CC30(&gCurrentLevelModel->segments[k])];
        func_8002C954(&gCurrentLevelModel->segments[k], &gCurrentLevelModel->segmentsBoundingBoxes[k], k);
        gCurrentLevelModel->segments[k].unk30 = 0;
        gCurrentLevelModel->segments[k].unk34 = (s16 *) j;
        func_8002C71C(&gCurrentLevelModel->segments[k]);
        j = (s32) align16(((u8 *) (gCurrentLevelModel->segments[k].unk32 * 2)) + j);
    }
    temp_s4 = j - (s32)gCurrentLevelModel;
    if (temp_s4 > LEVEL_MODEL_MAX_SIZE) {
        rmonPrintf("ERROR!! TrackMem overflow .. %d\n", temp_s4);
    }
    set_free_queue_state(0);
    free_from_memory_pool(D_8011D30C);
    allocate_at_address_in_main_pool(temp_s4, (u8* ) D_8011D30C, COLOUR_TAG_YELLOW);
    set_free_queue_state(2);
    func_800A83B4(gCurrentLevelModel);

    for(i = 0; i < gCurrentLevelModel->numberOfSegments; i++) {
        for(temp_s4 = 0; temp_s4 < gCurrentLevelModel->segments[i].numberOfBatches; temp_s4++) {
            for(k = gCurrentLevelModel->segments[i].batches[temp_s4].verticesOffset; 
                k < gCurrentLevelModel->segments[i].batches[temp_s4+1].verticesOffset; 
                k++) {
                // Why do this? Why not just set the vertex colors in the model itself?
                if(gCurrentLevelModel->segments[i].vertices[k].r == 1 && gCurrentLevelModel->segments[i].vertices[k].g == 1) { 
                    gCurrentLevelModel->segments[i].vertices[k].a = gCurrentLevelModel->segments[i].vertices[k].b;
                    gCurrentLevelModel->segments[i].vertices[k].r = 0x80;
                    gCurrentLevelModel->segments[i].vertices[k].g = 0x80;
                    gCurrentLevelModel->segments[i].vertices[k].b = 0x80;
                    gCurrentLevelModel->segments[i].batches[temp_s4].flags |= 0x08000000;
                }
            }
        }
    }
    set_texture_colour_tag(COLOUR_TAG_MAGENTA);
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002C0C4.s")
#endif

void func_8002C71C(LevelModelSegment *segment) {
    s32 curVertY;
    s32 numVerts;
    s32 i;

    segment->unk38 = -10000;
    numVerts = 0;
    for (i = 0; i < segment->numberOfBatches; i++) {
        if (segment->batches[i].flags & 0x2000) {
            segment->unk34[numVerts++] = i;
            curVertY = segment->vertices[segment->batches[i].verticesOffset].y;
            if (segment->unk38 == -10000 || segment->unk38 < curVertY) {
                segment->unk38 = curVertY;
            }
        }
    }
    segment->unk32 = numVerts;
}

LevelModel *get_current_level_model(void) {
    return gCurrentLevelModel;
}

void func_8002C7D4(void) {
    s32 i;

    func_8000B290();
    if (D_8011D384 != 0) {
        func_800B7D20();
    }
    for(i = 0; i < gCurrentLevelModel->numberOfTextures; i++) {
        free_texture(gCurrentLevelModel->textures[i].texture);
    }
    free_from_memory_pool(D_8011D30C);
    free_from_memory_pool(D_8011D370);
    free_from_memory_pool(D_8011D374);
    free_sprite((Sprite *) gCurrentLevelModel->unk20);
    for(i = 0; i < MAXCONTROLLERS; i++) {
        free_from_memory_pool(D_8011D350[i]);
        free_from_memory_pool(D_8011D320[i]);
        free_from_memory_pool(D_8011D338[i]);
    }
    func_800257D0();
    if (D_8011B0B8 != NULL) {
        gParticlePtrList_addObject(D_8011B0B8);
        gParticlePtrList_flush();
    }
    func_8000C604();
    gCurrentLevelModel = NULL;
}

void func_8002C954(LevelModelSegment *segment, LevelModelSegmentBoundingBox *bbox, UNUSED s32 arg2) {
    Vertex *vert;
    s16 boxDelta;
    s32 vertZ;
    s32 vertX;
    s16 boxMin;
    s16 bit;
    s16 maxX;
    s32 j;
    s16 minX;
    s16 val;
    s16 maxZ;
    s16 minZ;
    s16 k;
    s16 boxMax;
    s32 i;
    s32 l;
    s32 startTri;
    s32 endTri;
    s32 vertsOffset;

    for (i = 0; i < segment->numberOfBatches; i++) {
        startTri = segment->batches[i].facesOffset;
        endTri = segment->batches[i+1].facesOffset;
        vertsOffset = segment->batches[i].verticesOffset;
        for (j = startTri; j < endTri; j++) {
            if (segment->triangles[j].flags & 0x80) {
                segment->unk10[j] = 0;
            } else {
                maxX = -32000;
                maxZ = -32000;
                minZ = 32000;
                minX = 32000;
                
                for (l = 0; l != 3; l++) {
                    vert = &segment->vertices[segment->triangles[j].verticesArray[l + 1] + vertsOffset];
                    k = vert->x; vertX = k; // This is probably fake, but it matches.
                    vertZ = vert->z;
                    if (maxX < vertX) {
                        maxX = vertX;
                    }
                    if (vertX < minX) {
                        minX = vertX;
                    }
                    if (maxZ < vertZ) {
                        maxZ = vertZ;
                    }
                    if (vertZ < minZ) {
                        minZ = vertZ;
                    }
                }
                boxDelta = ( (bbox->x2 - bbox->x1) >> 3) + 1;
                bit = 1;
                boxMax = boxDelta + bbox->x1;
                boxMin = bbox->x1;
                val = 0;
                for (k = 0; k < 8; k++) {
                    if ((boxMax >= minX) && (maxX >= boxMin)) {
                        val |= bit;
                    }
                    boxMax += boxDelta;
                    boxMin += boxDelta;
                    bit <<= 1;
                }
                boxDelta = ((bbox->z2 - bbox->z1) >> 3) + 1;
                boxMax = boxDelta + bbox->z1;
                boxMin = bbox->z1;
                for (k = 0; k < 8; k++) {
                    if ((boxMax >= minZ) && (maxZ >= boxMin)) {
                        val |= bit;
                    }
                    boxMax += boxDelta;
                    boxMin += boxDelta;
                    bit <<= 1;
                }
                segment->unk10[j] = val;
            }
        }
    } 
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002CC30.s")

typedef struct unk8002D30C_a0 {
    u8 pad00[0x04];
    struct unk8002D30C_a0 *unk04;
    struct unk8002D30C_a0 *unk08;
} unk8002D30C_a0;

void func_8002D30C(unk8002D30C_a0 *arg0, s32 arg1) {
    while(1) {
        if(!arg0) {
            return;
        }
        if (arg0->unk04) {
            arg0->unk04 = (unk8002D30C_a0 *)((s32)arg0->unk04 + arg1);
        }
        if (arg0->unk08) {
            arg0->unk08 = (unk8002D30C_a0 *)((s32)arg0->unk08 + arg1);
        }

        func_8002D30C(arg0->unk04, arg1);
        arg0 = arg0->unk08;
    }
}

/**
 * Render a flat model that projects itself on the floor.
 */
void render_floor_decal(Object *obj, Object_50 *arg1) {
    s32 i;
    s32 temp_a0;
    s32 temp_a3;
    Vertex *vtx;
    Triangle *tri;
    s32 flags;
    UNUSED s32 temp2;
    s32 temp3;
    s32 new_var;
    s32 new_var2;
    s32 someAlpha;
    
    if (obj->segment.header->unk32 != 0) {
        if (arg1->unk8 != -1 && D_8011B0C4 == 0) {
            D_8011B0CC = D_8011B0C8;
            if (obj->segment.header->unk32 == 1) {
                D_8011B0CC += 2;
            }
            i = arg1->unk8;
            D_8011D360 = (unk8011D360 *) D_8011D350[D_8011B0CC];
            D_8011D330 = (unk8011D330 *) D_8011D320[D_8011B0CC];
            D_8011D348 = (unk8011D348 *) D_8011D338[D_8011B0CC];
            someAlpha = D_8011D348[D_8011D360[i].unk6].unk9;
            flags = RENDER_FOG_ACTIVE | RENDER_Z_COMPARE;
            if (someAlpha == 0 || obj->segment.unk38.half.lower == 0) {
                i = arg1->unkA;
            } else if (someAlpha != 255 || obj->segment.unk38.half.lower != 255) {
                flags = RENDER_FOG_ACTIVE | RENDER_SEMI_TRANSPARENT | RENDER_Z_COMPARE;
                someAlpha = (obj->segment.unk38.half.lower * someAlpha) >> 8;
                gDPSetPrimColor(gSceneCurrDisplayList++, 0, 0, 255, 255, 255, someAlpha);
            }
            while (i < arg1->unkA) {
                load_and_set_texture_no_offset(&gSceneCurrDisplayList, (TextureHeader *) D_8011D360[i].unk0, flags);
                // I hope we can clean this part up.
                temp2 = new_var2 = D_8011D360[i].unk4; // Fakematch
                temp3 = new_var = D_8011D360[i].unk6;
                temp_a3 = D_8011D360[i+1].unk4 - new_var2;
                temp_a0 = D_8011D360[i+1].unk6 - new_var;
                tri = (Triangle *) &D_8011D330[new_var2];
                vtx = (Vertex *) &D_8011D348[temp3];
                gSPVertexDKR(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(vtx), temp_a0, 0);
                gSPPolygon(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(tri), temp_a3, 1);
                i++;
            }
            
            if (flags != RENDER_Z_COMPARE) {
                gDPSetPrimColor(gSceneCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            }
        }
    }
}

void func_8002D670(Object *obj, Object_50 *arg1) {
    s32 i;
    s32 temp_a0;
    s32 temp_a3;
    Vertex *vtx;
    Triangle *tri;
    s32 flags;
    UNUSED s32 temp2;
    UNUSED s32 temp3;

    if (obj->segment.header->unk36 != 0) {
        if ((arg1->unk8 != -1) && (D_8011B0C4 == 0)) {
            D_8011B0D0 = D_8011B0C8;
            i = arg1->unk8;
            if (obj->segment.header->unk36 == 1) {
                D_8011B0D0 = D_8011B0C8;
                D_8011B0D0 += 2;
                if (get_distance_to_active_camera(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position) > 768.0f) {
                    i = arg1->unkA;
                }
            }
            flags = RENDER_FOG_ACTIVE | RENDER_Z_COMPARE;
            D_8011D360 = (unk8011D360* ) D_8011D350[D_8011B0D0];
            D_8011D330 = (unk8011D330* ) D_8011D320[D_8011B0D0];
            D_8011D348 = (unk8011D348* ) D_8011D338[D_8011B0D0];
            while (i < arg1->unkA) {
                load_and_set_texture_no_offset(&gSceneCurrDisplayList, (TextureHeader *) D_8011D360[i].unk0, flags);
                temp2 = D_8011D360[i].unk4; // Fakematch
                temp3 = D_8011D360[i].unk6; // Fakematch
                temp_a3 = D_8011D360[i+1].unk4 - D_8011D360[i].unk4;
                temp_a0 = D_8011D360[i+1].unk6 - D_8011D360[i].unk6;
                tri = &((Triangle *) D_8011D330)[D_8011D360[i].unk4];
                vtx = &((Vertex *) D_8011D348)[D_8011D360[i].unk6];
                gSPVertexDKR(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(vtx), temp_a0, 0);
                gSPPolygon(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(tri), temp_a3, 1);
                i++;
            }
        }
    }
}

void func_8002D8DC(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp94;
    s32 sp90;
    Object *obj;
    ObjectHeader *objHeader;
    f32 var_f20;
    s32 temp_v1_2;
    s32 numViewports;
    Object **objects;
    s32 var_a0;
    Object_58_4* obj58_4;
    Object_50 *obj50;
    Object_58* obj58;
    s32 temp;

    D_8011B0CC = D_8011B0C8;
    if (arg0 == 1) {
        D_8011B0CC += 2;
    }
    D_8011D330 = (unk8011D330* ) D_8011D320[D_8011B0CC];
    D_8011D348 = (unk8011D348* ) D_8011D338[D_8011B0CC];
    D_8011D360 = (unk8011D360* ) D_8011D350[D_8011B0CC];
    D_8011D364 = 0;
    D_8011D368 = 0;
    D_8011D36C = 0;
    numViewports = get_viewport_count();
    objects = func_8000E988(&sp94, &sp90);
    while (sp94 < sp90) {
        obj = objects[sp94];
        objHeader = obj->segment.header;
        obj58 = obj->unk58;
        obj50 = obj->unk50;
        sp94 += 1;
        if (!(obj->segment.trans.unk6 & 0x8000)) {
            if (obj50 != NULL && obj50->unk0 > 0.0f && arg0 == objHeader->unk32) {
                obj50->unk8 = -1;
            } 
            if (obj->segment.trans.unk6 & 0x4000) {
                obj50 = NULL;
            }
            if ((obj50 != NULL && objHeader->unk32 == 2) || (obj58 != NULL && objHeader->unk36 == 2)) {
                var_f20 = get_distance_to_active_camera(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
            } else {
                var_f20 = 0;
            }
            if (obj50 != NULL && obj50->unk0 > 0.0f && arg0 == objHeader->unk32) {
                D_8011D0D4 = 1.0f;
                obj50->unk8 = -1;
                var_a0 = FALSE;
                if (objHeader->unk32 == 2 && numViewports > ONE_PLAYER && numViewports <= FOUR_PLAYERS) {
                    if (obj->behaviorId == BHV_RACER) {
                        temp = obj->unk64->racer.playerIndex;
                        if (temp != PLAYER_COMPUTER) {
                            func_8002E234(obj, FALSE);
                            var_a0 = TRUE;
                        }
                    } else if (obj->behaviorId == BHV_WEAPON) {
                        func_8002E234(obj, FALSE);
                        var_a0 = TRUE;
                    }
                } else {
                    temp_v1_2 = objHeader->unk4A;
                    if (var_f20 < temp_v1_2) {
                        if (objHeader->unk4C < var_f20) {
                            D_8011D0D4 = (temp_v1_2 - var_f20) / ( temp_v1_2 - objHeader->unk4C);
                        }
                        func_8002E234(obj, FALSE);
                        var_a0 = TRUE;
                    }
                }
                if ((!var_a0) && (obj->unk54 != NULL)) {
                    func_8002DE30(obj);
                }
            }
            if (obj58 != NULL && obj58->unk0 > 0.0f && arg1 == objHeader->unk36) {
                obj58->unk8 = -1;
                D_8011D0D4 = 1.0f;
                obj58_4 = obj58->unk4;
                if (obj58_4 != NULL && arg2 != 0 && obj58_4->unk12 != 0x100) {
                    obj58->unkC += obj58->unkE;
                    while (obj58_4->unk12 < obj58->unkC) {
                        obj58->unkC -= obj58_4->unk12;
                    } 
                }
                
                if (objHeader->unk32 == 2 && numViewports > ONE_PLAYER && numViewports <= FOUR_PLAYERS) {
                    if (obj->behaviorId == BHV_RACER) {
                        temp = obj->unk64->racer.playerIndex;
                        if (temp != -1) {
                            func_8002E234(obj, TRUE);
                        }
                    } else if (obj->behaviorId == BHV_WEAPON) {
                        func_8002E234(obj, TRUE);
                    }
                } else {
                    if (var_f20 < objHeader->unk4A) {
                        if (objHeader->unk4C < var_f20) {
                            D_8011D0D4 = (objHeader->unk4A - var_f20) / (objHeader->unk4A - objHeader->unk4C);
                        }
                        func_8002E234(obj, TRUE);
                    }
                }
            }
        }
    }
    D_8011D360[D_8011D364].unk4 = D_8011D368;
    D_8011D360[D_8011D364].unk6 = D_8011D36C;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002DE30.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002E234.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002E904.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002EEEC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002F2AC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002F440.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002FA64.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002FD74.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002FF6C.s")

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800304C8.s")

#ifdef NON_EQUIVALENT

// Should be functionally equivalent.
void func_80030664(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5) {
    s32 max, min;

    max = arg2;
    min = arg1;
    if (arg2 < arg1) {
        max = arg1;
        min = arg2;
    }
    if (max >= 0x400) {
        max = 0x3FF;
    }
    if (min >= max - 5) {
        min = max - 5;
    }
    D_8011D388[arg0].unk20 = 0;
    D_8011D388[arg0].unk24 = 0;
    D_8011D388[arg0].unk14 = 0;
    D_8011D388[arg0].unk18 = 0;
    D_8011D388[arg0].unk1C = 0;
    D_8011D388[arg0].unk0 = arg3 << 0x10;
    D_8011D388[arg0].unk4 = arg4 << 0x10;
    D_8011D388[arg0].unk8 = arg5 << 0x10;
    D_8011D388[arg0].unkC = min << 0x10;
    D_8011D388[arg0].unk10 = max << 0x10;
    D_8011D388[arg0].unk28 = arg3;
    D_8011D388[arg0].unk2C = min;
    D_8011D388[arg0].unk2E = max;
    D_8011D388[arg0].unk30 = 0;
    D_8011D388[arg0].unk34 = 0;
    D_8011D388[arg0].unk29 = arg4;
    D_8011D388[arg0].unk2A = arg5;
}

#else
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030664.s")
#endif

void func_80030750(s32 arg0, s16 *arg1, s16 *arg2, u8 *arg3, u8 *arg4, u8 *arg5) {
    *arg1 = D_8011D388[arg0].unkC >> 0x10;
    *arg2 = D_8011D388[arg0].unk10 >> 0x10;
    *arg3 = D_8011D388[arg0].unk0 >> 0x10;
    *arg4 = D_8011D388[arg0].unk4 >> 0x10;
    *arg5 = D_8011D388[arg0].unk8 >> 0x10;
}

void func_800307BC(s32 arg0) {
    D_8011D388[arg0].unk20 = 0;
    D_8011D388[arg0].unk24 = 0;
    D_8011D388[arg0].unk14 = 0;
    D_8011D388[arg0].unk18 = 0;
    D_8011D388[arg0].unk1C = 0;
    D_8011D388[arg0].unkC = 0x03FA0000;
    D_8011D388[arg0].unk10 = 0x03FF0000;
    D_8011D388[arg0].unk28 = D_8011D388[arg0].unk0 >> 0x10;
    D_8011D388[arg0].unk29 = D_8011D388[arg0].unk4 >> 0x10;
    D_8011D388[arg0].unk2A = D_8011D388[arg0].unk8 >> 0x10;
    D_8011D388[arg0].unk2C = 0x03FA;
    D_8011D388[arg0].unk2E = 0x03FF;
    D_8011D388[arg0].unk30 = 0;
    D_8011D388[arg0].unk34 = 0;
}

void func_80030838(s32 arg0, s32 arg1) {
    s32 i;
    for (i = 0; i < arg0; i++) {
        if (D_8011D388[i].unk30 > 0) {
            if (arg1 < D_8011D388[i].unk30) {
                D_8011D388[i].unk0 += D_8011D388[i].unk14 * arg1;
                D_8011D388[i].unk4 += D_8011D388[i].unk18 * arg1;
                D_8011D388[i].unk8 += D_8011D388[i].unk1C * arg1;
                D_8011D388[i].unkC += D_8011D388[i].unk20 * arg1;
                D_8011D388[i].unk10 += D_8011D388[i].unk24 * arg1;
                D_8011D388[i].unk30 -= arg1;
            } else {
                D_8011D388[i].unk0 = D_8011D388[i].unk28 << 0x10;
                D_8011D388[i].unk4 = D_8011D388[i].unk29 << 0x10;
                D_8011D388[i].unk8 = D_8011D388[i].unk2A << 0x10;
                D_8011D388[i].unkC = D_8011D388[i].unk2C << 0x10;
                D_8011D388[i].unk10 = D_8011D388[i].unk2E << 0x10;
                D_8011D388[i].unk30 = 0;
            }
        }
    }
}

void func_8003093C(s32 arg0) {
    gDPSetFogColor(gSceneCurrDisplayList++, D_8011D388[arg0].unk0 >> 0x10, D_8011D388[arg0].unk4 >> 0x10, D_8011D388[arg0].unk8 >> 0x10, 0xFF);
    gSPFogPosition(gSceneCurrDisplayList++, D_8011D388[arg0].unkC >> 0x10, D_8011D388[arg0].unk10 >> 0x10);
}

/**
 * Sets the active viewport's fog target when passed through.
 * Used in courses to make less, or more dense.
*/
void obj_loop_fogchanger(Object *obj) {
    s32 temp3;
    s32 fogNear;
    s32 views;
    s32 playerIndex;
    s32 index;
    UNUSED s32 pad;
    s32 fogFar;
    s32 i;
    s32 fogR;
    s32 fogG;
    s32 fogB;
    f32 x;
    f32 z;
    s32 temp_a1;
    LevelObjectEntry_FogChanger *sp44;
    Object **racers;
    Object_Racer *racer;
    UNUSED s32 pad2;
    unk8011D388 *temp_v0_3;
    ObjectSegment *phi_s3;
    
    racers = NULL;
    sp44 = (LevelObjectEntry_FogChanger *) obj->segment.unk3C_a.level_entry;
    phi_s3 = NULL;
    
    if (check_if_showing_cutscene_camera()) {
        phi_s3 = func_80069D7C();
        views = get_viewport_count() + 1;
    } else {
        racers = get_racer_objects(&views);
    }
    
    for(i = 0; i < views; i++) {
        index = PLAYER_COMPUTER;
        if (racers != NULL) {
            racer = &racers[i]->unk64->racer;
            playerIndex = racer->playerIndex;
            if (playerIndex >= PLAYER_ONE && playerIndex <= PLAYER_FOUR && obj != D_8011D388[playerIndex].unk34) {
                index = playerIndex;
                x = racers[i]->segment.trans.x_position;
                z = racers[i]->segment.trans.z_position;
            }
        } else if (i <= PLAYER_FOUR && obj != D_8011D388[i].unk34) {
            index = i;
            x = phi_s3[i].trans.x_position;
            z = phi_s3[i].trans.z_position;
        }
        if (index != PLAYER_COMPUTER) {
            x -= obj->segment.trans.x_position;
            z -= obj->segment.trans.z_position;
            if (1) {} // Fakematch
            if ((x * x) + (z * z) < obj->unk78f) {
                fogNear = sp44->unkC;
                fogFar = sp44->unkE;
                fogR = sp44->unk9;
                fogG = sp44->unkA;
                fogB = sp44->unkB;
                temp_a1 = sp44->unk10;
                if (fogFar < fogNear) {
                    temp3 = fogNear;
                    fogNear = fogFar;
                    fogFar = temp3;
                }
                if (fogFar > 1023) {
                    fogFar = 1023;
                }
                if (fogNear >= fogFar - 5) {
                    fogNear = fogFar - 5;
                }
                temp_v0_3 = &D_8011D388[index];
                temp_v0_3->unk28 = fogR;
                temp_v0_3->unk29 = fogG;
                temp_v0_3->unk2A = fogB;
                temp_v0_3->unk2C = fogNear;
                temp_v0_3->unk2E = fogFar;
                temp_v0_3->unk14 = ((fogR << 16) - temp_v0_3->unk0) / temp_a1;
                temp_v0_3->unk18 = ((fogG << 16) - temp_v0_3->unk4) / temp_a1;
                temp_v0_3->unk1C = ((fogB << 16) - temp_v0_3->unk8) / temp_a1;
                temp_v0_3->unk20 = ((fogNear << 16) - temp_v0_3->unkC) / temp_a1;
                temp_v0_3->unk24 = ((fogFar << 16) - temp_v0_3->unk10) / temp_a1;
                temp_v0_3->unk30 = temp_a1;
                temp_v0_3->unk34 = obj;
            }
        }
    }
}

#ifdef NON_EQUIVALENT
void func_80030DE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 max, min;
    unk8011D388 *entry;

    entry = &D_8011D388[arg0];
    max = arg5;
    min = arg4;
    if (arg5 < arg4) {
        max = arg4;
        min = arg5;
    }
    if (max > 0x3FF) {
        max = 0x3FF;
    }
    if (min >= max - 5) {
        min = max - 5;
    }
    entry->unk28 = arg1;
    entry->unk29 = arg2;
    entry->unk2A = arg3;
    entry->unk2C = min;
    entry->unk2E = max;
    entry->unk14 = ((arg1 << 16) - entry->unk0) / arg6;
    entry->unk18 = ((arg2 << 16) - entry->unk4) / arg6;
    entry->unk1C = ((arg3 << 16) - entry->unk8) / arg6;
    entry->unk20 = ((min << 16) - entry->unkC) / arg6;
    entry->unk24 = ((max << 16) - entry->unk10) / arg6;
    entry->unk30 = arg6;
    entry->unk34 = 0;
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030DE0.s")
#endif

UNUSED void func_80030FA0(void) {
    D_8011B0B0 = get_active_camera_segment();
    func_80031018();
    set_and_normalize_D_8011AFE8((f32) D_8011D468.x / 65536.0f, (f32) D_8011D468.y / 65536.0f, (f32) D_8011D468.z / 65536.0f);
}

void func_80031018(void) {
    Matrix mf;
    ObjectTransform trans;

    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = -65536.0f;

    trans.z_rotation = D_8011B0B0->trans.z_rotation;
    trans.x_rotation = D_8011B0B0->trans.x_rotation;
    trans.y_rotation = D_8011B0B0->trans.y_rotation;
    trans.x_position = 0.0f;
    trans.y_position = 0.0f;
    trans.z_position = 0.0f;
    trans.scale = 1.0f;

    object_transform_to_matrix(mf, &trans);
    guMtxXFMF(mf, x, y, z, &x, &y, &z);

    //Store x/y/z as integers
    D_8011D468.x = (s32)x;
    D_8011D468.y = (s32)y;
    D_8011D468.z = (s32)z;
}
