/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C29F0 */

#include "game_text.h"
#include "menu.h"
#include "objects.h"
#include "racer.h"
#include "game.h"
#include "controller.h"

/************ .data ************/

s8 gTextTableExists = FALSE;
s16 gTextDisplayNumber = 0;
s32 gTextboxDelay = 0;
s32 gDelayedTextID = 0;
s32 gSubtitleSetting = TRUE;

/*******************************/

/************ .bss ************/

GameTextTableStruct *gGameTextTable[1];
s8 gCloseTextMessage;
s8 gTextCloseTimerFrames;
s8 gTextCloseTimerSeconds;
s8 D_8012A787;
s8 D_8012A788;
u8 gShowOnscreenMessage;
u8 D_8012A78A;
UNUSED s16 D_8012A78C; // Set to -1, never read.
s16 D_8012A78E;
s16 gTextTableEntries;
UNUSED s16 D_8012A792;
char *gGameTextTableEntries[2]; // 960 x2 bytes
char *D_8012A7A0;
s32 D_8012A7A4;
s16 gDialogueAlpha;
s16 gTextAlphaVelocity;
s16 gSubtitleTimer;
s16 gDialogueXPos1; // The Upper Left X Coord of the Dialogue Box.
s16 gDialogueYPos1; // The Upper Left Y Coord of the Dialogue Box. Changes for PAL / NTSC
s16 gDialogueXPos2; // The Lower Right X Coord of the Dialogue Box.
s16 gDialogueYPos2; // The Lower Right Y Coord of the Dialogue Box. Changes for PAL / NTSC
s16 gShowSubtitles;
s16 gSubtitleLineCount;
s16 gCurrentTextID;
UNUSED s16 D_8012A7BE;
char *gSubtitleProperties[1];
char *gCurrentMessageText[2];
char *gCurrentTextProperties;
s32 D_8012A7D4;

/*****************************/

/**
 * Set the default values of dialogue and allocate memory for the active text entry.
 */
void init_dialogue_text(void) {
    gCurrentMessageText[0] = (char *) allocate_from_main_pool_safe(0x780, COLOUR_TAG_GREEN);
    gCurrentMessageText[1] = gCurrentMessageText[0] + 0x3C0;
    D_8012A7D4 = 0;
    gShowSubtitles = FALSE;
    gDialogueAlpha = 0;
    gTextAlphaVelocity = 32;
    gCurrentTextID = 0;
    gDialogueXPos1 = 32;
    gDialogueXPos2 = 288;
    if (osTvType == TV_TYPE_PAL) {
        gDialogueYPos1 = 224;
        gDialogueYPos2 = 248;
    } else {
        gDialogueYPos1 = SCREEN_HEIGHT - 38;
        gDialogueYPos2 = SCREEN_HEIGHT - 18;
    }
    clear_dialogue_box_open_flag(6);
}

/**
 * Close screen dialogue and free the text currently loaded into it.
 */
void free_message_box(void) {
    free_from_memory_pool(gCurrentMessageText[0]);
    gShowSubtitles = FALSE;
    dialogue_close(6);
    dialogue_clear(6);
}

/**
 * Toggle an override that prevents subtitles from showing.
 */
void set_subtitles(s32 setting) {
    gSubtitleSetting = setting;
}

/**
 * Render currently active subtitles on the screen.
 */
void render_subtitles(void) {
    s32 textX;
    s32 textY;
    s32 i;
    s32 textFlags;
    char **textData;

    dialogue_clear(6);
    set_current_dialogue_box_coords(6, gDialogueXPos1, gDialogueYPos1, gDialogueXPos2, gDialogueYPos2);
    set_current_dialogue_background_colour(6, 64, 96, 96, (gDialogueAlpha * 160) >> 8);
    set_current_text_background_colour(6, 0, 0, 0, 0);
    textY = ((((gDialogueYPos2 - gDialogueYPos1) - (gSubtitleLineCount * 12)) - (gSubtitleLineCount * 2)) + 2) >> 1;

    for (i = 0; i < gSubtitleLineCount; i++) {
        textData = &gSubtitleProperties[0];
        set_dialogue_font(6, (s32) textData[i][TEXT_FONT]);
        textFlags = textData[i][TEXT_FLAGS];
        if (textFlags == ALIGN_TOP_CENTER) {
            textX = (gDialogueXPos2 - gDialogueXPos1) >> 1;
        } else {
            if (textFlags == ALIGN_TOP_RIGHT) {
                textX = (gDialogueXPos2 - gDialogueXPos1) - 8;
            } else {
                textX = 8;
            }
        }
        set_current_text_colour(6, textData[i][TEXT_COL_R], textData[i][TEXT_COL_G], textData[i][TEXT_COL_B], 255,
                                (textData[i][TEXT_ALPHA] * gDialogueAlpha) >> 8);
        render_dialogue_text(6, textX, textY, textData[i] + 8, 1, textFlags);
        set_current_text_colour(6, 0, 0, 0, 255, (gDialogueAlpha * 255) >> 8);
        render_dialogue_text(6, textX + 1, textY + 1, textData[i] + 8, 1, textFlags);
        textY += 14;
    }
    open_dialogue_box(6);
}

