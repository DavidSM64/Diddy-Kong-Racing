/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8006F510 */

#include "math_util.h"

#include <math.h>
#include "types.h"
#include "macros.h"
#include "structs.h"
#include "game.h"
#include "string.h"

extern s32 gIntDisFlag;
extern s32 gCurrentRNGSeed; // Official Name: rngSeed
extern s32 gPrevRNGSeed;
extern s16 gSineTable[];
extern s16 gArcTanTable[];

/**
 * Most files below are handwritten assembly. Because of this, matching C code is impossible.
 * Nonmatching is not, so functionally equivalent C code can be here to replace these handwritten functions in
 * nonmatching builds. Variables cannot be declared here because of the way they're aligned, so they have to stay in an
 * assembly file.
 */

/******************************/

#ifdef NON_MATCHING
/**
 * Zero out the interrupt mask. This stops this thread
 * from being interrupted by others, letting you safely
 * work with delicate areas in memory. Kind of like a mutex.
 * Returns what the interrupt mask wask before.
 * Official Name: disableInterrupts */
u32 interrupts_disable(void) {
    if (gIntDisFlag) {
        return __osDisableInt();
    }
}
#else
GLOBAL_ASM("asm/math_util/disable_interrupts.s")
#endif

#ifdef NON_MATCHING
/**
 * Set the interrupt mask to whichever flags were given.
 * Required after zeroing them out, otherwise system
 * operation won't work as normal.
 * Official Name: enableInterrupts */
void interrupts_enable(u32 flags) {
    if (gIntDisFlag) {
        __osRestoreInt(flags);
    }
}
#else
GLOBAL_ASM("asm/math_util/enable_interrupts.s")
#endif

#ifdef NON_MATCHING
/* Official Name: setIntDisFlag */
void set_gIntDisFlag(s8 setting) {
    gIntDisFlag = setting;
}
#else
GLOBAL_ASM("asm/math_util/set_gIntDisFlag.s")
#endif

#ifdef NON_MATCHING
/* Official Name: getIntDisFlag */
s8 get_gIntDisFlag(void) {
    return gIntDisFlag;
}
#else
GLOBAL_ASM("asm/math_util/get_gIntDisFlag.s")
#endif

#ifdef NON_EQUIVALENT // Untested
UNUSED void s32_matrix_to_s16_matrix(s32 **input, s16 **output) {
    s32 i;
    for (i = 0; i < 4; i++) {
        output[i][2] = input[i][0];
        output[i][3] = input[i + 4][0];
        output[i][6] = input[i][1];
        output[i][7] = input[i + 4][1];
        output[i][0] = input[i][0] >> 16;
        output[i][1] = input[i + 4][0] >> 16;
        output[i][4] = input[i][1] >> 16;
        output[i][5] = input[i + 4][1] >> 16;
    }
}
#else
GLOBAL_ASM("asm/math_util/s32_matrix_to_s16_matrix.s")
#endif

#ifdef NON_MATCHING
void f32_matrix_to_s32_matrix(Matrix *input, MatrixS *output) {
    s32 i;
    for (i = 0; i < 4; i++) {
        (*output)[i][0] = (s32) ((*input)[i][0] * 65536.0f);
        (*output)[i][1] = (s32) ((*input)[i][1] * 65536.0f);
        (*output)[i][2] = (s32) ((*input)[i][2] * 65536.0f);
        (*output)[i][3] = (s32) ((*input)[i][3] * 65536.0f);
    }
}
#else
GLOBAL_ASM("asm/math_util/f32_matrix_to_s32_matrix.s")
#endif

#ifdef NON_MATCHING
/* Official name: mathMtxXFMF */
void guMtxXFMF(Matrix mf, float x, float y, float z, float *ox, float *oy, float *oz) {
    *ox = mf[0][0] * x + mf[1][0] * y + mf[2][0] * z + mf[3][0];
    *oy = mf[0][1] * x + mf[1][1] * y + mf[2][1] * z + mf[3][1];
    *oz = mf[0][2] * x + mf[1][2] * y + mf[2][2] * z + mf[3][2];
}
#else
GLOBAL_ASM("asm/math_util/guMtxXFMF.s")
#endif

