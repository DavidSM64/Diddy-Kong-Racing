/*====================================================================
 * 
 * Copyright 1995, Silicon Graphics, Inc.
 * All Rights Reserved.
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics,
 * Inc.; the contents of this file may not be disclosed to third
 * parties, copied or duplicated in any form, in whole or in part,
 * without the prior written permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to
 * restrictions as set forth in subdivision (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS
 * 252.227-7013, and/or in similar or successor clauses in the FAR,
 * DOD or NASA FAR Supplement. Unpublished - rights reserved under the
 * Copyright Laws of the United States.
 *====================================================================*/
#include <ultralog.h>
#include <assert.h>
#include <sched.h>
// TODO: this comes from a header
#ident "$Revision: 1.17 $"

/*
 * private typedefs and defines
 */
#define UNK_MSG         99
#define VIDEO_MSG       666
#define RSP_DONE_MSG    667
#define RDP_DONE_MSG    668
#define PRE_NMI_MSG     669
#define SCHED_THREAD_ID 5

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
 * private functions
 */
static void     __scMain(void *arg);
static void     __scHandleRetrace(OSSched *s);
static void     __scHandleRSP(OSSched *s);
static void     __scHandleRDP(OSSched *s);

static void     __scAppendList(OSSched *s, OSScTask *t);
OSScTask        *__scTaskReady(OSScTask *t);
static s32      __scTaskComplete(OSSched *s,OSScTask *t);
static void     __scExec(OSSched *sc, OSScTask *sp, OSScTask *dp);
static void	__scYield(OSSched *s);

/************ .data ************/

s32 D_800DE730[] = { OSMESG_SWAP_BUFFER, OSMESG_SWAP_BUFFER };
s32 gBootBlackoutMesg[] = { OSMESG_SWAP_BUFFER, MESG_SKIP_BUFFER_SWAP };

f32 gAudTaskTimer0 = 0;
f32 gAudTaskTimer1 = 0;
f32 gAudTaskTimer2 = 0;
f32 gAudTaskTimer3 = 0;

s32 gRetraceCounter32 = 0;
s32 gCurRSPTaskCounter = 0;
s32 gCurRDPTaskCounter = 0;
UNUSED s32 D_800DE75C = 0;
u64 gRetraceCounter64 = 0;

/*******************************/

/************ .rodata ************/

const char D_800E7800[] = "(Audio task)";
const char D_800E7810[] = "(Game task)";
const char D_800E781C[] = "(DI task)\n";
const char D_800E7828[] = "(DI benchmark test)\n";
const char D_800E7840[] = "(Unknown task type %d)\n";
const char D_800E7858[] = "\nRCP TASK INFO\n";
const char D_800E7868[] = "-------------\n";
const char D_800E7878[] = "\ttype\t\t= %u\n";
const char D_800E7888[] = "\tflags\t\t= %u\n";
const char D_800E7898[] = "\tucode_boot\t\t= %p\n";
const char D_800E78AC[] = "\tucode_boot_size\t\t= %u\n";
const char D_800E78C4[] = "\tucode\t\t= %p\n";
const char D_800E78D4[] = "\tucode_size\t\t= %u\n";
const char D_800E78E8[] = "\tucode_data\t\t= %p\n";
const char D_800E78FC[] = "\tucode_data_size\t\t= %u\n";
const char D_800E7914[] = "\toutput_buff\t\t= %p\n";
const char D_800E7928[] = "\toutput_buff_size\t\t= %u\n";
const char D_800E7944[] = "\tdata_ptr\t\t= %p\n";
const char D_800E7958[] = "\tdata_size\t\t= %u\n";

/************ .bss ************/

s32 gCurRSPTaskIsSet;
s32 gCurRDPTaskIsSet;
OSTime gYieldTime;
u32 gRSPAudTaskFlushTime;
u32 gRSPAudTaskDoneTime;
UNUSED s32 D_80126128[18];

static s32      __scSchedule(OSSched *sc, OSScTask **sp, OSScTask **dp,
                             s32 availRCP);


/*
#define SC_LOGGING 1
*/


#ifdef SC_LOGGING
#define SC_LOG_LEN      32*1024
static OSLog    scLog;
static OSLog    *l = &scLog;
static u32      logArray[SC_LOG_LEN/sizeof(u32)];
#endif

