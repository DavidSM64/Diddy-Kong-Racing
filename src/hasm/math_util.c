#include "math_util.h"

#include <math.h>
#include "types.h"
#include "macros.h"
#include "structs.h"
#include "game.h"
#include "string.h"
#include "PR/os_internal_reg.h"

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

/**
 * Converts a Mtx (fixed-point matrix with split integer and fractional parts)
 * into a 4×4 matrix of 32-bit signed integers, where each element is in 16.16 fixed-point format.
 */
#ifdef NON_MATCHING
UNUSED void mtx_to_mtxs(Mtx *m, MtxS *mi) {
    s32 i, j;
    s32 ei, ef;
    s32 *ai, *af;

    ai = &m->m[0][0];
    af = &m->m[2][0];

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j += 2) {
            ei = *ai++;
            ef = *af++;
            (*mi)[i][j] = (ei & 0xFFFF0000) | ((ef >> 16) & 0xFFFF);
            (*mi)[i][j + 1] = ((ei & 0xFFFF) << 16) | (ef & 0xFFFF);
        }
    }
}
#else
GLOBAL_ASM("asm/math_util/mtx_to_mtxs.s")
#endif

/**
 * Converts a 4×4 matrix of 32-bit floating-point values into a 4×4 matrix
 * of 32-bit signed fixed-point values in 16.16 format.
 */
#ifdef NON_MATCHING
void mtxf_to_mtxs(MtxF *mf, MtxS *mi) {
    s32 i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            (*mi)[i][j] = FTOFIX32((*mf)[i][j]);
        }
    }
}
#else
GLOBAL_ASM("asm/math_util/mtxf_to_mtxs.s")
#endif

#ifdef NON_MATCHING
/**
 * Transforms a 3D vector using a 4×4 transformation matrix.
 */
/* Official name: mathMtxXFMF */
void mtxf_transform_point(MtxF *mf, float x, float y, float z, float *ox, float *oy, float *oz) {
    *ox = (*mf)[0][0] * x + (*mf)[1][0] * y + (*mf)[2][0] * z + (*mf)[3][0];
    *oy = (*mf)[0][1] * x + (*mf)[1][1] * y + (*mf)[2][1] * z + (*mf)[3][1];
    *oz = (*mf)[0][2] * x + (*mf)[1][2] * y + (*mf)[2][2] * z + (*mf)[3][2];
}
#else
GLOBAL_ASM("asm/math_util/mtxf_transform_point.s")
#endif

#ifdef NON_MATCHING
/**
 * Transforms a direction vector in 3D space using the rotation part of a 4×4 matrix.
 * This function multiplies the input vector by the upper-left 3×3 portion of the matrix mf,
 * ignoring the translation component. It is used for transforming directions, such as normals,
 * rather than points.
 */
/* Official name: mathMtxFastXFMF */
void mtxf_transform_dir(MtxF *mf, Vec3f *in, Vec3f *out) {
    out->f[0] = (in->f[0] * mf[0][0]) + (in->f[1] * mf[1][0]) + (in->f[2] * mf[2][0]);
    out->f[1] = (in->f[0] * mf[0][1]) + (in->f[1] * mf[1][1]) + (in->f[2] * mf[2][1]);
    out->f[2] = (in->f[0] * mf[0][2]) + (in->f[1] * mf[1][2]) + (in->f[2] * mf[2][2]);
}
#else
GLOBAL_ASM("asm/math_util/mtxf_transform_dir.s")
#endif

#ifdef NON_MATCHING
/**
 * Multiplies two 4×4 matrices.
 */
