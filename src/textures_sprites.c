/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8007AC70 */

#include "textures_sprites.h"
#include "gzip.h"
#include "asset_loading.h"
#include "memory.h"
#include "math_util.h"
#include "unknown_0255E0.h"

/************ .data ************/

u32 gTexColourTag = COLOUR_TAG_MAGENTA;
s32 D_800DE7C4 = 1;

// See "include/f3ddkr.h" for the defines

Gfx D_800DE7C8[][2] = {
    {
        gsDPSetCombineMode(G_CC_MODULATEIA, DKR_CC_UNK0),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | DKR_RM_UNKNOWN0 | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA, DKR_CC_UNK0),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | DKR_RM_UNKNOWN0 | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA, DKR_CC_UNK0),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | DKR_RM_UNKNOWN0 | G_RM_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA, DKR_CC_UNK0),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | DKR_RM_UNKNOWN0 | G_RM_AA_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | DKR_RM_UNKNOWN1 | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | DKR_RM_UNKNOWN1 | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | DKR_RM_UNKNOWN1 | G_RM_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | DKR_RM_UNKNOWN1 | G_RM_AA_ZB_XLU_SURF2),
    },
};

Gfx D_800DE848[][2] = {
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT, DKR_OML_COMMON | G_RM_CLD_SURF | G_RM_CLD_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT, DKR_OML_COMMON | G_RM_ZB_CLD_SURF | G_RM_ZB_CLD_SURF2),
    },
};

// Should probably be merged with D_800DE848
Gfx D_800DE868[][2] = {
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT, DKR_OML_COMMON | DKR_RM_UNKNOWN2_1 | DKR_RM_UNKNOWN2_2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT, DKR_OML_COMMON | DKR_RM_UNKNOWN3_1 | DKR_RM_UNKNOWN3_2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT, DKR_OML_COMMON | G_RM_AA_ZB_XLU_INTER | G_RM_AA_ZB_XLU_INTER2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT, DKR_OML_COMMON | DKR_RM_UNKNOWN2_1 | DKR_RM_UNKNOWN2_2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT, DKR_OML_COMMON | DKR_RM_UNKNOWN3_1 | DKR_RM_UNKNOWN3_2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT, DKR_OML_COMMON | G_RM_AA_ZB_XLU_INTER | G_RM_AA_ZB_XLU_INTER2),
    },
};

Gfx D_800DE8E8[][2] = {
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_OPA_SURF | G_RM_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_AA_OPA_SURF | G_RM_AA_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_ZB_OPA_SURF | G_RM_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_OPA_SURF | G_RM_AA_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_AA_XLU_SURF | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_ZB_XLU_SURF | G_RM_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_XLU_SURF | G_RM_AA_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_AA_XLU_SURF | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_TEX_EDGE | G_RM_AA_ZB_TEX_EDGE2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_XLU_INTER | G_RM_AA_ZB_XLU_INTER2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_AA_XLU_SURF | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_TEX_EDGE | G_RM_AA_ZB_TEX_EDGE2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_XLU_INTER | G_RM_AA_ZB_XLU_INTER2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, DKR_CC_UNK2),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, DKR_CC_UNK2),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, DKR_CC_UNK2),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_TEX_EDGE2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, DKR_CC_UNK2),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_XLU_INTER2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, DKR_CC_UNK2),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, DKR_CC_UNK2),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, DKR_CC_UNK2),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_XLU_INTER2 | Z_UPD),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, DKR_CC_UNK2),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_XLU_INTER2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_OPA_SURF | G_RM_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_AA_OPA_SURF | G_RM_AA_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_ZB_OPA_SURF | G_RM_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_OPA_SURF | G_RM_AA_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_AA_XLU_SURF | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_ZB_XLU_SURF | G_RM_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_XLU_SURF | G_RM_AA_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_OPA_SURF | G_RM_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_AA_OPA_SURF | G_RM_AA_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_ZB_OPA_SURF | G_RM_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_OPA_SURF | G_RM_AA_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_AA_XLU_SURF | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_TEX_EDGE | G_RM_AA_ZB_TEX_EDGE2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_XLU_INTER | G_RM_AA_ZB_XLU_INTER2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_TEX_EDGE2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_XLU_INTER2),
    },
};

Gfx D_800DECE8[][2] = {
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_AA_XLU_SURF | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_TEX_EDGE | G_RM_AA_ZB_TEX_EDGE2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | DKR_RM_UNKNOWN4_1 | DKR_RM_UNKNOWN4_2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_AA_XLU_SURF | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_TEX_EDGE | G_RM_AA_ZB_TEX_EDGE2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | DKR_RM_UNKNOWN4_1 | DKR_RM_UNKNOWN4_2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_TEX_EDGE2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | DKR_RM_UNKNOWN4_2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_TEX_EDGE2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | DKR_RM_UNKNOWN4_2),
    },
};

