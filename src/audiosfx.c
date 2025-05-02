#include "audiosfx.h"
#include "memory.h"
#include "audio_internal.h"
#include "video.h"
#include "math_util.h"
#include "asset_loading.h"
#include "objects.h"
#include "PR/libaudio.h"

ALUnkStruct D_800DC6B0 = { NULL, NULL, NULL };
unk800DC6BC gAlSndPlayer;
unk800DC6BC *gAlSndPlayerPtr = &gAlSndPlayer;
s32 sfxVolumeSlider = 256;
s16 D_800DC6C4 = 0;
u16 *gSoundChannelVolume;

/**** Debug strings ****/
const char D_800E4AB0[] = "Bad soundState: voices =%d, states free =%d, states busy =%d, type %d data %x\n";
const char D_800E4B00[] = "playing a playing sound\n";
const char D_800E4B1C[] = "Nonsense sndp event\n";
const char D_800E4B34[] = "Sound state allocate failed - sndId %d\n";
const char D_800E4B5C[] = "Don't worry - game should cope OK\n";
const char D_800E4B80[] = "WARNING: Attempt to stop NULL sound aborted\n";

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

/**
 * Initialise a sound player and ready it for use with the sound event system.
 * Official Name: gsSndpNew
 */
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
    gAlSndPlayerPtr->frameTime = 33000; // AL_USEC_PER_FRAME        /* time between API events */
    gAlSndPlayerPtr->unk40 = (unk800DC6BC_40 *) alHeapAlloc(c->hp, 1, c->unk00 * sizeof(unk800DC6BC_40));
    alEvtqNew(&(gAlSndPlayerPtr->evtq), alHeapAlloc(c->hp, 1, (c->unk04) * 28), c->unk04);
    D_800DC6B0.unk8 = (ALSoundState *) gAlSndPlayerPtr->unk40;
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

#pragma GLOBAL_ASM("asm/nonmatchings/audiosfx/_handleEvent.s")

void func_8000410C(ALSoundState *state) {
    if (state->flags & AL_SNDP_PAN_EVT) {
        alSynStopVoice(gAlSndPlayerPtr->drvr, &state->voice);
        alSynFreeVoice(gAlSndPlayerPtr->drvr, &state->voice);
    }
    func_80004520(state);
    _removeEvents(&gAlSndPlayerPtr->evtq, state, 0xFFFF);
}

//sndp_apply_detune_pitch in PD
void func_8000418C(ALVoiceState *voiceState) {
    ALEvent_unk8000418C evt;
    f32 pitch;

    pitch = alCents2Ratio(((ALLink_unk8000418C *) voiceState->voice.node.prev->prev)->unk5) * voiceState->vibrato;
    evt.type = AL_SNDP_PITCH_EVT;
    evt.unk4 = voiceState;
    evt.unk8 = *(u32 *)&pitch;
    alEvtqPostEvent(&gAlSndPlayerPtr->evtq, (ALEvent *) &evt, 33333);
}

static void _removeEvents(ALEventQueue *evtq, ALSoundState *state, u16 eventType) {
    ALLink *thisNode;
    ALLink *nextNode;
    ALEventListItem *thisItem;
    ALEventListItem *nextItem;
    ALSndpEvent *thisEvent;
    OSIntMask mask;

    mask = osSetIntMask(OS_IM_NONE);

    thisNode = evtq->allocList.next;
    while (thisNode != 0) {
        nextNode = thisNode->next;
        thisItem = (ALEventListItem *) thisNode;
        nextItem = (ALEventListItem *) nextNode;
        thisEvent = (ALSndpEvent *) &thisItem->evt;
        if (thisEvent->common.state == state && (u16) thisEvent->msg.type & eventType) {
            if (nextItem) {
                nextItem->delta += thisItem->delta;
            }
            alUnlink(thisNode);
            alLink(thisNode, &evtq->freeList);
        }
        thisNode = nextNode;
    }

    osSetIntMask(mask);
}

/**
 * Official Name: getSoundStateCounts
 */
