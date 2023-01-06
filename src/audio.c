/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80000450 */

#include "audio.h"
#include "memory.h"

#include "types.h"
#include "macros.h"
#include "asset_enums.h"
#include "asset_loading.h"
#include "audio_internal.h"
#include "unknown_003260.h"
#include "sched.h"
#include "video.h"
#include "lib/src/mips1/al/unknown_0646F0.h"

/************ .data ************/

ALSeqPlayer *gMusicPlayer = NULL;
ALSeqPlayer *gSndFxPlayer = NULL;
u8 musicRelativeVolume = 127;
u8 sfxRelativeVolume = 127;
u8 D_800DC640 = 1;
u8 D_800DC644 = 0;
s32 D_800DC648 = 0;
s32 audioPrevCount = 0;
f32 sMusicFadeVolume = 1.0f;
s32 musicVolumeSliderPercentage = 256;
s32 D_800DC658 = 0;
u8 D_800DC65C = 0;
u8 D_800DC660 = 0;
UNUSED s32 D_800DC664 = 0;
UNUSED s32 D_800DC668 = 0; // Currently unknown, might be a different type.
s32 sMusicVolumeMultiplier = 256; // This is never not 256...
u8 D_800DC670 = 0;

/*******************************/

/************ .rodata ************/

/*********************************/

/************ .bss ************/

#define AUDIO_HEAP_SIZE 0x29D88

// The audio heap is located at the start of the BSS section.
u8 gBssSectionStart[AUDIO_HEAP_SIZE];

ALHeap gALHeap;

/* Unknown size */
typedef struct unk80115CF8 {
    u8 pad0[2];
    s16 unk2;
} unk80115CF8;

ALSeqFile *ALSeqFile_80115CF8;
void *D_80115CFC;

void *D_80115D00;
u8 D_80115D04;
u8 D_80115D05;
s32 musicTempo;
u32 *D_80115D0C;
ALBankFile *ALBankFile_80115D10; // And I have reason to believe these are voice clips.
ALBankFile *ALBankFile_80115D14; // These are sound effects, I do not know if it is ALL the sound effects.

unk80115D18 *sSoundEffectsPool;
unk80115D1C *sMusicPool;

s32 D_80115D20;
s32 D_80115D24;
u32 sSoundEffectsPoolSize;
u32 sMusicPoolSize;
s16 sMusicTempo;
f32 D_80115D34;
s32 sMusicDelayTimer;
s32 sMusicDelayLength;
u8 D_80115D40;
u8 D_80115D41;
unk80115D48 D_80115D48[8];
ALCSeq D_80115D88;
ALCSeq D_80115E80;
u8 D_80115F78;
u8 D_80115F79;
s32 D_80115F7C;
s32 *gGlobalSoundMask;
u32 *gSpatialSoundMask;
u32 D_80115F88;

/******************************/

