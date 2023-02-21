/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065EA0 */

#include "camera.h"
#include "audio.h"
#include "objects.h"
#include "game.h"
#include "unknown_0255E0.h"
#include "video.h"
#include "lib/src/libc/rmonPrintf.h"
#include "math_util.h"
#include "weather.h"

/************ .rodata ************/

UNUSED const char D_800E6F00[] = "Camera Error: Illegal mode!\n";
UNUSED const char D_800E6F20[] = "Camera Error: Illegal player no!\n";
UNUSED const char D_800E6F34[] = "cameraPushSprMtx: model stack overflow!!\n";
UNUSED const char D_800E6F70[] = "\nCam do 2D sprite called with NULL pointer!";
UNUSED const char D_800E6F9C[] = "CamDo2DSprite FrameNo Overflow !!!\n";
UNUSED const char D_800E6FC0[] = "cameraPushModelMtx: model stack overflow!!\n";
UNUSED const char D_800E6FEC[] = "camPushModelMtx: bsp stack overflow!!\n";
UNUSED const char D_800E7010[] = "camPopModelMtx: model stack negative overflow!!\n";
UNUSED const char D_800E7048[] = "camPopModelMtx: bsp stack negative overflow!!\n";

/*********************************/

/************ .data ************/

s8 gAntiPiracyViewport = FALSE;

// x1, y1, x2, y2
// posX, posY, width, height
// scissorX1, scissorY1, scissorX2, scissorY2
// flags
#define DEFAULT_VIEWPORT                                                \
    0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,                                  \
    SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF, SCREEN_WIDTH, SCREEN_HEIGHT, \
    0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1,                          \
    0

ScreenViewport gScreenViewports[4] = {
    { DEFAULT_VIEWPORT },
    { DEFAULT_VIEWPORT },
    { DEFAULT_VIEWPORT },
    { DEFAULT_VIEWPORT },
};

u32 gViewportWithBG = FALSE;

Vertex D_800DD138 = {
    0, 0, 0, 255, 255, 255, 255
};

//The viewport z-range below is half of the max (511)
#define G_HALFZ (G_MAXZ / 2) /* 9 bits of integer screen-Z precision */

// RSP Viewports
Vp gViewportStack[20] = {
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
};

ObjectTransform D_800DD288 = {
    0, 0, 0, 0, 1.0f, 0.0f, 0.0f, -281.0f,
};

ObjectTransform D_800DD2A0 = {
    0, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f,
};

Matrix gOrthoMatrix = {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 160.0f },
};

u8 D_800DD2F8[8] = {
    0, 0, 0, 0, 0, 0, 0, 0
};

/*******************************/

/************ .bss ************/

ObjectSegment gActiveCameraStack[8];
s32 gNumberOfViewports;
s32 gActiveCameraID;
s32 gViewportCap;
UNUSED s32 D_80120CEC;
ObjectTransform gCameraTransform;
s32 D_80120D08;
s32 D_80120D0C;
f32 gCurCamFOV;
s8 gCutsceneCameraActive;
s8 gAdjustViewportHeight;
s32 D_80120D18;
s32 D_80120D1C;
s32 D_80120D20;
UNUSED s32 D_80120D24;
f32 D_80120D28[6];
f32 D_80120D40[6];
f32 D_80120D58[5];
u16 perspNorm;
Matrix *D_80120D70[6];
MatrixS *D_80120D88[6];
Matrix D_80120DA0[5];
Matrix gPerspectiveMatrixF;
Matrix D_80120F20;
Matrix D_80120F60;
Matrix D_80120FA0;
MatrixS gPerspectiveMatrixS;
MatrixS D_80121020;
Matrix D_80121060;
Matrix D_801210A0;

/******************************/

#ifdef NON_EQUIVALENT
extern s32 D_B0000578;

void func_80065EA0(void) {
    s32 i, j;
    for (i = 0; i < 5; i++) {
        D_80120D70[i] = &D_80120DA0[i];
    };
    for (j = 0; j < 8; j++) {
        gActiveCameraID = j;
        func_800663DC(200, 200, 200, 0, 0, 180);
    };
    gCutsceneCameraActive = FALSE;
    gActiveCameraID = 0;
    D_80120D1C = 0;
    D_80120D20 = 0;
    gNumberOfViewports = 0;
    D_80120D0C = 0;
    D_80120D18 = 0;
    gAdjustViewportHeight = 0;
    gAntiPiracyViewport = 0;
    while (IO_READ(PI_STATUS_REG) & PI_STATUS_ERROR) {
    }
    if ((D_B0000578 & 0xFFFF) != 0x8965) {
        gAntiPiracyViewport = TRUE;
    }
    guPerspectiveF(gPerspectiveMatrixF, &perspNorm, CAMERA_DEFAULT_FOV, CAMERA_ASPECT, CAMERA_NEAR, CAMERA_FAR, CAMERA_SCALE);
    f32_matrix_to_s16_matrix(gPerspectiveMatrixF, gPerspectiveMatrixS);
    gCurCamFOV = CAMERA_DEFAULT_FOV;
}
#else
GLOBAL_ASM("asm/non_matchings/camera/func_80065EA0.s")
#endif

void func_80066060(s32 arg0, s32 arg1) {
    if (arg0 >= 0 && arg0 < 4) {
        D_800DD2F8[arg0] = arg1;
        gActiveCameraStack[arg0].unk38.byte.unk3B = arg1;
    }
}

/**
 * Set gAdjustViewportHeight to PAL mode if necessary, if setting is 1.
 * Otherwise, set it to 0, regardless of TV type.
*/
void set_viewport_tv_type(s8 setting) {
    if (osTvType == TV_TYPE_PAL) {
        gAdjustViewportHeight = setting;
    }
}

void func_800660C0(void) {
    D_80120D18 = 1;
}

void func_800660D0(void) {
    D_80120D18 = 0;
}

/**
 * Unused function that will return the current camera's FoV.
 * Official Name: camGetFOV
 */
UNUSED f32 get_current_camera_fov(void) {
    return gCurCamFOV;
}

/**
 * Set the FoV of the viewspace, then recalculate the perspective matrix.
 * Official Name: camSetFOV
 */
void update_camera_fov(f32 camFieldOfView) {
    if (CAMERA_MIN_FOV < camFieldOfView && camFieldOfView < CAMERA_MAX_FOV && camFieldOfView != gCurCamFOV) {
        gCurCamFOV = camFieldOfView;
        guPerspectiveF(gPerspectiveMatrixF, &perspNorm, camFieldOfView, CAMERA_ASPECT, CAMERA_NEAR, CAMERA_FAR, CAMERA_SCALE);
        f32_matrix_to_s16_matrix(&gPerspectiveMatrixF, &gPerspectiveMatrixS);
    }
}

/**
 * Unused function that recalculates the perspective matrix.
 */
UNUSED void calculate_camera_perspective(void) {
    guPerspectiveF(gPerspectiveMatrixF, &perspNorm, CAMERA_DEFAULT_FOV, CAMERA_ASPECT, CAMERA_NEAR, CAMERA_FAR, CAMERA_SCALE);
    f32_matrix_to_s16_matrix(&gPerspectiveMatrixF, &gPerspectiveMatrixS);
}

UNUSED Matrix *func_80066204(void) {
    return &D_801210A0;
}

/**
 * Returns the number of active viewports.
*/
s32 get_viewport_count(void) {
    return gNumberOfViewports;
}

/**
 * Return the index of the active view.
 * 0-3 is players 1-4, and 4-7 is the same, but with 4 added on for cutscenes.
*/
s32 get_current_viewport(void) {
    return gActiveCameraID;
}

