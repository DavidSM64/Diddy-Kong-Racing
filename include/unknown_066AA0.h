#ifndef _UNKNOWN_066AA0_H_
#define _UNKNOWN_066AA0_H_

#include "types.h"

extern s32 D_800DD060;

/* Size: 0x34 bytes. */
typedef struct unk800DD064 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
} unk800DD064;

extern unk800DD064 D_800DD064[4];

// Not sure about the typing here
extern s16 D_800DD134[10];

// Not sure about the typing here
extern u16 D_800DD148[160];

extern f32 D_800DD288[6];

extern f32 D_800DD2A0[6];

extern f32 D_800DD2B8[5];

extern f32 D_800DD2CC[11];

extern u8 D_800DD2F8[8];

extern s32 D_800DD300;

extern s16 D_800DD304;

// Remove this when unknown_066AA0 is split.
extern s32 __FILE_BOUNDARY_PADDING[2];

/** File boundary! The following variables belong to the next file when unknown_066AA0 is split **/

extern s8  D_800DD310;
extern s8  D_800DD314;
extern s8  D_800DD318;
extern s32 D_800DD31C;
extern s32 D_800DD320;
extern s32 D_800DD324;
extern s16 D_800DD328;
extern s16 D_800DD32C;

extern s8 D_800DD330;

// Unused? Unsure on pointer type
extern s32 *D_800DD334[6];

// Unused?
extern char gBuildString[40];

extern s8  D_800DD374;
extern s32 D_800DD378;
extern s32 D_800DD37C;
extern s32 D_800DD380;
extern s32 D_800DD384;
extern s32 D_800DD388;
extern s8  D_800DD38C;
extern u8  D_800DD390;
extern s16 D_800DD394;
extern u8  D_800DD398;
extern s32 D_800DD39C;
extern s8  D_800DD3A0;
extern s32 D_800DD3A4;
extern s32 D_800DD3A8;
extern s32 D_800DD3AC;
extern s32 D_800DD3B0;
extern s32 D_800DD3B4;
extern s32 D_800DD3B8;
extern s32 D_800DD3BC;
extern s32 D_800DD3C0;
extern s32 D_800DD3C4;
extern s32 D_800DD3C8;
extern s32 D_800DD3CC;
extern s32 D_800DD3D0;
extern s32 D_800DD3D4;
extern s32 D_800DD3D8;
extern s32 D_800DD3DC;
extern s32 D_800DD3E0;
extern s32 D_800DD3E4;
extern s32 D_800DD3E8;
extern s32 D_800DD3EC;

extern s8  D_800DD3F0;
extern s16 D_800DD3F4[8];
extern s32 D_800DD404;
extern s32 D_800DD408;
extern s32 D_800DD40C;

// Unused? Unsure on pointer type
extern s32 *D_800DD410[3];

// Not sure if this is an array or a struct.
extern s32 D_800DD41C[2];

extern s32 D_800DD424[2];

#endif