Gfx D_800DEDE8[][2] = {
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_ZB_OPA_DECAL | G_RM_ZB_OPA_DECAL2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_OPA_DECAL | G_RM_AA_ZB_OPA_DECAL2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_ZB_XLU_DECAL | G_RM_ZB_XLU_DECAL2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_XLU_DECAL | G_RM_AA_ZB_XLU_DECAL2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_ZB_OPA_DECAL2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_DECAL2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_ZB_XLU_DECAL2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, DKR_CC_UNK1),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_XLU_DECAL2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_ZB_OPA_DECAL | G_RM_ZB_OPA_DECAL2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_OPA_DECAL | G_RM_AA_ZB_OPA_DECAL2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_ZB_XLU_DECAL | G_RM_ZB_XLU_DECAL2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_XLU_DECAL | G_RM_AA_ZB_XLU_DECAL2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_ZB_OPA_DECAL2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_DECAL2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_ZB_XLU_DECAL2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_XLU_DECAL2),
    },
};

Gfx D_800DEEE8[][2] = {
    {
        gsDPSetCombineMode(DKR_CC_UNK3, G_CC_MODULATEIA_PRIM2),
        gsDPSetOtherMode(DKR_OMH_2CYC_POINT, DKR_OML_COMMON | G_RM_NOOP | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK3, G_CC_MODULATEIA_PRIM2),
        gsDPSetOtherMode(DKR_OMH_2CYC_POINT, DKR_OML_COMMON | G_RM_NOOP | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK3, G_CC_MODULATEIA_PRIM2),
        gsDPSetOtherMode(DKR_OMH_2CYC_POINT, DKR_OML_COMMON | G_RM_NOOP | G_RM_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK3, G_CC_MODULATEIA_PRIM2),
        gsDPSetOtherMode(DKR_OMH_2CYC_POINT, DKR_OML_COMMON | G_RM_NOOP | G_RM_AA_ZB_XLU_SURF2),
    },
};

Gfx D_800DEF28[][2] = {
    {
        gsDPSetCombineMode(DKR_CC_UNK4, DKR_CC_UNK4),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT, DKR_OML_COMMON | G_RM_OPA_SURF | G_RM_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK4, DKR_CC_UNK4),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT, DKR_OML_COMMON | G_RM_AA_OPA_SURF | G_RM_AA_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK4, DKR_CC_UNK4),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT, DKR_OML_COMMON | G_RM_ZB_OPA_SURF | G_RM_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK4, DKR_CC_UNK4),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT, DKR_OML_COMMON | G_RM_AA_ZB_OPA_INTER | G_RM_AA_ZB_OPA_INTER2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK4, DKR_CC_UNK4),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK4, DKR_CC_UNK4),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT, DKR_OML_COMMON | G_RM_AA_XLU_SURF | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK4, DKR_CC_UNK4),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT, DKR_OML_COMMON | G_RM_ZB_XLU_SURF | G_RM_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK4, DKR_CC_UNK4),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT, DKR_OML_COMMON | G_RM_AA_ZB_XLU_SURF | G_RM_AA_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK4, G_CC_MODULATEIA_PRIM2),
        gsDPSetOtherMode(DKR_OMH_2CYC_POINT, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK4, G_CC_MODULATEIA_PRIM2),
        gsDPSetOtherMode(DKR_OMH_2CYC_POINT, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK4, G_CC_MODULATEIA_PRIM2),
        gsDPSetOtherMode(DKR_OMH_2CYC_POINT, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK4, G_CC_MODULATEIA_PRIM2),
        gsDPSetOtherMode(DKR_OMH_2CYC_POINT, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK4, G_CC_MODULATEIA_PRIM2),
        gsDPSetOtherMode(DKR_OMH_2CYC_POINT, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK4, G_CC_MODULATEIA_PRIM2),
        gsDPSetOtherMode(DKR_OMH_2CYC_POINT, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK4, G_CC_MODULATEIA_PRIM2),
        gsDPSetOtherMode(DKR_OMH_2CYC_POINT, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK4, G_CC_MODULATEIA_PRIM2),
        gsDPSetOtherMode(DKR_OMH_2CYC_POINT, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_XLU_SURF2),
    },
};

