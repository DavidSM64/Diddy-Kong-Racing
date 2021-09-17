/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8007A310 */

#include "video.h"

/************ .data ************/

u16 *gVideoDepthBuffer = NULL;
s32 D_800DE774 = 0; // Currently unknown, might be a different type.
s8  D_800DE778 = 2;

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
OSMesg D_80126180[8];
OSMesgQueue D_801261A0[8];
OSViMode D_80126260;
s32 gVideoFbWidths[2];
s32 gVideoFbHeights[2];
u16 *gVideoFramebuffers[2];
s32 gVideoCurrFbIndex;
s32 gVideoModeIndex;
s32 D_801262D0;
u16 *gVideoCurrFramebuffer;
u16 *gVideoLastFramebuffer;
u16 *gVideoCurrDepthBuffer;
u16 *gVideoLastDepthBuffer;
u8 D_801262E4;
s32 D_801262E8[8];
u8  D_80126308;
u8  D_80126309;
s32 D_8012630C;
OSScClient *D_80126310;

/******************************/

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
        for(i = 0; i < 8; i++) {
            gVideoModeResolutions[i].height += PAL_HEIGHT_DIFFERENCE;
        }
    }
    
    func_8007A974();
    set_video_mode_index(videoModeIndex);
    gVideoFramebuffers[0] = 0;
    gVideoFramebuffers[1] = 0;
    init_framebuffer(0);
    init_framebuffer(1);
    gVideoCurrFbIndex = 1;
    swap_framebuffers();
    osCreateMesgQueue(&D_801261A0, &D_80126180, 8);
    osScAddClient(sc, &D_80126310, &D_801261A0, 2);
    init_vi_settings();
    D_801262D0 = 12;
    osViBlack(1);
    D_80126308 = 0;
    D_801262E4 = 3;
}

void set_video_mode_index(s32 videoModeIndex) {
    gVideoModeIndex = videoModeIndex;
}

/* Unused? */
s32 get_video_mode_index(void) {
    return gVideoModeIndex;
}

/* Unused? */
void set_video_width_and_height_from_index(s32 fbIndex) {
    gVideoFbWidths[fbIndex] = gVideoModeResolutions[gVideoModeIndex & 7].width;
    gVideoFbHeights[fbIndex] = gVideoModeResolutions[gVideoModeIndex & 7].height;
}

s32 get_video_width_and_height_as_s32(void) {
    return (gVideoFbHeights[gVideoCurrFbIndex] << 16) | gVideoFbWidths[gVideoCurrFbIndex];
}

void init_vi_settings(void) {
    s32 viModeTableIndex;
    OSViMode *tvViMode;
    
    viModeTableIndex = OS_VI_NTSC_LPN1;
    if (osTvType == TV_TYPE_PAL) {
        viModeTableIndex = OS_VI_PAL_LPN1;
    } else if (osTvType == TV_TYPE_MPAL) {
        viModeTableIndex = OS_VI_MPAL_LPN1;
    }
    
    switch(gVideoModeIndex & 7) {
        case 0:
            stubbed_printf("320 by 240 Point sampled, Non interlaced.\n");
            osViSetMode(&osViModeTable[viModeTableIndex]);
            break;
        case 1:
            stubbed_printf("320 by 240 Anti-aliased, Non interlaced.\n");
            tvViMode = &D_800E4620;
            if (osTvType == TV_TYPE_PAL) {
                tvViMode = &D_800E4670;
            } else if (osTvType == TV_TYPE_MPAL) {
                tvViMode = &D_800E46C0;
            }
            memory_copy(tvViMode, &D_80126260, sizeof(OSViMode));
            if (osTvType == TV_TYPE_PAL) {
                D_80126260.fldRegs[0].vStart -= 0x180000;
                D_80126260.fldRegs[1].vStart -= 0x180000;
                D_80126260.fldRegs[0].vStart += 24;
                D_80126260.fldRegs[1].vStart += 24;
            }
            osViSetMode(&D_80126260);
            break;
        case 2:
            stubbed_printf("640 by 240 Point sampled, Non interlaced.\n");
            tvViMode = &D_800E4620;
            if (osTvType == TV_TYPE_PAL) {
                tvViMode = &D_800E4670;
            } else if (osTvType == TV_TYPE_MPAL) {
                tvViMode = &D_800E46C0;
            }
            
            memory_copy(tvViMode, &D_80126260, sizeof(OSViMode));
            D_80126260.comRegs.width = 0x280;
            D_80126260.comRegs.xScale = 0x400;
            D_80126260.fldRegs[0].origin = 0x500;
            D_80126260.fldRegs[1].origin = 0x500;
            osViSetMode(&D_80126260);
            break;
        case 3:
            stubbed_printf("640 by 240 Anti-aliased, Non interlaced.\n");
            tvViMode = &D_800E4710;
            if (osTvType == TV_TYPE_PAL) {
                tvViMode = &D_800E4760;
            } else if (osTvType == TV_TYPE_MPAL) {
                tvViMode = &D_800E47B0;
            }
            memory_copy(tvViMode, &D_80126260, sizeof(OSViMode));
            D_80126260.comRegs.width = 0x280;
            D_80126260.comRegs.xScale = 0x400;
            D_80126260.fldRegs[0].origin = 0x500;
            D_80126260.fldRegs[1].origin = 0x500;
            osViSetMode(&D_80126260);
            break;
        case 4:
            stubbed_printf("640 by 480 Point sampled, Interlaced.\n");
            osViSetMode(&osViModeTable[viModeTableIndex + 8]);
            break;
        case 5:
            stubbed_printf("640 by 480 Anti-aliased, Interlaced.\n");
            osViSetMode(&osViModeTable[viModeTableIndex + 10]);
            break;
        case 6:
            stubbed_printf("640 by 480 Point sampled, Interlaced, De-flickered.\n");
            osViSetMode(&osViModeTable[viModeTableIndex + 9]);
            break;
        case 7:
            stubbed_printf("640 by 480 Anti-aliased, Interlaced, De-flickered.\n");
            osViSetMode(&osViModeTable[viModeTableIndex + 11]);
            break;
    }
    osViSetSpecialFeatures(OS_VI_DIVOT_ON);
    osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON);
    osViSetSpecialFeatures(OS_VI_GAMMA_OFF);
}