/***********************************************************************
 * Scheduler API
 **********************************************************************/
void osCreateScheduler(OSSched *sc, void *stack, OSPri priority,
                       u8 mode, u8 numFields)
{
    sc->curRSPTask      = 0;
    sc->curRDPTask      = 0;
    sc->clientList      = 0;
    sc->audioListHead   = 0;
    sc->gfxListHead     = 0;
    sc->audioListTail   = 0;
    sc->gfxListTail     = 0;
    sc->frameCount      = 0;
    sc->unkTask         = 0;
    sc->retraceMsg.type = OS_SC_RETRACE_MSG;  /* sent to apps */
    sc->prenmiMsg.type  = OS_SC_PRE_NMI_MSG;

    /*
     * Set up video manager, listen for Video, RSP, and RDP interrupts
     */
    osCreateViManager(OS_PRIORITY_VIMGR);    
    osViSetMode(&osViModeTable[mode]);
    osViBlack(TRUE);
    osCreateMesgQueue(&sc->interruptQ, sc->intBuf, OS_SC_MAX_MESGS);
    osCreateMesgQueue(&sc->cmdQ, sc->cmdMsgBuf, OS_SC_MAX_MESGS);
    osSetEventMesg(OS_EVENT_SP, &sc->interruptQ, (OSMesg)RSP_DONE_MSG);
    osSetEventMesg(OS_EVENT_DP, &sc->interruptQ, (OSMesg)RDP_DONE_MSG);    
    osSetEventMesg(OS_EVENT_PRENMI, &sc->interruptQ, (OSMesg)PRE_NMI_MSG);    

    osViSetEvent(&sc->interruptQ, (OSMesg)VIDEO_MSG, numFields);    

#ifdef SC_LOGGING    
    osCreateLog(l, logArray, sizeof(logArray));
#endif

    osCreateThread(&sc->thread, SCHED_THREAD_ID, __scMain, (void *)sc, stack, priority);
    osStartThread(&sc->thread);
}

/*
 * Add a client to the scheduler.  Clients receive messages at retrace time
 */
void osScAddClient(OSSched *sc, OSScClient *c, OSMesgQueue *msgQ, u8 id)
{
    OSIntMask mask;

    mask = osSetIntMask(OS_IM_NONE);

    c->msgQ = msgQ;
    c->next = sc->clientList;
    c->id = id;
    sc->clientList = c;

    osSetIntMask(mask);
}

void osScRemoveClient(OSSched *sc, OSScClient *c)
{
    OSScClient *client = sc->clientList; 
    OSScClient *prev   = 0;
    OSIntMask  mask;

    mask = osSetIntMask(OS_IM_NONE);
    
    while (client != 0) {
        if (client == c) {
	    if(prev)
		prev->next = c->next;
	    else
		sc->clientList = c->next;
            break;
        }
        prev   = client;
        client = client->next;
    }

    osSetIntMask(mask);
}

OSMesgQueue *osScGetCmdQ(OSSched *sc)
{
    return &sc->cmdQ;
}

OSMesgQueue *osScGetInterruptQ(OSSched *sc) {
    return &sc->interruptQ;
}

/**
 * Official Name: osScGetAudioSPStats
*/
UNUSED void scGetAudioTaskTimers(f32 *timer0, f32 *timer1, f32 *timer2) {
    *timer0 = gAudTaskTimer0;
    *timer1 = gAudTaskTimer2;
    *timer2 = gAudTaskTimer3;
}

/***********************************************************************
 * Scheduler implementation
 **********************************************************************/
