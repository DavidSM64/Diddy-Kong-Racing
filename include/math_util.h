#ifndef MATH_UTIL_H
#define MATH_UTIL_H

#include "types.h"
#include "structs.h"

/**
 * Keeps the value within the range.
 */
#define CLAMP(x, low, high) {          \
    if ((x) > (high)) (x) = (high);            \
    if ((x) < (low)) (x) = (low);              \
}
/**
 * Allows an arbitrary range the number can wrap around.
 * Often used for angles, to keep them within s16 bounds while stored in an s32.
 */
#define WRAP(x, low, high) {           \
    if ((x) > (high)) (x) -= ((high) * 2) - 1; \
    if ((x) < (low)) (x) += ((high) * 2) - 1;  \
}

s16 arctan2_f(f32 y, f32 x);
f32 sine_s(s16 angle);
f32 cosine_s(s16 angle);
void func_80031130(s32, f32*, f32*, s32);
s32 func_80031600(f32*, f32*, f32*, s8* surface, s32, s32*);
void func_80070130(Matrix, s32, f32, f32);
void func_80070638(Matrix, f32, f32, f32);
void func_8006FE04(Matrix*, f32);
void func_8006FE30(Matrix*, f32);

#endif // MATH_UTIL_H
