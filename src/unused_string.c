/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B4710 */

#include "types.h"
#include "macros.h"

/**
 * Copy a string to a given location.
 * Return the address of the destrination.
 */
UNUSED char *strcpy(char *src, const char *dest) {
    char *ret = src;

    while ((*src++ = *dest++) != '\0') {}
    return ret;
}

/**
 * Append a string to the end of a given string.
 * Return the address of the destrination.
 */
UNUSED char *strcat(char *dest, const char *src) {
    char *ret = dest;

    while (*dest != '\0') {
        dest++;
    }
    while ((*dest++ = *src++) != '\0') {}

    return ret;
}

/**
 * Compare two strings, with no case sensitivity.
 * Return zero if they match.
 */
UNUSED int strcasecmp(const char *s1, const char *s2) {
    unsigned char c1;
    unsigned char c2;

    while (*s1 || *s2) {
        c1 = *s1;

        if (c1 >= 'a' && c1 <= 'z') {
            c1 -= 0x20;
        }

        c2 = *s2;

        if (c2 >= 'a' && c2 <= 'z') {
            c2 -= 0x20;
        }

        if (c1 < c2) {
            return -1;
        }

        if (c2 < c1) {
            return 1;
        }

        s1++;
        s2++;
    }

    return 0;
}

/**
 * Compare an arbitrary amount of characters in two strings, with no case sensitivity.
 * Return zero if they match.
 */
UNUSED int strncasecmp(const char *s1, const char *s2, size_t n) {
    unsigned char c1;
    unsigned char c2;

    while ((*s1 || *s2) && n) {
        c1 = *s1;

        if (c1 >= 'a' && c1 <= 'z') {
            c1 -= 0x20;
        }

        c2 = *s2;

        if (c2 >= 'a' && c2 <= 'z') {
            c2 -= 0x20;
        }

        if (c1 < c2) {
            return -1;
        }

        if (c2 < c1) {
            return 1;
        }

        s1++;
        s2++;
        n--;
    }

    return 0;
}

/**
 * memset(void *s, int c, size_t n)
 *
 * s: start of area to clear
 * c: char to fill with
 * n: size of area to clear
 */
UNUSED void *memset(void *s, int c, size_t n) {
    unsigned char *ret = s;

    while (n-- > 0) {
        *ret++ = c;
    }
    return s;
}
