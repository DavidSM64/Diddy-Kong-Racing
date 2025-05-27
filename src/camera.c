#include "camera.h"
#include "audio.h"
#include "objects.h"
#include "game.h"
#include "tracks.h"
#include "video.h"
#include "libultra/src/libc/rmonPrintf.h"
#include "math_util.h"
#include "weather.h"
#include "PRinternal/piint.h"
#include "PRinternal/viint.h"

/************ .rodata ************/

UNUSED const char D_800E6F00[] = "Camera Error: Illegal mode!\n";

/*********************************/

/************ .data ************/

s8 gAntiPiracyViewport = FALSE;

// x1, y1, x2, y2
// posX, posY, width, height
// scissorX1, scissorY1, scissorX2, scissorY2
// flags
#define DEFAULT_VIEWPORT                                                                                         \
    0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, \
        SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, 0

#define SCISSOR_INTERLACE G_SC_NON_INTERLACE

ScreenViewport gScreenViewports[4] = {
    { DEFAULT_VIEWPORT },
    { DEFAULT_VIEWPORT },
    { DEFAULT_VIEWPORT },
    { DEFAULT_VIEWPORT },
};

u32 gViewportWithBG = FALSE;

Vertex gVehiclePartVertex = { 0, 0, 0, 255, 255, 255, 255 };

// The viewport z-range below is half of the max (511)
#define G_HALFZ (G_MAXZ / 2) /* 9 bits of integer screen-Z precision */

// RSP Viewports
Vp gViewportStack[20] = {
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } }, { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } }, { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } }, { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } }, { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } }, { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } }, { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } }, { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } }, { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } }, { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
    { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } }, { { { 0, 0, G_HALFZ, 0 }, { 0, 0, G_HALFZ, 0 } } },
};

ObjectTransform D_800DD288 = {
    { { { 0, 0, 0 } } }, { 0 }, 1.0f, 0.0f, 0.0f, -281.0f,
};

ObjectTransform D_800DD2A0 = {
    { { { 0, 0, 0 } } }, { 0 }, 1.0f, 0.0f, 0.0f, 0.0f,
};

Matrix gOrthoMatrixF = {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 160.0f },
};

