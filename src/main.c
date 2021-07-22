/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065D40 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

/************ .rodata ************/

#ifndef NON_MATCHING
// Remove this when func_80065E30 is matching.
const char D_800E6ED0[] = "WARNING: Stack overflow/underflow!!!\n";
#endif

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
OSThread *D_8011F910; // OSThread for thread 3
s32 D_8011F914;
s32 D_8011F918[1130];

/******************************/

void func_80065D98(s32 arg0);
void thread3_main(s32 arg0);

void main(void) {
    osInitialize();
    osCreateThread(&D_8011F760, 1, &func_80065D98, 0, &D_8011D750, 0);
    osStartThread(&D_8011F760);
}

#ifdef NON_MATCHING
void func_80065D98(s32 arg0) {
    func_800B6F50();
    osCreateThread(&D_8011F910, 3, &thread3_main, 0, &D_8011F758, 10);
    D_8011D758[2049] = 0;
    D_8011D758[2048] = 0;
    D_8011D758[1] = 0;
    D_8011D758[0] = 0;
    osStartThread(&D_8011F910);
    osSetThreadPri(NULL, 0);
    while(1){}
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
        func_800C9D54("WARNING: Stack overflow/underflow!!!\n");
    }
}
#else
GLOBAL_ASM("asm/non_matchings/main/func_80065E30.s")
#endif


