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
#include "audiosfx.h"
#include "math_util.h"
#include "game_text.h"
#include "fade_transition.h"
#include "unknown_005740.h"
#include "object_models.h"
#include "lib/src/libc/rmonPrintf.h"
#include "collision.h"
#include "main.h"
#include "controller.h"

/************ .data ************/

// Unsure about the signed/unsigned with these arrays.
FadeTransition D_800DC970 = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_UNK1, FADE_COLOR_WHITE, 7, 3);
FadeTransition D_800DC978 = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 30, 0xFFFF);

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
s8 D_8011D4E0;
s16 D_8011D4E2; // Taj Voice clips

/******************************/

void func_80031130(s32 arg0, f32* arg1, f32* arg2, s32 arg3) {
#ifdef PUPPYPRINT_DEBUG
    u32 first = osGetCount();
#endif
    func_80031130_2(arg0, arg1, arg2, arg3);
#ifdef PUPPYPRINT_DEBUG
    profiler_add(gPuppyTimers.timers[PP_COLLISION], osGetCount() - first);
#endif
}

s32 func_80031600(f32* arg0, f32* arg1, f32* arg2, s8* arg3, s32 arg4, s32* arg5) {
#ifdef PUPPYPRINT_DEBUG
    u32 first = osGetCount();
#endif
    s32 ret = func_80031600_2(arg0, arg1, arg2, arg3, arg4, arg5);
#ifdef PUPPYPRINT_DEBUG
    profiler_add(gPuppyTimers.timers[PP_COLLISION], osGetCount() - first);
#endif
return ret;
}

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
    obj->segment.unk38.byte.unk3A = entry->unk8;
    obj->segment.trans.y_rotation = entry->unkA << 6 << 4;
    if (entry->unkB) {
        obj->interactObj->unk14 = 1;
        obj->interactObj->unk11 = 1;
        obj->interactObj->unk10 = 20;
        obj->interactObj->unk12 = 0;
        obj->interactObj->unk16 = -5;
        obj->interactObj->unk17 = entry->unkB;
    }
    if (obj->segment.unk38.byte.unk3A >= obj->segment.header->numberOfModelIds) {
        obj->segment.unk38.byte.unk3A = 0;
    }
    obj->action = 0;
    obj->unk7C.word = 0;
}