u8 gCameraZoomLevels[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

/*******************************/

/************ .bss ************/

Camera gCameras[8];
s32 gViewportLayout;
s32 gActiveCameraID;
s32 gNumCameras;
UNUSED s32 D_80120CEC;
ObjectTransform gCameraTransform;
s32 gMatrixType;
s32 gSpriteAnimOff;
f32 gCurCamFOV;
s8 gCutsceneCameraActive;
s8 gAdjustViewportHeight;
s32 D_80120D18;
s32 gModelMatrixStackPos;
s32 gCameraMatrixPos;
UNUSED s32 D_80120D24;
f32 gModelMatrixViewX[6];
f32 gModelMatrixViewY[6];
f32 gModelMatrixViewZ[5];
u16 perspNorm;
Matrix *gModelMatrixF[6];
MatrixS *gModelMatrixS[6];
f32 D_80120DA0[5 * 16];
Matrix gPerspectiveMatrixF;
Matrix gViewMatrixF;
Matrix gCameraMatrixF;
Matrix gProjectionMatrixF;
MatrixS gProjectionMatrixS;
UNUSED MatrixS gUnusedProjectionMatrixS; // Copied to the same way as gProjectionMatrixS, but not actually used.
Matrix gCurrentModelMatrixF;
Matrix gCurrentModelMatrixS;

/******************************/

/**
 * Official Name: camInit
 */
extern s32 D_B0000578;
void cam_init(void) {
    s32 i;
    s32 j;
    u32 stat;

    // clang-format off
    for (i = 0; i < 5; i++) { gModelMatrixF[i] = (Matrix*)&D_80120DA0[i << 4]; }
    // clang-format on

    for (j = 0; j < 8; j++) {
        gActiveCameraID = j;
        camera_reset(200, 200, 200, 0, 0, 180);
    }

    gCutsceneCameraActive = FALSE;
    gActiveCameraID = 0;
    gModelMatrixStackPos = 0;
    gCameraMatrixPos = 0;
    gViewportLayout = 0;
    gSpriteAnimOff = FALSE;
    D_80120D18 = FALSE;
    gAdjustViewportHeight = FALSE;
    gAntiPiracyViewport = FALSE;

    WAIT_ON_IOBUSY(stat);

    // 0xB0000578 is a direct read from the ROM as opposed to RAM
    if (((D_B0000578 & 0xFFFF) & 0xFFFF) != 0x8965) {
        gAntiPiracyViewport = TRUE;
    }

    guPerspectiveF(gPerspectiveMatrixF, &perspNorm, CAMERA_DEFAULT_FOV, CAMERA_ASPECT, CAMERA_NEAR, CAMERA_FAR,
                   CAMERA_SCALE);
    f32_matrix_to_s16_matrix(&gPerspectiveMatrixF, &gProjectionMatrixS);
    gCurCamFOV = CAMERA_DEFAULT_FOV;
}

void cam_set_zoom(s32 cameraID, s32 zoomLevel) {
    if (cameraID >= 0 && cameraID <= 3) {
        gCameraZoomLevels[cameraID] = zoomLevel;
        gCameras[cameraID].zoom = zoomLevel;
    }
}

/**
 * Set gAdjustViewportHeight to PAL mode if necessary, if setting is 1.
 * Otherwise, set it to 0, regardless of TV type.
 */
void enable_pal_viewport_height_adjust(s8 setting) {
    if (osTvType == OS_TV_TYPE_PAL) {
        gAdjustViewportHeight = setting;
    }
}

void func_800660C0(void) {
    D_80120D18 = TRUE;
}

void func_800660D0(void) {
    D_80120D18 = FALSE;
}

/**
 * Unused function that will return the current camera's FoV.
 * Official Name: camGetFOV
 */
UNUSED f32 cam_get_fov(void) {
    return gCurCamFOV;
}

/**
 * Set the FoV of the viewspace, then recalculate the perspective matrix.
 * Official Name: camSetFOV
 */
void cam_set_fov(f32 camFieldOfView) {
    if (CAMERA_MIN_FOV < camFieldOfView && camFieldOfView < CAMERA_MAX_FOV && camFieldOfView != gCurCamFOV) {
        gCurCamFOV = camFieldOfView;
        guPerspectiveF(gPerspectiveMatrixF, &perspNorm, camFieldOfView, CAMERA_ASPECT, CAMERA_NEAR, CAMERA_FAR,
                       CAMERA_SCALE);
        f32_matrix_to_s16_matrix(&gPerspectiveMatrixF, &gProjectionMatrixS);
    }
}

/**
 * Unused function that recalculates the perspective matrix.
 */
UNUSED void cam_reset_fov(void) {
    guPerspectiveF(gPerspectiveMatrixF, &perspNorm, CAMERA_DEFAULT_FOV, CAMERA_ASPECT, CAMERA_NEAR, CAMERA_FAR,
                   CAMERA_SCALE);
    f32_matrix_to_s16_matrix(&gPerspectiveMatrixF, &gProjectionMatrixS);
}

/**
 * Return the current fixed point model matrix.
 */
UNUSED Matrix *matrix_get_model_s16(void) {
    return &gCurrentModelMatrixS;
}

/**
 * Returns the number of active viewports.
 */
s32 cam_get_viewport_layout(void) {
    return gViewportLayout;
}

/**
 * Return the index of the active view.
 * 0-3 is players 1-4, and 4-7 is the same, but with 4 added on for cutscenes.
 * Official Name: camGetMode
 */
s32 get_current_viewport(void) {
    return gActiveCameraID;
}

/**
 * Initialises the camera object for the tracks menu.
 */
void camera_init_tracks_menu(Gfx **dList, MatrixS **mtxS) {
    Camera *cam;
    s16 angleY;
    s16 angleX;
    s16 angleZ;
    s16 sp24;
    f32 posX;
    f32 posY;
    f32 posZ;

    cam_set_layout(VIEWPORT_LAYOUT_1_PLAYER);
    set_active_camera(0);
    cam = cam_get_active_camera();
    angleY = cam->trans.rotation.y_rotation;
    angleX = cam->trans.rotation.x_rotation;
    angleZ = cam->trans.rotation.z_rotation;
    posX = cam->trans.x_position;
    posY = cam->trans.y_position;
    posZ = cam->trans.z_position;
    sp24 = cam->pitch;
    cam->trans.rotation.z_rotation = 0;
    cam->trans.rotation.x_rotation = 0;
    cam->trans.rotation.y_rotation = -0x8000;
    cam->pitch = 0;
    cam->trans.x_position = 0.0f;
    cam->trans.y_position = 0.0f;
    cam->trans.z_position = 0.0f;
    update_envmap_position(0.0f, 0.0f, -1.0f);
    viewport_main(dList, mtxS);
    cam->pitch = sp24;
    cam->trans.rotation.y_rotation = angleY;
    cam->trans.rotation.x_rotation = angleX;
    cam->trans.rotation.z_rotation = angleZ;
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

    dz = zPos - gCameras[index].trans.z_position;
    dx = xPos - gCameras[index].trans.x_position;
    dy = yPos - gCameras[index].trans.y_position;
    return sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
}

/**
 * Sets the position and angle of the active camera.
 * Also sets the other properties of the camera to a default.
 */
void camera_reset(s32 xPos, s32 yPos, s32 zPos, s32 angleZ, s32 angleX, s32 angleY) {
    gCameras[gActiveCameraID].trans.rotation.z_rotation = angleZ * (0x7FFF / 180);
    gCameras[gActiveCameraID].trans.x_position = xPos;
    gCameras[gActiveCameraID].trans.y_position = yPos;
    gCameras[gActiveCameraID].trans.z_position = zPos;
    gCameras[gActiveCameraID].trans.rotation.x_rotation = angleX * (0x7FFF / 180);
    gCameras[gActiveCameraID].pitch = 0;
    gCameras[gActiveCameraID].x_velocity = 0.0f;
    gCameras[gActiveCameraID].y_velocity = 0.0f;
    gCameras[gActiveCameraID].z_velocity = 0.0f;
    gCameras[gActiveCameraID].shakeMagnitude = 0.0f;
    gCameras[gActiveCameraID].boomLength = 160.0f;
    gCameras[gActiveCameraID].trans.rotation.y_rotation = angleY * (0x7FFF / 180);
    gCameras[gActiveCameraID].zoom = gCameraZoomLevels[gActiveCameraID];
}

/**
 * Write directly to the second set of object stack indeces.
 * The first 4 are reserved for the 4 player viewports, so the misc views, used in the title screen
 * and course previews instead use the next 4.
 */
void write_to_object_render_stack(s32 stackPos, f32 xPos, f32 yPos, f32 zPos, s16 arg4, s16 arg5, s16 arg6) {
    stackPos += 4;
    gCameras[stackPos].pitch = 0;
    gCameras[stackPos].trans.x_position = xPos;
    gCameras[stackPos].trans.y_position = yPos;
    gCameras[stackPos].trans.z_position = zPos;
    gCameras[stackPos].trans.rotation.y_rotation = arg4;
    gCameras[stackPos].trans.rotation.x_rotation = arg5;
    gCameras[stackPos].trans.rotation.z_rotation = arg6;
    gCameras[stackPos].cameraSegmentID = get_level_segment_index_from_position(xPos, yPos, zPos);
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
 */
void disable_cutscene_camera(void) {
    gCutsceneCameraActive = FALSE;
}

/**
 * Sets the current layout and returns the number of active cameras for that layout.
 * The layoutID argument must be from the ViewportCount enumeration.
 */
s32 cam_set_layout(s32 layoutID) {
    if (layoutID >= VIEWPORT_LAYOUT_1_PLAYER && layoutID <= VIEWPORT_LAYOUT_4_PLAYERS) {
        gViewportLayout = layoutID;
    } else {
        gViewportLayout = VIEWPORT_LAYOUT_1_PLAYER;
    }
    switch (gViewportLayout) {
        case VIEWPORT_LAYOUT_1_PLAYER:
            gNumCameras = 1;
            break;
        case VIEWPORT_LAYOUT_2_PLAYERS:
            gNumCameras = 2;
            break;
        case VIEWPORT_LAYOUT_3_PLAYERS:
            gNumCameras = 3;
            break;
        case VIEWPORT_LAYOUT_4_PLAYERS:
            gNumCameras = 4;
            break;
    }
    if (gActiveCameraID >= gNumCameras) {
        gActiveCameraID = 0;
    }
    return gNumCameras;
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
        stubbed_printf("Camera Error: Illegal player no!\n");
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
                if (0) {} // Fakematch
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
    if (arg1) {
        gScreenViewports[viewPortIndex].flags |= VIEWPORT_EXTRA_BG;
    } else {
        gScreenViewports[viewPortIndex].flags |= VIEWPORT_UNK_02;
    }
    gScreenViewports[viewPortIndex].flags &= ~VIEWPORT_UNK_04;
}

void camDisableUserView(s32 viewPortIndex, s32 arg1) {
    if (arg1) {
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
 * Official Name: camSetUserView
 */
void viewport_menu_set(s32 viewPortIndex, s32 x1, s32 y1, s32 x2, s32 y2) {
    s32 widthAndHeight, width, height;
    s32 temp;

    widthAndHeight = fb_size();
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
    // gDPFillRectangle values
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
    u32 widthAndHeight = fb_size();
    *x1 = 0;
    *y1 = 0;
    *x2 = GET_VIDEO_WIDTH(widthAndHeight);
    *y2 = GET_VIDEO_HEIGHT(widthAndHeight);
}

void viewport_main(Gfx **dlist, MatrixS **mats) {
    u32 y;
    u32 x;
    u32 tempX;
    u32 sp58_height;
    u32 sp54_width;
    u32 posY;
    u32 posX;
    u32 tempY;
    u32 videoHeight;
    u32 videoWidth;
    u32 widthAndHeight;
    s32 viewports;
    s32 originalCameraID;
    s32 savedCameraID;
    s32 tempCameraID;

    originalCameraID = gActiveCameraID;
    savedCameraID = gActiveCameraID;

    if (func_8000E184() && gViewportLayout == VIEWPORT_LAYOUT_1_PLAYER) {
        gActiveCameraID = 1;
        savedCameraID = 0;
    }
    widthAndHeight = fb_size();
    videoHeight = GET_VIDEO_HEIGHT(widthAndHeight);
    videoWidth = GET_VIDEO_WIDTH(widthAndHeight);
    if (gScreenViewports[savedCameraID].flags & VIEWPORT_EXTRA_BG) {
        tempCameraID = gActiveCameraID;
        gActiveCameraID = savedCameraID;
        gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, gScreenViewports[gActiveCameraID].scissorX1,
                      gScreenViewports[gActiveCameraID].scissorY1, gScreenViewports[gActiveCameraID].scissorX2,
                      gScreenViewports[gActiveCameraID].scissorY2);
        viewport_rsp_set(dlist, 0, 0, 0, 0);
        gActiveCameraID = tempCameraID;
        if (mats != 0) {
            func_80067D3C(dlist, mats);
        }
        gActiveCameraID = originalCameraID;
        return;
    }

    viewports = gViewportLayout;
    if (viewports == VIEWPORT_LAYOUT_3_PLAYERS) {
        viewports = VIEWPORT_LAYOUT_4_PLAYERS;
    }
    x = videoWidth >> 1;
    sp54_width = x;
    y = videoHeight >> 1;
    sp58_height = y;

    if (osTvType == 0) {
        sp58_height = 145;
    }

    switch (viewports) {
        case VIEWPORT_LAYOUT_1_PLAYER:
            posX = sp54_width;
            posY = sp58_height;
            if (osTvType == OS_TV_TYPE_PAL) {
                posY -= 18;
            }
            gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, 0, 0, videoWidth, videoHeight);
            break;
        case VIEWPORT_LAYOUT_2_PLAYERS:
            // 2 players = split screen horizontally
            // first player has top half
            posX = sp54_width;
            posY = gActiveCameraID;
            if (posY == 0) {
                posY = videoHeight >> 2;
                if (osTvType == OS_TV_TYPE_PAL) {
                    posY -= 12;
                }
                gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, 0, 0, videoWidth, y - (videoHeight >> 7));
            } else {
                // second player has bottom half
                posY = y;
                posY += videoHeight >> 2;
                tempY = y;
                tempY += (videoHeight >> 7);
                gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, 0, tempY, videoWidth, videoHeight - (videoHeight >> 7));
            }

            break;
        // this is probably never reached because of an if above that sets the viewport to 4 players if its currently 3
        // players
        case VIEWPORT_LAYOUT_3_PLAYERS:
            posY = sp58_height;
            // 3 player splits screen in 4 parts, first player = top left, second = top right, third = bottom left and
            // bottom right has map of race track
            if (gActiveCameraID == 0) {
                posX = videoWidth >> 2;
                gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, 0, 0, x - (videoWidth >> 8), videoHeight);
            } else {
                posX = x;
                posX += (videoWidth >> 2);
                tempX = x;
                tempX += (videoWidth >> 8);
                gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, tempX, 0, videoWidth - (videoWidth >> 8), videoHeight);
            }
            break;
        case VIEWPORT_LAYOUT_4_PLAYERS:
            sp58_height >>= 1;
            sp54_width >>= 1;
            tempY = 0;
            tempX = 0;
            switch (gActiveCameraID) {
                case 0:
                    // Using tempX and tempY here is not smart since IDO can't optimize out the zero now.
                    // Why here of all places did they do this instead of just setting zero like everywhere else?
                    gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, tempX, tempY, x - (videoWidth >> 8),
                                  y - (videoHeight >> 7));
                    break;
                case 1:
                    tempY = x;
                    posX = x;
                    posX += (videoWidth >> 8);
                    gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, posX, 0, (x + x) - (videoWidth >> 8),
                                  y - (videoHeight >> 7));
                    break;
                case 2:
                    tempX = y;
                    posY = y;
                    posY += (videoHeight >> 7);
                    posX = x;
                    posX -= (videoWidth >> 8);
                    gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, 0, posY, posX, (y + y) - (videoHeight >> 7));
                    break;
                case 3:
                    tempY = x;
                    tempX = y;
                    posX = x;
                    posX += (videoWidth >> 8);
                    gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, posX, y + (videoHeight >> 7),
                                  (x + x) - (videoWidth >> 8), (y + y) - (videoHeight >> 7));
                    break;
            }
            posY = tempX + sp58_height;
            posX = tempY + sp54_width;
            if (osTvType == OS_TV_TYPE_PAL) {
                if (gActiveCameraID <= 1) {
                    posY -= 20;
                } else {
                    posY -= 6;
                }
            }
            break;
    }

    if (osTvType == OS_TV_TYPE_PAL) {
        posX -= 4;
    }
    viewport_rsp_set(dlist, sp54_width, sp58_height, posX, posY);
    if (mats != NULL) {
        func_80067D3C(dlist, mats);
    }
    gActiveCameraID = originalCameraID;
}

