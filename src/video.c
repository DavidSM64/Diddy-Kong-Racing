/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8007A310 */

#include "video.h"
#include "viint.h"
#include "camera.h"
#include "game.h"
#include "main.h"
#include "printf.h"

/************ .data ************/

u16 *gVideoDepthBuffer = NULL;

/*******************************/

/************ .bss ************/

s32 gVideoRefreshRate; //Official Name: viFramesPerSecond
f32 gVideoAspectRatio;
f32 gVideoHeightRatio;
OSMesg gVideoMesgBuf[8];
OSMesgQueue gVideoMesgQueue[8];
OSViMode gTvViMode;
s32 gVideoFbWidths[NUM_FRAMEBUFFERS];
s32 gVideoFbHeights[NUM_FRAMEBUFFERS];
u16 *gVideoFramebuffers[NUM_FRAMEBUFFERS];
s32 gVideoWriteFbIndex;
s32 gVideoReadyFbIndex;
s32 gVideoFrontFbIndex;
s32 gVideoModeIndex;
s32 sBlackScreenTimer;
u16 *gVideoWriteFramebuffer;
u16 *gVideoReadyFramebuffer;
u16 *gVideoFrontFramebuffer;
u16 *gVideoWriteDepthBuffer;
u16 *gVideoReadyDepthBuffer;
u16 *gVideoFrontDepthBuffer;
u8 gFrameBufferIndex = 0;
s32 gVideoHasReadyFrame;
u8 D_801262E4;
u8 gVideoDeltaCounter;
u8 gVideoDeltaTime;
OSScClient gVideoSched;
u8 gExpansionPak = FALSE;
u8 gUseExpansionMemory = FALSE;
u16 gScreenWidth = SCREEN_WIDTH;
u16 gScreenHeight;

/******************************/

/**
 * Set up the framebuffers and the VI.
 * Framebuffers are allocated at runtime.
 * Official Name: viInit
 */
void init_video(s32 videoModeIndex, OSSched *sc) {
    s32 i;
    gVideoRefreshRate = REFRESH_60HZ;
    gVideoAspectRatio = ASPECT_RATIO_NTSC;
    gVideoHeightRatio = HEIGHT_RATIO_NTSC;

    

    reset_video_delta_time();
    set_video_mode_index(videoModeIndex);
    // I run this even with an expansion pak just to use up the memory.
    // Means I don't run into any issues if I test without a pak that just happened to work with.
    if (SCREEN_WIDTH * SCREEN_HEIGHT <= 320 * 240) {
        for (i = 0; i < NUM_FRAMEBUFFERS; i++) {
            gVideoFramebuffers[i] = 0;
            init_framebuffer(i);
        }
    }
// If Enforced 4MB is on, move framebuffers to expansion memory
#if !defined(EXPANSION_PAK_SUPPORT) && !defined(FORCE_4MB_MEMORY)
    if (gExpansionPak) {
        gVideoFramebuffers[0] = (u16 *) 0x80500000;
        gVideoFramebuffers[1] = (u16 *) 0x80600000;
    #ifdef TRIPLE_BUFFERING
        gVideoFramebuffers[2] = (u16 *) 0x80700000;
    #endif
        gVideoDepthBuffer = (u16 *) 0x80400000;
    }
#endif
    gVideoWriteFbIndex = 0;
    gVideoWriteFramebuffer = gVideoFramebuffers[gVideoWriteFbIndex];
#ifdef TRIPLE_BUFFERING
    gVideoReadyFbIndex = 1;
    gVideoFrontFbIndex = 2;
    gVideoReadyFramebuffer = gVideoFramebuffers[gVideoReadyFbIndex];
    gVideoFrontFramebuffer = gVideoFramebuffers[gVideoFrontFbIndex];
#endif
    gVideoFrontDepthBuffer = gVideoDepthBuffer;
    gVideoWriteDepthBuffer = gVideoDepthBuffer;
    gVideoHasReadyFrame = FALSE;
    osCreateMesgQueue((OSMesgQueue *)&gVideoMesgQueue, gVideoMesgBuf, ARRAY_COUNT(gVideoMesgBuf));
    osScAddClient(sc, &gVideoSched, (OSMesgQueue *)&gVideoMesgQueue, OS_SC_ID_VIDEO);
    init_vi_settings();
    sBlackScreenTimer = 12;
    osViBlack(TRUE);
    gVideoDeltaCounter = 0;
    D_801262E4 = 3;
}

