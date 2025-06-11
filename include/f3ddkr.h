#ifndef _F3DDKR_H_
#define _F3DDKR_H_

#include "PR/mbi.h"
#include "PR/gbi.h"

// This file is an extension of PR/gbi.h

/**
 * This section explains how billboarding works from a 3D geometry perspective.
 * Several modifications were made to the RSP to implement billboarding:
 * 
 * 1) For the gSPVertexDKR command, the last parameter is either 0 or 1 (G_VTX_APPEND):
 *    - If 0: Vertices are always written to the beginning of RSP's internal vertex array, and their count is stored.
 *    - If 1: Vertices are appended after those written with flag 0.
 * 
 * 2) The commands gDkrEnableBillboard and gDkrDisableBillboard control billboarding:
 *    - When gDkrEnableBillboard is active, vertices processed by gSPVertexDKR have their coordinates added to
 *      the coordinates of vertex 0 in RSP's vertex array.
 *    - This addition occurs after MVP matrix transformation but before perspective division (normalization of (x,y,z,w) to (x/w,y/w,z/w,1)).
 * 
 * Implementation Steps:
 * 1) First, push an anchor vertex using gSPVertexDKR. This vertex should have a standard MVP matrix applied
 *    (with normal perspective and camera setup like other 3D objects). Inside RSP, this vertex gets transformed
 *    to clip coordinates (x,y,z,w). Note: with standard perspective, w represents the vertex's distance from the camera.
 * 
 * 2) Create a billboard matrix (simplest case: identity matrix) and store it in slot G_MTX_DKR_INDEX_2.
 *    More complex versions can tilt the sprite or scale it along two axes. This matrix will be used for subsequent
 *    billboard vertices (without camera or projection transformations).
 * 
 * 3) Enable billboarding with gDkrEnableBillboard. All subsequent billboard vertices will be added to the anchor vertex.
 * 
 * 4) Push billboard vertices using gSPVertexDKR and render primitives with gSPPolygon. These vertices use sprite-space coordinates.
 *    Example: For a 32×64 sprite, vertices would be (0,0,0), (32,0,0), (32,64,0), (0,64,0).
 * 
 * How Coordinate Addition Works (Perspective Explanation):
 * Let the anchor vertex have coordinates (x,y,z,w) and our sprite be 32×64 as above. After normalization:
 * anchor becomes (x/w,y/w,z/w,1). A billboard vertex would have (x+32,y,z,w) → ((x+32)/w,y/w,z/w,1).
 * 
 * Screen-space implications (assuming 320px viewport width):
 * The sprite's on-screen width becomes (32/w)*160 pixels. Since w equals distance from camera, sprites
 * farther away appear smaller (creating perspective). However, additional scaling is needed because
 * without accounting for field of view and aspect ratio, a 32×64 sprite wouldn't match the size of
 * a 32×64 3D object at the same location.
 */

// Color combiner values.

// cycle 1 modes

#define	G_CC_ENVIRONMENT   0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT
// blend two textures, modulated by SHADE, alpha modulated between texture and 1 by PRIMITITIVE
#define G_CC_BLENDTEX_MODULATEA_1_PRIM TEXEL1, TEXEL0, SHADE, TEXEL0, 1, TEXEL0, PRIMITIVE, TEXEL0

// The following several modes, where blending with ENVIRONMENT is modulated by ENV_ALPHA,
// are likely used to create ambient lighting defined by EnvColor (color and intensity)

// Blend with ENVIRONMENT modulated by ENV_ALPHA, alpha unchanged
#define G_CC_BLENDI_ENV_ALPHA ENVIRONMENT, SHADE, ENV_ALPHA, SHADE, 0, 0, 0, SHADE
// Blend SHADE and ENVIRONMENT with ENV_ALPHA, alpha from PRIMITIVE
#define G_CC_BLENDI_ENV_ALPHA_A_PRIM ENVIRONMENT, SHADE, ENV_ALPHA, SHADE, 0, 0, 0, PRIMITIVE

// The following modes do not use vertex colors at all

// Blend TEXEL0 and ENVIRONMENT with ENV_ALPHA, alpha from PRIMITIVE
#define G_CC_BLENDT_ENV_ALPHA_A_PRIM ENVIRONMENT, TEXEL0, ENV_ALPHA, TEXEL0, 0, 0, 0, PRIMITIVE
// Blend TEXEL0 and ENVIRONMENT with ENV_ALPHA, alpha = TEXEL0 * PRIMITIVE
#define G_CC_BLENDT_ENV_ALPHA_A_TxP ENVIRONMENT, TEXEL0, ENV_ALPHA, TEXEL0, TEXEL0, 0, PRIMITIVE, 0
// Like above, but alpha = TEXEL1 * PRIMITIVE
#define G_CC_BLENDT_ENV_ALPHA_A_T1xP ENVIRONMENT, TEXEL0, ENV_ALPHA, TEXEL0, TEXEL1, 0, PRIMITIVE, 0

