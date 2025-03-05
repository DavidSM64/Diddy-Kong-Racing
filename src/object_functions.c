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
#include "audio_spatial.h"
#include "objects.h"
#include "particles.h"
#include "tracks.h"
#include "font.h"
#include "lights.h"
#include "game_ui.h"
#include "waves.h"
#include "audiosfx.h"
#include "math_util.h"
#include "game_text.h"
#include "fade_transition.h"
#include "audio_vehicle.h"
#include "object_models.h"
#include "libultra/src/libc/rmonPrintf.h"
#include "collision.h"
#include "joypad.h"
#include "printf.h"
#include "PRinternal/viint.h"
#include "common.h"

/************ .data ************/

// Unsure about the signed/unsigned with these arrays.
FadeTransition gTajTransformTransitionEnd = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_INVERT, FADE_COLOR_WHITE, 7, 3);
FadeTransition gTajTransition = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 30, -1);

Vertex gCharacterFlagVertices[4] = {
    { -256, 256, 0, 255, 255, 255, 255 },
    { 256, 256, 0, 255, 255, 255, 255 },
    { 256, -256, 0, 255, 255, 255, 255 },
    { -256, -256, 0, 255, 255, 255, 255 },
};

VertexPosition D_800DC9A8[6] = {
    { 0, 64, -64 }, { 0, -64, -64 }, { 0, 64, 32 }, { 0, -64, 32 }, { 0, 64, 64 }, { 0, -64, 64 },
};

UNUSED s32 D_800DC9CC = 0;

// Fish Object Related
Triangle D_800DC9D0[8] = {
    { { { 0, 0, 3, 1 } }, { { { 4, 0 } } }, { { { 1, 4 } } }, { { { 4, 4 } } } },
    { { { 0, 0, 2, 3 } }, { { { 4, 0 } } }, { { { 1, 0 } } }, { { { 1, 4 } } } },
    { { { 0, 2, 5, 3 } }, { { { 1, 0 } } }, { { { 0, 4 } } }, { { { 1, 4 } } } },
    { { { 0, 2, 4, 5 } }, { { { 1, 0 } } }, { { { 0, 0 } } }, { { { 0, 4 } } } },
    { { { 0, 0, 1, 3 } }, { { { 4, 0 } } }, { { { 4, 4 } } }, { { { 1, 4 } } } },
    { { { 0, 0, 3, 2 } }, { { { 4, 0 } } }, { { { 1, 4 } } }, { { { 1, 0 } } } },
    { { { 0, 2, 3, 5 } }, { { { 1, 0 } } }, { { { 1, 4 } } }, { { { 0, 4 } } } },
    { { { 0, 2, 5, 4 } }, { { { 1, 0 } } }, { { { 0, 4 } } }, { { { 0, 0 } } } },
};

