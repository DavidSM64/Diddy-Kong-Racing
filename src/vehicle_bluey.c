/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005D0D0 */

#include "vehicle_bluey.h"

#include "types.h"
#include "macros.h"
#include "math_util.h"
#include "objects.h"
#include "object_functions.h"
#include "unknown_008C40.h"
#include "racer.h"
#include "unknown_05CEF0.h"
#include "particles.h"

/************ .data ************/

u16 D_800DCE00[16] = {
    0x022D, 0x00A7, 0x00A8, 0x00B7, 0x00B8, 0x00F4, 0x00F5, 0x00FA, 0x00FB, 0x0229, 0x022A, 0x002E, 0x002F, 0x0030, 0x0000, 0x0000
};

u16 D_800DCE20[16] = {
    0x022C, 0x00A5, 0x00A6, 0x00B5, 0x00B6, 0x00F2, 0x00F3, 0x00F8, 0x00F9, 0x0227, 0x0228, 0x002E, 0x002F, 0x0030, 0x0000, 0x0000
};

/*******************************/

/************ .bss ************/

s8 D_8011D5D0;
s8 D_8011D5D1;

// These 3 might be a file boundary.
s32 D_8011D5D4;
s32 D_8011D5D8;
s32 D_8011D5DC;

/******************************/