void obj_loop_scenery(Object *obj, s32 updateRate) {
	Object78_80033DD0 *obj78;
	s32 temp_v0;

    if (obj->interactObj != NULL) {
        obj78 = (Object78_80033DD0 *) &obj->action;
        if (obj->unk7C.half.upper > 0) {
            obj78->unk4 -= updateRate;
        }
        if ((obj->interactObj->unk14 & 0x40) && ((s32) obj78->unk4 <= 0)) {
            play_sound_at_position(SOUND_TWANG, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
            obj78->unk0 = (s32*) obj->interactObj->obj;
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
    obj->interactObj->unk14 = 2;
    obj->interactObj->unk11 = 0;
}

/**
 * Bubbler boss obstacle loop behaviour.
 * Representing the landmines and bubbletraps that Bubbler throws during the race.
 * When ran into by a player, they will suffer like they usually would when running into a landmine or a bubble trap.
 */
void obj_loop_fireball_octoweapon(Object *obj, s32 updateRate) {
    Object *someObj;
    f32 var_f2;
    f32 updateRateF;
    Object_Fireball_Octoweapon *weapon;
    Object_Racer *racer;
    ObjectInteraction *obj4C;
    s32 temp;
    f32 sp4C;

    someObj = (Object *) obj->unk78;
    updateRateF = updateRate;
    if (obj->behaviorId == BHV_FIREBALL_OCTOWEAPON_2 && obj->unk7C.word < 0) {
        obj->segment.trans.x_position = 0.0f;
        obj->segment.trans.y_position = 0.0f;
        obj->segment.trans.z_position = 0.0f;
        func_80011560();
        move_object(obj, someObj->segment.trans.x_position, someObj->segment.trans.y_position, someObj->segment.trans.z_position);
    } else {
        var_f2 = (someObj->segment.trans.x_position - obj->segment.trans.x_position) * 0.1f;
        if (var_f2 > 10.0f) {
            var_f2 = 10.0f;
        }
        if (var_f2 < -10.0f) {
            var_f2 = -10.0f;
        }
        obj->segment.x_velocity += (var_f2 - obj->segment.x_velocity) * 0.125f * updateRateF;
        var_f2 = (someObj->segment.trans.y_position - obj->segment.trans.y_position) * 0.1f;
        if (var_f2 > 10.0f) {
            var_f2 = 10.0f;
        }
        if (var_f2 < -10.0f) {
            var_f2 = -10.0f;
        }
        obj->segment.y_velocity += (var_f2 - obj->segment.y_velocity) * 0.125f * updateRateF;
        var_f2 = (someObj->segment.trans.z_position - obj->segment.trans.z_position) * 0.1f;
        if (var_f2 > 10.0f) {
            var_f2 = 10.0f;
        }
        if (var_f2 < -10.0f) {
            var_f2 = -10.0f;
        }
        obj->segment.z_velocity += (var_f2 - obj->segment.z_velocity) * 0.125f * updateRateF;
        if (((obj->segment.x_velocity * obj->segment.x_velocity) + (obj->segment.z_velocity * obj->segment.z_velocity)) > 0.5f * 0.5f) {
            obj->segment.trans.y_rotation = arctan2_f(obj->segment.x_velocity, obj->segment.z_velocity);
            obj->segment.trans.x_rotation -= updateRate * 0x200;
        }
        move_object(obj, obj->segment.x_velocity * updateRateF, obj->segment.y_velocity * updateRateF, obj->segment.z_velocity * updateRateF);
        if (obj->unk4A == 298) {
            if (get_wave_properties(obj->segment.trans.y_position, &sp4C, NULL)) {
                obj->segment.trans.y_position = sp4C;
            }
        }
    }
    obj->segment.animFrame += updateRate * 10;
    weapon = (Object_Fireball_Octoweapon *) obj->unk64;
    obj4C = obj->interactObj;
    if ((obj4C->obj)) { 
        if ((obj4C->distance < 60)) {
            someObj = obj4C->obj;
            if((someObj->segment.header->behaviorId == BHV_RACER)) {
                racer = (Object_Racer *) someObj->unk64;
                if (racer->playerIndex != PLAYER_COMPUTER) {
                    if (obj->behaviorId == BHV_FIREBALL_OCTOWEAPON) {
                        racer->attackType = ATTACK_EXPLOSION;
                        obj->unk7C.word = 20;
                        func_8003FC44(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 44, 17, 1.0f, 1);
                        gParticlePtrList_addObject(obj);
                    } else if (obj->unk7C.word > 0) {
                        racer->unk204 = 60;
                        obj->unk7C.word = -60;
                        obj->unk78 = (s32) someObj;
                        play_sound_global(SOUND_BUBBLE_RISE, &weapon->unk1C);
                    }
                }
            }
        }
    }
    if (obj->behaviorId == BHV_FIREBALL_OCTOWEAPON) {
        obj->unk74 = 1;
        func_800AFC3C(obj, updateRate);
        obj->unk7C.word -= updateRate;
        if (obj->unk7C.word < 0) {
            if (obj->unk4A == 298) {
                gParticlePtrList_addObject(obj);
                func_8003FC44(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 44, 17, 1.0f, 1);
            }
            obj->segment.trans.scale *= 0.9f;
            if (obj->segment.trans.scale < 0.5f){
                gParticlePtrList_addObject(obj);
            }
        }
    } else {
        if (obj->unk7C.word < 0) {
            obj->unk7C.word += updateRate;
            if (obj->unk7C.word >= 0) {
                obj->unk7C.word = 0;
            }
        } else {
            obj->unk7C.word -= updateRate;
            if (obj->unk7C.word <= 0) {
                obj->unk7C.word = 0;
            }
        }
        if (obj->unk7C.word == 0) {
            temp = weapon->unk1C;
            if (temp != 0) {
                func_8000488C(temp);
            }
            play_sound_at_position(SOUND_POP, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
            gParticlePtrList_addObject(obj);
        }
    }
}

/**
 * Laser gun init function.
 * Sets the face direction and active behaviour modes based on entry data.
 * This includes a targeting system and rate of fire.
*/
void obj_init_lasergun(Object *obj, LevelObjectEntry_Lasergun *entry) {
    Object_LaserGun *laserGun;
    obj->interactObj->unk14 = 34;
    obj->interactObj->unk11 = 0;
    laserGun = &obj->unk64->lasergun;
    laserGun->targeting = entry->targeting;
    laserGun->fireRate = entry->fireRate;
    laserGun->unk10 = entry->unkC;
    laserGun->unk11 = entry->unkD;
    laserGun->fireTimer = laserGun->fireRate;
    obj->segment.trans.y_rotation = entry->angleX << 4 << 4; // Not sure about the shift amounts here, but it
    obj->segment.trans.x_rotation = entry->angleY << 4 << 4; // just needs to be 2 left shifts that add up to 8.
}

/**
 * Laser gun loop behaviour.
 * A static mounted gun that shoots laserbeams at wherever it's facing.
 * The fire rate is adjustable per object and can be set to target racers.
*/
void obj_loop_lasergun(Object *obj, s32 updateRate) {
    Object_LaserGun *lasergun;
    Object *laserBoltObj;
    f32 distance;
    ObjectTransform trans;
    Matrix mtx;
    Object *racerObj;
    f32 diffX;
    f32 diffZ;
    f32 diffY;
    ObjectInteraction *obj4C;
    LevelObjectEntryCommon spawnObj;

    lasergun = (Object_LaserGun *) obj->unk64;
    if (lasergun->fireTimer > 0) {
        lasergun->fireTimer -= updateRate;
    } else {
        obj4C = obj->interactObj;
        if (lasergun->unk11 >= obj4C->distance) {
            if (lasergun->targeting) {
                racerObj = obj4C->obj;
                if (racerObj != NULL && racerObj->behaviorId == BHV_RACER) {
                    diffX = obj->segment.trans.x_position - racerObj->segment.trans.x_position;
                    diffY = obj->segment.trans.y_position - racerObj->segment.trans.y_position;
                    diffZ = obj->segment.trans.z_position - racerObj->segment.trans.z_position;
                    distance = ((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ));
                    if (distance > 10.0f * 10.0f) {
                        distance = sqrtf(distance);
                        diffX /= distance;
                        diffY /= distance;
                        diffZ /= distance;
                        obj->segment.trans.y_rotation = (arctan2_f(diffX, diffZ) - 0x8000) & 0xFFFF;
                        obj->segment.trans.x_rotation = arctan2_f(diffY, 1.0f) & 0xFFFF;
                    }
                }
            }
            lasergun->fireTimer = lasergun->fireRate;
            spawnObj.x = obj->segment.trans.x_position;
            spawnObj.y = obj->segment.trans.y_position;
            spawnObj.z = obj->segment.trans.z_position;
            spawnObj.size = 8;
            spawnObj.objectID = 0xC6;
            play_sound_at_position(SOUND_LASER_GUN, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
            laserBoltObj = spawn_object(&spawnObj, 1);
            if (laserBoltObj != NULL) {
                laserBoltObj->segment.unk3C_a.level_entry = NULL;
                laserBoltObj->segment.trans.y_rotation = obj->segment.trans.y_rotation;
                laserBoltObj->segment.trans.x_rotation = obj->segment.trans.x_rotation;
                laserBoltObj->unk78 = lasergun->unk10;
                laserBoltObj->unk7C.word = (s32) lasergun;
                trans.x_position = 0.0f;
                trans.y_position = 0.0f;
                trans.z_position = 0.0f;
                trans.scale = 1.0f;
                trans.y_rotation = obj->segment.trans.y_rotation;
                trans.x_rotation = obj->segment.trans.x_rotation;
                trans.z_rotation = 0;
                object_transform_to_matrix(mtx, &trans);
                diffX = 30.0f; // Need to use diffX to match.
                if (lasergun->targeting == FALSE) {
                    diffX = 45.0f;
                }
                guMtxXFMF(mtx, 0.0f, 0.0f, diffX, &laserBoltObj->segment.x_velocity, &laserBoltObj->segment.y_velocity, &laserBoltObj->segment.z_velocity);
            }
        }
    }
}

void obj_init_laserbolt(Object *obj, UNUSED LevelObjectEntry_Laserbolt *entry) {
    obj->interactObj->unk14 = 2;
    obj->interactObj->unk11 = 0;
}

typedef struct Object_7C_80034860 {
	u8 pad0[0xC];
	s16 unkC;
} Object_7C_80034860;

void obj_loop_laserbolt(Object *obj, s32 updateRate) {
	f32 updateRateF;

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
    updateRateF = updateRate;
    sp40 = obj->segment.trans.x_position + (obj->segment.x_velocity * updateRateF);
    sp44 = obj->segment.trans.y_position + (obj->segment.y_velocity * updateRateF);
    sp48 = obj->segment.trans.z_position + (obj->segment.z_velocity * updateRateF);
    sp3C = 9.0f;

    func_80031130(1, &obj->segment.trans.x_position, &sp40, -1);
    sp38 = FALSE;
    func_80031600(&obj->segment.trans.x_position, &sp40, &sp3C, &sp4E, 1, &sp38);
    if (sp38) {
        obj->segment.x_velocity = (sp40 - obj->segment.trans.x_position) / updateRateF;
        obj->segment.y_velocity = (sp44 - obj->segment.trans.y_position) / updateRateF;
        obj->segment.z_velocity = (sp48 - obj->segment.trans.z_position) / updateRateF;
    }
    move_object(obj, obj->segment.x_velocity * updateRateF, obj->segment.y_velocity * updateRateF, obj->segment.z_velocity * updateRateF);
    if (sp38) {
        func_8003FC44(obj->segment.trans.x_position, obj->segment.trans.y_position - 36.0f, obj->segment.trans.z_position, 44, 0, 0.2f, 0);
        sp4F = TRUE;
    }

    if (obj->unk78 > 0) {
        obj->unk78 -= updateRate;
    } else {
        sp4F = TRUE;
    }

    if (obj->interactObj->distance < 80) {
        obj4C_obj = (Object*)obj->interactObj->obj;
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
            func_8003FC44(obj->segment.trans.x_position, obj->segment.trans.y_position - 36.0f, obj->segment.trans.z_position, 44, 17, 0.5f, 0);
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

void obj_loop_torch_mist(Object *obj, s32 updateRate) {
    obj->segment.animFrame += obj->unk78 * updateRate;
}

void obj_init_effectbox(UNUSED Object *obj, UNUSED LevelObjectEntry_EffectBox *entry) {
}

#ifdef NON_MATCHING
// Has regalloc issues

void obj_loop_effectbox(Object *obj, UNUSED s32 updateRate) {
    Object **objList;
    Object_EffectBox *curObj64;
    s32 numberOfObjects;
    LevelObjectEntry_EffectBox *level_entry;
    s32 i;
    f32 diffX;
    f32 diffY;
    f32 diffZ;
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
        diffX = objList[i]->segment.trans.x_position - obj->segment.trans.x_position;
        diffY = objList[i]->segment.trans.y_position - obj->segment.trans.y_position;
        diffZ = objList[i]->segment.trans.z_position - obj->segment.trans.z_position;
        if ((-temp3 < diffY) && (diffY < temp3)) {
            temp5 = (diffX * temp0) + (diffZ * temp1);
            if ((-temp2 < temp5) && (temp5 < temp2)) {
                temp5 = (-diffX * temp1) + (diffZ * temp0);
                if ((-temp4 < temp5) && (temp5 < temp4)) {
                    curObj64 = &objList[i]->unk64->effect_box;
                    curObj64->unk1FE = level_entry->unkC;
                    curObj64->unk1FF = level_entry->unkD;
                    temp5 = temp3 / 2;
                    if ((temp5 < diffY) && (curObj64->unk1FE == 1)) {
                        temp5 = (1.0f - ((diffY - temp5) / temp5));
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
    obj->interactObj->unk14 = 1;
    obj->interactObj->unk11 = 2;
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
    LevelObjectEntryCommon newObject;
    LevelHeader* header;
    Object* tempObj;
    s32 dialogueID;
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
        bossFlags = settings->bosses;
        bossFlags |= 0x800;
        worldBalloons = (settings->balloonsPtr[settings->worldId] >= 8);
        if (worldBalloons) {
            worldBalloons = ((1 << (settings->worldId + 6)) & bossFlags) != 0;
        }
#ifdef UNLOCK_ALL
        worldBalloons = TRUE;
#endif
        if (obj->action == NULL && func_800C3400() == FALSE) {
            if (obj->unk5C->unk100 != NULL) {
                if (gfxData->unk4 == 0) {
                    if (worldBalloons) {
                        obj->action = 1;
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
        if (obj->action == 1) {
            func_800AB1AC(3);
            set_hud_visibility(0U);
            dialogueID = func_8009CFEC(4);
            if (dialogueID) {
                obj->action = 0;
                func_8009CF68(4);
                if (dialogueID == 1) {
                    func_8006F254();
                    obj->action = 2;
                } else {
                    set_hud_visibility(1);
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
    obj->interactObj->unk14 = 2;
    obj->interactObj->unk11 = 0;
    obj->interactObj->unk10 = 0x14;
    obj->interactObj->unk12 = 0;
}

void obj_loop_collectegg(Object *obj, s32 updateRate) {
    Object_CollectEgg *egg;
    Object *racerObj;
    Object_Racer *racer;
    f32 sp40[3];
    f32 sp3C;
    f32 updateRateF;
    s32 sp34;
    s8 sp33;

    egg = (Object_CollectEgg *) obj->unk64;
    updateRateF = updateRate;
    switch (egg->unkB) {
    case 0:
        func_80036040(obj, (Object_64 *) egg);
        break;
    case 2:
        obj->segment.trans.unk6 &= 0xBFFF;
        sp40[0] = obj->segment.trans.x_position + (obj->segment.x_velocity * updateRateF);
        sp40[1] = obj->segment.trans.y_position + (obj->segment.y_velocity * updateRateF);
        sp40[2] = obj->segment.trans.z_position + (obj->segment.z_velocity * updateRateF);
        sp3C = 9.0f;
        func_80031130(1, &obj->segment.trans.x_position, sp40, -1);
        sp34 = 0;
        sp33 = 0;
        func_80031600(&obj->segment.trans.x_position, sp40, &sp3C, &sp33, 1, &sp34);
        obj->segment.x_velocity = (sp40[0] - obj->segment.trans.x_position) / updateRateF;
        obj->segment.y_velocity = (sp40[1] - obj->segment.trans.y_position) / updateRateF;
        obj->segment.z_velocity = (sp40[2] - obj->segment.trans.z_position) / updateRateF;
        obj->segment.trans.x_position = sp40[0];
        obj->segment.trans.y_position = sp40[1];
        obj->segment.trans.z_position = sp40[2];
        obj->segment.y_velocity -= 0.5f;
        obj->segment.x_velocity *= 0.98f;
        obj->segment.z_velocity *= 0.98f;
        obj->segment.y_velocity *= 0.95;
        if (obj->segment.trans.y_position < -2000.0f || (sp34 != 0 && (sp33 < 5 || sp33 >= 10))) {
            if (egg->unk4 != NULL) {
                egg->unk4->action = 0;
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
            egg->unk4->action = 0;
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
        obj->segment.animFrame = 128;
        break;
    }
}

void obj_init_eggcreator(UNUSED Object *obj, UNUSED LevelObjectEntry_EggCreator *entry) {
}

void obj_loop_eggcreator(Object *obj, UNUSED s32 updateRate) {
    unk8003564C sp20;
    Object *someObj;

    if (obj->action == 0) {
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
    if (obj->segment.unk38.byte.unk3A >= obj->segment.header->numberOfModelIds) {
        obj->segment.unk38.byte.unk3A = 0;
    }
    obj->interactObj->unk14 = 1;
    obj->interactObj->unk11 = 2;
    obj->interactObj->unk10 = 0x14;
    obj->interactObj->unk12 = 0;
}

void obj_loop_rocketsignpost(Object *obj, UNUSED s32 updateRate) {
    Object *playerObj;
    ObjectInteraction *obj4C;

    playerObj = get_racer_object(0);
    if (playerObj != NULL) {
        obj4C = obj->interactObj;
        if (obj4C->distance < 0xC8) {
            if (playerObj == obj4C->obj) {
                // Detect if the player honks or slams into the signpost.
                if ((get_buttons_pressed_from_player(PLAYER_ONE) & Z_TRIG) || playerObj == obj->unk5C->unk100) {
                    func_8006F29C();
                }
            }
        }
    }
    obj->interactObj->distance = 0xFF;
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
    if (obj->segment.unk38.byte.unk3A >= objHeader->numberOfModelIds) {
        obj->segment.unk38.byte.unk3A = 0;
    }
    obj->interactObj->unk14 = 2;
    obj->interactObj->unk11 = 0;
    obj->interactObj->unk10 = 0x14;
    obj->interactObj->unk12 = 0;
    if (get_filtered_cheats() & CHEAT_TURN_OFF_ZIPPERS) {
        gParticlePtrList_addObject(obj);
    }
}


void obj_loop_airzippers_waterzippers(Object *obj, UNUSED s32 updateRate) {
    Object *curRacerObj;
    Object_Racer *racer;
    f32 diffX;
    f32 diffY;
    f32 diffZ;
    s32 numObjects;
    Object** racerObjs;
    s32 i;

    if (find_non_car_racers() == FALSE) {
        obj->segment.trans.unk6 |= 0x4000;
    } else {
        obj->segment.trans.unk6 &= 0xBFFF;
    }
    if ((obj->interactObj->distance < 100) && !(obj->segment.trans.unk6 & 0x4000)) {
        racerObjs = get_racer_objects(&numObjects);
        for (i = 0; i < numObjects; i++) {
            curRacerObj = racerObjs[i];
            racer = &curRacerObj->unk64->racer;
            if ((racer->unk1F5 == 0) && (racer->boostTimer < 15)) {
                diffX = curRacerObj->segment.trans.x_position - obj->segment.trans.x_position;
                diffY = curRacerObj->segment.trans.y_position - obj->segment.trans.y_position;
                diffZ = curRacerObj->segment.trans.z_position - obj->segment.trans.z_position;
                if ((s32) sqrtf((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ)) < 100) {
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
    if (arg0->segment.unk38.byte.unk3A >= arg0->segment.header->numberOfModelIds) {
        arg0->segment.unk38.byte.unk3A = 0;
    }
    arg0->unk78 = (s32)(28.0f * objScale) + 15;
    if (arg0->unk78 < 0) {
        arg0->unk78 = 0;
    }
    if (arg0->unk78 > 255) {
        arg0->unk78 = 255;
    }
    arg0->interactObj->unk14 = 2;
    arg0->interactObj->unk11 = 0;
    arg0->interactObj->unk10 = 0x14;
    arg0->interactObj->unk12 = 0;
    arg0->interactObj->unk16 = -0x64;
    arg0->interactObj->unk17 = 0x64;
    if (get_filtered_cheats() & CHEAT_TURN_OFF_ZIPPERS) {
        gParticlePtrList_addObject(arg0);
    }
}

void obj_loop_groundzipper(Object *obj, UNUSED s32 updateRate) {
    Object *curRacerObj;
    Object_Racer *racer;
    f32 diffX;
    f32 diffY;
    s32 numObjects;
    f32 diffZ;
    Object** racerObjs;
    s32 i;

    obj->segment.trans.unk6 &= 0xBFFF;
    obj->segment.trans.unk6 |= 0x1000;
    get_racer_object(0); // Unused. I guess the developers forgot to remove this?
    if ((s32) obj->interactObj->distance < obj->unk78) {
        racerObjs = get_racer_objects(&numObjects);
        for (i = 0; i < numObjects; i++) {
            curRacerObj = racerObjs[i];
            racer = &curRacerObj->unk64->racer;
            if ((racer->boostTimer < 15) && (racer->unk1E2 != 0)) {
                diffX = curRacerObj->segment.trans.x_position - obj->segment.trans.x_position;
                diffY = curRacerObj->segment.trans.y_position - obj->segment.trans.y_position;
                diffZ = curRacerObj->segment.trans.z_position - obj->segment.trans.z_position;
                if ((s32) ((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ)) < obj->unk78 * obj->unk78) {
                    if (racer->playerIndex != PLAYER_COMPUTER) {
                        play_sound_spatial(SOUND_ZIP_PAD_BOOST, curRacerObj->segment.trans.x_position, curRacerObj->segment.trans.y_position, curRacerObj->segment.trans.z_position, NULL);
                    }
                    racer->boostTimer = (45);
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

void obj_loop_unknown58(Object *obj, s32 updateRate) {
    Object *someObj;
    Object *someOtherObj;
    Object_UnkId58 *someOtherObj64;
    Object_60 *obj60;
    s8 vehicleID;

    obj->segment.unk38.byte.unk3B = 0;
    obj->segment.animFrame = 40;
    if (func_8001139C() == 0) {
        obj->unk78 += updateRate;
    }
    set_ghost_position_and_rotation(obj);
    func_800AFC3C(obj, updateRate);
    someOtherObj = get_racer_object(0);
    someOtherObj64 = &someOtherObj->unk64->unkid58;
    obj60 = obj->unk60;
    if (obj60->unk0 == 1) {
        vehicleID = someOtherObj64->vehicleID;
        if (vehicleID == VEHICLE_HOVERCRAFT || vehicleID == VEHICLE_PLANE) {
            someObj = (Object *) obj60->unk4;
            someObj->segment.trans.y_rotation = 0x4000;
            someObj->segment.unk38.byte.unk3A++;
            someObj->segment.unk38.byte.unk3A &= 1;
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

void obj_loop_characterflag(Object *obj, UNUSED s32 updateRate) {
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
    obj->interactObj->unk14 = 1;
    obj->interactObj->unk11 = 0;
    obj->interactObj->unk10 = 0x1E;
    obj->interactObj->unk12 = 0;
    temp = &obj->unk64->tt;
    temp->unkD = 0xFF;
    temp->unk0 = 0.0f;
    gTTSoundMask = 0;
}

/**
 * Hub world T.T loop behaviour.
 * Handles all the behaviour for the T.T NPC found in the overworld.
 * This uses a state machine to handle whether to wander around, approach the player and engage dialogue.
*/
void obj_loop_stopwatchman(Object *obj, s32 updateRate) {
    f32 updateRateF;
    f32 diffX;
    f32 diffZ;
    f32 distance;
    f32 tempPosY;
    Object_NPC *tt;
    Object *racerObj;
    s32 angleDiff;
    s32 index;
    Object_Racer *racer;
    LevelHeader *header;
    struct TempStruct8 **sp48;

    tempPosY = obj->segment.trans.y_position;
    updateRateF = updateRate;
    tt = (Object_NPC *) obj->unk64;
    if (obj->segment.animFrame == 0) {
        if (tt->unk4 > 1.0f) {
            tt->unk4 = 0.0f;
        }
    }
    header = get_current_level_header();
    distance = 0.0f;
    obj->segment.x_velocity = 0.0f;
    obj->segment.z_velocity = 0.0f;
    racerObj = get_racer_object(PLAYER_ONE);
    if (racerObj != NULL) {
        racer = (Object_Racer *) racerObj->unk64;
        diffX = ((racerObj->segment.trans.x_position - (racer->ox1 * 50.0f)) - (racer->ox3 * 5.0f)) - obj->segment.trans.x_position;
        diffZ = ((racerObj->segment.trans.z_position - (racer->oz1 * 50.0f)) - (racer->oz3 * 5.0f)) - obj->segment.trans.z_position;
        distance = sqrtf((diffX * diffX) + (diffZ * diffZ));
        angleDiff = arctan2_f(racerObj->segment.trans.x_position - obj->segment.trans.x_position, racerObj->segment.trans.z_position - obj->segment.trans.z_position) - (racerObj->segment.trans.y_rotation & 0xFFFF);
        if (angleDiff > 0x8000) {
            angleDiff = -0xFFFF;
        }
        if (angleDiff < -0x8000) {
            angleDiff = 0xFFFF;
        }
        if (racer->unk108 != NULL) {
            obj->action = TT_MODE_ROAM;
            obj->unk7C.word = 1;
        }
    }
    index = get_buttons_pressed_from_player(PLAYER_ONE);
    if (obj->action == TT_MODE_ROAM && distance < 300.0f && obj->unk7C.word == 0) {
        if (angleDiff > -0x2000 && angleDiff < 0x2000) {
            if ((obj->interactObj->unk14 & 8 && racerObj == obj->interactObj->obj) || index & Z_TRIG) {
                if (index & Z_TRIG) {
                    play_char_horn_sound(racerObj, racer);
                }
                obj->action = TT_MODE_APPROACH_PLAYER;
                func_80030750(0, &tt->unk20, &tt->unk22, &tt->unk11, &tt->unk12, &tt->unk13);
                func_80030DE0(0, 0x80, 0x80, 0xFF, 0x384, 0x3E6, 0xF0);
                func_800012E8();
                play_music(SEQUENCE_TTS_THEME);
                if (racerObj != NULL) {
                    func_80006AC8(racerObj);
                    racer->unk118 = 0;
                }
            }
        }
    }
    if (obj->action != TT_MODE_ROAM) {
        func_8005A3B0();
        func_800AB194(3);
    }
    if (obj->action >= TT_MODE_TURN_TOWARDS_PLAYER) {
        index = func_8009CFEC(2U);
    } else {
        func_8009CF68(2);
        index = 0;
    }
    switch (obj->action) {
    case TT_MODE_APPROACH_PLAYER:
        obj->segment.unk38.byte.unk3B = 0;
        tt->unkD = 255;
        if (distance < 100.0f) {
            func_8005A3C0();
        }
        if (distance > 10.0f) {
            angleDiff = (arctan2_f(diffX / distance, diffZ / distance) - (obj->segment.trans.y_rotation & 0xFFFF)) + 0x8000;
            if (angleDiff > 0x8000) {
                angleDiff -= 0xFFFF;
            }
            if (angleDiff < -0x8000) {
                angleDiff += 0xFFFF;
            }
            if (angleDiff > 0) {
                if (angleDiff < 0x10) {
                    angleDiff = 0x10;
                }
            }
            obj->segment.trans.y_rotation += angleDiff >> 4;
            distance = -2.0f;
            if (angleDiff > 0x800 || angleDiff < -0x800) {
                distance = -0.5f;
            }
            tt->unk14 += (distance - tt->unk14) * 0.125f;
            obj->segment.x_velocity = sins_f(obj->segment.trans.y_rotation) * tt->unk14;
            obj->segment.z_velocity = coss_f(obj->segment.trans.y_rotation) * tt->unk14;
            tt->unk4 -= (tt->unk14 * 2 * updateRateF);
        } else {
            obj->action = TT_MODE_TURN_TOWARDS_PLAYER;
        }
        move_object(obj, obj->segment.x_velocity * updateRateF, obj->segment.y_velocity * updateRateF, obj->segment.z_velocity * updateRateF);
        func_8006F388(1);
        break;
    case TT_MODE_TURN_TOWARDS_PLAYER:
        func_8005A3C0();
        obj->segment.unk38.byte.unk3B = 0;
        tt->unk4 += 3.0f * updateRateF;
        angleDiff = (racerObj->segment.trans.y_rotation - (obj->segment.trans.y_rotation & 0xFFFF)) + 0x8000;
        if (angleDiff > 0x8000) {
            angleDiff -= 0xFFFF;
        }
        if (angleDiff < -0x8000) {
            angleDiff += 0xFFFF;
        }
        if (angleDiff > 0) {
            if (angleDiff < 0x10) {
                angleDiff = 0x10;
            }
        }
        obj->segment.trans.y_rotation += (angleDiff >> 4);
        obj->segment.x_velocity = diffX * 0.05f;
        obj->segment.z_velocity = diffZ * 0.05f;
        if (angleDiff < 0x500) {
            if (angleDiff >= -0x4FF) {
                obj->action = TT_MODE_DIALOGUE;
                play_tt_voice_clip(SOUND_VOICE_TT_INTRO, 1); // Hi there, I'm T.T!
            }
        }
        move_object(obj, obj->segment.x_velocity * updateRateF, obj->segment.y_velocity * updateRateF, obj->segment.z_velocity * updateRateF);
        break;
    case TT_MODE_DIALOGUE:
        obj->segment.x_velocity = diffX * 0.05f;
        obj->segment.z_velocity = diffZ * 0.05f;
        obj->segment.unk38.byte.unk3B = 1;
        tt->unk4 += 1.0f * updateRateF;
        func_8005A3C0();
        if (index == 3) {
            obj->action = TT_MODE_DIALOGUE_END;
            if (is_time_trial_enabled()) {
                play_tt_voice_clip(SOUND_VOICE_TT_SEE_YOU, 1);
            } else {
                play_tt_voice_clip(SOUND_VOICE_TT_OK, 1);
            }
            func_80030DE0(0, tt->unk11, tt->unk12, tt->unk13, tt->unk20, tt->unk22, 0xB4);
            play_music(header->music);
            func_80001074(header->instruments);
            racer->unk118 = func_80004B40(racer->characterId, racer->vehicleID);
        }
        obj->unk7C.word = 0xB4;
        move_object(obj, obj->segment.x_velocity * updateRateF, obj->segment.y_velocity * updateRateF, obj->segment.z_velocity * updateRateF);
        break;
    case TT_MODE_DIALOGUE_END:
        tt->unk4 += 1.0f * updateRateF;
        func_8005A3C0();
        if (obj->unk7C.word < 140) {
            obj->unk7C.word += 60;
            obj->action = TT_MODE_ROAM;
            obj->segment.unk38.byte.unk3B = 0;
        }
        break;
    default:
        obj->segment.unk38.byte.unk3B = 0;
        tt->unk14 = 0.0f;
        if (tt->unkD == 0xFF) {
            tt->unkD = func_8001C524(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 0);
            if (tt->unkD != 0xFF) {
                tt->unkE = func_8001CC48(tt->unkD, -1, 0);
                tt->unkF = func_8001CC48(tt->unkE, tt->unkD, 0);
                tt->unk10 = func_8001CC48(tt->unkF, tt->unkE, 0);
                tt->unkC = tt->unkD;
            }
        } else {
            diffZ =  func_8001C6C4((Object_64 *) tt, obj, updateRateF, 1.0f, 0);
            tt->unk4 += diffZ * 1.5f;
        }
        break;
    }
    obj->segment.trans.y_position = tempPosY;
    index = func_8002B0F4(obj->segment.unk2C.half.lower, obj->segment.trans.x_position, obj->segment.trans.z_position, (struct TempStruct8 **) &sp48);
     if(index != 0) {
        index--;
        while(index >= 0) {
            if ((sp48[index]->unk10 != 11) && (sp48[index]->unk10 != 14) && (sp48[index]->unk8 > 0.0f)) {
                obj->segment.trans.y_position = sp48[index]->unk0;
            }
            index--;
        }
    }
    obj->segment.trans.x_rotation = 0;
    obj->segment.trans.z_rotation = 0;
    if (obj->action != TT_MODE_ROAM) {
        D_8011D4D0 = obj->segment.trans.y_position;
    }
    obj->segment.animFrame = 1.0f * tt->unk4;
    func_80061C0C(obj);
    if (obj->unk7C.word > 0) {
        obj->unk7C.word -= updateRate;
    } else {
        obj->unk7C.word = 0;
    }
}


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

void obj_loop_lavaspurt(Object *obj, s32 updateRate) {
    if (obj->unk78 > 0) {
        obj->unk78 -= updateRate;
        obj->segment.trans.unk6 |= 0x4000;
    } else {
        obj->segment.trans.unk6 &= ~0x4000;
        obj->segment.animFrame += updateRate * 4;
        if (obj->segment.animFrame > 255) {
            obj->segment.animFrame = 0;
            obj->unk78 = get_random_number_from_range(0, 30) + obj->unk7C.word;
        }
    }
}

void obj_init_posarrow(Object *obj, UNUSED LevelObjectEntry_PosArrow *entry) {
    obj->segment.trans.unk6 |= 0x4000;
}

void obj_loop_posarrow(Object *obj, UNUSED s32 updateRate) {
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
        obj->segment.animFrame = obj->unk78 * 127;
    }
}

/* Offical name: animInit */
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

void obj_loop_animator(Object *obj, s32 updateRate) {
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

    temp = obj64->xSpeedFactor * updateRate;
    obj64->xSpeed += temp << 4;
    sp20 = obj64->xSpeed >> 4;
    obj64->xSpeed &= 0xF;

    temp2 = obj64->ySpeedFactor * updateRate;
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
    obj->action = arg2;
    if (arg2 != 0 && (get_buttons_pressed_from_player(PLAYER_ONE) & R_CBUTTONS)) {
        obj->action = 2;
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


void obj_loop_animobject(Object *obj, s32 updateRate) {
    func_8001F460(obj, updateRate, obj);
}

void obj_loop_dooropener(Object *obj, s32 updateRate) {
    s32 phi_a0;
    unk80037D08_arg0_64 *sp18;

    sp18 = (unk80037D08_arg0_64 *) obj->unk64;
    phi_a0 = 1 - func_8001F460(obj, updateRate, obj);
    if (sp18->unk2A > 0) {
        phi_a0 = 0;
    }
    func_800235D0(phi_a0);
}

void obj_init_overridepos(UNUSED Object *obj, UNUSED LevelObjectEntry_OverridePos *entry) {
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
                                play_sound_at_position(SOUND_LASER_GUN, wizShipObj->segment.trans.x_position, wizShipObj->segment.trans.y_position, wizShipObj->segment.trans.z_position, 4, NULL);
                            }
                        }
                    }
                }
            }
        }
    }
}

void obj_loop_vehicleanim(Object *obj, s32 updateRate) {
    Object_60_800380F8 *obj60;
    Object *someObj;

    func_8001F460(obj, updateRate, obj);
    obj60 = (Object_60_800380F8 *) obj->unk60;
    if (obj60 != NULL) {
        if (obj60->unk0 > 0) {
            someObj = obj60->unk0 == 3 ? obj60->unkC : obj60->unk4;
            someObj->segment.trans.y_rotation = 0x4000;
            someObj->segment.unk38.byte.unk3A++;
            if (someObj->segment.unk38.byte.unk3A == someObj->segment.header->numberOfModelIds) {
                someObj->segment.unk38.byte.unk3A = 0;
            }
        }
    }
}

void obj_init_hittester(Object *obj, UNUSED LevelObjectEntry_HitTester *entry) {
    obj->interactObj->unk14 = 0x81;
    obj->interactObj->unk11 = 2;
    obj->interactObj->unk10 = 0x14;
    obj->interactObj->unk12 = 0;
}

void obj_loop_hittester(Object *obj, s32 updateRate) {
    func_8001F460(obj, updateRate, obj);
}

void obj_init_dynamic_lighting_object(Object *obj, UNUSED LevelObjectEntry_DynamicLightingObject *entry) {
    obj->interactObj->unk14 = 1;
    obj->interactObj->unk11 = 2;
    obj->interactObj->unk10 = 0x14;
    obj->interactObj->unk12 = 0;
}

void obj_init_unknown96(Object *obj, UNUSED LevelObjectEntry_Unknown96 *entry) {
    obj->interactObj->unk14 = 0x81;
    obj->interactObj->unk11 = 2;
    obj->interactObj->unk10 = 0x14;
    obj->interactObj->unk12 = 0;
}

void obj_init_snowball(Object *obj, UNUSED LevelObjectEntry_Snowball *entry) {
    obj->interactObj->unk14 = 1;
    obj->interactObj->unk11 = 2;
    obj->interactObj->unk10 = 0x14;
    obj->interactObj->unk12 = 0;
}

void obj_loop_snowball(Object *obj, s32 updateRate) {
    Object_Snowball *obj64 = &obj->unk64->snowball;
    if (obj64->unk24 == 0) {
        if (obj64->unk38 != 0) {
            obj64->unk24 = (s16)(obj64->unk38 & 0xFF);
        }
    }
    if (obj64->unk24 != 0) {
        if (obj64->soundMask == 0) {
            play_sound_at_position(obj64->unk24, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 1, (s32 *) &obj64->soundMask);
        } else {
            update_spatial_audio_position(obj64->soundMask, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
        }
    }
    func_8001F460(obj, updateRate, obj);
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_char_select.s")

void obj_loop_animcamera(Object *obj, s32 updateRate) {
    s32 temp_v0;
    s32 phi_v1;
    Object_AnimCamera *obj64;

    temp_v0 = func_8001F460(obj, updateRate, obj);
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

/**
 * Racer cutscene target loop behaviour.
 * Exists as a target point for racer objects to automatically move towards, for cutscenes.
 */
void obj_loop_animcar(Object *obj, s32 updateRate) {
    Object *racerObj;
    s32 racerID;
    racerID = obj->action;
    racerObj = NULL;
    if (racerID != 0) {
        racerObj = get_racer_object(racerID - 1);
    }
    obj->unk7C.word = func_8001F460(obj, updateRate, obj);
    obj->segment.trans.unk6 |= 0x4000;
    if (obj->unk7C.word == 0 && racerObj != NULL) {
        Object_Racer *racer = &racerObj->unk64->racer;
        racer->approachTarget = obj;
    }
}

void obj_init_infopoint(Object *obj, LevelObjectEntry_InfoPoint *entry) {
    if (entry->unk8[1] != 0) {
        obj->interactObj->unk14 = 0x21;
    } else {
        obj->interactObj->unk14 = 0x22;
    }
    obj->interactObj->unk11 = 0;
    obj->interactObj->unk10 = 0xF;
    obj->interactObj->unk12 = 0;
    obj->unk78 = (entry->unk8[2] << 16) | entry->unk8[0]; // Not sure about the values here.
    obj->unk7C.word = entry->unk8[1];
    obj->segment.trans.y_rotation = entry->unkB << 10; // Not sure about the values here.
}

void obj_loop_infopoint(Object *obj, UNUSED s32 updateRate) {
    s16 player;
    ObjectInteraction *obj4C;
    Object *playerObj;

    if (obj->unk7C.word == 0) {
        obj->segment.trans.unk6 |= 0x4000;
    } else {
        obj->segment.trans.unk6 &= ~0x4000;
    }

    obj4C = obj->interactObj;
    if (obj4C->distance < ((obj->unk78 >> 16) & 0xFF)) {
        playerObj = obj4C->obj;
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

void obj_loop_smoke(Object *obj, s32 updateRate) {
    f32 updateRateF = updateRate;
    obj->segment.trans.x_position += obj->segment.x_velocity * updateRateF;
    obj->segment.animFrame += updateRate * 16;
    obj->segment.trans.y_position += obj->segment.y_velocity * updateRateF;
    obj->segment.trans.z_position += obj->segment.z_velocity * updateRateF;
    if (obj->segment.animFrame > 255) {
        gParticlePtrList_addObject(obj);
        obj->segment.animFrame = 255;
    }
}

void obj_init_unknown25(UNUSED Object *obj, UNUSED LevelObjectEntry_Unknown25 *entry) {
}

void obj_loop_unknown25(Object *obj, s32 updateRate) {
    obj->segment.animFrame += updateRate * 8;
    if (obj->segment.animFrame > 255) {
        gParticlePtrList_addObject(obj);
        obj->segment.animFrame = 255;
    }
}

void obj_init_wardensmoke(UNUSED Object *obj, UNUSED LevelObjectEntry_WardenSmoke *entry) {
}

void obj_loop_wardensmoke(Object *obj, s32 updateRate) {
    f32 updateRateF;

    updateRateF = (f32) updateRate;
    obj->segment.animFrame += updateRate * 4;
    obj->segment.trans.y_position += updateRateF * 0.25f;
    if (obj->segment.animFrame > 255) {
        gParticlePtrList_addObject(obj);
        obj->segment.animFrame = 255;
    }
}

void obj_init_bombexplosion(Object *obj, LevelObjectEntry_BombExplosion *entry) {
    LevelObjectEntry_BombExplosion *entry2;
    obj->segment.animFrame = 0;
    obj->segment.trans.scale = 0.5f;
    obj->segment.unk38.byte.unk3A = get_random_number_from_range(0, obj->segment.header->numberOfModelIds - 1);
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
    obj->interactObj->unk14 = 2;
    obj->interactObj->unk11 = 0;
    obj->interactObj->unk10 = 0xF;
    obj->interactObj->unk12 = 0;
    if (get_settings()->cutsceneFlags & CUTSCENE_LIGHTHOUSE_ROCKET) {
        obj->action = 1;
    }
}

void obj_loop_teleport(Object *obj, UNUSED s32 updateRate) {
    if (obj->action != 0) {
        LevelObjectEntry_Teleport *level_entry = &obj->segment.unk3C_a.level_entry->teleport;
        if (obj->interactObj->distance < 0x78) {
            func_8006F338(level_entry->unk8);
            obj->action = 0;
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
    obj->interactObj->unk14 = 2;
    obj->interactObj->unk11 = 0;
    obj->interactObj->unk10 = entry->unk10;
    obj->interactObj->unk12 = 0;
}

void obj_loop_exit(Object *obj, UNUSED s32 updateRate) {
    Object *racerObj;
    Object_Racer *racer;
    s32 numberOfRacers;
    f32 diffX;
    f32 diffZ;
    f32 dist;
    f32 diffY;
    Object_Exit *obj64;
    s32 enableWarp;
    Object** racerObjects;
    s32 i;
    f32 temp;

    obj64 = &obj->unk64->exit;
    enableWarp = TRUE;
#ifndef UNLOCK_ALL
    if ((obj64->unk14 == 0) && (settings->balloonsPtr[settings->worldId] == 8)) {
        enableWarp = FALSE;
    }
    if ((obj64->unk14 == 1) && (settings->balloonsPtr[settings->worldId] < 8)) {
        enableWarp = FALSE;
    }
#else
    enableWarp = TRUE;
#endif
    if (enableWarp) {
        if (obj->interactObj->distance < obj64->unk10) {
            dist = obj64->unk10;
            racerObjects = get_racer_objects(&numberOfRacers);
            for (i = 0; i < numberOfRacers; i++) {
                racerObj = racerObjects[i];
                racer = &racerObj->unk64->racer;
                if ((racer->playerIndex != -1) && (racer->unk108 == 0)) {
                    diffX = racerObj->segment.trans.x_position - obj->segment.trans.x_position;
                    diffY = racerObj->segment.trans.y_position - obj->segment.trans.y_position;
                    diffZ = racerObj->segment.trans.z_position - obj->segment.trans.z_position;
                    if ((((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ)) < dist * dist)) {
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
    obj->action = entry->unk8;
    func_80011390();
}

void obj_loop_cameracontrol(UNUSED Object *obj, UNUSED s32 updateRate) {
}

void obj_init_setuppoint(Object *obj, LevelObjectEntry_SetupPoint *entry) {
    obj->action = entry->unk8;
    obj->unk7C.word = entry->unk9;
    obj->segment.trans.y_rotation = entry->unkA << 6 << 4; // Not sure about the values here.
}

void obj_loop_setuppoint(UNUSED Object *obj, UNUSED s32 updateRate) {
}

void obj_init_dino_whale(Object *obj, UNUSED LevelObjectEntry_Dino_Whale *entry) {
    obj->interactObj->unk14 = 1;
    obj->interactObj->unk11 = 3;
    obj->interactObj->unk10 = 0x14;
    obj->interactObj->unk12 = 0;
}

void obj_loop_dino_whale(Object *obj, s32 updateRate) {
    s32 sp2C;

    if (obj->unk78 > 0) {
        obj->unk78 -= updateRate;
        updateRate *= 2;
    } else {
        obj->unk78 = 0;
    }
    sp2C = obj->segment.animFrame;
    func_8001F460(obj, updateRate, obj);
    func_800113CC(obj, 0, sp2C, 0xAC, 0xAD);
    if (obj->interactObj->distance < 0xFF) {
        if (obj->unk78 == 0) {
            obj->unk78 = 0x3C;
            play_sound_at_position(SOUND_VOICE_BRONTO_ROAR, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
        }
    }
}

void obj_init_parkwarden(Object *obj, UNUSED LevelObjectEntry_Parkwarden *entry) {
    Object_NPC *temp;
    obj->interactObj->unk14 = (u16)1;
    obj->interactObj->unk11 = (u8)0;
    obj->interactObj->unk10 = (u8)0x1E;
    obj->interactObj->unk12 = (u8)0;
    temp = &obj->unk64->npc;
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

/**
 * Hub world Taj loop behaviour.
 * Handles all the behaviour for the Taj NPC found in the overworld.
 * This uses a state machine to handle whether to wander around, approach the player, change their vehicle and teleport away.
*/
void obj_loop_parkwarden(Object *obj, s32 updateRate) {
    f32 updateRateF;
    f32 xPosDiff;
    f32 updateRateF2;
    f32 zPosDiff;
    f32 distance;
    f32 sp98_yPos;
    struct TempStruct8 **sp94;
    Object *racerObj;
    s32 sp3C;
    Object *temp_v0_12;
    s32 var_a2;
    Object **racerObjs;
    s32 var_a2_2;
    s32 numRacers;
    Object_NPC *taj;
    Object_64 *racer64;
    u32 buttonsPressed;
    s8 sp6B;
    LevelHeader *levelHeader;
    ObjectSegment *temp_v0_22;
    f32 var_f2;
    s32 arctan;
    s32 temp;

    sp6B = 0;
    sp98_yPos = obj->segment.trans.y_position;

    updateRateF2 = updateRate;
    updateRateF = updateRateF2;
    taj = (Object_NPC *) obj->unk64;
    levelHeader = get_current_level_header();
    obj->unk74 = 0;
    if (obj->segment.animFrame == 0 && taj->unk4 > 1.0f) {
        taj->unk4 = 0.0f;
    }
    distance = 0.0f;
    obj->segment.x_velocity = 0.0f;
    obj->segment.z_velocity = 0.0f;
    racerObj = get_racer_object(PLAYER_ONE);
    if (racerObj != NULL) {
        racer64 = racerObj->unk64;
        xPosDiff = (racerObj->segment.trans.x_position - (racer64->racer.ox1 * 50.0f)) - obj->segment.trans.x_position;
        zPosDiff = (racerObj->segment.trans.z_position - (racer64->racer.oz1 * 50.0f)) - obj->segment.trans.z_position;
        distance = sqrtf((xPosDiff * xPosDiff) + (zPosDiff * zPosDiff));
    }
    buttonsPressed = get_buttons_pressed_from_player(PLAYER_ONE);
    var_a2 = FALSE;
    if (
        (obj->action == NULL) &&
        (distance < 300.0f) &&
        (
            ((obj->interactObj->unk14 & 8) && (racerObj == obj->interactObj->obj)) ||
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
        var_a2 = FALSE;
        if (arctan > -0x2000 && arctan < 0x2000) {
            var_a2 = TRUE;
        }
    }
    obj->interactObj->unk14 = 1;
    if ((func_80052188() || (var_a2)) && ((obj->action == 0 || obj->action == 31))) {
        func_800012E8();
        set_music_player_voice_limit(24);
        play_music(SEQUENCE_ENTRANCED);
        if (racerObj != NULL) {
            func_80006AC8(racerObj);
            racer64->racer.unk118 = 0;
        }
        func_80008140();
        arctan = arctan2_f(
            racerObj->segment.trans.x_position - obj->segment.trans.x_position,
            racerObj->segment.trans.z_position - obj->segment.trans.z_position
        );
        arctan -= (racerObj->segment.trans.y_rotation & 0xFFFF);
        if (var_a2) {
            obj->action = 1;
        } else {
            obj->action = 10;
            sp6B = 1;
        }
        func_80030750(0, &taj->unk20, &taj->unk22, &taj->unk11, &taj->unk12, &taj->unk13);
        func_80030DE0(0, 0xFF, 0, 0x78, 0x3C0, 0x44C, 0xF0);
        taj->unk4 = 0.0f;
    }

    if (!(obj->action == TAJ_MODE_ROAM || obj->action == TAJ_MODE_RACE || obj->action == TAJ_MODE_TELEPORT_AWAY_BEGIN || obj->action == TAJ_MODE_TELEPORT_AWAY_END)) {
            func_8005A3B0();
            func_800AB194(3);
    }

    switch (obj->action) {
        case TAJ_MODE_GREET_PLAYER:
        case TAJ_MODE_DIALOGUE:
        case TAJ_MODE_TRANSFORM_BEGIN:
        case TAJ_MODE_TRANSFORM_END:
            var_a2_2 = func_8009CFEC(0);
            break;
        default:
            func_8009CF68(0);
            var_a2_2 = 0;
            break;
    }

    switch (obj->action) {
        case TAJ_MODE_APPROACH_PLAYER:
        case TAJ_MODE_TURN_TOWARDS_PLAYER:
        case TAJ_MODE_GREET_PLAYER:
        case TAJ_MODE_DIALOGUE:
        case TAJ_MODE_END_DIALOGUE:
        case TAJ_MODE_TELEPORT_TO_PLAYER_BEGIN:
        case TAJ_MODE_TELEPORT_TO_PLAYER_END:
        case TAJ_MODE_SET_CHALLENGE:
        case TAJ_MODE_TELEPORT_AWAY_BEGIN:
        case TAJ_MODE_TELEPORT_AWAY_END:
            func_8006F388(1);
            break;
    }

    if (obj->action != TAJ_MODE_ROAM && var_a2_2 != 0 && obj->action < 4) {
        obj->action = TAJ_MODE_DIALOGUE;
    }
    switch (obj->action) {
    case TAJ_MODE_APPROACH_PLAYER:
        obj->segment.unk38.byte.unk3B = 0;
        taj->unkD = 0xFF;
        if (distance < 100.0f) {
            func_8005A3C0();
        }
        if (distance > 10.0f) {
            arctan = (arctan2_f(xPosDiff / distance, zPosDiff / distance) - (obj->segment.trans.y_rotation & 0xFFFF)) + 0x8000;
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
            taj->unk14 += (var_f2 - taj->unk14) * 0.125f;
            obj->segment.x_velocity = sins_f(obj->segment.trans.y_rotation) * taj->unk14;
            obj->segment.z_velocity = coss_f(obj->segment.trans.y_rotation) * taj->unk14;
            taj->unk4 -= taj->unk14 * 2 * updateRateF;
        } else {
            obj->action = TAJ_MODE_TURN_TOWARDS_PLAYER;
        }
        move_object(obj, obj->segment.x_velocity * updateRateF, obj->segment.y_velocity * updateRateF, obj->segment.z_velocity * updateRateF);
        break;
    case TAJ_MODE_TURN_TOWARDS_PLAYER:
        func_8005A3C0();
        obj->segment.unk38.byte.unk3B = 0;
        taj->unk4 += updateRateF * 2.0f;
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
        if (arctan < 0x400 && arctan > -0x400 && distance < 2.0f) {
            obj->action = TAJ_MODE_GREET_PLAYER;
            taj->unk4 = 0;
            play_taj_voice_clip(D_8011D4E2, 1);
            D_8011D4E2 = SOUND_VOICE_TAJ_HELLO;
        }
        obj->segment.x_velocity = xPosDiff * 0.125f;
        obj->segment.y_velocity = 0;
        obj->segment.z_velocity = zPosDiff * 0.125f;
        move_object(obj, obj->segment.x_velocity * updateRateF, obj->segment.y_velocity * updateRateF, obj->segment.z_velocity * updateRateF);
        break;
    case TAJ_MODE_GREET_PLAYER:
        obj->segment.unk38.byte.unk3B = 1;
        taj->unk14 = 0.0f;
        taj->unk4 += updateRateF * 1.0f;
        if (taj->unk4 > 77.0f) {
            taj->unk4 = 77.0f;
            taj->unk18 = -1.0f;
            obj->action = TAJ_MODE_DIALOGUE;
        }
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
        obj->segment.trans.y_rotation = obj->segment.trans.y_rotation + (arctan >> 4);
        func_8005A3C0();
        break;
    case TAJ_MODE_DIALOGUE:
        obj->segment.unk38.byte.unk3B = 4;
        taj->unk4 += updateRateF * 1.0f;
        func_8005A3C0();
        if (var_a2_2 == 3 || var_a2_2 == 4) {
            obj->action = (var_a2_2 == 4) ? TAJ_MODE_END_DIALOGUE_UNUSED : TAJ_MODE_END_DIALOGUE;
            taj->unk4 = 0.1f;
            obj->segment.unk38.byte.unk3B = 2;
            taj->unk1C = 0;
            play_taj_voice_clip(SOUND_VOICE_TAJ_BYE, 1);
            func_80030DE0(0, taj->unk11, taj->unk12, taj->unk13, taj->unk20, taj->unk22, 0xB4);
            set_music_player_voice_limit(levelHeader->voiceLimit);
            play_music(levelHeader->music);
            func_80001074(levelHeader->instruments);
            func_80008168();
        }
        if (var_a2_2 & 0x80) {
            D_8011D4E0 = var_a2_2 & 0x7F;
            if (D_8011D4E0 != racer64->racer.vehicleID) {
                obj->action = TAJ_MODE_TRANSFORM_BEGIN;
                taj->unk4 = 0;
                // Voice clips: Abrakadabra, Alakazam, Alakazoom?
                play_taj_voice_clip((racer64->racer.vehicleID + SOUND_VOICE_TAJ_ABRAKADABRA), 1);
            } else {
                set_menu_id_if_option_equal(0x62, 2);
            }
        }
        if (var_a2_2 & 0x40) {
            D_8011D4E0 = var_a2_2 & 0xF;
            if (D_8011D4E0 != racer64->racer.vehicleID) {
                D_8011D4E0 |= 0x80;
                obj->action = TAJ_MODE_TRANSFORM_BEGIN;
                taj->unk4 = 0.0f;
                // Voice clips: Abrakadabra, Alakazam, Alakazoom?
                play_taj_voice_clip((racer64->racer.vehicleID + SOUND_VOICE_TAJ_ABRAKADABRA), 1);
            } else {
                obj->action = TAJ_MODE_SET_CHALLENGE;
                transition_begin(&D_800DC978);
                sp6B = 1;
                play_taj_voice_clip(SOUND_WHOOSH4, 1);
                taj->unk4 = 0.0f;
            }
        }
        break;
    case TAJ_MODE_TRANSFORM_BEGIN:
        obj->segment.unk38.byte.unk3B = 5;
        func_8005A3C0();
        taj->unk4 += updateRateF * 2.0f;
        if (taj->unk4 > 25.0f) {
            obj->unk74 = 11;
        }
        if (taj->unk4 > 50.0f) {
            obj->unk74 = 0;
        }
        if (taj->unk4 > 60.0f) {
            taj->unk4 = 60.0f;
            if (racer64->racer.transparency > (updateRate * 16)) {
                racer64->racer.transparency -= (updateRate * 16);
            } else {
                racer64->racer.transparency = 0;
                func_8000E1EC(racerObj, D_8011D4E0 & 0xF);
                obj->action = TAJ_MODE_TRANSFORM_END;
                play_sound_global(SOUND_CYMBAL, NULL);
                transition_begin(&D_800DC970);
            }
        }
        break;
    case TAJ_MODE_TRANSFORM_END:
        func_8005A3C0();
        if (racerObj != NULL) {
            if (taj->unk4 != 0.0f) {
                taj->unk4 += 8.0f;
            }
            var_a2 = updateRate;
            if (var_a2 > 4) {
                var_a2 = 4;
            }
            var_a2 <<= 5;
            if (racer64->racer.transparency < (255 - (var_a2))) {
                racer64->racer.transparency += var_a2;
            } else {
                racer64->racer.transparency = 255;
                if (taj->unk4 == 0.0f) {
                    if (D_8011D4E0 & 0x80) {
                        transition_begin(&D_800DC978);
                        sp6B = 1;
                        obj->action = TAJ_MODE_SET_CHALLENGE;
                        play_sound_global(SOUND_WHOOSH4, NULL);
                        taj->unk4 = 0.0f;
                    } else {
                        obj->action = TAJ_MODE_DIALOGUE;
                        set_menu_id_if_option_equal(0x62, 2);
                    }
                }
            }
        }
        break;
    case TAJ_MODE_END_DIALOGUE:
    case TAJ_MODE_END_DIALOGUE_UNUSED:
        if (taj->unk4 != 0.0f) {
            taj->unk4 = taj->unk4 + (0.5f * updateRateF);
        }
        if (taj->unk4 == 0) {
            sp6B = 1;
            if (obj->action == TAJ_MODE_END_DIALOGUE_UNUSED) {
                func_80022CFC(
                    obj->segment.unk2C.half.lower,
                    obj->segment.trans.x_position - (racer64->racer.ox1 * 50.0f),
                    obj->segment.trans.y_position,
                    obj->segment.trans.z_position - (racer64->racer.oz1 * 50.0f)
                );
            }
            obj->action = TAJ_MODE_TELEPORT_AWAY_BEGIN;
            play_sound_global(SOUND_WHOOSH4, NULL);
            racer64->racer.unk118 = func_80004B40(racer64->racer.characterId, racer64->racer.vehicleID);
        }
        break;
    case TAJ_MODE_TELEPORT_TO_PLAYER_BEGIN:
        obj->segment.unk38.byte.unk3B = 3;
        taj->unkD = 0xFF;
        taj->unk14 = 0.0f;
        taj->unk4 +=  updateRateF * 2.0f;
        if (taj->unk4 > 79.0f) {
            taj->unk4 = 79.0f;
        }

        var_a2 = updateRate * 8;
        if (taj->unk4 < 20.0f) {
            var_a2 = 0;
        }
        if (obj->segment.unk38.byte.unk39 > var_a2) {
            obj->segment.unk38.byte.unk39 -= var_a2;
        } else {
            play_sound_global(SOUND_WHOOSH4, NULL);
            sp6B = 1;
            obj->segment.unk38.byte.unk39 = 0;
            obj->action = TAJ_MODE_TELEPORT_TO_PLAYER_END;
            obj->segment.trans.x_position = racerObj->segment.trans.x_position - (racer64->racer.ox1 * 150.0f);
            obj->segment.trans.z_position = racerObj->segment.trans.z_position - (racer64->racer.oz1 * 150.0f);
            obj->segment.unk2C.half.lower = get_level_segment_index_from_position(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
            obj->segment.trans.y_rotation = racerObj->segment.trans.y_rotation + 0x8000;
        }
        break;
    case TAJ_MODE_TELEPORT_TO_PLAYER_END:
        obj->segment.unk38.byte.unk3B = 3;
        taj->unk4 -= updateRateF * 2.0f;
        if (taj->unk4 < 0.0f) {
            taj->unk4 = 0.0f;
        }
        var_a2 = updateRate * 4;
        if (obj->segment.unk38.byte.unk39 < (255 - var_a2)) {
            obj->segment.unk38.byte.unk39 += var_a2;
        } else {
            obj->segment.unk38.byte.unk39 = 0xFF;
            obj->action = TAJ_MODE_APPROACH_PLAYER;
        }
        break;
    case TAJ_MODE_SET_CHALLENGE:
        obj->segment.unk38.byte.unk3B = 3;
        taj->unkD = 0xFF;
        taj->unk14 = 0.0f;
        taj->unk4 += updateRateF * 2.0f;
        if (taj->unk4 > 79.0f) {
            taj->unk4 = 79.0f;
        }
        var_a2 = updateRate * 8;
        if (taj->unk4 < 20.0f) {
            var_a2 = 0;
        }
        if (obj->segment.unk38.byte.unk39 > var_a2) {
            obj->segment.unk38.byte.unk39 -= var_a2;
        } else {
            racer64->racer.unk118 = func_80004B40(racer64->racer.characterId, racer64->racer.vehicleID);
            func_80030DE0(0, taj->unk11, taj->unk12, taj->unk13, taj->unk20, taj->unk22, 0xB4);
            set_music_player_voice_limit(levelHeader->voiceLimit);
            play_music(levelHeader->music);
            func_80001074(levelHeader->instruments);
            init_racer_for_challenge(racer64->racer.vehicleID);
            temp_v0_12 = func_8002342C(obj->segment.trans.x_position, obj->segment.trans.z_position);
            if (temp_v0_12 != NULL) {
                obj->segment.trans.x_position = temp_v0_12->segment.trans.x_position;
                obj->segment.trans.z_position = temp_v0_12->segment.trans.z_position;
                obj->segment.unk2C.half.lower = temp_v0_12->segment.unk2C.half.lower;
                obj->segment.trans.y_rotation = racerObj->segment.trans.y_rotation + 0x8000;
            }
            obj->action = TAJ_MODE_RACE;
        }
        break;
    case TAJ_MODE_TELEPORT_AWAY_BEGIN:
        obj->segment.unk38.byte.unk3B = 3;
        taj->unkD = 0xFF;
        taj->unk14 = 0.0f;
        taj->unk4 += updateRateF * 2.0f;
        if (taj->unk4 > 79.0f) {
            taj->unk4 = 79.0f;
        }
        var_a2 = updateRate * 8;
        if (taj->unk4 < 20.0f) {
            var_a2 = 0;
        }
        if (obj->segment.unk38.byte.unk39 > var_a2) {
            obj->segment.unk38.byte.unk39 -= var_a2;
        } else {
            obj->segment.unk38.byte.unk39 = 0;
            obj->action = TAJ_MODE_TELEPORT_AWAY_END;
            temp_v0_12 = func_8002342C(obj->segment.trans.x_position, obj->segment.trans.z_position);
            if (temp_v0_12 != NULL) {
                obj->segment.trans.x_position = temp_v0_12->segment.trans.x_position;
                obj->segment.trans.z_position = temp_v0_12->segment.trans.z_position;
                obj->segment.unk2C.half.lower = temp_v0_12->segment.unk2C.half.lower;
                obj->segment.trans.y_rotation = racerObj->segment.trans.y_rotation + 0x8000;
            }
        }
        break;
    case TAJ_MODE_TELEPORT_AWAY_END:
        obj->segment.unk38.byte.unk3B = 3;
        taj->unk4 -= updateRateF * 2.0f;
        if (taj->unk4 < 0.0f) {
            taj->unk4 = 0.0f;
        }
        var_a2 = updateRate * 4;
        if (obj->segment.unk38.byte.unk39 < (0xFF - var_a2)) {
            obj->segment.unk38.byte.unk39 += var_a2;
        } else {
            obj->segment.unk38.byte.unk39 = 0xFF;
            obj->action = TAJ_MODE_ROAM;
        }
        break;
    case TAJ_MODE_RACE:
        obj->interactObj->unk14 = 0;
        obj->segment.unk38.byte.unk3B = 6;
        obj->segment.unk38.byte.unk39 = 0xFF;
        taj->unk4 += updateRateF * 1.0f;
        break;
    default:
        obj->segment.unk38.byte.unk3B = 0;
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
            if ((distance < 55.0f) && (taj->unk1C == 0) && (racerObj != NULL)) {
                taj->unk1C = 240;
                taj->unk1E = (s16) (arctan2_f(xPosDiff / distance, zPosDiff / distance) + 0x4000);
            }
            if (taj->unk1C > 0) {
                taj->unk1C -= updateRate;
            } else {
                taj->unk1C = 0;
            }
            if (taj->unk1C < 120) {
                taj->unk4 += func_8001C6C4((Object_64*)taj, obj, updateRateF, 1.0f, 0);
            } else {
                var_a2 = taj->unk1E - (obj->segment.trans.y_rotation & 0xFFFF);
                if (var_a2 > 0x8000) {
                    var_a2 -= 0xFFFF;
                }
                if (var_a2 < -0x8000) {
                    var_a2 += 0xFFFF;
                }
                obj->segment.trans.y_rotation += ((var_a2 * updateRate) >> 4);
                xPosDiff = sins_f(obj->segment.trans.y_rotation + 0x8000);
                zPosDiff = coss_f(obj->segment.trans.y_rotation + 0x8000);
                move_object(
                    obj,
                    (updateRateF2 * xPosDiff) * 1.1f,
                    0.0f,
                    (updateRateF2 * zPosDiff) * 1.1f
                );
                taj->unk4 += updateRate * 2.2f;
            }
        }
        racerObjs = get_racer_objects(&numRacers);
        if (racerObjs[PLAYER_ONE] != NULL) {
            xPosDiff = racerObjs[PLAYER_ONE]->segment.trans.x_position - obj->segment.trans.x_position;
            distance = racerObjs[PLAYER_ONE]->segment.trans.y_position - obj->segment.trans.y_position;
            zPosDiff = racerObjs[PLAYER_ONE]->segment.trans.z_position - obj->segment.trans.z_position;
            var_f2 = ((xPosDiff * xPosDiff) + (distance * distance) + (zPosDiff * zPosDiff));
            if (var_f2 < 1000.0f * 1000.0f) {
                var_f2 = sqrtf(var_f2);
                var_f2 = (1000.0f) - var_f2;
                sp3C = (127.0f * var_f2) / (1000.0f);
                temp_v0_22 = func_80069D7C();
                xPosDiff = obj->segment.trans.x_position - temp_v0_22->trans.x_position;
                zPosDiff = obj->segment.trans.z_position - temp_v0_22->trans.z_position;
                arctan = func_800090C0(xPosDiff, zPosDiff, temp_v0_22->trans.y_rotation);
                temp = arctan;
                func_80001268(0xA, sp3C);
                func_80001268(0xB, sp3C);
                func_80001268(0xF, sp3C);
                musicSetChlPan(0xA, temp);
                musicSetChlPan(0xB, temp);
                musicSetChlPan(0xF, temp);
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
        switch (taj->unk36) {
        case 0:
            if (taj->unk34 > updateRate << 7) {
                taj->unk34 -= updateRate << 7;
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
                taj->unk2C += updateRate;
                if (taj->unk30 < taj->unk2C) {
                    taj->unk36 = 1;
                    taj->unk2C = get_random_number_from_range(600, 900);
                }
            } else {
                taj->unk2C = 0;
                taj->unk30 = 0;
            }
            break;
        case 1:
            if ((musicGetChanMask() & ~0x4000) == 0xB) {
                taj->unk34 += (updateRate * 128);
                if (taj->unk34 > 0x7F00) {
                    taj->unk34 = 0x7F00;
                }
                taj->unk2C -= updateRate;
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
    var_a2 = func_8002B0F4(obj->segment.unk2C.half.lower, obj->segment.trans.x_position, obj->segment.trans.z_position, (struct TempStruct8 **) &sp94);
    if(var_a2 != 0) {
        var_a2--;
        while(var_a2 >= 0) {
            if ((sp94[var_a2]->unk10 != 11) && (sp94[var_a2]->unk10 != 14) && (sp94[var_a2]->unk8 > 0.0f)) {
                obj->segment.trans.y_position = sp94[var_a2]->unk0;
            }
            var_a2--;
        }
    }
    obj->segment.trans.x_rotation = 0;
    obj->segment.trans.z_rotation = 0;
    if (obj->action != TAJ_MODE_ROAM) {
        D_8011D4D0 = obj->segment.trans.y_position;
    }
    if (sp6B != 0) {
        func_8003FC44(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 0xC, 0, 1.0f, 0);
    }
    obj->segment.animFrame = taj->unk4 * 1.0f;
    func_80061C0C(obj);
    func_800AFC3C(obj, updateRate);
}

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

void obj_loop_gbparkwarden(UNUSED Object *obj, UNUSED s32 updateRate) {
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

void obj_loop_checkpoint(UNUSED Object *obj, UNUSED s32 updateRate) {
}

/**
 * Vehicle mode changer initialisation function.
 * Sets direction and vehicleID based off spawn info.
*/
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
    obj64->vehicleID = entry->vehicleID;
    obj->interactObj->unk14 = 2;
    obj->interactObj->unk11 = 0;
    obj->interactObj->unk10 = entry->unk8;
    obj->interactObj->unk12 = 0;
}

/**
 * Vehicle mode changer loop behaviour.
 * Racers that pass through will have their vehicle type changed. This is usually used for loop-de-loops.
*/
void obj_loop_modechange(Object *obj, UNUSED s32 updateRate) {
    Object *racerObj;
    Object **racerObjects;
    s32 numRacers;
    Object_Racer *racer;
    Object_ModeChange *modeChange;
    f32 diffX;
    f32 diffY;
    f32 diffZ;
    s32 radius_3;
    s32 i;
    f32 radiusF;
    f32 dist;
    
    modeChange = (Object_ModeChange *) obj->unk64;
    if (obj->interactObj->distance < modeChange->unk10) {
        radiusF = modeChange->unk10;
        racerObjects = get_racer_objects(&numRacers);
        for (i = 0; i < numRacers; i++) {
            racerObj = racerObjects[i];
            racer = (Object_Racer *) racerObj->unk64;
            if (racer->vehicleID != modeChange->vehicleID) {
                diffX = racerObj->segment.trans.x_position - obj->segment.trans.x_position;
                diffY = racerObj->segment.trans.y_position - obj->segment.trans.y_position;
                diffZ = racerObj->segment.trans.z_position - obj->segment.trans.z_position;
                dist = ((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ));
                if (dist < radiusF * radiusF) {
                    dist = ((modeChange->unk0 * racerObj->segment.trans.x_position) + (modeChange->unk8 * racerObj->segment.trans.z_position) + modeChange->unkC);
                    if (dist < 0.0f) {
                        racer->unk1E0 = 0;
                        if (modeChange->vehicleID == VEHICLE_CAR) {
                            racer->vehicleID = racer->vehicleIDPrev;
                        } else {
                            racer->vehicleID = modeChange->vehicleID;
                        }
                        if (modeChange->vehicleID == VEHICLE_LOOPDELOOP) {
                            if (racer->raceFinished == FALSE) {
                                func_80072348(racer->playerIndex, 8);
                            }
                            radius_3 = func_8001C524(racerObj->segment.trans.x_position, racerObj->segment.trans.y_position, racerObj->segment.trans.z_position, 0);
                            if (radius_3 != 0xFF) {
                                racer->unk158 = func_8001D214(radius_3);
                            } else {
                                racer->unk158 = NULL;
                            }
                            racer->unk15C = NULL;
                            racer->unk19A = 0;
                        }
                        racer->unk198 = obj->segment.trans.y_rotation;
                    }
                }
            }
        }
    }
    
}


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
    obj->interactObj->unk14 = 2;
    obj->interactObj->unk11 = 0;
    obj->interactObj->unk10 = entry->unk8;
    obj->interactObj->unk12 = 0;
}

void obj_loop_bonus(Object *obj, UNUSED s32 updateRate) {
    Object *racerObj;
    Object_Racer *racer;
    s32 numberOfRacers;
    f32 diffX;
    f32 diffY;
    f32 halfDist;
    f32 dist;
    f32 diffZ;
    Object_Bonus *obj64;
    Object **racerObjects;
    s32 i;

    obj64 = &obj->unk64->bonus;
    if (obj->interactObj->distance < obj64->unk10) {
        dist = obj64->unk10;
        halfDist = dist * 0.5f;
        racerObjects = get_racer_objects(&numberOfRacers);
        for (i = 0; i < numberOfRacers; i++) {
            racerObj = racerObjects[i];
            racer = &racerObj->unk64->racer;
            diffY = racerObj->segment.trans.y_position - obj->segment.trans.y_position;
            if ((diffY < halfDist) && (-halfDist < diffY)) {
                diffX = racerObj->segment.trans.x_position - obj->segment.trans.x_position;
                diffZ = racerObj->segment.trans.z_position - obj->segment.trans.z_position;
                if ((((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ)) < dist * dist)) {
                    f32 temp = (obj64->unk0 * racerObj->segment.trans.x_position) + (obj64->unk8 * racerObj->segment.trans.z_position) + obj64->unkC;
                    if (temp < 0.0f) {
                        if ((s32) racer->bananas < 10) {
                            racer->bananas = 10;
                            play_sound_at_position(SOUND_SELECT, racerObj->segment.trans.x_position, racerObj->segment.trans.y_position, racerObj->segment.trans.z_position, 4, NULL);
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
    obj->interactObj->unk14 = 2;
    obj->interactObj->unk11 = 4;
    obj->interactObj->unk10 = 20;
    obj->interactObj->unk12 = 0;
    scalef = entry->scale & 0xFF;
    if (scalef < 10.0f) {
        scalef = 10.0f;
    }
    scalef /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * scalef;
    obj64 = &obj->unk64->golden_balloon;
    obj64->unkD = 255;
    obj64->unk0 = 0.0f;
    obj->action = 0;
    if (entry->unkA != 0) {
        if ((get_settings()->tajFlags & (1 << (entry->unkA + 2))) != 0) {
            obj->action = 0;
        } else {
            obj->action = 1;
        }
    }
}

void obj_loop_goldenballoon(Object *obj, s32 updateRate) {
    LevelObjectEntry *levelEntry;
    ObjectInteraction *obj4C;
    Object_Racer *racer;
    Object_GoldenBalloon *obj64;
    Settings *settings;
    s32 flag;
    s32 doubleSpeed;
    Object *racerObj;
    f32 updateRateF;
    f32 speedf;
    s32 isPirated;

    updateRateF = updateRate;
    isPirated = FALSE;
#ifndef NO_ANTIPIRACY
    // AntiPiracy check. Seems to set a flag that prevents collecting balloons.
    if (IO_READ(0x284) != 0x240B17D7) {
        isPirated = TRUE;
    }
#endif
    speedf = updateRateF;
    settings = get_settings();
    levelEntry = obj->segment.unk3C_a.level_entry;
    flag = 0x10000 << levelEntry->goldenBalloon.unk8;
    if (settings->courseFlagsPtr[settings->courseId] & flag) {
        if (obj->unk7C.word > 0) {
            obj->unk74 = 2;
            func_800AFC3C(obj, updateRate);
            obj->unk7C.word -= updateRate;
        } else {
            gParticlePtrList_addObject(obj);
        }
    } else {
        obj->segment.trans.unk6 |= 0x4000;
        if (obj->action == 0) {
            obj->segment.trans.unk6 &= 0xBFFF;
            doubleSpeed = updateRate * 2;
            if (obj->segment.unk38.byte.unk39 < (255 - doubleSpeed)) {
                obj->segment.unk38.byte.unk39 += doubleSpeed;
            } else {
                obj->segment.unk38.byte.unk39 = 255;
            }
            obj4C = obj->interactObj;
            if ((obj4C->distance < 45) && (isPirated == FALSE)) {
                racerObj = obj4C->obj;
                if ((racerObj && (racerObj->segment.header->behaviorId == 1))) {
                    racer = &racerObj->unk64->racer;
                    if (racer->playerIndex == PLAYER_ONE) {
                        settings->balloonsPtr[settings->worldId]++;
                        if (settings->worldId != 0) {
                            settings->balloonsPtr[0]++;
                        }
                        settings->courseFlagsPtr[settings->courseId] |= flag;
                        play_sound_spatial(SOUND_COLLECT_BALLOON, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, NULL);
                        obj->unk7C.word = 16;
                        obj->unk74 = 2;
                        obj->segment.trans.unk6 |= 0x4000;
                        func_800AFC3C(obj, updateRate);
                    }
                }
            }
            obj64 = &obj->unk64->golden_balloon;
            obj->segment.unk38.byte.unk3B = 0;
            obj64->unk14 = 0.0f;
            speedf = (obj->segment.unk38.byte.unk39 < 255) ? 0 : 1;
            if (obj64->unkD == 255) {
                obj64->unkD = func_8001C524(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 0);
                if (obj64->unkD != 255) {
                    obj64->unkE = func_8001CC48(obj64->unkD, -1, 0);
                    obj64->unkF = func_8001CC48(obj64->unkE, obj64->unkD, 0);
                    obj64->unk10 = func_8001CC48(obj64->unkF, obj64->unkE, 0);
                    obj64->unkC = obj64->unkD;
                }
            } else {
                func_8001C6C4((Object_64 *) obj64, obj, updateRateF, speedf, 0);
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
    obj->segment.unk38.byte.unk3A = entry->modelIndex;
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
    obj->interactObj->unk14 = 0x21;
    obj->interactObj->unk11 = 2;
    obj->interactObj->unk10 = 0x14;
    obj->interactObj->unk12 = 0;
    if (obj->segment.unk38.byte.unk3A >= obj->segment.header->numberOfModelIds) {
        obj->segment.unk38.byte.unk3A = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_door.s")

void obj_init_ttdoor(Object *obj, LevelObjectEntry_TTDoor *entry) {
    Object_TTDoor *obj64;
    f32 phi_f0;

    obj->segment.unk38.byte.unk3A = 0;
    obj64 = &obj->unk64->tt_door;
    obj->segment.trans.y_rotation = entry->unk8 << 6 << 4;
    obj64->unkF = entry->unkE;
    obj64->unk13 = entry->unkB;
    obj64->unk0 = obj->segment.trans.y_position;
    obj64->unk8 = 0;
    obj64->unk12 = entry->unkA;
    obj->action = obj->segment.trans.y_rotation;
    obj->unk7C.word = (entry->unk9 & 0x3F) << 0xA;
    phi_f0 = entry->unkC & 0xFF;
    if (phi_f0 < 10) {
        phi_f0 = 10;
    }
    phi_f0 /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * phi_f0;
    obj->interactObj->unk14 = 0x21;
    obj->interactObj->unk11 = 2;
    obj->interactObj->unk10 = 0x14;
    obj->interactObj->unk12 = 0;
    if (obj->segment.unk38.byte.unk3A >= obj->segment.header->numberOfModelIds) {
        obj->segment.unk38.byte.unk3A = 0;
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
        obj->segment.unk38.byte.unk3A = D_800DCA94[settings->ttAmulet];
    } else {
        obj->segment.unk38.byte.unk3A = D_800DCA9C[settings->ttAmulet];
    }
#ifndef UNLOCK_ALL
    if (obj->interactObj->distance < ttDoor->unk12 && (settings->ttAmulet < 4 || *settings->balloonsPtr < 47)) {
        racerObj = obj->interactObj->obj;
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
#endif
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
#ifndef UNLOCK_ALL
    if (settings->ttAmulet >= 4 && obj->interactObj->distance < ttDoor->unk12 && *settings->balloonsPtr >= 47) {
#else
    if (obj->interactObj->distance < ttDoor->unk12) {
#endif
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
            play_sound_at_position(SOUND_DOOR_OPEN, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 1, (s32 *) &ttDoor->soundMask);
        }
    } else {
        if (ttDoor->soundMask) {
            func_800096F8((s32) ttDoor->soundMask);
            ttDoor->soundMask = NULL;
        }
    }
    obj->interactObj->distance = 0xFF;
    obj->interactObj->obj = NULL;
    obj->interactObj->unk14 &= 0xFFF7;
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
    obj->interactObj->unk14 = 2;
    obj->interactObj->unk11 = 0;
    obj->interactObj->unk10 = entry->scale;
    obj->interactObj->unk12 = 0;
}


void obj_loop_trigger(Object *obj, UNUSED s32 updateRate) {
    s32 i;
    s32 curRaceType;
    s32 numRacers;
    LevelObjectEntry_Trigger *triggerEntry;
    Object *racerObj;
    Object **racers;
    Object_Trigger *trigger;
    Object_Racer *racer;
    Settings *settings;
    f32 diffX;
    f32 diffY;
    f32 diffZ;
    f32 radiusF;
    s32 flags;
    f32 distance;
    s32 courseFlags;

    triggerEntry = (LevelObjectEntry_Trigger *) obj->segment.unk3C_a.level_entry;
    trigger = (Object_Trigger *) obj->unk64;
    settings = get_settings();
    courseFlags = settings->courseFlagsPtr[settings->courseId];
    curRaceType = get_current_level_race_type();
    if (triggerEntry->unk9 >= 0) {
        flags = 0x10000 << triggerEntry->unk9;
        if (obj->interactObj->distance < trigger->unk10) {
            if (((u8) curRaceType != RACETYPE_HUBWORLD) || !(courseFlags & flags)) {
                radiusF = trigger->unk10;
                racers = get_racer_objects(&numRacers);
                for (i = 0; i < numRacers; i++) {
                    racerObj = racers[i];
                    racer = (Object_Racer*)racerObj->unk64;
                    if ((!(trigger->unk14 & 1) && racer->playerIndex == PLAYER_COMPUTER) || (!(trigger->unk14 & 2) && racer->playerIndex != PLAYER_COMPUTER)) {
                        diffX = racerObj->segment.trans.x_position - obj->segment.trans.x_position;
                        diffY = racerObj->segment.trans.y_position - obj->segment.trans.y_position;
                        diffZ = racerObj->segment.trans.z_position - obj->segment.trans.z_position;
                        distance = ((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ));
                        if (distance < radiusF * radiusF) {
                            distance = (trigger->unk0 * racerObj->segment.trans.x_position) + (trigger->unk8 * racerObj->segment.trans.z_position) + trigger->unkC;
                            if (distance < 0.0f) {
                                settings->courseFlagsPtr[settings->courseId] |= flags;
                                if (triggerEntry->unkB != 0xFF) {
                                    func_800C31EC(triggerEntry->unkB);
                                }
                                if (triggerEntry->unkC != 0xFF) {
                                    func_80021400(triggerEntry->unkC + 0x80);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void obj_init_bridge_whaleramp(Object *obj, LevelObjectEntry_Bridge_WhaleRamp *entry) {
    Object_Bridge_WhaleRamp *temp = &obj->unk64->bridge_whale_ramp;
    obj->segment.unk38.byte.unk3A = entry->unk8;
    obj->segment.trans.y_rotation = entry->unk9 << 6 << 4;
    temp->unk0 = obj->segment.trans.y_position;
    obj->interactObj->unk14 = 0x21;
    obj->interactObj->unk11 = 2;
    obj->interactObj->unk10 = 0x14;
    obj->interactObj->unk12 = 0;
    temp->unk4 = 0;
    if (obj->segment.unk38.byte.unk3A >= obj->segment.header->numberOfModelIds) {
        obj->segment.unk38.byte.unk3A = 0;
    }
}

/**
 * Moving bridge loop behaviour.
 * In Whale Bay and Boulder Canyon, there exist two bridge objects you can use.
 * This function makes the whale oscillate and move upwards when a player gets near.
 * For the boulder canyon bridge, it raises and plays a bell sound while it's set to be raised.
*/
void obj_loop_bridge_whaleramp(Object *obj, s32 updateRate) {
    Object *racerObj;
    f32 temp_f2;
    Object_Bridge_WhaleRamp *whaleRamp;
    LevelObjectEntry_Bridge_WhaleRamp *entry;
    f32 updateRateF;
    s32 var_v0;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    Object_Racer *racer;
    
    whaleRamp = (Object_Bridge_WhaleRamp *) obj->unk64;
    entry = (LevelObjectEntry_Bridge_WhaleRamp *) obj->segment.unk3C_a.level_entry;
    updateRateF = updateRate;
    
    if (entry->unkB != 3) {
        if (obj->unk78 != 0) {
            temp_f2 = (2.0f * (f32) entry->unkE);
            if (temp_f2 > 0.0f) {
                if (obj->segment.trans.y_position < (whaleRamp->unk0 + temp_f2)) {
                    obj->segment.trans.y_position += (updateRateF * 2);
                }
            } else {
                if ((whaleRamp->unk0 + temp_f2) < obj->segment.trans.y_position) {
                    obj->segment.trans.y_position -= (updateRateF * 2);
                }
            }
        } else if (entry->unkC > 0) {
            if (whaleRamp->unk0 < obj->segment.trans.y_position) {
                obj->segment.trans.y_position -= (updateRateF * 2);
            }
        } else {
            if (obj->segment.trans.y_position < whaleRamp->unk0) {
                obj->segment.trans.y_position += (updateRateF * 2);
            }
        }
    } else if (obj->unk78 != 0) {
        if (obj->segment.trans.x_rotation >= -0x12FF) {
            obj->segment.trans.x_rotation -= (updateRate * 0x2D);
        }
        if (whaleRamp->unk4 == 0) {
            whaleRamp = whaleRamp;
            func_8001E36C(entry->unkA, &sp50, &sp4C, &sp48);
            play_sound_at_position(SOUND_DRAWBRIDGE_BELL, sp50, sp4C, sp48, 1, &whaleRamp->unk4);
        }
    } else {
        if (obj->segment.trans.x_rotation < 0) {
            obj->segment.trans.x_rotation = obj->segment.trans.x_rotation + (updateRate * 0x28);
            if (whaleRamp->unk4 == 0) {
                whaleRamp = whaleRamp;
                func_8001E36C(entry->unkA, &sp44, &sp40, &sp3C);
                play_sound_at_position(SOUND_DRAWBRIDGE_BELL, sp44, sp40, sp3C, 1, &whaleRamp->unk4);
            }
        } else {
            obj->segment.trans.x_rotation = 0;
            if (whaleRamp->unk4 != 0) {
                func_800096F8(whaleRamp->unk4);
            }
        }
    }
    
    switch (entry->unkB) {
    case 0:
        obj->unk78 = 0;
        if (obj->interactObj->distance < entry->unkC) {
            obj->unk78 = 1;
        }
        break;
    case 2:
        obj->unk78 = 1;
        racerObj = get_racer_object(0);
        if (racerObj != NULL) {
            racer = (Object_Racer *) racerObj->unk64;
            switch(racer->vehicleID) {
                default:
                    var_v0 = VEHICLE_HOVERCRAFT;
                    break;
                case 1:
                    var_v0 = VEHICLE_PLANE;
                    break;
                case 2:
                    var_v0 = VEHICLE_LOOPDELOOP;
                    break;
            }
            if (entry->unkF & var_v0) {
                obj->unk78 = NULL;
            }
        }
        break;
    default:
        if (func_8001E2EC(entry->unkA) != 0) {
            obj->unk78 = (entry->unkD * 2);
        }
        if (obj->unk78 > 0) {
            obj->unk78 -= updateRate;
        } else {
            obj->unk78 = 0;
        }
        break;
    }
    
    obj->interactObj->distance = 255;
    obj->interactObj->obj = NULL;
    obj->interactObj->unk14 &= 0xFFF7;
}

void obj_init_rampswitch(Object *obj, LevelObjectEntry_RampSwitch *entry) {
    obj->interactObj->unk14 = 2;
    obj->interactObj->unk11 = 0;
    obj->interactObj->unk10 = 0x14;
    obj->interactObj->unk12 = 0;
    obj->action = entry->unk8;
}

void obj_loop_rampswitch(Object *obj, UNUSED s32 updateRate) {
    if (obj->interactObj->distance < 0x2D) {
        func_8001E344(obj->action);
    }
    obj->interactObj->distance = (u8)0xFF;
}

void obj_init_seamonster(UNUSED Object *obj, UNUSED LevelObjectEntry_SeaMonster *entry) {
}

void obj_loop_seamonster(UNUSED Object *obj, UNUSED s32 updateRate) {
}

/* Official name: fogInit(?) */
void obj_init_fogchanger(Object *obj, LevelObjectEntry_FogChanger *entry) {
    f32 temp_f0;
    temp_f0 = entry->unk8 * 8.0f;
    temp_f0 = temp_f0 * temp_f0;
    obj->unk78f = temp_f0;
}

void obj_init_skycontrol(Object *obj, LevelObjectEntry_SkyControl *entry) {
    obj->interactObj->unk14 = 2;
    obj->interactObj->unk11 = 0;
    obj->interactObj->unk10 = entry->unk9;
    obj->action = entry->unk8;
    obj->unk7C.word = entry->unk9;
}

void obj_loop_skycontrol(Object *obj, UNUSED s32 updateRate) {
    if (obj->interactObj->distance < obj->unk7C.word) {
        set_skydome_visbility(obj->action);
    }
}

void obj_init_ainode(Object *obj, LevelObjectEntry_AiNode *entry) {
    if (entry->unk9 == 0xFF) {
        entry->unk9 = func_8001C48C(obj) & 0xFF;
    }
    func_8001D1BC(entry->unk9);
    func_8001D1AC();
}

void obj_loop_ainode(UNUSED Object *obj, UNUSED s32 updateRate) {
}

void obj_init_treasuresucker(Object *obj, LevelObjectEntry_TreasureSucker *entry) {
    obj->segment.animFrame = 120;
    obj->action = (entry->unk8 - 1) & 3;
}

/**
 * Smokey's castle treasure box loop function.
 * When the player approaches carrying bananas, it spawns visual objects to enter it, then takes them from the player.
*/
void obj_loop_treasuresucker(Object *obj, s32 updateRate) {
    Object *racerObj;
    f32 scale;
    Object_Racer *racer;
    f32 diffX;
    f32 diffY;
    f32 diffZ;
    Object *newObj;
    LevelObjectEntryCommon spawnObj;
    s32 doSpawnObj;

    racerObj = get_racer_object(obj->unk78);
    if (racerObj != NULL) {
        racer = (Object_Racer *) racerObj->unk64;
        doSpawnObj = FALSE;
        if (racer->bananas != 0 && obj->unk7C.word == 0) {
            diffX = obj->segment.trans.x_position - racerObj->segment.trans.x_position;
            diffY = obj->segment.trans.y_position - racerObj->segment.trans.y_position;
            diffZ = obj->segment.trans.z_position - racerObj->segment.trans.z_position;
            diffX = (diffX * diffX) + (diffY * diffY) + (diffZ * diffZ); // Required to match.
            if (diffX < 225 * 225) {
                obj->unk7C.word = 8;
                doSpawnObj = TRUE;
            }
        }
        if (obj->unk7C.word > 0) {
            obj->unk7C.word -= updateRate;
            if (obj->unk7C.word <= 0) {
                if (racer->bananas > 0) {
                    racer->bananas--;
                    if (racer->bananas != 0) {
                        doSpawnObj = TRUE;
                    }
                    obj->unk7C.word = 8;
                } else {
                    obj->unk7C.word = 0;
                }
            }
        }
        if (doSpawnObj) {
            spawnObj.x = racerObj->segment.trans.x_position;
            spawnObj.y = (s16) racerObj->segment.trans.y_position + 10;
            spawnObj.z = racerObj->segment.trans.z_position;
            spawnObj.size = 8;
            spawnObj.objectID = BHV_SNOWBALL_2;
            newObj = spawn_object(&spawnObj, 1);
            if (newObj != NULL) {
                newObj->segment.unk3C_a.level_entry = NULL;
                newObj->segment.y_velocity = 10.0f;
                scale = (newObj->segment.y_velocity * 2) / 0.5f;
                newObj->segment.x_velocity = (obj->segment.trans.x_position - racerObj->segment.trans.x_position) / scale;
                newObj->segment.z_velocity = (obj->segment.trans.z_position - racerObj->segment.trans.z_position) / scale;
                newObj->unk7C.word = (s32) racer;
                newObj->unk78 = scale;
            }
        }
    }
}


void obj_init_flycoin(UNUSED Object *obj, UNUSED LevelObjectEntry_FlyCoin *entry) {
}

// Smokey's castle banana pickups.
void obj_loop_flycoin(Object *obj, s32 updateRate) {
    f32 updateRateF;
    Object_Racer *racerObj;

    updateRateF = updateRate;
    obj->segment.y_velocity -= 0.5f * updateRateF;
    move_object(obj, obj->segment.x_velocity * updateRateF, obj->segment.y_velocity * updateRateF, obj->segment.z_velocity * updateRateF);
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
    obj->segment.animFrame += updateRate * 8;
}

void obj_init_bananacreator(Object *obj, UNUSED LevelObjectEntry_BananaCreator *entry) {
    obj->segment.animFrame = 100;
}

void obj_loop_bananacreator(Object *obj, s32 updateRate) {
  LevelObjectEntryCommon newEntry;
  Object *newBananaObj;
  Object_Banana *newBananaObj64;

  if (obj->unk7C.word != 0) {
    obj->unk78 -= updateRate;
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
    obj->interactObj->unk14 = 2;
    obj->interactObj->unk11 = 0;
    obj->interactObj->unk10 = 0x1E;
    obj->unk7C.half.upper = 0x14;
    obj->unk7C.half.lower = 0x10;
    if (get_filtered_cheats() & CHEAT_DISABLE_BANANAS) {
        gParticlePtrList_addObject(obj);
    }
}

/**
 * Banana loop behaviour.
 * When dropped by a player, will have initial velocity to give some spread.
 * When touched by a player, will increase their banana count.
*/
void obj_loop_banana(Object *obj, s32 updateRate) {
    Object *racerObj;
    Object_Racer *racer;
    f32 tempPos[3];
    f32 sp58;
    f32 updateRateF;
    f32 velX;
    f32 velZ;
    s32 sp48;
    s32 sp44;
    s8 sp43;
    Object_Banana *banana;
    Object_78_Banana *obj78;
    s32 racerPrevUnk180;

    updateRateF = updateRate;
    banana = (Object_Banana *) obj->unk64;
    obj->segment.animFrame += updateRate * 8;
    obj78 = (Object_78_Banana *) &obj->unk78;
    if (obj->unk78 == -1) {
        obj->segment.trans.unk6 |= 0x4000; 
        obj78->unk6 -= updateRate;
        obj->unk74 = 1;
        func_800AFC3C(obj, updateRate);
        if (obj78->unk6 <= 0) {
            gParticlePtrList_addObject(obj);
        }
    } else {
        if (banana->unk8 > 0) {
            banana->unk8 -= updateRate;
        } else {
            banana->unk8 = 0;
            banana->unk0 = 0;
        }
        if (obj78->unk0 == 1) {
            tempPos[0] = obj->segment.trans.x_position + (obj->segment.x_velocity * updateRateF);
            tempPos[1] = obj->segment.trans.y_position + (obj->segment.y_velocity * updateRateF);
            tempPos[2] = obj->segment.trans.z_position + (obj->segment.z_velocity * updateRateF);
            sp58 = 8.0f;
            func_80031130(1, &obj->segment.trans.x_position, tempPos, -1);
            sp48 = 0;
            func_80031600(&obj->segment.trans.x_position, tempPos, &sp58, &sp43, 1, &sp48);
            obj->segment.x_velocity = (tempPos[0] - obj->segment.trans.x_position) / updateRateF;
            obj->segment.y_velocity = (tempPos[1] - obj->segment.trans.y_position) / updateRateF;
            obj->segment.z_velocity = (tempPos[2] - obj->segment.trans.z_position) / updateRateF;
            obj->segment.trans.x_position = tempPos[0];
            obj->segment.trans.y_position = tempPos[1];
            obj->segment.trans.z_position = tempPos[2];
            if (banana->unk9 != 2) {
                obj->segment.y_velocity -= 1.0f;
                obj->segment.x_velocity *= 0.95;
                obj->segment.z_velocity *= 0.95;
            } else {
                obj->segment.x_velocity = 0.0f;
                obj->segment.y_velocity = 0.0f;
                obj->segment.z_velocity = 0.0f;
            }
            velX = obj->segment.x_velocity;
            if (velX < 0.0f) {
                velX = -velX;
            }
            velZ = obj->segment.z_velocity;
            if (velZ < 0.0f) {
                velZ = -velZ;
            }
            if (sp48 > 0 && velX < 0.5f && velZ < 0.5f) {
                obj78->unk0 = 0;
            }
            sp58 = -10000.0f;
            if (func_8002B9BC(obj, &sp58, NULL, 1) != 0 && obj->segment.trans.y_position < sp58) {
                obj78->unk0 = 0;
                obj->segment.trans.y_position = sp58;
            }
        }
        sp44 = 70;
        if (banana->unk9 != 2) {
            sp44 = 55;
        }
        
        if (obj78->unk4 > 0) {
            obj78->unk4 -= updateRate;
        } else {
            obj78->unk4 = 0;
        }
        if (obj->interactObj->distance < 0x78) {
            if (get_current_level_race_type() == RACETYPE_CHALLENGE_BANANAS) {
                racerObj = obj->interactObj->obj;
                if (racerObj != NULL && racerObj->segment.header->behaviorId == BHV_RACER) {
                    racer = (Object_Racer *) racerObj->unk64;
                    if (racer->playerIndex == PLAYER_COMPUTER) {
                        sp44 += 30;
                    }
                }
            }
        }
        if (obj->interactObj->distance < sp44 && obj78->unk4 == 0) {
            racerObj = obj->interactObj->obj;
            if (racerObj != NULL && racerObj->segment.header->behaviorId == BHV_RACER) { 
                racer = (Object_Racer *) racerObj->unk64;
                if ((get_current_level_race_type() != RACETYPE_CHALLENGE_BANANAS) || racer->bananas < 2) {
                    racerPrevUnk180 = racer->unk180;
                    play_sound_at_position( SOUND_SELECT,  racerObj->segment.trans.x_position,  racerObj->segment.trans.y_position,  racerObj->segment.trans.z_position, 4, &racer->unk180);
                    if (racerPrevUnk180 != 0) {
                        func_800096F8(racerPrevUnk180);
                    }
                    if ((racer->playerIndex != PLAYER_COMPUTER) && racer->bananas == 9) {
                        play_sound_spatial(racer->characterId + SOUND_UNK_7B, racerObj->segment.trans.x_position, racerObj->segment.trans.y_position, racerObj->segment.trans.z_position, NULL
                        );
                    }
                    racer->bananas++;
                    if (banana->spawner != NULL) {
                        banana->spawner->unk7C.word = 1;
                    }
                    if (get_number_of_active_players() > TWO_PLAYERS) {
                        gParticlePtrList_addObject(obj);
                    } else {
                        obj78->unk0 = -1;
                        obj->unk74 = 1;
                        func_800AFC3C(obj, updateRate);
                    }
                }
            }
        }
    }
}


/**
 * Race silver coin init behaviour.
 * Checks if in the correct modes, then sets the flag to active, otherwise inactive.
 * If the flag is inactive, destroy the object.
 * Rareware duplicated this function just to check for adventure 2...
*/
void obj_init_silvercoin_adv2(Object *obj, UNUSED LevelObjectEntry_SilverCoinAdv2 *entry) {
    obj->interactObj->unk14 = 2;
    obj->interactObj->unk11 = 0;
    obj->interactObj->unk10 = 0x1E;
    obj->action = 3;
    obj->unk7C.word = 16;
    if (!is_in_tracks_mode()) {
        if (check_if_silver_coin_race() && is_in_adventure_two()) {
            obj->action = SILVER_COIN_ACTIVE;
        } else {
            obj->action = SILVER_COIN_INACTIVE;
        }
    }
    if (obj->action == SILVER_COIN_INACTIVE) {
        obj->segment.trans.unk6 |= 0x600;
        gParticlePtrList_addObject(obj);
    }
}

/**
 * Race silver coin init behaviour.
 * Checks if in the correct modes, then sets the flag to active, otherwise inactive.
 * If the flag is inactive, destroy the object.
*/
void obj_init_silvercoin(Object *obj, UNUSED LevelObjectEntry_SilverCoin *entry) {
    obj->interactObj->unk14 = 2;
    obj->interactObj->unk11 = 0;
    obj->interactObj->unk10 = 0x1E;
    obj->action = SILVER_COIN_INACTIVE;
    obj->unk7C.word = 0;
    if (!is_in_tracks_mode()) {
        if (check_if_silver_coin_race() && !is_in_adventure_two()) {
            obj->action = SILVER_COIN_ACTIVE;
        } else {
            obj->action = SILVER_COIN_INACTIVE;
        }
    }
    if (obj->action == SILVER_COIN_INACTIVE) {
        obj->segment.trans.unk6 |= 0x600;
        gParticlePtrList_addObject(obj);
    }
}

/**
 * Race silver coin loop behaviour.
 * Can only be collected by players. Sets a flag equal to the player number when collected.
 * Under normal gameplay, that's 1 and 2, since the silver coin challenge can be done with at most two players.
 * When collected, the coins are hidden for that player, rather than being removed outright.
*/
void obj_loop_silvercoin(Object *obj, s32 updateRate) {
    ObjectInteraction *silverCoin4C;
    Object_Racer* racer;
    Object *racerObj;
    s32 temp;

    temp = func_8006C19C();
    if ((temp && obj->action != SILVER_COIN_INACTIVE) || (!temp && obj->action == SILVER_COIN_ACTIVE)) {
        silverCoin4C = obj->interactObj;
        if (silverCoin4C->distance < 80) {
            racerObj = (Object *) silverCoin4C->obj;
            if (racerObj != NULL && racerObj->segment.header->behaviorId == BHV_RACER) {
                racer = (Object_Racer *) racerObj->unk64;
                if (racer->playerIndex != PLAYER_COMPUTER) {
                    if (racer->raceFinished == FALSE && !(obj->action & (SILVER_COIN_COLLECTED << racer->playerIndex))) {
                        obj->action |= SILVER_COIN_COLLECTED << racer->playerIndex;
                        obj->unk7C.word = 0x10;
                        obj->segment.trans.unk6 |= 0x200 << racer->playerIndex;
                        play_sequence(SEQUENCE_SILVER_COIN_1 + racer->silverCoinCount);
                        racer->silverCoinCount++;
                    }
                }
            }
        }
        obj->segment.animFrame += 8 * updateRate;
    }
    if (obj->unk7C.word > 0) {
        obj->unk7C.word -= updateRate;
        obj->unk74 = 1;
        func_800AFC3C(obj, updateRate);
    }
}


void obj_init_worldkey(Object *obj, LevelObjectEntry_WorldKey *entry) {
    Settings *settings;
    obj->interactObj->unk14 = 2;
    obj->interactObj->unk11 = 0;
    obj->interactObj->unk10 = 0x1E;
    entry->unk8 &= 0xF;
    obj->action = entry->unk8;
    settings = get_settings();
    if (!is_in_tracks_mode() && !(settings->keys & (1 << obj->action))) {
        return;
    }
    gParticlePtrList_addObject(obj);
}

/**
 * Rotates the key and checks to see if the player grabbed it.
 */
void obj_loop_worldkey(Object *worldKeyObj, s32 updateRate) {
    Settings *settings;
    Object *playerObj;

    // Check if the player is near the key
    // "worldKeyObj->interactObj->distance" is the player's distance from the key (Up to 255).
    if (worldKeyObj->interactObj->distance < WORLD_KEY_GRAB_CHECK_RADIUS) {
        // "worldKeyObj->interactObj->obj" is only set when the player is within 255 units of
        // the key object, otherwise it is NULL.
        playerObj = worldKeyObj->interactObj->obj;
        if (playerObj != NULL) {
            if (playerObj->segment.header->behaviorId == BHV_RACER) {
                Object_WorldKey *obj64 = &playerObj->unk64->world_key;
                if (obj64->unk0 != -1) {
                    // Player has grabbed the key!
                    play_sequence(SEQUENCE_KEY_COLLECT);
                    settings = get_settings();
                    settings->keys |= 1 << worldKeyObj->action; // Set key flag
                    gParticlePtrList_addObject(worldKeyObj);   // Makes the key unload.
                }
            }
        }
    }

    // Rotate world key
    worldKeyObj->segment.trans.y_rotation += updateRate * 0x100;
}

void obj_init_weaponballoon(Object *obj, LevelObjectEntry_WeaponBalloon *entry) {
    s32 cheats;
    Object_WeaponBalloon *obj64;
    f32 scalef;

    obj->interactObj->unk14 = 2;
    obj->interactObj->unk11 = 4;
    obj->interactObj->unk10 = 0x14;

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

    if (obj->segment.unk38.byte.unk3A >= obj->segment.header->numberOfModelIds) {
        obj->segment.unk38.byte.unk3A = 0;
    }

    obj->segment.unk38.byte.unk3A = entry->balloonType;
    obj->unk78 = obj->segment.unk38.byte.unk3A;

    scalef = entry->scale & 0xFF;
    if (scalef < 10) {
        scalef = 10;
    }
    scalef /= 64.0f;

    obj64 = &obj->unk64->weapon_balloon;

    obj->segment.trans.scale = obj->segment.header->scale * scalef;
    obj64->unk0 = obj->segment.trans.scale;
    obj64->unk4 = 0;
    obj->unk7C.word = 0;

    if (get_filtered_cheats() & CHEAT_DISABLE_WEAPONS) {
        gParticlePtrList_addObject(obj);
    }
}

#ifdef NON_MATCHING
void obj_loop_weaponballoon(Object *obj, s32 updateRate) {
    s8 currentBalloon;
    Object_Racer *racer;
    Object_WeaponBalloon *balloon;
    s8 *balloonAsset;
    s8 prevQuantity;
    s8 levelMask;
    Object *interactObj;
    s32 newvar;

    balloon = (Object_WeaponBalloon *) obj->unk64;
    obj->segment.trans.scale = balloon->unk0 * (1.0f - (balloon->unk4 / 90.0f));
    if (obj->segment.trans.scale < 0.001f) {
        obj->segment.trans.scale = 0.001f;
    }
    if (obj->segment.trans.scale < 0.1f) {
        obj->segment.trans.unk6 |= 0x4000;
    } else {
        obj->segment.trans.unk6 &= 0xBFFF;
    }
    if (obj->unk7C.word > 0) {
        obj->unk74 = 1;
        func_800AFC3C(obj, updateRate);
        obj->unk7C.word -= updateRate;
    }
    if (balloon->unk4 != 0) {
        if (!(balloon->unk4 == 90 && obj->interactObj->distance < 45)) {
            balloon->unk4 = (balloon->unk4 - updateRate) - updateRate;
        }
        if (balloon->unk4 < 0) {
            balloon->unk4 = 0;
        }
    } else {
        if (obj->interactObj->distance < 45) {
            interactObj = obj->interactObj->obj;
            if (interactObj != NULL && interactObj->segment.header->behaviorId == BHV_RACER) {
                racer = (Object_Racer *) interactObj->unk64;
                    if (racer->vehicleID < VEHICLE_TRICKY|| racer->playerIndex != PLAYER_COMPUTER) {
                    currentBalloon = racer->balloon_type;
                    racer->balloon_type = obj->unk78;
                    if (currentBalloon == racer->balloon_type && racer->balloon_quantity != 0) {
                        racer->balloon_level++;
                    } else {
                        racer->balloon_level = 0;
                    }
                    // Disallow level 3 ballons in challenge mode
                    if (get_current_level_race_type() & RACETYPE_CHALLENGE) {
                        if (racer->balloon_level > 1) {
                            racer->balloon_level = 1;
                        }
                        // And instantly upgrade oil slicks to tripmines.
                        if (racer->balloon_type == BALLOON_TYPE_TRAP) {
                            racer->balloon_level = 1;
                        }
                    }
                    levelMask = 3; // 3 isn't an attainable level so the future check won't be true if the item's already max level.
                    if (get_filtered_cheats() & CHEAT_MAXIMUM_POWER_UP) {
                        racer->balloon_level = 2;
                    }
                    if (racer->balloon_level > 2) {
                        racer->balloon_level = 2;
                        levelMask = 2;
                    }
                    balloonAsset = (s8 *) get_misc_asset(MISC_ASSET_UNK0C);
                    prevQuantity = racer->balloon_quantity;
                    racer->balloon_quantity = balloonAsset[(racer->balloon_type * 10) + (racer->balloon_level * 2) + 1];
                    racer->unk209 |= 1;
                    if (get_number_of_active_players() < THREE_PLAYERS) {
                        obj->unk7C.word = 0x10;
                    }
                    if (racer->playerIndex == PLAYER_COMPUTER) {
                        play_sound_at_position(SOUND_BALLOON_POP, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
                    } else {
                        if (levelMask == racer->balloon_level) {
                            if (racer->raceFinished == FALSE) {
                                if (prevQuantity != racer->balloon_quantity) {
                                    func_800A7484(SOUND_VOICE_TT_POWERUP, 1.0f, racer->playerIndex);
                                    newvar = racer->balloon_level;
                                    if (racer->balloon_level > 2) {
                                        newvar = 2;
                                    }
                                    play_sound_global(SOUND_COLLECT_ITEM + newvar, NULL);
                                } else {
                                    play_sound_at_position(SOUND_BALLOON_POP, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
                                }
                            }
                        } else if (racer->raceFinished == FALSE) {
                            newvar = racer->balloon_level;
                            if (newvar > 0) {
                                func_800A7484(SOUND_VOICE_TT_POWERUP, 1.0f, racer->playerIndex);
                            }
                            play_sound_global(SOUND_COLLECT_ITEM + racer->balloon_level, NULL);
                        }
                    }
                    obj->unk74 = 1;
                    func_800AFC3C(obj, updateRate);
                    balloon->unk4 = 90;
                }
            }
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_weaponballoon.s")
#endif

void obj_init_wballoonpop(UNUSED Object *obj, UNUSED LevelObjectEntry_WBalloonPop *entry) {
}

void obj_loop_wballoonpop(UNUSED Object *obj, UNUSED s32 updateRate) {
}

void obj_init_weapon(Object *obj, UNUSED LevelObjectEntry_Weapon *entry) {
    obj->interactObj->unk14 = 2;
    obj->interactObj->unk11 = 0;
    obj->interactObj->unk10 = 0x18;
    obj->interactObj->unk12 = 0;
    obj->unk78 = (480);
    obj->unk7C.word = 0;
}

/**
 * Racer weapon loop behaviour.
 * Rockets will move forwards, or towards their victim.
 * Stationary traps will drop to the floor and stay there for a while before self-detonating.
*/
void obj_loop_weapon(Object *obj, s32 updateRate) {
    Object_Weapon *weapon = &obj->unk64->weapon;
    switch (weapon->weaponID) {
        case WEAPON_ROCKET_HOMING:
        case WEAPON_ROCKET:
            handle_rocket_projectile(obj, updateRate);
            break;
        case WEAPON_TRIPMINE:
        case WEAPON_OIL_SLICK:
        case WEAOON_BUBBLE_TRAP:
        case WEAPON_UNK_11:
            func_8003F2E8(obj, updateRate);
            break;
    }
    return;
}

/**
 * Firing a standard rocket makes it fly forward.
 * A homing rocket uses the checkpoint system to path towards its victim.
 * When it collides with a racer, they're launched into the air.
*/
void handle_rocket_projectile(Object *obj, s32 updateRate) {
    Object *interactObj;
    Object_Racer *weaponOwner;
    Object_Weapon *weapon;
    Object *temp_s1_2;
    f32 offsetZ;
    f32 offsetY;
    f32 offsetX;
    f32 spC4;
    f32 updateRateF;
    f32 posX;
    f32 posY;
    f32 posZ;
    f32 diffX;
    f32 diffY;
    f32 diffZ;
    s32 spA4;
    s32 size;
    s32 numCheckpoints;
    Object_Racer *racer;
    s8 sp97;
    Matrix mtxf;
    ObjectTransform trans;

    obj->interactObj->unk14 |= 0x100;
    weapon = (Object_Weapon *) obj->unk64;
    posX = obj->segment.trans.x_position;
    posY = obj->segment.trans.y_position;
    posZ = obj->segment.trans.z_position;
    trans.y_rotation = obj->segment.trans.y_rotation;
    trans.x_rotation = obj->segment.trans.x_rotation;
    trans.z_rotation = 0;
    trans.x_position = 0.0f;
    trans.y_position = 0.0f;
    trans.z_position = 0.0f;
    trans.scale = 1.0f;
    object_transform_to_matrix(mtxf, &trans);
    guMtxXFMF(mtxf, 0.0f, 0.0f, weapon->forwardVel, &obj->segment.x_velocity, &obj->segment.y_velocity, &obj->segment.z_velocity);
    updateRateF = updateRate;
    offsetX = obj->segment.trans.x_position + (obj->segment.x_velocity * updateRateF);
    offsetY = obj->segment.trans.y_position + (obj->segment.y_velocity * updateRateF);
    offsetZ = obj->segment.trans.z_position + (obj->segment.z_velocity * updateRateF);
    if (weapon->weaponID != WEAPON_MAGNET_LEVEL_3) {
        spC4 = 16.0f;
        func_80031130(1, &obj->segment.trans.x_position, &offsetX, -1);
        spA4 = 0;
        sp97 = -1;
        func_80031600(&obj->segment.trans.x_position, &offsetX, &spC4, &sp97, 1, &spA4);
        if (spA4 > 0) {
            if (func_8002ACD4(&diffX, &diffY, &diffZ) != 0) {
                obj->unk78 = 0;
            }
        }
    }
    diffX = offsetX - posX;
    diffY = offsetY - posY;
    diffZ = offsetZ - posZ;
    if (move_object(obj, diffX, diffY, diffZ) != 0) {
        obj->unk78 = 0;
    }
    diffX = ((diffX * diffX) + (diffZ * diffZ)) / updateRateF;
    diffZ = (weapon->forwardVel * weapon->forwardVel) / 2;
    if (diffX < diffZ) {
        obj->unk78 = 0;
    }
    if (weapon->weaponID == WEAPON_ROCKET_HOMING) {
        numCheckpoints = get_checkpoint_count();
        if (numCheckpoints > 0) {
            if (func_800185E4(weapon->checkpoint, obj, posX, posY, posZ, &weapon->checkpointDist, (u8* ) &sp97) == FALSE) {
                weapon->checkpoint++;
                if (weapon->checkpoint >= numCheckpoints) {
                    weapon->checkpoint = 0;
                }
            }
        } else {
            weapon->checkpoint = -1;
        }
    }
    if (weapon->weaponID == WEAPON_ROCKET_HOMING) {
        homing_rocket_prevent_overshoot(obj, updateRate, weapon);
    } else {
        rocket_prevent_overshoot(obj, updateRate, weapon);
    }
    //TODO: Fix these gotos.
    if (obj->interactObj->obj != NULL) {
        interactObj = obj->interactObj->obj;
        if (interactObj == weapon->owner) {
            if (obj->unk78 < (450) && obj->unk78 != 0) {
                goto block_25;
            }
            goto block_37;
        }
block_25:
        if (weapon->weaponID == WEAPON_ROCKET_HOMING) {
            if (interactObj == weapon->target) {
                size = 75;
            } else {
                size = 20;
            }
        } else {
            size = 60;
        }
        if (obj->interactObj->distance < size) {
            if (interactObj->segment.header->behaviorId == BHV_RACER) {
                racer = (Object_Racer *) interactObj->unk64;
                racer->attackType = ATTACK_EXPLOSION;
                weaponOwner = (Object_Racer *) weapon->owner->unk64;
                if (racer->playerIndex != PLAYER_COMPUTER || weaponOwner->playerIndex != PLAYER_COMPUTER) {
                    weaponOwner->boost_sound |= 2;
                }
                if (racer->raceFinished == FALSE) {
                    func_80072348(racer->playerIndex, 9);
                }
            }
            func_8003FC44(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 44, 17, 1.0f, 1);
            gParticlePtrList_addObject(obj);
            return;
        }
    }
block_37:
    obj->unk7C.word += updateRate;
    if (obj->unk60 != NULL) {
        temp_s1_2 = (Object *) obj->unk60->unk4;
        if (obj->unk7C.word < 8) {
            temp_s1_2->segment.trans.scale = obj->unk7C.word * 0.5f;
        } else if (obj->unk7C.word < 16) {
            temp_s1_2->segment.trans.scale = 4.0f - ((obj->unk7C.word - 8) * 0.25f);
        } else {
            temp_s1_2->segment.trans.scale = (sins_f(obj->unk7C.word << 12) * 0.25f) + 2.0f;
        }
    }
    obj->unk78 -= updateRate;
    if (obj->unk78 < 0) {
        func_8003FC44(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 44, 17, 1.0f, 1);
        gParticlePtrList_addObject(obj);
        return;
    }
}

/**
 * If a collision target is found for a level 1 or 3 rocket, reverse the velocity and set the next position target
 * to be right on top of them. This ensures a collision is guaranteed this frame.
 * This function also calls the function that plays the incoming rocket sound.
*/
void rocket_prevent_overshoot(Object *obj, UNUSED s32 updateRate, Object_Weapon *rocket) {
    Object *interactedObj;
    f32 dist;
    f32 diffX;
    f32 diffY;
    f32 diffZ;
    s32 angle;
    s32 angleDiff;

    if (obj->interactObj->distance < 80 || rocket->hitObj != NULL) {
        interactedObj = obj->interactObj->obj;
        if (interactedObj != NULL && interactedObj != rocket->owner && interactedObj->behaviorId == BHV_RACER) {
            rocket->hitObj = interactedObj;
        }
    }
    interactedObj = rocket->hitObj;
    if (rocket->hitObj != NULL) {
        diffX = interactedObj->segment.trans.x_position - obj->segment.trans.x_position;
        diffY = interactedObj->segment.trans.y_position - obj->segment.trans.y_position;
        diffZ = interactedObj->segment.trans.z_position - obj->segment.trans.z_position;
        dist = sqrtf((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ));
        if (dist > 0.0f) {
            rocket->forwardVel = -25.0f;
            angle = (arctan2_f(diffX, diffZ) - 0x8000) & 0xFFFF;
            angleDiff = angle - (obj->segment.trans.y_rotation & 0xFFFF);
            if (angleDiff > 0x8000) {
                angleDiff -= 0xFFFF;
            }
            if (angleDiff < -0x8000) {
                angleDiff += 0xFFFF;
            }
            if (angleDiff > 0x6000 || angleDiff < -0x6000) {
                obj->interactObj->obj = (Object *) interactedObj;
                obj->interactObj->distance = 1;
            }
            obj->segment.trans.x_rotation = arctan2_f(diffY, dist);
            obj->segment.trans.y_rotation = angle;
        }
    }
    play_rocket_trailing_sound(obj, rocket, SOUND_INCOMING_ROCKET);
}

/**
 * If a collision target is found for a level 2 rocket, reverse the velocity and set the next position target
 * to be right on top of them. This ensures a collision is guaranteed this frame.
 * This function also calls the function that plays the incoming rocket sound.
*/
void homing_rocket_prevent_overshoot(Object *obj, s32 updateRate, Object_Weapon *rocket) {
    Object *targetObj;
    Object_64 *racer;
    f32 dist;
    f32 diffX;
    f32 diffY;
    f32 diffZ;
    f32 distY; 
    s32 sp58;
    s32 angle;
    s32 sineY;
    s32 angleDiff;
    s32 shift;

    if (rocket->target != NULL) {
        targetObj = rocket->target;
        racer = targetObj->unk64;
        rocket->unk14 = racer->racer.unk1BA >> 1;
        rocket->unk16 = racer->racer.unk1BC >> 1;
        diffX = targetObj->segment.trans.x_position - obj->segment.trans.x_position;
        diffY = targetObj->segment.trans.y_position - obj->segment.trans.y_position;
        diffZ = targetObj->segment.trans.z_position - obj->segment.trans.z_position;
        dist = (diffX * diffX) + (diffZ * diffZ);
        distY = diffY * diffY;
        if (dist < 10000.0 && distY > 10000.0) {
            rocket->target = NULL;
            return;
        }
        dist = sqrtf(dist + distY);
        if (dist > 300.0f && rocket->checkpoint != -1 && rocket->hitObj == NULL) {
            sp58 = func_8001955C(obj, rocket->checkpoint, racer->racer.unk1C8, rocket->unk14, rocket->unk16, rocket->checkpointDist, &diffX, &diffY, &diffZ);
            sineY = arctan2_f(diffY, 500.0f) & 0xFFFF;
            shift = 3;
        } else {
            rocket->hitObj = targetObj;
            rocket->forwardVel = -25.0f;
            sp58 = NULL;
        }
        angle = (arctan2_f(diffX, diffZ) - 0x8000) & 0xFFFF;
        angleDiff = angle - (obj->segment.trans.y_rotation & 0xFFFF);
        WRAP(angleDiff, -0x8000, 0x8000);
        if (sp58 != NULL) {
            obj->segment.trans.y_rotation += (angleDiff * updateRate) >> shift;
            angleDiff = sineY - (obj->segment.trans.x_rotation & 0xFFFF);
            WRAP(angleDiff, -0x8000, 0x8000);
            obj->segment.trans.x_rotation += (angleDiff * updateRate) >> shift;
        } else {
            if (angleDiff > 0x6000 || angleDiff < -0x6000) {
                obj->interactObj->obj = targetObj;
                obj->interactObj->distance = 1;
            }
            obj->segment.trans.x_rotation = arctan2_f(diffY, dist) & 0xFFFFu;
            
            obj->segment.trans.y_rotation = angle;
        }
        
    }
    play_rocket_trailing_sound(obj, rocket, SOUND_HOMING_ROCKET);
    if (get_number_of_active_players() < 3) {
        obj->unk74 |= 1;
        func_800AFC3C(obj, updateRate);
    }
}

void func_8003F0D0(void) {
    D_8011D4DC = 0;
}

void func_8003F0DC(void) {
    D_8011D4DC--;
}

/**
 * Existing flying rockets that don't belong to that player will play a sound when flying.
 * This will check if that player is close enough to hear it, and whether to update an existing sound or play a new one.
*/
void play_rocket_trailing_sound(Object *obj, struct Object_Weapon *weapon, u16 soundID) {
    Object *racer;
    Object **racerGroup;
    f32 distance;
    s32 numRacers;
    f32 diffX;
    f32 diffZ;
    f32 diffY;
    s32 shouldPlaySound;
    f32 dist;
    s32 i;

    shouldPlaySound = FALSE;
    racerGroup = get_racer_objects_by_port(&numRacers);
    for (i = 0; i < numRacers; i++) {
        racer = racerGroup[i];
        if (weapon->owner != racerGroup[i] && racer->unk64->racer.playerIndex != PLAYER_COMPUTER) {
            diffX = racer->segment.trans.x_position - obj->segment.trans.x_position;
            diffY = racer->segment.trans.y_position - obj->segment.trans.y_position;
            diffZ = racer->segment.trans.z_position - obj->segment.trans.z_position;
            distance = ((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ));
            dist = func_80001CB8(soundID);
            if (distance <= dist * dist) {
                shouldPlaySound = TRUE;
            }
        }
    }
    if (shouldPlaySound) {
        if (weapon->unk1C == 0) {
            if (D_8011D4DC < 8) {
                play_sound_at_position(soundID, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 1, &weapon->unk1C);
                D_8011D4DC += 1;
            }
        } else {
            update_spatial_audio_position(weapon->unk1C, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
        }
    } else {
        if (weapon->unk1C != 0) {
            func_800096F8(weapon->unk1C);
            weapon->unk1C = 0;
            D_8011D4DC -= 1;
        }
    }
}

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
        newObj->segment.trans.scale = newObj->segment.trans.scale * 3.5f * scale;
    }
    if (arg4 != 0) {
        play_sound_at_position(arg4, x, y, z, 4, NULL);
    }
}

void obj_init_audio(Object *obj, LevelObjectEntry_Audio *entry) {
    Object_Audio *obj64;

    obj64 = &obj->unk64->audio;
    obj64->soundId = entry->unk8;
    obj64->unk2 = entry->unkA;
    obj64->unkC = entry->unkF;
    obj64->unk6 = entry->unkE;
    obj64->unk4 = entry->unkC;
    obj64->unk5 = entry->unkD;
    obj64->unkD = entry->unk10;
    obj64->unk8 = 0;
    if (ALBankFile_80115D14_GetSoundDecayTime(obj64->soundId)) {
        func_8000974C(obj64->soundId, entry->common.x, entry->common.y, entry->common.z,
            9, obj64->unk5, obj64->unk4, obj64->unk2, obj64->unkC,
            obj64->unk6, obj64->unkD, (s32 *) &obj64->unk8);
    } else {
        func_8000974C(obj64->soundId, entry->common.x, entry->common.y, entry->common.z,
            10, obj64->unk5, obj64->unk4, obj64->unk2, obj64->unkC,
            obj64->unk6, obj64->unkD, (s32 *) &obj64->unk8);
    }
    gParticlePtrList_addObject(obj);
}

/* Official name: audioLineInit */
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

/* Official name: texscrollInit */
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
    obj64->unk4 = entry->unkA;
    obj64->unk6 = entry->unkB;
    if (arg2 == 0) {
        obj64->unk8 = 0;
        obj64->unkA = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/obj_loop_texscroll.s")

/* Official name: rgbalightInit */
void obj_init_rgbalight(Object *obj, LevelObjectEntry_RgbaLight *entry, UNUSED s32 arg2) {
    obj->unk64 = func_80031CAC(obj, entry);
}

void obj_init_buoy_pirateship(Object *obj, UNUSED LevelObjectEntry_Buoy_PirateShip *entry, UNUSED s32 arg2) {
    obj->unk64 = func_800BE654(obj->segment.unk2C.half.lower, obj->segment.trans.x_position, obj->segment.trans.z_position);
    obj->interactObj->unk14 = 1;
    obj->interactObj->unk11 = 0;
    obj->interactObj->unk10 = 0x1E;
    obj->interactObj->unk12 = 0;
}

/**
 * Floating buoy loop behaviour.
 * Exists to serve as an outer bound for water courses.
 * All it does is stays afloat on water and scrolls through each texture.
*/
void obj_loop_buoy_pirateship(Object *obj, s32 updateRate) {
    if (obj->unk64 != NULL) {
        obj->segment.trans.y_position = func_800BEEB4(obj->unk64);
    }
    obj->segment.animFrame += updateRate * 8;
}

void obj_init_log(Object *obj, LevelObjectEntry_Log *entry, UNUSED s32 arg2) {
    f32 phi_f0;
    obj->unk64 = func_800BE654(obj->segment.unk2C.half.lower, obj->segment.trans.x_position, obj->segment.trans.z_position);
    obj->interactObj->unk14 = 1;
    obj->interactObj->unk11 = 2;
    obj->interactObj->unk10 = 0x1E;
    phi_f0 = entry->unk9 & 0xFF;
    if (phi_f0 < 10.0f) {
        phi_f0 = 10.0f;
    }
    phi_f0 /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * phi_f0;
    obj->segment.unk38.byte.unk3A = entry->unk8;
    obj->segment.trans.y_rotation = entry->unkA << 6 << 4;
}

/**
 * Spinning log loop behaviour.
 * Exists as a physical obstruction, will start spinning around on the spot when hit.
*/
void obj_loop_log(Object *obj, s32 updateRate) {
    Object *racerObj;
    Object_Log *log;
    f32 cosine;
    f32 sine;
    Object_Racer *racer;
    f32 diffZ;
    f32 diffX;

    log = (Object_Log *) obj->unk64;
    if (log != NULL) {
        obj->segment.trans.y_position = func_800BEEB4((Object_64 *) log);
    } else {
        obj->segment.trans.y_position = ((LevelObjectEntryCommon *) obj->segment.unk3C_a.level_entry)->y;
    }
    if (obj->unk5C->unk100 != NULL) {
        obj->unk7C.word++;
        racerObj = (Object *) obj->unk5C->unk100;
        if (racerObj->behaviorId == BHV_RACER) {
            racer = (Object_Racer *) racerObj->unk64;
            if (racer->velocity < -4.0f && racer->raceFinished == FALSE) {
                func_80072348(racer->playerIndex, 18);
            }
        }
        sine = sins_f(-obj->segment.trans.y_rotation);
        cosine = coss_f(-obj->segment.trans.y_rotation);
        
        // This looks a bit messy, but is required to match.
        diffX = obj->segment.trans.x_position - racerObj->segment.trans.x_position;
        diffZ = obj->segment.trans.z_position - racerObj->segment.trans.z_position;
        diffX = (diffX * cosine) + (diffZ * sine);
        diffZ = (racerObj->segment.x_velocity * sine) - (racerObj->segment.z_velocity * cosine);
        diffX *= diffZ;
        obj->unk78 -= (s32) (diffX / 4.0f);
        
        if (obj->unk78 > 0x200) {
            obj->unk78 = 0x200;
        }
        if (obj->unk78 < -0x200) {
            obj->unk78 = -0x200;
        }
    } else {
        if (obj->unk7C.word > 0) {
            obj->unk7C.word--;
        }
    }
    obj->segment.trans.y_position -= (f32) obj->unk7C.word;
    if (obj->unk78 > 0) {
        obj->unk78 -= updateRate;
        if (obj->unk78 < 0) {
            obj->unk78 = 0;
        }
    }
    if (obj->unk78 < 0) {
        obj->unk78 += updateRate;
        if (obj->unk78 > 0) {
            obj->unk78 = 0;
        }
    }
    obj->segment.trans.y_rotation += obj->unk78 * updateRate;
    obj->unk5C->unk100 = NULL;
}

/* Official name: weatherInit */
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
void obj_loop_weather(Object *obj, UNUSED s32 updateRate) {
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
      changeWeather(entry->unkA * 256, entry->unkC * 256, entry->unkE * 256, entry->unk10 * 257, entry->unk11 * 257, entry->unk12);
    }
  }
}

void obj_init_lensflare(Object *obj, UNUSED LevelObjectEntry_LensFlare *entry) {
    func_800AC8A8(obj);
}

void obj_init_lensflareswitch(Object *obj, LevelObjectEntry_LensFlareSwitch *entry, UNUSED s32 arg2) {
    cameraAddOverrideObject(obj);
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

/* Official name: bubblerInit */
void obj_init_bubbler(Object *obj, LevelObjectEntry_Bubbler *entry) {
    func_800AF134((Particle *) obj->unk6C, entry->unk9, entry->unk8, 0, 0, 0);
    obj->unk78 = entry->unkA;
}

void obj_loop_bubbler(Object *obj, s32 updateRate) {
    if (obj->unk78 >= get_random_number_from_range(0, 1024)) {
        obj->unk74 = 1;
    } else {
        obj->unk74 = 0;
    }
    if (get_number_of_active_players() < 2) {
        func_800AFC3C(obj, updateRate);
    }
}

void obj_init_boost(Object *obj, LevelObjectEntry_Boost *entry) {
    obj->unk64 = (Object_64 *) ((s32) get_misc_asset(MISC_ASSET_UNK14) + (entry->unk8[0] << 7));
    obj->segment.unk3C_a.level_entry = NULL;
}

void obj_init_unknown94(UNUSED Object *obj, UNUSED LevelObjectEntry_Unknown94 *entry, UNUSED s32 arg2) {
}

void obj_loop_unknown94(UNUSED Object *obj, s32 UNUSED updateRate) {
}

void obj_init_rangetrigger(UNUSED Object *obj, UNUSED LevelObjectEntry_RangeTrigger *entry) {
}

/* Official name: rangetriggerControl */
void obj_loop_rangetrigger(Object *obj, s32 updateRate) {
    LevelObjectEntry_RangeTrigger *level_entry;
    unk80042178 sp20;

    level_entry = &obj->segment.unk3C_a.level_entry->rangeTrigger;
    if (func_80016DE8(obj->segment.trans.x_position, 0, obj->segment.trans.z_position, (f32)level_entry->unk8, 1, &sp20) > 0) {
        obj->unk74 = level_entry->unkA;
    } else {
        obj->unk74 = 0;
    }
    func_800AFC3C(obj, updateRate);
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
        obj->segment.unk38.byte.unk3A = 1;
        /**
          * Don't spawn the chicken frog if drumstick is already unlocked, or
          * if the player hasn't completed the trophy races yet.
          */
        if (is_drumstick_unlocked() || (get_settings()->trophies & 0xFF) != 0xFF) {
            gParticlePtrList_addObject(obj);
        }
    } else {
        obj->segment.unk38.byte.unk3A = 0;
    }
}

/**
 * Overworld frog loop function.
 * Hops, skips, jumps around. Can be flattened by players.
 * If a Drumstick frog exists after beating all 4 trophy races, he can be squashed and will be unlocked as a playable character.
*/
void obj_loop_frog(Object *obj, s32 updateRate) {
    s32 i;
    s32 sp104;
    s32 var_v1;
    f32 sp6C;
    Object_Frog *frog;
    f32 diffX;
    f32 diffY;
    f32 diffZ;
    f32 cosine;
    f32 updateRateF;
    Object *racerObj;

    updateRateF = updateRate;
    frog = (Object_Frog *) obj->unk64;
    switch (frog->unk14) {
    case 0:
        sp104 = FALSE;
        if (frog->unk19 > 0) {
            frog->unk19 -= updateRate;
        }
        if (func_80016DE8(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 96.0f, 1, (unk80042178 *) &racerObj) > 0) {
            diffX = obj->segment.trans.x_position - racerObj->segment.trans.x_position;
            diffY = obj->segment.trans.y_position - racerObj->segment.trans.y_position;
            diffZ = obj->segment.trans.z_position - racerObj->segment.trans.z_position;
            if (frog->unk19 <= 0 && (diffX * diffX) + (diffY * diffY) + (diffZ * diffZ) < 40.0f * 40.0f) {
                if (frog->unk15 != 0) {
                    play_sound_at_position(SOUND_VOICE_DRUMSTICK_POSITIVE2, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
                    set_eeprom_settings_value(2);
                    set_magic_code_flags(CHEAT_CONTROL_DRUMSTICK);
                    func_8006D8A4();
                    gParticlePtrList_addObject(obj);
                    break;
                } else {
                    frog->unk14 = 2;
                    play_sound_at_position(SOUND_SPLAT, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
                }
            } else {
                frog->unk1C = 72.0f;
                if (frog->unk15 != 0) {
                    frog->unk1C *= 1.34f;
                }
                frog->unk1A = arctan2_f(-diffX, -diffZ) + 0x8000;
                sp104 = TRUE;
            }
        } else {
            frog->unk16 -= updateRate;
            if (frog->unk16 < 0) {
                sp104 = TRUE;
                frog->unk1C = get_random_number_from_range(0x28, 0x48);
                frog->unk1A = get_random_number_from_range(-0x4000, 0x4000) + obj->segment.trans.y_rotation;
            }
        }
        if (sp104) {
            for(i = 0, var_v1 = FALSE; i < 4 && var_v1 == FALSE; i++) {
                frog->unk28 = sins_f(frog->unk1A) * frog->unk1C;
                frog->unk2C = coss_f(frog->unk1A) * -frog->unk1C;
                diffX = (obj->segment.trans.x_position + frog->unk28) - frog->unk0;
                diffZ = (obj->segment.trans.z_position + frog->unk2C) - frog->unk8;
                if ((diffX * diffX) + (diffZ * diffZ) < frog->unk10) {
                    var_v1 = TRUE;
                } else {
                    frog->unk1A += 0x4000;
                }
            }
            if (var_v1 == FALSE) {
                diffX = frog->unk0 - obj->segment.trans.x_position;
                diffZ = frog->unk8 - obj->segment.trans.z_position;
                frog->unk1A = arctan2_f(diffX, diffZ);
            }
            if (frog->unk15 != 0) {
                play_sound_at_position(SOUND_VOICE_DRUMSTICK_POSITIVE6, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
            } else {
                play_sound_at_position(SOUND_RIBBIT, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
            }
            frog->unk14 = 1;
            frog->unk20 = obj->segment.trans.x_position;
            frog->unk24 = obj->segment.trans.z_position;
            frog->unk18 = 32;
            obj->segment.trans.y_rotation = -frog->unk1A;
        }
    default:
        break;
    case 1:
        frog->unk18 -= updateRate;
        if (frog->unk19 > 0) {
            frog->unk19 -= updateRate;
        }
        if (frog->unk18 < 0) {
            frog->unk14 = 0;
            frog->unk16 = get_random_number_from_range(0, 300);
            frog->unk18 = 0;
        }
        obj->segment.animFrame = ((32 - frog->unk18) << 3) / 3;
        cosine = (coss_f(frog->unk18 << 10) + 1.0f) * 0.5f;
        obj->segment.trans.x_position = frog->unk20;
        obj->segment.trans.z_position = frog->unk24;
        obj->segment.x_velocity = frog->unk28 * cosine;
        obj->segment.z_velocity = frog->unk2C * cosine;
        func_80011560();
        move_object(obj, obj->segment.x_velocity, 0.0f, obj->segment.z_velocity);
        if (func_8002BAB0(obj->segment.unk2C.half.lower, obj->segment.trans.x_position, obj->segment.trans.z_position, &sp6C) != 0) {
            obj->segment.trans.y_position = 0.0f;
            func_80011560();
            move_object(obj, 0.0f, sp6C, 0.0f);
        }
        if (frog->unk19 <= 0 && (frog->unk18 < 6 || frog->unk18 >= 27)) {
            if (func_80016DE8(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 40.0f, 0, (unk80042178 *) &racerObj) != 0) {
                if (frog->unk15 != 0) {
                    play_sound_at_position(SOUND_VOICE_DRUMSTICK_POSITIVE2, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
                    set_eeprom_settings_value(2);
                    set_magic_code_flags(CHEAT_CONTROL_DRUMSTICK);
                    func_8006D8A4();
                    gParticlePtrList_addObject(obj);
                } else {
                    frog->unk14 = 2;
                    play_sound_at_position(SOUND_SPLAT, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
                }
            }
        }
        break;
    case 2:
        frog->unk30 -= 0.15f * updateRateF;
        if (frog->unk30 < 0.05f) {
            frog->unk30 = 0.05f;
            frog->unk14 = 3;
            frog->unk16 = 40;
        }
        break;
    case 3:
        frog->unk16 -= updateRate; 
        if (frog->unk16 < 0) {
            frog->unk14 = 4;
            play_sound_at_position(SOUND_PLOP2, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
        }
        break;
    case 4:
        if (frog->unk30 > 1.0f) {
            frog->unk30 = 1.0f;
            frog->unk14 = 0;
            frog->unk16 = 0;
            frog->unk19 = 60;
        } else {
            frog->unk30 += 0.15f * updateRateF;
        }
        break;
    }
}

void obj_loop_pigrocketeer(Object *obj, s32 updateRate) {
    Object *someObj;
    Object_Wizpig2 *obj64;

    func_8001F460(obj, updateRate, obj);
    someObj = func_8000BF44(-1);

    if (someObj != NULL) {
        obj64 = &someObj->unk64->wizpig2;
        someObj->action = 0;
        if (obj64 != 0) {
            obj64->unk72 += updateRate;
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

/**
 * Overworld level name behaviour.
 * Placed at a level entrance, when a player gets near, display the level name on screen.
*/
void obj_loop_levelname(Object *obj, s32 updateRate) {
    s32 textWidth;
    s32 x1;
    s32 y1;
    s32 x2;
    s32 y2;
    char *levelName;
    Object *racerObj;
    f32 diffX;
    f32 diffZ;
    Object_LevelName_78 *temp_s0;

    racerObj = get_racer_object_by_port(0);
    if (racerObj != NULL) {
        diffX = obj->segment.trans.x_position - racerObj->segment.trans.x_position;
        diffZ = obj->segment.trans.z_position - racerObj->segment.trans.z_position;
        temp_s0 = (Object_LevelName_78 *) &obj->unk78;
        if ((diffX * diffX) + (diffZ * diffZ) < temp_s0->radius) {
            temp_s0->unk6 += updateRate * 16;
            if (temp_s0->unk6 > 256) {
                temp_s0->unk6 = 256;
            }
        } else {
            temp_s0->unk6 -= updateRate * 16;
            if (temp_s0->unk6 < 0) {
                temp_s0->unk6 = 0;
            }
        }
        if (temp_s0->unk6 > 0) {
            levelName = get_level_name(temp_s0->unk4);
            textWidth = (get_text_width(levelName, 0, 0) + 24) >> 1;
            x1 = (gScreenWidth / 2) - textWidth;
            x2 = textWidth + (gScreenWidth / 2);
            y1 = SCREEN_HEIGHT - 38;
            y2 = SCREEN_HEIGHT - 38 + 20;
            assign_dialogue_box_id(4);
            set_current_dialogue_box_coords(4, x1, y1, x2, y2);
            set_current_dialogue_background_colour(4, 128, 64, 128, (temp_s0->unk6 * 160) >> 8);
            set_current_text_background_colour(4, 0, 0, 0, 0);
            set_dialogue_font(4, 0);
            set_current_text_colour(4, 255, 255, 255, 0, (temp_s0->unk6 * 255) >> 8);
            render_dialogue_text(4, (x2 - x1) >> 1, ((y2 - y1) >> 1) + 2, levelName, 1, 12);
            open_dialogue_box(4);
        }
    }
}

void obj_loop_wizghosts(Object *obj, s32 updateRate) {
    func_8001F460(obj, updateRate, obj);
    obj->segment.animFrame = (obj->segment.animFrame + (updateRate * 8)) & 0xFF;
}

