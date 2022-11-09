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

/************ .data ************/

// Unsure about the signed/unsigned with these arrays.
u16 D_800DC970[4] = {
    0x40FF, 0xFFFF, 0x0007, 0x0003
};
u16 D_800DC978[4] = {
    0x0000, 0x0000, 0x001E, 0xFFFF
};
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
s16 D_8011D4E2;

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
        obj78 = &obj->unk78;
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
        if (obj->unk4A == 298 && func_8002AD08(obj->segment.trans.y_position, &sp4C, 0)) {
			obj->segment.trans.y_position = sp4C[0];
        }
    }
    obj->segment.unk18 += speed * 10;
    obj64 = obj->unk64;
    obj4C = obj->unk4C;
    obj4C_obj = (Object*)obj4C->unk0; // This should be a0, not v1!
    if ((obj4C_obj != NULL) && (obj4C->unk13 < 60) && (obj4C_obj->segment.header->behaviorId == 1)) {
        obj4C_obj64 = obj4C_obj->unk64;
        if (obj4C_obj64->unk0 != -1) {
            if (obj->behaviorId == 108) {
                obj4C_obj64->unk187 = 1;
                obj->unk7C.word = 20;
                func_8003FC44(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 44, 17, 1.0f, 1);
                gParticlePtrList_addObject(obj);
            } else if (obj->unk7C.word > 0) {
                obj4C_obj64->unk204 = 60;
                obj->unk7C.word = -60;
                obj->unk78 = obj4C_obj;
                play_sound_global(SOUND_BUBBLE_RISE, &obj64->unk1C);
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

void obj_loop_effectbox(Object *obj, s32 speed) {
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
    temp0 = sine_s((level_entry->unkB << 8) * -1);
    temp1 = cosine_s((level_entry->unkB << 8) * -1);
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

#ifdef NON_EQUIVALENT

void play_sound_global(u16, s32 *);
void play_sound_global(u16, s32 *);
u32 func_80001C08(void);
void play_sound_global(u16, s32 *);
Object *spawn_object(void *, s32);
void func_8005A3B0(void);
void func_8006F254(void);
void func_8009CF68(s32 arg0);
s32 func_8009CFEC(u32 arg0);
void func_800A3870(void);
void func_800AB1AC(s32 arg0);
void func_800AB1D4(u8 arg0);
void func_800C31EC(s32);
s32 func_800C3400(void);
LevelHeader *get_current_level_header(void);
Settings *get_settings(void);
void set_music_fade_timer(s32 time);
void set_sndfx_player_voice_limit(u8 voiceLimit);

typedef struct Object_54_80034E9C {
    u8 pad0[0x28];
    f32 unk28;
    f32 unk2C;
} Object_54_80034E9C;

// Has regalloc & stack issues.

void obj_loop_trophycab(Object *obj, s32 speed) {
    s32 sp34;
    s32 isTrophyRaceAvaliable;
    s32 raceType;
    LevelObjectEntryCommon sp44;
    Settings *settings;
    LevelHeader *curLevelHeader;
    Object_TrophyCabinet *obj64;
    Object *trophyObj;
    Object *playerObj;
    f32 xDiff;
    f32 zDiff;
    s32 new_var2;

    settings = get_settings();
    curLevelHeader = get_current_level_header();
    obj64 = &obj->unk64->trophy_cabinet;

    // Show trophy inside the cabinet
    if (obj->unk7C.word == 0) {
        raceType = curLevelHeader->race_type;
        if ((raceType != 7) && (raceType != 6)) { // Make sure the current level is not a cutscene.
            obj->unk7C.word = 1;
            if ((settings->trophies >> (((settings->worldId - 1) ^ 0) * 2)) & 3) {
                sp44.objectID = 128;
                sp44.x = obj->segment.unk3C_a.level_entry->trophyCabinet.common.x;
                sp44.y = obj->segment.unk3C_a.level_entry->trophyCabinet.common.y;
                sp44.z = obj->segment.unk3C_a.level_entry->trophyCabinet.common.z;
                sp44.size = 8;
                trophyObj = spawn_object(&sp44, 1);
                if (trophyObj) {
                    trophyObj->segment.unk3C_a.level_entry = NULL;
                    trophyObj->segment.trans.y_rotation = obj->segment.trans.y_rotation;
                }
            }
        }
    }

    ((Object_54_80034E9C *) obj->unk54)->unk2C = 0.612f;
    ((Object_54_80034E9C *) obj->unk54)->unk28 = 0.0f;

    playerObj = get_racer_object(0);
    if (playerObj) {
        xDiff = obj->segment.trans.x_position - playerObj->segment.trans.x_position;
        zDiff = playerObj->segment.trans.z_position - obj->segment.trans.z_position;
        sqrtf((xDiff * xDiff) + (zDiff * zDiff)); // Distance on X & Z axes. Not used?

        new_var2 = settings->bosses;

        /**
          * Future Fun Land doesn't have a boss rematch, so this OR is needed so that
          * trophy race becomes avaliable after all the balloons have been collected.
          */
        new_var2 |= 0x800;

        // Check if all the balloons have been collected.
        isTrophyRaceAvaliable = (settings->balloonsPtr[settings->worldId] < 8) ^ 1;
        if (isTrophyRaceAvaliable) {
            // Check if the boss rematch has been beaten.
            isTrophyRaceAvaliable = ((1 << (settings->worldId + 6)) & new_var2) != 0;
        }

        // Hit detection between cabinet & player?
        if ((((obj->unk78 == 0) && (!func_800C3400())) && obj->unk5C->unk100) && (obj64->unk4 == 0)) {
            // A hit has been detected at this point.
            if (isTrophyRaceAvaliable) {
                obj->unk78 = 1;
                play_sound_global(SOUND_VOICE_TT_TROPHY_RACE, NULL);
                func_800A3870();
            }
            else
            {
                func_800C31EC(4);
                obj64->unk4 = 180;
                obj64->unk0 = 140;
                set_sndfx_player_voice_limit(16);
                set_music_fade_timer(-8);
                play_sequence(SEQUENCE_NO_TROPHY_FOR_YOU);
            }
        }
        if ((obj64->unk0 != 0) && (func_80001C08() == 0)) {
            if (speed < obj64->unk0) {
                obj64->unk0 -= speed;
            }
            else
            {
                obj64->unk0 = 0;
                set_music_fade_timer(8);
                set_sndfx_player_voice_limit(6);
            }
        }
        if (obj->unk5C->unk100 || func_800C3400()) {
            obj64->unk4 = 180;
        }
        if (obj64->unk4 > 0) {
            obj64->unk4 -= speed;
        }
        else
        {
            obj64->unk4 = 0;
        }
        if (obj->unk78 == 1) {
            func_800AB1AC(3);
            func_800AB1D4(0);
            sp34 = func_8009CFEC(4);
            if (sp34 != 0) {
                obj->unk78 = 0;
                func_8009CF68(4);
                if (sp34 == 1) {
                    func_8006F254();
                    obj->unk78 = 2;
                }
                else
                {
                    func_800AB1D4(1);
                }
            }
            func_8005A3B0();
        }
        obj->unk5C->unk100 = NULL;
        if (isTrophyRaceAvaliable) {
            // Changes lighting/color of the cabinet?
            ((Object_54_80034E9C *) obj->unk54)->unk28 = 0.552f;
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_trophycab.s")
#endif

void obj_init_collectegg(Object *obj, UNUSED LevelObjectEntry_CollectEgg *entry) {
    obj->unk4C->unk14 = 2;
    obj->unk4C->unk11 = 0;
    obj->unk4C->unk10 = 0x14;
    obj->unk4C->unk12 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_collectegg.s")

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
            obj->unk78 = someObj;
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

void obj_init_unknown58(Object *obj, LevelObjectEntry_Unknown58 *entry) {
    obj->unk78 = 0;
    obj->unk7C.word = obj->segment.header;
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
            obj64->unk24 = obj->unk68[obj->unk7C.word];
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
                if (!(triangle->drawBackface & 0x80)) {
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
    Object* sp24;
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
            gParticlePtrList_addObject(obj64);
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

    sp18 = obj->unk64;
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

void obj_init_wizpigship(UNUSED Object *obj, UNUSED LevelObjectEntry_WizpigShip *entry) {
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_wizpigship.s")

void obj_loop_vehicleanim(Object *obj, s32 speed) {
    Object_60_800380F8 *obj60;
    Object *someObj;

    func_8001F460(obj, speed, obj);
    obj60 = obj->unk60;
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

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_bombexplosion.s")

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
    obj64->unk0 = cosine_s(obj->segment.trans.y_rotation);
    obj64->unk4 = 0.0f;
    obj64->unk8 = sine_s(obj->segment.trans.y_rotation);
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
    s32 temp;
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
    D_8011D4E2 = 0x10F;
}

void func_80039320(s16 arg0) {
    D_8011D4E2 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_parkwarden.s")

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
    obj64->unk0 = cosine_s(obj->segment.trans.y_rotation);
    obj64->unk4 = 0.0f;
    obj64->unk8 = sine_s(obj->segment.trans.y_rotation);
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
    obj64->unk0 = cosine_s(obj->segment.trans.y_rotation);
    obj64->unk4 = 0.0f;
    obj64->unk8 = sine_s(obj->segment.trans.y_rotation);
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
                        if (&obj->segment){ }
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
    f32 temp_f0;
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

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_ttdoor.s")

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
    obj64->unk0 = cosine_s(obj->segment.trans.y_rotation);
    obj64->unk4 = 0.0f;
    obj64->unk8 = sine_s(obj->segment.trans.y_rotation);
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

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_flycoin.s")

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

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_silvercoin.s")

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
    switch (obj64->unk18) {
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

#ifdef NON_EQUIVALENT
// Regalloc issues
void func_8003FC44(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, f32 arg5, s32 arg6) {
    Object *someObj;
    unk8003FC44 sp24;

    sp24.unk4 = (s32)arg1 + 0x24;
    sp24.unk1 = 0xA;
    sp24.unk2 = arg0;
    sp24.unk0 = arg3;
    sp24.unk7 = arg6;
    sp24.unk6 = arg2;
    someObj = spawn_object(&sp24, 1);
    if (someObj != NULL) {
        someObj->segment.trans.scale *= 3.5 * arg5;
        someObj->segment.unk3C_a.level_entry = NULL;
        someObj->segment.x_velocity = 0.0f;
        someObj->segment.y_velocity = 0.0f;
        someObj->segment.z_velocity = 0.0f;
    }
    if (arg4 != 0) {
        func_80009558(arg4, arg0, arg1, arg2, 4, 0);
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_8003FC44.s")
#endif

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


#ifdef NON_EQUIVALENT
void func_800ABC5C(s32, s32, s32, s32, s32, s32); /* extern */

// Has stack & regalloc issues.
void obj_loop_weather(Object *obj, s32 speed) {
    s32 sp54;
    s32 numberOfObjects;
    Object_Racer *curObj64;
    Object **objects;
    Object **lastObj;
    Object *curObj;
    LevelObjectEntry_Weather *level_entry;
    f32 temp_f0;
    f32 new_var;
    f32 temp_f2;
    s32 i;
    s32 temp[3];
    sp54 = get_object_render_stack_pos();
    objects = get_racer_objects(&numberOfObjects);
    if (numberOfObjects != 0) {
        lastObj = &objects[numberOfObjects - 1];
        objects--;
        do {
            curObj = objects[1];
            curObj64 = &curObj->unk64->racer;
        } while (((++objects) < lastObj) && (sp54 != curObj64->playerIndex));
        temp_f0 = obj->segment.trans.x_position - curObj->segment.trans.x_position;
        temp_f2 = obj->segment.trans.z_position - curObj->segment.trans.z_position;
        new_var = obj->unk78f;
        level_entry = &obj->segment.unk3C_a.level_entry->weather;
        if (((temp_f0 * temp_f0) + (temp_f2 * temp_f2)) <= (new_var * 1.0f)){
            func_800ABC5C(level_entry->unkA * 256, level_entry->unkC * 256, level_entry->unkE * 256, level_entry->unk10 * 257, level_entry->unk11 * 257, (s32) level_entry->unk12);
        }
    }
}

#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_weather.s")
#endif

void obj_init_lensflare(Object *obj, UNUSED LevelObjectEntry_LensFlare *entry) {
    func_800AC8A8(obj);
}

void obj_init_lensflareswitch(Object *obj, LevelObjectEntry_LensFlareSwitch *entry, UNUSED s32 arg2) {
    func_800ACF60(obj);
    obj->segment.trans.scale = entry->unk8;
    obj->segment.trans.scale /= 40.0f;
}

void obj_init_wavegenerator(Object *obj, UNUSED LevelObjectEntry_WaveGenerator *entry, UNUSED s32 arg2) {
    func_800BF524(obj); //waves.c
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
            obj64->triangles[i].drawBackface = D_800DCAA8[i].drawBackface;
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
    unk80042014_arg0_64 *temp = obj->unk64;
    temp->unk0 = entry->unk8;
    temp->unk2 = entry->unkA;
    temp->unk3 = entry->unkB;
}

void obj_init_bubbler(Object *obj, LevelObjectEntry_Bubbler *entry) {
    func_800AF134(obj->unk6C, entry->unk9, entry->unk8, 0, 0, 0);
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
    obj->unk64 = (s32)get_misc_asset(MISC_ASSET_UNK14) + (entry->unk8[0] << 7);
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

