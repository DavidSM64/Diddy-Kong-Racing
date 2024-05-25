/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C3C00 */

#include "font.h"
#include "menu.h"
#include "textures_sprites.h"
#include "camera.h"

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

#define INWARDS 0
#define OUTWARDS 1

// clang-format off
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
// clang-format on

#undef INWARDS
#undef OUTWARDS

OSDevMgr __osPiDevMgr = {
    0, NULL, NULL, NULL, NULL, NULL, NULL,
};

/*******************************/

/************ .bss ************/

s32 gNumberOfFonts;
FontData *gFonts;                              // Official Name: Font
DialogueBoxBackground *gDialogueBoxBackground; // Official Name: Window
DialogueTextElement *gDialogueText;            // Official Name: String
s32 gCompactKerning; // Official Name: squash - Boolean value, seems to be related to X placement of menus on the X
                     // Axis?
s8 sDialogueBoxCloseTimer;

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
        gFonts[i].loadedFonts[0] = 0;
    }

    gDialogueBoxBackground = (DialogueBoxBackground *) allocate_from_main_pool_safe(
        DIALOGUEBOXBACKGROUND_TOTAL_SIZE + DialogueTextElement_TOTAL_SIZE, COLOUR_TAG_YELLOW);
    gDialogueText = (DialogueTextElement *) &gDialogueBoxBackground[DIALOGUEBOXBACKGROUND_COUNT];

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
        gDialogueBoxBackground[i].flags = (i != 0) ? DIALOGUE_BOX_VERTS : 0;
        gDialogueBoxBackground[i].textOffsetX = 0;
        gDialogueBoxBackground[i].textOffsetY = 0;
        gDialogueBoxBackground[i].textBox = 0;
    }
    for (i = 0; i < DIALOGUETEXTELEMENT_COUNT; i++) {
        gDialogueText[i].number = 255;
        gDialogueText[i].text = NULL;
        gDialogueText[i].textColourR = 255;
        gDialogueText[i].textColourG = 255;
        gDialogueText[i].textColourB = 255;
        gDialogueText[i].textColourA = 0;
        gDialogueText[i].textBGColourR = 255;
        gDialogueText[i].textBGColourG = 255;
        gDialogueText[i].textBGColourB = 255;
        gDialogueText[i].textBGColourA = 0;
        gDialogueText[i].nextBox = NULL;
    }
    load_font(ASSET_FONTS_FUNFONT);
    load_font(ASSET_FONTS_SMALLFONT);
    gCompactKerning = FALSE;
}

/**
 * Sets text kerning to true or false.
 * If false, text displayed will be monospaced.
 */
void set_kerning(s32 setting) {
    gCompactKerning = setting;
}

/**
 * Load the texture assets of the given font into RAM.
 * This is required before any text using this font can be displayed in a scene.
 */
void load_font(s32 fontID) {
    if (fontID < gNumberOfFonts) {
        FontData *fontData = &gFonts[fontID];
        fontData->loadedFonts[0]++;
        if (fontData->loadedFonts[0] == 1) {
            s32 i = 0;
            while (i < 32 && fontData->textureID[i] != -1) {
                fontData->texturePointers[i] = load_texture(fontData->textureID[i]);
                i++;
            }
        }
    }
}

/**
 * Free a font's assets from RAM.
 * Highly recommended to do for any existing font when unloading a scene to prevent leaks.
 */
