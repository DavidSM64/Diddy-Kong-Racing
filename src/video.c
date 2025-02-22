/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8007A310 */

#include "video.h"
#include "PRinternal/viint.h"

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
OSScClient gVideoSched;

/******************************/

/**
 * Set up the framebuffers and the VI.
 * Framebuffers are allocated at runtime.
 * Official Name: viInit
 */
void video_init(s32 videoModeIndex, OSSched *sc) {
    if (osTvType == OS_TV_TYPE_PAL) {
        gVideoRefreshRate = REFRESH_50HZ;
        gVideoAspectRatio = ASPECT_RATIO_PAL;
        gVideoHeightRatio = HEIGHT_RATIO_PAL;
    } else if (osTvType == OS_TV_TYPE_MPAL) {
        gVideoRefreshRate = REFRESH_60HZ;
        gVideoAspectRatio = ASPECT_RATIO_MPAL;
        gVideoHeightRatio = HEIGHT_RATIO_MPAL;
    } else {
        gVideoRefreshRate = REFRESH_60HZ;
        gVideoAspectRatio = ASPECT_RATIO_NTSC;
        gVideoHeightRatio = HEIGHT_RATIO_NTSC;
    }

    if (osTvType == OS_TV_TYPE_PAL) {
        s32 i;
        for (i = 0; i < 8; i++) {
            gVideoModeResolutions[i].height += PAL_HEIGHT_DIFFERENCE;
        }
    }

    video_delta_reset();
    fb_mode_set(videoModeIndex);
    gVideoFramebuffers[0] = NULL;
    gVideoFramebuffers[1] = NULL;
    fb_alloc(0);
    fb_alloc(1);
    gVideoCurrFbIndex = 1;
    fb_swap();
    osCreateMesgQueue((OSMesgQueue *) &gVideoMesgQueue, gVideoMesgBuf, ARRAY_COUNT(gVideoMesgBuf));
    osScAddClient(sc, &gVideoSched, (OSMesgQueue *) &gVideoMesgQueue, OS_SC_ID_VIDEO);
    fb_init_vi();
    sBlackScreenTimer = 12;
    osViBlack(TRUE);
    gVideoDeltaCounter = 0;
    D_801262E4 = 3;
}

/**
 * Set the current video mode to the id specified.
 */
void fb_mode_set(s32 videoModeIndex) {
    gVideoModeIndex = videoModeIndex;
}

/**
 * Unused function that would return the current video mode index.
 */
UNUSED s32 fb_mode(void) {
    return gVideoModeIndex;
}

/**
 * Unused function that would change the framebuffer dimensions.
 * Since only one kind of video mode is ever used, this function is never called.
 */
UNUSED void fb_mode_size(s32 fbIndex) {
    gVideoFbWidths[fbIndex] = gVideoModeResolutions[gVideoModeIndex & NUM_RESOLUTION_MODES].width;
    gVideoFbHeights[fbIndex] = gVideoModeResolutions[gVideoModeIndex & NUM_RESOLUTION_MODES].height;
}

/**
 * Return the current framebuffer dimensions as a single s32 value.
 * The high 16 bits are the height of the frame, and the low 16 bits are the width.
 * Official Name: viGetCurrentSize
 */
s32 fb_size(void) {
    return (gVideoFbHeights[gVideoCurrFbIndex] << 16) | gVideoFbWidths[gVideoCurrFbIndex];
}

/**
 * Initialise the VI settings.
 * It first checks the TV type ad then will set the properties of the VI
 * depending on the gVideoModeIndex value.
 * Most of these go unused, as the value is always 1.
 */