// Decal with alpha modulated by PRIMITIVE
#define G_CC_DECAL_A_PRIM 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0
// PRIMITIVE and TEXEL0 blend using SHADE_ALPHA, alpha = TEXEL0 * PRIMITIVE
#define G_CC_BLEND_SHADEALPHA TEXEL0, PRIMITIVE, SHADE_ALPHA, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0
// PRIM and ENV blend, alpha = TEXEL0 * PRIM
#define G_CC_BLENDPE_A_PRIM PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0
// TEXEL0 * SCALE, used in G_CYC_COPY, unclear purpose
#define G_CC_DECAL_SCALE TEXEL0, 0, SCALE, 0, 0, 0, 0, TEXEL0
// ENVIRONMENT color, alpha from TEXEL0, used for text
#define	G_CC_ENV_DECALA 0, 0, 0, ENVIRONMENT, 0, 0, 0, TEXEL0
// blend two textures, modulated by PRIMITIVE
// used for blinking lights
#define G_CC_BLENDTEX_PRIM TEXEL1, TEXEL0, PRIMITIVE, TEXEL0, TEXEL1, TEXEL0, PRIMITIVE, TEXEL0

// cycle 2 modes

// Alpha = COMBINED * PRIM
#define G_CC_MODULATEA_PRIM2 0, 0, 0, COMBINED, COMBINED, 0, PRIMITIVE, 0
// Blend with ENV using ENV_ALPHA, alpha = COMBINED * PRIM
#define G_CC_BLENDI_ENV_ALPHA_PRIM2 ENVIRONMENT, COMBINED, ENV_ALPHA, COMBINED, COMBINED, 0, PRIMITIVE, 0
// Blend with ENV using ENV_ALPHA, alpha unchanged
#define G_CC_BLEND_ENV_ALPHA2 ENVIRONMENT, COMBINED, ENV_ALPHA, COMBINED, 0, 0, 0, COMBINED
// Blend with ENV using SHADE, alpha unchanged; used after G_CC_BLEND_SHADEALPHA
#define G_CC_BLENDI_SHADE ENVIRONMENT, COMBINED, SHADE, COMBINED, 0, 0, 0, COMBINED
// Blend with ENV using ENV_ALPHA, alpha = COMBINED * SHADE; used for water
#define G_CC_BLENDI_ENV_ALPHA_MODULATEA2 ENVIRONMENT, COMBINED, ENV_ALPHA, COMBINED, COMBINED, 0, SHADE, 0
#define G_CC_MODULATEIDECALA2 COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED

// Inside the RSP, when we change otherMode, it sends the new mode to the RDP with the lower 4 bits set to 1.
// If we use the standard g*SPSetOtherMode macros, this doesn't matter to us.
// But in DKR, direct command transmission to the RDP is often used, bypassing processing in the RSP,
// so in custom code we also need to set those 4 bits to 1.
#define G_DKR_BLENDMASK 15

// OtherMode_H values.
#define DKR_OMH_COMMON G_DKR_BLENDMASK | G_PM_NPRIMITIVE | G_TD_CLAMP | G_TL_TILE | G_TC_FILT \
                     | G_CK_NONE | G_CD_MAGICSQ | G_AD_PATTERN

#define DKR_OMH_1CYC_POINT          DKR_OMH_COMMON | G_CYC_1CYCLE | G_TT_NONE   | G_TF_POINT  | G_TP_PERSP
#define DKR_OMH_1CYC_POINT_NOPERSP  DKR_OMH_COMMON | G_CYC_1CYCLE | G_TT_NONE   | G_TF_POINT  | G_TP_NONE
#define DKR_OMH_1CYC_BILERP         DKR_OMH_COMMON | G_CYC_1CYCLE | G_TT_NONE   | G_TF_BILERP | G_TP_PERSP
#define DKR_OMH_1CYC_BILERP_NOPERSP DKR_OMH_COMMON | G_CYC_1CYCLE | G_TT_NONE   | G_TF_BILERP | G_TP_NONE
#define DKR_OMH_1CYC_CI_BILERP      DKR_OMH_COMMON | G_CYC_1CYCLE | G_TT_RGBA16 | G_TF_BILERP | G_TP_PERSP
#define DKR_OMH_2CYC_BILERP         DKR_OMH_COMMON | G_CYC_2CYCLE | G_TT_NONE   | G_TF_BILERP | G_TP_PERSP
#define DKR_OMH_2CYC_POINT          DKR_OMH_COMMON | G_CYC_2CYCLE | G_TT_NONE   | G_TF_POINT  | G_TP_PERSP
#define DKR_OMH_2CYC_POINT_NOPERSP  DKR_OMH_COMMON | G_CYC_2CYCLE | G_TT_NONE   | G_TF_POINT  | G_TP_NONE
#define DKR_OMH_2CYC_CI_BILERP      DKR_OMH_COMMON | G_CYC_2CYCLE | G_TT_RGBA16 | G_TF_BILERP | G_TP_PERSP

