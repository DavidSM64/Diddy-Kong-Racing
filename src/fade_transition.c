/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C0170 */

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

s16 gTransitionBarnHorizontalData[28] = {
    0xFE20, 0x0078, 0xFEC0, 0x0078, 0xFF60, 0x0078, 0x0000, 0x0078, 0x00A0, 0x0078, 0x0140, 0x0078, 0x01E0, 0x0078,
    0xFE20, 0xFF88, 0xFEC0, 0xFF88, 0xFF60, 0xFF88, 0x0000, 0xFF88, 0x00A0, 0xFF88, 0x0140, 0xFF88, 0x01E0, 0xFF88,
};

s16 gTransitionBarnVerticalData[28] = {
    0xFF60, 0x0168, 0xFF60, 0x00F0, 0xFF60, 0x0078, 0xFF60, 0x0000, 0xFF60, 0xFF88, 0xFF60, 0xFF10, 0xFF60, 0xFF10,
    0x00A0, 0x0168, 0x00A0, 0x00F0, 0x00A0, 0x0078, 0x00A0, 0x0000, 0x00A0, 0xFF88, 0x00A0, 0xFF10, 0x00A0, 0xFF10,
};

u8 D_800E32A0[12] = {
    0x00, 0x02, 0x04, 0x0E, 0x10, 0x12, 0x08, 0x0A, 0x0C, 0x16, 0x18, 0x1A,
};

u8 D_800E32AC[12] = {
    0x04, 0x06, 0x08, 0x12, 0x14, 0x16, 0x04, 0x06, 0x08, 0x12, 0x14, 0x16,
};

TriangleList gTransitionBarnDoorTris[24] = {
    0, 3, 1, 1, 3, 4, 1, 4, 2, 2, 4, 5, 6, 9, 7, 7, 9, 10, 7, 10, 8, 8, 10, 11,
};

u8 gTransitionBarnDoorAlpha[12] = {
    255, 255, 0, 255, 255, 0, 0, 255, 255, 0, 255, 255,
};

s16 gTransitionBarnDiagData[24] = {
    0xFCE0, 0x0078, 0xFE20, 0x0078, 0xFF60, 0x0078, 0x00A0, 0x0078, 0x01E0, 0x0078, 0x0320, 0x0078,
    0xFCE0, 0xFF88, 0xFE20, 0xFF88, 0xFF60, 0xFF88, 0x00A0, 0xFF88, 0x01E0, 0xFF88, 0x0320, 0xFF88,
};

u8 D_800E330C[12] = {
    0, 2, 4, 12, 14, 8, 10, 18, 20, 22, 0, 0,
};

u8 D_800E3318[12] = {
    4, 6, 8, 16, 18, 4, 6, 14, 16, 18, 0, 0,
};

TriangleList gTransitionBarnDoorDiagTris[20] = {
    0, 1, 3, 1, 3, 4, 1, 4, 2, 5, 7, 8, 5, 8, 6, 6, 8, 9, 0, 0,
};

u8 gTransitionBarnDoorDiagAlpha[12] = {
    255, 255, 0, 255, 0, 0, 255, 0, 255, 255, 0, 0,
};

s16 gTransitionWaveData[126] = {
    0xFF60, 0x00A0, 0xFF70, 0x00A0, 0xFF80, 0x00A0, 0xFF90, 0x00A0, 0xFFA0, 0x00A0, 0xFFB0, 0x00A0, 0xFFC0, 0x00A0,
    0xFFD0, 0x00A0, 0xFFE0, 0x00A0, 0xFFF0, 0x00A0, 0x0000, 0x00A0, 0x0010, 0x00A0, 0x0020, 0x00A0, 0x0030, 0x00A0,
    0x0040, 0x00A0, 0x0050, 0x00A0, 0x0060, 0x00A0, 0x0070, 0x00A0, 0x0080, 0x00A0, 0x0090, 0x00A0, 0x00A0, 0x00A0,
    0xFF60, 0xFF38, 0xFF70, 0xFF60, 0xFF80, 0xFF74, 0xFF90, 0xFF7E, 0xFFA0, 0xFF74, 0xFFB0, 0xFF38, 0xFFC0, 0xFF10,
    0xFFD0, 0xFEFC, 0xFFE0, 0xFEF2, 0xFFF0, 0xFEFC, 0x0000, 0xFF24, 0x0010, 0xFF2E, 0x0020, 0xFF38, 0x0030, 0xFF2E,
    0x0040, 0xFF24, 0x0050, 0xFEFC, 0x0060, 0xFEF2, 0x0070, 0xFEFC, 0x0080, 0xFF24, 0x0090, 0xFF60, 0x00A0, 0xFF74,
    0xFF60, 0xFEE8, 0xFF70, 0xFEE8, 0xFF80, 0xFEE8, 0xFF90, 0xFEE8, 0xFFA0, 0xFEE8, 0xFFB0, 0xFEE8, 0xFFC0, 0xFEE8,
    0xFFD0, 0xFEE8, 0xFFE0, 0xFEE8, 0xFFF0, 0xFEE8, 0x0000, 0xFEE8, 0x0010, 0xFEE8, 0x0020, 0xFEE8, 0x0030, 0xFEE8,
    0x0040, 0xFEE8, 0x0050, 0xFEE8, 0x0060, 0xFEE8, 0x0070, 0xFEE8, 0x0080, 0xFEE8, 0x0090, 0xFEE8, 0x00A0, 0xFEE8,
};

