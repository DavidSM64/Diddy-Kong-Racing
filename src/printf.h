#ifndef _PRINTF_H_
#define _PRINTF_H_

#include "types.h"
#include <PR/gu.h>


#define RENDER_PRINTF_CMD_ARG_BYTE(val) *D_801285D8 = val; D_801285D8++;
#define RENDER_PRINTF_CMD_ARG_SHORT(val) RENDER_PRINTF_CMD_ARG_BYTE(val) RENDER_PRINTF_CMD_ARG_BYTE(val >> 8)

#define RENDER_PRINTF_CMD_END RENDER_PRINTF_CMD_ARG_BYTE(0)

#define RENDER_PRINTF_CMD_SET_COLOR(red, green, blue, alpha) \
    RENDER_PRINTF_CMD_ARG_BYTE(0x81)                         \
    RENDER_PRINTF_CMD_ARG_BYTE(red)                          \
    RENDER_PRINTF_CMD_ARG_BYTE(green)                        \
    RENDER_PRINTF_CMD_ARG_BYTE(blue)                         \
    RENDER_PRINTF_CMD_ARG_BYTE(alpha)                        \
    RENDER_PRINTF_CMD_END

#define RENDER_PRINTF_CMD_SET_POSITION(x, y) \
    RENDER_PRINTF_CMD_ARG_BYTE(0x82)         \
    RENDER_PRINTF_CMD_ARG_SHORT(x)           \
    RENDER_PRINTF_CMD_ARG_SHORT(y)           \
    RENDER_PRINTF_CMD_END
    
#define RENDER_PRINTF_CMD_SET_BACKGROUND_COLOR(red, green, blue, alpha) \
    RENDER_PRINTF_CMD_ARG_BYTE(0x85)                                    \
    RENDER_PRINTF_CMD_ARG_BYTE(red)                                     \
    RENDER_PRINTF_CMD_ARG_BYTE(green)                                   \
    RENDER_PRINTF_CMD_ARG_BYTE(blue)                                    \
    RENDER_PRINTF_CMD_ARG_BYTE(alpha)                                   \
    RENDER_PRINTF_CMD_END


void func_800B4A08(s32 arg0);
void func_800B5E88(void);
void set_render_printf_colour(u8 red, u8 green, u8 blue, u8 alpha);
void set_render_printf_background_colour(u8 red, u8 green, u8 blue, u8 alpha);

void set_render_printf_position(u16 xpos, u16 ypos); // Non Matching
s32 render_printf(const char *format, ...); // Non Matching
void print_debug_strings(Gfx **arg0); // Non Matching

#endif
