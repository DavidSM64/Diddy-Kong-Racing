/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C0170 */

#include "fade_transition.h"

#include "types.h"
#include "macros.h"
#include "f3ddkr.h"
#include "asset_enums.h"
#include "memory.h"
#include "PR/libultra.h"
#include "video.h"
#include "textures_sprites.h"

/************ .data ************/

s32 gTransitionsDisabled = FALSE;
s32 sLevelTransitionDelayTimer = 0; // Set when a level is loaded after a transition, to hold it for a few extra frames.
s32 D_800E31A8 = 0;
s32 sTransitionStatus = TRANSITION_NONE;
u16 sTransitionFadeTimer = 0;
u16 sTransitionFlags = 0;
u16 D_800E31B8 = 0;
s8 D_800E31BC = 0;
VertexList *sTransitionVtx[2] = { NULL, NULL };
TriangleList *sTransitionTris[2] = { NULL, NULL };
s32 sTransitionTaskNum[2] = { 0, 0 }; // The second index goes unused. Is it even an array at all?

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

VertexList D_800E3230[28] = {
    0xFE20, 0x0078, 0xFEC0, 0x0078, 0xFF60, 0x0078, 0x0000, 0x0078,
    0x00A0, 0x0078, 0x0140, 0x0078, 0x01E0, 0x0078, 0xFE20, 0xFF88,
    0xFEC0, 0xFF88, 0xFF60, 0xFF88, 0x0000, 0xFF88, 0x00A0, 0xFF88,
    0x0140, 0xFF88, 0x01E0, 0xFF88,
};

VertexList D_800E3268[28] = {
    0xFF60, 0x0168, 0xFF60, 0x00F0, 0xFF60, 0x0078, 0xFF60, 0x0000,
    0xFF60, 0xFF88, 0xFF60, 0xFF10, 0xFF60, 0xFF10, 0x00A0, 0x0168,
    0x00A0, 0x00F0, 0x00A0, 0x0078, 0x00A0, 0x0000, 0x00A0, 0xFF88,
    0x00A0, 0xFF10, 0x00A0, 0xFF10,
};

TriangleList D_800E32A0[12] = {
    0x00, 0x02, 0x04, 0x0E, 0x10, 0x12, 0x08, 0x0A,
    0x0C, 0x16, 0x18, 0x1A,
};

TriangleList D_800E32AC[12] = {
    0x04, 0x06, 0x08, 0x12, 0x14, 0x16, 0x04, 0x06,
    0x08, 0x12, 0x14, 0x16,
};

s8 D_800E32B8[24] = {
    0, 3, 1, 1, 3, 4, 1, 4,
    2, 2, 4, 5, 6, 9, 7, 7,
    9, 10, 7, 10, 8, 8, 10, 11,
};

s8 D_800E32D0[12] = {
    -1, -1, 0, -1, -1, 0, 0, -1, -1, 0, -1, -1,
};

VertexList D_800E32DC[24] = {
    0xFCE0, 0x0078, 0xFE20, 0x0078, 0xFF60, 0x0078, 0x00A0, 0x0078,
    0x01E0, 0x0078, 0x0320, 0x0078, 0xFCE0, 0xFF88, 0xFE20, 0xFF88,
    0xFF60, 0xFF88, 0x00A0, 0xFF88, 0x01E0, 0xFF88, 0x0320, 0xFF88,
};

s8 D_800E330C[12] = {
    0, 2, 4, 12, 14, 8, 10, 18, 20, 22, 0, 0,
};

s8 D_800E3318[12] = {
    4, 6, 8, 16, 18, 4, 6, 14, 16, 18, 0, 0,
};

s8 D_800E3324[20] = {
    0, 1, 3, 1, 3, 4, 1, 4, 2, 5, 7, 8, 5, 8, 6, 6, 8, 9, 0, 0,
};

