#ifndef _UNKNOWN_078050_H_
#define _UNKNOWN_078050_H_

#include "types.h"
#include "structs.h"
#include "f3ddkr.h"
#include "sched.h"
#include "libultra_internal.h"

#include "game_ui.h"
#include "video.h"

#define SEGMENT_DEPTH_BUFFER 0x02000000
#define SEGMENT_COLOUR_BUFFER 0x01000000
#define FIFO_BUFFER_SIZE 0x18000

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
} DKR_OSTask;

extern OSMesgQueue gGfxTaskMesgQueue;

extern u8 sBackgroundPrimColourR;
extern u8 sBackgroundPrimColourG;
extern u8 sBackgroundPrimColourB;
extern s32 sBackgroundFillColour;

extern TextureHeader *D_800DE4C4;
extern TextureHeader *D_800DE4C8;
extern s32 gChecquerBGEnabled;

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

void wait_for_gfx_task(void);
void func_80077AAC(void *bufPtr, s32 arg1, UNUSED s32 arg2);
void set_background_prim_colour(u8 arg0, u8 arg1, u8 arg2);
void set_background_fill_colour(s32 red, s32 green, s32 blue);
void init_rdp_and_framebuffer(Gfx **dlist);
void init_rsp(Gfx **dlist);
void setup_gfx_mesg_queues(OSSched *sc);
void func_80078170(TextureHeader *arg0, TextureHeader *arg1, u32 arg2);
s32 setup_ostask_xbus(Gfx* dlBegin, Gfx* dlEnd, s32 recvMesg);
void setup_ostask_fifo(Gfx* dlBegin, Gfx* dlEnd, s32 recvMesg);
void render_textured_rectangle(Gfx **dlist, DrawTexture *img, s32 xPos, s32 yPos, u8 red, u8 green, u8 blue, u8 alpha);
void render_chequer_background(Gfx** dList);
void render_background(Gfx **dlist, Matrix *mtx, s32 drawBG);
void set_background_draw_function(void *arg0);
void render_texture_rectangle_scaled(Gfx **dlist, DrawTexture *element, f32 xPos, f32 yPos, f32 xScale, f32 yScale, u32 colour, s32 flags);

//Non Matching
void func_80078190(Gfx **dlist);

#endif
