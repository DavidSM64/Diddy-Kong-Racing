#ifndef _UNKNOWN_078050_H_
#define _UNKNOWN_078050_H_

#include "types.h"
#include "structs.h"
#include "f3ddkr.h"
#include "sched.h"
#include "libultra_internal.h"

#include "game_ui.h"
#include "video.h"

typedef union {
    void (*function)(Gfx*, Mtx *);
    void *ptr;
} unk800DE4D0;

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

extern u8 sBackgroundPrimColourR;
extern u8 sBackgroundPrimColourG;
extern u8 sBackgroundPrimColourB;
extern s32 sBackgroundFillColour;

extern u32 D_800DE4C0;
extern u32 D_800DE4C4;
extern u32 D_800DE4C8;
extern s32 D_800DE4CC;

extern s32 gfxBufCounter;
extern s32 gfxBufCounter2;
extern s32 gGfxTaskIsRunning;

// Defined in dkr.ld
extern s8 rspF3DDKRDramStart[];
extern s8 rspF3DDKRBootStart[];
extern s8 rspF3DDKRXbusStart[];
extern s8 rspF3DDKRDataXbusStart[];
extern s8 rspF3DDKRFifoStart[];
extern s8 rspF3DDKRDataFifoStart[];

s32 wait_for_gfx_task(void);
void func_80077AAC(void *bufPtr, s32 arg1, UNUSED s32 arg2);
void set_background_prim_colour(u8 arg0, u8 arg1, u8 arg2);
void set_background_fill_colour(s32 red, s32 green, s32 blue);
void init_rdp_and_framebuffer(Gfx **dlist);
void init_rsp(Gfx **dlist);
void setup_gfx_mesg_queues(OSSched *sc);
void func_80078170(u32 arg0, u32 arg1, u32 arg2);
s32 setup_ostask_xbus(Gfx* dlBegin, Gfx* dlEnd, s32 recvMesg);
void setup_ostask_fifo(Gfx* dlBegin, Gfx* dlEnd, s32 recvMesg);
void render_textured_rectangle(Gfx **dlist, DrawTexture *img, s32 xPos, s32 yPos, u8 red, u8 green, u8 blue, u8 alpha);
void func_800787FC(Gfx** arg0);
void render_background(Gfx **dlist, Mtx *mtx, s32 drawBG);
void func_80078AAC(void *arg0);

//Non Matching
void render_texture_rectangle_scaled(Gfx **dlist, DrawTexture *element, f32 x, f32 y, f32 x_scale, f32 y_scale, u32 color, s32 flip);
void func_80078190(Gfx **dlist);

#endif