Gfx D_800DF028[][2] = {
    {
        gsDPSetCombineMode(DKR_CC_DECALFADEPRIM, DKR_CC_DECALFADEPRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_ZB_OPA_DECAL | G_RM_ZB_OPA_DECAL2),
    },
    {
        gsDPSetCombineMode(DKR_CC_DECALFADEPRIM, DKR_CC_DECALFADEPRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_OPA_DECAL | G_RM_AA_ZB_OPA_DECAL2),
    },
    {
        gsDPSetCombineMode(DKR_CC_DECALFADEPRIM, DKR_CC_DECALFADEPRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_ZB_XLU_DECAL | G_RM_ZB_XLU_DECAL2),
    },
    {
        gsDPSetCombineMode(DKR_CC_DECALFADEPRIM, DKR_CC_DECALFADEPRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_XLU_DECAL | G_RM_AA_ZB_XLU_DECAL2),
    },
    {
        gsDPSetCombineMode(DKR_CC_DECALFADEPRIM, DKR_CC_DECALFADEPRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_ZB_OPA_DECAL | G_RM_ZB_OPA_DECAL2),
    },
    {
        gsDPSetCombineMode(DKR_CC_DECALFADEPRIM, DKR_CC_DECALFADEPRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_OPA_DECAL | G_RM_AA_ZB_OPA_DECAL2),
    },
    {
        gsDPSetCombineMode(DKR_CC_DECALFADEPRIM, DKR_CC_DECALFADEPRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_ZB_XLU_DECAL | G_RM_ZB_XLU_DECAL2),
    },
    {
        gsDPSetCombineMode(DKR_CC_DECALFADEPRIM, DKR_CC_DECALFADEPRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_CI_BILERP, DKR_OML_COMMON | G_RM_AA_ZB_XLU_DECAL | G_RM_AA_ZB_XLU_DECAL2),
    },
};

Gfx D_800DF0A8[][2] = {
    {
        gsDPSetCombineMode(DKR_CC_UNK5, DKR_CC_UNK6),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK5, DKR_CC_UNK6),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_AA_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK5, DKR_CC_UNK6),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK5, DKR_CC_UNK6),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_AA_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK5, DKR_CC_UNK6),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK5, DKR_CC_UNK6),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK5, DKR_CC_UNK6),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK5, DKR_CC_UNK6),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_AA_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK5, DKR_CC_UNK6),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK5, DKR_CC_UNK6),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_AA_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK5, DKR_CC_UNK6),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK5, DKR_CC_UNK6),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_AA_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK5, DKR_CC_UNK6),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK5, DKR_CC_UNK6),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK5, DKR_CC_UNK6),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_AA_ZB_TEX_EDGE2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK5, DKR_CC_UNK6),
        gsDPSetOtherMode(DKR_OMH_2CYC_CI_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_AA_ZB_XLU_INTER2),
    },
};

Gfx D_800DF1A8[][2] = {
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_AA_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_AA_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_AA_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_AA_ZB_TEX_EDGE2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | DKR_RM_UNKNOWN4_2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | G_RM_AA_ZB_TEX_EDGE2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_NOOP | DKR_RM_UNKNOWN4_2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_TEX_EDGE2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | DKR_RM_UNKNOWN4_2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | G_RM_AA_ZB_TEX_EDGE2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK7, DKR_CC_UNK8),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_FOG_SHADE_A | DKR_RM_UNKNOWN4_2),
    },
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
    {
        gsDPSetCombineMode(DKR_CC_UNK9, DKR_CC_UNK9),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP_NOPERSP, DKR_OML_COMMON | G_RM_ZB_CLD_SURF | G_RM_ZB_CLD_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_BLENDPE, G_CC_BLENDPE),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_ZB_CLD_SURF | G_RM_ZB_CLD_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_UNK9, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_BILERP, DKR_OML_COMMON | G_RM_ZB_CLD_SURF | G_RM_ZB_CLD_SURF2),
    },
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

s32 *D_80126320[2];

TextureCacheEntry *gTextureCache;

u8 *gCiPalettes;
s32 gNumberOfLoadedTextures;
s32 D_80126334;
s32 D_80126338[2];
s32 gCiPalettesSize;
s32 D_80126344;
s32 *gSpriteOffsetTable;

SpriteCacheEntry *gSpriteCache;

Sprite *gCurrentSprite;
s32 D_80126354;
s32 D_80126358;
s32 D_8012635C;
s32 D_80126360;
s32 D_80126364;
s32 D_80126368;

TempTexHeader *gTempTextureHeader;
s32 D_80126370;
s32 gCurrentRenderFlags;
s32 D_80126378; // Set in Game UI
TextureHeader *D_8012637C;
s16 D_80126380;
s16 gForceFlags;
s16 D_80126384;

/******************************/

GLOBAL_ASM("asm/non_matchings/textures_sprites/texInitTextures.s")

void texDisableModes(s32 flags) {
    D_80126378 |= flags;
}

void texEnableModes(s32 flags) {
    D_80126378 &= ~flags;
}

/* Unused? */
s32 func_8007AE44(void) {
    return D_80126338[0];
}

