/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005D0D0 */

#include "vehicle_misc.h"

#include "types.h"
#include "macros.h"
#include "math_util.h"
#include "objects.h"
#include "object_functions.h"
#include "unknown_008C40.h"
#include "racer.h"
#include "particles.h"

/************ .data ************/

u16 D_800DCE00[16] = {
    SOUND_VOICE_BLUEY_EH3,
    SOUND_VOICE_BLUEY_EH,
    SOUND_VOICE_BLUEY_OHNO,
    SOUND_VOICE_BLUEY_HAHA,
    SOUND_VOICE_BLUEY_HAHA2,
    SOUND_VOICE_BLUEY_EH2,
    SOUND_VOICE_BLUEY_OHNO2,
    SOUND_VOICE_BLUEY_HAHA3,
    SOUND_VOICE_BLUEY_HAHA4,
    SOUND_VOICE_BLUEY_AIEE,
    SOUND_VOICE_BLUEY_OHNO3,
    SOUND_VOICE_CONKER_YEHAHA,
    SOUND_VOICE_TIMBER_WOW,
    SOUND_WHOOSH2,
    SOUND_NONE,
    SOUND_NONE,
};

u16 D_800DCE20[16] = {
    SOUND_VOICE_BOSS_LAUGH2,
    SOUND_VOICE_TRICKY_HM,
    SOUND_VOICE_TRICKY_HMMM,
    SOUND_VOICE_WIZPIG_HA,
    SOUND_VOICE_WIZPIG_H2,
    SOUND_VOICE_SMOKEY_EH,
    SOUND_VOICE_SMOKEY_HEH,
    SOUND_VOICE_SMOKEY_HAH,
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

s8 D_8011D5D0;
s8 D_8011D5D1;

/******************************/

/**
 * Top level function for the Bluey vehicle, as seen in the Snowflake Mountain boss stage.
*/
void update_bluey(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, u32 *buttonsPressed, s32 *startTimer) {
    s16 sp5E;
    s16 sp5C;
    s16 sp5A;
    f32 diffX;
    f32 diffZ;
    s32 var_v0;
    s32 sp48;
    ObjectModel *objModel;
    Object_68 *obj68;
    s32 sp3C;
    UNUSED s32 pad;
    Object *firstRacerObj;

    set_boss_voice_clip_offset(D_800DCE00);
    *buttonsPressed &= ~R_TRIG;
    *input &= ~R_TRIG;
    sp5E = obj->segment.unk38.byte.unk3B;
    sp5C = obj->segment.animFrame;
    sp5A = racer->headAngle;
    if (racer->raceFinished == TRUE && func_80023568()) {
        func_80021400(130);
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
    racer->headAngle = sp5A;
    obj->segment.unk38.byte.unk3B = (s8) sp5E;
    obj->segment.animFrame = sp5C;
    if (racer->attackType != ATTACK_NONE) {
        if (obj->segment.unk38.byte.unk3B != 4) {
            racer->unk1CD = obj->segment.unk38.byte.unk3B;
            obj->segment.unk38.byte.unk3B = 4;
            racer->unkC = 0.0f;
            func_8005CB04(1);
            play_sound_global(SOUND_EXPLOSION, NULL);
            set_camera_shake(12.0f);
            racer->attackType = ATTACK_NONE;
            racer->velocity *= 0.3;
            obj->segment.y_velocity += 7.5;
        }
    }
    if (racer->approachTarget != NULL) {
        diffX = obj->segment.x_velocity * obj->segment.x_velocity;
        diffZ = obj->segment.z_velocity * obj->segment.z_velocity;
        racer->velocity = -sqrtf((diffX * diffX) + (diffZ * diffZ));
    }
    sp3C = FALSE;
    if ((find_next_checkpoint_node(racer->checkpoint, racer->unk1C8))->unk36[racer->unk1CA] == 1) {
        sp3C = TRUE;
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
    diffX = (objModel->animations[obj->segment.unk38.byte.unk3B].unk4 * 16) - 17;
    while (racer->unkC < 0.0f) {
        racer->unkC += diffX;
        obj68->unk10 = -1;
    }
    while (diffX < racer->unkC) {
        racer->unkC -= diffX;
        obj68->unk10 = -1;
    }
    if ((obj68->unk10 == -1) && (obj->segment.unk38.byte.unk3B == 4)) {
        obj->segment.unk38.byte.unk3B = racer->unk1CD;
    }
    sp5C = obj->segment.animFrame;
    obj->segment.animFrame = racer->unkC;
    obj->unk74 = 0;
    if (obj->segment.unk38.byte.unk3B == 0) {
        func_800113CC(obj, 2, sp5C, SOUND_STOMP2, SOUND_STOMP3);
        obj->unk74 |= 3;
    }
    func_800AFC3C(obj, updateRate);
    fade_when_near_camera(obj, racer, 0x28);
    firstRacerObj = get_racer_object(0);
    diffX = firstRacerObj->segment.trans.x_position - obj->segment.trans.x_position;
    diffZ = firstRacerObj->segment.trans.z_position - obj->segment.trans.z_position;
    if (sqrtf((diffX * diffX) + (diffZ * diffZ)) < 700.0) {
        sp48 = (arctan2_f(diffX, diffZ) - (obj->segment.trans.y_rotation & 0xFFFF)) + 0x8000;
        WRAP(sp48, -0x8000, 0x8000);
        CLAMP(sp48, -0xC00, 0xC00);
        racer->headAngleTarget = sp48;
    }
    if (obj->segment.unk38.byte.unk3B == 1) {
        if ((racer->miscAnimCounter & 0x1F) < 10) {
            racer->headAngleTarget >>= 1;
        }
    }
    if (obj->segment.unk38.byte.unk3B == 3) {
        racer->headAngleTarget = 0;
    }
    racer = (Object_Racer *) firstRacerObj->unk64;
    if (obj == firstRacerObj->interactObj->obj && firstRacerObj->interactObj->flags & INTERACT_FLAGS_PUSHING && obj->segment.unk38.byte.unk3B == 1) {
        racer->attackType = ATTACK_SQUISHED;
    }
    if (racer->raceFinished) {
        if (D_8011D5D0 == 0) {
            D_8011D5D0 = 1;
            func_8005CB68(racer, &D_8011D5D0);
        }
    }
}
