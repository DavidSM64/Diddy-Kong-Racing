#include "audiosfx.h"
#include "memory.h"
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
s16 *gSoundChannelVolume;

/**** Debug strings ****/
const char D_800E4AB0[] = "Bad soundState: voices =%d, states free =%d, states busy =%d, type %d data %x\n";
const char D_800E4B00[] = "playing a playing sound\n";
const char D_800E4B1C[] = "Nonsense sndp event\n";
const char D_800E4B34[] = "Sound state allocate failed - sndId %d\n";
const char D_800E4B5C[] = "Don't worry - game should cope OK\n";
const char D_800E4B80[] = "WARNING: Attempt to stop NULL sound aborted\n";

static void _removeEvents(ALEventQueue *, ALSoundState *, u16);
void func_80065A80(ALSynth *arg0, struct PVoice_s *arg1, s16 arg2);

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
    ALEventListItem * items;

    /*
     * Init member variables
     */
    gAlSndPlayerPtr->soundChannelsMax = c->maxChannels;
    gAlSndPlayerPtr->soundChannels = c->maxChannels;
    gAlSndPlayerPtr->unk3C = 0;
    gAlSndPlayerPtr->frameTime = 33000; // AL_USEC_PER_FRAME        /* time between API events */
    gAlSndPlayerPtr->sndState = (unk800DC6BC_40 *) alHeapAlloc(c->hp, 1, c->maxSounds * sizeof(unk800DC6BC_40));

    /*
     * init the event queue
     */
    items = (ALEventListItem *) alHeapAlloc(c->hp, 1, c->maxEvents * sizeof(ALEventListItem));
    alEvtqNew(&gAlSndPlayerPtr->evtq, items, c->maxEvents);

    D_800DC6B0.freeList = (ALSoundState *) gAlSndPlayerPtr->sndState;
    for (i = 1; i < c->maxSounds; i++) {
        tmp1 = gAlSndPlayerPtr->sndState;
        alLink(&(tmp1 + i)->node, &(tmp1 + i - 1)->node);
    }

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

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))