/**
 * Takes the size of the screen as depicted by the active menu viewport, then sets the RDP scissor to match it.
 * Official Name: camSetScissor
 */
void viewport_scissor(Gfx **dList) {
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

    size = fb_size();
    height = (u16) GET_VIDEO_HEIGHT(size);
    width = (u16) size;
    numViewports = gViewportLayout;

    if (numViewports != VIEWPORT_LAYOUT_1_PLAYER) {
        if (numViewports == VIEWPORT_LAYOUT_3_PLAYERS) {
            numViewports = VIEWPORT_LAYOUT_4_PLAYERS;
        }
        lrx = ulx = 0;
        lry = uly = 0;
        // clang-format off
        lrx += width;\
        lry += height;
        // clang-format on
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
                // clang-format off
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
                        ulx = temp4 + temp2;\
                        uly = temp3 + temp;
                        lrx -= temp2;\
                        lry -= temp;
                        break;
                }
                // clang-format on
                break;
        }
        gDPSetScissor((*dList)++, 0, ulx, uly, lrx, lry);
    } else {
        gDPSetScissor((*dList)++, 0, 0, 0, width, height);
    }
}

// Official Name: camGetPlayerProjMtx / camSetProjMtx - ??
void func_80067D3C(Gfx **dList, UNUSED MatrixS **mats) {
    s32 temp;

    gSPPerspNormalize((*dList)++, perspNorm);

    temp = gActiveCameraID;
    if (gCutsceneCameraActive) {
        gActiveCameraID += 4;
    }

    gCameraTransform.rotation.y_rotation = 0x8000 + gCameras[gActiveCameraID].trans.rotation.y_rotation;
    gCameraTransform.rotation.x_rotation =
        gCameras[gActiveCameraID].trans.rotation.x_rotation + gCameras[gActiveCameraID].pitch;
    gCameraTransform.rotation.z_rotation = gCameras[gActiveCameraID].trans.rotation.z_rotation;

    gCameraTransform.x_position = -gCameras[gActiveCameraID].trans.x_position;
    gCameraTransform.y_position = -gCameras[gActiveCameraID].trans.y_position;
    if (D_80120D18) {
        gCameraTransform.y_position -= gCameras[gActiveCameraID].shakeMagnitude;
    }
    gCameraTransform.z_position = -gCameras[gActiveCameraID].trans.z_position;

    object_inverse_transform_to_matrix(gCameraMatrixF, &gCameraTransform);
    f32_matrix_mult(&gCameraMatrixF, &gPerspectiveMatrixF, &gViewMatrixF);

    gCameraTransform.rotation.y_rotation = -0x8000 - gCameras[gActiveCameraID].trans.rotation.y_rotation;
    gCameraTransform.rotation.x_rotation =
        -(gCameras[gActiveCameraID].trans.rotation.x_rotation + gCameras[gActiveCameraID].pitch);
    gCameraTransform.rotation.z_rotation = -gCameras[gActiveCameraID].trans.rotation.z_rotation;
    gCameraTransform.scale = 1.0f;
    gCameraTransform.x_position = gCameras[gActiveCameraID].trans.x_position;
    gCameraTransform.y_position = gCameras[gActiveCameraID].trans.y_position;
    if (D_80120D18) {
        gCameraTransform.y_position += gCameras[gActiveCameraID].shakeMagnitude;
    }
    gCameraTransform.z_position = gCameras[gActiveCameraID].trans.z_position;

    object_transform_to_matrix(gProjectionMatrixF, &gCameraTransform);
    f32_matrix_to_s16_matrix(&gProjectionMatrixF, &gUnusedProjectionMatrixS);

    gActiveCameraID = temp;
}