void audio_init(OSSched *sc) {
    s32 iCnt;
    ALSynConfig synth_config;
    s32 *addrPtr;
    u32 seqfSize;
    u32 seq_max_len;
    audioMgrConfig audConfig;

    seq_max_len = 0;
    alHeapInit(&gALHeap, gBssSectionStart, AUDIO_HEAP_SIZE);

    addrPtr = (s32 *) load_asset_section_from_rom(ASSET_AUDIO_TABLE);
    ALBankFile_80115D14 = (ALBankFile *) allocate_from_main_pool_safe(addrPtr[2] - addrPtr[1], COLOUR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, (u32) ALBankFile_80115D14, addrPtr[1], addrPtr[2] - addrPtr[1]);
    alBnkfNew(ALBankFile_80115D14, get_rom_offset_of_asset(ASSET_AUDIO, addrPtr[2]));

    sSoundEffectsPoolSize = addrPtr[7] - addrPtr[6];
    sSoundEffectsPool = (unk80115D18 *) allocate_from_main_pool_safe(sSoundEffectsPoolSize, COLOUR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, (u32) sSoundEffectsPool, addrPtr[6], sSoundEffectsPoolSize);
    D_80115D20 = sSoundEffectsPoolSize / 10;

    sMusicPoolSize = addrPtr[6] - addrPtr[5];
    sMusicPool = (unk80115D1C *) allocate_from_main_pool_safe(sMusicPoolSize, COLOUR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, (u32) sMusicPool, addrPtr[5], sMusicPoolSize);
    D_80115D24 = sMusicPoolSize / 3;

    ALBankFile_80115D10 = (ALBankFile *) allocate_from_main_pool_safe(addrPtr[0], COLOUR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, (u32) ALBankFile_80115D10, 0, addrPtr[0]);
    alBnkfNew(ALBankFile_80115D10, get_rom_offset_of_asset(ASSET_AUDIO, addrPtr[0]));
    ALSeqFile_80115CF8 = (ALSeqFile *) alHeapDBAlloc(0, 0, &gALHeap, 1, 4);
    load_asset_to_address(ASSET_AUDIO, (u32) ALSeqFile_80115CF8, addrPtr[4], 4);

    seqfSize = (ALSeqFile_80115CF8->seqCount) * 8 + 4;
    ALSeqFile_80115CF8 = allocate_from_main_pool_safe(seqfSize, COLOUR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, (u32) ALSeqFile_80115CF8, addrPtr[4], seqfSize);
    alSeqFileNew(ALSeqFile_80115CF8, get_rom_offset_of_asset(ASSET_AUDIO, addrPtr[4]));
    D_80115D0C = (u32 *) allocate_from_main_pool_safe((ALSeqFile_80115CF8->seqCount) * 4, COLOUR_TAG_CYAN);

    for (iCnt = 0; iCnt < ALSeqFile_80115CF8->seqCount; iCnt++) {
        D_80115D0C[iCnt] = ALSeqFile_80115CF8->seqArray[iCnt].len;
        if (D_80115D0C[iCnt] & 1) {
            D_80115D0C[iCnt]++;
        }
        if (seq_max_len < D_80115D0C[iCnt]) {
            seq_max_len = D_80115D0C[iCnt];
        }
    }

    synth_config.maxVVoices = 40;
    synth_config.maxPVoices = 40;
    synth_config.maxUpdates = 96;
    synth_config.dmaproc = NULL;
    synth_config.fxType[0] = 6;
    synth_config.fxType[1] = 2;
    synth_config.outputRate = 0;
    synth_config.heap = &gALHeap;
    if (gExpansionPak) {
        audioNewThread8MB(&synth_config, 12, sc);
    } else {
        audioNewThread(&synth_config, 12, sc);
    }
    gMusicPlayer = func_80002224(24, 120);
    set_voice_limit(gMusicPlayer, 18);
    gSndFxPlayer = func_80002224(16, 50);
    D_80115CFC = allocate_from_main_pool_safe(seq_max_len, COLOUR_TAG_CYAN);
    D_80115D00 = allocate_from_main_pool_safe(seq_max_len, COLOUR_TAG_CYAN);
    audConfig.unk04 = 150;
    audConfig.unk00 = 32;
    audConfig.maxChannels = 16;
    audConfig.unk10 = 1;
    audConfig.hp = &gALHeap;
    alSndPNew(&audConfig);
    audioStartThread();
    func_80000968(0);
    free_from_memory_pool(addrPtr);
    set_sound_channel_count(10);
    D_800DC648 = 0;
    D_80115D40 = 0;
    D_80115D41 = 0;
    D_800DC658 = 0;
    D_80115F78 = 0;
    D_80115F79 = 0;
    return;
}

