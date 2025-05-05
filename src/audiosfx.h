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
#define AL_SNDP_RETRIGGER_EVT (1 << 9)
#define AL_SNDP_STOP_EVT (1 << 10)
#define AL_SNDP_GROUP_VOL_EVT (1 << 11)
#define AL_SNDP_RELEASE_NEXT_EVT (1 << 12)

#define AL_SNDP_PRIORITY_DEFAULT 64
#define AL_SNDP_GROUP_VOLUME_MAX 32767

enum SoundFlags {
    SOUND_FLAG_FINAL_IN_SEQUENCE = 1 << 0,
    SOUND_FLAG_LOOPED = 1 << 1,
    SOUND_FLAG_PLAYING = 1 << 2,
    SOUND_FLAG_RETRIGGER = 1 << 4,
    SOUND_FLAG_PITCH_SLIDE = 1 << 5
};

enum SoundStates {
    SOUND_STATE_NONE,
    SOUND_STATE_PLAYING,
    SOUND_STATE_STOPPING,
    SOUND_STATE_PREEMPT,
    SOUND_STATE_WAIT_VOICE,
    SOUND_STATE_INIT
};

typedef struct ALSoundState {
    /* 0x00 */ struct ALSoundState *next;
    /* 0x04 */ struct ALSoundState *prev;
    /* 0x08 */ ALSound *sound;
    /* 0x0C */ ALVoice     voice;
    /* 0x28 */ f32 slideMult;
    /* 0x2C */ f32 pitch;
    /* 0x30 */ struct ALSoundState **userHandle;
    /* 0x34 */ s16 volume;
    /* 0x36 */ u8 priority;
    /* 0x38 */ s32 retries;
    /* 0x3C */ ALPan pan;
    /* 0x3D */ u8 fxmix;
    /* 0x3E */ u8 flags;
    /* 0x3F */ u8 state;
} ALSoundState;

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
    s32             maxSystemSoundChannels;
    s32             maxActiveSounds;
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
    } retrigger;
    
} ALSndpEvent;

typedef struct audioMgrConfig_s{
    /* 0x00 */ s32 maxSounds; // Number of ALSoundState structures
    /* 0x04 */ s32 maxEvents; // Maximum number of events that can be held in the queue
    /* 0x08 */ s32 maxChannels;
    /* 0x0C */ ALHeap *heap;
    /* 0x10 */ u16  numGroups;
} audioMgrConfig;

extern void *alHeapDBAlloc(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size);
extern void alEvtqNew(ALEventQueue *evtq, ALEventListItem *items, s32 itemCount);
extern ALMicroTime alEvtqNextEvent(ALEventQueue *evtq, ALEvent *evt);
extern void alSynAddPlayer(ALSynth *drvr, ALPlayer *client);
extern void alEvtqPostEvent(ALEventQueue *evtq, ALEvent *evt, ALMicroTime delta);

void sndp_set_global_volume(u32 volume);
s32 sndp_get_global_volume(void);
void sndp_set_active_sound_limit(s32 numChannels);
void sndp_init_player(audioMgrConfig *c);
ALMicroTime  sndp_voice_handler(void *node);
void sndp_end(ALSoundState *state);
u16 sndp_get_state_counts(u16 *numFree, u16 *numAllocated);
void sndp_set_priority(ALSoundState *sndp, u8 priority);
ALSoundState *sndp_play(ALBank *bnk, s16 sndIndx, SoundHandle *soundMask);
void sndp_stop_all_looped(void);
void sndp_set_param(SoundHandle soundMask, s16 type, u32 volume);
u16 sndp_get_group_volume(u8 channel);
void sndp_set_group_volume(u8 channel, u16 volume);
void sndp_apply_pitch_slide(ALSoundState *voiceState);
void sndp_stop_with_flags(u8 event);
void sndp_stop(SoundHandle soundMask);
ALSoundState *sndp_allocate(UNUSED ALBank *arg0, ALSound *arg1);
void sndp_deallocate(ALSoundState *);
ALSoundState *sndp_play_with_priority(ALBank *bnk, s16 sndIndx, u8 priority, SoundHandle *soundMask);
void sndp_handle_event(SoundPlayer *sndp, ALSndpEvent *event);

#endif
