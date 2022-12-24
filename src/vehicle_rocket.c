/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005F310 */

#include "vehicle_rocket.h"

#include "types.h"
#include "macros.h"
#include "racer.h"
#include "unknown_05CEF0.h"
#include "objects.h"
#include "audio.h"
#include "camera.h"
#include "particles.h"

/************ .data ************/

//sSoundEffectsPool index values?
s16 D_800DCE80[14] = {
    SOUND_VOICE_BOSS_LAUGH2,
    SOUND_VOICE_TRICKY_HM,
    SOUND_VOICE_TRICKY_HMMM,
    SOUND_VOICE_WIZPIG_LAUGH4,
    SOUND_VOICE_WIZPIG_LAUGH2,
    SOUND_VOICE_WIZPIG_GROAN,
    SOUND_VOICE_WIZPIG_LAUGH3,
    SOUND_VOICE_SMOKEY_HAH,
    SOUND_VOICE_SMOKEY_LAUGH,
    SOUND_VOICE_SMOKEY_HM,
    SOUND_VOICE_SMOKEY_HM2,
    SOUND_VOICE_CONKER_YEHAHA,
    SOUND_VOICE_TIMBER_WOW,
    SOUND_WHOOSH2
};

/*******************************/

/************ .bss ************/

s8 D_8011D610;
s8 D_8011D611;

/******************************/

/**
 * Top level update function for the Wizpig Rocket vehicle, used in the Wizpig rematch.
*/
void update_rocket(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, u32 *buttonsPressed, s32 *startTimer) {
    s16 sp3E;
    s16 sp3C;
    s16 sp3A;
    f32 zDiff;
    f32 xDiff;
    s32 sp2C;
    Object *someObj;
    Object *firstRacerObj;
    Object_WizpigRocket *rocket;
    Object_68 *gfxData;
    ObjectModel *objModel;

    func_8005CA78((u16* ) D_800DCE80);
    racer->unk1EC = 0;
    sp3E = obj->segment.unk38.byte.unk3B;
    sp3C = obj->segment.animFrame;
    sp3A = racer->unk16A;
    if ((racer->velocity < 0.3) && (-0.3 < racer->velocity)) {
        *buttonsPressed = 0;
    }
    if (racer->raceFinished == 1) {
        if (func_80023568() != 0) {
            func_80021400(0x82);
            racer->raceFinished += 1;
        }
    }
    sp2C = *startTimer;
    if (sp2C == 0x64) {
        D_8011D610 = 0;
    }
    racer->unk1F5 = 0;
    if (racer->playerIndex == PLAYER_COMPUTER) {
        if (*startTimer != 100) {
        *startTimer -= 30;
            if (*startTimer < 0) {
                if (D_8011D611 == 0) {
                    sp2C = sp2C;
                    func_8005CB04(0);
                }
                D_8011D611 = 1;
                *startTimer = 0;
                *input |= 0x8000;
            } else {
                D_8011D611 = 0;
            }
        }
    }
    racer->vehicleID = VEHICLE_CARPET;
    func_80049794(updateRate, updateRateF, obj, racer);
    racer->vehicleID = racer->unk1D7;
    *startTimer = sp2C;
    obj->unk74 = 0;
    racer->unk16A = sp3A;
    obj->segment.unk38.byte.unk3B = sp3E;
    obj->segment.animFrame = sp3C;
    if ((racer->attackType != 0) && (obj->segment.unk38.byte.unk3B != 1)) {
        func_8005CB04(1);
        play_sound_global(SOUND_EXPLOSION, NULL);
        func_80069F28(12.0f);
        obj->segment.x_velocity *= 0.4;
        obj->segment.unk38.byte.unk3B = 1;
        obj->segment.z_velocity *= 0.4;
        racer->unkC = 0.0f;
        obj->segment.y_velocity += 4.0;
    }
    racer->attackType = ATTACK_NONE;
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
    racer->unkC += 2.0 * updateRateF;
    gfxData = *obj->unk68;
    objModel = gfxData->objModel;
    xDiff = (objModel->animations[obj->segment.unk38.byte.unk3B].unk4 * 0x10) - 0x11;
    while (xDiff <= racer->unkC) {
        racer->unkC -= xDiff;
        gfxData->unk10 = -1;
    }
    while (racer->unkC <= 0.0f) {
        racer->unkC += xDiff;
        gfxData->unk10 = -1;
    }
    if (obj->segment.unk38.byte.unk3B == 1 && gfxData->unk10 == -1) {
        obj->segment.unk38.byte.unk3B = 0;
        racer->unkC = 0.0f;
    }
    obj->segment.animFrame = racer->unkC;
    obj->unk74 = 0;
    func_800AF714(obj, updateRate);
    func_8005D048(obj, racer, 0x28);
    if (*startTimer != 100) {
        someObj = func_8000BF44(-1);
        if (someObj != NULL) {
            rocket = (Object_WizpigRocket *) someObj->unk64;
            someObj->unk78 = 0;
            if (rocket != NULL) {
                rocket->unk72 += updateRate;
                rocket->unk70 = 2;
                rocket->unk74 = 1.0f;
                func_8000B750(obj, -1, 2, 1, 1);
            }
        }
    }
    firstRacerObj = get_racer_object(0);
    racer = (Object_Racer*)firstRacerObj->unk64;
    if (obj == firstRacerObj->interactObj->obj && firstRacerObj->interactObj->unk14 & 8 && obj->segment.unk38.byte.unk3B == 1) {
        racer->attackType = ATTACK_SQUISHED;
    }
    if (racer->raceFinished != 0) {
        if (D_8011D610 == 0) {
            D_8011D610 = 1;
            func_8005CB68(racer, &D_8011D610);
        }
    }
}
