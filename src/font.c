/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C3C00 */

#include "font.h"
#include "menu.h"
#include "textures_sprites.h"

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
    1000000000, 100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10,
}; 

s8 D_800E3710[48] = {
    4,  FALSE,  0, FALSE,  1, 
    2,  FALSE,  1, FALSE,  2, 
    1,  FALSE,  2, FALSE,  4, 
    0,  FALSE,  4,  TRUE, -4, 
    1,   TRUE, -4,  TRUE, -2, 
    2,   TRUE, -2,  TRUE, -1, 
    4,   TRUE, -1,  TRUE,  0, 
    -1, 0, 0, 0, 0, // End of Data
    0, 0, 0, 0, 0, 0, 0, 0,
};

OSDevMgr __osPiDevMgr = { 0, NULL, NULL, NULL, NULL, NULL, NULL, };

/*******************************/

/************ .bss ************/

s32 gNumberOfFonts;
FontData *gFonts;
unk8012A7E8 (*D_8012A7E8)[1];
unk8012A7EC (*D_8012A7EC)[1];
s32 D_8012A7F0;
s8 D_8012A7F4;
s32 D_8012A7F8;
s32 D_8012A7FC;

/******************************/
    
void load_fonts(void) {
    s32 *fontAssetData;
    s32 i;

    fontAssetData = load_asset_section_from_rom(ASSET_BINARY_44);
    
    gFonts = (FontData*)(fontAssetData); // ???
    gNumberOfFonts = *(fontAssetData);
    gFonts = (FontData*)(fontAssetData + 1);
    
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
                fontData->texturePointers[i] = load_texture(fontData->unk40[i]);
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
                    free_texture(fontData->texturePointers[i]);
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

// Unused?
void func_800C4404(Gfx** displayList, char *text, s32 alignmentFlags) {
    func_800C45A4(displayList, &(*D_8012A7E8)[0], text, alignmentFlags, 1.0f);
}

void draw_text(Gfx** displayList, s32 xpos, s32 ypos, char *text, s32 alignmentFlags) {
    unk8012A7E8 *temp = &(*D_8012A7E8)[0];
    temp->xpos = (xpos == -0x8000) ? temp->unkC >> 1 : xpos;
    temp->ypos = (ypos == -0x8000) ? temp->unkE >> 1 : ypos;
    func_800C45A4(displayList, temp, text, alignmentFlags, 1.0f);
}

// Unused?
void func_800C44C0(Gfx** displayList, s32 arg1, char *text, s32 alignmentFlags) {
    if (arg1 >= 0 && arg1 < 8) {
        unk8012A7E8 *temp = &D_8012A7E8[arg1];
        func_800C45A4(displayList, temp, text, alignmentFlags, 1.0f);
    }
}

// Unused?
void func_800C4510(Gfx** displayList, s32 arg1, s32 xpos, s32 ypos, char *text, s32 alignmentFlags) {
    if (arg1 >= 0 && arg1 < 8) {
        unk8012A7E8 *temp = &D_8012A7E8[arg1];
        temp->xpos = (xpos == -0x8000) ? temp->unkC >> 1 : xpos;
        temp->ypos = (ypos == -0x8000) ? temp->unkE >> 1 : ypos;
        func_800C45A4(displayList, temp, text, alignmentFlags, 1.0f);
    }
}

GLOBAL_ASM("asm/non_matchings/font/func_800C45A4.s")

// Should be functionally equivalent.
#ifdef NON_MATCHING
s32 func_800C4DA0(u8 *text, s32 x, s32 font) {
    s32 diffX, thisDiffX;
    FontData *fontData;
    FontCharData *fontCharData;
    
    if (text == NULL) {
        return 0;
    }
    diffX = x;
    if (font < 0) {
        font = (*D_8012A7E8)[0].font;
    }
    fontData = &gFonts[font];
    while(*text != '\0') {
        u8 ch = *text;
        thisDiffX = diffX;
        if ((ch < 0x21) || (ch >= 0x80)) {
            if (ch == '\t') { // Tab character
                diffX = (diffX + fontData->unk26) - (diffX % fontData->unk26);
            } else {
                diffX += fontData->unk24;
            }
        } else {
            fontCharData = &fontData->unk100[(ch - 0x20) & 0xFF];
            if (fontCharData->unk0 != 0xFF) {
                if (fontData->unk20 == 0) {
                    diffX += fontCharData->unk1;
                } else {
                    diffX += fontData->unk20;
                }
            }
        }
        if (D_8012A7F0 != 0 && thisDiffX != diffX) {
            diffX--;
        }
        text++;
    }
    return diffX - x;
}
#else
GLOBAL_ASM("asm/non_matchings/font/func_800C4DA0.s")
#endif

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

// Unused
void func_800C5428(s32 arg0, unk8012A7E8_24 *arg1) {
    unk8012A7E8 *temp;
    unk8012A7E8_24 *temp_24;
    unk8012A7E8_24 **temp_24_ptr;
    
    temp = &D_8012A7E8[arg0];
    temp_24_ptr = &temp->unk24;
    temp_24 = temp->unk24;
    while ((temp_24 != NULL) && (temp_24 != arg1)) {
        temp_24_ptr = &temp_24->unk1C;
        temp_24 = temp_24->unk1C;
    }
    if (temp_24 != NULL) {
        *temp_24_ptr = temp_24->unk1C;
        arg1->unk01 = 0xFF;
    }
}

void func_800C5494(s32 arg0) {
    unk8012A7E8 *temp;
    unk8012A7E8_24 *temp_24, *temp_24_2;
    
    temp = &D_8012A7E8[arg0];
    temp_24 = temp->unk24;
    if (temp_24 != NULL) {
        temp_24_2 = temp_24; // This seems redundant. 
        while (temp_24_2 != NULL) {
            temp_24_2->unk01 = 0xFF;
            temp_24_2 = temp_24_2->unk1C;
        }
        temp->unk24 = NULL;
    }
}

// Unused
void func_800C54E8(s32 arg0, unk800C54E8 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    FontData *fontData;
    unk8012A7E8 *temp;
    
    temp = &D_8012A7E8[arg0];

    if(arg1 != NULL){
        if (arg1->unk19 != 0xFF) {
            fontData = &gFonts[arg1->unk19];
            if(arg4 != 4) {
                switch(arg4) {
                    case 1:
                        arg3 *= fontData->unk22;
                        break;
                    case 2:
                        arg3 *= (temp->unkE / fontData->unk22) * fontData->unk22;
                        break;
                }
                arg1->unkC += arg2;
                arg1->unkE += arg3;
                return;
            }
            arg1->unkC = 0;
            arg1->unkE = 0;
            return;
        }
    }
}

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

void func_800C5B58(Gfx **dlist, s32 *arg1, s32 *arg2, s32 arg3) {
    unk8012A7E8 *temp;
    unk8012A7E8_24 *temp_24;
    s32 i;
    s32 x0, x1;
    char sp6C[256];
    s32 y0, y1;
    
    temp = &D_8012A7E8[arg3];
    
    if (temp->unk13 != 0) {
        gSPDisplayList((*dlist)++, &D_800E3690);
        gDkrDmaDisplayList((*dlist)++, ((u8*)&D_800E36C8[1]) + 0x80000000, 2);
        gDPSetEnvColor((*dlist)++, 0, 0, 0, 0);
        if ((temp->unk8 - temp->unk4) < 10 || (temp->unkA - temp->unk6) < 10) {
            render_fill_rectangle(dlist, temp->unk4 - 2, temp->unk6 - 2, temp->unk8 + 2, temp->unkA + 2);
        } else {
            render_fill_rectangle(dlist, temp->unk4 - 2, temp->unk6 + 2, temp->unk4 + 2, temp->unkA - 2);
            render_fill_rectangle(dlist, temp->unk4 - 2, temp->unk6 - 2, temp->unk8 + 2, temp->unk6 + 2);
            render_fill_rectangle(dlist, temp->unk8 - 2, temp->unk6 + 2, temp->unk8 + 2, temp->unkA - 2);
            render_fill_rectangle(dlist, temp->unk4 - 2, temp->unkA - 2, temp->unk8 + 2, temp->unkA + 2);
        }
        gDPPipeSync((*dlist)++);
        gDPSetEnvColor((*dlist)++, temp->unk10, temp->unk11, temp->unk12, temp->unk13);
        for (i = 0; D_800E3710[i] >= 0; i += 5) {
            x0 = D_800E3710[i] + temp->unk4;
            y0 = (D_800E3710[i + 1]) ? D_800E3710[i + 2] + temp->unkA : D_800E3710[i + 2] + temp->unk6;
            x1 = temp->unk8 - D_800E3710[i];
            y1 = (D_800E3710[i + 3]) ? D_800E3710[i + 4] + temp->unkA : D_800E3710[i + 4] + temp->unk6;
            render_fill_rectangle(dlist, x0, y0, x1, y1);
        }
        gDPPipeSync((*dlist)++);
    }
    if (arg1 != NULL && arg2 != NULL) {
        if (!D_800E36E8) {
            func_8009E9A0();
            D_800E36E8 = 1;
        }
        D_8012A7F4 = 2;
        func_8009E9B0(temp, dlist, arg1, arg2);
    }
    temp_24 = temp->unk24;
    while (temp_24 != NULL) {
        temp->xpos = temp_24->unk8 + temp_24->unkC;
        temp->ypos = temp_24->unkA + temp_24->unkE;
        temp->colorRed = temp_24->unk10;
        temp->colorGreen = temp_24->unk11;
        temp->colorBlue = temp_24->unk12;
        temp->colorAlpha = temp_24->unk13;
        temp->bgRed = temp_24->unk14;
        temp->bgGreen = temp_24->unk15;
        temp->bgBlue = temp_24->unk16;
        temp->bgAlpha = temp_24->unk17;
        temp->opacity = temp_24->unk18;
        temp->font = temp_24->unk19;
        parse_string_with_number(temp_24->unk4, &sp6C, temp_24->unk01);
        func_800C45A4(dlist, temp, &sp6C, 0, 1.0f);
        temp_24 = temp_24->unk1C;
    }
}

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
