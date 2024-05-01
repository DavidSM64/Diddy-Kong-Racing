/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005F310 */

#include "vehicle_misc.h"

#include "types.h"
#include "macros.h"
#include "racer.h"
#include "objects.h"
#include "audio.h"
#include "camera.h"
#include "particles.h"

/************ .data ************/

// sSoundEffectsPool index values?
s16 gRocketVoiceTable[14] = {
    SOUND_VOICE_BOSS_LAUGH2,   SOUND_VOICE_TRICKY_HM,
    SOUND_VOICE_TRICKY_HMMM,   SOUND_VOICE_WIZPIG_LAUGH4,
    SOUND_VOICE_WIZPIG_LAUGH2, SOUND_VOICE_WIZPIG_GROAN,
    SOUND_VOICE_WIZPIG_LAUGH3, SOUND_VOICE_SMOKEY_HAH,
    SOUND_VOICE_SMOKEY_LAUGH,  SOUND_VOICE_SMOKEY_HM,
    SOUND_VOICE_SMOKEY_HM2,    SOUND_VOICE_CONKER_YEHAHA,
    SOUND_VOICE_TIMBER_WOW,    SOUND_WHOOSH2,
};

/*******************************/

/************ .bss ************/

s8 gRocketCutsceneTimer;
s8 gRocketStartBoost;

/******************************/

enum RocketAnimations { ANIM_ROCKET_IDLE, ANIM_ROCKET_DAMAGE };

/**
 * Top level update function for the Wizpig Rocket vehicle, used in the Wizpig rematch.
 */
void update_rocket(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, u32 *buttonsPressed,
                   s32 *startTimer) {
    s16 animID;
    s16 animFrame;
    s16 tempHeadAngle;
    f32 diffZ;
    f32 diffX;
    s32 tempStartTimer;
    Object *someObj;
    Object *firstRacerObj;
    Object_WizpigRocket *rocket;
    Object_68 *gfxData;
    ObjectModel *objModel;

    set_boss_voice_clip_offset((u16 *) gRocketVoiceTable);
    racer->tappedR = 0;
    animID = obj->segment.object.animationID;
    animFrame = obj->segment.animFrame;
    tempHeadAngle = racer->headAngle;
    if (racer->velocity < 0.3 && -0.3 < racer->velocity) {
        *buttonsPressed = 0;
    }
    if (racer->raceFinished == TRUE && func_80023568()) {
        func_80021400(130);
        racer->raceFinished++;
    }
    tempStartTimer = *startTimer;
    if (tempStartTimer == 100) {
        gRocketCutsceneTimer = 0;
    }
    racer->zipperDirCorrection = FALSE;
    if (racer->playerIndex == PLAYER_COMPUTER) {
        if (*startTimer != 100) {
            *startTimer -= 30;
            if (*startTimer < 0) {
                if (gRocketStartBoost == FALSE) {
                    play_random_boss_sound(BOSS_SOUND_POSITIVE);
                }
                gRocketStartBoost = TRUE;
                *startTimer = 0;
                *input |= A_BUTTON;
            } else {
                gRocketStartBoost = FALSE;
            }
        }
    }
    racer->vehicleID = VEHICLE_CARPET;
    func_80049794(updateRate, updateRateF, obj, racer);
    racer->vehicleID = racer->vehicleIDPrev;
    *startTimer = tempStartTimer;
    obj->particleEmitFlags = OBJ_EMIT_OFF;
    racer->headAngle = tempHeadAngle;
    obj->segment.object.animationID = animID;
    obj->segment.animFrame = animFrame;
    if (racer->attackType != ATTACK_NONE && obj->segment.object.animationID != ANIM_ROCKET_DAMAGE) {
        play_random_boss_sound(BOSS_SOUND_NEGATIVE);
        sound_play(SOUND_EXPLOSION, NULL);
        set_camera_shake(12.0f);
        obj->segment.x_velocity *= 0.4;
        obj->segment.object.animationID = ANIM_ROCKET_DAMAGE;
        obj->segment.z_velocity *= 0.4;
        racer->animationSpeed = 0.0f;
        obj->segment.y_velocity += 4.0;
    }
    racer->attackType = ATTACK_NONE;
    if (racer->approachTarget != NULL) {
        diffX = obj->segment.x_velocity * obj->segment.x_velocity;
        diffZ = obj->segment.z_velocity * obj->segment.z_velocity;
        racer->velocity = -sqrtf((diffX * diffX) + (diffZ * diffZ));
        if (racer->velocity > -0.5) {
            racer->velocity = 0.0f;
            obj->segment.x_velocity = 0.0f;
            obj->segment.y_velocity = 0.0f;
            obj->segment.z_velocity = 0.0f;
        }
    }
    racer->animationSpeed += 2.0 * updateRateF;
    gfxData = *obj->unk68;
    objModel = gfxData->objModel;
    diffX = (objModel->animations[obj->segment.object.animationID].unk4 * 16) - 17;
    while (diffX <= racer->animationSpeed) {
        racer->animationSpeed -= diffX;
        gfxData->animationID = -1;
    }
    while (racer->animationSpeed <= 0.0f) {
        racer->animationSpeed += diffX;
        gfxData->animationID = -1;
    }
    if (obj->segment.object.animationID == ANIM_ROCKET_DAMAGE && gfxData->animationID == -1) {
        obj->segment.object.animationID = ANIM_ROCKET_IDLE;
        racer->animationSpeed = 0.0f;
    }
    obj->segment.animFrame = racer->animationSpeed;
    obj->particleEmitFlags = OBJ_EMIT_OFF;
    func_800AF714(obj, updateRate);
    fade_when_near_camera(obj, racer, 40);
    if (*startTimer != 100) {
        someObj = func_8000BF44(-1);
        if (someObj != NULL) {
            rocket = (Object_WizpigRocket *) someObj->unk64;
            someObj->properties.racer.unk0 = 0;
            if (rocket != NULL) {
                rocket->unk72 += updateRate;
                rocket->unk70 = 2;
                rocket->unk74 = 1.0f;
                func_8000B750(obj, -1, 2, 1, 1);
            }
        }
    }
    firstRacerObj = get_racer_object(PLAYER_ONE);
    racer = (Object_Racer *) firstRacerObj->unk64;
    if (obj == firstRacerObj->interactObj->obj && firstRacerObj->interactObj->flags & INTERACT_FLAGS_PUSHING &&
        obj->segment.object.animationID == ANIM_ROCKET_DAMAGE) {
        racer->attackType = ATTACK_SQUISHED;
    }
    if (racer->raceFinished != 0) {
        if (gRocketCutsceneTimer == 0) {
            gRocketCutsceneTimer = 1;
            racer_boss_finish(racer, &gRocketCutsceneTimer);
        }
    }
}
