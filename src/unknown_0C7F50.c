/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C7350 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

extern s32 D_800E3770; // boolean
extern s32 D_800E3774;
extern s32 D_800E3778;
extern s32 D_800E377C;

extern OSMesgQueue D_8012ACA0;
extern OSMesg D_8012ACB8;
extern OSThread D_8012AAF0;
extern void *D_8012CCC0;

void func_800C74A0(void *arg);

void func_800C7350(void) {
    osCreateMesgQueue(&D_8012ACA0, &D_8012ACB8, 2);
    osCreateThread(&D_8012AAF0, 0x1E, &func_800C74A0, 0, &D_8012CCC0, 8);
    osStartThread(&D_8012AAF0);
}

void func_800C73BC(void) {
    osStopThread(&D_8012AAF0);
}

s32 func_800C73E0(void) {
    return D_800E3770;
}

void func_800C73F0(void) {
    s32 temp_t7;

    if (D_800E3770) {
        if (D_800E377C > 0) {
            D_800E377C--;
            if (D_800E377C == 0) {
                osSendMesg(&D_8012ACA0, (OSMesg)10, 0);
            }
        }
    }
}

// Unused?
s32 func_800C7448(void) {
    return D_800E377C;
}

s32 func_800C7458(s32 arg0, s32 arg1) {
    if (!D_800E3770) {
        D_800E377C = 4;
        D_800E3774 = arg0;
        D_800E3778 = arg1;
        D_800E3770 = 1;
        return 1;
    }
    return 0;
}

void func_800C74A0(void *arg) {
    OSMesg sp34 = 0;
    while(1){
        do {
            osRecvMesg(&D_8012ACA0, &sp34, 1);
        } while(sp34 != (OSMesg)10);
        func_8006E2E8(D_800E3774, -1, D_800E3778);
        D_800E3770 = 0;
    }
}