void func_80066230(Gfx **dlist, MatrixS **mats) {
    ObjectSegment *cam;
    s16 angleY;
    s16 angleX;
    s16 angleZ;
    s16 sp24;
    f32 posX;
    f32 posY;
    f32 posZ;

    set_active_viewports_and_max(0);
    set_active_camera(0);
    cam = get_active_camera_segment();
    angleY = cam->trans.y_rotation;
    angleX = cam->trans.x_rotation;
    angleZ = cam->trans.z_rotation;
    posX = cam->trans.x_position;
    posY = cam->trans.y_position;
    posZ = cam->trans.z_position;
    sp24 = cam->unk38.half.unk38;
    cam->trans.z_rotation = 0;
    cam->trans.x_rotation = 0;
    cam->trans.y_rotation = -0x8000;
    cam->unk38.half.unk38 = 0;
    cam->trans.x_position = 0.0f;
    cam->trans.y_position = 0.0f;
    cam->trans.z_position = 0.0f;
    update_envmap_position(0.0f, 0.0f, -1.0f);
    func_80066CDC(dlist, mats);
    cam->unk38.half.unk38 = sp24;
    cam->trans.y_rotation = angleY;
    cam->trans.x_rotation = angleX;
    cam->trans.z_rotation = angleZ;
    cam->trans.x_position = posX;
    cam->trans.y_position = posY;
    cam->trans.z_position = posZ;
}

/**
 * Compare the coordinates passed through to the active camera and return the distance between them.
*/
f32 get_distance_to_active_camera(f32 xPos, f32 yPos, f32 zPos) {
    s32 index;
    f32 dx, dz, dy;

    index = gActiveCameraID;

    if (gCutsceneCameraActive) {
        index += 4;
    }

    dz = zPos - gActiveCameraStack[index].trans.z_position;
    dx = xPos - gActiveCameraStack[index].trans.x_position;
    dy = yPos - gActiveCameraStack[index].trans.y_position;
    return sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
}

void func_800663DC(s32 xPos, s32 yPos, s32 zPos, s32 arg3, s32 arg4, s32 arg5) {
    gActiveCameraStack[gActiveCameraID].trans.z_rotation = (s16) (arg3 * 0xB6);
    gActiveCameraStack[gActiveCameraID].trans.x_position = (f32) xPos;
    gActiveCameraStack[gActiveCameraID].trans.y_position = (f32) yPos;
    gActiveCameraStack[gActiveCameraID].trans.z_position = (f32) zPos;
    gActiveCameraStack[gActiveCameraID].trans.x_rotation = (s16) (arg4 * 0xB6);
    gActiveCameraStack[gActiveCameraID].unk38.half.unk38 = (s16) 0;
    gActiveCameraStack[gActiveCameraID].z_velocity = 0.0f;
    gActiveCameraStack[gActiveCameraID].unk28 = 0.0f;
    gActiveCameraStack[gActiveCameraID].unk2C.word = 0.0f;
    gActiveCameraStack[gActiveCameraID].unk30 = 0.0f;
    gActiveCameraStack[gActiveCameraID].x_velocity = 160.0f;
    gActiveCameraStack[gActiveCameraID].trans.y_rotation = (s16) (arg5 * 0xB6);
    gActiveCameraStack[gActiveCameraID].unk38.byte.unk3B = D_800DD2F8[gActiveCameraID];
}

/**
 * Write directly to the second set of object stack indeces.
 * The first 4 are reserved for the 4 player viewports, so the misc views, used in the title screen
 * and course previews instead use the next 4.
*/
void write_to_object_render_stack(s32 stackPos, f32 xPos, f32 yPos, f32 zPos, s16 arg4, s16 arg5, s16 arg6) {
    stackPos += 4;
    gActiveCameraStack[stackPos].unk38.half.unk38 = 0;
    gActiveCameraStack[stackPos].trans.x_position = xPos;
    gActiveCameraStack[stackPos].trans.y_position = yPos;
    gActiveCameraStack[stackPos].trans.z_position = zPos;
    gActiveCameraStack[stackPos].trans.y_rotation = arg4;
    gActiveCameraStack[stackPos].trans.x_rotation = arg5;
    gActiveCameraStack[stackPos].trans.z_rotation = arg6;
    gActiveCameraStack[stackPos].unk34_a.levelSegmentIndex = get_level_segment_index_from_position(xPos, yPos, zPos);
    gCutsceneCameraActive = TRUE;
}

/**
 * Check if the misc camera view is active.
 * Official name: camIsUserView
*/
s8 check_if_showing_cutscene_camera(void) {
    return gCutsceneCameraActive;
}

/**
 * Disable the cutscene camera, returning it to the conventional mode.
 * Official name: camSetUserView
*/
void disable_cutscene_camera(void) {
    gCutsceneCameraActive = FALSE;
}

/**
 * Sets the cap for the viewports. Usually reflecting how many there are.
 * If the number passed is within 1-4, then the stack cap is set to
 * how many active viewports there are.
*/
s32 set_active_viewports_and_max(s32 num) {
    if (num >= 0 && num < 4) {
        gNumberOfViewports = num;
    } else {
        gNumberOfViewports = 0;
    }
    switch (gNumberOfViewports) {
        case VIEWPORTS_COUNT_1_PLAYER:
            gViewportCap = 1;
            break;
        case VIEWPORTS_COUNT_2_PLAYERS:
            gViewportCap = 2;
            break;
        case VIEWPORTS_COUNT_3_PLAYERS:
            gViewportCap = 3;
            break;
        case VIEWPORTS_COUNT_4_PLAYERS:
            gViewportCap = 4;
            break;
    }
    if (gActiveCameraID >= gViewportCap) {
        gActiveCameraID = 0;
    }
    return gViewportCap;
}

/**
 * Sets the active viewport ID to the passed number.
 * If it's not within 1-4, then it's set to 0.
 * Official name: camSetView
*/
void set_active_camera(s32 num) {
    if (num >= 0 && num < 4) {
        gActiveCameraID = num;
    } else {
        gActiveCameraID = 0;
    }
}

/**
 * Takes the size of each view frame and writes them to the viewport stack, using values compatable with the RSP.
 * Only does this if extended backgrounds are enabled.
*/
void copy_viewports_to_stack(void) {
    s32 width;
    s32 height;
    s32 port;
    s32 yPos;
    s32 xPos;
    s32 i;

    gViewportWithBG = 1 - gViewportWithBG;
    for (i = 0; i < 4; i++) {
        if (gScreenViewports[i].flags & VIEWPORT_UNK_04) {
            gScreenViewports[i].flags &= ~VIEWPORT_EXTRA_BG;
        } else if (gScreenViewports[i].flags & VIEWPORT_UNK_02) {
            gScreenViewports[i].flags |= VIEWPORT_EXTRA_BG;
        }
        gScreenViewports[i].flags &= ~(VIEWPORT_UNK_02 | VIEWPORT_UNK_04);
        if (gScreenViewports[i].flags & VIEWPORT_EXTRA_BG) {
            if (!(gScreenViewports[i].flags & VIEWPORT_X_CUSTOM)) {
                xPos = (((gScreenViewports[i].x2 - gScreenViewports[i].x1) + 1) << 1) + (gScreenViewports[i].x1 * 4);
            } else {
                xPos = gScreenViewports[i].posX;
                xPos *= 4;
            }
            if (!(gScreenViewports[i].flags & VIEWPORT_Y_CUSTOM)) {
                yPos = (((gScreenViewports[i].y2 - gScreenViewports[i].y1 + 1)) << 1) + (gScreenViewports[i].y1 * 4);
            } else {
                yPos = gScreenViewports[i].posY;
                yPos *= 4;
            }
            if (!(gScreenViewports[i].flags & VIEWPORT_WIDTH_CUSTOM)) {
                width = gScreenViewports[i].x2 - gScreenViewports[i].x1;
                width += 1;
                width *= 2;
            } else {
                width = gScreenViewports[i].width;
                width *= 2;
            }
            if (!(gScreenViewports[i].flags & VIEWPORT_HEIGHT_CUSTOM)) {
                height = (gScreenViewports[i].y2 - gScreenViewports[i].y1) + 1;
                height *= 2;
            } else {
                height = gScreenViewports[i].height;
                height *= 2;
            }
            port = i + (gViewportWithBG * 5);
            port += 10;
            if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
                if (0) { } // Fakematch
                width = -width;
            }
            gViewportStack[port].vp.vtrans[0] = xPos;
            gViewportStack[port].vp.vtrans[1] = yPos;
            gViewportStack[port].vp.vscale[0] = width;
            gViewportStack[port].vp.vscale[1] = height;
        }
    }
}

void camEnableUserView(s32 viewPortIndex, s32 arg1) {
    if (arg1 != 0) {
        gScreenViewports[viewPortIndex].flags |= VIEWPORT_EXTRA_BG;
    } else {
        gScreenViewports[viewPortIndex].flags |= VIEWPORT_UNK_02;
    }
    gScreenViewports[viewPortIndex].flags &= ~VIEWPORT_UNK_04;
}