s8 D_800E3338[12] = {
    -1, -1, 0, -1, 0, 0, -1, 0, -1, -1, 0, 0,
};

VertexList D_800E3344[126] = {
    0xFF60, 0x00A0, 0xFF70, 0x00A0, 0xFF80, 0x00A0, 0xFF90, 0x00A0,
    0xFFA0, 0x00A0, 0xFFB0, 0x00A0, 0xFFC0, 0x00A0, 0xFFD0, 0x00A0,
    0xFFE0, 0x00A0, 0xFFF0, 0x00A0, 0x0000, 0x00A0, 0x0010, 0x00A0,
    0x0020, 0x00A0, 0x0030, 0x00A0, 0x0040, 0x00A0, 0x0050, 0x00A0,
    0x0060, 0x00A0, 0x0070, 0x00A0, 0x0080, 0x00A0, 0x0090, 0x00A0,
    0x00A0, 0x00A0, 0xFF60, 0xFF38, 0xFF70, 0xFF60, 0xFF80, 0xFF74,
    0xFF90, 0xFF7E, 0xFFA0, 0xFF74, 0xFFB0, 0xFF38, 0xFFC0, 0xFF10,
    0xFFD0, 0xFEFC, 0xFFE0, 0xFEF2, 0xFFF0, 0xFEFC, 0x0000, 0xFF24,
    0x0010, 0xFF2E, 0x0020, 0xFF38, 0x0030, 0xFF2E, 0x0040, 0xFF24,
    0x0050, 0xFEFC, 0x0060, 0xFEF2, 0x0070, 0xFEFC, 0x0080, 0xFF24,
    0x0090, 0xFF60, 0x00A0, 0xFF74, 0xFF60, 0xFEE8, 0xFF70, 0xFEE8,
    0xFF80, 0xFEE8, 0xFF90, 0xFEE8, 0xFFA0, 0xFEE8, 0xFFB0, 0xFEE8,
    0xFFC0, 0xFEE8, 0xFFD0, 0xFEE8, 0xFFE0, 0xFEE8, 0xFFF0, 0xFEE8,
    0x0000, 0xFEE8, 0x0010, 0xFEE8, 0x0020, 0xFEE8, 0x0030, 0xFEE8,
    0x0040, 0xFEE8, 0x0050, 0xFEE8, 0x0060, 0xFEE8, 0x0070, 0xFEE8,
    0x0080, 0xFEE8, 0x0090, 0xFEE8, 0x00A0, 0xFEE8,
};

TriangleList D_800E3440[92] = {
    0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E,
    0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E,
    0x0E, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1A, 0x0E,
    0x10, 0x12, 0x14, 0x16, 0x18, 0x1A, 0x1A, 0x1C,
    0x1E, 0x20, 0x22, 0x24, 0x26, 0x28, 0x1A, 0x1C,
    0x1E, 0x20, 0x22, 0x24, 0x26, 0x28, 0x00, 0x02,
    0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x54, 0x56,
    0x58, 0x5A, 0x5C, 0x5E, 0x60, 0x62, 0x0E, 0x10,
    0x12, 0x14, 0x16, 0x18, 0x1A, 0x62, 0x64, 0x66,
    0x68, 0x6A, 0x6C, 0x6E, 0x1A, 0x1C, 0x1E, 0x20,
    0x22, 0x24, 0x26, 0x28, 0x6E, 0x70, 0x72, 0x74,
    0x76, 0x78, 0x7A, 0x7C,
};

