#ifndef _PRINTF_H_
#define _PRINTF_H_

#include "types.h"
#include "structs.h"
#include "macros.h"
#include <PR/gu.h>

typedef struct TexFontCoords {
    u8 u, v;
} TexFontCoords;

#define RENDER_PRINTF_CMD_ARG_BYTE(val) *gDebugPrintBufferEnd = val; gDebugPrintBufferEnd++;
#define RENDER_PRINTF_CMD_ARG_SHORT(val) RENDER_PRINTF_CMD_ARG_BYTE(val) RENDER_PRINTF_CMD_ARG_BYTE(val >> 8)

#define RENDER_PRINTF_CMD_END RENDER_PRINTF_CMD_ARG_BYTE(0)

#define RENDER_PRINTF_CMD_SET_COLOR(red, green, blue, alpha) \
    RENDER_PRINTF_CMD_ARG_BYTE(0x81)                         \
    RENDER_PRINTF_CMD_ARG_BYTE(red)                          \
    RENDER_PRINTF_CMD_ARG_BYTE(green)                        \
    RENDER_PRINTF_CMD_ARG_BYTE(blue)                         \
    RENDER_PRINTF_CMD_ARG_BYTE(alpha)                        \
    RENDER_PRINTF_CMD_END

// This is a bit hacky, but it matches.
#define RENDER_PRINTF_CMD_SET_POSITION(x, y) \
    u16 tempX, tempY;                        \
    RENDER_PRINTF_CMD_ARG_BYTE(0x82)         \
    RENDER_PRINTF_CMD_ARG_BYTE(x & 0xFF)     \
    tempX = x >> 8;                          \
    RENDER_PRINTF_CMD_ARG_BYTE(tempX)        \
    RENDER_PRINTF_CMD_ARG_BYTE(y & 0xFF)     \
    tempY = y >> 8;                          \
    RENDER_PRINTF_CMD_ARG_BYTE(tempY)        \
    RENDER_PRINTF_CMD_END
    
#define RENDER_PRINTF_CMD_SET_BACKGROUND_COLOR(red, green, blue, alpha) \
    RENDER_PRINTF_CMD_ARG_BYTE(0x85)                                    \
    RENDER_PRINTF_CMD_ARG_BYTE(red)                                     \
    RENDER_PRINTF_CMD_ARG_BYTE(green)                                   \
    RENDER_PRINTF_CMD_ARG_BYTE(blue)                                    \
    RENDER_PRINTF_CMD_ARG_BYTE(alpha)                                   \
    RENDER_PRINTF_CMD_END


char *_itoa(u64 n, char *outBuffer, u32 radix, s32 useUpperCase);
void func_800B4A08(s32 setting);
void debug_text_init(void);
void set_render_printf_colour(u8 red, u8 green, u8 blue, u8 alpha);
void set_render_printf_background_colour(u8 red, u8 green, u8 blue, u8 alpha);
void debug_text_background(Gfx **dList, u32 ulx, u32 uly, u32 lrx, u32 lry);
s32 debug_text_character(Gfx **dList, s32 asciiVal);
void debug_text_print(Gfx **dList);
void set_render_printf_position(u16 x, u16 y);
s32 render_printf(const char *format, ...);
void debug_text_bounds(void);
void debug_text_origin(void);
void debug_text_newline(void);

s32 func_800B653C(Gfx**, char*);
int vsprintf(char *s, const char *fmt, ...);

#endif
