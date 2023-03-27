/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B3140 */

#include "unknown_0B3D40.h"
#include "macros.h"
#include "objects.h"
#include "particles.h"

GLOBAL_ASM("asm/non_matchings/printf/func_800B3140.s")
GLOBAL_ASM("asm/non_matchings/printf/func_800B3240.s")
GLOBAL_ASM("asm/non_matchings/printf/func_800B3358.s")
GLOBAL_ASM("asm/non_matchings/printf/func_800B34B0.s")
GLOBAL_ASM("asm/non_matchings/printf/func_800B3564.s")

UNUSED void func_800B3678(Gfx **arg0, MatrixS **arg1, Vertex **arg2) {
    UNUSED s32 pad;
    UNUSED s32 pad2;
    Object **objects;
    s32 iObj;
    s32 nObjs;

    objects = objGetObjList(&iObj, &nObjs);
    for (; iObj < nObjs; iObj++) {
        if (objects[iObj]->segment.trans.unk6 & 0x8000) {
            if ((s32) objects[iObj]->segment.header & 0x8000) {
                func_800B3740(objects[iObj], arg0, arg1, arg2, 0);
            }
        }
    }
}

GLOBAL_ASM("asm/non_matchings/printf/func_800B3740.s")
GLOBAL_ASM("asm/non_matchings/printf/func_800B3E64.s")

UNUSED unk800E2CF0 *func_800B4488(s32 idx) {
    if (idx < gParticlesAssetTableCount) {
        return gParticlesAssetTable[idx];
    }
    return gParticlesAssetTable[gParticlesAssetTableCount - 1];
}

UNUSED unk800E2CF0 *func_800B44D4(s32 *idx) {
    *idx = *idx + 1;
    while (*idx >= gParticlesAssetTableCount) {
        *idx = *idx - gParticlesAssetTableCount;
    }
    return gParticlesAssetTable[*idx];
}

UNUSED unk800E2CF0 *func_800B452C(s32 *arg0) {
    for (*arg0 = *arg0 - 1; *arg0 < 0; *arg0 += gParticlesAssetTableCount);
    return gParticlesAssetTable[*arg0];
}

UNUSED ParticleBehavior *func_800B4578(s32 idx) {
    if (idx < gParticleBehavioursAssetTableCount) {
        return gParticleBehavioursAssetTable[idx];
    }
    return gParticleBehavioursAssetTable[gParticleBehavioursAssetTableCount - 1];
}

GLOBAL_ASM("asm/non_matchings/printf/func_800B45C4.s")
GLOBAL_ASM("asm/non_matchings/printf/func_800B461C.s")
GLOBAL_ASM("asm/non_matchings/printf/func_800B4668.s")
GLOBAL_ASM("asm/non_matchings/printf/func_800B46BC.s")
