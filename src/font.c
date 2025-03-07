/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C3C00 */

#include "font.h"
#include "menu.h"
#include "textures_sprites.h"
#include "camera.h"
#include "common.h"

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
#if REGION == REGION_JP
    {
        gsDPSetCombineMode(DKR_CC_UNK13, G_CC_PASS2),
        gsDPSetOtherMode(DKR_OMH_2CYC_POINT_NOPERSP, DKR_OML_COMMON | G_RM_NOOP | G_RM_XLU_SURF2),
    },
#endif
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
s8 sDialogueBoxDimensions[] = {
    /*X Offset*/ 4,  INWARDS,  /*Y Start*/  0,  INWARDS,  /*Y end*/  1,
    /*X Offset*/ 2,  INWARDS,  /*Y Start*/  1,  INWARDS,  /*Y end*/  2,
    /*X Offset*/ 1,  INWARDS,  /*Y Start*/  2,  INWARDS,  /*Y end*/  4,
    /*X Offset*/ 0,  INWARDS,  /*Y Start*/  4,  OUTWARDS, /*Y end*/ -4,
    /*X Offset*/ 1,  OUTWARDS, /*Y Start*/ -4,  OUTWARDS, /*Y end*/ -2,
    /*X Offset*/ 2,  OUTWARDS, /*Y Start*/ -2,  OUTWARDS, /*Y end*/ -1,
    /*X Offset*/ 4,  OUTWARDS, /*Y Start*/ -1,  OUTWARDS,  0,
    /*X Offset*/ -1, // End of Data
};
// clang-format on

#undef INWARDS
#undef OUTWARDS

/*******************************/

/************ .bss ************/

s32 gNumberOfFonts;
FontData *gFonts;                              // Official Name: Font
DialogueBoxBackground *gDialogueBoxBackground; // Official Name: Window
DialogueTextElement *gDialogueText;            // Official Name: String
s32 gCompactKerning; // Official Name: squash - Boolean value, seems to be related to X placement of menus on the X
                     // Axis?

#if REGION == REGION_JP
#define JP_FONT_ARRAY_SIZE 256
#define NUMBER_OF_JP_FONTS 4

// Header for a single japanese character. 0x10 bytes
typedef struct JpCharHeader {
    char *ptr;
    char *unk4;
    u8 pad8[2];
    u8 left;
    u8 top;
    u8 right;
    u8 bottom;
    u8 spacing;
} JpCharHeader;

// Japanese Font Header, 0x10 bytes
// Asset45 contains 4 font headers.
typedef struct FontData_JP {
    u8 unk0;
    u8 x;
    u8 y;
    u8 charWidth;
    u8 height;
    u8 pad[3];
    s32 offsetToData;
    s32 bytesPerCharacter;
} FontData_JP;

typedef struct FontJpSpacing {
    u8 spacing[256]; // 256 characters in the japanese font
} FontJpSpacing;

typedef struct Unk8012C2D4_JP {
    char unk0;
    char unk1;
    u16 unk2;
    Gfx *dlist;
} Unk8012C2D4_JP;

FontData_JP *D_8012C2A4_EE5E4;
FontJpSpacing *D_8012C2A8_EE5E8[4]; // 4 tables for spacing in different fonts?
s32 D_8012C2B8_EE5F8;
Unk8012C2D4_JP (*D_8012C2BC_EE5FC)[128];
JpCharHeader (*D_8012C2C0_EE600)[18];
Gfx *D_8012C2C4_EE604;
Unk8012C2D4_JP *D_8012C2C8_EE608;
JpCharHeader (*D_8012C2CC_EE60C)[18];
Gfx *D_8012C2D0_EE610;
Unk8012C2D4_JP *D_8012C2D4_EE614;
Unk8012C2D4_JP *D_8012C2D8_EE618;
#endif

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

    gDialogueBoxBackground = (DialogueBoxBackground *) mempool_alloc_safe(
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
#if REGION == REGION_JP
    func_800C6464_C7064();
#else
    load_font(ASSET_FONTS_FUNFONT);
    load_font(ASSET_FONTS_SMALLFONT);
#endif
    gCompactKerning = FALSE;
}

/**
 * Sets text kerning to true or false.
 * If false, text displayed will be monospaced.
 */
