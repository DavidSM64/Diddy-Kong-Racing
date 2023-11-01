/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80000450 */

#include "audio.h"
#include "memory.h"

#include "types.h"
#include "macros.h"
#include "asset_enums.h"
#include "asset_loading.h"
#include "audio_internal.h"
#include "audiomgr.h"
#include "audiosfx.h"
#include "sched.h"
#include "lib/src/mips1/al/unknown_0646F0.h"

/************ .data ************/

ALSeqPlayer *gMusicPlayer = NULL;
ALSeqPlayer *gSndFxPlayer = NULL;
u8 musicRelativeVolume = 127;
u8 sfxRelativeVolume = 127;
u8 gCanPlayMusic = TRUE;
u8 gCanPlayJingle = FALSE;
s32 D_800DC648 = FALSE;
s32 audioPrevCount = 0;
f32 sMusicFadeVolume = 1.0f;
s32 musicVolumeSliderPercentage = 256;
s32 D_800DC658 = 0;
u8 gMusicSetChannelMask = FALSE;
u8 gSoundSetChannelMask = FALSE;
UNUSED s32 D_800DC664 = 0;
UNUSED s32 D_800DC668 = 0;
s32 sMusicVolumeMultiplier = 256; // This is never not 256...
u8 D_800DC670 = 0;

/*******************************/

/************ .bss ************/

#define AUDIO_HEAP_SIZE 0x29D88

// The audio heap is located at the start of the BSS section.
u8 gBssSectionStart[AUDIO_HEAP_SIZE];

ALHeap gALHeap;
ALSeqFile *gSequenceTable;
void *gMusicSequenceData;

void *gJingleSequenceData;
u8 gCurrentSequenceID;
u8 gCurrentJingleID;
s32 musicTempo;
u32 *gSeqLengthTable;
ALBankFile *ALBankFile_80115D10; // And I have reason to believe these are voice clips.
ALBankFile *gSoundEffectsTable; // These are sound effects, I do not know if it is ALL the sound effects.

SoundData *sSoundEffectsPool;
unk80115D1C *sMusicPool;

s32 gSoundEffectCount;
s32 sMusicPoolCount;
u32 gSoundTableSize;
u32 sMusicPoolSize;
s16 sMusicTempo;
f32 gMusicAnimationTick;
s32 sMusicDelayTimer;
s32 sMusicDelayLength;
u8 gMusicPlaying;
u8 gJinglePlaying;
unk80115D48 D_80115D48[8];
ALCSeq gMusicSequence;
ALCSeq gJingleSequence;
u8 gSkipResetChannels; // Stored and used by a single function, but redundant.
u8 gAudioVolumeSetting;
s32 gDynamicMusicChannelMask;
SoundMask *gGlobalSoundMask;
SoundMask *gSpatialSoundMask;
SoundMask *gRacerSoundMask;

/******************************/

