/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065EA0 */

#include "camera.h"
#include "audio.h"
#include "unknown_00BC20.h"
#include "unknown_06B2B0.h"
#include "unknown_0255E0.h"
#include "video.h"
#include "lib/src/libc/rmonPrintf.h"

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

s8 D_800DD060 = 0;

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

// Not sure about the typing here
s16 D_800DD138[8] = {
    0, 0, 0, -1, -1, 0, 0, 0
};

// RSP Viewports
Vp D_800DD148[20] = {
    { 0, 0, 0x01FF, 0, 0, 0, 0x01FF, 0 },
    { 0, 0, 0x01FF, 0, 0, 0, 0x01FF, 0 },
    { 0, 0, 0x01FF, 0, 0, 0, 0x01FF, 0 },
    { 0, 0, 0x01FF, 0, 0, 0, 0x01FF, 0 },
    { 0, 0, 0x01FF, 0, 0, 0, 0x01FF, 0 },
    { 0, 0, 0x01FF, 0, 0, 0, 0x01FF, 0 },
    { 0, 0, 0x01FF, 0, 0, 0, 0x01FF, 0 },
    { 0, 0, 0x01FF, 0, 0, 0, 0x01FF, 0 },
    { 0, 0, 0x01FF, 0, 0, 0, 0x01FF, 0 },
    { 0, 0, 0x01FF, 0, 0, 0, 0x01FF, 0 },
    { 0, 0, 0x01FF, 0, 0, 0, 0x01FF, 0 },
    { 0, 0, 0x01FF, 0, 0, 0, 0x01FF, 0 },
    { 0, 0, 0x01FF, 0, 0, 0, 0x01FF, 0 },
    { 0, 0, 0x01FF, 0, 0, 0, 0x01FF, 0 },
    { 0, 0, 0x01FF, 0, 0, 0, 0x01FF, 0 },
    { 0, 0, 0x01FF, 0, 0, 0, 0x01FF, 0 },
    { 0, 0, 0x01FF, 0, 0, 0, 0x01FF, 0 },
    { 0, 0, 0x01FF, 0, 0, 0, 0x01FF, 0 },
    { 0, 0, 0x01FF, 0, 0, 0, 0x01FF, 0 },
    { 0, 0, 0x01FF, 0, 0, 0, 0x01FF, 0 },
};

unk8011D510 D_800DD288 = {  
    0, 0, 0, 0, 1.0f, 0.0f, 0.0f, -281.0f,
};

unk8011D510 D_800DD2A0 = {  
    0, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f,
};

Matrix D_800DD2B8 = {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 160.0f },
};

u8 D_800DD2F8[8] = {
    0, 0, 0, 0, 0, 0, 0, 0
};

s32 D_800DD300 = 0; // Currently unknown, might be a different type.

s16 gButtonMask = 0xFFFF;

/*******************************/

/************ .bss ************/

unk80120AC0 D_80120AC0[8];
s32 gNumberOfViewports;
s32 D_80120CE4;
s32 D_80120CE8;
s32 D_80120CEC;
s32 D_80120CF0[6];
s32 D_80120D08;
s32 D_80120D0C;
f32 gCurCamFOV;
s8 D_80120D14;
u8 D_80120D15;
s32 D_80120D18;
s32 D_80120D1C;
s32 D_80120D20[2];
s32 D_80120D28[6];
s32 D_80120D40[6];
u16 *perspNorm[6];
Mtx *D_80120D70[6];
s32 D_80120D88[6];
Mtx D_80120DA0[5];
Matrix D_80120EE0;
Matrix D_80120F20;
Matrix D_80120F60;
Matrix D_80120FA0;
Matrix D_80120FE0;
Matrix D_80121020;
Matrix D_80121060;
Matrix D_801210A0;
OSMesgQueue *D_801210E0[6];
OSMesg *D_801210F8;
OSMesg D_801210FC;
OSContStatus status;
s32 D_80121108[2]; //Padding?
unk80121110 D_80121110[8];
u16 D_80121140[4];
u16 D_80121148[4];
u8 D_80121150[16];

/******************************/

#if 00
extern s32 D_B0000578;