static void __scMain(void *arg)
{
    OSMesg msg = NULL;
    OSSched *sc = (OSSched *)arg;
    OSScClient *client;
    s32 state = 0;
    OSScTask *sp = NULL;
    OSScTask *dp = NULL;
    
    while (1) {
        
        osRecvMesg(&sc->interruptQ, (OSMesg *)&msg, OS_MESG_BLOCK);

#ifdef SC_LOGGING 
        if (++count % 1024 == 0)
            osFlushLog(l);
#endif
        

        switch ((int) msg) {
          case (VIDEO_MSG):
              __scHandleRetrace(sc);
              break;

          case (RSP_DONE_MSG):
              __scHandleRSP(sc);
              break;

          case (RDP_DONE_MSG):
              __scHandleRDP(sc);
              break;
          case (UNK_MSG):
                func_80079760(sc);
                break;

          case (PRE_NMI_MSG):
	      /*
	       * notify audio and graphics threads to fade out
	       */
              for (client = sc->clientList;client != 0;client = client->next) {
                  osSendMesg(client->msgQ, (OSMesg) &sc->prenmiMsg,
                             OS_MESG_NOBLOCK);
              }
              break;
          default:
                __scAppendList(sc, (OSScTask *) msg);
                state = ((sc->curRSPTask == 0) << 1) | (sc->curRDPTask == 0);
                if (__scSchedule(sc, &sp, &dp, state) != state)
                    __scExec(sc, sp, dp);
                break;
        }
    }
}

void func_80079760(OSSched *sc) {
    s32 state;
    OSScTask *sp = 0;
    OSScTask *dp = 0;

    if (sc->audioListHead) {
        sc->doAudio = 1;
    }
    if (sc->doAudio && sc->curRSPTask) {
        __scYield(sc);
    } else {
        state = ((sc->curRSPTask == 0) << 1) | (sc->curRDPTask == 0);
        if (__scSchedule(sc, &sp, &dp, state) != state) {
            __scExec(sc, sp, dp);
        }
    }
}

UNUSED void dummy_80079808() {}
UNUSED void dummy_80079810() {}

void __scHandleRetrace(OSSched *sc) {
    OSScTask *rspTask = NULL;
    OSScClient *client;
    s32 state;
    OSScTask *sp = 0;
    OSScTask *dp = 0;
    u8 set_curRSPTask_NULL = FALSE;
    u8 set_curRDPTask_NULL = FALSE;
    OSScTask *unkTask;

    if (sc->curRSPTask) {
        gCurRSPTaskCounter++;
    }

    if (sc->curRDPTask) {
        gCurRDPTaskCounter++;
    }

    if ((gCurRSPTaskCounter > 10) && (sc->curRSPTask)) {
        gCurRSPTaskCounter = 0;
        set_curRSPTask_NULL = TRUE;

        __osSpSetStatus(SP_SET_HALT | SP_CLR_INTR_BREAK | SP_CLR_SIG0 |
            SP_CLR_SIG1 | SP_CLR_SIG2 | SP_CLR_SIG3 | SP_CLR_SIG4 |
            SP_CLR_SIG5 | SP_CLR_SIG6 | SP_CLR_SIG7);
    } else if (sc->curRSPTask) {
        gCurRSPTaskIsSet = TRUE;
    }

    if ((gCurRDPTaskCounter > 10) && (sc->curRDPTask)) {
        if (sc->curRDPTask->unk68 == 0) {
            osSendMesg(sc->curRDPTask->msgQ, &gBootBlackoutMesg, OS_MESG_BLOCK);
        }

        set_curRDPTask_NULL = TRUE;
        sc->frameCount = 0;
        gCurRDPTaskCounter = 0;

        __osSpSetStatus(SP_SET_HALT | SP_CLR_INTR_BREAK | SP_CLR_SIG0 |
            SP_CLR_SIG1 | SP_CLR_SIG2 | SP_CLR_SIG3 | SP_CLR_SIG4 |
            SP_CLR_SIG5 | SP_CLR_SIG6 | SP_CLR_SIG7);

        osDpSetStatus(DPC_SET_XBUS_DMEM_DMA | DPC_CLR_FREEZE | DPC_CLR_FLUSH |
            DPC_CLR_TMEM_CTR | DPC_CLR_PIPE_CTR | DPC_CLR_CMD_CTR);
    } else if (sc->curRDPTask) {
        gCurRDPTaskIsSet = TRUE;
    }

    if (set_curRSPTask_NULL) {
        sc->curRSPTask = NULL;
    }
    if (set_curRDPTask_NULL) {
        sc->curRDPTask = NULL;
    }

    while (osRecvMesg(&sc->cmdQ, (OSMesg *)&rspTask, OS_MESG_NOBLOCK) != -1)
        __scAppendList(sc, rspTask);

    state = ((sc->curRSPTask == NULL) << 1) | (sc->curRDPTask == NULL);
    if (__scSchedule(sc, &sp, &dp, state) != state)
        __scExec(sc, sp, dp);

    gRetraceCounter64++;
    gRetraceCounter32++;
    sc->frameCount+=1; // If you want to make the game 60FPS, change this to 2.

    if ((sc->unkTask) && (sc->frameCount >= 2)) {
        unkTask = sc->unkTask;
        if (unkTask->msgQ) {
            if ((unkTask->unk68) || (unkTask->msg)) {
                osSendMesg(unkTask->msgQ, unkTask->msg, OS_MESG_BLOCK);
            } else {
                osSendMesg(unkTask->msgQ, &D_800DE730, OS_MESG_BLOCK);
            }
        }
        sc->frameCount = 0;
        sc->unkTask = 0;
    }

    for (client = sc->clientList; client != 0; client = client->next) {
        if (client->id == OS_SC_ID_AUDIO) {
            //Only run this on even calls to this function
            if (gRetraceCounter64 % 2 == 0) {
                osSendMesg(client->msgQ, sc, OS_MESG_NOBLOCK);
                if (sc->audioListHead) {
                    func_80079760(sc);
                }
            }
        } else if (client->id == OS_SC_ID_VIDEO) {
            osSendMesg(client->msgQ, sc, OS_MESG_NOBLOCK);
        }
    }
}

