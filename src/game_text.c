/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C29F0 */

#include "game_text.h"
#include "menu.h"
#include "objects.h"
#include "racer.h"
#include "game.h"

/************ .data ************/

s8 D_800E3670 = 0;
s16 D_800E3674 = 0;
s32 D_800E3678 = 0;
s32 D_800E367C = 0;
s32 D_800E3680 = 1;

/*******************************/

/************ .bss ************/

GameTextTableStruct *gGameTextTable[1];
s8 D_8012A784;
s8 D_8012A785;
s8 D_8012A786;
s8 D_8012A787;
s8 D_8012A788;
u8 D_8012A789;
u8 D_8012A78A;
s16 D_8012A78C;
s16 D_8012A78E;
s16 D_8012A790;
s16 D_8012A792;
char *D_8012A798[2]; //960 x2 bytes
char *D_8012A7A0;
s32 D_8012A7A4;
s16 sDialogueAlpha;
s16 D_8012A7AA;
s16 D_8012A7AC;
s16 sDialogueXPos1; // The Upper Left X Coord of the Dialogue Box.
s16 sDialogueYPos1; // The Upper Left Y Coord of the Dialogue Box. Changes for PAL / NTSC
s16 sDialogueXPos2; // The Lower Right X Coord of the Dialogue Box.
s16 sDialogueYPos2; // The Lower Right Y Coord of the Dialogue Box. Changes for PAL / NTSC
s16 D_8012A7B6;     // A Boolean value
s16 D_8012A7B8;
s16 D_8012A7BA;
s16 D_8012A7BE;
char *D_8012A7C0[1];
char *D_8012A7C8[2];
char *D_8012A7D0;
s32 D_8012A7D4;
s32 D_8012A7D8;
s32 D_8012A7DC;

/*****************************/

void func_800C29F0(void) {
    D_8012A7C8[0] = (char *) allocate_from_main_pool_safe(0x780, COLOUR_TAG_GREEN);
    D_8012A7C8[1] = D_8012A7C8[0] + 0x3C0;
    D_8012A7D4 = 0;
    D_8012A7B6 = 0;
    sDialogueAlpha = 0;
    D_8012A7AA = 32;
    D_8012A7BA = 0;
    sDialogueXPos1 = 32;
    sDialogueXPos2 = 288;
    if (osTvType == TV_TYPE_PAL) {
        sDialogueYPos1 = 224;
        sDialogueYPos2 = 248;
    } else {
        sDialogueYPos1 = SCREEN_HEIGHT - 38;
        sDialogueYPos2 = SCREEN_HEIGHT - 18;
    }
    func_800C56D0(6);
}

void func_800C2AB4(void) {
    free_from_memory_pool(D_8012A7C8[0]);
    D_8012A7B6 = 0;
    close_dialogue_box(6);
    assign_dialogue_box_id(6);
}

void func_800C2AF4(s32 arg0) {
    D_800E3680 = arg0;
}

void func_800C2B00(void) {
    s32 var_s1;
    s32 var_s3;
    s32 i;
    s32 textFlags;
    char **var_s2;

    assign_dialogue_box_id(6);
    set_current_dialogue_box_coords(6, sDialogueXPos1, sDialogueYPos1, sDialogueXPos2, sDialogueYPos2);
    set_current_dialogue_background_colour(6, 0x40, 0x60, 0x60, (sDialogueAlpha * 0xA0) >> 8);
    set_current_text_background_colour(6, 0, 0, 0, 0);
    var_s3 = ((((sDialogueYPos2 - sDialogueYPos1) - (D_8012A7B8 * 0xC)) - (D_8012A7B8 * 2)) + 2) >> 1;

    
    for (i = 0; i < D_8012A7B8; i++) {
        var_s2 = &D_8012A7C0[0];
        set_dialogue_font(6, (s32)var_s2[i][5]);
        textFlags = var_s2[i][6];
        if (textFlags == 4) {
            var_s1 = (sDialogueXPos2 - sDialogueXPos1) >> 1;
        } else {
            if (textFlags == 1) {
                var_s1 = (sDialogueXPos2 - sDialogueXPos1) - 8;
            } else {
                var_s1 = 8;
            }
        }
        set_current_text_colour(6, var_s2[i][1], var_s2[i][2], var_s2[i][3], 255, (var_s2[i][4] * sDialogueAlpha) >> 8);
        render_dialogue_text(6, var_s1, var_s3, var_s2[i] + 8, 1, textFlags);
        set_current_text_colour(6, 0, 0, 0, 255, (sDialogueAlpha * 255) >> 8);
        render_dialogue_text(6, var_s1 + 1, var_s3 + 1, var_s2[i] + 8, 1, textFlags);
        var_s3 += 14;
    }
    open_dialogue_box(6);
}