void set_kerning(s32 setting) {
    gCompactKerning = setting;
}

#if REGION != REGION_JP
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
#endif

/**
 * Set the font of the current dialogue box's text.
 */
void set_text_font(s32 fontID) {
#if REGION == REGION_JP
    gDialogueBoxBackground[0].font = D_8012C2B8_EE5F8 = fontID;
#else
    if (fontID < gNumberOfFonts) {
        gDialogueBoxBackground[0].font = fontID;
    }
#endif
}

/**
 * Returns the address of the loaded font ID if it exists.
 * Goes unused.
 */
UNUSED TextureHeader *get_loaded_font(s32 font, u8 index) {
#if REGION == REGION_JP
    return NULL;
#else
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
#if REGION != REGION_JP
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
#else
void render_text_string(Gfx **dList, DialogueBoxBackground *box, char *text, enum AlignmentFlags alignmentFlags,
                        f32 scisScale) {
    s32 jpTexS;
    s32 prevFont;
    s32 jpTexT;
    s32 xpos;
    s32 ulx;
    s32 uly;
    s32 lrx;
    s32 lry;
    s32 ypos;
    s32 scisOffset;
    s32 charSpace;
    s32 scisPos;
    s32 textureS;
    s32 textureT;
    s32 textureS2;
    s32 textureT2;
    s32 xAlignmentDiff;
    s32 someIndexForJpChar;
    u16 jpCharValue;
    s32 textureLrx;
    s32 textureLry;
    u8 curChar;
    FontData_JP *fontData;
    s32 newTempX;
    s32 newTempY;
    s32 charIndex;
    s32 temp;
    char otherText[220]; // Not sure about the length of this buffer.
    s32 temp2;

    xAlignmentDiff = -1;
    if (text == NULL) {
        return;
    }

    func_800C7864_C8464(text, otherText);
    prevFont = D_8012C2B8_EE5F8;
    D_8012C2B8_EE5F8 = box->font;
    xpos = box->xpos;
    ypos = box->ypos;

    fontData = (FontData_JP *) &D_8012C2A4_EE5E4[D_8012C2B8_EE5F8];
    gSPDisplayList((*dList)++, dDialogueBoxBegin);
    if (box != gDialogueBoxBackground) {
        scisOffset = (((box->y2 - box->y1) + 1) / (f32) 2) * scisScale;
        scisPos = (box->y1 + box->y2) >> 1;
        ulx = box->x1;
        lrx = box->x2;
        // Pretty sure these are macros.
        if (ulx < 0) {
            ulx = 0;
        }
        if (ulx >= 320) {
            ulx = 319;
        }
        if (lrx < 0) {
            lrx = 0;
        }
        if (lrx >= 320) {
            lrx = 319;
        }
        uly = scisPos - scisOffset;
        lry = scisPos + scisOffset;
        if (uly < 0) {
            uly = 0;
        }
        if (uly >= 240) {
            uly = 239;
        }
        if (lry < 0) {
            lry = 0;
        }
        if (lry >= 240) {
            lry = 239;
        }
        gDPSetScissor((*dList)++, 0, ulx, uly, lrx, lry);
    }
    if (alignmentFlags & (HORZ_ALIGN_RIGHT | HORZ_ALIGN_CENTER)) {
        xAlignmentDiff = get_text_width(otherText, xpos, box->font);
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
            xAlignmentDiff = get_text_width(otherText, xpos, box->font);
        }
        lrx = xpos + xAlignmentDiff;
        lry = fontData->y + ypos;
        gDkrDmaDisplayList((*dList)++, OS_K0_TO_PHYSICAL(dDialogueBoxDrawModes[1]), 2);
        gDPFillRectangle((*dList)++, xpos + box->x1, ypos + box->y1, lrx + box->x1, lry + box->y1);
        gDPPipeSync((*dList)++);
    }
    gDPSetPrimColor((*dList)++, 0, 0, 255, 255, 255, box->opacity);
    gDPSetEnvColor((*dList)++, box->textColourR, box->textColourG, box->textColourB, box->textColourA);
    gDkrDmaDisplayList((*dList)++, OS_K0_TO_PHYSICAL(dDialogueBoxDrawModes[0]), 2);
    gDPPipeSync((*dList)++);

    xpos += box->textOffsetX;
    ypos += box->textOffsetY;
    charIndex = 0;
    while ((otherText[charIndex] != '\0') && (box->y2 >= ypos)) {
        curChar = otherText[charIndex++];
        jpCharValue = 0;
        if (curChar & 0x80) { // Test if this is a japanese character text.
            // So this text system supports up to 32768 unique characters, although the game only uses 256.
            jpCharValue = (otherText[charIndex++] | ((curChar & 0x7F) << 8));
            if (jpCharValue == 15) { // Index 15 is the space character.
                jpCharValue = 0;
                curChar = ' ';
            }
        }
        if (jpCharValue != 0) {
            // Texture coordinates of the 256x256 japanese font texture.
            ulx = box->x1 + xpos;
            uly = box->y1 + ypos;
            lrx = ulx + fontData->x;
            lry = uly + fontData->y;
            charSpace = D_8012C2A8_EE5E8[D_8012C2B8_EE5F8]->spacing[jpCharValue];
            if ((lrx > 0) && (lry > 0) && (ulx < box->x2) && (uly < box->y2)) {
                someIndexForJpChar =
                    func_800C7744_C8344(dList, jpCharValue, &textureS, &textureT, &textureS2, &textureT2);
            } else {
                someIndexForJpChar = -1;
            }
            if (someIndexForJpChar >= 0) {
                ulx = ulx << 2;
                uly = (uly + textureT) << 2;
                lrx = (textureS2 - textureS) * 4 + ulx;
                lry = (textureT2 - textureT) * 4 + uly;
                if ((lrx > 0) && (lry > 0)) {
                    textureS <<= 5;
                    textureT <<= 5;
                    if (ulx < 0) {
                        textureS += (ulx * -1) << 3;
                        ulx = 0;
                    }
                    if (uly < 0) {
                        textureT += (uly * -1) << 3;
                        uly = 0;
                    }
                    func_800C7804_C8404(someIndexForJpChar);
                    gSPTextureRectangle((*dList)++, ulx, uly, lrx, lry, 0, textureS, textureT, 1 << 10, 1 << 10);
                }
            }
            if ((gCompactKerning) && (charSpace != 0)) {
                charSpace--;
            }
            xpos += charSpace;
        } else {
            // This was a regular ascii character.
            switch (curChar) {
                case '\n': // newline
                    xpos = box->textOffsetX;
                    ypos += fontData->height;
                    break;
                case '\t': // Tab
                    xpos = ((s32) xpos + (fontData->charWidth * 4)) -
                           ((xpos - box->textOffsetX) % (fontData->charWidth * 4));
                    break;
                case '\v': // VT - Vertical Tab
                    ypos += fontData->height;
                    break;
                case '\r': // Carriage Return
                    xpos = box->textOffsetX;
                    break;
                default:
                    xpos += fontData->charWidth;
                    break;
            }
        }
    }
    box->xpos = xpos - box->textOffsetX;
    box->ypos = ypos - box->textOffsetY;
    D_8012C2B8_EE5F8 = prevFont; // Put previous font index back.
    if (box != gDialogueBoxBackground) {
        viewport_scissor(dList);
    }
    reset_render_settings(dList);
    gDPPipeSync((*dList)++);
}
#endif

