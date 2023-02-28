#ifndef _SCHED_H_
#define _SCHED_H_

#include "types.h"
#include "macros.h"
#include "f3ddkr.h"
#include "libultra_internal.h"

#define OS_SC_RETRACE_MSG       1
#define OS_SC_PRE_NMI_MSG       4
#define OS_SC_AUDIO_MSG         5
#define OS_SC_MAX_MESGS         8

#define OS_SC_ID_NONE   0
#define OS_SC_ID_AUDIO  1
#define OS_SC_ID_VIDEO  2
#define OS_SC_ID_PRENMI 3

#define OSMESG_SWAP_BUFFER 0
#define MESG_SKIP_BUFFER_SWAP 8

/*
 * OSScTask state
 */
#define OS_SC_DP                0x0001  /* set if still needs dp        */
#define OS_SC_SP                0x0002  /* set if still needs sp        */
#define OS_SC_YIELD             0x0010  /* set if yield requested       */
#define OS_SC_YIELDED           0x0020  /* set if yield completed       */

/*
 * OSScTask->flags type identifier
 */
#define OS_SC_XBUS      (OS_SC_SP | OS_SC_DP)
#define OS_SC_DRAM      (OS_SC_SP | OS_SC_DP | OS_SC_DRAM_DLIST)
#define OS_SC_DP_XBUS   (OS_SC_SP)
#define OS_SC_DP_DRAM   (OS_SC_SP | OS_SC_DRAM_DLIST)
#define OS_SC_SP_XBUS   (OS_SC_DP)
#define OS_SC_SP_DRAM   (OS_SC_DP | OS_SC_DRAM_DLIST)
/*
 * OSScTask flags:
 */
#define OS_SC_NEEDS_RDP         0x0001  /* uses the RDP */
#define OS_SC_NEEDS_RSP         0x0002  /* uses the RSP */
#define OS_SC_DRAM_DLIST        0x0004  /* SP & DP communicate through DRAM */
#define OS_SC_PARALLEL_TASK     0x0010  /* must be first gfx task on list */
#define OS_SC_LAST_TASK         0x0020  /* last task in queue for frame */
#define OS_SC_SWAPBUFFER        0x0040  /* swapbuffers when gfx task done */

#define OS_SC_RCP_MASK          0x0003  /* mask for needs bits */
#define OS_SC_TYPE_MASK         0x0007  /* complete type mask */

typedef struct {
    short type;
    char  misc[30];
} OSScMsg;

typedef struct OSScTask_s {
    struct OSScTask_s   *next;          /* note: this must be first */
    u32                 state;
    u32                 flags;
    void                *framebuffer;   /* used by graphics tasks */

    OSTask              list;
    OSMesgQueue         *msgQ;
    OSMesg              msg;
    s32                 unk58;
    s32                 unk5C;
    s32                 unk60;
    s32                 unk64;
    s32                 unk68;          /* Added by Rare?             */
    s32                 unk6C;
} OSScTask;

typedef struct SCClient_s {
    u8                  id;   /* Client ID, added by Rareware to single out individual scheduler clients*/
    struct SCClient_s   *next;  /* next client in the list      */
    OSMesgQueue         *msgQ;  /* where to send the frame msg  */
} OSScClient;

/* 0x288 bytes */
typedef struct {
  /* 0x00 */  OSScMsg     retraceMsg;
  /* 0x20 */  OSScMsg     prenmiMsg;
  /* 0x40 */  OSMesgQueue interruptQ;
  /* 0x58 */  OSMesg      intBuf[OS_SC_MAX_MESGS]; //0x8 per OSMesg
  /* 0x78 */  OSMesgQueue cmdQ;
  /* 0x90 */  OSMesg      cmdMsgBuf[OS_SC_MAX_MESGS]; //0x8 per OSMesg
  /* 0xB0 */  OSThread    thread;
  /* 0x260 */ OSScClient  *clientList;
  /* 0x264 */ OSScTask    *audioListHead;
  /* 0x268 */ OSScTask    *gfxListHead;
  /* 0x26C */ OSScTask    *audioListTail;
  /* 0x270 */ OSScTask    *gfxListTail;
  /* 0x274 */ OSScTask    *curRSPTask;
  /* 0x278 */ OSScTask    *curRDPTask;
  /* 0x27C */ OSScTask    *unkTask; //Rare added?
  /* 0x280 */ u32         frameCount;
  /* 0x284 */ s32         doAudio;
} OSSched;

typedef struct{
    u8 pad00[0x50];
} unk800E3900;

extern OSViMode osViModeTable[];

/*******************************/

void __scYield(OSSched *sc);
void __scExec(OSSched *sc, OSScTask *sp, OSScTask *dp);
void osCreateScheduler(OSSched *sc, void *stack, OSPri priority, u8 mode, u8 numFields);
void osScAddClient(OSSched *sc, OSScClient *c, OSMesgQueue *msgQ, u8 id);
void osScRemoveClient(OSSched *sc, OSScClient *c);
OSMesgQueue *osScGetCmdQ(OSSched *sc);
OSMesgQueue *osScGetInterruptQ(OSSched *sc);
void func_80079584(f32 *arg0, f32 *arg1, f32 *arg2);
void func_80079760(OSSched *sc);
void __scHandleRDP(OSSched *sc);
void __scHandleRSP(OSSched *sc);
OSScTask *__scTaskReady(OSScTask *t);
s32 __scTaskComplete(OSSched *sc, OSScTask *t);
void __scAppendList(OSSched *sc, OSScTask *t);
void __scExec(OSSched *sc, OSScTask *sp, OSScTask *dp);
void __scHandleRetrace(OSSched *sc);

#endif