void func_80065EA0(void) {
    s32 i, j;
    for (i = 0; i < 5; i++) {
        D_80120D70[i] = &D_80120DA0[i];
    };
    for (j = 0; j < 8; j++) {
        D_80120CE4 = j;
        func_800663DC(200, 200, 200, 0, 0, 180);
    };
    D_80120D14 = 0;
    D_80120CE4 = 0;
    D_80120D1C = 0;
    D_80120D20[0] = 0;
    gNumberOfViewports = 0;
    D_80120D0C = 0;
    D_80120D18 = 0;
    D_80120D15 = 0;
    D_800DD060 = 0;
    while (IO_READ(PI_STATUS_REG) & 3) {
    }
    if ((D_B0000578 & 0xFFFF) != 0x8965) {
        D_800DD060 = 1;
    }
    guPerspectiveF(D_80120EE0, perspNorm[5], CAMERA_DEFAULT_FOV, CAMERA_ASPECT, CAMERA_NEAR, CAMERA_FAR, CAMERA_SCALE);
    func_8006F870(D_80120EE0, D_80120FE0);
    gCurCamFOV = CAMERA_DEFAULT_FOV;
}
#else
GLOBAL_ASM("asm/non_matchings/camera/func_80065EA0.s")
#endif

void func_80066060(s32 arg0, s32 arg1) {
    if (arg0 >= 0 && arg0 < 4) {
        D_800DD2F8[arg0] = arg1;
        D_80120AC0[arg0].unk3B = arg1;
    }
}

void func_80066098(s8 arg0) {
    s8 temp = (arg0 << 24) >> 24;
    if (!osTvType) {
        D_80120D15 = temp;
    }
}
void func_800660C0(void) {
    D_80120D18 = 1;
}
void func_800660D0(void) {
    D_80120D18 = 0;
}
/* Unused? */
f32 get_current_camera_fov(void) {
    return gCurCamFOV;
}

void update_camera_fov(f32 camFieldOfView) {
    if (CAMERA_MIN_FOV < camFieldOfView && camFieldOfView < CAMERA_MAX_FOV && camFieldOfView != gCurCamFOV) {
        gCurCamFOV = camFieldOfView;
        guPerspectiveF(D_80120EE0, &perspNorm[5], camFieldOfView, CAMERA_ASPECT, CAMERA_NEAR, CAMERA_FAR, CAMERA_SCALE);
        func_8006F870(D_80120EE0, D_80120FE0);
    }
}

void func_80066194(void) {
    guPerspectiveF(D_80120EE0, &perspNorm[5], CAMERA_DEFAULT_FOV, CAMERA_ASPECT, CAMERA_NEAR, CAMERA_FAR, CAMERA_SCALE);
    func_8006F870(D_80120EE0, D_80120FE0);
}

/* Unused? */
Matrix *func_80066204(void) {
    return &D_801210A0;
}

s32 get_viewport_count(void) {
    return gNumberOfViewports;
}

s32 func_80066220(void) {
    return D_80120CE4;
}

void func_80066230(Gfx **dlist, s32 arg1) {
    unk80120AC0 *someStruct;
    s16 sp2A;
    s16 sp28;
    s16 sp26;
    s16 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;

    func_8006652C(0);
    func_800665E8(0);
    someStruct = func_80069D20();
    sp2A = someStruct->unk0;
    sp28 = someStruct->unk2;
    sp26 = someStruct->unk4;
    sp20 = someStruct->x_position;
    sp1C = someStruct->y_position;
    sp18 = someStruct->z_position;
    sp24 = someStruct->unk38;
    someStruct->unk4 = 0;
    someStruct->unk2 = 0;
    someStruct->unk0 = -0x8000;
    someStruct->unk38 = 0;
    someStruct->x_position = 0.0f;
    someStruct->y_position = 0.0f;
    someStruct->z_position = 0.0f;
    func_8001D5E0(0.0f, 0.0f, -1.0f);
    func_80066CDC(dlist, arg1);
    someStruct->unk38 = sp24;
    someStruct->unk0 = sp2A;
    someStruct->unk2 = sp28;
    someStruct->unk4 = sp26;
    someStruct->x_position = sp20;
    someStruct->y_position = sp1C;
    someStruct->z_position = sp18;
}

