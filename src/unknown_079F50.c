/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80079350 */

#include "types.h"
#include "macros.h"
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

typedef struct {
    OSScMsg     retraceMsg;
    OSScMsg     prenmiMsg;
    OSMesgQueue interruptQ;
    OSMesg      intBuf[OS_SC_MAX_MESGS];
    OSMesgQueue cmdQ;
    OSMesg      cmdMsgBuf[OS_SC_MAX_MESGS];
    OSThread    thread;
    OSScClient  *clientList;
    OSScTask    *audioListHead;
    OSScTask    *gfxListHead;
    OSScTask    *audioListTail;
    OSScTask    *gfxListTail;
    OSScTask    *curRSPTask;
    OSScTask    *curRDPTask;
    u32         frameCount;
    s32         doAudio;
} OSSched;

typedef struct{
    u8 pad00[0x50];
}unk800E3900;


/************ .data ************/

// Unsure about if this is an array or struct.
s32 D_800DE730[] = { 0, 0 };
s32 D_800DE738[] = { 0, 8 };

s32 D_800DE740 = 0; // Currently unknown, might be a different type.
s32 D_800DE744 = 0; // Currently unknown, might be a different type.
s32 D_800DE748 = 0; // Currently unknown, might be a different type.
s32 D_800DE74C = 0; // Currently unknown, might be a different type.

s32 D_800DE750 = 0; // Currently unknown, might be a different type.
u32 D_800DE754 = 0;
u32 D_800DE758 = 0;
s32 D_800DE75C = 0; // Currently unknown, might be a different type.

s32 D_800DE760 = 0; // Currently unknown, might be a different type.
s32 D_800DE764 = 0; // Currently unknown, might be a different type.

/*******************************/

extern OSViMode D_800E3900[];//osViModeTable;

extern s32 D_80126120;

void __scMain(void);
void __scExec(OSSched *sc, OSScTask *sp, OSScTask *dp);

void osCreateScheduler(OSSched *sc, void *stack, OSPri priority, u8 mode, u8 numFields){
    sc->curRSPTask      = 0;
    sc->curRDPTask      = 0;
    sc->clientList      = 0;
    
    sc->audioListHead   = 0;
    sc->gfxListHead     = 0;
    sc->audioListTail   = 0;
    sc->gfxListTail     = 0;
    sc->doAudio         = 0;
    sc->frameCount      = 0;
    sc->retraceMsg.type = OS_SC_RETRACE_MSG;  /* sent to apps */
    sc->prenmiMsg.type  = OS_SC_PRE_NMI_MSG;
    
    /*
     * Set up video manager, listen for Video, RSP, and RDP interrupts
     */
    osCreateViManager(OS_PRIORITY_VIMGR);    
    osViSetMode(&D_800E3900[mode]);
    osViBlack(TRUE);

    osCreateMesgQueue(&sc->interruptQ, sc->intBuf, OS_SC_MAX_MESGS);
    osCreateMesgQueue(&sc->cmdQ, sc->cmdMsgBuf, OS_SC_MAX_MESGS);
    
    osSetEventMesg(OS_EVENT_SP, &sc->interruptQ, (OSMesg)667);
    osSetEventMesg(OS_EVENT_DP, &sc->interruptQ, (OSMesg)668);    
    osSetEventMesg(OS_EVENT_PRENMI, &sc->interruptQ, (OSMesg)669);    

    osViSetEventMsg(&sc->interruptQ, (OSMesg)666, numFields);    


    osCreateThread(&sc->thread, 5, __scMain, (void *)sc, stack, priority);
    osStartThread(&sc->thread);
}

