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
    1000000000,
    100000000,
    10000000,
    1000000,
    100000,
    10000,
    1000,
    100,
    10,
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
DialogueBoxBackground (*gDialogueBoxBackground)[1];
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

    gFonts = (FontData *)(fontAssetData); // ???
    gNumberOfFonts = *(fontAssetData);
    gFonts = (FontData *)(fontAssetData + 1);

    for (i = 0; i < gNumberOfFonts; i++) {
        gFonts[i].unk28[0] = 0;
    }

    gDialogueBoxBackground = allocate_from_main_pool_safe(DIALOGUEBOXBACKGROUND_TOTAL_SIZE + unk8012A7EC_TOTAL_SIZE, COLOR_TAG_YELLOW);
    D_8012A7EC = (unk8012A7EC *)((u8 *)gDialogueBoxBackground + DIALOGUEBOXBACKGROUND_TOTAL_SIZE);

    for (i = 0; i < DIALOGUEBOXBACKGROUND_COUNT; i++) {
        (*gDialogueBoxBackground)[i].xpos = 0;
        (*gDialogueBoxBackground)[i].ypos = 0;
        (*gDialogueBoxBackground)[i].x1 = 0;
        (*gDialogueBoxBackground)[i].y1 = 0;
        (*gDialogueBoxBackground)[i].x2 = SCREEN_WIDTH - 1;
        (*gDialogueBoxBackground)[i].y2 = SCREEN_HEIGHT - 1;
        (*gDialogueBoxBackground)[i].width = SCREEN_WIDTH;
        (*gDialogueBoxBackground)[i].height = SCREEN_HEIGHT;
        (*gDialogueBoxBackground)[i].backgroundColourR = 0xFF;
        (*gDialogueBoxBackground)[i].backgroundColourG = 0xFF;
        (*gDialogueBoxBackground)[i].backgroundColourB = 0xFF;
        (*gDialogueBoxBackground)[i].backgroundColourA = 0;
        (*gDialogueBoxBackground)[i].textColourR = 0xFF;
        (*gDialogueBoxBackground)[i].textColourG = 0xFF;
        (*gDialogueBoxBackground)[i].textColourB = 0xFF;
        (*gDialogueBoxBackground)[i].textColourA = 0;
        (*gDialogueBoxBackground)[i].textBGColourR = 0xFF;
        (*gDialogueBoxBackground)[i].textBGColourG = 0xFF;
        (*gDialogueBoxBackground)[i].textBGColourB = 0xFF;
        (*gDialogueBoxBackground)[i].textBGColourA = 0;
        (*gDialogueBoxBackground)[i].opacity = 0xFF;
        (*gDialogueBoxBackground)[i].font = 0xFF;
        if (i != 0) {
            (*gDialogueBoxBackground)[i].flags = DIALOGUE_BOX_UNK_01;
        } else {
            (*gDialogueBoxBackground)[i].flags = 0;
        }
        (*gDialogueBoxBackground)[i].unk20 = 0;
        (*gDialogueBoxBackground)[i].unk22 = 0;
        (*gDialogueBoxBackground)[i].text = 0;
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
        (*gDialogueBoxBackground)[0].font = arg0;
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
    (*gDialogueBoxBackground)[0].textColourR = red;
    (*gDialogueBoxBackground)[0].textColourG = green;
    (*gDialogueBoxBackground)[0].textColourB = blue;
    (*gDialogueBoxBackground)[0].textColourA = alpha;
    (*gDialogueBoxBackground)[0].opacity = opacity;
}

void set_text_background_color(s32 red, s32 green, s32 blue, s32 alpha) {
    (*gDialogueBoxBackground)[0].textBGColourR = red;
    (*gDialogueBoxBackground)[0].textBGColourG = green;
    (*gDialogueBoxBackground)[0].textBGColourB = blue;
    (*gDialogueBoxBackground)[0].textBGColourA = alpha;
}

// Unused?
void func_800C4404(Gfx **displayList, char *text, s32 alignmentFlags) {
    func_800C45A4(displayList, &(*gDialogueBoxBackground)[0], text, alignmentFlags, 1.0f);
}

void draw_text(Gfx **displayList, s32 xpos, s32 ypos, char *text, s32 alignmentFlags) {
    DialogueBoxBackground *temp = &(*gDialogueBoxBackground)[0];
    temp->xpos = (xpos == POS_CENTRED) ? temp->width >> 1 : xpos;
    temp->ypos = (ypos == POS_CENTRED) ? temp->height >> 1 : ypos;
    func_800C45A4(displayList, temp, text, alignmentFlags, 1.0f);
}

// Unused?
void func_800C44C0(Gfx **displayList, s32 arg1, char *text, s32 alignmentFlags) {
    if (arg1 >= 0 && arg1 < 8) {
        DialogueBoxBackground *temp = &gDialogueBoxBackground[arg1];
        func_800C45A4(displayList, temp, text, alignmentFlags, 1.0f);
    }
}

