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

extern u32 osTvType;

/************ .rodata ************/

const char D_800E6F00[] = "Camera Error: Illegal mode!\n";
const char D_800E6F20[] = "Camera Error: Illegal player no!\n";
const char D_800E6F34[] = "cameraPushSprMtx: model stack overflow!!\n";
const char D_800E6F70[] = "\nCam do 2D sprite called with NULL pointer!";
const char D_800E6F9C[] = "CamDo2DSprite FrameNo Overflow !!!\n";
const char D_800E6FC0[] = "cameraPushModelMtx: model stack overflow!!\n";
const char D_800E6FEC[] = "camPushModelMtx: bsp stack overflow!!\n";
const char D_800E7010[] = "camPopModelMtx: model stack negative overflow!!\n";
const char D_800E7048[] = "camPopModelMtx: bsp stack negative overflow!!\n";

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

s32 D_800DD134 = 0;

Vertex D_800DD138 = {
    0, 0, 0, 255, 255, 255, 255
};

// RSP Viewports
Vp D_800DD148[20] = {
    { { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } } },
    { { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } } },
    { { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } } },
    { { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } } },
    { { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } } },
    { { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } } },
    { { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } } },
    { { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } } },
    { { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } } },
    { { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } } },
    { { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } } },
    { { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } } },
    { { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } } },
    { { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } } },
    { { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } } },
    { { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } } },
    { { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } } },
    { { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } } },
    { { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } } },
    { { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } } },
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

s32 sNoControllerPluggedIn = FALSE; // Looks to be a boolean for whether a controller is plugged in. FALSE if plugged in, and TRUE if not.

s16 gButtonMask = 0xFFFF;

/*******************************/

/************ .bss ************/

ObjectSegment gObjectRenderStack[8];
s32 gNumberOfViewports;
s32 gObjectRenderStackPos;
s32 gOjbectRenderStackCap;
s32 D_80120CEC;
ObjectTransform D_80120CF0;
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
Matrix *D_80120D88[6];
Matrix D_80120DA0[5];
Matrix D_80120EE0; // Perspective matrix?
Matrix D_80120F20;
Matrix D_80120F60;
Matrix D_80120FA0;
Matrix D_80120FE0;
Matrix D_80121020;
Matrix D_80121060;
Matrix D_801210A0;
OSMesgQueue sSIMesgQueue;
OSMesg sSIMesgBuf;
OSMesg gSIMesg;
OSContStatus status;
UNUSED s32 D_80121108[2]; //Padding?
ControllerData sControllerData[8];
u16 gControllerButtonsPressed[4];
u16 gControllerButtonsReleased[4];
u8 sPlayerID[16];

/******************************/

#ifdef NON_EQUIVALENT
extern s32 D_B0000578;

void func_80065EA0(void) {
    s32 i, j;
    for (i = 0; i < 5; i++) {
        D_80120D70[i] = &D_80120DA0[i];
    };
    for (j = 0; j < 8; j++) {
        gObjectRenderStackPos = j;
        func_800663DC(200, 200, 200, 0, 0, 180);
    };
    gCutsceneCameraActive = FALSE;
    gObjectRenderStackPos = 0;
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
    guPerspectiveF(D_80120EE0, &perspNorm, CAMERA_DEFAULT_FOV, CAMERA_ASPECT, CAMERA_NEAR, CAMERA_FAR, CAMERA_SCALE);
    func_8006F870(D_80120EE0, D_80120FE0);
    gCurCamFOV = CAMERA_DEFAULT_FOV;
}
#else
GLOBAL_ASM("asm/non_matchings/camera/func_80065EA0.s")
#endif

