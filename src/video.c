/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8007A310 */

#include "video.h"
#include "viint.h"

/************ .data ************/

u16 *gVideoDepthBuffer = NULL;
s32 D_800DE774 = 0; // Currently unknown, might be a different type.
s8 D_800DE778 = 2;

VideoModeResolution gVideoModeResolutions[] = {
    {          SCREEN_WIDTH,          SCREEN_HEIGHT }, // 320x240
    {          SCREEN_WIDTH,          SCREEN_HEIGHT }, // 320x240
    { HIGH_RES_SCREEN_WIDTH,          SCREEN_HEIGHT }, // 640x240
    { HIGH_RES_SCREEN_WIDTH,          SCREEN_HEIGHT }, // 640x240
    { HIGH_RES_SCREEN_WIDTH, HIGH_RES_SCREEN_HEIGHT }, // 640x480
    { HIGH_RES_SCREEN_WIDTH, HIGH_RES_SCREEN_HEIGHT }, // 640x480
    { HIGH_RES_SCREEN_WIDTH, HIGH_RES_SCREEN_HEIGHT }, // 640x480
    { HIGH_RES_SCREEN_WIDTH, HIGH_RES_SCREEN_HEIGHT }, // 640x480
};

s32 D_800DE7BC = 0; // Currently unknown, might be a different type.

/*******************************/

/************ .bss ************/

s32 gVideoRefreshRate;
f32 gVideoAspectRatio;
f32 gVideoHeightRatio;
s32 D_8012617C;
OSMesg gVideoMesgBuf[8];
OSMesgQueue gVideoMesgQueue[8];
OSViMode gTvViMode;
s32 gVideoFbWidths[NUM_FRAMEBUFFERS];
s32 gVideoFbHeights[NUM_FRAMEBUFFERS];
u16 *gVideoFramebuffers[NUM_FRAMEBUFFERS];
s32 gVideoCurrFbIndex;
s32 gVideoModeIndex;
s32 D_801262D0;
u16 *gVideoCurrFramebuffer;
u16 *gVideoLastFramebuffer;
u16 *gVideoCurrDepthBuffer;
u16 *gVideoLastDepthBuffer;
u8 D_801262E4;
s32 D_801262E8[8];
u8 D_80126308;
u8 D_80126309;
s32 D_8012630C;
OSScClient gVideoSched;

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

    if (osTvType == TV_TYPE_PAL) {
        for (i = 0; i < 8; i++) {
            gVideoModeResolutions[i].height += PAL_HEIGHT_DIFFERENCE;
        }
    }

    func_8007A974();
    set_video_mode_index(videoModeIndex);
    for (i = 0; i < NUM_FRAMEBUFFERS; i++) {
        gVideoFramebuffers[i] = 0;
        init_framebuffer(i);
    }
    gVideoCurrFbIndex = 1;
    swap_framebuffers();
    osCreateMesgQueue((OSMesgQueue *)&gVideoMesgQueue, gVideoMesgBuf, ARRAY_COUNT(gVideoMesgBuf));
    osScAddClient(sc, &gVideoSched, (OSMesgQueue *)&gVideoMesgQueue, OS_SC_ID_VIDEO);
    init_vi_settings();
    D_801262D0 = 12;
    osViBlack(TRUE);
    D_80126308 = 0;
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
    gVideoFbWidths[fbIndex] = gVideoModeResolutions[gVideoModeIndex & 7].width;
    gVideoFbHeights[fbIndex] = gVideoModeResolutions[gVideoModeIndex & 7].height;
}

/**
 * Return the current framebuffer dimensions as a single s32 value.
 * The high 16 bits are the height of the frame, and the low 16 bits are the width.
 */
s32 get_video_width_and_height_as_s32(void) {
    return (gVideoFbHeights[gVideoCurrFbIndex] << 16) | gVideoFbWidths[gVideoCurrFbIndex];
}

OSViMode gGlobalVI;

