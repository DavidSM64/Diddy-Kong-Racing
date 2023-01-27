/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80002660 */

#include "unknown_003260.h"
#include "memory.h"
#include "audio_internal.h"
#include "video.h"
#include "math_util.h"
#include "asset_loading.h"
#include "objects.h"

/************ .bss ************/

// All of these are defined in unknown_003260_bss.c
// This was needed, since there is a bss reordering issue with D_80119BD0 and gAlSndPlayer

extern OSSched *gAudioSched;
extern ALHeap *gAudioHeap;
extern Acmd *ACMDList[2];
extern s32 D_80115FA0[3];
extern OSThread audioThread;
extern OSMesgQueue gAudioMesgQueue;
extern OSMesg gAudioFrameMsgBuf[8];
extern OSMesgQueue audioReplyMsgQ;
extern OSMesg gAudioReplyMsgBuf[8];
extern ALGlobals ALGlobals_801161D0;
extern u64 audioStack[AUDIO_STACKSIZE/sizeof(u64)];
extern AMDMAState dmaState;
extern AMDMABuffer dmaBuffs[50];
extern u32 minFrameSize;
extern u32 framesize;
extern u32 maxFrameSize;
extern u32 nextDMA;
extern u32 D_8011963c;
extern u32 maxRSPCmds;
extern OSIoMesg audDMAIOMesgBuf[NUM_DMA_MESSAGES];
extern OSMesgQueue audDMAMessageQ;
extern OSMesg audDMAMessageBuf[NUM_DMA_MESSAGES];
extern unk800DC6BC D_80119BD0;
extern u16 *gSoundChannelVolume;

/******************************/

/************ .data ************/

u32 audFrameCt = 0;
u32 nextDMA = 0;
u32 curAcmdList = 0;
s8 gAntiPiracyAudioFreq = 0;       // Anti Piracy - Sets random audio frequency?
s32 gFunc80019808Checksum = 0x35281;
s32 gFunc80019808Length = 0xFD0;
s16 *gLastAudioPtr = 0;
s32 gLastAudioFrameSamples = 0;

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

/**** private routines ****/
static void __amMain(UNUSED void *arg);
static s32 __amDMA(s32 addr, s32 len, void *state);
static ALDMAproc __amDmaNew(AMDMAState **state);
static u32  __amHandleFrameMsg(AudioInfo *info, AudioInfo *lastInfo);
static void __amHandleDoneMsg(AudioInfo *info);
static void __clearAudioDMA(void);
static void _removeEvents(ALEventQueue *, ALSoundState *, u16);

extern void alInit(ALGlobals *g, ALSynConfig *c);
extern s16 gDMABufferLength;
#define NUM_ACMD_LISTS 2

/******************************************************************************
 * Audio Manager API
 *****************************************************************************/