void func_80000890(u8 arg0) {
    if (!D_80115F79) {
        D_80115F78 = arg0;
        if (D_80115F78 == 0) {
            sMusicVolumeMultiplier = 256;
            set_relative_volume_for_music(musicRelativeVolume);
            func_80004A60(0, sMusicVolumeMultiplier * 128 - 1);
            func_80004A60(1, sMusicVolumeMultiplier * 128 - 1);
            func_80004A60(2, sMusicVolumeMultiplier * 128 - 1);
            func_80004A60(4, sMusicVolumeMultiplier * 128 - 1);
        }
    }
}

void func_80000968(s32 arg0) {
    switch (arg0) {
        case 1:
            func_80004A60(0, 0);
            func_80004A60(1, 32767);
            func_80004A60(2, 0);
            func_80004A60(4, 0);
            alCSPSetVol((ALCSPlayer *) gMusicPlayer, (s16) (musicRelativeVolume * musicVolumeSliderPercentage >> 2));
            alCSPSetVol((ALCSPlayer *) gSndFxPlayer, 0);
            break;
        case 2:
            func_80004A60(0, 0);
            func_80004A60(1, 32767);
            func_80004A60(2, 32767);
            func_80004A60(4, 32767);
            break;
        case 3:
            func_80004A60(0, 0);
            func_80004A60(1, 32767);
            func_80004A60(2, 0);
            func_80004A60(4, 0);
            break;
        default:
            func_80004A60(0, 32767);
            func_80004A60(1, 32767);
            func_80004A60(2, 32767);
            func_80004A60(4, 32767);
            alCSPSetVol((ALCSPlayer *) gMusicPlayer, (s16) (musicRelativeVolume * musicVolumeSliderPercentage));
            alCSPSetVol((ALCSPlayer *) gSndFxPlayer, (s16) (sfxGetVolumeSlider() * sfxRelativeVolume));
            break;
    }
    D_80115F79 = arg0;
}

void func_80000B18(void) {
    D_800DC648 = 1;
}

void func_80000B28(void) {
    D_800DC648 = 0;
}

void play_music(u8 seqID) {
    if (D_800DC648 == 0 && musicVolumeSliderPercentage != 0) {
        D_80115D04 = seqID;
        musicRelativeVolume = 127;
        if (D_800DC640 != 0) {
            func_800022BC(D_80115D04, gMusicPlayer);
        }
        musicTempo = alCSPGetTempo((ALCSPlayer *) gMusicPlayer);
        audioPrevCount = osGetCount();
        D_80115D40 = 1;
        D_80115F7C = -1;
    }
}

void set_music_player_voice_limit(u8 voiceLimit) {
    if (D_800DC670 == 0) {
        set_voice_limit(gMusicPlayer, voiceLimit);
    }
}

void func_80000C1C(void) {
    D_800DC670 = 1;
}

void func_80000C2C(void) {
    D_800DC670 = 0;
}

void set_sndfx_player_voice_limit(u8 voiceLimit) {
    set_voice_limit(gSndFxPlayer, voiceLimit);
}

/* Unused? */
void func_80000C68(u8 arg0) {
    func_80063A90(gMusicPlayer, arg0);
}

/**
 * Enables the timer to start fading in or out the background music.
 * Give it a positive number to fade in, otherwise, give it a negative one to fade out.
 */
void set_music_fade_timer(s32 time) {
    sMusicDelayTimer = 0;
    sMusicDelayLength = (time * 60) >> 8;
}

void func_80000CBC(void) {
    sMusicDelayTimer = 0;
    sMusicDelayLength = 0;
    sMusicFadeVolume = 1.0f;
    set_relative_volume_for_music(musicRelativeVolume);
}

