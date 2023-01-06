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
s32 D_800DE4CC = 0;

unk800DE4D0 gBackgroundDrawFunc = { NULL };
s32 gfxBufCounter = 0;
s32 gfxBufCounter2 = 0;
s32 gGfxTaskIsRunning = FALSE;
u64 *gGfxSPTaskOutputBuffer = NULL; 

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
    gsDPPipelineMode(G_PM_NPRIMITIVE),
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

#define YIELD_BUFFER_SIZE 1

u8 gDramStack[SP_DRAM_STACK_SIZE8];
u8 gGfxSPTaskYieldBuffer[YIELD_BUFFER_SIZE];
OSMesgQueue D_80125EA0;
OSMesg D_80125EB8;
OSMesgQueue D_80125EC0;
OSMesgQueue gGfxTaskMesgQueue;
OSMesg D_80125EF0[8];
OSMesg gGfxTaskMesgBuf[8];
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

DKR_OSTask gGfxTaskBuf[2];
DKR_OSTask gGfxTaskBuf2[2];

OSMesgQueue *osScInterruptQ;

/*******************************/

/**
 * Prepare the gfx task for the F3DDKR XBus microcode.
 * Sends a message to the scheduler to start processing an RSP task once set up.
 */
s32 setup_ostask_xbus(Gfx* dlBegin, Gfx* dlEnd, UNUSED s32 recvMesg) {
    DKR_OSTask *dkrtask;

    gGfxTaskIsRunning = TRUE;
    dkrtask = &gGfxTaskBuf[gfxBufCounter];
    gfxBufCounter++;
    if (gfxBufCounter == 2) {
        gfxBufCounter = 0;
    }
    dkrtask->flags = OS_SC_LAST_TASK | OS_SC_SWAPBUFFER | OS_SC_NEEDS_RDP | OS_SC_NEEDS_RSP;
    dkrtask->mesgQueue = &gGfxTaskMesgQueue;
    dkrtask->unused58 = COLOUR_TAG_RED;
    dkrtask->unused5C = COLOUR_TAG_RED;
    dkrtask->task.data_ptr = (u64 *) dlBegin;
    dkrtask->task.data_size = ((s32) dlEnd - (s32) dlBegin) >> 3; // Shifted by 3, repsenting the size of the Gfx type.
    dkrtask->task.type = 1;
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
    osSendMesg(osScInterruptQ, dkrtask, 1);
    return 0;
}

void allocate_task_buffer(void) {
    gGfxSPTaskOutputBuffer = allocate_from_main_pool_safe(sizeof(u64) * FIFO_BUFFER_SIZE, COLOUR_TAG_WHITE);
}

/**
 * 
 * Prepare the gfx task for the F3DDKR FIFO microcode.
 * Sends a message to the scheduler to start processing an RSP task once set up.
 * Goes unused, and is broken.
 */
