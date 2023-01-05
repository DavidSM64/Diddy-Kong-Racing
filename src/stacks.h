#ifndef _STACKS_H_
#define _STACKS_H_

#include "types.h"

#define OS_PIM_STACKSIZE 4096

extern u8 piThreadStack[0x100]; // piThreadStack[OS_PIM_STACKSIZE];
extern u16 D_80129BB0[512]; //epcStack?
extern s32 D_80129FB0[3];
extern s32 D_80129FBC;

#endif
