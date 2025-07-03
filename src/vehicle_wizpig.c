#include "vehicle_misc.h"

#include "types.h"
#include "macros.h"
#include "racer.h"
#include "objects.h"
#include "object_functions.h"
#include "particles.h"
#include "audio.h"
#include "camera.h"

/************ .data ************/

// The highest index that ever seems to be read from this table is 6.
u16 gWizpigVoiceTable[16] = {
    SOUND_VOICE_BOSS_LAUGH2,
    SOUND_VOICE_TRICKY_HM,
    SOUND_VOICE_TRICKY_HMMM,
    SOUND_VOICE_WIZPIG_LAUGH4,
    SOUND_VOICE_WIZPIG_LAUGH2,
    SOUND_VOICE_WIZPIG_GROAN,
    SOUND_VOICE_WIZPIG_LAUGH3,
    SOUND_VOICE_SMOKEY_HAH, // Never read from this point?
    SOUND_VOICE_SMOKEY_LAUGH,
    SOUND_VOICE_SMOKEY_HM,
    SOUND_VOICE_SMOKEY_HM2,
    SOUND_VOICE_CONKER_YEHAHA,
    SOUND_VOICE_TIMBER_WOW,
    SOUND_WHOOSH2,
    SOUND_NONE,
    SOUND_NONE,
};

/*******************************/

/************ .bss ************/

s8 gWizpigCutsceneTimer;
s8 gWizpigStartBoost;

/******************************/

enum WizpigAnimations {
    ANIM_WIZPIG_IDLE,
    ANIM_WIZPIG_WALK,
    ANIM_WIZPIG_RUN,
    ANIM_WIZPIG_JUMP,
    ANIM_WIZPIG_FLY,
    ANIM_WIZPIG_DAMAGE // Unused.
};

/**
 * Top level function for updating the wizpig vehicle from the first boss race against him.
 */
