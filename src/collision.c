/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80031130 */

#include "collision.h"

#include "types.h"
#include "macros.h"

/*******************************/

// All handwritten assembly, below.

// Collision for a different segment
GLOBAL_ASM("asm/collision/func_80031130.s")
// Might be segment related.
#ifdef NON_EQUIVALENT
void func_800314DC(LevelModelSegmentBoundingBox* segment, s32 x1, s32 z1, s32 x2, s32 z2) {
    s32 segDiff;
    s32 segMin;
    s32 i;

    if (segment != NULL) {
        if (x2 < segment->x1) {
            x2 = segment->x1;
        }
        if (x1 < segment->x1) {
            x1 = segment->x1;
        }
        if (z2 < segment->z1) {
            z2 = segment->z1;
        }
        if (z1 < segment->z1) {
            z1 = segment->z1;
        }
        if (segment->x2 < x2) {
            x2 = segment->x2;
        }
        if (segment->x2 < x1) {
            x1 = segment->x2;
        }
        if (segment->z2 < z2) {
            z2 = segment->z2;
        }
        if (segment->z2 < z1) {
            z1 = segment->z2;
        }
        segDiff = ((segment->x2 - segment->x1) >> 3) + 1;
        segMin = segDiff + segment->x1;
        for (i = 0; i < 8; i++) {
            if (segMin >= x1 && x2 >= segment->x1) {
                segMin += segDiff;
                segment->x1 += segDiff;
            }
        }
        segDiff = ((segment->z2 - segment->z1) >> 3) + 1;
        segMin = segDiff + segment->z1;
        for (i = 0; i < 8; i++) {
            if (segMin >= z1 && z2 >= segment->z1) {
                segMin += segDiff;
                segment->z1 += segDiff;
            }
        }
    }
}
#else
GLOBAL_ASM("asm/collision/func_800314DC.s")
#endif
// Player collision for the current segment
GLOBAL_ASM("asm/collision/func_80031600.s")
