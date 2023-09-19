/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B4710 */

#include "types.h"
#include "macros.h"

UNUSED char *strcpy(char *src, const char *dest) {
    char *ret = src;

    while ((*src++ = *dest++));
    return ret;
}

UNUSED char *strcat(char *dest, const char *src) {
    char *ret = dest;
    
    while (*dest) dest++;
    while ((*dest++ = *src++));
    
    return ret;
}

GLOBAL_ASM("asm/non_matchings/unused_string/strcasecmp.s")

/**
 * memset(void *s, int c, size_t n)
 *
 * s: start of area to clear
 * c: char to fill with
 * n: size of area to clear
 */
UNUSED void *memset(void *s, int c, size_t n) {
    u8 *var_v0 = s;

    while (n-- > 0) {
        *var_v0++ = c;
    }
    return s;
}