#ifdef NON_MATCHING
/* Official name: mathMtxFastXFMF */
void f32_matrix_dot(Matrix *mat1, Matrix *mat2, Matrix *output) {
    f32 temp_f4;
    f32 temp_f6;
    f32 temp_f8;

    temp_f4 = (*mat2)[0][0];
    temp_f6 = (*mat2)[0][1];
    temp_f8 = (*mat2)[0][2];
    (*output)[0][0] = (temp_f4 * (*mat1)[0][0]) + (temp_f6 * (*mat1)[1][0]) + (temp_f8 * (*mat1)[2][0]);
    (*output)[0][1] = (temp_f4 * (*mat1)[0][1]) + (temp_f6 * (*mat1)[1][1]) + (temp_f8 * (*mat1)[2][1]);
    (*output)[0][2] = (temp_f4 * (*mat1)[0][2]) + (temp_f6 * (*mat1)[1][2]) + (temp_f8 * (*mat1)[2][2]);
}
#else
GLOBAL_ASM("asm/math_util/f32_matrix_dot.s")
#endif

#ifdef NON_MATCHING
/* Official name: mathMtxCatF */
void f32_matrix_mult(Matrix *mat1, Matrix *mat2, Matrix *output) {
    s32 i;
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    for (i = 0; i < 4; i++) {
        x = (*mat1)[i][0];
        y = (*mat1)[i][1];
        z = (*mat1)[i][2];
        w = (*mat1)[i][3];
        (*output)[i][0] =
            (f32) ((y * (*mat2)[1][0]) + (z * (*mat2)[2][0]) + ((x * (*mat2)[0][0]) + (w * (*mat2)[3][0])));
        (*output)[i][1] =
            (f32) ((y * (*mat2)[1][1]) + (z * (*mat2)[2][1]) + ((x * (*mat2)[0][1]) + (w * (*mat2)[3][1])));
        (*output)[i][2] =
            (f32) ((y * (*mat2)[1][2]) + (z * (*mat2)[2][2]) + ((x * (*mat2)[0][2]) + (w * (*mat2)[3][2])));
        (*output)[i][3] =
            (f32) ((y * (*mat2)[1][3]) + (z * (*mat2)[2][3]) + ((x * (*mat2)[0][3]) + (w * (*mat2)[3][3])));
    }
}
#else
GLOBAL_ASM("asm/math_util/f32_matrix_mult.s")
#endif

#ifdef NON_MATCHING
/* Official name: mathMtxF2L */
void f32_matrix_to_s16_matrix(Matrix *input, MatrixS *output) {
    guMtxF2L((float(*)[4]) input, (Mtx *) output);
}
#else
GLOBAL_ASM("asm/math_util/f32_matrix_to_s16_matrix.s")
#endif

/* Official Name: mathSeed */
void set_rng_seed(s32 num) {
    gCurrentRNGSeed = num;
}

#ifdef NON_MATCHING
void save_rng_seed(void) {
    s32 num = gCurrentRNGSeed;
    gPrevRNGSeed = num;
}
#else
GLOBAL_ASM("asm/math_util/save_rng_seed.s")
#endif

#ifdef NON_MATCHING
void load_rng_seed(void) {
    s32 num = gPrevRNGSeed;
    gCurrentRNGSeed = num;
}
#else
GLOBAL_ASM("asm/math_util/load_rng_seed.s")
#endif

s32 get_rng_seed(void) {
    return gCurrentRNGSeed;
}

