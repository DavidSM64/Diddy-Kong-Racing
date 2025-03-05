/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80077450 */

#include "rcp_dkr.h"
#include "types.h"
#include "structs.h"
#include "macros.h"
#include "video.h"
#include "camera.h"
#include "set_rsp_segment.h"
// #include "libultra/src/unknown_0D24D0.h"

/************ .data ************/

s16 gGfxTaskMesgNums[16] = { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

u8 sBGPrimColourrR = 0;
u8 sBGPrimColourrG = 0;
u8 sBGPrimColourrB = 0;
s32 sBackgroundFillColour = GPACK_RGBA5551(0, 0, 0, 1) | (GPACK_RGBA5551(0, 0, 0, 1) << 16);

u32 gTexBGShiftX = 64;
TextureHeader *gTexBGTex1 = NULL;
TextureHeader *gTexBGTex2 = NULL;
s32 gChequerBGEnabled = FALSE;

BackgroundFunction gBGDrawFunc = { NULL };
s32 gGfxBufCounter = 0;
s32 gGfxBufCounter2 = 0;
s32 gGfxTaskIsRunning = FALSE;

Gfx dRspInit[] = {
    gsSPClearGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_CULL_FRONT | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                          G_TEXTURE_GEN_LINEAR | G_LOD),
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
    gsDPPipeSync(), // Why are we randomly pipesyncing in the middle of setting RDP states?
    gsSPEndDisplayList(),
};

