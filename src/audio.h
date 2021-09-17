#ifndef _UNKNOWN_001050_H_
#define _UNKNOWN_001050_H_

#include "types.h"
#include "audio_internal.h"

extern ALCSPlayer* gMusicPlayer;
extern ALCSPlayer* gSndFxPlayer;
extern u8 musicRelativeVolume;
extern u8 sfxRelativeVolume;
extern u8 D_800DC640;
extern u8 D_800DC644;
extern s32 D_800DC648;
extern s32 audioPrevCount;
extern f32 D_800DC650;
extern s32 musicVolumeSliderPercentage;
extern s32 D_800DC658;
extern u8 D_800DC65C;
extern u8  D_800DC660;
extern s32 D_800DC664;
extern s32 D_800DC668;
extern s32 D_800DC66C;
extern u8 D_800DC670;
extern u8 D_800DC65C;

/* Size: 0x0A bytes */
typedef struct unk80115D18 {
    u8 pad0[6];
    u16 unk6;
    u8 pad8[2];
} unk80115D18;

/* Size: 3 bytes */
typedef struct unk80115D1C {
    u8 unk0;
    u8 unk1;
    u8 unk2;
} unk80115D1C;

void  alCSPNew(ALCSPlayer *seqp, ALSeqpConfig *config); //lib/src/al/csplayer.c
void  alCSPSetBank(ALCSPlayer *seqp, ALBank *b); //lib/src/unknown_0C8660.c
void func_8000B010(ALCSPlayer *, u8); //lib/src/mips1/alseqplayer.c
void    *alHeapDBAlloc(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size); //lib/src/al/alHeapDBAlloc.c
s32 alCSPSetChlPan(ALCSPlayer *seqp, u8 chan, ALPan pan); //lib/src/unknown_0C84E0.c
void alCSPSetChlVol(ALCSPlayer *, u8 chan, u8 vol); //lib/src/unknown_0C84E0.c
s32 alCSPGetChlVol(ALCSPlayer *seqp, u8 chan); //lib/src/al
void func_80063BA0(ALCSPlayer *seqp, u8 arg1, u8 arg2); //lib/src/unknown_0647A0.c
u8 func_80063C00(ALCSPlayer *seqp, u8 arg1); //lib/src/mips1/al/unknown_064800.c
u8 alSeqpGetChlFXMix(ALSeqPlayer *seqp, u8 chan); //lib/src/al/alSeqpGetChlFXMix.c
void func_8006492C(u8 arg0); //lib/src/mips1/al/reverb.c

ALCSPlayer *func_80002224(s32 _max_voices, s32 _max_events);
void audio_init(u32 arg0);
void set_relative_volume_for_music(u8 vol);
void func_80000890(u8 arg0);
void func_80000968(s32 arg0);
void func_80000B18(void);
void func_80000B28(void);
void func_800022BC(u8 arg0, ALCSPlayer *arg1);
void play_music(u8 arg0);
void func_80000BE0(u8 arg0);
void func_80000C1C(void);
void func_80000C2C(void);
void func_80000C38(u8 arg0);
void func_80000C68(u8 arg0);
void func_80000C98(s32 arg0);
void func_80000CBC(void);
void func_80000D00(u8 arg0);
void func_80000FDC(u16 arg0, s32 arg1, f32 arg2);
void func_80001050(void);
u16 musicGetChanMask(void);
void func_80001074(u16 arg0);
void func_80001114(u8 arg0);
s32 musicGetChnlActive(s32 arg0);
void func_80001170(u8 arg0);
void musicSetChlPan(u8 chan, ALPan pan);
void musicSetChlVol(u8 chan, u8 vol);
s32 musicGetChlVol(u8 arg0);
void func_80001268(u8 arg0, u8 arg1);
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
void play_sound(u8 arg0);
u32 func_80001C08(void);
void func_80001C5C(u16 arg0);
u16 func_80001CB8(u16 arg0);
void func_80001EA8(u16 arg0, f32 x, f32 y, f32 z, s32 **arg4);
void func_80001F14(u16 sndIndx, u32 *arg1);
u16 ALBankFile_80115D14_GetSoundCount(void);
u8 ALSeqFile_80115CF8_GetSeqCount(void);
void func_80002128(unk80115D18 **arg0, s32 *arg1, s32 *arg2);
void func_8000216C(unk80115D1C **arg0, s32 *arg1, s32 *arg2);
u8 ALBankFile_80115D14_GetSoundDecayTime(u16 sndIndx);
ALCSPlayer *func_80002224(s32 _max_voices, s32 _max_events);
void func_800022BC(u8 arg0, ALCSPlayer *arg1);
void func_80002570(ALCSPlayer *seqp);
void func_80002608(u8 arg0);
u8 func_80002630(void);

void func_80001D04(u16, s32*); //Non matching.
void func_8000232C(ALCSPlayer *seqp, void *ptr, u8 *arg2, ALCSeq *seq); //Non Matching
f32 func_800015F8(void); //Non Matching
void func_80001FB8(u16 arg0); //Non Matching
void func_8000232C(ALCSPlayer *seqp, void *ptr, u8 *arg2, ALCSeq *seq); // Non Matching
void func_80009B7C(s32 *arg0, f32 x, f32 y, f32 z); // Non Matching

#endif
