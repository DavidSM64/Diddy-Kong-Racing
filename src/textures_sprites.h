#ifndef _TEXTURES_SPRITES_H_
#define _TEXTURES_SPRITES_H_

#include "asset_enums.h"
#include "types.h"
#include "f3ddkr.h"
#include "structs.h"
#include "macros.h"
#include "memory.h"
#include "libultra_internal.h"

/**
 * First two entries are combine mode.
 * Third entry is othermode high word. (Most importantly, the cycle mode and texture filter settings)
 * Fourth and fifth entries are render modes.
*/
#define DRAW_TABLE_ENTRY(combine1, combine2, cycleMode, renderMode1, renderMode2) { \
    gsDPSetCombineLERP(combine1, combine2), \
    gsDPSetOtherMode(cycleMode, DKR_OML_COMMON | renderMode1 | renderMode2), \
}

/**
 * Diddy Kong Racing sets up many of the rendermode tables with a certain pattern.
 * First two entries are combine mode.
 * Third entry is othermode high word. (Most importantly, the cycle mode and texture filter settings)
 * Fourth and fifth entries are render modes for no AA or ZB
 * Sixth and seventh entries are render modes for for AA, but no ZB
 * Eighth and ninth entries are render modes for for ZB, but no AA
 * Tenth and eleventh entries are render modes for for AA and ZB
*/
#define DRAW_TABLE_GROUP(combine1, combine2, cycleMode, renderMode1, renderMode2, renderMode1AA, rendermode2AA, renderMode1ZB, rendermode2ZB, renderMode1ZBAA, renderMode2ZBAA) \
{gsDPSetCombineLERP(combine1, combine2), gsDPSetOtherMode(cycleMode, DKR_OML_COMMON | renderMode1 | renderMode2), }, \
{gsDPSetCombineLERP(combine1, combine2), gsDPSetOtherMode(cycleMode, DKR_OML_COMMON | renderMode1AA | rendermode2AA), }, \
{gsDPSetCombineLERP(combine1, combine2), gsDPSetOtherMode(cycleMode, DKR_OML_COMMON | renderMode1ZB | rendermode2ZB), }, \
{gsDPSetCombineLERP(combine1, combine2), gsDPSetOtherMode(cycleMode, DKR_OML_COMMON | renderMode1ZBAA | renderMode2ZBAA), }

enum RenderFlags {
    RENDER_NONE,
    RENDER_VEHICLE_PART =       (1 << 0), // Shares a spot with RENDER_ANTI_ALIASING, since TEX_EDGE enforces anti aliasing unconditionally.
    RENDER_ANTI_ALIASING =      (1 << 0), // Smooths the edges to improve visual quality.
    RENDER_Z_COMPARE =          (1 << 1), // Compares depth values with existing geometry to prevent rendering errors.
    RENDER_SEMI_TRANSPARENT =   (1 << 2), // Renders with translucency enabled, blending with existing geometry.
    RENDER_FOG_ACTIVE =         (1 << 3), // Applies fog to the geometry.
    RENDER_CUTOUT =             (1 << 4), // A surface with 1 bit alpha cut out for quick transparency.
    RENDER_COLOUR_INDEX =       (1 << 5), // Enables palleted textures.
    RENDER_CLAMP_X =            (1 << 6), // Prevent texture repeating on the X axis.
    RENDER_CLAMP_Y =            (1 << 7), // Prevent texture repeating on the Y axis.
    RENDER_Z_UPDATE =           (1 << 8), // Updates the depth buffer when rendering.
    RENDER_PRESERVE_COVERAGE =  (1 << 9), // Coverage is used to help smooth the image. This won't write over existing coverage values.
    RENDER_LINE_SWAP =          (1 << 10), // Texture has swapped lines, for speed. Makes the load process slightly different.
    RENDER_DECAL =              (1 << 11), // Projects a surface on existing geometry, taking precedent to not zfight.
    RENDER_UNK_0001000 =        (1 << 12),
    RENDER_UNK_0002000 =        (1 << 13),
    RENDER_UNK_0004000 =        (1 << 14),
    RENDER_UNK_0008000 =        (1 << 15),
    RENDER_UNK_0010000 =        (1 << 16),
    RENDER_UNK_0020000 =        (1 << 17),
    RENDER_UNK_0040000 =        (1 << 18),
    RENDER_UNK_0080000 =        (1 << 19),
    RENDER_UNK_0100000 =        (1 << 20),
    RENDER_UNK_0200000 =        (1 << 21),
    RENDER_UNK_0400000 =        (1 << 22),
    RENDER_UNK_0800000 =        (1 << 23),
    RENDER_UNK_1000000 =        (1 << 24),
    RENDER_UNK_2000000 =        (1 << 25),
    RENDER_UNK_4000000 =        (1 << 26),
    RENDER_VTX_ALPHA   =        (1 << 27),  // Allows use of vertex alpha, disabling fog if necessary.
    RENDER_ALL         =        0xFFFFFFFF
};

