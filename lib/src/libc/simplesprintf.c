/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C9D40 */

#include "simplesprintf.h"
#include "types.h"
#include "macros.h"
#include "stdarg.h"
#include "xprintf.h"

/**
 * This gets called inside of _PrintF, but it is just hardcoded to return true.
 */
char *prout_simple_sprintf(char *dst, const char *src, size_t count) {
    return TRUE;
}

/**
 * Like sprintf, but simpler. It just hardcodes 0 for the dst,
 * and calls a function that just hardcodes a return of TRUE.
 */
s32 simple_sprintf(const char *format, ...) {
    s32 written;
    va_list args;
    va_start(args, format);
    written =  _Printf(prout_simple_sprintf, 0, format, args);
    va_end(args);

    return written;
}
