#ifndef _UNKNOWN_005740_H_
#define _UNKNOWN_005740_H_

#include "types.h"
#include "structs.h"
#include "audio.h"

/* Size: 0x24 / 36 bytes */
typedef struct unk80119C50 {
    /* 0x00 */ f32 x, y, z;
    /* 0x0C */ u16 soundId;
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u32 *soundMask;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 unk21;
    /* 0x22 */ u8 unk22;
} unk80119C50;


/* Size: 0x180 / 384 bytes */
typedef struct unk80119C58 {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 pad1[0x16A];
    /* 0x16C */ s32 unk16C;
    /* 0x170 */ u8 pad170[0x008];
    /* 0x178 */ s32 unk178;
    /* 0x17C */ s8 unk17C;
    /* 0x17D */ u8 pad17D[0x003];
} unk80119C58;


extern u8 D_800DC6D0;
extern s32 D_800DC6D4;
extern s32 D_800DC6D8;
extern s32 D_800DC6DC;
extern u16 D_800DC6E0;
extern unk80119C50 **D_80119C48;
extern unk80119C50 **D_80119C44;
extern unk80119C50 **D_80119C50;
extern u8 D_80119C4C;
extern unk80119C58 *D_80119C58;


void func_800050D0(Object* obj, u32 buttonsPressed, u32 carInput, s32 updateRate);        /* extern */

f32 func_80007FA4(f32 arg0);
void func_80006AC8(Object *);
s32 func_80004B40(s8, s8);

#endif
