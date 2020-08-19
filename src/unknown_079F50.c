/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80079350 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

#define OS_SC_RETRACE_MSG       1
#define OS_SC_PRE_NMI_MSG       4
#define OS_SC_MAX_MESGS         8

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

extern OSViMode D_800E3900[];//osViModeTable;

void __scMain(void);

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
GLOBAL_ASM("asm/non_matchings/unknown_079F50/func_80079B44.s")
GLOBAL_ASM("asm/non_matchings/unknown_079F50/func_80079D5C.s")
GLOBAL_ASM("asm/non_matchings/unknown_079F50/func_80079DE8.s")
GLOBAL_ASM("asm/non_matchings/unknown_079F50/func_80079E40.s")
GLOBAL_ASM("asm/non_matchings/unknown_079F50/func_80079F40.s")
GLOBAL_ASM("asm/non_matchings/unknown_079F50/func_80079FA8.s")
GLOBAL_ASM("asm/non_matchings/unknown_079F50/func_8007A080.s")
GLOBAL_ASM("asm/non_matchings/unknown_079F50/func_8007A0D4.s")
GLOBAL_ASM("asm/non_matchings/unknown_079F50/func_8007A2D0.s")
