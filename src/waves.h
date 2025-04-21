#ifndef _WAVES_H_
#define _WAVES_H_

#include "types.h"
#include "structs.h"

/* Size: 4 bytes */
typedef struct {
    u8 unk0[4];
} LevelModelSubArray;

/* Size: 0x1C bytes */
typedef struct {
    LevelModelSegment *unk00;
    s16 unk4; // something with x
    s16 unk6; // something with y AND used as playerIndex
    s16 unk8; // something with z
    u8 unkA; // some sort of x ratio
    u8 unkB; // some sort of z ratio / index of D_8012A0E8
    u32 unkC;
    s16 unk10;
    s16 unk12;
    LevelModelSubArray unk14[2];
} LevelModel_Alternate;

/* Size: 0x40 bytes */
typedef struct unk800E3190 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    u16 unk1A;
    u32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    u8 unk31;
    u8 unk32;
    u8 pad33[0xE];
} unk800E3190;

typedef struct unk800E3184 {
    u8 unk0[8];
} unk800E3184;

typedef struct unk80129FC8 {
    s32 unk0; // count or index?
    s32 unk4; // compared to and substracted
    s32 unk8;
    f32 unkC;
    s32 unk10; // used in sins_f
    s32 unk14;
    f32 unk18;
    s32 unk1C; // used in sins_f
    s32 unk20; // max count of something? Maybe D_800E3040?
    s32 unk24;
    s32 unk28; // some sort of flag? maybe bool?
    s32 unk2C; // something to do with texture? maybe id?
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    f32 magnitude; // Global wave strength
    f32 unk44; // something related to scale?
    f32 unk48;
    s32 unk4C;
} unk80129FC8;

typedef struct unk800BBE08_arg1 {
    u8 pad[0x70];
    s32 unk70[1]; // Unknown length.
} unk800BBE08_arg1;

typedef struct unk800BFC54_arg0 {
    f32 unk0;
    f32 unk4;
    u8 pad8[0x4];
    f32 unkC;
    f32 unk10;
    u8 pad14[0x8];
    u32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
} unk800BFC54_arg0;

typedef struct unk800BF9F8 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 pad14[4];
    u16 unk18;
} unk800BF9F8;

// 4 Vertexes
// Size: 0x28 - 40 bytes/
typedef struct unk8012A028 {
    Vertex vert[4];
    // Vertex vertexA;
    // Vertex vertexB;
    // Vertex vertexC;
    // Vertex vertexD;
} unk8012A028;

// /* Size: 10 bytes */
// typedef struct Vertex {
// /* 0x00 */ s16 x;
// /* 0x02 */ s16 y;
// /* 0x04 */ s16 z;
// /* 0x06 */ u8  r;
// /* 0x07 */ u8  g;
// /* 0x08 */ u8  b;
// /* 0x09 */ u8  a;
// } Vertex;

void free_waves(void);
void func_800B8B8C(void);
s32 func_800B9228(LevelModelSegment *arg0);
void func_800BBDDC(LevelModel *level, LevelHeader *header);
void func_800BFE98(s32 arg0);
void func_800B8134(LevelHeader *header);
void func_800BBE08(LevelModel *level, LevelHeader *arg1);
void obj_loop_wavepower(Object *obj);
void func_800BFC54(unk800BFC54_arg0 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_800BF3E4(Object *obj);
f32 log_wave_height(Object_Log *log, s32 updateRate);
void func_800BA288(s32 arg0, s32 arg1);
void func_800BF9F8(unk800BF9F8 *arg0, f32 arg1, f32 arg2);
unk800E3190 *func_800BF634(Object *obj, f32 xPos, f32 zPos, f32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, s32 arg8);
void wave_init(void);

Object_64 *func_800BE654(s16, f32, f32); // Non Matching
void func_800BBF78(LevelModel *arg0); // Non Matching
f32 func_800BB2F4(s32, f32, f32, Vec3f *);
void func_800B8C04(s32, s32, s32, s32, s32);
void func_800BF524(Object *);
f32 func_800BEFC4(s32, s32, s32);
void func_800BC6C8(void);
void func_800BCC70(LevelModel *arg0);

#endif