// Unused?
void func_800C4510(Gfx **displayList, s32 arg1, s32 xpos, s32 ypos, char *text, s32 alignmentFlags) {
    if (arg1 >= 0 && arg1 < 8) {
        DialogueBoxBackground *temp = &gDialogueBoxBackground[arg1];
        temp->xpos = (xpos == POS_CENTRED) ? temp->width >> 1 : xpos;
        temp->ypos = (ypos == POS_CENTRED) ? temp->height >> 1 : ypos;
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
        font = (*gDialogueBoxBackground)[0].font;
    }
    fontData = &gFonts[font];
    while (*text != '\0') {
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

void set_current_dialogue_box_coords(s32 arg0, s32 x1, s32 y1, s32 x2, s32 y2) {
    if (arg0 > 0 && arg0 < 8) {
        DialogueBoxBackground *temp = &gDialogueBoxBackground[arg0];
        temp->xpos = 0;
        temp->ypos = 0;
        if (x1 < x2) {
            temp->x1 = (s16)x1;
            temp->x2 = (s16)x2;
        } else {
            temp->x2 = (s16)x1;
            temp->x1 = (s16)x2;
        }
        if (y1 < y2) {
            temp->y1 = (s16)y1;
            temp->y2 = (s16)y2;
        } else {
            temp->y2 = (s16)y1;
            temp->y1 = (s16)y2;
        }
        temp->width = (temp->x2 - temp->x1) + 1;
        temp->height = (temp->y2 - temp->y1) + 1;
    }
}

void set_dialogue_font(s32 arg0, s32 font) {
    if (arg0 >= 0 && arg0 < 8) {
        DialogueBoxBackground *temp = &gDialogueBoxBackground[arg0];
        if (font < gNumberOfFonts) {
            temp->font = font;
        }
    }
}

void set_current_dialogue_background_colour(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0 > 0 && arg0 < 8) {
        DialogueBoxBackground *temp = &gDialogueBoxBackground[arg0];
        temp->backgroundColourR = arg1;
        temp->backgroundColourG = arg2;
        temp->backgroundColourB = arg3;
        temp->backgroundColourA = arg4;
    }
}

void set_current_text_colour(s32 arg0, s32 red, s32 green, s32 blue, s32 alpha, s32 opacity) {
    DialogueBoxBackground *temp;
    if (arg0 <= 0 || arg0 >= 8) {
        return;
    }
    temp = &gDialogueBoxBackground[arg0];
    temp->textColourR = red;
    temp->textColourG = green;
    temp->textColourB = blue;
    temp->textColourA = alpha;
    temp->opacity = opacity;
}

void set_current_text_background_colour(s32 arg0, s32 red, s32 green, s32 blue, s32 alpha) {
    DialogueBoxBackground *temp;
    if (arg0 <= 0 || arg0 >= 8) {
        return;
    }
    temp = &gDialogueBoxBackground[arg0];
    temp->textBGColourR = red;
    temp->textBGColourG = green;
    temp->textBGColourB = blue;
    temp->textBGColourA = alpha;
}

// Unused?
void func_800C5094(s32 arg0, s32 arg1, s32 arg2) {
    DialogueBoxBackground *temp;
    if (arg0 <= 0 || arg0 >= 8) {
        return;
    }
    temp = &gDialogueBoxBackground[arg0];
    temp->unk20 += arg1;
    temp->unk22 += arg2;
}

// Unused?
void func_800C50D8(s32 arg0) {
    DialogueBoxBackground *temp;
    if (arg0 <= 0 || arg0 >= 8) {
        return;
    }
    temp = &gDialogueBoxBackground[arg0];
    temp->unk20 = 0;
    temp->unk22 = 0;
}

// Unused?
void func_800C510C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    render_dialogue_text(arg0, (*gDialogueBoxBackground)[arg0].xpos, (*gDialogueBoxBackground)[arg0].ypos, arg1, arg2, arg3);
}

GLOBAL_ASM("asm/non_matchings/font/render_dialogue_text.s")

// Unused
void func_800C5428(s32 arg0, DialogueBox *arg1) {
    DialogueBoxBackground *temp;
    DialogueBox *temp_24;
    DialogueBox **temp_24_ptr;

    temp = &gDialogueBoxBackground[arg0];
    temp_24_ptr = &temp->text;
    temp_24 = temp->text;
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
    DialogueBoxBackground *temp;
    DialogueBox *temp_24, *temp_24_2;

    temp = &gDialogueBoxBackground[arg0];
    temp_24 = temp->text;
    if (temp_24 != NULL) {
        temp_24_2 = temp_24; // This seems redundant.
        while (temp_24_2 != NULL) {
            temp_24_2->unk01 = 0xFF;
            temp_24_2 = temp_24_2->unk1C;
        }
        temp->text = NULL;
    }
}