/* Unused? */
s32 func_8007AE54(void) {
    return D_80126338[1];
}

/* Unused? */
s32 func_8007AE64(void) {
    return D_80126354;
}

#ifdef NON_EQUIVALENT
// Minor matching issues with loops, but should be functionally the same.
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
    if ((assetIndex >= D_80126338[assetTable]) || (assetIndex < 0)) {
        arg0 = 0;
    }
    for (i = 0; i < gNumberOfLoadedTextures; i++) {
        if (arg0 == gTextureCache[i].id) {
            tex = gTextureCache[i].texture;
            tex->numberOfInstances++;
            return tex;
        }
    }
    assetOffset = D_80126320[assetTable][assetIndex];
    assetSize = D_80126320[assetTable][assetIndex + 1] - assetOffset;
    load_asset_to_address(assetSection, gTempTextureHeader, assetOffset, 0x28);
    numberOfTextures = (gTempTextureHeader->header.numOfTextures >> 8) & 0xFFFF;

    if (!gTempTextureHeader->header.isCompressed) {
        tex = allocate_from_main_pool((numberOfTextures * 0x60) + assetSize, gTexColourTag);
        if (tex == NULL) {
            return NULL;
        }
        load_asset_to_address(assetSection, tex, assetOffset, assetSize);
    } else {
        temp_v0_5 = byteswap32(&gTempTextureHeader->uncompressedSize);
        temp_a0 = (numberOfTextures * 0x60) + temp_v0_5;
        sp3C = temp_v0_5 + 0x20;
        tex = allocate_from_main_pool(temp_a0 + 0x20, gTexColourTag);
        if (tex == NULL) {
            return NULL;
        }
        temp_a1 = ((s32)tex + sp3C) - assetSize;
        temp_a1 -= temp_a1 % 0x10;
        load_asset_to_address(assetSection, temp_a1, assetOffset, assetSize);
        gzip_inflate(temp_a1 + 0x20, tex);
        assetSize = sp3C - 0x20;
    }
    texIndex = -1;
    for (i = 0; i < gNumberOfLoadedTextures; i++) {
        if (gTextureCache[i].id == -1) {
            texIndex = i;
        }
    }
    if (texIndex == -1) {
        texIndex = gNumberOfLoadedTextures++;
    }
    gTextureCache[texIndex].id = arg0;
    gTextureCache[texIndex].texture = tex;
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
    alignedAddress = align16((u8 *)((s32)texTemp + assetSize));
    for (i = 0; i < numberOfTextures; i++) {
        build_tex_display_list(texTemp, alignedAddress);
        if (paletteOffset >= 0) {
            texTemp->ciPaletteOffset = paletteOffset;
            alignedAddress += 0x30; // I'm guessing it takes 6 f3d commands to load the palette
        }
        alignedAddress += 0x60; // I'm guessing it takes 12 f3d commands to load the texture
        texTemp = (TextureHeader *)((s32)texTemp + texTemp->textureSize);
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
GLOBAL_ASM("asm/non_matchings/textures_sprites/load_texture.s")
#endif

#ifdef NON_EQUIVALENT
void free_texture(TextureHeader *tex) {
    s32 i;
    if (tex != NULL) {
        tex->numberOfInstances--;
        if ((tex->numberOfInstances & 0xFF) <= 0) {
            for (i = 0; i < gNumberOfLoadedTextures; i++) {
                if (tex == gTextureCache[i].texture) {
                    free_from_memory_pool(tex);
                    gTextureCache[i].id = -1;
                    gTextureCache[i].texture = (TextureHeader *)-1;
                }
            }
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/textures_sprites/free_texture.s")
#endif

/**
 * Set the colour tag that determines which memory pool textures will be loaded into.
 * By default, this generally stays as COLOUR_TAG_MAGENTA
*/
void set_texture_colour_tag(s32 tagID) {
    gTexColourTag = tagID;
}

#ifdef NON_EQUIVALENT
// Unused.
TextureHeader *func_8007B380(s32 arg0) {
    if ((arg0 < 0) || (arg0 >= gNumberOfLoadedTextures)) {
        return 0;
    }
    // Regalloc issue here
    if (gTextureCache[arg0].texture == (TextureHeader *)-1) {
        return 0;
    }
    return gTextureCache[arg0].texture;
}
#else
GLOBAL_ASM("asm/non_matchings/textures_sprites/func_8007B380.s")
#endif

/**
 * Resets all render settings to the default state.
 * The next draw call will be forced to apply all settings instead of skipping unecessary steps.
*/
void reset_render_settings(Gfx **dlist) {
    D_8012637C = NULL;
    gCurrentRenderFlags = RENDER_NONE;
    D_80126380 = 0;
    gForceFlags = TRUE;
    D_80126378 = RENDER_NONE;
    D_80126384 = FALSE;
    gDPPipeSync((*dlist)++);
    gSPSetGeometryMode((*dlist)++, G_SHADING_SMOOTH | G_SHADE | G_ZBUFFER);
}

void func_8007B43C(void) {
    D_80126384 = TRUE;
    gForceFlags = TRUE;
}

void func_8007B454(void) {
    D_80126384 = FALSE;
    gForceFlags = TRUE;
}

typedef struct Struct_Unk_8007B46C {
    u8 pad0[0x12];
    u16 unk12;
    u8 pad14[2];
    s16 unk16;
    u8 pad17[3];
} Struct_Unk_8007B46C;

Struct_Unk_8007B46C *func_8007B46C(Struct_Unk_8007B46C *arg0, s32 arg1) {
    if (arg1 > 0) {
        if (arg1 < arg0->unk12 << 8) {
            arg0 = (Struct_Unk_8007B46C *) (((u8*)arg0) + ((arg1 >> 16) * arg0->unk16));
        } else {
            arg0 = (Struct_Unk_8007B46C *) (((u8*)arg0) + ((arg0->unk12 >> 8) - 1) * arg0->unk16);
        }
    }
    return arg0;
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
        if (texhead != D_8012637C) {
            gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(texhead->cmd), texhead->numberOfCommands);
            D_8012637C = texhead;
            doPipeSync = FALSE;
        }
        if (D_80126380 == 0) {
            forceFlags = TRUE;
            D_80126380 = 1;
        }
    } else if (D_80126380 != 0) {
        forceFlags = TRUE;
        D_80126380 = 0;
    }

    flags = (D_80126384) ? (flags & (RENDER_DECAL | RENDER_COLOUR_INDEX | RENDER_ANTI_ALIASING | RENDER_Z_COMPARE | RENDER_SEMI_TRANSPARENT)) : (flags & (RENDER_UNK_8000000 | RENDER_DECAL | RENDER_Z_UPDATE | RENDER_COLOUR_INDEX | RENDER_UNK_0000010 | RENDER_FOG_ACTIVE | RENDER_SEMI_TRANSPARENT | RENDER_Z_COMPARE | RENDER_ANTI_ALIASING));
    flags &= ~D_80126378;
    flags = (flags & RENDER_UNK_8000000) ? flags & ~RENDER_FOG_ACTIVE : flags & ~RENDER_Z_UPDATE;

    if ((flags != gCurrentRenderFlags) || (forceFlags)) {
        if (doPipeSync) {
            gDPPipeSync((*dlist)++);
        }

        if (((flags & RENDER_UNK_8000000) != (gCurrentRenderFlags & RENDER_UNK_8000000)) || ((gForceFlags))) {
            if ((flags & RENDER_UNK_8000000) || (D_80126384)) {
                gSPClearGeometryMode((*dlist)++, G_FOG);
            } else {
                gSPSetGeometryMode((*dlist)++, G_FOG);
            }
        }

        if (((flags & RENDER_Z_COMPARE) != (gCurrentRenderFlags & RENDER_Z_COMPARE)) || (gForceFlags)) {
            if (flags & RENDER_Z_COMPARE) {
                gSPSetGeometryMode((*dlist)++, G_ZBUFFER);
            } else {
                gSPClearGeometryMode((*dlist)++, G_ZBUFFER);
            }
        }

        gForceFlags = FALSE;
        gCurrentRenderFlags = flags;
        if (!D_80126380) {
            if (flags & RENDER_UNK_8000000) {
                gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(D_800DEEE8[flags & (RENDER_ANTI_ALIASING | RENDER_Z_COMPARE)]), numberOfGfxCommands(D_800DEEE8[0]));
                return;
            }
            gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(D_800DEF28[flags & (RENDER_FOG_ACTIVE | RENDER_SEMI_TRANSPARENT | RENDER_Z_COMPARE | RENDER_ANTI_ALIASING)]), numberOfGfxCommands(D_800DEF28[0]));
            return;
        }

        if (D_80126384) {
            if ((flags & RENDER_DECAL) && (flags & RENDER_Z_COMPARE)) {
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
                gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(D_800DF028[dlIndex]), numberOfGfxCommands(D_800DF028[0]));
                return;
            }
            if (flags & RENDER_COLOUR_INDEX) {
                flags = (flags ^ RENDER_COLOUR_INDEX) | RENDER_FOG_ACTIVE;
            }
            gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(D_800DF0A8[flags]), numberOfGfxCommands(D_800DF0A8[0]));
            return;
        }

        if ((flags & RENDER_DECAL) && (flags & RENDER_Z_COMPARE)) {
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
            gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(D_800DEDE8[dlIndex]), numberOfGfxCommands(D_800DEDE8[0]));
            return;
        }

        if (flags & RENDER_UNK_0000010) {
            dlIndex = flags & (RENDER_ANTI_ALIASING | RENDER_Z_COMPARE | RENDER_SEMI_TRANSPARENT);
            if (flags & RENDER_FOG_ACTIVE) {
                dlIndex |= 8; // Fog
            }
            gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(D_800DECE8[dlIndex]), numberOfGfxCommands(D_800DECE8[0]));
            return;
        }

        flags &= ~RENDER_DECAL;
        if (flags & RENDER_UNK_8000000) {
            dlIndex = flags & (RENDER_ANTI_ALIASING | RENDER_Z_COMPARE);
            if (flags & RENDER_Z_UPDATE) {
                dlIndex |= 4; // Z write
            } else {
                gSPSetGeometryMode((*dlist)++, G_ZBUFFER);
                gCurrentRenderFlags |= RENDER_Z_COMPARE;
            }
            gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(D_800DE7C8[dlIndex]), numberOfGfxCommands(D_800DE7C8[0]));
            return;
        }

        gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(D_800DE8E8[flags]), numberOfGfxCommands(D_800DE8E8[0]));
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
    mblock = (u16*)(texture_list + 1);
    tblock = mblock + 0x400;
    if (texture_list->width == 64) {
        gDPLoadMultiBlock((*dlist)++, OS_K0_TO_PHYSICAL(mblock), 256, 1,
            G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 16, 0, 0, 0, 6, 4, 0, 0);
        gDPLoadTextureBlock((*dlist)++, OS_K0_TO_PHYSICAL(tblock),
            G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 16, 0, 0, 0, 6, 4, 0, 0);
    } else {
        gDPLoadMultiBlock((*dlist)++, OS_K0_TO_PHYSICAL(mblock), 256, 1,
            G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, 0, 0, 5, 5, 0, 0);
        gDPLoadTextureBlock((*dlist)++, OS_K0_TO_PHYSICAL(tblock),
            G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, 0, 0, 5, 5, 0, 0);
    }
    
    // gSPSetGeometryMode((*dlist)++, 0);
    gDPPipeSync((*dlist)++);
    D_8012637C = 0;
    flags &= 0x1F;
    gSPSetGeometryMode((*dlist)++, G_FOG);

    if (flags & G_TEXTURE_ENABLE) {
        gSPSetGeometryMode((*dlist)++, G_ZBUFFER);
    } else {
        gSPClearGeometryMode((*dlist)++, G_ZBUFFER);
    }
    gForceFlags = TRUE;
    gCurrentRenderFlags = RENDER_NONE;
    gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(D_800DF1A8[flags]), numberOfGfxCommands(D_800DF1A8[0]));
}


