/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CD260 */

#include "libultra_internal.h"

extern OSTime __osCurrentTime;

void osSetTime(OSTime time) {
    __osCurrentTime = time;
}
