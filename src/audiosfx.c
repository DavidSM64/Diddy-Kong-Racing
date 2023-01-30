/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80003160 */

#include "audiosfx.h"
#include "memory.h"
#include "audio_internal.h"
#include "video.h"
#include "math_util.h"
#include "asset_loading.h"
#include "objects.h"

/************ .bss ************/
 

ALEventQueue *D_800DC6B0 = NULL;
s32 D_800DC6B4 = 0; // Currently unknown, might be a different type.
unk800DC6BC_40 *D_800DC6B8 = NULL;
extern unk800DC6BC D_80119BD0;
unk800DC6BC *gAlSndPlayer = &D_80119BD0;
s32 sfxVolumeSlider = 256;
s32 D_800DC6C4 = 0; // Currently unknown, might be a different type.
unk800DC6BC D_80119BD0;
u16 *gSoundChannelVolume;

static void _removeEvents(ALEventQueue *, ALSoundState *, u16);

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