void func_8007BF1C(s32 arg0) {
    D_800DE7C4 = arg0;
    gForceFlags = TRUE;
}

#ifdef NON_EQUIVALENT
// Reasonably certain the macros are correct, but definitely need to figure out the gDkrDmaDisplayList Gfx arguments
void func_8007BF34(Gfx **dlist, s32 arg1) {
    s32 temp_a1;
    s32 temp_t8;
    s32 temp_v0_3;

    if ((arg1 != gCurrentRenderFlags) || (gForceFlags != 0)) {
        gDPPipeSync((*dlist)++);
        if (((gCurrentRenderFlags * 16) < 0) || (gForceFlags != 0)) {
            gSPSetGeometryMode((*dlist)++, G_FOG);
        }
        temp_a1 = arg1 & 0xF7FFFFFF & ~D_80126378;
        temp_v0_3 = temp_a1 & 2;
        if (((gCurrentRenderFlags & 2) != temp_v0_3) || (gForceFlags != 0)) {
            if (temp_v0_3 != 0) {
                gSPSetGeometryMode((*dlist)++, G_ZBUFFER);
            } else {
                gSPClearGeometryMode((*dlist)++, G_ZBUFFER);
            }
        }
        gForceFlags = 0;
        gCurrentRenderFlags = temp_a1;
        temp_t8 = temp_a1 & ~0x800;
        if (D_800DE7C4 == 0) {
            if ((gCurrentRenderFlags & 0x200) != 0) {
                gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(D_800DE848[((temp_t8 >> 1) & 1) * 16]), numberOfGfxCommands(D_800DE848[0]));
            } else {
                gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(D_800DE868[(temp_t8 - 16) * 16]), numberOfGfxCommands(D_800DE868[0]));
            }
        } else {
            gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(D_800DE8E8[temp_t8 * 16]), numberOfGfxCommands(D_800DE8E8[0]));
        }
        D_8012637C = NULL;
        D_80126380 = 1;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/textures_sprites/func_8007BF34.s")
