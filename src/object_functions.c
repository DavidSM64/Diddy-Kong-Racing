/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80033CC0 */

#include "object_functions.h"

#include "PR/os_cont.h"
#include "types.h"
#include "macros.h"
#include "structs.h"
#include "video.h"
#include "camera.h"
#include "menu.h" // For cheats
#include "weather.h"
#include "racer.h"
#include "game.h"
#include "audio.h"
#include "unknown_008C40.h"
#include "objects.h"
#include "particles.h"
#include "unknown_0255E0.h"
#include "font.h"
#include "unknown_032760.h"
#include "game_ui.h"
#include "waves.h"
#include "unknown_003260.h"
#include "objects.h"
#include "math_util.h"
#include "game_text.h"
#include "fade_transition.h"

/************ .data ************/

// Unsure about the signed/unsigned with these arrays.
FadeTransition D_800DC970 = FADE_TRANSITION(0x40, FADE_COLOR_WHITE, 7, 3);
FadeTransition D_800DC978 = FADE_TRANSITION(0x00, FADE_COLOR_BLACK, 30, 0xFFFF);

u16 D_800DC980[20] = {
    0xFF00, 0x0100, 0x0000, 0xFFFF,
    0xFFFF, 0x0100, 0x0100, 0x0000,
    0xFFFF, 0xFFFF, 0x0100, 0xFF00,
    0x0000, 0xFFFF, 0xFFFF, 0xFF00,
    0xFF00, 0x0000, 0xFFFF, 0xFFFF,
};
u16 D_800DC9A8[20] = {
    0x0000, 0x0040, 0xFFC0, 0x0000,
    0xFFC0, 0xFFC0, 0x0000, 0x0040,
    0x0020, 0x0000, 0xFFC0, 0x0020,
    0x0000, 0x0040, 0x0040, 0x0000,
    0xFFC0, 0x0040, 0x0000, 0x0000,
};
u16 D_800DC9D0[64] = {
    0x0000, 0x0301, 0x0004, 0x0000,
    0x0001, 0x0004, 0x0004, 0x0004,
    0x0000, 0x0203, 0x0004, 0x0000,
    0x0001, 0x0000, 0x0001, 0x0004,
    0x0002, 0x0503, 0x0001, 0x0000,
    0x0000, 0x0004, 0x0001, 0x0004,
    0x0002, 0x0405, 0x0001, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0004,
    0x0000, 0x0103, 0x0004, 0x0000,
    0x0004, 0x0004, 0x0001, 0x0004,
    0x0000, 0x0302, 0x0004, 0x0000,
    0x0001, 0x0004, 0x0001, 0x0000,
    0x0002, 0x0305, 0x0001, 0x0000,
    0x0001, 0x0004, 0x0000, 0x0004,
    0x0002, 0x0504, 0x0001, 0x0000,
    0x0000, 0x0004, 0x0000, 0x0000,
};
s8 D_800DCA50[8] = {
    2, 5, 6, 3, 10, 8, 7, 9
};
u8 D_800DCA58[9] = {
    2, 5, 6, 3, 10, 8, 7, 9, 11
};
s8 D_800DCA64[9] = {
    2, 5, 6, 3, 10, 8, 7, 9, 12
};
s8 D_800DCA70[10] = {
    2, 5, 6, 3, 10, 8, 7, 9, 11, 12
};
s32 D_800DCA7C[3] = { // Not sure about typing
    0, 0, 0
};
s32 D_800DCA88[3] = { // Not sure about typing
    0, 0, 0
};

s8 D_800DCA94[8] = {
    0x00, 0x00, 0x01, 0x01, 0x02, 0x00, 0x00, 0x00
};

