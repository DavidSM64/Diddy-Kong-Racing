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
s32 func_800314DC(LevelModelSegmentBoundingBox *segment, s32 x1, s32 z1, s32 x2, s32 z2) {
    s32 v0 = 0;
    s32 v1;
    s32 t0, t1, t2, t3, t4;

    if (segment == NULL) {
        return v0;
    }

    t0 = segment->x1;
    t1 = segment->z1;
    t2 = segment->x2;
    t3 = segment->z2;

    if (x2 < t0) {
        x2 = t0;
    }

    if (x1 < t0) {
        x1 = t0;
    }

    if (z2 < t1) {
        z2 = t1;
    }

    if (z1 < t1) {
        z1 = t1;
    }

    if (t2 < x2) {
        x2 = t2;
    }

    if (t2 < x1) {
        x1 = t2;
    }

    if (t3 < z2) {
        z2 = t3;
    }

    if (t3 < z1) {
        z1 = t3;
    }

    v1 = 1;

    t2 = ((t2 - t0) >> 3) + 1;
    t4 = t2 + t0;

    while (v1 < (1 << 8)) {
        if (t4 >= x1 && x2 >= t0) {
            v0 |= v1;
        }

        v1 <<= 1;
        t4 += t2;
        t0 += t2;
    }

    t2 = ((t3 - t1) >> 3) + 1;
    t4 = t2 + t1;

    while (v1 < (1 << 16)) {
        if (t4 >= z1 && z2 >= t1) {
            v0 |= v1;
        }

        v1 <<= 1;
        t4 += t2;
        t1 += t2;
    }

    return v0;
}
#else
GLOBAL_ASM("asm/collision/func_800314DC.s")
#endif

// Player collision for the current segment
GLOBAL_ASM("asm/collision/func_80031600.s")
