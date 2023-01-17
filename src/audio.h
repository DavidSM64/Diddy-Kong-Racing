#ifndef _AUDIO_H_
#define _AUDIO_H_

#include "types.h"
#include "audio_internal.h"
#include "sched.h"

enum AudioVolumeBehaviour {
    VOLUME_NORMAL,
    VOLUME_LOWER,
    VOLUME_LOWER_AMBIENT,
    VOLUME_UNK03,
};

/* Size: 0x0A bytes */
typedef struct unk80115D18 {
 u16 unk0;
 u8 unk2;
 u8 unk3;
 u8 unk4;
 u8 unk5;
 u16 unk6;
 u8 unk8;
 u8 unk9;
} unk80115D18;


/* Size: 0x03 bytes */
typedef struct unk80115D1C {
    u8 unk0;
    u8 unk1;
    u8 unk2;
} unk80115D1C;

/* Size: 0x08 bytes */
typedef struct unk80115D48 {
    /* 0x00 */ u16 unk0;
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
void func_8006492C(u8 arg0); //lib/src/mips1/al/reverb.c
u8 func_8006493C(); //lib/src/mips1/al/reverb.c
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
void func_80000FDC(u16 arg0, s32 arg1, f32 arg2);
void func_80001050(void);
u16 musicGetChanMask(void);
void func_80001074(u16 arg0);
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
void func_800014BC(f32 arg0);
void musicSetTempo(s32 tempo);
s16 musicGetTempo(void);
u8 music_is_playing(void);
void func_80001728(u8 arg0, u8 *arg1, u8 *arg2, u8 *arg3);
void func_80001784(u8 a0);
void sfxSetTempo(s32 tempo);
void func_80001844(void);
void func_80001878(u8 arg0);
u8 func_800018D0(void);
void func_800018E0(void);
u8 func_80001918(void);
u8 func_80001954(void);
u8 func_80001980(void);
void set_relative_volume_for_music(u8 vol);
void set_music_volume_slider(u32 slider_val);
u8 musicGetRelativeVolume(void);
s32 musicGetVolSliderPercentage(void);
void sfxSetRelativeVolume(u8 arg0);
void sfxSetPan(ALPan pan);
void play_sequence(u8 seqID);
u32 func_80001C08(void);
void set_all_channel_volume(u16 arg0);
u16 func_80001CB8(u16 arg0);
void play_sound_spatial(u16 soundID, f32 x, f32 y, f32 z, s32 **arg4);
void func_80001F14(u16 soundID, s32 *arg1);
u16 ALBankFile_80115D14_GetSoundCount(void);
u8 ALSeqFile_80115CF8_GetSeqCount(void);
void func_80002128(unk80115D18 **arg0, s32 *arg1, s32 *arg2);
void func_8000216C(unk80115D1C **arg0, s32 *arg1, s32 *arg2);
u8 ALBankFile_80115D14_GetSoundDecayTime(u16 soundID);
ALSeqPlayer *func_80002224(s32 _max_voices, s32 _max_events);
void func_800022BC(u8 arg0, ALSeqPlayer *arg1);
void func_80002570(ALSeqPlayer *seqp);
void func_80002608(u8 arg0);
u8 func_80002630(void);
void alSeqFileNew(ALSeqFile *file, u8 *base);
void func_80063A90(ALSeqPlayer *seqp, u8 chan);
void func_80001FB8(u16 soundID, void *soundState, u8 volume);
void func_8000232C(ALSeqPlayer* arg0, void* arg1, u8* arg2, ALCSeq* arg3);

void play_sound_global(u16 soundID, s32* soundMask); //Non matching.
f32 audio_get_chr_select_anim_frac(void);
void func_80009B7C(s32 *arg0, f32 x, f32 y, f32 z); // Non Matching
void func_8000974C(u16 soundId, f32 x, f32 y, f32 z, u8 arg4, u8 arg5, u8 arg6, u16 arg7, s32 arg8, u8 arg9, u8 argA, u32 *soundMask); // Non Matching

#endif