/**
 * Top level function for the Bluey vehicle, as seen in the Snowflake Mountain boss stage.
*/
void update_bluey(s32 updateRate, f32 updateRateF, Object* obj, Object_Racer* racer, u32* input, u32* buttonsPressed, s32* startTimer) {
    s16 sp5E;
    s16 sp5C;
    s16 sp5A;
    f32 xDiff;
    f32 zDiff;
    s32 var_v0;
    s32 sp48;
    ObjectModel *objModel;
    Object_68* obj68;
    s32 sp3C;
    UNUSED s32 pad;
    Object* firstRacerObj;

    func_8005CA78(D_800DCE00);
    *buttonsPressed &= ~R_TRIG;
    *input &= ~R_TRIG;
    sp5E = obj->segment.unk38.byte.unk3B;
    sp5C = obj->segment.animFrame;
    sp5A = racer->unk16A;
    if (racer->raceFinished == 1 && func_80023568()) {
        func_80021400(0x82);
        racer->raceFinished++;
    }
    sp48 = *startTimer;
    if (sp48 == 100) {
        D_8011D5D0 = 0;
    }
    if (racer->playerIndex == PLAYER_COMPUTER) {
        if (*startTimer != 100) {
            *startTimer -= 15;
            if (*startTimer  < 0) {
                if (D_8011D5D1 == 0) {
                    func_8005CB04(0);
                    racer->boostTimer = 3;
                }
                D_8011D5D1 = 1;
                *startTimer = 0;
                *input |= A_BUTTON;
            } else {
                D_8011D5D1 = 0;
            }
        }
    }
    
    func_8004F7F4(updateRate, updateRateF, obj, racer);
    *startTimer = sp48;
    racer->lateral_velocity = 0.0f;
    racer->unk16A = sp5A;
    obj->segment.unk38.byte.unk3B = (s8) sp5E;
    obj->segment.animFrame = sp5C;
    if (racer->attackType != 0) {
        if (obj->segment.unk38.byte.unk3B != 4) {
            racer->unk1CD = obj->segment.unk38.byte.unk3B;
            obj->segment.unk38.byte.unk3B = 4;
            racer->unkC = 0.0f;
            func_8005CB04(1);
            play_sound_global(SOUND_EXPLOSION, NULL);
            func_80069F28(12.0f);
            racer->attackType = 0;
            racer->velocity *= 0.3;
            obj->segment.y_velocity += 7.5;
        }
    }
    if (racer->unk148 != NULL) {
        xDiff = obj->segment.x_velocity * obj->segment.x_velocity;
        zDiff = obj->segment.z_velocity * obj->segment.z_velocity;
        racer->velocity = -sqrtf((xDiff * xDiff) + (zDiff * zDiff));
    }
    sp3C = 0;
    if ((find_next_checkpoint_node(racer->checkpoint, racer->unk1C8))->unk36[racer->unk1CA] == 1) {
        sp3C = 1;
    }
    if (obj->segment.unk38.byte.unk3B != 4) {
        if (racer->velocity < -2.0) {
            if (sp3C) {
                if (racer->unk1CD != 3) {
                    racer->unkC = 40.0f;
                }
                obj->segment.unk38.byte.unk3B = 3;
                var_v0 = racer->steerAngle;
                var_v0 *= 2;
                var_v0 = 40 - var_v0;
                if (var_v0 < 0) {
                    var_v0 = 0;
                }
                if (var_v0 > 73) {
                    var_v0 = 73;
                }
                racer->unk1CD = 3;
                racer->unkC += (var_v0 - racer->unkC) * 0.25;
            } else {
                racer->unk1CD = 0;
                obj->segment.unk38.byte.unk3B = 0;
                racer->unkC -= (racer->velocity * updateRateF) * 0.5;
            }
        } else if (racer->velocity < -0.1 || 0.1 < racer->velocity) {
            racer->unk1CD = 1;
            obj->segment.unk38.byte.unk3B = 1;
            racer->unkC -= racer->velocity * updateRateF * 2;
        } else {
            racer->unk1CD = 2;
            obj->segment.unk38.byte.unk3B = 2;
            racer->unkC += updateRateF * 1.0;
        }
    } else {
        racer->unkC += updateRateF * 1.0;
    }
    obj68 = *obj->unk68;
    objModel = obj68->objModel;
    xDiff = (objModel->animations[obj->segment.unk38.byte.unk3B].unk4 * 16) - 17;
    while (racer->unkC < 0.0f) {
        racer->unkC += xDiff;
        obj68->unk10 = -1;
    }
    while (xDiff < racer->unkC) {
        racer->unkC -= xDiff;
        obj68->unk10 = -1;
    }
    if ((obj68->unk10 == -1) && (obj->segment.unk38.byte.unk3B == 4)) {
        obj->segment.unk38.byte.unk3B = racer->unk1CD;
    }
    sp5C = obj->segment.animFrame;
    obj->segment.animFrame = racer->unkC;
    obj->unk74 = 0;
    if (obj->segment.unk38.byte.unk3B == 0) {
        func_800113CC(obj, 2, sp5C, 172, 173);
        obj->unk74 |= 3;
    }
    func_800AFC3C(obj, updateRate);
    func_8005D048(obj, racer, 0x28);
    firstRacerObj = get_racer_object(0);
    xDiff = firstRacerObj->segment.trans.x_position - obj->segment.trans.x_position;
    zDiff = firstRacerObj->segment.trans.z_position - obj->segment.trans.z_position;
    if (sqrtf((xDiff * xDiff) + (zDiff * zDiff)) < 700.0) {
        sp48 = (arctan2_f(xDiff, zDiff) - (obj->segment.trans.y_rotation & 0xFFFF)) + 0x8000;
        if (sp48 > 0x8000) {
            sp48 -= 0xFFFF;
        }
        if (sp48 < -0x8000) {
            sp48 += 0xFFFF;
        }
        if (sp48 > 0xC00) {
            sp48 = 0xC00;
        }
        if (sp48 < -0xC00) {
            sp48 = -0xC00;
        }
        racer->unk16C = sp48;
    }
    if (obj->segment.unk38.byte.unk3B == 1) {
        if ((racer->unk1E7 & 0x1F) < 10) {
            racer->unk16C >>= 1;
        }
    }
    if (obj->segment.unk38.byte.unk3B == 3) {
        racer->unk16C = 0;
    }
    racer = (Object_Racer *) firstRacerObj->unk64;
    if (obj == firstRacerObj->interactObj->obj && firstRacerObj->interactObj->unk14 & 8 && obj->segment.unk38.byte.unk3B == 1) {
        racer->attackType = ATTACK_SQUISHED;
    }
    if (racer->raceFinished) {
        if (D_8011D5D0 == 0) {
            D_8011D5D0 = 1;
            func_8005CB68(racer, &D_8011D5D0);
        }
    }
}