#ifdef NON_MATCHING
/* Official Name: mathRnd */
s32 get_random_number_from_range(s32 min, s32 max) {
    s32 newSeed;
    u64 curSeed;

    curSeed = (((u64) ((s64) gCurrentRNGSeed << 0x3F) >> 0x1F) | ((u64) ((s64) gCurrentRNGSeed << 0x1F) >> 0x20)) ^
              ((u64) ((s64) gCurrentRNGSeed << 0x2C) >> 0x20);
    newSeed = ((curSeed >> 0x14) & 0xFFF) ^ curSeed;
    gCurrentRNGSeed = newSeed;
    return ((u32) (newSeed - min) % (u32) ((max - min) + 1)) + min;
}
#else
GLOBAL_ASM("asm/math_util/rng.s")
#endif

#ifdef NON_EQUIVALENT
/* Official name: fastShortReflection */
void s16_matrix_rotate(s16 *arg0[4][4], s16 arg1[4][4]) {
    s32 temp_t6;

    temp_t6 = (s32) ((*arg0[0][0] * arg1[0][0]) + (*arg0[0][1] * arg1[0][1]) + (*arg0[0][2] * *arg0[0][2])) >> 12;
    *arg0[1][0] = (s16) (((s32) (temp_t6 * arg1[0][0]) >> 13) - *arg0[0][0]);
    *arg0[1][1] = (s16) (((s32) (temp_t6 * arg1[0][1]) >> 13) - *arg0[0][1]);
    *arg0[1][2] =
        (s16) (((s32) (temp_t6 * arg1[0][2]) >> 13) - *arg0[0][0]); // Did they mean to do `- *arg0[0][2]` here?
}
#else
GLOBAL_ASM("asm/math_util/s16_matrix_rotate.s")
#endif

#ifdef NON_EQUIVALENT // Untested
UNUSED void s16_matrix_to_s32_matrix(s16 **arg0, s32 **arg1) {
    s32 i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            arg1[i][j] = (arg0[i][j] << 16) | arg0[i + 4][j];
        }
    }
}
#else
GLOBAL_ASM("asm/math_util/s16_matrix_to_s32_matrix.s")
#endif

#ifdef NON_EQUIVALENT // Untested
UNUSED void s16_vec3_mult_by_s32_matrix_full(s32 **input, s16 *output) {
    output[0] = ((output[0] * input[0][0]) + (output[1] * input[1][0]) + (output[2] * input[2][0]) + input[3][0]) >> 16;
    output[1] = ((output[0] * input[0][1]) + (output[1] * input[1][1]) + (output[2] * input[2][1]) + input[3][1]) >> 16;
    output[2] = ((output[0] * input[0][2]) + (output[1] * input[1][2]) + (output[2] * input[2][2]) + input[3][2]) >> 16;
}
#else
GLOBAL_ASM("asm/math_util/s16_vec3_mult_by_s32_matrix_full.s")
#endif

#ifdef NON_MATCHING
void s16_vec3_mult_by_s32_matrix(MatrixS input, Vec3s *output) {
    s32 x;
    s32 y;
    s32 z;

    x = output->x;
    y = output->y;
    z = output->z;
    output->x = ((x * input[0][0]) + (y * input[1][0]) + (z * input[2][0])) >> 16;
    output->y = ((x * input[0][1]) + (y * input[1][1]) + (z * input[2][1])) >> 16;
    output->z = ((x * input[0][2]) + (y * input[1][2]) + (z * input[2][2])) >> 16;
}
#else
GLOBAL_ASM("asm/math_util/s16_vec3_mult_by_s32_matrix.s")
#endif

