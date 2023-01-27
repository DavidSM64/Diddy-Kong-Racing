/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80002660 */

#include "unknown_003260.h"
#include "PR/abi.h"

// This file is needed, since there is a bss reordering issue with D_80119BD0 and gAlSndPlayer
#define NUM_ACMD_LISTS 2
OSSched *gAudioSched;
ALHeap *gAudioHeap;
Acmd *ACMDList[NUM_ACMD_LISTS];
s32 D_80115FA0[3];
OSThread audioThread;
OSMesgQueue gAudioMesgQueue;
OSMesg D_80116178[8];
OSMesgQueue audioReplyMsgQ;
OSMesg D_801161B0[8];
ALGlobals ALGlobals_801161D0;
u64 audioStack[AUDIO_STACKSIZE/sizeof(u64)];
AMDMAState dmaState;
AMDMABuffer dmaBuffs[50];
u32 minFrameSize;
u32 framesize;
u32 maxFrameSize;
s32 gAudioCmdLen;
s16 gDMABufferLength;
u32 D_8011963C;
OSIoMesg audDMAIOMesgBuf[NUM_DMA_MESSAGES];
OSMesgQueue audDMAMessageQ;
OSMesg audDMAMessageBuf[NUM_DMA_MESSAGES];
unk800DC6BC D_80119BD0;
u16 *gSoundChannelVolume;