f32 func_80066348(f32 arg0, f32 arg1, f32 arg2) {
    s32 phi_v1;
    f32 temp_f2, temp_f0, temp_f14;

    phi_v1 = D_80120CE4;

    if (D_80120D14 != 0) {
        phi_v1 += 4;
    }

    temp_f0 = arg2 - D_80120AC0[phi_v1].z_position;
    temp_f2 = arg0 - D_80120AC0[phi_v1].x_position;
    temp_f14 = arg1 - D_80120AC0[phi_v1].y_position;
    return sqrtf((temp_f0 * temp_f0) + ((temp_f2 * temp_f2) + (temp_f14 * temp_f14)));
}

void func_800663DC(s32 xPos, s32 yPos, s32 zPos, s32 arg3, s32 arg4, s32 arg5) {
    D_80120AC0[D_80120CE4].unk4 = (s16)(arg3 * 0xB6);
    D_80120AC0[D_80120CE4].x_position = (f32)xPos;
    D_80120AC0[D_80120CE4].y_position = (f32)yPos;
    D_80120AC0[D_80120CE4].z_position = (f32)zPos;
    D_80120AC0[D_80120CE4].unk2 = (s16)(arg4 * 0xB6);
    D_80120AC0[D_80120CE4].unk38 = (u16)0;
    D_80120AC0[D_80120CE4].unk24 = 0.0f;
    D_80120AC0[D_80120CE4].unk28 = 0.0f;
    D_80120AC0[D_80120CE4].unk2C = 0.0f;
    D_80120AC0[D_80120CE4].unk30 = 0.0f;
    D_80120AC0[D_80120CE4].unk1C = 160.0f;
    D_80120AC0[D_80120CE4].unk0 = (s16)(arg5 * 0xB6);
    D_80120AC0[D_80120CE4].unk3B = D_800DD2F8[D_80120CE4];
}

void func_80066488(s32 arg0, f32 xPos, f32 yPos, f32 zPos, s16 arg4, s16 arg5, s16 arg6) {
    arg0 += 4;
    D_80120AC0[arg0].unk38 = 0;
    D_80120AC0[arg0].x_position = xPos;
    D_80120AC0[arg0].y_position = yPos;
    D_80120AC0[arg0].z_position = zPos;
    D_80120AC0[arg0].unk0 = arg4;
    D_80120AC0[arg0].unk2 = arg5;
    D_80120AC0[arg0].unk4 = arg6;
    D_80120AC0[arg0].levelSegmentIndex = get_level_segment_index_from_position(xPos, yPos, zPos);
    D_80120D14 = 1;
}

s8 func_80066510(void) {
    return D_80120D14;
}

void func_80066520(void) {
    D_80120D14 = 0;
}

s32 func_8006652C(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 4)) {
        gNumberOfViewports = arg0;
    } else {
        gNumberOfViewports = 0;
    }
    switch (gNumberOfViewports) {
        case VIEWPORTS_COUNT_1_PLAYER:
            D_80120CE8 = 1;
            break;
        case VIEWPORTS_COUNT_2_PLAYERS:
            D_80120CE8 = 2;
            break;
        case VIEWPORTS_COUNT_3_PLAYERS:
            D_80120CE8 = 3;
            break;
        case VIEWPORTS_COUNT_4_PLAYERS:
            D_80120CE8 = 4;
            break;
    }
    if (D_80120CE4 >= D_80120CE8) {
        D_80120CE4 = 0;
    }
    return D_80120CE8;
}

void func_800665E8(s32 arg0) {
    if (arg0 >= 0 && arg0 < 4) {
        D_80120CE4 = arg0;
    } else {
        D_80120CE4 = 0;
    }
}

#ifdef NON_MATCHING