/* Official name: mathMtxCatF */
void mtxf_mul(MtxF *mat1, MtxF *mat2, MtxF *output) {
    s32 i, j, k;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            /*
            (*output)[i][j] = 0.0f;
            for (k = 0; k < 4; k++) {
                (*output)[i][j] += (*mat1)[i][k] * (*mat2)[k][j];
            }
            */
            // Reordered addition to preserve exact bitwise result
            (*output)[i][j] = ((*mat1)[i][1] * (*mat2)[1][j] + (*mat1)[i][2] * (*mat2)[2][j]) +
                              ((*mat1)[i][0] * (*mat2)[0][j] + (*mat1)[i][3] * (*mat2)[3][j]);
        }
    }
}
#else
GLOBAL_ASM("asm/math_util/mtxf_mul.s")
#endif

#ifdef NON_MATCHING
/**
 * Converts a floating-point 4×4 matrix to a Mtx fixed-point matrix.
 */
/* Official name: mathMtxF2L */
void mtxf_to_mtx(MtxF *mf, Mtx *m) {
    s32 i, j;
    s32 e1, e2;
    s32 *ai, *af;

    ai = &m->m[0][0];
    af = &m->m[2][0];

    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j += 2) {
            e1 = FTOFIX32((*mf)[i][j]);
            e2 = FTOFIX32((*mf)[i][j + 1]);
            *ai++ = (e1 & 0xFFFF0000) | ((e2 >> 16) & 0xFFFF);
            *af++ = ((e1 << 16) & 0xFFFF0000) | (e2 & 0xFFFF);
        }
}
}
#else
GLOBAL_ASM("asm/math_util/mtxf_to_mtx.s")
#endif

/* Official Name: mathSeed */
void set_rng_seed(s32 num) {
    gCurrentRNGSeed = num;
}

#ifdef NON_MATCHING
void save_rng_seed(void) {
    gPrevRNGSeed = gCurrentRNGSeed;
}
#else
GLOBAL_ASM("asm/math_util/save_rng_seed.s")
#endif

#ifdef NON_MATCHING
void load_rng_seed(void) {
    gCurrentRNGSeed = gPrevRNGSeed;
}
#else
GLOBAL_ASM("asm/math_util/load_rng_seed.s")
#endif

s32 get_rng_seed(void) {
    return gCurrentRNGSeed;
}

#ifdef NON_MATCHING
/**
 * Generates a random integer within the inclusive range [min, max].
 */
/* Official Name: mathRnd */
s32 rand_range(s32 min, s32 max) {
    s64 temp = gCurrentRNGSeed;

    temp = (temp << 32) | (temp >> 1);
    temp = temp ^ ((gCurrentRNGSeed & 0xFFFFF) << 12);
    gCurrentRNGSeed = temp ^ ((temp >> 20) & 0xFFF);

    return (u32) (gCurrentRNGSeed - min) % (max - min + 1) + min;
}
#else
GLOBAL_ASM("asm/math_util/rng.s")
#endif

#ifdef NON_MATCHING
/**
 * Reflects a vector across a given normal, such that the sum of the input and output vectors
 * lies in the direction of the normal (i.e. symmetric reflection).
 *
 * The normal vector must be normalized and represented in 3.13 fixed-point format (signed 16-bit,
 * with 13 fractional bits).
 *
 */
/* Official name: fastShortReflection */
void vec3s_reflect(Vec3s *vec, Vec3s *n) {
    s32 proj_x2 = (vec->x * n->x + vec->y * n->y + vec->z * n->z) >> 12;

    vec[1].x = ((proj_x2 * n->x) >> 13) - vec->x;
    vec[1].y = ((proj_x2 * n->y) >> 13) - vec->y;
    vec[1].z = ((proj_x2 * n->z) >> 13) - vec->x; //!@bug: should be vec->z
}
#else
GLOBAL_ASM("asm/math_util/vec3s_reflect.s")
#endif

#ifdef NON_MATCHING
/**
 * Converts an Mtx matrix (used by the RSP) into a 4x4 fixed-point matrix,
 * where each element is in 16.16 fixed-point format.
 */
