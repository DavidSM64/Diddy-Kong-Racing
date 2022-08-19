#ifndef _UNKNOWN_003260_H_
#define _UNKNOWN_003260_H_

#include "types.h"
#include "macros.h"
#include "audio_internal.h"
#include "asset_enums.h"
#include "libultra_internal.h"
#include "sched.h"

#define AL_SNDP_PLAY_EVT (1 << 0)
#define AL_SNDP_STOP_EVT (1 << 1)
#define AL_SNDP_PAN_EVT (1 << 2)
#define AL_SNDP_VOL_EVT (1 << 3)
#define AL_SNDP_PITCH_EVT (1 << 4)
#define AL_SNDP_API_EVT (1 << 5)
#define AL_SNDP_DECAY_EVT (1 << 6)
#define AL_SNDP_END_EVT (1 << 7)
#define AL_SNDP_FX_EVT (1 << 8)

#define AUDIO_STACKSIZE 0x3010
#define NUM_DMA_MESSAGES 50

typedef struct unk800DC6BC_40 {
    ALLink node;
    u8 pad0C[0x38];
} unk800DC6BC_40; //ALSoundState

/* Unknown Size */
typedef struct unk800DC6BC {
    ALPlayer        node;
    ALEventQueue    evtq;
    ALEvent         nextEvent;
    ALSynth        *drvr;
    u32             unk3C;
    unk800DC6BC_40 *unk40;
    s32             soundChannelsMax;
    s32             soundChannels;
    s32             frameTime;
    ALMicroTime     nextDelta;
    ALMicroTime     curTime;
} unk800DC6BC; //ALSndPlayer

typedef union {
    ALEvent msg;

    struct{
        s16 type;
        void* state;
        u32 unk04;
    }snd_event;

}ALSndpEvent;

typedef struct
{
    ALLink      node;
    u32         startAddr;
    u32         lastFrame;
    char        *ptr;
} AMDMABuffer;

/* Unknown Size */
/*typedef struct unk800DC6B0 {
    ALLink node;
    ALLink_s * unk08;
} unk800DC6B0;
*/

typedef struct audioMgrConfig_s{
    u32 unk00;
    u32 unk04;
    u32 maxChannels;
    ALHeap *hp;
    u16  unk10;
} audioMgrConfig;

typedef struct {
    u8 initialized;
    AMDMABuffer *firstUsed;
    AMDMABuffer *firstFree;
} AMDMAState;

extern u32 audFrameCt;
extern s32 D_800DC684;
extern s32 D_800DC688;
extern s32 D_800DC68C;
extern s32 gFunc80019808Checksum;
extern s32 gFunc80019808Length;
extern s32 D_800DC698;
extern s32 D_800DC69C;
extern s32 D_800DC6A0;
extern s32 D_800DC6A4;
extern s32 D_800DC6A8;
extern s32 D_800DC6AC;

extern ALEventQueue *D_800DC6B0;
extern s32 D_800DC6B4;
extern unk800DC6BC_40* D_800DC6B8;
extern unk800DC6BC* gAlSndPlayer;

extern s32 sfxVolumeSlider;
extern s32 D_800DC6C4;

extern void thread4_audio(void*);
void *alHeapDBAlloc(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size); //lib/src/al
void alEvtqNew(ALEventQueue *evtq, ALEventListItem *items, s32 itemCount); //lib/src/unknown_0C9C90.c
ALMicroTime alEvtqNextEvent(ALEventQueue *evtq, ALEvent *evt); //lib/src/unknown_0C9C90.c
void alSynAddPlayer(ALSynth *drvr, ALPlayer *client); //lib/src/unknown_0C9C90.c
void alEvtqPostEvent(ALEventQueue *evtq, ALEvent *evt, ALMicroTime delta); //lib/src/unknown_0C9C90.c Non Matching

void audioStartThread(void);
void audioStopThread(void);
void set_sfx_volume_slider(u32 arg0);
s32 sfxGetVolumeSlider(void);
void set_sound_channel_count(s32 arg0);
void alSndPNew(audioMgrConfig *c);
void func_80004604(u8 *arg0, u8 arg1);
u8 func_8000461C(u8 *arg0);
void func_80004638(ALBank *bnk, s16 sndIndx, s32 arg2);
//Causes issues with its type
//void func_8000488C(u8 *soundMask);
void func_800049D8(void);
void func_800049F8(void * sndState,s16 type, u32 arg2);
u16 func_80004A3C(u8 arg0);
ALDMAproc __amDmaNew(AMDMAState **state);
void func_80004A60(u8 arg0, u16 arg1);

// Non Matching
ALMicroTime  _sndpVoiceHandler(void *node);
void func_80004668(ALBank *bnk, s16 sndIndx, u8, s32);
void audioNewThread(ALSynConfig *c, OSPri p, OSSched *arg2);

#endif