// Has regalloc/stack issues
void func_80066610(void) {
    s32 s1;
    s32 s2;
    s32 s3;
    s32 s4;
    s32 s5;
    s32 i;

    D_800DD134 = 1 - D_800DD134;
    for (i = 0; i < 4; i++) {
        if (gScreenViewports[i].flags & 4) {
            gScreenViewports[i].flags &= ~1;
        } else if (gScreenViewports[i].flags & 2) {
            gScreenViewports[i].flags |= 1;
        }
        gScreenViewports[i].flags &= ~6;
        if (gScreenViewports[i].flags & 1) {
            if (!(gScreenViewports[i].flags & 8)) {
                // Issue here
                s5 = (gScreenViewports[i].unk0 * 4) + (((gScreenViewports[i].unk8 - gScreenViewports[i].unk0) + 1) * 2);
            } else {
                s5 = gScreenViewports[i].unk10;
                s5 *= 4;
            }
            if (!(gScreenViewports[i].flags & 0x10)) {
                // Issue here
                s4 = (gScreenViewports[i].unk4 * 4) + (((gScreenViewports[i].unkC - gScreenViewports[i].unk4) + 1) * 2);
            } else {
                s4 = gScreenViewports[i].unk14;
                s4 *= 4;
            }
            if (!(gScreenViewports[i].flags & 0x20)) {
                s1 = gScreenViewports[i].unk8 - gScreenViewports[i].unk0;
                s1 += 1;
                s1 *= 2;
            } else {
                s1 = gScreenViewports[i].unk18;
                s1 *= 2;
            }
            if (!(gScreenViewports[i].flags & 0x40)) {
                s2 = gScreenViewports[i].unkC - gScreenViewports[i].unk4;
                s2 += 1;
                s2 *= 2;
            } else {
                s2 = gScreenViewports[i].unk1C;
                s2 *= 2;
            }
            s3 = i + (D_800DD134 * 5);
            s3 += 10;
            if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
                s2 = -s2;
            }
            D_800DD148[s3].vp.vtrans[0] = s5;
            D_800DD148[s3].vp.vtrans[1] = s4;
            D_800DD148[s3].vp.vscale[0] = s1;
            D_800DD148[s3].vp.vscale[1] = s2;
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/camera/func_80066610.s")
#endif

void func_80066818(s32 viewPortIndex, s32 arg1) {
    if (arg1 != 0) {
        gScreenViewports[viewPortIndex].flags |= 1;
    } else {
        gScreenViewports[viewPortIndex].flags |= 2;
    }
    gScreenViewports[viewPortIndex].flags &= ~4;
}

void func_80066894(s32 viewPortIndex, s32 arg1) {
    if (arg1 != 0) {
        gScreenViewports[viewPortIndex].flags &= ~1;
    } else {
        gScreenViewports[viewPortIndex].flags |= 4;
    }
    gScreenViewports[viewPortIndex].flags &= ~2;
}

s32 func_80066910(s32 viewPortIndex) {
    return gScreenViewports[viewPortIndex].flags & 0x1;
}

#ifdef NON_MATCHING

// Should be functionally equivalent.
void func_80066940(s32 viewPortIndex, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 widthAndHeight, width, height;
    s32 phi_a1;
    s32 phi_a2;
    s32 phi_a3;

    widthAndHeight = get_video_width_and_height_as_s32();
    width = widthAndHeight & 0xFFFF;
    // Placement issues with the height variable.
    height = (widthAndHeight >> 0x10) & 0xFFFF;
    phi_a2 = arg4;
    phi_a3 = arg3;
    phi_a1 = arg1;
    if (arg3 < arg1) {
        phi_a1 = arg3;
        phi_a3 = arg1;
    }
    if (arg4 < arg2) {
        arg2 = arg4;
        phi_a2 = arg2;
    }
    if ((phi_a1 >= width) || (phi_a3 < 0) || (arg2 >= height) || (phi_a2 < 0)) {
        gScreenViewports[viewPortIndex].upperLeftX = 0;
        gScreenViewports[viewPortIndex].upperLeftY = 0;
        gScreenViewports[viewPortIndex].lowerRightX = 0;
        gScreenViewports[viewPortIndex].lowerRightY = 0;
    } else {
        if (phi_a1 < 0) {
            gScreenViewports[viewPortIndex].upperLeftX = 0;
        } else {
            gScreenViewports[viewPortIndex].upperLeftX = phi_a1;
        }
        if (arg2 < 0) {
            gScreenViewports[viewPortIndex].upperLeftY = 0;
        } else {
            gScreenViewports[viewPortIndex].upperLeftY = arg2;
        }
        if (phi_a3 >= width) {
            gScreenViewports[viewPortIndex].lowerRightX = width - 1;
        } else {
            gScreenViewports[viewPortIndex].lowerRightX = phi_a3;
        }
        if (phi_a2 >= height) {
            gScreenViewports[viewPortIndex].lowerRightY = height - 1;
        } else {
            gScreenViewports[viewPortIndex].lowerRightY = phi_a2;
        }
    }
    gScreenViewports[viewPortIndex].unk4 = arg2;
    gScreenViewports[viewPortIndex].unk0 = phi_a1;
    gScreenViewports[viewPortIndex].unk8 = phi_a3;
    gScreenViewports[viewPortIndex].unkC = phi_a2;
}
#else
GLOBAL_ASM("asm/non_matchings/camera/func_80066940.s")
#endif

void func_80066AA8(s32 viewPortIndex, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg1 != 0x8000) {
        gScreenViewports[viewPortIndex].unk10 = arg1;
        gScreenViewports[viewPortIndex].flags |= 8;
    } else {
        gScreenViewports[viewPortIndex].flags &= ~8;
    }
    if (arg2 != 0x8000) {
        gScreenViewports[viewPortIndex].unk10 = arg2;
        gScreenViewports[viewPortIndex].flags |= 0x10;
    } else {
        gScreenViewports[viewPortIndex].flags &= ~0x10;
    }
    if (arg3 != 0x8000) {
        gScreenViewports[viewPortIndex].unk18 = arg3;
        gScreenViewports[viewPortIndex].flags |= 0x20;
    } else {
        gScreenViewports[viewPortIndex].flags &= ~0x20;
    }
    if (arg4 != 0x8000) {
        gScreenViewports[viewPortIndex].unk1C = arg4;
        gScreenViewports[viewPortIndex].flags |= 0x40;
        return;
    }
    gScreenViewports[viewPortIndex].flags &= ~0x40;
}

s32 func_80066BA8(s32 viewPortIndex, s32 *upperLeftX, s32 *upperLeftY, s32 *lowerRightX, s32 *lowerRightY) {
    //gDPFillRectangle values
    *upperLeftX = gScreenViewports[viewPortIndex].upperLeftX;
    *lowerRightX = gScreenViewports[viewPortIndex].lowerRightX;
    *upperLeftY = gScreenViewports[viewPortIndex].upperLeftY;
    *lowerRightY = gScreenViewports[viewPortIndex].lowerRightY;
    if ((*upperLeftX | *lowerRightX | *upperLeftY | *lowerRightY) == 0) {
        return 0;
    }
    return 1;
}

void func_80066C2C(s32 viewPortIndex, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4) {
    *arg1 = gScreenViewports[viewPortIndex].unk0;
    *arg2 = gScreenViewports[viewPortIndex].unk4;
    *arg3 = gScreenViewports[viewPortIndex].unk8;
    *arg4 = gScreenViewports[viewPortIndex].unkC;
}

// Unused?
void func_80066C80(s32 *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    u32 temp_v0 = get_video_width_and_height_as_s32();
    *arg0 = 0;
    *arg1 = 0;
    *arg2 = temp_v0 & 0xFFFF;
    *arg3 = temp_v0 >> 0x10;
}

#ifdef NON_MATCHING

// Still a work-in-progress but it doesn't seem to cause any problems,
// which is why it is labeled under NON_MATCHING

#define SCISSOR_INTERLACE G_SC_NON_INTERLACE

void func_80066CDC(Gfx **dlist, s32 arg1) {
    u32 sp58;
    u32 sp54;
    u32 sp4C;
    u32 temp_a2;
    u32 temp_a3;
    u32 temp_t0;
    u32 temp_t1;
    u32 widthAndHeight;
    u32 temp_v0_6;
    u32 phi_a1;
    u32 phi_t3;
    u32 phi_t5;
    u32 phi_t4;

    if (func_8000E184() && !gNumberOfViewports) {
        D_80120CE4 = 1;
    }
    widthAndHeight = get_video_width_and_height_as_s32();
    temp_t0 = widthAndHeight >> 16;
    temp_a3 = temp_t0 >> 1;
    if (gScreenViewports[D_80120CE4].flags & 1) {
        gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, 
            gScreenViewports[D_80120CE4].upperLeftX, 
            gScreenViewports[D_80120CE4].upperLeftY, 
            gScreenViewports[D_80120CE4].lowerRightX, 
            gScreenViewports[D_80120CE4].lowerRightY
        );
        func_80068158(dlist, 0, 0, 0, 0);
        if (arg1 != 0) {
            func_80067D3C(dlist, arg1);
        }
        return;
    }
    temp_t1 = widthAndHeight & 0xFFFF;
    if (gNumberOfViewports == VIEWPORTS_COUNT_3_PLAYERS) {
        gNumberOfViewports = VIEWPORTS_COUNT_4_PLAYERS;
    }
    temp_a2 = temp_t1 >> 1;
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
            gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, 0, 0, temp_t1, temp_t0);
            sp4C = temp_a2;
            break;
        case VIEWPORTS_COUNT_2_PLAYERS:
            if (D_80120CE4 == 0) {
                temp_v0_6 = temp_t0 >> 2;
                phi_t3 = temp_v0_6;
                if (osTvType == TV_TYPE_PAL) {
                    phi_t3 = temp_v0_6 - 0xC;
                }
                gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, 0, 0, temp_t1, (temp_a3 - (temp_t0 >> 7)));
            } else {
                gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, 0, (temp_a3 + (temp_t0 >> 7)), temp_t1, (temp_t0 - (temp_t0 >> 7)));
                phi_t3 = temp_a3 + (temp_t0 >> 2);
            }
            sp4C = temp_a2;
            break;
        case VIEWPORTS_COUNT_3_PLAYERS:
            if (D_80120CE4 == 0) {
                gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, 0, 0, temp_a2 - (temp_t1 >> 8), temp_t0);
                phi_a1 = temp_t1 >> 2;
            } else {
                gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, temp_a2 + (temp_t1 >> 8), 0, temp_t1 - (temp_t1 >> 8), temp_t0);
                phi_a1 = temp_a2 + (temp_t1 >> 2);
            }
            sp4C = phi_a1;
            phi_t3 = sp58;
            break;
        case VIEWPORTS_COUNT_4_PLAYERS:
            sp58 = sp58 >> 1;
            sp54 = temp_a2 >> 1;
            switch (D_80120CE4) {
                case 0:
                    gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, 0.0f, 0.0f, (temp_a2 - (temp_t1 >> 8)), (temp_a3 - (temp_t0 >> 7)));
                    phi_t5 = 0;
                    phi_t4 = 0;
                case 1:
                    gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, (temp_a2 + (temp_t1 >> 8)), 0, ((temp_a2 * 2) - (temp_t1 >> 8)), (temp_a3 - (temp_t0 >> 7)));
                    phi_t5 = 0;
                    phi_t4 = temp_a2;
                    break;
                case 2:
                    gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, 0, temp_a3 + (temp_t0 >> 7), temp_a2 - (temp_t1 >> 8), (temp_a3 * 2) - (temp_t0 >> 7));
                    phi_t5 = temp_a3;
                    phi_t4 = 0;
                    break;
                case 3:
                    gDPSetScissor((*dlist)++, SCISSOR_INTERLACE, temp_a2 + (temp_t1 >> 8), temp_a3 + (temp_t0 >> 7), (temp_a2 * 2) - (temp_t1 >> 8), (temp_a3 * 2) - (temp_t0 >> 7));
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
                if (D_80120CE4 < 2) {
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
    if (arg1 != 0) {
        func_80067D3C(dlist, arg1);
    }
}