s8 D_800DCA9C[12] = {
    0x00, 0x01, 0x01, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

Triangle D_800DCAA8[8] = {
    { {{ 0, 0, 3, 1 }}, {  0, 0 }, { -1, -1 }, {  0, -1 } },
    { {{ 0, 0, 2, 3 }}, {  0, 0 }, { -1,  0 }, { -1, -1 } },
    { {{ 0, 2, 5, 3 }}, { -1, 0 }, {  0, -1 }, { -1, -1 } },
    { {{ 0, 2, 4, 5 }}, { -1, 0 }, {  0,  0 }, {  0, -1 } },
    { {{ 0, 0, 1, 3 }}, {  0, 0 }, {  0, -1 }, { -1, -1 } },
    { {{ 0, 0, 3, 2 }}, {  0, 0 }, { -1, -1 }, { -1,  0 } },
    { {{ 0, 2, 3, 5 }}, { -1, 0 }, { -1, -1 }, {  0, -1 } },
    { {{ 0, 2, 5, 4 }}, { -1, 0 }, {  0, -1 }, {  0,  0 } },
};

VertexPosition D_800DCB28[6] = {
    { -64, 0,  32 },
    { -64, 0, -32 },
    {   0, 0,  32 },
    {   0, 0, -32 },
    {  64, 0,  32 },
    {  64, 0, -32 },
};

/*******************************/

/************ .bss ************/

f32 D_8011D4D0;
s32 gTajSoundMask;
s32 gTTSoundMask;
s32 D_8011D4DC;
s16 D_8011D4E0;
s16 D_8011D4E2; // Taj Voice clips

/******************************/

void obj_init_scenery(Object *obj, LevelObjectEntry_Scenery *entry) {
    f32 phi_f0;
    obj->segment.trans.unk6 |= 2;
    phi_f0 = entry->unk9 & 0xFF;
    if (phi_f0 < 10) {
        phi_f0 = 10;
    }
    phi_f0 /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * phi_f0;
    ((Object_50_Scenery *)obj->unk50)->unk0 = obj->segment.header->unk4 * phi_f0;
    obj->segment.unk3A = entry->unk8;
    obj->segment.trans.y_rotation = entry->unkA << 6 << 4;
    if (entry->unkB) {
        obj->unk4C->unk14 = 1;
        obj->unk4C->unk11 = 1;
        obj->unk4C->unk10 = 20;
        obj->unk4C->unk12 = 0;
        obj->unk4C->unk16 = -5;
        obj->unk4C->unk17 = entry->unkB;
    }
    if (obj->segment.unk3A >= obj->segment.header->numberOfModelIds) {
        obj->segment.unk3A = 0;
    }
    obj->unk78 = 0;
    obj->unk7C.word = 0;
}

void obj_loop_scenery(Object *obj, s32 speed) {
	Object78_80033DD0 *obj78;
	s32 temp_v0;

    if (obj->unk4C != NULL) {
        obj78 = (Object78_80033DD0 *) &obj->unk78;
        if (obj->unk7C.half.upper > 0) {
            obj78->unk4 -= speed;
        }
        if ((obj->unk4C->unk14 & 0x40) && ((s32) obj78->unk4 <= 0)) {
            func_80009558(SOUND_TWANG, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
            obj78->unk0 = (s32*) obj->unk4C->unk0;
            obj78->unk6 = 1820;
            obj78->unk4 = 10;
            if (get_number_of_active_players() < 2) {
                if (obj->segment.header->unk57 > 0) {
                    if (obj->segment.header->unk57 == 1) {
                        temp_v0 = 0;
                    } else {
                        temp_v0 = get_random_number_from_range(0, obj->segment.header->unk57 - 1);
                    }
                    obj->unk74 = 1 << temp_v0;
                    func_800AFC3C(obj, 2);
                }
            }
        } else if (obj78->unk4 <= 0) {
            obj78->unk0 = 0;
        }
        obj->segment.trans.z_rotation = (s16) obj78->unk6;
        obj78->unk6 = (obj78->unk6 * -200) >> 8;
    }
}

void obj_init_fireball_octoweapon(Object *obj, UNUSED LevelObjectEntry_Fireball_Octoweapon *entry) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
}

#ifdef NON_MATCHING
// Has a minor regalloc issue with obj4C_obj.

typedef struct Object80033F60_64 {
	u8 pad0[0x1C];
	s32 *unk1C;
	u8 pad20[0x8];
	s32 unk28;
} Object80033F60_64;

typedef struct Object80033F60_4C_64 {
	s16 unk0;
	u8 pad2[0x185];
	s8 unk187;
	u8 pad188[0x7C];
	s16 unk204;
} Object80033F60_4C_64;

void obj_loop_fireball_octoweapon(Object *obj, s32 speed) {
	ObjectTransform *trans78;
	Object_4C *obj4C;
	f32 sp7C;
	Object80033F60_4C_64 *obj4C_obj64;
	Object80033F60_64 *obj64;
	Object *obj4C_obj;
	f32 phi_f2;
    s32 *temp;
	f32 sp4C[7];

    trans78 = obj->trans78;

    sp7C = speed;
    if (osTvType == TV_TYPE_PAL) {
        sp7C *= 1.2;
    }

    if ((obj->behaviorId == 116) && (obj->unk7C.word < 0)) {
        obj->segment.trans.x_position = 0.0f;
        obj->segment.trans.y_position = 0.0f;
        obj->segment.trans.z_position = 0.0f;
        func_80011560();
        func_80011570(obj, trans78->x_position, trans78->y_position, trans78->z_position);
    } else {
        phi_f2 = (trans78->x_position - obj->segment.trans.x_position) * 0.1;
        if (phi_f2 > 10.0) {
            phi_f2 = 10.0f;
        }
        if (phi_f2 < -10.0) {
            phi_f2 = -10.0f;
        }
        obj->segment.x_velocity += (phi_f2 - obj->segment.x_velocity) * 0.125 * sp7C;
        phi_f2 = (trans78->y_position - obj->segment.trans.y_position) * 0.1;
        if (phi_f2 > 10.0) {
            phi_f2 = 10.0f;
        }
        if (phi_f2 < -10.0) {
            phi_f2 = -10.0f;
        }
        obj->segment.y_velocity += (phi_f2 - obj->segment.y_velocity) * 0.125 * sp7C;
        phi_f2 = (trans78->z_position - obj->segment.trans.z_position) * 0.1;
        if (phi_f2 > 10.0) {
            phi_f2 = 10.0f;
        }
        if (phi_f2 < -10.0) {
            phi_f2 = -10.0f;
        }
        obj->segment.z_velocity += (phi_f2 - obj->segment.z_velocity) * 0.125 * sp7C;
        if (sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) + (obj->segment.z_velocity * obj->segment.z_velocity)) > 0.5) {
            obj->segment.trans.y_rotation = arctan2_f(obj->segment.x_velocity, obj->segment.z_velocity);
            obj->segment.trans.x_rotation -= speed << 9;
        }
        func_80011570(obj, obj->segment.x_velocity * sp7C, obj->segment.y_velocity * sp7C, obj->segment.z_velocity * sp7C);
        if (obj->unk4A == 298 && func_8002AD08(obj->segment.trans.y_position, sp4C, 0)) {
			obj->segment.trans.y_position = sp4C[0];
        }
    }
    obj->segment.unk18 += speed * 10;
    obj64 = (Object80033F60_64 *) obj->unk64;
    obj4C = obj->unk4C;
    obj4C_obj = (Object*)obj4C->unk0; // This should be a0, not v1!
    if ((obj4C_obj != NULL) && (obj4C->unk13 < 60) && (obj4C_obj->segment.header->behaviorId == 1)) {
        obj4C_obj64 = (Object80033F60_4C_64 *) obj4C_obj->unk64;
        if (obj4C_obj64->unk0 != -1) {
            if (obj->behaviorId == 108) {
                obj4C_obj64->unk187 = 1;
                obj->unk7C.word = 20;
                func_8003FC44(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 44, 17, 1.0f, 1);
                gParticlePtrList_addObject(obj);
            } else if (obj->unk7C.word > 0) {
                obj4C_obj64->unk204 = 60;
                obj->unk7C.word = -60;
                obj->unk78 = (s32) obj4C_obj;
                play_sound_global(SOUND_BUBBLE_RISE, obj64->unk1C);
            }
        }
    }
    if (obj->behaviorId == 108) {
        obj->unk74 = 1;
        func_800AFC3C(obj, speed);
        obj->unk7C.word -= speed;
        if (obj->unk7C.word < 0) {
            if (obj->unk4A == 298) {
                gParticlePtrList_addObject(obj);
                func_8003FC44(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 44, 17, 1.0f, 1);
            }
            obj->segment.trans.scale *= 0.9;
            if (obj->segment.trans.scale < 0.5) {
                gParticlePtrList_addObject(obj);
            }
        }
    } else {
        if (obj->unk7C.word < 0) {
            obj->unk7C.word += speed;
            if (obj->unk7C.word >= 0) {
                obj->unk7C.word = 0;
            }
        } else {
            obj->unk7C.word -= speed;
            if (obj->unk7C.word <= 0) {
                obj->unk7C.word = 0;
            }
        }
        if (obj->unk7C.word == 0) {
            temp = obj64->unk1C;
            if (temp != 0) {
                func_8000488C(temp);
            }
            func_80009558(SOUND_POP, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, 0);
            gParticlePtrList_addObject(obj);
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_fireball_octoweapon.s")
#endif

void obj_init_lasergun(Object *obj, LevelObjectEntry_Lasergun *entry) {
    Object_LaserGun *obj64;
    obj->unk4C->unk14 = 0x22;
    obj->unk4C->unk11 = 0;
    obj64 = &obj->unk64->laser_gun;
    obj64->unkE = entry->unkA;
    obj64->unkF = entry->unkB;
    obj64->unk10 = entry->unkC;
    obj64->unk11 = entry->unkD;
    obj64->unkC = obj64->unkF;
    obj->segment.trans.y_rotation = entry->unk8 << 4 << 4; // Not sure about the shift amounts here, but it
    obj->segment.trans.x_rotation = entry->unk9 << 4 << 4; // just needs to be 2 left shifts that add up to 8.
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_lasergun.s")

void obj_init_laserbolt(Object *obj, UNUSED LevelObjectEntry_Laserbolt *entry) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
}

typedef struct Object_7C_80034860 {
	u8 pad0[0xC];
	s16 unkC;
} Object_7C_80034860;

void obj_loop_laserbolt(Object *obj, s32 speed) {
	f32 sp5C;

	Object *obj4C_obj;

	Object_7C_80034860 *obj7C;
	Object_Laser *obj4C_obj64;

	s8 sp4F; // Boolean
	s8 sp4E;
	f32 sp48;
	f32 sp44;
	f32 sp40;
	f32 sp3C;
	s32 sp38; // Boolean


    sp4F = FALSE;
    sp5C = speed;
    if (osTvType == TV_TYPE_PAL) {
        sp5C *= 1.2;
    }
    sp40 = obj->segment.trans.x_position + (obj->segment.x_velocity * sp5C);
    sp44 = obj->segment.trans.y_position + (obj->segment.y_velocity * sp5C);
    sp48 = obj->segment.trans.z_position + (obj->segment.z_velocity * sp5C);
    sp3C = 9.0f;

    func_80031130(1, &obj->segment.trans.x_position, &sp40, -1);
    sp38 = FALSE;
    func_80031600(&obj->segment.trans.x_position, &sp40, &sp3C, &sp4E, 1, &sp38);
    if (sp38) {
        obj->segment.x_velocity = (sp40 - obj->segment.trans.x_position) / sp5C;
        obj->segment.y_velocity = (sp44 - obj->segment.trans.y_position) / sp5C;
        obj->segment.z_velocity = (sp48 - obj->segment.trans.z_position) / sp5C;
    }
    func_80011570(obj, obj->segment.x_velocity * sp5C, obj->segment.y_velocity * sp5C, obj->segment.z_velocity * sp5C);
    if (sp38) {
        func_8003FC44(obj->segment.trans.x_position, obj->segment.trans.y_position - 36.0f, obj->segment.trans.z_position, 44, 0, 0.2, 0);
        sp4F = TRUE;
    }

    if (obj->unk78 > 0) {
        obj->unk78 -= speed;
    } else {
        sp4F = TRUE;
    }

    if (obj->unk4C->unk13 < 80) {
        obj4C_obj = (Object*)obj->unk4C->unk0;
        if (obj4C_obj && (obj4C_obj->behaviorId == 1)) {
            obj4C_obj64 = &obj4C_obj->unk64->laser;
            sp4F = TRUE;
            if (obj4C_obj64->unk0 != -1) {
                obj4C_obj64->unk187 = 1;
            }
            obj7C = (Object_7C_80034860 *)obj->unk7C.word;
            if (obj7C) {
                obj7C->unkC = 180;
            }
            sp4F = TRUE;
            func_8003FC44(obj->segment.trans.x_position, obj->segment.trans.y_position - 36.0f, obj->segment.trans.z_position, 44, 17, 0.5, 0);
        }
    }
    if (sp4F) {
        gParticlePtrList_addObject(obj);
    }
}

void obj_init_torch_mist(Object *obj, LevelObjectEntry_Torch_Mist *entry) {
    f32 phi_f0 = (s32)(entry->unk9 & 0xFF);
    if (phi_f0 < 10.0f) {
        phi_f0 = 10.0f;
    }
    phi_f0 /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * phi_f0;
    obj->unk78 = entry->unk8;
}

void obj_loop_torch_mist(Object *obj, s32 speed) {
    obj->segment.unk18 += obj->unk78 * speed;
}

void obj_init_effectbox(UNUSED Object *obj, UNUSED LevelObjectEntry_EffectBox *entry) {
}

#ifdef NON_MATCHING
// Has regalloc issues

void obj_loop_effectbox(Object *obj, UNUSED s32 speed) {
    Object **objList;
    Object_EffectBox *curObj64;
    s32 numberOfObjects;
    LevelObjectEntry_EffectBox *level_entry;
    s32 i;
    f32 xDiff;
    f32 yDiff;
    f32 zDiff;
    f32 temp0;
    f32 temp1;
    f32 temp2;
    f32 temp3;
    f32 temp4;
    f32 temp5;

    level_entry = &obj->segment.unk3C_a.level_entry->effectBox;
    objList = get_racer_objects(&numberOfObjects);
    temp0 = coss_f((level_entry->unkB << 8) * -1);
    temp1 = sins_f((level_entry->unkB << 8) * -1);
    temp2 = level_entry->unk8 * 3;
    temp3 = level_entry->unk9 * 3;
    temp4 = level_entry->unkA * 3;
    for (i = 0; i < numberOfObjects; i++)
    {
        xDiff = objList[i]->segment.trans.x_position - obj->segment.trans.x_position;
        yDiff = objList[i]->segment.trans.y_position - obj->segment.trans.y_position;
        zDiff = objList[i]->segment.trans.z_position - obj->segment.trans.z_position;
        if ((-temp3 < yDiff) && (yDiff < temp3)) {
            temp5 = (xDiff * temp0) + (zDiff * temp1);
            if ((-temp2 < temp5) && (temp5 < temp2)) {
                temp5 = (-xDiff * temp1) + (zDiff * temp0);
                if ((-temp4 < temp5) && (temp5 < temp4)) {
                    curObj64 = &objList[i]->unk64->effect_box;
                    curObj64->unk1FE = level_entry->unkC;
                    curObj64->unk1FF = level_entry->unkD;
                    temp5 = temp3 / 2;
                    if ((temp5 < yDiff) && (curObj64->unk1FE == 1)) {
                        temp5 = (1.0 - ((yDiff - temp5) / temp5));
                        curObj64->unk1FF *= temp5;
                    }
                }
            }
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_effectbox.s")
#endif

void obj_init_trophycab(Object *obj, LevelObjectEntry_TrophyCab *entry) {
    obj->unk4C->unk14 = 1;
    obj->unk4C->unk11 = 2;
    obj->segment.trans.y_rotation = entry->rotation << 6 << 4; // Not sure about the values here.
}

/**
 * Trophy Cabinet loop behaviour.
 * Displays the dialogue when ran into.
 * Has unused behaviour that presumably would've handled activating the dialogue from here.
*/
void obj_loop_trophycab(Object *obj, s32 updateRate) {
    Settings* settings;
    Object_TrophyCabinet *gfxData;
    f32 dist;
    LevelObjectEntryCommon newObject;
    LevelHeader* header;
    Object* tempObj;
    f32 diffX;
    s32 dialogueID;
    f32 diffZ;
    UNUSED s32 pad2;
    s32 worldBalloons;
    s32 bossFlags;

    settings = get_settings();
    header = get_current_level_header();
    gfxData = (Object_TrophyCabinet *)obj->unk64;
    if (obj->unk7C.word == 0) {
        if (header->race_type != RACETYPE_CUTSCENE_2 && header->race_type != RACETYPE_CUTSCENE_1) {
            obj->unk7C.word = 1;
            if ((settings->trophies >> (((settings->worldId - 1) ^ 0) * 2)) & 3) {
                newObject.objectID = 0x80;
                newObject.x = obj->segment.unk3C_a.level_entry->animation.common.x;
                newObject.y = obj->segment.unk3C_a.level_entry->animation.common.y;
                newObject.z = obj->segment.unk3C_a.level_entry->animation.common.z;
                newObject.size = 8;
                tempObj = spawn_object(&newObject, 1);
                if (tempObj != NULL) {
                    tempObj->segment.unk3C_a.level_entry = NULL;
                    tempObj->segment.trans.y_rotation = obj->segment.trans.y_rotation;
                }
            }
        }
    }
    obj->unk54->unk2C = 0.612f;
    obj->unk54->unk28 = 0.0f;
    tempObj = get_racer_object(PLAYER_ONE);
    if (tempObj != NULL) {
        diffX = obj->segment.trans.x_position - tempObj->segment.trans.x_position;
        diffZ = obj->segment.trans.z_position - tempObj->segment.trans.z_position;
        dist = sqrtf((diffX * diffX) + (diffZ * diffZ)); // unused
        bossFlags = settings->bosses;
        bossFlags |= 0x800;
        worldBalloons = (settings->balloonsPtr[settings->worldId] >= 8);
        if (worldBalloons) {
            worldBalloons = ((1 << (settings->worldId + 6)) & bossFlags) != 0;
        }
        if (obj->unk78 == NULL && func_800C3400() == FALSE) {
            if (obj->unk5C->unk100 != NULL) {
                if (gfxData->unk4 == 0) {
                    if (worldBalloons) {
                        obj->unk78 = 1;
                        play_sound_global(SOUND_VOICE_TT_TROPHY_RACE, NULL);
                        func_800A3870();
                    } else {
                        func_800C31EC(4);
                        gfxData->unk4 = 180;
                        gfxData->unk0 = 140;
                        set_sndfx_player_voice_limit(16);
                        set_music_fade_timer(-8);
                        play_sequence(SEQUENCE_NO_TROPHY_FOR_YOU);
                    }
                }
            }
        }
        if (gfxData->unk0 && func_80001C08() == 0) {
            if (updateRate < gfxData->unk0) {
                gfxData->unk0 -= updateRate;
            } else {
                gfxData->unk0 = 0;
                set_music_fade_timer(8);
                set_sndfx_player_voice_limit(6);
            }
        }
        if (obj->unk5C->unk100 != NULL || func_800C3400()) {
            gfxData->unk4 = 180;
        }
        if (gfxData->unk4 > 0) {
            gfxData->unk4 -= updateRate;
        } else {
            gfxData->unk4 = 0;
        }
        if (obj->unk78 == 1) {
            func_800AB1AC(3);
            func_800AB1D4(0U);
            dialogueID = func_8009CFEC(4);
            if (dialogueID) {
                obj->unk78 = NULL;
                func_8009CF68(4);
                if (dialogueID == 1) {
                    func_8006F254();
                    obj->unk78 = 2;
                } else {
                    func_800AB1D4(1);
                }
            }
            func_8005A3B0();
        }
        obj->unk5C->unk100 = NULL;
        if (worldBalloons) {
            obj->unk54->unk28 = 0.552f;
        }
    }
}

void obj_init_collectegg(Object *obj, UNUSED LevelObjectEntry_CollectEgg *entry) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
}

void obj_loop_collectegg(Object *obj, s32 updateRate) {
    Object_CollectEgg *egg;
    Object *racerObj;
    Object_Racer *racer;
    f32 sp40[3];
    f32 sp3C;
    f32 speed;
    s32 sp34;
    s8 sp33;

    egg = (Object_CollectEgg *) obj->unk64;
    speed = updateRate;
    if (osTvType == TV_TYPE_PAL) {
        speed *= 1.2;
    }
    switch (egg->unkB) {
    case 0:
        func_80036040(obj, (Object_64 *) egg);
        break;
    case 2:
        obj->segment.trans.unk6 &= 0xBFFF;
        sp40[0] = obj->segment.trans.x_position + (obj->segment.x_velocity * speed);
        sp40[1] = obj->segment.trans.y_position + (obj->segment.y_velocity * speed);
        sp40[2] = obj->segment.trans.z_position + (obj->segment.z_velocity * speed);
        sp3C = 9.0f;
        func_80031130(1, &obj->segment.trans.x_position, sp40, -1);
        sp34 = 0;
        sp33 = 0;
        func_80031600(&obj->segment.trans.x_position, sp40, &sp3C, &sp33, 1, &sp34);
        obj->segment.x_velocity = (sp40[0] - obj->segment.trans.x_position) / speed;
        obj->segment.y_velocity = (sp40[1] - obj->segment.trans.y_position) / speed;
        obj->segment.z_velocity = (sp40[2] - obj->segment.trans.z_position) / speed;
        obj->segment.trans.x_position = sp40[0];
        obj->segment.trans.y_position = sp40[1];
        obj->segment.trans.z_position = sp40[2];
        obj->segment.y_velocity -= 0.5;
        obj->segment.x_velocity *= 0.98;
        obj->segment.z_velocity *= 0.98;
        obj->segment.y_velocity *= 0.95;
        if (obj->segment.trans.y_position < -2000.0f || (sp34 != 0 && (sp33 < 5 || sp33 >= 10))) {
            if (egg->unk4 != NULL) {
                egg->unk4->unk78 = 0;
            }
            gParticlePtrList_addObject(obj);
        }
        if (sp34 != 0 && sp33 == 5) {
            egg->unkB = 0;
            obj->segment.x_velocity = 0.0f;
            obj->segment.z_velocity = 0.0f;
        }
        if (sp34 != 0 && sp33 >= 6 && sp33 < 10) {
            egg->unkA = sp33 - 6;
            egg->unkB = 3;
            racerObj = get_racer_object(egg->unkA);
            if (racerObj != NULL) {
                racer = (Object_Racer *) racerObj->unk64;
                racer->unk1CF += 1;
            }
            egg->unk8 = 600;
            obj->segment.x_velocity = 0.0f;
            obj->segment.z_velocity = 0.0f;
        }
        break;
    case 3:
        egg->unk8 -= updateRate;
        racerObj = get_racer_object(egg->unkA);
        if (racerObj != NULL) {
            racer = (Object_Racer *) racerObj->unk64;
        }
        if (egg->unk8 <= 0) {
            if (racerObj != NULL) {
                racer->lap += 1;
            }
            egg->unkB = 4;
            egg->unk4->unk78 = 0;
        }
        if (egg->unk8 < 540) {
            func_80036040(obj, (Object_64 *) egg);
        }
        if (racerObj != NULL && egg->unkB != 3) {
            racer->unk1CF -= 1;
        }
        break;
    case 4:
        racerObj = get_racer_object(egg->unkA);
        if (racerObj != NULL) {
            racer = (Object_Racer *) racerObj->unk64;
            if (racer->lap >= 3) {
                racer->raceFinished = TRUE;
            }
        }
        obj->segment.unk18 = 0x80;
        break;
    }
}

void obj_init_eggcreator(UNUSED Object *obj, UNUSED LevelObjectEntry_EggCreator *entry) {
}

void obj_loop_eggcreator(Object *obj, UNUSED s32 speed) {
    unk8003564C sp20;
    Object *someObj;

    if (obj->unk78 == 0) {
        sp20.unk2 = obj->segment.trans.x_position;
        sp20.unk4 = obj->segment.trans.y_position;
        sp20.unk6 = obj->segment.trans.z_position;
        sp20.unk1 = 8;
        sp20.unk0 = 0x34;
        someObj = spawn_object(&sp20, 1);
        if (someObj != NULL) {
            Object_EggCreator *someObj64 = &someObj->unk64->egg_creator;
            someObj64->unk4 = obj;
            obj->unk78 = (s32) someObj;
            someObj->segment.unk3C_a.level_entry = NULL;
        }
    }
}

void obj_init_lighthouse_rocketsignpost(Object *obj, LevelObjectEntry_Lighthouse_RocketSignpost *entry) {
    f32 phi_f0 = entry->unk9 & 0xFF;
    if (phi_f0 < 10) {
        phi_f0 = 10;
    }
    phi_f0 /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * phi_f0;
    obj->segment.trans.y_rotation = entry->unkA << 6 << 4;
    if (obj->segment.unk3A >= obj->segment.header->numberOfModelIds) {
        obj->segment.unk3A = 0;
    }
    obj->unk4C->unk14 = 1;
    obj->unk4C->unk11 = 2;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
}

void obj_loop_rocketsignpost(Object *obj, UNUSED s32 speed) {
    Object *playerObj;
    Object_4C *obj4C;

    playerObj = get_racer_object(0);
    if (playerObj != NULL) {
        obj4C = obj->unk4C;
        if (obj4C->unk13 < 0xC8) {
            if (playerObj == obj4C->unk0) {
                // Detect if the player honks or slams into the signpost.
                if ((get_buttons_pressed_from_player(PLAYER_ONE) & Z_TRIG) || playerObj == obj->unk5C->unk100) {
                    func_8006F29C();
                }
            }
        }
    }
    obj->unk4C->unk13 = 0xFF;
}

void obj_init_airzippers_waterzippers(Object *obj, LevelObjectEntry_AirZippers_WaterZippers *entry) {
    ObjectHeader *objHeader;
    f32 phi_f0;

    phi_f0 = entry->unk9 & 0xFF;
    if (phi_f0 < 10.0f) {
        phi_f0 = 10.0f;
    }
    objHeader = obj->segment.header;
    phi_f0 /= 64;
    obj->segment.trans.scale = objHeader->scale * phi_f0;
    obj->segment.trans.y_rotation = entry->unkA << 6 << 4;
    if (obj->segment.unk3A >= objHeader->numberOfModelIds) {
        obj->segment.unk3A = 0;
    }
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
    if (get_filtered_cheats() & CHEAT_TURN_OFF_ZIPPERS) {
        gParticlePtrList_addObject(obj);
    }
}


void obj_loop_airzippers_waterzippers(Object *obj, UNUSED s32 speed) {
    Object *curRacerObj;
    Object_Racer *racer;
    f32 xDiff;
    f32 yDiff;
    f32 zDiff;
    s32 numObjects;
    Object** racerObjs;
    s32 i;

    if (find_non_car_racers() == FALSE) {
        obj->segment.trans.unk6 |= 0x4000;
    } else {
        obj->segment.trans.unk6 &= 0xBFFF;
    }
    if ((obj->unk4C->unk13 < 100) && !(obj->segment.trans.unk6 & 0x4000)) {
        racerObjs = get_racer_objects(&numObjects);
        for (i = 0; i < numObjects; i++) {
            curRacerObj = racerObjs[i];
            racer = &curRacerObj->unk64->racer;
            if ((racer->unk1F5 == 0) && (racer->boostTimer < 15)) {
                xDiff = curRacerObj->segment.trans.x_position - obj->segment.trans.x_position;
                yDiff = curRacerObj->segment.trans.y_position - obj->segment.trans.y_position;
                zDiff = curRacerObj->segment.trans.z_position - obj->segment.trans.z_position;
                if ((s32) sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff)) < 100) {
                    racer->unk1F5 = 1;
                    racer->unk14C = obj;
                }
            }
        }
    }
}

void obj_init_groundzipper(Object *arg0, LevelObjectEntry_GroundZipper *entry) {
    ObjectHeader *header;
    f32 objScale;

    objScale = entry->scale & 0xFF;
    if (objScale < 10.0f) {
        objScale = 10.0f;
    }
    objScale /= 64;
    header = arg0->segment.header;
    arg0->segment.trans.scale = header->scale * objScale;
    arg0->unk50->unk0 = header->unk4 * objScale;
    arg0->segment.trans.y_rotation = entry->rotation << 6 << 4;
    if (arg0->segment.unk3A >= arg0->segment.header->numberOfModelIds) {
        arg0->segment.unk3A = 0;
    }
    arg0->unk78 = (s32)(28.0f * objScale) + 15;
    if (arg0->unk78 < 0) {
        arg0->unk78 = 0;
    }
    if (arg0->unk78 >= 0x100) {
        arg0->unk78 = 0xFF;
    }
    arg0->unk4C->unk14 = 2;
    arg0->unk4C->unk11 = 0;
    arg0->unk4C->unk10 = 0x14;
    arg0->unk4C->unk12 = 0;
    arg0->unk4C->unk16 = -0x64;
    arg0->unk4C->unk17 = 0x64;
    if (get_filtered_cheats() & CHEAT_TURN_OFF_ZIPPERS) {
        gParticlePtrList_addObject(arg0);
    }
}

void obj_loop_groundzipper(Object *obj, UNUSED s32 speed) {
    Object *curRacerObj;
    Object_Racer *racer;
    f32 xDiff;
    f32 yDiff;
    s32 numObjects;
    f32 zDiff;
    Object** racerObjs;
    s32 i;

    obj->segment.trans.unk6 &= 0xBFFF;
    obj->segment.trans.unk6 |= 0x1000;
    get_racer_object(0); // Unused. I guess the developers forgot to remove this?
    if ((s32) obj->unk4C->unk13 < obj->unk78) {
        racerObjs = get_racer_objects(&numObjects);
        for (i = 0; i < numObjects; i++) {
            curRacerObj = racerObjs[i];
            racer = &curRacerObj->unk64->racer;
            if ((racer->boostTimer < 15) && (racer->unk1E2 != 0)) {
                xDiff = curRacerObj->segment.trans.x_position - obj->segment.trans.x_position;
                yDiff = curRacerObj->segment.trans.y_position - obj->segment.trans.y_position;
                zDiff = curRacerObj->segment.trans.z_position - obj->segment.trans.z_position;
                if ((s32) sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff)) < obj->unk78) {
                    if (racer->playerIndex != PLAYER_COMPUTER) {
                        play_sound_spatial(SOUND_ZIP_PAD_BOOST, curRacerObj->segment.trans.x_position, curRacerObj->segment.trans.y_position, curRacerObj->segment.trans.z_position, NULL);
                    }
                    racer->boostTimer = normalise_time(45);
                    racer->boostType = BOOST_LARGE;
                    if (racer->throttleReleased) {
                        racer->boostType |= BOOST_SMALL_FAST;
                    }
                    if (racer->raceFinished == FALSE) {
                        func_80072348(racer->playerIndex, 8);
                    }
                }
            }
        }
    }
}

