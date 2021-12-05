/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80000450 */

#include "audio.h"
#include "memory.h"

#include "types.h"
#include "macros.h"
#include "asset_sections.h"
#include "asset_loading.h"
#include "audio_internal.h"
#include "unknown_003260.h"
#include "sched.h"

/************ .data ************/

ALSeqPlayer *gMusicPlayer = NULL;
ALSeqPlayer *gSndFxPlayer = NULL;
u8 musicRelativeVolume = 0x7F;
u8 sfxRelativeVolume = 0x7F;
u8 D_800DC640 = 1;
u8 D_800DC644 = 0;
s32 D_800DC648 = 0;
s32 audioPrevCount = 0;
f32 D_800DC650 = 1.0;
s32 musicVolumeSliderPercentage = 0x100;
s32 D_800DC658 = 0;
u8 D_800DC65C = 0;
u8 D_800DC660 = 0;
s32 D_800DC664 = 0; // Currently unknown, might be a different type.
s32 D_800DC668 = 0; // Currently unknown, might be a different type.
s32 D_800DC66C = 0x100;
u8 D_800DC670 = 0;

/*******************************/

/************ .rodata ************/

// Debug strings
const char D_800E4950[] = "amSndPlay: Illegal sound effects table index\n";
const char D_800E4980[] = "amSndPlayDirect: Somebody tried to play illegal sound %d\n";
const char D_800E49BC[] = "Invalid midi sequence index\n";

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
ALBankFile *ALBankFile_80115D10;
ALBankFile *ALBankFile_80115D14;

unk80115D18 *D_80115D18;
unk80115D1C *D_80115D1C;

s32 D_80115D20;
s32 D_80115D24;
u32 D_80115D28;
u32 D_80115D2C;
s16 D_80115D30;
f32 D_80115D34;
s32 D_80115D38;
s32 D_80115D3C;
u8 D_80115D40;
u8 D_80115D41;
unk80115D48 D_80115D48[8];
ALCSeq D_80115D88;
ALCSeq D_80115E80;
u8 D_80115F78;
u8 D_80115F79;
s32 D_80115F7C;
s32 D_80115F80;
u32 D_80115F84;
u32 D_80115F88;

/******************************/

void audio_init(OSSched *arg0) {
    s32 iCnt;
    ALSynConfig synth_config;
    s32 *reg_s2;
    u32 seqfSize;
    u32 seq_max_len;
    u32 tmp2;
    audioMgrConfig audConfig;

    seq_max_len = 0;
    alHeapInit(&gALHeap, gBssSectionStart, AUDIO_HEAP_SIZE);

    reg_s2 = load_asset_section_from_rom(ASSET_AUDIO_TABLE);
    ALBankFile_80115D14 = (ALBankFile *)allocate_from_main_pool_safe(reg_s2[2] - reg_s2[1], COLOR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, ALBankFile_80115D14, reg_s2[1], reg_s2[2] - reg_s2[1]);
    alBnkfNew(ALBankFile_80115D14, get_rom_offset_of_asset(ASSET_AUDIO, reg_s2[2]));

    D_80115D28 = reg_s2[7] - reg_s2[6];
    D_80115D18 = (unk80115D18 *)allocate_from_main_pool_safe(D_80115D28, COLOR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, D_80115D18, reg_s2[6], D_80115D28);
    D_80115D20 = D_80115D28 / 10;

    D_80115D2C = reg_s2[6] - reg_s2[5];
    D_80115D1C = (unk80115D1C *)allocate_from_main_pool_safe(D_80115D2C, COLOR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, D_80115D1C, reg_s2[5], D_80115D2C);
    D_80115D24 = D_80115D2C / 3;

    ALBankFile_80115D10 = (ALBankFile *)allocate_from_main_pool_safe(reg_s2[0], COLOR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, ALBankFile_80115D10, 0, reg_s2[0]);
    alBnkfNew(ALBankFile_80115D10, get_rom_offset_of_asset(ASSET_AUDIO, reg_s2[0]));
    ALSeqFile_80115CF8 = (ALSeqFile *)alHeapDBAlloc(0, 0, &gALHeap, 1, 4);
    load_asset_to_address(ASSET_AUDIO, ALSeqFile_80115CF8, reg_s2[4], 4);

    seqfSize = (ALSeqFile_80115CF8->seqCount) * 8 + 4;
    ALSeqFile_80115CF8 = allocate_from_main_pool_safe(seqfSize, COLOR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, ALSeqFile_80115CF8, reg_s2[4], seqfSize);
    alSeqFileNew(ALSeqFile_80115CF8, get_rom_offset_of_asset(ASSET_AUDIO, reg_s2[4]));
    D_80115D0C = (u32 *)allocate_from_main_pool_safe((ALSeqFile_80115CF8->seqCount) * 4, COLOR_TAG_CYAN);

    for (iCnt = 0; iCnt < ALSeqFile_80115CF8->seqCount; iCnt++) {
        (u32 *)((u32)ALSeqFile_80115CF8 + 8 + iCnt * 8);
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
    audioNewThread(&synth_config, 12, arg0);
    gMusicPlayer = func_80002224(24, 120);
    set_voice_limit(gMusicPlayer, 18);
    gSndFxPlayer = func_80002224(16, 50);
    D_80115CFC = allocate_from_main_pool_safe(seq_max_len, COLOR_TAG_CYAN);
    D_80115D00 = allocate_from_main_pool_safe(seq_max_len, COLOR_TAG_CYAN);
    audConfig.unk04 = 150;
    audConfig.unk00 = 32;
    audConfig.maxChannels = 16;
    audConfig.unk10 = 1;
    audConfig.hp = &gALHeap;
    alSndPNew(&audConfig);
    audioStartThread();
    func_80000968(0);
    free_from_memory_pool(reg_s2);
    func_8000318C(10);
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
            D_800DC66C = 256;
            set_relative_volume_for_music(musicRelativeVolume);
            func_80004A60(0, D_800DC66C * 128 - 1);
            func_80004A60(1, D_800DC66C * 128 - 1);
            func_80004A60(2, D_800DC66C * 128 - 1);
            func_80004A60(4, D_800DC66C * 128 - 1);
        }
    }
}

