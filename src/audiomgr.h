#ifndef _AUDIOMGR_H_
#define _AUDIOMGR_H_

#include "types.h"
#include "macros.h"
#include "audio_internal.h"
#include "asset_enums.h"
#include <ultra64.h>
#include "sched.h"

#define MAX_UPDATES             32
#define MAX_EVENTS              32
#define AUDIO_HEAP_SIZE         0x29D88

#define MAX_VOICES              22
#define EXTRA_SAMPLES           96
#define NUM_OUTPUT_BUFFERS      3      /* Need three of these */
#define OUTPUT_RATE             22050
#define MAX_MESGS               8
#define QUIT_MSG                10

#define DMA_BUFFER_LENGTH       0x400  /* Larger buffers result in fewer DMA' but more  */
                                       /* memory being used.  */


#define NUM_ACMD_LISTS          2      /* two lists used by this example                */
#define MAX_RSP_CMDS            4096   /* max number of commands in any command list.   */
                                       /* Mainly dependent on sequences used            */

#define NUM_DMA_BUFFERS         50     /* max number of dma buffers needed.             */
                                       /* Mainly dependent on sequences and sfx's       */

#define NUM_DMA_MESSAGES        50     /* The maximum number of DMAs any one frame can  */
                                       /* have.                                         */

#define FRAME_LAG               1      /* The number of frames to keep a dma buffer.    */
                                       /* Increasing this number causes buffers to not  */
                                       /* be deleted as quickly. This results in fewer  */
                                       /* DMA's but you need more buffers.              */


#define AUDIO_STACKSIZE         0x3010

#define MAX_SEQ_LENGTH  20000

extern Acmd *alAudioFrame(Acmd *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen);
extern void *alHeapDBAlloc(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size);
extern void alInit(ALGlobals *g, ALSynConfig *c);

extern s8 rspF3DDKRBootStart[];
extern s8 rspF3DDKRDramStart[];

void audioStartThread(void);
void audioStopThread(void);
void amCreateAudioMgr(ALSynConfig *c, OSPri pri, OSSched *audSched);

#endif