u16 func_800042CC(u16 *lastAllocListIndex, u16 *lastFreeListIndex) {
    OSIntMask mask;
    u16 freeListNextIndex;
    u16 allocListNextIndex;
    u16 freeListLastIndex;
    ALSoundState *nextAllocList;
    ALSoundState *nextFreeList;
    ALSoundState *prevFreeList;
    ALSoundState *queue;

    mask = osSetIntMask(OS_IM_NONE);
    queue = (ALSoundState *) &D_800DC6B0;
    nextFreeList = queue->next;
    nextAllocList = queue->unk8;
    prevFreeList = queue->prev;

    for (freeListNextIndex = 0; nextFreeList != NULL; freeListNextIndex++) {
        nextFreeList = nextFreeList->next;
    }

    for (allocListNextIndex = 0; nextAllocList != NULL; allocListNextIndex++) {
        nextAllocList = nextAllocList->next;
    }

    for (freeListLastIndex = 0; prevFreeList != NULL; freeListLastIndex++) {
        prevFreeList = prevFreeList->prev;
    }

    *lastAllocListIndex = allocListNextIndex;
    *lastFreeListIndex = freeListNextIndex;

    osSetIntMask(mask);

    return freeListLastIndex;
}

// This function is full of names like next / prev that I made up based on other funcs.
// It's in no way guaranteed to be correct.
// I'm really not even sure what it's supposed to be returning as a type.
// sndp_alloc_state in PD
ALSound *func_80004384(UNUSED ALBank *arg0, ALSound *arg1) {
    s32 temp;
    ALKeyMap *temp_a2;
    unk80004384 *nextAllocList;
    u32 mask;
    s32 temp_a1;

    nextAllocList = (unk80004384 *) D_800DC6B0.unk8;
    temp_a2 = arg1->keyMap;
    if (nextAllocList != NULL) {
        mask = osSetIntMask(OS_IM_NONE);
        D_800DC6B0.unk8 = nextAllocList->next;
        alUnlink((ALLink *) nextAllocList);
        if (D_800DC6B0.next != NULL) {
            nextAllocList->next = D_800DC6B0.next;
            nextAllocList->prev = NULL;
            D_800DC6B0.next->prev = (ALSoundState *) nextAllocList;
            D_800DC6B0.next = (ALSoundState *) nextAllocList;
        } else {
            nextAllocList->prev = NULL;
            nextAllocList->next = NULL;
            D_800DC6B0.next = (ALSoundState *) nextAllocList;
            D_800DC6B0.prev = (ALSoundState *) nextAllocList;
        }
        osSetIntMask(mask);
        temp = ((arg1->envelope->decayTime + 1) == 0);
        temp_a1 = temp + 64;
        temp = 6000;
        nextAllocList->unk36 = temp_a1;
        nextAllocList->unk3F = 5;
        nextAllocList->unk38 = 2;
        nextAllocList->unk8 = (ALSoundState *) arg1;
        nextAllocList->unk2C = 1.0f;
        nextAllocList->unk3E = temp_a2->keyMax & 0xF0;
        nextAllocList->unk30 = 0;
        if (nextAllocList->unk3E & 0x20) {
            nextAllocList->unk28 = alCents2Ratio((temp_a2->keyBase * 100) - temp);
        } else {
            nextAllocList->unk28 = alCents2Ratio(((temp_a2->keyBase * 100) + temp_a2->detune) - temp);
        }
        if (temp_a1 != 64) {
            nextAllocList->unk3E |= 2; //SNDSTATEFLAG_NO_DECAY
        }
        nextAllocList->unk3D = 0;
        nextAllocList->unk3C = AL_PAN_CENTER;
        nextAllocList->unk34 = 0x7FFF; //AL_VOL_FULL;
    }
    return (ALSound *) nextAllocList;
}

// sndp_free_state2 in PD
void func_80004520(ALSoundState *soundState) {
    if (soundState == D_800DC6B0.next) {
        D_800DC6B0.next = soundState->next;
    }
    if (soundState == D_800DC6B0.prev) {
        D_800DC6B0.prev = soundState->prev;
    }
    alUnlink((ALLink *) soundState);
    if (D_800DC6B0.unk8 != NULL) {
        soundState->next = D_800DC6B0.unk8;
        soundState->prev = NULL;
        D_800DC6B0.unk8->prev = soundState;
        D_800DC6B0.unk8 = soundState;
    } else {
        soundState->prev = NULL;
        soundState->next = NULL;
        D_800DC6B0.unk8 = soundState;
    }
    if (soundState->flags & AL_SNDP_PAN_EVT) {
        D_800DC6C4--;
    }
    soundState->soundState = 0;
    if (soundState->unk30 != NULL) {
        if (soundState == soundState->unk30->next) {
            soundState->unk30->next = NULL;
        }
        soundState->unk30 = NULL;
    }
}

/**
 * Official Name: gsSndpSetPriority
 */
