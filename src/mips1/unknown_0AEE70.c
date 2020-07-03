/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800AE270 */

#include "types.h"
#include "macros.h"

// Not sure what kind of pointers these are.
extern s32* D_800E2CA8;
extern s32* D_800E2CB4;
extern s32* D_800E2CC0;
extern s32* D_800E2CCC;
extern s32* D_800E2CD8;
extern s32* D_800E2CE0;
extern s32* D_800E2CE4;
extern s32* D_800E2CEC;
extern s32* D_800E2CF0;
extern s32* D_800E2CF8;
extern s32* D_800E2CFC;

extern s32* D_800E2E60;
extern s32  D_800E2E64;

void func_800AE2D8(void);
void func_800AE374(void);
void func_800AE438(void);
void func_800AE490(void);

void func_800AE270(void) {
    func_800AE374();
    func_800AE438();
    func_800AE2D8();
}

void func_800AE2A0(void) {
    func_800AE374();
    func_800AE438();
    func_800AE490();
    func_800AE2D8();
}

void func_800AE2D8(void) {
    s32 phi_s1;
    s32 phi_s0;

    if (D_800E2E60 != NULL) {
        phi_s1 = 0;
        phi_s0 = 0;
        if (D_800E2E64 > 0) {
            do {
                func_8007CCB0(*(D_800E2E60 + phi_s1));
                phi_s0 += 1;
                phi_s1 += 1;
            } while (phi_s0 < D_800E2E64);
        }
        func_80071140(D_800E2E60);
        D_800E2E60 = 0;
    }
}

void func_800AE374(void) {
    if (D_800E2CA8 != NULL) {
        func_80071140(D_800E2CA8);
        D_800E2CA8 = NULL;
    }
    if (D_800E2CB4 != NULL) {
        func_80071140(D_800E2CB4);
        D_800E2CB4 = NULL;
    }
    if (D_800E2CC0 != NULL) {
        func_80071140(D_800E2CC0);
        D_800E2CC0 = NULL;
    }
    if (D_800E2CCC != NULL) {
        func_80071140(D_800E2CCC);
        D_800E2CCC = NULL;
    }
    if (D_800E2CD8 != NULL) {
        func_80071140(D_800E2CD8);
        D_800E2CD8 = NULL;
    }
}

void func_800AE438(void) {
    if (D_800E2CE0 != NULL) {
        func_80071140(D_800E2CE0);
        D_800E2CE0 = NULL;
    }
    if (D_800E2CE4 != NULL) {
        func_80071140(D_800E2CE4);
        D_800E2CE4 = NULL;
    }
}

void func_800AE490(void) {
    if (D_800E2CEC != NULL) {
        func_80071140(D_800E2CEC);
        D_800E2CEC = NULL;
    }
    if (D_800E2CF0 != NULL) {
        func_80071140(D_800E2CF0);
        D_800E2CF0 = NULL;
    }
    if (D_800E2CF8 != NULL) {
        func_80071140(D_800E2CF8);
        D_800E2CF8 = NULL;
    }
    if (D_800E2CFC != NULL) {
        func_80071140(D_800E2CFC);
        D_800E2CFC = NULL;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AE530.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AE728.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AEE14.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AEEB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AEF88.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF024.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF0A4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF0F0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF134.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF1E0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF29C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF404.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF52C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF6E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF714.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AFC3C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AFE5C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B0010.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B03C0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B0698.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B0BAC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B1130.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B1CB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B2040.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B2260.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B22FC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B263C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B26E0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B2FBC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B3140.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B3240.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B3358.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B34B0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B3564.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B3740.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B3E64.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B4668.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B46BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B4940.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B4A08.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B4A40.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B5E88.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B5EDC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B5F78.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B62B4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B635C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B653C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B695C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B69FC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B6E50.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B6EE0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B6F04.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B6F40.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B6F50.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/D_800B6FC4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B70D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B7144.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B71B0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B7460.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B76B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B76DC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B77D4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B7810.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B7D10.s")