void func_800C2D6C(void) {
    u32 new_var3;
    u8 new_var;
    s32 new_var2;
    s32 done;
    
    D_8012A7B8 = 0;
    D_8012A7AC = 0;
    done = FALSE;
    while ((D_8012A7D0[0] != 0) && done == FALSE) {
        D_8012A7BA = D_8012A7D0[0] - 1;
        D_8012A7C0[(D_8012A7B8)] = D_8012A7D0;
        D_8012A7AC = normalise_time(D_8012A7D0[7] * 6);
        D_8012A7D0 += 8;
        do {
            new_var = D_8012A7D0[0];
            if (new_var & 0x80) {
            D_8012A7D0 += 2;
            } else {
            D_8012A7D0++;
            }
        } while (D_8012A7D0[0] != 0);
        D_8012A7B8++;
        if (D_8012A7B8 >= 2) {
            done = TRUE;
        }
        D_8012A7D0++;
        new_var3 = (new_var2 = D_8012A7D0[0]);
        if (D_8012A7D0[0] == 10) {
            D_8012A7D0++;
        } else if (new_var3 == 12) {
            D_8012A7D0++;
            done = TRUE;
        }
    }
    if (D_8012A7B8 > 0) {
    D_8012A7B6 = 1;
    }
}

void func_800C2F1C(s32 arg0) {
    if (D_800E3680 == 0) {
        D_8012A7B6 = 0;
    }
    if (D_8012A7B6 != 0) {
        if (D_8012A7AC <= 0) {
            sDialogueAlpha -= arg0 * D_8012A7AA;
            if (sDialogueAlpha < 0) {
                sDialogueAlpha = 0;
                D_8012A7B6 = 0;
                close_dialogue_box(6);
                assign_dialogue_box_id(6);
            }
        } else {
            sDialogueAlpha += arg0 * D_8012A7AA;
            if (sDialogueAlpha > 256) {
                sDialogueAlpha = 256;
            }
            D_8012A7AC -= arg0;
            if (D_8012A7AC <= 0) {
                func_800C2D6C();
            }
        }
    }
    if (D_8012A7B6 != 0) {
        func_800C2B00();
    }
}

void func_800C3048(void) {
    D_8012A78C = -1;
    gGameTextTable[0] = (GameTextTableStruct *) allocate_from_main_pool_safe(0x800, COLOUR_TAG_GREEN);
    D_8012A798[0] = (char *) &gGameTextTable[0]->entries[32];
    D_8012A798[1] = &D_8012A798[0][960];
    D_8012A7A4 = 0;
    func_800C29F0();
    D_8012A790 = (get_size_of_asset_section(ASSET_GAME_TEXT_TABLE) >> 2) - 2;
    D_800E3670 = 1;
}

void func_800C30CC(void) {
    s32 i;
    if (D_800E3670) {
        free_from_memory_pool(gGameTextTable[0]);
        D_800E3670 = 0;
        D_8012A789 = 0;
        for (i = 0; i < 10; i++) {
            func_8009CFB0();
        };
        func_800C2AB4();
    }
}

void func_800C3140(s32 arg0) {
    D_800E3674 = arg0;
}

void func_800C314C(void) {
    D_800E3678 = 0;
}

void func_800C3158(s32 arg0, f32 arg1) {
    if (osTvType == TV_TYPE_PAL) {
        D_800E3678 = arg1 * 50.0;
    } else {
        D_800E3678 = arg1 * 60.0;
    }
    D_800E367C = arg0;
}