void camDisableUserView(s32 viewPortIndex, s32 arg1) {
    if (arg1 != 0) {
        gScreenViewports[viewPortIndex].flags &= ~VIEWPORT_EXTRA_BG;
    } else {
        gScreenViewports[viewPortIndex].flags |= VIEWPORT_UNK_04;
    }
    gScreenViewports[viewPortIndex].flags &= ~VIEWPORT_UNK_02;
}

/**
 * Return's the current viewport's flag status for extended backgrounds.
 * Required to draw some extra things used in menus.
*/
s32 check_viewport_background_flag(s32 viewPortIndex) {
    return gScreenViewports[viewPortIndex].flags & VIEWPORT_EXTRA_BG;
}

/**
 * Sets the intended viewport to the size passed through by arguments.
*/
void resize_viewport(s32 viewPortIndex, s32 x1, s32 y1, s32 x2, s32 y2) {
    s32 widthAndHeight, width, height;
    s32 temp;

    widthAndHeight = get_video_width_and_height_as_s32();
    height = GET_VIDEO_HEIGHT(widthAndHeight) & 0xFFFF;
    width = GET_VIDEO_WIDTH(widthAndHeight);

    if (x2 < x1) {
        temp = x1;
        x1 = x2;
        x2 = temp;
    }
    if (y2 < y1) {
        temp = y1;
        y1 = y2;
        y2 = temp;
    }

    if (x1 >= width || x2 < 0 || y1 >= height || y2 < 0) {
        gScreenViewports[viewPortIndex].scissorX1 = 0;
        gScreenViewports[viewPortIndex].scissorY1 = 0;
        gScreenViewports[viewPortIndex].scissorX2 = 0;
        gScreenViewports[viewPortIndex].scissorY2 = 0;
    } else {
        if (x1 < 0) {
            gScreenViewports[viewPortIndex].scissorX1 = 0;
        } else {
            gScreenViewports[viewPortIndex].scissorX1 = x1;
        }
        if (y1 < 0) {
            gScreenViewports[viewPortIndex].scissorY1 = 0;
        } else {
            gScreenViewports[viewPortIndex].scissorY1 = y1;
        }
        if (x2 >= width) {
            gScreenViewports[viewPortIndex].scissorX2 = width - 1;
        } else {
            gScreenViewports[viewPortIndex].scissorX2 = x2;
        }
        if (y2 >= height) {
            gScreenViewports[viewPortIndex].scissorY2 = height - 1;
        } else {
            gScreenViewports[viewPortIndex].scissorY2 = y2;
        }
    }
    gScreenViewports[viewPortIndex].y1 = y1;
    gScreenViewports[viewPortIndex].x1 = x1;
    gScreenViewports[viewPortIndex].x2 = x2;
    gScreenViewports[viewPortIndex].y2 = y2;
}

/**
 * Set the selected viewport's coordinate offsets and view size.
 * If you pass VIEWPORT_AUTO through, then the property will be automatically set when the game creates the viewports.
 */
void set_viewport_properties(s32 viewPortIndex, s32 posX, s32 posY, s32 width, s32 height) {
    if (posX != VIEWPORT_AUTO) {
        gScreenViewports[viewPortIndex].posX = posX;
        gScreenViewports[viewPortIndex].flags |= VIEWPORT_X_CUSTOM;
    } else {
        gScreenViewports[viewPortIndex].flags &= ~VIEWPORT_X_CUSTOM;
    }
    if (posY != VIEWPORT_AUTO) {
//!@bug Viewport Y writes to the X value. Luckily, all cases this function is called use VIEWPORT_AUTO,
// so this bug doesn't happen in practice.
        gScreenViewports[viewPortIndex].posX = posY;
        gScreenViewports[viewPortIndex].flags |= VIEWPORT_Y_CUSTOM;
    } else {
        gScreenViewports[viewPortIndex].flags &= ~VIEWPORT_Y_CUSTOM;
    }
    if (width != VIEWPORT_AUTO) {
        gScreenViewports[viewPortIndex].width = width;
        gScreenViewports[viewPortIndex].flags |= VIEWPORT_WIDTH_CUSTOM;
    } else {
        gScreenViewports[viewPortIndex].flags &= ~VIEWPORT_WIDTH_CUSTOM;
    }
    if (height != VIEWPORT_AUTO) {
        gScreenViewports[viewPortIndex].height = height;
        gScreenViewports[viewPortIndex].flags |= VIEWPORT_HEIGHT_CUSTOM;
    } else {
        gScreenViewports[viewPortIndex].flags &= ~VIEWPORT_HEIGHT_CUSTOM;
    }
}

/**
 * Sets the passed values to be equal to the selected viewports scissor size, before drawing the background elements.
 * Usually, this is the same size as the viewport's size.
 * Official name: camGetVisibleUserView
 */
s32 copy_viewport_background_size_to_coords(s32 viewPortIndex, s32 *x1, s32 *y1, s32 *x2, s32 *y2) {
    //gDPFillRectangle values
    *x1 = gScreenViewports[viewPortIndex].scissorX1;
    *x2 = gScreenViewports[viewPortIndex].scissorX2;
    *y1 = gScreenViewports[viewPortIndex].scissorY1;
    *y2 = gScreenViewports[viewPortIndex].scissorY2;
    if ((*x1 | *x2 | *y1 | *y2) == 0) {
        return 0;
    }
    return 1;
}

/**
 * Sets the passed values to the coordinate size of the passed viewport.
 * Official name: camGetUserView
 */
void copy_viewport_frame_size_to_coords(s32 viewPortIndex, s32 *x1, s32 *y1, s32 *x2, s32 *y2) {
    *x1 = gScreenViewports[viewPortIndex].x1;
    *y1 = gScreenViewports[viewPortIndex].y1;
    *x2 = gScreenViewports[viewPortIndex].x2;
    *y2 = gScreenViewports[viewPortIndex].y2;
}

/**
 * Unused function that sets the passed values to the framebuffer's size in coordinates.
 * Official name: camGetWindowLimits
 */
UNUSED void copy_framebuffer_size_to_coords(s32 *x1, s32 *y1, s32 *x2, s32 *y2) {
    u32 widthAndHeight = get_video_width_and_height_as_s32();
    *x1 = 0;
    *y1 = 0;
    *x2 = GET_VIDEO_WIDTH(widthAndHeight);
    *y2 = GET_VIDEO_HEIGHT(widthAndHeight);
}

#ifdef NON_EQUIVALENT

// Still a work-in-progress but it doesn't seem to cause any problems,
// which is why it is labeled under NON_EQUIVALENT

#define SCISSOR_INTERLACE G_SC_NON_INTERLACE