void init_framebuffer(s32 index) {
    if (gVideoFramebuffers[index] != 0) {
        func_80071538(gVideoFramebuffers[index]);
        free_from_memory_pool(gVideoFramebuffers[index]);
    }
    gVideoFbWidths[index] = gVideoModeResolutions[gVideoModeIndex & 7].width;
    gVideoFbHeights[index] = gVideoModeResolutions[gVideoModeIndex & 7].height;
    if (gVideoModeIndex >= 2) {
        gVideoFramebuffers[index] = allocate_from_main_pool_safe((640 * 480 * 2) + 0x30, COLOR_TAG_WHITE);
        gVideoFramebuffers[index] = ((s32)gVideoFramebuffers[index] + 0x3F) & ~0x3F;
        if (gVideoDepthBuffer == NULL) {
            gVideoDepthBuffer = allocate_from_main_pool_safe((640 * 480 * 2) + 0x30, COLOR_TAG_WHITE);
            gVideoDepthBuffer = ((s32)gVideoDepthBuffer + 0x3F) & ~0x3F;
        }
    } else {
        gVideoFramebuffers[index] = allocate_from_main_pool_safe((gVideoFbWidths[index] * gVideoFbHeights[index] * 2) + 0x30, COLOR_TAG_WHITE);
        gVideoFramebuffers[index] = ((s32)gVideoFramebuffers[index] + 0x3F) & ~0x3F;
        if (gVideoDepthBuffer == NULL) {
            gVideoDepthBuffer = allocate_from_main_pool_safe((gVideoFbWidths[index] * gVideoFbHeights[index] * 2) + 0x30, COLOR_TAG_WHITE);
            gVideoDepthBuffer = ((s32)gVideoDepthBuffer + 0x3F) & ~0x3F;
        }
    }
    
}

void func_8007A974(void) {
    D_80126308 = 0;
    D_80126309 = 2;
}

#ifdef NON_MATCHING
// regalloc & stack issues
s32 func_8007A98C(s32 arg0) {
    s32 s0;

    s0 = 1;
    if (D_801262D0 != 0) {
        D_801262D0--;
        if (D_801262D0 == 0) {
            osViBlack(0);
        }
    }
    if (arg0 != 8) {
        swap_framebuffers();
    }
    while (osRecvMesg(&D_801261A0, NULL, 0) != -1) {
        s0 += 1;
        s0 &= 0xFF;
    }
    
    if (s0 < D_80126309) {
        if (D_80126308 < 0x14) {
            D_80126308++;
        }
        if (D_80126308 == 0x14) {
            D_80126309 = s0;
            D_80126308 = 0;
        }
    } else {
        D_80126308 = 0;
        if ((D_80126309 >= s0) || (D_801262E4 > s0)) {
            D_80126309 = s0;
        }
    }
    while (s0 < D_80126309) {
        osRecvMesg(&D_801261A0, NULL, 1);
        s0 += 1;
        s0 &= 0xFF;
    }
    osViSwapBuffer(gVideoLastFramebuffer);
    osRecvMesg(&D_801261A0, NULL, 1);
    return s0;
}
#else
GLOBAL_ASM("asm/non_matchings/video/func_8007A98C.s")
#endif

void func_8007AB24(s8 arg0) {
    D_801262E4 = arg0;
}

// Unused?
s32 func_8007AB34(void) {
    return (s32)((f32)gVideoRefreshRate / (f32)D_80126309);
}

void swap_framebuffers(void) {
    gVideoLastFramebuffer = gVideoFramebuffers[gVideoCurrFbIndex];
    gVideoLastDepthBuffer = gVideoDepthBuffer;
    gVideoCurrFbIndex ^= 1;
    gVideoCurrFramebuffer = gVideoFramebuffers[gVideoCurrFbIndex];
    gVideoCurrDepthBuffer = gVideoDepthBuffer;
}

#ifdef NON_MATCHING
// regalloc issues
void memory_copy(u8 *src, u8 *dst, s32 numBytes) {
    s32 i;
    for(i = 0; i < numBytes; i++){
        dst[i] = src[i];
    }
}
#else
GLOBAL_ASM("asm/non_matchings/video/memory_copy.s")
#endif


