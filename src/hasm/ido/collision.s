#ifdef MODERN_CC
.set gp=64
#endif

#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"
#include "asm_macros.h"

.rdata

EXPORT(D_800E5F60)
    .float -0.1
EXPORT(D_800E5F64)
    .float -0.1
EXPORT(D_800E5F68)
    .float 0.707
EXPORT(D_800E5F6C)
    .float 0.45
EXPORT(D_800E5F70)
    .float -0.1

.text

#define RENDER_HIDDEN 0x100
#define RENDER_NO_COLLISION 0x200

#define SURFACE_WATER_CALM 11
#define SURFACE_INVIS_WALL 17
#define SURFACE_UNK12 18

#define VEHICLE_NO_OVERRIDE -1
#define VEHICLE_CAR 1
#define VEHICLE_PLANE 2

#define TEX_INDEX_NO_TEXTURE 0xFF

#define MAX_COLLISION_CANDIDATES 500

#define sizeOfVec3f 0xC
#define sizeOfLevelModelSegmentBoundingBox 0xC
#define sizeOfLevelModelSegment 0x44
#define sizeOfTriangleBatchInfo 0xC
#define sizeOfTextureInfo 0x8

#define minX s5
#define maxX s4
#define minZ s3
#define maxZ s2
#define x1 t0
#define z1 t1
#define x2 t2
#define z2 t3
#define vehicleID s6

LEAF(generate_collision_candidates)
    addiu      sp, sp, -0x70
    sw         ra, 0x30(sp)
    sw         s6, 0x2C(sp)
    sw         s5, 0x28(sp)
    sw         s4, 0x24(sp)
    sw         s3, 0x20(sp)
    sw         s2, 0x1C(sp)
    sw         s1, 0x18(sp)
    sw         s0, 0x14(sp)
    li         t0, 100000
    li         t1, -100000
    move       minX, t0 # s5 = minX
    move       maxX, t1 # s4 = maxX
    move       minZ, t0 # s3 = minZ
    move       maxZ, t1 # s2 = maxZ
    move       vehicleID, a3 # s6 = vehicleID
    beqz       a0, .zero_numPoints # Skip if no collision candidates
    sll        t0, a0, 3 # t0 = a0 * 8
    sll        t1, a0, 2 # t1 = a0 * 4
    add        a0, t0, t1 # a0 = a0 * 12
    add        a0, a0, a1 # a0 = forLoopEnd = a1 + (numPoints * sizeof(Vec3f))
.for_loop_start: # for (i = 0; i < numPoints; i++)
    lwc1       fv0, 0x0(a1) /* fv0 = origins[i].x */
    lwc1       fv1, 0x8(a1) /* fv1 = origins[i].z */
    lwc1       ft0, 0x0(a2) /* ft0 = targets[i].x */
    lwc1       ft1, 0x8(a2) /* ft1 = targets[i].z */
    trunc.w.s  fv0, fv0
    trunc.w.s  fv1, fv1
    trunc.w.s  ft0, ft0
    trunc.w.s  ft1, ft1
    mfc1       x1, fv0 /* t0 = x1 = (s32) origins[i].x */
    mfc1       z1, fv1 /* t1 = z1 = (s32) origins[i].z */
    mfc1       x2, ft0 /* t2 = x2 = (s32) targets[i].x */
    mfc1       z2, ft1 /* t3 = z2 = (s32) targets[i].z */
    bge        maxX, x1, .skip_maxX_update
    move       maxX, x1  /* maxX = x1 */
.skip_maxX_update:
    ble        minX, x1, .skip_minX_update
    move       minX, x1  /* minX = x1 */
.skip_minX_update:
    bge        maxZ, z1, .skip_maxZ_update
    move       maxZ, z1  /* maxZ = z1 */
.skip_maxZ_update:
    ble        minZ, z1, .skip_minZ_update
    move       minZ, z1  /* minZ = z1 */
