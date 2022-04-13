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
s32 D_8011D534;
s32 D_8011D538;
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
s32 D_8011D560;
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
s8 D_8011D586;
s8 D_8011D587;
s8 D_8011D588;
s8 D_8011D589;
s8 D_8011D58A;
s8 D_8011D58B;
s8 D_8011D58C;
s8 D_8011D58D;
s8 D_8011D58E;
s8 D_8011D58F;
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
s8 D_8011D5BA;
s8 D_8011D5BB;
s8 D_8011D5BC;

/******************************/

GLOBAL_ASM("asm/non_matchings/racer/func_80042D20.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80043ECC.s")

typedef struct Object_64_80044170 {
    char unk0[0x2C];
    f32 unk2C;
    char unk30[0x124];
    s32 unk154;
    char unk158[0x72];
    s8 unk1CA;
    char unk1CB[0x3];
    u8 unk1CE;
    char unk1CF[0x13];
    s8 unk1E2;
    char unk1E3[0x30];
    s8 unk213;
    s8 unk214;
    s8 unk215;
} Object_64_80044170;

// Might be the main loop for the AI racers.
void func_80044170(Object *arg0, Object_64_80044170 *arg1, s32 arg2) {
    s32 raceType;

    raceType = get_current_level_race_type();

    switch (raceType) {
        case RACE_TYPE_CHALLENGE_BATTLE:
        case RACE_TYPE_CHALLENGE_BANANAS:
            func_8004447C(arg0, arg1, arg2);
            break;
        case RACE_TYPE_CHALLENGE_EGGS:
            func_800452A0(arg0, arg1, arg2);
            break;
        default:
            // last argument was required for match, might not really exist
            func_80045C48(arg0, arg1, arg2, raceType);
            break;
    }

    if (arg1->unk214 == 0 && arg1->unk2C < -0.5) {
        arg1->unk215 -= arg2;
        if (arg1->unk215 < 0) {
            arg1->unk215 = 0;
        }
    }

    if (arg1->unk2C > -1.0 && arg1->unk214 == 0 && D_8011D540 == 0 && D_8011D544 == 0.0f && arg1->unk1E2 != 0 && arg1->unk215 == 0) {
        arg1->unk213 += arg2;

        if (arg1->unk213 > 60) {
            arg1->unk213 = 0;
            arg1->unk214 = 60;
            arg1->unk215 = 120;

            if ((raceType & RACE_TYPE_CHALLENGE) == 0) {
                arg1->unk1CA = (arg1->unk1CA + 1) & 3;
            } else if (raceType == RACE_TYPE_CHALLENGE_BATTLE || raceType == RACE_TYPE_CHALLENGE_BANANAS) {
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

    if (arg1->unk214 != 0) {
        D_8011D534 *= -1;
        gCurrentCarInput &= ~A_BUTTON;
        D_8011D538 = -50;
        gCurrentCarInput |= B_BUTTON;
    }

    if (D_8011D534 > 75) {
        D_8011D534 = 75;
    }

    if (D_8011D534 < -75) {
        D_8011D534 = -75;
    }

    if (D_8011D538 > 75) {
        D_8011D538 = 75;
    }

    if (D_8011D538 < -75) {
        D_8011D538 = -75;
    }
}

s32 func_80044450(s32 arg0) {
    return get_random_number_from_range(0, 99) < arg0;
}

GLOBAL_ASM("asm/non_matchings/racer/func_8004447C.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80045128.s")
GLOBAL_ASM("asm/non_matchings/racer/func_800452A0.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80045C48.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80046524.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80048C7C.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80048E64.s")
GLOBAL_ASM("asm/non_matchings/racer/func_800494E0.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80049794.s")

// Something Plane related.
void func_8004C0A0(s32 arg0, Object *planeObj, Object_64_8004C0A0 *planeObj64) {
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

void func_8004C140(Object *obj, Object_64_8004C140 *obj64) {
    s8 phi_v1;
    s8 temp;
    if (obj64->unk0 == -1) {
        phi_v1 = 0;
    } else {
        phi_v1 = obj64->unk185;
    }
    temp = obj64->unk187;
    if (temp == 0 || obj64->unk18E > 0) {
        obj64->unk187 = 0;
        return;
    }
    if (temp != 4) {
        func_800576E0(obj, obj64, 2);
    }
    obj64->unk18C = 0x168;
    if (obj64->unk1C9 == 8) {
        obj64->unk1C9 = 0;
    }
    if (obj64->unk1D6 < 5) {
        func_800570B8(obj, 0x1C2, 8, 0x81);
        switch (obj64->unk187) {
            case 1:
            case 2:
                if (phi_v1 != 0) {
                    obj64->unk1DB = 0x28;
                } else {
                    obj64->unk1DB = 0x3C;
                }
                break;
            case 3:
                if (phi_v1 != 0) {
                    obj64->unk1DB = 0x28;
                } else {
                    obj64->unk1DB = 0x3C;
                }
                break;
            case 6:
                obj64->unk204 = 0x78;
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

void func_8004D95C(s32 arg0, s32 arg1, Object *obj, Object_64_8004D95C *obj64) {
    s16 sp26;

    if (obj64->unk118 != 0) {
        func_80006AC8(obj);
    }
    if ((func_8002341C() != 0) && (obj64->unk1D6 == 0xA)) {
        obj->unk4C->unk14 = 0;
    }
    sp26 = obj->segment.unk18;
    obj64->unk1D6 = 0xA;
    func_80049794(arg0, arg1, obj, obj64);
    obj64->unk1D6 = obj64->unk1D7;
    obj->segment.unk3B = 0;
    if (obj64->unk1D6 == 0xA) {
        if (obj64->someObject != NULL) {
            obj64->someObject->segment.trans.x_position = obj->segment.trans.x_position;
            obj64->someObject->segment.trans.y_position = obj->segment.trans.y_position;
            obj64->someObject->segment.trans.z_position = obj->segment.trans.z_position;
            obj64->someObject->segment.unk2C.half.lower = obj->segment.unk2C.half.lower;
            obj64->someObject->segment.trans.y_rotation = obj->segment.trans.y_rotation;
            obj64->someObject->segment.trans.x_rotation = obj->segment.trans.x_rotation;
            obj64->someObject->segment.trans.z_rotation = obj->segment.trans.z_rotation;
            obj->segment.unk3B = 0;
            obj->segment.unk18 = sp26 + arg0;
            func_80061C0C(obj);
        }
    }
}

GLOBAL_ASM("asm/non_matchings/racer/obj_init_racer.s")
GLOBAL_ASM("asm/non_matchings/racer/func_8004DE38.s")

void func_8004F77C(unk8004F77C *arg0) {
    s32 temp;

    arg0->flags &= ~0x80;
    if ((gCurrentCarInput & B_BUTTON) != 0) {
        arg0->flags |= 0x80;
    }

    temp = arg0->flags & 0xF;
    if ((arg0->flags & 0xC0) != 0) {
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

#ifdef NON_EQUIVALENT

typedef struct Object_64_80050754 {
            u8 unk0[0x2C];
            f32 unk2C;
            f32 unk30;
            u8 unk34[0x114];
/* 0x148 */ Object *someObj;
            u8 unk14C[0x54];
/* 0x1A0 */ s16 unk1A0;
/* 0x1A2 */ s16 unk1A2;
/* 0x1A4 */ s16 unk1A4;
            u8 unk1A6[0x4C];
/* 0x1F2 */ s8 unk1F2;
} Object_64_80050754;

// Mainly has regalloc issues.
void func_80050754(Object *obj, Object_64_80050754 *obj64, f32 arg2) {
    f32 xDiff, yDiff, zDiff;
    Object *someObj;

    obj->segment.unk3B = 0;
    obj->segment.unk18 = 0x28;
    someObj = obj64->someObj;
    xDiff = someObj->segment.trans.x_position - obj->segment.trans.x_position;
    yDiff = someObj->segment.trans.y_position - obj->segment.trans.y_position;
    zDiff = someObj->segment.trans.z_position - obj->segment.trans.z_position;
    func_80011570(obj, xDiff, yDiff, zDiff);
    obj->segment.trans.y_rotation = obj64->someObj->segment.trans.y_rotation;
    obj->segment.trans.x_rotation = obj64->someObj->segment.trans.x_rotation;
    obj->segment.trans.z_rotation = obj64->someObj->segment.trans.z_rotation;
    obj64->unk1A4 = obj->segment.trans.z_rotation;
    obj64->unk1A0 = obj->segment.trans.y_rotation;
    obj->segment.x_velocity = xDiff / arg2;
    obj->segment.y_velocity = yDiff / arg2;
    obj->segment.z_velocity = zDiff / arg2;
    obj64->unk1F2 = 0;
    obj64->unk2C = 0.0f;
    obj64->unk30 = 0.0f;
}
#else
GLOBAL_ASM("asm/non_matchings/racer/func_80050754.s")
#endif

GLOBAL_ASM("asm/non_matchings/racer/func_80050850.s")
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

GLOBAL_ASM("asm/non_matchings/racer/func_800521C4.s")

// Ran by the AI. Seems to be direction related of some sorts.
void func_8005234C(unk8005234C *arg0) {
    arg0->unk16C -= arg0->unk16C >> 3;
    if (arg0->unk16C >= -9 && arg0->unk16C < 10) { // Deadzone?
        arg0->unk16C = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_80052388.s")
GLOBAL_ASM("asm/non_matchings/racer/func_8005250C.s")

// action seems to be 1 when you're reversing, if you hit the horn, it's 4, and if you introduce yourself to a brick wall, it's 3 then 6.
// unk18 seems to be a counter that's used as a baseline for animations
// unk3B mostly mirrors what arg2 is, but it gets set to 0
// I've yet to find a scenario where D_8011D55C is not 0.
// I've also yet to find a scenario where the action is < 3
// arg6 is set to 6 when honking, but 7 when reversing and not honking and 0 when crashing.
// arg7 seems to be based on direction????
void func_80052988(Object *arg0, Object_64 *arg1, s32 action, s32 arg3, s32 duration, s32 arg5, s32 arg6, s32 arg7) {
    arg5 *= arg7;

    if ((D_8011D55C == -1) && (action >= 3)) {
        arg0->segment.unk3B = 0;
        arg1->unk1F2 = 0;
        //render_printf("set0\n");
    } else if (arg0->segment.unk3B == 0) {
        if (arg6 & 1) {
            if (arg0->segment.unk18 >= 41) {
                arg0->segment.unk18 -= arg7 * 4;
                if (arg0->segment.unk18 < 41) {
                    arg0->segment.unk3B = action;
                    arg0->segment.unk18 = arg3;
                }
                //render_printf("set1\n");
            } else {
                arg0->segment.unk18 += arg7 * 4;
                if (arg0->segment.unk18 >= 40) {
                    arg0->segment.unk3B = action;
                    arg0->segment.unk18 = arg3;
                }
                //render_printf("set2\n");
            }
        } else { // Set active flag, whether it's from just crashing, or beginning to honk.
            arg0->segment.unk3B = action;
            arg0->segment.unk18 = arg3;
            arg1->unk1F3 &= ~0x80;
        }
    } else if (arg0->segment.unk3B == action) {
        if (arg6 & 2) {
            if (arg1->unk1F3 & 0x80) { // Stop honking or reversing.
                arg0->segment.unk18 -= arg5;
                if (arg0->segment.unk18 <= 0) {
                    arg0->segment.unk3B = 0;
                    arg1->unk1F2 = 0;
                    arg0->segment.unk18 = 40;
                    arg1->unk1F3 = 0;
                }
            } else { // Actively reversing or honking or boosting, possibly a velocity modifier, have found it's also set when recovering from getting hit by a rocket or spike trap
                arg0->segment.unk18 += arg5;
                // Keeps the timer below the duration value, while actively held.
                if (arg0->segment.unk18 >= duration) {
                    arg0->segment.unk18 = duration - 1;
                    if ((arg6 & 4) == 0) {
                        arg1->unk1F3 |= 0x80;
                    }
                }
            }
        } else { // Crash recoil
            arg0->segment.unk18 += arg5;
            if (arg0->segment.unk18 >= duration) {
                arg0->segment.unk3B = 0;
                arg1->unk1F2 = 0;
                arg0->segment.unk18 = 40;
                arg1->unk1F3 = 0;
            }
        }
    } else { // Haven't seen this trigger yet.
        arg0->segment.unk18 = arg3;
        arg0->segment.unk3B = action;
    }
    /*render_printf("D_8011D55C %d\n", D_8011D55C);
    render_printf("action %d\n", action);
    render_printf("unk18 %d\n", arg0->segment.unk18);
    render_printf("unk3B %d\n", arg0->segment.unk3B);
    render_printf("arg6 %d\n", arg6);
    render_printf("arg7 %d\n", arg7);*/
}

GLOBAL_ASM("asm/non_matchings/racer/func_80052B64.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80052D7C.s")

/**
 * Handle the steering input of all cars.
 * It takes the speed of the car, creating a curve for the rotational velocity to scale with.
 */
void handle_car_steering(Object_64_80053478 *car) {
    s32 velScale;
    f32 vel = car->unk2C;

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
    if (car->unk1E6 != 0) {
        velScale = vel * 68.0f;
    } else {
        velScale = vel * 58.0f;
    }
    // Set the steering velocity based on the car's steering value, scaled with the temp forward velocity value.
    gCurrentCarSteerVel -= (car->unk1E1 * velScale);
    // If the car is reversing, then flip the steering.
    if (car->unk2C > 0.0f) {
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
void handle_car_velocity_control(Object_64 *car) {
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

void play_char_horn_sound(Object *obj, Object_64 *obj64) {
    if (get_filtered_cheats() & CHEAT_HORN_CHEAT) {
        // Play character voice instead of horn.
        func_800570B8(obj, 0x162, 8, 0x82);
    } else {
        // Play character's horn sound
        func_80057048(obj, obj64->unk0_a.unk0_b.unk3 + 0x156);
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_8005698C.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80056E2C.s")

void func_80057048(Object *obj, s32 arg1) {
    Object_64 *obj64 = obj->unk64;
    if (D_8011D55C != -1 && obj64->unk108 == 0) {
        func_80001EA8(arg1, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, NULL);
    }
}

void func_800570A4(Object *obj, s32 arg1, s32 arg2) {
    Object_64_unk800570A4 *temp = obj->unk64;
    temp->unk20E = arg1;
    temp->unk210 = arg2;
}

#ifdef NON_EQUIVALENT
typedef struct Object_64_800570B8 {
    u8 pad0[3];
    s8 unk3;
    u8 pad4[0x20];
    s32 unk24;
    u16 unk28;
    u16 unk2A;
    u8 pad2C[0xDC];
    s32 unk108;
} Object_64_800570B8;

void func_800570B8(Object *obj, s32 arg1, s32 arg2, s32 arg3) {
    s32 phi_t0;
    Object_64_800570B8 *obj64;

    obj64 = obj->unk64;
    if ((obj64->unk108 == 0) && ((!(arg3 & 0x80)) || (D_8011D55C != -1))) {
        if (arg3 == 2) {
            if ((obj64->unk24 != 0) && (arg1 != obj64->unk2A)) {
                func_800096F8(obj64->unk24);
                obj64->unk24 = 0;
            }
        }
        if (obj64->unk24 == 0) {
            if (arg3 != 3 || get_random_number_from_range(0, 1) != 0) {
                obj64->unk2A = arg1;
                arg1 += obj64->unk3;
                arg2--;
                phi_t0 = (get_random_number_from_range(0, arg2) * 12) + arg1;
                if (arg2 > 0) {
                    while (phi_t0 == obj64->unk28) {
                        phi_t0 = (get_random_number_from_range(0, arg2) * 12) + arg1;
                    }
                }
                //sp34 = phi_t0;
                func_80009558(phi_t0, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, &obj64->unk24);
                obj64->unk28 = phi_t0;
            }
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/racer/func_800570B8.s")
#endif

GLOBAL_ASM("asm/non_matchings/racer/func_80057220.s")

void func_800575EC(Object *obj, Object_64_800575EC *obj64) {
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

void func_800579B0(unk800579B0 *arg0, UNUSED s32 arg1, f32 arg2) {
    s32 temp, temp2;

    temp = D_8011D534 - arg0->unk1E1;
    temp2 = (s32)((f64)((f32)temp * arg2) * 0.125);

    if (temp != 0 && temp2 == 0) {
        if (temp > 0) {
            temp2 = 1;
        }
        if (temp < 0) {
            temp2 = -1;
        }
    }

    arg0->unk1E1 = arg0->unk1E1 + temp2;
}

GLOBAL_ASM("asm/non_matchings/racer/func_80057A40.s")

void func_800580B4(Object *obj, Object_64_800580B4 *obj64, s32 arg2, f32 arg3) {
    f32 xPos, yPos, zPos;
    if ((D_8011D55C != -1) && (obj64->unk1D8 != 1)) {
        if (arg2 != gCameraObject->unk36) {
            func_80057A40(obj, obj64, arg3);
            xPos = gCameraObject->x_position;
            yPos = gCameraObject->y_position;
            zPos = gCameraObject->z_position;
            gCameraObject->unk36 = arg2;
            func_80057A40(obj, obj64, arg3);
            if (D_8011D540 == 0 && D_8011D582 == 0) {
                gCameraObject->unk24 = xPos - gCameraObject->x_position;
                gCameraObject->unk28 = yPos - (gCameraObject->y_position + gCameraObject->unk30);
                gCameraObject->unk2C = zPos - gCameraObject->z_position;
            }
        }
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_800581E8.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80058B84.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80058D5C.s")

#ifdef NON_EQUIVALENT
void func_80058F44(f32 arg0, Object *arg1, Object *arg2) {
    s32 temp0, temp1;
    temp0 = (s32)arg0;
    temp1 = func_8007066C(gCameraObject->x_position - arg1->segment.trans.x_position, gCameraObject->z_position - arg1->segment.trans.z_position);
    gCameraObject->y_rotation += (((-temp1 - gCameraObject->y_rotation) + 0x8000) * temp0) >> 4;
    gCameraObject->z_rotation -= (gCameraObject->z_rotation * temp0) >> 4;
    gCameraObject->unk34 = get_level_segment_index_from_position(gCameraObject->x_position, arg2->segment.unk3C_a.unk3C_f, gCameraObject->z_position);
}
#else
GLOBAL_ASM("asm/non_matchings/racer/func_80058F44.s")
#endif

GLOBAL_ASM("asm/non_matchings/racer/func_80059080.s")
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
