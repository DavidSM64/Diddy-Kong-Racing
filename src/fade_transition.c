#include "fade_transition.h"

#include "types.h"
#include "macros.h"
#include "f3ddkr.h"
#include "asset_enums.h"
#include "memory.h"
#include "video.h"
#include "textures_sprites.h"
#include "math_util.h"
#include "PRinternal/viint.h"

/************ .data ************/

s32 gTransitionsDisabled = FALSE;
s32 sLevelTransitionDelayTimer = 0; // Set when a level is loaded after a transition, to hold it for a few extra frames.
s32 gTransitionInvert = 0;
s32 sTransitionStatus = TRANSITION_NONE;
u16 sTransitionFadeTimer = 0;
u16 gTransitionEndTimer = 0;
u16 sTransitionFadeDuration = 0;
s8 gTransitionFadeIn = 0;
Vertex *sTransitionVtx[2] = { NULL, NULL };
Triangle *sTransitionTris[2] = { NULL, NULL };
s32 sTransitionTaskNum = 0;

Gfx dTransitionFadeSettings[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
    gsSPEndDisplayList(),
};

Vec2s gTransitionBarnHorizontalCoords[14] = {
    { -480, 120 },  { -320, 120 },  { -160, 120 },  { 0, 120 },  { 160, 120 },  { 320, 120 },  { 480, 120 },
    { -480, -120 }, { -320, -120 }, { -160, -120 }, { 0, -120 }, { 160, -120 }, { 320, -120 }, { 480, -120 },
};

Vec2s gTransitionBarnVerticalCoords[14] = {
    { -160, 360 }, { -160, 240 }, { -160, 120 }, { -160, 0 }, { -160, -120 }, { -160, -240 }, { -160, -240 },
    { 160, 360 },  { 160, 240 },  { 160, 120 },  { 160, 0 },  { 160, -120 },  { 160, -240 },  { 160, -240 },
};

TriangleList D_800E32A0[12] = {
    0, 2, 4, 14, 16, 18, 8, 10, 12, 22, 24, 26,
};

TriangleList D_800E32AC[12] = {
    4, 6, 8, 18, 20, 22, 4, 6, 8, 18, 20, 22,
};

TriangleList gTransitionBarnDoorTris[24] = {
    0, 3, 1, 1, 3, 4, 1, 4, 2, 2, 4, 5, 6, 9, 7, 7, 9, 10, 7, 10, 8, 8, 10, 11,
};

u8 gTransitionBarnDoorAlpha[12] = {
    255, 255, 0, 255, 255, 0, 0, 255, 255, 0, 255, 255,
};

Vec2s gTransitionBarnDiagCoords[12] = {
    { -800, 120 },  { -480, 120 },  { -160, 120 },  { 160, 120 },  { 480, 120 },  { 800, 120 },
    { -800, -120 }, { -480, -120 }, { -160, -120 }, { 160, -120 }, { 480, -120 }, { 800, -120 },
};

TriangleList D_800E330C[12] = {
    0, 2, 4, 12, 14, 8, 10, 18, 20, 22, 0, 0,
};

TriangleList D_800E3318[12] = {
    4, 6, 8, 16, 18, 4, 6, 14, 16, 18, 0, 0,
};

TriangleList gTransitionBarnDoorDiagTris[20] = {
    0, 1, 3, 1, 3, 4, 1, 4, 2, 5, 7, 8, 5, 8, 6, 6, 8, 9, 0, 0,
};

u8 gTransitionBarnDoorDiagAlpha[12] = {
    255, 255, 0, 255, 0, 0, 255, 0, 255, 255, 0, 0,
};

Vec2s gTransitionWaveCoords[63] = {
    { -160, 160 },  { -144, 160 },  { -128, 160 },  { -112, 160 },  { -96, 160 },  { -80, 160 },  { -64, 160 },
    { -48, 160 },   { -32, 160 },   { -16, 160 },   { 0, 160 },     { 16, 160 },   { 32, 160 },   { 48, 160 },
    { 64, 160 },    { 80, 160 },    { 96, 160 },    { 112, 160 },   { 128, 160 },  { 144, 160 },  { 160, 160 },
    { -160, -200 }, { -144, -160 }, { -128, -140 }, { -112, -130 }, { -96, -140 }, { -80, -200 }, { -64, -240 },
    { -48, -260 },  { -32, -270 },  { -16, -260 },  { 0, -220 },    { 16, -210 },  { 32, -200 },  { 48, -210 },
    { 64, -220 },   { 80, -260 },   { 96, -270 },   { 112, -260 },  { 128, -220 }, { 144, -160 }, { 160, -140 },
    { -160, -280 }, { -144, -280 }, { -128, -280 }, { -112, -280 }, { -96, -280 }, { -80, -280 }, { -64, -280 },
    { -48, -280 },  { -32, -280 },  { -16, -280 },  { 0, -280 },    { 16, -280 },  { 32, -280 },  { 48, -280 },
    { 64, -280 },   { 80, -280 },   { 96, -280 },   { 112, -280 },  { 128, -280 }, { 144, -280 }, { 160, -280 }
};