.skip_minZ_update:
    bge        maxX, x2, .skip_maxX_update2
    move       maxX, x2  /* maxX = x2 */
.skip_maxX_update2:
    ble        minX, x2, .skip_minX_update2
    move       minX, x2  /* minX = x2 */
.skip_minX_update2:
    bge        maxZ, z2, .skip_maxZ_update2
    move       maxZ, z2  /* maxZ = z2 */
.skip_maxZ_update2:
    ble        minZ, z2, .skip_minZ_update2
    move       minZ, z2  /* minZ = z2 */
.skip_minZ_update2:
    addiu     a1, a1, sizeOfVec3f /* Advance to the next origin pointer */
    addiu     a2, a2, sizeOfVec3f /* Advance to the next target pointer */
    blt       a1, a0, .for_loop_start
.zero_numPoints:
    /* Expand the bounding box by 20 units in all directions */
    addiu      minX, -20
    addiu      maxX, 20
    addiu      minZ, -20
    addiu      maxZ, 20
    /* if (maxX >= minX) swap min and max x */
    bge        maxX, minX, .skip_swap_x
    move       t0, minX
    move       minX, maxX
    move       maxX, t0
.skip_swap_x:
    /* if (maxZ >= minZ) swap min and max z */
    bge        maxZ, minZ, .skip_swap_z
    move       t0, minZ
    move       minZ, maxZ
    move       maxZ, t0
.skip_swap_z:
    lui        t0, %hi(gCurrentLevelModel)
    lw         t0, %lo(gCurrentLevelModel)(t0)
    addi       s1, sp, 0x34 /* s16 grid_mask[10]; */
    addi       s0, sp, 0x48 /* LevelModelSegment *segments[10]; */
    move       t8, zero
    lw         a0, 0x8(t0)   /* a0 = &gCurrentLevelModel->segmentsBoundingBoxes */
    lw         t6, 0x4(t0)   /* t6 = &gCurrentLevelModel->segments */
    lh         t7, 0x1A(t0)  /* t7 = gCurrentLevelModel->numberOfSegments */
    beqz       t7, .end_loop /* Skip loop if no segments */
.start_of_loop:
    lh         v1, 0x0(a0) /* v1 = segmentBoundingBox->x1 */
    lh         v0, 0x6(a0) /* v0 = segmentBoundingBox->x2 */
    addiu      v0, 5       /* v0 = x2 + 5 */
    addiu      v1, -5      /* v1 = x1 - 5 */
    blt        v0, minX, .continue_loop
    blt        maxX, v1, .continue_loop
    lh         t1, 0x4(a0) /* t1 = segmentBoundingBox->z1 */
    lh         t0, 0xA(a0) /* t0 = segmentBoundingBox->z2 */
    addiu      t1, -5      /* t1 = z1 - 5 */
    addiu      t0, 5       /* t0 = z2 + 5 */
    blt        t0, minZ, .continue_loop
    blt        maxZ, t1, .continue_loop
    move       a1, minX
    move       a2, minZ
    move       a3, maxX
    sw         maxZ, 0x10(sp)
    jal        compute_grid_overlap_mask
    sh         v0, 0x0(s1) /* *s1 = gridOverlapMask */
    sw         t6, 0x0(s0) /* *s0 = pointer for &gCurrentLevelModel->segments[i] */
    addiu      s1, 0x2 /* s1 = gridOverlapMask++ */
    addiu      s0, 4 /* segments++ */
    addiu      t8, 1 /* counter++ */
    beq        t8, 10, .end_loop
.continue_loop:
    addiu      t7, -1
    addiu      a0, sizeOfLevelModelSegmentBoundingBox
    addiu      t6, sizeOfLevelModelSegment
    bnez       t7, .start_of_loop