void handle_music_fade(u8 updateRate) {
    s32 reg_s2;
    s32 j;
    if (sMusicDelayLength > 0) {

        sMusicDelayTimer += updateRate;
        sMusicFadeVolume = ((f32)sMusicDelayTimer) / ((f32)sMusicDelayLength);

        if (sMusicFadeVolume > 1.0f) {
            sMusicDelayTimer = 0;
            sMusicDelayLength = 0;
            sMusicFadeVolume = 1.0f;
        }
        set_relative_volume_for_music(musicRelativeVolume);
    } else if (sMusicDelayLength < 0) {

        sMusicDelayTimer -= updateRate;
        sMusicFadeVolume = 1.0f - ((f32)sMusicDelayTimer) / ((f32)sMusicDelayLength);
        if (sMusicFadeVolume < 0.0f) {
            sMusicDelayTimer = 0;
            sMusicDelayLength = 0;
            sMusicFadeVolume = 0.0f;
        }
        set_relative_volume_for_music(musicRelativeVolume);
    }

    if (D_800DC658 > 0) {
        for (reg_s2 = 0; reg_s2 < D_800DC658;) {
            D_80115D48[reg_s2].unk2 -= updateRate;
            if (D_80115D48[reg_s2].unk2 <= 0) {
                j = reg_s2;
                play_sound_global(D_80115D48[reg_s2].unk0, (s32 *) D_80115D48[reg_s2].unk4);

                D_800DC658 -= 1;
                while (j < D_800DC658) {
                    D_80115D48[reg_s2].unk0 = D_80115D48[reg_s2 + 1].unk0;
                    D_80115D48[reg_s2].unk2 = D_80115D48[reg_s2 + 1].unk2;
                    D_80115D48[reg_s2].unk4 = D_80115D48[reg_s2 + 1].unk4;
                    j++;
                }
                j++;
            } else {
                reg_s2++;
            }
        }
    }

    func_8000232C(gMusicPlayer, D_80115CFC, &D_800DC65C, &D_80115D88);
    func_8000232C(gSndFxPlayer, D_80115D00, &D_800DC660, &D_80115E80);
    if (sMusicTempo == -1 && gMusicPlayer->target) {
        sMusicTempo = 60000000 / alCSPGetTempo((ALCSPlayer *) gMusicPlayer);
    }
}

void func_80000FDC(u16 arg0, s32 arg1, f32 arg2) {
    if (D_800DC658 < 8) {
        D_80115D48[D_800DC658].unk0 = arg0;
        D_80115D48[D_800DC658].unk4 = arg1;
        D_80115D48[D_800DC658].unk2 = arg2 * 60.0f;
        D_800DC658++;
    }
}

void func_80001050(void) {
    D_800DC658 = 0;
}

u16 musicGetChanMask(void) {
    return gMusicPlayer->chanMask;
}

void func_80001074(u16 arg0) {
    u32 chan;
    if (D_800DC65C) {
        D_80115F7C = arg0;
    } else {
        gMusicPlayer->chanMask = arg0;
        for (chan = 0; chan != 16; chan++) {
            if (arg0 & (1 << chan)) {
                func_80001170(chan);
            } else {
                func_80001114(chan);
            }
        }
    }
    return;
}

void func_80001114(u8 chan) {
    if (chan < 16) {
        func_80063AF0(gMusicPlayer, chan);
    }
}

s32 musicGetChnlActive(s32 arg0) {
    return (gMusicPlayer->chanMask & (1 << arg0)) == 0;
}

void func_80001170(u8 chan) {
    if (chan < 16) {
        func_80063B44(gMusicPlayer, chan);
    }
}

void musicSetChlPan(u8 chan, ALPan pan) {
    if (chan < 16) {
        alCSPSetChlPan((ALCSPlayer *) gMusicPlayer, chan, pan);
    }
}

void musicSetChlVol(u8 chan, u8 vol) {
    if (chan < 0x10) {
        alCSPSetChlVol((ALCSPlayer *) gMusicPlayer, chan, vol);
    }
}

/* Unused?*/
u8 musicGetChlVol(u8 chan) {
    if (chan >= 16) {
        return 0;
    } else {
        return alCSPGetChlVol((ALCSPlayer *) gMusicPlayer, chan);
    }
}

