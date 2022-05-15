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

s32 D_8011D4F0[2];
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
s32 D_8011D540;
f32 D_8011D544;
s32 D_8011D548;
s32 D_8011D54C;
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
s32 D_8011D570;
s32 D_8011D574;
s32 D_8011D578;
s32 D_8011D57C;
s8 D_8011D580;
s8 D_8011D581;
s8 D_8011D582;
s8 D_8011D583;
s8 D_8011D584;
s8 D_8011D585;
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

typedef struct Object_64_Unknown5 {
    u8 pad0[0x88];
    u8 unk89;
    u8 pad90[0xE9];
    s8 unk172;
    s8 unk173;
    s8 unk174;
    u8 pad175[0x5E];
    s8 unk1D3;
} Object_64_Unknown5;

typedef struct TempStruct5 {
    s8 pad0[8];
    s8 unk8[4][4];
} TempStruct5;

void func_80043ECC(s32 arg0, Object_64_Unknown5 *arg1, s32 arg2) {
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
            D_8011D5BA += arg2;
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
void func_80044170(Object *arg0, Object_Racer *arg1, s32 arg2) {
    s32 raceType;

    raceType = get_current_level_race_type();

    switch (raceType) {
        case RACETYPE_CHALLENGE_BATTLE:
        case RACETYPE_CHALLENGE_BANANAS:
            func_8004447C(arg0, arg1, arg2);
            break;
        case RACETYPE_CHALLENGE_EGGS:
            func_800452A0(arg0, arg1, arg2);
            break;
        default:
            // last argument was required for match, might not really exist
            func_80045C48(arg0, arg1, arg2, raceType);
            break;
    }

    if (arg1->unk214 == 0 && arg1->velocity < -0.5) {
        arg1->unk215 -= arg2;
        if (arg1->unk215 < 0) {
            arg1->unk215 = 0;
        }
    }

    if (arg1->velocity > -1.0 && arg1->unk214 == 0 && D_8011D540 == 0 && D_8011D544 == 0.0f && arg1->unk1E2 != 0 && arg1->unk215 == 0) {
        arg1->unk213 += arg2;

        if (arg1->unk213 > 60) {
            arg1->unk213 = 0;
            arg1->unk214 = 60;
            arg1->unk215 = 120;

            if ((raceType & RACETYPE_CHALLENGE) == 0) {
                arg1->unk1CA = (arg1->unk1CA + 1) & 3;
            } else if (raceType == RACETYPE_CHALLENGE_BATTLE || raceType == RACETYPE_CHALLENGE_BANANAS) {
                if (arg1->unk1CE != 0xFF) {
                    arg1->unk154 = func_8001D214(arg1->unk1CE);
                }
            }
        }
    } else {
        arg1->unk214 -= arg2;
        arg1->unk213 = 0;

        if (arg1->unk214 < 0) {
            arg1->unk214 = 0;
        }
    }

    // Kick it into reverse.
    if (arg1->unk214 != 0) {
        gCurrentStickX *= -1;
        gCurrentCarInput &= ~A_BUTTON;
        gCurrentStickY = -50;
        gCurrentCarInput |= B_BUTTON;
    }

    // Cap stick inputs.
    if (gCurrentStickX > 75) {
        gCurrentStickX = 75;
    }

    if (gCurrentStickX < -75) {
        gCurrentStickX = -75;
    }

    if (gCurrentStickY > 75) {
        gCurrentStickY = 75;
    }

    if (gCurrentStickY < -75) {
        gCurrentStickY = -75;
    }
}

s32 func_80044450(s32 arg0) {
    return get_random_number_from_range(0, 99) < arg0;
}

GLOBAL_ASM("asm/non_matchings/racer/func_8004447C.s")

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
GLOBAL_ASM("asm/non_matchings/racer/func_80048E64.s")
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
        if (phi_v0 >= 0x4A) {
            phi_v0 = 0x49;
        }
        temp_v1 = phi_v0 - planeObj->segment.unk18.half.upper;
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
        planeObj->segment.unk18.half.upper += phi_v0;
    }
}

