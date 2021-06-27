/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8007AC70 */

#include "unknown_07B870.h"

#include "types.h"
#include "macros.h"

/************ .data ************/

u32 D_800DE7C0 = 0xFF00FFFF;
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

s32 D_80126320[2];
s32 D_80126328;
s32 D_8012632C;
s32 D_80126330[2];
s32 D_80126338;
s32 D_8012633C;
s32 D_80126340;
s32 D_80126344;
s32 D_80126348;
s32 D_8012634C;
s32 D_80126350;
s32 D_80126354;
s32 D_80126358;
s32 D_8012635C;
s32 D_80126360;
s32 D_80126364;
s32 D_80126368;
s32 D_8012636C;
s32 D_80126370;
s32 D_80126374;
s32 D_80126378;
s32 D_8012637C;
s16 D_80126380;
s16 D_80126382;
s16 D_80126384;

/******************************/

GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007AC70.s")

void func_8007AE0C(s32 arg0) {
    D_80126378 |= arg0;
}

void func_8007AE28(s32 arg0) {
    D_80126378 &= ~arg0;
}

/* Unused? */
s32 func_8007AE44(void) {
    return D_80126338;
}

/* Unused? */
s32 func_8007AE54(void) {
    return D_8012633C;
}

/* Unused? */
s32 func_8007AE64(void) {
    return D_80126354;
}

GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007AE74.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007B2BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007B374.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007B3D0.s")

void func_8007B43C(void) {
    D_80126384 = 1;
    D_80126382 = 1;
}

void func_8007B454(void) {
    D_80126384 = 0;
    D_80126382 = 1;
}

GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007B46C.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007B4C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007B4E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007BA5C.s")

void func_8007BF1C(s32 arg0) {
    D_800DE7C4 = arg0;
    D_80126382 = 1;
}

GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007BF34.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007C12C.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007C57C.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007C8E0.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007CA68.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007CCB0.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007CDC0.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007D0F4.s")

s32 func_8007EF64(s16 arg0) {
    return arg0 + D_8012632C;
}

GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007EF80.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007F1E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007F24C.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007F414.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007F460.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007F594.s")