void amCreateAudioMgr(ALSynConfig *c, OSPri pri, OSSched *audSched) {
    s32 i;
    f32 fsize;
    uintptr_t *asset;
    u32 *assetAudioTable;
    s32 *asset8;
    s32 assetSize;
    s32 checksum;
    u8 *crc_region_start;
    u8 *crc_region;

    gAudioSched = audSched;
    gAudioHeap = c->heap;

    c->dmaproc = &__amDmaNew;
    c->outputRate = osAiSetFrequency(OUTPUT_RATE);

    /*
     * Calculate the frame sample parameters from the
     * video field rate and the output rate
     */
    fsize = (f32) c->outputRate * 2 / (f32) gVideoRefreshRate;
    framesize = (s32) fsize;
    if (framesize < fsize) {
        framesize++;
    }
    if (framesize & 0xf) {
        framesize = (framesize & ~0xf) + 0x10;
    }
    minFrameSize = framesize - 16;
    maxFrameSize = framesize + EXTRA_SAMPLES + 16;

    if (c->fxType[0] == AL_FX_CUSTOM) {
        assetAudioTable = load_asset_section_from_rom(ASSET_AUDIO_TABLE);
        assetSize = assetAudioTable[ASSET_AUDIO_9] - assetAudioTable[ASSET_AUDIO_8];
        asset8 = allocate_from_main_pool_safe(assetSize, COLOUR_TAG_CYAN);
        load_asset_to_address(ASSET_AUDIO, (u32) asset8, assetAudioTable[ASSET_AUDIO_8], assetSize);
        c->params = asset8;
        c[1].maxVVoices = 0;
        alInit(&ALGlobals_801161D0, c);
        free_from_memory_pool(asset8);
    } else {
        alInit(&ALGlobals_801161D0, c);
    }

    dmaBuffs[0].node.prev = 0;
    dmaBuffs[0].node.next = 0;

    for (i = 0; i < NUM_DMA_BUFFERS - 1; i++) {
        alLink((ALLink *) &(dmaBuffs[i + 1]), (ALLink *) &(dmaBuffs[i]));
        dmaBuffs[i].ptr = alHeapDBAlloc(0, 0, c->heap, 1, DMA_BUFFER_LENGTH);
    }
    /* last buffer already linked, but still needs buffer */
    dmaBuffs[i].ptr = alHeapDBAlloc(0, 0, c->heap, 1, DMA_BUFFER_LENGTH);

    // Antipiracy measure
    gDMABufferLength = DMA_BUFFER_LENGTH;
    checksum = (s32) &func_80019808 - gDMABufferLength;
    crc_region_start = (u8 *) checksum;
    crc_region = &crc_region_start[gDMABufferLength];
    gAntiPiracyAudioFreq = FALSE;
    i = 0;
    for (checksum = 0; i < gFunc80019808Length; i++) {
        checksum += crc_region[i];
        gDMABufferLength++;
    }
    if (checksum != gFunc80019808Checksum) {
        gAntiPiracyAudioFreq = TRUE;
    }

    for (i = 0; i < NUM_ACMD_LISTS; i++) {
        ACMDList[i] = (Acmd *) alHeapDBAlloc(0, 0, c->heap, 1,
            0xA000); //sizeof(Acmd) * DMA_BUFFER_LENGTH * 5?
    }

    asset = allocate_at_address_in_main_pool((maxFrameSize * 12), (u8 *)(0x803FFE00 - (maxFrameSize * 12)), COLOUR_TAG_CYAN);

    /**** initialize the done messages ****/
    for (i = 0; i < NUM_ACMD_LISTS + 1; i++) {
        ACMDList[i + NUM_ACMD_LISTS] = (Acmd *) alHeapDBAlloc(0, 0, c->heap, 1, 120);
        ACMDList[i + NUM_ACMD_LISTS]->words.w0 = (uintptr_t) asset;
        asset += maxFrameSize;
    }

    osCreateMesgQueue(&audioReplyMsgQ, gAudioReplyMsgBuf, MAX_MESGS);
    osCreateMesgQueue(&gAudioMesgQueue, gAudioFrameMsgBuf, MAX_MESGS);
    osCreateMesgQueue(&audDMAMessageQ, audDMAMessageBuf, NUM_DMA_MESSAGES);

    osCreateThread(&audioThread, 4, __amMain, 0,
                    (void *)(audioStack+AUDIO_STACKSIZE/sizeof(u64)), pri);
}

void audioStartThread(void) {
    osStartThread(&audioThread);
}

void audioStopThread(void) {
    osStopThread(&audioThread);
}

/******************************************************************************
 *
 * Audio Manager implementation. This thread wakes up at every retrace,
 * and builds an audio task, which it returns to the scheduler, who then
 * is responsible for its finally execution on the RSP. Once the task has
 * finished execution, the scheduler sends back a message saying the task
 * is complete. The audio is triple buffered because the switching to a new
 * audio buffer does not occur exactly at the gfx swapbuffer time.  With
 * 3 buffers you ensure that the program does not destroy data before it is
 * played.
 *
 *****************************************************************************/
/**
 * Main function for handling ingame audio. Loops continuously as long as the scheduler feeds it updates.
 */
