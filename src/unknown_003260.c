/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80002660 */

#include "unknown_003260.h"
#include "memory.h"

/************ .bss ************/

// All of these are defined in unknown_003260_bss.c
// This was needed, since there is a bss reordering issue with D_80119BD0 and gAlSndPlayer

extern s32 D_80115F90;
extern ALHeap *D_80115F94;
extern s32 D_80115F98[2];
extern s32 D_80115FA0[3];
extern OSThread audioThread;
extern OSMesgQueue OSMesgQueue_80116160;
extern OSMesg D_80116178[8];
extern OSMesgQueue D_80116198;
extern OSMesg D_801161B0[8];
extern ALGlobals ALGlobals_801161D0;
extern u64 audioStack[AUDIO_STACKSIZE/sizeof(u64)];
extern AMDMAState dmaState;
extern AMDMABuffer dmaBuffs[50];
extern u32 minFrameSize;
extern u32 framesize;
extern u32 maxFrameSize;
extern u32 nextDMA;
extern u32 frameSize;
extern u32 D_8011963c;
extern u32 maxRSPCmds;
extern OSIoMesg audDMAIOMesgBuf[NUM_DMA_MESSAGES];
extern OSMesgQueue audDMAMessageQ;
extern OSMesg audDMAMessageBuf[NUM_DMA_MESSAGES];
extern unk800DC6BC D_80119BD0;
extern u16 *D_80119C28;
extern f32 gVideoRefreshRate;

/******************************/

/************ .data ************/

u32 audFrameCt = 0;       // Currently unknown, might be a different type.
s32 D_800DC684 = 0;       // Currently unknown, might be a different type.
s32 D_800DC688 = 0;       // Currently unknown, might be a different type.
s32 D_800DC68C = 0;       // Currently unknown, might be a different type.
s32 gFunc80019808Checksum = 0x35281;
s32 gFunc80019808Length = 0xFD0;
s32 D_800DC698 = 0;       // Currently unknown, might be a different type.
s32 D_800DC69C = 0;       // Currently unknown, might be a different type.
s32 D_800DC6A0 = 1;       // Currently unknown, might be a different type.
s32 D_800DC6A4 = 0;       // Currently unknown, might be a different type.
s32 D_800DC6A8 = 0;       // Currently unknown, might be a different type.
s32 D_800DC6AC = 0;       // Currently unknown, might be a different type.

ALEventQueue *D_800DC6B0 = NULL;
s32 D_800DC6B4 = 0; // Currently unknown, might be a different type.
unk800DC6BC_40 *D_800DC6B8 = NULL;
unk800DC6BC *gAlSndPlayer = &D_80119BD0;

s32 sfxVolumeSlider = 256;
s32 D_800DC6C4 = 0; // Currently unknown, might be a different type.

/*******************************/

/************ .rodata ************/

// Debug strings
const char D_800E49F0[] = "audio manager: RCP audio interface bug caused DMA from bad address - move audiomgr.c in the makelist!\n";
const char D_800E4A58[] = "audio: ai out of samples\n";
const char D_800E4A74[] = "OH DEAR - No audio DMA buffers left\n";
const char D_800E4A9C[] = "Dma not done\n";
const char D_800E4AAC[] = "";
const char D_800E49B0[] = "Bad soundState: voices =%d, states free =%d, states busy =%d, type %d data %x\n";
const char D_800E4B00[] = "playing a playing sound\n";
const char D_800E4B1C[] = "Nonsense sndp event\n";
const char D_800E4B34[] = "Sound state allocate failed - sndId %d\n";
const char D_800E4B5C[] = "Don't worry - game should cope OK\n";
const char D_800E4B80[] = "WARNING: Attempt to stop NULL sound aborted\n";

/*********************************/

s32 __amDMA(s32 addr, s32 len, void *state);

