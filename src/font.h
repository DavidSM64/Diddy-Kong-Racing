#ifndef _FONT_H_
#define _FONT_H_

#include "memory.h"
#include "video.h"
#include "stacks.h"

#include "asset_loading.h"
#include "structs.h"
#include "types.h"
#include "macros.h"
#include "asset_enums.h"
#include "libultra_internal.h"
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
    DIALOGUE_BOX_VERTS = 0x4000,
    DIALOGUE_BOX_CLOSED =    0x7FFF,
    DIALOGUE_BOX_OPEN =      0x8000,
    DIALOGUE_BOX_UNK_02 =    0xBFFF,
    DIALOGUE_BOX_UNUSED_02 = 0xFFFE
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
    u8 unk0; // Texture Pointer Index?
    u8 unk1; // Upper Left Corner? Maybe only used when FontData->unk20 is 0 for some reason.
    u8 unk2; // Font Char Width?
    u8 unk3; // Font Char Height?
    u8 unk4; // Upper left coordinate for the texture derived from X?
    u8 unk5; // Upper left coordinate for the texture derived from Y?
    u8 unk6; // Related to the lower right X Coordinate.
    u8 unk7; // Related to the lower right Y Coordinate.
} FontCharData;

/* Size: 0x400 bytes */
typedef struct FontData {
/* 0x000 */ s32 unk0;
/* 0x004 */ char name[0x1C];
/* 0x020 */ u16 unk20; // x1?
/* 0x022 */ u16 unk22; // y1?
/* 0x024 */ u16 unk24; // x2?
/* 0x026 */ u16 unk26; // y2?
/* 0x028 */ u8 unk28[24];
/* 0x040 */ s16 unk40[32];
/* 0x080 */ TextureHeader *texturePointers[32];
/* 0x100 */ FontCharData unk100[96];
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
typedef struct unk8012A7EC {
/* 0x00 */ u8 unk0;
/* 0x01 */ u8 unk1;
/* 0x02 */ u8 unk2;
/* 0x03 */ u8 unk3;
/* 0x04 */ char *text; // Pointer to the text array
/* 0x08 */ s16 posX;
/* 0x0A */ s16 posY;
/* 0x0C */ s16 unkC;
/* 0x0E */ s16 unkE;
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
} unk8012A7EC;

typedef struct {
    u8 r;
    u8 g;
    u8 b;
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
    s16 textOffsetX; // Functionally Unused
    s16 textOffsetY; // Functionally Unused
    DialogueBox *textBox;
} DialogueBoxBackground;

#define DIALOGUEBOXBACKGROUND_COUNT 8
#define unk8012A7EC_COUNT 64
#define DIALOGUEBOXBACKGROUND_TOTAL_SIZE (sizeof(DialogueBoxBackground) * DIALOGUEBOXBACKGROUND_COUNT)
#define unk8012A7EC_TOTAL_SIZE (sizeof(unk8012A7EC) * unk8012A7EC_COUNT)

void load_fonts(void);
void set_kerning(s32 arg0);
void set_text_font(s32 arg0);
void set_text_colour(s32 red, s32 green, s32 blue, s32 alpha, s32 opacity);
void set_text_background_colour(s32 red, s32 green, s32 blue, s32 alpha);
void draw_text(Gfx** displayList, s32 xpos, s32 ypos, char *text, AlignmentFlags alignmentFlags);
void draw_dialogue_text_unused(Gfx** displayList, s32 dialogueBoxID, char *text, AlignmentFlags alignmentFlags);
void draw_dialogue_text_pos_unused(Gfx** displayList, s32 dialogueBoxID, s32 xpos, s32 ypos, char *text, AlignmentFlags alignmentFlags);
void set_current_dialogue_box_coords(s32 dialogueBoxID, s32 x1, s32 y1, s32 x2, s32 y2);
void set_dialogue_font(s32 dialogueBoxID, s32 font);
void set_current_dialogue_background_colour(s32 dialogueBoxID, s32 red, s32 green, s32 blue, s32 alpha);
void set_current_text_colour(s32 dialogueBoxID, s32 red, s32 green, s32 blue, s32 alpha, s32 opacity);
void set_current_text_background_colour(s32 dialogueBoxID, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void move_dialogue_box_to_front(s32 arg0, DialogueBox *arg1);
void assign_dialogue_box_id(s32 arg0);
void func_800C54E8(s32 arg0, unk800C54E8 *arg1, s32 arg2, s32 arg3, s32 arg4);
void open_dialogue_box(s32 dialogueBoxID);
void close_dialogue_box(s32 dialogueBoxID);
UNUSED void set_dialogue_box_unused_flag(s32 dialogueBoxID);
UNUSED void dialogue_box_clear_flags(s32 dialogueBoxID);
UNUSED void enable_dialogue_box_vertices(s32 dialogueBoxID);
void func_800C56D0(s32 dialogueBoxID);
void render_dialogue_boxes(Gfx **dlist, Matrix **mat, VertexList **verts);
void render_fill_rectangle(Gfx **dlist, s32 ulx, s32 uly, s32 lrx, s32 lry);
void render_dialogue_box(Gfx **dlist, Matrix **mat, VertexList **verts, s32 dialogueBoxID);
void parse_string_with_number(char *input, char *output, s32 number);
void s32_to_string(char **outString, s32 number);

void load_font(s32 fontID); //Non Matching
void unload_font(s32 arg0); //Non Matching
void render_text_string(Gfx **dlist, DialogueBoxBackground *arg1, char *text, AlignmentFlags alignmentFlags, f32 arg4); //Non Matching
s32 get_text_width(char *text, s32 x, s32 font); //Non Matching
void *render_dialogue_text(s32 dialogueBoxID, s32 posX, s32 posY, char *text, s32 arg4, s32 arg5); //Non Matching

#endif
