/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8007AC70 */

#include "textures_sprites.h"
#include "gzip.h"
#include "asset_loading.h"
#include "memory.h"
#include "math_util.h"
#include "tracks.h"

#define TEX_HEADER_COUNT 175
#define TEX_SPRITE_COUNT 50
#define TEX_PALLETE_COUNT 20

/************ .data ************/

u32 gTexColourTag = COLOUR_TAG_MAGENTA;
s32 gSpriteOpaque = TRUE;

// See "include/f3ddkr.h" for the defines

Gfx dRenderSettingsVtxAlpha[][2] = {
    // Semitransparent Vertex Alpha'd surface (Zsorted)
    DRAW_TABLE_GROUP(G_CC_MODULATEIA, DKR_CC_UNK0, DKR_OMH_2CYC_BILERP, DKR_RM_UNKNOWN0, G_RM_XLU_SURF2,
                     DKR_RM_UNKNOWN0, G_RM_AA_XLU_SURF2, DKR_RM_UNKNOWN0, G_RM_ZB_XLU_SURF2, DKR_RM_UNKNOWN0,
                     G_RM_AA_ZB_XLU_SURF2),
    // Semitransparent Vertex Alpha'd surface (No Zsort)
    DRAW_TABLE_GROUP(G_CC_MODULATEIA, DKR_CC_UNK1, DKR_OMH_2CYC_BILERP, DKR_RM_UNKNOWN1, G_RM_XLU_SURF2,
                     DKR_RM_UNKNOWN1, G_RM_AA_XLU_SURF2, DKR_RM_UNKNOWN1, G_RM_ZB_XLU_SURF2, DKR_RM_UNKNOWN1,
                     G_RM_AA_ZB_XLU_SURF2),
};

Gfx dRenderSettingsSpriteCld[][2] = {
    // Semitransparent Sprite (Preserve coverage)
    DRAW_TABLE_ENTRY(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_POINT, G_RM_CLD_SURF, G_RM_CLD_SURF2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_POINT, G_RM_ZB_CLD_SURF,
                     G_RM_ZB_CLD_SURF2)
};

// Should probably be merged with dRenderSettingsSpriteCld
Gfx dRenderSettingsSpriteXlu[][2] = {
    // Semitransparent Sprite (Overwrite coverage)
    DRAW_TABLE_ENTRY(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_POINT, G_RM_XLU_SURF, G_RM_XLU_SURF2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_POINT, DKR_RM_UNKNOWN2_1,
                     DKR_RM_UNKNOWN2_2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_POINT, DKR_RM_UNKNOWN3_1,
                     DKR_RM_UNKNOWN3_2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_POINT, G_RM_AA_ZB_XLU_INTER,
                     G_RM_AA_ZB_XLU_INTER2),
    // Semitransparent Sprite (Overwrite coverage) (Copy)
    DRAW_TABLE_ENTRY(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_POINT, G_RM_XLU_SURF, G_RM_XLU_SURF2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_POINT, DKR_RM_UNKNOWN2_1,
                     DKR_RM_UNKNOWN2_2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_POINT, DKR_RM_UNKNOWN3_1,
                     DKR_RM_UNKNOWN3_2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_POINT, G_RM_AA_ZB_XLU_INTER,
                     G_RM_AA_ZB_XLU_INTER2)
};

Gfx dRenderSettingsCommon[][2] = {
    // Opaque Surface
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA, DKR_OMH_1CYC_BILERP, G_RM_OPA_SURF, G_RM_OPA_SURF2,
                     G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2, G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2, G_RM_AA_ZB_OPA_SURF,
                     G_RM_AA_ZB_OPA_SURF2),
    // Semitransparent Surface
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA, DKR_OMH_1CYC_BILERP, G_RM_XLU_SURF, G_RM_XLU_SURF2,
                     G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2, G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2, G_RM_AA_ZB_XLU_SURF,
                     G_RM_AA_ZB_XLU_SURF2),
    // Opaque Surface with fog
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, DKR_CC_UNK1, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A, G_RM_OPA_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_OPA_SURF2, G_RM_FOG_SHADE_A, G_RM_ZB_OPA_SURF2, G_RM_FOG_SHADE_A,
                     G_RM_AA_ZB_OPA_SURF2),
    // Semitransparent Surface with fog
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, DKR_CC_UNK1, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A, G_RM_XLU_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2, G_RM_FOG_SHADE_A,
                     G_RM_AA_ZB_XLU_SURF2),
    // Cutout Surface with primitive colour
    DRAW_TABLE_GROUP(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_BILERP, G_RM_XLU_SURF, G_RM_XLU_SURF2,
                     G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2,
                     G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2),
    // Cutout Surface with primitive colour (Copy)
    DRAW_TABLE_GROUP(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_BILERP, G_RM_XLU_SURF, G_RM_XLU_SURF2,
                     G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2,
                     G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2),
    // Cutout Surface with primitive colour and fog
    DRAW_TABLE_GROUP(G_CC_MODULATEIA_PRIM, DKR_CC_UNK2, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A, G_RM_XLU_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2, G_RM_FOG_SHADE_A,
                     G_RM_AA_ZB_XLU_INTER2),
    // Cutout Surface with primitive colour and fog (Zsorted interpenetrating)
    DRAW_TABLE_GROUP(G_CC_MODULATEIA_PRIM, DKR_CC_UNK2, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A, G_RM_XLU_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_INTER2 | Z_UPD,
                     G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_INTER2),
    // Opaque Surface with indexed texture
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA, DKR_OMH_1CYC_CI_BILERP, G_RM_OPA_SURF, G_RM_OPA_SURF2,
                     G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2, G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2, G_RM_AA_ZB_OPA_SURF,
                     G_RM_AA_ZB_OPA_SURF2),
    // Semitransparent Surface with indexed texture
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA, DKR_OMH_1CYC_CI_BILERP, G_RM_XLU_SURF, G_RM_XLU_SURF2,
                     G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2, G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2, G_RM_AA_ZB_XLU_SURF,
                     G_RM_AA_ZB_XLU_SURF2),
    // Opqaue Surface with indexed texture and fog
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, G_CC_PASS2, DKR_OMH_2CYC_CI_BILERP, G_RM_FOG_SHADE_A, G_RM_OPA_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_OPA_SURF2, G_RM_FOG_SHADE_A, G_RM_ZB_OPA_SURF2, G_RM_FOG_SHADE_A,
                     G_RM_AA_ZB_OPA_SURF2),
    // Semitransparent Surface with indexed texture and fog
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, G_CC_PASS2, DKR_OMH_2CYC_CI_BILERP, G_RM_FOG_SHADE_A, G_RM_XLU_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2, G_RM_FOG_SHADE_A,
                     G_RM_AA_ZB_XLU_SURF2),
    // Opaque Surface with indexed texture. (Cutout)
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA, DKR_OMH_1CYC_CI_BILERP, G_RM_OPA_SURF, G_RM_OPA_SURF2,
                     G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2, G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2, G_RM_AA_ZB_OPA_SURF,
                     G_RM_AA_ZB_OPA_SURF2),
    // Semitransparent Surface with indexed texture (Cutout)
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA, DKR_OMH_1CYC_CI_BILERP, G_RM_XLU_SURF, G_RM_XLU_SURF2,
                     G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2,
                     G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2),
    // Opqaue Surface with indexed texture and fog (Cutout)
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, G_CC_PASS2, DKR_OMH_2CYC_CI_BILERP, G_RM_FOG_SHADE_A, G_RM_OPA_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_OPA_SURF2, G_RM_FOG_SHADE_A, G_RM_ZB_OPA_SURF2, G_RM_FOG_SHADE_A,
                     G_RM_AA_ZB_OPA_SURF2),
    // Semitransparent Surface with indexed texture and fog (Cutout)
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, G_CC_PASS2, DKR_OMH_2CYC_CI_BILERP, G_RM_FOG_SHADE_A, G_RM_XLU_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2, G_RM_FOG_SHADE_A,
                     G_RM_AA_ZB_XLU_INTER2),
};

Gfx dRenderSettingsCutout[][2] = {
    // Semitransparent Surface
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_BILERP, G_RM_XLU_SURF, G_RM_XLU_SURF2,
                     G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2, DKR_RM_UNKNOWN4_1,
                     DKR_RM_UNKNOWN4_2),
    // Semitransparent Surface (Copy)
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_BILERP, G_RM_XLU_SURF, G_RM_XLU_SURF2,
                     G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2, DKR_RM_UNKNOWN4_1,
                     DKR_RM_UNKNOWN4_2),
    // Semitransparent Surface with fog
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, DKR_CC_UNK1, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A, G_RM_XLU_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2, G_RM_FOG_SHADE_A,
                     DKR_RM_UNKNOWN4_2),
    // Semitransparent Surface with fog (Copy)
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, DKR_CC_UNK1, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A, G_RM_XLU_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2, G_RM_FOG_SHADE_A,
                     DKR_RM_UNKNOWN4_2),
};