void func_80066CDC(Gfx **dlist, MatrixS **mats) {
    u32 sp58;
    u32 sp54;
    u32 sp4C;
    u32 temp_a2;
    u32 temp_a3;
    u32 temp_t0;
    u32 width;
    u32 widthAndHeight;
    u32 temp_v0_6;
    u32 phi_a1;
    u32 phi_t3;
    u32 phi_t5;
    u32 phi_t4;

    if (func_8000E184() && !gNumberOfViewports) {
        gActiveCameraID = 1;
    }
    widthAndHeight = get_video_width_and_height_as_s32();
    temp_t0 = widthAndHeight >> 16;
    temp_a3 = temp_t0 >> 1;
    if (gScreenViewports[gActiveCameraID].flags & VIEWPORT_EXTRA_BG) {
        gDPSetScissor((*dlist)++, SCISSOR_INTERLACE,
            gScreenViewports[gActiveCameraID].scissorX1,
            gScreenViewports[gActiveCameraID].scissorY1,
            gScreenViewports[gActiveCameraID].scissorX2,
            gScreenViewports[gActiveCameraID].scissorY2
        );
        func_80068158(dlist, 0, 0, 0, 0);
        if (mats != 0) {
            func_80067D3C(dlist, mats);
        }
        return;
    }
    width = GET_VIDEO_WIDTH(widthAndHeight);
    if (gNumberOfViewports == VIEWPORTS_COUNT_3_PLAYERS) {
        gNumberOfViewports = VIEWPORTS_COUNT_4_PLAYERS;
    }
    temp_a2 = width >> 1;
    sp54 = temp_a2;
    sp58 = temp_a3;
    if (osTvType == TV_TYPE_PAL) {
        sp58 = 0x91;
    }

    switch (gNumberOfViewports) {
        case VIEWPORTS_COUNT_1_PLAYER:
            phi_t3 = sp58;
            if (osTvType == TV_TYPE_PAL) {
                phi_t3 = sp58 - 0x12;
            }
            gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, 0, 0, width, temp_t0);
            sp4C = temp_a2;
            break;
        case VIEWPORTS_COUNT_2_PLAYERS:
            if (gActiveCameraID == 0) {
                temp_v0_6 = temp_t0 >> 2;
                phi_t3 = temp_v0_6;
                if (osTvType == TV_TYPE_PAL) {
                    phi_t3 = temp_v0_6 - 0xC;
                }
                gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, 0, 0, width, (temp_a3 - (temp_t0 >> 7)));
            } else {
                gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, 0, (temp_a3 + (temp_t0 >> 7)), width, (temp_t0 - (temp_t0 >> 7)));
                phi_t3 = temp_a3 + (temp_t0 >> 2);
            }
            sp4C = temp_a2;
            break;
        case VIEWPORTS_COUNT_3_PLAYERS:
            if (gActiveCameraID == 0) {
                gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, 0, 0, temp_a2 - (width >> 8), temp_t0);
                phi_a1 = width >> 2;
            } else {
                gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, temp_a2 + (width >> 8), 0, width - (width >> 8), temp_t0);
                phi_a1 = temp_a2 + (width >> 2);
            }
            sp4C = phi_a1;
            phi_t3 = sp58;
            break;
        case VIEWPORTS_COUNT_4_PLAYERS:
            sp58 = sp58 >> 1;
            sp54 = temp_a2 >> 1;
            switch (gActiveCameraID) {
                case 0:
                    gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, 0.0f, 0.0f, (temp_a2 - (width >> 8)), (temp_a3 - (temp_t0 >> 7)));
                    phi_t5 = 0;
                    phi_t4 = 0;
                case 1:
                    gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, (temp_a2 + (width >> 8)), 0, ((temp_a2 * 2) - (width >> 8)), (temp_a3 - (temp_t0 >> 7)));
                    phi_t5 = 0;
                    phi_t4 = temp_a2;
                    break;
                case 2:
                    gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, 0, temp_a3 + (temp_t0 >> 7), temp_a2 - (width >> 8), (temp_a3 * 2) - (temp_t0 >> 7));
                    phi_t5 = temp_a3;
                    phi_t4 = 0;
                    break;
                case 3:
                    gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, temp_a2 + (width >> 8), temp_a3 + (temp_t0 >> 7), (temp_a2 * 2) - (width >> 8), (temp_a3 * 2) - (temp_t0 >> 7));
                    phi_t5 = temp_a3;
                    phi_t4 = temp_a2;
                    break;
                default:
                    phi_t5 = 0;
                    phi_t4 = 0;
                    break;
            }
            phi_t3 = phi_t5 + sp58;
            sp4C = phi_t4 + sp54;
            if (osTvType == TV_TYPE_PAL) {
                phi_t3 -= 6;
                if (gActiveCameraID < 2) {
                    phi_t3 -= 0x14;
                }
            }
            break;
        default:
            //phi_t3 = sp50;
            phi_t3 = sp54;
            break;
    }

    if (osTvType == TV_TYPE_PAL) {
        sp4C -= 4;
    }
    func_80068158(dlist, sp54, sp58, sp4C, phi_t3);
    if (mats != 0) {
        func_80067D3C(dlist, mats);
    }
}

#else
GLOBAL_ASM("asm/non_matchings/camera/func_80066CDC.s")
#endif

/**
 * Takes the size of the screen as depicted by an active screen viewport, then sets the RDP scissor to match it.
 * Official Name: camSetScissor
*/
void set_viewport_scissor(Gfx **dlist) {
    s32 size;
    s32 lrx;
    s32 lry;
    s32 ulx;
    s32 uly;
    s32 numViewports;
    s32 temp;
    s32 temp2;
    s32 temp3;
    s32 temp4;
    s32 width;
    s32 height;

    size = get_video_width_and_height_as_s32();
    height = (u16) GET_VIDEO_HEIGHT(size);
    width = (u16) size;
    numViewports = gNumberOfViewports;

    if (numViewports != 0) {
        if (numViewports == VIEWPORTS_COUNT_3_PLAYERS) {
            numViewports = VIEWPORTS_COUNT_4_PLAYERS;
        }
        lrx = ulx = 0;
        lry = uly = 0;
        lrx += width;\
        lry += height;
        temp = lry >> 7;
        temp2 = lrx >> 8;
        temp4 = lrx >> 1;
        temp3 = lry >> 1;
        switch (numViewports) {
            case 1:
                switch (gActiveCameraID) {
                    case 0:
                        lry = temp3 - temp;
                        break;
                    default:
                        uly = temp3 + temp;
                        lry -= temp;
                        break;
                }
                break;

            case 2:
                switch (gActiveCameraID) {
                    case 0:
                        lrx = temp4 - temp2;
                        break;

                    default:
                        ulx = temp4 + temp2;
                        lrx -= temp2;
                        break;
                }
                break;

            case 3:
                switch (gActiveCameraID) {
                    case 0:
                        lrx = temp4 - temp2;\
                        lry = temp3 - temp;
                        break;

                    case 1:
                        ulx = temp4 + temp2;
                        lrx -= temp2;
                        lry = temp3 - temp;
                        break;

                    case 2:
                        uly = temp3 + temp;
                        lrx = temp4 - temp2;\
                        lry -= temp;
                        break;

                    case 3:
                        ulx = temp4 + temp2; \
                        uly = temp3 + temp;
                        lrx -= temp2; \
                        lry -= temp;
                        break;
                }
                break;
        }
        gDPSetScissor((*dlist)++, 0, ulx, uly, lrx, lry);
        return;
    }
    gDPSetScissor((*dlist)++, 0, 0, 0, width, height);
}

//Official Name: camGetPlayerProjMtx / camSetProjMtx - ??
void func_80067D3C(Gfx **dlist, UNUSED MatrixS **mats) {
    s32 temp;

    gSPPerspNormalize((*dlist)++, perspNorm);

    temp = gActiveCameraID;
    if (gCutsceneCameraActive) {
        gActiveCameraID += 4;
    }

    gCameraTransform.y_rotation = 0x8000 + gActiveCameraStack[gActiveCameraID].trans.y_rotation;
    gCameraTransform.x_rotation = gActiveCameraStack[gActiveCameraID].trans.x_rotation + gActiveCameraStack[gActiveCameraID].unk38.half.unk38;
    gCameraTransform.z_rotation = gActiveCameraStack[gActiveCameraID].trans.z_rotation;

    gCameraTransform.x_position = -gActiveCameraStack[gActiveCameraID].trans.x_position;
    gCameraTransform.y_position = -gActiveCameraStack[gActiveCameraID].trans.y_position;
    if (D_80120D18 != 0) {
        gCameraTransform.y_position -= gActiveCameraStack[gActiveCameraID].unk30;
    }
    gCameraTransform.z_position = -gActiveCameraStack[gActiveCameraID].trans.z_position;

    object_transform_to_matrix_2(D_80120F60, &gCameraTransform);
    f32_matrix_mult(&D_80120F60, &gPerspectiveMatrixF, &D_80120F20);

    gCameraTransform.y_rotation = -0x8000 - gActiveCameraStack[gActiveCameraID].trans.y_rotation;
    gCameraTransform.x_rotation = -(gActiveCameraStack[gActiveCameraID].trans.x_rotation + gActiveCameraStack[gActiveCameraID].unk38.half.unk38);
    gCameraTransform.z_rotation = -gActiveCameraStack[gActiveCameraID].trans.z_rotation;
    gCameraTransform.scale = 1.0f;
    gCameraTransform.x_position = gActiveCameraStack[gActiveCameraID].trans.x_position;
    gCameraTransform.y_position = gActiveCameraStack[gActiveCameraID].trans.y_position;
    if (D_80120D18 != 0) {
        gCameraTransform.y_position += gActiveCameraStack[gActiveCameraID].unk30;
    }
    gCameraTransform.z_position = gActiveCameraStack[gActiveCameraID].trans.z_position;

    object_transform_to_matrix(D_80120FA0, &gCameraTransform);
    f32_matrix_to_s16_matrix(&D_80120FA0, &D_80121020);

    gActiveCameraID = temp;
}

