/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8007A310 */

#include "video.h"
#include "viint.h"

/************ .data ************/

u16 *gVideoDepthBuffer = NULL;
UNUSED s32 D_800DE774 = 0;
UNUSED s8 D_800DE778 = 2;

VideoModeResolution gVideoModeResolutions[] = {
    { SCREEN_WIDTH, SCREEN_HEIGHT },                   // 320x240
    { SCREEN_WIDTH, SCREEN_HEIGHT },                   // 320x240
    { HIGH_RES_SCREEN_WIDTH, SCREEN_HEIGHT },          // 640x240
    { HIGH_RES_SCREEN_WIDTH, SCREEN_HEIGHT },          // 640x240
    { HIGH_RES_SCREEN_WIDTH, HIGH_RES_SCREEN_HEIGHT }, // 640x480
    { HIGH_RES_SCREEN_WIDTH, HIGH_RES_SCREEN_HEIGHT }, // 640x480
    { HIGH_RES_SCREEN_WIDTH, HIGH_RES_SCREEN_HEIGHT }, // 640x480
    { HIGH_RES_SCREEN_WIDTH, HIGH_RES_SCREEN_HEIGHT }, // 640x480
};

// This value exists in order to make sure there are no out of bounds accesses of gVideoModeResolutions
#define NUM_RESOLUTION_MODES ((sizeof(gVideoModeResolutions) / sizeof(VideoModeResolution)) - 1)

/*******************************/

/************ .bss ************/

s32 gVideoRefreshRate; // Official Name: viFramesPerSecond
f32 gVideoAspectRatio;
f32 gVideoHeightRatio;
UNUSED s32 D_8012617C;
OSMesg gVideoMesgBuf[8];
OSMesgQueue gVideoMesgQueue[8];
OSViMode gTvViMode;
s32 gVideoFbWidths[2];
s32 gVideoFbHeights[2];
u16 *gVideoFramebuffers[2];
s32 gVideoCurrFbIndex;
s32 gVideoModeIndex;
s32 sBlackScreenTimer;
u16 *gVideoCurrFramebuffer; // Official Name: currentScreen
u16 *gVideoLastFramebuffer; // Official Name: otherScreen
u16 *gVideoCurrDepthBuffer;
u16 *gVideoLastDepthBuffer; // Official Name: otherZbuf
u8 D_801262E4;
UNUSED OSMesg D_801262E8[8];
u8 gVideoDeltaCounter;
u8 gVideoDeltaTime;
UNUSED s32 D_8012630C;
OSScClient gVideoSched;

/******************************/

/**
 * Set up the framebuffers and the VI.
 * Framebuffers are allocated at runtime.
 * Official Name: viInit
 */
