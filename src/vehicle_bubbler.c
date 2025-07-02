#include "vehicle_misc.h"

#include "types.h"
#include "macros.h"
#include "racer.h"
#include "math_util.h"
#include "objects.h"
#include "particles.h"
#include "printf.h"
#include "audio.h"

/************ .data ************/

u16 gBubblerVoiceTable[16] = {
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

s8 gBubblerCutsceneTimer;
s8 gBubblerStartBoost;

/******************************/

enum BubblerAnimations { ANIM_BUBBLER_IDLE, ANIM_BUBBLER_MOVE, ANIM_BUBBLER_DAMAGE };

/**
 * Top level function for updating the "Bubbler" vehicle.
 * Basically this controls the Bubbler boss on Sherbert Island, who follows a path, then throws special tripmines and
 * bubble traps on the course.
 */
void update_bubbler(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, u32 *buttonsPressed,
                    s32 *startTimer) {
    s16 animID;
    s16 animFrame;
    s16 tempHeadAngle;
    s32 objectID;
    f32 diffZ;
    ModelInstance *modInst;
    s32 timer;
    UNUSED s32 pad;
    s32 headAngleRange;
    ObjectModel *model;
    Object *firstRacerObj;
    f32 diffX;
    s32 temp2;

    set_boss_voice_clip_offset(gBubblerVoiceTable);
    *buttonsPressed &= ~R_TRIG;
    *input &= ~R_TRIG;
    animID = obj->animationID;
    animFrame = obj->animFrame;
    tempHeadAngle = racer->headAngle;
    if (racer->raceFinished == TRUE) {
        func_80021400(130);
        racer->raceFinished++;
    }
    timer = *startTimer;
    if (timer == 100) {
        gBubblerCutsceneTimer = 0;
    }
    if (racer->playerIndex == PLAYER_COMPUTER && *startTimer != 100) {
        *startTimer -= 30;
        if (*startTimer < 0) {
            if (gBubblerStartBoost == FALSE) {
                play_random_boss_sound(BOSS_SOUND_POSITIVE);
                racer->boostTimer = 5;
            }
            gBubblerStartBoost = TRUE;
            *startTimer = 0;
            *input |= A_BUTTON;
        } else {
            gBubblerStartBoost = FALSE;
        }
    }
    func_8004F7F4(updateRate, updateRateF, obj, racer);
    *startTimer = timer;
    racer->lateral_velocity = 0.0f;
    racer->headAngle = tempHeadAngle;
    obj->animationID = animID;
    obj->animFrame = animFrame;
    if (racer->attackType != ATTACK_NONE && obj->animationID != ANIM_BUBBLER_DAMAGE) {
        racer->unk1CD = obj->animationID;
        obj->animationID = ANIM_BUBBLER_DAMAGE;
        obj->y_velocity += 7.5;
        play_random_boss_sound(BOSS_SOUND_NEGATIVE);
        sound_play(SOUND_EXPLOSION, NULL);
        set_camera_shake(12.0f);
        racer->velocity *= 0.3;
        racer->animationSpeed = 0.0f;
    }
    racer->attackType = ATTACK_NONE;
    if (racer->approachTarget != 0) {
        diffX = obj->x_velocity * obj->x_velocity;
        diffZ = obj->z_velocity * obj->z_velocity;
        racer->velocity = -sqrtf((diffX * diffX) + (diffZ * diffZ));
    }
    modInst = obj->modelInstances[0];
    model = modInst->objModel;
    diffX = (model->animations[obj->animationID].animLength * 16) - 17;
    obj->animationID = ANIM_BUBBLER_MOVE;
    racer->animationSpeed += 2.0 * updateRateF;
    while (racer->animationSpeed < 0.0f) {
        racer->animationSpeed += diffX;
        modInst->animationID = -1;
    }
    while (diffX < racer->animationSpeed) {
        racer->animationSpeed -= diffX;
        modInst->animationID = -1;
    }
    if (modInst->animationID == -1 && obj->animationID == ANIM_BUBBLER_DAMAGE) {
        obj->animationID = ANIM_BUBBLER_MOVE;
        racer->animationSpeed = 0.0f;
    }
    obj->animFrame = racer->animationSpeed;
    if (racer->playerIndex == PLAYER_COMPUTER) {
        temp2 = func_80023568();
        if (temp2 != 0) {
            objectID = ASSET_OBJECT_ID_OCTOBUBBLE;
            if (temp2 == 6) {
                objectID = ASSET_OBJECT_ID_OCTOBOMB;
            }
            spawn_boss_hazard(obj, racer, 0.0f, objectID, SOUND_VOICE_BUBBLER_HOHO2);
        }
    }
    obj->particleEmittersEnabled = OBJ_EMIT_NONE;
    obj_spawn_particle(obj, updateRate);
    fade_when_near_camera(obj, racer, 40);
    switch (obj->animationID) {
        case ANIM_BUBBLER_MOVE:
            headAngleRange = 0x2500;
            break;
        case ANIM_BUBBLER_DAMAGE:
            headAngleRange = 0x100;
            break;
        default:
            headAngleRange = 0x1500;
            break;
    }
    firstRacerObj = get_racer_object(PLAYER_ONE);
    diffX = firstRacerObj->trans.x_position - obj->trans.x_position;
    diffZ = firstRacerObj->trans.z_position - obj->trans.z_position;
    if (sqrtf((diffX * diffX) + (diffZ * diffZ)) < 700.0) {
        timer = (arctan2_f(diffX, diffZ) - (obj->trans.rotation.y_rotation & 0xFFFF)) + 0x8000;
        WRAP(timer, -0x8000, 0x8000);
        CLAMP(timer, -headAngleRange, headAngleRange);
        racer->headAngleTarget = timer;
    }
    if (obj->animationID == ANIM_BUBBLER_MOVE) {
        if ((racer->miscAnimCounter & 0x1F) < 10) {
            racer->headAngleTarget >>= 1;
        }
    }
    racer = firstRacerObj->racer;
    if (obj == firstRacerObj->interactObj->obj && firstRacerObj->interactObj->flags & INTERACT_FLAGS_PUSHING &&
        obj->animationID == ANIM_BUBBLER_MOVE) {
        racer->attackType = ATTACK_SQUISHED;
    }
    if (racer->raceFinished) {
        if (gBubblerCutsceneTimer == 0) {
            gBubblerCutsceneTimer = 1;
            racer_boss_finish(racer, &gBubblerCutsceneTimer);
        }
    }
}
