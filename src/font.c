/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C3C00 */

#include "memory.h"
#include "video.h"

#include "structs.h"
#include "types.h"
#include "macros.h"
#include "asset_sections.h"
#include "libultra_internal.h"
#include "f3ddkr.h"

/************ .data ************/

Gfx D_800E3690[] = {
    gsDPPipeSync(), 
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPClearGeometryMode(G_ZBUFFER | G_FOG), 
    gsDPPipeSync(), 
    gsSPEndDisplayList(),
};

// Unused?
Gfx D_800E36C8[][2] = {    
    {
        gsDPSetCombineMode(DKR_CC_UNK11, DKR_CC_UNK11),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT_NOPERSP, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_ENVIRONMENT, DKR_CC_ENVIRONMENT),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT_NOPERSP, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    },
};

s8 D_800E36E8 = 0;

// Descending powers of 10
s32 gDescPowsOf10[9] = {
    1000000000, 100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10
}; 

s8 D_800E3710[48] = {
    4, 0, 0, 0, 1, 2, 0, 1, 0, 2, 1, 0, 2, 0, 4, 0, 
    0, 4, 1, -4, 1, 1, -4, 1, -2, 2, 1, -2, 1, -1, 4, 1, 
    -1, 1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

OSDevMgr __osPiDevMgr = { 0, NULL, NULL, NULL, NULL, NULL, NULL };

/*******************************/

/************ .bss ************/

#define OS_PIM_STACKSIZE	4096
u8 piThreadStack[256];//piThreadStack[OS_PIM_STACKSIZE];

s32 D_80129BB0[256];
s32 D_80129FB0[3];
s32 D_80129FBC;
s32 D_80129FC0;
s32 D_80129FC4;
s32 D_80129FC8;
s32 D_80129FCC;
s32 D_80129FD0[4];
s32 D_80129FE0[2];
s32 D_80129FE8;
s32 D_80129FF0[6];
s32 D_8012A008;
s32 D_8012A00C;
s32 D_8012A010;
s32 D_8012A014;
s32 D_8012A018;
s32 D_8012A01C;
s32 D_8012A020[2];
s32 D_8012A028[20];
s32 D_8012A078;
s32 D_8012A07C;
s32 D_8012A080;
s32 D_8012A084;
s32 D_8012A088;
s32 D_8012A08C;
s32 D_8012A090;
s32 D_8012A094;
s32 D_8012A098;
s32 D_8012A09C;
s32 D_8012A0A0;
s32 D_8012A0A4;
s32 D_8012A0A8;
s32 D_8012A0AC;
s32 D_8012A0B0;
s32 D_8012A0B4;
s32 D_8012A0B8;
s32 D_8012A0BC;
s32 D_8012A0C0;
s32 D_8012A0C4;
s32 D_8012A0C8;
s32 D_8012A0CC;
s32 D_8012A0D0;
s32 D_8012A0D4;
s32 D_8012A0D8;
s32 D_8012A0DC;
s32 D_8012A0E0;
s32 D_8012A0E8[64];
s32 D_8012A1E8[256];
s32 D_8012A5E8[3];
s32 D_8012A5F4;
s32 D_8012A5F8;
s32 D_8012A5FC;
s32 D_8012A600[72];
s32 D_8012A720;
s32 D_8012A724;
s32 D_8012A728[2];
s32 D_8012A730;
s8 D_8012A734;
s8 D_8012A735;
s8 D_8012A736;
s8 D_8012A737;
s32 D_8012A738;
s32 D_8012A73C;
s32 D_8012A740;
s32 D_8012A744;
s32 D_8012A748;
s32 D_8012A74C;
s32 D_8012A750;
s32 D_8012A754;
s32 D_8012A758;
s32 D_8012A75C;
s32 D_8012A760;
s32 D_8012A764;
s32 D_8012A768;
s32 D_8012A76C;
s32 D_8012A770;
s32 D_8012A774;
s32 D_8012A778;
s32 D_8012A77C;
s32 D_8012A780;
s8 D_8012A784;
s8 D_8012A785;
s8 D_8012A786;
s8 D_8012A787;
s8 D_8012A788;
s8 D_8012A789;
s8 D_8012A78A;
s16 D_8012A78C;
s16 D_8012A78E;
s32 D_8012A790[2];
s32 D_8012A798;
s32 D_8012A79C;
s32 D_8012A7A0;
s32 D_8012A7A4;
s16 D_8012A7A8;
s16 D_8012A7AA;
s16 D_8012A7AC;
s16 D_8012A7AE;
s16 D_8012A7B0;
s16 D_8012A7B2;
s16 D_8012A7B4;
s16 D_8012A7B6;
s16 D_8012A7B8;
s16 D_8012A7BA;
s32 D_8012A7C0[2];
s32 D_8012A7C8;
s32 D_8012A7CC;
s32 D_8012A7D0;
s32 D_8012A7D4;
s32 D_8012A7D8;
s32 D_8012A7DC;

s32 gNumberOfFonts;

/* Size: 8 bytes */
typedef struct FontCharData {
    u8 unk0;
    u8 unk1[7];
} FontCharData;

/* Size: 0x400 bytes */
typedef struct FontData {
    char name[0x28];
    u8 unk28[24];
    s16 unk40[32];
    TextureHeader *texturePointers[32];
    FontCharData unk100[96];
} FontData;

FontData* gFonts;

/* Size: 0x28 bytes */
typedef struct unk8012A7E8_24 {
    u8 unk00;
    u8 unk01;
    u8 pad02[0x1A];
    struct unk8012A7E8_24* unk1C;
} unk8012A7E8_24;

/* Size: 0x28 bytes */
typedef struct unk8012A7E8 {
    s16 xpos;
    s16 ypos;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    u8 colorRed;
    u8 colorGreen;
    u8 colorBlue;
    u8 colorAlpha;
    u8 bgRed;
    u8 bgGreen;
    u8 bgBlue;
    u8 bgAlpha;
    u8 opacity;
    u8 font;
    u16 unk1E;
    s16 unk20;
    s16 unk22;
    unk8012A7E8_24 *unk24;
} unk8012A7E8;

unk8012A7E8 (*D_8012A7E8)[1];

/* Size: 0x20 bytes */
typedef struct unk8012A7EC {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    s32 unk18;
    s32 unk1C;
} unk8012A7EC;
unk8012A7EC (*D_8012A7EC)[1];

s32 D_8012A7F0;
s8 D_8012A7F4;
s32 D_8012A7F8;
s32 D_8012A7FC;
/******************************/


void func_800C4170(s32 arg0);

#define unk8012A7E8_COUNT 8
#define unk8012A7EC_COUNT 64
#define unk8012A7E8_TOTAL_SIZE (sizeof(unk8012A7E8) * unk8012A7E8_COUNT)
#define unk8012A7EC_TOTAL_SIZE (sizeof(unk8012A7EC) * unk8012A7EC_COUNT)
    
void load_fonts(void) {
    u8 *fontAssetData;
    s32 i;

    fontAssetData = load_asset_section_from_rom(ASSET_BINARY_44);
    
    gFonts = (FontData*)(fontAssetData); // ???
    gNumberOfFonts = *((s32*)fontAssetData);
    gFonts = (FontData*)(fontAssetData + 4);
    
    for (i = 0; i < gNumberOfFonts; i++) {
        gFonts[i].unk28[0] = 0;
    }
    
    D_8012A7E8 = allocate_from_main_pool_safe(unk8012A7E8_TOTAL_SIZE + unk8012A7EC_TOTAL_SIZE, COLOR_TAG_YELLOW);
    D_8012A7EC = (unk8012A7EC*)((u8*)D_8012A7E8 + unk8012A7E8_TOTAL_SIZE);
    
    for (i = 0; i < unk8012A7E8_COUNT; i++) {
        (*D_8012A7E8)[i].xpos = 0;
        (*D_8012A7E8)[i].ypos = 0;
        (*D_8012A7E8)[i].unk4 = 0;
        (*D_8012A7E8)[i].unk6 = 0;
        (*D_8012A7E8)[i].unk8 = SCREEN_WIDTH - 1;
        (*D_8012A7E8)[i].unkA = SCREEN_HEIGHT - 1;
        (*D_8012A7E8)[i].unkC = SCREEN_WIDTH;
        (*D_8012A7E8)[i].unkE = SCREEN_HEIGHT;
        (*D_8012A7E8)[i].unk10 = 0xFF;
        (*D_8012A7E8)[i].unk11 = 0xFF;
        (*D_8012A7E8)[i].unk12 = 0xFF;
        (*D_8012A7E8)[i].unk13 = 0;
        (*D_8012A7E8)[i].colorRed = 0xFF;
        (*D_8012A7E8)[i].colorGreen = 0xFF;
        (*D_8012A7E8)[i].colorBlue = 0xFF;
        (*D_8012A7E8)[i].colorAlpha = 0;
        (*D_8012A7E8)[i].bgRed = 0xFF;
        (*D_8012A7E8)[i].bgGreen = 0xFF;
        (*D_8012A7E8)[i].bgBlue = 0xFF;
        (*D_8012A7E8)[i].bgAlpha = 0;
        (*D_8012A7E8)[i].opacity = 0xFF;
        (*D_8012A7E8)[i].font = 0xFF;
        if (i != 0) {
            (*D_8012A7E8)[i].unk1E = 0x4000;
        } else {
            (*D_8012A7E8)[i].unk1E = 0;
        }
        (*D_8012A7E8)[i].unk20 = 0;
        (*D_8012A7E8)[i].unk22 = 0;
        (*D_8012A7E8)[i].unk24 = 0;
    }
    for (i = 0; i < unk8012A7EC_COUNT; i++) {
        (*D_8012A7EC)[i].unk1 = 0xFF;
        (*D_8012A7EC)[i].unk4 = 0;
        (*D_8012A7EC)[i].unk10 = 0xFF;
        (*D_8012A7EC)[i].unk11 = 0xFF;
        (*D_8012A7EC)[i].unk12 = 0xFF;
        (*D_8012A7EC)[i].unk13 = 0;
        (*D_8012A7EC)[i].unk14 = 0xFF;
        (*D_8012A7EC)[i].unk15 = 0xFF;
        (*D_8012A7EC)[i].unk16 = 0xFF;
        (*D_8012A7EC)[i].unk17 = 0;
        (*D_8012A7EC)[i].unk1C = 0;
    }
    func_800C4170(0);
    func_800C4170(1);
    D_8012A7F0 = 0;
}

void func_800C4164(s32 arg0) {
    D_8012A7F0 = arg0;
}

#ifdef NON_MATCHING
// Mostly has regalloc issues.
void func_800C4170(s32 arg0) {
    if (arg0 < gNumberOfFonts) {
        FontData *fontData = &gFonts[arg0];
        fontData->unk28[0]++;
        if (fontData->unk28[0] == 1) {
            // Minor issue with this loop.
            s32 i = 0;
            while (fontData->unk40[i] != -1) {
                fontData->texturePointers[i] = func_8007AE74(fontData->unk40[i]);
                i++;
                if (i >= 64) {
                    break;
                }
            }
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/font/func_800C4170.s")
#endif

#ifdef NON_MATCHING
// Mostly has regalloc issues.
void func_800C422C(s32 arg0) {
    if (arg0 < gNumberOfFonts) {
        FontData *fontData = &gFonts[arg0];
        if (fontData->unk28[0] > 0) {
            fontData->unk28[0]--;
            if ((fontData->unk28[0] & 0xFF) == 0) {
                // Minor issue with this loop.
                s32 i = 0;
                while (fontData->unk40[i] != -1) {
                    func_8007B2BC(fontData->texturePointers[i]);
                    fontData->texturePointers[i] = NULL;
                    i++;
                    if (i >= 32) {
                        break;
                    }
                }
            }
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/font/func_800C422C.s")
#endif

void set_text_font(s32 arg0) {
    if (arg0 < gNumberOfFonts) {
        (*D_8012A7E8)[0].font = arg0;
    }
}

#ifdef NON_MATCHING

// Unused. Has regalloc issues
TextureHeader *func_800C4318(s32 font, u8 arg1) {
    if (font < gNumberOfFonts) {
        FontData *fontData = &gFonts[font];
        if (fontData->unk28[0] != 0) {
            arg1 = fontData->unk100[(arg1 - 32) & 0xFF].unk0;
            if (arg1 != 0xFF) {
                return fontData->texturePointers[arg1];
            }
            return NULL;
        }
    }
    // @bug: No return statement. The function will return whatever happens to be in v0 
    //       before this function was called.
}

#else
GLOBAL_ASM("asm/non_matchings/font/func_800C4318.s")
#endif

void set_text_color(s32 red, s32 green, s32 blue, s32 alpha, s32 opacity) {
    (*D_8012A7E8)[0].colorRed = red;
    (*D_8012A7E8)[0].colorGreen = green;
    (*D_8012A7E8)[0].colorBlue = blue;
    (*D_8012A7E8)[0].colorAlpha = alpha;
    (*D_8012A7E8)[0].opacity = opacity;
}

void set_text_background_color(s32 red, s32 green, s32 blue, s32 alpha) {
    (*D_8012A7E8)[0].bgRed = red;
    (*D_8012A7E8)[0].bgGreen = green;
    (*D_8012A7E8)[0].bgBlue = blue;
    (*D_8012A7E8)[0].bgAlpha = alpha;
}

void func_800C45A4(s32, unk8012A7E8*, s32, s32, f32);

// Unused?
void func_800C4404(Gfx** displayList, char* text, s32 alignmentFlags) {
    func_800C45A4(displayList, &(*D_8012A7E8)[0], text, alignmentFlags, 1.0f);
}

void draw_text(Gfx** displayList, s32 xpos, s32 ypos, char* text, s32 alignmentFlags) {
    unk8012A7E8 *temp = &(*D_8012A7E8)[0];
    temp->xpos = (xpos == -0x8000) ? temp->unkC >> 1 : xpos;
    temp->ypos = (ypos == -0x8000) ? temp->unkE >> 1 : ypos;
    func_800C45A4(displayList, temp, text, alignmentFlags, 1.0f);
}

// Unused?
void func_800C44C0(Gfx** displayList, s32 arg1, char* text, s32 alignmentFlags) {
    if (arg1 >= 0 && arg1 < 8) {
        unk8012A7E8 *temp = &D_8012A7E8[arg1];
        func_800C45A4(displayList, temp, text, alignmentFlags, 1.0f);
    }
}

// Unused?
void func_800C4510(Gfx** displayList, s32 arg1, s32 xpos, s32 ypos, char* text, s32 alignmentFlags) {
    if (arg1 >= 0 && arg1 < 8) {
        unk8012A7E8 *temp = &D_8012A7E8[arg1];
        temp->xpos = (xpos == -0x8000) ? temp->unkC >> 1 : xpos;
        temp->ypos = (ypos == -0x8000) ? temp->unkE >> 1 : ypos;
        func_800C45A4(displayList, temp, text, alignmentFlags, 1.0f);
    }
}

GLOBAL_ASM("asm/non_matchings/font/func_800C45A4.s")
GLOBAL_ASM("asm/non_matchings/font/func_800C4DA0.s")

void func_800C4EDC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0 > 0 && arg0 < 8) {
        unk8012A7E8 *temp = &D_8012A7E8[arg0];
        temp->xpos = 0;
        temp->ypos = 0;
        if (arg1 < arg3) {
            temp->unk4 = (s16) arg1;
            temp->unk8 = (s16) arg3;
        } else {
            temp->unk8 = (s16) arg1;
            temp->unk4 = (s16) arg3;
        }
        if (arg2 < arg4) {
            temp->unk6 = (s16) arg2;
            temp->unkA = (s16) arg4;
        } else {
            temp->unkA = (s16) arg2;
            temp->unk6 = (s16) arg4;
        }
        temp->unkC = (temp->unk8 - temp->unk4) + 1;
        temp->unkE = (temp->unkA - temp->unk6) + 1;
    }
}

void func_800C4F7C(s32 arg0, s32 font) {
    if (arg0 >= 0 && arg0 < 8) {
        unk8012A7E8 *temp = &D_8012A7E8[arg0];
        if (font < gNumberOfFonts) {
            temp->font = font;
        }
    }
}


void func_800C4FBC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0 > 0 && arg0 < 8) {
        unk8012A7E8 *temp = &D_8012A7E8[arg0];
        temp->unk10 = arg1;
        temp->unk11 = arg2;
        temp->unk12 = arg3;
        temp->unk13 = arg4;
    }
}

void func_800C5000(s32 arg0, s32 red, s32 green, s32 blue, s32 alpha, s32 opacity) {
    unk8012A7E8 *temp;
    if (arg0 <= 0 || arg0 >= 8) {
        return;
    }
    temp = &D_8012A7E8[arg0];
    temp->colorRed = red;
    temp->colorGreen = green;
    temp->colorBlue = blue;
    temp->colorAlpha = alpha;
    temp->opacity = opacity;
}

void func_800C5050(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    unk8012A7E8 *temp;
    if (arg0 <= 0 || arg0 >= 8) {
        return;
    }
    temp = &D_8012A7E8[arg0];
    temp->bgRed = arg1;
    temp->bgGreen = arg2;
    temp->bgBlue = arg3;
    temp->bgAlpha = arg4;
}

// Unused?
void func_800C5094(s32 arg0, s32 arg1, s32 arg2) {
    unk8012A7E8 *temp;
    if (arg0 <= 0 || arg0 >= 8) {
        return;
    }
    temp = &D_8012A7E8[arg0];
    temp->unk20 += arg1;
    temp->unk22 += arg2;
}

// Unused?
void func_800C50D8(s32 arg0) {
    unk8012A7E8 *temp;
    if (arg0 <= 0 || arg0 >= 8) {
        return;
    }
    temp = &D_8012A7E8[arg0];
    temp->unk20 = 0;
    temp->unk22 = 0;
}

// Unused?
void func_800C510C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_800C5168(arg0, (*D_8012A7E8)[arg0].xpos, (*D_8012A7E8)[arg0].ypos, arg1, arg2, arg3);
}

GLOBAL_ASM("asm/non_matchings/font/func_800C5168.s")
GLOBAL_ASM("asm/non_matchings/font/func_800C5494.s")

void func_800C55F4(s32 arg0) {
    (*D_8012A7E8)[arg0].unk1E |= 0x8000;
}

void func_800C5620(s32 arg0) {
    (*D_8012A7E8)[arg0].unk1E &= 0x7FFF;
}

// Unused?
void func_800C564C(s32 arg0) {
    (*D_8012A7E8)[arg0].unk1E |= 0x0001;
}

// Unused?
void func_800C5678(s32 arg0) {
    (*D_8012A7E8)[arg0].unk1E &= 0xFFFE;
}

// Unused?
void func_800C56A4(s32 arg0) {
    (*D_8012A7E8)[arg0].unk1E |= 0x4000;
}

void func_800C56D0(s32 arg0) {
    (*D_8012A7E8)[arg0].unk1E &= 0xBFFF;
}

void func_800C56FC(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;

    if (D_800E36E8 != 0) {
        D_8012A7F4--;
        if (D_8012A7F4 == 0) {
            func_8009E9A8();
            D_800E36E8 = 0;
        }
    }
    
    for(i = 1; i < 8; i++) {
        if ((*D_8012A7E8)[i].unk1E & 0x8000) {
            if ((*D_8012A7E8)[i].unk1E & 0x4000) {
                func_800C5B58(arg0, arg1, arg2, i);
            } else {
                func_800C5B58(arg0, 0, 0, i);
            }
        }
    }
}

#ifdef NON_MATCHING
void s32_to_string(char** outString, s32 number) {
    u8 digit;
    s32 i;
    s32 hasDigit; // boolean
    s32 div;
    
    // Check for a negative number
    if (number < 0) { 
        **outString = '-';
        number = -number;
        (*outString)++;
    }
    
    // Loop through digit places.
    for(i = 0; i < 9; i++){
        hasDigit = FALSE;
        digit = '0';
        if (number >= gDescPowsOf10[i]) {
            div = number / gDescPowsOf10[i];
            hasDigit = TRUE;
            digit = '0' + div;
            number -= div * gDescPowsOf10[i];
        }
        if (hasDigit) {
            **outString = digit;
            (*outString)++;
        }
    }

    // One's digit place
    **outString = '0' + number;
    (*outString)++;
}
#else
void s32_to_string(char**, s32);
GLOBAL_ASM("asm/non_matchings/font/s32_to_string.s")
#endif

/**
 * Draws a solid color rectangle at the coordinates specified.
 * ulx, uly = upper-left position
 * lrx, lry = lower-right position
 */
void render_fill_rectangle(Gfx **dlist, s32 ulx, s32 uly, s32 lrx, s32 lry) {
    u32 temp_v0 = get_video_width_and_height_as_s32();
    if (lrx >= 0 && ulx < (temp_v0 & 0xFFFF) && lry >= 0 && uly < (temp_v0 >> 16)) {
        if (ulx < 0) {
            ulx = 0;
        }
        if (uly < 0) {
            uly = 0;
        }
        gDPFillRectangle((*dlist)++, ulx, uly, lrx, lry);
    }
}

GLOBAL_ASM("asm/non_matchings/font/func_800C5B58.s")

/**
 * Takes in a string and a number, and replaces each instance of the 
 * character '~' with the number.
 */
void parse_string_with_number(unsigned char *input, char *output, s32 number) {
    while (*input != '\0') {
        if ('~' == *input) { // ~ is equivalent to a %d.
            // output the number as part of the string
            s32_to_string(&output, number);
            input++;
        } else {
            *output = *input;
            input++;
            output++;
        }
    }
    *output = '\0'; // null terminator
}


/*********************************************************************************/

extern OSMesgQueue piAccessQueue; //piAccessQueue
extern u32 __osPiAccessQueueEnabled; //__osPiAccessQueueEnabled
extern OSDevMgr __osPiDevMgr;
void __osDevMgrMain(void);

// bss variables
OSThread piThread;
s32 D_8012A9B0[64];
OSMesgQueue piEventQueue;
OSMesg piEventBuf[2];

// osCreatePiManager is compiled with -mips1, so it belongs in the source folder.
// However, I can't just put this in another file because the piThreadStack
// variable is at the top of this file's bss

void osCreatePiManager(OSPri pri, OSMesgQueue *cmdQ, OSMesg *cmdBuf, s32 cmdMsgCnt)
{
	u32 savedMask;
	OSPri oldPri;
	OSPri myPri;
	if (!__osPiDevMgr.active)
	{
		osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
		osCreateMesgQueue(&piEventQueue, (OSMesg*)&piEventBuf, 1);
		if (!__osPiAccessQueueEnabled)
			__osPiCreateAccessQueue();
		osSetEventMesg(OS_EVENT_PI, &piEventQueue, (OSMesg)0x22222222);
		oldPri = -1;
		myPri = osGetThreadPri(NULL);
		if (myPri < pri)
		{
			oldPri = myPri;
			osSetThreadPri(NULL, pri);
		}
		savedMask = __osDisableInt();
		__osPiDevMgr.active = 1;
		__osPiDevMgr.thread = &piThread;
		__osPiDevMgr.cmdQueue = cmdQ;
		__osPiDevMgr.evtQueue = &piEventQueue;
		__osPiDevMgr.acsQueue = &piAccessQueue;
		__osPiDevMgr.dma = osPiRawStartDma;
        __osPiDevMgr.edma = osEPiRawStartDma;

		osCreateThread(&piThread, 0, __osDevMgrMain, &__osPiDevMgr, &piThreadStack[OS_PIM_STACKSIZE], pri);
		osStartThread(&piThread);
		__osRestoreInt(savedMask);
		if (oldPri != -1)
		{
			osSetThreadPri(NULL, oldPri);
		}
	}
}
