#include "collision.h"

#include "types.h"
#include "macros.h"
#include "textures_sprites.h"

/*******************************/

extern LevelModel *gCurrentLevelModel;

extern f32 D_8011B0E4;
extern f32 D_8011B0E8;
extern f32 D_8011B0EC;
extern s32 D_8011B0F0;
extern s32 D_8011B0F4;

extern s32 *gCollisionCandidates;
extern s8 *gCollisionSurfaces;
extern s32 gNumCollisionCandidates;

// All handwritten assembly, below.

#ifdef NON_EQUIVALENT
void func_80031130(s32 arg0, Vec3f *arg1, Vec3f *arg2, s32 arg3) {
    s32 i;
    s32 s5, s4, s3, s2;
    s32 counter;
    LevelModelSegment *sp48[10];
    s16 sp34[10];
    s32 i, j, batchIndex, triIndex;
    s32 t2;

    s5 = 100000;
    s4 = -100000;
    s3 = 100000;
    s2 = -100000;

    for (i = 0; i < arg0; i++) {
        s32 x1 = arg1[i].x;
        s32 z1 = arg1[i].z;
        s32 x2 = arg2[i].x;
        s32 z2 = arg2[i].z;

        if (s4 < x1) {
            s4 = x1;
        }
        if (s5 > x1) {
            s5 = x1;
        }

        if (s2 < z1) {
            s2 = z1;
        }
        if (s3 > z1) {
            s3 = z1;
        }

        if (s4 < x2) {
            s4 = x2;
        }
        if (s5 > x2) {
            s5 = x2;
        }

        if (s2 < z2) {
            s2 = z2;
        }
        if (s3 > z2) {
            s3 = z2;
        }
    }

    s5 -= 20;
    s4 += 20;
    s3 -= 20;
    s2 += 20;

    if (s4 < s5) {
        s32 temp;

        temp = s5;
        s5 = s4;
        s4 = temp;
    }
    if (s2 < s3) {
        s32 temp;

        temp = s3;
        s3 = s2;
        s2 = temp;
    }

    counter = 0;
    for (i = 0; i < gCurrentLevelModel->numberOfSegments; i++) {
        if (s5 <= gCurrentLevelModel->segmentsBoundingBoxes[i].x2 + 5 &&
            s4 >= gCurrentLevelModel->segmentsBoundingBoxes[i].x1 - 5 &&
            s3 <= gCurrentLevelModel->segmentsBoundingBoxes[i].z2 + 5 &&
            s2 >= gCurrentLevelModel->segmentsBoundingBoxes[i].z1 - 5) {
            sp34[counter] = func_800314DC(&gCurrentLevelModel->segmentsBoundingBoxes[i], s5, s3, s4, s2);
            sp48[counter] = &gCurrentLevelModel->segments[i];
            if (counter == 10) {
                break;
            }
        }
    }

    j = 0;
    for (i = 0; i < counter; i++) {
        LevelModelSegment *seg = sp48[i];

        gCollisionCandidates[j] = (s32) seg & ~0x80000000;
        j++;

        for (batchIndex = 0; batchIndex < seg->numberOfBatches; batchIndex++) {
            if (seg->batches[batchIndex].flags & RENDER_UNK_200) {
                continue;
            }
            if (arg3 == -1 && (seg->batches[batchIndex].flags & RENDER_HIDDEN)) {
                continue;
            }

            t2 = 0;
            if (seg->batches[batchIndex].textureIndex != 255) {
                t2 = gCurrentLevelModel->textures[seg->batches[batchIndex].textureIndex].unk7;
                if (t2 == 11 || arg3 == 2 && t2 == 17 || arg3 != 0 && t2 == 18) {
                    continue;
                }

                for (triIndex = seg->batches[batchIndex].facesOffset;
                     triIndex < seg->batches[batchIndex + 1].facesOffset; triIndex++) {
                    CollisionNode *colNode = &seg->unk14[triIndex];

                    if (((seg->unk10[triIndex] & sp34[i]) & 0x00FF) == 0 ||
                        ((seg->unk10[triIndex] & sp34[i]) & 0xFF00) == 0) {
                        continue;
                    }

                    gCollisionCandidates[j] = (s32) colNode;
                    gCollisionSurfaces[j] = t2;
                    j++;

                    if (j == 500) {
                        goto out;
                    }
                }
            }
        }
    }

out:
    gNumCollisionCandidates = j;
    return 0;
}
#else
GLOBAL_ASM("asm/collision/func_80031130.s")
#endif

