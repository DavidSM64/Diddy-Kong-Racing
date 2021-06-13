#ifndef _UNKNOWN_0255E0_H_
#define _UNKNOWN_0255E0_H_

#include "types.h"
#include "structs.h"

/* Size: 0x8 bytes */
typedef struct unknown800DC874 {
    union {
        s8 unk00;
        s32 dummy_force_alignment; // Not sure of a better way to do this.
    };
    u16 unk04;
    s16 unk06;
} unknown800DC874;

extern s32 D_800DC870;
extern unknown800DC874 D_800DC874;
extern unknown800DC874 D_800DC87C;

extern f32 D_800DC884[10];

extern f32 D_800DC8AC[27];

typedef struct{
    u8 pad00[0x12];
    u16 unk12;
    u16 unk14;
} unk800DC918_00_00;

typedef struct{
    unk800DC918_00_00 *unk00;
    u8 pad00[0x04];
} unk800DC918_00;

typedef struct{
    u8 unk00;
    u8 pad01[0x05];
    u8  unk06;
    u8  unk07;
    u32 unk08;  
} unk800DC918_04_0C;

typedef struct{
    u8 pad00[0x0C];
    unk800DC918_04_0C* unk0C;
    u8 pad0C[0x10];
    s16 unk20;
    u8 pad22[0x09];
    s8 unk2B;
    u8 pad2C[0x14];
    u8 unk40;
    u8 pad41[0x3];
} unk800DC918_04;

typedef struct{
    s16 unk00; //sx
    s16 unk02; //sy
    s16 unk04; //sz
    s16 unk06; //lx
    s16 unk08; //ly
    s16 unk0A; //lz
} unk800DC918_08; //bounding box

typedef struct{
    unk800DC918_00 *unk00;
    unk800DC918_04 *unk04;
    unk800DC918_08 *unk08;
    u8 pad0C[0x0E];
    s16 count;
} unk800DC918;

extern unk800DC918* D_800DC918;
extern LevelHeader *D_800DC91C;

extern s32 D_800DC920;
extern s32 D_800DC924;
extern s32 D_800DC928;

extern s8 D_800DC92C[24];

#endif