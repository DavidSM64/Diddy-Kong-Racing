#include "printf.h"
#include "types.h"
#include "macros.h"
#include "f3ddkr.h"
#include "stdarg.h"
#include "libc/string.h"
#include "textures_sprites.h"
#include "rcp_dkr.h"

/************ .data ************/

s32 gSprintfSpacingCode = FALSE; // Used to determine if vsprintf should use fixed width mode or not

// Char width is (v - u) + 1
TexFontCoords gDebugFontCoords[3][32] = {
    // ASCII symbols and numbers
    // (This is out of order since they subtract 0x21 instead of 0x20)
    // !"#$%&'()*+,-./0123456789:;<=>?{SPACE}
    {
        { 0x02, 0x04 }, // !
        { 0x06, 0x08 }, // "
        { 0x0A, 0x0F }, // #
        { 0x11, 0x15 }, // $
        { 0x17, 0x1F }, // %
        { 0x21, 0x27 }, // &
        { 0x29, 0x2B }, // '
        { 0x2D, 0x2F }, // (
        { 0x31, 0x33 }, // )
        { 0x35, 0x38 }, // *
        { 0x3A, 0x3F }, // +
        { 0x41, 0x43 }, // ,
        { 0x45, 0x48 }, // -
        { 0x4A, 0x4B }, // .
        { 0x4D, 0x50 }, // /
        { 0x52, 0x56 }, // 0
        { 0x58, 0x5B }, // 1
        { 0x5D, 0x62 }, // 2
        { 0x64, 0x68 }, // 3
        { 0x6A, 0x6F }, // 4
        { 0x71, 0x76 }, // 5
        { 0x78, 0x7D }, // 6
        { 0x7F, 0x84 }, // 7
        { 0x86, 0x8B }, // 8
        { 0x8D, 0x92 }, // 9
        { 0x94, 0x96 }, // :
        { 0x98, 0x9A }, // ;
        { 0x9D, 0xA2 }, // <
        { 0xA5, 0xA9 }, // =
        { 0xAB, 0xB0 }, // >
        { 0xB3, 0xB8 }, // ?
        { 0x00, 0x01 }, // {SPACE}
    },
    // ASCII Upper Case
    // @ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_
    {
        { 0x00, 0x09 }, // @
        { 0x0B, 0x11 }, // A
        { 0x13, 0x19 }, // B
        { 0x1B, 0x21 }, // C
        { 0x23, 0x29 }, // D
        { 0x2B, 0x31 }, // E
        { 0x33, 0x38 }, // F
        { 0x3A, 0x41 }, // G
        { 0x43, 0x49 }, // H
        { 0x4B, 0x4C }, // I
        { 0x4E, 0x53 }, // J
        { 0x55, 0x5B }, // K
        { 0x5D, 0x62 }, // L
        { 0x64, 0x6B }, // M
        { 0x6D, 0x73 }, // N
        { 0x75, 0x7B }, // O
        { 0x7D, 0x83 }, // P
        { 0x85, 0x8B }, // Q
        { 0x8D, 0x93 }, // R
        { 0x95, 0x9B }, // S
        { 0x9D, 0xA3 }, // T
        { 0xA5, 0xAA }, // U
        { 0xAC, 0xB2 }, // V
        { 0xB4, 0xBC }, // W
        { 0xBE, 0xC4 }, // X
        { 0xC6, 0xCC }, // Y
        { 0xCE, 0xD3 }, // Z
        { 0xD5, 0xD7 }, // [
        { 0xD9, 0xDC }, // {backslash}
        { 0xDE, 0xE0 }, // ]
        { 0xE2, 0xE7 }, // ^
        { 0xE9, 0xEF }, // _
    },
    // ASCII Lower Case
    // `abcdefghijklmnopqrstuvwxyz{|}~
    {
        { 0x00, 0x01 }, // `
        { 0x03, 0x08 }, // a
        { 0x09, 0x0F }, // b
        { 0x11, 0x16 }, // c
        { 0x18, 0x1D }, // d
        { 0x1F, 0x24 }, // e
        { 0x26, 0x28 }, // f
        { 0x2A, 0x2F }, // g
        { 0x31, 0x36 }, // h
        { 0x38, 0x39 }, // i
        { 0x3B, 0x3D }, // j
        { 0x3F, 0x43 }, // k
        { 0x45, 0x46 }, // l
        { 0x48, 0x4F }, // m
        { 0x51, 0x56 }, // n
        { 0x58, 0x5D }, // o
        { 0x5F, 0x64 }, // p
        { 0x66, 0x6B }, // q
        { 0x6C, 0x70 }, // r
        { 0x72, 0x77 }, // s
        { 0x79, 0x7C }, // t
        { 0x7E, 0x82 }, // u
        { 0x84, 0x89 }, // v
        { 0x8B, 0x92 }, // w
        { 0x94, 0x99 }, // x
        { 0x9B, 0xA0 }, // y
        { 0xA2, 0xA6 }, // z
        { 0xA8, 0xAB }, // {
        { 0xAD, 0xAE }, // |
        { 0xB0, 0xB3 }, // }
        { 0xB5, 0xB9 }, // ~
        { 0xB5, 0xB9 }  // ASCII DEL, so it just reuses the tilde above.
    }
};