u8 D_800E3440[92] = {
    0,  2,   4,   6,   8,   10,  12,  14, 0,  2,  4,  6,  8,  10, 12, 14,  14,  16,  18,  20,  22,  24,  26,
    14, 16,  18,  20,  22,  24,  26,  26, 28, 30, 32, 34, 36, 38, 40, 26,  28,  30,  32,  34,  36,  38,  40,
    0,  2,   4,   6,   8,   10,  12,  14, 84, 86, 88, 90, 92, 94, 96, 98,  14,  16,  18,  20,  22,  24,  26,
    98, 100, 102, 104, 106, 108, 110, 26, 28, 30, 32, 34, 36, 38, 40, 110, 112, 114, 116, 118, 120, 122, 124,
};

u8 D_800E349C[92] = {
    42, 44,  46,  48,  50,  52,  54,  56,  84,  86,  88,  90,  92,  94,  96,  98,  56,  58,  60,  62,  64,  66,  68,
    98, 100, 102, 104, 106, 108, 110, 68,  70,  72,  74,  76,  78,  80,  82,  110, 112, 114, 116, 118, 120, 122, 124,
    84, 86,  88,  90,  92,  94,  96,  98,  84,  86,  88,  90,  92,  94,  96,  98,  98,  100, 102, 104, 106, 108, 110,
    98, 100, 102, 104, 106, 108, 110, 110, 112, 114, 116, 118, 120, 122, 124, 110, 112, 114, 116, 118, 120, 122, 124,
};

u8 gTransitionWaveAlpha[92] = {
    0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 255, 255, 255, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,
    255, 255, 255, 255, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
};

TriangleList gTransitionWaveTris[244] = {
    0,  8, 9,  0,  9,  1,  1,  9,  10, 1,  10, 2,  2,  10, 11, 2,  11, 3,  3,  11, 12, 3,  12, 4, 4,  12, 13, 4,
    13, 5, 5,  13, 14, 5,  14, 6,  6,  14, 15, 6,  15, 7,  0,  7,  8,  0,  8,  1,  1,  8,  9,  1, 9,  2,  2,  9,
    10, 2, 10, 3,  3,  10, 11, 3,  11, 4,  4,  11, 12, 4,  12, 5,  5,  12, 13, 5,  13, 6,  0,  8, 9,  0,  9,  1,
    1,  9, 10, 1,  10, 2,  2,  10, 11, 2,  11, 3,  3,  11, 12, 3,  12, 4,  4,  12, 13, 4,  13, 5, 5,  13, 14, 5,
    14, 6, 6,  14, 15, 6,  15, 7,  0,  8,  9,  0,  9,  1,  1,  9,  10, 1,  10, 2,  2,  10, 11, 2, 11, 3,  3,  11,
    12, 3, 12, 4,  4,  12, 13, 4,  13, 5,  5,  13, 14, 5,  14, 6,  6,  14, 15, 6,  15, 7,  0,  7, 8,  0,  8,  1,
    1,  8, 9,  1,  9,  2,  2,  9,  10, 2,  10, 3,  3,  10, 11, 3,  11, 4,  4,  11, 12, 4,  12, 5, 5,  12, 13, 5,
    13, 6, 0,  8,  9,  0,  9,  1,  1,  9,  10, 1,  10, 2,  2,  10, 11, 2,  11, 3,  3,  11, 12, 3, 12, 4,  4,  12,
    13, 4, 13, 5,  5,  13, 14, 5,  14, 6,  6,  14, 15, 6,  15, 7,  0,  0,  0,  0,
};

Gfx dTransitionShapeSettings[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetOtherMode(DKR_OMH_1CYC_POINT, DKR_OML_COMMON | G_RM_CLD_SURF | G_RM_CLD_SURF2),
    gsSPEndDisplayList(),
};

/*******************************/

/************ .bss ************/

s32 gCurFadeTransition;
u8 gCurFadeRed;
u8 gCurFadeGreen;
u8 gCurFadeBlue;
u8 gCurFadeAlpha;
s32 gLastFadeRed;
s32 gLastFadeGreen;
s32 gLastFadeBlue;
s32 gLastFadeRedStep;
s32 gLastFadeGreenStep;
s32 gLastFadeBlueStep;
f32 sTransitionOpacity;
f32 gTransitionOpacityVel;
f32 D_8012A758;
f32 D_8012A75C;
f32 D_8012A760;
f32 D_8012A764;
f32 D_8012A768;
f32 D_8012A76C;
f32 *gTransitionNextVtx;
f32 *gTransitionVtxStep;
f32 *gTransitionVertexTarget;
s32 gTransitionVertexCount;

/*****************************/

/**
 * Set the value indicating that a new screen transition can be started.
 */
void enable_new_screen_transitions(void) {
    gTransitionsDisabled = TRUE;
}

/**
 * Set the value indicating new transitions will not be created.
 */
void disable_new_screen_transitions(void) {
    gTransitionsDisabled = FALSE;
}

/**
 * Checks if there is currently a fadeout transition playing.
 */
u32 check_fadeout_transition(void) {
    u32 isActive = sTransitionFadeTimer != 0;
    if (isActive == FALSE) {
        isActive = gTransitionEndTimer != 0;
        if (isActive) {
            return (gTransitionFadeIn != 0);
        }
    }
    //!@bug: This doesn't seem to guarantee a return.
#ifdef AVOID_UB
    return FALSE;
#endif
}

