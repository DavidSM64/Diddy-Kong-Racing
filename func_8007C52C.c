#include "ctx.c"

extern s32 D_80126358;
extern s32 gSpriteCache;

s32 func_8007C52C(s32 arg0) {
    s32 temp_v1;

    if ((arg0 < 0) || (arg0 >= D_80126358)) {
        return 0;
    }
    temp_v1 = (gSpriteCache + (arg0 * 8))->unk4;
    if (temp_v1 == -1) {
        return 0;
    }
    return temp_v1;
}
