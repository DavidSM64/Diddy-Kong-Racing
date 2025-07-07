#include "collision.h"

#include "macros.h"
#include "PR/R4300.h"
#include "textures_sprites.h"
#include "types.h"

/*******************************/

extern LevelModel *gCurrentLevelModel;

extern f32 gCollisionNormalX;
extern f32 gCollisionNormalY;
extern f32 gCollisionNormalZ;
extern s32 gHitWall;
extern s32 gCollisionMode;

extern s32 *gCollisionCandidates;
extern s8 *gCollisionSurfaces;
extern s32 gNumCollisionCandidates;

// All handwritten assembly, below.

#ifdef NON_MATCHING
/**
 * Populates a list of triangle candidates that will be tested for collision in resolve_collisions.
 * Calculates a single bounding rectangle that contains all origin and target points.
 * Then, terrain segments overlapping this rectangle are identified, and eligible triangles within them are selected.
 * Triangle batches are filtered based on visibility, surface type, and collision flags.
 */
void generate_collision_candidates(s32 numPoints, Vec3f *origins, Vec3f *targets, s32 vehicleID) {
    s32 minX, maxX, minZ, maxZ;
    s32 counter;
    LevelModelSegment *segments[10];
    s16 grid_mask[10];
    s32 i, j, batchIndex, triIndex;
    s32 surface;

    minX = 100000;
    maxX = -100000;
    minZ = 100000;
    maxZ = -100000;

    // Calculate a single bounding rectangle containing all origin and target points
    for (i = 0; i < numPoints; i++) {
        s32 x1 = origins[i].x;
        s32 z1 = origins[i].z;
        s32 x2 = targets[i].x;
        s32 z2 = targets[i].z;

        if (maxX < x1) {
            maxX = x1;
        }
        if (minX > x1) {
            minX = x1;
        }

        if (maxZ < z1) {
            maxZ = z1;
        }
        if (minZ > z1) {
            minZ = z1;
        }

        if (maxX < x2) {
            maxX = x2;
        }
        if (minX > x2) {
            minX = x2;
        }

        if (maxZ < z2) {
            maxZ = z2;
        }
        if (minZ > z2) {
            minZ = z2;
        }
    }

    // Add padding to ensure slight overlap with nearby geometry
    minX -= 20;
    maxX += 20;
    minZ -= 20;
    maxZ += 20;

    // Swap values if necessary (should never happen)
    if (maxX < minX) {
        s32 temp;

        temp = minX;
        minX = maxX;
        maxX = temp;
    }
    if (maxZ < minZ) {
        s32 temp;

        temp = minZ;
        minZ = maxZ;
        maxZ = temp;
    }

    // Select up to 10 terrain segments whose bounding boxes overlap the search rectangle (with 5 units tolerance)
    counter = 0;
    for (i = 0; i < gCurrentLevelModel->numberOfSegments; i++) {
        if (minX <= gCurrentLevelModel->segmentsBoundingBoxes[i].x2 + 5 &&
            maxX >= gCurrentLevelModel->segmentsBoundingBoxes[i].x1 - 5 &&
            minZ <= gCurrentLevelModel->segmentsBoundingBoxes[i].z2 + 5 &&
            maxZ >= gCurrentLevelModel->segmentsBoundingBoxes[i].z1 - 5) {

            grid_mask[counter] =
                compute_grid_overlap_mask(&gCurrentLevelModel->segmentsBoundingBoxes[i], minX, minZ, maxX, maxZ);
            segments[counter] = &gCurrentLevelModel->segments[i];
            counter++;
            if (counter == 10) {
                break;
            }
        }
    }

    // Populate the list of collision candidates
    j = 0;
    for (i = 0; i < counter; i++) {
        LevelModelSegment *seg = segments[i];

        // Insert the segment pointer encoded with MSB = 0 to differentiate from collision facets
        gCollisionCandidates[j] = (s32) K0_TO_PHYS(seg);
        j++;

        for (batchIndex = 0; batchIndex < seg->numberOfBatches; batchIndex++) {
            // Skip batches marked as non-collidable
            if (seg->batches[batchIndex].flags & RENDER_NO_COLLISION) {
                continue;
            }

            // Skip hidden surfaces for non-vehicle objects (e.g., projectiles, pickups)
            if (vehicleID == -1 && (seg->batches[batchIndex].flags & RENDER_HIDDEN)) {
                continue;
            }

            // Skip batches with no texture, since the surface type is stored in the texture data
            if (seg->batches[batchIndex].textureIndex == 255) {
                continue;
            }

            // Skip surfaces that are non-solid or selectively passable depending on the vehicle type:
            // - SURFACE_WATER_CALM is passable by all objects (treated like water surface).
            // - SURFACE_INVIS_WALL can be passed through only by planes.
            // - SURFACE_UNK12 is impassable only for cars, but passable by other vehicle types.
            surface = gCurrentLevelModel->textures[seg->batches[batchIndex].textureIndex].surfaceType;
            if (surface == SURFACE_WATER_CALM || (vehicleID == VEHICLE_PLANE && surface == SURFACE_INVIS_WALL) ||
                (vehicleID != VEHICLE_CAR && surface == SURFACE_UNK12)) {
                continue;
            }

            // Iterate over triangles in the batch and add eligible ones based on grid mask intersection
            for (triIndex = seg->batches[batchIndex].facesOffset; triIndex < seg->batches[batchIndex + 1].facesOffset;
                 triIndex++) {
                CollisionFacetPlanes *facet = &seg->collisionFacets[triIndex];

                // Check if the triangle's grid mask intersects with the bounding rectangle's grid mask
                if (((seg->unk10[triIndex] & grid_mask[i]) & 0x00FF) == 0 ||
                    ((seg->unk10[triIndex] & grid_mask[i]) & 0xFF00) == 0) {
                    continue;
                }

                gCollisionCandidates[j] = (s32) facet;
                gCollisionSurfaces[j] = surface;
                j++;

                if (j == MAX_COLLISION_CANDIDATES) {
                    goto out;
                }
            }
        }
    }

out:
    gNumCollisionCandidates = j;
}
#else
GLOBAL_ASM("asm/collision/generate_collision_candidates.s")
#endif

