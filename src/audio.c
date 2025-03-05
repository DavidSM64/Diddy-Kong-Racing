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
#include "libultra/src/audio/seqchannel.h"

/************ .data ************/

ALSeqPlayer *gMusicPlayer = NULL;
ALSeqPlayer *gJinglePlayer = NULL;
u8 gMusicBaseVolume = 127;
u8 sfxRelativeVolume = 127;
u8 gCanPlayMusic = TRUE;
u8 gCanPlayJingle = FALSE;
s32 gBlockMusicChange = FALSE;
s32 audioPrevCount = 0;
f32 sMusicFadeVolume = 1.0f;
s32 gMusicSliderVolume = 256;
s32 gDelayedSoundsCount = 0;
u8 gMusicNextSeqID = SEQUENCE_NONE;
u8 gJingleNextSeqID = SEQUENCE_NONE;
UNUSED s32 D_800DC664 = 0;
UNUSED s32 D_800DC668 = 0;
s32 gGlobalMusicVolume = 256; // This is never not 256...
u8 gBlockVoiceLimitChange = FALSE;

/*******************************/

/************ .bss ************/

// The audio heap is located at the start of the BSS section.
u8 gAudioHeapStack[AUDIO_HEAP_SIZE];

ALHeap gALHeap;
ALSeqFile *gSequenceTable;
void *gMusicSequenceData;
void *gJingleSequenceData;
u8 gCurrentSequenceID;
u8 gCurrentJingleID;
s32 gMusicTempo;
u32 *gSeqLengthTable;
ALBankFile *gSequenceBank;
ALBankFile *gSoundBank; // Official Name: sfxBankPtr
SoundData *gSoundTable;
MusicData *gSeqSoundTable;
s32 gSoundCount;
s32 gSeqSoundCount;
u32 gSoundTableSize;
u32 gSeqSoundTableSize;
s16 sMusicTempo;
f32 gMusicAnimationTick;
s32 sMusicDelayTimer;
s32 sMusicDelayLength;
u8 gMusicPlaying;
u8 gJinglePlaying;
DelayedSound gDelayedSounds[8];
ALCSeq gMusicSequence;
ALCSeq gJingleSequence;
u8 gSkipResetChannels; // Stored and used by a single function, but redundant.
u8 gAudioVolumeSetting;
u32 gDynamicMusicChannelMask;
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
    alHeapInit(&gALHeap, gAudioHeapStack, sizeof(gAudioHeapStack));

    addrPtr = (s32 *) load_asset_section_from_rom(ASSET_AUDIO_TABLE);
    gSoundBank = (ALBankFile *) mempool_alloc_safe(addrPtr[ASSET_AUDIO_2] - addrPtr[ASSET_AUDIO_1], COLOUR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, (u32) gSoundBank, addrPtr[ASSET_AUDIO_1],
                          addrPtr[ASSET_AUDIO_2] - addrPtr[ASSET_AUDIO_1]);
    alBnkfNew(gSoundBank, get_rom_offset_of_asset(ASSET_AUDIO, addrPtr[ASSET_AUDIO_2]));

    gSoundTableSize = addrPtr[ASSET_AUDIO_7] - addrPtr[ASSET_AUDIO_6];
    gSoundTable = (SoundData *) mempool_alloc_safe(gSoundTableSize, COLOUR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, (u32) gSoundTable, addrPtr[ASSET_AUDIO_6], gSoundTableSize);
    gSoundCount = gSoundTableSize / sizeof(SoundData);

    gSeqSoundTableSize = addrPtr[ASSET_AUDIO_6] - addrPtr[ASSET_AUDIO_5];
    gSeqSoundTable = (MusicData *) mempool_alloc_safe(gSeqSoundTableSize, COLOUR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, (u32) gSeqSoundTable, addrPtr[ASSET_AUDIO_5], gSeqSoundTableSize);
    gSeqSoundCount = gSeqSoundTableSize / sizeof(MusicData);

    gSequenceBank = (ALBankFile *) mempool_alloc_safe(addrPtr[ASSET_AUDIO_0], COLOUR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, (u32) gSequenceBank, 0, addrPtr[ASSET_AUDIO_0]);
    alBnkfNew(gSequenceBank, get_rom_offset_of_asset(ASSET_AUDIO, addrPtr[ASSET_AUDIO_0]));
    gSequenceTable = (ALSeqFile *) alHeapAlloc(&gALHeap, 1, 4);
    load_asset_to_address(ASSET_AUDIO, (u32) gSequenceTable, addrPtr[ASSET_AUDIO_4], 4);

    seqfSize = (gSequenceTable->seqCount) * 8 + 4;
    gSequenceTable = mempool_alloc_safe(seqfSize, COLOUR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, (u32) gSequenceTable, addrPtr[ASSET_AUDIO_4], seqfSize);
    alSeqFileNew(gSequenceTable, get_rom_offset_of_asset(ASSET_AUDIO, addrPtr[ASSET_AUDIO_4]));
    gSeqLengthTable = (u32 *) mempool_alloc_safe((gSequenceTable->seqCount) * 4, COLOUR_TAG_CYAN);

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
    gJinglePlayer = sound_seqplayer_init(16, 50);
    gMusicSequenceData = mempool_alloc_safe(seqLength, COLOUR_TAG_CYAN);
    gJingleSequenceData = mempool_alloc_safe(seqLength, COLOUR_TAG_CYAN);
    audConfig.unk04 = 150;
    audConfig.unk00 = 32;
    audConfig.maxChannels = AUDIO_CHANNELS;
    audConfig.unk10 = 1;
    audConfig.hp = &gALHeap;
    alSndPNew(&audConfig);
    audioStartThread();
    sound_volume_change(VOLUME_NORMAL);
    mempool_free(addrPtr);
    set_sound_channel_count(10);
    gBlockMusicChange = FALSE;
    gMusicPlaying = FALSE;
    gJinglePlaying = FALSE;
    gDelayedSoundsCount = 0;
    gSkipResetChannels = FALSE;
    gAudioVolumeSetting = VOLUME_NORMAL;
