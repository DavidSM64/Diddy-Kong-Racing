#ifndef _STACKS_H_
#define _STACKS_H_

#include "types.h"

#define OS_PIM_STACKSIZE 4096

extern u8 piThreadStack[256]; // piThreadStack[OS_PIM_STACKSIZE];
extern s64 D_80129BB0[128]; //epcStack?
extern s32 D_80129FB0[3];
extern s32 D_80129FBC;

#endif