UNUSED void mtx_to_mtxs_2(Mtx *m, MtxS *mi) {
    s16 *ai;
    u16 *af;
    s32 *ptr;
    s32 i;

    ai = (s16 *) &m->m[0][0];
    af = (u16 *) &m->m[2][0];
    ptr = (s32 *) &mi[0][0];

    for (i = 0; i < 16; i++) {
        *ptr++ = (*ai++ << 16) | (*af++);
    }
}
#else
GLOBAL_ASM("asm/math_util/mtx_to_mtxs_2.s")
#endif

#ifdef NON_MATCHING
/**
 * Transforms a 3D short vector using a 4×4 fixed-point (16.16) matrix.
 * The result is written back into the input vector.
 */
UNUSED void mtxs_transform_point(MtxS *mi, Vec3s *vec) {
    s16 x = vec->x;
    s16 y = vec->y;
    s16 z = vec->z;

    vec->x = ((*mi)[0][0] * x + (*mi)[1][0] * y + (*mi)[2][0] * z + (*mi)[3][0]) >> 16;
    vec->y = ((*mi)[0][1] * x + (*mi)[1][1] * y + (*mi)[2][1] * z + (*mi)[3][1]) >> 16;
    vec->z = ((*mi)[0][2] * x + (*mi)[1][2] * y + (*mi)[2][2] * z + (*mi)[3][2]) >> 16;
}
#else
GLOBAL_ASM("asm/math_util/mtxs_transform_point.s")
#endif

#ifdef NON_MATCHING
/**
 * Transforms a direction vector in 3D space using a 4×4 fixed-point (16.16) matrix.
 * The result is written back into the input vector.
 */
void mtxs_transform_dir(MtxS *mi, Vec3s *vec) {
    s16 x = vec->x;
    s16 y = vec->y;
    s16 z = vec->z;

    vec->x = ((*mi)[0][0] * x + (*mi)[1][0] * y + (*mi)[2][0] * z) >> 16;
    vec->y = ((*mi)[0][1] * x + (*mi)[1][1] * y + (*mi)[2][1] * z) >> 16;
    vec->z = ((*mi)[0][2] * x + (*mi)[1][2] * y + (*mi)[2][2] * z) >> 16;
}
#else
GLOBAL_ASM("asm/math_util/mtxs_transform_dir.s")
#endif

#ifdef NON_MATCHING
/**
 * Converts an ObjectTransform into a transformation matrix and writes it to `mtx`.
 * The matrix is built by applying the following operations in order:
 * 1. Scaling
 * 2. Rotation around Z axis (roll)
 * 3. Rotation around X axis (pitch)
 * 4. Rotation around Y axis (yaw)
 * 5. Translation
 */
void mtxf_from_transform(MtxF *mtx, ObjectTransform *trans) {
    f32 yRotSine;
    f32 yRotCosine;
    f32 xRotSine;
    f32 xRotCosine;
    f32 zRotSine;
    f32 zRotCosine;
    f32 scale;

    yRotSine = sins_s16(trans->rotation.y_rotation) * (1.0f / 0x10000);
    yRotCosine = coss_s16(trans->rotation.y_rotation) * (1.0f / 0x10000);
    xRotSine = sins_s16(trans->rotation.x_rotation) * (1.0f / 0x10000);
    xRotCosine = coss_s16(trans->rotation.x_rotation) * (1.0f / 0x10000);
    zRotSine = sins_s16(trans->rotation.z_rotation) * (1.0f / 0x10000);
    zRotCosine = coss_s16(trans->rotation.z_rotation) * (1.0f / 0x10000);
    scale = trans->scale;

    (*mtx)[0][0] = (xRotSine * yRotSine * zRotSine + zRotCosine * yRotCosine) * scale;
    (*mtx)[0][1] = (zRotSine * xRotCosine) * scale;
    (*mtx)[0][2] = (xRotSine * yRotCosine * zRotSine - zRotCosine * yRotSine) * scale;
    (*mtx)[0][3] = 0;
    (*mtx)[1][0] = (xRotSine * yRotSine * zRotCosine - zRotSine * yRotCosine) * scale;
    (*mtx)[1][1] = (zRotCosine * xRotCosine) * scale;
    (*mtx)[1][2] = (xRotSine * yRotCosine * zRotCosine + zRotSine * yRotSine) * scale;
    (*mtx)[1][3] = 0;
    (*mtx)[2][0] = (xRotCosine * yRotSine) * scale;
    (*mtx)[2][1] = -(xRotSine * scale);
    (*mtx)[2][2] = (xRotCosine * yRotCosine) * scale;
    (*mtx)[2][3] = 0;
    (*mtx)[3][0] = trans->x_position;
    (*mtx)[3][1] = trans->y_position;
    (*mtx)[3][2] = trans->z_position;
    (*mtx)[3][3] = 1.0f;
}
#else
GLOBAL_ASM("asm/math_util/mtxf_from_transform.s")
#endif