void _handleEvent(unk800DC6BC *sndp, ALSndpEvent *event) {
    ALVoiceConfig spC8;
    ALVoice* s3;
    s32 delta;
    s32 s0;
    ALSndpEvent spAC;
    ALSndpEvent sp9C;
    ALSound *s2;
    ALKeyMap *s6;
    s32 sp90;    
    s32 fxMix;
    s32 someFlags;
    ALPan pan;
    s32 sp80;
    s32 sp7C;
    ALSoundState *s1;
    ALSoundState *sp74;

    sp80 = TRUE;
    sp7C = FALSE;
    s1 = NULL;
    sp74 = NULL;

    do {
        if (sp74 != NULL) {
            sp9C.common.state = s1;
            sp9C.common.type = event->common.type;
            sp9C.common.unk8 = event->common.unk8;            
            event = &sp9C;
        }

        s1 = event->common.state;
        s2 = s1->unk8;

        if (s2 == NULL) {
            u16 n2, n3;
            func_800042CC(&n2, &n3);
            return;
        }

        s6 = s2->keyMap;
        sp74 = s1->next;        

        switch (event->common.type) {
            case AL_SNDP_PLAY_EVT:
                if (s1->soundState != 5 && s1->soundState != 4) {
                    return;
                }

                spC8.fxBus = 0;
                spC8.priority = s1->unk36;
                spC8.unityPitch = 0;
                
                s0 = sndp->soundChannels <= D_800DC6C4;

                if (!s0 || (s1->flags & 0x10)) {
                    sp7C = alSynAllocVoice(sndp->drvr, &s1->voice, &spC8);
                }
                if (sp7C) {
                    func_80065A80(sndp->drvr, s1->voice.pvoice, 1);
                }

                s3 = &s1->voice;
                if (!sp7C) {
                    if ((s1->flags & (0x10 | 0x2)) || s1->unk38 > 0) {
                        s1->soundState = 4;
                        s1->unk38--;
                        alEvtqPostEvent(&sndp->evtq, (ALEvent *) event, 33333);
                    } else if (s0) {
                        ALSoundState* iterState = D_800DC6B0.list2;

                        do {
                            if (iterState->unk36 <= s1->unk36 && iterState->soundState != 3) {
                                ALSndpEvent sp5C;

                                sp5C.common.type = AL_SNDP_END_EVT;
                                sp5C.common.state = iterState;
                                iterState->soundState = 3;
                                s0 = FALSE;
                                alEvtqPostEvent(&sndp->evtq, (ALEvent *) &sp5C, 1000);
                                alSynSetVol(sndp->drvr, &iterState->voice, (s1->soundState == 1) * 0, 1000); // FAKE
                            }
                            iterState = iterState->prev;
                        } while (s0 && iterState != NULL);

                        if (!s0) {
                            s1->unk38 = 2;
                            alEvtqPostEvent(&sndp->evtq, (ALEvent *) event, 1001);
                        } else {
                            func_8000410C(s1);
                        }
                    } else {
                        func_8000410C(s1);
                    }
                    return;
                }

                s1->flags |= 4;
                alSynStartVoice(sndp->drvr, s3, s2->wavetable);
                s1->soundState = 1;
                D_800DC6C4++;

                delta = s2->envelope->attackTime / s1->unk2C / s1->unk28;
                sp90 = MAX(0, gSoundChannelVolume[s6->keyMin & 0x3F] * (s2->envelope->attackVolume * s1->unk34 * s2->sampleVolume / 16129) / 32767 - 1);
                sp90 = (u32)(sp90 * sfxVolumeSlider) >> 8;
                alSynSetVol(sndp->drvr, &s1->voice, 0, 0);
                alSynSetVol(sndp->drvr, &s1->voice, sp90, delta);

                pan = MIN(MAX((s1->unk3C + s2->samplePan - AL_PAN_CENTER), AL_PAN_LEFT), AL_PAN_RIGHT);
                alSynSetPan(sndp->drvr, &s1->voice, pan);

                alSynSetPitch(sndp->drvr, &s1->voice, s1->unk2C * s1->unk28);

                fxMix = (s1->unk3D + (s6->keyMax & 0xF)) * 8;
                fxMix = MIN(127, MAX(0, fxMix));
                alSynSetFXMix(sndp->drvr, &s1->voice, fxMix);

                spAC.common.type = AL_SNDP_DECAY_EVT;
                spAC.common.state = s1;
                alEvtqPostEvent(&sndp->evtq, (ALEvent *) &spAC, s2->envelope->attackTime / s1->unk2C / s1->unk28);
                break;
            case AL_SNDP_STOP_EVT:
            case AL_SNDP_UNK_10_EVT:
            case AL_SNDP_UNK_12_EVT:
                if (event->common.type != AL_SNDP_UNK_12_EVT || (s1->flags & 2)) {
                    switch (s1->soundState) {
                        case 1:
                            _removeEvents(&sndp->evtq, s1, AL_SNDP_DECAY_EVT);
                            delta = s2->envelope->releaseTime / s1->unk28 / s1->unk2C;
                            alSynSetVol(sndp->drvr, &s1->voice, 0, delta);
                            if (delta != 0) {
                                spAC.common.type = AL_SNDP_END_EVT;
                                spAC.common.state = s1;
                                alEvtqPostEvent(&sndp->evtq, (ALEvent *) &spAC, delta);
                                s1->soundState = 2;
                            } else {
                                func_8000410C(s1);
                            }
                            break;
                        case 4:
                        case 5:
                            func_8000410C(s1);
                            break;
                    }
                    if (event->common.type == AL_SNDP_STOP_EVT) {
                        event->common.type = AL_SNDP_UNK_12_EVT;
                    }
                }
                break;
            case AL_SNDP_PAN_EVT:
                s1->unk3C = event->common.unk8;
                if (s1->soundState == 1) {
                    pan = MIN(MAX((s1->unk3C + s2->samplePan - AL_PAN_CENTER), AL_PAN_LEFT), AL_PAN_RIGHT);
                    alSynSetPan(sndp->drvr, &s1->voice, pan);
                }
                break;
            case AL_SNDP_PITCH_EVT:
                s1->unk2C = *(f32*)&event->common.unk8;
                if (s1->soundState == 1) {
                    alSynSetPitch(sndp->drvr, &s1->voice, s1->unk2C * s1->unk28);
                    if (s1->flags & 0x20) {
                        func_8000418C(s1);
                    }
                }
                break;
            case AL_SNDP_FX_EVT:
                s1->unk3D = event->common.unk8;
                if (s1->soundState == 1) {
                    fxMix = (s1->unk3D + (s6->keyMax & 0xF)) * 8;
                    fxMix = MIN(127, MAX(0, fxMix));
                    alSynSetFXMix(sndp->drvr, &s1->voice, fxMix);
                }
                break;
            case AL_SNDP_VOL_EVT:
                s1->unk34 = event->vol.vol;
                if (s1->soundState == 1) {
                    sp90 = MAX(0, gSoundChannelVolume[s6->keyMin & 0x3F] * (s2->envelope->decayVolume * s1->unk34 * s2->sampleVolume / 16129) / 32767 - 1);
                    sp90 = (u32)(sp90 * sfxVolumeSlider) >> 8;
                    alSynSetVol(sndp->drvr, &s1->voice, sp90, 1000);
                }
                break;
            case AL_SNDP_UNK_11_EVT:
                if (s1->soundState == 1) {
                    delta = s2->envelope->releaseTime / s1->unk28 / s1->unk2C;
                    sp90 = MAX(0, gSoundChannelVolume[s6->keyMin & 0x3F] * (s2->envelope->decayVolume * s1->unk34 * s2->sampleVolume / 16129) / 32767 - 1);
                    sp90 = (u32)(sp90 * sfxVolumeSlider) >> 8;                    
                    alSynSetVol(sndp->drvr, &s1->voice, sp90, delta);
                }
                break;
            case AL_SNDP_DECAY_EVT:
                if (!(s1->flags & 2)) {
                    sp90 = MAX(0, gSoundChannelVolume[s6->keyMin & 0x3F] * (s2->envelope->decayVolume * s1->unk34 * s2->sampleVolume / 16129) / 32767 - 1);
                    sp90 = (u32)(sp90 * sfxVolumeSlider) >> 8;
                    delta = s2->envelope->decayTime / s1->unk28 / s1->unk2C;
                    alSynSetVol(sndp->drvr, &s1->voice, sp90, delta);

                    spAC.common.type = AL_SNDP_STOP_EVT;
                    spAC.common.state = s1;
                    alEvtqPostEvent(&sndp->evtq, (ALEvent *) &spAC, delta);

                    if (s1->flags & 0x20) {
                        func_8000418C(s1);
                    }
                }
                break;
            case AL_SNDP_END_EVT:
                func_8000410C(s1);
                break;
            case AL_SNDP_UNK_9_EVT:
                if (s1->flags & 0x10) {
                    ALSoundState* newSOund = func_80004638(event->unk9.unkC, event->unk9.unk8, s1->unk30);
                    if (newSOund != NULL) {
                        sound_event_update(newSOund, AL_SNDP_VOL_EVT, s1->unk34);
                        if ((!event) && (!event)) {}
                        sound_event_update(newSOund, AL_SNDP_PAN_EVT, s1->unk3C);
                        sound_event_update(newSOund, AL_SNDP_FX_EVT, s1->unk3D);
                        sound_event_update(newSOund, AL_SNDP_PITCH_EVT, *(s32*)&s1->unk2C);
                    }
                }
                break;
            default:
                break;
        }

        s1 = sp74;
        someFlags = event->common.type & (AL_SNDP_PLAY_EVT | AL_SNDP_PITCH_EVT | AL_SNDP_DECAY_EVT | AL_SNDP_END_EVT | AL_SNDP_UNK_9_EVT);
        
        if (s1 != NULL && !someFlags) {
            sp80 = s1->flags & 1;
        }

        
    } while (!sp80 && s1 != NULL && !someFlags);
}