/**
 * Allocate memory for all of the audio systems, including sequence data, sound data and heaps.
 * Afterwards, set up the audio thread and start it.
*/
void audio_init(OSSched *sc) {
    s32 iCnt;
    ALSynConfig synth_config;
    s32 *addrPtr;
    u32 seqfSize;
    u32 seqLength;
    UNUSED u32 pad;
    audioMgrConfig audConfig;

    seqLength = 0;
    alHeapInit(&gALHeap, gBssSectionStart, sizeof(gBssSectionStart));

    addrPtr = (s32 *) load_asset_section_from_rom(ASSET_AUDIO_TABLE);
    gSoundEffectsTable = (ALBankFile *) allocate_from_main_pool_safe(addrPtr[ASSET_AUDIO_2] - addrPtr[ASSET_AUDIO_1], COLOUR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, (u32) gSoundEffectsTable, addrPtr[ASSET_AUDIO_1], addrPtr[ASSET_AUDIO_2] - addrPtr[ASSET_AUDIO_1]);
    alBnkfNew(gSoundEffectsTable, get_rom_offset_of_asset(ASSET_AUDIO, addrPtr[ASSET_AUDIO_2]));

    gSoundTableSize = addrPtr[ASSET_AUDIO_7] - addrPtr[ASSET_AUDIO_6];
    sSoundEffectsPool = (SoundData *) allocate_from_main_pool_safe(gSoundTableSize, COLOUR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, (u32) sSoundEffectsPool, addrPtr[ASSET_AUDIO_6], gSoundTableSize);
    gSoundEffectCount = gSoundTableSize / sizeof(SoundData);

    sMusicPoolSize = addrPtr[ASSET_AUDIO_6] - addrPtr[ASSET_AUDIO_5];
    sMusicPool = (unk80115D1C *) allocate_from_main_pool_safe(sMusicPoolSize, COLOUR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, (u32) sMusicPool, addrPtr[ASSET_AUDIO_5], sMusicPoolSize);
    sMusicPoolCount = sMusicPoolSize / sizeof(unk80115D1C);

    ALBankFile_80115D10 = (ALBankFile *) allocate_from_main_pool_safe(addrPtr[ASSET_AUDIO_0], COLOUR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, (u32) ALBankFile_80115D10, 0, addrPtr[ASSET_AUDIO_0]);
    alBnkfNew(ALBankFile_80115D10, get_rom_offset_of_asset(ASSET_AUDIO, addrPtr[ASSET_AUDIO_0]));
    gSequenceTable = (ALSeqFile *) alHeapAlloc(&gALHeap, 1, 4);
    load_asset_to_address(ASSET_AUDIO, (u32) gSequenceTable, addrPtr[ASSET_AUDIO_4], 4);

    seqfSize = (gSequenceTable->seqCount) * 8 + 4;
    gSequenceTable = allocate_from_main_pool_safe(seqfSize, COLOUR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, (u32) gSequenceTable, addrPtr[ASSET_AUDIO_4], seqfSize);
    alSeqFileNew(gSequenceTable, get_rom_offset_of_asset(ASSET_AUDIO, addrPtr[ASSET_AUDIO_4]));
    gSeqLengthTable = (u32 *) allocate_from_main_pool_safe((gSequenceTable->seqCount) * 4, COLOUR_TAG_CYAN);

    for (iCnt = 0; iCnt < gSequenceTable->seqCount; iCnt++) {
        pad = (u32) (gSequenceTable + 8 + iCnt * 8); // Fakematch
        gSeqLengthTable[iCnt] = gSequenceTable->seqArray[iCnt].len;
        if (gSeqLengthTable[iCnt] & 1) {
            gSeqLengthTable[iCnt]++;
        }
        if (seqLength < gSeqLengthTable[iCnt]) {
            seqLength = gSeqLengthTable[iCnt];
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
    amCreateAudioMgr(&synth_config, 12, sc);
    gMusicPlayer = sound_seqplayer_init(24, 120);
    set_voice_limit(gMusicPlayer, 18);
    gSndFxPlayer = sound_seqplayer_init(16, 50);
    gMusicSequenceData = allocate_from_main_pool_safe(seqLength, COLOUR_TAG_CYAN);
    gJingleSequenceData = allocate_from_main_pool_safe(seqLength, COLOUR_TAG_CYAN);
    audConfig.unk04 = 150;
    audConfig.unk00 = 32;
    audConfig.maxChannels = AUDIO_CHANNELS;
    audConfig.unk10 = 1;
    audConfig.hp = &gALHeap;
    alSndPNew(&audConfig);
    audioStartThread();
    adjust_audio_volume(VOLUME_NORMAL);
    free_from_memory_pool(addrPtr);
    set_sound_channel_count(10);
    D_800DC648 = FALSE;
    gMusicPlaying = FALSE;
    gJinglePlaying = FALSE;
    D_800DC658 = 0;
    gSkipResetChannels = FALSE;
    gAudioVolumeSetting = VOLUME_NORMAL;
#ifdef AVOID_UB
    gMusicAnimationTick = 1.0f; // Prevents a denorm crash on the character select screen.
#endif
}

/**
 * Depending on whether or not the audio volume is set to normal and the argument is false, reset sound effect channel volumes.
*/
void reset_sound_volume(u8 skipReset) {
    if (gAudioVolumeSetting == VOLUME_NORMAL) {
        gSkipResetChannels = skipReset;
        if (gSkipResetChannels == FALSE) {
            sMusicVolumeMultiplier = 256;
            set_relative_volume_for_music(musicRelativeVolume);
            set_sound_channel_volume(0, sMusicVolumeMultiplier * 128 - 1);
            set_sound_channel_volume(1, sMusicVolumeMultiplier * 128 - 1);
            set_sound_channel_volume(2, sMusicVolumeMultiplier * 128 - 1);
            set_sound_channel_volume(4, sMusicVolumeMultiplier * 128 - 1);
        }
    }
}

/**
 * Changes the volume of each sound channel depending on what value is passed through.
*/
void adjust_audio_volume(s32 behaviour) {
    switch (behaviour) {
        case VOLUME_LOWER: // Mute most sound effects and half the volume of music.
            set_sound_channel_volume(0, 0);
            set_sound_channel_volume(1, 32767);
            set_sound_channel_volume(2, 0);
            set_sound_channel_volume(4, 0);
            alCSPSetVol((ALCSPlayer *) gMusicPlayer, (s16) (musicRelativeVolume * musicVolumeSliderPercentage >> 2));
            alCSPSetVol((ALCSPlayer *) gSndFxPlayer, 0);
            break;
        case VOLUME_LOWER_AMBIENT: // Mute the ambient channel, making course elements stop making noise.
            set_sound_channel_volume(0, 0);
            set_sound_channel_volume(1, 32767);
            set_sound_channel_volume(2, 32767);
            set_sound_channel_volume(4, 32767);
            break;
        case VOLUME_UNK03:
            set_sound_channel_volume(0, 0);
            set_sound_channel_volume(1, 32767);
            set_sound_channel_volume(2, 0);
            set_sound_channel_volume(4, 0);
            break;
        default: // Restore sound back to normal.
            set_sound_channel_volume(0, 32767);
            set_sound_channel_volume(1, 32767);
            set_sound_channel_volume(2, 32767);
            set_sound_channel_volume(4, 32767);
            alCSPSetVol((ALCSPlayer *) gMusicPlayer, (s16) (musicRelativeVolume * musicVolumeSliderPercentage));
            alCSPSetVol((ALCSPlayer *) gSndFxPlayer, (s16) (get_sfx_volume_slider() * sfxRelativeVolume));
            break;
    }
    gAudioVolumeSetting = behaviour;
}

void func_80000B18(void) {
    D_800DC648 = TRUE;
}

void func_80000B28(void) {
    D_800DC648 = FALSE;
}

void play_music(u8 seqID) {
    if (D_800DC648 == FALSE && musicVolumeSliderPercentage != 0) {
        gCurrentSequenceID = seqID;
        musicRelativeVolume = 127;
        if (gCanPlayMusic) {
            music_sequence_start(gCurrentSequenceID, gMusicPlayer);
        }
        musicTempo = alCSPGetTempo((ALCSPlayer *) gMusicPlayer);
        audioPrevCount = osGetCount();
        gMusicPlaying = TRUE;
        gDynamicMusicChannelMask = -1;
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

UNUSED void func_80000C68(u8 arg0) {
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

        if (sMusicFadeVolume > 1.0) {
            sMusicDelayTimer = 0;
            sMusicDelayLength = 0;
            sMusicFadeVolume = 1.0f;
        }
        set_relative_volume_for_music(musicRelativeVolume);
    } else if (sMusicDelayLength < 0) {

        sMusicDelayTimer -= updateRate;
        sMusicFadeVolume = 1.0f - ((f32)sMusicDelayTimer) / ((f32)sMusicDelayLength);
        if (sMusicFadeVolume < 0.0) {
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
                play_sound_global(D_80115D48[reg_s2].soundId, (s32 *) D_80115D48[reg_s2].unk4);

                D_800DC658 -= 1;
                while (j < D_800DC658) {
                    D_80115D48[reg_s2].soundId = D_80115D48[reg_s2 + 1].soundId;
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

    music_sequence_init(gMusicPlayer, gMusicSequenceData, &gMusicSetChannelMask, &gMusicSequence);
    music_sequence_init(gSndFxPlayer, gJingleSequenceData, &gSoundSetChannelMask, &gJingleSequence);
    if (sMusicTempo == -1 && gMusicPlayer->target) {
        sMusicTempo = 60000000 / alCSPGetTempo((ALCSPlayer *) gMusicPlayer);
    }
}

void func_80000FDC(u16 soundId, s32 arg1, f32 arg2) {
    if (D_800DC658 < 8) {
        D_80115D48[D_800DC658].soundId = soundId;
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

void music_dynamic_reset(u16 channel) {
    u32 chan;
    if (gMusicSetChannelMask) {
        gDynamicMusicChannelMask = channel;
    } else {
        gMusicPlayer->chanMask = channel;
        for (chan = 0; chan != AUDIO_CHANNELS; chan++) {
            if (channel & (1 << chan)) {
                func_80001170(chan);
            } else {
                func_80001114(chan);
            }
        }
    }
}

void func_80001114(u8 chan) {
    if (chan < AUDIO_CHANNELS) {
        func_80063AF0(gMusicPlayer, chan);
    }
}

s32 musicGetChnlActive(s32 arg0) {
    return (gMusicPlayer->chanMask & (1 << arg0)) == 0;
}

void func_80001170(u8 chan) {
    if (chan < AUDIO_CHANNELS) {
        func_80063B44(gMusicPlayer, chan);
    }
}

void musicSetChlPan(u8 chan, ALPan pan) {
    if (chan < AUDIO_CHANNELS) {
        alCSPSetChlPan((ALCSPlayer *) gMusicPlayer, chan, pan);
    }
}

void musicSetChlVol(u8 chan, u8 vol) {
    if (chan < AUDIO_CHANNELS) {
        alCSPSetChlVol((ALCSPlayer *) gMusicPlayer, chan, vol);
    }
}

UNUSED u8 musicGetChlVol(u8 chan) {
    if (chan >= AUDIO_CHANNELS) {
        return 0;
    } else {
        return alCSPGetChlVol((ALCSPlayer *) gMusicPlayer, chan);
    }
}

void func_80001268(u8 chan, ALPan pan) {
    if (chan < AUDIO_CHANNELS) {
        func_80063BA0(gMusicPlayer, chan, pan);
    }
}

u8 func_800012A8(u8 chan) {
    if (chan >= AUDIO_CHANNELS) {
        return 0;
    }
    return func_80063C00((ALCSPlayer *) gMusicPlayer, chan);
}

void func_800012E8(void) {
    u32 chan;
    if (D_800DC648 == FALSE) {
        for (chan = 0; chan < AUDIO_CHANNELS; chan++) {
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
}

/**
 * Multiplies the current tempo of the background music.
 * Since it calls musicGetTempo and multiplies it by the result, calling this repeatedly can recursively change the music's speed.
*/
void multiply_music_tempo(f32 tempo) {
    musicSetTempo((s32)((f32)(u32)(musicGetTempo() & 0xFF) * tempo));
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

/**
 * Returns true if background music is currently playing.
*/
u8 music_is_playing(void) {
    return (alCSPGetState((ALCSPlayer *) gMusicPlayer) == AL_PLAYING);
}

/**
 * Counts up using the internal timer.
 * Loops itself round, so the final result will return 0.0f - 1.0f.
*/
f32 music_animation_fraction(void) {
    f32 tmp;
    u32 cnt = osGetCount();
    if ((u32) audioPrevCount < cnt) {
        gMusicAnimationTick += (f32) (cnt - audioPrevCount) / 46875.0f;
    } else {
        gMusicAnimationTick += (f32) ((cnt - audioPrevCount) - 1) / 46875.0f;
    }
    if (gMusicPlaying == FALSE) {
        sMusicTempo = 182;
    }
    for (tmp = 120000.0f / (f32) sMusicTempo; tmp < gMusicAnimationTick; gMusicAnimationTick -= tmp)
        ;
    audioPrevCount = (s32) cnt;
    return gMusicAnimationTick / tmp;
}

/**
 * Writes the music and sound tempo, as well as the volume to the arguments.
*/
UNUSED void sound_get_properties(u8 poolID, u8 *tempo, u8 *volume, u8 *reverb) {
    *tempo = sMusicPool[poolID].tempo;
    *volume = sMusicPool[poolID].volume;
    *reverb = sMusicPool[poolID].reverb;
}

/**
 * Play a jingle, but only if there isn't one playing already.
*/
void music_jingle_play_safe(u8 jingleID) {
    if (music_jingle_playing() == SEQUENCE_NONE) {
        music_sequence_start(gCurrentJingleID = jingleID, gSndFxPlayer);
        gJinglePlaying = TRUE;
    }
}

void sfxSetTempo(s32 tempo) {
    f32 inv_tempo = (1.0f / tempo);
    alCSPSetTempo((ALCSPlayer *) gSndFxPlayer, (s32)(inv_tempo * 60000000.0f));
}

/**
 * Stops the background music.
*/
void music_stop(void) {
    if (D_800DC648 == FALSE) {
        music_sequence_stop(gMusicPlayer);
    }
}

/**
 * Set background music to play or not.
 * If the setting changed, then either stop or start music.
*/
UNUSED void music_enabled_set(u8 setting) {
    if (setting != gCanPlayMusic) {
        gCanPlayMusic = setting;
        if (setting) {
            play_music(gCurrentSequenceID);
        } else {
            music_stop();
        }
    }
}

/**
 * Return whether background music can be played.
*/
u8 music_can_play(void) {
    return gCanPlayMusic;
}

/**
 * Stops the currently playing jingle.
*/
void music_jingle_stop(void) {
    if (music_jingle_playing() == SEQUENCE_NONE) {
        gCurrentJingleID = SEQUENCE_NONE;
        music_sequence_stop(gSndFxPlayer);
    }
}

/**
 * Return the currently playing music.
*/
u8 music_current_sequence(void) {
    if (gCurrentSequenceID != SEQUENCE_NONE && gMusicPlayer->state == AL_PLAYING) {
        return gCurrentSequenceID;
    } else {
        return SEQUENCE_NONE;
    }
}

UNUSED u8 func_80001954(void) {
    if (gMusicSetChannelMask) {
        return gMusicSetChannelMask;
    } else {
        return gCurrentSequenceID;
    }
}

/**
 * Return the currently playing jingle.
*/
u8 music_jingle_current(void) {
    return gCurrentJingleID;
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
    alCSPSetVol((ALCSPlayer *) gSndFxPlayer, (s16)(get_sfx_volume_slider() * sfxRelativeVolume));
}

void sfxSetPan(ALPan pan) {
    u32 iChan;
    for (iChan = 0; iChan < AUDIO_CHANNELS; iChan++) {
        alCSPSetChlPan((ALCSPlayer *) gSndFxPlayer, iChan, pan);
    }
}

/**
 * Plays a sequence just once, allowing it to coexist with the music if necessary.
 * Examples include getting silver coins, challenge keys, or getting the locked message.
 */
void music_jingle_play(u8 seqID) {
    gCanPlayJingle = TRUE;
    music_sequence_start(gCurrentJingleID = seqID, gSndFxPlayer);
}

/**
 * If there's a jingle playing, return that, otherwise, return 0.
*/
u32 music_jingle_playing(void) {
    if (gCurrentJingleID && gCanPlayJingle && (gSndFxPlayer->state == AL_PLAYING)) {
        return gCurrentJingleID;
    }
    gCanPlayJingle = FALSE;
    return SEQUENCE_NONE;
}

/**
 * Sets the volume of what I presume is all sound channels
*/
UNUSED void set_all_channel_volume(u16 volume) {
    u32 i;
    for (i = 0; i < 64; i++) {
        set_sound_channel_volume(i, volume << 8);
    }
}

/**
 * Return the audible distance of the sound effect.
*/
u16 sound_distance(u16 soundId) {
    if (soundId > gSoundEffectCount) {
        return 0;
    }
    return sSoundEffectsPool[soundId].distance;
}

/**
 * Add the requested sound to the queue and update the mask to show that this sound is playing at that source.
 * If no soundmask is provided, then instead use the global mask.
*/
void play_sound_global(u16 soundID, s32 *soundMask) {
    f32 pitch;
    s32 soundBite;

    if (soundID > gSoundEffectCount) {
        if (soundMask != NULL) {
            *soundMask = NULL;
        }
        stubbed_printf("amSndPlay: Illegal sound effects table index\n");
        return;
    }
    soundBite = sSoundEffectsPool[soundID].soundBite;
    if (soundBite == NULL) {
        if (soundMask != NULL) {
            *soundMask = NULL;
        }
        stubbed_printf("amSndPlayDirect: Somebody tried to play illegal sound %d\n", soundID);
        return;
    }
    pitch = sSoundEffectsPool[soundID].pitch / 100.0f;
    if (soundMask != NULL) {
        func_80004668(gSoundEffectsTable->bankArray[0], soundBite, sSoundEffectsPool[soundID].unk8, (s32) soundMask);
        if (*soundMask != NULL) {
            sound_event_update(*soundMask, AL_SNDP_VOL_EVT, sSoundEffectsPool[soundID].volume * 256);
            sound_event_update(*soundMask, AL_SNDP_PITCH_EVT, *((u32*) &pitch));
        }
    } else {
        soundMask = (s32 *) &gGlobalSoundMask;
        func_80004668(gSoundEffectsTable->bankArray[0], soundBite, sSoundEffectsPool[soundID].unk8, (s32) &gGlobalSoundMask);
        if (*soundMask != NULL) {
            sound_event_update(*soundMask, AL_SNDP_VOL_EVT, sSoundEffectsPool[soundID].volume * 256);
            sound_event_update(*soundMask, AL_SNDP_PITCH_EVT, *((u32*) &pitch));
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

void func_80001F14(u16 soundID, s32 *soundMask) {
    if (soundID <= 0 || sound_count() < soundID) {
        if (soundMask) {
            *soundMask = NULL;
        }
        return;
    }
    if (soundMask) {
        func_80004638(gSoundEffectsTable->bankArray[0], (s16) soundID, soundMask);
    } else {
        func_80004638(gSoundEffectsTable->bankArray[0], (s16) soundID, &gRacerSoundMask);
    }
}

void func_80001FB8(u16 soundID, void *soundState, u8 volume) {
    s32 new_var = ((s32) (sSoundEffectsPool[soundID].volume * (volume / 127.0f))) * 256;
    if (soundState) {
        sound_event_update((s32) soundState, AL_SNDP_VOL_EVT, new_var);
    }
}

UNUSED void func_8000208C(void *sndState, u8 arg1) {
    if (sndState != NULL) {
        sound_event_update((s32) sndState, AL_SNDP_VOL_EVT, arg1 << 8);
    }
}

UNUSED void amSndSetPitchDirect(void *sndState, u32 arg1) {
    u32 *temp = &arg1;
    if (sndState != NULL) {
        sound_event_update((s32) sndState, AL_SNDP_PITCH_EVT, *temp);
    }
}

/**
 * Return the number of playable sounds in the audio table.
*/
u16 sound_count(void) {
    return gSoundEffectsTable->bankArray[0]->instArray[0]->soundCount;
}

/**
 * Return mumber of playable sequences in the table.
*/
u8 music_sequence_count(void) {
    return gSequenceTable->seqCount;
}

/**
 * Writes the sound pool address, size and pool count into the arguments
*/
void sound_pool_properties(SoundData **pool, s32 *size, s32 *count) {
    if (pool != NULL) {
        *pool = sSoundEffectsPool;
    }
    if (size != NULL) {
        *size = gSoundTableSize;
    }
    if (count != NULL) {
        *count = gSoundEffectCount;
    }
}

/**
 * Writes the music pool address, size and pool count into the arguments
*/
UNUSED void music_pool_properties(unk80115D1C **pool, s32 *size, s32 *count) {
    if (pool != NULL) {
        *pool = sMusicPool;
    }
    if (size != NULL) {
        *size = sMusicPoolSize;
    }
    if (count != NULL) {
        *count = sMusicPoolCount;
    }
}

u8 gSoundEffectsTable_GetSoundDecayTime(u16 soundID) {
    if (soundID <= 0 || gSoundEffectsTable->bankArray[0]->instArray[0]->soundCount < soundID) {
        return 0;
    }
    return ((u32)(1 + gSoundEffectsTable->bankArray[0]->instArray[0]->soundArray[soundID - 1]->envelope->decayTime) == 0);
}

/**
 * Allocate space, then initialise a sequence player for audio playback.
*/
ALSeqPlayer *sound_seqplayer_init(s32 maxVoices, s32 maxEvents) {
    ALCSPlayer *cseqp;
    ALSeqpConfig config;

    config.maxVoices = maxVoices;
    config.maxEvents = maxEvents;
    config.unknown_0x10 = maxVoices; //this member doesn't exist in other versions of ALSeqpConfig
    config.maxChannels = AUDIO_CHANNELS;
    config.heap = &gALHeap;
    config.initOsc = NULL;
    config.updateOsc = NULL;
    config.stopOsc = NULL;

    cseqp = (ALCSPlayer *) alHeapAlloc(&gALHeap, 1, sizeof(ALCSPlayer));
    alCSPNew(cseqp, &config);
    alCSPSetBank(cseqp, ALBankFile_80115D10->bankArray[0]);
    cseqp->unk36 = 127;

    return (ALSeqPlayer *) cseqp;
}

/**
 * Stop the current sequence then set the parameters for the next sequence.
*/
void music_sequence_start(u8 seqID, ALSeqPlayer *seqPlayer) {
    music_sequence_stop(seqPlayer);
    if (seqID < gSequenceTable->seqCount) {
        if (seqPlayer == gMusicPlayer) {
            gMusicSetChannelMask = seqID;
        } else {
            gSoundSetChannelMask = seqID;
        }
    } else {
        stubbed_printf("Invalid midi sequence index\n");
    }
}

/** 
 * If the sequence player is currently inactive, start a new sequence with the current properties.
*/
void music_sequence_init(ALSeqPlayer *seqp, void *sequence, u8 *arg2, ALCSeq *seq) {
    s32 i;

    if ((alCSPGetState((ALCSPlayer* ) seqp) == AL_STOPPED) && (*arg2 != 0)) {
        load_asset_to_address(ASSET_AUDIO, (u32) sequence, gSequenceTable->seqArray[*arg2].offset - get_rom_offset_of_asset(ASSET_AUDIO, 0), (s32) gSeqLengthTable[*arg2]);
        alCSeqNew(seq, sequence);
        alCSPSetSeq((ALCSPlayer* ) seqp, seq);
        alCSPPlay((ALCSPlayer* ) seqp);
        if (seqp == gMusicPlayer) {
            set_relative_volume_for_music(sMusicPool[*arg2].volume);
            if (sMusicPool[*arg2].tempo != 0) {
                musicSetTempo(sMusicPool[*arg2].tempo);
            } else {
                sMusicTempo = -1;
            }
            sound_reverb_set(sMusicPool[*arg2].reverb);
            gCurrentSequenceID = *arg2;
            if (gDynamicMusicChannelMask != -1) {
                for (i = 0; i < AUDIO_CHANNELS; i++) {
                    if ((1 << i) & gDynamicMusicChannelMask) {
                        func_80001170(i);
                    } else {
                        func_80001114(i);
                    }
                }
            }
        } else {
            sfxSetRelativeVolume(sMusicPool[*arg2].volume);
            if (sMusicPool[*arg2].tempo != 0) {
                sfxSetTempo(sMusicPool[*arg2].tempo);
            }
            gCurrentJingleID = *arg2;
        }
        *arg2 = 0;
    }
}

/**
 * Stops the current playing sequence for the given sequence player.
*/
void music_sequence_stop(ALSeqPlayer *seqPlayer) {
    if (gMusicPlayer == seqPlayer && gMusicPlaying) {
        alCSPStop((ALCSPlayer *) seqPlayer);
        gMusicPlaying = FALSE;
        gCurrentSequenceID = SEQUENCE_NONE;
        gMusicSetChannelMask = FALSE;
    } else if (gSndFxPlayer == seqPlayer && gJinglePlaying) {
        alCSPStop((ALCSPlayer *) seqPlayer);
        gJinglePlaying = FALSE;
        gSoundSetChannelMask = FALSE;
    }
}

/**
 * Enable or disable special audio effects.
 * This includes reverb and echo.
*/
void sound_reverb_set(u8 setting) {
    alFxReverbSet(setting);
}

/**
 * Returns whether or not reverb is currently enabled.
*/
UNUSED u8 sound_reverb_enabled(void) {
    return sMusicPool[gCurrentSequenceID].reverb;
}
