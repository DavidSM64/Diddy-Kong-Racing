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
#ifndef _FINALROM                       /* all #ifdef items should    */
    OSTime              startTime;      /* remain at the end!!, or    */
    OSTime              totalTime;      /* possible conflict if       */
#endif                                  /* FINALROM library used with */
                                        /* non FINALROM code          */

    s32                 unk68;          /* Added by Rare?             */
} OSScTask;

typedef struct SCClient_s {
    u8                  unk0;   /* Added by Rare?               */
    struct SCClient_s   *next;  /* next client in the list      */
    OSMesgQueue         *msgQ;  /* where to send the frame msg  */
} OSScClient;

/* 0x7C8 bytes - Side note, I'm seeing 0x288 now... */
typedef struct {
  /* 0x00 */  OSScMsg     retraceMsg;
  /* 0x20 */  OSScMsg     prenmiMsg;
  /* 0x40 */  OSMesgQueue interruptQ;
  /* 0x68 */  OSMesg      intBuf[OS_SC_MAX_MESGS]; //0x8 per OsMesg
  /* 0xA8 */  OSMesgQueue cmdQ;
  /* 0xD0 */  OSMesg      cmdMsgBuf[OS_SC_MAX_MESGS]; //0x8 per OsMesg
  /* 0x110 */ OSThread    thread;
  /* 0x2D8 */ OSScClient  *clientList;
  /* 0x2F0 */ OSScTask    *audioListHead;
  /* 0x3A0 */ OSScTask    *gfxListHead;
  /* 0x450 */ OSScTask    *audioListTail;
  /* 0x500 */ OSScTask    *gfxListTail;
  /* 0x5B0 */ OSScTask    *curRSPTask;
  /* 0x660 */ OSScTask    *curRDPTask;
  /* 0x710 */ OSScTask    *unkTask; //Rare added?
  /* 0x7C0 */ u32         frameCount;
  /* 0x7C4 */ s32         doAudio;
} OSSched;

typedef struct{
    u8 pad00[0x50];
} unk800E3900;

extern OSViMode osViModeTable[];

/*******************************/

void __scYield(OSSched *sc);
static void __scMain(void *arg);
void __scExec(OSSched *sc, OSScTask *sp, OSScTask *dp);
void osCreateScheduler(OSSched *sc, void *stack, OSPri priority, u8 mode, u8 numFields);
void osScAddClient(OSSched *sc, OSScClient *c, OSMesgQueue *msgQ, u8 arg3);
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
static s32 __scSchedule(OSSched *sc, OSScTask **sp, OSScTask **dp, s32 availRCP);

#endif
