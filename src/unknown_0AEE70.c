/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800AE270 */

#include "types.h"

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


