/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C9D40 */

#include "types.h"
#include "macros.h"
#include "stdarg.h"

s32 get_true(s32 arg0, s32 arg1, s32 arg2) {
    return TRUE;
}

void func_800C9D54(const char *format, ...) {
    va_list args;
    va_start(args, format);
    _Printf(get_true, 0, format, args);
}
