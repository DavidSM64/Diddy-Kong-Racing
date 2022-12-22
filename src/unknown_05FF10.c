/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005F310 */

#include "unknown_05FF10.h"

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

#ifdef NON_EQUIVALENT
// Seems to be mostly regalloc and stack differences
void func_8005F310(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, u32 *buttonsPressed, s32 *startTimer) {
    s16 sp3E;
    s16 sp3C;
    s16 sp3A;
    Object *tempObj;
    Object_64 *obj64;
    Object_68 *obj68;
    f32 zVelSquared;
    f32 xVelSquared;
    f32 temp_f2_3;

    func_8005CA78(D_800DCE80);
    racer->unk1EC = 0;
    sp3E = obj->segment.unk38.byte.unk3A;
    sp3C = obj->segment.animFrame;
    sp3A = racer->unk16A;
    if ((racer->velocity < 0.3) && (racer->velocity > -0.3)) {
        *buttonsPressed = 0;
    }
    if (racer->raceFinished == TRUE && func_80023568()) {
        func_80021400(130);
        racer->raceFinished++;
    }
    if (*startTimer == 100) {
        D_8011D610 = 0;
    }
    racer->unk1F5 = 0;
    if (racer->playerIndex == -1) {
        if (*startTimer != 100) {
            *startTimer -= 30;
            if (*startTimer < 0) {
                if (D_8011D611 == 0) {
                    func_8005CB04(0);
                }
                D_8011D611 = 1;
                *startTimer = 0;
                *input |= A_BUTTON;
            } else {
                D_8011D611 = 0;
            }
        }
    }
    racer->vehicleID = VEHICLE_CARPET;
    func_80049794(updateRate, updateRateF, obj, racer);
    racer->vehicleID = racer->unk1D7;
    obj->unk74 = 0;
    racer->unk16A = sp3A;
    obj->segment.unk38.byte.unk3A = sp3E;
    obj->segment.animFrame = sp3C;
    if ((racer->attackType != ATTACK_NONE) && (obj->segment.unk38.byte.unk3A != 1)) {
        func_8005CB04(1);
        play_sound_global(SOUND_EXPLOSION, NULL);
        func_80069F28(12.0f);
        obj->segment.x_velocity *= 0.4;
        obj->segment.z_velocity *= 0.4;
        obj->segment.unk38.byte.unk3A = 1;
        racer->unkC = 0;
        obj->segment.y_velocity += 4.0;
    }
    racer->attackType = ATTACK_NONE;
    if (racer->unk148 != NULL) {
        xVelSquared = obj->segment.x_velocity * obj->segment.x_velocity;
        zVelSquared = obj->segment.z_velocity * obj->segment.z_velocity;
        racer->velocity = -sqrtf((xVelSquared * xVelSquared) + (zVelSquared * zVelSquared));
        if (racer->velocity > -0.5) {
            racer->velocity = 0;
            obj->segment.x_velocity = 0;
            obj->segment.y_velocity = 0;
            obj->segment.z_velocity = 0;
        }
    }
    racer->unkC += (updateRateF * 2.0);
    obj68 = obj->unk68[0];
    temp_f2_3 = ((obj68->objModel->animations[obj->segment.unk38.byte.unk3A].unk4 * 16) - 17);
    while (temp_f2_3 <= racer->unkC) {
        racer->unkC -= temp_f2_3;
        obj68->unk10 = -1;
    }
    while (racer->unkC <= 0) {
        racer->unkC += temp_f2_3;
        obj68->unk10 = -1;
    }
    if ((obj->segment.unk38.byte.unk3A == 1) && (obj68->unk10 == -1)) {
        obj->segment.unk38.byte.unk3A = 0;
        racer->unkC = 0;
    }
    obj->unk74 = 0;
    obj->segment.animFrame = racer->unkC;
    func_800AF714(obj, updateRate);
    func_8005D048(obj, racer, 40);
    if (*startTimer != 100) {
        tempObj = func_8000BF44(-1);
        if (tempObj != NULL) {
            tempObj->unk78 = 0;
            obj64 = tempObj->unk64;
            if (obj64 != NULL) {
                // This part here is HIHGLY suspicious, and probably wrong.
                // It's probably an unidentified unk64 struct.
                // Though it could actually be effect box once we add some defined attributes.
                obj64->effect_box.pad0[0x72] += updateRate;
                obj64->effect_box.pad0[0x70] = 2;
                obj64->racer.unk74 = 1.0f;
                func_8000B750(obj, -1, 2, 1, 1);
            }
        }
    }
    tempObj = get_racer_object(0);
    obj64 = tempObj->unk64;
    if ((obj == tempObj->interactObj->obj) && (tempObj->interactObj->unk14 & 8) && (obj->segment.unk38.byte.unk3A == 1)) {
        obj64->racer.attackType = ATTACK_SQUISHED;
    }
    if ((obj64->racer.raceFinished != FALSE) && (D_8011D610 == 0)) {
        D_8011D610 = 1;
        func_8005CB68(obj64, &D_8011D610);
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_05FF10/func_8005F310.s")
#endif
