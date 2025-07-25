#include "vehicle_misc.h"

#include "audio.h"
#include "audio_spatial.h"
#include "camera.h"
#include "macros.h"
#include "math_util.h"
#include "objects.h"
#include "particles.h"
#include "racer.h"
#include "types.h"

/************ .data ************/

// The highest index that ever seems to be read from this table is 6.
u16 gBlueyVoiceTable[16] = {
    SOUND_VOICE_BLUEY_EH3,
    SOUND_VOICE_BLUEY_EH,
    SOUND_VOICE_BLUEY_OHNO,
    SOUND_VOICE_BLUEY_HAHA,
    SOUND_VOICE_BLUEY_HAHA2,
    SOUND_VOICE_BLUEY_EH2,
    SOUND_VOICE_BLUEY_OHNO2,
    SOUND_VOICE_BLUEY_HAHA3, // Never read from this point?
    SOUND_VOICE_BLUEY_HAHA4,
    SOUND_VOICE_BLUEY_AIEE,
    SOUND_VOICE_BLUEY_OHNO3,
    SOUND_VOICE_CONKER_YEHAHA,
    SOUND_VOICE_TIMBER_WOW,
    SOUND_WHOOSH2,
    SOUND_NONE,
    SOUND_NONE,
};

/*******************************/

/************ .bss ************/

s8 gBlueyCutsceneTimer;
s8 gBlueyStartBoost;

/******************************/

enum BlueAnimations { ANIM_BLUEY_RUN, ANIM_BLUEY_WALK, ANIM_BLUEY_IDLE, ANIM_BLUEY_TURN, ANIM_BLUEY_DAMAGE };

/**
 * Top level function for the Bluey vehicle, as seen in the Snowflake Mountain boss stage.
 */