/**
 * Reset the state then initialise the transition states based on the current transition data.
 */
s32 transition_begin(FadeTransition *transition) {
    if (gTransitionsDisabled) {
        return 0;
    }
    transition_end();
    if (transition == NULL) {
        return 0;
    }
    sTransitionFadeTimer = transition->duration;
    sTransitionFadeDuration = transition->duration;
    gTransitionEndTimer = transition->endTimer;
    gTransitionFadeIn = !(transition->type & FADE_FLAG_OUT);
    gCurFadeTransition = transition->type & 0x3F;
    gTransitionInvert = transition->type & FADE_FLAG_INVERT;
    sLevelTransitionDelayTimer = 0;
    if (!gTransitionFadeIn && !sLevelTransitionDelayTimer) {
        sLevelTransitionDelayTimer = 2;
    }
    if (sTransitionFadeTimer > 0) {
        gLastFadeRed = gCurFadeRed;
        gLastFadeGreen = gCurFadeGreen;
        gLastFadeBlue = gCurFadeBlue;
        gCurFadeRed = transition->red;
        gCurFadeGreen = transition->green;
        gCurFadeBlue = transition->blue;
        switch (gCurFadeTransition) {
            case FADE_FULLSCREEN:
                transition_fullscreen_start(transition);
                break;
            case FADE_BARNDOOR_HORIZONTAL:
                transition_init_shape(transition, 12, 8, (s16 *) gTransitionBarnHorizontalCoords, D_800E32A0,
                                      D_800E32AC, gTransitionBarnDoorAlpha, gTransitionBarnDoorAlpha,
                                      gTransitionBarnDoorTris);
                break;
            case FADE_BARNDOOR_VERTICAL:
                transition_init_shape(transition, 12, 8, (s16 *) gTransitionBarnVerticalCoords, D_800E32A0, D_800E32AC,
                                      gTransitionBarnDoorAlpha, gTransitionBarnDoorAlpha, gTransitionBarnDoorTris);
                break;
            case FADE_CIRCLE:
                transition_init_circle(transition);
                break;
            case FADE_WAVES:
                transition_init_shape(transition, 92, 80, (s16 *) gTransitionWaveCoords, D_800E349C, D_800E3440,
                                      gTransitionWaveAlpha, gTransitionWaveAlpha, gTransitionWaveTris);
                break;
            case FADE_BARNDOOR_DIAGONAL:
                transition_init_shape(transition, 10, 6, (s16 *) gTransitionBarnDiagCoords, D_800E330C, D_800E3318,
                                      gTransitionBarnDoorDiagAlpha, gTransitionBarnDoorDiagAlpha,
                                      gTransitionBarnDoorDiagTris);
                break;
            case FADE_DISABLED:
                transition_init_blank(transition);
                break;
        }
    }
    return sTransitionStatus;
}

/**
 * Handle the logic portion of the transitions. Runs always and calls the specific transition func from here.
 * Afterwards, it will return the transition status. The condition where this function is called wants a nonzero
 * return, which will then call the bit that renders the transitions.
 */
s32 transition_update(s32 updateRate) {
    if (sLevelTransitionDelayTimer) {
        sLevelTransitionDelayTimer--;
        updateRate = LOGIC_NULL;
    } else if (updateRate >= LOGIC_10FPS) {
        // Redundant because the logic update rate is clamped before this function is called.
        updateRate = LOGIC_12FPS;
    }

    if (sTransitionStatus != TRANSITION_NONE) {
        if (sTransitionFadeTimer == 0) {
            sTransitionStatus = TRANSITION_LEVELSWAP;
        }
        if (sTransitionFadeTimer == 0 && gTransitionEndTimer == 0) {
            transition_end();
        } else {
            if (sTransitionFadeTimer > 0) {
                sTransitionTaskNum = 1 - sTransitionTaskNum; // Haven't you heard of a XOR, Rareware employee?
            }
            switch (gCurFadeTransition) {
                case FADE_FULLSCREEN:
                    transition_update_fullscreen(updateRate);
                    break;
                case FADE_BARNDOOR_HORIZONTAL:
                case FADE_BARNDOOR_VERTICAL:
                case FADE_WAVES:
                case FADE_BARNDOOR_DIAGONAL:
                    transition_update_shape(updateRate);
                    break;
                case FADE_CIRCLE:
                    transition_update_circle(updateRate);
                    break;
                case FADE_DISABLED:
                    transition_update_blank(updateRate);
                    break;
            }
        }
    }
    return sTransitionStatus;
}

/**
 * The rendering portion of transitions.
 * First establishes an orthogonal matrix, then renders a transition effect onscreen.
 */
