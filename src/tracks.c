#include "tracks.h"

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
#include "objects.h"
#include "math_util.h"
#include "printf.h"
#include "collision.h"
#include "PRinternal/viint.h"
#include "common.h"

// Maximum size for a level model is 522.5 KiB
#define LEVEL_MODEL_MAX_SIZE 0x82A00
#define LEVEL_SEGMENT_MAX 128

#define FLAGS_8002E904 \
    (BATCH_FLAGS_HIDDEN | BATCH_FLAGS_RECEIVE_SHADOWS | BATCH_FLAGS_WATER | BATCH_FLAGS_FORCE_NO_SHADOWS)

/************ .data ************/

s32 D_800DC870 = 0; // Currently unknown, might be a different type.
//!@bug These two transition effects are marked to not clear when done, meaning they stay active the whole time.
FadeTransition gFullFadeToBlack = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_OUT, FADE_COLOR_BLACK, 40, FADE_STAY);
FadeTransition gCircleFadeToBlack = FADE_TRANSITION(FADE_CIRCLE, FADE_FLAG_OUT, FADE_COLOR_BLACK, 70, FADE_STAY);

f32 D_800DC884[10] = { 0.0f, 0.125f, 0.25f, 0.375f, 0.5f, 0.625f, 0.75f, 0.875f };

Vec3f D_800DC8AC[3][3] = {
    { { { { 50.0f, 0.0f, 32.0f } } }, { { { -50.0f, 0.0f, 32.0f } } }, { { { -50.0f, 100.0f, 32.0f } } } },
    { { { { 0.0f, 0.0f, 32.0f } } }, { { { 130.0f, 60.0f, -68.0f } } }, { { { 130.0f, -60.0f, -68.0f } } } },
    { { { { 0.0f, 0.0f, 32.0f } } }, { { { -130.0f, -60.0f, -68.0f } } }, { { { -130.0f, 60.0f, -68.0f } } } },
};

LevelModel *gCurrentLevelModel = NULL; // Official Name: track
LevelHeader *gCurrentLevelHeader2 = NULL;

s32 D_800DC920 = -1;
#if REGION == REGION_JP
// T.T.カメラ  -  T.T. Camera
char gJpnTTCam[] = { 0x80, 0x2D, 0x80, 0x3C, 0x80, 0x2D, 0x80, 0x3C, 0x80, 0x55, 0x80, 0x71, 0x80, 0x76 };
#endif
u8 *D_800DC924 = NULL;
s32 D_800DC928 = 0; // Currently unknown, might be a different type.

u8 D_800DC92C[24] = {
    0, 1, 4, 1, 2, 4, 2, 3, 4, 3, 0, 4, 5,
    6, 1, 1, 0, 5, 3, 2, 7, 7, 8, 3
    // There may or may not be extra zeroes here.
};

/*******************************/

/************ .bss ************/

Gfx *gSceneCurrDisplayList;
MatrixS *gSceneCurrMatrix;
Vertex *gSceneCurrVertexList;
Triangle *gSceneCurrTriList;

ObjectSegment *gSceneActiveCamera;

s32 gSceneCurrentPlayerID;
Object *gSkydomeSegment;
UNUSED s32 gIsNearCurrBBox; // Set to true if the current visible segment is close to the camera.
UNUSED s32 D_8011B0C0;      // Set to 0 then never read.
UNUSED s32 gDisableShadows; // Never not 0.
s32 gShadowHeapFlip;        // Flips between 0 and 1 to prevent incorrect access between frames.
s32 gShadowIndex;
s32 gWaterEffectIndex;
s32 gSceneStartSegment;
s32 D_8011B0D8;
s32 gSceneRenderSkyDome;
s8 gDrawLevelSegments;
u8 D_8011B0E1; // R of RGB
u8 D_8011B0E2; // G of RGB
u8 D_8011B0E3; // B of RGB
f32 D_8011B0E4;
f32 D_8011B0E8;
f32 D_8011B0EC;
s32 D_8011B0F0;
s32 D_8011B0F4;
s32 D_8011B0F8; // gIsInCutscene?
s32 gAntiAliasing;
s32 D_8011B100;
s32 D_8011B104;
s32 D_8011B108;
s32 D_8011B10C;
s32 D_8011B110;
u32 D_8011B114;
s32 D_8011B118;
s32 D_8011B11C;
unk8011B120 D_8011B120[32]; // Struct sizeof(0x10) / sizeof(16)
s32 D_8011B320[4];
unk8011B330 D_8011B330[120]; // Struct sizeof(0x20) / sizeof(32)
s32 D_8011C230;
s32 D_8011C234;
unk8011C238 D_8011C238[32]; // Struct sizeof(0xC) / sizeof(12)
unk8011C3B8 D_8011C3B8[64];
unk8011C8B8 D_8011C8B8[128];
s32 D_8011D0B8;
unk8011C8B8 *D_8011D0BC;
TextureHeader *gNewShadowTexture;
Object *gNewShadowObj;
f32 D_8011D0C8;
s16 gNewShadowY1;
s16 gNewShadowY2;
s16 D_8011D0D0;
f32 gShadowOpacity;
f32 gNewShadowScale;
f32 gNewShadowWidth;
f32 gNewShadowLength;
f32 D_8011D0E4;
s32 D_8011D0E8;
s32 D_8011D0EC;
f32 D_8011D0F0;
f32 D_8011D0F4;
Vec4f D_8011D0F8[3];
WaterProperties D_8011D128[20];
WaterProperties *gTrackWaves[20];
s8 D_8011D308;
LevelModel *gTrackModelHeap;
s32 *gLevelModelTable;
UNUSED f32 gPrevCameraX;          // Set but never read
UNUSED f32 gPrevCameraY;          // Set but never read
UNUSED f32 gPrevCameraZ;          // Set but never read
Triangle *gShadowHeapTris[2 + 2]; // Triangle Data for shadows
Triangle *gCurrShadowTris;
UNUSED s32 D_8011D334;
Vertex *gShadowHeapVerts[2 + 2]; // Vertex Data for shadows
Vertex *gCurrShadowVerts;
UNUSED s32 D_8011D34C;
ShadowHeapProperties *gShadowHeapData[2 + 2]; // General data for shadows. Texture and geometry size.
ShadowHeapProperties *gCurrShadowHeapData;
s32 gShadowTail;        // Position in the heap the shadow data ends at.
s32 gNewShadowTriCount; // xOffset?
s32 gNewShadowVtxCount; // yOffset?
u16 **D_8011D370;       // Allocated 0x7D0
s32 *D_8011D374;
s32 D_8011D378;
s32 gScenePlayerViewports;
UNUSED f32 gCurrBBoxDistanceToCamera; // Used in a comparison check, but functionally unused.
u32 gWaveBlockCount;
FogData gFogData[4];
Vec3i gScenePerspectivePos;
unk8011D474 *D_8011D474; // 0x10 bytes struct?
unk8011D478 *D_8011D478; // 0xC bytes struct?
s8 *D_8011D47C;
Vertex *D_8011D480[2];
Vertex *D_8011D488;
s32 D_8011D48C;
Triangle *D_8011D490[2];
Triangle *D_8011D498;
s16 D_8011D49C;
s16 D_8011D49E;
f32 D_8011D4A0; // something x coordinate related
f32 D_8011D4A4; // something z coordinate related
f32 D_8011D4A8;
f32 D_8011D4AC; // something x coordinate related
f32 D_8011D4B0; // something z coordinate related
s8 D_8011D4B4;
typedef struct Unk8011D4B6 {
    union {
        struct {
            u8 one, two;
        };
        s16 whole;
    };
} Unk8011D4B6;
Unk8011D4B6 D_8011D4B6;
s16 D_8011D4B8;
s16 D_8011D4BA;
s16 D_8011D4BC;

/******************************/

/**
 * Sets the number of expected viewports in the scene.
 * Like most other viewport vars, it's 0-3 rather than 1-4.
 * Set as an s32 for some reason.
 */
s32 set_scene_viewport_num(s32 numPorts) {
    gScenePlayerViewports = numPorts;
    return 0;
}

/**
 * Initialises the level.
 * Allocates RAM to load generate the level geometry, spawn objects and generate shadows.
 */
void init_track(u32 geometry, u32 skybox, s32 numberOfPlayers, Vehicle vehicle, u32 entranceId, u32 collectables,
                u32 arg6) {
    s32 i;

    gCurrentLevelHeader2 = get_current_level_header();
    D_8011B0F8 = FALSE;
    D_8011B100 = 0;
    D_8011B104 = 0;
    D_8011B108 = 0;
    D_8011B10C = 0;

    if (gCurrentLevelHeader2->race_type == RACETYPE_CUTSCENE_1 ||
        gCurrentLevelHeader2->race_type == RACETYPE_CUTSCENE_2) {
        D_8011B0F8 = TRUE;
    }

    func_8002C0C4(geometry);

    gWaveBlockCount = 0;

    if (numberOfPlayers < 2) {
        for (i = 0; i < gCurrentLevelModel->numberOfSegments; i++) {
            if (gCurrentLevelModel->segments[i].hasWaves != 0) {
                gWaveBlockCount++;
                gCurrentLevelModel->segments[i].hasWaves = 1;
            }
        }
    }

    if (is_in_two_player_adventure() &&
        (gCurrentLevelHeader2->race_type == RACETYPE_DEFAULT || gCurrentLevelHeader2->race_type & RACETYPE_CHALLENGE)) {
        i = 2;
    } else {
        i = numberOfPlayers + 1;
    }

    if (gWaveBlockCount) {
        func_800B82B4(gCurrentLevelModel, gCurrentLevelHeader2, i);
    }

    set_active_viewports_and_max(numberOfPlayers);
    spawn_skydome(skybox);
    D_8011B110 = 0;
    D_8011B114 = 0x10000;
    path_enable();
    func_8000C8F8(arg6, 0);
    func_8000C8F8(collectables, 1);
    gScenePlayerViewports = numberOfPlayers;
    func_8000CC7C(vehicle, entranceId, numberOfPlayers);
    racerfx_alloc(72, 64);

    if (geometry == 0 && entranceId == 0) {
        transition_begin(&gCircleFadeToBlack);
    } else {
        transition_begin(&gFullFadeToBlack);
    }
    set_active_viewports_and_max(gScenePlayerViewports);

    numberOfPlayers = gScenePlayerViewports;
    gAntiAliasing = FALSE;
    // All shadow groups are double buffered. Environment shadows never change, so they could've single buffered them.
    for (i = 0; i < ARRAY_COUNT(gShadowHeapData); i++) {
        gShadowHeapData[i] =
            (ShadowHeapProperties *) mempool_alloc_safe(sizeof(ShadowHeapProperties) * 400, COLOUR_TAG_YELLOW);
        gShadowHeapTris[i] = (Triangle *) mempool_alloc_safe(sizeof(Triangle) * 800, COLOUR_TAG_YELLOW);
        gShadowHeapVerts[i] = (Vertex *) mempool_alloc_safe(sizeof(Vertex) * 2000, COLOUR_TAG_YELLOW);
    }

    gShadowHeapFlip = 0;
    shadow_update(SHADOW_SCENERY, SHADOW_SCENERY, LOGIC_NULL);
    shadow_update(SHADOW_ACTORS, SHADOW_ACTORS, LOGIC_NULL);
    gShadowHeapFlip = 1;
    shadow_update(SHADOW_SCENERY, SHADOW_SCENERY, LOGIC_NULL);
    shadow_update(SHADOW_ACTORS, SHADOW_ACTORS, LOGIC_NULL);
    gShadowHeapFlip = 0;
    if (gCurrentLevelHeader2->unkB7) {
        D_8011B0E1 = gCurrentLevelHeader2->rgb.red;
        D_8011B0E2 = gCurrentLevelHeader2->rgb.green;
        D_8011B0E3 = gCurrentLevelHeader2->rgb.blue;
        func_80025510(numberOfPlayers + 1);
    }
}

/**
 * The root function for rendering the entire scene.
 * Handles drawing the track, objects and the majority of the HUD in single player.
 */
void render_scene(Gfx **dList, MatrixS **mtx, Vertex **vtx, Triangle **tris, s32 updateRate) {
    s32 i;
    s32 numViewports;
    s32 tempUpdateRate;
    s8 flip;
    s32 posX;
    s32 posY;
    s32 j;

    gSceneCurrDisplayList = *dList;
    gSceneCurrMatrix = *mtx;
    gSceneCurrVertexList = *vtx;
    gSceneCurrTriList = *tris;
    gSceneRenderSkyDome = TRUE;
    gDisableShadows = FALSE;
    D_8011B0C0 = 0;
    gIsNearCurrBBox = FALSE;
    numViewports = set_active_viewports_and_max(gScenePlayerViewports);
    if (is_game_paused()) {
        tempUpdateRate = 0;
    } else {
        tempUpdateRate = updateRate;
    }
    if (gWaveBlockCount) {
        func_800B9C18(tempUpdateRate);
    }
    shadow_update(SHADOW_ACTORS, SHADOW_ACTORS, updateRate);
    for (i = 0; i < 7; i++) {
        if ((s32) gCurrentLevelHeader2->unk74[i] != -1) {
            update_colour_cycle(gCurrentLevelHeader2->unk74[i], tempUpdateRate);
        }
    }
    if (gCurrentLevelHeader2->pulseLightData != (PulsatingLightData *) -1) {
        update_pulsating_light_data(gCurrentLevelHeader2->pulseLightData, tempUpdateRate);
    }
    gDrawLevelSegments = TRUE;
    if (gCurrentLevelHeader2->race_type == RACETYPE_CUTSCENE_2) {
        gDrawLevelSegments = FALSE;
        gAntiAliasing = TRUE;
    }
    if (gCurrentLevelHeader2->race_type == RACETYPE_CUTSCENE_1 || gCurrentLevelHeader2->unkBD) {
        gAntiAliasing = TRUE;
    }
    if (gCurrentLevelHeader2->skyDome == -1) {
        i = (gCurrentLevelHeader2->unkA4->width << 9) - 1;
        gCurrentLevelHeader2->unkA8 =
            (gCurrentLevelHeader2->unkA8 + (gCurrentLevelHeader2->unkA2 * tempUpdateRate)) & i;
        i = (gCurrentLevelHeader2->unkA4->height << 9) - 1;
        gCurrentLevelHeader2->unkAA =
            (gCurrentLevelHeader2->unkAA + (gCurrentLevelHeader2->unkA3 * tempUpdateRate)) & i;
        tex_animate_texture(gCurrentLevelHeader2->unkA4, &D_8011B114, &D_8011B110, tempUpdateRate);
    }
    flip = FALSE;
    if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
        flip = TRUE;
    }
#ifdef ANTI_TAMPER
    // Antipiracy measure
    if (IO_READ(0x200) != 0xAC290000) {
        flip = TRUE;
    }
#endif
    rendermode_reset(&gSceneCurrDisplayList);
    gDkrDisableBillboard(gSceneCurrDisplayList++);
    gSPClearGeometryMode(gSceneCurrDisplayList++, G_CULL_FRONT);
    gDPSetBlendColor(gSceneCurrDisplayList++, 0, 0, 0, 0x64);
    gDPSetPrimColor(gSceneCurrDisplayList++, 0, 0, 255, 255, 255, 255);
    gDPSetEnvColor(gSceneCurrDisplayList++, 255, 255, 255, 0);
    rain_fog();
    update_fog(numViewports, tempUpdateRate);
    scroll_particle_textures(tempUpdateRate);
    if (gCurrentLevelModel->numberOfAnimatedTextures > 0) {
        animate_level_textures(tempUpdateRate);
    }
    for (j = gSceneCurrentPlayerID = 0; j < numViewports; gSceneCurrentPlayerID++, j = gSceneCurrentPlayerID) {
        if (gCurrentLevelHeader2 && !gCurrentLevelHeader2 && !gCurrentLevelHeader2) {} // Fakematch
        if (j == 0) {
            if (func_8000E184() && numViewports == 1) {
                gSceneCurrentPlayerID = PLAYER_TWO;
            }
        }
        if (flip) {
            gSPSetGeometryMode(gSceneCurrDisplayList++, G_CULL_FRONT);
        }
        apply_fog(gSceneCurrentPlayerID);
        gDPPipeSync(gSceneCurrDisplayList++);
        set_active_camera(gSceneCurrentPlayerID);
        viewport_main(&gSceneCurrDisplayList, &gSceneCurrMatrix);
        func_8002A31C();
        // Show detailed skydome in single player.
        if (numViewports < 2) {
            matrix_world_origin(&gSceneCurrDisplayList, &gSceneCurrMatrix);
            if (gCurrentLevelHeader2->skyDome == -1) {
                func_80028050();
            } else {
                render_skydome();
            }
        } else {
            func_8006807C(&gSceneCurrDisplayList, &gSceneCurrMatrix);
            draw_gradient_background();
            func_80067D3C(&gSceneCurrDisplayList, &gSceneCurrMatrix);
            matrix_world_origin(&gSceneCurrDisplayList, &gSceneCurrMatrix);
        }
        gDPPipeSync(gSceneCurrDisplayList++);
        initialise_player_viewport_vars(updateRate);
        weather_clip_planes(-1, -512);
        // Show weather effects in single player.
        if (gCurrentLevelHeader2->weatherEnable > 0 && numViewports < 2) {
            weather_update(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, &gSceneCurrTriList,
                           tempUpdateRate);
        }
        lensflare_override(get_active_camera_segment());
        lensflare_render(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, get_active_camera_segment());
        hud_render_player(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList,
                          get_racer_object_by_port(gSceneCurrentPlayerID), updateRate);
    }
    // Show TT Cam toggle for the fourth viewport when playing 3 player.
    if (numViewports == 3 && get_current_level_race_type() != RACETYPE_CHALLENGE_EGGS &&
        get_current_level_race_type() != RACETYPE_CHALLENGE_BATTLE &&
        get_current_level_race_type() != RACETYPE_CHALLENGE_BANANAS) {
        if (hud_setting() == 0) {
            if (flip) {
                gSPSetGeometryMode(gSceneCurrDisplayList++, G_CULL_FRONT);
            }
            apply_fog(PLAYER_FOUR);
            gDPPipeSync(gSceneCurrDisplayList++);
            set_active_camera(PLAYER_FOUR);
            disable_cutscene_camera();
            func_800278E8(updateRate);
            viewport_main(&gSceneCurrDisplayList, &gSceneCurrMatrix);
            func_8002A31C();
            func_8006807C(&gSceneCurrDisplayList, &gSceneCurrMatrix);
            draw_gradient_background();
            func_80067D3C(&gSceneCurrDisplayList, &gSceneCurrMatrix);
            matrix_world_origin(&gSceneCurrDisplayList, &gSceneCurrMatrix);
            gDPPipeSync(gSceneCurrDisplayList++);
            initialise_player_viewport_vars(updateRate);
            weather_clip_planes(-1, -512);
            lensflare_override(get_active_camera_segment());
            lensflare_render(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList,
                             get_active_camera_segment());
            set_text_font(FONT_COLOURFUL);
            if (osTvType == OS_TV_TYPE_PAL) {
                posX = SCREEN_WIDTH_HALF + 6;
                posY = SCREEN_HEIGHT_HALF_PAL + 6;
            } else {
                posX = SCREEN_WIDTH_HALF + 10;
                posY = SCREEN_HEIGHT_HALF + 5;
            }
#if REGION == REGION_JP
            draw_text(&gSceneCurrDisplayList, posX, posY, gJpnTTCam, ALIGN_TOP_LEFT);
#else
            draw_text(&gSceneCurrDisplayList, posX, posY, "TT CAM", ALIGN_TOP_LEFT);
#endif
        } else {
            set_active_camera(PLAYER_FOUR);
            func_800278E8(updateRate);
        }
    }
    viewport_reset(&gSceneCurrDisplayList);
    gDPPipeSync(gSceneCurrDisplayList++);
    gDkrDisableBillboard(gSceneCurrDisplayList++);
    gShadowHeapFlip = 1 - gShadowHeapFlip;
    *dList = gSceneCurrDisplayList;
    *mtx = gSceneCurrMatrix;
    *vtx = gSceneCurrVertexList;
    *tris = gSceneCurrTriList;
}

/************ .rodata ************/
UNUSED const char gTrackClippingErrorString[] = "Solid Clipping x0=x1 Error!!!\n";
UNUSED const char gTrackHeightOverflowString[] = "TrackGetHeight() - Overflow!!!\n";

void func_80025510(s32 count) {
    s32 i;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    u8 *ptr;

    D_8011D4BA = 175;
    D_8011D4BC = 45;
    if (count >= 2) {
        D_8011D4BC >>= 1;
    }

    sp30 = (D_8011D4BA + 6) * sizeof(unk8011D478);
    sp2C = D_8011D4BA + 5;
    sp28 = (D_8011D4BC + 5) * 4 * sizeof(Vertex);
    sp24 = (D_8011D4BC + 5) * 2 * sizeof(Triangle);

    D_8011D474 = mempool_alloc_safe(count * sizeof(unk8011D474), COLOUR_TAG_CYAN);
    D_800DC924 = mempool_alloc_safe(sp30 + sp2C + (sp28 + sp24) * 2 * count, COLOUR_TAG_CYAN);

    ptr = D_800DC924;

    if (ptr != NULL) {
        D_8011D478 = (unk8011D478 *) ptr;
        ptr += sp30;

        D_8011D47C = (s8 *) ptr;
        ptr = (u8 *) ((s32) (ptr + sp2C + 8) & ~7);

        for (i = 0; i < count; i++) {
            D_8011D474[i].unk0 = (Triangle *) ptr;
            ptr += sp24;

            D_8011D474[i].unk4 = (Triangle *) ptr;
            ptr += sp24;

            D_8011D474[i].unk8 = (Vertex *) ptr;
            ptr += sp28;

            D_8011D474[i].unkC = (Vertex *) ptr;
            ptr += sp28;
        }
    }
    D_8011D4B4 = 0;
}