void change_vi(OSViMode *mode, int width, int height) {
    s32 addPAL = 0;
    s32 addX = 16;
    gGlobalVI = osViModeNtscLan1;

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

    switch (gVideoModeIndex & 7) {
        case VIDEO_MODE_LOWRES_LAN:
            stubbed_printf("320 by 240 Point sampled, Non interlaced.\n");
            osViSetMode(&osViModeTable[viModeTableIndex]);
            break;
        case VIDEO_MODE_LOWRES_LPN:
			change_vi(&gGlobalVI, gVideoModeResolutions[gVideoModeIndex & 7].width, gVideoModeResolutions[gVideoModeIndex & 7].height);
			osViSetMode(&gGlobalVI);
            /*//@bug: The video mode being set here is Point sampled
            //but the printf implies it was intended to be Anti-aliased.
            //By my understanding, this is the case we will always hit in code,
            //So maybe it was swapped out late in development?
            stubbed_printf("320 by 240 Anti-aliased, Non interlaced.\n");
            tvViMode = &osViModeNtscLpn1;
            if (osTvType == TV_TYPE_PAL) {
                tvViMode = &osViModePalLpn1;
            } else if (osTvType == TV_TYPE_MPAL) {
                tvViMode = &osViModeMpalLpn1;
            }
            memory_copy((u8 *)tvViMode, (u8 *)&gTvViMode, sizeof(OSViMode));
            if (osTvType == TV_TYPE_PAL) {
                //A simple osViExtendVStart to add an additional 24 scanlines?
                gTvViMode.fldRegs[0].vStart -= (PAL_HEIGHT_DIFFERENCE << 16);
                gTvViMode.fldRegs[1].vStart -= (PAL_HEIGHT_DIFFERENCE << 16);
                gTvViMode.fldRegs[0].vStart += PAL_HEIGHT_DIFFERENCE;
                gTvViMode.fldRegs[1].vStart += PAL_HEIGHT_DIFFERENCE;
            }
            osViSetMode(&gTvViMode);*/
            break;
        case VIDEO_MODE_MEDRES_LPN:
            stubbed_printf("640 by 240 Point sampled, Non interlaced.\n");
            tvViMode = &osViModeNtscLpn1;
            if (osTvType == TV_TYPE_PAL) {
                tvViMode = &osViModePalLpn1;
            } else if (osTvType == TV_TYPE_MPAL) {
                tvViMode = &osViModeMpalLpn1;
            }

            memory_copy((u8 *)tvViMode, (u8 *)&gTvViMode, sizeof(OSViMode));
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
            memory_copy((u8 *)tvViMode, (u8 *)&gTvViMode, sizeof(OSViMode));
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
        func_80071538((u8 *)gVideoFramebuffers[index]);
        free_from_memory_pool(gVideoFramebuffers[index]);
    }
    gVideoFbWidths[index] = gVideoModeResolutions[gVideoModeIndex & 7].width;
    gVideoFbHeights[index] = gVideoModeResolutions[gVideoModeIndex & 7].height;
    if (gVideoModeIndex >= VIDEO_MODE_MIDRES_MASK) {
        gVideoFramebuffers[index] = allocate_from_main_pool_safe((HIGH_RES_SCREEN_WIDTH * HIGH_RES_SCREEN_HEIGHT * 2) + 0x30, COLOUR_TAG_WHITE);
        gVideoFramebuffers[index] = (u16 *)(((s32)gVideoFramebuffers[index] + 0x3F) & ~0x3F);
        if (gVideoDepthBuffer == NULL) {
            gVideoDepthBuffer = allocate_from_main_pool_safe((HIGH_RES_SCREEN_WIDTH * HIGH_RES_SCREEN_HEIGHT * 2) + 0x30, COLOUR_TAG_WHITE);
            gVideoDepthBuffer = (u16 *)(((s32)gVideoDepthBuffer + 0x3F) & ~0x3F);
        }
    } else {
        gVideoFramebuffers[index] = allocate_from_main_pool_safe((gVideoFbWidths[index] * gVideoFbHeights[index] * 2) + 0x30, COLOUR_TAG_WHITE);
        gVideoFramebuffers[index] = (u16 *)(((s32)gVideoFramebuffers[index] + 0x3F) & ~0x3F);
        if (gVideoDepthBuffer == NULL) {
            gVideoDepthBuffer = allocate_from_main_pool_safe((gVideoFbWidths[index] * gVideoFbHeights[index] * 2) + 0x30, COLOUR_TAG_WHITE);
            gVideoDepthBuffer = (u16 *)(((s32)gVideoDepthBuffer + 0x3F) & ~0x3F);
        }
    }
}

void func_8007A974(void) {
    D_80126308 = 0;
    D_80126309 = 2;
}

//#ifdef NON_EQUIVALENT
// regalloc & stack issues
s32 func_8007A98C(s32 arg0) {
    s32 tempUpdateRate;

#if NUM_FRAMEBUFFERS == 2
    tempUpdateRate = LOGIC_60FPS;
    if (D_801262D0 != 0) {
        D_801262D0--;
        if (D_801262D0 == 0) {
            osViBlack(FALSE);
        }
    }
    if (arg0 != 8) {
        swap_framebuffers();
    }
    while (osRecvMesg(&gVideoMesgQueue, NULL, OS_MESG_NOBLOCK) != -1) {
        tempUpdateRate += 1;
        tempUpdateRate &= 0xFF;
    }

    if (tempUpdateRate < D_80126309) {
        if (D_80126308 < 0x14) {
            D_80126308++;
        }
        if (D_80126308 == 0x14) {
            D_80126309 = tempUpdateRate;
            D_80126308 = 0;
        }
    } else {
        D_80126308 = 0;
        if ((D_80126309 >= tempUpdateRate) || (D_801262E4 > tempUpdateRate)) {
            D_80126309 = tempUpdateRate;
        }
    }
    while (tempUpdateRate < D_80126309) {
        osRecvMesg(&gVideoMesgQueue, NULL, OS_MESG_BLOCK);
        tempUpdateRate += 1;
        tempUpdateRate &= 0xFF;
    }
#else
    osRecvMesg(&gVideoMesgQueue, NULL, OS_MESG_BLOCK);
    osViBlack(FALSE);
    swap_framebuffers();
#endif
    osViSwapBuffer(gVideoLastFramebuffer);
#if NUM_FRAMEBUFFERS == 2
    osRecvMesg(&gVideoMesgQueue, NULL, OS_MESG_BLOCK);
#endif
    return tempUpdateRate;
}
/*#else
GLOBAL_ASM("asm/non_matchings/video/func_8007A98C.s")
#endif*/

void func_8007AB24(s8 arg0) {
    D_801262E4 = arg0;
}

/**
 * Unused function that returns the refresh rate, after performance.
 * A fully performant game would return 60.
 * Perhaps may have been used originally to calculate the factor in which to handle frameskipping with.
 */
UNUSED s32 get_video_refresh_speed(void) {
    return (s32)((f32)gVideoRefreshRate / (f32)D_80126309);
}

/**
 * Flips the current framebuffer index, swapping to the other framebuffer
 * for the next frame, then update the current and previous framebuffer pointers.
 */
void swap_framebuffers(void) {
    gVideoLastFramebuffer = gVideoFramebuffers[gVideoCurrFbIndex];
    gVideoLastDepthBuffer = gVideoDepthBuffer;
    gVideoCurrFbIndex++;
    if (gVideoCurrFbIndex == NUM_FRAMEBUFFERS) {
        gVideoCurrFbIndex = 0;
    }
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
