/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005EA90 */

#include "vehicle_wizpig.h"

#include "types.h"
#include "racer.h"
#include "macros.h"
#include "objects.h"
#include "unknown_05CEF0.h"
#include "object_functions.h"
#include "unknown_05DCD0.h"
#include "particles.h"

/************ .data ************/

s16 D_800DCE60[14] = {
    0x022C, 0x00A5, 0x00A6, 0x0057, 0x0051, 0x006D, 0x0052, 0x00F8, 0x00F9, 0x0227, 0x0228, 0x002E, 0x002F, 0x0030
};

/*******************************/

/************ .bss ************/

s8 D_8011D600;
s8 D_8011D601;

/******************************/

/**
 * Top level function for updating the wizpig vehicle from the first boss race against him.
*/
void update_wizpig(s32 updateRate, f32 updateRateF, Object* obj, Object_Racer* racer, u32* input, u32* buttonsPressed, s32* startTimer) {
    s16 sp3E;
    s16 sp3C;
    s16 sp3A;
    s16 sp38;
    f32 zDiff;
    f32 xDiff;
    f32 var_f12;
    s32 sp28;
    Object* firstRacerObj;
    ObjectModel* objModel;
    Object_68* gfxData;

    func_8005CA78((u16* ) D_800DCE60);
    racer->unk1EC = 0;
    sp3E = obj->segment.unk38.byte.unk3B;
    sp3C = obj->segment.animFrame;
    sp3A = racer->unk16A;
    if (racer->velocity < 0.3 && -0.3 < racer->velocity) {
        *buttonsPressed = 0;
    }
    if (racer->raceFinished == 1 && func_80023568() != 0) {
        func_80021400(0x82);
        racer->raceFinished++;
    }
    sp28 = *startTimer;
    if (sp28 == 0x64) {
        D_8011D600 = 0;
    }
    racer->unk1F5 = 0;
    if (racer->playerIndex == PLAYER_COMPUTER) {
        if (*startTimer != 100) {
            *startTimer -= 30;
            if (*startTimer < 0) {
                if (D_8011D601 == 0) {
                    func_8005CB04(0);
                    racer->boostTimer = 0xA;
                }
                D_8011D601 = 1;
                *startTimer = 0;
                *input |= 0x8000;
            } else {
                D_8011D601 = 0;
            }
        }
    }
    racer->vehicleID = VEHICLE_WIZPIG;
    func_80049794(updateRate, updateRateF, obj, racer);
    racer->vehicleID = racer->unk1D7;
    *startTimer = sp28;
    obj->unk74 = 0;
    racer->unk16A = sp3A;
    obj->segment.unk38.byte.unk3B = sp3E;
    obj->segment.animFrame = sp3C;
    if (racer->attackType != 0 && obj->segment.unk38.byte.unk3B != 5) {
        func_8005CB04(1);
        play_sound_global(0x11U, NULL);
        func_80069F28(12.0f);
        obj->segment.unk38.byte.unk3B = 5;
        obj->segment.x_velocity *= 0.4;
        obj->segment.z_velocity *= 0.4;
        racer->unkC = 0.0f;
        obj->segment.y_velocity += 4.0;
    }
    racer->attackType = 0;
    if (racer->unk148 != NULL) {
        xDiff = obj->segment.x_velocity * obj->segment.x_velocity;
        zDiff = (obj->segment.z_velocity * obj->segment.z_velocity);
        racer->velocity = -sqrtf((xDiff * xDiff) + (zDiff * zDiff));
        if (racer->velocity > -0.5) {
            racer->velocity = 0.0f;
            obj->segment.x_velocity = 0.0f;
            obj->segment.y_velocity = 0.0f;
            obj->segment.z_velocity = 0.0f;
        }
    }
    sp38 = 0;
    sp38 = sp38;
    if (find_next_checkpoint_node(racer->checkpoint, racer->unk1C8)->unk36[racer->unk1CA] == 1) {
        sp38 = 1;
    }
    racer->x_rotation_offset = -obj->segment.trans.x_rotation;
    gfxData = *obj->unk68;
    objModel = gfxData->objModel;
    xDiff = (objModel->animations[obj->segment.unk38.byte.unk3B].unk4 * 0x10) - 0x11;
    var_f12 = (racer->velocity * updateRateF) * 0.45;
    if (var_f12 <= 0.0) {
        if (var_f12 > -2.0) {
            var_f12 = -2.0f;
        }
    } else if (var_f12 < 2.0) {
        var_f12 = 2.0f;
    }
    switch (obj->segment.unk38.byte.unk3B) {
    case 0:
        racer->unk1CD = 0;
        racer->unkC += 1.0 * updateRateF;
        break;
    case 1:
        if (racer->unk1CD == 2) {
            racer->unkC += var_f12;
        } else {
            racer->unkC -= var_f12;
        }
        break;
    case 2:
        racer->unk1CD = 2;
        racer->unkC -= var_f12;
        break;
    case 3:
        if (racer->unk1CD == 4) {
            racer->unkC -= 2.0 * updateRateF;
        } else {
            racer->unkC += 2.0 * updateRateF;
        }
        break;
    case 4:
        racer->unk1CD = 4;
        racer->unkC += 2.0 * updateRateF;
        break;
    case 5:
        racer->unkC += 2.0 * updateRateF;
        break;
    default:
        break;
    }
    
    while (xDiff <= racer->unkC) {
        racer->unkC -= xDiff;
        gfxData->unk10 = -1;
    }
    while (racer->unkC <= 0.0f){
        racer->unkC += xDiff;
        gfxData->unk10 = -1;
    }
    if (obj->segment.unk38.byte.unk3B == 2 && sp38 != 0) {
        obj->segment.unk38.byte.unk3B = 3;
        racer->unkC = 0.0f;
    }
    if (gfxData->unk10 == -1 || obj->segment.unk38.byte.unk3B == 0) {
        if (obj->segment.unk38.byte.unk3B == 5) {
            obj->segment.unk38.byte.unk3B = (s8) racer->unk1CD;
            racer->unkC = 0.0f;
        } else if (obj->segment.unk38.byte.unk3B == 1) {
            if (racer->unk1CD == 0) {
                obj->segment.unk38.byte.unk3B = 2;
            } else {
                obj->segment.unk38.byte.unk3B = 0;
            }
        } else if (obj->segment.unk38.byte.unk3B == 3) {
            if (racer->unk1CD == 4) {
                obj->segment.unk38.byte.unk3B = 2;
            } else {
                obj->segment.unk38.byte.unk3B = 4;
            }
        } else {
            if (-0.1 < racer->velocity && racer->velocity < 0.1) {
                if (obj->segment.unk38.byte.unk3B == 2) {
                    obj->segment.unk38.byte.unk3B = 1;
                    racer->unkC = (objModel->animations[obj->segment.unk38.byte.unk3B].unk4 * 0x10) - 0x11;
                } else {
                    obj->segment.unk38.byte.unk3B = 0;
                }
            } else {
                if (obj->segment.unk38.byte.unk3B == 0) {
                    obj->segment.unk38.byte.unk3B = 1;
                    racer->unkC = 0.0f;
                }
                if ((obj->segment.unk38.byte.unk3B == 4) && (sp38 == 0)) {
                    obj->segment.unk38.byte.unk3B = 3;
                    racer->unkC = (objModel->animations[obj->segment.unk38.byte.unk3B].unk4 * 0x10) - 0x11;
                }
            }
        }
    }
    sp3C = obj->segment.animFrame;
    obj->segment.animFrame = racer->unkC;
    obj->unk74 = 0;
    if (obj->segment.unk38.byte.unk3B == 2) {
        func_800113CC(obj, 2, sp3C, 0xAC, 0xAD);
    }
    if (racer->playerIndex == -1) {
        if (func_80023568() != 0) {
            func_8005E204(obj, racer, 0x42C80000, 0x89, 0xA5);
        }
    }
    func_800AFC3C(obj, updateRate);
    func_8005D048(obj, racer, 0x28);
    firstRacerObj = get_racer_object(0);
    racer = (Object_Racer *) firstRacerObj->unk64;
    if (obj == firstRacerObj->interactObj->obj && firstRacerObj->interactObj->unk14 & 8 && obj->segment.unk38.byte.unk3B == 1) {
        racer->attackType = 4;
    }
    if (racer->raceFinished) {
        if (D_8011D600 == 0) {
            D_8011D600 = 1;
            func_8005CB68(racer, &D_8011D600);
        }
    }
}
