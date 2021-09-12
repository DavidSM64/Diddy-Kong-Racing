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

typedef struct unk8012A7E8_24 {
    u8 unk00;
    u8 unk01;
    char *unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 unk19;
    struct unk8012A7E8_24 *unk1C;
} unk8012A7E8_24;

/* Size: 0x28 bytes */
typedef struct unk8012A7E8 {
    s16 xpos;
    s16 ypos;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    u8 colorRed;
    u8 colorGreen;
    u8 colorBlue;
    u8 colorAlpha;
    u8 bgRed;
    u8 bgGreen;
    u8 bgBlue;
    u8 bgAlpha;
    u8 opacity;
    u8 font;
    u16 unk1E;
    s16 unk20;
    s16 unk22;
    unk8012A7E8_24 *unk24;
} unk8012A7E8;

/* Size: 0x20 bytes */
typedef struct unk8012A7EC {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
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

#define unk8012A7E8_COUNT 8
#define unk8012A7EC_COUNT 64
#define unk8012A7E8_TOTAL_SIZE (sizeof(unk8012A7E8) * unk8012A7E8_COUNT)
#define unk8012A7EC_TOTAL_SIZE (sizeof(unk8012A7EC) * unk8012A7EC_COUNT)

f32 func_8009E9B0(s32 arg0, Gfx **arg1, s32 *arg2, s32 *arg3); //menu.c
void func_8009E9A0(void); //menu.c
void func_8009E9A8(void); //menu.c
//TextureHeader *load_texture(s32 arg0); //texture_sprites.c NON_MATCHING

void load_fonts(void);
void func_800C4164(s32 arg0);
void set_text_font(s32 arg0);
void func_800C5B58(Gfx **dlist, s32 *arg1, s32 *arg2, s32 arg3);
void set_text_color(s32 red, s32 green, s32 blue, s32 alpha, s32 opacity);
void set_text_background_color(s32 red, s32 green, s32 blue, s32 alpha);
void func_800C4404(Gfx** displayList, char *text, s32 alignmentFlags);
void draw_text(Gfx** displayList, s32 xpos, s32 ypos, char *text, s32 alignmentFlags);
void func_800C44C0(Gfx** displayList, s32 arg1, char *text, s32 alignmentFlags);
void func_800C4510(Gfx** displayList, s32 arg1, s32 xpos, s32 ypos, char *text, s32 alignmentFlags);
void func_800C4EDC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_800C4F7C(s32 arg0, s32 font);
void func_800C4FBC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_800C5000(s32 arg0, s32 red, s32 green, s32 blue, s32 alpha, s32 opacity);
void func_800C5050(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_800C5094(s32 arg0, s32 arg1, s32 arg2);
void func_800C50D8(s32 arg0);
void func_800C510C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_800C5428(s32 arg0, unk8012A7E8_24 *arg1);
void func_800C5494(s32 arg0);
void func_800C54E8(s32 arg0, unk800C54E8 *arg1, s32 arg2, s32 arg3, s32 arg4);
void func_800C55F4(s32 arg0);
void func_800C5620(s32 arg0);
void func_800C564C(s32 arg0);
void func_800C5678(s32 arg0);
void func_800C56A4(s32 arg0);
void func_800C56D0(s32 arg0);
void func_800C56FC(s32 arg0, s32 arg1, s32 arg2);
void render_fill_rectangle(Gfx **dlist, s32 ulx, s32 uly, s32 lrx, s32 lry);
void func_800C5B58(Gfx **dlist, s32 *arg1, s32 *arg2, s32 arg3);
void parse_string_with_number(unsigned char *input, char *output, s32 number);

void s32_to_string(char** outString, s32 number); //Non Matching
TextureHeader *func_800C4318(s32 font, u8 arg1); //Non Matching
void func_800C4170(s32 arg0); //Non Matching
void func_800C422C(s32 arg0); //Non Matching
void func_800C45A4(Gfx **dlist, unk8012A7E8 *arg1, u8 *text, s32 alignmentFlags, f32 arg4); //Non Matching
s32 func_800C4DA0(u8 *text, s32 x, s32 font); //Non Matching
//void func_800C5168(s32, s16, s16, s32, s32, s32); //Non Matching

#endif