/*
 * __scHandleRSP is called when an RSP task signals that it has
 * finished or yielded (at the hosts request)
 */
void __scHandleRSP(OSSched *sc)
{
    OSScTask *t, *sp = 0, *dp = 0;
    s32 state;

    
    assert(sc->curRSPTask);

    t = sc->curRSPTask;
    sc->curRSPTask = 0;
    
#ifdef SC_LOGGING    
    osLogEvent(l, 510, 3, t, t->state, t->flags);
#endif

    //Rare seems to have edited this function, most specifically here.
    //This should probably have all been behind a debug #ifdef as none of these values are used.
    if (t->list.t.type == M_AUDTASK) {
        gRSPAudTaskDoneTime = osGetCount();

        gAudTaskTimer3 = ((gRSPAudTaskDoneTime - gRSPAudTaskFlushTime) * 60.0f) / (OS_CPU_COUNTER / 100);
        gAudTaskTimer1 += gAudTaskTimer3;

        if (gAudTaskTimer0 < gAudTaskTimer3) {
            gAudTaskTimer0 = gAudTaskTimer3;
        }

        if ((gRetraceCounter32 % 1000 == 1) || (gRetraceCounter32 % 1000 == 2)) {
            gAudTaskTimer2 = gAudTaskTimer1 / 500.0f;
            gAudTaskTimer1 = 0.0f;
            gAudTaskTimer0 = 0.0f;
        }
    }

    if ((t->state & OS_SC_YIELD)) {
        if (osSpTaskYielded(&t->list)) {
            t->state |= OS_SC_YIELDED;
            if ((t->flags & OS_SC_TYPE_MASK) == OS_SC_XBUS) {
                /* push the task back on the list */
                t->next = sc->gfxListHead;
                sc->gfxListHead = t;
                if (sc->gfxListTail == 0)
                    sc->gfxListTail = t;
            }
        } else {
            t->state &= ~OS_SC_NEEDS_RSP;
            do{} while(0);
        }
        if ((t->flags & OS_SC_TYPE_MASK) != OS_SC_XBUS){}
    } else {
        t->state &= ~OS_SC_NEEDS_RSP;
        __scTaskComplete(sc, t);
    }

    state = ((sc->curRSPTask == 0) << 1) | (sc->curRDPTask == 0);
    if ( (__scSchedule (sc, &sp, &dp, state)) != state)
        __scExec(sc, sp, dp);
}

/*
 * __scHandleRDP is called when an RDP task signals that it has
 * finished
 */
void __scHandleRDP(OSSched *sc)
{
    OSScTask *t, *sp = 0, *dp = 0; 
    s32 state;
        
    assert(sc->curRDPTask);
    assert(sc->curRDPTask->list.t.type == M_GFXTASK);
    
    t = sc->curRDPTask;
    sc->curRDPTask = 0;
    
#ifdef SC_LOGGING    
    osLogEvent(l, 515, 3, t, t->state, t->flags);
#endif

    t->state &= ~OS_SC_NEEDS_RDP;

    __scTaskComplete(sc, t);

    state = ((sc->curRSPTask == 0) << 1) | (sc->curRDPTask == 0);
    if ( (__scSchedule (sc, &sp, &dp, state)) != state)
        __scExec(sc, sp, dp);
}

