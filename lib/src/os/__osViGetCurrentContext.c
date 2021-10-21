/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D6080 */

#include "libultra_internal.h"
#include "viint.h"

__OSViContext *__osViGetCurrentContext(void){
    return __osViCurr;
}
