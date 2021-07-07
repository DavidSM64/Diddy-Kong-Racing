#ifndef _UNKNOWN_07AF10_H_
#define _UNKNOWN_07AF10_H_

#include "types.h"

#define REFRESH_50HZ 50
#define REFRESH_60HZ 60

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

#endif