void func_800C31EC(s32 arg0) {
    char **entries;
    UNUSED s32 pad;
    s32 size;
    s32 language;
    s32 temp;
    
  if ((D_800E3670 != 0) && (arg0 >= 0)) {
    if (arg0 < D_8012A790) {
      language = get_language();
      switch (language) {
        case LANGUAGE_GERMAN:
          arg0 += 0x55;
          break;
        case LANGUAGE_FRENCH:
          arg0 += 0xAA;
          break;
        case LANGUAGE_JAPANESE:
          arg0 += 0xFF;
          break;
      }

      load_asset_to_address(ASSET_GAME_TEXT_TABLE, (u32) (*gGameTextTable)->entries, (arg0 & (~1)) << 2, 16);
      
      entries = (*gGameTextTable)->entries;
      temp = ((s32) entries[(arg0 & 1)]) & 0xFF000000;
      size = (((s32) entries[(arg0 & 1) + 1]) & 0xFFFFFF) - (((s32) entries[(arg0 & 1)]) & 0xFFFFFF);
      
      if (temp) {
        load_asset_to_address(ASSET_GAME_TEXT, (u32) D_8012A7C8[D_8012A7D4], ((s32) entries[(arg0 & 1)]) ^ temp, size);
        D_8012A7D0 = D_8012A7C8[D_8012A7D4];
        func_800C2D6C();
        D_8012A7D4 = (D_8012A7D4 + 1) & 1;
        return;
      }
      load_asset_to_address(ASSET_GAME_TEXT, (u32) D_8012A798[D_8012A7A4], ((s32) entries[(arg0 & 1)]) ^ temp, size);
      D_8012A7A0 = D_8012A798[D_8012A7A4];
      D_8012A7A4 = (D_8012A7A4 + 1) & 1;
      D_8012A788 = 0;
      D_8012A786 = 0;
      D_8012A784 = 0;
      D_8012A787 = 1;
      D_8012A7A0[size] = 2;
      if (!D_8012A789) {
        D_8012A78E = 0;
        D_8012A78A = 1;
        D_8012A789 = 1;
      }
      return;
    }
  }
  D_8012A784 = 1;
}

s32 func_800C3400(void) {
    s32 result = 0;
    if (D_800E3670 != 0) {
        if (D_8012A789 != 0) {
            result = 1;
            if (D_8012A788 != 0) {
                result = 2;
            }
        }
    }
    return result;
}

void func_800C3440(s32 arg0) {
    if (D_800E3670 != 0) {
        if (!is_game_paused()) {
            if (D_800E3678 > 0) {
                D_800E3678 -= arg0;
                if (D_800E3678 <= 0) {
                    func_800C31EC(D_800E367C);
                    D_800E3678 = 0;
                }
            }
        }
        func_800C2F1C(arg0);
        if (D_8012A789 != 0) {
            func_8005A3B0();
            if (D_8012A786 != 0) {
                D_8012A785 -= arg0;
                while (D_8012A785 < 0) {
                    D_8012A785 += normalise_time(60);
                    D_8012A786--;
                }
                if (D_8012A786 <= 0) {
                    D_8012A784 = 1;
                }
            }
            func_8009CFEC(3);
        }
    }
}

s32 func_800C3564(void) {
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
    set_current_text_colour(1, textBox.textColRed, textBox.textColGreen, textBox.textColBlue, textBox.textColAlpha, 255);

    
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
        render_dialogue_text(1, xPos, textBox.textY, &D_8012A7A0[index], D_800E3674, textBox.textFlags);
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
        if (playerButtons & A_BUTTON || D_8012A784 != 0) {
            if (D_8012A7A0[index] == 1) {
                D_8012A78E += 1;
            } else {
                D_8012A789 = 0;
                func_8009CF68(3);
            }
            D_8012A784 = 0;
            D_8012A786 = 0;
        }
    }
    D_8012A78A = 0;
    return 1;
}

s32 func_800C38B4(s32 arg0, TextBox *textbox) {
    s32 temp;
    char *var_s0;

    var_s0 = &D_8012A7A0[arg0];
    while ((var_s0[0] >= 3) && (var_s0[0] < 13)) {
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
            if (osTvType == 0) {
                temp = textbox->top;
                textbox->top = ((textbox->top * 0x108) / 240);
                temp = textbox->top - temp;
            } else {
                temp = 0;
            }
            textbox->right = (D_8012A7A0[arg0 + 3] & 0xFF) + 0x41;
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
            set_current_text_colour(1, textbox->textColRed, textbox->textColGreen, textbox->textColBlue, textbox->textColAlpha, 255);
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
            if (D_8012A786 == 0) {
                D_8012A786 = var_s0[1] & 0xFF;
                D_8012A785 = normalise_time(0x3C);
                var_s0 = &D_8012A7A0[arg0];
            }
            arg0 += 2;
            var_s0 += 2;
            break;
        case 8:
            arg0 += 2;
            D_8012A787 = (s8) var_s0[1];
            var_s0 += 2;
            break;
        case 9:
            arg0 += 2;
            D_8012A788 = (s8) var_s0[1];
            var_s0 += 2;
            break;
        }
    }
    return arg0;
}