/**
 * Get the line count and text timer from the next message of the subtitle.
 * Close the subtitles if none can be found.
 */
void find_next_subtitle(void) {
    u32 new_var3;
    u8 new_var;
    s32 new_var2;
    s32 done;

    gSubtitleLineCount = 0;
    gSubtitleTimer = 0;
    done = FALSE;
    while (gCurrentTextProperties[0] != NULL && done == FALSE) {
        gCurrentTextID = gCurrentTextProperties[0] - 1;
        gSubtitleProperties[gSubtitleLineCount] = gCurrentTextProperties;
        gSubtitleTimer = normalise_time(gCurrentTextProperties[7] * 6);
        gCurrentTextProperties += 8;
        do {
            new_var = gCurrentTextProperties[0];
            if (new_var & 0x80) {
                gCurrentTextProperties += 2;
            } else {
                gCurrentTextProperties++;
            }
        } while (gCurrentTextProperties[0] != NULL);
        gSubtitleLineCount++;
        if (gSubtitleLineCount >= 2) {
            done = TRUE;
        }
        gCurrentTextProperties++;
        new_var3 = (new_var2 = gCurrentTextProperties[0]);
        if (gCurrentTextProperties[0] == 10) {
            gCurrentTextProperties++;
        } else if (new_var3 == 12) {
            gCurrentTextProperties++;
            done = TRUE;
        }
    }
    if (gSubtitleLineCount > 0) {
        gShowSubtitles = TRUE;
    }
}

/**
 * Handle the subtitle system from here.
 * Slowly show the text, tick down the timer, find the next message or close the box, then render.
 */
void process_subtitles(s32 updateRate) {
    if (gSubtitleSetting == FALSE) {
        gShowSubtitles = FALSE;
    }
    if (gShowSubtitles) {
        if (gSubtitleTimer <= 0) {
            gDialogueAlpha -= updateRate * gTextAlphaVelocity;
            if (gDialogueAlpha < 0) {
                gDialogueAlpha = 0;
                gShowSubtitles = FALSE;
                dialogue_close(6);
                dialogue_clear(6);
            }
        } else {
            gDialogueAlpha += updateRate * gTextAlphaVelocity;
            if (gDialogueAlpha > 256) {
                gDialogueAlpha = 256;
            }
            gSubtitleTimer -= updateRate;
            if (gSubtitleTimer <= 0) {
                find_next_subtitle();
            }
        }
    }
    if (gShowSubtitles) {
        render_subtitles();
    }
}

/**
 * Load the text table into RAM.
 * Assign the entries to a pointer table, then calculate the number of entries.
 */
void load_game_text_table(void) {
    D_8012A78C = -1;
    gGameTextTable[0] = (GameTextTableStruct *) allocate_from_main_pool_safe(0x800, COLOUR_TAG_GREEN);
    gGameTextTableEntries[0] = (char *) &gGameTextTable[0]->entries[32];
    gGameTextTableEntries[1] = &gGameTextTableEntries[0][960];
    D_8012A7A4 = 0;
    init_dialogue_text();
    gTextTableEntries = (get_size_of_asset_section(ASSET_GAME_TEXT_TABLE) >> 2) - 2;
    gTextTableExists = TRUE;
}

/**
 * Free the text table from RAM.
 * Close every dialogue box, then call a function that frees menu dialogue, too.
 */
void free_game_text_table(void) {
    s32 i;
    if (gTextTableExists) {
        free_from_memory_pool(gGameTextTable[0]);
        gTextTableExists = FALSE;
        gShowOnscreenMessage = FALSE;
        for (i = 0; i < 10; i++) {
            dialogue_try_close();
        };
        free_message_box();
    }
}

/**
 * Set the variable used by the message boxes when trying to display an arbitrary number.
 */
void set_textbox_display_value(s32 num) {
    gTextDisplayNumber = num;
}

/**
 * Sets the delayed text timer back to 0.
 */
void reset_delayed_text(void) {
    gTextboxDelay = 0;
}

/**
 * Set the delayed text ID and delay (in seconds)
 */
void set_delayed_text(s32 textID, f32 delay) {
    if (osTvType == TV_TYPE_PAL) {
        gTextboxDelay = delay * 50.0;
    } else {
        gTextboxDelay = delay * 60.0;
    }
    gDelayedTextID = textID;
}

/**
 * Set the current text index based on the entry.
 * Start certain behaviours based on the header,
 * like showing a subtitle, or opening an onscreen text box.
 */
