/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C9D40 */

#include "rmonPrintf.h"
#include "types.h"
#include "macros.h"
#include "stdarg.h"
#include "xprintf.h"

/**
 * This gets called inside of _PrintF, but it is just a fake pointer returned
 */
static char *is_proutSyncPrintf(UNUSED char *str, UNUSED const char *buf, UNUSED size_t n) {
    return ((char *) 1);   /* return a fake pointer so that it's not NULL */
}

/**
 * Like sprintf, but simpler. It just hardcodes NULL for the dst,
 * and calls a function that just hardcodes a fake pointer.
 * Could still be an earlier version of osSyncPrintf
 * Official name: osSyncPrintf
 */
void rmonPrintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    _Printf(is_proutSyncPrintf, NULL, format, args);
    va_end(args);
}