TriangleList D_800E349C[92] = {
    0x2A, 0x2C, 0x2E, 0x30, 0x32, 0x34, 0x36, 0x38,
    0x54, 0x56, 0x58, 0x5A, 0x5C, 0x5E, 0x60, 0x62,
    0x38, 0x3A, 0x3C, 0x3E, 0x40, 0x42, 0x44, 0x62,
    0x64, 0x66, 0x68, 0x6A, 0x6C, 0x6E, 0x44, 0x46,
    0x48, 0x4A, 0x4C, 0x4E, 0x50, 0x52, 0x6E, 0x70,
    0x72, 0x74, 0x76, 0x78, 0x7A, 0x7C, 0x54, 0x56,
    0x58, 0x5A, 0x5C, 0x5E, 0x60, 0x62, 0x54, 0x56,
    0x58, 0x5A, 0x5C, 0x5E, 0x60, 0x62, 0x62, 0x64,
    0x66, 0x68, 0x6A, 0x6C, 0x6E, 0x62, 0x64, 0x66,
    0x68, 0x6A, 0x6C, 0x6E, 0x6E, 0x70, 0x72, 0x74,
    0x76, 0x78, 0x7A, 0x7C, 0x6E, 0x70, 0x72, 0x74,
    0x76, 0x78, 0x7A, 0x7C,
};

s8 D_800E34F8[92] = {
    0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1,
    0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, 0, 0,
    0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
};