.end_loop:
    move       s3, zero /* j = 0 */
    beqz       t8, .L800314A8
    lui        a0, %hi(gCurrentLevelModel)
    lw         a0, %lo(gCurrentLevelModel)(a0)
    lui        s2, %hi(gCollisionCandidates)
    lw         s2, %lo(gCollisionCandidates)(s2)
    lui        t9, %hi(gCollisionSurfaces)
    lw         t9, %lo(gCollisionSurfaces)(t9)
    addi       s1, sp, 0x34 /* s16 grid_mask[10]; */
    addi       s0, sp, 0x48 /* LevelModelSegment *segments[10]; */
    sll        t8, 1 /* t8 = counter * 2 */
    add        t8, s1, t8 /* t8 = &grid_mask[counter] */
    lw         a0, 0x0(a0) /* a0 = gCurrentLevelModel->textures */
.start_of_candidate_loop:
    lw         t7, 0x0(s0) /* t7 = pointer for segments[i] */
    lh         t6, 0x0(s1) /* t6 = grid_mask[counter] */
    and        v0, t7, 0x7FFFFFFF /* v0 = seg & 0x7FFFFFFF: clear sign bit to tag as segment (non-negative)  */
    sw         v0, 0x0(s2) /* gCollisionCandidates[j] = tagged segment ptr (MSB=0; facets stay negative) */
    lh         t0, 0x20(t7) /* t0 = segments[i].numberOfBatches */
    lw         t5, 0xC(t7)  /* t5 = segments[i].batches (current batch) */
#if (sizeOfTriangleBatchInfo != 0xC)
    /* Do this in case sizeOfTriangleBatchInfo changes in the future. */
    mul        t3, t0, sizeOfTriangleBatchInfo
#else
    sll        v0, t0, 3
    sll        v1, t0, 2
    add        t3, v0, v1 /* t3 = numberOfBatches * 12 (sizeof(TriangleBatchInfo)) */
#endif
    add        t3, t3, t5 /* t3 = &batches[numberOfBatches] (loop end) */
    addiu      s3, 1 /* j++ */
    addiu      s2, 4 /* Advance to the next gCollisionCandidates value */
    addiu      t9, 1 /* Advance to the next gCollisionSurfaces value */
    addiu      t4, t5, sizeOfTriangleBatchInfo /* t4 = &batches[1] (the batchIndex+1 batch) */
.start_of_inner_loop:
    lw         t0, 0x8(t5) /* t0 = batch->flags */
    andi       v0, t0, RENDER_NO_COLLISION
    bnez       v0, .L8003148C
    bne        vehicleID, VEHICLE_NO_OVERRIDE, .L800313D0
    andi       v0, t0, RENDER_HIDDEN
    bnez       v0, .L8003148C
.L800313D0:
    lbu        v1, 0x0(t5) /* v1 = batch->textureIndex */
    move       t2, zero /* t2 = 0 */
    beq        v1, TEX_INDEX_NO_TEXTURE, .skip_no_texture /* Skip batches with no texture, since the surface type is stored in the texture data */
    mul        v1, sizeOfTextureInfo
    add        v1, a0 /* v1 = &textures[textureIndex] */
    lb         t2, 0x7(v1) /* t2 = textures[textureIndex].surfaceType */
    beq        t2, SURFACE_WATER_CALM, .L8003148C
    bne        vehicleID, VEHICLE_PLANE, .L80031408
    beq        t2, SURFACE_INVIS_WALL, .L8003148C
.L80031408:
    beqz       vehicleID, .skip_no_texture
    beq        t2, SURFACE_UNK12, .L8003148C
.skip_no_texture:
    lh         t0, 0x4(t5)
    lh         t1, 0x4(t4)
    lw         a2, 0x10(t7)
    lw         a3, 0x14(t7)
    sll        t1, t1, 1
    sll        v0, t0, 1
    sll        v1, t0, 3
    add        a1, a2, t1
    add        a2, a2, v0
    add        a3, a3, v1