static void __amMain(UNUSED void *arg) {
    s32 done = 0;
    AudioMsg *msg = NULL;
    AudioInfo *lastInfo = 0;

    osScAddClient(gAudioSched, (OSScClient *) &audioStack, &gAudioMesgQueue, OS_MESG_BLOCK);
    while (!done) {
        (void) osRecvMesg(&gAudioMesgQueue, (OSMesg *) &msg, 1);
        switch (msg->gen.type) {
        case OS_SC_RETRACE_MSG:
            //TODO: Check type of ACMDList?
            __amHandleFrameMsg((AudioInfo *) ACMDList[(((u32) audFrameCt % 3))+2], lastInfo);
            /* wait for done message */
            osRecvMesg(&audioReplyMsgQ, (OSMesg *) &lastInfo, OS_MESG_BLOCK);
            __amHandleDoneMsg(lastInfo);
            break;
        case OS_SC_PRE_NMI_MSG:
            /* what should we really do here? quit? ramp down volume? */
            break;
        case QUIT_MSG:
            done = 1;
            break;
        default:
            break;
        }
    }
    alClose(&ALGlobals_801161D0);
}

/******************************************************************************
 *
 * __amHandleFrameMsg. First, clear the past audio dma's, then calculate 
 * the number of samples you will need for this frame. This value varies
 * due to the fact that audio is synchronised off of the video interupt 
 * which can have a small amount of jitter in it. Varying the number of 
 * samples slightly will allow you to stay in synch with the video. This
 * is an advantageous thing to do, since if you are in synch with the 
 * video, you will have fewer graphics yields. After you've calculated 
 * the number of frames needed, call alAudioFrame, which will call all
 * of the synthesizer's players (sequence player and sound player) to
 * generate the audio task list. If you get a valid task list back, put
 * it in a task structure and send a message to the scheduler to let it
 * know that the next frame of audio is ready for processing.
 *
 *****************************************************************************/
static u32 __amHandleFrameMsg(AudioInfo *info, AudioInfo *lastInfo) {
    s16 *audioPtr;
    Acmd *cmdp;
    int samplesLeft = 0;
    OSScTask *t;
    u32 ret;

    
    __clearAudioDMA(); /* call once a frame, before doing alAudioFrame */

    audioPtr = (s16 *) osVirtualToPhysical(info->data);
    
    if (lastInfo) {
        s16 *outputDataPointer;
        s32 frameSamples;

        gLastAudioPtr = outputDataPointer = lastInfo->data;
        gLastAudioFrameSamples = frameSamples = lastInfo->frameSamples << 2;
        osAiSetNextBuffer(outputDataPointer, frameSamples);

        // Antipiracy measure
        if (gAntiPiracyAudioFreq != 0) {
            osAiSetFrequency(get_random_number_from_range(0, 10000) + OUTPUT_RATE);
        }
    }

    
    /* calculate how many samples needed for this frame to keep the DAC full */
    /* this will vary slightly frame to frame, must recalculate every frame */
    samplesLeft = osAiGetLength() >> 2; /* divide by four, to convert bytes */
                                        /* to stereo 16 bit samples */
    info->frameSamples = (16 + (framesize - samplesLeft + EXTRA_SAMPLES)) & ~0xf;
    if ((u32)info->frameSamples < minFrameSize)
        info->frameSamples = minFrameSize;

    cmdp = alAudioFrame(ACMDList[curAcmdList], &gAudioCmdLen, audioPtr,
                        info->frameSamples);

    t = &info->task;
    
    t->next      = 0;                    /* paranoia */
    t->msgQ      = &audioReplyMsgQ; /* reply to when finished */
    //TODO: This should be &info->msg, but the struct is likely modified.
    t->msg       = (OSMesg) &info->data;   /* reply with this message */
    t->flags     = OS_SC_NEEDS_RSP;
    t->unk58 = -1;
    t->unk60 = 0xFF;
    t->unk5C = 0;
    t->unk64 = 0;
    
    t->list.t.data_ptr    = (u64 *) ACMDList[curAcmdList];
    t->list.t.data_size   = (cmdp - ACMDList[curAcmdList]) * sizeof(Acmd);
    t->list.t.type  = M_AUDTASK;
    t->list.t.ucode_boot = (u64 *)rspF3DDKRBootStart;
    t->list.t.ucode_boot_size =
        ((int) rspF3DDKRDramStart - (int) rspF3DDKRBootStart);
    t->list.t.flags  = OS_TASK_DP_WAIT;
    t->list.t.ucode = (u64 *) aspMainTextStart;
    t->list.t.ucode_data = (u64 *) aspMainDataStart;
    t->list.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    t->list.t.yield_data_ptr = NULL;
    t->list.t.yield_data_size = 0;
    t->unk6C = 1;

    ret = osSendMesg(osScGetCmdQ(gAudioSched), (OSMesg) t, OS_MESG_NOBLOCK);
    
    curAcmdList ^= 1; /* swap which acmd list you use each frame */    
    
    return ret;
}

