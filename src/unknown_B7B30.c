/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B6F30 */

#include "unknown_B7B30.h"

UNUSED void func_800B6F30(UNUSED int arg0, UNUSED int arg1, UNUSED int arg2) {}

// Only called from two libultra funcs for some reason. 
// This is likely an assert gone wrong.
// Called from alEnvMixerPull, and _pullSubFrame
// thread0_Assert("samples >= 0", "env.c", 104);
// thread0_Assert("samples <= AL_MAX_RSP_SAMPLES", "env.c", 105);
// thread0_Assert("source", "env.c", 373);
void thread0_Assert(UNUSED char *message, UNUSED char *fileName, UNUSED s32 lineNumber) {}