.L80031440:
    lh         t0, 0x0(a2)
    and        t0, t0, t6
    andi       v0, t0, 0xFF
    andi       v1, t0, 0xFF00
    beqz       v0, .L8003147C
    beqz       v1, .L8003147C
    sw         a3, 0x0(s2)
    addiu      s3, 0x1
    sb         t2, 0x0(t9)
    addiu      s2, 0x4
    addiu      t9, t9, 0x1
    beq        s3, MAX_COLLISION_CANDIDATES, .L800314A8
.L8003147C:
    addiu      a2, a2, 0x2
    addiu      a3, a3, 0x8
    blt        a2, a1, .L80031440
.L8003148C:
    addiu      t5, sizeOfTriangleBatchInfo
    addiu      t4, t4, 0xC
    blt        t5, t3, .start_of_inner_loop
    addiu      s1, s1, 0x2
    addiu      s0, s0, 0x4
    blt        s1, t8, .start_of_candidate_loop
.L800314A8:
    lw         ra, 0x30(sp)
    sw         s3, gNumCollisionCandidates
    lw         s6, 0x2C(sp)
    lw         s5, 0x28(sp)
    lw         s4, 0x24(sp)
    lw         s3, 0x20(sp)
    lw         s2, 0x1C(sp)
    lw         s1, 0x18(sp)
    lw         s0, 0x14(sp)
    or         v0, zero, zero
    addiu      sp, sp, 0x70
    jr         ra
END(generate_collision_candidates)

.set noreorder
.set noat
LEAF(compute_grid_overlap_mask)
    beqz       a0, .L800315F8
    or        v0, zero, zero
    lh         t0, 0x0(a0)
    lw         t5, 0x10(sp) /* maxZ from generate_collision_candidates */
    lh         t1, 0x4(a0)
    slt        $at, a3, t0
    lh         t2, 0x6(a0)
    beqz       $at, .L80031504
    lh        t3, 0xA(a0)
    or         a3, t0, zero
    .L80031504:
    slt        $at, a1, t0
    beql       $at, zero, .L80031518
    slt       $at, t5, t1
    or         a1, t0, zero
    slt        $at, t5, t1
    .L80031518:
    beql       $at, zero, .L80031528
    slt       $at, a2, t1
    or         t5, t1, zero
    slt        $at, a2, t1
    .L80031528:
    beql       $at, zero, .L80031538
    slt       $at, t2, a3
    or         a2, t1, zero
    slt        $at, t2, a3
    .L80031538:
    beql       $at, zero, .L80031548
    slt       $at, t2, a1
    or         a3, t2, zero
    slt        $at, t2, a1
    .L80031548:
    beql       $at, zero, .L80031558
    slt       $at, t3, t5
    or         a1, t2, zero
    slt        $at, t3, t5
    .L80031558:
    beql       $at, zero, .L80031568
    slt       $at, t3, a2
    or         t5, t3, zero
    slt        $at, t3, a2
    .L80031568:
    beql       $at, zero, .L80031578
    sub       t2, t2, t0
    or         a2, t3, zero
    sub        t2, t2, t0
    .L80031578:
    sra        t2, t2, 3
    addiu      t2, t2, 0x1
    addiu      v1, zero, 0x1
    add        t4, t2, t0
    .L80031588:
    slt        $at, t4, a1
    bnez       $at, .L800315A0
    slt       $at, a3, t0
    bnel       $at, zero, .L800315A4
    sll       v1, v1, 1
    or         v0, v0, v1
    .L800315A0:
    sll        v1, v1, 1
    .L800315A4:
    slti       $at, v1, 0x100
    add        t4, t4, t2
    bnez       $at, .L80031588
    add       t0, t0, t2
    sub        t2, t3, t1
    sra        t2, t2, 3
    addiu      t2, t2, 0x1
    add        t4, t2, t1
    or         t0, t1, zero
    .L800315C8:
    slt        $at, t4, a2
    bnez       $at, .L800315E0
    slt       $at, t5, t0
    bnel       $at, zero, .L800315E4
    sll       v1, v1, 1
    or         v0, v0, v1
    .L800315E0:
    sll        v1, v1, 1
    .L800315E4:
    lui        $at, (0x10000 >> 16)
    slt        $at, v1, $at
    add        t4, t4, t2
    bnez       $at, .L800315C8
    add       t0, t0, t2
    .L800315F8:
    jr         ra
    nop
