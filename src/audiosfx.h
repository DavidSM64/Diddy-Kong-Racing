#ifndef _AUDIOSFX_H_
#define _AUDIOSFX_H_

#include "types.h"
#include "macros.h"
#include "audio_internal.h"
#include "asset_enums.h"
#include "libultra_internal.h"
#include "sched.h"

#define AL_SNDP_PLAY_EVT (1 << 0)
#define AL_SNDP_STOP_EVT (1 << 1)
#define AL_SNDP_PAN_EVT (1 << 2)
#define AL_SNDP_VOL_EVT (1 << 3)
#define AL_SNDP_PITCH_EVT (1 << 4)
#define AL_SNDP_API_EVT (1 << 5)
#define AL_SNDP_DECAY_EVT (1 << 6)
#define AL_SNDP_END_EVT (1 << 7)
#define AL_SNDP_FX_EVT (1 << 8)

typedef struct {
  /* 0x00 */ s8 pad00[0x0C];
  /* 0x0C */ ALVoice     voice;
    ALSound     *sound;         /* sound referenced here */
    s16         priority;
    f32         pitch;          /* current playback pitch                    */
    s32         state;          /* play state for this sound                 */
    s16         vol;            /* volume - combined with volume from bank   */
    ALPan       pan;            /* pan - 0 = left, 127 = right               */
    u8          fxMix;          /* wet/dry mix - 0 = dry, 127 = wet          */
  /* 0x3C */ u8 pad3C[2];
  /* 0x3E */ u8 unk3E;
} ALSoundState;

typedef struct unk800DC6BC_40 {
    ALLink node;
    u8 pad0C[0x38];
} unk800DC6BC_40; //ALSoundState

/* Unknown Size */
typedef struct unk800DC6BC {
    ALPlayer        node;
    ALEventQueue    evtq;
    ALEvent         nextEvent;
    ALSynth        *drvr;
    u32             unk3C;
    unk800DC6BC_40 *unk40;
    s32             soundChannelsMax;
    s32             soundChannels;
    s32             frameTime;
    ALMicroTime     nextDelta;
    ALMicroTime     curTime;
} unk800DC6BC; //ALSndPlayer

typedef union {
    ALEvent msg;

    struct{
        s16 type;
        void* state;
        u32 unk04;
    }snd_event;

} ALEvent2;

typedef union {

    ALEvent             msg;

    struct {
        s16             type;
        ALSoundState    *state;
    } common;
    
    struct {
        s16             type;
        ALSoundState    *state;
        s16             vol;
    } vol;
    
    struct {
        s16             type;
        ALSoundState    *state;
        f32             pitch;
    } pitch;
    
    struct {
        s16             type;
        ALSoundState    *state;
        ALPan           pan;
    } pan;
    
    struct {
        s16             type;
        ALSoundState    *state;
        u8              mix;
    } fx;
    
} ALSndpEvent;

typedef struct audioMgrConfig_s{
    u32 unk00;
    u32 unk04;
    u32 maxChannels;
    ALHeap *hp;
    u16  unk10; // Heap Size?
} audioMgrConfig;

extern Acmd *alAudioFrame(Acmd *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen);
extern void *alHeapDBAlloc(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size); //lib/src/al
extern void alEvtqNew(ALEventQueue *evtq, ALEventListItem *items, s32 itemCount); //lib/src/unknown_0C9C90.c
extern ALMicroTime alEvtqNextEvent(ALEventQueue *evtq, ALEvent *evt); //lib/src/unknown_0C9C90.c
extern void alSynAddPlayer(ALSynth *drvr, ALPlayer *client); //lib/src/unknown_0C9C90.c
extern void alEvtqPostEvent(ALEventQueue *evtq, ALEvent *evt, ALMicroTime delta); //lib/src/unknown_0C9C90.c Non Matching

void alSndPNew(audioMgrConfig *c);
void set_sfx_volume_slider(u32 arg0);
s32 sfxGetVolumeSlider(void);
void set_sound_channel_count(s32 numChannels);
void alSndPNew(audioMgrConfig *c);
ALMicroTime  _sndpVoiceHandler(void *node);
void func_8000410C(ALSoundState *state);
u16 func_800042CC(u16 *lastAllocListIndex, u16 *lastFreeListIndex);
void func_80004604(u8 *arg0, u8 arg1);
void func_80004638(ALBank *bnk, s16 sndIndx, s32 arg2);
void func_80004668(ALBank *bnk, s16 sndIndx, u8, s32);
INCONSISTENT void func_8000488C();
void func_800049D8(void);
void func_800049F8(s32 soundMask, s16 type, u32 volume);
u16 get_sound_channel_volume(u8 arg0);
void set_sound_channel_volume(u8 channel, u16 volume);
void func_800048D8(s32);
void func_80004520(ALSoundState *);

#endif
