#ifndef _PRINTF_H_
#define _PRINTF_H_

#include "types.h"
#include "structs.h"
#include "particles.h"
#include "macros.h"
#include <PR/gu.h>


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
UNUSED unk800E2CF0 *func_800B4488(s32 idx);
UNUSED unk800E2CF0 *func_800B44D4(s32 *idx);
UNUSED unk800E2CF0 *func_800B452C(s32 *arg0);
UNUSED ParticleBehavior *func_800B4578(s32 idx);
void func_800B5E88(void);
void set_render_printf_colour(u8 red, u8 green, u8 blue, u8 alpha);
void set_render_printf_background_colour(u8 red, u8 green, u8 blue, u8 alpha);
void func_800B695C(Gfx** dList, u32 arg1, u32 arg2, u32 arg3, u32 arg4);
s32 func_800B69FC(Gfx **dlist, s32 arg1);
void print_debug_strings(Gfx **dList);

void set_render_printf_position(u16 xpos, u16 ypos); // Non Matching
s32 render_printf(const char *format, ...); // Non Matchingg
void func_800B3740(Object *, Gfx **, Matrix **, VertexList **, s32); // Non Matching
s32 func_800B653C(Gfx**, s8*);

#endif
