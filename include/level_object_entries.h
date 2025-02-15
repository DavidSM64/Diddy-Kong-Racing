#ifndef _LEVEL_OBJECT_ENTRIES_H_
#define _LEVEL_OBJECT_ENTRIES_H_


/**
 * Only used in the DKR asset tool to help it figure out how to parse certain struct members.
 * Shouldn't affect the actual game code.
 * Also: It sucks that C didn't support variadic args in macros till c99. Double parenthesis is needed as a workaround.
*/
#define Hint(args) 

/* Size: 8 bytes. Shared across every entry. */
typedef struct LevelObjectEntryCommon {
    u8 objectID; // 9-bit object ID to load (uses size's MSB).
    u8 size; // 7-bit total entry length (MSB is used in object_id).
    s16 x, y, z; // Position in level
} LevelObjectEntryCommon;

typedef struct LevelObjectEntry_Racer {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s16 angleZ; 
    /* 0x0A */ s16 angleX; 
    /* 0x0C */ s16 angleY; 
    /* 0x0E */ s16 playerIndex;
} LevelObjectEntry_Racer;

typedef struct LevelObjectEntry_Scenery {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 modelIndex;
    /* 0x09 */ u8 radius;
    /* 0x0A */ u8 angleY; Hint((Angle, DivideBy:64))
    /* 0x0B */ u8 solid;
} LevelObjectEntry_Scenery;

typedef struct LevelObjectEntry_Animator {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s8 batchID;
    /* 0x09 */ s8 speedFactorX;
    /* 0x0A */ s8 speedfactorY;
    /* 0x0B */ s8 padB;
} LevelObjectEntry_Animator;

