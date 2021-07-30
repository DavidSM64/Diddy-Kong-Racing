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

extern LevelModel* D_800DC918;
extern LevelHeader *D_800DC91C;

extern s32 D_800DC920;
extern s32 D_800DC924;
extern s32 D_800DC928;

extern s8 D_800DC92C[24];

#endif