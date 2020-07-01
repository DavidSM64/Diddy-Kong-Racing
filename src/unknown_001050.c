/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80000450 */

#include "types.h"
#include "macros.h"

extern u8 D_800DC638;
extern s8 D_800DC670;
extern u8 D_80115D05;

extern s16 D_80115D30;

extern s32 D_800DC634;
extern s32 D_800DC648;
extern s32 D_800DC654;
extern s32 D_800DC658;
extern s32 D_80115D38;
extern s32 D_80115D3C;

extern s32* D_800DC630;

extern f32 D_800DC650;

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80000450.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80000890.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80000968.s")

void func_80000B18(void) {
    D_800DC648 = 1;
}

void func_80000B28(void) {
    D_800DC648 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80000B34.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80000BE0.s")

void func_80000C1C(void) {
    D_800DC670 = 1;
}

void func_80000C2C(void) {
    D_800DC670 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80000C38.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80000C98.s")

void func_80000CBC(void) {
    D_80115D38 = 0;
    D_80115D3C = 0;
    D_800DC650 = 1.0f;
    func_80001990(D_800DC638);
}

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80000D00.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80000FDC.s")

void func_80001050(void) {
    D_800DC658 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_8000105C.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001074.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001114.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_8000114C.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001170.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_800011A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_800011E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001268.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_800012A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_800012E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_800014BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001534.s")

s16 func_800015B8(void) {
    return D_80115D30;
}

s32 func_800015C8(void) {
    return (func_800C7A50(D_800DC630) == 1) & 0xFF;
}

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_800015F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001784.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_800017D4.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001844.s")

void func_800018E0(void) {
    if (func_80001C08() == 0) {
        D_80115D05 = 0;
        func_80002570(D_800DC634);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001918.s")

u8 func_80001980(void) {
    return D_80115D05;
}

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001990.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001A3C.s")

u8 func_80001AEC(void) {
    return D_800DC638;
}

s32 musicVolumeSliderPercentage(void) {
    return D_800DC654;
}

GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001B0C.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001B58.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001BC0.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001C08.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001CB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001D04.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001EA8.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001F14.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001FB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_800020E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80002110.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80002128.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_800021B0.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80002224.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_800022BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_8000232C.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80002570.s")
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80002608.s")
