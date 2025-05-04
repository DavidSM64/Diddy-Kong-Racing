#ifndef _AUDIOSFX_H_
#define _AUDIOSFX_H_

#include "types.h"
#include "macros.h"
#include "asset_enums.h"
#include <ultra64.h>
#include "sched.h"
#include "structs.h"
#include "audio.h"

#define AL_SNDP_PLAY_EVT (1 << 0)
#define AL_SNDP_RELEASE_EVT (1 << 1)
#define AL_SNDP_PAN_EVT (1 << 2)
#define AL_SNDP_VOL_EVT (1 << 3)
#define AL_SNDP_PITCH_EVT (1 << 4)
#define AL_SNDP_API_EVT (1 << 5)
#define AL_SNDP_DECAY_EVT (1 << 6)
#define AL_SNDP_END_EVT (1 << 7)
#define AL_SNDP_FX_EVT (1 << 8)
#define AL_SNDP_LOOP_RESTART_EVT (1 << 9)
#define AL_SNDP_STOP_EVT (1 << 10)
#define AL_SNDP_UNK_11_EVT (1 << 11)
#define AL_SNDP_UNK_12_EVT (1 << 12)

enum SoundFlags {
    SOUND_FLAG_FINAL_IN_SEQUENCE = 1 << 0,
    SOUND_FLAG_PERSISTENT = 1 << 1,
    SOUND_FLAG_PLAYING = 1 << 2,
    SOUND_FLAG_LOOPING = 1 << 4,
    SOUND_FLAG_PITCH_SLIDE = 1 << 5
};

enum SoundStates {
    SOUND_STATE_NONE,
    SOUND_STATE_PLAYING,
    SOUND_STATE_STOPPING,
    SOUND_STATE_PREEMPT,
    SOUND_STATE_4,
    SOUND_STATE_5
};

typedef struct ALSoundStateLists {
    /* 0x00 */ ALSoundState *allocHead;
    /* 0x04 */ ALSoundState *allocTail;
    /* 0x08 */ ALSoundState *freeHead;
  } ALSoundStateLists;

/* Unknown Size */
typedef struct SoundPlayer {
    ALPlayer        node;
    ALEventQueue    evtq;
    ALEvent         nextEvent;
    ALSynth        *drvr;
    u32             lastSoundState;
    ALSoundState   *soundStatesArray;
    s32             soundChannelsMax;
    s32             soundChannels;
    s32             frameTime;
    ALMicroTime     nextDelta;
    ALMicroTime     curTime;
} SoundPlayer;

typedef union {

    ALEvent             msg;

    struct {
        u16             type;
        ALSoundState    *state;
        s32             param;
    } common;

    struct {
        s16             type;
        ALSoundState    *state;
        s32             soundIndex;
        ALBank          *bank;
    } loopRestart;
    
} ALSndpEvent;

typedef struct audioMgrConfig_s{
    s32 maxSounds;
    s32 maxEvents;
    s32 maxChannels;
    ALHeap *heap;
    u16  unk10;
} audioMgrConfig;

extern void *alHeapDBAlloc(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size); //lib/src/al
extern void alEvtqNew(ALEventQueue *evtq, ALEventListItem *items, s32 itemCount); //lib/src/unknown_0C9C90.c
extern ALMicroTime alEvtqNextEvent(ALEventQueue *evtq, ALEvent *evt); //lib/src/unknown_0C9C90.c
extern void alSynAddPlayer(ALSynth *drvr, ALPlayer *client); //lib/src/unknown_0C9C90.c
extern void alEvtqPostEvent(ALEventQueue *evtq, ALEvent *evt, ALMicroTime delta); //lib/src/unknown_0C9C90.c Non Matching

void sndp_set_master_volume(u32 volume);
s32 sndp_get_master_volume(void);
void sndp_set_channel_count(s32 numChannels);
void sndp_init_player(audioMgrConfig *c);
ALMicroTime  sndp_voice_handler(void *node);
void sndp_end(ALSoundState *state);
u16 sndp_get_state_counts(u16 *lastAllocListIndex, u16 *lastFreeListIndex);
void sndp_set_priority(ALSoundState *sndp, u8 priority);
ALSoundState *sndp_play(ALBank *bnk, s16 sndIndx, ALSoundState **soundMask);
void sound_stop_all(void);
void sndp_set_param(SoundHandle soundMask, s16 type, u32 volume);
u16 sndp_get_channel_volume(u8 channel);
void sndp_set_channel_volume(u8 channel, u16 volume);
void func_8000418C(ALSoundState *voiceState);
void sndp_stop_with_flags(u8 event);
void sndp_stop(SoundHandle soundMask);
ALSoundState *sndp_allocate(UNUSED ALBank *arg0, ALSound *arg1);

// Non Matching
void sndp_deallocate(ALSoundState *);
ALSoundState * sndp_play_with_priority(ALBank *bnk, s16 sndIndx, u8, ALSoundState **soundMask);
void sndp_handle_event(SoundPlayer *sndp, ALSndpEvent *event);

#endif