/*
 * __scTaskReady checks to see if the graphics task is able to run
 * based on the current state of the RCP.
 */
OSScTask *__scTaskReady(OSScTask *t) 
{

    if (t) {    
        /*
         * If there is a pending swap bail out til later (next
         * retrace).
         */
        if ((osViGetCurrentFramebuffer()) != (osViGetNextFramebuffer())) {
#ifdef SC_LOGGING
            osLogEvent(l, 513, 2, a, b);
#endif            
            return 0;
        }

        return t;
    }

    return 0;
}

/*
 * __scTaskComplete checks to see if the task is complete (all RCP
 * operations have been performed) and sends the done message to the
 * client if it is.
 */
s32 __scTaskComplete(OSSched *sc, OSScTask *t) {
    if ((t->state & OS_SC_RCP_MASK) == 0) {
        if (t->msgQ) {
            if (t->flags & OS_SC_LAST_TASK) {
                if (sc->frameCount <= 1) {
                    sc->unkTask = t;
                    return 1;
                }
                if (t->unk68 || t->msg) {
                    osSendMesg(t->msgQ, t->msg, OS_MESG_BLOCK);
                } else {
                    osSendMesg(t->msgQ, &D_800DE730, OS_MESG_BLOCK);
                }
                sc->frameCount = 0;
                return 1;
            }
            if (t->unk68 || t->msg) {
                osSendMesg(t->msgQ, t->msg, OS_MESG_BLOCK);
                return 1;
            }
            osSendMesg(t->msgQ, &D_800DE730, OS_MESG_BLOCK);
        }
        return 1;
    }
    return 0;
}

/*
 * Place task on either the audio or graphics queue
 */
void __scAppendList(OSSched *sc, OSScTask *t) 
{
    long type = t->list.t.type;
    
    assert ( (type == M_AUDTASK) || (type == M_GFXTASK));
    
    if (type == M_AUDTASK) {
        if (sc->audioListTail)
            sc->audioListTail->next = t;
        else
            sc->audioListHead = t;
            
        sc->audioListTail = t;
#ifdef SC_LOGGING
        osLogEvent(l, 506, 1, t);
#endif
    } else {
        if (sc->gfxListTail)
            sc->gfxListTail->next = t;
        else
            sc->gfxListHead = t;
        
	sc->gfxListTail = t;
#ifdef SC_LOGGING
        osLogEvent(l, 507, 1, t);
#endif
    }
    
    t->next = NULL;
    t->state = t->flags & OS_SC_RCP_MASK;    
}

/*
 * 
 */
void __scExec(OSSched *sc, OSScTask *sp, OSScTask *dp)
{
    
#ifdef SC_LOGGING
    osLogEvent(l, 511, 2, sp, dp);
#endif

    assert(sc->curRSPTask == 0);

    if (sp) {
        if (sp->list.t.type == M_AUDTASK) {
            osWritebackDCacheAll();  /* flush the cache */
            gRSPAudTaskFlushTime = osGetCount();

        }
    
        sp->state &= ~(OS_SC_YIELD | OS_SC_YIELDED);
#ifndef _FINALROM
	sp->startTime = osGetTime();
#endif
        osSpTaskLoad(&sp->list);
        osSpTaskStartGo(&sp->list);
        gCurRSPTaskCounter = 0;
        gCurRDPTaskCounter = 0;
        sc->curRSPTask = sp;
        if (sp == dp)
            sc->curRDPTask = dp;
    }

    if (dp && (dp != sp)) {
        assert(dp->list.t.output_buff);
    
#ifdef SC_LOGGING
        osLogEvent(l, 523, 3, dp, dp->list.t.output_buff,
                   (u32)*dp->list.t.output_buff_size);
#endif

        osDpSetNextBuffer(dp->list.t.output_buff,
                               *dp->list.t.output_buff_size);
        
        sc->curRDPTask = dp;
    }
}