#endif

GLOBAL_ASM("asm/non_matchings/textures_sprites/func_8007C12C.s")

#ifdef NON_MATCHING
Sprite *func_8007C52C(s32 arg0) {
    Sprite *temp_v1;

    if ((arg0 < 0) || (arg0 >= D_80126358)) {
        return NULL;
    }
    temp_v1 = gSpriteCache[arg0].sprite;
    if (temp_v1 == (Sprite *)-1) {
        return NULL;
    }
    return temp_v1;
}
#else
GLOBAL_ASM("asm/non_matchings/textures_sprites/func_8007C52C.s")
#endif

#ifdef NON_EQUIVALENT
// Mostly has regalloc issues.
s32 get_texture_size_from_id(s32 arg0) {
    s32 assetIndex;
    s32 assetSection;
    s32 assetTable;
    s32 start;
    s32 size;

    assetSection = ASSET_TEXTURES_2D;
    assetIndex = arg0;
    assetTable = 0;
    if (arg0 & 0x8000) {
        assetIndex = arg0 & 0x7FFF;
        assetSection = ASSET_TEXTURES_3D;
        assetTable = 1;
    }
    if ((assetIndex >= D_80126338[assetTable]) || (assetIndex < 0)) {
        return 0;
    }
    start = D_80126320[assetTable][assetIndex];
    size = D_80126320[assetTable][assetIndex + 1] - start;
    if (gTempTextureHeader->header.isCompressed) {
        load_asset_to_address(assetSection, gTempTextureHeader, start, 0x28);
        size = byteswap32(&gTempTextureHeader->uncompressedSize);
    }
    return (((gTempTextureHeader->header.numOfTextures >> 8) & 0xFFFF) * 0x60) + size;
}

