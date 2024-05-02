#ifndef _OBJECT_PROPERTIES_H_
#define _OBJECT_PROPERTIES_H_

#include "types.h"
#include "enums.h"
#include "level_object_entries.h"

/**
 * Objects have a union at offset 0x78, that's 8 bytes large. 
 * Here's a collection of unions to help improve readability for them.
*/

typedef struct ObjPropertyCommon {
    s32 unk0;
    s32 unk4;
} ObjPropertyCommon;

typedef struct ObjPropertyDistance {
    f32 radius;
    s32 unk4;
} ObjPropertyDistance;

typedef struct ObjPropertySpeed {
    s32 speed;
    s32 unk4;
} ObjPropertySpeed;

typedef struct ObjPropertyBanana {
    s32 status;
    s16 intangibleTimer;
    s16 destroyTimer;
} ObjPropertyBanana;

typedef struct ObjPropertyName {
    f32 radius;
    s16 levelID;
    s16 opacity;
} ObjPropertyName;

typedef struct ObjPropertyProjectile {
    s32 timer;
    s32 unk4;
} ObjPropertyProjectile;

typedef struct ObjPropertyLog {
    s32 angleVel;
    s32 velocityY;
} ObjPropertyLog;

typedef struct ObjPropertyScenery {
	struct Object *interactObj;
	s16 hitTimer;
	s16 angleVel;
} ObjPropertyScenery;

typedef struct ObjPropertyFireball {
	struct Object *obj;
	s32 timer;
} ObjPropertyFireball;

typedef struct ObjPropertyLasergun {
	s32 timer;
	struct Object_LaserGun *obj;
} ObjPropertyLasergun;

typedef struct ObjPropertyTrophyCabinet {
	s32 action;
	s32 trophy;
} ObjPropertyTrophyCabinet;

typedef struct ObjPropertyEggSpawner {
	struct Object *egg;
} ObjPropertyEggSpawner;

typedef struct ObjPropertyZipper {
	s32 radius;
} ObjPropertyZipper;

typedef struct ObjPropertyCharacterFlag {
	s32 playerID;
	s32 characterID;
} ObjPropertyCharacterFlag;

typedef struct ObjPropertyNPC {
	s32 action;
	s32 timer;
} ObjPropertyNPC;

typedef struct ObjPropertyLavaSpurt {
	s32 actionTimer;
	s32 delayTimer;
} ObjPropertyLavaSpurt;

typedef struct ObjPropertyAnimation {
	s32 action;
	s32 behaviourID;
} ObjPropertyAnimation;

typedef struct ObjPropertyInfoPoint {
	s32 radius;
	s32 visible;
} ObjPropertyInfoPoint;

typedef struct ObjPropertyBombExplosion {
	s32 timer;
	s32 unk4;
} ObjPropertyBombExplosion;

typedef struct ObjPropertyLighthouse {
	s32 active;
} ObjPropertyLighthouse;

typedef struct ObjPropertyDoor {
	s32 closeAngle;
	s32 openAngle;
} ObjPropertyDoor;

typedef struct ObjPropertySkyControl {
	s32 setting;
	s32 radius;
} ObjPropertySkyControl;

typedef struct ObjPropertyTreasureSucker {
	s32 playerID;
	s32 spawnTimer;
} ObjPropertyTreasureSucker;

typedef struct ObjPropertyTreasureBanana {
	s32 diff;
	struct Object_Racer *racer;
} ObjPropertyTreasureBanana;

typedef struct ObjPropertyBananaSpawner {
	s32 timer;
	s32 spawn;
} ObjPropertyBananaSpawner;

typedef struct ObjPropertyWorldKey {
	s32 keyID;
} ObjPropertyWorldKey;

typedef struct ObjPropertyWeaponBalloon {
	s32 balloonID;
    s32 particleTimer;
} ObjPropertyWeaponBalloon;

typedef struct ObjPropertyRacer {
	struct Object *unk0;
    s32 unk4;
} ObjPropertyRacer;

typedef struct ObjPropertySetupPoint {
    s32 racerIndex; 
    s32 entranceID; 
} ObjPropertySetupPoint;

typedef struct ObjPropertyWeapon {
    s32 decayTimer;
    u8 status;
    u8 submerged;
    s16 scale;
} ObjPropertyWeapon;

typedef struct ObjPropertyCamControl {
    s32 cameraID; 
} ObjPropertyCamControl;

typedef struct ObjPropertyTimeTrial {
    s32 timestamp; 
    struct ObjectHeader *header; 
} ObjPropertyTimeTrial;

typedef struct ObjProperties {
    union {
        ObjPropertyCommon common;
        ObjPropertyDistance distance;
        ObjPropertySpeed speed;
        ObjPropertyBanana banana;
        ObjPropertyName levelName;
        ObjPropertyProjectile projectile;
        ObjPropertyLog log;
        ObjPropertyScenery scenery;
        ObjPropertyFireball fireball;
        ObjPropertyLasergun lasergun;
        ObjPropertyTrophyCabinet trophyCabinet;
        ObjPropertyEggSpawner eggSpawner;
        ObjPropertyZipper zipper;
        ObjPropertyCharacterFlag characterFlag;
        ObjPropertyNPC npc;
        ObjPropertyLavaSpurt lavaSpurt;
        ObjPropertyAnimation animatedObj;
        ObjPropertyInfoPoint infoPoint;
        ObjPropertyBombExplosion bombExplosion;
        ObjPropertyLighthouse lighthouse;
        ObjPropertyDoor door;
        ObjPropertySkyControl skyControl;
        ObjPropertyTreasureSucker treasureSucker;
        ObjPropertyTreasureBanana treasureBanana;
        ObjPropertyBananaSpawner bananaSpawner;
        ObjPropertyWorldKey worldKey;
        ObjPropertyWeaponBalloon weaponBalloon;
        ObjPropertyRacer racer;
        ObjPropertySetupPoint setupPoint;
        ObjPropertyWeapon weapon;
        ObjPropertyCamControl camControl;
        ObjPropertyTimeTrial timeTrial;
    };
} ObjProperties;

#endif