static void __scYield(OSSched *sc) 
{

#ifdef SC_LOGGING
    osLogEvent(l, 503, 1, sc->curRSPTask );
#endif
    
    if (sc->curRSPTask->list.t.type == M_GFXTASK) {
    
/*	assert(sc->curRSPTask->state & OS_SC_YIELD);*/

        sc->curRSPTask->state |= OS_SC_YIELD;
        gYieldTime = osGetTime();

        osSpTaskYield();
    } else {
#ifdef SC_LOGGING
        osLogEvent(l, 508, 1, sc->curRSPTask);
#endif        
    }    
}

/*
 * Schedules the tasks to be run on the RCP
 */
s32 __scSchedule(OSSched *sc, OSScTask **sp, OSScTask **dp, s32 availRCP) 
{
    s32 avail = availRCP;
    OSScTask *gfx = sc->gfxListHead;
    OSScTask *audio = sc->audioListHead;

#ifdef SC_LOGGING
    osLogEvent(l, 517, 3, *sp, *dp, availRCP);
#endif    

    if (sc->doAudio && (avail & OS_SC_SP)) {

        if (gfx && (gfx->flags & OS_SC_PARALLEL_TASK)) {
            *sp = gfx;
            avail &= ~OS_SC_SP;
        } else {
            *sp = audio;
            avail &= ~OS_SC_SP;
            sc->doAudio = 0;
            sc->audioListHead = sc->audioListHead->next;
            if (sc->audioListHead == NULL)
                sc->audioListTail = NULL; 
        }        
    } else {            
#ifdef SC_LOGGING
        osLogEvent(l, 520, 1, gfx);
#endif        
        if (__scTaskReady(gfx)) {            

#ifdef SC_LOGGING
            osLogEvent(l, 522, 3, gfx, gfx->state, gfx->flags);
#endif        
            switch (gfx->flags & OS_SC_TYPE_MASK) {
              case (OS_SC_XBUS):
                  if (gfx->state & OS_SC_YIELDED) {
#ifdef SC_LOGGING
                      osLogEvent(l, 518, 0);
#endif                      
		      /* can hit this if RDP finishes at yield req */
                      /* assert(gfx->state & OS_SC_DP); */

                      if (avail & OS_SC_SP) {   /* if SP is available */
#ifdef SC_LOGGING
                      osLogEvent(l, 519, 0);
#endif                      
                          *sp = gfx;
                          avail &= ~OS_SC_SP;
                      
                          if (gfx->state & OS_SC_DP) {  /* if it needs DP */
                              *dp = gfx;
                              avail &= ~OS_SC_DP;

                              if (avail & OS_SC_DP == 0)
                                  assert(sc->curRDPTask == gfx);
                              
                          }

                          sc->gfxListHead = sc->gfxListHead->next;
                          if (sc->gfxListHead == NULL)
                              sc->gfxListTail = NULL;
                          
                      }                  
                  } else {
                      if (avail == (OS_SC_SP | OS_SC_DP)) {
                          *sp = *dp = gfx;
                          avail &= ~(OS_SC_SP | OS_SC_DP);
                          sc->gfxListHead = sc->gfxListHead->next;
                          if (sc->gfxListHead == NULL)
                              sc->gfxListTail = NULL;
                      }
                  }
                      
                  break;
          
              case (OS_SC_DRAM):
              case (OS_SC_DP_DRAM):
              case (OS_SC_DP_XBUS):
                  if (gfx->state & OS_SC_SP) {  /* if needs SP */
                      if (avail & OS_SC_SP) {   /* if SP is available */
                          *sp = gfx;
                          avail &= ~OS_SC_SP;
                      }
                  }
                  if (gfx->state & OS_SC_DP) {   /* if needs DP */
                      if (avail & OS_SC_DP) {        /* if DP available */
                          *dp = gfx;
                          avail &= ~OS_SC_DP;
                          sc->gfxListHead = sc->gfxListHead->next;
                          if (sc->gfxListHead == NULL)
                              sc->gfxListTail = NULL;
                      }
                  }
                  break;

              case (OS_SC_SP_DRAM):
              case (OS_SC_SP_XBUS):
              default:
                  break;
            }
        }
    }

    if (avail != availRCP)
        avail = __scSchedule(sc, sp, dp, avail);

    return avail;
    
}
