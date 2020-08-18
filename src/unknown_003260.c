/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80002660 */

#include "types.h"
#include "macros.h"
#include "audio_internal.h"
#include "libultra_internal.h"

extern void D_80002A98(void*);
extern u32 D_80003008;

/* Unknown Size */
typedef struct unk800DC6BC {
    u8  pad00[0x44];
    s32 unk44;
    s32 unk48;
} unk800DC6BC;

typedef struct unk80119240
{
    ALLink node;
    u32    unk08;
    u32    unk0C;
    void*  unk10;
} unk80119240;

/* Unknown Size */
/*typedef struct unk800DC6B0 {
    ALLink node;
    ALLink_s * unk08;
} unk800DC6B0;
*/
extern u32 D_800DC6A0;
//extern unk800DC6B0* D_800DC6B0;
extern unk800DC6BC* D_800DC6BC;
extern s32 sfxVolumeSlider;
extern s32 D_80115F90;
extern ALHeap* D_80115F94;
extern OSThread audioThread;
extern OSMesgQueue D_80116160;
extern OSMesg D_80116178;
extern OSMesgQueue D_80116198;
extern OSMesg D_801161B0;
extern ALGlobals D_801161D0;
extern s32 D_80119230;
extern unk80119240 D_80119240[0x31];
extern s32 D_8011962C;
extern OSMesgQueue D_80119AF0;
extern OSMesg D_80119B08;
extern u16* D_80119C28;
extern f32 D_80126170;

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
    c->dmaproc = &D_80003008;
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
        alInit(&D_801161D0, c);
        func_80071140(reg_s0);
    }
    else{
        alInit(&D_801161D0, c);
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
    osCreateMesgQueue(&D_80116160, &D_80116178, 8);
    osCreateMesgQueue(&D_80119AF0, &D_80119B08, 50);

    osCreateThread(&audioThread, 4, &D_80002A98, NULL, &D_80119230, p);
}
#endif

void audioStartThread(void) {
    osStartThread(&audioThread);
}

void audioStopThread(void) {
    osStopThread(&audioThread);
}

GLOBAL_ASM("asm/non_matchings/unknown_003260/D_80002A98.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80002C00.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80002DF8.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/D_80002E38.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/D_80003008.s")
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
    if (D_800DC6BC->unk44 >= arg0) {
        D_800DC6BC->unk48 = arg0;
    } else {
        D_800DC6BC->unk48 = D_800DC6BC->unk44;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_003260/func_800031C0.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/_sndpVoiceHandler.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/_handleEvent.s")
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

GLOBAL_ASM("asm/non_matchings/unknown_003260/func_8000488C.s")
GLOBAL_ASM("asm/non_matchings/unknown_003260/func_800048D8.s")

void func_800049D8(void) {
    func_800048D8(3);
}



GLOBAL_ASM("asm/non_matchings/unknown_003260/func_800049F8.s")

u16 func_80004A3C(u8 arg0){
    return D_80119C28[arg0];
}

GLOBAL_ASM("asm/non_matchings/unknown_003260/func_80004A60.s")
