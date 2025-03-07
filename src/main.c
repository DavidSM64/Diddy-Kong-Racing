/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065D40 */

#include "main.h"
#include "thread0_epc.h"
#include "game.h"
#include "libultra/src/libc/rmonPrintf.h"

/************ .bss ************/

u64 gThread1Stack[0x21];
u64 gThread3Stack[0x401];
OSThread gThread1; // OSThread for thread 1
OSThread gThread3; // OSThread for thread 3
UNUSED u64 gUnusedThreadStack[0x200];

/******************************/

/**
 * Where it all begins.
 * Once the boot procedure is finished in IPL3, this function is run.
 * It kicks things off by initialising thread1, which serves as the top level
 * Official name: boot
 */
void main(void) {
    osInitialize();
    osCreateThread(&gThread1, 1, &thread1_main, 0, &gThread1Stack[0x20], OS_PRIORITY_IDLE);
    osStartThread(&gThread1);
}

/**
 * Initialise the crash handler thread, then initialise the main game thread.
 * Reset the start and endpoint of the game thread stack, then set thread priority to zero, effectively
 * stopping this thread, as it's no longer needed.
 */
void thread1_main(UNUSED void *unused) {
    thread0_create();
    osCreateThread(&gThread3, 3, &thread3_main, 0, &gThread3Stack[0x400], 10);
    gThread3Stack[0x400] = 0;
    gThread3Stack[0] = 0;
    osStartThread(&gThread3);
    osSetThreadPri(NULL, OS_PRIORITY_IDLE);
    while (1) {}
}

/**
 * Increments the start and endpoint of the stack.
 * They should have an equal value, so if they don't, that triggers a printout saying a stack wraparound has occured.
 * Official Name: bootCheckStack
 */
void thread3_verify_stack(void) {
    gThread3Stack[0x400]++;
    gThread3Stack[0]++;
    if ((gThread3Stack[0x400] != gThread3Stack[0])) {
        rmonPrintf("WARNING: Stack overflow/underflow!!!\n");
    }
}