Gfx dRenderSettingsDecal[][2] = {
    // Opaque Decal.
    DRAW_TABLE_ENTRY(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA, DKR_OMH_1CYC_BILERP, G_RM_ZB_OPA_DECAL,
                     G_RM_ZB_OPA_DECAL2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA, DKR_OMH_1CYC_BILERP, G_RM_AA_ZB_OPA_DECAL,
                     G_RM_AA_ZB_OPA_DECAL2),
    // Semitransparent Decal.
    DRAW_TABLE_ENTRY(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA, DKR_OMH_1CYC_BILERP, G_RM_ZB_XLU_DECAL,
                     G_RM_ZB_XLU_DECAL2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA, DKR_OMH_1CYC_BILERP, G_RM_AA_ZB_XLU_DECAL,
                     G_RM_AA_ZB_XLU_DECAL2),
    // Opaque Decal with fog.
    DRAW_TABLE_ENTRY(G_CC_MODULATEIDECALA, DKR_CC_UNK1, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A, G_RM_ZB_OPA_DECAL2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIDECALA, DKR_CC_UNK1, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_DECAL2),
    // Semitransparent Decal with fog.
    DRAW_TABLE_ENTRY(G_CC_MODULATEIDECALA, DKR_CC_UNK1, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A, G_RM_ZB_XLU_DECAL2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIDECALA, DKR_CC_UNK1, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    // Opaque Decal with indexed texture.
    DRAW_TABLE_ENTRY(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA, DKR_OMH_1CYC_CI_BILERP, G_RM_ZB_OPA_DECAL,
                     G_RM_ZB_OPA_DECAL2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA, DKR_OMH_1CYC_CI_BILERP, G_RM_AA_ZB_OPA_DECAL,
                     G_RM_AA_ZB_OPA_DECAL2),
    // Semitransparent Decal with indexed texture.
    DRAW_TABLE_ENTRY(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA, DKR_OMH_1CYC_CI_BILERP, G_RM_ZB_XLU_DECAL,
                     G_RM_ZB_XLU_DECAL2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA, DKR_OMH_1CYC_CI_BILERP, G_RM_AA_ZB_XLU_DECAL,
                     G_RM_AA_ZB_XLU_DECAL2),
    // Opaque Decal with indexed texture and fog.
    DRAW_TABLE_ENTRY(G_CC_MODULATEIDECALA, G_CC_PASS2, DKR_OMH_2CYC_CI_BILERP, G_RM_FOG_SHADE_A, G_RM_ZB_OPA_DECAL2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIDECALA, G_CC_PASS2, DKR_OMH_2CYC_CI_BILERP, G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_DECAL2),
    // Semitransparent Decal with indexed texture and fog.
    DRAW_TABLE_ENTRY(G_CC_MODULATEIDECALA, G_CC_PASS2, DKR_OMH_2CYC_CI_BILERP, G_RM_FOG_SHADE_A, G_RM_ZB_XLU_DECAL2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIDECALA, G_CC_PASS2, DKR_OMH_2CYC_CI_BILERP, G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2)
};

Gfx dRenderSettingsSolidColourVtxAlpha[][2] = {
    DRAW_TABLE_GROUP(DKR_CC_UNK3, G_CC_MODULATEIA_PRIM2, DKR_OMH_2CYC_POINT, G_RM_NOOP, G_RM_XLU_SURF2, G_RM_NOOP,
                     G_RM_AA_XLU_SURF2, G_RM_NOOP, G_RM_ZB_XLU_SURF2, G_RM_NOOP, G_RM_AA_ZB_XLU_SURF2),
};

Gfx dRenderSettingsSolidColour[][2] = {
    // Opaque Surface
    DRAW_TABLE_GROUP(DKR_CC_UNK4, DKR_CC_UNK4, DKR_OMH_1CYC_POINT, G_RM_OPA_SURF, G_RM_OPA_SURF2, G_RM_AA_OPA_SURF,
                     G_RM_AA_OPA_SURF2, G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2, G_RM_AA_ZB_OPA_INTER,
                     G_RM_AA_ZB_OPA_INTER2),
    // Semitransparent Surface
    DRAW_TABLE_GROUP(DKR_CC_UNK4, DKR_CC_UNK4, DKR_OMH_1CYC_POINT, G_RM_XLU_SURF, G_RM_XLU_SURF2, G_RM_AA_XLU_SURF,
                     G_RM_AA_XLU_SURF2, G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2, G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    // Opaque Surface with fog
    DRAW_TABLE_GROUP(DKR_CC_UNK4, G_CC_MODULATEIA_PRIM2, DKR_OMH_2CYC_POINT, G_RM_FOG_SHADE_A, G_RM_OPA_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_OPA_SURF2, G_RM_FOG_SHADE_A, G_RM_ZB_OPA_SURF2, G_RM_FOG_SHADE_A,
                     G_RM_AA_ZB_OPA_SURF2),
    // Semitransparent Surface
    DRAW_TABLE_GROUP(DKR_CC_UNK4, G_CC_MODULATEIA_PRIM2, DKR_OMH_2CYC_POINT, G_RM_FOG_SHADE_A, G_RM_XLU_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2, G_RM_FOG_SHADE_A,
                     G_RM_AA_ZB_XLU_SURF2),
};

// Some kind of texture on top of a solid colour
Gfx dRenderSettingsPrimOverlay[][2] = {
    // Opaque Surface
    DRAW_TABLE_ENTRY(DKR_CC_DECALFADEPRIM, DKR_CC_DECALFADEPRIM, DKR_OMH_1CYC_BILERP, G_RM_ZB_OPA_DECAL,
                     G_RM_ZB_OPA_DECAL2),
    DRAW_TABLE_ENTRY(DKR_CC_DECALFADEPRIM, DKR_CC_DECALFADEPRIM, DKR_OMH_1CYC_BILERP, G_RM_AA_ZB_OPA_DECAL,
                     G_RM_AA_ZB_OPA_DECAL2),
    // Semitransparent Surface
    DRAW_TABLE_ENTRY(DKR_CC_DECALFADEPRIM, DKR_CC_DECALFADEPRIM, DKR_OMH_1CYC_BILERP, G_RM_ZB_XLU_DECAL,
                     G_RM_ZB_XLU_DECAL2),
    DRAW_TABLE_ENTRY(DKR_CC_DECALFADEPRIM, DKR_CC_DECALFADEPRIM, DKR_OMH_1CYC_BILERP, G_RM_AA_ZB_XLU_DECAL,
                     G_RM_AA_ZB_XLU_DECAL2),
    // Opaque Surface with indexed texture
    DRAW_TABLE_ENTRY(DKR_CC_DECALFADEPRIM, DKR_CC_DECALFADEPRIM, DKR_OMH_1CYC_CI_BILERP, G_RM_ZB_OPA_DECAL,
                     G_RM_ZB_OPA_DECAL2),
    DRAW_TABLE_ENTRY(DKR_CC_DECALFADEPRIM, DKR_CC_DECALFADEPRIM, DKR_OMH_1CYC_CI_BILERP, G_RM_AA_ZB_OPA_DECAL,
                     G_RM_AA_ZB_OPA_DECAL2),
    // Semitransparent Surface with indexed texture
    DRAW_TABLE_ENTRY(DKR_CC_DECALFADEPRIM, DKR_CC_DECALFADEPRIM, DKR_OMH_1CYC_CI_BILERP, G_RM_ZB_XLU_DECAL,
                     G_RM_ZB_XLU_DECAL2),
    DRAW_TABLE_ENTRY(DKR_CC_DECALFADEPRIM, DKR_CC_DECALFADEPRIM, DKR_OMH_1CYC_CI_BILERP, G_RM_AA_ZB_XLU_DECAL,
                     G_RM_AA_ZB_XLU_DECAL2)
};

// Not sure what it is specifically, but some onscreen actors like TT and Taj use it.
Gfx dRenderSettingsPrimCol[][2] = {
    // Opaque Surface
    DRAW_TABLE_GROUP(DKR_CC_UNK5, DKR_CC_UNK6, DKR_OMH_2CYC_BILERP, G_RM_NOOP, G_RM_OPA_SURF2, G_RM_NOOP,
                     G_RM_AA_OPA_SURF2, G_RM_NOOP, G_RM_ZB_OPA_SURF2, G_RM_NOOP, G_RM_AA_ZB_OPA_SURF2),
    // Semitransparent Surface
    DRAW_TABLE_GROUP(DKR_CC_UNK5, DKR_CC_UNK6, DKR_OMH_2CYC_BILERP, G_RM_NOOP, G_RM_XLU_SURF2, G_RM_NOOP,
                     G_RM_AA_XLU_SURF2, G_RM_NOOP, G_RM_ZB_XLU_SURF2, G_RM_NOOP, G_RM_AA_ZB_XLU_SURF2),
    // Opaque Surface with indexed texture
    DRAW_TABLE_GROUP(DKR_CC_UNK5, DKR_CC_UNK6, DKR_OMH_2CYC_CI_BILERP, G_RM_NOOP, G_RM_OPA_SURF2, G_RM_NOOP,
                     G_RM_AA_OPA_SURF2, G_RM_NOOP, G_RM_ZB_OPA_SURF2, G_RM_NOOP, G_RM_AA_ZB_OPA_SURF2),
    // Semitransparent Surface with indexed texture
    DRAW_TABLE_GROUP(DKR_CC_UNK5, DKR_CC_UNK6, DKR_OMH_2CYC_CI_BILERP, G_RM_NOOP, G_RM_XLU_SURF2, G_RM_NOOP,
                     G_RM_AA_XLU_SURF2, G_RM_NOOP, G_RM_AA_ZB_TEX_EDGE2, G_RM_NOOP, G_RM_AA_ZB_XLU_INTER2),
};

// Only opaque surface is actually used here.
Gfx dRenderSettingsBlinkingLights[][2] = {
    // Opaque Surface
    DRAW_TABLE_GROUP(DKR_CC_UNK7, DKR_CC_UNK8, DKR_OMH_2CYC_BILERP, G_RM_NOOP, G_RM_OPA_SURF2, G_RM_NOOP,
                     G_RM_AA_OPA_SURF2, G_RM_NOOP, G_RM_ZB_OPA_SURF2, G_RM_NOOP, G_RM_AA_ZB_OPA_SURF2),
    // Semitransparent Surface
    DRAW_TABLE_GROUP(DKR_CC_UNK7, DKR_CC_UNK8, DKR_OMH_2CYC_BILERP, G_RM_NOOP, G_RM_XLU_SURF2, G_RM_NOOP,
                     G_RM_AA_XLU_SURF2, G_RM_NOOP, G_RM_ZB_XLU_SURF2, G_RM_NOOP, G_RM_AA_ZB_XLU_SURF2),
    // Opaque Surface with fog
    DRAW_TABLE_GROUP(DKR_CC_UNK7, DKR_CC_UNK8, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A, G_RM_OPA_SURF2, G_RM_FOG_SHADE_A,
                     G_RM_AA_OPA_SURF2, G_RM_FOG_SHADE_A, G_RM_ZB_OPA_SURF2, G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    // Semitransparent Surface with fog
    DRAW_TABLE_GROUP(DKR_CC_UNK7, DKR_CC_UNK8, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A, G_RM_XLU_SURF2, G_RM_FOG_SHADE_A,
                     G_RM_AA_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    // Cutout Surface
    DRAW_TABLE_GROUP(DKR_CC_UNK7, DKR_CC_UNK8, DKR_OMH_2CYC_BILERP, G_RM_NOOP, G_RM_XLU_SURF2, G_RM_NOOP,
                     G_RM_AA_XLU_SURF2, G_RM_NOOP, G_RM_AA_ZB_TEX_EDGE2, G_RM_NOOP, DKR_RM_UNKNOWN4_2),
    // Cutout Surface (Copy)
    DRAW_TABLE_GROUP(DKR_CC_UNK7, DKR_CC_UNK8, DKR_OMH_2CYC_BILERP, G_RM_NOOP, G_RM_XLU_SURF2, G_RM_NOOP,
                     G_RM_AA_XLU_SURF2, G_RM_NOOP, G_RM_AA_ZB_TEX_EDGE2, G_RM_NOOP, DKR_RM_UNKNOWN4_2),
    // Cutout Surface with fog
    DRAW_TABLE_GROUP(DKR_CC_UNK7, DKR_CC_UNK8, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A, G_RM_XLU_SURF2, G_RM_FOG_SHADE_A,
                     G_RM_AA_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2, G_RM_FOG_SHADE_A, DKR_RM_UNKNOWN4_2),
    // Cutout Surface with fog (Copy)
    DRAW_TABLE_GROUP(DKR_CC_UNK7, DKR_CC_UNK8, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A, G_RM_XLU_SURF2, G_RM_FOG_SHADE_A,
                     G_RM_AA_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2, G_RM_FOG_SHADE_A, DKR_RM_UNKNOWN4_2),
};

Gfx D_800DF3A8[] = {
    gsDPPipeSync(),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPClearGeometryMode(G_ZBUFFER | G_FOG),
    gsSPEndDisplayList(),
};

Gfx D_800DF3D8[] = {
    gsDPPipeSync(),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPClearGeometryMode(G_FOG),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPEndDisplayList(),
};

Gfx D_800DF410[][2] = {
    DRAW_TABLE_ENTRY(DKR_CC_UNK9, DKR_CC_UNK9, DKR_OMH_1CYC_BILERP_NOPERSP, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2),
    DRAW_TABLE_ENTRY(G_CC_BLENDPE, G_CC_BLENDPE, DKR_OMH_1CYC_BILERP, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2),
    DRAW_TABLE_ENTRY(DKR_CC_UNK9, G_CC_PASS2, DKR_OMH_2CYC_BILERP, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2)
};

/*******************************/

/************ .rodata ************/

const char D_800E7B30[] = "Error: Texture no %x out of range on load. !!\n";
const char D_800E7B60[] = "TEX Error: Palette memory overflow!!\n";
const char D_800E7B88[] = "TEX Error: TexTab overflow!!\n";
const char D_800E7BA8[] = "texFreeTexture: NULL tex!!\n";
const char D_800E7BC4[] = "TEX Error: Tryed to deallocate non-existent texture!!\n";
const char D_800E7BFC[] = "SRPBUF overflow!!\n";
const char D_800E7C10[] = "Error: Sprite table overflow!!\n";
const char D_800E7C30[] = "texFreeSprite: NULL sprite!!\n";
const char D_800E7C50[] = "TEXSPR Error: Tryed to deallocate non-existent sprite!!\n";

/*********************************/

/************ .bss ************/

s32 *gTextureAssetTable[2];

s32 *gTextureCache;

u8 *gCiPalettes;
s32 gNumberOfLoadedTextures;
s32 D_80126334;
s32 gTextureAssetID[2];
s32 gCiPalettesSize;
s32 D_80126344;
s32 *gSpriteOffsetTable;

s32 *gSpriteCache;

Sprite *gCurrentSprite;
s32 gSpriteTableNum;
s32 D_80126358;
s32 D_8012635C;
Vertex *D_80126360;
Gfx *D_80126364;
Triangle *D_80126368;

TempTexHeader *gTempTextureHeader;
u8 *D_80126370;
s32 gCurrentRenderFlags;
s32 gBlockedRenderFlags;
TextureHeader *gCurrentTextureHeader;
s16 gUsingTexture;
s16 gForceFlags;
s16 gUsePrimColour;

/******************************/

/**
 * Load the texture table from ROM and allocate space for all the texture asset management.
 */
void tex_init_textures(void) {
    s32 i;

    gTextureCache = mempool_alloc_safe(sizeof(TextureHeader) * TEX_HEADER_COUNT, COLOUR_TAG_MAGENTA);
    gCiPalettes = mempool_alloc_safe(0x280, COLOUR_TAG_MAGENTA);
    gNumberOfLoadedTextures = 0;
    gCiPalettesSize = 0;
    gTextureAssetTable[TEX_TABLE_2D] = (s32 *) load_asset_section_from_rom(ASSET_TEXTURES_2D_TABLE);
    gTextureAssetTable[TEX_TABLE_3D] = (s32 *) load_asset_section_from_rom(ASSET_TEXTURES_3D_TABLE);

    for (i = 0; gTextureAssetTable[TEX_TABLE_2D][i] != -1; i++) {}
    gTextureAssetID[TEX_TABLE_2D] = --i;

    for (i = 0; gTextureAssetTable[TEX_TABLE_3D][i] != -1; i++) {}
    gTextureAssetID[TEX_TABLE_3D] = --i;

    gSpriteCache = mempool_alloc_safe(sizeof(Sprite) * TEX_SPRITE_COUNT, COLOUR_TAG_MAGENTA);
    gCurrentSprite = mempool_alloc_safe(sizeof(Sprite) * 32, COLOUR_TAG_MAGENTA);
    D_80126358 = 0;
    gSpriteOffsetTable = (s32 *) load_asset_section_from_rom(ASSET_SPRITES_TABLE);
    gSpriteTableNum = 0;
    while (gSpriteOffsetTable[gSpriteTableNum] != -1) {
        gSpriteTableNum++;
    }
    gSpriteTableNum--;

    gTempTextureHeader = mempool_alloc_safe(0x28, COLOUR_TAG_MAGENTA);
    D_80126344 = 0;
}

/**
 * Official Name: texDisableModes
 * Add flags to the block list so they are removed when drawn.
 */
void tex_disable_modes(s32 flags) {
    gBlockedRenderFlags |= flags;
}

/**
 * Official Name: texEnableModes
 * Remove flags to the block list so they are no longer removed when drawn.
 */
void tex_enable_modes(s32 flags) {
    gBlockedRenderFlags &= ~flags;
}

/**
 * Return the texture asset ID table for 2D textures.
 * Goes unused.
 */
UNUSED s32 get_loaded_2D_textures(void) {
    return gTextureAssetID[TEX_TABLE_2D];
}

/**
 * Return the texture asset ID table for 3D textures.
 * Goes unused.
 */
UNUSED s32 get_loaded_3D_textures(void) {
    return gTextureAssetID[TEX_TABLE_3D];
}

UNUSED s32 func_8007AE64(void) {
    return gSpriteTableNum;
}

#ifdef NON_EQUIVALENT
// Minor matching issues with loops, but should be functionally the same.
// Official Name: texLoadTexture
TextureHeader *load_texture(s32 arg0) {
    s32 assetSection;
    s32 assetIndex;
    s32 assetOffset;
    s32 assetSize;
    s32 assetTable;
    s32 texIndex;
    s32 temp_a1;
    s32 paletteOffset;
    s32 i;
    u8 *alignedAddress;
    TextureHeader *tex;
    TextureHeader *texTemp;
    s32 numberOfTextures;
    s32 sp3C;
    s32 temp_a0;
    s32 temp_v0_5;

    arg0 &= 0xFFFF;
    assetIndex = arg0;
    assetSection = ASSET_TEXTURES_2D;
    assetTable = 0;
    if (arg0 & 0x8000) {
        assetTable = 1;
        assetIndex = arg0 & 0x7FFF;
        assetSection = ASSET_TEXTURES_3D;
    }
    if ((assetIndex >= gTextureAssetID[assetTable]) || (assetIndex < 0)) {
        arg0 = 0;
    }
    for (i = 0; i < gNumberOfLoadedTextures; i++) {
        if (arg0 == gTextureCache[(i << 1)]) {
            tex = gTextureCache[(i << 1) + 1];
            tex->numberOfInstances++;
            return tex;
        }
    }
    assetOffset = gTextureAssetTable[assetTable][assetIndex];
    assetSize = gTextureAssetTable[assetTable][assetIndex + 1] - assetOffset;
    load_asset_to_address(assetSection, gTempTextureHeader, assetOffset, 0x28);
    numberOfTextures = (gTempTextureHeader->header.numOfTextures >> 8) & 0xFFFF;

    if (!gTempTextureHeader->header.isCompressed) {
        tex = mempool_alloc((numberOfTextures * 0x60) + assetSize, gTexColourTag);
        if (tex == NULL) {
            return NULL;
        }
        load_asset_to_address(assetSection, tex, assetOffset, assetSize);
    } else {
        temp_v0_5 = byteswap32(&gTempTextureHeader->uncompressedSize);
        temp_a0 = (numberOfTextures * 0x60) + temp_v0_5;
        sp3C = temp_v0_5 + 0x20;
        tex = mempool_alloc(temp_a0 + 0x20, gTexColourTag);
        if (tex == NULL) {
            return NULL;
        }
        temp_a1 = ((s32) tex + sp3C) - assetSize;
        temp_a1 -= temp_a1 % 0x10;
        load_asset_to_address(assetSection, temp_a1, assetOffset, assetSize);
        gzip_inflate(temp_a1 + 0x20, tex);
        assetSize = sp3C - 0x20;
    }
    texIndex = -1;
    for (i = 0; i < gNumberOfLoadedTextures; i++) {
        if (gTextureCache[(i << 1)] == -1) {
            texIndex = i;
        }
    }
    if (texIndex == -1) {
        texIndex = gNumberOfLoadedTextures++;
    }
    gTextureCache[(texIndex << 1)] = arg0;
    gTextureCache[(texIndex << 1) + 1] = tex;
    paletteOffset = -1;
    if ((tex->format & 0xF) == TEX_FORMAT_CI4) {
        if (D_80126344 == 0) {
            load_asset_to_address(ASSET_EMPTY_14, &gCiPalettes[gCiPalettesSize], tex->ciPaletteOffset, 32);
            tex->ciPaletteOffset = gCiPalettesSize;
            gCiPalettesSize += 32; // (32 bytes / 2 bytes per color) = 16 colors.
        }
        paletteOffset = gCiPalettesSize - 32;
    }
    if ((tex->format & 0xF) == TEX_FORMAT_CI8) {
        if (D_80126344 == 0) {
            load_asset_to_address(ASSET_EMPTY_14, &gCiPalettesSize[gCiPalettes], tex->ciPaletteOffset, 128);
            tex->ciPaletteOffset = gCiPalettesSize;
            gCiPalettesSize += 128; // (128 bytes / 2 bytes per color) = 64 colors.
        }
        paletteOffset = gCiPalettesSize - 128;
    }
    D_80126344 = 0;
    texTemp = tex;
    alignedAddress = align16((u8 *) ((s32) texTemp + assetSize));
    for (i = 0; i < numberOfTextures; i++) {
        build_tex_display_list(texTemp, alignedAddress);
        if (paletteOffset >= 0) {
            texTemp->ciPaletteOffset = paletteOffset;
            alignedAddress += 0x30; // I'm guessing it takes 6 f3d commands to load the palette
        }
        alignedAddress += 0x60; // I'm guessing it takes 12 f3d commands to load the texture
        texTemp = (TextureHeader *) ((s32) texTemp + texTemp->textureSize);
    }
    if (gCiPalettesSize >= 0x280) {
        return NULL;
    }
    if (gNumberOfLoadedTextures >= 701) {
        return NULL;
    }
    return tex;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/textures_sprites/load_texture.s")
#endif

/**
 * This function frees textures
 * Official Name: texFreeTexture
 */
void free_texture(TextureHeader *tex) {
    s32 i;

    if (tex != 0) {
        if ((--tex->numberOfInstances) <= 0) {
            for (i = 0; i < gNumberOfLoadedTextures; i++) {
                if ((s32) tex == gTextureCache[(i << 1) + 1]) {
                    mempool_free(tex);

                    gTextureCache[(i << 1)] = -1;
                    gTextureCache[(i << 1) + 1] = -1;
                    return;
                }
            }
        }
    }
}

/**
 * Set the colour tag that determines which memory pool textures will be loaded into.
 * By default, this generally stays as COLOUR_TAG_MAGENTA
 * Official Name: setTexMemColour
 */
void set_texture_colour_tag(s32 tagID) {
    gTexColourTag = tagID;
}

UNUSED s32 func_8007B380(s32 arg0) {
    if ((arg0 < 0) || (arg0 >= gNumberOfLoadedTextures)) {
        return 0;
    }
    if (gTextureCache[(arg0 << 1) + 1] == -1) {
        return 0;
    }
    return gTextureCache[(arg0 << 1) + 1];
}

/**
 * Resets all render settings to the default state.
 * The next draw call will be forced to apply all settings instead of skipping unecessary steps.
 * Official Name: texDPInit
 */
void reset_render_settings(Gfx **dlist) {
    gCurrentTextureHeader = NULL;
    gCurrentRenderFlags = RENDER_NONE;
    gUsingTexture = FALSE;
    gForceFlags = TRUE;
    gBlockedRenderFlags = RENDER_NONE;
    gUsePrimColour = FALSE;
    gDPPipeSync((*dlist)++);
    gSPSetGeometryMode((*dlist)++, G_SHADING_SMOOTH | G_SHADE | G_ZBUFFER);
}

/**
 * Enables usage of combiners utilising the indidual primitive colours.
 */
void enable_primitive_colour(void) {
    gUsePrimColour = TRUE;
    gForceFlags = TRUE;
}

/**
 * Disables usage of combiners utilising the indidual primitive colours.
 */
void disable_primitive_colour(void) {
    gUsePrimColour = FALSE;
    gForceFlags = TRUE;
}

/**
 * Shift the texture header by the offset and return the result.
 * Official Name: texFrame
 */
TextureHeader *set_animated_texture_header(TextureHeader *texHead, s32 offset) {
    if (offset > 0) {
        if (offset < texHead->numOfTextures << 8) {
            texHead = (TextureHeader *) (((u8 *) texHead) + ((offset >> 16) * texHead->textureSize));
        } else {
            texHead = (TextureHeader *) (((u8 *) texHead) + ((texHead->numOfTextures >> 8) - 1) * texHead->textureSize);
        }
    }
    return texHead;
}

/**
 * A version of the function below that chooses not to pass along an offset.
 */
void load_and_set_texture_no_offset(Gfx **dlist, TextureHeader *texhead, u32 flags) {
    load_and_set_texture(dlist, texhead, flags, 0);
}

/**
 * Load a texture from memory into texture memory.
 * Also set render mode, combine mode and othermodes based on flags.
 * Also tracks which modes are active, to prevent setting them again if they're already active.
 * A number can be attached that adds a texture address offset. An example of this being used is
 * the numbered doors in the hub, to change what number is written on it.
 */
void load_and_set_texture(Gfx **dlist, TextureHeader *texhead, s32 flags, s32 texOffset) {
    s32 forceFlags;
    s32 doPipeSync;
    s32 dlIndex;

    forceFlags = gForceFlags;
    doPipeSync = TRUE;

    if (texhead != NULL) {
        if (texOffset && (texOffset < texhead->numOfTextures << 8)) {
            texhead = (TextureHeader *) ((s8 *) texhead + ((texOffset >> 16) * texhead->textureSize));
        }

        flags |= texhead->flags;
        if (texhead != gCurrentTextureHeader) {
            gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(texhead->cmd), texhead->numberOfCommands);
            gCurrentTextureHeader = texhead;
            doPipeSync = FALSE;
        }
        if (gUsingTexture == FALSE) {
            forceFlags = TRUE;
            gUsingTexture = TRUE;
        }
    } else if (gUsingTexture) {
        forceFlags = TRUE;
        gUsingTexture = FALSE;
    }

    flags = (gUsePrimColour)
                ? (flags & (RENDER_DECAL | RENDER_COLOUR_INDEX | RENDER_ANTI_ALIASING | RENDER_Z_COMPARE |
                            RENDER_SEMI_TRANSPARENT))
                : (flags & (RENDER_VTX_ALPHA | RENDER_DECAL | RENDER_Z_UPDATE | RENDER_COLOUR_INDEX | RENDER_CUTOUT |
                            RENDER_FOG_ACTIVE | RENDER_SEMI_TRANSPARENT | RENDER_Z_COMPARE | RENDER_ANTI_ALIASING));
    flags &= ~gBlockedRenderFlags;
    flags = (flags & RENDER_VTX_ALPHA) ? flags & ~RENDER_FOG_ACTIVE : flags & ~RENDER_Z_UPDATE;

    if (flags != gCurrentRenderFlags || forceFlags) {
        if (doPipeSync) {
            gDPPipeSync((*dlist)++);
        }

        if (((flags & RENDER_VTX_ALPHA) != (gCurrentRenderFlags & RENDER_VTX_ALPHA)) || gForceFlags) {
            if (flags & RENDER_VTX_ALPHA || gUsePrimColour) {
                gSPClearGeometryMode((*dlist)++, G_FOG);
            } else {
                gSPSetGeometryMode((*dlist)++, G_FOG);
            }
        }

        if (((flags & RENDER_Z_COMPARE) != (gCurrentRenderFlags & RENDER_Z_COMPARE)) || gForceFlags) {
            if (flags & RENDER_Z_COMPARE) {
                gSPSetGeometryMode((*dlist)++, G_ZBUFFER);
            } else {
                gSPClearGeometryMode((*dlist)++, G_ZBUFFER);
            }
        }

        gForceFlags = FALSE;
        gCurrentRenderFlags = flags;
        if (!gUsingTexture) {
            if (flags & RENDER_VTX_ALPHA) {
                gDkrDmaDisplayList(
                    (*dlist)++,
                    OS_PHYSICAL_TO_K0(
                        dRenderSettingsSolidColourVtxAlpha[flags & (RENDER_ANTI_ALIASING | RENDER_Z_COMPARE)]),
                    numberOfGfxCommands(dRenderSettingsSolidColourVtxAlpha[0]));
                return;
            }
            gDkrDmaDisplayList(
                (*dlist)++,
                OS_PHYSICAL_TO_K0(dRenderSettingsSolidColour[flags & (RENDER_FOG_ACTIVE | RENDER_SEMI_TRANSPARENT |
                                                                      RENDER_Z_COMPARE | RENDER_ANTI_ALIASING)]),
                numberOfGfxCommands(dRenderSettingsSolidColour[0]));
            return;
        }

        if (gUsePrimColour) {
            if (flags & RENDER_DECAL && flags & RENDER_Z_COMPARE) {
                dlIndex = 0;
                if (flags & RENDER_ANTI_ALIASING) {
                    dlIndex |= 1; // Anti Aliasing
                }
                if (flags & RENDER_SEMI_TRANSPARENT) {
                    dlIndex |= 2; // Z Compare
                }
                if (flags & RENDER_COLOUR_INDEX) {
                    dlIndex |= 4; // Colour Index
                }
                gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(dRenderSettingsPrimOverlay[dlIndex]),
                                   numberOfGfxCommands(dRenderSettingsPrimOverlay[0]));
                return;
            }
            if (flags & RENDER_COLOUR_INDEX) {
                flags = (flags ^ RENDER_COLOUR_INDEX) | RENDER_FOG_ACTIVE;
            }
            gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(dRenderSettingsPrimCol[flags]),
                               numberOfGfxCommands(dRenderSettingsPrimCol[0]));
            return;
        }

        if (flags & RENDER_DECAL && flags & RENDER_Z_COMPARE) {
            dlIndex = 0;
            if (flags & RENDER_ANTI_ALIASING) {
                dlIndex |= 1; // Anti Aliasing
            }
            if (flags & RENDER_SEMI_TRANSPARENT) {
                dlIndex |= 2; // Z Compare
            }
            if (flags & RENDER_FOG_ACTIVE) {
                dlIndex |= 4; // Fog
            }
            if (flags & RENDER_COLOUR_INDEX) {
                dlIndex |= 8; // Colour Index
            }
            gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(dRenderSettingsDecal[dlIndex]),
                               numberOfGfxCommands(dRenderSettingsDecal[0]));
            return;
        }

        if (flags & RENDER_CUTOUT) {
            dlIndex = flags & (RENDER_ANTI_ALIASING | RENDER_Z_COMPARE | RENDER_SEMI_TRANSPARENT);
            if (flags & RENDER_FOG_ACTIVE) {
                dlIndex |= 8; // Fog
            }
            gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(dRenderSettingsCutout[dlIndex]),
                               numberOfGfxCommands(dRenderSettingsCutout[0]));
            return;
        }

        flags &= ~RENDER_DECAL;
        if (flags & RENDER_VTX_ALPHA) {
            dlIndex = flags & (RENDER_ANTI_ALIASING | RENDER_Z_COMPARE);
            if (flags & RENDER_Z_UPDATE) {
                dlIndex |= 4; // Z write
            } else {
                gSPSetGeometryMode((*dlist)++, G_ZBUFFER);
                gCurrentRenderFlags |= RENDER_Z_COMPARE;
            }
            gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(dRenderSettingsVtxAlpha[dlIndex]),
                               numberOfGfxCommands(dRenderSettingsVtxAlpha[0]));
            return;
        }

        gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(dRenderSettingsCommon[flags]),
                           numberOfGfxCommands(dRenderSettingsCommon[0]));
        return;
    }
}