/**
 * Sets the Y value of the Y axis in the matrix to the passed value.
 * This is used to vertically scale ortho geometry to look identical across NTSC and PAL systems.
 * Official Name: camOrthoYAspect
 */
void set_ortho_matrix_height(f32 value) {
    gOrthoMatrixF[1][1] = value;
}

/**
 * Sets the current matrix to represent an orthogonal view.
 * Used for drawing triangles on screen as HUD.
 * Official Name: camStandardOrtho
 */
void set_ortho_matrix_view(Gfx **dList, MatrixS **mtx) {
    u32 widthAndHeight;
    s32 width, height;
    s32 i, j;

    widthAndHeight = fb_size();
    height = GET_VIDEO_HEIGHT(widthAndHeight);
    width = GET_VIDEO_WIDTH(widthAndHeight);
    f32_matrix_to_s16_matrix(&gOrthoMatrixF, *mtx);
    gModelMatrixS[0] = *mtx;
    gViewportStack[gActiveCameraID + 5].vp.vscale[0] = width * 2;
    gViewportStack[gActiveCameraID + 5].vp.vscale[1] = width * 2;
    gViewportStack[gActiveCameraID + 5].vp.vtrans[0] = width * 2;
    gViewportStack[gActiveCameraID + 5].vp.vtrans[1] = height * 2;
    gSPViewport((*dList)++, OS_K0_TO_PHYSICAL(&gViewportStack[gActiveCameraID + 5]));
    gSPMatrixDKR((*dList)++, OS_K0_TO_PHYSICAL((*mtx)++), G_MTX_DKR_INDEX_0);
    gModelMatrixStackPos = 0;
    gMatrixType = G_MTX_DKR_INDEX_0;

    for (i = 0; i < 4; i++) {
        // clang-format off
        // Required to be one line, but the "\" fixes that.
        for (j = 0; j < 4; j++) { \
            gViewMatrixF[i][j] = gOrthoMatrixF[i][j];
        }
        // clang-format on
    }
}

// Official Name: camStandardPersp?
void func_8006807C(Gfx **dList, MatrixS **mtx) {
    object_inverse_transform_to_matrix(gCurrentModelMatrixF, &D_800DD288);
    f32_matrix_mult(&gCurrentModelMatrixF, &gPerspectiveMatrixF, &gViewMatrixF);
    object_inverse_transform_to_matrix((float (*)[4]) gModelMatrixF[0], &D_800DD2A0);
    f32_matrix_mult(gModelMatrixF[0], &gViewMatrixF, &gCurrentModelMatrixF);
    f32_matrix_to_s16_matrix(&gCurrentModelMatrixF, *mtx);
    gSPMatrixDKR((*dList)++, OS_K0_TO_PHYSICAL((*mtx)++), G_MTX_DKR_INDEX_0);
    gModelMatrixStackPos = 0;
    gMatrixType = G_MTX_DKR_INDEX_0;
}

/**
 * Sets the RSP viewport onscreen to the given properties.
 * Viewports have a centre position and a scale factor, rather than a standard four corners.
 * Official Name: camSetViewport
 */
void viewport_rsp_set(Gfx **dList, s32 halfWidth, s32 halfHeight, s32 centerX, s32 centerY) {
    s32 tempWidth = (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) ? -halfWidth : halfWidth;
#ifdef ANTI_TAMPER
    // Antipiracy measure. Flips the screen upside down.
    if (gAntiPiracyViewport) {
        halfHeight = -halfHeight;
        tempWidth = -halfWidth;
    }
#endif
    if (!(gScreenViewports[gActiveCameraID].flags & VIEWPORT_EXTRA_BG)) {
        gViewportStack[gActiveCameraID].vp.vtrans[0] = centerX * 4;
        gViewportStack[gActiveCameraID].vp.vtrans[1] = centerY * 4;
        gViewportStack[gActiveCameraID].vp.vscale[0] = tempWidth * 4;
        gViewportStack[gActiveCameraID].vp.vscale[1] = halfHeight * 4;
        gSPViewport((*dList)++, OS_K0_TO_PHYSICAL(&gViewportStack[gActiveCameraID]));
    } else {
        gSPViewport((*dList)++, OS_K0_TO_PHYSICAL(&gViewportStack[gActiveCameraID + 10 + (gViewportWithBG * 5)]));
    }
}

/**
 * Resets the viewport back to default.
 * If in the track menu, or post-race, set it to a small screen view instead.
 * Official Name: camResetView?
 */
void viewport_reset(Gfx **dList) {
    u32 widthAndHeight, width, height;
    gActiveCameraID = 4;
    widthAndHeight = fb_size();
    height = GET_VIDEO_HEIGHT(widthAndHeight);
    width = GET_VIDEO_WIDTH(widthAndHeight);
    if (!(gScreenViewports[gActiveCameraID].flags & VIEWPORT_EXTRA_BG)) {
        gDPSetScissor((*dList)++, G_SC_NON_INTERLACE, 0, 0, width - 1, height - 1);
        viewport_rsp_set(dList, width >> 1, height >> 1, width >> 1, height >> 1);
    } else {
        viewport_scissor(dList);
        viewport_rsp_set(dList, 0, 0, 0, 0);
    }
    gActiveCameraID = 0;
}

UNUSED const char D_800E6F44[] = "cameraPushSprMtx: model stack overflow!!\n";

/**
 * Sets the matrix position to the world origin (0, 0, 0)
 * Used when the next thing rendered relies on there not being any matrix offset.
 * Official Name: camOffsetZero?
 */
void matrix_world_origin(Gfx **dList, MatrixS **mtx) {
    f32_matrix_from_position(gModelMatrixF[gModelMatrixStackPos], 0.0f, 0.0f, 0.0f);
    f32_matrix_mult(gModelMatrixF[gModelMatrixStackPos], &gViewMatrixF, &gCurrentModelMatrixF);
    f32_matrix_to_s16_matrix(&gCurrentModelMatrixF, *mtx);
    gModelMatrixS[gModelMatrixStackPos] = *mtx;
    gSPMatrixDKR((*dList)++, OS_K0_TO_PHYSICAL((*mtx)++), gMatrixType);
}

/**
 * If set to true, disables animated sprite frames.
 * Used when the sprite frame is already established before calling to draw.
 */
void sprite_anim_off(s32 setting) {
    gSpriteAnimOff = setting;
}

/**
 * Calculates angle from object to camera, then renders the sprite as a billboard, facing the camera.
 */