void setup_ostask_fifo(Gfx* dlBegin, Gfx* dlEnd, s32 recvMesg) {
    DKR_OSTask *dkrtask;
    s32 *mesgBuf;

    gGfxTaskIsRunning = TRUE;
    dkrtask = &gGfxTaskBuf[gfxBufCounter];
    gfxBufCounter ^= 1;

    if (gGfxSPTaskOutputBuffer == NULL) {
        allocate_task_buffer();
    }
    
    dkrtask->task.data_ptr = (u64 *) dlBegin;
    dkrtask->task.ucode_boot = (u64 *) rspF3DDKRBootStart;
    dkrtask->task.data_size = (s32) (dlEnd - dlBegin) * sizeof(Gfx);
    dkrtask->task.type = 1;
    dkrtask->task.flags = 0;
    dkrtask->task.ucode_boot_size = (s32) (rspF3DDKRDramStart - rspF3DDKRBootStart);
    dkrtask->task.ucode = (u64 *) rspF3DDKRFifoStart;
    dkrtask->task.ucode_data = (u64 *) rspF3DDKRDataFifoStart;
    dkrtask->task.ucode_data_size = 0x800;
    dkrtask->task.dram_stack = (u64 *) gDramStack;
    dkrtask->task.dram_stack_size = 0x400;
    dkrtask->task.output_buff = gGfxSPTaskOutputBuffer;
    dkrtask->task.output_buff_size = (u64 *)((u8 *) gGfxSPTaskOutputBuffer + (sizeof(u64) * FIFO_BUFFER_SIZE));
    dkrtask->task.yield_data_ptr = (u64 *) gGfxTaskYieldData;
    dkrtask->task.yield_data_size = sizeof(gGfxTaskYieldData);
    dkrtask->next = 0;
    dkrtask->flags = OS_SC_LAST_TASK | OS_SC_SWAPBUFFER | OS_SC_NEEDS_RDP | OS_SC_NEEDS_RSP;
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
        osRecvMesg(&D_80125EA0, (OSMesg) &mesgBuf, 1);
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

/**
 * Clears the ZBuffer first, then decides how to draw the background which goes directly
 * over the colour buffer. DrawBG if set to 0 (which never happens) will completely skip
 * over clearing the colour buffer.
*/
void render_background(Gfx **dlist, Matrix *mtx, s32 drawBG) {
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

    gDPPipeSync((*dlist)++);
    gDPSetScissor((*dlist)++, 0, 0, 0, w - 1, h - 1);
    gDPSetCycleType((*dlist)++, G_CYC_FILL);
    gDPSetColorImage((*dlist)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, w, SEGMENT_DEPTH_BUFFER);
    gDPSetFillColor((*dlist)++, GPACK_RGBA5551(255, 255, 240, 0) << 16 | GPACK_RGBA5551(255, 255, 240, 0));
    gDPFillRectangle((*dlist)++, 0, 0, w - 1, h - 1);
    gDPPipeSync((*dlist)++);
    gDPSetColorImage((*dlist)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, w, SEGMENT_COLOUR_BUFFER);
    if (drawBG) {
        if (func_80066910(0)) {
            if (D_800DE4CC) {
                func_800787FC(dlist);
            } else if (D_800DE4C4 != 0) {
                func_80078190(dlist);
            } else if (gBackgroundDrawFunc.ptr != NULL) {
                gBackgroundDrawFunc.function((Gfx *) dlist, mtx);
            } else {
                gDPSetFillColor((*dlist)++, sBackgroundFillColour);
                gDPFillRectangle((*dlist)++, 0, 0, w - 1, h - 1);
            }
            /*if (copy_viewport_background_size_to_coords(0, &x1, &y1, &x2, &y2)) {
                gDPSetCycleType((*dlist)++, G_CYC_1CYCLE);
                gDPSetPrimColor((*dlist)++, 0, 0, sBackgroundPrimColourR, sBackgroundPrimColourG, sBackgroundPrimColourB, 255);
                gDPSetCombineMode((*dlist)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
                gDPSetRenderMode((*dlist)++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
                gDPFillRectangle((*dlist)++, x1, y1, x2, y2);
            }*/
        } else {
            if (D_800DE4CC) {
                func_800787FC(dlist);
            } else if (D_800DE4C4 != 0) {
                func_80078190(dlist);
            } else if (gBackgroundDrawFunc.ptr != NULL) {
                gBackgroundDrawFunc.function((Gfx *) dlist, mtx);
            } else {
                gDPSetFillColor((*dlist)++, (GPACK_RGBA5551(sBackgroundPrimColourR, sBackgroundPrimColourG, sBackgroundPrimColourB, 1) << 16) | GPACK_RGBA5551(sBackgroundPrimColourR, sBackgroundPrimColourG, sBackgroundPrimColourB, 1));
                gDPFillRectangle((*dlist)++, 0, 0, w - 1, h - 1);
            }
        }
    }
    gDPPipeSync((*dlist)++);
    func_80067A3C(dlist);
}

/**
 * Gets the framebuffer width, then points to the start of segment 0x01 in memory.
 * afterwards, calls the draw command that initialises all the rendermodes, ready for use.
 */
void init_rdp_and_framebuffer(Gfx **dlist) {
    gDPSetColorImage((*dlist)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, gScreenWidth, SEGMENT_COLOUR_BUFFER);
    gDPSetDepthImage((*dlist)++, SEGMENT_DEPTH_BUFFER);
    gSPDisplayList((*dlist)++, dRdpInit);
}

/**
 * Calls the draw command that sets all the OtherModes, ready for use.
 */
void init_rsp(Gfx **dlist) {
    gSPDisplayList((*dlist)++, dRspInit);
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

void func_80078170(TextureHeader *arg0, TextureHeader *arg1, u32 arg2) {
    D_800DE4C4 = arg0;
    D_800DE4C8 = arg1;
    D_800DE4C0 = arg2 << 2;
}

GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80078190.s")

UNUSED void func_80078778(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
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

UNUSED void func_800787F0(void) {
    D_800DE4CC = 0;
}

void func_800787FC(Gfx **arg0) {
    s32 height;
    s32 width;
    s32 var_t4; // Flips between 0 and 1
    s32 y;
    s32 x;

    var_t4 = get_video_width_and_height_as_s32();
    height = GET_VIDEO_HEIGHT(var_t4) & 0xFFFF;
    width = GET_VIDEO_WIDTH(var_t4);
    
    gSPDisplayList((*arg0)++, D_800DE5E0);
    gDPSetPrimColor((*arg0)++, 0, 0, D_80125F30, D_80125F31, D_80125F32, D_80125F33);

    for (y = 0, var_t4 = 0; y < height; y += D_80125F3C, var_t4 ^= 1) {
        for (x = var_t4 * D_80125F38; x < width; x += D_80125F38 * 2) {
            gDPFillRectangle((*arg0)++, x, y, x + D_80125F38, y + D_80125F3C);            
        }
    }
    
    gDPSetPrimColor((*arg0)++, 0, 0, D_80125F34, D_80125F35, D_80125F36, D_80125F37);
    
    for (y = 0, var_t4 = 1; y < height; y += D_80125F3C, var_t4 ^= 1) {
        for (x = var_t4 * D_80125F38; x < width; x += D_80125F38 * 2) {
            gDPFillRectangle((*arg0)++, x, y, x + D_80125F38, y + D_80125F3C);            
        }
    }
    
    gDPPipeSync((*arg0)++);
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
void render_textured_rectangle(Gfx **dlist, DrawTexture *element, s32 xPos, s32 yPos, u8 red, u8 green, u8 blue, u8 alpha) {
    TextureHeader *tex;
    s32 i;
    s32 uly;
    s32 ulx;
    s32 lry;
    s32 lrx;
    s32 t;
    s32 s;

    gSPDisplayList((*dlist)++, dTextureRectangleModes);
    gDPSetPrimColor((*dlist)++, 0, 0, red, green, blue, alpha); 
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
            gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(tex->cmd), tex->numberOfCommands);
            gSPTextureRectangle((*dlist)++, ulx, uly, lrx, lry, G_TX_RENDERTILE, s, t, 1024, 1024);
        }
    }
    gDPPipeSync((*dlist)++);
    gDPSetPrimColor((*dlist)++, 0, 0, 255, 255, 255, 255);
}

GLOBAL_ASM("asm/non_matchings/unknown_078050/render_texture_rectangle_scaled.s")