void func_80066060(s32 arg0, s32 arg1) {
    if (arg0 >= 0 && arg0 < 4) {
        D_800DD2F8[arg0] = arg1;
        gObjectRenderStack[arg0].unk3B = arg1;
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
 */
UNUSED f32 get_current_camera_fov(void) {
    return gCurCamFOV;
}

/**
 * Set the FoV of the viewspace, then recalculate the perspective matrix.
 */
void update_camera_fov(f32 camFieldOfView) {
    if (CAMERA_MIN_FOV < camFieldOfView && camFieldOfView < CAMERA_MAX_FOV && camFieldOfView != gCurCamFOV) {
        gCurCamFOV = camFieldOfView;
        guPerspectiveF(D_80120EE0, &perspNorm, camFieldOfView, CAMERA_ASPECT, CAMERA_NEAR, CAMERA_FAR, CAMERA_SCALE);
        func_8006F870(&D_80120EE0, &D_80120FE0);
    }
}

/**
 * Unused function that recalculates the perspective matrix.
 */
UNUSED void calculate_camera_perspective(void) {
    guPerspectiveF(D_80120EE0, &perspNorm, CAMERA_DEFAULT_FOV, CAMERA_ASPECT, CAMERA_NEAR, CAMERA_FAR, CAMERA_SCALE);
    func_8006F870(&D_80120EE0, &D_80120FE0);
}

UNUSED Matrix *func_80066204(void) {
    return &D_801210A0;
}

s32 get_viewport_count(void) {
    return gNumberOfViewports;
}

s32 get_object_render_stack_pos(void) {
    return gObjectRenderStackPos;
}

void func_80066230(Gfx **dlist, Matrix **mats) {
    ObjectSegment *someStruct;
    s16 sp2A;
    s16 sp28;
    s16 sp26;
    s16 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;

    set_active_viewports_and_object_stack_cap(0);
    set_object_stack_pos(0);
    someStruct = func_80069D20();
    sp2A = someStruct->trans.y_rotation;
    sp28 = someStruct->trans.x_rotation;
    sp26 = someStruct->trans.z_rotation;
    sp20 = someStruct->trans.x_position;
    sp1C = someStruct->trans.y_position;
    sp18 = someStruct->trans.z_position;
    sp24 = someStruct->unk38.word;
    someStruct->trans.z_rotation = 0;
    someStruct->trans.x_rotation = 0;
    someStruct->trans.y_rotation = -0x8000;
    someStruct->unk38.word = 0;
    someStruct->trans.x_position = 0.0f;
    someStruct->trans.y_position = 0.0f;
    someStruct->trans.z_position = 0.0f;
    set_and_normalize_D_8011AFE8(0.0f, 0.0f, -1.0f);
    func_80066CDC(dlist, mats);
    someStruct->unk38.word = sp24;
    someStruct->trans.y_rotation = sp2A;
    someStruct->trans.x_rotation = sp28;
    someStruct->trans.z_rotation = sp26;
    someStruct->trans.x_position = sp20;
    someStruct->trans.y_position = sp1C;
    someStruct->trans.z_position = sp18;
}

f32 func_80066348(f32 xPos, f32 yPos, f32 zPos) {
    s32 index;
    f32 dx, dz, dy;

    index = gObjectRenderStackPos;

    if (gCutsceneCameraActive) {
        index += 4;
    }

    dz = zPos - gObjectRenderStack[index].trans.z_position;
    dx = xPos - gObjectRenderStack[index].trans.x_position;
    dy = yPos - gObjectRenderStack[index].trans.y_position;
    return sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
}

void func_800663DC(s32 xPos, s32 yPos, s32 zPos, s32 arg3, s32 arg4, s32 arg5) {
    gObjectRenderStack[gObjectRenderStackPos].trans.z_rotation = (s16) (arg3 * 0xB6);
    gObjectRenderStack[gObjectRenderStackPos].trans.x_position = (f32) xPos;
    gObjectRenderStack[gObjectRenderStackPos].trans.y_position = (f32) yPos;
    gObjectRenderStack[gObjectRenderStackPos].trans.z_position = (f32) zPos;
    gObjectRenderStack[gObjectRenderStackPos].trans.x_rotation = (s16) (arg4 * 0xB6);
    gObjectRenderStack[gObjectRenderStackPos].unk38.word = (s16) 0;
    gObjectRenderStack[gObjectRenderStackPos].z_velocity = 0.0f;
    gObjectRenderStack[gObjectRenderStackPos].unk28 = 0.0f;
    gObjectRenderStack[gObjectRenderStackPos].unk2C.word = 0.0f;
    gObjectRenderStack[gObjectRenderStackPos].unk30 = 0.0f;
    gObjectRenderStack[gObjectRenderStackPos].x_velocity = 160.0f;
    gObjectRenderStack[gObjectRenderStackPos].trans.y_rotation = (s16) (arg5 * 0xB6);
    gObjectRenderStack[gObjectRenderStackPos].unk3B = D_800DD2F8[gObjectRenderStackPos];
}

/**
 * Write directly to the second set of object stack indeces.
 * The first 4 are reserved for the 4 player viewports, so the misc views, used in the title screen
 * and course previews instead use the next 4.
*/
void write_to_object_render_stack(s32 stackPos, f32 xPos, f32 yPos, f32 zPos, s16 arg4, s16 arg5, s16 arg6) {
    stackPos += 4;
    gObjectRenderStack[stackPos].unk38.word = 0;
    gObjectRenderStack[stackPos].trans.x_position = xPos;
    gObjectRenderStack[stackPos].trans.y_position = yPos;
    gObjectRenderStack[stackPos].trans.z_position = zPos;
    gObjectRenderStack[stackPos].trans.y_rotation = arg4;
    gObjectRenderStack[stackPos].trans.x_rotation = arg5;
    gObjectRenderStack[stackPos].trans.z_rotation = arg6;
    gObjectRenderStack[stackPos].unk34_a.levelSegmentIndex = get_level_segment_index_from_position(xPos, yPos, zPos);
    gCutsceneCameraActive = TRUE;
}

/**
 * Check if the misc camera view is active.
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
 * Sets the cap for the object render stack.
 * If the number passed is within 1-4, then the stack cap is set to
 * how many active viewports there are.
*/
s32 set_active_viewports_and_object_stack_cap(s32 num) {
    if (num >= 0 && num < 4) {
        gNumberOfViewports = num;
    } else {
        gNumberOfViewports = 0;
    }
    switch (gNumberOfViewports) {
        case VIEWPORTS_COUNT_1_PLAYER:
            gOjbectRenderStackCap = 1;
            break;
        case VIEWPORTS_COUNT_2_PLAYERS:
            gOjbectRenderStackCap = 2;
            break;
        case VIEWPORTS_COUNT_3_PLAYERS:
            gOjbectRenderStackCap = 3;
            break;
        case VIEWPORTS_COUNT_4_PLAYERS:
            gOjbectRenderStackCap = 4;
            break;
    }
    if (gObjectRenderStackPos >= gOjbectRenderStackCap) {
        gObjectRenderStackPos = 0;
    }
    return gOjbectRenderStackCap;
}

/**
 * Sets the object stack pos to the passed number.
 * If it's not within 1-4, then it's set to 0.
*/
void set_object_stack_pos(s32 num) {
    if (num >= 0 && num < 4) {
        gObjectRenderStackPos = num;
    } else {
        gObjectRenderStackPos = 0;
    }
}

#ifdef NON_EQUIVALENT

// Has regalloc/stack issues
// Proposed name: init_viewports
void func_80066610(void) {
    s32 width;
    s32 height;
    s32 s3;
    s32 yPos;
    s32 xPos;
    s32 i;

    D_800DD134 = 1 - D_800DD134;
    for (i = 0; i < 4; i++) {
        if (gScreenViewports[i].flags & VIEWPORT_UNK_04) {
            gScreenViewports[i].flags &= ~VIEWPORT_UNK_01;
        } else if (gScreenViewports[i].flags & VIEWPORT_UNK_02) {
            gScreenViewports[i].flags |= VIEWPORT_UNK_01;
        }
        gScreenViewports[i].flags &= ~VIEWPORT_UNK_02 | VIEWPORT_UNK_04;
        if (gScreenViewports[i].flags & 1) {
            if (!(gScreenViewports[i].flags & VIEWPORT_X_CUSTOM)) {
                // Issue here
                xPos = (gScreenViewports[i].x1 * 4) + (((gScreenViewports[i].x2 - gScreenViewports[i].x1) + 1) * 2);
            } else {
                xPos = gScreenViewports[i].posX;
                xPos *= 4;
            }
            if (!(gScreenViewports[i].flags & VIEWPORT_Y_CUSTOM)) {
                // Issue here
                yPos = (gScreenViewports[i].y1 * 4) + (((gScreenViewports[i].y2 - gScreenViewports[i].y1) + 1) * 2);
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
                height = gScreenViewports[i].y2 - gScreenViewports[i].y1;
                height += 1;
                height *= 2;
            } else {
                height = gScreenViewports[i].height;
                height *= 2;
            }
            s3 = i + (D_800DD134 * 5);
            s3 += 10;
            if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
                height = -height;
            }
            D_800DD148[s3].vp.vtrans[0] = xPos;
            D_800DD148[s3].vp.vtrans[1] = yPos;
            D_800DD148[s3].vp.vscale[0] = width;
            D_800DD148[s3].vp.vscale[1] = height;
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/camera/func_80066610.s")
#endif

void func_80066818(s32 viewPortIndex, s32 arg1) {
    if (arg1 != 0) {
        gScreenViewports[viewPortIndex].flags |= VIEWPORT_UNK_01;
    } else {
        gScreenViewports[viewPortIndex].flags |= VIEWPORT_UNK_02;
    }
    gScreenViewports[viewPortIndex].flags &= ~VIEWPORT_UNK_04;
}

void func_80066894(s32 viewPortIndex, s32 arg1) {
    if (arg1 != 0) {
        gScreenViewports[viewPortIndex].flags &= ~VIEWPORT_UNK_01;
    } else {
        gScreenViewports[viewPortIndex].flags |= VIEWPORT_UNK_04;
    }
    gScreenViewports[viewPortIndex].flags &= ~VIEWPORT_UNK_02;
}

s32 func_80066910(s32 viewPortIndex) {
    return gScreenViewports[viewPortIndex].flags & VIEWPORT_UNK_01;
}

// proposed name: resize_viewport
void func_80066940(s32 viewPortIndex, s32 x1, s32 y1, s32 x2, s32 y2) {
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

    if ((x1 >= width) || (x2 < 0) || (y1 >= height) || (y2 < 0)) {
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
// !@bug Viewport Y writes to the X value. Luckily, all cases this function is called use VIEWPORT_AUTO,
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
 */
void copy_viewport_frame_size_to_coords(s32 viewPortIndex, s32 *x1, s32 *y1, s32 *x2, s32 *y2) {
    *x1 = gScreenViewports[viewPortIndex].x1;
    *y1 = gScreenViewports[viewPortIndex].y1;
    *x2 = gScreenViewports[viewPortIndex].x2;
    *y2 = gScreenViewports[viewPortIndex].y2;
}

/**
 * Unused function that sets the passed values to the framebuffer's size in coordinates.
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

void func_80066CDC(Gfx **dlist, Matrix **mats) {
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
        gObjectRenderStackPos = 1;
    }
    widthAndHeight = get_video_width_and_height_as_s32();
    temp_t0 = widthAndHeight >> 16;
    temp_a3 = temp_t0 >> 1;
    if (gScreenViewports[gObjectRenderStackPos].flags & VIEWPORT_UNK_01) {
        gDPSetScissor((*dlist)++, SCISSOR_INTERLACE,
            gScreenViewports[gObjectRenderStackPos].scissorX1,
            gScreenViewports[gObjectRenderStackPos].scissorY1,
            gScreenViewports[gObjectRenderStackPos].scissorX2,
            gScreenViewports[gObjectRenderStackPos].scissorY2
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
            if (gObjectRenderStackPos == 0) {
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
            if (gObjectRenderStackPos == 0) {
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
            switch (gObjectRenderStackPos) {
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
                if (gObjectRenderStackPos < 2) {
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

void func_80067A3C(Gfx **dlist) {
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
        if (numViewports == 2) {
            numViewports = 3;
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
                switch (gObjectRenderStackPos) {
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
                switch (gObjectRenderStackPos) {
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
                switch (gObjectRenderStackPos) {
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

void func_80067D3C(Gfx **dlist, UNUSED Matrix **mats) {
    s32 temp;

    gSPPerspNormalize((*dlist)++, perspNorm);

    temp = gObjectRenderStackPos;
    if (gCutsceneCameraActive) {
        gObjectRenderStackPos += 4;
    }

    D_80120CF0.y_rotation = 0x8000 + gObjectRenderStack[gObjectRenderStackPos].trans.y_rotation;
    D_80120CF0.x_rotation = gObjectRenderStack[gObjectRenderStackPos].trans.x_rotation + gObjectRenderStack[gObjectRenderStackPos].unk38.word;
    D_80120CF0.z_rotation = gObjectRenderStack[gObjectRenderStackPos].trans.z_rotation;

    D_80120CF0.x_position = -gObjectRenderStack[gObjectRenderStackPos].trans.x_position;
    D_80120CF0.y_position = -gObjectRenderStack[gObjectRenderStackPos].trans.y_position;
    if (D_80120D18 != 0) {
        D_80120CF0.y_position -= gObjectRenderStack[gObjectRenderStackPos].unk30;
    }
    D_80120CF0.z_position = -gObjectRenderStack[gObjectRenderStackPos].trans.z_position;

    func_8006FE74(&D_80120F60, &D_80120CF0);
    func_8006F768(&D_80120F60, &D_80120EE0, &D_80120F20);

    D_80120CF0.y_rotation = -0x8000 - gObjectRenderStack[gObjectRenderStackPos].trans.y_rotation;
    D_80120CF0.x_rotation = -(gObjectRenderStack[gObjectRenderStackPos].trans.x_rotation + gObjectRenderStack[gObjectRenderStackPos].unk38.word);
    D_80120CF0.z_rotation = -gObjectRenderStack[gObjectRenderStackPos].trans.z_rotation;
    D_80120CF0.scale = 1.0f;
    D_80120CF0.x_position = gObjectRenderStack[gObjectRenderStackPos].trans.x_position;
    D_80120CF0.y_position = gObjectRenderStack[gObjectRenderStackPos].trans.y_position;
    if (D_80120D18 != 0) {
        D_80120CF0.y_position += gObjectRenderStack[gObjectRenderStackPos].unk30;
    }
    D_80120CF0.z_position = gObjectRenderStack[gObjectRenderStackPos].trans.z_position;

    func_8006FC30(D_80120FA0, &D_80120CF0);
    func_8006F870(&D_80120FA0, &D_80121020);

    gObjectRenderStackPos = temp;
}

/**
 * Sets the Y value of the Y axis in the matrix to the passed value.
 * This is used to vertically scale ortho geometry to look identical across NTSC and PAL systems.
 */
void set_ortho_matrix_height(f32 value) {
    gOrthoMatrix[1][1] = value;
}

void func_80067F2C(Gfx **dlist, Matrix **mats) {
    u32 widthAndHeight;
    s32 width, height;
    s32 i, j;

    widthAndHeight = get_video_width_and_height_as_s32();
    height = GET_VIDEO_HEIGHT(widthAndHeight);
    width = GET_VIDEO_WIDTH(widthAndHeight);
    func_8006F870(&gOrthoMatrix, (Matrix *)*mats);
    D_80120D88[0] = (Matrix *) *mats;
    D_800DD148[gObjectRenderStackPos + 5].vp.vscale[0] = width * 2;
    D_800DD148[gObjectRenderStackPos + 5].vp.vscale[1] = width * 2;
    D_800DD148[gObjectRenderStackPos + 5].vp.vtrans[0] = width * 2;
    D_800DD148[gObjectRenderStackPos + 5].vp.vtrans[1] = height * 2;
    gSPViewport((*dlist)++, OS_K0_TO_PHYSICAL(&D_800DD148[gObjectRenderStackPos + 5]));
    gSPMatrix((*dlist)++, OS_PHYSICAL_TO_K0((*mats)++), G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    D_80120D1C = 0;
    D_80120D08 = 0;

    for (i = 0; i < 4; i++) {
        //Required to be one line, but the "\" fixes that.
        for (j = 0; j < 4; j++){ \
            D_80120F20[i][j] = gOrthoMatrix[i][j];
        }
    }
}

void func_8006807C(Gfx **dlist, Matrix **mats) {
    func_8006FE74(&D_80121060, &D_800DD288);
    func_8006F768(&D_80121060, &D_80120EE0, &D_80120F20);
    func_8006FE74(D_80120D70[0], &D_800DD2A0);
    func_8006F768(D_80120D70[0], &D_80120F20, &D_80121060);
    func_8006F870(&D_80121060, (Matrix *)*mats);
    gSPMatrix((*dlist)++, OS_PHYSICAL_TO_K0((*mats)++), G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    D_80120D1C = 0;
    D_80120D08 = 0;
}

void func_80068158(Gfx **dlist, s32 width, s32 height, s32 posX, s32 posY) {
    s32 tempWidth = (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) ? -width : width;
    // Antipiracy measure. Flips the screen upside down.
    if (gAntiPiracyViewport) {
        height = -height;
        tempWidth = -width;
    }
    if (!(gScreenViewports[gObjectRenderStackPos].flags & VIEWPORT_UNK_01)) {
        D_800DD148[gObjectRenderStackPos].vp.vtrans[0] = posX * 4;
        D_800DD148[gObjectRenderStackPos].vp.vtrans[1] = posY * 4;
        D_800DD148[gObjectRenderStackPos].vp.vscale[0] = tempWidth * 4;
        D_800DD148[gObjectRenderStackPos].vp.vscale[1] = height * 4;
        gSPViewport((*dlist)++, OS_PHYSICAL_TO_K0(&D_800DD148[gObjectRenderStackPos]));
    } else {
        gSPViewport((*dlist)++, OS_PHYSICAL_TO_K0(&D_800DD148[gObjectRenderStackPos + 10 + (D_800DD134 * 5)]));
    }
}

void func_800682AC(Gfx **dlist) {
    u32 widthAndHeight, width, height;
    gObjectRenderStackPos = 4;
    widthAndHeight = get_video_width_and_height_as_s32();
    height = GET_VIDEO_HEIGHT(widthAndHeight);
    width = GET_VIDEO_WIDTH(widthAndHeight);
    if (!(gScreenViewports[gObjectRenderStackPos].flags & VIEWPORT_UNK_01)) {
        gDPSetScissor((*dlist)++, G_SC_NON_INTERLACE, 0, 0, width - 1, height - 1);
        func_80068158(dlist, width >> 1, height >> 1, width >> 1, height >> 1);
    } else {
        func_80067A3C(dlist);
        func_80068158(dlist, 0, 0, 0, 0);
    }
    gObjectRenderStackPos = 0;
}

void func_80068408(Gfx **dlist, Matrix **mats) {
    func_800705F8(D_80120D70[D_80120D1C], 0.0f, 0.0f, 0.0f);
    func_8006F768(D_80120D70[D_80120D1C], &D_80120F20, &D_80121060);
    func_8006F870(&D_80121060, (Matrix *)*mats);
    D_80120D88[D_80120D1C] = (Matrix *) *mats;
    gSPMatrix((*dlist)++, OS_PHYSICAL_TO_K0((*mats)++), D_80120D08 << 6);
}

void func_80068508(s32 arg0) {
    D_80120D0C = arg0;
}

/**
 * Calculates angle from object to camera, then renders the sprite as a billboard, facing the camera.
 */
s32 render_sprite_billboard(Gfx **dlist, Matrix **mtx, Vertex **vertexList, Object *obj, unk80068514_arg4 *arg4, s32 flags) {
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
    if (flags & 1) {
        sp5C = D_80120D28[D_80120D20] - obj->segment.trans.x_position;
        sp58 = D_80120D40[D_80120D20] - obj->segment.trans.y_position;
        var_f20 = D_80120D58[D_80120D20] - obj->segment.trans.z_position;
        sp4C = cosine_s(obj->segment.trans.y_rotation);
        temp_f0 = sine_s(obj->segment.trans.y_rotation);
        sp44 = (sp5C * temp_f0) + (var_f20 * sp4C);
        var_f20 = (var_f20 * temp_f0) - (sp5C * sp4C);
        sp38 = arctan2_f(sp44, sqrtf((sp58 * sp58) + (var_f20 * var_f20)));
        sp3C = -func_80070830(arctan2_f(sp44, var_f20)) >> 8;
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
        D_80120CF0.y_rotation = arctan2_f(sp5C, var_f20);
        D_80120CF0.x_rotation = -arctan2_f(sp58, sp50);
        D_80120CF0.z_rotation = sp34;
        D_80120CF0.scale = obj->segment.trans.scale;
        D_80120CF0.x_position = obj->segment.trans.x_position;
        D_80120CF0.y_position = obj->segment.trans.y_position;
        D_80120CF0.z_position = obj->segment.trans.z_position;
        func_8006FC30(D_80121060, &D_80120CF0);
        D_80120D1C++;
        func_8006F768((Matrix*) D_80121060, (Matrix*)&D_80120D70[D_80120D1C-1][0][0], (Matrix*)&D_80120D70[D_80120D1C][0][0]);
        func_8006F768(D_80120D70[D_80120D1C], (Matrix*) D_80120F20, (Matrix*) D_80121060);
        func_8006F870((Matrix*) D_80121060, *mtx);
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
            sp34 = gObjectRenderStack[gObjectRenderStackPos].trans.z_rotation + obj->segment.trans.z_rotation;
        } else {
            sp34 = gObjectRenderStack[gObjectRenderStackPos + 4].trans.z_rotation + obj->segment.trans.z_rotation;
        }
        var_s2 = obj->segment.unk18;
        D_80120D1C++;
        func_80070130((f32 (*)[4]) D_80120D70[D_80120D1C], sp34, obj->segment.trans.scale, gVideoAspectRatio);
        func_8006F870(D_80120D70[D_80120D1C], *mtx);
        D_80120D88[D_80120D1C] = *mtx;
        gSPMatrix((*dlist)++, OS_PHYSICAL_TO_K0((*mtx)++), 0x80);
        gDkrEnableBillboard((*dlist)++);
    }
    if (D_80120D0C == 0) {
        var_s2 = ((var_s2 & 0xFF) * arg4->unk0) >> 8;
    }
    flags &= ~1;
    if (flags & 4) {
        flags |= 1;
    }
    func_8007BF34(dlist, arg4->unk6 | (flags & 0xF));
    if (!(flags & 0x100)) {
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

void func_80068BF4(Gfx **arg0, Matrix **arg1, Vertex **arg2, ObjectSegment *arg3, unk80068BF4 *arg4, s32 arg5) {
    UNUSED s32 pad;
    f32 scale;
    s32 index;
    Vertex *temp_v1;
    Matrix sp90;
    Matrix sp50;

    if (arg4 != NULL) {
        temp_v1 = *arg2;
        temp_v1->x = arg3->trans.x_position;
        temp_v1->y = arg3->trans.y_position;
        temp_v1->z = arg3->trans.z_position;
        temp_v1->r = 255;
        temp_v1->g = 255;
        temp_v1->b = 255;
        temp_v1->a = 255;
        gDkrVertices((*arg0)++, OS_PHYSICAL_TO_K0(*arg2), (((s32)OS_PHYSICAL_TO_K0(*arg2)) & 6), 13);
        (*arg2)++; // Can't be done in the macro?
        index = arg3->unk18;
        D_80120D1C ++;
        D_80120CF0.y_rotation = -arg3->trans.y_rotation;
        D_80120CF0.x_rotation = -arg3->trans.x_rotation;
        D_80120CF0.z_rotation = gObjectRenderStack[gObjectRenderStackPos].trans.z_rotation + arg3->trans.z_rotation;
        D_80120CF0.x_position = 0.0f;
        D_80120CF0.y_position = 0.0f;
        D_80120CF0.z_position = 0.0f;
        if (gAdjustViewportHeight) {
            scale = arg3->trans.scale;
            func_80070638(sp50, scale, scale, 1.0f);
            func_80070130(sp90, 0, 1.0f, gVideoAspectRatio);
            func_8006F768(&sp90, &sp50, &D_80121060);
        } else {
            scale = arg3->trans.scale;
            func_80070638(D_80121060, scale, scale, 1.0f);
        }
        func_8006FE74(&sp90, &D_80120CF0);
        func_8006F768(&D_80121060, &sp90, D_80120D70[D_80120D1C]);
        func_8006F870(D_80120D70[D_80120D1C], *arg1);
        D_80120D88[D_80120D1C] = *arg1;
        gSPMatrix((*arg0)++, OS_PHYSICAL_TO_K0((*arg1)++), G_MTX_DKR_INDEX_2);
        gDkrEnableBillboard((*arg0)++);
        if (D_80120D0C == 0) {
            index =  (((u8) index) * arg4->unk0) >> 8;
        }
        func_8007BF34(arg0, arg4->unk6 | arg5);
        if (index >= arg4->unk0) {
            index = arg4->unk0 - 1;
        }
        gSPDisplayList((*arg0)++, arg4->unkC[index]);
        if (--D_80120D1C == 0) {
            index = 0;
        } else {
            index = 1;
        }
        gDkrInsertMatrix((*arg0)++, 0, index << 6);
        gDkrDisableBillboard((*arg0)++);
    }
}

GLOBAL_ASM("asm/non_matchings/camera/func_80068FA8.s")

void func_80069484(Gfx **arg0, Matrix **arg1, ObjectTransform *arg2, f32 arg3, f32 arg4) {
    f32 tempX;
    f32 tempY;
    f32 tempZ;
    s32 index;
    f32 scaleFactor;

    func_8006FC30(D_80121060, arg2);
    if (arg4 != 0.0f) {
        func_8006FE30(&D_80121060, arg4);
    }
    if (arg3 != 1.0f) {
        func_8006FE04(&D_80121060, arg3);
    }
    func_8006F768(&D_80121060, D_80120D70[D_80120D1C], D_80120D70[D_80120D1C + 1]);
    func_8006F768(D_80120D70[D_80120D1C + 1], &D_80120F20, &D_801210A0);
    func_8006F870(&D_801210A0, *arg1);
    D_80120D1C++;
    D_80120D88[0, D_80120D1C] = *arg1; // Should be [D_80120D1C], but only matches with [0, D_80120D1C]
    if (1) { } if (1) { } if (1) { }; // Necessary to match
    gSPMatrix((*arg0)++, OS_PHYSICAL_TO_K0((*arg1)++), G_MTX_DKR_INDEX_1);
    guMtxXFMF(*D_80120D70[D_80120D1C], 0.0f, 0.0f, 0.0f, &tempX, &tempY, &tempZ);
    index = gObjectRenderStackPos;
    if (gCutsceneCameraActive) {
        index += 4;
    }
    tempX = gObjectRenderStack[index].trans.x_position - tempX;
    tempY = gObjectRenderStack[index].trans.y_position - tempY;
    tempZ = gObjectRenderStack[index].trans.z_position - tempZ;
    D_80120CF0.y_rotation = -arg2->y_rotation;
    D_80120CF0.x_rotation = -arg2->x_rotation;
    D_80120CF0.z_rotation = -arg2->z_rotation;
    D_80120CF0.x_position = 0.0f;
    D_80120CF0.y_position = 0.0f;
    D_80120CF0.z_position = 0.0f;
    D_80120CF0.scale = 1.0f;
    func_8006FE74(&D_80121060, &D_80120CF0);
    guMtxXFMF(D_80121060, tempX, tempY, tempZ, &tempX, &tempY, &tempZ);
    scaleFactor = 1.0f / arg2->scale;
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

GLOBAL_ASM("asm/non_matchings/camera/func_80069790.s")

UNUSED void func_800699E4(f32 *arg0, f32 *arg1, f32 *arg2) {
    *arg0 = D_80120D28[D_80120D20];
    *arg1 = D_80120D40[D_80120D20];
    *arg2 = D_80120D58[D_80120D20];
}

void func_80069A40(Gfx **dlist) {
    D_80120D20--;
    D_80120D1C--;

    // Fakematch?
    { s32 temp = D_80120D20; if ((temp && temp) != 0){} }

    if (D_80120D1C > 0) {
        gSPMatrix((*dlist)++, OS_PHYSICAL_TO_K0(D_80120D88[D_80120D1C]), G_MTX_DKR_INDEX_1);
    }
    else {
        gDkrInsertMatrix((*dlist)++, G_MWO_MATRIX_XX_XY_I, 0);
    }
}

UNUSED void func_80069ACC(f32 x, f32 y, f32 z) {
    gObjectRenderStack[gObjectRenderStackPos].trans.x_position += x;
    gObjectRenderStack[gObjectRenderStackPos].trans.y_position += y;
    gObjectRenderStack[gObjectRenderStackPos].trans.z_position += z;
    gObjectRenderStack[gObjectRenderStackPos].unk34_a.levelSegmentIndex =
        get_level_segment_index_from_position(
            gObjectRenderStack[gObjectRenderStackPos].trans.x_position,
            gObjectRenderStack[gObjectRenderStackPos].trans.y_position,
            gObjectRenderStack[gObjectRenderStackPos].trans.z_position);
}

UNUSED void func_80069B70(f32 x, UNUSED f32 y, f32 z) {
    gObjectRenderStack[gObjectRenderStackPos].trans.x_position -= x * sine_s(gObjectRenderStack[gObjectRenderStackPos].trans.y_rotation);
    gObjectRenderStack[gObjectRenderStackPos].trans.z_position -= x * cosine_s(gObjectRenderStack[gObjectRenderStackPos].trans.y_rotation);
    gObjectRenderStack[gObjectRenderStackPos].trans.x_position -= z * cosine_s(gObjectRenderStack[gObjectRenderStackPos].trans.y_rotation);
    gObjectRenderStack[gObjectRenderStackPos].trans.z_position += z * sine_s(gObjectRenderStack[gObjectRenderStackPos].trans.y_rotation);
    gObjectRenderStack[gObjectRenderStackPos].unk34_a.levelSegmentIndex =
        get_level_segment_index_from_position(
            gObjectRenderStack[gObjectRenderStackPos].trans.x_position,
            gObjectRenderStack[gObjectRenderStackPos].trans.y_position,
            gObjectRenderStack[gObjectRenderStackPos].trans.z_position);
}

UNUSED void func_80069CB4(s32 xRotation, s32 yRotation, s32 zRotation) {
    gObjectRenderStack[gObjectRenderStackPos].trans.y_rotation += xRotation;
    gObjectRenderStack[gObjectRenderStackPos].trans.x_rotation += yRotation;
    gObjectRenderStack[gObjectRenderStackPos].trans.z_rotation += zRotation;
}

ObjectSegment *func_80069CFC(void) {
    return &gObjectRenderStack[gObjectRenderStackPos];
}

ObjectSegment *func_80069D20(void) {
    if (gCutsceneCameraActive) {
        return &gObjectRenderStack[gObjectRenderStackPos + 4];
    }
    return &gObjectRenderStack[gObjectRenderStackPos];
}

ObjectSegment *func_80069D7C(void) {
    if (gCutsceneCameraActive) {
        return &gObjectRenderStack[4];
    }
    return &gObjectRenderStack[0];
}

Matrix *func_80069DA4(void) {
    return &D_80120FA0;
}

Matrix *func_80069DB0(void) {
    return &D_80120FE0;
}

Matrix *func_80069DBC(void) {
    return &D_80120F60;
}

f32 func_80069DC8(f32 x, f32 y, f32 z) {
    f32 ox, oy, oz;

    guMtxXFMF(D_80120F60, x, y, z, &ox, &oy, &oz);

    return oz;
}

void func_80069E14(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f14;
    f32 temp_f2;
    s32 i;

    for (i = 0; i <= gNumberOfViewports; i++) {
        temp_f0 = arg0 - gObjectRenderStack[i].trans.x_position;
        temp_f2 = arg1 - gObjectRenderStack[i].trans.y_position;
        temp_f14 = arg2 - gObjectRenderStack[i].trans.z_position;
        temp_f0_2 = sqrtf(((temp_f0 * temp_f0) + (temp_f2 * temp_f2)) + (temp_f14 * temp_f14));
        if (temp_f0_2 < arg3) {
            gObjectRenderStack[i].unk30 = ((arg3 - temp_f0_2) * arg4) / arg3;
        }
    }
}

void func_80069F28(f32 arg0) {
    s32 i;
    for (i = 0; i <= gNumberOfViewports; i++) {
        gObjectRenderStack[i].unk30 = arg0;
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
        if (!val){}
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

OSMesgQueue *get_si_mesg_queue(void) {
    return &sSIMesgQueue;
}

/**
 * Initialise the player controllers, and return the status when finished.
 */
s32 init_controllers(void) {
    UNUSED s32 *temp1; // Unused
    u8 bitpattern;
    UNUSED s32 *temp2; // Unused

    osCreateMesgQueue(&sSIMesgQueue, &sSIMesgBuf, 1);
    osSetEventMesg(OS_EVENT_SI, &sSIMesgQueue, gSIMesg);
    osContInit(&sSIMesgQueue, &bitpattern, &status);
    osContStartReadData(&sSIMesgQueue);
    initialise_player_ids();

    sNoControllerPluggedIn = FALSE;

    if ((bitpattern & CONT_ABSOLUTE) && (!(status.errno & CONT_NO_RESPONSE_ERROR))) {
        return CONTROLLER_EXISTS;
    }

    if (!bitpattern) {} // Fakematch

    sNoControllerPluggedIn = TRUE;

    return CONTROLLER_MISSING;
}

GLOBAL_ASM("asm/non_matchings/camera/func_8006A1C4.s")

/**
 * Set the first 4 player ID's to the controller numbers, so players can input in the menus after boot.
 */
void initialise_player_ids(void) {
    s32 i;
    for (i = 0; i < MAXCONTROLLERS; i++) {
        sPlayerID[i] = i;
    }
}

/**
 * Assign the first four player ID's to the index of the connected players.
 * Assign the next four player ID's to the index of the players who are not connected.
 */
void assign_player_ids(s8 *activePlayers) {
    s32 i;
    s32 temp = 0;
    for (i = 0; i < MAXCONTROLLERS; i++) {
        if (activePlayers[i]) {
            sPlayerID[temp++] = i;
        }
    }
    for (i = 0; i < MAXCONTROLLERS; i++) {
        if (!activePlayers[i]) {
            sPlayerID[temp++] = i;
        }
    }
}

/**
 * Returns the id of the selected index.
 */
u8 get_player_id(s32 player) {
    return sPlayerID[player];
}

/**
 * Swaps the ID's of the first two indexes.
 * This applies in 2 player adventure, so that player 2 can control the car in the overworld.
 */
void swap_player_1_and_2_ids(void) {
    u8 tempID = sPlayerID[0];
    sPlayerID[0] = sPlayerID[1];
    sPlayerID[1] = tempID;
}

/**
 * Returns the buttons that are currently pressed down on the controller.
 */
u16 get_buttons_held_from_player(s32 player) {
    return sControllerData[sPlayerID[player]].buttonData;
}

/**
 * Returns the buttons that are newly pressed during that frame.
 * NOTE: This was a u16, but we only got a match in menu_ghost_data_loop when it was a u32 for some reason
 */
u32 get_buttons_pressed_from_player(s32 player) {
    return gControllerButtonsPressed[sPlayerID[player]];
}

/**
 * Unused function that returns the buttons that are no longer pressed in that frame.
 */
UNUSED u16 get_buttons_released_from_player(s32 player) {
    return gControllerButtonsReleased[sPlayerID[player]];
}

/**
 * Clamps the X joystick axis of the selected player to 70 and returns it.
 */
s8 clamp_joystick_x_axis(s32 player) {
    return clamp_joystick(sControllerData[sPlayerID[player]].rawStickX);
}

/**
 * Clamps the Y joystick axis of the selected player to 70 and returns it.
 */
s8 clamp_joystick_y_axis(s32 player) {
    return clamp_joystick(sControllerData[sPlayerID[player]].rawStickY);
}

/**
 * Keeps the joysticks axis reads no higher than 70 (of a possible 127 or -128)
 * Will also pull the reading towards the centre.
 */
s8 clamp_joystick(s8 stickMag) {
    if (stickMag < JOYSTICK_DEADZONE && stickMag > -JOYSTICK_DEADZONE) {
        return 0;
    }
    if (stickMag > 0) {
        stickMag -= 8;
        if (stickMag > JOYSTICK_MAX_RANGE) {
            stickMag = JOYSTICK_MAX_RANGE;
        }
    } else {
        stickMag += 8;
        if (stickMag < -JOYSTICK_MAX_RANGE) {
            stickMag = -JOYSTICK_MAX_RANGE;
        }
    }
    return stickMag;
}

/**
 * Used when anti-cheat/anti-tamper has failed in func_8006A6B0()
 */
void disable_button_mask(void) {
    gButtonMask = 0;
}
