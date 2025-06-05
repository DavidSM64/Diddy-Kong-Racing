#include "textures_sprites.h"
#include "gzip.h"
#include "asset_loading.h"
#include "memory.h"
#include "math_util.h"
#include "tracks.h"
#include "game_ui.h"

#define MAX_NUM_TEXTURES 700
#define TEX_SPRITE_COUNT 50
#define TEX_PALLETE_COUNT 20
#define MAX_TEX_PALETTE_SIZE 640
#define TEXTURE_GFX_SIZE (12 * sizeof(Gfx))
#define PALETTE_GFX_SIZE (6 * sizeof(Gfx))

/************ .data ************/

u32 gTexColourTag = COLOUR_TAG_MAGENTA;
s32 gSpriteOpaque = TRUE;

// See "include/f3ddkr.h" for the defines

/**
 * Description of how these rendering modes work.
 *
 * First, the color combiner:
 * Color – the texture color is modulated by vertex shading. In the second cycle, the result is blended with the
 * environmental lighting color. Alpha – the texture alpha is multiplied by the vertex alpha (!) and then by the alpha
 * of PrimColor, which controls the overall transparency of the model.
 *
 * Now regarding the rendering modes: the base mode is XLU_SURF. However, in the first group, every mode has Z buffer
 * updates enabled. Presumably, this speeds up rendering of overlapping translucent primitives by allowing Z-based
 * rejection, but the visual result depends on draw order. For example: if you draw the far primitive first, then the
 * near one, both will be visible. But if drawn in the reverse order, only the near one will appear — the far one won't
 * render at all, even though the background behind the near primitive will remain visible.
 *
 * It’s also unclear why G_RM_NOOP is used in the first cycle instead of G_RM_PASS, but the effect should be the same:
 * the pixel color is passed unchanged to the second cycle.
 */
Gfx dRenderSettingsVtxAlpha[][2] = {
    // Semitransparent Vertex Alpha'd surface (Zsorted)
    DRAW_TABLE_GROUP(G_CC_MODULATERGBA, G_CC_MODULATEA_PRIM2, DKR_OMH_2CYC_BILERP, G_RM_NOOP, G_RM_XLU_SURF2 | Z_UPD,
                     G_RM_NOOP, G_RM_AA_XLU_SURF2 | Z_UPD, G_RM_NOOP, G_RM_ZB_XLU_SURF2 | Z_UPD, G_RM_NOOP,
                     G_RM_AA_ZB_XLU_SURF2 | Z_UPD),
    // Semitransparent Vertex Alpha'd surface (No Zsort)
    DRAW_TABLE_GROUP(G_CC_MODULATERGBA, G_CC_BLENDI_ENV_ALPHA_PRIM2, DKR_OMH_2CYC_BILERP, G_RM_NOOP, G_RM_XLU_SURF2,
                     G_RM_NOOP, G_RM_AA_XLU_SURF2, G_RM_NOOP, G_RM_ZB_XLU_SURF2, G_RM_NOOP, G_RM_AA_ZB_XLU_SURF2),
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
    DRAW_TABLE_GROUP(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_POINT, G_RM_XLU_SURF, G_RM_XLU_SURF2,
                     G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2,
                     G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2),
    // Semitransparent Sprite (Overwrite coverage) (Copy)
    DRAW_TABLE_GROUP(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_POINT, G_RM_XLU_SURF, G_RM_XLU_SURF2,
                     G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2,
                     G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2)
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
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, G_CC_BLENDI_ENV_ALPHA_PRIM2, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A,
                     G_RM_OPA_SURF2, G_RM_FOG_SHADE_A, G_RM_AA_OPA_SURF2, G_RM_FOG_SHADE_A, G_RM_ZB_OPA_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    // Semitransparent Surface with fog
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, G_CC_BLENDI_ENV_ALPHA_PRIM2, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A,
                     G_RM_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_AA_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    // Cutout Surface with primitive colour
    DRAW_TABLE_GROUP(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_BILERP, G_RM_XLU_SURF, G_RM_XLU_SURF2,
                     G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2,
                     G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2),
    // Cutout Surface with primitive colour (Copy)
    DRAW_TABLE_GROUP(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_BILERP, G_RM_XLU_SURF, G_RM_XLU_SURF2,
                     G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2,
                     G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2),
    // Cutout Surface with primitive colour and fog
    DRAW_TABLE_GROUP(G_CC_MODULATEIA_PRIM, G_CC_BLEND_ENV_ALPHA2, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A, G_RM_XLU_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2, G_RM_FOG_SHADE_A,
                     G_RM_AA_ZB_XLU_INTER2),
    // Cutout Surface with primitive colour and fog (Zsorted interpenetrating)
    DRAW_TABLE_GROUP(G_CC_MODULATEIA_PRIM, G_CC_BLEND_ENV_ALPHA2, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A, G_RM_XLU_SURF2,
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
    // Opaque Surface with indexed texture and fog (Cutout)
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
                     G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2,
                     G_RM_AA_ZB_XLU_LINE_MOD, G_RM_AA_ZB_XLU_LINE_MOD2),
    // Semitransparent Surface (Copy)
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_BILERP, G_RM_XLU_SURF, G_RM_XLU_SURF2,
                     G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2,
                     G_RM_AA_ZB_XLU_LINE_MOD, G_RM_AA_ZB_XLU_LINE_MOD2),
    // Semitransparent Surface with fog
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, G_CC_BLENDI_ENV_ALPHA_PRIM2, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A,
                     G_RM_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_AA_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2,
                     G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_LINE_MOD2),
    // Semitransparent Surface with fog (Copy)
    DRAW_TABLE_GROUP(G_CC_MODULATEIDECALA, G_CC_BLENDI_ENV_ALPHA_PRIM2, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A,
                     G_RM_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_AA_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2,
                     G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_LINE_MOD2),
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
    DRAW_TABLE_ENTRY(G_CC_MODULATEIDECALA, G_CC_BLENDI_ENV_ALPHA_PRIM2, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A,
                     G_RM_ZB_OPA_DECAL2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIDECALA, G_CC_BLENDI_ENV_ALPHA_PRIM2, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A,
                     G_RM_AA_ZB_OPA_DECAL2),
    // Semitransparent Decal with fog.
    DRAW_TABLE_ENTRY(G_CC_MODULATEIDECALA, G_CC_BLENDI_ENV_ALPHA_PRIM2, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A,
                     G_RM_ZB_XLU_DECAL2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIDECALA, G_CC_BLENDI_ENV_ALPHA_PRIM2, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A,
                     G_RM_AA_ZB_XLU_DECAL2),
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
    DRAW_TABLE_GROUP(G_CC_BLENDI_ENV_ALPHA, G_CC_MODULATEIA_PRIM2, DKR_OMH_2CYC_POINT, G_RM_NOOP, G_RM_XLU_SURF2,
                     G_RM_NOOP, G_RM_AA_XLU_SURF2, G_RM_NOOP, G_RM_ZB_XLU_SURF2, G_RM_NOOP, G_RM_AA_ZB_XLU_SURF2),
};