void set_current_text(s32 textID) {
    char **entries;
    UNUSED s32 pad;
    s32 size;
    s32 language;
    s32 temp;

    if (gTextTableExists && textID >= 0 && textID < gTextTableEntries) {
        language = get_language();
        switch (language) {
            case LANGUAGE_GERMAN:
                textID += 85;
                break;
            case LANGUAGE_FRENCH:
                textID += 170;
                break;
            case LANGUAGE_JAPANESE:
                textID += 255;
                break;
        }

        load_asset_to_address(ASSET_GAME_TEXT_TABLE, (u32) (*gGameTextTable)->entries, (textID & (~1)) << 2, 16);

        entries = (*gGameTextTable)->entries;
        temp = ((s32) entries[textID & 1]) & 0xFF000000;
        size = (((s32) entries[(textID & 1) + 1]) & 0xFFFFFF) - (((s32) entries[textID & 1]) & 0xFFFFFF);

        if (temp) {
            load_asset_to_address(ASSET_GAME_TEXT, (u32) gCurrentMessageText[D_8012A7D4],
                                  ((s32) entries[textID & 1]) ^ temp, size);
            gCurrentTextProperties = gCurrentMessageText[D_8012A7D4];
            find_next_subtitle();
            D_8012A7D4 = (D_8012A7D4 + 1) & 1;
            return;
        }
        load_asset_to_address(ASSET_GAME_TEXT, (u32) gGameTextTableEntries[D_8012A7A4],
                              ((s32) entries[textID & 1]) ^ temp, size);
        D_8012A7A0 = gGameTextTableEntries[D_8012A7A4];
        D_8012A7A4 = (D_8012A7A4 + 1) & 1;
        D_8012A788 = 0;
        gTextCloseTimerSeconds = 0;
        gCloseTextMessage = FALSE;
        D_8012A787 = 1;
        D_8012A7A0[size] = 2;
        if (gShowOnscreenMessage == FALSE) {
            D_8012A78E = 0;
            D_8012A78A = 1;
            gShowOnscreenMessage = TRUE;
        }
        return;
    }
    gCloseTextMessage = TRUE;
}

/**
 * Returns nonzero if a textbox is visible.
 * The number depends on what kind it is.
 */
s32 textbox_visible(void) {
    s32 result = 0;
    if (gTextTableExists) {
        if (gShowOnscreenMessage) {
            result = 1;
            if (D_8012A788) {
                result = 2;
            }
        }
    }
    return result;
}

/**
 * Top level function for handling message boxes and dialogue.
 * Calls a function too, to load in text entries when needed.
 */
void process_onscreen_textbox(s32 updateRate) {
    if (gTextTableExists) {
        if (!is_game_paused()) {
            if (gTextboxDelay > 0) {
                gTextboxDelay -= updateRate;
                if (gTextboxDelay <= 0) {
                    set_current_text(gDelayedTextID);
                    gTextboxDelay = 0;
                }
            }
        }
        process_subtitles(updateRate);
        if (gShowOnscreenMessage) {
            disable_racer_input();
            if (gTextCloseTimerSeconds) {
                gTextCloseTimerFrames -= updateRate;
                while (gTextCloseTimerFrames < 0) {
                    gTextCloseTimerFrames += normalise_time(60);
                    gTextCloseTimerSeconds--;
                }
                if (gTextCloseTimerSeconds <= 0) {
                    gCloseTextMessage = TRUE;
                }
            }
            npc_dialogue_loop(DIALOGUE_CHALLENGE);
        }
    }
}