Gfx dDebugFontSettings[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetPrimColor(0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

/*******************************/

/************ .rodata ************/

const char gLowerCase[] = "0123456789abcdefghijklmnopqrstuvwxyz";
const char gUpperCase[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char D_800E8C50[] = "";
const char D_800E8C54[] = "(null)";
const char D_800E8C5C[] = "(nil)";

/*********************************/

/************ .bss ************/

TextureHeader *gTexture[3];
u16 gDebugTextX;
u16 gDebugTextY;
u16 D_80127CB0;
u16 D_80127CB2;
s32 gDebugFixedWidthMode;
s32 gDebugTextOn;
s32 gDebugBoundsX1;
s32 gDebugBoundsX2;
s32 gDebugBoundsY1;
s32 gDebugBoundsY2;
s32 gDebugFontTexture;
u16 gDebugScreenWidth;
u16 gDebugScreenHeight;
UNUSED s32 D_80127CD4;
char gDebugPrintBufferStart[0x900];
char *gDebugPrintBufferEnd;

/******************************/

/**
 * Standard C Library function that converts integers to strings.
 */
char *_itoa(u64 n, char *outBuffer, u32 radix, s32 useUpperCase) {
    char *alphabet;
    char *buffer;

    alphabet = (useUpperCase) ? (char *) gUpperCase : (char *) gLowerCase;

    for (buffer = outBuffer; n > 0; n /= radix) {
        *(--buffer) = alphabet[n % radix];
    }

    return buffer;
}

/**
 * Used to determine if vsprintf should use fixed width mode or not
 * Official Name: sprintfSetSpacingCodes
 */
void sprintfSetSpacingCodes(s32 setting) {
    gSprintfSpacingCode = setting;
}

/**
 * Official name: sprintf
 */
UNUSED int sprintf(char *s, const char *format, ...) {
    s32 ret;
    va_list args;
    va_start(args, format);
    ret = vsprintf(s, format, args);
    va_end(args);
    return ret;
}

/**
 * https://decomp.me/scratch/xoBfs
 * Official name: vsprintf
 */
#ifdef NON_EQUIVALENT
#define outchar(x)  \
    do {            \
        done++;     \
        (*s++) = x; \
    } while (0)

#define PAD(x)          \
    while (width > 0) { \
        width--;        \
        outchar(x);     \
    }

#define HAVE_LONGLONG 1

#define PTR void *

/* Cast the next arg, of type ARGTYPE, into CASTTYPE, and put it in VAR.  */
#define castarg(var, argtype, casttype) var = (casttype) va_arg(args, argtype)

/* Get the next arg, of type TYPE, and put it in VAR.  */
#define nextarg(var, type) castarg(var, type, type)

#define BUFSIZ 100

#define isdigit(c) ((c >= '0') && (c <= '9'))

// Returns the total number of characters written.
int vsprintf(char *s, const char *fmt, va_list args) {
    /* The string describing the size of groups of digits.  */
    UNUSED char *grouping;

    /* Pointer into the format string.  */
    register char *f;

    /* Number of characters written.  */
    register int done = 0;

    f = fmt;
    while (*f != '\0') {
        /* Type modifiers.  */
        char is_short, is_long, is_long_double;

#ifdef HAVE_LONGLONG
        /* We use the `L' modifier for `long long int'.  */
#define is_longlong is_long_double
#else
#define is_longlong 0
#endif

        /* Format spec modifiers.  */
        char space, showsign, left, alt;

        /* Padding character: ' ' or '0'.  */
        char pad;
        /* Width of a field.  */
        register int width;
        /* Precision of a field.  */
        int prec;

        /* Decimal integer is negative.  */
        char is_neg;

        /* Current character of the format.  */
        char fc;

        /* Base of a number to be written.  */
        int base;
        /* Integral values to be written.  */
        u64 num;
        s64 signed_num;

        /* String to be written.  */
        char *str;

        s32 a1;
        s32 i;
        s32 unused2;

        if (*f != '%') {
            /*   This isn't a format spec, so write everything out until the
                 next one.  To properly handle multibyte characters, we cannot
                 just search for a '%'.  Since multibyte characters are hairy
                 (and dealt with above), if we hit any byte above 127 (only
                 those can start a multibyte character) we just punt back to
                 that code.  */
            while (*f != '%' && *f != '\0') {
                outchar(*f++);
            }
            continue;
        }

        ++f;

        /* Check for "%%".  Note that although the ANSI standard lists
            '%' as a conversion specifier, it says "The complete format
            specification shall be `%%'," so we can avoid all the width
            and precision processing.  */
        if (*f == '%') {
            ++f;
            outchar('%');
            continue;
        }

        /* Check for spec modifiers.  */
        space = showsign = left = alt = 0;
        pad = ' ';
        while (*f == ' ' || *f == '+' || *f == '-' || *f == '#' || *f == '0') {
            switch (*f++) {
                case ' ':
                    /* Output a space in place of a sign, when there is no sign.  */
                    space = 1;
                    break;
                case '+':
                    /* Always output + or - for numbers.  */
                    showsign = 1;
                    break;
                case '-':
                    /* Left-justify things.  */
                    left = 1;
                    break;
                case '#':
                    /* Use the "alternate form":
                    Hex has 0x or 0X, FP always has a decimal point.  */
                    alt = 1;
                    break;
                case '0':
                    /* Pad with 0s.  */
                    pad = '0';
                    break;
            }
        }
        // end of while loop

        if (left) {
            pad = ' ';
        }

        /* Get the field width.  */
        width = 0;
        if (*f == '*') {
            /* The field width is given in an argument.
               A negative field width indicates left justification.  */
            nextarg(width, int);
            if (width < 0) {
                width = -width;
                left = 1;
            }
            ++f;
        } else {
            while (isdigit(*f)) {
                width *= 10;
                width += *f++ - '0';
            }
        }

        /* Get the precision.  */
        /* -1 means none given; 0 means explicit 0.  */
        prec = -1;
        if (*f == '.') {
            ++f;
            if (*f == '*') {
                /* The precision is given in an argument.  */
                nextarg(prec, int);
                /* Avoid idiocy.  */
                if (prec < 0) {
                    prec = -1;
                }
                ++f;
            } else if (isdigit(*f)) {
                prec = 0;
                while (isdigit(*f)) {
                    prec *= 10;
                    prec += *f++ - '0';
                }
            }
        }

        /* Check for type modifiers.  */
        is_short = is_long = is_long_double = 0;
        while (*f == 'h' || *f == 'l' || *f == 'L' || *f == 'Z' || *f == 'q') {
            switch (*f++) {
                case 'h':
                    /* int's are short int's.  */
                    is_short = 1;
                    break;
                case 'l':
#ifdef HAVE_LONGLONG
                    if (is_long) {
                        /* A double `l' is equivalent to an `L'.  */
                        is_longlong = 1;
                    } else {
#endif
                        /* int's are long int's.  */
                        is_long = 1;
                    }
                    break;
                case 'L':
                    /* double's are long double's, and int's are long long int's.  */
                    is_long_double = 1;
                    break;
                case 'Z':
                    /* int's are size_t's.  */
#ifdef HAVE_LONGLONG
                    // assert (sizeof(size_t) <= sizeof(unsigned long long int));
                    // is_longlong = sizeof(size_t) > sizeof(unsigned long int);
#endif
                    is_long = TRUE; // sizeof(size_t) > sizeof(unsigned int);
                    break;
                case 'q':
                    is_longlong = 1;
                    break;
            }
        }

        /* Format specification.  */
        fc = *f++;
        switch (fc) {
            case 'i':
            case 'd':
                /* Decimal integer.  */
                base = 10;
                if (is_longlong) {
                    nextarg(signed_num, s64);
                } else if (is_long) {
                    nextarg(signed_num, long int);
                } else if (!is_short) {
                    castarg(signed_num, int, long int);
                } else {
                    castarg(signed_num, int, short int);
                }

                is_neg = signed_num < 0;
                num = is_neg ? (-signed_num) : signed_num;
                goto number;
            case 'u':
                /* Decimal unsigned integer.  */
                base = 10;
                goto unsigned_number;
            case 'o':
                /* Octal unsigned integer.  */
                base = 8;
                goto unsigned_number;
            case 'X':
                /* Hexadecimal unsigned integer.  */
                base = 16;
                goto unsigned_number;
            case 'x':
                /* Hex with lower-case digits.  */
                base = 16;

            unsigned_number:
                /* Unsigned number of base BASE.  */
                if (is_longlong) {
                    castarg(num, s64, u64);
                } else if (is_long) {
                    castarg(num, long int, unsigned long int);
                } else if (!is_short) {
                    castarg(num, int, unsigned int);
                } else {
                    castarg(num, int, unsigned short int);
                }
                /* ANSI only specifies the `+' and
                   ` ' flags for signed conversions.  */
                is_neg = showsign = space = 0;

            number:
                /* Number of base BASE.  */
                {
                    char work[BUFSIZ];
                    char *workend = &work[sizeof(work) - 1];
                    register char *w;

                    if (gSprintfSpacingCode) {
                        outchar(0x84);
                    }
                    if (prec >= 0) {
                        pad = ' ';
                    }
                    /* Supply a default precision if none was given.  */
                    if (prec == -1) {
                        prec = 1;
                    }

                    /* Put the number in WORK.  */
                    w = _itoa(num, workend + 1, base, fc == 'X') - 1;
                    width -= workend - w;
                    prec -= workend - w;

                    if (alt && base == 8 && prec <= 0) {
                        *w-- = '0';
                        --width;
                    }

                    if (prec > 0) {
                        width -= prec;
                        while (prec-- > 0) {
                            *w-- = '0';
                        }
                    }

                    if (alt && base == 16) {
                        width -= 2;
                    }

                    if (is_neg || showsign || space) {
                        --width;
                    }

                    if (!left && pad == ' ') {
                        while (width-- > 0) {
                            outchar(' ');
                        }
                    }

                    if (is_neg) {
                        outchar('-');
                    } else if (showsign) {
                        outchar('+');
                    } else if (space) {
                        outchar(' ');
                    }

                    if (alt && base == 16) {
                        outchar('0');
                        outchar(fc);
                    }

                    if (!left && pad == '0') {
                        while (width-- > 0) {
                            outchar('0');
                        }
                    }

                    /* Write the number.  */
                    while (++w <= workend) {
                        outchar(*w);
                    }

                    if (left) {
                        while (width-- > 0) {
                            outchar(' ');
                        }
                    }
                }
                break;

            case 'e':
            case 'E': {
                s32 v1;
                s32 a0;
                s32 s4;

                s32 digit;

                f64 f16;
                s32 v02;
                s32 a05;
                f64 f02;
                f64 f0;
                // s32 i;
                f64 spD0;

                v02 = FALSE;

                if (gSprintfSpacingCode) {
                    outchar(0x84);
                }

                if (prec < 0) {
                    prec = 6;
                }

                if (is_short) {
                    castarg(spD0, f32, f64);
                } else {
                    nextarg(spD0, f64);
                }

                if (*((s8 *) &spD0) < 0) {
                    v02 = TRUE;
                    spD0 = -spD0;
                }

                if (spD0 == 0.0) {
                    s4 = 0;
                    f16 = 1.0;
                } else if (spD0 < 1.0) {
                    s4 = 0;
                    f16 = 1.0;
                    while (spD0 < f16) {
                        f16 /= 10.0;
                        s4--;
                    }
                }

                if (spD0 >= 1.0) {
                    s4 = 0;
                    f16 = 1.0;
                    f0 = 10.0;

                    while (f0 <= spD0) {
                        f16 = f0;
                        f0 *= 10.0;
                        s4++;
                    }
                }

                f02 = f16 * 0.5;

                for (i = prec; i > 0; i--) {
                    f02 /= 10.0;
                }

                spD0 += f02;
                if (spD0 >= f16 * 10.0) {
                    f16 = f16 * 10.0;
                    s4++;
                }

                a05 = (v02 || showsign || space);
                a1 = a05 + prec + (prec > 0 || alt) + (s4 >= 100) + 5;

                if (!left && pad == ' ') {
                    while (width-- > a1) {
                        outchar(pad);
                    }
                }

                if (v02) {
                    outchar('-');
                } else if (showsign) {
                    outchar('+');
                } else if (space) {
                    outchar(' ');
                }

                if (!left && pad == '0') {
                    while (width-- > a1) {
                        outchar(pad);
                    }
                }

                digit = '0';
                while (spD0 >= f16) {
                    spD0 -= f16;
                    digit++;
                }
                outchar(digit);
                f16 /= 10.0;

                if (prec > 0 || alt) {
                    outchar('.');
                }

                if (prec) {
                    do {
                        digit = '0';
                        while (spD0 >= f16) {
                            spD0 -= f16;
                            digit++;
                        }
                        outchar(digit);
                        f16 /= 10.0;
                    } while (--prec > 0);
                }

                outchar(fc);

                if (s4 < 0) {
                    s4 = -s4;
                    outchar('-');
                    v1 = '0' + ((s4 / 10) % 10);
                    a0 = '0' + (s4 % 10);
                } else {
                    outchar('+');
                    v1 = '0' + ((s4 / 10) % 10);
                    a0 = '0' + (s4 % 10);
                }

                if (s4 >= 100) {
                    outchar('0' + s4 / 100);
                }

                outchar(v1);
                outchar(a0);

                if (left) {
                    while (width-- > a1) {
                        outchar(' ');
                    }
                }
                break;
            }
            case 'G':
            case 'g':
                break;
            case 'f': {
                f64 f12 = 1.0;
                f64 f14 = 10.0;
                f64 f2;
                // s32 i;
                s32 digit;
                s32 vara1;
                s32 a05;
                s32 v010;
                f64 spD0;

                vara1 = FALSE;

                if (gSprintfSpacingCode) {
                    outchar(0x84);
                }
                if (prec < 0) {
                    prec = 6;
                }

                for (i = 0; i < prec; i++) {
                    f12 /= 10.0;
                }

                if (is_short) {
                    castarg(spD0, f32, f64);
                } else {
                    nextarg(spD0, f64);
                }

                if (spD0 < 0.0) {
                    vara1 = TRUE;
                    spD0 = -spD0;
                }

                spD0 += f12 * 0.5;

                for (f2 = 1.0, v010 = 1; spD0 >= f2; v010++) {
                    f2 = f14;
                    f14 *= 10.0;
                }

                a05 = (vara1 || showsign || space);
                a1 = (prec > 0 || alt) + a05 + v010 + prec;

                if (!left && pad == ' ') {
                    while (width-- > a1) {
                        outchar(pad);
                    }
                }

                if (vara1) {
                    outchar('-');
                } else if (showsign) {
                    outchar('+');
                } else if (space) {
                    outchar(' ');
                }

                if (!left && pad == '0') {
                    while (width-- > a1) {
                        outchar(pad);
                    }
                }

                do {
                    digit = '0';
                    while (spD0 >= f2) {
                        spD0 -= f2;
                        digit++;
                    }
                    f2 /= 10.0;
                    outchar(digit);
                } while (f2 >= 1.0);

                if (prec > 0 || alt) {
                    outchar('.');
                }

                if (prec > 0) {
                    do {
                        digit = '0';
                        while (spD0 >= f2) {
                            spD0 -= f2;
                            digit++;
                        }
                        outchar(digit);
                        f2 /= 10.0;
                    } while (--prec > 0);
                }

                if (left) {
                    while (width-- > a1) {
                        outchar(' ');
                    }
                }
                break;
            }
            case 'c':
                /* Character.  */
                nextarg(num, int);
                if (!left) {
                    while (--width > 0) {
                        outchar(pad);
                    }
                }
                outchar((unsigned char) num);
                if (left) {
                    while (--width > 0) {
                        outchar(' ');
                    }
                }
                break;

            case 's': {
                static char null[] = "(null)";
                s32 len;

                nextarg(str, char *);

                if (str == NULL) {
                    /* Write "(null)" if there's space.  */
                    if (prec == -1 || prec >= (int) sizeof(null) - 1) {
                        str = null;
                        len = sizeof(null) - 1;
                    } else {
                        str = "";
                        len = 0;
                    }
                } else {
                    len = strlen(str);
                }

                if (prec != -1 && prec < len) {
                    len = prec;
                }
                width -= len;

                if (!left) {
                    while (width-- > 0) {
                        outchar(' ');
                    }
                }
                while (len-- > 0) {
                    outchar(*str++);
                }

                if (left) {
                    while (width-- > 0) {
                        outchar(' ');
                    }
                }
            } break;

            case 'p':
                /* Generic pointer.  */
                {
                    PTR ptr;
                    nextarg(ptr, PTR);
                    if (ptr != NULL) {
                        /* If the pointer is not NULL, write it as a %#x spec.  */
                        base = 16;
                        fc = 'x';
                        alt = 1;
                        num = (u64) (unsigned long int) ptr;
                        is_neg = 0;
                        goto number;
                    } else {
                        /* Write "(nil)" for a nil pointer.  */
                        static char nil[] = "(nil)";
                        register char *p;

                        width -= sizeof(nil) - 1;
                        if (!left) {
                            while (width-- > 0) {
                                outchar(' ');
                            }
                        }
                        for (p = nil; *p != '\0';) {
                            outchar(*p++);
                        }
                        if (left) {
                            while (width-- > 0) {
                                outchar(' ');
                            }
                        }
                    }
                }
                break;

            case 'n':
                /* Answer the count of characters written.  */
                if (is_longlong) {
                    s64 *p;
                    nextarg(p, s64 *);
                    *p = done;
                } else if (is_long) {
                    long int *p;
                    nextarg(p, long int *);
                    *p = done;
                } else if (!is_short) {
                    int *p;
                    nextarg(p, int *);
                    *p = done;
                } else {
                    short int *p;
                    nextarg(p, short int *);
                    *p = done;
                }
                break;
            default:
                /* Unrecognized format specifier.  */
                break;
        }
        if (gSprintfSpacingCode) {
            outchar(0x83);
        }
    }
    *s = 0;
    return done;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/printf/vsprintf.s")
#endif

/**
 * Load the font textures for the debug text, then set the buffer to the beginning.
 * Official Name: diPrintfInit
 */
void debug_text_init(void) {
    gTexture[0] = load_texture(ASSET_TEX2D_SMALLFONT_0);
    gTexture[1] = load_texture(ASSET_TEX2D_SMALLFONT_1);
    gTexture[2] = load_texture(ASSET_TEX2D_SMALLFONT_2);
    gDebugPrintBufferEnd = gDebugPrintBufferStart;
}

/**
 * Add a string to the onscreen debug text buffer.
 * Has variable args, so can use multiple string elements.
 * Official Name: diPrintf
 */
s32 render_printf(const char *format, ...) {
    va_list args;
    s32 written;
    va_start(args, format);
    if ((gDebugPrintBufferEnd - gDebugPrintBufferStart) > 0x800) {
        stubbed_printf("*** diPrintf Error *** ---> Out of string space. (Print less text!)\n");
        return -1;
    }
    sprintfSetSpacingCodes(TRUE);
    written = vsprintf(gDebugPrintBufferEnd, format, args);
    sprintfSetSpacingCodes(FALSE);
    if (written > 0) {
        gDebugPrintBufferEnd = &gDebugPrintBufferEnd[written] + 1;
    }
    return 0;
}

/**
 * At the end of a frame, iterate through the debug text buffer and print it on screen.
 * Soft-clear the buffer afterwards by setting the endpoint to the start point.
 * Official Name: diPrintfAll
 */
void debug_text_print(Gfx **dList) {
    char *buffer;
    u32 widthAndHeight;

    rdp_init(dList);
    widthAndHeight = fb_size();
    gDebugScreenHeight = GET_VIDEO_HEIGHT(widthAndHeight);
    gDebugScreenWidth = GET_VIDEO_WIDTH(widthAndHeight);
    gDPSetScissor((*dList)++, 0, 0, 0, gDebugScreenWidth, gDebugScreenHeight);
    debug_text_bounds();
    gSPDisplayList((*dList)++, dDebugFontSettings);
    buffer = (char *) gDebugPrintBufferStart;
    debug_text_origin();
    gDebugFontTexture = -1;
    gDebugFixedWidthMode = FALSE;
    D_80127CB0 = gDebugTextX;
    D_80127CB2 = gDebugTextY;
    while ((s32) buffer != (s32) gDebugPrintBufferEnd) {
        gDebugTextOn = FALSE;
        buffer += debug_text_parse(dList, buffer);
    }
    debug_text_background(dList, D_80127CB0, D_80127CB2, gDebugTextX, gDebugTextY + 10);
    buffer = (char *) gDebugPrintBufferStart;
    debug_text_origin();
    gDebugFontTexture = -1;
    gDebugFixedWidthMode = FALSE;
    while ((s32) buffer != (s32) gDebugPrintBufferEnd) {
        gDebugTextOn = TRUE;
        buffer += debug_text_parse(dList, buffer);
    }
    gDebugPrintBufferEnd = gDebugPrintBufferStart;
}

/**
 * Clears the text buffer, then sets the position back to the top left.
 */
UNUSED void debug_text_reset(void) {
    gDebugPrintBufferEnd = gDebugPrintBufferStart;
    debug_text_origin();
}

/**
 * Set the colour of the current debug text.
 * Official Name: diPrintfSetCol
 */
void set_render_printf_colour(u8 red, u8 green, u8 blue, u8 alpha) {
    RENDER_PRINTF_CMD_SET_COLOR(red, green, blue, alpha)
}

/**
 * Set the background colour of the current debug text.
 * Official Name: diPrintfSetBG
 */
void set_render_printf_background_colour(u8 red, u8 green, u8 blue, u8 alpha) {
    RENDER_PRINTF_CMD_SET_BACKGROUND_COLOR(red, green, blue, alpha)
}

/**
 * Sets the character position of further prints to the given coordinates.
 * Official name: diPrintfSetXY
 */
void set_render_printf_position(u16 x, u16 y){ RENDER_PRINTF_CMD_SET_POSITION(x, y) }

/**
 * Definitely has some fakematch shenanigans.
 * This will return the length in pixels of a given string using the debug small font.
 */
UNUSED s32 debug_text_width(const char *format, ...) {
    s32 pad;
    s32 fontCharU;
    s32 stringLength;
    char s[255];
    u8 *ch;
    va_list args;
    va_start(args, format);

    stringLength = 0;
    sprintfSetSpacingCodes(TRUE);
    vsprintf(s, format, args);
    sprintfSetSpacingCodes(FALSE);
    for (ch = (u8 *) &s[0]; *ch != '\0'; ch++) {
        pad = *ch;
        if (*ch != (0, '\n')) {
            if (pad == ' ') {
                stringLength += 6;
                if (1) {}
            } else {
                if (*ch < 0x40) {
                    // Character is a symbol or number and not a letter
                    gDebugFontTexture = ASSET_TEX2D_SMALLFONT_0;
                    *ch -= 0x21;
                } else if (*ch < 0x60) {
                    // Character is a upper case letter
                    gDebugFontTexture = ASSET_TEX2D_SMALLFONT_1;
                    *ch -= 0x40;
                } else if (*ch <= 0x7F) {
                    // Character is a lower case letter
                    gDebugFontTexture = ASSET_TEX2D_SMALLFONT_2;
                    *ch -= 0x60;
                }
                fontCharU = gDebugFontCoords[gDebugFontTexture][*ch].u;
                stringLength = ((stringLength + gDebugFontCoords[gDebugFontTexture][*ch].v) - fontCharU) + (pad = 1);
            }
        }
    }
    va_end(args);
    return stringLength;
}

/**
 * Read the current character in the debug text buffer.
 * Also executes commands when they come up.
 */
s32 debug_text_parse(Gfx **dList, char *buffer) {
    char *bufferCopy;
    s32 xOffset;
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    u8 bufferValue;

    bufferCopy = buffer;
    bufferValue = *buffer;
    buffer++;
    while (bufferValue != NULL) {
        xOffset = 0;
        switch (bufferValue) {
            case 0x83: // Leave fixed-width mode
                gDebugFixedWidthMode = FALSE;
                break;
            case 0x84: // Enter fixed-width mode
                gDebugFixedWidthMode = TRUE;
                break;
            case 0x81: // Set the text color from the next 4 bytes
                red = buffer[0];
                green = buffer[1];
                blue = buffer[2];
                alpha = buffer[3];
                buffer += 4;
                if (gDebugTextOn) {
                    gDPSetEnvColor((*dList)++, red, green, blue, alpha);
                }
                break;
            case 0x85: // Set the background color from the next 4 bytes
                red = buffer[0];
                green = buffer[1];
                blue = buffer[2];
                alpha = buffer[3];
                buffer += 4;
                if (!gDebugTextOn) {
                    gDPSetPrimColor((*dList)++, 0, 0, red, green, blue, alpha);
                }
                break;
            case 0x82: // Set debug text position from the next 4 bytes
                if (!gDebugTextOn) {
                    debug_text_background(dList, D_80127CB0, D_80127CB2, gDebugTextX, gDebugTextY + 10);
                }
                gDebugTextX = buffer[0];
                gDebugTextX |= buffer[1] << 8;
                gDebugTextY = buffer[2];
                gDebugTextY |= buffer[3] << 8;
                D_80127CB0 = gDebugTextX;
                D_80127CB2 = gDebugTextY;
                buffer += 4;
                break;
            case ' ': // Space
                xOffset = 6;
                break;
            case '\n': // Line Feed
                if (!gDebugTextOn) {
                    debug_text_background(dList, D_80127CB0, D_80127CB2, gDebugTextX, gDebugTextY + 10);
                }
                debug_text_newline();
                D_80127CB0 = gDebugTextX;
                D_80127CB2 = gDebugTextY;
                break;
            case '\t': // HT - Horizontal Tab
                if (!(gDebugTextX % 32)) {
                    xOffset = 32;
                } else {
                    xOffset = 32 - (gDebugTextX % 32);
                }
                break;
            default:
                xOffset = debug_text_character(dList, bufferValue);
                break;
        }

        if (gDebugFixedWidthMode && bufferValue >= 0x20 && bufferValue < 0x80) {
            xOffset = 7;
        }
        gDebugTextX += xOffset;
        if ((gDebugScreenWidth - 16) < gDebugTextX) {
            if (!gDebugTextOn) {
                debug_text_background(dList, D_80127CB0, D_80127CB2, gDebugTextX, gDebugTextY + 10);
            }
            debug_text_newline();
            D_80127CB0 = gDebugTextX;
            D_80127CB2 = gDebugTextY;
        }
        bufferValue = *buffer;
        buffer++;
    }

    return buffer - bufferCopy;
}

/**
 * Render the background for the debug text.
 */
void debug_text_background(Gfx **dList, u32 ulx, u32 uly, u32 lrx, u32 lry) {
    if (!((ulx == lrx) | (uly == lry))) {
        if (ulx >= 2) {
            ulx -= 2;
        }
        lrx += 2;
        gDPSetCombineMode((*dList)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPFillRectangle((*dList)++, ulx, uly, lrx, lry);
    }
}

/**
 * Renders a character onscreen at the current debug text position.
 * If necessary, load the correct font texture.
 * Return the width of the char that was just printed.
 */
s32 debug_text_character(Gfx **dList, s32 asciiVal) {
    s32 fontCharWidth;
    s32 fontCharU;

    if (asciiVal < 0x40) {
        // Character is a symbol or number and not a letter
        if (gDebugFontTexture != 0) {
            if (gDebugTextOn) {
                gDPLoadTextureBlock((*dList)++, OS_K0_TO_PHYSICAL(gTexture[0] + 1), G_IM_FMT_IA, G_IM_SIZ_8b, 192, 11,
                                    0, 2, 2, 0, 0, 0, 0);
            }
            gDebugFontTexture = 0;
        }
        asciiVal -= 0x21;
    } else if (asciiVal < 0x60) {
        // Character is a upper case letter
        if (gDebugFontTexture != 1) {
            if (gDebugTextOn) {
                gDPLoadTextureBlock((*dList)++, OS_K0_TO_PHYSICAL(gTexture[1] + 1), G_IM_FMT_IA, G_IM_SIZ_8b, 248, 11,
                                    0, 2, 2, 0, 0, 0, 0);
            }
            gDebugFontTexture = 1;
        }
        asciiVal -= 0x40;
    } else if (asciiVal <= 0x7F) {
        // Character is a lower case letter
        if (gDebugFontTexture != 2) {
            if (gDebugTextOn) {
                gDPLoadTextureBlock((*dList)++, OS_K0_TO_PHYSICAL(gTexture[2] + 1), G_IM_FMT_IA, G_IM_SIZ_8b, 192, 11,
                                    0, 2, 2, 0, 0, 0, 0);
            }
            gDebugFontTexture = 2;
        }
        asciiVal -= 0x60;
    }
    fontCharU = gDebugFontCoords[gDebugFontTexture][asciiVal].u;
    fontCharWidth = (gDebugFontCoords[gDebugFontTexture][asciiVal].v - fontCharU) + 1;
    if (gDebugTextOn) {
        gDPSetCombineMode((*dList)++, G_CC_ENV_DECALA, G_CC_ENV_DECALA);
        gSPTextureRectangle((*dList)++, (gDebugTextX << 2), (gDebugTextY << 2), ((gDebugTextX + fontCharWidth) << 2),
                            ((gDebugTextY + 10) << 2), 0, (fontCharU << 5), 0, 1024, 1024);
    }
    return fontCharWidth;
}

/**
 * Sets the upper and lower boundaries of the debug text.
 */
void debug_text_bounds(void) {
    if (gDebugScreenWidth <= 320) {
        gDebugBoundsX1 = 16;
        gDebugBoundsX2 = gDebugScreenWidth - 16;
    } else {
        gDebugBoundsX1 = 32;
        gDebugBoundsX2 = gDebugScreenWidth - 32;
    }
    if (gDebugScreenHeight <= 240) {
        gDebugBoundsY1 = 16;
        gDebugBoundsY2 = gDebugScreenHeight - 16;
    } else {
        gDebugBoundsY1 = 32;
        gDebugBoundsY2 = gDebugScreenHeight - 32;
    }
}

/**
 * Sets the print position of the text back to top left.
 */
void debug_text_origin(void) {
    gDebugTextX = gDebugBoundsX1;
    gDebugTextY = gDebugBoundsY1;
}

/**
 * Moves the print position of the text down one line.
 */
void debug_text_newline(void) {
    gDebugTextX = gDebugBoundsX1;
    gDebugTextY += 11;
}

UNUSED void func_800B6F30(UNUSED int arg0, UNUSED int arg1, UNUSED int arg2) {
}