#ifdef AVOID_UB
    gMusicAnimationTick = 1.0f; // Prevents a denorm crash on the character select screen.
#endif
}

/**
 * Depending on whether or not the audio volume is set to normal and the argument is false, reset sound effect channel
 * volumes.
 */
void sound_volume_reset(u8 skipReset) {
    if (gAudioVolumeSetting == VOLUME_NORMAL) {
        gSkipResetChannels = skipReset;
        if (gSkipResetChannels == FALSE) {
            gGlobalMusicVolume = 256;
            music_volume_set(gMusicBaseVolume);
            set_sound_channel_volume(0, gGlobalMusicVolume * 128 - 1);
            set_sound_channel_volume(1, gGlobalMusicVolume * 128 - 1);
            set_sound_channel_volume(2, gGlobalMusicVolume * 128 - 1);
            set_sound_channel_volume(4, gGlobalMusicVolume * 128 - 1);
        }
    }
}

/**
 * Changes the volume of each sound channel depending on what value is passed through.
 */
void sound_volume_change(s32 behaviour) {
    switch (behaviour) {
        case VOLUME_LOWER: // Mute most sound effects and half the volume of music.
            set_sound_channel_volume(0, 0);
            set_sound_channel_volume(1, 32767);
            set_sound_channel_volume(2, 0);
            set_sound_channel_volume(4, 0);
            alCSPSetVol((ALCSPlayer *) gMusicPlayer, (s16) (gMusicBaseVolume * gMusicSliderVolume >> 2));
            alCSPSetVol((ALCSPlayer *) gJinglePlayer, 0);
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
            alCSPSetVol((ALCSPlayer *) gMusicPlayer, (s16) (gMusicBaseVolume * gMusicSliderVolume));
            alCSPSetVol((ALCSPlayer *) gJinglePlayer, (s16) (get_sfx_volume_slider() * sfxRelativeVolume));
            break;
    }
    gAudioVolumeSetting = behaviour;
}

