/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80079350 */

#include "sched.h"
#include "types.h"
#include "macros.h"
#include "f3ddkr.h"
#include "libultra_internal.h"

/************ .data ************/

// Unsure about if this is an array or struct.
s32 D_800DE730[] = { 0, 0 };
s32 D_800DE738[] = { 0, 8 };

f32 D_800DE740 = 0;
f32 D_800DE744 = 0;
f32 D_800DE748 = 0;
f32 D_800DE74C = 0;

s32 D_800DE750 = 0; // Currently unknown, might be a different type.
u32 D_800DE754 = 0;
u32 D_800DE758 = 0;
s32 D_800DE75C = 0; // Currently unknown, might be a different type.

s32 D_800DE760 = 0; // Currently unknown, might be a different type.
s32 D_800DE764 = 0; // Currently unknown, might be a different type.

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

s32 D_80126110;
s32 D_80126114;
OSTime D_80126118;
s32 D_80126120;
s32 D_80126124;
s32 D_80126128[18];

/*******************************/

void func_8007A080(OSSched *sc);
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
    osViSetMode(&osViModeTable[mode]);
    osViBlack(TRUE);

    osCreateMesgQueue(&sc->interruptQ, sc->intBuf, OS_SC_MAX_MESGS);
    osCreateMesgQueue(&sc->cmdQ, sc->cmdMsgBuf, OS_SC_MAX_MESGS);
    
    osSetEventMesg(OS_EVENT_SP, &sc->interruptQ, (OSMesg)667);
    osSetEventMesg(OS_EVENT_DP, &sc->interruptQ, (OSMesg)668);    
    osSetEventMesg(OS_EVENT_PRENMI, &sc->interruptQ, (OSMesg)669);    

    osViSetEvent(&sc->interruptQ, (OSMesg)666, numFields);


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

OSMesgQueue *osScGetInterruptQ(OSSched *sc) {
    return &sc->interruptQ;
}

// Unused.
void func_80079584(f32 *arg0, f32 *arg1, f32 *arg2) {
    *arg0 = D_800DE740;
    *arg1 = D_800DE748;
    *arg2 = D_800DE74C;
}

GLOBAL_ASM("lib/asm/non_matchings/sched/__scMain.s")

void func_80079760(OSSched *sc) {
    s32 sp24;
    s32 sp20;
    s32 sp1C;

    sp20 = 0;
    sp1C = 0;
    if (sc->audioListHead != 0) {
        sc->unk284 = 1;
    }
    if ((sc->unk284 != 0) && (sc->curRSPTask != 0)) {
        func_8007A080(sc);
    } else {
        sp24 = ((sc->curRSPTask == 0) << 1) | (sc->curRDPTask == 0);
        if (__scSchedule(sc, &sp20, &sp1C, sp24) != sp24) {
            __scExec(sc, sp20, sp1C);
        }
    }
}

void dummy_80079808() {
}
void dummy_80079810() {
}

GLOBAL_ASM("lib/asm/non_matchings/sched/func_80079818.s")
GLOBAL_ASM("lib/asm/non_matchings/sched/__scHandleRSP.s")

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

#if 0
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
#else
GLOBAL_ASM("lib/asm/non_matchings/sched/__scTaskComplete.s")
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
        
        sp->state &= ~0x30;
        osSpTaskLoad(&sp->list);
        osSpTaskStartGo(&sp->list); 
        D_800DE754 = 0;
        D_800DE758 = 0;
        sc->curRSPTask = sp;

        if (sp == dp)
            sc->curRDPTask = dp;
    }

    if (dp && (dp != sp)) {
        osDpSetNextBuffer(dp->list.t.output_buff,  *dp->list.t.output_buff_size);        
        sc->curRDPTask = dp;
    }
}

void func_8007A080(OSSched *sc) {
    if (sc->curRSPTask->list.t.type == M_GFXTASK) {
        sc->curRSPTask->state |= 0x10;
        D_80126118 = osGetTime();
        osSpTaskYield();
    } 
}

GLOBAL_ASM("lib/asm/non_matchings/sched/__scSchedule.s")

// This might need to be moved into it's own file.
void set_rsp_segment(Gfx **dlist, s32 segment, s32 base) {
    gSPSegment((*dlist)++, segment, base + 0x80000000)
}
