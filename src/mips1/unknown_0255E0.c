/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800249E0 */

#include "types.h"
#include "macros.h"

extern s32 D_800DC924;
extern s32 D_8011D37C;
extern s32 D_8011D474;
extern s32 D_8011B0DC;
extern s32 D_8011B0F0;
extern s32 D_8011B0F4;
extern s32 D_8011B0FC;

extern f32 D_8011B0E4;
extern f32 D_8011B0E8;
extern f32 D_8011B0EC;

extern s32* D_800DC918;

s32 func_800249E0(s32 arg0) {
    D_8011D37C = arg0;
    return 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800249F0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/D_80024D54.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80025510.s")

void func_800257D0(void) {
    if (D_800DC924 != 0) {
        func_80071140(D_8011D474);
        func_80071140(D_800DC924);
        D_800DC924 = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002581C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80026070.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80026430.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80026C14.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80026E54.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80027184.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80027568.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800278E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80027E24.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80027FC4.s")

void func_80028044(s32 arg0) {
    D_8011B0DC = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80028050.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800289B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80028C10.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80028CD0.s")

void func_80028FA0(s32 arg0) {
    D_8011B0FC = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80028FAC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80029658.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80029AF8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80029D14.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80029F18.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002A05C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002A134.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002A2DC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002A31C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002A5F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002A900.s")

void func_8002ACC8(s32 arg0) {
    D_8011B0F4 = arg0;
}

s32 func_8002ACD4(f32* arg0, f32* arg1, f32* arg2) {
    *arg0 = D_8011B0E4;
    *arg1 = D_8011B0E8;
    *arg2 = D_8011B0EC;
    return D_8011B0F0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002AD08.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002B0F4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002B9BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002BAB0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002C0C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002C71C.s")

s32* func_8002C7C4(void) {
    return D_800DC918;
}

GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002C7D4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002C954.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002CC30.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002D30C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002D384.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002D670.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002D8DC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002DE30.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002E234.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002E904.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002EEEC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002F2AC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002F440.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002FA64.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002FD74.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8002FF6C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800304C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030664.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030750.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800307BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030838.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_8003093C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030A74.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80030DE0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80031018.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80031130.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800314DC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80031600.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_800318C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80031944.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80031954.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80031B18.s")
GLOBAL_ASM("asm/non_matchings/unknown_0255E0/func_80031B24.s")