void func_80001268(u8 chan, ALPan pan) {
    if (chan < 16) {
        func_80063BA0(gMusicPlayer, chan, pan);
    }
}

u8 func_800012A8(u8 chan) {
    if (chan >= 16) {
        return 0;
    }
    return func_80063C00((ALCSPlayer *) gMusicPlayer, chan);
}

void func_800012E8(void) {
    u32 chan;
    if (!D_800DC648) {
        for (chan = 0; chan < 16; chan++) {
            func_80001170(chan);
            func_80001268(chan, 127);
            musicSetChlVol(chan, 127);
        }
    }
    return;
}

u8 func_80001358(u8 arg0, u8 arg1, s32 arg2) {
    u8 val_1f;
    u8 val_1e;
    s32 updatedVol;

    //u8 fadeIn_chan = arg0;
    if (!(arg0 == 100)) {
        val_1f = arg2 + alCSPGetChlVol((ALCSPlayer *) gMusicPlayer, arg0);
        if (val_1f > 127) {
            val_1f = 127;
        }
        alCSPSetChlVol((ALCSPlayer *) gMusicPlayer, arg0, val_1f);
    }

    if (arg1 != 100) {

        updatedVol = alCSPGetChlVol((ALCSPlayer *) gMusicPlayer, arg1);
        val_1e = (updatedVol > arg2) ? updatedVol - arg2 : 0;
        alCSPSetChlVol((ALCSPlayer *) gMusicPlayer, arg1, val_1e);
        return val_1e;
    } else {
        return 127 - val_1f;
    }
}

void func_80001440(u8 *arg0) {
    s32 s0 = 0;
    if (gMusicPlayer->maxChannels > 0) {
        do {
            arg0[s0] = alSeqpGetChlFXMix(gMusicPlayer, s0);
            s0++;
        } while (s0 < gMusicPlayer->maxChannels);
    }
    return;
}

void func_800014BC(f32 arg0) {
    musicSetTempo((s32)((f32)(u32)(musicGetTempo() & 0xFF) * arg0));
}

/**
 * Set the tempo of the current playing background music.
 */
void musicSetTempo(s32 tempo) {
    if (tempo != 0) {
        f32 inv_tempo = (1.0f / tempo);
        alCSPSetTempo((ALCSPlayer *) gMusicPlayer, (s32)(inv_tempo * 60000000.0f));
        sMusicTempo = tempo;
    }
}

/**
 * Return the tempo of the current playing background music.
 */
s16 musicGetTempo(void) {
    return sMusicTempo;
}

u8 music_is_playing(void) {
    return (alCSPGetState((ALCSPlayer *) gMusicPlayer) == AL_PLAYING);
}

f32 audio_get_chr_select_anim_frac(void) {
    f32 tmp;
    u32 cnt = osGetCount();
    if ((u32) audioPrevCount < cnt) {
        D_80115D34 += (f32) (cnt - audioPrevCount) / 46875.0f;
    } else {
        D_80115D34 += (f32) ((cnt - audioPrevCount) - 1) / 46875.0f;
    }
    if (D_80115D40 == 0) {
        sMusicTempo = 182;
    }
    for (tmp = 120000.0f / (f32) sMusicTempo; tmp < D_80115D34; D_80115D34 -= tmp)
        ;
    audioPrevCount = (s32) cnt;
    return D_80115D34 / tmp;
}

void func_80001728(u8 arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    *arg1 = sMusicPool[arg0].unk1;
    *arg2 = sMusicPool[arg0].unk0;
    *arg3 = sMusicPool[arg0].unk2;
}

void func_80001784(u8 a0) {
    if (!func_80001C08()) {
        func_800022BC(D_80115D05 = a0, gSndFxPlayer);
        D_80115D41 = 1;
    }
}

void sfxSetTempo(s32 tempo) {
    f32 inv_tempo = (1.0f / tempo);
    alCSPSetTempo((ALCSPlayer *) gSndFxPlayer, (s32)(inv_tempo * 60000000.0f));
}

