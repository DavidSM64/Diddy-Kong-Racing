/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B3140 */

#include "printf.h"
#include "types.h"
#include "macros.h"
#include "f3ddkr.h"
#include "thread0_epc.h"
#include "stdarg.h"
#include "textures_sprites.h"
#include "stdio.h"
#include "objects.h"
#include "particles.h"
#include "unknown_078050.h"

/************ .data ************/

s32 D_800E2EF0 = 0;

u8 D_800E2EF4[196] = {
    0x02, 0x04, 0x06, 0x08, 0x0A, 0x0F, 0x11, 0x15, 0x17, 0x1F, 0x21, 0x27, 0x29, 0x2B, 0x2D, 0x2F, 
    0x31, 0x33, 0x35, 0x38, 0x3A, 0x3F, 0x41, 0x43, 0x45, 0x48, 0x4A, 0x4B, 0x4D, 0x50, 0x52, 0x56, 
    0x58, 0x5B, 0x5D, 0x62, 0x64, 0x68, 0x6A, 0x6F, 0x71, 0x76, 0x78, 0x7D, 0x7F, 0x84, 0x86, 0x8B, 
    0x8D, 0x92, 0x94, 0x96, 0x98, 0x9A, 0x9D, 0xA2, 0xA5, 0xA9, 0xAB, 0xB0, 0xB3, 0xB8, 0x00, 0x01, 
    0x00, 0x09, 0x0B, 0x11, 0x13, 0x19, 0x1B, 0x21, 0x23, 0x29, 0x2B, 0x31, 0x33, 0x38, 0x3A, 0x41, 
    0x43, 0x49, 0x4B, 0x4C, 0x4E, 0x53, 0x55, 0x5B, 0x5D, 0x62, 0x64, 0x6B, 0x6D, 0x73, 0x75, 0x7B, 
    0x7D, 0x83, 0x85, 0x8B, 0x8D, 0x93, 0x95, 0x9B, 0x9D, 0xA3, 0xA5, 0xAA, 0xAC, 0xB2, 0xB4, 0xBC, 
    0xBE, 0xC4, 0xC6, 0xCC, 0xCE, 0xD3, 0xD5, 0xD7, 0xD9, 0xDC, 0xDE, 0xE0, 0xE2, 0xE7, 0xE9, 0xEF, 
    0x00, 0x01, 0x03, 0x08, 0x09, 0x0F, 0x11, 0x16, 0x18, 0x1D, 0x1F, 0x24, 0x26, 0x28, 0x2A, 0x2F, 
    0x31, 0x36, 0x38, 0x39, 0x3B, 0x3D, 0x3F, 0x43, 0x45, 0x46, 0x48, 0x4F, 0x51, 0x56, 0x58, 0x5D, 
    0x5F, 0x64, 0x66, 0x6B, 0x6C, 0x70, 0x72, 0x77, 0x79, 0x7C, 0x7E, 0x82, 0x84, 0x89, 0x8B, 0x92, 
    0x94, 0x99, 0x9B, 0xA0, 0xA2, 0xA6, 0xA8, 0xAB, 0xAD, 0xAE, 0xB0, 0xB3, 0xB5, 0xB9, 0xB5, 0xB9, 
    0x00, 0x00, 0x00, 0x00
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

const char D_800E8C00[] = "0123456789abcdefghijklmnopqrstuvwxyz";
const char D_800E8C28[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char D_800E8C50[] = "";
const char D_800E8C54[] = "(null)";
const char D_800E8C5C[] = "(nil)";
const char D_800E8C64[] = "*** diPrintf Error *** ---> Out of string space. (Print less text!)\n";

/*********************************/

/************ .bss ************/

extern TextureHeader *gTexture0;
extern TextureHeader *gTexture1;
extern TextureHeader *gTexture2;
extern u8 gDebugPrintBufferStart[];
extern u8 *gDebugPrintBufferEnd;

/******************************/

GLOBAL_ASM("asm/non_matchings/printf/func_800B3140.s")
GLOBAL_ASM("asm/non_matchings/printf/func_800B3240.s")
GLOBAL_ASM("asm/non_matchings/printf/func_800B3358.s")
GLOBAL_ASM("asm/non_matchings/printf/func_800B34B0.s")
GLOBAL_ASM("asm/non_matchings/printf/func_800B3564.s")

UNUSED void func_800B3678(Gfx **arg0, MatrixS **arg1, Vertex **arg2) {
    UNUSED s32 pad;
    UNUSED s32 pad2;
    Object **temp_s0;
    s32 sp38;
    s32 sp34;

    temp_s0 = func_8000E988(&sp38, &sp34);
    for (; sp38 < sp34; sp38++) {
        if (temp_s0[sp38]->segment.trans.unk6 & 0x8000) {
            if ((s32) temp_s0[sp38]->segment.header & 0x8000) {
                func_800B3740(temp_s0[sp38], arg0, arg1, arg2, 0);
            }
        }
    }
}

GLOBAL_ASM("asm/non_matchings/printf/func_800B3740.s")
GLOBAL_ASM("asm/non_matchings/printf/func_800B3E64.s")

UNUSED unk800E2CF0 *func_800B4488(s32 idx) {
    if (idx < gParticlesAssetTableCount) {
        return gParticlesAssetTable[idx];
    }
    return gParticlesAssetTable[gParticlesAssetTableCount - 1];
}

UNUSED unk800E2CF0 *func_800B44D4(s32 *idx) {
    *idx = *idx + 1;
    while (*idx >= gParticlesAssetTableCount) {
        *idx = *idx - gParticlesAssetTableCount;
    }
    return gParticlesAssetTable[*idx];
}

UNUSED unk800E2CF0 *func_800B452C(s32 *arg0) {
    for (*arg0 = *arg0 - 1; *arg0 < 0; *arg0 += gParticlesAssetTableCount);
    return gParticlesAssetTable[*arg0];
}

UNUSED ParticleBehavior *func_800B4578(s32 idx) {
    if (idx < gParticleBehavioursAssetTableCount) {
        return gParticleBehavioursAssetTable[idx];
    }
    return gParticleBehavioursAssetTable[gParticleBehavioursAssetTableCount - 1];
}

GLOBAL_ASM("asm/non_matchings/printf/func_800B45C4.s")
GLOBAL_ASM("asm/non_matchings/printf/func_800B461C.s")
GLOBAL_ASM("asm/non_matchings/printf/func_800B4668.s")
GLOBAL_ASM("asm/non_matchings/printf/func_800B46BC.s")
GLOBAL_ASM("asm/non_matchings/printf/func_800B4940.s")

void func_800B4A08(s32 arg0) {
    D_800E2EF0 = arg0;
}

void func_800B4A14(char *s, char *format, ...) {
    va_list args;
    va_start(args, format);
    sprintf(s, format, args);
    va_end(args);
}

GLOBAL_ASM("asm/non_matchings/printf/sprintf.s")

void func_800B5E88(void) {
    gTexture0 = load_texture(0);
    gTexture1 = load_texture(1);
    gTexture2 = load_texture(2);
    gDebugPrintBufferEnd = gDebugPrintBufferStart;
}

#ifdef NON_EQUIVALENT
s32 render_printf(const char *format, ...) {
    s32 written;
    va_list args;
    va_start(args, format);
    if ((gDebugPrintBufferEnd - gDebugPrintBufferStart) >= 0x801) {
        return -1;
    }
    func_800B4A08(1);
    written = sprintf(gDebugPrintBufferEnd, format, args);
    func_800B4A08(0);
    if (written > 0) {
        gDebugPrintBufferEnd = &gDebugPrintBufferEnd[written] + 1;
    }
    return 0;
}
#else
GLOBAL_ASM("asm/non_matchings/printf/render_printf.s")
#endif

/**
 * At the end of a frame, iterate through the debug text buffer and print it on screen.
 * Soft-clear the buffer afterwards by setting the endpoint to the start point.
 */
void print_debug_strings(Gfx **dList) {
    char *buffer;
    u32 widthAndHeight;

    init_rdp_and_framebuffer(dList);
    widthAndHeight = get_video_width_and_height_as_s32();
    D_80127CD2 = (widthAndHeight >> 0x10);
    D_80127CD0 = widthAndHeight & 0xFFFF;
    gDPSetScissor((*dList)++, 0, 0, 0, D_80127CD0, D_80127CD2);
    func_800B6E50();
    gSPDisplayList((*dList)++, dDebugFontSettings);
    buffer = (char *) gDebugPrintBufferStart;
    func_800B6EE0();
    D_80127CCC = -1;
    D_80127CB4 = 0;
    D_80127CB0 = D_80127CAC;
    D_80127CB2 = D_80127CAE;
    while ((s32)buffer != (s32)gDebugPrintBufferEnd) {
        D_80127CB8 = 0;
        buffer += func_800B653C(dList, (s8 *) buffer);
    }
    func_800B695C(dList, (u16) D_80127CB0, (u16) D_80127CB2, D_80127CAC, D_80127CAE + 10);
    buffer = (char *) gDebugPrintBufferStart;
    func_800B6EE0();
    D_80127CCC = -1;
    D_80127CB4 = 0;
    while ((s32)buffer != (s32)gDebugPrintBufferEnd) {
        D_80127CB8 = 1;
        buffer += func_800B653C(dList, (s8 *) buffer);
    }
    gDebugPrintBufferEnd = gDebugPrintBufferStart;
}

UNUSED void func_800B61E0(void) {
    gDebugPrintBufferEnd = gDebugPrintBufferStart;
    func_800B6EE0();
}

/**
 * Set the colour of the current debug text.
 */
void set_render_printf_colour(u8 red, u8 green, u8 blue, u8 alpha) {
    RENDER_PRINTF_CMD_SET_COLOR(red, green, blue, alpha)
}

/**
 * Set the background colour of the current debug text.
 */
void set_render_printf_background_colour(u8 red, u8 green, u8 blue, u8 alpha) {
    RENDER_PRINTF_CMD_SET_BACKGROUND_COLOR(red, green, blue, alpha)
}

/**
 * Sets the character position of further prints to the given coordinates.
*/
void set_render_printf_position(u16 x, u16 y) {
    RENDER_PRINTF_CMD_SET_POSITION(x, y)
}

GLOBAL_ASM("asm/non_matchings/printf/func_800B63F4.s")
GLOBAL_ASM("asm/non_matchings/printf/func_800B653C.s")

void func_800B695C(Gfx **dList, u32 arg1, u32 arg2, u32 arg3, u32 arg4) {
    if (!((arg1 == arg3) | (arg2 == arg4))) {
        if (arg1 >= 2) {
            arg1 -= 2;
        }
        arg3 += 2;
        gDPSetCombineMode((*dList)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPFillRectangle((*dList)++, arg1, arg2, arg3, arg4);
    }
}

s32 func_800B69FC(Gfx **dList, s32 arg1) {
    s32 temp_a3;
    s32 temp_a2;
    u8* temp_v0_22;

    if (arg1 < 64) {
        if (D_80127CCC != 0) {
            if (D_80127CB8 != 0) {
                gDPLoadTextureBlock((*dList)++, OS_PHYSICAL_TO_K0(gTexture0 + 1), G_IM_FMT_IA, G_IM_SIZ_8b, 192, 11, 0, 2, 2, 0, 0, 0, 0);
            }
            D_80127CCC = 0;
        }
        arg1 -= 33;
    } else if (arg1 < 96) {
        if (D_80127CCC != 1) {
            if (D_80127CB8) {
                gDPLoadTextureBlock((*dList)++, OS_PHYSICAL_TO_K0(gTexture1 + 1), G_IM_FMT_IA, G_IM_SIZ_8b, 248, 11, 0, 2, 2, 0, 0, 0, 0);
            }
            D_80127CCC = 1;
        }
        arg1 -= 64;
    } else if (arg1 < 128) {
        arg1 -= 96;
        if (D_80127CCC != 2) {
            if (D_80127CB8 != 0) {
                gDPLoadTextureBlock((*dList)++, OS_PHYSICAL_TO_K0(gTexture2 + 1), G_IM_FMT_IA, G_IM_SIZ_8b, 192, 11, 0, 2, 2, 0, 0, 0, 0);
            }
            D_80127CCC = 2;
        }
    }
    temp_v0_22 = &D_800E2EF4[(D_80127CCC << 6) + (arg1 * 2)];
    temp_a2 = temp_v0_22[0];
    temp_a3 = (temp_v0_22[1] - temp_a2) + 1;
    if (D_80127CB8) {
        gDPSetCombineMode((*dList)++, DKR_CC_UNK12, DKR_CC_UNK12);
        gSPTextureRectangle((*dList)++, (D_80127CAC << 2), (D_80127CAE << 2), ((D_80127CAC + temp_a3) << 2), ((D_80127CAE + 10) << 2), 0, (temp_a2 << 5), 0, 1024, 1024);
    }
    return temp_a3;
}
