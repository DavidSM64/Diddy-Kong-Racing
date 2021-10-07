/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8007A2D0 */

#include "set_rsp_segment.h"
#include "PR/mbi.h"
#include "PR/gbi.h"
#include "PR/R4300.h"

void set_rsp_segment(Gfx **dlist, s32 segment, s32 base) {
    gSPSegment((*dlist)++, segment, base + K0BASE)
}