u8 D_800E3440[92] = {
    0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x0E, 0x10, 0x12,
    0x14, 0x16, 0x18, 0x1A, 0x0E, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1A, 0x1A, 0x1C, 0x1E, 0x20, 0x22, 0x24, 0x26, 0x28,
    0x1A, 0x1C, 0x1E, 0x20, 0x22, 0x24, 0x26, 0x28, 0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x54, 0x56, 0x58,
    0x5A, 0x5C, 0x5E, 0x60, 0x62, 0x0E, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1A, 0x62, 0x64, 0x66, 0x68, 0x6A, 0x6C, 0x6E,
    0x1A, 0x1C, 0x1E, 0x20, 0x22, 0x24, 0x26, 0x28, 0x6E, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7A, 0x7C,
};

u8 D_800E349C[92] = {
    0x2A, 0x2C, 0x2E, 0x30, 0x32, 0x34, 0x36, 0x38, 0x54, 0x56, 0x58, 0x5A, 0x5C, 0x5E, 0x60, 0x62, 0x38, 0x3A, 0x3C,
    0x3E, 0x40, 0x42, 0x44, 0x62, 0x64, 0x66, 0x68, 0x6A, 0x6C, 0x6E, 0x44, 0x46, 0x48, 0x4A, 0x4C, 0x4E, 0x50, 0x52,
    0x6E, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7A, 0x7C, 0x54, 0x56, 0x58, 0x5A, 0x5C, 0x5E, 0x60, 0x62, 0x54, 0x56, 0x58,
    0x5A, 0x5C, 0x5E, 0x60, 0x62, 0x62, 0x64, 0x66, 0x68, 0x6A, 0x6C, 0x6E, 0x62, 0x64, 0x66, 0x68, 0x6A, 0x6C, 0x6E,
    0x6E, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7A, 0x7C, 0x6E, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7A, 0x7C,
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
                init_transition_shape(transition, 12, 8, gTransitionBarnHorizontalData, D_800E32A0, D_800E32AC,
                                      gTransitionBarnDoorAlpha, gTransitionBarnDoorAlpha, gTransitionBarnDoorTris);
                break;
            case FADE_BARNDOOR_VERTICAL:
                init_transition_shape(transition, 12, 8, gTransitionBarnVerticalData, D_800E32A0, D_800E32AC,
                                      gTransitionBarnDoorAlpha, gTransitionBarnDoorAlpha, gTransitionBarnDoorTris);
                break;
            case FADE_CIRCLE:
                func_800C15D4(transition);
                break;
            case FADE_WAVES:
                init_transition_shape(transition, 92, 80, gTransitionWaveData, D_800E349C, D_800E3440,
                                      gTransitionWaveAlpha, gTransitionWaveAlpha, gTransitionWaveTris);
                break;
            case FADE_BARNDOOR_DIAGONAL:
                init_transition_shape(transition, 10, 6, gTransitionBarnDiagData, D_800E330C, D_800E3318,
                                      gTransitionBarnDoorDiagAlpha, gTransitionBarnDoorDiagAlpha,
                                      gTransitionBarnDoorDiagTris);
                break;
            case FADE_DISABLED:
                init_transition_blank(transition);
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
s32 handle_transitions(s32 updateRate) {
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
                    process_transition_fullscreen(updateRate);
                    break;
                case FADE_BARNDOOR_HORIZONTAL:
                case FADE_BARNDOOR_VERTICAL:
                case FADE_WAVES:
                case FADE_BARNDOOR_DIAGONAL:
                    process_transition_shape(updateRate);
                    break;
                case FADE_CIRCLE:
                    func_800C1EE8(updateRate);
                    break;
                case FADE_DISABLED:
                    process_transition_disabled(updateRate);
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
void render_fade_transition(Gfx **dList, MatrixS **mats, Vertex **verts) {
    if (sTransitionStatus != TRANSITION_NONE) {
        if (osTvType == OS_TV_TYPE_PAL) {
            set_ortho_matrix_height(1.4f);
        } else {
            set_ortho_matrix_height(1.2f);
        }
        set_ortho_matrix_view(dList, mats);
        set_ortho_matrix_height(1.0f);
        switch (gCurFadeTransition) {
            case FADE_FULLSCREEN:
                render_fade_fullscreen(dList, mats, verts);
                break;
            case FADE_BARNDOOR_HORIZONTAL:
                render_fade_barndoor_horizontal(dList, mats, verts);
                break;
            case FADE_BARNDOOR_VERTICAL:
                render_fade_barndoor_vertical(dList, mats, verts);
                break;
            case FADE_CIRCLE:
                render_fade_circle(dList, mats, verts);
                break;
            case FADE_WAVES:
                render_fade_waves(dList, mats, verts);
                break;
            case FADE_BARNDOOR_DIAGONAL:
                render_fade_barndoor_diagonal(dList, mats, verts);
                break;
            case FADE_DISABLED:
                render_fade_disabled(dList, mats, verts);
                break;
        }

        func_80066CDC(dList, mats);
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
void process_transition_fullscreen(s32 updateRate) {
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
void render_fade_fullscreen(Gfx **dList, UNUSED MatrixS **mats, UNUSED Vertex **verts) {
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
void init_transition_shape(FadeTransition *transition, s32 numVerts, s32 numTris, s16 *coords, u8 *nextPos,
                           u8 *targetPos, u8 *nextAlpha, u8 *targetAlpha, u8 *vertIndices) {
    UNUSED s32 pad;
    u8 *swap;
    s32 sizeVerts;
    s32 sizeTris;
    s32 i;
    s32 j;

    j = numVerts;
    sizeVerts = j * 10;
    sizeTris = numTris * 16;
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
            sTransitionTris[i][j].flags = 0x40;
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
void process_transition_shape(s32 updateRate) {
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
void render_fade_barndoor_horizontal(Gfx **dList, UNUSED MatrixS **mats, UNUSED Vertex **verts) {
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
void render_fade_barndoor_vertical(Gfx **dList, UNUSED MatrixS **mats, UNUSED Vertex **verts) {
    reset_render_settings(dList);
    gSPDisplayList((*dList)++, dTransitionShapeSettings);
    gSPVertexDKR((*dList)++, OS_PHYSICAL_TO_K0(sTransitionVtx[sTransitionTaskNum]), 12, 0);
    gSPPolygon((*dList)++, OS_PHYSICAL_TO_K0(sTransitionTris[sTransitionTaskNum]), 8, TRIN_DISABLE_TEXTURE);
    reset_render_settings(dList);
}

#ifdef NON_EQUIVALENT
void func_800C15D4(FadeTransition *transition) {
    s32 i;
    s32 j;
    s32 sizeVerts;
    s32 sizeTris;
    s32 numVerts = 72;
    s32 numTris = 64;

    sizeVerts = numVerts * sizeof(Vertex);
    sizeTris = numTris * sizeof(Triangle);

    sTransitionVtx[0] = (Vertex *) mempool_alloc_safe(((sizeVerts + sizeTris) * 2), COLOUR_TAG_YELLOW);
    sTransitionVtx[1] = (Vertex *) ((uintptr_t) sTransitionVtx[0] + sizeVerts);
    sTransitionTris[0] = (Triangle *) ((uintptr_t) sTransitionVtx[1] + sizeVerts);
    sTransitionTris[1] = (Triangle *) ((uintptr_t) sTransitionTris[0] + sizeTris);

    // This first one should be correct?
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 72; j++) {
            sTransitionVtx[i][j].r = gCurFadeRed;
            sTransitionVtx[i][j].g = gCurFadeGreen;
            sTransitionVtx[i][j].b = gCurFadeBlue;
            sTransitionVtx[i][j].a = 255;
        }
    }

    // ???
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 9; j++) {
            sTransitionVtx[i][j + 19].a = 0;
            sTransitionVtx[i][j + 55].a = 0;
        }
    }

    for (i = 0; i < 2; i++) {
        s16 xSins = sins_f(i * 0x1000) * 240.0f;
        s16 yCoss = coss_f(i * 0x1000) * 180.0f;
        for (j = 0; j < 9; j++) {
            sTransitionVtx[i][j].x = xSins;
            sTransitionVtx[i][j].y = yCoss;
            sTransitionVtx[i][j].z = -16;
            sTransitionVtx[i][j + 1].z = -16;
            sTransitionVtx[i][j + 17].z = -16;
            sTransitionVtx[i][j + 18].z = -16;
            sTransitionVtx[i][j + 34].x = -xSins;
            sTransitionVtx[i][j + 36].x = yCoss;
            sTransitionVtx[i][j + 36].y = -16;
            sTransitionVtx[i][j + 54].z = -16;
            sTransitionVtx[i][j + 55].z = -16;
        }
    }

    if (transition->type & FADE_FLAG_OUT) {
        D_8012A758 = 0.0f;
        D_8012A75C = 0.0f;
        D_8012A760 = (240.0f / sTransitionFadeTimer);
        D_8012A764 = (180.0f / sTransitionFadeTimer);
        D_8012A768 = 240.0f;
        D_8012A76C = 180.0f;
    } else {
        D_8012A758 = 240.0f;
        D_8012A75C = 180.0f;
        D_8012A760 = (-240.0f / sTransitionFadeTimer);
        D_8012A764 = (-180.0f / sTransitionFadeTimer);
        D_8012A768 = 0.0f;
        D_8012A76C = 0.0f;
    }

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 64; j++) {
            sTransitionTris[i][j].flags = 0x40;
            sTransitionTris[i][j].uv0.u = 0;
            sTransitionTris[i][j].uv0.v = 0;
            sTransitionTris[i][j].uv1.u = 0;
            sTransitionTris[i][j].uv1.v = 0;
            sTransitionTris[i][j].uv2.u = 0;
            sTransitionTris[i][j].uv2.v = 0;
        }
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            sTransitionTris[i][j * sizeof(Triangle)].vi0 = (i) + 1;
            sTransitionTris[i][j * sizeof(Triangle)].vi1 = (i) + 2;
            sTransitionTris[i][j * sizeof(Triangle)].vi2 = (i) + 3;
            sTransitionTris[i][j * sizeof(Triangle) + 1].vi0 = (i) + 1;
            sTransitionTris[i][j * sizeof(Triangle) + 1].vi1 = (i) + 2;
            sTransitionTris[i][j * sizeof(Triangle) + 1].vi2 = (i) + 3;
        }
    }

    sTransitionStatus = TRANSITION_ACTIVE;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/fade_transition/func_800C15D4.s")
#endif

void func_800C1EE8(s32 updateRate) {
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
void render_fade_circle(Gfx **dList, UNUSED MatrixS **mats, UNUSED Vertex **verts) {
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
void render_fade_waves(Gfx **dlist, UNUSED MatrixS **mats, UNUSED Vertex **verts) {
    Gfx *gfx;
    s32 i;
    Vertex *v;
    Triangle *t;
    reset_render_settings(dlist);
    gfx = *dlist;
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
    *dlist = gfx;
    reset_render_settings(dlist);
}

/**
 * Renders a transition effect on screen that will close in from the opposite corners of the screen.
 */
void render_fade_barndoor_diagonal(Gfx **dList, UNUSED MatrixS **mats, UNUSED Vertex **verts) {
    reset_render_settings(dList);
    gSPDisplayList((*dList)++, dTransitionShapeSettings);
    gSPVertexDKR((*dList)++, OS_PHYSICAL_TO_K0(sTransitionVtx[sTransitionTaskNum]), 10, 0);
    gSPPolygon((*dList)++, OS_PHYSICAL_TO_K0(sTransitionTris[sTransitionTaskNum]), 6, TRIN_DISABLE_TEXTURE);
    reset_render_settings(dList);
}

/**
 * Set the transition colour target, then set the velocity for the colour to fade to.
 */
void init_transition_blank(UNUSED FadeTransition *transition) {
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
void process_transition_disabled(s32 updateRate) {
    s32 var_v0;
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
void render_fade_disabled(Gfx **dList, UNUSED MatrixS **mats, UNUSED Vertex **verts) {
    s32 screenSize = fb_size();
    gSPDisplayList((*dList)++, dTransitionFadeSettings);
    gDPSetPrimColor((*dList)++, 0, 0, (gLastFadeRed >> 16), (gLastFadeGreen >> 16), (gLastFadeBlue >> 16), 255);
    gDPSetCombineMode((*dList)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPFillRectangle((*dList)++, 0, 0, screenSize & 0x3FF, (screenSize >> 16) & 0x3FF);
    reset_render_settings(dList);
}