Gfx dRenderSettingsSolidColour[][2] = {
    // Opaque Surface
    DRAW_TABLE_GROUP(G_CC_BLENDI_ENV_ALPHA_A_PRIM, G_CC_BLENDI_ENV_ALPHA_A_PRIM, DKR_OMH_1CYC_POINT, G_RM_OPA_SURF,
                     G_RM_OPA_SURF2, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2, G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2,
                     G_RM_AA_ZB_OPA_INTER, G_RM_AA_ZB_OPA_INTER2),
    // Semitransparent Surface
    DRAW_TABLE_GROUP(G_CC_BLENDI_ENV_ALPHA_A_PRIM, G_CC_BLENDI_ENV_ALPHA_A_PRIM, DKR_OMH_1CYC_POINT, G_RM_XLU_SURF,
                     G_RM_XLU_SURF2, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2, G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2,
                     G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    // Opaque Surface with fog
    DRAW_TABLE_GROUP(G_CC_BLENDI_ENV_ALPHA_A_PRIM, G_CC_MODULATEIA_PRIM2, DKR_OMH_2CYC_POINT, G_RM_FOG_SHADE_A,
                     G_RM_OPA_SURF2, G_RM_FOG_SHADE_A, G_RM_AA_OPA_SURF2, G_RM_FOG_SHADE_A, G_RM_ZB_OPA_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    // Semitransparent Surface with fog
    DRAW_TABLE_GROUP(G_CC_BLENDI_ENV_ALPHA_A_PRIM, G_CC_MODULATEIA_PRIM2, DKR_OMH_2CYC_POINT, G_RM_FOG_SHADE_A,
                     G_RM_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_AA_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
};

// Some kind of texture on top of a solid colour
Gfx dRenderSettingsPrimOverlay[][2] = {
    // Opaque Surface
    DRAW_TABLE_ENTRY(G_CC_DECAL_A_PRIM, G_CC_DECAL_A_PRIM, DKR_OMH_1CYC_BILERP, G_RM_ZB_OPA_DECAL, G_RM_ZB_OPA_DECAL2),
    DRAW_TABLE_ENTRY(G_CC_DECAL_A_PRIM, G_CC_DECAL_A_PRIM, DKR_OMH_1CYC_BILERP, G_RM_AA_ZB_OPA_DECAL,
                     G_RM_AA_ZB_OPA_DECAL2),
    // Semitransparent Surface
    DRAW_TABLE_ENTRY(G_CC_DECAL_A_PRIM, G_CC_DECAL_A_PRIM, DKR_OMH_1CYC_BILERP, G_RM_ZB_XLU_DECAL, G_RM_ZB_XLU_DECAL2),
    DRAW_TABLE_ENTRY(G_CC_DECAL_A_PRIM, G_CC_DECAL_A_PRIM, DKR_OMH_1CYC_BILERP, G_RM_AA_ZB_XLU_DECAL,
                     G_RM_AA_ZB_XLU_DECAL2),
    // Opaque Surface with indexed texture
    DRAW_TABLE_ENTRY(G_CC_DECAL_A_PRIM, G_CC_DECAL_A_PRIM, DKR_OMH_1CYC_CI_BILERP, G_RM_ZB_OPA_DECAL,
                     G_RM_ZB_OPA_DECAL2),
    DRAW_TABLE_ENTRY(G_CC_DECAL_A_PRIM, G_CC_DECAL_A_PRIM, DKR_OMH_1CYC_CI_BILERP, G_RM_AA_ZB_OPA_DECAL,
                     G_RM_AA_ZB_OPA_DECAL2),
    // Semitransparent Surface with indexed texture
    DRAW_TABLE_ENTRY(G_CC_DECAL_A_PRIM, G_CC_DECAL_A_PRIM, DKR_OMH_1CYC_CI_BILERP, G_RM_ZB_XLU_DECAL,
                     G_RM_ZB_XLU_DECAL2),
    DRAW_TABLE_ENTRY(G_CC_DECAL_A_PRIM, G_CC_DECAL_A_PRIM, DKR_OMH_1CYC_CI_BILERP, G_RM_AA_ZB_XLU_DECAL,
                     G_RM_AA_ZB_XLU_DECAL2)
};

/**
 * Color combiner behavior:
 *
 * RGB: First, `PrimColor` and the texture color are blended using the vertex alpha as the blend factor
 *      (0 = fully shaded color, 1 = pure texture).
 *      The result is then blended with `EnvColor`, modulated by the vertex RGB color
 *      (all RGB components are expected to be equal, representing lighting intensity).
 *
 * Alpha: The texture's alpha is multiplied by the alpha value of `PrimColor`.
 *
 * This setup enables more advanced lighting by combining directional shadowing (e.g. from the sky)
 * with directional lighting (e.g. from a colored point light).
 *
 * This differs from simpler lighting models where illumination is uniform and non-directional.
 *
 * - `EnvColor` represents the light color.
 * - `PrimColor` represents the shadow (shaded) color.
 * - The vertex alpha is the **inverted shadow strength**:
 *     - alpha = 1 → fully lit (pure texture),
 *     - alpha = 0 → fully shaded (flat `PrimColor`).
 * - The vertex RGB intensity acts as the **lighting intensity**.
 */
Gfx dRenderSettingsDirectionalLighting[][2] = {
    // Opaque Surface
    DRAW_TABLE_GROUP(G_CC_BLEND_SHADEALPHA, G_CC_BLENDI_SHADE, DKR_OMH_2CYC_BILERP, G_RM_NOOP, G_RM_OPA_SURF2,
                     G_RM_NOOP, G_RM_AA_OPA_SURF2, G_RM_NOOP, G_RM_ZB_OPA_SURF2, G_RM_NOOP, G_RM_AA_ZB_OPA_SURF2),
    // Semitransparent Surface
    DRAW_TABLE_GROUP(G_CC_BLEND_SHADEALPHA, G_CC_BLENDI_SHADE, DKR_OMH_2CYC_BILERP, G_RM_NOOP, G_RM_XLU_SURF2,
                     G_RM_NOOP, G_RM_AA_XLU_SURF2, G_RM_NOOP, G_RM_ZB_XLU_SURF2, G_RM_NOOP, G_RM_AA_ZB_XLU_SURF2),
    // Opaque Surface with indexed texture
    DRAW_TABLE_GROUP(G_CC_BLEND_SHADEALPHA, G_CC_BLENDI_SHADE, DKR_OMH_2CYC_CI_BILERP, G_RM_NOOP, G_RM_OPA_SURF2,
                     G_RM_NOOP, G_RM_AA_OPA_SURF2, G_RM_NOOP, G_RM_ZB_OPA_SURF2, G_RM_NOOP, G_RM_AA_ZB_OPA_SURF2),
    // Semitransparent Surface with indexed texture
    DRAW_TABLE_GROUP(G_CC_BLEND_SHADEALPHA, G_CC_BLENDI_SHADE, DKR_OMH_2CYC_CI_BILERP, G_RM_NOOP, G_RM_XLU_SURF2,
                     G_RM_NOOP, G_RM_AA_XLU_SURF2, G_RM_NOOP, G_RM_AA_ZB_TEX_EDGE2, G_RM_NOOP, G_RM_AA_ZB_XLU_INTER2),
};

// Only opaque surface is actually used here.
Gfx dRenderSettingsBlinkingLights[][2] = {
    // Opaque Surface
    DRAW_TABLE_GROUP(G_CC_BLENDTEX_PRIM, G_CC_MODULATEIDECALA2, DKR_OMH_2CYC_BILERP, G_RM_NOOP, G_RM_OPA_SURF2,
                     G_RM_NOOP, G_RM_AA_OPA_SURF2, G_RM_NOOP, G_RM_ZB_OPA_SURF2, G_RM_NOOP, G_RM_AA_ZB_OPA_SURF2),
    // Semitransparent Surface
    DRAW_TABLE_GROUP(G_CC_BLENDTEX_PRIM, G_CC_MODULATEIDECALA2, DKR_OMH_2CYC_BILERP, G_RM_NOOP, G_RM_XLU_SURF2,
                     G_RM_NOOP, G_RM_AA_XLU_SURF2, G_RM_NOOP, G_RM_ZB_XLU_SURF2, G_RM_NOOP, G_RM_AA_ZB_XLU_SURF2),
    // Opaque Surface with fog
    DRAW_TABLE_GROUP(G_CC_BLENDTEX_PRIM, G_CC_MODULATEIDECALA2, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A, G_RM_OPA_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_OPA_SURF2, G_RM_FOG_SHADE_A, G_RM_ZB_OPA_SURF2, G_RM_FOG_SHADE_A,
                     G_RM_AA_ZB_OPA_SURF2),
    // Semitransparent Surface with fog
    DRAW_TABLE_GROUP(G_CC_BLENDTEX_PRIM, G_CC_MODULATEIDECALA2, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A, G_RM_XLU_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2, G_RM_FOG_SHADE_A,
                     G_RM_AA_ZB_XLU_SURF2),
    // Cutout Surface
    DRAW_TABLE_GROUP(G_CC_BLENDTEX_PRIM, G_CC_MODULATEIDECALA2, DKR_OMH_2CYC_BILERP, G_RM_NOOP, G_RM_XLU_SURF2,
                     G_RM_NOOP, G_RM_AA_XLU_SURF2, G_RM_NOOP, G_RM_AA_ZB_TEX_EDGE2, G_RM_NOOP,
                     G_RM_AA_ZB_XLU_LINE_MOD2),
    // Cutout Surface (Copy)
    DRAW_TABLE_GROUP(G_CC_BLENDTEX_PRIM, G_CC_MODULATEIDECALA2, DKR_OMH_2CYC_BILERP, G_RM_NOOP, G_RM_XLU_SURF2,
                     G_RM_NOOP, G_RM_AA_XLU_SURF2, G_RM_NOOP, G_RM_AA_ZB_TEX_EDGE2, G_RM_NOOP,
                     G_RM_AA_ZB_XLU_LINE_MOD2),
    // Cutout Surface with fog
    DRAW_TABLE_GROUP(G_CC_BLENDTEX_PRIM, G_CC_MODULATEIDECALA2, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A, G_RM_XLU_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2, G_RM_FOG_SHADE_A,
                     G_RM_AA_ZB_XLU_LINE_MOD2),
    // Cutout Surface with fog (Copy)
    DRAW_TABLE_GROUP(G_CC_BLENDTEX_PRIM, G_CC_MODULATEIDECALA2, DKR_OMH_2CYC_BILERP, G_RM_FOG_SHADE_A, G_RM_XLU_SURF2,
                     G_RM_FOG_SHADE_A, G_RM_AA_XLU_SURF2, G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2, G_RM_FOG_SHADE_A,
                     G_RM_AA_ZB_XLU_LINE_MOD2),
};

Gfx dBasicRenderSettingsZBOff[] = {
    gsDPPipeSync(),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPClearGeometryMode(G_ZBUFFER | G_FOG),
    gsSPEndDisplayList(),
};

Gfx dBasicRenderSettingsZBOn[] = {
    gsDPPipeSync(),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPClearGeometryMode(G_FOG),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPEndDisplayList(),
};

Gfx dBasicRenderModes[][2] = {
    DRAW_TABLE_ENTRY(G_CC_BLENDPE_A_PRIM, G_CC_BLENDPE_A_PRIM, DKR_OMH_1CYC_BILERP_NOPERSP, G_RM_ZB_CLD_SURF,
                     G_RM_ZB_CLD_SURF2),
    DRAW_TABLE_ENTRY(G_CC_BLENDPE, G_CC_BLENDPE, DKR_OMH_1CYC_BILERP, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2),
    DRAW_TABLE_ENTRY(G_CC_BLENDPE_A_PRIM, G_CC_PASS2, DKR_OMH_2CYC_BILERP, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2)
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
s32 gTextureTableSize[2];
s32 gCiPalettesSize;
s32 gFirstTexIsLoaded;
s32 *gSpriteOffsetTable;

s32 *gSpriteCache;

Sprite *gCurrentSprite;
s32 gSpriteTableSize;
s32 gSpriteCacheCount;
s32 D_8012635C; // Set but never used
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
s16 gUseDirectionalLighting;

/******************************/

/**
 * Load the texture table from ROM and allocate space for all the texture asset management.
 */
void tex_init_textures(void) {
    s32 i;

    gTextureCache = mempool_alloc_safe(8 * MAX_NUM_TEXTURES, COLOUR_TAG_MAGENTA);
    gCiPalettes = mempool_alloc_safe(MAX_TEX_PALETTE_SIZE, COLOUR_TAG_MAGENTA);
    gNumberOfLoadedTextures = 0;
    gCiPalettesSize = 0;
    gTextureAssetTable[TEX_TABLE_2D] = (s32 *) load_asset_section_from_rom(ASSET_TEXTURES_2D_TABLE);
    gTextureAssetTable[TEX_TABLE_3D] = (s32 *) load_asset_section_from_rom(ASSET_TEXTURES_3D_TABLE);

    for (i = 0; gTextureAssetTable[TEX_TABLE_2D][i] != -1; i++) {}
    gTextureTableSize[TEX_TABLE_2D] = --i;

    for (i = 0; gTextureAssetTable[TEX_TABLE_3D][i] != -1; i++) {}
    gTextureTableSize[TEX_TABLE_3D] = --i;

    gSpriteCache = mempool_alloc_safe(sizeof(Sprite) * TEX_SPRITE_COUNT, COLOUR_TAG_MAGENTA);
    gCurrentSprite = mempool_alloc_safe(sizeof(Sprite) * 32, COLOUR_TAG_MAGENTA);
    gSpriteCacheCount = 0;
    gSpriteOffsetTable = (s32 *) load_asset_section_from_rom(ASSET_SPRITES_TABLE);
    gSpriteTableSize = 0;
    while (gSpriteOffsetTable[gSpriteTableSize] != -1) {
        gSpriteTableSize++;
    }
    gSpriteTableSize--;

    gTempTextureHeader = mempool_alloc_safe(sizeof(TempTexHeader), COLOUR_TAG_MAGENTA);
    gFirstTexIsLoaded = FALSE;
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
UNUSED s32 tex_get_table_2D(void) {
    return gTextureTableSize[TEX_TABLE_2D];
}

/**
 * Return the texture asset ID table for 3D textures.
 * Goes unused.
 */
UNUSED s32 tex_get_table_3D(void) {
    return gTextureTableSize[TEX_TABLE_3D];
}

/**
 * Return the size of the sprite asset table.
 */
UNUSED s32 sprite_table_size(void) {
    return gSpriteTableSize;
}

/**
 * Loads a texture into memory and initializes display lists for texture loading.
 * First checks if the texture is already in the cache.
 * Also loads color palettes if the texture uses them (though this game doesn't use such textures).
 *
 * Official Name: texLoadTexture
 */
TextureHeader *load_texture(s32 id) {
    TextureHeader *tex;
    TextureHeader *texTemp;
    u32 compressedStart;
    s32 assetIndex;
    s32 assetOffset;
    s32 assetSize;
    s32 paletteOffset;
    s32 assetSection;
    s32 slotIndex;
    s32 tableType;
    s32 i;
    u16 numberOfTextures;
    s32 uncompressedSize;

    // 'id' is a 16-bit value; the highest bit determines whether it's a 2D or 3D texture
    id &= 0xFFFF;
    assetIndex = id;
    assetSection = ASSET_TEXTURES_2D;
    tableType = TEX_TABLE_2D;
    if (id & ASSET_MASK_TEX3D) {
        tableType = TEX_TABLE_3D;
        assetIndex = id & 0x7FFF;
        assetSection = ASSET_TEXTURES_3D;
    }

    // If the index is out of bounds, fall back to texture 0. Returning NULL would be better.
    if (assetIndex >= gTextureTableSize[tableType] || assetIndex < 0) {
        id = 0;
    }

    // Check if texture is already loaded; if so, increment the reference count and return it.
    for (i = 0; i < gNumberOfLoadedTextures; i++) {
        if (id == gTextureCache[ASSETCACHE_ID(i)]) {
            tex = (TextureHeader *) gTextureCache[ASSETCACHE_PTR(i)];
            tex->numberOfInstances++;
            return tex;
        }
    }
    assetOffset = gTextureAssetTable[tableType][assetIndex];
    assetSize = gTextureAssetTable[tableType][assetIndex + 1] - assetOffset;
    load_asset_to_address(assetSection, (u32) gTempTextureHeader, assetOffset, sizeof(TempTexHeader));
    numberOfTextures = gTempTextureHeader->header.numOfTextures >> 8;

    // Allocate memory for the texture and its display lists.
    // If compressed, decompress it.
    if (!gTempTextureHeader->header.isCompressed) {
        tex = (TextureHeader *) mempool_alloc(numberOfTextures * TEXTURE_GFX_SIZE + assetSize, gTexColourTag);
        if (tex == NULL) {
            return NULL;
        }
        load_asset_to_address(assetSection, (u32) tex, assetOffset, assetSize);
    } else {
        // Allocate enough memory for the decompressed texture
        uncompressedSize = byteswap32((u8 *) &gTempTextureHeader->uncompressedSize) + sizeof(TextureHeader);
        tex = (TextureHeader *) mempool_alloc(numberOfTextures * TEXTURE_GFX_SIZE + uncompressedSize, gTexColourTag);
        if (tex == NULL) {
            return NULL;
        }

        // Load the compressed texture at the end of the allocated block,
        // so it can be decompressed into the entire block
        compressedStart = (((s32) tex + uncompressedSize) - assetSize);
        compressedStart = (s32) compressedStart - (s32) compressedStart % 16;
        load_asset_to_address(assetSection, compressedStart, assetOffset, assetSize);
        gzip_inflate((u8 *) (compressedStart + sizeof(TextureHeader)), (u8 *) tex);
        assetSize = uncompressedSize - sizeof(TextureHeader);
    }

    // Find an available slot in the texture cache and store the newly loaded texture
    slotIndex = -1;
    for (i = 0; i < gNumberOfLoadedTextures; i++) {
        if (gTextureCache[ASSETCACHE_ID(i)] == -1) {
            slotIndex = i;
        }
    }
    if (slotIndex == -1) {
        slotIndex = gNumberOfLoadedTextures;
        gNumberOfLoadedTextures++;
    }
    gTextureCache[ASSETCACHE_ID(slotIndex)] = id;
    gTextureCache[ASSETCACHE_PTR(slotIndex)] = (s32) tex;

    // Load palettes if needed. If the texture has multiple frames, the palette is shared, so we only load it once.
    paletteOffset = -1;
    if (TEX_FORMAT(tex->format) == TEX_FORMAT_CI4) {
        if (!gFirstTexIsLoaded) {
            load_asset_to_address(ASSET_EMPTY_14, (u32) &gCiPalettes[gCiPalettesSize], tex->ciPaletteOffset, 32);
            tex->ciPaletteOffset = gCiPalettesSize;
            gCiPalettesSize += 32; // (32 bytes / 2 bytes per color) = 16 colors.
        }
        paletteOffset = gCiPalettesSize - 32;
    }
    if (TEX_FORMAT(tex->format) == TEX_FORMAT_CI8) {
        if (!gFirstTexIsLoaded) {
            // Normally, TEX_FORMAT_CI8 requires 256 colors (512 bytes),
            // but maybe only 64 colors (128 bytes) are actually used in this game
            load_asset_to_address(ASSET_EMPTY_14, (u32) &gCiPalettes[gCiPalettesSize], tex->ciPaletteOffset, 128);
            tex->ciPaletteOffset = gCiPalettesSize;
            gCiPalettesSize += 128; // (128 bytes / 2 bytes per color) = 64 colors.
        }
        paletteOffset = gCiPalettesSize - 128;
    }
    gFirstTexIsLoaded = FALSE;

    // Initialize display lists for each frame of the texture
    assetOffset = (s32) align16((u8 *) ((s32) tex + assetSize));
    texTemp = tex;
    for (i = 0; i < numberOfTextures; i++) {
        material_init(texTemp, (Gfx *) assetOffset);
        if (paletteOffset >= 0) {
            texTemp->ciPaletteOffset = paletteOffset;
            assetOffset += PALETTE_GFX_SIZE; // I'm guessing it takes 6 f3d commands to load the palette
                                             //!@bug — no memory was allocated for this!
        }
        assetOffset += TEXTURE_GFX_SIZE; // I'm guessing it takes 12 f3d commands to load the texture
        texTemp = (TextureHeader *) ((s32) texTemp + texTemp->textureSize);
    }
    if (gCiPalettesSize >= MAX_TEX_PALETTE_SIZE) {
        return NULL;
    }
    if (gNumberOfLoadedTextures > MAX_NUM_TEXTURES) {
        return NULL;
    }
    return tex;
}

/**
 * This function attempts to free the texture from memory.
 * It checks if the refcount is zero, then finds the cache entry, before clearing it.
 * Official Name: texFreeTexture
 */
void tex_free(TextureHeader *tex) {
    s32 i;

    if (tex != NULL) {
        if ((--tex->numberOfInstances) <= 0) {
            for (i = 0; i < gNumberOfLoadedTextures; i++) {
                if ((s32) tex == gTextureCache[ASSETCACHE_PTR(i)]) {
                    mempool_free(tex);

                    gTextureCache[ASSETCACHE_ID(i)] = -1;
                    gTextureCache[ASSETCACHE_PTR(i)] = -1;
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

/**
 * Returns the texture stored in the specified cache slot, if any.
 */
UNUSED TextureHeader *get_cached_texture_by_slot(s32 slotId) {
    if (slotId < 0 || slotId >= gNumberOfLoadedTextures) {
        return NULL;
    }
    if (gTextureCache[ASSETCACHE_PTR(slotId)] == -1) {
        return NULL;
    }
    return (TextureHeader *) gTextureCache[ASSETCACHE_PTR(slotId)];
}

/**
 * Resets all render settings to the default state.
 * The next draw call will be forced to apply all settings instead of skipping unecessary steps.
 * Official Name: texDPInit
 */
void rendermode_reset(Gfx **dList) {
    gCurrentTextureHeader = NULL;
    gCurrentRenderFlags = RENDER_NONE;
    gUsingTexture = FALSE;
    gForceFlags = TRUE;
    gBlockedRenderFlags = RENDER_NONE;
    gUseDirectionalLighting = FALSE;
    gDPPipeSync((*dList)++);
    gSPSetGeometryMode((*dList)++, G_SHADING_SMOOTH | G_SHADE | G_ZBUFFER);
}

/**
 * Enables usage of combiners utilising the individual primitive colours.
 */
void directional_lighting_on(void) {
    gUseDirectionalLighting = TRUE;
    gForceFlags = TRUE;
}

/**
 * Disables usage of combiners utilising the individual primitive colours.
 */
void directional_lighting_off(void) {
    gUseDirectionalLighting = FALSE;
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
void material_set_no_tex_offset(Gfx **dList, TextureHeader *texhead, u32 flags) {
    material_set(dList, texhead, flags, 0);
}

/**
 * Load a texture from memory into texture memory.
 * Also set render mode, combine mode and othermodes based on flags.
 * Also tracks which modes are active, to prevent setting them again if they're already active.
 * A number can be attached that adds a texture address offset. An example of this being used is
 * the numbered doors in the hub, to change what number is written on it.
 */
void material_set(Gfx **dList, TextureHeader *texhead, s32 flags, s32 texOffset) {
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
            gDkrDmaDisplayList((*dList)++, OS_K0_TO_PHYSICAL(texhead->cmd), texhead->numberOfCommands);
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

    flags = (gUseDirectionalLighting)
                ? (flags & (RENDER_DECAL | RENDER_COLOUR_INDEX | RENDER_ANTI_ALIASING | RENDER_Z_COMPARE |
                            RENDER_SEMI_TRANSPARENT))
                : (flags & (RENDER_VTX_ALPHA | RENDER_DECAL | RENDER_Z_UPDATE | RENDER_COLOUR_INDEX | RENDER_CUTOUT |
                            RENDER_FOG_ACTIVE | RENDER_SEMI_TRANSPARENT | RENDER_Z_COMPARE | RENDER_ANTI_ALIASING));
    flags &= ~gBlockedRenderFlags;
    flags = (flags & RENDER_VTX_ALPHA) ? flags & ~RENDER_FOG_ACTIVE : flags & ~RENDER_Z_UPDATE;

    if (flags != gCurrentRenderFlags || forceFlags) {
        if (doPipeSync) {
            gDPPipeSync((*dList)++);
        }

        if ((flags & RENDER_VTX_ALPHA) != (gCurrentRenderFlags & RENDER_VTX_ALPHA) || gForceFlags) {
            if (flags & RENDER_VTX_ALPHA || gUseDirectionalLighting) {
                gSPClearGeometryMode((*dList)++, G_FOG);
            } else {
                gSPSetGeometryMode((*dList)++, G_FOG);
            }
        }

        if ((flags & RENDER_Z_COMPARE) != (gCurrentRenderFlags & RENDER_Z_COMPARE) || gForceFlags) {
            if (flags & RENDER_Z_COMPARE) {
                gSPSetGeometryMode((*dList)++, G_ZBUFFER);
            } else {
                gSPClearGeometryMode((*dList)++, G_ZBUFFER);
            }
        }

        gForceFlags = FALSE;
        gCurrentRenderFlags = flags;
        if (!gUsingTexture) {
            if (flags & RENDER_VTX_ALPHA) {
                gDkrDmaDisplayList(
                    (*dList)++,
                    OS_K0_TO_PHYSICAL(
                        dRenderSettingsSolidColourVtxAlpha[flags & (RENDER_ANTI_ALIASING | RENDER_Z_COMPARE)]),
                    numberOfGfxCommands(dRenderSettingsSolidColourVtxAlpha[0]));
                return;
            }
            gDkrDmaDisplayList(
                (*dList)++,
                OS_K0_TO_PHYSICAL(dRenderSettingsSolidColour[flags & (RENDER_FOG_ACTIVE | RENDER_SEMI_TRANSPARENT |
                                                                      RENDER_Z_COMPARE | RENDER_ANTI_ALIASING)]),
                numberOfGfxCommands(dRenderSettingsSolidColour[0]));
            return;
        }

        if (gUseDirectionalLighting) {
            if ((flags & RENDER_DECAL) && (flags & RENDER_Z_COMPARE)) {
                dlIndex = 0;
                if (flags & RENDER_ANTI_ALIASING) {
                    dlIndex |= 1; // Anti Aliasing
                }
                if (flags & RENDER_SEMI_TRANSPARENT) {
                    dlIndex |= 2; // Semi-transparent
                }
                if (flags & RENDER_COLOUR_INDEX) {
                    dlIndex |= 4; // Colour Index
                }
                // In this mode, the decal is rendered without any shading or lighting whatsoever.
                // It's unclear what this mode has in common with the complex lighting mode set below.
                gDkrDmaDisplayList((*dList)++, OS_K0_TO_PHYSICAL(dRenderSettingsPrimOverlay[dlIndex]),
                                   numberOfGfxCommands(dRenderSettingsPrimOverlay[0]));
                return;
            }
            if (flags & RENDER_COLOUR_INDEX) {
                // set flag 8 if color indexed
                flags = (flags ^ RENDER_COLOUR_INDEX) | 8;
            }
            gDkrDmaDisplayList((*dList)++, OS_K0_TO_PHYSICAL(dRenderSettingsDirectionalLighting[flags]),
                               numberOfGfxCommands(dRenderSettingsDirectionalLighting[0]));
            return;
        }

        if ((flags & RENDER_DECAL) && (flags & RENDER_Z_COMPARE)) {
            dlIndex = 0;
            if (flags & RENDER_ANTI_ALIASING) {
                dlIndex |= 1; // Anti Aliasing
            }
            if (flags & RENDER_SEMI_TRANSPARENT) {
                dlIndex |= 2; // Semi-transparent
            }
            if (flags & RENDER_FOG_ACTIVE) {
                dlIndex |= 4; // Fog
            }
            if (flags & RENDER_COLOUR_INDEX) {
                dlIndex |= 8; // Colour Index
            }
            gDkrDmaDisplayList((*dList)++, OS_K0_TO_PHYSICAL(dRenderSettingsDecal[dlIndex]),
                               numberOfGfxCommands(dRenderSettingsDecal[0]));
            return;
        }

        if (flags & RENDER_CUTOUT) {
            dlIndex = flags & (RENDER_ANTI_ALIASING | RENDER_Z_COMPARE | RENDER_SEMI_TRANSPARENT);
            if (flags & RENDER_FOG_ACTIVE) {
                dlIndex |= 8; // Fog
            }
            gDkrDmaDisplayList((*dList)++, OS_K0_TO_PHYSICAL(dRenderSettingsCutout[dlIndex]),
                               numberOfGfxCommands(dRenderSettingsCutout[0]));
            return;
        }

        flags &= ~RENDER_DECAL;
        if (flags & RENDER_VTX_ALPHA) {
            dlIndex = flags & (RENDER_ANTI_ALIASING | RENDER_Z_COMPARE);
            if (flags & RENDER_Z_UPDATE) {
                dlIndex |= 4; // Z write
            } else {
                gSPSetGeometryMode((*dList)++, G_ZBUFFER);
                gCurrentRenderFlags |= RENDER_Z_COMPARE;
            }
            gDkrDmaDisplayList((*dList)++, OS_K0_TO_PHYSICAL(dRenderSettingsVtxAlpha[dlIndex]),
                               numberOfGfxCommands(dRenderSettingsVtxAlpha[0]));
            return;
        }

        gDkrDmaDisplayList((*dList)++, OS_K0_TO_PHYSICAL(dRenderSettingsCommon[flags]),
                           numberOfGfxCommands(dRenderSettingsCommon[0]));
        return;
    }
}

/**
 * Loads the texture and render settings for the blinking lights seen in Spaceport Alpha.
 */
void material_set_blinking_lights(Gfx **dList, TextureHeader *texture_list, u32 flags, s32 texture_index) {
    u16 *mblock;
    u16 *tblock;
    if (texture_index != 0 && texture_index < (texture_list->numOfTextures * 256)) {
        texture_list = (TextureHeader *) ((s32) texture_list + ((texture_index >> 16) * texture_list->textureSize));
    }
    mblock = (u16 *) (texture_list + 1);
    tblock = mblock + 0x400;
    if (texture_list->width == 64) {
        gDPLoadMultiBlock((*dList)++, OS_K0_TO_PHYSICAL(mblock), 256, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 16, 0, 0, 0,
                          6, 4, 0, 0);
        gDPLoadTextureBlock((*dList)++, OS_K0_TO_PHYSICAL(tblock), G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 16, 0, 0, 0, 6, 4,
                            0, 0);
    } else {
        gDPLoadMultiBlock((*dList)++, OS_K0_TO_PHYSICAL(mblock), 256, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, 0, 0,
                          5, 5, 0, 0);
        gDPLoadTextureBlock((*dList)++, OS_K0_TO_PHYSICAL(tblock), G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, 0, 0, 5, 5,
                            0, 0);
    }

    gDPPipeSync((*dList)++);
    gCurrentTextureHeader = NULL;
    flags &= (RENDER_ANTI_ALIASING | RENDER_Z_COMPARE | RENDER_SEMI_TRANSPARENT | RENDER_FOG_ACTIVE | RENDER_CUTOUT);
    gSPSetGeometryMode((*dList)++, G_FOG);

    if (flags & RENDER_Z_COMPARE) {
        gSPSetGeometryMode((*dList)++, G_ZBUFFER);
    } else {
        gSPClearGeometryMode((*dList)++, G_ZBUFFER);
    }
    gForceFlags = TRUE;
    gCurrentRenderFlags = RENDER_NONE;
    gDkrDmaDisplayList((*dList)++, OS_PHYSICAL_TO_K0(dRenderSettingsBlinkingLights[flags]),
                       numberOfGfxCommands(dRenderSettingsBlinkingLights[0]));
}

/**
 * Set whether to use an opaque render mode for sprites.
 */
void sprite_opaque(s32 setting) {
    gSpriteOpaque = setting;
    gForceFlags = TRUE;
}

/**
 * Load a texture from memory into texture memory.
 * Much simpler than the regular material function, only having modes for opaque and transparent.
 */
void material_load_simple(Gfx **dList, s32 flags) {
    if (flags != gCurrentRenderFlags || gForceFlags) {
        gDPPipeSync((*dList)++);
        if ((gCurrentRenderFlags & RENDER_VTX_ALPHA) || gForceFlags) {
            gSPSetGeometryMode((*dList)++, G_FOG);
        }
        flags &= ~RENDER_VTX_ALPHA;
        flags &= ~gBlockedRenderFlags;
        if ((flags & RENDER_Z_COMPARE) != (gCurrentRenderFlags & RENDER_Z_COMPARE) || gForceFlags) {
            if (flags & RENDER_Z_COMPARE) {
                gSPSetGeometryMode((*dList)++, G_ZBUFFER);
            } else {
                gSPClearGeometryMode((*dList)++, G_ZBUFFER);
            }
        }
        gForceFlags = FALSE;
        gCurrentRenderFlags = flags;
        flags &= ~RENDER_DECAL;
        if (gSpriteOpaque == FALSE) {
            if (gCurrentRenderFlags & RENDER_PRESERVE_COVERAGE) {
                gDkrDmaDisplayList((*dList)++, OS_K0_TO_PHYSICAL(dRenderSettingsSpriteCld[(flags >> 1) & 1]),
                                   numberOfGfxCommands(dRenderSettingsSpriteCld[0]));
            } else {
                // fake ^ 0 required for some reason
                gDkrDmaDisplayList((*dList)++, OS_K0_TO_PHYSICAL(dRenderSettingsSpriteXlu[(flags - RENDER_CUTOUT) ^ 0]),
                                   numberOfGfxCommands(dRenderSettingsSpriteXlu[0]));
            }
        } else {
            gDkrDmaDisplayList((*dList)++, OS_K0_TO_PHYSICAL(dRenderSettingsCommon[flags]),
                               numberOfGfxCommands(dRenderSettingsCommon[0]));
        }
        gCurrentTextureHeader = NULL;
        gUsingTexture = TRUE;
    }
}

Sprite *tex_load_sprite(s32 spriteID, s32 arg1) {
    Sprite *refSprite;
    Sprite *newSprite;
    s32 cacheNum;
    Sprite *sprite;
    TextureHeader *tex;
    s32 i;
    s32 size;
    s8 allocFailed;
    s8 cacheFull;
    s16 frameCount;
    s32 allocSize;

    D_8012635C = arg1;
    if (spriteID < 0 || spriteID >= gSpriteTableSize) {
        return NULL;
    }

    for (i = 0, cacheFull = 0; i < gSpriteCacheCount; i++) {
        if (spriteID == gSpriteCache[ASSETCACHE_ID(i)]) {
            refSprite = (Sprite *) gSpriteCache[ASSETCACHE_PTR(i)];
            refSprite->numberOfInstances++;
            return refSprite;
        }
    }

    cacheNum = -1;
    for (i = 0; i < gSpriteCacheCount; i++) {
        // @fake
        if (newSprite) {}
        if (gSpriteCache[ASSETCACHE_ID(i)] == -1) {
            cacheNum = i;
        }
    }

    if (cacheNum == -1) {
        cacheFull = TRUE;
        cacheNum = gSpriteCacheCount;
        gSpriteCacheCount++;
    }

    size = gSpriteOffsetTable[spriteID];
    sprite = gCurrentSprite;
    load_asset_to_address(12, (u32) sprite, size, gSpriteOffsetTable[spriteID + 1] - size);

    frameCount = sprite->unkC.val[sprite->numberOfFrames];
    size = frameCount * 4;
    allocSize = size * sizeof(Vertex);
    allocSize += size << 3;
    allocSize += sprite->numberOfFrames * sizeof(Gfx);
    allocSize += frameCount << 4 << 1;
    allocSize += size;
    allocSize += (s32) align16((u8 *) 0x10);
    allocSize += (s32) align16((u8 *) (sprite->numberOfFrames * 4));
    newSprite = (Sprite *) mempool_alloc(allocSize, COLOUR_TAG_MAGENTA);
    if (newSprite == NULL) {
        if (cacheFull) {
            gSpriteCacheCount--;
        }

        return NULL;
    }

    D_80126368 = (Triangle *) ((s32) newSprite + (s32) align16((u8 *) sizeof(Sprite)) +
                               (s32) align16((u8 *) (sprite->numberOfFrames * 4)));
    D_80126364 = (Gfx *) (&((u8 *) D_80126368)[frameCount << 5]); // `<< 5` is `sizeof(Triangle) * 2`
    D_80126360 = (Vertex *) ((Gfx *) (((s32) & ((u8 *) D_80126364)[frameCount << 5]) + (sprite->numberOfFrames << 3)));
    newSprite->gfx[0] = (Gfx *) &((u8 *) D_80126360)[frameCount * sizeof(Vertex) * 4];

    allocFailed = FALSE;
    for (i = 0; i < frameCount; i++) {
        gTexColourTag = COLOUR_TAG_LIME;
        tex = load_texture(sprite->baseTextureId + i);
        newSprite->frames[i] = tex;
        if (newSprite->frames[i] == NULL) {
            allocFailed = TRUE;
        }

        gTexColourTag = COLOUR_TAG_MAGENTA;
        gFirstTexIsLoaded = TRUE;
    }

    gFirstTexIsLoaded = FALSE;
    if (allocFailed) {
        for (i = 0; i < frameCount; i++) {
            tex = (TextureHeader *) newSprite->frames[i];
            if (tex != NULL) {
                tex_free(tex);
            }
        }
        if (cacheFull) {
            gSpriteCacheCount--;
        }
        mempool_free(newSprite);
        return NULL;
    }

    newSprite->numberOfFrames = frameCount;
    newSprite->baseTextureId = sprite->numberOfFrames;
    for (i = 0; i < sprite->numberOfFrames; i++) {
        newSprite->unkC.ptr[i] = (u8 *) D_80126364;
        func_8007CDC0(sprite, newSprite, i);
    }

    if (gSpriteCacheCount >= 100) {
        return NULL;
    }

    gSpriteCache[ASSETCACHE_ID(cacheNum)] = spriteID;
    gSpriteCache[ASSETCACHE_PTR(cacheNum)] = (s32) newSprite;
    newSprite->numberOfInstances = 1;
    return newSprite;
}

/**
 * Gets the sprite cache index from the argument.
 * Returns NULL if the entry is invalid.
 */
UNUSED s32 sprite_cache_index(s32 cacheID) {
    if (cacheID < 0 || cacheID >= gSpriteCacheCount) {
        return NULL;
    }

    if (gSpriteCache[ASSETCACHE_PTR(cacheID)] == -1) {
        return NULL;
    }
    return gSpriteCache[ASSETCACHE_PTR(cacheID)];
}

s32 tex_asset_size(s32 id) {
    s32 textureRomOffset;
    TempTexHeader *new_var2;
    UNUSED s32 pad;
    u32 textureTable;
    s32 size;
    s32 new_var3;
    s32 textureTableType;
    u16 numOfTextures;
    TempTexHeader *new_var4;

    textureTable = ASSET_TEXTURES_2D;
    textureTableType = TEX_TABLE_2D;
    if (id & ASSET_MASK_TEX3D) {
        textureTable = ASSET_TEXTURES_3D;
        textureTableType = TEX_TABLE_3D;
        id &= (ASSET_MASK_TEX3D - 1);
    }
    if (id >= gTextureTableSize[textureTableType] || id < 0) {
        return 0;
    }
    textureRomOffset = gTextureAssetTable[textureTableType][id];
    new_var3 = textureRomOffset;
    size = gTextureAssetTable[textureTableType][id + 1] - new_var3;
    new_var2 = gTempTextureHeader;
    if (new_var2->header.isCompressed) {
        load_asset_to_address(textureTable, (u32) new_var2, textureRomOffset, sizeof(TempTexHeader));
        new_var4 = gTempTextureHeader;
        size = byteswap32((u8 *) (&new_var4->uncompressedSize));
    }
    new_var2 = gTempTextureHeader;
    numOfTextures = new_var2->header.numOfTextures;
    return (((numOfTextures >> 8) & 0xFFFF) * 0x60) + size;
}

UNUSED u8 func_8007C660(s32 texID) {
    Sprite *temp_s1;
    s32 j;
    s32 i;
    s32 temp_v1;

    if (texID & ASSET_MASK_TEX3D) {
        return 0;
    }
    if (D_80126370 == 0) {
        D_80126370 = (u8 *) mempool_alloc_safe(gTextureTableSize[TEX_TABLE_2D], COLOUR_TAG_MAGENTA);
        for (i = 0; i < gTextureTableSize[TEX_TABLE_2D]; i++) {
            D_80126370[i] = 0;
        }
        for (i = 0; i < gSpriteTableSize; i++) {
            temp_s1 = gCurrentSprite;
            load_asset_to_address(ASSET_SPRITES, (u32) temp_s1, gSpriteOffsetTable[i],
                                  gSpriteOffsetTable[i + 1] - gSpriteOffsetTable[i]);
            temp_v1 = temp_s1->unkC.val[temp_s1->numberOfFrames];
            for (j = 0; j < temp_v1; j++) {
                D_80126370[temp_s1->baseTextureId + j] = 1;
            }
        }
    }
    return D_80126370[texID];
}

/**
 * Returns the texture cache asset ID from the cache table entry given by the argument.
 * Returns -1 if the argument is out of bounds
 */
UNUSED s32 tex_cache_asset_id(s32 cacheID) {
    if (cacheID < 0 || cacheID >= gNumberOfLoadedTextures) {
        return -1;
    }
    return gTextureCache[ASSETCACHE_ID(cacheID)];
}

/**
 * Returns the sprite cache asset ID from the cache table entry given by the argument.
 * Returns -1 if the argument is out of bounds
 */
UNUSED s32 sprite_cache_asset_id(s32 cacheID) {
    if (cacheID < 0 || cacheID >= gSpriteCacheCount) {
        return -1;
    }
    return gSpriteCache[ASSETCACHE_ID(cacheID)];
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

    if ((spriteIndex < 0) || (spriteIndex >= gSpriteTableSize)) {
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
        *formatOut = TEX_FORMAT(tex->format);
        tex_free(tex);
        *sizeOut = 0;
        for (i = 0; i < new_var2->numberOfFrames; i++) {
            for (j = new_var2->unkC.val[i]; j < (s32) new_var2->unkC.val[i + 1]; j++) {
                *sizeOut += tex_asset_size(new_var2->baseTextureId + j);
            }
        }
        *numFramesOut = new_var2->numberOfFrames;
        *numOfInstancesOut = new_var2->numberOfInstances;
        *unkOut = new_var2->drawFlags;
        return 1;
    }
    goto textureCouldNotBeLoaded;
}

void func_8007CA68(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3, s32 *arg4) {
    Sprite *sprite;
    TextureHeader *tex;
    s32 temp_a0;
    s32 temp_v1;
    s32 var_s1;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    s32 temp_a1;
    s32 temp_a2;

    if ((arg0 < 0) || (arg0 >= gSpriteTableSize)) {
        *arg2 = 0;
        *arg3 = 0;
        return;
    }

    temp_a2 = gSpriteOffsetTable[arg0];

    // Must be on the same line. (maybe a macro?)
    // clang-format off
    sprite = gCurrentSprite; \
    load_asset_to_address(12, (u32)sprite, temp_a2, gSpriteOffsetTable[arg0 + 1] - temp_a2);
    // clang-format on

    if (sprite->numberOfFrames < arg1) {
    failedExit:
        *arg2 = 0;
        *arg3 = 0;
        *arg4 = 0;
        return;
    }
    tex = load_texture(sprite->unkC.val[arg1] + sprite->baseTextureId);
    if (tex == NULL) {
        goto failedExit;
    }
    *arg4 = tex_asset_size(sprite->unkC.val[arg1] + sprite->baseTextureId);
    var_s3 = tex->unk3 - sprite->numberOfInstances;
    var_s4 = sprite->drawFlags - tex->unk4;
    temp_a1 = tex->width;
    temp_a2 = tex->height;
    var_s5 = var_s3 + temp_a1;
    var_s6 = var_s4 - temp_a2;
    tex_free(tex);

    for (var_s1 = sprite->unkC.val[arg1] + 1; var_s1 < sprite->unkC.val[arg1 + 1]; var_s1++) {
        tex = load_texture(sprite->baseTextureId + var_s1);
        if (tex == NULL) {
            goto failedExit;
        }
        *arg4 += tex_asset_size(sprite->baseTextureId + var_s1);
        temp_v1 = tex->unk3 - sprite->numberOfInstances;
        temp_a0 = sprite->drawFlags - tex->unk4;
        temp_a1 = tex->width;
        temp_a2 = tex->height;
        if (temp_v1 < var_s3) {
            var_s3 = temp_v1;
        }
        if (var_s5 < temp_v1 + temp_a1) {
            var_s5 = temp_v1 + temp_a1;
        }
        if (temp_a0 - temp_a2 < var_s6) {
            var_s6 = temp_a0 - temp_a2;
        }
        if (var_s4 < temp_a0) {
            var_s4 = temp_a0;
        }
        tex_free(tex);
    }
    *arg2 = var_s5 - var_s3;
    *arg3 = var_s4 - var_s6;
}

/**
 * This function attempts to free the sprite from memory.
 * It checks if the refcount is zero, then finds the cache entry, before clearing it.
 * Official Name: texFreeSprite
 */
void sprite_free(Sprite *sprite) {
    s32 i;
    s32 frame;

    if (sprite != NULL) {
        sprite->numberOfInstances--;
        if (sprite->numberOfInstances <= 0) {
            for (i = 0; i < gSpriteCacheCount; i++) {
                if (sprite == (Sprite *) gSpriteCache[ASSETCACHE_PTR(i)]) {
                    for (frame = 0; frame < sprite->numberOfFrames; frame++) {
                        tex_free(sprite->frames[frame]);
                    }
                    mempool_free(sprite);
                    gSpriteCache[ASSETCACHE_ID(i)] = -1;
                    gSpriteCache[ASSETCACHE_PTR(i)] = -1;
                    break;
                }
            }
        }
    }
}

void func_8007CDC0(Sprite *sprite1, Sprite *sprite2, s32 arg2) {
    UNUSED s32 pad[2];
    s32 spriteCount;
    s32 spriteDrawFlags;
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
    Gfx *dlptr;
    TextureHeader *tex;

    spriteCount = sprite1->numberOfInstances;
    spriteDrawFlags = sprite1->drawFlags;
    i = sprite1->unkC.val[arg2];
    j = sprite1->unkC.val[arg2 + 1];
    dlptr = D_80126364;
    vertices = D_80126360;
    triangles = D_80126368;
    if (i < j) {
        tex = sprite2->frames[i];
        sprite2->drawFlags = ((tex->flags & 0xFFFF) & 0x3B);
    }
    curVertIndex = 0;
    var_t5 = 0;
    while (i < j) {
        curVerts = vertices;
        tex = sprite2->frames[i];
        texWidth = tex->width;
        texHeight = tex->height;
        xTemp = tex->unk3 - spriteCount;
        yTemp = spriteDrawFlags - tex->unk4;
        vertices->x = xTemp;
        vertices->y = yTemp - 1;
        vertices->z = 0;
        vertices->r = 255;
        vertices->g = 255;
        vertices->b = 255;
        vertices->a = 255;
        vertices++;
        vertices->x = xTemp + texWidth - 1;
        vertices->y = yTemp - 1;
        vertices->z = 0;
        vertices->r = 255;
        vertices->g = 255;
        vertices->b = 255;
        vertices->a = 255;
        vertices++;
        vertices->x = xTemp + texWidth - 1;
        vertices->y = yTemp - texHeight;
        vertices->z = 0;
        vertices->r = 255;
        vertices->g = 255;
        vertices->b = 255;
        vertices->a = 255;
        vertices++;
        vertices->x = xTemp;
        vertices->y = yTemp - texHeight;
        vertices->z = 0;
        vertices->r = 255;
        vertices->g = 255;
        vertices->b = 255;
        vertices->a = 255;
        vertices++;
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

/**
 * Build the display list for the texture.
 * Takes the texture properties from the header and then constructs the F3D gfx commands.
 * Certain texture types will also have draw mode flag overrides.
 */
void material_init(TextureHeader *tex, Gfx *_dList) {
    s32 texFormat;
    s32 texRenderMode;
    s32 width;
    s32 height;
    s32 cms;
    s32 cmt;
    s32 masks;
    s32 maskt;
    s32 i;
    s32 uClamp;
    s32 vClamp;
    s32 size;
    s32 texLut;
    Gfx *dList;

    tex->cmd = dList = _dList;
    texFormat = TEX_FORMAT(tex->format);
    texRenderMode = TEX_RENDERMODE(tex->format);
    height = tex->height;
    width = tex->width;
    size = 1;
    masks = 1;
    maskt = 1;
    uClamp = TRUE;
    vClamp = TRUE;

    for (i = 0; i < 7; i++) {
        if (size < width) {
            masks = i + 1;
        } else if ((size == width) != 0) {
            uClamp = FALSE;
        }
        if (size < height) {
            maskt = i + 1;
        } else if ((size == height) != 0) {
            vClamp = FALSE;
        }
        size *= 2;
    }

    if (uClamp || tex->flags & RENDER_CLAMP_X) {
        cms = G_TX_CLAMP;
        masks = G_TX_NOMASK;
    } else {
        cms = G_TX_WRAP;
    }

    if (vClamp || tex->flags & RENDER_CLAMP_Y) {
        cmt = G_TX_CLAMP;
        maskt = G_TX_NOMASK;
    } else {
        cmt = G_TX_WRAP;
    }

    if (!(tex->flags & RENDER_LINE_SWAP)) {
        // If it is not swapped, then use the regular loadTexBlock macros.
        if (texFormat == TEX_FORMAT_RGBA32) {
            gDPLoadTextureBlock(dList++, OS_K0_TO_PHYSICAL(tex + 1), G_IM_FMT_RGBA, G_IM_SIZ_32b, width, height, 0, cms,
                                cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
            if (texRenderMode == TRANSPARENT || texRenderMode == TRANSPARENT_2) {
                tex->flags |= RENDER_SEMI_TRANSPARENT;
            }
        }
        if (texFormat == TEX_FORMAT_RGBA16) {
            gDPLoadTextureBlock(dList++, OS_K0_TO_PHYSICAL(tex + 1), G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height, 0, cms,
                                cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
            if (texRenderMode == TRANSPARENT || texRenderMode == TRANSPARENT_2) {
                tex->flags |= RENDER_SEMI_TRANSPARENT;
            }
        }
        if (texFormat == TEX_FORMAT_CI4) {
            texLut = tex_palette_id(tex->ciPaletteOffset);
            gDPLoadTextureBlock_4b(dList++, OS_K0_TO_PHYSICAL(tex + 1), G_IM_FMT_CI, width, height, 0, cms, cmt, masks,
                                   maskt, G_TX_NOLOD, G_TX_NOLOD);
            gDPLoadTLUT_pal16(dList++, 0, texLut);

            tex->flags |= RENDER_COLOUR_INDEX;
            if (texRenderMode == TRANSPARENT || texRenderMode == TRANSPARENT_2) {
                tex->flags |= RENDER_SEMI_TRANSPARENT;
            }
        }
        if (texFormat == TEX_FORMAT_IA16) {
            gDPLoadTextureBlock(dList++, OS_K0_TO_PHYSICAL(tex + 1), G_IM_FMT_IA, G_IM_SIZ_16b, width, height, 0, cms,
                                cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
            tex->flags |= RENDER_SEMI_TRANSPARENT;
        }
        if (texFormat == TEX_FORMAT_IA8) {
            gDPLoadTextureBlock(dList++, OS_K0_TO_PHYSICAL(tex + 1), G_IM_FMT_IA, G_IM_SIZ_8b, width, height, 0, cms,
                                cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
            tex->flags |= RENDER_SEMI_TRANSPARENT;
        }
        if (texFormat == TEX_FORMAT_IA4) {
            gDPLoadTextureBlock_4b(dList++, OS_K0_TO_PHYSICAL(tex + 1), G_IM_FMT_IA, width, height, 0, cms, cmt, masks,
                                   maskt, G_TX_NOLOD, G_TX_NOLOD);
            tex->flags |= RENDER_SEMI_TRANSPARENT;
        }
        if (texFormat == TEX_FORMAT_I8) {
            gDPLoadTextureBlock(dList++, OS_K0_TO_PHYSICAL(tex + 1), G_IM_FMT_I, G_IM_SIZ_8b, width, height, 0, cms,
                                cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
        }
        if (texFormat == TEX_FORMAT_I4) {
            gDPLoadTextureBlock_4b(dList++, OS_K0_TO_PHYSICAL(tex + 1), G_IM_FMT_I, width, height, 0, cms, cmt, masks,
                                   maskt, G_TX_NOLOD, G_TX_NOLOD);
        }
        tex->numberOfCommands = dList - tex->cmd;
    } else {
        // Textures are swapped, so we need to use the LoadTextureBlockS macros.
        if (texFormat == TEX_FORMAT_RGBA32) {
            gDPLoadTextureBlockS(dList++, OS_K0_TO_PHYSICAL(tex + 1), G_IM_FMT_RGBA, G_IM_SIZ_32b, width, height, 0,
                                 cms, cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
            if (texRenderMode == TRANSPARENT || texRenderMode == TRANSPARENT_2) {
                tex->flags |= RENDER_SEMI_TRANSPARENT;
            }
        }
        if (texFormat == TEX_FORMAT_RGBA16) {
            gDPLoadTextureBlockS(dList++, OS_K0_TO_PHYSICAL(tex + 1), G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height, 0,
                                 cms, cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
            if (texRenderMode == TRANSPARENT || texRenderMode == TRANSPARENT_2) {
                tex->flags |= RENDER_SEMI_TRANSPARENT;
            }
        }
        if (texFormat == TEX_FORMAT_CI4) {
            texLut = tex_palette_id(tex->ciPaletteOffset);
            gDPLoadTextureBlock_4bS(dList++, OS_K0_TO_PHYSICAL(tex + 1), G_IM_FMT_CI, width, height, 0, cms, cmt, masks,
                                    maskt, G_TX_NOLOD, G_TX_NOLOD);
            gDPLoadTLUT_pal16(dList++, 0, texLut);

            tex->flags |= RENDER_COLOUR_INDEX;
            if (texRenderMode == TRANSPARENT || texRenderMode == TRANSPARENT_2) {
                tex->flags |= RENDER_SEMI_TRANSPARENT;
            }
        }
        if (texFormat == TEX_FORMAT_IA16) {
            gDPLoadTextureBlockS(dList++, OS_K0_TO_PHYSICAL(tex + 1), G_IM_FMT_IA, G_IM_SIZ_16b, width, height, 0, cms,
                                 cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
            tex->flags |= RENDER_SEMI_TRANSPARENT;
        }
        if (texFormat == TEX_FORMAT_IA8) {
            gDPLoadTextureBlockS(dList++, OS_K0_TO_PHYSICAL(tex + 1), G_IM_FMT_IA, G_IM_SIZ_8b, width, height, 0, cms,
                                 cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
            tex->flags |= RENDER_SEMI_TRANSPARENT;
        }
        if (texFormat == TEX_FORMAT_IA4) {
            gDPLoadTextureBlock_4bS(dList++, OS_K0_TO_PHYSICAL(tex + 1), G_IM_FMT_IA, width, height, 0, cms, cmt, masks,
                                    maskt, G_TX_NOLOD, G_TX_NOLOD);
            tex->flags |= RENDER_SEMI_TRANSPARENT;
        }
        if (texFormat == TEX_FORMAT_I8) {
            gDPLoadTextureBlockS(dList++, OS_K0_TO_PHYSICAL(tex + 1), G_IM_FMT_I, G_IM_SIZ_8b, width, height, 0, cms,
                                 cmt, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
        }
        if (texFormat == TEX_FORMAT_I4) {
            gDPLoadTextureBlock_4bS(dList++, OS_K0_TO_PHYSICAL(tex + 1), G_IM_FMT_I, width, height, 0, cms, cmt, masks,
                                    maskt, G_TX_NOLOD, G_TX_NOLOD);
        }
        tex->numberOfCommands = dList - tex->cmd;
    }
}

/**
 * Returns the palette offset from the heap.
 */
s32 tex_palette_id(s16 paletteID) {
    return (s32) (paletteID + gCiPalettes);
}

/**
 * Official Name: texAnimateTexture
 */
void tex_animate_texture(TextureHeader *texture, u32 *triangleBatchInfoFlags, s32 *arg2, s32 updateRate) {
    s32 bit23Set;
    s32 bit25Set;
    s32 bit26Set;
    s32 breakVar;

    bit23Set = *triangleBatchInfoFlags & RENDER_UNK_0800000;
    bit26Set = *triangleBatchInfoFlags & RENDER_UNK_4000000;
    bit25Set = *triangleBatchInfoFlags & RENDER_UNK_2000000;
    if (bit23Set) {
        if (!bit25Set) {
            if (rand_range(0, 1000) > 985) {
                *triangleBatchInfoFlags &= ~RENDER_UNK_4000000;
                *triangleBatchInfoFlags |= RENDER_UNK_2000000;
            }
        } else if (!bit26Set) {
            *arg2 += texture->frameAdvanceDelay * updateRate;
            if (*arg2 >= texture->numOfTextures) {
                *arg2 = ((texture->numOfTextures * 2) - *arg2) - 1;
                if (*arg2 < 0) {
                    *arg2 = 0;
                    *triangleBatchInfoFlags &= ~(RENDER_UNK_2000000 | RENDER_UNK_4000000);
                } else {
                    *triangleBatchInfoFlags |= RENDER_UNK_4000000;
                }
            }
        } else {
            *arg2 -= texture->frameAdvanceDelay * updateRate;
            if (*arg2 < 0) {
                *arg2 = 0;
                *triangleBatchInfoFlags &= ~(RENDER_UNK_2000000 | RENDER_UNK_4000000);
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
                *triangleBatchInfoFlags &= ~RENDER_UNK_4000000;
                breakVar = TRUE;
            }
            if (*arg2 >= texture->numOfTextures) {
                *arg2 = ((texture->numOfTextures * 2) - *arg2) - 1;
                *triangleBatchInfoFlags |= RENDER_UNK_4000000;
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
    arg0->rgba.r = arg0->rgba2.r;
    arg0->rgba.g = arg0->rgba2.g;
    arg0->rgba.b = arg0->rgba2.b;
    arg0->rgba.a = arg0->rgba2.a;
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
        cur_red = cur->rgba2.r;
        cur_green = cur->rgba2.g;
        cur_blue = cur->rgba2.b;
        cur_alpha = cur->rgba2.a;

        next = (LevelHeader_70 *) (&((LevelHeader_70_18 *) arg0)[nextIndex]);
        next_red = next->rgba2.r;
        next_green = next->rgba2.g;
        next_blue = next->rgba2.b;
        next_alpha = next->rgba2.a;

        next = arg0;
        arg0->rgba.r = (((next_red - cur_red) * temp) >> 16) + cur_red;
        arg0->rgba.g = (((next_green - cur_green) * temp) >> 16) + cur_green;
        arg0->rgba.b = (((next_blue - cur_blue) * temp) >> 16) + cur_blue;
        arg0->rgba.a = (((next_alpha - cur_alpha) * temp) >> 16) + cur_alpha;
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

/**
 * Initialises some draw modes for rendering semitransparent geometry.
 * Sets everything needed to render, but relies on the texture being set manually.
 */
void gfx_init_basic_xlu(Gfx **dList, u32 index, u32 primitiveColor, u32 environmentColor) {
    Gfx *gfxTemp;
    Gfx *tempDlist;
    u32 tempIndex;

    tempDlist = dBasicRenderSettingsZBOff;
    tempIndex = index;

    if (tempIndex >= DRAW_BASIC_2CYCLE) {
        tempIndex = DRAW_BASIC_2CYCLE;
        tempDlist = dBasicRenderSettingsZBOn;
    }

    gfxTemp = *dList;
    gSPDisplayList(gfxTemp++, tempDlist);
    gDkrDmaDisplayList(gfxTemp++, OS_K0_TO_PHYSICAL(dBasicRenderModes[tempIndex]),
                       numberOfGfxCommands(dBasicRenderModes[0]));
    gDPSetPrimColorRGBA(gfxTemp++, primitiveColor);
    gDPSetEnvColorRGBA(gfxTemp++, environmentColor);
    *dList = gfxTemp;
}
