#ifndef _UNKNOWN_066AA0_H_
#define _UNKNOWN_066AA0_H_

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "f3ddkr.h"
#include "menu.h"
#include "libultra_internal.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH_HALF (SCREEN_WIDTH / 2)
#define SCREEN_HEIGHT_HALF (SCREEN_HEIGHT / 2)

#define SCREEN_WIDTH_FLOAT ((float)(SCREEN_WIDTH))
#define SCREEN_HEIGHT_FLOAT ((float)(SCREEN_HEIGHT))

#define CAMERA_ASPECT (SCREEN_WIDTH_FLOAT / SCREEN_HEIGHT_FLOAT)
#define CAMERA_FAR 15000.0f
#define CAMERA_NEAR 10.0f
#define CAMERA_DEFAULT_FOV 60.0f
#define CAMERA_MIN_FOV 0.0f
#define CAMERA_MAX_FOV 90.0f
#define CAMERA_SCALE 1.0f

enum ViewportCount {
    VIEWPORTS_COUNT_1_PLAYER,
    VIEWPORTS_COUNT_2_PLAYERS,
    VIEWPORTS_COUNT_3_PLAYERS,
    VIEWPORTS_COUNT_4_PLAYERS
};

extern s8 D_800DD060;

/* Size: 0x34 bytes. */
typedef struct ScreenViewport {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 upperLeftX; //gDPFillRectangle values
    /* 0x24 */ s32 upperLeftY;
    /* 0x28 */ s32 lowerRightX;
    /* 0x2C */ s32 lowerRightY;
    /* 0x30 */ s32 flags;
} ScreenViewport;

/* Size: 6 bytes */
typedef struct unk80121110 {
    u16 unk0;
    s8 unk2;
    s8 unk3;
    s8 unk4;
    s8 unk6;
} unk80121110;

extern ScreenViewport gScreenViewports[4];

// Not sure about the typing here
extern s16 D_800DD138[8];

// RSP Viewports
extern Vp D_800DD148[20]; 

extern unk8011D510 D_800DD288;

extern unk8011D510 D_800DD2A0;

extern Matrix D_800DD2B8;

extern u8 D_800DD2F8[8];

extern s32 D_800DD300;

extern s16 gButtonMask;

extern s32 D_A4000000;

extern s32 SP_IMEM;

//TODO: Figure out where these functions live: unknown_070110?
    void func_8006F870(Matrix, Matrix); //unknown_070110
    void func_800705F8(s32, f32, f32, f32); //From unknown_070110
    void func_8006FE74(Matrix *, unk8011D510 *); // Non Matching unknown_070110?
    void func_8006F768(Matrix *, Matrix *, Matrix *); // Non Matching unknown_070110?

f32 sqrtf(f32); //IDO?

void func_80066060(s32 arg0, s32 arg1);
void func_80066098(s8 arg0);
void func_800660C0(void);
void func_800660D0(void);
f32 get_current_camera_fov(void);
void update_camera_fov(f32 camFieldOfView);
void func_80066194(void);
Matrix *func_80066204(void);
s32 get_viewport_count(void);
s32 func_80066220(void);
void func_80066CDC(Gfx **dlist, s32 arg1);
void func_80066230(Gfx **dlist, s32 arg1);
f32 func_80066348(f32 arg0, f32 arg1, f32 arg2);
void func_800663DC(s32 xPos, s32 yPos, s32 zPos, s32 arg3, s32 arg4, s32 arg5);
void func_80066488(s32 arg0, f32 xPos, f32 yPos, f32 zPos, s16 arg4, s16 arg5, s16 arg6);
void func_80066520(void);
s8 func_80066510(void);
s32 func_8006652C(s32 arg0);
void func_800665E8(s32 arg0);
void func_80066818(s32 viewPortIndex, s32 arg1);
void func_80066894(s32 viewPortIndex, s32 arg1);
s32 func_80066910(s32 viewPortIndex);
void func_80066940(s32 viewPortIndex, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_80066AA8(s32 viewPortIndex, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_80066BA8(s32 viewPortIndex, s32 *upperLeftX, s32 *upperLeftY, s32 *lowerRightX, s32 *lowerRightY);
void func_80066C2C(s32 viewPortIndex, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4);
void func_80066C80(s32 *arg0, s32 *arg1, s32 *arg2, s32 *arg3);
void func_80066CDC(Gfx **dlist, s32 arg1);
void func_80067F20(f32 arg0);
void func_80067F2C(Gfx **dlist, s32 *arg1);
void func_8006807C(Gfx **dlist, s32 *arg1);
void func_80068158(Gfx **dlist, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_800682AC(Gfx **dlist);
void func_80068408(Gfx **dlist, s32 *arg1);
void func_80068508(s32 arg0);
unk80120AC0 *func_80069CFC(void);
unk80120AC0 *func_80069D20(void);
unk80120AC0 *func_80069D7C(void);
Matrix *func_80069DA4(void);
Matrix *func_80069DB0(void);
Matrix *func_80069DBC(void);
f32 func_80069DC8(f32 x, f32 y, f32 z);
void func_80069E14(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_80069F28(f32 arg0);
void func_8006A03C(f32 *mtx);
OSMesgQueue *func_8006A100(void);
void func_8006A434(void);
void func_8006A458(s8 *activePlayers);
u8 func_8006A4F8(s32 arg0);
void func_8006A50C(void);
u16 get_buttons_held_from_player(s32 arg0);
u16 get_buttons_pressed_from_player(s32 arg0);
u16 func_8006A578(s32 arg0);
s32 func_8006A59C(s32 arg0);
s32 func_8006A5E0(s32 arg0);
s32 func_8006A624(s8 arg0);
void disable_button_mask(void);

// Non Matching
void func_80067A3C(Gfx **dlist);

#endif
