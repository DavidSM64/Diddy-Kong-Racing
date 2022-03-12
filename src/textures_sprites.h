#ifndef _TEXTURES_SPRITES_H_
#define _TEXTURES_SPRITES_H_

#include "asset_sections.h"
#include "types.h"
#include "f3ddkr.h"
#include "structs.h"
#include "macros.h"
#include "memory.h"

extern u32 gTexColourTag;
extern s32 D_800DE7C4;

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

typedef struct Sprite {
    s16 baseTextureId;
    s16 numberOfFrames; // 1 means static texture
    s16 numberOfInstances;
    s16 unk6;
    TextureHeader **frames;
    u8 unkC[1]; // Actual size varies.
} Sprite;

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

s32 get_random_number_from_range(s32, s32); //?

void func_8007AE0C(s32 arg0);
void func_8007AE28(s32 arg0);
s32 func_8007AE44(void);
s32 func_8007AE54(void);
s32 func_8007AE64(void);
void func_8007B374(s32 arg0);
void func_8007B3D0(Gfx **dlist);
void func_8007B43C(void);
void func_8007B454(void);
void func_8007B4C8(s32 arg0, s32 arg1, s32 arg2);
void func_8007BF1C(s32 arg0);
s32 func_8007EF64(s16 arg0);

// There might be a file boundary here.
void func_8007EF80(TextureHeader *texture, u32 *triangleBatchInfoFlags, s32 *arg2, s32 arg3);
void func_8007F1E8(unk8007F1E8 *arg0);
void init_pulsating_light_data(PulsatingLightData *data);
void update_pulsating_light_data(PulsatingLightData *data, s32 timeDelta);

TextureHeader *load_texture(s32 arg0); // Non Matching
void free_texture(TextureHeader *tex); // Non Matching
TextureHeader *func_8007B380(s32 arg0); // Non Matching
void func_8007B4E8(s32, s32, s32, s32); // Non Matching
s32 get_texture_size_from_id(s32 arg0); // Non Matching
s32 func_8007C860(s32 spriteIndex); // Non Matching
s32 load_sprite_info(s32 spriteIndex, s32 *numOfInstancesOut, s32 *unkOut,
	s32 *numFramesOut, s32 *formatOut, s32 *sizeOut); // Non Matching
void free_sprite(Sprite *sprite); // Non Matching
void func_8007F594(Gfx **dlist, u32 index, u32 primitiveColor, u32 environmentColor); // Non Matching
void func_8007CA68(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3, s32 *arg4); // Non Matching
MemoryPoolSlot *func_8007C12C(s32 arg0, s32 arg1); // Non Matching
void func_8007AC70(void); // Non Matching

#endif