#ifdef NON_MATCHING
/**
 * Scales the Y axis of the given 4×4 transformation matrix by the specified factor.
 * If this is a model matrix, the operation is equivalent to stretching or squashing
 * the model along its local Y axis.
 /
/* Official name: mathSquashY */
void mtxf_scale_y(MtxF *input, f32 scale) {
    (*input)[1][0] *= scale;
    (*input)[1][1] *= scale;
    (*input)[1][2] *= scale;
}
#else
GLOBAL_ASM("asm/math_util/mtxf_scale_y.s")
#endif

#ifdef NON_MATCHING
/**
 * Modifies the matrix by translating its position along the local Y axis.
 * If this is a model matrix, the operation is equivalent to moving the model
 * along its local Y axis in model space.
 */
/* Official name: mathTransY */
void mtxf_translate_y(MtxF *input, f32 offset) {
    (*input)[3][0] += (*input)[1][0] * offset;
    (*input)[3][1] += (*input)[1][1] * offset;
    (*input)[3][2] += (*input)[1][2] * offset;
}
#else
GLOBAL_ASM("asm/math_util/mtxf_translate_y.s")
#endif

#ifdef NON_MATCHING
/**
 * Writes an inverse transformation matrix to `mtx` based on a pre-inverted `ObjectTransform`.
 * This is used to convert world-space coordinates to local object-space coordinates.
 * Unlike the standard transform, this version:
 *   - Omits scaling
 *   - Applies the transformation steps in reverse order
 *   - Assumes that the translation and rotation values in `trans` are already negated
 *
 * Operation order:
 *   1. Translate (negative offset)
 *   2. Rotate Y (negative yaw)
 *   3. Rotate X (negative pitch)
 *   4. Rotate Z (negative roll)
 */