void fb_init_vi(void) {
    s32 viModeTableIndex;
    OSViMode *tvViMode;

    viModeTableIndex = OS_VI_NTSC_LPN1;
    if (osTvType == OS_TV_TYPE_PAL) {
        viModeTableIndex = OS_VI_PAL_LPN1;
    } else if (osTvType == OS_TV_TYPE_MPAL) {
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
            if (osTvType == OS_TV_TYPE_PAL) {
                tvViMode = &osViModePalLpn1;
            } else if (osTvType == OS_TV_TYPE_MPAL) {
                tvViMode = &osViModeMpalLpn1;
            }
            fb_memcpy((u8 *) tvViMode, (u8 *) &gTvViMode, sizeof(OSViMode));
            if (osTvType == OS_TV_TYPE_PAL) {
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
            if (osTvType == OS_TV_TYPE_PAL) {
                tvViMode = &osViModePalLpn1;
            } else if (osTvType == OS_TV_TYPE_MPAL) {
                tvViMode = &osViModeMpalLpn1;
            }

            fb_memcpy((u8 *) tvViMode, (u8 *) &gTvViMode, sizeof(OSViMode));
            gTvViMode.comRegs.width = WIDTH(HIGH_RES_SCREEN_WIDTH);
            gTvViMode.comRegs.xScale = SCALE(1, 0);
            gTvViMode.fldRegs[0].origin = ORIGIN(HIGH_RES_SCREEN_WIDTH * 2);
            gTvViMode.fldRegs[1].origin = ORIGIN(HIGH_RES_SCREEN_WIDTH * 2);
            osViSetMode(&gTvViMode);
            break;
        case VIDEO_MODE_MEDRES_LAN:
            stubbed_printf("640 by 240 Anti-aliased, Non interlaced.\n");
            tvViMode = &osViModeNtscLan1;
            if (osTvType == OS_TV_TYPE_PAL) {
                tvViMode = &osViModePalLan1;
            } else if (osTvType == OS_TV_TYPE_MPAL) {
                tvViMode = &osViModeMpalLan1;
            }
            fb_memcpy((u8 *) tvViMode, (u8 *) &gTvViMode, sizeof(OSViMode));
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
 * Framebuffers should be 64 bit aligned, but since the memory allocator
 * already aligns by 16, it only needs 48 bits of alignment in addition.
 */
void fb_alloc(s32 index) {
    if (gVideoFramebuffers[index] != 0) {
        mempool_locked_unset((u8 *) gVideoFramebuffers[index]); // Effectively unused.
        mempool_free(gVideoFramebuffers[index]);
    }
    gVideoFbWidths[index] = gVideoModeResolutions[gVideoModeIndex & NUM_RESOLUTION_MODES].width;
    gVideoFbHeights[index] = gVideoModeResolutions[gVideoModeIndex & NUM_RESOLUTION_MODES].height;
    if (gVideoModeIndex >= VIDEO_MODE_MIDRES_MASK) {
        gVideoFramebuffers[index] =
            mempool_alloc_safe((HIGH_RES_SCREEN_WIDTH * HIGH_RES_SCREEN_HEIGHT * 2) + 0x30, COLOUR_TAG_WHITE);
        gVideoFramebuffers[index] = FBALIGN(gVideoFramebuffers[index]);
        if (gVideoDepthBuffer == NULL) {
            gVideoDepthBuffer =
                mempool_alloc_safe((HIGH_RES_SCREEN_WIDTH * HIGH_RES_SCREEN_HEIGHT * 2) + 0x30, COLOUR_TAG_WHITE);
            gVideoDepthBuffer = FBALIGN(gVideoDepthBuffer);
        }
    } else {
        gVideoFramebuffers[index] =
            mempool_alloc_safe((gVideoFbWidths[index] * gVideoFbHeights[index] * 2) + 0x30, COLOUR_TAG_WHITE);
        gVideoFramebuffers[index] = FBALIGN(gVideoFramebuffers[index]);
        if (gVideoDepthBuffer == NULL) {
            gVideoDepthBuffer =
                mempool_alloc_safe((gVideoFbWidths[index] * gVideoFbHeights[index] * 2) + 0x30, COLOUR_TAG_WHITE);
            gVideoDepthBuffer = FBALIGN(gVideoDepthBuffer);
        }
    }
}

/**
 * Sets the video counters to their default values.
 * Another renmant from an unused system.
 */
void video_delta_reset(void) {
    gVideoDeltaCounter = 0;
    gVideoDeltaTime = 2;
}

/**
 * Wait for the finished message from the scheduler while counting up a timer,
 * then update the current framebuffer index.
 * This function also has a section where it counts a timer that goes no higher
 * than an update magnitude of 2. It's only purpose is to be used as a divisor
 * in the unused function, vi_refresh_rate.
 */
s32 fb_update(s32 mesg) {
    u8 tempUpdateRate;

    tempUpdateRate = LOGIC_60FPS;
    if (sBlackScreenTimer) {
        sBlackScreenTimer--;
        if (sBlackScreenTimer == 0) {
            osViBlack(FALSE);
        }
    }
    if (mesg != MESG_SKIP_BUFFER_SWAP) {
        fb_swap();
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
UNUSED s32 vi_refresh_rate(void) {
    return (s32) ((f32) gVideoRefreshRate / (f32) gVideoDeltaTime);
}

/**
 * Flips the current framebuffer index, swapping to the other framebuffer
 * for the next frame, then update the current and previous framebuffer pointers.
 */
void fb_swap(void) {
    gVideoLastFramebuffer = gVideoFramebuffers[gVideoCurrFbIndex];
    gVideoLastDepthBuffer = gVideoDepthBuffer;
    gVideoCurrFbIndex ^= 1;
    gVideoCurrFramebuffer = gVideoFramebuffers[gVideoCurrFbIndex];
    gVideoCurrDepthBuffer = gVideoDepthBuffer;
}

/**
 * Copy byte-by-byte a region from one address to another.
 */
void fb_memcpy(u8 *src, u8 *dest, s32 len) {
    s32 i;

    for (i = 0; i < len; i++) {
        *dest++ = *src++;
    }
}
