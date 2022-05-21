/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80042D20 */

#include "racer.h"
#include "memory.h"
#include "menu.h"
#include "video.h"

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "asset_enums.h"
#include "save_data.h"
#include "unknown_008C40.h"
#include "objects.h"
#include "audio.h"
#include "object_functions.h"
#include "game.h"
#include "printf.h"
#include "math_util.h"
#include "unknown_0255E0.h"
#include "weather.h"

#define MAX_NUMBER_OF_GHOST_NODES 360

/**
 * This file features extensive use of CLAMP and WRAP.
 * CLAMP will keep the value within the two ranges.
 * WRAP will "overflow" the value. Used to keep angles within s16 bounds.
 */

/************ .data ************/

s32 gObjLoopGoldenBalloonLength = 0x310;
s16 D_800DCB54 = 0;
s32 D_800DCB58 = 0; // Currently unknown, might be a different type.
s32 D_800DCB5C = 0; // Currently unknown, might be a different type.

// Not sure if D_800DCB58 & D_800DCB5C are actually a part of this array.
f32 D_800DCB60[14] = {
    -10.0f, 5.0f, 0.0f, 0.0f,
    10.0f, 5.0f, 0.0f, 0.0f,
    -10.0f, 10.0f, 0.0f, 0.0f,
    10.0f, 10.0f,
};

s32 D_800DCB98 = 0; // Currently unknown, might be a different type.
// Table used for quantifying speed reduction while the car drives over it, like how grass will slow you down more than the road.
// An antipiracy trigger can set the first index to 0.5f, which makes that surface type impossible to drive on.
f32 gSurfaceTractionTable[19] = {
    0.004f, 0.007f, 0.01f, 0.004f,
    0.01f, 0.01f, 0.01f, 0.01f,
    0.01f, 0.01f, 0.004f, 0.004f,
    0.004f, 0.004f, 0.004f, 0.004f,
    0.004f, 0.004f, 0.004f,
};
// Can only assume this is surface related too. Not incline thresholds though.
f32 D_800DCBE8[19] = {
    0.8f, 0.85f, 0.85f, 0.5f,
    0.5f, 0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f, 0.8f,
    0.8f, 0.84f, 0.8f, 0.8f,
    0.8f, 0.8f, 0.8f,
};

