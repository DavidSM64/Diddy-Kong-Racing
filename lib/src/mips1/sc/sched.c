/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80079350 */

#include <assert.h>
#include "sched.h"
#include "types.h"
#include "macros.h"
#include "f3ddkr.h"
#include "libultra_internal.h"
#include "viint.h"
#include "main.h"

static void __scTaskComplete(OSSched *sc, OSScTask *t) {
    if (t->list.t.type == M_GFXTASK) {
        if (sc->scheduledFB == NULL) {
            sc->scheduledFB = t->framebuffer;
            osViSwapBuffer(t->framebuffer);
        } else {
            sc->queuedFB = t->framebuffer;
        }

        osSendMesg(sc->gfxmq, (OSMesg)OS_SC_DONE_MSG, OS_MESG_NOBLOCK);
        puppyprint_update_rsp(RSP_GFX_FINISHED);
    } else {
        osSendMesg(t->msgQ, t->msg, OS_MESG_NOBLOCK);
        puppyprint_update_rsp(RSP_AUDIO_FINISHED);
    }
}

static void __scExec(OSSched *sc, OSScTask *t) {
    if (t->list.t.type == M_AUDTASK) {
        osWritebackDCacheAll();
        puppyprint_update_rsp(RSP_AUDIO_START);
    } else {
        puppyprint_update_rsp(RSP_GFX_START);
    }

    t->state &= ~(OS_SC_YIELD | OS_SC_YIELDED);
    osSpTaskLoad(&t->list);
    osSpTaskStartGo(&t->list);

    sc->curRSPTask = t;

    if (t->list.t.type == M_GFXTASK) {
        sc->curRDPTask = t;
    }
}

static void __scTryDispatch(OSSched *sc) {
    if (sc->curRSPTask == NULL) {
        if (sc->doAudio) {
            OSScTask *t = sc->nextAudTask;
            sc->nextAudTask = NULL;
            sc->doAudio = 0;
            __scExec(sc, t);
        } else if (sc->curRDPTask == NULL && sc->queuedFB == NULL) {
            OSScTask *t = sc->nextGfxTask;

            if (t) {
                sc->nextGfxTask = sc->nextGfxTask2;
                sc->nextGfxTask2 = NULL;
                __scExec(sc, t);
            }
        }
    }
}

//-----------------------------------------------------------------------------\
//-- Event handlers -----------------------------------------------------------/
//----------------------------------------------------------------------------/

static void __scHandlePrenmi(OSSched *sc) {
    osSendMesg(sc->audmq, (OSMesg) &sc->prenmiMsg, OS_MESG_NOBLOCK);
    osSendMesg(sc->gfxmq, (OSMesg) OS_SC_PRE_NMI_MSG, OS_MESG_NOBLOCK);
}

static void __scHandleRetrace(OSSched *sc) {
    if (sc->scheduledFB && osViGetCurrentFramebuffer() == sc->scheduledFB) {
        if (sc->queuedFB) {
            sc->scheduledFB = sc->queuedFB;
            sc->queuedFB = NULL;
            osViSwapBuffer(sc->scheduledFB);
        } else {
            sc->scheduledFB = NULL;
        }
    }

    sc->alt ^= 1;

    if (sc->audmq && sc->alt == 0) {
        osSendMesg(sc->audmq, &sc->retraceMsg, OS_MESG_NOBLOCK);

        if (sc->nextAudTask) {
            sc->doAudio = 1;

            if (sc->curRSPTask && sc->curRSPTask->list.t.type == M_GFXTASK) {
                puppyprint_update_rsp(RSP_GFX_PAUSED);
                sc->curRSPTask->state |= OS_SC_YIELD;
                osSpTaskYield();
            }
        }
    }

    __scTryDispatch(sc);
}

static void __scHandleRSP(OSSched *sc) {
    OSScTask *t = sc->curRSPTask;
    sc->curRSPTask = NULL;

    if ((t->state & OS_SC_YIELD) && osSpTaskYielded(&t->list)) {
        t->state |= OS_SC_YIELDED;
        if ((t->flags & OS_SC_RCP_MASK) == OS_SC_XBUS) {
            sc->nextGfxTask2 = sc->nextGfxTask;
            sc->nextGfxTask = t;
            puppyprint_update_rsp(RSP_GFX_RESUME);
        }
        sc->curRDPTask = NULL;
    } else {
        t->state &= ~OS_SC_NEEDS_RSP;
        if ((t->state & OS_SC_RCP_MASK) == 0) {
            __scTaskComplete(sc, t);
        }
    }

    __scTryDispatch(sc);
}

