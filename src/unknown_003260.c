/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80002660 */

#include "unknown_003260.h"

#define AL_SNDP_PLAY_EVT (1 << 0)
#define AL_SNDP_STOP_EVT (1 << 1)
#define AL_SNDP_PAN_EVT (1 << 2)
#define AL_SNDP_VOL_EVT (1 << 3)
#define AL_SNDP_PITCH_EVT (1 << 4)
#define AL_SNDP_API_EVT (1 << 5)
#define AL_SNDP_DECAY_EVT (1 << 6)
#define AL_SNDP_END_EVT (1 << 7)
#define AL_SNDP_FX_EVT (1 << 8)

extern void func_80002A98(void*);
extern u32 func_80003008;

/************ .bss ************/

// All of these are defined in unknown_003260_bss.c
// This was needed, since there is a bss reordering issue with D_80119BD0 and gAlSndPlayer

extern s32 D_80115F90;
extern ALHeap* D_80115F94;
extern s32 D_80115F98[2];
extern s32 D_80115FA0[3];
extern OSThread audioThread;
extern OSMesgQueue OSMesgQueue_80116160;
extern OSMesg D_80116178[8];
extern OSMesgQueue D_80116198;
extern OSMesg D_801161B0[8];
extern ALGlobals ALGlobals_801161D0;
extern s32 D_80116220[3076];
extern s32 D_80119230[3];
extern unk80119240 D_80119240[50];
extern s32 D_80119628;
extern s32 D_8011962C;
extern s32 D_80119630;
extern s32 D_80119634;
extern s32 D_80119638[2];
extern s32 D_80119640[300];
extern OSMesgQueue D_80119AF0;
extern OSMesg D_80119B08[50];
extern unk800DC6BC D_80119BD0;
extern u16 *D_80119C28;

extern f32 D_80126170;

/******************************/

/************ .data ************/

s32 D_800DC680 = 0; // Currently unknown, might be a different type.
s32 D_800DC684 = 0; // Currently unknown, might be a different type.
s32 D_800DC688 = 0; // Currently unknown, might be a different type.
s32 D_800DC68C = 0; // Currently unknown, might be a different type.
s32 D_800DC690 = 0x35281; // Checksum of func_80019808
s32 D_800DC694 = 0xFD0; // Size of func_80019808 (for checksum).
s32 D_800DC698 = 0; // Currently unknown, might be a different type.
s32 D_800DC69C = 0; // Currently unknown, might be a different type.
s32 D_800DC6A0 = 1; // Currently unknown, might be a different type.
s32 D_800DC6A4 = 0; // Currently unknown, might be a different type.
s32 D_800DC6A8 = 0; // Currently unknown, might be a different type.
s32 D_800DC6AC = 0; // Currently unknown, might be a different type.

s32 D_800DC6B0 = 0; // Currently unknown, might be a different type.
s32 D_800DC6B4 = 0; // Currently unknown, might be a different type.
unk800DC6BC_40 *D_800DC6B8 = NULL;
unk800DC6BC *gAlSndPlayer = &D_80119BD0;

s32 sfxVolumeSlider = 0x100;
s32 D_800DC6C4 = 0; // Currently unknown, might be a different type.

/*******************************/

/************ .rodata ************/

// Debug strings
const char D_800E49F0[] = "audio manager: RCP audio interface bug caused DMA from bad address - move audiomgr.c in the makelist!\n";
const char D_800E4A58[] = "audio: ai out of samples\n";
const char D_800E4A74[] = "OH DEAR - No audio DMA buffers left\n";
const char D_800E4A9C[] = "Dma not done\n";
const char D_800E4AAC[] = "";
const char D_800E49B0[] = "Bad soundState: voices =%d, states free =%d, states busy =%d, type %d data %x\n";
const char D_800E4B00[] = "playing a playing sound\n";
const char D_800E4B1C[] = "Nonsense sndp event\n";
const char D_800E4B34[] = "Sound state allocate failed - sndId %d\n";
const char D_800E4B5C[] = "Don't worry - game should cope OK\n";
const char D_800E4B80[] = "WARNING: Attempt to stop NULL sound aborted\n";

/*********************************/

void    *alHeapDBAlloc(u8 *, s32, ALHeap *, s32, s32);

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_003260/audioNewThread.s")
#else
void audioNewThread(ALSynConfig* c, OSPri p, s32 arg2){
    u32     *reg_v0;
    void    *reg_s0;
    u32     tmp_size;
    s32     tmp;
    s32 i;
    D_80115F90 = arg2;
    D_80115F94 = c->heap;
    c->dmaproc = &func_80003008;
    c->outputRate = func_800C8600(22050);
    D_8011962C = (((f32) c->outputRate)*2.0f)/D_80126170;
    if(D_8011962C < 0){
    }

    if(c->fxType == AL_FX_CUSTOM){
        reg_v0 = func_80076C58(38);
        tmp_size = reg_v0[9]-reg_v0[8];
        reg_s0 = func_80070C9C(tmp_size, 0x00FFFFFF, reg_v0[8]);
        func_80076E68(39,reg_s0, reg_v0[8],tmp_size);
        c->params = reg_s0;
        c[1].maxVVoices = 0;
        alInit(&ALGlobals_801161D0, c);
        func_80071140(reg_s0);
    }
    else{
        alInit(&ALGlobals_801161D0, c);
    }
    D_80119240[0].node.next = NULL;
    D_80119240[0].node.prev = NULL;

    for(i=0; i< 0x30; i++){
        alLink(&(D_80119240[i+1].node), &(D_80119240[i].node));
        D_80119240[i].unk10 = alHeapDBAlloc(0,0,c->heap, 1, 0x400);
    }
    D_80119240[i].unk10 = alHeapDBAlloc(0,0, c->heap, 1, 0x400);
    alHeapDBAlloc(0,0, c->heap, 1, 120);


    osCreateMesgQueue(&D_80116198, &D_801161B0, 8);
    osCreateMesgQueue(&OSMesgQueue_80116160, &D_80116178, 8);
    osCreateMesgQueue(&D_80119AF0, &D_80119B08, 50);

    osCreateThread(&audioThread, 4, &func_80002A98, NULL, &D_80119230, p);
}
#endif