s32 render_sprite_billboard(Gfx **dList, MatrixS **mtx, Vertex **vertexList, Object *obj, Sprite *arg4, s32 flags) {
    f32 diffX;
    f32 diffY;
    Vertex *v;
    f32 lateralDist;
    f32 sineY;
    f32 cosY;
    f32 sp44;
    f32 diffZ;
    s32 tanX;
    s32 tanY;
    s32 angleDiff;
    s32 result;
    s32 textureFrame;

    if (obj == NULL) {
        stubbed_printf("\nCam do 2D sprite called with NULL pointer!");
    }

    result = TRUE;
    if (flags & RENDER_VEHICLE_PART) {
        diffX = gModelMatrixViewX[gCameraMatrixPos] - obj->segment.trans.x_position;
        diffY = gModelMatrixViewY[gCameraMatrixPos] - obj->segment.trans.y_position;
        diffZ = gModelMatrixViewZ[gCameraMatrixPos] - obj->segment.trans.z_position;
        sineY = sins_f(obj->segment.trans.rotation.y_rotation);
        cosY = coss_f(obj->segment.trans.rotation.y_rotation);
        sp44 = (diffX * cosY) + (diffZ * sineY);
        diffZ = (diffZ * cosY) - (diffX * sineY);
        tanY = arctan2_f(sp44, sqrtf((diffY * diffY) + (diffZ * diffZ)));
        tanX = -sins_s16(arctan2_f(sp44, diffZ)) >> 8;
        if (diffZ < 0.0f) {
            diffZ = -diffZ;
            tanX = 1 - tanX;
            tanY = -tanY;
        }
        angleDiff = arctan2_f(diffY, diffZ);
        if (angleDiff > 0x8000) {
            angleDiff -= 0x10000;
        }
        angleDiff = (angleDiff * tanX) >> 8;
        textureFrame = (tanY >> 7) & 0xFF;
        if (textureFrame > 127) {
            stubbed_printf("CamDo2DSprite FrameNo Overflow !!!\n");
            textureFrame = 255 - textureFrame;
            angleDiff += 0x8000;
            result = FALSE;
        }
        textureFrame *= 2;
        diffX = gModelMatrixViewX[gCameraMatrixPos] - obj->segment.trans.x_position;
        diffY = gModelMatrixViewY[gCameraMatrixPos] - obj->segment.trans.y_position;
        diffZ = gModelMatrixViewZ[gCameraMatrixPos] - obj->segment.trans.z_position;
        lateralDist = sqrtf((diffX * diffX) + (diffZ * diffZ));
        gCameraTransform.rotation.y_rotation = arctan2_f(diffX, diffZ);
        gCameraTransform.rotation.x_rotation = -arctan2_f(diffY, lateralDist);
        gCameraTransform.rotation.z_rotation = angleDiff;
        gCameraTransform.scale = obj->segment.trans.scale;
        gCameraTransform.x_position = obj->segment.trans.x_position;
        gCameraTransform.y_position = obj->segment.trans.y_position;
        gCameraTransform.z_position = obj->segment.trans.z_position;
        object_transform_to_matrix(gCurrentModelMatrixF, &gCameraTransform);
        gModelMatrixStackPos++;
        f32_matrix_mult(&gCurrentModelMatrixF, gModelMatrixF[gModelMatrixStackPos - 1],
                        gModelMatrixF[gModelMatrixStackPos]);
        f32_matrix_mult(gModelMatrixF[gModelMatrixStackPos], &gViewMatrixF, &gCurrentModelMatrixF);
        f32_matrix_to_s16_matrix(&gCurrentModelMatrixF, *mtx);
        gModelMatrixS[gModelMatrixStackPos] = *mtx;
        gSPMatrixDKR((*dList)++, OS_K0_TO_PHYSICAL((*mtx)++), G_MTX_DKR_INDEX_2);
        gSPVertexDKR((*dList)++, OS_K0_TO_PHYSICAL(&gVehiclePartVertex), 1, 0);
    } else {
        v = *vertexList;
        v->x = obj->segment.trans.x_position;
        v->y = obj->segment.trans.y_position;
        v->z = obj->segment.trans.z_position;
        v->r = 255; // These don't actually do anything since vertex colours are disabled anyway.
        v->g = 255;
        v->b = 255;
        v->a = 255;
        gSPVertexDKR((*dList)++, OS_K0_TO_PHYSICAL(*vertexList), 1, 0);
        (*vertexList)++;
        if (!gCutsceneCameraActive) {
            angleDiff = gCameras[gActiveCameraID].trans.rotation.z_rotation + obj->segment.trans.rotation.z_rotation;
        } else {
            angleDiff =
                gCameras[gActiveCameraID + 4].trans.rotation.z_rotation + obj->segment.trans.rotation.z_rotation;
        }
        textureFrame = obj->segment.animFrame;
        gModelMatrixStackPos++;
        f32_matrix_from_rotation_and_scale((f32(*)[4]) gModelMatrixF[gModelMatrixStackPos], angleDiff,
                                           obj->segment.trans.scale, gVideoAspectRatio);
        f32_matrix_to_s16_matrix(gModelMatrixF[gModelMatrixStackPos], *mtx);
        gModelMatrixS[gModelMatrixStackPos] = *mtx;
        gSPMatrixDKR((*dList)++, OS_K0_TO_PHYSICAL((*mtx)++), G_MTX_DKR_INDEX_2);
        gDkrEnableBillboard((*dList)++);
    }
    if (gSpriteAnimOff == FALSE) {
        textureFrame = ((textureFrame & 0xFF) * arg4->baseTextureId) >> 8;
    }
    flags &= ~RENDER_VEHICLE_PART;
    if (flags & RENDER_SEMI_TRANSPARENT) {
        flags |= RENDER_ANTI_ALIASING;
    }
    material_load_simple(dList, arg4->drawFlags | (flags & (RENDER_FOG_ACTIVE | RENDER_SEMI_TRANSPARENT |
                                                            RENDER_Z_COMPARE | RENDER_ANTI_ALIASING)));
    if (!(flags & RENDER_Z_UPDATE)) {
        gDPSetPrimColor((*dList)++, 0, 0, 255, 255, 255, 255);
    }
    gSPDisplayList((*dList)++, arg4->gfx[textureFrame + 1]);
    gModelMatrixStackPos--;
    if (gModelMatrixStackPos == 0) {
        textureFrame = G_MTX_DKR_INDEX_0;
    } else {
        textureFrame = G_MTX_DKR_INDEX_1;
    }
    gSPSelectMatrixDKR((*dList)++, textureFrame);
    gDkrDisableBillboard((*dList)++);
    return result;
}

/**
 * Sets transform and scale matrices to set position and size, loads the texture, sets the rendermodes, then draws the
 * result onscreen.
 */
