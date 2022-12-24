/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005E4C0 */

#include "vehicle_bubbler.h"

#include "types.h"
#include "macros.h"
#include "racer.h"
#include "unknown_05CEF0.h"
#include "math_util.h"
#include "objects.h"
#include "particles.h"
#include "unknown_05DCD0.h"
#include "vehicle_bubbler.h"
#include "printf.h"

/************ .data ************/

s16 D_800DCE40[16] = {
    SOUND_VOICE_BUBBLER_HOHO,
    SOUND_VOICE_BUBBLER_OW,
    SOUND_VOICE_BUBBLER_AUGH,
    SOUND_VOICE_BUBBLER_HOHO2,
    SOUND_VOICE_BUBBLER_AW,
    SOUND_VOICE_BUBBLER_OW2,
    SOUND_VOICE_BUBBLER_AUGH2,
    SOUND_VOICE_TRICKY_LAUGH,
    SOUND_VOICE_TRICKY_LAUGH2,
    SOUND_VOICE_TRICKY_OW,
    SOUND_VOICE_TRICKY_OW2,
    SOUND_VOICE_CONKER_YEHAHA,
    SOUND_VOICE_TIMBER_WOW,
    SOUND_WHOOSH2,
    SOUND_NONE,
    SOUND_NONE,
};

/*******************************/

/************ .bss ************/

s8 D_8011D5F0;
s8 D_8011D5F1;

/******************************/

/**
 * Top level function for updating the "Bubbler" vehicle.
 * Basically this controls the Bubbler boss on Sherbert Island, who follows a path, then throws special tripmines and bubble traps on the course.
*/
void update_bubbler(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, u32 *buttonsPressed, s32 *startTimer) {
    s16 sp56;
    s16 animFrame;
    s16 sp52;
    s32 objectID;
    f32 zDiff;
    Object_68 *gfxData;
    s32 timer;
    UNUSED s32 pad;
    s32 sp38;
    ObjectModel *model;
    Object *firstRacerObj;
    f32 xDiff;
    s32 temp2;
    
    set_boss_voice_clip_offset((u16 *) D_800DCE40);
    *buttonsPressed &= ~R_TRIG;
    *input &= ~(R_TRIG);
    sp56 = obj->segment.unk38.byte.unk3B;
    animFrame = obj->segment.animFrame;
    sp52 = racer->unk16A;
    if (racer->raceFinished == 1) {
        func_80021400(0x82);
        racer->raceFinished++;
    }
    timer = *startTimer;
    if (timer == 100) {
        D_8011D5F0 = 0;
    }
    if (racer->playerIndex == PLAYER_COMPUTER && *startTimer != 100) {
        *startTimer -= 30;
        if (*startTimer < 0) {
            if (D_8011D5F1 == 0) {
                func_8005CB04(0);
                racer->boostTimer = 5;
            }
            D_8011D5F1 = 1;
            *startTimer = 0;
            *input |= 0x8000;
        } else {
            D_8011D5F1 = 0;
        }
    }
    func_8004F7F4(updateRate, updateRateF, obj, racer);
    *startTimer = timer;
    racer->lateral_velocity = 0.0f;
    racer->unk16A = sp52;
    obj->segment.unk38.byte.unk3B = sp56;
    obj->segment.animFrame = animFrame;
    if (racer->attackType != ATTACK_NONE && obj->segment.unk38.byte.unk3B != 2) {
        racer->unk1CD = obj->segment.unk38.byte.unk3B;
        obj->segment.unk38.byte.unk3B = 2;
        obj->segment.y_velocity += 7.5;
        func_8005CB04(1);
        play_sound_global(SOUND_EXPLOSION, 0);
        func_80069F28(12.0f);
        racer->velocity *= 0.3;
        racer->unkC = 0.0f;
    }
    racer->attackType = ATTACK_NONE;
    if (racer->unk148 != 0) {
        xDiff = obj->segment.x_velocity * obj->segment.x_velocity;
        zDiff = obj->segment.z_velocity * obj->segment.z_velocity;
        racer->velocity = -sqrtf((xDiff * xDiff) + (zDiff * zDiff));
    }
    gfxData = *obj->unk68;
    model = gfxData->objModel;
    xDiff = (model->animations[obj->segment.unk38.byte.unk3B].unk4 * 16) - 17;
    obj->segment.unk38.byte.unk3B = 1;
    racer->unkC += 2.0 * updateRateF;
    while (racer->unkC < 0.0f) {
        racer->unkC += xDiff;
        gfxData->unk10 = -1;
    }
    while (xDiff < racer->unkC) {
        racer->unkC -= xDiff;
        gfxData->unk10 = -1;
    }
    if (gfxData->unk10 == -1 && obj->segment.unk38.byte.unk3B == 2) {
        obj->segment.unk38.byte.unk3B = 1;
        racer->unkC = 0.0f;
    }
    obj->segment.animFrame = racer->unkC;
    if (racer->playerIndex == PLAYER_COMPUTER) {
        temp2 = func_80023568();
        if (temp2 != 0) {
            objectID = 0x110;
            if (temp2 == 6) {
                objectID = 0x12A;
            }
            func_8005E204(obj, racer, 0.0f, objectID, 0x245);
        }
    }
    obj->unk74 = 0;
    func_800AFC3C(obj, updateRate);
    fade_when_near_camera(obj, racer, 0x28);
    switch (obj->segment.unk38.byte.unk3B) {
    case 1:
        sp38 = 0x2500;
    break;
    case 2:
        sp38 = 0x100;
    break;
    default:
        sp38 = 0x1500;
    break;
    }
    firstRacerObj = get_racer_object(0);
    xDiff = firstRacerObj->segment.trans.x_position - obj->segment.trans.x_position;
    zDiff = firstRacerObj->segment.trans.z_position - obj->segment.trans.z_position;
    if (sqrtf((xDiff * xDiff) + (zDiff * zDiff)) < 700.0) {
        timer = (arctan2_f(xDiff, zDiff) - (obj->segment.trans.y_rotation & 0xFFFF)) + 0x8000;
        WRAP(timer, -0x8000, 0x8000);
        CLAMP(timer, -sp38, sp38);
        racer->unk16C = timer;
    }
    if (obj->segment.unk38.byte.unk3B == 1) {
        if ((racer->unk1E7 & 0x1F) < 10) {
            racer->unk16C >>= 1;
        }
    }
    racer = (Object_Racer *) firstRacerObj->unk64;
    if (obj == firstRacerObj->interactObj->obj && firstRacerObj->interactObj->unk14 & 8 && obj->segment.unk38.byte.unk3B == 1) {
        racer->attackType = ATTACK_SQUISHED;
    }
    if (racer->raceFinished) {
        if (D_8011D5F0 == 0) {
        D_8011D5F0 = 1;
        func_8005CB68(racer, &D_8011D5F0);
        }
    }
}
