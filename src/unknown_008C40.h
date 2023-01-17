#ifndef _UNKNOWN_008C40_H_
#define _UNKNOWN_008C40_H_

#include "types.h"
#include "libc/math.h"
#include "structs.h"

typedef struct floatXYZVals {
    f32 x1;
    f32 y1;
    f32 z1;
    f32 x2;
    f32 y2;
    f32 z2;
} floatXYZVals;

/* Size: 0x0C / 12 bytes - Possibly just a Vec3f? */
typedef struct unk8011A6D8_04 {
  /* 0x00 */ f32 unk0;
  /* 0x04 */ f32 unk4;
  /* 0x08 */ f32 unk8;
} unk8011A6D8_04;

/* Size: 0xC0 / 192 bytes - Thought it was a LevelHeader, but that didn't match other usages */
typedef struct unk8011A6D8 {
  /* 0x00 */ u8 pad0[0x04];
  /* 0x04 */ unk8011A6D8_04 *unk4;
  /* 0x05 */ u8 pad05[0xB0];
  /* 0xB8 */ s8 unkB8;
  /* 0xB9 */ u8 padB9[0x07];
} unk8011A6D8;

extern unk8011A6D8 D_8011A6D8[];

void func_80008168(void);
void func_800096F8(s32);
void func_80008140(void);
void func_8000974C(u16 soundId, f32 x, f32 y, f32 z, u8 arg4, u8 arg5, u8 arg6, u16 arg7, u8 arg8, u8 arg9, u8 argA, u32 *soundMask);
void play_sound_at_position(u16 soundId, f32 x, f32 y, f32 z, u8 arg4, u32 *soundMask);
//void update_spatial_audio_position(Vec3f *arg0, f32 arg1, f32 arg2, f32 arg3);

s32 func_800092A8(f32 inX, f32 inY, f32 inZ, floatXYZVals *floatXYZ, f32 *outX, f32 *outY, f32 *outZ);
void func_80009968(f32, f32, f32, u8, u8, s32); // Non Matching
void update_spatial_audio_position(s32, f32, f32, f32); //Not accurate, the real one is above but it breaks update_player_racer
void func_8000A2E8(s32); // Non Matching
// Yeah this one seems excessive, and it's Non Matching
void func_800098A4(s32, s32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_80008174(void); // Non Matching
void func_80008040(void); // Non Matching
s32 func_800090C0(f32, f32, s16); // Non Matching
void func_80008438(Object **arg0, s32 numRacers, s32 updateRate); // Non Matching
void func_80006FC8(Object **arg0, s32 numRacers, ObjectSegment *arg2, u8 arg3, s32 updateRate); // Non Matching
void func_80006BFC(Object *arg0, ObjectSegment *arg1, Object *arg2, s32 updateRate); // Non Matching


#endif