void transition_render(Gfx **dList, MatrixS **mtx, Vertex **vtx) {
    if (sTransitionStatus != TRANSITION_NONE) {
        if (osTvType == OS_TV_TYPE_PAL) {
            set_ortho_matrix_height(1.4f);
        } else {
            set_ortho_matrix_height(1.2f);
        }
        set_ortho_matrix_view(dList, mtx);
        set_ortho_matrix_height(1.0f);
        switch (gCurFadeTransition) {
            case FADE_FULLSCREEN:
                transition_render_fullscreen(dList, mtx, vtx);
                break;
            case FADE_BARNDOOR_HORIZONTAL:
                transition_render_barndoor_hor(dList, mtx, vtx);
                break;
            case FADE_BARNDOOR_VERTICAL:
                transition_render_barndoor_vert(dList, mtx, vtx);
                break;
            case FADE_CIRCLE:
                transition_render_circle(dList, mtx, vtx);
                break;
            case FADE_WAVES:
                transition_render_waves(dList, mtx, vtx);
                break;
            case FADE_BARNDOOR_DIAGONAL:
                transition_render_barndoor_diag(dList, mtx, vtx);
                break;
            case FADE_DISABLED:
                transition_render_blank(dList, mtx, vtx);
                break;
        }

        func_80066CDC(dList, mtx);
    }
}

/**
 * Disable the transition effect.
 * If there's existing allocated memory for transitions, free it.
 */
void transition_end(void) {
    if (sTransitionVtx[0] != NULL) {
        mempool_free(sTransitionVtx[0]);
        sTransitionVtx[0] = NULL;
        sTransitionVtx[1] = NULL;
        sTransitionTris[0] = NULL;
        sTransitionTris[1] = NULL;
    }
    sTransitionStatus = TRANSITION_NONE;
    sTransitionTaskNum = 0;
}

/**
 * Sets the transition timer and opacity to positive or negative depending on whether to fade in or out.
 */
void transition_fullscreen_start(FadeTransition *transition) {
    if (transition->type & FADE_FLAG_OUT) {
        sTransitionOpacity = 255.0f;
        gTransitionOpacityVel = -255.0f / (f32) sTransitionFadeTimer;
    } else {
        sTransitionOpacity = 0.0f;
        gTransitionOpacityVel = 255.0f / (f32) sTransitionFadeTimer;
    }
    sTransitionStatus = TRANSITION_ACTIVE;
}

/**
 * Slowly dade in or out by increasing or decreasing opacity.
 */
void transition_update_fullscreen(s32 updateRate) {
    s32 var_v0;
    do {
        var_v0 = TRUE;
        if ((sTransitionFadeTimer) > 0) {
            if (updateRate < sTransitionFadeTimer) {
                sTransitionFadeTimer -= updateRate;
                sTransitionOpacity += gTransitionOpacityVel * updateRate;
            } else {
                updateRate -= sTransitionFadeTimer;
                var_v0 = FALSE;
                if (gTransitionOpacityVel < 0.0f) {
                    sTransitionOpacity = 0.0f;
                } else {
                    sTransitionOpacity = 255.0f;
                }
                sTransitionFadeTimer = 0 * updateRate; // Fakematch
            }
            if (sTransitionOpacity < 0.0f) {
                sTransitionOpacity = 0.0f;
            } else if (sTransitionOpacity > 255.0f) {
                sTransitionOpacity = 255.0f;
            }
            gCurFadeAlpha = sTransitionOpacity;
        } else if (gTransitionEndTimer != 0xFFFF) {
            if (updateRate < gTransitionEndTimer) {
                gTransitionEndTimer -= updateRate;
            } else {
                updateRate -= gTransitionEndTimer;
                gTransitionEndTimer = 0;
                if (gTransitionInvert != 0) {
                    gTransitionInvert = 0;
                    sTransitionFadeTimer = sTransitionFadeDuration;
                    gTransitionOpacityVel = -gTransitionOpacityVel;
                    var_v0 = FALSE;
                }
            }
        }
    } while (var_v0 == FALSE && updateRate > 0);
}

/**
 * Draws a simple fillrect covering the whole screen that fades in or out.
 */
