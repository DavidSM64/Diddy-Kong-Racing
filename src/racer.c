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
#include "unknown_05CEF0.h"
#include "unknown_05DCD0.h"
#include "unknown_05F0C0.h"
#include "unknown_05F690.h"
#include "unknown_05FF10.h"
#include "unknown_005740.h"

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

s32 gNumViewports = 0; // Currently unknown, might be a different type.
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
s32 gObjLoopGoldenBalloonChecksum = 0xA597;

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

f32 gCurrentCourseHeight;
s32 D_8011D4F8[3];
s8 D_8011D504;
ObjectCamera *gCameraObject;
UNUSED s32 D_8011D50C;
ObjectTransform D_8011D510;
u32 gCurrentRacerInput;
u32 gCurrentButtonsPressed;
u32 gCurrentButtonsReleased;
s32 gCurrentStickX;
s32 gCurrentStickY;
s32 D_8011D53C; // Set to 0 and only 0. Checked for being 1, but never true.
s32 gRaceStartTimer;
f32 D_8011D544; // Starts are 300, then counts down when the race starts. Usage currently unknown.
f32 D_8011D548;
f32 D_8011D54C;
s16 D_8011D550;
s8 D_8011D552;
s8 D_8011D553;
s32 gCurrentCarSteerVel;
s32 D_8011D558;
s32 gCurrentPlayerIndex;
s16 D_8011D560; // Set, but never read.
UNUSED s16 D_8011D562;
f32 *gCurrentRacerMiscAssetPtr;
f32 *D_8011D568;
f32 gCurrentRacerWeightStat;
f32 gCurrentRacerHandlingStat;
f32 D_8011D574;
f32 D_8011D578;
f32 D_8011D57C;
u8 D_8011D580;
s8 gCurrentSurfaceType;
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
s8 D_8011D5AE;
s8 D_8011D5AF;
struct TempStruct8 **D_8011D5B0;
s32 D_8011D5B4;
s16 D_8011D5B8;

extern void func_8000488C(u8 *soundMask);

/******************************/

GLOBAL_ASM("asm/non_matchings/racer/func_80042D20.s")

