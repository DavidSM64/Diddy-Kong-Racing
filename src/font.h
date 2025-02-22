#ifndef _FONT_H_
#define _FONT_H_

#include "memory.h"
#include "video.h"

#include "asset_loading.h"
#include "structs.h"
#include "types.h"
#include "macros.h"
#include "asset_enums.h"
#include <ultra64.h>
#include "f3ddkr.h"
#include "textures_sprites.h"

#define POS_CENTRED -0x8000

#define DIALOGUE_NUM_NULL 0xFF

typedef enum TextFonts {
    FONT_COLOURFUL,
    FONT_SMALL,
    FONT_LARGE,
    FONT_UNK_FF = 255
} TextFonts;

enum DialogueFlags {
    DIALOGUE_BOX_UNUSED_01 = 0x0001,
    DIALOGUE_BOX_VERTS     = 0x4000,
    DIALOGUE_BOX_CLOSED    = 0x7FFF,
    DIALOGUE_BOX_OPEN      = 0x8000
};

typedef struct unk800C54E8 {
    u8 pad0[0xC];
    s16 unkC;
    s16 unkE;
    u8 pad10[9];
    u8 unk19;
} unk800C54E8;

/* Size: 8 bytes */
typedef struct FontCharData {
    u8 textureID; // Texture Pointer Index?
    u8 ulx; // Upper Left Corner? Maybe only used when FontData->unk20 is 0 for some reason.
    u8 width; // Font Char Width?
    u8 height; // Font Char Height?
    u8 s; // Upper left coordinate for the texture derived from X?
    u8 t; // Upper left coordinate for the texture derived from Y?
    u8 lrx; // Related to the lower right X Coordinate.
    u8 lry; // Related to the lower right Y Coordinate.
} FontCharData;

/* Size: 0x400 bytes */
typedef struct FontData {
/* 0x000 */ s32 unk0; // Unused
/* 0x004 */ char name[28];
/* 0x020 */ u16 x;
/* 0x022 */ u16 y;
/* 0x024 */ u16 charWidth;
/* 0x026 */ u16 charHeight;
/* 0x028 */ u8 loadedFonts[24];
/* 0x040 */ s16 textureID[32];
/* 0x080 */ TextureHeader *texturePointers[32];
/* 0x100 */ FontCharData letter[96];
} FontData;

/* Size: 0x20 bytes */
//Dialogue Box text linked list (Including background struct)
typedef struct DialogueBox {
/* 0x00 */ u8 unk00; // Unused
/* 0x01 */ u8 textNum; // A number that is drawn with the text, like a balloon door telling you how many more you need.
/* 0x02 */ char *text; // Pointer to the text array
/* 0x06 */ s16 x1; // Left position of the text
/* 0x08 */ s16 y1; // Top portion of the text
/* 0x0A */ s16 x2; // Right portion of the text
/* 0x0C */ s16 y2; // Bottom portion of the text
/* 0x0E */ u8 textColourR;
/* 0x0F */ u8 textColourG;
/* 0x10 */ u8 textColourB;
/* 0x11 */ u8 textColourA;
/* 0x12 */ u8 textBGColourR;
/* 0x13 */ u8 textBGColourG;
/* 0x14 */ u8 textBGColourB;
/* 0x15 */ u8 textBGColourA;
/* 0x16 */ u8 opacity;
/* 0x17 */ u8 font;
/* 0x18 */ struct DialogueBox *nextBox;
} DialogueBox;


/* Size: 0x20 bytes */
typedef struct DialogueTextElement {
/* 0x00 */ u8 unk0;
/* 0x01 */ u8 number;
/* 0x02 */ u8 unk2;
/* 0x03 */ u8 unk3;
/* 0x04 */ char *text; // Pointer to the text array
/* 0x08 */ s16 posX;
/* 0x0A */ s16 posY;
/* 0x0C */ s16 offsetX;
/* 0x0E */ s16 offsetY;
/* 0x10 */ u8 textColourR;
/* 0x11 */ u8 textColourG;
/* 0x12 */ u8 textColourB;
/* 0x13 */ u8 textColourA;
/* 0x14 */ u8 textBGColourR;
/* 0x15 */ u8 textBGColourG;
/* 0x16 */ u8 textBGColourB;
/* 0x17 */ u8 textBGColourA;
/* 0x18 */ u8 opacity;
/* 0x19 */ u8 font;
/* 0x1A */ u16 flags;
/* 0x1C */ DialogueBox *nextBox;
} DialogueTextElement;

