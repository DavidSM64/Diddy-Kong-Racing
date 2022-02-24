/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065D40 */

#include "main.h"
#include "thread0_epc.h"
#include "game.h"
#include "lib/src/libc/rmonPrintf.h"

/************ .bss ************/

u64 *gThread1StackPointer; // stack pointer for thread 1
u64 gThread3Stack[1024];
u64 *gThread3StackPointer; // stack pointer for thread 3
OSThread gThread1; // OSThread for thread 1
OSThread gThread3; // OSThread for thread 3
u64 D_8011FAC0[512]; //Thread1 stack?

/******************************/

void main(void) {
    osInitialize();
    osCreateThread(&gThread1, 1, &thread1_main, 0, &gThread1StackPointer, OS_PRIORITY_IDLE);
    osStartThread(&gThread1);
}

void thread1_main(UNUSED void *unused) {
    thread0_create();
    osCreateThread(&gThread3, 3, &thread3_main, 0, &gThread3StackPointer, 10);
    gThread3Stack[1024] = 0;
    gThread3Stack[0] = 0;
    osStartThread(&gThread3);
    osSetThreadPri(NULL, 0);
    while (1) {}
}

void thread3_verify_stack(void) {
    gThread3Stack[1024]++;
    gThread3Stack[0]++;
    if ((gThread3Stack[1024] != gThread3Stack[0])) {
        rmonPrintf("WARNING: Stack overflow/underflow!!!\n");
    }
}
