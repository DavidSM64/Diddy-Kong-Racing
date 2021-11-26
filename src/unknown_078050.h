#ifndef _UNKNOWN_078050_H_
#define _UNKNOWN_078050_H_

#include "types.h"
#include "structs.h"
#include "f3ddkr.h"
#include "sched.h"
#include "libultra_internal.h"

typedef union {
    void (*function)(Gfx*, s32);
    void *ptr;
} unk800DE4D0;

extern s16 D_800DE490[16];

extern u8 D_800DE4B0;
extern u8 D_800DE4B4;
extern u8 D_800DE4B8;
extern s32 D_800DE4BC;

extern u32 D_800DE4C0;
extern u32 D_800DE4C4;
extern u32 D_800DE4C8;
extern s32 D_800DE4CC;

extern s32 D_800DE4D4;
extern s32 D_800DE4D8;
extern s32 D_800DE4DC;

s32 func_80077A54(void);
void func_80077AAC(void *bufPtr, s32 arg1, s32 arg2);
void func_80077B34(u8 arg0, u8 arg1, u8 arg2);
void func_80077B5C(s32 red, s32 green, s32 blue);
void init_rdp_and_framebuffer(Gfx **dlist);
void init_rsp(Gfx **dlist);
void func_80078100(OSSched *sc);
void func_80078170(u32 arg0, u32 arg1, u32 arg2);
void func_80078778(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_800787F0(void);

//Non Matching
void render_background(Gfx **dlist, s32 *arg1, s32 arg2);
void render_textured_rectangle(Gfx **dlist, DrawTexture *arg1,
	s32 arg2, s32 arg3, u8 red, u8 green, u8 blue, u8 alpha);
void func_80078D00(Gfx**, void *element, s32, s32, f32, f32, u32, s32);

#endif
