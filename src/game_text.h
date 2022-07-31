#ifndef _GAME_TEXT_H_
#define _GAME_TEXT_H_

#include "types.h"
#include "macros.h"
#include "f3ddkr.h"
#include "asset_enums.h"
#include "memory.h"
#include "font.h"
#include "PR/libultra.h"

typedef struct unk8012A7C8 {
    u8 *unk0;
    u8 *unk4;
} unk8012A7C8;

typedef struct unk8012A798 {
    u8 *unk0;
    u8 *unk4;
} unk8012A798;

extern u32 osTvType;

void func_800C29F0(void);
void func_800C2AB4(void);
void func_800C2AF4(s32 arg0);
void func_800C2F1C(s32 arg0);
void func_800C3048(void);
void func_800C30CC(void);
void func_800C3140(s32 arg0);
void func_800C314C(void);
void func_800C3158(s32 arg0, f32 arg1);
s32 func_800C3400(void);
void func_800C3440(s32 arg0);

void func_800C31EC(s32); //Non Matching
s32 func_800C3564(void); //Non Matching
void func_800C2D6C(void); //Non Matching
void func_800C2B00(void); //Non Matching

#endif