/**
 * Prevents changing of background music.
 */
void music_change_off(void) {
    gBlockMusicChange = TRUE;
}

/**
 * Allows changing of background music.
 */
void music_change_on(void) {
    gBlockMusicChange = FALSE;
}

/**
 * Queue a new music sequence to play if not blocked.
 * Stops any playing existing music beforehand.
 */
void music_play(u8 seqID) {
    if (gBlockMusicChange == FALSE && gMusicSliderVolume != 0) {
        gCurrentSequenceID = seqID;
        gMusicBaseVolume = 127;
        if (gCanPlayMusic) {
            music_sequence_start(gCurrentSequenceID, gMusicPlayer);
        }
        gMusicTempo = alCSPGetTempo((ALCSPlayer *) gMusicPlayer);
        audioPrevCount = osGetCount();
        gMusicPlaying = TRUE;
        gDynamicMusicChannelMask = MUSIC_CHAN_MASK_NONE;
    }
}

/**
 * Update the background music voice limit if not prevented from doing so.
 */
void music_voicelimit_set(u8 voiceLimit) {
    if (gBlockVoiceLimitChange == FALSE) {
        set_voice_limit(gMusicPlayer, voiceLimit);
    }
}

/**
 * Prevent the background music voice limit from being changed.
 */
void music_voicelimit_change_off(void) {
    gBlockVoiceLimitChange = TRUE;
}

/**
 * Allow the background music voice limit to be changed.
 */
void music_voicelimit_change_on(void) {
    gBlockVoiceLimitChange = FALSE;
}

/**
 * Update the jingle players voice limit.
 */
void music_jingle_voicelimit_set(u8 voiceLimit) {
    set_voice_limit(gJinglePlayer, voiceLimit);
}

UNUSED void func_80000C68(u8 arg0) {
    func_80063A90(gMusicPlayer, arg0);
}

/**
 * Enables the timer to start fading in or out the background music.
 * Give it a positive number to fade in, otherwise, give it a negative one to fade out.
 */
void music_fade(s32 time) {
    sMusicDelayTimer = 0;
    sMusicDelayLength = (time * 60) >> 8;
}

/**
 * Sets the background music volume back to normal.
 */
void music_volume_reset(void) {
    sMusicDelayTimer = 0;
    sMusicDelayLength = 0;
    sMusicFadeVolume = 1.0f;
    music_volume_set(gMusicBaseVolume);
}

/**
 * Run every frame, this handles the transitions in and out of music sequences.
 * If there's something in the queue, then begin to play that.
 * Additionally, it also handles the delayed audio queue, counting down and playing any sounds.
 */
void sound_update_queue(u8 updateRate) {
    s32 i;
    s32 j;

    if (sMusicDelayLength > 0) {
        sMusicDelayTimer += updateRate;
        sMusicFadeVolume = ((f32) sMusicDelayTimer) / ((f32) sMusicDelayLength);
        if (sMusicFadeVolume > 1.0) {
            sMusicDelayTimer = 0;
            sMusicDelayLength = 0;
            sMusicFadeVolume = 1.0f;
        }
        music_volume_set(gMusicBaseVolume);
    } else if (sMusicDelayLength < 0) {
        sMusicDelayTimer -= updateRate;
        sMusicFadeVolume = 1.0f - ((f32) sMusicDelayTimer) / ((f32) sMusicDelayLength);
        if (sMusicFadeVolume < 0.0) {
            sMusicDelayTimer = 0;
            sMusicDelayLength = 0;
            sMusicFadeVolume = 0.0f;
        }
        music_volume_set(gMusicBaseVolume);
    }

    if (gDelayedSoundsCount > 0) {
        for (i = 0; i < gDelayedSoundsCount;) {
            gDelayedSounds[i].timer -= updateRate;
            if (gDelayedSounds[i].timer <= 0) {
                j = i;
                sound_play(gDelayedSounds[i].soundId, (s32 *) gDelayedSounds[i].soundMask);

                gDelayedSoundsCount -= 1;
                while (j < gDelayedSoundsCount) {
                    gDelayedSounds[i].soundId = gDelayedSounds[i + 1].soundId;
                    gDelayedSounds[i].timer = gDelayedSounds[i + 1].timer;
                    gDelayedSounds[i].soundMask = gDelayedSounds[i + 1].soundMask;
                    j++;
                }
                j++;
            } else {
                i++;
            }
        }
    }

    music_sequence_init(gMusicPlayer, gMusicSequenceData, &gMusicNextSeqID, &gMusicSequence);
    music_sequence_init(gJinglePlayer, gJingleSequenceData, &gJingleNextSeqID, &gJingleSequence);
    if (sMusicTempo == -1 && gMusicPlayer->target) {
        sMusicTempo = 60000000 / alCSPGetTempo((ALCSPlayer *) gMusicPlayer);
    }
}

