#ifndef _PI_MANAGER_H_
#define _PI_MANAGER_H_

#include "types.h"
#include "libultra_internal.h"
#include "stacks.h"

extern OSThread piThread;
extern s32 D_8012A9B0[64];
extern OSMesgQueue piEventQueue;
extern OSMesg piEventBuf[2];

void osCreatePiManager(OSPri pri, OSMesgQueue *cmdQ, OSMesg *cmdBuf, s32 cmdMsgCnt);

#endif