void func_80004604(ALSoundState *sndp, u8 priority) {
    if (sndp != NULL) {
        sndp->soundPriority = priority;
    }
}

/**
 * Official Name: gsSndpGetState
 */
UNUSED u8 func_8000461C(ALSoundState *sndp) {
    if (sndp != NULL) {
        return sndp->soundState;
    } else {
        return 0;
    }
}

s32 func_80004638(ALBank *bnk, s16 sndIndx, SoundMask *soundMask) {
    return func_80004668(bnk, sndIndx, 0, soundMask);
}

#ifdef NON_EQUIVALENT
s32 func_80004668(ALBank *bnk, s16 sndIndx, u8 arg2, SoundMask *soundMask) {
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/audiosfx/func_80004668.s")
#endif

/**
 * input typing not right (some type of struct)
 * 99% sure this function will clear the audio buffer associated with a given sound mask.
 * Official Name: gsSndpStop
 */
void sound_stop(ALSoundState *sndp) {
    ALEvent alEvent;

    alEvent.type = AL_SNDP_UNK_10_EVT;
    alEvent.msg.sndpevent.soundState = sndp;
    if (sndp != NULL) {
        sndp->flags &= ~AL_SNDP_PITCH_EVT;
        alEvtqPostEvent(&gAlSndPlayerPtr->evtq, &alEvent, 0);
    } else {
        // From JFG
        // osSyncPrintf("WARNING: Attempt to stop NULL sound aborted\n");
    }
}

void func_800048D8(u8 event) {
    OSIntMask mask;
    ALEvent evt;
    ALSoundState *queue;

    mask = osSetIntMask(OS_IM_NONE);
    queue = D_800DC6B0.next;
    while (queue != NULL) {
        evt.type = AL_SNDP_UNK_10_EVT;
        evt.msg.sndpevent.soundState = queue;
        if ((queue->flags & event) == event) {
            evt.msg.sndpevent.soundState->flags &= ~AL_SNDP_PITCH_EVT;
            alEvtqPostEvent(&gAlSndPlayerPtr->evtq, &evt, 0);
        }
        queue = queue->next;
    }
    osSetIntMask(mask);
}

/**
 * Official Name: gsSndpStopAll
 */
UNUSED void func_80004998(void) {
    func_800048D8(AL_SNDP_PLAY_EVT);
}

/**
 * Official Name: gsSndpStopAllRetrigger
 */
UNUSED void func_800049B8(void) {
    func_800048D8(AL_SNDP_PLAY_EVT | AL_SNDP_PITCH_EVT);
}

/**
 * Stops all sounds from playing.
 * Official Name: gsSndpStopAllLooped
 */
void sound_stop_all(void) {
    func_800048D8(AL_SNDP_PLAY_EVT | AL_SNDP_STOP_EVT);
}

/**
 * Send a message to the sound player to update an existing property of the sound entry.
 * Official Name: gsSndpSetParam
 */
void sound_event_update(s32 soundMask, s16 type, u32 volume) {
    ALEvent2 sndEvt;
    sndEvt.snd_event.type = type;
    sndEvt.snd_event.state = (void *) soundMask;
    sndEvt.snd_event.param = volume;
    if (soundMask != NULL) {
        alEvtqPostEvent(&gAlSndPlayerPtr->evtq, (ALEvent *) &sndEvt, 0);
    } else {
        // From JFG
        // osSyncPrintf("WARNING: Attempt to modify NULL sound aborted\n");
    }
}

/**
 * Returns the volume level of the channel ID.
 * Official Name: gsSndpGetMasterVolume
 */
u16 get_sound_channel_volume(u8 channel) {
    return gSoundChannelVolume[channel];
}

// TODO: The structs used here are almost definitely wrong, but they do match, so it can at least show the pattern we're
// looking for.
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
    queue = (ALEventQueue *) D_800DC6B0.next;
    gSoundChannelVolume[channel] = volume;

    while (queue != NULL) {
        // This is almost definitely the wrong struct list, but it matches so I'm not going to complain
        if ((((ALInstrument *) queue->allocList.next->prev)->priority & 0x3F) == channel) {
            evt.type = AL_SNDP_UNK_11_EVT;
            evt.msg.spseq.seq = (void *) queue;
            alEvtqPostEvent(&gAlSndPlayerPtr->evtq, &evt, 0);
        }
        queue = (ALEventQueue *) queue->freeList.next;
    }

    osSetIntMask(mask);
}