/******************************************************************************
 *
 * __amHandleDoneMsg. Really just debugging info in this frame. Checks
 * to make sure we completed before we were out of samples.
 *
 *****************************************************************************/
static void __amHandleDoneMsg(UNUSED AudioInfo *info) {
    s32    samplesLeft;
    static int firstTime = 1;

    samplesLeft = osAiGetLength()>>2;
    if (samplesLeft == 0 && !firstTime) {
        //stubbed_printf("audio: ai out of samples\n");    
        firstTime = 0;
    }
}

UNUSED s32 D_800DC6A4 = 0;       // Currently unknown, might be a different type.
UNUSED s32 D_800DC6A8 = 0;       // Currently unknown, might be a different type.
UNUSED s32 D_800DC6AC = 0;       // Currently unknown, might be a different type.

ALEventQueue *D_800DC6B0 = NULL;
s32 D_800DC6B4 = 0; // Currently unknown, might be a different type.
unk800DC6BC_40 *D_800DC6B8 = NULL;
unk800DC6BC *gAlSndPlayer = &D_80119BD0;

s32 sfxVolumeSlider = 256;
s32 D_800DC6C4 = 0; // Currently unknown, might be a different type.

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
s32 __amDMA(s32 addr, s32 len, UNUSED void *state) {
    void            *foundBuffer;
    s32             delta, addrEnd, buffEnd;
    AMDMABuffer     *dmaPtr, *lastDmaPtr;
    UNUSED s32 pad;

    lastDmaPtr = 0;
    delta = addr & 1;
    dmaPtr = dmaState.firstUsed;
    addrEnd = addr+len;

    /* first check to see if a currently existing buffer contains the
       sample that you need.  */

    while (dmaPtr) {
        buffEnd = dmaPtr->startAddr + DMA_BUFFER_LENGTH;
        if(dmaPtr->startAddr > (u32)addr) /* since buffers are ordered */
            break;                   /* abort if past possible */

        else if(addrEnd <= buffEnd) { /* yes, found a buffer with samples */
            dmaPtr->lastFrame = audFrameCt; /* mark it used */
            foundBuffer = dmaPtr->ptr + addr - dmaPtr->startAddr;
            return (int) osVirtualToPhysical(foundBuffer);
        }
        lastDmaPtr = dmaPtr;
        dmaPtr = (AMDMABuffer * )dmaPtr->node.next;
    }

    /* get here, and you didn't find a buffer, so dma a new one */

    /* get a buffer from the free list */
    dmaPtr = dmaState.firstFree;

    if (!dmaPtr && !lastDmaPtr) {
        lastDmaPtr = dmaState.firstUsed;
    }

    /*
     * if you get here and dmaPtr is null, send back the a bogus
     * pointer, it's better than nothing
     */
    if (!dmaPtr) {
	    return (int) osVirtualToPhysical(lastDmaPtr->ptr) + delta;
    }

    dmaState.firstFree = (AMDMABuffer *) dmaPtr->node.next;
    alUnlink((ALLink *) dmaPtr);

    /* add it to the used list */
    if (lastDmaPtr) { /* if you have other dmabuffers used, add this one */
                     /* to the list, after the last one checked above */
        alLink((ALLink *) dmaPtr, (ALLink *) lastDmaPtr);
    }
    else if (dmaState.firstUsed) { /* if this buffer is before any others */
                                  /* jam at begining of list */
        lastDmaPtr = dmaState.firstUsed;
        dmaState.firstUsed = dmaPtr;
        dmaPtr->node.next = (ALLink *) lastDmaPtr;
        dmaPtr->node.prev = 0;
        lastDmaPtr->node.prev = (ALLink *) dmaPtr;
    }
    else { /* no buffers in list, this is the first one */
        dmaState.firstUsed = dmaPtr;
        dmaPtr->node.next = 0;
        dmaPtr->node.prev = 0;
    }

    foundBuffer = dmaPtr->ptr;
    addr -= delta;
    dmaPtr->startAddr = addr;
    dmaPtr->lastFrame = audFrameCt;  /* mark it */

    osPiStartDma(&audDMAIOMesgBuf[nextDMA++], OS_MESG_PRI_HIGH, OS_READ,
                addr, foundBuffer, DMA_BUFFER_LENGTH, &audDMAMessageQ);

    return (int) osVirtualToPhysical(foundBuffer) + delta;
}

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
static ALDMAproc __amDmaNew(AMDMAState **state) {

    if(!dmaState.initialized) {  /* only do this once */
        dmaState.firstUsed = 0;
        dmaState.firstFree = &dmaBuffs[0];
        dmaState.initialized = 1;
    }

    *state = &dmaState;  /* state is never used in this case */

    return __amDMA;
}