/**
 * Loads the texture and render settings for the blinking lights seen in Spaceport Alpha.
 */
void load_blinking_lights_texture(Gfx **dlist, TextureHeader *texture_list, u32 flags, s32 texture_index) {
    u16 *mblock;
    u16 *tblock;
    if ((texture_index != 0) && (texture_index < (texture_list->numOfTextures * 256))) {
        texture_list = (TextureHeader *) ((s32) texture_list + ((texture_index >> 16) * texture_list->textureSize));
    }
    mblock = (u16 *) (texture_list + 1);
    tblock = mblock + 0x400;
    if (texture_list->width == 64) {
        gDPLoadMultiBlock((*dlist)++, OS_K0_TO_PHYSICAL(mblock), 256, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 16, 0, 0, 0,
                          6, 4, 0, 0);
        gDPLoadTextureBlock((*dlist)++, OS_K0_TO_PHYSICAL(tblock), G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 16, 0, 0, 0, 6, 4,
                            0, 0);
    } else {
        gDPLoadMultiBlock((*dlist)++, OS_K0_TO_PHYSICAL(mblock), 256, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, 0, 0,
                          5, 5, 0, 0);
        gDPLoadTextureBlock((*dlist)++, OS_K0_TO_PHYSICAL(tblock), G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, 0, 0, 5, 5,
                            0, 0);
    }

    gDPPipeSync((*dlist)++);
    gCurrentTextureHeader = 0;
    flags &= (RENDER_ANTI_ALIASING | RENDER_Z_COMPARE | RENDER_SEMI_TRANSPARENT | RENDER_FOG_ACTIVE | RENDER_CUTOUT);
    gSPSetGeometryMode((*dlist)++, G_FOG);

    if (flags & RENDER_Z_COMPARE) {
        gSPSetGeometryMode((*dlist)++, G_ZBUFFER);
    } else {
        gSPClearGeometryMode((*dlist)++, G_ZBUFFER);
    }
    gForceFlags = TRUE;
    gCurrentRenderFlags = RENDER_NONE;
    gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(dRenderSettingsBlinkingLights[flags]),
                       numberOfGfxCommands(dRenderSettingsBlinkingLights[0]));
}