/**
 * Add a sound to a queue to play after a set time has passed.
 * Delay time is in seconds. (1.0f = 1 second)
 */
void sound_play_delayed(u16 soundId, SoundMask *soundMask, f32 delayTime) {
    if (gDelayedSoundsCount < 8) {
        gDelayedSounds[gDelayedSoundsCount].soundId = soundId;
        gDelayedSounds[gDelayedSoundsCount].soundMask = soundMask;
        gDelayedSounds[gDelayedSoundsCount].timer = delayTime * 60.0f;
        gDelayedSoundsCount++;
    }
}

/**
 * Clear the delayed sound queue.
 */
void sound_clear_delayed(void) {
    gDelayedSoundsCount = 0;
}

/**
 * Return the channel mask of the music player.
 * Official name: musicGetChanMask
 */
u16 music_channel_get_mask(void) {
    return gMusicPlayer->chanMask;
}

/**
 * Sets the channels in the sequence on or off based on the channel mask given.
 */
void music_dynamic_set(u16 channelMask) {
    u32 i;
    if (gMusicNextSeqID) {
        gDynamicMusicChannelMask = channelMask;
    } else {
        gMusicPlayer->chanMask = channelMask;
        for (i = 0; i != AUDIO_CHANNELS; i++) {
            if (channelMask & (1 << i)) {
                music_channel_on(i);
            } else {
                music_channel_off(i);
            }
        }
    }
}

/**
 * Mute the sequence channel, preventing it from playing any sound.
 */
void music_channel_off(u8 channel) {
    if (channel < AUDIO_CHANNELS) {
        alSeqChOff(gMusicPlayer, channel);
    }
}

/**
 * Return true if the given channel is currently active.
 * Official name: musicGetChnlActive
 */
s32 music_channel_active(s32 channel) {
    return (gMusicPlayer->chanMask & (1 << channel)) == 0;
}

/**
 * Unmute the sequence channel so it can play sound.
 */
void music_channel_on(u8 channel) {
    if (channel < AUDIO_CHANNELS) {
        alSeqChOn(gMusicPlayer, channel);
    }
}

/**
 * Set the panning level of the given channel for the music player.
 * Official name: musicSetChlPan
 */
void music_channel_pan_set(u8 channel, ALPan pan) {
    if (channel < AUDIO_CHANNELS) {
        alCSPSetChlPan((ALCSPlayer *) gMusicPlayer, channel, pan);
    }
}

/**
 * Set the volume of the given channel for the music player.
 * Official name musicSetChlVol
 */
void music_channel_volume_set(u8 channel, u8 volume) {
    if (channel < AUDIO_CHANNELS) {
        alCSPSetChlVol((ALCSPlayer *) gMusicPlayer, channel, volume);
    }
}

/**
 * Return the volume of the given channel in the music player.
 * Official name: musicGetChlVol
 */
