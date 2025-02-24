#ifndef _RCP_DKR_H_
#define _RCP_DKR_H_

#include "types.h"
#include "structs.h"
#include "f3ddkr.h"
#include "sched.h"
#include <ultra64.h>

#include "game_ui.h"
#include "video.h"

// Recommended size is around 100KB, or 0x19000. This is unused though so it doesn't matter.
#define OUTPUT_BUFFER_SIZE 0x1800

enum TextureRectangleFlags {
    TEXRECT_BILERP,
    TEXRECT_POINT = (1 << 0),
    TEXRECT_FLIP_X = (1 << 12),
    TEXRECT_FLIP_Y = (1 << 13),
};

typedef union {
    void (*function)(Gfx*, Matrix *);
    void *ptr;
} BackgroundFunction;

typedef struct DKR_OSTask {
    struct DKR_OSTask *next;
    u32 state;
    u32 flags;
    void *frameBuffer;
    OSTask_t task; // Size: 0x40 bytes
    OSMesgQueue *mesgQueue;
    OSMesg mesg;
    s32 unused58;
    s32 unused5C;
    s32 unused60;
    s32 unused64;
    u32 unk68;
    s32 unused6C;
} DKR_OSTask;

extern s16 gGfxTaskMesgNums[16];

extern u8 sBGPrimColourrR;
extern u8 sBGPrimColourrG;
extern u8 sBGPrimColourrB;
extern s32 sBackgroundFillColour;

extern TextureHeader *gTexBGTex1;
extern TextureHeader *gTexBGTex2;
extern s32 gChequerBGEnabled;

extern s32 gGfxBufCounter;
extern s32 gGfxBufCounter2;
extern s32 gGfxTaskIsRunning;

// Defined in dkr.ld
extern s8 rspF3DDKRDramStart[];
extern s8 rspF3DDKRBootStart[];
extern s8 rspF3DDKRXbusStart[];
extern s8 rspF3DDKRDataXbusStart[];
extern s8 rspF3DDKRFifoStart[];
extern s8 rspF3DDKRDataFifoStart[];

s32 gfxtask_wait(void);
void bgdraw_primcolour(u8 red, u8 green, u8 blue);
void bgdraw_fillcolour(s32 red, s32 green, s32 blue);
void rdp_init(Gfx **dList);
void rsp_init(Gfx **dList);
void gfxtask_init(OSSched *sc);
void bgdraw_texture_init(TextureHeader *tex1, TextureHeader *tex2, u32 shiftX);
s32 gfxtask_run_xbus(Gfx* dlBegin, Gfx* dlEnd, s32 recvMesg);
void gfxtask_run_fifo(Gfx* dlBegin, Gfx* dlEnd, s32 recvMesg);
void texrect_draw(Gfx **dList, DrawTexture *element, s32 xPos, s32 yPos, u8 red, u8 green, u8 blue,
                               u8 alpha);
void bgdraw_chequer(Gfx** dList);
void bgdraw_render(Gfx **dList, Matrix *mtx, s32 drawBG);
void bgdraw_set_func(void *func);
void texrect_draw_scaled(Gfx **dlist, DrawTexture *element, f32 xPos, f32 yPos, f32 xScale, f32 yScale, u32 colour, s32 flags);

//Non Matching
void func_80078190(Gfx **dlist);

#endif