/**
 * Set whether to use an opaque render mode for sprites.
 */
void sprite_opaque(s32 setting) {
    gSpriteOpaque = setting;
    gForceFlags = TRUE;
}

void func_8007BF34(Gfx **dlist, s32 flags) {
    if ((flags != gCurrentRenderFlags) || gForceFlags) {
        gDPPipeSync((*dlist)++);
        if ((gCurrentRenderFlags & RENDER_VTX_ALPHA) || gForceFlags) {
            gSPSetGeometryMode((*dlist)++, G_FOG);
        }
        flags &= ~RENDER_VTX_ALPHA;
        flags &= ~gBlockedRenderFlags;
        if (((flags & RENDER_Z_COMPARE) != (gCurrentRenderFlags & RENDER_Z_COMPARE)) || gForceFlags) {
            if (flags & RENDER_Z_COMPARE) {
                gSPSetGeometryMode((*dlist)++, G_ZBUFFER);
            } else {
                gSPClearGeometryMode((*dlist)++, G_ZBUFFER);
            }
        }
        gForceFlags = FALSE;
        gCurrentRenderFlags = flags;
        flags &= ~RENDER_DECAL;
        if (gSpriteOpaque == FALSE) {
            if ((gCurrentRenderFlags & RENDER_PRESERVE_COVERAGE)) {
                gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(dRenderSettingsSpriteCld[(flags >> 1) & 1]),
                                   numberOfGfxCommands(dRenderSettingsSpriteCld[0]));
            } else {
                // fake ^ 0 required for some reason
                gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(dRenderSettingsSpriteXlu[(flags - 16) ^ 0]),
                                   numberOfGfxCommands(dRenderSettingsSpriteXlu[0]));
            }
        } else {
            gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(dRenderSettingsCommon[flags]),
                               numberOfGfxCommands(dRenderSettingsCommon[0]));
        }
        gCurrentTextureHeader = NULL;
        gUsingTexture = TRUE;
    }
}

