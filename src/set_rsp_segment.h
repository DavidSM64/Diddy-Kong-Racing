#ifndef _SET_RSP_SEGMENT_H_
#define _SET_RSP_SEGMENT_H_

#include "PR/gbi.h"

/**
 * Normally, in F3D, RSP segments go up to 16.
 * DKR's custom microcode is an exception, capping at 8.
 * A DMEM saving measure, since they don't use segments for assets.
*/
enum RSPSegments {
    SEGMENT_MAIN,
    SEGMENT_FRAMEBUFFER,
    SEGMENT_ZBUFFER,
    SEGMENT_UNUSED_3,
    SEGMENT_FRAMEBUFFER_OFFSET, // Also unused

    SEGMENT_COUNT,
};

void rsp_segment(Gfx **dlist, s32 segment, s32 base);

#endif
