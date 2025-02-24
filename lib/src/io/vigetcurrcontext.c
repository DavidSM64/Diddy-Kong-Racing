/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D6080 */

#include "PR/os_internal.h"
#include "PRinternal/viint.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

__OSViContext* __osViGetCurrentContext(void) {
    return __osViCurr;
}