#define DKR_OMH_COPY_POINT_NOPERSP G_DKR_BLENDMASK | G_PM_NPRIMITIVE | G_TD_CLAMP | G_TL_TILE | G_TC_FILT \
                                 | G_CK_NONE | G_CD_DISABLE | G_AD_PATTERN | G_CYC_COPY | G_TT_NONE       \
                                 | G_TF_POINT  | G_TP_NONE
    
// OtherMode_L values.
#define DKR_OML_COMMON G_AC_NONE | G_ZS_PIXEL

// modified version of RM_AA_ZB_XLU_LINE, with ALPHA_CVG_SEL disabled
#define	RM_AA_ZB_XLU_LINE_MOD(clk) \
    AA_EN | Z_CMP | IM_RD | CVG_X_ALPHA | \
    FORCE_BL | CVG_DST_CLAMP | ZMODE_XLU | \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define G_RM_AA_ZB_XLU_LINE_MOD RM_AA_ZB_XLU_LINE_MOD(1)
#define G_RM_AA_ZB_XLU_LINE_MOD2 RM_AA_ZB_XLU_LINE_MOD(2)

// Temporary until all commands are properly defined.
#define fast3d_cmd(pkt, word0, word1) \
{                                     \
    Gfx *_g = (Gfx*)(pkt);            \
    _g->words.w0 = word0;             \
    _g->words.w1 = word1;             \
}

/****** F3DDKR display list commands ******/

#define G_TRIN  5
#define G_DMADL 7
#define G_MTX_DKR_INDEX_0 0
#define G_MTX_DKR_INDEX_1 1
#define G_MTX_DKR_INDEX_2 2
#define G_MW_BILLBOARD 0x02 //0x01 = billboarding enabled, 0x00 = disabled
#define G_MW_MVPMATRIX 0x0A  //Specifies the index of the mvp matrix. 
#define G_VTX_APPEND 1

#define gDkrEnableBillboard(pkt)            \
	gMoveWd(pkt, G_MW_BILLBOARD, 0, 1)  

#define gDkrDisableBillboard(pkt)           \
	gMoveWd(pkt, G_MW_BILLBOARD, 0, 0)

#define gSPVertexDKR(pkt, v, n, v0) \
    gDma1p(pkt, G_VTX, v, (((n) * 8 + (n)) << 1) + 8, ((n)-1)<<3|(((u32)(v) & 6))|(v0))

#define gSPMatrixDKR(pkt, m, i) \
    gSPMatrix(pkt, m, (i) << 6)
#define gSPSelectMatrixDKR(pkt, num)   \
	gMoveWd(pkt, G_MW_MVPMATRIX, 0, (num) << 6)

#define TRIN_DISABLE_TEXTURE 0
#define TRIN_ENABLE_TEXTURE 1

#define gSPPolygon(dl, ptr, numTris, texEnabled) {                                                                                  \
    Gfx *_g = (Gfx *)(dl);                                                                                                          \
    _g->words.w0 = _SHIFTL((((numTris) - 1) << 4) | (texEnabled), 16, 8) | _SHIFTL(G_TRIN, 24, 8) | _SHIFTL(((numTris)*16), 0, 16); \
    _g->words.w1 = (unsigned int)(ptr);                                                                                             \
}

#define numberOfGfxCommands(gfxCmds) (sizeof(gfxCmds) / sizeof(Gfx))

#define gDkrDmaDisplayList(pkt, address, numberOfCommands)                         \
{                                                                                  \
    Gfx *_g = (Gfx *)(pkt);                                                        \
                                                                                   \
    _g->words.w0 = (_SHIFTL(G_DMADL, 24, 8) | _SHIFTL((numberOfCommands), 16, 8) | \
            _SHIFTL((numberOfCommands*8), 0, 16));                                 \
    _g->words.w1 = (unsigned int)(address);                                        \
}

#define gDPSetPrimColorRGBA(pkt, rgba)             \
{                                                  \
    Gfx *_g = (Gfx *)(pkt);                        \
    _g->words.w0 = _SHIFTL(G_SETPRIMCOLOR, 24, 8); \
    _g->words.w1 = rgba;                           \
}

#define gDPSetEnvColorRGBA(pkt, rgba)             \
{                                                 \
    Gfx *_g = (Gfx *)(pkt);                       \
    _g->words.w0 = _SHIFTL(G_SETENVCOLOR, 24, 8); \
    _g->words.w1 = rgba;                          \
}

#if defined(F3DDKR_GBI)
 // ?????? - Needed to modify this to work with matching material_init
#undef TXL2WORDS_4b
#define TXL2WORDS_4b(txls) ((txls)/16)
#endif

#endif
