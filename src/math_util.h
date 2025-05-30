#ifndef MATH_UTIL_H
#define MATH_UTIL_H

#include "types.h"
#include "structs.h"
#include "memory.h"

typedef struct RPYAngles {
    s16 z_rotation;
    s16 x_rotation;
    s16 y_rotation;
} RPYAngles;

/**
 * Keeps the value within the range.
 */
#define CLAMP(x, low, high) {       \
    if ((x) > (high)) (x) = (high); \
    if ((x) < (low)) (x) = (low);   \
}

/**
 * Allows an arbitrary range the number can wrap around.
 * Often used for angles, to keep them within s16 bounds while stored in an s32.
 */
#define WRAP(x, low, high) {                    \
    if ((x) > (high)) (x) -= ((high) * 2) - 1;  \
    if ((x) < (low)) (x) += ((high) * 2) - 1;   \
}
// Returning s16 causes good compilers to optimise out parts of the resultant, causing bugs. They most likely intended u16, since that fixes every single one.
#ifdef AVOID_UB
u16 arctan2_f(f32 y, f32 x);
#else
s16 arctan2_f(f32 y, f32 x);
#endif
f32 coss_f(s16 angle);
f32 sins_f(s16 angle);
s32 coss_s16(s16 angle);
s32 sins_s16(s16 angle);
s32 sins_2(s16 angle);
void set_rng_seed(s32 num);
void save_rng_seed(void);
void load_rng_seed(void);
s32 get_rng_seed(void);
s32 rand_range(s32, s32);
void mtxf_to_mtxs(MtxF *mf, MtxS *mi);
void mtxf_transform_point(MtxF *mf, float x, float y, float z, float *ox, float *oy, float *oz);
void mtxf_transform_dir(MtxF *mf, Vec3f *in, Vec3f *out);
void mtxf_mul(MtxF *mat1, MtxF *mat2, MtxF *output);
void mtxf_to_mtx(MtxF *input, Mtx *output);
void vec3s_reflect(Vec3s *vec, Vec3s *n);
void mtxs_transform_dir(MtxS *input, Vec3s *output);
void mtxf_from_transform(MtxF *mtx, ObjectTransform *trans);
void mtxf_scale_y(MtxF *input, f32 scale);
void mtxf_translate_y(MtxF *input, f32 offset);
void mtxf_from_inverse_transform(MtxF *mtx, ObjectTransform *trans);
void mtxf_billboard(MtxF *mtx, s32 angle, f32 scale, f32 scaleY);
void vec3s_rotate_rpy(RPYAngles *rotation, Vec3s *vec3Arg);
void vec3f_rotate(Vec3s *rotation, Vec3f *vec);
void vec3f_rotate_ypr(Vec3s *rotation, Vec3f *vec);
void vec3f_rotate_py(Vec3s *rotation, Vec3f *vec);
s32 tri2d_xz_contains_point(s32 x, s32 z, Vec3s *vec3A, Vec3s *vec3B, Vec3s *vec3C);
void mtxf_from_translation(MtxF *mtx, f32 x, f32 y, f32 z);
void mtxf_from_scale(MtxF *mtx, f32 scaleX, f32 scaleY, f32 scaleZ);
s32 atan2s(s32 xDelta, s32 zDelta);
f32 area_triangle_2d(f32 x0, f32 z0, f32 x1, f32 z1, f32 x2, f32 z2);
void dmacopy_doubleword(void *src, void *dst, s32 end);
StackInfo *stack_pointer(void);
/**
 * Zero out the interrupt mask. This stops this thread
 * from being interrupted by others, letting you safely
 * work with delicate areas in memory. Kind of like a mutex.
 * Returns what the interrupt mask wask before.
 * Official Name: disableInterrupts */
u32 interrupts_disable(void);
/**
 * Set the interrupt mask to whichever flags were given.
 * Required after zeroing them out, otherwise system
 * operation won't work as normal.
 * Official Name: enableInterrupts */
void interrupts_enable(u32 flags);

#endif // MATH_UTIL_H