void obj_init_unknown58(Object *obj, UNUSED LevelObjectEntry_Unknown58 *entry) {
    obj->unk78 = 0;
    obj->unk7C.word = (s32) obj->segment.header;
}

void obj_loop_unknown58(Object *obj, s32 speed) {
    Object *someObj;
    Object *someOtherObj;
    Object_UnkId58 *someOtherObj64;
    Object_60 *obj60;

    obj->segment.unk3B = 0;
    obj->segment.unk18 = 0x28;
    if (func_8001139C() == 0) {
        obj->unk78 += speed;
    }
    set_ghost_position_and_rotation(obj);
    func_800AFC3C(obj, speed);
    someOtherObj = get_racer_object(0);
    someOtherObj64 = &someOtherObj->unk64->unkid58;
    obj60 = obj->unk60;
    if (obj60->unk0 == 1) {
        s8 temp = someOtherObj64->unk1D6;
        if ((temp == 1) || (temp == 2)) {
            someObj = (Object *)obj60->unk4;
            someObj->segment.trans.y_rotation = 0x4000;
            someObj->segment.unk3A++;
            someObj->segment.unk3A &= 1;
        }
    }
}

void obj_init_characterflag(Object *obj, LevelObjectEntry_CharacterFlag *entry) {
    f32 phi_f0;
    obj->unk78 = (s32)entry->unkE;
    obj->unk7C.word = -1;
    obj->segment.trans.y_rotation = entry->unkC << 6 << 4; // Not sure about the values here.
    phi_f0 = (f32)(entry->unkA & 0xFF);
    if (phi_f0 < 10.0f) {
        phi_f0 = 10.0f;
    }
    phi_f0 /= 64;
    obj->segment.trans.scale = (f32)(obj->segment.header->scale * phi_f0);
}

