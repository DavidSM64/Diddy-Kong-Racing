/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80063C30 */

#include "types.h"
#include "macros.h"

extern s32 D_80065900;
extern s32 alAuxBusParam;
extern s32 D_800CA0D0;
extern s32 alEnvmixerParam;
extern s32 alLoadParam;
extern s32 D_800CBBEC;
extern s32 alResampleParam;
extern s32 D_800CC17C;
extern s32 D_800CC390;
extern s32 D_800CC3C0;
extern s32 alSaveParam;
extern s32 D_800CC514;

GLOBAL_ASM("asm/non_matchings/unknown_064830/D_80063C30.s")

s32 D_80063F94(s32* arg0, s32 arg1, s32 arg2) {
    if (arg1 == 1) {
        *arg0 = arg2;
    }
    return 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_064830/D_80063FAC.s")
GLOBAL_ASM("asm/non_matchings/unknown_064830/func_80064224.s")
GLOBAL_ASM("asm/non_matchings/unknown_064830/func_800644A0.s")
GLOBAL_ASM("asm/non_matchings/unknown_064830/func_80064638.s")
GLOBAL_ASM("asm/non_matchings/unknown_064830/func_800647D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_064830/func_80064884.s")
GLOBAL_ASM("asm/non_matchings/unknown_064830/func_8006492C.s")
GLOBAL_ASM("asm/non_matchings/unknown_064830/func_80064950.s")
GLOBAL_ASM("asm/non_matchings/unknown_064830/func_80064A08.s")

typedef struct unk80064E54 {
    u8  unk00[0x14]; // unknown
    s32 unk14;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    u8  unk2A[0x04]; // unknown
    s16 unk2E;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
} unk80064E54;

void alEnvmixerNew(unk80064E54* arg0, s32 arg1) {
    func_800CA0B0(arg0, &D_800CA0D0, &alEnvmixerParam, 4);
    arg0->unk14 = alHeapDBAlloc(0, 0, arg1, 1, 0x50);
    arg0->unk38 = 1;
    arg0->unk48 = 0;
    arg0->unk1A = 1;
    arg0->unk28 = 1;
    arg0->unk2E = 1;
    arg0->unk1C = 1;
    arg0->unk1E = 1;
    arg0->unk20 = 0;
    arg0->unk22 = 0;
    arg0->unk26 = 1;
    arg0->unk24 = 0;
    arg0->unk30 = 0;
    arg0->unk34 = 0;
    arg0->unk18 = 0;
    arg0->unk3C = 0;
    arg0->unk40 = 0;
    arg0->unk44 = 0;
}

typedef struct unk80064EF8 {
    u8  unk00[0x14]; // unknown
    s32 unk14;
    s32 unk18;
    u8  unk1C[0x14]; // unknown
    s32 unk30;
    s32 unk34;
    u8  unk38[0x04]; // unknown
    s32 unk3C;
    s32 unk40;
    s32 unk44;
} unk80064EF8;

void alLoadNew(unk80064EF8* arg0, s32 (*arg1)(s32*), s32 arg2) {
    func_800CA0B0(arg0, &D_800CBBEC, &alLoadParam, 0);
    arg0->unk14 = alHeapDBAlloc(0, 0, arg2, 1, 0x20);
    arg0->unk18 = alHeapDBAlloc(0, 0, arg2, 1, 0x20);
    arg0->unk30 = arg1(&arg0->unk34);
    arg0->unk3C = 0;
    arg0->unk40 = 1;
    arg0->unk44 = 0;
}

typedef struct unk80064F9C {
    u8  unk00[0x14]; // unknown
    s32 unk14;
    f32 unk18;
    s32 unk1C;
    f32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
} unk80064F9C;

void alResampleNew(unk80064F9C* arg0, s32 arg1) {
    func_800CA0B0(arg0, &D_800CC17C, &alResampleParam, 1);
    arg0->unk14 = alHeapDBAlloc(0, 0, arg1, 1, 0x20);
    arg0->unk24 = 1;
    arg0->unk30 = 0;
    arg0->unk1C = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk20 = 0.0f;
    arg0->unk18 = 1.0f;
}

typedef struct unk80065024 {
    u8  unk00[0x14]; // unknown
    s32 unk14;
    s32 unk18;
    s32 unk1C;
} unk80065024;

void alAuxBusNew(unk80065024* arg0, s32 arg1, s32 arg2) {
    func_800CA0B0(arg0, &D_80065900, &alAuxBusParam, 6);
    arg0->unk14 = 0;
    arg0->unk18 = arg2;
    arg0->unk1C = arg1;
}

typedef struct unk80065084 {
    u8  unk00[0x14]; // unknown
    s32 unk14;
    s32 unk18;
    s32 unk1C;
} unk80065084;

void alMainBusNew(unk80065084* arg0, s32 arg1, s32 arg2) {
    func_800CA0B0(arg0, &D_800CC3C0, &D_800CC390, 7);
    arg0->unk14 = 0;
    arg0->unk18 = arg2;
    arg0->unk1C = arg1;
}

typedef struct unk800650E4 {
    u8  unk00[0x14]; // unknown
    s32 unk14;
    s32 unk18;
} unk800650E4;

void alSaveNew(unk800650E4* arg0) {
    func_800CA0B0(arg0, &D_800CC514, &alSaveParam, 3);
    arg0->unk14 = 0;
    arg0->unk18 = 1;
}
