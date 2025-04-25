#ifndef __sgi
extern void *__$sp;
#endif

/**
 * Uses IDO specific -dollar compiler flag to get the current stack pointer.
 * Official Name: diCpuTraceCurrentStack
 */
void *stack_pointer(void) {
    return __$sp;
}
