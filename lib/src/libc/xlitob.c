
/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D6700 */

#include "macros.h"
#include "xprintf.h"
#include "stdlib.h"
#include "string.h"

#define BUFF_LEN 0x18

extern char ldigs[];
extern char udigs[];

void _Litob(printf_struct *args, char type) {
    char buff[BUFF_LEN];
    const char *digs;
    s32 base;
    s32 i;
    u64 us64val;

    if (type == 'X') {
        digs = udigs;
    } else {
        digs = ldigs;
    }

    base = (type == 'o') ? 8 : ((type != 'x' && type != 'X') ? 10 : 16);
    i = BUFF_LEN;
    us64val = args->value.s64;

    if ((type == 'd' || type == 'i') && args->value.s64 < 0) {
        us64val = -us64val;
    }

    if (us64val != 0 || args->precision != 0) {
        buff[--i] = digs[us64val % base];
    }

    args->value.s64 = us64val / base;

    while (args->value.s64 > 0 && i > 0) {
        lldiv_t qr = lldiv(args->value.s64, base);
        
        args->value.s64 = qr.quot;
        buff[--i] = digs[qr.rem];
    }

    args->part2_len = BUFF_LEN - i;

    memcpy(args->buff, buff + i, args->part2_len);

    if (args->part2_len < args->precision) {
        args->num_leading_zeros = args->precision - args->part2_len;
    }

    if (args->precision < 0 && (args->flags & (FLAGS_ZERO | FLAGS_MINUS)) == FLAGS_ZERO) {
        i = args->width - args->n0 - args->num_leading_zeros - args->part2_len;
        
        if (i > 0) {
            args->num_leading_zeros += i;
        }
    }
}