// Might be segment related.
#ifdef NON_EQUIVALENT
s32 func_800314DC(LevelModelSegmentBoundingBox *segment, s32 x1, s32 z1, s32 x2, s32 z2) {
    s32 v0 = 0;
    s32 v1;
    s32 t0, t1, t2, t3, t4;

    if (segment == NULL) {
        return v0;
    }

    t0 = segment->x1;
    t1 = segment->z1;
    t2 = segment->x2;
    t3 = segment->z2;

    if (x2 < t0) {
        x2 = t0;
    }

    if (x1 < t0) {
        x1 = t0;
    }

    if (z2 < t1) {
        z2 = t1;
    }

    if (z1 < t1) {
        z1 = t1;
    }

    if (t2 < x2) {
        x2 = t2;
    }

    if (t2 < x1) {
        x1 = t2;
    }

    if (t3 < z2) {
        z2 = t3;
    }

    if (t3 < z1) {
        z1 = t3;
    }

    v1 = 1;

    t2 = ((t2 - t0) >> 3) + 1;
    t4 = t2 + t0;

    while (v1 < (1 << 8)) {
        if (t4 >= x1 && x2 >= t0) {
            v0 |= v1;
        }

        v1 <<= 1;
        t4 += t2;
        t0 += t2;
    }

    t2 = ((t3 - t1) >> 3) + 1;
    t4 = t2 + t1;

    while (v1 < (1 << 16)) {
        if (t4 >= z1 && z2 >= t1) {
            v0 |= v1;
        }

        v1 <<= 1;
        t4 += t2;
        t1 += t2;
    }

    return v0;
}
#else
GLOBAL_ASM("asm/collision/func_800314DC.s")
#endif

