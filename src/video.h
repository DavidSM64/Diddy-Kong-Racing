#ifndef _VIDEO_H_
#define _VIDEO_H_

#include "types.h"
#include "macros.h"
#include "memory.h"
#include "PR/libultra.h"
#include "PR/os_message.h"
#include "PR/os_vi.h"
#include "lib/src/mips1/sc/sched.h"

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

extern s32 gVideoRefreshRate;

extern u16 *gVideoDepthBuffer;
extern s32 D_800DE774;
extern s8  D_800DE778;

extern OSViMode D_800E4620, D_800E4670, D_800E46C0, D_800E4760, D_800E4710, D_800E47B0;

/* Size: 0x08 bytes */
typedef struct VideoModeResolution {
    /* 0x00 */ s32 width;
    /* 0x04 */ s32 height;
} VideoModeResolution;

extern VideoModeResolution gVideoModeResolutions[8];

extern s32 D_800DE7BC;

void init_video(s32 videoModeIndex, OSSched *sc);
void set_video_mode_index(s32 videoModeIndex);
s32 get_video_mode_index(void);
void set_video_width_and_height_from_index(s32 fbIndex);
s32 get_video_width_and_height_as_s32(void);
void init_vi_settings(void);
void init_framebuffer(s32 index);
void func_8007A974(void);
void func_8007AB24(s8 arg0);
s32 func_8007AB34(void);
void swap_framebuffers(void);

//Non Matching
void memory_copy(u8 *src, u8 *dst, s32 numBytes);
s32 func_8007A98C(s32 arg0);

#endif