void audioStartThread(void) {
    osStartThread(&audioThread);
}

void audioStopThread(void) {
    osStopThread(&audioThread);
}

GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80002A98.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80002C00.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80002DF8.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80002E38.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80003008.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80003040.s")

void sfxSetVolumeSlider(u32 arg0) {
    if (arg0 > 256) {
        arg0 = 256;
    }
    
    sfxVolumeSlider = arg0;
}

s32 sfxGetVolumeSlider(void) {
    return sfxVolumeSlider;
}

void func_8000318C(s32 arg0) {
    if (gAlSndPlayer->unk44 >= arg0) {
        gAlSndPlayer->unk48 = arg0;
    } else {
        gAlSndPlayer->unk48 = gAlSndPlayer->unk44;
    }
}



ALMicroTime     _sndpVoiceHandler(void *node);

void alSndPNew(audioMgrConfig* c){
    u32 i;
    unk800DC6BC_40* tmp1;
    ALEvent sp_38;

    gAlSndPlayer->unk44 = c->maxChannels;
    gAlSndPlayer->unk48 = c->maxChannels;
    gAlSndPlayer->unk3C = 0;
    gAlSndPlayer->frameTime = 33000;
    gAlSndPlayer->unk40 = (unk800DC6BC_40 *) alHeapDBAlloc(0, 0, c->hp, 1, (c->unk00) << 6);
    alEvtqNew(&(gAlSndPlayer->evtq), alHeapDBAlloc(0,0,c->hp,1, (c->unk04)*28), c->unk04);
    D_800DC6B8 = gAlSndPlayer->unk40;
    i=1;
    for(i=1; i < c->unk00; i++){
        tmp1 = gAlSndPlayer->unk40;
        alLink( i + tmp1, i + tmp1 - 1);
    }

    D_80119C28 = alHeapDBAlloc(0,0,c->hp, 2, c->unk10);
    for (i=0; i < c->unk10; i++){
        D_80119C28[i] = 32767;
    }


    gAlSndPlayer->drvr = alGlobals;
    gAlSndPlayer->node.next = NULL;
    gAlSndPlayer->node.handler = &_sndpVoiceHandler;
    gAlSndPlayer->node.clientData = gAlSndPlayer;
    
    alSynAddPlayer(gAlSndPlayer->drvr, gAlSndPlayer);
    sp_38.type = 32;
    alEvtqPostEvent(&(gAlSndPlayer->evtq), &sp_38, gAlSndPlayer->frameTime);
    gAlSndPlayer->nextDelta = alEvtqNextEvent(&(gAlSndPlayer->evtq), &(gAlSndPlayer->nextEvent));
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_003260/_sndpVoiceHandler.s")
#else  
ALMicroTime     _sndpVoiceHandler(void *node){
    unk800DC6BC *sndp = (unk800DC6BC *) node;
    ALSndpEvent evt;

    do {
        switch (sndp->nextEvent.type) {
            case (AL_SNDP_API_EVT):
                //TODO cannot get this const to load into reg t7
                evt.snd_event.type = AL_SNDP_API_EVT;
                alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, sndp->frameTime);
                break;
            
            default:
                _handleEvent(sndp, (ALSndpEvent *)&sndp->nextEvent);
                break;
        }
        sndp->nextDelta = alEvtqNextEvent(&sndp->evtq, &sndp->nextEvent);
        
    } while (sndp->nextDelta == 0);
    sndp->curTime += sndp->nextDelta;
    return sndp->nextDelta;
}
#endif

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_003260/_handleEvent.s")
#else

#endif

GLOBAL_ASM("asm/non_matchings/unknown_003260/func_8000410C.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_8000418C.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_800041FC.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_800042CC.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80004384.s")



GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80004520.s")


void func_80004604(u8* arg0, u8 arg1){
    if (arg0)
        arg0[0x36]=arg1;
}

u8 func_8000461C(u8* arg0){
    if (arg0)
        return arg0[0x3F];
    return 0;     
}

void func_80004638(ALBank* bnk, s16 sndIndx, s32 arg2) {
    func_80004668(bnk, sndIndx, 0, arg2);
}


#if 1
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80004668.s")
#else
void func_80004668(ALBank* bnk, s16 sndIndx, u8, s32){
}
#endif

//input typing not right (some type of struct)
void func_8000488C(u8* arg0){
    ALEvent sp_18;
    sp_18.type = 1024;
    ((u32*)(&sp_18))[1] = (u32) arg0;
    if(arg0){
        arg0[0x3e] &= ~(1<<4);
        alEvtqPostEvent(&(gAlSndPlayer->evtq), &sp_18, 0);
    }
}
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_800048D8.s")

void func_800049D8(void) {
    func_800048D8(3);
}

void func_800049F8(void * sndState,s16 type, u32 arg2){
    ALSndpEvent sndEvt;
    sndEvt.snd_event.type = type;
    sndEvt.snd_event.state = sndState;
    sndEvt.snd_event.unk04 = arg2;
    if(sndState){
        alEvtqPostEvent(&(gAlSndPlayer->evtq), &sndEvt,0);
    }

}

u16 func_80004A3C(u8 arg0){
    return D_80119C28[arg0];
}

GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80004A60.s")