#else
GLOBAL_ASM("asm/non_matchings/textures_sprites/get_texture_size_from_id.s")
#endif

GLOBAL_ASM("asm/non_matchings/textures_sprites/func_8007C660.s")

UNUSED s32 func_8007C860(s32 spriteIndex) {
    if ((spriteIndex < 0) || (spriteIndex >= gNumberOfLoadedTextures)) {
        return -1;
    }
    return ((TextureCacheEntry *) ((s32*) gTextureCache + spriteIndex * 2))->id;
}

UNUSED s32 func_8007C8A0(s32 spriteIndex) {
    if ((spriteIndex < 0) || (spriteIndex >= D_80126358)) {
        return -1;
    }
    return ((SpriteCacheEntry*) ((s32*) gSpriteCache + spriteIndex * 2))->id;
}

#ifdef NON_EQUIVALENT
s32 load_sprite_info(s32 spriteIndex, s32 *numOfInstancesOut, s32 *unkOut, s32 *numFramesOut, s32 *formatOut, s32 *sizeOut) {
    TextureHeader *tex;
    s32 i, j;
    s32 start, size;

    if ((spriteIndex < 0) || (spriteIndex >= D_80126354)) {
        *numFramesOut = 0;
        *numOfInstancesOut = 0;
        *unkOut = 0;
        return;
    }
    start = gSpriteOffsetTable[spriteIndex];
    size = gSpriteOffsetTable[spriteIndex + 1] - start;
    load_asset_to_address(ASSET_SPRITES, gCurrentSprite, start, size);
    tex = load_texture(gCurrentSprite->unkC[0] + gCurrentSprite->baseTextureId);
    if (tex != NULL) {
        *formatOut = tex->format & 0xF;
        free_texture(tex);
        *sizeOut = 0;
        for (i = 0; i < gCurrentSprite->numberOfFrames; i++) {
            for (j = (s32) gCurrentSprite->unkC[i]; j < (s32) gCurrentSprite->unkC[i + 1]; j++) {
                *sizeOut += get_texture_size_from_id(gCurrentSprite->baseTextureId + j);
            }
        }
        *numFramesOut = gCurrentSprite->numberOfFrames;
        *numOfInstancesOut = gCurrentSprite->numberOfInstances;
        *unkOut = gCurrentSprite->unk6;
        return 1;
    }
    *numFramesOut = 0;
    *numOfInstancesOut = 0;
    *unkOut = 0;
    return 0;
}
#else
GLOBAL_ASM("asm/non_matchings/textures_sprites/load_sprite_info.s")
#endif

GLOBAL_ASM("asm/non_matchings/textures_sprites/func_8007CA68.s")