// Unused
void func_800C54E8(s32 arg0, unk800C54E8 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    FontData *fontData;
    DialogueBoxBackground *temp;

    temp = &gDialogueBoxBackground[arg0];

    if (arg1 != NULL) {
        if (arg1->unk19 != 0xFF) {
            fontData = &gFonts[arg1->unk19];
            if (arg4 != 4) {
                switch (arg4) {
                    case 1:
                        arg3 *= fontData->unk22;
                        break;
                    case 2:
                        arg3 *= (temp->height / fontData->unk22) * fontData->unk22;
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

void open_dialogue_box(s32 arg0) {
    (*gDialogueBoxBackground)[arg0].flags |= DIALOGUE_BOX_OPEN;
}

void close_dialogue_box(s32 arg0) {
    (*gDialogueBoxBackground)[arg0].flags &= DIALOGUE_BOX_CLOSED;
}

// Unused?
void func_800C564C(s32 arg0) {
    (*gDialogueBoxBackground)[arg0].flags |= DIALOGUE_BOX_UNUSED_01;
}

// Unused?
void func_800C5678(s32 arg0) {
    (*gDialogueBoxBackground)[arg0].flags &= DIALOGUE_BOX_UNUSED_02;
}

// Unused?
void func_800C56A4(s32 arg0) {
    (*gDialogueBoxBackground)[arg0].flags |= DIALOGUE_BOX_UNK_01;
}

void func_800C56D0(s32 arg0) {
    (*gDialogueBoxBackground)[arg0].flags &= DIALOGUE_BOX_UNK_02;
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

    for (i = 1; i < 8; i++) {
        if ((*gDialogueBoxBackground)[i].flags & DIALOGUE_BOX_OPEN) {
            if ((*gDialogueBoxBackground)[i].flags & DIALOGUE_BOX_UNK_01) {
                func_800C5B58(arg0, arg1, arg2, i);
            } else {
                func_800C5B58(arg0, 0, 0, i);
            }
        }
    }
}

#ifdef NON_MATCHING
void s32_to_string(char **outString, s32 number) {
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
    for (i = 0; i < 9; i++) {
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
    DialogueBoxBackground *temp;
    DialogueBox *temp_24;
    s32 i;
    s32 x0, x1;
    char sp6C[256];
    s32 y0, y1;

    temp = &gDialogueBoxBackground[arg3];

    if (temp->backgroundColourA != 0) {
        gSPDisplayList((*dlist)++, &D_800E3690);
        gDkrDmaDisplayList((*dlist)++, ((u8 *)&D_800E36C8[1]) + 0x80000000, 2);
        gDPSetEnvColor((*dlist)++, 0, 0, 0, 0);
        if ((temp->x2 - temp->x1) < 10 || (temp->y2 - temp->y1) < 10) {
            render_fill_rectangle(dlist, temp->x1 - 2, temp->y1 - 2, temp->x2 + 2, temp->y2 + 2);
        } else {
            render_fill_rectangle(dlist, temp->x1 - 2, temp->y1 + 2, temp->x1 + 2, temp->y2 - 2);
            render_fill_rectangle(dlist, temp->x1 - 2, temp->y1 - 2, temp->x2 + 2, temp->y1 + 2);
            render_fill_rectangle(dlist, temp->x2 - 2, temp->y1 + 2, temp->x2 + 2, temp->y2 - 2);
            render_fill_rectangle(dlist, temp->x1 - 2, temp->y2 - 2, temp->x2 + 2, temp->y2 + 2);
        }
        gDPPipeSync((*dlist)++);
        gDPSetEnvColor((*dlist)++, temp->backgroundColourR, temp->backgroundColourG, temp->backgroundColourB, temp->backgroundColourA);
        for (i = 0; D_800E3710[i] >= 0; i += 5) {
            x0 = D_800E3710[i] + temp->x1;
            y0 = (D_800E3710[i + 1]) ? D_800E3710[i + 2] + temp->y2 : D_800E3710[i + 2] + temp->y1;
            x1 = temp->x2 - D_800E3710[i];
            y1 = (D_800E3710[i + 3]) ? D_800E3710[i + 4] + temp->y2 : D_800E3710[i + 4] + temp->y1;
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
    temp_24 = temp->text;
    while (temp_24 != NULL) {
        temp->xpos = temp_24->unk8 + temp_24->unkC;
        temp->ypos = temp_24->unkA + temp_24->unkE;
        temp->textColourR = temp_24->unk10;
        temp->textColourG = temp_24->unk11;
        temp->textColourB = temp_24->unk12;
        temp->textColourA = temp_24->unk13;
        temp->textBGColourR = temp_24->unk14;
        temp->textBGColourG = temp_24->unk15;
        temp->textBGColourB = temp_24->unk16;
        temp->textBGColourA = temp_24->unk17;
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