#else
GLOBAL_ASM("asm/non_matchings/camera/func_80066CDC.s")
#endif

GLOBAL_ASM("asm/non_matchings/camera/func_80067A3C.s")
GLOBAL_ASM("asm/non_matchings/camera/func_80067D3C.s")

void func_80067F20(f32 arg0) {
    D_800DD2B8[1][1] = arg0;
}

void func_80067F2C(Gfx **dlist, s32 *arg1) {
    u32 widthAndHeight;
    s32 width, height;
    s32 i, j;

    widthAndHeight = get_video_width_and_height_as_s32();
    height = widthAndHeight >> 0x10;
    width = widthAndHeight & 0xFFFF;
    func_8006F870(D_800DD2B8, *arg1);
    D_80120D88[0] = *arg1;
    D_800DD148[D_80120CE4 + 5].vp.vscale[0] = width * 2;
    D_800DD148[D_80120CE4 + 5].vp.vscale[1] = width * 2;
    D_800DD148[D_80120CE4 + 5].vp.vtrans[0] = width * 2;
    D_800DD148[D_80120CE4 + 5].vp.vtrans[1] = height * 2;
    gSPViewport((*dlist)++, (u8 *)&D_800DD148[D_80120CE4 + 5] + 0x80000000);
    fast3d_cmd((*dlist)++, 0x1000040, (u32)(*arg1 + 0x80000000));
    *arg1 += 0x40;
    D_80120D1C = 0;
    D_80120D08 = 0;

    i = 0;
    while (i < 4) { // for loop doesn't match here.
        j = 0;
        while (j < 4) {
            D_80120F20[i][j] = D_800DD2B8[i][j];
            j++;
        }
        i++;
    }
}