void func_800257D0(void) {
    if (D_800DC924 != NULL) {
        mempool_free(D_8011D474);
        mempool_free(D_800DC924);
        D_800DC924 = NULL;
    }
}

void func_8002581C(u8 *segmentIds, s32 numberOfSegments, s32 viewportIndex) {
    s16 i;
    s16 j;
    f32 yCameraSins;
    f32 yCameraCoss;
    f32 temp_f22;
    Vertex *spAC;
    Triangle *spA8;
    s16 temp_s3;
    s16 var_s0;
    s16 var_s4;
    s16 breakLoop;
    s32 *ptr2;
    LevelModelSegmentBoundingBox *bbox;
    s16 sum;
    s8 sp7C[24]; // possible UB here, real size is unknown
    s32 pad;

    D_8011D490[0] = D_8011D474[viewportIndex].unk0;
    D_8011D490[1] = D_8011D474[viewportIndex].unk4;
    D_8011D480[0] = D_8011D474[viewportIndex].unk8;
    D_8011D480[1] = D_8011D474[viewportIndex].unkC;
    material_set_no_tex_offset(&gSceneCurrDisplayList, NULL, RENDER_ANTI_ALIASING | RENDER_Z_COMPARE);
    D_8011D49C = 0;
    D_8011D49E = 0;

    yCameraSins = sins_f(-gSceneActiveCamera->trans.rotation.y_rotation);
    yCameraCoss = coss_f(-gSceneActiveCamera->trans.rotation.y_rotation);

    D_8011D4AC = gSceneActiveCamera->trans.x_position + yCameraSins * 250.0;
    D_8011D4B0 = gSceneActiveCamera->trans.z_position + yCameraCoss * 250.0;

    temp_f22 = -(yCameraSins * D_8011D4AC + yCameraCoss * D_8011D4B0);

    D_8011D4A0 = -yCameraCoss;
    D_8011D4A4 = yCameraSins;
    D_8011D4A8 = -(D_8011D4A0 * D_8011D4AC + D_8011D4A4 * D_8011D4B0);

    i = 0;
    for (; i < numberOfSegments; i++) {
        bbox = &gCurrentLevelModel->segmentsBoundingBoxes[segmentIds[i]];
        breakLoop = 0;
        breakLoop += bbox->x1 * yCameraSins + yCameraCoss * bbox->z1 + temp_f22 <= 0.0;
        breakLoop += yCameraSins * bbox->x2 + yCameraCoss * bbox->z1 + temp_f22 <= 0.0;
        breakLoop += bbox->x1 * yCameraSins + yCameraCoss * bbox->z2 + temp_f22 <= 0.0;
        breakLoop += yCameraSins * bbox->x2 + yCameraCoss * bbox->z2 + temp_f22 <= 0.0;
        if (breakLoop & 3) {
            func_80026430(&gCurrentLevelModel->segments[segmentIds[i]], yCameraSins, yCameraCoss, temp_f22);
            if (gCurrentLevelModel->segments[segmentIds[i]].unk3C & 2) {
                func_80026070(bbox, yCameraSins, yCameraCoss, temp_f22);
            }
        }
    }

    func_80026C14(300, gCurrentLevelModel->lowerYBounds - 195, 1);
    func_80026C14(-300, gCurrentLevelModel->lowerYBounds - 195, 1);
    func_80026C14(300, gCurrentLevelModel->upperYBounds + 195, 0);
    func_80026C14(-300, gCurrentLevelModel->upperYBounds + 195, 0);

    if (D_8011D49E >= D_8011D4BA || D_8011D49E == 0) {
        return;
    }

    do {
        breakLoop = TRUE;
        ptr2 = (s32 *) D_8011D478;
        for (i = 0; i < D_8011D49E - 1; i++, ptr2 += 2) {
            if (D_8011D478[i + 1].unk0 < D_8011D478[i].unk0) {
                s32 tmp;

                tmp = ptr2[0];
                ptr2[0] = ptr2[2];
                ptr2[2] = tmp;

                tmp = ptr2[1];
                ptr2[1] = ptr2[3];
                ptr2[3] = tmp;

                breakLoop = FALSE;
            }
        }
    } while (!breakLoop);

    var_s0 = 0;

    for (i = 0; i < D_8011D49E; i++) {
        j = D_8011D478[i].unk7 * 2;
        if (D_8011D47C[j] == -1) {
            D_8011D478[i].unk6 |= 2;
            D_8011D47C[j] = i;
        } else {
            D_8011D47C[j + 1] = i;
        }
    }
    var_s4 = temp_s3 = D_8011D478[0].unk0;

    spAC = gSceneCurrVertexList;
    spA8 = gSceneCurrTriList;
    gSceneCurrVertexList = D_8011D480[D_8011D4B4];
    gSceneCurrTriList = D_8011D490[D_8011D4B4];

    D_8011D4B4 = 1 - D_8011D4B4;
    D_8011D488 = gSceneCurrVertexList;
    D_8011D498 = gSceneCurrTriList;
    D_8011D4B6.whole = 0;
    D_8011D4B8 = 0;

    i = 0;
    while (i < D_8011D49E) {
        while (i < D_8011D49E && var_s4 == D_8011D478[i].unk0) {
            if (D_8011D478[i].unk6 & 2) {
                sp7C[var_s0] = D_8011D478[i].unk7;
                var_s0++;
            } else {
                for (j = 0; j < var_s0; j++) {
                    if (sp7C[j] == D_8011D478[i].unk7) {
                        var_s0--;
                        while (j < var_s0) {
                            sp7C[j] = sp7C[j + 1];
                            j++;
                        }
                    }
                }
            }
            i++;
        }
        if (i < D_8011D49E) {
            temp_s3 = D_8011D478[i].unk0;
            if (var_s4 != temp_s3) {
                func_80026E54(var_s0, sp7C, temp_s3, var_s4);
                var_s4 = temp_s3;
            }
        }
    }
    if (D_8011D4B6.whole != 0) {
        gSPVertexDKR(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(D_8011D488), D_8011D4B6.whole, 0);
        gSPPolygon(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(D_8011D498), D_8011D4B6.whole >> 1, TRIN_DISABLE_TEXTURE);
    }
    gSceneCurrVertexList = spAC;
    gSceneCurrTriList = spA8;
}

void func_80026070(LevelModelSegmentBoundingBox *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp80[4];
    f32 sp70[4];
    f32 sp60[4];
    f32 temp;
    f32 sp54[2];
    f32 sp4C[2];
    s16 index;
    s16 nextIndex;
    s16 sp40[4];
    s16 var_t0;
    s16 temp2;

    sp80[0] = arg0->x1;
    sp70[0] = arg0->z1;
    sp80[1] = arg0->x2;
    sp70[1] = arg0->z1;
    sp80[2] = arg0->x2;
    sp70[2] = arg0->z2;
    sp80[3] = arg0->x1;
    sp70[3] = arg0->z2;

    temp2 = 0;
    for (index = 0; index < 4; index++) {
        sp60[index] = (arg1 * sp80[index]) + (sp70[index] * arg2) + arg3;
        sp40[index] = sp60[index] <= 0.0;
        temp2 += sp40[index];
    }
    if (temp2 != 0) {
        var_t0 = 0;
        if (temp2 == 4) {
            return;
        }
        for (index = 0; index < 4; index++) {
            nextIndex = index + 1;
            if (nextIndex >= 4) {
                nextIndex = 0;
            }
            if ((sp40[nextIndex] != sp40[index]) != 0U) {
                temp = sp60[index] / (sp60[index] - sp60[nextIndex]);
                sp54[var_t0] = sp80[index] + ((sp80[nextIndex] - sp80[index]) * temp);
                sp4C[var_t0] = sp70[index] + ((sp70[nextIndex] - sp70[index]) * temp);
                var_t0++;
            }
        }
        if (var_t0 != 2) {
            return;
        }

        sp60[0] = (D_8011D4A0 * sp54[0]) + (D_8011D4A4 * sp4C[0]) + D_8011D4A8;
        sp60[1] = (D_8011D4A0 * sp54[1]) + (D_8011D4A4 * sp4C[1]) + D_8011D4A8;

        if (sp60[1] < sp60[0]) {
            temp = sp60[0];
            sp60[0] = sp60[1];
            sp60[1] = temp;
        }

        // Returns must be on the same line.
        // clang-format off
        if (-300.0 > sp60[1]) { return; }
        if (sp60[0] > 300.0) { return; }
        // clang-format on

        if (sp60[0] < -300.0) {
            sp60[0] = -300.0f;
        }
        if (sp60[1] > 300.0) {
            sp60[1] = 300.0f;
        }
        func_80026C14(sp60[1], gCurrentLevelModel->lowerYBounds - 195, 0);
        func_80026C14(sp60[0], gCurrentLevelModel->lowerYBounds - 195, 0);
    }
}

void func_80026430(LevelModelSegment *segment, f32 arg1, f32 arg2, f32 arg3) {
    s16 i;
    s16 index;
    s16 verticesOffset;
    s16 nextFaceOffset;
    s16 nextIndex;
    s16 currFaceOffset;
    s16 j;
    Vertex *vert;
    s8 spF8[3];
    f32 temp;
    s16 var_s0;
    s16 var_t0;
#ifdef AVOID_UB
    f32 spE8[3]; // This really should be size of 3, but something is keeping it from matching that way.
#else
    f32 spE8[2];
#endif
    f32 spDC[3];
    f32 spD0[3];
    f32 spC4[3];
    f32 spB8[3];
    f32 spB0[2];
    f32 spA8[2];
    f32 spA0[2];

    if (D_8011D49E >= D_8011D4BA) {
        return;
    }

    for (i = 0; i < segment->numberOfBatches; i++) {
        currFaceOffset = segment->batches[i].facesOffset;
        verticesOffset = segment->batches[i].verticesOffset;
        nextFaceOffset = segment->batches[i + 1].facesOffset;
        if (segment->batches[i].flags & (BATCH_FLAGS_HIDDEN | BATCH_FLAGS_UNK00000200)) {
            currFaceOffset = nextFaceOffset;
        }
        for (j = currFaceOffset; j < nextFaceOffset; j++) {
            if ((segment->triangles[j].flags & BACKFACE_DRAW)) {
                continue;
            }
            var_t0 = 0;
            for (index = 0; index < 3; index++) {
                vert = &(segment->triangles[j].verticesArray[index + 1] + verticesOffset)[segment->vertices];
                spE8[index] = vert->x;
                spDC[index] = vert->y;
                spD0[index] = vert->z;
                spC4[index] = (arg1 * spE8[index]) + (arg2 * spD0[index]) + arg3;

                spF8[index] = (spC4[index] <= 0.0);
                var_t0 += (spF8[index] <= 0.0);
            }
            if ((var_t0 == 1) || (var_t0 == 2)) {
                for (var_s0 = 0, index = 0; index < 3; index++) {
                    nextIndex = index + 1;
                    if (nextIndex >= 3) {
                        nextIndex = 0;
                    }
                    if ((spF8[nextIndex] != spF8[index]) != 0) {
                        temp = spC4[index] / (spC4[index] - spC4[nextIndex]);
                        spB0[var_s0] = spE8[index] + ((spE8[nextIndex] - spE8[index]) * temp);
                        spB8[var_s0] = spDC[index] + ((spDC[nextIndex] - spDC[index]) * temp);
                        spA0[var_s0] = spB8[var_s0];
                        spA8[var_s0] = spD0[index] + ((spD0[nextIndex] - spD0[index]) * temp);
                        var_s0++;
                    }
                }

                var_s0 = 0;
                spF8[0] = 0;
                spF8[1] = 0;
                spC4[0] = (D_8011D4A0 * spB0[0]) + (D_8011D4A4 * spA8[0]) + D_8011D4A8;
                spC4[1] = (D_8011D4A0 * spB0[1]) + (D_8011D4A4 * spA8[1]) + D_8011D4A8;
                if (spC4[0] < -300.0) {
                    spF8[0] = 1;
                }
                if (spC4[0] > 300.0) {
                    spF8[0] |= 2;
                }
                if (spC4[1] < -300.0) {
                    spF8[1] = 1;
                }
                if (spC4[1] > 300.0) {
                    spF8[1] |= 2;
                }
                // clang-format off
                if ((spF8[0] | spF8[1]) == 0) {  var_s0 = 1; }
                // clang-format on
                else if ((spF8[1] != spF8[0]) != 0) {
                    index = 0;
                    if (spC4[1] < spC4[0]) {
                        index = 1;
                    }
                    nextIndex = 1 - index;
                    if (spF8[index] == 1) {
                        temp = ((-spC4[index] - 300.0) / (spC4[nextIndex] - spC4[index]));
                        spB8[index] = spB8[index] + ((spB8[nextIndex] - spB8[index]) * temp);
                        spC4[index] = -300.0f;
                    }
                    if (spF8[nextIndex] == 2) {
                        temp = ((spC4[nextIndex] - 300.0) / (spC4[nextIndex] - spC4[index]));
                        spB8[nextIndex] = spB8[nextIndex] + ((spB8[index] - spB8[nextIndex]) * temp);
                        spC4[nextIndex] = 300.0f;
                    }
                    var_s0 = 1;
                }
                if (var_s0 != 0) {
                    var_t0 = (segment->unk14[j].triangleIndex << 2);
                    temp = (spB0[0] + D_8011D4A0) * segment->unk18[var_t0];
                    temp += spB8[0] * segment->unk18[var_t0 + 1];
                    temp += (spA8[0] + D_8011D4A4) * segment->unk18[var_t0 + 2];
                    temp += segment->unk18[var_t0 + 3];
                    var_s0 = (temp > 0.0) << 2;
                    if (segment->unk18[var_t0 + 1] < 0.0f) {
                        var_s0 |= 1;
                    }
                    if (spC4[0] == spC4[1]) {
                        var_s0 |= 8;
                    }
                    func_80026C14(spC4[0], spB8[0], var_s0);
                    func_80026C14(spC4[1], spB8[1], var_s0);
                }
            }
        }
    }
}

void func_80026C14(s16 arg0, s16 arg1, s32 arg2) {
    s16 i;
    s16 j;

    if (D_8011D49E < D_8011D4BA) {
        i = 0;
        while (i < D_8011D49E && D_8011D478[i].unk0 < arg0) {
            i++;
        }
        while (i < D_8011D49E && arg0 == D_8011D478[i].unk0 && D_8011D478[i].unk2 < arg1) {
            i++;
        }
        j = D_8011D49E;
        while (i < j) {
            D_8011D478[j].unk0 = D_8011D478[j - 1].unk0;
            D_8011D478[j].unk2 = D_8011D478[j - 1].unk2;
            D_8011D478[j].unk7 = D_8011D478[j - 1].unk7;
            D_8011D478[j].unk6 = D_8011D478[j - 1].unk6;
            j--;
        }
        D_8011D478[i].unk0 = arg0;
        D_8011D478[i].unk2 = arg1;
        D_8011D478[i].unk4 = 0;
        D_8011D478[i].unk7 = D_8011D49C;
        D_8011D478[i].unk6 = arg2;
        D_8011D47C[D_8011D49E] = -1;
        if (D_8011D49E & 1) {
            D_8011D49C++;
        }
        D_8011D49E++;
    }
}

void func_80026E54(s16 arg0, s8 *arg1, f32 arg2, f32 arg3) {
    UNUSED s32 pad[7];
    unk8011D478 *next;
    unk8011D478 *curr;
    s16 temp3;
    s16 temp4;
    f32 diff_unk0;
    f32 curr_unk0;
    f32 curr_unk2;
    f32 next_unk0;
    f32 next_unk2;
    s32 noSwap;
    s16 i;
    s16 j;
    s8 temp;
    s8 temp0;
    s8 temp1;
    UNUSED f32 temp2;
    f32 sp94[10];
    f32 sp6C[10];
    s8 sp60[10];
    s8 swapByte;

    if (arg0 >= 10 || arg0 == 0) {
        return;
    }

    for (j = 0, i = 0; i < arg0;) {
        temp = arg1[i];
        curr = &D_8011D478[D_8011D47C[(s16) (temp * 2)]];
        next = &D_8011D478[D_8011D47C[((s16) (temp * 2)) + 1]];
        curr_unk0 = (f32) curr->unk0;
        curr_unk2 = (f32) curr->unk2;
        next_unk0 = (f32) next->unk0;
        next_unk2 = (f32) next->unk2;
        if (curr_unk0 == next_unk0) {
            return;
        }
        diff_unk0 = (curr_unk0 - next_unk0);
        sp94[j++] = ((next_unk2 - curr_unk2) * ((curr_unk0 - arg3) / diff_unk0)) + curr_unk2;
        sp6C[i] = sp94[j - 1];
        sp60[i] = i;
        sp94[j++] = ((curr_unk2 - next_unk2) * ((arg2 - next_unk0) / diff_unk0)) + next_unk2;
        sp6C[i] += sp94[j - 1];
        i++;
    }

    do {
        noSwap = TRUE;
        for (i = 0; i < arg0 - 1; i++) {
            if (sp6C[sp60[i + 1]] < sp6C[sp60[i]]) {
                swapByte = arg1[i];
                arg1[i] = arg1[i + 1];
                arg1[i + 1] = swapByte;
                swapByte = sp60[i];
                sp60[i] = sp60[i + 1];
                sp60[i + 1] = swapByte;
                noSwap = FALSE;
            }
        }
    } while (noSwap == FALSE);

    for (i = 0; i < arg0 - 1; i++) {
        temp0 = D_8011D478[D_8011D47C[arg1[i] * 2]].unk6 & 1;
        temp1 = D_8011D478[D_8011D47C[arg1[i + 1] * 2]].unk6 & 1;
        if (temp0 && !temp1) {
            temp3 = (sp60[i] * 2);
            temp4 = (sp60[i + 1] * 2);
            func_80027184(&sp94[temp3], &sp94[temp4], arg3, arg2);
        }
    }
}

s32 func_80027184(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3) {
    Vertex *verts;
    Triangle *tris;
    s32 triIndex;
    s16 vertZ1;
    s16 vertX2;
    s16 vertZ2;
    s16 vertX1;
    u8 colour_r;
    u8 colour_g;
    u8 colour_b;
    u8 colour_a;

    if (D_8011D4B8 >= D_8011D4BC) {
        return NULL;
    }

    if (D_8011D4B6.whole == 24) {
        gSPVertexDKR(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(D_8011D488), D_8011D4B6.whole, 0);
        gSPPolygon(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(D_8011D498), (D_8011D4B6.whole >> 1),
                   TRIN_DISABLE_TEXTURE);
        D_8011D488 = gSceneCurrVertexList;
        D_8011D4B6.whole = 0;
        D_8011D498 = gSceneCurrTriList;
    }

    vertX1 = arg2 * D_8011D4A0 + D_8011D4AC;
    vertZ1 = arg2 * D_8011D4A4 + D_8011D4B0;
    vertX2 = arg3 * D_8011D4A0 + D_8011D4AC;
    vertZ2 = arg3 * D_8011D4A4 + D_8011D4B0;

    colour_r = D_8011B0E1;
    colour_g = D_8011B0E2;
    colour_b = D_8011B0E3;
    colour_a = 0xFF;

    verts = gSceneCurrVertexList;
    verts[0].x = vertX1;
    verts[0].y = arg0[0] + 2.0f;
    verts[0].z = vertZ1;
    verts[0].r = colour_r;
    verts[0].g = colour_g;
    verts[0].b = colour_b;
    verts[0].a = colour_a;

    verts[1].x = vertX2;
    verts[1].y = arg0[1] + 2.0f;
    verts[1].z = vertZ2;
    verts[1].r = colour_r;
    verts[1].g = colour_g;
    verts[1].b = colour_b;
    verts[1].a = colour_a;

    verts[2].x = vertX1;
    verts[2].y = arg1[0] - 2.0f;
    verts[2].z = vertZ1;
    verts[2].r = colour_r;
    verts[2].g = colour_g;
    verts[2].b = colour_b;
    verts[2].a = colour_a;

    verts[3].x = vertX2;
    verts[3].y = arg1[1] - 2.0f;
    verts[3].z = vertZ2;
    verts[3].r = colour_r;
    verts[3].g = colour_g;
    verts[3].b = colour_b;
    verts[3].a = colour_a;
    // @fake
    if (1) {}
    verts += 4;
    gSceneCurrVertexList = verts;

    tris = gSceneCurrTriList;
    triIndex = D_8011D4B6.two;

    // @fake, using index 0 directly doesn't match
    vertX2 = 0;
    tris[vertX2].flags = BACKFACE_DRAW;
    tris[vertX2].vi0 = triIndex + 2;
    tris[vertX2].vi1 = triIndex + 1;
    tris[vertX2].vi2 = triIndex;
    tris[vertX2].uv0.u = 0x3E0;
    tris[vertX2].uv0.v = 0x3E0;
    tris[vertX2].uv1.u = 0x3E0;
    tris[vertX2].uv1.v = 0;
    tris[vertX2].uv2.u = 1;
    tris[vertX2].uv2.v = 0;

    tris[1].flags = BACKFACE_DRAW;
    tris[1].vi0 = triIndex + 3;
    tris[1].vi1 = triIndex + 1;
    tris[1].vi2 = triIndex + 2;
    tris[1].uv0.u = 1;
    tris[1].uv0.v = 0x3E0;
    tris[1].uv1.u = 0x3E0;
    tris[1].uv1.v = 0x3E0;
    tris[1].uv2.u = 1;
    tris[1].uv2.v = 0;
    tris += 2;
    gSceneCurrTriList = tris;

    D_8011D4B6.whole += 4;
    D_8011D4B8++;
    return NULL;
}

#ifdef NON_EQUIVALENT
typedef struct Unk80027568_2 {
    s32 unk0;
    u16 unk4;
} Unk80027568_2;

