#include "memory.h"

#ifdef __sgi
/**
 * Uses IDO specific -dollar compiler flag to get the current stack pointer.
 * Official Name: diCpuTraceCurrentStack
 */
StackInfo *stack_pointer(void) {
    return (StackInfo *) __$sp;
}
#else
// Easiest method to support getting the stack pointer on all platforms.
#pragma GLOBAL_ASM("asm/nonmatchings/get_stack_pointer/stack_pointer.s")
#endif
