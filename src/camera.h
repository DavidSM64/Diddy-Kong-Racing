#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "f3ddkr.h"
#include "menu.h"
#include "libultra_internal.h"
#include "math.h"

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

#define CONTROLLER_MISSING -1
#define CONTROLLER_EXISTS   0

#define JOYSTICK_DEADZONE 8
#define JOYSTICK_MAX_RANGE 70

#define VIEWPORT_AUTO 0x8000

enum ViewportCount {
    VIEWPORTS_COUNT_1_PLAYER,
    VIEWPORTS_COUNT_2_PLAYERS,
    VIEWPORTS_COUNT_3_PLAYERS,
    VIEWPORTS_COUNT_4_PLAYERS
};

enum ViewPortFlags {
    VIEWPORT_UNK_01        = 0x0001,
    VIEWPORT_UNK_02        = 0x0002,
    VIEWPORT_UNK_04        = 0x0004,
    VIEWPORT_X_CUSTOM      = 0x0008,
    VIEWPORT_Y_CUSTOM      = 0x0010,
    VIEWPORT_WIDTH_CUSTOM  = 0x0020,
    VIEWPORT_HEIGHT_CUSTOM = 0x0040,
};

extern s8 D_800DD060;

/* Size: 0x34 bytes. */
typedef struct ScreenViewport {
    /* 0x00 */ s32 x1;
    /* 0x04 */ s32 y1;
    /* 0x08 */ s32 x2;
    /* 0x0C */ s32 y2;
    /* 0x10 */ s32 posX;
    /* 0x14 */ s32 posY;
    /* 0x18 */ s32 width;
    /* 0x1C */ s32 height;
    /* 0x20 */ s32 scissorX1;
    /* 0x24 */ s32 scissorY1;
    /* 0x28 */ s32 scissorX2;
    /* 0x2C */ s32 scissorY2;
    /* 0x30 */ s32 flags;
} ScreenViewport;

/* Size: 6 bytes */
typedef struct ControllerData {
    u16 buttonData; // Buttons
    s8 rawStickX;
    s8 rawStickY;
    s8 unk4;
    s8 unk6;
} ControllerData;

extern ScreenViewport gScreenViewports[4];

// Not sure about the typing here
extern s16 D_800DD138[8];

// RSP Viewports
extern Vp D_800DD148[20];

extern ObjectTransform D_800DD288;

extern ObjectTransform D_800DD2A0;

extern Matrix gOrthoMatrix;

extern u8 D_800DD2F8[8];

extern s16 gButtonMask;

//TODO: Figure out where these functions live: unknown_070110?
    void func_8006F870(Matrix *, Matrix *); //unknown_070110
    void func_800705F8(Matrix *, f32, f32, f32); //From unknown_070110
    void func_8006FE74(Matrix *, ObjectTransform *); // Non Matching unknown_070110?
    void func_8006F768(Matrix *, Matrix *, Matrix *); // Non Matching unknown_070110?

void func_80066060(s32 arg0, s32 arg1);
void func_80066098(s8 arg0);
void func_800660C0(void);
void func_800660D0(void);
UNUSED f32 get_current_camera_fov(void);
void update_camera_fov(f32 camFieldOfView);
UNUSED void calculate_camera_perspective(void);
Matrix *func_80066204(void);
s32 get_viewport_count(void);
s32 func_80066220(void);
void func_80066CDC(Gfx **dlist, Gfx **arg1);
void func_80066230(Gfx **dlist, Gfx **arg1);
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
void func_80066940(s32 viewPortIndex, s32 x1, s32 y1, s32 x2, s32 y2);
void set_viewport_properties(s32 viewPortIndex, s32 x1, s32 x2, s32 y1, s32 y2);
s32 copy_viewport_background_size_to_coords(s32 viewPortIndex, s32 *x1, s32 *y1, s32 *x2, s32 *y2);
void copy_viewport_frame_size_to_coords(s32 viewPortIndex, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4);
void copy_framebuffer_size_to_coords(s32 *x1, s32 *y1, s32 *x2, s32 *y2);
void set_ortho_matrix_height(f32 value);
void func_80067F2C(Gfx **dlist, s32 *arg1);
void func_8006807C(Gfx **dlist, s32 *arg1);
void func_80068158(Gfx **dlist, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_800682AC(Gfx **dlist);
void func_80068408(Gfx **dlist, s32 *arg1);
void func_80068508(s32 arg0);
ObjectSegment *func_80069CFC(void);
ObjectSegment *func_80069D20(void);
ObjectSegment *func_80069D7C(void);
Matrix *func_80069DA4(void);
Matrix *func_80069DB0(void);
Matrix *func_80069DBC(void);
f32 func_80069DC8(f32 x, f32 y, f32 z);
void func_80069E14(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_80069F28(f32 arg0);
UNUSED void debug_print_float_matrix_values(f32 *mtx);
OSMesgQueue *get_si_mesg_queue(void);
void initialise_player_ids(void);
void assign_player_ids(s8 *activePlayers);
u8 get_player_id(s32 player);
void swap_player_1_and_2_ids(void);
u16 get_buttons_held_from_player(s32 player);
u32 get_buttons_pressed_from_player(s32 player);
UNUSED u16 get_buttons_released_from_player(s32 player);
s8 clamp_joystick_x_axis(s32 player);
s8 clamp_joystick_y_axis(s32 player);
s8 clamp_joystick(s8 stickMag);
void disable_button_mask(void);
s32 init_controllers(void);

// Non Matching
void func_80067A3C(Gfx **dlist);
void func_80066610(void);
void func_80066CDC(Gfx **dlist, Gfx **arg1);
void func_80065EA0(void);
s32 func_8006A1C4(s32 arg0, s32 logicUpdateRate);

#endif