/**
 * Official Name: texLoadSprite
 */
#pragma GLOBAL_ASM("asm/nonmatchings/textures_sprites/func_8007C12C.s")

Sprite *func_8007C52C(s32 arg0) {
    if ((arg0 < 0) || (arg0 >= D_80126358)) {
        return NULL;
    }

    if (gSpriteCache[(arg0 << 1) + 1] == -1) {
        return NULL;
    }
    return (Sprite *) gSpriteCache[(arg0 << 1) + 1];
}

s32 get_texture_size_from_id(s32 id) {
    s32 textureRomOffset;
    TempTexHeader *new_var2;
    UNUSED s32 pad;
    u32 textureTable;
    s32 size;
    s32 new_var3;
    s32 textureTableType;
    s32 numOfTextures;
    TempTexHeader *new_var4;

    textureTable = ASSET_TEXTURES_2D;
    textureTableType = 0;
    if (id & 0x8000) {
        textureTable = ASSET_TEXTURES_3D;
        textureTableType = 1;
        id &= 0x7FFF;
    }
    if ((id >= gTextureAssetID[textureTableType]) || (id < 0)) {
        return 0;
    }
    textureRomOffset = gTextureAssetTable[textureTableType][id];
    new_var3 = textureRomOffset;
    size = gTextureAssetTable[textureTableType][id + 1] - new_var3;
    new_var2 = gTempTextureHeader;
    if (new_var2->header.isCompressed) {
        load_asset_to_address(textureTable, (u32) new_var2, textureRomOffset, 0x28);
        new_var4 = gTempTextureHeader;
        size = byteswap32((u8 *) (&new_var4->uncompressedSize));
    }
    new_var2 = gTempTextureHeader;
    numOfTextures = new_var2->header.numOfTextures;
    return (((numOfTextures >> 8) & 0xFFFF) * 0x60) + size;
}