void func_80001844(void) {
    if (!D_800DC648) {
        func_80002570(gMusicPlayer);
    }
    return;
}

void func_80001878(u8 arg0) {
    if (arg0 != D_800DC640) {
        D_800DC640 = arg0;
        if (arg0) {
            play_music(D_80115D04);
        } else {
            func_80001844();
        }
    }
}

u8 func_800018D0(void) {
    return D_800DC640;
}

void func_800018E0(void) {
    if (func_80001C08() == 0) {
        D_80115D05 = 0;
        func_80002570(gSndFxPlayer);
    }
}

u8 func_80001918(void) {
    if (D_80115D04 != 0 && gMusicPlayer->state == AL_PLAYING) {
        return D_80115D04;
    }
    return 0;
}

// Unused?
u8 func_80001954(void) {
    if (D_800DC65C != 0) {
        return D_800DC65C;
    }
    return D_80115D04;
}

u8 func_80001980(void) {
    return D_80115D05;
}

void set_relative_volume_for_music(u8 vol) {
    f32 normalized_vol;

    musicRelativeVolume = vol;
    normalized_vol = musicVolumeSliderPercentage * musicRelativeVolume * sMusicFadeVolume;
    alCSPSetVol((ALCSPlayer *) gMusicPlayer, (s16)((s32)(sMusicVolumeMultiplier * normalized_vol) >> 8));
}

void set_music_volume_slider(u32 slider_val) {
    f32 normalized_vol;

    slider_val = (slider_val <= 256) ? slider_val : 256;
    musicVolumeSliderPercentage = slider_val;
    normalized_vol = musicVolumeSliderPercentage * musicRelativeVolume * sMusicFadeVolume;
    alCSPSetVol((ALCSPlayer *) gMusicPlayer, (s16)((s32)(sMusicVolumeMultiplier * normalized_vol) >> 8));
}

u8 musicGetRelativeVolume(void) {
    return musicRelativeVolume;
}

s32 musicGetVolSliderPercentage(void) {
    return musicVolumeSliderPercentage;
}

void sfxSetRelativeVolume(u8 arg0) {
    sfxRelativeVolume = arg0;
    alCSPSetVol((ALCSPlayer *) gSndFxPlayer, (s16)(sfxGetVolumeSlider() * sfxRelativeVolume));
}

void sfxSetPan(ALPan pan) {
    u32 iChan;
    for (iChan = 0; iChan < 16; iChan++) {
        alCSPSetChlPan((ALCSPlayer *) gSndFxPlayer, iChan, pan);
    }
    return;
}

/**
 * Plays a sequence just once, allowing it to coexist with the music if necessary.
 * Examples include getting silver coins, challenge keys, or getting the locked message.
 */
void play_sequence(u8 seqID) {
    D_800DC644 = 1;
    func_800022BC(D_80115D05 = seqID, gSndFxPlayer);
}

u32 func_80001C08(void) {
    if (D_80115D05 && D_800DC644 && (gSndFxPlayer->state == AL_PLAYING)) {
        return D_80115D05;
    }
    D_800DC644 = 0;
    return 0;
}

void func_80001C5C(u16 arg0) {
    u32 s0;
    for (s0 = 0; s0 < 64; s0++) {
        func_80004A60(s0, arg0 << 8);
    }
}

u16 func_80001CB8(u16 arg0) {
    if (D_80115D20 < arg0) {
        return 0;
    }
    return sSoundEffectsPool[arg0].unk6;
}

