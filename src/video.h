#ifndef _VIDEO_H_
#define _VIDEO_H_

#include "types.h"
#include "macros.h"
#include "memory.h"
#include "PR/libultra.h"
#include "PR/os_message.h"
#include "PR/os_vi.h"
#include "sched.h"

#define REFRESH_50HZ 50
#define REFRESH_60HZ 60

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define HIGH_RES_SCREEN_WIDTH 640
#define HIGH_RES_SCREEN_HEIGHT 480

#define LOW_RES_WIDTH 320.0f
#define LOW_RES_PAL_HEIGHT 264.0f
#define LOW_RES_NTSC_HEIGHT 240.0f
#define LOW_RES_MPAL_HEIGHT LOW_RES_NTSC_HEIGHT

#define PAL_HEIGHT_DIFFERENCE 24

#define ASPECT_RATIO_PAL  (LOW_RES_WIDTH / LOW_RES_PAL_HEIGHT)
#define ASPECT_RATIO_NTSC (LOW_RES_WIDTH / LOW_RES_NTSC_HEIGHT)
#define ASPECT_RATIO_MPAL (LOW_RES_WIDTH / LOW_RES_MPAL_HEIGHT)

#define HEIGHT_RATIO_PAL  (LOW_RES_PAL_HEIGHT / LOW_RES_NTSC_HEIGHT)
#define HEIGHT_RATIO_NTSC (LOW_RES_NTSC_HEIGHT / LOW_RES_NTSC_HEIGHT)
#define HEIGHT_RATIO_MPAL (LOW_RES_MPAL_HEIGHT / LOW_RES_NTSC_HEIGHT)

/**
 * The video width is the lower 16 bits of the returned 32 bit value
 */
#define GET_VIDEO_WIDTH(width_and_height) (width_and_height & 0xFFFF)
/**
 * The video width is the higher 16 bits of the returned 32 bit value
 */
#define GET_VIDEO_HEIGHT(width_and_height) (width_and_height >> 16)

/**
 * Values for the rate game logic will work depending on the framerate. Vanilla DKR will default to LOGIC_30FPS (2)
 */

enum LogicUpdateRates {
    LOGIC_NULL,
    LOGIC_60FPS,
    LOGIC_30FPS,
    LOGIC_20FPS,
    LOGIC_15FPS,
    LOGIC_12FPS,
    LOGIC_10FPS,
    LOGIC_5FPS = 12
};

enum VideoModes {
    VIDEO_MODE_LOWRES_LAN,
    VIDEO_MODE_LOWRES_LPN,
    VIDEO_MODE_MEDRES_LPN,
    VIDEO_MODE_MEDRES_LAN,
    VIDEO_MODE_HIGHRES_HPN,
    VIDEO_MODE_HIGHRES_HAN,
    VIDEO_MODE_HIGHRES_HPF,
    VIDEO_MODE_HIGHRES_HAF,

    VIDEO_MODE_LOWRES_MASK = 0,
    VIDEO_MODE_MIDRES_MASK = 2,
    VIDEO_MODE_HIGHRES_MASK = 4
};

extern s32 gVideoRefreshRate;
extern f32 gVideoAspectRatio;
extern u16 *gVideoDepthBuffer;
extern u16 *gVideoCurrFramebuffer;
extern u16 *gVideoLastFramebuffer;
extern u16 *gVideoCurrDepthBuffer;
extern u16 *gVideoLastDepthBuffer;

extern OSViMode osViModeNtscLpn1, osViModePalLpn1, osViModeMpalLpn1, osViModePalLan1, osViModeNtscLan1, osViModeMpalLan1;

/* Size: 0x08 bytes */
typedef struct VideoModeResolution {
    /* 0x00 */ s32 width;
    /* 0x04 */ s32 height;
} VideoModeResolution;

extern VideoModeResolution gVideoModeResolutions[8];

void init_video(s32 videoModeIndex, OSSched *sc);
void set_video_mode_index(s32 videoModeIndex);
s32 get_video_width_and_height_as_s32(void);
void init_vi_settings(void);
void init_framebuffer(s32 index);
void reset_video_delta_time(void);
void func_8007AB24(u8 arg0);
s32 get_video_refresh_speed(void);
void swap_framebuffers(void);
void memory_copy(u8 *src, u8 *dest, s32 len);
s32 swap_framebuffer_when_ready(s32 mesg);

#endif