u8 D_800DCA50[8] = { 2, 5, 6, 3, 10, 8, 7, 9 };
u8 D_800DCA58[9] = { 2, 5, 6, 3, 10, 8, 7, 9, 11 };
u8 D_800DCA64[9] = { 2, 5, 6, 3, 10, 8, 7, 9, 12 };
u8 D_800DCA70[10] = { 2, 5, 6, 3, 10, 8, 7, 9, 11, 12 };
u8 D_800DCA7C[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

u8 D_800DCA88[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s8 D_800DCA94[8] = { 0x00, 0x00, 0x01, 0x01, 0x02, 0x00, 0x00, 0x00 };

s8 D_800DCA9C[12] = { 0x00, 0x01, 0x01, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

// Butterfly Object Related
Triangle D_800DCAA8[8] = {
    { { { 0, 0, 3, 1 } }, { { { 0, 0 } } }, { { { -1, -1 } } }, { { { 0, -1 } } } },
    { { { 0, 0, 2, 3 } }, { { { 0, 0 } } }, { { { -1, 0 } } }, { { { -1, -1 } } } },
    { { { 0, 2, 5, 3 } }, { { { -1, 0 } } }, { { { 0, -1 } } }, { { { -1, -1 } } } },
    { { { 0, 2, 4, 5 } }, { { { -1, 0 } } }, { { { 0, 0 } } }, { { { 0, -1 } } } },
    { { { 0, 0, 1, 3 } }, { { { 0, 0 } } }, { { { 0, -1 } } }, { { { -1, -1 } } } },
    { { { 0, 0, 3, 2 } }, { { { 0, 0 } } }, { { { -1, -1 } } }, { { { -1, 0 } } } },
    { { { 0, 2, 3, 5 } }, { { { -1, 0 } } }, { { { -1, -1 } } }, { { { 0, -1 } } } },
    { { { 0, 2, 5, 4 } }, { { { -1, 0 } } }, { { { 0, -1 } } }, { { { 0, 0 } } } },
};

VertexPosition D_800DCB28[6] = {
    { -64, 0, 32 }, { -64, 0, -32 }, { 0, 0, 32 }, { 0, 0, -32 }, { 64, 0, 32 }, { 64, 0, -32 },
};

/*******************************/

/************ .bss ************/

f32 gNPCPosY;
s32 gTajSoundMask;
s32 gTTSoundMask;
s32 gRocketSoundTimer;
s8 gTajDialogueChoice;
s16 gTajSoundID; // Taj Voice clips

/******************************/

/**
 * Level scenery init behaviour.
 * Set rotation and scale based off spawn info.
 * Also have the option based off spawn info to add solidity to the hitbox.
 */
void obj_init_scenery(Object *obj, LevelObjectEntry_Scenery *entry) {
    f32 radius;
    obj->segment.trans.flags |= OBJ_FLAGS_UNK_0002;
    radius = entry->radius & 0xFF;
    if (radius < 10) {
        radius = 10;
    }
    radius /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * radius;
    obj->shadow->scale = obj->segment.header->shadowScale * radius;
    obj->segment.object.modelIndex = entry->modelIndex;
    obj->segment.trans.rotation.y_rotation = U8_ANGLE_TO_U16(entry->angleY);
    if (entry->solid) {
        obj->interactObj->flags = INTERACT_FLAGS_SOLID;
        obj->interactObj->unk11 = 1;
        obj->interactObj->hitboxRadius = 20;
        obj->interactObj->pushForce = 0;
        obj->interactObj->unk16 = -5;
        obj->interactObj->unk17 = entry->solid;
    }
    if (obj->segment.object.modelIndex >= obj->segment.header->numberOfModelIds) {
        obj->segment.object.modelIndex = 0;
    }
    obj->properties.scenery.interactObj = NULL;
    obj->properties.common.unk4 = 0;
}

/**
 * Level scenery loop behaviour.
 * When hit by a racer, give it an elastic behaviour as feedback.
 */
void obj_loop_scenery(Object *obj, s32 updateRate) {
    ObjPropertyScenery *properties;
    s32 particleFlagShift;

    if (obj->interactObj != NULL) {
        properties = &obj->properties.scenery;
        if (properties->hitTimer > 0) {
            properties->hitTimer -= updateRate;
        }
        if (obj->interactObj->flags & INTERACT_FLAGS_COLLIDED && properties->hitTimer <= 0) {
            play_sound_at_position(SOUND_TWANG, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                   obj->segment.trans.z_position, 4, NULL);
            properties->interactObj = obj->interactObj->obj;
            properties->angleVel = 0x71C;
            properties->hitTimer = 10;
            if (get_number_of_active_players() < 2) {
                if (obj->segment.header->particleCount > 0) {
                    if (obj->segment.header->particleCount == 1) {
                        particleFlagShift = 0;
                    } else {
                        particleFlagShift = get_random_number_from_range(0, obj->segment.header->particleCount - 1);
                    }
                    obj->particleEmitFlags = OBJ_EMIT_PARTICLE_1 << particleFlagShift;
                    obj_spawn_particle(obj, LOGIC_30FPS);
                }
            }
        } else if (properties->hitTimer <= 0) {
            properties->interactObj = NULL;
        }
        obj->segment.trans.rotation.z_rotation = properties->angleVel;
        properties->angleVel = (properties->angleVel * -200) >> 8;
    }
}

/**
 * Bubbler boss obstacle init behaviour.
 * Sets hitbox info so it can be interacted with.
 */
void obj_init_fireball_octoweapon(Object *obj, UNUSED LevelObjectEntry_Fireball_Octoweapon *entry) {
    obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE;
    obj->interactObj->unk11 = 0;
}

/**
 * Bubbler boss obstacle loop behaviour.
 * Representing the landmines and bubbletraps that Bubbler throws during the race.
 * When ran into by a player, they will suffer like they usually would when running into a landmine or a bubble trap.
 */
void obj_loop_fireball_octoweapon(Object *obj, s32 updateRate) {
    Object *someObj;
    f32 diff;
    f32 updateRateF;
    UNUSED s32 pad;
    Object_Fireball_Octoweapon *weapon;
    Object_Racer *racer;
    UNUSED s32 pad2[6];
    ObjectInteraction *interactObj;
    s32 soundMask;
    f32 waveHeight;

    someObj = obj->properties.fireball.obj;
    updateRateF = updateRate;
    if (osTvType == OS_TV_TYPE_PAL) {
        updateRateF *= 1.2;
    }
    if (obj->behaviorId == BHV_FIREBALL_OCTOWEAPON_2 && obj->properties.fireball.timer < 0) {
        obj->segment.trans.x_position = 0.0f;
        obj->segment.trans.y_position = 0.0f;
        obj->segment.trans.z_position = 0.0f;
        ignore_bounds_check();
        move_object(obj, someObj->segment.trans.x_position, someObj->segment.trans.y_position,
                    someObj->segment.trans.z_position);
    } else {
        diff = (someObj->segment.trans.x_position - obj->segment.trans.x_position) * 0.1;
        if (diff > 10.0) {
            diff = 10.0f;
        }
        if (diff < -10.0) {
            diff = -10.0f;
        }
        obj->segment.x_velocity += (diff - obj->segment.x_velocity) * 0.125 * updateRateF;
        diff = (someObj->segment.trans.y_position - obj->segment.trans.y_position) * 0.1;
        if (diff > 10.0) {
            diff = 10.0f;
        }
        if (diff < -10.0) {
            diff = -10.0f;
        }
        obj->segment.y_velocity += (diff - obj->segment.y_velocity) * 0.125 * updateRateF;
        diff = (someObj->segment.trans.z_position - obj->segment.trans.z_position) * 0.1;
        if (diff > 10.0) {
            diff = 10.0f;
        }
        if (diff < -10.0) {
            diff = -10.0f;
        }
        obj->segment.z_velocity += (diff - obj->segment.z_velocity) * 0.125 * updateRateF;
        if (sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) +
                  (obj->segment.z_velocity * obj->segment.z_velocity)) > 0.5) {
            obj->segment.trans.rotation.y_rotation = arctan2_f(obj->segment.x_velocity, obj->segment.z_velocity);
            obj->segment.trans.rotation.x_rotation -= updateRate * 0x200;
        }
        move_object(obj, obj->segment.x_velocity * updateRateF, obj->segment.y_velocity * updateRateF,
                    obj->segment.z_velocity * updateRateF);
        if (obj->objectID == ASSET_OBJECT_ID_OCTOBOMB) {
            if (get_wave_properties(obj->segment.trans.y_position, &waveHeight, NULL)) {
                obj->segment.trans.y_position = waveHeight;
            }
        }
    }
    obj->segment.animFrame += updateRate * 10;
    weapon = (Object_Fireball_Octoweapon *) obj->unk64;
    interactObj = obj->interactObj;
    if ((interactObj->obj)) {
        if ((interactObj->distance < 60)) {
            someObj = interactObj->obj;
            if ((someObj->segment.header->behaviorId == BHV_RACER)) {
                racer = (Object_Racer *) someObj->unk64;
                if (racer->playerIndex != PLAYER_COMPUTER) {
                    if (obj->behaviorId == BHV_FIREBALL_OCTOWEAPON) {
                        racer->attackType = ATTACK_EXPLOSION;
                        obj->properties.fireball.timer = 20;
                        obj_spawn_effect(obj->segment.trans.x_position, obj->segment.trans.y_position,
                                         obj->segment.trans.z_position, ASSET_OBJECT_ID_BOMBEXPLOSION, SOUND_EXPLOSION,
                                         1.0f, 1);
                        free_object(obj);
                    } else if (obj->properties.fireball.timer > 0) {
                        racer->bubbleTrapTimer = 60;
                        obj->properties.fireball.timer = -60;
                        obj->properties.fireball.obj = someObj;
                        sound_play(SOUND_BUBBLE_RISE, &weapon->soundMask);
                    }
                }
            }
        }
    }
    if (obj->behaviorId == BHV_FIREBALL_OCTOWEAPON) {
        obj->particleEmitFlags = OBJ_EMIT_PARTICLE_1;
        obj_spawn_particle(obj, updateRate);
        obj->properties.fireball.timer -= updateRate;
        if (obj->properties.fireball.timer < 0) {
            if (obj->objectID == ASSET_OBJECT_ID_OCTOBOMB) {
                free_object(obj);
                obj_spawn_effect(obj->segment.trans.x_position, obj->segment.trans.y_position,
                                 obj->segment.trans.z_position, ASSET_OBJECT_ID_BOMBEXPLOSION, SOUND_EXPLOSION, 1.0f,
                                 1);
            }
            obj->segment.trans.scale *= 0.9; //!@Delta
            if (obj->segment.trans.scale < 0.5) {
                free_object(obj);
            }
        }
    } else {
        if (obj->properties.fireball.timer < 0) {
            obj->properties.fireball.timer += updateRate;
            if (obj->properties.fireball.timer >= 0) {
                obj->properties.fireball.timer = 0;
            }
        } else {
            obj->properties.fireball.timer -= updateRate;
            if (obj->properties.fireball.timer <= 0) {
                obj->properties.fireball.timer = 0;
            }
        }
        if (obj->properties.fireball.timer == 0) {
            soundMask = weapon->soundMask;
            if (soundMask != NULL) {
                sound_stop(soundMask);
            }
            play_sound_at_position(SOUND_POP, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                   obj->segment.trans.z_position, 4, NULL);
            free_object(obj);
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
    obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE | INTERACT_FLAGS_UNK_0020;
    obj->interactObj->unk11 = 0;
    laserGun = &obj->unk64->lasergun;
    laserGun->targeting = entry->targeting;
    laserGun->fireRate = entry->fireRate;
    laserGun->laserDuration = entry->laserDuration;
    laserGun->radius = entry->radius;
    laserGun->fireTimer = laserGun->fireRate;
    obj->segment.trans.rotation.y_rotation = entry->angleY << 4 << 4; // Not sure about the shift amounts here, but it
    obj->segment.trans.rotation.x_rotation = entry->angleX << 4 << 4; // just needs to be 2 left shifts to add up to 8.
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
    ObjectInteraction *interactObj;
    LevelObjectEntryCommon spawnObj;

    lasergun = (Object_LaserGun *) obj->unk64;
    if (lasergun->fireTimer > 0) {
        lasergun->fireTimer -= updateRate;
    } else {
        interactObj = obj->interactObj;
        if (lasergun->radius >= interactObj->distance) {
            if (lasergun->targeting) {
                racerObj = interactObj->obj;
                if (racerObj != NULL && racerObj->behaviorId == BHV_RACER) {
                    diffX = obj->segment.trans.x_position - racerObj->segment.trans.x_position;
                    diffY = obj->segment.trans.y_position - racerObj->segment.trans.y_position;
                    diffZ = obj->segment.trans.z_position - racerObj->segment.trans.z_position;
                    distance = sqrtf((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ));
                    if (distance > 10.0f) {
                        diffX /= distance;
                        diffY /= distance;
                        diffZ /= distance;
                        obj->segment.trans.rotation.y_rotation = (arctan2_f(diffX, diffZ) - 0x8000) & 0xFFFF;
                        obj->segment.trans.rotation.x_rotation = arctan2_f(diffY, 1.0f) & 0xFFFF;
                    }
                }
            }
            lasergun->fireTimer = lasergun->fireRate;
            spawnObj.x = obj->segment.trans.x_position;
            spawnObj.y = obj->segment.trans.y_position;
            spawnObj.z = obj->segment.trans.z_position;
            spawnObj.size = sizeof(LevelObjectEntryCommon);
            spawnObj.objectID = ASSET_OBJECT_ID_LASERBOLT;
            play_sound_at_position(SOUND_LASER_GUN, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                   obj->segment.trans.z_position, 4, NULL);
            laserBoltObj = spawn_object(&spawnObj, 1);
            if (laserBoltObj != NULL) {
                laserBoltObj->segment.level_entry = NULL;
                laserBoltObj->segment.trans.rotation.y_rotation = obj->segment.trans.rotation.y_rotation;
                laserBoltObj->segment.trans.rotation.x_rotation = obj->segment.trans.rotation.x_rotation;
                laserBoltObj->properties.lasergun.timer = lasergun->laserDuration;
                laserBoltObj->properties.lasergun.obj = lasergun;
                trans.x_position = 0.0f;
                trans.y_position = 0.0f;
                trans.z_position = 0.0f;
                trans.scale = 1.0f;
                trans.rotation.y_rotation = obj->segment.trans.rotation.y_rotation;
                trans.rotation.x_rotation = obj->segment.trans.rotation.x_rotation;
                trans.rotation.z_rotation = 0;
                object_transform_to_matrix(mtx, &trans);
                diffX = 30.0f; // Need to use diffX to match.
                if (lasergun->targeting == FALSE) {
                    diffX = 45.0f;
                }
                guMtxXFMF(mtx, 0.0f, 0.0f, diffX, &laserBoltObj->segment.x_velocity, &laserBoltObj->segment.y_velocity,
                          &laserBoltObj->segment.z_velocity);
            }
        }
    }
}

/**
 * Laser Bolt init behaviour.
 * Sets hitbox data so it can be interacted with.
 */
void obj_init_laserbolt(Object *obj, UNUSED LevelObjectEntry_Laserbolt *entry) {
    obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE;
    obj->interactObj->unk11 = 0;
}

/**
 * Laser Bolt init behaviour.
 * Move in a set direction, until it either times out, hits a racer, or hits a wall.
 */
void obj_loop_laserbolt(Object *obj, s32 updateRate) {
    f32 updateRateF;

    Object *racerObj;

    Object_LaserGun *laserGun;
    Object_Laser *laser;

    s8 delete; // Boolean
    s8 surface;
    Vec3f dir;
    f32 radius;
    s32 hasCollision; // Boolean

    delete = FALSE;
    updateRateF = updateRate;
    if (osTvType == OS_TV_TYPE_PAL) {
        updateRateF *= 1.2;
    }
    dir.x = obj->segment.trans.x_position + (obj->segment.x_velocity * updateRateF);
    dir.y = obj->segment.trans.y_position + (obj->segment.y_velocity * updateRateF);
    dir.z = obj->segment.trans.z_position + (obj->segment.z_velocity * updateRateF);
    radius = 9.0f;

    func_80031130(1, &obj->segment.trans.x_position, &dir.x, -1);
    hasCollision = FALSE;
    func_80031600(&obj->segment.trans.x_position, (f32 *) &dir, &radius, &surface, TRUE, &hasCollision);
    if (hasCollision) {
        obj->segment.x_velocity = (dir.x - obj->segment.trans.x_position) / updateRateF;
        obj->segment.y_velocity = (dir.y - obj->segment.trans.y_position) / updateRateF;
        obj->segment.z_velocity = (dir.z - obj->segment.trans.z_position) / updateRateF;
    }
    move_object(obj, obj->segment.x_velocity * updateRateF, obj->segment.y_velocity * updateRateF,
                obj->segment.z_velocity * updateRateF);
    if (hasCollision) {
        obj_spawn_effect(obj->segment.trans.x_position, obj->segment.trans.y_position - 36.0f,
                         obj->segment.trans.z_position, ASSET_OBJECT_ID_BOMBEXPLOSION, SOUND_NONE, 0.2, 0);
        delete = TRUE;
    }

    if (obj->properties.lasergun.timer > 0) {
        obj->properties.lasergun.timer -= updateRate;
    } else {
        delete = TRUE;
    }

    if (obj->interactObj->distance < 80) {
        racerObj = obj->interactObj->obj;
        if (racerObj && racerObj->behaviorId == BHV_RACER) {
            laser = &racerObj->unk64->laser;
            delete = TRUE;
            if (laser->unk0 != -1) {
                laser->unk187 = 1;
            }
            laserGun = obj->properties.lasergun.obj;
            if (laserGun) {
                laserGun->fireTimer = 180;
            }
            delete = TRUE;
            obj_spawn_effect(obj->segment.trans.x_position, obj->segment.trans.y_position - 36.0f,
                             obj->segment.trans.z_position, ASSET_OBJECT_ID_BOMBEXPLOSION, SOUND_EXPLOSION, 0.5, 0);
        }
    }
    if (delete) {
        free_object(obj);
    }
}

/**
 * Torch / Mist init behaviour.
 * Sets scale and animation speed based off spawn info.
 */
void obj_init_torch_mist(Object *obj, LevelObjectEntry_Torch_Mist *entry) {
    f32 radius = entry->radius & 0xFF;
    if (radius < 10.0f) {
        radius = 10.0f;
    }
    radius /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * radius;
    obj->properties.speed.speed = entry->animSpeed;
}

/**
 * Torch / Mist loop behaviour.
 * Updates the animation frame based on spawn info's animation speed.
 */
void obj_loop_torch_mist(Object *obj, s32 updateRate) {
    obj->segment.animFrame += obj->properties.speed.speed * updateRate;
}

/**
 * Effect box init behaviour.
 * Does nothing.
 */
void obj_init_effectbox(UNUSED Object *obj, UNUSED LevelObjectEntry_EffectBox *entry) {
}

/**
 * Effect box loop behaviour.
 * Searches for any racers that are inside the region.
 * Applies an effect to their weight and velocity.
 */
void obj_loop_effectbox(Object *obj, UNUSED s32 updateRate) {
    Object **racers;
    LevelObjectEntry_EffectBox *effectBoxEntry;
    s32 numRacers;
    Object *curRacerObj;
    Object_Racer *curRacer;
    f32 sinAngle;
    f32 zDiff;
    f32 yExtentsHalf;
    f32 xDiff;
    f32 yExtents;
    f32 cosAngle;
    f32 xExtents;
    f32 zExtents;
    f32 yDiff;
    s32 i;

    effectBoxEntry = (LevelObjectEntry_EffectBox *) obj->segment.level_entry;
    racers = get_racer_objects(&numRacers);
    cosAngle = coss_f(-(effectBoxEntry->unkB * 256));
    sinAngle = sins_f(-(effectBoxEntry->unkB * 256));
    xExtents = effectBoxEntry->unk8 * 3;
    yExtents = effectBoxEntry->unk9 * 3;
    zExtents = effectBoxEntry->unkA * 3;
    for (i = 0; i < numRacers; i++) {
        curRacerObj = racers[i];
        xDiff = curRacerObj->segment.trans.x_position - obj->segment.trans.x_position;
        yDiff = curRacerObj->segment.trans.y_position - obj->segment.trans.y_position;
        zDiff = curRacerObj->segment.trans.z_position - obj->segment.trans.z_position;
        if (-yExtents < yDiff && yDiff < yExtents) {
            yExtentsHalf = (xDiff * cosAngle) + (zDiff * sinAngle);
            if (-xExtents < yExtentsHalf && yExtentsHalf < xExtents) {
                zDiff = (-xDiff * sinAngle) + (zDiff * cosAngle);
                if (-zExtents < zDiff && zDiff < zExtents) {
                    yExtentsHalf = yExtents / 2;
                    curRacer = &curRacerObj->unk64->racer;
                    curRacer->unk1FE = effectBoxEntry->unkC;
                    curRacer->unk1FF = effectBoxEntry->unkD;
                    if (yExtentsHalf < yDiff && curRacer->unk1FE == 1) {
                        xDiff = (yDiff - yExtentsHalf) / yExtentsHalf;
                        yDiff = (1.0 - xDiff);
                        curRacer->unk1FF *= yDiff;
                    }
                }
            }
        }
    }
}

/**
 * Trophy Cabinet loop behaviour.
 * Sets rotation and hitbox data so it can be collided with.
 */
void obj_init_trophycab(Object *obj, LevelObjectEntry_TrophyCab *entry) {
    obj->interactObj->flags = INTERACT_FLAGS_SOLID;
    obj->interactObj->unk11 = 2;
    obj->segment.trans.rotation.y_rotation = U8_ANGLE_TO_U16(entry->angleY);
}

/**
 * Trophy Cabinet loop behaviour.
 * Displays the dialogue when ran into.
 * Has unused behaviour that presumably would've handled activating the dialogue from here.
 */
void obj_loop_trophycab(Object *obj, s32 updateRate) {
    Settings *settings;
    Object_TrophyCabinet *gfxData;
    UNUSED f32 dist;
    LevelObjectEntryCommon newObject;
    LevelHeader *header;
    Object *tempObj;
    f32 diffX;
    s32 dialogueID;
    f32 diffZ;
    UNUSED s32 pad2;
    s32 worldBalloons;
    s32 bossFlags;

    settings = get_settings();
    header = get_current_level_header();
    gfxData = (Object_TrophyCabinet *) obj->unk64;
    if (obj->properties.trophyCabinet.trophy == FALSE) {
        if (header->race_type != RACETYPE_CUTSCENE_2 && header->race_type != RACETYPE_CUTSCENE_1) {
            obj->properties.trophyCabinet.trophy = TRUE;
            if ((settings->trophies >> (((settings->worldId - 1) ^ 0) * 2)) & 3) { // Fakematch
                newObject.objectID = ASSET_OBJECT_ID_TROPHY;
                newObject.x = obj->segment.level_entry->animation.common.x;
                newObject.y = obj->segment.level_entry->animation.common.y;
                newObject.z = obj->segment.level_entry->animation.common.z;
                newObject.size = sizeof(LevelObjectEntryCommon);
                tempObj = spawn_object(&newObject, 1);
                if (tempObj != NULL) {
                    tempObj->segment.level_entry = NULL;
                    tempObj->segment.trans.rotation.y_rotation = obj->segment.trans.rotation.y_rotation;
                }
            }
        }
    }
    obj->shading->ambient = 0.612f;
    obj->shading->brightness = 0.0f;
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
        if (obj->properties.trophyCabinet.action == NULL && textbox_visible() == FALSE) {
            if (obj->unk5C->unk100 != NULL) {
                if (gfxData->unk4 == 0) {
                    if (worldBalloons) {
                        obj->properties.trophyCabinet.action = 1;
                        sound_play(SOUND_VOICE_TT_TROPHY_RACE, NULL);
                        hud_speedometre_reset();
                    } else {
                        // Text for "TROPHY RACE" "TO ENTER THE TROPHY RACE, YOU MUST COMPLETE ALL THE TASKS FROM THIS
                        // WORLD. KEEP RACING!"
                        set_current_text(ASSET_GAME_TEXT_4);
                        gfxData->unk4 = 180;
                        gfxData->unk0 = 140;
                        music_jingle_voicelimit_set(16);
                        music_fade(-8);
                        music_jingle_play(SEQUENCE_NO_TROPHY_FOR_YOU);
                    }
                }
            }
        }
        if (gfxData->unk0 && music_jingle_playing() == SEQUENCE_NONE) {
            if (updateRate < gfxData->unk0) {
                gfxData->unk0 -= updateRate;
            } else {
                gfxData->unk0 = 0;
                music_fade(8);
                music_jingle_voicelimit_set(6);
            }
        }
        if (obj->unk5C->unk100 != NULL || textbox_visible()) {
            gfxData->unk4 = 180;
        }
        if (gfxData->unk4 > 0) {
            gfxData->unk4 -= updateRate;
        } else {
            gfxData->unk4 = 0;
        }
        if (obj->properties.trophyCabinet.action == 1) {
            minimap_opacity_set(3);
            hud_visibility(0);
            dialogueID = npc_dialogue_loop(DIALOGUE_TROPHY);
            if (dialogueID) {
                obj->properties.trophyCabinet.action = 0;
                dialogue_npc_finish(4);
                if (dialogueID == 1) {
                    begin_trophy_race_teleport();
                    obj->properties.trophyCabinet.action = 2;
                } else {
                    hud_visibility(1);
                }
            }
            disable_racer_input();
        }
        obj->unk5C->unk100 = NULL;
        if (worldBalloons) {
            obj->shading->brightness = 0.552f;
        }
    }
}

/**
 * Fire Mountain egg init function.
 * Sets up hitbox data so it can be picked up.
 */
void obj_init_collectegg(Object *obj, UNUSED LevelObjectEntry_CollectEgg *entry) {
    obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE;
    obj->interactObj->unk11 = 0;
    obj->interactObj->hitboxRadius = 20;
    obj->interactObj->pushForce = 0;
}

/**
 * Fire Mountain egg loop function.
 * Spawn on SURFACE_EGG_SPAWN, and if dropped on surfaces SURFACE_EGG_01 to SURFACE_EGG_04, begin ticking down to hatch.
 */
void obj_loop_collectegg(Object *obj, s32 updateRate) {
    Object_CollectEgg *egg;
    Object *racerObj;
    Object_Racer *racer;
    f32 dir[3];
    f32 radius;
    f32 updateRateF;
    s32 hasCollision;
    s8 surface;

    egg = (Object_CollectEgg *) obj->unk64;
    updateRateF = updateRate;
    if (osTvType == OS_TV_TYPE_PAL) {
        updateRateF *= 1.2;
    }
    switch (egg->status) {
        case EGG_SPAWNED:
            try_to_collect_egg(obj, egg);
            break;
        case EGG_MOVING:
            obj->segment.trans.flags &= (0xFFFF - OBJ_FLAGS_INVISIBLE);
            dir[0] = obj->segment.trans.x_position + (obj->segment.x_velocity * updateRateF);
            dir[1] = obj->segment.trans.y_position + (obj->segment.y_velocity * updateRateF);
            dir[2] = obj->segment.trans.z_position + (obj->segment.z_velocity * updateRateF);
            radius = 9.0f;
            func_80031130(1, &obj->segment.trans.x_position, dir, -1);
            hasCollision = FALSE;
            surface = SURFACE_DEFAULT;
            func_80031600(&obj->segment.trans.x_position, dir, &radius, &surface, TRUE, &hasCollision);
            obj->segment.x_velocity = (dir[0] - obj->segment.trans.x_position) / updateRateF;
            obj->segment.y_velocity = (dir[1] - obj->segment.trans.y_position) / updateRateF;
            obj->segment.z_velocity = (dir[2] - obj->segment.trans.z_position) / updateRateF;
            obj->segment.trans.x_position = dir[0];
            obj->segment.trans.y_position = dir[1];
            obj->segment.trans.z_position = dir[2];
            obj->segment.y_velocity -= 0.5;
            obj->segment.x_velocity *= 0.98;
            obj->segment.z_velocity *= 0.98;
            obj->segment.y_velocity *= 0.95;
            // Destroy the egg if it lands on an invalid surface.
            if (obj->segment.trans.y_position < -2000.0f ||
                (hasCollision && (surface < SURFACE_EGG_SPAWN || surface > SURFACE_EGG_04))) {
                if (egg->spawnerObj != NULL) {
                    egg->spawnerObj->properties.eggSpawner.egg = NULL;
                }
                free_object(obj);
            }
            if (hasCollision && surface == SURFACE_EGG_SPAWN) {
                egg->status = EGG_SPAWNED;
                obj->segment.x_velocity = 0.0f;
                obj->segment.z_velocity = 0.0f;
            }
            if (hasCollision && surface >= SURFACE_EGG_01 && surface <= SURFACE_EGG_04) {
                egg->racerID = surface - SURFACE_EGG_01;
                egg->status = EGG_IN_BASE;
                racerObj = get_racer_object(egg->racerID);
                if (racerObj != NULL) {
                    racer = (Object_Racer *) racerObj->unk64;
                    racer->eggHudCounter += 1;
                }
                egg->hatchTimer = 600;
                obj->segment.x_velocity = 0.0f;
                obj->segment.z_velocity = 0.0f;
            }
            break;
        case EGG_IN_BASE:
            egg->hatchTimer -= updateRate;
            racerObj = get_racer_object(egg->racerID);
            if (racerObj != NULL) {
                racer = (Object_Racer *) racerObj->unk64;
            }
            if (egg->hatchTimer <= 0) {
                if (racerObj != NULL) {
                    racer->lap += 1;
                }
                egg->status = EGG_HATCHED;
                egg->spawnerObj->properties.eggSpawner.egg = NULL;
            }
            if (egg->hatchTimer < 540) {
                try_to_collect_egg(obj, egg);
            }
            if (racerObj != NULL && egg->status != EGG_IN_BASE) {
                racer->eggHudCounter -= 1;
            }
            break;
        case EGG_HATCHED:
            racerObj = get_racer_object(egg->racerID);
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

/**
 * Egg Spawner init behaviour.
 * Does nothing.
 */
void obj_init_eggcreator(UNUSED Object *obj, UNUSED LevelObjectEntry_EggCreator *entry) {
}

/**
 * Egg Spawner Sign init behaviour.
 * Action is set to 0 if it has no egg child object.
 * Spawns an egg and tracks its existence.
 */
void obj_loop_eggcreator(Object *obj, UNUSED s32 updateRate) {
    LevelObjectEntryCommon spawnObj;
    Object *eggObj;

    if (obj->properties.eggSpawner.egg == NULL) {
        spawnObj.x = obj->segment.trans.x_position;
        spawnObj.y = obj->segment.trans.y_position;
        spawnObj.z = obj->segment.trans.z_position;
        spawnObj.size = sizeof(LevelObjectEntryCommon);
        spawnObj.objectID = ASSET_OBJECT_ID_COLLECTEGG;
        eggObj = spawn_object(&spawnObj, 1);
        if (eggObj != NULL) {
            Object_EggCreator *eggSpawner = &eggObj->unk64->egg_creator;
            eggSpawner->currentEgg = obj;
            obj->properties.eggSpawner.egg = eggObj;
            eggObj->segment.level_entry = NULL;
        }
    }
}

/**
 * Trophy Race Sign init behaviour.
 * Sets size and rotation based off spawn info.
 */
void obj_init_lighthouse_rocketsignpost(Object *obj, LevelObjectEntry_Lighthouse_RocketSignpost *entry) {
    f32 radius = entry->radius & 0xFF;
    if (radius < 10) {
        radius = 10;
    }
    radius /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * radius;
    obj->segment.trans.rotation.y_rotation = U8_ANGLE_TO_U16(entry->angleY);
    if (obj->segment.object.modelIndex >= obj->segment.header->numberOfModelIds) {
        obj->segment.object.modelIndex = 0;
    }
    obj->interactObj->flags = INTERACT_FLAGS_SOLID;
    obj->interactObj->unk11 = 2;
    obj->interactObj->hitboxRadius = 20;
    obj->interactObj->pushForce = 0;
}

/**
 * Trophy Race Sign loop behaviour.
 * Checks if the player is nearby and if they have tried to initiate dialogue.
 * It then calls the function to check if it should start the lighthouse cutscene.
 */
void obj_loop_rocketsignpost(Object *obj, UNUSED s32 updateRate) {
    Object *playerObj;
    ObjectInteraction *interactObj;

    playerObj = get_racer_object(PLAYER_ONE);
    if (playerObj != NULL) {
        interactObj = obj->interactObj;
        if (interactObj->distance < 200) {
            if (playerObj == interactObj->obj) {
                // Detect if the player honks or slams into the signpost.
                if ((get_buttons_pressed_from_player(PLAYER_ONE) & Z_TRIG) || playerObj == obj->unk5C->unk100) {
                    begin_lighthouse_rocket_cutscene();
                }
            }
        }
    }
    obj->interactObj->distance = 0xFF;
}

/**
 * Air/Water Zipper init behaviour.
 * Sets scale and angle based on entry data.
 */
void obj_init_airzippers_waterzippers(Object *obj, LevelObjectEntry_AirZippers_WaterZippers *entry) {
    ObjectHeader *objHeader;
    f32 radius;

    radius = entry->radius & 0xFF;
    if (radius < 10.0f) {
        radius = 10.0f;
    }
    objHeader = obj->segment.header;
    radius /= 64;
    obj->segment.trans.scale = objHeader->scale * radius;
    obj->segment.trans.rotation.y_rotation = U8_ANGLE_TO_U16(entry->angleY);
    if (obj->segment.object.modelIndex >= objHeader->numberOfModelIds) {
        obj->segment.object.modelIndex = 0;
    }
    obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE;
    obj->interactObj->unk11 = 0;
    obj->interactObj->hitboxRadius = 20;
    obj->interactObj->pushForce = 0;
    if (get_filtered_cheats() & CHEAT_TURN_OFF_ZIPPERS) {
        free_object(obj);
    }
}

/**
 * Air/Water Zipper loop behaviour.
 * Searches for a racer among its interactions.
 * If a racer passes over it, set the value to initiate a boost on their end to true.
 * Will turn invisible and intangible if there are no hovercraft or airplanes being used.
 */
void obj_loop_airzippers_waterzippers(Object *obj, UNUSED s32 updateRate) {
    Object *curRacerObj;
    Object_Racer *racer;
    f32 diffX;
    f32 diffY;
    f32 diffZ;
    s32 numObjects;
    Object **racerObjs;
    s32 i;

    if (find_non_car_racers() == FALSE) {
        obj->segment.trans.flags |= OBJ_FLAGS_INVISIBLE;
    } else {
        obj->segment.trans.flags &= (0xFFFF - OBJ_FLAGS_INVISIBLE);
    }
    if (obj->interactObj->distance < 100 && !(obj->segment.trans.flags & OBJ_FLAGS_INVISIBLE)) {
        racerObjs = get_racer_objects(&numObjects);
        for (i = 0; i < numObjects; i++) {
            curRacerObj = racerObjs[i];
            racer = &curRacerObj->unk64->racer;
            if (racer->zipperDirCorrection == FALSE && racer->boostTimer < 15) {
                diffX = curRacerObj->segment.trans.x_position - obj->segment.trans.x_position;
                diffY = curRacerObj->segment.trans.y_position - obj->segment.trans.y_position;
                diffZ = curRacerObj->segment.trans.z_position - obj->segment.trans.z_position;
                if ((s32) sqrtf((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ)) < 100) {
                    racer->zipperDirCorrection = TRUE;
                    racer->zipperObj = obj;
                }
            }
        }
    }
}

/**
 * Ground Zipper init behaviour.
 * Sets scale and angle based on entry data.
 */
void obj_init_groundzipper(Object *obj, LevelObjectEntry_GroundZipper *entry) {
    ObjectHeader *header;
    f32 radius;

    radius = entry->scale & 0xFF;
    if (radius < 10.0f) {
        radius = 10.0f;
    }
    radius /= 64;
    header = obj->segment.header;
    obj->segment.trans.scale = header->scale * radius;
    obj->shadow->scale = header->shadowScale * radius;
    obj->segment.trans.rotation.y_rotation = U8_ANGLE_TO_U16(entry->angleY);
    if (obj->segment.object.modelIndex >= obj->segment.header->numberOfModelIds) {
        obj->segment.object.modelIndex = 0;
    }
    obj->properties.zipper.radius = (s32) (28.0f * radius) + 15;
    if (obj->properties.zipper.radius < 0) {
        obj->properties.zipper.radius = 0;
    }
    if (obj->properties.zipper.radius > 255) {
        obj->properties.zipper.radius = 255;
    }
    obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE;
    obj->interactObj->unk11 = 0;
    obj->interactObj->hitboxRadius = 20;
    obj->interactObj->pushForce = 0;
    obj->interactObj->unk16 = -0x64;
    obj->interactObj->unk17 = 0x64;
    if (get_filtered_cheats() & CHEAT_TURN_OFF_ZIPPERS) {
        free_object(obj);
    }
}

/**
 * Ground Zipper loop behaviour.
 * Searches for a racer among its interactions.
 * If a racer passes over it, initiate a boost, which can be empowered by releasing the A button.
 */
void obj_loop_groundzipper(Object *obj, UNUSED s32 updateRate) {
    Object *racerObj;
    Object_Racer *racer;
    f32 diffX;
    f32 diffY;
    s32 numObjects;
    f32 diffZ;
    Object **racerObjs;
    s32 i;

    obj->segment.trans.flags &= (0xFFFF - OBJ_FLAGS_INVISIBLE);
    obj->segment.trans.flags |= OBJ_FLAGS_SHADOW_ONLY;
    get_racer_object(PLAYER_ONE); // Unused. I guess the developers forgot to remove this?
    if (obj->interactObj->distance < obj->properties.zipper.radius) {
        racerObjs = get_racer_objects(&numObjects);
        for (i = 0; i < numObjects; i++) {
            racerObj = racerObjs[i];
            racer = &racerObj->unk64->racer;
            if (racer->boostTimer < 15 && racer->groundedWheels) {
                diffX = racerObj->segment.trans.x_position - obj->segment.trans.x_position;
                diffY = racerObj->segment.trans.y_position - obj->segment.trans.y_position;
                diffZ = racerObj->segment.trans.z_position - obj->segment.trans.z_position;
                if ((s32) sqrtf((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ)) < obj->properties.zipper.radius) {
                    if (racer->playerIndex != PLAYER_COMPUTER) {
                        sound_play_spatial(SOUND_ZIP_PAD_BOOST, racerObj->segment.trans.x_position,
                                           racerObj->segment.trans.y_position, racerObj->segment.trans.z_position,
                                           NULL);
                    }
                    racer->boostTimer = normalise_time(45);
                    racer->boostType = BOOST_LARGE;
                    if (racer->throttleReleased) {
                        racer->boostType |= BOOST_SMALL_FAST;
                    }
                    if (racer->raceFinished == FALSE) {
                        rumble_set(racer->playerIndex, RUMBLE_TYPE_8);
                    }
                }
            }
        }
    }
}

/**
 * Time Trial Ghost init func.
 * Sets the timestamp frame to 0
 */
void obj_init_timetrialghost(Object *obj, UNUSED LevelObjectEntry_TimeTrial_Ghost *entry) {
    obj->properties.timeTrial.timestamp = 0;
    obj->properties.timeTrial.header = obj->segment.header;
}

/**
 * Time Trial Ghost loop func.
 * Reads the ghost data associated with the header,
 * then has the position and rotation manually set to simulate time trial playback.
 * Has particle data, but never used.
 */
void obj_loop_timetrialghost(Object *obj, s32 updateRate) {
    Object *someObj;
    Object *someOtherObj;
    Object_UnkId58 *someOtherObj64;
    Object_60 *obj60;
    s8 vehicleID;

    obj->segment.object.animationID = 0;
    obj->segment.animFrame = 40;
    if (get_race_countdown() == 0) {
        obj->properties.timeTrial.timestamp += updateRate;
    }
    set_ghost_position_and_rotation(obj);
    obj_spawn_particle(obj, updateRate);
    someOtherObj = get_racer_object(PLAYER_ONE);
    someOtherObj64 = &someOtherObj->unk64->unkid58;
    obj60 = obj->unk60;
    if (obj60->unk0 == 1) {
        vehicleID = someOtherObj64->vehicleID;
        if (vehicleID == VEHICLE_HOVERCRAFT || vehicleID == VEHICLE_PLANE) {
            someObj = (Object *) obj60->unk4[0];
            someObj->segment.trans.rotation.y_rotation = 0x4000;
            someObj->segment.object.modelIndex++;
            someObj->segment.object.modelIndex &= 1;
        }
    }
}

/**
 * Character World Portrait init func.
 * Sets the scale, but the actual geometry data is built during the update loop.
 * These are seen in the challenge maps.
 */
void obj_init_characterflag(Object *obj, LevelObjectEntry_CharacterFlag *entry) {
    f32 radius;
    obj->properties.characterFlag.playerID = entry->playerIndex;
    obj->properties.characterFlag.characterID = -1; // Set to -1 so the loop func builds the gfx data.
    obj->segment.trans.rotation.y_rotation = U8_ANGLE_TO_U16(entry->angleY);
    radius = entry->radius & 0xFF;
    if (radius < 10.0f) {
        radius = 10.0f;
    }
    radius /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * radius;
}

/**
 * Character World Portrait loop func.
 * If there's no associated character ID, build the portrait geometry
 * and set the texture based on the character ID, then write the character ID.
 */
void obj_loop_characterflag(Object *obj, UNUSED s32 updateRate) {
    s32 temp_t4;
    s32 temp_t5;
    Object *racerObj;
    Object_CharacterFlag *flag;
    Object_Racer *racer;

    if (obj->properties.characterFlag.characterID < 0) {
        racerObj = get_racer_object(obj->properties.characterFlag.playerID);
        if (racerObj != NULL) {
            flag = &obj->unk64->character_flag;
            racer = &racerObj->unk64->racer;
            obj->properties.characterFlag.characterID = racer->characterId;
            if (obj->properties.characterFlag.characterID < 0 ||
                obj->properties.characterFlag.characterID >= NUMBER_OF_CHARACTERS) {
                obj->properties.characterFlag.characterID = 0;
            }
            flag->vertices = gCharacterFlagVertices;
            flag->texture = (TextureHeader *) &obj->unk68[obj->properties.characterFlag.characterID]->texHeader;
            temp_t4 = (flag->texture->width - 1) << 21;
            temp_t5 = (flag->texture->height - 1) << 5;
            // 0x40 = Draw backface
            flag->triangles[0].vertices = (0x40 << 24) | (0 << 16) | (1 << 8) | 3;
            flag->triangles[0].uv0.texCoords = 0;
            flag->triangles[0].uv1.texCoords = temp_t4;
            flag->triangles[0].uv2.texCoords = temp_t5;
            flag->triangles[1].vertices = (0x40 << 24) | (1 << 16) | (2 << 8) | 3;
            flag->triangles[1].uv0.texCoords = temp_t4;
            flag->triangles[1].uv1.texCoords = (temp_t4 | temp_t5);
            flag->triangles[1].uv2.texCoords = temp_t5;
        }
    }
}

/**
 * If interacted by a racer, attach itself to the player and mark as invisible
 * if the player is not already carrying an egg.
 */
void try_to_collect_egg(Object *obj, Object_CollectEgg *egg) {
    Object_64 *racer;
    Object *interactedObj;
    Matrix mat;
    ObjectTransform transF;

    if (obj->interactObj->distance < 40) {
        interactedObj = obj->interactObj->obj;
        if (interactedObj->segment.header->behaviorId == BHV_RACER) {
            racer = interactedObj->unk64;
            if (racer->racer.held_obj == NULL) {
                egg->status = EGG_COLLECTED;
                obj->segment.trans.flags |= OBJ_FLAGS_INVISIBLE;
                racer->racer.held_obj = obj;
                transF.rotation.y_rotation = -interactedObj->segment.trans.rotation.y_rotation;
                transF.rotation.x_rotation = -interactedObj->segment.trans.rotation.x_rotation;
                transF.rotation.z_rotation = -interactedObj->segment.trans.rotation.z_rotation;
                transF.scale = 1.0f;
                transF.x_position = -interactedObj->segment.trans.x_position;
                transF.y_position = -interactedObj->segment.trans.y_position;
                transF.z_position = -interactedObj->segment.trans.z_position;
                object_transform_to_matrix_2(mat, &transF);
                guMtxXFMF(mat, obj->segment.trans.x_position, obj->segment.trans.y_position,
                          obj->segment.trans.z_position, &obj->segment.trans.x_position, &obj->segment.trans.y_position,
                          &obj->segment.trans.z_position);
                obj->segment.trans.x_position /= interactedObj->segment.trans.scale;
                obj->segment.trans.y_position /= interactedObj->segment.trans.scale;
                obj->segment.trans.z_position /= interactedObj->segment.trans.scale;
            }
        }
    }
}

/**
 * Hub world T.T init behaviour.
 * Sets hitbox data to make him solid.
 */
void obj_init_stopwatchman(Object *obj, UNUSED LevelObjectEntry_StopWatchMan *entry) {
    Object_TT *tt;
    obj->interactObj->flags = INTERACT_FLAGS_SOLID;
    obj->interactObj->unk11 = 0;
    obj->interactObj->hitboxRadius = 30;
    obj->interactObj->pushForce = 0;
    tt = &obj->unk64->tt;
    tt->unkD = 0xFF;
    tt->unk0 = 0.0f;
    gTTSoundMask = NULL;
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
    UNUSED s32 pad;
    s32 angleDiff;
    s32 index;
    UNUSED s32 pad2;
    Object_Racer *racer;
    LevelHeader *header;
    struct WaterProperties **water;

    tempPosY = obj->segment.trans.y_position;
    updateRateF = updateRate;
    if (osTvType == OS_TV_TYPE_PAL) {
        updateRateF *= 1.2;
    }
    tt = (Object_NPC *) obj->unk64;
    if (obj->segment.animFrame == 0) {
        if (tt->animFrameF > 1.0) {
            tt->animFrameF = 0.0f;
        }
    }
    header = get_current_level_header();
    distance = 0.0f;
    obj->segment.x_velocity = 0.0f;
    obj->segment.z_velocity = 0.0f;
    racerObj = get_racer_object(PLAYER_ONE);
    if (racerObj != NULL) {
        racer = (Object_Racer *) racerObj->unk64;
        diffX = ((racerObj->segment.trans.x_position - (racer->ox1 * 50.0f)) - (racer->ox3 * 5.0f)) -
                obj->segment.trans.x_position;
        diffZ = ((racerObj->segment.trans.z_position - (racer->oz1 * 50.0f)) - (racer->oz3 * 5.0f)) -
                obj->segment.trans.z_position;
        distance = sqrtf((diffX * diffX) + (diffZ * diffZ));
        angleDiff = arctan2_f(racerObj->segment.trans.x_position - obj->segment.trans.x_position,
                              racerObj->segment.trans.z_position - obj->segment.trans.z_position) -
                    (racerObj->segment.trans.rotation.y_rotation & 0xFFFF);
        if (angleDiff > 0x8000) {
            angleDiff = -0xFFFF;
        }
        if (angleDiff < -0x8000) {
            angleDiff = 0xFFFF;
        }
        if (racer->exitObj != NULL) {
            obj->properties.npc.action = TT_MODE_ROAM;
            obj->properties.npc.timer = 1;
        }
    }
    index = get_buttons_pressed_from_player(PLAYER_ONE);
    if (obj->properties.npc.action == TT_MODE_ROAM && distance < 300.0 && obj->properties.npc.timer == 0) {
        if (angleDiff > -0x2000 && angleDiff < 0x2000) {
            if ((obj->interactObj->flags & INTERACT_FLAGS_PUSHING && racerObj == obj->interactObj->obj) ||
                index & Z_TRIG) {
                if (index & Z_TRIG) {
                    play_char_horn_sound(racerObj, racer);
                }
                obj->properties.npc.action = TT_MODE_APPROACH_PLAYER;
                get_fog_settings(PLAYER_ONE, &tt->fogNear, &tt->fogFar, &tt->fogR, &tt->fogG, &tt->fogB);
                slowly_change_fog(PLAYER_ONE, 128, 128, 255, 900, 998, 240);
                music_channel_reset_all();
                music_play(SEQUENCE_TTS_THEME);
                if (racerObj != NULL) {
                    racer_sound_free(racerObj);
                    racer->vehicleSound = NULL;
                }
            }
        }
    }
    if (obj->properties.npc.action != TT_MODE_ROAM) {
        disable_racer_input();
        minimap_fade(3);
    }
    if (obj->properties.npc.action >= TT_MODE_TURN_TOWARDS_PLAYER) {
        index = npc_dialogue_loop(DIALOGUE_TT);
    } else {
        dialogue_npc_finish(2);
        index = 0;
    }
    switch (obj->properties.npc.action) {
        case TT_MODE_APPROACH_PLAYER:
            obj->segment.object.animationID = 0;
            tt->nodeCurrent = 255;
            if (distance < 100.0) {
                racer_set_dialogue_camera();
            }
            if (distance > 10.0) {
                angleDiff = (arctan2_f(diffX / distance, diffZ / distance) -
                             (obj->segment.trans.rotation.y_rotation & 0xFFFF)) +
                            0x8000;
                WRAP(angleDiff, -0x8000, 0x8000);
                if (angleDiff > 0) {
                    if (angleDiff < 0x10) {
                        angleDiff = 0x10;
                    }
                }
                obj->segment.trans.rotation.y_rotation += angleDiff >> 4;
                distance = -2.0f;
                if (angleDiff > 0x800 || angleDiff < -0x800) {
                    distance = -0.5f;
                }
                tt->forwardVel += (distance - tt->forwardVel) * 0.125;
                obj->segment.x_velocity = sins_f(obj->segment.trans.rotation.y_rotation) * tt->forwardVel;
                obj->segment.z_velocity = coss_f(obj->segment.trans.rotation.y_rotation) * tt->forwardVel;
                tt->animFrameF -= (tt->forwardVel * 2 * updateRateF);
            } else {
                obj->properties.npc.action = TT_MODE_TURN_TOWARDS_PLAYER;
            }
            move_object(obj, obj->segment.x_velocity * updateRateF, obj->segment.y_velocity * updateRateF,
                        obj->segment.z_velocity * updateRateF);
            set_pause_lockout_timer(1);
            break;
        case TT_MODE_TURN_TOWARDS_PLAYER:
            racer_set_dialogue_camera();
            obj->segment.object.animationID = 0;
            tt->animFrameF += 3.0 * updateRateF;
            angleDiff =
                (racerObj->segment.trans.rotation.y_rotation - (obj->segment.trans.rotation.y_rotation & 0xFFFF)) +
                0x8000;
            WRAP(angleDiff, -0x8000, 0x8000);
            if (angleDiff > 0) {
                if (angleDiff < 0x10) {
                    angleDiff = 0x10;
                }
            }
            obj->segment.trans.rotation.y_rotation += (angleDiff >> 4);
            obj->segment.x_velocity = diffX * 0.05;
            obj->segment.z_velocity = diffZ * 0.05;
            if (angleDiff < 0x500) {
                if (angleDiff >= -0x4FF) {
                    obj->properties.npc.action = TT_MODE_DIALOGUE;
                    play_tt_voice_clip(SOUND_VOICE_TT_INTRO, 1); // Hi there, I'm T.T!
                }
            }
            move_object(obj, obj->segment.x_velocity * updateRateF, obj->segment.y_velocity * updateRateF,
                        obj->segment.z_velocity * updateRateF);
            break;
        case TT_MODE_DIALOGUE:
            obj->segment.x_velocity = diffX * 0.05;
            obj->segment.z_velocity = diffZ * 0.05;
            obj->segment.object.animationID = 1;
            tt->animFrameF += 1.0 * updateRateF;
            racer_set_dialogue_camera();
            if (index == 3) {
                obj->properties.npc.action = TT_MODE_DIALOGUE_END;
                if (is_time_trial_enabled()) {
                    play_tt_voice_clip(SOUND_VOICE_TT_SEE_YOU, 1);
                } else {
                    play_tt_voice_clip(SOUND_VOICE_TT_OK, 1);
                }
                slowly_change_fog(PLAYER_ONE, tt->fogR, tt->fogG, tt->fogB, tt->fogNear, tt->fogFar, 180);
                music_play(header->music);
                music_dynamic_set(header->instruments);
                racer->vehicleSound = func_80004B40(racer->characterId, racer->vehicleID);
            }
            obj->properties.npc.timer = 180;
            move_object(obj, obj->segment.x_velocity * updateRateF, obj->segment.y_velocity * updateRateF,
                        obj->segment.z_velocity * updateRateF);
            break;
        case TT_MODE_DIALOGUE_END:
            tt->animFrameF += 1.0 * updateRateF;
            racer_set_dialogue_camera();
            if (obj->properties.npc.timer < 140) {
                obj->properties.npc.timer += 60;
                obj->properties.npc.action = TT_MODE_ROAM;
                obj->segment.object.animationID = 0;
            }
            break;
        default:
            obj->segment.object.animationID = 0;
            tt->forwardVel = 0.0f;
            if (tt->nodeCurrent == NODE_NONE) {
                tt->nodeCurrent = ainode_find_nearest(obj->segment.trans.x_position, obj->segment.trans.y_position,
                                                      obj->segment.trans.z_position, FALSE);
                if (tt->nodeCurrent != NODE_NONE) {
                    tt->nodeBack2 = func_8001CC48(tt->nodeCurrent, -1, 0);
                    tt->nodeForward1 = func_8001CC48(tt->nodeBack2, tt->nodeCurrent, 0);
                    tt->nodeForward2 = func_8001CC48(tt->nodeForward1, tt->nodeBack2, 0);
                    tt->nodeBack1 = tt->nodeCurrent;
                }
            } else {
                diffZ = func_8001C6C4((Object_64 *) tt, obj, updateRateF, 1.0f, 0);
                tt->animFrameF += diffZ * 1.5;
            }
            break;
    }
    obj->segment.trans.y_position = tempPosY;
    index = func_8002B0F4(obj->segment.object.segmentID, obj->segment.trans.x_position, obj->segment.trans.z_position,
                          &water);
    if (index != 0) {
        index--;
        while (index >= 0) {
            if ((water[index]->type != WATER_CALM) && (water[index]->type != WATER_WAVY) &&
                (water[index]->rotY > 0.0)) {
                obj->segment.trans.y_position = water[index]->waveHeight;
            }
            index--;
        }
    }
    obj->segment.trans.rotation.x_rotation = 0;
    obj->segment.trans.rotation.z_rotation = 0;
    if (obj->properties.npc.action != TT_MODE_ROAM) {
        gNPCPosY = obj->segment.trans.y_position;
    }
    obj->segment.animFrame = 1.0 * tt->animFrameF;
    func_80061C0C(obj);
    if (0) {} // Fakematch
    if (obj->properties.npc.timer > 0) {
        obj->properties.npc.timer -= updateRate;
    } else {
        obj->properties.npc.timer = 0;
    }
}

/**
 * If TT is currently talking, clear the audio associated with gTTSoundMask,
 * then play the new sound ID in its place.
 */
void play_tt_voice_clip(u16 soundID, s32 interrupt) {
    if (gTTSoundMask && interrupt & 1) {
        sound_stop(gTTSoundMask); // This is likely wrong and will need to be fixed
        gTTSoundMask = NULL;
    }
    if (gTTSoundMask == NULL) {
        sound_play(soundID, &gTTSoundMask);
    }
}

void obj_init_fish(Object *fishObj, LevelObjectEntry_Fish *fishEntry, s32 param) {
    Object_Fish *fish;
    s32 pad0[2];
    f32 xPos;
    f32 zPos;
    f32 sins104;
    s32 uMask;
    s32 vMask;
    f32 coss104;
    s32 i;
    f32 tempxPos;

    fish = &fishObj->unk64->fish;
    fish->unk100 = fishEntry->unkE << 4;
    fish->unk104 = fishEntry->unkF << 8;
    fish->unk114 = fishEntry->unk8;
    fish->unk118 = fishEntry->unkA;
    fish->unk108 = fishEntry->common.x;
    fish->unk10C = fishEntry->common.y;
    fish->unk110 = fishEntry->common.z;
    if (param == 0) {
        fish->unkFE = get_random_number_from_range(0, 0x10000);
        fish->unk102 = get_random_number_from_range(0, 0x10000);
        fish->unk106 = get_random_number_from_range(0, 0x10000);
        fish->unkFD = 0;
    } else {
        fish->unkFE = 0x4000;
        fishObj->segment.trans.rotation.y_rotation = fish->unk104;
    }

    xPos = sins_f(fish->unkFE * 2) * fish->unk114;
    zPos = coss_f(fish->unkFE) * fish->unk114;
    sins104 = sins_f(fish->unk104);
    coss104 = coss_f(fish->unk104);

    tempxPos = xPos;

    xPos = (tempxPos * coss104) + (zPos * sins104);
    zPos = (zPos * coss104) - (tempxPos * sins104);

    fishObj->segment.trans.x_position = fish->unk108;
    fishObj->segment.trans.z_position = fish->unk110;

    ignore_bounds_check();
    move_object(fishObj, xPos, 0.0f, zPos);
    if (param == 0) {
        for (i = 0; i < 8; i++) {
            fish->triangles[i].flags = D_800DC9D0[i].flags;
            fish->triangles[i].vi0 = D_800DC9D0[i].vi0;
            fish->triangles[i].vi1 = D_800DC9D0[i].vi1;
            fish->triangles[i].vi2 = D_800DC9D0[i].vi2;
        }
        uMask = 0;
        for (i = 0; i < 6; i++) {
            fish->vertices[uMask].x = D_800DC9A8[uMask].x;
            fish->vertices[uMask].y = D_800DC9A8[uMask].y;
            fish->vertices[uMask].z = D_800DC9A8[uMask].z;
            fish->vertices[uMask].r = 255;
            fish->vertices[uMask].g = 255;
            fish->vertices[uMask].b = 255;
            fish->vertices[uMask].a = 255;
            fish->vertices[uMask + 6].x = D_800DC9A8[uMask].x;
            fish->vertices[uMask + 6].y = D_800DC9A8[uMask].y;
            fish->vertices[uMask + 6].z = D_800DC9A8[uMask].z;
            fish->vertices[uMask + 6].r = 255;
            fish->vertices[uMask + 6].g = 255;
            fish->vertices[uMask + 6].b = 255;
            fish->vertices[uMask + 6].a = 255;
            uMask++;
        }
        fish->unkFC = 1;
    }
    fishObj->segment.trans.scale = fishEntry->unkC * 0.01f;
    if (fishEntry->unkB < fishObj->segment.header->numberOfModelIds) {
        fish->texture = (TextureHeader *) fishObj->unk68[fishEntry->unkB];
    } else {
        fish->texture = (TextureHeader *) fishObj->unk68[0];
    }
    if (fish->texture != NULL) {
        uMask = (fish->texture->width - 1) << 5;
        vMask = (fish->texture->height - 1) << 5;
    } else {
        uMask = 0;
        vMask = 0;
    }
    for (i = 0; i < 8; i++) {
        fish->triangles[i].uv0.u = D_800DC9D0[i].uv0.u * uMask >> 2;
        fish->triangles[i].uv0.v = D_800DC9D0[i].uv0.v * vMask >> 2;
        fish->triangles[i].uv1.u = D_800DC9D0[i].uv1.u * uMask >> 2;
        fish->triangles[i].uv1.v = D_800DC9D0[i].uv1.v * vMask >> 2;
        fish->triangles[i].uv2.u = D_800DC9D0[i].uv2.u * uMask >> 2;
        fish->triangles[i].uv2.v = D_800DC9D0[i].uv2.v * vMask >> 2;
    }
}

void obj_loop_fish(Object *fishObj, s32 updateRate) {
    f32 zThing;
    f32 yThing;
    f32 xThing;
    f32 xDiff;
    f32 yDiff;
    f32 zDiff;
    f32 dist2D;
    f32 dist3D;
    f32 sinUnk104;
    Object_Fish *fish;
    f32 cosUnk104;
    s16 temp_v0_2;
    s32 temp_s0_2;
    s32 temp_t1;
    s32 temp_t9;
    f32 prevXThing, prevZThing;
    Vertex *verts;
    s32 randNumber;

    if (get_viewport_count() > 0) {
        free_object(fishObj);
        return;
    }
    fish = &fishObj->unk64->fish;
    yThing = fishObj->segment.trans.y_position;
    if (fish->unkFD != 0) {
        if ((s32) fish->unkFD >= updateRate) {
            yThing += (fishObj->segment.y_velocity * updateRate);
            fish->unkFD = fish->unkFD - updateRate;
        } else {
            yThing += (fishObj->segment.y_velocity * fish->unkFD);
            fish->unkFD = 0;
        }
    } else {
        randNumber = get_random_number_from_range(0, 7);
        if (randNumber == 0 && fish->unk118 >= 1.0f) {
            fish->unkFD = get_random_number_from_range(160, 255);
            randNumber = get_random_number_from_range(0, fish->unk118);
            fishObj->segment.y_velocity = fish->unk10C - fishObj->segment.trans.y_position;
            fishObj->segment.y_velocity = (fishObj->segment.trans.y_position < fish->unk10C)
                                              ? (fishObj->segment.y_velocity + randNumber)
                                              : (fishObj->segment.y_velocity - randNumber);
            fishObj->segment.y_velocity /= fish->unkFD;
        }
    }
    fish->unkFE += updateRate * fish->unk100;
    zThing = sins_f(fish->unkFE * 2) * fish->unk114;
    xThing = coss_f(fish->unkFE) * fish->unk114;
    sinUnk104 = sins_f(fish->unk104);
    cosUnk104 = coss_f(fish->unk104);
    dist3D += 0; // Fakematch
    prevXThing = zThing;
    prevZThing = xThing;
    zThing = prevXThing; // Fakematch?
    zThing = (zThing * cosUnk104) + (prevZThing * sinUnk104);
    xThing = (prevZThing * cosUnk104) - (prevXThing * sinUnk104);
    zThing += fish->unk108;
    xThing += fish->unk110;
    xDiff = fishObj->segment.trans.x_position - zThing;
    yDiff = fishObj->segment.trans.y_position - yThing;
    zDiff = fishObj->segment.trans.z_position - xThing;
    fishObj->segment.trans.x_position = 0.0f;
    fishObj->segment.trans.y_position = 0.0f;
    fishObj->segment.trans.z_position = 0.0f;
    ignore_bounds_check();
    move_object(fishObj, zThing, yThing, xThing);
    dist2D = (xDiff * xDiff) + (zDiff * zDiff);
    dist3D = sqrtf((yDiff * yDiff) + dist2D);
    dist2D = sqrtf(dist2D);
    fish->unk106 += (s32) (dist3D * 0x600);
    fishObj->segment.trans.rotation.y_rotation = arctan2_f(xDiff, zDiff);
    temp_v0_2 = arctan2_f(-yDiff, dist2D);
    temp_t9 = (temp_v0_2 - fishObj->segment.trans.rotation.x_rotation) & 0xFFFF;
    temp_t1 = (fishObj->segment.trans.rotation.x_rotation - temp_v0_2) & 0xFFFF;
    if (temp_t9 < temp_t1) {
        fishObj->segment.trans.rotation.x_rotation += ((temp_t9 * updateRate) >> 3);
    } else {
        fishObj->segment.trans.rotation.x_rotation -= ((temp_t1 * updateRate) >> 3);
    }
    fish->unkFC = 1 - fish->unkFC;
    verts = &fish->vertices[fish->unkFC * 6];
    randNumber = sins_s16(fish->unk106) >> 3;
    temp_s0_2 = (s32) (coss_f(randNumber) * 32);
    temp_t1 = (s32) (sins_f(randNumber) * 32);
    verts[4].x = (verts[2].x + temp_t1);
    verts[4].z = (verts[2].z + temp_s0_2);
    verts[5].x = (verts[3].x + temp_t1);
    verts[5].z = (verts[3].z + temp_s0_2);
}

/**
 * Lava Spurt init behaviour.
 * Set the timer between animations, and also set the timer to wait before playing the first animation.
 */
void obj_init_lavaspurt(Object *obj, LevelObjectEntry_LavaSpurt *entry) {
    obj->properties.lavaSpurt.actionTimer = entry->initialTimer * 2;
    obj->properties.lavaSpurt.delayTimer = entry->delayTimer;
}

/**
 * Lava Spurt loop behaviour.
 * Count down until zero, then play an animation, after which, set the down time to a random amount with an offset based
 * on spawn properties.
 */
void obj_loop_lavaspurt(Object *obj, s32 updateRate) {
    if (obj->properties.lavaSpurt.actionTimer > 0) {
        obj->properties.lavaSpurt.actionTimer -= updateRate;
        obj->segment.trans.flags |= OBJ_FLAGS_INVISIBLE;
    } else {
        obj->segment.trans.flags &= ~OBJ_FLAGS_INVISIBLE;
        obj->segment.animFrame += updateRate * 4;
        if (obj->segment.animFrame > 255) {
            obj->segment.animFrame = 0;
            obj->properties.lavaSpurt.actionTimer =
                get_random_number_from_range(0, 30) + obj->properties.lavaSpurt.delayTimer;
        }
    }
}

void obj_init_posarrow(Object *obj, UNUSED LevelObjectEntry_PosArrow *entry) {
    obj->segment.trans.flags |= OBJ_FLAGS_INVISIBLE;
}

void obj_loop_posarrow(Object *obj, UNUSED s32 updateRate) {
    Object_PosArrow *posArrow;
    Object **someObjList;
    Object *someObj;
    s32 numberOfObjects;

    obj->segment.trans.flags |= OBJ_FLAGS_INVISIBLE;
    someObjList = get_racer_objects_by_position(&numberOfObjects);
    if (obj->properties.common.unk0 < numberOfObjects) {
        someObj = someObjList[obj->properties.common.unk0];
        posArrow = &someObj->unk64->pos_arrow;
        if (posArrow->unk0 == -1) {
            obj->segment.trans.flags &= ~OBJ_FLAGS_INVISIBLE;
            posArrow->unk150 = obj;
        }
        obj->segment.animFrame = obj->properties.common.unk0 * 127;
    }
}

/* Offical name: animInit */
void obj_init_animator(Object *obj, LevelObjectEntry_Animator *entry, s32 param) {
    Object_Animator *obj64;
    LevelModel *levelModel;
    s16 segmentBatchCount;

    obj64 = &obj->unk64->animator;
    levelModel = get_current_level_model();
    obj64->batchId = entry->batchID;
    obj64->speedFactorX = entry->speedFactorX;
    obj64->speedFactorY = entry->speedfactorY;
    obj64->segmentId = get_level_segment_index_from_position(
        obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
    // Always true.
    if (param == 0) {
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

void obj_loop_animator(Object *obj, s32 updateRate) {
    s32 pad[2];
    Object_64 *obj64;
    LevelModel *levelModel;
    s32 trisStart;
    s32 trisEnd;
    s32 textureIndex;
    s32 tri;
    s32 shift; // a1
    s32 t0;
    s32 t1;
    Triangle *curTriangle;
    TriangleBatchInfo *curBatch;
    LevelModelSegment *curBlock;
    s32 shift2;
    TextureHeader *tex;

    obj64 = obj->unk64;

    t0 = obj64->animator.speedFactorX;
    t1 = obj64->animator.speedFactorY;

    t0 *= updateRate;
    t1 *= updateRate;

    t0 <<= 4;
    t1 <<= 4;

    obj64->animator.xSpeed += t0;
    obj64->animator.ySpeed += t1;

    trisStart = obj64->animator.xSpeed;
    t0 = trisStart;
    trisEnd = obj64->animator.ySpeed;
    t1 = trisEnd;

    obj64->animator.xSpeed &= 0xF;
    obj64->animator.ySpeed &= 0xF;

    t0 >>= 4;
    t1 >>= 4;

    if (obj64->animator.segmentId == -1) {
        return;
    }

    levelModel = get_current_level_model();
    curBlock = &levelModel->segments[obj64->animator.segmentId];
    curBatch = &curBlock->batches[obj64->animator.batchId];
    textureIndex = curBatch->textureIndex;
    trisStart = curBatch->facesOffset;
    trisEnd = (curBatch + 1)->facesOffset;

    if (textureIndex != TEX_INDEX_NO_TEXTURE) {
        if (!curBatch) {} // Fake
        tex = levelModel->textures[textureIndex].texture;
        shift2 = tex->width << 7;
        shift = tex->width << 7;
        for (tri = trisStart; tri < trisEnd; tri++) {
            curTriangle = &curBlock->triangles[tri];
            if (!(curTriangle->flags & 0x80)) {
                if ((shift << 1) < curTriangle->uv0.v) {
                    curTriangle->uv0.v -= shift;
                    curTriangle->uv1.v -= shift;
                    curTriangle->uv2.v -= shift;
                }
                if (curTriangle->uv0.v < 0) {
                    curTriangle->uv0.v += shift;
                    curTriangle->uv1.v += shift;
                    curTriangle->uv2.v += shift;
                }
                if ((shift2 << 1) < curTriangle->uv0.u) {
                    curTriangle->uv0.u -= shift2;
                    curTriangle->uv1.u -= shift2;
                    curTriangle->uv2.u -= shift2;
                }
                if (curTriangle->uv0.u < 0) {
                    curTriangle->uv0.u += shift2;
                    curTriangle->uv1.u += shift2;
                    curTriangle->uv2.u += shift2;
                }
                curTriangle->uv0.v += t1;
                curTriangle->uv1.v += t1;
                curTriangle->uv2.v += t1;
                curTriangle->uv0.u += t0;
                curTriangle->uv1.u += t0;
                curTriangle->uv2.u += t0;
            }
        }
    }
}

void obj_init_animation(Object *obj, LevelObjectEntry_Animation *entry, s32 arg2) {
    Object_Animation *obj64;
    s8 tempOrderIndex;
    f32 scalef;

    scalef = entry->scale & 0xFF;
    if (scalef < 1.0f) {
        scalef = 1.0f;
    }
    scalef /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * scalef;
    obj->segment.trans.rotation.y_rotation = entry->y_rotation << 8;
    obj->segment.trans.rotation.x_rotation = entry->x_rotation << 8;
    obj->segment.trans.rotation.z_rotation = entry->z_rotation << 8;
    if (entry->actorIndex == -2) {
        entry->actorIndex = func_8001F3B8();
    } else {
        if (entry->actorIndex < 0 && entry->actorIndex >= -2) {
            entry->actorIndex = 0;
        }
        func_8001F3C8(entry->actorIndex);
    }
    if (entry->channel == -1) {
        entry->channel = cutscene_id();
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
    path_enable();
    obj->properties.animatedObj.behaviourID = entry->actorIndex;
    obj->properties.animatedObj.action = arg2;
    if (arg2 != 0 && (get_buttons_pressed_from_player(PLAYER_ONE) & R_CBUTTONS)) {
        obj->properties.animatedObj.action = 2;
    }
    if (((cutscene_id() == entry->channel) || (entry->channel == 20)) && (obj->unk64 == NULL) && (entry->order == 0) &&
        (entry->objectIdToSpawn != -1)) {
        func_8001F23C(obj, entry);
    }
    obj64 = &obj->unk64->animation;
    if (obj->unk64 != 0) {
        obj_init_animcamera(obj, (Object *) obj64);
        if (entry->order != 0 || obj64->unk4A != entry->objectIdToSpawn) {
            free_object((Object *) obj64);
            obj->unk64 = NULL;
        }
    }
    if (func_80021600(obj->properties.animatedObj.behaviourID)) {
        func_8001EE74();
    }
}

void obj_loop_animobject(Object *obj, s32 updateRate) {
    func_8001F460(obj, updateRate, obj);
}

void obj_loop_dooropener(Object *obj, s32 updateRate) {
    s32 openDoors;
    unk80037D08_arg0_64 *doorOpener;

    doorOpener = (unk80037D08_arg0_64 *) obj->unk64;
    openDoors = 1 - func_8001F460(obj, updateRate, obj);
    if (doorOpener->unk2A > 0) {
        openDoors = FALSE;
    }
    obj_door_open(openDoors);
}

void obj_init_overridepos(UNUSED Object *obj, UNUSED LevelObjectEntry_OverridePos *entry) {
}

UNUSED void obj_loop_overridepos(UNUSED Object *obj, UNUSED s32 arg1) {
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
        if (wizShipObj->properties.fireball.timer > 0) {
            wizShipObj->properties.fireball.timer -= updateRate;
        } else {
            wizShipObj->properties.fireball.timer = 0;
        }
        if ((wizShipObj->unk60 != NULL) && (wizShipObj->properties.fireball.timer == 0)) {
            if (wizShipObj->particleEmitFlags & OBJ_EMIT_PARTICLE_1) {
                wizShipObj->properties.fireball.timer = 20;
                object_transform_to_matrix(shipMtx, &wizShipObj->segment.trans);
                trans.x_position = 0.0f;
                trans.y_position = 0.0f;
                trans.z_position = 0.0f;
                trans.scale = 1.0f;
                trans.rotation.y_rotation = wizShipObj->segment.trans.rotation.y_rotation;
                trans.rotation.x_rotation = wizShipObj->segment.trans.rotation.x_rotation;
                trans.rotation.z_rotation = 0;
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
                            newObject.size = sizeof(LevelObjectEntryCommon);
                            newObject.objectID = ASSET_OBJECT_ID_LASERBOLT;
                            newObj = spawn_object(&newObject, 1);
                            if (newObj != NULL) {
                                newObj->segment.level_entry = NULL;
                                newObj->segment.trans.rotation.y_rotation =
                                    wizShipObj->segment.trans.rotation.y_rotation + 0x8000;
                                newObj->segment.trans.rotation.x_rotation =
                                    -wizShipObj->segment.trans.rotation.x_rotation;
                                newObj->properties.lasergun.timer = 0x3C;
                                guMtxXFMF(laserMtx, 0.0f, 0.0f, -30.0f, &newObj->segment.x_velocity,
                                          &newObj->segment.y_velocity, &newObj->segment.z_velocity);
                                play_sound_at_position(SOUND_LASER_GUN, wizShipObj->segment.trans.x_position,
                                                       wizShipObj->segment.trans.y_position,
                                                       wizShipObj->segment.trans.z_position, 4, NULL);
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
            someObj->segment.trans.rotation.y_rotation = 0x4000;
            someObj->segment.object.modelIndex++;
            if (someObj->segment.object.modelIndex == someObj->segment.header->numberOfModelIds) {
                someObj->segment.object.modelIndex = 0;
            }
        }
    }
}

void obj_init_hittester(Object *obj, UNUSED LevelObjectEntry_HitTester *entry) {
    obj->interactObj->flags = INTERACT_FLAGS_SOLID | INTERACT_FLAGS_UNK_0080;
    obj->interactObj->unk11 = 2;
    obj->interactObj->hitboxRadius = 20;
    obj->interactObj->pushForce = 0;
}

void obj_loop_hittester(Object *obj, s32 updateRate) {
    func_8001F460(obj, updateRate, obj);
}

/**
 * Dynamically Lit Prop init behaviour.
 * Sets hitbox to add solidity.
 */
void obj_init_dynamic_lighting_object(Object *obj, UNUSED LevelObjectEntry_DynamicLightingObject *entry) {
    obj->interactObj->flags = INTERACT_FLAGS_SOLID;
    obj->interactObj->unk11 = 2;
    obj->interactObj->hitboxRadius = 20;
    obj->interactObj->pushForce = 0;
}

void obj_init_unknown96(Object *obj, UNUSED LevelObjectEntry_Unknown96 *entry) {
    obj->interactObj->flags = INTERACT_FLAGS_SOLID | INTERACT_FLAGS_UNK_0080;
    obj->interactObj->unk11 = 2;
    obj->interactObj->hitboxRadius = 20;
    obj->interactObj->pushForce = 0;
}

/**
 * Rolling snowball init behaviour.
 * Sets hitbox to add solidity.
 */
void obj_init_snowball(Object *obj, UNUSED LevelObjectEntry_Snowball *entry) {
    obj->interactObj->flags = INTERACT_FLAGS_SOLID;
    obj->interactObj->unk11 = 2;
    obj->interactObj->hitboxRadius = 20;
    obj->interactObj->pushForce = 0;
}

void obj_loop_snowball(Object *obj, s32 updateRate) {
    Object_AnimatedObject *obj64 = &obj->unk64->animatedObject;
    if (obj64->currentSound == SOUND_NONE) {
        if (obj64->soundID != SOUND_NONE) {
            obj64->currentSound = obj64->soundID & 0xFF;
        }
    }
    if (obj64->currentSound != SOUND_NONE) {
        if (obj64->soundMask == NULL) {
            play_sound_at_position(obj64->currentSound, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                   obj->segment.trans.z_position, 1, (SoundMask **) &obj64->soundMask);
        } else {
            update_spatial_audio_position((SoundMask *) obj64->soundMask, obj->segment.trans.x_position,
                                          obj->segment.trans.y_position, obj->segment.trans.z_position);
        }
    }
    func_8001F460(obj, updateRate, obj);
}

/**
 * Character select init behaviour.
 * Does nothing. Not even called.
 */
UNUSED void obj_init_char_select(UNUSED s32 arg0, UNUSED s32 arg1) {
}

void obj_loop_char_select(Object *charSelectObj, s32 updateRate) {
    s32 i2;
    s32 i;
    f32 temp_f0;
    ObjectModel *objMdl;
    Object_CharacterSelect *charSelect;
    s32 charCount;
    s32 var_s0;
    s8 *status = NULL;
    Object_68 *gfxData;
    u8 sp50[4];
    u8 sp4F;
    u8 *var_a2;

    var_s0 = 0;
    func_8001F460(charSelectObj, updateRate, NULL);
    charSelect = &charSelectObj->unk64->characterSelect;
    charSelectObj->particleEmitFlags = OBJ_EMIT_OFF;
    if (charSelect != NULL) {
        gfxData = charSelectObj->unk68[charSelectObj->segment.object.modelIndex];
        if (gfxData != NULL) {
            objMdl = gfxData->objModel;
            if (is_drumstick_unlocked()) {
                if (is_tt_unlocked()) {
                    var_a2 = D_800DCA70;
                    charCount = 10;
                } else {
                    var_a2 = D_800DCA58;
                    charCount = 9;
                }
            } else if (is_tt_unlocked()) {
                var_a2 = D_800DCA64;
                charCount = 9;
            } else {
                var_a2 = D_800DCA50;
                charCount = 8;
            }

            for (i = 0; i < charCount && !var_s0; i++) {
                if (charSelect->unk28 == var_a2[i]) {
                    var_s0 = 1;
                }
            }
            i--;
            if (var_s0) {
                charSelectObj->segment.object.animationID = 1;
                for (var_s0 = 0, sp4F = 0; var_s0 < MAXCONTROLLERS; var_s0++) {
                    if (get_player_character(var_s0) == i) {
                        sp50[sp4F++] = var_s0;
                    }
                }
                D_800DCA7C[i] += updateRate;
                if (D_800DCA7C[i] >= 16) {
                    D_800DCA7C[i] &= 0xF;
                    D_800DCA88[i]++;
                }
                if (D_800DCA88[i] >= sp4F) {
                    D_800DCA88[i] = 0;
                }
                if (sp4F > 0) {
                    status = charselect_status();
                    for (i2 = 0; i2 < sp4F; i2++) {
                        if (status[sp50[i2]] == 1) {
                            charSelectObj->particleEmitFlags = OBJ_EMIT_PARTICLE_1;
                            obj_spawn_particle(charSelectObj, LOGIC_30FPS);
                        }
                    }

                    for (i2 = 0; i2 < objMdl->numberOfBatches; i2++) {
                        // Unneccessary check for textureIndex to be greater than or equal to zero since it's a u8 and
                        // can't be less.
                        if (objMdl->batches[i2].textureIndex >= 0 && objMdl->batches[i2].textureIndex < 4) {
                            objMdl->batches[i2].textureIndex = sp50[D_800DCA88[i]];
                        }
                    }
                    charSelectObj->segment.object.animationID = 0;
                }
            }
            if (charSelectObj->segment.object.animationID >= 0) {
                if ((charSelectObj->segment.object.animationID < objMdl->numberOfAnimations)) {
                    i = (objMdl->animations[charSelectObj->segment.object.animationID].unk4 - 1) << 4;
                    if ((charSelect->unk2C == 1)) {
                        temp_f0 = music_animation_fraction();
                        if (temp_f0 > 0.5) {
                            temp_f0 -= 0.5;
                            temp_f0 *= 2.0;
                            charSelectObj->segment.animFrame = i - (temp_f0 * i);
                        } else {
                            temp_f0 *= 2;
                            charSelectObj->segment.animFrame = temp_f0 * i;
                        }
                    }
                }
            }
        }
    }
}

/**
 * Camera Animation loop func.
 * Follows a path and then writes to the view perspective.
 */
void obj_loop_animcamera(Object *obj, s32 updateRate) {
    s32 temp_v0;
    s32 updateCam;
    Object_Animation *camera;

    temp_v0 = func_8001F460(obj, updateRate, obj);
    obj->segment.trans.flags |= OBJ_FLAGS_INVISIBLE;
    camera = &obj->unk64->animation;
    if (temp_v0 == 0) {
        if (get_viewport_count() == VIEWPORTS_COUNT_1_PLAYER) {
            updateCam = func_800210CC(camera->unk44);
        } else {
            updateCam = TRUE;
        }
        if (updateCam) {
            write_to_object_render_stack(camera->cameraID, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                         obj->segment.trans.z_position, 0x8000 - obj->segment.trans.rotation.y_rotation,
                                         -obj->segment.trans.rotation.x_rotation,
                                         obj->segment.trans.rotation.z_rotation);
        }
    }
}

/**
 * Racer cutscene target init behaviour.
 * Does nothing. Not even called.
 */
UNUSED void obj_init_animcar(UNUSED Object *obj, UNUSED s32 arg1) {
}

/**
 * Racer cutscene target loop behaviour.
 * Exists as a target point for racer objects to automatically move towards, for cutscenes.
 */
void obj_loop_animcar(Object *obj, s32 updateRate) {
    Object *racerObj;
    s32 racerID;
    racerID = obj->properties.common.unk0;
    racerObj = NULL;
    if (racerID != 0) {
        racerObj = get_racer_object(racerID - 1);
    }
    obj->properties.common.unk4 = func_8001F460(obj, updateRate, obj);
    obj->segment.trans.flags |= OBJ_FLAGS_INVISIBLE;
    if (obj->properties.common.unk4 == 0 && racerObj != NULL) {
        Object_Racer *racer = &racerObj->unk64->racer;
        racer->approachTarget = obj;
    }
}

void obj_init_infopoint(Object *obj, LevelObjectEntry_InfoPoint *entry) {
    if (entry->hitbox[1] != 0) {
        obj->interactObj->flags = INTERACT_FLAGS_SOLID | INTERACT_FLAGS_UNK_0020;
    } else {
        obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE | INTERACT_FLAGS_UNK_0020;
    }
    obj->interactObj->unk11 = 0;
    obj->interactObj->hitboxRadius = 15;
    obj->interactObj->pushForce = 0;
    obj->properties.infoPoint.radius = (entry->hitbox[2] << 16) | entry->hitbox[0]; // Not sure about the values here.
    obj->properties.infoPoint.visible = entry->hitbox[1];
    obj->segment.trans.rotation.y_rotation = entry->unkB << 10; // Not sure about the values here.
}

void obj_loop_infopoint(Object *obj, UNUSED s32 updateRate) {
    s16 player;
    ObjectInteraction *interactObj;
    Object *playerObj;

    if (obj->properties.infoPoint.visible == FALSE) {
        obj->segment.trans.flags |= OBJ_FLAGS_INVISIBLE;
    } else {
        obj->segment.trans.flags &= ~OBJ_FLAGS_INVISIBLE;
    }

    interactObj = obj->interactObj;
    if (interactObj->distance < ((obj->properties.infoPoint.radius >> 16) & 0xFF)) {
        playerObj = interactObj->obj;
        if (playerObj->segment.header->behaviorId == 1) {
            Object_InfoPoint *playerObj64 = &playerObj->unk64->info_point;
            player = playerObj64->unk0;
            if ((player != PLAYER_COMPUTER) && (get_buttons_pressed_from_player(player) & Z_TRIG)) {
                set_current_text(obj->properties.infoPoint.radius & 0xFF);
            }
        }
    }
}

void obj_init_smoke(UNUSED Object *obj, UNUSED LevelObjectEntry_Smoke *entry) {
}

void obj_loop_smoke(Object *obj, s32 updateRate) {
    f32 updateRateF = updateRate;
    if (osTvType == OS_TV_TYPE_PAL) {
        updateRateF *= 1.2;
    }
    obj->segment.trans.x_position += obj->segment.x_velocity * updateRateF;
    obj->segment.animFrame += updateRate * 16;
    obj->segment.trans.y_position += obj->segment.y_velocity * updateRateF;
    obj->segment.trans.z_position += obj->segment.z_velocity * updateRateF;
    if (obj->segment.animFrame > 255) {
        free_object(obj);
        obj->segment.animFrame = 255;
    }
}

void obj_init_unknown25(UNUSED Object *obj, UNUSED LevelObjectEntry_Unknown25 *entry) {
}

void obj_loop_unknown25(Object *obj, s32 updateRate) {
    obj->segment.animFrame += updateRate * 8;
    if (obj->segment.animFrame > 255) {
        free_object(obj);
        obj->segment.animFrame = 255;
    }
}

void obj_init_wardensmoke(UNUSED Object *obj, UNUSED LevelObjectEntry_WardenSmoke *entry) {
}

void obj_loop_wardensmoke(Object *obj, s32 updateRate) {
    f32 updateRateF;

    updateRateF = (f32) updateRate;
    if (osTvType == OS_TV_TYPE_PAL) {
        updateRateF *= 1.2;
    }
    obj->segment.animFrame += updateRate * 4;
    obj->segment.trans.y_position += updateRateF * 0.25;
    if (obj->segment.animFrame > 255) {
        free_object(obj);
        obj->segment.animFrame = 255;
    }
}

void obj_init_bombexplosion(Object *obj, LevelObjectEntry_BombExplosion *entry) {
    LevelObjectEntry_BombExplosion *entry2;
    obj->segment.animFrame = 0;
    obj->segment.trans.scale = 0.5f;
    obj->segment.object.modelIndex = get_random_number_from_range(0, obj->segment.header->numberOfModelIds - 1);
    entry2 = entry; // Needed for a match.
    obj->properties.bombExplosion.timer = 0;
    obj->properties.bombExplosion.unk4 = 0xFF;
    if (entry->unk8) {
        obj->properties.bombExplosion.unk4 |= (entry2->unk8 << 8) & 0xFF00;
    }
    obj->particleEmitFlags = OBJ_EMIT_PARTICLE_1;
}

void obj_loop_bombexplosion(Object *obj, s32 updateRate) {
    s32 temp_t8;

    obj->properties.bombExplosion.timer += updateRate;
    temp_t8 = (obj->properties.bombExplosion.unk4 >> 8) & 0xFF;
    if (obj->properties.bombExplosion.timer > 10 && temp_t8 != 0) {
        obj->properties.bombExplosion.unk4 ^= (temp_t8 << 8);
        obj_spawn_effect(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position,
                         ASSET_OBJECT_ID_BOMBEXPLOSION, SOUND_NONE, 1.0f, temp_t8 - 1);
    }
    if (obj->properties.bombExplosion.timer < 20) {
        obj->segment.trans.scale = ((obj->properties.bombExplosion.timer / 20.0f) * 10.0f) + 0.5f;
        obj->properties.bombExplosion.unk4 |= 0xFF;
    } else if (obj->properties.bombExplosion.timer < 0x28) {
        obj->segment.trans.scale = (((obj->properties.bombExplosion.timer - 20) / 20.0f) * 5.0f) + 10.5f;
        obj->properties.bombExplosion.unk4 = 0x1EF - (obj->properties.bombExplosion.timer * 0xC);
    } else {
        free_object(obj);
    }

    if (obj->particleEmitFlags) {
        if (get_number_of_active_players() < THREE_PLAYERS) {
            obj_spawn_particle(obj, LOGIC_30FPS);
            obj->particleEmitFlags = OBJ_EMIT_OFF;
        }
    }
}

/**
 * Future Fun Land Teleport init behaviour.
 * Sets hitbox data based off spawn info.
 * If the player has seen the lighthouse cutscene, enable the object.
 */
void obj_init_teleport(Object *obj, UNUSED LevelObjectEntry_Teleport *entry) {
    obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE;
    obj->interactObj->unk11 = 0;
    obj->interactObj->hitboxRadius = 15;
    obj->interactObj->pushForce = 0;
    if (get_settings()->cutsceneFlags & CUTSCENE_LIGHTHOUSE_ROCKET) {
        obj->properties.lighthouse.active = TRUE;
    }
}

/**
 * Future Fun Land Teleport loop behaviour.
 * Triggers a warp to the space hub world when entered, if active.
 */
void obj_loop_teleport(Object *obj, UNUSED s32 updateRate) {
    if (obj->properties.lighthouse.active) {
        LevelObjectEntry_Teleport *level_entry = &obj->segment.level_entry->teleport;
        if (obj->interactObj->distance < 120) {
            begin_level_teleport(level_entry->levelID);
            obj->properties.lighthouse.active = FALSE;
            sound_play(SOUND_WHOOSH2, NULL);
            sound_play_delayed(SOUND_VOICE_TT_FUTURE_FUN_LAND, NULL, 1.0f);
        }
    }
}

/**
 * Exit init behaviour.
 * Sets scale, rotation and hitbox from spawn info.
 * Also applies a face direction used to account for node rotation relative to the angle difference of the racer.
 */
void obj_init_exit(Object *obj, LevelObjectEntry_Exit *entry) {
    f32 radius;
    Object_Exit *exit;
    radius = entry->radius & 0xFF;
    if (radius < 5) {
        radius = 5;
    }
    exit = &obj->unk64->exit;
    radius /= 128;
    obj->segment.trans.scale = radius;
    obj->segment.trans.rotation.y_rotation = U8_ANGLE_TO_U16(entry->angleY);
    exit->directionX = sins_f(obj->segment.trans.rotation.y_rotation);
    exit->directionY = 0.0f;
    exit->directionZ = coss_f(obj->segment.trans.rotation.y_rotation);
    exit->rotationDiff =
        -((exit->directionX * obj->segment.trans.x_position) + (exit->directionZ * obj->segment.trans.z_position));
    exit->radius = entry->radius;
    exit->bossFlag = entry->bossFlag;
    obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE;
    obj->interactObj->unk11 = 0;
    obj->interactObj->hitboxRadius = entry->radius;
    obj->interactObj->pushForce = 0;
}

/**
 * Exit loop behaviour.
 * Waits for a racer to interact with it, then sets the exit ID for the racer, triggering a level transition on their
 * end.
 */
void obj_loop_exit(Object *obj, UNUSED s32 updateRate) {
    Object *racerObj;
    Object_Racer *racer;
    s32 numberOfRacers;
    Settings *settings;
    f32 diffX;
    f32 diffZ;
    f32 dist;
    f32 diffY;
    Object_Exit *exit;
    s32 enableWarp;
    Object **racerObjects;
    s32 i;
    f32 rotDiff;

    exit = &obj->unk64->exit;
    enableWarp = TRUE;
    settings = get_settings();
    // Disable the warp if it's for the first boss encounter, having collected every balloon.
    if (exit->bossFlag == WARP_BOSS_FIRST && settings->balloonsPtr[settings->worldId] == 8) {
        enableWarp = FALSE;
    }
    // Disable the warp if it's for the second boss encounter, having not collected every balloon.
    if (exit->bossFlag == WARP_BOSS_REMATCH && settings->balloonsPtr[settings->worldId] < 8) {
        enableWarp = FALSE;
    }
    // The above ensures only one of the boss warps is active so they don't overlap. This could also probably have been
    // done in the initialiser.
    if (enableWarp && obj->interactObj->distance < exit->radius) {
        dist = exit->radius;
        racerObjects = get_racer_objects(&numberOfRacers);
        for (i = 0; i < numberOfRacers; i++) {
            racerObj = racerObjects[i];
            racer = &racerObj->unk64->racer;
            if (racer->playerIndex != PLAYER_COMPUTER && racer->exitObj == NULL) {
                diffX = racerObj->segment.trans.x_position - obj->segment.trans.x_position;
                diffY = racerObj->segment.trans.y_position - obj->segment.trans.y_position;
                diffZ = racerObj->segment.trans.z_position - obj->segment.trans.z_position;
                if ((sqrtf((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ)) < dist)) {
                    rotDiff = (exit->directionX * racerObj->segment.trans.x_position) +
                              (exit->directionZ * racerObj->segment.trans.z_position) + exit->rotationDiff;
                    if (rotDiff < 0.0f) {
                        racer->exitObj = obj;
                        racer->transitionTimer = -120;
                    }
                }
            }
        }
    }
}

/**
 * Spectate Camera init func.
 * Sets the camera ID then signals to update the pathing systems which include spectate cameras.
 */
void obj_init_cameracontrol(Object *obj, LevelObjectEntry_CameraControl *entry) {
    obj->properties.camControl.cameraID = entry->cameraID;
    path_enable();
}

/**
 * Spectate Cameras loop func.
 * Does nothing since all the behaviour is handled globally.
 */
void obj_loop_cameracontrol(UNUSED Object *obj, UNUSED s32 updateRate) {
}

/**
 * Racer Spawnpoint init func.
 * Sets the spawn ID as well as racer index.
 */
void obj_init_setuppoint(Object *obj, LevelObjectEntry_SetupPoint *entry) {
    obj->properties.setupPoint.racerIndex = entry->racerIndex;
    obj->properties.setupPoint.entranceID = entry->entranceID;
    obj->segment.trans.rotation.y_rotation = U8_ANGLE_TO_U16(entry->angleY);
}

/**
 * Racer Spawnpoint loop func.
 * Does nothing by itself; the game will use these as an anchor for spawning racer objects.
 */
void obj_loop_setuppoint(UNUSED Object *obj, UNUSED s32 updateRate) {
}

/**
 * Dinosaur init behaviour.
 * Walks around, playing footstep sounds and roaring when nearby.
 */
void obj_init_dino_whale(Object *obj, UNUSED LevelObjectEntry_Dino_Whale *entry) {
    obj->interactObj->flags = INTERACT_FLAGS_SOLID;
    obj->interactObj->unk11 = 3;
    obj->interactObj->hitboxRadius = 20;
    obj->interactObj->pushForce = 0;
}

/**
 * Dinosaur loop behaviour.
 * Walks around, playing footstep sounds and roaring when nearby.
 */
void obj_loop_dino_whale(Object *obj, s32 updateRate) {
    s32 animFrame;

    if (obj->properties.common.unk0 > 0) {
        obj->properties.common.unk0 -= updateRate;
        updateRate *= 2;
    } else {
        obj->properties.common.unk0 = 0;
    }
    animFrame = obj->segment.animFrame;
    func_8001F460(obj, updateRate, obj);
    play_footstep_sounds(obj, 0, animFrame, SOUND_STOMP2, SOUND_STOMP3);
    if (obj->interactObj->distance < 255) {
        if (obj->properties.common.unk0 == 0) {
            obj->properties.common.unk0 = 60;
            play_sound_at_position(SOUND_VOICE_BRONTO_ROAR, obj->segment.trans.x_position,
                                   obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
        }
    }
}

/**
 * Hub world Taj init behaviour.
 * Sets hitbox data to give him solidity.
 */
void obj_init_parkwarden(Object *obj, UNUSED LevelObjectEntry_Parkwarden *entry) {
    Object_NPC *taj;
    obj->interactObj->flags = INTERACT_FLAGS_SOLID;
    obj->interactObj->unk11 = 0;
    obj->interactObj->hitboxRadius = 30;
    obj->interactObj->pushForce = 0;
    taj = &obj->unk64->npc;
    taj->nodeCurrent = 0xFF;
    taj->unk0 = 0.0f;
    taj->unk28 = 0;
    taj->unk2C = 0;
    taj->musicFade = 0;
    taj->unk36 = 0;
    gTajSoundMask = NULL;
    gTajSoundID = SOUND_VOICE_TAJ_HELLO;
}

/**
 * Sets the sound ID of Taj's next voice line when spoken to.
 */
void set_taj_voice_line(s16 soundID) {
    // Set to SOUND_VOICE_TAJ_CHALLENGE_RACE in func_800CC7C
    gTajSoundID = soundID;
}

/**
 * Hub world Taj loop behaviour.
 * Handles all the behaviour for the Taj NPC found in the overworld.
 * This uses a state machine to handle whether to wander around, approach the player, change their vehicle and teleport
 * away.
 */
void obj_loop_parkwarden(Object *obj, s32 updateRate) {
    f32 updateRateF;
    f32 xPosDiff;
    f32 updateRateF2;
    f32 zPosDiff;
    f32 distance;
    f32 tempPosY;
    struct WaterProperties **water;
    Object *racerObj;
    s32 sp3C;
    Object *telepoint;
    s32 var_a2;
    Object **racerObjs;
    s32 dialogueID;
    s32 numRacers;
    Object_NPC *taj;
    Object_Racer *racer;
    u32 buttonsPressed;
    s8 spawnSmoke;
    LevelHeader *levelHeader;
    ObjectSegment *temp_v0_22;
    f32 var_f2;
    s32 arctan;
    s32 temp;

    spawnSmoke = FALSE;
    tempPosY = obj->segment.trans.y_position;

    updateRateF2 = updateRate;
    updateRateF = updateRateF2;
    if (osTvType == OS_TV_TYPE_PAL) {
        updateRateF *= 1.2;
    }
    taj = (Object_NPC *) obj->unk64;
    levelHeader = get_current_level_header();
    obj->particleEmitFlags = OBJ_EMIT_OFF;
    if (obj->segment.animFrame == 0 && taj->animFrameF > 1.0) {
        taj->animFrameF = 0.0f;
    }
    distance = 0.0f;
    obj->segment.x_velocity = 0.0f;
    obj->segment.z_velocity = 0.0f;
    racerObj = get_racer_object(PLAYER_ONE);
    if (racerObj != NULL) {
        racer = (Object_Racer *) racerObj->unk64;
        xPosDiff = (racerObj->segment.trans.x_position - (racer->ox1 * 50.0f)) - obj->segment.trans.x_position;
        zPosDiff = (racerObj->segment.trans.z_position - (racer->oz1 * 50.0f)) - obj->segment.trans.z_position;
        distance = sqrtf((xPosDiff * xPosDiff) + (zPosDiff * zPosDiff));
    }
    buttonsPressed = get_buttons_pressed_from_player(PLAYER_ONE);
    var_a2 = FALSE;
    if ((obj->properties.npc.action == NULL) && (distance < 300.0) &&
        (((obj->interactObj->flags & INTERACT_FLAGS_PUSHING) && (racerObj == obj->interactObj->obj)) ||
         (buttonsPressed & Z_TRIG))) {
        if (buttonsPressed & Z_TRIG) {
            play_char_horn_sound(racerObj, racer);
        }
        arctan = arctan2_f(racerObj->segment.trans.x_position - obj->segment.trans.x_position,
                           racerObj->segment.trans.z_position - obj->segment.trans.z_position) -
                 (racerObj->segment.trans.rotation.y_rotation & 0xFFFF);
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
    obj->interactObj->flags = INTERACT_FLAGS_SOLID;
    if ((should_taj_teleport() || var_a2) &&
        (obj->properties.npc.action == TAJ_MODE_ROAM || obj->properties.npc.action == TAJ_MODE_UNK1F)) {
        music_channel_reset_all();
        music_voicelimit_set(24);
        music_play(SEQUENCE_ENTRANCED);
        if (racerObj != NULL) {
            racer_sound_free(racerObj);
            racer->vehicleSound = NULL;
        }
        audioline_off();
        arctan = arctan2_f(racerObj->segment.trans.x_position - obj->segment.trans.x_position,
                           racerObj->segment.trans.z_position - obj->segment.trans.z_position);
        arctan -= (racerObj->segment.trans.rotation.y_rotation & 0xFFFF);
        if ((arctan > 0x8000)) {
            // Probably had a debug statement here.
            if ((obj->properties.npc.action) && (!obj->properties.npc.action) && (!obj->properties.npc.action)) {
            } // Fakematch
        }
        if (var_a2) {
            obj->properties.npc.action = TAJ_MODE_APPROACH_PLAYER;
        } else {
            obj->properties.npc.action = TAJ_MODE_TELEPORT_TO_PLAYER_BEGIN;
            spawnSmoke = TRUE;
        }
        get_fog_settings(PLAYER_ONE, &taj->fogNear, &taj->fogFar, &taj->fogR, &taj->fogG, &taj->fogB);
        slowly_change_fog(PLAYER_ONE, 255, 0, 120, 960, 1100, 240);
        taj->animFrameF = 0.0f;
    }

    if (!(obj->properties.npc.action == TAJ_MODE_ROAM || obj->properties.npc.action == TAJ_MODE_RACE ||
          obj->properties.npc.action == TAJ_MODE_TELEPORT_AWAY_BEGIN ||
          obj->properties.npc.action == TAJ_MODE_TELEPORT_AWAY_END)) {
        disable_racer_input();
        minimap_fade(3);
    }

    switch (obj->properties.npc.action) {
        case TAJ_MODE_GREET_PLAYER:
        case TAJ_MODE_DIALOGUE:
        case TAJ_MODE_TRANSFORM_BEGIN:
        case TAJ_MODE_TRANSFORM_END:
            dialogueID = npc_dialogue_loop(DIALOGUE_TAJ);
            break;
        default:
            dialogue_npc_finish(0);
            dialogueID = 0;
            break;
    }

    switch (obj->properties.npc.action) {
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
            set_pause_lockout_timer(1);
            break;
    }
    if (obj->properties.npc.action != TAJ_MODE_ROAM && dialogueID != 0 && obj->properties.npc.action < 4) {
        obj->properties.npc.action = TAJ_MODE_DIALOGUE;
    }
    switch (obj->properties.npc.action) {
        case TAJ_MODE_APPROACH_PLAYER:
            obj->segment.object.animationID = 0;
            taj->nodeCurrent = 0xFF;
            if (distance < 100.0) {
                racer_set_dialogue_camera();
            }
            if (distance > 10.0) {
                arctan = (arctan2_f(xPosDiff / distance, zPosDiff / distance) -
                          (obj->segment.trans.rotation.y_rotation & 0xFFFF)) +
                         0x8000;
                if (arctan > 0x8000) {
                    arctan -= 0xFFFF;
                }
                if (arctan < -0x8000) {
                    arctan += 0xFFFF;
                }
                if (arctan > 0 && arctan < 16) {
                    arctan = 16;
                }
                obj->segment.trans.rotation.y_rotation += (arctan >> 4);
                var_f2 = -2.0f;
                if (arctan > 0x800 || arctan < -0x800) {
                    var_f2 = -0.5f;
                }
                taj->forwardVel += (var_f2 - taj->forwardVel) * 0.125;
                obj->segment.x_velocity = sins_f(obj->segment.trans.rotation.y_rotation) * taj->forwardVel;
                obj->segment.z_velocity = coss_f(obj->segment.trans.rotation.y_rotation) * taj->forwardVel;
                taj->animFrameF -= taj->forwardVel * 2 * updateRateF;
            } else {
                obj->properties.npc.action = TAJ_MODE_TURN_TOWARDS_PLAYER;
            }
            move_object(obj, obj->segment.x_velocity * updateRateF, obj->segment.y_velocity * updateRateF,
                        obj->segment.z_velocity * updateRateF);
            break;
        case TAJ_MODE_TURN_TOWARDS_PLAYER:
            racer_set_dialogue_camera();
            obj->segment.object.animationID = 0;
            taj->animFrameF += updateRateF * 2.0;
            arctan = (racerObj->segment.trans.rotation.y_rotation - (obj->segment.trans.rotation.y_rotation & 0xFFFF)) +
                     0x8000;
            if (arctan > 0x8000) {
                arctan -= 0xFFFF;
            }
            if (arctan < -0x8000) {
                arctan += 0xFFFF;
            }
            if (arctan > 0 && arctan < 16) {
                arctan = 16;
            }
            obj->segment.trans.rotation.y_rotation += arctan >> 3;
            if (arctan < 0x400 && arctan > -0x400 && distance < 2.0) {
                obj->properties.npc.action = TAJ_MODE_GREET_PLAYER;
                taj->animFrameF = 0;
                play_taj_voice_clip(gTajSoundID, TRUE);
                gTajSoundID = SOUND_VOICE_TAJ_HELLO;
            }
            obj->segment.x_velocity = xPosDiff * 0.125;
            obj->segment.y_velocity = 0;
            obj->segment.z_velocity = zPosDiff * 0.125;
            move_object(obj, obj->segment.x_velocity * updateRateF, obj->segment.y_velocity * updateRateF,
                        obj->segment.z_velocity * updateRateF);
            break;
        case TAJ_MODE_GREET_PLAYER:
            obj->segment.object.animationID = 1;
            taj->forwardVel = 0.0f;
            taj->animFrameF += updateRateF * 1.0;
            if (taj->animFrameF > 77.0) {
                taj->animFrameF = 77.0;
                taj->unk18 = -1.0f;
                obj->properties.npc.action = TAJ_MODE_DIALOGUE;
            }
            arctan = (racerObj->segment.trans.rotation.y_rotation - (obj->segment.trans.rotation.y_rotation & 0xFFFF)) +
                     0x8000;
            if (arctan > 0x8000) {
                arctan -= 0xFFFF;
            }
            if (arctan < -0x8000) {
                arctan += 0xFFFF;
            }
            if (arctan > 0 && arctan < 16) {
                arctan = 16;
            }
            obj->segment.trans.rotation.y_rotation = obj->segment.trans.rotation.y_rotation + (arctan >> 4);
            racer_set_dialogue_camera();
            break;
        case TAJ_MODE_DIALOGUE:
            obj->segment.object.animationID = 4;
            taj->animFrameF += updateRateF * 1.0;
            racer_set_dialogue_camera();
            if (dialogueID == 3 || dialogueID == 4) {
                obj->properties.npc.action =
                    (dialogueID == 4) ? TAJ_MODE_END_DIALOGUE_CHALLENGE : TAJ_MODE_END_DIALOGUE;
                taj->animFrameF = 0.1f;
                obj->segment.object.animationID = 2;
                taj->unk1C = 0;
                play_taj_voice_clip(SOUND_VOICE_TAJ_BYE, TRUE);
                slowly_change_fog(PLAYER_ONE, taj->fogR, taj->fogG, taj->fogB, taj->fogNear, taj->fogFar, 180);
                music_voicelimit_set(levelHeader->voiceLimit);
                music_play(levelHeader->music);
                music_dynamic_set(levelHeader->instruments);
                audioline_on();
            }
            if (dialogueID & 0x80) {
                gTajDialogueChoice = dialogueID & 0x7F;
                if (gTajDialogueChoice != racer->vehicleID) {
                    obj->properties.npc.action = TAJ_MODE_TRANSFORM_BEGIN;
                    taj->animFrameF = 0;
                    // Voice clips: Abrakadabra, Alakazam, Alakazoom?
                    play_taj_voice_clip((racer->vehicleID + SOUND_VOICE_TAJ_ABRAKADABRA), TRUE);
                } else {
                    set_menu_id_if_option_equal(0x62, 2);
                }
            }
            if (dialogueID & 0x40) {
                gTajDialogueChoice = dialogueID & 0xF;
                if (gTajDialogueChoice != racer->vehicleID) {
                    gTajDialogueChoice |= 0x80;
                    obj->properties.npc.action = TAJ_MODE_TRANSFORM_BEGIN;
                    taj->animFrameF = 0.0f;
                    // Voice clips: Abrakadabra, Alakazam, Alakazoom?
                    play_taj_voice_clip((racer->vehicleID + SOUND_VOICE_TAJ_ABRAKADABRA), TRUE);
                } else {
                    obj->properties.npc.action = TAJ_MODE_SET_CHALLENGE;
                    transition_begin(&gTajTransition);
                    spawnSmoke = TRUE;
                    play_taj_voice_clip(SOUND_WHOOSH4, TRUE);
                    taj->animFrameF = 0.0f;
                }
            }
            break;
        case TAJ_MODE_TRANSFORM_BEGIN:
            obj->segment.object.animationID = 5;
            racer_set_dialogue_camera();
            taj->animFrameF += updateRateF * 2.0;
            if (taj->animFrameF > 25.0) {
                obj->particleEmitFlags = OBJ_EMIT_PARTICLE_1 | OBJ_EMIT_PARTICLE_2 | OBJ_EMIT_PARTICLE_4;
            }
            if (taj->animFrameF > 50.0) {
                obj->particleEmitFlags = OBJ_EMIT_OFF;
            }
            if (taj->animFrameF > 60.0) {
                taj->animFrameF = 60.0f;
                if (racer->transparency > (updateRate * 16)) {
                    racer->transparency -= (updateRate * 16);
                } else {
                    racer->transparency = 0;
                    despawn_player_racer(racerObj, gTajDialogueChoice & 0xF);
                    obj->properties.npc.action = TAJ_MODE_TRANSFORM_END;
                    sound_play(SOUND_CYMBAL, NULL);
                    transition_begin(&gTajTransformTransitionEnd);
                }
            }
            break;
        case TAJ_MODE_TRANSFORM_END:
            racer_set_dialogue_camera();
            if (racerObj != NULL) {
                if (taj->animFrameF != 0.0f) {
                    taj->animFrameF += 8.0;
                }
                var_a2 = updateRate;
                if (var_a2 > 4) {
                    var_a2 = 4;
                }
                var_a2 <<= 5;
                if (racer->transparency < (255 - (var_a2))) {
                    racer->transparency += var_a2;
                } else {
                    racer->transparency = 255;
                    if (taj->animFrameF == 0.0) {
                        if (gTajDialogueChoice & 0x80) {
                            transition_begin(&gTajTransition);
                            spawnSmoke = TRUE;
                            obj->properties.npc.action = TAJ_MODE_SET_CHALLENGE;
                            sound_play(SOUND_WHOOSH4, NULL);
                            taj->animFrameF = 0.0f;
                        } else {
                            obj->properties.npc.action = TAJ_MODE_DIALOGUE;
                            set_menu_id_if_option_equal(0x62, 2);
                        }
                    }
                }
            }
            break;
        case TAJ_MODE_END_DIALOGUE:
        case TAJ_MODE_END_DIALOGUE_CHALLENGE:
            if (taj->animFrameF != 0.0) {
                taj->animFrameF = taj->animFrameF + (0.5 * updateRateF);
            }
            if (taj->animFrameF == 0) {
                spawnSmoke = TRUE;
                if (obj->properties.npc.action == TAJ_MODE_END_DIALOGUE_CHALLENGE) {
                    obj_taj_create_balloon(
                        obj->segment.object.segmentID, obj->segment.trans.x_position - (racer->ox1 * 50.0f),
                        obj->segment.trans.y_position, obj->segment.trans.z_position - (racer->oz1 * 50.0f));
                }
                obj->properties.npc.action = TAJ_MODE_TELEPORT_AWAY_BEGIN;
                sound_play(SOUND_WHOOSH4, NULL);
                racer->vehicleSound = func_80004B40(racer->characterId, racer->vehicleID);
            }
            break;
        case TAJ_MODE_TELEPORT_TO_PLAYER_BEGIN:
            obj->segment.object.animationID = 3;
            taj->nodeCurrent = 0xFF;
            taj->forwardVel = 0.0f;
            taj->animFrameF += updateRateF * 2.0;
            if (taj->animFrameF > 79.0f) {
                taj->animFrameF = 79.0f;
            }

            var_a2 = updateRate * 8;
            if (taj->animFrameF < 20.0f) {
                var_a2 = 0;
            }
            if (obj->segment.object.opacity > var_a2) {
                obj->segment.object.opacity -= var_a2;
            } else {
                sound_play(SOUND_WHOOSH4, NULL);
                spawnSmoke = TRUE;
                obj->segment.object.opacity = 0;
                obj->properties.npc.action = TAJ_MODE_TELEPORT_TO_PLAYER_END;
                obj->segment.trans.x_position = racerObj->segment.trans.x_position - (racer->ox1 * 150.0f);
                obj->segment.trans.z_position = racerObj->segment.trans.z_position - (racer->oz1 * 150.0f);
                obj->segment.object.segmentID = get_level_segment_index_from_position(
                    obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
                obj->segment.trans.rotation.y_rotation = racerObj->segment.trans.rotation.y_rotation + 0x8000;
            }
            break;
        case TAJ_MODE_TELEPORT_TO_PLAYER_END:
            obj->segment.object.animationID = 3;
            taj->animFrameF -= updateRateF * 2.0;
            if (taj->animFrameF < 0.0f) {
                taj->animFrameF = 0.0f;
            }
            var_a2 = updateRate * 4;
            if (obj->segment.object.opacity < (255 - var_a2)) {
                obj->segment.object.opacity += var_a2;
            } else {
                obj->segment.object.opacity = 255;
                obj->properties.npc.action = TAJ_MODE_APPROACH_PLAYER;
            }
            break;
        case TAJ_MODE_SET_CHALLENGE:
            obj->segment.object.animationID = 3;
            taj->nodeCurrent = 0xFF;
            taj->forwardVel = 0.0f;
            taj->animFrameF += updateRateF * 2.0;
            if (taj->animFrameF > 79.0f) {
                taj->animFrameF = 79.0f;
            }
            var_a2 = updateRate * 8;
            if (taj->animFrameF < 20.0f) {
                var_a2 = 0;
            }
            if (obj->segment.object.opacity > var_a2) {
                obj->segment.object.opacity -= var_a2;
            } else {
                racer->vehicleSound = func_80004B40(racer->characterId, racer->vehicleID);
                slowly_change_fog(PLAYER_ONE, taj->fogR, taj->fogG, taj->fogB, taj->fogNear, taj->fogFar, 180);
                music_voicelimit_set(levelHeader->voiceLimit);
                music_play(levelHeader->music);
                music_dynamic_set(levelHeader->instruments);
                init_racer_for_challenge(racer->vehicleID);
                telepoint = find_furthest_telepoint(obj->segment.trans.x_position, obj->segment.trans.z_position);
                if (telepoint != NULL) {
                    obj->segment.trans.x_position = telepoint->segment.trans.x_position;
                    obj->segment.trans.z_position = telepoint->segment.trans.z_position;
                    obj->segment.object.segmentID = telepoint->segment.object.segmentID;
                    obj->segment.trans.rotation.y_rotation = racerObj->segment.trans.rotation.y_rotation + 0x8000;
                }
                obj->properties.npc.action = TAJ_MODE_RACE;
            }
            break;
        case TAJ_MODE_TELEPORT_AWAY_BEGIN:
            obj->segment.object.animationID = 3;
            taj->nodeCurrent = 0xFF;
            taj->forwardVel = 0.0f;
            taj->animFrameF += updateRateF * 2.0;
            if (taj->animFrameF > 79.0f) {
                taj->animFrameF = 79.0f;
            }
            var_a2 = updateRate * 8;
            if (taj->animFrameF < 20.0f) {
                var_a2 = 0;
            }
            if (obj->segment.object.opacity > var_a2) {
                obj->segment.object.opacity -= var_a2;
            } else {
                obj->segment.object.opacity = 0;
                obj->properties.npc.action = TAJ_MODE_TELEPORT_AWAY_END;
                telepoint = find_furthest_telepoint(obj->segment.trans.x_position, obj->segment.trans.z_position);
                if (telepoint != NULL) {
                    obj->segment.trans.x_position = telepoint->segment.trans.x_position;
                    obj->segment.trans.z_position = telepoint->segment.trans.z_position;
                    obj->segment.object.segmentID = telepoint->segment.object.segmentID;
                    obj->segment.trans.rotation.y_rotation = racerObj->segment.trans.rotation.y_rotation + 0x8000;
                }
            }
            break;
        case TAJ_MODE_TELEPORT_AWAY_END:
            obj->segment.object.animationID = 3;
            taj->animFrameF -= updateRateF * 2.0;
            if (taj->animFrameF < 0.0f) {
                taj->animFrameF = 0.0f;
            }
            var_a2 = updateRate * 4;
            if (obj->segment.object.opacity < (255 - var_a2)) {
                obj->segment.object.opacity += var_a2;
            } else {
                obj->segment.object.opacity = 255;
                obj->properties.npc.action = TAJ_MODE_ROAM;
            }
            break;
        case TAJ_MODE_RACE:
            obj->interactObj->flags = INTERACT_FLAGS_NONE;
            obj->segment.object.animationID = 6;
            obj->segment.object.opacity = 255;
            taj->animFrameF += updateRateF * 1.0;
            break;
        default:
            obj->segment.object.animationID = 0;
            taj->forwardVel = 0.0f;
            if (taj->nodeCurrent == NODE_NONE) {
                taj->nodeCurrent = ainode_find_nearest(obj->segment.trans.x_position, obj->segment.trans.y_position,
                                                       obj->segment.trans.z_position, FALSE);
                if (taj->nodeCurrent != NODE_NONE) {
                    taj->nodeBack2 = func_8001CC48(taj->nodeCurrent, -1, 0);
                    taj->nodeForward1 = func_8001CC48(taj->nodeBack2, taj->nodeCurrent, 0);
                    taj->nodeForward2 = func_8001CC48(taj->nodeForward1, taj->nodeBack2, 0);
                    taj->nodeBack1 = taj->nodeCurrent;
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
                    taj->animFrameF += func_8001C6C4((Object_64 *) taj, obj, updateRateF, 1.0f, 0);
                } else {
                    var_a2 = taj->unk1E - (obj->segment.trans.rotation.y_rotation & 0xFFFF);
                    if (var_a2 > 0x8000) {
                        var_a2 -= 0xFFFF;
                    }
                    if (var_a2 < -0x8000) {
                        var_a2 += 0xFFFF;
                    }
                    obj->segment.trans.rotation.y_rotation += ((var_a2 * updateRate) >> 4);
                    xPosDiff = sins_f(obj->segment.trans.rotation.y_rotation + 0x8000);
                    zPosDiff = coss_f(obj->segment.trans.rotation.y_rotation + 0x8000);
                    move_object(obj, (updateRateF2 * xPosDiff) * 1.1, 0.0f, (updateRateF2 * zPosDiff) * 1.1);
                    taj->animFrameF += updateRate * 2.2;
                }
            }
            racerObjs = get_racer_objects(&numRacers);
            if (racerObjs[PLAYER_ONE] != NULL) {
                xPosDiff = racerObjs[PLAYER_ONE]->segment.trans.x_position - obj->segment.trans.x_position;
                distance = racerObjs[PLAYER_ONE]->segment.trans.y_position - obj->segment.trans.y_position;
                zPosDiff = racerObjs[PLAYER_ONE]->segment.trans.z_position - obj->segment.trans.z_position;
                var_f2 = sqrtf((xPosDiff * xPosDiff) + (distance * distance) + (zPosDiff * zPosDiff));
                if (var_f2 < 1000.0f) {
                    var_f2 = 1000.0f - var_f2;
                    sp3C = (127.0f * var_f2) / 1000.0f;
                    temp_v0_22 = get_cutscene_camera_segment();
                    xPosDiff = obj->segment.trans.x_position - temp_v0_22->trans.x_position;
                    zPosDiff = obj->segment.trans.z_position - temp_v0_22->trans.z_position;
                    arctan = func_800090C0(xPosDiff, zPosDiff, temp_v0_22->trans.rotation.y_rotation);
                    temp = arctan;
                    music_channel_fade_set(10, sp3C);
                    music_channel_fade_set(11, sp3C);
                    music_channel_fade_set(15, sp3C);
                    music_channel_pan_set(10, temp);
                    music_channel_pan_set(11, temp);
                    music_channel_pan_set(15, temp);
                    music_channel_on(10);
                    music_channel_on(11);
                    music_channel_on(15);
                    music_channel_fade_set(3, 127 - sp3C);
                } else {
                    music_channel_off(10);
                    music_channel_off(11);
                    music_channel_off(15);
                }
            }
            switch (taj->unk36) {
                case 0:
                    if (taj->musicFade > updateRate << 7) {
                        taj->musicFade -= updateRate << 7;
                        music_channel_on(14);
                        music_channel_fade_set(14, taj->musicFade >> 8);
                        taj->unk30 = 0;
                    } else {
                        taj->musicFade = 0;
                        music_channel_off(14);
                        if (taj->unk30 == 0) {
                            taj->unk30 = get_random_number_from_range(600, 900);
                            taj->unk2C = 0;
                        }
                    }
                    if ((taj->unk30 != 0) && ((music_channel_get_mask() & ~0x4000) == 0xB)) {
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
                    if ((music_channel_get_mask() & ~0x4000) == 0xB) {
                        taj->musicFade += (updateRate * 128);
                        if (taj->musicFade > 0x7F00) {
                            taj->musicFade = 0x7F00;
                        }
                        taj->unk2C -= updateRate;
                        if (taj->unk2C < 0) {
                            taj->unk36 = 0;
                        }
                        music_channel_on(14);
                        music_channel_fade_set(14, taj->musicFade >> 8);
                    } else {
                        taj->unk36 = 0;
                        taj->unk2C = 0;
                        taj->unk30 = 0;
                    }
                    break;
            }
            taj->unk28 = music_channel_get_mask() & 0xBFFF;
            break;
    }
    obj->segment.trans.y_position = tempPosY;
    var_a2 = func_8002B0F4(obj->segment.object.segmentID, obj->segment.trans.x_position, obj->segment.trans.z_position,
                           &water);
    if (var_a2 != 0) {
        var_a2--;
        while (var_a2 >= 0) {
            if ((water[var_a2]->type != WATER_CALM) && (water[var_a2]->type != WATER_WAVY) &&
                (water[var_a2]->rotY > 0.0)) {
                obj->segment.trans.y_position = water[var_a2]->waveHeight;
            }
            var_a2--;
        }
    }
    obj->segment.trans.rotation.x_rotation = 0;
    obj->segment.trans.rotation.z_rotation = 0;
    if (obj->properties.npc.action != TAJ_MODE_ROAM) {
        gNPCPosY = obj->segment.trans.y_position;
    }
    if (spawnSmoke) {
        obj_spawn_effect(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position,
                         ASSET_OBJECT_ID_WARDENSMOKE, SOUND_NONE, 1.0f, 0);
    }
    obj->segment.animFrame = taj->animFrameF * 1.0;
    func_80061C0C(obj);
    obj_spawn_particle(obj, updateRate);
}

/**
 * If Taj is currently talking, clear the audio associated with gTajSoundMask,
 * then play the new sound ID in its place.
 */
void play_taj_voice_clip(u16 soundID, s32 interrupt) {
    if (gTajSoundMask && interrupt & 1) {
        sound_stop(gTajSoundMask);
        gTajSoundMask = NULL;
    }
    if (!gTajSoundMask) {
        sound_play(soundID, &gTajSoundMask);
    }
}

void obj_loop_gbparkwarden(UNUSED Object *obj, UNUSED s32 updateRate) {
}

/**
 * Return the Y pos of an NPC when they're in dialogue.
 */
f32 get_npc_pos_y(void) {
    return gNPCPosY;
}

/**
 * Checkpoint initialisation function.
 * Sets direction and scale based off spawn info.
 * Uses bit shifting to convert a u8 angle to an s16 angle.
 */
void obj_init_checkpoint(Object *obj, LevelObjectEntry_Checkpoint *entry, UNUSED s32 arg2) {
    f32 scale = (s32) (entry->scale & 0xFF);
    if (scale < 5.0f) {
        scale = 5.0f;
    }
    scale /= 64;
    obj->segment.trans.scale = scale;
    obj->segment.trans.rotation.y_rotation = U8_ANGLE_TO_U16(entry->angleY);
    path_enable();
}

/**
 * Checkpoint initialisation function.
 * Does nothing, since the racers themselves iterate checkpoints and use their data.
 */
void obj_loop_checkpoint(UNUSED Object *obj, UNUSED s32 updateRate) {
}

/**
 * Vehicle mode changer initialisation function.
 * Sets direction and vehicleID based off spawn info.
 */
void obj_init_modechange(Object *obj, LevelObjectEntry_ModeChange *entry) {
    f32 radius;
    Object_Trigger *obj64;
    radius = entry->radius & 0xFF;
    if (radius < 5) {
        radius = 5;
    }
    obj64 = &obj->unk64->trigger;
    radius /= 128;
    obj->segment.trans.scale = radius;
    obj->segment.trans.rotation.y_rotation = U8_ANGLE_TO_U16(entry->angleY);
    obj64->directionX = sins_f(obj->segment.trans.rotation.y_rotation);
    obj64->directionY = 0.0f;
    obj64->directionZ = coss_f(obj->segment.trans.rotation.y_rotation);
    obj64->rotationDiff =
        -((obj64->directionX * obj->segment.trans.x_position) + (obj64->directionZ * obj->segment.trans.z_position));
    obj64->radius = entry->radius;
    obj64->vehicleID = entry->vehicleID;
    obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE;
    obj->interactObj->unk11 = 0;
    obj->interactObj->hitboxRadius = entry->radius;
    obj->interactObj->pushForce = 0;
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
    Object_Trigger *modeChange;
    f32 diffX;
    f32 diffY;
    f32 diffZ;
    s32 node;
    s32 i;
    f32 radiusF;
    f32 dist;

    modeChange = (Object_Trigger *) obj->unk64;
    if (obj->interactObj->distance < modeChange->radius) {
        radiusF = modeChange->radius;
        racerObjects = get_racer_objects(&numRacers);
        for (i = 0; i < numRacers; i++) {
            racerObj = racerObjects[i];
            racer = (Object_Racer *) racerObj->unk64;
            if (racer->vehicleID != modeChange->vehicleID) {
                diffX = racerObj->segment.trans.x_position - obj->segment.trans.x_position;
                diffY = racerObj->segment.trans.y_position - obj->segment.trans.y_position;
                diffZ = racerObj->segment.trans.z_position - obj->segment.trans.z_position;
                dist = sqrtf((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ));
                if (dist < radiusF) {
                    dist = ((modeChange->directionX * racerObj->segment.trans.x_position) +
                            (modeChange->directionZ * racerObj->segment.trans.z_position) + modeChange->rotationDiff);
                    if (dist < 0.0f) {
                        racer->trickType = 0;
                        if (modeChange->vehicleID == VEHICLE_CAR) {
                            racer->vehicleID = racer->vehicleIDPrev;
                        } else {
                            racer->vehicleID = modeChange->vehicleID;
                        }
                        if (modeChange->vehicleID == VEHICLE_LOOPDELOOP) {
                            if (racer->raceFinished == FALSE) {
                                rumble_set(racer->playerIndex, RUMBLE_TYPE_8);
                            }
                            node = ainode_find_nearest(racerObj->segment.trans.x_position,
                                                       racerObj->segment.trans.y_position,
                                                       racerObj->segment.trans.z_position, FALSE);
                            if (node != NODE_NONE) {
                                racer->nodeCurrent = ainode_get(node);
                            } else {
                                racer->nodeCurrent = NULL;
                            }
                            racer->challengeMarker = NULL;
                            racer->unk19A = 0;
                        }
                        racer->unk198 = obj->segment.trans.rotation.y_rotation;
                    }
                }
            }
        }
    }
}

void obj_init_bonus(Object *obj, LevelObjectEntry_Bonus *entry) {
    f32 radius;
    Object_Trigger *bonus;
    radius = entry->radius & 0xFF;
    if (radius < 5) {
        radius = 5;
    }
    bonus = &obj->unk64->trigger;
    radius /= 128;
    obj->segment.trans.scale = radius;
    obj->segment.trans.rotation.y_rotation = U8_ANGLE_TO_U16(entry->angleY);
    bonus->directionX = sins_f(obj->segment.trans.rotation.y_rotation);
    bonus->directionY = 0.0f;
    bonus->directionZ = coss_f(obj->segment.trans.rotation.y_rotation);
    bonus->rotationDiff =
        -((bonus->directionX * obj->segment.trans.x_position) + (bonus->directionZ * obj->segment.trans.z_position));
    bonus->radius = entry->radius;
    bonus->unk14 = entry->unkA; // Unused?
    obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE;
    obj->interactObj->unk11 = 0;
    obj->interactObj->hitboxRadius = entry->radius;
    obj->interactObj->pushForce = 0;
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
    Object_Trigger *obj64;
    Object **racerObjects;
    s32 i;

    obj64 = &obj->unk64->trigger;
    if (obj->interactObj->distance < obj64->radius) {
        dist = obj64->radius;
        halfDist = dist * 0.5;
        racerObjects = get_racer_objects(&numberOfRacers);
        for (i = 0; i < numberOfRacers; i++) {
            racerObj = racerObjects[i];
            racer = &racerObj->unk64->racer;
            diffY = racerObj->segment.trans.y_position - obj->segment.trans.y_position;
            if (diffY < halfDist && -halfDist < diffY) {
                diffX = racerObj->segment.trans.x_position - obj->segment.trans.x_position;
                diffZ = racerObj->segment.trans.z_position - obj->segment.trans.z_position;
                if (sqrtf((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ)) < dist) {
                    f32 temp = (obj64->directionX * racerObj->segment.trans.x_position) +
                               (obj64->directionZ * racerObj->segment.trans.z_position) + obj64->rotationDiff;
                    if (temp < 0.0f) {
                        if (racer->bananas < 10) {
                            racer->bananas = 10;
                            play_sound_at_position(SOUND_SELECT, racerObj->segment.trans.x_position,
                                                   racerObj->segment.trans.y_position,
                                                   racerObj->segment.trans.z_position, 4, NULL);
                            sound_play_spatial(racer->characterId + SOUND_UNK_7B, racerObj->segment.trans.x_position,
                                               racerObj->segment.trans.y_position, racerObj->segment.trans.z_position,
                                               NULL);
                        }
                    }
                }
            }
        }
    }
}

/**
 * Golden Balloon init func.
 * Assigns the balloon ID either from the entry, or from the balloon ID table.
 */
void obj_init_goldenballoon(Object *obj, LevelObjectEntry_GoldenBalloon *entry) {
    Object_NPC *obj64;
    f32 scalef;

    if (entry->balloonID == -1) {
        entry->balloonID = func_8000CC20(obj);
    } else {
        func_8000CBF0(obj, entry->balloonID);
    }
    if (entry->balloonID == -1) {
        rmonPrintf("Illegal door no!!!\n"); // Did the devs just copy-paste the door init function?
    }
    obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE;
    obj->interactObj->unk11 = 4;
    obj->interactObj->hitboxRadius = 20;
    obj->interactObj->pushForce = 0;
    scalef = entry->scale & 0xFF;
    if (scalef < 10.0f) {
        scalef = 10.0f;
    }
    scalef /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * scalef;
    obj64 = &obj->unk64->npc;
    obj64->nodeCurrent = 255;
    obj64->unk0 = 0.0f;
    obj->properties.npc.action = 0;
    if (entry->challengeID) {
        if (get_settings()->tajFlags & (1 << (entry->challengeID + 2))) {
            obj->properties.npc.action = 0;
        } else {
            obj->properties.npc.action = 1;
        }
    }
}

/**
 * Golden Balloon loop func.
 * Made invisible every frame, but made visible during behaviour if applicable.
 * Follows a path, like Taj and T.T, until collected.
 * Auto deletes if the ID is already claimed by the save flags.
 */
void obj_loop_goldenballoon(Object *obj, s32 updateRate) {
    LevelObjectEntry *levelEntry;
    ObjectInteraction *interactObj;
    Object_Racer *racer;
    Object_NPC *obj64;
    Settings *settings;
    s32 flag;
    s32 doubleSpeed;
    Object *racerObj;
    f32 updateRateF;
    f32 speedf;
    s32 isPirated;

    updateRateF = updateRate;
    if (osTvType == OS_TV_TYPE_PAL) {
        updateRateF *= 1.2;
    }
    isPirated = FALSE;
#ifdef ANTI_TAMPER
    // AntiPiracy check. Seems to set a flag that prevents collecting balloons.
    if (IO_READ(0x284) != 0x240B17D7) {
        isPirated = TRUE;
    }
#endif
    speedf = updateRateF;
    settings = get_settings();
    levelEntry = obj->segment.level_entry;
    flag = 0x10000 << levelEntry->goldenBalloon.balloonID;
    if (settings->courseFlagsPtr[settings->courseId] & flag) {
        if (obj->properties.npc.timer > 0) {
            obj->particleEmitFlags = OBJ_EMIT_PARTICLE_2;
            obj_spawn_particle(obj, updateRate);
            obj->properties.npc.timer -= updateRate;
        } else {
            free_object(obj);
        }
    } else {
        obj->segment.trans.flags |= OBJ_FLAGS_INVISIBLE;
        if (obj->properties.npc.action == 0) {
            obj->segment.trans.flags &= (0xFFFF - OBJ_FLAGS_INVISIBLE);
            doubleSpeed = updateRate * 2;
            if (obj->segment.object.opacity < 255 - doubleSpeed) {
                obj->segment.object.opacity += doubleSpeed;
            } else {
                obj->segment.object.opacity = 255;
            }
            interactObj = obj->interactObj;
            if ((interactObj->distance < 45) && (isPirated == FALSE)) {
                racerObj = interactObj->obj;
                if ((racerObj && (racerObj->segment.header->behaviorId == 1))) {
                    racer = &racerObj->unk64->racer;
                    if (racer->playerIndex == PLAYER_ONE) {
                        settings->balloonsPtr[settings->worldId]++;
                        if (isPirated == 1) {} // Fakematch
                        if (settings->worldId != WORLD_CENTRAL_AREA) {
                            settings->balloonsPtr[0]++;
                        }
                        settings->courseFlagsPtr[settings->courseId] |= flag;
                        if (1) {} // Fakematch
                        sound_play_spatial(SOUND_COLLECT_BALLOON, obj->segment.trans.x_position,
                                           obj->segment.trans.y_position, obj->segment.trans.z_position, NULL);
                        obj->properties.npc.timer = 16;
                        obj->particleEmitFlags = OBJ_EMIT_PARTICLE_2;
                        obj->segment.trans.flags |= OBJ_FLAGS_INVISIBLE;
                        obj_spawn_particle(obj, updateRate);
                    }
                }
            }
            obj64 = &obj->unk64->npc;
            obj->segment.object.animationID = 0;
            obj64->forwardVel = 0.0f;
            speedf = (obj->segment.object.opacity < 255) ? 0 : 1;
            if (obj64->nodeCurrent == 255) {
                obj64->nodeCurrent = ainode_find_nearest(obj->segment.trans.x_position, obj->segment.trans.y_position,
                                                         obj->segment.trans.z_position, FALSE);
                if (obj64->nodeCurrent != 255) {
                    obj64->nodeBack2 = func_8001CC48(obj64->nodeCurrent, -1, 0);
                    obj64->nodeForward1 = func_8001CC48(obj64->nodeBack2, obj64->nodeCurrent, 0);
                    obj64->nodeForward2 = func_8001CC48(obj64->nodeForward1, obj64->nodeBack2, 0);
                    obj64->nodeBack1 = obj64->nodeCurrent;
                }
            } else {
                func_8001C6C4((Object_64 *) obj64, obj, updateRateF, speedf, 0);
            }
        }
    }
}

/**
 * Door init func.
 * Sets all door parameters, which include type, direction and number of balloons needed to open
 */
void obj_init_door(Object *obj, LevelObjectEntry_Door *entry) {
    Object_Door *door;
    f32 radius;

    door = &obj->unk64->door;
    if (entry->doorID == -1) {
        entry->doorID = func_8000CC20(obj);
    } else {
        func_8000CBF0(obj, entry->doorID);
    }
    door->doorID = entry->doorID;
    door->doorType = entry->doorType;
    door->balloonCountUnused = entry->balloonCount;
    door->balloonCount = entry->balloonCount;
    door->radius = entry->distanceToOpen;
    if (door->doorID == -1) {
        rmonPrintf("Illegal door no!!!\n");
    }
    obj->segment.object.modelIndex = entry->modelIndex;
    obj->segment.trans.rotation.y_rotation = U8_ANGLE_TO_U16(entry->closedRotation);
    door->homeY = obj->segment.trans.y_position;
    door->jingleTimer = 0;
    obj->properties.door.closeAngle = obj->segment.trans.rotation.y_rotation;
    obj->properties.door.openAngle = (entry->openRotation & 0x3F) << 10;
    radius = entry->scale & 0xFF;
    if (radius < 10.0f) {
        radius = 10.0f;
    }
    radius /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * radius;
    door->textID = entry->textID;
    door->keyID = entry->keyID;
    obj->interactObj->flags = INTERACT_FLAGS_SOLID | INTERACT_FLAGS_UNK_0020;
    obj->interactObj->unk11 = 2;
    obj->interactObj->hitboxRadius = 20;
    obj->interactObj->pushForce = 0;
    if (obj->segment.object.modelIndex >= obj->segment.header->numberOfModelIds) {
        obj->segment.object.modelIndex = 0;
    }
}

/**
 * Door loop func.
 * If the requirement to open the door is not met, play a jingle and show a message.
 * Since there's a number of different kinds of doors, this code handles each type.
 */
void obj_loop_door(Object *doorObj, s32 updateRate) {
    s32 playSound;
    s16 angleVel;
    volatile s32 doorIDFlag; // ???
    s32 dist;
    s32 keyBits;
    Object_Racer *racer;
    Object_Door *door;
    Settings *settings;
    Object *racerObj;
    ObjectInteraction *racerObjInter;
    LevelObjectEntry_Door *doorEntry;
    f32 updateRateF;
    s32 model;
    s32 sp28;

    doorEntry = &doorObj->segment.level_entry->door;
    updateRateF = updateRate;
    if (osTvType == OS_TV_TYPE_PAL) {
        updateRateF *= 1.2;
    }
    settings = get_settings();
    playSound = settings->courseFlagsPtr[settings->courseId];
    door = &doorObj->unk64->door;
    if (door->doorID >= 0) {
        doorIDFlag = 0x10000 << door->doorID;
        racerObjInter = doorObj->interactObj;
        dist = racerObjInter->distance;
        if (!(door->doorType & 1)) {
            dist = 0; // Door is forced open
        }
        sp28 = playSound & doorIDFlag;
        if (sp28 == 0 && racerObjInter->distance < door->radius) {
            racerObj = racerObjInter->obj;
            if (racerObj != NULL && racerObj->segment.header->behaviorId == BHV_RACER) {
                racer = &racerObj->unk64->racer;
                if (racer->playerIndex != PLAYER_COMPUTER && racerObj == doorObj->unk5C->unk100) {
                    if (door->textID != -1 && textbox_visible() == FALSE && door->jingleCooldown == 0) {
                        music_fade(-8);
                        door->jingleTimer = 140; // PAL users once again forsaken.
                        music_jingle_voicelimit_set(16);
                        audioline_off();
                        music_jingle_play(SEQUENCE_NO_TROPHY_FOR_YOU);
                        set_textbox_display_value(door->balloonCount);
                        set_current_text(door->textID & 0xFF);
                    }
                    door->jingleCooldown = 300;
                }
                if (textbox_visible()) {
                    door->jingleCooldown = 300;
                }
            }
        }
        if (door->jingleTimer != 0 && music_jingle_playing() == SEQUENCE_NONE) {
            if (updateRate < door->jingleTimer) {
                door->jingleTimer -= updateRate;
            } else {
                door->jingleTimer = 0;
                music_fade(8);
                music_jingle_voicelimit_set(6);
                audioline_on();
            }
        }
        if (door->jingleCooldown > 0) {
            door->jingleCooldown -= updateRate;
        } else {
            door->jingleCooldown = 0;
        }
        racerObjInter = doorObj->interactObj;
        keyBits = 0;
        if (racerObjInter->distance < door->radius) {
            racerObj = racerObjInter->obj;
            if (racerObj != NULL && racerObj->segment.header->behaviorId == BHV_RACER) {
                racer = &racerObj->unk64->racer;
                switch (racer->vehicleID) {
                    case VEHICLE_HOVERCRAFT:
                        keyBits = 2;
                        break;
                    case VEHICLE_PLANE:
                        keyBits = 4;
                        break;
                    default:
                        keyBits = 1;
                        break;
                }
            }
        }
        keyBits &= doorEntry->unk10;
        if (doorEntry->common.objectID == ASSET_OBJECT_ID_BIGBOSSDOOR ||
            doorEntry->common.objectID == ASSET_OBJECT_ID_BOSSDOOR) {
            if (obj_door_override()) {
                dist = 0;
            }
        }
        if (door->openDir == DOOR_CLOSED) {
            if (keyBits == 0 && sp28 != 0 && dist < door->radius) {
                door->openDir = DOOR_OPENING;
            } else if (door->radius + 10 < dist) {
                door->openDir = DOOR_CLOSING;
            }
        }
        playSound = FALSE;
        if (door->doorType & 2) {
            if (sp28 != 0 && doorEntry->common.objectID == ASSET_OBJECT_ID_LEVELDOOR) {
                if (settings->courseFlagsPtr[doorEntry->levelID] & RACE_CLEARED) {
                    if (settings->worldId == WORLD_FUTURE_FUN_LAND || settings->bosses & (1 << settings->worldId)) {
                        door->balloonCount = doorEntry->balloonCountOverride;
                        if (door->balloonCount >= 10) {
                            doorObj->segment.object.modelIndex = 3;
                        } else {
                            doorObj->segment.object.modelIndex = 2;
                        }
                    } else {
                        doorObj->segment.object.modelIndex = 0;
                    }
                }
                if (settings->courseFlagsPtr[doorEntry->levelID] & RACE_CLEARED_SILVER_COINS) {
                    doorObj->segment.object.modelIndex = 1;
                }
            }
            if (door->openDir == DOOR_OPENING) {
                if (doorObj->segment.trans.y_position < door->homeY + 130.0) {
                    playSound = TRUE;
                    doorObj->segment.trans.y_position += 2.0 * updateRateF;
                }
            } else if (door->openDir == DOOR_CLOSING) {
                if (door->homeY < doorObj->segment.trans.y_position) {
                    playSound = TRUE;
                    doorObj->segment.trans.y_position -= 2.0 * updateRateF;
                }
            }
        } else {
            if (doorEntry->common.objectID == ASSET_OBJECT_ID_BOSSDOOR) {
                doorObj->segment.object.modelIndex = 0;
                if (settings->bosses & (1 << settings->worldId)) {
                    if (settings->balloonsPtr[settings->worldId] == 8) {
                        doorObj->segment.object.modelIndex = 1;
                    }
                }
                if (settings->bosses & (1 << (settings->worldId + 6))) {
                    doorObj->segment.object.modelIndex = 2;
                }
                if (settings->worldId == WORLD_FUTURE_FUN_LAND) {
                    model = doorObj->segment.object.modelIndex;
                    if (model < 2) {
                        doorObj->segment.object.modelIndex = model + 1;
                    }
                }
            }
            angleVel = 0;
            if (door->openDir == DOOR_OPENING) {
                angleVel = doorObj->segment.trans.rotation.y_rotation - doorObj->properties.common.unk4;
            } else if (door->openDir == DOOR_CLOSING) {
                angleVel = doorObj->segment.trans.rotation.y_rotation - doorObj->properties.common.unk0;
            }
            angleVel >>= 3;
            if (angleVel > 0x200) {
                angleVel = 0x200;
            }
            if (angleVel < -0x200) {
                angleVel = -0x200;
            }
            doorObj->segment.trans.rotation.y_rotation -= angleVel; //@!Delta
            if (angleVel != 0) {
                playSound = TRUE;
            }
        }
        if (playSound) {
            if (door->soundMask == NULL) {
                play_sound_at_position(SOUND_DOOR_OPEN, doorObj->segment.trans.x_position,
                                       doorObj->segment.trans.y_position, doorObj->segment.trans.z_position, 1,
                                       &door->soundMask);
            }
        } else {
            door->openDir = DOOR_CLOSED;
            if (door->soundMask != NULL) {
                func_800096F8((SoundMask *) (s32) door->soundMask);
                door->soundMask = NULL;
            }
        }
        if (door->keyID >= 0) {
            keyBits = 1 << door->keyID;
            if (settings->keys & keyBits) {
                settings->courseFlagsPtr[settings->courseId] |= doorIDFlag;
            }
        } else {
            if (doorEntry->localBalloons == FALSE) {
                if (*settings->balloonsPtr >= door->balloonCount) {
                    settings->courseFlagsPtr[settings->courseId] |= doorIDFlag;
                } else {
                    settings->courseFlagsPtr[settings->courseId] &= ~doorIDFlag;
                }
            } else if (settings->balloonsPtr[settings->worldId] >= door->balloonCount) {
                settings->courseFlagsPtr[settings->courseId] |= doorIDFlag;
            } else {
                settings->courseFlagsPtr[settings->courseId] &= ~doorIDFlag;
            }
        }
    }
    doorObj->interactObj->distance = 0xFF;
    doorObj->interactObj->obj = NULL;
    racerObjInter = doorObj->interactObj;
    racerObjInter->flags &= ~INTERACT_FLAGS_PUSHING;
    doorObj->unk5C->unk100 = NULL;
}

/**
 * T.T Door init func.
 * A much simpler version of the regular door, but has many of the same attributes.
 */
void obj_init_ttdoor(Object *obj, LevelObjectEntry_TTDoor *entry) {
    Object_Door *obj64;
    f32 radius;

    obj->segment.object.modelIndex = 0;
    obj64 = &obj->unk64->door;
    obj->segment.trans.rotation.y_rotation = U8_ANGLE_TO_U16(entry->angleY);
    obj64->doorType = entry->doorType;
    obj64->textID = entry->textID;
    obj64->homeY = obj->segment.trans.y_position;
    obj64->jingleTimer = 0;
    obj64->radius = entry->radius;
    obj->properties.door.closeAngle = obj->segment.trans.rotation.y_rotation;
    obj->properties.door.openAngle = (entry->unk9 & 0x3F) << 0xA;
    radius = entry->scale & 0xFF;
    if (radius < 10) {
        radius = 10;
    }
    radius /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * radius;
    obj->interactObj->flags = INTERACT_FLAGS_SOLID | INTERACT_FLAGS_UNK_0020;
    obj->interactObj->unk11 = 2;
    obj->interactObj->hitboxRadius = 20;
    obj->interactObj->pushForce = 0;
    if (obj->segment.object.modelIndex >= obj->segment.header->numberOfModelIds) {
        obj->segment.object.modelIndex = 0;
    }
}

/**
 * T.T Door loop behaviour.
 * Checks if the player has complete the T.T amulet and has all 47 balloons.
 * If so, it will open, otherwise it opens dialogue telling the player to get them.
 */
void obj_loop_ttdoor(Object *obj, s32 updateRate) {
    Settings *settings;
    Object_Door *ttDoor;
    Object *racerObj;
    Object_Racer *racer;
    s16 angle;
    s32 openDoor;

    ttDoor = (Object_Door *) obj->unk64;
    settings = get_settings();
    if (ttDoor->doorType == 0) {
        obj->segment.object.modelIndex = D_800DCA94[settings->ttAmulet];
    } else {
        obj->segment.object.modelIndex = D_800DCA9C[settings->ttAmulet];
    }
    if (obj->interactObj->distance < ttDoor->radius && (settings->ttAmulet < 4 || *settings->balloonsPtr < 47)) {
        racerObj = obj->interactObj->obj;
        if (racerObj != NULL && racerObj->segment.header->behaviorId == BHV_RACER) {
            racer = (Object_Racer *) racerObj->unk64;
            if (racer->playerIndex != PLAYER_COMPUTER && racerObj == obj->unk5C->unk100) {
                if (ttDoor->textID != -1 && textbox_visible() == 0 && ttDoor->jingleCooldown == 0) {
                    music_fade(-8);
                    ttDoor->jingleTimer = 140;
                    music_jingle_voicelimit_set(16);
                    music_jingle_play(SEQUENCE_NO_TROPHY_FOR_YOU);
                    set_current_text(ttDoor->textID & 0xFF);
                }
                ttDoor->jingleCooldown = 300;
            }
            if (textbox_visible()) {
                ttDoor->jingleCooldown = 300;
            }
        }
    }
    if (ttDoor->jingleTimer && music_jingle_playing() == SEQUENCE_NONE) {
        if (updateRate < ttDoor->jingleTimer) {
            ttDoor->jingleTimer -= updateRate;
        } else {
            ttDoor->jingleTimer = 0.0f;
            music_fade(8);
            music_jingle_voicelimit_set(6);
        }
    }
    if (ttDoor->jingleCooldown > 0) {
        ttDoor->jingleCooldown -= updateRate;
    } else {
        ttDoor->jingleCooldown = 0;
    }
    openDoor = TRUE;
    if (settings->ttAmulet >= 4 && obj->interactObj->distance < ttDoor->radius && *settings->balloonsPtr >= 47) {
        angle = obj->segment.trans.rotation.y_rotation - obj->properties.door.openAngle;
    } else {
        angle = obj->segment.trans.rotation.y_rotation - obj->properties.door.closeAngle;
    }
    angle >>= 3;
    if (angle > 0x200) {
        angle = 0x200;
    }
    if (angle < -0x200) {
        angle = -0x200;
    }
    obj->segment.trans.rotation.y_rotation -= angle;
    if (angle == 0) {
        openDoor = FALSE;
    }
    if (openDoor) {
        if (ttDoor->soundMask == NULL) {
            play_sound_at_position(SOUND_DOOR_OPEN, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                   obj->segment.trans.z_position, 1, &ttDoor->soundMask);
        }
    } else if (ttDoor->soundMask != NULL) {
        func_800096F8((SoundMask *) ((s32) ttDoor->soundMask));
        ttDoor->soundMask = NULL;
    }
    obj->interactObj->distance = 0xFF;
    obj->interactObj->obj = NULL;
    obj->interactObj->flags &= 0xFFF7;
    obj->unk5C->unk100 = NULL;
}

void obj_init_trigger(Object *obj, LevelObjectEntry_Trigger *entry) {
    f32 radius;
    Object_Trigger *obj64;

    if (entry->index == -1) {
        entry->index = func_8000CC20(obj);
    } else {
        func_8000CBF0(obj, entry->index);
    }
    if (entry->index == -1) {
        rmonPrintf("Illegal door no!!!\n");
    }
    radius = (s32) entry->scale & 0xFF;
    if (radius < 5.0f) {
        radius = 5.0f;
    }
    obj64 = &obj->unk64->trigger;
    radius /= 128;
    obj->segment.trans.scale = radius;
    obj->segment.trans.rotation.y_rotation = U8_ANGLE_TO_U16(entry->angleY);
    obj64->directionX = sins_f(obj->segment.trans.rotation.y_rotation);
    obj64->directionY = 0.0f;
    obj64->directionZ = coss_f(obj->segment.trans.rotation.y_rotation);
    obj64->rotationDiff =
        -((obj64->directionX * obj->segment.trans.x_position) + (obj64->directionZ * obj->segment.trans.z_position));
    obj64->radius = entry->scale;
    obj64->unk14 = entry->unkD;
    obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE;
    obj->interactObj->unk11 = 0;
    obj->interactObj->hitboxRadius = entry->scale;
    obj->interactObj->pushForce = 0;
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

    triggerEntry = (LevelObjectEntry_Trigger *) obj->segment.level_entry;
    trigger = (Object_Trigger *) obj->unk64;
    settings = get_settings();
    courseFlags = settings->courseFlagsPtr[settings->courseId];
    curRaceType = get_current_level_race_type();
    if (triggerEntry->index >= 0) {
        flags = 0x10000 << triggerEntry->index;
        if (obj->interactObj->distance < trigger->radius) {
            if (((u8) curRaceType != RACETYPE_HUBWORLD) || !(courseFlags & flags)) {
                radiusF = trigger->radius;
                racers = get_racer_objects(&numRacers);
                for (i = 0; i < numRacers; i++) {
                    racerObj = racers[i];
                    racer = (Object_Racer *) racerObj->unk64;
                    if ((!(trigger->unk14 & 1) && racer->playerIndex == PLAYER_COMPUTER) ||
                        (!(trigger->unk14 & 2) && racer->playerIndex != PLAYER_COMPUTER)) {
                        diffX = racerObj->segment.trans.x_position - obj->segment.trans.x_position;
                        diffY = racerObj->segment.trans.y_position - obj->segment.trans.y_position;
                        diffZ = racerObj->segment.trans.z_position - obj->segment.trans.z_position;
                        distance = sqrtf((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ));
                        if (distance < radiusF) {
                            distance = (trigger->directionX * racerObj->segment.trans.x_position) +
                                       (trigger->directionZ * racerObj->segment.trans.z_position) +
                                       trigger->rotationDiff;
                            if (distance < 0.0f) {
                                settings->courseFlagsPtr[settings->courseId] |= flags;
                                if (triggerEntry->unkB != 0xFF) {
                                    set_current_text(triggerEntry->unkB);
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

/**
 * Moving Bridge init func.
 * Sets hitbox info and the model from spawn info.
 */
void obj_init_bridge_whaleramp(Object *obj, LevelObjectEntry_Bridge_WhaleRamp *entry) {
    Object_Bridge_WhaleRamp *bridge = &obj->unk64->bridge_whale_ramp;
    obj->segment.object.modelIndex = entry->modelIndex;
    obj->segment.trans.rotation.y_rotation = U8_ANGLE_TO_U16(entry->angleY);
    bridge->homeY = obj->segment.trans.y_position;
    obj->interactObj->flags = INTERACT_FLAGS_SOLID | INTERACT_FLAGS_UNK_0020;
    obj->interactObj->unk11 = 2;
    obj->interactObj->hitboxRadius = 20;
    obj->interactObj->pushForce = 0;
    bridge->soundMask = NULL;
    if (obj->segment.object.modelIndex >= obj->segment.header->numberOfModelIds) {
        obj->segment.object.modelIndex = 0;
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
    UNUSED ObjectTransform *temp_v0_4;
    f32 bobAmount;
    Object_Bridge_WhaleRamp *whaleRamp;
    LevelObjectEntry_Bridge_WhaleRamp *entry;
    f32 updateRateF;
    s32 vehicleID;
    f32 bellX1;
    f32 bellY1;
    f32 bellZ1;
    f32 bellX2;
    f32 bellY2;
    f32 bellZ2;
    Object_Racer *racer;

    whaleRamp = (Object_Bridge_WhaleRamp *) obj->unk64;
    entry = (LevelObjectEntry_Bridge_WhaleRamp *) obj->segment.level_entry;
    updateRateF = updateRate;

    if (osTvType == OS_TV_TYPE_PAL) {
        updateRateF *= 1.2;
    }

    if (entry->unkB != 3) {
        if (obj->properties.common.unk0 != 0) {
            bobAmount = 2.0 * (f32) entry->bobAmount;
            if (bobAmount > 0.0f) {
                if (obj->segment.trans.y_position < whaleRamp->homeY + bobAmount) {
                    obj->segment.trans.y_position += updateRateF * 2;
                }
            } else {
                if (whaleRamp->homeY + bobAmount < obj->segment.trans.y_position) {
                    obj->segment.trans.y_position -= updateRateF * 2;
                }
            }
        } else if (entry->radius > 0) {
            if (whaleRamp->homeY < obj->segment.trans.y_position) {
                obj->segment.trans.y_position -= updateRateF * 2;
            }
        } else {
            if (obj->segment.trans.y_position < whaleRamp->homeY) {
                obj->segment.trans.y_position += updateRateF * 2;
            }
        }
    } else if (obj->properties.common.unk0 != 0) {
        if (obj->segment.trans.rotation.x_rotation >= -0x12FF) {
            obj->segment.trans.rotation.x_rotation -= updateRate * 0x2D;
        }
        if (whaleRamp->soundMask == NULL) {
            obj_bridge_pos(entry->unkA, &bellX1, &bellY1, &bellZ1);
            play_sound_at_position(SOUND_DRAWBRIDGE_BELL, bellX1, bellY1, bellZ1, 1, &whaleRamp->soundMask);
        }
    } else {
        if (obj->segment.trans.rotation.x_rotation < 0) {
            obj->segment.trans.rotation.x_rotation += updateRate * 0x28;
            if (whaleRamp->soundMask == NULL) {
                obj_bridge_pos(entry->unkA, &bellX2, &bellY2, &bellZ2);
                play_sound_at_position(SOUND_DRAWBRIDGE_BELL, bellX2, bellY2, bellZ2, 1, &whaleRamp->soundMask);
            }
        } else {
            obj->segment.trans.rotation.x_rotation = 0;
            if (whaleRamp->soundMask != NULL) {
                func_800096F8(whaleRamp->soundMask);
            }
        }
    }

    switch (entry->unkB) {
        case 0:
            obj->properties.common.unk0 = 0;
            if (obj->interactObj->distance < entry->radius) {
                obj->properties.common.unk0 = 1;
            }
            break;
        case 2:
            obj->properties.common.unk0 = 1;
            racerObj = get_racer_object(PLAYER_ONE);
            if (racerObj != NULL) {
                racer = (Object_Racer *) racerObj->unk64;
                switch (racer->vehicleID) {
                    default:
                        vehicleID = VEHICLE_HOVERCRAFT;
                        break;
                    case 1:
                        vehicleID = VEHICLE_PLANE;
                        break;
                    case 2:
                        vehicleID = VEHICLE_LOOPDELOOP;
                        break;
                }
                if (entry->allowedVehicles & vehicleID) {
                    obj->properties.common.unk0 = NULL;
                }
            }
            break;
        default:
            if (func_8001E2EC(entry->unkA) != 0) {
                obj->properties.common.unk0 = (entry->unkD * 2);
            }
            if (obj->properties.common.unk0 > 0) {
                obj->properties.common.unk0 -= updateRate;
            } else {
                obj->properties.common.unk0 = 0;
            }
            break;
    }

    obj->interactObj->distance = 255;
    obj->interactObj->obj = NULL;
    obj->interactObj->flags &= ~INTERACT_FLAGS_PUSHING;
}

void obj_init_rampswitch(Object *obj, LevelObjectEntry_RampSwitch *entry) {
    obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE;
    obj->interactObj->unk11 = 0;
    obj->interactObj->hitboxRadius = 20;
    obj->interactObj->pushForce = 0;
    obj->properties.common.unk0 = entry->unk8;
}

void obj_loop_rampswitch(Object *obj, UNUSED s32 updateRate) {
    if (obj->interactObj->distance < 45) {
        func_8001E344(obj->properties.common.unk0);
    }
    obj->interactObj->distance = 255;
}

void obj_init_seamonster(UNUSED Object *obj, UNUSED LevelObjectEntry_SeaMonster *entry) {
}

void obj_loop_seamonster(UNUSED Object *obj, UNUSED s32 updateRate) {
}

/* Official name: fogInit(?) */
void obj_init_fogchanger(Object *obj, LevelObjectEntry_FogChanger *entry) {
    f32 dist;
    dist = entry->distance * 8.0f;
    dist = dist * dist;
    obj->properties.distance.radius = dist;
}

/**
 * Skydome control init behaviour.
 * Sets hitbox data and on or off setting based off spawn info.
 */
void obj_init_skycontrol(Object *obj, LevelObjectEntry_SkyControl *entry) {
    obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE;
    obj->interactObj->unk11 = 0;
    obj->interactObj->hitboxRadius = entry->radius;
    obj->properties.skyControl.setting = entry->setting;
    obj->properties.skyControl.radius = entry->radius;
}

/**
 * Skydome control loop behaviour.
 * When a player goes through this object, enable or disable rendering the skydome depending on setting.
 * Used for transitions between indoors and outdoors.
 */
void obj_loop_skycontrol(Object *obj, UNUSED s32 updateRate) {
    if (obj->interactObj->distance < obj->properties.skyControl.radius) {
        set_skydome_visbility(obj->properties.skyControl.setting);
    }
}

/**
 * AI node init func.
 * Adds itself to the node list, and then tells the game AI nodes exist.
 */
void obj_init_ainode(Object *obj, LevelObjectEntry_AiNode *entry) {
    if (entry->nodeID == NODE_NONE) {
        entry->nodeID = ainode_register(obj) & NODE_NONE;
    }
    ainode_tail_set(entry->nodeID);
    ainode_enable();
}

/**
 * AI node loop func.
 * Does nothing. All the relevant behaviour is handled globally.
 */
void obj_loop_ainode(UNUSED Object *obj, UNUSED s32 updateRate) {
}

/**
 * Smokey's castle treasure box init function.
 * Sets up player ID, making sure the value doesn't go over 4 players.
 */
void obj_init_treasuresucker(Object *obj, LevelObjectEntry_TreasureSucker *entry) {
    obj->segment.animFrame = 120;
    obj->properties.treasureSucker.playerID = (entry->playerID - 1) & 3;
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

    racerObj = get_racer_object(obj->properties.treasureSucker.playerID);
    if (racerObj != NULL) {
        racer = (Object_Racer *) racerObj->unk64;
        doSpawnObj = FALSE;
        if (racer->bananas != 0 && obj->properties.treasureSucker.spawnTimer == 0) {
            diffX = obj->segment.trans.x_position - racerObj->segment.trans.x_position;
            diffY = obj->segment.trans.y_position - racerObj->segment.trans.y_position;
            diffZ = obj->segment.trans.z_position - racerObj->segment.trans.z_position;
            diffX = (diffX * diffX) + (diffY * diffY) + (diffZ * diffZ); // Required to match.
            if (diffX < 225 * 225) {
                obj->properties.treasureSucker.spawnTimer = 8;
                doSpawnObj = TRUE;
            }
        }
        if (obj->properties.treasureSucker.spawnTimer > 0) {
            obj->properties.treasureSucker.spawnTimer -= updateRate;
            if (obj->properties.treasureSucker.spawnTimer <= 0) {
                if (racer->bananas > 0) {
                    racer->bananas--;
                    if (racer->bananas != 0) {
                        doSpawnObj = TRUE;
                    }
                    obj->properties.treasureSucker.spawnTimer = 8;
                } else {
                    obj->properties.treasureSucker.spawnTimer = 0;
                }
            }
        }
        if (doSpawnObj) {
            spawnObj.x = racerObj->segment.trans.x_position;
            spawnObj.y = (s16) racerObj->segment.trans.y_position + 10;
            spawnObj.z = racerObj->segment.trans.z_position;
            spawnObj.size = sizeof(LevelObjectEntryCommon);
            spawnObj.objectID = ASSET_OBJECT_ID_FLYCOIN;
            newObj = spawn_object(&spawnObj, 1);
            if (newObj != NULL) {
                newObj->segment.level_entry = NULL;
                newObj->segment.y_velocity = 10.0f;
                scale = (newObj->segment.y_velocity * 2) / 0.5;
                newObj->segment.x_velocity =
                    (obj->segment.trans.x_position - racerObj->segment.trans.x_position) / scale;
                newObj->segment.z_velocity =
                    (obj->segment.trans.z_position - racerObj->segment.trans.z_position) / scale;
                newObj->properties.treasureBanana.racer = racer;
                newObj->properties.treasureBanana.diff = scale;
            }
        }
    }
}

/**
 * Smokey's Castle Treasure Visual init func.
 */
void obj_init_flycoin(UNUSED Object *obj, UNUSED LevelObjectEntry_FlyCoin *entry) {
}

/**
 * Smokey's Castle Treasure Visual loop func.
 * When spawned, moves with the velocity given, which makes it aim towards the treasure box.
 * Deletes itself once the timer hits zero. Will also trigger the win condition once necessary.
 */
void obj_loop_flycoin(Object *obj, s32 updateRate) {
    f32 updateRateF;
    Object_Racer *racerObj;

    updateRateF = updateRate;
    if (osTvType == OS_TV_TYPE_PAL) {
        updateRateF *= 1.2;
    }
    obj->segment.y_velocity -= 0.5 * updateRateF;
    move_object(obj, obj->segment.x_velocity * updateRateF, obj->segment.y_velocity * updateRateF,
                obj->segment.z_velocity * updateRateF);
    obj->properties.treasureBanana.diff -= updateRate;
    if (obj->properties.treasureBanana.diff <= 0) {
        racerObj = obj->properties.treasureBanana.racer;
        racerObj->lap++;
        if (racerObj->lap >= 10) {
            racerObj->raceFinished = TRUE;
        }
        free_object(obj);
        if (racerObj->playerIndex != PLAYER_COMPUTER) {
            sound_play(SOUND_SELECT, NULL);
        }
    }
    obj->segment.animFrame += updateRate * 8;
}

/**
 * Smokey's Castle Banana Spawner init func.
 * Seemingly does nothing.
 */
void obj_init_bananacreator(Object *obj, UNUSED LevelObjectEntry_BananaCreator *entry) {
    obj->segment.animFrame = 100;
}

/**
 * Smokey's Castle Banana Spawner loop func.
 * Spawns a banana. If it is collected, then it will spawn another 20 seconds later.
 */
void obj_loop_bananacreator(Object *obj, s32 updateRate) {
    LevelObjectEntryCommon newEntry;
    Object *newBananaObj;
    Object_Banana *newBananaObj64;

    if (obj->properties.bananaSpawner.spawn != 0) {
        obj->properties.bananaSpawner.timer -= updateRate;
    }

    if (obj->properties.bananaSpawner.timer <= 0) {
        newEntry.x = obj->segment.trans.x_position;
        newEntry.y = (s16) obj->segment.trans.y_position - 3;
        newEntry.z = obj->segment.trans.z_position;
        newEntry.size = sizeof(LevelObjectEntryCommon);
        newEntry.objectID = ASSET_OBJECT_ID_COIN;
        newBananaObj = spawn_object(&newEntry, 1);
        obj->properties.bananaSpawner.spawn = TRUE;
        if (newBananaObj) {
            newBananaObj->segment.level_entry = NULL;
            newBananaObj64 = &newBananaObj->unk64->banana;
            newBananaObj64->spawner = obj;
            obj_spawn_effect(obj->segment.trans.x_position, obj->segment.trans.y_position - 14.0f,
                             obj->segment.trans.z_position, ASSET_OBJECT_ID_BOMBEXPLOSION, SOUND_SELECT, 0.25f, 0);
            obj->properties.bananaSpawner.spawn = FALSE;
        }
        // Set respawn timer 20 seconds. Poor PAL users aren't accounted for, and must wait 24 seconds.
        obj->properties.bananaSpawner.timer = TIME_SECONDS(20);
    }
}

/**
 * Banana init func.
 * Sets the interaction properties.
 * If bananas are disabled, then delete itself.
 */
void obj_init_banana(Object *obj, UNUSED LevelObjectEntry_Banana *entry) {
    obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE;
    obj->interactObj->unk11 = 0;
    obj->interactObj->hitboxRadius = 30;
    obj->properties.banana.intangibleTimer = 20; // PAL users doomed to wait 24 frames.
    obj->properties.banana.destroyTimer = 16;
    if (get_filtered_cheats() & CHEAT_DISABLE_BANANAS) {
        free_object(obj);
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
    f32 radius;
    f32 updateRateF;
    f32 velX;
    f32 velZ;
    s32 sp48;
    s32 hitDist;
    s8 sp43;
    Object_Banana *banana;
    ObjPropertyBanana *properties;
    SoundMask *prevSoundMask;

    updateRateF = updateRate;
    if (osTvType == OS_TV_TYPE_PAL) {
        updateRateF *= 1.2;
    }
    banana = (Object_Banana *) obj->unk64;
    obj->segment.animFrame += updateRate * 8;
    properties = (ObjPropertyBanana *) &obj->properties.banana;
    if (properties->status == BANANA_COLLECTED) {
        obj->segment.trans.flags |= OBJ_FLAGS_INVISIBLE;
        properties->destroyTimer -= updateRate;
        obj->particleEmitFlags = OBJ_EMIT_PARTICLE_1;
        obj_spawn_particle(obj, updateRate);
        if (properties->destroyTimer <= 0) {
            free_object(obj);
        }
    } else {
        if (banana->unk8 > 0) {
            banana->unk8 -= updateRate;
        } else {
            banana->unk8 = 0;
            banana->unk0 = 0;
        }
        if (properties->status == BANANA_DROPPED) {
            tempPos[0] = obj->segment.trans.x_position + (obj->segment.x_velocity * updateRateF);
            tempPos[1] = obj->segment.trans.y_position + (obj->segment.y_velocity * updateRateF);
            tempPos[2] = obj->segment.trans.z_position + (obj->segment.z_velocity * updateRateF);
            radius = 8.0f;
            func_80031130(1, &obj->segment.trans.x_position, tempPos, -1);
            sp48 = 0;
            func_80031600(&obj->segment.trans.x_position, tempPos, &radius, &sp43, TRUE, &sp48);
            obj->segment.x_velocity = (tempPos[0] - obj->segment.trans.x_position) / updateRateF;
            obj->segment.y_velocity = (tempPos[1] - obj->segment.trans.y_position) / updateRateF;
            obj->segment.z_velocity = (tempPos[2] - obj->segment.trans.z_position) / updateRateF;
            obj->segment.trans.x_position = tempPos[0];
            obj->segment.trans.y_position = tempPos[1];
            obj->segment.trans.z_position = tempPos[2];
            // Bananas dropped by planes will not have gravity.
            if (banana->droppedVehicleID != VEHICLE_PLANE) {
                obj->segment.y_velocity -= 1.0;  //!@Delta
                obj->segment.x_velocity *= 0.95; //!@Delta
                obj->segment.z_velocity *= 0.95; //!@Delta
            } else {
                obj->segment.x_velocity = 0.0f;
                obj->segment.y_velocity = 0.0f;
                obj->segment.z_velocity = 0.0f;
            }
            velX = obj->segment.x_velocity;
            if (velX < 0.0) {
                velX = -velX;
            }
            velZ = obj->segment.z_velocity;
            if (velZ < 0.0) {
                velZ = -velZ;
            }
            if (sp48 > 0 && velX < 0.5 && velZ < 0.5) {
                properties->status = BANANA_IDLE;
            }
            radius = -10000.0f;
            if (func_8002B9BC(obj, &radius, NULL, 1) != 0 && obj->segment.trans.y_position < radius) {
                properties->status = BANANA_IDLE;
                obj->segment.trans.y_position = radius;
            }
        }
        hitDist = 70;
        if (banana->droppedVehicleID != VEHICLE_PLANE) {
            hitDist = 55; // Non-planes have smaller hitboxes.
        }

        if (properties->intangibleTimer > 0) {
            properties->intangibleTimer -= updateRate;
        } else {
            properties->intangibleTimer = 0;
        }
        if (obj->interactObj->distance < 120) {
            if (get_current_level_race_type() == RACETYPE_CHALLENGE_BANANAS) {
                racerObj = obj->interactObj->obj;
                if (racerObj != NULL && racerObj->segment.header->behaviorId == BHV_RACER) {
                    racer = (Object_Racer *) racerObj->unk64;
                    if (racer->playerIndex == PLAYER_COMPUTER) {
                        hitDist += 30; // AI players are offered extra courtesy.
                    }
                }
            }
        }
        if (obj->interactObj->distance < hitDist && properties->intangibleTimer == 0) {
            racerObj = obj->interactObj->obj;
            if (racerObj != NULL && racerObj->segment.header->behaviorId == BHV_RACER) {
                racer = (Object_Racer *) racerObj->unk64;
                if (get_current_level_race_type() != RACETYPE_CHALLENGE_BANANAS || racer->bananas < 2) {
                    prevSoundMask = racer->bananaSoundMask;
                    play_sound_at_position(SOUND_SELECT, racerObj->segment.trans.x_position,
                                           racerObj->segment.trans.y_position, racerObj->segment.trans.z_position, 4,
                                           &racer->bananaSoundMask);
                    if (prevSoundMask) {
                        func_800096F8(prevSoundMask);
                    }
                    if (racer->playerIndex != PLAYER_COMPUTER && racer->bananas == 9) {
                        sound_play_spatial(racer->characterId + SOUND_UNK_7B, racerObj->segment.trans.x_position,
                                           racerObj->segment.trans.y_position, racerObj->segment.trans.z_position,
                                           NULL);
                    }
                    racer->bananas++;
                    if (banana->spawner != NULL) {
                        banana->spawner->properties.bananaSpawner.spawn = TRUE;
                    }
                    if (get_number_of_active_players() > TWO_PLAYERS) {
                        free_object(obj);
                    } else {
                        properties->status = BANANA_COLLECTED;
                        obj->particleEmitFlags = OBJ_EMIT_PARTICLE_1;
                        obj_spawn_particle(obj, updateRate);
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
    obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE;
    obj->interactObj->unk11 = 0;
    obj->interactObj->hitboxRadius = 30;
    obj->properties.npc.action = SILVER_COIN_INACTIVE;
    obj->properties.npc.timer = 16;
    if (!is_in_tracks_mode()) {
        if (check_if_silver_coin_race() && is_in_adventure_two()) {
            obj->properties.npc.action = SILVER_COIN_ACTIVE;
        } else {
            obj->properties.npc.action = SILVER_COIN_INACTIVE;
        }
    }
    if (obj->properties.npc.action == SILVER_COIN_INACTIVE) {
        obj->segment.trans.flags |= OBJ_FLAGS_INVIS_PLAYER1 | OBJ_FLAGS_INVIS_PLAYER2;
        free_object(obj);
    }
}

/**
 * Race silver coin init behaviour.
 * Checks if in the correct modes, then sets the flag to active, otherwise inactive.
 * If the flag is inactive, destroy the object.
 */
void obj_init_silvercoin(Object *obj, UNUSED LevelObjectEntry_SilverCoin *entry) {
    obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE;
    obj->interactObj->unk11 = 0;
    obj->interactObj->hitboxRadius = 30;
    obj->properties.npc.action = SILVER_COIN_INACTIVE;
    obj->properties.npc.timer = 0;
    if (!is_in_tracks_mode()) {
        if (check_if_silver_coin_race() && !is_in_adventure_two()) {
            obj->properties.npc.action = SILVER_COIN_ACTIVE;
        } else {
            obj->properties.npc.action = SILVER_COIN_INACTIVE;
        }
    }
    if (obj->properties.npc.action == SILVER_COIN_INACTIVE) {
        obj->segment.trans.flags |= OBJ_FLAGS_INVIS_PLAYER2 | OBJ_FLAGS_INVIS_PLAYER1;
        free_object(obj);
    }
}

/**
 * Race silver coin loop behaviour.
 * Can only be collected by players. Sets a flag equal to the player number when collected.
 * Under normal gameplay, that's 1 and 2, since the silver coin challenge can be done with at most two players.
 * When collected, the coins are hidden for that player, rather than being removed outright.
 */
void obj_loop_silvercoin(Object *obj, s32 updateRate) {
    ObjectInteraction *interactObj;
    Object_Racer *racer;
    Object *racerObj;
    s32 twoPlayerAdv;

    twoPlayerAdv = is_two_player_adventure_race();
    if ((twoPlayerAdv && obj->properties.npc.action != SILVER_COIN_INACTIVE) ||
        (!twoPlayerAdv && obj->properties.npc.action == SILVER_COIN_ACTIVE)) {
        interactObj = obj->interactObj;
        if (interactObj->distance < 80) {
            racerObj = interactObj->obj;
            if (racerObj != NULL && racerObj->segment.header->behaviorId == BHV_RACER) {
                racer = (Object_Racer *) racerObj->unk64;
                if (racer->playerIndex != PLAYER_COMPUTER) {
                    if (racer->raceFinished == FALSE &&
                        !(obj->properties.npc.action & (SILVER_COIN_COLLECTED << racer->playerIndex))) {
                        obj->properties.npc.action |= SILVER_COIN_COLLECTED << racer->playerIndex;
                        obj->properties.npc.timer = 16;
                        obj->segment.trans.flags |= OBJ_FLAGS_INVIS_PLAYER1 << racer->playerIndex;
                        music_jingle_play(SEQUENCE_SILVER_COIN_1 + racer->silverCoinCount);
                        racer->silverCoinCount++;
                    }
                }
            }
        }
        obj->segment.animFrame += 8 * updateRate;
    }
    if (obj->properties.npc.timer > 0) {
        obj->properties.npc.timer -= updateRate;
        obj->particleEmitFlags = OBJ_EMIT_PARTICLE_1;
        obj_spawn_particle(obj, updateRate);
    }
}

/**
 * Challenge Key init behaviour.
 * Sets hitbox info based off spawn info.
 * Deletes itself in tracks mode, or if it's already been collected.
 */
void obj_init_worldkey(Object *obj, LevelObjectEntry_WorldKey *entry) {
    Settings *settings;
    obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE;
    obj->interactObj->unk11 = 0;
    obj->interactObj->hitboxRadius = 30;
    entry->keyID &= 0xF;
    obj->properties.worldKey.keyID = entry->keyID;
    settings = get_settings();
    if (!is_in_tracks_mode() && !(settings->keys & (1 << obj->properties.worldKey.keyID))) {
        return;
    }
    free_object(obj);
}

/**
 * Challenge Key loop behaviour.
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
                    music_jingle_play(SEQUENCE_KEY_COLLECT);
                    settings = get_settings();
                    settings->keys |= 1 << worldKeyObj->properties.worldKey.keyID; // Set key flag
                    free_object(worldKeyObj);                                      // Makes the key unload.
                }
            }
        }
    }

    // Rotate world key
    worldKeyObj->segment.trans.rotation.y_rotation += updateRate * 0x100;
}

/**
 * Weapon Balloon init behaviour.
 * Sets scale and rotation based off spawn info.
 * Sets model ID based on balloon ID.
 */
void obj_init_weaponballoon(Object *obj, LevelObjectEntry_WeaponBalloon *entry) {
    s32 cheats;
    Object_WeaponBalloon *balloon;
    f32 scale;

    obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE;
    obj->interactObj->unk11 = 4;
    obj->interactObj->hitboxRadius = 20;

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

    if (obj->segment.object.modelIndex >= obj->segment.header->numberOfModelIds) {
        obj->segment.object.modelIndex = 0;
    }

    obj->segment.object.modelIndex = entry->balloonType;
    obj->properties.weaponBalloon.balloonID = obj->segment.object.modelIndex;

    scale = entry->scale & 0xFF;
    if (scale < 10) {
        scale = 10;
    }
    scale /= 64;

    balloon = &obj->unk64->weapon_balloon;

    obj->segment.trans.scale = obj->segment.header->scale * scale;
    balloon->scale = obj->segment.trans.scale;
    balloon->respawnTime = 0;
    obj->properties.weaponBalloon.particleTimer = 0;

    if (get_filtered_cheats() & CHEAT_DISABLE_WEAPONS) {
        free_object(obj);
    }
}

/**
 * Weapon Balloon loop func.
 * Checks for any racers going over it.
 * It gives them a weapon, then marks as disappeared, before slowly regrowing and becoming tangible again.
 */
void obj_loop_weaponballoon(Object *weaponBalloonObj, s32 updateRate) {
    UNUSED s32 pad;
    Object_Racer *racer;
    Object_WeaponBalloon *weaponBalloon;
    s8 *powerupTable;
    UNUSED s8 pad3;
    s8 prevBalloonQuantity;
    s8 levelMask;
    Object *whatObjInteracted;
    ObjectInteraction *interactObj;
    s32 prevBalloonType;

    weaponBalloon = (Object_WeaponBalloon *) weaponBalloonObj->unk64;
    weaponBalloonObj->segment.trans.scale = weaponBalloon->scale * (1.0 - (weaponBalloon->respawnTime / 90.0f));
    if (weaponBalloonObj->segment.trans.scale < 0.001) {
        weaponBalloonObj->segment.trans.scale = 0.001f;
    }
    if (weaponBalloonObj->segment.trans.scale < 0.1) {
        weaponBalloonObj->segment.trans.flags |= OBJ_FLAGS_INVISIBLE;
    } else {
        weaponBalloonObj->segment.trans.flags &= ~OBJ_FLAGS_INVISIBLE;
    }
    if (weaponBalloonObj->properties.weaponBalloon.particleTimer > 0) {
        weaponBalloonObj->particleEmitFlags = OBJ_EMIT_PARTICLE_1;
        obj_spawn_particle(weaponBalloonObj, updateRate);
        weaponBalloonObj->properties.weaponBalloon.particleTimer -= updateRate;
    }
    if (weaponBalloon->respawnTime != 0) {
        if (weaponBalloon->respawnTime != 90 || weaponBalloonObj->interactObj->distance >= 45) {
            weaponBalloon->respawnTime = (weaponBalloon->respawnTime - updateRate) - updateRate;
        }
        if (weaponBalloon->respawnTime < 0) {
            weaponBalloon->respawnTime = 0;
        }
    } else {
        interactObj = weaponBalloonObj->interactObj;
        if (interactObj->distance < 45) {
            whatObjInteracted = interactObj->obj;
            if (whatObjInteracted != NULL && whatObjInteracted->segment.header->behaviorId == BHV_RACER) {
                racer = &whatObjInteracted->unk64->racer;
                if (racer->vehicleID < VEHICLE_TRICKY || racer->playerIndex != PLAYER_COMPUTER) {
                    prevBalloonType = racer->balloon_type;
                    racer->balloon_type = weaponBalloonObj->properties.weaponBalloon.balloonID;
                    if (prevBalloonType == racer->balloon_type && racer->balloon_quantity != 0) {
                        racer->balloon_level++;
                    } else {
                        racer->balloon_level = 0;
                    }
                    // Disallow level 3 balloons in challenge mode
                    if (get_current_level_race_type() & RACETYPE_CHALLENGE) {
                        if (racer->balloon_level > 1) {
                            racer->balloon_level = 1;
                        }
                        // And instantly upgrade oil slicks to tripmines.
                        if (racer->balloon_type == BALLOON_TYPE_TRAP) {
                            racer->balloon_level = 1;
                        }
                    }
                    levelMask = 3; // 3 isn't an attainable level so the future check won't be true if the item's
                                   // already max level.
                    if (get_filtered_cheats() & CHEAT_MAXIMUM_POWER_UP) {
                        racer->balloon_level = 2;
                    }
                    if (racer->balloon_level > 2) {
                        racer->balloon_level = 2;
                        levelMask = 2;
                    }
                    powerupTable = (s8 *) get_misc_asset(ASSET_MISC_BALLOON_DATA);
                    prevBalloonQuantity = racer->balloon_quantity;
                    racer->balloon_quantity = powerupTable[(racer->balloon_type * 10) + (racer->balloon_level * 2) + 1];
                    racer->unk209 |= 1;
                    if (get_number_of_active_players() < THREE_PLAYERS) {
                        weaponBalloonObj->properties.weaponBalloon.particleTimer = 16;
                    }
                    if (racer->playerIndex == PLAYER_COMPUTER) {
                        play_sound_at_position(SOUND_BALLOON_POP, weaponBalloonObj->segment.trans.x_position,
                                               weaponBalloonObj->segment.trans.y_position,
                                               weaponBalloonObj->segment.trans.z_position, 4, NULL);
                    } else {
                        if (levelMask == racer->balloon_level) {
                            if (racer->raceFinished == FALSE) {
                                if (prevBalloonQuantity != racer->balloon_quantity) {
                                    hud_sound_play_delayed(SOUND_VOICE_TT_POWERUP, 1.0f, racer->playerIndex);
                                    prevBalloonQuantity = racer->balloon_level;
                                    if (prevBalloonQuantity > 2) {
                                        prevBalloonQuantity = 2;
                                    }
                                    sound_play(SOUND_COLLECT_ITEM + prevBalloonQuantity, NULL);
                                } else {
                                    play_sound_at_position(SOUND_BALLOON_POP,
                                                           weaponBalloonObj->segment.trans.x_position,
                                                           weaponBalloonObj->segment.trans.y_position,
                                                           weaponBalloonObj->segment.trans.z_position, 4, NULL);
                                }
                            }
                        } else if (racer->raceFinished == FALSE) {
                            if (racer->balloon_level > 0) {
                                hud_sound_play_delayed(SOUND_VOICE_TT_POWERUP, 1.0f, racer->playerIndex);
                            }
                            sound_play(SOUND_COLLECT_ITEM + racer->balloon_level, NULL);
                        }
                    }
                    weaponBalloonObj->particleEmitFlags = OBJ_EMIT_PARTICLE_1;
                    obj_spawn_particle(weaponBalloonObj, updateRate);
                    weaponBalloon->respawnTime = 90;
                }
            }
        }
    }
}

/**
 * Balloon Burst Effect init behaviour.
 * Does nothing.
 */
void obj_init_wballoonpop(UNUSED Object *obj, UNUSED LevelObjectEntry_WBalloonPop *entry) {
}

/**
 * Balloon Burst Effect loop behaviour.
 * Does nothing.
 */
void obj_loop_wballoonpop(UNUSED Object *obj, UNUSED s32 updateRate) {
}

/**
 * Racer weapon init behaviour.
 * Sets hitbox info so racers can interact with it.
 * Also sets a timer to remove the object after that many frames.
 */
void obj_init_weapon(Object *obj, UNUSED LevelObjectEntry_Weapon *entry) {
    obj->interactObj->flags = INTERACT_FLAGS_TANGIBLE;
    obj->interactObj->unk11 = 0;
    obj->interactObj->hitboxRadius = 24;
    obj->interactObj->pushForce = 0;
    obj->properties.projectile.timer = normalise_time(480);
    obj->properties.projectile.unk4 = 0;
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
            weapon_projectile(obj, updateRate);
            break;
        case WEAPON_TRIPMINE:
        case WEAPON_OIL_SLICK:
        case WEAPON_BUBBLE_TRAP:
        case WEAPON_UNK_11:
            weapon_trap(obj, updateRate);
            break;
    }
    return;
}

/**
 * Firing a standard rocket makes it fly forward.
 * A homing rocket uses the checkpoint system to path towards its victim.
 * When it collides with a racer, they're launched into the air.
 */
void weapon_projectile(Object *obj, s32 updateRate) {
    Object *interactObj;
    Object_Racer *weaponOwner;
    Object_Weapon *weapon;
    Object *temp_s1_2;
    UNUSED s32 pad;
    Vec3f offset;
    f32 radius;
    f32 updateRateF;
    f32 posX;
    f32 posY;
    f32 posZ;
    f32 diffX;
    f32 diffY;
    f32 diffZ;
    s32 hasCollision;
    s32 size;
    s32 numCheckpoints;
    Object_Racer *racer;
    s8 surface;
    Matrix mtxf;
    ObjectTransform trans;

    obj->interactObj->flags |= INTERACT_FLAGS_UNK_0100;
    weapon = (Object_Weapon *) obj->unk64;
    posX = obj->segment.trans.x_position;
    posY = obj->segment.trans.y_position;
    posZ = obj->segment.trans.z_position;
    trans.rotation.y_rotation = obj->segment.trans.rotation.y_rotation;
    trans.rotation.x_rotation = obj->segment.trans.rotation.x_rotation;
    trans.rotation.z_rotation = 0;
    trans.x_position = 0.0f;
    trans.y_position = 0.0f;
    trans.z_position = 0.0f;
    trans.scale = 1.0f;
    object_transform_to_matrix(mtxf, &trans);
    guMtxXFMF(mtxf, 0.0f, 0.0f, weapon->forwardVel, &obj->segment.x_velocity, &obj->segment.y_velocity,
              &obj->segment.z_velocity);
    updateRateF = updateRate;
    if (osTvType == OS_TV_TYPE_PAL) {
        updateRateF *= 1.2;
    }
    offset.x = obj->segment.trans.x_position + (obj->segment.x_velocity * updateRateF);
    offset.y = obj->segment.trans.y_position + (obj->segment.y_velocity * updateRateF);
    offset.z = obj->segment.trans.z_position + (obj->segment.z_velocity * updateRateF);
    if (weapon->weaponID != WEAPON_MAGNET_LEVEL_3) {
        radius = 16.0f;
        func_80031130(1, &obj->segment.trans.x_position, (f32 *) &offset, -1);
        hasCollision = FALSE;
        surface = SURFACE_NONE;
        func_80031600(&obj->segment.trans.x_position, (f32 *) &offset, &radius, &surface, TRUE, &hasCollision);
        if (hasCollision > 0) {
            if (func_8002ACD4(&diffX, &diffY, &diffZ)) {
                obj->properties.projectile.timer = 0;
            }
        }
    }
    diffX = offset.x - posX;
    diffY = offset.y - posY;
    diffZ = offset.z - posZ;
    if (move_object(obj, diffX, diffY, diffZ)) {
        obj->properties.projectile.timer = 0;
    }
    diffX = ((diffX * diffX) + (diffZ * diffZ)) / updateRateF;
    diffZ = (weapon->forwardVel * weapon->forwardVel) / 2;
    if (diffX < diffZ) {
        obj->properties.projectile.timer = 0;
    }
    if (weapon->weaponID == WEAPON_ROCKET_HOMING) {
        numCheckpoints = get_checkpoint_count();
        if (numCheckpoints > 0) {
            if (func_800185E4(weapon->checkpoint, obj, posX, posY, posZ, &weapon->checkpointDist, (u8 *) &surface) ==
                FALSE) {
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
    // TODO: Fix these gotos.
    if (obj->interactObj->obj != NULL) {
        interactObj = obj->interactObj->obj;
        if (interactObj == weapon->owner) {
            if (obj->properties.projectile.timer < normalise_time(450) && obj->properties.projectile.timer) {
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
                    weaponOwner->boost_sound |= BOOST_SOUND_UNK2;
                }
                if (racer->raceFinished == FALSE) {
                    rumble_set(racer->playerIndex, RUMBLE_TYPE_9);
                }
            }
            obj_spawn_effect(obj->segment.trans.x_position, obj->segment.trans.y_position,
                             obj->segment.trans.z_position, ASSET_OBJECT_ID_BOMBEXPLOSION, SOUND_EXPLOSION, 1.0f, 1);
            free_object(obj);
            return;
        }
    }
block_37:
    obj->properties.projectile.unk4 += updateRate;
    if (obj->unk60 != NULL) {
        temp_s1_2 = (Object *) obj->unk60->unk4[0];
        if (obj->properties.projectile.unk4 < 8) {
            temp_s1_2->segment.trans.scale = obj->properties.projectile.unk4 * 0.5f;
        } else if (obj->properties.projectile.unk4 < 16) {
            temp_s1_2->segment.trans.scale = 4.0f - ((obj->properties.projectile.unk4 - 8) * 0.25f);
        } else {
            temp_s1_2->segment.trans.scale = (sins_f(obj->properties.projectile.unk4 << 12) * 0.25f) + 2.0f;
        }
    }
    obj->properties.projectile.timer -= updateRate;
    if (obj->properties.projectile.timer < 0) {
        obj_spawn_effect(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position,
                         ASSET_OBJECT_ID_BOMBEXPLOSION, SOUND_EXPLOSION, 1.0f, 1);
        free_object(obj);
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
            angleDiff = angle - (obj->segment.trans.rotation.y_rotation & 0xFFFF);
            WRAP(angleDiff, -0x8000, 0x8000);
            if (angleDiff > 0x6000 || angleDiff < -0x6000) {
                obj->interactObj->obj = (Object *) interactedObj;
                obj->interactObj->distance = 1;
            }
            obj->segment.trans.rotation.x_rotation = arctan2_f(diffY, dist);
            obj->segment.trans.rotation.y_rotation = angle;
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
            sp58 = func_8001955C(obj, rocket->checkpoint, racer->racer.unk1C8, rocket->unk14, rocket->unk16,
                                 rocket->checkpointDist, &diffX, &diffY, &diffZ);
            sineY = arctan2_f(diffY, 500.0f) & 0xFFFF;
            shift = 3;
        } else {
            rocket->hitObj = targetObj;
            rocket->forwardVel = -25.0f;
            sp58 = FALSE;
        }
        angle = (arctan2_f(diffX, diffZ) - 0x8000) & 0xFFFF;
        angleDiff = angle - (obj->segment.trans.rotation.y_rotation & 0xFFFF);
        WRAP(angleDiff, -0x8000, 0x8000);
        if (sp58) {
            obj->segment.trans.rotation.y_rotation += (angleDiff * updateRate) >> shift;
            angleDiff = sineY - (obj->segment.trans.rotation.x_rotation & 0xFFFF);
            WRAP(angleDiff, -0x8000, 0x8000);
            obj->segment.trans.rotation.x_rotation += (angleDiff * updateRate) >> shift;
        } else {
            if (angleDiff > 0x6000 || angleDiff < -0x6000) {
                obj->interactObj->obj = targetObj;
                obj->interactObj->distance = 1;
            }
            obj->segment.trans.rotation.x_rotation = arctan2_f(diffY, dist) & 0xFFFFu;

            obj->segment.trans.rotation.y_rotation = angle;
        }
    }
    play_rocket_trailing_sound(obj, rocket, SOUND_HOMING_ROCKET);
    if (get_number_of_active_players() < 3) {
        obj->particleEmitFlags |= OBJ_EMIT_PARTICLE_1;
        obj_spawn_particle(obj, updateRate);
    }
}

/**
 * Set the rocket sound timer back to zero.
 */
void reset_rocket_sound_timer(void) {
    gRocketSoundTimer = 0;
}

/**
 * Reduce the rocket sound timer by 1 increment.
 */
void decrease_rocket_sound_timer(void) {
    gRocketSoundTimer--;
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
    s32 i;

    shouldPlaySound = FALSE;
    racerGroup = get_racer_objects_by_port(&numRacers);
    for (i = 0; i < numRacers; i++) {
        racer = racerGroup[i];
        if (weapon->owner != racerGroup[i] && racer->unk64->racer.playerIndex != PLAYER_COMPUTER) {
            diffX = racer->segment.trans.x_position - obj->segment.trans.x_position;
            diffY = racer->segment.trans.y_position - obj->segment.trans.y_position;
            diffZ = racer->segment.trans.z_position - obj->segment.trans.z_position;
            distance = sqrtf((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ));
            if (distance <= sound_distance(soundID)) {
                shouldPlaySound = TRUE;
            }
        }
    }
    if (shouldPlaySound) {
        if (weapon->soundMask == NULL) {
            if (gRocketSoundTimer < 8) {
                play_sound_at_position(soundID, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                       obj->segment.trans.z_position, 1, &weapon->soundMask);
                gRocketSoundTimer++;
            }
        } else {
            update_spatial_audio_position(weapon->soundMask, obj->segment.trans.x_position,
                                          obj->segment.trans.y_position, obj->segment.trans.z_position);
        }
    } else {
        if (weapon->soundMask) {
            func_800096F8(weapon->soundMask);
            weapon->soundMask = NULL;
            gRocketSoundTimer -= 1;
        }
    }
}

/**
 * Handles all the trap weapon behaviour.
 * When dropped, will fall to the ground, provided the user wasn't in a plane.
 * Once on the ground, will count up until it reaches the target and consider itself armed.
 * The timer is used for scaling the trap, which the bubble and oil slick use.
 * If triggered, the trap will perform different behaviours depending on what it is, then remove itself.
 */
void weapon_trap(Object *weaponObj, s32 updateRate) {
    Object *weaponInteractObj;
    Object_Racer *weaponHit;
    Object_Racer *weaponOwner;
    Vec3f intendedPos;
    f32 radius;
    f32 updateRateF;
    s32 hasCollision;
    s32 hitDist;
    s8 surface;
    Object_Weapon *weapon;
    ObjPropertyWeapon *weaponProperties;

    weapon = &weaponObj->unk64->weapon;
    weaponOwner = &weapon->owner->unk64->racer;
    updateRateF = updateRate;
    weaponProperties = &weaponObj->properties.weapon;
    if (osTvType == OS_TV_TYPE_PAL) {
        updateRateF *= 1.2;
    }
    if (weaponProperties->status == WEAPON_DROPPED) {
        intendedPos.x = weaponObj->segment.trans.x_position + (weaponObj->segment.x_velocity * updateRateF);
        intendedPos.y = weaponObj->segment.trans.y_position + (weaponObj->segment.y_velocity * updateRateF);
        intendedPos.z = weaponObj->segment.trans.z_position + (weaponObj->segment.z_velocity * updateRateF);
        radius = 9.0f;
        func_80031130(1, &weaponObj->segment.trans.x_position, &intendedPos.x, -1);
        hasCollision = FALSE;
        surface = -1;
        func_80031600(&weaponObj->segment.trans.x_position, &intendedPos.x, &radius, &surface, 1, &hasCollision);
        weaponObj->segment.x_velocity = (intendedPos.x - weaponObj->segment.trans.x_position) / updateRateF;
        weaponObj->segment.y_velocity = (intendedPos.y - weaponObj->segment.trans.y_position) / updateRateF;
        weaponObj->segment.z_velocity = (intendedPos.z - weaponObj->segment.trans.z_position) / updateRateF;
        weaponObj->segment.trans.x_position = intendedPos.x;
        weaponObj->segment.trans.y_position = intendedPos.y;
        weaponObj->segment.trans.z_position = intendedPos.z;
        if (hasCollision || weaponOwner->vehicleID == VEHICLE_PLANE) {
            weaponObj->segment.x_velocity = 0.0f;
            weaponObj->segment.z_velocity = 0.0f;
            weaponProperties->status = WEAPON_ARMED;
            weaponProperties->submerged = 0;
            weaponProperties->scale = 0;
            if (weapon->weaponID == WEAPON_BUBBLE_TRAP) {
                weaponObj->segment.trans.y_position += 16.0f;
            }
        }
        radius = -10000.0f;
        if (func_8002B9BC(weaponObj, &radius, NULL, 1) && (weaponObj->segment.trans.y_position < radius)) {
            weaponProperties->status = WEAPON_ARMED;
            weaponProperties->submerged = 1;
            weaponProperties->scale = 0;
            if (weapon->weaponID == WEAPON_BUBBLE_TRAP) {
                weaponObj->segment.trans.y_position += 16.0f;
            }
        }
    }
    if (weapon->weaponID == WEAPON_OIL_SLICK) {
        if (weaponProperties->status != WEAPON_DROPPED) {
            if (weaponProperties->status == WEAPON_ARMED) {
                weaponProperties->scale += updateRate;
                if (weaponProperties->scale > 12) {
                    weaponProperties->scale = 12;
                }
            } else {
                weaponProperties->scale -= updateRate;
                if (weaponProperties->scale <= 0) {
                    weaponProperties->scale = 1;
                    free_object(weaponObj);
                }
            }
            if (weaponOwner->vehicleID != VEHICLE_PLANE) {
                if (weaponProperties->submerged != 0) {
                    weaponObj->waterEffect->scale = weaponProperties->scale * 0.6f;
                } else {
                    weaponObj->shadow->scale = weaponProperties->scale * 0.6f;
                }
                weaponObj->segment.trans.flags |= OBJ_FLAGS_SHADOW_ONLY;
            }
        }
    }
    if (weapon->weaponID == WEAPON_BUBBLE_TRAP) {
        if (weapon->target != NULL) {
            weaponObj->segment.trans.x_position = 0.0f;
            weaponObj->segment.trans.y_position = 0.0f;
            weaponObj->segment.trans.z_position = 0.0f;
            ignore_bounds_check();
            move_object(weaponObj, weapon->target->segment.trans.x_position, weapon->target->segment.trans.y_position,
                        weapon->target->segment.trans.z_position);
        }
        if (weaponProperties->status == WEAPON_ARMED || weaponProperties->status == WEAPON_TRIGGERED) {
            weaponProperties->scale += updateRate;
            if (weaponProperties->scale > 20) {
                weaponProperties->scale = 20;
            }
        }
        if (weaponProperties->status == WEAPON_TRIGGERED) {
            weaponProperties->submerged += updateRate;
            if (weaponProperties->submerged > 120) {
                weaponProperties->status = WEAPON_DESTROY;
                if (weapon->soundMask != NULL) {
                    func_800096F8(weapon->soundMask);
                    weapon->soundMask = NULL;
                }
                play_sound_at_position(SOUND_POP, weaponObj->segment.trans.x_position,
                                       weaponObj->segment.trans.y_position, weaponObj->segment.trans.z_position, 4,
                                       NULL);
            }
        }
        if (weaponProperties->status == WEAPON_DESTROY) {
            weaponObj->particleEmitFlags = OBJ_EMIT_PARTICLE_1;
            obj_spawn_particle(weaponObj, updateRate);
            weaponObj->segment.trans.flags |= OBJ_FLAGS_INVISIBLE;
            weaponProperties->scale -= updateRate;
            if (weaponProperties->scale < 1) {
                weaponProperties->scale = 1;
                free_object(weaponObj);
            }
        }
        if (weaponProperties->status != WEAPON_DROPPED) {
            weaponObj->segment.trans.scale = weaponProperties->scale * 0.075f;
        }
        weaponObj->segment.animFrame += updateRate * 16;
    }
    if (weaponProperties->status < WEAPON_TRIGGERED) {
        hitDist = 60;
        if (weaponOwner->vehicleID != VEHICLE_PLANE) {
            hitDist = 34;
            weaponObj->segment.y_velocity -= 2.0;
            weaponObj->segment.x_velocity -= (weaponObj->segment.x_velocity / 8);
            weaponObj->segment.z_velocity -= (weaponObj->segment.z_velocity / 8);
        } else {
            weaponObj->segment.y_velocity = 0.0f;
            weaponObj->segment.animFrame += updateRate * 8;
        }
        if (weapon->weaponID == WEAPON_BUBBLE_TRAP || weapon->weaponID == WEAPON_OIL_SLICK) {
            hitDist += hitDist >> 1;
        }
        weaponInteractObj = weaponObj->interactObj->obj;
        if (weaponInteractObj != NULL) {
            if (weapon->owner != weaponObj->interactObj->obj || weaponProperties->decayTimer < normalise_time(450)) {
                if (weaponObj->interactObj->distance < hitDist) {
                    weaponInteractObj = weaponObj->interactObj->obj;
                    if (weaponInteractObj->segment.header->behaviorId == BHV_RACER) {
                        weaponHit = &weaponInteractObj->unk64->racer;
                        weaponHit->attackType = ATTACK_EXPLOSION;
                        if (weapon->weaponID == WEAPON_TRIPMINE) {
                            obj_spawn_effect(weaponObj->segment.trans.x_position, weaponObj->segment.trans.y_position,
                                             weaponObj->segment.trans.z_position, ASSET_OBJECT_ID_BOMBEXPLOSION,
                                             SOUND_EXPLOSION, 1.0f, 1);
                        } else if (weapon->weaponID == WEAPON_BUBBLE_TRAP) {
                            if (weaponHit->shieldTimer > 0 && weaponHit->shieldType >= SHIELD_LEVEL3) {
                                weaponProperties->status = WEAPON_DESTROY;

                                play_sound_at_position(SOUND_POP, weaponObj->segment.trans.x_position,
                                                       weaponObj->segment.trans.y_position,
                                                       weaponObj->segment.trans.z_position, 4, NULL);
                            } else {
                                weapon->target = weaponInteractObj;

                                play_sound_at_position(SOUND_BUBBLE, weaponInteractObj->segment.trans.x_position,
                                                       weaponInteractObj->segment.trans.y_position,
                                                       weaponInteractObj->segment.trans.z_position, 4,
                                                       &weapon->soundMask);
                                weaponHit->attackType = ATTACK_BUBBLE;
                                weaponProperties->status = WEAPON_TRIGGERED;
                                weaponProperties->submerged = 0;
                            }
                        } else if (weapon->weaponID == WEAPON_OIL_SLICK) {
                            weaponHit->attackType = ATTACK_SPIN;
                            weaponProperties->status = WEAPON_TRIGGERED;
                        }
                        if (!weaponHit->raceFinished) {
                            rumble_set(weaponHit->playerIndex, RUMBLE_TYPE_13);
                        }
                        weaponOwner = &weapon->owner->unk64->racer;
                        if (weaponHit->playerIndex != PLAYER_COMPUTER || weaponOwner->playerIndex != PLAYER_COMPUTER) {
                            weaponOwner->boost_sound |= BOOST_SOUND_UNK2;
                        }
                        if (weapon->weaponID != WEAPON_OIL_SLICK && weapon->weaponID != WEAPON_BUBBLE_TRAP) {
                            free_object(weaponObj);
                            return;
                        }
                    }
                }
            }
        }
        weaponProperties->decayTimer -= updateRate;
        if (weaponProperties->status < WEAPON_TRIGGERED) {
            if (weaponProperties->decayTimer < normalise_time(-1320)) {
                if (weapon->weaponID == WEAPON_OIL_SLICK) {
                    weaponProperties->status = WEAPON_TRIGGERED;
                } else if ((weapon->weaponID == WEAPON_BUBBLE_TRAP)) {
                    weaponProperties->status = WEAPON_DESTROY;
                    play_sound_at_position(SOUND_POP, weaponObj->segment.trans.x_position,
                                           weaponObj->segment.trans.y_position, weaponObj->segment.trans.z_position, 4,
                                           NULL);
                } else {
                    obj_spawn_effect(weaponObj->segment.trans.x_position, weaponObj->segment.trans.y_position,
                                     weaponObj->segment.trans.z_position, ASSET_OBJECT_ID_BOMBEXPLOSION,
                                     SOUND_EXPLOSION, 1.0f, 1);
                    free_object(weaponObj);
                }
            }
        }
    }
}

/**
 * Create a special effect at the given position.
 * Plays a sound if one is given.
 */
void obj_spawn_effect(f32 x, f32 y, f32 z, s32 objectID, s32 soundID, f32 scale, s32 arg6) {
    LevelObjectEntry8003FC44 spawnObj;
    Object *newObj;

    spawnObj.common.x = x;
    spawnObj.common.y = (s16) y + 36;
    spawnObj.common.z = z;
    spawnObj.common.size = 10;
    spawnObj.common.objectID = objectID;
    spawnObj.unk9 = arg6;
    newObj = spawn_object((LevelObjectEntryCommon *) &spawnObj, 1);
    if (newObj != NULL) {
        newObj->segment.level_entry = NULL;
        newObj->segment.x_velocity = 0.0f;
        newObj->segment.y_velocity = 0.0f;
        newObj->segment.z_velocity = 0.0f;
        newObj->segment.trans.scale = newObj->segment.trans.scale * 3.5 * scale;
    }
    if (soundID != SOUND_NONE) {
        play_sound_at_position(soundID, x, y, z, 4, NULL);
    }
}

void obj_init_audio(Object *obj, LevelObjectEntry_Audio *entry) {
    Object_Audio *obj64;

    obj64 = &obj->unk64->audio;
    obj64->soundId = entry->soundId;
    obj64->unk2 = entry->unkA;
    obj64->unkC = entry->unkF;
    obj64->unk6 = entry->unkE;
    obj64->unk4 = entry->unkC;
    obj64->unk5 = entry->unkD;
    obj64->unkD = entry->unk10;
    obj64->soundMask = NULL;
    if (gSoundBank_GetSoundDecayTime(obj64->soundId)) {
        func_8000974C(obj64->soundId, entry->common.x, entry->common.y, entry->common.z, 9, obj64->unk5, obj64->unk4,
                      obj64->unk2, obj64->unkC, obj64->unk6, obj64->unkD, &obj64->soundMask);
    } else {
        func_8000974C(obj64->soundId, entry->common.x, entry->common.y, entry->common.z, 10, obj64->unk5, obj64->unk4,
                      obj64->unk2, obj64->unkC, obj64->unk6, obj64->unkD, &obj64->soundMask);
    }
    free_object(obj);
}

/* Official name: audioLineInit */
void obj_init_audioline(Object *obj, LevelObjectEntry_AudioLine *entry) {
    Object_AudioLine *audLine;

    audLine = &obj->unk64->audio_line;
    audLine->unk0 = entry->unk8;
    audLine->soundID = entry->soundID;
    audLine->lineID = entry->lineID;
    audLine->unkD = entry->unkD;
    audLine->unk_union.unk8_word = 0;
    audLine->unk4 = entry->unkE;
    audLine->unk11 = entry->unk12;
    audLine->unk10 = entry->unk11;
    audLine->unkE = entry->unk9;
    audLine->unkF = entry->unk10;
    audLine->unk12 = entry->unk13;
    audioline_ambient_create(audLine->unk0, audLine->soundID, entry->common.x, entry->common.y, entry->common.z,
                             audLine->unkF, audLine->unkE, audLine->unk10, audLine->unk12, audLine->unk4,
                             audLine->unk11, audLine->lineID, audLine->unkD);
    free_object(obj);
}

void obj_init_audioreverb(Object *obj, LevelObjectEntry_AudioReverb *entry) {
    s32 temp;
    Object_AudioReverb *reverb = &obj->unk64->audio_reverb;
    reverb->unk2 = entry->unk8;
    temp = entry->lineID;
    reverb->lineID = temp & 0xFF;
    reverb->unk5 = entry->unkA;
    func_80009968(entry->common.x, entry->common.y, entry->common.z, reverb->unk2, reverb->lineID, reverb->unk5);
    free_object(obj);
}

/* Official name: texscrollInit */
void obj_init_texscroll(Object *obj, LevelObjectEntry_TexScroll *entry, s32 arg2) {
    Object_TexScroll *obj64;
    LevelModel *levelModel;
    s16 numberOfTexturesInLevel;

    obj64 = &obj->unk64->tex_scroll;
    levelModel = get_current_level_model();
    obj64->textureIndex = entry->textureIndex;
    if (obj64->textureIndex < 0) {
        obj64->textureIndex = 0;
    }
    numberOfTexturesInLevel = levelModel->numberOfTextures;
    if (obj64->textureIndex >= numberOfTexturesInLevel) {
        obj64->textureIndex = numberOfTexturesInLevel - 1;
    }
    obj64->unk4 = entry->unkA;
    obj64->unk6 = entry->unkB;
    if (arg2 == 0) {
        obj64->unk8 = 0;
        obj64->unkA = 0;
    }
}

void obj_loop_texscroll(Object *obj, s32 updateRate) {
    s32 pad[2];
    LevelModel *levelModel;
    LevelModelSegment *curBlock;
    Object_64 *obj64;
    Triangle *curTriangle;
    TriangleBatchInfo *curBatch;
    s32 prevUnk8;
    s32 prevUnkA;
    s32 tri;
    s32 uShift;
    s32 vShift;
    s32 block;
    s32 batch;
    TextureInfo *texture;
    TextureHeader *tex;
    s32 texIndex;
    s32 temp;
    s32 temp2;
    u8 temp3;
    s32 t0;
    s32 t1;
    s32 i;
    s32 j;

    obj64 = obj->unk64;
    levelModel = get_current_level_model();

    t0 = obj64->tex_scroll.unk4;
    t1 = obj64->tex_scroll.unk6;

    tex = levelModel->textures[obj64->tex_scroll.textureIndex].texture;

    uShift = tex->width;
    vShift = tex->height;
    uShift <<= 8;
    vShift <<= 8;

    t0 *= updateRate;
    t1 *= updateRate;

    obj64->tex_scroll.unk8 += t0;
    obj64->tex_scroll.unkA += t1;

    t0 = obj64->tex_scroll.unk8;
    t1 = obj64->tex_scroll.unkA;

    obj64->tex_scroll.unk8 &= 3;
    obj64->tex_scroll.unkA &= 3;

    t0 = t0 >> 2;
    t1 = ((t1 >> 2) & 0xFFFFFFFFFFFFFFFF); // fake

    curBlock = levelModel->segments;
    for (i = 0; i < levelModel->numberOfSegments; i++) {
        curBatch = curBlock[i].batches;
        for (j = 0; j < curBlock[i].numberOfBatches; j++) {
            if ((curBatch[j].textureIndex == obj64->tex_scroll.textureIndex)) {
                for (tri = curBatch[j].facesOffset; tri < curBatch[j + 1].facesOffset; tri++) {
                    curTriangle = &curBlock[i].triangles[tri];
                    if (!(curTriangle->flags & 0x80)) {
                        if (vShift < curTriangle->uv0.v) {
                            curTriangle->uv0.v -= vShift;
                            curTriangle->uv1.v -= vShift;
                            curTriangle->uv2.v -= vShift;
                        }
                        if (curTriangle->uv0.v < 0) {
                            curTriangle->uv0.v += vShift;
                            curTriangle->uv1.v += vShift;
                            curTriangle->uv2.v += vShift;
                        }
                        if (uShift < curTriangle->uv0.u) {
                            curTriangle->uv0.u -= uShift;
                            curTriangle->uv1.u -= uShift;
                            curTriangle->uv2.u -= uShift;
                        }
                        if (curTriangle->uv0.u < 0) {
                            curTriangle->uv0.u += uShift;
                            curTriangle->uv1.u += uShift;
                            curTriangle->uv2.u += uShift;
                        }

                        curTriangle->uv0.v += t1;
                        curTriangle->uv1.v += t1;
                        curTriangle->uv2.v += t1;
                        curTriangle->uv0.u += t0;
                        curTriangle->uv1.u += t0;
                        curTriangle->uv2.u += t0;
                    }
                }
            }
        }
    }
}

/* Official name: rgbalightInit */
void obj_init_rgbalight(Object *obj, LevelObjectEntry_RgbaLight *entry, UNUSED s32 arg2) {
    obj->unk64 = (Object_64 *) func_80031CAC(obj, entry);
}

/**
 * Floating buoy init behaviour.
 * Sets hitbox data from spawn info.
 */
void obj_init_buoy_pirateship(Object *obj, UNUSED LevelObjectEntry_Buoy_PirateShip *entry, UNUSED s32 arg2) {
    obj->unk64 =
        func_800BE654(obj->segment.object.segmentID, obj->segment.trans.x_position, obj->segment.trans.z_position);
    obj->interactObj->flags = INTERACT_FLAGS_SOLID;
    obj->interactObj->unk11 = 0;
    obj->interactObj->hitboxRadius = 30;
    obj->interactObj->pushForce = 0;
}

/**
 * Floating buoy loop behaviour.
 * Exists to serve as an outer bound for water courses.
 * All it does is stays afloat on water and scrolls through each texture.
 */
void obj_loop_buoy_pirateship(Object *obj, s32 updateRate) {
    if (obj->unk64 != NULL) {
        obj->segment.trans.y_position = log_wave_height((Object_Log *) obj->unk64, updateRate);
    }
    obj->segment.animFrame += updateRate * 8;
}

/**
 * Spinning log init behaviour.
 * Sets scale, angle and hitbox data based off the spawn info.
 */
void obj_init_log(Object *obj, LevelObjectEntry_Log *entry, UNUSED s32 arg2) {
    f32 radius;
    obj->unk64 =
        func_800BE654(obj->segment.object.segmentID, obj->segment.trans.x_position, obj->segment.trans.z_position);
    obj->interactObj->flags = INTERACT_FLAGS_SOLID;
    obj->interactObj->unk11 = 2;
    obj->interactObj->hitboxRadius = 30;
    radius = entry->radius & 0xFF;
    if (radius < 10.0f) {
        radius = 10.0f;
    }
    radius /= 64;
    obj->segment.trans.scale = obj->segment.header->scale * radius;
    obj->segment.object.modelIndex = entry->modelIndex;
    obj->segment.trans.rotation.y_rotation = U8_ANGLE_TO_U16(entry->angleY);
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
        obj->segment.trans.y_position = log_wave_height(log, updateRate);
    } else {
        obj->segment.trans.y_position = ((LevelObjectEntryCommon *) obj->segment.level_entry)->y;
    }
    if (obj->unk5C->unk100 != NULL) {
        obj->properties.log.velocityY++;
        racerObj = (Object *) obj->unk5C->unk100;
        if (racerObj->behaviorId == BHV_RACER) {
            racer = (Object_Racer *) racerObj->unk64;
            if (racer->velocity < -4.0 && racer->raceFinished == FALSE) {
                rumble_set(racer->playerIndex, RUMBLE_TYPE_18);
            }
        }
        sine = sins_f(-obj->segment.trans.rotation.y_rotation);
        cosine = coss_f(-obj->segment.trans.rotation.y_rotation);

        // This looks a bit messy, but is required to match.
        diffX = obj->segment.trans.x_position - racerObj->segment.trans.x_position;
        diffZ = obj->segment.trans.z_position - racerObj->segment.trans.z_position;
        diffX = (diffX * cosine) + (diffZ * sine);
        diffZ = (racerObj->segment.x_velocity * sine) - (racerObj->segment.z_velocity * cosine);
        diffX *= diffZ;
        obj->properties.log.angleVel -= (s32) (diffX / 4);

        if (obj->properties.log.angleVel > 0x200) {
            obj->properties.log.angleVel = 0x200;
        }
        if (obj->properties.log.angleVel < -0x200) {
            obj->properties.log.angleVel = -0x200;
        }
    } else {
        if (obj->properties.log.velocityY > 0) {
            obj->properties.log.velocityY--;
        }
    }
    obj->segment.trans.y_position -= (f32) obj->properties.log.velocityY * 1.0;
    if (obj->properties.log.angleVel > 0) {
        obj->properties.log.angleVel -= updateRate;
        if (obj->properties.log.angleVel < 0) {
            obj->properties.log.angleVel = 0;
        }
    }
    if (obj->properties.log.angleVel < 0) {
        obj->properties.log.angleVel += updateRate;
        if (obj->properties.log.angleVel > 0) {
            obj->properties.log.angleVel = 0;
        }
    }
    obj->segment.trans.rotation.y_rotation += obj->properties.log.angleVel * updateRate;
    obj->unk5C->unk100 = NULL;
}

/* Official name: weatherInit */
void obj_init_weather(Object *obj, LevelObjectEntry_Weather *entry) {
    f32 radius = entry->radius;
    radius *= radius;
    obj->properties.distance.radius = radius;
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
        dist = obj->properties.distance.radius;
        entry = (LevelObjectEntry_Weather *) obj->segment.level_entry;
        if ((diffX * diffX) + (diffZ * diffZ) <= dist) {
            if (((!obj->segment.level_entry) && (!obj->segment.level_entry)) && (!obj->segment.level_entry)) {
            } // Fakematch
            weather_set(entry->unkA * 256, entry->unkC * 256, entry->unkE * 256, entry->unk10 * 257, entry->unk11 * 257,
                        entry->unk12);
        }
    }
}

/**
 * Lens Flare init func.
 * Calls the function to initialise the lens flare system, using presets.
 */
void obj_init_lensflare(Object *obj, UNUSED LevelObjectEntry_LensFlare *entry) {
    lensflare_init(obj);
}

/**
 * Lens Flare Override init func.
 * Calls a function adding the object to the lens flare system,
 * so the rendering portion knows to disable lens flares when inside.
 */
void obj_init_lensflareswitch(Object *obj, LevelObjectEntry_LensFlareSwitch *entry, UNUSED s32 arg2) {
    lensflare_override_add(obj);
    obj->segment.trans.scale = entry->radius;
    obj->segment.trans.scale /= 40.0f;
}

void obj_init_wavegenerator(Object *obj, UNUSED LevelObjectEntry_WaveGenerator *entry, UNUSED s32 arg2) {
    func_800BF524(obj);
}

void obj_init_butterfly(Object *butterflyObj, LevelObjectEntry_Butterfly *butterflyEntry, s32 param) {
    Object_Butterfly *butterfly;
    s32 uMask;
    s32 vMask;
    s32 i;

    butterfly = &butterflyObj->unk64->butterfly;
    if (param == 0) {
        butterflyObj->segment.y_velocity = 0.0f;
        butterfly->unkFE = 0;
        butterfly->unk100 = 0;
        butterfly->unk104 = 0;
        butterfly->unkFD = 0;
        butterfly->unk106 = 0x180;
        butterfly->unk108 = 0.0f;
        for (i = 0; i < 8; i++) {
            butterfly->triangles[i].flags = D_800DCAA8[i].flags;
            butterfly->triangles[i].vi0 = D_800DCAA8[i].vi0;
            butterfly->triangles[i].vi1 = D_800DCAA8[i].vi1;
            butterfly->triangles[i].vi2 = D_800DCAA8[i].vi2;
        }
        uMask = 0;
        for (i = 0; i < 6; i++) {
            butterfly->vertices[uMask].x = D_800DCB28[uMask].x;
            butterfly->vertices[uMask].y = D_800DCB28[uMask].y;
            butterfly->vertices[uMask].z = D_800DCB28[uMask].z;
            butterfly->vertices[uMask].r = 255;
            butterfly->vertices[uMask].g = 255;
            butterfly->vertices[uMask].b = 255;
            butterfly->vertices[uMask].a = 255;
            butterfly->vertices[uMask + 6].x = D_800DCB28[uMask].x;
            butterfly->vertices[uMask + 6].y = D_800DCB28[uMask].y;
            butterfly->vertices[uMask + 6].z = D_800DCB28[uMask].z;
            butterfly->vertices[uMask + 6].r = 255;
            butterfly->vertices[uMask + 6].g = 255;
            butterfly->vertices[uMask + 6].b = 255;
            butterfly->vertices[uMask + 6].a = 255;
            uMask++;
        }
        butterfly->unkFC = 1;
    }
    butterflyObj->segment.trans.scale = butterflyEntry->unkB * 0.01f;
    if (butterflyEntry->unkA < butterflyObj->segment.header->numberOfModelIds) {
        butterfly->texture = (TextureHeader *) butterflyObj->unk68[butterflyEntry->unkA];
    } else {
        butterfly->texture = (TextureHeader *) butterflyObj->unk68[0];
    }
    if (butterfly->texture != NULL) {
        uMask = (butterfly->texture->width - 1) << 5;
        vMask = (butterfly->texture->height - 1) << 5;
    } else {
        uMask = 0;
        vMask = 0;
    }
    for (i = 0; i < 8; i++) {
        butterfly->triangles[i].uv0.u = D_800DCAA8[i].uv0.u & uMask;
        butterfly->triangles[i].uv0.v = D_800DCAA8[i].uv0.v & vMask;
        butterfly->triangles[i].uv1.u = D_800DCAA8[i].uv1.u & uMask;
        butterfly->triangles[i].uv1.v = D_800DCAA8[i].uv1.v & vMask;
        butterfly->triangles[i].uv2.u = D_800DCAA8[i].uv2.u & uMask;
        butterfly->triangles[i].uv2.v = D_800DCAA8[i].uv2.v & vMask;
    }
}

void obj_loop_butterfly(Object *butterflyObj, s32 updateRate) {
    f32 xDiff;
    f32 yDiff;
    f32 zDiff;
    f32 radius;
    f32 sp84;
    f32 var_f0;
    f32 sp7C;
    f32 sp78;
    s16 var_v1;
    s16 shiftAmount;
    s16 sp72;
    s16 temp;
    s32 xPos;
    s32 yPos;
    s32 sp64;
    Object *sp44[8];
    Vertex *vertices;
    Object_Butterfly *butterfly;
    LevelObjectEntry_Butterfly *butterflyEntry;

    butterflyEntry = &butterflyObj->segment.level_entry->butterfly;
    butterfly = &butterflyObj->unk64->butterfly;
    sp64 = butterflyEntry->unkA == 2;
    sp72 = butterfly->unk106;
    if (sp72 < 0) {
        sp72 = -sp72;
    }
    sp7C = 0.1f;
    sp72 *= updateRate;
    if (sp64) {
        sp7C *= 1.6f;
    }
    sp78 = 3.0f;
    if (sp64) {
        sp78 *= 1.6f;
    }
    switch (butterfly->unkFD) {
        case 0:
            butterfly->unk108 = 0.0f;
            sp84 = butterflyEntry->unk8;
            temp = obj_dist_racer(butterflyEntry->common.x, 0.0f, butterflyEntry->common.z, sp84, 1, sp44);
            if (temp > 0) {
                butterfly->unk100 = sp44[0];
                butterfly->unk104 = 0xF0;
                butterfly->unkFD = 3;
            } else {
                butterfly->unk100 =
                    obj_butterfly_node(butterflyEntry->common.x, 0.0f, butterflyEntry->common.z, sp84, 1);
                if (butterfly->unk100 != 0) {
                    butterfly->unk104 = 0xF0;
                    butterfly->unkFD = 3;
                }
            }
            butterflyObj->segment.animFrame = (butterflyObj->segment.animFrame + updateRate) & 0xFF;
            if (sp64) {
                butterflyObj->segment.animFrame = 0x78;
            }
            break;
        case 1:
        case 2:
            if (butterfly->unk106 < 0x480) {
                butterfly->unk106 += (updateRate * 0x10);
                if (butterfly->unk106 >= 0x481) {
                    butterfly->unk106 = 0x480;
                }
            }
            xDiff = butterflyObj->segment.trans.x_position - butterflyEntry->common.x;
            zDiff = butterflyObj->segment.trans.z_position - butterflyEntry->common.z;
            temp = arctan2_f(xDiff, zDiff);
            temp -= butterflyObj->segment.trans.rotation.y_rotation & 0xffff & 0xffff;
            if (temp < 0) {
                if (temp > -sp72) {
                    butterflyObj->segment.trans.rotation.y_rotation += temp;
                } else {
                    butterflyObj->segment.trans.rotation.y_rotation -= sp72;
                }
            } else if ((temp > 0)) {
                if (temp < sp72) {
                    butterflyObj->segment.trans.rotation.y_rotation += temp;
                } else {
                    butterflyObj->segment.trans.rotation.y_rotation += sp72;
                }
            }
            sp84 = butterflyEntry->common.y - butterflyObj->segment.trans.y_position;
            if (sp84 < 0.0f) {
                butterflyObj->segment.y_velocity -= sp7C * updateRate;
                if (butterflyObj->segment.y_velocity < sp84) {
                    butterflyObj->segment.y_velocity = sp84;
                }
            } else if ((sp84 > 0.0f)) {
                butterflyObj->segment.y_velocity += sp7C * updateRate;
                if (sp84 < butterflyObj->segment.y_velocity) {
                    butterflyObj->segment.y_velocity = sp84;
                }
            } else {
                butterflyObj->segment.y_velocity = 0.0f;
            }
            if (butterfly->unkFD == 1) {
                sp84 = butterflyEntry->unk8;
                temp = obj_dist_racer(butterflyEntry->common.x, 0.0f, butterflyEntry->common.z, sp84, 1, sp44);
                if (temp > 0) {
                    butterfly->unk100 = sp44[0];
                    butterfly->unk104 = 0x78;
                    butterfly->unkFD = 3;
                } else {
                    butterfly->unk100 =
                        obj_butterfly_node(butterflyEntry->common.x, 0.0f, butterflyEntry->common.z, sp84, 1);
                    if (butterfly->unk100 != NULL) {
                        butterfly->unk104 = 0xF0;
                        butterfly->unkFD = 3;
                    }
                }
            }
            if (butterfly->unkFD != 3) {
                yDiff = butterflyObj->segment.trans.y_position - butterflyEntry->common.y;
                if (sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff)) < 4.0f) {
                    ignore_bounds_check();
                    move_object(butterflyObj, -xDiff, -yDiff, -zDiff);
                    butterflyObj->segment.y_velocity = 0.0f;
                    butterfly->unkFD = 0;
                    butterfly->unk108 = 0.0f;
                }
            }
            butterflyObj->segment.animFrame = (butterflyObj->segment.animFrame + (updateRate * 0x10)) & 0xFF;
            break;
        case 3:
            if (butterfly->unk106 < 0x480) {
                butterfly->unk106 += (updateRate * 0x10);
                if (butterfly->unk106 >= 0x481) {
                    butterfly->unk106 = 0x480;
                }
            }
            xDiff = butterfly->unk100->segment.trans.x_position - butterflyEntry->common.x;
            zDiff = butterfly->unk100->segment.trans.z_position - butterflyEntry->common.z;
            radius = (butterflyEntry->unk8 * 2);
            radius *= radius;
            if (radius < ((xDiff * xDiff) + (zDiff * zDiff))) {
                butterfly->unk100 = 0;
                sp84 = butterflyEntry->unk8;
                temp = obj_dist_racer(butterflyEntry->common.x, 0.0f, butterflyEntry->common.z, sp84, 1, sp44);
                if (temp > 0) {
                    butterfly->unk100 = sp44[0];
                    butterfly->unk104 = 0xF0;
                } else {
                    butterfly->unk100 =
                        obj_butterfly_node(butterflyEntry->common.x, 0.0f, butterflyEntry->common.z, sp84, 1);
                    if (butterfly->unk100 != 0) {
                        butterfly->unk104 = 0xF0;
                    }
                }
            }
            if (butterfly->unk100 != 0) {
                xDiff = butterflyObj->segment.trans.x_position - butterfly->unk100->segment.trans.x_position;
                zDiff = butterflyObj->segment.trans.z_position - butterfly->unk100->segment.trans.z_position;
                temp = arctan2_f(xDiff, zDiff);
                temp -= butterflyObj->segment.trans.rotation.y_rotation & 0xffff & 0xffff;
                if (temp < 0) {
                    if (-sp72 < temp) {
                        butterflyObj->segment.trans.rotation.y_rotation += temp;
                    } else {
                        butterflyObj->segment.trans.rotation.y_rotation -= sp72;
                    }
                } else if ((temp > 0)) {
                    if (temp < sp72) {
                        butterflyObj->segment.trans.rotation.y_rotation += temp;
                    } else {
                        butterflyObj->segment.trans.rotation.y_rotation += sp72;
                    }
                }
                sp84 = (butterfly->unk100->segment.trans.y_position + 16.0f) - butterflyObj->segment.trans.y_position;
                if (sp84 < 0.0f) {
                    butterflyObj->segment.y_velocity -= sp7C * updateRate;
                    if (butterflyObj->segment.y_velocity < sp84) {
                        butterflyObj->segment.y_velocity = sp84;
                    }
                } else if ((sp84 > 0.0f)) {
                    butterflyObj->segment.y_velocity += sp7C * updateRate;
                    if (sp84 < butterflyObj->segment.y_velocity) {
                        butterflyObj->segment.y_velocity = sp84;
                    }
                }
                if (((xDiff * xDiff) + (zDiff * zDiff)) < 256.0f) {
                    butterfly->unkFD = 4;
                }
            } else {
                butterfly->unkFD = 1;
            }
            butterflyObj->segment.animFrame = (butterflyObj->segment.animFrame + (updateRate * 0x10)) & 0xFF;
            break;
        case 4:
            if (butterfly->unk106 >= 0x181) {
                butterfly->unk106 -= (updateRate * 0x10);
                if (butterfly->unk106 < 0x180) {
                    butterfly->unk106 = 0x180;
                }
            }
            xDiff = butterflyObj->segment.trans.x_position - butterflyEntry->common.x;
            zDiff = butterflyObj->segment.trans.z_position - butterflyEntry->common.z;
            radius = (butterflyEntry->unk8 * 2);
            radius *= radius;
            if (radius < ((xDiff * xDiff) + (zDiff * zDiff))) {
                butterfly->unkFD = 2;
            } else {
                if (updateRate < butterfly->unk104) {
                    butterfly->unk104 -= updateRate;
                } else {
                    butterfly->unk104 = 0;
                    var_v1 = obj_dist_racer(butterflyObj->segment.trans.x_position, 0.0f,
                                            butterflyObj->segment.trans.z_position, 150.0f, 1, sp44);
                    if (var_v1 == 0) {
                        butterfly->unk100 = 0;
                        butterfly->unkFD = 1;
                    } else {
                        if (var_v1 >= 2) {
                            var_v1 = get_random_number_from_range(1, var_v1);
                        }
                        var_v1--;
                        butterfly->unk100 = sp44[var_v1];
                        butterfly->unk104 = 0xF0;
                    }
                }
                if (butterfly->unkFD == 4) {
                    xDiff = butterflyObj->segment.trans.x_position - butterfly->unk100->segment.trans.x_position;
                    zDiff = butterflyObj->segment.trans.z_position - butterfly->unk100->segment.trans.z_position;
                    if (((xDiff * xDiff) + (zDiff * zDiff)) > 22500.0f) {
                        butterfly->unkFD = 3;
                    } else {
                        if (get_random_number_from_range(0, 0x64) >= 0x63) {
                            butterfly->unk106 = -butterfly->unk106;
                        }
                        butterflyObj->segment.trans.rotation.y_rotation += updateRate * butterfly->unk106;
                        if ((butterfly->unk100->segment.trans.y_position + 64.0f) <
                            butterflyObj->segment.trans.y_position) {
                            butterfly->unkFE = 0;
                        } else if (butterflyObj->segment.trans.y_position <
                                   (butterfly->unk100->segment.trans.y_position + 8.0f)) {
                            butterfly->unkFE = 1;
                        }
                        if (butterfly->unkFE != 0) {
                            butterflyObj->segment.y_velocity += (sp7C * updateRate);
                        } else {
                            butterflyObj->segment.y_velocity -= (sp7C * updateRate);
                        }
                        butterflyObj->segment.trans.rotation.y_rotation += butterfly->unk106;
                    }
                }
            }
            butterflyObj->segment.animFrame = (butterflyObj->segment.animFrame + (updateRate * 0x10)) & 0xFF;
            break;
    }
    if (butterfly->unkFD != 0) {
        if (butterfly->unk108 < sp78) {
            butterfly->unk108 += (0.25f * updateRate);
            if (sp78 < butterfly->unk108) {
                butterfly->unk108 = sp78;
            }
        }
    }
    if (butterfly->unk108 != 0.0f) {
        if (butterfly->unkFD != 4) {
            var_f0 = 1.2f;
        } else {
            var_f0 = 1.6f;
        }
        if (sp64) {
            var_f0 *= 1.6f;
        }
        if (butterflyObj->segment.y_velocity < -var_f0) {
            butterflyObj->segment.y_velocity = -var_f0;
        }
        if (var_f0 < butterflyObj->segment.y_velocity) {
            butterflyObj->segment.y_velocity = var_f0;
        }
        if (butterfly->unk108 != 0.0f) {
            butterflyObj->segment.x_velocity =
                sins_f(butterflyObj->segment.trans.rotation.y_rotation) * -butterfly->unk108;
            butterflyObj->segment.z_velocity =
                coss_f(butterflyObj->segment.trans.rotation.y_rotation) * -butterfly->unk108;
            move_object(butterflyObj, butterflyObj->segment.x_velocity, butterflyObj->segment.y_velocity,
                        butterflyObj->segment.z_velocity);
        }
    }
    butterfly->unkFC = 1 - butterfly->unkFC;
    vertices = &butterfly->vertices[butterfly->unkFC * 6];
    var_v1 = sp64 == 0 ? 7 : 8;
    xPos = sins_s16((butterflyObj->segment.animFrame << var_v1)) >> 10;
    yPos = coss_s16((butterflyObj->segment.animFrame << var_v1)) >> 10;
    if (xPos < 0) {
        xPos = -xPos;
    }
    if ((!sp64) && (yPos < 0)) {
        yPos = -yPos;
    }
    vertices[0].x = -xPos;
    vertices[0].y = yPos;
    vertices[1].x = -xPos;
    vertices[1].y = yPos;
    vertices[4].x = xPos;
    vertices[4].y = yPos;
    vertices[5].x = xPos;
    vertices[5].y = yPos;
}

void obj_init_midifade(Object *obj, LevelObjectEntry_MidiFade *entry) {
    Object_64 *obj64;
    s32 pad0;
    ObjectTransform transform;
    f32 ox;
    f32 oy;
    f32 oz;
    s32 pad[10];
    Object_68 *obj68;
    ObjectModel *objModel;
    Vertex *vertices;
    Vertex *vertex;
    f32 mtx[4];
    f32 sinYRot;
    f32 tempF3;
    f32 minX;
    f32 minZ;
    f32 scaleF;
    f32 minY;
    f32 maxX;
    f32 maxZ;
    f32 cosYRot;
    f32 tempF2;
    f32 maxY;
    s32 numOfVertices;
    s32 i;
    f32 scaleF2;

    obj->segment.trans.rotation.y_rotation = entry->angleY << 8 << 2; // Two shifts needed to skip a register.
    obj64 = obj->unk64;
    scaleF = (f32) (((s32) entry->scale) & 0xFFFF);
    if (scaleF < 1.0f) {
        scaleF = 1.0f;
    }
    scaleF /= 8;
    obj->segment.trans.scale = obj->segment.header->scale * (scaleF);
    transform.rotation.y_rotation = obj->segment.trans.rotation.y_rotation;
    transform.rotation.x_rotation = obj->segment.trans.rotation.x_rotation;
    transform.rotation.z_rotation = obj->segment.trans.rotation.z_rotation;
    transform.scale = 1.0f;
    transform.x_position = 0.0f;
    transform.y_position = 0.0f;
    transform.z_position = 0.0f;
    object_transform_to_matrix(mtx, &transform);
    guMtxXFMF(mtx, 0.0f, 0.0f, 1.0f, &ox, &oy, &oz);
    obj64->midi_fade.unk8 = ox;
    obj64->midi_fade.unkC = oy;
    obj64->midi_fade.unk10 = oz;
    obj64->midi_fade.unk14 = -((obj->segment.trans.x_position * ox) + (obj->segment.trans.y_position * oy) +
                               (obj->segment.trans.z_position * oz));
    obj64->midi_fade.unk2 = entry->unk1A;
    obj64->midi_fade.unk40 = entry->unk1B;

    for (i = 0; i < 15; i++) {
        obj64->midi_fade.unk2F[i] = entry->unkA[i];
    }

    obj68 = *obj->unk68;
    objModel = obj68->objModel;
    vertex = &objModel->vertices[1];
    maxX = vertex->x;
    maxY = vertex->y;
    maxZ = vertex->z;
    minX = maxX;
    minY = maxY;
    minZ = maxZ;
    for (i = 1; i < objModel->numberOfVertices; i++) {
        vertex = &objModel->vertices[i];
        if (vertex->x < minX) {
            minX = vertex->x;
        }
        if (maxX < vertex->x) {
            maxX = vertex->x;
        }
        if (vertex->y < minY) {
            minY = vertex->y;
        }
        if (maxY < vertex->y) {
            maxY = vertex->y;
        }
        if (vertex->z < minZ) {
            minZ = vertex->z;
        }
        if (maxZ < vertex->z) {
            maxZ = vertex->z;
        }
    }
    cosYRot = coss_f(obj->segment.trans.rotation.y_rotation);
    sinYRot = sins_f(obj->segment.trans.rotation.y_rotation);
    tempF3 = minX;
    minX = (minX * cosYRot) + (minZ * sinYRot);
    minZ = (minZ * cosYRot) - (tempF3 * sinYRot);
    tempF3 = maxX;
    maxX = (maxX * cosYRot) + (maxZ * sinYRot);
    maxZ = (maxZ * cosYRot) - (tempF3 * sinYRot);
    if (maxX < minX) {
        tempF2 = maxX;
        maxX = minX;
        minX = tempF2;
    }
    if (maxZ < minZ) {
        tempF2 = maxZ;
        maxZ = minZ;
        minZ = tempF2;
    }
    obj64->midi_fade.unk18 = (obj->segment.trans.scale * minX) + obj->segment.trans.x_position;
    obj64->midi_fade.unk1C = (obj->segment.trans.scale * minY) + obj->segment.trans.y_position;
    obj64->midi_fade.unk20 = (obj->segment.trans.scale * minZ) + obj->segment.trans.z_position;
    obj64->midi_fade.unk24 = (obj->segment.trans.scale * maxX) + obj->segment.trans.x_position;
    obj64->midi_fade.unk28 = (obj->segment.trans.scale * maxY) + obj->segment.trans.y_position;
    obj64->midi_fade.unk2C = (obj->segment.trans.scale * maxZ) + obj->segment.trans.z_position;
    obj64->midi_fade.unk1 = 0;
}

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
    obj->segment.trans.rotation.z_rotation = 0;
    obj->segment.trans.rotation.x_rotation = 0;
    obj->segment.trans.rotation.y_rotation = 0;

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
    func_800AF134((Particle *) obj->particleEmitter, entry->particleBehaviourID, entry->particlePropertyID, 0, 0, 0);
    obj->properties.common.unk0 = entry->particleDensity;
}

/**
 * Bubbler Boss loop func.
 * All the racer side is handled elsewhere.
 * This rolls a random number and starts emitting particles based on that for variable density.
 */
void obj_loop_bubbler(Object *obj, s32 updateRate) {
    if (obj->properties.common.unk0 >= get_random_number_from_range(0, 1024)) {
        obj->particleEmitFlags = OBJ_EMIT_PARTICLE_1;
    } else {
        obj->particleEmitFlags = OBJ_EMIT_OFF;
    }
    if (get_number_of_active_players() < 2) {
        obj_spawn_particle(obj, updateRate);
    }
}

void obj_init_boost(Object *obj, LevelObjectEntry_Boost2 *entry) {
    obj->unk64 = (Object_64 *) ((s32) get_misc_asset(ASSET_MISC_20) + (entry->unk8[0] << 7));
    obj->segment.level_entry = NULL;
}

void obj_init_unknown94(UNUSED Object *obj, UNUSED LevelObjectEntry_Unknown94 *entry, UNUSED s32 arg2) {
}

void obj_loop_unknown94(UNUSED Object *obj, s32 UNUSED updateRate) {
}

/**
 * Particle Emitter init func.
 * Does nothing.
 */
void obj_init_rangetrigger(UNUSED Object *obj, UNUSED LevelObjectEntry_RangeTrigger *entry) {
}

/**
 * Particle Emitter loop func.
 * Emits particles set by the spawn parameters when any races are in range.
 * Official name: rangetriggerControl
 */
void obj_loop_rangetrigger(Object *obj, s32 updateRate) {
    UNUSED s32 pad;
    LevelObjectEntry_RangeTrigger *entry;
    Object *objs[8];

    entry = &obj->segment.level_entry->rangeTrigger;
    if (obj_dist_racer(obj->segment.trans.x_position, 0, obj->segment.trans.z_position, entry->radius, 1, objs) > 0) {
        obj->particleEmitFlags = entry->particleFlags;
    } else {
        obj->particleEmitFlags = OBJ_EMIT_OFF;
    }
    obj_spawn_particle(obj, updateRate);
}

/**
 * Overworld Frog init func.
 * Sets the home position to where it is currently.
 * Checks if this frog is supposed to be drumstick.
 * If so, delete if Drumstick is either unlocked, or all trophy races are not yet complete.
 */
void obj_init_frog(Object *obj, LevelObjectEntry_Frog *entry) {
    Object_Frog *frog;

    frog = &obj->unk64->frog;
    frog->drumstick = entry->drumstick;
    frog->homeX = obj->segment.trans.x_position;
    frog->homeY = obj->segment.trans.y_position;
    frog->homeZ = obj->segment.trans.z_position;
    frog->homeRadius = entry->homeRadius;
    frog->homeRadiusSquare = frog->homeRadius * frog->homeRadius;
    frog->action = FROG_IDLE;
    frog->hopStartX = obj->segment.trans.x_position;
    frog->hopStartZ = obj->segment.trans.z_position;
    frog->squishCooldown = 0;
    frog->scaleY = 1.0f;

    if (frog->drumstick) {
        obj->segment.object.modelIndex = 1;
        /**
         * Don't spawn the chicken frog if drumstick is already unlocked, or
         * if the player hasn't completed the trophy races yet.
         */
        if (is_drumstick_unlocked() || (get_settings()->trophies & 0xFF) != 0xFF) {
            free_object(obj);
        }
    } else {
        obj->segment.object.modelIndex = 0;
    }
}

/**
 * Overworld frog loop function.
 * Hops, skips, jumps around. Can be flattened by players.
 * If a Drumstick frog exists after beating all 4 trophy races, he can be squashed and will be unlocked as a playable
 * character.
 */
void obj_loop_frog(Object *obj, s32 updateRate) {
    Object_Frog *frog;
    s32 i;
    s32 hopping;
    s32 var_v1;
    UNUSED s32 pad0[29]; // Wtf is this large gap here?
    f32 colY[8];
    UNUSED s32 pad2[4];
    f32 cosine;
    f32 diffX;
    f32 diffY;
    f32 diffZ;
    f32 updateRateF;
    Object *racerObj;

    updateRateF = updateRate;
    if (osTvType == OS_TV_TYPE_PAL) {
        updateRateF *= 1.2;
    }
    frog = (Object_Frog *) obj->unk64;

    switch (frog->action) {
        case FROG_IDLE:
            hopping = FALSE;
            if (frog->squishCooldown > 0) {
                frog->squishCooldown -= updateRate;
            }
            if (obj_dist_racer(obj->segment.trans.x_position, obj->segment.trans.y_position,
                               obj->segment.trans.z_position, 96.0f, 1, &racerObj) > 0) {
                diffX = obj->segment.trans.x_position - racerObj->segment.trans.x_position;
                diffY = obj->segment.trans.y_position - racerObj->segment.trans.y_position;
                diffZ = obj->segment.trans.z_position - racerObj->segment.trans.z_position;
                if (frog->squishCooldown <= 0 && (diffX * diffX) + (diffY * diffY) + (diffZ * diffZ) < 40.0f * 40.0f) {
                    if (frog->drumstick) {
                        play_sound_at_position(SOUND_VOICE_DRUMSTICK_POSITIVE2, obj->segment.trans.x_position,
                                               obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
                        set_eeprom_settings_value(2);
                        set_magic_code_flags(CHEAT_CONTROL_DRUMSTICK);
                        set_drumstick_unlock_transition();
                        free_object(obj);
                        break;
                    } else {
                        frog->action = FROG_SQUISH;
                        play_sound_at_position(SOUND_SPLAT, obj->segment.trans.x_position,
                                               obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
                    }
                } else {
                    frog->forwardVel = 72.0f;
                    if (frog->drumstick) {
                        frog->forwardVel *= 1.34f;
                    }
                    frog->hopDirection = arctan2_f(-diffX, -diffZ) + 0x8000;
                    hopping = TRUE;
                }
            } else {
                frog->hopTimer -= updateRate;
                if (frog->hopTimer < 0) {
                    hopping = TRUE;
                    frog->forwardVel = get_random_number_from_range(40, 72);
                    frog->hopDirection =
                        get_random_number_from_range(-0x4000, 0x4000) + obj->segment.trans.rotation.y_rotation;
                }
            }
            if (hopping) {
                for (i = 0, var_v1 = FALSE; i < 4 && var_v1 == FALSE; i++) {
                    frog->hopTargetX = sins_f(frog->hopDirection) * frog->forwardVel;
                    frog->hopTargetZ = coss_f(frog->hopDirection) * -frog->forwardVel;
                    diffX = (obj->segment.trans.x_position + frog->hopTargetX) - frog->homeX;
                    diffZ = (obj->segment.trans.z_position + frog->hopTargetZ) - frog->homeZ;
                    if ((diffX * diffX) + (diffZ * diffZ) < frog->homeRadiusSquare) {
                        var_v1 = TRUE;
                    } else {
                        frog->hopDirection += 0x4000;
                    }
                }
                if (var_v1 == FALSE) {
                    diffX = frog->homeX - obj->segment.trans.x_position;
                    diffZ = frog->homeZ - obj->segment.trans.z_position;
                    frog->hopDirection = arctan2_f(diffX, diffZ);
                }
                if (frog->drumstick) {
                    play_sound_at_position(SOUND_VOICE_DRUMSTICK_POSITIVE6, obj->segment.trans.x_position,
                                           obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
                } else {
                    play_sound_at_position(SOUND_RIBBIT, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                           obj->segment.trans.z_position, 4, NULL);
                }
                frog->action = FROG_HOP;
                frog->hopStartX = obj->segment.trans.x_position;
                frog->hopStartZ = obj->segment.trans.z_position;
                frog->hopFrame = 32;
                obj->segment.trans.rotation.y_rotation = -frog->hopDirection;
            }
        default:
            break;
        case FROG_HOP:
            frog->hopFrame -= updateRate;
            if (frog->squishCooldown > 0) {
                frog->squishCooldown -= updateRate;
            }
            if (frog->hopFrame < 0) {
                frog->action = FROG_IDLE;
                frog->hopTimer = get_random_number_from_range(0, 300);
                frog->hopFrame = 0;
            }
            obj->segment.animFrame = ((32 - frog->hopFrame) << 3) / 3;
            cosine = (coss_f(frog->hopFrame << 10) + 1.0f) * 0.5f;
            obj->segment.trans.x_position = frog->hopStartX;
            obj->segment.trans.z_position = frog->hopStartZ;
            obj->segment.x_velocity = frog->hopTargetX * cosine;
            obj->segment.z_velocity = frog->hopTargetZ * cosine;
            ignore_bounds_check();
            move_object(obj, obj->segment.x_velocity, 0.0f, obj->segment.z_velocity);
            if (func_8002BAB0(obj->segment.object.segmentID, obj->segment.trans.x_position,
                              obj->segment.trans.z_position, colY) != 0) {
                obj->segment.trans.y_position = 0.0f;
                ignore_bounds_check();
                move_object(obj, 0.0f, (f32) colY[0], 0.0f);
            }
            if (frog->squishCooldown <= 0 && (frog->hopFrame < 6 || frog->hopFrame >= 27)) {
                if (obj_dist_racer(obj->segment.trans.x_position, obj->segment.trans.y_position,
                                   obj->segment.trans.z_position, 40.0f, 0, &racerObj)) {
                    if (frog->drumstick) {
                        play_sound_at_position(SOUND_VOICE_DRUMSTICK_POSITIVE2, obj->segment.trans.x_position,
                                               obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
                        set_eeprom_settings_value(2);
                        set_magic_code_flags(CHEAT_CONTROL_DRUMSTICK);
                        set_drumstick_unlock_transition();
                        free_object(obj);
                    } else {
                        frog->action = FROG_SQUISH;
                        play_sound_at_position(SOUND_SPLAT, obj->segment.trans.x_position,
                                               obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
                    }
                }
            }
            break;
        case FROG_SQUISH:
            frog->scaleY -= 0.15f * updateRateF;
            if (frog->scaleY < 0.05f) {
                frog->scaleY = 0.05f;
                frog->action = FROG_FLAT;
                frog->hopTimer = 40;
            }
            break;
        case FROG_FLAT:
            frog->hopTimer -= updateRate;
            if (frog->hopTimer < 0) {
                frog->action = FROG_UNSQUISH;
                play_sound_at_position(SOUND_PLOP2, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                       obj->segment.trans.z_position, 4, NULL);
            }
            break;
        case FROG_UNSQUISH:
            if (frog->scaleY > 1.0f) {
                frog->scaleY = 1.0f;
                frog->action = FROG_IDLE;
                frog->hopTimer = 0;
                frog->squishCooldown = 60;
            } else {
                frog->scaleY += 0.15f * updateRateF;
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
        someObj->properties.common.unk0 = 0;
        if (obj64 != 0) {
            obj64->unk72 += updateRate;
            obj64->unk70 = 2;
            obj64->unk74 = 1.0f;
            func_8000B750(obj, -1, 2, 1, 1);
        }
    }
}

/**
 * Overworld level name init behaviour.
 * Sets level name and radius based off spawn info.
 */
void obj_init_levelname(Object *obj, LevelObjectEntry_LevelName *entry) {
    obj->properties.levelName.radius = entry->radius * 8.0f;
    obj->properties.levelName.radius *= obj->properties.levelName.radius;
    obj->properties.levelName.levelID = entry->levelID;
    obj->properties.levelName.opacity = 0;
    if (is_in_tracks_mode()) {
        free_object(obj);
    }
    clear_dialogue_box_open_flag(4);
}

/**
 * Overworld level name loop behaviour.
 * Placed at a level entrance, when a player gets near, display the level name on screen.
 */
void obj_loop_levelname(Object *obj, s32 updateRate) {
    s32 textWidth;
    s32 x1;
    s32 y1;
    s32 x2;
    s32 y2;
    UNUSED s32 pad[5];
    char *levelName;
    Object *racerObj;
    f32 diffX;
    f32 diffZ;
    ObjPropertyName *properties;

    racerObj = get_racer_object_by_port(PLAYER_ONE);
    if (racerObj != NULL) {
        diffX = obj->segment.trans.x_position - racerObj->segment.trans.x_position;
        diffZ = obj->segment.trans.z_position - racerObj->segment.trans.z_position;
        properties = &obj->properties.levelName;
        if ((diffX * diffX) + (diffZ * diffZ) < properties->radius) {
            properties->opacity += updateRate * 16;
            if (properties->opacity > 256) {
                properties->opacity = 256;
            }
        } else {
            properties->opacity -= updateRate * 16;
            if (properties->opacity < 0) {
                properties->opacity = 0;
            }
        }
        if (properties->opacity > 0) {
            levelName = get_level_name(properties->levelID);
            textWidth = (get_text_width(levelName, 0, 0) + 24) >> 1;
            x1 = SCREEN_WIDTH_HALF - textWidth;
            x2 = textWidth + SCREEN_WIDTH_HALF;
            if (osTvType == OS_TV_TYPE_PAL) {
                y1 = SCREEN_HEIGHT - 16;
                y2 = SCREEN_HEIGHT - 16 + 24;
            } else {
                y1 = SCREEN_HEIGHT - 38;
                y2 = SCREEN_HEIGHT - 38 + 20;
            }
            dialogue_clear(4);
            set_current_dialogue_box_coords(4, x1, y1, x2, y2);
            set_current_dialogue_background_colour(4, 128, 64, 128, (properties->opacity * 160) >> 8);
            set_current_text_background_colour(4, 0, 0, 0, 0);
#if REGION == REGION_JP
            set_dialogue_font(4, FONT_SMALL);
            set_current_text_colour(4, 255, 255, 64, 255, (properties->opacity * 255) >> 8);
            render_dialogue_text(4, (x2 - x1) >> 1, ((y2 - y1) >> 1), levelName, 1, ALIGN_MIDDLE_CENTER);
#else
            set_dialogue_font(4, FONT_COLOURFUL);
            set_current_text_colour(4, 255, 255, 255, 0, (properties->opacity * 255) >> 8);
            render_dialogue_text(4, (x2 - x1) >> 1, ((y2 - y1) >> 1) + 2, levelName, 1, ALIGN_MIDDLE_CENTER);
#endif
            open_dialogue_box(4);
        }
    }
}

void obj_loop_wizghosts(Object *obj, s32 updateRate) {
    func_8001F460(obj, updateRate, obj);
    obj->segment.animFrame = (obj->segment.animFrame + (updateRate * 8)) & 0xFF;
}