UNUSED u8 func_8007C660(s32 arg0) {
    Sprite *temp_s1;
    s32 j;
    s32 i;
    s32 temp_v1;

    if (arg0 & 0x8000) {
        return 0;
    }
    if (D_80126370 == 0) {
        D_80126370 = (u8 *) mempool_alloc_safe(gTextureAssetID[TEX_TABLE_2D], COLOUR_TAG_MAGENTA);
        for (i = 0; i < gTextureAssetID[TEX_TABLE_2D]; i++) {
            D_80126370[i] = 0;
        }
        for (i = 0; i < gSpriteTableNum; i++) {
            temp_s1 = gCurrentSprite;
            load_asset_to_address(ASSET_SPRITES, (u32) temp_s1, gSpriteOffsetTable[i],
                                  gSpriteOffsetTable[i + 1] - gSpriteOffsetTable[i]);
            temp_v1 = temp_s1->unkC.val[temp_s1->numberOfFrames];
            for (j = 0; j < temp_v1; j++) {
                D_80126370[temp_s1->baseTextureId + j] = 1;
            }
        }
    }
    return D_80126370[arg0];
}

UNUSED s32 func_8007C860(s32 spriteIndex) {
    if ((spriteIndex < 0) || (spriteIndex >= gNumberOfLoadedTextures)) {
        return -1;
    }
    return gTextureCache[spriteIndex << 1];
}

UNUSED s32 func_8007C8A0(s32 spriteIndex) {
    if ((spriteIndex < 0) || (spriteIndex >= D_80126358)) {
        return -1;
    }
    return gSpriteCache[spriteIndex << 1];
}

s32 load_sprite_info(s32 spriteIndex, s32 *numOfInstancesOut, s32 *unkOut, s32 *numFramesOut, s32 *formatOut,
                     s32 *sizeOut) {
    TextureHeader *tex;
    s32 i;
    Sprite *new_var2;
    s32 j;
    s32 start;
    s32 size;
    s32 new_var;

    if ((spriteIndex < 0) || (spriteIndex >= gSpriteTableNum)) {
    textureCouldNotBeLoaded:
        *numOfInstancesOut = 0;
        *unkOut = 0;
        *numFramesOut = 0;
        return 0;
    }
    start = gSpriteOffsetTable[spriteIndex];
    size = gSpriteOffsetTable[spriteIndex + 1] - start;
    new_var2 = gCurrentSprite;
    new_var = size;
    load_asset_to_address(ASSET_SPRITES, (u32) new_var2, start, new_var);
    tex = load_texture(new_var2->unkC.val[0] + new_var2->baseTextureId);
    if (tex != NULL) {
        *formatOut = tex->format & 0xF;
        free_texture(tex);
        *sizeOut = 0;
        for (i = 0; i < new_var2->numberOfFrames; i++) {
            for (j = new_var2->unkC.val[i]; j < (s32) new_var2->unkC.val[i + 1]; j++) {
                *sizeOut += get_texture_size_from_id(new_var2->baseTextureId + j);
            }
        }
        *numFramesOut = new_var2->numberOfFrames;
        *numOfInstancesOut = new_var2->numberOfInstances;
        *unkOut = new_var2->unk6;
        return 1;
    }
    goto textureCouldNotBeLoaded;
}

#pragma GLOBAL_ASM("asm/nonmatchings/textures_sprites/func_8007CA68.s")

/* Official name: texFreeSprite */
void free_sprite(Sprite *sprite) {
    s32 i;
    s32 frame;

    if (sprite != NULL) {
        sprite->numberOfInstances--;
        if (sprite->numberOfInstances <= 0) {
            for (i = 0; i < D_80126358; i++) {
                if ((s32) sprite == gSpriteCache[(i << 1) + 1]) {
                    for (frame = 0; frame < sprite->numberOfFrames; frame++) {
                        free_texture(sprite->frames[frame]);
                    }
                    mempool_free(sprite);
                    gSpriteCache[(i << 1) + 0] = -1;
                    gSpriteCache[(i << 1) + 1] = -1; // ?
                    break;
                }
            }
        }
    }
}

