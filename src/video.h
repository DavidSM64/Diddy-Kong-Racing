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

/* Size: 0x08 bytes */
typedef struct VideoModeResolution {
    /* 0x00 */ s32 width;
    /* 0x04 */ s32 height;
} VideoModeResolution;

extern VideoModeResolution gVideoModeResolutions[8];

extern s32 D_800DE7BC;

s32 func_8007A98C(s32 arg0);

#endif