void obj_loop_characterflag(Object *obj, UNUSED s32 speed) {
    s32 temp_t4;
    s32 temp_t5;
    Object *someObj;
    Object_CharacterFlag *obj64;
    Object_Racer *someObj64;

    if (obj->unk7C.word < 0) {
        someObj = get_racer_object(obj->unk78);
        if (someObj != NULL) {
            obj64 = &obj->unk64->character_flag;
            someObj64 = &someObj->unk64->racer;
            obj->unk7C.word = someObj64->characterId;
            if (obj->unk7C.word < 0 || obj->unk7C.word >= 0xA) {
                obj->unk7C.word = 0;
            }
            obj64->unk20 = D_800DC980;
            obj64->unk24 = (u8 *) obj->unk68[obj->unk7C.word];
            temp_t4 = (obj64->unk24[0] - 1) << 0x15;
            temp_t5 = (obj64->unk24[1] - 1) << 5;
            obj64->unk0 = 0x40000103;
            obj64->unk4 = 0;
            obj64->unk8 = temp_t4;
            obj64->unkC = temp_t5;
            obj64->unk10 = 0x40010203;
            obj64->unk14 = temp_t4;
            obj64->unk18 = (s32)(temp_t4 | temp_t5);
            obj64->unk1C = temp_t5;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80036040.s")

void obj_init_stopwatchman(Object *obj, UNUSED LevelObjectEntry_StopWatchMan *entry) {
    Object_TT *temp;
    obj->unk4C->unk14 = 1;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x1E;
    obj->unk4C->unk12 = 0;
    temp = &obj->unk64->tt;
    temp->unkD = 0xFF;
    temp->unk0 = 0.0f;
    gTTSoundMask = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_stopwatchman.s")

/**
 * If TT is currently talking, clear the audio associated with gTTSoundMask,
 * then play the new sound ID in its place.
 */
void play_tt_voice_clip(u16 soundID, s32 interrupt) {
    if (gTTSoundMask && interrupt & 1) {
        func_8000488C(gTTSoundMask); //This is likely wrong and will need to be fixed
        gTTSoundMask = 0;
    }
    if (gTTSoundMask == 0) {
        play_sound_global(soundID, &gTTSoundMask);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_init_fish.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_fish.s")

void obj_init_lavaspurt(Object *obj, LevelObjectEntry_LavaSpurt *entry) {
    obj->unk78 = entry->unk9 * 2;
    obj->unk7C.word = entry->unk8;
}

void obj_loop_lavaspurt(Object *obj, s32 speed) {
    if (obj->unk78 > 0) {
        obj->unk78 -= speed;
        obj->segment.trans.unk6 |= 0x4000;
    } else {
        obj->segment.trans.unk6 &= ~0x4000;
        obj->segment.unk18 += speed * 4;
        if (obj->segment.unk18 >= 256) {
            obj->segment.unk18 = 0;
            obj->unk78 = get_random_number_from_range(0, 30) + obj->unk7C.word;
        }
    }
}

void obj_init_posarrow(Object *obj, UNUSED LevelObjectEntry_PosArrow *entry) {
    obj->segment.trans.unk6 |= 0x4000;
}

void obj_loop_posarrow(Object *obj, UNUSED s32 speed) {
    Object_PosArrow *someObj64;
    Object **someObjList;
    Object *someObj;
    s32 numberOfObjects;

    obj->segment.trans.unk6 |= 0x4000;
    someObjList = get_racer_objects_by_position(&numberOfObjects);
    if (obj->unk78 < numberOfObjects) {
        someObj = someObjList[obj->unk78];
        someObj64 = &someObj->unk64->pos_arrow;
        if (someObj64->unk0 == -1) {
            obj->segment.trans.unk6 &= ~0x4000;
            someObj64->unk150 = obj;
        }
        obj->segment.unk18 = obj->unk78 * 127;
    }
}

void obj_init_animator(Object *obj, LevelObjectEntry_Animator *entry, s32 arg2) {
    Object_Animator *obj64;
    LevelModel *levelModel;
    s16 segmentBatchCount;

    obj64 = &obj->unk64->animator;
    levelModel = get_current_level_model();
    obj64->batchId = entry->unk8;
    obj64->xSpeedFactor = entry->unk9;
    obj64->ySpeedFactor = entry->unkA;
    obj64->segmentId = get_level_segment_index_from_position(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
    if (arg2 == 0) {
        obj64->xSpeed = 0;
        obj64->ySpeed = 0;
    }
    if (obj64->segmentId != -1) {
        if (obj64->batchId < 0) {
            obj64->batchId = 0;
        }
        segmentBatchCount = levelModel->segments[obj64->segmentId].numberOfBatches;
        if (obj64->batchId >= segmentBatchCount) {
            obj64->batchId = segmentBatchCount - 1;
        }
    }
    obj_loop_animator(obj, 0x20000);
}

#ifdef NON_EQUIVALENT

#define TEX_INDEX_NO_TEXTURE 255

// Has minor issues

void obj_loop_animator(Object* obj, s32 speed) {
    Object_Animator* obj64; // 3C
    s32 sp20;
    s32 sp1C;
    LevelModel* levelModel;
    s32 temp, temp2, segmentId, batchId;
    s32 i;
    s32 nextFacesOffset;
    s32 curFacesOffset;
    s32 texUVSpeed;
    s32 texIndex;
    TextureInfo *texInfo;
    TriangleBatchInfo *triangleBatchInfo;
    LevelModelSegment *levelModelSegment;
    Triangle* triangle;
    TextureHeader *tex;
    s32 maxSpeed;

    obj64 = &obj->unk64->animator;

    temp = obj64->xSpeedFactor * speed;
    obj64->xSpeed += temp << 4;
    sp20 = obj64->xSpeed >> 4;
    obj64->xSpeed &= 0xF;

    temp2 = obj64->ySpeedFactor * speed;
    obj64->ySpeed += temp2 << 4;
    sp1C = obj64->ySpeed >> 4;
    obj64->ySpeed &= 0xF;

    segmentId = obj64->segmentId;

    if (obj64->segmentId != -1) {
        levelModel = get_current_level_model();
        levelModelSegment = &levelModel->segments[segmentId];
        batchId = obj64->batchId;
        triangleBatchInfo = &levelModelSegment->batches[batchId];
        texIndex = triangleBatchInfo->textureIndex;
        curFacesOffset = triangleBatchInfo->facesOffset;
        nextFacesOffset = triangleBatchInfo[1].facesOffset;
        if (texIndex != TEX_INDEX_NO_TEXTURE) {
            texUVSpeed = levelModel->textures[texIndex].texture->width << 7;
            maxSpeed = texUVSpeed * 2;
            for (i = curFacesOffset; i < nextFacesOffset; i++) {
                triangle = &levelModelSegment->triangles[i];
                if (!(triangle->flags & 0x80)) {
                    if (maxSpeed < triangle->uv0.v) {
                        triangle->uv0.v -= texUVSpeed;
                        triangle->uv1.v -= texUVSpeed;
                        triangle->uv2.v -= texUVSpeed;
                    }
                    if (triangle->uv0.v < 0) {
                        triangle->uv0.v += texUVSpeed;
                        triangle->uv1.v += texUVSpeed;
                        triangle->uv2.v += texUVSpeed;
                    }
                    if (maxSpeed < triangle->uv0.u) {
                        triangle->uv0.u -= texUVSpeed;
                        triangle->uv1.u -= texUVSpeed;
                        triangle->uv2.u -= texUVSpeed;
                    }
                    if (triangle->uv0.u < 0) {
                        triangle->uv0.u += texUVSpeed;
                        triangle->uv1.u += texUVSpeed;
                        triangle->uv2.u += texUVSpeed;
                    }
                    triangle->uv0.v += sp1C;
                    triangle->uv1.v += sp1C;
                    triangle->uv2.v += sp1C;
                    triangle->uv0.u += sp20;
                    triangle->uv1.u += sp20;
                    triangle->uv2.u += sp20;
                }
            }
        }
    }
}

#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_animator.s")
#endif

void obj_init_animation(Object *obj, LevelObjectEntry_Animation *entry, s32 arg2) {
    Object_Animation* obj64;
    s8 tempOrderIndex;
    f32 scalef;

    scalef = entry->scale & 0xFF;
    if (scalef < 1.0f) {
        scalef = 1.0f;
    }
    scalef /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * scalef;
    obj->segment.trans.y_rotation = entry->y_rotation << 8;
    obj->segment.trans.x_rotation = entry->x_rotation << 8;
    obj->segment.trans.z_rotation = entry->z_rotation << 8;
    if (entry->actorIndex == -2) {
        entry->actorIndex = func_8001F3B8();
    } else {
        if (entry->actorIndex < 0 && entry->actorIndex >= -2) {
            entry->actorIndex = 0;
        }
        func_8001F3C8(entry->actorIndex);
    }
    if (entry->channel == -1) {
        entry->channel = func_8001E440();
    }
    if (entry->channel == 20) {
        entry->actorIndex |= 0x80;
    }
    tempOrderIndex = func_8001F3EC(entry->actorIndex);
    if (entry->order == -2) {
        entry->order = tempOrderIndex;
        if (entry->order < 0) {
            entry->order = 0;
        }
    } else {
        if ((tempOrderIndex >= 0) && (entry->order >= tempOrderIndex)) {
            entry->order = tempOrderIndex;
        }
        if (entry->order < 0) {
            entry->order = 0;
        }
    }
    func_80011390();
    obj->unk7C.word = entry->actorIndex;
    obj->unk78 = arg2;
    if (arg2 != 0 && (get_buttons_pressed_from_player(PLAYER_ONE) & R_CBUTTONS)) {
        obj->unk78 = 2;
    }
    if (((func_8001E440() == entry->channel) || (entry->channel == 20)) && (obj->unk64 == NULL) && (entry->order == 0) && (entry->objectIdToSpawn != -1)) {
        func_8001F23C(obj, entry);
    }
    obj64 = &obj->unk64->animation;
    if (obj->unk64 != 0) {
        func_8001EFA4(obj, obj64);
        if (entry->order != 0 || obj64->unk4A != entry->objectIdToSpawn) {
            gParticlePtrList_addObject((Object *) obj64);
            obj->unk64 = NULL;
        }
    }
    if (func_80021600(obj->unk7C.word)) {
        func_8001EE74();
    }
}


void obj_loop_animobject(Object *obj, s32 speed) {
    func_8001F460(obj, speed, obj);
}

void obj_loop_dooropener(Object *obj, s32 speed) {
    s32 phi_a0;
    unk80037D08_arg0_64 *sp18;

    sp18 = (unk80037D08_arg0_64 *) obj->unk64;
    phi_a0 = 1 - func_8001F460(obj, speed, obj);
    if (sp18->unk2A > 0) {
        phi_a0 = 0;
    }
    func_800235D0(phi_a0);
}

void obj_init_overridepos(UNUSED Object *obj, UNUSED LevelObjectEntry_OverridePos *entry) {
}

UNUSED void func_80037D60(UNUSED s32 arg0, UNUSED s32 arg1) {
}

/**
 * Wizpig ship initilisation.
 * Does nothing.
*/
void obj_init_wizpigship(UNUSED Object *obj, UNUSED LevelObjectEntry_WizpigShip *entry) {
}

/**
 * Wizpig ship loop behaviour.
 * Periodically shoots laserbeams in front of it.
*/
void obj_loop_wizpigship(Object *wizShipObj, s32 updateRate) {
    s32 i;
    s32 index;
    f32 posX;
    f32 posY;
    f32 posZ;
    Object *newObj;
    ObjectModel *wizShipModel;
    Matrix shipMtx;
    Matrix laserMtx;
    LevelObjectEntryCommon newObject;
    ObjectTransform trans;

    func_8001F460(wizShipObj, updateRate, wizShipObj);
    if ((*wizShipObj->unk68) != NULL) {
        wizShipModel = (*wizShipObj->unk68)->objModel;
        if (wizShipObj->unk7C.word > 0) {
            wizShipObj->unk7C.word -= updateRate;
        } else {
            wizShipObj->unk7C.word = 0;
        }
        if ((wizShipObj->unk60 != NULL) && (wizShipObj->unk7C.word == 0)) {
            if (wizShipObj->unk74 & 1) {
                wizShipObj->unk7C.word = 0x14;
                object_transform_to_matrix(shipMtx, &wizShipObj->segment.trans);
                trans.x_position = 0.0f;
                trans.y_position = 0.0f;
                trans.z_position = 0.0f;
                trans.scale = 1.0f;
                trans.y_rotation = wizShipObj->segment.trans.y_rotation;
                trans.x_rotation = wizShipObj->segment.trans.x_rotation;
                trans.z_rotation = 0;
                object_transform_to_matrix(laserMtx, &trans);
                
                for (i = 0; i < wizShipObj->unk60->unk0; i++) {
                    index = wizShipObj->unk60->unk2C[i];
                    if ((index >= 0) && (index < wizShipModel->unk18)) {
                        if (wizShipObj->unk44 != NULL) {
                            posX = wizShipObj->unk44[wizShipModel->unk14[index]].x;
                            posY = wizShipObj->unk44[wizShipModel->unk14[index]].y;
                            posZ = wizShipObj->unk44[wizShipModel->unk14[index]].z;
                            guMtxXFMF(shipMtx, posX, posY, posZ, &posX, &posY, &posZ);
                            newObject.x = posX;
                            newObject.y = posY;
                            newObject.z = posZ;
                            newObject.size = 8;
                            newObject.objectID = 0xC6;
                            newObj = spawn_object(&newObject, 1);
                            if (newObj != NULL) {
                                newObj->segment.unk3C_a.level_entry = NULL;
                                newObj->segment.trans.y_rotation = wizShipObj->segment.trans.y_rotation + 0x8000;
                                newObj->segment.trans.x_rotation = -wizShipObj->segment.trans.x_rotation;
                                newObj->unk78 = 0x3C; 
                                guMtxXFMF(laserMtx, 0.0f, 0.0f, -30.0f, &newObj->segment.x_velocity, &newObj->segment.y_velocity, &newObj->segment.z_velocity);
                                func_80009558(SOUND_LASER_GUN, wizShipObj->segment.trans.x_position, wizShipObj->segment.trans.y_position, wizShipObj->segment.trans.z_position, 4, NULL);
                            }
                        }
                    }
                }
            }
        }
    }
}

void obj_loop_vehicleanim(Object *obj, s32 speed) {
    Object_60_800380F8 *obj60;
    Object *someObj;

    func_8001F460(obj, speed, obj);
    obj60 = (Object_60_800380F8 *) obj->unk60;
    if (obj60 != NULL) {
        if (obj60->unk0 > 0) {
            someObj = obj60->unk0 == 3 ? obj60->unkC : obj60->unk4;
            someObj->segment.trans.y_rotation = 0x4000;
            someObj->segment.unk3A++;
            if (someObj->segment.unk3A == someObj->segment.header->numberOfModelIds) {
                someObj->segment.unk3A = 0;
            }
        }
    }
}

void obj_init_hittester(Object *obj, UNUSED LevelObjectEntry_HitTester *entry) {
    obj->unk4C->unk14 = 0x81;
    obj->unk4C->unk11 = 2;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
}

void obj_loop_hittester(Object *obj, s32 speed) {
    func_8001F460(obj, speed, obj);
}

void obj_init_dynamic_lighting_object(Object *obj, UNUSED LevelObjectEntry_DynamicLightingObject *entry) {
    obj->unk4C->unk14 = 1;
    obj->unk4C->unk11 = 2;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
}

void obj_init_unknown96(Object *obj, UNUSED LevelObjectEntry_Unknown96 *entry) {
    obj->unk4C->unk14 = 0x81;
    obj->unk4C->unk11 = 2;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
}

void obj_init_snowball(Object *obj, UNUSED LevelObjectEntry_Snowball *entry) {
    obj->unk4C->unk14 = 1;
    obj->unk4C->unk11 = 2;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
}

void obj_loop_snowball(Object *obj, s32 speed) {
    Object_Snowball *obj64 = &obj->unk64->snowball;
    if (obj64->unk24 == 0) {
        if (obj64->unk38 != 0) {
            obj64->unk24 = (s16)(obj64->unk38 & 0xFF);
        }
    }
    if (obj64->unk24 != 0) {
        if (obj64->soundMask == 0) {
            func_80009558(obj64->unk24, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 1, &obj64->soundMask);
        } else {
            update_spatial_audio_position(obj64->soundMask, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
        }
    }
    func_8001F460(obj, speed, obj);
}

UNUSED void func_80038330(UNUSED s32 arg0, UNUSED s32 arg1) {
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_char_select.s")

void obj_loop_animcamera(Object *obj, s32 speed) {
    s32 temp_v0;
    s32 phi_v1;
    Object_AnimCamera *obj64;

    temp_v0 = func_8001F460(obj, speed, obj);
    obj->segment.trans.unk6 |= 0x4000;
    obj64 = &obj->unk64->anim_camera;
    if (temp_v0 == 0) {
        if (get_viewport_count() == VIEWPORTS_COUNT_1_PLAYER) {
            phi_v1 = func_800210CC(obj64->unk44);
        } else {
            phi_v1 = 1;
        }
        if (phi_v1) {
            write_to_object_render_stack(obj64->unk30, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 0x8000 - obj->segment.trans.y_rotation, -obj->segment.trans.x_rotation, obj->segment.trans.z_rotation);
        }
    }
}

UNUSED void func_800387C0(UNUSED s32 arg0, UNUSED s32 arg1) {
}

void obj_loop_animcar(Object *obj, s32 speed) {
    Object *someObj;
    s32 temp_v0;
    temp_v0 = obj->unk78;
    someObj = NULL;
    if (temp_v0 != 0) {
        someObj = get_racer_object(temp_v0 - 1);
    }
    obj->unk7C.word = func_8001F460(obj, speed, obj);
    obj->segment.trans.unk6 |= 0x4000;
    if (obj->unk7C.word == 0 && someObj != NULL) {
        Object_AnimCar *someObj64 = &someObj->unk64->anim_car;
        someObj64->unk148 = obj;
    }
}

void obj_init_infopoint(Object *obj, LevelObjectEntry_InfoPoint *entry) {
    if (entry->unk8[1] != 0) {
        obj->unk4C->unk14 = 0x21;
    } else {
        obj->unk4C->unk14 = 0x22;
    }
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0xF;
    obj->unk4C->unk12 = 0;
    obj->unk78 = (entry->unk8[2] << 16) | entry->unk8[0]; // Not sure about the values here.
    obj->unk7C.word = entry->unk8[1];
    obj->segment.trans.y_rotation = entry->unkB << 10; // Not sure about the values here.
}

void obj_loop_infopoint(Object *obj, UNUSED s32 speed) {
    s16 player;
    Object_4C *obj4C;
    Object *playerObj;

    if (obj->unk7C.word == 0) {
        obj->segment.trans.unk6 |= 0x4000;
    } else {
        obj->segment.trans.unk6 &= ~0x4000;
    }

    obj4C = obj->unk4C;
    if (obj4C->unk13 < ((obj->unk78 >> 16) & 0xFF)) {
        playerObj = obj4C->unk0;
        if (playerObj->segment.header->behaviorId == 1) {
            Object_InfoPoint *playerObj64 = &playerObj->unk64->info_point;
            player = playerObj64->unk0;
            if ((player != PLAYER_COMPUTER) && (get_buttons_pressed_from_player(player) & Z_TRIG)) {
                func_800C31EC(obj->unk78 & 0xFF);
            }
        }
    }
}

void obj_init_smoke(UNUSED Object *obj, UNUSED LevelObjectEntry_Smoke *entry) {
}

void obj_loop_smoke(Object *obj, s32 speed) {
    f32 temp_f2 = speed;
    if (osTvType == TV_TYPE_PAL) {
        temp_f2 *= 1.2;
    }
    obj->segment.trans.x_position += obj->segment.x_velocity * temp_f2;
    obj->segment.unk18 += speed * 16;
    obj->segment.trans.y_position += obj->segment.y_velocity * temp_f2;
    obj->segment.trans.z_position += obj->segment.z_velocity * temp_f2;
    if (obj->segment.unk18 >= 256) {
        gParticlePtrList_addObject(obj);
        obj->segment.unk18 = 255;
    }
}

void obj_init_unknown25(UNUSED Object *obj, UNUSED LevelObjectEntry_Unknown25 *entry) {
}

void obj_loop_unknown25(Object *obj, s32 speed) {
    obj->segment.unk18 += speed * 8;
    if (obj->segment.unk18 >= 256) {
        gParticlePtrList_addObject(obj);
        obj->segment.unk18 = 255;
    }
}

void obj_init_wardensmoke(UNUSED Object *obj, UNUSED LevelObjectEntry_WardenSmoke *entry) {
}

void obj_loop_wardensmoke(Object *obj, s32 speed) {
    f32 temp_f2;

    temp_f2 = (f32)speed;
    if (osTvType == TV_TYPE_PAL) {
        temp_f2 *= 1.2;
    }
    obj->segment.unk18 += speed * 4;
    obj->segment.trans.y_position += temp_f2 * 0.25;
    if (obj->segment.unk18 >= 256) {
        gParticlePtrList_addObject(obj);
        obj->segment.unk18 = 255;
    }
}

void obj_init_bombexplosion(Object *obj, LevelObjectEntry_BombExplosion *entry) {
    LevelObjectEntry_BombExplosion *entry2;
    obj->segment.unk18 = 0;
    obj->segment.trans.scale = 0.5f;
    obj->segment.unk3A = get_random_number_from_range(0, obj->segment.header->numberOfModelIds - 1);
    entry2 = entry; // Needed for a match.
    obj->unk78 = 0;
    obj->unk7C.word = 0xFF;
    if (entry->unk8) {
        obj->unk7C.word |= (entry2->unk8 << 8) & 0xFF00;
    }
    obj->unk74 = 1;
}

void obj_loop_bombexplosion(Object *obj, s32 updateRate) {
    s32 temp_t8;

    obj->unk78 += updateRate;
    temp_t8 = (obj->unk7C.word >> 8) & 0xFF;
    if (obj->unk78 > 10 && temp_t8 != 0) {
        obj->unk7C.word ^= (temp_t8 << 8);
        func_8003FC44(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 44, 0, 1.0f, temp_t8 - 1);
    }
    if (obj->unk78 < 20) {
        obj->segment.trans.scale = ((obj->unk78 / 20.0f) * 10.0f) + 0.5f;
        obj->unk7C.word |= 0xFF;
    } else if (obj->unk78 < 0x28) {
        obj->segment.trans.scale = (((obj->unk78 - 20) / 20.0f) * 5.0f) + 10.5f;
        obj->unk7C.word = 0x1EF - (obj->unk78 * 0xC);
    } else {
        gParticlePtrList_addObject(obj);
    }
    
    if (obj->unk74 != 0) {
        if (get_number_of_active_players() < THREE_PLAYERS) {
            func_800AFC3C(obj, 2);
            obj->unk74 = 0;
        }
    }
}



void obj_init_teleport(Object *obj, UNUSED LevelObjectEntry_Teleport *entry) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0xF;
    obj->unk4C->unk12 = 0;
    if (get_settings()->cutsceneFlags & CUTSCENE_LIGHTHOUSE_ROCKET) {
        obj->unk78 = 1;
    }
}

void obj_loop_teleport(Object *obj, UNUSED s32 speed) {
    if (obj->unk78 != 0) {
        LevelObjectEntry_Teleport *level_entry = &obj->segment.unk3C_a.level_entry->teleport;
        if (obj->unk4C->unk13 < 0x78) {
            func_8006F338(level_entry->unk8);
            obj->unk78 = 0;
            play_sound_global(SOUND_WHOOSH2, NULL);
            func_80000FDC(SOUND_VOICE_TT_FUTURE_FUN_LAND, 0, 1.0f);
        }
    }
}

void obj_init_exit(Object *obj, LevelObjectEntry_Exit *entry) {
    f32 phi_f0;
    Object_Exit *obj64;
    phi_f0 = entry->unk10 & 0xFF;
    if (phi_f0 < 5) {
        phi_f0 = 5;
    }
    obj64 = &obj->unk64->exit;
    phi_f0 /= 128;
    obj->segment.trans.scale = phi_f0;
    obj->segment.trans.y_rotation = entry->unk11 << 6 << 4;
    obj64->unk0 = sins_f(obj->segment.trans.y_rotation);
    obj64->unk4 = 0.0f;
    obj64->unk8 = coss_f(obj->segment.trans.y_rotation);
    obj64->unkC = -((obj64->unk0 * obj->segment.trans.x_position) + (obj64->unk8 * obj->segment.trans.z_position));
    obj64->unk10 = entry->unk10;
    obj64->unk14 = entry->bossFlag;
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = entry->unk10;
    obj->unk4C->unk12 = 0;
}

void obj_loop_exit(Object *obj, UNUSED s32 speed) {
    Object *racerObj;
    Object_Racer *racer;
    s32 numberOfRacers;
    Settings *settings;
    f32 xDiff;
    f32 zDiff;
    f32 dist;
    f32 yDiff;
    Object_Exit *obj64;
    s32 enableWarp;
    Object** racerObjects;
    s32 i;
    f32 temp;

    obj64 = &obj->unk64->exit;
    enableWarp = TRUE;
    settings = get_settings();
    if ((obj64->unk14 == 0) && (settings->balloonsPtr[settings->worldId] == 8)) {
        enableWarp = FALSE;
    }
    if ((obj64->unk14 == 1) && (settings->balloonsPtr[settings->worldId] < 8)) {
        enableWarp = FALSE;
    }
    if (enableWarp) {
        if (obj->unk4C->unk13 < obj64->unk10) {
            dist = obj64->unk10;
            racerObjects = get_racer_objects(&numberOfRacers);
            for (i = 0; i < numberOfRacers; i++) {
                racerObj = racerObjects[i];
                racer = &racerObj->unk64->racer;
                if ((racer->playerIndex != -1) && (racer->unk108 == 0)) {
                    xDiff = racerObj->segment.trans.x_position - obj->segment.trans.x_position;
                    yDiff = racerObj->segment.trans.y_position - obj->segment.trans.y_position;
                    zDiff = racerObj->segment.trans.z_position - obj->segment.trans.z_position;
                    if ((sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff)) < dist)) {
                        temp = (obj64->unk0 * racerObj->segment.trans.x_position) + (obj64->unk8 * racerObj->segment.trans.z_position) + obj64->unkC;
                        if (temp < 0.0f) {
                            racer->unk108 = obj;
                            racer->transitionTimer = -120;
                        }
                    }
                }
            }
        }
    }
}


void obj_init_cameracontrol(Object *obj, LevelObjectEntry_CameraControl *entry) {
    obj->unk78 = entry->unk8;
    func_80011390();
}

void obj_loop_cameracontrol(UNUSED Object *obj, UNUSED s32 speed) {
}

void obj_init_setuppoint(Object *obj, LevelObjectEntry_SetupPoint *entry) {
    obj->unk78 = entry->unk8;
    obj->unk7C.word = entry->unk9;
    obj->segment.trans.y_rotation = entry->unkA << 6 << 4; // Not sure about the values here.
}

void obj_loop_setuppoint(UNUSED Object *obj, UNUSED s32 speed) {
}

void obj_init_dino_whale(Object *obj, UNUSED LevelObjectEntry_Dino_Whale *entry) {
    obj->unk4C->unk14 = 1;
    obj->unk4C->unk11 = 3;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
}

void obj_loop_dino_whale(Object *obj, s32 speed) {
    s32 sp2C;

    if (obj->unk78 > 0) {
        obj->unk78 -= speed;
        speed *= 2;
    } else {
        obj->unk78 = 0;
    }
    sp2C = obj->segment.unk18;
    func_8001F460(obj, speed, obj);
    func_800113CC(obj, 0, sp2C, 0xAC, 0xAD);
    if (obj->unk4C->unk13 < 0xFF) {
        if (obj->unk78 == 0) {
            obj->unk78 = 0x3C;
            func_80009558(SOUND_VOICE_BRONTO_ROAR, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
        }
    }
}

void obj_init_parkwarden(Object *obj, UNUSED LevelObjectEntry_Parkwarden *entry) {
    Object_Taj *temp;
    obj->unk4C->unk14 = (u16)1;
    obj->unk4C->unk11 = (u8)0;
    obj->unk4C->unk10 = (u8)0x1E;
    obj->unk4C->unk12 = (u8)0;
    temp = &obj->unk64->taj;
    temp->unkD = 0xFF;
    temp->unk0 = 0.0f;
    temp->unk28 = 0;
    temp->unk2C = 0;
    temp->unk34 = 0;
    temp->unk36 = 0;
    gTajSoundMask = 0;
    D_8011D4E2 = SOUND_VOICE_TAJ_HELLO;
}

void func_80039320(s16 voiceClip) {
    //Set to SOUND_VOICE_TAJ_CHALLENGE_RACE in func_800CC7C
    D_8011D4E2 = voiceClip;
}

#ifdef NON_EQUIVALENT
s32 func_80004B40(s8, s8/*, s8, s32, s8*/);             /* extern */
s32 func_800090C0(f32, f32, s16);                   /* extern */
void func_80061C0C(Object*);                         /* extern */
void func_80030DE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
Object *func_8002342C(f32 x, f32 z);
void obj_loop_parkwarden(Object *obj, s32 arg1) {
    f32 arg1_f32;
    f32 spA8;
    f32 spA0;
    f32 sp9C;
    f32 sp98_yPos;
    struct TempStruct8 **sp94;
    s32 var_a2;
    s32 sp7C;
    s32 numRacers;
    s8 sp6B;
    LevelHeader *levelHeader;
    f32 sp5C;
    s32 sp54;
    s32 sp3C;
    Object *racerObj;
    Object *temp_v0_12;
    Object **racerObjs;
    ObjectSegment *temp_v0_22;
    Object_64 *racer64;
    Object_Taj *taj;
    f32 xPosDiff;
    f32 yPosDiff;
    f32 zPosDiff;
    f32 var_f2;
    s16 temp_a1_3;
    s32 temp_t0;
    s32 temp_t5;
    s32 var_a2_2;
    s32 arctan;
    s8 temp_v0_24;
    u32 buttonsPressed;
    u8 temp_v0_13;

    sp6B = 0;
    arg1_f32 = arg1;
    sp98_yPos = obj->segment.trans.y_position;
    if (osTvType == TV_TYPE_PAL) {
        arg1_f32 *= 1.2;
    }
    taj = (Object_Taj *)obj->unk64;
    levelHeader = get_current_level_header();
    obj->unk74 = 0;
    if (obj->segment.unk18 == 0 && taj->unk4 > 1.0) {
        taj->unk4 = 0.0f;
    }
    sp9C = 0.0f;
    obj->segment.x_velocity = 0.0f;
    obj->segment.z_velocity = 0.0f;
    racerObj = get_racer_object(PLAYER_ONE);
    if (racerObj != NULL) {
        racer64 = racerObj->unk64;
        spA8 = (racerObj->segment.trans.x_position - (racer64->racer.ox1 * 50.0f)) - obj->segment.trans.x_position;
        spA0 = (racerObj->segment.trans.z_position - (racer64->racer.oz1 * 50.0f)) - obj->segment.trans.z_position;
        sp9C = sqrtf((spA8 * spA8) + (spA0 * spA0));
    }
    buttonsPressed = get_buttons_pressed_from_player(PLAYER_ONE);
    var_a2 = FALSE;
    if (
        (obj->unk78 == NULL) && 
        (sp9C < 300.0) && 
        (
            ((obj->unk4C->unk14 & 8) && (racerObj == obj->unk4C->unk0)) ||
            (buttonsPressed & Z_TRIG)
        )
    ) {
        if (buttonsPressed & Z_TRIG) {
            play_char_horn_sound(racerObj, &racer64->racer);
        }
        arctan = arctan2_f(racerObj->segment.trans.x_position - obj->segment.trans.x_position, racerObj->segment.trans.z_position - obj->segment.trans.z_position) - (racerObj->segment.trans.y_rotation & 0xFFFF);
        if (arctan > 0x8000) {
            arctan = -0xFFFF;
        }
        if (arctan < -0x8000) {
            arctan = 0xFFFF;
        }
        if (arctan > -0x2000 && arctan < 0x2000) {
            var_a2 = TRUE;
        }
    }
    obj->unk4C->unk14 = 1;
    if ((func_80052188() || var_a2) && (obj->unk78 == NULL || obj->unk78 == 0x1F)) {
        func_800012E8();
        set_music_player_voice_limit(24);
        play_music(SEQUENCE_ENTRANCED);
        if (racerObj != NULL) {
            func_80006AC8(racerObj);
            racer64->racer.unk118 = 0;
        }
        func_80008140();
        if (((arctan2_f(racerObj->segment.trans.x_position - obj->segment.trans.x_position, racerObj->segment.trans.z_position - obj->segment.trans.z_position) - (racerObj->segment.trans.y_rotation & 0xFFFF)) > 0x8000) && var_a2) {
            obj->unk78 = 1;
        } else {
            obj->unk78 = 10;
            sp6B = 1;
        }
        func_80030750(0, &taj->unk20, &taj->unk22, &taj->unk11, &taj->unk12, &taj->unk13);
        func_80030DE0(0, 0xFF, 0, 0x78, 0x3C0, 0x44C, 0xF0);
        taj->unk4 = 0.0f;
    }
    switch (obj->unk78) {                            /* switch 3; irregular */
        case 0:                                         /* switch 3 */
        case 20:                                        /* switch 3 */
        case 21:                                        /* switch 3 */
        case 30:                                        /* switch 3 */
            break;
        default:                                        /* switch 3 */
            func_8005A3B0();
            func_800AB194(3);
            break;
    }
    if ((obj->unk78 == 3) || (obj->unk78 == 4) || (obj->unk78 == 5) || (obj->unk78 == 6)) {
        sp7C = func_8009CFEC(0);
    } else {
        func_8009CF68(0);
        sp7C = 0;
    }
    switch (obj->unk78) {                            /* switch 1 */
        case 1:                                         /* switch 1 */
        case 2:                                         /* switch 1 */
        case 3:                                         /* switch 1 */
        case 4:                                         /* switch 1 */
        case 7:                                         /* switch 1 */
        case 10:                                        /* switch 1 */
        case 11:                                        /* switch 1 */
        case 15:                                        /* switch 1 */
        case 20:                                        /* switch 1 */
        case 21:                                        /* switch 1 */
            func_8006F388(1);
            break;
    }
    if (obj->unk78 != 0 && sp7C != 0 && obj->unk78 < 4) {
        obj->unk78 = 4;
    }
    switch (obj->unk78 - 1) {                           /* switch 2 */
    case 0:                                         /* switch 2 */
        obj->segment.unk3B = 0;
        taj->unkD = 0xFF;
        if (sp9C < 100.0) {
            func_8005A3C0();
        }
        if (sp9C > 10.0) {
            arctan = (arctan2_f(spA8 / sp9C, spA0 / sp9C) - (obj->segment.trans.y_rotation & 0xFFFF)) + 0x8000;
            if (arctan > 0x8000) {
                arctan -= 0xFFFF;
            }
            if (arctan < -0x8000) {
                arctan += 0xFFFF;
            }
            if (arctan > 0 && arctan < 16) {
                arctan = 16;
            }
            obj->segment.trans.y_rotation += (arctan >> 4);
            var_f2 = -2.0f;
            if (arctan > 0x800 || arctan < -0x800) {
                var_f2 = -0.5f;
            }
            taj->unk14 += (var_f2 - taj->unk14) * 0.125;
            obj->segment.x_velocity = sins_f(obj->segment.trans.y_rotation) * taj->unk14;
            obj->segment.z_velocity = coss_f(obj->segment.trans.y_rotation) * taj->unk14;
            taj->unk4 -= taj->unk14 * 2 * arg1_f32;
        } else {
            obj->unk78 = 2;
        }
        func_80011570(obj, obj->segment.x_velocity * arg1_f32, obj->segment.y_velocity * arg1_f32, obj->segment.z_velocity * arg1_f32);
        break;
    case 1:                                         /* switch 2 */
        func_8005A3C0();
        obj->segment.unk3B = 0;
        taj->unk4 += arg1_f32 * 2.0;
        arctan = (racerObj->segment.trans.y_rotation - (obj->segment.trans.y_rotation & 0xFFFF)) + 0x8000;
        if (arctan > 0x8000) {
            arctan -= 0xFFFF;
        }
        if (arctan < -0x8000) {
            arctan += 0xFFFF;
        }
        if (arctan > 0 && arctan < 16) {
            arctan = 16;
        }
        obj->segment.trans.y_rotation += arctan >> 3;
        if (arctan < 0x400 && arctan > -0x400 && sp9C < 2.0) {
            obj->unk78 = 3;
            taj->unk4 = 0;
            play_taj_voice_clip(D_8011D4E2, 1);
            D_8011D4E2 = SOUND_VOICE_TAJ_HELLO;
        }
        obj->segment.x_velocity = spA8 * 0.125;
        obj->segment.y_velocity = 0;
        obj->segment.z_velocity = spA0 * 0.125;
        func_80011570(obj, obj->segment.x_velocity * arg1_f32, obj->segment.y_velocity * arg1_f32, obj->segment.z_velocity * arg1_f32);
        break;
    case 2:                                         /* switch 2 */
        obj->segment.unk3B = 1;
        taj->unk14 = 0.0f;   
        taj->unk4 += arg1_f32 * 1.0;
        if (taj->unk4 > 77.0) {
            taj->unk4 = 77.0;
            taj->unk18 = -1.0f;
            obj->unk78 = 4;
        }
        temp_a1_3 = obj->segment.trans.y_rotation;
        arctan = (racerObj->segment.trans.y_rotation - (temp_a1_3 & 0xFFFF)) + 0x8000;
        if (arctan > 0x800) {
            arctan -= 0xFFFF;
        }
        if (arctan < -0x8000) {
            arctan += 0xFFFF;
        }
        if (arctan > 0 && arctan < 16) {
            arctan = 16;
        }
        obj->segment.trans.y_rotation = temp_a1_3 + (arctan >> 4);
        func_8005A3C0();
        break;
    case 3:                                         /* switch 2 */
        obj->segment.unk3B = 4;
        taj->unk4 += arg1_f32 * 1.0;        
        func_8005A3C0();
        if (sp7C == 3 || sp7C == 4) {
            obj->unk78 = (sp7C == 4) ? 8 : 7;
            taj->unk4 = 0.1f;
            obj->segment.unk3B = 2;
            taj->unk1C = 0;
            play_taj_voice_clip(SOUND_VOICE_TAJ_BYE, 1);
            func_80030DE0(0, taj->unk11, taj->unk12, taj->unk13, taj->unk20, taj->unk22, 0xB4);
            set_music_player_voice_limit(levelHeader->voiceLimit);
            play_music(levelHeader->music);
            func_80001074(levelHeader->instruments);
            func_80008168();
        }
        if (sp7C & 0x80) {
            D_8011D4E0 = sp7C & 0x7F;
            if (racer64->racer.unk1D6 != D_8011D4E0) {
                obj->unk78 = 5;
                taj->unk4 = 0;
                // Voice clips: Abrakadabra, Alakazam, Alakazoom?
                play_taj_voice_clip((racer64->racer.unk1D6 + 0x235), 1);
            } else {
                set_menu_id_if_option_equal(0x62, 2);
            }
        }
        if (sp7C & 0x40) {
            D_8011D4E0 = sp7C & 0xF;
            if (racer64->racer.unk1D6 != D_8011D4E0) {
                D_8011D4E0 |= 0x80;
                obj->unk78 = 5;
                taj->unk4 = 0.0f;
                // Voice clips: Abrakadabra, Alakazam, Alakazoom?
                play_taj_voice_clip((racer64->racer.unk1D6 + 0x235), 1);
            } else {
                obj->unk78 = 0xF;
                sp6B = 1;
                func_800C01D8(&D_800DC978);
                play_taj_voice_clip(SOUND_WHOOSH4, 1);
                taj->unk4 = 0.0f;
            }
        }
        break;
    case 4:                                         /* switch 2 */
        obj->segment.unk3B = 5;
        func_8005A3C0();
        taj->unk4 += arg1_f32 * 2.0;
        if (taj->unk4 > 25.0) {
            obj->unk74 = 11;
        }
        if (taj->unk4 > 50.0) {
            obj->unk74 = 0;
        }
        if (taj->unk4 > 60.0) {
            taj->unk4 = 60.0f;
            if (racer64->racer.transparency > (arg1 * 16)) {
                racer64->racer.transparency -= (arg1 * 16) ;
            } else {
                racer64->racer.transparency = 0;
                func_8000E1EC(racerObj, D_8011D4E0 & 0xF);
                obj->unk78 = 6;
                play_sound_global(SOUND_CYMBAL, NULL);
                func_800C01D8(&D_800DC970);
            }
        }
        break;
    case 5:                                         /* switch 2 */
        func_8005A3C0();
        if (racerObj != NULL) {
            var_a2_2 = arg1;
            if (taj->unk4 != 0.0f) {
                taj->unk4 += 8.0;
            }
            if (var_a2_2 > 4) {
                var_a2_2 = 4;
            }
            temp_t0 = var_a2_2 * 32;
            if (racer64->racer.transparency < (255 - temp_t0)) {
                racer64->racer.transparency += temp_t0;
            } else {
                if (taj->unk4 == 0.0) {
                    if (D_8011D4E0 & 0x80) {
                        sp6B = 1;
                        func_800C01D8(&D_800DC978);
                        obj->unk78 = 0xF;
                        play_sound_global(SOUND_WHOOSH4, NULL);
                        taj->unk4 = 0.0f;
                    } else {
                        obj->unk78 = 4;
                        set_menu_id_if_option_equal(0x62, 2);
                    }
                }
            }
        }
        break;
    case 6:                                         /* switch 2 */
    case 7:                                         /* switch 2 */
        if (taj->unk4 != 0.0) {
            taj->unk4 += arg1_f32 * 0.5;
        }
        if (taj->unk4 == 0) {
            sp6B = 1;
            if (obj->unk78 == 8) {
                func_80022CFC(
                    obj->segment.unk2C.half.lower, 
                    obj->segment.trans.x_position - (racer64->racer.ox1 * 50.0f), 
                    obj->segment.trans.y_position, 
                    obj->segment.trans.z_position - (racer64->racer.oz1 * 50.0f)
                );
            }
            obj->unk78 = 0x14;
            play_sound_global(SOUND_WHOOSH4, NULL);
            racer64->racer.unk118 = func_80004B40(racer64->racer.characterId, racer64->racer.unk1D6);
        }
        break;
    case 9:                                         /* switch 2 */
        obj->segment.unk3B = 3;
        taj->unkD = 0xFF;
        taj->unk14 = 0.0f;
        taj->unk4 +=  arg1_f32 * 2.0;
        if (taj->unk4 > 79.0f) {
            taj->unk4 = 79.0f;
        }
        temp_t0 = arg1 * 8;
        if (taj->unk4 < 20.0f) {
            temp_t0 = 0;
        }
        if (obj->segment.unk38.half.lower > temp_t0) {
            obj->segment.unk38.half.lower -= temp_t0;
        } else {
            sp6B = 1;
            play_sound_global(SOUND_WHOOSH4, NULL);
            obj->segment.unk38.half.lower = 0;
            obj->unk78 = 0xB;
            obj->segment.trans.x_position = racerObj->segment.trans.x_position - (racer64->racer.ox1 * 150.0f);
            obj->segment.trans.z_position = racerObj->segment.trans.z_position - (racer64->racer.oz1 * 150.0f);
            obj->segment.unk2C.half.lower = get_level_segment_index_from_position(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
            obj->segment.trans.y_rotation = racerObj->segment.trans.y_rotation + 0x8000;
        }
        break;
    case 10:                                        /* switch 2 */
        obj->segment.unk3B = 3;
        taj->unk4 -= arg1_f32 * 2.0;
        if (taj->unk4 < 0.0f) {
            taj->unk4 = 0.0f;
        }
        temp_t0 = arg1 * 4;
        if (obj->segment.unk38.half.lower < (255 - temp_t0)) {
            obj->segment.unk38.half.lower += temp_t0;
        } else {
            obj->segment.unk38.half.lower = 0xFF;
            obj->unk78 = 1;
        }
        break;
    case 14:                                        /* switch 2 */
        obj->segment.unk3B = 3;
        taj->unkD = 0xFF;
        taj->unk14 = 0.0f;
        taj->unk4 -= arg1_f32 * 2.0;
        if (taj->unk4 > 79.0f) {
            taj->unk4 = 79.0f;
        }
        temp_t0 = arg1 * 8;
        if (taj->unk4 < 20.0f) {
            temp_t0 = 0;
        }
        if (obj->segment.unk38.half.lower > temp_t0) {
            obj->segment.unk38.half.lower -= temp_t0;
        } else {
            racer64->racer.unk118 = func_80004B40(racer64->racer.characterId, racer64->racer.unk1D6);
            func_80030DE0(0, taj->unk11, taj->unk12, taj->unk13, taj->unk20, taj->unk22, 0xB4);
            set_music_player_voice_limit(levelHeader->voiceLimit);
            play_music(levelHeader->music);
            func_80001074(levelHeader->instruments);
            func_800228EC((s32) racer64->racer.unk1D6);
            temp_v0_12 = func_8002342C(obj->segment.trans.x_position, obj->segment.trans.z_position);
            if (temp_v0_12 != NULL) {
                obj->segment.trans.x_position = temp_v0_12->segment.trans.x_position;
                obj->segment.trans.z_position = temp_v0_12->segment.trans.z_position;
                obj->segment.unk2C.half.lower = temp_v0_12->segment.unk2C.half.lower;
                obj->segment.trans.y_rotation = racerObj->segment.trans.y_rotation + 0x8000;
            }
            obj->unk78 = 0x1E;
        }
        break;
    case 19:                                        /* switch 2 */
        obj->segment.unk3B = 3;
        taj->unkD = 0xFF;
        taj->unk14 = 0.0f;
        taj->unk4 += arg1_f32 * 2.0;
        if (taj->unk4 > 79.0f) {
            taj->unk4 = 79.0f;
        }
        temp_t0 = arg1 * 8;
        if (taj->unk4 < 20.0f) {
            temp_t0 = 0;
        }
        temp_v0_13 = obj->segment.unk38.half.lower;
        if (obj->segment.unk38.half.lower > temp_t0) {
            obj->segment.unk38.half.lower -= temp_t0;
        } else {
            obj->segment.unk38.half.lower = 0;
            obj->unk78 = 0x15;
            temp_v0_12 = func_8002342C(obj->segment.trans.x_position, obj->segment.trans.z_position);
            if (temp_v0_12 != NULL) {
                obj->segment.trans.x_position = temp_v0_12->segment.trans.x_position;
                obj->segment.trans.z_position = temp_v0_12->segment.trans.z_position;
                obj->segment.unk2C.half.lower = temp_v0_12->segment.unk2C.half.lower;
                obj->segment.trans.y_rotation = racerObj->segment.trans.y_rotation + 0x8000;
            }
        }
        break;
    case 20:                                        /* switch 2 */
        obj->segment.unk3B = 3;
        taj->unk4 -= arg1_f32 * 2.0;
        if (taj->unk4 < 0.0f) {
            taj->unk4 = 0.0f;
        }
        temp_t0 = arg1 * 4;
        if (obj->segment.unk38.half.lower < (0xFF - temp_t0)) {
            obj->segment.unk38.half.lower += temp_t0;
        } else {
            obj->segment.unk38.half.lower = 0xFF;
            obj->unk78 = NULL;
        }
        break;
    case 29:                                        /* switch 2 */
        obj->unk4C->unk14 = 0;
        obj->segment.unk3B = 6;
        obj->segment.unk38.half.lower = 0xFF;
        taj->unk4 += arg1_f32 * 1.0;
        break;
    default:                                        /* switch 2 */
        obj->segment.unk3B = 0;
        taj->unk14 = 0.0f;
        if (taj->unkD == 0xFF) {
            taj->unkD = func_8001C524(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 0);
            if (taj->unkD != 0xFF) {
                taj->unkE = func_8001CC48(taj->unkD, -1, 0);
                taj->unkF = func_8001CC48(taj->unkE, taj->unkD, 0);
                taj->unk10 = func_8001CC48(taj->unkF, taj->unkE, 0);
                taj->unkC = taj->unkD;
            }
        } else {
            if ((sp9C < 55.0f) && (taj->unk1C == 0) && (racerObj != NULL)) {
                taj->unk1C = 240;
                taj->unk1E = (s16) (arctan2_f(spA8 / sp9C, spA0 / sp9C) + 0x4000);
            }
            if (taj->unk1C > 0) {
                taj->unk1C -= arg1;
            } else {
                taj->unk1C = 0;
            }
            if (taj->unk1C < 120) {
                taj->unk4 += func_8001C6C4((Object_64*)taj, obj, arg1_f32, 1.0f, 0);
            } else {
                arctan = taj->unk1E - (obj->segment.trans.y_rotation & 0xFFFF);
                if (arctan > 0x8000) {
                    arctan -= 0xFFFF;
                }
                if (arctan < -0x8000) {
                    arctan += 0xFFFF;
                }
                obj->segment.trans.y_rotation += ((arctan * arg1) >> 4);
                spA8 = sins_f(obj->segment.trans.y_rotation + 0x8000);
                func_80011570(
                    obj, 
                    (arg1_f32 * spA8) * 1.1, 
                    0.0f, 
                    (arg1_f32 * coss_f(obj->segment.trans.y_rotation + 0x8000)) * 1.1
                );
                taj->unk4 += arg1 * 2.2;
            }
        }
        racerObjs = get_racer_objects(&numRacers);
        if (numRacers != NULL) {
            xPosDiff = racerObjs[PLAYER_ONE]->segment.trans.x_position - obj->segment.trans.x_position;
            yPosDiff = racerObjs[PLAYER_ONE]->segment.trans.y_position - obj->segment.trans.y_position;
            zPosDiff = racerObjs[PLAYER_ONE]->segment.trans.z_position - obj->segment.trans.z_position;
            sp5C = sqrtf((xPosDiff * xPosDiff) + (yPosDiff * yPosDiff) + (zPosDiff * zPosDiff));
            if (sp5C < 1000.0f) {
                sp5C = 1000.0f - sp5C;
                temp_v0_22 = func_80069D7C();
                sp54 = func_800090C0(obj->segment.trans.x_position - temp_v0_22->trans.x_position, obj->segment.trans.z_position - temp_v0_22->trans.z_position, temp_v0_22->trans.y_rotation);
                sp3C = (127.0f * sp5C) / 1000.0f;
                arg1_f32 = sp3C;
                func_80001268(0xA, sp3C);
                func_80001268(0xB, sp3C);
                func_80001268(0xF, sp3C);
                musicSetChlPan(0xA, sp3C);
                musicSetChlPan(0xB, sp3C);
                musicSetChlPan(0xF, sp3C);
                func_80001170(0xA);
                func_80001170(0xB);
                func_80001170(0xF);
                func_80001268(3, 0x7F - sp3C);
            } else {
                func_80001114(0xA);
                func_80001114(0xB);
                func_80001114(0xF);
            }
        }
        switch (taj->unk36) {                        /* switch 4; irregular */
        case 0:                                     /* switch 4 */
            temp_t5 = arg1 << 7;
            if (taj->unk34 > temp_t5) {
                taj->unk34 -= temp_t5;
                func_80001170(14);
                func_80001268(14, taj->unk34 >> 8);
                taj->unk30 = 0;
            } else {
                taj->unk34 = 0;
                func_80001114(14);
                if (taj->unk30 == 0) {
                    taj->unk30 = get_random_number_from_range(600, 900);
                    taj->unk2C = 0;
                }
            }
            if ((taj->unk30 != 0) && ((musicGetChanMask() & ~0x4000) == 0xB)) {
                taj->unk2C += arg1;
                if (taj->unk30 < taj->unk2C) {
                    taj->unk36 = 1;
                    taj->unk2C = get_random_number_from_range(600, 900);
                }
            } else {
                taj->unk2C = 0;
                taj->unk30 = 0;
            }
            break;
        case 1:                                     /* switch 4 */
            if ((musicGetChanMask() & ~0x4000) == 0xB) {
                taj->unk34 += (arg1 << 7);
                if (taj->unk34 > 0x7F00) {
                    taj->unk34 = 0x7F00;
                }
                taj->unk2C -= arg1;
                if (taj->unk2C < 0) {
                    taj->unk36 = 0;
                }
                func_80001170(0xE);
                func_80001268(0xE, taj->unk34 >> 8);
            } else {
                taj->unk36 = 0;
                taj->unk2C = 0;
                taj->unk30 = 0;
            }
            break;
        }
        taj->unk28 = musicGetChanMask() & 0xBFFF;
        break;
    }
    obj->segment.trans.y_position = sp98_yPos;
    temp_v0_24 = func_8002B0F4(obj->segment.unk2C.half.lower, obj->segment.trans.x_position, obj->segment.trans.z_position, &sp94);
    //Loop backwards through temp_v0_24
    for (; temp_v0_24 > 0; temp_v0_24--) {
        if ((sp94[temp_v0_24]->unk10 != 11) && (sp94[temp_v0_24]->unk10 != 14) && (sp94[temp_v0_24]->unk8 > 0.0)) {
            obj->segment.trans.y_position = sp94[temp_v0_24]->unk0;
        }
    }
    obj->segment.trans.x_rotation = 0;
    obj->segment.trans.z_rotation = 0;
    if (obj->unk78 != NULL) {
        D_8011D4D0 = obj->segment.trans.y_position;
    }
    if (sp6B != 0) {
        func_8003FC44(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 0xC, 0, 1.0f, 0);
    }
    obj->segment.unk18 = taj->unk4;
    func_80061C0C(obj);
    func_800AFC3C(obj, arg1);
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_parkwarden.s")
#endif

/**
 * If Taj is currently talking, clear the audio associated with gTajSoundMask,
 * then play the new sound ID in its place.
 */
void play_taj_voice_clip(u16 soundID, s32 interrupt) {
    if (gTajSoundMask && interrupt & 1) {
        func_8000488C(gTajSoundMask);
        gTajSoundMask = 0;
    }
    if (!gTajSoundMask) {
        play_sound_global(soundID, &gTajSoundMask);
    }
}

void obj_loop_gbparkwarden(UNUSED Object *obj, UNUSED s32 speed) {
}

f32 func_8003ACAC(void) {
    return D_8011D4D0;
}

void obj_init_checkpoint(Object *obj, LevelObjectEntry_Checkpoint *entry, UNUSED s32 arg2) {
    f32 phi_f0 = (s32)(entry->unk8 & 0xFF);
    if (phi_f0 < 5.0f) {
        phi_f0 = 5.0f;
    }
    phi_f0 /= 64;
    obj->segment.trans.scale = phi_f0;
    obj->segment.trans.y_rotation = entry->unkA << 6 << 4; // Not sure about the values here.
    func_80011390();
}

void obj_loop_checkpoint(UNUSED Object *obj, UNUSED s32 speed) {
}

void obj_init_modechange(Object *obj, LevelObjectEntry_ModeChange *entry) {
    f32 phi_f0;
    Object_ModeChange *obj64;
    phi_f0 = entry->unk8 & 0xFF;
    if (phi_f0 < 5) {
        phi_f0 = 5;
    }
    obj64 = &obj->unk64->mode_change;
    phi_f0 /= 128;
    obj->segment.trans.scale = phi_f0;
    obj->segment.trans.y_rotation = entry->unk9 << 6 << 4;
    obj64->unk0 = sins_f(obj->segment.trans.y_rotation);
    obj64->unk4 = 0.0f;
    obj64->unk8 = coss_f(obj->segment.trans.y_rotation);
    obj64->unkC = -((obj64->unk0 * obj->segment.trans.x_position) + (obj64->unk8 * obj->segment.trans.z_position));
    obj64->unk10 = entry->unk8;
    obj64->unk14 = entry->unkA;
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = entry->unk8;
    obj->unk4C->unk12 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_modechange.s")

void obj_init_bonus(Object *obj, LevelObjectEntry_Bonus *entry) {
    f32 phi_f0;
    Object_Bonus *obj64;
    phi_f0 = entry->unk8 & 0xFF;
    if (phi_f0 < 5) {
        phi_f0 = 5;
    }
    obj64 = &obj->unk64->bonus;
    phi_f0 /= 128;
    obj->segment.trans.scale = phi_f0;
    obj->segment.trans.y_rotation = entry->unk9 << 6 << 4;
    obj64->unk0 = sins_f(obj->segment.trans.y_rotation);
    obj64->unk4 = 0.0f;
    obj64->unk8 = coss_f(obj->segment.trans.y_rotation);
    obj64->unkC = -((obj64->unk0 * obj->segment.trans.x_position) + (obj64->unk8 * obj->segment.trans.z_position));
    obj64->unk10 = entry->unk8;
    obj64->unk14 = entry->unkA;
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = entry->unk8;
    obj->unk4C->unk12 = 0;
}

void obj_loop_bonus(Object *obj, UNUSED s32 speed) {
    Object *racerObj;
    Object_Racer *racer;
    s32 numberOfRacers;
    f32 xDiff;
    f32 yDiff;
    f32 halfDist;
    f32 dist;
    f32 zDiff;
    Object_Bonus *obj64;
    Object **racerObjects;
    s32 i;

    obj64 = &obj->unk64->bonus;
    if (obj->unk4C->unk13 < obj64->unk10) {
        dist = obj64->unk10;
        halfDist = dist * 0.5;
        racerObjects = get_racer_objects(&numberOfRacers);
        for (i = 0; i < numberOfRacers; i++) {
            racerObj = racerObjects[i];
            racer = &racerObj->unk64->racer;
            yDiff = racerObj->segment.trans.y_position - obj->segment.trans.y_position;
            if ((yDiff < halfDist) && (-halfDist < yDiff)) {
                xDiff = racerObj->segment.trans.x_position - obj->segment.trans.x_position;
                zDiff = racerObj->segment.trans.z_position - obj->segment.trans.z_position;
                if ((sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff)) < dist)) {
                    f32 temp = (obj64->unk0 * racerObj->segment.trans.x_position) + (obj64->unk8 * racerObj->segment.trans.z_position) + obj64->unkC;
                    if (temp < 0.0f) {
                        if ((s32) racer->bananas < 10) {
                            racer->bananas = 10;
                            func_80009558(SOUND_SELECT, racerObj->segment.trans.x_position, racerObj->segment.trans.y_position, racerObj->segment.trans.z_position, 4, NULL);
                            play_sound_spatial(racer->characterId + SOUND_UNK_7B, racerObj->segment.trans.x_position, racerObj->segment.trans.y_position, racerObj->segment.trans.z_position, NULL);
                        }
                    }
                }
            }
        }
    }
}
void obj_init_goldenballoon(Object *obj, LevelObjectEntry_GoldenBalloon *entry) {
    Object_GoldenBalloon *obj64;
    f32 scalef;

    if (entry->unk8 == -1) {
        entry->unk8 = func_8000CC20(obj);
    } else {
        func_8000CBF0(obj, entry->unk8);
    }
    if (entry->unk8 == -1) {
        rmonPrintf("Illegal door no!!!\n"); // Did the devs just copy-paste the door init function?
    }
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 4;
    obj->unk4C->unk10 = 20;
    obj->unk4C->unk12 = 0;
    scalef = entry->scale & 0xFF;
    if (scalef < 10.0f) {
        scalef = 10.0f;
    }
    scalef /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * scalef;
    obj64 = &obj->unk64->golden_balloon;
    obj64->unkD = 255;
    obj64->unk0 = 0.0f;
    obj->unk78 = 0;
    if (entry->unkA != 0) {
        if ((get_settings()->tajFlags & (1 << (entry->unkA + 2))) != 0) {
            obj->unk78 = 0;
        } else {
            obj->unk78 = 1;
        }
    }
}

void obj_loop_goldenballoon(Object *obj, s32 speed) {
    LevelObjectEntry *levelEntry;
    Object_4C *obj4C;
    Object_Racer *racer;
    Object_GoldenBalloon *obj64;
    Settings *settings;
    s32 flag;
    s32 doubleSpeed;
    Object *racerObj;
    f32 sp2C;
    f32 speedf;
    s32 isPirated;

    sp2C = speed;
    if (osTvType == TV_TYPE_PAL) {
        sp2C *= 1.2;
    }
    isPirated = FALSE;
    // AntiPiracy check. Seems to set a flag that prevents collecting balloons.
    if (IO_READ(0x284) != 0x240B17D7) {
        isPirated = TRUE;
    }
    speedf = sp2C;
    settings = get_settings();
    levelEntry = obj->segment.unk3C_a.level_entry;
    flag = 0x10000 << levelEntry->goldenBalloon.unk8;
    if (settings->courseFlagsPtr[settings->courseId] & flag) {
        if (obj->unk7C.word > 0) {
            obj->unk74 = 2;
            func_800AFC3C(obj, speed);
            obj->unk7C.word -= speed;
        } else {
            gParticlePtrList_addObject(obj);
        }
    } else {
        obj->segment.trans.unk6 |= 0x4000;
        if (obj->unk78 == 0) {
            obj->segment.trans.unk6 &= 0xBFFF;
            doubleSpeed = speed * 2;
            if (obj->segment.unk38.half.lower < (255 - doubleSpeed)) {
                obj->segment.unk38.half.lower += doubleSpeed;
            } else {
                obj->segment.unk38.half.lower = 255;
            }
            obj4C = obj->unk4C;
            if ((obj4C->unk13 < 45) && (isPirated == FALSE)) {
                racerObj = obj4C->unk0;
                if ((racerObj && (racerObj->segment.header->behaviorId == 1))) {
                    racer = &racerObj->unk64->racer;
                    if (racer->playerIndex == PLAYER_ONE) {
                        settings->balloonsPtr[settings->worldId]++;
                        if(isPirated == 1) { }
                        if (settings->worldId != 0) {
                            settings->balloonsPtr[0]++;
                        }
                        settings->courseFlagsPtr[settings->courseId] |= flag;
                        if (&obj->segment){ } // Fakematch
                        play_sound_spatial(SOUND_COLLECT_BALLOON, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, NULL);
                        obj->unk7C.word = 16;
                        obj->unk74 = 2;
                        obj->segment.trans.unk6 |= 0x4000;
                        func_800AFC3C(obj, speed);
                    }
                }
            }
            obj64 = &obj->unk64->golden_balloon;
            obj->segment.unk3B = 0;
            obj64->unk14 = 0.0f;
            speedf = (obj->segment.unk38.half.lower < 255) ? 0 : 1;
            if (obj64->unkD == 255) {
                obj64->unkD = func_8001C524(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 0);
                if (obj64->unkD != 255) {
                    obj64->unkE = func_8001CC48(obj64->unkD, -1, 0);
                    obj64->unkF = func_8001CC48(obj64->unkE, obj64->unkD, 0);
                    obj64->unk10 = func_8001CC48(obj64->unkF, obj64->unkE, 0);
                    obj64->unkC = obj64->unkD;
                }
            } else {
                func_8001C6C4(obj64, obj, sp2C, speedf, 0);
            }
        }
    }
}

void obj_init_door(Object *obj, LevelObjectEntry_Door *entry) {
    Object_Door *obj64;
    f32 phi_f0;

    obj64 = &obj->unk64->door;
    if (entry->unkC == -1) {
        entry->unkC = func_8000CC20(obj);
    } else {
        func_8000CBF0(obj, entry->unkC);
    }
    obj64->unkE = entry->unkC;
    obj64->unkF = entry->unkE;
    obj64->unk11 = entry->numBalloonsToOpen;
    obj64->unk10 = entry->numBalloonsToOpen;
    obj64->unk12 = entry->distanceToOpen;
    if (obj64->unkE == -1) {
        rmonPrintf("Illegal door no!!!\n");
    }
    obj->segment.unk3A = entry->modelIndex;
    obj->segment.trans.y_rotation = entry->closedRotation << 6 << 4;
    obj64->unk0 = obj->segment.trans.y_position;
    obj64->unk8 = 0;
    obj->unk78 = obj->segment.trans.y_rotation;
    obj->unk7C.word = (s32) ((entry->openRotation & 0x3F) << 10);
    phi_f0 = entry->scale & 0xFF;
    if (phi_f0 < 10.0f) {
        phi_f0 = 10.0f;
    }
    phi_f0 /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * phi_f0;
    obj64->unk13 = (u8) entry->unkF;
    obj64->unk14 = (s8) entry->unk11;
    obj->unk4C->unk14 = 0x21;
    obj->unk4C->unk11 = 2;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
    if (obj->segment.unk3A >= obj->segment.header->numberOfModelIds) {
        obj->segment.unk3A = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_door.s")

void obj_init_ttdoor(Object *obj, LevelObjectEntry_TTDoor *entry) {
    Object_TTDoor *obj64;
    f32 phi_f0;

    obj->segment.unk3A = 0;
    obj64 = &obj->unk64->tt_door;
    obj->segment.trans.y_rotation = entry->unk8 << 6 << 4;
    obj64->unkF = entry->unkE;
    obj64->unk13 = entry->unkB;
    obj64->unk0 = obj->segment.trans.y_position;
    obj64->unk8 = 0;
    obj64->unk12 = entry->unkA;
    obj->unk78 = obj->segment.trans.y_rotation;
    obj->unk7C.word = (entry->unk9 & 0x3F) << 0xA;
    phi_f0 = entry->unkC & 0xFF;
    if (phi_f0 < 10) {
        phi_f0 = 10;
    }
    phi_f0 /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * phi_f0;
    obj->unk4C->unk14 = 0x21;
    obj->unk4C->unk11 = 2;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
    if (obj->segment.unk3A >= obj->segment.header->numberOfModelIds) {
        obj->segment.unk3A = 0;
    }
}

/**
 * T.T Door loop behaviour.
 * Checks if the player has complete the T.T amulet and has all 47 balloons.
 * If so, it will open, otherwise it opens dialogue telling the player to get them.
*/
void obj_loop_ttdoor(Object *obj, s32 updateRate) {
    Settings *settings;
    Object_TTDoor *ttDoor;
    Object *racerObj;
    Object_Racer *racer;
    s16 angle;
    s32 openDoor;

    ttDoor = (Object_TTDoor *) obj->unk64;
    settings = get_settings();
    if (ttDoor->unkF == 0) {
        obj->segment.unk3A = D_800DCA94[settings->ttAmulet];
    } else {
        obj->segment.unk3A = D_800DCA9C[settings->ttAmulet];
    }
    if (obj->unk4C->unk13 < ttDoor->unk12 && (settings->ttAmulet < 4 || *settings->balloonsPtr < 47)) {
        racerObj = obj->unk4C->unk0;
        if (racerObj != NULL && racerObj->segment.header->behaviorId == BHV_RACER) {
            racer = (Object_Racer *) racerObj->unk64;
            if (racer->playerIndex != PLAYER_COMPUTER && racerObj == obj->unk5C->unk100) {
                if (ttDoor->unk13 != -1 && func_800C3400() == 0 && ttDoor->unkC == 0) {
                    set_music_fade_timer(-8);
                    ttDoor->unk8 = 140;
                    set_sndfx_player_voice_limit(16);
                    play_sequence(SEQUENCE_NO_TROPHY_FOR_YOU);
                    func_800C31EC(ttDoor->unk13 & 0xFF);
                }
                ttDoor->unkC = 300;
            }
            if (func_800C3400() != 0) {
                ttDoor->unkC = 300;
            }
        }
    }
    if (ttDoor->unk8 && func_80001C08() == 0) {
        if (updateRate < ttDoor->unk8) {
            ttDoor->unk8 -= updateRate;
        } else {
            ttDoor->unk8 = 0.0f;
            set_music_fade_timer(8);
            set_sndfx_player_voice_limit(6);
        }
    }
    if (ttDoor->unkC > 0) {
        ttDoor->unkC -= updateRate;
    } else {
        ttDoor->unkC = 0;
    }
    openDoor = TRUE;
    if (settings->ttAmulet >= 4 && obj->unk4C->unk13 < ttDoor->unk12 && *settings->balloonsPtr >= 47) {
        angle = obj->segment.trans.y_rotation - obj->unk7C.word;
    } else {
        angle = obj->segment.trans.y_rotation - obj->unk78;
    }
    angle >>= 3;
    if (angle > 0x200) {
        angle = 0x200;
    }
    if (angle < -0x200) {
        angle = -0x200; 
    }
    obj->segment.trans.y_rotation -= angle;
    if (angle == 0) {
        openDoor = FALSE;
    }
    if (openDoor) {
        if (ttDoor->soundMask == NULL) {
            func_80009558(SOUND_DOOR_OPEN, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 1, &ttDoor->soundMask);
        }
    } else {
        if (ttDoor->soundMask) {
            func_800096F8((s32) ttDoor->soundMask);
            ttDoor->soundMask = NULL;
        }
    }
    obj->unk4C->unk13 = 0xFF;
    obj->unk4C->unk0 = NULL;
    obj->unk4C->unk14 &= 0xFFF7;
    obj->unk5C->unk100 = NULL;
}


void obj_init_trigger(Object *obj, LevelObjectEntry_Trigger *entry) {
    f32 phi_f0;
    Object_Trigger *obj64;

    if (entry->unk9 == -1) {
        entry->unk9 = func_8000CC20(obj);
    } else {
        func_8000CBF0(obj, entry->unk9);
    }
    if (entry->unk9 == -1) {
        rmonPrintf("Illegal door no!!!\n");
    }
    phi_f0 = (s32)entry->scale & 0xFF;
    if (phi_f0 < 5.0f) {
        phi_f0 = 5.0f;
    }
    obj64 = &obj->unk64->trigger;
    phi_f0 /= 128;
    obj->segment.trans.scale = phi_f0;
    obj->segment.trans.y_rotation = entry->rotation << 6 << 4;
    obj64->unk0 = sins_f(obj->segment.trans.y_rotation);
    obj64->unk4 = 0.0f;
    obj64->unk8 = coss_f(obj->segment.trans.y_rotation);
    obj64->unkC = -((obj64->unk0 * obj->segment.trans.x_position) + (obj64->unk8 * obj->segment.trans.z_position));
    obj64->unk10 = entry->scale;
    obj64->unk14 = entry->unkD;
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = entry->scale;
    obj->unk4C->unk12 = 0;
}


GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_trigger.s")

void obj_init_bridge_whaleramp(Object *obj, LevelObjectEntry_Bridge_WhaleRamp *entry) {
    Object_Bridge_WhaleRamp *temp = &obj->unk64->bridge_whale_ramp;
    obj->segment.unk3A = entry->unk8;
    obj->segment.trans.y_rotation = entry->unk9 << 6 << 4;
    temp->unk0 = obj->segment.trans.y_position;
    obj->unk4C->unk14 = 0x21;
    obj->unk4C->unk11 = 2;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
    temp->unk4 = 0;
    if (obj->segment.unk3A >= obj->segment.header->numberOfModelIds) {
        obj->segment.unk3A = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_bridge_whaleramp.s")

void obj_init_rampswitch(Object *obj, LevelObjectEntry_RampSwitch *entry) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
    obj->unk78 = entry->unk8;
}

void obj_loop_rampswitch(Object *obj, UNUSED s32 speed) {
    if (obj->unk4C->unk13 < 0x2D) {
        func_8001E344(obj->unk78);
    }
    obj->unk4C->unk13 = (u8)0xFF;
}

void obj_init_seamonster(UNUSED Object *obj, UNUSED LevelObjectEntry_SeaMonster *entry) {
}

void obj_loop_seamonster(UNUSED Object *obj, UNUSED s32 speed) {
}

void obj_init_fogchanger(Object *obj, LevelObjectEntry_FogChanger *entry) {
    f32 temp_f0;
    temp_f0 = entry->unk8 * 8.0f;
    temp_f0 = temp_f0 * temp_f0;
    obj->unk78f = temp_f0;
}

void obj_init_skycontrol(Object *obj, LevelObjectEntry_SkyControl *entry) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = entry->unk9;
    obj->unk78 = entry->unk8;
    obj->unk7C.word = entry->unk9;
}

void obj_loop_skycontrol(Object *obj, UNUSED s32 speed) {
    if (obj->unk4C->unk13 < obj->unk7C.word) {
        func_80028044(obj->unk78);
    }
}

void obj_init_ainode(Object *obj, LevelObjectEntry_AiNode *entry) {
    if (entry->unk9 == 0xFF) {
        entry->unk9 = func_8001C48C(obj) & 0xFF;
    }
    func_8001D1BC(entry->unk9);
    func_8001D1AC();
}

void obj_loop_ainode(UNUSED Object *obj, UNUSED s32 speed) {
}

void obj_init_treasuresucker(Object *obj, LevelObjectEntry_TreasureSucker *entry) {
    obj->segment.unk18 = 0x78;
    obj->unk78 = (entry->unk8 - 1) & 3;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_treasuresucker.s")

void obj_init_flycoin(UNUSED Object *obj, UNUSED LevelObjectEntry_FlyCoin *entry) {
}

// Smokey's castle banana pickups.
void obj_loop_flycoin(Object *obj, s32 updateRate) {
    f32 updateRateF;
    Object_Racer *racerObj;

    updateRateF = updateRate;
    if (osTvType == TV_TYPE_PAL) {
        updateRateF *= 1.2;
    }
    obj->segment.y_velocity -= 0.5 * updateRateF;
    func_80011570(obj, obj->segment.x_velocity * updateRateF, obj->segment.y_velocity * updateRateF, obj->segment.z_velocity * updateRateF);
    obj->unk78 -= updateRate;
    if (obj->unk78 <= 0) {
        racerObj = (Object_Racer *) obj->unk7C.word;
        racerObj->lap++;
        if (racerObj->lap >= 10) {
            racerObj->raceFinished = TRUE;
        }
        gParticlePtrList_addObject(obj);
        if (racerObj->playerIndex != PLAYER_COMPUTER) {
            play_sound_global(SOUND_SELECT, NULL);
        }
    }
    obj->segment.unk18 += updateRate * 8;
}

void obj_init_bananacreator(Object *obj, UNUSED LevelObjectEntry_BananaCreator *entry) {
    obj->segment.unk18 = 100;
}

void obj_loop_bananacreator(Object *obj, s32 speed) {
  LevelObjectEntryCommon newEntry;
  Object *newBananaObj;
  Object_Banana *newBananaObj64;

  if (obj->unk7C.word != 0) {
    obj->unk78 -= speed;
  }

  if (obj->unk78 <= 0) {
    newEntry.x = (s32) obj->segment.trans.x_position;
    newEntry.y = ((s32) ((s16) obj->segment.trans.y_position)) - 3;
    newEntry.z = (s32) obj->segment.trans.z_position;
    newEntry.size = 8;
    newEntry.objectID = 83;
    newBananaObj = spawn_object(&newEntry, 1);
    obj->unk7C.word = 1;
    if (newBananaObj) {
      newBananaObj->segment.unk3C_a.level_entry = NULL;
      newBananaObj64 = &newBananaObj->unk64->banana;
      newBananaObj64->spawner = obj;
      func_8003FC44(obj->segment.trans.x_position, obj->segment.trans.y_position - 14.0f, obj->segment.trans.z_position, 44, 34, 0.25f, 0);
      obj->unk7C.word = 0;
    }
    obj->unk78 = TIME_SECONDS(20); // Set delay to respawn banana to 20 seconds.
  }
}


void obj_init_banana(Object *obj, UNUSED LevelObjectEntry_Banana *entry) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x1E;
    obj->unk7C.half.upper = 0x14;
    obj->unk7C.half.lower = 0x10;
    if (get_filtered_cheats() & CHEAT_DISABLE_BANANAS) {
        gParticlePtrList_addObject(obj);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_banana.s")

void obj_init_silvercoin_adv2(Object *obj, UNUSED LevelObjectEntry_SilverCoinAdv2 *entry) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x1E;
    obj->unk78 = 3;
    obj->unk7C.word = 16;
    if (!is_in_tracks_mode()) {
        if (check_if_silver_coin_race() && is_in_adventure_two()) {
            obj->unk78 = 0;
        } else {
            obj->unk78 = 3;
        }
    }
    if (obj->unk78 == 3) {
        obj->segment.trans.unk6 |= 0x600;
        gParticlePtrList_addObject(obj);
    }
}

void obj_init_silvercoin(Object *obj, UNUSED LevelObjectEntry_SilverCoin *entry) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x1E;
    obj->unk78 = 3;
    obj->unk7C.word = 0;
    if (!is_in_tracks_mode()) {
        if (check_if_silver_coin_race() && !is_in_adventure_two()) {
            obj->unk78 = 0;
        } else {
            obj->unk78 = 3;
        }
    }
    if (obj->unk78 == 3) {
        obj->segment.trans.unk6 |= 0x600;
        gParticlePtrList_addObject(obj);
    }
}

void obj_loop_silvercoin(Object *obj, s32 updateRate) {
    Object_4C* silverCoin4C;
    Object_Racer* racer;
    Object *racerObj;
    s32 temp;

    temp = func_8006C19C();
    if ((temp && obj->unk78 != 3) || (!temp && obj->unk78 == 0)) {
        silverCoin4C = obj->unk4C;
        if (silverCoin4C->unk13 < 80) {
            racerObj = (Object *) silverCoin4C->unk0;
            if (racerObj != NULL && racerObj->segment.header->behaviorId == BHV_RACER) {
                racer = (Object_Racer *) racerObj->unk64;
                if (racer->playerIndex != -1) {
                    if (racer->raceFinished == FALSE && !(obj->unk78 & (1 << racer->playerIndex))) {
                        obj->unk78 |= (1 << racer->playerIndex);
                        obj->unk7C.word = 0x10;
                        obj->segment.trans.unk6 |= 0x200 << racer->playerIndex;
                        play_sequence(racer->unk202 + 0x2B);
                        racer->unk202++;
                    }
                }
            }
        }
        obj->segment.unk18 += 8 * updateRate;
    }
    if (obj->unk7C.word > 0) {
        obj->unk7C.word -= updateRate;
        obj->unk74 = 1;
        func_800AFC3C(obj, updateRate);
    }
}


void obj_init_worldkey(Object *obj, LevelObjectEntry_WorldKey *entry) {
    Settings *settings;
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x1E;
    entry->unk8 &= 0xF;
    obj->unk78 = entry->unk8;
    settings = get_settings();
    if (!is_in_tracks_mode() && !(settings->keys & (1 << obj->unk78))) {
        return;
    }
    gParticlePtrList_addObject(obj);
}

/**
 * Rotates the key and checks to see if the player grabbed it.
 */
void obj_loop_worldkey(Object *worldKeyObj, s32 speed) {
    Settings *settings;
    Object *playerObj;

    // Check if the player is near the key
    // "worldKeyObj->unk4C->unk13" is the player's distance from the key (Up to 255).
    if (worldKeyObj->unk4C->unk13 < WORLD_KEY_GRAB_CHECK_RADIUS) {
        // "worldKeyObj->unk4C->unk0" is only set when the player is within 255 units of
        // the key object, otherwise it is NULL.
        playerObj = worldKeyObj->unk4C->unk0;
        if (playerObj != NULL) {
            if (playerObj->segment.header->behaviorId == 1) { // Is the player a racer?
                Object_WorldKey *obj64 = &playerObj->unk64->world_key;
                if (obj64->unk0 != -1) {
                    // Player has grabbed the key!
                    play_sequence(SEQUENCE_KEY_COLLECT);
                    settings = get_settings();
                    settings->keys |= 1 << worldKeyObj->unk78; // Set key flag
                    gParticlePtrList_addObject(worldKeyObj);   // Makes the key unload.
                }
            }
        }
    }

    // Rotate world key
    worldKeyObj->segment.trans.y_rotation += speed * 256;
}

void obj_init_weaponballoon(Object *obj, LevelObjectEntry_WeaponBalloon *entry) {
    s32 cheats;
    Object_WeaponBalloon *obj64;
    f32 scalef;

    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 4;
    obj->unk4C->unk10 = 0x14;

    cheats = get_filtered_cheats();

    if (cheats & CHEAT_ALL_BALLOONS_ARE_BLUE) {
        entry->balloonType = BALLOON_TYPE_BOOST;
    } else if (cheats & CHEAT_ALL_BALLOONS_ARE_RED) {
        entry->balloonType = BALLOON_TYPE_MISSILE;
    } else if (cheats & CHEAT_ALL_BALLOONS_ARE_GREEN) {
        entry->balloonType = BALLOON_TYPE_TRAP;
    } else if (cheats & CHEAT_ALL_BALLOONS_ARE_YELLOW) {
        entry->balloonType = BALLOON_TYPE_SHIELD;
    } else if (cheats & CHEAT_ALL_BALLOONS_ARE_RAINBOW) {
        entry->balloonType = BALLOON_TYPE_MAGNET;
    }

    // I guess unk8 is unused?
    if (entry->unk8 >= 6) {
        entry->unk8 = 0;
    }

    if (obj->segment.unk3A >= obj->segment.header->numberOfModelIds) {
        obj->segment.unk3A = 0;
    }

    obj->segment.unk3A = entry->balloonType;
    obj->unk78 = obj->segment.unk3A;

    scalef = entry->scale & 0xFF;
    if (scalef < 10) {
        scalef = 10;
    }
    scalef /= 64;

    obj64 = &obj->unk64->weapon_balloon;

    obj->segment.trans.scale = obj->segment.header->scale * scalef;
    obj64->unk0 = obj->segment.trans.scale;
    obj64->unk4 = 0;
    obj->unk7C.word = 0;

    if (get_filtered_cheats() & CHEAT_DISABLE_WEAPONS) {
        gParticlePtrList_addObject(obj);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_weaponballoon.s")

void obj_init_wballoonpop(UNUSED Object *obj, UNUSED LevelObjectEntry_WBalloonPop *entry) {
}

void obj_loop_wballoonpop(UNUSED Object *obj, UNUSED s32 speed) {
}

void obj_init_weapon(Object *obj, UNUSED LevelObjectEntry_Weapon *entry) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x18;
    obj->unk4C->unk12 = 0;
    obj->unk78 = normalise_time(0x1E0);
    obj->unk7C.word = 0;
}

void obj_loop_weapon(Object *obj, s32 speed) {
    Object_Weapon *obj64 = &obj->unk64->weapon;
    switch (obj64->weaponID) {
        case 0:
        case 1:
            func_8003E694(obj, speed);
            break;
        case 2:
        case 3:
        case 10:
        case 11:
            func_8003F2E8(obj, speed);
            break;
    }
    return;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003E694.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003EC14.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003EDD8.s")

void func_8003F0D0(void) {
    D_8011D4DC = 0;
}

void func_8003F0DC(void) {
    D_8011D4DC--;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003F0F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003F2E8.s")

void func_8003FC44(f32 x, f32 y, f32 z, s32 objectID, s32 arg4, f32 scale, s32 arg6) {
    LevelObjectEntry8003FC44 spawnObj;
    Object *newObj;

    spawnObj.common.x = x;
    spawnObj.common.y = (s16) y + 36;
    spawnObj.common.z = z;
    spawnObj.common.size = 10;
    spawnObj.common.objectID = objectID;
    spawnObj.unk9 = arg6;
    newObj = spawn_object(&spawnObj, 1);
    if (newObj != NULL) {
        newObj->segment.unk3C_a.level_entry = NULL;
        newObj->segment.x_velocity = 0.0f;
        newObj->segment.y_velocity = 0.0f;
        newObj->segment.z_velocity = 0.0f;
        newObj->segment.trans.scale = newObj->segment.trans.scale * 3.5 * scale;
    }
    if (arg4 != 0) {
        func_80009558(arg4, x, y, z, 4, NULL);
    }
}

void obj_init_audio(Object *obj, LevelObjectEntry_Audio *entry) {
    Object_Audio *obj64;

    obj64 = &obj->unk64->audio;
    obj64->unk0 = entry->unk8;
    obj64->unk2 = entry->unkA;
    obj64->unkC = entry->unkF;
    obj64->unk6 = entry->unkE;
    obj64->unk4 = entry->unkC;
    obj64->unk5 = entry->unkD;
    obj64->unkD = entry->unk10;
    obj64->unk8 = 0;
    if (ALBankFile_80115D14_GetSoundDecayTime(obj64->unk0)) {
        func_8000974C(obj64->unk0, entry->common.x, entry->common.y, entry->common.z,
            9, obj64->unk5, obj64->unk4, obj64->unk2, obj64->unkC,
            obj64->unk6, obj64->unkD, &obj64->unk8);
    } else {
        func_8000974C(obj64->unk0, entry->common.x, entry->common.y, entry->common.z,
            10, obj64->unk5, obj64->unk4, obj64->unk2, obj64->unkC,
            obj64->unk6, obj64->unkD, &obj64->unk8);
    }
    gParticlePtrList_addObject(obj);
}

void obj_init_audioline(Object *obj, LevelObjectEntry_AudioLine *entry) {
    Object_AudioLine *obj64;

    obj64 = &obj->unk64->audio_line;
    obj64->unk0 = entry->unk8;
    obj64->unk2 = entry->unkA;
    obj64->unkC = entry->unkC;
    obj64->unkD = entry->unkD;
    obj64->unk_union.unk8_word = 0;
    obj64->unk4 = entry->unkE;
    obj64->unk11 = entry->unk12;
    obj64->unk10 = entry->unk11;
    obj64->unkE = entry->unk9;
    obj64->unkF = entry->unk10;
    obj64->unk12 = entry->unk13;
    func_800098A4(obj64->unk0, obj64->unk2, entry->common.x, entry->common.y, entry->common.z,
                  obj64->unkF, obj64->unkE, obj64->unk10, obj64->unk12, obj64->unk4, obj64->unk11,
                  obj64->unkC, obj64->unkD);
    gParticlePtrList_addObject(obj);
}

void obj_init_audioreverb(Object *obj, LevelObjectEntry_AudioReverb *entry) {
    s32 temp;
    Object_AudioReverb *obj64 = &obj->unk64->audio_reverb;
    obj64->unk2 = entry->unk8;
    temp = entry->unk9;
    obj64->unk4 = temp & 0xFF;
    obj64->unk5 = entry->unkA;
    func_80009968(entry->common.x, entry->common.y, entry->common.z, obj64->unk2, obj64->unk4, obj64->unk5);
    gParticlePtrList_addObject(obj);
}

void obj_init_texscroll(Object *obj, LevelObjectEntry_TexScroll *entry, s32 arg2) {
    Object_TexScroll *obj64;
    LevelModel *levelModel;
    s16 numberOfTexturesInLevel;

    obj64 = &obj->unk64->tex_scroll;
    levelModel = get_current_level_model();
    obj64->unk0 = entry->unk8;
    if (obj64->unk0 < 0) {
        obj64->unk0 = 0;
    }
    numberOfTexturesInLevel = levelModel->numberOfTextures;
    if (obj64->unk0 >= numberOfTexturesInLevel) {
        obj64->unk0 = numberOfTexturesInLevel - 1;
    }
    obj64->unk4 = (s16)entry->unkA;
    obj64->unk6 = (s16)entry->unkB;
    if (arg2 == 0) {
        obj64->unk8 = 0;
        obj64->unkA = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_texscroll.s")

void obj_init_rgbalight(Object *obj, LevelObjectEntry_RgbaLight *entry, UNUSED s32 arg2) {
    obj->unk64 = func_80031CAC(obj, entry);
}

void obj_init_buoy_pirateship(Object *obj, UNUSED LevelObjectEntry_Buoy_PirateShip *entry, UNUSED s32 arg2) {
    obj->unk64 = func_800BE654(obj->segment.unk2C.half.lower, obj->segment.trans.x_position, obj->segment.trans.z_position);
    obj->unk4C->unk14 = 1;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x1E;
    obj->unk4C->unk12 = 0;
}

void obj_loop_buoy_pirateship(Object *obj, s32 speed) {
    if (obj->unk64 != NULL) {
        obj->segment.trans.y_position = func_800BEEB4(obj->unk64);
    }
    obj->segment.unk18 += speed * 8;
}

void obj_init_log(Object *obj, LevelObjectEntry_Log *entry, UNUSED s32 arg2) {
    f32 phi_f0;
    obj->unk64 = func_800BE654(obj->segment.unk2C.half.lower, obj->segment.trans.x_position, obj->segment.trans.z_position);
    obj->unk4C->unk14 = 1;
    obj->unk4C->unk11 = 2;
    obj->unk4C->unk10 = 0x1E;
    phi_f0 = entry->unk9 & 0xFF;
    if (phi_f0 < 10.0f) {
        phi_f0 = 10.0f;
    }
    phi_f0 /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * phi_f0;
    obj->segment.unk3A = entry->unk8;
    obj->segment.trans.y_rotation = entry->unkA << 6 << 4;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_log.s")

void obj_init_weather(Object *obj, LevelObjectEntry_Weather *entry) {
    f32 temp = entry->unk8;
    temp *= temp;
    obj->unk78f = temp;
}

/**
 * Weather updater loop behaviour.
 * When passed through by the player, it will update the current weather settings.
 * Can be used to stop, start or change the intensity of the current weather.
*/
void obj_loop_weather(Object *obj, UNUSED s32 speed) {
  s32 currViewport;
  s32 numberOfObjects;
  Object_Racer *curObj64;
  Object **objects;
  Object *curObj;
  LevelObjectEntry_Weather *entry;
  f32 diffX;
  f32 diffZ;
  s32 cur;
  s32 last;
  f32 dist;
    
  currViewport = get_current_viewport();
  objects = get_racer_objects(&numberOfObjects);
  cur = -1;
  if (numberOfObjects != 0) {
    last = numberOfObjects - 1;
    do {
      curObj = objects[cur + 1];
      curObj64 = (Object_Racer *) curObj->unk64;
    } while (++cur < last && currViewport != curObj64->playerIndex);
    
    diffX = obj->segment.trans.x_position - curObj->segment.trans.x_position;
    diffZ = obj->segment.trans.z_position - curObj->segment.trans.z_position;
    dist = obj->unk78f;
    entry = (LevelObjectEntry_Weather *)obj->segment.unk3C_a.level_entry;
    if (((diffX * diffX) + (diffZ * diffZ)) <= dist){
      if (((!obj->segment.unk3C_a.level_entry) && (!obj->segment.unk3C_a.level_entry)) && (!obj->segment.unk3C_a.level_entry)){}  // Fakematch
      func_800ABC5C(entry->unkA * 256, entry->unkC * 256, entry->unkE * 256, entry->unk10 * 257, entry->unk11 * 257, entry->unk12);
    }
  }
}

void obj_init_lensflare(Object *obj, UNUSED LevelObjectEntry_LensFlare *entry) {
    func_800AC8A8(obj);
}

void obj_init_lensflareswitch(Object *obj, LevelObjectEntry_LensFlareSwitch *entry, UNUSED s32 arg2) {
    func_800ACF60(obj);
    obj->segment.trans.scale = entry->unk8;
    obj->segment.trans.scale /= 40.0f;
}

void obj_init_wavegenerator(Object *obj, UNUSED LevelObjectEntry_WaveGenerator *entry, UNUSED s32 arg2) {
    func_800BF524(obj);
}

#ifdef NON_EQUIVALENT

void obj_init_butterfly(Object *obj, LevelObjectEntry_Butterfly *entry, s32 arg2) {
    Object_Butterfly *obj64;
    s32 i, j;
    s32 uMask, vMask;

    obj64 = &obj->unk64->butterfly;
    if (arg2 == 0) {
        obj->segment.y_velocity = 0.0f;
        obj64->unkFE = 0;
        obj64->unk100 = 0;
        obj64->unk104 = 0;
        obj64->unkFD = 0;
        obj64->unk106 = 384;
        obj64->unk108 = 0.0f;
        // This loop is okay
        for(i = 0; i < 8; i++) {
            obj64->triangles[i].flags = D_800DCAA8[i].flags;
            obj64->triangles[i].vi0 = D_800DCAA8[i].vi0;
            obj64->triangles[i].vi1 = D_800DCAA8[i].vi1;
            obj64->triangles[i].vi2 = D_800DCAA8[i].vi2;
        }
        // This loop is not.
        for(i = 0; i < 6; i++) {
            //u32 j = i + 6;
            obj64->vertices[i].x = D_800DCB28[i].x;
            obj64->vertices[i].y = D_800DCB28[i+1].y;
            obj64->vertices[i].z = D_800DCB28[i+1].z;
            obj64->vertices[i].r = 255;
            obj64->vertices[i].g = 255;
            obj64->vertices[i].b = 255;
            obj64->vertices[i].a = 255;
            obj64->vertices[(u32)(i+6)].x = D_800DCB28[i+1].x;
            obj64->vertices[i+6].y = D_800DCB28[i].y;
            obj64->vertices[i+6].z = D_800DCB28[i].z;
            obj64->vertices[i+6].r = 255;
            obj64->vertices[i+6].g = 255;
            obj64->vertices[i+6].b = 255;
            obj64->vertices[i+6].a = 255;
        }
        obj64->unkFC = 1;
    }
    obj->segment.trans.scale = entry->unkB * 0.01f;
    if (entry->unkA < obj->segment.header->numberOfModelIds) {
        obj64->texture = (TextureHeader*)obj->unk68[entry->unkA];
    } else {
        obj64->texture = (TextureHeader*)obj->unk68[0];
    }

    if (obj64->texture) {
        uMask = (obj64->texture->width - 1) << 5;
        vMask = (obj64->texture->height - 1) << 5;
    } else {
        uMask = 0;
        vMask = 0;
    }
    for(i = 0; i < 8; i++) {
        obj64->triangles[i].uv0.u = D_800DCAA8[i].uv0.u & uMask;
        obj64->triangles[i].uv0.v = D_800DCAA8[i].uv0.v & vMask;
        obj64->triangles[i].uv1.u = D_800DCAA8[i].uv1.u & uMask;
        obj64->triangles[i].uv1.v = D_800DCAA8[i].uv1.v & vMask;
        obj64->triangles[i].uv2.u = D_800DCAA8[i].uv2.u & uMask;
        obj64->triangles[i].uv2.v = D_800DCAA8[i].uv2.v & vMask;
    }
}


#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_init_butterfly.s")
#endif

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_butterfly.s")

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_init_midifade.s")

void obj_init_midifadepoint(Object *obj, LevelObjectEntry_MidiFadePoint *entry) {
  Object_MidiFadePoint *obj64;
  ObjectModel **models;
  ObjectModel *objModel;
  Vertex *vertex;
  s32 i;
  f32 x;
  f32 y;
  f32 z;
  f32 dist;

  obj64 = &obj->unk64->midi_fade_point;
  obj64->unk2 = entry->unkA;
  obj64->unk0 = entry->unk8;
  obj64->unk1C = entry->unk1C;
  if (obj64->unk2 < obj64->unk0) {
    obj64->unk2 = obj64->unk0 + 10;
  }
  obj->segment.trans.z_rotation = 0;
  obj->segment.trans.x_rotation = 0;
  obj->segment.trans.y_rotation = 0;

  for (i = 0; i < 15; i++) {
    obj64->unkC[i] = entry->unkC[i];
  }

  models = *((ObjectModel ***) obj->unk68);
  objModel = models[0];
  vertex = objModel->vertices + 1;
  x = vertex->x;
  y = vertex->y;
  z = vertex->z;
  dist = sqrtf(((x * x) + (y * y)) + (z * z));
  obj64->unk4 = entry->unk8 / dist;
  obj64->unk8 = entry->unkA / dist;
  obj->segment.trans.scale = obj64->unk8;
}

void obj_init_midichset(Object *obj, LevelObjectEntry_Midichset *entry) {
    unk80042014_arg0_64 *temp = (unk80042014_arg0_64 *) obj->unk64;
    temp->unk0 = entry->unk8;
    temp->unk2 = entry->unkA;
    temp->unk3 = entry->unkB;
}

void obj_init_bubbler(Object *obj, LevelObjectEntry_Bubbler *entry) {
    func_800AF134((unk800B2260 *) obj->unk6C, entry->unk9, entry->unk8, 0, 0, 0);
    obj->unk78 = entry->unkA;
}

void obj_loop_bubbler(Object *obj, s32 speed) {
    if (obj->unk78 >= get_random_number_from_range(0, 0x400)) {
        obj->unk74 = 1;
    } else {
        obj->unk74 = 0;
    }
    if (get_number_of_active_players() < 2) {
        func_800AFC3C(obj, speed);
    }
}

void obj_init_boost(Object *obj, LevelObjectEntry_Boost *entry) {
    obj->unk64 = (s32) get_misc_asset(MISC_ASSET_UNK14) + (entry->unk8[0] << 7);
    obj->segment.unk3C_a.level_entry = NULL;
}

void obj_init_unknown94(UNUSED Object *obj, UNUSED LevelObjectEntry_Unknown94 *entry, UNUSED s32 arg2) {
}

void obj_loop_unknown94(UNUSED Object *obj, s32 UNUSED speed) {
}

void obj_init_rangetrigger(UNUSED Object *obj, UNUSED LevelObjectEntry_RangeTrigger *entry) {
}

void obj_loop_rangetrigger(Object *obj, s32 speed) {
    UNUSED s32 temp;
    LevelObjectEntry_RangeTrigger *level_entry;
    unk80042178 sp20;

    level_entry = &obj->segment.unk3C_a.level_entry->rangeTrigger;
    if (func_80016DE8(obj->segment.trans.x_position, 0, obj->segment.trans.z_position, (f32)level_entry->unk8, 1, &sp20) > 0) {
        obj->unk74 = level_entry->unkA;
    } else {
        obj->unk74 = 0;
    }
    func_800AFC3C(obj, speed);
}

void obj_init_frog(Object *obj, LevelObjectEntry_Frog *entry) {
    Object_Frog *obj64;

    obj64 = &obj->unk64->frog;
    obj64->unk15 = entry->unkA;
    obj64->unk0 = obj->segment.trans.x_position;
    obj64->unk4 = obj->segment.trans.y_position;
    obj64->unk8 = obj->segment.trans.z_position;
    obj64->unkC = entry->unk8;
    obj64->unk10 = obj64->unkC * obj64->unkC;
    obj64->unk14 = 0;
    obj64->unk20 = obj->segment.trans.x_position;
    obj64->unk24 = obj->segment.trans.z_position;
    obj64->unk19 = 0;
    obj64->unk30 = 1.0f;

    if (obj64->unk15) {
        obj->segment.unk3A = 1;
        /**
          * Don't spawn the chicken frog if drumstick is already unlocked, or
          * if the player hasn't completed the trophy races yet.
          */
        if (is_drumstick_unlocked() || (get_settings()->trophies & 0xFF) != 0xFF) {
            gParticlePtrList_addObject(obj);
        }
    } else {
        obj->segment.unk3A = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_frog.s")

void obj_loop_pigrocketeer(Object *obj, s32 speed) {
    Object *someObj;
    Object_Wizpig2 *obj64;

    func_8001F460(obj, speed, obj);
    someObj = func_8000BF44(-1);

    if (someObj != NULL) {
        obj64 = &someObj->unk64->wizpig2;
        someObj->unk78 = 0;
        if (obj64 != 0) {
            obj64->unk72 += speed;
            obj64->unk70 = 2;
            obj64->unk74 = 1.0f;
            func_8000B750(obj, -1, 2, 1, 1);
        }
    }
}

void obj_init_levelname(Object *obj, LevelObjectEntry_LevelName *entry) {
    obj->unk78f = entry->unk9 * 8.0f;
    obj->unk78f *= obj->unk78f;
    obj->unk7C.half.upper = entry->unk8;
    obj->unk7C.half.lower = 0;
    if (is_in_tracks_mode()) {
        gParticlePtrList_addObject(obj);
    }
    func_800C56D0(4);
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_levelname.s")

void obj_loop_wizghosts(Object *obj, s32 speed) {
    func_8001F460(obj, speed, obj);
    obj->segment.unk18 = (obj->segment.unk18 + (speed * 8)) & 0xFF;
}

