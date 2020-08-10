/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80002660 */

#include "types.h"
#include "macros.h"
#include "audio_internal.h"
#include "libultra_internal.h"

extern void D_80002A98(void*);
extern u32 D_80003008;

/* Unknown Size */
typedef struct unk800DC6BC {
    u8  pad00[0x44];
    s32 unk44;
    s32 unk48;
} unk800DC6BC;

extern unk800DC6BC* D_800DC6BC;
extern s32 D_800DC6C0;
extern s32 D_80115F90;
extern ALHeap* D_80115F94;
extern OSThread D_80115FB0;
extern OSMesgQueue D_80116160;
extern OSMesg D_80116178;
extern OSMesgQueue D_80116198;
extern OSMesg D_801161B0;
extern s32 D_80119230;
extern OSMesgQueue D_80119AF0;
extern OSMesg D_80119B08;
extern f32 D_80126170;

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80002660.s")
#else
    void func_80002660(ALSynConfig* c, OSPri p, s32 arg2){
        D_80115F90 = arg2;
        D_80115F94 = c->heap;
        c->dmaproc = &D_80003008;
        c->outputRate = func_800C8600(22050);

        alHeapDBAlloc(0,0, c->heap, 1, 120);

        osCreateMesgQueue(&D_80116198, &D_801161B0, 8);
        osCreateMesgQueue(&D_80116160, &D_80116178, 8);
        osCreateMesgQueue(&D_80119AF0, &D_80119B08, 50);

        osCreateThread(&D_80115FB0, 4, &D_80002A98, NULL, &D_80119230, p);
    }
#endif

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
GLOBAL_ASM("asm/non_matchings/unknown_003260/_sndpVoiceHandler.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/_handleEvent.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_8000410C.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_8000418C.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_800041FC.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_800042CC.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80004384.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80004520.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80004604.s")

void func_80004638(ALBank* bnk, s16 arg1, s32 arg2) {
    func_80004668(bnk, arg1, 0, arg2);
}

GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80004668.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_8000488C.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_800048D8.s")

void func_800049D8(void) {
    func_800048D8(3);
}

GLOBAL_ASM("asm/non_matchings/unknown_003260/func_800049F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80004A60.s")
