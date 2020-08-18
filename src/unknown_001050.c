/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80000450 */

#include "types.h"
#include "macros.h"

#include "audio_internal.h"


/* Size: 0x08 bytes */
typedef struct unk80115D48 {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s32 unk4;
} unk80115D48;

extern ALCSPlayer* gMusicPlayer;
extern ALCSPlayer* gSndFxPlayer;

extern u8  musicRelativeVolume;
extern u8  sfxRelativeVolume;
extern u8  D_800DC640;
extern u8  D_800DC644;
extern s32 D_800DC648;
extern s32 audioPrevCount;
extern f32 D_800DC650;
extern s32 musicVolumeSliderPercentage;
extern s32 D_800DC658;
extern u8  D_800DC65C;
extern u8  D_800DC660;
extern s32 D_800DC66C;
extern u8  D_800DC670;

extern f32 D_800E49DC;
extern f32 D_800E49EC;

extern u8  D_800EBF60;
extern ALHeap gALHeap;

/* Unknown size */
typedef struct unk80115CF8 {
    u8 pad0[2];
    s16 unk2;
} unk80115CF8;

extern ALSeqFile *ALSeqFile_80115CF8;
extern void *D_80115CFC;

extern u8  D_80115D04;
extern u8  D_80115D05;
extern s32 musicTempo;

extern ALBankFile *ALBankFile_80115D10;

extern ALBankFile *ALBankFile_80115D14;

/* Size: 0x0A bytes */
typedef struct unk80115D18 {
    u8 pad0[6];
    u16 unk6;
    u8 pad8[2];
} unk80115D18;

extern unk80115D18* D_80115D18;

/* Size: 3 bytes */
typedef struct unk80115D1C {
    u8 unk0;
    u8 unk1;
    u8 unk2;
} unk80115D1C;
extern void *D_80115D00;
extern u32 *D_80115D0C;
extern unk80115D1C* D_80115D1C;
extern s32 D_80115D20;
extern s32 D_80115D24;
extern u32 D_80115D28;
extern u32 D_80115D2C;
extern s16 D_80115D30;
extern s32 D_80115D38;
extern s32 D_80115D3C;
extern u8  D_80115D40;
extern u8  D_80115D41;
extern unk80115D48 D_80115D48[8];
extern ALCSeq D_80115D88;
extern ALCSeq D_80115E80;
extern u8  D_80115F78;
extern u8  D_80115F79;
extern s32 D_80115F7C;
extern u32 D_80115F84;
extern u32 D_80115F88;



typedef struct audioMgrConfig_s{
    u32 unk00;
    u32 unk04;
    u32 maxChannels;
    ALHeap* hp;
    u16  unk10;
} audioMgrConfig;

void func_80000968(s32 arg0);
ALCSPlayer* func_80002224(s32, s32);
void func_8000B010(ALCSPlayer*, u8);
void    *func_80070C9C(u32, u32);
void    *func_80076C58(u32);
void    *alHeapDBAlloc(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size);