void func_8000410C(ALSoundState *state) {
    if (state->flags & AL_SNDP_PAN_EVT) {
        alSynStopVoice(gAlSndPlayerPtr->drvr, &state->voice);
        alSynFreeVoice(gAlSndPlayerPtr->drvr, &state->voice);
    }
    func_80004520(state);
    _removeEvents(&gAlSndPlayerPtr->evtq, state, 0xFFFF);
}

void func_8000418C(ALVoiceState *voiceState) {
    ALEvent_unk8000418C evt;
    f32 sp1C;

    sp1C = alCents2Ratio(((ALLink_unk8000418C *) voiceState->voice.node.prev->prev)->unk5) * voiceState->vibrato;
    evt.type = AL_SEQP_STOP_EVT;
    evt.unk4 = voiceState;
    evt.unk8 = *((s32 *) &sp1C); // But why tho?
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

    mask = osSetIntMask(OS_IM_NONE);
    nextFreeList = D_800DC6B0.list1;
    nextAllocList = D_800DC6B0.freeList;
    prevFreeList = D_800DC6B0.list2;

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
ALSoundState *func_80004384(UNUSED ALBank *arg0, ALSound *arg1) {
    s32 temp;
    ALKeyMap *temp_a2;
    ALSoundState *state;
    u32 mask;
    s32 temp_a1;

    state = D_800DC6B0.freeList;
    temp_a2 = arg1->keyMap;
    if (state != NULL) {
        mask = osSetIntMask(OS_IM_NONE);
        D_800DC6B0.freeList = state->next;
        alUnlink((ALLink *) state);
        if (D_800DC6B0.list1 != NULL) {
            state->next = D_800DC6B0.list1;
            state->prev = NULL;
            D_800DC6B0.list1->prev = (ALSoundState *) state;
            D_800DC6B0.list1 = (ALSoundState *) state;
        } else {
            state->prev = NULL;
            state->next = NULL;
            D_800DC6B0.list1 = (ALSoundState *) state;
            D_800DC6B0.list2 = (ALSoundState *) state;
        }
        osSetIntMask(mask);

        temp = ((arg1->envelope->decayTime + 1) == 0);
        temp_a1 = temp + 0x40;
        temp = 6000;
        state->unk36 = temp_a1;
        state->soundState = 5;
        state->unk38 = 2;
        state->unk8 = arg1;
        state->unk2C = 1.0f;
        state->flags = temp_a2->keyMax & 0xF0;
        state->unk30 = 0;
        if (state->flags & 0x20) {
            state->unk28 = alCents2Ratio((temp_a2->keyBase * 100) - temp);
        } else {
            state->unk28 = alCents2Ratio(((temp_a2->keyBase * 100) + temp_a2->detune) - temp);
        }
        if (temp_a1 != 0x40) {
            state->flags |= 2;
        }
        state->unk3D = 0;
        state->unk3C = 0x40;
        state->unk34 = 0x7FFF;
    }
    return state;
}

void func_80004520(ALSoundState *soundState) {
    if (soundState == D_800DC6B0.list1) {
        D_800DC6B0.list1 = soundState->next;
    }
    if (soundState == D_800DC6B0.list2) {
        D_800DC6B0.list2 = soundState->prev;
    }
    alUnlink((ALLink *) soundState);
    if (D_800DC6B0.freeList != NULL) {
        soundState->next = D_800DC6B0.freeList;
        soundState->prev = NULL;
        D_800DC6B0.freeList->prev = soundState;
        D_800DC6B0.freeList = soundState;
    } else {
        soundState->prev = NULL;
        soundState->next = NULL;
        D_800DC6B0.freeList = soundState;
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
        sndp->unk36 = priority;
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

ALSoundState *func_80004638(ALBank *bnk, s16 sndIndx, ALSoundState **soundMask) {
    return func_80004668(bnk, sndIndx, 0, soundMask);
}

ALSoundState *func_80004668(ALBank *bnk, s16 sndIndx, u8 arg2, ALSoundState **handlePtr) {
    ALSound* temp_s2;
    ALSoundState* s7;
    ALSoundState* v0;
    ALMicroTime s4;
    s16 sp6E;
    ALMicroTime sp68;
    ALMicroTime s3;
    ALKeyMap *keyMap;

    s7 = NULL;
    sp6E = 0;
    s4 = 0;        

    if (sndIndx == 0) {
        return NULL;
    }

    do {
        temp_s2 = bnk->instArray[0]->soundArray[sndIndx - 1];
        v0 = func_80004384(bnk, temp_s2);
        if (v0 != NULL) {
            ALSndpEvent evt;

            gAlSndPlayerPtr->unk3C = v0;

            evt.common.type = AL_SNDP_PLAY_EVT;
            evt.common.state = v0;
            s3 = temp_s2->keyMap->velocityMax * 33333;

            if (arg2 != 0) {
                v0->unk36 = arg2;
            }

            if (v0->flags & 0x10) {
                v0->flags &= ~0x10;
                alEvtqPostEvent(&gAlSndPlayerPtr->evtq, (ALEvent*)&evt, s4 + 1);
                sp68 = s3 + 1;
                sp6E = sndIndx;
            } else {
                alEvtqPostEvent(&gAlSndPlayerPtr->evtq, (ALEvent*)&evt, s3 + 1);
            }

            s7 = v0;
        }

        s4 += s3;
        keyMap = temp_s2->keyMap;
        sndIndx = keyMap->velocityMin + (keyMap->keyMin & 0xC0) * 4; // What is going on here?

    } while (sndIndx != 0 && v0 != NULL);

    if (s7 != NULL) {
        s7->flags |= 1;
        s7->unk30 = handlePtr;
        if (sp6E != 0) {
            ALSndpEvent evt2;

            s7->flags |= 0x10;
            evt2.unk9.type = AL_SNDP_UNK_9_EVT;
            evt2.unk9.state = s7;
            evt2.unk9.unk8 = sp6E;
            evt2.unk9.unkC = bnk;
            alEvtqPostEvent(&gAlSndPlayerPtr->evtq, (ALEvent*)&evt2, sp68);
        }
    }

    if (handlePtr != NULL) {
        *handlePtr = s7;
    }
    return s7;
}

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
    queue = D_800DC6B0.list1;
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
void sound_event_update(SoundHandle soundMask, s16 type, u32 volume) {
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
    queue = (ALEventQueue *) D_800DC6B0.list1;
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
