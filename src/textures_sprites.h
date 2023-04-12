#ifndef _TEXTURES_SPRITES_H_
#define _TEXTURES_SPRITES_H_

#include "asset_enums.h"
#include "types.h"
#include "f3ddkr.h"
#include "structs.h"
#include "macros.h"
#include "memory.h"
#include "libultra_internal.h"

enum RenderFlags {
    RENDER_NONE,
    RENDER_ANTI_ALIASING = (1 << 0),
    RENDER_Z_COMPARE =     (1 << 1),
    RENDER_SEMI_TRANSPARENT = (1 << 2),
    RENDER_FOG_ACTIVE = (1 << 3),
    RENDER_UNK_0000010 = (1 << 4),
    RENDER_COLOUR_INDEX = (1 << 5),
    RENDER_UNK_0000040 = (1 << 6),
    RENDER_UNK_0000080 = (1 << 7),
    RENDER_Z_UPDATE = (1 << 8),
    RENDER_UNK_0000200 = (1 << 9),
    RENDER_UNK_0000400 = (1 << 10),
    RENDER_DECAL = (1 << 11),
    RENDER_UNK_0001000 = (1 << 12),
    RENDER_UNK_0002000 = (1 << 13),
    RENDER_UNK_0004000 = (1 << 14),
    RENDER_UNK_0008000 = (1 << 15),
    RENDER_UNK_0010000 = (1 << 16),
    RENDER_UNK_0020000 = (1 << 17),
    RENDER_UNK_0040000 = (1 << 18),
    RENDER_UNK_0080000 = (1 << 19),
    RENDER_UNK_0100000 = (1 << 20),
    RENDER_UNK_0200000 = (1 << 21),
    RENDER_UNK_0400000 = (1 << 22),
    RENDER_UNK_0800000 = (1 << 23),
    RENDER_UNK_1000000 = (1 << 24),
    RENDER_UNK_2000000 = (1 << 25),
    RENDER_UNK_4000000 = (1 << 26),
    RENDER_UNK_8000000 = (1 << 27),
};

extern u32 gTexColourTag;
extern s32 D_800DE7C4;

extern Gfx D_800DF1A8[32][2];
extern Gfx *gSceneCurrDisplayList;
extern s32 D_8011B0FC;
extern u32 D_8011D384;
extern LevelHeader *gCurrentLevelHeader2;
extern s32 gCurrentRenderFlags;
extern TextureHeader *D_8012637C;
extern s16 gForceFlags;
extern Gfx dTextureRectangleModes[];
extern Gfx D_800DE848[2][2];
extern Gfx D_800DE868[8][2];
extern Gfx D_800DE8E8[64][2];
extern s32 D_80126378;
extern s16 D_80126380;
extern Gfx D_800DE7C8[8][2];
extern Gfx D_800DECE8[16][2];
extern Gfx D_800DEDE8[16][2];
extern Gfx D_800DEEE8[4][2];
extern Gfx D_800DEF28[16][2];
extern Gfx D_800DF028[8][2];
extern Gfx D_800DF0A8[16][2];
extern s16 D_80126384;
extern Gfx D_800DF3A8[6];
extern Gfx D_800DF3D8[7];
extern Gfx D_800DF410[3][2];


/* Size: 8 bytes */
typedef struct unk8007F1E8_18 {
    s32 unk0;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
} unk8007F1E8_18;

/* Size: Variable. */
typedef struct unk8007F1E8 {
    s32 unk0;
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
    unk8007F1E8_18 unk18[1]; // Actual length depends on unk0
} unk8007F1E8;

typedef struct TextureCacheEntry {
    s32 id;
    TextureHeader *texture;
} TextureCacheEntry;

typedef struct SpriteCacheEntry {
    s32 id;
    Sprite *sprite;
} SpriteCacheEntry;

/* Size: 0x28 bytes */
typedef struct TempTexHeader {
/* 0x00 */ TextureHeader header;
/* 0x20 */ u32 uncompressedSize; // Little endian
/* 0x24 */ u8 gzipLevel; // Always 9.
/* 0x25 */ u8 pad25[3]; // padding
} TempTexHeader;

void tex_disable_modes(s32 flags);
void tex_enable_modes(s32 flags);
s32 func_8007AE44(void);
s32 func_8007AE54(void);
s32 func_8007AE64(void);
void set_texture_colour_tag(s32 tagID);
void reset_render_settings(Gfx **dlist);
void func_8007B43C(void);
void func_8007B454(void);
void load_and_set_texture_no_offset(Gfx **dlist, TextureHeader *texhead, u32 flags);
void func_8007BF1C(s32 arg0);
s32 func_8007EF64(s16 arg0);
void load_and_set_texture(Gfx **dlist, TextureHeader *texhead, s32 flags, s32 offset);

// There might be a file boundary here.
void tex_animate_texture(TextureHeader *texture, u32 *triangleBatchInfoFlags, s32 *arg2, s32 updateRate);
void func_8007F1E8(unk8007F1E8 *arg0);
void init_pulsating_light_data(PulsatingLightData *data);
void update_pulsating_light_data(PulsatingLightData *data, s32 timeDelta);

TextureHeader *load_texture(s32 arg0); // Non Matching
void free_texture(TextureHeader *tex); // Non Matching
TextureHeader *func_8007B380(s32 arg0); // Non Matching
s32 get_texture_size_from_id(s32 arg0); // Non Matching
s32 func_8007C860(s32 spriteIndex); // Non Matching
s32 load_sprite_info(s32 spriteID, s32 *numOfInstancesOut, s32 *unkOut,
	s32 *numFramesOut, s32 *formatOut, s32 *sizeOut); // Non Matching
void free_sprite(Sprite *sprite); // Non Matching
void func_8007F594(Gfx **dlist, u32 index, u32 primitiveColor, u32 environmentColor); // Non Matching
void func_8007CA68(s32 spriteID, s32 arg1, s32 *arg2, s32 *arg3, s32 *arg4); // Non Matching
MemoryPoolSlot *func_8007C12C(s32 spriteID, s32 arg1); // Non Matching
void tex_init_textures(void); // Non Matching
void func_8007BF34(Gfx **dlist, s32 arg1); // Non Matching
void load_blinking_lights_texture(Gfx **dlist, TextureHeader *arg1, u32 flags, s32 arg3); // Non Matching
void build_tex_display_list(TextureHeader *tex, Gfx *dlist); //Non Matching

#endif
