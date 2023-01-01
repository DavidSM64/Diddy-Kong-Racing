/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005C2F0 */

#include "vehicle_misc.h"

#include "structs.h"
#include "types.h"
#include "macros.h"
#include "audio.h"
#include "objects.h"
#include "unknown_005740.h"
#include "unknown_008C40.h"
#include "menu.h"
#include "game.h"
#include "particles.h"
#include "math_util.h"

/************ .data ************/

u16 D_800DCDE0[16] = {
    SOUND_VOICE_BOSS_LAUGH,
    SOUND_VOICE_TRICKY_WOAH,
    SOUND_VOICE_TRICKY_WOAH2,
    SOUND_VOICE_WIZPIG_LAUGH_SHORT2,
    SOUND_VOICE_WIZPIG_LAUGH_SHORT3,
    SOUND_VOICE_TRICKY_WOAH3,
    SOUND_VOICE_TRICKY_WOAH4,
    SOUND_VOICE_TRICKY_LAUGH,
    SOUND_VOICE_TRICKY_LAUGH2,
    SOUND_VOICE_TRICKY_OW,
    SOUND_VOICE_TRICKY_OW2,
    SOUND_VOICE_CONKER_YEHAHA,
    SOUND_VOICE_TIMBER_WOW,
    SOUND_WHOOSH2,
    SOUND_NONE,
    SOUND_NONE
};

/*******************************/

/************ .bss ************/

f32 D_8011D5C0;
s8 D_8011D5C4;
u16 *gBossSoundIDOffset;
s8 D_8011D5CC;

/******************************/

void func_8005C2F0(Object *object, unk8005C2F0 *arg1) {
    object->interactObj->unk14 = 5;
    object->interactObj->unk11 = 0;
    object->interactObj->unk10 = 0x1E;
    object->interactObj->unk12 = 0;
    arg1->unkC = 0.0f;
    D_8011D5C0 = object->segment.trans.y_position;
    if (arg1->unk118 != 0) {
        func_80006AC8(object);
    }
    D_8011D5C4 = 0;
}

