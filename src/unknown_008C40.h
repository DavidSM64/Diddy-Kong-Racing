#ifndef _UNKNOWN_008C40_H_
#define _UNKNOWN_008C40_H_

#include "types.h"
#include "math.h"

typedef struct floatXYZVals {
    f32 x1;
    f32 y1;
    f32 z1;
    f32 x2;
    f32 y2;
    f32 z2;
} floatXYZVals;

extern s32 *D_80119C44;
void func_80008168(void);
void func_800096F8(s32);

s32 func_800092A8(f32 inX, f32 inY, f32 inZ, floatXYZVals *floatXYZ, f32 *outX, f32 *outY, f32 *outZ);
void func_80009558(u16, f32 x, f32 y, f32 z, s32, s32 *); // Non Matching
void func_80009968(f32, f32, f32, u8, u8, s32); // Non Matching
void func_800096D8(s32, f32, f32, f32); // Non Matching
void func_8000A2E8(s32); // Non Matching
// Yeah this one seems excessive, and it's Non Matching
void func_800098A4(s32, s32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_80008174(void); // Non Matching
void func_80008040(void); // Non Matching

#endif