END(compute_grid_overlap_mask)

LEAF(resolve_collisions)
    addiu      t0, zero, 0x1
    sb         t0, 0x1(sp)
    lui        t0, %hi(gNumCollisionCandidates)
    lw         t0, %lo(gNumCollisionCandidates)(t0)
    lui        $at, %hi(gHitWall)
    sb         zero, 0x0(sp)
    beqz       t0, .L80031B4C
    sw        zero, %lo(gHitWall)($at)
    .L80031620:
    or         t6, zero, zero
    .L80031624:
    lui        t5, %hi(gCollisionSurfaces)
    lui        t1, %hi(gCollisionCandidates)
    lui        t0, %hi(gNumCollisionCandidates)
    or         t7, zero, zero
    lw         t5, %lo(gCollisionSurfaces)(t5)
    lw         t1, %lo(gCollisionCandidates)(t1)
    lw         t0, %lo(gNumCollisionCandidates)(t0)
    .L80031640:
    lw         t2, 0x0(t1)
    blezl      t2, .L80031660
    lhu       v0, 0x0(t2)
    lui        t3, 0x8000
    or         t3, t3, t2
    j          .L80031944
    lw        t3, 0x18(t3)
    lhu        v0, 0x0(t2)
    .L80031660:
    lwc1       ft2, 0x0(a1)
    lwc1       ft3, 0x4(a1)
    sll        v0, v0, 4
    addu       v0, v0, t3
    lwc1       fv0, 0(v0)
    lwc1       fv1, 4(v0)
    lwc1       ft0, 8(v0)
    mul.s      ft2, ft2, fv0
    lwc1       ft4, 0x8(a1)
    lwc1       ft1, 0xC(v0)
    mul.s      ft3, ft3, fv1
    lui        $at, %hi(D_800E5F60)
    mul.s      ft4, ft4, ft0
    add.s      ft2, ft2, ft3
    add.s      ft2, ft2, ft4
    add.s      ft5, ft2, ft1
    lwc1       ft2, 0x0(a2)
    sub.s      ft5, ft5, ft2
    lwc1       ft2, %lo(D_800E5F60)($at)
    c.olt.s    ft5, ft2
    bc1fl      .L80031948
    addiu     t0, t0, -0x1
    lwc1       ft2, 0x0(a0)
    lwc1       ft3, 0x4(a0)
    lwc1       ft4, 0x8(a0)
    mul.s      ft2, ft2, fv0
    lui        $at, %hi(D_800E5F64)
    mul.s      ft3, ft3, fv1
    add.s      ft2, ft2, ft3
    mul.s      ft4, ft4, ft0
    add.s      ft2, ft2, ft4
    add.s      ft4, ft2, ft1
    lwc1       ft2, 0x0(a2)
    sub.s      ft4, ft4, ft2
    lwc1       ft2, %lo(D_800E5F64)($at)
    c.olt.s    ft4, ft2
    bc1tl      .L80031948
    addiu     t0, t0, -0x1
    lwc1       ft2, 0x0(a0)
    lwc1       ft3, 0x0(a1)
    sub.s      fv0, ft3, ft2
    lwc1       ft2, 0x4(a0)
    lwc1       ft3, 0x4(a1)
    sub.s      fv1, ft3, ft2
    lwc1       ft2, 0x8(a0)
    lwc1       ft3, 0x8(a1)
    sub.s      ft0, ft3, ft2
    mtc1       zero, ft3
    sub.s      ft2, ft4, ft5
    c.ueq.s    ft2, ft3
    bc1t       .L80031734
    nop
    div.s      ft3, ft4, ft2
    .L80031734:
    mul.s      fv0, fv0, ft3
    lwc1       ft1, 0x0(a0)
    lui        $at, (0x40800000 >> 16)
    mul.s      fv1, fv1, ft3
    addiu      t4, zero, 0x3
    mul.s      ft0, ft0, ft3
    mtc1       $at, ft3
    add.s      fv0, ft1, fv0
    lwc1       ft1, 0x4(a0)
    add.s      fv1, ft1, fv1
    lwc1       ft1, 0x8(a0)
    add.s      ft0, ft1, ft0
    .L80031764:
    lhu        v1, 0x2(t2)
    or         t8, zero, zero
    andi       t9, v1, 0x8000
    beql       t9, zero, .L80031784
    sll       v1, v1, 4
    andi       v1, v1, 0x7FFF
    addiu      t8, zero, 0x1
    sll        v1, v1, 4
    .L80031784:
    addu       v1, v1, t3
    lwc1       ft1, 0(v1)
    lwc1       ft2, 4(v1)
    mul.s      ft1, fv0, ft1
    nop
    mul.s      ft2, fv1, ft2
    add.s      ft1, ft1, ft2
    lwc1       ft2, 0x8(v1)
    mul.s      ft2, ft0, ft2
    add.s      ft1, ft1, ft2
    lwc1       ft2, 0xC(v1)
    beqz       t8, .L800317BC
    add.s     ft1, ft1, ft2
    neg.s      ft1, ft1
    .L800317BC:
    c.ole.s    ft1, ft3
    bc1fl      .L80031948
    addiu     t0, t0, -0x1
    addiu      t4, t4, -0x1
    bnez       t4, .L80031764
    addiu     t2, t2, 0x2
    lui        $at, %hi(D_800E5F68)
    lwc1       fv0, %lo(D_800E5F68)($at)
    lwc1       fv1, 0x4(v0)
    lwc1       ft0, 0x8(v0)
    c.ult.s    fv1, fv0
    lwc1       fv0, 0x0(v0)
    bc1t       .L80031848
    nop
    lb         v1, 0x0(t5)
    addiu      $at, zero, 0x4
    beq        v1, $at, .L80031848
    nop
    lui        v1, %hi(gCollisionMode)
    lw         v1, %lo(gCollisionMode)(v1)
    bnez       v1, .L80031848
    nop
    lwc1       ft1, 0x0(a1)
    mul.s      fv0, ft1, fv0
    lwc1       ft1, 0x8(a1)
    mul.s      ft0, ft1, ft0
    lwc1       ft1, 0xC(v0)
    add.s      fv0, fv0, ft0
    lwc1       ft0, 0x8(a1)
    add.s      fv0, fv0, ft1
    lwc1       ft1, 0x0(a2)
    sub.s      fv0, ft1, fv0
    div.s      fv1, fv0, fv1
    j          .L800318C8
    lwc1      fv0, 0x0(a1)
    .L80031848:
    lui        $at, %hi(D_800E5F6C)
    lwc1       ft3, %lo(D_800E5F6C)($at)
    c.olt.s    fv1, ft3
    bc1f       .L800318A0
    nop
    lui        v1, %hi(gCollisionMode)
    lw         v1, %lo(gCollisionMode)(v1)
    addiu      $at, zero, 0x2
    beq        v1, $at, .L800318A0
    nop
    addiu      v1, zero, 0x1
    lui        $at, %hi(gHitWall)
    sw         v1, %lo(gHitWall)($at)
    lwc1       ft1, 0x0(v0)
    lui        $at, %hi(gCollisionNormalX)
    swc1       ft1, %lo(gCollisionNormalX)($at)
    lwc1       ft1, 0x4(v0)
    lui        $at, %hi(gCollisionNormalY)
    swc1       ft1, %lo(gCollisionNormalY)($at)
    lwc1       ft1, 0x8(v0)
    lui        $at, %hi(gCollisionNormalZ)
    swc1       ft1, %lo(gCollisionNormalZ)($at)
    .L800318A0:
    mul.s      fv0, fv0, ft5
    lwc1       ft1, 0x0(a1)
    mul.s      fv1, fv1, ft5
    nop
    mul.s      ft0, ft0, ft5
    sub.s      fv0, ft1, fv0
    lwc1       ft1, 0x4(a1)
    sub.s      fv1, ft1, fv1
    lwc1       ft1, 0x8(a1)
    sub.s      ft0, ft1, ft0
    .L800318C8:
    lui        v1, %hi(gHitWall)
    lw         v1, %lo(gHitWall)(v1)
    bnel       v1, zero, .L80031900
    lb        t4, 0x0(t5)
    lwc1       ft1, 0x0(v0)
    lui        $at, %hi(gCollisionNormalX)
    swc1       ft1, %lo(gCollisionNormalX)($at)
    lwc1       ft1, 0x4(v0)
    lui        $at, %hi(gCollisionNormalY)
    swc1       ft1, %lo(gCollisionNormalY)($at)
    lwc1       ft1, 0x8(v0)
    lui        $at, %hi(gCollisionNormalZ)
    swc1       ft1, %lo(gCollisionNormalZ)($at)
    lb         t4, 0x0(t5)
    .L80031900:
    lb         v0, 0x0(a3)
    slt        $at, v0, t4
    beql       $at, zero, .L80031918
    addiu     t6, t6, 0x1
    sb         t4, 0x0(a3)
    addiu      t6, t6, 0x1
    .L80031918:
    slti       $at, t6, 0xB
    bnez       $at, .L80031934
    addiu     t7, zero, 0x1
    or         t7, zero, zero
    lwc1       fv0, 0x0(a0)
    lwc1       fv1, 0x4(a0)
    lwc1       ft0, 0x8(a0)
    .L80031934:
    swc1       fv0, 0x0(a1)
    swc1       fv1, 0x4(a1)
    j          .L80031954
    swc1      ft0, 0x8(a1)
    .L80031944:
    addiu      t0, t0, -0x1
    .L80031948:
    addiu      t5, t5, 0x1
    bnez       t0, .L80031640
    addiu     t1, t1, 0x4
    .L80031954:
    bnez       t7, .L80031624
    nop
    beqz       t6, .L80031980
    lbu       t2, 0x1(sp)
    lw         t1, 0x14(sp)
    lw         t0, 0x0(t1)
    addiu      t0, t0, 0x1
    sw         t0, 0x0(t1)
    lbu        t0, 0x0(sp)
    or         t0, t0, t2
    sb         t0, 0x0(sp)
    .L80031980:
    sll        t2, t2, 1
    sb         t2, 0x1(sp)
    or         t6, zero, zero
    .L8003198C:
    lui        t1, %hi(gCollisionCandidates)
    lui        t0, %hi(gNumCollisionCandidates)
    or         t7, zero, zero
    lw         t1, %lo(gCollisionCandidates)(t1)
    lw         t0, %lo(gNumCollisionCandidates)(t0)
    .L800319A0:
    lw         t2, 0x0(t1)
    blezl      t2, .L800319C0
    lhu       v0, 0x0(t2)
    lui        t3, 0x8000
    or         t3, t3, t2
    j          .L80031B18
    lw        t3, 0x18(t3)
    lhu        v0, 0x0(t2)
    .L800319C0:
    lwc1       ft2, 0x0(a1)
    lwc1       ft3, 0x4(a1)
    sll        v0, v0, 4
    addu       v0, v0, t3
    lwc1       fv0, 0x0(v0)
    lwc1       fv1, 0x4(v0)
    lwc1       ft0, 0x8(v0)
    mul.s      ft2, ft2, fv0
    lwc1       ft4, 0x8(a1)
    lwc1       ft1, 0xC(v0)
    mul.s      ft3, ft3, fv1
    lui        $at, %hi(D_800E5F70)
    mul.s      ft4, ft4, ft0
    add.s      ft2, ft2, ft3
    add.s      ft2, ft2, ft4
    add.s      ft5, ft2, ft1
    lwc1       ft2, 0x0(a2)
    sub.s      ft5, ft5, ft2
    lwc1       ft2, %lo(D_800E5F70)($at)
    c.olt.s    ft5, ft2
    bc1f       .L80031B18
    lui       $at, (0x40400000 >> 16)
    mtc1       $at, ft3
    lwc1       ft2, 0x0(a2)
    add.s      ft2, ft2, ft3
    neg.s      ft2, ft2
    c.ole.s    ft5, ft2
    bc1t       .L80031B18
    lui       $at, (0x40800000 >> 16)
    mtc1       $at, ft3
    lwc1       fv0, 0x0(a1)
    lwc1       fv1, 0x4(a1)
    lwc1       ft0, 0x8(a1)
    addiu      t4, zero, 0x3
    .L80031A48:
    lhu        v1, 0x2(t2)
    or         t8, zero, zero
    andi       t9, v1, 0x8000
    beql       t9, zero, .L80031A68
    sll       v1, v1, 4
    andi       v1, v1, 0x7FFF
    addiu      t8, zero, 0x1
    sll        v1, v1, 4
    .L80031A68:
    addu       v1, v1, t3
    lwc1       ft1, 0x0(v1)
    lwc1       ft2, 0x4(v1)
    mul.s      ft1, fv0, ft1
    nop
    mul.s      ft2, fv1, ft2
    add.s      ft1, ft1, ft2
    lwc1       ft2, 0x8(v1)
    mul.s      ft2, ft0, ft2
    add.s      ft1, ft1, ft2
    lwc1       ft2, 0xC(v1)
    beqz       t8, .L80031AA0
    add.s     ft1, ft1, ft2
    neg.s      ft1, ft1
    .L80031AA0:
    c.ole.s    ft1, ft3
    bc1fl      .L80031B1C
    addiu     t0, t0, -0x1
    addiu      t4, t4, -0x1
    bnez       t4, .L80031A48
    addiu     t2, t2, 0x2
    lwc1       fv0, 0x0(v0)
    lwc1       fv1, 0x4(v0)
    lwc1       ft1, 0x0(a1)
    mul.s      fv0, fv0, ft5
    lwc1       ft0, 0x8(v0)
    addiu      t6, t6, 0x1
    mul.s      fv1, fv1, ft5
    slti       $at, t6, 0xB
    addiu      t7, zero, 0x1
    mul.s      ft0, ft0, ft5
    sub.s      fv0, ft1, fv0
    lwc1       ft1, 0x4(a1)
    sub.s      fv1, ft1, fv1
    lwc1       ft1, 0x8(a1)
    bnez       $at, .L80031B08
    sub.s     ft0, ft1, ft0
    or         t7, zero, zero
    lwc1       fv0, 0x0(a0)
    lwc1       fv1, 0x4(a0)
    lwc1       ft0, 0x8(a0)
    .L80031B08:
    swc1       fv0, 0x0(a1)
    swc1       fv1, 0x4(a1)
    j          .L80031B24
    swc1      ft0, 0x8(a1)
    .L80031B18:
    addiu      t0, t0, -0x1
    .L80031B1C:
    bnez       t0, .L800319A0
    addiu     t1, t1, 0x4
    .L80031B24:
    bnez       t7, .L8003198C
    nop
    lw         t0, 0x10(sp)
    addiu      a0, a0, 0xC
    addiu      a1, a1, 0xC
    addiu      t0, t0, -0x1
    addiu      a2, a2, 0x4
    addiu      a3, a3, 0x1
    bnez       t0, .L80031620
    sw        t0, 0x10(sp)
    .L80031B4C:
    jr         ra
    lb        v0, 0x0(sp)
END(resolve_collisions)