void transition_render_fullscreen(Gfx **dList, UNUSED MatrixS **mtx, UNUSED Vertex **vtx) {
    s32 screenSize = fb_size();
    gSPDisplayList((*dList)++, dTransitionFadeSettings);
    gDPSetPrimColor((*dList)++, 0, 0, gCurFadeRed, gCurFadeGreen, gCurFadeBlue, gCurFadeAlpha);
    gDPSetCombineMode((*dList)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPFillRectangle((*dList)++, 0, 0, screenSize & 0x3FF, (screenSize >> 16) & 0x3FF);
    reset_render_settings(dList);
}

/**
 * Allocate space for the new transitions vertices and triangles, then build the geometry based on the vertex and
 * triangle shapes given.
 */
void transition_init_shape(FadeTransition *transition, s32 numVerts, s32 numTris, s16 *coords, u8 *nextPos,
                           u8 *targetPos, u8 *nextAlpha, u8 *targetAlpha, u8 *vertIndices) {
    UNUSED s32 pad;
    u8 *swap;
    s32 sizeVerts;
    s32 sizeTris;
    s32 i;
    s32 j;

    j = numVerts;
    sizeVerts = j * sizeof(Vertex);
    sizeTris = numTris * sizeof(Triangle);
    i = j * 12;

    sTransitionVtx[0] = mempool_alloc_safe(((sizeVerts + sizeTris) * 2) + (i * 3), COLOUR_TAG_YELLOW);
    sTransitionVtx[1] = sTransitionVtx[0] + j;
    sTransitionTris[0] = (Triangle *) (sTransitionVtx[1] + j);
    sTransitionTris[1] = (Triangle *) (((u8 *) sTransitionTris[0]) + sizeTris);
    gTransitionNextVtx = (f32 *) (((u8 *) sTransitionTris[1]) + sizeTris);
    gTransitionVtxStep = (f32 *) (((u8 *) gTransitionNextVtx) + i);
    gTransitionVertexTarget = (f32 *) (((u8 *) gTransitionVtxStep) + i);
    if (transition->type & FADE_FLAG_OUT) {
        swap = nextPos;
        nextPos = targetPos;
        targetPos = swap;
        swap = nextAlpha;
        nextAlpha = targetAlpha;
        targetAlpha = swap;
    }

    for (i = 0; i < numVerts; i++) {
        gTransitionNextVtx[(i * 3) + 0] = coords[nextPos[i]];
        gTransitionNextVtx[(i * 3) + 1] = coords[nextPos[i] + 1];
        gTransitionNextVtx[(i * 3) + 2] = nextAlpha[i];
        gTransitionVertexTarget[(i * 3) + 0] = coords[targetPos[i]];
        gTransitionVertexTarget[(i * 3) + 1] = coords[targetPos[i] + 1];
        gTransitionVertexTarget[(i * 3) + 2] = targetAlpha[i];
        gTransitionVtxStep[(i * 3) + 0] =
            (gTransitionVertexTarget[(i * 3) + 0] - gTransitionNextVtx[(i * 3) + 0]) / sTransitionFadeTimer;
        gTransitionVtxStep[(i * 3) + 1] =
            (gTransitionVertexTarget[(i * 3) + 1] - gTransitionNextVtx[(i * 3) + 1]) / sTransitionFadeTimer;
        gTransitionVtxStep[(i * 3) + 2] =
            (gTransitionVertexTarget[(i * 3) + 2] - gTransitionNextVtx[(i * 3) + 2]) / sTransitionFadeTimer;
    }

    for (i = 0; i < 2; i++) {
        for (j = 0; j < numVerts; j++) {
            sTransitionVtx[i][j].z = -16;
            sTransitionVtx[i][j].r = gCurFadeRed;
            sTransitionVtx[i][j].g = gCurFadeGreen;
            sTransitionVtx[i][j].b = gCurFadeBlue;
        }
    }

    for (i = 0; i < 2; i++) {
        for (j = 0; j < numTris; j++) {
            sTransitionTris[i][j].flags = BACKFACE_DRAW;
            sTransitionTris[i][j].vi0 = vertIndices[(j * 3) + 0];
            sTransitionTris[i][j].uv0.u = 0;
            sTransitionTris[i][j].uv0.v = 0;
            sTransitionTris[i][j].vi1 = vertIndices[(j * 3) + 1];
            sTransitionTris[i][j].uv1.u = 0;
            sTransitionTris[i][j].uv1.v = 0;
            sTransitionTris[i][j].vi2 = vertIndices[(j * 3) + 2];
            sTransitionTris[i][j].uv2.u = 0;
            sTransitionTris[i][j].uv2.v = 0;
        }
    }

    sTransitionStatus = TRANSITION_ACTIVE;
    gTransitionVertexCount = numVerts;
}

/**
 * Slowly update the vertices of the transition based on what the next frames target is.
 * That target is set based on a velocity.
 */
void transition_update_shape(s32 updateRate) {
    s32 i;
    f32 updateRateF;

    updateRateF = updateRate;
    if (sTransitionFadeTimer > 0) {
        if (updateRate < sTransitionFadeTimer) {
            for (i = 0; i < gTransitionVertexCount; i++) {
                gTransitionNextVtx[i * 3] += updateRateF * gTransitionVtxStep[i * 3];
                gTransitionNextVtx[i * 3 + 1] += updateRateF * gTransitionVtxStep[i * 3 + 1];
                gTransitionNextVtx[i * 3 + 2] += updateRateF * gTransitionVtxStep[i * 3 + 2];
            }
            sTransitionFadeTimer -= updateRate;
        } else {
            for (i = 0; i < gTransitionVertexCount; i++) {
                gTransitionNextVtx[i * 3] = gTransitionVertexTarget[i * 3];
                gTransitionNextVtx[i * 3 + 1] = gTransitionVertexTarget[i * 3 + 1];
                gTransitionNextVtx[i * 3 + 2] = gTransitionVertexTarget[i * 3 + 2];
            }
            sTransitionFadeTimer = 0;
        }
        for (i = 0; i < gTransitionVertexCount; i++) {
            sTransitionVtx[sTransitionTaskNum][i].x = gTransitionNextVtx[i * 3];
            sTransitionVtx[sTransitionTaskNum][i].y = gTransitionNextVtx[i * 3 + 1];
            sTransitionVtx[sTransitionTaskNum][i].a = (s32) gTransitionNextVtx[i * 3 + 2];
        }
    } else if (gTransitionEndTimer != 0xFFFF) {
        if (updateRate < gTransitionEndTimer) {
            gTransitionEndTimer -= updateRate;
        } else {
            gTransitionEndTimer = 0;
        }
    }
}

/**
 * Renders a transition effect on screen that will close in from both sides horizonally.
 */
void transition_render_barndoor_hor(Gfx **dList, UNUSED MatrixS **mtx, UNUSED Vertex **vtx) {
    reset_render_settings(dList);
    gSPDisplayList((*dList)++, dTransitionShapeSettings);
    gSPVertexDKR((*dList)++, OS_PHYSICAL_TO_K0(sTransitionVtx[sTransitionTaskNum]), 12, 0);
    gSPPolygon((*dList)++, OS_PHYSICAL_TO_K0(sTransitionTris[sTransitionTaskNum]), 8, TRIN_DISABLE_TEXTURE);
    reset_render_settings(dList);
}

/**
 * Renders a transition effect on screen that will close in from both sides vertically.
 * Codewise, exactly the same as above, but uses a different vertex layout to make the difference.
 */
void transition_render_barndoor_vert(Gfx **dList, UNUSED MatrixS **mtx, UNUSED Vertex **vtx) {
    reset_render_settings(dList);
    gSPDisplayList((*dList)++, dTransitionShapeSettings);
    gSPVertexDKR((*dList)++, OS_PHYSICAL_TO_K0(sTransitionVtx[sTransitionTaskNum]), 12, 0);
    gSPPolygon((*dList)++, OS_PHYSICAL_TO_K0(sTransitionTris[sTransitionTaskNum]), 8, TRIN_DISABLE_TEXTURE);
    reset_render_settings(dList);
}

void transition_init_circle(FadeTransition *transition) {
    s32 i;
    s32 j;
    s32 k;
    f32 var_f12;
    f32 var_f20;
    s32 sizeVerts;
    s32 sizeTris;
    s16 xSins;
    s16 yCoss;

    sizeVerts = 72 * sizeof(Vertex);
    sizeTris = 64 * sizeof(Triangle);
    sTransitionVtx[0] = (Vertex *) mempool_alloc_safe((sizeVerts + sizeTris) * 2, COLOUR_TAG_YELLOW);
    sTransitionVtx[1] = sTransitionVtx[0] + 72;
    sTransitionTris[0] = (Triangle *) (sTransitionVtx[1] + 72);
    sTransitionTris[1] = sTransitionTris[0] + 64;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 72; j++) {
            sTransitionVtx[i][j].r = gCurFadeRed;
            sTransitionVtx[i][j].g = gCurFadeGreen;
            sTransitionVtx[i][j].b = gCurFadeBlue;
            sTransitionVtx[i][j].a = 255;
        }
    }

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 9; j++) {
            sTransitionVtx[i][(j << 1) + 19].a = 0;
            sTransitionVtx[i][(j << 1) + 55].a = 0;
        }
    }

    var_f12 = 180.0f;
    var_f20 = 240.0f;
    k = 0;
    for (i = 0; i < 9; i++, k += 0x1000) {
        xSins = sins_f(k) * var_f20;
        yCoss = coss_f(k) * var_f12;
        for (j = 0; j < 2; j++) {
            sTransitionVtx[j][i << 1].x = xSins;
            sTransitionVtx[j][i << 1].y = yCoss;
            sTransitionVtx[j][i << 1].z = -16;
            sTransitionVtx[j][(i << 1) + 1].z = -16;
            sTransitionVtx[j][(i << 1) + 18].z = -16;
            sTransitionVtx[j][(i << 1) + 19].z = -16;
            sTransitionVtx[j][(i << 1) + 36].x = -xSins;
            sTransitionVtx[j][(i << 1) + 36].y = yCoss;
            sTransitionVtx[j][(i << 1) + 36].z = -16;
            sTransitionVtx[j][(i << 1) + 37].z = -16;
            sTransitionVtx[j][(i << 1) + 54].z = -16;
            sTransitionVtx[j][(i << 1) + 55].z = -16;
        }
    }

    if (transition->type & FADE_FLAG_OUT) {
        D_8012A758 = 0.0f;
        D_8012A75C = 0.0f;
        D_8012A760 = var_f20 / sTransitionFadeTimer;
        D_8012A764 = var_f12 / sTransitionFadeTimer;
        D_8012A768 = var_f20;
        D_8012A76C = var_f12;
    } else {
        D_8012A758 = var_f20;
        D_8012A75C = var_f12;
        D_8012A760 = (-var_f20) / sTransitionFadeTimer;
        D_8012A764 = (-var_f12) / sTransitionFadeTimer;
        D_8012A768 = 0.0f;
        D_8012A76C = 0.0f;
    }

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 64; j++) {
            sTransitionTris[i][j].flags = BACKFACE_DRAW;
            sTransitionTris[i][j].uv0.u = 0;
            sTransitionTris[i][j].uv0.v = 0;
            sTransitionTris[i][j].uv1.u = 0;
            sTransitionTris[i][j].uv1.v = 0;
            sTransitionTris[i][j].uv2.u = 0;
            sTransitionTris[i][j].uv2.v = 0;
        }
    }