/******************************************************************************
 *
 * __clearAudioDMA.  Routine to move dma buffers back to the unused list.
 * First clear out your dma messageQ. Then check each buffer to see when
 * it was last used. If that was more than FRAME_LAG frames ago, move it
 * back to the unused list. 
 *
 *****************************************************************************/
static void __clearAudioDMA(void) {
    u32          i;
    OSIoMesg     *iomsg = 0;
    AMDMABuffer  *dmaPtr,*nextPtr;
    
    /*
     * Don't block here. If dma's aren't complete, you've had an audio
     * overrun. (Bad news, but go for it anyway, and try and recover.
     */
    for (i = 0; i < nextDMA; i++) {
        if (osRecvMesg(&audDMAMessageQ, (OSMesg *) &iomsg, OS_MESG_NOBLOCK) == -1)
        { /* stubbed_printf("Dma not done\n"); */ }
        // if (logging)
        //     osLogEvent(log, 17, 2, iomsg->devAddr, iomsg->size);
    }

    
    dmaPtr = dmaState.firstUsed;
    while(dmaPtr) {
        nextPtr = (AMDMABuffer *) dmaPtr->node.next;

        /* remove old dma's from list */
        /* Can change FRAME_LAG value.  Should be at least one.  */
        /* Larger values mean more buffers needed, but fewer DMA's */
        if(dmaPtr->lastFrame + FRAME_LAG  < audFrameCt) {
            if(dmaState.firstUsed == dmaPtr) {
                dmaState.firstUsed = (AMDMABuffer *) dmaPtr->node.next;
            }
            alUnlink((ALLink *) dmaPtr);
            if(dmaState.firstFree) {
                alLink((ALLink *) dmaPtr, (ALLink *) dmaState.firstFree);
            }
            else {
                dmaState.firstFree = dmaPtr;
                dmaPtr->node.next = 0;
                dmaPtr->node.prev = 0;
            }
        }
        dmaPtr = nextPtr;
    }
    
    nextDMA = 0;  /* reset */
    audFrameCt++;
}

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
        alLink((ALLink *) (i + tmp1), (ALLink *) (i + tmp1 - 1));
    }

    gSoundChannelVolume = alHeapDBAlloc(0, 0, c->hp, 2, c->unk10);
    for (i = 0; i < c->unk10; i++) {
        gSoundChannelVolume[i] = 32767;
    }

    gAlSndPlayer->drvr = (ALSynth *) alGlobals;
    gAlSndPlayer->node.next = NULL;
    gAlSndPlayer->node.handler = &_sndpVoiceHandler;
    gAlSndPlayer->node.clientData = gAlSndPlayer;

    alSynAddPlayer(gAlSndPlayer->drvr, (ALPlayer *) gAlSndPlayer);
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

void func_8000410C(ALSoundState *state) {
    if (state->unk3E & 4) {
        alSynStopVoice(gAlSndPlayer->drvr, &state->voice);
        alSynFreeVoice(gAlSndPlayer->drvr, &state->voice);
    }
    func_80004520(state);
    _removeEvents(&gAlSndPlayer->evtq, state, 0xFFFF);
}