/**
 * Add the requested sound to the queue and update the mask to show that this sound is playing at that source.
 * If no soundmask is provided, then instead use the global mask.
*/
void play_sound_global(u16 soundID, s32 *soundMask) {
    f32 volumeF;
    s32 soundBite;

    if (D_80115D20 < soundID) {
        if (soundMask != NULL) {
            *soundMask = NULL;
        }
    } else {
        soundBite = sSoundEffectsPool[soundID].unk0;
        if (soundBite == NULL) {
            if (soundMask != NULL) {
                *soundMask = NULL;
            }
        } else {
            volumeF = sSoundEffectsPool[soundID].unk4 / 100.0f;
            if (soundMask != NULL) {
                func_80004668(ALBankFile_80115D14->bankArray[0], soundBite, sSoundEffectsPool[soundID].unk8, (s32) soundMask);
                if (*soundMask != NULL) {
                    func_800049F8(*soundMask, 8, sSoundEffectsPool[soundID].unk2 * 256);
                    func_800049F8(*soundMask, 16, *((u32*) &volumeF));
                }
            } else {
                soundMask = (s32 *) &gGlobalSoundMask;
                func_80004668(ALBankFile_80115D14->bankArray[0], soundBite, sSoundEffectsPool[soundID].unk8, (s32) &gGlobalSoundMask);
                if (*soundMask != NULL) {
                    func_800049F8(*soundMask, 8, sSoundEffectsPool[soundID].unk2 * 256);
                    func_800049F8(*soundMask, 16, *((u32*) &volumeF));
                }
            }
        }
    }
}

/**
 * Creates a spatial audio reference, then plays a sound.
 * This then makes the audio pan around in 3D space.
 * If it is not given a mask, then it will use the global mask.
 */
void play_sound_spatial(u16 soundID, f32 x, f32 y, f32 z, s32 **soundMask) {
    if (soundMask == NULL) {
        soundMask = (s32 **) &gSpatialSoundMask;
    }

    play_sound_global(soundID, (s32 *) soundMask);

    if (*soundMask != NULL) {
        func_80009B7C(*soundMask, x, y, z);
    }
}

void func_80001F14(u16 soundID, s32 *arg1) {
    if (soundID <= 0 || ALBankFile_80115D14_GetSoundCount() < soundID) {
        if (arg1) {
            *arg1 = 0;
        }
    } else {
        if (arg1) {
            func_80004638(ALBankFile_80115D14->bankArray[0], (s16) soundID, (s32) arg1);
        } else {
            func_80004638(ALBankFile_80115D14->bankArray[0], (s16) soundID, (s32) &D_80115F88);
        }
    }
}

void func_80001FB8(u16 soundID, void *soundState, u8 volume) {
    s32 new_var = ((s32) (sSoundEffectsPool[soundID].unk2 * (volume / 127.0f))) * 256;
    if (soundState) {
        func_800049F8((s32) soundState, 8, new_var);
    }
}

u16 ALBankFile_80115D14_GetSoundCount(void) {
    return ALBankFile_80115D14->bankArray[0]->instArray[0]->soundCount;
}

u8 ALSeqFile_80115CF8_GetSeqCount(void) {
    return ALSeqFile_80115CF8->seqCount;
}

void func_80002128(unk80115D18 **arg0, s32 *arg1, s32 *arg2) {
    if (arg0 != NULL) {
        *arg0 = sSoundEffectsPool;
    }
    if (arg1 != NULL) {
        *arg1 = sSoundEffectsPoolSize;
    }
    if (arg2 != NULL) {
        *arg2 = D_80115D20;
    }
}

/* Unused? */
void func_8000216C(unk80115D1C **arg0, s32 *arg1, s32 *arg2) {
    if (arg0 != NULL) {
        *arg0 = sMusicPool;
    }
    if (arg1 != NULL) {
        *arg1 = sMusicPoolSize;
    }
    if (arg2 != NULL) {
        *arg2 = D_80115D24;
    }
}

u8 ALBankFile_80115D14_GetSoundDecayTime(u16 soundID) {
    if (soundID <= 0 || ALBankFile_80115D14->bankArray[0]->instArray[0]->soundCount < soundID) {
        return 0;
    }
    return ((u32)(1 + ALBankFile_80115D14->bankArray[0]->instArray[0]->soundArray[soundID - 1]->envelope->decayTime) == 0);
}

