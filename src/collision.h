#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "types.h"
#include "structs.h"

void func_80031130(s32, f32 *, f32 *, s32);
s32 func_800314DC(LevelModelSegmentBoundingBox *segment, s32 x1, s32 z1, s32 x2, s32 z2);
s32 func_80031600(Vec3f *pos, Vec3f *pos2, f32 *radius, s8 *surface, s32 numEntries, s32 *numCollisions);

#endif