/**
 * Set the current video mode to the id specified.
 */
void set_video_mode_index(s32 videoModeIndex) {
    gVideoModeIndex = videoModeIndex;
}

/**
 * Return the current framebuffer dimensions as a single s32 value.
 * The high 16 bits are the height of the frame, and the low 16 bits are the width.
 * Official Name: viGetCurrentSize?
 */
s32 get_video_width_and_height_as_s32(void) {
    return (gScreenHeight << 16) | gScreenWidth;
}

OSViMode gGlobalVI;

void change_vi(OSViMode *mode, int width, int height) {
    s32 addPAL = 0;
    s32 addX = 16;
    gGlobalVI = osViModeNtscLan1;

    if (height < 240) {
        if (width == SCREEN_WIDTH_16_10) {
            addX = 20;
        } else if (width == SCREEN_WIDTH_WIDE) {
            addX = 24;
        }
        mode->comRegs.width = width;
        mode->comRegs.xScale = ((width + addX)*512)/320;
        // Y Scale
        mode->fldRegs[0].yScale = (((height + 16 - (addPAL * 2))*1024)/240);
        mode->fldRegs[1].yScale = (((height + 16 - (addPAL * 2))*1024)/240);
        // X Centre
        mode->fldRegs[0].origin = width*2;
        mode->fldRegs[1].origin = width*4;

        mode->comRegs.hStart = (428-304 + (gScreenPos[0] * 2)) << 16 | (428+304 + (gScreenPos[0] * 2));
        mode->fldRegs[0].vStart = (277-height + (gScreenPos[1] * 2)) << 16 | (271+height + (gScreenPos[1] * 2));
        mode->fldRegs[1].vStart = (277-height + (gScreenPos[1] * 2)) << 16 | (271+height + (gScreenPos[1] * 2));
    } else if (height == 240) {
        mode->comRegs.width = width;
        mode->comRegs.xScale = (width*512)/320;
        mode->fldRegs[0].origin = width*2;
        mode->fldRegs[1].origin = width*4;
        mode->fldRegs[0].yScale = ((height*1024)/240);
        mode->fldRegs[1].yScale = ((height*1024)/240);
    } else {
        mode->comRegs.width = width;
        mode->comRegs.xScale = (width*512)/320;
        mode->comRegs.ctrl |= 0x40;
        mode->fldRegs[0].origin = width*2;
        mode->fldRegs[1].origin = width*4;
        mode->fldRegs[0].yScale = 0x2000000|((height*1024)/240);
        mode->fldRegs[1].yScale = 0x2000000|((height*1024)/240);
        mode->fldRegs[0].vStart = mode->fldRegs[1].vStart-0x20002;
    }
    gVideoAspectRatio = (f32) width / (f32) height;
    reset_perspective_matrix();
}

void set_dither_filter(void) {
    if (gAntiAliasing && !gOverrideAA) {
        osViSetSpecialFeatures(OS_VI_DIVOT_ON);
        osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON);
    } else {
        osViSetSpecialFeatures(OS_VI_DIVOT_OFF);
        osViSetSpecialFeatures(OS_VI_DITHER_FILTER_OFF);
    }
}

/**
 * Initialise the VI settings.
 * It first checks the TV type ad then will set the properties of the VI
 * depending on the gVideoModeIndex value.
 * Most of these go unused, as the value is always 1.
 */
void init_vi_settings(void) {
	change_vi(&gGlobalVI, SCREEN_WIDTH, SCREEN_HEIGHT);
	osViSetMode(&gGlobalVI);
    gScreenWidth = SCREEN_WIDTH;
    gScreenHeight = SCREEN_HEIGHT;
    set_dither_filter();
    osViSetSpecialFeatures(OS_VI_GAMMA_OFF);
}

