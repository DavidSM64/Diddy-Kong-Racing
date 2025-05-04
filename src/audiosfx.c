#include "audiosfx.h"
#include "memory.h"
#include "video.h"
#include "math_util.h"
#include "asset_loading.h"
#include "objects.h"
#include "PR/libaudio.h"

#define SOUND_PARAM_DURATION(m) (m->velocityMax * 33333)
#define SOUND_PARAM_NEXT_SOUND(m) (m->velocityMin + (m->keyMin & 0xC0) * 4);

ALSoundStateLists gSoundStateLists = { NULL, NULL, NULL };
SoundPlayer gSoundPlayer;
SoundPlayer *gSoundPlayerPtr = &gSoundPlayer;
s32 gSoundMasterVolume = 256;
s16 D_800DC6C4 = 0;
s16 *gSoundChannelVolume;

/**** Debug strings ****/
const char D_800E4AB0[] = "Bad soundState: voices =%d, states free =%d, states busy =%d, type %d data %x\n";
const char D_800E4B00[] = "playing a playing sound\n";
const char D_800E4B1C[] = "Nonsense sndp event\n";
const char D_800E4B34[] = "Sound state allocate failed - sndId %d\n";
const char D_800E4B5C[] = "Don't worry - game should cope OK\n";
const char D_800E4B80[] = "WARNING: Attempt to stop NULL sound aborted\n";

static void sndp_remove_events(ALEventQueue *, ALSoundState *, u16);
void func_80065A80(ALSynth *arg0, struct PVoice_s *arg1, s16 arg2);

void sndp_set_master_volume(u32 volume) {
    if (volume > 256) {
        volume = 256;
    }

    gSoundMasterVolume = volume;
}

s32 sndp_get_master_volume(void) {
    return gSoundMasterVolume;
}

/**
 * Sets the number of active sound channels to either the passed number, or the maximum amount, whichever's lower.
 */
void sndp_set_channel_count(s32 numChannels) {
    if (gSoundPlayerPtr->soundChannelsMax >= numChannels) {
        gSoundPlayerPtr->soundChannels = numChannels;
    } else {
        gSoundPlayerPtr->soundChannels = gSoundPlayerPtr->soundChannelsMax;
    }
}

/**
 * Initialise a sound player and ready it for use with the sound event system.
 * Official Name: gsSndpNew
 */
void sndp_init_player(audioMgrConfig *c) {
    u32 i;
    ALSoundState *sounds;
    ALEvent evt;
    ALEventListItem *items;

    /*
     * Init member variables
     */
    gSoundPlayerPtr->soundChannelsMax = c->maxChannels;
    gSoundPlayerPtr->soundChannels = c->maxChannels;
    gSoundPlayerPtr->lastSoundState = NULL;
    gSoundPlayerPtr->frameTime = 33000; // AL_USEC_PER_FRAME        /* time between API events */
    gSoundPlayerPtr->soundStatesArray = (ALSoundState *) alHeapAlloc(c->heap, 1, c->maxSounds * sizeof(ALSoundState));

    /*
     * init the event queue
     */
    items = (ALEventListItem *) alHeapAlloc(c->heap, 1, c->maxEvents * sizeof(ALEventListItem));
    alEvtqNew(&gSoundPlayerPtr->evtq, items, c->maxEvents);

    gSoundStateLists.freeHead = (ALSoundState *) gSoundPlayerPtr->soundStatesArray;
    for (i = 1; i < c->maxSounds; i++) {
        sounds = gSoundPlayerPtr->soundStatesArray;
        alLink(&(sounds + i)->next, &(sounds + i - 1)->next);
    }

    gSoundChannelVolume = alHeapAlloc(c->heap, 2, c->unk10);
    for (i = 0; i < c->unk10; i++) {
        gSoundChannelVolume[i] = 32767;
    }

    /*
     * add ourselves to the driver
     */
    gSoundPlayerPtr->drvr = &alGlobals->drvr;
    gSoundPlayerPtr->node.next = NULL;
    gSoundPlayerPtr->node.handler = sndp_voice_handler;
    gSoundPlayerPtr->node.clientData = gSoundPlayerPtr;
    alSynAddPlayer(gSoundPlayerPtr->drvr, &gSoundPlayerPtr->node);

    /*
     * Start responding to API events
     */
    evt.type = AL_SNDP_API_EVT;
    alEvtqPostEvent(&gSoundPlayerPtr->evtq, (ALEvent *) &evt, gSoundPlayerPtr->frameTime);
    gSoundPlayerPtr->nextDelta = alEvtqNextEvent(&gSoundPlayerPtr->evtq, &gSoundPlayerPtr->nextEvent);
}