#ifdef NON_MATCHING
/**
 * Computes the overlap between a rectangle and a segment's bounding box, returning a 16-bit grid mask.
 * The bounding box is divided into an 8x8 grid. The function determines which grid columns (X) and rows (Z)
 * the input rectangle intersects.
 * The resulting 16-bit mask encodes this information:
 * - lower 8 bits represent intersections along the X-axis (1 bit per column),
 * - upper 8 bits represent intersections along the Z-axis (1 bit per row).
 */
s32 compute_grid_overlap_mask(LevelModelSegmentBoundingBox *bbox, s32 x1, s32 z1, s32 x2, s32 z2) {
    s32 mask = 0;
    s32 v1;
    s32 i;
    s32 cell_width;
    s32 cell_height;
    s32 cell_x, cell_z;
    s32 bbox_x1, bbox_z1, bbox_x2, bbox_z2;

    if (bbox == NULL) {
        return mask;
    }

    bbox_x1 = bbox->x1;
    bbox_z1 = bbox->z1;
    bbox_x2 = bbox->x2;
    bbox_z2 = bbox->z2;

    if (x2 < bbox_x1) {
        x2 = bbox_x1;
    }

    if (x1 < bbox_x1) {
        x1 = bbox_x1;
    }

    if (z2 < bbox_z1) {
        z2 = bbox_z1;
    }

    if (z1 < bbox_z1) {
        z1 = bbox_z1;
    }

    if (x2 > bbox_x2) {
        x2 = bbox_x2;
    }

    if (x1 > bbox_x2) {
        x1 = bbox_x2;
    }

    if (z2 > bbox_z2) {
        z2 = bbox_z2;
    }

    if (z1 > bbox_z2) {
        z1 = bbox_z2;
    }

    v1 = 1;

    cell_width = ((bbox_x2 - bbox_x1) >> 3) + 1;
    cell_x = bbox_x1;

    for (i = 0; i < 8; i++) {
        if (cell_x + cell_width >= x1 && x2 >= cell_x) {
            mask |= v1;
        }

        v1 <<= 1;
        cell_x += cell_width;
    }

    cell_height = ((bbox_z2 - bbox_z1) >> 3) + 1;
    cell_z = bbox_z1;

    for (i = 0; i < 8; i++) {
        if (cell_z + cell_height >= z1 && z2 >= bbox_z1) {
            mask |= v1;
        }

        v1 <<= 1;
        cell_z += cell_height;
    }

    return mask;
}
#else
GLOBAL_ASM("asm/collision/compute_grid_overlap_mask.s")
#endif

