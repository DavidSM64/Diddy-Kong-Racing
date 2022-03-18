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

OSDevMgr __osPiDevMgr = { 0, NULL, NULL, NULL, NULL, NULL, NULL, };

/*******************************/

/************ .bss ************/

s32 gNumberOfFonts;
FontData *gFonts;
DialogueBoxBackground (*gDialogueBoxBackground)[1];
unk8012A7EC (*D_8012A7EC)[1];
s32 D_8012A7F0;
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
        (*gDialogueBoxBackground)[i].font = FONT_UNK_FF;
        if (i != 0) {
            (*gDialogueBoxBackground)[i].flags = DIALOGUE_BOX_UNK_01;
        } else {
            (*gDialogueBoxBackground)[i].flags = 0;
        }
        (*gDialogueBoxBackground)[i].unk20 = 0;
        (*gDialogueBoxBackground)[i].unk22 = 0;
        (*gDialogueBoxBackground)[i].textBox = 0;
    }
    for (i = 0; i < unk8012A7EC_COUNT; i++) {
        (*D_8012A7EC)[i].unk1 = 0xFF;
        (*D_8012A7EC)[i].unk4 = 0;
        (*D_8012A7EC)[i].textColourR = 0xFF;
        (*D_8012A7EC)[i].textColourG = 0xFF;
        (*D_8012A7EC)[i].textColourB = 0xFF;
        (*D_8012A7EC)[i].textColourA = 0;
        (*D_8012A7EC)[i].textBGColourR = 0xFF;
        (*D_8012A7EC)[i].textBGColourG = 0xFF;
        (*D_8012A7EC)[i].textBGColourB = 0xFF;
        (*D_8012A7EC)[i].textBGColourA = 0;
        (*D_8012A7EC)[i].unk1C = 0;
    }
    func_800C4170(0);
    func_800C4170(1);
    D_8012A7F0 = 0;
}

void func_800C4164(s32 arg0) {
    D_8012A7F0 = arg0;
}