void unload_font(s32 fontID) {
    if (fontID < gNumberOfFonts) {
        FontData *fontData = &gFonts[fontID];
        if (fontData->loadedFonts[0] > 0) {
            fontData->loadedFonts[0]--;
            if (fontData->loadedFonts[0] == 0) {
                s32 i = 0;
                while (i < 32 && fontData->textureID[i] != -1) {
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

/**
 * Returns the address of the loaded font ID if it exists.
 * Goes unused.
 */
UNUSED TextureHeader *get_loaded_font(s32 font, u8 index) {
    FontData *fontData;
    u8 pointerIndex;

    if (font < gNumberOfFonts) {
        fontData = &gFonts[font];
        if (fontData->loadedFonts[0] != 0) {
            index -= 32;
            pointerIndex = fontData->letter[index].textureID;
            if (pointerIndex != 0xFF) {
                return fontData->texturePointers[pointerIndex];
            }
            return NULL;
        }
    }
    //!@bug: No return statement. The function will return whatever happens to be in v0 before this function was called.
#ifdef AVOID_UB
    return NULL;
#endif
}

/**
 * Sets the colour of the current dialogue box's text.
 * Official Name: fontColour
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
 * Official Name: fontBackground
 */
void set_text_background_colour(s32 red, s32 green, s32 blue, s32 alpha) {
    gDialogueBoxBackground[0].textBGColourR = red;
    gDialogueBoxBackground[0].textBGColourG = green;
    gDialogueBoxBackground[0].textBGColourB = blue;
    gDialogueBoxBackground[0].textBGColourA = alpha;
}

/**
 * Unused text draw function that just calls the function without any modifications.
 */
UNUSED void draw_text_plain_unused(Gfx **displayList, char *text, AlignmentFlags alignmentFlags) {
    render_text_string(displayList, &gDialogueBoxBackground[0], text, alignmentFlags, 1.0f);
}

/**
 * Builds the background settings, then renders the given text at a given position.
 * Official Name: fontPrintWindowXY?
 */
void draw_text(Gfx **displayList, s32 xpos, s32 ypos, char *text, AlignmentFlags alignmentFlags) {
    DialogueBoxBackground *temp = &gDialogueBoxBackground[0];
    temp->xpos = (xpos == POS_CENTRED) ? temp->width >> 1 : xpos;
    temp->ypos = (ypos == POS_CENTRED) ? temp->height >> 1 : ypos;
    render_text_string(displayList, temp, text, alignmentFlags, 1.0f);
}

/**
 * Unused text draw function that would draw text in the current dialogue box.
 */
UNUSED void draw_dialogue_text_unused(Gfx **displayList, s32 dialogueBoxID, char *text, AlignmentFlags alignmentFlags) {
    if (dialogueBoxID >= 0 && dialogueBoxID < DIALOGUEBOXBACKGROUND_COUNT) {
        DialogueBoxBackground *temp = &gDialogueBoxBackground[dialogueBoxID];
        render_text_string(displayList, temp, text, alignmentFlags, 1.0f);
    }
}

/**
 * Unused text draw function that would draw text in the current dialogue box while overriding position.
 * Official Name: fontPrintWindowXY
 */
UNUSED void draw_dialogue_text_pos_unused(Gfx **displayList, s32 dialogueBoxID, s32 xpos, s32 ypos, char *text,
                                          AlignmentFlags alignmentFlags) {
    if (dialogueBoxID >= 0 && dialogueBoxID < DIALOGUEBOXBACKGROUND_COUNT) {
        DialogueBoxBackground *temp = &gDialogueBoxBackground[dialogueBoxID];
        temp->xpos = (xpos == POS_CENTRED) ? temp->width >> 1 : xpos;
        temp->ypos = (ypos == POS_CENTRED) ? temp->height >> 1 : ypos;
        render_text_string(displayList, temp, text, alignmentFlags, 1.0f);
    }
}

/**
 * Loops through a string, then draws each character onscreen.
 * Will also draw a fillrect if text backgrounds are enabled.
 */
void render_text_string(Gfx **dList, DialogueBoxBackground *box, char *text, AlignmentFlags alignmentFlags,
                        f32 scisScale) {
    s32 scisOffset;
    s32 scisPos;
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
    s32 charSpace;
    s32 newData;
    s32 textureIndex;
    FontData *fontData;
    s32 newTempX;
    s32 newTempY;
    u8 curChar;
    xAlignmentDiff = -1;
    lastTextureIndex = -1;
    if (text != NULL) {
        textureLry = 0;
        xpos = box->xpos;
        ypos = box->ypos;
        fontData = &gFonts[box->font];
        gSPDisplayList((*dList)++, dDialogueBoxBegin);
        if (box != gDialogueBoxBackground) {
            scisOffset = (((box->y2 - box->y1) + 1) / (f32) 2) * scisScale;
            scisPos = (box->y1 + box->y2) >> 1;
            gDPSetScissor((*dList)++, 0, box->x1, scisPos - scisOffset, box->x2, scisPos + scisOffset);
        }
        if (alignmentFlags & (HORZ_ALIGN_RIGHT | HORZ_ALIGN_CENTER)) {
            xAlignmentDiff = get_text_width(text, xpos, box->font);
            if (alignmentFlags & HORZ_ALIGN_RIGHT) {
                xpos = (xpos - xAlignmentDiff) + 1;
            } else {
                xpos -= xAlignmentDiff >> 1;
            }
        }
        if (alignmentFlags & VERT_ALIGN_BOTTOM) {
            ypos = (ypos - fontData->y) + 1;
        }
        if (alignmentFlags & VERT_ALIGN_MIDDLE) {
            ypos -= fontData->y >> 1;
        }
        if (box->textBGColourA != 0) {
            gDPSetEnvColor((*dList)++, box->textBGColourR, box->textBGColourG, box->textBGColourB, box->textBGColourA);
            if (xAlignmentDiff == -1) {
                xAlignmentDiff = get_text_width(text, xpos, box->font);
            }
            newTempX = xpos + xAlignmentDiff - 1;
            newTempY = ypos + fontData->y - 1;
            gDkrDmaDisplayList((*dList)++, OS_K0_TO_PHYSICAL(dDialogueBoxDrawModes[1]), 2);
            gDPFillRectangle((*dList)++, xpos + box->x1, ypos + box->y1, newTempX + box->x1, newTempY + box->y1);
            gDPPipeSync((*dList)++);
        }
        gDPSetPrimColor((*dList)++, textureLry, 0, 255, 255, 255, box->opacity);
        gDPSetEnvColor((*dList)++, box->textColourR, box->textColourG, box->textColourB, box->textColourA);
        gDkrDmaDisplayList((*dList)++, OS_K0_TO_PHYSICAL(dDialogueBoxDrawModes[0]), 2);
        gDPPipeSync((*dList)++);
        xpos += box->textOffsetX;
        ypos += box->textOffsetY;
        for (charIndex = 0; (text[charIndex] != '\0') && (box->y2 >= ypos); xpos += charSpace, charIndex++) {
            curChar = text[charIndex];
            newData = FALSE;
            charSpace = 0;
            if (curChar <= 0x20 || curChar >= 0x80) {
                switch (curChar) {
                    case ' ': // Space
                        xpos += fontData->charWidth;
                        break;
                    case '\n': // Line Feed
                        xpos = box->textOffsetX;
                        ypos += fontData->y;
                        break;
                    case '\t': // Tab
                        xpos += fontData->charHeight - ((xpos - box->textOffsetX) % fontData->charHeight);
                        break;
                    case '\v': // VT - Vertical Tab
                        ypos += fontData->y;
                        break;
                    case '\r': // Carriage Return
                        xpos = box->textOffsetX;
                        break;
                    default:
                        xpos += fontData->charWidth;
                        break;
                }
            } else {
                curChar -= 0x20; // Convert lower case to upper case ASCII
                textureIndex = fontData->letter[curChar].textureID;
                if (textureIndex != 0xFF) {
                    newData = TRUE;
                    if (lastTextureIndex != textureIndex) {
                        lastTextureIndex = textureIndex;
                        texture = fontData->texturePointers[textureIndex];
                        gDkrDmaDisplayList((*dList)++, OS_PHYSICAL_TO_K0(texture->cmd), texture->numberOfCommands);
                    }
                    textureWidth = fontData->letter[curChar].width;
                    textureHeight = fontData->letter[curChar].height;
                    textureS = fontData->letter[curChar].s;
                    textureT = fontData->letter[curChar].t;
                    xAlignmentDiff = fontData->letter[curChar].lrx;
                    yAlignmentDiff = fontData->letter[curChar].lry;
                    charSpace = (fontData->x == 0) ? (fontData->letter[curChar].ulx) : (fontData->x);
                    newData = TRUE;
                }
            }
            if (newData) {
                textureUlx = ((box->x1 + xpos) + textureWidth) * 4;
                textureUly = ((box->y1 + ypos) + textureHeight) * 4;
                textureLrx = (xAlignmentDiff * 4) + textureUlx;
                newTempY = (yAlignmentDiff * 4) + textureUly;
                textureS *= 32;
                textureT *= 32;
                if ((textureUlx < 0) && (textureLrx > 0)) {
                    textureS += (-textureUlx) * 8;
                    textureUlx = 0;
                }
                if ((textureUly <= (0 - 1)) && (newTempY > 0)) {
                    textureT += -textureUly * 8;
                    textureUly = 0;
                }
                gSPTextureRectangle((*dList)++, textureUlx, textureUly, textureLrx, newTempY, 0, textureS, textureT,
                                    1 << 10, 1 << 10);
                if (lastTextureIndex) {} // Fakematch
            }
            if (gCompactKerning && charSpace) {
                charSpace--;
            }
        }

        box->xpos = xpos - box->textOffsetX;
        box->ypos = ypos - box->textOffsetY;
        gDPPipeSync((*dList)++);
        if (box != gDialogueBoxBackground) {
            viewport_scissor(dList);
        }
        reset_render_settings(dList);
        gDPPipeSync((*dList)++);
    }
}

/**
 * Start from the beginning of the line then add to an offset from the starting position.
 * Returns the width of the string.
 * Official Name: fontStringWidth
 */
s32 get_text_width(char *text, s32 x, s32 font) {
    s32 diffX, thisDiffX;
    FontData *fontData;
    s32 index;
    u8 ch;

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
        if (ch <= 0x20 || ch >= 0x80) {
            if (ch == '\t') { // Tab character
                diffX += fontData->charHeight - (diffX % fontData->charHeight);
            } else {
                diffX += fontData->charWidth;
            }
        } else {
            ch -= 0x20; // Convert lower case to upper case ASCII

            if (fontData->letter[ch].textureID != 0xFF) {
                if (fontData->x == 0) {
                    diffX += fontData->letter[ch].ulx;
                } else {
                    diffX += fontData->x;
                }
            }
        }
        if (gCompactKerning && diffX != thisDiffX) {
            diffX--;
        }
    }
    return diffX - x;
}

/**
 * Sets the position and size of the current dialogue box.
 * Official Name: fontWindowSize
 */
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

/**
 * Sets the active front of the current dialogue box.
 * Official Name: fontWindowUseFont
 */
void set_dialogue_font(s32 dialogueBoxID, s32 font) {
    if (dialogueBoxID >= 0 && dialogueBoxID < DIALOGUEBOXBACKGROUND_COUNT) {
        DialogueBoxBackground *temp = &gDialogueBoxBackground[dialogueBoxID];
        if (font < gNumberOfFonts) {
            temp->font = font;
        }
    }
}

/**
 * Sets the background colour of the current dialogue box.
 * Official Name: fontWindowColour
 */
void set_current_dialogue_background_colour(s32 dialogueBoxID, s32 red, s32 green, s32 blue, s32 alpha) {
    if (dialogueBoxID > 0 && dialogueBoxID < DIALOGUEBOXBACKGROUND_COUNT) {
        DialogueBoxBackground *temp = &gDialogueBoxBackground[dialogueBoxID];
        temp->backgroundColourR = red;
        temp->backgroundColourG = green;
        temp->backgroundColourB = blue;
        temp->backgroundColourA = alpha;
    }
}

/**
 * Sets the text colour of the current dialogue box.
 * Official Name: fontWindowFontColour
 */
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

/**
 * Sets text background colour of the current dialogue box.
 * Official Name: fontWindowFontBackground
 */
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

/**
 * Sets the positional text offset of the current dialogue box.
 * Goes unused.
 */
UNUSED void set_current_text_offset(s32 dialogueBoxID, s32 x, s32 y) {
    DialogueBoxBackground *dialogueBox;
    if (dialogueBoxID <= 0 || dialogueBoxID >= DIALOGUEBOXBACKGROUND_COUNT) {
        return;
    }
    dialogueBox = &gDialogueBoxBackground[dialogueBoxID];
    dialogueBox->textOffsetX += x;
    dialogueBox->textOffsetY += y;
}

/**
 * Resets the positional text offset of the current dialogue box.
 * Goes unused.
 */
UNUSED void reset_current_text_offset(s32 dialogueBoxID) {
    DialogueBoxBackground *dialogueBox;
    if (dialogueBoxID <= 0 || dialogueBoxID >= DIALOGUEBOXBACKGROUND_COUNT) {
        return;
    }
    dialogueBox = &gDialogueBoxBackground[dialogueBoxID];
    dialogueBox->textOffsetX = 0;
    dialogueBox->textOffsetY = 0;
}

/**
 * Calls the basic dialogue text draw function passing through the global dialogue box ID.
 * Goes unused.
 */
UNUSED void func_800C510C(s32 dialogueBoxID, char *text, s32 number, s32 flags) {
    render_dialogue_text(dialogueBoxID, gDialogueBoxBackground[dialogueBoxID].xpos,
                         gDialogueBoxBackground[dialogueBoxID].ypos, text, number, flags);
}

/**
 * Draws the text portion of a dialogue box that's passed through.
 * Binds the text to the box, then returns it.
 * Official Name: fontWindowAddStringXY
 */
void *render_dialogue_text(s32 dialogueBoxID, s32 posX, s32 posY, char *text, s32 number, s32 flags) {
    s32 width;
    UNUSED s32 var_a0;
    char buffer[256];
    DialogueTextElement *ret;
    DialogueBox *textBox;
    s32 i;
    DialogueBoxBackground *bg;
    FontData *fontData;
    DialogueBox **textBoxPtr;

    if (text == NULL) {
        return NULL;
    }

    for (i = 0, ret = NULL; i < 64 && ret == NULL; i++) {
        if (gDialogueText[i].number == 255) {
            ret = &gDialogueText[i];
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
            if (flags & (HORZ_ALIGN_CENTER | HORZ_ALIGN_RIGHT)) {
                parse_string_with_number(text, buffer, number);
                width = get_text_width(buffer, posX, bg->font);
                if (flags & HORZ_ALIGN_RIGHT) {
                    posX = (posX - width) + 1;
                } else {
                    posX = posX - (width >> 1);
                }
            }
            if (flags & VERT_ALIGN_BOTTOM) {
                posY = (posY - fontData->y) + 1;
            }
            if (flags & VERT_ALIGN_MIDDLE) {
                posY -= fontData->y >> 1;
            }
        }
        if (bg->textBox == NULL) {
            bg->textBox = (DialogueBox *) ret;
            ret->nextBox = NULL;
        } else {
            textBoxPtr = &bg->textBox;
            textBox = *textBoxPtr;
            while (textBox != NULL && number < textBox->textNum) {
                textBoxPtr = &textBox->nextBox;
                textBox = textBox->nextBox;
            }
            *textBoxPtr = (DialogueBox *) ret;
            ret->nextBox = textBox;
        }
        ret->number = number;
        ret->text = text;
        ret->posX = posX;
        ret->posY = posY;
        ret->offsetX = 0;
        ret->offsetY = 0;
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
 * Clear all strings from this dialogue box ID.
 * Official Name: fontWindowFlushStrings
 */
void dialogue_clear(s32 dialogueBoxID) {
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

/**
 * Unused function that set the offset of the text in the current dialogue box based on alignment flags.
 * Goes unused, as does the whole text offset system.
 */
UNUSED void align_text_in_box(s32 dialogueBoxID, DialogueTextElement *box, s32 x, s32 y, s32 flags) {
    FontData *fontData;
    DialogueBoxBackground *dialogueBox;

    dialogueBox = &gDialogueBoxBackground[dialogueBoxID];

    if (box != NULL) {
        if (box->font != FONT_UNK_FF) {
            fontData = &gFonts[box->font];
            if (flags != ALIGN_TOP_CENTER) {
                switch (flags) {
                    case ALIGN_TOP_RIGHT:
                        y *= fontData->y;
                        break;
                    case ALIGN_BOTTOM_LEFT:
                        y *= (dialogueBox->height / fontData->y) * fontData->y;
                        break;
                }
                box->offsetX += x;
                box->offsetY += y;
                return;
            }
            box->offsetX = 0;
            box->offsetY = 0;
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
 * Official Name: fontWindowDisable
 */
void dialogue_close(s32 dialogueBoxID) {
    gDialogueBoxBackground[dialogueBoxID].flags &= DIALOGUE_BOX_CLOSED;
}

/**
 * Mark the selected dialogue box as an unknown value
 */
UNUSED void set_dialogue_box_unused_flag(s32 dialogueBoxID) {
    gDialogueBoxBackground[dialogueBoxID].flags |= DIALOGUE_BOX_UNUSED_01;
}

/**
 * Clear DIALOGUE_BOX_UNUSED_01 from the dialogue box.
 */
UNUSED void dialogue_box_clear_unused_flag(s32 dialogueBoxID) {
    gDialogueBoxBackground[dialogueBoxID].flags &= (0xFFFF & ~DIALOGUE_BOX_UNUSED_01);
}

/**
 * Mark the selected dialogue box as using triangles to draw.
 */
UNUSED void enable_dialogue_box_vertices(s32 dialogueBoxID) {
    gDialogueBoxBackground[dialogueBoxID].flags |= DIALOGUE_BOX_VERTS;
}

/**
 * Clears the open flag from the dialogue box.
 */
void clear_dialogue_box_open_flag(s32 dialogueBoxID) {
    gDialogueBoxBackground[dialogueBoxID].flags &= (DIALOGUE_BOX_VERTS + DIALOGUE_BOX_CLOSED);
}

/**
 * Main function to render each dialogue box entry.
 * Contains a timer that counts down two frames before closing a dialogue box
 * when the player exits out of one.
 * Official Name: fontWindowsDraw
 */
void render_dialogue_boxes(Gfx **dlist, MatrixS **mat, Vertex **verts) {
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
            if (gDialogueBoxBackground[i].flags & DIALOGUE_BOX_VERTS) {
                render_dialogue_box(dlist, mat, verts, i);
            } else {
                render_dialogue_box(dlist, NULL, NULL, i);
            }
        }
    }
}

/**
 * Convert an integer to a string.
 * Official Name: fontStringAddNumber
 */
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
 * Official Name: fontWindowDraw
 */
void render_dialogue_box(Gfx **dlist, MatrixS **mat, Vertex **verts, s32 dialogueBoxID) {
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
        if (dialogueBox->x2 - dialogueBox->x1 < 10 || dialogueBox->y2 - dialogueBox->y1 < 10) {
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
        if (sDialogueBoxIsOpen == FALSE) {
            dialogue_open_stub();
            sDialogueBoxIsOpen = TRUE;
        }
        sDialogueBoxCloseTimer = 2;
        dialogue_ortho(dialogueBox, dlist, mat, verts);
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
        render_text_string(dlist, dialogueBox, text, 0, 1.0f);
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