#define ASSIGN_TRANSITION_TRI(i, j, k)                                                                                 \
    ((u8 *) sTransitionTris[j])[((i << 1) << 4) + (sizeof(Triangle) * k) * sizeof(Triangle) + 1] = (i << 1) + 0;       \
    ((u8 *) sTransitionTris[j])[((i << 1) << 4) + (sizeof(Triangle) * k) * sizeof(Triangle) + 2] = (i << 1) + 1;       \
    ((u8 *) sTransitionTris[j])[((i << 1) << 4) + (sizeof(Triangle) * k) * sizeof(Triangle) + 3] = (i << 1) + 3;       \
    ((u8 *) sTransitionTris[j])[((i << 1) << 4) + (1 + (sizeof(Triangle) * k)) * sizeof(Triangle) + 1] = (i << 1) + 0; \
    ((u8 *) sTransitionTris[j])[((i << 1) << 4) + (1 + (sizeof(Triangle) * k)) * sizeof(Triangle) + 2] = (i << 1) + 3; \
    ((u8 *) sTransitionTris[j])[((i << 1) << 4) + (1 + (sizeof(Triangle) * k)) * sizeof(Triangle) + 3] = (i << 1) + 2;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 2; j++) {
            ASSIGN_TRANSITION_TRI(i, j, 0);
            ASSIGN_TRANSITION_TRI(i, j, 1);
            ASSIGN_TRANSITION_TRI(i, j, 2);
            ASSIGN_TRANSITION_TRI(i, j, 3);
        }
    }

    sTransitionStatus = TRANSITION_ACTIVE;
}