void init_video(s32 videoModeIndex, OSSched *sc) {
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

    if (osTvType == TV_TYPE_PAL) {
        s32 i;
        for (i = 0; i < 8; i++) {
            gVideoModeResolutions[i].height += PAL_HEIGHT_DIFFERENCE;
        }
    }

    reset_video_delta_time();
    set_video_mode_index(videoModeIndex);
    gVideoFramebuffers[0] = NULL;
    gVideoFramebuffers[1] = NULL;
    init_framebuffer(0);
    init_framebuffer(1);
    gVideoCurrFbIndex = 1;
    swap_framebuffers();
    osCreateMesgQueue((OSMesgQueue *) &gVideoMesgQueue, gVideoMesgBuf, ARRAY_COUNT(gVideoMesgBuf));
    osScAddClient(sc, &gVideoSched, (OSMesgQueue *) &gVideoMesgQueue, OS_SC_ID_VIDEO);
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
 * Unused function that would return the current video mode index.
 */
UNUSED s32 get_video_mode_index(void) {
    return gVideoModeIndex;
}

/**
 * Unused function that would change the framebuffer dimensions.
 * Since only one kind of video mode is ever used, this function is never called.
 */
UNUSED void set_video_width_and_height_from_index(s32 fbIndex) {
    gVideoFbWidths[fbIndex] = gVideoModeResolutions[gVideoModeIndex & NUM_RESOLUTION_MODES].width;
    gVideoFbHeights[fbIndex] = gVideoModeResolutions[gVideoModeIndex & NUM_RESOLUTION_MODES].height;
}

/**
 * Return the current framebuffer dimensions as a single s32 value.
 * The high 16 bits are the height of the frame, and the low 16 bits are the width.
 * Official Name: viGetCurrentSize
 */
s32 get_video_width_and_height_as_s32(void) {
    return (gVideoFbHeights[gVideoCurrFbIndex] << 16) | gVideoFbWidths[gVideoCurrFbIndex];
}

/**
 * Initialise the VI settings.
 * It first checks the TV type ad then will set the properties of the VI
 * depending on the gVideoModeIndex value.
 * Most of these go unused, as the value is always 1.
 */
void init_vi_settings(void) {
    s32 viModeTableIndex;
    OSViMode *tvViMode;

    viModeTableIndex = OS_VI_NTSC_LPN1;
    if (osTvType == TV_TYPE_PAL) {
        viModeTableIndex = OS_VI_PAL_LPN1;
    } else if (osTvType == TV_TYPE_MPAL) {
        viModeTableIndex = OS_VI_MPAL_LPN1;
    }

    switch (gVideoModeIndex & NUM_RESOLUTION_MODES) {
        case VIDEO_MODE_LOWRES_LAN:
            stubbed_printf("320 by 240 Point sampled, Non interlaced.\n");
            osViSetMode(&osViModeTable[viModeTableIndex]);
            break;
        case VIDEO_MODE_LOWRES_LPN:
            //@bug: The video mode being set here is Point sampled
            // but the printf implies it was intended to be Anti-aliased.
            // By my understanding, this is the case we will always hit in code,
            // So maybe it was swapped out late in development?
            stubbed_printf("320 by 240 Anti-aliased, Non interlaced.\n");
            tvViMode = &osViModeNtscLpn1;
            if (osTvType == TV_TYPE_PAL) {
                tvViMode = &osViModePalLpn1;
            } else if (osTvType == TV_TYPE_MPAL) {
                tvViMode = &osViModeMpalLpn1;
            }
            memory_copy((u8 *) tvViMode, (u8 *) &gTvViMode, sizeof(OSViMode));
            if (osTvType == TV_TYPE_PAL) {
                // A simple osViExtendVStart to add an additional 24 scanlines?
                gTvViMode.fldRegs[0].vStart -= (PAL_HEIGHT_DIFFERENCE << 16);
                gTvViMode.fldRegs[1].vStart -= (PAL_HEIGHT_DIFFERENCE << 16);
                gTvViMode.fldRegs[0].vStart += PAL_HEIGHT_DIFFERENCE;
                gTvViMode.fldRegs[1].vStart += PAL_HEIGHT_DIFFERENCE;
            }
            osViSetMode(&gTvViMode);
            break;
        case VIDEO_MODE_MEDRES_LPN:
            stubbed_printf("640 by 240 Point sampled, Non interlaced.\n");
            tvViMode = &osViModeNtscLpn1;
            if (osTvType == TV_TYPE_PAL) {
                tvViMode = &osViModePalLpn1;
            } else if (osTvType == TV_TYPE_MPAL) {
                tvViMode = &osViModeMpalLpn1;
            }

            memory_copy((u8 *) tvViMode, (u8 *) &gTvViMode, sizeof(OSViMode));
            gTvViMode.comRegs.width = WIDTH(HIGH_RES_SCREEN_WIDTH);
            gTvViMode.comRegs.xScale = SCALE(1, 0);
            gTvViMode.fldRegs[0].origin = ORIGIN(HIGH_RES_SCREEN_WIDTH * 2);
            gTvViMode.fldRegs[1].origin = ORIGIN(HIGH_RES_SCREEN_WIDTH * 2);
            osViSetMode(&gTvViMode);
            break;
        case VIDEO_MODE_MEDRES_LAN:
            stubbed_printf("640 by 240 Anti-aliased, Non interlaced.\n");
            tvViMode = &osViModeNtscLan1;
            if (osTvType == TV_TYPE_PAL) {
                tvViMode = &osViModePalLan1;
            } else if (osTvType == TV_TYPE_MPAL) {
                tvViMode = &osViModeMpalLan1;
            }
            memory_copy((u8 *) tvViMode, (u8 *) &gTvViMode, sizeof(OSViMode));
            gTvViMode.comRegs.width = WIDTH(HIGH_RES_SCREEN_WIDTH);
            gTvViMode.comRegs.xScale = SCALE(1, 0);
            gTvViMode.fldRegs[0].origin = ORIGIN(HIGH_RES_SCREEN_WIDTH * 2);
            gTvViMode.fldRegs[1].origin = ORIGIN(HIGH_RES_SCREEN_WIDTH * 2);
            osViSetMode(&gTvViMode);
            break;
        case VIDEO_MODE_HIGHRES_HPN:
            stubbed_printf("640 by 480 Point sampled, Interlaced.\n");
            osViSetMode(&osViModeTable[viModeTableIndex + OS_VI_NTSC_HPN1]);
            break;
        case VIDEO_MODE_HIGHRES_HAN:
            stubbed_printf("640 by 480 Anti-aliased, Interlaced.\n");
            osViSetMode(&osViModeTable[viModeTableIndex + OS_VI_NTSC_HAN1]);
            break;
        case VIDEO_MODE_HIGHRES_HPF:
            stubbed_printf("640 by 480 Point sampled, Interlaced, De-flickered.\n");
            osViSetMode(&osViModeTable[viModeTableIndex + OS_VI_NTSC_HPF1]);
            break;
        case VIDEO_MODE_HIGHRES_HAF:
            stubbed_printf("640 by 480 Anti-aliased, Interlaced, De-flickered.\n");
            osViSetMode(&osViModeTable[viModeTableIndex + OS_VI_NTSC_HAF1]);
            break;
    }
    osViSetSpecialFeatures(OS_VI_DIVOT_ON);
    osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON);
    osViSetSpecialFeatures(OS_VI_GAMMA_OFF);
}

