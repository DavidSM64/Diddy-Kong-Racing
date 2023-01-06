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
s32 func_800314DC(LevelModelSegmentBoundingBox *a0, s32 a1, s32 a2, s32 a3, s32 t5) {
    s32 v0 = 0;
    s32 v1;
    s32 t0, t1, t2, t3, t4;

    if (a0 == NULL)
        return v0;

    t0 = a0->x1;
    t1 = a0->z1;
    t2 = a0->x2;
    t3 = a0->z2;

    if (a3 < t0)
        a3 = t0;

    if (a1 < t0)
        a1 = t0;

    if (t5 < t1)
        t5 = t1;

    if (a2 < t1)
        a2 = t1;

    if (t2 < a3)
        a3 = t2;

    if (t2 < a1)
        a1 = t2;

    if (t3 < t5)
        t5 = t3;

    if (t3 < a2)
        a2 = t3;

    v1 = 1;

    t2 = ((t2 - t0) >> 3) + 1;
    t4 = t2 + t0;

    while (v1 < (1 << 8)) {
        if (t4 >= a1 && a3 >= t0)
            v0 |= v1;

        v1 <<= 1;
        t4 += t2;
        t0 += t2;
    }

    t2 = ((t3 - t1) >> 3) + 1;
    t4 = t2 + t1;

    while (v1 < (1 << 16)) {
        if (t4 >= a2 && t5 >= t1)
            v0 |= v1;

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