/**
 * Start from the beginning of the line then add to an offset from the starting position.
 * Returns the width of the string.
 * Official Name: fontStringWidth
 */
#if REGION != REGION_JP
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
#else
s32 get_text_width(char *text, s32 x, s32 font) {
    FontData_JP *currentFont;
    FontJpSpacing *currentFontSpacing;
    s32 glyphIndex;
    s32 length;

    currentFont = &D_8012C2A4_EE5E4[font];
    currentFontSpacing = D_8012C2A8_EE5E8[font];
    length = 0;
    while (text[0]) {
        if (text[0] & 0x80) {
            glyphIndex = (text[1] & 0xFF) | ((text[0] & 0x7F) << 8);
            text += 2;
            if ((glyphIndex == 0) || (glyphIndex == 15)) {
                length += currentFont->charWidth;
            } else {
                length += currentFontSpacing->spacing[glyphIndex];
            }
        } else {
            text += 1;
            length += currentFont->charWidth;
        }
    }
    return length;
}
#endif

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
#if REGION == REGION_JP
    gDialogueBoxBackground[dialogueBoxID].font = font;
#else
    if (dialogueBoxID >= 0 && dialogueBoxID < DIALOGUEBOXBACKGROUND_COUNT) {
        DialogueBoxBackground *temp = &gDialogueBoxBackground[dialogueBoxID];
        if (font < gNumberOfFonts) {
            temp->font = font;
        }
    }