#ifdef NON_EQUIVALENT
void object_transform_to_matrix(Matrix mtx, ObjectTransform *trans) {
    f32 yRotSine;
    f32 yRotCosine;
    f32 xRotSine;
    f32 xRotCosine;
    f32 zRotSine;
    f32 zRotCosine;
    f32 scale;

    yRotSine = sins(trans->y_rotation) * 0.000015f;
    yRotCosine = coss(trans->y_rotation) * 0.000015f;
    xRotSine = sins(trans->x_rotation) * 0.000015f;
    xRotCosine = coss(trans->x_rotation) * 0.000015f;
    zRotSine = sins(trans->z_rotation) * 0.000015f;
    zRotCosine = coss(trans->z_rotation) * 0.000015f;
    scale = trans->scale * 0.000015f;

    mtx[0][0] = ((xRotSine * yRotSine * zRotSine) + (scale * yRotCosine)) * scale;
    mtx[0][1] = (zRotSine * xRotCosine * scale);
    mtx[0][2] = (((xRotSine * yRotCosine * zRotSine) - (scale * yRotSine)) * scale);
    mtx[0][3] = 0;
    mtx[1][0] = (((xRotSine * yRotSine * scale) - (zRotSine * yRotCosine)) * scale);
    mtx[1][1] = (scale * xRotCosine * scale);
    mtx[1][2] = (((xRotSine * yRotCosine * scale) + (zRotSine * yRotSine)) * scale);
    mtx[1][3] = 0;
    mtx[2][0] = (xRotCosine * yRotSine * scale);
    mtx[2][1] = -(xRotSine * scale);
    mtx[2][2] = (xRotCosine * yRotCosine * scale);
    mtx[2][3] = 0;
    mtx[3][0] = trans->x_position;
    mtx[3][1] = trans->y_position;
    mtx[3][2] = 1.0f;
    mtx[3][3] = trans->z_position;
}
#else
GLOBAL_ASM("asm/math_util/object_transform_to_matrix.s")
#endif

#ifdef NON_MATCHING
/* Official name: mathSquashY */
void f32_matrix_scale(Matrix *input, f32 scale) {
    input[0][1][0] *= scale;
    input[0][1][1] *= scale;
    input[0][1][2] *= scale;
}
#else
GLOBAL_ASM("asm/math_util/f32_matrix_scale.s")
#endif

#ifdef NON_MATCHING
/* Official name: mathTransY */
void f32_matrix_y_scale(Matrix *input, f32 scale) {
    input[0][3][0] += input[0][1][0] * scale;
    input[0][3][1] += input[0][1][1] * scale;
    input[0][3][2] += input[0][1][2] * scale;
}
#else
GLOBAL_ASM("asm/math_util/f32_matrix_y_scale.s")
#endif

#ifdef NON_EQUIVALENT
void object_transform_to_matrix_2(Matrix mtx, ObjectTransform *trans) {
    f32 yRotSine;
    f32 yRotCosine;
    f32 xRotSine;
    f32 xRotCosine;
    f32 zRotSine;
    f32 zRotCosine;
    f32 scale;

    yRotCosine = coss(trans->y_rotation) * 0.000015f;
    yRotSine = sins(trans->y_rotation) * 0.000015f;
    xRotCosine = coss(trans->x_rotation) * 0.000015f;
    xRotSine = sins(trans->x_rotation) * 0.000015f;
    zRotCosine = coss(trans->z_rotation) * 0.000015f;
    zRotSine = sins(trans->z_rotation) * 0.000015f;

    scale = trans->scale * 0.000015f;

    mtx[0][0] = (yRotSine * scale) - (xRotCosine * zRotCosine * yRotCosine);
    mtx[0][1] = (xRotCosine * scale * yRotCosine) + (yRotSine * zRotCosine);
    mtx[0][2] = -(yRotCosine * xRotSine);
    mtx[0][3] = 0;
    mtx[1][0] = -(xRotSine * zRotCosine);
    mtx[1][1] = xRotSine * scale;
    mtx[1][2] = xRotCosine;
    mtx[1][3] = 0;
    mtx[2][0] = (xRotCosine * zRotCosine * yRotSine) + (yRotCosine * scale);
    mtx[2][1] = (yRotCosine * zRotCosine) - (xRotCosine * scale * yRotSine);
    mtx[2][2] = yRotSine * xRotSine;
    mtx[2][3] = 0;
    mtx[3][0] = (mtx[0][0] * trans->x_position) + (mtx[1][0] * trans->y_position) + (mtx[2][0] * trans->z_position);
    mtx[3][1] = (mtx[0][1] * trans->x_position) + (mtx[1][1] * trans->y_position) + (mtx[2][1] * trans->z_position);
    mtx[3][2] = (mtx[0][2] * trans->x_position) + (mtx[1][2] * trans->y_position) + (mtx[2][2] * trans->z_position);
    mtx[3][3] = 1.0f;
}
#else
GLOBAL_ASM("asm/math_util/object_transform_to_matrix_2.s")
#endif

