/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80002660 */

#include "types.h"
#include "macros.h"

/* Unknown Size */
typedef struct unk800DC6BC {
    u8  pad00[0x44];
    s32 unk44;
    s32 unk48;
} unk800DC6BC;

extern unk800DC6BC* D_800DC6BC;
extern s32 D_800DC6C0;

extern s32* D_80115FB0;

GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80002660.s")

void func_80002A50(void) {
    osStartThread(&D_80115FB0);
}

void func_80002A74(void) {
    osStopThread(&D_80115FB0);
}

GLOBAL_ASM("asm/non_matchings/unknown_003260/D_80002A98.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80002C00.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80002DF8.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/D_80002E38.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/D_80003008.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80003040.s")

void func_80003160(u32 arg0) {
    if (arg0 > 256) {
        arg0 = 256;
    }

    D_800DC6C0 = arg0;
}

s32 sfxVolumeSliderPercentage(void) {
    return D_800DC6C0;
}

void func_8000318C(s32 arg0) {
    if (D_800DC6BC->unk44 >= arg0) {
        D_800DC6BC->unk48 = arg0;
    } else {
        D_800DC6BC->unk48 = D_800DC6BC->unk44;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_003260/func_800031C0.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/D_800033C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80003470.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_8000410C.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_8000418C.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_800041FC.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_800042CC.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80004384.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80004520.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80004604.s")

void func_80004638(s32 arg0, s16 arg1, s32 arg2) {
    func_80004668(arg0, arg1, 0, arg2);
}

GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80004668.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_8000488C.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_800048D8.s")

void func_800049D8(void) {
    func_800048D8(3);
}

GLOBAL_ASM("asm/non_matchings/unknown_003260/func_800049F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80004A60.s")
