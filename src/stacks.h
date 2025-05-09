#ifndef _STACKS_H_
#define _STACKS_H_

#include "types.h"

#define STACK_EPC       0x1000
#define STACK_EPCINFO1  0x200
#define STACK_EPCINFO2  0x400
#define STACK_IDLE      0x100
#define STACK_SCHED     0x2000
#define STACK_AUD       0x3010
#define STACK_GAME      0x2000
#define STACK_BGLOAD    0x2000

#define STACKSIZE(x) (x / sizeof(u64))

#endif