GLOBAL_ASM("asm/math_util/func_80070058.s")

#ifdef NON_MATCHING
void f32_matrix_from_rotation_and_scale(Matrix mtx, s32 angle, f32 arg2, f32 arg3) {
    f32 cosine, sine;

    cosine = sins(angle) * 0.000015f;
    sine = coss(angle) * 0.000015f;
    mtx[0][0] = sine * arg2;
    mtx[0][1] = cosine * arg2;
    mtx[0][2] = 0;
    mtx[0][3] = 0;
    mtx[1][0] = -cosine * arg2;
    mtx[1][1] = (sine * arg2) * arg3;
    mtx[1][2] = 0;
    mtx[1][3] = 0;
    mtx[2][0] = 0;
    mtx[2][1] = 0;
    mtx[2][2] = arg2;
    mtx[2][3] = 0;
    mtx[3][0] = 0;
    mtx[3][1] = 0;
    mtx[3][2] = 0;
    mtx[3][3] = 1.0f;
}
#else
GLOBAL_ASM("asm/math_util/f32_matrix_from_rotation_and_scale.s")
#endif

#ifdef NON_EQUIVALENT
void s16_vec3_apply_object_rotation(ObjectTransform *trans, s16 *vec3Arg) {
    s32 yRotSine;
    s32 yRotCosine;
    s32 xRotSine;
    s32 xRotCosine;
    s32 zRotSine;
    s32 zRotCosine;
    s32 temp_t3;
    s32 temp_t4;
    s32 temp_t5;

    yRotCosine = coss(trans->y_rotation);
    yRotSine = sins(trans->y_rotation);
    xRotCosine = coss(trans->x_rotation);
    xRotSine = sins(trans->x_rotation);
    zRotCosine = coss(trans->z_rotation);
    zRotSine = sins(trans->z_rotation);

    temp_t3 = ((vec3Arg[0] * yRotSine) - (vec3Arg[1] * yRotCosine)) >> 16;
    temp_t4 = ((vec3Arg[1] * yRotSine) + (vec3Arg[0] * yRotCosine)) >> 16;

    temp_t4 = ((temp_t4 * xRotSine) - (vec3Arg[2] * xRotCosine)) >> 16;
    temp_t5 = ((vec3Arg[2] * xRotSine) + (temp_t4 * xRotCosine)) >> 16;

    vec3Arg[1] = temp_t4;

    temp_t3 = ((temp_t3 * zRotSine) + (temp_t5 * zRotCosine)) >> 16;
    temp_t5 = ((temp_t5 * zRotSine) - (temp_t3 * zRotCosine)) >> 16;

    vec3Arg[0] = temp_t3;
    vec3Arg[2] = temp_t5;
}
#else
GLOBAL_ASM("asm/math_util/s16_vec3_apply_object_rotation.s")
#endif