void update_wizpig(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, u32 *buttonsPressed,
                   s32 *startTimer) {
    s16 animID;
    s16 animFrame;
    s16 tempHeadAngle;
    s16 nextCheckpoint;
    f32 diffZ;
    f32 diffX;
    f32 animVelocity;
    s32 tempStartTimer;
    Object *firstRacerObj;
    ObjectModel *objModel;
    ModelInstance *modInst;

    set_boss_voice_clip_offset(gWizpigVoiceTable);
    racer->tappedR = 0;
    animID = obj->animationID;
    animFrame = obj->animFrame;
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
        gWizpigCutsceneTimer = 0;
    }
    racer->zipperDirCorrection = FALSE;
    if (racer->playerIndex == PLAYER_COMPUTER) {
        if (*startTimer != 100) {
            *startTimer -= 30;
            if (*startTimer < 0) {
                if (gWizpigStartBoost == FALSE) {
                    play_random_boss_sound(BOSS_SOUND_POSITIVE);
                    racer->boostTimer = 10;
                }
                gWizpigStartBoost = TRUE;
                *startTimer = 0;
                *input |= A_BUTTON;
            } else {
                gWizpigStartBoost = FALSE;
            }
        }
    }
    racer->vehicleID = VEHICLE_WIZPIG;
    func_80049794(updateRate, updateRateF, obj, racer);
    racer->vehicleID = racer->vehicleIDPrev;
    *startTimer = tempStartTimer;
    obj->particleEmittersEnabled = OBJ_EMIT_NONE;
    racer->headAngle = tempHeadAngle;
    obj->animationID = animID;
    obj->animFrame = animFrame;
    // Unused, since there are no weapon balloons in Wizpig 1.
    if (racer->attackType != ATTACK_NONE && obj->animationID != ANIM_WIZPIG_DAMAGE) {
        play_random_boss_sound(BOSS_SOUND_NEGATIVE);
        sound_play(SOUND_EXPLOSION, NULL);
        set_camera_shake(12.0f);
        obj->animationID = ANIM_WIZPIG_DAMAGE;
        obj->x_velocity *= 0.4;
        obj->z_velocity *= 0.4;
        racer->animationSpeed = 0.0f;
        obj->y_velocity += 4.0;
    }
    racer->attackType = ATTACK_NONE;
    if (racer->approachTarget != NULL) {
        diffX = obj->x_velocity * obj->x_velocity;
        diffZ = (obj->z_velocity * obj->z_velocity);
        racer->velocity = -sqrtf((diffX * diffX) + (diffZ * diffZ));
        if (racer->velocity > -0.5) {
            racer->velocity = 0.0f;
            obj->x_velocity = 0.0f;
            obj->y_velocity = 0.0f;
            obj->z_velocity = 0.0f;
        }
    }
    nextCheckpoint = FALSE;
    if (find_next_checkpoint_node(racer->checkpoint, racer->unk1C8)->unk36[racer->unk1CA] == 1) {
        nextCheckpoint = TRUE;
    }
    racer->x_rotation_offset = -obj->trans.rotation.x_rotation;
    modInst = obj->modelInstances[0];
    objModel = modInst->objModel;
    diffX = (objModel->animations[obj->animationID].animLength * 16) - 17;
    animVelocity = (racer->velocity * updateRateF) * 0.45;
    if (animVelocity <= 0.0) {
        if (animVelocity > -2.0) {
            animVelocity = -2.0f;
        }
    } else if (animVelocity < 2.0) {
        animVelocity = 2.0f;
    }
    switch (obj->animationID) {
        case ANIM_WIZPIG_IDLE:
            racer->unk1CD = 0;
            racer->animationSpeed += 1.0 * updateRateF;
            break;
        case ANIM_WIZPIG_WALK:
            if (racer->unk1CD == 2) {
                racer->animationSpeed += animVelocity;
            } else {
                racer->animationSpeed -= animVelocity;
            }
            break;
        case ANIM_WIZPIG_RUN:
            racer->unk1CD = 2;
            racer->animationSpeed -= animVelocity;
            break;
        case ANIM_WIZPIG_JUMP:
            if (racer->unk1CD == 4) {
                racer->animationSpeed -= 2.0 * updateRateF;
            } else {
                racer->animationSpeed += 2.0 * updateRateF;
            }
            break;
        case ANIM_WIZPIG_FLY:
            racer->unk1CD = 4;
            racer->animationSpeed += 2.0 * updateRateF;
            break;
        case ANIM_WIZPIG_DAMAGE:
            racer->animationSpeed += 2.0 * updateRateF;
            break;
        default:
            break;
    }

    while (diffX <= racer->animationSpeed) {
        racer->animationSpeed -= diffX;
        modInst->animationID = -1;
    }
    while (racer->animationSpeed <= 0.0f) {
        racer->animationSpeed += diffX;
        modInst->animationID = -1;
    }
    if (obj->animationID == ANIM_WIZPIG_RUN && nextCheckpoint) {
        obj->animationID = ANIM_WIZPIG_JUMP;
        racer->animationSpeed = 0.0f;
    }
    if (modInst->animationID == -1 || obj->animationID == ANIM_WIZPIG_IDLE) {
        if (obj->animationID == ANIM_WIZPIG_DAMAGE) {
            obj->animationID = racer->unk1CD;
            racer->animationSpeed = 0.0f;
        } else if (obj->animationID == ANIM_WIZPIG_WALK) {
            if (racer->unk1CD == 0) {
                obj->animationID = ANIM_WIZPIG_RUN;
            } else {
                obj->animationID = ANIM_WIZPIG_IDLE;
            }
        } else if (obj->animationID == ANIM_WIZPIG_JUMP) {
            if (racer->unk1CD == 4) {
                obj->animationID = ANIM_WIZPIG_RUN;
            } else {
                obj->animationID = ANIM_WIZPIG_FLY;
            }
        } else {
            if (-0.1 < racer->velocity && racer->velocity < 0.1) {
                if (obj->animationID == ANIM_WIZPIG_RUN) {
                    obj->animationID = ANIM_WIZPIG_WALK;
                    racer->animationSpeed = (objModel->animations[obj->animationID].animLength * 16) - 17;
                } else {
                    obj->animationID = ANIM_WIZPIG_IDLE;
                }
            } else {
                if (obj->animationID == ANIM_WIZPIG_IDLE) {
                    obj->animationID = ANIM_WIZPIG_WALK;
                    racer->animationSpeed = 0.0f;
                }
                if ((obj->animationID == ANIM_WIZPIG_FLY) && nextCheckpoint == FALSE) {
                    obj->animationID = ANIM_WIZPIG_JUMP;
                    racer->animationSpeed = (objModel->animations[obj->animationID].animLength * 16) - 17;
                }
            }
        }
    }
    animFrame = obj->animFrame;
    obj->animFrame = racer->animationSpeed;
    obj->particleEmittersEnabled = OBJ_EMIT_NONE;
    if (obj->animationID == ANIM_WIZPIG_RUN) {
        play_footstep_sounds(obj, 2, animFrame, SOUND_STOMP2, SOUND_STOMP3);
    }
    if (racer->playerIndex == PLAYER_COMPUTER) {
        if (func_80023568() != 0) {
            spawn_boss_hazard(obj, racer, 100.0f, ASSET_OBJECT_ID_FIREBALL, SOUND_VOICE_TRICKY_HM);
        }
    }
    obj_spawn_particle(obj, updateRate);
    fade_when_near_camera(obj, racer, 40);
    firstRacerObj = get_racer_object(PLAYER_ONE);
    racer = firstRacerObj->racer;
    if (obj == firstRacerObj->interactObj->obj && firstRacerObj->interactObj->flags & INTERACT_FLAGS_PUSHING &&
        obj->animationID == ANIM_WIZPIG_WALK) {
        racer->attackType = ATTACK_SQUISHED;
    }
    if (racer->raceFinished) {
        if (gWizpigCutsceneTimer == 0) {
            gWizpigCutsceneTimer = 1;
            racer_boss_finish(racer, &gWizpigCutsceneTimer);
        }
    }
}
