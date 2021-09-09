#ifndef _SCHED_H_
#define _SCHED_H_
#include "types.h"
#include "macros.h"
#include "f3ddkr.h"
#include "libultra_internal.h"

#define OS_SC_RETRACE_MSG       1
#define OS_SC_PRE_NMI_MSG       4
#define OS_SC_MAX_MESGS         8

#define OS_SC_YIELD             2

typedef struct {
    short type;
    char  misc[30];
} OSScMsg;

typedef struct OSScTask_s {
    struct OSScTask_s   *next;          /* note: this must be first */
    u32                 state;
    u32			flags;
    void		*framebuffer;	/* used by graphics tasks */

    OSTask              list;
    OSMesgQueue         *msgQ;
    OSMesg              msg;
#ifndef _FINALROM                       /* all #ifdef items should    */
    OSTime              startTime;      /* remain at the end!!, or    */
    OSTime              totalTime;      /* possible conflict if       */
#endif                                  /* FINALROM library used with */
} OSScTask;                             /* non FINALROM code          */


typedef struct SCClient_s {
    u8                  unk0;
    struct SCClient_s   *next;  /* next client in the list      */
    OSMesgQueue         *msgQ;  /* where to send the frame msg  */
} OSScClient;

/* 0x71C bytes */
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
  /* 0x710 */ u32         frameCount;
  /* 0x714 */ s32         doAudio;
  /* 0x718 */ s32         unk284;
} OSSched;

typedef struct{
    u8 pad00[0x50];
} unk800E3900;

extern OSViMode osViModeTable[];

/*******************************/

void func_8007A080(OSSched *sc);
void __scMain(void);
void __scExec(OSSched *sc, OSScTask *sp, OSScTask *dp);
void osCreateScheduler(OSSched *sc, void *stack, OSPri priority, u8 mode, u8 numFields);
void osScAddClient(OSSched *sc, OSScClient *c, OSMesgQueue *msgQ, u8 arg3);
void osScRemoveClient(OSSched *sc, OSScClient *c);
OSMesgQueue *osScGetCmdQ(OSSched *sc);
OSMesgQueue *osScGetInterruptQ(OSSched *sc);
void func_80079584(f32 *arg0, f32 *arg1, f32 *arg2);
void func_80079760(OSSched *sc);
void __scHandleRDP(OSSched *sc);
OSScTask *__scTaskReady(OSScTask *t);
s32 __scTaskComplete(OSSched *sc, OSScTask *t);
void __scAppendList(OSSched *sc, OSScTask *t);
void __scExec(OSSched *sc, OSScTask *sp, OSScTask *dp);
void func_8007A080(OSSched *sc);
// This might need to be moved into it's own file.
void set_rsp_segment(Gfx **dlist, s32 segment, s32 base);

#endif
