#ifndef _SIMPLESPRINTF_H_
#define _SIMPLESPRINTF_H_
#include "types.h"
#include <stdarg.h>

char *prout_simple_sprintf(char *dst, const char *src, size_t count);
s32 simple_sprintf(const char *format, ...);

#endif