void osScAddClient(OSSched *sc, OSScClient *c, OSMesgQueue *msgQ, u8 arg3){
    OSIntMask mask;

    mask = osSetIntMask(OS_IM_NONE);

    c->msgQ = msgQ;
    c->next = sc->clientList;
    c->unk0 = arg3;
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

OSMesgQueue *osScGetCmdQ(OSSched *sc){
    return &sc->cmdQ;
}

GLOBAL_ASM("asm/non_matchings/unknown_079F50/func_8007957C.s")
GLOBAL_ASM("asm/non_matchings/unknown_079F50/__scMain.s")
GLOBAL_ASM("asm/non_matchings/unknown_079F50/func_80079760.s")
GLOBAL_ASM("asm/non_matchings/unknown_079F50/func_80079818.s")


#if 1 
GLOBAL_ASM("asm/non_matchings/unknown_079F50/func_80079B44.s")
#else
extern f32 D_800DE740;
extern f32 D_800DE744;
extern f32 D_800DE748;
extern f32 D_800DE74C;
extern u32 D_800DE750;
extern f32 D_800E796C;
extern u32 D_80126124;
void func_80079B44(OSSched *sc){
    OSScTask *t, *sp = 0, *dp = 0;
    s32 state;
    u32 delta;
    f32 tmp1;

    
   //assert(sc->curRSPTask);

    t = sc->curRSPTask;
    sc->curRSPTask = 0;
    
    if (t->list.t.type == 2) {
        D_80126124 = osGetCount();
        delta = D_80126124 - D_80126120;
        tmp1 = (f32) delta;
        if(delta < 0){
            tmp1 += 4294967296.0;
        }
        D_800DE74C = tmp1*60.0f/D_800E796C;
        D_800DE744 = D_800DE744 + D_800DE74C;
        if(D_800DE740 < D_800DE74C){
            D_800DE740 = D_800DE74C;
        }
        if(D_800DE750%1000 == 1 || D_800DE750%1000 == 2){
            D_800DE748 = D_800DE744/500.0f;
            D_800DE744 = 0.0f;
            D_800DE740 = 0.0f;
        }
    }
    if(t->state & 0x10){
        if(func_800D1DF0(&(t->list))){
            t->state |= 0x20;
            if ((t->flags & 0x07) == -3) {
    
            /* push the task back on the list */
                t->next = sc->gfxListHead;
                sc->gfxListHead = t;
                if (sc->gfxListTail == 0)
                    sc->gfxListTail = t;
            }
        }
        else{
            t->state &= -3;
        }
    } 
    else {
        t->state &= -3;
        __scTaskComplete(sc, t);
    }

    state = ((sc->curRSPTask == 0) << 1) | (sc->curRDPTask == 0);
    if ( (__scSchedule (sc, &sp, &dp, state)) != state)
        __scExec(sc, sp, dp);
}
#endif

void __scHandleRDP(OSSched *sc){
    OSScTask *t, *sp = 0, *dp = 0; 
    s32 state;
    
    t = sc->curRDPTask;
    sc->curRDPTask = 0;

    t->state &= -2;

    __scTaskComplete(sc, t);

    state = ((sc->curRSPTask == 0) << 1) | (sc->curRDPTask == 0);
    if ( (__scSchedule(sc, &sp, &dp, state)) != state)
        __scExec(sc, sp, dp);
}


OSScTask *__scTaskReady(OSScTask *t){
    if (t) {    
        /*
         * If there is a pending swap bail out til later (next
         * retrace).
         */
        if (osViGetCurrentFramebuffer() != osViGetNextFramebuffer()) {           
            return 0;
        }

        return t;
    }

    return 0;
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_079F50/__scTaskComplete.s")
#else
s32 __scTaskComplete(OSSched *sc, OSScTask *t) {
    int rv;
    int firsttime = 1;

    if ((t->state & 0x03) == 0) { /* none of the needs bits set */

        assert (t->msgQ);
        if(t->msgQ){

            //rv = osSendMesg(t->msgQ, &t->msg, OS_MESG_BLOCK);

            //if (t->list.t.type == M_GFXTASK) {
                    if ((t->flags & 0x20) /*&& (t->flags & OS_SC_LAST_TASK)*/){
                        if(sc->doAudio < 2){
                            sc->frameCount = t;
                        }
                        else{
                            if(t->startTime == 0){
                                osSendMesg(t->msgQ, t->msg, 1);
                            }
                        }
                        //if (firsttime) {
                         //       osViBlack(FALSE);
                          //  firsttime = 0;
                        //}
                        //osViSwapBuffer(t->framebuffer);
                    }
            //}
        }
        return 1;
    }
    
    return 0;
}
#endif

void __scAppendList(OSSched *sc, OSScTask *t) {
   u32 tmp = t->list.t.type;
   if (tmp == 2){
        if(sc->audioListTail)
            sc->audioListTail->next = t;
        else
            sc->audioListHead = t;

        sc->audioListTail = t;
   }
   else{
        if(sc->gfxListTail)
            sc->gfxListTail->next = t;
        else
            sc->gfxListHead = t;

        sc->gfxListTail = t;
   }
    t->next = NULL;
    t->state = t->flags & 0x03;
}

void __scExec(OSSched *sc, OSScTask *sp, OSScTask *dp){

    if (sp) {
        if (sp->list.t.type == M_AUDTASK) {
            osWritebackDCacheAll();  /* flush the cache */
            D_80126120 = osGetCount();
        }
        
        //sp->state &= ~(OS_SC_YIELD | OS_SC_YIELDED);
        sp->state &= -49;
        osSpTaskLoad(&sp->list);
        osSpTaskStartGo(&sp->list); 
        D_800DE754 = 0;
        D_800DE758 = 0;
        sc->curRSPTask = sp;

        if (sp == dp)
            sc->curRDPTask = dp;
    }

    if (dp && (dp != sp)) {
        osDpSetNextBuffer(dp->list.t.output_buff,
                               *dp->list.t.output_buff_size);        
        sc->curRDPTask = dp;
    }
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_079F50/func_8007A080.s")
#else
extern OSTime D_80126118;
void func_8007A080(OSSched *sc) {
    if (sc->curRSPTask->list.t.type == M_GFXTASK) {

        //sc->curRSPTask->state |= OS_SC_YIELD;
        sc->curRSPTask->state |= 0x10;
        D_80126118 = osGetTime(); //TODO extra lui
        osSpTaskYield();
    } 
}
#endif
GLOBAL_ASM("asm/non_matchings/unknown_079F50/__scSchedule.s")
GLOBAL_ASM("asm/non_matchings/unknown_079F50/func_8007A2D0.s")
