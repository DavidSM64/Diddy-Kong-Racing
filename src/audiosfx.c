/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80003160 */

#include "audiosfx.h"
#include "memory.h"
#include "audio_internal.h"
#include "video.h"
#include "math_util.h"
#include "asset_loading.h"
#include "objects.h"
#include "PR/libaudio.h"

ALEventQueue *D_800DC6B0 = NULL;
s32 D_800DC6B4 = 0; // Currently unknown, might be a different type.
unk800DC6BC_40 *D_800DC6B8 = NULL; // Set but not used.
unk800DC6BC gAlSndPlayer;
unk800DC6BC *gAlSndPlayerPtr = &gAlSndPlayer;
s32 sfxVolumeSlider = 256;
s32 D_800DC6C4 = 0; // Currently unknown, might be a different type.
u16 *gSoundChannelVolume;

static void _removeEvents(ALEventQueue *, ALSoundState *, u16);

void set_sfx_volume_slider(u32 volume) {
    if (volume > 256) {
        volume = 256;
    }

    sfxVolumeSlider = volume;
}

s32 get_sfx_volume_slider(void) {
    return sfxVolumeSlider;
}

/**
 * Sets the number of active sound channels to either the passed number, or the maximum amount, whichever's lower.
 */
void set_sound_channel_count(s32 numChannels) {
    if (gAlSndPlayerPtr->soundChannelsMax >= numChannels) {
        gAlSndPlayerPtr->soundChannels = numChannels;
    } else {
        gAlSndPlayerPtr->soundChannels = gAlSndPlayerPtr->soundChannelsMax;
    }
}

void alSndPNew(audioMgrConfig *c) {
    u32 i;
    unk800DC6BC_40 *tmp1;
    ALEvent evt;

    /*
     * Init member variables
     */
    gAlSndPlayerPtr->soundChannelsMax = c->maxChannels;
    gAlSndPlayerPtr->soundChannels = c->maxChannels;
    gAlSndPlayerPtr->unk3C = 0;
    gAlSndPlayerPtr->frameTime = 33000; //AL_USEC_PER_FRAME        /* time between API events */
    gAlSndPlayerPtr->unk40 = (unk800DC6BC_40 *) alHeapAlloc(c->hp, 1,
                                                         c->unk00 * sizeof(unk800DC6BC_40));
    alEvtqNew(&(gAlSndPlayerPtr->evtq), alHeapAlloc(c->hp, 1, (c->unk04) * 28), c->unk04);
    D_800DC6B8 = gAlSndPlayerPtr->unk40;
    for (i = 1; i < c->unk00; i++) {
        tmp1 = gAlSndPlayerPtr->unk40;
        alLink((ALLink *) (i + tmp1), (ALLink *) (i + tmp1 - 1));
    }

    /*
     * init the event queue
     */
    gSoundChannelVolume = alHeapAlloc(c->hp, 2, c->unk10);
    for (i = 0; i < c->unk10; i++) {
        gSoundChannelVolume[i] = 32767;
    }

    /*
     * add ourselves to the driver
     */
    gAlSndPlayerPtr->drvr = (ALSynth *) alGlobals;
    gAlSndPlayerPtr->node.next = NULL;
    gAlSndPlayerPtr->node.handler = _sndpVoiceHandler;
    gAlSndPlayerPtr->node.clientData = gAlSndPlayerPtr;
    alSynAddPlayer(gAlSndPlayerPtr->drvr, (ALPlayer *) gAlSndPlayerPtr);

    /*
     * Start responding to API events
     */
    evt.type = AL_SNDP_API_EVT;
    alEvtqPostEvent(&gAlSndPlayerPtr->evtq, (ALEvent *) &evt, gAlSndPlayerPtr->frameTime);
    gAlSndPlayerPtr->nextDelta = alEvtqNextEvent(&gAlSndPlayerPtr->evtq, &gAlSndPlayerPtr->nextEvent);
}