UNUSED u8 music_channel_volume(u8 channel) {
    if (channel >= AUDIO_CHANNELS) {
        return 0;
    } else {
        return alCSPGetChlVol((ALCSPlayer *) gMusicPlayer, channel);
    }
}

/**
 * Set this channel to fade in over time.
 */
void music_channel_fade_set(u8 channel, ALPan fade) {
    if (channel < AUDIO_CHANNELS) {
        alCSPSetFadeIn(gMusicPlayer, channel, fade);
    }
}

/**
 * Return the fade volume of the given channel.
 */
u8 music_channel_fade(u8 channel) {
    if (channel >= AUDIO_CHANNELS) {
        return 0;
    }
    return alCSPGetFadeIn((ALCSPlayer *) gMusicPlayer, channel);
}

/**
 * Resets all audio channels for the music player to the default state.
 * This is being enabled, centre panning and at normal volume.
 */
void music_channel_reset_all(void) {
    u32 channel;
    if (gBlockMusicChange == FALSE) {
        for (channel = 0; channel < AUDIO_CHANNELS; channel++) {
            music_channel_on(channel);
            music_channel_fade_set(channel, 127);
            music_channel_volume_set(channel, 127);
        }
    }
}

UNUSED u8 func_80001358(u8 arg0, u8 arg1, s32 arg2) {
    u8 val_1f;
    u8 val_1e;
    s32 updatedVol;

    // u8 fadeIn_chan = arg0;
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

UNUSED void func_80001440(u8 *arg0) {
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
 * Since it calls music_tempo and multiplies it by the result, calling this repeatedly can recursively change the
 * music's speed.
 */
void music_tempo_set_relative(f32 tempo) {
    music_tempo_set((s32) ((f32) (u32) (music_tempo() & 0xFF) * tempo));
}

/**
 * Set the tempo of the current playing background music.
 * Official name: musicSetTempo
 */
void music_tempo_set(s32 tempo) {
    if (tempo != 0) {
        f32 inv_tempo = (1.0f / tempo);
        alCSPSetTempo((ALCSPlayer *) gMusicPlayer, (s32) (inv_tempo * 60000000.0f));
        sMusicTempo = tempo;
    }
}

/**
 * Return the tempo of the current playing background music.
 * Official name: musicGetTempo
 */
s16 music_tempo(void) {
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
    for (tmp = 120000.0f / (f32) sMusicTempo; tmp < gMusicAnimationTick; gMusicAnimationTick -= tmp) {
        ;
    }
    audioPrevCount = (s32) cnt;
    return gMusicAnimationTick / tmp;
}

/**
 * Writes the music and sound tempo, as well as the volume to the arguments.
 */
UNUSED void sound_get_properties(u8 poolID, u8 *tempo, u8 *volume, u8 *reverb) {
    *tempo = gSeqSoundTable[poolID].tempo;
    *volume = gSeqSoundTable[poolID].volume;
    *reverb = gSeqSoundTable[poolID].reverb;
}

/**
 * Play a jingle, but only if there isn't one playing already.
 */
void music_jingle_play_safe(u8 jingleID) {
    if (music_jingle_playing() == SEQUENCE_NONE) {
        music_sequence_start(gCurrentJingleID = jingleID, gJinglePlayer);
        gJinglePlaying = TRUE;
    }
}

/**
 * Sets the tempo for the jingle player.
 */
void sound_jingle_tempo_set(s32 tempo) {
    f32 inv_tempo = (1.0f / tempo);
    alCSPSetTempo((ALCSPlayer *) gJinglePlayer, (s32) (inv_tempo * 60000000.0f));
}

/**
 * Stops the background music.
 */
void music_stop(void) {
    if (gBlockMusicChange == FALSE) {
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
            music_play(gCurrentSequenceID);
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
        music_sequence_stop(gJinglePlayer);
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

/**
 * Return the next music sequence to be played if there is one.
 * Otherwise, return what's currently playing.
 */
UNUSED u8 music_next(void) {
    if (gMusicNextSeqID) {
        return gMusicNextSeqID;
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

/**
 * Set the volume of the music.
 * Update music volume with this new setting.
 */
void music_volume_set(u8 volume) {
    f32 normalized_vol;

    gMusicBaseVolume = volume;
    normalized_vol = gMusicSliderVolume * gMusicBaseVolume * sMusicFadeVolume;
    alCSPSetVol((ALCSPlayer *) gMusicPlayer, (s16) ((s32) (gGlobalMusicVolume * normalized_vol) >> 8));
}

/**
 * Set the user configured music volume.
 * Update music volume with this new setting.
 */
void music_volume_config_set(u32 slider_val) {
    f32 normalized_vol;

    slider_val = (slider_val <= 256) ? slider_val : 256;
    gMusicSliderVolume = slider_val;
    normalized_vol = gMusicSliderVolume * gMusicBaseVolume * sMusicFadeVolume;
    alCSPSetVol((ALCSPlayer *) gMusicPlayer, (s16) ((s32) (gGlobalMusicVolume * normalized_vol) >> 8));
}

/**
 * Return the baseline music volume, unaffected by user config.
 */
u8 music_volume(void) {
    return gMusicBaseVolume;
}

/**
 * Return the music volume set by the player.
 */
s32 music_volume_config(void) {
    return gMusicSliderVolume;
}

/**
 * Set the volume for the jingle player.
 * The jingle player scales with sfx volume rather than music volume.
 */
void music_jingle_volume_set(u8 arg0) {
    sfxRelativeVolume = arg0;
    alCSPSetVol((ALCSPlayer *) gJinglePlayer, (s16) (get_sfx_volume_slider() * sfxRelativeVolume));
}

/**
 * Set the panning level for every channel in the jingle player.
 */
void music_jingle_pan_set(ALPan pan) {
    u32 iChan;
    for (iChan = 0; iChan < AUDIO_CHANNELS; iChan++) {
        alCSPSetChlPan((ALCSPlayer *) gJinglePlayer, iChan, pan);
    }
}

/**
 * Plays a sequence just once, allowing it to coexist with the music if necessary.
 * Examples include getting silver coins, challenge keys, or getting the locked message.
 */
void music_jingle_play(u8 seqID) {
    gCanPlayJingle = TRUE;
    music_sequence_start(gCurrentJingleID = seqID, gJinglePlayer);
}

/**
 * If there's a jingle playing, return that, otherwise, return 0.
 */
u32 music_jingle_playing(void) {
    if (gCurrentJingleID && gCanPlayJingle && (gJinglePlayer->state == AL_PLAYING)) {
        return gCurrentJingleID;
    }
    gCanPlayJingle = FALSE;
    return SEQUENCE_NONE;
}

/**
 * Sets the volume for every sound channel.
 * Tries to set up to 64, regardless of if there are 64 sound channels or not.
 * !@bug: This can cause an out of bounds array index.
 */
UNUSED void sound_channel_volume_all(u16 volume) {
    u32 i;
    for (i = 0; i < 64; i++) {
        set_sound_channel_volume(i, volume << 8);
    }
}

/**
 * Return the audible distance of the sound effect.
 */
u16 sound_distance(u16 soundId) {
    if (soundId > gSoundCount) {
        return 0;
    }
    return gSoundTable[soundId].distance;
}

/**
 * Add the requested sound to the queue and update the mask to show that this sound is playing at that source.
 * If no soundmask is provided, then instead use the global mask.
 */
void sound_play(u16 soundID, s32 *soundMask) {
    f32 pitch;
    s32 soundBite;

    if (soundID > gSoundCount) {
        if (soundMask != NULL) {
            *soundMask = NULL;
        }
        stubbed_printf("amSndPlay: Illegal sound effects table index\n");
        return;
    }
    soundBite = gSoundTable[soundID].soundBite;
    if (soundBite == NULL) {
        if (soundMask != NULL) {
            *soundMask = NULL;
        }
        stubbed_printf("amSndPlayDirect: Somebody tried to play illegal sound %d\n", soundID);
        return;
    }
    pitch = gSoundTable[soundID].pitch / 100.0f;
    if (soundMask != NULL) {
        func_80004668(gSoundBank->bankArray[0], soundBite, gSoundTable[soundID].unk8, (SoundMask *) soundMask);
        if (*soundMask != NULL) {
            sound_event_update(*soundMask, AL_SNDP_VOL_EVT, gSoundTable[soundID].volume * 256);
            sound_event_update(*soundMask, AL_SNDP_PITCH_EVT, *((u32 *) &pitch));
        }
    } else {
        soundMask = (s32 *) &gGlobalSoundMask;
        func_80004668(gSoundBank->bankArray[0], soundBite, gSoundTable[soundID].unk8, (SoundMask *) &gGlobalSoundMask);
        if (*soundMask != NULL) {
            sound_event_update(*soundMask, AL_SNDP_VOL_EVT, gSoundTable[soundID].volume * 256);
            sound_event_update(*soundMask, AL_SNDP_PITCH_EVT, *((u32 *) &pitch));
        }
    }
}

/**
 * Creates a spatial audio reference, then plays a sound.
 * This then makes the audio pan around in 3D space.
 * If it is not given a mask, then it will use the global mask.
 */
void sound_play_spatial(u16 soundID, f32 x, f32 y, f32 z, s32 **soundMask) {
    if (soundMask == NULL) {
        soundMask = (s32 **) &gSpatialSoundMask;
    }

    sound_play(soundID, (s32 *) soundMask);

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
        func_80004638(gSoundBank->bankArray[0], (s16) soundID, (SoundMask *) soundMask);
    } else {
        func_80004638(gSoundBank->bankArray[0], (s16) soundID, (SoundMask *) &gRacerSoundMask);
    }
}

/**
 * Set the volume of the sound relative to the baseline volume of the sound ID.
 */
void sound_volume_set_relative(u16 soundID, void *soundState, u8 volume) {
    s32 newVolume = ((s32) (gSoundTable[soundID].volume * (volume / 127.0f))) * 256;
    if (soundState) {
        sound_event_update((s32) soundState, AL_SNDP_VOL_EVT, newVolume);
    }
}

/**
 * Updates the volume of the given sound mask.
 */
UNUSED void sound_volume_set(SoundMask *soundMask, u8 arg1) {
    if (soundMask != NULL) {
        sound_event_update((s32) soundMask, AL_SNDP_VOL_EVT, arg1 * 256);
    }
}

/**
 * Updates the pitch of the given sound mask.
 * Official name: amSndSetPitchDirect
 */
UNUSED void sound_pitch_set(SoundMask *soundMask, u32 pitch) {
    u32 *pitchAddr = &pitch;
    if (soundMask != NULL) {
        sound_event_update((s32) soundMask, AL_SNDP_PITCH_EVT, *pitchAddr);
    }
}

/**
 * Return the number of playable sounds in the audio table.
 * Official name: amGetSfxCount
 */
u16 sound_count(void) {
    return gSoundBank->bankArray[0]->instArray[0]->soundCount;
}

/**
 * Return mumber of playable sequences in the table.
 */
u8 music_sequence_count(void) {
    return gSequenceTable->seqCount;
}

/**
 * Writes the sound table address, size and element count into the arguments.
 */
void sound_table_properties(SoundData **table, s32 *size, s32 *count) {
    if (table != NULL) {
        *table = gSoundTable;
    }
    if (size != NULL) {
        *size = gSoundTableSize;
    }
    if (count != NULL) {
        *count = gSoundCount;
    }
}

/**
 * Writes the music sound table address, size and element count into the arguments.
 */
UNUSED void music_table_properties(MusicData **table, s32 *size, s32 *count) {
    if (table != NULL) {
        *table = gSeqSoundTable;
    }
    if (size != NULL) {
        *size = gSeqSoundTableSize;
    }
    if (count != NULL) {
        *count = gSeqSoundCount;
    }
}

u8 gSoundBank_GetSoundDecayTime(u16 soundID) {
    if (soundID <= 0 || gSoundBank->bankArray[0]->instArray[0]->soundCount < soundID) {
        return 0;
    }
    return ((u32) (1 + gSoundBank->bankArray[0]->instArray[0]->soundArray[soundID - 1]->envelope->decayTime) == 0);
}

/**
 * Allocate space, then initialise a sequence player for audio playback.
 */
ALSeqPlayer *sound_seqplayer_init(s32 maxVoices, s32 maxEvents) {
    ALCSPlayer *cseqp;
    ALSeqpConfig config;

    config.maxVoices = maxVoices;
    config.maxEvents = maxEvents;
    config.unknown_0x10 = maxVoices; // this member doesn't exist in other versions of ALSeqpConfig
    config.maxChannels = AUDIO_CHANNELS;
    config.heap = &gALHeap;
    config.initOsc = NULL;
    config.updateOsc = NULL;
    config.stopOsc = NULL;

    cseqp = (ALCSPlayer *) alHeapAlloc(&gALHeap, 1, sizeof(ALCSPlayer));
    alCSPNew(cseqp, &config);
    alCSPSetBank(cseqp, gSequenceBank->bankArray[0]);
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
            gMusicNextSeqID = seqID;
        } else {
            gJingleNextSeqID = seqID;
        }
    } else {
        stubbed_printf("Invalid midi sequence index\n");
    }
}

/**
 * If the sequence player is currently inactive, start a new sequence with the current properties.
 */
void music_sequence_init(ALSeqPlayer *seqp, void *sequence, u8 *seqID, ALCSeq *seq) {
    s32 i;

    if ((alCSPGetState((ALCSPlayer *) seqp) == AL_STOPPED) && (*seqID != 0)) {
        load_asset_to_address(ASSET_AUDIO, (u32) sequence,
                              gSequenceTable->seqArray[*seqID].offset - get_rom_offset_of_asset(ASSET_AUDIO, 0),
                              (s32) gSeqLengthTable[*seqID]);
        alCSeqNew(seq, sequence);
        alCSPSetSeq((ALCSPlayer *) seqp, seq);
        alCSPPlay((ALCSPlayer *) seqp);
        if (seqp == gMusicPlayer) {
            music_volume_set(gSeqSoundTable[*seqID].volume);
            if (gSeqSoundTable[*seqID].tempo != 0) {
                music_tempo_set(gSeqSoundTable[*seqID].tempo);
            } else {
                sMusicTempo = -1;
            }
            sound_reverb_set(gSeqSoundTable[*seqID].reverb);
            gCurrentSequenceID = *seqID;
            if (gDynamicMusicChannelMask != MUSIC_CHAN_MASK_NONE) {
                for (i = 0; i < AUDIO_CHANNELS; i++) {
                    if ((1 << i) & gDynamicMusicChannelMask) {
                        music_channel_on(i);
                    } else {
                        music_channel_off(i);
                    }
                }
            }
        } else {
            music_jingle_volume_set(gSeqSoundTable[*seqID].volume);
            if (gSeqSoundTable[*seqID].tempo != 0) {
                sound_jingle_tempo_set(gSeqSoundTable[*seqID].tempo);
            }
            gCurrentJingleID = *seqID;
        }
        *seqID = SEQUENCE_NONE;
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
        gMusicNextSeqID = SEQUENCE_NONE;
    } else if (gJinglePlayer == seqPlayer && gJinglePlaying) {
        alCSPStop((ALCSPlayer *) seqPlayer);
        gJinglePlaying = FALSE;
        gJingleNextSeqID = SEQUENCE_NONE;
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
    return gSeqSoundTable[gCurrentSequenceID].reverb;
}
