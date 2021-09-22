/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D3820 */

#include "types.h"
#include "macros.h"

//TODO: This probably belongs somewhere else
s32 D_800E48A0[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

void alCopy(void *src, void *dest, s32 len) {
    s32  i;
    u8 *s = (u8 *)src;
    u8 *d = (u8 *)dest;

    for (i = 0; i < len; i++) {
        *d++ = *s++;
    }
}