/**
 * Sets the Y value of the Y axis in the matrix to the passed value.
 * This is used to vertically scale ortho geometry to look identical across NTSC and PAL systems.
 * Official Name: camOrthoYAspect
 */
void set_ortho_matrix_height(f32 value) {
    gOrthoMatrix[1][1] = value;
}

/**
 * Sets the current matrix to represent an orthogonal view.
 * Used for drawing triangles on screen as HUD.
 * Official Name: camStandardOrtho
*/
void set_ortho_matrix_view(Gfx **dlist, MatrixS **mtx) {
    u32 widthAndHeight;
    s32 width, height;
    s32 i, j;

    widthAndHeight = get_video_width_and_height_as_s32();
    height = GET_VIDEO_HEIGHT(widthAndHeight);
    width = GET_VIDEO_WIDTH(widthAndHeight);
    f32_matrix_to_s16_matrix(&gOrthoMatrix, *mtx);
    D_80120D88[0] = *mtx;
    gViewportStack[gActiveCameraID + 5].vp.vscale[0] = width * 2;
    gViewportStack[gActiveCameraID + 5].vp.vscale[1] = width * 2;
    gViewportStack[gActiveCameraID + 5].vp.vtrans[0] = width * 2;
    gViewportStack[gActiveCameraID + 5].vp.vtrans[1] = height * 2;
    gSPViewport((*dlist)++, OS_K0_TO_PHYSICAL(&gViewportStack[gActiveCameraID + 5]));
    gSPMatrix((*dlist)++, OS_PHYSICAL_TO_K0((*mtx)++), G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    D_80120D1C = 0;
    D_80120D08 = 0;

    for (i = 0; i < 4; i++) {
        //Required to be one line, but the "\" fixes that.
        for (j = 0; j < 4; j++){ \
            D_80120F20[i][j] = gOrthoMatrix[i][j];
        }
    }
}

//Official Name: camStandardPersp?
void func_8006807C(Gfx **dlist, MatrixS **mtx) {
    object_transform_to_matrix_2(D_80121060, &D_800DD288);
    f32_matrix_mult(&D_80121060, &gPerspectiveMatrixF, &D_80120F20);
    object_transform_to_matrix_2((float (*)[4]) D_80120D70[0], &D_800DD2A0);
    f32_matrix_mult(D_80120D70[0], &D_80120F20, &D_80121060);
    f32_matrix_to_s16_matrix(&D_80121060, *mtx);
    gSPMatrix((*dlist)++, OS_PHYSICAL_TO_K0((*mtx)++), G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    D_80120D1C = 0;
    D_80120D08 = 0;
}

//Official Name: camSetViewport?
void func_80068158(Gfx **dlist, s32 width, s32 height, s32 posX, s32 posY) {
    s32 tempWidth = (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) ? -width : width;
    // Antipiracy measure. Flips the screen upside down.
    if (gAntiPiracyViewport) {
        height = -height;
        tempWidth = -width;
    }
    if (!(gScreenViewports[gActiveCameraID].flags & VIEWPORT_EXTRA_BG)) {
        gViewportStack[gActiveCameraID].vp.vtrans[0] = posX * 4;
        gViewportStack[gActiveCameraID].vp.vtrans[1] = posY * 4;
        gViewportStack[gActiveCameraID].vp.vscale[0] = tempWidth * 4;
        gViewportStack[gActiveCameraID].vp.vscale[1] = height * 4;
        gSPViewport((*dlist)++, OS_PHYSICAL_TO_K0(&gViewportStack[gActiveCameraID]));
    } else {
        gSPViewport((*dlist)++, OS_PHYSICAL_TO_K0(&gViewportStack[gActiveCameraID + 10 + (gViewportWithBG * 5)]));
    }
}

//Official Name: camResetView?
void func_800682AC(Gfx **dlist) {
    u32 widthAndHeight, width, height;
    gActiveCameraID = 4;
    widthAndHeight = get_video_width_and_height_as_s32();
    height = GET_VIDEO_HEIGHT(widthAndHeight);
    width = GET_VIDEO_WIDTH(widthAndHeight);
    if (!(gScreenViewports[gActiveCameraID].flags & VIEWPORT_EXTRA_BG)) {
        gDPSetScissor((*dlist)++, G_SC_NON_INTERLACE, 0, 0, width - 1, height - 1);
        func_80068158(dlist, width >> 1, height >> 1, width >> 1, height >> 1);
    } else {
        set_viewport_scissor(dlist);
        func_80068158(dlist, 0, 0, 0, 0);
    }
    gActiveCameraID = 0;
}

//Official Name: camOffsetZero?
void func_80068408(Gfx **dlist, MatrixS **mtx) {
    f32_matrix_from_position(D_80120D70[D_80120D1C], 0.0f, 0.0f, 0.0f);
    f32_matrix_mult(D_80120D70[D_80120D1C], &D_80120F20, &D_80121060);
    f32_matrix_to_s16_matrix(&D_80121060, *mtx);
    D_80120D88[D_80120D1C] = *mtx;
    gSPMatrix((*dlist)++, OS_PHYSICAL_TO_K0((*mtx)++), D_80120D08 << 6);
}

void func_80068508(s32 arg0) {
    D_80120D0C = arg0;
}

/**
 * Calculates angle from object to camera, then renders the sprite as a billboard, facing the camera.
 */
s32 render_sprite_billboard(Gfx **dlist, MatrixS **mtx, Vertex **vertexList, Object *obj, unk80068514_arg4 *arg4, s32 flags) {
    f32 sp5C;
    f32 sp58;
    Vertex *v;
    f32 sp50;
    f32 sp4C;
    f32 temp_f0;
    f32 sp44;
    f32 var_f20;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 result;
    s32 var_s2;

    result = TRUE;
    if (flags & RENDER_ANTI_ALIASING) {
        sp5C = D_80120D28[D_80120D20] - obj->segment.trans.x_position;
        sp58 = D_80120D40[D_80120D20] - obj->segment.trans.y_position;
        var_f20 = D_80120D58[D_80120D20] - obj->segment.trans.z_position;
        sp4C = sins_f(obj->segment.trans.y_rotation);
        temp_f0 = coss_f(obj->segment.trans.y_rotation);
        sp44 = (sp5C * temp_f0) + (var_f20 * sp4C);
        var_f20 = (var_f20 * temp_f0) - (sp5C * sp4C);
        sp38 = arctan2_f(sp44, sqrtf((sp58 * sp58) + (var_f20 * var_f20)));
        sp3C = -sins(arctan2_f(sp44, var_f20)) >> 8;
        if (var_f20 < 0.0f) {
            var_f20 = -var_f20;
            sp3C = 1 - sp3C;
            sp38 = -sp38;
        }
        sp34 = arctan2_f(sp58, var_f20);
        if (sp34 > 0x8000) {
            sp34 -= 0x10000;
        }
        sp34 = (sp34 * sp3C) >> 8;
        var_s2 = (sp38 >> 7) & 0xFF;
        if (var_s2 > 127) {
            var_s2 = 255 - var_s2;
            sp34 += 0x8000;
            result = FALSE;
        }
        var_s2 *= 2;
        sp5C = D_80120D28[D_80120D20] - obj->segment.trans.x_position;
        sp58 = D_80120D40[D_80120D20] - obj->segment.trans.y_position;
        var_f20 = D_80120D58[D_80120D20] - obj->segment.trans.z_position;
        sp50 = sqrtf((sp5C * sp5C) + (var_f20 * var_f20));
        gCameraTransform.y_rotation = arctan2_f(sp5C, var_f20);
        gCameraTransform.x_rotation = -arctan2_f(sp58, sp50);
        gCameraTransform.z_rotation = sp34;
        gCameraTransform.scale = obj->segment.trans.scale;
        gCameraTransform.x_position = obj->segment.trans.x_position;
        gCameraTransform.y_position = obj->segment.trans.y_position;
        gCameraTransform.z_position = obj->segment.trans.z_position;
        object_transform_to_matrix(D_80121060, &gCameraTransform);
        D_80120D1C++;
        f32_matrix_mult((Matrix *) D_80121060, (Matrix *) &D_80120D70[D_80120D1C-1][0][0], (Matrix *) &D_80120D70[D_80120D1C][0][0]);
        f32_matrix_mult(D_80120D70[D_80120D1C], (Matrix *) D_80120F20, (Matrix *) D_80121060);
        f32_matrix_to_s16_matrix((Matrix *) D_80121060, *mtx);
        D_80120D88[D_80120D1C] = *mtx;
        gSPMatrix((*dlist)++, OS_PHYSICAL_TO_K0((*mtx)++), 0x80);
        gSPVertexDKR((*dlist)++, OS_K0_TO_PHYSICAL(&D_800DD138), 1, 0);
    } else {
        v = *vertexList;
        v->x = obj->segment.trans.x_position;
        v->y = obj->segment.trans.y_position;
        v->z = obj->segment.trans.z_position;
        v->r = 255;
        v->g = 255;
        v->b = 255;
        v->a = 255;
        gSPVertexDKR((*dlist)++, OS_PHYSICAL_TO_K0(*vertexList), 1, 0);
        (*vertexList)++;
        if (gCutsceneCameraActive == 0) {
            sp34 = gActiveCameraStack[gActiveCameraID].trans.z_rotation + obj->segment.trans.z_rotation;
        } else {
            sp34 = gActiveCameraStack[gActiveCameraID + 4].trans.z_rotation + obj->segment.trans.z_rotation;
        }
        var_s2 = obj->segment.animFrame;
        D_80120D1C++;
        f32_matrix_from_rotation_and_scale((f32 (*)[4]) D_80120D70[D_80120D1C], sp34, obj->segment.trans.scale, gVideoAspectRatio);
        f32_matrix_to_s16_matrix(D_80120D70[D_80120D1C], *mtx);
        D_80120D88[D_80120D1C] = *mtx;
        gSPMatrix((*dlist)++, OS_PHYSICAL_TO_K0((*mtx)++), 0x80);
        gDkrEnableBillboard((*dlist)++);
    }
    if (D_80120D0C == 0) {
        var_s2 = ((var_s2 & 0xFF) * arg4->unk0) >> 8;
    }
    flags &= ~RENDER_ANTI_ALIASING;
    if (flags & RENDER_SEMI_TRANSPARENT) {
        flags |= RENDER_ANTI_ALIASING;
    }
    func_8007BF34(dlist, arg4->unk6 | (flags & (RENDER_FOG_ACTIVE | RENDER_SEMI_TRANSPARENT | RENDER_Z_COMPARE | RENDER_ANTI_ALIASING)));
    if (!(flags & RENDER_Z_UPDATE)) {
        gDPSetPrimColor((*dlist)++, 0, 0, 255, 255, 255, 255);
    }
    gSPDisplayList((*dlist)++, arg4->unk8[var_s2 + 1]);
    D_80120D1C--;
    if (D_80120D1C == 0) {
        var_s2 = 0;
    } else {
        var_s2 = 1;
    }
    gDkrInsertMatrix((*dlist)++, 0, var_s2 << 6);
    gDkrDisableBillboard((*dlist)++);
    return result;
}

/**
 * Sets transform and scale matrices to set position and size, loads the texture, sets the rendermodes, then draws the result onscreen.
*/
void render_ortho_triangle_image(Gfx **dList, MatrixS **mtx, Vertex **vtx, ObjectSegment *segment, Sprite *sprite, s32 flags) {
    UNUSED s32 pad;
    f32 scale;
    s32 index;
    Vertex *temp_v1;
    Matrix sp90;
    Matrix sp50;

    if (sprite != NULL) {
        temp_v1 = *vtx;
        temp_v1->x = segment->trans.x_position;
        temp_v1->y = segment->trans.y_position;
        temp_v1->z = segment->trans.z_position;
        temp_v1->r = 255;
        temp_v1->g = 255;
        temp_v1->b = 255;
        temp_v1->a = 255;
        gSPVertexDKR((*dList)++, OS_PHYSICAL_TO_K0(*vtx), 1, 0);
        (*vtx)++; // Can't be done in the macro?
        index = segment->animFrame;
        D_80120D1C ++;
        gCameraTransform.y_rotation = -segment->trans.y_rotation;
        gCameraTransform.x_rotation = -segment->trans.x_rotation;
        gCameraTransform.z_rotation = gActiveCameraStack[gActiveCameraID].trans.z_rotation + segment->trans.z_rotation;
        gCameraTransform.x_position = 0.0f;
        gCameraTransform.y_position = 0.0f;
        gCameraTransform.z_position = 0.0f;
        if (gAdjustViewportHeight) {
            scale = segment->trans.scale;
            f32_matrix_from_scale(sp50, scale, scale, 1.0f);
            f32_matrix_from_rotation_and_scale(sp90, 0, 1.0f, gVideoAspectRatio);
            f32_matrix_mult(&sp90, &sp50, &D_80121060);
        } else {
            scale = segment->trans.scale;
            f32_matrix_from_scale(D_80121060, scale, scale, 1.0f);
        }
        object_transform_to_matrix_2(sp90, &gCameraTransform);
        f32_matrix_mult(&D_80121060, &sp90, D_80120D70[D_80120D1C]);
        f32_matrix_to_s16_matrix(D_80120D70[D_80120D1C], *mtx);
        D_80120D88[D_80120D1C] = *mtx;
        gSPMatrix((*dList)++, OS_PHYSICAL_TO_K0((*mtx)++), G_MTX_DKR_INDEX_2);
        gDkrEnableBillboard((*dList)++);
        if (D_80120D0C == 0) {
            index =  (((u8) index) * sprite->baseTextureId) >> 8;
        }
        func_8007BF34(dList, sprite->unk6 | flags);
        if (index >= sprite->baseTextureId) {
            index = sprite->baseTextureId - 1;
        }
        gSPDisplayList((*dList)++, sprite->unkC[index]);
        if (--D_80120D1C == 0) {
            index = 0;
        } else {
            index = 1;
        }
        gDkrInsertMatrix((*dList)++, 0, index << 6);
        gDkrDisableBillboard((*dList)++);
    }
}

#ifdef NON_EQUIVALENT
void func_80068FA8(Gfx **dlist, MatrixS** mtx, Object *arg2, Object *arg3, f32 shear) {
    Matrix matrix_mult;
    f32 sinsf_x_arg2;
    f32 sinsf_x_arg3;
    f32 cossf_y_arg3;
    f32 arg2_xPos;
    f32 arg2_yPos;
    f32 arg2_zPos;
    f32 arg3_xPos;
    f32 arg3_yPos;
    f32 arg3_zPos;
    f32 arg3_cossf_x_and_sinsf_y;
    f32 arg3_sinsf_z_and_cossf_x;
    f32 sinsf_y_arg3;
    f32 arg3_cossf_and_y;
    f32 new_var;
    f32 temp_f10_4;
    f32 arg3_cossf_z_and_x;
    f32 temp_f14;
    f32 arg2_shear;
    f32 temp_f18;
    f32 cossf_z_arg3;
    f32 cossf_y_arg2;
    f32 sinsf_y_arg2;
    f32 sinsf_z_arg3;
    f32 temp_f26_2;
    f32 cossf_x_arg3;
    f32 arg2_scale;
    f32 cossf_x_arg2;
    f32 arg3_sinsf_x_and_cossf_y;
    f32 temp_f6_3;
    f32 temp_f6_5;
    f32 temp_f6_7;

    //arg2
    cossf_x_arg2 = coss_f(arg2->segment.trans.x_rotation);
    sinsf_x_arg2 = sins_f(arg2->segment.trans.x_rotation);
    cossf_y_arg2 = coss_f(arg2->segment.trans.y_rotation);
    sinsf_y_arg2 = sins_f(arg2->segment.trans.y_rotation);
    arg2_xPos = arg2->segment.trans.x_position;
    arg2_yPos = arg2->segment.trans.y_position;
    arg2_zPos = arg2->segment.trans.z_position;

    //arg3
    cossf_z_arg3 = coss_f(arg3->segment.trans.z_rotation);
    sinsf_z_arg3 = sins_f(arg3->segment.trans.z_rotation);
    cossf_x_arg3 = coss_f(arg3->segment.trans.x_rotation);
    sinsf_x_arg3 = sins_f(arg3->segment.trans.x_rotation);
    cossf_y_arg3 = coss_f(arg3->segment.trans.y_rotation);
    new_var = sinsf_y_arg2;
    sinsf_y_arg3 = sins_f(arg3->segment.trans.y_rotation);
    arg3_xPos = arg3->segment.trans.x_position;
    arg3_yPos = arg3->segment.trans.y_position;
    arg3_zPos = arg3->segment.trans.z_position;

    arg2_scale = arg2->segment.trans.scale;
    arg2_shear = shear * arg2_scale;

    temp_f18 = (cossf_z_arg3 * cossf_y_arg3) + (sinsf_z_arg3 * (sinsf_x_arg3 * sinsf_y_arg3));

    arg3_cossf_x_and_sinsf_y = cossf_x_arg3 * sinsf_y_arg3;

    matrix_mult[0][0] = ((temp_f18 * cossf_y_arg2) + (-sinsf_y_arg2 * arg3_cossf_x_and_sinsf_y)) * arg2_scale;

    arg3_sinsf_z_and_cossf_x = sinsf_z_arg3 * cossf_x_arg3;

    matrix_mult[0][1] = ((arg3_sinsf_z_and_cossf_x * cossf_y_arg2) + (-new_var * -sinsf_x_arg3)) * arg2_scale;

    arg3_sinsf_x_and_cossf_y = sinsf_x_arg3 * cossf_y_arg3;

    temp_f6_3 = (-sinsf_y_arg3 * cossf_z_arg3) + (sinsf_z_arg3 * arg3_sinsf_x_and_cossf_y);

    arg3_cossf_and_y = cossf_x_arg3 * cossf_y_arg3;

    matrix_mult[0][2] = ((temp_f6_3 * cossf_y_arg2) + (-sinsf_x_arg3 * arg3_cossf_and_y)) * arg2_scale;
    matrix_mult[0][3] = 0.0f;

    temp_f6_5 = (-sinsf_z_arg3 * cossf_y_arg3) + (cossf_z_arg3 * (sinsf_x_arg3 * sinsf_y_arg3));
    temp_f10_4 = (sinsf_y_arg2 * temp_f18) + (cossf_y_arg2 * arg3_cossf_x_and_sinsf_y);
    arg3_cossf_z_and_x = cossf_z_arg3 * cossf_x_arg3;
    matrix_mult[1][0] = ((temp_f6_5 * cossf_x_arg2) + (sinsf_x_arg2 * temp_f10_4)) * arg2_shear;

    temp_f26_2 = (sinsf_y_arg2 * arg3_sinsf_z_and_cossf_x) + (cossf_y_arg2 * -sinsf_x_arg3);
    matrix_mult[1][1] = ((arg3_cossf_z_and_x * cossf_x_arg2) + (sinsf_x_arg2 * temp_f26_2)) * arg2_shear;

    temp_f14 = (-sinsf_z_arg3 * -sinsf_y_arg3) + (cossf_z_arg3 * arg3_sinsf_x_and_cossf_y);
    temp_f6_7 = (sinsf_y_arg2 * temp_f6_3) + (cossf_y_arg2 * arg3_cossf_and_y);
    matrix_mult[1][2] = ((temp_f14 * cossf_x_arg2) + (sinsf_x_arg2 * temp_f6_7)) * arg2_shear;
    matrix_mult[1][3] = 0.0f;
    matrix_mult[2][0] = ((-sinsf_x_arg2 * temp_f6_5) + (cossf_x_arg2 * temp_f10_4)) * arg2_scale;
    matrix_mult[2][1] = ((-sinsf_x_arg2 * arg3_cossf_z_and_x) + (cossf_x_arg2 * temp_f26_2)) * arg2_scale;
    matrix_mult[2][2] = ((-sinsf_x_arg2 * temp_f14) + (cossf_x_arg2 * temp_f6_7)) * arg2_scale;
    matrix_mult[2][3] = 0.0f;
    matrix_mult[3][0] = (temp_f18 * arg2_xPos) + (arg2_yPos * temp_f6_5) + (arg2_zPos * arg3_cossf_x_and_sinsf_y) + arg3_xPos;
    matrix_mult[3][1] = (arg3_sinsf_z_and_cossf_x * arg2_xPos) + (arg2_yPos * arg3_cossf_z_and_x) + (arg2_zPos * -sinsf_x_arg3) + arg3_yPos;
    matrix_mult[3][2] = (temp_f6_3 * arg2_xPos) + (arg2_yPos * temp_f14) + (arg2_zPos * arg3_cossf_and_y) + arg3->segment.trans.z_position;
    matrix_mult[3][3] = 1.0f;

    f32_matrix_mult(&matrix_mult, &D_80120F20, &D_801210A0);
    f32_matrix_to_s16_matrix(&D_801210A0, *mtx);
    gSPMatrix((*dlist)++, OS_PHYSICAL_TO_K0((*mtx)++), G_MTX_DKR_INDEX_1);
}
#else
GLOBAL_ASM("asm/non_matchings/camera/func_80068FA8.s")
#endif

void func_80069484(Gfx **dList, MatrixS **mtx, ObjectTransform *trans, f32 scale, f32 scaleY) {
    f32 tempX;
    f32 tempY;
    f32 tempZ;
    s32 index;
    f32 scaleFactor;

    object_transform_to_matrix(D_80121060, trans);
    if (scaleY != 0.0f) {
        f32_matrix_y_scale(&D_80121060, scaleY);
    }
    if (scale != 1.0f) {
        f32_matrix_scale(&D_80121060, scale);
    }
    f32_matrix_mult(&D_80121060, D_80120D70[D_80120D1C], D_80120D70[D_80120D1C + 1]);
    f32_matrix_mult(D_80120D70[D_80120D1C + 1], &D_80120F20, &D_801210A0);
    f32_matrix_to_s16_matrix(&D_801210A0, *mtx);
    D_80120D1C++;
    D_80120D88[0, D_80120D1C] = *mtx; // Should be [D_80120D1C], but only matches with [0, D_80120D1C]
    if (1) { } if (1) { } if (1) { }; // Fakematch
    gSPMatrix((*dList)++, OS_PHYSICAL_TO_K0((*mtx)++), G_MTX_DKR_INDEX_1);
    guMtxXFMF(*D_80120D70[D_80120D1C], 0.0f, 0.0f, 0.0f, &tempX, &tempY, &tempZ);
    index = gActiveCameraID;
    if (gCutsceneCameraActive) {
        index += 4;
    }
    tempX = gActiveCameraStack[index].trans.x_position - tempX;
    tempY = gActiveCameraStack[index].trans.y_position - tempY;
    tempZ = gActiveCameraStack[index].trans.z_position - tempZ;
    gCameraTransform.y_rotation = -trans->y_rotation;
    gCameraTransform.x_rotation = -trans->x_rotation;
    gCameraTransform.z_rotation = -trans->z_rotation;
    gCameraTransform.x_position = 0.0f;
    gCameraTransform.y_position = 0.0f;
    gCameraTransform.z_position = 0.0f;
    gCameraTransform.scale = 1.0f;
    object_transform_to_matrix_2(D_80121060, &gCameraTransform);
    guMtxXFMF(D_80121060, tempX, tempY, tempZ, &tempX, &tempY, &tempZ);
    scaleFactor = 1.0f / trans->scale;
    tempX *= scaleFactor;
    tempY *= scaleFactor;
    tempZ *= scaleFactor;
    D_80120D20++;
    index = D_80120D20;
    D_80120D28[index] = tempX;
    D_80120D40[index] = tempY;
    if (0) {} // Necessary to match
    D_80120D58[index] = tempZ;
}

#ifdef NON_EQUIVALENT
void func_80069790(Gfx **dlist, MatrixS **mtx, Object_68 *obj68, s16 headAngle) {
    f32 spF4;
    f32 spF0;
    f32 spE4;
    Matrix spA4_mat;
    Matrix sp64_mat;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f4;
    f32 temp_f6;
    f32 temp_f6_2;

    spF4 = (f32) obj68->unk16;
    spF0 = (f32) obj68->unk18;
    temp_f6 = (f32) obj68->unk1A;
    temp_f20 = coss_f(obj68->unk1C);
    spE4 = sins_f(obj68->unk1C);
    temp_f22 = coss_f(headAngle);
    temp_f0 = sins_f(headAngle);
    temp_f18 = temp_f22 * temp_f20;
    temp_f10 = temp_f22 * spE4;
    temp_f4 = temp_f0 * temp_f20;
    temp_f6_2 = temp_f0 * spE4;
    sp64_mat[0][0] = temp_f18;
    sp64_mat[0][1] = temp_f10;
    sp64_mat[0][2] = -temp_f0;
    sp64_mat[0][3] = 0.0f;
    sp64_mat[1][0] = -spE4;
    sp64_mat[1][1] = temp_f20;
    sp64_mat[1][2] = 0.0f;
    sp64_mat[1][3] = 0.0f;
    sp64_mat[2][0] = temp_f4;
    sp64_mat[2][1] = temp_f6_2;
    sp64_mat[2][2] = temp_f22;
    sp64_mat[2][3] = 0.0f;
    sp64_mat[3][0] = (-spF4 * temp_f18) + (-spF0 * -spE4) + (-temp_f6 * temp_f4) + spF4;
    sp64_mat[3][1] = (-spF4 * temp_f10) + (-spF0 * temp_f20) + (-temp_f6 * temp_f6_2) + spF0;
    sp64_mat[3][2] = (-spF4 * -temp_f0) + (-temp_f6 * temp_f22) + temp_f6;
    sp64_mat[3][3] = 1.0f;
    f32_matrix_mult(&sp64_mat, &D_801210A0, &spA4_mat);
    f32_matrix_to_s16_matrix(&spA4_mat, *mtx);
    gSPMatrix((*dlist)++, OS_PHYSICAL_TO_K0((*mtx)++), G_MTX_DKR_INDEX_2);
    gDkrInsertMatrix((*dlist)++, G_MWO_MATRIX_XX_XY_I, G_MTX_DKR_INDEX_1);
}
#else
GLOBAL_ASM("asm/non_matchings/camera/func_80069790.s")
#endif

UNUSED void func_800699E4(f32 *arg0, f32 *arg1, f32 *arg2) {
    *arg0 = D_80120D28[D_80120D20];
    *arg1 = D_80120D40[D_80120D20];
    *arg2 = D_80120D58[D_80120D20];
}

void func_80069A40(Gfx **dlist) {
    D_80120D20--;
    D_80120D1C--;

    { s32 temp = D_80120D20; if ((temp && temp) != 0){} } // Fakematch

    if (D_80120D1C > 0) {
        gSPMatrix((*dlist)++, OS_PHYSICAL_TO_K0(D_80120D88[D_80120D1C]), G_MTX_DKR_INDEX_1);
    }
    else {
        gDkrInsertMatrix((*dlist)++, G_MWO_MATRIX_XX_XY_I, G_MTX_DKR_INDEX_0);
    }
}

UNUSED void func_80069ACC(f32 x, f32 y, f32 z) {
    gActiveCameraStack[gActiveCameraID].trans.x_position += x;
    gActiveCameraStack[gActiveCameraID].trans.y_position += y;
    gActiveCameraStack[gActiveCameraID].trans.z_position += z;
    gActiveCameraStack[gActiveCameraID].unk34_a.levelSegmentIndex =
        get_level_segment_index_from_position(
            gActiveCameraStack[gActiveCameraID].trans.x_position,
            gActiveCameraStack[gActiveCameraID].trans.y_position,
            gActiveCameraStack[gActiveCameraID].trans.z_position);
}

UNUSED void func_80069B70(f32 x, UNUSED f32 y, f32 z) {
    gActiveCameraStack[gActiveCameraID].trans.x_position -= x * coss_f(gActiveCameraStack[gActiveCameraID].trans.y_rotation);
    gActiveCameraStack[gActiveCameraID].trans.z_position -= x * sins_f(gActiveCameraStack[gActiveCameraID].trans.y_rotation);
    gActiveCameraStack[gActiveCameraID].trans.x_position -= z * sins_f(gActiveCameraStack[gActiveCameraID].trans.y_rotation);
    gActiveCameraStack[gActiveCameraID].trans.z_position += z * coss_f(gActiveCameraStack[gActiveCameraID].trans.y_rotation);
    gActiveCameraStack[gActiveCameraID].unk34_a.levelSegmentIndex =
        get_level_segment_index_from_position(
            gActiveCameraStack[gActiveCameraID].trans.x_position,
            gActiveCameraStack[gActiveCameraID].trans.y_position,
            gActiveCameraStack[gActiveCameraID].trans.z_position);
}

UNUSED void func_80069CB4(s32 xRotation, s32 yRotation, s32 zRotation) {
    gActiveCameraStack[gActiveCameraID].trans.y_rotation += xRotation;
    gActiveCameraStack[gActiveCameraID].trans.x_rotation += yRotation;
    gActiveCameraStack[gActiveCameraID].trans.z_rotation += zRotation;
}

/**
 * Returns the segment data of the active camera, but won't apply the offset for cutscenes.
*/
ObjectSegment *get_active_camera_segment_no_cutscenes(void) {
    return &gActiveCameraStack[gActiveCameraID];
}

/**
 * Returns the segment data of the active camera.
*/
ObjectSegment *get_active_camera_segment(void) {
    if (gCutsceneCameraActive) {
        return &gActiveCameraStack[gActiveCameraID + 4];
    }
    return &gActiveCameraStack[gActiveCameraID];
}

ObjectSegment *func_80069D7C(void) {
    if (gCutsceneCameraActive) {
        return &gActiveCameraStack[4];
    }
    return &gActiveCameraStack[0];
}

Matrix *func_80069DA4(void) {
    return &D_80120FA0;
}

MatrixS *func_80069DB0(void) {
    return &gPerspectiveMatrixS;
}

Matrix *func_80069DBC(void) {
    return &D_80120F60;
}

f32 func_80069DC8(f32 x, f32 y, f32 z) {
    f32 ox, oy, oz;

    guMtxXFMF(D_80120F60, x, y, z, &ox, &oy, &oz);

    return oz;
}

/**
 * Apply a shake to the camera based on the distance to the source.
*/
void set_camera_shake_by_distance(f32 x, f32 y, f32 z, f32 dist, f32 magnitude) {
    f32 diffX;
    f32 distance;
    f32 diffZ;
    f32 diffY;
    s32 i;

    for (i = 0; i <= gNumberOfViewports; i++) {
        diffX = x - gActiveCameraStack[i].trans.x_position;
        diffY = y - gActiveCameraStack[i].trans.y_position;
        diffZ = z - gActiveCameraStack[i].trans.z_position;
        distance = sqrtf(((diffX * diffX) + (diffY * diffY)) + (diffZ * diffZ));
        if (distance < dist) {
            gActiveCameraStack[i].unk30 = ((dist - distance) * magnitude) / dist;
        }
    }
}

/**
 * Apply a shake to all active cameras.
*/
void set_camera_shake(f32 magnitude) {
    s32 i;
    for (i = 0; i <= gNumberOfViewports; i++) {
        gActiveCameraStack[i].unk30 = magnitude;
    }
}

/**
 * Unused function that prints out the passed matrix values to the debug output.
 * This function prints in fixed point.
 */
UNUSED void debug_print_fixed_matrix_values(s16 *mtx) {
    s32 i, j;
    s32 val;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            val = mtx[i * 4 + j];
            rmonPrintf("%x.", val);
            val = mtx[((i + 4) * 4 + j)];
            rmonPrintf("%x  ", (u16)val & 0xFFFF);
        }
        rmonPrintf("\n");
        if (!val){} // Fakematch
    }
    rmonPrintf("\n");
}

/**
 * Unused function that prints out the passed matrix values to the debug output.
 * This function prints in floating point.
 */
UNUSED void debug_print_float_matrix_values(f32 *mtx) {
    s32 i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            rmonPrintf("%f  ", mtx[i * 4 + j]);
        }
        rmonPrintf("\n");
    }
    rmonPrintf("\n");
}
