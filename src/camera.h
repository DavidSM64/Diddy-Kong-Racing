#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "f3ddkr.h"
#include "menu.h"
#include <ultra64.h>
#include "libc/math.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_HEIGHT_PAL (SCREEN_HEIGHT + 44)
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
    s16 textureCount;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    Gfx *unk8[1];
} unk80068514_arg4;

void func_80066060(s32 cameraID, s32 zoomLevel);
void set_viewport_tv_type(s8 setting);
void func_800660C0(void);
void func_800660D0(void);
UNUSED f32 get_current_camera_fov(void);
void update_camera_fov(f32 camFieldOfView);
Matrix *matrix_get_model_s16(void);
s32 get_viewport_count(void);
s32 get_current_viewport(void);
void camera_init_tracks_menu(Gfx **dList, MatrixS **mtxS);
f32 get_distance_to_active_camera(f32 xPos, f32 yPos, f32 zPos);
void camera_reset(s32 xPos, s32 yPos, s32 zPos, s32 angleZ, s32 angleX, s32 angleY);
void write_to_object_render_stack(s32 stackPos, f32 xPos, f32 yPos, f32 zPos, s16 arg4, s16 arg5, s16 arg6);
void disable_cutscene_camera(void);
s8 check_if_showing_cutscene_camera(void);
s32 set_active_viewports_and_max(s32 num);
void set_active_camera(s32 num);
void camEnableUserView(s32 viewPortIndex, s32 arg1);
void camDisableUserView(s32 viewPortIndex, s32 arg1);
s32 check_viewport_background_flag(s32 viewPortIndex);
void viewport_menu_set(s32 viewPortIndex, s32 x1, s32 y1, s32 x2, s32 y2);
void set_viewport_properties(s32 viewPortIndex, s32 posX, s32 posY, s32 width, s32 height);
s32 copy_viewport_background_size_to_coords(s32 viewPortIndex, s32 *x1, s32 *y1, s32 *x2, s32 *y2);
void copy_viewport_frame_size_to_coords(s32 viewPortIndex, s32 *x1, s32 *y1, s32 *x2, s32 *y2);
void copy_framebuffer_size_to_coords(s32 *x1, s32 *y1, s32 *x2, s32 *y2);
void set_ortho_matrix_height(f32 value);
void set_ortho_matrix_view(Gfx **dlist, MatrixS **mtx);
void func_8006807C(Gfx **dlist, MatrixS **mtx);
void viewport_rsp_set(Gfx **dlist, s32 width, s32 height, s32 posX, s32 posY);
void viewport_reset(Gfx **dlist);
void matrix_world_origin(Gfx **dlist, MatrixS **mtx);
void sprite_anim_off(s32 setting);
ObjectSegment *get_active_camera_segment_no_cutscenes(void);
ObjectSegment *get_active_camera_segment(void);
ObjectSegment *get_cutscene_camera_segment(void);
Matrix *get_projection_matrix_f32(void);
MatrixS *get_projection_matrix_s16(void);
Matrix *get_camera_matrix(void);
f32 get_distance_to_camera(f32 x, f32 y, f32 z);
void set_camera_shake_by_distance(f32 x, f32 y, f32 z, f32 dist, f32 magnitude);
void set_camera_shake(f32 magnitude);
void func_80067D3C(Gfx **dlist, MatrixS **mats);
void render_ortho_triangle_image(Gfx **dList, MatrixS **mtx, Vertex **vtx, ObjectSegment *segment, Sprite *sprite, s32 flags);
s32 render_sprite_billboard(Gfx **dlist, MatrixS **mtx, Vertex **vertexList, Object *obj, unk80068514_arg4 *arg4, s32 flags);
void camera_push_model_mtx(Gfx **dList, MatrixS **mtx, ObjectTransform *trans, f32 scale, f32 scaleY);
void viewport_scissor(Gfx **dlist);
void apply_matrix_from_stack(Gfx **dlist);
void copy_viewports_to_stack(void);
void apply_head_turning_matrix(Gfx **dlist, MatrixS **mtx, Object_68 *objGfx, s16 headAngle);
void apply_object_shear_matrix(Gfx **dList, MatrixS **mtx, Object *arg2, Object *arg3, f32 shear);

// Non Matching
void camera_init(void);
void func_80066CDC(Gfx **dlist, MatrixS **mats);

#endif
