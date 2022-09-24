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
    void (*function)(Gfx*, s32);
    void *ptr;
} unk800DE4D0;

typedef struct DKR_OSTask {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    OSTask_t task; // Size: 0x40 bytes
    OSMesgQueue *unk50;
    s32 unk54;
    s32 unk58;
    s32 unk5C;
    s32 unk60;
    s32 unk64;
    s32 unk68;
    s32 unk6C;
} DKR_OSTask;

extern s16 D_800DE490[16];

extern u8 sBackgroundPrimColourR;
extern u8 sBackgroundPrimColourG;
extern u8 sBackgroundPrimColourB;
extern s32 sBackgroundFillColour;

extern u32 D_800DE4C0;
extern u32 D_800DE4C4;
extern u32 D_800DE4C8;
extern s32 D_800DE4CC;

extern s32 D_800DE4D4;
extern s32 D_800DE4D8;
extern s32 D_800DE4DC;

// Defined in dkr.ld
extern s8 rspF3DDKRDramStart[];
extern s8 rspF3DDKRBootStart[];
extern s8 rspF3DDKRXbusStart[];
extern s8 rspF3DDKRDataXbusStart[];
extern s8 rspF3DDKRFifoStart[];
extern s8 rspF3DDKRDataFifoStart[];

s32 func_80077A54(void);
void func_80077AAC(void *bufPtr, s32 arg1, UNUSED s32 arg2);
void set_background_prim_colour(u8 arg0, u8 arg1, u8 arg2);
void set_background_fill_colour(s32 red, s32 green, s32 blue);
void init_rdp_and_framebuffer(Gfx **dlist);
void init_rsp(Gfx **dlist);
void func_80078100(OSSched *sc);
void func_80078170(u32 arg0, u32 arg1, u32 arg2);
void func_80078778(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_800787F0(void);

//Non Matching
void render_background(Gfx **dlist, s32 *arg1, s32 arg2);
void render_textured_rectangle(Gfx **dlist, DrawTexture *arg1, s32 xPos, s32 yPos, u8 red, u8 green, u8 blue, u8 alpha);
void render_texture_rectangle_scaled(Gfx **dlist, DrawTexture *element, f32 x, f32 y, f32 x_scale, f32 y_scale, u32 color, s32 flip);
s32 setup_ostask_xbus(Gfx *, Gfx *, s32 arg2); // Not 100% sure about these types, but it matches what main_game_loop is sending.

#endif
