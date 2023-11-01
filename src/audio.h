#ifndef _AUDIO_H_
#define _AUDIO_H_

#include "types.h"
#include "audio_internal.h"
#include "sched.h"

#define AUDIO_CHANNELS 16

enum AudioVolumeBehaviour {
    VOLUME_NORMAL,
    VOLUME_LOWER,
    VOLUME_LOWER_AMBIENT,
    VOLUME_UNK03,
};

/* Size: 0x0A bytes */
typedef struct SoundData {
 u16 soundBite; // Audio file index.
 u8 volume; // Multiplied by 256. 128 = 32768, max volume.
 u8 unk3;
 u8 pitch; // Fractional. 100 = 1.0f.
 u8 unk5;
 u16 distance; // Ingame units distance, same as any other.
 u8 unk8;
 u8 unk9;
} SoundData;


/* Size: 0x03 bytes */
typedef struct unk80115D1C {
    u8 volume;
    u8 tempo;
    u8 reverb;
} unk80115D1C;

/* Size: 0x08 bytes */
typedef struct unk80115D48 {
    /* 0x00 */ u16 soundId;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s32 unk4;
} unk80115D48;

void  alCSPNew(ALCSPlayer *seqp, ALSeqpConfig *config); //lib/src/al/csplayer.c
void  alCSPSetBank(ALCSPlayer *seqp, ALBank *b); //lib/src/unknown_0C8660.c
void set_voice_limit(ALSeqPlayer *seqp, u8 voiceLimit); //lib/src/mips1/alseqplayer.c
void    *alHeapDBAlloc(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size); //lib/src/al/alHeapDBAlloc.c
void alCSPSetChlPan(ALCSPlayer *seqp, u8 chan, ALPan pan); //lib/src/unknown_0C84E0.c
void alCSPSetChlVol(ALCSPlayer *, u8 chan, u8 vol); //lib/src/unknown_0C84E0.c
u8 alCSPGetChlVol(ALCSPlayer *seqp, u8 chan); //lib/src/al
void func_80063BA0(ALSeqPlayer *seqp, u8 chan, ALPan pan); //lib/src/unknown_0647A0.c
u8 func_80063C00(ALCSPlayer *seqp, u8 chan); //lib/src/mips1/al/unknown_064800.c
u8 alSeqpGetChlFXMix(ALSeqPlayer *seqp, u8 chan); //lib/src/al/alSeqpGetChlFXMix.c
void alFxReverbSet(u8 arg0); //lib/src/mips1/al/reverb.c
u8 _alFxEnabled(); //lib/src/mips1/al/reverb.c
void alHeapInit(ALHeap *hp, u8 *base, s32 len); //lib/src/al/alHeapInit.c
void alBnkfNew(ALBankFile *ctl, u8 *tbl); //lib/src/al/global_asm.c
void alCSPSetVol(ALCSPlayer *seqp, s16 vol); //lib/src/al/alCSPSetVol.c
void alCSPStop(ALCSPlayer *seqp); //lib/src/al/unknown_0C91A0.c
s32  alCSPGetState(ALCSPlayer *seqp); //lib/src/unknown_0C8650.c

void audio_init(OSSched *arg0);
void reset_sound_volume(u8 skipReset);
void adjust_audio_volume(s32 arg0);
void func_80000B18(void);
void func_80000B28(void);
void play_music(u8 seqID);
void set_music_player_voice_limit(u8 voiceLimit);
void func_80000C1C(void);
void func_80000C2C(void);
void set_sndfx_player_voice_limit(u8 voiceLimit);
void func_80000C68(u8 arg0);
void set_music_fade_timer(s32 time);
void func_80000CBC(void);
void handle_music_fade(u8 updateRate);
void func_80000FDC(u16 soundId, s32 arg1, f32 arg2);
void func_80001050(void);
u16 musicGetChanMask(void);
void music_dynamic_reset(u16 arg0);
void func_80001114(u8 chan);
s32 musicGetChnlActive(s32 arg0);
void func_80001170(u8 arg0);
void musicSetChlPan(u8 chan, ALPan pan);
void musicSetChlVol(u8 chan, u8 vol);
u8 musicGetChlVol(u8 arg0);
void func_80001268(u8 chan, ALPan pan);
u8 func_800012A8(u8 arg0);
void func_800012E8(void);
u8 func_80001358(u8 arg0, u8 arg1, s32 arg2);
void func_80001440(u8 *arg0);
void multiply_music_tempo(f32 tempo);
void musicSetTempo(s32 tempo);
s16 musicGetTempo(void);
u8 music_is_playing(void);
void sound_get_properties(u8 arg0, u8 *arg1, u8 *arg2, u8 *arg3);
void music_jingle_play_safe(u8 a0);
void sfxSetTempo(s32 tempo);
void music_stop(void);
void music_enabled_set(u8 arg0);
u8 music_can_play(void);
void music_jingle_stop(void);
u8 music_current_sequence(void);
u8 func_80001954(void);
u8 music_jingle_current(void);
void set_relative_volume_for_music(u8 vol);
void set_music_volume_slider(u32 slider_val);
u8 musicGetRelativeVolume(void);
s32 musicGetVolSliderPercentage(void);
void sfxSetRelativeVolume(u8 arg0);
void sfxSetPan(ALPan pan);
void music_jingle_play(u8 seqID);
u32 music_jingle_playing(void);
void set_all_channel_volume(u16 arg0);
u16 sound_distance(u16 soundId);
void play_sound_spatial(u16 soundID, f32 x, f32 y, f32 z, s32 **arg4);
void func_80001F14(u16 soundID, s32 *soundMask);
u16 sound_count(void);
u8 music_sequence_count(void);
void sound_pool_properties(SoundData **arg0, s32 *arg1, s32 *arg2);
void music_pool_properties(unk80115D1C **arg0, s32 *arg1, s32 *arg2);
u8 gSoundEffectsTable_GetSoundDecayTime(u16 soundID);
ALSeqPlayer *sound_seqplayer_init(s32 _max_voices, s32 _max_events);
void music_sequence_start(u8 arg0, ALSeqPlayer *arg1);
void music_sequence_stop(ALSeqPlayer *seqp);
void sound_reverb_set(u8 arg0);
u8 sound_reverb_enabled(void);
void alSeqFileNew(ALSeqFile *file, u8 *base);
void func_80063A90(ALSeqPlayer *seqp, u8 chan);
void func_80001FB8(u16 soundID, void *soundState, u8 volume);
void music_sequence_init(ALSeqPlayer* arg0, void* arg1, u8* arg2, ALCSeq* arg3);

void play_sound_global(u16 soundID, s32* soundMask); //Non matching.
f32 music_animation_fraction(void);
void func_80009B7C(s32 *arg0, f32 x, f32 y, f32 z); // Non Matching

#endif
