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

s16 gGfxTaskMesgNums[16] = {
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

u8 sBackgroundPrimColourR = 0;
u8 sBackgroundPrimColourG = 0;
u8 sBackgroundPrimColourB = 0;
s32 sBackgroundFillColour = GPACK_RGBA5551(0, 0, 0, 1) | (GPACK_RGBA5551(0, 0, 0, 1) << 16);

u32 D_800DE4C0 = 0x40;
TextureHeader *D_800DE4C4 = 0;
TextureHeader *D_800DE4C8 = 0;
s32 gChecquerBGEnabled = 0;

BackgroundFunction gBackgroundDrawFunc = { NULL };
s32 gfxBufCounter = 0;
s32 gfxBufCounter2 = 0;
s32 gGfxTaskIsRunning = FALSE;

Gfx dRspInit[] = {
    gsSPClearGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_CULL_FRONT | G_CULL_BACK |
                          G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD),
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

Gfx dChequerBGSettings[] = {
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

Gfx dTextureRectangleModes[] = {
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

Gfx dTextureRectangleScaledOpa[][2] = {
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

Gfx dTextureRectangleScaledXlu[][2] = {
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

#define YIELD_BUFFER_SIZE 0x1800

u8 gDramStack[SP_DRAM_STACK_SIZE8];
u8 gGfxSPTaskYieldBuffer[YIELD_BUFFER_SIZE];
OSMesgQueue D_80125EA0;
OSMesg D_80125EB8;
OSMesgQueue D_80125EC0;
OSMesgQueue gGfxTaskMesgQueue;
OSMesg D_80125EF0[8];
OSMesg gGfxTaskMesgBuf[8];
u8 gChequerBGColourR1;
u8 gChequerBGColourG1;
u8 gChequerBGColourB1;
u8 gChequerBGColourA1;
u8 gChequerBGColourR2;
u8 gChequerBGColourG2;
u8 gChequerBGColourB2;
u8 gChequerBGColourA2;
s32 gChequerBGWidth;
s32 gChequerBGHeight;

DKR_OSTask gGfxTaskBuf[2];
DKR_OSTask gGfxTaskBuf2[2];

OSMesgQueue *osScInterruptQ;

/*******************************/

/**
 * Prepare the gfx task for the F3DDKR XBus microcode.
 * Sends a message to the scheduler to start processing an RSP task once set up.
 * Official Name: rcpFast3d
 */
s32 setup_ostask_xbus(Gfx* dlBegin, Gfx* dlEnd, UNUSED s32 recvMesg) {
    DKR_OSTask *dkrtask;

    gGfxTaskIsRunning = TRUE;
    dkrtask = &gGfxTaskBuf[gfxBufCounter];
    gfxBufCounter++;
    if (gfxBufCounter == 2) {
        gfxBufCounter = 0;
    }
    dkrtask->flags = OS_SC_LAST_TASK | OS_SC_NEEDS_RDP | OS_SC_NEEDS_RSP;
    dkrtask->mesgQueue = &gGfxTaskMesgQueue;
    dkrtask->unused58 = COLOUR_TAG_RED;
    dkrtask->unused5C = COLOUR_TAG_RED;
    dkrtask->task.data_ptr = (u64 *) dlBegin;
    dkrtask->task.data_size = ((s32) dlEnd - (s32) dlBegin) >> 3; // Shifted by 3, repsenting the size of the Gfx type.
    dkrtask->task.type = M_GFXTASK;
    dkrtask->task.flags = 2;
    dkrtask->task.ucode_boot = (u64 *) rspF3DDKRBootStart;
    dkrtask->task.ucode_boot_size = (s32) (rspF3DDKRDramStart - rspF3DDKRBootStart);
    dkrtask->task.ucode = (u64 *) rspF3DDKRXbusStart;
    dkrtask->task.ucode_data = (u64 *) rspF3DDKRDataXbusStart;
    dkrtask->task.ucode_data_size = 0x800;
    dkrtask->task.dram_stack = (u64 *) gDramStack;
    dkrtask->task.dram_stack_size = 0x400;
    dkrtask->task.output_buff = (u64 *) gGfxSPTaskYieldBuffer;
    dkrtask->task.output_buff_size = (u64 *) &D_80125EA0;
    dkrtask->task.yield_data_ptr = (u64 *) gGfxTaskYieldData;
    dkrtask->task.yield_data_size = sizeof(gGfxTaskYieldData);
    dkrtask->task.output_buff = NULL;
    dkrtask->task.output_buff_size = NULL;
    dkrtask->next = NULL;
    dkrtask->frameBuffer = gVideoCurrFramebuffer;
    dkrtask->unused60 = 0xFF;
    dkrtask->unused64 = 0xFF;
    osWritebackDCacheAll();
    osSendMesg(osScInterruptQ, dkrtask, OS_MESG_BLOCK);
    return 0;
}

/**
 * Unused variant of the xbus task function.
 * Probably intended to be a secondary task system, since it doesn't set the var saying there's a task running.
 */
UNUSED void setup_ostask_xbus_2(Gfx* dlBegin, Gfx* dlEnd, s32 recvMesg) {
    DKR_OSTask *dkrtask;
    OSMesg mesgBuf;

    mesgBuf = NULL;
    dkrtask = &gGfxTaskBuf2[gfxBufCounter2];
    gfxBufCounter2++;
    if (gfxBufCounter2 == 2) {
        gfxBufCounter2 = 0;
    }
    dkrtask->task.data_ptr = (u64 *) dlBegin;
    dkrtask->task.data_size = (s32) (dlEnd - dlBegin) * sizeof(Gfx);
    dkrtask->task.type = M_GFXTASK;
    dkrtask->task.flags = 2;
    dkrtask->task.ucode_boot = (u64 *) rspF3DDKRBootStart;
    dkrtask->task.ucode_boot_size = (s32) (rspF3DDKRDramStart - rspF3DDKRBootStart);
    dkrtask->task.ucode = (u64 *) rspF3DDKRXbusStart;
    dkrtask->task.ucode_data = (u64 *) rspF3DDKRDataXbusStart;
    dkrtask->task.ucode_data_size = 0x800;
    dkrtask->task.dram_stack = (u64 *) gDramStack;
    dkrtask->task.dram_stack_size = 0x400;
    dkrtask->task.yield_data_ptr = (u64 *) gGfxTaskYieldData;
    dkrtask->task.yield_data_size = sizeof(gGfxTaskYieldData);
    dkrtask->task.output_buff = NULL;
    dkrtask->task.output_buff_size = 0;
    dkrtask->next = NULL;
    dkrtask->flags = OS_SC_NEEDS_RDP | OS_SC_NEEDS_RSP;
    dkrtask->mesgQueue = &gGfxTaskMesgQueue;
    dkrtask->mesg = gGfxTaskMesgNums;
    dkrtask->frameBuffer = gVideoCurrFramebuffer;
    dkrtask->unused58 = COLOUR_TAG_RED;
    dkrtask->unused5C = COLOUR_TAG_RED;
    dkrtask->unused60 = 0xFF;
    dkrtask->unused64 = 0xFF;
    dkrtask->unk68 = 0;
    
    if (recvMesg) {
        dkrtask->mesgQueue = &D_80125EA0;
    }
    osWritebackDCacheAll();
    osSendMesg(osScInterruptQ, dkrtask, 1);
    if (recvMesg) {
        osRecvMesg(&D_80125EA0, &mesgBuf, OS_MESG_BLOCK);
    }
}

/**
 * 
 * Prepare the gfx task for the F3DDKR FIFO microcode.
 * Sends a message to the scheduler to start processing an RSP task once set up.
 * Goes unused, and is broken.
 */
UNUSED void setup_ostask_fifo(Gfx* dlBegin, Gfx* dlEnd, s32 recvMesg) {
    DKR_OSTask *dkrtask;
    OSMesg mesgBuf;

    mesgBuf = NULL;
    dkrtask = &gGfxTaskBuf2[gfxBufCounter2];
    gfxBufCounter2++;
    if (gfxBufCounter2 == 2) {
        gfxBufCounter2 = 0;
    }
    
    dkrtask->task.data_ptr = (u64 *) dlBegin;
    dkrtask->task.ucode_boot = (u64 *) rspF3DDKRBootStart;
    dkrtask->task.data_size = (s32) (dlEnd - dlBegin) * sizeof(Gfx);
    dkrtask->task.type = M_GFXTASK;
    dkrtask->task.flags = 2;
    dkrtask->task.ucode_boot_size = (s32) (rspF3DDKRDramStart - rspF3DDKRBootStart);
    dkrtask->task.ucode = (u64 *) rspF3DDKRFifoStart;
    dkrtask->task.ucode_data = (u64 *) rspF3DDKRDataFifoStart;
    dkrtask->task.ucode_data_size = 0x800;
    dkrtask->task.dram_stack = (u64 *) gDramStack;
    dkrtask->task.dram_stack_size = 0x400;
    dkrtask->task.output_buff = (u64 *) gGfxSPTaskYieldBuffer;
    dkrtask->task.output_buff_size = (u64 *) (gGfxSPTaskYieldBuffer + YIELD_BUFFER_SIZE);
    dkrtask->task.yield_data_ptr = (u64 *) gGfxTaskYieldData;
    dkrtask->task.yield_data_size = sizeof(gGfxTaskYieldData);
    dkrtask->next = NULL;
    dkrtask->flags = OS_SC_NEEDS_RDP | OS_SC_NEEDS_RSP | OS_SC_DRAM_DLIST;
    dkrtask->mesgQueue = &gGfxTaskMesgQueue;
    dkrtask->mesg = gGfxTaskMesgNums;
    dkrtask->frameBuffer = gVideoCurrFramebuffer;
    dkrtask->unused58 = COLOUR_TAG_RED;
    dkrtask->unused5C = COLOUR_TAG_RED;
    dkrtask->unused60 = 0xFF;
    dkrtask->unused64 = 0xFF;
    dkrtask->unk68 = 0;
    
    if (recvMesg) {
        dkrtask->mesgQueue =  &D_80125EA0;
    }
    osWritebackDCacheAll();
    osSendMesg(osScInterruptQ, dkrtask, 1);
    
    if (recvMesg) {
        osRecvMesg(&D_80125EA0, &mesgBuf, OS_MESG_BLOCK);
    }
}

/**
 * Unused variant of the FIFO task function.
 * Probably intended to be a secondary task system, since it doesn't set the var saying there's a task running.
 */
UNUSED void setup_ostask_fifo_2(Gfx* dlBegin, Gfx* dlEnd, s32 recvMesg) {
    DKR_OSTask *dkrtask;
    OSMesg mesgBuf;

    mesgBuf = NULL;
    dkrtask = &gGfxTaskBuf[gfxBufCounter];
    gfxBufCounter++;
    //!@bug - gfxBufCounter being 2 would mean an out of bounds access of gGfxTaskBuf
    if (gfxBufCounter == 3) {
        gfxBufCounter = 0;
    }
    
    dkrtask->task.data_size = (s32) (dlEnd - dlBegin) * sizeof(Gfx);
    dkrtask->task.data_ptr = (u64 *) dlBegin;
    dkrtask->task.type = M_GFXTASK;
    dkrtask->task.flags = 2;
    dkrtask->task.ucode_boot = (u64 *) rspF3DDKRBootStart;
    dkrtask->task.ucode_boot_size = (s32) (rspF3DDKRDramStart - rspF3DDKRBootStart);
    dkrtask->task.ucode = (u64 *) rspF3DDKRFifoStart;
    dkrtask->task.ucode_data = (u64 *) rspF3DDKRDataFifoStart;
    dkrtask->task.ucode_data_size = 0x800;
    dkrtask->task.dram_stack = (u64 *) gDramStack;
    dkrtask->task.dram_stack_size = 0x400;
    dkrtask->task.output_buff = (u64 *) gGfxSPTaskYieldBuffer;
    dkrtask->task.output_buff_size = (u64 *) &D_80125EA0;
    dkrtask->task.yield_data_ptr = (u64 *) gGfxTaskYieldData;
    dkrtask->task.yield_data_size = sizeof(gGfxTaskYieldData);
    dkrtask->next = NULL;
    dkrtask->flags = OS_SC_NEEDS_RDP | OS_SC_NEEDS_RSP | OS_SC_DRAM_DLIST;
    dkrtask->mesgQueue = &gGfxTaskMesgQueue;
    dkrtask->mesg = gGfxTaskMesgNums;
    dkrtask->frameBuffer = gVideoCurrFramebuffer;
    dkrtask->unused58 = COLOUR_TAG_RED;
    dkrtask->unused5C = COLOUR_TAG_RED;
    if (recvMesg) {
        dkrtask->unused60 = 0xFF;
        dkrtask->unused64 = 0xFF;
    }
    dkrtask->unk68 = 0;
    osWritebackDCacheAll();
    osSendMesg(osScInterruptQ, dkrtask, 1);
    if (recvMesg) {
        osRecvMesg(&gGfxTaskMesgQueue, &mesgBuf, OS_MESG_BLOCK);
    }
}

/**
 * Called from the main game loop, will halt until a message comes through saying the graphics task
 * has finished.
 * Alternatively, if no task is active, then it will just skip.
 */
s32 wait_for_gfx_task(void) {
    OSMesg *mesg = NULL;
    if (gGfxTaskIsRunning == FALSE) { 
        return 0;
    }
    osRecvMesg(&gGfxTaskMesgQueue, (OSMesg) &mesg, OS_MESG_BLOCK); 
    gGfxTaskIsRunning = FALSE;
    return (s32) mesg[1];
}

UNUSED void func_80077AAC(void *bufPtr, s32 bufSize, UNUSED s32 unused) {
    osWritebackDCacheAll();
    while (osDpGetStatus() & DPC_CLR_CMD_CTR) {}
    osDpSetNextBuffer(bufPtr, bufSize);
    while (osDpGetStatus() & DPC_CLR_CMD_CTR) {}
}

/**
 * Sets the primitive colour for the cyclemode fillrect background.
 * Official name: rcpSetScreenColour
 */
void set_background_prim_colour(u8 red, u8 green, u8 blue) {
    sBackgroundPrimColourR = red;
    sBackgroundPrimColourG = green;
    sBackgroundPrimColourB = blue;
}

/**
 * Sets the fill colour for the fillmode fillrect background.
 * Uses RGBA5551
 * Official name: rcpSetBorderColour
 */
void set_background_fill_colour(s32 red, s32 green, s32 blue) {
    sBackgroundFillColour = GPACK_RGBA5551(red, green, blue, 1);
    sBackgroundFillColour |= (sBackgroundFillColour << 16);
}
/**
 * Clears the ZBuffer first, then decides how to draw the background which goes directly
 * over the colour buffer. DrawBG if set to 0 (which never happens) will completely skip
 * over clearing the colour buffer.
*/
void render_background(Gfx **dList, Matrix *mtx, s32 drawBG) {
    s32 widthAndHeight;
    s32 w;
    s32 h;
    s32 x1;
    s32 y1;
    s32 x2;
    s32 y2;

    widthAndHeight = get_video_width_and_height_as_s32();
    w = GET_VIDEO_WIDTH(widthAndHeight);
    h = GET_VIDEO_HEIGHT(widthAndHeight);

    gDPPipeSync((*dList)++);
    //!@bug: the scissor does not need the off by one here, despite being intended for fill mode.
    gDPSetScissor((*dList)++, 0, 0, 0, w - 1, h - 1);
    gDPSetCycleType((*dList)++, G_CYC_FILL);
    gDPSetColorImage((*dList)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, w, SEGMENT_DEPTH_BUFFER);
    gDPSetFillColor((*dList)++, GPACK_RGBA5551(255, 255, 240, 0) << 16 | GPACK_RGBA5551(255, 255, 240, 0));
    gDPFillRectangle((*dList)++, 0, 0, w - 1, h - 1);
    gDPPipeSync((*dList)++);
    gDPSetColorImage((*dList)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, w, SEGMENT_COLOUR_BUFFER);
    if (drawBG) {
        if (check_viewport_background_flag(0)) {
            if (gChecquerBGEnabled) {
                render_chequer_background(dList);
            } else if (D_800DE4C4) {
                func_80078190(dList);
            } else if (gBackgroundDrawFunc.ptr != NULL) {
                gBackgroundDrawFunc.function((Gfx *) dList, mtx);
            } else {
                gDPSetFillColor((*dList)++, sBackgroundFillColour);
                gDPFillRectangle((*dList)++, 0, 0, w - 1, h - 1);
            }
            if (copy_viewport_background_size_to_coords(0, &x1, &y1, &x2, &y2)) {
                gDPSetCycleType((*dList)++, G_CYC_1CYCLE);
                gDPSetPrimColor((*dList)++, 0, 0, sBackgroundPrimColourR, sBackgroundPrimColourG, sBackgroundPrimColourB, 255);
                gDPSetCombineMode((*dList)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
                gDPSetRenderMode((*dList)++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
                gDPFillRectangle((*dList)++, x1, y1, x2, y2);
            }
        } else {
            if (gChecquerBGEnabled) {
                render_chequer_background(dList);
            } else if (D_800DE4C4) {
                func_80078190(dList);
            } else if (gBackgroundDrawFunc.ptr != NULL) {
                gBackgroundDrawFunc.function((Gfx *) dList, mtx);
            } else {
                gDPSetFillColor((*dList)++, (GPACK_RGBA5551(sBackgroundPrimColourR, sBackgroundPrimColourG, sBackgroundPrimColourB, 1) << 16) | GPACK_RGBA5551(sBackgroundPrimColourR, sBackgroundPrimColourG, sBackgroundPrimColourB, 1));
                gDPFillRectangle((*dList)++, 0, 0, w - 1, h - 1);
            }
        }
    }
    gDPPipeSync((*dList)++);
    set_viewport_scissor(dList);
}

/**
 * Gets the framebuffer width, then points to the start of segment 0x01 in memory.
 * afterwards, calls the draw command that initialises all the rendermodes, ready for use.
 */
void init_rdp_and_framebuffer(Gfx **dList) {
    s32 width = GET_VIDEO_WIDTH(get_video_width_and_height_as_s32());
    gDPSetColorImage((*dList)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, SEGMENT_COLOUR_BUFFER);
    gDPSetDepthImage((*dList)++, SEGMENT_DEPTH_BUFFER);
    gSPDisplayList((*dList)++, dRdpInit);
}

/**
 * Calls the draw command that sets all the OtherModes, ready for use.
 * Official name: rcpInitSp or rcpInitDpNoSize
 */
void init_rsp(Gfx **dList) {
    gSPDisplayList((*dList)++, dRspInit);
}

/**
 * Initialise the mesg queues for the gfx tasks, that interface with the scheduler.
 */
void setup_gfx_mesg_queues(OSSched *sc) {
    osScInterruptQ = osScGetInterruptQ(sc);
    osCreateMesgQueue(&D_80125EA0, &D_80125EB8, 1);
    osCreateMesgQueue(&D_80125EC0, D_80125EF0, 8);
    osCreateMesgQueue(&gGfxTaskMesgQueue, gGfxTaskMesgBuf, 8);
}

//Called after finishing a race. Sets values during single player races. Set to zero during trophy races.
void func_80078170(TextureHeader *arg0, TextureHeader *arg1, u32 arg2) {
    D_800DE4C4 = arg0;
    D_800DE4C8 = arg1;
    D_800DE4C0 = arg2 << 2;
}

#ifdef NON_EQUIVALENT
//Seems to render the background screen after a race finishes while you're at the menu deciding what to do next.
//https://i.imgur.com/MHbUD2a.png is an example. The left is correct, and the right is incorrect rendering.
void func_80078190(Gfx **dlist) {
    s32 texture1And2UpperHeight;
    s32 videoHeight;
    s32 videoWidth;
    s32 upperVideoWidth;
    s32 upperVideoHeight;
    s32 texture1UpperWidth;
    s32 texture1UpperHeight;
    //s32 texture2UpperHeight;
    s32 widthAndHeight;
    s32 yPos;
    s32 var_s3;
    s32 uly; //the y-coordinate of upper-left corner of rectangle (10.2, 0.0~1023.75)
    s32 ulx; //the y-coordinate of upper-left corner of rectangle (10.2, 0.0~1023.75)
    s32 lry; //the y-coordinate of lower-right corner of rectangle (10.2, 0.0~1023.75)
    s32 lrx; //the x-coordinate of lower-right corner of rectangle (10.2, 0.0~1023.75)
    s32 t;   //the texture coordinate t of upper-left corner of rectangle (s10.5)
    s32 s;   //the texture coordinate s of upper-left corner of rectangle (s10.5)

    widthAndHeight = get_video_width_and_height_as_s32();
    videoWidth = GET_VIDEO_WIDTH(widthAndHeight);
    videoHeight = GET_VIDEO_HEIGHT(widthAndHeight);
    gSPDisplayList((*dlist)++, D_800DE598);

    if (D_800DE4C8 == NULL) {
        gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(D_800DE4C4->cmd), D_800DE4C4->numberOfCommands);
        upperVideoWidth = videoWidth << 2;
        upperVideoHeight = videoHeight << 2;
        texture1UpperWidth = D_800DE4C4->width << 2;
        texture1UpperHeight = D_800DE4C4->height << 2;
        var_s3 = 0;
        for (yPos = 0; yPos < upperVideoHeight; yPos += texture1UpperHeight) {
            uly = yPos;
            lry = yPos + texture1UpperHeight;
            ulx = -var_s3;
            while (ulx < upperVideoWidth) {
                lrx = ulx + texture1UpperWidth;
                s = 0;
                t = 0;
                if (ulx < 0) {
                    s = -(ulx << 3);
                    gSPTextureRectangle((*dlist)++, 0, uly, lrx, lry, G_TX_RENDERTILE, s, t, 1024, 1024);
                } else {
                    gSPTextureRectangle((*dlist)++, ulx, uly, lrx, lry, G_TX_RENDERTILE, s, t, 1024, 1024);
                }
                ulx = lrx;
            }
            var_s3 = (var_s3 + D_800DE4C0) & (texture1UpperWidth - 1);
        }
    } else {
        gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(D_800DE4C4->cmd), D_800DE4C4->numberOfCommands);
        upperVideoWidth = videoWidth << 2;
        upperVideoHeight = videoHeight << 2;
        texture1UpperWidth = D_800DE4C4->width << 2;
        texture1UpperHeight = D_800DE4C4->height << 2;
        //texture2UpperHeight = D_800DE4C8->height << 2;
        texture1And2UpperHeight = (D_800DE4C8->height << 2) + texture1UpperHeight;
        var_s3 = 0;
        for (yPos = 0; yPos < upperVideoHeight; yPos += texture1And2UpperHeight) {
            uly = yPos;
            lry = yPos + texture1UpperHeight;
            ulx = -var_s3;
            while (ulx < upperVideoWidth) {
                lrx = ulx + texture1UpperWidth;
                s = 0;
                t = 0;
                if (ulx < 0) {
                    s = -(ulx << 3);
                    gSPTextureRectangle((*dlist)++, 0, uly, lrx, lry, G_TX_RENDERTILE, s, t, 1024, 1024);
                } else {
                    gSPTextureRectangle((*dlist)++, ulx, uly, lrx, lry, G_TX_RENDERTILE, s, t, 1024, 1024);
                }
                ulx = lrx;
            }
            var_s3 = (var_s3 + D_800DE4C0) & (texture1UpperWidth - 1);
        }
        gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(D_800DE4C8->cmd), D_800DE4C8->numberOfCommands);
        upperVideoWidth <<= 2;
        upperVideoHeight <<= 2;
        var_s3 = 0;
        for (yPos = texture1UpperHeight; yPos < upperVideoHeight; yPos += texture1And2UpperHeight) {
            uly = yPos;
            lry = yPos + texture1And2UpperHeight;
            ulx = -var_s3;
            while (ulx < upperVideoWidth) {
                lrx = ulx + texture1UpperWidth;
                s = 0;
                t = 0;
                if (ulx < 0) {
                    s = -(ulx << 3);
                    gSPTextureRectangle((*dlist)++, 0, uly, lrx, lry, G_TX_RENDERTILE, s, t, 1024, 1024);
                } else {
                    gSPTextureRectangle((*dlist)++, ulx, uly, lrx, lry, G_TX_RENDERTILE, s, t, 1024, 1024);
                }
                ulx = lrx;
            }
            var_s3 = (var_s3 + D_800DE4C0) & (texture1UpperWidth - 1);
        }
    }
    gDPPipeSync((*dlist)++);
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80078190.s")
#endif

/**
 * Enables the chequer background and sets up its properties.
*/
UNUSED void set_chequer_background(s32 colourA, s32 colourB, s32 width, s32 height) {
    gChequerBGColourR1 = (colourA >> 24) & 0xFF;
    gChequerBGColourG1 = (colourA >> 16) & 0xFF;
    gChequerBGColourB1 = (colourA >> 8) & 0xFF;
    gChequerBGColourA1 = colourA & 0xFF;
    gChequerBGColourR2 = (colourB >> 24) & 0xFF;
    gChequerBGColourG2 = (colourB >> 16) & 0xFF;
    gChequerBGColourB2 = (colourB >> 8) & 0xFF;
    gChequerBGColourA2 = colourB & 0xFF;
    gChequerBGWidth = width;
    gChequerBGHeight = height;
    gChecquerBGEnabled = TRUE;
}

/**
 * Disables the chequer background.
*/
UNUSED void disable_chequer_background(void) {
    gChecquerBGEnabled = FALSE;
}

/**
 * Uses global chequerboard settings to render a background using two different alternating colours.
 * Goes unused.
*/
void render_chequer_background(Gfx **dList) {
    s32 height;
    s32 width;
    s32 flip; // Flips between 0 and 1
    s32 y;
    s32 x;

    width = get_video_width_and_height_as_s32();
    height = GET_VIDEO_HEIGHT(width) & 0xFFFF;
    width = GET_VIDEO_WIDTH(width);
    
    gSPDisplayList((*dList)++, dChequerBGSettings);
    gDPSetPrimColor((*dList)++, 0, 0, gChequerBGColourR1, gChequerBGColourG1, gChequerBGColourB1, gChequerBGColourA1);

    for (y = 0, flip = 0; y < height; y += gChequerBGHeight, flip ^= 1) {
        for (x = flip * gChequerBGWidth; x < width; x += gChequerBGWidth * 2) {
            gDPFillRectangle((*dList)++, x, y, x + gChequerBGWidth, y + gChequerBGHeight);            
        }
    }
    
    gDPSetPrimColor((*dList)++, 0, 0, gChequerBGColourR2, gChequerBGColourG2, gChequerBGColourB2, gChequerBGColourA2);
    
    for (y = 0, flip = 1; y < height; y += gChequerBGHeight, flip ^= 1) {
        for (x = flip * gChequerBGWidth; x < width; x += gChequerBGWidth * 2) {
            gDPFillRectangle((*dList)++, x, y, x + gChequerBGWidth, y + gChequerBGHeight);            
        }
    }
    
    gDPPipeSync((*dList)++);
}

/**
 * Sets the function pointer to whatever's passed through.
 * If nonzero, will override the background drawing section.
*/
void set_background_draw_function(void *func) {
    gBackgroundDrawFunc.ptr = func;
}

/**
 * Renders one or more textures directly on screen resulting from the passed image properties.
 * Texture rectangle coordinates use 10.2 precision and texture coords use 10.5 precision.
 * Typically, you do these shifts in the draw call itself, but Rare decided to do it beforehand.
*/
void render_textured_rectangle(Gfx **dList, DrawTexture *element, s32 xPos, s32 yPos, u8 red, u8 green, u8 blue, u8 alpha) {
    TextureHeader *tex;
    s32 i;
    s32 uly;
    s32 ulx;
    s32 lry;
    s32 lrx;
    s32 t;
    s32 s;

    gSPDisplayList((*dList)++, dTextureRectangleModes);
    gDPSetPrimColor((*dList)++, 0, 0, red, green, blue, alpha); 
    xPos <<= 2;
    yPos <<= 2;
    for (i = 0; (tex = element[i].texture); i++) {
        ulx = (element[i].xOffset << 2) + xPos;
        uly = (element[i].yOffset << 2) + yPos;
        lrx = (tex->width << 2) + ulx;
        lry = (tex->height << 2) + uly;
        if (lrx > 0 && lry > 0) {
            s = 0;
            t = 0;
            if (ulx < 0) {
                s = -(ulx << 3);
                ulx = 0;
            }
            if (uly < 0) {
                t = -(uly << 3);
                uly = 0;
            }
            gDkrDmaDisplayList((*dList)++, OS_PHYSICAL_TO_K0(tex->cmd), tex->numberOfCommands);
            gSPTextureRectangle((*dList)++, ulx, uly, lrx, lry, G_TX_RENDERTILE, s, t, 1024, 1024);
        }
    }
    gDPPipeSync((*dList)++);
    gDPSetPrimColor((*dList)++, 0, 0, 255, 255, 255, 255);
}

void render_texture_rectangle_scaled(Gfx **dlist, DrawTexture *element, f32 xPos, f32 yPos, f32 xScale, f32 yScale, u32 colour, s32 flags) {
    TextureHeader *tex;
    Gfx *dmaDlist;
    s32 i;
    s32 bFlipX;
    s32 bFlipY;
    s32 s;   //the texture coordinate s of upper-left corner of rectangle (s10.5)
    s32 t;   //the texture coordinate t of upper-left corner of rectangle (s10.5)
    s32 dsdx;//the change in s for each change in x (s5.10)
    s32 dtdy;//the change in t for each change in y (s5.10)
    s32 ulx; //the y-coordinate of upper-left corner of rectangle (10.2, 0.0~1023.75)
    s32 uly; //the y-coordinate of upper-left corner of rectangle (10.2, 0.0~1023.75)
    s32 lrx; //the x-coordinate of lower-right corner of rectangle (10.2, 0.0~1023.75)
    s32 lry; //the y-coordinate of lower-right corner of rectangle (10.2, 0.0~1023.75)
    s32 xPos4x;
    s32 yPos4x;
    s32 width;
    s32 height;

    height = get_video_width_and_height_as_s32();
    width = GET_VIDEO_WIDTH(height) * 4;
    height = (GET_VIDEO_HEIGHT(height) & 0xFFFF) * 4;

    //If the colour is fully opaque
    if ((colour & 0xFF) == 0xFF) {
        dmaDlist = dTextureRectangleScaledOpa[(u8)flags & 0xFF];
    } else {
        dmaDlist = dTextureRectangleScaledXlu[(u8)flags & 0xFF];
    }

    gSPDisplayList((*dlist)++, D_800DE670);
    gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(dmaDlist), numberOfGfxCommands(dTextureRectangleScaledOpa[0]));
    gDPSetPrimColorRGBA((*dlist)++, colour);

    bFlipX = flags & (1 << 12);
    bFlipY = flags & (1 << 13);
    xScale *= 4;
    yScale *= 4;
    xPos4x = xPos * 4;
    yPos4x = yPos * 4;

    for (i = 0; (tex = element[i].texture); i++) {
        if (!bFlipX) {
            ulx = (s32) (element[i].xOffset * xScale) + xPos4x;
        } else {
            lrx = xPos4x - (s32) (element[i].xOffset * xScale);
            ulx = lrx - (s32) (tex->width * xScale);
        }
        if (!bFlipY) {
            uly = (s32) (element[i].yOffset * yScale) + yPos4x;
        } else {
            lry = yPos4x - (s32) (element[i].yOffset * yScale);
            uly = lry - (s32) (tex->height * yScale);
        }
        if (ulx < width && uly < height) {
            if (!bFlipX) {
                lrx = (s32) (tex->width * xScale) + ulx;
            }
            if (!bFlipY) {
                lry = (s32) (tex->height * yScale) + uly;
            }
            if (lrx > 0 && lry > 0 && ulx < lrx && uly < lry) {
                dsdx = ((tex->width - 1) << 12) / (lrx - ulx);
                if (bFlipX) {
                    s = (tex->width - 1) << 5;
                    dsdx = -dsdx;
                } else {
                    s = 0;
                }
                dtdy = ((tex->height - 1) << 12) / (lry - uly);
                if (bFlipY) {
                    t = (tex->height - 1) << 5;
                    dtdy = -dtdy;
                } else {
                    t = 0;
                }
                if (ulx < 0) {
                    s += (-ulx * dsdx) >> 7;
                    ulx = 0;
                }
                if (uly < 0) {
                    t += (-uly * dtdy) >> 7;
                    uly = 0;
                }

                gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(tex->cmd), tex->numberOfCommands);
                gSPTextureRectangle((*dlist)++, ulx, uly, lrx, lry, G_TX_RENDERTILE, s, t, dsdx, dtdy);
            }
        }
    }

    gDPPipeSync((*dlist)++);
    gDPSetPrimColor((*dlist)++, 0, 0, 255, 255, 255, 255);
}
