/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005C2F0 */

#include "unknown_05CEF0.h"

#include "structs.h"
#include "types.h"
#include "macros.h"
#include "audio.h"
#include "objects.h"
#include "unknown_005740.h"
#include "unknown_008C40.h"
#include "menu.h"
#include "game.h"

/************ .data ************/

s16 D_800DCDE0[16] = {
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
    SOUND_UNK00,
    SOUND_UNK00
};

/*******************************/

/************ .bss ************/

f32 D_8011D5C0;
s8 D_8011D5C4;
u16 *D_8011D5C8;
s32 D_8011D5CC;

/******************************/

void func_8005C2F0(Object *object, unk8005C2F0 *arg1) {
    object->unk4C->unk14 = 5;
    object->unk4C->unk11 = 0;
    object->unk4C->unk10 = 0x1E;
    object->unk4C->unk12 = 0;
    arg1->unkC = 0.0f;
    D_8011D5C0 = object->segment.trans.y_position;
    if (arg1->unk118 != 0) {
        func_80006AC8(object);
    }
    D_8011D5C4 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_05CEF0/func_8005C364.s")

void func_8005CA78(u16 *arg0) {
    D_8011D5C8 = arg0;
}

void func_8005CA84(f32 x, f32 y, f32 z, s32 arg3) {
    s8 phi_v1 = get_random_number_from_range(0, 1);
    if (arg3 == 0) {
        phi_v1 = 0;
    }
    arg3 += phi_v1;
    func_80009558(D_8011D5C8[arg3], x, y, z, 4, 0);
}

void func_8005CB04(s32 arg0) {
    s8 phi_v1 = get_random_number_from_range(0, 1);
    if (arg0 == 0) {
        phi_v1 = 0;
    }
    arg0 += phi_v1;
    play_sound_global(D_8011D5C8[arg0], 0);
}

#ifdef NON_EQUIVALENT
// This looks like it's just some stack and regalloc differences, but I can't be certain it's NON_MATCHING yet.
// This function looks like it sets up the animation sequences
void func_8005CB68(Object_Racer *racer, s8 *arg1) {
    Settings *settings;
    s8 arg1_ret;
    s32 racerUnk1AC;
    s32 bossId;
    s8 *miscAsset68;
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
    racerUnk1AC = racer->unk1AC;
    miscAsset67CourseByte = miscAsset67[i + 1];
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
                    func_8006C1AC(-2, 0, 0, 0);
                    func_8006C1AC(miscAsset68Byte5, 0, -1, 0);
                    func_8006C1AC(miscAsset67CourseByte, 0, -1, 1);
                } else {
                    func_8006C1AC(-10, 0, 0, 0);
                    func_8006C1AC(miscAsset67CourseByte, 0, -1, 2);
                }
            } else if (racerUnk1AC == 1) {
                set_eeprom_settings_value(1); //Set Adventure Two Unlocked
                func_8006C1AC(-2, 0, 0, 0);
                func_8006C1AC(miscAsset68Byte7, 0, -1, 0);
                func_8006C1AC(miscAsset68Byte6, 0, -1, 0);
                func_8006C1AC(miscAsset67CourseByte, 0, -1, 1);
            } else {
                func_8006C1AC(-10, 0, 0, 0);
                func_8006C1AC(miscAsset67CourseByte, 0, -1, 2);
            }
            if (racerUnk1AC == 1) {
                func_8006F140(4);
            } else {
                func_8006F140(3);
            }
            *arg1 = arg1_ret + 1;
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
            *arg1 = arg1_ret + 1;
            return;
        }
        if (racerUnk1AC == 1) {
            settings->courseFlagsPtr[settings->courseId] |= 2;
            if (!(settings->bosses & bossId)) {
                settings->bosses |= bossId;
                func_8006C1AC(-1, 0, 0, 0);
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
                    func_8006C1AC(-1, 0, 0, 0);
                    func_8006C1AC(ASSET_LEVELNAME_WIZPIGAMULETSEQUENCE, 0, -1, settings->wizpigAmulet - 1);
                    func_8006C1AC(miscAsset67CourseByte, 6, -1, 6);
                } else {
                    func_8006C1AC(-1, 0, 0, 0);
                    func_8006C1AC(miscAsset67CourseByte, 4, -1, 4);
                }
            } else {
                func_8006C1AC(-1, 0, 0, 0);
                func_8006C1AC(miscAsset67CourseByte, 4, -1, 4);
            }
            func_8006F140(4);
            func_8000E128();
        } else {
            func_8006C1AC(-10, 0, 0, 0);
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

void func_8005D048(Object *object, Object_Racer *arg1, s32 arg2) {
    Object *sp1C = get_object_struct(0);
    arg1->transparency = 0xFF;
    if (!func_8001139C()) {
        if ((object->segment.unk30 + arg2) < sp1C->segment.unk30) {
            arg1->transparency = 0x40;
        }
    }
}