#ifdef NON_EQUIVALENT
/* Official Name: mathOneFloatRPY */
void f32_vec3_apply_object_rotation(ObjectTransform *trans, f32 *vec3_f32) {
    f32 yRotSine;
    f32 yRotCosine;
    f32 xRotSine;
    f32 xRotCosine;
    f32 zRotSine;
    f32 zRotCosine;
    f32 x, y, z;
    f32 temp;

    zRotSine = sinf(trans->z_rotation);
    zRotCosine = cosf(trans->z_rotation);
    xRotSine = sinf(trans->x_rotation);
    xRotCosine = cosf(trans->x_rotation);
    yRotSine = sinf(trans->y_rotation);
    yRotCosine = cosf(trans->y_rotation);

    x = vec3_f32[0];
    y = vec3_f32[1];
    z = vec3_f32[2];

    x = (vec3_f32[0] * zRotCosine) - (vec3_f32[1] * zRotSine);
    y = (vec3_f32[1] * zRotCosine) + (vec3_f32[0] * zRotSine);

    temp = y;
    y = (temp * xRotCosine) - (vec3_f32[2] * xRotSine);
    z = (vec3_f32[2] * xRotCosine) + (temp * xRotSine);

    temp = x;
    x = (temp * yRotCosine) + (z * yRotSine);
    z = (z * yRotCosine) - (temp * yRotSine);

    vec3_f32[0] = x;
    vec3_f32[1] = y;
    vec3_f32[2] = z;
}
#else
GLOBAL_ASM("asm/math_util/f32_vec3_apply_object_rotation.s")
#endif

#ifdef NON_EQUIVALENT
/* Official Name: mathOneFloatYPR */
void f32_vec3_apply_object_rotation2(ObjectTransform *trans, f32 *arg1) {
    f32 yRotSine;
    f32 yRotCosine;
    f32 xRotSine;
    f32 xRotCosine;
    f32 zRotSine;
    f32 zRotCosine;
    f32 temp_f4;
    f32 temp_f6;
    f32 temp_f8;

    xRotSine = sinf(trans->x_rotation);
    xRotCosine = cosf(trans->x_rotation);
    yRotSine = sinf(trans->y_rotation);
    yRotCosine = cosf(trans->y_rotation);
    zRotCosine = cosf(trans->z_rotation);
    zRotSine = sinf(trans->z_rotation);

    temp_f4 = (arg1[0] * xRotSine) + (arg1[2] * xRotCosine);
    temp_f8 = (arg1[2] * xRotSine) - (arg1[0] * xRotCosine);

    temp_f6 = (arg1[1] * yRotSine) - (temp_f8 * yRotCosine);
    temp_f8 = (temp_f8 * yRotSine) + (arg1[1] * yRotCosine);

    arg1[2] = temp_f8;

    temp_f4 = (temp_f4 * zRotSine) - (temp_f6 * zRotCosine);
    temp_f6 = (temp_f6 * zRotSine) + (temp_f4 * zRotCosine);

    arg1[0] = temp_f4;
    arg1[1] = temp_f6;
}
#else
GLOBAL_ASM("asm/math_util/f32_vec3_apply_object_rotation2.s")
#endif

#ifdef NON_EQUIVALENT
/* Official Name: mathOneFloatPY */
void f32_vec3_apply_object_rotation3(ObjectTransform *trans, f32 *vec3_f32) {
    f32 xRotSine;
    f32 xRotCosine;
    f32 yRotSine;
    f32 yRotCosine;
    f32 x, y, z;

    xRotSine = sinf(trans->x_rotation);
    xRotCosine = cosf(trans->x_rotation);
    yRotSine = sinf(trans->y_rotation);
    yRotCosine = cosf(trans->y_rotation);

    z = vec3_f32[2];
    y = -(z * xRotSine);
    z = z * xRotCosine;
    x = (z * yRotSine);
    z = z * yRotCosine;

    vec3_f32[0] = x;
    vec3_f32[1] = y;
    vec3_f32[2] = z;
}
#else
GLOBAL_ASM("asm/math_util/f32_vec3_apply_object_rotation3.s")
#endif

