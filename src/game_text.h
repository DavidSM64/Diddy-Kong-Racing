#ifndef _GAME_TEXT_H_
#define _GAME_TEXT_H_

#include "types.h"
#include "macros.h"
#include "f3ddkr.h"
#include "asset_enums.h"
#include "memory.h"
#include "font.h"

#define SET_TEXTBOX_BOUNDARY(leftVal, topVal, rightVal, bottomVal) \
    textBox.left = leftVal;                                        \
    textBox.top = topVal;                                          \
    textBox.right = rightVal;                                      \
    textBox.bottom = bottomVal

#define SET_TEXTBOX_TEXT_POS_AND_LINEHEIGHT(x, y, height) \
    textBox.textX = x;                                    \
    textBox.textY = y;                                    \
    textBox.lineHeight = height

enum TextProperties {
    TEXT_NONE,
    TEXT_COL_R,
    TEXT_COL_G,
    TEXT_COL_B,
    TEXT_ALPHA,
    TEXT_FONT,
    TEXT_FLAGS
};

typedef struct GameTextTableStruct  {
 char *entries[128];
 s32 *somethingElse;
} GameTextTableStruct;

typedef struct TextBox {
    s32 font;
    s32 left;
    s32 top;
    s32 right;
    s32 bottom;
    s32 textColRed;
    s32 textColGreen;
    s32 textColBlue;
    s32 textColAlpha;
    s32 textFlags;
    s32 textX;
    s32 textY;
    s32 lineHeight;
} TextBox;

void init_dialogue_text(void);
void free_message_box(void);
void set_subtitles(s32 setting);
void process_subtitles(s32 updateRate);
void load_game_text_table(void);
void free_game_text_table(void);
void set_textbox_display_value(s32 num);
void reset_delayed_text(void);
void set_delayed_text(s32 textID, f32 delay);
s32 textbox_visible(void);
void process_onscreen_textbox(s32 updateRate);
void find_next_subtitle(void);
s32 func_800C38B4(s32 arg0, TextBox *textbox);
void render_subtitles(void);
void set_current_text(s32 textID);
s32 dialogue_challenge_loop(void);

#endif
