/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8007A310 */

#include "video.h"
#include "viint.h"
#include "camera.h"

/************ .data ************/

u16 *gVideoDepthBuffer = NULL;

/*******************************/

/************ .bss ************/

s32 gVideoRefreshRate;
f32 gVideoAspectRatio;
f32 gVideoHeightRatio;
OSMesg gVideoMesgBuf[8];
OSMesgQueue gVideoMesgQueue[8];
OSViMode gTvViMode;
s32 gVideoFbWidths[3];
s32 gVideoFbHeights[3];
u16 *gVideoFramebuffers[3];
s32 gVideoCurrFbIndex;
s32 gVideoModeIndex;
s32 sBlackScreenTimer;
u16 *gVideoCurrFramebuffer;
u16 *gVideoLastFramebuffer;
u16 *gVideoCurrDepthBuffer;
u16 *gVideoLastDepthBuffer;
u8 D_801262E4;
u8 gVideoDeltaCounter;
u8 gVideoDeltaTime;
OSScClient gVideoSched;
u8 gNumFrameBuffers = 2;
u8 gExpansionPak = FALSE;
u16 gScreenWidth = SCREEN_WIDTH;
u16 gScreenHeight;

/******************************/

/**
 * Set up the framebuffers and the VI.
 * Framebuffers are allocated at runtime.
 */
void init_video(s32 videoModeIndex, OSSched *sc) {
    s32 i;
    if (osTvType == TV_TYPE_PAL) {
        gVideoRefreshRate = REFRESH_50HZ;
        gVideoAspectRatio = ASPECT_RATIO_PAL;
        gVideoHeightRatio = HEIGHT_RATIO_PAL;
    } else if (osTvType == TV_TYPE_MPAL) {
        gVideoRefreshRate = REFRESH_60HZ;
        gVideoAspectRatio = ASPECT_RATIO_MPAL;
        gVideoHeightRatio = HEIGHT_RATIO_MPAL;
    } else {
        gVideoRefreshRate = REFRESH_60HZ;
        gVideoAspectRatio = ASPECT_RATIO_NTSC;
        gVideoHeightRatio = HEIGHT_RATIO_NTSC;
    }

    if (gExpansionPak) {
        gNumFrameBuffers++;
    }

    reset_video_delta_time();
    set_video_mode_index(videoModeIndex);
    for (i = 0; i < gNumFrameBuffers; i++) {
        gVideoFramebuffers[i] = 0;
        init_framebuffer(i);
    }
    gVideoCurrFbIndex = 1;
    swap_framebuffers();
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
 */
s32 get_video_width_and_height_as_s32(void) {
    return (gScreenHeight << 16) | gScreenWidth;
}

OSViMode gGlobalVI;

void change_vi(OSViMode *mode, int width, int height) {
    s32 addPAL = 0;
    s32 addX = 16;
    gGlobalVI = osViModeNtscLan1;

    if (osTvType == TV_TYPE_PAL) {
        addPAL = PAL_HEIGHT_DIFFERENCE;
    }

    if (height < 240) {
        //addX = 24;
        mode->comRegs.width = width;
        mode->comRegs.xScale = ((width + addX)*512)/320;
        // Y Scale
        mode->fldRegs[0].yScale = (((height + 16 - (addPAL * 2))*1024)/240);
        mode->fldRegs[1].yScale = (((height + 16 - (addPAL * 2))*1024)/240);
        // X Centre
        mode->fldRegs[0].origin = width*2;
        mode->fldRegs[1].origin = width*4;

        mode->comRegs.hStart = (428-304) << 16 | (428+304);
        mode->fldRegs[0].vStart = (277-height) << 16 | (271+height);
        mode->fldRegs[1].vStart = (277-height) << 16 | (271+height);
    }
    gVideoAspectRatio = (f32) width / (f32) height;
    func_80065EA0();
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
    osViSetSpecialFeatures(OS_VI_DIVOT_ON);
    osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON);
    osViSetSpecialFeatures(OS_VI_GAMMA_OFF);
}

/**
 * Allocate the selected framebuffer index from the main pool.
 * Will also allocate the depthbuffer if it does not already exist.
 */
void init_framebuffer(s32 index) {
    s32 width;
    if (gVideoFramebuffers[index] != 0) {
        func_80071538((u8 *) gVideoFramebuffers[index]);
        free_from_memory_pool(gVideoFramebuffers[index]);
    }

    if (gExpansionPak) {
        width = SCREEN_WIDTH_WIDE;
    } else {
        width = SCREEN_WIDTH;
    }
    if (gExpansionPak) {
        gVideoFramebuffers[index] = (u16 *) 0x80500000 + (((SCREEN_WIDTH * SCREEN_HEIGHT * 2) + 0x30) * index);
    } else {
        gVideoFramebuffers[index] = allocate_from_main_pool_safe((SCREEN_WIDTH * SCREEN_HEIGHT * 2) + 0x30, COLOUR_TAG_WHITE);
    }
    gVideoFramebuffers[index] = (u16 *)(((s32)gVideoFramebuffers[index] + 0x3F) & ~0x3F);
    if (gVideoDepthBuffer == NULL) {
        gVideoDepthBuffer = allocate_from_main_pool_safe((SCREEN_WIDTH * SCREEN_HEIGHT * 2) + 0x30, COLOUR_TAG_WHITE);
        gVideoDepthBuffer = (u16 *)(((s32)gVideoDepthBuffer + 0x3F) & ~0x3F);
    }
}

#include "printf.h"

/**
 * Sets the video counters to their default values.
 * Another renmant from an unused system.
 */
void reset_video_delta_time(void) {
    gVideoDeltaCounter = 0;
    gVideoDeltaTime = 2;
}

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
        swap_framebuffers();
    }
    while (osRecvMesg(gVideoMesgQueue, NULL, OS_MESG_NOBLOCK) != -1) {
        tempUpdateRate++;
    }

    while (tempUpdateRate < gVideoDeltaTime) {
        osRecvMesg(gVideoMesgQueue, NULL, OS_MESG_BLOCK);
        tempUpdateRate++;
    }

    //render_printf

    osViSwapBuffer(gVideoLastFramebuffer);
    osRecvMesg(gVideoMesgQueue, NULL, OS_MESG_BLOCK);
    return tempUpdateRate;
}

void func_8007AB24(u8 arg0) {
    D_801262E4 = arg0;
}
/**
 * Flips the current framebuffer index, swapping to the other framebuffer
 * for the next frame, then update the current and previous framebuffer pointers.
 */
void swap_framebuffers(void) {
    gVideoLastFramebuffer = gVideoFramebuffers[gVideoCurrFbIndex];
    gVideoLastDepthBuffer = gVideoDepthBuffer;
    gVideoCurrFbIndex++;
    if (gVideoCurrFbIndex == gNumFrameBuffers) {
        gVideoCurrFbIndex = 0;
    }
    gVideoCurrFramebuffer = gVideoFramebuffers[gVideoCurrFbIndex];
    gVideoCurrDepthBuffer = gVideoDepthBuffer;
}