TriangleList D_800E3554[244] = {
    0, 8, 9, 0, 9, 1, 1, 9, 10, 1, 10, 2, 2, 10, 11, 2,
    11, 3, 3, 11, 12, 3, 12, 4, 4, 12, 13, 4, 13, 5, 5, 13,
    14, 5, 14, 6, 6, 14, 15, 6, 15, 7, 0, 7, 8, 0, 8, 1,
    1, 8, 9, 1, 9, 2, 2, 9, 10, 2, 10, 3, 3, 10, 11, 3,
    11, 4, 4, 11, 12, 4, 12, 5, 5, 12, 13, 5, 13, 6, 0, 8,
    9, 0, 9, 1, 1, 9, 10, 1, 10, 2, 2, 10, 11, 2, 11, 3,
    3, 11, 12, 3, 12, 4, 4, 12, 13, 4, 13, 5, 5, 13, 14, 5,
    14, 6, 6, 14, 15, 6, 15, 7, 0, 8, 9, 0, 9, 1, 1, 9,
    10, 1, 10, 2, 2, 10, 11, 2, 11, 3, 3, 11, 12, 3, 12, 4,
    4, 12, 13, 4, 13, 5, 5, 13, 14, 5, 14, 6, 6, 14, 15, 6,
    15, 7, 0, 7, 8, 0, 8, 1, 1, 8, 9, 1, 9, 2, 2, 9,
    10, 2, 10, 3, 3, 10, 11, 3, 11, 4, 4, 11, 12, 4, 12, 5,
    5, 12, 13, 5, 13, 6, 0, 8, 9, 0, 9, 1, 1, 9, 10, 1,
    10, 2, 2, 10, 11, 2, 11, 3, 3, 11, 12, 3, 12, 4, 4, 12,
    13, 4, 13, 5, 5, 13, 14, 5, 14, 6, 6, 14, 15, 6, 15, 7,
    0, 0, 0, 0,
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
s32 D_8012A744;
s32 D_8012A748;
s32 D_8012A74C;
f32 sTransitionOpacity;
f32 gTransitionOpacityVel;
s32 D_8012A758;
s32 D_8012A75C;
s32 D_8012A760;
s32 D_8012A764;
s32 D_8012A768;
s32 D_8012A76C;
s32 D_8012A770;
s32 D_8012A774;
s32 D_8012A778;
s32 D_8012A77C;

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

//@bug: This doesn't seem to guarantee a return.
u32 fxFadeOn(void) {
    u32 isActive = sTransitionFadeTimer != 0;
    if (isActive == FALSE) {
        isActive = sTransitionFlags != 0;
        if (isActive) {
            return (D_800E31BC != 0);
        }
    }
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
    D_800E31B8 = transition->duration;
    sTransitionFlags = transition->unk6;
    D_800E31BC = !(transition->type & FADE_FLAG_UNK2);
    gCurFadeTransition = transition->type & 0x3F;
    D_800E31A8 = transition->type & FADE_FLAG_UNK1;
    sLevelTransitionDelayTimer = 0;
    if (!D_800E31BC && !sLevelTransitionDelayTimer) {
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
            func_800C0B00(transition, 12, 8, D_800E3230, D_800E32A0, D_800E32AC, D_800E32D0, D_800E32D0, D_800E32B8);
            break;
        case FADE_BARNDOOR_VERTICAL:
            func_800C0B00(transition, 12, 8, D_800E3268, D_800E32A0, D_800E32AC, D_800E32D0, D_800E32D0, D_800E32B8);
            break;
        case FADE_CIRCLE:
            func_800C15D4(transition);
            break;
        case FADE_WAVES:
            func_800C0B00(transition, 92, 80, D_800E3344, D_800E349C, D_800E3440, D_800E34F8, D_800E34F8, D_800E3554);
            break;
        case FADE_BARNDOOR_DIAGONAL:
            func_800C0B00(transition, 10, 6, D_800E32DC, D_800E330C, D_800E3318, D_800E3338, D_800E3338, D_800E3324);
            break;
        case FADE_DISABLED:
            func_800C2640(transition);
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
    } else if (updateRate >= LOGIC_10FPS) { // Redundant because the logic update rate is clamped before this function is called.
        updateRate = LOGIC_12FPS;
    }

    if (sTransitionStatus != TRANSITION_NONE) {
        if (sTransitionFadeTimer == 0) {
            sTransitionStatus = TRANSITION_LEVELSWAP;
        }
        if ((sTransitionFadeTimer == 0) && (sTransitionFlags == 0)) {
            transition_end();
        } else {
            if (sTransitionFadeTimer > 0) {
                sTransitionTaskNum[0] = 1 - sTransitionTaskNum[0]; // Haven't you heard of a XOR, Rareware employee?
            }
            switch (gCurFadeTransition) {
                case FADE_FULLSCREEN:
                    func_800C0834(updateRate);
                    break;
                case FADE_BARNDOOR_HORIZONTAL:
                case FADE_BARNDOOR_VERTICAL:
                case FADE_WAVES:
                case FADE_BARNDOOR_DIAGONAL:
                    func_800C1130(updateRate);
                    break;
                case FADE_CIRCLE:
                    func_800C1EE8(updateRate);
                    break;
                case FADE_DISABLED:
                    func_800C27A0(updateRate);
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
        if (osTvType == TV_TYPE_PAL) {
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
        free_from_memory_pool(sTransitionVtx[0]);
        sTransitionVtx[0] = NULL;
        sTransitionVtx[1] = NULL;
        sTransitionTris[0] = NULL;
        sTransitionTris[1] = NULL;
    }
    sTransitionStatus = TRANSITION_NONE;
    sTransitionTaskNum[0] = 0;
}

/**
 * Sets the transition timer and opacity to positive or negative depending on whether to fade in or out.
*/
void transition_fullscreen_start(FadeTransition *transition) {
    if (transition->type & 0x80) {
        sTransitionOpacity = 255.0f;
        gTransitionOpacityVel = -255.0f / (f32) sTransitionFadeTimer;
    } else {
        sTransitionOpacity = 0.0f;
        gTransitionOpacityVel = 255.0f / (f32) sTransitionFadeTimer;
    }
    sTransitionStatus = TRANSITION_ACTIVE;
}

void func_800C0834(s32 updateRate) {
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
        } else if (sTransitionFlags != 0xFFFF) {
            if (updateRate < sTransitionFlags) {
                sTransitionFlags -= updateRate;
            } else {
                updateRate -= sTransitionFlags;
                sTransitionFlags = 0;
                if (D_800E31A8 != 0) {
                    D_800E31A8 = 0;
                    sTransitionFadeTimer = D_800E31B8;
                    gTransitionOpacityVel = -gTransitionOpacityVel;
                    var_v0 = FALSE;
                }
            }
        }
    } while (var_v0 == FALSE && (updateRate > 0));
}

/**
 * Draws a simple fillrect covering the whole screen that fades in or out.
*/
void render_fade_fullscreen(Gfx **dList, UNUSED MatrixS **mats, UNUSED Vertex **verts) {
    s32 screenSize = get_video_width_and_height_as_s32();
    gSPDisplayList((*dList)++, dTransitionFadeSettings);
    gDPSetPrimColor((*dList)++, 0, 0, gCurFadeRed, gCurFadeGreen, gCurFadeBlue, gCurFadeAlpha);
    gDPSetCombineMode((*dList)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPFillRectangle((*dList)++, 0, 0, screenSize & 0x3FF, (screenSize >> 16) & 0x3FF);
    reset_render_settings(dList);
}

GLOBAL_ASM("asm/non_matchings/fade_transition/func_800C0B00.s")
GLOBAL_ASM("asm/non_matchings/fade_transition/func_800C1130.s")

/**
 * Renders a transition effect on screen that will close in from both sides horizonally.
*/
void render_fade_barndoor_horizontal(Gfx **dList, UNUSED MatrixS **mats, UNUSED Vertex **verts) {
    reset_render_settings(dList);
    gSPDisplayList((*dList)++, dTransitionShapeSettings);
    gSPVertexDKR((*dList)++, OS_PHYSICAL_TO_K0(sTransitionVtx[sTransitionTaskNum[0]]), 12, 0);
    gSPPolygon((*dList)++, OS_PHYSICAL_TO_K0(sTransitionTris[sTransitionTaskNum[0]]), 8, TRIN_DISABLE_TEXTURE);
    reset_render_settings(dList);
}

/**
 * Renders a transition effect on screen that will close in from both sides vertically.
 * Codewase, exactly the same as above, but uses a different vertex layout to make the difference.
*/
void render_fade_barndoor_vertical(Gfx **dList, UNUSED MatrixS **mats, UNUSED Vertex **verts) {
    reset_render_settings(dList);
    gSPDisplayList((*dList)++, dTransitionShapeSettings);
    gSPVertexDKR((*dList)++, OS_PHYSICAL_TO_K0(sTransitionVtx[sTransitionTaskNum[0]]), 12, 0);
    gSPPolygon((*dList)++, OS_PHYSICAL_TO_K0(sTransitionTris[sTransitionTaskNum[0]]), 8, TRIN_DISABLE_TEXTURE);
    reset_render_settings(dList);
}

GLOBAL_ASM("asm/non_matchings/fade_transition/func_800C15D4.s")
GLOBAL_ASM("asm/non_matchings/fade_transition/func_800C1EE8.s")

#define NUM_OF_VERTS 18
#define NUM_OF_TRIS 16
void render_fade_circle(Gfx **dList, UNUSED MatrixS **mats, UNUSED Vertex **verts) {
    Vertex *vertsToRender;
    Triangle *trisToRender;
    Gfx *gfx;
    s32 i;

    reset_render_settings(dList);
    gfx = *dList;

    vertsToRender = (Vertex *) sTransitionVtx[sTransitionTaskNum[0]];
    trisToRender = (Triangle *) sTransitionTris[sTransitionTaskNum[0]];
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

#ifdef NON_EQUIVALENT
// This doesn't work properly.
void render_fade_waves(Gfx **dList, UNUSED MatrixS **mats, UNUSED Vertex **verts) {
    Gfx *gfx;
    s32 i;

    reset_render_settings(dList);
    gfx = *dList;

    gSPDisplayList(gfx++, dTransitionShapeSettings);

    for(i = 0; i < 6; i++) {
        s32 index = sTransitionTaskNum[0] + i;
        if(i != 1 && i != 4) {
            gSPVertexDKR(gfx++, OS_PHYSICAL_TO_K0(sTransitionVtx[index]), 14, 0);
            gSPPolygon(gfx++, OS_PHYSICAL_TO_K0(sTransitionTris[index]), 14, TRIN_DISABLE_TEXTURE);
        } else {
            gSPVertexDKR(gfx++, OS_PHYSICAL_TO_K0(sTransitionVtx[index]), 16, 0);
            gSPPolygon(gfx++, OS_PHYSICAL_TO_K0(sTransitionTris[index]), 12, TRIN_DISABLE_TEXTURE);
        }
    }

    *dList = gfx;
    reset_render_settings(dList);
}
#else
GLOBAL_ASM("asm/non_matchings/fade_transition/render_fade_waves.s")
#endif

/**
 * Renders a transition effect on screen that will close in from the opposite corners of the screen.
*/
void render_fade_barndoor_diagonal(Gfx **dList, UNUSED MatrixS **mats, UNUSED Vertex **verts) {
    reset_render_settings(dList);
    gSPDisplayList((*dList)++, dTransitionShapeSettings);
    gSPVertexDKR((*dList)++, OS_PHYSICAL_TO_K0(sTransitionVtx[sTransitionTaskNum[0]]), 10, 0);
    gSPPolygon((*dList)++, OS_PHYSICAL_TO_K0(sTransitionTris[sTransitionTaskNum[0]]), 6, TRIN_DISABLE_TEXTURE);
    reset_render_settings(dList);
}

void func_800C2640(UNUSED FadeTransition *transition) {
    gLastFadeRed <<= 0x10;
    gLastFadeGreen <<= 0x10;
    gLastFadeBlue <<= 0x10;
    gCurFadeAlpha = 0xFF;
    sTransitionOpacity = 255.0f;
    gTransitionOpacityVel = 0.0f;
    D_8012A744 = (s32) ((gCurFadeRed << 0x10) - gLastFadeRed) / (s32) sTransitionFadeTimer;
    D_8012A748 = (s32) ((gCurFadeGreen << 0x10) - gLastFadeGreen) / (s32) sTransitionFadeTimer;
    D_8012A74C = (s32) ((gCurFadeBlue << 0x10) - gLastFadeBlue) / (s32) sTransitionFadeTimer;
    sTransitionStatus = 1;
}

void func_800C27A0(s32 updateRate) {
    s32 var_v0;
    do {
        var_v0 = TRUE;
        if (sTransitionFadeTimer > 0) {
            gLastFadeRed += D_8012A744 * updateRate;
            gLastFadeGreen += D_8012A748 * updateRate;
            gLastFadeBlue += D_8012A74C * updateRate;
            if (updateRate >= sTransitionFadeTimer) {
                gLastFadeRed = gCurFadeRed << 0x10;
                gLastFadeGreen = gCurFadeGreen << 0x10;
                gLastFadeBlue = gCurFadeBlue << 0x10;
                updateRate -= sTransitionFadeTimer;
                sTransitionFadeTimer = 0;
            } else {
                sTransitionFadeTimer -= updateRate;
            }
        } else {
            if (sTransitionFlags != 0xFFFF) {
                sTransitionFlags -= updateRate;
                if (sTransitionFlags <= 0) {
                    sTransitionFlags = 0;
                }
            }
        }
    } while (var_v0 == FALSE);
}

void render_fade_disabled(Gfx **dList, UNUSED MatrixS **mats, UNUSED Vertex **verts) {
    s32 screenSize = get_video_width_and_height_as_s32();
    gSPDisplayList((*dList)++, dTransitionFadeSettings);
    gDPSetPrimColor((*dList)++, 0, 0, (gLastFadeRed >> 16), (gLastFadeGreen >> 16), (gLastFadeBlue >> 16), 255);
    gDPSetCombineMode((*dList)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPFillRectangle((*dList)++, 0, 0, screenSize & 0x3FF, (screenSize >> 16) & 0x3FF);
    reset_render_settings(dList);
}