/* Official Name: mathRpyXyzMtx */
void mtxf_from_inverse_transform(MtxF *mtx, ObjectTransform *trans) {
    f32 yRotSine;
    f32 yRotCosine;
    f32 xRotSine;
    f32 xRotCosine;
    f32 zRotSine;
    f32 zRotCosine;

    yRotCosine = coss_s16(trans->rotation.y_rotation) * (1.0f / 0x10000);
    yRotSine = sins_s16(trans->rotation.y_rotation) * (1.0f / 0x10000);
    xRotCosine = coss_s16(trans->rotation.x_rotation) * (1.0f / 0x10000);
    xRotSine = sins_s16(trans->rotation.x_rotation) * (1.0f / 0x10000);
    zRotCosine = coss_s16(trans->rotation.z_rotation) * (1.0f / 0x10000);
    zRotSine = sins_s16(trans->rotation.z_rotation) * (1.0f / 0x10000);

    (*mtx)[0][0] = yRotCosine * zRotCosine - xRotSine * zRotSine * yRotSine;
    (*mtx)[0][1] = xRotSine * zRotCosine * yRotSine + yRotCosine * zRotSine;
    (*mtx)[0][2] = -(yRotSine * xRotCosine);
    (*mtx)[0][3] = 0;
    (*mtx)[1][0] = -(xRotCosine * zRotSine);
    (*mtx)[1][1] = xRotCosine * zRotCosine;
    (*mtx)[1][2] = xRotSine;
    (*mtx)[1][3] = 0;
    (*mtx)[2][0] = xRotSine * zRotSine * yRotCosine + yRotSine * zRotCosine;
    (*mtx)[2][1] = yRotSine * zRotSine - xRotSine * zRotCosine * yRotCosine;
    (*mtx)[2][2] = yRotCosine * xRotCosine;
    (*mtx)[2][3] = 0;
    (*mtx)[3][0] =
        ((*mtx)[0][0] * trans->x_position) + ((*mtx)[1][0] * trans->y_position) + ((*mtx)[2][0] * trans->z_position);
    (*mtx)[3][1] =
        ((*mtx)[0][1] * trans->x_position) + ((*mtx)[1][1] * trans->y_position) + ((*mtx)[2][1] * trans->z_position);
    (*mtx)[3][2] =
        ((*mtx)[0][2] * trans->x_position) + ((*mtx)[1][2] * trans->y_position) + ((*mtx)[2][2] * trans->z_position);
    (*mtx)[3][3] = 1.0f;
}
#else
GLOBAL_ASM("asm/math_util/mtxf_from_inverse_transform.s")
#endif

GLOBAL_ASM("asm/math_util/func_80070058.s")

#ifdef NON_MATCHING
/**
 * Builds a billboard matrix for a sprite that always faces the camera.
 *
 * The resulting 4×4 matrix applies a rotation around the Z axis (in the XY plane),
 * followed by non-uniform scaling (uniform in X/Z and scaled by scaleY in Y).
 *
 * This is commonly used to render flat sprites that rotate to face the camera
 * while preserving their upright orientation.
 */
void mtxf_billboard(MtxF *mtx, s32 angle, f32 scale, f32 scaleY) {
    f32 cosine, sine;

    sine = sins_s16(angle) * (1.0f / 0x10000);
    cosine = coss_s16(angle) * (1.0f / 0x10000);
    (*mtx)[0][0] = cosine * scale;
    (*mtx)[0][1] = sine * scale;
    (*mtx)[0][2] = 0;
    (*mtx)[0][3] = 0;
    (*mtx)[1][0] = -sine * scale;
    (*mtx)[1][1] = (cosine * scale) * scaleY;
    (*mtx)[1][2] = 0;
    (*mtx)[1][3] = 0;
    (*mtx)[2][0] = 0;
    (*mtx)[2][1] = 0;
    (*mtx)[2][2] = scale;
    (*mtx)[2][3] = 0;
    (*mtx)[3][0] = 0;
    (*mtx)[3][1] = 0;
    (*mtx)[3][2] = 0;
    (*mtx)[3][3] = 1.0f;
}
#else
GLOBAL_ASM("asm/math_util/mtxf_billboard.s")
#endif

#ifdef NON_MATCHING
/**
 * Rotates the given vector in place.
 * Note: The rotation angles are specified in reverse order, but the applied rotation is standard
 * — roll first, then pitch, then yaw.
 */