static void __scHandleRDP(OSSched *sc) {
    OSScTask *t = sc->curRDPTask;
    sc->curRDPTask = NULL;

    t->state &= ~OS_SC_NEEDS_RDP;
    update_rdp_profiling();

    if ((t->state & OS_SC_RCP_MASK) == 0) {
        __scTaskComplete(sc, t);
    }

    __scTryDispatch(sc);
}

static void __scMain(void *arg) {
    void (*msg)(OSSched *sc);
    OSSched *sc = (OSSched *)arg;

    while (1) {
        osRecvMesg(&sc->interruptQ, (OSMesg *)&msg, OS_MESG_BLOCK);
        msg(sc);
    }
}

//-----------------------------------------------------------------------------\
//-- Public functions ---------------------------------------------------------/
//----------------------------------------------------------------------------/

void osScSubmitAudTask(OSSched *sc, OSScTask *t) {
    OSPri prevpri = osGetThreadPri(0);
    osSetThreadPri(0, OS_SC_PRIORITY + 1);

    t->state = OS_SC_NEEDS_RSP;
    sc->nextAudTask = t;

    osSetThreadPri(0, prevpri);
}

void osScSubmitGfxTask(OSSched *sc, OSScTask *t) {
    OSPri prevpri = osGetThreadPri(0);
    osSetThreadPri(0, OS_SC_PRIORITY + 1);

    t->state = OS_SC_NEEDS_RSP | OS_SC_NEEDS_RDP;

    if (sc->curRSPTask == NULL && sc->curRDPTask == NULL && sc->queuedFB == NULL) {
        __scExec(sc, t);
    } else {
        if (sc->nextGfxTask == NULL) {
            sc->nextGfxTask = t;
        } else {
            sc->nextGfxTask2 = t;
        }
    }

    osSetThreadPri(0, prevpri);
}

void osScAddClient(OSSched *sc, OSScClient *c, OSMesgQueue *msgQ, u8 id) {
    OSIntMask mask = osSetIntMask(OS_IM_NONE);

    if (id == OS_SC_ID_VIDEO) {
        sc->gfxmq = msgQ;
    } else if (id == OS_SC_ID_AUDIO) {
        sc->audmq = msgQ;
    }

    osSetIntMask(mask);
}

extern OSViMode osViModeNtscLpn1, osViModePalLpn1, osViModeMpalLpn1, osViModePalLan1, osViModeNtscLan1, osViModeMpalLan1;

void osCreateScheduler(OSSched *sc, void *stack, OSPri priority, u8 mode, u8 numFields) {
    sc->audmq           = NULL;
    sc->gfxmq           = NULL;
    sc->curRSPTask      = NULL;
    sc->curRDPTask      = NULL;
    sc->nextAudTask     = NULL;
    sc->nextGfxTask     = NULL;
    sc->nextGfxTask2    = NULL;
    sc->scheduledFB     = NULL;
    sc->queuedFB        = NULL;
    sc->retraceMsg.type = OS_SC_RETRACE_MSG;
    sc->prenmiMsg.type  = OS_SC_PRE_NMI_MSG;
    sc->alt             = 0;

    osCreateViManager(OS_PRIORITY_VIMGR);
    osViSetMode(&osViModeNtscLan1);
    osViBlack(TRUE);
    osCreateMesgQueue(&sc->interruptQ, sc->intBuf, OS_SC_MAX_MESGS);
    osCreateMesgQueue(&sc->cmdQ, sc->cmdMsgBuf, OS_SC_MAX_MESGS);
    osSetEventMesg(OS_EVENT_SP, &sc->interruptQ, (OSMesg)&__scHandleRSP);
    osSetEventMesg(OS_EVENT_DP, &sc->interruptQ, (OSMesg)&__scHandleRDP);
    osSetEventMesg(OS_EVENT_PRENMI, &sc->interruptQ, (OSMesg)&__scHandlePrenmi);

    osViSetEvent(&sc->interruptQ, (OSMesg)&__scHandleRetrace, numFields);

    osCreateThread(&sc->thread, 5, __scMain, (void *)sc, stack, priority);
    osStartThread(&sc->thread);
}