/* Size: 0x28 bytes */
// Dialogue Box background
typedef struct DialogueBoxBackground {
    s16 xpos;
    s16 ypos;
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
    s16 width;
    s16 height;
    u8 backgroundColourR; //Ideally should also be an array like the rest, but doesn't currently match.
    u8 backgroundColourG;
    u8 backgroundColourB;
    u8 backgroundColourA;
    //ColourRGBA textColour;
    u8 textColourR;
    u8 textColourG;
    u8 textColourB;
    u8 textColourA;
    u8 textBGColourR;
    u8 textBGColourG;
    u8 textBGColourB;
    u8 textBGColourA;
    u8 opacity;
    u8 font;
    u16 flags;
    s16 textOffsetX; // Functionally Unused
    s16 textOffsetY; // Functionally Unused
    DialogueBox *textBox;
} DialogueBoxBackground;

typedef struct Asset46 {
    s32 unk0;
    s32 unk4;
    u8 unk8;
} Asset46;

#define DIALOGUEBOXBACKGROUND_COUNT 8
#define DIALOGUETEXTELEMENT_COUNT 64
#define DIALOGUEBOXBACKGROUND_TOTAL_SIZE (sizeof(DialogueBoxBackground) * DIALOGUEBOXBACKGROUND_COUNT)
#define DialogueTextElement_TOTAL_SIZE (sizeof(DialogueTextElement) * DIALOGUETEXTELEMENT_COUNT)

void load_fonts(void);
void set_kerning(s32 setting);
void set_text_font(s32 fontID);
void set_text_colour(s32 red, s32 green, s32 blue, s32 alpha, s32 opacity);
void set_text_background_colour(s32 red, s32 green, s32 blue, s32 alpha);
void draw_text(Gfx** displayList, s32 xpos, s32 ypos, char *text, AlignmentFlags alignmentFlags);
void draw_dialogue_text_unused(Gfx **displayList, s32 dialogueBoxID, char *text, AlignmentFlags alignmentFlags);
void draw_dialogue_text_pos_unused(Gfx **displayList, s32 dialogueBoxID, s32 xpos, s32 ypos, char *text, AlignmentFlags alignmentFlags);
void set_current_dialogue_box_coords(s32 dialogueBoxID, s32 x1, s32 y1, s32 x2, s32 y2);
void set_dialogue_font(s32 dialogueBoxID, s32 font);
void set_current_dialogue_background_colour(s32 dialogueBoxID, s32 red, s32 green, s32 blue, s32 alpha);
void set_current_text_colour(s32 dialogueBoxID, s32 red, s32 green, s32 blue, s32 alpha, s32 opacity);
void set_current_text_background_colour(s32 dialogueBoxID, s32 red, s32 green, s32 blue, s32 alpha);
void move_dialogue_box_to_front(s32 dialogueBoxID, DialogueBox *dialogueBox);
void dialogue_clear(s32 dialogueBoxID);
void open_dialogue_box(s32 dialogueBoxID);
void dialogue_close(s32 dialogueBoxID);
void clear_dialogue_box_open_flag(s32 dialogueBoxID);
void render_dialogue_boxes(Gfx **dlist, MatrixS **mat, Vertex **verts);
void render_fill_rectangle(Gfx **dlist, s32 ulx, s32 uly, s32 lrx, s32 lry);
void render_dialogue_box(Gfx **dlist, MatrixS **mat, Vertex **verts, s32 dialogueBoxID);
void parse_string_with_number(char *input, char *output, s32 number);
void s32_to_string(char **outString, s32 number);
void load_font(s32 fontID);
void unload_font(s32 fontID);
void render_text_string(Gfx **dList, DialogueBoxBackground *box, char *text, AlignmentFlags alignmentFlags,
                        f32 scisScale);
s32 get_text_width(char *text, s32 x, s32 font);
void *render_dialogue_text(s32 dialogueBoxID, s32 posX, s32 posY, char *text, s32 number, s32 flags);

// Japanese Region exclusives
void func_800C6464_C7064(void);
void func_800C663C_C723C(void);
void func_800C6870_C7470(void);
void func_800C67F4_C73F4(void);
s32 func_800C68CC_C74CC(u16 arg0);
void func_800C6DD4_C79D4(Gfx *dlist, Asset46 *asset, s32 width, s32 height);
s32 func_800C7744_C8344(Gfx **dlist, u16 charIndex, s32 *outLeft, s32 *outTop, s32 *outRight, s32 *outBottom);
void func_800C7804_C8404(s32 arg0);
void func_800C7864_C8464(char *inString, char *outString);
void func_800C78E0_C84E0(void);

#endif