void transition_update_circle(s32 updateRate) {
    f32 temp_f20;
    f32 temp_f2;
    f32 temp_f16;
    s16 temp_f6;
    s32 i;
    f32 arg0F;
    f32 new_var;
    s32 j;

    arg0F = updateRate;
    if (sTransitionFadeTimer > 0) {
        if (updateRate < sTransitionFadeTimer) {
            D_8012A758 += (arg0F * D_8012A760);
            D_8012A75C += (arg0F * D_8012A764);
            sTransitionFadeTimer -= updateRate;
        } else {
            D_8012A758 = D_8012A768;
            D_8012A75C = D_8012A76C;
            sTransitionFadeTimer = 0;
        }

        for (j = 0, i = 0; i < 9; i++, j += 0x1000) {
            new_var = 1.2f;
            temp_f20 = sins_f(j) * D_8012A758;
            temp_f2 = coss_f(j) * D_8012A75C;
            temp_f6 = (temp_f20 * new_var);
            temp_f16 = (temp_f2 * new_var);
            sTransitionVtx[sTransitionTaskNum][(i << 1) + 1].x = temp_f6;
            sTransitionVtx[sTransitionTaskNum][(i << 1) + 1].y = temp_f16;
            sTransitionVtx[sTransitionTaskNum][(i << 1) + 37].x = -temp_f6;
            sTransitionVtx[sTransitionTaskNum][(i << 1) + 37].y = temp_f16;
            sTransitionVtx[sTransitionTaskNum][(i << 1) + 18].x = temp_f6;
            sTransitionVtx[sTransitionTaskNum][(i << 1) + 18].y = temp_f16;
            sTransitionVtx[sTransitionTaskNum][(i << 1) + 54].x = -temp_f6;
            sTransitionVtx[sTransitionTaskNum][(i << 1) + 54].y = temp_f16;
            sTransitionVtx[sTransitionTaskNum][(i << 1) + 19].x = temp_f20;
            sTransitionVtx[sTransitionTaskNum][(i << 1) + 19].y = temp_f2;
            temp_f6 = temp_f20;
            sTransitionVtx[sTransitionTaskNum][(i << 1) + 55].x = -temp_f6;
            sTransitionVtx[sTransitionTaskNum][(i << 1) + 55].y = temp_f2;
        }
    } else if (gTransitionEndTimer != 0xFFFF) {
        if (updateRate < gTransitionEndTimer) {
            gTransitionEndTimer -= updateRate;
        } else {
            gTransitionEndTimer = 0;
        }
    }
}

#define NUM_OF_VERTS 18
#define NUM_OF_TRIS 16
/**
 * Render a circle shape transition onscreen using previously allocated geometry.
 */
void transition_render_circle(Gfx **dList, UNUSED MatrixS **mtx, UNUSED Vertex **vtx) {
    Vertex *vertsToRender;
    Triangle *trisToRender;
    Gfx *gfx;
    s32 i;

    reset_render_settings(dList);
    gfx = *dList;

    vertsToRender = (Vertex *) sTransitionVtx[sTransitionTaskNum];
    trisToRender = (Triangle *) sTransitionTris[sTransitionTaskNum];
    gSPDisplayList(gfx++, dTransitionShapeSettings);

    for (i = 0; i < 4; i++) {
        gSPVertexDKR(gfx++, OS_PHYSICAL_TO_K0(vertsToRender), NUM_OF_VERTS, 0);
        gSPPolygon(gfx++, OS_PHYSICAL_TO_K0(trisToRender), NUM_OF_TRIS, TRIN_DISABLE_TEXTURE);
        vertsToRender += NUM_OF_VERTS;
        trisToRender += NUM_OF_TRIS;
    }

    *dList = gfx;
    reset_render_settings(dList);
}

