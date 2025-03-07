#ifndef _XPRINTF_H_
#define _XPRINTF_H_
#include "types.h"
#include <stdarg.h>

/**
 * This is a definition for a function that gets passed to and
 * will get called inside _PrintF
 */
typedef char *outfun(char *dst, const char *src, size_t count);
typedef struct {
    union {
        /* 00 */ long long s64;
        double f64;
    } value;
    /* 08 */ char *buff;
    /* 0c */ int n0;
    /* 10 */ int num_leading_zeros;
    /* 14 */ int part2_len;
    /* 18 */ int num_mid_zeros;
    /* 1c */ int part3_len;
    /* 20 */ int num_trailing_zeros;
    /* 24 */ int precision;
    /* 28 */ int width;
    /* 2c */ unsigned int size;
    /* 30 */ unsigned int flags;
    /* 34 */ unsigned char length;
} printf_struct;

#define isdigit(x) ((x >= '0' && x <= '9'))
#define LDSIGN(x) (((unsigned short *)&(x))[0] & 0x8000)
#define ATOI(dst, src)                                        \
    for (dst = 0; isdigit(*src); ++src)  {                    \
        if (dst < 999)                                        \
            dst = dst * 10 + *src - '0';                      \
    }
#define _PROUT(fmt, _size)                                    \
    if (_size > 0) {                                          \
        dst = (*prout)(dst, fmt, _size);                      \
        if (dst != 0)                                         \
            x.size += _size;                                  \
        else                                                  \
            return x.size;                                    \
    }
#define MAX_PAD ((sizeof(_spaces) - 1))
#define _PAD(s, n)                                            \
    if (0 < (n)) {                                            \
        int i, j = (n);                                       \
        for (; 0 < j; j -= i) {                               \
            i = MAX_PAD < (unsigned int)j ? (int)MAX_PAD : j; \
            _PROUT(s, i);                                     \
        }                                                     \
    }
#define FLAGS_SPACE 1
#define FLAGS_PLUS  2
#define FLAGS_MINUS 4
#define FLAGS_HASH  8
#define FLAGS_ZERO  16
s32 _Printf(outfun prout, char *dst, const char *fmt, va_list args);
void _Litob(printf_struct *args, char type);
void _Ldtob(printf_struct *args, u8 type);
#endif