void func_80000968(s32 arg0) {
    switch (arg0) {
        case 1:
            func_80004A60(0, 0);
            func_80004A60(1, 0x7FFF);
            func_80004A60(2, 0);
            func_80004A60(4, 0);
            alCSPSetVol(gMusicPlayer, (s16)(musicRelativeVolume * musicVolumeSliderPercentage >> 2));
            alCSPSetVol(gSndFxPlayer, 0);
            break;
        case 2:
            func_80004A60(0, 0);
            func_80004A60(1, 0x7FFF);
            func_80004A60(2, 0x7FFF);
            func_80004A60(4, 0x7FFF);
            break;
        case 3:
            func_80004A60(0, 0);
            func_80004A60(1, 0x7FFF);
            func_80004A60(2, 0);
            func_80004A60(4, 0);
            break;
        default:
            func_80004A60(0, 0x7FFF);
            func_80004A60(1, 0x7FFF);
            func_80004A60(2, 0x7FFF);
            func_80004A60(4, 0x7FFF);
            alCSPSetVol(gMusicPlayer, (s16)(musicRelativeVolume * musicVolumeSliderPercentage));
            alCSPSetVol(gSndFxPlayer, (s16)(sfxGetVolumeSlider() * sfxRelativeVolume));
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

void play_music(u8 arg0) {
    if (D_800DC648 == 0 && musicVolumeSliderPercentage != 0) {
        D_80115D04 = arg0;
        musicRelativeVolume = 0x7F;
        if (D_800DC640 != 0) {
            func_800022BC(D_80115D04, gMusicPlayer);
        }
        musicTempo = alCSPGetTempo(gMusicPlayer);
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

void func_80000C98(s32 arg0) {
    D_80115D38 = 0;
    D_80115D3C = (arg0 * 0x3C) >> 8;
}

void func_80000CBC(void) {
    D_80115D38 = 0;
    D_80115D3C = 0;
    D_800DC650 = 1.0f;
    set_relative_volume_for_music(musicRelativeVolume);
}

void process_audio(u8 updateRate) {
    s32 reg_s2;
    s32 j;
    if (D_80115D3C > 0) {

        D_80115D38 += updateRate;
        D_800DC650 = ((f32)D_80115D38) / ((f32)D_80115D3C);

        if ((f64)D_800DC650 > 1.0f) {
            D_80115D38 = 0;
            D_80115D3C = 0;
            D_800DC650 = 1.0f;
        }
        set_relative_volume_for_music(musicRelativeVolume);
    } else if (D_80115D3C < 0) {

        D_80115D38 -= updateRate;
        D_800DC650 = 1.0f - ((f32)D_80115D38) / ((f32)D_80115D3C);
        if ((f64)D_800DC650 < 0) {
            D_80115D38 = 0;
            D_80115D3C = 0;
            D_800DC650 = 0.0f;
        }
        set_relative_volume_for_music(musicRelativeVolume);
    }

    if (D_800DC658 > 0) {
        //reg_arg0 = updateRate;
        for (reg_s2 = 0; reg_s2 < D_800DC658;) {
            D_80115D48[reg_s2].unk2 -= updateRate;
            if (D_80115D48[reg_s2].unk2 <= 0) {
                j = reg_s2;
                func_80001D04(D_80115D48[reg_s2].unk0, D_80115D48[reg_s2].unk4);

                D_800DC658 -= 1;
                while (j < D_800DC658) {
                    D_80115D48[reg_s2].unk0 = D_80115D48[reg_s2 + 1].unk0;
                    D_80115D48[reg_s2].unk2 = D_80115D48[reg_s2 + 1].unk2;
                    D_80115D48[reg_s2].unk4 = D_80115D48[reg_s2 + 1].unk4;
                    j++;
                    //break;
                }
                j++;
            } else {
                reg_s2++;
            }
        }
    }

    func_8000232C(gMusicPlayer, D_80115CFC, &D_800DC65C, &D_80115D88);
    func_8000232C(gSndFxPlayer, D_80115D00, &D_800DC660, &D_80115E80);
    if (D_80115D30 == -1 && gMusicPlayer->target) {
        D_80115D30 = 0x03938700 / alCSPGetTempo(gMusicPlayer);
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

void func_80001114(u8 arg0) {
    if (arg0 < 0x10) {
        func_80063AF0(gMusicPlayer, arg0);
    }
}

s32 musicGetChnlActive(s32 arg0) {
    return (gMusicPlayer->chanMask & (1 << arg0)) == 0;
}

void func_80001170(u8 arg0) {
    if (arg0 < 0x10) {
        func_80063B44(gMusicPlayer, arg0);
    }
}

void musicSetChlPan(u8 chan, ALPan pan) {
    if (chan < 0x10) {
        alCSPSetChlPan(gMusicPlayer, chan, pan);
    }
}

void musicSetChlVol(u8 chan, u8 vol) {
    if (chan < 0x10) {
        alCSPSetChlVol(gMusicPlayer, chan, vol);
    }
}

/* Unused?*/
s32 musicGetChlVol(u8 arg0) {
    if (arg0 >= 0x10) {
        return 0;
    } else {
        return alCSPGetChlVol(gMusicPlayer, arg0);
    }
}

void func_80001268(u8 arg0, u8 arg1) {
    if (arg0 < 0x10) {
        func_80063BA0(gMusicPlayer, arg0, arg1);
    }
}

u8 func_800012A8(u8 arg0) {
    if (arg0 >= 0x10) {
        return 0;
    }
    return func_80063C00(gMusicPlayer, arg0);
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
        val_1f = arg2 + alCSPGetChlVol(gMusicPlayer, arg0);
        if (val_1f > 127) {
            val_1f = 127;
        }
        alCSPSetChlVol(gMusicPlayer, arg0, val_1f);
    }

    if (arg1 != 100) {

        updatedVol = alCSPGetChlVol(gMusicPlayer, arg1);
        val_1e = (updatedVol > arg2) ? updatedVol - arg2 : 0;
        alCSPSetChlVol(gMusicPlayer, arg1, val_1e);
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

void musicSetTempo(s32 tempo) {
    if (tempo != 0) {
        f32 inv_tempo = (1.0f / tempo);
        alCSPSetTempo(gMusicPlayer, (s32)(inv_tempo * 60000000.0f));
        D_80115D30 = tempo;
    }
}

s16 musicGetTempo(void) {
    return D_80115D30;
}

u8 music_is_playing(void) {
    return (alCSPGetState(gMusicPlayer) == AL_PLAYING);
}

#if 1
GLOBAL_ASM("asm/non_matchings/audio/func_800015F8.s")
#else
f32 func_800015F8(void) {
    u32 current_cnt = osGetCount();
    u32 delta;
    f32 delta_f;
    f32 tmp;
    f32 *tmp2 = &D_80115D34;

    if (audioPrevCount < current_cnt) {
        delta = current_cnt - audioPrevCount;
        delta_f = (delta < 0)
                      ? (f32)delta + 4294967296.000000f
                      : delta;
        D_80115D34 = delta_f / D_800E49E0 + *tmp2;
    } else {
        delta = audioPrevCount - current_cnt;
        delta_f = (delta + -1);
        delta_f = (delta < 0)
                      ? delta_f + 4294967296.000000f
                      : delta_f;
        *tmp2 = delta_f / D_800E49E0 + D_80115D34;
    }
    if (D_80115D40 == 0) {
        D_80115D30 = 182;
    }
    tmp = D_800E49E8 / (f32)D_80115D30;
    while (D_80115D34 > tmp) {
        D_80115D34 -= tmp;
    }
    audioPrevCount = current_cnt;
    return D_80115D34 / tmp;
}
#endif

void func_80001728(u8 arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    *arg1 = D_80115D1C[arg0].unk1;
    *arg2 = D_80115D1C[arg0].unk0;
    *arg3 = D_80115D1C[arg0].unk2;
}

void func_80001784(u8 a0) {
    if (!func_80001C08()) {
        func_800022BC(D_80115D05 = a0, gSndFxPlayer);
        D_80115D41 = 1;
    }
}

void sfxSetTempo(s32 tempo) {
    f32 inv_tempo = (1.0f / tempo);
    alCSPSetTempo(gSndFxPlayer, (s32)(inv_tempo * 60000000.0f));
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
    normalized_vol = musicVolumeSliderPercentage * musicRelativeVolume * D_800DC650;
    alCSPSetVol(gMusicPlayer, (s16)((s32)(D_800DC66C * normalized_vol) >> 8));
}

void set_music_volume_slider(u32 slider_val) {
    f32 normalized_vol;

    slider_val = (slider_val < 0x101) ? slider_val : 256;
    musicVolumeSliderPercentage = slider_val;
    normalized_vol = musicVolumeSliderPercentage * musicRelativeVolume * D_800DC650;
    alCSPSetVol(gMusicPlayer, (s16)((s32)(D_800DC66C * normalized_vol) >> 8));
}

u8 musicGetRelativeVolume(void) {
    return musicRelativeVolume;
}

s32 musicGetVolSliderPercentage(void) {
    return musicVolumeSliderPercentage;
}

void sfxSetRelativeVolume(u8 arg0) {
    sfxRelativeVolume = arg0;
    alCSPSetVol(gSndFxPlayer, (s16)(sfxGetVolumeSlider() * sfxRelativeVolume));
}

void sfxSetPan(ALPan pan) {
    u32 iChan;
    for (iChan = 0; iChan < 16; iChan++) {
        alCSPSetChlPan(gSndFxPlayer, iChan, pan);
    }
    return;
}

void play_sound(u8 arg0) {
    D_800DC644 = 1;
    func_800022BC(D_80115D05 = arg0, gSndFxPlayer);
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
    return D_80115D18[arg0].unk6;
}

GLOBAL_ASM("asm/non_matchings/audio/func_80001D04.s")

void func_80001EA8(u16 arg0, f32 x, f32 y, f32 z, s32 **arg4) {
    if (arg4 == NULL) {
        arg4 = &D_80115F84;
    }

    func_80001D04(arg0, arg4);

    if (*arg4 != NULL) {
        func_80009B7C(*arg4, x, y, z);
    }
}

void func_80001F14(u16 sndIndx, u32 *arg1) {
    if (sndIndx <= 0 || ALBankFile_80115D14_GetSoundCount() < sndIndx) {
        if (arg1) {
            *arg1 = 0;
        }
    } else {
        if (arg1) {
            func_80004638(ALBankFile_80115D14->bankArray[0], (s16)sndIndx, arg1);
        } else {
            func_80004638(ALBankFile_80115D14->bankArray[0], (s16)sndIndx, &D_80115F88);
        }
    }
}

#if 1
GLOBAL_ASM("asm/non_matchings/audio/func_80001FB8.s")
#else
void func_80001FB8(u16 arg0) {
    arg0 * 10 + D_80115D18[0].unk00;
}
#endif

u16 ALBankFile_80115D14_GetSoundCount(void) {
    return ALBankFile_80115D14->bankArray[0]->instArray[0]->soundCount;
}

u8 ALSeqFile_80115CF8_GetSeqCount(void) {
    return ALSeqFile_80115CF8->seqCount;
}

void func_80002128(unk80115D18 **arg0, s32 *arg1, s32 *arg2) {
    if (arg0 != NULL) {
        *arg0 = D_80115D18;
    }
    if (arg1 != NULL) {
        *arg1 = D_80115D28;
    }
    if (arg2 != NULL) {
        *arg2 = D_80115D20;
    }
}

/* Unused? */
void func_8000216C(unk80115D1C **arg0, s32 *arg1, s32 *arg2) {
    if (arg0 != NULL) {
        *arg0 = D_80115D1C;
    }
    if (arg1 != NULL) {
        *arg1 = D_80115D2C;
    }
    if (arg2 != NULL) {
        *arg2 = D_80115D24;
    }
}

u8 ALBankFile_80115D14_GetSoundDecayTime(u16 sndIndx) {
    if (sndIndx <= 0 || ALBankFile_80115D14->bankArray[0]->instArray[0]->soundCount < sndIndx) {
        return 0;
    }
    return ((u32)(1 + ALBankFile_80115D14->bankArray[0]->instArray[0]->soundArray[sndIndx - 1]->envelope->decayTime) == 0);
}

ALSeqPlayer *func_80002224(s32 _max_voices, s32 _max_events) {
    ALCSPlayer_Custom *cseqp;
    ALSeqpConfig config;

    config.maxVoices = _max_voices;
    config.maxEvents = _max_events;
    config.unknown_0x10 = _max_voices; //this member doesn't exist in other versions of ALSeqpConfig
    config.maxChannels = 16;
    config.heap = &gALHeap;
    config.initOsc = NULL;
    config.updateOsc = NULL;
    config.stopOsc = NULL;

    cseqp = (ALCSPlayer_Custom *)alHeapDBAlloc(NULL, 0, &gALHeap, 1, sizeof(ALCSPlayer_Custom));
    alCSPNew(cseqp, &config);
    alCSPSetBank(cseqp, ALBankFile_80115D10->bankArray[0]);
    cseqp->unk36 = 0x7F;

    return cseqp;
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

#if 1
GLOBAL_ASM("asm/non_matchings/audio/func_8000232C.s")
#else
void func_8000232C(ALSeqPlayer *seqp, void *ptr, u8 *arg2, ALCSeq *seq) {
    if (alCSPGetState(seqp) == AL_STOPPED && *arg2) {
        /*load_asset_to_address(ASSET_AUDIO, ptr, 
            (u32)((ALSeqFile_80115CF8->seqArray)[*arg2]) - get_rom_offset_of_asset(ASSET_AUDIO,0),
            *((u32*)(((*arg2) << 3) + D_80115D0C)));*/
        alCSeqNew(seq, ptr);
        alCSPSetSeq(seqp, seq);
        alCSPPlay(seqp);
        if (seqp == gMusicPlayer) {
            set_relative_volume_for_music(*((u8 *)((*arg2) * 3 + D_80115D1C->unk0)));
        } else {
        }
    }
}
#endif

void func_80002570(ALSeqPlayer *seqp) {
    if (gMusicPlayer == seqp && D_80115D40 != 0) {
        alCSPStop(seqp);
        D_80115D40 = 0;
        D_80115D04 = 0;
        D_800DC65C = 0;
    } else if (gSndFxPlayer == seqp && D_80115D41 != 0) {
        alCSPStop(seqp);
        D_80115D41 = 0;
        D_800DC660 = 0;
    }
    return;
}

void func_80002608(u8 arg0) {
    func_8006492C(arg0);
}

u8 func_80002630(void) {
    return D_80115D1C[D_80115D04].unk2;
}
