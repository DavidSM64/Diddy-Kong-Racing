/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8007A2D0 */

#include "set_rsp_segment.h"
#include "PR/mbi.h"
#include "PR/gbi.h"
#include "PR/R4300.h"

/**
 * Set the offset for the given address, so the RSP can get the correct physical address.
 * This is used for the colour and depth buffers.
 */
void set_rsp_segment(Gfx **dlist, s32 segment, void *base) {
    gSPSegment((*dlist)++, segment, (s32) base + K0BASE)
}
