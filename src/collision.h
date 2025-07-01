#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "types.h"
#include "structs.h"

#define MAX_COLLISION_CANDIDATES 500

enum CollisionModes { COLLISION_MODE_DEFAULT, COLLISION_MODE_1, COLLISION_MODE_NO_WALLS };

void generate_collision_candidates(s32, f32 *, f32 *, s32);
s32 compute_grid_overlap_mask(LevelModelSegmentBoundingBox *segment, s32 x1, s32 z1, s32 x2, s32 z2);
s32 resolve_collisions(Vec3f *pos, Vec3f *pos2, f32 *radius, s8 *surface, s32 numEntries, s32 *numCollisions);

#endif
