#ifndef _AUDIO_SPATIAL_H_
#define _AUDIO_SPATIAL_H_

#include "types.h"
#include "libc/math.h"
#include "structs.h"
#include "PR/gbi.h"
#include "PR/libaudio.h"

typedef struct floatXYZVals {
    f32 x1;
    f32 y1;
    f32 z1;
    f32 x2;
    f32 y2;
    f32 z2;
} floatXYZVals;

/* Size: 0x180 / 384 bytes */
typedef struct unk80119C58 {
    /* 0x000 */ u8 unk0_02;
    /* 0x000 */ u8 unk0_03;
    /* 0x000 */ u8 unk0_04;
    /* 0x000 */ u8 unk0_05;
    /* 0x004 */ f32 unk4_floats[30 * 3]; // Should be a Vec3f, but that just doesn't match
    /* 0x16C */ s32 soundID;
    /* 0x170 */ s32 unk170;
    /* 0x174 */ u8 unk174;
    /* 0x175 */ u8 unk175;
    /* 0x176 */ u8 unk176;
    /* 0x177 */ u8 unk177;
    /* 0x178 */ SoundHandle soundPtr;
    /* 0x17C */ s8 unk17C;
    /* 0x17D */ u8 unk17D;
    /* 0x17E */ u8 unk17E;
} unk80119C58;

/* Size: 0xC0 / 192 bytes - Thought it was a LevelHeader, but that didn't match other usages */
typedef struct unk8011A6D8 {
  /* 0x00 */ u8 unk0_02;
  /* 0x04 */ f32 unk4_floats[15 * 3];
  /* 0xB8 */ s8 unkB8;
  /* 0xB9 */ u8 padB9[0x03];
  /* 0xBC */ f32 unkBC;
} unk8011A6D8;

void audioline_on(void);
void func_800096F8(SoundMask *);
void audioline_off(void);
void func_8000974C(u16 soundBite, f32 x, f32 y, f32 z, u8 arg4, u8 arg5, u8 volume, u16 distance, u8 arg8, u8 pitch,
                   u8 argA, SoundMask **soundMask);
void play_sound_at_position(u16 soundId, f32 x, f32 y, f32 z, u8 arg4, SoundMask **soundMask);
void func_8000A2E8(s32 arg0);
s32 func_800090C0(f32, f32, s32);
void func_800095E8(u16 soundId, f32 x, f32 y, f32 z, u8 arg4, u8 arg5, f32 pitch, SoundMask **soundMask);
void audioline_ambient_create(u8 arg0, u16 soundId, f32 x, f32 y, f32 z, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u16 arg9,
                              u8 argA, u8 lineID, u8 argC);
s32 func_800099EC(u8 arg0);
void debug_render_line(Gfx **dList, Vertex **verts, Triangle **tris, f32 coords[6], u8 red, u8 green, u8 blue);
void func_80006BFC(Object *obj, ObjectSegment *segment, Object *obj2, s32 updateRate);
void update_spatial_audio_position(SoundMask *soundMask, f32 x, f32 y, f32 z);
s32 func_80009AB4(u8 arg0);
void audioline_init(void);
void audioline_reverb_create(f32, f32, f32, u8, u8, u8);
void audioline_reverb(SoundHandle soundHandle, f32 x, f32 y, f32 z);

s32 audioline_distance(f32 inX, f32 inY, f32 inZ, f32 coords[6], f32 *outX, f32 *outY, f32 *outZ);
void audioline_reset(void);
void func_80008438(Object **objRacers, s32 numRacers, s32 updateRate);                             // Non Matching
void func_80006FC8(Object **objs, s32 numRacers, ObjectSegment *segment, u8 arg3, s32 updateRate); // Non Matching
u8 func_80009D6C(unk8011A6D8 *, f32, f32, f32);

#endif
