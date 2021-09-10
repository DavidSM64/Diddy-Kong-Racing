#ifndef _UNKNOWN_003260_H_
#define _UNKNOWN_003260_H_

#include "types.h"
#include "macros.h"
#include "audio_internal.h"
#include "asset_sections.h"
#include "libultra_internal.h"

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
    s32             unk44;
    s32             unk48;
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

typedef struct unk80119240
{
    ALLink node;
    u32 unk08;
    u32 unk0C;
    void *unk10;
} unk80119240;

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

extern s32 D_800DC680;
extern s32 D_800DC684;
extern s32 D_800DC688;
extern s32 D_800DC68C;
extern s32 D_800DC690;
extern s32 D_800DC694;
extern s32 D_800DC698;
extern s32 D_800DC69C;
extern s32 D_800DC6A0;
extern s32 D_800DC6A4;
extern s32 D_800DC6A8;
extern s32 D_800DC6AC;

extern s32 D_800DC6B0;
extern s32 D_800DC6B4;
extern unk800DC6BC_40* D_800DC6B8;
extern unk800DC6BC* gAlSndPlayer;

extern s32 sfxVolumeSlider;
extern s32 D_800DC6C4;

#endif