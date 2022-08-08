/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D38A0 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"
#include <stdarg.h>
#include <string.h>
#include "xprintf.h"

const char length_str[] = "hlL";
const char flags_str[] = " +-#0";
const u32 flags_arr[] = { FLAGS_SPACE, FLAGS_PLUS, FLAGS_MINUS, FLAGS_HASH, FLAGS_ZERO, 0 };
char _spaces[] = "                                ";
char _zeroes[] = "00000000000000000000000000000000";

static void _Putfld(printf_struct *a0, va_list *args, u8 type, u8 *buff);
s32 _Printf(outfun prout, char *dst, const char *fmt, va_list args) {
    printf_struct x;
    const u8 *fmt_ptr;
    u8 c;
    const char *flag_index;
    u8 ac[0x20]; // probably a buffer?
    x.size = 0;
    while (TRUE) {
        fmt_ptr = (u8 *) fmt;
        while ((c = *fmt_ptr++) > 0) {
            if (c == '%') {
                fmt_ptr--;
                break;
            }
        }
        _PROUT(fmt, fmt_ptr - (u8 *) fmt);
        if (c == 0) {
            return x.size;
        }
        fmt = (char *) ++fmt_ptr;
        x.flags = 0;
        for (; (flag_index = strchr(flags_str, *fmt_ptr)) != NULL; fmt_ptr++) {
            x.flags |= flags_arr[flag_index - flags_str];
        }
        if (*fmt_ptr == '*') {
            x.width = va_arg(args, s32);
            if (x.width < 0) {
                x.width = -x.width;
                x.flags |= FLAGS_MINUS;
            }
            fmt_ptr++;
        } else {
            ATOI(x.width, fmt_ptr);
        }
        if (*fmt_ptr != '.') {
            x.precision = -1;
        } else {
            fmt_ptr++;
            if (*fmt_ptr == '*') {
                x.precision = va_arg(args, s32);
                fmt_ptr++;
            } else {
                ATOI(x.precision, fmt_ptr);
            }
        }
        if (strchr(length_str, *fmt_ptr) != NULL) {
            x.length = *fmt_ptr++;
        } else {
            x.length = 0;
        }

        if (x.length == 'l' && *fmt_ptr == 'l') {
            x.length = 'L';
            fmt_ptr++;
        }
        _Putfld(&x, (va_list *)&args, *fmt_ptr, ac);
        x.width -= x.n0 + x.num_leading_zeros + x.part2_len + x.num_mid_zeros
                      + x.part3_len + x.num_trailing_zeros;
        if (!(x.flags & FLAGS_MINUS))
            _PAD(_spaces, x.width);
        _PROUT((char *) ac, x.n0);
        _PAD(_zeroes, x.num_leading_zeros);
        _PROUT(x.buff, x.part2_len);
        _PAD(_zeroes, x.num_mid_zeros);
        _PROUT((char *) (&x.buff[x.part2_len]), x.part3_len)
        _PAD(_zeroes, x.num_trailing_zeros);
        if (x.flags & FLAGS_MINUS)
            _PAD(_spaces, x.width);
        fmt = (char *) fmt_ptr + 1;
    }
}

static void _Putfld(printf_struct *a0, va_list *args, u8 type, u8 *buff) {
    a0->n0 = a0->num_leading_zeros = a0->part2_len = a0->num_mid_zeros = a0->part3_len =
        a0->num_trailing_zeros = 0;

    switch (type) {

        case 'c':
            buff[a0->n0++] = va_arg(*args, u32);
            break;

        case 'd':
        case 'i':
            if (a0->length == 'l') {
                a0->value.s64 = va_arg(*args, s32);
            } else if (a0->length == 'L') {
                a0->value.s64 = va_arg(*args, s64);
            } else {
                a0->value.s64 = va_arg(*args, s32);
            }

            if (a0->length == 'h') {
                a0->value.s64 = (s16) a0->value.s64;
            }

            if (a0->value.s64 < 0) {
                buff[a0->n0++] = '-';
            } else if (a0->flags & FLAGS_PLUS) {
                buff[a0->n0++] = '+';
            } else if (a0->flags & FLAGS_SPACE) {
                buff[a0->n0++] = ' ';
            }

            a0->buff = (char *) &buff[a0->n0];

            _Litob(a0, type);
            break;

        case 'x':
        case 'X':
        case 'u':
        case 'o':
            if (a0->length == 'l') {
                a0->value.s64 = va_arg(*args, s32);
            } else if (a0->length == 'L') {
                a0->value.s64 = va_arg(*args, s64);
            } else {
                a0->value.s64 = va_arg(*args, s32);
            }

            if (a0->length == 'h') {
                a0->value.s64 = (u16) a0->value.s64;
            } else if (a0->length == 0) {
                a0->value.s64 = (u32) a0->value.s64;
            }

            if (a0->flags & FLAGS_HASH) {
                buff[a0->n0++] = '0';
                if (type == 'x' || type == 'X') {

                    buff[a0->n0++] = type;
                }
            }
            a0->buff = (char *) &buff[a0->n0];
            _Litob(a0, type);
            break;

        case 'e':
        case 'f':
        case 'g':
        case 'E':
        case 'G':
            //... okay?
            a0->value.f64 = a0->length == 'L' ? va_arg(*args, f64) : va_arg(*args, f64);

            if (LDSIGN(a0->value.f64)) {
                buff[a0->n0++] = '-';
            } else {
                if (a0->flags & FLAGS_PLUS) {
                    buff[a0->n0++] = '+';
                } else if (a0->flags & FLAGS_SPACE) {
                    buff[a0->n0++] = ' ';
                }
            }

            a0->buff = (char *) &buff[a0->n0];
            _Ldtob(a0, type);
            break;

        case 'n':
            if (a0->length == 'h') {
                *(va_arg(*args, u16 *)) = a0->size;
            } else if (a0->length == 'l') {
                *va_arg(*args, u32 *) = a0->size;
            } else if (a0->length == 'L') {
                *va_arg(*args, u64 *) = a0->size;
            } else {
                *va_arg(*args, u32 *) = a0->size;
            }
            break;

        case 'p':
            a0->value.s64 = (long) va_arg(*args, void *);
            a0->buff = (char *) &buff[a0->n0];
            _Litob(a0, 'x');
            break;

        case 's':
            a0->buff = va_arg(*args, char *);
            a0->part2_len = strlen(a0->buff);
            if (a0->precision >= 0 && a0->part2_len > a0->precision) {
                a0->part2_len = a0->precision;
            }
            break;

        case '%':
            buff[a0->n0++] = '%';
            break;

        default:
            buff[a0->n0++] = type;
            break;
    }
}
