#ifndef _LEVEL_OBJECT_ENTRIES_H_
#define _LEVEL_OBJECT_ENTRIES_H_

    /* Size: 8 bytes. Shared across every entry. */
typedef struct LevelObjectEntryCommon {
    u8 objectID; // 9-bit object ID to load (uses size's MSB).
    u8 size; // 7-bit total entry length (MSB is used in object_id).
    s16 x, y, z; // Position in level
} LevelObjectEntryCommon;

typedef struct LevelObjectEntry_Racer {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Racer;

typedef struct LevelObjectEntry_Scenery {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
} LevelObjectEntry_Scenery;

typedef struct LevelObjectEntry_Fish {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Fish;

typedef struct LevelObjectEntry_Animator {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s8 unk8;
    /* 0x09 */ s8 unk9;
    /* 0x0A */ s8 unkA;
} LevelObjectEntry_Animator;

typedef struct LevelObjectEntry_Weapon {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Weapon;

typedef struct LevelObjectEntry_Smoke {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Smoke;

typedef struct LevelObjectEntry_Exit {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 pad8[8];
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 pad12[6];
    /* 0x18 */ s8 unk18;
} LevelObjectEntry_Exit;

typedef struct LevelObjectEntry_Audio {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
    /* 0x10 */ u8 unk10;
} LevelObjectEntry_Audio;

typedef struct LevelObjectEntry_AudioLine {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u16 unkE;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
} LevelObjectEntry_AudioLine;

typedef struct LevelObjectEntry_CameraControl {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s8 unk8;
} LevelObjectEntry_CameraControl;

typedef struct LevelObjectEntry_SetupPoint {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
} LevelObjectEntry_SetupPoint;

typedef struct LevelObjectEntry_Dino_Whale {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Dino_Whale;

typedef struct LevelObjectEntry_Checkpoint {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
} LevelObjectEntry_Checkpoint;

typedef struct LevelObjectEntry_Door {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 closedRotation;
    /* 0x09 */ u8 openRotation;
    /* 0x0A */ u8 modelIndex;
    /* 0x0B */ u8 distanceToOpen;
    /* 0x0C */ s8 unkC;
    /* 0x0D */ u8 numBalloonsToOpen;
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ s8 unk11;
    /* 0x12 */ u8 scale;
} LevelObjectEntry_Door;

typedef struct LevelObjectEntry_FogChanger {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
} LevelObjectEntry_FogChanger;

typedef struct LevelObjectEntry_AiNode {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
} LevelObjectEntry_AiNode;

#define BALLOON_TYPE_BOOST   0
#define BALLOON_TYPE_MISSILE 1
#define BALLOON_TYPE_TRAP    2
#define BALLOON_TYPE_SHIELD  3
#define BALLOON_TYPE_MAGNET  4

typedef struct LevelObjectEntry_WeaponBalloon {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8; // Unused?
    /* 0x09 */ u8 balloonType; 
    /* 0x0A */ u8 scale; // This is divided by 64 to get actual scale.
} LevelObjectEntry_WeaponBalloon;

typedef struct LevelObjectEntry_AudioSeqLine {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_AudioSeqLine;

typedef struct LevelObjectEntry_BombExplosion {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s8 unk8;
} LevelObjectEntry_BombExplosion;

typedef struct LevelObjectEntry_WBalloonPop {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_WBalloonPop;

typedef struct LevelObjectEntry_Unknown25 {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown25;

typedef struct LevelObjectEntry_SkyControl {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
} LevelObjectEntry_SkyControl;

typedef struct LevelObjectEntry_AudioReverb {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
} LevelObjectEntry_AudioReverb;

typedef struct LevelObjectEntry_Torch_Mist {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
} LevelObjectEntry_Torch_Mist;

typedef struct LevelObjectEntry_TexScroll {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s8 unkA;
    /* 0x0B */ s8 unkB;
} LevelObjectEntry_TexScroll;

typedef struct LevelObjectEntry_ModeChange {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
} LevelObjectEntry_ModeChange;

typedef struct LevelObjectEntry_StopWatchMan {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_StopWatchMan;

typedef struct LevelObjectEntry_Banana {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Banana;

typedef struct LevelObjectEntry_RgbaLight {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_RgbaLight;

typedef struct LevelObjectEntry_Buoy_PirateShip {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Buoy_PirateShip;

typedef struct LevelObjectEntry_Weather {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s16 unk8;
} LevelObjectEntry_Weather;

typedef struct LevelObjectEntry_Bridge_WhaleRamp {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
} LevelObjectEntry_Bridge_WhaleRamp;

typedef struct LevelObjectEntry_RampSwitch {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
} LevelObjectEntry_RampSwitch;

typedef struct LevelObjectEntry_SeaMonster {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_SeaMonster;

typedef struct LevelObjectEntry_Bonus {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
} LevelObjectEntry_Bonus;

typedef struct LevelObjectEntry_LensFlare {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_LensFlare;

typedef struct LevelObjectEntry_LensFlareSwitch {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s16 unk8;
} LevelObjectEntry_LensFlareSwitch;

typedef struct LevelObjectEntry_CollectEgg {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_CollectEgg;

typedef struct LevelObjectEntry_EggCreator {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_EggCreator;

typedef struct LevelObjectEntry_CharacterFlag {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s16 unk8;    
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
} LevelObjectEntry_CharacterFlag;

/*
 * Note: the member names are just my best guesses. 
 * Take them with a grain of salt.
 */
typedef struct LevelObjectEntry_Animation {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 z_rotation;
    /* 0x09 */ u8 x_rotation;
    /* 0x0A */ u8 y_rotation;
    /* 0x0B */ u8 scale;
    /* 0x0C */ s16 objectIdToSpawn;
    /* 0x0E */ s16 animationStartDelay;
    /* 0x10 */ s8 actorIndex;
    /* 0x11 */ s8 order;
    /* 0x12 */ s8 objAnimIndex;
    /* 0x13 */ u8 pad13;
    /* 0x14 */ s8 nodeSpeed;
    /* 0x15 */ u8 pad15[2];
    /* 0x17 */ s8 objAnimSpeed;
    /* 0x18 */ u8 objAnimLoopType; // 0 = Loop, 1 = Reverse loop, 2 = Play once, 3 = reverse once then stop.
    /* 0x19 */ u8 rotateType;
    /* 0x1A */ s8 yawSpinSpeed;
    /* 0x1B */ s8 rollSpinSpeed;
    /* 0x1C */ s8 pitchSpinSpeed;
    /* 0x1D */ u8 goToNode;
    /* 0x1E */ u8 pad1E[3];
    /* 0x21 */ s8 channel;
    /* 0x22 */ u8 pad22[2];
    /* 0x24 */ s8 pauseFrameCount;
    /* 0x25 */ u8 pad25;
    /* 0x26 */ u8 specialHide;
    /* 0x27 */ u8 messageId;
    /* 0x28 */ u8 pad28[3];
    /* 0x2B */ u8 fadeAlpha;
    /* 0x2C */ u8 nextAnim;
    /* 0x2D */ u8 pad2D;
    /* 0x2E */ u8 soundEffect;
    /* 0x2F */ u8 fadeOptions; // 1 = Start fading from fadeAlpha, 2 = make visible, 3 = make invisible.
    /* 0x30 */ u8 pad30[2];
} LevelObjectEntry_Animation;

typedef struct LevelObjectEntry_InfoPoint {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8[3];
    /* 0x0B */ u8 unkB;
} LevelObjectEntry_InfoPoint;

typedef struct LevelObjectEntry_Trigger {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 scale;
    /* 0x09 */ s8 unk9;
    /* 0x0A */ u8 rotation;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
} LevelObjectEntry_Trigger;

typedef struct LevelObjectEntry_AirZippers_WaterZippers {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
} LevelObjectEntry_AirZippers_WaterZippers;

typedef struct LevelObjectEntry_Unknown58 {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown58;

typedef struct LevelObjectEntry_WaveGenerator {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_WaveGenerator;

typedef struct LevelObjectEntry_Butterfly {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
} LevelObjectEntry_Butterfly;

typedef struct LevelObjectEntry_Parkwarden {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Parkwarden;

typedef struct LevelObjectEntry_WorldKey {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
} LevelObjectEntry_WorldKey;

typedef struct LevelObjectEntry_BananaCreator {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_BananaCreator;

typedef struct LevelObjectEntry_TreasureSucker {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s8 unk8;
} LevelObjectEntry_TreasureSucker;

typedef struct LevelObjectEntry_Log {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
} LevelObjectEntry_Log;

typedef struct LevelObjectEntry_LavaSpurt {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
} LevelObjectEntry_LavaSpurt;

typedef struct LevelObjectEntry_PosArrow {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_PosArrow;

typedef struct LevelObjectEntry_HitTester {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_HitTester;

typedef struct LevelObjectEntry_MidiFade {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 scale;
    /* 0x09 */ u8 rotation;
    /* 0x0A */ u8 unkA[16]; // Is this 16 bytes or 15 bytes with a padded 0?
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
} LevelObjectEntry_MidiFade;

typedef struct LevelObjectEntry_DynamicLightingObject {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_DynamicLightingObject;

typedef struct LevelObjectEntry_EffectBox {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_EffectBox;

typedef struct LevelObjectEntry_TrophyCab {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 rotation;
} LevelObjectEntry_TrophyCab;

typedef struct LevelObjectEntry_Bubbler {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u16 unkA;
} LevelObjectEntry_Bubbler;

typedef struct LevelObjectEntry_FlyCoin {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_FlyCoin;

typedef struct LevelObjectEntry_GoldenBalloon {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s8 unk8;
    /* 0x09 */ u8 scale;
    /* 0x0A */ s8 unkA;
} LevelObjectEntry_GoldenBalloon;

typedef struct LevelObjectEntry_Laserbolt {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Laserbolt;

typedef struct LevelObjectEntry_Lasergun {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ s8 unkA;
    /* 0x0B */ s8 unkB;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
} LevelObjectEntry_Lasergun;

typedef struct LevelObjectEntry_GroundZipper {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 scale;
    /* 0x0A */ u8 rotation;
} LevelObjectEntry_GroundZipper;

typedef struct LevelObjectEntry_OverridePos {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_OverridePos;

typedef struct LevelObjectEntry_WizpigShip {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_WizpigShip;

typedef struct LevelObjectEntry_SilverCoin {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_SilverCoin;

typedef struct LevelObjectEntry_Boost {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s8 unk8[1];
} LevelObjectEntry_Boost;

typedef struct LevelObjectEntry_WardenSmoke {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_WardenSmoke;

typedef struct LevelObjectEntry_Unknown94 {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown94;

typedef struct LevelObjectEntry_Unknown96 {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown96;

typedef struct LevelObjectEntry_Snowball {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Snowball;

typedef struct LevelObjectEntry_Teleport {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Teleport;

typedef struct LevelObjectEntry_Lighthouse_RocketSignpost {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
} LevelObjectEntry_Lighthouse_RocketSignpost;

typedef struct LevelObjectEntry_Windsail {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Windsail;

typedef struct LevelObjectEntry_RangeTrigger {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_RangeTrigger;

typedef struct LevelObjectEntry_Fireball_Octoweapon {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Fireball_Octoweapon;

typedef struct LevelObjectEntry_Frog {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ u8 unkA;
} LevelObjectEntry_Frog;

typedef struct LevelObjectEntry_SilverCoinAdv2 {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_SilverCoinAdv2;

typedef struct LevelObjectEntry_TTDoor {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 padD;
    /* 0x0E */ s8 unkE;
} LevelObjectEntry_TTDoor;

typedef struct LevelObjectEntry_MidiFadePoint {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u8 unkC[16];
    /* 0x1C */ u8 unk1C;
} LevelObjectEntry_MidiFadePoint;

typedef struct LevelObjectEntry_OctoBubble {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_OctoBubble;

typedef struct LevelObjectEntry_LevelName {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s8 unk8;
    /* 0x09 */ s8 unk9;
} LevelObjectEntry_LevelName;

typedef struct LevelObjectEntry_Midichset {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
} LevelObjectEntry_Midichset;

#endif