ALMicroTime sndp_voice_handler(void *node) {
    SoundPlayer *sndp = (SoundPlayer *) node;
    ALSndpEvent evt;
    u32 eventType = AL_SNDP_API_EVT;

    do {
        switch (sndp->nextEvent.type) {
            case (AL_SNDP_API_EVT):
                evt.common.type = eventType;
                alEvtqPostEvent(&sndp->evtq, (ALEvent *) &evt, sndp->frameTime);
                break;

            default:
                sndp_handle_event(sndp, (ALSndpEvent *) &sndp->nextEvent);
                break;
        }
        sndp->nextDelta = alEvtqNextEvent(&sndp->evtq, &sndp->nextEvent);

    } while (sndp->nextDelta == 0);
    sndp->curTime += sndp->nextDelta;
    return sndp->nextDelta;
}

void sndp_handle_event(SoundPlayer *sndp, ALSndpEvent *event) {
    ALVoiceConfig config;
    ALVoice *voice;
    s32 delta;
    s32 fullQueue;
    ALSndpEvent spAC;
    ALSndpEvent sp9C;
    ALSound *sound;
    ALKeyMap *keyMap;
    s32 volume;
    s32 fxMix;
    s32 isEventForSingleSound;
    ALPan pan;
    s32 lastInSequence;
    s32 isVoiceAllocated;
    ALSoundState *soundState;
    ALSoundState *nextState;

    lastInSequence = TRUE;
    isVoiceAllocated = FALSE;
    soundState = NULL;
    nextState = NULL;

    do {
        if (nextState != NULL) {
            sp9C.common.state = soundState;
            sp9C.common.type = event->common.type;
            sp9C.common.param = event->common.param;
            event = &sp9C;
        }

        soundState = event->common.state;
        sound = soundState->sound;

        if (sound == NULL) {
            u16 n2, n3;
            sndp_get_state_counts(&n2, &n3);
            return;
        }

        keyMap = sound->keyMap;
        nextState = soundState->next;

        switch (event->common.type) {
            case AL_SNDP_PLAY_EVT:
                if (soundState->state != SOUND_STATE_5 && soundState->state != SOUND_STATE_4) {
                    return;
                }

                config.fxBus = 0;
                config.priority = soundState->priority;
                config.unityPitch = 0;

                fullQueue = sndp->soundChannels <= D_800DC6C4;

                if (!fullQueue || (soundState->flags & SOUND_FLAG_LOOPING)) {
                    isVoiceAllocated = alSynAllocVoice(sndp->drvr, &soundState->voice, &config);
                }
                if (isVoiceAllocated) {
                    func_80065A80(sndp->drvr, soundState->voice.pvoice, 1);
                }

                voice = &soundState->voice;
                if (!isVoiceAllocated) {
                    if ((soundState->flags & (SOUND_FLAG_LOOPING | SOUND_FLAG_PERSISTENT)) || soundState->retries > 0) {
                        soundState->state = SOUND_STATE_4;
                        soundState->retries--;
                        alEvtqPostEvent(&sndp->evtq, (ALEvent *) event, 33333);
                    } else if (fullQueue) {
                        ALSoundState *iterState = gSoundStateLists.allocTail;

                        do {
                            if (iterState->priority <= soundState->priority &&
                                iterState->state != SOUND_STATE_PREEMPT) {
                                // Found a lower-priority sound; it can be preempted
                                ALSndpEvent interruptEvent;

                                interruptEvent.common.type = AL_SNDP_END_EVT;
                                interruptEvent.common.state = iterState;
                                iterState->state = SOUND_STATE_PREEMPT;
                                fullQueue = FALSE;
                                alEvtqPostEvent(&sndp->evtq, (ALEvent *) &interruptEvent, 1000);
                                alSynSetVol(sndp->drvr, &iterState->voice, (soundState->state == 1) * 0, 1000); // FAKE
                            }
                            iterState = iterState->prev;
                        } while (fullQueue && iterState != NULL);

                        if (!fullQueue) {
                            soundState->retries = 2;
                            alEvtqPostEvent(&sndp->evtq, (ALEvent *) event, 1001);
                        } else {
                            sndp_end(soundState);
                        }
                    } else {
                        sndp_end(soundState);
                    }
                    return;
                }

                soundState->flags |= SOUND_FLAG_PLAYING;
                alSynStartVoice(sndp->drvr, voice, sound->wavetable);
                soundState->state = SOUND_STATE_PLAYING;
                D_800DC6C4++;

                delta = sound->envelope->attackTime / soundState->pitch / soundState->unk28;
                volume =
                    MAX(0, gSoundChannelVolume[keyMap->keyMin & 0x3F] *
                                   (sound->envelope->attackVolume * soundState->volume * sound->sampleVolume / 16129) /
                                   32767 -
                               1);
                volume = (u32) (volume * gSoundMasterVolume) >> 8;
                alSynSetVol(sndp->drvr, &soundState->voice, 0, 0);
                alSynSetVol(sndp->drvr, &soundState->voice, volume, delta);

                pan = MIN(MAX((soundState->pan + sound->samplePan - AL_PAN_CENTER), AL_PAN_LEFT), AL_PAN_RIGHT);
                alSynSetPan(sndp->drvr, &soundState->voice, pan);

                alSynSetPitch(sndp->drvr, &soundState->voice, soundState->pitch * soundState->unk28);

                fxMix = (soundState->fxmix + (keyMap->keyMax & 0xF)) * 8;
                fxMix = MIN(127, MAX(0, fxMix));
                alSynSetFXMix(sndp->drvr, &soundState->voice, fxMix);

                spAC.common.type = AL_SNDP_DECAY_EVT;
                spAC.common.state = soundState;
                alEvtqPostEvent(&sndp->evtq, (ALEvent *) &spAC,
                                sound->envelope->attackTime / soundState->pitch / soundState->unk28);
                break;
            case AL_SNDP_RELEASE_EVT:
            case AL_SNDP_STOP_EVT:
            case AL_SNDP_UNK_12_EVT:
                if (!(event->common.type == AL_SNDP_UNK_12_EVT && !(soundState->flags & SOUND_FLAG_PERSISTENT))) {
                    switch (soundState->state) {
                        case SOUND_STATE_PLAYING:
                            sndp_remove_events(&sndp->evtq, soundState, AL_SNDP_DECAY_EVT);
                            delta = sound->envelope->releaseTime / soundState->unk28 / soundState->pitch;
                            alSynSetVol(sndp->drvr, &soundState->voice, 0, delta);
                            if (delta != 0) {
                                spAC.common.type = AL_SNDP_END_EVT;
                                spAC.common.state = soundState;
                                alEvtqPostEvent(&sndp->evtq, (ALEvent *) &spAC, delta);
                                soundState->state = SOUND_STATE_STOPPING;
                            } else {
                                sndp_end(soundState);
                            }
                            break;
                        case SOUND_STATE_4:
                        case SOUND_STATE_5:
                            sndp_end(soundState);
                            break;
                    }
                    if (event->common.type == AL_SNDP_RELEASE_EVT) {
                        event->common.type = AL_SNDP_UNK_12_EVT;
                    }
                }
                break;
            case AL_SNDP_PAN_EVT:
                soundState->pan = event->common.param;
                if (soundState->state == SOUND_STATE_PLAYING) {
                    pan = MIN(MAX((soundState->pan + sound->samplePan - AL_PAN_CENTER), AL_PAN_LEFT), AL_PAN_RIGHT);
                    alSynSetPan(sndp->drvr, &soundState->voice, pan);
                }
                break;
            case AL_SNDP_PITCH_EVT:
                soundState->pitch = *(f32 *) &event->common.param;
                if (soundState->state == SOUND_STATE_PLAYING) {
                    alSynSetPitch(sndp->drvr, &soundState->voice, soundState->pitch * soundState->unk28);
                    if (soundState->flags & SOUND_FLAG_PITCH_SLIDE) {
                        func_8000418C(soundState);
                    }
                }
                break;
            case AL_SNDP_FX_EVT:
                soundState->fxmix = event->common.param;
                if (soundState->state == SOUND_STATE_PLAYING) {
                    fxMix = (soundState->fxmix + (keyMap->keyMax & 0xF)) * 8;
                    fxMix = MIN(127, MAX(0, fxMix));
                    alSynSetFXMix(sndp->drvr, &soundState->voice, fxMix);
                }
                break;
            case AL_SNDP_VOL_EVT:
                soundState->volume = event->common.param;
                if (soundState->state == SOUND_STATE_PLAYING) {
                    volume = MAX(
                        0, gSoundChannelVolume[keyMap->keyMin & 0x3F] *
                                   (sound->envelope->decayVolume * soundState->volume * sound->sampleVolume / 16129) /
                                   32767 -
                               1);
                    volume = (u32) (volume * gSoundMasterVolume) >> 8;
                    alSynSetVol(sndp->drvr, &soundState->voice, volume, 1000);
                }
                break;
            case AL_SNDP_UNK_11_EVT:
                if (soundState->state == SOUND_STATE_PLAYING) {
                    delta = sound->envelope->releaseTime / soundState->unk28 / soundState->pitch;
                    volume = MAX(
                        0, gSoundChannelVolume[keyMap->keyMin & 0x3F] *
                                   (sound->envelope->decayVolume * soundState->volume * sound->sampleVolume / 16129) /
                                   32767 -
                               1);
                    volume = (u32) (volume * gSoundMasterVolume) >> 8;
                    alSynSetVol(sndp->drvr, &soundState->voice, volume, delta);
                }
                break;
            case AL_SNDP_DECAY_EVT:
                if (!(soundState->flags & SOUND_FLAG_PERSISTENT)) {
                    volume = MAX(
                        0, gSoundChannelVolume[keyMap->keyMin & 0x3F] *
                                   (sound->envelope->decayVolume * soundState->volume * sound->sampleVolume / 16129) /
                                   32767 -
                               1);
                    volume = (u32) (volume * gSoundMasterVolume) >> 8;
                    delta = sound->envelope->decayTime / soundState->unk28 / soundState->pitch;
                    alSynSetVol(sndp->drvr, &soundState->voice, volume, delta);

                    spAC.common.type = AL_SNDP_RELEASE_EVT;
                    spAC.common.state = soundState;
                    alEvtqPostEvent(&sndp->evtq, (ALEvent *) &spAC, delta);

                    if (soundState->flags & SOUND_FLAG_PITCH_SLIDE) {
                        func_8000418C(soundState);
                    }
                }
                break;
            case AL_SNDP_END_EVT:
                sndp_end(soundState);
                break;
            case AL_SNDP_LOOP_RESTART_EVT:
                if (soundState->flags & SOUND_FLAG_LOOPING) {
                    ALSoundState *newSound =
                        sndp_play(event->loopRestart.bank, event->loopRestart.soundIndex, soundState->userHandle);
                    if (newSound != NULL) {
                        sndp_set_param(newSound, AL_SNDP_VOL_EVT, soundState->volume);
                        if ((!event) && (!event)) {} // Fake
                        sndp_set_param(newSound, AL_SNDP_PAN_EVT, soundState->pan);
                        sndp_set_param(newSound, AL_SNDP_FX_EVT, soundState->fxmix);
                        sndp_set_param(newSound, AL_SNDP_PITCH_EVT, *(s32 *) &soundState->pitch);
                    }
                }
                break;
            default:
                break;
        }

        soundState = nextState;
        isEventForSingleSound = event->common.type & (AL_SNDP_PLAY_EVT | AL_SNDP_PITCH_EVT | AL_SNDP_DECAY_EVT |
                                                      AL_SNDP_END_EVT | AL_SNDP_LOOP_RESTART_EVT);

        if (soundState != NULL && !isEventForSingleSound) {
            lastInSequence = soundState->flags & SOUND_FLAG_FINAL_IN_SEQUENCE;
        }

    } while (!lastInSequence && soundState != NULL && !isEventForSingleSound);
}