#endif
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
    u32 widthAndHeight = fb_size();
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
#if REGION != REGION_JP
void parse_string_with_number(char *input, char *output, s32 number) {
    while (*input) {
        if (*input == '~') { // ~ is equivalent to a %d.
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
#else
void parse_string_with_number(char *input, char *output, s32 number) {
    char currentChar;

    currentChar = *input++;
    while (currentChar) {
        if (currentChar & 0x80) {
            char nextChar = *input++;
            if (nextChar == 0xE) {
                s32_to_string(&output, number);
            } else {
                *output++ = currentChar;
                *output++ = nextChar;
            }
        } else if (currentChar == '~') { // ~ is equivalent to a %d.
            s32_to_string(&output, number);
        } else {
            *output++ = currentChar;
        }
        currentChar = *input;
        input++;
    }
    *output = '\0'; // null terminator
}

void func_800C6464_C7064(void) {
    s32 i;
    s32 charIndex;
    u8 **var_s3;
    JpCharHeader *jpFontData;
    FontData_JP *jpFontHeader;

    D_8012C2C4_EE604 = mempool_alloc_safe(0x6C00, COLOUR_TAG_RED);
    D_8012C2C8_EE608 = mempool_alloc_safe(0x400, COLOUR_TAG_RED);
    D_8012C2CC_EE60C = mempool_alloc_safe(0x9000, COLOUR_TAG_RED);
    for (i = 0, charIndex = 0; i < 128; i++) {
        D_8012C2C8_EE608[i].unk0 = 0;
        D_8012C2C8_EE608[i].dlist = &D_8012C2C4_EE604[charIndex];
        if (i & 1) {
            charIndex += 10;
        } else {
            charIndex += 17;
        }
    }

    D_8012C2A4_EE5E4 = (FontData_JP *) load_asset_section_from_rom(ASSET_BINARY_45);

    // Init the 4 pointers in D_8012C2A8_EE5E8 (table for spacing of each character in every font)
    D_8012C2A8_EE5E8[0] = mempool_alloc_safe(NUMBER_OF_JP_FONTS * JP_FONT_ARRAY_SIZE, COLOUR_TAG_RED);
    for (i = 1; i < 4; i++) {
        D_8012C2A8_EE5E8[i] = &D_8012C2A8_EE5E8[0]->spacing[i * JP_FONT_ARRAY_SIZE];
    }

    jpFontData = mempool_alloc_safe(0x40, COLOUR_TAG_RED);
    for (i = 0; i < 4; i++) {
        jpFontHeader = &D_8012C2A4_EE5E4[i];
        for (charIndex = 0; charIndex < JP_FONT_ARRAY_SIZE; charIndex++) {
            load_asset_to_address(ASSET_BINARY_46, (u32) jpFontData,
                                  jpFontHeader->offsetToData + (charIndex * jpFontHeader->bytesPerCharacter), 0x40);
            D_8012C2A8_EE5E8[i]->spacing[charIndex] = jpFontData->spacing;
        }
    }

    mempool_free(jpFontData);
    D_8012C2B8_EE5F8 = 0;
}

void func_800C663C_C723C(void) {
    s32 i;
    s32 var_v0;

    func_800C67F4_C73F4();
    D_8012C2D0_EE610 = mempool_alloc_safe(0x6C00, COLOUR_TAG_RED);
    D_8012C2D4_EE614 = mempool_alloc_safe(0x400, COLOUR_TAG_RED);
    D_8012C2D8_EE618 = mempool_alloc_safe(0x9000, COLOUR_TAG_RED);
    if (D_8012C2D0_EE610 == NULL || D_8012C2D4_EE614 == NULL || D_8012C2D8_EE618 == NULL) {
        func_800C67F4_C73F4();
        return;
    }
    var_v0 = 0;
    for (i = 0; i < 0x80; i++) {
        D_8012C2D4_EE614[i].unk0 = 0;
        D_8012C2D4_EE614[i].dlist = &D_8012C2D0_EE610[var_v0];
        if (i & 1) {
            var_v0 += 10;
        } else {
            var_v0 += 17;
        }
    }
}

void func_800C67F4_C73F4(void) {
    if (D_8012C2D0_EE610 != NULL) {
        mempool_free(D_8012C2D0_EE610);
        D_8012C2D0_EE610 = NULL;
    }
    if (D_8012C2D4_EE614 != NULL) {
        mempool_free(D_8012C2D4_EE614);
        D_8012C2D4_EE614 = NULL;
    }
    if (D_8012C2D8_EE618 != NULL) {
        mempool_free(D_8012C2D8_EE618);
        D_8012C2D8_EE618 = NULL;
    }
}

void func_800C6870_C7470(void) {
    if (D_8012C2C0_EE600 == D_8012C2CC_EE60C && D_8012C2D8_EE618 != NULL) {
        D_8012C2BC_EE5FC = D_8012C2D4_EE614;
        D_8012C2C0_EE600 = D_8012C2D8_EE618;
    } else {
        D_8012C2BC_EE5FC = D_8012C2C8_EE608;
        D_8012C2C0_EE600 = D_8012C2CC_EE60C;
    }
}

s32 func_800C68CC_C74CC(u16 arg0) {
    s32 assetSize;
    s32 i;
    s32 var_t0;
    s32 var_a3;
    s32 curIndex;
    s32 var_v1;
    u16 glyphIndex;
    Unk8012C2D4_JP *asset;

    glyphIndex = ((D_8012C2B8_EE5F8 << 12) | (arg0 & 0xFFF));
    var_a3 = (D_8012C2A4_EE5E4[D_8012C2B8_EE5F8].bytesPerCharacter + 0x11F) / 0x120;
    D_8012C2BC_EE5FC = D_8012C2C8_EE608;
    D_8012C2C0_EE600 = D_8012C2CC_EE60C;
    curIndex = -1;

    do {
        for (i = 0; i + var_a3 <= 128 && curIndex < 0; i += var_a3) {
            if ((*D_8012C2BC_EE5FC)[i].unk0 != 0 && (*D_8012C2BC_EE5FC)[i].unk2 == glyphIndex) {
                curIndex = i;
            }
        }
        if (curIndex < 0) {
            func_800C6870_C7470();
        }
    } while ((D_8012C2C0_EE600 != D_8012C2CC_EE60C) && (curIndex < 0));

    if (curIndex >= 0) {
        return curIndex;
    } else {
        D_8012C2BC_EE5FC = D_8012C2C8_EE608;
        D_8012C2C0_EE600 = D_8012C2CC_EE60C;
        do {
            for (i = 0; i + var_a3 <= 128 && curIndex < 0; i += var_a3) {
                if (((*D_8012C2BC_EE5FC)[i].unk0) == 0) {
                    curIndex = i;
                    for (var_v1 = 1; var_v1 < var_a3; var_v1++) {
                        if ((*D_8012C2BC_EE5FC)[i + var_v1].unk0 != 0) {
                            curIndex = -1;
                        }
                    }
                }
            }
            if (curIndex < 0) {
                func_800C6870_C7470();
            }
        } while ((D_8012C2C0_EE600 != D_8012C2CC_EE60C) && (curIndex < 0));

        if (curIndex >= 0) {
            for (var_v1 = 0; var_v1 < var_a3; var_v1++) {
                (*D_8012C2BC_EE5FC)[curIndex + var_v1].unk1 = var_a3;
                if (var_v1 == 0) {
                    (*D_8012C2BC_EE5FC)[curIndex + var_v1].unk2 = glyphIndex;
                } else {
                    (*D_8012C2BC_EE5FC)[curIndex + var_v1].unk2 = -1;
                }
            }
            asset = &D_8012C2C0_EE600[curIndex];
            load_asset_to_address(ASSET_BINARY_46, (u32) asset,
                                  D_8012C2A4_EE5E4[D_8012C2B8_EE5F8].offsetToData +
                                      (D_8012C2A4_EE5E4[D_8012C2B8_EE5F8].bytesPerCharacter * arg0),
                                  D_8012C2A4_EE5E4[D_8012C2B8_EE5F8].bytesPerCharacter);
            func_800C6DD4_C79D4((*D_8012C2BC_EE5FC)[curIndex].dlist, asset, D_8012C2A4_EE5E4[D_8012C2B8_EE5F8].x,
                                D_8012C2A4_EE5E4[D_8012C2B8_EE5F8].y);
        }

        return curIndex;
    }
}

void func_800C6DD4_C79D4(Gfx *dlist, Asset46 *asset, s32 width, s32 height) {
    if (asset->unk0 != -1) {
        asset->unk0 = (s32) asset + asset->unk0;
    } else {
        asset->unk0 = NULL;
    }
    if (asset->unk4 != -1) {
        asset->unk4 = (s32) asset + asset->unk4;
    } else {
        asset->unk4 = NULL;
    }

    if (asset->unk4 != NULL) {
        gDPLoadTextureBlockS(dlist++, OS_PHYSICAL_TO_K0(asset->unk0), G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height,
                             0,                         // palette
                             G_TX_NOMIRROR | G_TX_WRAP, // cms
                             G_TX_NOMIRROR | G_TX_WRAP, // cmt
                             8,                         // masks
                             8,                         // maskt
                             G_TX_NOLOD,                // shifts
                             G_TX_NOLOD);               // shiftt

        gDPLoadMultiBlock_4bS(dlist++, OS_PHYSICAL_TO_K0(asset->unk4), 0x100, 1, G_IM_FMT_I, width, height,
                              0,                         // palette
                              G_TX_NOMIRROR | G_TX_WRAP, // cms
                              G_TX_NOMIRROR | G_TX_WRAP, // cmt
                              8,                         // masks
                              8,                         // maskt
                              G_TX_NOLOD,                // shifts
                              G_TX_NOLOD);               // shiftt

        gDkrDmaDisplayList(dlist++, OS_K0_TO_PHYSICAL(&dDialogueBoxDrawModes[2]),
                           numberOfGfxCommands(dDialogueBoxDrawModes[1]));
    } else {
        switch (asset->unk8) {
            case 0: // RGBA32
                gDPLoadTextureBlockS(dlist++, OS_PHYSICAL_TO_K0(asset->unk0), G_IM_FMT_RGBA, G_IM_SIZ_32b, width,
                                     height,
                                     0,                         // palette
                                     G_TX_NOMIRROR | G_TX_WRAP, // cms
                                     G_TX_NOMIRROR | G_TX_WRAP, // cmt
                                     8,                         // masks
                                     8,                         // maskt
                                     G_TX_NOLOD,                // shifts
                                     G_TX_NOLOD);               // shiftt
                break;
            case 1: // RGBA16
                gDPLoadTextureBlockS(dlist++, OS_PHYSICAL_TO_K0(asset->unk0), G_IM_FMT_RGBA, G_IM_SIZ_16b, width,
                                     height,
                                     0,                         // palette
                                     G_TX_NOMIRROR | G_TX_WRAP, // cms
                                     G_TX_NOMIRROR | G_TX_WRAP, // cmt
                                     8,                         // masks
                                     8,                         // maskt
                                     G_TX_NOLOD,                // shifts
                                     G_TX_NOLOD);               // shiftt
                break;
            case 5: // IA8
                gDPLoadTextureBlockS(dlist++, OS_PHYSICAL_TO_K0(asset->unk0), G_IM_FMT_IA, G_IM_SIZ_8b, width, height,
                                     0,                         // palette
                                     G_TX_NOMIRROR | G_TX_WRAP, // cms
                                     G_TX_NOMIRROR | G_TX_WRAP, // cmt
                                     8,                         // masks
                                     8,                         // maskt
                                     G_TX_NOLOD,                // shifts
                                     G_TX_NOLOD);               // shiftt
                break;
            case 6: // IA4
                gDPLoadTextureBlock_4bS(dlist++, OS_PHYSICAL_TO_K0(asset->unk0), G_IM_FMT_IA, width, height,
                                        0,                         // palette
                                        G_TX_NOMIRROR | G_TX_WRAP, // cms
                                        G_TX_NOMIRROR | G_TX_WRAP, // cmt
                                        8,                         // masks
                                        8,                         // maskt
                                        G_TX_NOLOD,                // shifts
                                        G_TX_NOLOD);               // shiftt
                break;
            case 3: // I4
                gDPLoadTextureBlock_4bS(dlist++, OS_PHYSICAL_TO_K0(asset->unk0), G_IM_FMT_I, width, height,
                                        0,                         // palette
                                        G_TX_NOMIRROR | G_TX_WRAP, // cms
                                        G_TX_NOMIRROR | G_TX_WRAP, // cmt
                                        8,                         // masks
                                        8,                         // maskt
                                        G_TX_NOLOD,                // shifts
                                        G_TX_NOLOD);               // shiftt
                break;
            case 2: // I8
                gDPLoadTextureBlockS(dlist++, OS_PHYSICAL_TO_K0(asset->unk0), G_IM_FMT_I, G_IM_SIZ_8b, width, height,
                                     0,                         // palette
                                     G_TX_NOMIRROR | G_TX_WRAP, // cms
                                     G_TX_NOMIRROR | G_TX_WRAP, // cmt
                                     8,                         // masks
                                     8,                         // maskt
                                     G_TX_NOLOD,                // shifts
                                     G_TX_NOLOD);               // shiftt
                break;
        }
        gDkrDmaDisplayList(dlist++, OS_K0_TO_PHYSICAL(&dDialogueBoxDrawModes[0]),
                           numberOfGfxCommands(dDialogueBoxDrawModes[1]));
    }
    gSPEndDisplayList(dlist++);
}

s32 func_800C7744_C8344(Gfx **dlist, u16 charIndex, s32 *outLeft, s32 *outTop, s32 *outRight, s32 *outBottom) {
    s32 index;
    JpCharHeader *jpChar;

    index = func_800C68CC_C74CC(charIndex);
    if (index >= 0) {
        gSPDisplayList((*dlist)++, (*D_8012C2BC_EE5FC)[index].dlist);
        jpChar = D_8012C2C0_EE600[index];
        *outLeft = jpChar->left;
        *outTop = jpChar->top;
        *outRight = jpChar->right;
        *outBottom = jpChar->bottom;
    }
    return index;
}

void func_800C7804_C8404(s32 arg0) {
    s32 i;

    for (i = 0; i < (*D_8012C2BC_EE5FC)[arg0].unk1; i++) {
        (*D_8012C2BC_EE5FC)[arg0 + i].unk0 = 2;
    }
}

u8 D_800E5234_E5E34[] = {
    0x0F, 0x34, 0x0A, 0x36, 0x02, 0x06, 0x0D, 0x37, 0x03, 0x04, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x3E, 0x05, 0x0B, 0x3F, 0x0C, 0x40,
    0x41, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
    0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x07, 0x0F, 0x08, 0x0F, 0x0F,
    0x09, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3,
    0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0x03, 0x0F, 0x04, 0x0E, 0x0F,
};

void func_800C7864_C8464(char *inString, char *outString) {
    char currentChar;

    currentChar = *inString++;
    while (currentChar) {
        if (currentChar & 0x80) {
            *outString++ = currentChar;
            *outString++ = *inString++;
        } else if (currentChar < 32) {
            *outString++ = currentChar;
        } else {
            *outString++ = 0x80;
            *outString++ = D_800E5234_E5E34[currentChar - 32];
        }
        currentChar = *inString;
        inString++;
    }
    *outString = '\0';
}

void func_800C78E0_C84E0(void) {
    s32 i;

    D_8012C2BC_EE5FC = D_8012C2C8_EE608;
    D_8012C2C0_EE600 = D_8012C2CC_EE60C;
    do {
        for (i = 0; i < 128; i++) {
            if ((*D_8012C2BC_EE5FC)[i].unk0) {
                (*D_8012C2BC_EE5FC)[i].unk0--;
            }
        }
        func_800C6870_C7470();
    } while (D_8012C2C0_EE600 != D_8012C2CC_EE60C);
}

#endif