#ifdef NON_EQUIVALENT
// andi 0xff instead of a simple mov for j = i. s32 doesn't work.
void free_sprite(Sprite *sprite) {
    s32 i;
    u8 j;
    s32 frame;
    s32 spriteId;
    SpriteCacheEntry *cache;

    if (sprite != NULL) {
        sprite->numberOfInstances--;
        if (sprite->numberOfInstances <= 0) {
            for (i = 0; i < D_80126358; i++) {
                j = i; // What?
                if (sprite == gSpriteCache[j].sprite) {
                    for (frame = 0; frame < sprite->numberOfFrames; frame++) {
                        free_texture(sprite->frames[frame]);
                    }
                    spriteId = -1;
                    free_from_memory_pool(sprite);
                    gSpriteCache[j].id = spriteId;
                    gSpriteCache[j].sprite = (Sprite *)spriteId; // ?
                    break;
                }
            }
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/textures_sprites/free_sprite.s")
#endif

GLOBAL_ASM("asm/non_matchings/textures_sprites/func_8007CDC0.s")
GLOBAL_ASM("asm/non_matchings/textures_sprites/build_tex_display_list.s")

s32 func_8007EF64(s16 arg0) {
    return (s32) (arg0 + gCiPalettes);
}

// There might be a file boundary here.

void func_8007EF80(TextureHeader *texture, u32 *triangleBatchInfoFlags, s32 *arg2, s32 updateRate) {
    s32 bit23Set;
    s32 bit25Set;
    s32 bit26Set;
    s32 phi_a0;

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
            *arg2 = *arg2 + (texture->frameAdvanceDelay * updateRate);
            if (*arg2 >= texture->numOfTextures) {
                *arg2 = ((texture->numOfTextures * 2) - *arg2) - 1;
                if (*arg2 < 0) {
                    *arg2 = 0;
                    *triangleBatchInfoFlags &= ~(BATCH_FLAGS_UNK02000000 | BATCH_FLAGS_UNK04000000);
                    return;
                }
                *triangleBatchInfoFlags |= BATCH_FLAGS_UNK04000000;
            }
        } else {
            *arg2 = *arg2 - (texture->frameAdvanceDelay * updateRate);
            if (*arg2 < 0) {
                *arg2 = 0;
                *triangleBatchInfoFlags &= ~(BATCH_FLAGS_UNK02000000 | BATCH_FLAGS_UNK04000000);
            }
        }
    } else {
        if (bit25Set) {
            if (!bit26Set) {
                *arg2 += texture->frameAdvanceDelay * updateRate;
            } else {
                *arg2 -= texture->frameAdvanceDelay * updateRate;
            }
            do {
                phi_a0 = 0;
                if (*arg2 < 0) {
                    *arg2 = -*arg2;
                    *triangleBatchInfoFlags &= ~BATCH_FLAGS_UNK04000000;
                    phi_a0 = 1;
                }
                if (*arg2 >= texture->numOfTextures) {
                    *arg2 = ((texture->numOfTextures * 2) - *arg2) - 1;
                    *triangleBatchInfoFlags |= BATCH_FLAGS_UNK04000000;
                    phi_a0 = 1;
                }
            } while (phi_a0 != 0);
            return;
        }
        if (!bit26Set) {
            *arg2 = *arg2 + (texture->frameAdvanceDelay * updateRate);
            if (*arg2 >= texture->numOfTextures) {
                do {
                    *arg2 -= texture->numOfTextures;
                } while (*arg2 >= texture->numOfTextures);
            }
        } else {
            *arg2 = *arg2 - (texture->frameAdvanceDelay * updateRate);
            if (*arg2 < 0) {
                do {
                    *arg2 += texture->numOfTextures;
                } while (*arg2 < 0);
            }
        }
    }
}

void func_8007F1E8(unk8007F1E8 *arg0) {
    s32 i;

    arg0->unk4 = 0;
    arg0->unk8 = 0;
    arg0->unkC = 0;
    arg0->unk10 = arg0->unk14;
    arg0->unk11 = arg0->unk15;
    arg0->unk12 = arg0->unk16;
    arg0->unk13 = arg0->unk17;
    for (i = 0; i < arg0->unk0; i++) {
        arg0->unkC += arg0->unk18[i].unk0;
    }
}

GLOBAL_ASM("asm/non_matchings/textures_sprites/func_8007F24C.s")

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

#ifdef NON_EQUIVALENT
void func_8007F594(Gfx **dlist, u32 index, u32 primitiveColor, u32 environmentColor) {
    Gfx *tempDlist = D_800DF3A8;

    if (index >= 2) {
        index = 2;
        tempDlist = D_800DF3D8;
    }

    // There are issues with the structure, but this should be equivalent functionality-wise.
    gSPDisplayList((*dlist)++, tempDlist);
    gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(D_800DF410[index]), numberOfGfxCommands(D_800DF410[0]));
    gDPSetPrimColorRGBA((*dlist)++, primitiveColor);
    gDPSetEnvColorRGBA((*dlist)++, environmentColor);
}
#else
GLOBAL_ASM("asm/non_matchings/textures_sprites/func_8007F594.s")
#endif