void vec3s_rotate_rpy(RPYAngles *rotation, Vec3s *vec) {
    s32 x1, y1, z1;
    s32 x2, y2, z2;
    s32 sine, cosine;

    x1 = vec->x;
    y1 = vec->y;
    z1 = vec->z;

    sine = sins_s16(rotation->z_rotation);
    cosine = coss_s16(rotation->z_rotation);
    x2 = (x1 * cosine - y1 * sine) >> 16;
    y2 = (y1 * cosine + x1 * sine) >> 16;
    z2 = z1;

    sine = sins_s16(rotation->x_rotation);
    cosine = coss_s16(rotation->x_rotation);
    x1 = x2;
    y1 = (y2 * cosine - z2 * sine) >> 16;
    z1 = (z2 * cosine + y2 * sine) >> 16;

    sine = sins_s16(rotation->y_rotation);
    cosine = coss_s16(rotation->y_rotation);
    x2 = (x1 * cosine + z1 * sine) >> 16;
    y2 = y1;
    z2 = (z1 * cosine - x1 * sine) >> 16;

    vec->x = x2;
    vec->y = y2;
    vec->z = z2;
}
#else
GLOBAL_ASM("asm/math_util/vec3s_rotate_rpy.s")
#endif

#ifdef NON_MATCHING
/**
 * Rotates the given vector according to the specified rotation angles.
 * The result is written back into the same vector.
 */
/* Official Name: mathOneFloatRPY */
void vec3f_rotate(Vec3s *rotation, Vec3f *vec) {
    f32 sine;
    f32 cosine;
    f32 x1, y1, z1;
    f32 x2, y2, z2;

    x1 = vec->x;
    y1 = vec->y;
    z1 = vec->z;

    sine = sins_f(rotation->z_rotation);
    cosine = coss_f(rotation->z_rotation);
    x2 = x1 * cosine - y1 * sine;
    y2 = y1 * cosine + x1 * sine;
    z2 = z1;

    sine = sins_f(rotation->x_rotation);
    cosine = coss_f(rotation->x_rotation);
    x1 = x2;
    y1 = y2 * cosine - z2 * sine;
    z1 = z2 * cosine + y2 * sine;

    sine = sins_f(rotation->y_rotation);
    cosine = coss_f(rotation->y_rotation);
    x2 = x1 * cosine + z1 * sine;
    y2 = y1;
    z2 = z1 * cosine - x1 * sine;

    vec->x = x2;
    vec->y = y2;
    vec->z = z2;
}
#else
GLOBAL_ASM("asm/math_util/vec3f_rotate.s")
#endif

#ifdef NON_MATCHING
/**
 * Applies the inverse of the object rotation using the specified angles.
 * Unlike the standard roll-pitch-yaw (Z-X-Y) order, this applies the angles in yaw-pitch-roll (Y-X-Z) order.
 * To fully reverse the effect of vec3f_rotate, the input angles must also be negated.
 * The result is written back into the same vector.
 */
/* Official Name: mathOneFloatYPR */
void vec3f_rotate_ypr(Vec3s *rotation, Vec3f *vec) {
    f32 sine;
    f32 cosine;
    f32 x1, y1, z1;
    f32 x2, y2, z2;

    x1 = vec->x;
    y1 = vec->y;
    z1 = vec->z;

    sine = sins_f(rotation->y_rotation);
    cosine = coss_f(rotation->y_rotation);
    x2 = x1 * cosine + z1 * sine;
    y2 = y1;
    z2 = z1 * cosine - x1 * sine;

    sine = sins_f(rotation->x_rotation);
    cosine = coss_f(rotation->x_rotation);
    x1 = x2;
    y1 = y2 * cosine - z2 * sine;
    z1 = z2 * cosine + y2 * sine;

    sine = sins_f(rotation->z_rotation);
    cosine = coss_f(rotation->z_rotation);
    x2 = x1 * cosine - y1 * sine;
    y2 = y1 * cosine + x1 * sine;
    z2 = z1;

    vec->x = x2;
    vec->y = y2;
    vec->z = z2;
}
#else
GLOBAL_ASM("asm/math_util/vec3f_rotate_ypr.s")
#endif

#ifdef NON_MATCHING
/**
 * Rotates a forward-facing vector by the given pitch and yaw angles.
 * Only the Z component of the input vector is considered; X and Y components are ignored.
 * The roll angle is also ignored, as it has no effect on directional vectors.
 * This is typically used to compute a direction vector from pitch and yaw angles.
 * The result is written back into the same vector.
 */
