#include "rmonPrintf.h"
#include "types.h"
#include "macros.h"
#include "stdarg.h"
#include "xprintf.h"

/**
 * This gets called inside of _PrintF, but it is just a fake pointer returned
 */
static char *proutSyncPrintf(UNUSED char *str, UNUSED const char *buf, UNUSED size_t n) {
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
    _Printf(proutSyncPrintf, NULL, format, args);
    va_end(args);
}
