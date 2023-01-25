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


#define EXTRA_SAMPLES           96
#define AUDIO_STACKSIZE 0x3010
#define NUM_DMA_MESSAGES 50            /* The maximum number of DMAs any one frame can  */
                                       /* have.                                         */

#define FRAME_LAG               1      /* The number of frames to keep a dma buffer.    */
                                       /* Increasing this number causes buffers to not  */
                                       /* be deleted as quickly. This results in fewer  */
                                       /* DMA's but you need more buffers.              */
#define QUIT_MSG                10

/****  type define's for structures unique to audiomgr ****/
typedef union {    

    struct {
        short     type;
    } gen;

    struct {
        short     type;
        struct    AudioInfo_s *info;
    } done;
    
    OSScMsg       app;
    
} AudioMsg;

// TODO: Rare likely modified this struct as evidenced by __amHandleFrameMsg
// using *data when it should have been using msg.
typedef struct AudioInfo_s {
    short         *data;          /* Output data pointer */
    short         frameSamples;   /* # of samples synthesized in this frame */
    OSScTask      task;           /* scheduler structure */
    AudioMsg      msg;            /* completion message */
} AudioInfo;

typedef struct unk800DC6BC_40 {
    ALLink node;
    u8 pad0C[0x38];
} unk800DC6BC_40; //ALSoundState


typedef struct unk8000410C {
  /* 0x00 */ s8 pad00[0x0C];
  /* 0x0C */ ALVoice voice;
  /* 0x28 */ s8 pad28[0x16];
  /* 0x3E */ u8 unk3E;
} unk8000410C; //ALSoundState?

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

typedef struct {
  /* 0x00 */ s8 pad00[0x0C];
  /* 0x0C */ ALVoice     voice;
    ALSound     *sound;         /* sound referenced here */
    s16         priority;
    f32         pitch;          /* current playback pitch                    */
    s32         state;          /* play state for this sound                 */
    s16         vol;            /* volume - combined with volume from bank   */
    ALPan       pan;            /* pan - 0 = left, 127 = right               */
    u8          fxMix;          /* wet/dry mix - 0 = dry, 127 = wet          */
  /* 0x3C */ u8 pad3C[2];
  /* 0x3E */ u8 unk3E;
} ALSoundState;

typedef union {
    ALEvent msg;

    struct{
        s16 type;
        void* state;
        u32 unk04;
    }snd_event;

} ALEvent2;

typedef union {

    ALEvent             msg;

    struct {
        s16             type;
        ALSoundState    *state;
    } common;
    
    struct {
        s16             type;
        ALSoundState    *state;
        s16             vol;
    } vol;
    
    struct {
        s16             type;
        ALSoundState    *state;
        f32             pitch;
    } pitch;
    
    struct {
        s16             type;
        ALSoundState    *state;
        ALPan           pan;
    } pan;
    
    struct {
        s16             type;
        ALSoundState    *state;
        u8              mix;
    } fx;
    
} ALSndpEvent;

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
    u16  unk10; // Heap Size?
} audioMgrConfig;

typedef struct {
    u8 initialized;
    AMDMABuffer *firstUsed;
    AMDMABuffer *firstFree;
} AMDMAState;

extern u32 audFrameCt;
extern u32 nextDMA;
extern u32 curAcmdList;
extern s8 D_800DC68C;
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
extern s8 rspF3DDKRBootStart[];
extern s8 rspF3DDKRDramStart[];
extern s8 rspUnknownDataStart[];
extern s8 rspUnknownStart[];
extern u32 D_80119634;

extern void __amMain(void*);
Acmd *alAudioFrame(Acmd *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen);
void *alHeapDBAlloc(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size); //lib/src/al
void alEvtqNew(ALEventQueue *evtq, ALEventListItem *items, s32 itemCount); //lib/src/unknown_0C9C90.c
ALMicroTime alEvtqNextEvent(ALEventQueue *evtq, ALEvent *evt); //lib/src/unknown_0C9C90.c
void alSynAddPlayer(ALSynth *drvr, ALPlayer *client); //lib/src/unknown_0C9C90.c
void alEvtqPostEvent(ALEventQueue *evtq, ALEvent *evt, ALMicroTime delta); //lib/src/unknown_0C9C90.c Non Matching

void audioStartThread(void);
void audioStopThread(void);
void set_sfx_volume_slider(u32 arg0);
s32 sfxGetVolumeSlider(void);
void set_sound_channel_count(s32 numChannels);
void alSndPNew(audioMgrConfig *c);
void func_80004604(u8 *arg0, u8 arg1);
u8 func_8000461C(u8 *arg0);
void func_80004638(ALBank *bnk, s16 sndIndx, s32 arg2);
INCONSISTENT void func_8000488C();
void func_800049D8(void);
void func_800049F8(s32 soundMask, s16 type, u32 volume);
u16 get_sound_channel_volume(u8 arg0);
ALDMAproc __amDmaNew(AMDMAState **state);
void set_sound_channel_volume(u8 channel, u16 volume);
static void __amHandleDoneMsg(AudioInfo *info);
u16 func_800042CC(u16 *lastAllocListIndex, u16 *lastFreeListIndex);
void func_8000410C(ALSoundState *state);
static void _removeEvents(ALEventQueue *, ALSoundState *, u16);
void __clearAudioDMA(void);

// Non Matching
ALMicroTime  _sndpVoiceHandler(void *node);
void func_80004668(ALBank *bnk, s16 sndIndx, u8, s32);
void audioNewThread(ALSynConfig *c, OSPri p, OSSched *arg2);
void func_800048D8(s32);
u32 __amHandleFrameMsg(AudioInfo *info, AudioInfo *lastInfo);
void _handleEvent(unk800DC6BC *snd, ALSndpEvent *event);
void func_80004520(ALSoundState *);

#endif