#ifdef NON_EQUIVALENT
void audioNewThread(ALSynConfig *c, OSPri p, OSSched *arg2) {
    u32 *reg_v0;
    void *reg_s0;
    u32 tmp_size;
    s32 tmp;
    s32 i;
    D_80115F90 = arg2;
    D_80115F94 = c->heap;
    c->dmaproc = &__amDmaNew;
    c->outputRate = osAiSetFrequency(22050);
    framesize = (((f32)c->outputRate) * 2.0f) / gVideoRefreshRate;
    if (framesize < 0) {
    }

    // if (c->fxType == AL_FX_CUSTOM) {
    //     reg_v0 = load_asset_section_from_rom(ASSET_AUDIO_TABLE);
    //     tmp_size = reg_v0[9] - reg_v0[8];
    //     reg_s0 = allocate_from_main_pool_safe(tmp_size, COLOUR_TAG_CYAN);
    //     load_asset_to_address(39, reg_s0, reg_v0[8], tmp_size);
    //     c->params = reg_s0;
    //     c[1].maxVVoices = 0;
    //     alInit(&ALGlobals_801161D0, c);
    //     free_from_memory_pool(reg_s0);
    // } else {
    //     alInit(&ALGlobals_801161D0, c);
    // }
    // D_80119240[0].node.next = NULL;
    // D_80119240[0].node.prev = NULL;

    // for (i = 0; i < 0x30; i++) {
    //     alLink(&(D_80119240[i + 1].node), &(D_80119240[i].node));
    //     D_80119240[i].unk10 = alHeapDBAlloc(0, 0, c->heap, 1, 0x400);
    // }
    // D_80119240[i].unk10 = alHeapDBAlloc(0, 0, c->heap, 1, 0x400);
    alHeapDBAlloc(0, 0, c->heap, 1, 120);

    osCreateMesgQueue(&D_80116198, &D_801161B0, 8);
    osCreateMesgQueue(&OSMesgQueue_80116160, &D_80116178, 8);
    osCreateMesgQueue(&audDMAMessageQ, &audDMAMessageBuf, 50);

    osCreateThread(&audioThread, 4, &thread4_audio, NULL, &dmaState, p);
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_003260/audioNewThread.s")
#endif

void audioStartThread(void) {
    osStartThread(&audioThread);
}

void audioStopThread(void) {
    osStopThread(&audioThread);
}

/**
 * Main function for handling ingame audio. Loops continuously as long as the scheduler feeds it updates.
 */
void thread4_audio(UNUSED void *arg) {
    s32 audioThreadMarkExit;
    s16 *audioThreadRetraceMesg;
    s16 *audioThreadUpdateMesg;

    audioThreadMarkExit = FALSE;
    audioThreadRetraceMesg = NULL;
    audioThreadUpdateMesg = NULL;

    osScAddClient(D_80115F90, &audioStack, &OSMesgQueue_80116160, 1);
    while (!audioThreadMarkExit) {
        osRecvMesg(&OSMesgQueue_80116160, &audioThreadRetraceMesg, 1);
        switch (*audioThreadRetraceMesg) {
        case 1:
            func_80002C00(D_80115F98[(((u32) audFrameCt % 3))+2], audioThreadUpdateMesg);
            osRecvMesg(&D_80116198, &audioThreadUpdateMesg, 1);
            func_80002DF8(audioThreadUpdateMesg);
            break;
        case 4:
            // Mysterious void.
            break;
        case 10:
            audioThreadMarkExit = TRUE;
            break;
        }
    }
    alClose(&ALGlobals_801161D0);
}

GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80002C00.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80002DF8.s")

/******************************************************************************
 *
 * __amDMA This routine handles the dma'ing of samples from rom to ram.
 * First it checks the current buffers to see if the samples needed are
 * already in place. Because buffers are linked sequentially by the
 * addresses where the samples are on rom, it doesn't need to check all
 * of them, only up to the address that it needs. If it finds one, it
 * returns the address of that buffer. If it doesn't find the samples
 * that it needs, it will initiate a DMA of the samples that it needs.
 * In either case, it updates the lastFrame variable, to indicate that
 * this buffer was last used in this frame. This is important for the
 * __clearAudioDMA routine.
 *
 *****************************************************************************/
#ifdef NON_EQUIVALENT
#define DMA_BUFFER_LENGTH 0x400
s32 __amDMA(s32 addr, s32 len, void *state) {
    void            *foundBuffer;
    s32             delta, addrEnd, buffEnd;
    AMDMABuffer     *dmaPtr, *lastDmaPtr;

    lastDmaPtr = 0;
    dmaPtr = dmaState.firstUsed;
    addrEnd = addr+len;

    /* first check to see if a currently existing buffer contains the
       sample that you need.  */

    while(dmaPtr) {
        buffEnd = dmaPtr->startAddr + DMA_BUFFER_LENGTH;
        if(dmaPtr->startAddr > addr) /* since buffers are ordered */
            break;                   /* abort if past possible */

        else if(addrEnd <= buffEnd) { /* yes, found a buffer with samples */
            dmaPtr->lastFrame = audFrameCt; /* mark it used */
            foundBuffer = dmaPtr->ptr + addr - dmaPtr->startAddr;
            return (int) osVirtualToPhysical(foundBuffer);
        }
        lastDmaPtr = dmaPtr;
        dmaPtr = (AMDMABuffer*)dmaPtr->node.next;
    }

    /* get here, and you didn't find a buffer, so dma a new one */

    /* get a buffer from the free list */
    dmaPtr = dmaState.firstFree;

    /*
     * if you get here and dmaPtr is null, send back the a bogus
     * pointer, it's better than nothing
     */
    if(!dmaPtr) {
	    return osVirtualToPhysical(dmaState.firstUsed);
    }

    dmaState.firstFree = (AMDMABuffer*)dmaPtr->node.next;
    alUnlink((ALLink*)dmaPtr);

    /* add it to the used list */
    if(lastDmaPtr) { /* if you have other dmabuffers used, add this one */
                     /* to the list, after the last one checked above */
        alLink((ALLink*)dmaPtr,(ALLink*)lastDmaPtr);
    }
    else if(dmaState.firstUsed) { /* if this buffer is before any others */
                                  /* jam at begining of list */
        lastDmaPtr = dmaState.firstUsed;
        dmaState.firstUsed = dmaPtr;
        dmaPtr->node.next = (ALLink*)lastDmaPtr;
        dmaPtr->node.prev = 0;
        lastDmaPtr->node.prev = (ALLink*)dmaPtr;
    }
    else { /* no buffers in list, this is the first one */
        dmaState.firstUsed = dmaPtr;
        dmaPtr->node.next = 0;
        dmaPtr->node.prev = 0;
    }

    foundBuffer = dmaPtr->ptr;
    delta = addr & 0x1;
    addr -= delta;
    dmaPtr->startAddr = addr;
    dmaPtr->lastFrame = audFrameCt;  /* mark it */

    audDMAIOMesgBuf[nextDMA].hdr.pri      = OS_MESG_PRI_NORMAL;
    audDMAIOMesgBuf[nextDMA].hdr.retQueue = &audDMAMessageQ;
    audDMAIOMesgBuf[nextDMA].dramAddr     = foundBuffer;
    audDMAIOMesgBuf[nextDMA].devAddr      = (u32)addr;
    audDMAIOMesgBuf[nextDMA].size         = DMA_BUFFER_LENGTH;

    osPiStartDma(&audDMAIOMesgBuf[nextDMA++], 1, 0, addr, foundBuffer, 0x400U, &audDMAMessageQ);

    return (int) osVirtualToPhysical(foundBuffer) + delta;
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_003260/__amDMA.s")
#endif

/******************************************************************************
 *
 * __amDmaNew.  Initialize the dma buffers and return the address of the
 * procedure that will be used to dma the samples from rom to ram. This
 * routine will be called once for each physical voice that is created.
 * In this case, because we know where all the buffers are, and since
 * they are not attached to a specific voice, we will only really do any
 * initialization the first time. After that we just return the address
 * to the dma routine.
 *
 *****************************************************************************/
ALDMAproc __amDmaNew(AMDMAState **state) {
    int         i;

    if(!dmaState.initialized) {  /* only do this once */
        dmaState.firstUsed = 0;
        dmaState.firstFree = &dmaBuffs[0];
        dmaState.initialized = 1;
    }

    *state = &dmaState;  /* state is never used in this case */

    return __amDMA;
}

GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80003040.s")

void set_sfx_volume_slider(u32 volume) {
    if (volume > 256) {
        volume = 256;
    }

    sfxVolumeSlider = volume;
}

s32 sfxGetVolumeSlider(void) {
    return sfxVolumeSlider;
}

/**
 * Sets the number of active sound channels to either the passed number, or the maximum amount, whichever's lower.
 */
void set_sound_channel_count(s32 numChannels) {
    if (gAlSndPlayer->soundChannelsMax >= numChannels) {
        gAlSndPlayer->soundChannels = numChannels;
    } else {
        gAlSndPlayer->soundChannels = gAlSndPlayer->soundChannelsMax;
    }
}

void alSndPNew(audioMgrConfig *c) {
    u32 i;
    unk800DC6BC_40 *tmp1;
    ALEvent sp_38;

    gAlSndPlayer->soundChannelsMax = c->maxChannels;
    gAlSndPlayer->soundChannels = c->maxChannels;
    gAlSndPlayer->unk3C = 0;
    gAlSndPlayer->frameTime = 33000;
    gAlSndPlayer->unk40 = (unk800DC6BC_40 *)alHeapDBAlloc(0, 0, c->hp, 1, (c->unk00) << 6);
    alEvtqNew(&(gAlSndPlayer->evtq), alHeapDBAlloc(0, 0, c->hp, 1, (c->unk04) * 28), c->unk04);
    D_800DC6B8 = gAlSndPlayer->unk40;
    i = 1;
    for (i = 1; i < c->unk00; i++) {
        tmp1 = gAlSndPlayer->unk40;
        alLink(i + tmp1, i + tmp1 - 1);
    }

    D_80119C28 = alHeapDBAlloc(0, 0, c->hp, 2, c->unk10);
    for (i = 0; i < c->unk10; i++) {
        D_80119C28[i] = 32767;
    }

    gAlSndPlayer->drvr = alGlobals;
    gAlSndPlayer->node.next = NULL;
    gAlSndPlayer->node.handler = &_sndpVoiceHandler;
    gAlSndPlayer->node.clientData = gAlSndPlayer;

    alSynAddPlayer(gAlSndPlayer->drvr, gAlSndPlayer);
    sp_38.type = 32;
    alEvtqPostEvent(&(gAlSndPlayer->evtq), &sp_38, gAlSndPlayer->frameTime);
    gAlSndPlayer->nextDelta = alEvtqNextEvent(&(gAlSndPlayer->evtq), &(gAlSndPlayer->nextEvent));
}

#ifdef NON_EQUIVALENT
ALMicroTime _sndpVoiceHandler(void *node) {
    unk800DC6BC *sndp = (unk800DC6BC *)node;
    ALSndpEvent evt;

    do {
        switch (sndp->nextEvent.type) {
            case (AL_SNDP_API_EVT):
                //TODO cannot get this const to load into reg t7
                evt.snd_event.type = AL_SNDP_API_EVT;
                alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, sndp->frameTime);
                break;

            default:
                _handleEvent(sndp, (ALSndpEvent *)&sndp->nextEvent);
                break;
        }
        sndp->nextDelta = alEvtqNextEvent(&sndp->evtq, &sndp->nextEvent);

    } while (sndp->nextDelta == 0);
    sndp->curTime += sndp->nextDelta;
    return sndp->nextDelta;
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_003260/_sndpVoiceHandler.s")
#endif

GLOBAL_ASM("asm/non_matchings/unknown_003260/_handleEvent.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_8000410C.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_8000418C.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_800041FC.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_800042CC.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80004384.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80004520.s")

void func_80004604(u8 *arg0, u8 arg1) {
    if (arg0)
        arg0[0x36] = arg1;
}

u8 func_8000461C(u8 *arg0) {
    if (arg0)
        return arg0[0x3F];
    return 0;
}

void func_80004638(ALBank *bnk, s16 sndIndx, s32 arg2) {
    func_80004668(bnk, sndIndx, 0, arg2);
}

#ifdef NON_EQUIVALENT
void func_80004668(ALBank *bnk, s16 sndIndx, u8 arg2, s32 arg3) {
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80004668.s")
#endif

//input typing not right (some type of struct)
// 99% sure this function will clear the audio buffer associated with a given sound mask.
void func_8000488C(u8 *arg0) {
    ALEvent sp_18;
    sp_18.type = 1024;
    ((u32 *)(&sp_18))[1] = (u32)arg0;
    if (arg0) {
        arg0[0x3e] &= ~(1 << 4);
        alEvtqPostEvent(&(gAlSndPlayer->evtq), &sp_18, 0);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_003260/func_800048D8.s")

UNUSED void func_80004998(void) {
    func_800048D8(1);
}

UNUSED void func_800049B8(void) {
    func_800048D8(17);
}

void func_800049D8(void) {
    func_800048D8(3);
}

void func_800049F8(void *sndState, s16 type, u32 arg2) {
    ALSndpEvent sndEvt;
    sndEvt.snd_event.type = type;
    sndEvt.snd_event.state = sndState;
    sndEvt.snd_event.unk04 = arg2;
    if (sndState) {
        alEvtqPostEvent(&(gAlSndPlayer->evtq), &sndEvt, 0);
    }
}

u16 func_80004A3C(u8 arg0) {
    return D_80119C28[arg0];
}

//TODO: The structs used here are almost definitely wrong, but they do match,
//      so it can at least show the pattern we're looking for.
//arg0 = sound channel?
//arg1 = volume?
void func_80004A60(u8 arg0, u16 arg1) {
    OSIntMask mask;
    ALEventQueue *queue;
    UNUSED s32 pad;
    ALEvent evt;

    mask = osSetIntMask(1);
    queue = D_800DC6B0;
    D_80119C28[arg0] = arg1;

    while (queue != NULL) {
        //This is almost definitely the wrong struct list, but it matches so I'm not going to complain
        if ((((ALInstrument *)queue->allocList.next->prev)->priority & 0x3F) == arg0) {
            evt.type = 0x800;
            evt.msg.spseq.seq = (void *)queue;
            alEvtqPostEvent(&gAlSndPlayer->evtq, &evt, 0);
        }
        queue = (ALEventQueue *) queue->freeList.next;
    }

    osSetIntMask(mask);
}