void func_8004C140(Object *obj, Object_Racer *obj64) {
    s8 phi_v1;
    s8 temp;
    if (obj64->playerIndex == -1) {
        phi_v1 = 0;
    } else {
        phi_v1 = obj64->bananas;
    }
    temp = obj64->unk187;
    if (temp == 0 || obj64->unk18E > 0) {
        obj64->unk187 = 0;
        return;
    }
    if (temp != 4) {
        func_800576E0(obj, obj64, 2);
    }
    obj64->unk18C = 360;
    if (obj64->unk1C9 == 8) {
        obj64->unk1C9 = 0;
    }
    if (obj64->unk1D6 < 5) {
        func_800570B8(obj, 450, 8, 129);
        switch (obj64->unk187) {
            case 1:
            case 2:
                if (phi_v1 != 0) {
                    obj64->spinout_timer = 40;
                } else {
                    obj64->spinout_timer = 60;
                }
                break;
            case 3:
                if (phi_v1 != 0) {
                    obj64->spinout_timer = 40;
                } else {
                    obj64->spinout_timer = 60;
                }
                break;
            case 6:
                obj64->unk204 = 120;
                obj->segment.x_velocity *= 0.7;
                obj->segment.z_velocity *= 0.7;
                break;
        }
        obj64->unk187 = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_8004C2B0.s")
GLOBAL_ASM("asm/non_matchings/racer/func_8004CC20.s")
GLOBAL_ASM("asm/non_matchings/racer/func_8004D590.s")

void func_8004D95C(s32 arg0, s32 arg1, Object *obj, Object_Racer *obj64) {
    s16 sp26;

    if (obj64->unk118 != 0) {
        func_80006AC8(obj);
    }
    if ((func_8002341C() != 0) && (obj64->unk1D6 == 0xA)) {
        obj->unk4C->unk14 = 0;
    }
    sp26 = obj->segment.unk18.half.upper;
    obj64->unk1D6 = 0xA;
    func_80049794(arg0, arg1, obj, obj64);
    obj64->unk1D6 = obj64->unk1D7;
    obj->segment.unk3B = 0;
    if (obj64->unk1D6 == 0xA) {
        if (obj64->unk154 != NULL) {
            obj64->unk154->segment.trans.x_position = obj->segment.trans.x_position;
            obj64->unk154->segment.trans.y_position = obj->segment.trans.y_position;
            obj64->unk154->segment.trans.z_position = obj->segment.trans.z_position;
            obj64->unk154->segment.unk2C.half.lower = obj->segment.unk2C.half.lower;
            obj64->unk154->segment.trans.y_rotation = obj->segment.trans.y_rotation;
            obj64->unk154->segment.trans.x_rotation = obj->segment.trans.x_rotation;
            obj64->unk154->segment.trans.z_rotation = obj->segment.trans.z_rotation;
            obj->segment.unk3B = 0;
            obj->segment.unk18.half.upper = sp26 + arg0;
            func_80061C0C(obj);
        }
    }
}

/**
 * Initialise the basic properties of each racer object. If it's tied to a human player,
 * will also initialise a camera object.
 */
void obj_init_racer(Object *obj, LevelObjectEntry_CharacterFlag *arg1) {
    Object_Racer *tempObj;
    ActivePlayers player;
    s32 i;

    D_8011D53C = 0;
    tempObj = (struct Object_Racer *) obj->unk64;
    obj->segment.trans.y_rotation = arg1->unkC;
    obj->segment.trans.x_rotation = arg1->unkA;
    obj->segment.trans.z_rotation = arg1->unk8;
    player = arg1->unkE;
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
        gCameraObject->unk36 = 0;
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
    func_80043ECC(0, 0, 0);
    D_8011D583 = i;
    D_8011D585 = 0;
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

void func_80050754(Object *obj, Object_Racer *racer, f32 arg2) {
    f32 diffX;
    f32 diffY;
    f32 diffZ;

    obj->segment.unk3B = 0;
    obj->segment.unk18.half.upper = 40;
    diffX = racer->unk148->segment.trans.x_position - obj->segment.trans.x_position;
    diffY = racer->unk148->segment.trans.y_position - obj->segment.trans.y_position;
    diffZ = racer->unk148->segment.trans.z_position - obj->segment.trans.z_position;
    func_80011570(obj, diffX, diffY, diffZ);
    obj->segment.trans.y_rotation = racer->unk148->segment.trans.y_rotation;
    obj->segment.trans.x_rotation = racer->unk148->segment.trans.x_rotation;
    obj->segment.trans.z_rotation = racer->unk148->segment.trans.z_rotation;
    racer->unk1A4 = obj->segment.trans.z_rotation;
    racer->unk1A0 = obj->segment.trans.y_rotation;
    obj->segment.x_velocity = diffX / arg2;
    obj->segment.y_velocity = diffY / arg2;
    obj->segment.z_velocity = diffZ / arg2;
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
        tempAngle = yRotation - (obj->y_rotation_offset & 0xFFFF);
        obj->unk166 = xRotation;
        if (tempAngle > 0x8000) {
            tempAngle +=  0xFFFF0001;
        }
        if (tempAngle < -0x8000) {
            tempAngle += 0xFFFF;
        }
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
        tempAngle = xRotation - (obj->x_rotation_offset & 0xFFFF);
        if (tempAngle > 0x8000) {
            tempAngle = tempAngle + 0xFFFF0001;
        }
        if (tempAngle < -0x8000) {
            tempAngle = tempAngle + 0xFFFF;
        }
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
        tempAngle = zRotation - (obj->z_rotation_offset & 0xFFFF);
        if (tempAngle > 0x8000) {
            tempAngle = tempAngle + 0xFFFF0001;
        }
        if (tempAngle < -0x8000) {
            tempAngle = tempAngle + 0xFFFF;
        }
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

void func_800521C4(Object *obj, Object_Racer *racer, s32 arg2) {
    Object *tempObj;
    s8 foundObj;
    s32 sp24;
    s32 temp_f10;

    foundObj = 0;
    if (func_80023568()) {
        tempObj = get_object_struct(1);
        foundObj = func_80052388(obj, racer, tempObj, 160000.0f);
    }
    if (!foundObj) {
        tempObj = func_8001B7A8(racer, 1, &sp24);
        if (tempObj && !D_8011D540) {
            foundObj = func_80052388(obj, racer, tempObj, 160000.0f);
        }
    }
    if (!foundObj) {
        tempObj = func_8001B7A8(racer, -1, &sp24);
        if (tempObj && !D_8011D540) {
            foundObj = func_80052388(obj, racer, tempObj, 30000.0f);
        }
    }
    if (!foundObj) {
        if ((racer->unk1E7 & 0x1F) < 2) {
            temp_f10 = racer->velocity * 1280.0f;

            if (temp_f10 < 0) {
                temp_f10 = -temp_f10;
            }

            if (temp_f10 > 0x2800) {
                temp_f10 = 0x2800;
            }

            temp_f10 = 0x2800 - temp_f10;

            racer->unk16C = get_random_number_from_range(-temp_f10, temp_f10);
        }
    }
}

// Ran by the AI. Seems to be direction related of some sorts.
void func_8005234C(Object_Racer *arg0) {
    arg0->unk16C -= arg0->unk16C >> 3;
    if (arg0->unk16C >= -9 && arg0->unk16C < 10) { // Deadzone?
        arg0->unk16C = 0;
    }
}

s32 func_80052388(Object *obj1, Object_Racer *arg1, Object *obj2, f32 distance) {
    s32 rotation;
    f32 diffX;
    f32 diffZ;
    s32 ret = FALSE;

    diffX = obj2->segment.trans.x_position - obj1->segment.trans.x_position;
    diffZ = obj2->segment.trans.z_position - obj1->segment.trans.z_position;
    if ((diffX * diffX) + (diffZ * diffZ) < distance) {
        rotation = (arctan2_f(diffX, diffZ) - (obj1->segment.trans.y_rotation & 0xFFFF)) + 0x8000;
        if (rotation > 0x8000) {
            rotation -= 0xFFFF;
        }
        if (rotation < -0x8000) {
            rotation += 0xFFFF;
        }
        if (rotation > 0x3000) {
            rotation = 0x3000;
        }
        if (rotation < -0x3000) {
            rotation = -0x3000;
        }
        arg1->unk16C = rotation;
        if ((arg1->unk1E7 & 0x3F) < 0x1F) {
            arg1->unk16C = 0;
        }
        arg1 = (struct Object_Racer *) obj2->unk64;
        rotation = arctan2_f(diffX, diffZ) - (obj1->segment.trans.y_rotation & 0xFFFF);
        if (rotation > 0x8000) {
            rotation -= 0xFFFF;
        }
        if (rotation < -0x8000) {
            rotation += 0xFFFF;
        }
        if (rotation > 0x3000) {
            rotation = 0x3000;
        }
        if (rotation < -0x3000) {
            rotation = -0x3000;
        }
        arg1->unk16C = rotation;
        if (ret) {}
        ret = TRUE;
        if ((arg1->unk1E7 & 0x1F) < 0xA) {
            arg1->unk16C = 0;
        }
    }
    return ret;
}

GLOBAL_ASM("asm/non_matchings/racer/func_8005250C.s")

void func_80052988(Object *arg0, Object_Racer *arg1, s32 action, s32 arg3, s32 duration, s32 arg5, s32 arg6, s32 arg7) {
    arg5 *= arg7;

    if ((D_8011D55C == -1) && (action >= 3)) {
        arg0->segment.unk3B = 0;
        arg1->unk1F2 = 0;
    } else if (arg0->segment.unk3B == 0) {
        if (arg6 & 1) {
            if (arg0->segment.unk18.half.upper >= 41) {
                arg0->segment.unk18.half.upper -= arg7 * 4;
                if (arg0->segment.unk18.half.upper < 41) {
                    arg0->segment.unk3B = action;
                    arg0->segment.unk18.half.upper = arg3;
                }
            } else {
                arg0->segment.unk18.half.upper += arg7 * 4;
                if (arg0->segment.unk18.half.upper >= 40) {
                    arg0->segment.unk3B = action;
                    arg0->segment.unk18.half.upper = arg3;
                }
            }
        } else {
            arg0->segment.unk3B = action;
            arg0->segment.unk18.half.upper = arg3;
            arg1->unk1F3 &= ~0x80;
        }
    } else if (arg0->segment.unk3B == action) {
        if (arg6 & 2) {
            if (arg1->unk1F3 & 0x80) {
                arg0->segment.unk18.half.upper -= arg5;
                if (arg0->segment.unk18.half.upper <= 0) {
                    arg0->segment.unk3B = 0;
                    arg1->unk1F2 = 0;
                    arg0->segment.unk18.half.upper = 40;
                    arg1->unk1F3 = 0;
                }
            } else {
                arg0->segment.unk18.half.upper += arg5;
                if (arg0->segment.unk18.half.upper >= duration) {
                    arg0->segment.unk18.half.upper = duration - 1;
                    if ((arg6 & 4) == 0) {
                        arg1->unk1F3 |= 0x80;
                    }
                }
            }
        } else {
            arg0->segment.unk18.half.upper += arg5;
            if (arg0->segment.unk18.half.upper >= duration) {
                arg0->segment.unk3B = 0;
                arg1->unk1F2 = 0;
                arg0->segment.unk18.half.upper = 40;
                arg1->unk1F3 = 0;
            }
        }
    } else {
        arg0->segment.unk18.half.upper = arg3;
        arg0->segment.unk3B = action;
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_80052B64.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80052D7C.s")

/**
 * Handle the steering input of all cars.
 * It takes the speed of the car, creating a curve for the rotational velocity to scale with.
 */
void handle_car_steering(Object_Racer *obj) {
    s32 velScale;
    f32 vel = obj->velocity;

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
    if (obj->drift_direction != 0) {
        velScale = vel * 68.0f;
    } else {
        velScale = vel * 58.0f;
    }
    // Set the steering velocity based on the car's steering value, scaled with the temp forward velocity value.
    gCurrentCarSteerVel -= (obj->unk1E1 * velScale);
    // If the car is reversing, then flip the steering.
    if (obj->velocity > 0.0f) {
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
void handle_car_velocity_control(Object_Racer *car) {
    if (car->throttle > 0.0) {
        car->throttle -= 0.1;
    }

    if (gCurrentCarInput & A_BUTTON) {
        car->throttle = 1.0f;
    }

    if (gCurrentCarInput & B_BUTTON) {
        if (car->brake < 1.0) {
            car->brake += 0.2;
        }
    } else {
        //! @bug Will cause a negative brake value resulting in higher velocity
        if (car->brake > 0.05) {
            car->brake -= 0.1;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_80053750.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80053E9C.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80054110.s")
GLOBAL_ASM("asm/non_matchings/racer/func_8005492C.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80054FD0.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80055A84.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80055EC0.s")

void play_char_horn_sound(Object *obj, Object_Racer *obj64) {
    if (get_filtered_cheats() & CHEAT_HORN_CHEAT) {
        // Play character voice instead of horn.
        func_800570B8(obj, 0x162, 8, 0x82);
    } else {
        // Play character's horn sound
        func_80057048(obj, obj64->characterId + 0x156);
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_8005698C.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80056E2C.s")

void func_80057048(Object *obj, s32 arg1) {
    Object_Racer *obj64 = &obj->unk64->racer;
    if (D_8011D55C != -1 && obj64->unk108 == 0) {
        func_80001EA8(arg1, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, NULL);
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

f32 func_80057220(Object* arg0, Object_Racer* arg1) {
    f32 speedMultiplier;
    s32 temp_v1;
    f32 bananas;
    f32 cap;
    s32 phi_a1;
    s32 sp28;

    speedMultiplier = 1.0f;
    if (D_8011D540 != 0) {
        speedMultiplier = 0.0f;
    }
    sp28 = func_800113AC();
    if (D_8011D540);
    if ((D_8011D540 > 0) && (D_8011D540 < 30) && (!arg1->unk1F4)) {
        temp_v1 = D_8011D540 - 14;
        if (gActivePlayerButtonPress & A_BUTTON) {
            if ((temp_v1 < 0) && (sp28 >= 0)) {
                temp_v1 = 0;
            }
            if (temp_v1 < 0) {
                temp_v1 = -temp_v1;
            }

            if ((gCurrentCarInput & Z_TRIG)) {
                if (temp_v1 < 2) {
                    temp_v1 = 0;
                }
            }

			phi_a1 = 24 - temp_v1;
            arg1->unk1D3 = func_8000C8B4(phi_a1 >> 1);
            if (phi_a1 == 24) {
                func_80057048(arg0, 34);
                arg1->unk1D3 = func_8000C8B4(20);
            }
            if ((s32) arg1->unk1D3 < func_8000C8B4(20)) {
                arg1->unk203 = 0;
            } else if ((s32) arg1->unk1D3 < func_8000C8B4(35)) {
                arg1->unk203 = 1;
            } else {
                arg1->unk203 = 2;
            }
            arg1->boost_sound |= 1;
            D_8011D560 = 7;
            D_8011D585 = arg1->unk1D3;
        }
        if ((arg1->playerIndex == -1) && (!arg1->unk1CC || (arg1->unk1CC == 1 && D_8011D585))) {
            if (D_8011D585) {
                arg1->unk1D3 = D_8011D585;
            } else {
                arg1->unk1D3 = func_8000C8B4(5);
            }
            if (arg1->unk1D3 < func_8000C8B4(20)) {
                arg1->unk203 = 0;
            } else if (arg1->unk1D3 < func_8000C8B4(35)) {
                arg1->unk203 = 1;
            } else {
                arg1->unk203 = 2;
            }
        }
    }
    if (arg1->unk1D3 && !D_8011D540 && sp28 && !arg1->unk1D8) {
         func_80072348(arg1->playerIndex, 6);
    }
    if ((D_8011D540 < 80) && gActivePlayerButtonPress & A_BUTTON) {
        arg1->unk1F4 = 1U;
    }
    if (D_8011D540 == 0) {
        if ((arg1->boost_sound & 1) != 0) {
            arg1->boost_sound = (u8) (arg1->boost_sound & 0xFFFE);
            func_800570B8(arg0, 354, 8, 130);
            func_80057048(arg0, 33);
        }
    }
    if ((arg1->boost_sound & 2) != 0) {
        arg1->boost_sound = (u8) (arg1->boost_sound & 0xFFFD);
    }
    bananas = arg1->bananas;
    // Cheats only apply to human players.
    if (arg1->playerIndex == PLAYER_COMPUTER) {
        bananas = arg1->unk124;
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

void func_800575EC(Object *obj, Object_Racer *obj64) {
    Matrix mf;

    D_8011D510.y_rotation = obj->segment.trans.y_rotation;
    D_8011D510.x_rotation = obj->segment.trans.x_rotation;
    D_8011D510.z_rotation = 0;
    D_8011D510.x_position = 0.0f;
    D_8011D510.y_position = 0.0f;
    D_8011D510.z_position = 0.0f;
    D_8011D510.scale = 1.0f;
    func_8006FC30(mf, &D_8011D510);
    guMtxXFMF(mf, 0.0f, 0.0f, 1.0f, &obj64->ox1, &obj64->oy1, &obj64->oz1);
    guMtxXFMF(mf, 0.0f, 1.0f, 0.0f, &obj64->ox2, &obj64->oy2, &obj64->oz2);
    guMtxXFMF(mf, 1.0f, 0.0f, 0.0f, &obj64->ox3, &obj64->oy3, &obj64->oz3);
}

GLOBAL_ASM("asm/non_matchings/racer/func_800576E0.s")

void func_800579B0(Object_Racer *racer, UNUSED s32 arg1, f32 arg2) {
    s32 temp, temp2;

    temp = gCurrentStickX - racer->unk1E1;
    temp2 = (temp * arg2) * 0.125;

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

GLOBAL_ASM("asm/non_matchings/racer/func_80057A40.s")

void func_800580B4(Object *obj, Object_Racer *obj64, s32 arg2, f32 arg3) {
    f32 xPos, yPos, zPos;
    if ((D_8011D55C != -1) && (obj64->unk1D8 != 1)) {
        if (arg2 != gCameraObject->unk36) {
            func_80057A40(obj, obj64, arg3);
            xPos = gCameraObject->trans.x_position;
            yPos = gCameraObject->trans.y_position;
            zPos = gCameraObject->trans.z_position;
            gCameraObject->unk36 = arg2;
            func_80057A40(obj, obj64, arg3);
            if (D_8011D540 == 0 && D_8011D582 == 0) {
                gCameraObject->x_velocity = xPos - gCameraObject->trans.x_position;
                gCameraObject->y_velocity = yPos - (gCameraObject->trans.y_position + gCameraObject->unk30);
                gCameraObject->z_velocity = zPos - gCameraObject->trans.z_position;
            }
        }
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_800581E8.s")

void func_80058B84(f32 arg0, Object* obj, Object_Racer* arg2) {
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
    arg2->unk196 = gCameraObject->trans.y_rotation;
}

void func_80058D5C(f32 arg0, Object *arg1, Object_Racer *arg2) {
    s32 sp34;
    Object *tempObj;
    f32 xDiff;
    f32 yDiff;
    f32 zDiff;
    f32 distance;

    sp34 = arg2->unk1D0;
    tempObj = func_8001BDD4(arg1, &sp34);
    if (!tempObj) {
        gCameraObject->unk36 = 5;
        return;
    }
    arg2->unk1D0 = sp34;
    gCameraObject->trans.x_position = tempObj->segment.trans.x_position;
    gCameraObject->trans.y_position = tempObj->segment.trans.y_position;
    gCameraObject->trans.z_position = tempObj->segment.trans.z_position;
    xDiff = gCameraObject->trans.x_position - arg1->segment.trans.x_position;
    yDiff = gCameraObject->trans.y_position - arg1->segment.trans.y_position;
    zDiff = gCameraObject->trans.z_position - arg1->segment.trans.z_position;
    distance = sqrtf((xDiff * xDiff) + (zDiff * zDiff));
    gCameraObject->trans.y_rotation = (s16) (0x8000 - func_8007066C((s32) xDiff, (s32) zDiff));
    gCameraObject->trans.x_rotation = func_8007066C((s32) yDiff, (s32) distance);
    gCameraObject->trans.z_rotation = 0;
    gCameraObject->unk34 = get_level_segment_index_from_position(gCameraObject->trans.x_position, arg2->oy1, gCameraObject->trans.z_position);
}

void func_80058F44(f32 arg0, struct Object *arg1, struct Object *arg2)
{
    s32 temp_f4;
    f32 diffX;
    f32 diffZ;
    temp_f4 = (s32) arg0;
    diffX = gCameraObject->trans.x_position - arg1->segment.trans.x_position;
    diffZ = gCameraObject->trans.z_position - arg1->segment.trans.z_position;
    gCameraObject->trans.y_rotation += ((((-func_8007066C((s32) diffX, (s32) diffZ)) -
                                    gCameraObject->trans.y_rotation) + 0x8000) * temp_f4) >> 4;
    gCameraObject->trans.z_rotation -= (((s32) (gCameraObject->trans.z_rotation * temp_f4)) >> 4);
    gCameraObject->unk34 = get_level_segment_index_from_position(gCameraObject->trans.x_position,
                            arg2->segment.unk3C_a.unk3C_f, gCameraObject->trans.z_position);
}

void func_80059080(UNUSED Object *obj, Object_Racer *racer, f32 *velX, f32 *velY, f32 *velZ) {
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
        *velX = catmull_rom_interpolation(splineX, destReached, magnitude);
        *velY = catmull_rom_interpolation(splineY, destReached, magnitude);
        *velZ = catmull_rom_interpolation(splineZ, destReached, magnitude);
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

void func_8005C270(unk8005C270 *arg0) {
    s32 temp = func_8001BA64();

    arg0->unk192--;
    if (arg0->unk192 < 0) {
        arg0->unk192 += temp;
        if (arg0->unk193 > 0) {
            arg0->unk193--;
        }
    }

    if (arg0->unk190 >= -31999) {
        arg0->unk190--;
    }
}
