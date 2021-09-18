#ifndef _UNKNOWN_072E50_H_
#define _UNKNOWN_072E50_H_

#include "types.h"
#include "structs.h"

extern s32 *D_800DE440;
extern u8 gN64FontCodes[68];
extern s32 D_800DE488;
extern s32 D_800DE48C;

u8 func_80072250(s32 arg0);
void func_80072298(u8 arg0);
void func_80072708(void);
s32 get_s32_256(void);
s32 get_s32_512(void);
s32 func_80073F5C(s32 arg0, s32 arg1);
s32 func_80074148(s32 arg0, Settings *arg1);
void func_80074AA8(GhostHeader *ghostHeader, s16 characterID, s16 time, s16 nodeCount, u8 *dest);
s32 func_80075AEC(s32 controllerIndex);
s32 func_80075D38(s32 controllerIndex);
s32 func_80075DC4(s32 controllerIndex);
void func_80076164(void);
s32 func_80076194(s32 controllerIndex, s32 *arg1, s32 *arg2);
s32 read_data_from_controller_pak(s32 controllerIndex, s32 fileNum, u8 *data, s32 dataLength);
s32 func_80076AF4(s32 controllerIndex, s32 fileNum);

s32 func_800722E8(s16 arg0); //Non matching
s32 func_800738A4(Settings *arg0, void *arg1); //Non matching
s64 func_8007480C(u64 arg0); //Non matching
s32 func_8007497C(u64 *arg0); //Non matching
s32 func_80074B1C(void); //Non matching
s32 func_800762C8(s32 controllerIndex, s32 fileNum); //Non matching
s32 func_80076924(s32 controllerIndex, s32 arg1, s32 *arg2); //Non matching
s16 func_80074A4C(GhostHeader *ghostHeader); //Non matching

#endif