#ifdef NON_MATCHING
/**
 * Resolves collisions for a list of moving objects against previously identified collision candidates.
 * For each object, the function checks whether the path from `origin` to `target` intersects any collision plane.
 * If so, it adjusts the `target` position to resolve the collision, updates surface type, and sets output flags.
 * Returns a bitmask indicating which objects experienced a collision.
 */
s32 resolve_collisions(Vec3f *origin, Vec3f *target, f32 *radius, s8 *surface, s32 numEntries, s32 *numCollisions) {
    s32 i, j;
    f32 *collisionPlanes;
    f32 A, B, C, D;
    f32 A1, B1, C1, D1;
    CollisionFacetPlanes *facet;
    f32 targetDist;
    f32 originDist;
    f32 diffX, diffY, diffZ;
    f32 outX, outY, outZ;
    f32 intersectionFactor;
    f32 intersectionPointX, intersectionPointY, intersectionPointZ;
    s32 insideTriangle;
    u8 bitMask;
    s8 collisionMask;

    bitMask = 1;
    collisionMask = 0;
    gHitWall = FALSE;

    if (gNumCollisionCandidates == 0) {
        return 0;
    }

    // Step 1: forward collision resolution
    while (numEntries > 0) {
        s32 numCollidedSurfaces = 0;
        s32 continueSearch;

        do {
            continueSearch = FALSE;

            for (i = 0; i < gNumCollisionCandidates; i++) {
                if (gCollisionCandidates[i] >= 0) {
                    collisionPlanes = ((LevelModelSegment *) (PHYS_TO_K0(gCollisionCandidates[i])))->collisionPlanes;
                } else {
                    facet = (CollisionFacetPlanes *) gCollisionCandidates[i];
                    A = collisionPlanes[facet->basePlaneIndex * 4 + 0];
                    B = collisionPlanes[facet->basePlaneIndex * 4 + 1];
                    C = collisionPlanes[facet->basePlaneIndex * 4 + 2];
                    D = collisionPlanes[facet->basePlaneIndex * 4 + 3];

                    targetDist = (target->x * A + target->y * B + target->z * C + D) - *radius;
                    originDist = (origin->x * A + origin->y * B + origin->z * C + D) - *radius;

                    // Process only one-sided collisions (above -> below plane), with tolerance
                    if (targetDist < -0.1 && originDist >= -0.1) {
                        diffX = target->x - origin->x;
                        diffY = target->y - origin->y;
                        diffZ = target->z - origin->z;

                        if (targetDist != originDist) {
                            intersectionFactor = originDist / (originDist - targetDist);
                        } else {
                            intersectionFactor = 0.0f;
                        }

                        intersectionPointX = origin->x + diffX * intersectionFactor;
                        intersectionPointY = origin->y + diffY * intersectionFactor;
                        intersectionPointZ = origin->z + diffZ * intersectionFactor;

                        // Check if intersection point lies within triangle bounds
                        insideTriangle = TRUE;
                        for (j = 0; j < 3 && insideTriangle; j++) {
                            s32 flipSide = FALSE;
                            s32 edgeBisectorPlane = facet->edgeBisectorPlane[j];
                            f32 dist;

                            if (edgeBisectorPlane & 0x8000) {
                                flipSide = TRUE;
                                edgeBisectorPlane &= 0x7FFF;
                            }

                            A1 = collisionPlanes[edgeBisectorPlane * 4 + 0];
                            B1 = collisionPlanes[edgeBisectorPlane * 4 + 1];
                            C1 = collisionPlanes[edgeBisectorPlane * 4 + 2];
                            D1 = collisionPlanes[edgeBisectorPlane * 4 + 3];

                            dist = intersectionPointX * A1 + intersectionPointY * B1 + intersectionPointZ * C1 + D1;
                            if (flipSide) {
                                dist = -dist;
                            }

                            if (dist >= 4.0f) {
                                insideTriangle = FALSE;
                            }
                        }

                        if (insideTriangle) {
                            if (B >= 0.707f && gCollisionSurfaces[i] != SURFACE_STONE &&
                                gCollisionMode == COLLISION_MODE_DEFAULT) {
                                // Push up vertically if slope is gentle and not stone
                                outX = target->x;
                                outY = (*radius - (target->x * A + target->z * C + D)) / B;
                                outZ = target->z;
                            } else {
                                if (B < 0.45 && gCollisionMode != COLLISION_MODE_NO_WALLS) {
                                    // Wall-like surface: store collision normal
                                    gHitWall = TRUE;
                                    gCollisionNormalX = A;
                                    gCollisionNormalY = B;
                                    gCollisionNormalZ = C;
                                }

                                // Push out along surface normal
                                outX = target->x - A * targetDist;
                                outY = target->y - B * targetDist;
                                outZ = target->z - C * targetDist;
                            }

                            if (!gHitWall) {
                                gCollisionNormalX = A;
                                gCollisionNormalY = B;
                                gCollisionNormalZ = C;
                            }

                            // Store surface type with highest priority (higher ID wins)
                            if (*surface < gCollisionSurfaces[i]) {
                                *surface = gCollisionSurfaces[i];
                            }

                            continueSearch = TRUE;
                            numCollidedSurfaces++;
                            if (numCollidedSurfaces > 10) {
                                continueSearch = FALSE;
                                outX = origin->x;
                                outY = origin->y;
                                outZ = origin->z;
                            }

                            // Update target and recheck collisions
                            target->x = outX;
                            target->y = outY;
                            target->z = outZ;
                            break;
                        }
                    }
                }
            }
        } while (continueSearch);

        if (numCollidedSurfaces != 0) {
            (*numCollisions)++;
            collisionMask |= bitMask;
        }
        bitMask <<= 1;

        // Step 2: ensure object is fully pushed out from underneath
        numCollidedSurfaces = 0;
        do {
            continueSearch = FALSE;

            for (i = 0; i < gNumCollisionCandidates; i++) {
                if (gCollisionCandidates[i] >= 0) {
                    collisionPlanes = ((LevelModelSegment *) (PHYS_TO_K0(gCollisionCandidates[i])))->collisionPlanes;
                } else {
                    facet = (CollisionFacetPlanes *) gCollisionCandidates[i];
                    A = collisionPlanes[facet->basePlaneIndex * 4 + 0];
                    B = collisionPlanes[facet->basePlaneIndex * 4 + 1];
                    C = collisionPlanes[facet->basePlaneIndex * 4 + 2];
                    D = collisionPlanes[facet->basePlaneIndex * 4 + 3];

                    targetDist = (target->x * A + target->y * B + target->z * C + D) - *radius;
                    if (targetDist < -0.1 && targetDist > -(*radius + 3.0f)) {
                        insideTriangle = TRUE;
                        for (j = 0; j < 3 && insideTriangle; j++) {
                            s32 flipSide = FALSE;
                            s32 edgePlaneIndex = facet->edgeBisectorPlane[j];
                            f32 dist;

                            if (edgePlaneIndex & 0x8000) {
                                flipSide = TRUE;
                                edgePlaneIndex &= 0x7FFF;
                            }

                            A1 = collisionPlanes[edgePlaneIndex * 4 + 0];
                            B1 = collisionPlanes[edgePlaneIndex * 4 + 1];
                            C1 = collisionPlanes[edgePlaneIndex * 4 + 2];
                            D1 = collisionPlanes[edgePlaneIndex * 4 + 3];

                            dist = target->x * A1 + target->y * B1 + target->z * C1 + D1;
                            if (flipSide) {
                                dist = -dist;
                            }

                            if (dist >= 4.0f) {
                                insideTriangle = FALSE;
                            }
                        }

                        if (insideTriangle) {
                            outX = target->x - A * targetDist;
                            outY = target->y - B * targetDist;
                            outZ = target->z - C * targetDist;

                            continueSearch = TRUE;
                            numCollidedSurfaces++;
                            if (numCollidedSurfaces > 10) {
                                continueSearch = FALSE;
                                outX = origin->x;
                                outY = origin->y;
                                outZ = origin->z;
                            }

                            target->x = outX;
                            target->y = outY;
                            target->z = outZ;
                            break;
                        }
                    }
                }
            }
        } while (continueSearch);

        // Advance to next entry
        numEntries--;
        origin++;
        target++;
        radius++;
        surface++;
    }

    return collisionMask;
}
#else
GLOBAL_ASM("asm/collision/resolve_collisions.s")
#endif
