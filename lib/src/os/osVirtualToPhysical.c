/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C8CF0 */

#include "libultra_internal.h"
#include "osint.h"

u32 osVirtualToPhysical(void *addr) {
    if (IS_KSEG0(addr)) {
        return K0_TO_PHYS(addr);
    } else if (IS_KSEG1(addr)) {
        return K1_TO_PHYS(addr);
    } else {
        return __osProbeTLB(addr);
    }
}