typedef struct Unk80027568_1 {
    u8 unk0[0x18];
    Vec4f *unk18;
} Unk80027568_1;

s32 func_80027568(void) {
    f32 projectedRacerPos;
    f32 projectedCamPos;
    f32 temp_f18_2;
    f32 var_f16;
    f32 scalingFactor;
    s32 curViewport;
    s32 isNegative;
    s32 var_a1;
    s32 ret;
    s32 var_t4;
    s32 i;
    u16 *var_v0_1;
    u16 var_v0;
    Vec4f *vector;
    Object **racerGroup;
    s32 numRacers;
    Unk80027568_1 *var_ra; // spE4
    Object *currentObjRacer;
    f32 x, y, z;

    racerGroup = get_racer_objects(&numRacers);
    if (numRacers == 0) {
        return FALSE;
    }
    if ((check_if_showing_cutscene_camera() != 0) || (gSceneActiveCamera->object.unk36 >= 5) ||
        (gSceneActiveCamera->object.unk36 == 3)) {
        return FALSE;
    }
    curViewport = get_current_viewport();
    currentObjRacer = NULL;
    for (i = 0; i < numRacers; i++) {
        Object_Racer *racer = &racerGroup[i]->unk64->racer;
        if (curViewport == racer->playerIndex) {
            currentObjRacer = racerGroup[i];
            i = numRacers; // Come on! Just use break!
        }
    }
    if (currentObjRacer == NULL) {
        return FALSE;
    }
    func_80031130(1, &currentObjRacer->segment.trans.x_position, &gSceneActiveCamera->trans.x_position, -1);
    ret = FALSE;
    // bug? var_ra can be undefined?
    for (var_t4 = 0; var_t4 < D_8011D378 && ret == FALSE; var_t4++) {
        if ((s32) D_8011D370[var_t4] > 0) {
            var_ra = (void *) PHYS_TO_K0(D_8011D370[var_t4]);
        } else {
            vector = &var_ra->unk18[D_8011D370[var_t4][0]];
            projectedCamPos = vector->x * gSceneActiveCamera->trans.x_position +
                              vector->y * gSceneActiveCamera->trans.y_position +
                              vector->z * gSceneActiveCamera->trans.z_position + vector->w - 14.0;
            if (projectedCamPos < -0.1) {
                projectedRacerPos = vector->x * currentObjRacer->segment.trans.x_position +
                                    vector->y * currentObjRacer->segment.trans.y_position +
                                    vector->z * currentObjRacer->segment.trans.z_position + vector->w;
                if (projectedRacerPos >= -0.1) {
                    ret = TRUE;

                    if (projectedRacerPos != projectedCamPos) {
                        scalingFactor = projectedRacerPos / (projectedRacerPos - projectedCamPos);
                    } else {
                        scalingFactor = 0.0f;
                    }
                    for (var_a1 = 0; var_a1 < 3 && ret == TRUE; var_a1++) {
                        var_v0 = D_8011D370[var_t4][var_a1 + 1];
                        isNegative = FALSE;
                        if (var_v0 & 0x8000) {
                            var_v0 &= 0x7FFF;
                            isNegative = TRUE;
                        }
                        vector = &var_ra->unk18[var_v0];
                        var_f16 =
                            vector->x *
                                (currentObjRacer->segment.trans.x_position +
                                 (gSceneActiveCamera->trans.x_position - currentObjRacer->segment.trans.x_position) *
                                     scalingFactor) +
                            vector->y *
                                (currentObjRacer->segment.trans.y_position +
                                 (gSceneActiveCamera->trans.y_position - currentObjRacer->segment.trans.y_position) *
                                     scalingFactor) +
                            vector->z *
                                (currentObjRacer->segment.trans.z_position +
                                 (gSceneActiveCamera->trans.z_position - currentObjRacer->segment.trans.z_position) *
                                     scalingFactor) +
                            vector->w;
                        if (isNegative) {
                            var_f16 = -var_f16;
                        }
                        if (var_f16 > 4.0f) {
                            ret = FALSE;
                        }
                    }
                }
            }
        }
    }
    return ret;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/tracks/func_80027568.s")
#endif

void func_800278E8(s32 updateRate) {
    s16 angleDiff;
    f32 xDelta;
    f32 yDelta;
    f32 zDelta;
    f32 xzSqr;
    ObjectSegment *segment;
    Object *thisObject;
    Object **racerGroup;
    Object *lastObject;
    Object *objectFirstPlace;
    Object_Racer *currentRacer;
    Object_Racer *lastRacer;
    Object_Racer *racerFirstPlace;
    s32 numRacers;
    s32 i;
    s32 cameraId;
    Object *camera;

    racerGroup = get_racer_objects(&numRacers);
    lastRacer = NULL;
    for (i = 0; i < numRacers; i++) {
        if (1) {} // fake
        if (racerGroup[i] != NULL) {
            currentRacer = &racerGroup[i]->unk64->racer;
            cameraId = currentRacer->cameraIndex;
            spectate_nearest(racerGroup[i], &cameraId);
            currentRacer->cameraIndex = cameraId;
            if (currentRacer->raceFinished) {
                if (currentRacer->finishPosition == 1) {
                    racerFirstPlace = currentRacer;
                    objectFirstPlace = racerGroup[i];
                }
            } else if (lastRacer == NULL) {
                lastRacer = currentRacer;
                lastObject = racerGroup[i];
            } else if (currentRacer->racePosition < lastRacer->racePosition) {
                lastRacer = currentRacer;
                lastObject = racerGroup[i];
            }
        }
    }
    if (lastRacer != NULL) {
        currentRacer = lastRacer;
        thisObject = lastObject;
    } else {
        currentRacer = racerFirstPlace;
        thisObject = objectFirstPlace;
    }
    camera = spectate_object(currentRacer->cameraIndex);
    if (D_8011B104 != currentRacer->cameraIndex) {
        D_8011B108 = 0;
    } else if (D_8011B100 != currentRacer->playerIndex) {
        D_8011B108 = 180;
        D_8011B100 = currentRacer->playerIndex;
    }
    if (camera != NULL) {
        segment = get_active_camera_segment_no_cutscenes();
        segment->trans.x_position = camera->segment.trans.x_position;
        segment->trans.y_position = camera->segment.trans.y_position;
        segment->trans.z_position = camera->segment.trans.z_position;
        xDelta = segment->trans.x_position - thisObject->segment.trans.x_position;
        yDelta = segment->trans.y_position - thisObject->segment.trans.y_position;
        zDelta = segment->trans.z_position - thisObject->segment.trans.z_position;
        xzSqr = sqrtf((xDelta * xDelta) + (zDelta * zDelta));
        if (D_8011B108 != 0) {
            angleDiff = ((s32) (-atan2s(xDelta, zDelta) - segment->trans.rotation.y_rotation) + 0x8000);
            //!@bug Never true, since angleDiff is signed. Should be >=.
            if (angleDiff > 0x8000) {
                angleDiff = -(0xFFFF - angleDiff);
            }
            segment->trans.rotation.y_rotation += ((s32) (angleDiff / (16.0f * (D_8011B108 / 180.0f)))) & 0xFFFF;
            angleDiff = atan2s(yDelta, xzSqr) - segment->trans.rotation.x_rotation;
            //!@bug Never true, since angleDiff is signed. Should be >=.
            if (angleDiff > 0x8000) {
                angleDiff = -(0xFFFF - angleDiff);
            }
            segment->trans.rotation.x_rotation += ((s32) (angleDiff / (16.0f * (D_8011B108 / 180.0f)))) & 0xFFFF;
            D_8011B108 -= updateRate;
            if (D_8011B108 < 0) {
                D_8011B108 = 0;
            }
        } else {
            segment->trans.rotation.y_rotation = 0x8000 - atan2s(xDelta, zDelta);
            segment->trans.rotation.x_rotation = atan2s(yDelta, xzSqr);
        }
        segment->trans.rotation.z_rotation = 0;
        segment->object.cameraSegmentID = get_level_segment_index_from_position(
            segment->trans.x_position, currentRacer->oy1, segment->trans.z_position);
        D_8011B104 = currentRacer->cameraIndex;
    }
}

/**
 * Handle the flipbook effect for level geometry textures.
 */
void animate_level_textures(s32 updateRate) {
    s32 segmentNumber, batchNumber;
    LevelModelSegment *segment;
    TextureHeader *texture;
    TriangleBatchInfo *batch;
    s32 temp;

    segment = gCurrentLevelModel->segments;
    for (segmentNumber = 0; segmentNumber < gCurrentLevelModel->numberOfSegments; segmentNumber++) {
        batch = segment[segmentNumber].batches;
        for (batchNumber = 0; batchNumber < segment[segmentNumber].numberOfBatches; batchNumber++) {
            if (batch[batchNumber].flags & BATCH_FLAGS_TEXTURE_ANIM) {
                if (batch[batchNumber].textureIndex != 0xFF) {
                    texture = gCurrentLevelModel->textures[batch[batchNumber].textureIndex].texture;
                    if (texture->numOfTextures != 0x100 && texture->frameAdvanceDelay) {
                        temp = batch[batchNumber].unk7 << 6;
                        if (batch[batchNumber].flags & BATCH_FLAGS_UNK80000000) {
                            temp |= batch[batchNumber].unk6;
                            tex_animate_texture(texture, &batch[batchNumber].flags, &temp, updateRate);
                            batch[batchNumber].unk6 = temp & 0x3F;
                        } else {
                            tex_animate_texture(texture, &batch[batchNumber].flags, &temp, updateRate);
                        }
                        batch[batchNumber].unk7 = (temp >> 6) & 0xFF;
                    }
                }
            }
        }
    }
}

/**
 * Spawns and initialises the skydome object seen ingame.
 * Skipped if the object ID doesn't exist.
 * Also compares a checksum which can potentially trigger anti-tamper measures.
 */
void spawn_skydome(s32 objectID) {
    LevelObjectEntryCommon spawnObject;

#ifdef ANTI_TAMPER
    // Antipiracy measure
    drm_checksum_balloon();
#endif
    if (objectID == -1) {
        gSkydomeSegment = NULL;
        return;
    }
    spawnObject.x = 0;
    spawnObject.y = 0;
    spawnObject.z = 0;
    spawnObject.size = sizeof(LevelObjectEntryCommon);
    spawnObject.objectID = objectID;
    gSkydomeSegment = spawn_object(&spawnObject, 2);
    if (gSkydomeSegment != NULL) {
        gSkydomeSegment->segment.level_entry = NULL;
        gSkydomeSegment->objectID = -1;
    }
}

/**
 * Sets the status to render the sky.
 * If set to false, will skip the background and skydome rendering.
 */
void set_skydome_visbility(s32 renderSky) {
    gSceneRenderSkyDome = renderSky;
}

#ifdef NON_MATCHING
// This function creates the flashy sky effect in the wizpig 2 race.
// init_skydome
// https://decomp.me/scratch/E1DFy
void func_80028050(void) {
    Triangle *tris;
    Vertex *verts;
    s32 vCoordMask; // sp14C
    s32 uCoordMask;
    f32 scaledXSin;
    f32 scaledXCos;
    f32 var_f16;
    s16 uCoords[9]; // sp128
    s16 vCoords[9]; // sp114
    f32 xCos;
    f32 xSin; // sp10C
    f32 pad_sp108;
    ObjectSegment* objSegment;
    f32 pad_sp100;
    f32 xPositions[9]; // spDC
    f32 zPositions[9]; // spB8
    Vec3f pos;
    s32 i;
    s32 var_v0;
    s32 var_v1;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    u8* var_v0_3;
    f32 var_f14;
    s16 vertY;
    s16 vTempCoord;
    s16 uTempCoord;
    LevelHeader_70* levelHeader;
    LevelHeader_70* var_t2; // sp7C
    LevelHeader_70* sp78;
    TextureHeader* texHeader; // sp74
    s32 pad[4];

    verts = gSceneCurrVertexList;
    tris = gSceneCurrTriList;

    objSegment = get_active_camera_segment();
    texHeader = gCurrentLevelHeader2->unkA4;
    uCoordMask = (texHeader->width << 5) - 1;
    vCoordMask = (texHeader->height << 5) - 1;
    xSin = sins_f(-objSegment->trans.rotation.x);
    xCos = coss_f(-objSegment->trans.rotation.x);

    scaledXSin = xSin * 1280.0f;
    scaledXCos = xCos * 1280.0f;
    xPositions[0] = -scaledXCos - (xSin * 1280.0f);
    zPositions[0] = -scaledXCos + (xSin * 1280.0f);
    xPositions[1] = scaledXCos - (xSin * 1280.0f);
    zPositions[1] = -scaledXCos - (xSin * 1280.0f);
    xPositions[2] = scaledXCos + (xSin * 1280.0f);
    zPositions[2] = scaledXCos - (xSin * 1280.0f);
    xPositions[3] = -scaledXCos + (xSin * 1280.0f);
    zPositions[3] = scaledXCos + scaledXSin;
    xPositions[4] = 0.0f;
    zPositions[4] = 0.0f;

    zPositions[5] = scaledXSin - (2.0f * scaledXCos);
    xPositions[6] = scaledXCos - (2.0f * scaledXSin);
    zPositions[6] = -(2.0f * scaledXCos) - scaledXSin;
    xPositions[5] = -scaledXCos - (2.0f * scaledXSin);
    xPositions[7] = scaledXCos + (2.0f * scaledXSin);
    zPositions[7] = (2.0f * scaledXCos) - scaledXSin;
    xPositions[8] = -scaledXCos + (2.0f * scaledXSin);
    zPositions[8] = (2.0f * scaledXCos) + scaledXSin;

    var_f14 = 1280.0f;
    var_f14 *= 0.25f;

    var_a1 = texHeader->width * 16 * gCurrentLevelHeader2->unkA0;
    var_a2 = texHeader->height * 16 * gCurrentLevelHeader2->unkA1;

    var_v0 = ((s32) (objSegment->trans.x_position * (var_f14 / var_a1)) + (gCurrentLevelHeader2->unkA8 >> 4)) & uCoordMask;
    var_v1 = ((s32) (objSegment->trans.z_position * (var_f14 / var_a2)) + (gCurrentLevelHeader2->unkAA >> 4)) & vCoordMask;

    var_f14 = var_a1 * xCos;
    pos.z = var_a1 * xCos;
    pos.x = var_a1 * xCos;
    var_f16 = var_a2 * xSin;
    xCos = var_f16;

    // @fake
    var_a2 = texHeader->height * 16 * gCurrentLevelHeader2->unkA1;

    uCoords[0] = (s16) (-var_f14 - xCos) + var_v0;
    vCoords[0] = (s16) (var_f16 - var_f14) + var_v1;
    uCoords[1] = (s16) (var_f14 - xCos) + var_v0;
    vCoords[1] = (s16) (-var_f14 - var_f16) + var_v1;
    uCoords[2] = (s16) (var_f14 + var_f16) + var_v0;
    vCoords[2] = (s16) (var_f14 - var_f16) + var_v1;
    uCoords[3] = (s16) (var_f16 - var_f14) + var_v0;
    vCoords[3] = (s16) (var_f14 + var_f16) + var_v1;

    uCoords[4] = var_v0;
    vCoords[4] = var_v1;

    uCoords[5] = (s16) (-var_f14 - (2.0f * xCos)) + var_v0;
    vCoords[5] = (s16) (var_f16 - (2.0f * var_f14)) + var_v1;
    uCoords[6] = (s16) (var_f14 - (2.0f * xCos)) + var_v0;
    vCoords[6] = (s16) ((-(2.0f * var_f14)) - var_f16) + var_v1;
    uCoords[7] = (s16) ((2.0f * xCos) + pos.z) + var_v0;
    vCoords[7] = (s16) ((2.0f * pos.x) - var_f16) + var_v1;
    uCoords[8] = (s16) ((2.0f * xCos) - pos.z) + var_v0;
    vCoords[8] = (s16) ((2.0f * pos.x) + var_f16) + var_v1;

    matrix_world_origin(&gSceneCurrDisplayList, &gSceneCurrMatrix);

    var_t2 = *gCurrentLevelHeader2->unk74;
    var_a2 = -1;

    if ((u32)var_t2 != -1) {
        levelHeader = gCurrentLevelHeader2->unk74[1];
        if ((u32)levelHeader == -1) {
            levelHeader = var_t2;
        }
    } else {
        levelHeader = sp78; // @bug? sp78 is never set
        var_t2 = NULL;
    }

    var_a3 = -0x100;
    if (var_t2 != NULL) {
        var_a2 = var_t2->rgba.word;
        var_a3 = levelHeader->rgba.word & (~0xFF);
    }

    gfx_init_basic_xlu(&gSceneCurrDisplayList, 1, var_a2, var_a3);
    texHeader = set_animated_texture_header(texHeader, D_8011B110 << 8);
    gDkrDmaDisplayList(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(texHeader->cmd), texHeader->numberOfCommands);
    gSPVertexDKR(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(gSceneCurrVertexList), 9, 0);
    gSPPolygon(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(gSceneCurrTriList), 8, 1);
    gDPPipeSync(gSceneCurrDisplayList++);
    if (var_t2 != NULL) {
        gDPSetPrimColor(gSceneCurrDisplayList++, 0, 0, 255, 255, 255, 255);
        gDPSetEnvColor(gSceneCurrDisplayList++, 255, 255, 255, 0);
    }
    rendermode_reset(&gSceneCurrDisplayList);

    vertY = objSegment->trans.y_position + 192.0f;
    for (i = 0; i < 9; i++) {
        verts->x = xPositions[i] + objSegment->trans.x_position;
        verts->y = vertY;
        verts->z = zPositions[i] + objSegment->trans.z_position;
        verts->r = 0xFF;
        verts->g = 0xFF;
        verts->b = 0xFF;
        verts->a = (i <= 4) ? (255) : (0);
        verts++;
    }

    var_v0_3 = D_800DC92C;
    for (i = 0; i < 8; i++) {
        tris->flags = 0x40;
        tris->vi0 = *var_v0_3;
        tris->uv0.u = uCoords[*var_v0_3];
        tris->uv0.v = vCoords[*var_v0_3];
        var_v0_3 += 1;
        tris->vi1 = *var_v0_3;
        tris->uv1.u = uCoords[*var_v0_3];
        tris->uv1.v = vCoords[*var_v0_3];
        var_v0_3 += 1;
        tris->vi2 = *var_v0_3;
        tris->uv2.u = uCoords[*var_v0_3];
        tris->uv2.v = vCoords[*var_v0_3];
        var_v0_3 += 1;
        tris++;
    }

    gSceneCurrVertexList = verts;
    gSceneCurrTriList = tris;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/tracks/func_80028050.s")
#endif

/**
 * Instead of drawing the skydome with textures, draw a solid coloured background.
 * Using different colours set in the level header, the vertices are coloured and
 * it gives the background a gradient effect.
 */
void draw_gradient_background(void) {
    s16 z;
    UNUSED s16 pad;
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

    verts = (Vertex *) gSceneCurrVertexList;
    tris = (Triangle *) gSceneCurrTriList;

    headerRed0 = gCurrentLevelHeader2->BGColourTopR;
    headerGreen0 = gCurrentLevelHeader2->BGColourTopG;
    headerBlue0 = gCurrentLevelHeader2->BGColourTopB;
    headerRed1 = gCurrentLevelHeader2->BGColourBottomR;
    headerGreen1 = gCurrentLevelHeader2->BGColourBottomG;
    headerBlue1 = gCurrentLevelHeader2->BGColourBottomB;
    rendermode_reset(&gSceneCurrDisplayList);
    material_set_no_tex_offset(&gSceneCurrDisplayList, 0, RENDER_FOG_ACTIVE);
    gSPVertexDKR(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(verts), 4, 0);
    gSPPolygon(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(tris), 2, 0);

    z = 20;
    if (osTvType == OS_TV_TYPE_PAL) {
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
    verts->x = -200;
    verts->y = y0;
    verts->z = z;
    verts->r = headerRed0;
    verts->g = headerGreen0;
    verts->b = headerBlue0;
    verts->a = 255;
    verts++;

    verts->x = 200;
    verts->y = y0;
    verts->z = z;
    verts->r = headerRed0;
    verts->g = headerGreen0;
    verts->b = headerBlue0;
    verts->a = 255;
    verts++;

    verts->x = -200;
    verts->y = y1;
    verts->z = z;
    verts->r = headerRed1;
    verts->g = headerGreen1;
    verts->b = headerBlue1;
    verts->a = 255;
    verts++;

    verts->x = 200;
    verts->y = y1;
    verts->z = z;
    verts->r = headerRed1;
    verts->g = headerGreen1;
    verts->b = headerBlue1;
    verts->a = 255;
    verts++;

    tris->flags = BACKFACE_DRAW;
    tris->vi0 = 2;
    tris->vi1 = 1;
    tris->vi2 = 0;
    tris->uv0.u = 0;
    tris->uv0.v = 0;
    tris->uv1.u = 0;
    tris->uv1.v = 0;
    tris->uv2.u = 0;
    tris->uv2.v = 0;
    tris++;

    tris->flags = BACKFACE_DRAW;
    tris->vi0 = 3;
    tris->vi1 = 2;
    tris->vi2 = 1;
    tris->uv0.u = 0;
    tris->uv0.v = 0;
    tris->uv1.u = 0;
    tris->uv1.v = 0;
    tris->uv2.u = 0;
    tris->uv2.v = 0;
    tris++;

    gSceneCurrVertexList = verts;
    gSceneCurrTriList = tris;
}

/**
 * Sets the position to the current camera's position then renders the skydome if set to be visible.
 */
void render_skydome(void) {
    ObjectSegment *cam;
    if (gSkydomeSegment == NULL) {
        return;
    }

    cam = get_active_camera_segment();
    if (gCurrentLevelHeader2->skyDome == 0) {
        gSkydomeSegment->segment.trans.x_position = cam->trans.x_position;
        gSkydomeSegment->segment.trans.y_position = cam->trans.y_position;
        gSkydomeSegment->segment.trans.z_position = cam->trans.z_position;
    }

    matrix_world_origin(&gSceneCurrDisplayList, &gSceneCurrMatrix);
    if (gSceneRenderSkyDome) {
        render_object(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, gSkydomeSegment);
    }
}

/**
 * Sets up all of the required variables for the player's view perspective.
 * This includes setting up the camera index, viewport and
 */
void initialise_player_viewport_vars(s32 updateRate) {
    s32 i;
    s32 numRacers;
    s32 viewportID;
    Object **racers;
    s32 segmentIndex;
    Object_Racer *racer;

    gSceneActiveCamera = get_active_camera_segment();
    viewportID = get_current_viewport();
    compute_scene_camera_transform_matrix();
    update_envmap_position(gScenePerspectivePos.x / 65536.0f, gScenePerspectivePos.y / 65536.0f,
                           gScenePerspectivePos.z / 65536.0f);
    segmentIndex = gSceneActiveCamera->object.cameraSegmentID;
    if (segmentIndex > -1 && (segmentIndex < gCurrentLevelModel->numberOfSegments)) {
        gSceneStartSegment = gCurrentLevelModel->segments[segmentIndex].unk28;
    } else {
        gSceneStartSegment = -1;
    }
    gPrevCameraX = gSceneActiveCamera->trans.x_position;
    gPrevCameraY = gSceneActiveCamera->trans.y_position;
    gPrevCameraZ = gSceneActiveCamera->trans.z_position;
    if (gWaveBlockCount != 0) {
        func_800B8B8C();
        racers = get_racer_objects(&numRacers);
        if (gSceneActiveCamera->object.unk36 != 7 && numRacers > 0 && !check_if_showing_cutscene_camera()) {
            i = -1;
            do {
                i++;
                racer = &racers[i]->unk64->racer;
            } while (i < numRacers - 1 && viewportID != racer->playerIndex);
            func_800B8C04(racers[i]->segment.trans.x_position, racers[i]->segment.trans.y_position,
                          racers[i]->segment.trans.z_position, get_current_viewport(), updateRate);
        } else {
            func_800B8C04(gSceneActiveCamera->trans.x_position, gSceneActiveCamera->trans.y_position,
                          gSceneActiveCamera->trans.z_position, get_current_viewport(), updateRate);
        }
    }
    get_current_level_header()->unk3 = 1;
    render_level_geometry_and_objects();
}

/**
 * Enable or disable anti aliasing.
 * Improves visual quality at the cost of performance.
 */
void set_anti_aliasing(s32 setting) {
    gAntiAliasing = setting;
}

/**
 * Find which segments can and should be rendered, then render their opaque geometry.
 * Render all objects inside visible segments then render the level's semitransparent geometry.
 * Afterwards, render particles.
 */
void render_level_geometry_and_objects(void) {
    s32 objCount;
    s32 numberOfSegments;
    s32 objFlags;
    s32 sp160;
    s32 i;
    s32 visibleFlags;
    u8 segmentIds[LEVEL_SEGMENT_MAX];
    u8 objectsVisible[LEVEL_SEGMENT_MAX];
    s32 visible;
    Object *obj;

    func_80012C30();

    if (get_settings()->courseId == ASSET_LEVEL_OPENINGSEQUENCE) {
        gAntiAliasing = TRUE;
    }

    sp160 = get_first_active_object(&objCount);

    if (gCurrentLevelModel->numberOfSegments > 1) {
        numberOfSegments = 0;
        traverse_segments_bsp_tree(0, 0, gCurrentLevelModel->numberOfSegments - 1, segmentIds, &numberOfSegments);
    } else {
        numberOfSegments = 1;
        segmentIds[0] = 0;
    }

    for (i = 1; i <= gCurrentLevelModel->numberOfSegments; i++) {
        objectsVisible[i] = FALSE; // why not a bzero?
    }

    objectsVisible[0] = TRUE;

    if (gDrawLevelSegments) {
        for (i = 0; i < numberOfSegments; i++) {
            render_level_segment(segmentIds[i], FALSE); // Render opaque segments
            objectsVisible[segmentIds[i] + 1] = TRUE;
        }
    }

    if (gCurrentLevelModel->numberOfSegments < 2) {
        objectsVisible[1] = TRUE;
    }

    rendermode_reset(&gSceneCurrDisplayList);
    sort_objects_by_dist(sp160, objCount - 1);
    visibleFlags = OBJ_FLAGS_INVIS_PLAYER1 << (get_current_viewport() & 1);

    for (i = sp160; i < objCount; i++) {
        obj = get_object(i);
        visible = 255;
        objFlags = obj->segment.trans.flags;
        if (objFlags & OBJ_FLAGS_UNK_0080) {
            visible = 0;
        } else if (!(objFlags & OBJ_FLAGS_PARTICLE)) {
            visible = obj->segment.object.opacity;
        }
        if (objFlags & visibleFlags) {
            visible = 0;
        }
        if (obj != NULL && visible == 255 && check_if_in_draw_range(obj) &&
            (objectsVisible[obj->segment.object.segmentID + 1] || obj->segment.camera.unk34 > 1000.0)) {
            if (obj->segment.trans.flags & OBJ_FLAGS_PARTICLE) {
                render_object(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, obj);
                continue;
            } else if (obj->shadow != NULL) {
                shadow_render(obj, obj->shadow);
            }
            render_object(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, obj);
            if (obj->waterEffect != NULL && obj->segment.header->flags & HEADER_FLAGS_WATER_EFFECT) {
                watereffect_render(obj, obj->waterEffect);
            }
        }
    }

    for (i = objCount - 1; i >= sp160; i--) {
        obj = get_object(i);
        objFlags = obj->segment.trans.flags;
        if (objFlags & visibleFlags) {
            visible = FALSE;
        } else {
            visible = TRUE;
        }
        if (obj != NULL && visible && objFlags & OBJ_FLAGS_UNK_0100 &&
            objectsVisible[obj->segment.object.segmentID + 1] && check_if_in_draw_range(obj)) {
            if (obj->segment.trans.flags & OBJ_FLAGS_PARTICLE) {
                render_object(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, obj);
                continue;
            } else if (obj->shadow != NULL) {
                shadow_render(obj, obj->shadow);
            }
            render_object(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, obj);
            if (obj->waterEffect != NULL && obj->segment.header->flags & HEADER_FLAGS_WATER_EFFECT) {
                watereffect_render(obj, obj->waterEffect);
            }
        }
    }

    if (gDrawLevelSegments) {
        for (i = numberOfSegments - 1; i >= 0; i--) {
            render_level_segment(segmentIds[i], TRUE); // Render transparent segments
        }
    }

    if (gWaveBlockCount != 0) {
        func_800BA8E4(&gSceneCurrDisplayList, &gSceneCurrMatrix, get_current_viewport());
    }

    rendermode_reset(&gSceneCurrDisplayList);
    material_set_no_tex_offset(&gSceneCurrDisplayList, 0, RENDER_FOG_ACTIVE | RENDER_Z_COMPARE);
    func_80012C3C(&gSceneCurrDisplayList);

    // Particles and FX
    for (i = objCount - 1; i >= sp160; i--) {
        obj = get_object(i);
        visible = 255;
        objFlags = obj->segment.trans.flags;
        if (objFlags & OBJ_FLAGS_UNK_0080) {
            visible = 1;
        } else if (!(objFlags & OBJ_FLAGS_PARTICLE)) {
            visible = obj->segment.object.opacity;
        }
        if (objFlags & visibleFlags) {
            visible = 0;
        }
        if (obj->behaviorId == BHV_RACER && visible >= 255) {
            visible = 0;
        }
        if (obj != NULL && visible < 255 && objectsVisible[obj->segment.object.segmentID + 1] &&
            check_if_in_draw_range(obj)) {
            if (visible > 0) {
                if (obj->segment.trans.flags & OBJ_FLAGS_PARTICLE) {
                    render_object(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, obj);
                    goto skip;
                } else if (obj->shadow != NULL) {
                    shadow_render(obj, obj->shadow);
                }
                render_object(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, obj);
                if ((obj->waterEffect != 0) && (obj->segment.header->flags & 0x10)) {
                    watereffect_render(obj, obj->waterEffect);
                }
            }
        skip:
            if (obj->behaviorId == BHV_RACER) {
                render_racer_shield(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, obj);
                render_racer_magnet(&gSceneCurrDisplayList, &gSceneCurrMatrix, &gSceneCurrVertexList, obj);
            }
        }
    }

    if (D_800DC924 != NULL && func_80027568()) {
        func_8002581C(segmentIds, numberOfSegments, get_current_viewport());
    }
    gAntiAliasing = FALSE;
}

/**
 * Render a batch of level geometry.
 * Since opaque and transparent are done in two separate runs, it will skip over the other.
 * Has a special case for the flashing lights in Spaceport Alpha, too.
 */
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
    s32 isInvisible;
    s32 levelHeaderIndex;
    s32 texOffset;
    s32 sp78;
    s32 startPos;
    s32 endPos;
    s32 batchFlags;
    s32 textureFlags;
    //! @bug: batchInfo is uninitalized
    numberVertices = (batchInfo + 1)->verticesOffset - batchInfo->verticesOffset;
    segment = &gCurrentLevelModel->segments[segmentId];
    sp78 = (nonOpaque && gWaveBlockCount) ? func_800B9228(segment) : 0;
    if (nonOpaque) {
        startPos = segment->numberofOpaqueBatches;
        endPos = segment->numberOfBatches;
    } else {
        startPos = 0;
        endPos = segment->numberofOpaqueBatches;
    }
    for (i = startPos; i < endPos; i++) {
        batchInfo = &segment->batches[i];
        textureFlags = RENDER_NONE;
        isInvisible = batchInfo->flags & BATCH_FLAGS_HIDDEN;
        if (isInvisible) {
            continue;
        }
        batchFlags = batchInfo->flags;
        renderBatch = 0;
        if (batchInfo->textureIndex == 0xFF) {
            texture = FALSE;
        } else {
            texture = gCurrentLevelModel->textures[batchInfo->textureIndex].texture;
            textureFlags = texture->flags;
        }
        batchFlags |= BATCH_FLAGS_UNK00000008 | BATCH_FLAGS_UNK00000002;
        if (!(batchFlags & BATCH_FLAGS_DEPTH_WRITE) && !(batchFlags & BATCH_FLAGS_RECEIVE_SHADOWS)) {
            batchFlags |= gAntiAliasing;
        }
        if ((!(textureFlags & RENDER_SEMI_TRANSPARENT) && !(batchFlags & BATCH_FLAGS_WATER)) ||
            batchFlags & BATCH_FLAGS_RECEIVE_SHADOWS) {
            renderBatch = TRUE;
        }
        if (nonOpaque) {
            renderBatch = (renderBatch + 1) & 1;
        }
        if (sp78 && batchFlags & BATCH_FLAGS_WATER) {
            renderBatch = FALSE;
        }
        if (!renderBatch) {
            continue;
        }
        numberTriangles = batchInfo->facesOffset;
        do { // Fakematch
            numberVertices = (batchInfo + 1)->verticesOffset - batchInfo->verticesOffset;
            numberTriangles = (batchInfo + 1)->facesOffset - numberTriangles;
            vertices = (s32) &segment->vertices[batchInfo->verticesOffset];
        } while (0);
        triangles = (s32) &segment->triangles[batchInfo->facesOffset];
        texOffset = batchInfo->unk7 << 14;
        levelHeaderIndex = (batchFlags >> 28) & 7;
        if (levelHeaderIndex != (batchInfo->verticesOffset * 0)) {
            gDPSetEnvColor(
                gSceneCurrDisplayList++,
                ((LevelHeader_70 *) ((u8 **) (&((LevelHeader **) gCurrentLevelHeader2)[levelHeaderIndex]))[28])->rgba.r,
                ((LevelHeader_70 *) ((u8 **) (&((LevelHeader **) gCurrentLevelHeader2)[levelHeaderIndex]))[28])->rgba.g,
                ((LevelHeader_70 *) ((u8 **) (&((LevelHeader **) gCurrentLevelHeader2)[levelHeaderIndex]))[28])->rgba.b,
                ((LevelHeader_70 *) ((u8 **) (&((LevelHeader **) gCurrentLevelHeader2)[levelHeaderIndex]))[28])
                    ->rgba.a);
        } else {
            gDPSetEnvColor(gSceneCurrDisplayList++, 255, 255, 255, 0);
        }
        if (batchFlags & BATCH_FLAGS_PULSATING_LIGHTS) {
            color = gCurrentLevelHeader2->pulseLightData->outColorValue;
            gDPSetPrimColor(gSceneCurrDisplayList++, 0, 0, color, color, color, color);
            material_set_blinking_lights(&gSceneCurrDisplayList, texture, batchFlags, texOffset);
            gSPVertexDKR(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(vertices), numberVertices, 0);
            gSPPolygon(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(triangles), numberTriangles, TRIN_ENABLE_TEXTURE);
            gDPSetPrimColor(gSceneCurrDisplayList++, 0, 0, 255, 255, 255, 255);
        } else {
            material_set(&gSceneCurrDisplayList, texture, batchFlags, texOffset);
            batchFlags = TRUE;
            if (texture == NULL) {
                batchFlags = FALSE;
            }
            gSPVertexDKR(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(vertices), numberVertices, 0);
            gSPPolygon(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(triangles), numberTriangles, batchFlags);
        }
    }
}

/**
 * Parse through applicable segments in the level.
 * Uses function recursion to ensure adjacent segments remain next to each other in the list.
 */
void traverse_segments_bsp_tree(s32 nodeIndex, s32 segmentIndex, s32 segmentIndex2, u8 *segmentsOrder,
                                s32 *segmentsOrderIndex) {
    BspTreeNode *curNode;
    s32 camValue;

    curNode = &gCurrentLevelModel->segmentsBspTree[nodeIndex];
    if (curNode->splitType == 0) {
        camValue = gSceneActiveCamera->trans.x_position; // Camera X
    } else if (curNode->splitType == 1) {
        camValue = gSceneActiveCamera->trans.y_position; // Camera Y
    } else {
        camValue = gSceneActiveCamera->trans.z_position; // Camera Z
    }

    if (camValue < curNode->splitValue) {
        if (curNode->leftNode != -1) {
            traverse_segments_bsp_tree(curNode->leftNode, segmentIndex, curNode->segmentIndex - 1, segmentsOrder,
                                       segmentsOrderIndex);
        } else {
            add_segment_to_order(segmentIndex, segmentsOrderIndex, segmentsOrder);
        }

        if (curNode->rightNode != -1) {
            traverse_segments_bsp_tree(curNode->rightNode, curNode->segmentIndex, segmentIndex2, segmentsOrder,
                                       segmentsOrderIndex);
        } else {
            add_segment_to_order(segmentIndex2, segmentsOrderIndex, segmentsOrder);
        }
    } else {
        if (curNode->rightNode != -1) {
            traverse_segments_bsp_tree(curNode->rightNode, curNode->segmentIndex, segmentIndex2, segmentsOrder,
                                       segmentsOrderIndex);
        } else {
            add_segment_to_order(segmentIndex2, segmentsOrderIndex, segmentsOrder);
        }

        if (curNode->leftNode != -1) {
            traverse_segments_bsp_tree(curNode->leftNode, segmentIndex, curNode->segmentIndex - 1, segmentsOrder,
                                       segmentsOrderIndex);
        } else {
            add_segment_to_order(segmentIndex, segmentsOrderIndex, segmentsOrder);
        }
    }
}

/**
 * Add this segment index to the specified segment ordering table if the segment in question is in view of the camera.
 */
void add_segment_to_order(s32 segmentIndex, s32 *segmentsOrderIndex, u8 *segmentsOrder) {
    u32 temp;
    if (segmentIndex < gCurrentLevelModel->numberOfSegments) {
        if (gSceneStartSegment != -1) {
            temp = gCurrentLevelModel->segmentsBitfields[gSceneStartSegment + (segmentIndex >> 3)];
            temp >>= segmentIndex & 7;
            temp &= 0xFF;
        } else {
            temp = 1;
        }
        if (temp & 1 && should_segment_be_visible(&gCurrentLevelModel->segmentsBoundingBoxes[segmentIndex])) {
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
    if ((x < (bb->x2 + 25)) && ((bb->x1 - 25) < x) && (z < (bb->z2 + 25)) && ((bb->z1 - 25) < z) &&
        (y < (bb->y2 + 25)) && ((bb->y1 - 25) < y)) {
        return TRUE;
    }

    return FALSE;
}

/**
 * Iterates through every existing segment to see which one the active camera is inside.
 * Uses mainly a two dimensional axis check here, instead of the function above.
 * Returns the segment currently inside.
 * Official Name: trackGetBlock
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
        if (x < bb->x2 && bb->x1 < x && z < bb->z2 && bb->z1 < z) {
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
s32 get_inside_segment_count_xz(s32 x, s32 z, s32 *arg2) {
    s32 i;
    s32 cnt = 0;
    LevelModelSegmentBoundingBox *bb;
    for (i = 0; i < gCurrentLevelModel->numberOfSegments; i++) {
        bb = gCurrentLevelModel->segmentsBoundingBoxes + i;
        if (x < bb->x2 + 4 && bb->x1 - 4 < x && z < bb->z2 + 4 && bb->z1 - 4 < z) {
            *arg2 = i;
            cnt++;
            arg2++;
        }
    }
    return cnt;
}

/**
 * Carbon copy of the above function, but takes into account the Y axis, too.
 * Official name: trackGetCubeBlockList
 */
s32 get_inside_segment_count_xyz(s32 *arg0, s16 xPos1, s16 yPos1, s16 zPos1, s16 xPos2, s16 yPos2, s16 zPos2) {
    s32 cnt;
    s32 i;
    LevelModelSegmentBoundingBox *bb;

    xPos1 -= 4;
    yPos1 -= 4;
    zPos1 -= 4;
    xPos2 += 4;
    yPos2 += 4;
    zPos2 += 4;

    i = 0;
    cnt = 0;

    while (i < gCurrentLevelModel->numberOfSegments) {
        bb = &gCurrentLevelModel->segmentsBoundingBoxes[i];
        if ((bb->x2 >= xPos1) && (xPos2 >= bb->x1) && (bb->z2 >= zPos1) && (zPos2 >= bb->z1) && (bb->y2 >= yPos1) &&
            (yPos2 >= bb->y1)) {
            cnt++;
            *arg0++ = i;
        }
        i++;
    }
    return cnt;
}

/**
 * Returns this segment data.
 */
LevelModelSegment *get_segment(s32 segmentID) {
    if (segmentID < 0 || gCurrentLevelModel->numberOfSegments < segmentID) {
        return NULL;
    }

    return &gCurrentLevelModel->segments[segmentID];
}

/**
 * Returns the bounding box data of this segment.
 * Official name: trackBlockDim
 */
LevelModelSegmentBoundingBox *get_segment_bounding_box(s32 segmentID) {
    if (segmentID < 0 || gCurrentLevelModel->numberOfSegments < segmentID) {
        return NULL;
    }

    return &gCurrentLevelModel->segmentsBoundingBoxes[segmentID];
}

void func_8002A31C(void) {
    f32 ox1;
    f32 oy1;
    f32 oz1;
    f32 ox2;
    f32 oy2;
    f32 oz2;
    f32 ox3;
    f32 oy3;
    f32 oz3;
    Matrix *cameraMatrix;
    f32 inverseMagnitude;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    f32 w;

    cameraMatrix = get_projection_matrix_f32();
    for (i = 0; i < ARRAY_COUNT(D_8011D0F8);) {
        x = D_800DC8AC[i][0].x;
        y = D_800DC8AC[i][0].y;
        z = D_800DC8AC[i][0].z;
        ox1 = x;
        oy1 = y;
        oz1 = z;
        guMtxXFMF(*cameraMatrix, x, y, z, &ox1, &oy1, &oz1);
        x = D_800DC8AC[i][1].x;
        y = D_800DC8AC[i][1].y;
        z = D_800DC8AC[i][1].z;
        ox2 = x;
        oy2 = y;
        oz2 = z;
        guMtxXFMF(*cameraMatrix, x, y, z, &ox2, &oy2, &oz2);
        x = D_800DC8AC[i][2].x;
        y = D_800DC8AC[i][2].y;
        z = D_800DC8AC[i][2].z;
        ox3 = x;
        oy3 = y;
        oz3 = z;
        guMtxXFMF(*cameraMatrix, x, y, z, &ox3, &oy3, &oz3);
        x = ((oz2 - oz3) * oy1) + (oy2 * (oz3 - oz1)) + (oy3 * (oz1 - oz2));
        y = ((ox2 - ox3) * oz1) + (oz2 * (ox3 - ox1)) + (oz3 * (ox1 - ox2));
        z = ((oy2 - oy3) * ox1) + (ox2 * (oy3 - oy1)) + (ox3 * (oy1 - oy2));
        inverseMagnitude = (1.0 / sqrtf((x * x) + (y * y) + (z * z)));
        if (inverseMagnitude > 0.0) {
            x *= inverseMagnitude;
            y *= inverseMagnitude;
            z *= inverseMagnitude;
        }
        w = -((ox1 * x) + (oy1 * y) + (oz1 * z));
        D_8011D0F8[i].x = x;
        D_8011D0F8[i].y = y;
        D_8011D0F8[i].z = z;
        D_8011D0F8[i].w = w;
        i++;
    }
}

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
        dirX = D_8011D0F8[j].x;
        dirY = D_8011D0F8[j].y;
        dirZ = D_8011D0F8[j].z;
        dirW = D_8011D0F8[j].w;

        for (i = 0, isVisible = FALSE; i < 8 && !isVisible; i++) {
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

    if (!(obj->segment.trans.flags & OBJ_FLAGS_PARTICLE)) {
        alpha = 255;
        viewDistance = obj->segment.header->drawDistance;
        if (obj->segment.header->drawDistance) {
            if (gScenePlayerViewports == 3) {
                viewDistance *= 0.5;
            }

            dist = get_distance_to_active_camera(obj->segment.trans.x_position, obj->segment.trans.y_position,
                                                 obj->segment.trans.z_position);

            if (viewDistance < dist) {
                return FALSE;
            }

            fadeDist = viewDistance * 0.8;
            if (fadeDist < dist) {
                temp2 = viewDistance - fadeDist;
                if (temp2 > 0) {
                    fadeDist = dist - fadeDist;
                    alpha = ((f32) (1.0 - ((fadeDist) / temp2)) * 255.0);
                }
                if (alpha == 0) {
                    alpha = 1;
                }
            }
        }
        switch (obj->behaviorId) {
            case BHV_RACER:
                obj64 = obj->unk64;
                obj->segment.object.opacity = ((obj64->racer.transparency + 1) * alpha) >> 8;
                break;
            case BHV_TIMETRIAL_GHOST: // Ghost Object?
                obj64 = obj->unk64;
                obj->segment.object.opacity = obj64->racer.transparency;
                break;
            case BHV_ANIMATED_OBJECT: // Cutscene object?
            case BHV_CAMERA_ANIMATION:
            case BHV_CAR_ANIMATION:
            case BHV_CHARACTER_SELECT:
            case BHV_VEHICLE_ANIMATION: // Title screen actor
            case BHV_HIT_TESTER:        // hittester
            case BHV_HIT_TESTER_2:      // animated objects?
            case BHV_ANIMATED_OBJECT_2: // space ships
                obj64 = obj->unk64;
                obj->segment.object.opacity = obj64->wizpig2.pad0[0x42];
                break;
            case BHV_PARK_WARDEN:
            case BHV_GOLDEN_BALLOON:
            case BHV_PARK_WARDEN_2: // GBParkwarden
                break;
            default:
                obj->segment.object.opacity = alpha;
                break;
        }
        for (i = 0; i < 3; i++) {
            x = D_8011D0F8[i].x;
            z = D_8011D0F8[i].z;
            w = D_8011D0F8[i].w;
            y = D_8011D0F8[i].y;
            accum = (x * obj->segment.trans.x_position) + (y * obj->segment.trans.y_position) +
                    (z * obj->segment.trans.z_position) + w + obj->segment.camera.unk34;
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
UNUSED void dayGetTrackFade(s32 *arg0, s32 *arg1, s32 *arg2) {
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

/**
 * Iterates through active waves on the track, then saves its rotation vector and height if found.
 * Returns zero if no waves are found, or if too high up.
 * Two types exist: calm, which have no means of displacement, and wavy, which do.
 */
s32 get_wave_properties(f32 yPos, f32 *waterHeight, Vec3f *rotation) {
    s32 var_a0;
    WaterProperties **wave;
    s32 i;
    s32 index;
    s32 len;
    f32 height;

    len = D_8011D308;
    if (rotation != NULL) {
        rotation->f[0] = 0.0f;
        rotation->f[2] = 0.0f;
        rotation->f[1] = 1.0f;
    }
    wave = gTrackWaves;
    for (var_a0 = i = 0; i < len; i++) {
        if (wave[i]->type == WATER_CALM || wave[i]->type == WATER_WAVY) {
            var_a0++;
        }
    }
    if (var_a0 == 0) {
        return 0;
    }
    wave = gTrackWaves;
    index = -1;
    for (i = 0; i < len; i++) {
        height = wave[i]->waveHeight;
        if (wave[i]->type == WATER_CALM || wave[i]->type == WATER_WAVY) {
            if (yPos < height + 25.0 && (wave[i]->rot.y > 0.5 || var_a0 == 1)) {
                index = i;
            }
        } else if (index >= 0 && var_a0 >= 2 && yPos < height - 20.0) {
            index = -1;
        }
    }
    if (index < 0) {
        return 0;
    }
    *waterHeight = gTrackWaves[index]->waveHeight;
    if (rotation != NULL) {
        rotation->f[0] = gTrackWaves[index]->rot.x;
        rotation->f[1] = gTrackWaves[index]->rot.y;
        rotation->f[2] = gTrackWaves[index]->rot.z;
    }
    return gTrackWaves[index]->type;
}

#ifdef NON_EQUIVALENT
s32 func_8002B0F4(s32 levelSegmentIndex, f32 xIn, f32 zIn, WaterProperties ***arg3) {
    LevelModelSegment *currentSegment;
    LevelModelSegmentBoundingBox *currentBoundingBox;
    Triangle *tri;
    Vertex *vert;
    f32 temp_f2_2;
    s16 vert2X;
    s16 vert2Z;
    s16 temp_a2;
    s16 vert3X;
    s16 vert3Z;
    s32 currentVerticesOffset;
    s16 nextFaceOffset;
    s16 vert1X;
    s16 currentFaceOffset;
    s16 vert1Z;
    s16 var_a1;
    s32 faceNum;
    s16 var_s1;
    s16 var_t0;
    s16 var_t1;
    s32 XInInt;
    s32 ZInInt;
    s32 temp_ra_1;
    s32 temp_ra_2;
    s32 temp_ra_3;
    s32 yOutCount;
    s32 batchNum;
    s32 i;
    s32 var_v0;
    s32 stopSorting;
    TriangleBatchInfo *currentBatch;
    f32 *temp_v1_4;
    Vec4f tempVec4f;
    u16 temp;

    s32 sp108;
    s32 spB0[8];
    s32 temp_s2;
    s32 var_fp;

    D_8011D308 = 0;
    *arg3 = NULL;

    sp108 = get_inside_segment_count_xz(xIn, zIn, spB0);
    if (sp108 == 0 || sp108 >= 8) {
        return 0;
    }

    XInInt = xIn;
    ZInInt = zIn;

    for (var_fp = 0; var_fp < sp108; var_fp++) {
        currentSegment = &gCurrentLevelModel->segments[spB0[var_fp]];
        currentBoundingBox = &gCurrentLevelModel->segmentsBoundingBoxes[spB0[var_fp]];
        var_a1 = 1;
        var_s1 = 0;

        temp_a2 = ((currentBoundingBox->x2 - currentBoundingBox->x1) >> 3) + 1;
        var_t0 = temp_a2 + currentBoundingBox->x1;
        var_t1 = currentBoundingBox->x1;
        for (i = 0; i < 8; i++) {
            if (var_t0 >= XInInt && XInInt >= var_t1) {
                var_s1 |= var_a1;
            }
            var_t0 += temp_a2;
            var_t1 += temp_a2;
            var_a1 *= 2;
        }

        // Same as above, but for Z
        temp_a2 = ((currentBoundingBox->z2 - currentBoundingBox->z1) >> 3) + 1;
        var_t0 = temp_a2 + currentBoundingBox->z1;
        var_t1 = currentBoundingBox->z1;
        for (i = 0; i < 8; i++) {
            if (var_t0 >= ZInInt && ZInInt >= var_t1) {
                var_s1 |= var_a1;
            }
            var_t0 += temp_a2;
            var_t1 += temp_a2;
            var_a1 *= 2;
        }

        yOutCount = 0;

        for (batchNum = 0; batchNum < currentSegment->numberOfBatches; batchNum++) {
            currentBatch = &currentSegment->batches[batchNum];
            temp_s2 = gCurrentLevelModel->textures[currentBatch->textureIndex].unk7;
            currentFaceOffset = currentBatch->facesOffset;
            nextFaceOffset = currentBatch[1].facesOffset;
            currentVerticesOffset = currentBatch->verticesOffset;

            if (temp_s2 != 11 && temp_s2 != 15 &&
                (currentBatch->flags & (BATCH_FLAGS_HIDDEN | BATCH_FLAGS_UNK00000200))) {
                currentFaceOffset = nextFaceOffset;
            }

            for (faceNum = currentFaceOffset; faceNum < nextFaceOffset; faceNum++) {
                if (var_s1 == (currentSegment->unk10[faceNum] & var_s1)) {
                    tri = &currentSegment->triangles[faceNum];
                    vert = &currentSegment->vertices[tri->verticesArray[1] + currentVerticesOffset];
                    vert1X = vert->x;
                    vert1Z = vert->z;
                    vert = &currentSegment->vertices[tri->verticesArray[2] + currentVerticesOffset];
                    vert2X = vert->x;
                    vert2Z = vert->z;
                    vert = &currentSegment->vertices[tri->verticesArray[3] + currentVerticesOffset];
                    vert3X = vert->x;
                    vert3Z = vert->z;
                    temp_ra_1 =
                        ((((XInInt - vert2X) * (vert3Z - vert2Z)) - ((vert3X - vert2X) * (ZInInt - vert2Z))) >= 0);
                    temp_ra_2 =
                        ((((XInInt - vert1X) * (vert2Z - vert1Z)) - ((vert2X - vert1X) * (ZInInt - vert1Z))) >= 0);
                    temp_ra_3 =
                        ((((XInInt - vert1X) * (vert3Z - vert1Z)) - ((vert3X - vert1X) * (ZInInt - vert1Z))) >= 0);
                    if (temp_ra_1 == temp_ra_2 && temp_ra_2 != temp_ra_3) {
                        temp = currentSegment->unk14[faceNum].triangleIndex;
                        temp_v1_4 = (f32 *) &currentSegment->unk18[temp * 4];
                        tempVec4f.x = temp_v1_4[0];
                        tempVec4f.y = temp_v1_4[1];
                        tempVec4f.z = temp_v1_4[2];
                        tempVec4f.w = temp_v1_4[3];
                        if (tempVec4f.y != 0.0) {
                            D_8011D128[yOutCount].type = temp_s2;
                            D_8011D128[yOutCount].waveHeight =
                                -(((tempVec4f.x * xIn) + (tempVec4f.z * zIn) + tempVec4f.w) / tempVec4f.y);
                            D_8011D128[yOutCount].rot.x = tempVec4f.x;
                            D_8011D128[yOutCount].rot.y = tempVec4f.y;
                            D_8011D128[yOutCount].rot.z = tempVec4f.z;
                            yOutCount++;

                            if (yOutCount >= 20) {
                                batchNum = currentSegment->numberOfBatches;
                                faceNum = nextFaceOffset;
                                var_fp = sp108;
                            }
                        }
                    }
                }
            }
        }
    }

    if (levelSegmentIndex >= 0 && levelSegmentIndex < gCurrentLevelModel->numberOfSegments) {
        D_8011D128[yOutCount].type = WATER_WAVY;
        if (gCurrentLevelModel->segments[levelSegmentIndex].hasWaves && gWaveBlockCount != 0) {
            D_8011D128[yOutCount].waveHeight = func_800BB2F4(levelSegmentIndex, xIn, zIn, &D_8011D128[yOutCount].rot);
        } else {
            D_8011D128[yOutCount].waveHeight = gCurrentLevelModel->segments[levelSegmentIndex].unk38;
            D_8011D128[yOutCount].rot.x = 0.0f;
            D_8011D128[yOutCount].rot.y = 1.0f;
            D_8011D128[yOutCount].rot.z = 0.0f;
        }
        yOutCount++;
    }

    // clang-format off
    for (i = 0; i < yOutCount; i++) { gTrackWaves[i] = &D_8011D128[i]; }
    // clang-format on

    do {
        stopSorting = TRUE;
        for (i = 0; i < yOutCount - 1; i++) {
            if (gTrackWaves[i]->waveHeight < gTrackWaves[i + 1]->waveHeight) {
                WaterProperties *wave = gTrackWaves[i];
                stopSorting = FALSE;
                gTrackWaves[i] = gTrackWaves[i + 1];
                gTrackWaves[i + 1] = wave;
            }
        }
    } while (!stopSorting);

    *arg3 = gTrackWaves;
    D_8011D308 = yOutCount;
    return yOutCount;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/tracks/func_8002B0F4.s")
#endif

s32 func_8002B9BC(Object *obj, f32 *arg1, Vec3f *arg2, s32 arg3) {
    LevelModelSegment *seg;

    if (arg2 != NULL) {
        arg2->x = 0.0f;
        arg2->z = 0.0f;
        arg2->y = 1.0f;
    }
    if ((obj->segment.object.segmentID < 0) ||
        (obj->segment.object.segmentID >= gCurrentLevelModel->numberOfSegments)) {
        return FALSE;
    }
    seg = &gCurrentLevelModel->segments[obj->segment.object.segmentID];
    if ((seg->hasWaves != 0) && (gWaveBlockCount != 0) && (arg3 == 1)) {
        *arg1 = func_800BB2F4(obj->segment.object.segmentID, obj->segment.trans.x_position,
                              obj->segment.trans.z_position, arg2);
        return TRUE;
    } else {
        *arg1 = seg->unk38;
        return TRUE;
    }
}

#ifdef NON_MATCHING
// Collision: Returns the Y Values in yOut, and the number of values in the array as the return.
// Get's the Y Offset acrross a surface.
// Basically it goes down, finds a triangle, then locates where the intersection is and returns the Y level of that.
s32 func_8002BAB0(s32 levelSegmentIndex, f32 xIn, f32 zIn, f32 *yOut) {
    LevelModelSegment *currentSegment;
    LevelModelSegmentBoundingBox *currentBoundingBox;
    Triangle *tri;
    Vertex *vert;
    f32 temp_f2_2;
    s16 vert2X;
    s16 vert2Z;
    s16 temp_a2;
    s16 vert3X;
    s16 vert3Z;
    s32 currentVerticesOffset;
    s16 nextFaceOffset;
    s16 vert1X;
    s16 currentFaceOffset;
    s16 vert1Z;
    s16 var_a1;
    s32 faceNum;
    s16 var_s1;
    s16 var_t0;
    s16 var_t1;
    s32 XInInt;
    s32 ZInInt;
    s32 temp_ra_1;
    s32 temp_ra_2;
    s32 temp_ra_3;
    s32 yOutCount;
    s32 batchNum;
    s32 i;
    s32 var_v0;
    s32 stopSorting;
    TriangleBatchInfo *currentBatch;
    f32 *temp_v1_4;
    Vec4f tempVec4f;
    u16 temp;

    if (levelSegmentIndex < 0 || levelSegmentIndex >= gCurrentLevelModel->numberOfSegments) {
        return 0;
    }

    vert = NULL; // fake?
    currentSegment = &gCurrentLevelModel->segments[levelSegmentIndex];
    currentBoundingBox = &gCurrentLevelModel->segmentsBoundingBoxes[levelSegmentIndex];
    var_a1 = 1;
    var_s1 = 0;
    XInInt = xIn;
    ZInInt = zIn;

    temp_a2 = ((currentBoundingBox->x2 - currentBoundingBox->x1) >> 3) + 1;
    var_t0 = temp_a2 + currentBoundingBox->x1;
    var_t1 = currentBoundingBox->x1;
    for (i = 0; i < 8; i++) {
        if (var_t0 >= XInInt && XInInt >= var_t1) {
            var_s1 |= var_a1;
        }
        var_t0 += temp_a2;
        var_t1 += temp_a2;
        var_a1 *= 2;
    }

    // Same as above, but for Z
    temp_a2 = ((currentBoundingBox->z2 - currentBoundingBox->z1) >> 3) + 1;
    var_t0 = temp_a2 + currentBoundingBox->z1;
    var_t1 = currentBoundingBox->z1;
    for (i = 0; i < 8; i++) {
        if (var_t0 >= ZInInt && ZInInt >= var_t1) {
            var_s1 |= var_a1;
        }
        var_t0 += temp_a2;
        var_t1 += temp_a2;
        var_a1 *= 2;
    }

    yOutCount = 0;
    for (batchNum = 0; batchNum < currentSegment->numberOfBatches; batchNum++) {
        do {
        } while (0);
        currentBatch = &currentSegment->batches[batchNum];
        currentFaceOffset = currentBatch->facesOffset;
        nextFaceOffset = currentBatch[1].facesOffset;
        currentVerticesOffset = currentBatch->verticesOffset;
        for (faceNum = currentFaceOffset; faceNum < nextFaceOffset; faceNum++) {
            if (var_s1 == (currentSegment->unk10[faceNum] & var_s1)) {
                tri = &currentSegment->triangles[faceNum];
                vert = &currentSegment->vertices[tri->verticesArray[1] + currentVerticesOffset];
                vert1X = vert->x;
                vert1Z = vert->z;
                vert = &currentSegment->vertices[tri->verticesArray[2] + currentVerticesOffset];
                vert2X = vert->x;
                vert2Z = vert->z;
                vert = &currentSegment->vertices[tri->verticesArray[3] + currentVerticesOffset];
                vert3X = vert->x;
                vert3Z = vert->z;
                temp_ra_1 = ((((XInInt - vert2X) * (vert3Z - vert2Z)) - ((vert3X - vert2X) * (ZInInt - vert2Z))) >= 0);
                temp_ra_2 = ((((XInInt - vert1X) * (vert2Z - vert1Z)) - ((vert2X - vert1X) * (ZInInt - vert1Z))) >= 0);
                temp_ra_3 = ((((XInInt - vert1X) * (vert3Z - vert1Z)) - ((vert3X - vert1X) * (ZInInt - vert1Z))) >= 0);
                if (temp_ra_1 == temp_ra_2 && temp_ra_2 != temp_ra_3) {
                    temp = currentSegment->unk14[faceNum].triangleIndex;
                    temp_v1_4 = (f32 *) &currentSegment->unk18[temp * 4];
                    tempVec4f.x = temp_v1_4[0];
                    tempVec4f.y = temp_v1_4[1];
                    tempVec4f.z = temp_v1_4[2];
                    tempVec4f.w = temp_v1_4[3];
                    if (tempVec4f.y != 0.0) {
                        yOut[yOutCount] = -(((tempVec4f.x * xIn) + (tempVec4f.z * zIn) + tempVec4f.w) / tempVec4f.y);
                        yOutCount++;
                    }
                }
            }
        }
    }

    do {
        stopSorting = TRUE;
        for (var_v0 = 0; var_v0 < yOutCount - 1; var_v0++) {
            if (yOut[var_v0] > yOut[var_v0 + 1]) {
                stopSorting = FALSE;
                temp_f2_2 = yOut[var_v0];
                yOut[var_v0] = yOut[var_v0 + 1];
                yOut[var_v0 + 1] = temp_f2_2;
            }
        }
    } while (!stopSorting);

    return yOutCount;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/tracks/func_8002BAB0.s")
#endif

#ifdef NON_MATCHING
// generate_track
// Loads a level track from the index in the models table.
// Has regalloc issues.
void func_8002C0C4(s32 modelId) {
    s32 i, j, k;
    s32 temp_s4;
    s32 temp;
    LevelModel *mdl;

    set_texture_colour_tag(COLOUR_TAG_GREEN);
    gTrackModelHeap = mempool_alloc_safe(LEVEL_MODEL_MAX_SIZE, COLOUR_TAG_YELLOW);
    gCurrentLevelModel = gTrackModelHeap;
    D_8011D370 = mempool_alloc_safe(0x7D0, COLOUR_TAG_YELLOW);
    D_8011D374 = mempool_alloc_safe(0x1F4, COLOUR_TAG_YELLOW);
    D_8011D378 = 0;
    gLevelModelTable = (s32 *) load_asset_section_from_rom(ASSET_LEVEL_MODELS_TABLE);

    for (i = 0; gLevelModelTable[i] != -1; i++) {}
    i--;
    if (modelId >= i) {
        modelId = 0;
    }

    // offset = gLevelModelTable[modelId];
    temp_s4 = gLevelModelTable[modelId + 1] - gLevelModelTable[modelId];

    // temp = compressedRamAddr
    temp = (s32) gCurrentLevelModel;
    temp += (LEVEL_MODEL_MAX_SIZE - temp_s4);
    temp -= ((s32) temp % 16); // Align to 16-byte boundary.

    load_asset_to_address(ASSET_LEVEL_MODELS, temp, gLevelModelTable[modelId], temp_s4);
    gzip_inflate((u8 *) temp, (u8 *) gCurrentLevelModel);
    mempool_free(gLevelModelTable); // Done with the level models table, so free it.

    mdl = gCurrentLevelModel;

    LOCAL_OFFSET_TO_RAM_ADDRESS(TextureInfo *, gCurrentLevelModel->textures);
    LOCAL_OFFSET_TO_RAM_ADDRESS(LevelModelSegment *, gCurrentLevelModel->segments);
    LOCAL_OFFSET_TO_RAM_ADDRESS(LevelModelSegmentBoundingBox *, gCurrentLevelModel->segmentsBoundingBoxes);
    LOCAL_OFFSET_TO_RAM_ADDRESS(u8 *, gCurrentLevelModel->unkC);
    LOCAL_OFFSET_TO_RAM_ADDRESS(u8 *, gCurrentLevelModel->segmentsBitfields);
    LOCAL_OFFSET_TO_RAM_ADDRESS(BspTreeNode *, gCurrentLevelModel->segmentsBspTree);

    if (1) {}
    if (1) {}
    if (1) {}
    if (1) {}
    if (1) {}
    if (1) {} // Fakematch

    for (k = 0; k < gCurrentLevelModel->numberOfSegments; k++) {
        LOCAL_OFFSET_TO_RAM_ADDRESS(Vertex *, gCurrentLevelModel->segments[k].vertices);
        LOCAL_OFFSET_TO_RAM_ADDRESS(Triangle *, gCurrentLevelModel->segments[k].triangles);
        LOCAL_OFFSET_TO_RAM_ADDRESS(TriangleBatchInfo *, gCurrentLevelModel->segments[k].batches);
        LOCAL_OFFSET_TO_RAM_ADDRESS(CollisionNode *, gCurrentLevelModel->segments[k].unk14);
    }
    for (k = 0; k < gCurrentLevelModel->numberOfTextures; k++) {
        gCurrentLevelModel->textures[k].texture =
            load_texture(((s32) gCurrentLevelModel->textures[k].texture) | 0x8000);
    }
    j = (s32) gCurrentLevelModel + gCurrentLevelModel->modelSize;
    for (k = 0; k < gCurrentLevelModel->numberOfSegments; k++) {
        gCurrentLevelModel->segments[k].unk10 = (s16 *) j;
        j = (s32) align16(((u8 *) (gCurrentLevelModel->segments[k].numberOfTriangles * 2)) + j);
        gCurrentLevelModel->segments[k].unk18 = (f32 *) j;
        j = (s32) & ((u8 *) j)[func_8002CC30(&gCurrentLevelModel->segments[k])];
        func_8002C954(&gCurrentLevelModel->segments[k], &gCurrentLevelModel->segmentsBoundingBoxes[k], k);
        gCurrentLevelModel->segments[k].unk30 = 0;
        gCurrentLevelModel->segments[k].unk34 = (s16 *) j;
        func_8002C71C(&gCurrentLevelModel->segments[k]);
        j = (s32) align16(((u8 *) (gCurrentLevelModel->segments[k].unk32 * 2)) + j);
    }
    temp_s4 = j - (s32) gCurrentLevelModel;
    if (temp_s4 > LEVEL_MODEL_MAX_SIZE) {
        rmonPrintf("ERROR!! TrackMem overflow .. %d\n", temp_s4);
    }
    mempool_free_timer(0);
    mempool_free(gTrackModelHeap);
    mempool_alloc_fixed(temp_s4, (u8 *) gTrackModelHeap, COLOUR_TAG_YELLOW);
    mempool_free_timer(2);
    minimap_init(gCurrentLevelModel);

    for (i = 0; i < gCurrentLevelModel->numberOfSegments; i++) {
        for (temp_s4 = 0; temp_s4 < gCurrentLevelModel->segments[i].numberOfBatches; temp_s4++) {
            for (k = gCurrentLevelModel->segments[i].batches[temp_s4].verticesOffset;
                 k < gCurrentLevelModel->segments[i].batches[temp_s4 + 1].verticesOffset; k++) {
                // Why do this? Why not just set the vertex colors in the model itself?
                if (gCurrentLevelModel->segments[i].vertices[k].r == 1 &&
                    gCurrentLevelModel->segments[i].vertices[k].g == 1) {
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
#pragma GLOBAL_ASM("asm/nonmatchings/tracks/func_8002C0C4.s")
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

/**
 * Returns the current loaded level geometry
 * Official Name: trackGetTrack
 */
LevelModel *get_current_level_model(void) {
    return gCurrentLevelModel;
}

/**
 * Frees and unloads level data from RAM.
 */
void free_track(void) {
    s32 i;

    racerfx_free();
    if (gWaveBlockCount != 0) {
        free_waves();
    }
    for (i = 0; i < gCurrentLevelModel->numberOfTextures; i++) {
        tex_free(gCurrentLevelModel->textures[i].texture);
    }
    mempool_free(gTrackModelHeap);
    mempool_free(D_8011D370);
    mempool_free(D_8011D374);
    sprite_free((Sprite *) gCurrentLevelModel->minimapSpriteIndex);
    for (i = 0; i < ARRAY_COUNT(gShadowHeapData); i++) {
        mempool_free(gShadowHeapData[i]);
        mempool_free(gShadowHeapTris[i]);
        mempool_free(gShadowHeapVerts[i]);
    }
    func_800257D0();
    if (gSkydomeSegment != NULL) {
        free_object(gSkydomeSegment);
        gParticlePtrList_flush();
    }
    free_all_objects();
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
        endTri = segment->batches[i + 1].facesOffset;
        vertsOffset = segment->batches[i].verticesOffset;
        for (j = startTri; j < endTri; j++) {
            if (segment->triangles[j].flags & 0x80) {
                segment->unk10[j] = 0;
            } else {
                maxX = -32000;
                maxZ = -32000;
                minZ = 32000;
                minX = 32000;

                for (l = 0; l < 3; l++) {
                    vert = &segment->vertices[segment->triangles[j].verticesArray[l + 1] + vertsOffset];
                    k = vert->x;
                    vertX = k; // This is probably fake, but it matches.
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
                boxDelta = ((bbox->x2 - bbox->x1) >> 3) + 1;
                bit = 1;
                boxMax = boxDelta + bbox->x1;
                boxMin = bbox->x1;
                val = 0;
                for (k = 0; k < 8; k++) {
                    if (boxMax >= minX && maxX >= boxMin) {
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
                    if (boxMax >= minZ && maxZ >= boxMin) {
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

#ifdef NON_EQUIVALENT
s32 func_8002CC30(LevelModelSegment *segment) {
    s32 spF4;
    s32 spEC;
    s32 spD0;
    f32 tri1z;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    s32 sp78;
    s32 i;
    Triangle *temp_v1_4;
    Vertex *temp_a0;
    Vertex *temp_a0_2;
    f32 tri3z;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 tri2y;
    f32 temp_f12_2;
    f32 tri2z;
    f32 temp_f14_2;
    f32 tri3x;
    f32 temp_f16_2;
    f32 tri3y;
    f32 temp_f18_2;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f24_2;
    f32 tri1x;
    f32 temp_f28_2;
    f32 tri2x;
    f32 temp_f2_2;
    f32 tri1y;
    f32 temp_f30_2;
    f32 temp_f4;
    f32 var_f20;
    f32 var_f22;
    f32 var_f26;
    s16 vertsOffset;
    s16 temp_fp_2;
    s16 temp_t7_2;
    s16 endTri;
    s16 startTri;
    s16 var_a1;
    s16 var_s7;
    s16 var_v1;
    s32 temp_s6;
    s32 temp_t2;
    s32 temp_t4;
    s32 temp_t7;
    s32 temp_t9;
    s32 var_a0;
    s32 var_a1_2;
    s32 var_at;
    s32 var_s0;
    s32 var_s4;
    s32 var_s5;
    s32 var_t1;
    s32 var_v0;
    s32 var_v0_2;
    u16 temp_s0;
    u16 temp_s1;
    u16 temp_t3;
    u8 *temp_v1_2;
    Vertex *temp_v0_2;
    Vertex *temp_v0_3;
    Vertex *temp_v0_4;
    TriangleBatchInfo *temp_v0_5;
    Vertex *temp_v0_6;
    Vertex *temp_v0_7;
    f32 *temp_v1_3;
    f32 *temp_v1_5;
    CollisionNode *temp_v1_6;

    spEC = 0;
    var_s4 = 0;
    for (i = 0; i < segment->numberOfBatches; i++) {
        startTri = segment->batches[i].facesOffset;
        endTri = segment->batches[i + 1].facesOffset;
        vertsOffset = segment->batches[i].verticesOffset;
        if (startTri < endTri) {
            var_a1_2 = startTri * sizeof(Triangle);
            do {
                temp_v1_2 = &segment->triangles->verticesArray[var_a1_2];
                if (!(temp_v1_2[0] & 0x80)) {
                    temp_a0 = segment->vertices;
                    temp_v0_2 = &temp_a0[temp_v1_2[1] + vertsOffset]; //((temp_v1_2[1] + temp_fp) * 0xA) + temp_a0;
                    tri1x = temp_v0_2->x;
                    tri1y = temp_v0_2->y;
                    tri1z = temp_v0_2->z;
                    temp_v0_3 =
                        &temp_a0[temp_v1_2[2] + vertsOffset]; //((temp_v1_2[2] + curVertOffset) * 0xA) + temp_a0;
                    tri2x = temp_v0_3->x;
                    tri2y = temp_v0_3->y;
                    tri2z = temp_v0_3->z;
                    temp_v0_4 =
                        &temp_a0[temp_v1_2[3] + vertsOffset]; //((temp_v1_2[3] + curVertOffset) * 0xA) + temp_a0;
                    tri3x = temp_v0_4->x;
                    tri3y = temp_v0_4->y;
                    tri3z = temp_v0_4->z;
                    temp_f20 = ((tri2z - tri3z) * tri1y) + (tri2y * (tri3z - tri1z)) + (tri3y * (tri1z - tri2z));
                    temp_f22 = ((tri2x - tri3x) * tri1z) + (tri2z * (tri3x - tri1x)) + (tri3z * (tri1x - tri2x));
                    temp_f24 = ((tri2y - tri3y) * tri1x) + (tri2x * (tri3y - tri1y)) + (tri3x * (tri1y - tri2y));
                    temp_f0_2 = sqrtf((temp_f20 * temp_f20) + (temp_f22 * temp_f22) + (temp_f24 * temp_f24));
                    if (temp_f0_2 > 0.0) {
                        temp_f20 /= temp_f0_2;
                        temp_f22 /= temp_f0_2;
                        temp_f24 /= temp_f0_2;
                    }
                    segment->unk18[var_s4 + 0] = temp_f20;
                    segment->unk18[var_s4 + 1] = temp_f22;
                    segment->unk18[var_s4 + 2] = temp_f24;
                    segment->unk18[var_s4 + 3] = -((tri1x * temp_f20) + (tri1y * temp_f22) + (tri1z * temp_f24));
                    var_s4++;
                }
                var_a1_2 += sizeof(Triangle);
            } while (var_a1_2 < (endTri * 0x10));
        }
    }
    var_t1 = var_s4;
    if (D_8011B0F8 == 0) {
        spEC = 0;
        if (var_a1 > 0) {
            i = 0;
            do {
                temp_v0_5 = segment->batches + i;
                temp_t7_2 = temp_v0_5[1].verticesOffset;
                var_v1 = temp_v0_5->facesOffset;
                temp_fp_2 = temp_v0_5->verticesOffset;
                spF4 = (s32) temp_t7_2;
                var_at = var_v1 < spF4;
                if (temp_v0_5->flags & 0x200) {
                    var_v1 = temp_t7_2;
                    var_at = var_v1 < spF4;
                }
                var_s7 = var_v1;
                if (var_at != 0) {
                    var_a0 = var_v1 * 0x10;
                    do {
                        if (!(segment->triangles->verticesArray[var_a0] & 0x80)) {
                            temp_s1 = segment->unk14[var_s7].triangleIndex;
                            temp_v1_3 = segment->unk18 + (temp_s1 * 0x10);
                            var_v0 = 0;
                            spA0 = temp_v1_3[0];
                            var_s5 = 0;
                            sp9C = temp_v1_3[1];
                            sp78 = var_a0;
                            temp_f24 = temp_v1_3[2];
                            do {
                                temp_s6 = var_v0 + 1;
                                temp_v1_4 = &segment->triangles[var_s7];
                                var_s0 = temp_s6;
                                if (temp_s6 >= 3) {
                                    var_s0 = 0;
                                }
                                temp_s0 = (&segment->unk14[var_s7] + var_s5)->closestTri01;
                                if ((s32) temp_s0 < var_t1) {
                                    temp_v1_5 = segment->unk18 + (temp_s0 * 0x10);
                                    temp_a0_2 = segment->vertices;
                                    temp_v0_6 = temp_a0_2 +
                                                ((temp_v1_4->verticesArray[var_v0 + 1] + temp_fp_2) *
                                                 0xA); //((temp_v1_4->verticesArray[var_v0].unk1 + temp_fp_2) * 0xA);
                                    temp_f4 = (f32) temp_v0_6->z;
                                    tri1z = temp_f4;
                                    temp_v0_7 = temp_a0_2 + ((temp_v1_4->verticesArray[var_s0 + 1] + temp_fp_2) * 0xA);
                                    temp_f28_2 = (f32) temp_v0_6->x;
                                    spD0 = var_t1;
                                    temp_f30_2 = (f32) temp_v0_6->y;
                                    temp_f2_2 = (f32) temp_v0_7->x;
                                    temp_f16_2 = ((temp_v1_5[0] + spA0) * 10.0f) + temp_f28_2;
                                    temp_f12_2 = (f32) temp_v0_7->y;
                                    temp_f14_2 = (f32) temp_v0_7->z;
                                    temp_f18_2 = ((temp_v1_5[1] + sp9C) * 10.0f) + temp_f30_2;
                                    temp_f0_3 = ((temp_v1_5[2] + temp_f24) * 10.0f) + temp_f4;
                                    var_f20 = ((temp_f14_2 - temp_f0_3) * temp_f30_2) +
                                              (temp_f12_2 * (temp_f0_3 - temp_f4)) +
                                              (temp_f18_2 * (temp_f4 - temp_f14_2));
                                    var_f22 = ((temp_f2_2 - temp_f16_2) * temp_f4) +
                                              (temp_f14_2 * (temp_f16_2 - temp_f28_2)) +
                                              (temp_f0_3 * (temp_f28_2 - temp_f2_2));
                                    temp_f24_2 = ((temp_f12_2 - temp_f18_2) * temp_f28_2) +
                                                 (temp_f2_2 * (temp_f18_2 - temp_f30_2)) +
                                                 (temp_f16_2 * (temp_f30_2 - temp_f12_2));
                                    var_f26 = temp_f24_2;
                                    temp_f0_4 =
                                        sqrtf((var_f20 * var_f20) + (var_f22 * var_f22) + (temp_f24_2 * temp_f24_2));
                                    if ((f64) temp_f0_4 > 0.0) {
                                        var_f20 /= temp_f0_4;
                                        var_f22 /= temp_f0_4;
                                        var_f26 = temp_f24_2 / temp_f0_4;
                                    }
                                    if (temp_s0 != temp_s1) {
                                        var_v0_2 = 0;
                                        do {
                                            temp_v1_6 = &segment->unk14[temp_s0] + var_v0_2;
                                            temp_t3 = temp_v1_6->closestTri01;
                                            var_v0_2 += 2;
                                            if (temp_s1 == temp_t3) {
                                                temp_v1_6->closestTri01 = (s16) (var_s4 | 0x8000);
                                            }
                                        } while (var_v0_2 != 6);
                                    }
                                    (&segment->unk14[var_s7] + var_s5)->closestTri01 = (s16) var_s4;
                                    temp_t2 = var_s4 * 0x10;
                                    (segment->unk18[temp_t2]) = var_f20;
                                    (segment->unk18[temp_t2 + 1]) = var_f22;
                                    (segment->unk18[temp_t2 + 2]) = var_f26;
                                    var_s4 += 1;
                                    segment->unk18[temp_t2 + 3] =
                                        (f32) - ((temp_f28_2 * var_f20) + (temp_f30_2 * var_f22) + (tri1z * var_f26));
                                }
                                var_v0 = temp_s6;
                                var_s5 += 2;
                            } while (temp_s6 != 3);
                            var_a0 = sp78;
                        }
                        var_s7 += 1;
                        var_a0 += 0x10;
                    } while (var_s7 != spF4);
                    var_a1 = segment->numberOfBatches;
                }
                temp_t4 = spEC + 1;
                i += 0xC;
                spEC = temp_t4;
            } while (temp_t4 < var_a1);
        }
    }
    return var_s4 * 0x10;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/tracks/func_8002CC30.s")
#endif

typedef struct unk8002D30C_a0 {
    u8 pad00[0x04];
    struct unk8002D30C_a0 *unk04;
    struct unk8002D30C_a0 *unk08;
} unk8002D30C_a0;

void trackMakeAbsolute(unk8002D30C_a0 *arg0, s32 arg1) {
    while (1) {
        if (!arg0) {
            return;
        }
        if (arg0->unk04) {
            arg0->unk04 = (unk8002D30C_a0 *) ((s32) arg0->unk04 + arg1);
        }
        if (arg0->unk08) {
            arg0->unk08 = (unk8002D30C_a0 *) ((s32) arg0->unk08 + arg1);
        }

        trackMakeAbsolute(arg0->unk04, arg1);
        arg0 = arg0->unk08;
    }
}

/**
 * Render the shadow of an object on the ground as a decal.
 * Can subdivide itself to wrap around the terrain properly, as the N64 lacks stencil buffering.
 */
void shadow_render(Object *obj, ShadowData *shadow) {
    s32 i;
    s32 numVerts;
    s32 numTris;
    Vertex *vtx;
    Triangle *tri;
    s32 flags;
    UNUSED s32 tri2;
    s32 vtx2;
    s32 vtxCount;
    s32 triCount;
    s32 alpha;

    if (obj->segment.header->shadowGroup) {
        if (shadow->meshStart != -1 && gDisableShadows == FALSE) {
            gShadowIndex = gShadowHeapFlip;
            if (obj->segment.header->shadowGroup == SHADOW_SCENERY) {
                gShadowIndex += 2;
            }
            i = shadow->meshStart;
            gCurrShadowHeapData = gShadowHeapData[gShadowIndex];
            gCurrShadowTris = gShadowHeapTris[gShadowIndex];
            gCurrShadowVerts = gShadowHeapVerts[gShadowIndex];
            alpha = gCurrShadowVerts[gCurrShadowHeapData[i].vtxCount].a;
            flags = RENDER_FOG_ACTIVE | RENDER_Z_COMPARE;
            if (alpha == 0 || obj->segment.object.opacity == 0) {
                i = shadow->meshEnd; // It'd be easier to just return...
            } else if (alpha != 255 || obj->segment.object.opacity != 255) {
                flags = RENDER_FOG_ACTIVE | RENDER_SEMI_TRANSPARENT | RENDER_Z_COMPARE;
                alpha = (obj->segment.object.opacity * alpha) >> 8;
                gDPSetPrimColor(gSceneCurrDisplayList++, 0, 0, 255, 255, 255, alpha);
            }
            while (i < shadow->meshEnd) {
                material_set_no_tex_offset(&gSceneCurrDisplayList, gCurrShadowHeapData[i].texture, flags);
                // I hope we can clean this part up.
                tri2 = triCount = gCurrShadowHeapData[i].triCount; // Fakematch
                vtx2 = vtxCount = gCurrShadowHeapData[i].vtxCount;
                numTris = gCurrShadowHeapData[i + 1].triCount - triCount;
                numVerts = gCurrShadowHeapData[i + 1].vtxCount - vtxCount;
                tri = &gCurrShadowTris[triCount];
                vtx = &gCurrShadowVerts[vtx2];
                gSPVertexDKR(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(vtx), numVerts, 0);
                gSPPolygon(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(tri), numTris, 1);
                i++;
            }

            if (flags != RENDER_Z_COMPARE) {
                gDPSetPrimColor(gSceneCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            }
        }
    }
}

/**
 * Used only by cars, render a texture on the surface of the water where the car is
 * to give the wave effect. Works almost identically to shadows, since water can be wavy.
 */
void watereffect_render(Object *obj, WaterEffect *effect) {
    s32 i;
    s32 numVerts;
    s32 numTris;
    Vertex *vtx;
    Triangle *tri;
    s32 flags;
    UNUSED s32 triCount;
    UNUSED s32 vtxCount;

    if (obj->segment.header->waterEffectGroup) {
        if (effect->meshStart != -1 && gDisableShadows == FALSE) {
            gWaterEffectIndex = gShadowHeapFlip;
            i = effect->meshStart;
            if (obj->segment.header->waterEffectGroup == SHADOW_SCENERY) {
                gWaterEffectIndex += 2;
                if (get_distance_to_active_camera(obj->segment.trans.x_position, obj->segment.trans.y_position,
                                                  obj->segment.trans.z_position) > 768.0f) {
                    i = effect->meshEnd; // Just return.
                }
            }
            flags = RENDER_FOG_ACTIVE | RENDER_Z_COMPARE;
            gCurrShadowHeapData = gShadowHeapData[gWaterEffectIndex];
            gCurrShadowTris = gShadowHeapTris[gWaterEffectIndex];
            gCurrShadowVerts = gShadowHeapVerts[gWaterEffectIndex];
            while (i < effect->meshEnd) {
                material_set_no_tex_offset(&gSceneCurrDisplayList, gCurrShadowHeapData[i].texture, flags);
                triCount = gCurrShadowHeapData[i].triCount; // Fakematch
                vtxCount = gCurrShadowHeapData[i].vtxCount; // Fakematch
                numTris = gCurrShadowHeapData[i + 1].triCount - gCurrShadowHeapData[i].triCount;
                numVerts = gCurrShadowHeapData[i + 1].vtxCount - gCurrShadowHeapData[i].vtxCount;
                tri = &gCurrShadowTris[gCurrShadowHeapData[i].triCount];
                vtx = &gCurrShadowVerts[gCurrShadowHeapData[i].vtxCount];
                gSPVertexDKR(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(vtx), numVerts, 0);
                gSPPolygon(gSceneCurrDisplayList++, OS_K0_TO_PHYSICAL(tri), numTris, 1);
                i++;
            }
        }
    }
}

/**
 * Updates shadow and water effect properties for each relevant object in the scene.
 * The first argument decides whether to update shadows for static objects or moving objects.
 * In multiplayer, only important objects get shadows.
 */
void shadow_update(s32 group, s32 waterGroup, s32 updateRate) {
    s32 objIndex;
    s32 objectCount;
    Object *obj;
    ObjectHeader *objHeader;
    f32 dist;
    s32 radius;
    s32 numViewports;
    Object **objects;
    s32 skipShading;
    TextureHeader *waterTex;
    ShadowData *shadow;
    WaterEffect *waterEffect;
    s32 playerIndex;

    gShadowIndex = gShadowHeapFlip;
    if (group == SHADOW_SCENERY) {
        gShadowIndex += 2;
    }
    gCurrShadowTris = (Triangle *) gShadowHeapTris[gShadowIndex];
    gCurrShadowVerts = (Vertex *) gShadowHeapVerts[gShadowIndex];
    gCurrShadowHeapData = (ShadowHeapProperties *) gShadowHeapData[gShadowIndex];
    gShadowTail = 0;
    gNewShadowTriCount = 0;
    gNewShadowVtxCount = 0;
    numViewports = get_viewport_count();
    objects = objGetObjList(&objIndex, &objectCount);
    while (objIndex < objectCount) {
        obj = objects[objIndex];
        objHeader = obj->segment.header;
        waterEffect = obj->waterEffect;
        shadow = obj->shadow;
        objIndex += 1;
        if ((obj->segment.trans.flags & OBJ_FLAGS_PARTICLE)) {
            continue;
        }
        if (shadow != NULL && shadow->scale > 0.0f && group == objHeader->shadowGroup) {
            shadow->meshStart = -1;
        }
        if (obj->segment.trans.flags & OBJ_FLAGS_INVISIBLE) {
            shadow = NULL;
        }
        if ((shadow != NULL && objHeader->shadowGroup == SHADOW_ACTORS) ||
            (waterEffect != NULL && objHeader->waterEffectGroup == SHADOW_ACTORS)) {
            dist = get_distance_to_active_camera(obj->segment.trans.x_position, obj->segment.trans.y_position,
                                                 obj->segment.trans.z_position);
        } else {
            dist = 0;
        }
        if (shadow != NULL && shadow->scale > 0.0f && group == objHeader->shadowGroup) {
            gShadowOpacity = 1.0f;
            shadow->meshStart = -1;
            skipShading = FALSE;
            // Multiplayer
            if (objHeader->shadowGroup == SHADOW_ACTORS && numViewports >= TWO_PLAYERS &&
                numViewports <= FOUR_PLAYERS) {
                if (obj->behaviorId == BHV_RACER) {
                    playerIndex = obj->unk64->racer.playerIndex;
                    if (playerIndex != PLAYER_COMPUTER) {
                        shadow_generate(obj, FALSE);
                        skipShading = TRUE;
                    }
                } else if (obj->behaviorId == BHV_WEAPON) {
                    shadow_generate(obj, FALSE);
                    skipShading = TRUE;
                }
            } else { // Single Player
                radius = objHeader->shadowFadeMin;
                if (dist < radius) {
                    if (objHeader->shadowFadeMax < dist) {
                        gShadowOpacity = (radius - dist) / (radius - objHeader->shadowFadeMax);
                    }
                    shadow_generate(obj, FALSE);
                    skipShading = TRUE;
                }
            }
            if (skipShading == FALSE && obj->shading != NULL) {
                func_8002DE30(obj);
            }
        }
        if (waterEffect != NULL && waterEffect->scale > 0.0f && waterGroup == objHeader->waterEffectGroup) {
            waterEffect->meshStart = -1;
            gShadowOpacity = 1.0f;
            waterTex = waterEffect->texture;
            if (waterTex != NULL && updateRate && waterTex->numOfTextures != 0x100) {
                waterEffect->textureFrame += waterEffect->animationSpeed;
                while (waterTex->numOfTextures < waterEffect->textureFrame) {
                    waterEffect->textureFrame -= waterTex->numOfTextures;
                }
            }

            // Multiplayer
            if (objHeader->shadowGroup == SHADOW_ACTORS && numViewports >= TWO_PLAYERS &&
                numViewports <= FOUR_PLAYERS) {
                if (obj->behaviorId == BHV_RACER) {
                    playerIndex = obj->unk64->racer.playerIndex;
                    if (playerIndex != PLAYER_COMPUTER) {
                        shadow_generate(obj, TRUE);
                    }
                } else if (obj->behaviorId == BHV_WEAPON) {
                    shadow_generate(obj, TRUE);
                }
            } else { // Single Player
                if (dist < objHeader->shadowFadeMin) {
                    if (objHeader->shadowFadeMax < dist) {
                        gShadowOpacity =
                            (objHeader->shadowFadeMin - dist) / (objHeader->shadowFadeMin - objHeader->shadowFadeMax);
                    }
                    shadow_generate(obj, TRUE);
                }
            }
        }
    }
    gCurrShadowHeapData[gShadowTail].triCount = gNewShadowTriCount;
    gCurrShadowHeapData[gShadowTail].vtxCount = gNewShadowVtxCount;
}

void func_8002DE30(Object *obj) {
    s32 sp94;
    s32 sp90;
    s32 blockId;
    s32 var_t3;
    s32 k;
    u32 batchFlags;
    s32 foundResult;
    s32 i;
    LevelModelSegment *block;
    Triangle *triangle;
    Vertex *vertices;
    s32 minYPos;
    s32 maxYPos;
    s32 j;

    sp94 = (s32) obj->segment.trans.y_position + obj->segment.header->unk44;
    sp90 = (s32) obj->segment.trans.y_position + obj->segment.header->unk42;
    blockId = obj->segment.object.segmentID;
    foundResult = FALSE;
    if (blockId != -1) {
        var_t3 = func_800314DC(&gCurrentLevelModel->segmentsBoundingBoxes[blockId],
                               obj->segment.trans.x_position - 16.0f, obj->segment.trans.z_position - 16.0f,
                               obj->segment.trans.x_position + 16.0f, obj->segment.trans.z_position + 16.0f);
        block = &gCurrentLevelModel->segments[blockId];
        for (i = 0; i < block->numberOfBatches && !foundResult; i++) {
            if (!(block->batches[i].flags & (BATCH_FLAGS_HIDDEN | BATCH_FLAGS_RECEIVE_SHADOWS | BATCH_FLAGS_WATER |
                                             BATCH_FLAGS_FORCE_NO_SHADOWS))) {
                batchFlags = (block->batches[i].flags >> 19) &
                             (BATCH_FLAGS_UNK00000001 | BATCH_FLAGS_UNK00000002 | BATCH_FLAGS_UNK00000004);
                vertices = &block->vertices[block->batches[i].verticesOffset];
                for (j = block->batches[i].facesOffset; j < block->batches[i + 1].facesOffset && !foundResult; j++) {
                    blockId = block->unk10[j] & var_t3;
                    if (blockId) {}
                    if (((block->unk10[j] & var_t3) & 0xFF) && ((block->unk10[j] & var_t3) & 0xFF00)) {
                        triangle = &block->triangles[j];
                        minYPos = vertices[triangle->verticesArray[1]].y;
                        maxYPos = minYPos;
                        for (k = 1; k < 3; k++) {
                            if (vertices[triangle->verticesArray[k + 1]].y < minYPos) {
                                minYPos = vertices[triangle->verticesArray[k + 1]].y;
                            } else if (maxYPos < vertices[triangle->verticesArray[k + 1]].y) {
                                maxYPos = vertices[triangle->verticesArray[k + 1]].y;
                            }
                        }
                        if (maxYPos >= sp90 && sp94 >= minYPos) {
                            if (point_triangle_2d_xz_intersection(
                                    obj->segment.trans.x_position, obj->segment.trans.z_position,
                                    &vertices[triangle->verticesArray[1]].x, &vertices[triangle->verticesArray[2]].x,
                                    &vertices[triangle->verticesArray[3]].x)) {
                                foundResult = TRUE;
                                obj->shading->unk0 += (((1.0f - D_800DC884[batchFlags]) - obj->shading->unk0) * 0.2);
                            }
                        }
                    }
                }
            }
        }
    }
}

/**
 * Generate shadow geometry for an object.
 * Handles water effects too, isWater is true.
 */
void shadow_generate(Object *obj, s32 isWater) {
    f32 dist;
    s32 yPos;
    f32 xPos;
    f32 zPos;
    UNUSED s32 *pad;
    s32 cheats;
    s32 inSegs[28];
    s32 i;
    s32 segs;
    f32 character_scale;
    s32 test;

    yPos = obj->segment.trans.y_position;
    character_scale = 1.0f;
    if (obj->behaviorId == BHV_RACER) {
        cheats = get_filtered_cheats();
        if (cheats & CHEAT_BIG_CHARACTERS) {
            character_scale = 1.4f;
        } else if (cheats & CHEAT_SMALL_CHARACTERS) {
            character_scale = 0.714f;
        }
    }

    gNewShadowObj = obj;
    D_8011D0C8 = 2.0f;

    if (isWater) {
        D_8011D0B8 = 0;
        obj->waterEffect->meshStart = gShadowTail;
        gNewShadowTexture = set_animated_texture_header(obj->waterEffect->texture, obj->waterEffect->textureFrame << 8);
        gNewShadowY2 = obj->segment.header->shadowTop + yPos;
        gNewShadowY1 = obj->segment.header->shadowBottom + yPos;
        if (gWaveBlockCount == 0 || get_viewport_count() < VIEWPORTS_COUNT_2_PLAYERS) {
            D_8011D0C8 = 0;
        }
        gNewShadowScale = (obj->waterEffect->scale * character_scale);
        gNewShadowWidth = gNewShadowScale * 10.0f;
        gNewShadowLength = gNewShadowScale * 10.0f;
        D_8011D0F0 = -1.0f;
    } else {
        obj->shadow->meshStart = gShadowTail;
        gNewShadowTexture = obj->shadow->texture;
        gNewShadowY2 = obj->segment.header->unk44 + yPos;
        gNewShadowY1 = obj->segment.header->unk42 + yPos;
        if (obj->behaviorId != BHV_RACER) {
            dist = obj->segment.object.distanceToCamera;
            if (dist < 0.0) {
                dist = -dist;
            }
            dist -= 512.0;
            if (dist < 0.0) {
                dist = 0.0;
            }
            if (dist > 1024.0) {
                dist = 1024.0;
            }
            D_8011D0C8 += (dist * 0.005f);
        }
        gNewShadowScale = (obj->shadow->scale * character_scale);
        gNewShadowWidth = gNewShadowScale * 10.0f;
        gNewShadowLength = gNewShadowScale * 10.0f;
        D_8011D0E4 = 4.0f * gNewShadowWidth * gNewShadowLength;
        D_8011D0F0 = (obj->segment.header->unk42 * 0.125f);
        if (D_8011D0F0 < 0.0f) {
            D_8011D0F0 = -D_8011D0F0;
        }
        D_8011D0F4 = (7.0f * D_8011D0F0);
        D_8011D0D0 = -0x8000;
    }
    gNewShadowScale = 144.0f / gNewShadowScale;
    xPos = gNewShadowObj->segment.trans.x_position;
    zPos = gNewShadowObj->segment.trans.z_position;
    segs = get_inside_segment_count_xyz(inSegs, (xPos - gNewShadowWidth), gNewShadowY1, (zPos - gNewShadowLength),
                                        (xPos + gNewShadowWidth), gNewShadowY2, (zPos + gNewShadowLength));
    D_8011C230 = 0;
    D_8011B118 = 0;
    for (i = 0; i < ARRAY_COUNT(D_8011B320); i++) {
        D_8011B320[i] = 0;
    }
    D_8011D0E8 = -1;
    D_8011D0EC = -1;
    for (i = 0; i < segs; i++) {
        if (inSegs[i] >= 0) {
            if (isWater && (gCurrentLevelModel->segments[inSegs[i]].hasWaves != 0) && (gWaveBlockCount != 0)) {
                func_8002EEEC(inSegs[i]);
            } else {
                test = func_800314DC(&gCurrentLevelModel->segmentsBoundingBoxes[inSegs[i]],
                                     (obj->segment.trans.x_position - gNewShadowWidth),  // x1
                                     (obj->segment.trans.z_position - gNewShadowLength), // z1
                                     (obj->segment.trans.x_position + gNewShadowWidth),  // x2
                                     (obj->segment.trans.z_position + gNewShadowLength)  // z2
                );
                func_8002E904(&gCurrentLevelModel->segments[inSegs[i]], test, isWater);
            }
        }
    }
    if (D_8011C230 > 0) {
        if ((obj->shading != NULL) && isWater == FALSE) {
            obj->shading->unk0 = func_8002FA64();
        }
        func_8002F2AC();
        func_8002F440();
    }
    if (isWater == FALSE) {
        obj->shadow->meshEnd = gShadowTail;
    } else {
        obj->waterEffect->meshEnd = gShadowTail;
    }
}

void func_8002E904(LevelModelSegment *arg0, s32 arg1, s32 arg2) {
    unk8011C8B8 sp100[8];
    Vec2f spD0[4];
    s32 spAC;
    Triangle *triangles;
    s32 nextFacesOffset;
    Vertex *vertices;
    s32 yPos;
    s32 minY;
    s32 foundIndex;
    s32 maxY;
    s32 temp_t6;
    s32 sp88;
    s32 someCount;
    s32 i2;
    s32 i;
    s32 curFacesOffset;

    spD0[0].x = gNewShadowObj->segment.trans.x_position + gNewShadowWidth;
    spD0[0].y = gNewShadowObj->segment.trans.z_position + gNewShadowLength;
    spD0[1].x = gNewShadowObj->segment.trans.x_position - gNewShadowWidth;
    spD0[1].y = gNewShadowObj->segment.trans.z_position + gNewShadowLength;
    spD0[2].x = gNewShadowObj->segment.trans.x_position - gNewShadowWidth;
    spD0[2].y = gNewShadowObj->segment.trans.z_position - gNewShadowLength;
    spD0[3].x = gNewShadowObj->segment.trans.x_position + gNewShadowWidth;
    spD0[3].y = gNewShadowObj->segment.trans.z_position - gNewShadowLength;

    for (spAC = 0; spAC < arg0->numberOfBatches; spAC++) {
        if ((arg2 && (arg0->batches[spAC].flags & BATCH_FLAGS_WATER)) ||
            (!arg2 && !(arg0->batches[spAC].flags & FLAGS_8002E904))) {
            curFacesOffset = arg0->batches[spAC].facesOffset;
            nextFacesOffset = arg0->batches[spAC + 1].facesOffset;
            vertices = &arg0->vertices[arg0->batches[spAC].verticesOffset];
            sp88 = (arg0->batches[spAC].flags >> 0x13) & 7;
            for (; curFacesOffset < nextFacesOffset; curFacesOffset++) {
                if (((arg0->unk10[curFacesOffset] & arg1) & 0xFF) && ((arg0->unk10[curFacesOffset] & arg1) & 0xFF00)) {
                    triangles = &arg0->triangles[curFacesOffset];
                    maxY = minY = vertices[triangles->verticesArray[1]].y;
                    for (i = 1; i < 3; i++) {
                        yPos = vertices[triangles->verticesArray[i + 1]].y;
                        if (yPos < minY) {
                            minY = yPos;
                        } else if (maxY < yPos) {
                            maxY = yPos;
                        }
                    }
                    if (gNewShadowY2 >= minY) {
                        if (maxY >= gNewShadowY1) {
                            for (i = 0; i < 3; i++) {
                                sp100[i].unk0 = vertices[triangles->verticesArray[i + 1]].x;
                                sp100[i].unk8 = vertices[triangles->verticesArray[i + 1]].z;
                                sp100[i].unkE = -1;
                            }
                            // @note while the cast to Vec4f is incorrect, func_8002FD74 only uses unk0 and unk8 which
                            // are both floats so this is fine as the size is the same
                            if (func_8002FD74(spD0[2].x, spD0[2].y, spD0[0].x, spD0[0].y, 3, (Vec4f *) sp100) != 0) {
                                temp_t6 = arg0->unk14[curFacesOffset].triangleIndex * 4;
                                D_8011D0BC = (unk8011C8B8 *) &(arg0->unk18)[temp_t6];
                                if (arg0->unk18[temp_t6 + 1] != 0) {
                                    if (D_8011D0F0 > 0.0f) {
                                        func_800304C8(sp100);
                                    }
                                    someCount = func_8002FF6C(3, sp100, 4, spD0);
                                    if (someCount >= 3) {
                                        D_8011C238[D_8011C230].unk1 = 0;
                                        for (i2 = 0; i2 < someCount; i2++) {
                                            if (sp100[i2].unkE < 0) {
                                                foundIndex = -1;
                                                i = 0;
                                                while ((i < D_8011B118) && (foundIndex == -1)) {
                                                    if ((D_8011B120[i].x == sp100[i2].unk0) &&
                                                        (D_8011B120[i].z == sp100[i2].unk8)) {
                                                        foundIndex = i;
                                                    }
                                                    i++;
                                                }
                                                if (foundIndex == -1) {
                                                    D_8011B120[D_8011B118].x = sp100[i2].unk0;
                                                    D_8011B120[D_8011B118].unkC = D_8011D0BC;
                                                    D_8011B120[D_8011B118].z = sp100[i2].unk8;
                                                    D_8011C238[D_8011C230].unk2[i2] = D_8011B118++;
                                                } else {
                                                    D_8011C238[D_8011C230].unk2[i2] = foundIndex;
                                                }
                                            } else {
                                                D_8011C238[D_8011C230].unk2[i2] = sp100[i2].unkE;
                                                D_8011C238[D_8011C230].unk1 |= 1 << i2;
                                            }
                                        }
                                        D_8011C238[D_8011C230].unk0 = someCount;
                                        D_8011C238[D_8011C230].unkA = sp88;
                                        D_8011C230 += 1;
                                        if ((D_8011D0E8 >= 0) && (sp88 != D_8011D0E8)) {
                                            D_8011D0EC = 0;
                                        }
                                        D_8011D0E8 = sp88;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void func_8002EEEC(s32 arg0) {
    unk8011C8B8 spA8[8];
    Vec2f sp88[4];
    s32 var_v0;
    s32 var_a0;
    s32 var_a1;
    s32 temp_v0;
    s32 temp_v0_3;
    s32 var_s4;
    s32 var_t1;
    s32 var_v1;
    s32 tempIdx;

    sp88[0].x = gNewShadowObj->segment.trans.x_position + gNewShadowWidth;
    sp88[0].y = gNewShadowObj->segment.trans.z_position + gNewShadowLength;
    sp88[1].x = gNewShadowObj->segment.trans.x_position - gNewShadowWidth;
    sp88[1].y = gNewShadowObj->segment.trans.z_position + gNewShadowLength;
    sp88[2].x = gNewShadowObj->segment.trans.x_position - gNewShadowWidth;
    sp88[2].y = gNewShadowObj->segment.trans.z_position - gNewShadowLength;
    sp88[3].x = gNewShadowObj->segment.trans.x_position + gNewShadowWidth;
    sp88[3].y = gNewShadowObj->segment.trans.z_position - gNewShadowLength;
    // clang-format off
    temp_v0 = func_800BDC80(
        arg0, D_8011C3B8, &D_8011C8B8[D_8011D0B8],
        sp88[2].x, sp88[2].y,
        sp88[0].x, sp88[0].y
    );
    // clang-format on

    for (var_s4 = 0; var_s4 < temp_v0; var_s4++) {
        var_a0 = D_8011C3B8[var_s4].unk2;
        var_a1 = D_8011C3B8[var_s4].unk2;
        if (D_8011C3B8[var_s4].unk8 < var_a1) {
            var_a0 = D_8011C3B8[var_s4].unk8;
        } else if (var_a1 < D_8011C3B8[var_s4].unk8) {
            var_a1 = D_8011C3B8[var_s4].unk8;
        }
        if (D_8011C3B8[var_s4].unkE < var_a0) {
            var_a0 = D_8011C3B8[var_s4].unkE;
        } else if (var_a1 < D_8011C3B8[var_s4].unkE) {
            var_a1 = D_8011C3B8[var_s4].unkE;
        }
        if (gNewShadowY2 >= var_a0) {
            if (var_a1 >= gNewShadowY1) {
                spA8[0].unk0 = D_8011C3B8[var_s4].unk0;
                spA8[0].unk8 = D_8011C3B8[var_s4].unk4;
                spA8[1].unk0 = D_8011C3B8[var_s4].unk6;
                spA8[1].unk8 = D_8011C3B8[var_s4].unkA;
                spA8[2].unk0 = D_8011C3B8[var_s4].unkC;
                spA8[2].unk8 = D_8011C3B8[var_s4].unk10;

                for (var_v0 = 0; var_v0 != 3; var_v0++) {
                    spA8[var_v0].unkE = -1;
                }

                D_8011D0BC = &D_8011C8B8[D_8011D0B8 + var_s4];
                temp_v0_3 = func_8002FF6C(3, spA8, 4, sp88);
                if (temp_v0_3 >= 3) {
                    tempIdx = D_8011C230;
                    D_8011C238[tempIdx].unk1 = 0;
                    for (var_t1 = 0; var_t1 < temp_v0_3; var_t1++) {
                        if (spA8[var_t1].unkE < 0) {
                            var_a1 = -1;
                            var_v1 = 0;
                            while (var_v1 < D_8011B118 && var_a1 == -1) {
                                if ((D_8011B120[var_v1].x == spA8[var_t1].unk0) &&
                                    (D_8011B120[var_v1].z == spA8[var_t1].unk8)) {
                                    var_a1 = var_v1;
                                }
                                var_v1++;
                            }
                            if (var_a1 == -1) {
                                D_8011B120[D_8011B118].x = spA8[var_t1].unk0;
                                D_8011B120[D_8011B118].unkC = D_8011D0BC;
                                D_8011B120[D_8011B118].z = spA8[var_t1].unk8;
                                D_8011C238[tempIdx].unk2[var_t1] = D_8011B118++;
                            } else {
                                D_8011C238[tempIdx].unk2[var_t1] = var_a1;
                            }
                        } else {
                            D_8011C238[tempIdx].unk2[var_t1] = spA8[var_t1].unkE;
                            D_8011C238[tempIdx].unk1 |= 1 << var_t1;
                        }
                    }
                    D_8011C230 = tempIdx + 1;
                    D_8011C238[tempIdx].unk0 = temp_v0_3;
                }
            }
        }
    }

    D_8011D0B8 += temp_v0;
}

#ifdef NON_EQUIVALENT
void func_8002F2AC(void) {
    f32 temp_f12;
    f32 temp_f16;
    unk8011C8B8 *var_v0;
    s32 i, j;

    for (i = 0; i < D_8011B118; i++) {
        var_v0 = D_8011B120[i].unkC;
        temp_f16 = D_8011B120[i].x * var_v0->unk0;
        temp_f12 = D_8011B120[i].z * var_v0->unk8;
        D_8011B120[i].y = (f32) (-(temp_f16 + temp_f12 + var_v0->unkC) / var_v0->unk4);
    }

    for (i = 0; i < ARRAY_COUNT(D_8011B320); i++) {
        for (j = 0; j < D_8011B320[i]; j++) {
            var_v0 = D_8011B330[j + i].unkC;
            temp_f16 = D_8011B330[j + i].x * var_v0->unk0;
            temp_f12 = D_8011B330[j + i].z * var_v0->unk8;
            D_8011B330[j + i].y = (f32) (-(temp_f16 + temp_f12 + var_v0->unkC) / var_v0->unk4);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/tracks/func_8002F2AC.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/tracks/func_8002F440.s")

// Transition points between different lighting levels, used by certain objects
f32 func_8002FA64(void) {
    f32 var_f2;
    f32 x0, z0, x1, z1, x2, z2;
    s32 temp_t5;
    s32 var_s2;
    s32 i;

    var_f2 = 0.0f;
    if (D_8011C230 > 0) {
        if (D_8011D0EC != 0) {
            if (D_8011D0E8 > 0) {
                var_f2 = D_800DC884[D_8011D0E8] * D_8011D0E4;
            }
        } else {
            for (i = 0; i < D_8011C230; i++) {
                if (D_8011C238[i].unkA > 0) {
                    temp_t5 = D_8011C238[i].unk1;
                    if (temp_t5 & 1) {
                        x0 = D_8011B330[D_8011C238[i].unk2[0]].x;
                        z0 = D_8011B330[D_8011C238[i].unk2[0]].z;
                    } else {
                        x0 = D_8011B120[D_8011C238[i].unk2[0]].x;
                        z0 = D_8011B120[D_8011C238[i].unk2[0]].z;
                    }
                    temp_t5 >>= 1;
                    if (temp_t5 & 1) {
                        x1 = D_8011B330[D_8011C238[i].unk2[1]].x;
                        z1 = D_8011B330[D_8011C238[i].unk2[1]].z;
                    } else {
                        x1 = D_8011B120[D_8011C238[i].unk2[1]].x;
                        z1 = D_8011B120[D_8011C238[i].unk2[1]].z;
                    }
                    temp_t5 >>= 1;
                    for (var_s2 = 2; var_s2 < D_8011C238[i].unk0; var_s2++) {
                        if (temp_t5 & 1) {
                            x2 = D_8011B330[D_8011C238[i].unk2[var_s2]].x;
                            z2 = D_8011B330[D_8011C238[i].unk2[var_s2]].z;
                        } else {
                            x2 = D_8011B120[D_8011C238[i].unk2[var_s2]].x;
                            z2 = D_8011B120[D_8011C238[i].unk2[var_s2]].z;
                        }
                        temp_t5 >>= 1;
                        var_f2 += area_triangle_2d(x0, z0, x1, z1, x2, z2) * D_800DC884[D_8011C238[i].unkA];
                        x1 = x2;
                        z1 = z2;
                    }
                }
            }
        }

        if (D_8011D0E4 < var_f2) {
            var_f2 = D_8011D0E4 * 0.99f;
        }
    }
    return (D_8011D0E4 - var_f2) / D_8011D0E4;
}

s32 func_8002FD74(f32 x0, f32 z0, f32 x1, f32 x2, s32 count, Vec4f *arg5) {
    if (count > 0) {
        f32 minX = arg5[0].x;
        f32 maxX = arg5[0].x;
        f32 minZ = arg5[0].z;
        f32 maxZ = arg5[0].z;
        s32 i;

        for (i = 1; i < count; i++) {
            if (arg5[i].x < minX) {
                minX = arg5[i].x;
            } else if (maxX < arg5[i].x) {
                maxX = arg5[i].x;
            }
            if (arg5[i].z < minZ) {
                minZ = arg5[i].z;
            } else if (maxZ < arg5[i].z) {
                maxZ = arg5[i].z;
            }
        }

        if ((x0 <= maxX) && (z0 <= maxZ) && (minX <= x1) && (minZ <= x2)) {
            return -1;
        }
    }

    return 0;
}

// arg0 is always 3
// arg1 always has size 8 (that's why spE0 is also of size 8)
// arg2 is always 4
// arg3 always has size 4
s32 func_8002FF6C(s32 arg0, unk8011C8B8 *arg1, s32 arg2, Vec2f *arg3) {
    unk8011C8B8 spE0[8];
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f22;
    f32 temp_f24;
    f32 var_f2;
    s32 var_a1;
    s32 var_v1_3;
    s32 var_a0;
    s32 var_t2;
    UNUSED s32 var_t5;
    s32 var_v0;
    s32 var_v1;
    s32 var_t1;
    s32 var_s2;
    unk8011C8B8 *var_s0;
    unk8011C8B8 *var_s3;
    unk8011C8B8 *swap; // swap var for var_s0 and var_s3

    var_s3 = arg1;
    var_s0 = spE0;
    var_s2 = arg0;
    var_v0 = 0;

    while (var_v0 < arg2 && var_s2 >= 3) {
        var_v1 = var_v0 + 1;
        if (var_v1 >= arg2) {
            var_v1 = 0;
        }

        temp_f12 = arg3[var_v1].y - arg3[var_v0].y;
        temp_f14 = -(arg3[var_v1].x - arg3[var_v0].x);
        if (arg3[var_v0].x < arg3[var_v1].x) {
            var_f2 = (temp_f12 * arg3[var_v0].x) + (arg3[var_v0].y * temp_f14);
            var_f2 = -var_f2;
        } else {
            var_f2 = (temp_f12 * arg3[var_v1].x) + (arg3[var_v1].y * temp_f14);
            var_f2 = -var_f2;
        }

        for (var_t1 = 0, var_t2 = 0; var_t1 < var_s2; var_t1++) {
            var_v1 = var_t1 + 1;
            if (var_v1 >= var_s2) {
                var_v1 = 0;
            }
            temp_f16 = (temp_f12 * var_s3[var_t1].unk0) + (var_s3[var_t1].unk8 * temp_f14) + var_f2;
            temp_f22 = (temp_f12 * var_s3[var_v1].unk0) + (var_s3[var_v1].unk8 * temp_f14) + var_f2;
            if ((temp_f16 >= 0.0f && temp_f22 < 0.0f) || (temp_f16 < 0.0f && temp_f22 >= 0.0f)) {
                var_a0 = D_8011B320[var_v0];
                var_a1 = -1;
                var_v1_3 = var_v0 << 5;
                while (var_a0 > 0 && var_a1 < 0) {
                    if ((D_8011B330[var_v1_3].unk10 == var_s3[var_t1].unk0) &&
                        (D_8011B330[var_v1_3].unk14 == var_s3[var_t1].unk8) &&
                        (D_8011B330[var_v1_3].unk18 == var_s3[var_v1].unk0) &&
                        (D_8011B330[var_v1_3].unk1C == var_s3[var_v1].unk8)) {
                        var_a1 = var_v1_3;
                    } else if ((D_8011B330[var_v1_3].unk10 == var_s3[var_v1].unk0) &&
                               (D_8011B330[var_v1_3].unk14 == var_s3[var_v1].unk8) &&
                               (D_8011B330[var_v1_3].unk18 == var_s3[var_t1].unk0) &&
                               (D_8011B330[var_v1_3].unk1C == var_s3[var_t1].unk8)) {
                        var_a1 = var_v1_3;
                    }
                    var_a0 -= 1;
                    var_v1_3++;
                }
                if (var_a1 >= 0) {
                    var_s0[var_t2].unkE = var_a1;
                    var_s0[var_t2].unk0 = D_8011B330[var_a1].x;
                    var_s0[var_t2].unk8 = D_8011B330[var_a1].z;
                    var_t2++;
                } else {
                    temp_f24 = temp_f16 / (temp_f16 - temp_f22);
                    var_s0[var_t2].unk0 =
                        var_s3[var_t1].unk0 + ((var_s3[var_v1].unk0 - var_s3[var_t1].unk0) * temp_f24);
                    var_s0[var_t2].unk8 =
                        var_s3[var_t1].unk8 + ((var_s3[var_v1].unk8 - var_s3[var_t1].unk8) * temp_f24);
                    if (D_8011B320[var_v0] > 0x1F) {
                        D_8011B320[var_v0] = 0x1F;
                    }
                    var_v1_3 = D_8011B320[var_v0] + (var_v0 << 5);
                    D_8011B330[var_v1_3].unk10 = var_s3[var_t1].unk0;
                    D_8011B330[var_v1_3].unk14 = var_s3[var_t1].unk8;
                    D_8011B330[var_v1_3].unk18 = var_s3[var_v1].unk0;
                    D_8011B330[var_v1_3].unk1C = var_s3[var_v1].unk8;
                    D_8011B330[var_v1_3].x = var_s0[var_t2].unk0;
                    D_8011B330[var_v1_3].z = var_s0[var_t2].unk8;
                    D_8011B330[var_v1_3].unkC = D_8011D0BC;
                    D_8011B320[var_v0]++;
                    var_s0[var_t2].unkE = var_v1_3;
                    var_t2++;
                }
            }
            if (temp_f22 <= 0.0f) {
                var_s0[var_t2].unkE = var_s3[var_v1].unkE;
                var_s0[var_t2].unk0 = var_s3[var_v1].unk0;
                var_s0[var_t2].unk8 = var_s3[var_v1].unk8;
                var_t2++;
            }
        }
        var_s2 = var_t2;
        var_v0++;

        swap = var_s3;
        var_s3 = var_s0;
        var_s0 = swap;
    }

    if (var_s2 >= 3) {
        if (var_s3 != arg1) {
            for (var_t1 = 0; var_t1 < var_s2; var_t1++) {
                arg1[var_t1].unk0 = var_s3[var_t1].unk0;
                arg1[var_t1].unk8 = var_s3[var_t1].unk8;
                arg1[var_t1].unkE = var_s3[var_t1].unkE;
            }
        }
    } else {
        var_s2 = 0;
    }
    return var_s2;
}

#ifdef NON_EQUIUVALENT
void func_800304C8(unk8011C8B8 *arg0) {
    s16 found1;
    s16 found2;
    s16 found3;
    f32 temp;
    f32 arg02x;
    f32 arg00z;
    f32 compare;

    found1 = FALSE;
    found2 = FALSE;
    found3 = FALSE;
    temp = arg0[0].z;
    arg00z = temp;
    compare = 0.0f;
    temp = (gNewShadowObj->segment.trans.z_position - arg0[1].z);

    if ((((gNewShadowObj->segment.trans.x_position - arg0[0].x) * (arg0[1].z - arg00z)) -
         ((arg0[1].x - arg0[0].x) * (((0, gNewShadowObj->segment.trans.z_position)) - arg00z))) >= compare) {
        found1 = TRUE;
    }
    if ((((gNewShadowObj->segment.trans.x_position - arg0[1].x) * (arg0[2].z - arg0[1].z)) -
         (temp * (arg0[2].x - arg0[1].x))) >= compare) {
        found2 = TRUE;
    }
    arg02x = arg0[2].x;
    if (found1 == found2) {
        f32 zPosDiff = (arg00z - arg0[2].z);
        if ((((gNewShadowObj->segment.trans.x_position - arg02x) * zPosDiff) -
             ((arg0[0].x - arg02x) * (arg02x - arg0[2].z))) >= compare) {
            found3 = TRUE;
        }
        if (found2 == found3) {
            f32 test = (-(((D_8011D0BC->x * gNewShadowObj->segment.trans.x_position) +
                           (D_8011D0BC->z * gNewShadowObj->segment.trans.z_position)) +
                          D_8011D0BC->w)) /
                       D_8011D0BC->y;
            if (D_8011D0D0 < test) {
                D_8011D0D0 = test;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/tracks/func_800304C8.s")
#endif

/**
 * Instantly update current fog properties.
 * Official Name: trackSetFog
 */
void set_fog(s32 fogIdx, s16 near, s16 far, u8 red, u8 green, u8 blue) {
    s32 tempNear;
    FogData *fogData;

    fogData = &gFogData[fogIdx];

    if (far < near) {
        tempNear = near;
        near = far;
        far = tempNear;
    }

    if (far > 1023) {
        far = 1023;
    }
    if (near >= far - 5) {
        near = far - 5;
    }

    fogData->addFog.near = 0;
    fogData->addFog.far = 0;
    fogData->addFog.r = 0;
    fogData->addFog.g = 0;
    fogData->addFog.b = 0;
    fogData->fog.r = red << 16;
    fogData->fog.g = green << 16;
    fogData->fog.b = blue << 16;
    fogData->fog.near = near << 16;
    fogData->fog.far = far << 16;
    fogData->intendedFog.r = red;
    fogData->intendedFog.g = green;
    fogData->intendedFog.b = blue;
    fogData->intendedFog.near = near;
    fogData->intendedFog.far = far;
    fogData->switchTimer = 0;
    fogData->fogChanger = NULL;
}

/**
 * Writes the current fog settings to the arguments.
 * Pre-shifts the data, so the raw values are correct.
 * Official Name: trackGetFog
 */
void get_fog_settings(s32 playerID, s16 *near, s16 *far, u8 *r, u8 *g, u8 *b) {
    *near = gFogData[playerID].fog.near >> 16;
    *far = gFogData[playerID].fog.far >> 16;
    *r = gFogData[playerID].fog.r >> 16;
    *g = gFogData[playerID].fog.g >> 16;
    *b = gFogData[playerID].fog.b >> 16;
}

/**
 * Sets the fog of the player ID to the default values.
 * Current fog attributes are rightshifted 16 bytes.
 * Official Name: trackSetFogOff
 */
void reset_fog(s32 playerID) {
    gFogData[playerID].addFog.near = 0;
    gFogData[playerID].addFog.far = 0;
    gFogData[playerID].addFog.r = 0;
    gFogData[playerID].addFog.g = 0;
    gFogData[playerID].addFog.b = 0;
    gFogData[playerID].fog.near = 1018 << 16;
    gFogData[playerID].fog.far = 1023 << 16;
    gFogData[playerID].intendedFog.r = gFogData[playerID].fog.r >> 16;
    gFogData[playerID].intendedFog.g = gFogData[playerID].fog.g >> 16;
    gFogData[playerID].intendedFog.b = gFogData[playerID].fog.b >> 16;
    gFogData[playerID].intendedFog.near = 1018;
    gFogData[playerID].intendedFog.far = 1023;
    gFogData[playerID].switchTimer = 0;
    gFogData[playerID].fogChanger = NULL;
}

/**
 * If the fog override timer is active, apply that and slowly degrade.
 * Otherwise, set the current fog to the intended fog settings.
 */
void update_fog(s32 viewportCount, s32 updateRate) {
    s32 i;
    for (i = 0; i < viewportCount; i++) {
        if (gFogData[i].switchTimer > 0) {
            if (updateRate < gFogData[i].switchTimer) {
                gFogData[i].fog.r += gFogData[i].addFog.r * updateRate;
                gFogData[i].fog.g += gFogData[i].addFog.g * updateRate;
                gFogData[i].fog.b += gFogData[i].addFog.b * updateRate;
                gFogData[i].fog.near += gFogData[i].addFog.near * updateRate;
                gFogData[i].fog.far += gFogData[i].addFog.far * updateRate;
                gFogData[i].switchTimer -= updateRate;
            } else {
                gFogData[i].fog.r = gFogData[i].intendedFog.r << 16;
                gFogData[i].fog.g = gFogData[i].intendedFog.g << 16;
                gFogData[i].fog.b = gFogData[i].intendedFog.b << 16;
                gFogData[i].fog.near = gFogData[i].intendedFog.near << 16;
                gFogData[i].fog.far = gFogData[i].intendedFog.far << 16;
                gFogData[i].switchTimer = 0;
            }
        }
    }
}

/**
 * Sets the fog settings for the active viewport based on the parameters of the environment data.
 */
void apply_fog(s32 playerID) {
    gDPSetFogColor(gSceneCurrDisplayList++, gFogData[playerID].fog.r >> 0x10, gFogData[playerID].fog.g >> 0x10,
                   gFogData[playerID].fog.b >> 0x10, 0xFF);
    gSPFogPosition(gSceneCurrDisplayList++, gFogData[playerID].fog.near >> 0x10, gFogData[playerID].fog.far >> 0x10);
}

/**
 * Sets the active viewport's fog target when passed through.
 * Used in courses to make less, or more dense.
 * @bug: Timer doesn't account for PAL, meaning fog will scroll 20% slower on PAL systems.
 * Official Name: trackChangeFog
 */
void obj_loop_fogchanger(Object *obj) {
    s32 nearTemp;
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
    s32 switchTimer;
    LevelObjectEntry_FogChanger *fogChanger;
    Object **racers;
    Object_Racer *racer;
    UNUSED s32 pad2;
    FogData *fog;
    ObjectSegment *camera;

    racers = NULL;
    fogChanger = (LevelObjectEntry_FogChanger *) obj->segment.level_entry;
    camera = NULL;

    if (check_if_showing_cutscene_camera()) {
        camera = get_cutscene_camera_segment();
        views = get_viewport_count() + 1;
    } else {
        racers = get_racer_objects(&views);
    }

    for (i = 0; i < views; i++) {
        index = PLAYER_COMPUTER;
        if (racers != NULL) {
            racer = &racers[i]->unk64->racer;
            playerIndex = racer->playerIndex;
            if (playerIndex >= PLAYER_ONE && playerIndex <= PLAYER_FOUR && obj != gFogData[playerIndex].fogChanger) {
                index = playerIndex;
                x = racers[i]->segment.trans.x_position;
                z = racers[i]->segment.trans.z_position;
            }
        } else if (i <= PLAYER_FOUR && obj != gFogData[i].fogChanger) {
            index = i;
            x = camera[i].trans.x_position;
            z = camera[i].trans.z_position;
        }
        if (index != PLAYER_COMPUTER) {
            x -= obj->segment.trans.x_position;
            z -= obj->segment.trans.z_position;
            if (1) {} // Fakematch
            if ((x * x) + (z * z) < obj->properties.distance.radius) {
                fogNear = fogChanger->near;
                fogFar = fogChanger->far;
                fogR = fogChanger->r;
                fogG = fogChanger->g;
                fogB = fogChanger->b;
                switchTimer = fogChanger->switchTimer;
                // Swap near and far if they're the wrong way around.
                if (fogFar < fogNear) {
                    nearTemp = fogNear;
                    fogNear = fogFar;
                    fogFar = nearTemp;
                }
                if (fogFar > 1023) {
                    fogFar = 1023;
                }
                if (fogNear >= fogFar - 5) {
                    fogNear = fogFar - 5;
                }
                fog = &gFogData[index];
                fog->intendedFog.r = fogR;
                fog->intendedFog.g = fogG;
                fog->intendedFog.b = fogB;
                fog->intendedFog.near = fogNear;
                fog->intendedFog.far = fogFar;
                fog->addFog.r = ((fogR << 16) - fog->fog.r) / switchTimer;
                fog->addFog.g = ((fogG << 16) - fog->fog.g) / switchTimer;
                fog->addFog.b = ((fogB << 16) - fog->fog.b) / switchTimer;
                fog->addFog.near = ((fogNear << 16) - fog->fog.near) / switchTimer;
                fog->addFog.far = ((fogFar << 16) - fog->fog.far) / switchTimer;
                fog->switchTimer = switchTimer;
                fog->fogChanger = obj;
            }
        }
    }
}

/**
 * Set the fog properties from the current values to the target, over a time specified by switchTimer.
 * @bug: Timer doesn't account for PAL, meaning fog will scroll 20% slower on PAL systems.
 * Official Name: trackFadeFog
 */
void slowly_change_fog(s32 fogIdx, s32 red, s32 green, s32 blue, s32 near, s32 far, s32 switchTimer) {
    s32 temp;
    FogData *fogData;

    fogData = &gFogData[fogIdx];

    if (far < near) {
        temp = near;
        near = far;
        far = temp;
    }

    if (far > 1023) {
        far = 1023;
    }
    if (near >= far - 5) {
        near = far - 5;
    }

    fogData->intendedFog.r = red;
    fogData->intendedFog.g = green;
    fogData->intendedFog.b = blue;
    fogData->intendedFog.near = near;
    fogData->intendedFog.far = far;
    fogData->addFog.r = ((red << 16) - fogData->fog.r) / switchTimer;
    fogData->addFog.g = ((green << 16) - fogData->fog.g) / switchTimer;
    fogData->addFog.b = ((blue << 16) - fogData->fog.b) / switchTimer;
    fogData->addFog.near = ((near << 16) - fogData->fog.near) / switchTimer;
    fogData->addFog.far = ((far << 16) - fogData->fog.far) / switchTimer;
    fogData->switchTimer = switchTimer;
    fogData->fogChanger = NULL;
}

/**
 * Updates the stored perspective of the camera, as well as the envmap values derived from it.
 */
UNUSED void update_perspective_and_envmap(void) {
    gSceneActiveCamera = get_active_camera_segment();
    compute_scene_camera_transform_matrix();
    update_envmap_position((f32) gScenePerspectivePos.x / 65536.0f, (f32) gScenePerspectivePos.y / 65536.0f,
                           (f32) gScenePerspectivePos.z / 65536.0f);
}

/**
 * Take the current camera position and calculate the perspective position, for envmapping.
 */
void compute_scene_camera_transform_matrix(void) {
    Matrix mtx;
    ObjectTransform trans;

    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = -65536.0f;

    trans.rotation.z_rotation = gSceneActiveCamera->trans.rotation.z_rotation;
    trans.rotation.x_rotation = gSceneActiveCamera->trans.rotation.x_rotation;
    trans.rotation.y_rotation = gSceneActiveCamera->trans.rotation.y_rotation;
    trans.x_position = 0.0f;
    trans.y_position = 0.0f;
    trans.z_position = 0.0f;
    trans.scale = 1.0f;

    object_transform_to_matrix(mtx, &trans);
    guMtxXFMF(mtx, x, y, z, &x, &y, &z);

    // Store x/y/z as integers
    gScenePerspectivePos.x = x;
    gScenePerspectivePos.y = y;
    gScenePerspectivePos.z = z;
}