ALSeqPlayer *func_80002224(s32 _max_voices, s32 _max_events) {
    ALCSPlayer *cseqp;
    ALSeqpConfig config;

    config.maxVoices = _max_voices;
    config.maxEvents = _max_events;
    config.unknown_0x10 = _max_voices; //this member doesn't exist in other versions of ALSeqpConfig
    config.maxChannels = 16;
    config.heap = &gALHeap;
    config.initOsc = NULL;
    config.updateOsc = NULL;
    config.stopOsc = NULL;

    cseqp = (ALCSPlayer *)alHeapDBAlloc(NULL, 0, &gALHeap, 1, sizeof(ALCSPlayer));
    alCSPNew(cseqp, &config);
    alCSPSetBank(cseqp, ALBankFile_80115D10->bankArray[0]);
    cseqp->unk36 = 0x7F;

    return (ALSeqPlayer *) cseqp;
}

void func_800022BC(u8 arg0, ALSeqPlayer *arg1) {
    func_80002570(arg1);
    if (arg0 < ALSeqFile_80115CF8->seqCount) {
        if (arg1 == gMusicPlayer) {
            D_800DC65C = arg0;
            return;
        }
        D_800DC660 = arg0;
    }
}

void func_8000232C(ALSeqPlayer *arg0, void *arg1, u8 *arg2, ALCSeq *arg3) {
    s32 var_s0;
    u8 temp_a0;
    u8 temp_a0_2;

    if ((alCSPGetState((ALCSPlayer* ) arg0) == 0) && (*arg2 != 0)) {
        load_asset_to_address(ASSET_AUDIO, (u32) arg1, ALSeqFile_80115CF8->seqArray[*arg2].offset - get_rom_offset_of_asset(ASSET_AUDIO, 0), (s32) D_80115D0C[*arg2]);
        alCSeqNew(arg3, arg1);
        alCSPSetSeq((ALCSPlayer* ) arg0, arg3);
        alCSPPlay((ALCSPlayer* ) arg0);
        if (arg0 == gMusicPlayer) {
            set_relative_volume_for_music(sMusicPool[*arg2].unk0);
            temp_a0 = sMusicPool[*arg2].unk1;
            if (temp_a0 != 0) {
                musicSetTempo((s32) temp_a0);
            } else {
                sMusicTempo = -1;
            }
            func_80002608(sMusicPool[*arg2].unk2);
            D_80115D04 = *arg2;
            var_s0 = 0;
            if (D_80115F7C != -1) {
                do {
                    if ((1 << var_s0) & D_80115F7C) {
                        func_80001170(var_s0);
                    } else {
                        func_80001114(var_s0);
                    }
                    var_s0 += 1;
                } while (var_s0 != 0x10);
            }
        } else {
            sfxSetRelativeVolume(sMusicPool[*arg2].unk0);
            temp_a0_2 = sMusicPool[*arg2].unk1;
            if (temp_a0_2 != 0) {
                sfxSetTempo(temp_a0_2);
            }
            D_80115D05 = *arg2;
        }
        *arg2 = 0;
    }
}

void func_80002570(ALSeqPlayer *seqp) {
    if (gMusicPlayer == seqp && D_80115D40 != 0) {
        alCSPStop((ALCSPlayer *) seqp);
        D_80115D40 = 0;
        D_80115D04 = 0;
        D_800DC65C = 0;
    } else if (gSndFxPlayer == seqp && D_80115D41 != 0) {
        alCSPStop((ALCSPlayer *) seqp);
        D_80115D41 = 0;
        D_800DC660 = 0;
    }
    return;
}

void func_80002608(u8 arg0) {
    func_8006492C(arg0);
}

u8 func_80002630(void) {
    return sMusicPool[D_80115D04].unk2;
}
