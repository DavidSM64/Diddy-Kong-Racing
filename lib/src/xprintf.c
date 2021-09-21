/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C9D40 */

#include "xprintf.h"
#include "types.h"
#include "macros.h"
#include "stdarg.h"
#include "printf.h"

char *prout_xprintf(char *dst, const char *src, size_t count) {
    return TRUE;
}

s32 xprintf(const char *format, ...) {
    s32 written;
    va_list args;
    va_start(args, format);
    written =  _Printf(prout_xprintf, 0, format, args);
    va_end(args);

    return written;
}