ALMicroTime _sndpVoiceHandler(void *node) {
    unk800DC6BC *sndp = (unk800DC6BC *) node;
    ALSndpEvent evt;
    u32 eventType = AL_SNDP_API_EVT;

    do {
        switch (sndp->nextEvent.type) {
            case (AL_SNDP_API_EVT):
                evt.common.type = eventType;
                alEvtqPostEvent(&sndp->evtq, (ALEvent *) &evt, sndp->frameTime);
                break;

            default:
                _handleEvent(sndp, (ALSndpEvent *) &sndp->nextEvent);
                break;
        }
        sndp->nextDelta = alEvtqNextEvent(&sndp->evtq, &sndp->nextEvent);

    } while (sndp->nextDelta == 0);
    sndp->curTime += sndp->nextDelta;
    return sndp->nextDelta;
}

GLOBAL_ASM("asm/non_matchings/audiosfx/_handleEvent.s")

void func_8000410C(ALSoundState *state) {
    if (state->unk3E & 4) {
        alSynStopVoice(gAlSndPlayerPtr->drvr, &state->voice);
        alSynFreeVoice(gAlSndPlayerPtr->drvr, &state->voice);
    }
    func_80004520(state);
    _removeEvents(&gAlSndPlayerPtr->evtq, state, 0xFFFF);
}

#ifdef NON_EQUIVALENT
void func_8000418C(ALVoiceState *voiceState) {
    ALSndpEvent evt;
    UNUSED ALSound *sound;

    evt.pitch.pitch = alCents2Ratio(((ALSound *)voiceState->voice.node.prev)->keyMap->detune) * voiceState->vibrato;
    evt.pitch.type = AL_SEQP_STOP_EVT;
    evt.pitch.state = voiceState;
    alEvtqPostEvent(&gAlSndPlayerPtr->evtq, &evt.msg, 33333);
}
#else
GLOBAL_ASM("asm/non_matchings/audiosfx/func_8000418C.s")
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

GLOBAL_ASM("asm/non_matchings/audiosfx/func_80004384.s")
GLOBAL_ASM("asm/non_matchings/audiosfx/func_80004520.s")

void func_80004604(u8 *arg0, u8 arg1) {
    if (arg0)
        arg0[0x36] = arg1;
}

UNUSED u8 func_8000461C(u8 *arg0) {
    if (arg0)
        return arg0[0x3F];
    return 0;
}

s32 func_80004638(ALBank *bnk, s16 sndIndx, s32 arg2) {
    return func_80004668(bnk, sndIndx, 0, arg2);
}

#ifdef NON_EQUIVALENT
s32 func_80004668(ALBank *bnk, s16 sndIndx, u8 arg2, s32 arg3) {
}
#else
GLOBAL_ASM("asm/non_matchings/audiosfx/func_80004668.s")
#endif

//input typing not right (some type of struct)
// 99% sure this function will clear the audio buffer associated with a given sound mask.
void func_8000488C(u8 *arg0) {
    ALEvent sp_18;
    sp_18.type = 1024;
    //((u32 *)(&sp_18))[1] = (u32)arg0;
    sp_18.msg.osc.vs = (ALVoiceState *) arg0; //Not really a voice state, but not sure what else it is.
    if (arg0) {
        arg0[0x3e] &= ~(1 << 4);
        alEvtqPostEvent(&(gAlSndPlayerPtr->evtq), &sp_18, 0);
    }
}

GLOBAL_ASM("asm/non_matchings/audiosfx/func_800048D8.s")

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
        alEvtqPostEvent(&(gAlSndPlayerPtr->evtq), (ALEvent *) &sndEvt, 0);
    }
}

/**
 * Returns the volume level of the channel ID.
 * Official Name: gsSndpGetMasterVolume
*/
u16 get_sound_channel_volume(u8 channel) {
    return gSoundChannelVolume[channel];
}

//TODO: The structs used here are almost definitely wrong, but they do match, so it can at least show the pattern we're looking for.
/**
 * Looks for the intended audio channel in the main buffer and adjusts its volume
 * Official Name: gsSndpSetMasterVolume
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
            evt.type = AL_SNDP_UNK_11_EVT;
            evt.msg.spseq.seq = (void *) queue;
            alEvtqPostEvent(&gAlSndPlayerPtr->evtq, &evt, 0);
        }
        queue = (ALEventQueue *) queue->freeList.next;
    }

    osSetIntMask(mask);
}