void audio_init(u32 arg0){
    s32 iCnt;
    ALSynConfig synth_config;
    u32 *reg_s2;
    u32 seqfSize;
    u32 seq_max_len;
    u32 tmp2;
    audioMgrConfig audConfig;
   
    seq_max_len = 0;
    alHeapInit(&gALHeap, &D_800EBF60, 0x00029D88);
    
    reg_s2 = func_80076C58(38);
    ALBankFile_80115D14 = (ALBankFile*) func_80070C9C(reg_s2[2] - reg_s2[1], 0x00FFFFFF);
    func_80076E68(39, ALBankFile_80115D14, reg_s2[1], reg_s2[2] - reg_s2[1]);
    alBnkfNew(ALBankFile_80115D14, func_80076EE8(39, reg_s2[2]));
    
    D_80115D28 = reg_s2[7] - reg_s2[6];
    D_80115D18 = (unk80115D18 *) func_80070C9C(D_80115D28, 0x00FFFFFF);
    func_80076E68(39, D_80115D18, reg_s2[6], D_80115D28);
    D_80115D20 = D_80115D28/10;
    
    D_80115D2C = reg_s2[6]-reg_s2[5];
    D_80115D1C = (unk80115D1C *) func_80070C9C(D_80115D2C, 0x00FFFFFF);
    func_80076E68(39, D_80115D1C, reg_s2[5], D_80115D2C);
    D_80115D24 = D_80115D2C/3;

    ALBankFile_80115D10 = (ALBankFile *)func_80070C9C(reg_s2[0], 0x00FFFFFF);
    func_80076E68(39, ALBankFile_80115D10, 0, reg_s2[0]);
    alBnkfNew(ALBankFile_80115D10, func_80076EE8(39, reg_s2[0]));
    ALSeqFile_80115CF8 = (ALSeqFile *) alHeapDBAlloc(0,0,&gALHeap,1,4);
    func_80076E68(39, ALSeqFile_80115CF8, reg_s2[4], 4);

    seqfSize = (ALSeqFile_80115CF8->seqCount)*8 + 4;
    ALSeqFile_80115CF8 = func_80070C9C(seqfSize, 0x00FFFFFF);
    func_80076E68(39, ALSeqFile_80115CF8, reg_s2[4], seqfSize);
    alSeqFileNew(ALSeqFile_80115CF8, func_80076EE8(39, reg_s2[4]));
    D_80115D0C = (u32 *)func_80070C9C( (ALSeqFile_80115CF8->seqCount)*4, 0x00FFFFFF);


    for(iCnt = 0; iCnt < ALSeqFile_80115CF8->seqCount; iCnt++){
        (u32*)((u32) ALSeqFile_80115CF8 + 8 + iCnt*8);
        D_80115D0C[iCnt] = ALSeqFile_80115CF8->seqArray[iCnt].len;
        if(D_80115D0C[iCnt] & 1){
            D_80115D0C[iCnt]++;
        }
        if(seq_max_len < D_80115D0C[iCnt]){
            seq_max_len = D_80115D0C[iCnt];
        }
    }


    synth_config.maxVVoices = 40;
    synth_config.maxPVoices = 40;
    synth_config.maxUpdates = 96;
    synth_config.dmaproc = NULL;
    synth_config.fxType = 6;
    synth_config.unk1d = 2;
    synth_config.outputRate = 0;
    synth_config.heap = &gALHeap;
    audioNewThread(&synth_config, 12, arg0);
    gMusicPlayer = func_80002224(24, 120);
    func_8000B010(gMusicPlayer, 18);
    gSndFxPlayer = func_80002224(16, 50);
    D_80115CFC = func_80070C9C( seq_max_len, 0x00FFFFFF);
    D_80115D00 = func_80070C9C( seq_max_len, 0x00FFFFFF);
    audConfig.unk04 = 150;
    audConfig.unk00 = 32;
    audConfig.maxChannels = 16;
    audConfig.unk10 = 1;
    audConfig.hp = &gALHeap;
    func_800031C0(&audConfig);
    audioStartThread();
    func_80000968(0);
    func_80071140(reg_s2);
    func_8000318C(10);
    D_800DC648 = 0;
    D_80115D40 = 0;
    D_80115D41 = 0;
    D_800DC658 = 0;
    D_80115F78 = 0;
    D_80115F79 = 0;
    return;
}

void musicSetRelativeVolume(u8);
void func_80004A60(u8, u16);


void func_80000890(u8 arg0){
    if(!D_80115F79){  
        D_80115F78 = arg0;
        if(D_80115F78 == 0){
            D_800DC66C = 256;
            musicSetRelativeVolume(musicRelativeVolume);
            func_80004A60(0,D_800DC66C*128-1);
            func_80004A60(1,D_800DC66C*128-1);
            func_80004A60(2,D_800DC66C*128-1);
            func_80004A60(4,D_800DC66C*128-1);
        }
    }
}