void render_ortho_triangle_image(Gfx **dList, MatrixS **mtx, Vertex **vtx, ObjectSegment *segment, Sprite *sprite,
                                 s32 flags) {
    UNUSED s32 pad;
    f32 scale;
    s32 index;
    Vertex *temp_v1;
    Matrix aspectMtxF;
    Matrix scaleMtxF;

    if (sprite != NULL) {
        temp_v1 = *vtx;
        temp_v1->x = segment->trans.x_position;
        temp_v1->y = segment->trans.y_position;
        temp_v1->z = segment->trans.z_position;
        temp_v1->r = 255; // These don't actually do anything since vertex colours are disabled anyway.
        temp_v1->g = 255;
        temp_v1->b = 255;
        temp_v1->a = 255;
        gSPVertexDKR((*dList)++, OS_K0_TO_PHYSICAL(*vtx), 1, 0);
        (*vtx)++; // Can't be done in the macro?
        index = segment->animFrame;
        gModelMatrixStackPos++;
        gCameraTransform.rotation.y_rotation = -segment->trans.rotation.y_rotation;
        gCameraTransform.rotation.x_rotation = -segment->trans.rotation.x_rotation;
        gCameraTransform.rotation.z_rotation =
            gCameras[gActiveCameraID].trans.rotation.z_rotation + segment->trans.rotation.z_rotation;
        gCameraTransform.x_position = 0.0f;
        gCameraTransform.y_position = 0.0f;
        gCameraTransform.z_position = 0.0f;
        if (gAdjustViewportHeight) {
            scale = segment->trans.scale;
            f32_matrix_from_scale(scaleMtxF, scale, scale, 1.0f);
            f32_matrix_from_rotation_and_scale(aspectMtxF, 0, 1.0f, gVideoAspectRatio);
            f32_matrix_mult(&aspectMtxF, &scaleMtxF, &gCurrentModelMatrixF);
        } else {
            scale = segment->trans.scale;
            f32_matrix_from_scale(gCurrentModelMatrixF, scale, scale, 1.0f);
        }
        object_inverse_transform_to_matrix(aspectMtxF, &gCameraTransform);
        f32_matrix_mult(&gCurrentModelMatrixF, &aspectMtxF, gModelMatrixF[gModelMatrixStackPos]);
        f32_matrix_to_s16_matrix(gModelMatrixF[gModelMatrixStackPos], *mtx);
        gModelMatrixS[gModelMatrixStackPos] = *mtx;
        gSPMatrixDKR((*dList)++, OS_K0_TO_PHYSICAL((*mtx)++), G_MTX_DKR_INDEX_2);
        gDkrEnableBillboard((*dList)++);
        if (gSpriteAnimOff == FALSE) {
            index = (((u8) index) * sprite->baseTextureId) >> 8;
        }
        material_load_simple(dList, sprite->drawFlags | flags);
        if (index >= sprite->baseTextureId) {
            index = sprite->baseTextureId - 1;
        }
        gSPDisplayList((*dList)++, sprite->unkC.ptr[index]);
        if (--gModelMatrixStackPos == 0) {
            index = G_MTX_DKR_INDEX_0;
        } else {
            index = G_MTX_DKR_INDEX_1;
        }
        gSPSelectMatrixDKR((*dList)++, index);
        gDkrDisableBillboard((*dList)++);
    }
}

/**
 * Generate a matrix with rotation, scaling and shearing and run it.
 * Used for wavy type effects like the shield.
 */
void apply_object_shear_matrix(Gfx **dList, MatrixS **mtx, Object *arg2, Object *arg3, f32 shear) {
    UNUSED s32 pad;
    f32 cossf_x_arg2;
    f32 cossf_y_arg2;
    f32 sinsf_x_arg2;
    f32 sinsf_y_arg2;
    f32 sinsf_y_arg3;
    f32 sinsf_z_arg3;
    f32 arg2_scale;
    f32 cossf_x_arg3;
    f32 sinsf_x_arg3;
    f32 cossf_y_arg3;
    f32 cossf_z_arg3;
    f32 arg2_xPos;
    f32 arg2_yPos;
    f32 arg2_zPos;
    f32 arg3_xPos;
    f32 arg3_yPos;
    f32 arg3_zPos;
    Matrix matrix_mult;

    cossf_x_arg2 = coss_f(arg2->segment.trans.rotation.x_rotation);
    sinsf_x_arg2 = sins_f(arg2->segment.trans.rotation.x_rotation);
    cossf_y_arg2 = coss_f(arg2->segment.trans.rotation.y_rotation);
    sinsf_y_arg2 = sins_f(arg2->segment.trans.rotation.y_rotation);
    arg2_xPos = arg2->segment.trans.x_position;
    arg2_yPos = arg2->segment.trans.y_position;
    arg2_zPos = arg2->segment.trans.z_position;
    cossf_z_arg3 = coss_f(arg3->segment.trans.rotation.z_rotation);
    sinsf_z_arg3 = sins_f(arg3->segment.trans.rotation.z_rotation);
    cossf_x_arg3 = coss_f(arg3->segment.trans.rotation.x_rotation);
    sinsf_x_arg3 = sins_f(arg3->segment.trans.rotation.x_rotation);
    cossf_y_arg3 = coss_f(arg3->segment.trans.rotation.y_rotation);
    sinsf_y_arg3 = sins_f(arg3->segment.trans.rotation.y_rotation);
    arg3_xPos = arg3->segment.trans.x_position;
    arg3_yPos = arg3->segment.trans.y_position;
    arg3_zPos = arg3->segment.trans.z_position;
    arg2_scale = arg2->segment.trans.scale;
    shear *= arg2_scale;
    matrix_mult[0][0] =
        ((((cossf_z_arg3 * cossf_y_arg3) + (sinsf_z_arg3 * (sinsf_x_arg3 * sinsf_y_arg3))) * cossf_y_arg2) +
         (-sinsf_y_arg2 * (cossf_x_arg3 * sinsf_y_arg3))) *
        arg2_scale;
    matrix_mult[0][1] = (((sinsf_z_arg3 * cossf_x_arg3) * cossf_y_arg2) + (-sinsf_y_arg2 * -sinsf_x_arg3)) * arg2_scale;
    matrix_mult[0][2] =
        ((((-sinsf_y_arg3 * cossf_z_arg3) + (sinsf_z_arg3 * (sinsf_x_arg3 * cossf_y_arg3))) * cossf_y_arg2) +
         (-sinsf_y_arg2 * (cossf_x_arg3 * cossf_y_arg3))) *
        arg2_scale;
    matrix_mult[0][3] = 0.0f;
    matrix_mult[1][0] =
        ((((-sinsf_z_arg3 * cossf_y_arg3) + (cossf_z_arg3 * (sinsf_x_arg3 * sinsf_y_arg3))) * cossf_x_arg2) +
         (sinsf_x_arg2 *
          ((sinsf_y_arg2 * ((cossf_z_arg3 * cossf_y_arg3) + (sinsf_z_arg3 * (sinsf_x_arg3 * sinsf_y_arg3)))) +
           (cossf_y_arg2 * (cossf_x_arg3 * sinsf_y_arg3))))) *
        shear;
    matrix_mult[1][1] =
        (((cossf_z_arg3 * cossf_x_arg3) * cossf_x_arg2) +
         (sinsf_x_arg2 * ((sinsf_y_arg2 * (sinsf_z_arg3 * cossf_x_arg3)) + (cossf_y_arg2 * -sinsf_x_arg3)))) *
        shear;
    matrix_mult[1][2] =
        ((((-sinsf_z_arg3 * -sinsf_y_arg3) + (cossf_z_arg3 * (sinsf_x_arg3 * cossf_y_arg3))) * cossf_x_arg2) +
         (sinsf_x_arg2 *
          ((sinsf_y_arg2 * ((-sinsf_y_arg3 * cossf_z_arg3) + (sinsf_z_arg3 * (sinsf_x_arg3 * cossf_y_arg3)))) +
           (cossf_y_arg2 * (cossf_x_arg3 * cossf_y_arg3))))) *
        shear;
    matrix_mult[1][3] = 0.0f;
    matrix_mult[2][0] =
        ((-sinsf_x_arg2 * ((-sinsf_z_arg3 * cossf_y_arg3) + (cossf_z_arg3 * (sinsf_x_arg3 * sinsf_y_arg3)))) +
         (cossf_x_arg2 *
          ((sinsf_y_arg2 * ((cossf_z_arg3 * cossf_y_arg3) + (sinsf_z_arg3 * (sinsf_x_arg3 * sinsf_y_arg3)))) +
           (cossf_y_arg2 * (cossf_x_arg3 * sinsf_y_arg3))))) *
        arg2_scale;
    matrix_mult[2][1] =
        ((-sinsf_x_arg2 * (cossf_z_arg3 * cossf_x_arg3)) +
         (cossf_x_arg2 * ((sinsf_y_arg2 * (sinsf_z_arg3 * cossf_x_arg3)) + (cossf_y_arg2 * -sinsf_x_arg3)))) *
        arg2_scale;
    matrix_mult[2][2] =
        ((-sinsf_x_arg2 * ((-sinsf_z_arg3 * -sinsf_y_arg3) + (cossf_z_arg3 * (sinsf_x_arg3 * cossf_y_arg3)))) +
         (cossf_x_arg2 *
          ((sinsf_y_arg2 * ((-sinsf_y_arg3 * cossf_z_arg3) + (sinsf_z_arg3 * (sinsf_x_arg3 * cossf_y_arg3)))) +
           (cossf_y_arg2 * (cossf_x_arg3 * cossf_y_arg3))))) *
        arg2_scale;
    matrix_mult[2][3] = 0.0f;
    matrix_mult[3][0] =
        (((cossf_z_arg3 * cossf_y_arg3) + (sinsf_z_arg3 * (sinsf_x_arg3 * sinsf_y_arg3))) * arg2_xPos) +
        (arg2_yPos * ((-sinsf_z_arg3 * cossf_y_arg3) + (cossf_z_arg3 * (sinsf_x_arg3 * sinsf_y_arg3)))) +
        (arg2_zPos * (cossf_x_arg3 * sinsf_y_arg3)) + arg3_xPos;
    matrix_mult[3][1] = ((sinsf_z_arg3 * cossf_x_arg3) * arg2_xPos) + (arg2_yPos * (cossf_z_arg3 * cossf_x_arg3)) +
                        (arg2_zPos * -sinsf_x_arg3) + arg3_yPos;
    matrix_mult[3][2] =
        (((-sinsf_y_arg3 * cossf_z_arg3) + (sinsf_z_arg3 * (sinsf_x_arg3 * cossf_y_arg3))) * arg2_xPos) +
        (arg2_yPos * ((-sinsf_z_arg3 * -sinsf_y_arg3) + (cossf_z_arg3 * (sinsf_x_arg3 * cossf_y_arg3)))) +
        (arg2_zPos * (cossf_x_arg3 * cossf_y_arg3)) + arg3_zPos;
    matrix_mult[3][3] = 1.0f;

    f32_matrix_mult(&matrix_mult, &gViewMatrixF, &gCurrentModelMatrixS);
    f32_matrix_to_s16_matrix(&gCurrentModelMatrixS, *mtx);
    gSPMatrixDKR((*dList)++, OS_K0_TO_PHYSICAL((*mtx)++), G_MTX_DKR_INDEX_1);
}