#ifdef NON_MATCHING
s32 point_triangle_2d_xz_intersection(s32 x, s32 z, s16 *vec3A, s16 *vec3B, s16 *vec3C) {
    s32 result;
    s32 aX;
    s32 aZ;
    s32 bX;
    s32 bZ;
    s32 cX;
    s32 cZ;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;

    aX = vec3A[0];
    aZ = vec3A[2];
    bX = vec3B[0];
    bZ = vec3B[2];
    cX = vec3C[0];
    cZ = vec3C[2];
    result = FALSE;
    var_a1 = 1;
    var_a2 = 1;
    var_a3 = 1;
    if ((((x - aX) * (bZ - aZ)) - ((bX - aX) * (z - aZ))) < 0) {
        var_a3 ^= 1;
    }
    if ((((x - bX) * (cZ - bZ)) - ((cX - bX) * (z - bZ))) < 0) {
        var_a2 ^= 1;
    }
    if (var_a3 == var_a2) {
        if ((((x - cX) * (aZ - cZ)) - ((aX - cX) * (z - cZ))) < 0) {
            var_a1 ^= 1;
        }
        if (var_a1 == var_a2) {
            result = TRUE;
        }
    }
    return result;
}
#else
GLOBAL_ASM("asm/math_util/point_triangle_2d_xz_intersection.s")
#endif

#ifdef NON_EQUIVALENT
void f32_matrix_from_position(Matrix *mtx, f32 x, f32 y, f32 z) {
    s32 j;
    s32 i;
    // Clear matrix
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            *mtx[i][j] = 0;
        }
    }
    *mtx[0][0] = 1.0f;
    *mtx[1][1] = 1.0f;
    *mtx[2][2] = 1.0f;
    *mtx[3][3] = 1.0f;
    *mtx[3][0] = x;
    *mtx[3][1] = y;
    *mtx[3][2] = z;
}
#else
GLOBAL_ASM("asm/math_util/f32_matrix_from_position.s")
#endif

GLOBAL_ASM("asm/math_util/f32_matrix_from_scale.s")

#ifdef NON_MATCHING
// Blatantly stolen from SM64 :)
static u16 atan2_lookup(f32 y, f32 x) {
    u16 ret;

    if (x == 0) {
        ret = gArcTanTable[0];
    } else {
        ret = gArcTanTable[(s32) (y / x * 1024 + 0.5f)];
    }
    return ret;
}

s32 atan2s(s32 xDelta, s32 zDelta) {
    u16 ret;

    if (xDelta >= 0) {
        if (zDelta >= 0) {
            if (zDelta >= xDelta) {
                ret = atan2_lookup(xDelta, zDelta);
            } else {
                ret = 0x4000 - atan2_lookup(zDelta, xDelta);
            }
        } else {
            zDelta = -zDelta;
            if (zDelta < xDelta) {
                ret = 0x4000 + atan2_lookup(zDelta, xDelta);
            } else {
                ret = 0x8000 - atan2_lookup(xDelta, zDelta);
            }
        }
    } else {
        xDelta = -xDelta;
        if (zDelta < 0) {
            zDelta = -zDelta;
            if (zDelta >= xDelta) {
                ret = 0x8000 + atan2_lookup(xDelta, zDelta);
            } else {
                ret = 0xC000 - atan2_lookup(zDelta, xDelta);
            }
        } else {
            if (zDelta < xDelta) {
                ret = 0xC000 + atan2_lookup(zDelta, xDelta);
            } else {
                ret = -atan2_lookup(xDelta, zDelta);
            }
        }
    }
    return ret;
}
#else
GLOBAL_ASM("asm/math_util/atan2s.s")
#endif

#ifdef NON_MATCHING
u16 arctan2_f(f32 y, f32 x) {
    return atan2s((s32) (y * 255.0f), (s32) (x * 255.0f));
}
#else
GLOBAL_ASM("asm/math_util/arctan2_f.s")
#endif

#ifdef NON_EQUIVALENT // Untested
UNUSED s32 s32_matrix_cell_sqrt(s32 arg0) {
    return (s32) (sqrtf((f32) arg0 / 65536.0f) * 65536.0f);
}
#else
GLOBAL_ASM("asm/math_util/s32_matrix_cell_sqrt.s")
#endif

#ifdef NON_EQUIVALENT // Untested
UNUSED s32 bad_int_sqrt(s32 arg0) {
    return (s32) (sqrtf((f32) arg0 / 65536.0f) * 65536.0f);
}
#else
GLOBAL_ASM("asm/math_util/bad_int_sqrt.s")
#endif