void sndp_end(ALSoundState *state) {
    if (state->flags & SOUND_FLAG_PLAYING) {
        alSynStopVoice(gSoundPlayerPtr->drvr, &state->voice);
        alSynFreeVoice(gSoundPlayerPtr->drvr, &state->voice);
    }
    sndp_deallocate(state);
    sndp_remove_events(&gSoundPlayerPtr->evtq, state, 0xFFFF);
}

void func_8000418C(ALSoundState *soundState) {
    ALSndpEvent evt;
    f32 pitch;

    pitch = alCents2Ratio(soundState->sound->keyMap->detune) * soundState->pitch;
    evt.common.type = AL_SNDP_PITCH_EVT;
    evt.common.state = soundState;
    evt.common.param = *((s32 *) &pitch);
    alEvtqPostEvent(&gSoundPlayerPtr->evtq, (ALEvent *) &evt, 33333);
}

static void sndp_remove_events(ALEventQueue *evtq, ALSoundState *state, u16 eventType) {
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
        if (thisEvent->common.state == state && thisEvent->common.type & eventType) {
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
u16 sndp_get_state_counts(u16 *lastAllocListIndex, u16 *lastFreeListIndex) {
    OSIntMask mask;
    u16 numUsed;
    u16 numFree;
    u16 freeListLastIndex;
    ALSoundState *freePtr;
    ALSoundState *usedPtr;
    ALSoundState *usedRevPtr;

    mask = osSetIntMask(OS_IM_NONE);
    usedPtr = gSoundStateLists.allocHead;
    freePtr = gSoundStateLists.freeHead;
    usedRevPtr = gSoundStateLists.allocTail;

    for (numUsed = 0; usedPtr != NULL; numUsed++) {
        usedPtr = usedPtr->next;
    }

    for (numFree = 0; freePtr != NULL; numFree++) {
        freePtr = freePtr->next;
    }

    for (freeListLastIndex = 0; usedRevPtr != NULL; freeListLastIndex++) {
        usedRevPtr = usedRevPtr->prev;
    }

    *lastAllocListIndex = numFree;
    *lastFreeListIndex = numUsed;

    osSetIntMask(mask);

    return freeListLastIndex;
}

ALSoundState *sndp_allocate(UNUSED ALBank *bank, ALSound *sound) {
    s32 temp;
    ALKeyMap *keyMap;
    ALSoundState *state;
    u32 mask;
    s32 temp_a1;

    state = gSoundStateLists.freeHead;
    keyMap = sound->keyMap;
    if (state != NULL) {
        mask = osSetIntMask(OS_IM_NONE);
        gSoundStateLists.freeHead = state->next;
        alUnlink((ALLink *) state);
        if (gSoundStateLists.allocHead != NULL) {
            state->next = gSoundStateLists.allocHead;
            state->prev = NULL;
            gSoundStateLists.allocHead->prev = state;
            gSoundStateLists.allocHead = state;
        } else {
            state->prev = NULL;
            state->next = NULL;
            gSoundStateLists.allocHead = state;
            gSoundStateLists.allocTail = state;
        }
        osSetIntMask(mask);

        temp = sound->envelope->decayTime == -1;
        temp_a1 = temp + 64;
        temp = 6000;
        state->priority = temp_a1;
        state->state = SOUND_STATE_5;
        state->retries = 2;
        state->sound = sound;
        state->pitch = 1.0f;
        state->flags = keyMap->keyMax & 0xF0;
        state->userHandle = NULL;
        if (state->flags & SOUND_FLAG_PITCH_SLIDE) {
            state->unk28 = alCents2Ratio(keyMap->keyBase * 100 - 6000);
        } else {
            state->unk28 = alCents2Ratio(keyMap->keyBase * 100 + keyMap->detune - 6000);
        }
        if (temp_a1 != 64) {
            state->flags |= SOUND_FLAG_PERSISTENT;
        }
        state->fxmix = 0;
        state->pan = AL_PAN_CENTER;
        state->volume = 0x7FFF;
    }
    return state;
}

void sndp_deallocate(ALSoundState *state) {
    if (state == gSoundStateLists.allocHead) {
        gSoundStateLists.allocHead = state->next;
    }
    if (state == gSoundStateLists.allocTail) {
        gSoundStateLists.allocTail = state->prev;
    }
    alUnlink((ALLink *) state);
    if (gSoundStateLists.freeHead != NULL) {
        state->next = gSoundStateLists.freeHead;
        state->prev = NULL;
        gSoundStateLists.freeHead->prev = state;
        gSoundStateLists.freeHead = state;
    } else {
        state->prev = NULL;
        state->next = NULL;
        gSoundStateLists.freeHead = state;
    }
    if (state->flags & SOUND_FLAG_PLAYING) {
        D_800DC6C4--;
    }
    state->state = SOUND_STATE_NONE;
    if (state->userHandle != NULL) {
        if (state == *state->userHandle) {
            *state->userHandle = NULL;
        }
        state->userHandle = NULL;
    }
}

/**
 * Official Name: gsSndpSetPriority
 */
void sndp_set_priority(ALSoundState *sndp, u8 priority) {
    if (sndp != NULL) {
        sndp->priority = priority;
    }
}

/**
 * Official Name: gsSndpGetState
 */
UNUSED u8 sndp_get_state(ALSoundState *sndp) {
    if (sndp != NULL) {
        return sndp->state;
    } else {
        return SOUND_STATE_NONE;
    }
}

ALSoundState *sndp_play(ALBank *bnk, s16 sndIndx, ALSoundState **handlePtr) {
    return sndp_play_with_priority(bnk, sndIndx, 0, handlePtr);
}

ALSoundState *sndp_play_with_priority(ALBank *bank, s16 sndIndx, u8 priority, ALSoundState **handlePtr) {
    ALSound *sound;
    ALSoundState *lastSoundState;
    ALSoundState *soundState;
    ALMicroTime totalDuration;
    s16 loopingSoundID;
    ALMicroTime loopingSoundDuration;
    ALMicroTime duration;
    ALKeyMap *keyMap;

    lastSoundState = NULL;
    loopingSoundID = 0;
    totalDuration = 0;

    if (sndIndx == SOUND_NONE) {
        return NULL;
    }

    do {
        sound = bank->instArray[0]->soundArray[sndIndx - 1];
        soundState = sndp_allocate(bank, sound);
        if (soundState != NULL) {
            ALSndpEvent playEvent;

            gSoundPlayerPtr->lastSoundState = soundState;

            playEvent.common.type = AL_SNDP_PLAY_EVT;
            playEvent.common.state = soundState;
            duration = SOUND_PARAM_DURATION(sound->keyMap);

            if (priority != 0) {
                soundState->priority = priority;
            }

            if (soundState->flags & SOUND_FLAG_LOOPING) {
                soundState->flags &= ~SOUND_FLAG_LOOPING;
                alEvtqPostEvent(&gSoundPlayerPtr->evtq, (ALEvent *) &playEvent, totalDuration + 1);
                loopingSoundDuration = duration + 1;
                loopingSoundID = sndIndx;
            } else {
                //!@bug The 'delay' parameter must match 'totalDuration' to ensure sequential playback.
                // Mismatch causes sounds to overlap or trigger at wrong times.
                alEvtqPostEvent(&gSoundPlayerPtr->evtq, (ALEvent *) &playEvent, duration + 1);
            }

            lastSoundState = soundState;
        }

        totalDuration += duration; // UB: duration may be uninitialized
        keyMap = sound->keyMap;
        sndIndx = SOUND_PARAM_NEXT_SOUND(keyMap);

    } while (sndIndx != SOUND_NONE && soundState != NULL);

    if (lastSoundState != NULL) {
        lastSoundState->flags |= SOUND_FLAG_FINAL_IN_SEQUENCE;
        lastSoundState->userHandle = handlePtr;
        if (loopingSoundID != SOUND_NONE) {
            ALSndpEvent evtRestart;

            lastSoundState->flags |= SOUND_FLAG_LOOPING;
            evtRestart.loopRestart.type = AL_SNDP_LOOP_RESTART_EVT;
            evtRestart.loopRestart.state = lastSoundState;
            evtRestart.loopRestart.soundIndex = loopingSoundID;
            evtRestart.loopRestart.bank = bank;
            alEvtqPostEvent(&gSoundPlayerPtr->evtq, (ALEvent *) &evtRestart, loopingSoundDuration);
        }
    }

    if (handlePtr != NULL) {
        *handlePtr = lastSoundState;
    }
    return lastSoundState;
}

/**
 * Official Name: gsSndpStop
 */
void sndp_stop(ALSoundState *state) {
    ALSndpEvent alEvent;

    alEvent.common.type = AL_SNDP_STOP_EVT;
    alEvent.common.state = state;
    if (state != NULL) {
        state->flags &= ~SOUND_FLAG_LOOPING;
        alEvtqPostEvent(&gSoundPlayerPtr->evtq, &alEvent, 0);
    } else {
        // From JFG
        // osSyncPrintf("WARNING: Attempt to stop NULL sound aborted\n");
    }
}

void sndp_stop_with_flags(u8 flags) {
    OSIntMask mask;
    ALSndpEvent evt;
    ALSoundState *queue;

    mask = osSetIntMask(OS_IM_NONE);
    queue = gSoundStateLists.allocHead;
    while (queue != NULL) {
        evt.common.type = AL_SNDP_STOP_EVT;
        evt.common.state = queue;
        if ((queue->flags & flags) == flags) {
            evt.common.state->flags &= ~SOUND_FLAG_LOOPING;
            alEvtqPostEvent(&gSoundPlayerPtr->evtq, &evt, 0);
        }
        queue = queue->next;
    }
    osSetIntMask(mask);
}

/**
 * Official Name: gsSndpStopAll
 */
UNUSED void func_80004998(void) {
    sndp_stop_with_flags(SOUND_FLAG_FINAL_IN_SEQUENCE);
}

/**
 * Official Name: gsSndpStopAllRetrigger
 */
UNUSED void func_800049B8(void) {
    sndp_stop_with_flags(SOUND_FLAG_FINAL_IN_SEQUENCE | SOUND_FLAG_LOOPING);
}

/**
 * Stops all sounds from playing.
 * Official Name: gsSndpStopAllLooped
 */
void sound_stop_all(void) {
    sndp_stop_with_flags(SOUND_FLAG_FINAL_IN_SEQUENCE | SOUND_FLAG_PERSISTENT);
}

/**
 * Send a message to the sound player to update an existing property of the sound entry.
 * Official Name: gsSndpSetParam
 */
void sndp_set_param(SoundHandle soundMask, s16 type, u32 paramValue) {
    ALSndpEvent evt;
    evt.common.type = type;
    evt.common.state = (void *) soundMask;
    evt.common.param = paramValue;
    if (soundMask != NULL) {
        alEvtqPostEvent(&gSoundPlayerPtr->evtq, (ALEvent *) &evt, 0);
    } else {
        // From JFG
        // osSyncPrintf("WARNING: Attempt to modify NULL sound aborted\n");
    }
}

/**
 * Returns the volume level of the channel ID.
 * Official Name: gsSndpGetMasterVolume
 */
u16 sndp_get_channel_volume(u8 channel) {
    return gSoundChannelVolume[channel];
}

// TODO: The structs used here are almost definitely wrong, but they do match, so it can at least show the pattern we're
// looking for.
/**
 * Looks for the intended audio channel in the main buffer and adjusts its volume
 * Official Name: gsSndpSetMasterVolume
 */
void sndp_set_channel_volume(u8 channel, u16 volume) {
    OSIntMask mask;
    ALSoundState *state;
    UNUSED s32 pad;
    ALSndpEvent evt;

    mask = osSetIntMask(OS_IM_NONE);
    state = gSoundStateLists.allocHead;
    gSoundChannelVolume[channel] = volume;

    while (state != NULL) {
        if ((state->sound->keyMap->keyMin & 0x3F) == channel) {
            evt.common.type = AL_SNDP_UNK_11_EVT;
            evt.common.state = state;
            alEvtqPostEvent(&gSoundPlayerPtr->evtq, (ALEvent *) &evt, 0);
        }
        state = state->next;
    }

    osSetIntMask(mask);
}
