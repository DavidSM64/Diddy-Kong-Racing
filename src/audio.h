#ifndef _AUDIO_H_
#define _AUDIO_H_

#include "types.h"
#include "audio_internal.h"
#include "sched.h"
#include "structs.h"

#define AUDIO_CHANNELS 16
#define MUSIC_CHAN_MASK_NONE 0xFFFFFFFF

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
typedef struct MusicData {
    u8 volume;
    u8 tempo;
    u8 reverb;
} MusicData;

/* Size: 0x08 bytes */
typedef struct DelayedSound {
    /* 0x00 */ u16 soundId;
    /* 0x02 */ s16 timer;
    /* 0x04 */ SoundMask *soundMask;
} DelayedSound;

void  alCSPNew(ALCSPlayer *seqp, ALSeqpConfig *config); //lib/src/al/csplayer.c
void  alCSPSetBank(ALCSPlayer *seqp, ALBank *b); //lib/src/unknown_0C8660.c
void set_voice_limit(ALSeqPlayer *seqp, u8 voiceLimit); //lib/src/mips1/alseqplayer.c
void    *alHeapDBAlloc(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size); //lib/src/al/alHeapDBAlloc.c
void alCSPSetChlPan(ALCSPlayer *seqp, u8 channel, ALPan pan); //lib/src/unknown_0C84E0.c
void alCSPSetChlVol(ALCSPlayer *, u8 channel, u8 volume); //lib/src/unknown_0C84E0.c
u8 alCSPGetChlVol(ALCSPlayer *seqp, u8 channel); //lib/src/al
void alCSPSetFadeIn(ALSeqPlayer *seqp, u8 channel, ALPan pan); //lib/src/unknown_0647A0.c
u8 alCSPGetFadeIn(ALCSPlayer *seqp, u8 channel); //lib/src/mips1/al/unknown_064800.c
u8 alSeqpGetChlFXMix(ALSeqPlayer *seqp, u8 channel); //lib/src/al/alSeqpGetChlFXMix.c
void alFxReverbSet(u8 arg0); //lib/src/mips1/al/reverb.c
u8 _alFxEnabled(); //lib/src/mips1/al/reverb.c
void alHeapInit(ALHeap *hp, u8 *base, s32 len); //lib/src/al/alHeapInit.c
void alBnkfNew(ALBankFile *ctl, u8 *tbl); //lib/src/al/global_asm.c
void alCSPSetVol(ALCSPlayer *seqp, s16 volume); //lib/src/al/alCSPSetVol.c
void alCSPStop(ALCSPlayer *seqp); //lib/src/al/unknown_0C91A0.c
s32  alCSPGetState(ALCSPlayer *seqp); //lib/src/unknown_0C8650.c

void audio_init(OSSched *sc);
void sound_volume_reset(u8 skipReset);
void sound_volume_change(s32 behaviour);
void music_change_off(void);
void music_change_on(void);
void music_play(u8 seqID);
void music_voicelimit_set(u8 voiceLimit);
void music_voicelimit_change_off(void);
void music_voicelimit_change_on(void);
void music_jingle_voicelimit_set(u8 voiceLimit);
void music_fade(s32 time);
void music_volume_reset(void);
void sound_update_queue(u8 updateRate);
void sound_play_delayed(u16 soundId, SoundMask *soundMask, f32 delayTime);
void sound_clear_delayed(void);
u16 music_channel_get_mask(void);
void music_dynamic_set(u16 channelMask);
void music_channel_off(u8 channel);
s32 music_channel_active(s32 channel);
void music_channel_on(u8 channel);
void music_channel_pan_set(u8 channel, ALPan pan);
void music_channel_volume_set(u8 channel, u8 volume);
void music_channel_fade_set(u8 channel, ALPan fade);
u8 music_channel_fade(u8 channel);
void music_channel_reset_all(void);
void music_tempo_set_relative(f32 tempo);
void music_tempo_set(s32 tempo);
s16 music_tempo(void);
u8 music_is_playing(void);
void music_jingle_play_safe(u8 jingleID);
void sound_jingle_tempo_set(s32 tempo);
void music_stop(void);
u8 music_can_play(void);
void music_jingle_stop(void);
u8 music_current_sequence(void);
u8 music_jingle_current(void);
void music_volume_set(u8 volume);
void music_volume_config_set(u32 slider_val);
u8 music_volume(void);
s32 music_volume_config(void);
void music_jingle_volume_set(u8 arg0);
void music_jingle_pan_set(ALPan pan);
void music_jingle_play(u8 seqID);
u32 music_jingle_playing(void);
u16 sound_distance(u16 soundId);
void sound_play_spatial(u16 soundID, f32 x, f32 y, f32 z, s32 **soundMask);
void func_80001F14(u16 soundID, s32 *soundMask);
u16 sound_count(void);
u8 music_sequence_count(void);
void sound_table_properties(SoundData **table, s32 *size, s32 *count);
u8 gSoundBank_GetSoundDecayTime(u16 soundID);
ALSeqPlayer *sound_seqplayer_init(s32 maxVoices, s32 maxEvents);
void music_sequence_start(u8 seqID, ALSeqPlayer *seqPlayer);
void music_sequence_stop(ALSeqPlayer *seqPlayer);
void sound_reverb_set(u8 setting);
void alSeqFileNew(ALSeqFile *file, u8 *base);
void func_80063A90(ALSeqPlayer *seqp, u8 channel);
void sound_volume_set_relative(u16 soundID, void *soundState, u8 volume);
void music_sequence_init(ALSeqPlayer *seqp, void *sequence, u8 *seqID, ALCSeq *seq);
void sound_play(u16 soundID, s32* soundMask);
f32 music_animation_fraction(void);
void func_80009B7C(s32 *soundState, f32 x, f32 y, f32 z);

#endif