// Unused? Not sure if this is actually an array or just some random data.
s32 D_800DCC34[19] = {
    0, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

s32 D_800DCC80[13] = {
    0, 26, 27, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

// Unused?
s16 D_800DCCB4[12] = {
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

u16 D_800DCCCC[20] = {
    0x010C, 0x010B, 0x0009, 0x010C,
    0x010C, 0x010C, 0x010C, 0x010C,
    0x010C, 0x010C, 0x010C, 0x0005,
    0x010C, 0x010C, 0x010C, 0x010C,
    0x010C, 0x010C, 0x010C, 0x0000,
};

s32 D_800DCCF4[19] = {
    1, 4, 16, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0x100, 1, 1, 1, 1, 1,
};

s32 D_800DCD40[20] = {
    0, 4, 16, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0x100, 0, 0, 0, 0,
    0, 0,
};

s8 D_800DCD90[15] = {
    1, 1, 2, 2, 4, 3, 0, 6,
    4, 3, 2, 2, 5, 5, 5,
};

// Unused?
s8 D_800DCDA0[8] = {
    0, 0, 0, 1, 1, 2, 2, 2,
};

s8 D_800DCDA8[8] = {
    1, 1, 1, 2, 3, 2, 3, 2,
};

// Unused?
s16 D_800DCDB0[16] = {
    0x02FE, 0x03FE, 0x02FC, 0x02FB,
    0x02FB, 0x02FE, 0x02FD, 0x02FE,
    0x03FD, 0x05FC, 0x04FE, 0x02FE,
    0x02FA, 0x02FE, 0x08F8, 0x03FD,
};

// Checksum count for obj_loop_goldenballoon
s32 gObjLoopGoldenBalloonChecksum = 42391;

s16 D_800DCDD4[4] = {
    0, 0, 0x32, -1
    // There might be one or two extra zeroes here.
};

/*******************************/

/************ .rodata ************/

const char D_800E6280[] = "%.1f,%.1f,%.1f\n";
const char D_800E6290[] = "Chk ovflow!!\n";
const char D_800E62A0[] = "Back\n";

/*********************************/

/************ .bss ************/

f32 D_8011D4F0[2];
s32 D_8011D4F8[3];
s32 D_8011D504;
ObjectCamera *gCameraObject;
s32 D_8011D50C;
ObjectTransform D_8011D510;
s32 gCurrentCarInput; // Related to input of the car.
s32 gActivePlayerButtonPress;
s32 D_8011D530;
s32 gCurrentStickX;
s32 gCurrentStickY;
s32 D_8011D53C;
s32 gRaceStartTimer;
f32 D_8011D544;
f32 D_8011D548;
f32 D_8011D54C;
s16 D_8011D550;
s8 D_8011D552;
s8 D_8011D553;
s32 gCurrentCarSteerVel; // Related to rotational velocity of the car.
s32 D_8011D558;
s32 D_8011D55C;
s16 D_8011D560;
s16 D_8011D562;
s32 D_8011D564;
s32 D_8011D568;
s32 D_8011D56C;
f32 D_8011D570;
f32 D_8011D574;
f32 D_8011D578;
f32 D_8011D57C;
s8 D_8011D580;
s8 D_8011D581;
s8 D_8011D582;
s8 D_8011D583;
s8 D_8011D584;
s8 gStartBoostTime;
s16 D_8011D586;
s8 D_8011D588[4];
s8 D_8011D58C[4];
GhostHeader *gGhostData[3];
s8 D_8011D59C;
s8 D_8011D59D;
s16 D_8011D59E;
s16 D_8011D5A0[2];
s16 gTTGhostNodeCount; // Gets assigned, but never used?
s16 D_8011D5A8[2];
s16 D_8011D5AC;
s16 D_8011D5AE;
s32 D_8011D5B0;
s32 D_8011D5B4;
s16 D_8011D5B8;

/******************************/

GLOBAL_ASM("asm/non_matchings/racer/func_80042D20.s")

void func_80043ECC(s32 arg0, Object_64_Unknown5 *arg1, s32 updateRate) {
    TempStruct5 *temp_v0;
    s8 *test;
    s8 phi_a0;
    s32 i;
    static s8 D_8011D5BA;
    static s8 D_8011D5BB;
    static s8 D_8011D5BC;

    if (!arg0) {
        D_8011D5BA = 0;
        D_8011D5BB = 0;
        D_8011D5BC = 0;
        return;
    }
    temp_v0 = (TempStruct5 *)func_8006C18C();
    if (arg1->unk1D3) {
        if (!D_8011D5BB) {
            temp_v0->unk8[3][0] += temp_v0->unk8[3][2];
            temp_v0->unk8[3][1] += temp_v0->unk8[3][3];
            D_8011D5BB = 1;
        }
        if (!(gCurrentCarInput & A_BUTTON)) {
            D_8011D5BA += updateRate;
        }
    } else {
        D_8011D5BB = 0;
        if (D_8011D5BA > 20) {
            temp_v0->unk8[0][0] += temp_v0->unk8[0][2];
            temp_v0->unk8[0][1] += temp_v0->unk8[0][3];
        }
        D_8011D5BA = 0;
    }
    if (arg1->unk173) {
        if (D_8011D5BC < arg1->unk174) {
            temp_v0->unk8[1][0] += temp_v0->unk8[1][2];
            temp_v0->unk8[1][1] += temp_v0->unk8[1][3];
        }
        D_8011D5BC = arg1->unk174;
    } else {
        D_8011D5BC = 0;
    }
    test = get_misc_asset(12);
    if ((D_8011D530 & 0x2000) && arg1->unk173) {
        if (arg1->unk174 < 3) {
            phi_a0 = test[arg1->unk172 * 3 + arg1->unk174];
        } else {
            phi_a0 = arg1->unk172;
        }
        if (D_800DCD90[phi_a0] == 1) {
            temp_v0->unk8[2][0] += temp_v0->unk8[2][2];
            temp_v0->unk8[2][1] += temp_v0->unk8[2][3];
        }
    }
    for (i = 0; i < 2; i++) {
        if (temp_v0->unk8[1][i] > 100 || temp_v0->unk8[1][i] < 0) {
            temp_v0->unk8[1][i] = 100;
        }
        if (temp_v0->unk8[0][i]  > 100 || temp_v0->unk8[0][i] < 0) {
            temp_v0->unk8[0][i]  = 100;
        }
        if (temp_v0->unk8[3][i] > 100 || temp_v0->unk8[3][i] < 0) {
            temp_v0->unk8[3][i] = 100;
        }
        if (temp_v0->unk8[2][i] > 100 || temp_v0->unk8[2][i] < 0) {
            temp_v0->unk8[2][i] = 100;
        }
    }
}

// Might be the main loop for the AI racers.
void func_80044170(Object *obj, Object_Racer *racer, s32 updateRate) {
    s32 raceType;

    raceType = get_current_level_race_type();

    switch (raceType) {
        case RACETYPE_CHALLENGE_BATTLE:
        case RACETYPE_CHALLENGE_BANANAS:
            func_8004447C(obj, racer, updateRate);
            break;
        case RACETYPE_CHALLENGE_EGGS:
            func_800452A0(obj, racer, updateRate);
            break;
        default:
            func_80045C48(obj, racer, updateRate);
            break;
    }

    if (racer->unk214 == 0 && racer->velocity < -0.5) {
        racer->unk215 -= updateRate;
        if (racer->unk215 < 0) {
            racer->unk215 = 0;
        }
    }

    if (racer->velocity > -1.0 && racer->unk214 == 0 && !gRaceStartTimer && D_8011D544 == 0.0f && racer->unk1E2 && racer->unk215 == 0) {
        racer->unk213 += updateRate;

        if (racer->unk213 > 60) {
            racer->unk213 = 0;
            racer->unk214 = 60;
            racer->unk215 = 120;

            if (!(raceType & RACETYPE_CHALLENGE)) {
                racer->unk1CA = (racer->unk1CA + 1) & 3;
            } else if (raceType == RACETYPE_CHALLENGE_BATTLE || raceType == RACETYPE_CHALLENGE_BANANAS) {
                if (racer->unk1CE != 0xFF) {
                    racer->unk154 = func_8001D214(racer->unk1CE);
                }
            }
        }
    } else {
        racer->unk214 -= updateRate;
        racer->unk213 = 0;

        if (racer->unk214 < 0) {
            racer->unk214 = 0;
        }
    }

    // Kick it into reverse.
    if (racer->unk214 != 0) {
        gCurrentStickX *= -1;
        gCurrentCarInput &= ~A_BUTTON;
        gCurrentStickY = -50;
        gCurrentCarInput |= B_BUTTON;
    }

    // Cap stick inputs.
    CLAMP(gCurrentStickX, -75, 75);
    CLAMP(gCurrentStickY, -75, 75);
}

s32 func_80044450(s32 cap) {
    return get_random_number_from_range(0, 99) < cap;
}

GLOBAL_ASM("asm/non_matchings/racer/func_8004447C.s")

// Still don't know what this really is.
struct TempStruct2 {
    Object *unk0[4];
    u8 pad10[0x1BF];
    s32 unk1CF;
};

void func_80045128(struct TempStruct2 *header) {
    struct Object_Racer *obj;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = (struct Object_Racer *) header->unk0[i]->unk64;
        D_8011D588[i] = obj->unk193;
        if (obj->unk1CF != 0) {
            D_8011D588[i] |= 0x40;
        }
        if (obj->held_obj != 0) {
            D_8011D588[i] |= 0x80;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_800452A0.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80045C48.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80046524.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80048C7C.s")

/**
 * Handles the camera movement when the player is driving a hovercraft.
 * Since the hovercraft has very floaty controls, the camera movement is much slower to compensate.
 */
void update_camera_hovercraft(f32 updateRate, Object *obj, Object_Racer *racer) {
    f32 yVel;
    s32 numViewports;
    u8 tempZoom;
    f32 tempVel_3;
    s32 pad;
    f32 phi_f14 = 165.0f;
    f32 phi_f18 = 65.0f;
    f32 xVel;
    f32 zVel;
    f32 yOffset;
    f32 sp34;
    f32 extraOffset;
    f32 brakeVar;
    f32 baseSpeed;
    s32 sp24 = 0x400;
    s32 delta;
    s32 angle;
    s32 segmentIndex;
    s32 tempAngle;
    f32 anotherVel;

    delta = (s32) updateRate;
    // Place the camera a bit closer with 2+ players to help visibility.
    numViewports = get_viewport_count();
    if (numViewports == 1) {
        phi_f14 = 200.0f;
        phi_f18 = 51.0f;
        sp24 = 0x280;
    } else if (numViewports > 1) {
        phi_f14 = 130.0f;
        phi_f18 = 50.0f;
    }
    brakeVar = racer->brake;
    tempZoom = gCameraObject->zoom;
    baseSpeed = racer->unk8;
    switch (gCameraObject->zoom) {
    case 1:
        phi_f14 += 35.0f;
        break;
    case 2:
        phi_f14 -= 35.0f;
        phi_f18 -= 10.0f;
        break;
    case 3:
        phi_f14 -= 53.0f;
        phi_f18 -= 5.0f;
        baseSpeed *= 0.250;
        brakeVar = 0.0f;
        break;
    }
    if (racer->unk1E4 == 0) {
        angle = (obj->segment.trans.x_rotation);
        if (angle > 0) {
            angle -= 0x61C;
            if (angle < 0) {
                angle = 0;
            }
            angle >>= 1;
        } else {
            angle += 0x61C;
            if (angle > tempZoom * 0) {
                angle = 0;
            }
        }
        angle = sp24 - angle;
        tempAngle = angle - (u16) gCameraObject->trans.x_rotation;
        WRAP(tempAngle, -0x8000, 0x8000);
        gCameraObject->trans.x_rotation += (tempAngle * delta) >> 4;
    }
    get_viewport_count();
    if (racer->velocity < 0.0) {
        yVel = -(racer->velocity * brakeVar) * 6.0f;
        if (racer->velocity);
        if (yVel > 65.0) {
            yVel = 65.0f;
        }
        phi_f14 -= yVel;
    }
    phi_f14 += baseSpeed * 30.0f;
    if (gRaceStartTimer == 0) {
        if (normalise_time(36) < racer->boostTimer) {
            phi_f14 = -30.0f;
        } else if (racer->boostTimer > 0) {
            phi_f14 = 180.0f;
        }
    }
    if (gRaceStartTimer > 80) {
        gCameraObject->unk1C = phi_f14;
        gCameraObject->unk20 = phi_f18;
    }
    gCameraObject->unk1C += (phi_f14 - gCameraObject->unk1C) * 0.125;
    gCameraObject->unk20 += (phi_f18 - gCameraObject->unk20) * 0.125;
    sp34 = cosine_s(gCameraObject->trans.x_rotation - sp24);
    phi_f18 = sine_s(gCameraObject->trans.x_rotation - sp24);
    phi_f18 = (gCameraObject->unk1C * sp34) + (gCameraObject->unk20 * phi_f18);
    xVel = cosine_s(-racer->unk196 + 0x8000) * gCameraObject->unk1C;
    zVel = sine_s(-racer->unk196 + 0x8000) * gCameraObject->unk1C;
    yVel = (1.0 - (D_8011D586 / 10240.0f));
    xVel -= racer->ox1 * 10.0f * yVel;
    zVel -= racer->oz1 * 10.0f * yVel;
    yVel = racer->lateral_velocity * 2;
    racer->unkC8 -= (racer->unkC8 - yVel) * 0.25;
    yVel = cosine_s(racer->unk196 + 0x4000) * racer->unkC8;
    gCameraObject->trans.x_position = obj->segment.trans.x_position + xVel + yVel;
    yVel = gCameraObject->trans.y_position - (obj->segment.trans.y_position + phi_f18);
    if (yVel > 0.0f) {
        yVel *= 0.5;
    } else {
        if (D_8011D53C == 1) {
            yVel *= 0.5;
        } else {
            yVel *= 0.25;
        }
        if (racer->boostTimer != 0) {
            yVel *= 2.0;
        }
    }
    gCameraObject->trans.y_position -= yVel;
    gCameraObject->trans.z_rotation = 0;
    if (gRaceStartTimer) {
        gCameraObject->trans.y_position = obj->segment.trans.y_position + phi_f18;
    }

    // Unused function call that wasn't fully optimised out.
    sine_s(racer->unk196 + 0x4000);
    gCameraObject->trans.z_position = obj->segment.trans.z_position + zVel;
    gCameraObject->trans.y_rotation = racer->unk196;
    segmentIndex = get_level_segment_index_from_position(gCameraObject->trans.x_position, gCameraObject->trans.y_position, gCameraObject->trans.z_position);
    if (segmentIndex != -1) {
        gCameraObject->unk34 = segmentIndex;
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_800494E0.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80049794.s")

// Something Plane related.
void func_8004C0A0(s32 arg0, Object *planeObj, Object_Racer *planeObj64) {
    s32 temp_v1;
    s32 phi_v0;

    if (planeObj64->unk1D7 != 10) {
        //!@bug Typo. Should've been `== 0`, not `= 0`.
        if ((planeObj64->unk1F2 = 0)) {
            return; // This never gets called because of the typo.
        }
        phi_v0 = planeObj64->unk1E1;
        phi_v0 = 40 - (phi_v0 >> 1);
        if (phi_v0 < 0) {
            phi_v0 = 0;
        }
        if (phi_v0 > 73) {
            phi_v0 = 73;
        }
        temp_v1 = phi_v0 - planeObj->segment.unk18;
        phi_v0 = 0;
        if (temp_v1 > 0) {
            phi_v0 = arg0 * 3;
            if (temp_v1 < phi_v0) {
                phi_v0 = temp_v1;
            }
        }
        if (temp_v1 < 0) {
            phi_v0 = arg0 * -3;
            if (phi_v0 < temp_v1) {
                phi_v0 = temp_v1;
            }
        }
        planeObj->segment.unk18 += phi_v0;
    }
}

void func_8004C140(Object *obj, Object_Racer *racer) {
    s8 bananas;
    s8 temp;
    if (racer->playerIndex == PLAYER_COMPUTER) {
        bananas = 0;
    } else {
        bananas = racer->bananas;
    }
    temp = racer->unk187;
    if (temp == 0 || racer->unk18E > 0) {
        racer->unk187 = 0;
        return;
    }
    if (temp != 4) {
        func_800576E0(obj, racer, 2);
    }
    racer->unk18C = 360;
    if (racer->unk1C9 == 8) {
        racer->unk1C9 = 0;
    }
    if (racer->unk1D6 < 5) {
        func_800570B8(obj, 450, 8, 129);
        switch (racer->unk187) {
            case 1:
            case 2:
                if (bananas != 0) {
                    racer->spinout_timer = 40;
                } else {
                    racer->spinout_timer = 60;
                }
                break;
            case 3:
                if (bananas != 0) {
                    racer->spinout_timer = 40;
                } else {
                    racer->spinout_timer = 60;
                }
                break;
            case 6:
                racer->unk204 = 120;
                obj->segment.x_velocity *= 0.7;
                obj->segment.z_velocity *= 0.7;
                break;
        }
        racer->unk187 = 0;
    }
}


#ifdef NON_EQUIVALENT
void update_camera_plane(f32 updateRate, Object* obj, Object_Racer* racer) {
    s32 segmentIndex;
    f32 baseSpeed;
    f32 tempVel;
    f32 yOffset;
    f32 yVel;
    s32 angle;
    f32 temp_f16;
    f32 baseFloat1 = 120.0f;
    s32 angleVel;
    f32 xOffset;
    f32 zOffset;
    f32 baseFloat2 = 45.0f;
    f32 phi_f14;
    f32 brakeVar = 0.0f;
    s32 numViewports;
    f32 baseFloat3;
    s32 delta;

    delta = (s32) updateRate;
    temp_f16 = D_8011D4F0[0];
    temp_f16 = 200.0f - (obj->segment.trans.y_position + (-temp_f16));
    if (temp_f16 < 0.0f) {
        temp_f16 = 0.0f;
    }
    if (temp_f16 > 200.0f) {
        temp_f16 = 200.0f;
    }
    numViewports = get_viewport_count();
    if (numViewports == 1) {
        baseFloat2 = 180.0f;
        baseFloat1 = 50.0f;
    } else if (numViewports > 1) {
        baseFloat2 = 110.0f;
        baseFloat1 = 42.0f;
    }
    if (((!(gCurrentCarInput & 0x10)) || racer->unk1E2 < 3) && !racer->unk1F5) {
        angle = (-racer->unk1A0 - (racer->unk196 & 0xFFFF)) + 0x8000;
        if (angle > 0x8000) {
            angle -= 0xFFFF;
        }
        angle = angle;
        if (angle < -0x8000) {
            angle += 0xFFFF;
        }
        if (racer->camera_zoom < 0.4) {
            racer->camera_zoom += 0.005;
        } else {
            racer->camera_zoom = 0.4f;
        }
        angleVel = angle * racer->camera_zoom;
        if (angleVel > 0x200) {
            angleVel = 0x200;
        }
        if (angleVel < -0x200) {
            angleVel = -0x200;
        }
        angleVel *= delta;
        if (angle < 0 && angleVel < angle) {
            angleVel = angle;
        }
        if (angle > 0 && angle < angleVel) {
            angleVel = angle;
        }
        racer->unk196 += angleVel;
    } else {
        racer->camera_zoom = 0.0f;
    }
    if (D_8011D586) {
        racer->unk196 = 0x8000 - racer->unk1A0;
    }
    if (racer->unk1E0 == 2 || racer->unk1E0 == -2) {
        angle = 0;
    } else {
        angle = obj->segment.trans.x_rotation;
        if (angle > 0x3000) {
            angle = 0x3000;
        }
        if (angle < -0x3000) {
            angle = -0x3000;
        }
    }
    angle = -(angle - ((s32) (temp_f16 * 10.0f)));
    angle = angle - ((u16) gCameraObject->trans.x_rotation);
    if (angle > 0x8000) {
        angle -= 0xFFFF;
    }
    if (angle < -0x8000) {
        angle += 0xFFFF;
    }
    gCameraObject->trans.x_rotation += ((angle * delta) >> 4);
    brakeVar = racer->brake;
    baseSpeed = racer->unk8;
    switch (gCameraObject->zoom) {
    case 1:
        baseFloat2 += 35.0f;
        break;
    case 2:
        baseFloat1 -= 10.0f;
        baseFloat2 -= 35.0f;
        break;
    case 3:
        baseFloat2 -= 53.0f;
        baseFloat1 -= 5.0f;
        baseSpeed *= 0.25;
        brakeVar = 0.0f;
        break;
    }
    if (numViewports < 2) {
        phi_f14 = baseSpeed * 60.0f;
        phi_f14 = baseFloat2 + phi_f14;
    } else {
        phi_f14 = baseSpeed * 30.0f;
        phi_f14 = baseFloat2 + phi_f14;
    }
    if (racer->velocity < 0.0 && !racer->unk1E2) {
        tempVel = -(racer->velocity * brakeVar);
        tempVel = tempVel * 6.0f;
        if (65.0 < tempVel) {
            tempVel = 65.0f;
        }
        if (yOffset);
        phi_f14 -= tempVel;
    }
    if (!gRaceStartTimer) {
        if (normalise_time(36) < racer->boostTimer) {
            phi_f14 = -30.0f;
        } else if (racer->boostTimer > 0) {
            phi_f14 = 180.0f;
        }
    }
    if (gRaceStartTimer > 80) {
        gCameraObject->unk1C = phi_f14;
        gCameraObject->unk20 = baseFloat1;
    }
    gCameraObject->unk1C += (phi_f14 - gCameraObject->unk1C) * 0.125;
    gCameraObject->unk20 += (baseFloat1 - gCameraObject->unk20) * 0.125;
    phi_f14 = cosine_s(gCameraObject->trans.x_rotation - 0x400);
    xOffset = sine_s(gCameraObject->trans.x_rotation - 0x400);
    baseFloat3 = phi_f14;
    baseFloat2 = (gCameraObject->unk1C * baseFloat3) - (gCameraObject->unk20 * xOffset);
    baseFloat1 = ((gCameraObject->unk1C) * (gCameraObject->unk1C));
    baseFloat1 += (gCameraObject->unk20 * baseFloat3);
    xOffset = cosine_s(0x8000 - racer->unk196) * baseFloat2;
    zOffset = sine_s(0x8000 - racer->unk196) * baseFloat2;
    yVel = cosine_s(racer->unk196 + 0x4000) * 3.0f;
    yVel = yVel * racer->lateral_velocity;
    gCameraObject->trans.x_position = (obj->segment.trans.x_position + xOffset) + yVel;
    temp_f16 = obj->segment.trans.y_position;
    yOffset = gCameraObject->trans.y_position - (temp_f16 + baseFloat1);
    if (racer->unk1E0 == 1 || racer->unk1E0 == -1) {
        racer->unk74 = 8.0;
    }
    if (racer->unk1E0 == 2 || racer->unk1E0 == -2) {
        racer->unk74 = 8.0;
    }
    if (racer->unk74 > 2.0) {
        racer->unk74 -= 0.2;
    } else {
        racer->unk74 = 2.0;
    }
    yVel = racer->unk74;
    yVel = (yOffset * updateRate) / yVel;
    if (yVel > 0.0f && yOffset < yVel) {
        yVel = yOffset;
    }
    if (yVel < 0.0f && yVel < yOffset) {
        yVel = yOffset;
    }
    gCameraObject->trans.y_position -= yVel;
    gCameraObject->trans.z_position = zOffset + obj->segment.trans.z_position + (-sine_s(racer->unk196 + 0x4000) * 3.0f * racer->lateral_velocity);
    gCameraObject->trans.y_rotation = racer->unk196;
    if (racer->unk1E0 || D_8011D586) {
        angle = -(u16) gCameraObject->trans.z_rotation;
        if (angle > 0x8000) {
            angle -= 0xFFFF;
        }
        if (angle < -0x8000) {
            angle += 0xFFFF;
        }
        gCameraObject->trans.z_rotation += angle >> 2;
    } else {
        angle = (u16) gCameraObject->trans.z_rotation;
        angle = angle + (-(racer->unk1A4 >> 4));
        if (angle > 0x8000) {
            angle -= 0xFFFF;
        }
        if (angle < -0x8000) {
            angle += 0xFFFF;
        }
        gCameraObject->trans.z_rotation += angle >> 3;
    }
    tempVel = gCameraObject->trans.x_position;
    segmentIndex = get_level_segment_index_from_position(tempVel, gCameraObject->trans.y_position, gCameraObject->trans.z_position);
    if (segmentIndex != -1) {
        gCameraObject->unk34 = segmentIndex;
    }
    racer->unk196 = gCameraObject->trans.y_rotation;
}
#else
GLOBAL_ASM("asm/non_matchings/racer/update_camera_plane.s")
#endif


GLOBAL_ASM("asm/non_matchings/racer/func_8004CC20.s")

/**
 * Handles the camera movement when the player is on a loop-the-loop.
 * This happens in Walrus Cove and Darkmoon Caverns.
 * The camera's rotation follows the players exactly, in order to stay levelled.
 */
void update_camera_loop(f32 updateRate, Object* obj, Object_Racer* racer) {
    s32 delta;
    UNUSED f32 pad;
    s32 segmentIndex;
    s32 angle;
    f32 zoom;
    f32 xVel;
    f32 yVel;
    f32 zVel;
    Matrix mtx;
    s32 angleDiff;

	delta = (s32) updateRate;
    zoom = 120.0f;
    if (gRaceStartTimer >= 0x3D) {
        zoom += ((f32) (gRaceStartTimer - 0x3C) * 4.0f);
    }
    racer->unk196 = 0x8000 - racer->unk1A0;
    if (get_viewport_count() == 1) {
        zoom = 160.0f;
    }
    // A little bit of indecisiveness.
    if (gCameraObject->zoom == ZOOM_FAR) {
        zoom += 35.0f;
    }
    if (gCameraObject->zoom == ZOOM_FAR) {
        zoom -= 35.0f;
    }
    gCameraObject->unk1C += (zoom - gCameraObject->unk1C) * 0.125;
    D_8011D510.y_rotation = -gCameraObject->trans.y_rotation + 0x8000;
    D_8011D510.x_rotation = -gCameraObject->trans.x_rotation;
    D_8011D510.z_rotation = 0;
    D_8011D510.x_position = 0.0f;
    D_8011D510.y_position = 0.0f;
    D_8011D510.z_position = 0.0f;
    D_8011D510.scale = 1.0f;
    func_8006FC30(mtx, &D_8011D510);
    guMtxXFMF(mtx, 0.0f, 0.0f, gCameraObject->unk1C, &xVel, &yVel, &zVel);
    gCameraObject->trans.x_position = obj->segment.trans.x_position + xVel;
    gCameraObject->trans.y_position = obj->segment.trans.y_position + yVel;
    gCameraObject->trans.z_position = obj->segment.trans.z_position + zVel;
    guMtxXFMF(mtx, 0.0f, cosine_s(0x800) * gCameraObject->unk1C, 0.0f, &xVel, &yVel, &zVel);
    gCameraObject->trans.x_position += xVel;
    gCameraObject->trans.y_position += yVel;
    gCameraObject->trans.z_position += zVel;
    angleDiff = (u16) (-obj->segment.trans.z_rotation);
    angle = angleDiff - ((u16) gCameraObject->trans.z_rotation);
    WRAP(angle, -0x8000, 0x8000);
    gCameraObject->trans.z_rotation += ((angle * delta) >> 4);
    angleDiff = -obj->segment.trans.x_rotation;
    angle = angleDiff - (u16) gCameraObject->trans.x_rotation;
    WRAP(angle, -0x8000, 0x8000);
    gCameraObject->trans.x_rotation += ((angle * delta) >> 4);
    gCameraObject->trans.y_rotation = racer->unk196;
    segmentIndex = get_level_segment_index_from_position(gCameraObject->trans.x_position, gCameraObject->trans.y_position, gCameraObject->trans.z_position);
    if (segmentIndex != -1) {
        gCameraObject->unk34 = segmentIndex;
    }
    racer->unk196 = gCameraObject->trans.y_rotation;
    gCameraObject->trans.x_position += gCameraObject->x_velocity;
    gCameraObject->trans.y_position += gCameraObject->y_velocity;
    gCameraObject->trans.z_position += gCameraObject->z_velocity;
}

void func_8004D95C(s32 arg0, s32 arg1, Object *obj, Object_Racer *racer) {
    s16 sp26;

    if (racer->unk118 != 0) {
        func_80006AC8(obj);
    }
    if (func_8002341C() && racer->unk1D6 == 10) {
        obj->unk4C->unk14 = 0;
    }
    sp26 = obj->segment.unk18;
    racer->unk1D6 = 10;
    func_80049794(arg0, arg1, obj, racer);
    racer->unk1D6 = racer->unk1D7;
    obj->segment.unk3B = 0;
    if (racer->unk1D6 == 10) {
        if (racer->unk154 != NULL) {
            racer->unk154->segment.trans.x_position = obj->segment.trans.x_position;
            racer->unk154->segment.trans.y_position = obj->segment.trans.y_position;
            racer->unk154->segment.trans.z_position = obj->segment.trans.z_position;
            racer->unk154->segment.unk2C.half.lower = obj->segment.unk2C.half.lower;
            racer->unk154->segment.trans.y_rotation = obj->segment.trans.y_rotation;
            racer->unk154->segment.trans.x_rotation = obj->segment.trans.x_rotation;
            racer->unk154->segment.trans.z_rotation = obj->segment.trans.z_rotation;
            obj->segment.unk3B = 0;
            obj->segment.unk18 = sp26 + arg0;
            func_80061C0C(obj);
        }
    }
}

/**
 * Initialise the basic properties of each racer object. If it's tied to a human player,
 * will also initialise a camera object.
 */
void obj_init_racer(Object *obj, LevelObjectEntry_CharacterFlag *racer) {
    Object_Racer *tempObj;
    ActivePlayers player;
    s32 i;

    D_8011D53C = 0;
    tempObj = (struct Object_Racer *) obj->unk64;
    obj->segment.trans.y_rotation = racer->unkC;
    obj->segment.trans.x_rotation = racer->unkA;
    obj->segment.trans.z_rotation = racer->unk8;
    player = racer->unkE;
    tempObj->unk194 = 0;
    tempObj->stretch_height = 1.0f;
    tempObj->stretch_height_cap = 1.0f;
    // Decide which player ID to assign to this object. Human players get a value from 0-3.
    // Computer players will be -1.
    if (player >= PLAYER_ONE && player <= PLAYER_FOUR) {
        if (func_8000E158()) {
            player = 1 - player;
        }
        tempObj->playerIndex = player;
    } else {
        tempObj->playerIndex = PLAYER_COMPUTER;
    }
    tempObj->unk1A0 = obj->segment.trans.y_rotation;
    tempObj->unk1A4 = obj->segment.trans.z_rotation;
    tempObj->unkC4 = 0.5f;
    if (1);
    tempObj->unk196 = tempObj->unk1A0;
    tempObj->unkD8[0] = obj->segment.trans.x_position;
    tempObj->unkD8[1] = obj->segment.trans.y_position + 30.0f;
    tempObj->unkD8[2] = obj->segment.trans.z_position;
    tempObj->unkE4[0] = obj->segment.trans.x_position;
    tempObj->unkE4[1] = obj->segment.trans.y_position + 30.0f;
    tempObj->unkE4[2] = obj->segment.trans.z_position;
    tempObj->unkF0[0] = obj->segment.trans.x_position;
    tempObj->unkF0[1] = obj->segment.trans.y_position + 30.0f;
    tempObj->unkF0[2] = obj->segment.trans.z_position;
    tempObj->unkFC[0] = obj->segment.trans.x_position;
    tempObj->unkFC[1] = obj->segment.trans.y_position + 30.0f;
    tempObj->unkFC[2] = obj->segment.trans.z_position;
    tempObj->prev_x_position = obj->segment.trans.x_position;
    tempObj->prev_y_position = obj->segment.trans.y_position;
    tempObj->prev_z_position = obj->segment.trans.z_position;
    obj->unk4C->x_position = obj->segment.trans.x_position;
    obj->unk4C->y_position = obj->segment.trans.y_position;
    obj->unk4C->z_position = obj->segment.trans.z_position;
    tempObj->unk1E2 = 3;
    tempObj->unk1AA = 1;
    tempObj->unk1AE = 1;
    tempObj->unk1E7 = tempObj->playerIndex * 5;
    tempObj->checkpoint_distance = 1.0f;
    tempObj->unk1FD = 0;
    tempObj->unk178 = 0;
    tempObj->unk17C = 0;
    tempObj->unk180 = 0;
    tempObj->unk218 = 0;
    tempObj->unk220 = 0;
    tempObj->unk21C = 0;
    if (tempObj->playerIndex != -1 && !D_8011D582) {
        func_800665E8(player);
        gCameraObject = func_80069CFC();
        gCameraObject->trans.z_rotation = 0;
        gCameraObject->trans.x_rotation = 0x400;
        gCameraObject->trans.y_rotation = tempObj->unk196;
        gCameraObject->mode = CAMERA_CAR;
        gCameraObject->unk3C = 0xFF;
        gCameraObject->unk3D = 0xFF;
        gCameraObject->unk3E = 0xFF;
        gCameraObject->unk3F = 0xFF;
        gCameraObject->unk18 = 0.0f;
        func_80057A40(obj, tempObj, 1.0f);
    }
    if (!D_8011D582) {
        D_8011D583 = 0;
        D_8011D586 = 0;
        D_8011D584 = 0;
    }
    obj->unk4C->unk14 = 5;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0xF;
    obj->unk4C->unk12 = 0x14;
    tempObj->unk1EE = 0;
    if (!D_8011D582) {
        tempObj->transparency = 0xFF;
    }
    D_8011D560 = 0;
    D_8011D544 = 300.0f;
    tempObj->unk1C9 = 6;
    tempObj->unk1C6 = 100;
    D_8011D580 = 0;

    // This needs to be on one line to match.
    for (i = 0; i < 4; i++) { D_8011D58C[i] = 0; }
    if (1); if (1); // Also critical to match.
    func_80043ECC(0, NULL, 0);
    D_8011D583 = i;
    gStartBoostTime = 0;
    tempObj->unk20A = 0;
}

GLOBAL_ASM("asm/non_matchings/racer/func_8004DE38.s")

void func_8004F77C(unk8004F77C *arg0) {
    s32 temp;

    arg0->flags &= ~0x80;
    if ((gCurrentCarInput & B_BUTTON)) {
        arg0->flags |= 0x80;
    }

    temp = arg0->flags & 0xF;
    if ((arg0->flags & 0xC0)) {
        temp++;
        if (temp >= 3) {
            temp = 2;
        }
    } else {
        temp--;
        if (temp < 0) {
            temp = 0;
        }
    }

    arg0->flags = (arg0->flags & 0xFFF0) | temp;
}

GLOBAL_ASM("asm/non_matchings/racer/func_8004F7F4.s")

void func_80050754(Object *obj, Object_Racer *racer, f32 divisor) {
    f32 diffX;
    f32 diffY;
    f32 diffZ;

    obj->segment.unk3B = 0;
    obj->segment.unk18 = 40;
    diffX = racer->unk148->segment.trans.x_position - obj->segment.trans.x_position;
    diffY = racer->unk148->segment.trans.y_position - obj->segment.trans.y_position;
    diffZ = racer->unk148->segment.trans.z_position - obj->segment.trans.z_position;
    func_80011570(obj, diffX, diffY, diffZ);
    obj->segment.trans.y_rotation = racer->unk148->segment.trans.y_rotation;
    obj->segment.trans.x_rotation = racer->unk148->segment.trans.x_rotation;
    obj->segment.trans.z_rotation = racer->unk148->segment.trans.z_rotation;
    racer->unk1A4 = obj->segment.trans.z_rotation;
    racer->unk1A0 = obj->segment.trans.y_rotation;
    obj->segment.x_velocity = diffX / divisor;
    obj->segment.y_velocity = diffY / divisor;
    obj->segment.z_velocity = diffZ / divisor;
    racer->velocity = 0.0f;
    racer->unk1F2 = 0;
    racer->lateral_velocity = 0.0f;
}

/**
 * Applies visual rotational offets to vehicles.
 * Examples include planes when on the ground, or when crashing, or hovercraft when braking.
 */
void apply_vehicle_rotation_offset(Object_Racer *obj, s32 max, s16 yRotation, s16 xRotation, s16 zRotation) {
    s32 diff;
    s32 tempAngle;

    if (!obj->unk1F1) {
        tempAngle = yRotation - (u16) obj->y_rotation_offset;
        obj->unk166 = xRotation;
        WRAP(tempAngle, -0x8000, 0x8000);
        if (tempAngle > 0) {
            diff = max * 0x600;
            if (diff < tempAngle) {
                tempAngle = diff;
            }
            obj->y_rotation_offset +=  tempAngle;
        } else if (tempAngle < 0) {
            diff = -(max * 0x600);
            if (tempAngle < diff) {
                tempAngle = diff;
            }
            obj->y_rotation_offset += tempAngle;
        }
        tempAngle = xRotation - (u16) obj->x_rotation_offset;
        WRAP(tempAngle, -0x8000, 0x8000);
        if (tempAngle > 0) {
            diff = max * 0x600;
            if (diff < tempAngle) {
                tempAngle = diff;
            }
            obj->x_rotation_offset += tempAngle;
        } else if (tempAngle < 0) {
            diff = -(max * 0x600);
            if (tempAngle < diff) {
                tempAngle = diff;
            }
            obj->x_rotation_offset += tempAngle;
        }
        tempAngle = zRotation - (u16) obj->z_rotation_offset;
        WRAP(tempAngle, -0x8000, 0x8000);
        if (tempAngle > 0) {
            diff = max * 0x600;
            if (diff < tempAngle) {
                tempAngle = diff;
            }
            obj->z_rotation_offset += tempAngle;
            return;
        }
        if (tempAngle < 0) {
            diff = -(max * 0x600);
            if (tempAngle < diff) {
                tempAngle = diff;
            }
            obj->z_rotation_offset += tempAngle;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_80050A28.s")

// Loops for as long as Taj exists. After swapping vehicle once, will remain true until you enter a door.
s32 func_80052188(void) {
    if (D_8011D582 == 2) {
        D_8011D582 = 1;
        return TRUE;
    }
    return FALSE;
}

// Called when Taj swaps the active vehicle, is set to 1, each time.
void func_800521B8(s32 arg0) {
    D_8011D582 = arg0;
}

void func_800521C4(Object *obj, Object_Racer *racer, UNUSED s32 arg2) {
    Object *tempObj;
    s8 foundObj;
    f32 distance;
    s32 tempVel;

    foundObj = 0;
    if (func_80023568()) {
        tempObj = get_object_struct(1);
        foundObj = func_80052388(obj, racer, tempObj, 160000.0f);
    }
    if (!foundObj) {
        tempObj = func_8001B7A8(racer, 1, &distance);
        if (tempObj && !gRaceStartTimer) {
            foundObj = func_80052388(obj, racer, tempObj, 160000.0f);
        }
    }
    if (!foundObj) {
        tempObj = func_8001B7A8(racer, -1, &distance);
        if (tempObj && !gRaceStartTimer) {
            foundObj = func_80052388(obj, racer, tempObj, 30000.0f);
        }
    }
    if (!foundObj) {
        if ((racer->unk1E7 & 0x1F) < 2) {
            tempVel = racer->velocity * 1280.0f;

            if (tempVel < 0) {
                tempVel = -tempVel;
            }

            if (tempVel > 0x2800) {
                tempVel = 0x2800;
            }

            tempVel = 0x2800 - tempVel;

            racer->unk16C = get_random_number_from_range(-tempVel, tempVel);
        }
    }
}

// Ran by the AI. Seems to be direction related of some sorts.
void func_8005234C(Object_Racer *racer) {
    racer->unk16C -= racer->unk16C >> 3;
    if (racer->unk16C >= -9 && racer->unk16C < 10) { // Deadzone?
        racer->unk16C = 0;
    }
}

s32 func_80052388(Object *obj1, Object_Racer *racer, Object *obj2, f32 distance) {
    s32 rotation;
    f32 diffX;
    f32 diffZ;
    s32 ret = FALSE;

    diffX = obj2->segment.trans.x_position - obj1->segment.trans.x_position;
    diffZ = obj2->segment.trans.z_position - obj1->segment.trans.z_position;
    if ((diffX * diffX) + (diffZ * diffZ) < distance) {
        rotation = (arctan2_f(diffX, diffZ) - (obj1->segment.trans.y_rotation & 0xFFFF)) + 0x8000;
        WRAP(rotation, -0x8000, 0x8000);
        CLAMP(rotation, -0x3000, 0x3000);
        racer->unk16C = rotation;
        if ((racer->unk1E7 & 0x3F) < 0x1F) {
            racer->unk16C = 0;
        }
        racer = (struct Object_Racer *) obj2->unk64;
        rotation = arctan2_f(diffX, diffZ) - (obj1->segment.trans.y_rotation & 0xFFFF);
        WRAP(rotation, -0x8000, 0x8000);
        CLAMP(rotation, -0x3000, 0x3000);
        racer->unk16C = rotation;
        if (ret) {}
        ret = TRUE;
        if ((racer->unk1E7 & 0x1F) < 0xA) {
            racer->unk16C = 0;
        }
    }
    return ret;
}

GLOBAL_ASM("asm/non_matchings/racer/func_8005250C.s")

void func_80052988(Object *obj, Object_Racer *racer, s32 action, s32 arg3, s32 duration, s32 arg5, s32 arg6, s32 arg7) {
    arg5 *= arg7;

    if ((D_8011D55C == -1) && (action >= 3)) {
        obj->segment.unk3B = 0;
        racer->unk1F2 = 0;
    } else if (obj->segment.unk3B == 0) {
        if (arg6 & 1) {
            if (obj->segment.unk18 >= 41) {
                obj->segment.unk18 -= arg7 * 4;
                if (obj->segment.unk18 < 41) {
                    obj->segment.unk3B = action;
                    obj->segment.unk18 = arg3;
                }
            } else {
                obj->segment.unk18 += arg7 * 4;
                if (obj->segment.unk18 >= 40) {
                    obj->segment.unk3B = action;
                    obj->segment.unk18 = arg3;
                }
            }
        } else {
            obj->segment.unk3B = action;
            obj->segment.unk18 = arg3;
            racer->unk1F3 &= ~0x80;
        }
    } else if (obj->segment.unk3B == action) {
        if (arg6 & 2) {
            if (racer->unk1F3 & 0x80) {
                obj->segment.unk18 -= arg5;
                if (obj->segment.unk18 <= 0) {
                    obj->segment.unk3B = 0;
                    racer->unk1F2 = 0;
                    obj->segment.unk18 = 40;
                    racer->unk1F3 = 0;
                }
            } else {
                obj->segment.unk18 += arg5;
                if (obj->segment.unk18 >= duration) {
                    obj->segment.unk18 = duration - 1;
                    if (!(arg6 & 4)) {
                        racer->unk1F3 |= 0x80;
                    }
                }
            }
        } else {
            obj->segment.unk18 += arg5;
            if (obj->segment.unk18 >= duration) {
                obj->segment.unk3B = 0;
                racer->unk1F2 = 0;
                obj->segment.unk18 = 40;
                racer->unk1F3 = 0;
            }
        }
    } else {
        obj->segment.unk18 = arg3;
        obj->segment.unk3B = action;
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_80052B64.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80052D7C.s")

/**
 * Handle the steering input of all cars.
 * It takes the speed of the car, creating a curve for the rotational velocity to scale with.
 */
void handle_car_steering(Object_Racer *racer) {
    s32 velScale;
    f32 vel = racer->velocity;

    // Stay positive :)
    if (vel < 0.0) {
        vel = -vel;
    }
    if (vel > 1.8) {
        vel = 1.8f;
    }
    vel -= 0.2;
    if (vel < 0.0) {
        vel = 0.0f;
    }
    if (racer->drift_direction != 0) {
        velScale = vel * 68.0f;
    } else {
        velScale = vel * 58.0f;
    }
    // Set the steering velocity based on the car's steering value, scaled with the temp forward velocity value.
    gCurrentCarSteerVel -= (racer->unk1E1 * velScale);
    // If the car is reversing, then flip the steering.
    if (racer->velocity > 0.0f) {
        gCurrentCarSteerVel = -gCurrentCarSteerVel;
    }
}

void func_800535C4(unk800535C4 *arg0, unk800535C4_2 *arg1) {
    Matrix mf;

    D_8011D510.y_rotation = -arg1->unk1A0;
    D_8011D510.x_rotation = -arg0->unk2;
    D_8011D510.z_rotation = -arg1->unk1A4;
    D_8011D510.x_position = 0;
    D_8011D510.y_position = 0;
    D_8011D510.z_position = 0;
    D_8011D510.scale = 1;
    func_8006FE74(&mf, &D_8011D510);

    guMtxXFMF(mf, 0.0f, -1.0f, 0.0f, &arg1->ox, &arg1->oy, &arg1->oz);
}

/**
 * Adjusts the throttle and brake application for all cars, based off the input.
 */
void handle_car_velocity_control(Object_Racer *racer) {
    if (racer->throttle > 0.0) {
        racer->throttle -= 0.1;
    }

    if (gCurrentCarInput & A_BUTTON) {
        racer->throttle = 1.0f;
    }

    if (gCurrentCarInput & B_BUTTON) {
        if (racer->brake < 1.0) {
            racer->brake += 0.2;
        }
    } else {
        //! @bug Will cause a negative brake value resulting in higher velocity
        if (racer->brake > 0.05) {
            racer->brake -= 0.1;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_80053750.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80053E9C.s")

void func_80054110(Object *obj, Object_Racer *racer, s32 updateRate, f32 arg3) {
    f32 tempVel;
    f32 xVel;
    f32 zVel;
    f32 yVel;
    f32 hVel;
    f32 tempX;
    f32 tempY;
    f32 tempZ;
    Matrix mtx;
    LevelHeader *header;
    s32 angle;
    s32 tempAngle;

    tempX = obj->segment.trans.x_position;
    tempY = obj->segment.trans.y_position;
    tempZ = obj->segment.trans.z_position;
    gCurrentCarSteerVel = 0;
    D_8011D558 = 0;
    func_800579B0(racer, 0, arg3);
    handle_car_velocity_control(racer);
    func_800575EC(obj, racer);
    func_80055EC0(obj, racer, updateRate);
    func_80053E9C(obj, racer, updateRate);
    if (racer->spinout_timer) {
        func_80052B64(obj, racer, updateRate, arg3); // Sbinalla
    } else if (racer->unk1E2 > 0) {
        func_8005492C(obj, racer, updateRate, arg3);
    } else {
        func_80052D7C(obj, racer, updateRate, arg3);
    }
    apply_vehicle_rotation_offset(racer, updateRate, 0, 0, 0);
    header = get_current_level_header();
    if ((racer->unkC0 != 0.0 && header->unk2) || D_8011D581 == 10) {
        if (racer->unk1F0) {
            racer->checkpoint_distance -= 0.3;
        } else {
            racer->checkpoint_distance -= 0.1;
        }
        func_80059080(obj, racer, &xVel, &yVel, &zVel);
        if (racer->unk1F0) {
            racer->checkpoint_distance += 0.3;
        } else {
            racer->checkpoint_distance += 0.1;
        }
        xVel -= obj->segment.trans.x_position;
        zVel -= obj->segment.trans.z_position;
        yVel = sqrtf((xVel * xVel) + (zVel * zVel));
        xVel /= yVel;
        zVel /= yVel;
        obj->segment.x_velocity = xVel * 4.0f;
        obj->segment.z_velocity = zVel * 4.0f;
        obj->segment.y_velocity = 9.5f;
        racer->unk1F0 = 1;
    } else if (racer->unk1E2 > 2) {
        racer->unk1F0 = 0;
    }
    obj->segment.unk3B = 0;
    tempAngle = ((-racer->unk1A2 >> 8) / D_8011D570);
    tempAngle = 40 - tempAngle;
    if (tempAngle < 0) {
        tempAngle = 0;
    }
    if (tempAngle > 73) {
        tempAngle = 73;
    }
    obj->segment.unk18 = tempAngle;
    func_8005234C(racer);
    angle = gCurrentCarSteerVel - (u16) racer->unk1A2;
    WRAP(angle, -0x8000, 0x8000);
    angle >>= 2;
    CLAMP(angle, -0x2EE, 0x2EE);
    racer->unk1A2 += (angle * updateRate);
    obj->segment.trans.y_rotation = racer->unk1A0 + racer->unk1A2;
    racer->unk1A6 += ((D_8011D558 - racer->unk1A6) * updateRate) >> 4;
    obj->segment.trans.z_rotation = racer->unk1A4 + racer->unk1A6;
    if (!racer->unk1F0) {
        D_8011D510.y_rotation = racer->unk1A0 + racer->unk10C;
        D_8011D510.x_rotation = 0;
        D_8011D510.z_rotation = 0;
        D_8011D510.x_position = 0.0f;
        D_8011D510.y_position = 0.0f;
        D_8011D510.z_position = 0.0f;
        D_8011D510.scale = 1.0f;
        func_8006FE74(&mtx, &D_8011D510);
        guMtxXFMF(mtx, racer->lateral_velocity, 0.0f, racer->velocity, &obj->segment.x_velocity, &tempVel, &obj->segment.z_velocity);
    }
    if (racer->unk175) {
        obj->segment.x_velocity = D_8011D578;
        obj->segment.z_velocity = D_8011D57C;
    }
    if (!racer->unk148) {
        xVel = obj->segment.x_velocity;
        zVel = obj->segment.z_velocity;
        if (racer->unk1D2) {
            xVel += racer->unk11C;
            zVel += racer->unk120;
        }
        xVel += racer->unk84;
        zVel += racer->unk88;
        func_80011570(obj, xVel * arg3, obj->segment.y_velocity * arg3, zVel * arg3);
    } else {
        func_80050754(obj, racer, arg3);
    }
    if (D_8011D55C == -1 && !func_80023568()) {
            func_80055A84(obj, racer, updateRate);
    } else {
        func_80054FD0(obj, racer, updateRate);
    }
    if (!racer->unk201) {
        obj->unk74 = 0;
    } else if (racer->unk1D6 < 5) {
        func_800AF714(obj, updateRate);
    }
    func_80053750(obj, racer, arg3);
    tempVel = 1.0f / arg3;
    xVel = (((obj->segment.trans.x_position - tempX) - D_8011D548) * tempVel) - racer->unk84;
    obj->segment.y_velocity = (obj->segment.trans.y_position - tempY) * tempVel;
    zVel = (((obj->segment.trans.z_position - tempZ) - D_8011D54C) * tempVel) - racer->unk88;
    D_8011D510.y_rotation = -(racer->unk1A0 + racer->unk10C);
    D_8011D510.x_rotation = -obj->segment.trans.x_rotation;
    D_8011D510.z_rotation = -obj->segment.trans.z_rotation;
    D_8011D510.x_position = 0.0f;
    D_8011D510.y_position = 0.0f;
    D_8011D510.z_position = 0.0f;
    D_8011D510.scale = 1.0f;
    func_8006FE74(&mtx, &D_8011D510);
    guMtxXFMF(mtx, xVel, 0.0f, zVel, &hVel, &tempVel, &yVel);
    if (racer->unk1D2) {
        racer->unk1D2 -= updateRate;
        if (racer->unk1D2 < 0) {
            racer->unk1D2 = 0;
        }
    } else {
        tempVel = racer->velocity - yVel;
        if (tempVel > 0.5) {
            racer->velocity -= tempVel - 0.5;
        }
        if (tempVel < -0.5) {
            racer->velocity -= tempVel + 0.5;
        }
        tempVel = racer->lateral_velocity - hVel;
        if (tempVel && tempVel) {}
        if (tempVel > 0.5) {
            racer->lateral_velocity -= tempVel - 0.5;
        }
        if (tempVel < -0.5) {
            racer->lateral_velocity -= tempVel + 0.5;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_8005492C.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80054FD0.s")

void func_80055A84(Object *obj, Object_Racer *racer, s32 updateRate) {
    f32 angleZ;
    f32 distance;
    s32 sp74;
    s32 flags;
    s32 temp_v1_2;
    f32 tempX;
    f32 tempY;
    f32 tempZ;
    s32 xRot;
    f32 angleX;
    f32 *temp_v0;
    f32 tempPos[3];
    s32 i;
    f32 sp40;
    s8 sp3F;
    s8 shouldSquish;

    if (D_8011D4F0[0] < obj->segment.trans.y_position) {
        obj->segment.trans.y_position = D_8011D4F0[0];
    }
    temp_v0 =(f32 *) get_misc_asset(56);
    sp3F = -1;
    sp40 = temp_v0[racer->unk1D7];
    tempPos[0] = obj->segment.trans.x_position;
    tempPos[1] = obj->segment.trans.y_position;
    tempPos[2] = obj->segment.trans.z_position;
    D_8011D548 = 0.0f;
    D_8011D54C = 0.0f;
    sp74 = 0;
    flags = 0;
    if (racer->playerIndex != PLAYER_COMPUTER || racer->unk1D7 < 5) {
        flags = func_80017248(obj, 1, &sp74, racer->unkD8, tempPos, &sp40, &sp3F);
    }
    if (flags & 0x80) {
        D_8011D548 = tempPos[0] - obj->segment.trans.x_position;
        D_8011D54C = tempPos[2] - obj->segment.trans.z_position;
        flags &= ~0x80;
    }
    shouldSquish = 0;
    if (flags && tempPos[1] < obj->segment.trans.y_position - 4.0) {
        shouldSquish = 1;
    }
    func_80031130(1, &racer->unkD8[0], tempPos, racer->unk1D6);
    sp74 = 0;
    racer->unk1E3 = func_80031600(racer->unkD8 , tempPos, &sp40, &sp3F, 1, &sp74);
    racer->unk1E4 = flags;
    racer->unk1E3 |= flags;
    racer->unk1E2 = 0;
    if (racer->unk1E3) {
        racer->unk1E3 = 15;
        racer->unk1E2 = 4;
    }
    if (shouldSquish && sp74) {
        if (racer->squish_timer == 0) {
            racer->unk187 = 4;
        } else {
            racer->squish_timer = 60;
        }
    }
    for (i = 0; i < 3; i++) {
        racer->unkD8[i] = tempPos[i];
    }
    racer->wheel_surfaces[0] = sp3F;
    i = 1;
    racer->wheel_surfaces[1] = sp3F;
    racer->wheel_surfaces[2] = sp3F;
    racer->wheel_surfaces[3] = sp3F;
    obj->segment.trans.x_position = racer->unkD8[0];
    obj->segment.trans.y_position = racer->unkD8[1];
    obj->segment.trans.z_position = racer->unkD8[2];
    if (racer->unk1E2) {
        func_8002ACD4(&tempX, &tempY, &tempZ);
        angleX = cosine_s(-obj->segment.trans.y_rotation);
        angleZ = sine_s(-obj->segment.trans.y_rotation);
        distance = (tempX * angleZ) + (tempZ * angleX);
        tempZ = (tempX * angleX) - (tempZ * angleZ);
        temp_v1_2 = -(s16)(u16)arctan2_f(distance, tempY);
        if (temp_v1_2 < 0x2000 && temp_v1_2 > -0x2000) {
            racer->unk1A4 = temp_v1_2;
        }
        xRot = -(s16)(u16)arctan2_f(tempZ, tempY);
        if ((xRot < 0x2000) && (xRot > -0x2000)) {
            obj->segment.trans.x_rotation = xRot;
        }
        if (racer->unk1D6 == 4) {
            if (1)
            xRot -= (u16) obj->segment.trans.x_rotation;
            WRAP(xRot, -0x8000, 0x8000);
            obj->segment.trans.x_rotation += xRot >> 2;
        }
    }
    if (racer->unk1D6 != 4 && racer->unk1D6 != 2 && racer->unk1D6 != 10 && racer->unk1D6 != 7) {
        CLAMP(racer->unk1A4, -0x3400, 0x3400);
        CLAMP(obj->segment.trans.x_rotation, -0x3400, 0x3400);
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_80055EC0.s")

void play_char_horn_sound(Object *obj, Object_Racer *racer) {
    if (get_filtered_cheats() & CHEAT_HORN_CHEAT) {
        // Play character voice instead of horn.
        func_800570B8(obj, 0x162, 8, 0x82);
    } else {
        // Play character's horn sound
        racer_play_sound(obj, racer->characterId + SOUND_HORN1);
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_8005698C.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80056E2C.s")

/**
 * Play a spatial sound, emitting from the position of the racer object.
 */
void racer_play_sound(Object *obj, s32 soundID) {
    Object_Racer *racer = &obj->unk64->racer;
    if (D_8011D55C != -1 && racer->unk108 == 0) {
        play_sound_spatial(soundID, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, NULL);
    }
}

void func_800570A4(Object *obj, s32 arg1, s32 arg2) {
    Object_Racer *temp = &obj->unk64->racer;
    temp->unk20E = arg1;
    temp->unk210 = arg2;
}

void func_800570B8(Object *obj, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v1;
    Object_64 *temp_s2;

    temp_s2 = obj->unk64;
    if ((temp_s2->racer.unk108 == 0) && ((!(arg3 & 0x80)) || (D_8011D55C != -1))) {
        if (arg3 == 2) {
            if ((temp_s2->racer.unk24 != 0) && (arg1 != temp_s2->racer.unk2A)) {
                func_800096F8(temp_s2->racer.unk24);
                temp_s2->racer.unk24 = 0;
            }
        }
        if ((temp_s2->racer.unk24 == 0) && ((arg3 != 3) || (get_random_number_from_range(0, 1) != 0))) {
            temp_s2->racer.unk2A = arg1;
            arg1 += temp_s2->racer.characterId;
            temp_v1 = (get_random_number_from_range(0, arg2 - 1) * 12) + arg1;
            if (arg2 - 1 > 0) {
                while (temp_v1 == temp_s2->racer.unk28) {
                    temp_v1 = (get_random_number_from_range(0, arg2 - 1) * 12) + arg1;
                }
            }
            func_80009558(temp_v1, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, &temp_s2->racer.unk24);
            temp_s2->racer.unk28 = temp_v1;
        }
    }
}

//s32 soundID = 545;

/**
 * This function dictates the base top speed of a racer.
 * During the race start sequence it hardsets it to 0 so you don't go anywhere.
 * It then adds to the multiplier an amount based on your bananas.
 */
f32 handle_racer_top_speed(Object *obj, Object_Racer *racer) {
    f32 speedMultiplier;
    s32 timer;
    f32 bananas;
    f32 cap;
    s32 timer2;
    s32 timer3;

    // If you want to change the baseline speed of vehicles, this is what you change.
    speedMultiplier = 1.0f;
    // Set the player's top speed to 0 before the race starts, so you can't jump the start.
    if (gRaceStartTimer) {
        speedMultiplier = 0.0f;
    }
    timer3 = get_race_start_timer();
    if (gRaceStartTimer);
    // If the A button is held for the first time, 30 frames prior to starting,
    // decide how much boost to add based on when it was pressed.
    if (gRaceStartTimer > 0 && gRaceStartTimer < 30 && !racer->startInput) {
        timer = gRaceStartTimer - 14;
        if (gActivePlayerButtonPress & A_BUTTON) {
            if (timer < 0 && timer3 >= 0) {
                timer = 0;
            }
            // Keep the timer positive.
            if (timer < 0) {
                timer = -timer;
            }
            if ((gCurrentCarInput & Z_TRIG)) {
                if (timer < 2) {
                    timer = 0;
                }
            }
			timer2 = 24 - timer;
            racer->boostTimer = normalise_time(timer2 >> 1);
            if (timer2 == 24) {
                racer_play_sound(obj, SOUND_SELECT);
                racer->boostTimer = normalise_time(20);
            }
            if (racer->boostTimer < normalise_time(20)) {
                racer->boostType = BOOST_SMALL;
            } else if (racer->boostTimer < normalise_time(35)) {
                racer->boostType = BOOST_MEDIUM;
            } else {
                racer->boostType = BOOST_LARGE;
            }
            racer->boost_sound |= BOOST_RACE_START;
            D_8011D560 = 7;
            gStartBoostTime = racer->boostTimer;
        }
        // For the AI, expert AI will match the players start, and master AI will get a good start always.
        if ((racer->playerIndex == PLAYER_COMPUTER) && (racer->aiSkill == AI_MASTER || (racer->aiSkill == AI_EXPERT && gStartBoostTime))) {
            if (gStartBoostTime) {
                racer->boostTimer = gStartBoostTime;
            } else {
                racer->boostTimer = normalise_time(5);
            }
            if (racer->boostTimer < normalise_time(20)) {
                racer->boostType = BOOST_SMALL;
            } else if (racer->boostTimer < normalise_time(35)) {
                racer->boostType = BOOST_MEDIUM;
            } else {
                racer->boostType = BOOST_LARGE;
            }
        }
    }
    /*render_printf("%d", soundID);
    if (gActivePlayerButtonPress & L_TRIG)
    {
        racer_play_sound(obj, soundID);
    }
    if (gActivePlayerButtonPress & L_JPAD)
        soundID --;
    if (gActivePlayerButtonPress & R_JPAD)
        soundID ++;*/
    if (racer->boostTimer && !gRaceStartTimer && timer3 && racer->raceStatus == STATUS_RACING) {
         func_80072348(racer->playerIndex, 6);
    }
    if ((gRaceStartTimer < 80) && gActivePlayerButtonPress & A_BUTTON) {
        racer->startInput = 1;
    }
    if (!gRaceStartTimer) {
        if (racer->boost_sound & BOOST_RACE_START) {
            racer->boost_sound &= ~BOOST_RACE_START;
            func_800570B8(obj, 354, 8, 130);
            racer_play_sound(obj, SOUND_NITRO_BOOST);
        }
    }

    if (racer->boost_sound & BOOST_UNK2) {
        racer->boost_sound &= ~BOOST_UNK2;
    }
    bananas = racer->bananas;
    // Cheats only apply to human players.
    if (racer->playerIndex == PLAYER_COMPUTER) {
        bananas = racer->unk124;
    }  else {
        if (bananas > 10.0) {
            // Cap the banana speed boost to 10 if the unlimited bananas cheat is not enabled.
            if (!(get_filtered_cheats() & CHEAT_NO_LIMIT_TO_BANANAS)) {
                bananas = 10.0f;
            }
        }
        // Make the speed bonus negative if the speed reduction cheat is on.
        if (((get_filtered_cheats() & CHEAT_BANANAS_REDUCE_SPEED)) && (bananas > 0.0f)) {
            bananas = -bananas;
        }
    }
    // This also means the AI can have twice as many
    cap = 20.0f;
    if (bananas > cap) {
        bananas = cap;
    }
    if (bananas < -cap) {
        bananas = -cap;
    }
    speedMultiplier += (bananas * 0.025f);
    return speedMultiplier;
}

void func_800575EC(Object *obj, Object_Racer *racer) {
    Matrix mf;

    D_8011D510.y_rotation = obj->segment.trans.y_rotation;
    D_8011D510.x_rotation = obj->segment.trans.x_rotation;
    D_8011D510.z_rotation = 0;
    D_8011D510.x_position = 0.0f;
    D_8011D510.y_position = 0.0f;
    D_8011D510.z_position = 0.0f;
    D_8011D510.scale = 1.0f;
    func_8006FC30(mf, &D_8011D510);
    guMtxXFMF(mf, 0.0f, 0.0f, 1.0f, &racer->ox1, &racer->oy1, &racer->oz1);
    guMtxXFMF(mf, 0.0f, 1.0f, 0.0f, &racer->ox2, &racer->oy2, &racer->oz2);
    guMtxXFMF(mf, 1.0f, 0.0f, 0.0f, &racer->ox3, &racer->oy3, &racer->oz3);
}

GLOBAL_ASM("asm/non_matchings/racer/func_800576E0.s")

void func_800579B0(Object_Racer *racer, UNUSED s32 arg1, f32 updateRate) {
    s32 temp, temp2;

    temp = gCurrentStickX - racer->unk1E1;
    temp2 = (temp * updateRate) * 0.125;

    if (temp != 0 && temp2 == 0) {
        if (temp > 0) {
            temp2 = 1;
        }
        if (temp < 0) {
            temp2 = -1;
        }
    }

    racer->unk1E1 += temp2;
}

void func_80057A40(Object *obj, Object_Racer *racer, f32 updateRate) {
	f32 temp_f14;
    s32 delta;
	s32 angle;

    if (gActivePlayerButtonPress & U_CBUTTONS && func_800A0190()) {
        gCameraObject->zoom++;
        if (gCameraObject->zoom > ZOOM_VERY_CLOSE) {
            gCameraObject->zoom = ZOOM_MEDIUM;
        }
        if (racer->playerIndex != PLAYER_COMPUTER) {
            func_80066060(racer->playerIndex, gCameraObject->zoom);
        }
        switch (gCameraObject->zoom) {
        case ZOOM_MEDIUM:
            func_80001D04(104, 0);
            break;
        case ZOOM_FAR:
            func_80001D04(105, 0);
            break;
        default:
            func_80001D04(106, 0);
            break;
        }
    }
    if (racer->raceStatus == STATUS_FINISHED && gCameraObject->mode != CAMERA_FINISH_CHALLENGE) {
            gCameraObject->mode = CAMERA_FINISH_RACE;
    }
    if (racer->unk108) {
        gCameraObject->mode = CAMERA_FIXED;
    }
    // Set the camera behaviour based on current mode.
    switch (gCameraObject->mode) {
	default:
		break;
    case CAMERA_CAR:
        // Driving a car.
        update_camera_car(updateRate, obj, racer);
        break;
    case CAMERA_PLANE:
        // Flying a plane.
        update_camera_plane(updateRate, obj, racer);
        break;
    case CAMERA_FIXED:
        // Fixes the camera in place, continuing to look at the player. Used when entering doors.
        update_camera_fixed(updateRate, obj, racer);
        break;
    case CAMERA_HOVERCRAFT:
        // Driving a hovercraft.
        update_camera_hovercraft(updateRate, obj, racer);
        break;
    case CAMERA_FINISH_CHALLENGE:
        // When you finish a challenge, the camera will rotate around the player, or around a set path, if the player's been KO'd.
        update_camera_finish_challenge(updateRate, obj, racer);
        break;
    case CAMERA_LOOP:
        // Used for loop-the-loops. Follows the face direction of the player exactly, the standard camera modes do not.
        update_camera_loop(updateRate, obj, racer);
        break;
    case CAMERA_FINISH_RACE:
        // When you finish a race, the camera will go into a more cinematic mode, following the player.
        update_camera_finish_race(updateRate, obj, racer);
        break;
    }
    temp_f14 = D_8011D586 / 10240.0f;
    gCameraObject->x_velocity = (((obj->segment.trans.x_position + (91.75 * racer->ox1) + (90.0 * racer->ox3)) - gCameraObject->trans.x_position) * temp_f14);
    gCameraObject->z_velocity = (((obj->segment.trans.z_position + (91.75 * racer->oz1) + (90.0 * racer->oz3)) - gCameraObject->trans.z_position) * temp_f14);
    gCameraObject->y_velocity = (((func_8003ACAC() + 48.5) - gCameraObject->trans.y_position) * temp_f14);
    gCameraObject->unk38 =  -gCameraObject->trans.x_rotation * temp_f14;
    gCameraObject->trans.x_position += gCameraObject->x_velocity;
    gCameraObject->trans.y_position += gCameraObject->y_velocity + gCameraObject->unk30;
    gCameraObject->trans.z_position += gCameraObject->z_velocity;
    if (!gRaceStartTimer && !D_8011D586) {
        gCameraObject->x_velocity = gCameraObject->x_velocity * 0.95;
        gCameraObject->y_velocity = gCameraObject->y_velocity * 0.95;
        gCameraObject->z_velocity = gCameraObject->z_velocity * 0.95;
    }
    angle = D_8011D586;
    if (angle > 0x1400) {
        angle = 0x2800 - D_8011D586;
    }
    if (angle > 0x600) {
        angle = 0x600;
    }
    angle = ((angle >> 4) + 4);
    delta = updateRate;
    if (D_8011D583) {
        D_8011D586 += (delta * angle);
        if (D_8011D586 > 0x2800) {
            D_8011D586 = 0x2800;
        }
    } else {
        D_8011D586 -= (delta * angle);
        if (D_8011D586 < 0) {
            D_8011D586 = 0;
        }
    }
    gCameraObject->trans.y_rotation -= D_8011D586;
    gCameraObject->unk3A -= delta;
    while (gCameraObject->unk3A < 0) {
        gCameraObject->unk3A += 5;
         gCameraObject->unk30 = -gCameraObject->unk30 * 0.75;
    }
}

void func_800580B4(Object *obj, Object_Racer *racer, s32 mode, f32 arg3) {
    f32 xPos, yPos, zPos;
    if ((D_8011D55C != -1) && (racer->raceStatus != STATUS_FINISHED)) {
        if (mode != gCameraObject->mode) {
            func_80057A40(obj, racer, arg3);
            xPos = gCameraObject->trans.x_position;
            yPos = gCameraObject->trans.y_position;
            zPos = gCameraObject->trans.z_position;
            gCameraObject->mode = mode;
            func_80057A40(obj, racer, arg3);
            if (gRaceStartTimer == 0 && D_8011D582 == 0) {
                gCameraObject->x_velocity = xPos - gCameraObject->trans.x_position;
                gCameraObject->y_velocity = yPos - (gCameraObject->trans.y_position + gCameraObject->unk30);
                gCameraObject->z_velocity = zPos - gCameraObject->trans.z_position;
            }
        }
    }
}

#ifdef NON_EQUIVALENT
void update_camera_car(f32 updateRate, Object *obj, Object_Racer *racer) {
    s64 pad;
    s32 segmentIndex;
    f32 sp54 = 120.0f;
    f32 baseDistance = 120.0f;
    f32 yVel = 50.0f;
    f32 temp_f16;
    f32 sineOffset;
    f32 baseSpeed;
    f32 lateralOffset;
    s32 angle;
    f32 cosOffset;
    s32 angleVel;
    f32 xOffset;
    f32 yOffset;
    f32 zOffset;
    f32 brakeVar;
    f32 tempVel;
    s32 baseAngle = 0x400;
    s32 newAngle;
    s32 numViewports;
    s32 tempAngle;
    s32 delta = (s32) updateRate;

    numViewports = get_viewport_count();
    if (numViewports == 1) {
        baseDistance = 192.0f;
        baseAngle = 0x200;
    } else if (numViewports > 2) {
        baseDistance = 100.0f;
        yVel = 40.0f;
    }
    numViewports = func_80023568();
    if (numViewports == 1 || numViewports == 4) {
        baseDistance = 144.0f;
        yVel = 110.0f;
        if (gCameraObject->zoom == ZOOM_VERY_CLOSE) {
            baseDistance += 30.0f;
        }
        baseAngle = 0xD00;
    }
    angle = racer->unk19E >> 3;
    racer->unk196 = (-racer->unk1A0 - racer->unk19E) + 0x8000;
    if (angle > 0x400) {
        angle = 0x400;
    }
    if (angle < -0x400) {
        angle = -0x400;
    }
    angle = angle * delta;
    angleVel = angle;
    if (angleVel > 0 && angleVel < racer->unk19E) {
        racer->unk19E -= angleVel;
    }
    if (angleVel < 0) {
        if (racer->unk19E < angleVel) {
            racer->unk19E -= angleVel;
        }
    }
    brakeVar = racer->brake;
    baseSpeed = racer->unk8;
    switch (gCameraObject->zoom) {
    case 1:
        baseDistance += 35.0f;
        break;
    case 2:
        baseDistance -= 35.0f;
        yVel -= 10.0f;
        break;
    case 3:
        baseDistance -= 53.0f;
        yVel -= 5.0f;
        brakeVar = 0.0f;
        baseSpeed *= 0.25;
        break;
    }
    if (racer->unk1E2 > 2 || racer->unk1E5 != 0) {
        angle = (obj->segment.trans.x_rotation);
        if (angle > 0) {
            angle -= 0x71C;
            if (angle < 0) {
                angle = 0;
            }
            angle >>= 1;
        } else {
            angle += 0x71C;
            if (angle > 0) {
                angle = 0;
            }
        }
        angle = baseAngle - angle;
        tempAngle = angle - (u16) gCameraObject->trans.x_rotation;
        if (tempAngle > 0x8000) {
            tempAngle -= 0xFFFF;
        }
        if (tempAngle < -0x8000) {
            tempAngle += 0xFFFF;
        }
        gCameraObject->trans.x_rotation += (tempAngle * delta) >> 4;
    }
    if (racer->velocity < 0.0) {
        tempVel = 6.0f;
        if (racer->drift_direction) {
            tempVel = 3.0f;
        }
        tempVel = -(racer->velocity * brakeVar) * tempVel;
        if (65.0 < tempVel) {
            tempVel = 65.0f;
        }
        baseDistance -= tempVel;
    }
    if (!racer->drift_direction) {
        baseDistance += baseSpeed * 60.0f;
    } else {
        baseDistance += baseSpeed * 30.0f;
    }
    if (gRaceStartTimer == 0) {
        if (normalise_time(0x24) < racer->boostTimer) {
            baseDistance = -30.0f;
        } else if (racer->boostTimer > 0) {
            baseDistance = 180.0f;
        }
    }
    if (gRaceStartTimer > 80) {
        gCameraObject->unk1C = baseDistance;
        gCameraObject->unk20 = yVel;
    }
    gCameraObject->unk1C += (baseDistance - gCameraObject->unk1C) * 0.125;
    gCameraObject->unk20 += (yVel - gCameraObject->unk20) * 0.125;
    cosOffset = cosine_s(gCameraObject->trans.x_rotation - baseAngle);
    sineOffset = sine_s(gCameraObject->trans.x_rotation - baseAngle);
    lateralOffset = gCameraObject->unk1C;
    lateralOffset = (lateralOffset * sineOffset) - (gCameraObject->unk20 * cosOffset);
    yVel = (gCameraObject->unk1C * cosOffset) + (gCameraObject->unk20 * sineOffset);
    sineOffset = cosine_s(-racer->unk196 + 0x8000) * lateralOffset;
    cosOffset = sine_s(-racer->unk196 + 0x8000) * lateralOffset;
    baseDistance = 0.0f;
    if (gCurrentCarInput & 0x8000) {
        baseDistance = racer->lateral_velocity * 1.3;
        if (baseDistance > 0.0f) {
            baseDistance -= 1.5;
            if (baseDistance < 0.0f) {
                baseDistance = 0.0f;
            }
        } else {
            baseDistance += 1.5;
            if (baseDistance > 0.0f) {
                baseDistance = 0.0f;
            }
        }
    }
    if (racer->drift_direction) {
        baseDistance = -(f32) racer->drift_direction * 12.0f;
    }
    racer->unkC8 += (baseDistance - racer->unkC8) * 0.125;
    if (racer->spinout_timer) {
        racer->camera_zoom -= racer->camera_zoom * 0.25;
    } else {
        racer->camera_zoom += (10.0 - racer->camera_zoom) * 0.25;
    }
    xOffset = obj->segment.trans.x_position - (racer->ox1 * racer->camera_zoom);
    yOffset = obj->segment.trans.y_position - (racer->oy1 * racer->camera_zoom);
    zOffset = obj->segment.trans.z_position - (racer->oz1 * racer->camera_zoom);
    tempVel = cosine_s(racer->unk196 + 0x4000) * racer->unkC8;
    baseDistance = xOffset + tempVel;
    gCameraObject->trans.x_position = sineOffset + baseDistance;
    yOffset += yVel;
    temp_f16 = (gCameraObject->trans.y_position - yOffset) * 0.25;
    if (temp_f16 < -2.0) {
        gCameraObject->trans.y_position -= temp_f16 + 2.0;
    }
    gCameraObject->trans.y_position -= temp_f16 * 0.25;
    if (temp_f16 > 0.0f || gRaceStartTimer) {
        gCameraObject->trans.y_position = yOffset;
    }
    gCameraObject->trans.z_position = zOffset + (-sine_s(racer->unk196 + 0x4000) * racer->unkC8) + cosOffset;
    gCameraObject->trans.y_rotation = racer->unk196;
    newAngle = gCameraObject->trans.z_rotation;
    if ((racer->drift_direction && racer->brake > 0.0) || D_8011D586) {
        newAngle = 0;
    }
    angle = obj->segment.trans.z_rotation;
    angleVel = (newAngle + angle) >> 4;
    gCameraObject->trans.z_rotation -= angleVel;
    if (gCameraObject->trans.z_rotation > 0x2000) {
        gCameraObject->trans.z_rotation = 0x2000;
    }
    if (gCameraObject->trans.z_rotation < -0x2000) {
        gCameraObject->trans.z_rotation = -0x2000;
    }
    gCameraObject->trans.y_position -= racer->unkC8 * cosine_s(gCameraObject->trans.z_rotation);
    lateralOffset = (yOffset = gCameraObject->trans.x_position);
    segmentIndex = get_level_segment_index_from_position(lateralOffset, gCameraObject->trans.y_position, gCameraObject->trans.z_position);
    if (segmentIndex != -1) {
        gCameraObject->unk34 = segmentIndex;
    }
    racer->unk196 = gCameraObject->trans.y_rotation;
}
#else
GLOBAL_ASM("asm/non_matchings/racer/update_camera_car.s")
#endif

/**
 * Handles the camera movement when the player has finished a challenge.
 * If the player still exists, it will follow and rotate around the player.
 * Otherwise, it will follow a set path while rotating.
 */
void update_camera_finish_challenge(UNUSED f32 updateRate, Object *obj, Object_Racer *racer) {
    s32 levelSeg;
    f32 temp_f12;
    f32 zOffset;
    f32 xOffset;

    gCameraObject->trans.y_rotation += 0x200;
    if (1);
    gCameraObject->trans.x_rotation = 0x400;
    gCameraObject->trans.z_rotation = 0;
    gCameraObject->unk1C = 150.0f;
    xOffset = cosine_s(0x8000 - gCameraObject->trans.y_rotation) * gCameraObject->unk1C;
    zOffset = sine_s(0x8000 - gCameraObject->trans.y_rotation) * gCameraObject->unk1C;
    gCameraObject->trans.x_position = obj->segment.trans.x_position + xOffset;
    temp_f12 = (gCameraObject->trans.y_position - (obj->segment.trans.y_position + 45.0f)) * 0.25;
    if (temp_f12 < -2.0) {
        gCameraObject->trans.y_position = (gCameraObject->trans.y_position - (temp_f12 + 2.0));
    }
    if (temp_f12 > 0.0f) {
        gCameraObject->trans.y_position = obj->segment.trans.y_position + 45.0f;
    }
    gCameraObject->trans.z_position = obj->segment.trans.z_position + zOffset;
    levelSeg = get_level_segment_index_from_position(gCameraObject->trans.x_position, gCameraObject->trans.y_position, gCameraObject->trans.z_position);
    if (levelSeg != -1) {
        gCameraObject->unk34 = levelSeg;
    }
    racer->unk196 = gCameraObject->trans.y_rotation;
}

/**
 * Handles the camera movement when the player has finished the race.
 * Uses a more cinematic approach to following the player, using pre-existing points in the track to look from.
 */
void update_camera_finish_race(UNUSED f32 updateRate, Object *obj, Object_Racer *racer) {
    s32 cameraID;
    Object *tempObj;
    f32 xDiff;
    f32 yDiff;
    f32 zDiff;
    f32 distance;

    cameraID = racer->spectateCamID;
    tempObj = func_8001BDD4(obj, &cameraID);
    if (!tempObj) {
        gCameraObject->mode = CAMERA_FINISH_CHALLENGE;
        return;
    }
    racer->spectateCamID = cameraID;
    gCameraObject->trans.x_position = tempObj->segment.trans.x_position;
    gCameraObject->trans.y_position = tempObj->segment.trans.y_position;
    gCameraObject->trans.z_position = tempObj->segment.trans.z_position;
    xDiff = gCameraObject->trans.x_position - obj->segment.trans.x_position;
    yDiff = gCameraObject->trans.y_position - obj->segment.trans.y_position;
    zDiff = gCameraObject->trans.z_position - obj->segment.trans.z_position;
    distance = sqrtf((xDiff * xDiff) + (zDiff * zDiff));
    gCameraObject->trans.y_rotation = (s16) (0x8000 - func_8007066C((s32) xDiff, (s32) zDiff));
    gCameraObject->trans.x_rotation = func_8007066C((s32) yDiff, (s32) distance);
    gCameraObject->trans.z_rotation = 0;
    gCameraObject->unk34 = get_level_segment_index_from_position(gCameraObject->trans.x_position, racer->oy1, gCameraObject->trans.z_position);
}

/**
 * Stops the camera in place when set, while still pointing in the direction of the player.
 * Used when entering doors.
 */
void update_camera_fixed(f32 updateRate, struct Object *obj, struct Object_Racer *racer) {
    s32 delta;
    f32 xDiff;
    f32 zDiff;
    delta = (s32) updateRate;
    xDiff = gCameraObject->trans.x_position - obj->segment.trans.x_position;
    zDiff = gCameraObject->trans.z_position - obj->segment.trans.z_position;
    gCameraObject->trans.y_rotation += ((((-func_8007066C((s32) xDiff, (s32) zDiff)) -
                                    gCameraObject->trans.y_rotation) + 0x8000) * delta) >> 4;
    gCameraObject->trans.z_rotation -= (((s32) (gCameraObject->trans.z_rotation * delta)) >> 4);
    gCameraObject->unk34 = get_level_segment_index_from_position(gCameraObject->trans.x_position,
                            racer->oy1, gCameraObject->trans.z_position);
}

void func_80059080(UNUSED Object *obj, Object_Racer *racer, f32 *xVel, f32 *yVel, f32 *zVel) {
    unknown8011AECC *temp_v0_2;
    s32 splinePos;
    s32 destReached;
    s32 splineEnd;
    f32 splineX[5];
    f32 splineY[5];
    f32 splineZ[5];
    f32 magnitude;
    s32 i;

    splineEnd = func_8001BA64();

    if (splineEnd) {
        magnitude = 1.0 - racer->checkpoint_distance;
        if (magnitude < 0.0f) {
            magnitude = 0.0f;
        }
        if (racer->unk192) {}
        splinePos = racer->unk192 - 2;
        if (splinePos < 0) {
            splinePos += splineEnd;
        }
        for (i = 0; i < 5; i++) {
            temp_v0_2 = func_8001BA1C(splinePos, racer->unk1C8);
            splineX[i] = temp_v0_2->unk10;
            splineY[i] = temp_v0_2->unk14;
            splineZ[i] = temp_v0_2->unk18;
            splinePos++;
            if (splinePos == splineEnd) {
                splinePos = 0;
            }
        }
        destReached = 0;
        if (magnitude >= 1.0) {
            destReached = 1;
            magnitude -= 1.0;
        }
        *xVel = catmull_rom_interpolation(splineX, destReached, magnitude);
        *yVel = catmull_rom_interpolation(splineY, destReached, magnitude);
        *zVel = catmull_rom_interpolation(splineZ, destReached, magnitude);
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_80059208.s")

void get_timestamp_from_frames(s32 frameCount, s32 *minutes, s32 *seconds, s32 *hundredths) {
    if (gVideoRefreshRate == REFRESH_50HZ) {
        frameCount = (f32)frameCount * 1.2;
    }
    // (REFRESH_60HZ * 60) is just frames per minute basically
    *minutes = frameCount / (REFRESH_60HZ * 60);
    *seconds = (frameCount - (*minutes * (REFRESH_60HZ * 60))) / REFRESH_60HZ;
    *hundredths = (((frameCount - (*minutes * (REFRESH_60HZ * 60))) - (*seconds * REFRESH_60HZ)) * 100) / REFRESH_60HZ;
}

void func_800598D0(void) {
    gGhostData[0] = allocate_from_main_pool_safe(0x21C0, COLOUR_TAG_RED);
    gGhostData[1] = (GhostNode *)gGhostData[0] + MAX_NUMBER_OF_GHOST_NODES;
    gGhostData[2] = NULL; // T.T. Ghost
    D_8011D5A0[0] = 0;
    D_8011D5A0[1] = 0;
    D_8011D5A0[2] = 0;
    D_8011D5A8[0] = 0;
    D_8011D5A8[1] = 0;
    D_8011D59D = 0;
    D_8011D5AC = -1;
}

void func_80059944(void) {
    D_8011D59C = D_8011D59D;
    D_8011D5A0[D_8011D59C] = 0;
    D_8011D5A8[D_8011D59C] = 0;
    D_8011D59E = 0;
}

void func_80059984(s32 arg0) {
    D_8011D59D = (s8)((D_8011D59C + 1) & 1);
    D_8011D5AC = arg0;
}

s32 func_800599A8(void) {
    return D_8011D5AC;
}

s32 func_800599B8(s32 arg0, s32 arg1, s16 arg2, s16 *arg3, s16 *arg4) {
    s32 temp_v0;
    s32 temp_t8;
    s16 sp2E;

    temp_t8 = (D_8011D59C + 1) & 1;
    temp_v0 = func_80074B34(arg0, (s16)arg1, arg2, arg3, arg4, &sp2E, gGhostData[temp_t8]);
    if (arg3 != 0) {
        if (temp_v0 == 0) {
            D_8011D5A0[temp_t8] = sp2E;
            D_8011D5AC = arg1;
        } else {
            D_8011D5AC = -1;
        }
    }

    return temp_v0;
}

/**
 * Loads T.T. ghost node data into gGhostData[2].
 * Returns 0 if successful, or 1 if an error occured.
 */
s32 load_tt_ghost(s32 ghostOffset, s32 size, s16 *outTime) {
    GhostHeader *ghost = allocate_from_main_pool_safe(size, COLOUR_TAG_RED);
    if (ghost != NULL) {
        load_asset_to_address(ASSET_TTGHOSTS, ghost, ghostOffset, size);
        if (gGhostData[2] != NULL) {
            free_from_memory_pool(gGhostData[2]);
        }
        gGhostData[2] = allocate_from_main_pool_safe(size - sizeof(GhostHeader), COLOUR_TAG_WHITE);
        if (gGhostData[2] != NULL) {
            *outTime = ghost->time;
            gTTGhostNodeCount = ghost->nodeCount;
            bcopy((u8 *)ghost + 8, gGhostData[2], size - sizeof(GhostHeader));
            free_from_memory_pool(ghost);
            return 0;
        }
        free_from_memory_pool(ghost);
    }
    return 1;
}

void free_tt_ghost_data(void) {
    if (gGhostData[2] != NULL) {
        free_from_memory_pool(gGhostData[2]);
    }
    gGhostData[2] = NULL;
}

s32 func_80059B7C(s32 controllerIndex, s32 arg1, s16 arg2, s16 arg3, s16 arg4) {
    return func_80075000(controllerIndex, (s16)arg1, arg2, arg3, arg4, D_8011D5A0[D_8011D59C], gGhostData[D_8011D59C]);
}

GLOBAL_ASM("asm/non_matchings/racer/func_80059BF0.s")

s16 func_80059E20(void) {
    return D_8011D5A8[D_8011D59C];
}

GLOBAL_ASM("asm/non_matchings/racer/set_ghost_position_and_rotation.s")

void func_8005A3B0(void) {
    D_8011D584 = 1;
}

void func_8005A3C0(void) {
    D_8011D583 = 1;
}

void func_8005A3D0(void) {
    s32 i;
    s32 count = 0;
    u8 *temp = (u8 *)&obj_loop_goldenballoon;

    for (i = 0; i < gObjLoopGoldenBalloonLength; i++) {
        count += temp[i];
    }

    if (count != gObjLoopGoldenBalloonChecksum) {
        D_800DCB54 = 0x800;
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_8005A424.s")
GLOBAL_ASM("asm/non_matchings/racer/func_8005A6F0.s")
GLOBAL_ASM("asm/non_matchings/racer/func_8005B818.s")

// This gets called if an anti-piracy checksum fails in func_8005F850.
/**
 * Triggered upon failure of an anti-tamper test. Sets the first index of the surface speed
 * table to an unreasonable value, wrecking drivability while on it.
 */
void antipiracy_modify_surface_traction_table(void) {
    gSurfaceTractionTable[0] = 0.05f;
}

void func_8005C270(Object_Racer *racer) {
    s32 temp = func_8001BA64();

    racer->unk192--;
    if (racer->unk192 < 0) {
        racer->unk192 += temp;
        if (racer->unk193 > 0) {
            racer->unk193--;
        }
    }

    if (racer->unk190 > -0x7D00) {
        racer->unk190--;
    }
}