void func_8006807C(Gfx **dlist, s32 *arg1) {
    func_8006FE74(&D_80121060, &D_800DD288);
    func_8006F768(&D_80121060, &D_80120EE0, &D_80120F20);
    func_8006FE74(D_80120D70[0], &D_800DD2A0);
    func_8006F768(D_80120D70[0], &D_80120F20, &D_80121060);
    func_8006F870(D_80121060, (s32 *)*arg1); // This doesn't look right. Need to check this!
    fast3d_cmd((*dlist)++, 0x1000040, (u32)(*arg1 + 0x80000000));
    *arg1 += 0x40;
    D_80120D1C = 0;
    D_80120D08 = 0;
}

void func_80068158(Gfx **dlist, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 tempArg1 = (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) ? -arg1 : arg1;
    if (D_800DD060 != 0) {
        arg2 = -arg2;
        tempArg1 = -arg1;
    }
    if (!(gScreenViewports[D_80120CE4].flags & 1)) {
        D_800DD148[D_80120CE4].vp.vtrans[0] = arg3 * 4;
        D_800DD148[D_80120CE4].vp.vtrans[1] = arg4 * 4;
        D_800DD148[D_80120CE4].vp.vscale[0] = tempArg1 * 4;
        D_800DD148[D_80120CE4].vp.vscale[1] = arg2 * 4;
        gSPViewport((*dlist)++, (u8 *)&D_800DD148[D_80120CE4] + 0x80000000);
    } else {
        gSPViewport((*dlist)++, (u8 *)&D_800DD148[D_80120CE4 + 10 + (D_800DD134 * 5)] + 0x80000000);
    }
}

