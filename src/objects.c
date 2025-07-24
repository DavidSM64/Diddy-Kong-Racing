#include "objects.h"
#include "memory.h"

#include "asset_enums.h"
#include "asset_loading.h"
#include "audio_spatial.h"
#include "audio_vehicle.h"
#include "audiosfx.h"
#include "camera.h"
#include "fade_transition.h"
#include "game.h"
#include "game_text.h"
#include "game_ui.h"
#include "gzip.h"
#include "joypad.h"
#include "level_object_entries.h"
#include "lights.h"
#include "macros.h"
#include "math_util.h"
#include "menu.h"
#include "object_functions.h"
#include "object_models.h"
#include "particles.h"
#include "PR/os_cont.h"
#include "PR/os_convert.h"
#include "PR/os_system.h"
#include "PR/rcp.h"
#include "PRinternal/piint.h"
#include "PRinternal/viint.h"
#include "printf.h"
#include "racer.h"
#include "save_data.h"
#include "structs.h"
#include "textures_sprites.h"
#include "thread0_epc.h"
#include "thread3_main.h"
#include "tracks.h"
#include "types.h"
#include "vehicle_misc.h"
#include "video.h"
#include "waves.h"
#include "weather.h"

#define OBJECT_MAP_SIZE 0x3000
#define MAX_CHECKPOINTS 60
#define OBJECT_POOL_SIZE 0x15800
#define OBJECT_BLUEPRINT_SIZE 0x800
#define OBJECT_SLOT_COUNT 512
#define OBJECT_COLLISION_COUNT 20
#define AINODE_COUNT 128
#define CAMCONTROL_COUNT 20
#define BOOST_VERT_COUNT 9
#define BOOST_TRI_COUNT 8

#ifndef _ALIGN16
#define _ALIGN16(a) (((u32) (a) & ~0xF) + 0x10)
#endif

#define SET_SHIFT_AND_MASK(varShift, varMask, x) \
    varShift = x;                                \
    varMask = 0xFFFF >> x;

/************ .data ************/

FadeTransition gTajChallengeTransition = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_OUT, FADE_COLOR_BLACK, 30, 15);
FadeTransition gBalloonCutsceneTransition = FADE_TRANSITION(FADE_CIRCLE, FADE_FLAG_NONE, FADE_COLOR_BLACK, 30, 15);

s32 D_800DC700 = 0;
s32 D_800DC704 = 0; // Currently unknown, might be a different type.
s16 D_800DC708 = 0;
s32 D_800DC70C = 0; // Currently unknown, might be a different type.
s16 D_800DC710 = 1;
s32 D_800DC714 = 0; // Currently unknown, might be a different type.
Object *gGhostObjStaff = NULL;
s8 gRollingDemo = FALSE;
s32 gObjectTexAnim = FALSE;
s16 gTimeTrialTime = 10800;
s16 gTimeTrialVehicle = -1;
s16 gTimeTrialCharacter = 0;
u8 gHasGhostToSave = FALSE;
u8 gTimeTrialStaffGhost = FALSE;
u8 gBeatStaffGhost = FALSE;
s8 gLeadPlayerIndex = 0;
s8 gTwoActivePlayersInAdventure = FALSE; // Has basically the same purpose as gTwoPlayerAdvRace
s8 gSwapLeadPlayer = FALSE;
s8 gIsP2LeadPlayer = FALSE;
Vertex *gBoostVerts[2] = { 0, 0 };
Triangle *gBoostTris[2] = { 0, 0 };
Object *gShieldEffectObject = NULL;
s32 gBoostObjOverrideID = 9;
Object *gMagnetEffectObject = NULL;

f32 D_800DC768[16] = { 0.0f, 1.0f,  0.70711f,  0.70711f,  1.0f,  0.0f, 0.70711f,  -0.70711f,
                       0.0f, -1.0f, -0.70711f, -0.70711f, -1.0f, 0.0f, -0.70711f, 0.70711f };

u16 gRacerObjectTable[] = {
    // Car
    ASSET_OBJECT_ID_KREMCAR,
    ASSET_OBJECT_ID_BADGERCAR,
    ASSET_OBJECT_ID_TORTCAR,
    ASSET_OBJECT_ID_CONKACAR,
    ASSET_OBJECT_ID_TIGERCAR,
    ASSET_OBJECT_ID_BANJOCAR,
    ASSET_OBJECT_ID_CHICKENCAR,
    ASSET_OBJECT_ID_MOUSECAR,
    ASSET_OBJECT_ID_SWCAR,
    ASSET_OBJECT_ID_DIDDYCAR,
    // Hover
    ASSET_OBJECT_ID_KREMLINHOVER,
    ASSET_OBJECT_ID_BADGERHOVER,
    ASSET_OBJECT_ID_TORTHOVER,
    ASSET_OBJECT_ID_CONKAHOVER,
    ASSET_OBJECT_ID_TIGERHOVER,
    ASSET_OBJECT_ID_BANJOHOVER,
    ASSET_OBJECT_ID_CHICKENHOVER,
    ASSET_OBJECT_ID_MOUSEHOVER,
    ASSET_OBJECT_ID_TICKTOCKHOVER,
    ASSET_OBJECT_ID_DIDDYHOVER,
    // Plane
    ASSET_OBJECT_ID_KREMPLANE,
    ASSET_OBJECT_ID_BADGERPLANE,
    ASSET_OBJECT_ID_TORTPLANE,
    ASSET_OBJECT_ID_CONKA,
    ASSET_OBJECT_ID_TIGPLANE,
    ASSET_OBJECT_ID_BANJOPLANE,
    ASSET_OBJECT_ID_CHICKENPLANE,
    ASSET_OBJECT_ID_MOUSEPLANE,
    ASSET_OBJECT_ID_TICKTOCKPLANE,
    ASSET_OBJECT_ID_DIDDYPLANE,
    // Car
    ASSET_OBJECT_ID_KREMCAR,
    ASSET_OBJECT_ID_BADGERCAR,
    ASSET_OBJECT_ID_TORTCAR,
    ASSET_OBJECT_ID_CONKACAR,
    ASSET_OBJECT_ID_TIGERCAR,
    ASSET_OBJECT_ID_BANJOCAR,
    ASSET_OBJECT_ID_CHICKENCAR,
    ASSET_OBJECT_ID_MOUSECAR,
    ASSET_OBJECT_ID_SWCAR,
    ASSET_OBJECT_ID_DIDDYCAR,
    // Car again?
    ASSET_OBJECT_ID_KREMCAR,
    ASSET_OBJECT_ID_BADGERCAR,
    ASSET_OBJECT_ID_TORTCAR,
    ASSET_OBJECT_ID_CONKACAR,
    ASSET_OBJECT_ID_TIGERCAR,
    ASSET_OBJECT_ID_BANJOCAR,
    ASSET_OBJECT_ID_CHICKENCAR,
    ASSET_OBJECT_ID_MOUSECAR,
    ASSET_OBJECT_ID_SWCAR,
    ASSET_OBJECT_ID_DIDDYCAR,
    // Special
    ASSET_OBJECT_ID_TRICKYTOPS,
    ASSET_OBJECT_ID_WALRUS,
    ASSET_OBJECT_ID_DRAGONBOSS,
    ASSET_OBJECT_ID_TERRYBOSS,
    ASSET_OBJECT_ID_SNOWBALLBOSS,
    ASSET_OBJECT_ID_FLYINGCARPET,
    ASSET_OBJECT_ID_OCTOPUS,
    ASSET_OBJECT_ID_WIZPIG,
    ASSET_OBJECT_ID_WIZPIGROCKET,
};

// A table of which vehicles to use for boss races.
// https://www.youtube.com/watch?v=WQJAtns_rMk
BossRaceVehicles gBossVehicles[] = {
    { VEHICLE_CAR, VEHICLE_TRICKY },         // Tricky 1
    { VEHICLE_HOVERCRAFT, VEHICLE_BLUEY },   // Bluey 1
    { VEHICLE_PLANE, VEHICLE_SMOKEY },       // Smokey 1
    { VEHICLE_CAR, VEHICLE_TRICKY },         // Tricky 2
    { VEHICLE_HOVERCRAFT, VEHICLE_BLUEY },   // Bluey 2
    { VEHICLE_HOVERCRAFT, VEHICLE_BUBBLER }, // Bubbler 1
    { VEHICLE_HOVERCRAFT, VEHICLE_BUBBLER }, // Bubbler 2
    { VEHICLE_PLANE, VEHICLE_SMOKEY },       // Smokey 2
    { VEHICLE_CAR, VEHICLE_WIZPIG },         // Wizpig 1
    { VEHICLE_PLANE, VEHICLE_ROCKET },       // Wizpig 2
};

s8 D_800DC834[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

s8 D_800DC840[8] = { 9, 1, 2, 3, 4, 5, 7, 0 };

s8 gNoBoundsCheck = FALSE;
u32 gMagnetColours[3] = {
    COLOUR_RGBA32(255, 64, 16, 0), // Level 1
    COLOUR_RGBA32(16, 64, 255, 0), // Level 2
    COLOUR_RGBA32(16, 255, 64, 0), // Level 3
};
FadeTransition gRaceEndFade = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 40, FADE_STAY);
FadeTransition gRaceEndTransition = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_OUT, FADE_COLOR_BLACK, 40, 0);

/*******************************/

/************ .rodata ************/

UNUSED const char sObjectOutofMemString[] = "Objects out of ram(1) !!\n";
UNUSED const char sDoorNumberErrorString[] = "Door numbering error %d!!\n";
UNUSED const char sObjectScopeErrorString[] = "objGetScope: Unknown scope for object %d\n";

/*********************************/

/************ .bss ************/

s16 D_8011AC20[128];
s8 D_8011AD20;
s8 D_8011AD21;
s8 D_8011AD22[2];
s8 D_8011AD24[2];
s8 D_8011AD26;
f32 gObjectModelScaleY;
s32 D_8011AD2C;
f32 gCurrentLightIntensity;
Object *gGhostObjPlayer;
s32 gTimeTrialContPak; // gTimeTrialContPak is ultimately set by func_80074B34, and is almost definitely SIDeviceStatus
s8 D_8011AD3C;
s8 D_8011AD3D;
s8 D_8011AD3E;
Object *gTransformObject; // Set but never read.
s8 gTransformTimer;
s8 gOverworldVehicle;
s16 gTransformPosX;
s16 gTransformPosY;
s16 gTransformPosZ;
s16 gTransformAngleY;
s16 gRaceEndTimer;
s8 gRaceEndStage;
s8 gNumRacersSaved;
UNUSED s8 unused_D_8011AD52;
s8 D_8011AD53;
s32 D_8011AD54;
s32 *gSpawnObjectHeap;
s32 D_8011AD5C;
s32 D_8011AD60;
s32 *gAssetsObjectHeadersTable;
s32 gAssetsObjectHeadersTableLength;
s32 *gAssetsMiscSection;
s32 *gAssetsMiscTable;
s32 D_8011AD74;
Gfx *D_8011AD78[10];
s32 gAssetsMiscTableLength;
s16 D_8011ADA4;
f32 gObjectUpdateRateF;
s32 gPathUpdateOff;
s32 gEventCountdown;
s32 gRaceFinishTriggered;
s32 gEventStartTimer;
s32 D_8011ADBC;
s32 gNumFinishedRacers;
s8 gFirstTimeFinish;
s8 D_8011ADC5;
u32 gBalloonCutsceneTimer;
s8 (*gDrawbridgeTimers)[8];
f32 gObjectOffsetY;
s8 D_8011ADD4;
s8 gOverrideDoors;
Object *D_8011ADD8[10]; // Array of OverRidePos objects
s8 D_8011AE00;          // Number of OverRidePos objects in D_8011ADD8
s8 D_8011AE01;          // A boolean? I've seen it either as 0 or 1
s8 gIsNonCarRacers;
s8 gIsSilverCoinRace;
Object *D_8011AE08[16];
ObjectHeader *(*gLoadedObjectHeaders)[ASSET_OBJECTS_COUNT];
u8 (*gObjectHeaderReferences)[ASSET_OBJECTS_COUNT];
TextureHeader *D_8011AE50;
TextureHeader *D_8011AE54;
Object **gObjPtrList; // Not sure about the number of elements
s32 gObjectCount;
s32 gObjectListStart;
s32 gParticleCount;
Object *gObjectMemoryPool;
Object **gCollisionObjects;
s32 gCollisionObjectCount;
Object **D_8011AE74; // Pointer to an array of Animation objects
s16 D_8011AE78;      // Number of Animation objects in D_8011AE74
s16 gCutsceneID;
s16 gFirstActiveObjectId;
s8 D_8011AE7E;
s16 gTTGhostTimeToBeat;
s16 gPrevTimeTrialVehicle; // Current Vehicle being used in track?
s16 gMapDefaultVehicle;    // Vehicle enum
s32 D_8011AE88;
Gfx *gObjectCurrDisplayList;
Mtx *gObjectCurrMatrix;
Vertex *gObjectCurrVertexList;
u8 *gObjectMapSpawnList[2];
s32 gObjectMapSize[2];
s32 gObjectMapID[2];
s32 *gObjectMap[2];
s16 *gAssetsLvlObjTranslationTable;
s32 gAssetsLvlObjTranslationTableLength;
s32 gObjectMapIndex;
Object **gParticlePtrList;
s32 gFreeListCount;
CheckpointNode *gTrackCheckpoints; // Array of structs, unknown number of members
s32 gNumberOfMainCheckpoints;
s32 gNumberOfTotalCheckpoints;
s16 gTajChallengeType;
Object *(*gCameraObjList)[CAMCONTROL_COUNT]; // Camera objects with a maximum of 20
s32 gCameraObjCount;                         // The number of camera objects in the above list
Object *(*gRacers)[10];                      // Official Name: playerlist
// Similar to gRacers, but sorts the pointer by the players' current position in the race.
Object **gRacersByPosition;
// Similar to gRacers, but sorts the pointer by controller ports 1-4, then CPUs.
Object **gRacersByPort;
s32 gNumRacers;
u8 gTimeTrialEnabled;
u8 gIsTimeTrial;
s8 gIsTajChallenge;
s8 gTajRaceInit;
s8 gChallengePrevMusic;
s32 gChallengePrevInstruments;
s8 D_8011AF00;
Object *(*gAINodes)[AINODE_COUNT];
s32 gAINodeTail[2];
s32 gInitAINodes;
s32 D_8011AF14;
f32 gElevationHeights[5];
s32 D_8011AF2C;
ShadeProperties *gWorldShading; // Effectively unused.
s32 D_8011AF34;
s32 D_8011AF38[10];
Object_MidiFade *D_8011AF60;
TexCoords D_8011AF68[32];
Vec3s gEnvmapPos[2];
unk800179D0 *D_8011AFF4;
s32 gBoostVertCount;
s32 gNumOfBoostVerts;
s32 gBoostTriCount;
s32 gNumOfBoostTris;
s32 gBoostVertFlip; // indexes gBoostVerts and gBoostTris
u8 gShieldSineTime[16];
Object *gBoostEffectObjects[NUMBER_OF_CHARACTERS];
u8 D_8011B048[16]; // Vehicle IDs for the boost objects, used to determine which racer is using which boost object.
u8 D_8011B058[16];
u8 D_8011B068[16];
RacerFXData gRacerFXData[NUMBER_OF_CHARACTERS];

extern s16 gGhostMapID;

/******************************/

/**
 * Spawns control objects for racer boost visuals, as well as shield and magnet visuals.
 * Boost geometry is made in real time, and allocated here.
 * This function is called on every level load, but only racers use the stuff here.
 */
void racerfx_alloc(s32 numberOfVertices, s32 numberOfTriangles) {
    Object_Boost *boostObj;
    LevelObjectEntry_Boost2 objEntry;
    s32 i;

    gBoostTris[0] = (Triangle *) mempool_alloc_safe(
        ((numberOfTriangles * sizeof(Triangle)) + (numberOfVertices * sizeof(Vertex))) * 2, COLOUR_TAG_BLUE);
    gBoostTris[1] = (Triangle *) ((u32) gBoostTris[0] + numberOfTriangles * sizeof(Triangle));
    gBoostVerts[0] = (Vertex *) ((u32) gBoostTris[1] + numberOfTriangles * sizeof(Triangle));
    gBoostVerts[1] = (Vertex *) ((u32) gBoostVerts[0] + numberOfVertices * sizeof(Vertex));
    gBoostVertCount = numberOfVertices;
    gNumOfBoostVerts = 0;
    gBoostTriCount = numberOfTriangles;
    gNumOfBoostTris = 0;
    gBoostVertFlip = 0;
    boostObj = (Object_Boost *) get_misc_asset(ASSET_MISC_20);
    // Makes 10 boost objects, but only 8 racers can actually exist at once.
    for (i = 0; i < NUMBER_OF_CHARACTERS; i++) {
        objEntry.common.objectID = ASSET_OBJECT_ID_BOOST;
        objEntry.common.size = sizeof(LevelObjectEntry_Boost2);
        objEntry.common.x = 0;
        objEntry.common.y = 0;
        objEntry.common.z = 0;
        objEntry.racerIndex = i;
        gBoostEffectObjects[i] = spawn_object(&objEntry.common, OBJECT_SPAWN_UNK01);
        if (gBoostEffectObjects[i] != NULL) {
            gBoostEffectObjects[i]->properties.common.unk0 = 0;
            gBoostEffectObjects[i]->properties.common.unk4 = 0;
            boostObj[i].unk70 = 0;
            boostObj[i].unk74 = 0.0f;
            boostObj[i].sprite = tex_load_sprite(boostObj[i].spriteId, 0);
            boostObj[i].tex = load_texture(boostObj[i].textureId);
            boostObj[i].unk72 = rand_range(0, 255);
            boostObj[i].unk73 = 0;
            // This is for shields, not boosts.
            gShieldSineTime[i] = rand_range(0, 255);
        }
        D_8011B068[i] = TRUE;
    }
    gBoostObjOverrideID = 9;
    objEntry.common.objectID = ASSET_OBJECT_ID_SHIELD;
    objEntry.common.size = sizeof(LevelObjectEntry_Boost2);
    objEntry.common.x = 0;
    objEntry.common.y = 0;
    objEntry.common.z = 0;
    gShieldEffectObject = spawn_object(&objEntry.common, OBJECT_SPAWN_NONE);
    for (i = 0; i < NUMBER_OF_CHARACTERS; i++) {
        gRacerFXData[i].unk0 = 0;
        gRacerFXData[i].unk1 = rand_range(0, 255);
        gRacerFXData[i].unk2 = rand_range(0, 255);
        gRacerFXData[i].unk3 = 0;
    }
    objEntry.common.objectID = ASSET_OBJECT_ID_AINODE;
    objEntry.common.size = sizeof(LevelObjectEntry_Boost2) + 0x80; // Not sure where this 0x80 comes from.
    objEntry.common.x = 0;
    objEntry.common.y = 0;
    objEntry.common.z = 0;
    gMagnetEffectObject = spawn_object(&objEntry.common, OBJECT_SPAWN_NONE);
}

/**
 * Attempts to free the boost, shield and magnet objects and assets.
 */
void racerfx_free(void) {
    Sprite *sprite;
    TextureHeader *texture;
    Object_Boost *objBoost;
    u32 i;

    if (gBoostTris[0]) {
        mempool_free(gBoostTris[0]);
        gBoostTris[0] = NULL;
        gBoostTris[1] = NULL;
        gBoostVerts[0] = NULL;
        gBoostVerts[1] = NULL;
    }
    objBoost = (Object_Boost *) get_misc_asset(ASSET_MISC_20);
    for (i = 0; i < NUMBER_OF_CHARACTERS; i++) {
        sprite = objBoost[i].sprite;
        if (sprite != NULL) {
            sprite_free(sprite);
            objBoost[i].sprite = NULL;
        }
        texture = objBoost[i].tex;
        if (texture != NULL) {
            tex_free(texture);
            objBoost[i].tex = NULL;
        }
    }
    if (gShieldEffectObject != NULL) {
        free_object(gShieldEffectObject);
    }
    gShieldEffectObject = NULL;

    if (gMagnetEffectObject != NULL) {
        free_object(gMagnetEffectObject);
    }
    gMagnetEffectObject = NULL;
    gParticlePtrList_flush();
}

void func_8000B38C(Vertex *vertices, Triangle *triangles, ObjectTransform *trans, f32 arg3, f32 arg4, s16 arg5,
                   TextureHeader *tex) {
    s32 sp80[8];
    s32 i;
    s32 height, width;
    s16 *v;
    Vec3f sp64;
    s32 *tri;
    f32 *ptr;
    s32 temp;

    v = (s16 *) vertices;

    sp64.z = -arg4;
    vec3f_rotate_py(&trans->rotation, &sp64);

    // A rather strange way to fill structures

    *v++ = sp64.f[0] + trans->x_position;
    *v++ = sp64.f[1] + trans->y_position;
    *v++ = sp64.f[2] + trans->z_position;
    *v++ = -1;
    *v++ = -1;

    ptr = D_800DC768;
    for (i = 0; i < 8; i++) {
        sp64.x = *ptr++ * arg3;
        sp64.y = *ptr++ * arg3;
        sp64.z = 0.0f;

        vec3f_rotate(&trans->rotation, &sp64);

        *v++ = sp64.f[0] + trans->x_position;
        *v++ = sp64.f[1] + trans->y_position;
        *v++ = sp64.f[2] + trans->z_position;
        *v++ = -1;
        *v++ = -1;
    }

    width = (tex->width - 1) << 4;
    height = (tex->height - 1) << 4;

    for (i = 0; i < 8; i++) {
        sp80[i] = width + ((sins_s16(arg5) * width) >> 16);
        sp80[i] |= ((height << 16) + height * coss_s16(arg5)) & 0xFFFF0000;
        arg5 += 0x2000;
    }

    tri = (s32 *) triangles;
    for (i = 0; i < 8; i++) {
        *tri++ = DKR_TRIANGLE(BACKFACE_CULL, 0, i + 1, ((i + 1) & 7) + 1);
        *tri++ = ((width & 0xFFFF) << 16) | (height & 0xFFFF);
        *tri++ = sp80[i];
        *tri++ = sp80[(i + 1) & 7];
    }
}

void func_8000B750(Object *racerObj, s32 racerIndex, s32 vehicleIDPrev, s32 boostType, s32 arg4) {
    Vec3f sp74;
    f32 temp_f0;
    f32 var_f2;
    Object_Boost *boostAsset;
    ObjectTransform objTrans;
    Object_Boost *objBoostRacer;
    Object_Boost *objBoostType;
    Object_Boost_Inner *boostData;

    if (racerIndex == -1) {
        racerIndex = gBoostObjOverrideID;
        gBoostObjOverrideID--;
    }
    if (gBoostObjOverrideID < 0) {
        gBoostObjOverrideID = 0;
    }
    if (racerIndex >= 0 && racerIndex < NUMBER_OF_CHARACTERS) {
        boostAsset = (Object_Boost *) get_misc_asset(ASSET_MISC_20);
        objBoostType = &boostAsset[boostType];
        objBoostRacer = &boostAsset[racerIndex];
        if (gBoostEffectObjects[racerIndex] != NULL) {
            switch (vehicleIDPrev) {
                default:
                    boostData = NULL;
                    break;
                case VEHICLE_CAR:
                    boostData = &objBoostRacer->carBoostData;
                    break;
                case VEHICLE_HOVERCRAFT:
                    boostData = &objBoostRacer->hovercraftBoostData;
                    break;
                case VEHICLE_PLANE:
                    boostData = &objBoostRacer->flyingBoostData;
                    break;
                case VEHICLE_ROCKET:
                    boostData = &objBoostRacer->flyingBoostData;
                    break;
            }
            if (boostData != NULL) {
                D_8011B048[racerIndex] = vehicleIDPrev;
                D_8011B058[racerIndex] = boostType;
                if (objBoostRacer->unk70 == 2) {
                    temp_f0 = coss_f(objBoostRacer->unk72 << 12);
                    var_f2 = (boostData->unk14 + (temp_f0 * boostData->unk18)) * objBoostRacer->unk74;
                    temp_f0 = (boostData->unk1C + (temp_f0 * boostData->unk20)) * objBoostRacer->unk74;
                    if ((boostType & 3) == BOOST_MEDIUM) {
                        var_f2 *= 1.09f;
                        temp_f0 *= 1.09f;
                    }
                    if ((boostType & 3) >= BOOST_LARGE) {
                        var_f2 *= 1.18f;
                        temp_f0 *= 1.18f;
                    }
                    objTrans.x_position = boostData->position.x;
                    objTrans.y_position = boostData->position.y;
                    objTrans.z_position = boostData->position.z;
                    objTrans.scale = 1.0f;
                    objTrans.rotation.y_rotation = -0x8000;
                    objTrans.rotation.x_rotation = 0;
                    objTrans.rotation.z_rotation = 0;
                    func_8000B38C(&gBoostVerts[gBoostVertFlip][gNumOfBoostVerts],
                                  &gBoostTris[gBoostVertFlip][gNumOfBoostTris], &objTrans, var_f2, temp_f0,
                                  objBoostRacer->unk72 << 12, objBoostType->tex);
                    gBoostEffectObjects[racerIndex]->properties.boost.indexes =
                        (racerIndex << 28) | (gNumOfBoostVerts << 14) | gNumOfBoostTris;
                    gNumOfBoostVerts += BOOST_VERT_COUNT;
                    gNumOfBoostTris += BOOST_TRI_COUNT;
                }
                gBoostEffectObjects[racerIndex]->properties.boost.obj = racerObj;
                gBoostEffectObjects[racerIndex]->trans.x_position = 0.0f;
                gBoostEffectObjects[racerIndex]->trans.y_position = 0.0f;
                gBoostEffectObjects[racerIndex]->trans.z_position = 0.0f;
                sp74.x = boostData->position.x;
                sp74.y = boostData->position.y;
                sp74.z = boostData->position.z;
                vec3f_rotate(&racerObj->trans.rotation, &sp74);
                ignore_bounds_check();
                move_object(gBoostEffectObjects[racerIndex], racerObj->trans.x_position + sp74.f[0],
                            racerObj->trans.y_position + sp74.f[1], racerObj->trans.z_position + sp74.f[2]);
            }
            if (arg4 != FALSE) {
                D_8011B068[racerIndex] = FALSE;
            }
        }
    }
}

/**
 * Updates the racer FX object states.
 * This includes the shield wobble timer, and the texture frames for the magnet and shield.
 */
void racerfx_update(s32 updateRate) {
    s32 i;
    Object_Boost *boostObj;
    s32 temp;
    Object_Boost *asset20;
    f32 updateRateF;
    Object_Racer *racer;

    gBoostVertFlip = 1 - gBoostVertFlip;
    gNumOfBoostVerts = 0;
    gNumOfBoostTris = 0;
    asset20 = (Object_Boost *) get_misc_asset(ASSET_MISC_20);
    gBoostObjOverrideID = 9;
    for (i = 0; i < NUMBER_OF_CHARACTERS; i++) {
        if (D_8011B068[i] && gBoostEffectObjects[i] != NULL) {
            gBoostEffectObjects[i]->properties.common.unk0 = 0;
        }
        D_8011B068[i] = TRUE;
    }
    for (i = 0; i < gNumRacers; i++) {
        updateRateF = (f32) updateRate;
        if (osTvType == OS_TV_TYPE_PAL) {
            updateRateF *= 1.2f;
        }
        racer = (*gRacers)[i]->racer;
        boostObj = &asset20[racer->racerIndex];
        if (racer->shieldTimer != 0) {
            gShieldSineTime[racer->racerIndex] += updateRate;
        }
        boostObj->unk72 += updateRate;
        if (racer->boostTimer != 0) {
            boostObj->unk73 = 20;
            if (boostObj->unk70 == 0) {
                boostObj->unk74 += updateRateF * 0.25f;
                updateRateF = 0.0f;
                if (boostObj->unk74 > 2.4f) {
                    boostObj->unk74 = 4.8f - boostObj->unk74;
                    boostObj->unk70 = 1;
                }
            }
            if (boostObj->unk70 == 1) {
                boostObj->unk74 -= updateRateF * 0.25f;
                updateRateF = 0.0f;
                if (boostObj->unk74 < 1.0f) {
                    boostObj->unk70 = 2;
                    boostObj->unk74 = 1.0f - boostObj->unk74;
                }
            }
            if (boostObj->unk70 == 2) {
                if (boostObj->unk74 < 1.0f) {
                    boostObj->unk74 += updateRateF * 0.125f;
                    if (boostObj->unk74 > 1.0f) {
                        boostObj->unk74 = 1.0f;
                    }
                }
            }
        } else {
            if (boostObj->unk73 > 0) {
                boostObj->unk73 -= updateRate;
            } else {
                if (boostObj->unk70 == 2) {
                    boostObj->unk74 -= updateRateF * 0.05f;
                    updateRateF = 0.0f;
                    if (boostObj->unk74 < 0.0f) {
                        boostObj->unk70 = 0;
                        boostObj->unk74 += 1.0f;
                    }
                }
                if (boostObj->unk70 < 2) {
                    boostObj->unk74 -= (updateRateF * 0.1f);
                    if (boostObj->unk74 < 0.0f) {
                        boostObj->unk74 = 0.0f;
                    }
                    boostObj->unk70 = 0;
                }
            }
        }
        if ((boostObj->unk70 > 0) || (boostObj->unk74 > 0.0f)) {
            func_8000B750((*gRacers)[i], racer->racerIndex, racer->vehicleIDPrev, racer->boostType, 0);
        }
        temp = racer->racerIndex;
        gRacerFXData[temp].unk1 += updateRate;
        gRacerFXData[temp].unk2 += updateRate;
        if (racer->magnetTimer != 0) {
            if (gRacerFXData[temp].unk3 + (updateRate << 2) < 32) {
                gRacerFXData[temp].unk3 += (updateRate << 2);
            } else {
                gRacerFXData[temp].unk3 = 32;
            }
        } else {
            if (gRacerFXData[temp].unk3 - updateRate > 0) {
                gRacerFXData[temp].unk3 -= updateRate;
            } else {
                gRacerFXData[temp].unk3 = 0;
            }
        }
    }
    if (gMagnetEffectObject != NULL) {
        obj_tex_animate(gMagnetEffectObject, updateRate);
    }
}

/**
 * Returns the boost object with the given ID.
 * Returns a specific ID if the arg passed is BOOST_DEFAULT.
 */
Object *racerfx_get_boost(s32 boostID) {
    if (boostID == BOOST_DEFAULT) {
        boostID = gBoostObjOverrideID;
    }
    if (boostID < 0 || boostID >= NUMBER_OF_CHARACTERS) {
        return NULL;
    }
    return gBoostEffectObjects[boostID];
}

/**
 * Allocate memory for objects and object related systems.
 * This includes the objects themselves, particles, and all of the pointer lists for tracking objects.
 */
void allocate_object_pools(void) {
    s32 i;

    set_world_shading(0.67f, 0.33f, 0, -0x2000, 0);
    gObjectMemoryPool = (Object *) mempool_new_sub(OBJECT_POOL_SIZE, OBJECT_SLOT_COUNT);
    gParticlePtrList = mempool_alloc_safe(sizeof(uintptr_t) * 200, COLOUR_TAG_BLUE);
    gCollisionObjects = mempool_alloc_safe(sizeof(uintptr_t) * OBJECT_COLLISION_COUNT, COLOUR_TAG_BLUE);
    D_8011AE74 = mempool_alloc_safe(sizeof(uintptr_t) * 128, COLOUR_TAG_BLUE);
    gTrackCheckpoints = mempool_alloc_safe(sizeof(CheckpointNode) * MAX_CHECKPOINTS, COLOUR_TAG_BLUE);
    gCameraObjList = mempool_alloc_safe(sizeof(uintptr_t *) * CAMCONTROL_COUNT, COLOUR_TAG_BLUE);
    gRacers = mempool_alloc_safe(sizeof(uintptr_t) * 10, COLOUR_TAG_BLUE);
    gRacersByPort = mempool_alloc_safe(sizeof(uintptr_t) * 10, COLOUR_TAG_BLUE);
    gRacersByPosition = mempool_alloc_safe(sizeof(uintptr_t) * 10, COLOUR_TAG_BLUE);
    gAINodes = mempool_alloc_safe(sizeof(uintptr_t) * AINODE_COUNT, COLOUR_TAG_BLUE);
    gDrawbridgeTimers = mempool_alloc_safe(8, COLOUR_TAG_BLUE);
    D_8011AFF4 = mempool_alloc_safe(sizeof(unk800179D0) * 16, COLOUR_TAG_BLUE);
    gAssetsLvlObjTranslationTable = (s16 *) asset_table_load(ASSET_LEVEL_OBJECT_TRANSLATION_TABLE);
    gAssetsLvlObjTranslationTableLength = (asset_table_size(ASSET_LEVEL_OBJECT_TRANSLATION_TABLE) >> 1) - 1;
    while (gAssetsLvlObjTranslationTable[gAssetsLvlObjTranslationTableLength] == 0) {
        gAssetsLvlObjTranslationTableLength--;
    }
    gSpawnObjectHeap = mempool_alloc_safe(OBJECT_BLUEPRINT_SIZE, COLOUR_TAG_BLUE);
    gAssetsObjectHeadersTable = (s32 *) asset_table_load(ASSET_OBJECT_HEADERS_TABLE);
    gAssetsObjectHeadersTableLength = 0;
    while (-1 != gAssetsObjectHeadersTable[gAssetsObjectHeadersTableLength]) {
        gAssetsObjectHeadersTableLength++;
    }
    gAssetsObjectHeadersTableLength--;
    gLoadedObjectHeaders = mempool_alloc_safe(gAssetsObjectHeadersTableLength * 4, COLOUR_TAG_WHITE);
    gObjectHeaderReferences = mempool_alloc_safe(gAssetsObjectHeadersTableLength, COLOUR_TAG_WHITE);

    for (i = 0; i < gAssetsObjectHeadersTableLength; i++) {
        (*gObjectHeaderReferences)[i] = 0;
    }

    gAssetsMiscSection = (s32 *) asset_table_load(ASSET_MISC);
    gAssetsMiscTable = (s32 *) asset_table_load(ASSET_MISC_TABLE);
    gAssetsMiscTableLength = 0;
    while (-1 != gAssetsMiscTable[gAssetsMiscTableLength]) {
        gAssetsMiscTableLength++;
    }

    decrypt_magic_codes(
        &gAssetsMiscSection[gAssetsMiscTable[ASSET_MISC_MAGIC_CODES]],
        (gAssetsMiscTable[ASSET_MISC_TITLE_SCREEN_DEMO_IDS] - gAssetsMiscTable[ASSET_MISC_MAGIC_CODES]) *
            sizeof(s32 *));
    gObjPtrList = mempool_alloc_safe(sizeof(uintptr_t) * OBJECT_SLOT_COUNT, COLOUR_TAG_BLUE);
    gFirstTimeFinish = 0;
    gTimeTrialEnabled = 0;
    gIsTimeTrial = FALSE;
    gObjectUpdateRateF = 2.0f;
    clear_object_pointers();
}

// Decrypts cheats
void decrypt_magic_codes(s32 *data, s32 length) {
    s32 i;
    s32 j;
    u8 *ptr = (u8 *) data;
    u8 temp[4];

    for (i = 0; i < (length >> 2); i++) {
        // Swap bits according to the following pattern:
        // AABBCCDD EEFFGGHH IIJJKKLL MMNNOOPP -> AAEEIIMM BBFFJJNN CCGGKKOO DDHHLLPP
        // clang-format off
        temp[0] = ((ptr[0] & 0xC0)     ) |
                  ((ptr[1] & 0xC0) >> 2) |
                  ((ptr[2] & 0xC0) >> 4) |
                  ((ptr[3] & 0xC0) >> 6);
        temp[1] = ((ptr[0] & 0x30) << 2) |
                  ((ptr[1] & 0x30)     ) |
                  ((ptr[2] & 0x30) >> 2) |
                  ((ptr[3] & 0x30) >> 4);
        temp[2] = ((ptr[0] & 0x0C) << 4) |
                  ((ptr[1] & 0x0C) << 2) |
                  ((ptr[2] & 0x0C)     ) |
                  ((ptr[3] & 0x0C) >> 2);
        temp[3] = ((ptr[0] & 0x03) << 6) |
                  ((ptr[1] & 0x03) << 4) |
                  ((ptr[2] & 0x03) << 2) |
                  ((ptr[3] & 0x03)     );
        // clang-format on

        // Swap the odd and even bits
        for (j = 0; j < 4; j++) {
            *ptr++ = (((temp[j] & 0xAA) >> 1) | ((temp[j] & 0x55) << 1));
        }
    }
}

/**
 * Set all object counters and headers to zero, effectively telling the game there are no objects currently in the
 * scene.
 */
void clear_object_pointers(void) {
    s32 i;

    D_8011AD26 = TRUE;
    D_8011AD5C = 0;
    D_8011AD60 = 0;
    gFreeListCount = 0;
    gCollisionObjectCount = 0;
    gNumberOfMainCheckpoints = 0;
    gNumberOfTotalCheckpoints = 0;
    gNumRacers = 0;
    D_8011AE78 = 0;
    D_8011AD21 = 0;
    D_8011AD22[0] = 0;
    D_8011AD22[1] = 0;

    for (i = 0; i < AINODE_COUNT; i++) {
        (*gAINodes)[i] = NULL;
    }
    for (i = 0; i < 8; i++) {
        (*gDrawbridgeTimers)[i] = 0;
    }
    for (i = 0; i < 16; i++) {
        D_8011AFF4[i].unk0 = 0;
    }

    gAINodeTail[0] = 0xFF;
    gAINodeTail[1] = 0xFF;
    gObjectCount = 0;
    gObjectListStart = 0;
    gParticleCount = 0;
    D_8011AE88 = 0;
    D_8011ADD4 = 0;
    gCutsceneID = 0;
    D_8011AE7E = TRUE;
    gFirstActiveObjectId = 0;
    gTransformTimer = 0;
    gIsTajChallenge = FALSE;
    gTajRaceInit = 0;
    D_8011AF60 = NULL;
    D_8011AE00 = 0;
    D_8011AE01 = TRUE;
    D_8011AD53 = 0;
    gOverrideDoors = FALSE;
}

/**
 * Clear all objects from memory. Also clear rumble.
 * Swap lead player in adventure two if the other player finished ahead of the lead player.
 */
void free_all_objects(void) {
    s32 i, len;
    timetrial_free_staff_ghost();
    gIsP2LeadPlayer = FALSE;
    if (gRollingDemo) {
        rumble_init(TRUE);
    }
    gRollingDemo = FALSE;
    if (gSwapLeadPlayer && is_in_two_player_adventure()) {
        gSwapLeadPlayer = FALSE;
        swap_lead_player();
    }
    gParticlePtrList_flush();
    len = gObjectCount;
    for (i = 0; i < len; i++) {
        obj_destroy(gObjPtrList[i], 1);
    }
    gFreeListCount = 0;
    gObjectCount = 0;
    gObjectListStart = 0;
    clear_object_pointers();
    mempool_free((void *) gObjectMap[0]);
    mempool_free((void *) gObjectMap[1]);
}

/**
 * Set the object's header.
 * Search if the intended header is already loaded and use that.
 * Otherwise, allocate space and load it into ROM and set it to that.
 */
ObjectHeader *load_object_header(s32 index) {
    s32 assetOffset;
    s32 size;
    ObjectHeader *address;

    if ((*gObjectHeaderReferences)[index] != 0) {
        (*gObjectHeaderReferences)[index]++;
        return (*gLoadedObjectHeaders)[index];
    }
    assetOffset = gAssetsObjectHeadersTable[index];
    size = gAssetsObjectHeadersTable[index + 1] - assetOffset;
    address = mempool_alloc_pool((MemoryPoolSlot *) gObjectMemoryPool, size);
    if (address != NULL) {
        asset_load(ASSET_OBJECTS, (u32) address, assetOffset, size);
        address->unk24 = (ObjectHeader24 *) ((uintptr_t) address + (uintptr_t) address->unk24);
        address->objectParticles =
            (ObjHeaderParticleEntry *) ((uintptr_t) address + (uintptr_t) address->objectParticles);
        address->vehiclePartIds = (s32 *) ((uintptr_t) address + (uintptr_t) address->vehiclePartIds);
        address->vehiclePartIndices = (s8 *) ((uintptr_t) address + (uintptr_t) address->vehiclePartIndices);
        address->modelIds = (s32 *) ((uintptr_t) address + (uintptr_t) address->modelIds);
        (*gLoadedObjectHeaders)[index] = address;
        (*gObjectHeaderReferences)[index] = 1;
    } else {
        return NULL;
    }
    return address;
}

/**
 * Remove this object from the loaded header's references.
 * If the reference number is zero, free the header.
 */
void try_free_object_header(s32 index) {
    if ((*gObjectHeaderReferences)[index] != 0) {
        (*gObjectHeaderReferences)[index]--;
        if ((*gObjectHeaderReferences)[index] == 0) {
            mempool_free((void *) (*gLoadedObjectHeaders)[index]);
        }
    }
}

/**
 * Converts the passed value into an accurate countdown value based on the systems region.
 * Since PAL runs at 50Hz, it therefore will reduce the timer to 5/6 to match, keeping
 * it consistent with non PAL timers, running 60Hz.
 * Official Name: objTvTimes
 */
s32 normalise_time(s32 timer) {
    if (osTvType != OS_TV_TYPE_PAL || timer < 0) {
        return timer;
    } else {
        return (timer * 5) / 6;
    }
}

/**
 * Load the object map into RAM, then start spawning objects into the world.
 * Also decides whether this race type should be for silver coins or not.
 */
void track_spawn_objects(s32 mapID, s32 index) {
    s32 assetSize;
    Settings *settings;
    s32 i;
    s32 *mem;
    s32 var_s0;
    u32 assetOffset;
    u32 *objMapTable;
    UNUSED s32 pad;
    u8 *compressedAsset;
    s32 temp_t3;

    settings = get_settings();
    assetOffset = settings->bosses | 0x820; // 0x820 = Wizpig 2 and some unknown 0x800 boss bit
    gIsSilverCoinRace = ((settings->courseFlagsPtr[settings->courseId] & RACE_CLEARED_SILVER_COINS) == FALSE) &&
                        (((1 << settings->worldId) & assetOffset) != 0);

    if ((settings->courseFlagsPtr[settings->courseId] & RACE_CLEARED) == FALSE) {
        gIsSilverCoinRace = FALSE;
    }
    if (is_in_tracks_mode()) {
        gIsSilverCoinRace = FALSE;
    }
    if (level_type()) {
        gIsSilverCoinRace = FALSE;
    }

    D_8011AD3E = 0;
    mem = mempool_alloc_safe(OBJECT_MAP_SIZE, COLOUR_TAG_BLUE);
    gObjectMap[index] = mem;
    gObjectMapSpawnList[index] = (u8 *) (gObjectMap[index] + sizeof(uintptr_t));
    gObjectMapSize[index] = NULL;
    gObjectMapID[index] = mapID;
    objMapTable = (u32 *) asset_table_load(ASSET_LEVEL_OBJECT_MAPS_TABLE);
    for (i = 0; objMapTable[i] != 0xFFFFFFFF; i++) {}
    i--;
    if (mapID >= i) {
        mapID = 0;
    }
    assetOffset = objMapTable[mapID];
    assetSize = objMapTable[mapID + 1] - assetOffset;

    if (assetSize != 0) {
        compressedAsset = (u8 *) mem;
        compressedAsset =
            ((compressedAsset + gzip_size_uncompressed(ASSET_LEVEL_OBJECT_MAPS, assetOffset)) - (0, assetSize)) + 0x20;
        asset_load(ASSET_LEVEL_OBJECT_MAPS, (u32) compressedAsset, assetOffset, assetSize);
        gzip_inflate(compressedAsset, (u8 *) mem);
        mempool_free(objMapTable);
        gObjectMapSpawnList[index] = (u8 *) (gObjectMap[index] + sizeof(uintptr_t));
        gObjectMapSize[index] = *mem;
        gObjectMapIndex = index;
        for (var_s0 = 0; var_s0 < gObjectMapSize[index]; var_s0 += temp_t3) {
            spawn_object((LevelObjectEntryCommon *) gObjectMapSpawnList[index], OBJECT_SPAWN_UNK01);
            gObjectMapSpawnList[index] = &gObjectMapSpawnList[index][temp_t3 = gObjectMapSpawnList[index][1] & 0x3F];
        }
        gObjectMapSpawnList[index] = (u8 *) (gObjectMap[index] + sizeof(uintptr_t));
        gCollisionObjectCount = 0;
        gNumFinishedRacers = 1;
        if (gPathUpdateOff == FALSE) {
            gParticlePtrList_flush();
            checkpoint_update_all();
            spectate_update();
            func_8001E93C();
        }
        gPathUpdateOff = TRUE;
    }
}

// Reset all values of D_8011AE08 to NULL
void func_8000CBC0(void) {
    s32 i; // Required to be one line to match
    // clang-format off
    for (i = 0; i < ARRAY_COUNT(D_8011AE08); i++) { D_8011AE08[i] = NULL; }
    // clang-format on
}

// Set the object value for the given index if it's not already set
void func_8000CBF0(Object *obj, s32 index) {
    if (D_8011AE08[index] == NULL) {
        D_8011AE08[index] = obj;
    } else {
        if (D_8011AE08[index]) {}
    }
}

// Set the next available value in D_8011AE08, and return it's index value. -1 if it's not set.
s32 func_8000CC20(Object *obj) {
    s32 i;
    s32 NextFreeIndex;

    NextFreeIndex = -1;
    for (i = 0; i < ARRAY_COUNT(D_8011AE08); i++) {
        if (D_8011AE08[i] == NULL) {
            NextFreeIndex = i;
            i = ARRAY_COUNT(D_8011AE08); // Why not just break?
        }
    }
    if (NextFreeIndex != -1) {
        D_8011AE08[NextFreeIndex] = obj;
    }
    return NextFreeIndex;
}

/**
 * Takes the level header and decides which race type to activate.
 * Sets up the racer spawning. Initialising vehicle types, racer count, then
 * spawning them into the world in their assigned order.
 */
void track_setup_racers(Vehicle vehicle, u32 entranceID, s32 playerCount) {
    LevelObjectEntry_Racer *racerEntry;
    Object *curObj;
    s32 numPlayers;
    Object *racerObj;
    LevelObjectEntry *objEntry;
    enum GameMode gameMode;
    Object_Racer *curRacer;
    s32 cutsceneID;
    s32 spawnObjFlags;
    s8 *miscAsset16;
    s8 sp127;
    u8 spawnedObjCount;
    s16 objectID;
    s8 racerActive[8];
    s8 racerIDs[8];
    s32 spawnX[8];
    s32 spawnY[8];
    s32 spawnZ[8];
    s32 spawnAngle[8];
    Settings *settings;
    s32 j;
    s32 var_s4;
    s32 i;
    s32 k;
    u8 raceType;
    LevelHeader *levelHeader;
    Camera *cutsceneCameraSegment;

    D_8011AD20 = FALSE;
    gEventCountdown = 0;
    gFirstTimeFinish = FALSE;
    gNumRacers = 0;
    D_8011AF00 = 0;
    set_taj_status(TAJ_WANDER);
    levelHeader = level_header();
    raceType = levelHeader->race_type;
    if (raceType == RACETYPE_CUTSCENE_1 || raceType == RACETYPE_CUTSCENE_2) {
        return;
    }
    if (raceType == RACETYPE_BOSS || raceType & RACETYPE_CHALLENGE) {
        gIsTimeTrial = FALSE;
        gTimeTrialEnabled = FALSE;
    }
    cutsceneID = -1;
    if (is_time_trial_enabled() && raceType == RACETYPE_DEFAULT) {
        cutsceneCameraSegment = cam_get_cameras();
        cutsceneID = cutsceneCameraSegment->zoom;
        cutsceneCameraSegment->zoom = 1;
    }
    gameMode = get_game_mode();
    settings = get_settings();
    miscAsset16 = (s8 *) get_misc_asset(ASSET_MISC_3);
    gPrevTimeTrialVehicle = D_8011ADC5;
    if (!(settings->courseFlagsPtr[settings->courseId] &
          RACE_VISITED)) { // Check if the player has not visited the course yet.
        settings->courseFlagsPtr[settings->courseId] |= RACE_VISITED;
        D_8011AF00 = 2;
    }
    if (raceType != RACETYPE_DEFAULT) {
        D_8011AF00 = 2;
    }
    for (j = 0; j < ARRAY_COUNT(spawnZ); j++) {
        spawnX[j] = 0;
        spawnY[j] = 0;
        spawnZ[j] = 0;
    }
    for (j = 0; j < gObjectCount; j++) {
        racerObj = gObjPtrList[j];
        if (!(racerObj->trans.flags & OBJ_FLAGS_PARTICLE)) {
            if (racerObj->behaviorId == BHV_SETUP_POINT) {
                if (entranceID == racerObj->properties.setupPoint.entranceID) {
                    if (racerObj->properties.setupPoint.racerIndex < 8) {
                        spawnX[racerObj->properties.setupPoint.racerIndex] = racerObj->trans.x_position;
                        spawnY[racerObj->properties.setupPoint.racerIndex] = racerObj->trans.y_position;
                        spawnZ[racerObj->properties.setupPoint.racerIndex] = racerObj->trans.z_position;
                        spawnAngle[racerObj->properties.setupPoint.racerIndex] = racerObj->trans.rotation.y_rotation;
                    }

                    objEntry = racerObj->level_entry;
                    if (objEntry->setupPoint.vehicle != -1) {
                        vehicle = objEntry->setupPoint.vehicle;
                    }
                }
            }
        }
    }
    D_8011ADC5 = vehicle; // UB if all setup points don't have an assigned vehicle ID.
    gPrevTimeTrialVehicle = D_8011ADC5;
    numPlayers = playerCount + 1;
    gNumRacers = 8;
    gTwoActivePlayersInAdventure = FALSE;
    if (race_is_adventure_2P()) {
        numPlayers = 2;
        gTwoActivePlayersInAdventure = TRUE;
        set_scene_viewport_num(VIEWPORT_LAYOUT_2_PLAYERS);
    }
    if (raceType == RACETYPE_HUBWORLD) {
        gTimeTrialEnabled = 0;
    }

    gIsTimeTrial = gTimeTrialEnabled;
    if (gIsTimeTrial) {
        raceType = RACETYPE_HUBWORLD; // ???
    }
    if (raceType == RACETYPE_HUBWORLD || numPlayers >= 3) {
        gNumRacers = numPlayers;
        if (level_properties_get() == 0 && D_800DC708 != 0) {
            spawnAngle[0] += D_800DC708;
            D_800DC708 = 0;
        }
    } else if (numPlayers == 2) {
        gNumRacers = get_multiplayer_racer_count();
    }

    if (raceType & RACETYPE_CHALLENGE) {
        gNumRacers = 4;
    }
    D_8011AD3C = 0;
    if (raceType == RACETYPE_BOSS) {
        gNumRacers = 2;
        numPlayers = 1;
        D_8011AD3C = 1;
    }
    gRollingDemo = FALSE;
    if (gameMode == GAMEMODE_MENU && raceType == RACETYPE_DEFAULT) {
        gNumRacers = 6;
        gRollingDemo = TRUE;
        D_8011AD3C = 2;
    }

    for (i = 0; i < gNumRacers; i++) {
        racerActive[i] = FALSE;
    }

    spawnedObjCount = 0;
    // Mark active for human players.
    for (i = 0; i < numPlayers; i++) {
        if (settings->racers[i].starting_position < gNumRacers) {
            if (racerActive[settings->racers[i].starting_position] == FALSE) {
                racerActive[settings->racers[i].starting_position] = TRUE;
                continue;
            }
        }
        racerIDs[spawnedObjCount++] = i;
    }

    // Mark active for computer players.
    for (i = numPlayers; i < gNumRacers; i++) {
        if (settings->racers[i].starting_position < gNumRacers) {
            if (racerActive[settings->racers[i].starting_position] == FALSE) {
                racerActive[settings->racers[i].starting_position] = TRUE;
                continue;
            }
        }
        racerIDs[spawnedObjCount++] = i;
    }

    // Assign spawn locations for active racers.
    for (i = 0; i < spawnedObjCount; i++) {
        for (j = 0; j < gNumRacers; j++) {
            if (racerActive[j] == FALSE) {
                racerActive[j] = TRUE;
                settings->racers[racerIDs[i]].starting_position = j;
                j = gNumRacers; // Break
            }
        }
    }
    racerEntry = mempool_alloc_safe(sizeof(LevelObjectEntry_Racer), COLOUR_TAG_YELLOW);
    racerEntry->angleY = 0;
    racerEntry->angleX = 0;
    racerEntry->angleZ = 0;
    if (levelHeader->vehicle == VEHICLE_CAR) {
        gIsNonCarRacers = FALSE;
    } else {
        gIsNonCarRacers = TRUE;
    }
    D_8011AD24[1] = levelHeader->bossRaceID;
    sp127 = -1;
    for (i = 0; i < gNumRacers; i++) {
        if (raceType != RACETYPE_HUBWORLD && !(raceType & RACETYPE_CHALLENGE) && D_8011AD3C == 0) {
            j = 0;
            var_s4 = j;
            do {
                if (i == settings->racers[j].starting_position) {
                    var_s4 = j;
                    j = gNumRacers;
                }
                j++;
            } while (j < gNumRacers);
        } else {
            var_s4 = i;
        }
        racerEntry->playerIndex = var_s4 < numPlayers ? var_s4 : 4;
        if (raceType != RACETYPE_HUBWORLD || racerEntry->playerIndex != 4) {
            if (D_8011AD3C == 1) {
                if (i == 0) {
                    vehicle = gBossVehicles[D_8011AD24[1]].playerVehicle;
                } else {
                    vehicle = gBossVehicles[D_8011AD24[1]].bossVehicle;
                }
            } else if (D_8011AD3C == 2) {
                vehicle = levelHeader->vehicle;
            } else {
                if (racerEntry->playerIndex == 4 || race_is_adventure_2P()) {
                    vehicle = get_player_selected_vehicle(PLAYER_ONE);
                } else if (numPlayers >= 2) {
                    vehicle = get_player_selected_vehicle(racerEntry->playerIndex);
                }
            }

            // Are these assignments correct? Seems weird.
            if (D_8011AD3C == 2) {
                objectID = gRacerObjectTable[D_800DC840[i] + (vehicle * NUM_CHARACTERS)];
            } else if (vehicle < 5) {
                objectID = gRacerObjectTable[(settings->racers[var_s4].character) + (vehicle * NUM_CHARACTERS)];
            } else {
                objectID = gRacerObjectTable[vehicle + 45];
            }

            racerEntry->common.objectID = objectID;
            racerEntry->common.size = ((objectID & 0x100) >> 1) | 0x10;
            racerEntry->common.x = spawnX[i];
            racerEntry->common.y = spawnY[i];
            racerEntry->common.z = spawnZ[i];
            racerEntry->angleY = spawnAngle[i];
            if (racerEntry->playerIndex == 4) {
                model_anim_offset(1);
            }

            spawnObjFlags = OBJECT_BEHAVIOUR_SHADED;
            if (racerEntry->playerIndex == 4) {
                spawnObjFlags = OBJECT_BEHAVIOUR_SHADED | OBJECT_BEHAVIOUR_WATER_EFFECT;
                // @fake but required for the | OBJECT_BEHAVIOUR_ANIMATION below to work
                if (1) {
                    spawnObjFlags |= 0;
                }
                if (numPlayers >= 2) {
                    spawnObjFlags |= OBJECT_BEHAVIOUR_ANIMATION;
                }
            }
            if (racerEntry->playerIndex != 4) {
                if (numPlayers == 1) {
                    spawnObjFlags |= OBJECT_BEHAVIOUR_INTERACTIVE;
                }
            }
            if (vehicle >= VEHICLE_BOSSES) {
                spawnObjFlags = OBJECT_BEHAVIOUR_SHADED;
                model_anim_offset(0);
            }
            racerObj = spawn_object((LevelObjectEntryCommon *) racerEntry, spawnObjFlags);
            racerObj->trans.rotation.y_rotation = spawnAngle[i];
            (*gRacers)[i] = racerObj;
            gRacersByPosition[i] = racerObj;
            gRacersByPort[var_s4] = racerObj;
            curRacer = racerObj->racer;
            racerObj->level_entry = NULL;
            curRacer->vehicleID = vehicle;
            curRacer->vehicleIDPrev = vehicle;
            if (sp127 != -1 && sp127 != (s32) vehicle) {
                D_8011AD20 = TRUE;
            }
            sp127 = vehicle;
            if (curRacer->vehicleID == VEHICLE_PLANE || curRacer->vehicleID == VEHICLE_SMOKEY ||
                curRacer->vehicleID == VEHICLE_PTERODACTYL) {
                gIsNonCarRacers = TRUE;
            }
            curRacer->unk1CB = vehicle;
            if (curRacer->unk1CB < VEHICLE_CAR || curRacer->unk1CB > VEHICLE_PLANE) {
                curRacer->unk1CB = 0;
            }
            curRacer->racerIndex = var_s4;
            curRacer->characterId = settings->racers[var_s4].character;
            if (D_8011AD3C == 2) {
                curRacer->characterId = D_800DC840[i];
            } else {
                curRacer->characterId = settings->racers[var_s4].character;
            }
            if (raceType == RACETYPE_CHALLENGE_BATTLE) {
                curRacer->bananas = 8;
            } else {
                curRacer->bananas = 0;
            }
            if (get_filtered_cheats() & CHEAT_START_WITH_10_BANANAS && !(raceType & RACETYPE_CHALLENGE)) {
                if (curRacer->playerIndex != PLAYER_COMPUTER) {
                    curRacer->bananas = 10;
                }
            }
            if ((gameMode != GAMEMODE_MENU || D_8011AD3C == 2) && vehicle < VEHICLE_BOSSES) {
                curRacer->vehicleSound = racer_sound_init(curRacer->characterId, curRacer->vehicleID);
            } else {
                curRacer->vehicleSound = NULL;
            }

            racerObj->interactObj->pushForce = miscAsset16[curRacer->characterId] + 1;
            switch (curRacer->vehicleID) {
                case VEHICLE_TRICKY:
                case VEHICLE_BLUEY:
                case VEHICLE_SMOKEY:
                case VEHICLE_PTERODACTYL:
                case VEHICLE_SNOWBALL:
                case VEHICLE_BUBBLER:
                case VEHICLE_WIZPIG:
                case VEHICLE_ROCKET:
                    racer_special_init(racerObj, curRacer);
                    break;
                default:
                    break;
            }
        }
    }
    var_s4 = 0;
    if (raceType != RACETYPE_BOSS) {
        D_8011AD3C = 0;
    }
    if (D_8011AD3C != 0) {
        D_8011AD20 = FALSE;
    }
    // Remove unwanted objects depending on race type.
    if (get_game_mode() == GAMEMODE_INGAME) {
        for (j = 0; j < gObjectCount; j++) {
            racerObj = gObjPtrList[j];
            i = racerObj->header->flags;
            if (i & OBJECT_HEADER_NO_TIME_TRIAL && gIsTimeTrial) {
                free_object(racerObj);
            } else if (i & OBJECT_HEADER_NO_MULTIPLATER && numPlayers >= 2) {
                free_object(racerObj);
            }
        }
    }
    gGhostObjStaff = NULL;
    timetrial_free_staff_ghost();
    gTimeTrialContPak = -1;
    if (gIsTimeTrial && numPlayers == 1) {
        timetrial_reset_player_ghost();
        gTimeTrialContPak = timetrial_init_player_ghost(PLAYER_ONE);
        gHasGhostToSave = 0;
        if (gTimeTrialVehicle >= VEHICLE_BOSSES) {
            gTimeTrialVehicle = VEHICLE_CAR;
        }
        // Spawn player ghost.
        if (timetrial_valid_player_ghost()) {
            objectID = gRacerObjectTable[gTimeTrialCharacter + (gTimeTrialVehicle * NUM_CHARACTERS)];
            racerEntry->common.size = ((objectID & 0x100) >> 1) | 0x10;
            racerEntry->common.objectID = objectID;
            racerEntry->common.x = spawnX[0];
            racerEntry->common.y = spawnY[0];
            racerEntry->common.z = spawnZ[0];
            racerEntry->angleY = spawnAngle[0];
            curObj = spawn_object((LevelObjectEntryCommon *) racerEntry, 1);
            curObj->level_entry = NULL;
            curObj->behaviorId = BHV_TIMETRIAL_GHOST;
            curObj->shadow->scale = 0.01f;
            curObj->interactObj->flags = INTERACT_FLAGS_NONE;
            gGhostObjPlayer = curObj;
            curRacer = gGhostObjPlayer->racer;
            curRacer->transparency = 96;
        }
        // Spawn staff ghost
        if (timetrial_init_staff_ghost(level_id())) {
            objectID = gRacerObjectTable[(gMapDefaultVehicle * NUM_CHARACTERS) + 8];

            racerEntry->common.size = ((objectID & 0x100) >> 1) | 0x10;
            racerEntry->common.objectID = objectID;
            racerEntry->common.x = spawnX[0];
            racerEntry->common.y = spawnY[0];
            racerEntry->common.z = spawnZ[0];
            racerEntry->angleY = spawnAngle[0];
            curObj = spawn_object((LevelObjectEntryCommon *) racerEntry, 1);
            curObj->level_entry = NULL;
            curObj->behaviorId = BHV_TIMETRIAL_GHOST;
            curObj->shadow->scale = 0.01f;
            curObj->interactObj->flags = INTERACT_FLAGS_NONE;
            gGhostObjStaff = curObj;
            curRacer = gGhostObjStaff->racer;
            curRacer->transparency = 96;
        }
    }

    for (j = 0, gEventCountdown = 100; j < gNumRacers; j++) {
        racerObj = (*gRacers)[j];
        curRacer = racerObj->racer;
        for (k = 0; k < 10; k++) {
            update_player_racer(racerObj, LOGIC_30FPS); // Settle racers.
        }
        if (curRacer->playerIndex == PLAYER_COMPUTER) {
            var_s4++;
            var_s4 &= 1;
            for (k = 0; k < racerObj->header->numberOfModelIds; k++) {
                if (racerObj->modelInstances[k] != NULL) {
                    if (racerObj->modelInstances[k]->animUpdateTimer != 0) {
                        racerObj->modelInstances[k]->animUpdateTimer = (var_s4 * 2);
                    }
                }
            }
        } else {
            // curRacer is a human racer.
            for (k = 0; k < racerObj->header->numberOfModelIds; k++) {
                if (racerObj->modelInstances[k] != NULL) {
                    if (racerObj->modelInstances[k]->animUpdateTimer != 0) {
                        racerObj->modelInstances[k]->animUpdateTimer = 0;
                    }
                }
            }
        }
        // Apply size cheats to racers.
        if (get_filtered_cheats() & CHEAT_BIG_CHARACTERS) {
            racerObj->trans.scale *= 1.4f;
        }
        if (get_filtered_cheats() & CHEAT_SMALL_CHARACTERS) {
            racerObj->trans.scale *= 0.714f;
        }
        curRacer->stretch_height_cap = 1.0f;
        curRacer->stretch_height = 1.0f;
    }
    if (raceType == RACETYPE_DEFAULT || raceType & RACETYPE_CHALLENGE || gIsTimeTrial || D_8011AD3C != 0) {
        gEventCountdown = 80;
    } else {
        gEventCountdown = 0;
    }
    if (raceType == RACETYPE_DEFAULT && (playerCount + 1) == 1 && is_in_adventure_two() == FALSE) {
        if (!race_is_adventure_2P()) {
            for (j = 0; j < 3; j++) {
                racerEntry->common.objectID = ASSET_OBJECT_ID_POSARROW;
                racerEntry->common.size = sizeof(LevelObjectEntryCommon);
                racerEntry->common.x = 0;
                racerEntry->common.y = 0;
                racerEntry->common.z = 0;
                curObj = spawn_object((LevelObjectEntryCommon *) racerEntry, OBJECT_SPAWN_UNK01);
                curObj->properties.common.unk0 = j;
                curObj->level_entry = NULL;
            }
        }
    }
    gRaceEndTimer = 0;
    gRaceFinishTriggered = FALSE;
    set_next_taj_challenge_menu(0);
    if (settings->worldId == WORLD_CENTRAL_AREA) {
        if (is_in_tracks_mode() == FALSE) {
            miscAsset16 = (s8 *) get_misc_asset(ASSET_MISC_16);
            j = 0;

            // settings->balloonsPtr[0] is the total balloon count.
            if (!(settings->tajFlags & TAJ_FLAGS_CAR_CHAL_UNLOCKED) && (settings->balloonsPtr[0] >= miscAsset16[0])) {
                j = 1;
            } else if (!(settings->tajFlags & TAJ_FLAGS_HOVER_CHAL_UNLOCKED) &&
                       (settings->balloonsPtr[0] >= miscAsset16[1])) {
                j = 2;
            } else if (!(settings->tajFlags & TAJ_FLAGS_PLANE_CHAL_UNLOCKED) &&
                       (settings->balloonsPtr[0] >= miscAsset16[2])) {
                j = 3;
            }

            // Taj will teleport straight to the player to initiate a challenge.
            if (j) {
                set_taj_voice_line(SOUND_VOICE_TAJ_CHALLENGE_RACE);
                settings->tajFlags |= 1 << (j + 31);
                set_taj_status(TAJ_TELEPORT);
                set_next_taj_challenge_menu(j);
                safe_mark_write_save_file(get_save_file_index());
            }
        }
    }
    D_8011AD24[0] = TRUE;
    if (cutsceneID >= 0) {
        cutsceneCameraSegment->zoom = cutsceneID;
    }
    // Menu demos will skip straight to the action.
    if (racetype_demo()) {
        rumble_init(FALSE);
        gEventCountdown = 0;
        level_music_start(1.0f);
    }
    //!@bug: Free timer is already 0 when loading levels.
    mempool_free_timer(0);
    mempool_free(racerEntry);
    mempool_free_timer(2);
}

/**
 * Return an error status for the controller pak.
 * Categorises multiple different controller pak messages into one for fewer cases.
 */
s32 get_contpak_error(void) {
    // gTimeTrialContPak is likely an SIDeviceStatus value, but not 100% sure yet.
    switch (gTimeTrialContPak) {
        case CONTROLLER_PAK_NOT_FOUND:
            return CONTPAK_ERROR_MISSING;
        case CONTROLLER_PAK_RUMBLE_PAK_FOUND:
            return CONTPAK_ERROR_NONE;
        case CONTROLLER_PAK_INCONSISTENT:
        case CONTROLLER_PAK_WITH_BAD_ID:
            return CONTPAK_ERROR_DAMAGED;
        case CONTROLLER_PAK_FULL:
        case CONTROLLER_PAK_NO_ROOM_FOR_GHOSTS:
            return CONTPAK_ERROR_FULL;
        case CONTROLLER_PAK_GOOD:
        case CONTROLLER_PAK_CHANGED:
        case CONTROLLER_PAK_SWITCH_TO_RUMBLE:
            return timetrial_ghost_full();
        default:
            return CONTPAK_ERROR_NONE;
    }
}

void instShowBearBar(void) {
    D_800DC708 = 0x8000;
}

s8 func_8000E138(void) {
    return D_8011AD20;
}

/**
 * Returns true if currently in a rolling demo.
 */
s8 racetype_demo(void) {
    return gRollingDemo;
}

/**
 * Returns true if we're in a race started by P2 in adventure mode.
 */
s8 is_race_started_by_player_two(void) {
    if (gTwoActivePlayersInAdventure) {
        return gLeadPlayerIndex;
    } else {
        return FALSE;
    }
}

/**
 * Returns true if P2 is the lead player in adventure mode.
 */
s8 is_player_two_in_control(void) {
    return gIsP2LeadPlayer;
}

/**
 * Swaps the lead player index during 2P adventure mode.
 */
void toggle_lead_player_index(void) {
    gLeadPlayerIndex = 1 - gLeadPlayerIndex;
    gTwoActivePlayersInAdventure = FALSE;
}

/**
 * Resets the lead player index.
 * Official name: fontUseFont (why?)
 */
void reset_lead_player_index(void) {
    gLeadPlayerIndex = 0;
    gTwoActivePlayersInAdventure = FALSE;
}

/**
 * Return true if there exist players piloting planes or hovercraft.
 * Used to determine whether to use certain zippers.
 */
s8 find_non_car_racers(void) {
    return gIsNonCarRacers;
}

/**
 * Return true if the silver coin race mode is active.
 * Used to determine whether to spawn silver coins.
 */
s8 check_if_silver_coin_race(void) {
    return gIsSilverCoinRace;
}

/**
 * Store some things about the racer object then remove it.
 */
void despawn_player_racer(Object *obj, s32 vehicleID) {
    gTransformObject = obj;
    gTransformTimer = 4;
    gOverworldVehicle = vehicleID;
    gTransformPosX = obj->trans.x_position;
    gTransformPosY = obj->trans.y_position;
    gTransformPosZ = obj->trans.z_position;
    gTransformAngleY = obj->trans.rotation.y_rotation;
    free_object(obj);
    gNumRacers = 0;
}

/**
 * Spawn a new racer object and set the initial position and rotation to what was set
 * before the old one was freed.
 */
void transform_player_vehicle(void) {
    Object *player;
    LevelObjectEntry8000E2B4 spawnObj;
    Settings *settings;
    Object_Racer *racer;
    s16 objectID;

    if (gTransformTimer == 0) {
        return;
    }
    gTransformTimer--;
    if (gTransformTimer) {
        return;
    }
    settings = get_settings();
    spawnObj.unkE = 0;
    spawnObj.common.size = 16;
    if (gOverworldVehicle < VEHICLE_BOSSES) {
        objectID =
            ((s16 *) gRacerObjectTable)[settings->racers[PLAYER_ONE].character + gOverworldVehicle * NUM_CHARACTERS];
    } else {
        objectID = gRacerObjectTable[gOverworldVehicle + 45];
    }
    set_level_default_vehicle(gOverworldVehicle);
    spawnObj.common.size |= (objectID & 0x100) >> 1;
    spawnObj.unkA = 0;
    spawnObj.unk8 = 0;
    spawnObj.common.objectID = objectID;
    spawnObj.common.x = gTransformPosX;
    spawnObj.common.y = gTransformPosY;
    spawnObj.common.z = gTransformPosZ;
    spawnObj.unkC = gTransformAngleY;
    set_taj_status(TAJ_DIALOGUE);
    player = spawn_object(&spawnObj.common, OBJECT_SPAWN_NO_LODS | OBJECT_SPAWN_UNK01);
    gNumRacers = 1;
    (*gRacers)[PLAYER_ONE] = player;
    gRacersByPort[PLAYER_ONE] = player;
    *gRacersByPosition = player;
    racer = player->racer;
    racer->vehicleID = gOverworldVehicle;
    racer->vehicleIDPrev = gOverworldVehicle;
    racer->racerIndex = 0;
    racer->characterId = settings->racers[PLAYER_ONE].character;
    racer->playerIndex = 0;
    racer->vehicleSound = 0;
    if (get_filtered_cheats() & CHEAT_BIG_CHARACTERS) {
        player->trans.scale *= 1.4f;
    }
    if (get_filtered_cheats() & CHEAT_SMALL_CHARACTERS) {
        player->trans.scale *= 0.714f;
    }
    player->level_entry = NULL;
    player->trans.rotation.y_rotation = gTransformAngleY;
    player->trans.y_position = gTransformPosY;
}

/**
 * Enables or Disables time trial mode.
 */
void set_time_trial_enabled(s32 status) {
    gTimeTrialEnabled = status;
}

/**
 * Returns the value in gTimeTrialEnabled.
 */
u8 is_time_trial_enabled(void) {
    return gTimeTrialEnabled;
}

/**
 * Returns true if the player is currently performaing a time trial.
 */
u8 is_in_time_trial(void) {
    return gIsTimeTrial;
}

UNUSED void func_8000E4E8(s32 index) {
    s32 *temp_v0;
    s32 i;
    u8 *temp_a1;

    temp_v0 = gObjectMap[index];
    temp_v0[0] = gObjectMapSize[index];
    temp_v0[3] = 0;
    temp_v0[2] = 0;
    temp_v0[1] = 0;
    temp_a1 = &gObjectMapSpawnList[index][gObjectMapSize[index]];

    // The backslash here is needed to match. And no, a for loop doesn't match.
    // clang-format off
    i = 0; \
    while (i < 16) {
        temp_a1[i] = 0;
        i++;
    }
    // clang-format on
}

UNUSED s32 func_8000E558(Object *arg0) {
    s32 temp_v0;
    s32 new_var, new_var2;
    if (arg0->level_entry == NULL) {
        return TRUE;
    }
    temp_v0 = (s32) arg0->level_entry;
    new_var2 = (s32) gObjectMapSpawnList[0];
    if ((temp_v0 >= new_var2) && (((gObjectMapSize[0] * 8) + new_var2) >= temp_v0)) {
        return FALSE;
    }
    new_var = (s32) gObjectMapSpawnList[1];
    // Why even bother with this check?
    if (temp_v0 >= new_var && temp_v0 <= ((gObjectMapSize[1] * 8) + new_var)) {
        return TRUE;
    }
    return TRUE;
}

void func_8000E5EC(LevelObjectEntryCommon *arg0) {
    u8 *src;
    u8 *dst;
    s32 end;
    s32 sp30[2];
    s32 size;
    s32 i;
    s32 pad;
    s32 sp1C;

    size = arg0->size & 0x3F;

    sp30[0] = (s32) gObjectMapSpawnList[0] + gObjectMapSize[0];
    sp30[1] = (s32) gObjectMapSpawnList[1] + gObjectMapSize[1];

    if ((s32) arg0 >= (s32) gObjectMapSpawnList[0] && (s32) arg0 < sp30[0]) {
        sp1C = 0;
    } else if ((s32) arg0 >= (s32) gObjectMapSpawnList[1] && (s32) arg0 < sp30[1]) {
        sp1C = 1;
    }
#ifdef AVOID_UB
    else {
        sp1C = 0;
    }
#endif

    dst = (u8 *) arg0;
    src = (u8 *) ((s32) arg0 + size);
    end = sp30[sp1C];
    if ((u32) src < (u32) end) {
        do {
            *dst++ = *src++;
        } while ((u32) src != (u32) end);
    }
    gObjectMapSize[sp1C] -= size;

    for (i = 0; i < gObjectCount; i++) {
        Object *obj = gObjPtrList[i];
        if (obj != NULL && obj->level_entry != NULL) {
            if ((s32) arg0 < (s32) obj->level_entry && (s32) obj->level_entry < end) {
                obj->level_entry = (LevelObjectEntry *) ((s32) obj->level_entry - size);
            } else if ((s32) arg0 == (s32) obj->level_entry) {
                obj->level_entry = NULL;
            }
        }
    }
}

void func_8000E79C(u8 *arg0, u8 *arg1) {
    s32 arg0Value;
    s32 arg0Value2;
    s32 arg1Value;
    u8 *var_a3;
    u8 *var_t0;
    u8 *temp_t2;
    u8 *var_a2;
    s32 i;
    s32 j;
    s32 k;

    arg0Value = arg0[1] & 0x3F;
    arg0Value2 = arg0Value;
    arg1Value = arg1[1] & 0x3F;
    i = gObjectMapIndex;
    var_a3 = (u8 *) gObjectMap[i] + gObjectMapSize[i];
    var_a3 += 16;

    if (arg1Value < arg0Value2) {
        var_a2 = arg0 + arg1Value;
        var_t0 = arg0 + arg0Value2;
        k = (u32) var_a3;
        while (((u32) var_t0) < (u32) k) {
            *var_a2 = *var_t0;
            var_a2++;
            var_t0++;
        }
    } else if (arg0Value2 < arg1Value) {
        var_a2 = var_a3 + arg1Value;
        var_a2 -= arg0Value2;
        var_t0 = var_a3;
        k = (u32) (arg0 + arg1Value);
        while ((u32) k < ((u32) var_a2)) {
            var_a2--;
            var_t0--;
            *var_a2 = *var_t0;
        }
    }

    j = 0;
    do {
        arg0[j] = arg1[j];
        j++;
    } while (j < arg1Value);

    gObjectMapSize[i] += arg1Value - arg0Value;
}

UNUSED u8 *func_8000E898(u8 *arg0, s32 arg1) {
    s32 temp_t6;
    s32 i;
    u8 *temp_v1;
    u8 *new_var;
    u8 *new_var2;

    temp_t6 = arg0[1] & 0x3F;
    new_var = arg0;
    new_var = &gObjectMapSpawnList[arg1][gObjectMapSize[arg1]];
    new_var2 = arg0;
    temp_v1 = new_var;
    gObjectMapSize[arg1] += temp_t6;
    for (i = 0; i < temp_t6; i++) {
        temp_v1[i] = new_var2[i];
    }
    return temp_v1;
}

/**
 * Returns the object at the current offset by ID.
 * Official name: objGetObject
 */
Object *get_object(s32 index) {
    if (index < 0 || index >= gObjectCount) {
        stubbed_printf("ObjList (Part) Overflow %d!!!\n");
        return 0;
    }
    return gObjPtrList[index];
}

/**
 * Return the standard object list index and how many objects are in that list.
 */
Object **objGetObjList(s32 *arg0, s32 *cnt) {
    *arg0 = gObjectListStart;
    *cnt = gObjectCount;
    return gObjPtrList;
}

/**
 * Return the number of objects currently existing.
 */
UNUSED s32 obj_count(void) {
    return gObjectCount;
}

/**
 * Return the number of particles currently existing.
 */
UNUSED s32 particle_count(void) {
    return gParticleCount;
}

void add_particle_to_entity_list(Object *obj) {
    obj->trans.flags |= OBJ_FLAGS_PARTICLE;
    func_800245B4(obj->headerType | (OBJ_FLAGS_PARTICLE | OBJ_FLAGS_INVISIBLE));
    gObjPtrList[gObjectCount++] = obj;
    if (1) {} // Fakematch
    gParticleCount++;
}

// Official Name: ObjSetupObject
Object *spawn_object(LevelObjectEntryCommon *entry, s32 spawnFlags) {
    s32 objType;
    Settings *settings;
    s32 i;
    s32 unused2;
    s32 unused;
    s32 behaviourFlags;
    s16 headerType;
    u8 *address;
    s32 sizeOfobj;
    Object *curObj;
    Object *prevObj;
    s32 assetCount;
    s8 failed;

    settings = get_settings();
    objType = entry->objectID | ((entry->size & 0x80) << 1);
    update_object_stack_trace(OBJECT_SPAWN, objType);
    if (spawnFlags & OBJECT_SPAWN_UNK02) {
        headerType = objType;
    } else {
        headerType = gAssetsLvlObjTranslationTable[objType];
    }
    if (headerType >= gAssetsObjectHeadersTableLength) {
        headerType = 0;
    }

    for (i = 0; i < OBJECT_BLUEPRINT_SIZE / 4; i++) {
        gSpawnObjectHeap[i] = NULL;
    }

    curObj = (Object *) gSpawnObjectHeap;
    curObj->trans.flags = OBJ_FLAGS_UNK_0002;
    curObj->header = load_object_header(headerType);
    if (curObj->header == NULL) {
        return NULL;
    }
    if (curObj->header->flags & HEADER_FLAGS_UNK_0080) {
        curObj->trans.flags |= OBJ_FLAGS_UNK_0080;
    }
    if (curObj->header->behaviorId == BHV_ROCKET_SIGNPOST && (settings->cutsceneFlags & CUTSCENE_LIGHTHOUSE_ROCKET)) {
        update_object_stack_trace(OBJECT_SPAWN, -1);
        stubbed_printf("ObjSetupObject(1) Memory fail!!\n");
        return NULL;
    }

    curObj->trans.x_position = entry->x;
    curObj->trans.y_position = entry->y;
    curObj->trans.z_position = entry->z;
    curObj->segmentID = get_level_segment_index_from_position(curObj->trans.x_position, curObj->trans.y_position,
                                                              curObj->trans.z_position);

    curObj->headerType = headerType;
    curObj->level_entry = (LevelObjectEntry *) entry;
    curObj->objectID = objType;
    func_800245B4(objType);
    curObj->trans.scale = curObj->header->scale;
    curObj->unk34 = curObj->header->unk50 * curObj->trans.scale;
    curObj->opacity = 255;
    behaviourFlags = obj_init_property_flags(curObj->header->behaviorId);
    curObj->header->unk52++;

    assetCount = curObj->header->numberOfModelIds;

    objType = curObj->header->modelType;
    curObj->modelInstances = (ModelInstance **) &curObj[1];
    if (spawnFlags & OBJECT_SPAWN_NO_LODS) {
        assetCount = 1;
    }
    i = 0; // a2
    switch (curObj->header->behaviorId) {
        case BHV_PARK_WARDEN:
            model_anim_offset(7);
            break;
        case BHV_ANIMATED_OBJECT_4:
            i = get_character_id_from_slot(PLAYER_ONE);
            curObj->modelIndex = i;
            assetCount = i + 1;
            break;
        case BHV_UNK_5B:
            i = (settings->trophies >> ((settings->worldId - 1) << 1));
            i = i & 0x3;
            if (i) {
                i--;
                assetCount = i + 1;
                curObj->modelIndex = i;
            }
            break;
        case BHV_DYNAMIC_LIGHT_OBJECT_2:
            i = settings->wizpigAmulet;
            assetCount = i + 1;
            curObj->modelIndex = settings->wizpigAmulet;
            break;
        case BHV_ROCKET_SIGNPOST_2:
            objType = settings->trophies;
            for (assetCount = 0; assetCount < 4; assetCount++) {
                if ((objType & 3) == 3) {
                    i++;
                }
                objType >>= 2;
            }
            curObj->modelIndex = i;
            assetCount = i + 1;
            break;
        case BHV_GOLDEN_BALLOON:
            assetCount = 1;
            if (is_in_adventure_two()) {
                curObj->header->modelIds[0] = curObj->header->modelIds[1];
            }
            curObj->header->numberOfModelIds = 1;
            break;
    }
    if (!(spawnFlags & OBJECT_SPAWN_UNK02)) {
        switch (curObj->objectID) {
            case ASSET_OBJECT_ID_POLYGOLDBALOON:
                assetCount = 1;
                if (is_in_adventure_two()) {
                    curObj->header->modelIds[0] = curObj->header->modelIds[1];
                }
                curObj->header->numberOfModelIds = 1;
                break;
            case ASSET_OBJECT_ID_LEVELDOOR:
                if (is_in_adventure_two()) {
                    for (i = 0; i < 5; i++) {
                        curObj->header->modelIds[i] = curObj->header->modelIds[i + 5];
                    }
                }
                assetCount = 5;
                curObj->header->numberOfModelIds = 5;
                i = 0;
                break;
        }
    }

    failed = FALSE;
    if (objType == OBJECT_MODEL_TYPE_3D_MODEL) {
        while (i < assetCount) {
            if (i == 0 && (spawnFlags & OBJECT_SPAWN_UNK04)) {
                curObj->modelInstances[i] = NULL;
            } else if (i == 1 && (spawnFlags & OBJECT_SPAWN_UNK08)) {
                curObj->modelInstances[i] = NULL;
            } else {
                curObj->modelInstances[i] = object_model_init(curObj->header->modelIds[i], behaviourFlags);
                if (curObj->modelInstances[i] == NULL) {
                    failed = TRUE;
                }
            }
            i++;
        }
    } else if (objType == OBJECT_MODEL_TYPE_MISC) {
        while (i < assetCount) {
            curObj->textures[i] = load_texture(curObj->header->modelIds[i]);
            if (curObj->textures[i] == NULL) {
                failed = TRUE;
            }
            i++;
        }
    } else {
        while (i < assetCount) {
            curObj->sprites[i] = tex_load_sprite(curObj->header->modelIds[i], 10);
            if (curObj->sprites[i] == NULL) {
                failed = TRUE;
            }
            i++;
        }
    }
    if (failed) {
        objFreeAssets(curObj, assetCount, objType);
        try_free_object_header(headerType);
        stubbed_printf("ObjSetupObject(2) Memory fail!!\n");
        return NULL;
    }

    address = (u8 *) &curObj->modelInstances[curObj->header->numberOfModelIds];
    address += get_object_property_size(curObj, address);
    D_8011AE50 = NULL;
    D_8011AE54 = NULL;

    if (behaviourFlags & OBJECT_BEHAVIOUR_SHADED) {
        address += init_object_shading(curObj, (ShadeProperties *) address);
    }
    if (behaviourFlags & OBJECT_BEHAVIOUR_SHADOW) {
        sizeOfobj = init_object_shadow(curObj, (ShadowData *) address);
        address += sizeOfobj;
        if (sizeOfobj == 0) {
            objFreeAssets(curObj, assetCount, objType);
            try_free_object_header(headerType);
            stubbed_printf("ObjSetupObject(5) Memory fail!!\n");
            return NULL;
        }
    }
    if (behaviourFlags & OBJECT_BEHAVIOUR_WATER_EFFECT) {
        sizeOfobj = init_object_water_effect(curObj, (WaterEffect *) address);
        address += sizeOfobj;
        if (sizeOfobj == 0) {
            if (D_8011AE50 != NULL) {
                tex_free((TextureHeader *) (s32) D_8011AE50);
            }
            objFreeAssets(curObj, assetCount, objType);
            try_free_object_header(headerType);
            stubbed_printf("ObjSetupObject(6) Memory fail!!\n");
            return NULL;
        }
    }
    if (behaviourFlags & OBJECT_BEHAVIOUR_INTERACTIVE) {
        address += init_object_interaction_data(curObj, (ObjectInteraction *) address);
    }
    if (behaviourFlags & OBJECT_BEHAVIOUR_COLLIDABLE) {
        address += obj_init_collision(curObj, (ObjectCollision *) address);
    }
    if (curObj->header->attachPointCount > 0 && curObj->header->attachPointCount < 10) {
        curObj->attachPoints = (AttachPoint *) address;
        address += sizeof(AttachPoint);
    }
    if (curObj->header->particleCount > 0) {
        address += obj_init_emitter(curObj, (ParticleEmitter *) address);
    }

    if (curObj->header->numLightSources > 0) {
        curObj->lightData = (ObjectLight **) address;
        address += curObj->header->numLightSources * 4;
    }

    sizeOfobj = (s32) address - (s32) curObj;
    prevObj = curObj;
    curObj = mempool_alloc_pool((MemoryPoolSlot *) gObjectMemoryPool, sizeOfobj);
    if (curObj == NULL) {
        if (D_8011AE50 != NULL) {
            tex_free((TextureHeader *) (s32) D_8011AE50);
        }
        if (D_8011AE54 != NULL) {
            tex_free((TextureHeader *) (s32) D_8011AE54);
        }
        objFreeAssets(prevObj, assetCount, objType);
        try_free_object_header(headerType);
        stubbed_printf("ObjSetupObject(3) Memory fail!!\n");
        return NULL;
    }

    i = 0;
    if (sizeOfobj & 0xF) {
        sizeOfobj = _ALIGN16(sizeOfobj);
    }

    sizeOfobj >>= 2;
    while (i < sizeOfobj) {
        ((u32 *) curObj)[i] = gSpawnObjectHeap[i];
        i++;
    }

    if (curObj->waterEffect != NULL) {
        curObj->waterEffect =
            (WaterEffect *) (((uintptr_t) curObj + (uintptr_t) curObj->waterEffect) - (uintptr_t) gSpawnObjectHeap);
    }
    if (curObj->shadow != NULL) {
        curObj->shadow =
            (ShadowData *) (((uintptr_t) curObj + (uintptr_t) curObj->shadow) - (uintptr_t) gSpawnObjectHeap);
    }
    if (curObj->shading != NULL) {
        curObj->shading =
            (ShadeProperties *) (((uintptr_t) curObj + (uintptr_t) curObj->shading) - (uintptr_t) gSpawnObjectHeap);
    }
    if (curObj->anyBehaviorData != NULL) {
        curObj->anyBehaviorData =
            (void *) (((uintptr_t) curObj + (uintptr_t) curObj->anyBehaviorData) - (uintptr_t) gSpawnObjectHeap);
    }
    if (curObj->interactObj != NULL) {
        curObj->interactObj = (ObjectInteraction *) (((uintptr_t) curObj + (uintptr_t) curObj->interactObj) -
                                                     (uintptr_t) gSpawnObjectHeap);
    }
    if (curObj->collisionData != NULL) {
        curObj->collisionData = (ObjectCollision *) (((uintptr_t) curObj + (uintptr_t) curObj->collisionData) -
                                                     (uintptr_t) gSpawnObjectHeap);
    }
    if (curObj->attachPoints != NULL) {
        curObj->attachPoints =
            (AttachPoint *) (((uintptr_t) curObj + (uintptr_t) curObj->attachPoints) - (uintptr_t) gSpawnObjectHeap);
    }
    if (curObj->header->particleCount > 0) {
        curObj->particleEmitter = (ParticleEmitter *) (((uintptr_t) curObj + (uintptr_t) curObj->particleEmitter) -
                                                       (uintptr_t) gSpawnObjectHeap);
    }
    if (curObj->header->numLightSources > 0) {
        curObj->lightData =
            (ObjectLight **) (((uintptr_t) curObj + (uintptr_t) curObj->lightData) - (uintptr_t) gSpawnObjectHeap);
    }
    curObj->modelInstances = (ModelInstance **) &curObj[1];

    if (spawnFlags & OBJECT_SPAWN_UNK01) {
        if (curObj && curObj) {} // Fakematch
        gObjPtrList[gObjectCount++] = curObj;
        if (gObjectCount > OBJECT_SLOT_COUNT) {
            stubbed_printf("ObjList Overflow %d!!!\n", gObjectCount);
        }
    }
    run_object_init_func(curObj, entry, 0);
    if (curObj->interactObj != NULL) {
        curObj->interactObj->x_position = curObj->trans.x_position;
        curObj->interactObj->y_position = curObj->trans.y_position;
        curObj->interactObj->z_position = curObj->trans.z_position;
    }
    if (curObj->header->attachPointCount > 0 && curObj->header->attachPointCount < 10 && obj_init_attachpoint(curObj)) {
        if (D_8011AE50 != NULL) {
            tex_free((TextureHeader *) (s32) D_8011AE50);
        }
        if (D_8011AE54 != NULL) {
            tex_free((TextureHeader *) (s32) D_8011AE54);
        }
        objFreeAssets(curObj, assetCount, objType);
        try_free_object_header(headerType);
        mempool_free(curObj);
        if (spawnFlags & OBJECT_SPAWN_UNK01) {
            gObjectCount--;
        }
        stubbed_printf("ObjSetupObject(4) Memory fail!!\n");
        return NULL;
    }
    if (curObj->header->numLightSources > 0) {
        light_setup_light_sources(curObj);
    }
    model_anim_offset(0);
    update_object_stack_trace(OBJECT_SPAWN, -1);
    return curObj;
}

/**
 * Run functions that will attempt to free the graphics data of the object
 * if there are no other references.
 */
void objFreeAssets(Object *obj, s32 count, s32 objType) {
    s32 i;
    if (objType == OBJECT_MODEL_TYPE_3D_MODEL) { // 3D model
        for (i = 0; i < count; i++) {
            if (obj->modelInstances[i] != NULL) {
                free_3d_model((ModelInstance *) (s32) obj->modelInstances[i]);
            }
        }
    } else if (objType == OBJECT_MODEL_TYPE_MISC) {
        for (i = 0; i < count; i++) {
            if (obj->textures[i] != NULL) {
                tex_free((TextureHeader *) (s32) obj->textures[i]);
            }
        }
    } else { // Sprite
        for (i = 0; i < count; i++) {
            if (obj->sprites[i] != NULL) {
                sprite_free((Sprite *) (s32) obj->sprites[i]);
            }
        }
    }
}
/**
 * Official Name: lightSetupLightSources
 */
void light_setup_light_sources(Object *obj) {
    s32 i;
    for (i = 0; i < obj->header->numLightSources; i++) {
        obj->lightData[i] = light_add_from_object_header(obj, &obj->header->unk24[i]);
    }
}

/**
 * Sets the shading properties of the object.
 */
s32 init_object_shading(Object *obj, ShadeProperties *shadeData) {
    s32 returnSize;
    s32 i;

    obj->shading = shadeData;
    returnSize = 0;
    if (obj->header->modelType == OBJECT_MODEL_TYPE_3D_MODEL) {
        for (i = 0; obj->modelInstances[i] == NULL; i++) {}
        if (obj->modelInstances[i] != NULL && obj->modelInstances[i]->objModel->normals != NULL) {
            set_shading_properties(obj->shading, obj->header->shadeAmbient, obj->header->shadeDiffuse, 0,
                                   obj->header->shadeAngleY, obj->header->shadeAngleZ);
            if (obj->header->shadeIntensityy != 0) {
                obj->shading->lightR = obj->header->unk3A;
                obj->shading->lightG = obj->header->unk3B;
                obj->shading->lightB = obj->header->unk3C;
                obj->shading->lightIntensity = obj->header->shadeIntensityy;
                obj->shading->lightDirX = -(obj->shading->shadowDirX >> 1);
                obj->shading->lightDirY = -(obj->shading->shadowDirY >> 1);
                obj->shading->lightDirZ = -(obj->shading->shadowDirZ >> 1);
            }
            returnSize = sizeof(ShadeProperties);
        }
    } else if (obj->header->modelType == OBJECT_MODEL_TYPE_SPRITE_BILLBOARD) {
        obj->shading->unk0 = 1.0f;
        shadeData->lightR = 255;
        shadeData->lightG = 255;
        shadeData->lightB = 255;
        shadeData->lightIntensity = 0;
        returnSize = 8;
    }
    if (returnSize == 0) {
        obj->shading = NULL;
    }
    return (returnSize & ~3) + 4;
}

s32 obj_init_attachpoint(Object *obj) {
    Object *attachObj;
    AttachPoint *attachPoint;
    s32 i;
    s32 failed;

    attachPoint = obj->attachPoints;
    attachPoint->count = obj->header->attachPointCount;
    attachPoint->count = attachPoint->count; // Fakematch?
    failed = FALSE;
    for (i = 0; i < attachPoint->count; i++) {
        attachPoint->obj[i] = obj_spawn_attachment(obj->header->vehiclePartIds[i ^ 0]); // i ^ 0 fakematch
        if (attachPoint->obj[i] == NULL) {
            failed = TRUE;
        }
    }
    if (failed) {
        for (i = 0; i < attachPoint->count; i++) {
            attachObj = attachPoint->obj[i];
            if (attachObj != NULL) {
                objFreeAssets(attachObj, attachObj->header->numberOfModelIds, attachObj->header->modelType);
                try_free_object_header(attachObj->headerType);
                mempool_free(attachObj);
            }
        }
        return TRUE;
    }
    attachPoint->unk2C = obj->header->vehiclePartIndices;
    return FALSE;
}

s32 obj_init_emitter(Object *obj, ParticleEmitter *emitter) {
    ObjHeaderParticleEntry *particleDataEntry;
    s32 i;

    obj->particleEmitter = emitter;
    particleDataEntry = obj->header->objectParticles;
    for (i = 0; i < obj->header->particleCount; i++) {
        if ((particleDataEntry[i].upper & 0xFFFF0000) == 0xFFFF0000) {
            emitter_init(&obj->particleEmitter[i], (particleDataEntry[i].upper >> 8) & 0xFF,
                         particleDataEntry[i].upper & 0xFF);
        } else {
            emitter_init_with_pos(&obj->particleEmitter[i], (particleDataEntry[i].upper >> 0x18) & 0xFF,
                                  (particleDataEntry[i].upper >> 0x10) & 0xFF, particleDataEntry[i].upper & 0xFFFF,
                                  (particleDataEntry[i].lower >> 0x10) & 0xFFFF, particleDataEntry[i].lower & 0xFFFF);
        }
    }
    return ((obj->header->particleCount * sizeof(ParticleEmitter)) + 3) & ~3;
}

/**
 * Assigns shadow data to an object. Loads and assigns the shadow texture, too.
 * Returns zero if the texture is missing.
 */
s32 init_object_shadow(Object *obj, ShadowData *shadow) {
    ObjectHeader *objHeader;

    obj->shadow = shadow;
    shadow->texture = NULL;
    objHeader = obj->header;
    if (objHeader->shadowGroup) {
        shadow->texture = load_texture(objHeader->unk34);
        objHeader = obj->header;
    }
    shadow->scale = objHeader->shadowScale;
    shadow->meshStart = -1;
    D_8011AE50 = shadow->texture;
    if (obj->header->shadowGroup && shadow->texture == NULL) {
        return 0;
    }
    return sizeof(ShadowData);
}

/**
 * Assigns water effect data to an object. Loads and assigns the effect texture, too.
 * Returns zero if the texture is missing.
 */
s32 init_object_water_effect(Object *obj, WaterEffect *waterEffect) {
    obj->waterEffect = waterEffect;
    waterEffect->scale = obj->header->unk8;
    waterEffect->textureFrame = 0;
    waterEffect->animationSpeed = obj->header->unk0 >> 8;
    waterEffect->texture = NULL;
    if (obj->header->waterEffectGroup) {
        waterEffect->texture = load_texture(obj->header->unk38);
    }
    waterEffect->meshStart = -1;
    D_8011AE54 = waterEffect->texture;
    if (obj->header->waterEffectGroup && waterEffect->texture == NULL) {
        return 0;
    }
    return sizeof(WaterEffect);
}

/**
 * Writes object interatction properties to the object.
 * Returns 40, to offset the pointer position used
 */
s32 init_object_interaction_data(Object *obj, ObjectInteraction *interactObj) {
    obj->interactObj = interactObj;
    interactObj->distance = 0xFF;
    return sizeof(ObjectInteraction);
}

/**
 * Sets up collision surface data for the object model.
 */
s32 obj_init_collision(Object *obj, ObjectCollision *colData) {
    obj->collisionData = colData;
    func_80016BC4(obj);
    return sizeof(ObjectCollision);
}

/**
 * Attempts to spawn an attachment object.
 * Similar to the regular object spawning function, but cut down considerably.
 */
Object *obj_spawn_attachment(s32 objID) {
    s32 modelType;
    Object *object;
    ObjectHeader *objHeader;
    s32 objSize;
    s32 i;
    s32 failedToLoadModel;
    s8 numModelIds;
    u8 *objectAsRawBytes;

    if (objID >= gAssetsObjectHeadersTableLength) {
        objID = 0;
    }
    objHeader = load_object_header(objID);
    if (objHeader == NULL) {
        return NULL;
    }
    objSize = (objHeader->numberOfModelIds * 4) + 0x80;
    object = (Object *) mempool_alloc(objSize, COLOUR_TAG_BLUE);
    if (object == NULL) {
        try_free_object_header(objID);
        return NULL;
    }

    // clang-format off
    objectAsRawBytes = (u8 *) object;
    for (i = 0; i < objSize; i++) { objectAsRawBytes[i] = 0; } // Must be one line! (Why not use bzero?)
    // clang-format on

    object->trans.flags = OBJ_FLAGS_UNK_0002;
    object->header = objHeader;
    object->headerType = objID;
    object->objectID = objID;
    object->trans.scale = objHeader->scale;
    if (objHeader->flags & HEADER_FLAGS_UNK_0080) {
        object->trans.flags |= OBJ_FLAGS_UNK_0080;
    }
    numModelIds = object->header->numberOfModelIds;
    modelType = object->header->modelType;
    object->modelInstances = (ModelInstance **) &object[1];

    failedToLoadModel = FALSE;
    if (modelType == OBJECT_MODEL_TYPE_3D_MODEL) {
        for (i = 0; i < numModelIds; i++) {
            object->modelInstances[i] = object_model_init(object->header->modelIds[i], 0);
            if (object->modelInstances[i] == NULL) {
                failedToLoadModel = TRUE;
            }
        }
    } else {
        for (i = 0; i < numModelIds; i++) {
            object->sprites[i] = tex_load_sprite(object->header->modelIds[i], 10);
            if (object->sprites[i] == NULL) {
                failedToLoadModel = TRUE;
            }
        }
    }
    if (failedToLoadModel) {
        objFreeAssets(object, numModelIds, modelType);
        try_free_object_header(objID);
        mempool_free(object);
        return NULL;
    }

    return object;
}

/**
 * Adds the object to the free list.
 * This object will be deallocated on the next update cycle.
 * Official Name: objFreeObject
 */
void free_object(Object *object) {
    func_800245B4(object->objectID | OBJ_FLAGS_PARTICLE);
    gParticlePtrList[gFreeListCount] = object;
    gFreeListCount++;
}

/**
 * Return the length of the object ID table.
 */
UNUSED s32 obj_table_ids(void) {
    return gAssetsLvlObjTranslationTableLength;
}

/**
 * Return true if the object ID is not higher than the header table length.
 */
UNUSED s32 obj_id_valid(s32 arg0) {
    return (gAssetsLvlObjTranslationTable[arg0] < gAssetsObjectHeadersTableLength);
}

/*
 * Clears all existing particles from the object list
 */
void gParticlePtrList_flush(void) {
    s32 j, i, search_indx;
    Object *searchObj;

    D_8011AE88 = 0;
    for (i = 0; i < gFreeListCount; i++) {
        search_indx = -1;
        searchObj = gParticlePtrList[i];

        for (j = 0; j < gObjectCount; j++) {
            if (searchObj == gObjPtrList[j]) {
                search_indx = j;
            }
        }

        // if object found
        if (search_indx != -1) {
            if (search_indx < gFirstActiveObjectId) {
                gFirstActiveObjectId--;
            }
            gObjectCount--;
            if (0) {} // Fakematch
            for (j = search_indx; j < gObjectCount; j++) {
                gObjPtrList[j] = gObjPtrList[j + 1];
            }
        }
        obj_destroy(searchObj, 0);
    }
    gFreeListCount = 0;
}

/**
 * Destroys an object and frees its resources.
 */
void obj_destroy(Object *obj, s32 arg1) {
    Object *tempObj;
    Object_Weapon *weapon;
    Object_Racer *racer;
    Object_AnimatedObject *snowball;
    Object_Weapon *fireball;
    Object_Log *log;
    Object_Butterfly *butterfly;
    SoundHandle soundMask;
    s32 numberOfModelIds;
    s32 i;
    s32 j;
    Object_AnimatedObject *obj64;
    ModelInstance *models;
    s32 modelType;

    if (obj->trans.flags & OBJ_FLAGS_PARTICLE) {
        particle_deallocate((Particle *) obj);
        gParticleCount--;
        return;
    }

    if (obj->attachPoints != NULL) {
        for (i = 0; i < obj->attachPoints->count; i++) {
            tempObj = obj->attachPoints->obj[i];
            numberOfModelIds = tempObj->header->numberOfModelIds;
            modelType = tempObj->header->modelType;
            if (modelType == OBJECT_MODEL_TYPE_3D_MODEL) {
                for (j = 0; j < numberOfModelIds; j++) {
                    free_3d_model((ModelInstance *) &tempObj->modelInstances[j]->objModel);
                }
            } else {
                for (j = 0; j < numberOfModelIds; j++) {
                    sprite_free(tempObj->sprites[j]);
                }
            }
            try_free_object_header(tempObj->headerType);
            mempool_free(tempObj);
        }
    }
    if (obj->lightData != NULL) {
        for (i = 0; i < obj->header->numLightSources; i++) {
            light_remove(obj->lightData[i]);
        }
    }
    switch (obj->behaviorId) {
        case BHV_RACER:
        case BHV_ANIMATED_OBJECT_3:
            for (i = 0; i < gObjectCount; i++) {
                tempObj = gObjPtrList[i];
                if (tempObj->behaviorId == BHV_BUTTERFLY) {
                    butterfly = tempObj->butterfly;
                    if (obj == butterfly->unk100) {
                        butterfly->unk100 = 0;
                        butterfly->unkFD = 1;
                    }
                }
            }

            i = BHV_RACER;
            break;
        case BHV_WEAPON:
        case BHV_WEAPON_2:
            weapon = obj->weapon;
            if (weapon->soundMask != NULL) {
                audspat_point_stop(weapon->soundMask);
                weapon->soundMask = NULL;
                if (obj->behaviorId == BHV_WEAPON_2) {
                    decrease_rocket_sound_timer();
                }
            }

            i = BHV_RACER;
            break;
        case BHV_FIREBALL_OCTOWEAPON_2:
            weapon = obj->weapon;
            if (weapon->soundMask != NULL) {
                audspat_point_stop(weapon->soundMask);
            }

            i = BHV_RACER;
            break;
        case BHV_SNOWBALL:
        case BHV_SNOWBALL_2:
        case BHV_SNOWBALL_3:
        case BHV_SNOWBALL_4:
            snowball = obj->animatedObject;
            if (snowball->soundMask != NULL) {
                audspat_point_stop((AudioPoint *) snowball->soundMask);
            }

            i = BHV_RACER;
            break;
        case BHV_WAVE_GENERATOR:
            wavegen_destroy(obj);

            i = BHV_RACER;
            break;
        case BHV_LIGHT_RGBA:
            light_remove(obj->light);

            i = BHV_RACER;
            break;
        case BHV_ANIMATION:
            if (obj->animTarget != NULL && arg1 == 0) {
                free_object(obj->animTarget);
            }

            i = BHV_RACER;
            break;
        case BHV_OVERRIDE_POS:
            for (j = 0; j < D_8011AE00 && obj != D_8011ADD8[j]; j++) {}
            if (j < D_8011AE00) {
                D_8011AE00--;
                for (; j < D_8011AE00; j++) {
                    D_8011ADD8[j] = D_8011ADD8[j + 1];
                }
            }

            i = BHV_RACER;
            break;
        case BHV_BUOY_PIRATE_SHIP:
        case BHV_LOG:
            log = obj->log;
            if (log != NULL) {
                mempool_free(log);
            }

            i = BHV_RACER;
            break;
        case BHV_LENS_FLARE:
            lensflare_remove(obj);

            i = BHV_RACER;
            break;
        case BHV_LENS_FLARE_SWITCH:
            lensflare_override_remove(obj);

            i = BHV_RACER;
            break;
        default:

            i = BHV_RACER;
            break;
    }
    switch (obj->behaviorId) {
        case BHV_DINO_WHALE:
        case BHV_ANIMATED_OBJECT:
        case BHV_CAMERA_ANIMATION:
        case BHV_CAR_ANIMATION:
        case BHV_CHARACTER_SELECT:
        case BHV_VEHICLE_ANIMATION:
        case BHV_HIT_TESTER:
        case BHV_HIT_TESTER_2:
        case BHV_PARK_WARDEN_2:
        case BHV_ANIMATED_OBJECT_2:
        case BHV_WIZPIG_SHIP:
        case BHV_ANIMATED_OBJECT_3:
        case BHV_ANIMATED_OBJECT_4:
        case BHV_SNOWBALL:
        case BHV_SNOWBALL_2:
        case BHV_SNOWBALL_3:
        case BHV_SNOWBALL_4:
        case BHV_HIT_TESTER_3:
        case BHV_HIT_TESTER_4:
        case BHV_DOOR_OPENER:
        case BHV_PIG_ROCKETEER:
        case BHV_WIZPIG_GHOSTS:
            obj64 = obj->animatedObject;
            soundMask = obj64->unk18;
            if (soundMask != NULL) {
                sndp_stop(soundMask);
            }
            break;
    }
    if (obj->behaviorId == i) {
        racer = obj->racer;
        if (racer->unk18 != NULL) {
            sndp_stop((SoundHandle) (s32) racer->unk18); // type cast required to match
        }
        if (racer->unk10 != NULL) {
            sndp_stop((SoundHandle) (s32) racer->unk10); // type cast required to match
        }
        if (racer->unk14 != NULL) {
            sndp_stop((SoundHandle) (s32) racer->unk14); // type cast required to match
        }
        if (racer->unk1C != NULL) {
            sndp_stop((SoundHandle) (s32) racer->unk1C); // type cast required to match
        }
        if (racer->unk20 != NULL) {
            sndp_stop((SoundHandle) (s32) racer->unk20); // type cast required to match
        }
        if (racer->soundMask != NULL) {
            audspat_point_stop(racer->soundMask);
        }
        if (racer->shieldSoundMask != NULL) {
            audspat_point_stop(racer->shieldSoundMask);
        }
        if (racer->magnetSoundMask != NULL) {
            sndp_stop(racer->magnetSoundMask);
        }
        racer_sound_free(obj);
        for (j = 0; j < gObjectCount; j++) {
            if ((gObjPtrList[j]->trans.flags & OBJ_FLAGS_PARTICLE) &&
                ((s32) gObjPtrList[j]->level_entry == (s32) obj)) {
                gObjPtrList[j]->level_entry = NULL;
            }
            if (gObjPtrList[j]->behaviorId == BHV_WEAPON_2 || gObjPtrList[j]->behaviorId == BHV_FLY_COIN ||
                gObjPtrList[j]->behaviorId == BHV_WEAPON) {
                free_object(gObjPtrList[j]);
            }
        }
    }
    if (obj->shadow != NULL && obj->shadow->texture != NULL) {
        tex_free(obj->shadow->texture);
    }
    if (obj->waterEffect != NULL && obj->waterEffect->texture != NULL) {
        tex_free(obj->waterEffect->texture);
    }
    numberOfModelIds = obj->header->numberOfModelIds;
    modelType = obj->header->modelType;
    if (modelType == OBJECT_MODEL_TYPE_3D_MODEL) {
        for (j = 0; j < numberOfModelIds; j++) {
            if (obj->modelInstances[j] != NULL) {
                models = obj->modelInstances[j];
                free_3d_model(models);
            }
        }
    } else if (modelType == OBJECT_MODEL_TYPE_MISC) {
        for (j = 0; j < numberOfModelIds; j++) {
            tex_free(obj->textures[j]);
        }
    } else {
        for (j = 0; j < numberOfModelIds; j++) {
            sprite_free(obj->sprites[j]);
        }
    }
    if (obj->header->particleCount > 0) {
        for (j = 0; j < obj->header->particleCount; j++) {
            emitter_cleanup(&obj->particleEmitter[j]);
        }
    }
    try_free_object_header(obj->headerType);
    mempool_free(obj);
}

/**
 * Updates all objects in the game.
 */
void obj_update(s32 updateRate) {
    s32 i;
    s32 j;
    Object_Racer *racer;
    ModelInstance *modInst;
    s32 sp54;
    Object *obj;

    func_800245B4(-1);
    gEventStartTimer = gEventCountdown;
    if (gEventCountdown > 0 && race_starting() != FALSE) {
        gEventCountdown -= updateRate;
        D_8011ADBC = 0;
    } else {
        D_8011ADBC += updateRate;
    }
    if (gEventCountdown <= 0) {
        gEventCountdown = 0;
    }
    D_8011AD3D = 0;
    D_8011AD21 = 1 - D_8011AD21;
    D_8011AD22[D_8011AD21] = 0;
    for (j = 0; j < gNumRacers; j++) {
        racer = (*gRacers)[j]->racer;
        racer->prev_x_position = (*gRacers)[j]->trans.x_position;
        racer->prev_y_position = (*gRacers)[j]->trans.y_position;
        racer->prev_z_position = (*gRacers)[j]->trans.z_position;
    }
    obj_tick_anims();
    process_object_interactions();
    func_8001E89C();
    // Update collidable objects first.
    for (i = 0; i < gCollisionObjectCount; i++) {
        run_object_loop_func(gCollisionObjects[i], updateRate);
    }
    func_8001E6EC(TRUE);
    for (i = 0; i < gCollisionObjectCount; i++) {
        obj_collision_transform(gCollisionObjects[i]);
    }
    // Update nonspecific objects
    j = gObjectCount;
    for (i = gObjectListStart; i < j; i++) {
        obj = gObjPtrList[i];
        if (!(obj->trans.flags & OBJ_FLAGS_PARTICLE)) {
            if ((obj->behaviorId != BHV_LIGHT_RGBA) && (obj->behaviorId != BHV_WEAPON) &&
                (obj->behaviorId != BHV_FOG_CHANGER)) {
                if (obj->interactObj != NULL) {
                    if (obj->interactObj->unk11 != 2) {
                        run_object_loop_func(obj, updateRate);
                    }
                } else {
                    run_object_loop_func(obj, updateRate);
                }
                if (obj->header->modelType == OBJECT_MODEL_TYPE_3D_MODEL) {
                    for (sp54 = 0; sp54 < obj->header->numberOfModelIds; sp54++) {
                        modInst = obj->modelInstances[sp54];
                        if (modInst != NULL) {
                            modInst->objModel->texOffsetUpdateRate = updateRate;
                        }
                    }
                    if (obj->header->unk72 != 0xFF) {
                        func_80014090(obj, updateRate);
                    }
                }
            }
        }
    }
    // Update racers
    for (i = 0; i < gNumRacers; i++) {
        update_player_racer((*gRacers)[i], updateRate);
    }
    if (level_type() == RACETYPE_DEFAULT) {
        for (i = 0; i < gNumRacers; i++) {
            racer = gRacersByPosition[i]->racer;
            if (racer->playerIndex != -1) {
                increment_ai_behaviour_chances(gRacersByPosition[i], racer, updateRate);
                i = gNumRacers; // Why not just break?
            }
        }
    }
    racerfx_update(updateRate);
    for (i = gObjectListStart; i < j; i++) {
        obj = gObjPtrList[i];
        if ((!(obj->trans.flags & OBJ_FLAGS_PARTICLE) && (obj->behaviorId == BHV_WEAPON)) ||
            (obj->behaviorId == BHV_FOG_CHANGER)) {
            run_object_loop_func(obj, updateRate);
        }
    }
    // Update particles
    if (gParticleCount > 0) {
        for (i = gObjectListStart; i < j; i++) {
            obj = gObjPtrList[i];
            if (obj->trans.flags & OBJ_FLAGS_PARTICLE) {
                particle_update((Particle *) obj, updateRate);
            }
        }
    }

    // Update lights
    light_update_all(updateRate);
    if (light_count() > 0) {
        for (i = gObjectListStart; i < gObjectCount; i++) {
            obj = gObjPtrList[i];
            if (!(obj->trans.flags & OBJ_FLAGS_PARTICLE) && (obj->shading != NULL)) {
                light_update_shading(obj);
            }
        }
    }
    func_8001E6EC(FALSE);
    if (gTajRaceInit) {
        mode_init_taj_race();
    }
    if (gPathUpdateOff == FALSE) {
        gParticlePtrList_flush();
        checkpoint_update_all();
        spectate_update();
        func_8001E93C();
    }
    if (gNumRacers != 0) {
        if (gRaceEndTimer == 0) {
            race_check_finish(updateRate);
        } else {
            race_transition_adventure(updateRate);
        }
    }
    audspat_update_all(gRacersByPort, gNumRacers, updateRate);
    gPathUpdateOff = TRUE;
    gObjectUpdateRateF = (f32) updateRate;
    D_8011AD24[0] = FALSE;
    D_8011AD53 = 0;
    transform_player_vehicle();
    dialogue_try_close();
    func_800179D0();

    // @fake
    do {
    } while (0);
    if (D_8011AF00 == 1) {
        if (gEventCountdown == 80 && gCutsceneID == CUTSCENE_NONE) {
            sp54 = 0;
            for (j = 0; j < MAXCONTROLLERS; j++) {
                sp54 |= input_pressed(j);
            }

            if (sp54 & A_BUTTON) {
                func_8001E45C(CUTSCENE_ID_UNK_64);
            } else if ((sp54 & B_BUTTON) && (get_trophy_race_world_id() == 0) && (is_in_tracks_mode() == 0)) {
                level_transition_begin(1); // FADE_BARNDOOR_HORIZONTAL?
            }
        }
    } else if (D_8011AF00 == 0) {
        D_8011AF00 = 1;
    }
}

/**
 * Handles texture animation for an object.
 * Applies texture offset based on the update rate.
 */
void obj_tex_animate(Object *obj, s32 updateRate) {
    ObjectModel *model;
    TriangleBatchInfo *batches;
    s32 offset;
    TextureHeader *tex;
    s16 temp_s5;
    s32 batchNumber;
    ModelInstance *modInst;

    modInst = obj->modelInstances[obj->modelIndex];
    model = modInst->objModel;
    batches = model->batches;
    temp_s5 = model->unk50;
    for (batchNumber = 0; temp_s5 > 0 && batchNumber < model->numberOfBatches; batchNumber++) {
        if (batches[batchNumber].flags & RENDER_TEX_ANIM) {
            if (batches[batchNumber].textureIndex != TEX_INDEX_NO_TEXTURE) {
                tex = model->textures[batches[batchNumber].textureIndex].texture;
                offset = batches[batchNumber].texOffset;
                offset <<= 6;
                tex_animate_texture(tex, &batches[batchNumber].flags, &offset, updateRate);
                batches[batchNumber].texOffset = (offset >> 6) & 0xFF;
            }
        }
    }
}

/**
 * Sets the texture offset on the door number based on the balloon requirement.
 */
void obj_door_number(ObjectModel *model, Object *obj) {
    Object_Door *door;
    s32 current;
    s32 remaining;
    s32 i;
    TriangleBatchInfo *batch;

    if (model->unk50 <= 0) {
        return;
    }

    door = obj->door;
    remaining = door->balloonCount;
    current = ((remaining / 10) - 1) << 2;
    remaining = (remaining % 10) << 2;
    i = 0;
    batch = model->batches;

    while (i < model->numberOfBatches) {
        if (batch[i].flags & RENDER_TEX_ANIM) {
            if (batch[i].textureIndex != TEX_INDEX_NO_TEXTURE) {
                // Fakematch
                if (model->textures[batch[i].textureIndex].texture) {}
                if (model->textures[batch[i].textureIndex].texture->numOfTextures > 0x900) {
                    batch[i].texOffset = remaining;
                } else if (current >= 0) {
                    batch[i].texOffset = current;
                }
            }
        }
        i++;
    }
}

/**
 * Do nothing. Unused.
 */
UNUSED void do_nothing_func_80011364(UNUSED s32 unused) {
}

/**
 * Return true if paths are intended to be updated.
 * The variable they use here is backwards in terms of use.
 * Yes means no, no means yes.
 */
UNUSED s32 path_update_check(void) {
    // Ever hear of return !gPathUpdateOff?
    if (gPathUpdateOff) {
        return FALSE;
    } else {
        return TRUE;
    }
}

/**
 * Signal to the game that checkpoints should be updated.
 */
void path_enable(void) {
    gPathUpdateOff = FALSE;
}

/**
 * Return the current race countdown timer.
 */
s32 get_race_countdown(void) {
    return gEventCountdown;
}

/**
 * Return the timer that the countdown is set to before the race starts.
 * There exists another variable in racer.c with exactly the same purpose.
 * This does not get used anywhere else.
 */
s32 get_race_start_timer(void) {
    return gEventStartTimer;
}

// Unused function, purpose currently unknown.
UNUSED s32 func_800113BC(void) {
    return D_8011ADBC;
}

/**
 * When the object reaches a certain anim frame, play a sound and shake the camera to emphasise the effect of their
 * movement.
 */
s32 play_footstep_sounds(Object *obj, s32 arg1, s32 frame, s32 oddSoundId, s32 evenSoundId) {
    s8 *asset;
    f32 shakeDist;
    f32 shakeMagnitude;
    s32 animFrame;
    s32 asset0;
    s8 nextAsset;
    s32 i;
    s32 ret;
    s32 soundId;

    ret = 0;
    if (arg1 < obj->header->unk5B) {
        // TODO: Figure this one out better. The index could be something like this:
        // obj->header->internalName[arg1 - 4]
        asset = (s8 *) get_misc_asset(*(&obj->header->unk5C + arg1));
        asset0 = asset[0];
        shakeDist = (asset[1] & 0xFF) * 8.0f;
        shakeMagnitude = asset[2];
        frame >>= 4;
        animFrame = obj->animFrame >> 4;
        for (i = 0; i < asset0; i++) {
            nextAsset = asset[i + 3];
            if ((animFrame >= nextAsset && frame < nextAsset) || (nextAsset >= animFrame && nextAsset < frame)) {
                set_camera_shake_by_distance(obj->trans.x_position, obj->trans.y_position, obj->trans.z_position,
                                             shakeDist, shakeMagnitude);
                if (i & 1) {
                    soundId = oddSoundId; // Always set to SOUND_STOMP2
                } else {
                    soundId = evenSoundId; // Always set to SOUND_STOMP3
                }
                audspat_play_sound_at_position(soundId, obj->trans.x_position, obj->trans.y_position,
                                               obj->trans.z_position, AUDIO_POINT_FLAG_ONE_TIME_TRIGGER, NULL);
                ret = i + 1;
                i = asset0; // Come on, just use break!
            }
        }
    }
    return ret;
}

/**
 * Make the next call of move_object never mark the object as out of bounds.
 * Official Name: objMoveXYZnocheck
 */
void ignore_bounds_check(void) {
    gNoBoundsCheck = TRUE;
}

/**
 * Sets the new position of the object using the differences given.
 * Compares against the outer edges of the level geometry to decide wether or not to apply a segment ID.
 * Official Name: objMoveXYZ
 */
s32 move_object(Object *obj, f32 xPos, f32 yPos, f32 zPos) {
    s32 segmentID;
    f32 x1, x2, y1, y2, z1, z2;
    f32 newXPos;
    f32 newYPos;
    f32 newZPos;
    LevelModel *levelModel;
    LevelModelSegmentBoundingBox *box;
    s32 outsideBBox;
    s32 outOfBounds;
    s32 intXPos, intYPos, intZPos;

    levelModel = get_current_level_model();
    newXPos = obj->trans.x_position + xPos;
    newYPos = obj->trans.y_position + yPos;
    newZPos = obj->trans.z_position + zPos;
    if (levelModel == NULL) {
        gNoBoundsCheck = FALSE;
        return FALSE;
    }
    outOfBounds = FALSE;
    x2 = (levelModel->upperXBounds + 1000.0);
    //!@bug should've compared against "obj->trans.x_position"
    if (newXPos > x2) {
        outOfBounds = TRUE;
    }
    x1 = (levelModel->lowerXBounds - 1000.0);
    if (obj->trans.x_position < x1) {
        outOfBounds = TRUE;
    }
    if (1) {}
    if (1) {}
    if (1) {} // Fakematch
    y2 = (levelModel->upperYBounds + 3000.0);
    if (obj->trans.y_position > y2) {
        outOfBounds = TRUE;
    }
    y1 = (levelModel->lowerYBounds - 500.00);
    if (obj->trans.y_position < y1) {
        outOfBounds = TRUE;
    }
    z2 = (levelModel->upperZBounds + 1000.0);
    if (obj->trans.z_position > z2) {
        outOfBounds = TRUE;
    }
    z1 = (levelModel->lowerZBounds - 1000.0);
    if (obj->trans.z_position < z1) {
        outOfBounds = TRUE;
    }
    if (gNoBoundsCheck) {
        outOfBounds = FALSE;
    }

    gNoBoundsCheck = FALSE;
    if (outOfBounds) {
        obj->segmentID = -1;
        return TRUE;
    }

    obj->trans.x_position = newXPos;
    obj->trans.y_position = newYPos;
    obj->trans.z_position = newZPos;
    box = block_boundbox(obj->segmentID);

    // For some reason the XYZ positions are converted into integers for the next section
    intXPos = newXPos, intYPos = newYPos, intZPos = newZPos;

    if (box == NULL) {
        obj->segmentID = get_level_segment_index_from_position(intXPos, intYPos, intZPos);
        return FALSE;
    } else {
        outsideBBox = FALSE;
        if (box->x2 < intXPos || intXPos < box->x1) {
            outsideBBox = TRUE;
        }
        if (box->y2 < intYPos || intYPos < box->y1) {
            outsideBBox = TRUE;
        }
        if (box->z2 < intZPos || intZPos < box->z1) {
            outsideBBox = TRUE;
        }
        if (outsideBBox) {
            segmentID = get_level_segment_index_from_position(intXPos, intYPos, intZPos);
            if (segmentID != -1) {
                obj->segmentID = segmentID;
            }
        }
    }
    return FALSE;
}

/**
 * Set up the basic model view matrix, load a texture, then render the mesh.
 * A much simpler, faster way to render an object model as opposed to render_3d_model
 */
void render_misc_model(Object *obj, Vertex *verts, u32 numVertices, Triangle *triangles, u32 numTriangles,
                       TextureHeader *tex, u32 flags, u32 texOffset, f32 scaleY) {
    s32 hasTexture = FALSE;
    mtx_cam_push(&gObjectCurrDisplayList, &gObjectCurrMatrix, &obj->trans, scaleY, 0.0f);
    gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
    gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 255, 0);
    if (tex != NULL) {
        hasTexture = TRUE;
    }
    material_set(&gObjectCurrDisplayList, tex, flags, texOffset);
    gSPVertexDKR(gObjectCurrDisplayList++, OS_K0_TO_PHYSICAL(verts), numVertices, 0);
    gSPPolygon(gObjectCurrDisplayList++, OS_K0_TO_PHYSICAL(triangles), numTriangles, hasTexture);
    mtx_pop(&gObjectCurrDisplayList);
}

/**
 * A few objects use unconventional means to render. They are handled here.
 */
void render_3d_misc(Object *obj) {
    f32 scaleY;
    Object_Fish *fish;
    Object_Butterfly *butterfly;
    CharacterFlagModel *characterFlagModel;

    switch (obj->behaviorId) {
        case BHV_CHARACTER_FLAG:
            if (obj->properties.characterFlag.characterID >= 0) {
                characterFlagModel = obj->characterFlagModel;
                render_misc_model(obj, characterFlagModel->vertices, 4, characterFlagModel->triangles, 2,
                                  characterFlagModel->texture,
                                  RENDER_ANTI_ALIASING | RENDER_Z_COMPARE | RENDER_FOG_ACTIVE, 0, 1.0f);
            }
            break;
        case BHV_BUTTERFLY:
            butterfly = obj->butterfly;
            render_misc_model(obj, &butterfly->vertices[butterfly->unkFC * 6], 6, butterfly->triangles, 8,
                              butterfly->texture, RENDER_Z_COMPARE | RENDER_FOG_ACTIVE, 0, 1.0f);
            break;
        case BHV_FISH:
            fish = obj->fish;
            scaleY = obj->level_entry->fish.unkD;
            scaleY *= 0.01f;
            render_misc_model(obj, &fish->vertices[fish->unkFC * 6], 6, fish->triangles, 8, fish->texture,
                              RENDER_Z_COMPARE | RENDER_FOG_ACTIVE | RENDER_CUTOUT, 0, scaleY);
            break;
        case BHV_BOOST:
            if (obj->properties.common.unk0 && (obj->boost->unk70 > 0 || obj->boost->unk74 > 0.0f)) {
                func_800135B8(obj);
            }
            break;
    }
}

/**
 * Render an object as a billboard.
 * A few tweaks are made depending on the behaviour ID of the object.
 * A few exceptions will not call to render a billboarded sprite.
 */
void render_3d_billboard(Object *obj) {
    s32 intensity;
    s32 flags;
    s32 alpha;
    s32 hasPrimCol;
    s32 hasEnvCol;
    ObjectTransformExt objTrans;
    Object *bubbleTrap;
    Sprite *sprite;

    intensity = 255;
    hasPrimCol = FALSE;
    hasEnvCol = FALSE;
    flags = obj->trans.flags | RENDER_Z_UPDATE | RENDER_FOG_ACTIVE;
    if (obj->shading != NULL) {
        hasPrimCol = TRUE;
        hasEnvCol = TRUE;
        intensity = obj->shading->unk0 * 255.0f;
    }

    if (obj->behaviorId == BHV_BOMB_EXPLOSION) {
        //!@bug Never true, because the type is u8.
        if (obj->opacity > 255) {
            obj->opacity = obj->properties.bombExplosion.opacity & 0xFF;
        } else {
            obj->opacity = (obj->opacity * (obj->properties.bombExplosion.opacity & 0xFF)) >> 8;
        }
    }

    alpha = obj->opacity;
    if (alpha > 255) {
        alpha = 255;
    }

    // If the behavior is a wizpig ghost, then halve it's transparency.
    if (obj->behaviorId == BHV_WIZPIG_GHOSTS) {
        alpha >>= 1;
    }

    if (alpha < 255) {
        flags |= RENDER_SEMI_TRANSPARENT;
        hasPrimCol = TRUE;
    }
    if ((obj->behaviorId == 5) && (obj->trans.scale == 6.0f)) {
        gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, (intensity * 3) >> 2, intensity, intensity >> 1, alpha);
        hasPrimCol = TRUE;
    } else if (obj->behaviorId == BHV_WIZPIG_GHOSTS) { // If the behavior is a wizpig ghost
        gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 150, 230, 255, alpha);
        hasPrimCol = TRUE;
    } else if (hasPrimCol || alpha < 255) {
        gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, intensity, intensity, intensity, alpha);
    } else {
        gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
    }
    if (hasEnvCol) {
        gDPSetEnvColor(gObjectCurrDisplayList++, obj->shading->lightR, obj->shading->lightG, obj->shading->lightB,
                       obj->shading->lightIntensity);
    } else if (obj->behaviorId == BHV_LAVA_SPURT) {
        hasEnvCol = TRUE;
        gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 0, 255);
    } else {
        gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 255, 0);
    }
    sprite = obj->sprites[obj->modelIndex];
    bubbleTrap = NULL;
    if (obj->behaviorId == BHV_FIREBALL_OCTOWEAPON_2) {
        bubbleTrap = obj->properties.fireball.obj;
        if (obj->properties.fireball.timer > 0) {
            bubbleTrap = obj;
        }
    }

    // 5 = OilSlick, SmokeCloud, Bomb, BubbleWeapon
    if (bubbleTrap != NULL || !(obj->behaviorId != BHV_WEAPON || obj->weapon->weaponID != WEAPON_BUBBLE_TRAP)) {
        objTrans.trans.rotation.z_rotation = 0;
        objTrans.trans.rotation.x_rotation = 0;
        objTrans.trans.rotation.y_rotation = 0;
        objTrans.trans.scale = obj->trans.scale;
        objTrans.trans.x_position = 0.0f;
        objTrans.trans.z_position = 0.0f;
        objTrans.trans.y_position = 12.0f;
        objTrans.animFrame = obj->animFrame;
        objTrans.unk1A = 32;
        if (bubbleTrap == NULL) {
            bubbleTrap = obj->weapon->target;
            if (bubbleTrap == NULL) {
                bubbleTrap = obj;
            }
        }
        render_bubble_trap(&bubbleTrap->trans, sprite, (Object *) &objTrans,
                           RENDER_Z_COMPARE | RENDER_SEMI_TRANSPARENT | RENDER_Z_UPDATE);
    } else {
        render_sprite_billboard(&gObjectCurrDisplayList, &gObjectCurrMatrix, &gObjectCurrVertexList, obj, sprite,
                                flags);
    }
    if (hasPrimCol) {
        gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
    }
    if (hasEnvCol) {
        gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 255, 0);
    }
}

/**
 * Renders a 3D object, with support for vehicle part entities as part of the process.
 * Loads materials, and sets environment and/or primitive colours based on the material type.
 * Computes the view matrix for the model, and calls a function to draw meshes.
 * Loops through racers to find vehicle parts, which are wheels and propellers.
 */
void render_3d_model(Object *obj) {
    s32 i;
    s32 intensity;
    s32 opacity;
    s32 vertOffset;
    s32 attachPointCount;
    s32 hasOpacity;
    s32 hasLighting;
    s32 flags;
    s32 meshBatch;
    s32 cicFailed;
    f32 vtxX;
    f32 vtxY;
    f32 vtxZ;
    s8 index;
    s8 isCargo;
    Object *loopObj;
    ModelInstance *modInst;
    Object_Racer *racerObj;
    ObjectModel *objModel;
    Sprite *something;

    modInst = obj->modelInstances[obj->modelIndex];
    if (modInst != NULL) {
        objModel = modInst->objModel;
        hasOpacity = FALSE;
        hasLighting = FALSE;
        intensity = 255;
        if (obj->shading != NULL) {
            intensity = (s32) (obj->shading->unk0 * 255.0f * gCurrentLightIntensity);
            hasOpacity = TRUE;
            hasLighting = TRUE;
        }
        if (obj->behaviorId == BHV_RACER) {
            racerObj = obj->racer;
            object_do_player_tumble(obj);
        } else {
            racerObj = NULL;
        }
        if (modInst->animUpdateTimer <= 0) {
            obj->curVertData = modInst->vertices[modInst->animationTaskNum];
            if (modInst->modelType == MODELTYPE_ANIMATED) {
                obj_animate(obj);
            }
            if (modInst->modelType != MODELTYPE_BASIC && objModel->normals != NULL) {
                flags = TRUE;
                if (racerObj != NULL && racerObj->vehicleID < VEHICLE_BOSSES &&
                    racerObj->playerIndex == PLAYER_COMPUTER) {
                    flags = FALSE;
                }
                if (cam_get_viewport_layout() != VIEWPORT_LAYOUT_1_PLAYER) {
                    flags = FALSE;
                }
                obj->curVertData = modInst->vertices[modInst->animationTaskNum];
                if (obj->behaviorId == BHV_UNK_3F) { // 63 = stopwatchicon, stopwatchhand
                    obj_shade_fancy(objModel, obj, 0, gCurrentLightIntensity);
                } else if (flags) {
                    obj_shade_fancy(objModel, obj, -1, gCurrentLightIntensity);
                } else {
                    obj_shade_fast(objModel, obj, gCurrentLightIntensity);
                }
            }
            // Set the animation ticker for non player racers to 2, making them animate at half the framerate.
            if ((racerObj != NULL) && (racerObj->playerIndex == PLAYER_COMPUTER) &&
                (racerObj->vehicleID < VEHICLE_BOSSES)) {
                modInst->animUpdateTimer = 2;
            } else {
                modInst->animUpdateTimer = 1;
            }
        }
        obj->curVertData = modInst->vertices[modInst->animationTaskNum];
        if (obj->behaviorId == BHV_DOOR) {
            obj_door_number(objModel, obj);
        }
        if (objModel->texOffsetUpdateRate && objModel->unk50 > 0) {
            obj_tex_animate(obj, objModel->texOffsetUpdateRate);
            modInst->objModel->texOffsetUpdateRate = 0;
        }
        mtx_cam_push(&gObjectCurrDisplayList, &gObjectCurrMatrix, &obj->trans, gObjectModelScaleY, 0.0f);
        vertOffset = FALSE;
        if (racerObj != NULL) {
            object_undo_player_tumble(obj);
            if (obj->animationID == 0 || racerObj->vehicleID >= VEHICLE_BOSSES) {
                mtx_head_push(&gObjectCurrDisplayList, &gObjectCurrMatrix, modInst, racerObj->headAngle);
                vertOffset = TRUE;
            } else {
                racerObj->headAngle = 0;
            }
        }
        opacity = obj->opacity;
        if (opacity > 255) {
            opacity = 255;
        }
        // If the behavior is a water zipper, then halve it's transparency.
        if (obj->behaviorId == BHV_ZIPPER_WATER) {
            opacity >>= 1;
        }
        if (opacity < 255) {
            hasOpacity = TRUE;
        }
        if (hasLighting) {
            gDPSetEnvColor(gObjectCurrDisplayList++, obj->shading->lightR, obj->shading->lightG, obj->shading->lightB,
                           obj->shading->lightIntensity);
        } else {
            gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 255, 0);
        }
        if (obj->header->directionalPointLighting) {
            gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, obj->shading->shadowR, obj->shading->shadowG,
                            obj->shading->shadowB, opacity);
            directional_lighting_on();
        } else if (hasOpacity) {
            gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, intensity, intensity, intensity, opacity);
        } else {
            gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
        }
        if (opacity < 255) {
            meshBatch = render_mesh(objModel, obj, 0, RENDER_SEMI_TRANSPARENT, vertOffset);
        } else {
            meshBatch = render_mesh(objModel, obj, 0, RENDER_NONE, vertOffset);
        }
        if (obj->header->directionalPointLighting) {
            if (hasOpacity) {
                gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, intensity, intensity, intensity, opacity);
            } else {
                gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            }
            directional_lighting_off();
        }
        if (obj->attachPoints != NULL) {
            attachPointCount = obj->attachPoints->count;
            if (racerObj != NULL && racerObj->vehicleID == VEHICLE_FLYING_CAR) {
                attachPointCount = 0;
            }
            for (i = 0; i < attachPointCount; i++) {
                loopObj = obj->attachPoints->obj[i];
                if (!(loopObj->trans.flags & OBJ_FLAGS_INVISIBLE)) {
                    index = obj->attachPoints->unk2C[i];
                    if (index >= 0 && index < objModel->unk18) {
                        something = loopObj->sprites[loopObj->modelIndex];
                        vtxX = obj->curVertData[objModel->unk14[index]].x;
                        vtxY = obj->curVertData[objModel->unk14[index]].y;
                        vtxZ = obj->curVertData[objModel->unk14[index]].z;
                        loopObj->trans.x_position += vtxX;
                        loopObj->trans.y_position += vtxY;
                        loopObj->trans.z_position += vtxZ;
                        if (loopObj->header->modelType == OBJECT_MODEL_TYPE_SPRITE_BILLBOARD) {
                            flags = (RENDER_Z_COMPARE | RENDER_FOG_ACTIVE | RENDER_Z_UPDATE);
                        } else {
                            flags = (RENDER_Z_COMPARE | RENDER_FOG_ACTIVE | RENDER_Z_UPDATE | RENDER_ANTI_ALIASING);
                        }
                        if (opacity < 255) {
                            flags |= RENDER_SEMI_TRANSPARENT;
                        }
#ifdef ANTI_TAMPER
                        cicFailed = FALSE;
                        // Anti-Piracy check
                        if (osCicId != CIC_ID) {
                            cicFailed = TRUE;
                        }
                        if (!cicFailed) {
#else
                        if (1) {
#endif
                            // In this instance, cargo refers to the eggs in the fire mountain challenge.
                            isCargo = (loopObj->trans.flags & OBJ_FLAGS_UNK_0080 && attachPointCount == 3);
                            if (racerObj != NULL && racerObj->transparency < 255) {
                                isCargo = FALSE;
                            }
                            if (isCargo) {
                                func_80012C98(&gObjectCurrDisplayList);
                                gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 255, 0);
                                gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, intensity, intensity, intensity,
                                                opacity);
                            }
                            loopObj->properties.common.unk0 =
                                render_sprite_billboard(&gObjectCurrDisplayList, &gObjectCurrMatrix,
                                                        &gObjectCurrVertexList, loopObj, something, flags);
                            if (isCargo) {
                                gSPSelectMatrixDKR(gObjectCurrDisplayList++, G_MTX_DKR_INDEX_0);
                                func_80012CE8(&gObjectCurrDisplayList);
                            }
                        }
                        loopObj->trans.x_position -= vtxX;
                        loopObj->trans.y_position -= vtxY;
                        loopObj->trans.z_position -= vtxZ;
                    }
                }
            }
        }
        // This section draws the egg sprite being held by a racer.
        if (racerObj != NULL) {
            loopObj = racerObj->held_obj;
            if (loopObj != NULL) {
                index = obj->header->unk58;
                if (index >= 0 && index < objModel->unk18) {
                    flags = (RENDER_Z_COMPARE | RENDER_FOG_ACTIVE | RENDER_Z_UPDATE);
                    something = loopObj->sprites[loopObj->modelIndex];
                    vtxX = obj->curVertData[objModel->unk14[index]].x;
                    vtxY = obj->curVertData[objModel->unk14[index]].y;
                    vtxZ = obj->curVertData[objModel->unk14[index]].z;
                    loopObj->trans.x_position += (vtxX - loopObj->trans.x_position) * 0.25;
                    loopObj->trans.y_position += (vtxY - loopObj->trans.y_position) * 0.25;
                    loopObj->trans.z_position += (vtxZ - loopObj->trans.z_position) * 0.25;
                    if (loopObj->header->modelType == OBJECT_MODEL_TYPE_SPRITE_BILLBOARD) {
                        render_sprite_billboard(&gObjectCurrDisplayList, &gObjectCurrMatrix, &gObjectCurrVertexList,
                                                loopObj, something, flags);
                    }
                }
            }
        }
        if (meshBatch != -1) {
            if (obj->header->directionalPointLighting) {
                gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, obj->shading->shadowR, obj->shading->shadowG,
                                obj->shading->shadowB, opacity);
                directional_lighting_on();
            }
            render_mesh(objModel, obj, meshBatch, RENDER_SEMI_TRANSPARENT, vertOffset);
            if (obj->header->directionalPointLighting) {
                directional_lighting_off();
            }
        }
        if (hasOpacity || obj->header->directionalPointLighting) {
            gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
        }
        if (hasLighting) {
            gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 255, 0);
        }
        mtx_pop(&gObjectCurrDisplayList);
    }
}

void func_80012C30(void) {
    D_8011ADA4 = 0;
}

void func_80012C3C(Gfx **dList) {
    s32 i;
    for (i = 0; i < D_8011ADA4; i++) {
        gSPDisplayList((*dList)++, D_8011AD78[i]);
    }
}

void func_80012C98(Gfx **dList) {
    if (D_8011ADA4 < 9) {
        gSPNoOp((*dList)++); // Placeholder instruction?
        D_8011AD78[D_8011ADA4] = *dList;
    }
}

void func_80012CE8(Gfx **dList) {
    if (D_8011ADA4 < 9) {
        gSPEndDisplayList((*dList)++);
        gSPBranchList(D_8011AD78[D_8011ADA4] - 1, *dList);
        D_8011ADA4++;
    }
}

/**
 * Update the object stack trace, set the draw pointers, then begin rendering the object.
 * Official Name: objPrintObject
 */
void render_object(Gfx **dList, Mtx **mtx, Vertex **verts, Object *obj) {
    f32 scale;
    if (obj->trans.flags & (OBJ_FLAGS_INVISIBLE | OBJ_FLAGS_SHADOW_ONLY)) {
        return;
    }
    update_object_stack_trace(OBJECT_DRAW, obj->objectID);
    gObjectCurrDisplayList = *dList;
    gObjectCurrMatrix = *mtx;
    gObjectCurrVertexList = *verts;
    scale = obj->trans.scale;
    render_object_parts(obj);
    obj->trans.scale = scale;
    *dList = gObjectCurrDisplayList;
    *mtx = gObjectCurrMatrix;
    *verts = gObjectCurrVertexList;
    update_object_stack_trace(OBJECT_DRAW, OBJECT_CLEAR);
}

/**
 * Official Name: objDoPlayerTumble
 */
void object_do_player_tumble(Object *this) {
    UNUSED s32 unused1;
    Object_Racer *sp_20;
    f32 tmp_f2;
    f32 offsetY;
    f32 tmp_f0;
    f32 temp;

    if (this->behaviorId == BHV_RACER) {

        sp_20 = this->racer;
        this->trans.rotation.y_rotation += sp_20->y_rotation_offset;
        this->trans.rotation.x_rotation += sp_20->x_rotation_offset;
        this->trans.rotation.z_rotation += sp_20->z_rotation_offset;
        offsetY = 0.0f;
        if (sp_20->vehicleIDPrev < VEHICLE_BOSSES) {

            offsetY = coss_f(sp_20->z_rotation_offset);
            tmp_f2 = offsetY;
            tmp_f0 = coss_f(sp_20->x_rotation_offset - sp_20->unk166) * tmp_f2;

            tmp_f0 = (tmp_f0 < 0.0f) ? 0.0f : tmp_f0 * tmp_f0;

            temp = (1.0f - tmp_f0) * 24.0f + sp_20->unkD0;
            if (0) {} // Fakematch
            offsetY = temp;
        }
        this->trans.y_position = this->trans.y_position + offsetY;
        gObjectOffsetY = offsetY;
    }
}

/**
 * Official Name: objUndoPlayerTumble
 */
void object_undo_player_tumble(Object *obj) {
    if (obj->behaviorId == BHV_RACER) {
        Object_Racer *racer = obj->racer;
        obj->trans.rotation.y_rotation -= racer->y_rotation_offset;
        obj->trans.rotation.x_rotation -= racer->x_rotation_offset;
        obj->trans.rotation.z_rotation -= racer->z_rotation_offset;
        obj->trans.y_position -= gObjectOffsetY;
    }
}

void set_temp_model_transforms(Object *obj) {
    s32 batchNum;
    ObjectModel *objModel;
    s32 var_v1;
    ModelInstance **modInstList;
    ModelInstance *modInst;
    u8 *bossAsset;
    f32 var_f0;
    u8 *var_a1;
    f32 ret2;
    UNUSED s32 pad;
    Object_Racer *objRacer;
    f32 ret1;
    s32 firstNonEmptyModelIndex;
    s32 modelIndex;
    s32 numberOfModels;

    ret1 = 1.0f;
    ret2 = 1.0f;
    if (!(obj->trans.flags & OBJ_FLAGS_PARTICLE)) {
        if (obj->header->behaviorId == BHV_RACER) {
            objRacer = obj->racer;
            objRacer->unk201 = 30;
            if (objRacer->unk206 > 0) {
                ret2 = 1.0f - (objRacer->unk206 * 0.05f);
                if (ret2 < 0.2f) {
                    ret2 = 0.2f;
                }
            }
            if (objRacer->playerIndex != PLAYER_COMPUTER && objRacer->raceFinished) {
                modelIndex = 0;
                batchNum = 0;
            } else {
                if (obj->behaviorId == BHV_TIMETRIAL_GHOST) { // Ghost Object?
                    modelIndex = 1;
                    batchNum = 0;
                } else {
                    // Loads vehicles between VEHICLE_TRICKY and VEHICLE_SMOKEY. So all boss vehicles except wizpig.
                    batchNum = objRacer->vehicleID;
                    if (objRacer->vehicleID >= NUMBER_OF_PLAYER_VEHICLES) {
                        batchNum = 0;
                    }
                    bossAsset = (u8 *) get_misc_asset(batchNum + VEHICLE_BOSSES); // 40 bytes of data u8[8][5]?
                    batchNum = 0;
                    bossAsset += cam_get_viewport_layout() * 10;
                    if (get_current_viewport() != objRacer->playerIndex) {
                        bossAsset += 5;
                    }
                    var_f0 = obj->distanceToCamera;
                    var_v1 = (s32) var_f0 >> 3;
                    if (obj->distanceToCamera < 0.0f) {
                        var_f0 = 0.0f;
                    } else if (var_f0 > 3500.0f) {
                        var_f0 = 3500.0f;
                    }
                    var_f0 /= 2700.0f;
                    var_f0 += 1.0f;
                    obj->trans.scale *= var_f0;
                    var_v1 *= ((f32 *) get_misc_asset(ASSET_MISC_4))[objRacer->characterId];
                    // ASSET_MISC_4 is just 10 floats of 1.0f. One for each playable character.
                    if (var_v1 < -50) {
                        modelIndex = 5;
                    } else {
                        var_v1 >>= 1;
                        if (var_v1 < 0) {
                            var_v1 = 0;
                        }

                        if (var_v1 < bossAsset[0]) {
                            modelIndex = 0;
                        } else if (var_v1 < bossAsset[1]) {
                            modelIndex = 1;
                        } else if (var_v1 < bossAsset[2]) {
                            modelIndex = 2;
                        } else if (var_v1 < bossAsset[3]) {
                            modelIndex = 3;
                        } else if (var_v1 < bossAsset[4]) {
                            modelIndex = 4;
                        } else {
                            modelIndex = 5;
                        }
                    }
                }
            }

            firstNonEmptyModelIndex = 0;
            modInstList = &obj->modelInstances[firstNonEmptyModelIndex];

            while (*modInstList == NULL) {
                firstNonEmptyModelIndex++;
                modInstList++;
            }

            numberOfModels = obj->header->numberOfModelIds - 1;
            modInstList = &obj->modelInstances[numberOfModels];

            while (*modInstList == NULL) {
                numberOfModels--;
                modInstList--;
            }

            if (modelIndex < firstNonEmptyModelIndex) {
                modelIndex = firstNonEmptyModelIndex;
            }
            if (numberOfModels < modelIndex) {
                modelIndex = numberOfModels;
            }
            obj->modelIndex = modelIndex;
            if ((obj->shading != NULL) && (obj->shading->unk0 < 0.6f)) {
                objRacer->lightFlags |= RACER_LIGHT_NIGHT;
            } else {
                objRacer->lightFlags &= ~RACER_LIGHT_NIGHT;
            }
            modelIndex = objRacer->lightFlags & RACER_LIGHT_TIMER;
            modInst = obj->modelInstances[obj->modelIndex];
            objModel = modInst->objModel;
            if (modelIndex != 0) {
                modelIndex--;
                if (objRacer->lightFlags & RACER_LIGHT_BRAKE) {
                    modelIndex += 1;
                    objRacer->lightFlags = (objRacer->lightFlags & ~RACER_LIGHT_UNK10) | RACER_LIGHT_UNK20;
                } else if (objRacer->lightFlags & RACER_LIGHT_NIGHT) {
                    modelIndex += 3;
                    objRacer->lightFlags = (objRacer->lightFlags & ~RACER_LIGHT_UNK20) | RACER_LIGHT_UNK10;
                } else if (objRacer->lightFlags & RACER_LIGHT_UNK20) {
                    modelIndex += 1;
                } else {
                    modelIndex += 3;
                }
            }
            modelIndex *= 4;
            for (batchNum = 0; batchNum < objModel->numberOfBatches; batchNum++) {
                if ((objModel->batches[batchNum].flags & 0x810000) == RENDER_TEX_ANIM) {
                    objModel->batches[batchNum].texOffset = modelIndex;
                }
            }
            obj->trans.x_position += objRacer->carBobX;
            obj->trans.y_position += objRacer->carBobY;
            obj->trans.z_position += objRacer->carBobZ;
            ret1 = objRacer->stretch_height;
        } else if (obj->behaviorId == BHV_FROG) {
            ret1 = obj->frog->scaleY;
        }
    }
    gObjectModelScaleY = ret1;
    gCurrentLightIntensity = ret2;
}

/**
 * Determine which model type the object is using, then call the related function to render it.
 * Beforehand, call a function to apply a temporary transformation, mostly for racers.
 * Afterwards, undo that.
 */
void render_object_parts(Object *obj) {
    set_temp_model_transforms(obj);
    if (obj->trans.flags & OBJ_FLAGS_PARTICLE) {
        render_particle((Particle *) obj, &gObjectCurrDisplayList, &gObjectCurrMatrix, &gObjectCurrVertexList,
                        PARTICLE_UNK_FLAG_8000);
    } else {
        if (obj->header->modelType == OBJECT_MODEL_TYPE_3D_MODEL) {
            render_3d_model(obj);
        } else if (obj->header->modelType == OBJECT_MODEL_TYPE_SPRITE_BILLBOARD) {
            render_3d_billboard(obj);
        } else if (obj->header->modelType == OBJECT_MODEL_TYPE_MISC) {
            render_3d_misc(obj);
        }
    }
    unset_temp_model_transforms(obj);
}

/**
 * After rendering, sets the object position back to normal.
 */
void unset_temp_model_transforms(Object *obj) {
    if (!(obj->trans.flags & OBJ_FLAGS_PARTICLE) && obj->header->behaviorId == BHV_RACER) {
        obj->trans.x_position -= obj->racer->carBobX;
        obj->trans.y_position -= obj->racer->carBobY;
        obj->trans.z_position -= obj->racer->carBobZ;
    }
}

// Renders the boost graphics.
void func_800135B8(Object *boostObj) {
    Vertex *vtx;
    Triangle *tri;
    ObjectTransform_800135B8 objTransform;
    Object_Boost_Inner *boostData;
    Object_Boost *boost;
    Object_Boost *asset;
    s32 hasTexture;
    s32 racerIndex;

    racerIndex = (boostObj->properties.boost.racerIndex) & 0xF;
    boost = boostObj->boost;
    switch (D_8011B048[racerIndex]) {
        case VEHICLE_CAR:
            boostData = &boost->carBoostData;
            break;
        case VEHICLE_HOVERCRAFT:
            boostData = &boost->hovercraftBoostData;
            break;
        default:
            boostData = &boost->flyingBoostData;
            break;
    }
    asset = (Object_Boost *) get_misc_asset(ASSET_MISC_20);
    asset = &asset[D_8011B058[racerIndex]];
    object_do_player_tumble(boostObj->properties.boost.obj);
    mtx_cam_push(&gObjectCurrDisplayList, &gObjectCurrMatrix, &boostObj->properties.boost.obj->trans, 1.0f, 0.0f);
    object_undo_player_tumble(boostObj->properties.boost.obj);
    objTransform.trans.x_position = boostData->position.x;
    objTransform.trans.y_position = boostData->position.y;
    objTransform.trans.z_position = boostData->position.z;
    objTransform.trans.scale = boostData->unkC + (boostData->unk10 * coss_f(boost->unk72 << 12));
    if (boost->unk70 < 2) {
        objTransform.trans.scale *= boost->unk74;
    }
    if (D_8011B058[racerIndex] != 0) {
        objTransform.trans.scale *= 1.15f;
    }
    objTransform.trans.rotation.z_rotation = 0;
    objTransform.trans.rotation.x_rotation = 0;
    objTransform.trans.rotation.y_rotation = 0;
    objTransform.unk18 = 0;
    gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
    gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 255, 0);
    render_sprite_billboard(&gObjectCurrDisplayList, &gObjectCurrMatrix, &gObjectCurrVertexList,
                            (Object *) &objTransform, asset->sprite,
                            (RENDER_Z_COMPARE | RENDER_FOG_ACTIVE | RENDER_Z_UPDATE));
    if (boost->unk70 == 2) {
        material_set(&gObjectCurrDisplayList, asset->tex,
                     (RENDER_Z_COMPARE | RENDER_SEMI_TRANSPARENT | RENDER_FOG_ACTIVE), 0);
        if (asset->tex != NULL) {
            hasTexture = TRUE;
        } else {
            hasTexture = FALSE;
        }

        vtx = &gBoostVerts[gBoostVertFlip][(boostObj->properties.boost.indexes >> 14) & 0x3FFF];
        tri = &gBoostTris[gBoostVertFlip][boostObj->properties.boost.indexes & 0x3FFF];
        gSPVertexDKR(gObjectCurrDisplayList++, OS_K0_TO_PHYSICAL(vtx), BOOST_VERT_COUNT, 0);
        gSPPolygon(gObjectCurrDisplayList++, OS_K0_TO_PHYSICAL(tri), BOOST_TRI_COUNT, hasTexture);
    }
    mtx_pop(&gObjectCurrDisplayList);
}

/**
 * Render the bubble trap weapon.
 */
void render_bubble_trap(ObjectTransform *trans, Sprite *gfxData, Object *obj, s32 flags) {
    f32 x;
    f32 y;
    f32 z;
    Camera *cameraSegment;
    f32 dist;

    vec3f_rotate(&trans->rotation, &obj->trans.position);
    obj->trans.x_position += trans->x_position;
    obj->trans.y_position += trans->y_position;
    obj->trans.z_position += trans->z_position;
    cameraSegment = cam_get_active_camera();
    x = cameraSegment->trans.x_position - obj->trans.x_position;
    y = cameraSegment->trans.y_position - obj->trans.y_position;
    z = cameraSegment->trans.z_position - obj->trans.z_position;
    dist = sqrtf((x * x) + (y * y) + (z * z));
    if (dist > 0.0) {
        dist = obj->numActiveEmitters / dist;
        x *= dist;
        y *= dist;
        z *= dist;
    }
    obj->trans.x_position += x;
    obj->trans.y_position += y;
    obj->trans.z_position += z;
    render_sprite_billboard(&gObjectCurrDisplayList, &gObjectCurrMatrix, &gObjectCurrVertexList, obj, gfxData, flags);
}

/**
 * Get the racer object data, and fetch set visual shield properties based on that racer.
 * Afterwards, render the graphics with opacity scaling with the fadetimer.
 */
void render_racer_shield(Gfx **dList, Mtx **mtx, Vertex **vtxList, Object *obj) {
    Object_Racer *racer;
    ModelInstance *modInst;
    ObjectModel *mdl;
    RacerShieldGfx *shield;
    s32 shieldType;
    s32 vehicleID;
    s32 racerIndex;
    f32 scale;
    f32 shear;

    racer = obj->racer;
    if (racer->shieldTimer > 0 && gShieldEffectObject != NULL) {
        gObjectCurrDisplayList = *dList;
        gObjectCurrMatrix = *mtx;
        gObjectCurrVertexList = *vtxList;
        racerIndex = racer->racerIndex;
        if (racerIndex > NUMBER_OF_CHARACTERS) {
            racerIndex = 0;
        }
        vehicleID = racer->vehicleID;
        if (vehicleID >= NUMBER_OF_PLAYER_VEHICLES) {
            vehicleID = VEHICLE_CAR;
        }
        shield = (RacerShieldGfx *) get_misc_asset(ASSET_MISC_SHIELD_DATA);
        vehicleID = (vehicleID * 10) + racerIndex;
        shield = shield + vehicleID;
        gShieldEffectObject->trans.x_position = shield->x_position;
        gShieldEffectObject->trans.y_position = shield->y_position;
        gShieldEffectObject->trans.z_position = shield->z_position;
        gShieldEffectObject->trans.y_position += shield->y_offset * sins_f(gShieldSineTime[racerIndex] * 0x200);
        shear = (coss_f(gShieldSineTime[racerIndex] * 0x400) * 0.05f) + 0.95f;
        gShieldEffectObject->trans.scale = shield->scale * shear;
        shear = shear * shield->turnSpeed;
        gShieldEffectObject->trans.rotation.y_rotation = gShieldSineTime[racerIndex] * 0x800;
        gShieldEffectObject->trans.rotation.x_rotation = 0x800;
        gShieldEffectObject->trans.rotation.z_rotation = 0;
        shieldType = racer->shieldType;
        if (shieldType != SHIELD_NONE) {
            shieldType--;
        }
        if (shieldType > SHIELD_LEVEL3 - 1) {
            shieldType = SHIELD_LEVEL3 - 1;
        }
        scale = ((f32) shieldType * 0.1) + 1.0f;
        gShieldEffectObject->trans.scale *= scale;
        shear *= scale;
        modInst = gShieldEffectObject->modelInstances[shieldType];
        mdl = modInst->objModel;
        gShieldEffectObject->curVertData = modInst->vertices[modInst->animationTaskNum];
        gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 255, 0);
        if (racer->shieldTimer < 64) {
            gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, racer->shieldTimer * 4);
        } else {
            gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
        }
        mtx_shear_push(&gObjectCurrDisplayList, &gObjectCurrMatrix, gShieldEffectObject, obj, shear);
        render_mesh(mdl, gShieldEffectObject, 0, RENDER_SEMI_TRANSPARENT, 0);
        gSPSelectMatrixDKR(gObjectCurrDisplayList++, G_MTX_DKR_INDEX_0);
        if (racer->shieldTimer < 64) {
            gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
        }
        *dList = gObjectCurrDisplayList;
        *mtx = gObjectCurrMatrix;
        *vtxList = gObjectCurrVertexList;
    }
}

/**
 * Get the racer object data, and fetch set visual magnet properties based on that racer.
 * Afterwards, render the graphics with opacity set by the properties.
 */
void render_racer_magnet(Gfx **dList, Mtx **mtx, Vertex **vtxList, Object *obj) {
    Object_Racer *racer;
    ModelInstance *modInst;
    ObjectModel *mdl;
    f32 *magnet;
    s32 vehicleID;
    s32 racerIndex;
    s32 opacity;
    f32 shear;
    UNUSED s32 pad;

    racer = obj->racer;
    racerIndex = racer->racerIndex;
    if (gRacerFXData[racerIndex].unk3 != 0) {
        if (gMagnetEffectObject != NULL) {
            gObjectCurrDisplayList = *dList;
            gObjectCurrMatrix = *mtx;
            gObjectCurrVertexList = *vtxList;
            magnet = (f32 *) get_misc_asset(ASSET_MISC_MAGNET_DATA);
            vehicleID = racer->vehicleID;
            if (vehicleID < VEHICLE_CAR || vehicleID >= NUMBER_OF_PLAYER_VEHICLES) {
                vehicleID = VEHICLE_CAR;
            }
            magnet = &magnet[vehicleID * 5];
            racerIndex = racer->racerIndex;
            if (racerIndex > NUMBER_OF_CHARACTERS) {
                racerIndex = 0;
            }
            gMagnetEffectObject->trans.x_position = magnet[0];
            gMagnetEffectObject->trans.y_position = magnet[1];
            gMagnetEffectObject->trans.z_position = magnet[2];
            magnet += 3;
            shear = (coss_f((gRacerFXData[racerIndex].unk1 * 0x400)) * 0.02f) + 0.98f;
            gMagnetEffectObject->trans.scale = magnet[0] * shear;
            magnet += 1;
            shear = magnet[0] * shear;
            gMagnetEffectObject->trans.rotation.y_rotation = gRacerFXData[racerIndex].unk2 * 0x1000;
            gMagnetEffectObject->trans.rotation.x_rotation = 0;
            gMagnetEffectObject->trans.rotation.z_rotation = 0;
            modInst = gMagnetEffectObject->modelInstances[0];
            mdl = modInst->objModel;
            gMagnetEffectObject->curVertData = modInst->vertices[modInst->animationTaskNum];
            opacity = ((gRacerFXData[racerIndex].unk1 * 8) & 0x7F) + 0x80;
            gfx_init_basic_xlu(&gObjectCurrDisplayList, DRAW_BASIC_2CYCLE, COLOUR_RGBA32(255, 255, 255, opacity),
                               gMagnetColours[racer->magnetModelID]);
            mtx_shear_push(&gObjectCurrDisplayList, &gObjectCurrMatrix, gMagnetEffectObject, obj, shear);
            gObjectTexAnim = TRUE;
            render_mesh(mdl, gMagnetEffectObject, 0, RENDER_SEMI_TRANSPARENT, 0);
            gObjectTexAnim = FALSE;
            gSPSelectMatrixDKR(gObjectCurrDisplayList++, G_MTX_DKR_INDEX_0);
            gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            rendermode_reset(&gObjectCurrDisplayList);
            *dList = gObjectCurrDisplayList;
            *mtx = gObjectCurrMatrix;
            *vtxList = gObjectCurrVertexList;
        }
    }
}

void func_80014090(Object *obj, s32 arg1) {
    ObjectHeader *objHeader;
    s16 width;
    s16 height;
    s32 i;
    s32 j;
    s32 k;
    s32 end;
    s16 objHeader72;
    s16 objHeader73;
    ObjectModel *objMdl;
    ModelInstance *modInst;
    TextureInfo *texInfo;
    Triangle *tri;
    s16 temp;
    s16 temp2;
    s16 newU1;
    s16 newU2;
    s16 newV1;
    s16 newV2;

    objHeader = obj->header;
    objHeader73 = objHeader->unk73;
    objHeader72 = objHeader->unk72;
    temp = (s16) (objHeader->unk74 * arg1);
    temp2 = (s16) (objHeader->unk75 * arg1);
    if ((objHeader73 == 0xFF) || (objHeader73 < objHeader->numberOfModelIds)) {
        if (objHeader73 == 0xFF) {
            end = objHeader->numberOfModelIds;
            objHeader73 = 0;
        } else {
            end = objHeader73 + 1;
        }
        for (i = objHeader73; i < end; i++) {
            modInst = obj->modelInstances[i];
            objMdl = modInst->objModel;
            if (objHeader72 < objMdl->numberOfTextures) {
                width = objMdl->textures[objHeader72].texture->width << 5;
                height = objMdl->textures[objHeader72].texture->height << 5;
                for (j = 0; j < objMdl->numberOfBatches; j++) {
                    if (objHeader72 == objMdl->batches[j].textureIndex) {
                        for (k = objMdl->batches[j].facesOffset; k < objMdl->batches[j + 1].facesOffset; k++) {
                            tri = &objMdl->triangles[k];
                            newU1 = (tri->uv1.u - tri->uv0.u);
                            newV1 = (tri->uv1.v - tri->uv0.v);
                            newU2 = (tri->uv2.u - tri->uv0.u);
                            newV2 = (tri->uv2.v - tri->uv0.v);
                            // s16 casts required
                            tri->uv0.u = (tri->uv0.u + temp) & (s16) (width - 1);
                            tri->uv0.v = (tri->uv0.v + temp2) & (s16) (height - 1);
                            tri->uv1.u = tri->uv0.u + newU1;
                            tri->uv1.v = tri->uv0.v + newV1;
                            tri->uv2.u = tri->uv0.u + newU2;
                            tri->uv2.v = tri->uv0.v + newV2;
                        }
                    }
                }
            }
        }
    }
}

/**
 * Loop through every object.
 * Check which ones have 3D models and count down the update timer.
 * The object will update its animation at 0.
 */
void obj_tick_anims(void) {
    s32 i = gObjectListStart;
    s32 j;
    Object *currObj;
    ModelInstance *modInst;

    for (; i < gObjectCount; i++) {
        currObj = gObjPtrList[i];
        if (!(currObj->trans.flags & OBJ_FLAGS_PARTICLE) && currObj->header->modelType == OBJECT_MODEL_TYPE_3D_MODEL) {
            for (j = 0; j < currObj->header->numberOfModelIds; j++) {
                modInst = currObj->modelInstances[j];
                if (modInst != NULL && modInst->animUpdateTimer > 0) {
                    modInst->animUpdateTimer &= 3;
                    modInst->animUpdateTimer--;
                }
            }
        }
    }
}

/**
 * Renders every triangle batch in an objects mesh.
 * If vertOffset is true, then draw in two passes, utilising the head matrix and vertex ID offset in the batch.
 */
s32 render_mesh(ObjectModel *objModel, Object *obj, s32 startIndex, s32 flags, s32 overrideVerts) {
    s32 i;
    s32 textureIndex;
    s32 triOffset;
    TextureHeader *texToSet;
    s32 endLoop;
    s32 numTris;
    s32 texEnabled;
    s32 texOffset;
    s32 numVertices;
    Vertex *vtx;
    s32 offsetStartVertex;
    s32 texToSetFlags;
    Triangle *tris;
    s32 vertOffset;
    Gfx *dList;

    dList = gObjectCurrDisplayList;
    i = startIndex;
    endLoop = FALSE;
    while (i < objModel->numberOfBatches && !endLoop) {
        if (!(objModel->batches[i].flags & RENDER_SEMI_TRANSPARENT) || flags & RENDER_SEMI_TRANSPARENT) {
            // Hidden/Invisible geometry
            textureIndex = objModel->batches[i].flags & RENDER_HIDDEN;
            // Probably a fakematch to use textureIndex here, but it works.
            if (!textureIndex) {
                vertOffset = objModel->batches[i].verticesOffset;
                triOffset = objModel->batches[i].facesOffset;
                numVertices = objModel->batches[i + 1].verticesOffset - vertOffset;
                offsetStartVertex = (overrideVerts) ? objModel->batches[i].vertOverride : numVertices;
                numTris = objModel->batches[i + 1].facesOffset - triOffset;
                tris = &objModel->triangles[triOffset];
                vtx = &obj->curVertData[vertOffset];
                textureIndex = objModel->batches[i].textureIndex;
                // textureIndex of 0xFF is no texture
                if (textureIndex == 0xFF) {
                    texOffset = 0;
                    texToSet = NULL;
                    texEnabled = FALSE;
                } else {
                    texOffset = objModel->batches[i].texOffset << 14;
                    texEnabled = TRUE;
                    texToSet = objModel->textures[textureIndex].texture;
                }
                texToSetFlags = objModel->batches[i].flags | RENDER_FOG_ACTIVE;
                if (flags & RENDER_SEMI_TRANSPARENT &&
                    !(objModel->batches[i].flags & (flags & ~RENDER_SEMI_TRANSPARENT))) {
                    texToSetFlags |= RENDER_SEMI_TRANSPARENT;
                }
                if (gObjectTexAnim == FALSE) {
                    material_set(&dList, texToSet, texToSetFlags, texOffset);
                } else {
                    texToSet = set_animated_texture_header(texToSet, texOffset);
                    gDkrDmaDisplayList(gObjectCurrDisplayList++, OS_K0_TO_PHYSICAL(texToSet->cmd),
                                       texToSet->numberOfCommands);
                }
                if (offsetStartVertex == numVertices) {
                    gSPVertexDKR(dList++, OS_K0_TO_PHYSICAL(vtx), numVertices, 0);
                } else {
                    if (offsetStartVertex > 0) {
                        gSPVertexDKR(dList++, OS_K0_TO_PHYSICAL(vtx), offsetStartVertex, 0);
                        gSPSelectMatrixDKR(dList++, G_MTX_DKR_INDEX_2);
                        gSPVertexDKR(dList++, OS_K0_TO_PHYSICAL(&vtx[offsetStartVertex]),
                                     (numVertices - offsetStartVertex), 1);
                    } else {
                        gSPSelectMatrixDKR(dList++, G_MTX_DKR_INDEX_2);
                        gSPVertexDKR(dList++, OS_K0_TO_PHYSICAL(vtx), numVertices, 0);
                    }
                    gSPSelectMatrixDKR(dList++, G_MTX_DKR_INDEX_1);
                }
                gSPPolygon(dList++, OS_K0_TO_PHYSICAL(tris), numTris, texEnabled);
            }
            i++;
        } else {
            endLoop = TRUE;
        }
    }
    if (i >= objModel->numberOfBatches) {
        i = -1;
    }
    gObjectCurrDisplayList = dList;
    return i;
}

s32 get_first_active_object(s32 *retObjCount) {
    s32 i, j;
    s32 minIndex, maxIndex;
    s32 breakLoop;

    *retObjCount = gObjectCount;
    if (gFirstActiveObjectId != 0) {
        // Already sorted
        return gFirstActiveObjectId;
    }

    i = gObjectListStart;
    j = gObjectCount - 1;
    minIndex = i;
    maxIndex = j;

    while (i <= j) {
        breakLoop = 0;
        while (i <= maxIndex && breakLoop == 0) {
            if (!(gObjPtrList[i]->trans.flags & OBJ_FLAGS_PARTICLE)) {
                if (gObjPtrList[i]->header->flags & HEADER_FLAGS_UNK_0001) {
                    i++;
                } else {
                    // Break the loop if neither OBJ_FLAGS_PARTICLE nor bit 1 in header->flags is set
                    breakLoop = -1;
                }
            } else {
                i++;
            }
        }

        breakLoop = 0;
        while (j >= minIndex && breakLoop == 0) {
            if (gObjPtrList[j]->trans.flags & OBJ_FLAGS_PARTICLE) {
                // Break the loop if OBJ_FLAGS_PARTICLE is set
                breakLoop = -1;
            } else if (!(gObjPtrList[j]->header->flags & HEADER_FLAGS_UNK_0001)) {
                j--;
            } else {
                // Break the loop if bit 1 in header->flags is set
                breakLoop = -1;
            }
        }

        if (i < j) {
            // Swap active and inactive objects
            Object *tempObject = gObjPtrList[i];
            gObjPtrList[i] = gObjPtrList[j];
            gObjPtrList[j] = tempObject;
            i++;
            j--;
        }
    }

    gFirstActiveObjectId = i;
    return i;
}

UNUSED void func_800149C0(unk800149C0 *arg0, UNUSED s32 arg1, s32 arg2, s32 arg3, s32 *arg4, s32 *arg5, s32 arg6) {
    UNUSED s32 pad;
    s32 endVal;
    s32 startVal;
    f32 temp_f0;
    s32 i;

    temp_f0 = arg0->unk6;
    endVal = func_80014B50(arg2, arg3, temp_f0, arg0->unk4);
    startVal = func_80014B50(arg2, endVal - 1, temp_f0, arg0->unk4 + 8);

    for (i = startVal; i < endVal; i++) {
        gObjPtrList[i]->unk38 += arg6;
    }

    *arg4 = startVal;
    *arg5 = endVal - 1;
}

// Only used in the unused function func_800149C0
s32 func_80014B50(s32 arg0, s32 arg1, f32 arg2, u32 arg3) {
    Object *swapTemp;
    s32 var_a0;
    s32 var_a1;

    var_a0 = arg0;
    var_a1 = arg1;
    switch (arg3) {
        case 0:
            while (arg1 >= arg0) {
                while ((var_a1 >= arg0) && ((gObjPtrList[arg0]->trans.x_position - gObjPtrList[arg0]->unk34) < arg2)) {
                    arg0++;
                }
                while ((arg1 >= var_a0) && (arg2 <= (gObjPtrList[arg1]->trans.x_position - gObjPtrList[arg1]->unk34))) {
                    arg1--;
                }
                if (arg0 < arg1) {
                    swapTemp = gObjPtrList[arg0];
                    gObjPtrList[arg0] = gObjPtrList[arg1];
                    gObjPtrList[arg1] = swapTemp;
                    arg0++;
                    arg1--;
                }
            }
            break;
        case 1:
            while (arg1 >= arg0) {
                while ((var_a1 >= arg0) && ((gObjPtrList[arg0]->trans.y_position - gObjPtrList[arg0]->unk34) < arg2)) {
                    arg0++;
                }
                while ((arg1 >= var_a0) && (arg2 <= (gObjPtrList[arg1]->trans.y_position - gObjPtrList[arg1]->unk34))) {
                    arg1--;
                }
                if (arg0 < arg1) {
                    swapTemp = gObjPtrList[arg0];
                    gObjPtrList[arg0] = gObjPtrList[arg1];
                    gObjPtrList[arg1] = swapTemp;
                    arg0++;
                    arg1--;
                }
            }
            break;
        case 2:
            while (arg1 >= arg0) {
                while ((var_a1 >= arg0) && ((gObjPtrList[arg0]->trans.z_position - gObjPtrList[arg0]->unk34) < arg2)) {
                    arg0++;
                }
                while ((arg1 >= var_a0) && (arg2 <= (gObjPtrList[arg1]->trans.z_position - gObjPtrList[arg1]->unk34))) {
                    arg1--;
                }
                if (arg0 < arg1) {
                    swapTemp = gObjPtrList[arg0];
                    gObjPtrList[arg0] = gObjPtrList[arg1];
                    gObjPtrList[arg1] = swapTemp;
                    arg0++;
                    arg1--;
                }
            }
            break;
        case 8:
            while (arg1 >= arg0) {
                while ((var_a1 >= arg0) && ((gObjPtrList[arg0]->trans.x_position + gObjPtrList[arg0]->unk34) < arg2)) {
                    arg0++;
                }
                while ((arg1 >= var_a0) && (arg2 <= (gObjPtrList[arg1]->trans.x_position + gObjPtrList[arg1]->unk34))) {
                    arg1--;
                }
                if (arg0 < arg1) {
                    swapTemp = gObjPtrList[arg0];
                    gObjPtrList[arg0] = gObjPtrList[arg1];
                    gObjPtrList[arg1] = swapTemp;
                    arg0++;
                    arg1--;
                }
            }
            break;
        case 9:
            while (arg1 >= arg0) {
                while ((var_a1 >= arg0) && ((gObjPtrList[arg0]->trans.y_position + gObjPtrList[arg0]->unk34) < arg2)) {
                    arg0++;
                }
                while ((arg1 >= var_a0) && (arg2 <= (gObjPtrList[arg1]->trans.y_position + gObjPtrList[arg1]->unk34))) {
                    arg1--;
                }
                if (arg0 < arg1) {
                    swapTemp = gObjPtrList[arg0];
                    gObjPtrList[arg0] = gObjPtrList[arg1];
                    gObjPtrList[arg1] = swapTemp;
                    arg0++;
                    arg1--;
                }
            }
            break;
        case 10:
            while (arg1 >= arg0) {
                while ((var_a1 >= arg0) && ((gObjPtrList[arg0]->trans.z_position + gObjPtrList[arg0]->unk34) < arg2)) {
                    arg0++;
                }
                while ((arg1 >= var_a0) && (arg2 <= (gObjPtrList[arg1]->trans.z_position + gObjPtrList[arg1]->unk34))) {
                    arg1--;
                }
                if (arg0 < arg1) {
                    swapTemp = gObjPtrList[arg0];
                    gObjPtrList[arg0] = gObjPtrList[arg1];
                    gObjPtrList[arg1] = swapTemp;
                    arg0++;
                    arg1--;
                }
            }
            break;
    }
    return arg0;
}

/**
 * Takes every object and sorts the main object list by distance to the camera.
 */
void sort_objects_by_dist(s32 startIndex, s32 lastIndex) {
    s32 i;
    s32 didNotSwap;
    Object *obj;

    if (lastIndex < startIndex) {
        return;
    }

    for (i = startIndex; i <= lastIndex; i++) {
        obj = gObjPtrList[i];
        if (obj != NULL) {
            if (obj->trans.flags & OBJ_FLAGS_PARTICLE) {
                // get_distance_to_camera calculates the distance to the camera from a XYZ location.
                obj->distanceToCamera =
                    -get_distance_to_camera(obj->trans.x_position, obj->trans.y_position, obj->trans.z_position);
            } else if (obj->header->flags & HEADER_FLAGS_UNK_0080) {
                obj->distanceToCamera += -16000.0f;
            } else {
                obj->distanceToCamera =
                    -get_distance_to_camera(obj->trans.x_position, obj->trans.y_position, obj->trans.z_position);
            }
        } else {
            //!@bug obj is NULL here, so it would probably cause a crash. Thankfully, gObjPtrList shouldn't have NULL
            //! objects in it.
            obj->distanceToCamera = 0.0f;
        }
    }

    // Keep swapping until all objects are sorted by the distance to the camera.
    do {
        didNotSwap = TRUE;
        for (i = startIndex; i < lastIndex; i++) {
            if (gObjPtrList[i]->distanceToCamera < gObjPtrList[i + 1]->distanceToCamera) {
                obj = gObjPtrList[i];
                gObjPtrList[i] = gObjPtrList[i + 1];
                gObjPtrList[i + 1] = obj;
                didNotSwap = FALSE;
            }
        }
    } while (!didNotSwap);
}

/**
 * Go through each object and detect potential interactions between each.
 * Add candidates to a list and calcualte their distances.
 */
void process_object_interactions(void) {
    Object *obj2;
    Object *obj;
    ObjectInteraction *objInteract;
    ObjectInteraction *objInteract2;
    f32 xDiff;
    f32 zDiff;
    f32 radius;
    s32 j;
    s32 i;
    s32 objsWithInteractives;
    Object *objList[257]; // 257 seems random, but it works for now.

    objsWithInteractives = 0;
    for (i = gObjectListStart; i < gObjectCount; i++) {
        obj = gObjPtrList[i];
        if (!(obj->trans.flags & OBJ_FLAGS_PARTICLE)) {
            objInteract = obj->interactObj;
            if (objInteract != NULL) {
                objList[objsWithInteractives] = obj;
                objsWithInteractives++;
                if (objInteract->unk11 != 2) {
                    objInteract->obj = NULL;
                    objInteract->flags &= ~(INTERACT_FLAGS_COLLIDED | INTERACT_FLAGS_PUSHING);
                    objInteract->distance = 255;
                }
            }
        }
    }

    gCollisionObjectCount = 0;

    for (i = 0; i < objsWithInteractives; i++) {
        obj = objList[i];
        objInteract = obj->interactObj;
        if (objInteract->unk11 == 2 && gCollisionObjectCount < 20) {
            gCollisionObjects[gCollisionObjectCount] = obj;
            gCollisionObjectCount++;
        }
        if (objInteract->flags & INTERACT_FLAGS_UNK_0004) {
            for (j = 0; j < objsWithInteractives; j++) {
                if (i != j) {
                    obj2 = objList[j];
                    objInteract2 = obj2->interactObj;
                    if (objInteract2->flags & (INTERACT_FLAGS_SOLID | INTERACT_FLAGS_TANGIBLE)) {
                        if (objInteract2->unk11 == 3) {
                            func_80016748(obj, obj2);
                        } else if (objInteract2->unk11 != 2) {
                            xDiff = obj->trans.x_position - obj2->trans.x_position;
                            zDiff = obj->trans.z_position - obj2->trans.z_position;
                            if (objInteract2->flags & INTERACT_FLAGS_UNK_0020) {
                                radius = 0x400000; // 4194304.0f;
                            } else {
                                radius = 0x40000; // 262144.0f;
                            }
                            if (((xDiff * xDiff) + (zDiff * zDiff)) < radius) {
                                func_800159C8(obj, obj2);
                            }
                        }
                    }
                }
            }
        }
        if (objInteract->flags & INTERACT_FLAGS_UNK_0100) {
            for (j = 0; j < objsWithInteractives; j++) {
                if (i != j) {
                    obj2 = objList[j];
                    objInteract2 = obj2->interactObj;
                    if (objInteract2->unk11 == 3) {
                        func_80016748(obj, obj2);
                    }
                }
            }
        }
    }

    for (i = 0; i < objsWithInteractives; i++) {
        obj = objList[i];
        objInteract = obj->interactObj;
        objInteract->x_position = obj->trans.x_position;
        objInteract->y_position = obj->trans.y_position;
        objInteract->z_position = obj->trans.z_position;
    }
}

// https://decomp.me/scratch/Hg44X
#ifdef NON_EQUIVALENT
void func_800159C8(Object *arg0, Object *arg1) {
    f32 sp9C;
    f32 sp98;
    f32 temp_f10; // sp94
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 var_f2;    // sp70
    f32 temp_f0_3; // sp6C
    f32 sp68;
    f32 sp64;
    f32 sp60;
    s32 var_v0; // sp5C
    ObjectInteraction *sp58;
    ObjectInteraction *sp54;
    Object_Racer *sp50;
    Object_Racer *sp4C;

    sp68 = arg1->trans.x_position - arg0->trans.x_position;
    sp64 = arg1->trans.y_position - arg0->trans.y_position;
    sp60 = arg1->trans.z_position - arg0->trans.z_position;

    sp58 = arg0->interactObj;
    sp54 = arg1->interactObj;
    sp80 = 1 / gObjectUpdateRateF;

    if (sp54->unk11 == 1) {
        if (-sp64 < sp54->unk16 * 10.0f || sp54->unk17 * 10.0f < -sp64) {
            return;
        }
        sp64 = 0.0f;
    }

    if (sp54->unk11 == 4 && sp64 < 0.0f) {
        sp64 *= 0.3;
    }

    sp9C = sqrtf(sp68 * sp68 + sp64 * sp64 + sp60 * sp60);
    temp_f10 = (s32) sp9C;

    var_v0 = temp_f10;
    if (sp58->flags & 0x20) {
        var_v0 >>= 3;
    }

    if (var_v0 > 255) {
        var_v0 = 255;
    }

    if (sp58->distance >= var_v0) {
        sp58->obj = arg1;
        sp58->distance = var_v0;
    }

    var_v0 = temp_f10;
    if (sp54->flags & 0x20) {
        var_v0 >>= 3;
    }

    if (var_v0 > 255) {
        var_v0 = 255;
    }

    if (sp54->distance >= var_v0) {
        sp54->obj = arg0;
        sp54->distance = var_v0;
    }

    if (!(sp54->flags & 1)) {
        return;
    }

    sp98 = sp54->hitboxRadius + sp58->hitboxRadius;

    sp7C = arg0->trans.x_position - sp58->x_position;
    sp78 = arg0->trans.y_position - sp58->y_position;
    sp74 = arg0->trans.z_position - sp58->z_position;

    if (sp54->unk11 == 1) {
        sp78 = 0.0f;
    }

    temp_f10 = sp7C * sp7C + sp78 * sp78 + sp74 * sp74;
    if (temp_f10 > 1.0) {
        var_f2 =
            ((arg1->trans.x_position - sp58->x_position) * sp7C + (arg1->trans.y_position - sp58->y_position) * sp78 +
             (arg1->trans.z_position - sp58->z_position) * sp74) /
            temp_f10;
        if (var_f2 >= 0.0f && var_f2 <= 1.0) {
            sp8C = sp58->x_position + var_f2 * sp7C;
            sp88 = sp58->y_position + var_f2 * sp78;
            sp84 = sp58->z_position + var_f2 * sp74;
            sp9C = sqrtf((sp8C - arg1->trans.x_position) * (sp8C - arg1->trans.x_position) +
                         (sp88 - arg1->trans.y_position) * (sp88 - arg1->trans.y_position) +
                         (sp84 - arg1->trans.z_position) * (sp84 - arg1->trans.z_position));
        }
    }

    if (sp9C < sp98 && sp9C > 0.0f) {
        sp8C = sp54->x_position - sp58->x_position;
        sp88 = sp54->y_position - sp58->y_position;
        sp84 = sp54->z_position - sp58->z_position;
        if (sp54->unk11 == 1) {
            sp88 = 0.0f;
        }

        temp_f0_3 = sqrtf(sp8C * sp8C + sp88 * sp88 + sp84 * sp84);
        if (temp_f0_3 > 0.0f) {
            sp68 = sp8C / temp_f0_3;
            sp64 = sp88 / temp_f0_3;
            sp60 = sp84 / temp_f0_3;
        } else {
            sp68 /= sp9C;
            sp64 /= sp9C;
            sp60 /= sp9C;
        }
        sp9C = temp_f0_3 - sp9C;
        if (sp9C < 0.0f) {
            sp9C = -sp9C;
        }

        sp68 *= sp9C;
        sp64 *= sp9C;
        sp60 *= sp9C;
        sp9C *= sp80;
        sp58->flags |= 8;
        sp54->flags |= 8;
        if (sp54->pushForce == 0) {
            arg0->trans.x_position -= sp68;
            arg0->trans.y_position -= sp64;
            arg0->trans.z_position -= sp60;

            sp68 *= sp80;
            sp60 *= sp80;
            if (arg0->behaviorId != 1) {
                return;
            }

            sp50 = arg0->racer;
            var_v0 = FALSE;
            if (sp50->vehicleID == 1) {
                if (sp9C > 0.3) {
                    if (sp9C > 1.0) {
                        var_v0 = TRUE;
                    }
                    if (var_v0) {
                        arg0->x_velocity *= 0.8;
                        arg0->z_velocity *= 0.8;
                    }
                    if (var_v0) {
                        sp54->flags |= 0x40;
                        var_f2 =
                            (arg0->trans.x_position * arg0->z_velocity - arg0->trans.z_position * arg0->x_velocity);
                        var_f2 =
                            (arg1->trans.x_position * arg0->z_velocity - arg1->trans.z_position * arg0->x_velocity) -
                            var_f2;
                        sp50->unk1D2 = 7;
                        if (var_f2 >= 0.0f) {
                            sp50->unk120 = arg0->x_velocity * 0.1;
                            sp50->unk11C = -arg0->z_velocity * 0.1;
                        } else {
                            sp50->unk120 = -arg0->x_velocity * 0.1;
                            sp50->unk11C = arg0->z_velocity * 0.1;
                        }
                    }
                }
            } else {
                if (sp9C > 0.3) {
                    if (sp9C > 1.0) {
                        var_v0 = 1;
                    }
                    arg0->x_velocity -= sp68;
                    arg0->z_velocity -= sp60;
                    sp50->velocity = sp9C * 0.25;
                    sp50->lateral_velocity = 0.0f;
                }
                if (var_v0) {
                    sp54->flags |= 0x40;
                    var_f2 = arg0->trans.x_position * arg0->z_velocity - arg0->trans.z_position * arg0->x_velocity;
                    var_f2 =
                        arg1->trans.x_position * arg0->z_velocity - arg1->trans.z_position * arg0->x_velocity - var_f2;
                    if (var_f2 >= 0.0f) {
                        var_f2 = 2.0f;
                    } else {
                        var_f2 = -2.0f;
                    }
                    sp50->unk1D2 = 7;
                    sp50->unk11C = sp50->ox3 * var_f2 * sp50->velocity;
                    sp50->unk120 = sp50->oz3 * var_f2 * sp50->velocity;
                }
            }
            if (var_v0 && sp50->playerIndex != -1) {
                func_80016500(arg0, sp50);
            }
            return;
        }

        sp68 *= 0.5;
        sp64 *= 0.5;
        sp60 *= 0.5;
        if (sp58->pushForce != 0) {
            arg0->trans.x_position -= sp68;
            arg0->trans.y_position -= sp64;
            arg0->trans.z_position -= sp60;
        }
        arg1->trans.x_position += sp68;
        arg1->trans.y_position += sp64;
        arg1->trans.z_position += sp60;

        sp68 *= sp80;
        sp60 *= sp80;
        if (arg0->behaviorId == 1 && arg1->behaviorId == 1) {
            sp90 = 1.0f;
            sp90 += (f32) (sp58->pushForce - sp54->pushForce) * 0.3;

            sp50 = arg0->racer;
            sp4C = arg1->racer;

            if (sp50->shieldType != 0 && sp4C->shieldType == 0) {
                sp4C->spinout_timer = sp50->shieldType;
            }
            if (sp4C->shieldType != 0 && sp50->shieldType == 0) {
                sp50->spinout_timer = sp4C->shieldType;
            }

            var_v0 = FALSE;
            if (sp50->vehicleID == 1) {
                var_v0 = TRUE;
            } else if (sp9C > 0.1) {
                var_v0 = TRUE;
                sp68 *= 0.5;
                sp60 *= 0.5;
            }

            if (var_v0) {
                if (sp58->pushForce != 0) {
                    temp_f0_3 = 2.0 - sp90;
                    arg0->x_velocity -= sp68 * temp_f0_3;
                    arg0->z_velocity -= sp60 * temp_f0_3;
                    func_80016500(arg0, sp50);
                }
                arg1->x_velocity += sp68 * sp90;
                arg1->z_velocity += sp60 * sp90;
                func_80016500(arg1, sp4C);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_800159C8.s")
#endif

void func_80016500(Object *obj, Object_Racer *racer) {
    s32 shakeMagnitude;
    s32 volume;
    s32 angle;
    f32 startVelocity;
    f32 cosAngle;
    f32 sinAngle;

    startVelocity = racer->velocity;
    angle = racer->steerVisualRotation;
    if (racer->vehicleID == VEHICLE_CAR) {
        if (racer->drift_direction != 0) {
            angle += racer->unk10C;
            angle = (s16) angle;
        }
    }
    cosAngle = coss_f(-angle);
    sinAngle = sins_f(-angle);
    racer->lateral_velocity = (obj->x_velocity * cosAngle) + (obj->z_velocity * sinAngle);
    racer->velocity = (-obj->x_velocity * sinAngle) + (obj->z_velocity * cosAngle);
    if (racer->playerIndex != PLAYER_COMPUTER) {
        volume = (startVelocity - racer->velocity) * 14.0f;
        if (volume < 0) {
            volume = -volume;
        }
        volume += 35;
        if (volume > 127) {
            volume = 127;
        }
        if (racer->unk1F6 == 0) {
            sound_play(SOUND_CRASH_CHARACTER, &racer->unk220);
            sound_volume_set_relative(SOUND_CRASH_CHARACTER, racer->unk220, volume);
        }
        if (racer->unk1F6 == 0 && volume > 55) {
            if (!racer->raceFinished) {
                rumble_set(racer->playerIndex, RUMBLE_TYPE_18);
            }
            racer->unk1F3 |= 8;
        }
        if (volume > 55) {
            play_random_character_voice(obj, SOUND_VOICE_CHARACTER_NEGATIVE, 8, 1);
        }
        shakeMagnitude = (startVelocity - racer->velocity);
        if (shakeMagnitude < 0) {
            shakeMagnitude = -shakeMagnitude;
        }
        if (shakeMagnitude > 3) {
            shakeMagnitude = 3;
        }
        racer->unk1F6 = 30;
        set_active_camera(racer->playerIndex);
        cam_get_active_camera()->shakeMagnitude = shakeMagnitude;
    }
}

void func_80016748(Object *obj0, Object *obj1) {
    ObjectModel *objModel;
    s32 i;
    f32 temp;

#ifdef AVOID_UB
    MtxF obj1TransformMtx;
#else
    // THIS IS A HACK! Supposed to be a MtxF, but the stack ended up being too big.
    f32 pad[2];
    f32 obj1TransformMtx[4][3];
#endif

    f32 xDiff;
    f32 yDiff;
    f32 zDiff;
    ObjectInteraction *obj1Interact;
    ObjectInteraction *obj0Interact;
    Object_Racer *racer;
    f32 distance;
    f32 radius;
    ModelInstance *modInst;

    if (obj1->curVertData != NULL) {
        modInst = obj1->modelInstances[0];
        objModel = modInst->objModel;
        xDiff = obj0->trans.x_position - obj1->trans.x_position;
        yDiff = obj0->trans.y_position - obj1->trans.y_position;
        zDiff = obj0->trans.z_position - obj1->trans.z_position;
        if (!((objModel->unk3C + 50.0) < sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff)))) {
            obj0Interact = obj0->interactObj;
            obj1Interact = obj1->interactObj;
            mtxf_from_transform((MtxF *) obj1TransformMtx, &obj1->trans);
            for (i = 0; i < objModel->unk20; i += 2) {
                xDiff = obj1->curVertData[objModel->unk1C[i]].x;
                yDiff = obj1->curVertData[objModel->unk1C[i]].y;
                zDiff = obj1->curVertData[objModel->unk1C[i]].z;
                mtxf_transform_point((float(*)[4]) obj1TransformMtx, xDiff, yDiff, zDiff, &xDiff, &yDiff, &zDiff);
                temp = (((f32) objModel->unk1C[i + 1] / 64) * obj1->trans.scale) * 50.0;
                xDiff -= obj0->trans.x_position;
                yDiff -= obj0->trans.y_position;
                zDiff -= obj0->trans.z_position;
                distance = sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff));
                temp += obj1Interact->hitboxRadius;
                if (distance < temp && distance > 0.0f) {
                    obj0Interact->flags |= INTERACT_FLAGS_PUSHING;
                    obj1Interact->flags |= INTERACT_FLAGS_PUSHING;
                    obj0Interact->obj = obj1;
                    obj1Interact->obj = obj0;
                    obj0Interact->distance = 0;
                    obj1Interact->distance = 0;
                    radius = (temp - distance) / distance;
                    distance = 2; // Needed
                    radius /= distance;
                    xDiff *= radius;
                    yDiff *= radius;
                    zDiff *= radius;
                    obj0->trans.x_position -= xDiff;
                    obj0->trans.y_position -= yDiff;
                    obj0->trans.z_position -= zDiff;

                    if (obj0->behaviorId == BHV_RACER) {
                        racer = obj0->racer;
                        if (!racer->raceFinished) {
                            rumble_set(racer->playerIndex, RUMBLE_TYPE_18);
                        }
                        if (racer->vehicleID == VEHICLE_HOVERCRAFT) {
                            if (radius > 0.1) {
                                obj0->x_velocity -= xDiff;
                                obj0->z_velocity -= zDiff;
                            }
                        } else if (radius > 0.3) {
                            obj0->x_velocity -= xDiff;
                            obj0->z_velocity -= zDiff;
                            racer->velocity = radius * 4.0f;
                            racer->lateral_velocity = 0.0f;
                        }
                    }
                }
            }
        }
    }
}

void func_80016BC4(Object *obj) {
    s32 i;

    obj->collisionData->mtxFlip = 0;
    obj_collision_transform(obj);
    obj_collision_transform(obj); // Not sure why they do this a second time.
    for (i = 0; i < obj->header->numberOfModelIds; i++) {
        if (obj->modelInstances[i] != NULL) {
            model_init_collision(obj->modelInstances[i]->objModel);
        }
    }
}

/**
 * Find the first butterfly node within range and return a pointer to it.
 */
Object *obj_butterfly_node(f32 x, f32 y, f32 z, f32 maxDistCheck, s32 dontCheckYAxis) {
    f32 diffY;
    f32 diffZ;
    f32 diffX;
    f32 distance;
    s32 i;
    Object *curObj;

    for (i = 0; i < gObjectCount; i++) {
        curObj = gObjPtrList[i];
        if (!(curObj->trans.flags & OBJ_FLAGS_PARTICLE) && curObj->behaviorId == BHV_ANIMATED_OBJECT_3) {
            diffX = curObj->trans.x_position - x;
            diffZ = curObj->trans.z_position - z;
            if (!dontCheckYAxis) {
                diffY = curObj->trans.y_position - y;
                distance = sqrtf((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ));
            } else {
                distance = sqrtf((diffX * diffX) + (diffZ * diffZ));
            }
            if (distance < maxDistCheck) {
                return curObj;
            }
        }
    }
    return NULL;
}

/**
 * Compare distance between itself and every racer.
 * Any racer within the radius is sorted from nearest to furthest.
 * Returns the number of racers within the radius.
 */
s32 obj_dist_racer(f32 x, f32 y, f32 z, f32 radius, s32 is2dCheck, Object **sortObj) {
    f32 distances[8];
    s32 i;
    s32 j;
    f32 xDiff;
    f32 yDiff;
    f32 zDiff;
    s32 result;
    Object *racerObj;
    Object_Racer *racer;
    Object *swapObj;
    f32 swapf;

    result = 0;
    if (gNumRacers > 0) {
        for (i = 0; i < gNumRacers; i++) {
            racerObj = (*gRacers)[i];
            racer = racerObj->racer;
            if (racer->playerIndex >= 0 && racer->playerIndex < 4) {
                if (is2dCheck) {
                    xDiff = racerObj->trans.x_position - x;
                    zDiff = racerObj->trans.z_position - z;
                    yDiff = sqrtf((xDiff * xDiff) + (zDiff * zDiff));
                } else {
                    xDiff = racerObj->trans.x_position - x;
                    yDiff = racerObj->trans.y_position - y;
                    zDiff = racerObj->trans.z_position - z;
                    yDiff = sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff));
                }
                if (yDiff < radius) {
                    distances[result] = yDiff;
                    sortObj[result] = (*gRacers)[i];
                    result++;
                }
            }
        }
        if (result >= 2) {
            for (i = result - 1; i > 0; i--) {
                for (j = 0; j < i; j++) {
                    if (distances[j + 1] < distances[j]) {
                        swapf = distances[j];
                        swapObj = sortObj[j];
                        distances[j] = distances[j + 1];
                        sortObj[j] = sortObj[j + 1];
                        distances[j + 1] = swapf;
                        sortObj[j + 1] = swapObj;
                    }
                }
            }
        }
    }
    return result;
}

/**
 * Updates the object's collision transformation matrices.
 */
void obj_collision_transform(Object *obj) {
    ObjectTransform trans;
    s32 i;
    f32 inverseScale;
    MtxF *curMtx;
    MtxF inverseMtx;
    ObjectCollision *colData;

    colData = obj->collisionData;
    colData->mtxFlip = (colData->mtxFlip + 1) & 1;
#ifdef AVOID_UB
    curMtx = &colData->matrices[colData->mtxFlip];
#else

    curMtx = (MtxF *) &colData->_matrices[colData->mtxFlip << 1];
#endif
    trans.rotation.y_rotation = -obj->trans.rotation.y_rotation;
    trans.rotation.x_rotation = -obj->trans.rotation.x_rotation;
    trans.rotation.z_rotation = -obj->trans.rotation.z_rotation;
    trans.scale = 1.0f;
    trans.x_position = -obj->trans.x_position;
    trans.y_position = -obj->trans.y_position;
    trans.z_position = -obj->trans.z_position;
    mtxf_from_inverse_transform(curMtx, &trans);
    inverseScale = 1.0 / obj->trans.scale;
    i = 0;
    // Zero out the matrix.
    while (i < 16) {
        ((f32 *) inverseMtx)[i] = 0.0f;
        i++;
    }
    inverseMtx[0][0] = inverseScale;
    inverseMtx[1][1] = inverseScale;
    inverseMtx[2][2] = inverseScale;
    inverseMtx[3][3] = 1.0f;
    mtxf_mul(curMtx, &inverseMtx, curMtx);
    trans.rotation.y_rotation = obj->trans.rotation.y_rotation;
    trans.rotation.x_rotation = obj->trans.rotation.x_rotation;
    trans.rotation.z_rotation = obj->trans.rotation.z_rotation;
    trans.scale = 1.0 / inverseScale;
    trans.x_position = obj->trans.x_position;
    trans.y_position = obj->trans.y_position;
    trans.z_position = obj->trans.z_position;
#ifdef AVOID_UB
    mtxf_from_transform((MtxF *) colData->matrices[(colData->mtxFlip + 2)], &trans);
#else
    mtxf_from_transform((MtxF *) colData->_matrices[(colData->mtxFlip + 2) << 1], &trans);
#endif
    colData->collidedObj = NULL;
}

// https://decomp.me/scratch/S3kHf
#ifdef NON_MATCHING
s32 collision_objectmodel(Object *obj, s32 arg1, s32 *arg2, Vec3f *arg3, f32 *arg4, f32 *arg5, s8 *surface) {
    ModelInstance *modInst;
    s32 sp170;
    s32 sp16C;
    s32 sp168;
    s32 j; // fp // sp164
    s32 sp160;
    f32 dist; // sp15C
    Object *sp158;
    ObjectModel *sp154;
    f32 temp;
    unk800179D0 *sp14C;
    f32 sp13C[4];
    f32 sp12C[4];
    f32 sp11C[4];
    s32 i;
    ObjectCollision *collision;
    s32 tempv0;
    f32 sp100[4];
    f32 spF0[4];
    f32 spE0[4];
    MtxF *spDC;
    s32 spB4[10];
    f32 sp8C[10];

    sp160 = 0;

    for (sp170 = 0; sp170 < gCollisionObjectCount; sp170++) {
        sp158 = gCollisionObjects[sp170];
        modInst = sp158->modelInstances[sp158->modelIndex];
        sp154 = modInst->objModel;

        temp = sp158->trans.x_position - obj->trans.x_position;
        dist = sqrtf(
            (temp) * (temp) +
            (sp158->trans.y_position - obj->trans.y_position) * (sp158->trans.y_position - obj->trans.y_position) +
            (sp158->trans.z_position - obj->trans.z_position) * (sp158->trans.z_position - obj->trans.z_position));

        j = dist;
        if (sp158->interactObj->flags & 0x20) {
            j >>= 3;
        }
        if (j > 255) {
            j = 255;
        }
        if (sp158->interactObj->distance > j) {
            sp158->interactObj->distance = j;
            sp158->interactObj->obj = obj;
        }

        if (dist - 25.0f < sp154->unk3C * sp158->trans.scale) {
            spB4[sp160] = sp170;
            sp8C[sp160] = dist;

            // clang-format off
            for (i = sp160; i > 0 && sp8C[i - 1] < sp8C[i]; i--) {\
                temp = sp8C[i];\
                sp16C = spB4[i];\
                sp8C[i] = sp8C[i - 1];\
                spB4[i] = spB4[i - 1];\
                sp8C[i - 1] = temp;
                spB4[i - 1] = sp16C;
            }
            // clang-format on

            sp160++;
        }
    }

    sp168 = 0;
    sp170 = 0;
    while (sp170 < sp160) {
        sp158 = gCollisionObjects[spB4[sp170]];
        modInst = sp158->modelInstances[sp158->modelIndex];
        sp154 = modInst->objModel;
        collision = sp158->collisionData;
#ifdef AVOID_UB
        spDC = &collision->matrices[((sp158->collisionData->mtxFlip + 1) & 1)];
#else
        spDC = (MtxF *) &collision->_matrices[((sp158->collisionData->mtxFlip + 1) & 1) << 1];
#endif

        sp14C = func_8001790C(obj, sp158);
        if (sp14C != NULL) {
            for (i = 0, j = 0; j < arg1; j++, i += 3) {
                sp13C[j] = sp14C->unk0C[i + 0];
                sp12C[j] = sp14C->unk0C[i + 1];
                sp11C[j] = sp14C->unk0C[i + 2];
                mtxf_transform_point(*spDC, arg4[i], arg4[i + 1], arg4[i + 2], &sp100[j], &spF0[j], &spE0[j]);
            }
        } else {
            for (i = 0, j = 0; j < arg1; j++, i++) {
                mtxf_transform_point(*spDC, arg3[i].x, arg3[i].y, arg3[i].z, &sp13C[j], &sp12C[j], &sp11C[j]);
            }
        }

        for (i = 0, j = 0; j < arg1; j++, i += 3) {
            mtxf_transform_point(*spDC, arg4[i], arg4[i + 1], arg4[i + 2], &sp100[j], &spF0[j], &spE0[j]);
        }

        arg2[0] = 0;
        tempv0 = func_80017A18(sp154, arg1, arg2, sp13C, sp12C, sp11C, sp100, spF0, spE0, arg5, surface,
                               1.0 / sp158->trans.scale);
        if (tempv0 != 0) {

            // @fake
            if (!j) {}

            sp158->collisionData->collidedObj = obj;
        }

        if (D_8011AD24[0] == 0) {
            sp14C = func_80017978(obj, sp158);
        }

#ifdef AVOID_UB
        spDC = &sp158->collisionData->matrices[(sp158->collisionData->mtxFlip + 2)];
#else
        spDC = (MtxF *) &sp158->collisionData->_matrices[(sp158->collisionData->mtxFlip + 2) << 1];
#endif

        // @fake
        if (sp158) {}

        sp16C = 1;
        for (i = 0, j = 0; j < arg1; j++, i += 3, sp16C <<= 1) {
            if (sp14C != NULL) {
                sp14C->unk0C[i + 0] = sp100[j];
                sp14C->unk0C[i + 1] = spF0[j];
                sp14C->unk0C[i + 2] = spE0[j];
            }
            if (tempv0 & sp16C) {
                mtxf_transform_point(*spDC, sp100[j], spF0[j], spE0[j], &arg4[i + 0], &arg4[i + 1], &arg4[i + 2]);
            }
        }

        sp168 |= tempv0;
        sp170++;
    }

    arg2[0] = 0;
    if (sp168 & 1) {
        arg2[0]++;
    }
    if (sp168 & 2) {
        arg2[0]++;
    }
    if (sp168 & 4) {
        arg2[0]++;
    }
    if (sp168 & 8) {
        arg2[0]++;
    }
    return sp168;
}

#else
#pragma GLOBAL_ASM("asm/nonmatchings/objects/collision_objectmodel.s")
#endif

unk800179D0 *func_8001790C(Object *arg0, Object *arg1) {
    unk800179D0 *entry;
    s16 i;

    for (i = 0; i < 16; i++) {
        entry = &D_8011AFF4[i];
        if (entry->unk0 != 0 && entry->unk04 == arg0 && entry->unk08 == arg1) {
            entry->unk0 = 0;
            return entry;
        }
    }
    return NULL;
}

unk800179D0 *func_80017978(Object *obj1, Object *obj2) {
    unk800179D0 *entry;
    s16 i;

    for (i = 0; i < 16; i++) {
        entry = &D_8011AFF4[i];
        if (entry->unk0 == 0) {
            entry->unk04 = obj1;
            entry->unk08 = obj2;
            entry->unk0 = 2;
            return entry;
        }
    }
    return NULL;
}

u32 func_800179D0(void) {
    s16 i = 0;
    while (i < 16) {
        unk800179D0 *temp = &D_8011AFF4[i];
        if (temp->unk0 != 0) {
            temp->unk0--;
        }
        i++;
    }
#ifdef AVOID_UB
    return 0;
#endif
}

// https://decomp.me/scratch/xNAlf
#ifdef NON_EQUIVALENT
s32 func_80017A18(ObjectModel *arg0, s32 arg1, s32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6, f32 *arg7,
                  f32 *arg8, f32 *arg9, s8 *argA, f32 argB) {
    f32 *planes;
    s32 i, j, k;
    f32 sum1, sum2;
    f32 t;
    u32 var_a2; // u32 required here to force loading 1 instead of a3 into it
    s32 counter;
    s32 spF8; // f8
    s32 var_s6;
    f32 A2, C2;
    f32 A; // e4
    f32 B; // e0
    f32 C; // dc
    f32 D; // d8
    f32 A1, B1, C1, D1;
    s32 redoLoop;
    f32 spC0; // c0
    f32 x1;   // bc
    f32 y1;
    f32 z1; // b4
    f32 x3, y3, z3;
    f32 x2; // a4
    f32 y2; // a0
    f32 z2; // 9c
    CollisionNode *node;
    f32 dx, dy, dz;
    s32 triIndex;
    s32 closestTri;

    spF8 = 0;
    planes = arg0->collisionPlanes;
    var_s6 = 1;

    for (i = 0; i < arg1; i++) {
        x1 = arg6[i];
        y1 = arg7[i];
        z1 = arg8[i];
        spC0 = arg9[i] * argB;

        counter = 0;
        do {
            redoLoop = FALSE;
            x2 = arg3[i];
            y2 = arg4[i];
            z2 = arg5[i];

            for (j = 0; j < arg0->collisionFacetCount; j++) {
                node = (CollisionNode *) &arg0->collisionFacets[j];
                triIndex = node->colPlaneIndex;

                A = planes[4 * triIndex + 0];
                B = planes[4 * triIndex + 1];
                C = planes[4 * triIndex + 2];
                D = planes[4 * triIndex + 3];

                A2 = A * x2;
                sum1 = A2;
                sum1 += B * y2;
                C2 = C * z2;
                sum1 += C2;
                sum1 = D + sum1;
                sum1 -= spC0;

                sum2 = planes[4 * triIndex + 0] * x1;
                sum2 += planes[4 * triIndex + 1] * y1;
                sum2 += planes[4 * triIndex + 2] * z1;
                sum2 += D;
                sum2 -= spC0;
                if (sum1 >= -0.1 && sum2 < -0.1) {
                    if (sum1 != sum2) {
                        t = sum1 / (sum1 - sum2);
                    } else {
                        t = 0.0f;
                    }
                    x3 = (x1 - x2) * t + x2;
                    y3 = (y1 - y2) * t + y2;
                    z3 = (z1 - z2) * t + z2;
                    var_a2 = TRUE;

                    for (k = 0; k < 3 && var_a2 == TRUE; k++) {
                        closestTri = node->closestTri[k];

                        A1 = planes[4 * closestTri + 0] * x3;
                        B1 = planes[4 * closestTri + 1] * y3;
                        C1 = planes[4 * closestTri + 2] * z3;
                        D1 = planes[4 * closestTri + 3];

                        if (A1 + B1 + C1 + D1 > 4.0f) {
                            var_a2 = FALSE;
                        }
                    }

                    if (var_a2) {
                        redoLoop = TRUE;
                        if (B > 0.707) {
                            y1 = (spC0 - (A2 + C2 + D)) / B;
                        } else {
                            x1 -= sum2 * A;
                            y1 -= sum2 * B;
                            z1 -= sum2 * C;
                        }
                        counter++;
                        if (counter > 10) {
                            redoLoop = FALSE;
                            x1 = x2;
                            y1 = y2;
                            z1 = z2;
                        }
                        argA[i] = 0;
                        arg6[i] = x1;
                        arg7[i] = y1;
                        arg8[i] = z1;
                        j = arg0->collisionFacetCount; // break
                    }
                }
            }
        } while (redoLoop);

        if (counter > 0) {
            arg2[0]++;
            spF8 |= var_s6;
        }
        var_s6 <<= 1;
    }

    return spF8;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_80017A18.s")
#endif

/**
 * Sets the active Taj challenge.
 */
void set_taj_challenge_type(s32 vehicleID) {
    gTajChallengeType = vehicleID;
    gPathUpdateOff = FALSE;
}

/**
 * Returns which Taj challenge is currently active.
 */
UNUSED s16 get_taj_challenge_type(void) {
    return gTajChallengeType;
}

/**
 * Updates information pertaining to all checkpoints in the current race.
 */
void checkpoint_update_all(void) {
    f32 xDiff;
    f32 zDiff;
    f32 yDiff;
    s32 tempCheckpointID;
    s32 checkpointNum;
    s32 duplicateCheckpoint;
    s32 breakOut;
    s32 altRouteId;
    s32 i;
    s32 isSorted;
    s32 checkpointID;
    f32 ox;
    f32 oy;
    f32 oz;
    Object *obj;
    CheckpointNode *checkpoint;
    LevelObjectEntry_Checkpoint *checkpointEntry;
    MtxF mtx;
    ObjectTransform transform;
    s32 alternateCount;

    alternateCount = 0;
    gNumberOfMainCheckpoints = 0;
    for (i = 0; i < gObjectCount; i++) {
        obj = gObjPtrList[i];
        if (!(obj->trans.flags & OBJ_FLAGS_PARTICLE) && obj->behaviorId == BHV_CHECKPOINT &&
            gNumberOfMainCheckpoints < MAX_CHECKPOINTS) {
            checkpointEntry = &obj->level_entry->checkpoint;
            if (checkpointEntry->vehicleType == gTajChallengeType) {
                gTrackCheckpoints[gNumberOfMainCheckpoints].obj = obj;
                checkpointID = checkpointEntry->index;
                if (checkpointEntry->isAltCheckpoint) {
                    checkpointID += 255;
                    alternateCount++;
                }
                gTrackCheckpoints[gNumberOfMainCheckpoints].checkpointID = checkpointID;
                gTrackCheckpoints[gNumberOfMainCheckpoints].altRouteID = -1;
                gNumberOfMainCheckpoints++;
            }
        }
    }

    duplicateCheckpoint = FALSE;
    do {
        isSorted = TRUE;

        for (i = 0; i < gNumberOfMainCheckpoints - 1; i++) {
            if (gTrackCheckpoints[i].checkpointID == gTrackCheckpoints[i + 1].checkpointID) {
                duplicateCheckpoint = TRUE;
                checkpointNum = gTrackCheckpoints[i].checkpointID;
            }

            if (gTrackCheckpoints[i + 1].checkpointID < gTrackCheckpoints[i].checkpointID) {
                tempCheckpointID = gTrackCheckpoints[i].checkpointID;
                obj = gTrackCheckpoints[i].obj;
                gTrackCheckpoints[i].checkpointID = gTrackCheckpoints[i + 1].checkpointID;
                gTrackCheckpoints[i].obj = gTrackCheckpoints[i + 1].obj;
                gTrackCheckpoints[i + 1].checkpointID = tempCheckpointID;
                gTrackCheckpoints[i + 1].obj = obj;
                isSorted = FALSE;
            }
        }
    } while (!isSorted);
    gNumberOfTotalCheckpoints = gNumberOfMainCheckpoints;
    gNumberOfMainCheckpoints -= alternateCount;
    if (duplicateCheckpoint) {
        set_render_printf_position(20, 220);
        render_printf("Error: Multiple checkpoint no: %d !!\n", checkpointNum);
    }
    for (i = gNumberOfMainCheckpoints; i < gNumberOfTotalCheckpoints; i++) {
        tempCheckpointID = gTrackCheckpoints[i].checkpointID - 255;
        for (checkpointID = 0, breakOut = FALSE; checkpointID < gNumberOfMainCheckpoints && !breakOut; checkpointID++) {
            if (tempCheckpointID == gTrackCheckpoints[checkpointID].checkpointID) {
                gTrackCheckpoints[checkpointID].altRouteID = i;
                gTrackCheckpoints[i].altRouteID = checkpointID;
                breakOut = TRUE;
            }
        }
    }

    for (i = 0; i < gNumberOfTotalCheckpoints; i++) {
        checkpoint = &gTrackCheckpoints[i];
        obj = checkpoint->obj;
        checkpointEntry = &obj->level_entry->checkpoint;
        transform.rotation.y_rotation = obj->trans.rotation.y_rotation;
        transform.rotation.x_rotation = obj->trans.rotation.x_rotation;
        transform.rotation.z_rotation = obj->trans.rotation.z_rotation;
        transform.scale = 1.0f;
        transform.x_position = 0.0f;
        transform.y_position = 0.0f;
        transform.z_position = 0.0f;
        mtxf_from_transform(&mtx, &transform);
        mtxf_transform_point(mtx, 0.0f, 0.0f, 1.0f, &ox, &oy, &oz);
        checkpoint->rotationXFrac = ox;
        checkpoint->rotationYFrac = oy;
        checkpoint->rotationZFrac = oz;
        checkpoint->unkC =
            -(((obj->trans.x_position * ox) + (obj->trans.y_position * oy)) + (obj->trans.z_position * oz));
        checkpoint->x = obj->trans.x_position;
        checkpoint->y = obj->trans.y_position;
        checkpoint->z = obj->trans.z_position;
        checkpoint->scale = obj->trans.scale * 2;
        checkpoint->checkpointID = obj->trans.scale * 128.0f;
        checkpoint->altDistance = 0.0f;
        checkpoint->distance = 0.0f;
        if (i < gNumberOfMainCheckpoints) {
            tempCheckpointID = i + 1;
            if (tempCheckpointID == gNumberOfMainCheckpoints) {
                tempCheckpointID = 0;
            }
            xDiff = obj->trans.x_position - gTrackCheckpoints[tempCheckpointID].obj->trans.x_position;
            yDiff = obj->trans.y_position - gTrackCheckpoints[tempCheckpointID].obj->trans.y_position;
            zDiff = obj->trans.z_position - gTrackCheckpoints[tempCheckpointID].obj->trans.z_position;
            checkpoint->distance = sqrtf(((xDiff * xDiff) + (yDiff * yDiff)) + (zDiff * zDiff));
            altRouteId = gTrackCheckpoints[tempCheckpointID].altRouteID;
            if (altRouteId != -1) {
                xDiff = obj->trans.x_position - gTrackCheckpoints[altRouteId].obj->trans.x_position;
                yDiff = obj->trans.y_position - gTrackCheckpoints[altRouteId].obj->trans.y_position;
                zDiff = obj->trans.z_position - gTrackCheckpoints[altRouteId].obj->trans.z_position;
                checkpoint->altDistance = sqrtf(((xDiff * xDiff) + (yDiff * yDiff)) + (zDiff * zDiff));
            } else {
                checkpoint->altDistance = checkpoint->distance;
            }
        } else {
            tempCheckpointID = gTrackCheckpoints[i].altRouteID + 1;
            if (tempCheckpointID == gNumberOfMainCheckpoints) {
                tempCheckpointID = 0;
            }
            xDiff = obj->trans.x_position - gTrackCheckpoints[tempCheckpointID].obj->trans.x_position;
            yDiff = obj->trans.y_position - gTrackCheckpoints[tempCheckpointID].obj->trans.y_position;
            zDiff = obj->trans.z_position - gTrackCheckpoints[tempCheckpointID].obj->trans.z_position;
            checkpoint->distance = sqrtf(((xDiff * xDiff) + (yDiff * yDiff)) + (zDiff * zDiff));
            altRouteId = gTrackCheckpoints[tempCheckpointID].altRouteID;
            if (altRouteId != -1) {
                xDiff = obj->trans.x_position - gTrackCheckpoints[altRouteId].obj->trans.x_position;
                yDiff = obj->trans.y_position - gTrackCheckpoints[altRouteId].obj->trans.y_position;
                zDiff = obj->trans.z_position - gTrackCheckpoints[altRouteId].obj->trans.z_position;
                checkpoint->altDistance = sqrtf(((xDiff * xDiff) + (yDiff * yDiff)) + (zDiff * zDiff));
            } else {
                checkpoint->altDistance = checkpoint->distance;
            }
        }
        checkpoint->unk2E[0] = checkpointEntry->unkB;
        checkpoint->unk32[0] = checkpointEntry->unkF;
        checkpoint->unk36[0] = checkpointEntry->unk13;
        checkpoint->unk2E[1] = checkpointEntry->unkC;
        checkpoint->unk32[1] = checkpointEntry->unk10;
        checkpoint->unk36[1] = checkpointEntry->unk14;
        checkpoint->unk2E[2] = checkpointEntry->unkD;
        checkpoint->unk32[2] = checkpointEntry->unk11;
        checkpoint->unk36[2] = checkpointEntry->unk15;
        checkpoint->unk2E[3] = checkpointEntry->unkE;
        checkpoint->unk32[3] = checkpointEntry->unk12;
        checkpoint->unk36[3] = checkpointEntry->unk16;
        checkpoint->unk3B = checkpointEntry->unk19;
    }
}

/**
 * Checks to see whether a racer or homing missile passed a checkpoint.
 * Return values:
 * - 0: Homing missile passed the checkpoint.
 * - -100: Racer passed the checkpoint.
 * - Otherwise: No checkpoint has been passed.
 */
s32 checkpoint_is_passed(s32 checkpointIndex, Object *obj, f32 objX, f32 objY, f32 objZ, f32 *checkpointDistance,
                         u8 *isOnAlternateRoute) {
    s32 retLength;
    s32 isAltCheckpoint;
    f32 distX, distY, distZ;
    f32 length;
    f32 nextLength;
    f32 toNext;
    Object_Racer *racer;
    f32 fromPrev;
    CheckpointNode *currentCheckpoint;
    CheckpointNode *prevCheckpoint;
    CheckpointNode *altRouteCheckpoint;

    if (gNumberOfMainCheckpoints == 0) {
        return 1;
    }

    currentCheckpoint = &gTrackCheckpoints[checkpointIndex];
    if (checkpointIndex != 0) {
        prevCheckpoint = &gTrackCheckpoints[checkpointIndex - 1];
    } else {
        prevCheckpoint = &gTrackCheckpoints[gNumberOfMainCheckpoints - 1];
    }

    if (*isOnAlternateRoute) {
        if (currentCheckpoint->altRouteID != -1) {
            currentCheckpoint = &gTrackCheckpoints[currentCheckpoint->altRouteID];
        }
        if (prevCheckpoint->altRouteID != -1) {
            prevCheckpoint = &gTrackCheckpoints[prevCheckpoint->altRouteID];
        }
    }

    isAltCheckpoint = FALSE;
    if (!(*isOnAlternateRoute) && prevCheckpoint->altRouteID == -1 && currentCheckpoint->altRouteID != -1) {
        altRouteCheckpoint = &gTrackCheckpoints[currentCheckpoint->altRouteID];
        distX = altRouteCheckpoint->x - obj->trans.x_position;
        distY = altRouteCheckpoint->y - obj->trans.y_position;
        distZ = altRouteCheckpoint->z - obj->trans.z_position;
        if (sqrtf(distX * distX + distY * distY + distZ * distZ) < altRouteCheckpoint->checkpointID) {
            currentCheckpoint = altRouteCheckpoint;
            isAltCheckpoint = TRUE;
        }
    }

    distX = currentCheckpoint->x - prevCheckpoint->x;
    distY = currentCheckpoint->y - prevCheckpoint->y;
    distZ = currentCheckpoint->z - prevCheckpoint->z;
    length = sqrtf(distX * distX + distY * distY + distZ * distZ);
    if (length > 0.0) {
        distX *= 1.0f / length;
        distY *= 1.0f / length;
        distZ *= 1.0f / length;
    }

    toNext = currentCheckpoint->rotationXFrac * obj->trans.x_position +
             currentCheckpoint->rotationYFrac * obj->trans.y_position +
             currentCheckpoint->rotationZFrac * obj->trans.z_position + currentCheckpoint->unkC;

    nextLength = currentCheckpoint->rotationXFrac * distX + currentCheckpoint->rotationYFrac * distY +
                 currentCheckpoint->rotationZFrac * distZ;
    nextLength = -toNext / nextLength;

    fromPrev = prevCheckpoint->rotationXFrac * obj->trans.x_position +
               prevCheckpoint->rotationYFrac * obj->trans.y_position +
               prevCheckpoint->rotationZFrac * obj->trans.z_position + prevCheckpoint->unkC;

    length = prevCheckpoint->rotationXFrac * distX + prevCheckpoint->rotationYFrac * distY +
             prevCheckpoint->rotationZFrac * distZ;
    length = fromPrev / length;

    if (nextLength + length != 0.0) {
        length = nextLength / (nextLength + length);
    } else {
        length = 0.0f;
    }
    *checkpointDistance = length;

    if (obj->behaviorId == BHV_RACER) {
        racer = obj->racer;
        if (racer->playerIndex == PLAYER_COMPUTER) {
            if (length < -0.3) {
                return -100;
            }
            if (length > 1.3) {
                return -100;
            }
        }
    }

    if (nextLength <= 0) {
        if (isAltCheckpoint) {
            *isOnAlternateRoute = TRUE;
        } else if (currentCheckpoint->altRouteID == -1) {
            *isOnAlternateRoute = FALSE;
        }

        distY = currentCheckpoint->rotationXFrac * objX + currentCheckpoint->rotationYFrac * objY +
                currentCheckpoint->rotationZFrac * objZ + currentCheckpoint->unkC;
        if (distY > 0) {
            if (obj->behaviorId == BHV_RACER) {
                Object_Racer *objRacer = obj->racer;
                if (currentCheckpoint->unk3B != 0) {
                    objRacer->indicator_type = currentCheckpoint->unk3B;
                    objRacer->indicator_timer = 120;
                }
            }

            prevCheckpoint = currentCheckpoint;
            checkpointIndex++;
            if (checkpointIndex == gNumberOfMainCheckpoints) {
                checkpointIndex = 0;
            }

            currentCheckpoint = &gTrackCheckpoints[checkpointIndex];

            toNext = currentCheckpoint->rotationXFrac * obj->trans.x_position +
                     currentCheckpoint->rotationYFrac * obj->trans.y_position +
                     currentCheckpoint->rotationZFrac * obj->trans.z_position + currentCheckpoint->unkC;
            nextLength = currentCheckpoint->rotationXFrac * distX + currentCheckpoint->rotationYFrac * distY +
                         currentCheckpoint->rotationZFrac * distZ;
            nextLength = -toNext / nextLength;

            fromPrev = prevCheckpoint->rotationXFrac * obj->trans.x_position +
                       prevCheckpoint->rotationYFrac * obj->trans.y_position +
                       prevCheckpoint->rotationZFrac * obj->trans.z_position + prevCheckpoint->unkC;
            length = prevCheckpoint->rotationXFrac * distX + prevCheckpoint->rotationYFrac * distY +
                     prevCheckpoint->rotationZFrac * distZ;
            length = fromPrev / length;

            if (nextLength + length != 0.0) {
                length = nextLength / (nextLength + length);
            } else {
                length = 0.0;
            }
            *checkpointDistance = length;
        } else {
            *checkpointDistance = 0.0;
        }
        return 0;
    } else {
        retLength = length * 100.0f;
        if (retLength == 0) {
            retLength++;
        }
        return retLength;
    }
}

/**
 * Search and return Taj's overworld object.
 * Used for drawing his minimap position.
 */
Object *find_taj_object(void) {
    s32 i;
    Object *current_obj;
    for (i = gObjectListStart; i < gObjectCount; i++) {
        current_obj = gObjPtrList[i];
        if (!(current_obj->trans.flags & OBJ_FLAGS_PARTICLE) && (current_obj->behaviorId == BHV_PARK_WARDEN)) {
            return current_obj;
        }
    }
    return NULL;
}

// Handles MidiFadePoint, MidiFade, and MidiSetChannel objects?
void func_80018CE0(Object *racerObj, f32 xPos, f32 yPos, f32 zPos, s32 updateRate) {
    f32 temp_f0;
    s32 pad_spF8;
    s32 spF4;
    s32 pad_spF0;
    f32 temp_f22;
    s32 pad_spE8;
    s32 pad_spE4;
    s32 pad_spE0;
    f32 temp_f2;
    s32 pad_spD8;
    f32 tempF2;
    s32 temp_f10;
    s32 temp_t3_2;
    s32 i; // s1
    s32 var_s2;
    f32 spC0;
    Object_MidiFadePoint *midiFadePoint; // spBC
    f32 tempF;
    u16 temp_t4;
    s8 var_v0_2;
    u8 var_v0_u;
    s8 var_v1;
    Object *obj;
    Object_MidiFade *midiFade;
    Object_MidiChannelSet *midiChannelSet;
    Object_Racer *racer;

    racer = racerObj->racer;
    if (racer->playerIndex != 0) {
        return;
    }

    if (cam_get_viewport_layout() != 0) {
        return;
    }

    for (spF4 = gObjectListStart; spF4 < gObjectCount; spF4++) {
        obj = gObjPtrList[spF4];
        if (!(obj->trans.flags & 0x8000)) {
            if (obj->behaviorId == BHV_MIDI_FADE_POINT) {
                spC0 = sqrtf(((racerObj->trans.x_position - obj->trans.x_position) *
                              (racerObj->trans.x_position - obj->trans.x_position)) +
                             ((racerObj->trans.y_position - obj->trans.y_position) *
                              (racerObj->trans.y_position - obj->trans.y_position)) +
                             ((racerObj->trans.z_position - obj->trans.z_position) *
                              (racerObj->trans.z_position - obj->trans.z_position)));
                midiFadePoint = obj->midi_fade_point;
                if (spC0 < midiFadePoint->unk2) {
                    if (midiFadePoint->unk1C == music_current_sequence()) {
                        if (spC0 <= midiFadePoint->unk0) {
                            var_s2 = 0;
                        } else {
                            spC0 -= midiFadePoint->unk0;
                            temp_f0 = (midiFadePoint->unk2 - midiFadePoint->unk0);
                            var_s2 = (127.0f * spC0) / temp_f0;
                        }
                        for (i = 0; i < 16; i++) {
                            switch (midiFadePoint->unkC[i]) {
                                case 1:
                                    if (var_s2 >= 0x7B) {
                                        music_channel_off(i);
                                    } else {
                                        music_channel_fade_set(i, (0x7F - var_s2));
                                        music_channel_on(i);
                                    }
                                    break;
                                case 2:
                                    if ((music_channel_fade(i) > 0) && (music_channel_active(i) == 0)) {
                                        music_channel_fade_set(i, var_s2);
                                    }
                                    break;
                                default:
                                    stubbed_printf("ERROR Channel %d\n", i);
                                    break;
                            }
                        }
                    }
                }
            } else if (obj->behaviorId == BHV_MIDI_FADE) {
                midiFade = obj->midi_fade;

                temp_f0 =
                    (midiFade->unk8 * xPos) + (midiFade->unkC * yPos) + (midiFade->unk10 * zPos) + midiFade->unk14;
                temp_f2 = (midiFade->unk8 * racerObj->trans.x_position) +
                          (midiFade->unkC * racerObj->trans.y_position) +
                          (midiFade->unk10 * racerObj->trans.z_position) + midiFade->unk14;
                if (temp_f0 > 0.0f && temp_f2 <= 0.0f) {
                    var_v1 = 1;
                } else if (temp_f2 > 0.0f && temp_f0 <= 0.0f) {
                    var_v1 = -1;
                } else {
                    var_v1 = 0;
                }
                if (var_v1 != 0) {
                    temp_f0 = racerObj->trans.x_position - xPos;
                    temp_f2 = racerObj->trans.y_position - yPos;

                    temp_f22 =
                        (-midiFade->unk8 * xPos - midiFade->unkC * yPos - midiFade->unk10 * zPos - midiFade->unk14) /
                        (midiFade->unk8 * temp_f0 + midiFade->unkC * temp_f2 +
                         midiFade->unk10 * (racerObj->trans.z_position - zPos));
                    tempF = temp_f22 * temp_f0;
                    if ((midiFade->unk18 <= tempF + xPos) && (tempF + xPos <= midiFade->unk24)) {
                        tempF2 = racerObj->trans.z_position - zPos;
                        if ((midiFade->unk1C <= (temp_f22 * temp_f2) + yPos) &&
                            ((temp_f22 * temp_f2) + yPos <= midiFade->unk28)) {
                            if ((midiFade->unk20 <= (temp_f22 * (tempF2)) + zPos) &&
                                ((temp_f22 * (tempF2)) + zPos <= midiFade->unk2C)) {
                                midiFade->unk0 = var_v1;
                                midiFade->unk1 = 0;
                                midiFade->unk4 = 0;
                                D_8011AF60 = midiFade;
                            }
                        }
                    }
                }
            } else if (obj->behaviorId == BHV_MIDI_CHANNEL_SET) {
                midiChannelSet = obj->midi_channel_set;
                temp_f0 = sqrtf(((racerObj->trans.x_position - obj->trans.x_position) *
                                 (racerObj->trans.x_position - obj->trans.x_position)) +
                                ((racerObj->trans.y_position - obj->trans.y_position) *
                                 (racerObj->trans.y_position - obj->trans.y_position)) +
                                ((racerObj->trans.z_position - obj->trans.z_position) *
                                 (racerObj->trans.z_position - obj->trans.z_position)));
                var_v0_u = midiChannelSet->unk2;
                if ((temp_f0 < (var_v0_u * 4)) && (midiChannelSet->unk0 != music_channel_get_mask()) &&
                    (midiChannelSet->unk3 == music_current_sequence())) {
                    music_dynamic_set(midiChannelSet->unk0);
                }
            }
        }
    }

    if (D_8011AF60 == 0) {
        return;
    }

    if (D_8011AF60->unk40 == music_current_sequence()) {
        D_8011AF60->unk4 += updateRate;
        temp_t4 = D_8011AF60->unk2 * gVideoRefreshRate;
        if (temp_t4 < D_8011AF60->unk4) {
            D_8011AF60->unk4 = temp_t4;
        }
        temp_f10 = (D_8011AF60->unk4 * 254.0f) / temp_t4;
        if (temp_f10 < 0xFE) {
            D_8011AF60->unk1 = temp_f10;
        } else {
            D_8011AF60->unk1 = 0xFE;
        }
        for (i = 0; i < 16; i++) {
            var_v0_2 = D_8011AF60->unk2F[i];
            if (D_8011AF60->unk0 == -1) {
                var_v0_2 >>= 2;
            }
            var_v0_2 &= 3;
            switch (var_v0_2) {
                case 1:
                    music_channel_on(i);
                    music_channel_fade_set(i, 0x7FU);
                    break;
                case 0:
                    music_channel_off(i);
                    break;
                case 3:
                    if (D_8011AF60->unk1 >= 0x80) {
                        temp_t3_2 = (D_8011AF60->unk1 - 0x7F) & 0xFF;
                        music_channel_on(i);
                        if (music_channel_fade(i) < temp_t3_2) {
                            music_channel_fade_set(i, temp_t3_2);
                        }
                    }
                    break;
                case 2:
                    if (D_8011AF60->unk1 < 0x7F) {
                        temp_t3_2 = (0x7F - D_8011AF60->unk1) & 0xFF;
                        if (temp_t3_2 < music_channel_fade(i)) {
                            music_channel_fade_set(i, temp_t3_2);
                        }
                    } else {
                        music_channel_off(i);
                    }
                    break;
                default:
                    break;
            }
        }
    }
    if ((D_8011AF60->unk1 == 0xFE) && (D_8011AF60->unk40 == music_current_sequence())) {
        D_8011AF60 = 0;
    }
}

/**
 * Calculates the direction a homing rocket takes toward the next checkpoint.
 * Returns true if a direction was calculated, or false if there are no checkpoints.
 */
s32 homing_rocket_get_next_direction(Object *obj, s32 checkpoint, u8 isOnAlternateRoute, s32 arg3, s32 arg4,
                                     f32 checkpointDist, f32 *outX, f32 *outY, f32 *outZ) {
    s32 numCheckpoints;
    s32 checkpointIndex;
    s32 i;
    f32 xData[4];
    f32 yData[4];
    f32 zData[4];
    f32 xSpline;
    f32 temp2;
    f32 zSpline;
    f32 ySpline;
    f32 dx;
    f32 dy;
    f32 dz;
    CheckpointNode *checkpointNode;

    numCheckpoints = gNumberOfMainCheckpoints;
    if (numCheckpoints == 0) {
        return FALSE;
    }
    checkpointIndex = checkpoint - 2;
    if (checkpointIndex < 0) {
        checkpointIndex += numCheckpoints;
    }
    for (i = 0; i < 4; i++) {
        checkpointNode = find_next_checkpoint_node(checkpointIndex, isOnAlternateRoute);
        xData[i] = checkpointNode->x + (checkpointNode->scale * checkpointNode->rotationZFrac * arg3);
        yData[i] = checkpointNode->y + (checkpointNode->scale * arg4);
        zData[i] = checkpointNode->z + (checkpointNode->scale * -checkpointNode->rotationXFrac * arg3);
        checkpointIndex += 1;
        if (checkpointIndex == numCheckpoints) {
            checkpointIndex = 0;
        }
    }
    temp2 = (1.0 - checkpointDist);
    if (temp2 < 0.0f) {
        temp2 = 0.0f;
    }
    if (temp2 > 1.0) {
        temp2 = 1.0f;
    }
    xSpline = cubic_spline_interpolation(xData, 0, temp2, &dx);
    ySpline = cubic_spline_interpolation(yData, 0, temp2, &dy);
    zSpline = cubic_spline_interpolation(zData, 0, temp2, &dz);
    temp2 = sqrtf((dx * dx) + (dy * dy) + (dz * dz));
    if (temp2 != 0.0f) {
        temp2 = 500.0 / temp2;
        dx *= temp2;
        dy *= temp2;
        dz *= temp2;
    }
    *outX = (xSpline + dx) - obj->trans.x_position;
    *outY = (ySpline + dy) - obj->trans.y_position;
    *outZ = (zSpline + dz) - obj->trans.z_position;
    return TRUE;
}

// D_B0000574 is a direct read from the ROM as opposed to RAM
extern s32 D_B0000574;

/**
 * Check the win conditions of the current race.
 * This varies based on the race type, so this does a multitude of different possible things.
 * When the race is finished, it will then for the most part trigger the next menu,
 * but adventure mode will start the balloon cutscene if it has not yet been awarded.
 */
void race_check_finish(s32 updateRate) {
    s32 prevRacerPos;
    s32 i;
    s32 j;
    s32 racerPos;
    Settings *settings;
    s16 numHumanRacers;
    s16 numHumanRacersFinished;
    Object_Racer *curRacer2;
    Object_Racer *curRacer;
    s16 numFinishedRacers;
    s16 foundIndex;
    Object_Racer *racer[4];
    s16 racerIndex;
    s8 raceType;
    s8 someBool;
    LevelHeader *currentLevelHeader;
    s32 newStartingPosition;
    s8 sp5C[4];
    s8 someBool2;
    s8 flags[3];
    s32 camera;

    currentLevelHeader = level_header();
    settings = get_settings();
    numHumanRacersFinished = 0;
    numHumanRacers = 0;
    someBool2 = currentLevelHeader->race_type;
    numFinishedRacers = 0;
    if (someBool2 != RACETYPE_DEFAULT && someBool2 != RACETYPE_HORSESHOE_GULCH && someBool2 != RACETYPE_BOSS) {
        if (someBool2 & RACETYPE_CHALLENGE) {
            if (someBool2 == RACETYPE_CHALLENGE_EGGS) {
                racer_update_eggs(*gRacers);
            }
            if (gRaceFinishTriggered == FALSE) {
                for (i = 0; i < gNumRacers; i++) {
                    racer[i] = (*gRacers)[i]->racer;
                    // Manage eliminated racers in deathmatch.
                    if (currentLevelHeader->race_type == RACETYPE_CHALLENGE_BATTLE && racer[i]->bananas <= 0 &&
                        !racer[i]->raceFinished) {
                        racer[i]->raceFinished = TRUE;
                        racer[i]->balloon_quantity = 0;
                        racer_sound_free((*gRacers)[i]);
                        (*gRacers)[i]->trans.flags |= OBJ_FLAGS_INVISIBLE;
                        (*gRacers)[i]->interactObj->flags = INTERACT_FLAGS_NONE;
                        racer[i]->finishPosition = 5 - gNumFinishedRacers;
                        gNumFinishedRacers++;
                    }
                    if (racer[i]->playerIndex != PLAYER_COMPUTER) {
                        if (racer[i]->raceFinished) {
                            numHumanRacersFinished++;
                        }
                        numHumanRacers++;
                    }
                    if (racer[i]->raceFinished) {
                        numFinishedRacers++;
                        if (racer[i]->finishPosition == 0) {
                            racer[i]->finishPosition = gNumFinishedRacers;
                            gNumFinishedRacers++;
                        }
                    }
                }
                if ((currentLevelHeader->race_type != RACETYPE_CHALLENGE_BATTLE && numFinishedRacers > 0) ||
                    ((((numHumanRacers == 1 && numHumanRacersFinished == 1) ||
                       (numHumanRacers >= 2 && numHumanRacersFinished >= numHumanRacers)) ||
                      numFinishedRacers >= 3))) {
                    for (i = 0; i < gNumRacers; i++) {
                        if (currentLevelHeader->race_type == RACETYPE_CHALLENGE_BATTLE) {
                            sp5C[i] = 10 - racer[i]->bananas;
                        } else {
                            sp5C[i] = racer[i]->lap;
                            if (currentLevelHeader->race_type == RACETYPE_CHALLENGE_EGGS) {
                                sp5C[i] *= 3;
                                if (racer[i]->eggHudCounter != 0) {
                                    sp5C[i] += 2;
                                } else if (racer[i]->held_obj != NULL) {
                                    sp5C[i] += 1;
                                }
                            }
                        }
                        if (sp5C[i] > 10) {
                            sp5C[i] = 10;
                        }
                        if (sp5C[i] < 0) {
                            sp5C[i] = 0;
                        }
                    }

                    i = 0;
                    do {
                        racerIndex = -1;
                        foundIndex = -1;
                        for (i = 0; i < gNumRacers; i++) {
                            if (!racer[i]->raceFinished && sp5C[i] >= foundIndex) {
                                foundIndex = sp5C[i];
                                racerIndex = i;
                            }
                        }

                        if (racerIndex != -1) {
                            // In battle mode, last to finish wins, so flip the finish order.
                            if (currentLevelHeader->race_type == RACETYPE_CHALLENGE_BATTLE) {
                                racer[racerIndex]->finishPosition = 5 - gNumFinishedRacers;
                            } else {
                                racer[racerIndex]->finishPosition = gNumFinishedRacers;
                            }
                            gNumFinishedRacers++;
                            racer[racerIndex]->raceFinished = TRUE;
                        }
                        i = 0;
                    } while (racerIndex != -1);

                    gSwapLeadPlayer = FALSE;
                    // Award the winner a TT amulet if not in tracks mode.
                    if (!is_in_tracks_mode() &&
                        (racer[0]->finishPosition == 1 ||
                         (is_in_two_player_adventure() && racer[1]->finishPosition == 1)) &&
                        (!(settings->courseFlagsPtr[settings->courseId] & RACE_CLEARED))) {
                        settings->courseFlagsPtr[settings->courseId] |= RACE_CLEARED;
                        i = settings->ttAmulet + 1;
                        if (i > 4) {
                            i = 4;
                        }
                        settings->ttAmulet = i;
                    }
                    for (racerPos = 0; racerPos < 8;) {
                        settings->racers[racerPos++].starting_position = -1;
                    }

                    newStartingPosition = SEQUENCE_BATTLE_LOSE;
                    for (racerPos = 0; racerPos < gNumRacers; racerPos++) {
                        if (racer[racerPos]->playerIndex != PLAYER_COMPUTER && racer[racerPos]->finishPosition == 1) {
                            newStartingPosition = SEQUENCE_BATTLE_VICTORY;
                        }
                        settings->racers[racerPos].starting_position = racer[racerPos]->finishPosition - 1;
                    }

                    music_play(newStartingPosition);
                    newStartingPosition = 4;
                    for (prevRacerPos = 0; prevRacerPos < 8; prevRacerPos++) {
                        if (settings->racers[prevRacerPos].starting_position == -1) {
                            settings->racers[prevRacerPos].starting_position = newStartingPosition;
                            newStartingPosition++;
                        }
                    }

                    gSwapLeadPlayer = FALSE;
                    if (is_in_two_player_adventure() && settings->racers[PLAYER_TWO].starting_position <
                                                            settings->racers[PLAYER_ONE].starting_position) {
                        gSwapLeadPlayer = TRUE;
                    }
                    // i will be nonzero if any adventure mode award triggers happened.
                    if (i == 0) {
                        if (is_in_two_player_adventure()) {
                            if (gSwapLeadPlayer) {
                                gSwapLeadPlayer = FALSE;
                                swap_lead_player();
                                if (gLeadPlayerIndex != 0) {
                                    gIsP2LeadPlayer = TRUE;
                                }
                            } else if (gLeadPlayerIndex != 0) {
                                gIsP2LeadPlayer = TRUE;
                            }
                        }
                        postrace_start(0, 30);
                    } else {
                        level_properties_push(SPECIAL_MAP_ID_NO_LEVEL, 0, VEHICLE_CAR, CUTSCENE_ID_NONE);
                        level_properties_push(ASSET_LEVEL_TTAMULETSEQUENCE, 0, VEHICLE_NO_OVERRIDE,
                                              settings->ttAmulet - 1);
                        race_finish_adventure(TRUE);
                    }
                    gRaceFinishTriggered = TRUE;
                }
            }
        }
        return;
    }

    i = 0;
    do {
        racerPos = 1;
        curRacer = (*gRacers)[i]->racer;
        prevRacerPos = curRacer->racerOrder;
        j = 0;
        do {
            if (j != i) {
                curRacer2 = (*gRacers)[j]->racer;
                if (curRacer->raceFinished == FALSE && curRacer2->raceFinished != FALSE) {
                    racerPos++;
                } else if (curRacer->courseCheckpoint < curRacer2->courseCheckpoint) {
                    racerPos++;
                } else if (curRacer->courseCheckpoint == curRacer2->courseCheckpoint) {
                    if (curRacer2->unk1A8 < curRacer->unk1A8) {
                        racerPos++;
                    }
                    if (curRacer->unk1A8 == curRacer2->unk1A8 && i < j) {
                        racerPos++;
                    }
                }
            }
            j++;
        } while (j < gNumRacers);

        curRacer->racerOrder = racerPos;
        if (curRacer->lap < currentLevelHeader->laps) {
            if (prevRacerPos == curRacer->racerOrder) {
                if (curRacer->unk1B0 < 2) {
                    if (curRacer->vehicleID != VEHICLE_LOOPDELOOP) {
                        curRacer->unk1B0++;
                    }
                } else if (curRacer->racerOrder != curRacer->racePosition) {
                    curRacer->unk1B2 = 10;
                    curRacer->racePosition = curRacer->racerOrder;
                }
            } else {
                curRacer->unk1B0 = 0;
            }
        }
        i++;
    } while (i < gNumRacers);

    i = 0;
    do {
        curRacer = (*gRacers)[i]->racer;
        if (curRacer->lap >= currentLevelHeader->laps && curRacer->raceFinished == FALSE) {
            if (get_game_mode() != GAMEMODE_UNUSED_4) {
                curRacer->raceFinished = TRUE;
                curRacer->finishPosition = gNumFinishedRacers;
                if (gNumFinishedRacers == 1 && curRacer->playerIndex == PLAYER_COMPUTER) {
                    sound_play(SOUND_WHOOSH5, NULL);
                }
                gNumFinishedRacers++;
            }
        }
        if (curRacer->playerIndex != PLAYER_COMPUTER) {
            numHumanRacers++;
            if (curRacer->raceFinished) {
                // clang-format off
                numHumanRacersFinished++;\
                numFinishedRacers++;
                // clang-format on
            }
        } else if (curRacer->raceFinished) {
            numFinishedRacers++;
        }
        i++;
    } while (i < gNumRacers);

    i = 0;
    do {
        gRacersByPosition[i] = 0;
        i++;
    } while (i < gNumRacers);

    i = 0;
    do {
        curRacer = (*gRacers)[i]->racer;
        if (curRacer->raceFinished) {
            racerPos = curRacer->finishPosition - 1;
        } else {
            racerPos = curRacer->racerOrder - 1;
        }
        gRacersByPosition[racerPos] = (*gRacers)[i];
        i++;
    } while (i < gNumRacers);

    i = 0;
    j = 0;
    do {
        // @fake
        if (1) {}

        someBool = FALSE;

        for (; j < gNumRacers; j++) {
            if (gRacersByPosition[j] == (*gRacers)[i]) {
                someBool = TRUE;
                if (!curRacer) {}
                j = gNumRacers;
            }
        }

        j = 0;
        if (someBool == FALSE) {
            for (; j < gNumRacers; j++) {
                if (gRacersByPosition[j] == 0) {
                    gRacersByPosition[j] = (*gRacers)[i];
                    j = gNumRacers;
                }
            }
        }
        j = 0;
        i++;
    } while (i < gNumRacers);

    j = 0;
    for (i = 0; i < MAXCONTROLLERS; i++) {
        // @fake
        if (1) {}
        if (1) {}
        if (1) {}
        if (1) {}
        j |= input_pressed(i);
    }

    if (gIsTajChallenge && numHumanRacersFinished != 0) {
        mode_end_taj_race(CHALLENGE_END_FINISH);
    } else if (D_8011AD3C != 0 && numFinishedRacers != 0) {
        curRacer = (*gRacers)[0]->racer;
        if (!curRacer->raceFinished) {
            curRacer->raceFinished = TRUE;
            curRacer->finishPosition = gNumFinishedRacers;
            gNumFinishedRacers++;
        }
    } else if (gRaceFinishTriggered == FALSE) {
        someBool2 = FALSE;
        if (is_in_two_player_adventure() && numHumanRacersFinished > 0 && get_trophy_race_world_id() == 0 &&
            set_course_finish_flags(settings) != 0) {
            someBool2 = TRUE;
        }
        if ((numHumanRacersFinished == numHumanRacers ||
             (numHumanRacers >= 2 && numFinishedRacers >= (gNumRacers - 1))) ||
            someBool2) {
            if (numHumanRacersFinished != numHumanRacers) {
                i = 0;
                do {
                    curRacer = gRacersByPosition[i]->racer;
                    if (curRacer->raceFinished == FALSE) {
                        if (curRacer->playerIndex >= 0) {
                            set_active_camera(curRacer->playerIndex);
                            camera = (s32) cam_get_active_camera_no_cutscenes();
                            // we need the camera to be a s32 for the WAIT_ON_IOBUSY anti tamper call to work
                            // but we *know* that cam_get_active_camera_no_cutscenes returns a Camera pointer so this
                            // should be safe
                            ((Camera *) camera)->mode = CAMERA_FINISH_CHALLENGE;
                        }
                        curRacer->raceFinished = TRUE;
                        curRacer->finishPosition = gNumFinishedRacers;
                        gNumFinishedRacers++;
                    }
                    i++;
                } while (i < gNumRacers);
            }

#ifdef ANTI_TAMPER
            raceType = FALSE;
            // Anti-Piracy check
            // passing in camera here is probably a fake
            WAIT_ON_IOBUSY(camera);
            // D_B0000574 is a direct read from the ROM as opposed to RAM
            if (((D_B0000574 & 0xFFFF) & 0xFFFF) != 0x6C07) {
                raceType = TRUE;
            }
#endif

            if (!gIsTimeTrial) {
                i = 0;
                do {
                    curRacer = gRacersByPosition[i]->racer;
                    racerPos = curRacer->racerIndex;
                    settings->racers[racerPos].starting_position = i;
                    i++;
                } while (i < gNumRacers);
            }
            gSwapLeadPlayer = FALSE;
            flags[2] = raceType;
            if (is_in_two_player_adventure() &&
                (settings->racers[PLAYER_TWO].starting_position < settings->racers[PLAYER_ONE].starting_position)) {
                gSwapLeadPlayer = TRUE;
            }
            curRacer = (*gRacersByPosition)->racer;
            gFirstTimeFinish = FALSE;
            if ((settings->gNumRacers == 1 || is_in_two_player_adventure()) &&
                curRacer->playerIndex != PLAYER_COMPUTER && !is_in_tracks_mode() && get_trophy_race_world_id() == 0) {
                gFirstTimeFinish = TRUE;
            }
            i = FALSE;
            if (gFirstTimeFinish && !someBool2) {
                i = set_course_finish_flags(settings);
            }
            if (someBool2) {
                gFirstTimeFinish = TRUE;
                i = TRUE;
            }

#ifdef ANTI_TAMPER
            if (flags[2]) {
                i = FALSE;
                gFirstTimeFinish = FALSE;
            }
#endif

            if (!i) {
                if (is_in_two_player_adventure()) {
                    if (gSwapLeadPlayer) {
                        gSwapLeadPlayer = FALSE;
                        swap_lead_player();
                        if (gLeadPlayerIndex) {
                            gIsP2LeadPlayer = TRUE;
                        }
                    } else if (gLeadPlayerIndex) {
                        gIsP2LeadPlayer = TRUE;
                    }
                }
                postrace_start(gFirstTimeFinish, 30);
            } else {
                settings->balloonsPtr[settings->worldId]++;
                if (settings->worldId != 0) {
                    settings->balloonsPtr[0]++;
                }
                race_finish_adventure(TRUE);
            }
            gRaceFinishTriggered = -1; // -1 doesn't do anything different.
            if (get_number_of_active_players() == 1) {
                race_finish_time_trial();
            }
        }
    }
}

/**
 * Mark the course as finished for the appropriate mode.
 * Check if it's the first race or the silver coin race before deciding which flag to write.
 * Return whether something was written.
 */
s8 set_course_finish_flags(Settings *settings) {
    Object_Racer *racer;

    racer = gRacersByPosition[PLAYER_ONE]->racer;
    if (racer->playerIndex == PLAYER_COMPUTER) {
        return FALSE;
    }
    gFirstTimeFinish = FALSE;
    if (!(settings->courseFlagsPtr[settings->courseId] & RACE_CLEARED)) {
        if (gIsTimeTrial == FALSE) {
            gFirstTimeFinish = TRUE;
            settings->courseFlagsPtr[settings->courseId] |= RACE_CLEARED;
        }
    } else if (gIsSilverCoinRace && racer->silverCoinCount >= 8 && gIsTimeTrial == FALSE) {
        gFirstTimeFinish = TRUE;
        settings->courseFlagsPtr[settings->courseId] |= RACE_CLEARED_SILVER_COINS;
    }
    return gFirstTimeFinish;
}

/**
 * Sets the countdown ready for the level to fade out.
 * Begins the timer that exits the level in 5 seconds.
 */
void race_finish_adventure(UNUSED s32 unusedArg) {
    gRaceEndTimer = 300;
    gRaceEndStage = 0;
    unused_D_8011AD52 = unusedArg;
}

/**
 * Begins counting down, once it reaches 0, start stopping all the race behaviours.
 * This function is also where the Taj Balloon cutscene is also handled.
 * After that's done, write to save and send the player back to the hub.
 */
void race_transition_adventure(s32 updateRate) {
    s32 i;
    Object_Racer *racer;
    Object *prevPort0Racer;
    s32 sp30;
    Object *prevRacer0Obj;
    Settings *settings;
    u32 cutsceneTimerLimit;

    set_pause_lockout_timer(1);
    sp30 = gRaceEndTimer;
    gRaceEndTimer -= updateRate;
    if (gRaceEndTimer <= 0) {
        gRaceEndTimer = -1;
    }
    if (sp30 > 50 && gRaceEndTimer <= 50) {
        transition_begin(&gRaceEndFade);
    }
    sp30 = 0;
    if (gRaceEndStage == 0 && gRaceEndTimer == -1) {
        for (i = 0; i < gNumRacers; i++) {
            racer = (*gRacers)[i]->racer;
            racer->magnetTargetObj = NULL;
            if (racer->playerIndex != PLAYER_COMPUTER && racer->finishPosition == 1) {
                sp30 = i;
            }
            if (racer->magnetSoundMask != NULL) {
                sndp_stop(racer->magnetSoundMask);
            }
            if (racer->shieldSoundMask != NULL) {
                audspat_point_stop(racer->shieldSoundMask);
            }
        }
        prevPort0Racer = (*gRacers)[0];
        (*gRacers)[0] = (*gRacers)[sp30];
        (*gRacers)[sp30] = prevPort0Racer;
        racer_sound_free((*gRacers)[0]);
        hud_audio_init();
        reset_rocket_sound_timer();
        sndp_stop_all_looped();
        if (is_in_two_player_adventure()) {
            set_scene_viewport_num(0);
            cam_set_layout(VIEWPORT_LAYOUT_1_PLAYER);
            prevRacer0Obj = (*gRacers)[0];
            prevPort0Racer = gRacersByPort[0];
            racer = prevRacer0Obj->racer;
            gRacersByPort[0] = prevRacer0Obj;
            gRacersByPort[1] = prevPort0Racer;
            if (gSwapLeadPlayer != 0) {
                gSwapLeadPlayer = 0;
                swap_lead_player();
                racer->playerIndex = 0;
            }
        }
        gNumRacersSaved = gNumRacers;
        gRaceEndStage = 1;
    }
    if (gRaceEndStage == 1) {
        hud_visibility(FALSE);
        gNumRacersSaved--;
        if (gNumRacersSaved > 0) {
            i = 0;
            while (i < gNumRacers && gRacersByPosition[i] != (*gRacers)[gNumRacersSaved]) {
                i++;
            }
            if (i < gNumRacers) {
                for (; i < (gNumRacers - 1); i++) {
                    gRacersByPosition[i] = gRacersByPosition[i + 1];
                }
            }
            free_object((*gRacers)[gNumRacersSaved]);
            (*gRacers)[gNumRacersSaved] = NULL;
            gNumRacers--;

        } else {
            gRaceEndStage = 2;
        }
    }
    if (gRaceEndStage == 2) {
        prevPort0Racer = (*gRacers)[0];
        racer = prevPort0Racer->racer;
        func_800230D0(prevPort0Racer, racer);
        racer->raceFinished = FALSE;
        gRaceEndStage = 3;
        func_8001E45C(CUTSCENE_ID_UNK_A);
        gBalloonCutsceneTimer = 0;
        func_8001E93C();
    }
    if (gRaceEndStage == 3) {
        transition_begin(&gRaceEndTransition);
        gRaceEndStage = 4;
        set_anti_aliasing(TRUE);
    }
    if (gRaceEndStage == 4) {
        set_anti_aliasing(TRUE);
        disable_racer_input();
        if (!(level_type() & RACETYPE_CHALLENGE_BATTLE)) {
            if (osTvType == OS_TV_TYPE_PAL) {
                cutsceneTimerLimit = 415;
            } else {
                cutsceneTimerLimit = 540;
            }
            gBalloonCutsceneTimer += updateRate;
            if (gBalloonCutsceneTimer < cutsceneTimerLimit) {
                minimap_fade(1);
            } else {
                hud_visibility(1);
            }
        }
        i = input_pressed(PLAYER_ONE) & A_BUTTON;
        settings = get_settings();
        if (!(settings->cutsceneFlags & 0x40000)) {
            i = 0;
        }
        if (func_800214C4() != 0 || (i != 0 && check_fadeout_transition() == 0)) {
            if (i != 0) {
                transition_begin(&gBalloonCutsceneTransition);
            }
            level_transition_begin(2);
            gRaceEndStage = 5;
            settings->cutsceneFlags |= 0x40000;
        }
    }
}

/**
 * Returns the race finish timer.
 */
s16 race_finish_timer(void) {
    return gRaceEndTimer;
}

/**
 * Return the timer used for the collectable balloon cutscene.
 */
u32 get_balloon_cutscene_timer(void) {
    return gBalloonCutsceneTimer;
}

/**
 * Checks if the fastest lap or the race time is faster than the current record.
 * Save those if they are, and if the staff ghost is not enabled, enable it for the next attempt.
 * The staff ghost comparison is also called here.
 */
void race_finish_time_trial(void) {
    s32 bestCourseTime;
    s32 bestRacerTime;
    s32 i;
    s32 courseTime;
    s32 vehicleID;
    s32 curRacerLapTime;
    s32 j;
    Object_Racer *curRacer;
    Object_Racer *bestRacer;
    Settings *settings;
    LevelHeader *levelHeader;

    levelHeader = level_header();
    settings = get_settings();
    settings->timeTrialRacer = 0;
    settings->unk115[1] = 0;
    settings->unk115[0] = 0;
    bestCourseTime = 36001;
    bestRacerTime = 36001;
    bestRacer = gRacersByPosition[0]->racer;
    for (i = 0; i < gNumRacers; i++) {
        curRacer = gRacersByPosition[i]->racer;
        if (curRacer->racerIndex >= 0) {
            if (curRacer->racerIndex < get_number_of_active_players()) {
                settings->racers[curRacer->racerIndex].best_times = 0;
                vehicleID = curRacer->vehicleIDPrev;
                if (vehicleID >= VEHICLE_CAR && vehicleID < NUMBER_OF_PLAYER_VEHICLES) {
                    courseTime = 0;
                    for (j = 0; j < levelHeader->laps && j < 5; j++) {
                        settings->racers[curRacer->racerIndex].lap_times[j] = curRacer->lap_times[j];
                        curRacerLapTime = curRacer->lap_times[j];
                        courseTime += curRacerLapTime;
                        if (curRacerLapTime < bestRacerTime) {
                            settings->unk115[1] = j;
                            settings->unk115[0] = curRacer->racerIndex;
                            bestRacerTime = curRacerLapTime;
                        }
                    }
                    settings->racers[curRacer->racerIndex].course_time = courseTime;
                    if (courseTime < bestCourseTime) {
                        bestCourseTime = courseTime;
                        settings->timeTrialRacer = curRacer->racerIndex;
                        bestRacer = curRacer;
                    }
                }
            }
        }
    }
    settings->display_times = FALSE;
    if (gIsTimeTrial) {
        vehicleID = gPrevTimeTrialVehicle;
        if (vehicleID >= NUMBER_OF_PLAYER_VEHICLES || vehicleID < VEHICLE_CAR) {
            vehicleID = VEHICLE_CAR;
        }
        settings->display_times = TRUE;
        if (settings->unk115[0] == 0) {
            if ((settings->flapTimesPtr[vehicleID][settings->courseId] == NULL) ||
                (bestRacerTime < settings->flapTimesPtr[vehicleID][settings->courseId])) {
                settings->flapTimesPtr[vehicleID][settings->courseId] = bestRacerTime;
                settings->racers[settings->unk115[0]].best_times |= 1 << settings->unk115[1];
            }
        }
        if (settings->timeTrialRacer == 0) {
            if ((settings->courseTimesPtr[vehicleID][settings->courseId] == NULL) ||
                (bestCourseTime < settings->courseTimesPtr[vehicleID][settings->courseId])) {
                settings->courseTimesPtr[vehicleID][settings->courseId] = bestCourseTime;
                settings->racers[settings->timeTrialRacer].best_times |= 0x80;
            }
        }
        if (((!vehicleID) && (!vehicleID)) && (!vehicleID)) {} // Fakematch
        if (settings->timeTrialRacer == 0) {
            if (bestCourseTime < 10800 && (vehicleID != gTimeTrialVehicle || timetrial_map_id() != level_id() ||
                                           bestCourseTime < gTimeTrialTime)) {
                gTimeTrialTime = bestCourseTime;
                gTimeTrialVehicle = gPrevTimeTrialVehicle;
                gTimeTrialCharacter = settings->racers[0].character;
                timetrial_swap_player_ghost(level_id());
                gHasGhostToSave = TRUE;
            }
            if (osTvType == OS_TV_TYPE_PAL) {
                bestCourseTime = (bestCourseTime * 6) / 5;
            }
            if (bestCourseTime < gTTGhostTimeToBeat) {
                if (gTimeTrialStaffGhost) {
                    tt_ghost_beaten(level_id(), &bestRacer->playerIndex);
                } else {
                    hud_time_trial_message(&bestRacer->playerIndex);
                }
            } else {
                hud_time_trial_message(&bestRacer->playerIndex);
            }
        }
    }
}

/**
 * Returns true if the player ghost data is valid for playback.
 */
s32 timetrial_valid_player_ghost(void) {
    if (timetrial_map_id() != level_id()) {
        return FALSE;
    } else {
        if (gTimeTrialVehicle != gPrevTimeTrialVehicle) {
            return FALSE;
        } else {
            return TRUE;
        }
    }
}

/**
 * Return the player ghost object.
 */
Object *timetrial_player_ghost(void) {
    return gGhostObjPlayer;
}

/**
Pretty sure this determines whether or not you're eligible to race TT ghost in track select
when TT is on. It looks like it checks some ghost data makes sure you've got a ghost for that level
with the default vehicle,
Returns 0 if TT ghost was loaded successfully.
*/
s32 timetrial_load_staff_ghost(s32 mapId) {
    TTGhostTable *ghostTable;
    TTGhostTable *prevGhostTable;
    s32 ret;
    TTGhostTable *nextGhostTable;

    gMapDefaultVehicle = leveltable_vehicle_default(mapId);
    ghostTable = (TTGhostTable *) asset_table_load(ASSET_TTGHOSTS_TABLE);

    nextGhostTable = ghostTable;
    do {
        prevGhostTable = nextGhostTable;
        if ((prevGhostTable->mapId == mapId) && (prevGhostTable->defaultVehicleId == gMapDefaultVehicle)) {
            break;
        }
        nextGhostTable++;
    } while (prevGhostTable->mapId != 0xFF);

    ret = 1;

    if (prevGhostTable->mapId != 0xFF) {
        ret = load_tt_ghost(nextGhostTable->ghostOffset, nextGhostTable[1].ghostOffset - nextGhostTable->ghostOffset,
                            &gTTGhostTimeToBeat);
    }

    mempool_free(ghostTable);
    return ret;
}

/**
 * Return true if this object is the time trial ghost.
 */
s32 timetrial_staff_ghost_check(Object *obj) {
    return obj == gGhostObjStaff;
}

/**
 * Free ghost data then save the players victory.
 * Check if the player has beaten every time and unlock TT.
 * Otherwise, tell them to try another track.
 */
void tt_ghost_beaten(s32 arg0, s16 *playerId) {
    s32 trackIdCount;
    s8 *mainTrackIds;

    gGhostObjStaff = NULL;
    timetrial_free_staff_ghost();
    gTimeTrialStaffGhost = FALSE;
    mainTrackIds = (s8 *) get_misc_asset(ASSET_MISC_MAIN_TRACKS_IDS);
    trackIdCount = 0;
    while (mainTrackIds[trackIdCount] != -1 && mainTrackIds[trackIdCount] != arg0) {
        trackIdCount++;
    }
    if (gBeatStaffGhost) {
        // Save that TT has been beaten for this track.
        set_eeprom_settings_value(16 << trackIdCount);
        // Check if TT has been beaten for all tracks.
        if ((get_eeprom_settings() & 0xFFFFF0) == 0xFFFFF0) {
            set_magic_code_flags(CHEAT_CONTROL_TT);
            sound_play(SOUND_VOICE_TT_BEAT_ALL_TIMES, NULL);
            sound_play_delayed(SOUND_VOICE_TT_UNLOCKED, NULL, 1.5f);
            set_current_text(
                ASSET_GAME_TEXT_84); // Text for "You have beaten all my times!" and then "Now you can PICK me!"
        } else {
            sound_play(SOUND_VOICE_TT_WELL_DONE, NULL);
            sound_play_delayed(SOUND_VOICE_TT_TRY_ANOTHER_TRACK, NULL, 1.0f);
            set_current_text(ASSET_GAME_TEXT_83); // Text for "Well Done! Now try another track."
        }
        gBeatStaffGhost = FALSE;
        return;
    }
    hud_time_trial_message(playerId);
}

/**
 * Compare if the course record is enough to unlock the staff ghost.
 * Also check if the ghost tiself has been beaten.
 * Store both results and return if there should be a ghost.
 */
u8 timetrial_init_staff_ghost(s32 trackId) {
    s32 i;
    s8 *mainTrackIds;
    u16 *staffTime;
    Settings *settings;

    gBeatStaffGhost = FALSE;
    gTimeTrialStaffGhost = FALSE;
    settings = get_settings();
    if (leveltable_vehicle_default(trackId) == (Vehicle) gPrevTimeTrialVehicle) {
        mainTrackIds = (s8 *) get_misc_asset(ASSET_MISC_MAIN_TRACKS_IDS);
        staffTime = (u16 *) get_misc_asset(ASSET_MISC_GHOST_UNLOCK_TIMES);
        for (i = 0; mainTrackIds[i] != -1 && trackId != mainTrackIds[i]; i++) {}
        if (mainTrackIds[i] != -1) {
            if (staffTime[i] >= settings->courseTimesPtr[gPrevTimeTrialVehicle][trackId]) {
                // Check if TT has been beaten?
                if (!(get_eeprom_settings() & ((1 << 4) << i))) {
                    gBeatStaffGhost = TRUE;
                }
                if (timetrial_load_staff_ghost(trackId) == 0) {
                    gTimeTrialStaffGhost = TRUE;
                }
            }
        }
    }
    return gTimeTrialStaffGhost;
}

/**
 * Return the time trial staff ghost object.
 */
Object *timetrial_ghost_staff(void) {
    return gGhostObjStaff;
}

/**
 * Return true if the tt ghost is unbeaten for this track.
 */
s32 timetrial_staff_unbeaten(void) {
    return gBeatStaffGhost == FALSE;
}

/**
 * Calls a function to start loading the player ghost data from the controller pak.
 * Returns the controller pak status. 0 means good.
 */
s32 timetrial_init_player_ghost(s32 playerID) {
    s16 characterID;
    s16 time;
    s32 cpakStatus;
    s32 ghostMapID;

    ghostMapID = timetrial_map_id();
    if (level_id() != ghostMapID || gTimeTrialVehicle != gPrevTimeTrialVehicle) {
        cpakStatus = timetrial_load_player_ghost(playerID, level_id(), gPrevTimeTrialVehicle, &characterID, &time);
        if (cpakStatus == CONTROLLER_PAK_GOOD) {
            gTimeTrialVehicle = gPrevTimeTrialVehicle;
            gTimeTrialCharacter = characterID;
            gTimeTrialTime = time;
        }
        return cpakStatus;
    }
    return timetrial_load_player_ghost(playerID, level_id(), gPrevTimeTrialVehicle, NULL, NULL);
}

/**
 * Call a function to write the ghost data to the controller pak.
 * Returns the controller pak status. 0 is good.
 */
SIDeviceStatus timetrial_save_player_ghost(s32 controllerIndex) {
    return timetrial_write_player_ghost(controllerIndex, timetrial_map_id(), gTimeTrialVehicle, gTimeTrialCharacter,
                                        gTimeTrialTime);
}

/**
 * Returns whether there's valid ghost data to save.
 */
u8 has_ghost_to_save(void) {
    return gHasGhostToSave;
}

/**
 * Resets the variables used for ghost data saving.
 */
void set_ghost_none(void) {
    gGhostMapID = -1;
    gHasGhostToSave = FALSE;
}

/**
 * Finds the opponent to this racer in a relative position to them and calculates the distance to them.
 * The position argument is relative to the racer's current position and represents the number of
 * places ahead (positive) or behind (negative) the opponent is. So, for instance, if position is 1,
 * find the opponent one place ahead of the racer; if it's -1, find the opponent one place behind.
 */
Object *racer_find_nearest_opponent_relative(Object_Racer *racer, s32 position, f32 *distance) {
    UNUSED s32 pad;
    Object *tempRacerObj;
    position = (racer->racerOrder - position) - 1;
    if (position < 0 || position >= gNumRacers) {
        return NULL;
    }
    tempRacerObj = gRacersByPosition[position];
    if (tempRacerObj == NULL) {
        return NULL;
    }
    *distance = racer_calc_distance_to_opponent(racer, tempRacerObj->racer);
    return tempRacerObj;
}

/**
 * Calculates the distance between two racers. Traverses through the checkpoints
 * between the two racers to calculate the total distance.
 * If the second racer is ahead, the distance is positive, otherwise negative.
 */
f32 racer_calc_distance_to_opponent(Object_Racer *racer1, Object_Racer *racer2) {
    Object_Racer *temp_racer;
    f32 totalDistance;
    s32 r1_ccp;
    UNUSED s32 pad;
    s32 reverseOrder;
    s32 checkpointID;

    if (gNumberOfMainCheckpoints <= 0) {
        return 0.0f;
    }
    totalDistance = 0.0f;
    reverseOrder = FALSE;
    if (racer2->courseCheckpoint < racer1->courseCheckpoint) {
        temp_racer = racer1;
        racer1 = racer2;
        racer2 = temp_racer;
        reverseOrder = TRUE;
    }
    checkpointID = racer1->nextCheckpoint;
    for (r1_ccp = racer1->courseCheckpoint; r1_ccp < racer2->courseCheckpoint; r1_ccp++) {
        totalDistance += gTrackCheckpoints[checkpointID++].distance;
        if (checkpointID == gNumberOfMainCheckpoints) {
            checkpointID = 0;
        }
    }
    checkpointID = racer1->nextCheckpoint - 1;
    if (checkpointID < 0) {
        checkpointID = gNumberOfMainCheckpoints - 1;
    }
    totalDistance += (gTrackCheckpoints[checkpointID].distance * racer1->checkpoint_distance);
    checkpointID = racer2->nextCheckpoint - 1;
    if (checkpointID < 0) {
        checkpointID = gNumberOfMainCheckpoints - 1;
    }
    totalDistance -= (gTrackCheckpoints[checkpointID].distance * racer2->checkpoint_distance);
    if (reverseOrder) {
        totalDistance = -totalDistance;
    }
    return totalDistance;
}

/**
 * Traverses from the racer's position through the upcoming checkpoints
 * to the starting line and calculates the total distance.
 */
UNUSED f32 race_calc_distance_to_start_line(Object_Racer *racer) {
    f32 distLeft;
    s32 checkpointID;

    if (gNumberOfMainCheckpoints <= 0) {
        return 0.0f;
    }
    distLeft = 0.0f;
    for (checkpointID = racer->nextCheckpoint; checkpointID < gNumberOfMainCheckpoints; checkpointID++) {
        distLeft += gTrackCheckpoints[checkpointID].distance;
    }
    checkpointID = racer->nextCheckpoint - 1;
    if (checkpointID < 0) {
        checkpointID = gNumberOfMainCheckpoints - 1;
    }
    distLeft += (gTrackCheckpoints[checkpointID].distance * racer->checkpoint_distance);
    return distLeft;
}

/**
 * Returns a pointer to a specific checkpoint.
 */
CheckpointNode *get_checkpoint_node(s32 checkpointID) {
    return &gTrackCheckpoints[checkpointID];
}

/**
 * Takes the position along the checkpoint path, and finds the next applicable node.
 * If an alternative path is available, use that node instead.
 */
CheckpointNode *find_next_checkpoint_node(s32 splinePos, s32 isAlternate) {
    CheckpointNode *checkpointNode = &gTrackCheckpoints[splinePos];
    if (isAlternate != 0 && checkpointNode->altRouteID != -1) {
        checkpointNode = &gTrackCheckpoints[checkpointNode->altRouteID];
    }
    return checkpointNode;
}

/**
 * Returns the number of active checkpoints in the current level.
 */
s32 get_checkpoint_count(void) {
    return gNumberOfMainCheckpoints;
}

/**
 * Returns the group of racer objects.
 * Official Name: objGetPlayerlist
 */
Object **get_racer_objects(s32 *numRacers) {
    *numRacers = gNumRacers;
    return *gRacers;
}

/**
 * Returns the group of racer objects, ordered by player index.
 */
Object **get_racer_objects_by_port(s32 *numRacers) {
    *numRacers = gNumRacers;
    return gRacersByPort;
}

/**
 * Returns the group of racer objects, ordered by current race position.
 */
Object **get_racer_objects_by_position(s32 *numRacers) {
    *numRacers = gNumRacers;
    return gRacersByPosition;
}

/**
 * Returns the racer object specified by the ID
 */
Object *get_racer_object(s32 index) {
    if (gNumRacers == 0) {
        return NULL;
    }
    if (index < 0 || index >= gNumRacers) {
        return NULL;
    }
    return (*gRacers)[index];
}

/**
 * Returns the racer object specified by the player ID.
 */
Object *get_racer_object_by_port(s32 index) {
    if (gNumRacers == 0) {
        return NULL;
    }
    if (index < 0 || index >= gNumRacers) {
        return NULL;
    }
    return gRacersByPort[index];
}

/**
 * Unused function that would've iterated through all active checkpoints to render their visual nodes.
 * The function it calls is completely stubbed out.
 */
UNUSED void debug_render_checkpoints(Gfx **dList, Mtx **mtx, Vertex **vtx) {
    s32 i;

    material_set_no_tex_offset(dList, NULL, RENDER_Z_COMPARE);
    if (gNumberOfMainCheckpoints > 3) {
        for (i = 0; i < gNumberOfMainCheckpoints; i++) {
            // Ground path
            debug_render_checkpoint_node(i, 0, dList, mtx, vtx);
        }
        for (i = 0; i < gNumberOfMainCheckpoints; i++) {
            // Air path
            debug_render_checkpoint_node(i, 1, dList, mtx, vtx);
        }
    }
}

/**
 * Would've rendered an individual checkpoint node. On https://noclip.website, with dev objects enabled, you can see a
 * visual representation of what these checkpoints would've looked like ingame.
 */
UNUSED void debug_render_checkpoint_node(UNUSED s32 checkpointID, UNUSED s32 pathID, UNUSED Gfx **dList,
                                         UNUSED Mtx **mtx, UNUSED Vertex **vtx) {
}

/**
 * Loop through every existing spectate camera and sort them by index.
 */
void spectate_update(void) {
    Object *objPtr;
    Object *temp;
    s32 continueLoop;
    s32 i;

    gCameraObjCount = 0;
    for (i = 0; i < gObjectCount; i++) {
        objPtr = gObjPtrList[i];
        if (!(objPtr->trans.flags & OBJ_FLAGS_PARTICLE)) {
            if (objPtr->behaviorId == BHV_CAMERA_CONTROL) {
                if (gCameraObjCount < CAMCONTROL_COUNT) {
                    (*gCameraObjList)[gCameraObjCount] = objPtr;
                    gCameraObjCount++;
                }
            }
        }
    }

    do {
        continueLoop = TRUE;
        for (i = 0; i < gCameraObjCount - 1; i++) {
            objPtr = (*gCameraObjList)[i + 1];
            temp = (*gCameraObjList)[i];
            if (temp->properties.camControl.cameraID > objPtr->properties.camControl.cameraID) {
                (*gCameraObjList)[i] = (*gCameraObjList)[i + 1];
                (*gCameraObjList)[i + 1] = temp;
                continueLoop = FALSE;
            }
        }
    } while (!continueLoop);
}

Object *spectate_object(s32 cameraIndex) {
    if (cameraIndex < 0 || cameraIndex >= gCameraObjCount) {
        return NULL;
    }
    return (*gCameraObjList)[cameraIndex];
}

/**
 * Take the current camera passed through the function and compare distances between the next and previous camera.
 * Set the camera to be whichever's closest to the object.
 */
Object *spectate_nearest(Object *obj, s32 *cameraId) {
    Object *nextCamera;
    Object *prevCamera;
    Object *currCamera;
    s32 *cameraIndex;
    f32 x;
    f32 y;
    f32 z;
    f32 prevCameraXYZ;
    f32 currCameraXYZ;
    f32 nextCameraXYZ;
    s32 cameraIndex_Curr;
    s32 cameraIndex_Prev;
    s32 cameraIndex_Next;
    cameraIndex = cameraId;
    if (gCameraObjCount == 0) {
        return NULL;
    }
    cameraIndex_Next = *cameraIndex + 1;
    cameraIndex_Curr = *cameraIndex;
    cameraIndex_Prev = *cameraIndex - 1;
    if (cameraIndex_Next >= gCameraObjCount) {
        cameraIndex_Next = 0;
    }
    if (cameraIndex_Prev < 0) {
        cameraIndex_Prev = gCameraObjCount - 1;
    }
    currCamera = (*gCameraObjList)[cameraIndex_Curr];
    nextCamera = (*gCameraObjList)[cameraIndex_Next];
    prevCamera = (*gCameraObjList)[cameraIndex_Prev];
    x = currCamera->trans.x_position - obj->trans.x_position;
    y = currCamera->trans.y_position - obj->trans.y_position;
    z = currCamera->trans.z_position - obj->trans.z_position;
    currCameraXYZ = (x * x) + (y * y) + (z * z);
    x = nextCamera->trans.x_position - obj->trans.x_position;
    y = nextCamera->trans.y_position - obj->trans.y_position;
    z = nextCamera->trans.z_position - obj->trans.z_position;
    nextCameraXYZ = (x * x) + (y * y) + (z * z);
    x = prevCamera->trans.x_position - obj->trans.x_position;
    y = prevCamera->trans.y_position - obj->trans.y_position;
    z = prevCamera->trans.z_position - obj->trans.z_position;
    prevCameraXYZ = (x * x) + (y * y) + (z * z);

    if (nextCameraXYZ < currCameraXYZ) {
        *cameraId = cameraIndex_Next;
        currCamera = nextCamera;
        currCameraXYZ = nextCameraXYZ;
    }
    if (prevCameraXYZ < currCameraXYZ) {
        *cameraId = cameraIndex_Prev;
        currCamera = prevCamera;
    }
    return currCamera;
}

/**
 * Take every existing AI node and find each neighbouring node.
 * Afterwards, sort them by height so the game can generate elevation thresholds.
 */
void ainode_update(void) {
    LevelObjectEntry_AiNode *aiNodeEntry;
    Object *obj;
    s16 nodeCount;
    Object *nextAiNodeObj;
    f32 diffX;
    f32 diffZ;
    f32 diffY;
    s32 i;
    s32 j;
    s8 index;  // Must be an s8
    u8 index2; // Must be an u8
    s16 swap;
    Object_AiNode *aiNodeObj64;
    s8 nodeIDs[AINODE_COUNT];
    s8 elevations[AINODE_COUNT];

    if (gInitAINodes == FALSE) {
        return;
    }
    gInitAINodes = FALSE;
    for (i = 0; i < AINODE_COUNT; i++) {
        (*gAINodes)[i] = NULL;
    }
    nodeCount = 0;
    // Store each existing node ID in the temporary vars.
    for (i = 0; i < gObjectCount; i++) {
        obj = gObjPtrList[i];
        if (!(obj->trans.flags & OBJ_FLAGS_PARTICLE) && obj->behaviorId == BHV_AINODE) {
            aiNodeEntry = &obj->level_entry->aiNode;
            index2 = aiNodeEntry->nodeID;
            if (!(index2 & AINODE_COUNT)) {
                (*gAINodes)[index2] = obj;
                nodeIDs[nodeCount] = aiNodeEntry->nodeID;
                elevations[nodeCount] = aiNodeEntry->elevation & 3;
                nodeCount++;
            }
        }
    }
    if (nodeCount == 0) {
        return;
    }
    // Find and set each neighbouring node and distance for each existing node.
    for (i = 0; i < AINODE_COUNT; i++) {
        obj = (*gAINodes)[i];
        if (obj != NULL) {
            aiNodeObj64 = obj->ai_node;
            aiNodeEntry = &obj->level_entry->aiNode;
            for (j = 0; j < 4; j++) {
                index2 = aiNodeEntry->adjacent[j];
                if (!(index2 & AINODE_COUNT)) {
                    nextAiNodeObj = (*gAINodes)[index2];
                    aiNodeObj64->nodeObj[j] = nextAiNodeObj;
                    if (nextAiNodeObj == NULL) {
                        aiNodeEntry->adjacent[j] = -1;
                    } else {
                        diffX = obj->trans.x_position - nextAiNodeObj->trans.x_position;
                        diffY = obj->trans.y_position - nextAiNodeObj->trans.y_position;
                        diffZ = obj->trans.z_position - nextAiNodeObj->trans.z_position;
                        aiNodeObj64->distToNode[j] = sqrtf((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ));
                    }
                }
            }
        }
    }
    // Sort them by height
    do {
        j = TRUE;
        for (i = 0; i < nodeCount - 1; i++) {
            if ((*gAINodes)[nodeIDs[i + 1]]->trans.y_position < (*gAINodes)[nodeIDs[i]]->trans.y_position) {
                swap = nodeIDs[i];
                nodeIDs[i] = nodeIDs[i + 1];
                nodeIDs[i + 1] = swap;
                swap = elevations[i];
                elevations[i] = elevations[i + 1];
                elevations[i + 1] = swap;
                j = FALSE;
            }
        }
    } while (!j); // Keep doing this until no more swaps are needed.

    if (1) {} // Fakematch

    for (i = 0; i < 5; i++) {
        gElevationHeights[i] = -20000.0f;
    }

    index = elevations[0];
    for (i = 0; i < nodeCount - 1;) {
        while (i < nodeCount - 1 && index >= elevations[i]) {
            i++;
        }
        if (index < elevations[i]) {
            index = elevations[i];
            gElevationHeights[index] =
                ((*gAINodes)[nodeIDs[i]]->trans.y_position + (*gAINodes)[nodeIDs[i - 1]]->trans.y_position) * 0.5;
        } else {
            i = nodeCount;
        }
    }
    gElevationHeights[0] = -10000.0f;
    gElevationHeights[4] = -gElevationHeights[0];
}

/**
 * Compare heights against the thresholds.
 * Elevation level is set based on position.
 */
s16 obj_elevation(f32 yPos) {
    s16 i = 0;
    s16 elevation = 0;
    for (; i < 4; i++) {
        if (gElevationHeights[i] != -20000.0f && gElevationHeights[i] < yPos) {
            elevation = i;
        }
    }
    return elevation;
}

/**
 * Loop through the AI Node list and add this new object to the list if it does not already exist.
 */
s32 ainode_register(Object *obj) {
    s32 i;
    for (i = 0; i < AINODE_COUNT; i++) {
        if ((*gAINodes)[i] == NULL) {
            (*gAINodes)[i] = obj;
            return i;
        }
    }
    return -1;
}

/**
 * Search through each AI node and find the one closest to the coordinates given.
 * Can choose to include or ignore elevation.
 */
s32 ainode_find_nearest(f32 diffX, f32 diffY, f32 diffZ, s32 useElevation) {
    UNUSED f32 pad[6];
    s32 elevation;
    f32 len;
    f32 x;
    f32 z;
    f32 y;
    f32 dist;
    s32 findDist;
    s32 numSteps;
    s32 result;
    Object *obj;
    LevelObjectEntry_AiNode *levelObj;

    if (useElevation) {
        elevation = obj_elevation(diffY);
    }
    dist = 50000.0;
    result = 0xFF;
    for (numSteps = 0; numSteps != AINODE_COUNT; numSteps++) {
        obj = (*gAINodes)[numSteps];
        if (obj) {
            levelObj = &((obj->level_entry)->aiNode);
            findDist = TRUE;
            if (useElevation && elevation != levelObj->elevation) {
                findDist = FALSE;
            }
            if (useElevation == 2 && levelObj->unk8 != 3) {
                findDist = FALSE;
            }
            if (findDist) {
                x = obj->trans.x_position - diffX;
                y = obj->trans.y_position - diffY;
                z = obj->trans.z_position - diffZ;
                len = sqrtf((x * x) + (y * y) + (z * z));
                if (len < dist) {
                    dist = len;
                    result = numSteps;
                }
            }
        }
    }
    return result;
}

// Updated Object_NPC
f32 func_8001C6C4(Object_NPC *npc, Object *npcParentObj, f32 updateRateF, f32 speedF, s32 direction) {
    f32 xPositions[5];
    f32 yPositions[5];
    f32 zPositions[5];
    f32 xDiff2;
    f32 yDiff2;
    f32 zDiff2;
    Object *aiNode;
    f32 dist;
    f32 xDiff;
    f32 yDiff;
    f32 zDiff;
    f32 tempYDiff;
    UNUSED s32 pad_sp84;
    s32 i;
    f32 var_f20_2;
    s32 var_s0;
    s32 someBool;

    if (osTvType == OS_TV_TYPE_PAL) {
        updateRateF *= 1.2;
    }

    for (i = 0; i < 5; i++) {
        if (npc->nodeData[i] == 0xFF) {
            return 0.0f;
        }

        aiNode = ainode_get(npc->nodeData[i]);
        if (aiNode == NULL) {
            return 0.0f;
        }

        xPositions[i] = aiNode->trans.x_position;
        yPositions[i] = aiNode->trans.y_position;
        zPositions[i] = aiNode->trans.z_position;
    }

    xDiff2 = catmull_rom_interpolation(xPositions, 0, npc->unk0);
    yDiff2 = catmull_rom_interpolation(yPositions, 0, npc->unk0);
    zDiff2 = catmull_rom_interpolation(zPositions, 0, npc->unk0);
    someBool = FALSE;
    if (npc->unk8 == 0.0f) {
        npc->unk8 = 0.01f;
    }

    for (var_s0 = 0; var_s0 != 2; var_s0++) {
        var_f20_2 = npc->unk0 + (npc->unk8 * updateRateF);
        if (var_f20_2 >= 1.0) {
            someBool = TRUE;
            var_f20_2 -= 1.0;
        }
        xDiff = catmull_rom_interpolation(xPositions, someBool, var_f20_2);
        yDiff = catmull_rom_interpolation(yPositions, someBool, var_f20_2);
        zDiff = catmull_rom_interpolation(zPositions, someBool, var_f20_2);
        xDiff -= xDiff2;
        yDiff -= yDiff2;
        zDiff -= zDiff2;
        if (var_s0 == 0) {
            someBool = FALSE;
            dist = sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff)) / updateRateF;
            if (dist != 0.0f) {
                npc->unk8 *= (speedF / dist);
            }
        }
    }
    npc->unk0 = var_f20_2;
    xDiff2 = xDiff + xDiff2;
    tempYDiff = yDiff2 = yDiff + yDiff2;
    zDiff2 = zDiff + zDiff2;

    xDiff = xDiff2 - npcParentObj->trans.x_position;
    yDiff = yDiff2 - npcParentObj->trans.y_position;
    zDiff = zDiff2 - npcParentObj->trans.z_position;

    xDiff2 = xDiff;
    yDiff2 = yDiff;
    zDiff2 = zDiff;

    dist = sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff));
    if (dist != 0.0f) {
        dist = 255.0 / dist;
        xDiff *= dist;
        yDiff *= dist;
        zDiff *= dist;
    }
    dist = sqrtf((xDiff2 * xDiff2) + (yDiff2 * yDiff2) + (zDiff2 * zDiff2)) / 16;
    if (speedF < dist) {
        dist = speedF;
    }
    if (dist >= 1.0) {
        var_s0 = (arctan2_f(xDiff, zDiff) - (npcParentObj->trans.rotation.y_rotation & 0xFFFF)) - 0x8000;
        if (var_s0 > 0x8000) {
            var_s0 -= 0xFFFF;
        }
        if (var_s0 < -0x8000) {
            var_s0 += 0xFFFF;
        }
        npcParentObj->trans.rotation.y_rotation += ((var_s0 * (s32) updateRateF)) >> 4;
        var_s0 = arctan2_f(yDiff, 255.0f) - (npcParentObj->trans.rotation.x_rotation & 0xFFFF);
        if (var_s0 > 0x8000) {
            var_s0 -= 0xFFFF;
        }
        if (var_s0 < -0x8000) {
            var_s0 += 0xFFFF;
        }
        npcParentObj->trans.rotation.x_rotation += ((var_s0 * (s32) updateRateF)) >> 4;
    }

    npcParentObj->trans.rotation.z_rotation = 0;
    xDiff = sins_f((s16) (npcParentObj->trans.rotation.y_rotation + 0x8000)) * dist;
    move_object(npcParentObj, xDiff * updateRateF, 0.0f,
                coss_f((npcParentObj->trans.rotation.y_rotation + 0x8000)) * dist * updateRateF);
    npcParentObj->trans.y_position = tempYDiff;
    dist = dist * updateRateF * 2;
    if (someBool != 0) {
        npc->nodeData[0] = npc->nodeData[1];
        npc->nodeData[1] = npc->nodeData[2];
        npc->nodeData[2] = npc->nodeData[3];
        npc->nodeData[3] = npc->nodeData[4];
        npc->nodeData[4] = ainode_find_next(npc->nodeData[3], npc->nodeData[2], direction);
    }

    return dist;
}

s32 ainode_find_next(s32 nodeId, s32 nextNodeId, s32 direction) {
    Object *aiNodeObj;
    LevelObjectEntry_AiNode *entry;
    Object_AiNode *aiNode;
    s32 nextIndex;
    s32 i;
    s32 someCount;

    if (nodeId < -1 || nodeId >= AINODE_COUNT) {
        return NODE_NONE;
    }
    aiNodeObj = (*gAINodes)[nodeId];
    if (aiNodeObj == NULL) {
        return NODE_NONE;
    }

    entry = &aiNodeObj->level_entry->aiNode;
    aiNode = aiNodeObj->ai_node;
    direction = direction & 3;
    someCount = 0;
    nextIndex = (aiNode->directions[direction] + 1) & 3;

    for (i = 0; i < 4; i++) {
        if (entry->adjacent[nextIndex] != NODE_NONE && entry->adjacent[nextIndex] != nextNodeId) {
            aiNode->directions[direction] = nextIndex;
            i = 4; // break
            someCount++;
        }
        nextIndex = (nextIndex + 1) & 3;
    }

    if (someCount == 0) {
        return NODE_NONE;
    } else {
        return entry->adjacent[aiNode->directions[direction]];
    }
}

s16 func_8001CD28(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 result;
    s32 sp370;
    s16 var_t1;
    s16 sp36C;
    s16 temp2;
    s16 i;
    LevelObjectEntry_AiNode *aiNodeEntry;
    s8 someBool;
    s8 var_s3;
    s8 var_s5;
    s8 temp;
    s32 var_ra;
    Object_AiNode *aiNode;
    Object *aiNodeObj;
    s32 sp154[AINODE_COUNT];
    s8 spD4[AINODE_COUNT];
    s8 sp54[AINODE_COUNT];

    // Only matches with do {} while?
    i = 0;
    do {
        sp154[i] = 0;
        i++;
    } while (i < AINODE_COUNT);

    aiNodeObj = (*gAINodes)[arg0];
    aiNode = aiNodeObj->ai_node;
    aiNodeEntry = &aiNodeObj->level_entry->aiNode;
    var_t1 = 0;
    var_ra = 0;
    result = NODE_NONE;
    var_s3 = 0;
    someBool = 1;
    var_s5 = 0;
    do {
        for (i = 0; i < 4; i++) {
            if (aiNode->nodeObj[i] != 0) {
                temp2 = aiNodeEntry->adjacent[i];
                temp = 1;
                if (((arg0 == aiNodeEntry->nodeID) && (temp2 == arg2)) ||
                    ((arg2 == aiNodeEntry->nodeID) && (temp2 == arg0))) {
                    temp = 0;
                    if (var_s5 != 0) {
                        temp = 1;
                    }
                    var_s5++;
                }
                if (temp != 0) {
                    sp36C = 0;
                    temp = 0;
                    while ((sp36C < var_t1) && (temp2 != spD4[sp36C])) {
                        sp36C++;
                    }

                    sp370 = aiNode->distToNode[i] + var_ra;
                    if (sp36C == var_t1) {
                        temp = 2;
                    } else if (sp370 < sp154[temp2]) {
                        temp = 1;
                    }
                }
                if (temp != 0) {
                    while (sp36C < var_t1 - 1) {
                        spD4[sp36C] = spD4[sp36C + 1];
                        sp54[sp36C] = sp54[sp36C + 1];
                        sp36C++;
                    }
                    if (temp == 2) {
                        var_t1++;
                    }
                    sp154[temp2] = sp370;

                    sp36C = var_t1 - 1;

                    sp54[sp36C] = (someBool) ? aiNodeEntry->adjacent[i] : var_s3;
                    spD4[sp36C] = aiNodeEntry->adjacent[i];

                    while ((sp36C > 0) && (sp154[spD4[sp36C - 1]] < sp154[spD4[sp36C]])) {
                        temp = spD4[sp36C];
                        spD4[sp36C] = spD4[sp36C - 1];
                        spD4[sp36C - 1] = temp;
                        temp = sp54[sp36C];
                        sp54[sp36C] = sp54[sp36C - 1] & 0xFF & 0xFF & 0xFF;
                        sp54[sp36C - 1] = temp & 0xFF;
                        sp36C--;
                    }
                }
            }
        }

        if (var_t1 > 0) {
            var_t1--;
            aiNodeObj = (*gAINodes)[spD4[var_t1]];
            aiNodeEntry = &aiNodeObj->level_entry->aiNode;
            var_s3 = sp54[var_t1];
            var_ra = sp154[aiNodeEntry->nodeID];
            aiNode = aiNodeObj->ai_node;
            someBool = 0;
            if (arg1 & 0x100) {
                if ((arg1 & 0x7F) == spD4[var_t1]) {
                    result = var_s3;
                }
            } else if (arg1 == aiNodeEntry->unk8) {
                result = var_s3;
            }
            if ((var_t1 == 0) && (result == 0xFF)) {
                result = var_s3;
            }
        }
    } while ((result == NODE_NONE) && (var_t1 > 0));

    if (result != 0xFF) {
        aiNodeObj = (*gAINodes)[arg0];
        aiNodeEntry = &aiNodeObj->level_entry->aiNode;
        aiNode = aiNodeObj->ai_node;
        for (i = 0; (i < 4) && (result != aiNodeEntry->adjacent[i]); i++) {}
        if (i < 4) {
            aiNode->directions[arg3] = i;
        }
    }
    return result;
}

/**
 * Signal that AI nodes exist, so the game knows to initialise them.
 */
void ainode_enable(void) {
    gInitAINodes = TRUE;
}

/**
 * If the node ID is new, set the tail ID to it.
 */
void ainode_tail_set(s32 nodeID) {
    if (nodeID != gAINodeTail[0]) {
        gAINodeTail[1] = gAINodeTail[0];
        gAINodeTail[0] = nodeID;
    }
}

/**
 * Return the last created AI node.
 */
UNUSED Object *ainode_tail(s32 *nodeID) {
    *nodeID = gAINodeTail[1];
    return gAINodes[0][gAINodeTail[1]];
}

/**
 * Return the AI node assigned to the given ID.
 */
Object *ainode_get(s32 nodeID) {
    if (nodeID >= 0 && nodeID < AINODE_COUNT) {
        return gAINodes[0][nodeID];
    }
    return NULL;
}

UNUSED void func_8001D248(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2) {
}

/**
 * Applies shading properties to a global variable.
 * Presumably intended for level geometry, which supports shading, but never uses it.
 */
void set_world_shading(f32 ambient, f32 diffuse, s16 angleX, s16 angleY, s16 angleZ) {
    set_shading_properties((ShadeProperties *) &gWorldShading, ambient, diffuse, angleX, angleY, angleZ);
}

/**
 * Add values onto the existing properties of an objects shading.
 * Resets the shading based off the new values.
 */
UNUSED void add_shading_properties(Object *obj, f32 ambientChange, f32 diffuseChange, s16 angleX, s16 angleY,
                                   s16 angleZ) {
    if (obj->shading != NULL) {
        obj->shading->ambient += ambientChange;
        if (obj->shading->ambient < 0.0f) {
            obj->shading->ambient = 0.0f;
        } else if (obj->shading->ambient > 1.0f) {
            obj->shading->ambient = 1.0f;
        }
        obj->shading->diffuse += diffuseChange;
        if (obj->shading->diffuse < 0.0f) {
            obj->shading->diffuse = 0.0f;
        }
        if (obj->shading->diffuse >= 2.0f) {
            obj->shading->diffuse = 1.99f;
        }
        set_shading_properties(obj->shading, obj->shading->ambient, obj->shading->diffuse,
                               (obj->shading->unk22 + angleX), (obj->shading->unk24 + angleY),
                               (obj->shading->unk26 + angleZ));
        if (obj->header->shadeIntensityy != 0) {
            obj->shading->lightR = obj->header->unk3A;
            obj->shading->lightG = obj->header->unk3B;
            obj->shading->lightB = obj->header->unk3C;
            obj->shading->lightIntensity = obj->header->shadeIntensityy;
            obj->shading->lightDirX = -(obj->shading->shadowDirX >> 1);
            obj->shading->lightDirY = -(obj->shading->shadowDirY >> 1);
            obj->shading->lightDirZ = -(obj->shading->shadowDirZ >> 1);
        }
    }
}

void set_shading_properties(ShadeProperties *arg0, f32 ambient, f32 diffuse, s16 angleX, s16 angleY, s16 angleZ) {
    Vec3s angle;
    Vec3f velocityPos;

    arg0->unk22 = angleX;
    arg0->ambient = ambient;
    arg0->diffuse = diffuse;
    arg0->unk0 = 1.0f;
    arg0->unk24 = angleY;
    arg0->unk26 = angleZ;
    angle.z_rotation = angleX;
    angle.y_rotation = angleZ;
    angle.x_rotation = angleY;
    velocityPos.z = -16384.0f;
    velocityPos.x = 0.0f;
    velocityPos.y = 0.0f;
    vec3f_rotate(&angle, &velocityPos);
    arg0->shadowDirX = -velocityPos.x;
    arg0->shadowDirY = -velocityPos.y;
    arg0->shadowDirZ = -velocityPos.z;
    arg0->shadowR = 0;
    arg0->shadowG = 0;
    arg0->shadowB = 0;
}

/**
 * Take the normalised length of the position set by the perspective and set the world angle for the envmap.
 * Official name: setObjectViewNormal
 */
void update_envmap_position(f32 x, f32 y, f32 z) {
    f32 vecLength = sqrtf((x * x) + (y * y) + (z * z));
    f32 normalizedLength;
    if (vecLength != 0.0f) {
        normalizedLength = -8192.0f / vecLength;
        x *= normalizedLength;
        y *= normalizedLength;
        z *= normalizedLength;
    }
    gEnvmapPos[0].x = x;
    gEnvmapPos[0].y = y;
    gEnvmapPos[0].z = z;
}

/**
 * If the triangle batch allows for it, compute envmap normals for the mesh.
 * Some objects will prefer some extra additions on top before calculating, like light intensity.
 */
void obj_shade_fancy(ObjectModel *model, Object *object, s32 arg2, f32 intensity) {
    s16 environmentMappingEnabled;
    s32 dynamicLightingEnabled;
    s16 i;

    dynamicLightingEnabled = 0;
    environmentMappingEnabled = 0;

    for (i = 0; i < model->numberOfBatches; i++) {
        if (model->batches[i].miscData != BATCH_VTX_COL) {
            dynamicLightingEnabled = -1; // This is a bit weird, but I guess it works.
        }
        if (model->batches[i].flags & RENDER_ENVMAP) {
            environmentMappingEnabled = -1;
        }
    }

    if (dynamicLightingEnabled) {
        // Calculates dynamic lighting for the object
        if (object->header->directionalPointLighting) {
            // Dynamic directional lighting for some objects (Intro diddy, Taj, T.T., Bosses)
            calc_dynamic_lighting_for_object_1(object, model, arg2, object, intensity, 1.0f);
        } else {
            // Dynamic ambient lighting for other objects (Racers, Rare logo, Wizpig face, etc.)
            calc_dynamic_lighting_for_object_2(object, model, arg2, intensity);
        }
    }

    if (environmentMappingEnabled) {
        // Calculates environment mapping for the object
        calc_env_mapping_for_object(model, object->trans.rotation.z_rotation, object->trans.rotation.x_rotation,
                                    object->trans.rotation.y_rotation);
    }
}

void calc_dynamic_lighting_for_object_1(Object *object, ObjectModel *model, s16 arg2, Object *anotherObject,
                                        f32 intensity, f32 arg5) {
    s16 normIdx;
    s16 j;
    s16 i;
    Vec3s objRot;
    s32 s6;
    s32 lightDirX, lightDirY, lightDirZ;    // 16.16 fixed point, normalized
    s32 shadowDirX, shadowDirY, shadowDirZ; // 16.16 fixed point, normalized
    s32 diffuseFactor;
    s32 ambientFactor;
    s32 lightIntensity;
    s32 shadeStrength;
    Vec3f direction;
    Vertex *vertices;
    Vec3s *normals;

    if (object->shading == NULL) {
        return;
    }

    vertices = object->curVertData;
    normals = model->normals;
    normIdx = 0;

    direction.x = -(object->shading->lightDirX << 3);
    direction.y = -(object->shading->lightDirY << 3);
    direction.z = -(object->shading->lightDirZ << 3);
    objRot.y_rotation = -object->trans.rotation.y_rotation;
    objRot.x_rotation = -object->trans.rotation.x_rotation;
    objRot.z_rotation = -object->trans.rotation.z_rotation;
    vec3f_rotate_ypr(&objRot, &direction);

    if (object->header->shadeIntensityy != 0 && arg2) {
        mtxf_transform_dir(get_projection_matrix_f32(), &direction, &direction);
    }

    lightDirX = -direction.x;
    lightDirY = -direction.y;
    lightDirZ = -direction.z;
    s6 = object->shading->lightIntensity;

    direction.x = object->shading->shadowDirX << 2;
    direction.y = object->shading->shadowDirY << 2;
    direction.z = object->shading->shadowDirZ << 2;

    if (arg2) {
        mtxf_transform_dir(get_projection_matrix_f32(), &direction, &direction);
    }
    vec3f_rotate_ypr(&objRot, &direction);

    shadowDirX = direction.x;
    shadowDirY = direction.y;
    shadowDirZ = direction.z;

    ambientFactor = object->shading->ambient * object->shading->unk0 * 255.0f * intensity;
    diffuseFactor = object->shading->diffuse * object->shading->unk0 * 255.0f * intensity;

    for (i = 0; i < model->numberOfBatches; i++) {
        if (model->batches[i].miscData != BATCH_VTX_COL) { // 0xFF means use vertex colors
            for (j = model->batches[i].verticesOffset; j < model->batches[i + 1].verticesOffset; j++) {
                // calculate lighting
                lightIntensity = (normals[normIdx].x * lightDirX + normals[normIdx].y * lightDirY +
                                  normals[normIdx].z * lightDirZ) >>
                                 13;
                if (lightIntensity > 0) {
                    lightIntensity = (lightIntensity * s6) >> 16;
                    if (lightIntensity > 255) {
                        lightIntensity = 255;
                    }
                } else {
                    lightIntensity = 0;
                }

                // calculate shading
                shadeStrength = (normals[normIdx].x * shadowDirX + normals[normIdx].y * shadowDirY +
                                 normals[normIdx].z * shadowDirZ) >>
                                13;
                if (shadeStrength > 0) {
                    shadeStrength = (shadeStrength * diffuseFactor) >> 16;
                    shadeStrength += ambientFactor;
                    if (shadeStrength > 255) {
                        shadeStrength = 255;
                    }
                } else {
                    shadeStrength = ambientFactor;
                }

                vertices[j].r = lightIntensity;
                vertices[j].g = lightIntensity;
                vertices[j].b = lightIntensity;
                vertices[j].a = shadeStrength;
                normIdx++;
            }
        } else if (model->batches[i].flags & RENDER_ENVMAP) {
            normIdx += model->batches[i + 1].verticesOffset - model->batches[i].verticesOffset;
        }
    }
}

void calc_env_mapping_for_object(ObjectModel *model, s16 zRot, s16 xRot, s16 yRot) {
    MtxS objRotMtxS32;
    MtxF objRotMtxF32;
    ObjectTransform objTrans;
    s16 k;
    s16 count;
    Triangle *triangles;
    Vec3s *model40Entries;
    s32 sp70;
    TextureHeader *tex;
    s16 shiftS;
    s16 maskS;
    s16 shiftT;
    s16 maskT;
    s16 i;
    s16 j;
    s16 var_v0;
    s16 var_v1;

    count = 0;
    triangles = model->triangles;
    model40Entries = model->normals;
    objTrans.rotation.z_rotation = zRot;
    objTrans.rotation.x_rotation = xRot;
    objTrans.rotation.y_rotation = yRot;
    objTrans.x_position = 0.0f;
    objTrans.y_position = 0.0f;
    objTrans.z_position = 0.0f;
    objTrans.scale = 1.0f;
    mtxf_from_transform(&objRotMtxF32, &objTrans);
    mtxf_to_mtxs(&objRotMtxF32, &objRotMtxS32);

    for (i = 0; i < model->numberOfBatches; i++) {
        if (model->batches[i].flags & RENDER_ENVMAP) {
            sp70 = ((model->batches[i].flags & RENDER_UNK_0020000) | RENDER_ENVMAP) ^ RENDER_ENVMAP;
            tex = model->textures[model->batches[i].textureIndex].texture;
            k = 0;

            switch (tex->width) {
                case 0x80:
                    SET_SHIFT_AND_MASK(shiftS, maskS, 4);
                    break;
                case 0x40:
                    SET_SHIFT_AND_MASK(shiftS, maskS, 5);
                    break;
                case 0x20:
                    SET_SHIFT_AND_MASK(shiftS, maskS, 6);
                    break;
                default:
                    SET_SHIFT_AND_MASK(shiftS, maskS, 7);
                    break;
            }
            switch (tex->height) {
                case 0x80:
                    SET_SHIFT_AND_MASK(shiftT, maskT, 4);
                    break;
                case 0x40:
                    SET_SHIFT_AND_MASK(shiftT, maskT, 5);
                    break;
                case 0x20:
                    SET_SHIFT_AND_MASK(shiftT, maskT, 6);
                    break;
                default:
                    SET_SHIFT_AND_MASK(shiftT, maskT, 7);
                    break;
            }

            for (j = model->batches[i].verticesOffset; j < model->batches[i + 1].verticesOffset; j++, k++) {
                gEnvmapPos[1].x = model40Entries[count].x;
                gEnvmapPos[1].y = model40Entries[count].y;
                gEnvmapPos[1].z = model40Entries[count].z;
                count++;
                mtxs_transform_dir(&objRotMtxS32, &gEnvmapPos[1]);
                if (sp70 == 0) {
                    vec3s_reflect(&gEnvmapPos[0], &gEnvmapPos[1]);
                }
                var_v0 = gEnvmapPos[1].x;
                var_v1 = gEnvmapPos[1].y;
                if (var_v0 > 0) {
                    var_v0--;
                }
                if (var_v1 > 0) {
                    var_v1--;
                }
                var_v0 = (var_v0 << 2) + 0x8000;
                var_v1 = (var_v1 << 2) + 0x8000;
                D_8011AF68[k].u = (var_v0 >> shiftS) & maskS;
                D_8011AF68[k].v = (var_v1 >> shiftT) & maskT;
            }

            for (j = model->batches[i].facesOffset; j < model->batches[i + 1].facesOffset; j++) {
                triangles[j].uv0.u = D_8011AF68[triangles[j].vi0].u;
                triangles[j].uv0.v = D_8011AF68[triangles[j].vi0].v;
                triangles[j].uv1.u = D_8011AF68[triangles[j].vi1].u;
                triangles[j].uv1.v = D_8011AF68[triangles[j].vi1].v;
                triangles[j].uv2.u = D_8011AF68[triangles[j].vi2].u;
                triangles[j].uv2.v = D_8011AF68[triangles[j].vi2].v;
            }
        } else if (model->batches[i].miscData < BATCH_VTX_COL) {
            count += model->batches[i + 1].verticesOffset - model->batches[i].verticesOffset;
        }
    }
}

/**
 * Find the racer object representing the player and directly set position and angle to new values.
 */
UNUSED void set_racer_position_and_angle(s16 player, s16 *x, s16 *y, s16 *z, s16 *angleZ, s16 *angleX, s16 *angleY) {
    Object *obj;
    Object_Racer *racer;
    s32 i;

    for (i = 0; i < gObjectCount; i++) {
        obj = gObjPtrList[i];
        if (!(obj->trans.flags & OBJ_FLAGS_PARTICLE)) {
            if (obj->behaviorId == BHV_RACER) {
                racer = obj->racer;
                if (player == racer->playerIndex) {
                    *x = obj->trans.x_position;
                    *y = obj->trans.y_position;
                    *z = obj->trans.z_position;
                    *angleZ = obj->trans.rotation.z_rotation;
                    *angleX = obj->trans.rotation.x_rotation;
                    *angleY = obj->trans.rotation.y_rotation;
                    i = gObjectCount; // Feels like it should be a break instead.
                }
            }
        }
    }
}

/**
 * Returns a pointer to the asset in the misc. section. If index is out of range, then this
 * function just returns the pointer to gAssetsMiscSection.
 * Official name: objGetTable
 */
s32 *get_misc_asset(s32 index) {
    if (index < 0 || index >= gAssetsMiscTableLength) {
        return gAssetsMiscSection;
    }
    return (s32 *) &gAssetsMiscSection[gAssetsMiscTable[index]];
}

/**
 * If the bridge is raised, decrement its timer and return the remaining time.
 */
s32 is_bridge_raised(s32 index) {
    if (index >= 0 && index < 8) {
        if (gDrawbridgeTimers[0][index] > 0) {
            gDrawbridgeTimers[0][index]--;
        }
        return gDrawbridgeTimers[0][index];
    }
    return 0;
}

/**
 * Starts the bridge timer when a racer hits the bell switch. 
 */
void start_bridge_timer(s32 index) {
    if (index >= 0 && index < 8) {
        gDrawbridgeTimers[0][index] = 8;
    }
}

/**
 * When the sound timer hits the correct value, write the objects position to the arguments.
 */
void obj_bridge_pos(s32 timing, f32 *x, f32 *y, f32 *z) {
    s32 i;
    Object *current_obj;
    *x = -32000.0f;
    *y = -32000.0f;
    *z = -32000.0f;
    for (i = 0; i < gObjectCount; i++) {
        current_obj = gObjPtrList[i];

        if (current_obj != NULL && !(current_obj->trans.flags & OBJ_FLAGS_PARTICLE) &&
            current_obj->behaviorId == BHV_RAMP_SWITCH && current_obj->properties.common.unk0 == timing) {
            *x = current_obj->trans.x_position;
            *y = current_obj->trans.y_position;
            *z = current_obj->trans.z_position;
        }
    }
}

/**
 * Return the index of the currently active cutscene.
 */
s16 cutscene_id(void) {
    return gCutsceneID;
}

/**
 * Set the current cutscene index.
 */
void cutscene_id_set(s32 cutsceneID) {
    gCutsceneID = cutsceneID;
}

void func_8001E45C(s32 cutsceneID) {
    if (cutsceneID != gCutsceneID) {
        gCutsceneID = cutsceneID;
        gPathUpdateOff = FALSE;
        D_8011AE7E = TRUE;
        if (get_game_mode() == GAMEMODE_MENU) {
            set_frame_blackout_timer();
        }
    }
}

/**
 * Returns the index of the standard object list.
 * Goes unused, since objGetObjList exists
 */
UNUSED s32 get_object_list_index(void) {
    return gObjectListStart;
}

void func_8001E4C4(void) {
    Object *obj;
    s32 lastObjCount;
    s32 curObjCount;
    s32 i;
    s32 j;
    LevelObjectEntry_Animation *entryAnimation;

    for (i = 0; i < gObjectCount; i++) {
        gObjPtrList[i]->trans.flags &= ~OBJ_FLAGS_UNK_2000;
    }
    for (i = 0; i < gObjectCount; i++) {
        obj = gObjPtrList[i];
        if (obj != NULL && !(obj->trans.flags & OBJ_FLAGS_PARTICLE) && obj->behaviorId == BHV_ANIMATION) {
            entryAnimation = &obj->level_entry->animation;
            if (entryAnimation->channel != gCutsceneID && entryAnimation->channel != 20) {
                obj->trans.flags |= OBJ_FLAGS_UNK_2000;
                if (obj->animTarget != NULL) {
                    obj->animTarget->trans.flags |= OBJ_FLAGS_UNK_2000;
                }
            }
        }
    }
    curObjCount = gObjectCount - 1;
    lastObjCount = curObjCount;
    for (i = 0; curObjCount >= i;) {
        for (j = 0; lastObjCount >= i && (j == 0);) {
            if (gObjPtrList[i]->trans.flags & OBJ_FLAGS_UNK_2000) {
                i++;
            } else {
                j = -1;
            }
        }
        for (j = 0; curObjCount >= 0 && j == 0;) {
            if (gObjPtrList[curObjCount]->trans.flags & OBJ_FLAGS_UNK_2000) {
                j = -1;
            } else {
                curObjCount--;
            }
        }
        if (i < curObjCount) {
            obj = gObjPtrList[i];
            gObjPtrList[i] = gObjPtrList[curObjCount];
            gObjPtrList[curObjCount] = obj;
            i++;
            curObjCount--;
        }
    }
    gObjectListStart = i;
    gFirstActiveObjectId = 0;
}

void func_8001E6EC(s8 arg0) {
    LevelObjectEntry_OverridePos *overridePosEntry;
    Object *overridePosObj;
    Object_OverridePos *overridePos;
    s32 i;
    s32 j;
    s32 someBool;
    Object *animTarget;

    for (i = 0; i < D_8011AE00; i++) {
        overridePosObj = D_8011ADD8[i];
        overridePosEntry = &overridePosObj->level_entry->overridePos;
        overridePos = overridePosObj->override_pos;
        if ((overridePosEntry->cutsceneId == gCutsceneID) || ((overridePosEntry->cutsceneId == 20))) {
            for (j = 0;
                 (j < D_8011AE78) && (overridePosEntry->behaviorId != D_8011AE74[j]->properties.animation.behaviourID);
                 j++) {}
            if (j != D_8011AE78 && D_8011AE74[j]->animTarget != NULL) {
                someBool = (D_8011AE74[j]->animTarget->collisionData != NULL) ? FALSE : TRUE;
                if (arg0 != someBool) {
                    animTarget = D_8011AE74[j]->animTarget;
                    overridePos->x = animTarget->trans.x_position;
                    overridePos->y = animTarget->trans.y_position;
                    overridePos->z = animTarget->trans.z_position;
                    overridePos->anim = animTarget;
                    animTarget->trans.x_position = overridePosObj->trans.x_position;
                    animTarget->trans.y_position = overridePosObj->trans.y_position;
                    animTarget->trans.z_position = overridePosObj->trans.z_position;
                }
            } else {
                overridePos->anim = NULL;
            }
        }
    }
    D_8011AE01 = FALSE;
}

void func_8001E89C(void) {
    s32 i;
    Object *obj;
    Object_OverridePos *obj64;

    // some flag, flips to 1 when loading a new zone
    if (D_8011AE01 != FALSE) {
        D_8011AE01 = FALSE;
        return;
    }

    // loading (boss) cutscene
    for (i = 0; i < D_8011AE00; i++) {
        obj = D_8011ADD8[i];
        obj64 = obj->override_pos;

        if (obj64->anim != NULL) {
            obj64->anim->trans.x_position = obj64->x;
            obj64->anim->trans.y_position = obj64->y;
            obj64->anim->trans.z_position = obj64->z;
        }
    }
}

void func_8001E93C(void) {
    s32 pad[3];
    LevelObjectEntry_OverridePos *overridePos;
    Object *obj;
    s32 numOfObjs;
    s32 pad2;
    s32 i;
    s32 stopLooping;
    s32 sp28;
    s16 animActorIndex1;
    s16 animActorIndex2;
    s32 var_a0;
    Object *animObj1;
    LevelObjectEntry_Animation *animation1;
    LevelObjectEntry_Animation *animation2;

    if (D_8011AE7E) {
        for (numOfObjs = 0; numOfObjs < D_8011AE78; numOfObjs++) {
            obj = D_8011AE74[numOfObjs];
            animation1 = &obj->level_entry->animation;
            if (obj->animTarget != NULL && animation1->channel != 20) {
                animObj1 = obj->animTarget;
                free_object(animObj1);
                obj->animTarget = NULL;
            }
        }
    }
    if (D_8011AD3E > 20) {
        D_8011AD3E = 0;
    }
    func_8001E4C4();
    numOfObjs = 0;
    for (i = 0; i < gObjectCount; i++) {
        if (gObjPtrList[i] != NULL) {
            if (!(gObjPtrList[i]->trans.flags & OBJ_FLAGS_PARTICLE)) {
                if (gObjPtrList[i]->behaviorId == BHV_OVERRIDE_POS) {
                    overridePos = &gObjPtrList[i]->level_entry->overridePos;
                    if (overridePos->cutsceneId == gCutsceneID ||
                        overridePos->cutsceneId == (CUTSCENE_SHERBET_ISLAND_BOSS | CUTSCENE_ADVENTURE_TWO)) {
                        D_8011ADD8[numOfObjs] = gObjPtrList[i];
                        numOfObjs++;
                    }
                }
            }
        }
    }
    D_8011AE00 = numOfObjs;
    D_8011AE01 = TRUE;

    D_8011AE78 = 0;
    numOfObjs = 0;
    for (i = gObjectListStart; i < gObjectCount; i++) {
        if (gObjPtrList[i] != NULL) {
            if (!(gObjPtrList[i]->trans.flags & OBJ_FLAGS_PARTICLE)) {
                if (gObjPtrList[i]->behaviorId == BHV_ANIMATION) {
                    D_8011AE74[numOfObjs] = gObjPtrList[i];
                    numOfObjs++;
                }
            }
        }
    }

    do {
        stopLooping = TRUE;
        for (i = 0; i < numOfObjs - 1; i++) {
            animation1 = &D_8011AE74[i]->level_entry->animation;
            animation2 = &D_8011AE74[i + 1]->level_entry->animation;
            animActorIndex1 = animation1->actorIndex;
            animActorIndex2 = animation2->actorIndex;

            if (animation1->channel == 20) {
                animActorIndex1 -= 400;
            }
            if (animation2->channel == 20) {
                animActorIndex2 -= 400;
            }

            if (animActorIndex2 < animActorIndex1) {
                animObj1 = D_8011AE74[i];
                D_8011AE74[i] = D_8011AE74[i + 1];
                D_8011AE74[i + 1] = animObj1;
                stopLooping = FALSE;
            } else if (animActorIndex1 == animActorIndex2) {
                if (animation2->order < animation1->order) {
                    animObj1 = D_8011AE74[i];
                    D_8011AE74[i] = D_8011AE74[i + 1];
                    D_8011AE74[i + 1] = animObj1;
                    stopLooping = FALSE;
                } else if (animation1->order == animation2->order &&
                           (D_8011AE74[i + 1]->properties.animation.action == 1 ||
                            D_8011AE74[i]->properties.animation.action == 2)) {
                    animObj1 = D_8011AE74[i];
                    D_8011AE74[i] = D_8011AE74[i + 1];
                    D_8011AE74[i + 1] = animObj1;
                    stopLooping = FALSE;
                }
            }
        }
    } while (stopLooping == FALSE);

    var_a0 = -101;
    for (i = 0; i < numOfObjs; i += 1) {
        animation1 = &D_8011AE74[i]->level_entry->animation;
        if (animation1->actorIndex != var_a0) {
            var_a0 = animation1->actorIndex;
            sp28 = 0;
        }
        animation1->order = sp28++; // It is possible that sp28 could not be initalized?
        D_8011AE74[i]->properties.animation.action = 0;
    }

    D_8011AE78 = numOfObjs;
    if (D_8011AE7E) {
        func_8001EE74();
    }
    D_8011AE7E = FALSE;
}

void func_8001EE74(void) {
    LevelObjectEntry_Animation *animation;
    Object *obj;
    s32 i;

    for (i = 0; i < D_8011AE78; i++) {
        obj = D_8011AE74[i];
        animation = &obj->level_entry->animation;
        if (obj->animTarget == NULL && animation->order == 0 && animation->objectIdToSpawn != -1) {
            func_8001F23C(obj, animation);
        }
        if (D_8011AD26 || animation->channel != 20) {
            if (obj->animTarget != NULL) {
                obj_init_animobject(obj, obj->animTarget);
            }
        }
    }
    D_8011AD26 = FALSE;
}

void obj_init_animobject(Object *animationObj, Object *animatedObj) {
    LevelObjectEntry_Animation *animEntry;
    Object_AnimatedObject *anim;
    f32 scale;

    animEntry = &animationObj->level_entry->animation;
    anim = animatedObj->animatedObject;
    scale = animEntry->scale & 0xFF;
    if (scale < 1.0f) {
        scale = 1.0f;
    }
    scale /= 64;
    animatedObj->trans.scale = animatedObj->header->scale * scale;
    animatedObj->properties.animatedObj.unk0 = 0;
    animatedObj->properties.animatedObj.unk4 = 0;
    if (animEntry->unk22 >= 2 && animEntry->unk22 < 10) {
        animatedObj->properties.animatedObj.unk0 = animEntry->unk22 - 1;
    }
    if (animEntry->unk22 >= 10 && animEntry->unk22 < 18) {
        animatedObj->properties.animatedObj.unk0 = animEntry->unk22 - 9;
    }
    animatedObj->trans.x_position = animationObj->trans.x_position;
    animatedObj->trans.y_position = animationObj->trans.y_position;
    animatedObj->trans.z_position = animationObj->trans.z_position;
    animatedObj->trans.rotation.y_rotation = animationObj->trans.rotation.y_rotation;
    animatedObj->trans.rotation.z_rotation = animationObj->trans.rotation.z_rotation;
    animatedObj->trans.rotation.x_rotation = animationObj->trans.rotation.x_rotation;
    anim->unk26 = 0;
    anim->unk3D = animEntry->channel;
    anim->actorIndex = animEntry->actorIndex;
    anim->unk8 = (f32) animEntry->nodeSpeed * 0.1;
    anim->startDelay = normalise_time(animEntry->animationStartDelay);
    animatedObj->animationID = animEntry->objAnimIndex;
    animatedObj->animFrame = animEntry->unk16;
    anim->z = animEntry->objAnimSpeed;
    anim->y = 0;
    anim->loopType = animEntry->objAnimLoopType;
    anim->unk2E = animEntry->rotateType;
    anim->unk3E = animEntry->nextAnim;
    anim->unk3F = animEntry->unk2D;
    anim->unk31 = animEntry->yawSpinSpeed;
    anim->unk32 = animEntry->rollSpinSpeed;
    anim->unk33 = animEntry->pitchSpinSpeed;
    anim->unk34 = animEntry->unk20;
    anim->unk2D = 0;
    anim->unk4 = 0;
    anim->unk0 = 0;
    animationObj->particleEmitter = NULL;
    anim->pauseCounter = normalise_time(animEntry->pauseFrameCount);
    anim->unk3A = animEntry->specialHide;
    if (animEntry->unk13 >= 0) {
        anim->unk2F = animEntry->unk13;
    }
    anim->unk39 = animEntry->unk1F;
    anim->soundID = animEntry->unk1E;
    anim->unk3B = animEntry->unk29;
    anim->unk40 = animEntry->soundEffect;
    anim->unk41 = animEntry->fadeOptions;
    anim->unk3C = animEntry->fadeAlpha;
    anim->unk42 = 0xFF;
    if (anim->unk18 != NULL) {
        sndp_stop(anim->unk18);
    }
    anim->unk18 = NULL;
    anim->unk43 = animEntry->unk30;
    anim->unk1C = animationObj;
    anim->unk45 = 0;
}

void func_8001F23C(Object *obj, LevelObjectEntry_Animation *animEntry) {
    s32 i;
    LevelObjectEntryCommon newObjEntry;
    Object *newObj;
    Object_AnimatedObject *camera;
    s32 viewportCount;

    NEW_OBJECT_ENTRY(newObjEntry, animEntry->objectIdToSpawn, 8, animEntry->common.x, animEntry->common.y,
                     animEntry->common.z);

    obj->animTarget = spawn_object(&newObjEntry, OBJECT_SPAWN_UNK01);
    newObj = obj->animTarget;
    // (newObj->behaviorId == BHV_DINO_WHALE) is Dinosaur1, Dinosaur2, Dinosaur3, Whale, and Dinoisle
    if (obj->animTarget != NULL && newObj->behaviorId == BHV_DINO_WHALE && gTimeTrialEnabled) {
        free_object(newObj);
        obj->animTarget = NULL;
        newObj = NULL;
    }
    if (newObj != NULL) {
        newObj->level_entry = NULL;
        obj_init_animobject(obj, newObj);
        if (newObj->header->behaviorId == BHV_CAMERA_ANIMATION) {
            camera = newObj->animatedObject;
            camera->unk44 = D_8011AD3E;
            viewportCount = cam_get_viewport_layout();
            if (race_is_adventure_2P()) {
                viewportCount = VIEWPORT_LAYOUT_2_PLAYERS;
            }
            for (i = 0; i < viewportCount;) {
                newObj = spawn_object(&newObjEntry, OBJECT_SPAWN_UNK01);
                if (newObj != NULL) {
                    newObj->level_entry = NULL;
                    obj_init_animobject(obj, newObj);
                    camera = newObj->animatedObject;
                    i++;
                    camera->cameraID = i;
                    camera->unk44 = D_8011AD3E;
                }
            }
            D_8011AD3E++;
        }
    }
}

s8 func_8001F3B8(void) {
    return D_8011ADD4;
}

void func_8001F3C8(s32 arg0) {
    if (arg0 != D_8011ADD4) {
        D_8011AE78 = 0;
    }
    D_8011ADD4 = arg0;
}

s32 func_8001F3EC(s32 arg0) {
    s32 i;
    s32 count;
    if (D_8011AE78 == 0) {
        return -1;
    }

    count = 0;
    for (i = 0; i < D_8011AE78; i++) {
        if (D_8011AE74[i]->properties.animation.behaviourID == arg0) {
            count++;
        }
    }

    return count;
}

void func_8001F450(void) {
    D_8011AD53 = 1;
}

s32 func_8001F460(Object *arg0, s32 arg1, Object *arg2) {
    f32 var_f2;
    f32 var_f0;
    f32 var_f20;
    s32 var_s0;
    s32 var_s2;
    s32 var_s4;
    s32 var_s5;
    s32 q;
    s32 var_t0;
    ObjectTransform *trans;
    Object_AnimatedObject *obj64;
    s32 sp168;
    f32 sp154[5];
    f32 sp140[5];
    f32 sp12C[5];
    LevelObjectEntry_Animation *temp_s1;
    f32 sp124;
    f32 sp120;
    f32 sp11C;
    Object *otherObj64;
    f32 sp114;
    ObjectModel *temp_a0_3;
    s32 temp_a1_2;
    s32 var_v0_2;

    f32 spF4[5];
    f32 spE0[5];
    f32 spCC[5];
    f32 spB8[5];
    f32 spB4;
    s8 *miscAsset;
    s32 pad;
    FadeTransition fadeTransition;

    if (gCutsceneID < 0) {
        return 1;
    }

    if (arg1 >= 9) {
        arg1 = 8;
    }

    sp114 = arg1;

    obj64 = arg0->animatedObject;
    if (osTvType == 0) {
        sp114 *= 1.2;
    }
    if (obj64->startDelay < 0) {
        var_t0 = 0;
        if (obj64->unk34 & 1) {
            var_t0 = A_BUTTON;
        }
        if (obj64->unk34 & 2) {
            var_t0 |= B_BUTTON;
        }
        if (obj64->unk34 & 4) {
            var_t0 |= CONT_START;
        }

        var_s2 = 0;

        // clang-format off
        for (var_s0 = 0; var_s0 < MAXCONTROLLERS; var_s0++) { var_s2 |= input_pressed(var_s0); }
        // clang-format on

        if (var_s2 & var_t0) {
            obj64->startDelay = 1;
        }
    }

    if ((obj64->startDelay >= 0) && (obj64->unk45 == 0)) {
        obj64->startDelay -= arg1;
        if (obj64->startDelay <= 0) {
            obj64->unk45 = 1;
            temp_s1 = &obj64->unk1C->level_entry->animation;
            func_80021104(arg0, obj64, temp_s1);
            obj64->startDelay = 0;
            func_8002125C(arg0, temp_s1, obj64, -1);
        }
    }
    if (obj64->startDelay != 0) {
        if (obj64->unk3A != 0) {
            arg0->trans.flags |= OBJ_FLAGS_INVISIBLE;
            obj64->unk42 = 0;
            return 1;
        } else {
            return 0;
        }
    }

    arg0->trans.flags &= ~OBJ_FLAGS_INVISIBLE;
    if (obj64->unk39 > 0) {
        if (obj64->unk39 != music_current_sequence()) {
            music_play(obj64->unk39);
            music_change_off();
        }
        obj64->unk39 = -2;
        music_volume_reset();
    } else if (obj64->unk39 == -2) {
        music_change_on();
        obj64->unk39 = -1;
    }
    if (obj64->soundID != 0) {
        var_v0_2 = obj64->soundID & 0xFF;
        if (obj64->currentSound == 0) {
            if (var_v0_2 == 0xFF) {
                if (obj64->unk18 != NULL) {
                    sndp_stop(obj64->unk18);
                }
            } else {
                if (obj64->unk18 != NULL) {
                    sndp_stop(obj64->unk18);
                    var_v0_2 = obj64->soundID & 0xFF;
                }
                sound_play(var_v0_2, &obj64->unk18);
            }
            obj64->soundID = 0;
        }
    }

    if (obj64->unk43 != 0) {
        music_fade(obj64->unk43 << 8);
        obj64->unk43 = 0;
    }

    var_t0 = (u8) obj64->unk42;
    if (obj64->unk41 & 1) {
        if (obj64->unk41 & 2) {
            var_t0 = 0;
        }
        if ((arg1 * 8) < var_t0) {
            var_t0 -= (arg1 * 8);
        } else {
            var_t0 = 0;
            arg0->trans.flags |= OBJ_FLAGS_INVISIBLE;
        }
    } else {
        if (obj64->unk41 & 2) {
            var_t0 = 0xFF;
        }
        var_t0 += arg1 * 8;
        if (var_t0 > 0xFF) {
            var_t0 = 0xFF;
        }
        arg0->trans.flags &= ~OBJ_FLAGS_INVISIBLE;
    }

    var_s2 = obj64->unk3B & 0x7F;
    obj64->unk42 = var_t0;
    if (var_s2 != 0x7F) {
        if (var_s2 >= 8) {
            miscAsset = ((s8 *) get_misc_asset(ASSET_MISC_13) + (var_s2 * 5));
            miscAsset -= 0x28;
            var_t0 = (miscAsset[0] & 0xFF) + 900;
            var_s0 = (miscAsset[1] & 0xFF) + 900;
            slowly_change_fog(0, miscAsset[2] & 0xFF, miscAsset[3] & 0xFF, miscAsset[4] & 0xFF, var_t0, var_s0,
                              normalise_time(6) * obj64->unk3C);
        } else if (var_s2 >= 6) {
            fadeTransition.type = FADE_FLAG_INVERT;
            // clang-format off
            if (var_s2 == 7) {
                fadeTransition.red = 200; fadeTransition.green = 200; fadeTransition.blue = 255; 
            } else {
                fadeTransition.red = 255; fadeTransition.green = 255; fadeTransition.blue = 255;
            }
            // clang-format on
            fadeTransition.duration = 7;
            fadeTransition.endTimer = 3;
            transition_begin(&fadeTransition);
        } else {
            fadeTransition.type = obj64->unk3B;
            miscAsset = (s8 *) get_misc_asset(ASSET_MISC_14) + (obj64->unk40 * 3);
            fadeTransition.red = miscAsset[0];
            fadeTransition.green = miscAsset[1];
            fadeTransition.blue = miscAsset[2];
            if (obj64->unk3B & 0x80) {
                fadeTransition.endTimer = 0;
            } else {
                fadeTransition.endTimer = 0xFFFF;
            }
            fadeTransition.duration = normalise_time(6) * obj64->unk3C;
            if (check_fadeout_transition() == 0 || (fadeTransition.type & 0x80)) {
                transition_begin(&fadeTransition);
            }
        }
        obj64->unk3B = 0xFF;
    }

    if (obj64->unk2E == 1) {
        arg0->trans.rotation.y_rotation += (s16) (obj64->unk31 * (f32) (sp114 * 8.0));
        arg0->trans.rotation.x_rotation += (s16) (obj64->unk32 * (f32) (sp114 * 8.0));
        arg0->trans.rotation.z_rotation += (s16) (obj64->unk33 * (f32) (sp114 * 8.0));
    }

    if (arg2 != NULL && arg2->header->modelType == 0) {
        arg2->animationID = arg0->animationID;
        if ((s16) obj64->y != arg2->animFrame) {
            obj64->y = arg2->animFrame;
        }
        if (arg2->modelInstances[arg2->modelIndex] != NULL) {
            temp_a0_3 = arg2->modelInstances[arg2->modelIndex]->objModel;
            if (arg2->animationID >= 0 && arg2->animationID < temp_a0_3->numberOfAnimations) {
                var_s5 = (temp_a0_3->animations[arg2->animationID].animLength - 1) << 4;
                switch (obj64->loopType) {
                    case 0:
                        obj64->y += obj64->z * sp114;
                        if (obj64->y >= var_s5) {
                            obj64->y -= var_s5;
                        }
                        break;
                    case 2:
                        obj64->y += obj64->z * sp114;
                        if (obj64->y >= var_s5) {
                            obj64->y = var_s5 - 1.0f;
                        }
                        break;
                    case 1:
                        if (obj64->unk2D == 0) {
                            obj64->y += obj64->z * sp114;
                            if (obj64->y >= var_s5) {
                                obj64->unk2D = 1;
                                obj64->y = var_s5 - 1.0f;
                            }
                        } else {
                            obj64->y -= obj64->z * sp114;
                            if (obj64->y <= 0) {
                                obj64->y = 0;
                                obj64->unk2D = 0;
                            }
                        }
                        break;
                    case 3:
                        if (obj64->unk2D == 0) {
                            obj64->y += obj64->z * sp114;
                            if (obj64->y >= var_s5) {
                                obj64->unk2D = 1;
                                obj64->y = var_s5 - 1.0f;
                            }
                        } else {
                            obj64->y -= obj64->z * sp114;
                            if (obj64->y <= 0) {
                                obj64->y = 0;
                            }
                        }
                        break;
                }
            }
        }
        arg2->animFrame = obj64->y;
    }

    if (obj64->unk8 <= 0.0) {
        return func_800214E4(arg0, arg1);
    }

    temp_a1_2 = obj64->actorIndex;
    for (var_s4 = 0; var_s4 < D_8011AE78 && temp_a1_2 != D_8011AE74[var_s4]->properties.animation.behaviourID;
         var_s4++) {}
    if (var_s4 >= D_8011AE78) {
        return func_800214E4(arg0, arg1);
    }

    for (var_s5 = 1;
         (var_s4 + var_s5) < D_8011AE78 && temp_a1_2 == D_8011AE74[var_s4 + var_s5]->properties.animation.behaviourID;
         var_s5++) {}
    if (var_s5 < 2) {
        return func_800214E4(arg0, arg1);
    }

    sp168 = -1;
    spB4 = 1.0 / D_8011AE74[0]->header->scale;

    temp_s1 = &D_8011AE74[var_s4 + var_s5 - 1]->level_entry->animation;
    if (var_s5 > 2) {
        if (temp_s1->goToNode >= 0 && temp_s1->goToNode < var_s5 - 1) {
            sp168 = temp_s1->goToNode;
        }
    }

    if (sp168 == -1 && obj64->unk26 >= var_s5 - 1) {
        return func_800214E4(arg0, arg1);
    }

    if (obj64->pauseCounter >= 0) {
        if (D_8011AD53 == 0) {
            obj64->pauseCounter -= arg1;
        }
        return 0;
    }

    var_s0 = obj64->unk26 - 1;
    var_s2 = 0;
    for (var_t0 = 0; var_t0 != 5; var_s2++, var_t0++, var_s0++) {
        if (var_s0 == -1) {
            if (sp168 != 0) {
                sp154[var_s2] = D_8011AE74[var_s4]->trans.x_position +
                                (D_8011AE74[var_s4]->trans.x_position - D_8011AE74[var_s4 + 1]->trans.x_position);
                sp140[var_s2] = D_8011AE74[var_s4]->trans.y_position +
                                (D_8011AE74[var_s4]->trans.y_position - D_8011AE74[var_s4 + 1]->trans.y_position);
                sp12C[var_s2] = D_8011AE74[var_s4]->trans.z_position +
                                (D_8011AE74[var_s4]->trans.z_position - D_8011AE74[var_s4 + 1]->trans.z_position);
                spE0[var_t0] = D_8011AE74[var_s4]->trans.rotation.y_rotation;
                spCC[var_t0] = D_8011AE74[var_s4]->trans.rotation.x_rotation;
                spB8[var_t0] = D_8011AE74[var_s4]->trans.rotation.z_rotation;
                spF4[var_t0] = D_8011AE74[var_s4]->trans.scale;
            } else {
                q = var_s4 + var_s5 - 1;
                sp154[var_s2] = D_8011AE74[q]->trans.x_position;
                sp140[var_s2] = D_8011AE74[q]->trans.y_position;
                sp12C[var_s2] = D_8011AE74[q]->trans.z_position;
                spE0[var_t0] = D_8011AE74[q]->trans.rotation.y_rotation;
                spCC[var_t0] = D_8011AE74[q]->trans.rotation.x_rotation;
                spB8[var_t0] = D_8011AE74[q]->trans.rotation.z_rotation;
                spF4[var_t0] = D_8011AE74[q]->trans.scale;
            }
        } else if (var_s0 >= var_s5) {
            if (sp168 == -1) {
                var_s0 = var_s5 - 1;
                q = var_s5 + var_s4 - 1;
                temp_s1 = &D_8011AE74[q]->level_entry->animation;
                if (temp_s1->unk22 == 1) {
                    set_active_camera(obj64->cameraID);
                    trans = &cam_get_active_camera_no_cutscenes()->trans;
                } else {
                    trans = &D_8011AE74[q]->trans;
                }
                sp154[var_s2] = trans->x_position + (trans->x_position - D_8011AE74[q - 1]->trans.x_position);
                sp140[var_s2] = trans->y_position + (trans->y_position - D_8011AE74[q - 1]->trans.y_position);
                sp12C[var_s2] = trans->z_position + (trans->z_position - D_8011AE74[q - 1]->trans.z_position);
                spCC[var_t0] = trans->rotation.x_rotation;
                spB8[var_t0] = trans->rotation.z_rotation;
                trans = &D_8011AE74[q]->trans;
                spE0[var_t0] = trans->rotation.y_rotation;
                spF4[var_t0] = D_8011AE74[q]->trans.scale;
            } else {
                q = var_s4 + sp168 + var_s0 - var_s5;
                sp154[var_s2] = D_8011AE74[q]->trans.x_position;
                sp140[var_s2] = D_8011AE74[q]->trans.y_position;
                sp12C[var_s2] = D_8011AE74[q]->trans.z_position;
                spE0[var_t0] = D_8011AE74[q]->trans.rotation.y_rotation;
                spCC[var_t0] = D_8011AE74[q]->trans.rotation.x_rotation;
                spB8[var_t0] = D_8011AE74[q]->trans.rotation.z_rotation;
                spF4[var_t0] = D_8011AE74[q]->trans.scale;
            }
        } else {
            q = var_s0 + var_s4;
            if (obj64->z) {} // @fake
            temp_s1 = &D_8011AE74[q]->level_entry->animation;

            if (temp_s1->unk22 == 1) {
                set_active_camera(obj64->cameraID);
                trans = &cam_get_active_camera_no_cutscenes()->trans;
            } else {
                trans = &D_8011AE74[q]->trans;
            }
            sp154[var_s2] = trans->x_position;
            sp140[var_s2] = trans->y_position;
            sp12C[var_s2] = trans->z_position;
            spCC[var_t0] = trans->rotation.x_rotation;
            spB8[var_t0] = trans->rotation.z_rotation;
            trans = &D_8011AE74[q]->trans;
            spE0[var_t0] = trans->rotation.y_rotation;
            if (temp_s1->unk22 == 1) {
                spCC[var_t0] = -spCC[var_t0];
            }
            spF4[var_t0] = D_8011AE74[q]->trans.scale;
        }
    }

    if (obj64->unk4 == 0) {
        obj64->unk4 = 0.01f;
    }

    for (var_s2 = 0, var_s0 = 0; var_s0 < 2; var_s0++) {
        var_f20 = obj64->unk0 + (obj64->unk4 * sp114);
        if (var_f20 >= 1.00) {
            var_s2 = 1;
            var_f20 -= 1.0;
        }
        if (obj64->unk3F == 0) {
            sp124 = catmull_rom_interpolation(sp154, var_s2, var_f20);
            sp120 = catmull_rom_interpolation(sp140, var_s2, var_f20);
            sp11C = catmull_rom_interpolation(sp12C, var_s2, var_f20);
        } else {
            sp124 = lerp(sp154, var_s2, var_f20);
            sp120 = lerp(sp140, var_s2, var_f20);
            sp11C = lerp(sp12C, var_s2, var_f20);
        }
        sp124 -= arg0->trans.x_position;
        sp120 -= arg0->trans.y_position;
        sp11C -= arg0->trans.z_position;
        if (var_s0 != 1) {
            var_s2 = 0;
            var_f2 = sqrtf((sp124 * sp124) + (sp120 * sp120) + (sp11C * sp11C)) / sp114;
            if (var_f2 != 0) {
                obj64->unk4 *= obj64->unk8 / var_f2;
            }
        }
    }

    arg0->trans.scale = catmull_rom_interpolation(spF4, var_s2, var_f20) * spB4 * arg0->header->scale;
    if (var_s2 != 0 && sp168 == -1 && var_s5 == obj64->unk26 + 2) {
        sp124 = catmull_rom_interpolation(sp154, 0, 1.0f);
        sp120 = catmull_rom_interpolation(sp140, 0, 1.0f);
        sp11C = catmull_rom_interpolation(sp12C, 0, 1.0f);
        sp124 -= arg0->trans.x_position;
        sp120 -= arg0->trans.y_position;
        sp11C -= arg0->trans.z_position;
    }

    arg0->x_velocity = sp124 / sp114;
    arg0->y_velocity = sp120 / sp114;
    arg0->z_velocity = sp11C / sp114;
    move_object(arg0, sp124, sp120, sp11C);

    switch (obj64->unk2E) {
        case 1:
            break;
        case 2:
            if (obj64->unk3F == 0) {
                cubic_spline_interpolation(sp154, var_s2, var_f20, &sp124);
                cubic_spline_interpolation(sp140, var_s2, var_f20, &sp120);
                cubic_spline_interpolation(sp12C, var_s2, var_f20, &sp11C);
            } else {
                lerp_and_get_derivative(sp154, var_s2, var_f20, &sp124);
                lerp_and_get_derivative(sp140, var_s2, var_f20, &sp120);
                lerp_and_get_derivative(sp12C, var_s2, var_f20, &sp11C);
            }
            var_f2 = sqrtf((sp124 * sp124) + (sp120 * sp120) + (sp11C * sp11C));
            if (var_f2 != 0) {
                var_f2 = 100.0 / var_f2;
                sp124 *= var_f2;
                sp120 *= var_f2;
                sp11C *= var_f2;
            }
            arg0->trans.rotation.y_rotation = arctan2_f(sp124, sp11C) - 0x8000;
            arg0->trans.rotation.x_rotation = arctan2_f(sp120, 100.0f);
            break;
        case 3:
            break;
        default:
            for (var_t0 = 1; var_t0 < 5; var_t0++) {
                f32 temp = 0;
                f32 delta;

                delta = spE0[var_t0] - spE0[var_t0 - 1];
                if (delta > 32768.0) {
                    temp -= 65536.0;
                } else if (delta < -32768.0) {
                    temp += 65536.0;
                }
                // clang-format off
                for (var_s0 = var_t0; var_s0 < 5; var_s0++) { spE0[var_s0] += temp; }
                // clang-format on

                temp = 0;
                delta = spCC[var_t0] - spCC[var_t0 - 1];
                if (delta > 32768.0) {
                    temp -= 65536.0;
                } else if (delta < -32768.0) {
                    temp += 65536.0;
                }
                // clang-format off
                for (var_s0 = var_t0; var_s0 < 5; var_s0++) {spCC[var_s0] += temp; }
                // clang-format on

                temp = 0;
                delta = spB8[var_t0] - spB8[var_t0 - 1];
                if (delta > 32768.0) {
                    temp -= 65536.0;
                } else if (delta < -32768.0) {
                    temp += 65536.0;
                }
                // clang-format off
                for (var_s0 = var_t0; var_s0 < 5; var_s0++) { spB8[var_s0] += temp; }
                // clang-format on
            }
            if (obj64->unk3F == 0) {
                arg0->trans.rotation.s[0] = catmull_rom_interpolation(spE0, var_s2, var_f20);
                arg0->trans.rotation.s[1] = catmull_rom_interpolation(spCC, var_s2, var_f20);
                arg0->trans.rotation.s[2] = catmull_rom_interpolation(spB8, var_s2, var_f20);
            } else {
                arg0->trans.rotation.s[0] = lerp(spE0, var_s2, var_f20);
                arg0->trans.rotation.s[1] = lerp(spCC, var_s2, var_f20);
                arg0->trans.rotation.s[2] = lerp(spB8, var_s2, var_f20);
            }
            break;
    }

    var_t0 = obj64->unk26;
    obj64->unk0 = var_f20;
    if (sp168 != -1 && var_t0 >= var_s5) {
        var_t0 = (var_t0 - var_s5) + sp168;
    }

    temp_s1 = &D_8011AE74[var_s4 + var_t0]->level_entry->animation;
    sp124 = (f32) temp_s1->nodeSpeed * 0.1;
    if (sp124 < 0) {
        sp124 = obj64->x;
    } else {
        obj64->x = sp124;
    }
    if (sp124 >= 0) {
        if (var_s2 == 0) {
            var_s0 = var_t0 + 1;
            if (sp168 != -1 && var_s0 >= var_s5) {
                var_s0 = var_s0 - var_s5 + sp168;
            }
            if (var_s0 < var_s5) {
                temp_s1 = &D_8011AE74[var_s4 + var_s0]->level_entry->animation;
                if (temp_s1->nodeSpeed >= 0) {
                    if (0) {} // @fake
                    sp11C = (f32) temp_s1->nodeSpeed * 0.1;
                } else {
                    sp11C = sp124;
                }
            }
            obj64->unk8 = ((sp11C - sp124) * var_f20) + sp124;
        }
    }

    if (var_s2 != 0) {
        obj64->unk26 += 1;
        if (sp168 == -1) {
            if (obj64->unk26 >= var_s5) {
                obj64->unk26 = var_s5 - 1;
            } else {
                temp_s1 = &D_8011AE74[var_s4 + obj64->unk26]->level_entry->animation;
                func_8002125C(arg0, temp_s1, obj64, var_s4);
            }
        } else {
            if (var_s5 < obj64->unk26) {
                obj64->unk26 = sp168 + 1;
            }
            var_s2 = obj64->unk26;
            if (obj64->unk26 >= var_s5) {
                var_s2 = (obj64->unk26 - var_s5) + sp168;
            }
            var_s2 += var_s4;
            temp_s1 = &D_8011AE74[var_s2]->level_entry->animation;
            func_8002125C(arg0, temp_s1, obj64, var_s4);
        }
    }
    if (obj64->unk2E == 3) {
        for (var_t0 = 0; var_t0 < D_8011AE78 && obj64->unk3E != D_8011AE74[var_t0]->properties.animation.behaviourID;
             var_t0++) {}
        if (var_t0 != D_8011AE78) {
            trans = &D_8011AE74[var_t0]->animTarget->trans;
            if (trans != NULL) {
                sp124 = trans->x_position - arg0->trans.x_position;
                sp120 = trans->y_position - arg0->trans.y_position;
                sp11C = trans->z_position - arg0->trans.z_position;
                var_f0 = sqrtf((sp124 * sp124) + (sp120 * sp120) + (sp11C * sp11C));
                if (var_f0 > 0) {
                    arg0->trans.rotation.y_rotation = arctan2_f(sp124, sp11C) - 0x8000;
                    arg0->trans.rotation.x_rotation = arctan2_f(sp120, var_f0);
                }
            }
        }
    }
    arg0->particleEmittersEnabled = obj64->unk2F;
    obj_spawn_particle(arg0, arg1);
    return 0;
}

s32 func_800210CC(s8 arg0) {
    if (arg0 >= D_8011AD3D) {
        D_8011AD3D = arg0;
        return TRUE;
    }
    return FALSE;
}

void func_80021104(Object *obj, Object_AnimatedObject *animObj, LevelObjectEntry_Animation *entry) {
    Camera *camera;
    ObjectTransform *animObjTrans;

    animObjTrans = &animObj->unk1C->trans;
    if (obj->behaviorId == BHV_CAMERA_ANIMATION) {
        animObj->unk44 = D_8011AD3E;
        D_8011AD3E++;
    }
    if (entry->unk22 == 18) {
        set_active_camera(animObj->cameraID);
        camera = cam_get_active_camera_no_cutscenes();
        animObjTrans->x_position = camera->trans.x_position;
        animObjTrans->y_position = camera->trans.y_position;
        animObjTrans->z_position = camera->trans.z_position;
        animObjTrans->rotation.y_rotation = (0x8000 - camera->trans.rotation.y_rotation);
        animObjTrans->rotation.x_rotation = -camera->trans.rotation.x_rotation;
        animObjTrans->rotation.z_rotation = camera->trans.rotation.z_rotation;
    }
    if ((entry->unk22 >= 10) && (entry->unk22 < 18)) {
        Object *seg = (*gRacers)[entry->unk22 - 10];
        if (seg != NULL) {
            animObjTrans->x_position = seg->trans.x_position;
            animObjTrans->y_position = seg->trans.y_position;
            animObjTrans->z_position = seg->trans.z_position;
            animObjTrans->rotation.y_rotation = seg->trans.rotation.y_rotation;
            animObjTrans->rotation.x_rotation = seg->trans.rotation.x_rotation;
            animObjTrans->rotation.z_rotation = seg->trans.rotation.z_rotation;
        }
    }
}

void func_8002125C(Object *obj, LevelObjectEntry_Animation *entry, Object_AnimatedObject *animObj, UNUSED s32 index) {
    s32 initialAnimFrame;

    initialAnimFrame = entry->objAnimIndex;
    if (initialAnimFrame >= 0) {
        if (initialAnimFrame != obj->animationID) {
            obj->animFrame = entry->unk16;
        }
        obj->animationID = entry->objAnimIndex;
        animObj->z = entry->objAnimSpeed;
        animObj->loopType = entry->objAnimLoopType;
    }
    if (entry->unk13 >= 0) {
        animObj->unk2F = entry->unk13;
    }
    animObj->pauseCounter = normalise_time(entry->pauseFrameCount);
    animObj->unk3F = entry->unk2D;
    animObj->unk3A = entry->specialHide;
    animObj->unk39 = entry->unk1F;
    animObj->unk43 = entry->unk30;
    animObj->soundID = entry->unk1E;
    animObj->unk3B = entry->unk29;
    animObj->unk40 = entry->soundEffect;
    animObj->unk41 = entry->fadeOptions;
    animObj->unk3C = entry->fadeAlpha;
    if (entry->messageId != 255) {
        set_current_text(entry->messageId);
    }
    if (entry->unk2A >= 0) {
        func_8001E45C(entry->unk2A);
        return;
    }
    if (entry->unk15 >= 0) {
        func_80021400(entry->unk15);
    }
    if (entry->unk28 >= 0) {
        D_8011AD22[D_8011AD21]++;
    }
}

void func_80021400(s32 arg0) {
    s32 i;
    arg0 &= 0xFF; //?

    for (i = 0; i < D_8011AE78 && (arg0 != (D_8011AE74[i]->properties.animation.behaviourID & 0xFF)); i++) {}

    if (i < D_8011AE78) {
        if (D_8011AE74[i]->animTarget != NULL) {
            if (D_8011AE74[i]->animTarget->animatedObject->startDelay < 0) {
                D_8011AE74[i]->animTarget->animatedObject->startDelay = 1;
            }
        }
    }
}

s8 func_800214C4(void) {
    return D_8011AD22[1 - D_8011AD21];
}

s8 func_800214E4(Object *obj, s32 updateRate) {
    s32 i;
    Object_AnimatedObject *animObj;

    animObj = obj->animatedObject;
    if (animObj->unk3A != 0) {
        obj->trans.flags |= OBJ_FLAGS_INVISIBLE;
    }
    if (animObj->pauseCounter == -1) {
        return animObj->unk3A;
    }
    if (animObj->pauseCounter >= 0) {
        animObj->pauseCounter -= updateRate;
    }
    if (animObj->pauseCounter == -1) {
        animObj->pauseCounter = -2;
    }
    if (animObj->pauseCounter <= 0) {
        obj->trans.flags |= OBJ_FLAGS_INVISIBLE;
        for (i = 0; (i < D_8011AE78 && animObj->actorIndex != D_8011AE74[i]->properties.animation.behaviourID); i++) {
            if (FALSE) {} // FAKEMATCH
        }
        obj_init_animobject(D_8011AE74[i], obj);
        return 1;
    }
    return 0;
}

s32 func_80021600(s32 arg0) {
    Object_AnimatedObject *objAnim;
    s32 i;
    Object *sp154;
    LevelObjectEntry_Animation *levelObjAnim;
    s32 count;
    s32 s0;
    s32 j;
    ObjectTransform *objTransform;
    f32 f0;
    s32 sp138;
    f32 xPositions[5];
    f32 yPositions[5];
    f32 zPositions[5];
    f32 spF8;
    f32 spF4;
    f32 spF0;
    f32 spEC;
    f32 delta;
    s32 q;
    f32 scales[5];
    f32 yRotations[5];
    f32 xRotations[5];
    f32 zRotations[5];
    f32 sp90;

    if (gCutsceneID < 0) {
        return TRUE;
    }

    for (i = 0; i < D_8011AE78 && arg0 != D_8011AE74[i]->properties.animation.behaviourID; i++) {}
    if (i >= D_8011AE78) {
        return TRUE;
    }

    for (count = 1; i + count < D_8011AE78 && arg0 == D_8011AE74[i + count]->properties.animation.behaviourID;
         count++) {}
    if (count < 2) {
        return TRUE;
    }

    sp154 = D_8011AE74[i]->animTarget;
    if (sp154 == NULL) {
        return TRUE;
    }

    objAnim = sp154->animatedObject;
    sp138 = -1;
    sp90 = 1.0 / D_8011AE74[i]->header->scale;

    levelObjAnim = &D_8011AE74[i + count - 1]->level_entry->animation;
    if (count > 2) {
        if (levelObjAnim->goToNode >= 0 && levelObjAnim->goToNode < count - 1) {
            sp138 = levelObjAnim->goToNode;
        }
    }

    s0 = objAnim->unk26 - 1;
    for (j = 0; j < 5; j++, s0++) {
        if (s0 == -1) {
            if (sp138 != 0) {
                xPositions[j] = D_8011AE74[i]->trans.x_position +
                                (D_8011AE74[i]->trans.x_position - D_8011AE74[i + 1]->trans.x_position);
                yPositions[j] = D_8011AE74[i]->trans.y_position +
                                (D_8011AE74[i]->trans.y_position - D_8011AE74[i + 1]->trans.y_position);
                zPositions[j] = D_8011AE74[i]->trans.z_position +
                                (D_8011AE74[i]->trans.z_position - D_8011AE74[i + 1]->trans.z_position);
                yRotations[j] = D_8011AE74[i]->trans.rotation.y_rotation;
                xRotations[j] = D_8011AE74[i]->trans.rotation.x_rotation;
                zRotations[j] = D_8011AE74[i]->trans.rotation.z_rotation;
                scales[j] = D_8011AE74[i]->trans.scale;
            } else {
                q = i + count - 1;
                xPositions[j] = D_8011AE74[q]->trans.x_position;
                yPositions[j] = D_8011AE74[q]->trans.y_position;
                zPositions[j] = D_8011AE74[q]->trans.z_position;
                yRotations[j] = D_8011AE74[q]->trans.rotation.y_rotation;
                xRotations[j] = D_8011AE74[q]->trans.rotation.x_rotation;
                zRotations[j] = D_8011AE74[q]->trans.rotation.z_rotation;
                scales[j] = D_8011AE74[q]->trans.scale;
            }
        } else if (s0 >= count) {
            if (sp138 == -1) {
                s0 = count - 1;
                q = s0 + i;
                levelObjAnim = &D_8011AE74[q]->level_entry->animation;
                if (levelObjAnim->unk22 == 1) {
                    set_active_camera(objAnim->cameraID);
                    objTransform = &cam_get_active_camera_no_cutscenes()->trans;
                } else {
                    objTransform = &D_8011AE74[q]->trans;
                }

                xPositions[j] =
                    (objTransform->x_position - D_8011AE74[q - 1]->trans.x_position) + objTransform->x_position;
                yPositions[j] =
                    (objTransform->y_position - D_8011AE74[q - 1]->trans.y_position) + objTransform->y_position;
                zPositions[j] =
                    (objTransform->z_position - D_8011AE74[q - 1]->trans.z_position) + objTransform->z_position;
                xRotations[j] = objTransform->rotation.x_rotation;
                zRotations[j] = objTransform->rotation.z_rotation;
                objTransform = &D_8011AE74[q]->trans;
                yRotations[j] = objTransform->rotation.y_rotation;
                scales[j] = D_8011AE74[q]->trans.scale;
            } else {
                q = i + sp138 + s0 - count;
                xPositions[j] = D_8011AE74[q]->trans.x_position;
                yPositions[j] = D_8011AE74[q]->trans.y_position;
                zPositions[j] = D_8011AE74[q]->trans.z_position;
                yRotations[j] = D_8011AE74[q]->trans.rotation.y_rotation;
                xRotations[j] = D_8011AE74[q]->trans.rotation.x_rotation;
                zRotations[j] = D_8011AE74[q]->trans.rotation.z_rotation;
                scales[j] = D_8011AE74[q]->trans.scale;
            }
        } else {
            q = s0 + i;
            if (1) {} // Fake
            levelObjAnim = &D_8011AE74[q]->level_entry->animation;
            if (levelObjAnim->unk22 == 1) {
                set_active_camera(objAnim->cameraID);
                objTransform = &cam_get_active_camera_no_cutscenes()->trans;
            } else {
                objTransform = &D_8011AE74[q]->trans;
            }
            xPositions[j] = objTransform->x_position;
            yPositions[j] = objTransform->y_position;
            zPositions[j] = objTransform->z_position;
            xRotations[j] = objTransform->rotation.x_rotation;
            zRotations[j] = objTransform->rotation.z_rotation;
            objTransform = &D_8011AE74[q]->trans;
            yRotations[j] = objTransform->rotation.y_rotation;
            if (levelObjAnim->unk22 == 1) {
                xRotations[j] = -xRotations[j];
            }
            scales[j] = D_8011AE74[q]->trans.scale;
        }
    }

    spEC = objAnim->unk0;
    if (objAnim->unk3F == 0) {
        spF8 = catmull_rom_interpolation(xPositions, 0, spEC);
        spF4 = catmull_rom_interpolation(yPositions, 0, spEC);
        spF0 = catmull_rom_interpolation(zPositions, 0, spEC);
    } else {
        spF8 = lerp(xPositions, 0, spEC);
        spF4 = lerp(yPositions, 0, spEC);
        spF0 = lerp(zPositions, 0, spEC);
    }

    spF8 -= sp154->trans.x_position;
    spF4 -= sp154->trans.y_position;
    spF0 -= sp154->trans.z_position;

    move_object(sp154, spF8, spF4, spF0);
    sp154->trans.scale = catmull_rom_interpolation(scales, 0, spEC) * sp90 * sp154->header->scale;

    switch (objAnim->unk2E) {
        case 1:
            break;
        case 2:
            if (objAnim->unk3F == 0) {
                cubic_spline_interpolation(xPositions, 0, spEC, &spF8);
                cubic_spline_interpolation(yPositions, 0, spEC, &spF4);
                cubic_spline_interpolation(zPositions, 0, spEC, &spF0);
            } else {
                lerp_and_get_derivative(xPositions, 0, spEC, &spF8);
                lerp_and_get_derivative(yPositions, 0, spEC, &spF4);
                lerp_and_get_derivative(zPositions, 0, spEC, &spF0);
            }

            spEC = sqrtf(spF8 * spF8 + spF4 * spF4 + spF0 * spF0);
            if (spEC != 0.0f) {
                delta = spEC;
                spEC = spF8;
                delta = 100.0 / delta;

                spF8 *= delta;
                spF4 *= delta;
                spF0 *= delta;
            }

            sp154->trans.rotation.y_rotation = arctan2_f(spF8, spF0) - 0x8000;
            sp154->trans.rotation.x_rotation = arctan2_f(spF4, 100.0f);
            break;
        case 3:
            for (j = 0; j < D_8011AE78 && objAnim->unk3E != D_8011AE74[j]->properties.animation.behaviourID; j++) {}

            if (j != D_8011AE78) {
                objTransform = &D_8011AE74[j]->animTarget->trans;
                if (objTransform != NULL) {
                    spF8 = objTransform->x_position - sp154->trans.x_position;
                    spF4 = objTransform->y_position - sp154->trans.y_position;
                    spF0 = objTransform->z_position - sp154->trans.z_position;
                    spEC = sqrtf(spF8 * spF8 + spF4 * spF4 + spF0 * spF0);
                    if (spEC > 0.0f) {
                        sp154->trans.rotation.y_rotation = arctan2_f(spF8, spF0) - 0x8000;
                        sp154->trans.rotation.x_rotation = arctan2_f(spF4, spEC);
                    }
                }
            }
            break;
        default:
            for (j = 1; j < 5; j++) {
                f0 = 0.0f;
                delta = yRotations[j] - yRotations[j - 1];
                if (delta > 32768.0) {
                    f0 -= 65536.0;
                } else if (delta < -32768.0) {
                    f0 += 65536.0;
                }

                // clang-format off
                for (s0 = j; s0 < 5; s0++) { yRotations[s0] += f0; }
                // clang-format on

                f0 = 0.0f;
                delta = xRotations[j] - xRotations[j - 1];
                if (delta > 32768.0) {
                    f0 -= 65536.0;
                } else if (delta < -32768.0) {
                    f0 += 65536.0;
                }

                // clang-format off
                for (s0 = j; s0 < 5; s0++) { xRotations[s0] += f0; }
                // clang-format on

                f0 = 0.0f;
                delta = zRotations[j] - zRotations[j - 1];
                if (delta > 32768.0) {
                    f0 -= 65536.0;
                } else if (delta < -32768.0) {
                    f0 += 65536.0;
                }

                // clang-format off
                for (s0 = j; s0 < 5; s0++) { zRotations[s0] += f0; }
                // clang-format on
            }

            if (objAnim->unk3F == 0) {
                sp154->trans.rotation.y_rotation = catmull_rom_interpolation(yRotations, 0, spEC);
                sp154->trans.rotation.x_rotation = catmull_rom_interpolation(xRotations, 0, spEC);
                sp154->trans.rotation.z_rotation = catmull_rom_interpolation(zRotations, 0, spEC);
            } else {
                sp154->trans.rotation.y_rotation = lerp(yRotations, 0, spEC);
                sp154->trans.rotation.x_rotation = lerp(xRotations, 0, spEC);
                sp154->trans.rotation.z_rotation = lerp(zRotations, 0, spEC);
            }
            break;
    }

    return FALSE;
}

f32 catmull_rom_interpolation(f32 *data, s32 index, f32 x) {
    f32 ret;
    f32 c, b, a;

    a = (-0.5 * data[index]) + (1.5 * data[index + 1]) + (-1.5 * data[index + 2]) + (0.5 * data[index + 3]);
    b = (1.0 * data[index]) + (-2.5 * data[index + 1]) + (2.0 * data[index + 2]) + (-0.5 * data[index + 3]);
    c = (data[index + 2] * 0.5) + (0.0 * data[index + 1]) + (-0.5 * data[index]) + (0.0 * data[index + 3]);

    ret = (1.0 * data[index + 1]);
    ret = (((((a * x) + b) * x) + c) * x) + ret;

    return ret;
}

/**
 * Interpolates x along a spline and returns the resultant progress along the spline.
 */
f32 cubic_spline_interpolation(f32 *data, s32 index, f32 x, f32 *derivative) {
    f32 ret;
    f32 c, b, a;

    a = (-0.5 * data[index]) + (1.5 * data[index + 1]) + (-1.5 * data[index + 2]) + (0.5 * data[index + 3]);
    b = (1.0 * data[index]) + (-2.5 * data[index + 1]) + (2.0 * data[index + 2]) + (-0.5 * data[index + 3]);
    c = (data[index + 2] * 0.5) + (0.0 * data[index + 1]) + (-0.5 * data[index]) + (0.0 * data[index + 3]);

    ret = (1.0 * data[index + 1]);
    *derivative = (((a * 3 * x) + (2 * b)) * x) + c;
    ret = (((((a * x) + b) * x) + c) * x) + ret;

    return ret;
}

f32 catmull_rom_derivative(f32 *data, s32 index, f32 x) {
    f32 derivative;
    f32 c, b, a;

    a = (-0.5 * data[index]) + (1.5 * data[index + 1]) + (-1.5 * data[index + 2]) + (0.5 * data[index + 3]);
    b = (1.0 * data[index]) + (-2.5 * data[index + 1]) + (2.0 * data[index + 2]) + (-0.5 * data[index + 3]);
    c = (data[index + 2] * 0.5) + (0.0 * data[index + 1]) + (-0.5 * data[index]) + (0.0 * data[index + 3]);

    derivative = (((a * 3 * x) + (2 * b)) * x) + c;

    return derivative;
}

/**
 * Imprecise method, which does not guarantee v = v1 when t = 1. (From Wikipedia)
 */
f32 lerp(f32 *data, u32 index, f32 t) {
    f32 result = data[index + 1] + t * ((data[index + 2] - data[index + 1]));
    return result;
}

/**
 * Peforms the lerp, and also returns the distance between the two points.
 */
f32 lerp_and_get_derivative(f32 *data, u32 index, f32 t, f32 *derivative) {
    f32 lerp;
    f32 vector;
    vector = data[index + 2] - data[index + 1];
    lerp = data[index + 1] + (vector * t);
    *derivative = vector;
    return lerp;
}

UNUSED void func_800228DC(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2) {
}

/**
 * Prepares the player racer for a Taj Challenge race.
 * Prevents them from pausing for 10 frames.
 */
void init_racer_for_challenge(s32 vehicleID) {
    Object_Racer *racer;

    gTajRaceInit = 3;
    racer = get_racer_object(PLAYER_ONE)->racer;
    racer->courseCheckpoint = 0;
    racer->nextCheckpoint = 0;
    racer->lap = 0;
    racer->unk1BA = 0;
    set_taj_challenge_type(vehicleID);
    set_pause_lockout_timer(10);
}

/**
 * Initialise the relevant variables related to races.
 * These are usually done on level load, but Taj challenges don't reset the level.
 */
void mode_init_taj_race(void) {
    CheckpointNode *checkpointNode;
    UNUSED s32 pad;
    s32 j;
    s32 i;
    s32 lvlSeg;
    LevelHeader *levelHeader;
    LevelObjectEntry_Racer newRacerEntry;
    Settings *settings;
    Object *racerObj;
    Object_Racer *racer;
    f32 yOut[8];

    gTajRaceInit -= 1;
    if (gTajRaceInit == 0) {
        levelHeader = level_header();
        gChallengePrevMusic = levelHeader->music;
        gChallengePrevInstruments = levelHeader->instruments;
        levelHeader->music = SEQUENCE_TAJS_RACES;
        levelHeader->instruments = 0xFFFF;
        racerObj = get_racer_object(PLAYER_ONE);
        racer = racerObj->racer;
        gIsTajChallenge = racer->vehicleID + 1;
        checkpointNode = func_800230D0(racerObj, racer);
        racer->cameraYaw = 0x8000 - racer->steerVisualRotation;
        racer->wrongWayCounter = 0;
        racer->startInput = 0;
        racer->courseCheckpoint = 0;
        racer->nextCheckpoint = 0;
        racer->lap = 0;
        racer->countLap = 0;
        racer->lap_times[0] = 0;
        racer->lap_times[1] = 0;
        racer->lap_times[2] = 0;
        racer->unk1BA = 0;
        settings = get_settings();
        gEventCountdown = 80;
        gRaceFinishTriggered = FALSE;
        gNumFinishedRacers = 1;
        levelHeader->laps = 3;
        levelHeader->race_type = RACETYPE_DEFAULT;
        hud_init_element();
        // clang-format off
        for (i = 0; i < ARRAY_COUNT(racer->lap_times); i++) { racer->lap_times[i] = 0; } // Must be a single line.
        // clang-format on
        newRacerEntry.common.x = (checkpointNode->x + (checkpointNode->rotationZFrac * 35.0f));
        newRacerEntry.common.z = (checkpointNode->z - (checkpointNode->rotationXFrac * 35.0f));
        lvlSeg =
            get_level_segment_index_from_position(newRacerEntry.common.x, checkpointNode->y, newRacerEntry.common.z);
        newRacerEntry.common.y =
            collision_get_y(lvlSeg, newRacerEntry.common.x, newRacerEntry.common.z, yOut) ? yOut[0] : checkpointNode->y;
        newRacerEntry.common.size = 16;
        newRacerEntry.angleY = racer->steerVisualRotation;
        newRacerEntry.angleX = 0;
        newRacerEntry.angleZ = 0;
        newRacerEntry.playerIndex = 4;
        newRacerEntry.common.objectID = ASSET_OBJECT_ID_FLYINGCARPET;
        model_anim_offset(0);
        racerObj = spawn_object(&newRacerEntry.common, OBJECT_SPAWN_UNK01);
        (*gRacers)[1] = racerObj;
        gRacersByPosition[1] = racerObj;
        gRacersByPort[1] = racerObj;
        racerObj->level_entry = NULL;
        gNumRacers = 2;
        racer = racerObj->racer;
        i = 0; // Fakematch
        racer->vehicleID = VEHICLE_CARPET;
        racer->vehicleIDPrev = racer->vehicleID;
        racer->racerIndex = 1;
        racer->characterId = settings->racers[0].character;
        racer->stretch_height_cap = 1.0f;
        racer->stretch_height = 1.0f;
        racer->transparency = 0xFF;
        racer->vehicleSound = NULL;
        racerObj->interactObj->pushForce = 2;

        for (j = gObjectListStart; j < gObjectCount; j++) {
            if (!(gObjPtrList[j]->trans.flags & OBJ_FLAGS_PARTICLE) && gObjPtrList[j]->behaviorId == BHV_PARK_WARDEN) {
                racer->unk154 = gObjPtrList[j];
            }
        }
        set_pause_lockout_timer(20);
        transition_begin(&gTajChallengeTransition);
    }
}

/**
 * Finds which golden balloon should be moved, and move it onto Taj's current position.
 * Sets opacity to 0, so the balloon with smoothly fade in.
 */
void obj_taj_create_balloon(s32 blockID, f32 x, f32 y, f32 z) {
    s32 i;
    Object *obj;
    Settings *settings = get_settings();

    for (i = 0; i < gObjectCount; i++) {
        obj = gObjPtrList[i];
        if (obj->behaviorId == BHV_GOLDEN_BALLOON && obj->level_entry != NULL &&
            obj->level_entry->goldenBalloon.challengeID > 0) {
            if (settings->tajFlags && settings->tajFlags & (1 << (obj->level_entry->goldenBalloon.challengeID + 2))) {
                obj->trans.x_position = x;
                obj->trans.y_position = y + 10.0;
                obj->trans.z_position = z;
                obj->segmentID = blockID;
                obj->properties.common.unk0 = 0;
                obj->opacity = 0;
            }
        }
    }
}

/**
 * Revert changes set by the game when starting the Taj challenge.
 * This includes the music set, as well as the extra racer spawned.
 * Has a different response depending on whether the challenge was aborted or finished.
 */
void mode_end_taj_race(s32 reason) {
    s32 flags;
    s32 i;
    Object_Racer *racer;
    Settings *settings;
    Object *obj;
    LevelHeader *levelHeader;

    levelHeader = level_header();
    levelHeader->race_type = RACETYPE_HUBWORLD;
    levelHeader->music = gChallengePrevMusic;
    levelHeader->instruments = gChallengePrevInstruments;
    minimap_opacity_set(1);

    // Only works with do {} while?
    i = 0;
    do {
        racer = (*gRacers)[i]->racer;
        if (!racer) {}
        racer->raceFinished = 0;
        racer->lap = 0;
        racer->nextCheckpoint = 0;
        racer->courseCheckpoint = 0;
    } while (++i < gNumRacers);

    free_object((*gRacers)[1]);
    gRacersByPosition[0] = (*gRacers)[0];
    gNumRacers = 1;
    for (i = gObjectListStart; i < gObjectCount; i++) {
        if (!(gObjPtrList[i]->trans.flags & OBJ_FLAGS_PARTICLE) && gObjPtrList[i]->behaviorId == BHV_PARK_WARDEN) {
            obj = gObjPtrList[i];
        }
    }
    racer = (*gRacers)[0]->racer;
    if (racer->challengeMarker != NULL) {
        free_object(racer->challengeMarker);
        racer->challengeMarker = NULL;
    }
    if (reason == CHALLENGE_END_FINISH) {
        if (racer->finishPosition == 1) {
            settings = get_settings();
            flags = racer->vehicleID;
            flags = 1 << (flags + 3);
            if (settings->tajFlags & flags) {
                set_next_taj_challenge_menu(5);
            } else {
                set_next_taj_challenge_menu(racer->vehicleID + 6);
                settings->tajFlags |= flags;
                safe_mark_write_save_file(get_save_file_index());
            }
        } else {
            set_next_taj_challenge_menu(4);
        }
        obj->properties.common.unk0 = 31;
        set_taj_status(TAJ_TELEPORT);
    } else {
        music_change_on();
        music_stop();
        set_next_taj_challenge_menu(0);
        audspat_jingle_on();
        if (reason == CHALLENGE_END_OOB) {
            set_current_text(ASSET_GAME_TEXT_0);
        }
        gEventCountdown = 0;
        gEventStartTimer = 0;
        obj->properties.common.unk0 = 20;
    }
    music_change_on();
    hud_audio_init();
    level_music_start(1.0f);
    gIsTajChallenge = FALSE;
}

CheckpointNode *func_800230D0(Object *obj, Object_Racer *racer) {
    CheckpointNode *lastCheckpointNode;
    Camera *activeCameraSegment;
    s32 yOutCount;
    f32 yOut[9];
    Object *ptrList;
    s32 i;

    if (gNumberOfMainCheckpoints == 0) {
        lastCheckpointNode = NULL;
        for (i = 0; i < gObjectCount; i++) {
            ptrList = gObjPtrList[i];
            if (!(ptrList->trans.flags & OBJ_FLAGS_PARTICLE) && (ptrList->behaviorId == BHV_SETUP_POINT)) {
                if (ptrList->properties.setupPoint.racerIndex == 0) {
                    obj->trans.x_position = ptrList->trans.x_position;
                    obj->trans.y_position = ptrList->trans.y_position;
                    obj->trans.z_position = ptrList->trans.z_position;
                    obj->segmentID = ptrList->segmentID;
                    i = gObjectCount;
                }
            }
        }
    } else {
        lastCheckpointNode = &gTrackCheckpoints[gNumberOfMainCheckpoints - 1];
        obj->trans.x_position = lastCheckpointNode->x - (lastCheckpointNode->rotationZFrac * 35.0f);
        obj->trans.y_position = lastCheckpointNode->y;
        obj->trans.z_position = lastCheckpointNode->z + (lastCheckpointNode->rotationXFrac * 35.0f);
        obj->segmentID =
            get_level_segment_index_from_position(obj->trans.x_position, obj->trans.y_position, obj->trans.z_position);
    }
    yOutCount = collision_get_y(obj->segmentID, obj->trans.x_position, obj->trans.z_position, yOut);
    if (yOutCount != 0) {
        obj->trans.y_position = yOut[yOutCount - 1];
    }
    racer->prev_x_position = obj->trans.x_position;
    racer->prev_y_position = obj->trans.y_position;
    racer->prev_z_position = obj->trans.z_position;
    if (lastCheckpointNode != NULL) {
        racer->steerVisualRotation = arctan2_f(lastCheckpointNode->rotationXFrac, lastCheckpointNode->rotationZFrac);
    } else {
        racer->steerVisualRotation = ptrList->trans.rotation.y_rotation;
    }
    racer->nextCheckpoint = 0;
    racer->courseCheckpoint = racer->lap * gNumberOfMainCheckpoints;
    obj->trans.rotation.y_rotation = racer->steerVisualRotation;
    racer->unkD8[0] = obj->trans.x_position;
    racer->unkD8[1] = obj->trans.y_position + 15.0f;
    racer->unkD8[2] = obj->trans.z_position;
    racer->unkD8[3] = obj->trans.x_position;
    racer->unkD8[4] = obj->trans.y_position + 15.0f;
    racer->unkD8[5] = obj->trans.z_position;
    racer->unkD8[6] = obj->trans.x_position;
    racer->unkD8[7] = obj->trans.y_position + 15.0f;
    racer->unkD8[8] = obj->trans.z_position;
    racer->unkD8[9] = obj->trans.x_position;
    racer->unkD8[10] = obj->trans.y_position + 15.0f;
    racer->unkD8[11] = obj->trans.z_position;
    obj->interactObj->x_position = obj->trans.x_position;
    obj->interactObj->y_position = obj->trans.y_position;
    obj->interactObj->z_position = obj->trans.z_position;
    // fake
    if (1) {}
    if (1) {}
    racer->velocity = 0.0f;
    racer->lateral_velocity = 0.0f;
    obj->x_velocity = 0.0f;
    obj->z_velocity = 0.0f;
    racer->vehicleID = racer->vehicleIDPrev;
    if (racer->playerIndex != -1) {
        set_active_camera(racer->playerIndex);
        activeCameraSegment = cam_get_active_camera_no_cutscenes();
        activeCameraSegment->trans.x_position = obj->trans.x_position;
        activeCameraSegment->trans.y_position = obj->trans.y_position;
        activeCameraSegment->trans.z_position = obj->trans.z_position;
    }
    return lastCheckpointNode;
}

/**
 * Returns true if a taj challenge is currently active.
 */
s8 is_taj_challenge(void) {
    return gIsTajChallenge;
}

/**
 * Searches for the furthest teleport anchor and returns it.
 */
Object *find_furthest_telepoint(f32 x, f32 z) {
    Object *tempObj;
    Object *bestObj;
    f32 diffX;
    f32 diffZ;
    f32 distance;
    f32 bestDist;
    s32 i;

    bestDist = 0.0f;
    i = 0;
    bestObj = NULL;
    if (gObjectCount > 0) {
        do {
            tempObj = gObjPtrList[i];
            if (!(tempObj->trans.flags & OBJ_FLAGS_PARTICLE) && tempObj->behaviorId == BHV_TAJ_TELEPOINT) {
                diffX = tempObj->trans.x_position - x;
                diffZ = tempObj->trans.z_position - z;
                tempObj = gObjPtrList[i]; // fakematch
                distance = sqrtf((diffX * diffX) + (diffZ * diffZ));
                if (bestDist < distance) {
                    bestDist = distance;
                    bestObj = tempObj;
                }
            }
            i += 1;
        } while (i < gObjectCount);
    }
    return bestObj;
}

s32 func_80023568(void) {
    if (D_8011AD3C != 0) {
        return D_8011AD24[1] + 1;
    } else if (level_type() == RACETYPE_BOSS) {
        return D_8011AD24[1] + 1;
    }
    return 0;
}

/**
 * Return whether doors can be forced open.
 */
s8 obj_door_override(void) {
    return gOverrideDoors;
}

/**
 * Set a value that decides whether doors can be forced open.
 */
void obj_door_open(s32 setting) {
    gOverrideDoors = setting;
}

/**
 * Return the size of the object property struct intended to be used with the object.
 */
s32 get_object_property_size(Object *obj, void *obj64) {
    s32 temp_v0;
    s32 ret = 0;

    obj->anyBehaviorData = obj64;

    switch (obj->header->behaviorId) {
        case BHV_RACER:
            ret = sizeof(Object_Racer);
            break;
        case BHV_DOOR:
        case BHV_TT_DOOR:
            ret = sizeof(Object_Door);
            break;
        case BHV_EXIT:
            ret = sizeof(Object_Exit);
            break;
        case BHV_ANIMATOR:
            ret = sizeof(Object_Animator);
            break;
        case BHV_AUDIO:
            ret = sizeof(Object_Audio);
            break;
        case BHV_AUDIO_LINE:
        case BHV_AUDIO_LINE_2:
            ret = sizeof(Object_AudioLine);
            break;
        case BHV_AINODE:
            ret = sizeof(Object_AiNode);
            break;
        case BHV_MODECHANGE:
        case BHV_BONUS:
        case BHV_TRIGGER:
            ret = sizeof(Object_Trigger);
            break;
        case BHV_AUDIO_REVERB:
            ret = sizeof(Object_AudioReverb);
            break;
        case BHV_TEXTURE_SCROLL:
            ret = sizeof(Object_TexScroll);
            break;
        case BHV_WEAPON:
        case BHV_WEAPON_2:
            ret = sizeof(Object_Weapon);
            break;
        case BHV_WEAPON_BALLOON:
            ret = sizeof(Object_WeaponBalloon);
            break;
        case BHV_BANANA:
            ret = sizeof(Object_Banana);
            break;
        case BHV_BRIDGE_WHALE_RAMP:
            ret = sizeof(Object_Bridge_WhaleRamp);
            break;
        case BHV_SEA_MONSTER:
            ret = 0x18;
            break;
        case BHV_COLLECT_EGG:
            ret = sizeof(Object_CollectEgg);
            break;
        case BHV_STOPWATCH_MAN:
        case BHV_PARK_WARDEN:
        case BHV_GOLDEN_BALLOON:
            ret = sizeof(Object_NPC);
            break;
        case BHV_LASER_GUN:
            ret = sizeof(Object_LaserGun);
            break;
        case BHV_OVERRIDE_POS:
            ret = sizeof(Object_OverridePos);
            break;
        case BHV_DINO_WHALE:
        case BHV_ANIMATED_OBJECT:
        case BHV_CAMERA_ANIMATION:
        case BHV_CAR_ANIMATION:
        case BHV_CHARACTER_SELECT:
        case BHV_VEHICLE_ANIMATION:
        case BHV_HIT_TESTER:
        case BHV_HIT_TESTER_2:
        case BHV_PARK_WARDEN_2:
        case BHV_ANIMATED_OBJECT_2:
        case BHV_WIZPIG_SHIP:
        case BHV_ANIMATED_OBJECT_3:
        case BHV_ANIMATED_OBJECT_4:
        case BHV_SNOWBALL:
        case BHV_SNOWBALL_2:
        case BHV_SNOWBALL_3:
        case BHV_SNOWBALL_4:
        case BHV_HIT_TESTER_3:
        case BHV_HIT_TESTER_4:
        case BHV_DOOR_OPENER:
        case BHV_PIG_ROCKETEER:
        case BHV_WIZPIG_GHOSTS:
            ret = sizeof(Object_AnimatedObject);
            break;
        case BHV_MIDI_FADE:
            ret = sizeof(Object_MidiFade);
            break;
        case BHV_MIDI_FADE_POINT:
            ret = sizeof(Object_MidiFadePoint);
            break;
        case BHV_MIDI_CHANNEL_SET:
            ret = sizeof(Object_MidiChannelSet);
            break;
        case BHV_BUTTERFLY:
            temp_v0 = 0x10 - ((s32) obj64 & 0xF);
            obj->butterfly = (Object_Butterfly *) ((s32) obj64 + temp_v0);
            ret = (temp_v0 + sizeof(Object_Butterfly));
            break;
        case BHV_FISH:
            temp_v0 = 0x10 - ((s32) obj64 & 0xF);
            obj->fish = (Object_Fish *) ((s32) obj64 + temp_v0);
            ret = (temp_v0 + sizeof(Object_Fish));
            break;
        case BHV_CHARACTER_FLAG:
            temp_v0 = 0x10 - ((s32) obj64 & 0xF);
            obj->characterFlagModel = (CharacterFlagModel *) ((s32) obj64 + temp_v0);
            ret = (temp_v0 + sizeof(CharacterFlagModel));
            break;
        case BHV_UNK_5E:
            ret = 0x60;
            break;
        case BHV_TROPHY_CABINET:
            ret = sizeof(JingleState);
            break;
        case BHV_FROG:
            ret = sizeof(Object_Frog);
            break;
        case BHV_FIREBALL_OCTOWEAPON_2:
            ret = sizeof(Object_Weapon);
            break;
        default:
            obj->anyBehaviorData = NULL;
            break;
    }

    return (ret & ~3) + 4;
}

/**
 * Run when an object is created.
 * Used to do one-time things like initialising variables
 * Arg2 is always zero. Effectively unused.
 */
void run_object_init_func(Object *obj, void *entry, s32 param) {
    obj->behaviorId = obj->header->behaviorId;
    switch (obj->behaviorId) {
        case BHV_RACER:
            obj_init_racer(obj, (LevelObjectEntry_Racer *) entry);
            break;
        case BHV_SCENERY:
            obj_init_scenery(obj, (LevelObjectEntry_Scenery *) entry);
            break;
        case BHV_FISH:
            obj_init_fish(obj, (LevelObjectEntry_Fish *) entry, param);
            break;
        case BHV_ANIMATOR:
            obj_init_animator(obj, (LevelObjectEntry_Animator *) entry, param);
            break;
        case BHV_SMOKE:
            obj_init_smoke(obj, (LevelObjectEntry_Smoke *) entry);
            break;
        case BHV_UNK_19:
            obj_init_unknown25(obj, (LevelObjectEntry_Unknown25 *) entry);
            break;
        case BHV_BOMB_EXPLOSION:
            obj_init_bombexplosion(obj, (LevelObjectEntry_BombExplosion *) entry);
            break;
        case BHV_EXIT:
            obj_init_exit(obj, (LevelObjectEntry_Exit *) entry);
            break;
        case BHV_AUDIO:
            obj_init_audio(obj, (LevelObjectEntry_Audio *) entry);
            break;
        case BHV_AUDIO_LINE:
        case BHV_AUDIO_LINE_2:
            obj_init_audioline(obj, (LevelObjectEntry_AudioLine *) entry);
            break;
        case BHV_AUDIO_REVERB:
            obj_init_audioreverb(obj, (LevelObjectEntry_AudioReverb *) entry);
            break;
        case BHV_CAMERA_CONTROL:
            obj_init_cameracontrol(obj, (LevelObjectEntry_CameraControl *) entry);
            break;
        case BHV_SETUP_POINT:
            obj_init_setuppoint(obj, (LevelObjectEntry_SetupPoint *) entry);
            break;
        case BHV_DINO_WHALE:
            obj_init_dino_whale(obj, (LevelObjectEntry_Dino_Whale *) entry);
            break;
        case BHV_CHECKPOINT:
            obj_init_checkpoint(obj, (LevelObjectEntry_Checkpoint *) entry, param);
            break;
        case BHV_MODECHANGE:
            obj_init_modechange(obj, (LevelObjectEntry_ModeChange *) entry);
            break;
        case BHV_BONUS:
            obj_init_bonus(obj, (LevelObjectEntry_Bonus *) entry);
            break;
        case BHV_DOOR:
            obj_init_door(obj, (LevelObjectEntry_Door *) entry);
            break;
        case BHV_TT_DOOR:
            obj_init_ttdoor(obj, (LevelObjectEntry_TTDoor *) entry);
            break;
        case BHV_FOG_CHANGER:
            obj_init_fogchanger(obj, (LevelObjectEntry_FogChanger *) entry);
            break;
        case BHV_AINODE:
            obj_init_ainode(obj, (LevelObjectEntry_AiNode *) entry);
            break;
        case BHV_WEAPON_BALLOON:
            obj_init_weaponballoon(obj, (LevelObjectEntry_WeaponBalloon *) entry);
            break;
        case BHV_BALLOON_POP:
            obj_init_wballoonpop(obj, (LevelObjectEntry_WBalloonPop *) entry);
            break;
        case BHV_WEAPON:
        case BHV_WEAPON_2:
            obj_init_weapon(obj, (LevelObjectEntry_Weapon *) entry);
            break;
        case BHV_SKY_CONTROL:
            obj_init_skycontrol(obj, (LevelObjectEntry_SkyControl *) entry);
            break;
        case BHV_TORCH_MIST:
            obj_init_torch_mist(obj, (LevelObjectEntry_Torch_Mist *) entry);
            break;
        case BHV_TEXTURE_SCROLL:
            obj_init_texscroll(obj, (LevelObjectEntry_TexScroll *) entry, param);
            break;
        case BHV_STOPWATCH_MAN:
            obj_init_stopwatchman(obj, (LevelObjectEntry_StopWatchMan *) entry);
            break;
        case BHV_BANANA:
            obj_init_banana(obj, (LevelObjectEntry_Banana *) entry);
            break;
        case BHV_LIGHT_RGBA:
            obj_init_rgbalight(obj, (LevelObjectEntry_RgbaLight *) entry, param);
            break;
        case BHV_BUOY_PIRATE_SHIP:
            obj_init_buoy_pirateship(obj, (LevelObjectEntry_Buoy_PirateShip *) entry, param);
            break;
        case BHV_LOG:
            obj_init_log(obj, (LevelObjectEntry_Log *) entry, param);
            break;
        case BHV_WEATHER:
            obj_init_weather(obj, (LevelObjectEntry_Weather *) entry);
            break;
        case BHV_BRIDGE_WHALE_RAMP:
            obj_init_bridge_whaleramp(obj, (LevelObjectEntry_Bridge_WhaleRamp *) entry);
            break;
        case BHV_RAMP_SWITCH:
            obj_init_rampswitch(obj, (LevelObjectEntry_RampSwitch *) entry);
            break;
        case BHV_SEA_MONSTER:
            obj_init_seamonster(obj, (LevelObjectEntry_SeaMonster *) entry);
            break;
        case BHV_LENS_FLARE:
            obj_init_lensflare(obj, (LevelObjectEntry_LensFlare *) entry);
            break;
        case BHV_LENS_FLARE_SWITCH:
            obj_init_lensflareswitch(obj, (LevelObjectEntry_LensFlareSwitch *) entry, param);
            break;
        case BHV_COLLECT_EGG:
            obj_init_collectegg(obj, (LevelObjectEntry_CollectEgg *) entry);
            break;
        case BHV_EGG_CREATOR:
            obj_init_eggcreator(obj, (LevelObjectEntry_EggCreator *) entry);
            break;
        case BHV_CHARACTER_FLAG:
            obj_init_characterflag(obj, (LevelObjectEntry_CharacterFlag *) entry);
            break;
        case BHV_ANIMATION:
            obj_init_animation(obj, (LevelObjectEntry_Animation *) entry, param);
            break;
        case BHV_INFO_POINT:
            obj_init_infopoint(obj, (LevelObjectEntry_InfoPoint *) entry);
            break;
        case BHV_TRIGGER:
            obj_init_trigger(obj, (LevelObjectEntry_Trigger *) entry);
            break;
        case BHV_ZIPPER_WATER:
        case BHV_ZIPPER_AIR:
            obj_init_airzippers_waterzippers(obj, (LevelObjectEntry_AirZippers_WaterZippers *) entry);
            break;
        case BHV_TIMETRIAL_GHOST:
            obj_init_timetrialghost(obj, (LevelObjectEntry_TimeTrial_Ghost *) entry);
            break;
        case BHV_WAVE_GENERATOR:
            obj_init_wavegenerator(obj, (LevelObjectEntry_WaveGenerator *) entry, param);
            break;
        case BHV_BUTTERFLY:
            obj_init_butterfly(obj, (LevelObjectEntry_Butterfly *) entry, param);
            break;
        case BHV_PARK_WARDEN:
            obj_init_parkwarden(obj, (LevelObjectEntry_Parkwarden *) entry);
            break;
        case BHV_WORLD_KEY:
            obj_init_worldkey(obj, (LevelObjectEntry_WorldKey *) entry);
            break;
        case BHV_BANANA_SPAWNER:
            obj_init_bananacreator(obj, (LevelObjectEntry_BananaCreator *) entry);
            break;
        case BHV_TREASURE_SUCKER:
            obj_init_treasuresucker(obj, (LevelObjectEntry_TreasureSucker *) entry);
            break;
        case BHV_LAVA_SPURT:
            obj_init_lavaspurt(obj, (LevelObjectEntry_LavaSpurt *) entry);
            break;
        case BHV_POS_ARROW:
            obj_init_posarrow(obj, (LevelObjectEntry_PosArrow *) entry);
            break;
        case BHV_HIT_TESTER:
        case BHV_HIT_TESTER_3:
            obj_init_hittester(obj, (LevelObjectEntry_HitTester *) entry);
            break;
        case BHV_HIT_TESTER_2:
        case BHV_DYNAMIC_LIGHT_OBJECT_2:
        case BHV_HIT_TESTER_4:
            obj_init_dynamic_lighting_object(obj, (LevelObjectEntry_DynamicLightingObject *) entry);
            break;
        case BHV_SNOWBALL:
        case BHV_SNOWBALL_3:
            obj_init_unknown96(obj, (LevelObjectEntry_Unknown96 *) entry);
            break;
        case BHV_SNOWBALL_2:
        case BHV_SNOWBALL_4:
            obj_init_snowball(obj, (LevelObjectEntry_Snowball *) entry);
            break;
        case BHV_MIDI_FADE:
            obj_init_midifade(obj, (LevelObjectEntry_MidiFade *) entry);
            break;
        case BHV_MIDI_FADE_POINT:
            obj_init_midifadepoint(obj, (LevelObjectEntry_MidiFadePoint *) entry);
            break;
        case BHV_MIDI_CHANNEL_SET:
            obj_init_midichset(obj, (LevelObjectEntry_Midichset *) entry);
            break;
        case BHV_EFFECT_BOX:
            obj_init_effectbox(obj, (LevelObjectEntry_EffectBox *) entry);
            break;
        case BHV_TROPHY_CABINET:
            obj_init_trophycab(obj, (LevelObjectEntry_TrophyCab *) entry);
            break;
        case BHV_BUBBLER:
            obj_init_bubbler(obj, (LevelObjectEntry_Bubbler *) entry);
            break;
        case BHV_FLY_COIN:
            obj_init_flycoin(obj, (LevelObjectEntry_FlyCoin *) entry);
            break;
        case BHV_GOLDEN_BALLOON:
            obj_init_goldenballoon(obj, (LevelObjectEntry_GoldenBalloon *) entry);
            break;
        case BHV_LASER_BOLT:
            obj_init_laserbolt(obj, (LevelObjectEntry_Laserbolt *) entry);
            break;
        case BHV_LASER_GUN:
            obj_init_lasergun(obj, (LevelObjectEntry_Lasergun *) entry);
            break;
        case BHV_ZIPPER_GROUND:
            obj_init_groundzipper(obj, (LevelObjectEntry_GroundZipper *) entry);
            break;
        case BHV_OVERRIDE_POS:
            obj_init_overridepos(obj, (LevelObjectEntry_OverridePos *) entry);
            break;
        case BHV_WIZPIG_SHIP:
            obj_init_wizpigship(obj, (LevelObjectEntry_WizpigShip *) entry);
            break;
        case BHV_BOOST:
            obj_init_boost(obj, (LevelObjectEntry_Boost2 *) entry);
            break;
        case BHV_SILVER_COIN:
            obj_init_silvercoin(obj, (LevelObjectEntry_SilverCoin *) entry);
            break;
        case BHV_WARDEN_SMOKE:
            obj_init_wardensmoke(obj, (LevelObjectEntry_WardenSmoke *) entry);
            break;
        case BHV_UNK_5E:
            obj_init_unknown94(obj, (LevelObjectEntry_Unknown94 *) entry, param);
            break;
        case BHV_TELEPORT:
            obj_init_teleport(obj, (LevelObjectEntry_Teleport *) entry);
            break;
        case BHV_ROCKET_SIGNPOST:
        case BHV_ROCKET_SIGNPOST_2:
            obj_init_lighthouse_rocketsignpost(obj, (LevelObjectEntry_Lighthouse_RocketSignpost *) entry);
            break;
        case BHV_RANGE_TRIGGER:
            obj_init_rangetrigger(obj, (LevelObjectEntry_RangeTrigger *) entry);
            break;
        case BHV_FIREBALL_OCTOWEAPON:
        case BHV_FIREBALL_OCTOWEAPON_2:
            obj_init_fireball_octoweapon(obj, (LevelObjectEntry_Fireball_Octoweapon *) entry);
            break;
        case BHV_FROG:
            obj_init_frog(obj, (LevelObjectEntry_Frog *) entry);
            break;
        case BHV_SILVER_COIN_2:
            obj_init_silvercoin_adv2(obj, (LevelObjectEntry_SilverCoinAdv2 *) entry);
            break;
        case BHV_LEVEL_NAME:
            obj_init_levelname(obj, (LevelObjectEntry_LevelName *) entry);
            break;
    }
}

/**
 * Set initialisation property flags based off object ID.
 * This includes things like shadow data, interaction and visuals.
 */
s32 obj_init_property_flags(s32 behaviorId) {
    s32 flags = OBJECT_BEHAVIOUR_NONE;
    switch (behaviorId) {
        case BHV_RACER:
            flags = OBJECT_BEHAVIOUR_SHADED | OBJECT_BEHAVIOUR_SHADOW | OBJECT_BEHAVIOUR_WATER_EFFECT |
                    OBJECT_BEHAVIOUR_ANIMATION | OBJECT_BEHAVIOUR_INTERACTIVE;
            break;
        case BHV_SCENERY:
            flags = OBJECT_BEHAVIOUR_SHADED | OBJECT_BEHAVIOUR_SHADOW | OBJECT_BEHAVIOUR_INTERACTIVE;
            break;
        case BHV_WEAPON:
            flags = OBJECT_BEHAVIOUR_SHADOW | OBJECT_BEHAVIOUR_WATER_EFFECT | OBJECT_BEHAVIOUR_INTERACTIVE;
            break;
        case BHV_DINO_WHALE:
            flags = OBJECT_BEHAVIOUR_SHADED | OBJECT_BEHAVIOUR_SHADOW | OBJECT_BEHAVIOUR_ANIMATION |
                    OBJECT_BEHAVIOUR_INTERACTIVE;
            break;
        case BHV_DOOR:
        case BHV_TT_DOOR:
            flags = OBJECT_BEHAVIOUR_INTERACTIVE | OBJECT_BEHAVIOUR_COLLIDABLE;
            break;
        case BHV_WEAPON_BALLOON:
        case BHV_GOLDEN_BALLOON:
            flags = OBJECT_BEHAVIOUR_SHADOW | OBJECT_BEHAVIOUR_INTERACTIVE;
            break;
        case BHV_HIT_TESTER:
        case BHV_HIT_TESTER_2:
        case BHV_SNOWBALL:
        case BHV_SNOWBALL_2:
            flags = OBJECT_BEHAVIOUR_SHADED | OBJECT_BEHAVIOUR_SHADOW | OBJECT_BEHAVIOUR_ANIMATION |
                    OBJECT_BEHAVIOUR_INTERACTIVE | OBJECT_BEHAVIOUR_COLLIDABLE;
            break;
        case BHV_SNOWBALL_3:
        case BHV_SNOWBALL_4:
        case BHV_HIT_TESTER_3:
        case BHV_HIT_TESTER_4:
            flags = OBJECT_BEHAVIOUR_SHADOW | OBJECT_BEHAVIOUR_ANIMATION | OBJECT_BEHAVIOUR_INTERACTIVE |
                    OBJECT_BEHAVIOUR_COLLIDABLE;
            break;
        case BHV_UNK_18:
            flags = OBJECT_BEHAVIOUR_WATER_EFFECT;
            break;
        case BHV_STOPWATCH_MAN:
            flags = OBJECT_BEHAVIOUR_SHADED | OBJECT_BEHAVIOUR_SHADOW | OBJECT_BEHAVIOUR_ANIMATION |
                    OBJECT_BEHAVIOUR_INTERACTIVE;
            break;
        case BHV_BANANA:
        case BHV_WORLD_KEY:
        case BHV_SILVER_COIN:
        case BHV_SILVER_COIN_2:
            flags = OBJECT_BEHAVIOUR_INTERACTIVE | OBJECT_BEHAVIOUR_SHADOW;
            break;
        case BHV_LOG:
            flags = OBJECT_BEHAVIOUR_INTERACTIVE | OBJECT_BEHAVIOUR_COLLIDABLE;
            break;
        case BHV_BRIDGE_WHALE_RAMP:
            flags = OBJECT_BEHAVIOUR_SHADED | OBJECT_BEHAVIOUR_ANIMATION | OBJECT_BEHAVIOUR_INTERACTIVE |
                    OBJECT_BEHAVIOUR_COLLIDABLE;
            break;
        case BHV_RAMP_SWITCH:
            flags = OBJECT_BEHAVIOUR_INTERACTIVE | OBJECT_BEHAVIOUR_SHADOW;
            break;
        case BHV_SEA_MONSTER:
            flags = OBJECT_BEHAVIOUR_SHADED | OBJECT_BEHAVIOUR_ANIMATION;
            break;
        case BHV_COLLECT_EGG:
            flags = OBJECT_BEHAVIOUR_SHADOW | OBJECT_BEHAVIOUR_INTERACTIVE;
            break;
        case BHV_UNK_30:
            flags = OBJECT_BEHAVIOUR_SHADED | OBJECT_BEHAVIOUR_ANIMATION;
            break;
        case BHV_UNK_3F:
            flags = OBJECT_BEHAVIOUR_SHADED | OBJECT_BEHAVIOUR_ANIMATION;
            break;
        case BHV_ANIMATED_OBJECT:
        case BHV_VEHICLE_ANIMATION:
        case BHV_PARK_WARDEN_2:
        case BHV_WIZPIG_SHIP:
        case BHV_ANIMATED_OBJECT_4:
        case BHV_PIG_ROCKETEER:
            flags = OBJECT_BEHAVIOUR_SHADED | OBJECT_BEHAVIOUR_SHADOW | OBJECT_BEHAVIOUR_ANIMATION;
            break;
        case BHV_CHARACTER_SELECT:
            flags = OBJECT_BEHAVIOUR_SHADED | OBJECT_BEHAVIOUR_SHADOW | OBJECT_BEHAVIOUR_ANIMATION;
            break;
        case BHV_TROPHY_CABINET:
        case BHV_DYNAMIC_LIGHT_OBJECT_2:
        case BHV_ROCKET_SIGNPOST:
        case BHV_ROCKET_SIGNPOST_2:
            flags = OBJECT_BEHAVIOUR_SHADED | OBJECT_BEHAVIOUR_INTERACTIVE | OBJECT_BEHAVIOUR_COLLIDABLE;
            break;
        case BHV_UNK_5B:
            flags = OBJECT_BEHAVIOUR_SHADED;
            break;
        case BHV_ANIMATED_OBJECT_2:
            flags = OBJECT_BEHAVIOUR_SHADOW | OBJECT_BEHAVIOUR_ANIMATION;
            break;
        case BHV_EXIT:
        case BHV_CHECKPOINT:
        case BHV_WEAPON_2:
        case BHV_SKY_CONTROL:
        case BHV_MODECHANGE:
        case BHV_BUOY_PIRATE_SHIP:
        case BHV_BONUS:
        case BHV_INFO_POINT:
        case BHV_TRIGGER:
        case BHV_ZIPPER_WATER:
        case BHV_LAVA_SPURT:
        case BHV_LASER_BOLT:
        case BHV_LASER_GUN:
        case BHV_ZIPPER_AIR:
        case BHV_TELEPORT:
        case BHV_FIREBALL_OCTOWEAPON:
        case BHV_FIREBALL_OCTOWEAPON_2:
            flags = OBJECT_BEHAVIOUR_INTERACTIVE;
            break;
        case BHV_ZIPPER_GROUND:
            flags = OBJECT_BEHAVIOUR_SHADOW | OBJECT_BEHAVIOUR_INTERACTIVE;
            break;
        case BHV_ANIMATION:
        case BHV_CAMERA_ANIMATION:
        case BHV_BUTTERFLY:
            flags = OBJECT_BEHAVIOUR_SHADOW;
            break;
        case BHV_PARK_WARDEN:
            flags = OBJECT_BEHAVIOUR_SHADED | OBJECT_BEHAVIOUR_SHADOW | OBJECT_BEHAVIOUR_ANIMATION |
                    OBJECT_BEHAVIOUR_INTERACTIVE;
            break;
        case BHV_FROG:
            flags = OBJECT_BEHAVIOUR_SHADED | OBJECT_BEHAVIOUR_SHADOW | OBJECT_BEHAVIOUR_ANIMATION;
            break;
        case BHV_UNK_72:
            flags = OBJECT_BEHAVIOUR_SHADED;
            break;
    }
    return flags;
}

/**
 * Run every frame for most objects with set behaviours.
 * One big switch statement for whichever object.
 */
void run_object_loop_func(Object *obj, s32 updateRate) {
    update_object_stack_trace(OBJECT_UPDATE, obj->objectID);
    switch (obj->behaviorId) {
        case BHV_SCENERY:
            obj_loop_scenery(obj, updateRate);
            break;
        case BHV_FISH:
            obj_loop_fish(obj, updateRate);
            break;
        case BHV_ANIMATOR:
            obj_loop_animator(obj, updateRate);
            break;
        case BHV_SMOKE:
            obj_loop_smoke(obj, updateRate);
            break;
        case BHV_UNK_19:
            obj_loop_unknown25(obj, updateRate);
            break;
        case BHV_BOMB_EXPLOSION:
            obj_loop_bombexplosion(obj, updateRate);
            break;
        case BHV_EXIT:
            obj_loop_exit(obj, updateRate);
            break;
        case BHV_CAMERA_CONTROL:
            obj_loop_cameracontrol(obj, updateRate);
            break;
        case BHV_SETUP_POINT:
            obj_loop_setuppoint(obj, updateRate);
            break;
        case BHV_DINO_WHALE:
            obj_loop_dino_whale(obj, updateRate);
            break;
        case BHV_CHECKPOINT:
            obj_loop_checkpoint(obj, updateRate);
            break;
        case BHV_MODECHANGE:
            obj_loop_modechange(obj, updateRate);
            break;
        case BHV_BONUS:
            obj_loop_bonus(obj, updateRate);
            break;
        case BHV_DOOR:
            obj_loop_door(obj, updateRate);
            break;
        case BHV_FOG_CHANGER:
            obj_loop_fogchanger(obj);
            break;
        case BHV_AINODE:
            obj_loop_ainode(obj, updateRate);
            break;
        case BHV_WEAPON_BALLOON:
            obj_loop_weaponballoon(obj, updateRate);
            break;
        case BHV_BALLOON_POP:
            obj_loop_wballoonpop(obj, updateRate);
            break;
        case BHV_WEAPON:
        case BHV_WEAPON_2:
            obj_loop_weapon(obj, updateRate);
            break;
        case BHV_SKY_CONTROL:
            obj_loop_skycontrol(obj, updateRate);
            break;
        case BHV_TORCH_MIST:
            obj_loop_torch_mist(obj, updateRate);
            break;
        case BHV_TEXTURE_SCROLL:
            obj_loop_texscroll(obj, updateRate);
            break;
        case BHV_STOPWATCH_MAN:
            obj_loop_stopwatchman(obj, updateRate);
            break;
        case BHV_BANANA:
            obj_loop_banana(obj, updateRate);
            break;
        case BHV_BUOY_PIRATE_SHIP:
            obj_loop_buoy_pirateship(obj, updateRate);
            break;
        case BHV_LOG:
            obj_loop_log(obj, updateRate);
            break;
        case BHV_WEATHER:
            obj_loop_weather(obj, updateRate);
            break;
        case BHV_BRIDGE_WHALE_RAMP:
            obj_loop_bridge_whaleramp(obj, updateRate);
            break;
        case BHV_RAMP_SWITCH:
            obj_loop_rampswitch(obj, updateRate);
            break;
        case BHV_SEA_MONSTER:
            obj_loop_seamonster(obj, updateRate);
            break;
        case BHV_COLLECT_EGG:
            obj_loop_collectegg(obj, updateRate);
            break;
        case BHV_EGG_CREATOR:
            obj_loop_eggcreator(obj, updateRate);
            break;
        case BHV_CHARACTER_FLAG:
            obj_loop_characterflag(obj, updateRate);
            break;
        case BHV_ANIMATED_OBJECT:
        case BHV_ANIMATED_OBJECT_2:
        case BHV_ANIMATED_OBJECT_3:
        case BHV_ANIMATED_OBJECT_4:
            obj_loop_animobject(obj, updateRate);
            break;
        case BHV_WIZPIG_GHOSTS:
            obj_loop_wizghosts(obj, updateRate);
            break;
        case BHV_CAMERA_ANIMATION:
            obj_loop_animcamera(obj, updateRate);
            break;
        case BHV_INFO_POINT:
            obj_loop_infopoint(obj, updateRate);
            break;
        case BHV_CAR_ANIMATION:
            obj_loop_animcar(obj, updateRate);
            break;
        case BHV_CHARACTER_SELECT:
            obj_loop_char_select(obj, updateRate);
            break;
        case BHV_TRIGGER:
            obj_loop_trigger(obj, updateRate);
            break;
        case BHV_VEHICLE_ANIMATION:
            obj_loop_vehicleanim(obj, updateRate);
            break;
        case BHV_ZIPPER_WATER:
        case BHV_ZIPPER_AIR:
            obj_loop_airzippers_waterzippers(obj, updateRate);
            break;
        case BHV_TIMETRIAL_GHOST:
            obj_loop_timetrialghost(obj, updateRate);
            break;
        case BHV_WAVE_POWER:
            obj_loop_wavepower(obj);
            break;
        case BHV_BUTTERFLY:
            obj_loop_butterfly(obj, updateRate);
            break;
        case BHV_PARK_WARDEN:
            obj_loop_parkwarden(obj, updateRate);
            break;
        case BHV_WORLD_KEY:
            obj_loop_worldkey(obj, updateRate);
            break;
        case BHV_BANANA_SPAWNER:
            obj_loop_bananacreator(obj, updateRate);
            break;
        case BHV_TREASURE_SUCKER:
            obj_loop_treasuresucker(obj, updateRate);
            break;
        case BHV_LAVA_SPURT:
            obj_loop_lavaspurt(obj, updateRate);
            break;
        case BHV_POS_ARROW:
            obj_loop_posarrow(obj, updateRate);
            break;
        case BHV_HIT_TESTER:
        case BHV_HIT_TESTER_2:
        case BHV_HIT_TESTER_3:
        case BHV_HIT_TESTER_4:
            obj_loop_hittester(obj, updateRate);
            break;
        case BHV_SNOWBALL:
        case BHV_SNOWBALL_2:
        case BHV_SNOWBALL_3:
        case BHV_SNOWBALL_4:
            obj_loop_snowball(obj, updateRate);
            break;
        case BHV_EFFECT_BOX:
            obj_loop_effectbox(obj, updateRate);
            break;
        case BHV_TROPHY_CABINET:
            obj_loop_trophycab(obj, updateRate);
            break;
        case BHV_BUBBLER:
            obj_loop_bubbler(obj, updateRate);
            break;
        case BHV_FLY_COIN:
            obj_loop_flycoin(obj, updateRate);
            break;
        case BHV_GOLDEN_BALLOON:
            obj_loop_goldenballoon(obj, updateRate);
            break;
        case BHV_LASER_BOLT:
            obj_loop_laserbolt(obj, updateRate);
            break;
        case BHV_LASER_GUN:
            obj_loop_lasergun(obj, updateRate);
            break;
        case BHV_PARK_WARDEN_2:
            obj_loop_gbparkwarden(obj, updateRate);
            break;
        case BHV_ZIPPER_GROUND:
            obj_loop_groundzipper(obj, updateRate);
            break;
        case BHV_WIZPIG_SHIP:
            obj_loop_wizpigship(obj, updateRate);
            break;
        case BHV_SILVER_COIN:
        case BHV_SILVER_COIN_2:
            obj_loop_silvercoin(obj, updateRate);
            break;
        case BHV_WARDEN_SMOKE:
            obj_loop_wardensmoke(obj, updateRate);
            break;
        case BHV_UNK_5E:
            obj_loop_unknown94(obj, updateRate);
            break;
        case BHV_TELEPORT:
            obj_loop_teleport(obj, updateRate);
            break;
        case BHV_RANGE_TRIGGER:
            obj_loop_rangetrigger(obj, updateRate);
            break;
        case BHV_ROCKET_SIGNPOST_2:
            obj_loop_rocketsignpost(obj, updateRate);
            break;
        case BHV_FIREBALL_OCTOWEAPON:
        case BHV_FIREBALL_OCTOWEAPON_2:
            obj_loop_fireball_octoweapon(obj, updateRate);
            break;
        case BHV_FROG:
            obj_loop_frog(obj, updateRate);
            break;
        case BHV_TT_DOOR:
            obj_loop_ttdoor(obj, updateRate);
            break;
        case BHV_DOOR_OPENER:
            obj_loop_dooropener(obj, updateRate);
            break;
        case BHV_PIG_ROCKETEER:
            obj_loop_pigrocketeer(obj, updateRate);
            break;
        case BHV_LEVEL_NAME:
            obj_loop_levelname(obj, updateRate);
            break;
    }
    update_object_stack_trace(OBJECT_UPDATE, OBJECT_CLEAR);
}

UNUSED void func_8002458C(UNUSED s32 arg0) {
}

s16 *func_80024594(s32 *currentCount, s32 *maxCount) {
    *currentCount = D_800DC700;
    *maxCount = ARRAY_COUNT(D_8011AC20);
    return D_8011AC20;
}

void func_800245B4(s16 arg0) {
    D_8011AC20[D_800DC700++] = arg0;
    if (D_800DC700 >= ARRAY_COUNT(D_8011AC20)) {
        D_800DC700 = 0;
    }
}

UNUSED const char sReadOutErrorString[] = "RO error %d!!\n";
UNUSED const char sPureAnguishString[] = "ARGHHHHHHHHH\n";