void update_bluey(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, u32 *buttonsPressed,
                  s32 *startTimer) {
    s16 animID;
    s16 animFrame;
    s16 tempHeadAngle;
    f32 diffX;
    f32 diffZ;
    s32 steerVel;
    s32 tempStartTimer;
    ObjectModel *objModel;
    ModelInstance *modInst;
    s32 sp3C;
    UNUSED s32 pad;
    Object *firstRacerObj;

    set_boss_voice_clip_offset(gBlueyVoiceTable);
    *buttonsPressed &= ~R_TRIG;
    *input &= ~R_TRIG;
    animID = obj->animationID;
    animFrame = obj->animFrame;
    tempHeadAngle = racer->headAngle;
    if (racer->raceFinished == TRUE && func_80023568()) {
        func_80021400(130);
        racer->raceFinished++;
    }
    tempStartTimer = *startTimer;
    if (tempStartTimer == 100) {
        gBlueyCutsceneTimer = 0;
    }
    if (racer->playerIndex == PLAYER_COMPUTER) {
        if (*startTimer != 100) {
            *startTimer -= 15;
            if (*startTimer < 0) {
                if (gBlueyStartBoost == FALSE) {
                    play_random_boss_sound(BOSS_SOUND_POSITIVE);
                    racer->boostTimer = 3;
                }
                gBlueyStartBoost = TRUE;
                *startTimer = 0;
                *input |= A_BUTTON;
            } else {
                gBlueyStartBoost = FALSE;
            }
        }
    }

    func_8004F7F4(updateRate, updateRateF, obj, racer);
    *startTimer = tempStartTimer;
    racer->lateral_velocity = 0.0f;
    racer->headAngle = tempHeadAngle;
    obj->animationID = animID;
    obj->animFrame = animFrame;
    if (racer->attackType != ATTACK_NONE) {
        if (obj->animationID != ANIM_BLUEY_DAMAGE) {
            racer->unk1CD = obj->animationID;
            obj->animationID = ANIM_BLUEY_DAMAGE;
            racer->animationSpeed = 0.0f;
            play_random_boss_sound(BOSS_SOUND_NEGATIVE);
            sound_play(SOUND_EXPLOSION, NULL);
            set_camera_shake(12.0f);
            racer->attackType = ATTACK_NONE;
            racer->velocity *= 0.3;
            obj->y_velocity += 7.5;
        }
    }
    if (racer->approachTarget != NULL) {
        diffX = obj->x_velocity * obj->x_velocity;
        diffZ = obj->z_velocity * obj->z_velocity;
        racer->velocity = -sqrtf((diffX * diffX) + (diffZ * diffZ));
    }
    sp3C = FALSE;
    if ((find_next_checkpoint_node(racer->nextCheckpoint, racer->isOnAlternateRoute))->unk36[racer->unk1CA] == 1) {
        sp3C = TRUE;
    }
    if (obj->animationID != ANIM_BLUEY_DAMAGE) {
        if (racer->velocity < -2.0) {
            if (sp3C) {
                if (racer->unk1CD != 3) {
                    racer->animationSpeed = 40.0f;
                }
                obj->animationID = ANIM_BLUEY_TURN;
                steerVel = racer->steerAngle * 2;
                steerVel = 40 - steerVel;
                if (steerVel < 0) {
                    steerVel = 0;
                }
                if (steerVel > 73) {
                    steerVel = 73;
                }
                racer->unk1CD = 3;
                racer->animationSpeed += (steerVel - racer->animationSpeed) * 0.25;
            } else {
                racer->unk1CD = 0;
                obj->animationID = ANIM_BLUEY_RUN;
                racer->animationSpeed -= (racer->velocity * updateRateF) * 0.5;
            }
        } else if (racer->velocity < -0.1 || 0.1 < racer->velocity) {
            racer->unk1CD = 1;
            obj->animationID = ANIM_BLUEY_WALK;
            racer->animationSpeed -= racer->velocity * updateRateF * 2;
        } else {
            racer->unk1CD = 2;
            obj->animationID = ANIM_BLUEY_IDLE;
            racer->animationSpeed += updateRateF * 1.0;
        }
    } else {
        racer->animationSpeed += updateRateF * 1.0;
    }
    modInst = obj->modelInstances[0];
    objModel = modInst->objModel;
    diffX = (objModel->animations[obj->animationID].animLength * 16) - 17;
    while (racer->animationSpeed < 0.0f) {
        racer->animationSpeed += diffX;
        modInst->animationID = -1;
    }
    while (diffX < racer->animationSpeed) {
        racer->animationSpeed -= diffX;
        modInst->animationID = -1;
    }
    if (modInst->animationID == -1 && obj->animationID == ANIM_BLUEY_DAMAGE) {
        obj->animationID = racer->unk1CD;
    }
    animFrame = obj->animFrame;
    obj->animFrame = racer->animationSpeed;
    obj->particleEmittersEnabled = OBJ_EMIT_NONE;
    if (obj->animationID == ANIM_BLUEY_RUN) {
        play_footstep_sounds(obj, 2, animFrame, SOUND_STOMP2, SOUND_STOMP3);
        obj->particleEmittersEnabled |= OBJ_EMIT_1 | OBJ_EMIT_2;
    }
    obj_spawn_particle(obj, updateRate);
    fade_when_near_camera(obj, racer, 40);
    firstRacerObj = get_racer_object(PLAYER_ONE);
    diffX = firstRacerObj->trans.x_position - obj->trans.x_position;
    diffZ = firstRacerObj->trans.z_position - obj->trans.z_position;
    if (sqrtf((diffX * diffX) + (diffZ * diffZ)) < 700.0) {
        tempStartTimer = (arctan2_f(diffX, diffZ) - (obj->trans.rotation.y_rotation & 0xFFFF)) + 0x8000;
        WRAP(tempStartTimer, -0x8000, 0x8000);
        CLAMP(tempStartTimer, -0xC00, 0xC00);
        racer->headAngleTarget = tempStartTimer;
    }
    if (obj->animationID == ANIM_BLUEY_WALK) {
        if ((racer->miscAnimCounter & 0x1F) < 10) {
            racer->headAngleTarget >>= 1;
        }
    }
    if (obj->animationID == ANIM_BLUEY_TURN) {
        racer->headAngleTarget = 0;
    }
    racer = firstRacerObj->racer;
    if (obj == firstRacerObj->interactObj->obj && firstRacerObj->interactObj->flags & INTERACT_FLAGS_PUSHING &&
        obj->animationID == ANIM_BLUEY_WALK) {
        racer->attackType = ATTACK_SQUISHED;
    }
    if (racer->raceFinished) {
        if (gBlueyCutsceneTimer == 0) {
            gBlueyCutsceneTimer = 1;
            racer_boss_finish(racer, &gBlueyCutsceneTimer);
        }
    }
}