void func_800682AC(Gfx **dlist) {
    u32 widthAndHeight, width, height;
    D_80120CE4 = 4;
    widthAndHeight = get_video_width_and_height_as_s32();
    height = widthAndHeight >> 0x10;
    width = widthAndHeight & 0xFFFF;
    if (!(gScreenViewports[D_80120CE4].flags & 1)) {
        gDPSetScissor((*dlist)++, G_SC_NON_INTERLACE, 0, 0, width - 1, height - 1);
        func_80068158(dlist, width >> 1, height >> 1, width >> 1, height >> 1);
    } else {
        func_80067A3C(dlist);
        func_80068158(dlist, 0, 0, 0, 0);
    }
    D_80120CE4 = 0;
}

void func_80068408(Gfx **dlist, s32 *arg1) {
    func_800705F8(D_80120D70[D_80120D1C], 0.0f, 0.0f, 0.0f);
    func_8006F768(D_80120D70[D_80120D1C], &D_80120F20, &D_80121060);
    func_8006F870(D_80121060, (s32 *)*arg1); // This doesn't look right. Need to check this!
    D_80120D88[D_80120D1C] = *arg1;

    fast3d_cmd((*dlist)++, ((((D_80120D08 << 6) & 0xFF) << 0x10) | 0x1000000) | 0x40, (u32)(*arg1 + 0x80000000));

    *arg1 += 0x40;
}

void func_80068508(s32 arg0) {
    D_80120D0C = arg0;
}

GLOBAL_ASM("asm/non_matchings/camera/func_80068514.s")
GLOBAL_ASM("asm/non_matchings/camera/func_80068BF4.s")
GLOBAL_ASM("asm/non_matchings/camera/func_80068FA8.s")
GLOBAL_ASM("asm/non_matchings/camera/func_80069484.s")
GLOBAL_ASM("asm/non_matchings/camera/func_80069790.s")
GLOBAL_ASM("asm/non_matchings/camera/func_80069A40.s")

unk80120AC0 *func_80069CFC(void) {
    return &D_80120AC0[D_80120CE4];
}

unk80120AC0 *func_80069D20(void) {
    if (D_80120D14 != 0) {
        return &D_80120AC0[D_80120CE4 + 4];
    }
    return &D_80120AC0[D_80120CE4];
}

