/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005D820 */

#include "vehicle_misc.h"

#include "types.h"
#include "macros.h"
#include "math_util.h"
#include "objects.h"
#include "object_functions.h"
#include "unknown_008C40.h"
#include "racer.h"
#include "particles.h"

/************ .bss ************/

s8 D_8011D5E0;
s8 D_8011D5E1;

/******************************/

/**
 * Top level function for updating the "Smokey" vehicle as seen in the Dragon Forest boss stage.
 * Also controls the pteradactyl found in Dino domain, from when it had a larger role ingame.
*/
void update_smokey(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, s32 *stickMag, s32 *startTimer) {
    s16 sp5E;
    s16 sp5C;
    s16 sp5A;
    f32 xDiff;
    f32 zDiff;
    ObjectModel *objModel;
    Object_68 *obj68;
    s32 sp44;
    f32 var_f2;
    UNUSED s32 pad;
    s16 newvar;
    Object *firstRacerObj;
    
    set_boss_voice_clip_offset(D_800DCE20);
    sp5E = obj->segment.unk38.byte.unk3B;
    sp5C = obj->segment.animFrame;
    sp5A = racer->headAngle;
    if (racer->velocity < 0.3 && -0.3 < racer->velocity) {
        *stickMag = 0;
    }
    if (racer->raceFinished == TRUE && func_80023568()) {
        func_80021400(130);
        racer->raceFinished++;
    }
    sp44 = *startTimer;
    if (sp44 == 100) {
        D_8011D5E0 = 0;
    }
    if (racer->playerIndex == PLAYER_COMPUTER && *startTimer != 100) {
        *startTimer -= 60;
        if (*startTimer < 0) {
            if (D_8011D5E1 == 0) {
                func_8005CB04(0);
                racer->boostTimer = 10;
            }
            D_8011D5E1 = 1;
            *startTimer = 0;
            *input |= A_BUTTON;
        } else {
            D_8011D5E1 = 0;
        }
    }
    racer->vehicleID = VEHICLE_SMOKEY;
    func_80049794(updateRate, updateRateF, obj, racer);
    racer->vehicleID = racer->vehicleIDPrev;
    *startTimer = sp44;
    obj->unk74 = 0;
    racer->headAngle = sp5A;
    obj->segment.unk38.byte.unk3B = sp5E;
    obj->segment.animFrame = sp5C;
    if (racer->attackType != ATTACK_NONE && obj->segment.unk38.byte.unk3B != 5) {
        func_8005CB04(1);
        play_sound_global(SOUND_EXPLOSION, 0);
        set_camera_shake(12.0f);
        obj->segment.unk38.byte.unk3B = 5;
        obj->segment.x_velocity *= 0.27;
        obj->segment.z_velocity *= 0.27;
        racer->unkC = 0.0f;
        obj->segment.y_velocity += 4.0;
    }
    racer->attackType = ATTACK_NONE;
    if (racer->unk148 != 0) {
        xDiff = obj->segment.x_velocity * obj->segment.x_velocity;
        zDiff = obj->segment.z_velocity * obj->segment.z_velocity;
        racer->velocity = -sqrtf((xDiff * xDiff) + (zDiff * zDiff));
        if (racer->velocity > -0.5) {
            racer->velocity = 0.0f;
            obj->segment.x_velocity = 0.0f;
            obj->segment.y_velocity = 0.0f;
            obj->segment.z_velocity = 0.0f;
        }
    }
    obj68 = *obj->unk68;
    objModel = obj68->objModel;
    xDiff = (objModel->animations[obj->segment.unk38.byte.unk3B].unk4 * 16) - 17;
    var_f2 = (racer->velocity * updateRateF) * 0.45;
    if (var_f2 <= 0.0) {
        if (var_f2 > -2.0) {
        var_f2 = -2.0f;
        }
    } else if (var_f2 < 2.0) {
        var_f2 = 2.0f;
    }
    switch (obj->segment.unk38.byte.unk3B) {
    case 0:
        racer->unk1CD = 0;
        racer->unkC += 1.0 * updateRateF;
        break;
    case 1:
        if (racer->unk1CD == 2) {
            racer->unkC += var_f2;
        } else {
            racer->unkC -= var_f2;
        }
        break;
    case 2:
        racer->unk1CD = 2;
        racer->unkC -= var_f2;
        break;
    case 3:
        if (racer->unk1CD == 4) {
            racer->unkC -= 2.0 * updateRateF;
        }
        else {
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
        obj68->unk10 = -1;
    }
    while (racer->unkC <= 0.0f) {
        racer->unkC += xDiff;
        obj68->unk10 = -1;
    }
    if (obj->segment.unk38.byte.unk3B == 2 && racer->unk1E2 == 0 && racer->velocity < -6.5) {
        obj->segment.unk38.byte.unk3B = 3;
        racer->unkC = 0.0f;
    }
    if (obj68->unk10 == -1 || obj->segment.unk38.byte.unk3B == 0) {
        if (obj->segment.unk38.byte.unk3B == 5) {
            obj->segment.unk38.byte.unk3B = racer->unk1CD;
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
        } else if (-0.1 < racer->velocity && racer->velocity < 0.1) {
            if (obj->segment.unk38.byte.unk3B == 2) {
                obj->segment.unk38.byte.unk3B = 1;
                racer->unkC = (objModel->animations[obj->segment.unk38.byte.unk3B].unk4 * 16) - 17;
            } else {
                obj->segment.unk38.byte.unk3B = 0;
            }
        } else {
            if (obj->segment.unk38.byte.unk3B == 0) {
                obj->segment.unk38.byte.unk3B = 1;
                racer->unkC = 0.0f;
            }
            if (obj->segment.unk38.byte.unk3B == 4 && racer->unk1E2 != 0 && racer->velocity > -6.0) {
                obj->segment.unk38.byte.unk3B = 3;
                racer->unkC = (objModel->animations[obj->segment.unk38.byte.unk3B].unk4 * 16) - 17;
            }
        }
    }
    sp5C = obj->segment.animFrame;
    obj->segment.animFrame = racer->unkC;
    newvar = obj->segment.animFrame >> 4;
    obj->unk74 = 0;
    if (obj->segment.unk38.byte.unk3B != 1 && obj->segment.unk38.byte.unk3B != 2) {
        sp5C >>= 4;
        newvar = 1;
        if (obj->segment.unk38.byte.unk3B == 0) {
            newvar = 3;
        }
        if (sp5C == newvar && newvar + 1 == obj->segment.animFrame >> 4) {
            func_80009558(SOUND_UNK_223, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, 0);
        }
    }
    if (racer->vehicleIDPrev == 7 && racer->playerIndex == PLAYER_COMPUTER && func_80023568()) {
        func_8005E204(obj, racer, 100.0f, 137, 165);
    }
    func_800AFC3C(obj, updateRate);
    fade_when_near_camera(obj, racer, 40);
    firstRacerObj = get_racer_object(0);
    xDiff = firstRacerObj->segment.trans.x_position - obj->segment.trans.x_position;
    zDiff = firstRacerObj->segment.trans.z_position - obj->segment.trans.z_position;
    if (sqrtf((xDiff * xDiff) + (zDiff * zDiff)) < 700.0) {
        sp44 = (arctan2_f(xDiff, zDiff) - (obj->segment.trans.y_rotation & 0xFFFF)) + 0x8000;
        if (sp44 > 0x8000) {
            sp44 -= 0xFFFF;
        }
        if (sp44 < -0x8000) {
            sp44 += 0xFFFF;
        }
        if (sp44 > 0xC00) {
            sp44 = 0xC00;
        }
        if (sp44 < -0xC00) {
            sp44 = -0xC00;
        }
        racer->headAngleTarget = sp44;
    }
    if (obj->segment.unk38.byte.unk3B >= 2) {
        if ((racer->unk1E7 & 0x1F) < 10) {
            racer->headAngleTarget >>= 1;
        }
    }
    racer = (Object_Racer *) firstRacerObj->unk64;
    if (obj == firstRacerObj->interactObj->obj && firstRacerObj->interactObj->unk14 & 8 && obj->segment.unk38.byte.unk3B == 1) {
        racer->attackType = ATTACK_SQUISHED;
    }
    if (racer->raceFinished != FALSE) {
        if (D_8011D5E0 == 0) {
            D_8011D5E0 = 1;
            func_8005CB68(racer, &D_8011D5E0);
        }
    }
}

void func_8005E204(Object *obj, Object_Racer *racer, f32 arg2, s32 objectID, s32 arg4) {
    Object **var_s6;
    s32 sp80;
    s32 sp7C;
    LevelObjectEntry *temp_s2;
    Object *temp_s1;
    Object *newObj;
    s32 i;
    LevelObjectEntryCommon spawnObj;
    f32 xDiff;
    f32 zDiff;
    f32 yDiff;

    var_s6 = func_8000E988(&sp80, &sp7C);
    spawnObj.objectID = objectID;
    spawnObj.size = (((objectID & 0x100) & 0xFFFF) >> 1) | 8;
    spawnObj.x = obj->segment.trans.x_position - (racer->ox1 * arg2);
    spawnObj.y = obj->segment.trans.y_position - (racer->oy1 * arg2);
    spawnObj.z = obj->segment.trans.z_position - (racer->oz1 * arg2);
    
    for (i = 0; i < sp7C; i++) {
        temp_s1 = var_s6[i];
        if (temp_s1->behaviorId == BHV_UNK_6B) {
            temp_s2 = temp_s1->segment.unk3C_a.level_entry; 
            if ((s8) temp_s2->animation.z_rotation == racer->lap + 1 || (s8) temp_s2->animation.z_rotation == 0) {
                xDiff = temp_s1->segment.trans.x_position - obj->segment.trans.x_position;
                yDiff = temp_s1->segment.trans.y_position - obj->segment.trans.y_position;
                zDiff = temp_s1->segment.trans.z_position - obj->segment.trans.z_position;
                if (sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff)) < (f32) ((s8) temp_s2->animation.x_rotation & 0xFF) * 4.0) {
                    if (temp_s1->unk78 == 0) {
                        temp_s1->unk78 = 1;
                        newObj = spawn_object(&spawnObj, 1);
                        if (newObj != NULL) {
                            newObj->segment.unk3C_a.level_entry = NULL;
                            newObj->segment.x_velocity = obj->segment.x_velocity;
                            newObj->segment.y_velocity = obj->segment.y_velocity;
                            newObj->segment.z_velocity = obj->segment.z_velocity;
                            newObj->unk78_obj = temp_s1;
                            newObj->unk7C.word = (s8) temp_s2->animation.y_rotation * 60;
                            newObj->segment.animFrame = get_random_number_from_range(0, 255);
                            func_80009558(arg4, newObj->segment.trans.x_position, newObj->segment.trans.y_position, newObj->segment.trans.z_position, 4, NULL);
                        }
                    }
                } else {
                    temp_s1->unk78 = 0;
                }
            }
        }
    }
}