Gfx dRaceFinishBackgroundSettings[] = {
    gsDPPipeSync(),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPClearGeometryMode(G_ZBUFFER | G_FOG),
    gsDPPipeSync(), // And here?
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
    gsDPPipeSync(), // Ditto
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
    gsDPPipeSync(), // Ditto
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetOtherMode(DKR_OMH_1CYC_POINT_NOPERSP, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx dScaledRectangleBaseModes[] = {
    gsDPPipeSync(),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPClearGeometryMode(G_ZBUFFER | G_FOG),
    gsDPPipeSync(), // Ditto
    gsSPEndDisplayList(),
};

Gfx dTextureRectangleScaledOpa[][2] = {
    // Bilinear Filtered texture
    DRAW_TABLE_ENTRY(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_BILERP_NOPERSP, G_RM_AA_OPA_SURF,
                     G_RM_AA_OPA_SURF2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_BILERP_NOPERSP, G_RM_OPA_SURF,
                     G_RM_OPA_SURF2),
    // Point Sampled texture
    DRAW_TABLE_ENTRY(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_POINT_NOPERSP, G_RM_AA_OPA_SURF,
                     G_RM_AA_OPA_SURF2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_POINT_NOPERSP, G_RM_OPA_SURF,
                     G_RM_OPA_SURF2)
};

Gfx dTextureRectangleScaledXlu[][2] = {
    // Bilinear Filtered texture
    DRAW_TABLE_ENTRY(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_BILERP_NOPERSP, G_RM_AA_XLU_SURF,
                     G_RM_AA_XLU_SURF2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_BILERP_NOPERSP, G_RM_XLU_SURF,
                     G_RM_XLU_SURF2),
    // Point Sampled texture
    DRAW_TABLE_ENTRY(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_POINT_NOPERSP, G_RM_AA_XLU_SURF,
                     G_RM_AA_XLU_SURF2),
    DRAW_TABLE_ENTRY(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM, DKR_OMH_1CYC_POINT_NOPERSP, G_RM_XLU_SURF,
                     G_RM_XLU_SURF2)
};

/*******************************/

/************ .bss ************/

u8 gDramStack[SP_DRAM_STACK_SIZE8];
u8 gGfxTaskOutputBuffer[OUTPUT_BUFFER_SIZE];
OSMesgQueue gRCPMesgQueue;
OSMesg gRCPMesgBuf;
UNUSED OSMesgQueue gUnusedMesgQueue;
OSMesgQueue gGfxTaskMesgQueue;
UNUSED OSMesg gUnusedMesgBuf[8];
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
s32 gfxtask_run_xbus(Gfx *dlBegin, Gfx *dlEnd, UNUSED s32 recvMesg) {
    DKR_OSTask *dkrtask;

    gGfxTaskIsRunning = TRUE;
    dkrtask = &gGfxTaskBuf[gGfxBufCounter];
    gGfxBufCounter++;
    if (gGfxBufCounter == 2) {
        gGfxBufCounter = 0;
    }
    dkrtask->flags = OS_SC_LAST_TASK | OS_SC_NEEDS_RDP | OS_SC_NEEDS_RSP;
    dkrtask->mesgQueue = &gGfxTaskMesgQueue;
    dkrtask->unused58 = COLOUR_TAG_RED;
    dkrtask->unused5C = COLOUR_TAG_RED;
    dkrtask->task.data_ptr = (u64 *) dlBegin;
    dkrtask->task.data_size = ((s32) dlEnd - (s32) dlBegin) >> 3; // Shifted by 3, repsenting the size of the Gfx type.
    dkrtask->task.type = M_GFXTASK;
    dkrtask->task.flags = OS_TASK_DP_WAIT;
    dkrtask->task.ucode_boot = (u64 *) rspF3DDKRBootStart;
    dkrtask->task.ucode_boot_size = (s32) (rspF3DDKRDramStart - rspF3DDKRBootStart);
    dkrtask->task.ucode = (u64 *) rspF3DDKRXbusStart;
    dkrtask->task.ucode_data = (u64 *) rspF3DDKRDataXbusStart;
    dkrtask->task.ucode_data_size = SP_UCODE_DATA_SIZE;
    dkrtask->task.dram_stack = (u64 *) gDramStack;
    dkrtask->task.dram_stack_size = SP_DRAM_STACK_SIZE8;
    dkrtask->task.output_buff = (u64 *) gGfxTaskOutputBuffer;
    dkrtask->task.output_buff_size = (u64 *) &gRCPMesgQueue;
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
UNUSED void gfxtask_run_xbus2(Gfx *dlBegin, Gfx *dlEnd, s32 recvMesg) {
    DKR_OSTask *dkrtask;
    OSMesg mesgBuf;

    mesgBuf = NULL;
    dkrtask = &gGfxTaskBuf2[gGfxBufCounter2];
    gGfxBufCounter2++;
    if (gGfxBufCounter2 == 2) {
        gGfxBufCounter2 = 0;
    }
    dkrtask->task.data_ptr = (u64 *) dlBegin;
    dkrtask->task.data_size = (s32) (dlEnd - dlBegin) * sizeof(Gfx);
    dkrtask->task.type = M_GFXTASK;
    dkrtask->task.flags = OS_TASK_DP_WAIT;
    dkrtask->task.ucode_boot = (u64 *) rspF3DDKRBootStart;
    dkrtask->task.ucode_boot_size = (s32) (rspF3DDKRDramStart - rspF3DDKRBootStart);
    dkrtask->task.ucode = (u64 *) rspF3DDKRXbusStart;
    dkrtask->task.ucode_data = (u64 *) rspF3DDKRDataXbusStart;
    dkrtask->task.ucode_data_size = SP_UCODE_DATA_SIZE;
    dkrtask->task.dram_stack = (u64 *) gDramStack;
    dkrtask->task.dram_stack_size = SP_DRAM_STACK_SIZE8;
    dkrtask->task.yield_data_ptr = (u64 *) gGfxTaskYieldData;
    dkrtask->task.yield_data_size = sizeof(gGfxTaskYieldData);
    dkrtask->task.output_buff = NULL;
    dkrtask->task.output_buff_size = 0;
    dkrtask->next = NULL;
    dkrtask->flags = OS_SC_NEEDS_RDP | OS_SC_NEEDS_RSP;
    dkrtask->mesgQueue = &gGfxTaskMesgQueue;
    dkrtask->mesg = &gGfxTaskMesgNums[0];
    dkrtask->frameBuffer = gVideoCurrFramebuffer;
    dkrtask->unused58 = COLOUR_TAG_RED;
    dkrtask->unused5C = COLOUR_TAG_RED;
    dkrtask->unused60 = 0xFF;
    dkrtask->unused64 = 0xFF;
    dkrtask->unk68 = FALSE;

    if (recvMesg) {
        dkrtask->mesgQueue = &gRCPMesgQueue;
    }
    osWritebackDCacheAll();
    osSendMesg(osScInterruptQ, dkrtask, 1);
    if (recvMesg) {
        osRecvMesg(&gRCPMesgQueue, &mesgBuf, OS_MESG_BLOCK);
    }
}

/**
 *
 * Prepare the gfx task for the F3DDKR FIFO microcode.
 * Sends a message to the scheduler to start processing an RSP task once set up.
 * Goes unused, and is broken.
 */
UNUSED void gfxtask_run_fifo(Gfx *dlBegin, Gfx *dlEnd, s32 recvMesg) {
    DKR_OSTask *dkrtask;
    OSMesg mesgBuf;

    mesgBuf = NULL;
    dkrtask = &gGfxTaskBuf2[gGfxBufCounter2];
    gGfxBufCounter2++;
    if (gGfxBufCounter2 == 2) {
        gGfxBufCounter2 = 0;
    }

    dkrtask->task.data_ptr = (u64 *) dlBegin;
    dkrtask->task.ucode_boot = (u64 *) rspF3DDKRBootStart;
    dkrtask->task.data_size = (s32) (dlEnd - dlBegin) * sizeof(Gfx);
    dkrtask->task.type = M_GFXTASK;
    dkrtask->task.flags = OS_TASK_DP_WAIT;
    dkrtask->task.ucode_boot_size = (s32) (rspF3DDKRDramStart - rspF3DDKRBootStart);
    dkrtask->task.ucode = (u64 *) rspF3DDKRFifoStart;
    dkrtask->task.ucode_data = (u64 *) rspF3DDKRDataFifoStart;
    dkrtask->task.ucode_data_size = SP_UCODE_DATA_SIZE;
    dkrtask->task.dram_stack = (u64 *) gDramStack;
    dkrtask->task.dram_stack_size = SP_DRAM_STACK_SIZE8;
    dkrtask->task.output_buff = (u64 *) gGfxTaskOutputBuffer;
    dkrtask->task.output_buff_size = (u64 *) (gGfxTaskOutputBuffer + OUTPUT_BUFFER_SIZE);
    dkrtask->task.yield_data_ptr = (u64 *) gGfxTaskYieldData;
    dkrtask->task.yield_data_size = sizeof(gGfxTaskYieldData);
    dkrtask->next = NULL;
    dkrtask->flags = OS_SC_NEEDS_RDP | OS_SC_NEEDS_RSP | OS_SC_DRAM_DLIST;
    dkrtask->mesgQueue = &gGfxTaskMesgQueue;
    dkrtask->mesg = &gGfxTaskMesgNums[0];
    dkrtask->frameBuffer = gVideoCurrFramebuffer;
    dkrtask->unused58 = COLOUR_TAG_RED;
    dkrtask->unused5C = COLOUR_TAG_RED;
    dkrtask->unused60 = COLOUR_TAG_BLACK;
    dkrtask->unused64 = COLOUR_TAG_BLACK;
    dkrtask->unk68 = FALSE;

    if (recvMesg) {
        dkrtask->mesgQueue = &gRCPMesgQueue;
    }
    osWritebackDCacheAll();
    osSendMesg(osScInterruptQ, dkrtask, 1);

    if (recvMesg) {
        osRecvMesg(&gRCPMesgQueue, &mesgBuf, OS_MESG_BLOCK);
    }
}

/**
 * Unused variant of the FIFO task function.
 * Probably intended to be a secondary task system, since it doesn't set the var saying there's a task running.
 */
UNUSED void gfxtask_run_fifo2(Gfx *dlBegin, Gfx *dlEnd, s32 recvMesg) {
    DKR_OSTask *dkrtask;
    OSMesg mesgBuf;

    mesgBuf = NULL;
    dkrtask = &gGfxTaskBuf[gGfxBufCounter];
    gGfxBufCounter++;
    //!@bug - gGfxBufCounter being 2 would mean an out of bounds access of gGfxTaskBuf
    if (gGfxBufCounter == 3) {
        gGfxBufCounter = 0;
    }

    dkrtask->task.data_size = (s32) (dlEnd - dlBegin) * sizeof(Gfx);
    dkrtask->task.data_ptr = (u64 *) dlBegin;
    dkrtask->task.type = M_GFXTASK;
    dkrtask->task.flags = OS_TASK_DP_WAIT;
    dkrtask->task.ucode_boot = (u64 *) rspF3DDKRBootStart;
    dkrtask->task.ucode_boot_size = (s32) (rspF3DDKRDramStart - rspF3DDKRBootStart);
    dkrtask->task.ucode = (u64 *) rspF3DDKRFifoStart;
    dkrtask->task.ucode_data = (u64 *) rspF3DDKRDataFifoStart;
    dkrtask->task.ucode_data_size = SP_UCODE_DATA_SIZE;
    dkrtask->task.dram_stack = (u64 *) gDramStack;
    dkrtask->task.dram_stack_size = SP_DRAM_STACK_SIZE8;
    dkrtask->task.output_buff = (u64 *) gGfxTaskOutputBuffer;
    dkrtask->task.output_buff_size = (u64 *) &gRCPMesgQueue;
    dkrtask->task.yield_data_ptr = (u64 *) gGfxTaskYieldData;
    dkrtask->task.yield_data_size = sizeof(gGfxTaskYieldData);
    dkrtask->next = NULL;
    dkrtask->flags = OS_SC_NEEDS_RDP | OS_SC_NEEDS_RSP | OS_SC_DRAM_DLIST;
    dkrtask->mesgQueue = &gGfxTaskMesgQueue;
    dkrtask->mesg = &gGfxTaskMesgNums[0];
    dkrtask->frameBuffer = gVideoCurrFramebuffer;
    dkrtask->unused58 = COLOUR_TAG_RED;
    dkrtask->unused5C = COLOUR_TAG_RED;
    if (recvMesg) {
        dkrtask->unused60 = COLOUR_TAG_BLACK;
        dkrtask->unused64 = COLOUR_TAG_BLACK;
    }
    dkrtask->unk68 = FALSE;
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
 * Official Name: rcpWaitDP
 */
s32 gfxtask_wait(void) {
    OSMesg *mesg = NULL;
    if (gGfxTaskIsRunning == FALSE) {
        return 0;
    }
    osRecvMesg(&gGfxTaskMesgQueue, (OSMesg) &mesg, OS_MESG_BLOCK);
    gGfxTaskIsRunning = FALSE;
    return (s32) mesg[1];
}

/**
 * Write Data Cache back into RAM and then execute an RDP task with a given command buffer.
 * This function skips the RSP, so it takes in raw RDP commands.
 */
UNUSED void gfxtask_run_rdp(void *bufPtr, s32 bufSize, UNUSED s32 unused) {
    osWritebackDCacheAll();
    while (osDpGetStatus() & DPC_CLR_CMD_CTR) {}
    osDpSetNextBuffer(bufPtr, bufSize);
    while (osDpGetStatus() & DPC_CLR_CMD_CTR) {}
}

/**
 * Sets the primitive colour for the cyclemode fillrect background.
 * Official name: rcpSetScreenColour
 */
void bgdraw_primcolour(u8 red, u8 green, u8 blue) {
    sBGPrimColourrR = red;
    sBGPrimColourrG = green;
    sBGPrimColourrB = blue;
}

/**
 * Sets the fill colour for the fillmode fillrect background.
 * Uses RGBA5551
 * Official name: rcpSetBorderColour
 */
void bgdraw_fillcolour(s32 red, s32 green, s32 blue) {
    sBackgroundFillColour = GPACK_RGBA5551(red, green, blue, 1);
    sBackgroundFillColour |= (sBackgroundFillColour << 16);
}

/**
 * Clears the ZBuffer first, then decides how to draw the background which goes directly
 * over the colour buffer. DrawBG if set to 0 (which never happens) will completely skip
 * over clearing the colour buffer.
 * Official Name: rcpClearScreen
 */
void bgdraw_render(Gfx **dList, Matrix *mtx, s32 drawBG) {
    s32 widthAndHeight;
    s32 w;
    s32 h;
    s32 x1;
    s32 y1;
    s32 x2;
    s32 y2;

    widthAndHeight = fb_size();
    w = GET_VIDEO_WIDTH(widthAndHeight);
    h = GET_VIDEO_HEIGHT(widthAndHeight);

    gDPPipeSync((*dList)++);
    //!@bug: the scissor does not need the off by one here, despite being intended for fill mode.
    gDPSetScissor((*dList)++, 0, 0, 0, w - 1, h - 1);
    gDPSetCycleType((*dList)++, G_CYC_FILL);
    gDPSetColorImage((*dList)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, w, SEGMENT_ZBUFFER << 24);
    gDPSetFillColor((*dList)++, GPACK_RGBA5551(255, 255, 240, 0) << 16 | GPACK_RGBA5551(255, 255, 240, 0));
    gDPFillRectangle((*dList)++, 0, 0, w - 1, h - 1);
    gDPPipeSync((*dList)++);
    gDPSetColorImage((*dList)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, w, SEGMENT_FRAMEBUFFER << 24);
    if (drawBG) {
        if (check_viewport_background_flag(0)) {
            if (gChequerBGEnabled) {
                bgdraw_chequer(dList); // Unused
            } else if (gTexBGTex1) {
                func_80078190(dList);
            } else if (gBGDrawFunc.ptr != NULL) {
                gBGDrawFunc.function((Gfx *) dList, mtx);
            } else {
                gDPSetFillColor((*dList)++, sBackgroundFillColour);
                gDPFillRectangle((*dList)++, 0, 0, w - 1, h - 1);
            }
            // Used for secondary viewport backgrounds. This does not need to be 1 cycle, this could easily work with
            // fillmode.
            if (copy_viewport_background_size_to_coords(0, &x1, &y1, &x2, &y2)) {
                gDPSetCycleType((*dList)++, G_CYC_1CYCLE);
                gDPSetPrimColor((*dList)++, 0, 0, sBGPrimColourrR, sBGPrimColourrG, sBGPrimColourrB, 255);
                gDPSetCombineMode((*dList)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
                gDPSetRenderMode((*dList)++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
                gDPFillRectangle((*dList)++, x1, y1, x2, y2);
            }
        } else {
            if (gChequerBGEnabled) {
                bgdraw_chequer(dList); // Unused
            } else if (gTexBGTex1) {
                func_80078190(dList);
            } else if (gBGDrawFunc.ptr != NULL) {
                gBGDrawFunc.function((Gfx *) dList, mtx);
            } else {
                gDPSetFillColor((*dList)++,
                                (GPACK_RGBA5551(sBGPrimColourrR, sBGPrimColourrG, sBGPrimColourrB, 1) << 16) |
                                    GPACK_RGBA5551(sBGPrimColourrR, sBGPrimColourrG, sBGPrimColourrB, 1));
                gDPFillRectangle((*dList)++, 0, 0, w - 1, h - 1);
            }
        }
    }
    gDPPipeSync((*dList)++);
    viewport_scissor(dList);
}

/**
 * Gets the framebuffer width, then points to the start of segment 0x01 in memory.
 * afterwards, calls the draw command that initialises all the rendermodes, ready for use.
 */
void rdp_init(Gfx **dList) {
    s32 width = GET_VIDEO_WIDTH(fb_size());
    gDPSetColorImage((*dList)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, SEGMENT_FRAMEBUFFER << 24);
    gDPSetDepthImage((*dList)++, SEGMENT_ZBUFFER << 24);
    gSPDisplayList((*dList)++, dRdpInit);
}

/**
 * Calls the draw command that sets all the OtherModes, ready for use.
 * Official name: rcpInitSp or rcpInitDpNoSize
 */
void rsp_init(Gfx **dList) {
    gSPDisplayList((*dList)++, dRspInit);
}

/**
 * Initialise the mesg queues for the gfx tasks, that interface with the scheduler.
 */
void gfxtask_init(OSSched *sc) {
    osScInterruptQ = osScGetInterruptQ(sc);
    osCreateMesgQueue(&gRCPMesgQueue, &gRCPMesgBuf, 1);
    osCreateMesgQueue(&gUnusedMesgQueue, gUnusedMesgBuf, ARRAY_COUNT(gUnusedMesgBuf));
    osCreateMesgQueue(&gGfxTaskMesgQueue, gGfxTaskMesgBuf, ARRAY_COUNT(gGfxTaskMesgBuf));
}

/**
 * Set one or two textures for the patterned world themed background.
 * Can also apply a shift to make tiling less obvious.
 */
void bgdraw_texture_init(TextureHeader *tex1, TextureHeader *tex2, u32 shiftX) {
    gTexBGTex1 = tex1;
    gTexBGTex2 = tex2;
    gTexBGShiftX = shiftX * 4;
}

// bgdraw_texture
#ifdef NON_EQUIVALENT
/**
 * Seems to render the background screen after a race finishes while you're at the menu deciding what to do next.
 * https://i.imgur.com/MHbUD2a.png is an example. The left is correct, and the right is incorrect rendering.
 * Official Name: rcpMosaicClear
 */
void func_80078190(Gfx **dlist) {
    s32 texture1And2UpperHeight;
    s32 videoHeight;
    s32 videoWidth;
    s32 upperVideoWidth;
    s32 upperVideoHeight;
    s32 texture1UpperWidth;
    s32 texture1UpperHeight;
    // s32 texture2UpperHeight;
    s32 widthAndHeight;
    s32 yPos;
    s32 var_s3;
    s32 uly; // the y-coordinate of upper-left corner of rectangle (10.2, 0.0~1023.75)
    s32 ulx; // the y-coordinate of upper-left corner of rectangle (10.2, 0.0~1023.75)
    s32 lry; // the y-coordinate of lower-right corner of rectangle (10.2, 0.0~1023.75)
    s32 lrx; // the x-coordinate of lower-right corner of rectangle (10.2, 0.0~1023.75)
    s32 t;   // the texture coordinate t of upper-left corner of rectangle (s10.5)
    s32 s;   // the texture coordinate s of upper-left corner of rectangle (s10.5)

    widthAndHeight = fb_size();
    videoWidth = GET_VIDEO_WIDTH(widthAndHeight);
    videoHeight = GET_VIDEO_HEIGHT(widthAndHeight);
    gSPDisplayList((*dlist)++, dRaceFinishBackgroundSettings);

    if (gTexBGTex2 == NULL) {
        gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(gTexBGTex1->cmd), gTexBGTex1->numberOfCommands);
        upperVideoWidth = videoWidth << 2;
        upperVideoHeight = videoHeight << 2;
        texture1UpperWidth = gTexBGTex1->width << 2;
        texture1UpperHeight = gTexBGTex1->height << 2;
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
            var_s3 = (var_s3 + gTexBGShiftX) & (texture1UpperWidth - 1);
        }
    } else {
        gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(gTexBGTex1->cmd), gTexBGTex1->numberOfCommands);
        upperVideoWidth = videoWidth << 2;
        upperVideoHeight = videoHeight << 2;
        texture1UpperWidth = gTexBGTex1->width << 2;
        texture1UpperHeight = gTexBGTex1->height << 2;
        // texture2UpperHeight = gTexBGTex2->height << 2;
        texture1And2UpperHeight = (gTexBGTex2->height << 2) + texture1UpperHeight;
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
            var_s3 = (var_s3 + gTexBGShiftX) & (texture1UpperWidth - 1);
        }
        gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(gTexBGTex2->cmd), gTexBGTex2->numberOfCommands);
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
            var_s3 = (var_s3 + gTexBGShiftX) & (texture1UpperWidth - 1);
        }
    }
    gDPPipeSync((*dlist)++);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/rcp_dkr/func_80078190.s")
#endif

/**
 * Enables the chequer background and sets up its properties.
 */
UNUSED void bgdraw_chequer_on(s32 colourA, s32 colourB, s32 width, s32 height) {
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
    gChequerBGEnabled = TRUE;
}

/**
 * Disables the chequer background.
 */
UNUSED void bgdraw_chequer_off(void) {
    gChequerBGEnabled = FALSE;
}

/**
 * Uses global chequerboard settings to render a background using two different alternating colours.
 * Goes unused.
 * Official Name: rcpCheckClear
 */
void bgdraw_chequer(Gfx **dList) {
    s32 height;
    s32 width;
    s32 flip; // Flips between 0 and 1
    s32 y;
    s32 x;

    width = fb_size();
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
void bgdraw_set_func(void *func) {
    gBGDrawFunc.ptr = func;
}

/**
 * Renders one or more textures directly on screen resulting from the passed image properties.
 * Texture rectangle coordinates use 10.2 precision and texture coords use 10.5 precision.
 * Typically, you do these shifts in the draw call itself, but Rare decided to do it beforehand.
 */
void texrect_draw(Gfx **dList, DrawTexture *element, s32 xPos, s32 yPos, u8 red, u8 green, u8 blue, u8 alpha) {
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

/**
 * Renders one or more textures directly on screen resulting from the passed image properties.
 * Texture rectangle coordinates use 10.2 precision and texture coords use 10.5 precision.
 * Typically, you do these shifts in the draw call itself, but Rare decided to do it beforehand.
 * Also applies texel shifting in order to apply scaling.
 */
void texrect_draw_scaled(Gfx **dlist, DrawTexture *element, f32 xPos, f32 yPos, f32 xScale, f32 yScale, u32 colour,
                         s32 flags) {
    TextureHeader *tex;
    Gfx *dmaDlist;
    s32 i;
    s32 bFlipX;
    s32 bFlipY;
    s32 s;    // the texture coordinate s of upper-left corner of rectangle (s10.5)
    s32 t;    // the texture coordinate t of upper-left corner of rectangle (s10.5)
    s32 dsdx; // the change in s for each change in x (s5.10)
    s32 dtdy; // the change in t for each change in y (s5.10)
    s32 ulx;  // the y-coordinate of upper-left corner of rectangle (10.2, 0.0~1023.75)
    s32 uly;  // the y-coordinate of upper-left corner of rectangle (10.2, 0.0~1023.75)
    s32 lrx;  // the x-coordinate of lower-right corner of rectangle (10.2, 0.0~1023.75)
    s32 lry;  // the y-coordinate of lower-right corner of rectangle (10.2, 0.0~1023.75)
    s32 xPos4x;
    s32 yPos4x;
    s32 width;
    s32 height;

    height = fb_size();
    width = GET_VIDEO_WIDTH(height) * 4;
    height = (GET_VIDEO_HEIGHT(height) & 0xFFFF) * 4;

    // If the colour is fully opaque
    if ((colour & 0xFF) == 0xFF) {
        dmaDlist = dTextureRectangleScaledOpa[(u8) flags & 0xFF];
    } else {
        dmaDlist = dTextureRectangleScaledXlu[(u8) flags & 0xFF];
    }

    gSPDisplayList((*dlist)++, dScaledRectangleBaseModes);
    gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(dmaDlist), numberOfGfxCommands(dTextureRectangleScaledOpa[0]));
    gDPSetPrimColorRGBA((*dlist)++, colour);

    bFlipX = flags & TEXRECT_FLIP_X;
    bFlipY = flags & TEXRECT_FLIP_Y;
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
