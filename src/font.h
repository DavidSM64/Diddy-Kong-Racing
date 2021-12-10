#ifndef _FONT_H_
#define _FONT_H_

#include "memory.h"
#include "video.h"
#include "stacks.h"

#include "asset_loading.h"
#include "structs.h"
#include "types.h"
#include "macros.h"
#include "asset_sections.h"
#include "libultra_internal.h"
#include "f3ddkr.h"
#include "textures_sprites.h"

#define POS_CENTRED -0x8000

#define DIALOGUE_NUM_NULL 0xFF

enum TextFonts {
    FONT_COLOURFUL,
    FONT_SMALL,
    FONT_LARGE,
    FONT_UNK_FF = 255,
};

enum DialogueFlags {
    DIALOGUE_BOX_UNUSED_01 = 0x0001,
    DIALOGUE_BOX_UNK_01 = 0x4000,
    DIALOGUE_BOX_CLOSED =    0x7FFF,
    DIALOGUE_BOX_OPEN =      0x8000,
    DIALOGUE_BOX_UNK_02 =    0xBFFF,
    DIALOGUE_BOX_UNUSED_02 = 0xFFFE,
};

/* Size: 0x20 bytes */
typedef struct unk8012A7EC {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 textColourR;
    u8 textColourG;
    u8 textColourB;
    u8 textColourA;
    u8 textBGColourR;
    u8 textBGColourG;
    u8 textBGColourB;
    u8 textBGColourA;
    s32 unk18;
    s32 unk1C;
} unk8012A7EC;

typedef struct unk800C54E8 {
    u8 pad0[0xC];
    s16 unkC;
    s16 unkE;
    u8 pad10[9];
    u8 unk19;
} unk800C54E8;

/* Size: 8 bytes */
typedef struct FontCharData {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
} FontCharData;

/* Size: 0x400 bytes */
typedef struct FontData {
/* 0x000 */ s32 unk0;
/* 0x004 */ char name[0x1C];
/* 0x020 */ u16 unk20;
/* 0x022 */ u16 unk22;
/* 0x024 */ u16 unk24;
/* 0x026 */ u16 unk26;
/* 0x028 */ u8 unk28[24];
/* 0x040 */ s16 unk40[32];
/* 0x080 */ TextureHeader *texturePointers[32];
/* 0x100 */ FontCharData unk100[96];
} FontData;

//Dialogue Box text linked list (Including background struct)
typedef struct DialogueBox {
    u8 unk00; // Unused
    u8 textNum; // A number that is drawn with the text, like a balloon door telling you how many more you need.
    char *text; // Pointer to the text array
    s16 x1; // Left position of the text
    s16 y1; // Top portion of the text
    s16 x2; // Right portion of the text
    s16 y2; // Bottom portion of the text
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
    struct DialogueBox *nextBox;
} DialogueBox;

typedef struct {
    u8 r;
    u8 b;
    u8 g;
    u8 a;
} ColourRGBA;

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
    s16 unk20; // Functionally Unused
    s16 unk22; // Functionally Unused
    DialogueBox *textBox;
} DialogueBoxBackground;

#define DIALOGUEBOXBACKGROUND_COUNT 8
#define unk8012A7EC_COUNT 64
#define DIALOGUEBOXBACKGROUND_TOTAL_SIZE (sizeof(DialogueBoxBackground) * DIALOGUEBOXBACKGROUND_COUNT)
#define unk8012A7EC_TOTAL_SIZE (sizeof(unk8012A7EC) * unk8012A7EC_COUNT)

void load_fonts(void);
void func_800C4164(s32 arg0);
void set_text_font(s32 arg0);
void render_dialogue_box(Gfx **dlist, Gfx *mat, VertexList *verts, s32 index);
void set_text_color(s32 red, s32 green, s32 blue, s32 alpha, s32 opacity);
void set_text_background_color(s32 red, s32 green, s32 blue, s32 alpha);
void func_800C4404(Gfx** displayList, char *text, s32 alignmentFlags);
void draw_text(Gfx** displayList, s32 xpos, s32 ypos, char *text, s32 alignmentFlags);
void func_800C44C0(Gfx** displayList, s32 arg1, char *text, s32 alignmentFlags);
void func_800C4510(Gfx** displayList, s32 arg1, s32 xpos, s32 ypos, char *text, s32 alignmentFlags);
void set_current_dialogue_box_coords(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void set_dialogue_font(s32 arg0, s32 font);
void set_current_dialogue_background_colour(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void set_current_text_colour(s32 arg0, s32 red, s32 green, s32 blue, s32 alpha, s32 opacity);
void set_current_text_background_colour(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_800C5094(s32 arg0, s32 arg1, s32 arg2);
void func_800C50D8(s32 arg0);
void func_800C510C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void move_dialogue_box_to_front(s32 arg0, DialogueBox *arg1);
void assign_dialogue_box_id(s32 arg0);
void func_800C54E8(s32 arg0, unk800C54E8 *arg1, s32 arg2, s32 arg3, s32 arg4);
void open_dialogue_box(s32 dialogueBoxID);
void close_dialogue_box(s32 dialogueBoxID);
UNUSED void func_800C564C(s32 dialogueBoxID);
UNUSED void func_800C5678(s32 dialogueBoxID);
UNUSED void func_800C56A4(s32 dialogueBoxID);
void func_800C56D0(s32 dialogueBoxID);
void render_dialogue_boxes(Gfx *dlist, Gfx *mat, VertexList *verts);
void render_fill_rectangle(Gfx **dlist, s32 ulx, s32 uly, s32 lrx, s32 lry);
void render_dialogue_box(Gfx **dlist, Gfx *mat, VertexList *verts, s32 index);
void parse_string_with_number(unsigned char *input, char *output, s32 number);

void s32_to_string(char** outString, s32 number); //Non Matching
TextureHeader *func_800C4318(s32 font, u8 arg1); //Non Matching
void func_800C4170(s32 arg0); //Non Matching
void func_800C422C(s32 arg0); //Non Matching
void func_800C45A4(Gfx **dlist, DialogueBoxBackground *arg1, u8 *text, s32 alignmentFlags, f32 arg4); //Non Matching
s32 func_800C4DA0(u8 *text, s32 x, s32 font); //Non Matching
//void render_dialogue_text(s32 unk01, s16 posX, s16 posY, s32 text, s32 unk01, s32 unk02); //Non Matching

#endif