void func_80043ECC(s32 arg0, Object_Racer *racer, s32 updateRate) {
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
    temp_v0 = func_8006C18C();
    if (racer->boostTimer) {
        if (!D_8011D5BB) {
            temp_v0->unk8[3][0] += temp_v0->unk8[3][2];
            temp_v0->unk8[3][1] += temp_v0->unk8[3][3];
            D_8011D5BB = 1;
        }
        if (!(gCurrentRacerInput & A_BUTTON)) {
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
    if (racer->balloon_quantity) {
        if (D_8011D5BC < racer->balloon_level) {
            temp_v0->unk8[1][0] += temp_v0->unk8[1][2];
            temp_v0->unk8[1][1] += temp_v0->unk8[1][3];
        }
        D_8011D5BC = racer->balloon_level;
    } else {
        D_8011D5BC = 0;
    }
    test = get_misc_asset(MISC_ASSET_UNK0C);
    if ((gCurrentButtonsReleased & 0x2000) && racer->balloon_quantity) {
        if (racer->balloon_level < 3) {
            phi_a0 = test[racer->balloon_type * 3 + racer->balloon_level];
        } else {
            phi_a0 = racer->balloon_type;
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

    if (racer->unk214 == 0 && racer->velocity < -0.5f){
        racer->unk215 -= updateRate;
        if (racer->unk215 < 0) {
            racer->unk215 = 0;
        }
    }

    if (racer->velocity > -1.0f && racer->unk214 == 0 && !gRaceStartTimer && D_8011D544 == 0.0f && racer->unk1E2 && racer->unk215 == 0) {
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
        gCurrentRacerInput &= ~A_BUTTON;
        gCurrentStickY = -50;
        gCurrentRacerInput |= B_BUTTON;
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
    Object_Racer *obj;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = (Object_Racer *) header->unk0[i]->unk64;
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

void func_80048C7C(Object* obj, Object_Racer* racer) {
    s8 bananas;

    if (racer->playerIndex == PLAYER_COMPUTER) {
        bananas = 0;
    } else {
        bananas = racer->bananas;
    }
    if ((racer->attackType == ATTACK_NONE) || (racer->shieldTimer > 0)) {
        racer->attackType = ATTACK_NONE;
        return;
    }
    if (racer->attackType != ATTACK_SQUISHED) {
        func_800576E0(obj, racer, 2);
    }
    play_random_character_voice(obj, SOUND_VOICE_CHARACTER_NEGATIVE, 8, 129);
    switch (racer->attackType) {
    // Getting hit by a rocket, running into a landmine or an oil slick.
    case ATTACK_EXPLOSION:
    case ATTACK_SPIN:
        racer->unk1F1 = 1;
        if (bananas == 0) {
            obj->segment.x_velocity = 0.0f;
            obj->segment.z_velocity = 0.0f;
            obj->segment.y_velocity = 8.0f;
        } else {
            obj->segment.x_velocity = obj->segment.x_velocity * 0.5f;
            obj->segment.z_velocity = obj->segment.z_velocity * 0.5f;
            obj->segment.y_velocity = 6.0f;
        }
        break;
    // Crushed by something big, like a snowball.
    case ATTACK_SQUISHED:
        racer->squish_timer = 60;
        break;
    // Running into a bubble trap.
    case ATTACK_BUBBLE:
        racer->unk204 = 0x78;
        obj->segment.x_velocity *= 0.7f;
        if (obj->segment.y_velocity > 2.0f) {
            obj->segment.y_velocity = 2.0f;
        }
        obj->segment.z_velocity *= 0.7f;
        break;
    // This goes unused.
    case ATTACK_FLUNG:
        racer->unk1F1 = 1;
        racer->velocity = 0.0f;
        obj->segment.y_velocity += 20.5f;
        racer_play_sound(obj, 0x139);
        break;
    }
    racer->attackType = ATTACK_NONE;
}

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
    baseSpeed = racer->forwardVel;
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
    if (racer->velocity < 0.0f) {
        yVel = -(racer->velocity * brakeVar) * 6.0f;
        if (racer->velocity);
        if (yVel > 65.0f) {
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
    gCameraObject->unk1C += (phi_f14 - gCameraObject->unk1C) * 0.125f;
    gCameraObject->unk20 += (phi_f18 - gCameraObject->unk20) * 0.125f;
    sp34 = cosine_s(gCameraObject->trans.x_rotation - sp24);
    phi_f18 = sine_s(gCameraObject->trans.x_rotation - sp24);
    phi_f18 = (gCameraObject->unk1C * sp34) + (gCameraObject->unk20 * phi_f18);
    xVel = cosine_s(-racer->unk196 + 0x8000) * gCameraObject->unk1C;
    zVel = sine_s(-racer->unk196 + 0x8000) * gCameraObject->unk1C;
    yVel = (1.0f - (D_8011D586 / 10240.0f));
    xVel -= racer->ox1 * 10.0f * yVel;
    zVel -= racer->oz1 * 10.0f * yVel;
    yVel = racer->lateral_velocity * 2;
    racer->unkC8 -= (racer->unkC8 - yVel) * 0.25f;
    yVel = cosine_s(racer->unk196 + 0x4000) * racer->unkC8;
    gCameraObject->trans.x_position = obj->segment.trans.x_position + xVel + yVel;
    yVel = gCameraObject->trans.y_position - (obj->segment.trans.y_position + phi_f18);
    if (yVel > 0.0f) {
        yVel *= 0.5f;
    } else {
        if (D_8011D53C == 1) {
            yVel *= 0.5f; // Unreachable. D_8011D53C is never not 0.
        } else {
            yVel *= 0.25f;
        }
        if (racer->boostTimer != 0) {
            yVel *= 2.0f;
        }
    }
    gCameraObject->trans.y_position -= yVel;
    gCameraObject->trans.z_rotation = 0;
    if (gRaceStartTimer) {
        gCameraObject->trans.y_position = obj->segment.trans.y_position + phi_f18;
    }

    sine_s(racer->unk196 + 0x4000); // Unused function call that wasn't fully optimised out.
    gCameraObject->trans.z_position = obj->segment.trans.z_position + zVel;
    gCameraObject->trans.y_rotation = racer->unk196;
    segmentIndex = get_level_segment_index_from_position(gCameraObject->trans.x_position, gCameraObject->trans.y_position, gCameraObject->trans.z_position);
    if (segmentIndex != SEGMENT_NONE) {
        gCameraObject->segmentIndex = segmentIndex;
    }
}

// Function itself matches but causes a diff in another func.
#ifdef NON_MATCHING
f32 func_800494E0(Object* obj1, Object_Racer* racer, f32 *pos, s8 arg3, s32 updateRate, s32 arg5, f32 arg6) {
    Matrix mtx;
    f32 velocity;
    s32 angle;
    s32 v1;
    f32 delta;

    delta = updateRate;
    if (arg3 == 14) {
        velocity = racer->velocity;
        if (velocity < 0.0f) {
            velocity = -velocity;
        }
        velocity = 1.0f - (velocity * 0.166);
        if (velocity < 0.0f) {
            velocity = 0.0f;
        }
    } else {
        obj1->segment.trans.x_position += pos[0] * delta * arg6;
        obj1->segment.trans.z_position += pos[2] * delta * arg6;
        velocity = 1.0f;
    }
    D_8011D510.y_rotation = -obj1->segment.trans.y_rotation;
    D_8011D510.x_rotation = 0;
    D_8011D510.z_rotation = 0;
    D_8011D510.x_position = 0.0f;
    D_8011D510.y_position = 0.0f;
    D_8011D510.z_position = 0.0f;
    D_8011D510.scale = 1.0f;
    func_8006FE74(&mtx, &D_8011D510);
    guMtxXFMF(mtx, pos[0], pos[1], pos[2], &pos[0], &pos[1], &pos[2]);
    angle = -((s16) (u16)arctan2_f(pos[0], pos[1])) * velocity;
    angle = (u16) (angle - (arg5 << 6)) - (u16) racer->x_rotation_vel;
    angle = angle > 0x8000 ? angle - 0xffff : angle;
    angle = angle < -0x8000 ? angle + 0xffff : angle;
    racer->x_rotation_vel += (angle * updateRate) >> 4;
    v1 = ((s16) (u16)arctan2_f(pos[2], pos[1]) * velocity);
    v1 += -gCurrentStickY * 32;
    v1 += 0x3C0;
    angle = (u16)v1 - ((u16) obj1->segment.trans.x_rotation);
    angle = angle > 0x8000 ? angle - 0xffff : angle;
    angle = angle < -0x8000 ? angle + 0xffff : angle;
    obj1->segment.trans.x_rotation += (angle * updateRate) >> 4;
    return velocity;
}
#else
GLOBAL_ASM("asm/non_matchings/racer/func_800494E0.s")
#endif

GLOBAL_ASM("asm/non_matchings/racer/func_80049794.s")

// Something Plane related.
void func_8004C0A0(s32 updateRate, Object *obj, Object_Racer *racer) {
    s32 temp_v1;
    s32 phi_v0;

    if (racer->unk1D7 != 10) {
        //!@bug Typo. Should've been `== 0`, not `= 0`.
        if ((racer->unk1F2 = 0)) {
            return; // This never gets called because of the typo.
        }
        phi_v0 = racer->steerAngle;
        phi_v0 = 40 - (phi_v0 >> 1);
        if (phi_v0 < 0) {
            phi_v0 = 0;
        }
        if (phi_v0 > 73) {
            phi_v0 = 73;
        }
        temp_v1 = phi_v0 - obj->segment.unk18;
        phi_v0 = 0;
        if (temp_v1 > 0) {
            phi_v0 = updateRate * 3;
            if (temp_v1 < phi_v0) {
                phi_v0 = temp_v1;
            }
        }
        if (temp_v1 < 0) {
            phi_v0 = updateRate * -3;
            if (phi_v0 < temp_v1) {
                phi_v0 = temp_v1;
            }
        }
        obj->segment.unk18 += phi_v0;
    }
}

// Another attack handler by the looks of things.
void func_8004C140(Object *obj, Object_Racer *racer) {
    s8 bananas;
    s8 attackType;
    if (racer->playerIndex == PLAYER_COMPUTER) {
        bananas = 0;
    } else {
        bananas = racer->bananas;
    }
    attackType = racer->attackType;
    if (attackType == 0 || racer->shieldTimer > 0) {
        racer->attackType = ATTACK_NONE;
        return;
    }
    if (attackType != ATTACK_SQUISHED) {
        func_800576E0(obj, racer, 2);
    }
    racer->unk18C = 360;
    if (racer->unk1C9 == 8) {
        racer->unk1C9 = 0;
    }
    if (racer->unk1D6 < 5) {
        play_random_character_voice(obj, SOUND_VOICE_CHARACTER_NEGATIVE, 8, 129);
        switch (racer->attackType) {
            case ATTACK_EXPLOSION:
            case ATTACK_SPIN:
                if (bananas != 0) {
                    racer->spinout_timer = 40;
                } else {
                    racer->spinout_timer = 60;
                }
                break;
            case ATTACK_UNK3:
                if (bananas != 0) {
                    racer->spinout_timer = 40;
                } else {
                    racer->spinout_timer = 60;
                }
                break;
            case ATTACK_BUBBLE:
                racer->unk204 = 120;
                obj->segment.x_velocity *= 0.7f;
                obj->segment.z_velocity *= 0.7f;
                break;
        }
        racer->attackType = ATTACK_NONE;
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
    temp_f16 = gCurrentCourseHeight;
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
    if (((!(gCurrentRacerInput & 0x10)) || racer->unk1E2 < 3) && !racer->unk1F5) {
        angle = (-racer->unk1A0 - (racer->unk196 & 0xFFFF)) + 0x8000;
        if (angle > 0x8000) {
            angle -= 0xFFFF;
        }
        angle = angle;
        if (angle < -0x8000) {
            angle += 0xFFFF;
        }
        if (racer->camera_zoom < 0.4f){
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
    baseSpeed = racer->forwardVel;
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
        baseSpeed *= 0.25f;
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
    if (racer->velocity < 0.0f && !racer->unk1E2) {
        tempVel = -(racer->velocity * brakeVar);
        tempVel = tempVel * 6.0f;
        if (65.0f < tempVel) {
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
    gCameraObject->unk1C += (phi_f14 - gCameraObject->unk1C) * 0.125f;
    gCameraObject->unk20 += (baseFloat1 - gCameraObject->unk20) * 0.125f;
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
        racer->unk74 = 8.0f;
    }
    if (racer->unk1E0 == 2 || racer->unk1E0 == -2) {
        racer->unk74 = 8.0f;
    }
    if (racer->unk74 > 2.0f) {
        racer->unk74 -= 0.2f;
    } else {
        racer->unk74 = 2.0f;
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
        angle = angle + (-(racer->x_rotation_vel >> 4));
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
        gCameraObject->segmentIndex = segmentIndex;
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
    if (gRaceStartTimer > 60) {
        zoom += ((f32) (gRaceStartTimer - 60) * 4.0f);
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
    gCameraObject->unk1C += (zoom - gCameraObject->unk1C) * 0.125f;
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
    if (segmentIndex != SEGMENT_NONE) {
        gCameraObject->segmentIndex = segmentIndex;
    }
    racer->unk196 = gCameraObject->trans.y_rotation;
    gCameraObject->trans.x_position += gCameraObject->x_velocity;
    gCameraObject->trans.y_position += gCameraObject->y_velocity;
    gCameraObject->trans.z_position += gCameraObject->z_velocity;
}

void func_8004D95C(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer) {
    s16 sp26;

    if (racer->unk118 != 0) {
        func_80006AC8(obj);
    }
    if (func_8002341C() && racer->unk1D6 == 10) {
        obj->unk4C->unk14 = 0;
    }
    sp26 = obj->segment.unk18;
    racer->unk1D6 = 10;
    func_80049794(updateRate, updateRateF, obj, racer);
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
            obj->segment.unk18 = sp26 + updateRate;
            func_80061C0C(obj);
        }
    }
}

/**
 * Initialise the basic properties of each racer object. If it's tied to a human player,
 * will also initialise a camera object.
 */
void obj_init_racer(Object *obj, LevelObjectEntry_CharacterFlag *racer) {
    Object_Racer *tempRacer;
    ActivePlayers player;
    s32 i;

    D_8011D53C = 0;
    tempRacer = (struct Object_Racer *) obj->unk64;
    obj->segment.trans.y_rotation = racer->unkC;
    obj->segment.trans.x_rotation = racer->unkA;
    obj->segment.trans.z_rotation = racer->unk8;
    player = racer->unkE;
    tempRacer->unk194 = 0;
    tempRacer->stretch_height = 1.0f;
    tempRacer->stretch_height_cap = 1.0f;
    // Decide which player ID to assign to this object. Human players get a value from 0-3.
    // Computer players will be -1.
    if (player >= PLAYER_ONE && player <= PLAYER_FOUR) {
        if (func_8000E158()) {
            player = 1 - player;
        }
        tempRacer->playerIndex = player;
    } else {
        tempRacer->playerIndex = PLAYER_COMPUTER;
    }
    tempRacer->unk1A0 = obj->segment.trans.y_rotation;
    tempRacer->x_rotation_vel = obj->segment.trans.z_rotation;
    tempRacer->unkC4 = 0.5f;
    if (1);
    tempRacer->unk196 = tempRacer->unk1A0;
    tempRacer->unkD8.x = obj->segment.trans.x_position;
    tempRacer->unkD8.y = obj->segment.trans.y_position + 30.0f;
    tempRacer->unkD8.z = obj->segment.trans.z_position;
    tempRacer->unkE4.x = obj->segment.trans.x_position;
    tempRacer->unkE4.y = obj->segment.trans.y_position + 30.0f;
    tempRacer->unkE4.z = obj->segment.trans.z_position;
    tempRacer->unkF0.x = obj->segment.trans.x_position;
    tempRacer->unkF0.y = obj->segment.trans.y_position + 30.0f;
    tempRacer->unkF0.z = obj->segment.trans.z_position;
    tempRacer->unkFC.x = obj->segment.trans.x_position;
    tempRacer->unkFC.y = obj->segment.trans.y_position + 30.0f;
    tempRacer->unkFC.z = obj->segment.trans.z_position;
    tempRacer->prev_x_position = obj->segment.trans.x_position;
    tempRacer->prev_y_position = obj->segment.trans.y_position;
    tempRacer->prev_z_position = obj->segment.trans.z_position;
    obj->unk4C->x_position = obj->segment.trans.x_position;
    obj->unk4C->y_position = obj->segment.trans.y_position;
    obj->unk4C->z_position = obj->segment.trans.z_position;
    tempRacer->unk1E2 = 3;
    tempRacer->unk1AA = 1;
    tempRacer->unk1AE = 1;
    tempRacer->unk1E7 = tempRacer->playerIndex * 5;
    tempRacer->checkpoint_distance = 1.0f;
    tempRacer->unk1FD = 0;
    tempRacer->unk178 = 0;
    tempRacer->shieldSoundMask = 0;
    tempRacer->unk180 = 0;
    tempRacer->unk218 = 0;
    tempRacer->unk220 = 0;
    tempRacer->unk21C = 0;
    if (tempRacer->playerIndex != -1 && !D_8011D582) {
        func_800665E8(player);
        gCameraObject = func_80069CFC();
        gCameraObject->trans.z_rotation = 0;
        gCameraObject->trans.x_rotation = 0x400;
        gCameraObject->trans.y_rotation = tempRacer->unk196;
        gCameraObject->mode = CAMERA_CAR;
        gCameraObject->unk3C = 0xFF;
        gCameraObject->unk3D = 0xFF;
        gCameraObject->unk3E = 0xFF;
        gCameraObject->unk3F = 0xFF;
        gCameraObject->unk18 = 0.0f;
        update_player_camera(obj, tempRacer, 1.0f);
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
    tempRacer->unk1EE = 0;
    if (!D_8011D582) {
        tempRacer->transparency = 0xFF;
    }
    D_8011D560 = 0;
    D_8011D544 = 300.0f;
    tempRacer->unk1C9 = 6;
    tempRacer->unk1C6 = 100;
    D_8011D580 = 0;

    // This needs to be on one line to match.
    for (i = 0; i < 4; i++) { D_8011D58C[i] = 0; }
    if (1); if (1); // Also critical to match.
    func_80043ECC(0, NULL, 0);
    D_8011D583 = i;
    gStartBoostTime = 0;
    tempRacer->unk20A = 0;
}

/**
 * Main function for handling everything related to the player controlled racer object.
 * Branches off into a different function if the player becomes computer controlled. (Finishing a race)
 */
void update_player_racer(Object* obj, s32 updateRate) {
    s32 tempVar;
    s32 temp_v0_17;
    s32 context;
    Object* tempObj;
    f32 delta;
    f32 waterHeight;
    Object_Racer* tempRacer;
    f32 xTemp;
    f32 yTemp;
    f32 zTemp;
    f32 lastCheckpointDist;
    f32 temp_f12;
    LevelHeader* header;
    unknown8011AECC* temp_v0_16;
    s32 angleVel;
    s32 temp_v1_4;
    s32 i;
    struct LevelObjectEntryCommon newObject;
#ifdef PUPPYPRINT_DEBUG
    u32 first =  osGetTime();
#endif

    gNumViewports = get_viewport_count() + 1;
    gCurrentSurfaceType = SURFACE_DEFAULT;
    gRaceStartTimer = func_8001139C();
    delta = updateRate;
    tempRacer = (Object_Racer *)obj->unk64;
    // Cap all of the velocities on the different axes.
    // Unfortunately, Rareware didn't appear to use a clamp macro here, which would've saved a lot of real estate.
    if (obj->segment.x_velocity > 50.0f) {
        obj->segment.x_velocity = 50.0f;
    }
    if (obj->segment.y_velocity > 50.0f) {
        obj->segment.y_velocity = 50.0f;
    }
    if (obj->segment.z_velocity > 50.0f) {
        obj->segment.z_velocity = 50.0f;
    }
    if (obj->segment.x_velocity < -50.0f) {
        obj->segment.x_velocity = -50.0f;
    }
    if (obj->segment.y_velocity < -50.0f) {
        obj->segment.y_velocity = -50.0f;
    }
    if (obj->segment.z_velocity < -50.0f) {
        obj->segment.z_velocity = -50.0f;
    }
    if (tempRacer->velocity > 50.0f) {
        tempRacer->velocity = 50.0f;
    }
    if (tempRacer->lateral_velocity > 50.0f) {
        tempRacer->lateral_velocity = 50.0f;
    }
    if (tempRacer->velocity < -50.0f) {
        tempRacer->velocity = -50.0f;
    }
    if (tempRacer->lateral_velocity < -50.0f) {
        tempRacer->lateral_velocity = -50.0f;
    }
    if (tempRacer->checkpoint_distance < -1.0f) {
        tempRacer->checkpoint_distance = -1.0f;
    }
    if (tempRacer->checkpoint_distance > 2.0f) {
        tempRacer->checkpoint_distance = 2.0f;
    }
    if (tempRacer->unk1FE == 1) {
        tempRacer->unk1F1 = 0;
    }
    // PAL moves 20% faster.
    if (osTvType == TV_TYPE_PAL) {
        delta *= 1.2f;
    }
    tempRacer->unk1F6 -= updateRate;
    if (tempRacer->unk1F6 < 0) {
        tempRacer->unk1F6 = 0;
    }
    obj->unk74 = 0;
    if (tempRacer->unk201 > 0) {
        tempRacer->unk201 -= updateRate;
    } else {
        tempRacer->unk201 = 0;
    }
    header = get_current_level_header();
    gCurrentCourseHeight = header->course_height;
    tempRacer->throttleReleased = 0;
    if (tempRacer->playerIndex == PLAYER_COMPUTER) {
        func_8005A6F0(obj, tempRacer, updateRate, delta); // AI.
    } else {
        // Print player 1's coordinates to the screen if the debug cheat is enabled.
        if ((gRaceStartTimer == 0) && (tempRacer->playerIndex == PLAYER_ONE)) {
            if (get_filtered_cheats() & CHEAT_PRINT_COORDS) {
                render_printf(&D_800E6280, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
            }
        }
        set_render_printf_background_colour(0, 0, 0, 128);
        if (func_8002341C()) {
            D_8011D586 = 0;
        }
        context = get_render_context();
        if (gRaceStartTimer == 0) {
            if (D_8011D544 > 0.0f) {
                D_8011D544 -= delta;
            } else {
                D_8011D544 = 0.0f;
            }
        } else {
            tempRacer->unk1C6 = get_random_number_from_range(-60, 60) + 120;
        }
        if (tempRacer->unk18C > 0) {
            tempRacer->unk18C -= updateRate;
        } else {
            tempRacer->unk18C = 0;
        }
        gCurrentRacerMiscAssetPtr = (f32*) get_misc_asset(MISC_RACER_WEIGHT);
        gCurrentRacerWeightStat = gCurrentRacerMiscAssetPtr[tempRacer->characterId] * 0.45f;
        if (tempRacer->unk204 > 0) {
            gCurrentRacerWeightStat = -0.02f;
        }
        gCurrentRacerMiscAssetPtr = (f32*) get_misc_asset(MISC_RACER_HANDLING);
        gCurrentRacerHandlingStat = gCurrentRacerMiscAssetPtr[tempRacer->characterId];
        gCurrentRacerMiscAssetPtr = (f32*) get_misc_asset(MISC_ASSET_UNK0B);
        D_8011D574 = gCurrentRacerMiscAssetPtr[tempRacer->characterId];
        if (tempRacer->unk1FE == 3) {
            gCurrentRacerWeightStat *= (f32) tempRacer->unk1FF / 256.0f;
        }
        if (tempRacer->unk1FE == 1) {
            gCurrentRacerWeightStat -= (gCurrentRacerWeightStat * tempRacer->unk1FF) / 128.0f;
            if (tempRacer->unk204 > 0) {
                gCurrentRacerWeightStat = -gCurrentRacerWeightStat;
            }
        }
        if (tempRacer->unk1FE == 2) {
            tempRacer->unk84 += ((cosine_s((tempRacer->unk1FF << 8)) * 4.0f) - tempRacer->unk84) * 0.0625 * delta;
            tempRacer->unk88 += ((sine_s((tempRacer->unk1FF << 8)) * 4.0f) - tempRacer->unk88) * 0.0625 * delta;
        } else {
            tempRacer->unk84 -= tempRacer->unk84 * 0.0625 * delta;
            tempRacer->unk88 -= tempRacer->unk88 * 0.0625 * delta;
        }
        gCurrentRacerMiscAssetPtr = (f32*) get_misc_asset(obj->segment.header->pad5B[1]);
        D_8011D568 = get_misc_asset(obj->segment.header->pad5B[2]);
        
        if (obj->segment.y_velocity < 4.0f && (tempRacer->unk1E2 >= 3 || tempRacer->buoyancy != 0.0f)) {
            tempRacer->unk1F1 = 0;
        }
        xTemp = obj->segment.trans.x_position;
        yTemp = obj->segment.trans.y_position;
        zTemp = obj->segment.trans.z_position;
        if (tempRacer->unk1B2 > 0) {
            tempRacer->unk1B2 -= updateRate;
            if (tempRacer->unk1B2 < 0) {
                tempRacer->unk1B2 = 0;
            }
        }
        func_800665E8(tempRacer->playerIndex);
        gCameraObject = (ObjectCamera *) func_80069CFC();
        tempRacer->unk1E7++;
        gCurrentPlayerIndex = tempRacer->playerIndex;
        if ((tempRacer->raceStatus == STATUS_FINISHED) || (context == 1)) {
            tempRacer->unk1CA = 1;
            tempRacer->playerIndex = PLAYER_COMPUTER;
            tempRacer->unk1C9 = 0;
            if (tempRacer->shieldTimer >= 6) {
                tempRacer->shieldTimer = 5;
            }
        }
        tempVar = tempRacer->playerIndex;
        if (tempRacer->playerIndex != PLAYER_COMPUTER) {
            if (tempRacer->unk108 == 0) {
                if (func_8000E158()) {
                    tempVar = 1 - tempVar;
                }
                //Cap the joystick tilt and write the button inputs to the current buffer.
                gCurrentStickX = clamp_joystick_x_axis(tempVar);
                // Flip the steering for adventure 2.
                if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
                    gCurrentStickX = -gCurrentStickX;
                }
                gCurrentStickY = clamp_joystick_y_axis(tempVar);
                gCurrentRacerInput = get_buttons_held_from_player(tempVar);
                gCurrentButtonsPressed = get_buttons_pressed_from_player(tempVar);
                gCurrentButtonsReleased = get_buttons_released_from_player(tempVar);
            } else {
                racer_enter_door(tempRacer, updateRate);
            }
        } else {
            func_80044170(obj, tempRacer, updateRate);
        }
        //Set the value that decides whether to get an empowered boost.
        if ((gCurrentRacerInput & A_BUTTON) == 0) {
            tempRacer->throttleReleased = 1;
        }
        if (func_80066510() || gRaceStartTimer == 100 || tempRacer->unk1F1 || D_8011D584 || tempRacer->unk148 || tempRacer->unk204 > 0) {
            gCurrentStickX = 0;
            gCurrentStickY = 0;
            gCurrentRacerInput = 0;
            gCurrentButtonsPressed = 0;
            gCurrentButtonsReleased = 0;
            tempRacer->steerAngle = 0;
        }
        if (tempRacer->unk204 > 0) {
            tempRacer->unk204 -= updateRate;
            tempRacer->velocity *= 0.9f;
            obj->segment.x_velocity *= 0.87f;
            if (obj->segment.y_velocity > 2.0f) {
                obj->segment.y_velocity = 2.0f;
            }
            obj->segment.z_velocity *= 0.87f;
        }
        if (tempRacer->unk206 > 0) {
            tempRacer->unk18A = tempRacer->unk206;
            tempRacer->unk206 -= updateRate;
        }
        if (tempRacer->unk18A > 0) {
            tempVar = tempRacer->unk18A & 0xF;
            tempRacer->unk18A -= updateRate;
            if (tempVar < (tempRacer->unk18A & 0xF)) {
                tempRacer->unk1D1 = get_random_number_from_range(-80, 80);
            }
            gCurrentStickX += tempRacer->unk1D1;
        } else {
            tempRacer->unk18A = 0;
        }
        if (tempRacer->unk175) {
            func_80056E2C(obj, tempRacer, updateRate);
        }
        // Zero out input before the race has begun.
        if (gRaceStartTimer && (header->race_type == RACETYPE_DEFAULT ||
            header->race_type == RACETYPE_HORSESHOE_GULCH || header->race_type == RACETYPE_BOSS)) {
            gCurrentStickX = 0;
            gCurrentStickY = 0;
            gCurrentRacerInput = 0;
        }
        // Handle the race timer if it's currently active.
        if (gRaceStartTimer == 0 && header->laps > (tempRacer->unk194)) {
            // Keep it under 10 minutes.
            if (tempRacer->lap_times[tempRacer->unk194] < normalise_time(36000) - updateRate) {
                tempRacer->lap_times[tempRacer->unk194] += updateRate;
            } else {
                tempRacer->lap_times[tempRacer->unk194] = normalise_time(36000);
            }
        }
        // Assign a camera to human players.
        if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
            gCameraObject = (ObjectCamera *) func_80069CFC();
        }
        D_8011D5AE = func_8002B0F4(obj->segment.unk2C.half.lower, obj->segment.trans.x_position, obj->segment.trans.z_position, &D_8011D5B0);
        if (D_8011D5AE) {
            for (i = 0; i < D_8011D5AE; i++) {
                if (D_8011D5B0[i]->unk10 == 0xF) {
                    if (D_8011D5B0[i]->unk0 < gCurrentCourseHeight) {
                        gCurrentCourseHeight = D_8011D5B0[i]->unk0;
                    }
                }
            }
        }
        if (tempRacer->unk1D6 != 1) {
            waterHeight = -10000.0f;
            // So I assume this func exists to find the water height.
            D_8011D504 = func_8002AD08(obj->segment.trans.y_position, &waterHeight, D_8011D4F8);
            if (D_8011D504) {
                if (obj->segment.trans.y_position - 5.0f < waterHeight) {
                    tempRacer->unk1E5 = 5;
                    tempRacer->buoyancy = waterHeight - (obj->segment.trans.y_position - 5.0f);
                } else {
                    tempRacer->buoyancy = 0.0f;
                }
            } else {
                if (tempRacer->unk1E5 > 0) {
                    tempRacer->unk1E5--;
                } else {
                    tempRacer->buoyancy = 0.0f;
                }
            }
            if (tempRacer->unk1E5 > 0 && obj->segment.trans.y_position < waterHeight + 5.0f) {
                obj->unk4C->unk14 |= 0x10;
            } else {
                obj->unk4C->unk14 &= 0xFFEF;
            }
        }
        func_8002ACC8(0);
        switch (tempRacer->unk1D6) {
        case 0:
            func_8004F7F4(updateRate, delta, obj, tempRacer);
            break;
        case 4:
            func_8004CC20(updateRate, delta, obj, tempRacer);
            break;
        case 1:
            func_80046524(updateRate, delta, obj, tempRacer);
            break;
        case 2:
            func_80049794(updateRate, delta, obj, tempRacer);
            break;
        case 3:
        case 10:
            func_8004D95C(updateRate, delta, obj, tempRacer);
            break;
        case 5:
            func_8005C364(updateRate, delta, obj, tempRacer, &gCurrentRacerInput, &gCurrentButtonsPressed, &gRaceStartTimer);
            break;
        case 6:
            func_8005D0D0(updateRate, delta, obj, tempRacer, &gCurrentRacerInput, &gCurrentButtonsPressed, &gRaceStartTimer);
            break;
        case 7:
        case 8:
            func_8005D820(updateRate, delta, obj, tempRacer, &gCurrentRacerInput, &gCurrentStickX, &gRaceStartTimer);
            break;
        case 11:
            func_8005E4C0(updateRate, delta, obj, tempRacer, &gCurrentRacerInput, &gCurrentButtonsPressed, &gRaceStartTimer);
            break;
        case 12:
            func_8005EA90(updateRate, delta, obj, tempRacer, &gCurrentRacerInput, &gCurrentButtonsPressed, &gRaceStartTimer);
            break;
        case 13:
            func_8005F310(updateRate, delta, obj, tempRacer, &gCurrentRacerInput, &gCurrentButtonsPressed, &gRaceStartTimer);
            break;
        }
        if (tempRacer->unk175 == 0) {
            if (tempRacer->unk178) {
                func_8000488C(tempRacer->unk178);
                tempRacer->unk178 = 0;
            }
        }
        temp_v0_17 = header->playerIndex;
        if (temp_v0_17) {
            temp_f12 = -(f32) temp_v0_17;
            if (tempRacer->velocity > temp_v0_17) {
                tempRacer->velocity = temp_v0_17;
            }
            if (tempRacer->velocity < temp_f12) {
                tempRacer->velocity = temp_f12;
            }
        }
        if (context != 1 || func_8000E148()) {
            func_800050D0(obj, gCurrentButtonsPressed, gCurrentRacerInput, updateRate);
        }
        lastCheckpointDist = tempRacer->checkpoint_distance;
        tempVar = func_800185E4(tempRacer->unk192, obj, xTemp, yTemp, zTemp, &tempRacer->checkpoint_distance, &tempRacer->unk1C8);
        if (tempVar == -100) {
            func_8005C270(tempRacer);
        }
        temp_v0_16 = func_8001BA1C(tempRacer->unk192, tempRacer->unk1C8);
        if (tempRacer->playerIndex == PLAYER_COMPUTER && temp_v0_16->unk36[tempRacer->unk1CA] == 5 && tempRacer->unk1E5) {
            tempRacer->unk1C8 = 1;
        }
        if (temp_v0_16->unk36[tempRacer->unk1CA] == 6) {
            tempRacer->unk193 = header->laps + 1;
        }
        if (tempVar == 0) {
            if (tempRacer->playerIndex == PLAYER_COMPUTER && temp_v0_16->unk36[tempRacer->unk1CA] == 2) {
                tempRacer->unk1C8 = 1;
            }
            temp_v0_17 = func_8001BA64();
            tempRacer->unk192++;
            if (tempRacer->unk192 >= temp_v0_17) {
                tempRacer->unk192 = 0;
                if (tempRacer->unk190 > 0) {
                    if (tempRacer->unk193 < 120) {
                        tempRacer->unk193++;
                    }
                }
                if (tempRacer->playerIndex != PLAYER_COMPUTER && tempRacer->unk193 + 1 == header->laps
                    && !D_8011D580 && get_current_level_race_type() == RACETYPE_DEFAULT) {
                    func_800014BC(1.12f);
                    D_8011D580 = 1;
                }
            }
            if (func_8002341C()) {
                if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
                    temp_v0_16 = func_8001BA1C(tempRacer->unk192, tempRacer->unk1C8);
                    if (!tempRacer->unk15C) {
                        newObject.x = 0;
                        newObject.y = 0;
                        newObject.z = 0;
                        newObject.objectID = 0x86;
                        newObject.size = 8;
                        tempRacer->unk15C = spawn_object(&newObject, 1);
                        if (tempRacer->unk15C) {
                            tempRacer->unk15C->segment.unk3C_a.unk3C = 0;
                            tempRacer->unk15C->segment.unk38.half.lower = 128;
                        }
                    }
                    if (tempRacer->unk15C) {
                        tempRacer->unk15C->segment.trans.x_position = temp_v0_16->unk28->segment.trans.x_position;
                        tempRacer->unk15C->segment.trans.y_position = temp_v0_16->unk28->segment.trans.y_position;
                        if (tempRacer->unk1D6 == 0) {
                            tempRacer->unk15C->segment.trans.y_position -= 30.0f;
                        }
                        tempRacer->unk15C->segment.trans.z_position = temp_v0_16->unk28->segment.trans.z_position;
                        tempRacer->unk15C->segment.trans.y_rotation = temp_v0_16->unk28->segment.trans.y_rotation;
                        tempRacer->unk15C->segment.trans.x_rotation = temp_v0_16->unk28->segment.trans.x_rotation;
                        tempRacer->unk15C->segment.unk2C.half.lower = temp_v0_16->unk28->segment.unk2C.half.lower;
                    }
                }
            }
            if (tempRacer->unk190 < (header->laps + 3) * temp_v0_17) {
                tempRacer->unk190++;
            }
            tempRacer->unk1A8 = 10000;
        } else {
            if (tempRacer->playerIndex == PLAYER_COMPUTER && lastCheckpointDist < tempRacer->checkpoint_distance) {
                tempRacer->checkpoint_distance = lastCheckpointDist;
            }
            tempRacer->unk1A8 = tempVar;
        }
        if (func_8002341C()) {
            if (tempRacer->unk15C) {
                tempRacer->unk15C->segment.unk18 += 8 * updateRate;
            }
            if ((tempRacer->unk1BA > 400) || (tempRacer->unk1BA < -400)) {
                func_80022E18(2);
            }
        }
        func_80018CE0(obj, xTemp, yTemp, zTemp, updateRate);
        func_80059208(obj, tempRacer, updateRate);
        if (tempRacer->raceStatus == 1) {
            if (tempRacer->unk1D9 < 60) {
                tempRacer->unk1D9 += updateRate;
            }
        }
        if (tempRacer->unk188 > 0) {
            func_800576E0(obj, tempRacer, tempRacer->unk188);
        }
        tempRacer->playerIndex = gCurrentPlayerIndex;
        update_player_camera(obj, tempRacer, delta);
        D_8011D583 = 0;
        if (tempRacer->unk148) {
            tempRacer->unk148 = NULL;
            tempRacer->velocity = 0.0f;
            tempRacer->lateral_velocity = 0.0f;
        }
        if (tempRacer->stretch_height <= tempRacer->stretch_height_cap) {
            temp_f12 = 0.02f;
        } else {
            temp_f12 = -0.02f;
        }
        tempRacer->stretch_height += (((tempRacer->stretch_height_cap - tempRacer->stretch_height) * 0.125f) + temp_f12) * delta;
        if ((temp_f12 < 0.0f && tempRacer->stretch_height <= tempRacer->stretch_height_cap) ||
            (temp_f12 > 0.0f && tempRacer->stretch_height >= tempRacer->stretch_height_cap)) {
            tempRacer->stretch_height = tempRacer->stretch_height_cap;
            tempRacer->stretch_height_cap = 1.0f;
        }

        tempVar = ((tempRacer->unk16C - tempRacer->unk16A) * updateRate) >> 3;
        if (tempVar > 0x800) {
            tempVar = 0x800;
        }
        if (tempVar < -0x800) {
            tempVar = -0x800;
        }
        angleVel = D_800DCB54;
        if (angleVel) {
            tempRacer->unk16A += angleVel;
        } else {
            tempRacer->unk16A += tempVar;
        }
        if ((gCurrentButtonsPressed & R_TRIG) && tempRacer->unk1EB) {
            tempRacer->unk1EC = 1;
            tempRacer->unk1EB = 0;
        } else if (gCurrentButtonsPressed & R_TRIG) {
            tempRacer->unk1EB = 22;
        }
        if (tempRacer->unk1EB > 0) {
            tempRacer->unk1EB -= updateRate;
        } else {
            tempRacer->unk1EB = 0;
        }
        if (tempRacer->shieldTimer > 0) {
            if (tempRacer->shieldTimer > 60) {
                if (tempRacer->shieldSoundMask) {
                    update_spatial_audio_position(tempRacer->shieldSoundMask, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
                } else if (tempRacer->unk118) {
                    func_80009558(SOUND_SHIELD, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 1, &tempRacer->shieldSoundMask);
                }
            } else if (tempRacer->shieldSoundMask) {
                func_800096F8(tempRacer->shieldSoundMask);
                tempRacer->shieldSoundMask = 0;
            }
            tempRacer->shieldTimer -= updateRate;
            if (tempRacer->shieldTimer <= 0) {
                tempRacer->shieldType = SHIELD_NONE;
            }
        }
        if (tempRacer->unk180) {
            update_spatial_audio_position(tempRacer->unk180, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
        }
        if (func_8000E4D8() && tempRacer->playerIndex == PLAYER_ONE && gRaceStartTimer == 0) {
            func_80059BF0(obj, updateRate);
        }
        if (tempRacer->soundMask) {
            update_spatial_audio_position(tempRacer->soundMask, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
        }
        D_8011D584 = 0;
        if (tempRacer->unk150 && gRaceStartTimer == 0) {
            s8 *yAsset;
            tempRacer->unk150->segment.trans.x_position = obj->segment.trans.x_position;
            yAsset = (s8 *)get_misc_asset(MISC_ASSET_UNK00);
            
            tempRacer->unk150->segment.trans.y_position = obj->segment.trans.y_position + yAsset[tempRacer->characterId];
            tempRacer->unk150->segment.trans.z_position = obj->segment.trans.z_position;
            tempRacer->unk150->segment.trans.scale = obj->segment.unk30 / 265.0f;
            if (obj->segment.unk30 < 1500.0f || get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
                tempObj = tempRacer->unk150;
                tempObj->segment.trans.unk6 |= 0x4000;
            }
            if (tempRacer->unk150->segment.trans.scale < 1.0f) {
                tempRacer->unk150->segment.trans.scale = 1.0f;
            }
            tempRacer->unk150 = NULL;
        }
        tempRacer->unk1FE = -1;
        func_8004F77C(tempRacer);
        if (tempRacer->unk20E) {
            if (tempRacer->unk210 > updateRate) {
                tempRacer->unk210 -= updateRate;
            } else {
                tempRacer->unk210 = 0;
                if (tempRacer->playerIndex == PLAYER_COMPUTER) {
                    func_80009558(tempRacer->unk20E, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
                } else {
                    play_sound_spatial(tempRacer->unk20E, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, NULL);
                }
                tempRacer->unk20E = 0;
            }
        }
        if (header->race_type & RACETYPE_CHALLENGE && header->race_type != RACETYPE_CHALLENGE_EGGS) {
            tempRacer->unk212 = func_8001C418(obj->segment.trans.y_position);
        } else {
            tempRacer->unk212 = 0;
        }
        if (tempRacer->unk194 < tempRacer->unk193) {
            tempRacer->unk194 = tempRacer->unk193;
        }
    }
#ifdef PUPPYPRINT_DEBUG
    profiler_add(gPuppyTimers.racerTime, osGetTime() - first);
#endif
}

void func_8004F77C(Object_Racer *racer) {
    s32 temp;

    racer->unk20A &= ~0x80;
    if ((gCurrentRacerInput & B_BUTTON)) {
        racer->unk20A |= 0x80;
    }

    temp = racer->unk20A & 0xF;
    if ((racer->unk20A & 0xC0)) {
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

    racer->unk20A = (racer->unk20A & 0xFFF0) | temp;
}

GLOBAL_ASM("asm/non_matchings/racer/func_8004F7F4.s")

void func_80050754(Object *obj, Object_Racer *racer, f32 divisor) {
    f32 xDiff;
    f32 yDiff;
    f32 zDiff;

    obj->segment.unk3B = 0;
    obj->segment.unk18 = 40;
    xDiff = racer->unk148->segment.trans.x_position - obj->segment.trans.x_position;
    yDiff = racer->unk148->segment.trans.y_position - obj->segment.trans.y_position;
    zDiff = racer->unk148->segment.trans.z_position - obj->segment.trans.z_position;
    func_80011570(obj, xDiff, yDiff, zDiff);
    obj->segment.trans.y_rotation = racer->unk148->segment.trans.y_rotation;
    obj->segment.trans.x_rotation = racer->unk148->segment.trans.x_rotation;
    obj->segment.trans.z_rotation = racer->unk148->segment.trans.z_rotation;
    racer->x_rotation_vel = obj->segment.trans.z_rotation;
    racer->unk1A0 = obj->segment.trans.y_rotation;
    obj->segment.x_velocity = xDiff / divisor;
    obj->segment.y_velocity = yDiff / divisor;
    obj->segment.z_velocity = zDiff / divisor;
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
    f32 xDiff;
    f32 zDiff;
    s32 ret = FALSE;

    xDiff = obj2->segment.trans.x_position - obj1->segment.trans.x_position;
    zDiff = obj2->segment.trans.z_position - obj1->segment.trans.z_position;
    if ((xDiff * xDiff) + (zDiff * zDiff) < distance) {
        rotation = (arctan2_f(xDiff, zDiff) - (obj1->segment.trans.y_rotation & 0xFFFF)) + 0x8000;
        WRAP(rotation, -0x8000, 0x8000);
        CLAMP(rotation, -0x3000, 0x3000);
        racer->unk16C = rotation;
        if ((racer->unk1E7 & 0x3F) < 0x1F) {
            racer->unk16C = 0;
        }
        racer = (struct Object_Racer *) obj2->unk64;
        rotation = arctan2_f(xDiff, zDiff) - (obj1->segment.trans.y_rotation & 0xFFFF);
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

void func_8005250C(Object* obj, Object_Racer* racer, s32 updateRate) {
    s8 *balloonAsset;
    s16 angleDelta;
    s32 phi_t1;
    s32 angleVel;
    s32 newAngle;
    s32 actionStatus;

    angleVel = 0;
    if (racer->balloon_quantity > 0) {
        balloonAsset = (s8 *) get_misc_asset(MISC_ASSET_UNK0C);
        
        angleVel = balloonAsset[(racer->balloon_type * 10) + (racer->balloon_level * 2)];
    }
    if (gCurrentButtonsPressed & Z_TRIG && angleVel != 4 && angleVel != 8) {
        racer->unk1F2 = 5;
    }
    if (racer->boostTimer) {
        racer->unk1F3 |= 4;
    }
    if (racer->unk1F3 & 8) {
        if (gNumViewports < 3) {
            if (gCurrentPlayerIndex >= PLAYER_ONE) {
                obj->unk74 |= 0x100000;
            } else {
                obj->unk74 |= 0x80000;
            }
        }
        racer->unk1F2 = 4;
    }
    if (gRaceStartTimer) {
        racer->unk1F3 = 0;
        racer->unk1F2 = 0;
    }
    if (racer->raceStatus == STATUS_FINISHED) {
        racer->unk1F2 = 0;
        racer->unk1F3 = 0;
    }
    switch (racer->unk1F2) {
    case 0: // Sliding, creating tyre marks
        angleVel = (s32) (((-racer->y_rotation_vel) >> 8) / gCurrentRacerHandlingStat);
        angleVel = 40 - angleVel;
        if (angleVel < 0) {
            angleVel = 0;
        }
        if (angleVel > 73) {
            angleVel = 73;
        }
        newAngle = angleVel - obj->segment.unk18;
        angleVel = 0;
        if (newAngle > 0) {
            angleVel = updateRate * 3;
            if (newAngle < angleVel) {
                angleVel = newAngle;
            }
        }
        if (newAngle < 0) {
            angleVel = updateRate * -3;
            if (angleVel < newAngle) {
                angleVel = newAngle;
            }
        }
        obj->segment.unk18 += angleVel;
        obj->segment.unk3B = 0;
        if (angleVel);
        if (racer->unk1F3 & 4) {
            racer->unk1F2 = 3;
            racer->unk1F3 &= 0xFFFB;
        }
        if (racer->velocity > 0.0f && gCurrentRacerInput & B_BUTTON) {
            racer->unk1F2 = 6;
        }
        break;
    case 3: // Boost
        actionStatus = 2;
        if (racer->unk1F3 & 4) {
            actionStatus = 6;
        }
        func_80052988(obj, racer, 2, 0, 32, 4, actionStatus, updateRate);
        racer->unk1F3 &= 0xFFFB;
        break;
    case 4: // Crash
        func_80052988(obj, racer, 3, 0, 32, 2, 0, updateRate);
        racer->unk1F3 &= 0xFFF7;
        break;
    case 5: // Horn
        actionStatus = 2;
        if (gCurrentRacerInput & Z_TRIG) {
            actionStatus = 6;
        }
        func_80052988(obj, racer, 4, 0, 48, 4, actionStatus, updateRate);
        break;
    case 6:
        actionStatus = 3;
        if (racer->velocity > 0.0f && gCurrentRacerInput & B_BUTTON) {
            actionStatus = 7; // Reverse
        }
        func_80052988(obj, racer, 1, 0, 80, 3, actionStatus, updateRate);
        break;
    case 7:
        func_80052988(obj, racer, 5, 0, 96, 4, 0, updateRate);
        if (racer->unk1F2 == 0) {
            func_80052988(obj, racer, 5, 0, 96, 4, 0, updateRate);
        }
        break;
    }
}

void func_80052988(Object *obj, Object_Racer *racer, s32 action, s32 arg3, s32 duration, s32 arg5, s32 arg6, s32 arg7) {
    arg5 *= arg7;

    if ((gCurrentPlayerIndex == -1) && (action >= 3)) {
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

/**
 * If the spinout timer is above zero, remove steering control and have them rotate until
 * the timer runs out.
 */
void racer_spinout_car(Object* obj, Object_Racer* racer, s32 updateRate, f32 updateRateF) {
    s32 angleVel;

    racer->velocity *= 0.97; //@Delta: Reduces 3% of speed per frame, not accounting for game speed.
    racer->lateral_velocity = 0.0f;
    if (racer->raceStatus == STATUS_RACING) {
        func_80072348(racer->playerIndex, 0);
    }
    angleVel = racer->y_rotation_vel;
    if (gCurrentPlayerIndex >= 0) {
        if (gNumViewports < 3) {
            obj->unk74 |= 0x4FC00;
            goto skip;
        }
        if (racer->wheel_surfaces[2] < SURFACE_NONE) {
            obj->unk74 |= 1 << (racer->wheel_surfaces[2] * 2);
        }
        if (racer->wheel_surfaces[3] < SURFACE_NONE) {
            obj->unk74 |= 2 << (racer->wheel_surfaces[3] * 2);
        }
    }
    skip:
    if (racer->spinout_timer > 0) {
        racer->y_rotation_vel += updateRate * 0x500;
        if (racer->y_rotation_vel > 0 && angleVel < 0) {
            racer->spinout_timer--; //@Delta
            if (gCurrentStickX > 50 && racer->spinout_timer == 1) {
                racer->spinout_timer = 0;
            }
        }
    } else if (racer->spinout_timer < 0) {
        racer->y_rotation_vel -= updateRate * 0x500;
        if (racer->y_rotation_vel < 0 && angleVel > 0) {
            racer->spinout_timer++; //@Delta
            if (gCurrentStickX < -50 && racer->spinout_timer == -1) {
                racer->spinout_timer = 0;
            }
        }
    }
    gCurrentCarSteerVel = racer->y_rotation_vel;
    obj->segment.y_velocity -= gCurrentRacerWeightStat * updateRateF;
    gCurrentStickX = 0;
    racer->steerAngle = 0;
}

void func_80052D7C(Object* obj, Object_Racer* racer, s32 updateRate, f32 updateRateF) {
    s32 steerAngle;
    s32 yStick;
    s32 angle;
    s8 sp33;
    f32 vel;
    s32 temp;

    sp33 = 0;
    if (racer->unk1FE == 1 && racer->playerIndex == PLAYER_COMPUTER) {
        gCurrentStickY = 60;
    }
    if (racer->unk1F0 != 0) {
        if (racer->playerIndex != PLAYER_COMPUTER) {
            steerAngle = racer->steerAngle;
        } else {
            steerAngle = gCurrentStickX;
        }
        racer->unk1A0 -= (u16) ((steerAngle * 6 * updateRate) >> 1);
        angle = -(u16) racer->x_rotation_vel;
        if (angle > 0x8000) {
            angle -= 0xFFFF;
        }
        if (angle < -0x8000) {
            angle += 0xFFFF;
        }
        racer->x_rotation_vel += (angle >> 3);
    }
    if (racer->unk18) {
        func_8000488C(racer->unk18);
    }
    if (racer->unk10) {
        func_8000488C(racer->unk10);
    }
    if (racer->unk14) {
        func_8000488C(racer->unk14);
    }
    if (racer->unk1FE == 1 || racer->unk1FE == 3) {
        racer->unk1E8 = racer->steerAngle;
    }
    if (racer->buoyancy != 0.0f) {
        if (obj->segment.y_velocity > 2.0f) {
            obj->segment.y_velocity = 2.0f;
        }
        if (obj->segment.y_velocity < -2.0f) {
            obj->segment.y_velocity = -2.0f;
        }
        racer->unk1E8 = racer->steerAngle;
        if (gCurrentRacerInput & A_BUTTON) {
            racer->velocity -= 0.5f;
        }
        if (gCurrentRacerInput & B_BUTTON && gCurrentStickY < -25) {
            racer->velocity += 0.5f;
        }
        sp33 = 1;
        racer->lateral_velocity *= 0.87;
        racer->velocity *= 0.87;
        obj->segment.y_velocity *= 0.9f;
        func_800494E0(obj, racer, D_8011D4F8, D_8011D504, updateRate, gCurrentStickX, 6.0f);
    }
    if (racer->playerIndex == -1) {
        racer->unk1E8 = racer->steerAngle;
    }
    if (racer->boostTimer > 0) {
        racer->boostTimer -= updateRate;
    } else {
        racer->boostTimer = 0;
    }
    angle = racer->unk1E8 * 6;
    if (racer->velocity > 0.3f){
        angle = -racer->steerAngle;
        angle *= 6;
    }
    racer->unk1A0 -= angle & 0xFFFF;
    gCurrentCarSteerVel = racer->unk110;
    if (racer->boostTimer) {
        if (racer->velocity > -20.0f) {
            racer->velocity -= 1.6f;
        }
    }
    yStick = gCurrentStickY;
    if ((yStick < 50) && (yStick > (-50))) {
        yStick = 0;
    }
    obj->segment.y_velocity -= (obj->segment.y_velocity * 0.025) * updateRateF;
    vel = gCurrentRacerWeightStat;
    if (racer->unk1F1 || racer->unk1F0) {
        vel = 0.45f;
        racer->y_rotation_offset += 0x500 * updateRate;
        racer->x_rotation_offset += 0x600 * updateRate;
    }
    if (racer->unk1FE == 1 || racer->unk1FE == 3) {
        racer->lateral_velocity *= 0.97;
        racer->velocity *= 0.97;
        if (yStick > 50) {
            racer->velocity -= 0.2f;
        }
        if (yStick < -50) {
            racer->velocity += 0.2f;
        }
        sp33 = 1;
    }
    if (sp33) {
        obj->unk74 = 0;
        racer->drift_direction = 0;
        racer->unk10C -= (racer->unk10C * updateRate) >> 4;
        gCurrentCarSteerVel = 0;
        handle_car_steering(racer);
    } else {
        if (yStick > 50) {
            vel *= 1.33;
        }
        if (yStick < -50) {
            vel *= 0.53;
        }
    }
    if (racer->boostTimer) {
        vel *= 0.5f;
    }
    yStick = -yStick;
    yStick *= 64;
    yStick = (u16) yStick;
    angle = yStick - ((u16) obj->segment.trans.x_rotation);
    angle = angle > 0x8000 ? angle - 0xFFFF : angle;
    angle = angle < -0x8000 ? angle + 0xFFFF : angle;
    obj->segment.trans.x_rotation += (angle >> 3);
    obj->segment.y_velocity -= vel * updateRateF;
    if (racer->buoyancy == 0.0f) {
        steerAngle = -obj->segment.y_velocity * 20.0f;
        if (steerAngle < 50) {
            steerAngle = 50;
        }
        if (steerAngle > 127) {
            steerAngle = 127;
        }
        racer->unk1E0 = steerAngle;
    }
    obj->unk74 = 0;
}

/**
 * Handle the steering input of all cars.
 * It takes the speed of the car, creating a curve for the rotational velocity to scale with.
 */
void handle_car_steering(Object_Racer *racer) {
    s32 velScale;
    f32 vel = racer->velocity;

    // Stay positive :)
    if (vel < 0.0f) {
        vel = -vel;
    }
    if (vel > 1.8f){
        vel = 1.8f;
    }
    vel -= 0.2f;
    if (vel < 0.0f) {
        vel = 0.0f;
    }
    if (racer->drift_direction != 0) {
        velScale = vel * 68.0f;
    } else {
        velScale = vel * 58.0f;
    }
    // Set the steering velocity based on the car's steering value, scaled with the temp forward velocity value.
    gCurrentCarSteerVel -= (racer->steerAngle * velScale);
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
    if (racer->throttle > 0.0f) {
        racer->throttle -= 0.1f;
    }

    if (gCurrentRacerInput & A_BUTTON) {
        racer->throttle = 1.0f;
    }

    if (gCurrentRacerInput & B_BUTTON) {
        if (racer->brake < 1.0f) {
            racer->brake += 0.2f;
        }
    } else {
        //! @bug Will cause a negative brake value resulting in higher velocity
        if (racer->brake > 0.05) {
            racer->brake -= 0.1f;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_80053750.s")

/**
 * Initialise some states when a racer is attacked or runs into something.
 * While the majority of the respondent behaviour takes place elsewhere, the squish behaviour
 * happens here.
 */
void racer_attack_handler(Object* obj, Object_Racer* racer, s32 updateRate) {
    s8 bananas;

    if (racer->playerIndex == PLAYER_COMPUTER) {
        bananas = 0;
    } else {
        bananas = racer->bananas;
    }
    if (racer->squish_timer > 0) {
        racer->squish_timer -= updateRate;
        racer->throttle = 0.0f;
        racer->stretch_height_cap = 0.1f;
        if (racer->squish_timer <= 0 && racer->playerIndex >= 0) {
            racer_play_sound(obj, SOUND_PLOP2);
        }
    } else {
        racer->squish_timer = 0;
    }
    if (racer->attackType == 0 || racer->shieldTimer > 0) {
        racer->attackType = 0;
    } else {
        if ((racer->squish_timer == 0) || racer->attackType != 4) {
            if ((racer->attackType != 2) && (racer->attackType != 4)) {
                func_800576E0(obj, racer, 2);
            }
            racer->unk18C = 360;
            if (racer->unk1C9 == 8) {
                racer->unk1C9 = 0;
            }
            if (racer->unk1D6 < 5) {
                play_random_character_voice(obj, SOUND_VOICE_CHARACTER_NEGATIVE, 8, 129);
                switch (racer->attackType) {
                // Getting hit by a rocket, or running into a landmine.
                case ATTACK_EXPLOSION:
                    racer->unk1F1 = 1;
                    if (bananas == 0) {
                        racer->velocity = 0.0f;
                        obj->segment.y_velocity += 10.5f;
                    } else {
                        racer->velocity /= 4;
                        obj->segment.y_velocity += 8.5f;
                    }
                    break;
                // Running into an oil slick.
                case ATTACK_SPIN:
                    racer->spinout_timer = 2;
                    racer->y_rotation_vel = 0x1002;
                    racer_play_sound(obj, SOUND_TYRE_SCREECH);
                    break;
                // Crushed by something big, like a snowball.
                case ATTACK_SQUISHED:
                    racer->squish_timer = 0x3C;
                    break;
                // Running into a bubble trap.
                case ATTACK_BUBBLE:
                    racer->unk204 = 0x78;
                    racer->velocity *= 0.5f;
                    break;
                // This goes unused.
                case ATTACK_FLUNG:
                    racer->unk1F1 = 1;
                    racer->velocity = 0.0f;
                    obj->segment.y_velocity += 20.5f;
                    racer_play_sound(obj, SOUND_WHEE);
                    break;
                }
                racer->attackType = 0;
            }
        }
    }
}

void func_80054110(Object *obj, Object_Racer *racer, s32 updateRate, f32 updateRateF) {
    f32 tempVel;
    f32 xVel;
    f32 zVel;
    f32 yVel;
    f32 hVel;
    f32 xTemp;
    f32 yTemp;
    f32 zTemp;
    Matrix mtx;
    LevelHeader *header;
    s32 angle;
    s32 tempAngle;

    xTemp = obj->segment.trans.x_position;
    yTemp = obj->segment.trans.y_position;
    zTemp = obj->segment.trans.z_position;
    gCurrentCarSteerVel = 0;
    D_8011D558 = 0;
    handle_base_steering(racer, 0, updateRateF);
    handle_car_velocity_control(racer);
    func_800575EC(obj, racer);
    func_80055EC0(obj, racer, updateRate);
    racer_attack_handler(obj, racer, updateRate);
    if (racer->spinout_timer) {
        racer_spinout_car(obj, racer, updateRate, updateRateF); // Sbinalla
    } else if (racer->unk1E2 > 0) {
        func_8005492C(obj, racer, updateRate, updateRateF);
    } else {
        func_80052D7C(obj, racer, updateRate, updateRateF);
    }
    apply_vehicle_rotation_offset(racer, updateRate, 0, 0, 0);
    header = get_current_level_header();
    if ((racer->buoyancy != 0.0f && header->unk2) || gCurrentSurfaceType == SURFACE_FROZEN_WATER) {
        if (racer->unk1F0) {
            racer->checkpoint_distance -= 0.3f;
        } else {
            racer->checkpoint_distance -= 0.1f;
        }
        func_80059080(obj, racer, &xVel, &yVel, &zVel);
        if (racer->unk1F0) {
            racer->checkpoint_distance += 0.3f;
        } else {
            racer->checkpoint_distance += 0.1f;
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
    tempAngle = ((-racer->y_rotation_vel >> 8) / gCurrentRacerHandlingStat);
    tempAngle = 40 - tempAngle;
    if (tempAngle < 0) {
        tempAngle = 0;
    }
    if (tempAngle > 73) {
        tempAngle = 73;
    }
    obj->segment.unk18 = tempAngle;
    func_8005234C(racer);
    angle = gCurrentCarSteerVel - (u16) racer->y_rotation_vel;
    WRAP(angle, -0x8000, 0x8000);
    angle >>= 2;
    CLAMP(angle, -0x2EE, 0x2EE);
    racer->y_rotation_vel += (angle * updateRate);
    obj->segment.trans.y_rotation = racer->unk1A0 + racer->y_rotation_vel;
    racer->z_rotation_vel += ((D_8011D558 - racer->z_rotation_vel) * updateRate) >> 4;
    obj->segment.trans.z_rotation = racer->x_rotation_vel + racer->z_rotation_vel;
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
        func_80011570(obj, xVel * updateRateF, obj->segment.y_velocity * updateRateF, zVel * updateRateF);
    } else {
        func_80050754(obj, racer, updateRateF);
    }
    if (gCurrentPlayerIndex == -1 && !func_80023568()) {
            func_80055A84(obj, racer, updateRate);
    } else {
        func_80054FD0(obj, racer, updateRate);
    }
    if (!racer->unk201) {
        obj->unk74 = 0;
    } else if (racer->unk1D6 < 5) {
        func_800AF714(obj, updateRate);
    }
    func_80053750(obj, racer, updateRateF);
    tempVel = 1.0f / updateRateF;
    xVel = (((obj->segment.trans.x_position - xTemp) - D_8011D548) * tempVel) - racer->unk84;
    obj->segment.y_velocity = (obj->segment.trans.y_position - yTemp) * tempVel;
    zVel = (((obj->segment.trans.z_position - zTemp) - D_8011D54C) * tempVel) - racer->unk88;
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
        if (tempVel > 0.5f){
            racer->velocity -= tempVel - 0.5f;
        }
        if (tempVel < -0.5f){
            racer->velocity -= tempVel + 0.5f;
        }
        tempVel = racer->lateral_velocity - hVel;
        if (tempVel && tempVel) {}
        if (tempVel > 0.5f){
            racer->lateral_velocity -= tempVel - 0.5f;
        }
        if (tempVel < -0.5f){
            racer->lateral_velocity -= tempVel + 0.5f;
        }
    }
}

void func_8005492C(Object* obj, Object_Racer* racer, s32 updateRate, f32 updateRateF) {
    s32 xStick;
    s32 stickMultiplier;
    s32 surfaceType;
    s32 sp38;
    f32 temp_f0_2;
    f32 velSquare;
    f32 pad;
    f32 traction;
    f32 forwardVel;
    f32 weight;
    f32 vel;
    f32 multiplier;
    s32 rawStick;
    s32 velocityS;
    s32 temp;
    u16 temp2;

    velSquare = racer->velocity * racer->velocity;
    racer->unk84 = 0.0f;
    racer->unk88 = 0.0f;
    if (racer->velocity < 0.0f) {
        velSquare = -velSquare;
    }
    sp38 = 0;
    multiplier = handle_racer_top_speed(obj, racer);
    if (racer->y_rotation_vel > 0x1C00 || racer->y_rotation_vel < -0x1C00) {
        sp38 = 1;
    }
    rawStick = gCurrentStickX;
    stickMultiplier = 6;
    if (gCurrentRacerInput & B_BUTTON) {
        stickMultiplier = 12;
    }
    if (gCurrentRacerInput & B_BUTTON && racer->drift_direction != 0) {
        stickMultiplier = 18;
    }
    xStick = 0;
    if (racer->velocity < -0.3f){
        xStick = rawStick * stickMultiplier;
    }
    if (racer->velocity > 0.3f){
        xStick = -rawStick * stickMultiplier;
    }
    xStick *= updateRate;
    temp = (s32) ((xStick >> 1) * gCurrentRacerHandlingStat); 
    temp2 = temp;
    racer->unk1A0 -= temp2;
    handle_car_steering(racer);
    racer->lateral_velocity *= 0.9f;
    surfaceType = SURFACE_DEFAULT;
    traction = 0.0f;
    if (racer->wheel_surfaces[0] != SURFACE_NONE) {
        traction += gSurfaceTractionTable[racer->wheel_surfaces[0]];
        if (racer->wheel_surfaces[0] > SURFACE_DEFAULT) {
            surfaceType = racer->wheel_surfaces[0];
        }
    }
    if (racer->buoyancy != 0.0f) {
        traction = 0.02f;
    }
    gCurrentSurfaceType = surfaceType;
    racer->drift_direction = 0;
    racer->unk10C = 0;
    if (surfaceType == 4) {
        multiplier = 0.25f;
        racer->lateral_velocity = 0.0f;
    }
    if (racer->boostTimer == 0 && surfaceType == SURFACE_UNK03) {
        racer->boostTimer = normalise_time(45);
        racer->boostType = 3;
    }
    racer->velocity -= velSquare * traction;
    if (sp38) {
        if (racer->unk1EE < 16) {
            racer->unk1EE++;
        }
    } else {
        racer->unk1EE = 0;
    }
    if (get_viewport_count() < 2 && sp38 && racer->velocity < -2.0f) {
        if (racer->wheel_surfaces[2] < 0xFF) {
            obj->unk74 |= 1 << (racer->wheel_surfaces[2] * 2);
        }
        if (racer->wheel_surfaces[3] < 0xFF) {
            obj->unk74 |= 2 << (racer->wheel_surfaces[3] * 2);
        }
    }
    vel = racer->velocity;
    if (vel < 0.0f) {
        vel = -vel;
    }
    if (vel > 12.0f) {
        vel = 12.0f;
    }
    velocityS = (s32) vel;
    temp_f0_2 = vel - (f32) velocityS;
    vel = (gCurrentRacerMiscAssetPtr[velocityS+1] * temp_f0_2) + (gCurrentRacerMiscAssetPtr[velocityS] * (1.0f - temp_f0_2));
    vel *= 1.7f;
    vel *= multiplier;
    if (racer->boostTimer > 0) {
        if (gRaceStartTimer == 0) {
            racer->throttle = 1.0f;
            if (vel != 0.0f) {
                vel = 2.0f;
            }
            racer->boostTimer -= updateRate;
        }
    } else {
        racer->boostTimer = 0;
    }
    // If basically at a standstill, then allow reversing.
    if (racer->velocity > -2.0f && racer->velocity < 3.0f) {
        f32 reverseVel = (3.0f - racer->velocity) * 0.15;
        if (gCurrentStickY < -25 && !(gCurrentRacerInput & A_BUTTON) && gCurrentRacerInput & B_BUTTON) {
            racer->brake = 0.0f;
            racer->velocity += reverseVel;
        }
    }
	forwardVel = (vel * racer->brake) * 0.32;
    racer->velocity -= vel * racer->throttle;
    if (racer->velocity > -0.04 && racer->velocity < 0.04) {
        racer->velocity = 0.0f;
    }
    if (racer->velocity < 0.0f) {
        racer->velocity += forwardVel;
        if (racer->velocity > 0.0f) {
            racer->velocity = 0.0f;
        }
    } else {
        racer->velocity -= forwardVel;
        if (racer->velocity < 0.0f) {
            racer->velocity = 0.0f;
        }
    }

    // Heavier characters will fall faster.
    weight = gCurrentRacerWeightStat;
    if (racer->buoyancy != 0.0f) {
        weight *= 0.5f;
    }
    if (racer->brake < 0.9f && gRaceStartTimer == 0) {
        racer->velocity += weight * (racer->pitch / 4) * updateRateF;
    }
    obj->segment.y_velocity -= weight * updateRateF;
}


GLOBAL_ASM("asm/non_matchings/racer/func_80054FD0.s")

void func_80055A84(Object *obj, Object_Racer *racer, s32 updateRate) {
    f32 angleZ;
    f32 distance;
    s32 sp74;
    s32 flags;
    s32 temp_v1_2;
    f32 xTemp;
    f32 yTemp;
    f32 zTemp;
    s32 xRot;
    f32 angleX;
    f32 *temp_v0;
    f32 tempPos[3];
    s32 i;
    f32 sp40;
    s8 surface;
    s8 shouldSquish;

    if (obj->segment.trans.y_position > gCurrentCourseHeight) {
        obj->segment.trans.y_position = gCurrentCourseHeight;
    }
    temp_v0 =(f32 *) get_misc_asset(MISC_ASSET_UNK38);
    surface = -1;
    sp40 = temp_v0[racer->unk1D7];
    tempPos[0] = obj->segment.trans.x_position;
    tempPos[1] = obj->segment.trans.y_position;
    tempPos[2] = obj->segment.trans.z_position;
    D_8011D548 = 0.0f;
    D_8011D54C = 0.0f;
    sp74 = 0;
    flags = 0;
    if (racer->playerIndex != PLAYER_COMPUTER || racer->unk1D7 < 5) {
        flags = func_80017248(obj, 1, &sp74, &racer->unkD8, tempPos, &sp40, &surface);
    }
    if (flags & 0x80) {
        D_8011D548 = tempPos[0] - obj->segment.trans.x_position;
        D_8011D54C = tempPos[2] - obj->segment.trans.z_position;
        flags &= ~0x80;
    }
    shouldSquish = 0;
    if (flags && tempPos[1] < obj->segment.trans.y_position - 4.0f) {
        shouldSquish = 1;
    }
    func_80031130(1, &racer->unkD8.x, tempPos, racer->unk1D6);
    sp74 = 0;
    racer->unk1E3 = func_80031600(&racer->unkD8.x, tempPos, &sp40, &surface, 1, &sp74);
    racer->unk1E4 = flags;
    racer->unk1E3 |= flags;
    racer->unk1E2 = 0;
    if (racer->unk1E3) {
        racer->unk1E3 = 15;
        racer->unk1E2 = 4;
    }
    if (shouldSquish && sp74) {
        if (racer->squish_timer == 0) {
            racer->attackType = ATTACK_SQUISHED;
        } else {
            racer->squish_timer = 60;
        }
    }
    for (i = 0; i < 3; i++) {
        racer->unkD8.f[i] = tempPos[i];
    }
    racer->wheel_surfaces[0] = surface;
    i = 1;
    racer->wheel_surfaces[1] = surface;
    racer->wheel_surfaces[2] = surface;
    racer->wheel_surfaces[3] = surface;
    obj->segment.trans.x_position = racer->unkD8.x;
    obj->segment.trans.y_position = racer->unkD8.y;
    obj->segment.trans.z_position = racer->unkD8.z;
    if (racer->unk1E2) {
        func_8002ACD4(&xTemp, &yTemp, &zTemp);
        angleX = cosine_s(-obj->segment.trans.y_rotation);
        angleZ = sine_s(-obj->segment.trans.y_rotation);
        distance = (xTemp * angleZ) + (zTemp * angleX);
        zTemp = (xTemp * angleX) - (zTemp * angleZ);
        temp_v1_2 = -(s16)(u16)arctan2_f(distance, yTemp);
        if (temp_v1_2 < 0x2000 && temp_v1_2 > -0x2000) {
            racer->x_rotation_vel = temp_v1_2;
        }
        xRot = -(s16)(u16)arctan2_f(zTemp, yTemp);
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
        CLAMP(racer->x_rotation_vel, -0x3400, 0x3400);
        CLAMP(obj->segment.trans.x_rotation, -0x3400, 0x3400);
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_80055EC0.s")

void play_char_horn_sound(Object *obj, Object_Racer *racer) {
    if (get_filtered_cheats() & CHEAT_HORN_CHEAT) {
        // Play character voice instead of horn.
        play_random_character_voice(obj, SOUND_VOICE_CHARACTER_POSITIVE, 8, 130);
    } else {
        // Play character's horn sound
        racer_play_sound(obj, racer->characterId + SOUND_HORN_CHARACTER);
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_8005698C.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80056E2C.s")

/**
 * Play a spatial sound, emitting from the position of the racer object.
 */
void racer_play_sound(Object *obj, s32 soundID) {
    Object_Racer *racer = &obj->unk64->racer;
    if (gCurrentPlayerIndex != -1 && racer->unk108 == 0) {
        play_sound_spatial(soundID, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, NULL);
    }
}

void func_800570A4(Object *obj, s32 arg1, s32 arg2) {
    Object_Racer *temp = &obj->unk64->racer;
    temp->unk20E = arg1;
    temp->unk210 = arg2;
}

/**
 * Play a random character voice clip from the given offset.
 * It uses SOUND_VOICE_CHARACTER_POSITIVE and SOUND_VOICE_CHARACTER_NEGATIVE for
 * acceptable offsets. Range will always be 8, because that's how many ID's for each
 * there are.
 */
void play_random_character_voice(Object *obj, s32 soundID, s32 range, s32 arg3) {
    s32 soundIndex;
    Object_64 *tempRacer;

    tempRacer = obj->unk64;
    if (tempRacer->racer.unk108 == 0 && ((!(arg3 & 0x80)) || gCurrentPlayerIndex != -1)) {
        if (arg3 == 2) {
            if ((tempRacer->racer.soundMask != 0) && (soundID != tempRacer->racer.unk2A)) {
                func_800096F8(tempRacer->racer.soundMask);
                tempRacer->racer.soundMask = 0;
            }
        }
        if (tempRacer->racer.soundMask == 0 && (arg3 != 3 || get_random_number_from_range(0, 1))) {
            tempRacer->racer.unk2A = soundID;
            soundID += tempRacer->racer.characterId;
            soundIndex = (get_random_number_from_range(0, range - 1) * 12) + soundID;
            if (range - 1 > 0) {
                while (soundIndex == tempRacer->racer.lastSoundID) {
                    soundIndex = (get_random_number_from_range(0, range - 1) * 12) + soundID;
                }
            }
            func_80009558(soundIndex, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, &tempRacer->racer.soundMask);
            tempRacer->racer.lastSoundID = soundIndex;
        }
    }
}

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
        if (gCurrentButtonsPressed & A_BUTTON) {
            if (timer < 0 && timer3 >= 0) {
                timer = 0;
            }
            // Keep the timer positive.
            if (timer < 0) {
                timer = -timer;
            }
            if ((gCurrentRacerInput & Z_TRIG)) {
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
    if (racer->boostTimer && !gRaceStartTimer && timer3 && racer->raceStatus == STATUS_RACING) {
         func_80072348(racer->playerIndex, 6);
    }
    if ((gRaceStartTimer < 80) && gCurrentButtonsPressed & A_BUTTON) {
        racer->startInput = 1;
    }
    if (!gRaceStartTimer) {
        if (racer->boost_sound & BOOST_RACE_START) {
            racer->boost_sound &= ~BOOST_RACE_START;
            play_random_character_voice(obj, SOUND_VOICE_CHARACTER_POSITIVE, 8, 130);
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
        if (bananas > 10.0f) {
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

/**
 * Generate the steer velocity by taking the current steer velocity and getting the difference between the stick tilt.
 * Get the velocity from a fraction of the difference.
 */
void handle_base_steering(Object_Racer *racer, UNUSED s32 updateRate, f32 updateRateF) {
    s32 steering, turnVel;

    steering = gCurrentStickX - racer->steerAngle;
    turnVel = (steering * updateRateF) * 0.125f;

    if (steering != 0 && turnVel == 0) {
        if (steering > 0) {
            turnVel = 1;
        }
        if (steering < 0) {
            turnVel = -1;
        }
    }

    racer->steerAngle += turnVel;

}

/**
 * Primary function for updating the camera during player control.
 * Decides which behaviour to use, then branches off to that function.
 * Afterwards, writes position data to the current camera object.
 */
void update_player_camera(Object *obj, Object_Racer *racer, f32 updateRate) {
	f32 temp_f14;
    s32 delta;
	s32 angle;

    if (gCurrentButtonsPressed & U_CBUTTONS && func_800A0190()) {
        gCameraObject->zoom++;
        if (gCameraObject->zoom > ZOOM_VERY_CLOSE) {
            gCameraObject->zoom = ZOOM_MEDIUM;
        }
        if (racer->playerIndex != PLAYER_COMPUTER) {
            func_80066060(racer->playerIndex, gCameraObject->zoom);
        }
        switch (gCameraObject->zoom) {
        case ZOOM_MEDIUM:
            play_sound_global(SOUND_MENU_BACK, NULL);
            break;
        case ZOOM_FAR:
            play_sound_global(SOUND_MENU_BACK2, NULL);
            break;
        default:
            play_sound_global(SOUND_UNK_6A, NULL);
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
    gCameraObject->x_velocity = (((obj->segment.trans.x_position + (91.75f * racer->ox1) + (90.0f * racer->ox3)) - gCameraObject->trans.x_position) * temp_f14);
    gCameraObject->z_velocity = (((obj->segment.trans.z_position + (91.75f * racer->oz1) + (90.0f * racer->oz3)) - gCameraObject->trans.z_position) * temp_f14);
    gCameraObject->y_velocity = (((func_8003ACAC() + 48.5f)- gCameraObject->trans.y_position) * temp_f14);
    gCameraObject->unk38 =  -gCameraObject->trans.x_rotation * temp_f14;
    gCameraObject->trans.x_position += gCameraObject->x_velocity;
    gCameraObject->trans.y_position += gCameraObject->y_velocity + gCameraObject->unk30;
    gCameraObject->trans.z_position += gCameraObject->z_velocity;
    if (!gRaceStartTimer && !D_8011D586) {
        gCameraObject->x_velocity = gCameraObject->x_velocity * 0.95f;
        gCameraObject->y_velocity = gCameraObject->y_velocity * 0.95f;
        gCameraObject->z_velocity = gCameraObject->z_velocity * 0.95f;
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
        gCameraObject->unk30 = -gCameraObject->unk30 * 0.75f;
    }
}

void func_800580B4(Object *obj, Object_Racer *racer, s32 mode, f32 arg3) {
    f32 xPos, yPos, zPos;
    if ((gCurrentPlayerIndex != -1) && (racer->raceStatus != STATUS_FINISHED)) {
        if (mode != gCameraObject->mode) {
            update_player_camera(obj, racer, arg3);
            xPos = gCameraObject->trans.x_position;
            yPos = gCameraObject->trans.y_position;
            zPos = gCameraObject->trans.z_position;
            gCameraObject->mode = mode;
            update_player_camera(obj, racer, arg3);
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
    baseSpeed = racer->forwardVel;
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
        baseSpeed *= 0.25f;
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
    if (racer->velocity < 0.0f) {
        tempVel = 6.0f;
        if (racer->drift_direction) {
            tempVel = 3.0f;
        }
        tempVel = -(racer->velocity * brakeVar) * tempVel;
        if (65.0f < tempVel) {
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
        if (normalise_time(36) < racer->boostTimer) {
            baseDistance = -30.0f;
        } else if (racer->boostTimer > 0) {
            baseDistance = 180.0f;
        }
    }
    if (gRaceStartTimer > 80) {
        gCameraObject->unk1C = baseDistance;
        gCameraObject->unk20 = yVel;
    }
    gCameraObject->unk1C += (baseDistance - gCameraObject->unk1C) * 0.125f;
    gCameraObject->unk20 += (yVel - gCameraObject->unk20) * 0.125f;
    cosOffset = cosine_s(gCameraObject->trans.x_rotation - baseAngle);
    sineOffset = sine_s(gCameraObject->trans.x_rotation - baseAngle);
    lateralOffset = gCameraObject->unk1C;
    lateralOffset = (lateralOffset * sineOffset) - (gCameraObject->unk20 * cosOffset);
    yVel = (gCameraObject->unk1C * cosOffset) + (gCameraObject->unk20 * sineOffset);
    sineOffset = cosine_s(-racer->unk196 + 0x8000) * lateralOffset;
    cosOffset = sine_s(-racer->unk196 + 0x8000) * lateralOffset;
    baseDistance = 0.0f;
    if (gCurrentRacerInput & A_BUTTON) {
        baseDistance = racer->lateral_velocity * 1.2f;
        if (baseDistance > 0.0f) {
            baseDistance -= 1.5f;
            if (baseDistance < 0.0f) {
                baseDistance = 0.0f;
            }
        } else {
            baseDistance += 1.5f;
            if (baseDistance > 0.0f) {
                baseDistance = 0.0f;
            }
        }
    }
    if (racer->drift_direction) {
        baseDistance = -(f32) racer->drift_direction * 12.0f;
    }
    racer->unkC8 += (baseDistance - racer->unkC8) * 0.125f;
    if (racer->spinout_timer) {
        racer->camera_zoom -= racer->camera_zoom * 0.25f;
    } else {
        racer->camera_zoom += (10.0f - racer->camera_zoom) * 0.25f;
    }
    xOffset = obj->segment.trans.x_position - (racer->ox1 * racer->camera_zoom);
    yOffset = obj->segment.trans.y_position - (racer->oy1 * racer->camera_zoom);
    zOffset = obj->segment.trans.z_position - (racer->oz1 * racer->camera_zoom);
    tempVel = cosine_s(racer->unk196 + 0x4000) * racer->unkC8;
    baseDistance = xOffset + tempVel;
    gCameraObject->trans.x_position = sineOffset + baseDistance;
    yOffset += yVel;
    temp_f16 = (gCameraObject->trans.y_position - yOffset) * 0.25f;
    if (temp_f16 < -2.0f) {
        gCameraObject->trans.y_position -= temp_f16 + 2.0f;
    }
    gCameraObject->trans.y_position -= temp_f16 * 0.25f;
    if (temp_f16 > 0.0f || gRaceStartTimer) {
        gCameraObject->trans.y_position = yOffset;
    }
    gCameraObject->trans.z_position = zOffset + (-sine_s(racer->unk196 + 0x4000) * racer->unkC8) + cosOffset;
    gCameraObject->trans.y_rotation = racer->unk196;
    newAngle = gCameraObject->trans.z_rotation;
    if ((racer->drift_direction && racer->brake > 0.0f)|| D_8011D586) {
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
        gCameraObject->segmentIndex = segmentIndex;
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
    s32 segmentIndex;
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
    temp_f12 = (gCameraObject->trans.y_position - (obj->segment.trans.y_position + 45.0f)) * 0.25f;
    if (temp_f12 < -2.0f) {
        gCameraObject->trans.y_position = (gCameraObject->trans.y_position - (temp_f12 + 2.0f));
    }
    if (temp_f12 > 0.0f) {
        gCameraObject->trans.y_position = obj->segment.trans.y_position + 45.0f;
    }
    gCameraObject->trans.z_position = obj->segment.trans.z_position + zOffset;
    segmentIndex = get_level_segment_index_from_position(gCameraObject->trans.x_position, gCameraObject->trans.y_position, gCameraObject->trans.z_position);
    if (segmentIndex != SEGMENT_NONE) {
        gCameraObject->segmentIndex = segmentIndex;
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
    gCameraObject->segmentIndex = get_level_segment_index_from_position(gCameraObject->trans.x_position, racer->oy1, gCameraObject->trans.z_position);
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
    gCameraObject->segmentIndex = get_level_segment_index_from_position(gCameraObject->trans.x_position,
                            racer->oy1, gCameraObject->trans.z_position);
}

// Think this is used to calculate the path for the AI.
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
        magnitude = 1.0f - racer->checkpoint_distance;
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
        if (magnitude >= 1.0f) {
            destReached = 1;
            magnitude -= 1.0f;
        }
        *xVel = catmull_rom_interpolation(splineX, destReached, magnitude);
        *yVel = catmull_rom_interpolation(splineY, destReached, magnitude);
        *zVel = catmull_rom_interpolation(splineZ, destReached, magnitude);
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_80059208.s")

void get_timestamp_from_frames(s32 frameCount, s32 *minutes, s32 *seconds, s32 *hundredths) {
    if (gVideoRefreshRate == REFRESH_50HZ) {
        frameCount = (f32)frameCount * 1.2f;
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

/**
 * When you enter a door, take control away from the player.
 * Get the angle to the door object, and drive towards it.
 * After a timer hits 0, execute the transition.
 */
void racer_enter_door(Object_Racer* racer, s32 updateRate) {
    struct Object_Exit *temp_a3;
    f32 delta;
    s32 angle;

    temp_a3 = (struct Object_Exit *) racer->unk108->unk64;
    racer->playerIndex = PLAYER_COMPUTER;
    angle = (u16) arctan2_f(temp_a3->unk0, temp_a3->unk8)  - (racer->unk1A0 & 0xFFFF);
    WRAP(angle, -0x8000, 0x8000);
    angle = -angle >> 5;
    gCurrentStickX = angle;
    gCurrentButtonsPressed = 0;
    gCurrentButtonsReleased = 0;
    gCurrentRacerInput = 0;
    gCurrentStickY = 0;
    if (racer->velocity > -4.0f) {
        gCurrentRacerInput |= A_BUTTON;
    } else if (racer->velocity < -5.0f) {
        gCurrentRacerInput |= B_BUTTON;
    }
    delta = (f32) updateRate;
    gCameraObject->trans.x_position += (temp_a3->unk0 * delta) * 1.5f;
    gCameraObject->trans.z_position += (temp_a3->unk8 * delta) * 1.5f;
    if (gCurrentStickX > 75) {
        gCurrentStickX = 75; 
        gCurrentRacerInput |= A_BUTTON | B_BUTTON; 
    }
    if (gCurrentStickX < -75) {
        gCurrentStickX = -75;
        gCurrentRacerInput |= A_BUTTON | B_BUTTON;
    }
    if (racer->transitionTimer < -1) {
        racer->transitionTimer += updateRate;
        if (racer->transitionTimer >= 0) {
            racer->transitionTimer = -1;
        }
    }
    if ((racer->transitionTimer < -1 && gCurrentStickX < 10 && gCurrentStickX > -10) || racer->transitionTimer == -1) {
        if (func_80066510() == 0) {
            func_800C01D8((FadeTransition* ) D_800DCDD4);
        }
        racer->transitionTimer = 60 - updateRate;
    }
    func_8006F388(1);
    if (racer->transitionTimer > 0) {
        racer->transitionTimer -= updateRate;
        if (racer->transitionTimer <= 0) {
            func_8006D968((s8* ) racer->unk108->segment.unk3C_a.unk3C);
            racer->transitionTimer = 0;
        }
    }
}

void func_8005A6F0(Object *obj, Object_Racer *racer, s32 updateRate, f32 updateRateF) {
    s32 var_t2; // sp9C
    Object **objects;
    s32 renderContext; //sp94
    s32 countOfObjects; //sp90
    f32 xPos; //sp8C
    f32 yPos; //sp88
    f32 zPos; //sp84
    f32 sp80; //sp80
    Object *playerOneObj;
    f32 var_fv1; //sp78
    Object *playerTwoObj;
    LevelHeader *levelHeader; //sp70
    s32 temp_v0_10;
    f32 temp_f0;
    unknown8011AECC *temp_v0_9;
    Object_Racer *tempRacer;
    f32 temp_fv1_2;

    gCurrentPlayerIndex = -1;
    renderContext = get_render_context();
    levelHeader = get_current_level_header();
    if (racer->unk1F6 > 0) {
        racer->unk1F6 -= updateRate;
    } else {
        racer->unk1F6 = 0;
    }
    if (gRaceStartTimer != 0) {
        racer->unk1C6 = get_random_number_from_range(-60, 60) + 120;
    }
    if (racer->unk18C > 0) {
        racer->unk18C -= updateRate;
    } else {
        racer->unk18C = 0;
    }
    gCurrentRacerMiscAssetPtr = (f32 *)get_misc_asset(MISC_RACER_WEIGHT);
    gCurrentRacerWeightStat = gCurrentRacerMiscAssetPtr[racer->characterId] * 0.45f;
    if (racer->unk204 > 0) {
        gCurrentRacerWeightStat = -0.02f;
    }
    gCurrentRacerMiscAssetPtr = (f32 *)get_misc_asset(MISC_RACER_HANDLING);
    gCurrentRacerHandlingStat = gCurrentRacerMiscAssetPtr[racer->characterId];
    gCurrentRacerMiscAssetPtr = (f32 *)get_misc_asset(MISC_ASSET_UNK0B);
    D_8011D574 = gCurrentRacerMiscAssetPtr[racer->characterId];
    xPos = obj->segment.trans.x_position;
    yPos = obj->segment.trans.y_position;
    zPos = obj->segment.trans.z_position;
    
    if (racer->unk1B2 > 0) {
        racer->unk1B2 -= updateRate;
        if (racer->unk1B2 < 0) {
            racer->unk1B2 = 0;
        }
    }
    
    racer->unk1E7++;
    
    if (
        func_8002341C() ||
        func_80023568() || 
        racer->unk1D6 == 4 ||
        D_8011D544 > 120.0f ||
        gRaceStartTimer != 0 ||
        (levelHeader->race_type & RACETYPE_CHALLENGE_BATTLE)
    ) {
        racer->unk201 = 30;
    }
    
    var_fv1 = 1000000;
    if (racer->unk201 == 0) {
        objects = get_object_struct_array(&countOfObjects);
        playerOneObj = playerTwoObj = NULL;
        for (var_t2 = 0; var_t2 < countOfObjects; var_t2++) {
            tempRacer = &objects[var_t2]->unk64->racer;
            if (tempRacer->playerIndex == PLAYER_ONE) {
                playerOneObj = objects[var_t2];
            }
            if (tempRacer->playerIndex == PLAYER_TWO) {
                 playerTwoObj = objects[var_t2];
            }
        }
        if (playerOneObj != NULL) {
            var_fv1 = playerOneObj->segment.trans.x_position - obj->segment.trans.x_position;
            temp_f0 = playerOneObj->segment.trans.z_position - obj->segment.trans.z_position;
            var_fv1 = (var_fv1 * var_fv1) + (temp_f0 * temp_f0);
        }
        if ((playerTwoObj != NULL) && (var_fv1 >= 160000.0f)) {
            var_fv1 = playerTwoObj->segment.trans.x_position - obj->segment.trans.x_position;
            temp_f0 = playerTwoObj->segment.trans.z_position - obj->segment.trans.z_position;
            var_fv1 = (var_fv1 * var_fv1) + (temp_f0 * temp_f0);
        }
    }
    if (racer->unk204 > 0) {
        racer->unk204 -= updateRate;
        racer->velocity *= 0.8f;
    }
    if (racer->unk206 > 0) {
        racer->unk18A = racer->unk206;
        racer->unk206 -= updateRate;
    }
    if ((racer->unk201 == 0) && (var_fv1 < 160000.0f)) {
        racer->unk201 = 30;
    }
    if (racer->unk201 != 0) {
        func_80044170(obj, racer, updateRate);
        if (!(gCurrentRacerInput & A_BUTTON)) {
            racer->throttleReleased = 1;
        }
        if (racer->unk1FE == 3) {
            gCurrentRacerWeightStat *= ((f32)racer->unk1FF / 256.0f);
        }
        if (racer->unk1FE == 1) {
            gCurrentRacerWeightStat -= ((gCurrentRacerWeightStat * racer->unk1FF) / 128.0f);
            if (racer->unk204 > 0) {
                gCurrentRacerWeightStat = -gCurrentRacerWeightStat;
            }
            gCurrentStickY = 60;
        }
        if (racer->unk1FE == 2) {
            racer->unk84 += ((((cosine_s(racer->unk1FF << 8) * 4) - racer->unk84) * 0.0625 * updateRateF));
            racer->unk88 += ((((sine_s  (racer->unk1FF << 8) * 4) - racer->unk88) * 0.0625 * updateRateF));
        } else {
            racer->unk84 -= racer->unk84 * 0.0625 * updateRateF;
            racer->unk88 -= racer->unk88 * 0.0625 * updateRateF;
        }
        gCurrentRacerHandlingStat = 1;
        gCurrentRacerMiscAssetPtr = (f32 *)get_misc_asset(MISC_ASSET_UNK21);
        D_8011D568 = (f32 *)get_misc_asset(obj->segment.header->unk5D);
        if ((obj->segment.y_velocity < 4.0f)&& ((racer->unk1E2 >= 3) || (racer->buoyancy != 0.0f))) {
            racer->unk1F1 = 0;
        }
        if (racer->unk175 != 0) {
            func_80056E2C(obj, racer, updateRate);
        }
        if (racer->unk1D6 != 1) {
            racer->unk1E5 = 0;
            racer->buoyancy = 0;
            D_8011D5AE = 0;
        } else {
            D_8011D5AE = func_8002B0F4(obj->segment.unk2C.half.lower, obj->segment.trans.x_position, obj->segment.trans.z_position, &D_8011D5B0);
        }
        func_8002ACC8(0);
        if ((racer->unk148 != NULL) || (gRaceStartTimer != 0) || (racer->unk204 > 0)) {
            gCurrentStickX = 0;
            gCurrentStickY = 0;
            gCurrentRacerInput = 0;
            gCurrentButtonsReleased = 0;
            gCurrentButtonsPressed = 0;
        }
        // The case statements break must be on the same line as the function call in order to match
        switch (racer->unk1D6) {
        case 0: func_8004F7F4(updateRate, updateRateF, obj, racer); break;
        case 4: func_8004CC20(updateRate, updateRateF, obj, racer); break;
        case 1: func_80046524(updateRate, updateRateF, obj, racer); break;
        case 2: func_80049794(updateRate, updateRateF, obj, racer); break;
        case 3: /* fall through */
        case 10:func_8004D95C(updateRate, updateRateF, obj, racer); break;
        case 5: func_8005C364(updateRate, updateRateF, obj, racer, &gCurrentRacerInput, &gCurrentButtonsPressed, &gRaceStartTimer); break;
        case 6: func_8005D0D0(updateRate, updateRateF, obj, racer, &gCurrentRacerInput, &gCurrentButtonsPressed, &gRaceStartTimer); break;
        case 7: /* fall through */
        case 8: func_8005D820(updateRate, updateRateF, obj, racer, &gCurrentRacerInput, &gCurrentStickX, &gRaceStartTimer); break;
        case 11:func_8005E4C0(updateRate, updateRateF, obj, racer, &gCurrentRacerInput, &gCurrentButtonsPressed, &gRaceStartTimer); break;
        case 12:func_8005EA90(updateRate, updateRateF, obj, racer, &gCurrentRacerInput, &gCurrentButtonsPressed, &gRaceStartTimer); break;
        case 13:func_8005F310(updateRate, updateRateF, obj, racer, &gCurrentRacerInput, &gCurrentButtonsPressed, &gRaceStartTimer); break;
        }
        if (renderContext != DRAW_MENU) {
            func_800050D0(obj, gCurrentButtonsPressed, gCurrentRacerInput, updateRate);
        }
        sp80 = racer->checkpoint_distance;
        countOfObjects = racer->unk192;
        var_t2 = func_800185E4(racer->unk192, obj, xPos, yPos, zPos, &racer->checkpoint_distance, &racer->unk1C8);
        if (var_t2 == -100) {
            func_8005C270(racer);
        }
        temp_v0_9 = func_8001BA1C(racer->unk192, racer->unk1C8);
        if (temp_v0_9->unk36[racer->unk1CA] == 5) {
            racer->unk201 = 30;
            if (racer->unk1E5 != 0) {
                racer->unk1C8 = 1;
            }
        }
        if (temp_v0_9->unk36[racer->unk1CA] == 6) {
            racer->unk193 = levelHeader->laps + 1;
        }
        if (temp_v0_9->unk36[racer->unk1CA] == 4) {
            if (racer->velocity < -4.0f) {
                racer->velocity *= 0.9f;
            }
        }
        if (var_t2 == 0) {
            if (temp_v0_9->unk36[racer->unk1CA] == 2) {
                racer->unk1C8 = 1;
            }
            temp_v0_10 = func_8001BA64();
            racer->unk192++;
            if (racer->unk192 >= temp_v0_10) {
                racer->unk192 = 0;
                if (racer->unk190 > 0) {
                    if (racer->unk193 < 120) {
                        racer->unk193++;
                    }
                }
            }
            if (racer->unk190 < ((levelHeader->laps + 3) * temp_v0_10)) {
                racer->unk190++;
            }
            racer->unk1A8 = 10000;
        } else {
            if ((racer->playerIndex == -1) && (sp80 < racer->checkpoint_distance)) {
                racer->checkpoint_distance = sp80;
            }
            racer->unk1A8 = var_t2;
        }
        racer->unk68 = obj->segment.trans.x_position;
        racer->unk6C = obj->segment.trans.y_position;
        racer->unk70 = obj->segment.trans.z_position;
    } else {
        func_8005B818(obj, racer, updateRate, updateRateF);
        if (renderContext != DRAW_MENU) {
            func_800050D0(obj, gCurrentButtonsPressed, gCurrentRacerInput, updateRate);
        }
    }
    if (racer->unk175 == 0) {
        if (racer->unk178 != NULL) {
            func_8000488C(racer->unk178);
            racer->unk178 = NULL;
        }
    }
    func_80018CE0(obj, xPos, yPos, zPos, updateRate);
    if (racer->unk188 > 0) {
        func_800576E0(obj, racer, racer->unk188);
    }
    if (racer->unk148 != NULL) {
        racer->unk148 = NULL;
        racer->velocity = 0.0f;
        racer->lateral_velocity = 0.0f;
    }
    if (racer->stretch_height <= racer->stretch_height_cap) {
        temp_fv1_2 = 0.02f;
    } else {
        temp_fv1_2 = -0.02f;
    }
    racer->stretch_height = (racer->stretch_height + ((((racer->stretch_height_cap - racer->stretch_height) * 0.125f) + temp_fv1_2) * updateRateF));
    if (((temp_fv1_2 < 0.0f) && (racer->stretch_height <= racer->stretch_height_cap)) || ((temp_fv1_2 > 0.0f) && (racer->stretch_height_cap <= racer->stretch_height))) {
        racer->stretch_height = racer->stretch_height_cap;
        racer->stretch_height_cap = 1.0f; 
    }
    var_t2 = ((racer->unk16C - racer->unk16A) * updateRate) >> 3;
    CLAMP(var_t2, -0x800, 0x800)
    if (D_800DCB54 != 0) {
        racer->unk16A += D_800DCB54;
    } else {
        racer->unk16A += var_t2;
    }
    if (racer->shieldTimer > 0) {
        if (racer->shieldTimer >= 61) {
            if (racer->shieldSoundMask != 0) {
                update_spatial_audio_position(racer->shieldSoundMask, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
            } else if (racer->unk118 != 0) {
                func_80009558(SOUND_SHIELD, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 1, &racer->shieldSoundMask);
            }
        } else {
            if (racer->shieldSoundMask != 0) {
                func_800096F8(racer->shieldSoundMask);
                racer->shieldSoundMask = 0;
            }
        }
        racer->shieldTimer -= updateRate;
        if (racer->shieldTimer <= 0) {
            racer->shieldType = 0;
        }
    }
    if (racer->soundMask != 0) {
        update_spatial_audio_position(racer->soundMask, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
    }
    D_8011D584 = 0;
    if ((racer->unk150 != NULL) && (gRaceStartTimer == 0)) {
        s8 *temp;
        racer->unk150->segment.trans.x_position = obj->segment.trans.x_position;
        temp = (s8 *)get_misc_asset(MISC_ASSET_UNK00);
        racer->unk150->segment.trans.y_position = obj->segment.trans.y_position + temp[racer->characterId];
        racer->unk150->segment.trans.z_position = obj->segment.trans.z_position;
        racer->unk150->segment.trans.scale = obj->segment.unk30 / 265.0f;
        if (obj->segment.unk30 < 1500.0f) {
            racer->unk150->segment.trans.unk6 |= 0x4000;
        }
        if (racer->unk150->segment.trans.scale < 1.0f) {
            racer->unk150->segment.trans.scale = 1.0f;
        }
        racer->unk150 = NULL;
    }
    racer->unk1FE = 0xFF;
    func_8004F77C(racer);
}

#ifdef NON_EQUIVALENT
//WIP
void func_8005B818(Object *obj, Object_Racer *racer, s32 updateRate, f32 updateRateF) {
    s32 sp11C;
    f32 sp100;
    f32 spEC;
    f32 spC0; //s32?
    f32 spD8;
    f32 spBC; //s32?
    f32 spB8;
    f32 spAC; //s32?
    f32 spA8; //s32?
    f32 spA4; //struct?
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp8C; //What sets this?
    LevelHeader *levelHeader; //sp80
    f32 *sp70;
    f32 *var_t0; //struct?
    f32 *var_a2;
    f32 *var_a3;
    f32 *var_t1;
    f32 *var_v1;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f24;
    f32 temp_f24_3;
    f32 temp_f26;
    f32 temp_f28;
    f32 var_f12;
    f32 var_f12_2;
    f32 var_f22;
    f32 var_f26;
    f32 var_f28;
    s16 temp_v0_4;
    s32 var_a0;
    s32 var_s0;
    s32 var_s2;
    s32 var_v0;
    s8 temp_v0_3;
    unknown8011AECC *temp_v0_2;
    s32 i;

    gCurrentRacerMiscAssetPtr = get_misc_asset(MISC_ASSET_UNK21);
    levelHeader = get_current_level_header();
    sp11C = func_8001BA64();
    if (sp11C != 0) {
        racer->unk1C9 = 0;
        racer->unk1F5 = 0;
        racer->attackType = 0;
        racer->lateral_velocity = 0;
        sp94 = 20.0f;
        if (racer->unk124 < -20.0f) {
            racer->unk124 = -20.0f;
        }
        if (racer->unk124 > sp94) {
            racer->unk124 = sp94;
        }
        var_f12 = sqrtf(((racer->unk124 * 0.025) + 0.595) / 0.004);
        var_v1 = &sp100;
        if (racer->boostTimer != 0) {
            var_f12 *= 1.2f;
        }
        var_a2 = &spEC;
        if (racer->unk1D6 == 1) {
            var_v0 = (racer->unk1BE & 0xFFFF) - (racer->unk1C2 & 0xFFFF);
            if (var_v0 >= 0x8001) {
                var_v0 += 0xFFFF0001;
            }
            if (var_v0 < -0x8000) {
                var_v0 += 0xFFFF;
            }
            if (var_v0 < 0) {
                var_v0 = -var_v0;
            }
            var_v0 -= 200;
            if (var_v0 < 0) {
                var_v0 = 0;
            }
            sp94 = (f32)var_v0 / 150.0f;
            var_f12_2 = var_f12 - sp94;
            if (var_f12_2 < 2.0f) {
                var_f12_2 = 2.0f;
            }
            if (racer->velocity < -var_f12_2) {
                racer->velocity = -var_f12_2;
            } else {
                racer->velocity += ((-var_f12_2 - racer->velocity) * 0.125f);
            }
        } else {
            racer->velocity += ((-var_f12 - racer->velocity) * 0.25f);
        }
        var_a3 = &spD8;
        var_a0 = racer->unk192 - 2;
        var_t1 = &spB8;
        if (var_a0 < 0) {
            var_a0 += sp11C;
        }
        var_t0 = &spA4;
        if (var_a0 >= sp11C) {
            var_a0 -= sp11C;
        }
        for (i = 0; i < 1; i++) {
            temp_v0_2 = func_8001BA1C(var_a0, racer->unk1C8);
            var_v1[i] = temp_v0_2->unk10;
            var_a2[i] = temp_v0_2->unk14;
            var_a3[i] = temp_v0_2->unk18;
            var_t1[i] = temp_v0_2->unk2E[racer->unk1CA];
            var_t0[i] = temp_v0_2->unk32[racer->unk1CA];
            var_v1[i] += ((temp_v0_2->unk1C * temp_v0_2->unk8 * temp_v0_2->unk2E[racer->unk1CA]));
            var_a2[i] += ((temp_v0_2->unk1C * temp_v0_2->unk32[racer->unk1CA]));
            var_a3[i] += ((temp_v0_2->unk1C * -temp_v0_2->unk0 * temp_v0_2->unk2E[racer->unk1CA]));
            var_a0++;
            if (var_a0 == sp11C) {
                var_a0 = 0;
            }
        }
        
        if (racer->velocity < 0.0f) {
            racer->velocity = -racer->velocity;
        }
        var_s2 = 0;
        if (racer->unkAC == 0.0f) {
            racer->unkAC = 0.01f;
        }
        for (var_s0 = 0; var_s0 < 2; var_s0++) {
            var_f22 = ((1.0f - racer->checkpoint_distance) + (racer->unkAC * updateRateF));
            if (var_f22 >= 1.0f) {
                var_s2 = 1;
                var_f22--;
            }
            temp_f26 = func_8002263C(&sp100, var_s2, var_f22, &sp9C);
            temp_f24 = func_8002263C(&spEC, var_s2, var_f22, &sp98);
            temp_f28 = func_8002263C(&spD8, var_s2, var_f22, &sp94);
            temp_f26 -= racer->unk68;
            temp_f24 -= racer->unk6C;
            temp_f28 -= racer->unk70;
            if (var_s0 == 0) {
                var_s2 = 0;
                temp_f12 = sqrtf((temp_f26 * temp_f26) + (temp_f24 * temp_f24) + (temp_f28 * temp_f28)) / updateRateF;
                if (temp_f12 != 0) {
                    racer->unkAC *= (sp8C / temp_f12);
                } else {
                    var_s0 = -1;
                    racer->unkAC += 0.01;
                }
            }
        }
        racer->unk68 += temp_f26;
        racer->unk6C += temp_f24;
        racer->unk70 += temp_f28;
        var_f26 = racer->unk68 - obj->segment.trans.x_position;
        var_f28 = racer->unk70 - obj->segment.trans.z_position;
        temp_f24_3 = racer->unk6C - obj->segment.trans.y_position;
        temp_f12_2 = sqrtf((var_f26 * var_f26) + (var_f28 * var_f28)) / updateRateF;
        if (temp_f12_2 > 35.0f) {
            temp_f0_4 = (35.0f / temp_f12_2);
            var_f26 *= temp_f0_4;
            var_f28 *= temp_f0_4;
        }
        racer->checkpoint_distance = (1 - var_f22);
        if (var_s2 != 0) {
            racer->unk192 += 1;
            if (racer->unk192 >= sp11C) {
                racer->unk192 = 0;
                if (racer->unk190 > 0) {
                    temp_v0_3 = racer->unk193;
                    if (temp_v0_3 < 0x78) {
                        racer->unk193 = temp_v0_3 + 1;
                    }
                }
            }
            temp_v0_4 = racer->unk190;
            if (temp_v0_4 < ((levelHeader->laps + 3) * sp11C)) {
                racer->unk190 = temp_v0_4 + 1;
            }
            racer->unk1A8 = 10000;
        } else {
            racer->unk1A8 = racer->checkpoint_distance * 100;
        }
        if (racer->boostTimer > 0) {
            racer->boostTimer -= updateRate;
        } else {
            racer->boostTimer = 0;
        }
        racer->unk1BA = (((spC0 - spBC) * var_f22) + spBC);
        racer->unk1BC = (((spAC - spA8) * var_f22) + spA8);
        temp_f0_5 = sqrtf((sp9C * sp9C) + (sp94 * sp94));
        if (temp_f0_5 != 0) {
            sp9C /= temp_f0_5;
            sp94 /= temp_f0_5;
            sp98 /= temp_f0_5;
            racer->unk1A0 = arctan2_f(sp9C, sp94) - 0x8000;
            obj->segment.trans.y_rotation = racer->unk1A0;
            obj->segment.trans.x_rotation = arctan2_f(sp98, 1.0f);
        }
        racer->unk1C2 = racer->unk1BE;
        racer->unk1C4 = racer->unk1C0;
        racer->unk1BE = racer->unk1A0;
        racer->unk1C0 = obj->segment.trans.x_rotation;
        if (func_80011570(obj, var_f26, temp_f24_3, var_f28)) {
            obj->segment.trans.x_position += var_f26;
            obj->segment.trans.y_position += temp_f24_3;
            obj->segment.trans.z_position += var_f28;
        }
        if (temp_f12_2 < 20.0f) {
            obj->segment.y_velocity = -1.0f;
            obj->segment.x_velocity = var_f26 / updateRateF;
            obj->segment.z_velocity = var_f28 / updateRateF;
        }
        func_80042D20(obj, racer, updateRate);
        func_80055EC0(obj, racer, updateRate);
        racer->unk1E5 = 0;
        obj->unk4C->x_position = obj->segment.trans.x_position;
        obj->unk4C->y_position = obj->segment.trans.y_position;
        obj->unk4C->z_position = obj->segment.trans.z_position;
        racer->drift_direction = 0;
        racer->y_rotation_vel = 0;
        racer->z_rotation_vel = 0;
        racer->unk1D2 = 0;
        racer->carBobX = 0.0f;
        racer->carBobY = 0.0f;
        racer->carBobZ = 0.0f;
        obj->segment.y_velocity = 0.0f;
        racer->unkD8.x = obj->segment.trans.x_position;
        racer->unkD8.y = obj->segment.trans.y_position;
        racer->unkD8.z = obj->segment.trans.z_position;
        racer->unkE4.x = obj->segment.trans.x_position;
        racer->unkE4.y = obj->segment.trans.y_position;
        racer->unkE4.z = obj->segment.trans.z_position;
        racer->unkF0.x = obj->segment.trans.x_position;
        racer->unkF0.y = obj->segment.trans.y_position;
        racer->unkF0.z = obj->segment.trans.z_position;
        racer->unkFC.x = obj->segment.trans.x_position;
        racer->unkFC.y = obj->segment.trans.y_position;
        racer->unkFC.z = obj->segment.trans.z_position;
        obj->unk74 = 0;
        func_800AF714(obj, updateRate);
    }
}
#else
GLOBAL_ASM("asm/non_matchings/racer/func_8005B818.s")
#endif

// This gets called if an anti-piracy checksum fails in func_8005F850.
/**
 * Triggered upon failure of an anti-tamper test. Sets the first index of the surface speed
 * table to an unreasonable value, wrecking drivability while on it.
 */
void antipiracy_modify_surface_traction_table(void) {
    gSurfaceTractionTable[SURFACE_DEFAULT] = 0.05f;
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
