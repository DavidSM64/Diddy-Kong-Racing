/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065D40 */

#include "main.h"
#include "thread0_epc.h"
#include "unknown_06B2B0.h"
#include "lib/src/libc/rmonPrintf.h"

/************ .rodata ************/

#ifndef NON_MATCHING
// Remove this when func_80065E30 is matching.
const char D_800E6ED0[] = "WARNING: Stack overflow/underflow!!!\n";
#endif

/*********************************/

/************ .bss ************/

s32 *gThread1StackPointer; // stack pointer for thread 1
s32 D_8011D754;
s32 D_8011D758[2048];
s32 *gThread3StackPointer; // stack pointer for thread 3
s32 D_8011F75C;
OSThread *gThread1; // OSThread for thread 1
s32 D_8011F764;
s32 D_8011F768[106];
OSThread *gThread3; // OSThread for thread 3
s32 D_8011F914;
s32 D_8011F918[1130];

/******************************/

void main(void) {
    osInitialize();
    osCreateThread(&gThread1, 1, (OSId)&func_80065D98, 0, &gThread1StackPointer, (OSPri)0);
    osStartThread(&gThread1);
}

#ifdef NON_MATCHING
void func_80065D98(s32 arg0) {
    func_800B6F50();
    osCreateThread(&gThread3, 3, (OSId)&thread3_main, 0, &gThread3StackPointer, (OSPri)10);
    D_8011D758[2049] = 0;
    D_8011D758[2048] = 0;
    D_8011D758[1] = 0;
    D_8011D758[0] = 0;
    osStartThread(&gThread3);
    osSetThreadPri(NULL, 0);
    while (1) {}
}
#else
GLOBAL_ASM("asm/non_matchings/main/func_80065D98.s")
#endif

#ifdef NON_MATCHING
void func_80065E30(void) {
    s32 temp, temp2, temp3, temp4;
    temp = D_8011D758[2049] + 1;
    temp2 = D_8011D758[2048] + (temp == 0);
    temp3 = D_8011D758[1] + 1;
    temp4 = D_8011D758[0] + (temp3 == 0);
    D_8011D758[2049] = temp;
    D_8011D758[2048] = temp2;
    D_8011D758[1] = temp3;
    D_8011D758[0] = temp4;
    if ((temp2 != temp4) || (temp != temp3)) {
        rmonPrintf("WARNING: Stack overflow/underflow!!!\n");
    }
}
#else
GLOBAL_ASM("asm/non_matchings/main/func_80065E30.s")
#endif