/**
 * Render the wavy transition onscreen using the vertex data allocated earlier.
 */
void transition_render_waves(Gfx **dList, UNUSED MatrixS **mtx, UNUSED Vertex **vtx) {
    Gfx *gfx;
    s32 i;
    Vertex *v;
    Triangle *t;
    reset_render_settings(dList);
    gfx = *dList;
    v = (Vertex *) sTransitionVtx[sTransitionTaskNum];
    t = (Triangle *) sTransitionTris[sTransitionTaskNum];
    gSPDisplayList(gfx++, dTransitionShapeSettings);
    /*
    i == 0 -> Left third wave?
    i == 1 -> Middle third wave?
    i == 2 -> Right third wave?
    i == 3 -> Left third mask? ("mask" being pure black square in this context)
    i == 4 -> Middle third mask?
    i == 5 -> Right third mask?
    */
    for (i = 0; i < 6; i++) {
        if (i == 1 || i == 4) { // Is middle third?
            gSPVertexDKR(gfx++, OS_PHYSICAL_TO_K0(v), 14, 0);
            gSPPolygon(gfx++, OS_PHYSICAL_TO_K0(t), 12, TRIN_DISABLE_TEXTURE);
            v += 14;
            t += 12;
        } else {
            gSPVertexDKR(gfx++, OS_PHYSICAL_TO_K0(v), 16, 0);
            gSPPolygon(gfx++, OS_PHYSICAL_TO_K0(t), 14, TRIN_DISABLE_TEXTURE);
            v += 16;
            t += 14;
        }
    }
    *dList = gfx;
    reset_render_settings(dList);
}

/**
 * Renders a transition effect on screen that will close in from the opposite corners of the screen.
 */
void transition_render_barndoor_diag(Gfx **dList, UNUSED MatrixS **mtx, UNUSED Vertex **vtx) {
    reset_render_settings(dList);
    gSPDisplayList((*dList)++, dTransitionShapeSettings);
    gSPVertexDKR((*dList)++, OS_PHYSICAL_TO_K0(sTransitionVtx[sTransitionTaskNum]), 10, 0);
    gSPPolygon((*dList)++, OS_PHYSICAL_TO_K0(sTransitionTris[sTransitionTaskNum]), 6, TRIN_DISABLE_TEXTURE);
    reset_render_settings(dList);
}

/**
 * Set the transition colour target, then set the velocity for the colour to fade to.
 */
void transition_init_blank(UNUSED FadeTransition *transition) {
    gLastFadeRed <<= 16;
    gLastFadeGreen <<= 16;
    gLastFadeBlue <<= 16;
    gCurFadeAlpha = 255;
    sTransitionOpacity = 255.0f;
    gTransitionOpacityVel = 0.0f;
    gLastFadeRedStep = ((gCurFadeRed << 16) - gLastFadeRed) / sTransitionFadeTimer;
    gLastFadeGreenStep = ((gCurFadeGreen << 16) - gLastFadeGreen) / sTransitionFadeTimer;
    gLastFadeBlueStep = ((gCurFadeBlue << 16) - gLastFadeBlue) / sTransitionFadeTimer;
    sTransitionStatus = TRANSITION_ACTIVE;
}

/**
 * Shifts the colours of the transition over time while the timer ticks down.
 */
void transition_update_blank(s32 updateRate) {
    s32 var_v0 = FALSE;
    do {
        var_v0 = TRUE;
        if (sTransitionFadeTimer > 0) {
            gLastFadeRed += gLastFadeRedStep * updateRate;
            gLastFadeGreen += gLastFadeGreenStep * updateRate;
            gLastFadeBlue += gLastFadeBlueStep * updateRate;
            if (updateRate >= sTransitionFadeTimer) {
                gLastFadeRed = gCurFadeRed << 16;
                gLastFadeGreen = gCurFadeGreen << 16;
                gLastFadeBlue = gCurFadeBlue << 16;
                updateRate -= sTransitionFadeTimer;
                sTransitionFadeTimer = 0;
            } else {
                sTransitionFadeTimer -= updateRate;
            }
        } else {
            if (gTransitionEndTimer != 0xFFFF) {
                gTransitionEndTimer -= updateRate;
                if (gTransitionEndTimer <= 0) {
                    gTransitionEndTimer = 0;
                }
            }
        }
    } while (var_v0 == FALSE);
}

/**
 * Fill the whole screen with a solid colour.
 */
void transition_render_blank(Gfx **dList, UNUSED MatrixS **mtx, UNUSED Vertex **vtx) {
    s32 screenSize = fb_size();
    gSPDisplayList((*dList)++, dTransitionFadeSettings);
    gDPSetPrimColor((*dList)++, 0, 0, (gLastFadeRed >> 16), (gLastFadeGreen >> 16), (gLastFadeBlue >> 16), 255);
    gDPSetCombineMode((*dList)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPFillRectangle((*dList)++, 0, 0, GET_VIDEO_WIDTH(screenSize), GET_VIDEO_HEIGHT(screenSize) & 0x3FF);
    reset_render_settings(dList);
}
