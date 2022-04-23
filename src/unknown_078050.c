/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80077450 */

#include "unknown_078050.h"
#include "types.h"
#include "structs.h"
#include "macros.h"
#include "video.h"
#include "camera.h"
//#include "lib/src/unknown_0D24D0.h"

/************ .data ************/

s16 D_800DE490[16] = {
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

u8 sBackgroundPrimColourR = 0;
u8 sBackgroundPrimColourG = 0;
u8 sBackgroundPrimColourB = 0;
s32 sBackgroundFillColour = 0x00010001;

u32 D_800DE4C0 = 0x40;
u32 D_800DE4C4 = 0;
u32 D_800DE4C8 = 0;
s32 D_800DE4CC = 0;

unk800DE4D0 D_800DE4D0 = { NULL };
s32 D_800DE4D4 = 0;
s32 D_800DE4D8 = 0;
s32 D_800DE4DC = 0;

Gfx dRspInit[] = {
    gsSPClearGeometryMode(0x001F3204),
    gsSPTexture(0, 0, 0, 0, 0),
    gsSPSetGeometryMode(G_SHADING_SMOOTH | G_SHADE),
    gsSPClipRatio(FRUSTRATIO_2),
    gsSPEndDisplayList(),
};

// Default RDP settings
Gfx dRdpInit[] = {
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

u8 gDramStack[SP_DRAM_STACK_SIZE8];
u8 gGfxSPTaskYieldBuffer[0x1800];
OSMesgQueue D_80125EA0;
OSMesg D_80125EB8;
OSMesgQueue D_80125EC0;
OSMesgQueue D_80125ED8;
OSMesg D_80125EF0[8];
OSMesg D_80125F10[8];
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
    s32 *sp1C = NULL;
    if (D_800DE4DC == 0) {
        return 0;
    }
    osRecvMesg(&D_80125ED8, (OSMesg)&sp1C, OS_MESG_BLOCK);
    D_800DE4DC = 0;
    return sp1C[1];
}

void func_80077AAC(void *bufPtr, s32 bufSize, UNUSED s32 unused) {
    osWritebackDCacheAll();
    while (osDpGetStatus() & DPC_CLR_CMD_CTR) {}
    osDpSetNextBuffer(bufPtr, bufSize);
    while (osDpGetStatus() & DPC_CLR_CMD_CTR) {}
}

/**
 * Sets the primitive colour for the cyclemode fillrect background.
 */
void set_background_prim_colour(u8 red, u8 green, u8 blue) {
    sBackgroundPrimColourR = red;
    sBackgroundPrimColourG = green;
    sBackgroundPrimColourB = blue;
}

/**
 * Sets the fill colour for the fillmode fillrect background.
 * Uses RGBA5551
 */
void set_background_fill_colour(s32 red, s32 green, s32 blue) {
    sBackgroundFillColour = GPACK_RGBA5551(red, green, blue, 1);
    sBackgroundFillColour |= (sBackgroundFillColour << 16);
}

#ifdef NON_EQUIVALENT
// Stack issues
void render_background(Gfx **dlist, s32 *arg1, s32 arg2) {
    s32 x1;
    s32 y1;
    s32 x2;
    s32 y2;
    s32 widthAndHeight;
    s32 w, h;
    s32 rgba16Color;

    widthAndHeight = get_video_width_and_height_as_s32();
    w = GET_VIDEO_WIDTH(widthAndHeight);
    h = GET_VIDEO_HEIGHT(widthAndHeight);

    gDPPipeSync((*dlist)++);
    gDPSetScissor((*dlist)++, 0, 0, 0, w - 1, h - 1);
    gDPSetCycleType((*dlist)++, G_CYC_FILL);
    gDPSetColorImage((*dlist)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, w, 0x02000000);
    gDPSetFillColor((*dlist)++, GPACK_RGBA5551(255, 255, 255, 128) << 16 | GPACK_RGBA5551(255, 255, 255, 128));
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
                gDPSetFillColor((*dlist)++, sBackgroundFillColour);
                gDPFillRectangle((*dlist)++, 0, 0, w - 1, h - 1);
            }
            if (copy_viewport_background_size_to_coords(0, &x1, &y1, &x2, &y2)) {
                gDPSetCycleType((*dlist)++, G_CYC_1CYCLE);
                gDPSetPrimColor((*dlist)++, 0, 0, sBackgroundPrimColourR, sBackgroundPrimColourG, sBackgroundPrimColourB, 255);
                gDPSetCombineMode((*dlist)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
                gDPSetRenderMode((*dlist)++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
                gDPFillRectangle((*dlist)++, x1, y1, x2, y2);
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
                rgba16Color = GPACK_RGBA5551(sBackgroundPrimColourR, sBackgroundPrimColourG, sBackgroundPrimColourB, 1);
                rgba16Color |= rgba16Color << 16;
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

/**
 * Gets the framebuffer height, then points to the start of segment 0x01 in memory.
 * afterwards, alls the draw command that initialises all the rendermodes, ready for use.
 */
void init_rdp_and_framebuffer(Gfx **dlist) {
    s32 width = GET_VIDEO_WIDTH(get_video_width_and_height_as_s32());
    gDPSetColorImage((*dlist)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, 0x01000000);
    gDPSetDepthImage((*dlist)++, 0x2000000);
    gSPDisplayList((*dlist)++, dRdpInit);
}

/**
 * Calls the draw command that sets all the OtherModes, ready for use.
 */
void init_rsp(Gfx **dlist) {
    gSPDisplayList((*dlist)++, dRspInit);
}

void func_80078100(OSSched *sc) {
    osScInterruptQ = osScGetInterruptQ(sc);
    osCreateMesgQueue(&D_80125EA0, &D_80125EB8, 1);
    osCreateMesgQueue(&D_80125EC0, D_80125EF0, 8);
    osCreateMesgQueue(&D_80125ED8, D_80125F10, 8);
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

void func_80078AAC(void *arg0) {
    D_800DE4D0.ptr = arg0;
}

#ifdef NON_MATCHING

// Regalloc issues.
void render_textured_rectangle(Gfx **dlist, DrawTexture *arg1, s32 xPos, s32 yPos, u8 red, u8 green, u8 blue, u8 alpha) {
    TextureHeader *tex;
    s32 ulx, uly;
    s32 lrx, lry;
    s32 s, t;
    s32 i;

    gSPDisplayList((*dlist)++, D_800DE628);
    gDPSetPrimColor((*dlist)++, 0, 0, red, green, blue, alpha);
    for (i = 0; (tex = arg1[i].texture); i++) {
        ulx = (arg1[i].xOffset * 4) + (xPos * 4);
        uly = (arg1[i].yOffset * 4) + (yPos * 4);
        lrx = (tex->width * 4) + ulx;
        lry = (tex->height * 4) + uly;
        if (lrx > 0) {
            if (lry > 0) {
                s = 0;
                t = 0;
                if (ulx < 0) {
                    s = -(ulx * 8);
                    ulx = 0;
                }
                if (uly < 0) {
                    t = -(uly * 8);
                    uly = 0;
                }
                gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(tex->cmd), tex->numberOfCommands);
                gSPTextureRectangle((*dlist)++, ulx, uly, lrx, lry, 0, s, t, 1024, 1024);
            }
        }
    }
    gDPPipeSync((*dlist)++);
    gDPSetPrimColor((*dlist)++, 0, 0, 255, 255, 255, 255);
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_078050/render_textured_rectangle.s")
#endif

GLOBAL_ASM("asm/non_matchings/unknown_078050/render_texture_rectangle_scaled.s")
