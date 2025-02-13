/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8007A2D0 */

#include "set_rsp_segment.h"
#include "PR/mbi.h"
#include "PR/gbi.h"
#include "PR/R4300.h"

/**
 * Set the offset for the given address, so the RSP can get the correct physical address.
 * This is used for the colour and depth buffers.
 * Official name: segSetBase
 */
void rsp_segment(Gfx **dlist, s32 segment, s32 base) {
    gSPSegment((*dlist)++, segment, base + K0BASE)
}
