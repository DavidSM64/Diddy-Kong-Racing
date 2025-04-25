#include "memory.h"

#ifdef __sgi
#define STACK_POINTER __$sp
#else
#define STACK_POINTER gStackPointer
StackInfo *gStackPointer;
#endif

/**
 * Uses IDO specific -dollar compiler flag to get the current stack pointer.
 * Official Name: diCpuTraceCurrentStack
 */
StackInfo *stack_pointer(void) {
    return (StackInfo *) STACK_POINTER;
}
