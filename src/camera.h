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
    VIEWPORT_LAYOUT_1_PLAYER,
    VIEWPORT_LAYOUT_2_PLAYERS,
    VIEWPORT_LAYOUT_3_PLAYERS,
    VIEWPORT_LAYOUT_4_PLAYERS
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

/* Size: 0x44 bytes */
typedef struct Camera {
    /* 0x0000 */ ObjectTransform trans;
    /* 0x0018 */ f32 cam_unk_18;
    /* 0x001C */ f32 boomLength;
    /* 0x0020 */ f32 cam_unk_20;
    /* 0x0024 */ f32 x_velocity;
    /* 0x0028 */ f32 y_velocity;
    /* 0x002C */ f32 z_velocity;
    /* 0x0030 */ f32 shakeMagnitude;
    /* 0x0034 */ s16 cameraSegmentID;
    /* 0x0036 */ s16 mode;
    /* 0x0038 */ s16 pitch;
    /* 0x003A */ s8 shakeTimer;
    /* 0x003B */ u8 zoom;
    /* 0x003C */ u8 unk3C;
    /* 0x003D */ u8 unk3D;
    /* 0x003E */ u8 unk3E;
    /* 0x003F */ u8 unk3F;
    /* 0x0040 */ ObjectHeader *header;
  } Camera;

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

void cam_set_zoom(s32 cameraID, s32 zoomLevel);
void set_viewport_tv_type(s8 setting);
void func_800660C0(void);
void func_800660D0(void);
UNUSED f32 cam_get_fov(void);
void cam_set_fov(f32 camFieldOfView);
Matrix *matrix_get_model_s16(void);
s32 cam_get_viewport_layout(void);
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
void set_ortho_matrix_view(Gfx **dList, MatrixS **mtx);
void func_8006807C(Gfx **dList, MatrixS **mtx);
void viewport_rsp_set(Gfx **dList, s32 width, s32 height, s32 posX, s32 posY);
void viewport_reset(Gfx **dList);
void matrix_world_origin(Gfx **dList, MatrixS **mtx);
void sprite_anim_off(s32 setting);
Camera *cam_get_active_camera_no_cutscenes(void);
Camera *cam_get_active_camera(void);
Camera *get_cutscene_camera_segment(void);
Matrix *get_projection_matrix_f32(void);
MatrixS *get_projection_matrix_s16(void);
Matrix *get_camera_matrix(void);
f32 get_distance_to_camera(f32 x, f32 y, f32 z);
void set_camera_shake_by_distance(f32 x, f32 y, f32 z, f32 dist, f32 magnitude);
void set_camera_shake(f32 magnitude);
void func_80067D3C(Gfx **dList, MatrixS **mats);
void render_ortho_triangle_image(Gfx **dList, MatrixS **mtx, Vertex **vtx, ObjectSegment *segment, Sprite *sprite, s32 flags);
s32 render_sprite_billboard(Gfx **dList, MatrixS **mtx, Vertex **vertexList, Object *obj, Sprite *arg4, s32 flags);
s32 camera_push_model_mtx(Gfx **dList, MatrixS **mtx, ObjectTransform *trans, f32 scaleY, f32 offsetY);
void viewport_scissor(Gfx **dList);
void apply_matrix_from_stack(Gfx **dList);
void copy_viewports_to_stack(void);
void apply_head_turning_matrix(Gfx **dList, MatrixS **mtx, Object_68 *objGfx, s16 headAngle);
void apply_object_shear_matrix(Gfx **dList, MatrixS **mtx, Object *arg2, Object *arg3, f32 shear);
void cam_init(void);
void viewport_main(Gfx **dlist, MatrixS **mats);

#endif
