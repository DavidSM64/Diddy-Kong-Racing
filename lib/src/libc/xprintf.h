#ifndef _XPRINTF_H_
#define _XPRINTF_H_
#include "types.h"
#include <stdarg.h>

char *prout_xprintf(char *dst, const char *src, size_t count);
s32 xprintf(const char *format, ...);

#endif
