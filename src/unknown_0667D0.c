/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065BD0 */

#include "unknown_0667D0.h"

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

/************ .data ************/

s16 D_800DD050 = 0;

/*******************************/

extern s32* D_80065D98; // func_80065D98 is the entry function for thread 1

/************ .rodata ************/

// In func_80065E30
const char D_800E6ED0[] = "WARNING: Stack overflow/underflow!!!\n";

/*********************************/

/************ .bss ************/

s32 *D_8011D750; // stack pointer for thread 1
s32 D_8011D754;
s32 D_8011D758[2048];
s32 *D_8011F758;
s32 D_8011F75C;
OSThread *D_8011F760; // OSThread for thread 1
s32 D_8011F764;
s32 D_8011F768[106];
s32 *D_8011F910;

/******************************/

void func_80065BD0(s32 arg0) {
    D_800DD050 = arg0;
}

/* Unused? */
s16 func_80065BDC(void) {
    return D_800DD050;
}

s32 func_80065BEC(s32 arg0) {
    switch(D_800DD050) {
        case 0:
            return arg0;
        case 2:
            arg0 = ((arg0 - 0x40) >> 1) + 0x40;
            return arg0;
        case 1:
        default:
            return 0x40;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_0667D0/alSynStartVoiceParams.s")

void func_80065D40(void) {
    osInitialize();
    osCreateThread(&D_8011F760, 1, &D_80065D98, 0, &D_8011D750, 0);
    osStartThread(&D_8011F760);
}

GLOBAL_ASM("asm/non_matchings/unknown_0667D0/func_80065D98.s")
GLOBAL_ASM("asm/non_matchings/unknown_0667D0/func_80065E30.s")


