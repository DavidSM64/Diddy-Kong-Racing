/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C7340 */

#include "types.h"

// Used for __osException, but .bss file order is weird. Need to fix later.
u8 leoDiskStack[16]; // technically should have a OS_LEO_STACKSIZE or something.
                     // This is something like 4096 in libreultra...

//This has been blanked out for some reason
s32 __osLeoInterrupt(void) {
    return 0;
}
