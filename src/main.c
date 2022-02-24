/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065D40 */

#include "main.h"
#include "thread0_epc.h"
#include "game.h"
#include "lib/src/libc/rmonPrintf.h"

/************ .rodata ************/

#ifndef NON_EQUIVALENT
// Remove this when func_80065E30 is matching.
const char D_800E6ED0[] = "WARNING: Stack overflow/underflow!!!\n";
#endif

/*********************************/

/************ .bss ************/

s32 *gThread1StackPointer; // stack pointer for thread 1
s32 D_8011D754;
s64 D_8011D758[1024];
s32 *gThread3StackPointer; // stack pointer for thread 3
s32 D_8011F75C;
OSThread gThread1; // OSThread for thread 1
OSThread gThread3; // OSThread for thread 3
s32 D_8011FAC0[1024];

/******************************/

void main(void) {
    osInitialize();
    osCreateThread(&gThread1, 1, &thread1_main, 0, &gThread1StackPointer, 0);
    osStartThread(&gThread1);
}

void thread1_main(UNUSED void *unused) {
    func_800B6F50();
    osCreateThread(&gThread3, 3, &thread3_main, 0, &gThread3StackPointer, 10);
    D_8011D758[1024] = 0;
    D_8011D758[0] = 0;
    osStartThread(&gThread3);
    osSetThreadPri(NULL, 0);
    while (1) {}
}

#ifdef NON_EQUIVALENT
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
