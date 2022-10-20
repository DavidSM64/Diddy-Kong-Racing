/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C3C00 */

#include "font.h"
#include "menu.h"
#include "textures_sprites.h"

/************ .data ************/

Gfx dDialogueBoxBegin[] = {
    gsDPPipeSync(),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPClearGeometryMode(G_ZBUFFER | G_FOG),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx dDialogueBoxDrawModes[][2] = {
    {
        gsDPSetCombineMode(DKR_CC_UNK11, DKR_CC_UNK11),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT_NOPERSP, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(DKR_CC_ENVIRONMENT, DKR_CC_ENVIRONMENT),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT_NOPERSP, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    },
};

s8 sDialogueBoxIsOpen = FALSE;

// Descending powers of 10
s32 gDescPowsOf10[9] = {
    1000000000, 100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10,
};

// The dialogue box will draw in pieces, using properties from each line. It starts with a box
// and goes inwards or outwards depending on the direction, set by the define.

#define INWARDS  0
#define OUTWARDS 1

s8 sDialogueBoxDimensions[48] = {
    /*X Offset*/ 4,  INWARDS,  /*Y Start*/  0,  INWARDS,  /*Y end*/  1,
    /*X Offset*/ 2,  INWARDS,  /*Y Start*/  1,  INWARDS,  /*Y end*/  2,
    /*X Offset*/ 1,  INWARDS,  /*Y Start*/  2,  INWARDS,  /*Y end*/  4,
    /*X Offset*/ 0,  INWARDS,  /*Y Start*/  4,  OUTWARDS, /*Y end*/ -4,
    /*X Offset*/ 1,  OUTWARDS, /*Y Start*/ -4,  OUTWARDS, /*Y end*/ -2,
    /*X Offset*/ 2,  OUTWARDS, /*Y Start*/ -2,  OUTWARDS, /*Y end*/ -1,
    /*X Offset*/ 4,  OUTWARDS, /*Y Start*/ -1,  OUTWARDS,  0,
    /*X Offset*/ -1, 0, 0, 0, 0, // End of Data
    /*X Offset*/ 0, 0, 0, 0, 0, 0, 0, 0,
};

#undef INWARDS
#undef OUTWARDS

OSDevMgr __osPiDevMgr = {
    0, NULL, NULL, NULL, NULL, NULL, NULL,
};

/*******************************/

/************ .bss ************/

s32 gNumberOfFonts;
FontData *gFonts;
DialogueBoxBackground *gDialogueBoxBackground;
unk8012A7EC *D_8012A7EC;
s32 D_8012A7F0; // Boolean value, seems to be related to X placement of menus on the X Axis?
s8 sDialogueBoxCloseTimer;
s32 D_8012A7F8;
s32 D_8012A7FC;

/******************************/

/**
 * Loads the text asset data and sets the default values for each dialogue box in the list.
 */
void load_fonts(void) {
    u32 *fontAssetData;
    s32 i;

    fontAssetData = load_asset_section_from_rom(ASSET_FONTS);

    gFonts = (FontData *) (fontAssetData); // ???
    gNumberOfFonts = *(fontAssetData);
    gFonts = (FontData *) (fontAssetData + 1);

    for (i = 0; i < gNumberOfFonts; i++) {
        gFonts[i].unk28[0] = 0;
    }

    gDialogueBoxBackground = (DialogueBoxBackground *) allocate_from_main_pool_safe(
        DIALOGUEBOXBACKGROUND_TOTAL_SIZE + unk8012A7EC_TOTAL_SIZE, COLOUR_TAG_YELLOW);
    D_8012A7EC = (unk8012A7EC *) &gDialogueBoxBackground[DIALOGUEBOXBACKGROUND_COUNT];

    for (i = 0; i < DIALOGUEBOXBACKGROUND_COUNT; i++) {
        gDialogueBoxBackground[i].xpos = 0;
        gDialogueBoxBackground[i].ypos = 0;
        gDialogueBoxBackground[i].x1 = 0;
        gDialogueBoxBackground[i].y1 = 0;
        gDialogueBoxBackground[i].x2 = SCREEN_WIDTH - 1;
        gDialogueBoxBackground[i].y2 = SCREEN_HEIGHT - 1;
        gDialogueBoxBackground[i].width = SCREEN_WIDTH;
        gDialogueBoxBackground[i].height = SCREEN_HEIGHT;
        gDialogueBoxBackground[i].backgroundColourR = 255;
        gDialogueBoxBackground[i].backgroundColourG = 255;
        gDialogueBoxBackground[i].backgroundColourB = 255;
        gDialogueBoxBackground[i].backgroundColourA = 0;
        gDialogueBoxBackground[i].textColourR = 255;
        gDialogueBoxBackground[i].textColourG = 255;
        gDialogueBoxBackground[i].textColourB = 255;
        gDialogueBoxBackground[i].textColourA = 0;
        gDialogueBoxBackground[i].textBGColourR = 255;
        gDialogueBoxBackground[i].textBGColourG = 255;
        gDialogueBoxBackground[i].textBGColourB = 255;
        gDialogueBoxBackground[i].textBGColourA = 0;
        gDialogueBoxBackground[i].opacity = 255;
        gDialogueBoxBackground[i].font = FONT_UNK_FF;
        gDialogueBoxBackground[i].flags = (i != 0) ? DIALOGUE_BOX_UNK_01 : 0;
        gDialogueBoxBackground[i].unk20 = 0;
        gDialogueBoxBackground[i].unk22 = 0;
        gDialogueBoxBackground[i].textBox = 0;
    }
    for (i = 0; i < unk8012A7EC_COUNT; i++) {
        D_8012A7EC[i].unk1 = 255;
        D_8012A7EC[i].text = NULL;
        D_8012A7EC[i].textColourR = 255;
        D_8012A7EC[i].textColourG = 255;
        D_8012A7EC[i].textColourB = 255;
        D_8012A7EC[i].textColourA = 0;
        D_8012A7EC[i].textBGColourR = 255;
        D_8012A7EC[i].textBGColourG = 255;
        D_8012A7EC[i].textBGColourB = 255;
        D_8012A7EC[i].textBGColourA = 0;
        D_8012A7EC[i].nextBox = NULL;
    }
    load_font(ASSET_FONTS_FUNFONT);
    load_font(ASSET_FONTS_SMALLFONT);
    D_8012A7F0 = 0;
}

void func_800C4164(s32 arg0) {
    D_8012A7F0 = arg0;
}

void load_font(s32 fontID) {
    if (fontID < gNumberOfFonts) {
        FontData *fontData = &gFonts[fontID];
        fontData->unk28[0]++;
        if (fontData->unk28[0] == 1) {
            s32 i = 0;
            while (i < 32 && fontData->unk40[i] != -1) {
                fontData->texturePointers[i] = load_texture(fontData->unk40[i]);
                i++;
            }
        }
    }
}

void unload_font(s32 fontID) {
    if (fontID < gNumberOfFonts) {
        FontData *fontData = &gFonts[fontID];
        if (fontData->unk28[0] > 0) {
            fontData->unk28[0]--;
            if (fontData->unk28[0] == 0) {
                s32 i = 0;
                while (i < 32 && fontData->unk40[i] != -1) {
                    free_texture(fontData->texturePointers[i]);
                    fontData->texturePointers[i] = NULL;
                    i++;
                }
            }
        }
    }
}

/**
 * Set the font of the current dialogue box's text.
 */
void set_text_font(s32 fontID) {
    if (fontID < gNumberOfFonts) {
        gDialogueBoxBackground[0].font = fontID;
    }
}

UNUSED TextureHeader *func_800C4318(s32 font, u8 arg1) {
    FontData *fontData;
    u8 pointerIndex;

    if (font < gNumberOfFonts) {
        fontData = &gFonts[font];
        if (fontData->unk28[0] != 0) {
            arg1 -= 32;
            pointerIndex = fontData->unk100[arg1].unk0;
            if (pointerIndex != 0xFF) {
                return fontData->texturePointers[pointerIndex];
            }
            return NULL;
        }
    }
    // @bug: No return statement. The function will return whatever happens to be in v0
    //       before this function was called.
}

/**
 * Sets the colour of the current dialogue box's text.
 */
void set_text_colour(s32 red, s32 green, s32 blue, s32 alpha, s32 opacity) {
    gDialogueBoxBackground[0].textColourR = red;
    gDialogueBoxBackground[0].textColourG = green;
    gDialogueBoxBackground[0].textColourB = blue;
    gDialogueBoxBackground[0].textColourA = alpha;
    gDialogueBoxBackground[0].opacity = opacity;
}

/**
 * Sets the colour of the current dialogue box's text background.
 */
void set_text_background_colour(s32 red, s32 green, s32 blue, s32 alpha) {
    gDialogueBoxBackground[0].textBGColourR = red;
    gDialogueBoxBackground[0].textBGColourG = green;
    gDialogueBoxBackground[0].textBGColourB = blue;
    gDialogueBoxBackground[0].textBGColourA = alpha;
}

// Unused?
void func_800C4404(Gfx **displayList, char *text, AlignmentFlags alignmentFlags) {
    func_800C45A4(displayList, &gDialogueBoxBackground[0], text, alignmentFlags, 1.0f);
}

/**
 * Builds the background settings, then renders the given text at a given position.
 */
void draw_text(Gfx **displayList, s32 xpos, s32 ypos, char *text, AlignmentFlags alignmentFlags) {
    DialogueBoxBackground *temp = &gDialogueBoxBackground[0];
    temp->xpos = (xpos == POS_CENTRED) ? temp->width >> 1 : xpos;
    temp->ypos = (ypos == POS_CENTRED) ? temp->height >> 1 : ypos;
    func_800C45A4(displayList, temp, text, alignmentFlags, 1.0f);
}

UNUSED void func_800C44C0(Gfx **displayList, s32 dialogueBoxID, char *text,
                          AlignmentFlags alignmentFlags) {
    if (dialogueBoxID >= 0 && dialogueBoxID < DIALOGUEBOXBACKGROUND_COUNT) {
        DialogueBoxBackground *temp = &gDialogueBoxBackground[dialogueBoxID];
        func_800C45A4(displayList, temp, text, alignmentFlags, 1.0f);
    }
}

UNUSED void func_800C4510(Gfx **displayList, s32 dialogueBoxID, s32 xpos, s32 ypos, char *text,
                          AlignmentFlags alignmentFlags) {
    if (dialogueBoxID >= 0 && dialogueBoxID < DIALOGUEBOXBACKGROUND_COUNT) {
        DialogueBoxBackground *temp = &gDialogueBoxBackground[dialogueBoxID];
        temp->xpos = (xpos == POS_CENTRED) ? temp->width >> 1 : xpos;
        temp->ypos = (ypos == POS_CENTRED) ? temp->height >> 1 : ypos;
        func_800C45A4(displayList, temp, text, alignmentFlags, 1.0f);
    }
}

void func_800C45A4(Gfx **dlist, DialogueBoxBackground *arg1, char *text, AlignmentFlags alignmentFlags,
                   f32 arg4) {
    s32 temp_f4;
    s32 temp_t9;
    s32 ypos;
    s32 xpos;
    TextureHeader *texture;
    s32 textureLrx;
    s32 textureLry;
    s32 textureS;
    s32 textureT;
    s32 textureUlx;
    s32 textureUly;
    s32 textureWidth;
    s32 textureHeight;
    s32 xAlignmentDiff;
    s32 yAlignmentDiff;
    s32 lastTextureIndex;
    s32 charIndex;
    s32 var_t0;
    s32 newData;
    s32 textureIndex;
    FontData *fontData;
    s32 newTempX;
    s32 newTempY;
    char curChar;
    xAlignmentDiff = -1;
    lastTextureIndex = -1;
    if (text != NULL) {
        textureLry = 0;
        xpos = arg1->xpos;
        ypos = arg1->ypos;
        fontData = &gFonts[arg1->font];
        gSPDisplayList((*dlist)++, dDialogueBoxBegin);
        if (arg1 != gDialogueBoxBackground) {
            temp_f4 = (((arg1->y2 - arg1->y1) + 1) / ((f32) 2)) * arg4;
            temp_t9 = (arg1->y1 + arg1->y2) >> 1;
            gDPSetScissor((*dlist)++, 0, arg1->x1, temp_t9 - temp_f4, arg1->x2, temp_t9 + temp_f4);
        }
        if (alignmentFlags & (HORZ_ALIGN_RIGHT | HORZ_ALIGN_CENTER)) {
            xAlignmentDiff = func_800C4DA0(text, xpos, arg1->font);
            if (alignmentFlags & HORZ_ALIGN_RIGHT) {
                xpos = (xpos - xAlignmentDiff) + 1;
            } else {
                xpos -= xAlignmentDiff >> 1;
            }
        }
        if (alignmentFlags & VERT_ALIGN_BOTTOM) {
            ypos = (ypos - fontData->unk22) + 1;
        }
        if (alignmentFlags & VERT_ALIGN_MIDDLE) {
            ypos -= fontData->unk22 >> 1;
        }
        if (arg1->textBGColourA != 0) {
            gDPSetEnvColor((*dlist)++, arg1->textBGColourR, arg1->textBGColourG, arg1->textBGColourB,
                           arg1->textBGColourA);
            if (xAlignmentDiff == -1) {
                xAlignmentDiff = func_800C4DA0(text, xpos, arg1->font);
            }
            newTempX = xpos + xAlignmentDiff - 1;
            newTempY = (ypos + fontData->unk22 - 1);
            gDkrDmaDisplayList((*dlist)++, OS_K0_TO_PHYSICAL(dDialogueBoxDrawModes[1]), 2);
            gDPFillRectangle((*dlist)++, xpos + arg1->x1, ypos + arg1->y1, newTempX + arg1->x1,
                             newTempY + arg1->y1);
            gDPPipeSync((*dlist)++);
        }
        gDPSetPrimColor((*dlist)++, textureLry, 0, 255, 255, 255, arg1->opacity);
        gDPSetEnvColor((*dlist)++, arg1->textColourR, arg1->textColourG, arg1->textColourB,
                       arg1->textColourA);
        gDkrDmaDisplayList((*dlist)++, OS_K0_TO_PHYSICAL(dDialogueBoxDrawModes[0]), 2);
        gDPPipeSync((*dlist)++);
        xpos += arg1->unk20;
        ypos += arg1->unk22;
        for (charIndex = 0; (text[charIndex] != '\0') && (arg1->y2 >= ypos);
             xpos += var_t0, charIndex++) {
            curChar = text[charIndex];
            newData = 0;
            var_t0 = 0;
            if ((curChar < 0x21) || (curChar >= 0x80)) {
                switch (curChar) {
                    case ' ': // Space
                        xpos += fontData->unk24;
                        break;
                    case '\n': // Line Feed
                        xpos = arg1->unk20;
                        ypos += fontData->unk22;
                        break;
                    case '\t': // Tab
                        xpos += fontData->unk26 - ((xpos - arg1->unk20) % fontData->unk26);
                        break;
                    case '\v': // VT - Vertical Tab
                        ypos += fontData->unk22;
                        break;
                    case '\r': // Carriage Return
                        xpos = arg1->unk20;
                        break;
                    default:
                        xpos += fontData->unk24;
                        break;
                }
            } else {
                curChar -= 0x20; // Convert lower case to upper case ASCII
                textureIndex = fontData->unk100[curChar].unk0;
                if (textureIndex != 0xFF) {
                    newData = 1;
                    if (lastTextureIndex != textureIndex) {
                        lastTextureIndex = textureIndex;
                        texture = fontData->texturePointers[textureIndex];
                        gDkrDmaDisplayList((*dlist)++, OS_PHYSICAL_TO_K0(texture->cmd),
                                           texture->numberOfCommands);
                    }
                    textureWidth = fontData->unk100[curChar].unk2;
                    textureHeight = fontData->unk100[curChar].unk3;
                    textureS = fontData->unk100[curChar].unk4;
                    textureT = fontData->unk100[curChar].unk5;
                    xAlignmentDiff = fontData->unk100[curChar].unk6;
                    yAlignmentDiff = fontData->unk100[curChar].unk7;
                    var_t0 =
                        (fontData->unk20 == 0) ? (fontData->unk100[curChar].unk1) : (fontData->unk20);
                    newData = 1;
                }
            }
            if (newData) {
                textureUlx = ((arg1->x1 + xpos) + textureWidth) * 4;
                textureUly = ((arg1->y1 + ypos) + textureHeight) * 4;
                textureLrx = (xAlignmentDiff * 4) + textureUlx;
                newTempY = (yAlignmentDiff * 4) + textureUly;
                textureS *= 32;
                textureT *= 32;
                if ((textureUlx < 0) && (textureLrx > 0)) {
                    textureS += (-textureUlx) * 8;
                    textureUlx = 0;
                }
                if ((textureUly <= (0 - 1)) && (newTempY > 0)) {
                    textureT += (-textureUly) * 8;
                    textureUly = 0;
                }
                gSPTextureRectangle((*dlist)++, textureUlx, textureUly, textureLrx, newTempY, 0,
                                    textureS, textureT, 1024, 1024);
                if (lastTextureIndex)
                    ;
            }
            if (D_8012A7F0 && var_t0) {
                var_t0--;
            }
        }

        arg1->xpos = xpos - arg1->unk20;
        arg1->ypos = ypos - arg1->unk22;
        gDPPipeSync((*dlist)++);
        if (arg1 != gDialogueBoxBackground) {
            func_80067A3C(dlist);
        }
        func_8007B3D0(dlist);
        gDPPipeSync((*dlist)++);
    }
}

s32 func_800C4DA0(char *text, s32 x, s32 font) {
    s32 diffX, thisDiffX;
    FontData *fontData;
    s32 index;
    char ch;

    if (text == NULL) {
        return 0;
    }
    diffX = x;
    if (font < 0) {
        font = gDialogueBoxBackground[0].font;
    }
    fontData = &gFonts[font];
    for (index = 0; text[index] != '\0'; index++) {
        thisDiffX = diffX;
        ch = text[index];
        if ((ch < 0x21) || (ch >= 0x80)) {
            if (ch == '\t') { // Tab character
                diffX += fontData->unk26 - (diffX % fontData->unk26);
            } else {
                diffX += fontData->unk24;
            }
        } else {
            ch -= 0x20; // Convert lower case to upper case ASCII

            if (fontData->unk100[ch].unk0 != 0xFF) {
                if (fontData->unk20 == 0) {
                    diffX += fontData->unk100[ch].unk1;
                } else {
                    diffX += fontData->unk20;
                }
            }
        }
        if (D_8012A7F0 != 0 && diffX != thisDiffX) {
            diffX--;
        }
    }
    return diffX - x;
}

void set_current_dialogue_box_coords(s32 dialogueBoxID, s32 x1, s32 y1, s32 x2, s32 y2) {
    if (dialogueBoxID > 0 && dialogueBoxID < DIALOGUEBOXBACKGROUND_COUNT) {
        DialogueBoxBackground *temp = &gDialogueBoxBackground[dialogueBoxID];
        temp->xpos = 0;
        temp->ypos = 0;
        if (x1 < x2) {
            temp->x1 = (s16) x1;
            temp->x2 = (s16) x2;
        } else {
            temp->x2 = (s16) x1;
            temp->x1 = (s16) x2;
        }
        if (y1 < y2) {
            temp->y1 = (s16) y1;
            temp->y2 = (s16) y2;
        } else {
            temp->y2 = (s16) y1;
            temp->y1 = (s16) y2;
        }
        temp->width = (temp->x2 - temp->x1) + 1;
        temp->height = (temp->y2 - temp->y1) + 1;
    }
}

void set_dialogue_font(s32 dialogueBoxID, s32 font) {
    if (dialogueBoxID >= 0 && dialogueBoxID < DIALOGUEBOXBACKGROUND_COUNT) {
        DialogueBoxBackground *temp = &gDialogueBoxBackground[dialogueBoxID];
        if (font < gNumberOfFonts) {
            temp->font = font;
        }
    }
}

void set_current_dialogue_background_colour(s32 dialogueBoxID, s32 red, s32 green, s32 blue,
                                            s32 alpha) {
    if (dialogueBoxID > 0 && dialogueBoxID < DIALOGUEBOXBACKGROUND_COUNT) {
        DialogueBoxBackground *temp = &gDialogueBoxBackground[dialogueBoxID];
        temp->backgroundColourR = red;
        temp->backgroundColourG = green;
        temp->backgroundColourB = blue;
        temp->backgroundColourA = alpha;
    }
}

void set_current_text_colour(s32 dialogueBoxID, s32 red, s32 green, s32 blue, s32 alpha, s32 opacity) {
    DialogueBoxBackground *temp;
    if (dialogueBoxID <= 0 || dialogueBoxID >= DIALOGUEBOXBACKGROUND_COUNT) {
        return;
    }
    temp = &gDialogueBoxBackground[dialogueBoxID];
    temp->textColourR = red;
    temp->textColourG = green;
    temp->textColourB = blue;
    temp->textColourA = alpha;
    temp->opacity = opacity;
}

void set_current_text_background_colour(s32 dialogueBoxID, s32 red, s32 green, s32 blue, s32 alpha) {
    DialogueBoxBackground *dialogueBox;
    if (dialogueBoxID <= 0 || dialogueBoxID >= DIALOGUEBOXBACKGROUND_COUNT) {
        return;
    }
    dialogueBox = &gDialogueBoxBackground[dialogueBoxID];
    dialogueBox->textBGColourR = red;
    dialogueBox->textBGColourG = green;
    dialogueBox->textBGColourB = blue;
    dialogueBox->textBGColourA = alpha;
}

// Unused?
void func_800C5094(s32 dialogueBoxID, s32 arg1, s32 arg2) {
    DialogueBoxBackground *dialogueBox;
    if (dialogueBoxID <= 0 || dialogueBoxID >= DIALOGUEBOXBACKGROUND_COUNT) {
        return;
    }
    dialogueBox = &gDialogueBoxBackground[dialogueBoxID];
    dialogueBox->unk20 += arg1;
    dialogueBox->unk22 += arg2;
}

// Unused?
void func_800C50D8(s32 dialogueBoxID) {
    DialogueBoxBackground *dialogueBox;
    if (dialogueBoxID <= 0 || dialogueBoxID >= DIALOGUEBOXBACKGROUND_COUNT) {
        return;
    }
    dialogueBox = &gDialogueBoxBackground[dialogueBoxID];
    dialogueBox->unk20 = 0;
    dialogueBox->unk22 = 0;
}

// Unused?
void func_800C510C(s32 dialogueBoxID, char *text, s32 arg2, s32 arg3) {
    render_dialogue_text(dialogueBoxID, gDialogueBoxBackground[dialogueBoxID].xpos,
                         gDialogueBoxBackground[dialogueBoxID].ypos, text, arg2, arg3);
}

void *render_dialogue_text(s32 dialogueBoxID, s32 posX, s32 posY, char *text, s32 arg4, s32 flags) {
    s32 temp_v0_2;
    s32 var_a0;
    char buffer[256];
    unk8012A7EC *ret;
    DialogueBox *textBox;
    s32 i;
    DialogueBoxBackground *bg;
    FontData *fontData;
    DialogueBox **textBoxPtr;

    if (text == NULL) {
        return NULL;
    }

    for (i = 0, ret = NULL; (i < 64) && (ret == NULL); i++) {
        if (D_8012A7EC[i].unk1 == 0xFF) {
            ret = &D_8012A7EC[i];
        }
    }

    if (ret != NULL) {
        bg = &gDialogueBoxBackground[dialogueBoxID];
        if (posX == POS_CENTRED) {
            posX = bg->width >> 1;
        }
        if (posY == POS_CENTRED) {
            posY = bg->height >> 1;
        }
        if (bg->font != FONT_UNK_FF) {
            fontData = &gFonts[bg->font];
            if (flags & 5) {
                parse_string_with_number(text, &buffer, arg4);
                temp_v0_2 = func_800C4DA0(&buffer, posX, bg->font);
                if (flags & 1) {
                    posX = (posX - temp_v0_2) + 1;
                } else {
                    posX = posX - (temp_v0_2 >> 1);
                }
            }
            if (flags & 2) {
                posY = (posY - fontData->unk22) + 1;
            }
            if (flags & 8) {
                posY -= fontData->unk22 >> 1;
            }
        }
        if (bg->textBox == NULL) {
            bg->textBox = (DialogueBox *) ret;
            ret->nextBox = NULL;
        } else {
            textBoxPtr = &bg->textBox;
            textBox = *textBoxPtr;
            while (textBox != NULL && arg4 < textBox->textNum) {
                textBoxPtr = &textBox->nextBox;
                textBox = textBox->nextBox;
            }
            *textBoxPtr = ret;
            ret->nextBox = textBox;
        }
        ret->unk1 = arg4;
        ret->text = text;
        ret->posX = posX;
        ret->posY = posY;
        ret->unkC = 0;
        ret->unkE = 0;
        ret->textColourR = bg->textColourR;
        ret->textColourG = bg->textColourG;
        ret->textColourB = bg->textColourB;
        ret->textColourA = bg->textColourA;
        ret->textBGColourR = bg->textBGColourR;
        ret->textBGColourG = bg->textBGColourG;
        ret->textBGColourB = bg->textBGColourB;
        ret->textBGColourA = bg->textBGColourA;
        ret->opacity = bg->opacity;
        ret->font = bg->font;
        ret->flags = bg->flags;
    }

    return ret;
}

/**
 * Unused function that moved a dialogue box ID to the front of the stack.
 */

UNUSED void move_dialogue_box_to_front(s32 dialogueBoxID, DialogueBox *dialogueBox) {
    DialogueBoxBackground *dialogueBoxTemp;
    DialogueBox *dialogueTextBox;
    DialogueBox **dialogueTextBoxTemp;

    dialogueBoxTemp = &gDialogueBoxBackground[dialogueBoxID];
    dialogueTextBoxTemp = &dialogueBoxTemp->textBox;
    dialogueTextBox = dialogueBoxTemp->textBox;
    while ((dialogueTextBox != NULL) && (dialogueTextBox != dialogueBox)) {
        dialogueTextBoxTemp = &dialogueTextBox->nextBox;
        dialogueTextBox = dialogueTextBox->nextBox;
    }
    if (dialogueTextBox != NULL) {
        *dialogueTextBoxTemp = dialogueTextBox->nextBox;
        dialogueBox->textNum = DIALOGUE_NUM_NULL;
    }
}

/**
 * Unused function that moved a dialogue box ID to the front of the list.
 */

void assign_dialogue_box_id(s32 dialogueBoxID) {
    DialogueBoxBackground *dialogueBox;
    DialogueBox *dialogueTextBox, *dialogueTextBoxTemp;

    dialogueBox = &gDialogueBoxBackground[dialogueBoxID];
    dialogueTextBox = dialogueBox->textBox;
    if (dialogueTextBox != NULL) {
        dialogueTextBoxTemp = dialogueTextBox; // This seems redundant.
        while (dialogueTextBoxTemp != NULL) {
            dialogueTextBoxTemp->textNum = DIALOGUE_NUM_NULL;
            dialogueTextBoxTemp = dialogueTextBoxTemp->nextBox;
        }
        dialogueBox->textBox = NULL;
    }
}

UNUSED void func_800C54E8(s32 dialogueBoxID, unk800C54E8 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    FontData *fontData;
    DialogueBoxBackground *dialogueBox;

    dialogueBox = &gDialogueBoxBackground[dialogueBoxID];

    if (arg1 != NULL) {
        if (arg1->unk19 != 0xFF) {
            fontData = &gFonts[arg1->unk19];
            if (arg4 != 4) {
                switch (arg4) {
                    case 1:
                        arg3 *= fontData->unk22;
                        break;
                    case 2:
                        arg3 *= (dialogueBox->height / fontData->unk22) * fontData->unk22;
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

/**
 * Mark the selected dialogue box as open
 */
void open_dialogue_box(s32 dialogueBoxID) {
    gDialogueBoxBackground[dialogueBoxID].flags |= DIALOGUE_BOX_OPEN;
}

/**
 * Mark the selected dialogue box as closed
 */
void close_dialogue_box(s32 dialogueBoxID) {
    gDialogueBoxBackground[dialogueBoxID].flags &= DIALOGUE_BOX_CLOSED;
}

/**
 * Mark the selected dialogue box as an unknown value
 */
UNUSED void func_800C564C(s32 dialogueBoxID) {
    gDialogueBoxBackground[dialogueBoxID].flags |= DIALOGUE_BOX_UNUSED_01;
}

/**
 * Mark the selected dialogue box with every flag
 */
UNUSED void func_800C5678(s32 dialogueBoxID) {
    gDialogueBoxBackground[dialogueBoxID].flags &= DIALOGUE_BOX_UNUSED_02;
}

/**
 * Mark the selected dialogue box as
 */
UNUSED void func_800C56A4(s32 dialogueBoxID) {
    gDialogueBoxBackground[dialogueBoxID].flags |= DIALOGUE_BOX_UNK_01;
}

/**
 * Mark the selected dialogue box as open with
 */
void func_800C56D0(s32 dialogueBoxID) {
    gDialogueBoxBackground[dialogueBoxID].flags &= DIALOGUE_BOX_UNK_02;
}

/**
 * Main function to render each dialogue box entry.
 * Contains a timer that counts down two frames before closing a dialogue box
 * when the player exits out of one.
 */
void render_dialogue_boxes(Gfx **dlist, Mtx **mat, VertexList **verts) {
    s32 i;

    if (sDialogueBoxIsOpen) {
        sDialogueBoxCloseTimer--;
        if (sDialogueBoxCloseTimer == 0) {
            dialogue_close_stub();
            sDialogueBoxIsOpen = FALSE;
        }
    }

    for (i = 1; i < DIALOGUEBOXBACKGROUND_COUNT; i++) {
        if (gDialogueBoxBackground[i].flags & DIALOGUE_BOX_OPEN) {
            if (gDialogueBoxBackground[i].flags & DIALOGUE_BOX_UNK_01) {
                render_dialogue_box(dlist, mat, verts, i);
            } else {
                render_dialogue_box(dlist, NULL, NULL, i);
            }
        }
    }
}

void s32_to_string(char **outString, s32 number) {
    u8 digit;
    s32 i;
    s32 hasDigit; // boolean
    s32 div;
    s32 pow;
    char *ret = *outString;

    // Check for a negative number
    if (number < 0) {
        *ret = '-';
        ret++;
        number = -number;
    }

    // Loop through digit places.
    hasDigit = FALSE;
    i = 0;
    while (i < 9) {
        pow = gDescPowsOf10[i++];
        digit = '0';
        if (number >= pow) {
            hasDigit = TRUE;
            div = number / pow;
            number -= div * pow;
            digit += div;
        }
        if (hasDigit) {
            *ret = digit;
            ret++;
        }
    }

    // One's digit place
    *ret = '0' + number;
    ret++;
    *outString = ret;
}

/**
 * Draws a solid color rectangle at the coordinates specified.
 * ulx, uly = upper-left position
 * lrx, lry = lower-right position
 */
void render_fill_rectangle(Gfx **dlist, s32 ulx, s32 uly, s32 lrx, s32 lry) {
    u32 widthAndHeight = get_video_width_and_height_as_s32();
    u32 width = GET_VIDEO_WIDTH(widthAndHeight);
    u32 height = GET_VIDEO_HEIGHT(widthAndHeight);

    if (lrx >= 0 && (u32) ulx < width && lry >= 0 && (u32) uly < height) {
        if (ulx < 0) {
            ulx = 0;
        }
        if (uly < 0) {
            uly = 0;
        }
        gDPFillRectangle((*dlist)++, ulx, uly, lrx, lry);
    }
}

/**
 * Render the selected dialogue box. Background first, then text.
 */
void render_dialogue_box(Gfx **dlist, Mtx **mat, VertexList **verts, s32 dialogueBoxID) {
    DialogueBoxBackground *dialogueBox;
    DialogueBox *dialogueTextBox;
    s32 i;
    s32 x1, x2;
    char text[256];
    s32 y1, y2;

    dialogueBox = &gDialogueBoxBackground[dialogueBoxID];

    // Render dialogue box background.
    if (dialogueBox->backgroundColourA != 0) {
        gSPDisplayList((*dlist)++, dDialogueBoxBegin);
        gDkrDmaDisplayList((*dlist)++, OS_K0_TO_PHYSICAL(&dDialogueBoxDrawModes[1]), 2);
        gDPSetEnvColor((*dlist)++, 0, 0, 0, 0);
        if ((dialogueBox->x2 - dialogueBox->x1) < 10 || (dialogueBox->y2 - dialogueBox->y1) < 10) {
            render_fill_rectangle(dlist, dialogueBox->x1 - 2, dialogueBox->y1 - 2, dialogueBox->x2 + 2,
                                  dialogueBox->y2 + 2);
        } else {
            render_fill_rectangle(dlist, dialogueBox->x1 - 2, dialogueBox->y1 + 2, dialogueBox->x1 + 2,
                                  dialogueBox->y2 - 2);
            render_fill_rectangle(dlist, dialogueBox->x1 - 2, dialogueBox->y1 - 2, dialogueBox->x2 + 2,
                                  dialogueBox->y1 + 2);
            render_fill_rectangle(dlist, dialogueBox->x2 - 2, dialogueBox->y1 + 2, dialogueBox->x2 + 2,
                                  dialogueBox->y2 - 2);
            render_fill_rectangle(dlist, dialogueBox->x1 - 2, dialogueBox->y2 - 2, dialogueBox->x2 + 2,
                                  dialogueBox->y2 + 2);
        }
        gDPPipeSync((*dlist)++);
        gDPSetEnvColor((*dlist)++, dialogueBox->backgroundColourR, dialogueBox->backgroundColourG,
                       dialogueBox->backgroundColourB, dialogueBox->backgroundColourA);
        // Loops through sDialogueBoxDimensions, rendering fillrects until it forms a rounded rectangle.
        // The array determines the width and height of each entry before drawing it.
        for (i = 0; sDialogueBoxDimensions[i] >= 0; i += 5) {
            x1 = sDialogueBoxDimensions[i] + dialogueBox->x1;
            y1 = (sDialogueBoxDimensions[i + 1]) ? sDialogueBoxDimensions[i + 2] + dialogueBox->y2
                                                 : sDialogueBoxDimensions[i + 2] + dialogueBox->y1;
            x2 = dialogueBox->x2 - sDialogueBoxDimensions[i];
            y2 = (sDialogueBoxDimensions[i + 3]) ? sDialogueBoxDimensions[i + 4] + dialogueBox->y2
                                                 : sDialogueBoxDimensions[i + 4] + dialogueBox->y1;
            render_fill_rectangle(dlist, x1, y1, x2, y2);
        }
        gDPPipeSync((*dlist)++);
    }
    if (mat != NULL && verts != NULL) {
        if (!sDialogueBoxIsOpen) {
            dialogue_open_stub();
            sDialogueBoxIsOpen = TRUE;
        }
        sDialogueBoxCloseTimer = 2;
        func_8009E9B0(dialogueBox, dlist, mat, verts);
    }
    // Set and render the text portions of the dialogue box.
    dialogueTextBox = dialogueBox->textBox;
    while (dialogueTextBox != NULL) {
        dialogueBox->xpos = dialogueTextBox->x1 + dialogueTextBox->x2;
        dialogueBox->ypos = dialogueTextBox->y1 + dialogueTextBox->y2;
        dialogueBox->textColourR = dialogueTextBox->textColourR;
        dialogueBox->textColourG = dialogueTextBox->textColourG;
        dialogueBox->textColourB = dialogueTextBox->textColourB;
        dialogueBox->textColourA = dialogueTextBox->textColourA;
        dialogueBox->textBGColourR = dialogueTextBox->textBGColourR;
        dialogueBox->textBGColourG = dialogueTextBox->textBGColourG;
        dialogueBox->textBGColourB = dialogueTextBox->textBGColourB;
        dialogueBox->textBGColourA = dialogueTextBox->textBGColourA;
        dialogueBox->opacity = dialogueTextBox->opacity;
        dialogueBox->font = dialogueTextBox->font;
        parse_string_with_number(dialogueTextBox->text, text, dialogueTextBox->textNum);
        func_800C45A4(dlist, dialogueBox, text, 0, 1.0f);
        dialogueTextBox = dialogueTextBox->nextBox;
    }
}

/**
 * Takes in a string and a number, and replaces each instance of the
 * character '~' with the number.
 */
void parse_string_with_number(char *input, char *output, s32 number) {
    while (*input != '\0') {
        if ('~' == *input) { // ~ is equivalent to a %d.
            // output the number as part of the string
            s32_to_string(&output, number);
            input++;
        } else {
            *output = (signed char) *input; // It's either this cast, or change the function signature
            input++;
            output++;
        }
    }
    *output = '\0'; // null terminator
}