/* Official Name: mathOneFloatPY */
void vec3f_rotate_py(Vec3s *rotation, Vec3f *vec) {
    f32 sinX;
    f32 cosX;
    f32 sinY;
    f32 cosY;
    f32 z;

    sinX = sins_f(rotation->x_rotation);
    cosX = coss_f(rotation->x_rotation);
    sinY = sins_f(rotation->y_rotation);
    cosY = coss_f(rotation->y_rotation);

    z = vec->z;

    vec->x = z * cosX * sinY;
    vec->y = -z * sinX;
    vec->z = z * cosX * cosY;
}
#else
GLOBAL_ASM("asm/math_util/vec3f_rotate_py.s")
#endif

#ifdef NON_MATCHING
/**
 * Determines whether a point lies inside a triangle, projected onto the XZ plane.
 * Points lying exactly on the triangle's edges are not considered inside.
 */
/* Official Name: mathXZInTri */
s32 tri2d_xz_contains_point(s32 x, s32 z, Vec3s *pointA, Vec3s *pointB, Vec3s *pointC) {
    s32 aX, aZ, bX, bZ, cX, cZ;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;

    aX = pointA->x;
    aZ = pointA->z;
    bX = pointB->x;
    bZ = pointB->z;
    cX = pointC->x;
    cZ = pointC->z;

    var_a3 = (x - aX) * (bZ - aZ) - (bX - aX) * (z - aZ) >= 0;
    var_a2 = (x - bX) * (cZ - bZ) - (cX - bX) * (z - bZ) >= 0;
    var_a1 = (x - cX) * (aZ - cZ) - (aX - cX) * (z - cZ) >= 0;
    return var_a3 == var_a2 && var_a2 == var_a1;
}
#else
GLOBAL_ASM("asm/math_util/tri2d_xz_contains_point.s")
#endif

#ifdef NON_MATCHING
/**
 * Creates a translation matrix that moves points by the specified (x, y, z) offset.
 */
/* Official Name: mathTranslateMtx */
void mtxf_from_translation(MtxF *mtx, f32 x, f32 y, f32 z) {
    s32 i, j;

    // Clear matrix
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            (*mtx)[i][j] = 0;
        }
    }
    (*mtx)[0][0] = 1.0f;
    (*mtx)[1][1] = 1.0f;
    (*mtx)[2][2] = 1.0f;
    (*mtx)[3][3] = 1.0f;
    (*mtx)[3][0] = x;
    (*mtx)[3][1] = y;
    (*mtx)[3][2] = z;
}
#else
GLOBAL_ASM("asm/math_util/mtxf_from_translation.s")
#endif

#ifdef NON_MATCHING
/**
 * Creates a scaling matrix with the specified scale factors along the X, Y, and Z axes.
 */
/* Official Name: mathScaleMtx */
void mtxf_from_scale(MtxF *mtx, f32 scaleX, f32 scaleY, f32 scaleZ) {
    s32 i, j;

    // Clear matrix
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            (*mtx)[i][j] = 0;
        }
    }

    (*mtx)[0][0] = scaleX;
    (*mtx)[1][1] = scaleY;
    (*mtx)[2][2] = scaleZ;
    (*mtx)[3][3] = 1.0f;
}
#else
GLOBAL_ASM("asm/math_util/mtxf_from_scale.s")
#endif

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

#ifdef NON_EQUIVALENT
/**
 * Computes the square root of a 16.16 fixed-point number and returns the result in the same format.
 * Due to differences in rounding, the result from this C implementation may differ by 1 from the
 * result produced by the assembly code.
 */
UNUSED s32 fix32_sqrt(s32 x) {
    return FTOFIX32(sqrtf(FIX32TOF(x)));
}
#else
GLOBAL_ASM("asm/math_util/fix32_sqrt.s")
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