/**
 * Official Name: camPushModelMtx
 */
s32 cam_push_model_mtx(Gfx **dList, MatrixS **mtx, ObjectTransform *trans, f32 scaleY, f32 offsetY) {
    f32 tempX;
    f32 tempY;
    f32 tempZ;
    s32 index;
    f32 scaleFactor;

    object_transform_to_matrix(gCurrentModelMatrixF, trans);
    if (offsetY != 0.0f) {
        f32_matrix_translate_y_axis(&gCurrentModelMatrixF, offsetY);
    }
    if (scaleY != 1.0f) {
        f32_matrix_scale_y_axis(&gCurrentModelMatrixF, scaleY);
    }
    f32_matrix_mult(&gCurrentModelMatrixF, gModelMatrixF[gModelMatrixStackPos],
                    gModelMatrixF[gModelMatrixStackPos + 1]);
    f32_matrix_mult(gModelMatrixF[gModelMatrixStackPos + 1], &gViewMatrixF, &gCurrentModelMatrixS);
    f32_matrix_to_s16_matrix(&gCurrentModelMatrixS, *mtx);
    gModelMatrixStackPos++;
    gModelMatrixS[0, gModelMatrixStackPos] = *mtx; // Should be [gModelMatrixStackPos]
    if (gModelMatrixStackPos >= ARRAY_COUNT(gModelMatrixS)) {
        stubbed_printf("cameraPushModelMtx: model stack overflow!!\n");
    }
    if (1) {}
    if (1) {}; // Fakematch
    gSPMatrixDKR((*dList)++, OS_K0_TO_PHYSICAL((*mtx)++), G_MTX_DKR_INDEX_1);
    guMtxXFMF(*gModelMatrixF[gModelMatrixStackPos], 0.0f, 0.0f, 0.0f, &tempX, &tempY, &tempZ);
    index = gActiveCameraID;
    if (gCutsceneCameraActive) {
        index += 4;
    }
    tempX = gCameras[index].trans.x_position - tempX;
    tempY = gCameras[index].trans.y_position - tempY;
    tempZ = gCameras[index].trans.z_position - tempZ;
    gCameraTransform.rotation.y_rotation = -trans->rotation.y_rotation;
    gCameraTransform.rotation.x_rotation = -trans->rotation.x_rotation;
    gCameraTransform.rotation.z_rotation = -trans->rotation.z_rotation;
    gCameraTransform.x_position = 0.0f;
    gCameraTransform.y_position = 0.0f;
    gCameraTransform.z_position = 0.0f;
    gCameraTransform.scale = 1.0f;
    object_inverse_transform_to_matrix(gCurrentModelMatrixF, &gCameraTransform);
    guMtxXFMF(gCurrentModelMatrixF, tempX, tempY, tempZ, &tempX, &tempY, &tempZ);
    scaleFactor = 1.0f / trans->scale;
    tempX *= scaleFactor;
    tempY *= scaleFactor;
    tempZ *= scaleFactor;
    gCameraMatrixPos++;
    index = gCameraMatrixPos;
    gModelMatrixViewX[index] = tempX;
    gModelMatrixViewY[index] = tempY;
    gModelMatrixViewZ[index] = tempZ;
    if (0) {
        stubbed_printf("camPushModelMtx: bsp stack overflow!!\n");
    }
}

/**
 * Calculate the rotation matrix for an actors head, then run it.
 */
