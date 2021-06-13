#ifndef _UNKNOWN_00BC20_H_
#define _UNKNOWN_00BC20_H_

#include "types.h"

/* Size: 0x8 bytes */
typedef struct unknown800DC6F0 {
    union {
        s8 unk00;
        s32 dummy_force_alignment; // Not sure of a better way to do this.
    };
    u16 unk04;
    u16 unk06;
} unknown800DC6F0;

extern unknown800DC6F0 D_800DC6F0;
extern unknown800DC6F0 D_800DC6F8;

extern s32 D_800DC700;
extern s32 D_800DC704;
extern s16 D_800DC708;
extern s32 D_800DC70C;
extern s16 D_800DC710;
extern s32 D_800DC714;
extern s32 D_800DC718;
extern s8 D_800DC71C;
extern s32 D_800DC720;
extern s16 D_800DC724;
extern s16 D_800DC728;
extern s16 D_800DC72C;
extern u8 D_800DC730;
extern s32 D_800DC734;
extern u8 D_800DC738;
extern s8 D_800DC73C;
extern s8 D_800DC740;
extern s8 D_800DC744;
extern s8 D_800DC748;
extern s32 D_800DC74C;
extern s32 D_800DC750;
extern s32 D_800DC754;
extern s32 D_800DC758;
extern s32 D_800DC75C;
extern s32 D_800DC760;
extern s32 D_800DC764;
extern s32 D_800DC768;

extern f32 D_800DC76C[15];

extern u16 D_800DC7A8[8];

extern s16 D_800DC7B8[52];

extern s16 D_800DC820[16];

extern s8 D_800DC840[8];

extern s8 D_800DC848;
extern s32 D_800DC84C[3];
extern s32 D_800DC858;
extern s32 D_800DC85C;

extern u8 D_800DC860;
extern u16 D_800DC864;

#endif