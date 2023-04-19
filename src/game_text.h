#ifndef _GAME_TEXT_H_
#define _GAME_TEXT_H_

#include "types.h"
#include "macros.h"
#include "f3ddkr.h"
#include "asset_enums.h"
#include "memory.h"
#include "font.h"
#include "PR/libultra.h"

#define SET_TEXTBOX_BOUNDARY(leftVal, topVal, rightVal, bottomVal) \
    textBox.left = leftVal;                                        \
    textBox.top = topVal;                                          \
    textBox.right = rightVal;                                      \
    textBox.bottom = bottomVal

#define SET_TEXTBOX_TEXT_POS_AND_LINEHEIGHT(x, y, height) \
    textBox.textX = x;                                    \
    textBox.textY = y;                                    \
    textBox.lineHeight = height

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


void func_800C29F0(void);
void func_800C2AB4(void);
void func_800C2AF4(s32 arg0);
void func_800C2F1C(s32 arg0);
void func_800C3048(void);
void func_800C30CC(void);
void func_800C3140(s32 arg0);
void func_800C314C(void);
void func_800C3158(s32 arg0, f32 arg1);
s32 func_800C3400(void);
void func_800C3440(s32 arg0);
void func_800C2D6C(void);
s32 func_800C38B4(s32 arg0, TextBox *textbox);
void func_800C2B00(void);
void func_800C31EC(s32 arg0);
s32 func_800C3564(void);

#endif