typedef enum TransFlags {
    OBJ_FLAGS_NONE,
    OBJ_FLAGS_UNK_0001 =            (1 << 0),
    OBJ_FLAGS_UNK_0002 =            (1 << 1),
    OBJ_FLAGS_UNK_0004 =            (1 << 2),
    OBJ_FLAGS_UNK_0008 =            (1 << 3),
    OBJ_FLAGS_UNK_0010 =            (1 << 4),
    OBJ_FLAGS_DESPAWN_TIME_TRIAL =  (1 << 5),  // Don't show up in time trial.
    OBJ_FLAGS_DESPAWN_MULTIPLAYER = (1 << 6),  // Don't show up in 3/4 player.
    OBJ_FLAGS_UNK_0080 =            (1 << 7),
    OBJ_FLAGS_UNK_0100 =            (1 << 8),
    OBJ_FLAGS_INVIS_PLAYER1 =       (1 << 9),  // Player 1 cannot see this.
    OBJ_FLAGS_INVIS_PLAYER2 =       (1 << 10), // Player 2 cannot see this.
    OBJ_FLAGS_UNK_0800 =            (1 << 11),
    OBJ_FLAGS_SHADOW_ONLY =         (1 << 12), // Still has a shadow, but the model is invisible.
    OBJ_FLAGS_UNK_2000 =            (1 << 13),
    OBJ_FLAGS_INVISIBLE =           (1 << 14), // Invisible, and hidden shadow too.
    OBJ_FLAGS_DEACTIVATED =         (1 << 15)  // Object is invisible and inactive.
} TransFlags;

#define TEX_TABLE_2D 0
#define TEX_TABLE_3D 1

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
s32 get_loaded_2D_textures(void);
s32 get_loaded_3D_textures(void);
s32 func_8007AE64(void);
void set_texture_colour_tag(s32 tagID);
void reset_render_settings(Gfx **dlist);
void enable_primitive_colour(void);
void disable_primitive_colour(void);
void load_and_set_texture_no_offset(Gfx **dlist, TextureHeader *texhead, u32 flags);
void sprite_opaque(s32 setting);
s32 func_8007EF64(s16 arg0);
void load_and_set_texture(Gfx **dlist, TextureHeader *texhead, s32 flags, s32 texOffset);
void free_sprite(Sprite *sprite);
void free_texture(TextureHeader *tex);

// There might be a file boundary here.
void tex_animate_texture(TextureHeader *texture, u32 *triangleBatchInfoFlags, s32 *arg2, s32 updateRate);
void func_8007F1E8(LevelHeader_70 *arg0);
void init_pulsating_light_data(PulsatingLightData *data);
void update_pulsating_light_data(PulsatingLightData *data, s32 timeDelta);
TextureHeader *set_animated_texture_header(TextureHeader *texHead, s32 offset);
TextureHeader *load_texture(s32 arg0); // Non Matching
s32 get_texture_size_from_id(s32 id);  // Non Matching
s32 func_8007C860(s32 spriteIndex); // Non Matching
s32 load_sprite_info(s32 spriteIndex, s32 *numOfInstancesOut, s32 *unkOut, s32 *numFramesOut, s32 *formatOut,
                     s32 *sizeOut);                                                   // Non Matching
void func_8007F594(Gfx **dlist, u32 index, u32 primitiveColor, u32 environmentColor); // Non Matching
void func_8007CA68(s32 spriteID, s32 arg1, s32 *arg2, s32 *arg3, s32 *arg4); // Non Matching
MemoryPoolSlot *func_8007C12C(s32 spriteID, s32 arg1); // Non Matching
void tex_init_textures(void); // Non Matching
void func_8007BF34(Gfx **dlist, s32 arg1); // Non Matching
void load_blinking_lights_texture(Gfx **dlist, TextureHeader *texture_list, u32 flags,
                                  s32 texture_index);        // Non Matching
void build_tex_display_list(TextureHeader *tex, Gfx *dlist); // Non Matching
void func_8007CDC0(Sprite *sprite1, Sprite *sprite2, s32 arg2); // Non Matching

#endif
