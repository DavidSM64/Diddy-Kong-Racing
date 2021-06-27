/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80077450 */

#include "unknown_078050.h"

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

/************ .data ************/

s16 D_800DE490[16] = {
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

u8 D_800DE4B0 = 0;
u8 D_800DE4B4 = 0;
u8 D_800DE4B8 = 0;
s32 D_800DE4BC = 0x00010001;

u32 D_800DE4C0 = 0x40;
u32 D_800DE4C4 = 0;
u32 D_800DE4C8 = 0;
s32 D_800DE4CC = 0;

u32 D_800DE4D0 = 0;
s32 D_800DE4D4 = 0;
s32 D_800DE4D8 = 0;
s32 D_800DE4DC = 0;

Gfx D_800DE4E0[] = {
    gsSPClearGeometryMode(0x001F3204),
    gsSPTexture(0, 0, 0, 0, 0),
    gsSPSetGeometryMode(G_SHADING_SMOOTH | G_SHADE),
    gsSPClipRatio(FRUSTRATIO_2),
    gsSPEndDisplayList(),
};

// Default RDP settings
Gfx D_800DE520[] = {
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPPipelineMode(G_PM_1PRIMITIVE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPPipeSync(), 
    gsSPEndDisplayList(),
};

Gfx D_800DE598[] = {
    gsDPPipeSync(), 
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPClearGeometryMode(G_ZBUFFER | G_FOG),
    gsDPPipeSync(), 
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetOtherMode(DKR_OMH_1CYC_POINT_NOPERSP, DKR_OML_COMMON | G_RM_OPA_SURF | G_RM_OPA_SURF2),
    gsSPEndDisplayList(),
};

Gfx D_800DE5E0[] = {
    gsDPPipeSync(), 
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPClearGeometryMode(G_ZBUFFER | G_FOG),
    gsDPPipeSync(), 
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsDPSetOtherMode(DKR_OMH_1CYC_POINT_NOPERSP, DKR_OML_COMMON | G_RM_OPA_SURF | G_RM_OPA_SURF2),
    gsSPEndDisplayList(),
};

Gfx D_800DE628[] = {
    gsDPPipeSync(), 
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPClearGeometryMode(G_ZBUFFER | G_FOG),
    gsDPPipeSync(), 
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetOtherMode(DKR_OMH_1CYC_POINT_NOPERSP, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx D_800DE670[] = {
    gsDPPipeSync(), 
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPClearGeometryMode(G_ZBUFFER | G_FOG),
    gsDPPipeSync(), 
    gsSPEndDisplayList(),
};

Gfx D_800DE6A8[][2] = {
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP_NOPERSP, DKR_OML_COMMON | G_RM_AA_OPA_SURF | G_RM_AA_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP_NOPERSP, DKR_OML_COMMON | G_RM_OPA_SURF | G_RM_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT_NOPERSP, DKR_OML_COMMON | G_RM_AA_OPA_SURF | G_RM_AA_OPA_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT_NOPERSP, DKR_OML_COMMON | G_RM_OPA_SURF | G_RM_OPA_SURF2),
    }
};

Gfx D_800DE6E8[][2] = {
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP_NOPERSP, DKR_OML_COMMON | G_RM_AA_XLU_SURF | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP_NOPERSP, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT_NOPERSP, DKR_OML_COMMON | G_RM_AA_XLU_SURF | G_RM_AA_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT_NOPERSP, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    }
};

/*******************************/

/************ .bss ************/

s32 D_801242A0[256];
s32 D_801246A0[1536];
OSMesgQueue  D_80125EA0;
OSMesg       D_80125EB8;
OSMesgQueue  D_80125EC0;
OSMesgQueue  D_80125ED8;
OSMesg       D_80125EF0;
s32          D_80125EF8[6];
OSMesg       D_80125F10;
s32          D_80125F18[6];
s8 D_80125F30;
s8 D_80125F31;
s8 D_80125F32;
s8 D_80125F33;
s8 D_80125F34;
s8 D_80125F35;
s8 D_80125F36;
s8 D_80125F37;
s32 D_80125F38;
s32 D_80125F3C;
s32 D_80125F40[56];
s32 D_80126020[56];
u32 D_80126100;

/*******************************/

GLOBAL_ASM("asm/non_matchings/unknown_078050/setupOSTasks.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80077A54.s")

void func_80077B34(u8 arg0, u8 arg1, u8 arg2){
    D_800DE4B0 = arg0;
    D_800DE4B4 = arg1;
    D_800DE4B8 = arg2;
}

GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80077B5C.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80077B9C.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80078054.s")



#if 1
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_800780DC.s")
#else
typedef struct{
    u32 unk00;
    u32* unk04;
} struct_800780DC_a0;

void func_800780DC(struct_800780DC_a0** arg0){
    u32* tmp2= D_800DE4E0;
    struct_800780DC_a0* tmp = *arg0;
    

    *arg0 = *arg0 + 1;
    tmp->unk00 = 0x6000000;
    tmp->unk04 = tmp2;
}
#endif


void func_80078100(void){
    D_80126100 = func_8007957C();
    osCreateMesgQueue(&D_80125EA0, &D_80125EB8,1);
    osCreateMesgQueue(&D_80125EC0, &D_80125EF0,8);
    osCreateMesgQueue(&D_80125ED8, &D_80125F10,8);
    
}

void func_80078170(u32 arg0, u32 arg1, u32 arg2){
    D_800DE4C4 = arg0;
    D_800DE4C8 = arg1;
    D_800DE4C0 = arg2 << 2;
}


GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80078190.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_800787FC.s")

void func_80078AAC(u32 arg0){
    D_800DE4D0 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80078AB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80078D00.s")