GLOBAL_ASM("asm/math_util/sins_f.s")
GLOBAL_ASM("asm/math_util/coss_f.s")
GLOBAL_ASM("asm/math_util/coss.s")
GLOBAL_ASM("asm/math_util/sins_2.s")

#ifdef NON_EQUIVALENT // Untested
UNUSED s32 calc_dyn_lighting_for_level_segment(LevelModelSegment *segment, s32 *vec3_ints) {
    s32 dotProduct;
    s32 numVertsInBatch;
    s32 vertCount;
    s32 upperColor;
    s32 alpha;
    s32 numBatches;
    s32 i, j;
    Vertex *verts;
    Vertex *verts2C;
    TriangleBatchInfo *batches;

    numBatches = segment->numberOfBatches;
    batches = segment->batches;
    vertCount = 0;
    for (i = 0; i < numBatches; i++) {
        // batches[i].unk6 is 0xFF if vertex colors are used. Otherwise dynamic lighting is used.
        if ((batches[i].unk6 - 0xFF) != 0) {
            verts = &segment->vertices[vertCount];
            verts2C = &segment->unk2C[vertCount];
            numVertsInBatch = batches[i + 1].verticesOffset - batches[i].verticesOffset;
            for (j = 0; j < numVertsInBatch; j++) {
                alpha = verts2C[j].a;
                dotProduct =
                    (verts2C[j].x * vec3_ints[0]) + (verts2C[j].y * vec3_ints[1]) + (verts2C[j].z * vec3_ints[2]);
                if (dotProduct > 0) {
                    alpha += dotProduct >> 22;
                    if (alpha > 128) {
                        alpha = 128;
                    }
                }
                upperColor = (alpha * (verts2C[j].r | (verts2C[j].g << 16))) >> 7;
                verts[j].r = (s8) upperColor;
                verts[j].g = (s8) (upperColor >> 16);
                verts[j].b = (s8) ((u32) (alpha * verts2C[j].b) >> 7);
            }
            vertCount += numVertsInBatch;
        } else {
            vertCount += batches[i + 1].verticesOffset - batches[i].verticesOffset;
        }
    }
    return vertCount;
}
#else
GLOBAL_ASM("asm/math_util/calc_dyn_lighting_for_level_segment.s")
#endif

#ifdef NON_MATCHING
/**
 * Signed distance field calculation. It's used to calculate the level of intersection between a point and a triangle.
 */
f32 area_triangle_2d(f32 x0, f32 z0, f32 x1, f32 z1, f32 x2, f32 z2) {
    f32 dx0 = x1 - x0;
    f32 dz0 = z1 - z0;
    f32 dx1 = x2 - x1;
    f32 dz1 = z2 - z1;
    f32 dx2 = x0 - x2;
    f32 dz2 = z0 - z2;
    f32 d0 = sqrtf((dx0 * dx0) + (dz0 * dz0)); // Distance between points 0 & 1
    f32 d1 = sqrtf((dx1 * dx1) + (dz1 * dz1)); // Distance between points 1 & 2
    f32 d2 = sqrtf((dx2 * dx2) + (dz2 * dz2)); // Distance between points 2 & 0
    f32 m = 0.5f * (d0 + d1 + d2);             // Half the sum of the distances?
    f32 result = m * (m - d0) * (m - d1) * (m - d2);
    if (result < 0.0f) {
        result = 0.0f;
    }
    return sqrtf(result);
}
#else
GLOBAL_ASM("asm/math_util/area_triangle_2d.s")
#endif

GLOBAL_ASM("asm/math_util/set_breakpoint.s")

#ifdef NON_MATCHING
void dmacopy_doubleword(void *src, void *dst, s32 end) {
    s32 size = end - (u32) dst;
    memcpy(dst, src, size);
}
#else
GLOBAL_ASM("asm/math_util/dmacopy_doubleword.s")
#endif
