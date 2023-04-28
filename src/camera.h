#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "f3ddkr.h"
#include "menu.h"
#include "libultra_internal.h"
#include "libc/math.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH_HALF (SCREEN_WIDTH / 2)
#define SCREEN_HEIGHT_HALF (SCREEN_HEIGHT / 2)
#define SCREEN_HEIGHT_HALF_PAL (SCREEN_HEIGHT_HALF + 12)

#define SCREEN_WIDTH_FLOAT ((float)(SCREEN_WIDTH))
#define SCREEN_HEIGHT_FLOAT ((float)(SCREEN_HEIGHT))
#define SCREEN_WIDTH_FLOAT_HALF ((float)SCREEN_WIDTH / 2)
#define SCREEN_HEIGHT_FLOAT_HALF ((float)SCREEN_HEIGHT / 2)

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
    VIEWPORT_EXTRA_BG      = 0x0001, //official name (guessed): VIEWPORT_IS_USER_VIEW
    VIEWPORT_UNK_02        = 0x0002,
    VIEWPORT_UNK_04        = 0x0004,
    VIEWPORT_X_CUSTOM      = 0x0008,
    VIEWPORT_Y_CUSTOM      = 0x0010,
    VIEWPORT_WIDTH_CUSTOM  = 0x0020,
    VIEWPORT_HEIGHT_CUSTOM = 0x0040
};

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

typedef struct unk80068514_arg4 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    Gfx *unk8[1];
} unk80068514_arg4;

void func_80066060(s32 arg0, s32 arg1);
void set_viewport_tv_type(s8 arg0);
void func_800660C0(void);
void func_800660D0(void);
UNUSED f32 get_current_camera_fov(void);
void update_camera_fov(f32 camFieldOfView);
UNUSED void calculate_camera_perspective(void);
Matrix *func_80066204(void);
s32 get_viewport_count(void);
s32 get_current_viewport(void);
void func_80066230(Gfx **dlist, MatrixS **arg1);
f32 get_distance_to_active_camera(f32 xPos, f32 yPos, f32 zPos);
void func_800663DC(s32 xPos, s32 yPos, s32 zPos, s32 arg3, s32 arg4, s32 arg5);
void write_to_object_render_stack(s32 arg0, f32 xPos, f32 yPos, f32 zPos, s16 arg4, s16 arg5, s16 arg6);
void disable_cutscene_camera(void);
s8 check_if_showing_cutscene_camera(void);
s32 set_active_viewports_and_max(s32 arg0);
void set_active_camera(s32 arg0);
void camEnableUserView(s32 viewPortIndex, s32 arg1);
void camDisableUserView(s32 viewPortIndex, s32 arg1);
s32 check_viewport_background_flag(s32 viewPortIndex);
void resize_viewport(s32 viewPortIndex, s32 x1, s32 y1, s32 x2, s32 y2);
void set_viewport_properties(s32 viewPortIndex, s32 x1, s32 x2, s32 y1, s32 y2);
s32 copy_viewport_background_size_to_coords(s32 viewPortIndex, s32 *x1, s32 *y1, s32 *x2, s32 *y2);
void copy_viewport_frame_size_to_coords(s32 viewPortIndex, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4);
void copy_framebuffer_size_to_coords(s32 *x1, s32 *y1, s32 *x2, s32 *y2);
void set_ortho_matrix_height(f32 value);
void set_ortho_matrix_view(Gfx **dlist, MatrixS **mats);
void func_8006807C(Gfx **dlist, MatrixS **mats);
void func_80068158(Gfx **dlist, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_800682AC(Gfx **dlist);
void func_80068408(Gfx **dlist, MatrixS **mats);
void func_80068508(s32 arg0);
ObjectSegment *get_active_camera_segment_no_cutscenes(void);
ObjectSegment *get_active_camera_segment(void);
ObjectSegment *get_cutscene_camera_segment(void);
Matrix *func_80069DA4(void);
MatrixS *func_80069DB0(void);
Matrix *func_80069DBC(void);
f32 func_80069DC8(f32 x, f32 y, f32 z);
void set_camera_shake_by_distance(f32 x, f32 y, f32 z, f32 dist, f32 magnitude);
void set_camera_shake(f32 magnitude);
void func_80067D3C(Gfx **dlist, MatrixS **mats);
void render_ortho_triangle_image(Gfx **dList, MatrixS **mtx, Vertex **vtx, ObjectSegment *segment, Sprite *sprite, s32 flags);
s32 render_sprite_billboard(Gfx **dlist, MatrixS **mtx, Vertex **vertexList, Object *obj, unk80068514_arg4 *arg4, s32 flags);
void camera_push_model_mtx(Gfx **arg0, MatrixS **arg1, ObjectTransform *arg2, f32 arg3, f32 arg4);
void set_viewport_scissor(Gfx **dlist);
void func_80069A40(Gfx **dlist);
void copy_viewports_to_stack(void);
void func_80069790(Gfx **dlist, MatrixS **mtx, Object_68 *obj68, s16 headAngle);
void func_80068FA8(Gfx **dlist, MatrixS **mtx, Object *arg2, Object *arg3, f32 shear);

// Non Matching
void func_80065EA0(void);
void func_80066CDC(Gfx **dlist, MatrixS **mats);

#endif
