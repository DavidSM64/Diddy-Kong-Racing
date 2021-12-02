/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80077450 */

#include "unknown_078050.h"
#include "types.h"
#include "structs.h"
#include "macros.h"
//#include "lib/src/unknown_0D24D0.h"

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

unk800DE4D0 D_800DE4D0 = { NULL };
s32 D_800DE4D4 = 0;
s32 D_800DE4D8 = 0;
s32 D_800DE4DC = 0;

Gfx dl_rsp_init[] = {
    gsSPClearGeometryMode(0x001F3204),
    gsSPTexture(0, 0, 0, 0, 0),
    gsSPSetGeometryMode(G_SHADING_SMOOTH | G_SHADE),
    gsSPClipRatio(FRUSTRATIO_2),
    gsSPEndDisplayList(),
};

// Default RDP settings
Gfx dl_rdp_init[] = {
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
    },
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
    },
};

/*******************************/

/************ .bss ************/

s32 D_801242A0[256];
s32 D_801246A0[1536];
OSMesgQueue D_80125EA0;
OSMesg D_80125EB8;
OSMesgQueue D_80125EC0;
OSMesgQueue D_80125ED8;
OSMesg D_80125EF0;
s32 D_80125EF8[6];
OSMesg D_80125F10;
s32 D_80125F18[6];
u8 D_80125F30;
u8 D_80125F31;
u8 D_80125F32;
u8 D_80125F33;
u8 D_80125F34;
u8 D_80125F35;
u8 D_80125F36;
u8 D_80125F37;
s32 D_80125F38;
s32 D_80125F3C;
s32 D_80125F40[56];
s32 D_80126020[56];
OSMesgQueue *osScInterruptQ;

/*******************************/

GLOBAL_ASM("asm/non_matchings/unknown_078050/setupOSTasks.s")

s32 func_80077A54(void) {
    OSMesg *sp1C = NULL;
    if (D_800DE4DC == 0) {
        return 0;
    }
    osRecvMesg(&D_80125ED8, &sp1C, 1);
    D_800DE4DC = 0;
    return sp1C[1];
}

void func_80077AAC(void *bufPtr, s32 arg1, s32 arg2) {
    osWritebackDCacheAll();
    while (osDpGetStatus() & DPC_CLR_CMD_CTR) {}
    osDpSetNextBuffer(bufPtr, arg1);
    while (osDpGetStatus() & DPC_CLR_CMD_CTR) {}
}

//Probable red, green, blue
void func_80077B34(u8 arg0, u8 arg1, u8 arg2) {
    D_800DE4B0 = arg0;
    D_800DE4B4 = arg1;
    D_800DE4B8 = arg2;
}

void func_80077B5C(s32 red, s32 green, s32 blue) {
    D_800DE4BC = ((red << 8) & 0xF800) | ((green * 8) & 0x7C0) | ((blue >> 2) & 0x3E) | 1;
    D_800DE4BC |= (D_800DE4BC << 0x10);
}