/**
 * Top level function for updating the Tricky vehicle as seen in the Dino Domain boss.
*/
void update_tricky(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, u32 *buttonsPressed, s32 *startTimer) {
    s16 sp56;
    s16 sp54;
    s16 sp52;
    f32 xDiff;
    f32 zDiff;
    ObjectModel *objModel;
    s32 sp40;
    Object_68 *obj68;
    s32 sp38;
    UNUSED s32 pad;
    Object *firstRacerObj;

    set_boss_voice_clip_offset(D_800DCDE0);
    *buttonsPressed &= ~R_TRIG;
    *input &= ~R_TRIG;
    sp56 = obj->segment.unk38.byte.unk3B;
    sp54 = obj->segment.animFrame;
    sp52 = racer->headAngle;
    if (racer->raceFinished == TRUE) {
        func_80021400(130);
        racer->raceFinished++;
    }
    sp40 = *startTimer;
    if (racer->playerIndex == PLAYER_COMPUTER) {
        if (*startTimer != 100) {
            *startTimer -= 15;
            if (*startTimer < 0) {
                if (D_8011D5CC == 0) {
                    func_8005CB04(0);
                    racer->boostTimer = 5;
                }
                D_8011D5CC = 1;
                *startTimer = 0;
                *input |= A_BUTTON;
            } else {
                D_8011D5CC = 0;
            }
        }
    }
    
    func_8004F7F4(updateRate, updateRateF, obj, racer);
    *startTimer = sp40;
    racer->lateral_velocity = 0.0f;
    racer->headAngle = sp52;
    obj->segment.unk38.byte.unk3B = sp56;
    obj->segment.animFrame = sp54;
    if (racer->attackType != 0) {
        if (obj->segment.unk38.byte.unk3B != 3) {
            racer->unk1CD = obj->segment.unk38.byte.unk3B;
            obj->segment.unk38.byte.unk3B = 3;
            obj->segment.y_velocity += 7.5;
            func_8005CB04(1);
            play_sound_global(SOUND_EXPLOSION, NULL);
            set_camera_shake(12.0f);
            racer->velocity *= 0.3;
            racer->unkC = 0.0f;
        }
    }
    racer->attackType = ATTACK_NONE;
    if (racer->approachTarget != NULL) {
        xDiff = obj->segment.x_velocity * obj->segment.x_velocity;
        zDiff = obj->segment.z_velocity * obj->segment.z_velocity;
        racer->velocity = -sqrtf((xDiff * xDiff) + (zDiff * zDiff));
    }
    obj68 = *obj->unk68;
    objModel = obj68->objModel;
    xDiff = (objModel->animations[obj->segment.unk38.byte.unk3B].unk4 * 16) - 17;
    if (obj->segment.unk38.byte.unk3B != 3) {
        if (racer->velocity < -2.0) {
            obj->segment.unk38.byte.unk3B = 1;
            racer->unkC -= (racer->velocity * updateRateF) * 0.5;
        } else if (racer->velocity < -0.1 || 0.1 < racer->velocity) {
            obj->segment.unk38.byte.unk3B = 2;
            racer->unkC -= (racer->velocity * updateRateF) * 2;
        } else {
            obj->segment.unk38.byte.unk3B = 0;
            racer->unkC += 1.0 * updateRateF;
        }
    } else {
        racer->unkC += 2.0 * updateRateF;
    }
    while (racer->unkC < 0.0f) {
        racer->unkC += xDiff;
        obj68->unk10 = -1;
    }
    while (xDiff < racer->unkC) {
        racer->unkC -= xDiff;
        obj68->unk10 = -1;
    }
    if (obj68->unk10 == -1 && obj->segment.unk38.byte.unk3B == 3) {
        obj->segment.unk38.byte.unk3B = racer->unk1CD;
    }
    sp54 = obj->segment.animFrame;
    obj->segment.animFrame = racer->unkC;
    obj->unk74 = 0;
    if (obj->segment.unk38.byte.unk3B == 1) {
        func_800113CC(obj, 2, sp54, 172, 173);
        obj->unk74 |= 3;
    }
    func_800AFC3C(obj, updateRate);
    fade_when_near_camera(obj, racer, 120);
    switch( obj->segment.unk38.byte.unk3B) {
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
        sp40 = (arctan2_f(xDiff, zDiff) - (obj->segment.trans.y_rotation & 0xFFFF)) + 0x8000;
        WRAP(sp40, -0x8000, 0x8000);
        CLAMP(sp40, -sp38, sp38);
        racer->headAngleTarget = sp40;
    }
    if (obj->segment.unk38.byte.unk3B == 1) {
        if ((racer->miscCounter & 0x1F) < 0xA) {
            racer->headAngleTarget >>= 1;
        }
    }
    racer = (Object_Racer *) firstRacerObj->unk64;
    if (D_8011D5C0 < firstRacerObj->segment.trans.y_position) {
        D_8011D5C0 = firstRacerObj->segment.trans.y_position;
    }
    if ((firstRacerObj->segment.trans.y_position + 400.0) < D_8011D5C0) {
        if (func_800C018C() == 0 && is_in_two_player_adventure()) {
            func_8006F398();
        }
        func_8006F140(1);
    }
    if (obj == firstRacerObj->interactObj->obj && firstRacerObj->interactObj->unk14 & 8 && obj->segment.unk38.byte.unk3B == 1) {
        racer->attackType = ATTACK_SQUISHED;
    }
    if (racer->raceFinished != FALSE) {
        if (D_8011D5C4 == 0) {
            D_8011D5C4 = 1;
            func_8005CB68(racer, &D_8011D5C4);
        }
    }
}

/**
 * Set the sound ID offset for a given boss clip.
*/
void set_boss_voice_clip_offset(u16 *soundID) {
    gBossSoundIDOffset = soundID;
}