void func_80000968(s32 arg0) {
    switch(arg0) {
        case 1:
            func_80004A60(0, 0);
            func_80004A60(1, 0x7FFF);
            func_80004A60(2, 0);
            func_80004A60(4, 0);
            alCSPSetVol(gMusicPlayer, (s16) (musicRelativeVolume * musicVolumeSliderPercentage >> 2));
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
            alCSPSetVol(gMusicPlayer, (s16) (musicRelativeVolume * musicVolumeSliderPercentage));
            alCSPSetVol(gSndFxPlayer, (s16) (sfxGetVolumeSlider() * sfxRelativeVolume));
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

void func_800022BC(u8, ALCSPlayer*);

void func_80000B34(u8 arg0) {
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

void func_8000B010(ALCSPlayer* arg0, u8 arg1);

void func_80000BE0(u8 arg0) {
    if (D_800DC670 == 0) {
        func_8000B010(gMusicPlayer, arg0);
    }
}

void func_80000C1C(void) {
    D_800DC670 = 1;
}

void func_80000C2C(void) {
    D_800DC670 = 0;
}

void func_80000C38(u8 arg0) {
    func_8000B010(gSndFxPlayer, arg0);
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
    musicSetRelativeVolume(musicRelativeVolume);
}

void func_80001D04(u16,void*);
void func_8000232C(ALCSPlayer*, void*, u8*, ALCSeq*);

void func_80000D00(u8 arg0){
    s32 reg_s2;
    s32 j;
    if(D_80115D3C > 0){
        
        D_80115D38 += arg0;
        D_800DC650 = ((f32)D_80115D38)/((f32)D_80115D3C);
        
        if((f64)D_800DC650 > 1.0f){
            D_80115D38 = 0;
            D_80115D3C = 0;
            D_800DC650 = 1.0f;
        }
        musicSetRelativeVolume(musicRelativeVolume);
    }else if(D_80115D3C < 0) {
        
        D_80115D38 -= arg0;
        D_800DC650 = 1.0f - ((f32)D_80115D38)/((f32)D_80115D3C);
        if((f64)D_800DC650 < 0){
            D_80115D38 = 0;
            D_80115D3C = 0;
            D_800DC650 = 0.0f;
        }
        musicSetRelativeVolume(musicRelativeVolume);
    }

    if(D_800DC658 > 0){
        //reg_arg0 = arg0;
        for(reg_s2 = 0; reg_s2 < D_800DC658;){
            D_80115D48[reg_s2].unk2 -= arg0;
            if(D_80115D48[reg_s2].unk2 <= 0){
                j = reg_s2;
                func_80001D04(D_80115D48[reg_s2].unk0, D_80115D48[reg_s2].unk4);
                
                D_800DC658 -= 1;
                while(j  < D_800DC658){
                    D_80115D48[reg_s2].unk0 = D_80115D48[reg_s2 + 1].unk0;
                    D_80115D48[reg_s2].unk2 = D_80115D48[reg_s2 + 1].unk2;
                    D_80115D48[reg_s2].unk4 = D_80115D48[reg_s2 + 1].unk4;
                    j++;
                    //break;
                }
                j++;
            }
            else{
                reg_s2++;
            }
        }
    }

    func_8000232C(gMusicPlayer, D_80115CFC, &D_800DC65C, &D_80115D88);
    func_8000232C(gSndFxPlayer, D_80115D00, &D_800DC660, &D_80115E80);
    if(D_80115D30 == -1 && gMusicPlayer->target){
        D_80115D30 = 0x03938700/alCSPGetTempo(gMusicPlayer);
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
void func_80001114(u8 arg0);
void func_80001170(u8 arg0);


void func_80001074(u16 arg0){
    u32 chan;
    if(D_800DC65C){
        D_80115F7C = arg0;
    }
    else{
        gMusicPlayer->chanMask = arg0;
        for(chan = 0; chan != 16; chan++){
            if(arg0 & (1 << chan)){
                func_80001170(chan);
            }
            else{
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

s32 alCSPSetChlPan(ALCSPlayer*, u8 chan, ALPan pan);

void musicSetChlPan(u8 chan, ALPan pan) {
    if (chan < 0x10) {
        alCSPSetChlPan(gMusicPlayer, chan, pan);
    }
}

void alCSPSetChlVol(ALCSPlayer*, u8 chan, u8 vol);

void musicSetChlVol(u8 chan, u8 vol) {
    if (chan < 0x10) {
        alCSPSetChlVol(gMusicPlayer, chan, vol);
    }
}

s32 alCSPGetChlVol(ALCSPlayer*, u8 arg1);

/* Unused?*/
s32 musicGetChlVol(u8 arg0) {
    if (arg0 >= 0x10) {
        return 0;
    } else {
        return alCSPGetChlVol(gMusicPlayer, arg0);
    }
}

s32 func_80063BA0(ALCSPlayer*, u8 arg1, u8 arg2);

void func_80001268(u8 arg0, u8 arg1) {
    if (arg0 < 0x10) {
        func_80063BA0(gMusicPlayer, arg0, arg1);
    }
}

s32 func_80063C00(ALCSPlayer*, u8 arg1);

s32 func_800012A8(u8 arg0) {
    if (arg0 >= 0x10) {
        return 0;
    }
    return func_80063C00(gMusicPlayer, arg0);
}

void func_800012E8(void){
    u32 chan;
    if(!D_800DC648){
        for(chan = 0; chan<16; chan++){
            func_80001170( chan );
            func_80001268( chan, 127 );
            musicSetChlVol( chan, 127 );
        }
    }
    return;
}


u8 func_80001358(u8 arg0, u8 arg1, s32 arg2){
    u8 val_1f;
    u8 val_1e;
    s32 updatedVol;
    
    //u8 fadeIn_chan = arg0;
    if(!(arg0 == 100)){
        val_1f = arg2 + alCSPGetChlVol(gMusicPlayer,arg0);
        if(val_1f > 127){
            val_1f = 127;
        }
        alCSPSetChlVol(gMusicPlayer,arg0, val_1f);
    }

    if(arg1 != 100){
        
        updatedVol = alCSPGetChlVol(gMusicPlayer,arg1);
        val_1e = (updatedVol > arg2) ? updatedVol - arg2 : 0;
        alCSPSetChlVol(gMusicPlayer,arg1, val_1e);
        return val_1e;
    }
    else{
        return 127-val_1f;
    }
}

u8 alSeqpGetChlFXMix(ALCSPlayer*, u8);

void func_80001440(u8 *arg0){
    s32 s0 = 0;
    if(gMusicPlayer->maxChannels > 0){
        do{
            arg0[s0] = alSeqpGetChlFXMix(gMusicPlayer, s0);
            s0++;
        }while(s0 < gMusicPlayer->maxChannels);
    }
    return;
}

s16 musicGetTempo(void);

void musicSetTempo(s32);

void func_800014BC(f32 arg0) {
    musicSetTempo((s32)((f32)(u32)(musicGetTempo() & 0xFF) * arg0));
}


void musicSetTempo(s32 tempo){
    if(tempo != 0){
        f32 inv_tempo = (1.0f/tempo);
        alCSPSetTempo(gMusicPlayer,(s32)(inv_tempo*D_800E49DC));
        D_80115D30 = tempo;
    }
}

s16 musicGetTempo(void) {
    return D_80115D30;
}

u8 musicIsPlaying(void) {
    return (alCSPGetState(gMusicPlayer) == AL_PLAYING);
}


extern f32 D_800E49E0;
extern f32 D_800E49E8;
extern f32 D_80115D34;

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_800015F8.s")
#else
f32 func_800015F8(void){
    u32 current_cnt = osGetCount();
    u32 delta;
    f32 delta_f;
    f32 tmp;
    f32* tmp2 = &D_80115D34;
    
    if(audioPrevCount < current_cnt){
        delta = current_cnt - audioPrevCount;
        delta_f = (delta < 0)
            ? (f32) delta + 4294967296.000000f
            : delta;
        D_80115D34  = delta_f/D_800E49E0 + *tmp2;
    }
    else{
        delta = audioPrevCount - current_cnt;
        delta_f = (delta + -1);
        delta_f = (delta < 0)
            ? delta_f + 4294967296.000000f
            : delta_f;
        *tmp2  = delta_f/D_800E49E0 + D_80115D34;
    }
    if(D_80115D40 == 0){
        D_80115D30 = 182;
    }
    tmp = D_800E49E8/(f32) D_80115D30;
    while(D_80115D34 > tmp){
        D_80115D34 -= tmp;
    }
    audioPrevCount = current_cnt;
    return D_80115D34/tmp;

}
#endif

void func_80001728(u8 arg0, u8* arg1, u8* arg2, u8* arg3){
    *arg1 = D_80115D1C[arg0].unk1;
    *arg2 = D_80115D1C[arg0].unk0;
    *arg3 = D_80115D1C[arg0].unk2;
}

u32 func_80001C08(void);

void func_80001784(u8 a0){
    if(!func_80001C08()){
        func_800022BC(D_80115D05 = a0, gSndFxPlayer);
        D_80115D41 = 1;
    }
}


void sfxSetTempo(s32 tempo){
    f32 inv_tempo = (1.0f/tempo);
    alCSPSetTempo(gSndFxPlayer,(s32)(inv_tempo*D_800E49EC));
}


void func_80002570(ALCSPlayer* arg0);

void func_80001844(void){
    if(!D_800DC648){
        func_80002570(gMusicPlayer);
    }
    return;
}


void func_80001878(u8 arg0) {
    if (arg0 != D_800DC640) {
        D_800DC640 = arg0;
        if (arg0) {
            func_80000B34(D_80115D04);
        } else {
            func_80001844();
        }
    }
}

u8 func_800018D0(void){
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

extern u8 D_800DC65C;

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


void musicSetRelativeVolume(u8 vol){
    f32 normalized_vol;

    musicRelativeVolume = vol;
    normalized_vol = musicVolumeSliderPercentage*musicRelativeVolume*D_800DC650;
    alCSPSetVol(gMusicPlayer, (s16)((s32)(D_800DC66C*normalized_vol)>>8));
}

void musicSetVolSlider(u32 slider_val){
    f32 normalized_vol;
    
    slider_val = (slider_val < 0x101)?slider_val:256;
    musicVolumeSliderPercentage = slider_val;
    normalized_vol = musicVolumeSliderPercentage*musicRelativeVolume*D_800DC650;
    alCSPSetVol(gMusicPlayer, (s16)((s32)(D_800DC66C*normalized_vol)>>8));
}

u8 musicGetRelativeVolume(void) {
    return musicRelativeVolume;
}

s32 musicGetVolSliderPercentage(void) {
    return musicVolumeSliderPercentage;
}

void sfxSetRelativeVolume(u8 arg0) {
    sfxRelativeVolume = arg0;
    alCSPSetVol(gSndFxPlayer, (s16) (sfxGetVolumeSlider() * sfxRelativeVolume));
}

void sfxSetPan(ALPan pan){
    u32 iChan;
    for(iChan = 0; iChan < 16; iChan++){
        alCSPSetChlPan(gSndFxPlayer, iChan, pan);
    }
    return;
}

void func_80001BC0(u8 arg0){
    D_800DC644 = 1;
    func_800022BC( D_80115D05 = arg0, gSndFxPlayer);
}

u32 func_80001C08(void){
    if(D_80115D05 && D_800DC644 && (gSndFxPlayer->state == AL_PLAYING) ){
        return D_80115D05;
    }
    D_800DC644 = 0;
    return 0;
}

void func_80001C5C(u16 arg0){
    u32 s0;
    for(s0 = 0; s0<64; s0++){
        func_80004A60(s0, arg0 << 8);
    }
}


u16 func_80001CB8(u16 arg0) {
    if (D_80115D20 < arg0) {
        return 0;
    }
    return D_80115D18[arg0].unk6;
}


#if 1
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001D04.s")
#else

#endif

typedef struct unknown_struct_80001EA8_s{
    u32    unk00;
    u32     unk04;
    u32     unk08;
}unknown_struct_80001EA8;

void func_80001EA8(u16 arg0, unknown_struct_80001EA8 arg1, u32* arg2){
    if(arg2 == NULL){
        arg2 = &D_80115F84;
    }
    func_80001D04(arg0, arg2);
    if(*arg2){
        func_80009B7C(*arg2, arg1.unk00, arg1.unk04, arg1.unk08);
    }
}

u16 ALBankFile_80115D14_GetSoundCount(void);

void func_80001F14(u16 sndIndx, u32 *arg1){
    if(sndIndx <= 0 || ALBankFile_80115D14_GetSoundCount() < sndIndx){
        if(arg1){
            *arg1 = 0;
        }
    }
    else{
        if(arg1){
            func_80004638(ALBankFile_80115D14->bankArray[0], (s16) sndIndx, arg1);
        }else{
            func_80004638(ALBankFile_80115D14->bankArray[0], (s16) sndIndx, &D_80115F88);
        }
    }
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80001FB8.s")
#else
void func_80001FB8(u16 arg0){
    arg0*10 + D_80115D18[0].unk00;
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

u8 ALBankFile_80115D14_GetSoundDecayTime(u16 sndIndx){
    if(sndIndx <= 0 || ALBankFile_80115D14->bankArray[0]->instArray[0]->soundCount < sndIndx){
        return 0;
    }
    return ((u32)(1+ ALBankFile_80115D14->bankArray[0]->instArray[0]->soundArray[sndIndx-1]->envelope->decayTime) == 0);
}


#if 0
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_80002224.s")
#else
extern void  alCSPNew(ALCSPlayer *seqp, ALSeqpConfig *config);
extern void  alCSPSetBank(ALCSPlayer *seqp, ALBank *b);

ALCSPlayer *func_80002224(s32 _max_voices, s32 _max_events){
    ALCSPlayer* cseqp;
    ALSeqpConfig config;
    
    config.maxVoices = _max_voices;
    config.maxEvents = _max_events;
    config.unknown_0x10 = _max_voices; //this member doesn't exist in other versions of ALSeqpConfig 
    config.maxChannels = 16;
    config.heap = &gALHeap;
    config.initOsc = NULL;
    config.updateOsc = NULL;
    config.stopOsc = NULL;

    
    cseqp = (ALCSPlayer *) alHeapDBAlloc(NULL, 0, &gALHeap, 1, 128);
    alCSPNew(cseqp, &config);
    alCSPSetBank(cseqp, ALBankFile_80115D10->bankArray[0]);
    ((u8*) cseqp)[0x36]= 0x7F; //this member doesn't exist in ALCSPlayer 
    return cseqp;
}
#endif



void func_800022BC(u8 arg0, ALCSPlayer* arg1) {
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
GLOBAL_ASM("asm/non_matchings/unknown_001050/func_8000232C.s")
#else
void func_8000232C(ALCSPlayer* seqp, void* ptr, u8* arg2, ALCSeq* seq){
    if(alCSPGetState(seqp) == AL_STOPPED && *arg2){
        /*func_80076E68(39, ptr, 
            (u32)((ALSeqFile_80115CF8->seqArray)[*arg2]) - func_80076EE8(39,0),
            *((u32*)(((*arg2) << 3) + D_80115D0C)));*/
        alCSeqNew(seq, ptr);
        alCSPSetSeq(seqp, seq);
        alCSPPlay(seqp);
        if(seqp == gMusicPlayer){
            musicSetRelativeVolume(*((u8*)((*arg2)*3 + D_80115D1C->unk0)));
        }else{

        }
    }
}
#endif

void func_80002570(ALCSPlayer* seqp){
    if(gMusicPlayer == seqp && D_80115D40 != 0){
        alCSPStop(seqp);
        D_80115D40 = 0;
        D_80115D04 = 0;
        D_800DC65C = 0;
    }
    else if(gSndFxPlayer == seqp && D_80115D41 != 0){
        alCSPStop(seqp);
        D_80115D41 = 0;
        D_800DC660 = 0;
    }
    return;
}

void func_8006492C(u8 arg0);

void func_80002608(u8 arg0) {
    func_8006492C(arg0);
}

u8 func_80002630(void) {
    return D_80115D1C[D_80115D04].unk2;
}