unk80120AC0 *func_80069D7C(void) {
    if (D_80120D14 != 0) {
        return &D_80120AC0[4];
    }
    return &D_80120AC0[0];
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
        temp_f0 = arg0 - D_80120AC0[i].x_position;
        temp_f2 = arg1 - D_80120AC0[i].y_position;
        temp_f14 = arg2 - D_80120AC0[i].z_position;
        temp_f0_2 = sqrtf(((temp_f0 * temp_f0) + (temp_f2 * temp_f2)) + (temp_f14 * temp_f14));
        if (temp_f0_2 < arg3) {
            D_80120AC0[i].unk30 = ((arg3 - temp_f0_2) * arg4) / arg3;
        }
    }
}

void func_80069F28(f32 arg0) {
    s32 i;
    for (i = 0; i <= gNumberOfViewports; i++) {
        D_80120AC0[i].unk30 = arg0;
    }
}

#ifdef NON_MATCHING
// Unused. Prints/Displays a 4x4 fixed-point RSP matrix.
void func_80069F64(s16 *mtx) {
    s32 i, j;
    s32 val;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            val = mtx[i * 4 + j];
            rmonPrintf("%x.", val);
            val = mtx[((i + 4) * 4 + j)]; // Issue here.
            rmonPrintf("%x  ", (u16)val);
        }
        rmonPrintf("\n");
    }
    rmonPrintf("\n");
}
#else
GLOBAL_ASM("asm/non_matchings/camera/func_80069F64.s")
#endif

// Unused. Prints/Displays a 4x4 floating-point matrix.
void func_8006A03C(f32 *mtx) {
    s32 i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            rmonPrintf("%f  ", mtx[i * 4 + j]);
        }
        rmonPrintf("\n");
    }
    rmonPrintf("\n");
}

OSMesgQueue *func_8006A100(void) {
    return &D_801210E0;
}

s32 func_8006A10C(void) {
    s32 *temp1;
    u8 bitpattern;
    s32 *temp2;

    osCreateMesgQueue(&D_801210E0, &D_801210F8, 1);
    osSetEventMesg(OS_EVENT_SI, &D_801210E0, D_801210FC);
    osContInit(&D_801210E0, &bitpattern, &status);
    osContStartReadData(&D_801210E0);
    func_8006A434();

    D_800DD300 = 0;

    if ((bitpattern & CONT_ABSOLUTE) && (!(status.errno & CONT_NO_RESPONSE_ERROR))) {
        return 0;
    }

    if (!bitpattern) {}

    D_800DD300 = 1;

    return -1;
}

GLOBAL_ASM("asm/non_matchings/camera/func_8006A1C4.s")

void func_8006A434(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        D_80121150[i] = i;
    }
}

void func_8006A458(s8 *activePlayers) {
    s32 i;
    s32 temp = 0;
    for (i = 0; i < 4; i++) {
        if (activePlayers[i]) {
            D_80121150[temp++] = i;
        }
    }
    for (i = 0; i < 4; i++) {
        if (!activePlayers[i]) {
            D_80121150[temp++] = i;
        }
    }
}

u8 func_8006A4F8(s32 arg0) {
    return D_80121150[arg0];
}

void func_8006A50C(void) {
    u8 temp = D_80121150[0];
    D_80121150[0] = D_80121150[1];
    D_80121150[1] = temp;
}

u16 get_buttons_held_from_player(s32 arg0) {
    return D_80121110[D_80121150[arg0]].unk0;
}

u16 get_buttons_pressed_from_player(s32 arg0) {
    return D_80121140[D_80121150[arg0]];
}

u16 func_8006A578(s32 arg0) {
    return D_80121148[D_80121150[arg0]];
}

s32 func_8006A59C(s32 arg0) {
    func_8006A624(D_80121110[D_80121150[arg0]].unk2);
}

s32 func_8006A5E0(s32 arg0) {
    func_8006A624(D_80121110[D_80121150[arg0]].unk3);
}

s32 func_8006A624(s8 arg0) {
    if (arg0 < 8 && arg0 >= -7) {
        return 0;
    }
    if (arg0 > 0) {
        arg0 -= 8;
        if (arg0 >= 0x47) {
            arg0 = 0x46;
        }
    } else {
        arg0 += 8;
        if (arg0 < -0x46) {
            arg0 = -0x46;
        }
    }
    return arg0;
}

// Used when anti-cheat/anti-tamper has failed in func_8006A6B0()
void disable_button_mask(void) {
    gButtonMask = 0;
}
