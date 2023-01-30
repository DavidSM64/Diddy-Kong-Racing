#ifndef _AUDIOSFX_H_
#define _AUDIOSFX_H_

#include "types.h"
#include "macros.h"
#include "audio_internal.h"
#include "asset_enums.h"
#include "libultra_internal.h"
#include "sched.h"
#include "audiomgr.h"

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