#ifdef NON_EQUIVALENT
// Mostly has regalloc issues.
void func_800C4170(s32 fontID) {
    if (fontID < gNumberOfFonts) {
        FontData *fontData = &gFonts[fontID];
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

#ifdef NON_EQUIVALENT
// Mostly has regalloc issues.
void func_800C422C(s32 fontID) {
    if (fontID < gNumberOfFonts) {
        FontData *fontData = &gFonts[fontID];
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

/**
 * Set the font of the current dialogue box's text.
 */
void set_text_font(s32 fontID) {
    if (fontID < gNumberOfFonts) {
        (*gDialogueBoxBackground)[0].font = fontID;
    }
}

#ifdef NON_EQUIVALENT

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

/**
 * Sets the colour of the current dialogue box's text.
 */
void set_text_colour(s32 red, s32 green, s32 blue, s32 alpha, s32 opacity) {
    (*gDialogueBoxBackground)[0].textColourR = red;
    (*gDialogueBoxBackground)[0].textColourG = green;
    (*gDialogueBoxBackground)[0].textColourB = blue;
    (*gDialogueBoxBackground)[0].textColourA = alpha;
    (*gDialogueBoxBackground)[0].opacity = opacity;
}

/**
 * Sets the colour of the current dialogue box's text background.
 */
void set_text_background_colour(s32 red, s32 green, s32 blue, s32 alpha) {
    (*gDialogueBoxBackground)[0].textBGColourR = red;
    (*gDialogueBoxBackground)[0].textBGColourG = green;
    (*gDialogueBoxBackground)[0].textBGColourB = blue;
    (*gDialogueBoxBackground)[0].textBGColourA = alpha;
}

// Unused?
void func_800C4404(Gfx **displayList, char *text, AlignmentFlags alignmentFlags) {
    func_800C45A4(displayList, &(*gDialogueBoxBackground)[0], text, alignmentFlags, 1.0f);
}

/**
 * Builds the background settings, then renders the given text at a given position.
 */
void draw_text(Gfx **displayList, s32 xpos, s32 ypos, char *text, AlignmentFlags alignmentFlags) {
    DialogueBoxBackground *temp = &(*gDialogueBoxBackground)[0];
    temp->xpos = (xpos == POS_CENTRED) ? temp->width >> 1 : xpos;
    temp->ypos = (ypos == POS_CENTRED) ? temp->height >> 1 : ypos;
    func_800C45A4(displayList, temp, text, alignmentFlags, 1.0f);
}

// Unused?
void func_800C44C0(Gfx **displayList, s32 dialogueBoxID, char *text, AlignmentFlags alignmentFlags) {
    if (dialogueBoxID >= 0 && dialogueBoxID < DIALOGUEBOXBACKGROUND_COUNT) {
        DialogueBoxBackground *temp = &gDialogueBoxBackground[dialogueBoxID];
        func_800C45A4(displayList, temp, text, alignmentFlags, 1.0f);
    }
}

// Unused?
void func_800C4510(Gfx **displayList, s32 dialogueBoxID, s32 xpos, s32 ypos, char *text, AlignmentFlags alignmentFlags) {
    if (dialogueBoxID >= 0 && dialogueBoxID < DIALOGUEBOXBACKGROUND_COUNT) {
        DialogueBoxBackground *temp = &gDialogueBoxBackground[dialogueBoxID];
        temp->xpos = (xpos == POS_CENTRED) ? temp->width >> 1 : xpos;
        temp->ypos = (ypos == POS_CENTRED) ? temp->height >> 1 : ypos;
        func_800C45A4(displayList, temp, text, alignmentFlags, 1.0f);
    }
}

GLOBAL_ASM("asm/non_matchings/font/func_800C45A4.s")

// Should be functionally equivalent.
#ifdef NON_EQUIVALENT
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

void set_current_dialogue_box_coords(s32 dialogueBoxID, s32 x1, s32 y1, s32 x2, s32 y2) {
    if (dialogueBoxID > 0 && dialogueBoxID < DIALOGUEBOXBACKGROUND_COUNT) {
        DialogueBoxBackground *temp = &gDialogueBoxBackground[dialogueBoxID];
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

void set_dialogue_font(s32 dialogueBoxID, s32 font) {
    if (dialogueBoxID >= 0 && dialogueBoxID < DIALOGUEBOXBACKGROUND_COUNT) {
        DialogueBoxBackground *temp = &gDialogueBoxBackground[dialogueBoxID];
        if (font < gNumberOfFonts) {
            temp->font = font;
        }
    }
}

void set_current_dialogue_background_colour(s32 dialogueBoxID, s32 red, s32 green, s32 blue, s32 alpha) {
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
    render_dialogue_text(dialogueBoxID, (*gDialogueBoxBackground)[dialogueBoxID].xpos, (*gDialogueBoxBackground)[dialogueBoxID].ypos, text, arg2, arg3);
}

GLOBAL_ASM("asm/non_matchings/font/render_dialogue_text.s")

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

// Unused
void func_800C54E8(s32 dialogueBoxID, unk800C54E8 *arg1, s32 arg2, s32 arg3, s32 arg4) {
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
    (*gDialogueBoxBackground)[dialogueBoxID].flags |= DIALOGUE_BOX_OPEN;
}

/**
 * Mark the selected dialogue box as closed
 */
void close_dialogue_box(s32 dialogueBoxID) {
    (*gDialogueBoxBackground)[dialogueBoxID].flags &= DIALOGUE_BOX_CLOSED;
}

/**
 * Mark the selected dialogue box as an unknown value
 */
UNUSED void func_800C564C(s32 dialogueBoxID) {
    (*gDialogueBoxBackground)[dialogueBoxID].flags |= DIALOGUE_BOX_UNUSED_01;
}

/**
 * Mark the selected dialogue box with every flag
 */
UNUSED void func_800C5678(s32 dialogueBoxID) {
    (*gDialogueBoxBackground)[dialogueBoxID].flags &= DIALOGUE_BOX_UNUSED_02;
}

/**
 * Mark the selected dialogue box as
 */
UNUSED void func_800C56A4(s32 dialogueBoxID) {
    (*gDialogueBoxBackground)[dialogueBoxID].flags |= DIALOGUE_BOX_UNK_01;
}

/**
 * Mark the selected dialogue box as open with
 */
void func_800C56D0(s32 dialogueBoxID) {
    (*gDialogueBoxBackground)[dialogueBoxID].flags &= DIALOGUE_BOX_UNK_02;
}

/**
 * Main function to render each dialogue box entry.
 * Contains a timer that counts down two frames before closing a dialogue box
 * when the player exits out of one.
 */
void render_dialogue_boxes(Gfx **dlist, Gfx **mat, VertexList **verts) {
    s32 i;

    if (sDialogueBoxIsOpen) {
        sDialogueBoxCloseTimer--;
        if (sDialogueBoxCloseTimer == 0) {
            dialogue_close_stub();
            sDialogueBoxIsOpen = FALSE;
        }
    }

    for (i = 1; i < DIALOGUEBOXBACKGROUND_COUNT; i++) {
        if ((*gDialogueBoxBackground)[i].flags & DIALOGUE_BOX_OPEN) {
                //render_printf("%X\n", (*gDialogueBoxBackground)[i].flags);
            if ((*gDialogueBoxBackground)[i].flags & DIALOGUE_BOX_UNK_01) {
                render_dialogue_box(dlist, mat, verts, i);
            } else {
                render_dialogue_box(dlist, NULL, NULL, i);
            }
        }
    }
}

#ifdef NON_EQUIVALENT
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
    u32 widthAndHeight = get_video_width_and_height_as_s32();
    u32 width = GET_VIDEO_WIDTH(widthAndHeight);
    u32 height = GET_VIDEO_HEIGHT(widthAndHeight);

    if (lrx >= 0 && (u32)ulx < width && lry >= 0 && (u32)uly < height) {
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
void render_dialogue_box(Gfx **dlist, Gfx **mat, VertexList **verts, s32 dialogueBoxID) {
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
            render_fill_rectangle(dlist, dialogueBox->x1 - 2, dialogueBox->y1 - 2, dialogueBox->x2 + 2, dialogueBox->y2 + 2);
        } else {
            render_fill_rectangle(dlist, dialogueBox->x1 - 2, dialogueBox->y1 + 2, dialogueBox->x1 + 2, dialogueBox->y2 - 2);
            render_fill_rectangle(dlist, dialogueBox->x1 - 2, dialogueBox->y1 - 2, dialogueBox->x2 + 2, dialogueBox->y1 + 2);
            render_fill_rectangle(dlist, dialogueBox->x2 - 2, dialogueBox->y1 + 2, dialogueBox->x2 + 2, dialogueBox->y2 - 2);
            render_fill_rectangle(dlist, dialogueBox->x1 - 2, dialogueBox->y2 - 2, dialogueBox->x2 + 2, dialogueBox->y2 + 2);
        }
        gDPPipeSync((*dlist)++);
        gDPSetEnvColor((*dlist)++, dialogueBox->backgroundColourR, dialogueBox->backgroundColourG, dialogueBox->backgroundColourB, dialogueBox->backgroundColourA);
        // Loops through sDialogueBoxDimensions, rendering fillrects until it forms a rounded rectangle.
        // The array determines the width and height of each entry before drawing it.
        for (i = 0; sDialogueBoxDimensions[i] >= 0; i += 5) {
            x1 = sDialogueBoxDimensions[i] + dialogueBox->x1;
            y1 = (sDialogueBoxDimensions[i + 1]) ? sDialogueBoxDimensions[i + 2] + dialogueBox->y2 : sDialogueBoxDimensions[i + 2] + dialogueBox->y1;
            x2 = dialogueBox->x2 - sDialogueBoxDimensions[i];
            y2 = (sDialogueBoxDimensions[i + 3]) ? sDialogueBoxDimensions[i + 4] + dialogueBox->y2 : sDialogueBoxDimensions[i + 4] + dialogueBox->y1;
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
