/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B4940 */

#include "printf.h"
#include "types.h"
#include "macros.h"
#include "f3ddkr.h"
#include "thread0_epc.h"
#include "stdarg.h"
#include "textures_sprites.h"
#include "stdio.h"
#include "unknown_078050.h"

/************ .data ************/

s32 D_800E2EF0 = 0;

//Char width is (v - u) + 1
TexFontCoords gDebugFontCoords[3][32] = {
    //ASCII symbols and numbers
    //(This is out of order since they subtract 0x21 instead of 0x20)
    //!"#$%&'()*+,-./0123456789:;<=>?{SPACE}
    {                         
        { 0x02, 0x04, }, //!
        { 0x06, 0x08, }, //"
        { 0x0A, 0x0F, }, //#
        { 0x11, 0x15, }, //$
        { 0x17, 0x1F, }, //%
        { 0x21, 0x27, }, //&
        { 0x29, 0x2B, }, //'
        { 0x2D, 0x2F, }, //(  
        { 0x31, 0x33, }, //)
        { 0x35, 0x38, }, //*
        { 0x3A, 0x3F, }, //+
        { 0x41, 0x43, }, //,
        { 0x45, 0x48, }, //-
        { 0x4A, 0x4B, }, //.
        { 0x4D, 0x50, }, ///
        { 0x52, 0x56, }, //0
        { 0x58, 0x5B, }, //1
        { 0x5D, 0x62, }, //2
        { 0x64, 0x68, }, //3
        { 0x6A, 0x6F, }, //4
        { 0x71, 0x76, }, //5
        { 0x78, 0x7D, }, //6
        { 0x7F, 0x84, }, //7
        { 0x86, 0x8B, }, //8
        { 0x8D, 0x92, }, //9
        { 0x94, 0x96, }, //:
        { 0x98, 0x9A, }, //;
        { 0x9D, 0xA2, }, //<
        { 0xA5, 0xA9, }, //=
        { 0xAB, 0xB0, }, //>
        { 0xB3, 0xB8, }, //?
        { 0x00, 0x01, }, //{SPACE} 
    },
    //ASCII Upper Case
    //@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_
    {
        { 0x00, 0x09, }, //@
        { 0x0B, 0x11, }, //A
        { 0x13, 0x19, }, //B
        { 0x1B, 0x21, }, //C
        { 0x23, 0x29, }, //D
        { 0x2B, 0x31, }, //E
        { 0x33, 0x38, }, //F
        { 0x3A, 0x41, }, //G
        { 0x43, 0x49, }, //H
        { 0x4B, 0x4C, }, //I
        { 0x4E, 0x53, }, //J
        { 0x55, 0x5B, }, //K
        { 0x5D, 0x62, }, //L
        { 0x64, 0x6B, }, //M
        { 0x6D, 0x73, }, //N
        { 0x75, 0x7B, }, //O
        { 0x7D, 0x83, }, //P
        { 0x85, 0x8B, }, //Q
        { 0x8D, 0x93, }, //R
        { 0x95, 0x9B, }, //S
        { 0x9D, 0xA3, }, //T
        { 0xA5, 0xAA, }, //U
        { 0xAC, 0xB2, }, //V
        { 0xB4, 0xBC, }, //W
        { 0xBE, 0xC4, }, //X
        { 0xC6, 0xCC, }, //Y
        { 0xCE, 0xD3, }, //Z
        { 0xD5, 0xD7, }, //[
        { 0xD9, 0xDC, }, //{backslash}
        { 0xDE, 0xE0, }, //]
        { 0xE2, 0xE7, }, //^
        { 0xE9, 0xEF, }, //_
    },
    //ASCII Lower Case
    //`abcdefghijklmnopqrstuvwxyz{|}~
    {        
        { 0x00, 0x01, }, //`
        { 0x03, 0x08, }, //a
        { 0x09, 0x0F, }, //b
        { 0x11, 0x16, }, //c
        { 0x18, 0x1D, }, //d
        { 0x1F, 0x24, }, //e
        { 0x26, 0x28, }, //f
        { 0x2A, 0x2F, }, //g    
        { 0x31, 0x36, }, //h
        { 0x38, 0x39, }, //i
        { 0x3B, 0x3D, }, //j
        { 0x3F, 0x43, }, //k
        { 0x45, 0x46, }, //l
        { 0x48, 0x4F, }, //m
        { 0x51, 0x56, }, //n
        { 0x58, 0x5D, }, //o    
        { 0x5F, 0x64, }, //p
        { 0x66, 0x6B, }, //q
        { 0x6C, 0x70, }, //r
        { 0x72, 0x77, }, //s
        { 0x79, 0x7C, }, //t
        { 0x7E, 0x82, }, //u
        { 0x84, 0x89, }, //v
        { 0x8B, 0x92, }, //w    
        { 0x94, 0x99, }, //x
        { 0x9B, 0xA0, }, //y
        { 0xA2, 0xA6, }, //z
        { 0xA8, 0xAB, }, //{
        { 0xAD, 0xAE, }, //|
        { 0xB0, 0xB3, }, //}
        { 0xB5, 0xB9, }, //~
        { 0xB5, 0xB9, }, //ASCII DEL, so it just reuses the tilde above.
    }, 
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
extern char gDebugPrintBufferStart[];
extern char *gDebugPrintBufferEnd;

/******************************/

GLOBAL_ASM("asm/non_matchings/printf/_itoa.s")

//Official Name: sprintfSetSpacingCodes
void func_800B4A08(s32 arg0) {
    D_800E2EF0 = arg0;
}

/* Official name: sprintf(?) */
UNUSED void func_800B4A14(char *s, char *format, ...) {
    va_list args;
    va_start(args, format);
    //!@bug Should be calling vsprintf here.
    sprintf(s, format, args);
    va_end(args);
}

//Official Name: vsprintf
GLOBAL_ASM("asm/non_matchings/printf/sprintf.s")

void diPrintfInit(void) {
    gTexture0 = load_texture(0);
    gTexture1 = load_texture(1);
    gTexture2 = load_texture(2);
    gDebugPrintBufferEnd = gDebugPrintBufferStart;
}

//Official Name: diPrintf
s32 render_printf(const char *format, ...) {
    va_list args;
    s32 written;
    va_start(args, format);
    if ((gDebugPrintBufferEnd - gDebugPrintBufferStart) > 0x800) {
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

/**
 * At the end of a frame, iterate through the debug text buffer and print it on screen.
 * Soft-clear the buffer afterwards by setting the endpoint to the start point.
 * Official Name: diPrintfAll
 */
void print_debug_strings(Gfx **dList) {
    char *buffer;
    u32 widthAndHeight;

    init_rdp_and_framebuffer(dList);
    widthAndHeight = get_video_width_and_height_as_s32();
    D_80127CD2 = GET_VIDEO_HEIGHT(widthAndHeight);
    D_80127CD0 = GET_VIDEO_WIDTH(widthAndHeight);
    gDPSetScissor((*dList)++, 0, 0, 0, D_80127CD0, D_80127CD2);
    func_800B6E50();
    gSPDisplayList((*dList)++, dDebugFontSettings);
    buffer = (char *) gDebugPrintBufferStart;
    func_800B6EE0();
    gDebugFontTexture = -1;
    D_80127CB4 = 0;
    D_80127CB0 = D_80127CAC;
    D_80127CB2 = D_80127CAE;
    while ((s32)buffer != (s32)gDebugPrintBufferEnd) {
        D_80127CB8 = FALSE;
        buffer += func_800B653C(dList, buffer);
    }
    func_800B695C(dList, (u16) D_80127CB0, (u16) D_80127CB2, D_80127CAC, D_80127CAE + 10);
    buffer = (char *) gDebugPrintBufferStart;
    func_800B6EE0();
    gDebugFontTexture = -1;
    D_80127CB4 = 0;
    while ((s32)buffer != (s32)gDebugPrintBufferEnd) {
        D_80127CB8 = TRUE;
        buffer += func_800B653C(dList, buffer);
    }
    gDebugPrintBufferEnd = gDebugPrintBufferStart;
}

UNUSED void func_800B61E0(void) {
    gDebugPrintBufferEnd = gDebugPrintBufferStart;
    func_800B6EE0();
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
void set_render_printf_position(u16 x, u16 y) {
    RENDER_PRINTF_CMD_SET_POSITION(x, y)
}

/**
 * Definitely has some fakematch shenanigans.
 * This will return the length in pixels of a given string using the debug small font.
*/
UNUSED s32 func_800B63F4(const char *format, ...) {
    s32 pad;
    s32 fontCharU;
    s32 stringLength;
    char s[255];
    char *ch;
    va_list args;
    va_start(args, format);

    stringLength = 0;
    func_800B4A08(1);
    sprintf(s, format, args);
    func_800B4A08(0);
    for (ch = &s[0]; *ch != '\0'; ch++) {
        pad = *ch;
        if (*ch != (0, '\n')) {
            if (pad == ' ') {
                stringLength += 6;
                if (1){ }
            } else {
                if (*ch < 0x40) {
                    //Character is a symbol or number and not a letter
                    gDebugFontTexture = 0;
                    *ch-= 0x21;
                } else if (*ch < 0x60) {
                    //Character is a upper case letter
                    gDebugFontTexture = 1;
                    *ch -= 0x40;
                } else if (*ch < 0x80) {
                    //Character is a lower case letter
                    gDebugFontTexture = 2;
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

GLOBAL_ASM("asm/non_matchings/printf/func_800B653C.s")

void func_800B695C(Gfx **dList, u32 ulx, u32 uly, u32 lrx, u32 lry) {
    if (!((ulx == lrx) | (uly == lry))) {
        if (ulx >= 2) {
            ulx -= 2;
        }
        lrx += 2;
        gDPSetCombineMode((*dList)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPFillRectangle((*dList)++, ulx, uly, lrx, lry);
    }
}

//Loads a font texture and returns the width of the character given.
s32 func_800B69FC(Gfx **dList, s32 asciiVal) {
    s32 fontCharWidth;
    s32 fontCharU;

    if (asciiVal < 0x40) {
        //Character is a symbol or number and not a letter
        if (gDebugFontTexture != 0) {
            if (D_80127CB8) {
                gDPLoadTextureBlock((*dList)++, OS_PHYSICAL_TO_K0(gTexture0 + 1), G_IM_FMT_IA, G_IM_SIZ_8b, 192, 11, 0, 2, 2, 0, 0, 0, 0);
            }
            gDebugFontTexture = 0;
        }
        asciiVal -= 0x21;
    } else if (asciiVal < 0x60) {
        //Character is a upper case letter
        if (gDebugFontTexture != 1) {
            if (D_80127CB8) {
                gDPLoadTextureBlock((*dList)++, OS_PHYSICAL_TO_K0(gTexture1 + 1), G_IM_FMT_IA, G_IM_SIZ_8b, 248, 11, 0, 2, 2, 0, 0, 0, 0);
            }
            gDebugFontTexture = 1;
        }
        asciiVal -= 0x40;
    } else if (asciiVal < 0x80) {
        //Character is a lower case letter
        if (gDebugFontTexture != 2) {
            if (D_80127CB8) {
                gDPLoadTextureBlock((*dList)++, OS_PHYSICAL_TO_K0(gTexture2 + 1), G_IM_FMT_IA, G_IM_SIZ_8b, 192, 11, 0, 2, 2, 0, 0, 0, 0);
            }
            gDebugFontTexture = 2;
        }
        asciiVal -= 0x60;
    }
    fontCharU = gDebugFontCoords[gDebugFontTexture][asciiVal].u;
    fontCharWidth = (gDebugFontCoords[gDebugFontTexture][asciiVal].v - fontCharU) + 1;
    if (D_80127CB8) {
        gDPSetCombineMode((*dList)++, DKR_CC_UNK12, DKR_CC_UNK12);
        gSPTextureRectangle((*dList)++, (D_80127CAC << 2), (D_80127CAE << 2), ((D_80127CAC + fontCharWidth) << 2), ((D_80127CAE + 10) << 2), 0, (fontCharU << 5), 0, 1024, 1024);
    }
    return fontCharWidth;
}

void func_800B6E50(void) {
    if (D_80127CD0 < 0x141) {
        D_80127CBC = 0x10;
        D_80127CC0 = D_80127CD0 - 0x10;
    } else {
        D_80127CBC = 0x20;
        D_80127CC0 = D_80127CD0 - 0x20;
    }
    if (D_80127CD2 < 0xF1) {
        D_80127CC4 = 0x10;
        D_80127CC8 = D_80127CD2 - 0x10;
    } else {
        D_80127CC4 = 0x20;
        D_80127CC8 = D_80127CD2 - 0x20;
    }
}

void func_800B6EE0(void) {
    D_80127CAC = D_80127CBC;
    D_80127CAE = D_80127CC4;
}

void func_800B6F04(void) {
    D_80127CAC = D_80127CBC;
    D_80127CAE += 11;
}