s32 dialogue_challenge_loop(void) {
    s32 xPos;
    s32 index;
    s32 numberOfOnes;
    s32 keepLooping;
    u32 playerButtons;
    TextBox textBox;

    textBox.font = ASSET_FONTS_FUNFONT;
    SET_TEXTBOX_BOUNDARY(10, 15, 180, 125);
    textBox.textFlags = 4;
    textBox.textColRed = 0;
    textBox.textColGreen = 0;
    textBox.textColBlue = 0;
    textBox.textColAlpha = 0;
    SET_TEXTBOX_TEXT_POS_AND_LINEHEIGHT(5, 10, 15);

    set_current_dialogue_box_coords(1, textBox.left, textBox.top, textBox.right, textBox.bottom);
    set_dialogue_font(1, textBox.font);
    set_current_dialogue_background_colour(1, 0, 16, 16, 128);
    set_current_text_colour(1, textBox.textColRed, textBox.textColGreen, textBox.textColBlue, textBox.textColAlpha,
                            255);

    for (index = 0, numberOfOnes = 0; D_8012A78E != numberOfOnes && D_8012A7A0[index] != 2; index++) {
        if (D_8012A7A0[index] >= 3 && D_8012A7A0[index] < 13) {
            index = func_800C38B4(index, &textBox);
        }
        if (D_8012A7A0[index] == 1) {
            numberOfOnes++;
        }
    }
    if (D_8012A7A0[index] >= 3 && D_8012A7A0[index] < 13) {
        index = func_800C38B4(index, &textBox);
    }

    keepLooping = TRUE;
    do {
        if (textBox.textFlags == 0) {
            xPos = textBox.textX;
        } else {
            xPos = (s32) (textBox.right - textBox.left) >> 1; // Center x position to box.
        }
        render_dialogue_text(1, xPos, textBox.textY, &D_8012A7A0[index], gTextDisplayNumber, textBox.textFlags);
        textBox.textY += textBox.lineHeight;
        while (D_8012A7A0[index] > 0) {
            index += 1;
        }
        while (D_8012A7A0[index] == 0) {
            index += 1;
        }
        if (D_8012A7A0[index] < 3) {
            keepLooping = FALSE;
        }
        if (D_8012A7A0[index] >= 3 && D_8012A7A0[index] < 13) {
            index = func_800C38B4(index, &textBox);
        }
    } while (keepLooping);
    playerButtons = get_buttons_pressed_from_player(PLAYER_ONE);
    if (D_8012A787 == 0) {
        playerButtons = 0;
    }
    if (D_8012A78A == 0) {
        if (playerButtons & A_BUTTON || gCloseTextMessage) {
            if (D_8012A7A0[index] == 1) {
                D_8012A78E += 1;
            } else {
                gShowOnscreenMessage = FALSE;
                dialogue_npc_finish(3);
            }
            gCloseTextMessage = FALSE;
            gTextCloseTimerSeconds = 0;
        }
    }
    D_8012A78A = 0;
    return 1;
}

s32 func_800C38B4(s32 arg0, TextBox *textbox) {
    s32 temp;
    char *var_s0;

    var_s0 = &D_8012A7A0[arg0];
    while (var_s0[0] >= 3 && var_s0[0] < 13) {
        switch (var_s0[0] - 3) {
            case 0:
                textbox->font = var_s0[1];
                arg0 += 2;
                set_dialogue_font(1, textbox->font);
                var_s0 = &D_8012A7A0[arg0];
                break;
            case 1:
                textbox->left = var_s0[1] & 0xFF;
                textbox->top = D_8012A7A0[arg0 + 2] & 0xFF;
                if (osTvType == TV_TYPE_PAL) {
                    temp = textbox->top;
                    textbox->top = (textbox->top * 264) / 240;
                    temp = textbox->top - temp;
                } else {
                    temp = 0;
                }
                textbox->right = (D_8012A7A0[arg0 + 3] & 0xFF) + 65;
                textbox->bottom = (D_8012A7A0[arg0 + 4] & 0xFF) + temp;
                arg0 += 5;
                set_current_dialogue_box_coords(1, textbox->left, textbox->top, textbox->right, textbox->bottom);
                var_s0 = &D_8012A7A0[arg0];
                break;
            case 2:
                textbox->textColRed = var_s0[1];
                textbox->textColGreen = D_8012A7A0[arg0 + 2];
                textbox->textColBlue = D_8012A7A0[arg0 + 3];
                textbox->textColAlpha = D_8012A7A0[arg0 + 4];
                arg0 += 5;
                set_current_text_colour(1, textbox->textColRed, textbox->textColGreen, textbox->textColBlue,
                                        textbox->textColAlpha, 255);
                var_s0 = &D_8012A7A0[arg0];
                break;
            case 3:
                if (var_s0[1] == 0) {
                    textbox->textFlags = 4;
                } else {
                    textbox->textFlags = 0;
                }
                arg0 += 2;
                var_s0 = &D_8012A7A0[arg0];
                break;
            case 4:
                arg0 += 2;
                textbox->textX = var_s0[1];
                var_s0 = &D_8012A7A0[arg0];
                break;
            case 5:
                arg0 += 2;
                textbox->textY += var_s0[1];
                var_s0 = &D_8012A7A0[arg0];
                break;
            case 6:
                arg0 += 2;
                textbox->lineHeight = var_s0[1];
                var_s0 = &D_8012A7A0[arg0];
                break;
            case 7:
                if (gTextCloseTimerSeconds == 0) {
                    gTextCloseTimerSeconds = var_s0[1] & 0xFF;
                    gTextCloseTimerFrames = normalise_time(60);
                    var_s0 = &D_8012A7A0[arg0];
                }
                arg0 += 2;
                var_s0 += 2;
                break;
            case 8:
                arg0 += 2;
                D_8012A787 = var_s0[1];
                var_s0 += 2;
                break;
            case 9:
                arg0 += 2;
                D_8012A788 = var_s0[1];
                var_s0 += 2;
                break;
        }
    }
    return arg0;
}