/**
 * Allocate the selected framebuffer index from the main pool.
 * Will also allocate the depthbuffer if it does not already exist.
 */
void init_framebuffer(s32 index) {
    if (gVideoFramebuffers[index] != 0) {
        memory_slot_exists((u8 *) gVideoFramebuffers[index]); // Effectively unused.
        free_from_memory_pool(gVideoFramebuffers[index]);
    }
    gVideoFbWidths[index] = gVideoModeResolutions[gVideoModeIndex & NUM_RESOLUTION_MODES].width;
    gVideoFbHeights[index] = gVideoModeResolutions[gVideoModeIndex & NUM_RESOLUTION_MODES].height;
    if (gVideoModeIndex >= VIDEO_MODE_MIDRES_MASK) {
        gVideoFramebuffers[index] =
            allocate_from_main_pool_safe((HIGH_RES_SCREEN_WIDTH * HIGH_RES_SCREEN_HEIGHT * 2) + 0x30, COLOUR_TAG_WHITE);
        gVideoFramebuffers[index] = (u16 *) (((s32) gVideoFramebuffers[index] + 0x3F) & ~0x3F);
        if (gVideoDepthBuffer == NULL) {
            gVideoDepthBuffer = allocate_from_main_pool_safe(
                (HIGH_RES_SCREEN_WIDTH * HIGH_RES_SCREEN_HEIGHT * 2) + 0x30, COLOUR_TAG_WHITE);
            gVideoDepthBuffer = (u16 *) (((s32) gVideoDepthBuffer + 0x3F) & ~0x3F);
        }
    } else {
        gVideoFramebuffers[index] =
            allocate_from_main_pool_safe((gVideoFbWidths[index] * gVideoFbHeights[index] * 2) + 0x30, COLOUR_TAG_WHITE);
        gVideoFramebuffers[index] = (u16 *) (((s32) gVideoFramebuffers[index] + 0x3F) & ~0x3F);
        if (gVideoDepthBuffer == NULL) {
            gVideoDepthBuffer = allocate_from_main_pool_safe(
                (gVideoFbWidths[index] * gVideoFbHeights[index] * 2) + 0x30, COLOUR_TAG_WHITE);
            gVideoDepthBuffer = (u16 *) (((s32) gVideoDepthBuffer + 0x3F) & ~0x3F);
        }
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

    if (tempUpdateRate < gVideoDeltaTime) {
        if (gVideoDeltaCounter < 20) {
            gVideoDeltaCounter++;
        }
        if (gVideoDeltaCounter == 20) {
            gVideoDeltaTime = tempUpdateRate;
            gVideoDeltaCounter = 0;
        }
    } else {
        gVideoDeltaCounter = 0;
        if ((gVideoDeltaTime < tempUpdateRate) && (D_801262E4 >= tempUpdateRate)) {
            gVideoDeltaTime = tempUpdateRate;
        }
    }
    while (tempUpdateRate < gVideoDeltaTime) {
        osRecvMesg(gVideoMesgQueue, NULL, OS_MESG_BLOCK);
        tempUpdateRate++;
    }

    osViSwapBuffer(gVideoLastFramebuffer);
    osRecvMesg(gVideoMesgQueue, NULL, OS_MESG_BLOCK);
    return tempUpdateRate;
}

void func_8007AB24(u8 arg0) {
    D_801262E4 = arg0;
}

/**
 * Unused function that returns the refresh rate, after performance.
 * A fully performant game would return 60.
 * Perhaps may have been used originally to calculate the factor in which to handle frameskipping with.
 */
UNUSED s32 get_video_refresh_speed(void) {
    return (s32) ((f32) gVideoRefreshRate / (f32) gVideoDeltaTime);
}

/**
 * Flips the current framebuffer index, swapping to the other framebuffer
 * for the next frame, then update the current and previous framebuffer pointers.
 */
void swap_framebuffers(void) {
    gVideoLastFramebuffer = gVideoFramebuffers[gVideoCurrFbIndex];
    gVideoLastDepthBuffer = gVideoDepthBuffer;
    gVideoCurrFbIndex ^= 1;
    gVideoCurrFramebuffer = gVideoFramebuffers[gVideoCurrFbIndex];
    gVideoCurrDepthBuffer = gVideoDepthBuffer;
}

/**
 * Copy byte-by-byte a region from one address to another.
 */
void memory_copy(u8 *src, u8 *dest, s32 len) {
    s32 i;

    for (i = 0; i < len; i++) {
        *dest++ = *src++;
    }
}