#ifdef NON_MATCHING
// Stack issues
void render_background(Gfx **dlist, s32 *arg1, s32 arg2) {
    s32 sp90;
    s32 sp8C;
    s32 sp88;
    s32 sp84;
    s32 widthAndHeight;
    s32 w, h;
    s32 rgba16Color;

    widthAndHeight = get_video_width_and_height_as_s32();
    w = widthAndHeight & 0xFFFF;
    h = widthAndHeight >> 0x10;

    gDPPipeSync((*dlist)++);
    gDPSetScissor((*dlist)++, 0, 0, 0, w - 1, h - 1);
    gDPSetCycleType((*dlist)++, G_CYC_FILL);
    gDPSetColorImage((*dlist)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, w, 0x02000000);
    gDPSetFillColor((*dlist)++, 0xFFFCFFFC);
    gDPFillRectangle((*dlist)++, 0, 0, w - 1, h - 1);
    gDPPipeSync((*dlist)++);
    gDPSetColorImage((*dlist)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, w, 0x01000000);
    if (arg2) {
        if (func_80066910(0)) {
            if (D_800DE4CC) {
                func_800787FC(dlist);
            } else if (D_800DE4C4 != 0) {
                func_80078190(dlist);
            } else if (D_800DE4D0.ptr != NULL) {
                D_800DE4D0.function(dlist, arg1);
            } else {
                gDPSetFillColor((*dlist)++, D_800DE4BC);
                gDPFillRectangle((*dlist)++, 0, 0, w - 1, h - 1);
            }
            if (func_80066BA8(0, &sp90, &sp8C, &sp88, &sp84)) {
                gDPSetCycleType((*dlist)++, G_CYC_1CYCLE);
                gDPSetPrimColor((*dlist)++, 0, 0, D_800DE4B0, D_800DE4B4, D_800DE4B8, 0xFF);
                gDPSetCombineMode((*dlist)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
                gDPSetRenderMode((*dlist)++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
                gDPFillRectangle((*dlist)++, sp90, sp8C, sp88, sp84);
            }
        } else {
            if (D_800DE4CC) {
                func_800787FC(dlist);
            } else if (D_800DE4C4 != 0) {
                func_80078190(dlist);
            } else if (D_800DE4D0.ptr != NULL) {
                D_800DE4D0.function(dlist, arg1);
            } else {
                //Also has an issue here.
                rgba16Color = ((D_800DE4B0 << 8) & 0xF800) | ((D_800DE4B4 * 8) & 0x7C0) | ((D_800DE4B8 >> 2) & 0x3E) | 1;
                rgba16Color |= rgba16Color << 0x10;
                gDPSetFillColor((*dlist)++, rgba16Color);
                gDPFillRectangle((*dlist)++, 0, 0, w - 1, h - 1);
            }
        }
    }
    gDPPipeSync((*dlist)++);
    func_80067A3C(dlist);
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_078050/render_background.s")
#endif

void init_rdp_and_framebuffer(Gfx **dlist) {
    s32 width = get_video_width_and_height_as_s32() & 0xFFF;
    gDPSetColorImage((*dlist)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, 0x01000000);
    gDPSetDepthImage((*dlist)++, 0x2000000);
    gSPDisplayList((*dlist)++, dl_rdp_init);
}

void init_rsp(Gfx **dlist) {
    gSPDisplayList((*dlist)++, dl_rsp_init);
}

void func_80078100(OSSched *sc) {
    osScInterruptQ = osScGetInterruptQ(sc);
    osCreateMesgQueue(&D_80125EA0, &D_80125EB8, 1);
    osCreateMesgQueue(&D_80125EC0, &D_80125EF0, 8);
    osCreateMesgQueue(&D_80125ED8, &D_80125F10, 8);
}

void func_80078170(u32 arg0, u32 arg1, u32 arg2) {
    D_800DE4C4 = arg0;
    D_800DE4C8 = arg1;
    D_800DE4C0 = arg2 << 2;
}

GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80078190.s")

// Unused
void func_80078778(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_80125F30 = (arg0 >> 24) & 0xFF;
    D_80125F31 = (arg0 >> 16) & 0xFF;
    D_80125F32 = (arg0 >> 8) & 0xFF;
    D_80125F33 = arg0 & 0xFF;
    D_80125F34 = (arg1 >> 24) & 0xFF;
    D_80125F35 = (arg1 >> 16) & 0xFF;
    D_80125F36 = (arg1 >> 8) & 0xFF;
    D_80125F37 = arg1 & 0xFF;
    D_80125F38 = arg2;
    D_80125F3C = arg3;
    D_800DE4CC = 1;
}

// Unused
void func_800787F0(void) {
    D_800DE4CC = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_078050/func_800787FC.s")

void func_80078AAC(u32 arg0) {
    D_800DE4D0.ptr = arg0;
}

#ifdef NON_MATCHING

// Regalloc & stack issues.
void render_textured_rectangle(Gfx **dlist, DrawTexture *arg1, s32 arg2, s32 arg3, u8 red, u8 green, u8 blue, u8 alpha) {
    TextureHeader *tex;
    DrawTexture *phi_t2;
    s32 x0, y0;
    s32 x1, y1;
    s32 u, v;

    gSPDisplayList((*dlist)++, D_800DE628);
    gDPSetPrimColor((*dlist)++, 0, 0, red, green, blue, alpha);
    tex = arg1->texture;
    while (tex != NULL) {
        x0 = (arg1->xOffset * 4) + (arg2 * 4);
        y0 = (arg1->yOffset * 4) + (arg3 * 4);
        x1 = (tex->width * 4) + x0;
        y1 = (tex->height * 4) + y0;
        if (x1 > 0) {
            u = 0;
            if (y1 > 0) {
                v = 0;
                if (x0 < 0) {
                    u = -(x0 * 8);
                    x0 = 0;
                }
                if (y0 < 0) {
                    v = -(y0 * 8);
                    y0 = 0;
                }
                gDkrDmaDisplayList((*dlist)++, tex->cmd + 0x80000000, tex->numberOfCommands);
                gSPTextureRectangle((*dlist)++, x0, y0, x1, y1, 0, u, v, 1024, 1024);
            }
        }
        arg1++;
        tex = arg1->texture;
    }
    gDPPipeSync((*dlist)++);
    gDPSetPrimColor((*dlist)++, 0, 0, 255, 255, 255, 255);
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_078050/render_textured_rectangle.s")
#endif

GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80078D00.s")