#if 0
void func_8000418C(void *arg0) {
    f32 sp28;
    void *sp24;
    s16 sp20;
    f32 sp1C;
    f32 temp_f6;

    temp_f6 = alCents2Ratio((s32) arg0->unk8->unk4->unk5) * arg0->unk2C;
    sp20 = 16;
    sp1C = temp_f6;
    sp24 = arg0;
    sp28 = sp1C;
    alEvtqPostEvent(&gAlSndPlayer->evtq, (ALEvent *) &sp20, 33333);
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_8000418C.s")
#endif

static void _removeEvents(ALEventQueue *evtq, ALSoundState *state, u16 eventType) {
    ALLink              *thisNode;
    ALLink              *nextNode;
    ALEventListItem     *thisItem;
    ALEventListItem     *nextItem;
    ALSndpEvent        *thisEvent;
    OSIntMask           mask;

    mask = osSetIntMask(OS_IM_NONE);

    thisNode = evtq->allocList.next;
    while( thisNode != 0 ) {
	nextNode = thisNode->next;
        thisItem = (ALEventListItem *)thisNode;
        nextItem = (ALEventListItem *)nextNode;
        thisEvent = (ALSndpEvent *) &thisItem->evt;
        if (thisEvent->common.state == state && (u16)thisEvent->msg.type & eventType){
            if( nextItem )
                nextItem->delta += thisItem->delta;
            alUnlink(thisNode);
            alLink(thisNode, &evtq->freeList);
        }
	thisNode = nextNode;
    }

    osSetIntMask(mask);
}

u16 func_800042CC(u16 *lastAllocListIndex, u16 *lastFreeListIndex) {
    OSIntMask mask;
    u16 freeListNextIndex;
    u16 allocListNextIndex;
    u16 freeListLastIndex;
    ALLink *nextAllocList;
    ALLink *nextFreeList;
    ALLink *prevFreeList;
    ALEventQueue *queue;

    mask = osSetIntMask(OS_IM_NONE);
    queue = (ALEventQueue *) &D_800DC6B0; //D_800DC6B0 could be a different type?
    nextFreeList = queue->freeList.next;
    nextAllocList = queue->allocList.next;
    prevFreeList = queue->freeList.prev;

    for (freeListNextIndex = 0; nextFreeList != 0; freeListNextIndex++) {
        nextFreeList = (ALLink *) nextFreeList->next;
    }

    for (allocListNextIndex = 0; nextAllocList != 0; allocListNextIndex++) {
        nextAllocList = (ALLink *) nextAllocList->next;
    }

    for (freeListLastIndex = 0; prevFreeList != 0; freeListLastIndex++) {
        prevFreeList = (ALLink *) prevFreeList->prev;
    }

    *lastAllocListIndex = allocListNextIndex;
    *lastFreeListIndex = freeListNextIndex;

    osSetIntMask(mask);

    return freeListLastIndex;
}

GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80004384.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80004520.s")

void func_80004604(u8 *arg0, u8 arg1) {
    if (arg0)
        arg0[0x36] = arg1;
}

UNUSED u8 func_8000461C(u8 *arg0) {
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

void func_800049F8(s32 soundMask, s16 type, u32 volume) {
    ALEvent2 sndEvt;
    sndEvt.snd_event.type = type;
    sndEvt.snd_event.state = (void *) soundMask;
    sndEvt.snd_event.unk04 = volume;
    if (soundMask) {
        alEvtqPostEvent(&(gAlSndPlayer->evtq), (ALEvent *) &sndEvt, 0);
    }
}

/**
 * Returns the volume level of the channel ID.
*/
u16 get_sound_channel_volume(u8 channel) {
    return gSoundChannelVolume[channel];
}

//TODO: The structs used here are almost definitely wrong, but they do match, so it can at least show the pattern we're looking for.
/**
 * Looks for the intended audio channel in the main buffer and adjusts its volume
*/
void set_sound_channel_volume(u8 channel, u16 volume) {
    OSIntMask mask;
    ALEventQueue *queue;
    UNUSED s32 pad;
    ALEvent evt;

    mask = osSetIntMask(OS_IM_NONE);
    queue = D_800DC6B0;
    gSoundChannelVolume[channel] = volume;

    while (queue != NULL) {
        //This is almost definitely the wrong struct list, but it matches so I'm not going to complain
        if ((((ALInstrument *) queue->allocList.next->prev)->priority & 0x3F) == channel) {
            evt.type = 0x800;
            evt.msg.spseq.seq = (void *) queue;
            alEvtqPostEvent(&gAlSndPlayer->evtq, &evt, 0);
        }
        queue = (ALEventQueue *) queue->freeList.next;
    }

    osSetIntMask(mask);
}