typedef struct LevelObjectEntry_Weapon {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Weapon;

typedef struct LevelObjectEntry_Smoke {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Smoke;

typedef struct LevelObjectEntry_Exit {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 destinationMapId; Hint((AssetId:ASSET_LEVEL_HEADERS))
    /* 0x09 */ u8 pad9;

    // Defines the location in overworld the player will spawn at.
    // Only used if the exit goes to overworld.
    //   0: Future Fun Land exit (also game start spawn)
    //   2: Dino Domain exit
    //   3: Snowflake Mountain exit
    //   4: Sherbet Island exit
    //   6: Dragon Forest exit
    //   7: Wizpig head exit
    /* 0x0A */ s8 overworldSpawnIndex;

    /* 0x0B */ u8 padB[5];
    /* 0x10 */ u8 radius; Hint((Scale, DivideBy:128)) // Activation radius.
    /* 0x11 */ u8 angleY; Hint((Angle, DivideBy:64))
    /* 0x12 */ u8 pad12[5];
    
    // Defines the location in a hub world the player will spawn at when exiting `destinationMapId`.
    // Only used if the exit goes to a race.
    //   0: Hub exit door
    //   1-4: One of the 4 race doors
    //   5: Boss door
    //   6: Minigame door
    //   7: Wizpig head
    /* 0x17 */ u8 returnSpawnIndex;

    // -1: Doesn't warp to a boss race
    // 0: Warps to a boss 1 race
    // 1: Warps to a boss 2 race
    /* 0x18 */ s8 bossFlag; Hint((Enum:WarpFlag))
    /* 0x19 */ u8 pad19;
} LevelObjectEntry_Exit;

typedef struct LevelObjectEntry_Audio {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u16 soundId;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
} LevelObjectEntry_Audio;

typedef struct LevelObjectEntry_AudioLine {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u16 soundID;
    /* 0x0C */ u8 lineID;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u16 unkE;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
} LevelObjectEntry_AudioLine;

typedef struct LevelObjectEntry_CameraControl {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s8 cameraID;
    /* 0x09 */ s8 pad9;
} LevelObjectEntry_CameraControl;

typedef struct LevelObjectEntry_SetupPoint {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 racerIndex;
    /* 0x09 */ u8 entranceID;
    /* 0x0A */ u8 angleY; Hint((Angle, DivideBy:64))
    /* 0x0B */ s8 vehicle; Hint((Enum:Vehicle))
} LevelObjectEntry_SetupPoint;

typedef struct LevelObjectEntry_Dino_Whale {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Dino_Whale;

typedef struct LevelObjectEntry_Checkpoint {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 scale;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 angleY; Hint((Angle, DivideBy:64))
    /* 0x0B */ s8 unkB;
    /* 0x0C */ s8 unkC;
    /* 0x0D */ s8 unkD;
    /* 0x0E */ s8 unkE;
    /* 0x0F */ s8 unkF;
    /* 0x10 */ s8 unk10;
    /* 0x11 */ s8 unk11;
    /* 0x12 */ s8 unk12;
    /* 0x13 */ s8 unk13;
    /* 0x14 */ s8 unk14;
    /* 0x15 */ s8 unk15;
    /* 0x16 */ s8 unk16;
    /* 0x17 */ s8 unk17;
    /* 0x18 */ s8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
} LevelObjectEntry_Checkpoint;

typedef struct LevelObjectEntry_Door {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 closedRotation; Hint((Angle, DivideBy:64))
    /* 0x09 */ u8 openRotation; Hint((Angle, DivideBy:64))
    /* 0x0A */ u8 modelIndex;
    /* 0x0B */ u8 distanceToOpen;
    /* 0x0C */ s8 doorID;
    /* 0x0D */ u8 balloonCount;
    /* 0x0E */ u8 doorType;
    /* 0x0F */ u8 textID;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ s8 keyID;
    /* 0x12 */ u8 scale;
    /* 0x13 */ s8 localBalloons; // Use world balloon count instead of total.
    /* 0x14 */ s8 levelID;
    /* 0x15 */ u8 balloonCountOverride; // Secondary balloon count requirement, for Future Fun Land.
} LevelObjectEntry_Door;

typedef struct LevelObjectEntry_FogChanger {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 distance;
    /* 0x09 */ u8 r;
    /* 0x0A */ u8 g;
    /* 0x0B */ u8 b;
    /* 0x0C */ s16 near;
    /* 0x0E */ s16 far;
    /* 0x10 */ s16 switchTimer;
} LevelObjectEntry_FogChanger;

typedef struct LevelObjectEntry_AiNode {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 nodeID;
    /* 0x0A */ u8 adjacent[4];
    /* 0x0E */ s8 elevation;
    /* 0x0F */ s8 padF;
} LevelObjectEntry_AiNode;

typedef struct LevelObjectEntry_WeaponBalloon {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8; // Unused?
    /* 0x09 */ u8 balloonType; Hint((Enum:BalloonType))
    /* 0x0A */ u8 scale; Hint((Scale, DivideBy:64)) // This is divided by 64 to get actual scale.
    /* 0x0B */ u8 padB; 
} LevelObjectEntry_WeaponBalloon;

typedef struct LevelObjectEntry_AudioSeqLine {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8[0xC];
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
    /* 0x08 */ u8 setting;
    /* 0x09 */ u8 radius;
} LevelObjectEntry_SkyControl;

typedef struct LevelObjectEntry_AudioReverb {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 lineID;
    /* 0x0A */ u8 unkA;
    /* 0x0A */ u8 unkB;
} LevelObjectEntry_AudioReverb;

typedef struct LevelObjectEntry_Torch_Mist {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 animSpeed;
    /* 0x09 */ u8 radius;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
} LevelObjectEntry_Torch_Mist;

typedef struct LevelObjectEntry_TexScroll {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s16 textureIndex;
    /* 0x0A */ s8 unkA;
    /* 0x0B */ s8 unkB;
} LevelObjectEntry_TexScroll;

typedef struct LevelObjectEntry_ModeChange {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 radius; 
    /* 0x09 */ u8 angleY; Hint((Angle, DivideBy:64))
    /* 0x0A */ u8 vehicleID; Hint((Enum:Vehicle))
    /* 0x0B */ u8 padB;
} LevelObjectEntry_ModeChange;

typedef struct LevelObjectEntry_StopWatchMan {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8[4];
} LevelObjectEntry_StopWatchMan;

typedef struct LevelObjectEntry_Banana {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Banana;

typedef struct LevelObjectEntry_RgbaLight {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ u8 unk1C;
} LevelObjectEntry_RgbaLight;

typedef struct LevelObjectEntry_Buoy_PirateShip {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8[4];
} LevelObjectEntry_Buoy_PirateShip;

typedef struct LevelObjectEntry_Weather {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s16 radius;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ s16 unk12;
} LevelObjectEntry_Weather;

typedef struct LevelObjectEntry_Bridge_WhaleRamp {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 modelIndex;
    /* 0x09 */ u8 angleY; Hint((Angle, DivideBy:64))
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u8 radius;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ s8 bobAmount; // How far up and down the whale goes
    /* 0x0F */ u8 allowedVehicles;
} LevelObjectEntry_Bridge_WhaleRamp;

typedef struct LevelObjectEntry_RampSwitch {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
} LevelObjectEntry_RampSwitch;

typedef struct LevelObjectEntry_SeaMonster {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_SeaMonster;

typedef struct LevelObjectEntry_Bonus {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 radius;
    /* 0x09 */ u8 angleY; Hint((Angle, DivideBy:64))
    /* 0x0A */ u8 unkA;
} LevelObjectEntry_Bonus;

typedef struct LevelObjectEntry_LensFlare {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s16 angleX;
    /* 0x0A */ s16 angleY;
    /* 0x0C */ u8 set1;
    /* 0x0D */ u8 set2;
    /* 0x0E */ u8 largeShine;
    /* 0x0A */ u8 padA;
    /* 0x10 */ u8 red;
    /* 0x11 */ u8 green;
    /* 0x12 */ u8 blue;
    /* 0x13 */ u8 alpha;
} LevelObjectEntry_LensFlare;

typedef struct LevelObjectEntry_LensFlareSwitch {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s16 radius;
    /* 0x0A */ u8 pad[10];
} LevelObjectEntry_LensFlareSwitch;

typedef struct LevelObjectEntry_CollectEgg {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_CollectEgg;

typedef struct LevelObjectEntry_EggCreator {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_EggCreator;

typedef struct LevelObjectEntry_CharacterFlag {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s16 angleZ;    
    /* 0x0A */ s16 radius;
    /* 0x0C */ s16 angleY;
    /* 0x0E */ s16 playerIndex;
} LevelObjectEntry_CharacterFlag;

/*
 * Note: the member names are just my best guesses. 
 * Take them with a grain of salt.
 */
typedef struct LevelObjectEntry_Animation {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 z_rotation; Hint((Angle, DivideBy:256))
    /* 0x09 */ u8 x_rotation; Hint((Angle, DivideBy:256))
    /* 0x0A */ u8 y_rotation; Hint((Angle, DivideBy:256))
    /* 0x0B */ u8 scale; Hint((Scale, DivideBy:64))
    /* 0x0C */ s16 objectIdToSpawn; Hint((Object)) // Index into the Level-Object Translation Table.
    /* 0x0E */ s16 animationStartDelay; Hint((Time, RoundToPlaces:3)) // Pause before continuing?
    /* 0x10 */ s8 actorIndex;
    /* 0x11 */ s8 order;
    /* 0x12 */ s8 objAnimIndex;
    /* 0x13 */ s8 unk13;
    /* 0x14 */ s8 nodeSpeed;
    /* 0x15 */ s8 unk15;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ s8 objAnimSpeed;
    /* 0x18 */ u8 objAnimLoopType; // 0 = Loop, 1 = Reverse loop, 2 = Play once, 3 = reverse once then stop.
    /* 0x19 */ u8 rotateType;
    /* 0x1A */ s8 yawSpinSpeed;
    /* 0x1B */ s8 rollSpinSpeed;
    /* 0x1C */ s8 pitchSpinSpeed;
    /* 0x1D */ u8 goToNode;
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ s8 unk1F;
    /* 0x20 */ s8 unk20;
    /* 0x21 */ s8 channel;
    /* 0x22 */ s8 unk22;
    /* 0x23 */ s8 unk23;
    /* 0x24 */ s16 pauseFrameCount; Hint((Time, RoundToPlaces:4)) // Pause before continuing?
    /* 0x26 */ s8 specialHide;
    /* 0x27 */ u8 messageId; Hint((AssetId:ASSET_GAME_TEXT))
    /* 0x28 */ s8 unk28;
    /* 0x29 */ s8 unk29;
    /* 0x2A */ s8 unk2A;
    /* 0x2B */ s8 fadeAlpha;
    /* 0x2C */ s8 nextAnim;
    /* 0x2D */ s8 unk2D;
    /* 0x2E */ s8 soundEffect;
    /* 0x2F */ s8 fadeOptions; // 1 = Start fading from fadeAlpha, 2 = make visible, 3 = make invisible.
    /* 0x30 */ s8 unk30;
    /* 0x31 */ u8 unk31;
} LevelObjectEntry_Animation;

typedef struct LevelObjectEntry_InfoPoint {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 hitbox[3];
    /* 0x0B */ u8 unkB;
} LevelObjectEntry_InfoPoint;

typedef struct LevelObjectEntry_Trigger {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 scale;
    /* 0x09 */ s8 index;
    /* 0x0A */ u8 angleY; Hint((Angle, DivideBy:64))
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
} LevelObjectEntry_Trigger;

typedef struct LevelObjectEntry_AirZippers_WaterZippers {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 radius;
    /* 0x0A */ u8 angleY; Hint((Angle, DivideBy:64))
    /* 0x0B */ u8 padB;
} LevelObjectEntry_AirZippers_WaterZippers;

typedef struct LevelObjectEntry_TimeTrial_Ghost {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_TimeTrial_Ghost;

typedef struct LevelObjectEntry_WaveGenerator {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8[10];
} LevelObjectEntry_WaveGenerator;

typedef struct LevelObjectEntry_Butterfly {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
} LevelObjectEntry_Butterfly;

typedef struct LevelObjectEntry_Fish {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
} LevelObjectEntry_Fish;

typedef struct LevelObjectEntry_Parkwarden {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Parkwarden;

typedef struct LevelObjectEntry_WorldKey {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 keyID;
    /* 0x09 */ u8 pad9;
} LevelObjectEntry_WorldKey;

typedef struct LevelObjectEntry_BananaCreator {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_BananaCreator;

typedef struct LevelObjectEntry_TreasureSucker {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s8 playerID;
    /* 0x09 */ u8 pad9;
} LevelObjectEntry_TreasureSucker;

typedef struct LevelObjectEntry_Log {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 modelIndex;
    /* 0x09 */ u8 radius;
    /* 0x0A */ u8 angleY; Hint((Angle, DivideBy:64))
    /* 0x0B */ u8 padB;
} LevelObjectEntry_Log;

typedef struct LevelObjectEntry_LavaSpurt {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 delayTimer; Hint((Time))
    /* 0x09 */ u8 initialTimer; Hint((Time))
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
    /* 0x09 */ u8 angleY; Hint((Angle, DivideBy:64))
    /* 0x0A */ u8 unkA[16]; // Is this 16 bytes or 15 bytes with a padded 0?
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
} LevelObjectEntry_MidiFade;

typedef struct LevelObjectEntry_DynamicLightingObject {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_DynamicLightingObject;

typedef struct LevelObjectEntry_EffectBox {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
} LevelObjectEntry_EffectBox;

typedef struct LevelObjectEntry_TrophyCab {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 angleY; Hint((Angle, DivideBy:64))
    /* 0x09 */ u8 pad9;
} LevelObjectEntry_TrophyCab;

typedef struct LevelObjectEntry_Bubbler {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 particlePropertyID;
    /* 0x09 */ u8 particleBehaviourID;
    /* 0x0A */ u16 particleDensity;
    /* 0x0C */ u8 unkC[4];
} LevelObjectEntry_Bubbler;

typedef struct LevelObjectEntry_FlyCoin {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_FlyCoin;

typedef struct LevelObjectEntry_GoldenBalloon {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s8 balloonID;
    /* 0x09 */ u8 scale;
    /* 0x0A */ s8 challengeID;
    /* 0x0B */ u8 padB;
} LevelObjectEntry_GoldenBalloon;

typedef struct LevelObjectEntry_Laserbolt {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Laserbolt;

typedef struct LevelObjectEntry_Lasergun {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 angleY; Hint((Angle, DivideBy:256))
    /* 0x09 */ u8 angleX; 
    /* 0x0A */ s8 targeting;
    /* 0x0B */ s8 fireRate;
    /* 0x0C */ u8 laserDuration;
    /* 0x0D */ u8 radius;
} LevelObjectEntry_Lasergun;

typedef struct LevelObjectEntry_GroundZipper {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 scale;
    /* 0x0A */ u8 angleY; Hint((Angle, DivideBy:64))
    /* 0x0B */ u8 unkB;
} LevelObjectEntry_GroundZipper;

typedef struct LevelObjectEntry_OverridePos {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s8 behaviorId;
    /* 0x09 */ s8 cutsceneId;
} LevelObjectEntry_OverridePos;

typedef struct LevelObjectEntry_WizpigShip {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_WizpigShip;

typedef struct LevelObjectEntry_SilverCoin {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_SilverCoin;

typedef struct LevelObjectEntry_Boost {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Boost;

// The object map file expects 8 bytes, but the in-game function expects something different?
typedef struct LevelObjectEntry_Boost2 {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s8 unk8[1];
} LevelObjectEntry_Boost2;

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
    /* 0x08 */ s8 levelID;
    /* 0x09 */ u8 pad9;
} LevelObjectEntry_Teleport;

typedef struct LevelObjectEntry_Lighthouse_RocketSignpost {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 radius;
    /* 0x0A */ u8 angleY; Hint((Angle, DivideBy:64))
    /* 0x0B */ u8 padB;
} LevelObjectEntry_Lighthouse_RocketSignpost;

typedef struct LevelObjectEntry_Windsail {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Windsail;

typedef struct LevelObjectEntry_RangeTrigger {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u16 radius;
    /* 0x0A */ u16 particleFlags;
} LevelObjectEntry_RangeTrigger;

typedef struct LevelObjectEntry_Fireball_Octoweapon {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Fireball_Octoweapon;

typedef struct LevelObjectEntry_Frog {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s16 homeRadius;
    /* 0x0A */ u8 drumstick;
    /* 0x0B */ u8 padB;
} LevelObjectEntry_Frog;

typedef struct LevelObjectEntry_SilverCoinAdv2 {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_SilverCoinAdv2;

typedef struct LevelObjectEntry_TTDoor {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 angleY; Hint((Angle, DivideBy:64)) // Rotation when closed
    /* 0x09 */ u8 unk9; Hint((Angle, DivideBy:64)) // Rotation when open
    /* 0x0A */ u8 radius;
    /* 0x0B */ u8 textID;
    /* 0x0C */ u8 scale;
    /* 0x0D */ u8 padD;
    /* 0x0E */ s8 doorType;
    /* 0x0F */ s8 padF;
} LevelObjectEntry_TTDoor;

typedef struct LevelObjectEntry_MidiFadePoint {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u8 unkC[16];
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
} LevelObjectEntry_MidiFadePoint;

typedef struct LevelObjectEntry_OctoBubble {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_OctoBubble;

typedef struct LevelObjectEntry_LevelName {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ s8 levelID;
    /* 0x09 */ s8 radius;
} LevelObjectEntry_LevelName;

typedef struct LevelObjectEntry_Midichset {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
} LevelObjectEntry_Midichset;

typedef struct LevelObjectEntry8000E2B4 {
    LevelObjectEntryCommon common;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
} LevelObjectEntry8000E2B4;

typedef struct LevelObjectEntry80011AD0 {
    LevelObjectEntryCommon common;
    u8 pad8[0x6];
    u8 unkD;
} LevelObjectEntry80011AD0;

typedef struct LevelObjectEntry8003FC44 {
    LevelObjectEntryCommon common;
    s8 unk9;
    s8 unkA;
} LevelObjectEntry8003FC44;

typedef struct LevelObjectEntry800BF524 {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
    u16 unkA;
    u16 unkC;
    u16 unkE;
    u8 unk10;
    u8 unk11;
} LevelObjectEntry800BF524;

typedef struct LevelObjectEntry_WavePower {
    LevelObjectEntryCommon common;
    u16 radius;
    u16 power;
    u16 divisor;
} LevelObjectEntry_WavePower;

typedef struct LevelObjectEntry_CharacterSelect {
    LevelObjectEntryCommon common;
    u8 pad8[0xA];
    s8 unk12; 
    s8 unk13;
    s8 unk14;
    s8 unk15;
    u8 unk16;
    s8 unk17;
    u8 unk18;
    s8 pad19[5]; 
    u8 unk1E;
    s8 unk1F;
    s8 pad20[4];
    s16 unk24;
    s8 unk26;
    u8 unk27;
    s8 unk28;
    s8 unk29;
    s8 unk2A;
    s8 unk2B;
    s8 unk2C;
    s8 unk2D;
    s8 unk2E;
    s8 unk2F;
    s8 unk30;
} LevelObjectEntry_CharacterSelect;

// Size: 0x10 bytes
typedef struct LevelObjectEntry_Unk8000CC7C {
    LevelObjectEntryCommon common;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
} LevelObjectEntry_Unk8000CC7C;

typedef struct LevelObjectEntry_Unknown20 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown20;

typedef struct LevelObjectEntry_Unknown21 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown21;

typedef struct LevelObjectEntry_Unknown24 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown24;

typedef struct LevelObjectEntry_Unknown34 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown34;

typedef struct LevelObjectEntry_Unknown35 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown35;

typedef struct LevelObjectEntry_Unknown42 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown42;

typedef struct LevelObjectEntry_Unknown48 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown48;

typedef struct LevelObjectEntry_Unknown63 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown63;

typedef struct LevelObjectEntry_Unknown91 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown91;

typedef struct LevelObjectEntry_Unknown92 {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
} LevelObjectEntry_Unknown92;

typedef struct LevelObjectEntry_Unknown106 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown106;

typedef struct LevelObjectEntry_Unknown114 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown114;

typedef struct LevelObjectEntry_AnimatedObject {
    LevelObjectEntryCommon common;
} LevelObjectEntry_AnimatedObject;

typedef struct LevelObjectEntry_DynamicLightObject2 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_DynamicLightObject2;

typedef struct LevelObjectEntry_ParkWarden {
    LevelObjectEntryCommon common;
} LevelObjectEntry_ParkWarden;

typedef struct LevelObjectEntry_TajTelepoint {
    LevelObjectEntryCommon common;
} LevelObjectEntry_TajTelepoint;

typedef struct LevelObjectEntry_CameraAnimation {
    LevelObjectEntryCommon common;
} LevelObjectEntry_CameraAnimation;

typedef struct LevelObjectEntry_BossHazardTrigger {
    LevelObjectEntryCommon common;
    u8 unk8[4];
} LevelObjectEntry_BossHazardTrigger;

typedef struct LevelObjectEntry_DoorOpener {
    LevelObjectEntryCommon common;
} LevelObjectEntry_DoorOpener;

typedef struct LevelObjectEntry_PigRocketeer {
    LevelObjectEntryCommon common;
} LevelObjectEntry_PigRocketeer;

typedef struct LevelObjectEntry_WizpigGhosts {
    LevelObjectEntryCommon common;
} LevelObjectEntry_WizpigGhosts;

typedef struct LevelObjectEntry_Unknown120 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown120;

typedef struct LevelObjectEntry_Unknown121 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown121;

typedef struct LevelObjectEntry_Unknown122 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown122;

typedef struct LevelObjectEntry_Unknown123 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown123;

typedef struct LevelObjectEntry_Unknown124 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown124;

typedef struct LevelObjectEntry_Unknown125 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown125;

typedef struct LevelObjectEntry_Unknown126 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown126;

typedef struct LevelObjectEntry_Unknown127 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown127;

typedef struct LevelObjectEntry {
    union {
        LevelObjectEntry_Racer racer;
        LevelObjectEntry_Scenery scenery;
        LevelObjectEntry_Fish fish;
        LevelObjectEntry_Animator animator;
        LevelObjectEntry_Weapon weapon;
        LevelObjectEntry_Smoke smoke;
        LevelObjectEntry_Exit exit;
        LevelObjectEntry_Audio audio;
        LevelObjectEntry_AudioLine audioLine;
        LevelObjectEntry_CameraControl cameraControl;
        LevelObjectEntry_SetupPoint setupPoint;
        LevelObjectEntry_Dino_Whale dino_whale;
        LevelObjectEntry_Checkpoint checkpoint;
        LevelObjectEntry_Door door;
        LevelObjectEntry_FogChanger fogChanger;
        LevelObjectEntry_AiNode aiNode;
        LevelObjectEntry_WeaponBalloon weaponBalloon;
        LevelObjectEntry_AudioSeqLine audioSeqLine;
        LevelObjectEntry_BombExplosion bombExplosion;
        LevelObjectEntry_WBalloonPop balloonPop;
        LevelObjectEntry_Unknown25 unk25;
        LevelObjectEntry_SkyControl skyControl;
        LevelObjectEntry_AudioReverb audioReverb;
        LevelObjectEntry_Torch_Mist torch_mist;
        LevelObjectEntry_TexScroll texScroll;
        LevelObjectEntry_ModeChange modeChange;
        LevelObjectEntry_StopWatchMan tt;
        LevelObjectEntry_Banana banana;
        LevelObjectEntry_RgbaLight rgbaLighting;
        LevelObjectEntry_Buoy_PirateShip buoy_pirateShip;
        LevelObjectEntry_Weather weather;
        LevelObjectEntry_Bridge_WhaleRamp bridge_whaleRamp;
        LevelObjectEntry_RampSwitch rampSwitch;
        LevelObjectEntry_SeaMonster seaMonster;
        LevelObjectEntry_Bonus bonus;
        LevelObjectEntry_LensFlare lensFlare;
        LevelObjectEntry_LensFlareSwitch lensFlareSwitch;
        LevelObjectEntry_CollectEgg collectEgg;
        LevelObjectEntry_EggCreator eggCreator;
        LevelObjectEntry_CharacterFlag characterFlag;
        LevelObjectEntry_Animation animation;
        LevelObjectEntry_InfoPoint infoPoint;
        LevelObjectEntry_Trigger trigger;
        LevelObjectEntry_AirZippers_WaterZippers airzipper_waterzipper;
        LevelObjectEntry_TimeTrial_Ghost ghost;
        LevelObjectEntry_WaveGenerator waverGenerator;
        LevelObjectEntry_Butterfly butterfly;
        LevelObjectEntry_Parkwarden taj;
        LevelObjectEntry_WorldKey worldKey;
        LevelObjectEntry_BananaCreator bananaCreator;
        LevelObjectEntry_TreasureSucker treasureSucker;
        LevelObjectEntry_Log log;
        LevelObjectEntry_LavaSpurt lavaSpurt;
        LevelObjectEntry_PosArrow posArrow;
        LevelObjectEntry_HitTester hitTester;
        LevelObjectEntry_MidiFade midiFade;
        LevelObjectEntry_DynamicLightingObject dynamicLighting;
        LevelObjectEntry_EffectBox effectBox;
        LevelObjectEntry_TrophyCab trophyCabinet;
        LevelObjectEntry_Bubbler bubbler;
        LevelObjectEntry_FlyCoin flyCoin;
        LevelObjectEntry_GoldenBalloon goldenBalloon;
        LevelObjectEntry_Laserbolt laserbolt;
        LevelObjectEntry_Lasergun lasergun;
        LevelObjectEntry_GroundZipper groundZipper;
        LevelObjectEntry_OverridePos overridePos;
        LevelObjectEntry_WizpigShip wizpigShip;
        LevelObjectEntry_SilverCoin silverCoin;
        LevelObjectEntry_Boost boost;
        LevelObjectEntry_WardenSmoke tajSmoke;
        LevelObjectEntry_Unknown94 unk94;
        LevelObjectEntry_Unknown96 unk96;
        LevelObjectEntry_Snowball snowball;
        LevelObjectEntry_Teleport teleport;
        LevelObjectEntry_Lighthouse_RocketSignpost lighthouse_signpost;
        LevelObjectEntry_Windsail windsail;
        LevelObjectEntry_RangeTrigger rangeTrigger;
        LevelObjectEntry_Fireball_Octoweapon fireball_octoweapon;
        LevelObjectEntry_Frog frog;
        LevelObjectEntry_SilverCoinAdv2 silverCoinAdv2;
        LevelObjectEntry_TTDoor ttDoor;
        LevelObjectEntry_MidiFadePoint midiFadePoint;
        LevelObjectEntry_OctoBubble octoBubble;
        LevelObjectEntry_LevelName levelName;
        LevelObjectEntry_Midichset midichset;
        LevelObjectEntry8000E2B4 unk8000E2B4;
        LevelObjectEntry80011AD0 unk80011AD0;
        LevelObjectEntry8003FC44 unk8003FC44;
        LevelObjectEntry800BF524 unk800BF524;
        LevelObjectEntry_WavePower wavePower;
        LevelObjectEntry_CharacterSelect characterSelect;
    };
} LevelObjectEntry;

#undef Hint

#endif