#ifdef NON_MATCHING
void func_8007CDC0(Sprite *sprite1, Sprite *sprite2, s32 arg2) {
    UNUSED s32 pad[2];
    s32 sprUnk4;
    s32 sprUnk6;
    s32 y0;
    s32 x0;
    s32 x1;
    s32 y1;
    s32 xTemp;
    s32 yTemp;
    s32 left;
    s32 var_t5;
    s32 curVertIndex;
    s32 j;
    s32 texWidth;
    s32 texHeight;
    s32 i;
    Vertex *vertices;
    Vertex *curVerts;
    Triangle *triangles;
    u8 *temp_a3;
    Gfx *dlptr;
    TextureHeader *tex;

    temp_a3 = &sprite1->unkC.val[arg2];
    sprUnk4 = sprite1->numberOfInstances;
    sprUnk6 = sprite1->unk6;
    i = temp_a3[0];
    j = temp_a3[1];
    dlptr = D_80126364;
    vertices = D_80126360;
    triangles = D_80126368;
    if (i < j) {
        tex = sprite2->frames[i];
        sprite2->unk6 = ((tex->flags & 0xFFFF) & 0x3B);
    }
    curVertIndex = 0;
    var_t5 = 0;
    while (i < j) {
        tex = sprite2->frames[i];
        texWidth = tex->width;
        texHeight = tex->height;
        xTemp = (tex->unk3 - sprUnk4);
        x0 = xTemp;
        x1 = (xTemp + texWidth) - 1;
        yTemp = (sprUnk6 - tex->unk4);
        y0 = yTemp - 1;
        y1 = (yTemp - texHeight);
        curVerts = vertices;
        vertices[0].x = x0;
        vertices[0].y = y0;
        vertices[0].z = 0;
        vertices[0].r = 255;
        vertices[0].g = 255;
        vertices[0].b = 255;
        vertices[0].a = 255;
        vertices[1].x = x1;
        vertices[1].y = y0;
        vertices[1].z = 0;
        vertices[1].r = 255;
        vertices[1].g = 255;
        vertices[1].b = 255;
        vertices[1].a = 255;
        vertices[2].x = x1;
        vertices[2].y = y1;
        vertices[2].z = 0;
        vertices[2].r = 255;
        vertices[2].g = 255;
        vertices[2].b = 255;
        vertices[2].a = 255;
        vertices[3].x = x0;
        vertices[3].y = y1;
        vertices[3].z = 0;
        vertices[3].r = 255;
        vertices[3].g = 255;
        vertices[3].b = 255;
        vertices[3].a = 255;
        vertices += 4;
        gDkrDmaDisplayList(dlptr++, OS_K0_TO_PHYSICAL(tex->cmd), tex->numberOfCommands);
        if (var_t5 == 0) {
            left = j - i;
            if (left >= 6) {
                left = 5;
            }
            gSPVertexDKR(dlptr++, OS_K0_TO_PHYSICAL(curVerts), (left * 4), 1);
        }
        gSPPolygon(dlptr++, OS_K0_TO_PHYSICAL(triangles), 2, 1);
        triangles[0].flags = 0x40;
        triangles[0].vi0 = curVertIndex + 3;
        triangles[0].vi1 = curVertIndex + 2;
        triangles[0].vi2 = curVertIndex + 1;
        triangles[0].uv0.u = (texWidth - 1) << 5;
        triangles[0].uv0.v = (texHeight - 1) << 5;
        triangles[0].uv1.u = (texWidth - 1) << 5;
        triangles[0].uv1.v = 0;
        triangles[0].uv2.u = 1;
        triangles[0].uv2.v = 0;
        triangles[1].flags = 0x40;
        triangles[1].vi0 = curVertIndex + 4;
        triangles[1].vi1 = curVertIndex + 3;
        triangles[1].vi2 = curVertIndex + 1;
        triangles[1].uv0.u = 1;
        triangles[1].uv0.v = (texHeight - 1) << 5;
        triangles[1].uv1.u = (texWidth - 1) << 5;
        triangles[1].uv1.v = (texHeight - 1) << 5;
        triangles[1].uv2.u = 1;
        triangles[1].uv2.v = 0;
        triangles += 2;
        curVertIndex += 4;
        var_t5 += 1;
        i += 1;
        if (var_t5 >= 5) {
            var_t5 = 0;
            curVertIndex = 0;
        }
    }
    gDPPipeSync(dlptr++);
    gSPEndDisplayList(dlptr++);
    D_80126364 = dlptr;
    D_80126360 = vertices;
    D_80126368 = triangles;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/textures_sprites/func_8007CDC0.s")
#endif

#ifdef NON_EQUIVALENT
// HEAVILY WIP
// Alternative attempt: https://decomp.me/scratch/TbR8j
void build_tex_display_list(TextureHeader *tex, Gfx *dlist) {
    s32 texFlags;
    s32 cms;
    s32 cmt;
    s32 texFormat;
    s32 temp_v0_4;
    s32 i;
    s32 uClamp;
    s32 vClamp;
    s32 masks;
    s32 maskt;
    u8 height;
    u8 width;
    s32 var_v0;

    tex->cmd = (s32 *) dlist;
    texFormat = tex->format & 0xF;
    texFlags = (tex->format >> 4) & 0xF;
    height = tex->height;
    width = tex->width;
    var_v0 = 1;
    masks = 1;
    maskt = 1;
    uClamp = TRUE;
    vClamp = TRUE;
    for (i = 0; i < 7; i++) {
        if (var_v0 < width) {
            masks = i + 1;
        }
        if (var_v0 == width) {
            uClamp = FALSE;
        }
        if (var_v0 < height) {
            maskt = i + 1;
        }
        if (var_v0 == height) {
            vClamp = FALSE;
        }
        var_v0 <<= 1;
    }
    if (uClamp || (tex->flags & 0x40)) {
        cms = 2;
        masks = 0;
    } else {
        cms = 0;
    }
    if (vClamp || (tex->flags & 0x80)) {
        cmt = 2;
        maskt = 0;
    } else {
        cmt = 0;
    }
    if (!(tex->flags & 0x400)) {
        if (texFormat == 0) {
            gDPLoadTextureBlock(dlist++, OS_PHYSICAL_TO_K0(tex + 1), G_IM_FMT_RGBA, G_IM_SIZ_32b, width, height, 0, cms,
                                cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
            if ((texFlags == 0) || (texFlags == 2)) {
                tex->flags |= 4;
            }
        }
        if (texFormat == 1) {
            gDPLoadTextureBlock(dlist++, OS_PHYSICAL_TO_K0(tex + 1), G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height, 0, cms,
                                cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
            if ((texFlags == 0) || (texFlags == 2)) {
                tex->flags |= 4;
            }
        }
        if (texFormat == 7) {
            gDPLoadTextureBlock(dlist++, OS_PHYSICAL_TO_K0(tex + 1), G_IM_FMT_CI, G_IM_SIZ_16b, width, height, 0, cms,
                                cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
            temp_v0_4 = func_8007EF64(tex->ciPaletteOffset);
            gDPLoadTLUT_pal16(dlist++, 0, temp_v0_4);

            tex->flags |= 0x20;
            if ((texFlags == 0) || (texFlags == 2)) {
                tex->flags |= 4;
            }
        }
        if (texFormat == 4) {
            gDPLoadTextureBlock(dlist++, OS_PHYSICAL_TO_K0(tex + 1), G_IM_FMT_IA, G_IM_SIZ_16b, width, height, 0, cms,
                                cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
            tex->flags |= 4;
        }
        if (texFormat == 5) {
            gDPLoadTextureBlock(dlist++, OS_PHYSICAL_TO_K0(tex + 1), G_IM_FMT_IA, G_IM_SIZ_8b, width, height, 0, cms,
                                cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
            tex->flags |= 4;
        }
        if (texFormat == 6) {
            gDPLoadTextureBlock(dlist++, OS_PHYSICAL_TO_K0(tex + 1), G_IM_FMT_IA, G_IM_SIZ_4b, width, height, 0, cms,
                                cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
            tex->flags |= 4;
        }
        if (texFormat == 2) {
            gDPLoadTextureBlock(dlist++, OS_PHYSICAL_TO_K0(tex + 1), G_IM_FMT_I, G_IM_SIZ_8b, width, height, 0, cms,
                                cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
        }
        if (texFormat == 3) {
            gDPLoadTextureBlock(dlist++, OS_PHYSICAL_TO_K0(tex + 1), G_IM_FMT_I, G_IM_SIZ_4b, width, height, 0, cms,
                                cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
        }
        tex->numberOfCommands = ((s32) ((s32) dlist - (s32) tex->cmd) >> 3);
    } else {

        if (texFormat == 0) {
            gDPLoadTextureBlockS(dlist++, OS_PHYSICAL_TO_K0(tex + 1), G_IM_FMT_RGBA, G_IM_SIZ_32b, width, height, 0,
                                 cms, cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
            if ((texFlags == 0) || (texFlags == 2)) {
                tex->flags |= 4;
            }
        }
        if (texFormat == 1) {
            gDPLoadTextureBlockS(dlist++, OS_PHYSICAL_TO_K0(tex + 1), G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height, 0,
                                 cms, cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
            if ((texFlags == 0) || (texFlags == 2)) {
                tex->flags |= 4;
            }
        }
        if (texFormat == 7) {
            gDPLoadTextureBlockS(dlist++, OS_PHYSICAL_TO_K0(tex + 1), G_IM_FMT_CI, G_IM_SIZ_16b, width, height, 0, cms,
                                 cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
            temp_v0_4 = func_8007EF64(tex->ciPaletteOffset);
            gDPLoadTLUT_pal16(dlist++, 0, temp_v0_4);

            tex->flags |= 0x20;
            if ((texFlags == 0) || (texFlags == 2)) {
                tex->flags |= 4;
            }
        }
        if (texFormat == 4) {
            gDPLoadTextureBlockS(dlist++, OS_PHYSICAL_TO_K0(tex + 1), G_IM_FMT_IA, G_IM_SIZ_16b, width, height, 0, cms,
                                 cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
            tex->flags |= 4;
        }
        if (texFormat == 5) {
            gDPLoadTextureBlockS(dlist++, OS_PHYSICAL_TO_K0(tex + 1), G_IM_FMT_IA, G_IM_SIZ_8b, width, height, 0, cms,
                                 cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
            tex->flags |= 4;
        }
        if (texFormat == 6) {
            gDPLoadTextureBlockS(dlist++, OS_PHYSICAL_TO_K0(tex + 1), G_IM_FMT_IA, G_IM_SIZ_4b, width, height, 0, cms,
                                 cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
            tex->flags |= 4;
        }
        if (texFormat == 2) {
            gDPLoadTextureBlockS(dlist++, OS_PHYSICAL_TO_K0(tex + 1), G_IM_FMT_I, G_IM_SIZ_8b, width, height, 0, cms,
                                 cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
        }
        if (texFormat == 3) {
            gDPLoadTextureBlockS(dlist++, OS_PHYSICAL_TO_K0(tex + 1), G_IM_FMT_I, G_IM_SIZ_4b, width, height, 0, cms,
                                 cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
        }
        tex->numberOfCommands = ((s32) ((s32) dlist - (s32) tex->cmd) >> 3);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/textures_sprites/build_tex_display_list.s")
#endif

s32 func_8007EF64(s16 arg0) {
    return (s32) (arg0 + gCiPalettes);
}

/**
 * Official Name: texAnimateTexture
 */
void tex_animate_texture(TextureHeader *texture, u32 *triangleBatchInfoFlags, s32 *arg2, s32 updateRate) {
    s32 bit23Set;
    s32 bit25Set;
    s32 bit26Set;
    s32 breakVar;

    bit23Set = *triangleBatchInfoFlags & BATCH_FLAGS_UNK00800000;
    bit26Set = *triangleBatchInfoFlags & BATCH_FLAGS_UNK04000000;
    bit25Set = *triangleBatchInfoFlags & BATCH_FLAGS_UNK02000000;
    if (bit23Set) {
        if (!bit25Set) {
            if (get_random_number_from_range(0, 1000) > 985) {
                *triangleBatchInfoFlags &= ~BATCH_FLAGS_UNK04000000;
                *triangleBatchInfoFlags |= BATCH_FLAGS_UNK02000000;
            }
        } else if (!bit26Set) {
            *arg2 += texture->frameAdvanceDelay * updateRate;
            if (*arg2 >= texture->numOfTextures) {
                *arg2 = ((texture->numOfTextures * 2) - *arg2) - 1;
                if (*arg2 < 0) {
                    *arg2 = 0;
                    *triangleBatchInfoFlags &= ~(BATCH_FLAGS_UNK02000000 | BATCH_FLAGS_UNK04000000);
                } else {
                    *triangleBatchInfoFlags |= BATCH_FLAGS_UNK04000000;
                }
            }
        } else {
            *arg2 -= texture->frameAdvanceDelay * updateRate;
            if (*arg2 < 0) {
                *arg2 = 0;
                *triangleBatchInfoFlags &= ~(BATCH_FLAGS_UNK02000000 | BATCH_FLAGS_UNK04000000);
            }
        }
    } else if (bit25Set) {
        if (!bit26Set) {
            *arg2 += texture->frameAdvanceDelay * updateRate;
        } else {
            *arg2 -= texture->frameAdvanceDelay * updateRate;
        }
        do {
            breakVar = FALSE;
            if (*arg2 < 0) {
                *arg2 = -*arg2;
                *triangleBatchInfoFlags &= ~BATCH_FLAGS_UNK04000000;
                breakVar = TRUE;
            }
            if (*arg2 >= texture->numOfTextures) {
                *arg2 = ((texture->numOfTextures * 2) - *arg2) - 1;
                *triangleBatchInfoFlags |= BATCH_FLAGS_UNK04000000;
                breakVar = TRUE;
            }
        } while (breakVar);
    } else if (!bit26Set) {
        *arg2 += texture->frameAdvanceDelay * updateRate;
        while (*arg2 >= texture->numOfTextures) {
            *arg2 -= texture->numOfTextures;
        }
    } else {
        *arg2 -= texture->frameAdvanceDelay * updateRate;
        while (*arg2 < 0) {
            *arg2 += texture->numOfTextures;
        }
    }
}

void func_8007F1E8(LevelHeader_70 *arg0) {
    s32 i;

    arg0->unk4 = 0;
    arg0->unk8 = 0;
    arg0->unkC = 0;
    arg0->red = arg0->red2;
    arg0->green = arg0->green2;
    arg0->blue = arg0->blue2;
    arg0->alpha = arg0->alpha2;
    for (i = 0; i < arg0->unk0; i++) {
        arg0->unkC += arg0->unk18[i].unk0;
    }
}

/**
 * Official name: updateColourCycle
 */
void update_colour_cycle(LevelHeader_70 *arg0, s32 updateRate) {
    s32 temp;
    s32 curIndex;
    s32 nextIndex;
    u32 next_red;
    u32 cur_red;
    u32 next_green;
    u32 next_blue;
    u32 next_alpha;
    u32 cur_green;
    u32 cur_blue;
    u32 cur_alpha;
    LevelHeader_70 *cur;
    LevelHeader_70 *next;

    if (arg0->unk0 >= 2) {
        arg0->unk8 += updateRate;
        while (arg0->unk8 >= arg0->unkC) {
            if (!temp) {}
            arg0->unk8 -= arg0->unkC;
        }
        while (arg0->unk8 >= arg0->unk18[arg0->unk4].unk0) {
            arg0->unk8 -= arg0->unk18[arg0->unk4].unk0;
            arg0->unk4++;
            if (arg0->unk4 >= arg0->unk0) {
                arg0->unk4 = 0;
            }
        }

        curIndex = arg0->unk4;
        nextIndex = curIndex + 1;
        if (nextIndex >= arg0->unk0) {
            nextIndex = 0;
        }

        cur = (LevelHeader_70 *) (&((LevelHeader_70_18 *) arg0)[curIndex]);
        temp = (arg0->unk8 << 16) / (cur->unk18->unk0);
        cur_red = cur->red2;
        cur_green = cur->green2;
        cur_blue = cur->blue2;
        cur_alpha = cur->alpha2;

        next = (LevelHeader_70 *) (&((LevelHeader_70_18 *) arg0)[nextIndex]);
        next_red = next->red2;
        next_green = next->green2;
        next_blue = next->blue2;
        next_alpha = next->alpha2;

        next = arg0;
        arg0->red = (((next_red - cur_red) * temp) >> 16) + cur_red;
        arg0->green = (((next_green - cur_green) * temp) >> 16) + cur_green;
        arg0->blue = (((next_blue - cur_blue) * temp) >> 16) + cur_blue;
        arg0->alpha = (((next_alpha - cur_alpha) * temp) >> 16) + cur_alpha;
    }
}

/**
 * Official name: resetMixCycle
 */
void init_pulsating_light_data(PulsatingLightData *data) {
    s32 i;
    data->currentFrame = 0;
    data->time = 0;
    data->totalTime = 0;
    data->outColorValue = data->frames[0].value;
    for (i = 0; i < data->numberFrames; i++) {
        data->totalTime += data->frames[i].time;
    }
}

/**
 * Official Name: updateMixCycle
 */
void update_pulsating_light_data(PulsatingLightData *data, s32 timeDelta) {
    s32 thisFrameIndex, nextFrameIndex;

    if (data->numberFrames > 1) {
        data->time += timeDelta;
        while (data->time >= data->totalTime) {
            data->time -= data->totalTime;
        }
        while (data->time >= data->frames[data->currentFrame].time) {
            data->time -= data->frames[data->currentFrame].time;
            data->currentFrame++;
            if (data->currentFrame >= data->numberFrames) {
                data->currentFrame = 0;
            }
        }
        thisFrameIndex = data->currentFrame;
        nextFrameIndex = thisFrameIndex + 1;
        if (nextFrameIndex >= data->numberFrames) {
            nextFrameIndex = 0;
        }

        data->outColorValue = data->frames[thisFrameIndex].value +
                              ((data->frames[nextFrameIndex].value * data->time) / data->frames[thisFrameIndex].time);
    }
}

void func_8007F594(Gfx **dlist, u32 index, u32 primitiveColor, u32 environmentColor) {
    Gfx *gfxTemp;
    Gfx *tempDlist;
    u32 tempIndex;

    tempDlist = D_800DF3A8;
    tempIndex = index;

    if (tempIndex >= 2) {
        tempIndex = 2;
        tempDlist = D_800DF3D8;
    }

    gfxTemp = *dlist;
    gSPDisplayList(gfxTemp++, tempDlist);
    gDkrDmaDisplayList(gfxTemp++, OS_PHYSICAL_TO_K0(D_800DF410[tempIndex]), numberOfGfxCommands(D_800DF410[0]));
    gDPSetPrimColorRGBA(gfxTemp++, primitiveColor);
    gDPSetEnvColorRGBA(gfxTemp++, environmentColor);
    *dlist = gfxTemp;
}
