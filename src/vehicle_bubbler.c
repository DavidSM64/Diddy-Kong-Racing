/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005E4C0 */

#include "vehicle_misc.h"

#include "types.h"
#include "macros.h"
#include "racer.h"
#include "math_util.h"
#include "objects.h"
#include "particles.h"
#include "printf.h"

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
    Object_68 *gfxData;
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
    animID = obj->segment.object.animationID;
    animFrame = obj->segment.animFrame;
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
            *input |= 0x8000;
        } else {
            gBubblerStartBoost = FALSE;
        }
    }
    func_8004F7F4(updateRate, updateRateF, obj, racer);
    *startTimer = timer;
    racer->lateral_velocity = 0.0f;
    racer->headAngle = tempHeadAngle;
    obj->segment.object.animationID = animID;
    obj->segment.animFrame = animFrame;
    if (racer->attackType != ATTACK_NONE && obj->segment.object.animationID != ANIM_BUBBLER_DAMAGE) {
        racer->unk1CD = obj->segment.object.animationID;
        obj->segment.object.animationID = ANIM_BUBBLER_DAMAGE;
        obj->segment.y_velocity += 7.5;
        play_random_boss_sound(BOSS_SOUND_NEGATIVE);
        sound_play(SOUND_EXPLOSION, 0);
        set_camera_shake(12.0f);
        racer->velocity *= 0.3;
        racer->animationSpeed = 0.0f;
    }
    racer->attackType = ATTACK_NONE;
    if (racer->approachTarget != 0) {
        diffX = obj->segment.x_velocity * obj->segment.x_velocity;
        diffZ = obj->segment.z_velocity * obj->segment.z_velocity;
        racer->velocity = -sqrtf((diffX * diffX) + (diffZ * diffZ));
    }
    gfxData = *obj->unk68;
    model = gfxData->objModel;
    diffX = (model->animations[obj->segment.object.animationID].unk4 * 16) - 17;
    obj->segment.object.animationID = ANIM_BUBBLER_MOVE;
    racer->animationSpeed += 2.0 * updateRateF;
    while (racer->animationSpeed < 0.0f) {
        racer->animationSpeed += diffX;
        gfxData->animationID = -1;
    }
    while (diffX < racer->animationSpeed) {
        racer->animationSpeed -= diffX;
        gfxData->animationID = -1;
    }
    if (gfxData->animationID == -1 && obj->segment.object.animationID == ANIM_BUBBLER_DAMAGE) {
        obj->segment.object.animationID = ANIM_BUBBLER_MOVE;
        racer->animationSpeed = 0.0f;
    }
    obj->segment.animFrame = racer->animationSpeed;
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
    obj->particleEmitFlags = OBJ_EMIT_OFF;
    obj_spawn_particle(obj, updateRate);
    fade_when_near_camera(obj, racer, 40);
    switch (obj->segment.object.animationID) {
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
    diffX = firstRacerObj->segment.trans.x_position - obj->segment.trans.x_position;
    diffZ = firstRacerObj->segment.trans.z_position - obj->segment.trans.z_position;
    if (sqrtf((diffX * diffX) + (diffZ * diffZ)) < 700.0) {
        timer = (arctan2_f(diffX, diffZ) - (obj->segment.trans.rotation.y_rotation & 0xFFFF)) + 0x8000;
        WRAP(timer, -0x8000, 0x8000);
        CLAMP(timer, -headAngleRange, headAngleRange);
        racer->headAngleTarget = timer;
    }
    if (obj->segment.object.animationID == ANIM_BUBBLER_MOVE) {
        if ((racer->miscAnimCounter & 0x1F) < 10) {
            racer->headAngleTarget >>= 1;
        }
    }
    racer = (Object_Racer *) firstRacerObj->unk64;
    if (obj == firstRacerObj->interactObj->obj && firstRacerObj->interactObj->flags & INTERACT_FLAGS_PUSHING &&
        obj->segment.object.animationID == ANIM_BUBBLER_MOVE) {
        racer->attackType = ATTACK_SQUISHED;
    }
    if (racer->raceFinished) {
        if (gBubblerCutsceneTimer == 0) {
            gBubblerCutsceneTimer = 1;
            racer_boss_finish(racer, &gBubblerCutsceneTimer);
        }
    }
}