// Player collision for the current segment
#ifdef NON_EQUIVALENT
void func_80031600(Vec3f *origin, Vec3f *target, f32 *radius, s8 *surface, s32 numEntries, s32 *numCollisions) {
    s32 i, j;
    f32 *colPlanes;
    f32 A, B, C, D;
    f32 A1, B1, C1, D1;
    CollisionNode *t2;
    f32 f18;
    f32 f16;
    f32 diffX, diffY, diffZ;
    f32 x1, y1, z1;
    f32 f10;
    f32 colPointX, colPointY, colPointZ;
    s32 insideTriangle;
    u8 sp1;
    s8 sp0;

    sp1 = 1;
    sp0 = 0;
    D_8011B0F0 = FALSE;

    if (gNumCollisionCandidates == 0) {
        return 0;
    }

    while (numEntries > 0) {
        s32 t6 = 0;
        s32 t7;

        do {
            t7 = FALSE;

            for (i = 0; i < gNumCollisionCandidates; i++) {
                if (gCollisionCandidates[i] >= 0) {
                    colPlanes = ((LevelModelSegment *) (gCollisionCandidates[i] | 0x80000000))->unk18;
                } else {
                    t2 = (CollisionNode *) gCollisionCandidates[i];
                    A = colPlanes[t2->colPlaneIndex * 4 + 0];
                    B = colPlanes[t2->colPlaneIndex * 4 + 1];
                    C = colPlanes[t2->colPlaneIndex * 4 + 2];
                    D = colPlanes[t2->colPlaneIndex * 4 + 3];

                    f18 = (target->x * A + target->y * B + target->z * C + D) - *radius;
                    f16 = (origin->x * A + origin->y * B + origin->z * C + D) - *radius;
                    if (f18 < -0.1 && f16 >= -0.1) {
                        diffX = target->x - origin->x;
                        diffY = target->y - origin->y;
                        diffZ = target->z - origin->z;

                        if (f18 != f16) {
                            f10 = f16 / (f16 - f18);
                        } else {
                            f10 = 0.0f;
                        }

                        colPointX = origin->x + diffX * f10;
                        colPointY = origin->y + diffY * f10;
                        colPointZ = origin->z + diffZ * f10;

                        insideTriangle = TRUE;
                        for (j = 0; j < 3 && insideTriangle; j++) {
                            s32 flipSide = FALSE;
                            s32 edgePlaneIndex = t2->closestTri[j];
                            f32 dist;

                            if (edgePlaneIndex & 0x8000) {
                                flipSide = TRUE;
                                edgePlaneIndex &= 0x7FFF;
                            }

                            A1 = colPlanes[edgePlaneIndex * 4 + 0];
                            B1 = colPlanes[edgePlaneIndex * 4 + 1];
                            C1 = colPlanes[edgePlaneIndex * 4 + 2];
                            D1 = colPlanes[edgePlaneIndex * 4 + 3];

                            dist = colPointX * A1 + colPointY * B1 + colPointX * C1 + D1;
                            if (flipSide) {
                                dist = -dist;
                            }

                            if (dist >= 4.0f) {
                                insideTriangle = FALSE;
                            }
                        }

                        if (insideTriangle) {
                            if (B >= 0.707 && gCollisionSurfaces[i] != 4 && D_8011B0F4 == 0) {
                                x1 = target->x;
                                y1 = (*radius - (target->x * A + target->z * C + D)) / B;
                                z1 = target->z;
                            } else {
                                if (B < 0.45 && D_8011B0F4 != 2) {
                                    D_8011B0F0 = TRUE;
                                    x1 = D_8011B0E4 = A;
                                    y1 = D_8011B0E8 = B;
                                    z1 = D_8011B0EC = C;
                                }

                                x1 = target->x - A * f18;
                                y1 = target->y - B * f18;
                                z1 = target->z - C * f18;
                            }

                            if (!D_8011B0F0) {
                                D_8011B0E4 = A;
                                D_8011B0E8 = B;
                                D_8011B0EC = C;
                            }

                            if (*surface < gCollisionSurfaces[i]) {
                                *surface = gCollisionSurfaces[i];
                            }

                            t7 = TRUE;
                            t6++;
                            if (t6 > 10) {
                                t7 = FALSE;
                                x1 = origin->x;
                                y1 = origin->y;
                                z1 = origin->z;
                            }

                            target->x = x1;
                            target->y = y1;
                            target->z = z1;
                            break;
                        }
                    }
                }
            }
        } while (t7);

        if (t6 != 0) {
            (*numCollisions)++;
            sp0 |= sp1;
        }
        sp1 <<= 1;

        t6 = 0;

        do {
            t7 = FALSE;

            for (i = 0; i < gNumCollisionCandidates; i++) {
                if (gCollisionCandidates[i] >= 0) {
                    colPlanes = ((LevelModelSegment *) (gCollisionCandidates[i] | 0x80000000))->unk18;
                } else {
                    t2 = (CollisionNode *) gCollisionCandidates[i];
                    A = colPlanes[t2->colPlaneIndex * 4 + 0];
                    B = colPlanes[t2->colPlaneIndex * 4 + 1];
                    C = colPlanes[t2->colPlaneIndex * 4 + 2];
                    D = colPlanes[t2->colPlaneIndex * 4 + 3];

                    f18 = (target->x * A + target->y * B + target->z * C + D) - *radius;
                    if (f18 < -0.1 && f18 > -(*radius + 3.0f)) {

                        insideTriangle = TRUE;
                        for (j = 0; j < 3 && insideTriangle; j++) {
                            s32 flipSide = FALSE;
                            s32 edgePlaneIndex = t2->closestTri[j];
                            f32 dist;

                            if (edgePlaneIndex & 0x8000) {
                                flipSide = TRUE;
                                edgePlaneIndex &= 0x7FFF;
                            }

                            A1 = colPlanes[edgePlaneIndex * 4 + 0];
                            B1 = colPlanes[edgePlaneIndex * 4 + 1];
                            C1 = colPlanes[edgePlaneIndex * 4 + 2];
                            D1 = colPlanes[edgePlaneIndex * 4 + 3];

                            dist = target->x * A1 + target->y * B1 + target->z * C1 + D1;
                            if (flipSide) {
                                dist = -dist;
                            }

                            if (dist >= 4.0f) {
                                insideTriangle = FALSE;
                            }
                        }

                        if (insideTriangle) {
                            x1 = target->x - A * f18;
                            y1 = target->y - B * f18;
                            z1 = target->z - C * f18;

                            t7 = TRUE;
                            t6++;
                            if (t6 > 10) {
                                t7 = FALSE;
                                x1 = origin->x;
                                y1 = origin->y;
                                z1 = origin->z;
                            }

                            target->x = x1;
                            target->y = y1;
                            target->z = z1;
                            break;
                        }
                    }
                }
            }
        } while (t7);

        numEntries--;
        origin++;
        target++;
        radius++;
        surface++;
    }

    return sp0;
}
#else
GLOBAL_ASM("asm/collision/func_80031600.s")
#endif
