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

typedef struct ObjPropertyTorchMist {
    s32 speed;
} ObjPropertyTorchMist;

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

typedef struct ObjPropertyWizPigShip {
    s32 unk0;
    s32 timer;
} ObjPropertyWizPigShip;

typedef struct ObjPropertyLaserbolt {
    s32 timer;
    struct Object_LaserGun *obj;
} ObjPropertyLaserbolt;

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

typedef struct ObjPropertyGoldenBalloon {
    s32 action;
    s32 timer;
} ObjPropertyGoldenBalloon;

typedef struct ObjPropertySilverCoin {
    s32 action;
    s32 timer;
} ObjPropertySilverCoin;

typedef struct ObjPropertyTT {
    s32 action;
    s32 timer;
} ObjPropertyTT;

typedef struct ObjPropertyTaj {
    s32 action;
    s32 timer;
} ObjPropertyTaj;

typedef struct ObjPropertyLavaSpurt {
    s32 actionTimer;
    s32 delayTimer;
} ObjPropertyLavaSpurt;

typedef struct ObjPropertyPosArrow {
    s32 playerID;
} ObjPropertyPosArrow;

typedef struct ObjPropertyAnimation {
    s32 action;
    s32 behaviourID;
} ObjPropertyAnimation;

typedef struct ObjPropertyAnimatedObject {
    s32 unk0;
    s32 unk4;
} ObjPropertyAnimatedObject;

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

typedef struct ObjPropertyBridgeWhaleRamp {
    s32 unk0;
} ObjPropertyBridgeWhaleRamp;

typedef struct ObjPropertyRampSwitch {
    s32 unk0;
} ObjPropertyRampSwitch;

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

typedef struct ObjPropertyFlyCoin {
    s32 diff;
    struct Object_Racer *racer;
} ObjPropertyFlyCoin;

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
    u32 entranceID;
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

typedef struct ObjPropertyDinoWhale {
    s32 unk0;
} ObjPropertyDinoWhale;

typedef struct ObjPropertyBubbler {
    s32 unk0;
} ObjPropertyBubbler;

typedef struct ObjPropertyBoost {
    struct Object *obj;
    union {
        s32 indexes; // Keep this for compatibility
        // This is a bitfield definition for the bits in indexes.
        // It won't match when used, but it's useful for understanding the structure.
        struct {
            s32 racerIndex : 4; // bits 28-31  ((indexes >> 28) & 0xF)
            s32 vertIndex : 14; // bits 14-27  ((indexes >> 14) & 0x3FFF)
            s32 trisIndex : 14; // bits 0-13   (indexes & 0x3FFF)
        };
    };
} ObjPropertyBoost;

typedef struct ObjProperties {
    union {
        ObjPropertyCommon common;
        ObjPropertyDistance distance;               // BHV_FOG_CHANGER, BHV_WEATHER
        ObjPropertyTorchMist torchMist;             // BHV_TORCH_MIST
        ObjPropertyBanana banana;                   // BHV_BANANA
        ObjPropertyName levelName;                  // BHV_LEVEL_NAME
        ObjPropertyProjectile projectile;           // BHV_WEAPON_2
        ObjPropertyLog log;                         // BHV_LOG
        ObjPropertyScenery scenery;                 // BHV_SCENERY
        ObjPropertyFireball fireball;               // BHV_FIREBALL_OCTOWEAPON, BHV_FIREBALL_OCTOWEAPON_2
        ObjPropertyLaserbolt laserbolt;             // BHV_LASER_BOLT
        ObjPropertyTrophyCabinet trophyCabinet;     // BHV_TROPHY_CABINET
        ObjPropertyEggSpawner eggSpawner;           // BHV_EGG_CREATOR
        ObjPropertyZipper zipper;                   // BHV_ZIPPER_GROUND
        ObjPropertyCharacterFlag characterFlag;     // BHV_CHARACTER_FLAG
        ObjPropertyGoldenBalloon goldenBalloon;     // BHV_GOLDEN_BALLOON
        ObjPropertySilverCoin silverCoin;           // BHV_SILVER_COIN_2, BHV_SILVER_COIN
        ObjPropertyTT tt;                           // BHV_STOPWATCH_MAN
        ObjPropertyTaj taj;                         // BHV_PARK_WARDEN
        ObjPropertyLavaSpurt lavaSpurt;             // BHV_LAVA_SPURT
        ObjPropertyPosArrow posArrow;               // BHV_POS_ARROW
        ObjPropertyAnimation animation;             // BHV_ANIMATION
        ObjPropertyWizPigShip wizpigship;           // BHV_WIZPIG_SHIP
        ObjPropertyAnimatedObject animatedObj;      // BHV_DINO_WHALE, BHV_ANIMATED_OBJECT, BHV_CAMERA_ANIMATION
                                                    // BHV_CAR_ANIMATION, BHV_CHARACTER_SELECT, BHV_VEHICLE_ANIMATION
                                                    // BHV_HIT_TESTER, BHV_HIT_TESTER_2, BHV_PARK_WARDEN_2
                                                    // BHV_ANIMATED_OBJECT_2, BHV_WIZPIG_SHIP, BHV_ANIMATED_OBJECT_3
                                                    // BHV_ANIMATED_OBJECT_4, BHV_SNOWBALL, BHV_SNOWBALL_2
                                                    // BHV_SNOWBALL_3, BHV_SNOWBALL_4, BHV_HIT_TESTER_3
                                                    // BHV_HIT_TESTER_4, BHV_DOOR_OPENER, BHV_PIG_ROCKETEER
                                                    // BHV_WIZPIG_GHOSTS
        ObjPropertyInfoPoint infoPoint;             // BHV_INFO_POINT
        ObjPropertyBombExplosion bombExplosion;     // BHV_BOMB_EXPLOSION
        ObjPropertyLighthouse lighthouse;           // BHV_TELEPORT
        ObjPropertyDoor door;                       // BHV_DOOR, BHV_TT_DOOR
        ObjPropertyBridgeWhaleRamp bridgeWhaleRamp; // BHV_BRIDGE_WHALE_RAMP
        ObjPropertyRampSwitch rampSwitch;           // BHV_RAMP_SWITCH
        ObjPropertySkyControl skyControl;           // BHV_SKY_CONTROL
        ObjPropertyTreasureSucker treasureSucker;   // BHV_TREASURE_SUCKER
        ObjPropertyFlyCoin flyCoin;                 // BHV_FLY_COIN
        ObjPropertyBananaSpawner bananaSpawner;     // BHV_BANANA_SPAWNER
        ObjPropertyWorldKey worldKey;               // BHV_WORLD_KEY
        ObjPropertyWeaponBalloon weaponBalloon;     // BHV_WEAPON_BALLOON
        ObjPropertySetupPoint setupPoint;           // BHV_SETUP_POINT
        ObjPropertyWeapon weapon;                   // BHV_WEAPON
        ObjPropertyCamControl camControl;           // BHV_CAMERA_CONTROL
        ObjPropertyTimeTrial timeTrial;             // BHV_TIMETRIAL_GHOST
        ObjPropertyDinoWhale dinoWhale;             // BHV_DINO_WHALE
        ObjPropertyBubbler bubbler;                 // BHV_BUBBLER
        ObjPropertyBoost boost;
    };
} ObjProperties;

#endif