/**
 * Allocate the selected framebuffer index from the main pool.
 * Will also allocate the depthbuffer if it does not already exist.
 */
void init_framebuffer(s32 index) {
    if (gVideoFramebuffers[index] != 0) {
        func_80071538((u8 *) gVideoFramebuffers[index]);
        free_from_memory_pool(gVideoFramebuffers[index]);
    }

    gVideoFramebuffers[index] = allocate_from_main_pool_safe((SCREEN_WIDTH * SCREEN_HEIGHT * 2) + 0x30, COLOUR_TAG_WHITE);
    gVideoFramebuffers[index] = (u16 *)(((s32)gVideoFramebuffers[index] + 0x3F) & ~0x3F);
    if (gVideoDepthBuffer == NULL) {
            gVideoDepthBuffer = allocate_from_main_pool_safe((SCREEN_WIDTH * SCREEN_HEIGHT * 2) + 0x30, COLOUR_TAG_WHITE);
            gVideoDepthBuffer = (u16 *)(((s32)gVideoDepthBuffer + 0x3F) & ~0x3F);
    }
}

/**
 * Sets the video counters to their default values.
 * Another renmant from an unused system.
 */
void reset_video_delta_time(void) {
    gVideoDeltaCounter = 0;
    gVideoDeltaTime = 2;
}

void swap_back_framebuffers(void);
void swap_front_ready_framebuffers(void);
void swap_framebuffers(void);

/**
 * Wait for the finished message from the scheduler while counting up a timer,
 * then update the current framebuffer index.
 * This function also has a section where it counts a timer that goes no higher
 * than an update magnitude of 2. It's only purpose is to be used as a divisor
 * in the unused function, get_video_refresh_speed.
 */
s32 swap_framebuffer_when_ready(s32 mesg) {
    u8 tempUpdateRate;

    tempUpdateRate = LOGIC_60FPS;
    if (sBlackScreenTimer) {
        sBlackScreenTimer--;
        if (sBlackScreenTimer == 0) {
            osViBlack(FALSE);
        }
    }
    if (mesg != MESG_SKIP_BUFFER_SWAP) {
#ifdef TRIPLE_BUFFERING
        if (osViGetCurrentFramebuffer() == gVideoReadyFramebuffer) {
            swap_back_framebuffers();
        } else {
            swap_back_framebuffers();
            swap_front_ready_framebuffers();
         }
#else
        swap_framebuffers();
#endif
    }
    while (osRecvMesg(gVideoMesgQueue, NULL, OS_MESG_NOBLOCK) != -1) {
        tempUpdateRate++;
    }

    osViSwapBuffer(gVideoFrontFramebuffer);
    return tempUpdateRate;
}

void func_8007AB24(u8 arg0) {
    D_801262E4 = arg0;
}

#ifdef TRIPLE_BUFFERING
void swap_front_ready_framebuffers(void) {
    s32 tmp = gVideoFrontFbIndex;
    gVideoFrontFbIndex = gVideoReadyFbIndex;
    gVideoReadyFbIndex = tmp;

    gVideoFrontFramebuffer = gVideoFramebuffers[gVideoFrontFbIndex];
    gVideoReadyFramebuffer = gVideoFramebuffers[gVideoReadyFbIndex];
}

void swap_back_framebuffers(void) {
    s32 tmp = gVideoWriteFbIndex;
    gVideoWriteFbIndex = gVideoReadyFbIndex;
    gVideoReadyFbIndex = tmp;

    gVideoWriteFramebuffer = gVideoFramebuffers[gVideoWriteFbIndex];
    gVideoReadyFramebuffer = gVideoFramebuffers[gVideoReadyFbIndex];
}
#else
void swap_framebuffers(void) {
    gVideoWriteFbIndex ^= 1;
    gVideoFrontFramebuffer = gVideoFramebuffers[gVideoWriteFbIndex];
}
#endif