void func_8005CA84(f32 x, f32 y, f32 z, s32 offset) {
    s8 phi_v1 = get_random_number_from_range(0, 1);
    if (offset == 0) {
        phi_v1 = 0;
    }
    offset += phi_v1;
    func_80009558(gBossSoundIDOffset[offset], x, y, z, 4, 0);
}

void func_8005CB04(s32 offset) {
    s8 phi_v1 = get_random_number_from_range(0, 1);
    if (offset == 0) {
        phi_v1 = 0;
    }
    offset += phi_v1;
    play_sound_global(gBossSoundIDOffset[offset], 0);
}

#ifdef NON_EQUIVALENT
// This looks like it's just some stack and regalloc differences, but I can't be certain it's NON_MATCHING yet.
// This function looks like it sets up the animation sequences
void func_8005CB68(Object_Racer *racer, s8 *arg1) {
    Settings *settings;
    s8 arg1_ret;
    s8 *miscAsset68;
    s32 bossId;
    s32 racerUnk1AC;
    s8 *miscAsset67;
    s32 miscAsset68Byte5;
    s32 miscAsset68Byte6;
    s32 miscAsset68Byte7;
    s8 miscAsset67CourseByte;
    s32 var_t1;
    s32 i;

    arg1_ret = *arg1;
    settings = get_settings();
    bossId = (1 << settings->worldId);
    if (!miscAsset67CourseByte){}
    /*
        ASSET_MISC_68[] =
        ASSET_LEVELNAME_DINODOMAINTROPHYANIM,
        ASSET_LEVELNAME_SHERBETISLANDTROPHYANIM
        ASSET_LEVELNAME_SNOWFLAKEMOUNTAINTROPHYANIM,
        ASSET_LEVELNAME_DRAGONFORESTTROPHYANIM,
        ASSET_LEVELNAME_WIZPIGMOUTHSEQUENCE,
        ASSET_LEVELNAME_PARTYSEQUENCE,
        ASSET_LEVELNAME_LASTBIT,
        ASSET_LEVELNAME_LASTBITB
    */
    miscAsset68 = (s8 *)get_misc_asset(ASSET_MISC_68); //8 bytes - 2F 31 30 32 2A 38 3F 40 - LevelIds for the world animations?
    miscAsset68Byte5 = miscAsset68[5]; //0x38 - 56 - ASSET_LEVELNAME_PARTYSEQUENCE?
    miscAsset68Byte6 = miscAsset68[6]; //0x3F - 63 - ASSET_LEVELNAME_LASTBIT?
    miscAsset68Byte7 = miscAsset68[7]; //0x40 - 64 - ASSET_LEVELNAME_LASTBITB?
    miscAsset67 = (s8 *)get_misc_asset(ASSET_MISC_67); //20 bytes - course id's array with world id index?
    for (i = 0; settings->courseId != miscAsset67[i]; i += 2) {
        if ((miscAsset67CourseByte && miscAsset67CourseByte) && miscAsset67CourseByte) {}
    }
    miscAsset67CourseByte = miscAsset67[i + 1];
    racerUnk1AC = racer->unk1AC;
    if (arg1_ret == 1) {
        if (racerUnk1AC == 1) {
            play_music(SEQUENCE_BATTLE_VICTORY);
        } else {
            play_music(SEQUENCE_BATTLE_LOSE);
        }
        if ((settings->worldId == WORLD_CENTRAL_AREA) || (settings->worldId == WORLD_FUTURE_FUN_LAND)) {
            if (racerUnk1AC == 1) {
                settings->bosses |= bossId;
                settings->courseFlagsPtr[settings->courseId] |= 2;
            }
            if (settings->worldId == WORLD_CENTRAL_AREA) {
                if (racerUnk1AC == 1) {
                    func_8006C1AC((s32)SPECIAL_MAP_ID_UNK_NEG2, 0, VEHICLE_CAR, 0);
                    func_8006C1AC(miscAsset68Byte5, 0, -1, 0);
                    func_8006C1AC(miscAsset67CourseByte, 0, -1, 1);
                } else {
                    func_8006C1AC((s32)SPECIAL_MAP_ID_UNK_NEG10, 0, VEHICLE_CAR, 0);
                    func_8006C1AC(miscAsset67CourseByte, 0, -1, 2);
                }
            } else if (racerUnk1AC == 1) {
                set_eeprom_settings_value(1); //Set Adventure Two Unlocked
                func_8006C1AC((s32)SPECIAL_MAP_ID_UNK_NEG2, 0, VEHICLE_CAR, 0);
                func_8006C1AC(miscAsset68Byte7, 0, -1, 0);
                func_8006C1AC(miscAsset68Byte6, 0, -1, 0);
                func_8006C1AC(miscAsset67CourseByte, 0, -1, 1);
            } else {
                func_8006C1AC((s32)SPECIAL_MAP_ID_UNK_NEG10, 0, VEHICLE_CAR, 0);
                func_8006C1AC(miscAsset67CourseByte, 0, -1, 2);
            }
            if (racerUnk1AC == 1) {
                func_8006F140(4);
            } else {
                func_8006F140(3);
            }
            arg1_ret++;
            *arg1 = arg1_ret;
            return;
        }
        if (settings->courseFlagsPtr[settings->courseId] & 2) {
            if (racerUnk1AC == 1) {
                func_8006F140(4);
                func_8000E128();
            } else {
                func_8006F140(3);
                if (is_in_two_player_adventure()) {
                    func_8006F398();
                }
            }
            arg1_ret++;
            *arg1 = arg1_ret;
            return;
        }
        if (racerUnk1AC == 1) {
            settings->courseFlagsPtr[settings->courseId] |= 2;
            if (!(settings->bosses & bossId)) {
                settings->bosses |= bossId;
                func_8006C1AC((s32)SPECIAL_MAP_ID_NO_LEVEL, 0, VEHICLE_CAR, 0);
                func_8006C1AC(miscAsset67CourseByte, 4, -1, 4);
            } else if (!(settings->bosses & (bossId << 6))) {
                settings->bosses |= bossId << 6;
                var_t1 = 0;
                if ((settings->worldId > 0) && (settings->worldId < 5)) {
                    var_t1 = settings->wizpigAmulet + 1;
                    if (var_t1 >= 5) {
                        var_t1 = 4;
                    }
                    settings->wizpigAmulet = var_t1;
                }
                if (var_t1 != 0) {
                    func_8006C1AC((s32)SPECIAL_MAP_ID_NO_LEVEL, 0, VEHICLE_CAR, 0);
                    func_8006C1AC(ASSET_LEVELNAME_WIZPIGAMULETSEQUENCE, 0, -1, settings->wizpigAmulet - 1);
                    func_8006C1AC(miscAsset67CourseByte, 6, -1, 6);
                } else {
                    func_8006C1AC((s32)SPECIAL_MAP_ID_NO_LEVEL, 0, VEHICLE_CAR, 0);
                    func_8006C1AC(miscAsset67CourseByte, 4, -1, 4);
                }
            } else {
                func_8006C1AC((s32)SPECIAL_MAP_ID_NO_LEVEL, 0, VEHICLE_CAR, 0);
                func_8006C1AC(miscAsset67CourseByte, 4, -1, 4);
            }
            func_8006F140(4);
            func_8000E128();
        } else {
            func_8006C1AC((s32)SPECIAL_MAP_ID_UNK_NEG10, 0, VEHICLE_CAR, 0);
            func_8006C1AC(miscAsset67CourseByte, 5, -1, 5);
            func_8006F140(3);
        }
        arg1_ret++;
        func_8006EC48(get_save_file_index());
    }
    *arg1 = arg1_ret;
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_05CEF0/func_8005CB68.s")
#endif

/**
 * When close to the camera, fade the object so it doesn't block the screen.
 */
void fade_when_near_camera(Object *object, Object_Racer *racer, s32 distance) {
    Object *player = get_racer_object(0);
    racer->transparency = 255;
    if (!func_8001139C()) {
        if ((object->segment.unk30 + distance) < player->segment.unk30) {
            racer->transparency = 64;
        }
    }
}
