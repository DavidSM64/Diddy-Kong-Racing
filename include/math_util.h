#ifndef MATH_UTIL_H
#define MATH_UTIL_H

#include "types.h"
#include "structs.h"

s16 arctan2_f(f32 y, f32 x);
f32 sine_s(s16 angle);
f32 cosine_s(s16 angle);
void func_80031130(s32, f32*, f32*, s32);
s32 func_80031600(f32*, f32*, s32*, s8*, s32, s32*);

#endif // MATH_UTIL_H