void apply_head_turning_matrix(Gfx **dList, MatrixS **mtx, Object_68 *objGfx, s16 headAngle) {
    f32 coss_headAngle;
    f32 sins_headAngle;
    f32 offsetX;
    f32 offsetY;
    f32 offsetZ;
    f32 coss_unk1C;
    f32 sins_unk1C;
    Matrix rotationMtxF;
    Matrix headMtxF;

    offsetX = (f32) objGfx->offsetX;
    offsetY = (f32) objGfx->offsetY;
    offsetZ = (f32) objGfx->offsetZ;
    coss_unk1C = coss_f(objGfx->headTilt);
    sins_unk1C = sins_f(objGfx->headTilt);
    coss_headAngle = coss_f(headAngle);
    sins_headAngle = sins_f(headAngle);
    headMtxF[0][0] = (coss_headAngle * coss_unk1C);
    headMtxF[0][1] = (coss_headAngle * sins_unk1C);
    headMtxF[0][2] = -sins_headAngle;
    headMtxF[0][3] = 0.0f;
    headMtxF[1][0] = -sins_unk1C;
    headMtxF[1][1] = coss_unk1C;
    headMtxF[1][2] = 0.0f;
    headMtxF[1][3] = 0.0f;
    headMtxF[2][0] = (sins_headAngle * coss_unk1C);
    headMtxF[2][1] = (sins_headAngle * sins_unk1C);
    headMtxF[2][2] = coss_headAngle;
    headMtxF[2][3] = 0.0f;
    headMtxF[3][0] = (-offsetX * (coss_headAngle * coss_unk1C)) + (-offsetY * -sins_unk1C) +
                     (-offsetZ * (sins_headAngle * coss_unk1C)) + offsetX;
    headMtxF[3][1] = (-offsetX * (coss_headAngle * sins_unk1C)) + (-offsetY * coss_unk1C) +
                     (-offsetZ * (sins_headAngle * sins_unk1C)) + offsetY;
    headMtxF[3][2] = (-offsetX * -sins_headAngle) + (-offsetZ * coss_headAngle) + offsetZ;
    headMtxF[3][3] = 1.0f;
    f32_matrix_mult(&headMtxF, &gCurrentModelMatrixS, &rotationMtxF);
    f32_matrix_to_s16_matrix(&rotationMtxF, *mtx);
    gSPMatrixDKR((*dList)++, OS_K0_TO_PHYSICAL((*mtx)++), G_MTX_DKR_INDEX_2);
    gSPSelectMatrixDKR((*dList)++, G_MTX_DKR_INDEX_1);
}

/**
 * Writes the model matrix vector to the arguments.
 */
UNUSED void get_modelmatrix_vector(f32 *x, f32 *y, f32 *z) {
    *x = gModelMatrixViewX[gCameraMatrixPos];
    *y = gModelMatrixViewY[gCameraMatrixPos];
    *z = gModelMatrixViewZ[gCameraMatrixPos];
}

/**
 * Run a matrix from the top of the stack and pop it.
 * If the stack pos is less than zero, add a matrix instead.
 */
void apply_matrix_from_stack(Gfx **dList) {
    gCameraMatrixPos--;
    gModelMatrixStackPos--;

    {
        s32 temp = gCameraMatrixPos;
        if ((temp && temp) != 0) {}
        if (temp > ARRAY_COUNT(gModelMatrixViewX)) {
            stubbed_printf("camPopModelMtx: model stack negative overflow!!\n");
            // TODO: get the condition matching for this one too.
            stubbed_printf("camPopModelMtx: bsp stack negative overflow!!\n");
        }
    } // Fakematch

    if (gModelMatrixStackPos > 0) {
        gSPMatrixDKR((*dList)++, OS_K0_TO_PHYSICAL(gModelMatrixS[gModelMatrixStackPos]), G_MTX_DKR_INDEX_1);
    } else {
        gSPSelectMatrixDKR((*dList)++, G_MTX_DKR_INDEX_0);
    }
}

/**
 * Move the camera with the given velocities.
 * Also recalculates which block it's in.
 */
UNUSED void translate_camera_segment(f32 x, f32 y, f32 z) {
    gCameras[gActiveCameraID].trans.x_position += x;
    gCameras[gActiveCameraID].trans.y_position += y;
    gCameras[gActiveCameraID].trans.z_position += z;
    gCameras[gActiveCameraID].cameraSegmentID = get_level_segment_index_from_position(
        gCameras[gActiveCameraID].trans.x_position, gCameras[gActiveCameraID].trans.y_position,
        gCameras[gActiveCameraID].trans.z_position);
}

/**
 * Move the camera with velocities accounting for face direction.
 * Also recalculates which block it's in.
 */
UNUSED void transform_camera_segment(f32 x, UNUSED f32 y, f32 z) {
    gCameras[gActiveCameraID].trans.x_position -= x * coss_f(gCameras[gActiveCameraID].trans.rotation.y_rotation);
    gCameras[gActiveCameraID].trans.z_position -= x * sins_f(gCameras[gActiveCameraID].trans.rotation.y_rotation);
    gCameras[gActiveCameraID].trans.x_position -= z * sins_f(gCameras[gActiveCameraID].trans.rotation.y_rotation);
    gCameras[gActiveCameraID].trans.z_position += z * coss_f(gCameras[gActiveCameraID].trans.rotation.y_rotation);
    gCameras[gActiveCameraID].cameraSegmentID = get_level_segment_index_from_position(
        gCameras[gActiveCameraID].trans.x_position, gCameras[gActiveCameraID].trans.y_position,
        gCameras[gActiveCameraID].trans.z_position);
}

/**
 * Rotate the camera with the given angles.
 */
UNUSED void rotate_camera_segment(s32 angleX, s32 angleY, s32 angleZ) {
    gCameras[gActiveCameraID].trans.rotation.y_rotation += angleX;
    gCameras[gActiveCameraID].trans.rotation.x_rotation += angleY;
    gCameras[gActiveCameraID].trans.rotation.z_rotation += angleZ;
}

/**
 * Returns the segment data of the active camera, but won't apply the offset for cutscenes.
 */
Camera *cam_get_active_camera_no_cutscenes(void) {
    return &gCameras[gActiveCameraID];
}

/**
 * Returns the segment data of the active camera.
 */
Camera *cam_get_active_camera(void) {
    if (gCutsceneCameraActive) {
        return &gCameras[gActiveCameraID + 4];
    }
    return &gCameras[gActiveCameraID];
}

/**
 * Returns the segment data of the active cutscene camera.
 * If no cutscene is active, return player 1's camera.
 */
Camera *get_cutscene_camera_segment(void) {
    if (gCutsceneCameraActive) {
        return &gCameras[4];
    }
    return &gCameras[PLAYER_ONE];
}

/**
 * Return the current floating point projection matrix.
 */
Matrix *get_projection_matrix_f32(void) {
    return &gProjectionMatrixF;
}

/**
 * Return the current fixed point projection matrix.
 */
MatrixS *get_projection_matrix_s16(void) {
    return &gProjectionMatrixS;
}

/**
 * Return the current camera matrix.
 */
Matrix *get_camera_matrix(void) {
    return &gCameraMatrixF;
}

/**
 * Return the screenspace distance to the camera.
 */
f32 get_distance_to_camera(f32 x, f32 y, f32 z) {
    f32 ox, oy, oz;

    guMtxXFMF(gCameraMatrixF, x, y, z, &ox, &oy, &oz);

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

    for (i = 0; i <= gViewportLayout; i++) {
        diffX = x - gCameras[i].trans.x_position;
        diffY = y - gCameras[i].trans.y_position;
        diffZ = z - gCameras[i].trans.z_position;
        distance = sqrtf(((diffX * diffX) + (diffY * diffY)) + (diffZ * diffZ));
        if (distance < dist) {
            gCameras[i].shakeMagnitude = ((dist - distance) * magnitude) / dist;
        }
    }
}

/**
 * Apply a shake to all active cameras.
 */
void set_camera_shake(f32 magnitude) {
    s32 i;
    for (i = 0; i <= gViewportLayout; i++) {
        gCameras[i].shakeMagnitude = magnitude;
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
            rmonPrintf("%x  ", (u16) val & 0xFFFF);
        }
        rmonPrintf("\n");
        if (!val) {} // Fakematch
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
