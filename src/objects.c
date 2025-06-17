#include "objects.h"
#include "memory.h"

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "level_object_entries.h"
#include "asset_enums.h"
#include "asset_loading.h"
#include "thread0_epc.h"
#include "save_data.h"
#include "menu.h"
#include "game.h"
#include "racer.h"
#include "particles.h"
#include "tracks.h"
#include "math_util.h"
#include "camera.h"
#include "waves.h"
#include "object_functions.h"
#include "object_models.h"
#include "lights.h"
#include "game_ui.h"
#include "audio_spatial.h"
#include "joypad.h"
#include "game_text.h"
#include "audiosfx.h"
#include "audio_vehicle.h"
#include "vehicle_misc.h"
#include "PRinternal/viint.h"
#include "printf.h"
#include "weather.h"
#include "PRinternal/piint.h"

#define MAX_CHECKPOINTS 60
#define OBJECT_POOL_SIZE 0x15800
#define OBJECT_SPAWN_HEAP_SIZE 0x800
#define OBJECT_SLOT_COUNT 512
#define AINODE_COUNT 128
#define CAMCONTROL_COUNT 20
#define BOOST_VERT_COUNT 9
#define BOOST_TRI_COUNT 8

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
s8 D_800DC71C = 0;
s32 gObjectTexAnim = FALSE;
s16 gTimeTrialTime = 10800;
s16 gTimeTrialVehicle = -1;
s16 gTimeTrialCharacter = 0;
u8 gHasGhostToSave = FALSE;
u8 gTimeTrialStaffGhost = FALSE;
u8 gBeatStaffGhost = FALSE;
s8 D_800DC73C = 0;
s8 D_800DC740 = 0;
s8 gSwapLeadPlayer = FALSE;
s8 D_800DC748 = FALSE;
Vertex *gBoostVerts[2] = { 0, 0 };
Triangle *gBoostTris[2] = { 0, 0 };
Object *gShieldEffectObject = NULL;
s32 gBoostObjOverrideID = 9;
Object *gMagnetEffectObject = NULL;

f32 D_800DC768[16] = { 0.0f, 1.0f,  0.70711f,  0.70711f,  1.0f,  0.0f, 0.70711f,  -0.70711f,
                       0.0f, -1.0f, -0.70711f, -0.70711f, -1.0f, 0.0f, -0.70711f, 0.70711f };

u16 D_800DC7A8[] = {
    // Car
    ASSET_OBJECT_ID_KREMCAR,  ASSET_OBJECT_ID_BADGERCAR, ASSET_OBJECT_ID_TORTCAR,    ASSET_OBJECT_ID_CONKACAR,
    ASSET_OBJECT_ID_TIGERCAR, ASSET_OBJECT_ID_BANJOCAR,  ASSET_OBJECT_ID_CHICKENCAR, ASSET_OBJECT_ID_MOUSECAR,
};

s16 D_800DC7B8[] = {
    // TODO: move these first two entries to the first var above. I'm thinking this is either all one big var, or the
    // boss objects have their own table.
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
UNUSED const char sObjectListDataOverflowString[] = "ObjList (Part) Overflow %d!!!\n";
UNUSED const char sObjectSetupError1String[] = "ObjSetupObject(1) Memory fail!!\n";
UNUSED const char sObjectSetupError2String[] = "ObjSetupObject(2) Memory fail!!\n";
UNUSED const char sObjectSetupError5String[] = "ObjSetupObject(5) Memory fail!!\n";
UNUSED const char sObjectSetupError6String[] = "ObjSetupObject(6) Memory fail!!\n";
UNUSED const char sObjectSetupError3String[] = "ObjSetupObject(3) Memory fail!!\n";
UNUSED const char sObjectListOverflowString[] = "ObjList Overflow %d!!!\n";
UNUSED const char sObjectSetupError4String[] = "ObjSetupObject(4) Memory fail!!\n";
UNUSED const char sDuplicateCheckpointString[] = "Error: Multiple checkpoint no: %d !!\n";
UNUSED const char sErrorChannelString[] = "ERROR Channel %d\n";
UNUSED const char sReadOutErrorString[] = "RO error %d!!\n";
UNUSED const char sPureAnguishString[] = "ARGHHHHHHHHH\n";

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
Object *(*gSpawnObjectHeap)[sizeof(Object)];
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
s32 D_8011ADB4;
s32 gEventStartTimer;
s32 D_8011ADBC;
s32 D_8011ADC0;
s8 gFirstTimeFinish;
s8 D_8011ADC5;
u32 gBalloonCutsceneTimer;
s8 (*D_8011ADCC)[8];
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
Object **D_8011AE6C;
s32 D_8011AE70;
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
u8 *D_8011AE98[2];
s32 D_8011AEA0[2];
s32 D_8011AEA8[2];
s32 *D_8011AEB0[2];
s16 *gAssetsLvlObjTranslationTable;
s32 gAssetsLvlObjTranslationTableLength;
s32 D_8011AEC0;
Object **gParticlePtrList;
s32 gFreeListCount;
CheckpointNode *gTrackCheckpoints; // Array of structs, unknown number of members
s32 gNumberOfCheckpoints;
s32 D_8011AED4;
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
Object_MidiFade *D_8011AF60[2];
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

typedef struct LevelObjectEntry_unk8000B020 {
    LevelObjectEntryCommon common;
    s8 unk8;
    s8 unk9;
} LevelObjectEntry_unk8000B020;

/**
 * Spawns control objects for racer boost visuals, as well as shield and magnet visuals.
 * Boost geometry is made in real time, and allocated here.
 * This function is called on every level load, but only racers use the stuff here.
 */
void racerfx_alloc(s32 numberOfVertices, s32 numberOfTriangles) {
    Object_Boost *boostObj;
    LevelObjectEntry_unk8000B020 objEntry;
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
        objEntry.common.size = sizeof(LevelObjectEntry_unk8000B020);
        objEntry.common.x = 0;
        objEntry.common.y = 0;
        objEntry.common.z = 0;
        objEntry.unk8 = i;
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
    objEntry.common.size = sizeof(LevelObjectEntry_unk8000B020);
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
    objEntry.common.size = sizeof(LevelObjectEntry_unk8000B020) + 0x80; // Not sure where this 0x80 comes from.
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
                gBoostEffectObjects[racerIndex]->segment.trans.x_position = 0.0f;
                gBoostEffectObjects[racerIndex]->segment.trans.y_position = 0.0f;
                gBoostEffectObjects[racerIndex]->segment.trans.z_position = 0.0f;
                sp74.x = boostData->position.x;
                sp74.y = boostData->position.y;
                sp74.z = boostData->position.z;
                vec3f_rotate(&racerObj->segment.trans.rotation, &sp74);
                ignore_bounds_check();
                move_object(gBoostEffectObjects[racerIndex], racerObj->segment.trans.x_position + sp74.f[0],
                            racerObj->segment.trans.y_position + sp74.f[1],
                            racerObj->segment.trans.z_position + sp74.f[2]);
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
        racer = &(*gRacers)[i]->unk64->racer;
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
                    boostObj->unk74 = (f32) (4.8f - boostObj->unk74);
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
    D_8011AE6C = mempool_alloc_safe(sizeof(uintptr_t) * 20, COLOUR_TAG_BLUE);
    D_8011AE74 = mempool_alloc_safe(sizeof(uintptr_t) * 128, COLOUR_TAG_BLUE);
    gTrackCheckpoints = mempool_alloc_safe(sizeof(CheckpointNode) * MAX_CHECKPOINTS, COLOUR_TAG_BLUE);
    gCameraObjList = mempool_alloc_safe(sizeof(uintptr_t *) * CAMCONTROL_COUNT, COLOUR_TAG_BLUE);
    gRacers = mempool_alloc_safe(sizeof(uintptr_t) * 10, COLOUR_TAG_BLUE);
    gRacersByPort = mempool_alloc_safe(sizeof(uintptr_t) * 10, COLOUR_TAG_BLUE);
    gRacersByPosition = mempool_alloc_safe(sizeof(uintptr_t) * 10, COLOUR_TAG_BLUE);
    gAINodes = mempool_alloc_safe(sizeof(uintptr_t) * AINODE_COUNT, COLOUR_TAG_BLUE);
    D_8011ADCC = mempool_alloc_safe(8, COLOUR_TAG_BLUE);
    D_8011AFF4 = mempool_alloc_safe(sizeof(unk800179D0) * 16, COLOUR_TAG_BLUE);
    gAssetsLvlObjTranslationTable = (s16 *) load_asset_section_from_rom(ASSET_LEVEL_OBJECT_TRANSLATION_TABLE);
    gAssetsLvlObjTranslationTableLength = (get_size_of_asset_section(ASSET_LEVEL_OBJECT_TRANSLATION_TABLE) >> 1) - 1;
    while (gAssetsLvlObjTranslationTable[gAssetsLvlObjTranslationTableLength] == 0) {
        gAssetsLvlObjTranslationTableLength--;
    }
    gSpawnObjectHeap = mempool_alloc_safe(sizeof(uintptr_t) * 512, COLOUR_TAG_BLUE);
    gAssetsObjectHeadersTable = (s32 *) load_asset_section_from_rom(ASSET_OBJECT_HEADERS_TABLE);
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

    gAssetsMiscSection = (s32 *) load_asset_section_from_rom(ASSET_MISC);
    gAssetsMiscTable = (s32 *) load_asset_section_from_rom(ASSET_MISC_TABLE);
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
    D_8011AE70 = 0;
    gNumberOfCheckpoints = 0;
    D_8011AED4 = 0;
    gNumRacers = 0;
    D_8011AE78 = 0;
    D_8011AD21 = 0;
    D_8011AD22[0] = 0;
    D_8011AD22[1] = 0;

    for (i = 0; i < AINODE_COUNT; i++) {
        (*gAINodes)[i] = NULL;
    }
    for (i = 0; i < 8; i++) {
        (*D_8011ADCC)[i] = 0;
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
    D_8011AF60[0] = 0;
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
    D_800DC748 = FALSE;
    if (D_800DC71C) {
        rumble_init(TRUE);
    }
    D_800DC71C = 0;
    if (gSwapLeadPlayer && is_in_two_player_adventure()) {
        gSwapLeadPlayer = FALSE;
        swap_lead_player();
    }
    gParticlePtrList_flush();
    len = gObjectCount;
    for (i = 0; i < len; i++) {
        func_800101AC(gObjPtrList[i], 1);
    }
    gFreeListCount = 0;
    gObjectCount = 0;
    gObjectListStart = 0;
    clear_object_pointers();
    mempool_free((void *) D_8011AEB0[0]);
    mempool_free((void *) D_8011AEB0[1]);
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
        load_asset_to_address(ASSET_OBJECTS, (u32) address, assetOffset, size);
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

void func_8000C8F8(s32 arg0, s32 arg1) {
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
    gIsSilverCoinRace =
        ((settings->courseFlagsPtr[settings->courseId] & 4) == 0) && (((1 << settings->worldId) & assetOffset) != 0);

    if (!(settings->courseFlagsPtr[settings->courseId] & 2)) {
        gIsSilverCoinRace = 0;
    }
    if (is_in_tracks_mode()) {
        gIsSilverCoinRace = 0;
    }
    if (get_current_level_race_type()) {
        gIsSilverCoinRace = 0;
    }

    D_8011AD3E = 0;
    mem = mempool_alloc_safe(0x3000, COLOUR_TAG_BLUE);
    D_8011AEB0[arg1] = mem;
    D_8011AE98[arg1] = (u8 *) (D_8011AEB0[arg1] + 4);
    D_8011AEA0[arg1] = 0;
    D_8011AEA8[arg1] = arg0;
    objMapTable = (u32 *) load_asset_section_from_rom(ASSET_LEVEL_OBJECT_MAPS_TABLE);
    for (i = 0; objMapTable[i] != 0xFFFFFFFF; i++) {}
    i--;
    if (arg0 >= i) {
        arg0 = 0;
    }
    assetOffset = objMapTable[arg0];
    assetSize = objMapTable[arg0 + 1] - assetOffset;

    if (assetSize != 0) {
        compressedAsset = (u8 *) mem;
        compressedAsset =
            ((compressedAsset + get_asset_uncompressed_size(ASSET_LEVEL_OBJECT_MAPS, assetOffset)) - (0, assetSize)) +
            0x20;
        load_asset_to_address(ASSET_LEVEL_OBJECT_MAPS, (u32) compressedAsset, assetOffset, assetSize);
        gzip_inflate(compressedAsset, (u8 *) mem);
        mempool_free(objMapTable);
        D_8011AE98[arg1] = (u8 *) (D_8011AEB0[arg1] + 4);
        D_8011AEA0[arg1] = *mem;
        D_8011AEC0 = arg1;
        for (var_s0 = 0; var_s0 < D_8011AEA0[arg1]; var_s0 += temp_t3) {
            spawn_object((LevelObjectEntryCommon *) D_8011AE98[arg1], 1);
            D_8011AE98[arg1] = &D_8011AE98[arg1][temp_t3 = D_8011AE98[arg1][1] & 0x3F];
        }
        D_8011AE98[arg1] = (u8 *) (D_8011AEB0[arg1] + 4);
        D_8011AE70 = 0;
        D_8011ADC0 = 1;
        if (gPathUpdateOff == FALSE) {
            gParticlePtrList_flush();
            func_80017E98();
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

// https://decomp.me/scratch/EXgPQ
#ifdef NON_EQUIVALENT
// track_init_racers
void func_8000CC7C(Vehicle vehicle, u32 arg1, s32 arg2) {
    s32 numPlayers; // sp144
    enum GameMode gameMode;
    s32 cutsceneID; // sp130
    s8 *miscAsset16;
    s8 sp11C[8];
    s8 sp114[8];
    s32 spF4[8];
    s32 spD4[8];
    s32 spB4[8];
    s32 sp94[8];
    LevelHeader *levelHeader;
    Camera *cutsceneCameraSegment; // sp74
    s16 objectId;
    s8 sp127;
    u8 raceType;
    s8 tempVehicle;
    u8 var_a1;
    s32 isChallengeMode; // sp64
    s32 i6;              // sp54
    LevelObjectEntry_Unk8000CC7C *entry;
    Object *curObj;
    Object *curRacerObj;
    Object *newRacerObj;
    Object_Racer *curRacer;
    Settings *settings;
    s32 spawnObjFlags;
    s32 racerPos;
    s32 i2;
    s32 j;
    s32 var_s4;
    s32 tajFlags;

    D_8011AD20 = FALSE;
    gEventCountdown = 0;
    gFirstTimeFinish = 0;
    gNumRacers = 0;
    D_8011AF00 = 0;
    set_taj_status(0);
    levelHeader = get_current_level_header();
    raceType = levelHeader->race_type;
    if (raceType == RACETYPE_CUTSCENE_1 || raceType == RACETYPE_CUTSCENE_2) {
        return;
    }
    if (raceType == RACETYPE_BOSS || raceType & RACETYPE_CHALLENGE) {
        gIsTimeTrial = 0;
        gTimeTrialEnabled = 0;
    }
    cutsceneID = -1;
    if (is_time_trial_enabled() && raceType == RACETYPE_DEFAULT) {
        cutsceneCameraSegment = cam_get_cameras();
        cutsceneID = (u8) cutsceneCameraSegment->zoom;
        cutsceneCameraSegment->zoom = 1;
    }
    gameMode = get_game_mode();
    settings = get_settings();
    miscAsset16 = (s8 *) get_misc_asset(3);
    gPrevTimeTrialVehicle = D_8011ADC5;
    tajFlags = settings->courseFlagsPtr[settings->courseId];
    if (!(tajFlags & 1)) { // Check if the player has not visited the course yet.
        settings->courseFlagsPtr[settings->courseId] = tajFlags | 1;
        D_8011AF00 = 2;
    }
    if (raceType != RACETYPE_DEFAULT) {
        D_8011AF00 = 2;
    }
    for (i2 = 0; i2 < 8; i2++) {
        spB4[i2] = 0;
        spF4[i2] = 0;
        spD4[i2] = 0;
    }
    for (i2 = 0; i2 < gObjectCount; i2++) {
        curObj = gObjPtrList[i2];
        if (!(curObj->segment.trans.flags & OBJ_FLAGS_PARTICLE)) {
            if (curObj->behaviorId == BHV_SETUP_POINT) {
                if (arg1 == (u32) curObj->properties.setupPoint.entranceID) {
                    if (curObj->properties.setupPoint.racerIndex < 8) {
                        spF4[curObj->properties.setupPoint.racerIndex] = curObj->segment.trans.x_position;
                        spD4[curObj->properties.setupPoint.racerIndex] = curObj->segment.trans.y_position;
                        spB4[curObj->properties.setupPoint.racerIndex] = curObj->segment.trans.z_position;
                        sp94[curObj->properties.setupPoint.racerIndex] = curObj->segment.trans.rotation.y_rotation;
                    }
                    tempVehicle = curObj->segment.level_entry->setupPoint.vehicle;
                    if (tempVehicle != -1) {
                        vehicle = tempVehicle;
                    }
                }
            }
        }
    }
    D_8011ADC5 = vehicle;
    gPrevTimeTrialVehicle = D_8011ADC5;
    numPlayers = arg2 + 1;
    gNumRacers = 8;
    D_800DC740 = 0;
    if (is_two_player_adventure_race()) {
        numPlayers = 2;
        D_800DC740 = 1;
        set_scene_viewport_num(1);
    }
    if (raceType == RACETYPE_HUBWORLD) {
        gTimeTrialEnabled = 0;
    }

    gIsTimeTrial = gTimeTrialEnabled;
    if (gIsTimeTrial) {
        raceType = RACETYPE_HUBWORLD; // ???
    }
    isChallengeMode = raceType & RACETYPE_CHALLENGE;
    if (raceType == RACETYPE_HUBWORLD || numPlayers >= 3) {
        gNumRacers = numPlayers;
        if (get_level_property_stack_pos() == 0 && D_800DC708 != 0) {
            sp94[0] += D_800DC708;
            D_800DC708 = 0;
        }
    } else if (numPlayers == 2) {
        gNumRacers = get_multiplayer_racer_count();
    }

    if (isChallengeMode != 0) {
        gNumRacers = 4;
    }
    D_8011AD3C = 0;
    if (raceType == RACETYPE_BOSS) {
        gNumRacers = 2;
        numPlayers = 1;
        D_8011AD3C = 1;
    }
    D_800DC71C = 0;
    if (gameMode == GAMEMODE_MENU && raceType == RACETYPE_DEFAULT) {
        gNumRacers = 6;
        D_800DC71C = 1;
        D_8011AD3C = 2;
    }

    for (i2 = 0; i2 < gNumRacers; i2++) {
        sp11C[i2] = 0;
    }

    var_a1 = 0;
    for (i2 = 0; i2 < numPlayers; i2++) {
        racerPos = settings->racers[i2].starting_position;
        if (racerPos < gNumRacers) {
            if (sp11C[racerPos] == 0) {
                sp11C[racerPos] = 1;
                continue;
            }
        }
        sp114[var_a1++] = (u16) i2;
    }

    for (i2 = numPlayers; i2 < gNumRacers; i2++) {
        racerPos = settings->racers[i2].starting_position;
        if (racerPos < gNumRacers) {
            if (sp11C[racerPos] == 0) {
                sp11C[racerPos] = 1;
                continue;
            }
        }
        sp114[var_a1++] = (u16) i2;
    }

    for (i6 = 0; i6 < var_a1; i6++) {
        for (j = 0; j < gNumRacers; j++) {
            if (sp11C[j] == 0) {
                sp11C[j] = 1;
                settings->racers[sp114[i6]].starting_position = j;
                j = gNumRacers;
            }
        }
    }
    if (((!(curObj->segment.trans.rotation.y_rotation)) && (!(curObj->segment.trans.rotation.y_rotation))) &&
        (!(curObj->segment.trans.rotation.y_rotation))) {}
    entry = mempool_alloc_safe(sizeof(LevelObjectEntry_Unk8000CC7C), COLOUR_TAG_YELLOW);
    entry->unkC = 0;
    entry->unkA = 0;
    entry->unk8 = 0;
    if (levelHeader->vehicle == VEHICLE_CAR) {
        gIsNonCarRacers = FALSE;
    } else {
        gIsNonCarRacers = TRUE;
    }
    sp127 = -1;
    i2 = gNumRacers;
    D_8011AD24[1] = levelHeader->bossRaceID;
    for (i6 = 0; i6 < gNumRacers; i6++) {
        var_s4 = i6;
        if (raceType != RACETYPE_HUBWORLD && isChallengeMode == 0 && D_8011AD3C == 0) {
            var_s4 = 0;
            // This might not be a for loop?
            for (j = 0; j < gNumRacers; j++) {
                if (i6 == settings->racers[j].starting_position) {
                    var_s4 = j;
                    j = i2;
                }
            }
        }
        if (var_s4 < numPlayers) {
            entry->unkE = var_s4;
        } else {
            entry->unkE = 4;
        }
        if (raceType != RACETYPE_HUBWORLD || entry->unkE != 4) {
            spawnObjFlags = 1;
            if (D_8011AD3C == 1) {
                if (i6 == 0) {
                    vehicle = gBossVehicles[D_8011AD24[1]].playerVehicle;
                } else {
                    vehicle = gBossVehicles[D_8011AD24[1]].playerVehicle;
                }
            } else if (D_8011AD3C == 2) {
                vehicle = levelHeader->vehicle;
            } else {
                if (entry->unkE == 4 || is_two_player_adventure_race()) {
                    vehicle = get_player_selected_vehicle(PLAYER_ONE);
                } else if (numPlayers >= 2) {
                    vehicle = get_player_selected_vehicle(entry->unkE);
                }
            }

            // Are these assignments correct? Seems weird.
            if (D_8011AD3C == 2) {
                objectId = D_800DC7A8[D_800DC840[i6] + (vehicle * 10)];
            } else if (vehicle < 5) {
                objectId = D_800DC7A8[(settings->racers[var_s4].character) + (vehicle * 10)];
            } else {
                objectId = D_800DC7B8[vehicle];
            }

            entry->common.objectID = objectId;
            entry->common.size = ((objectId & 0x100) >> 1) | 0x10;
            entry->common.x = spF4[i6];
            entry->common.y = spD4[i6];
            entry->common.z = spB4[i6];
            entry->unkC = sp94[i6];
            if (entry->unkE == 4) {
                func_800619F4(1);
            }
            if (entry->unkE == 4) {
                spawnObjFlags = 5;
                if (numPlayers >= 2) {
                    spawnObjFlags |= 8;
                }
            }
            if (entry->unkE != 4) {
                if (numPlayers == 1) {
                    spawnObjFlags |= 0x10;
                }
            }
            if (vehicle >= VEHICLE_BOSSES) {
                spawnObjFlags = 1;
                func_800619F4(0);
            }
            newRacerObj = spawn_object((LevelObjectEntryCommon *) entry, spawnObjFlags);
            newRacerObj->segment.trans.rotation.y_rotation = sp94[i6];
            (*gRacers)[i6] = newRacerObj;
            gRacersByPosition[i6] = newRacerObj;
            gRacersByPort[var_s4] = newRacerObj;
            curRacer = &newRacerObj->unk64->racer;
            newRacerObj->segment.level_entry = NULL;
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
            tempVehicle = curRacer->unk1CB;
            if (tempVehicle < VEHICLE_CAR || tempVehicle > VEHICLE_PLANE) {
                curRacer->unk1CB = 0;
            }
            curRacer->racerIndex = var_s4;
            curRacer->characterId = settings->racers[var_s4].character;
            if (D_8011AD3C == 2) {
                curRacer->characterId = D_800DC840[i6];
            } else {
                curRacer->characterId = settings->racers[var_s4].character;
            }
            if (raceType == RACETYPE_CHALLENGE_BATTLE) {
                curRacer->bananas = 8;
            } else {
                curRacer->bananas = 0;
            }
            if (get_filtered_cheats() & CHEAT_START_WITH_10_BANANAS && !isChallengeMode) {
                if (curRacer->playerIndex != PLAYER_COMPUTER) {
                    curRacer->bananas = 10;
                }
            }
            if ((gameMode != GAMEMODE_MENU || D_8011AD3C == 2) && vehicle < VEHICLE_BOSSES) {
                curRacer->vehicleSound = racer_sound_init(curRacer->characterId, curRacer->vehicleID);
            } else {
                curRacer->vehicleSound = NULL;
            }

            newRacerObj->interactObj->pushForce = miscAsset16[curRacer->characterId] + 1;
            switch (curRacer->vehicleID) {
                case VEHICLE_TRICKY:
                case VEHICLE_BLUEY:
                case VEHICLE_SMOKEY:
                case VEHICLE_PTERODACTYL:
                case VEHICLE_SNOWBALL:
                case VEHICLE_BUBBLER:
                case VEHICLE_WIZPIG:
                case VEHICLE_ROCKET:
                    racer_special_init(newRacerObj, curRacer);
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
    if (get_game_mode() == GAMEMODE_INGAME) {
        for (j = 0; j < gObjectCount; j++) {
            curObj = gObjPtrList[j];
            tajFlags = curObj->segment.header->flags;
            if ((tajFlags & 0x20) && (gIsTimeTrial)) {
                free_object(curObj);
            } else if ((tajFlags & 0x40) && (numPlayers >= 2)) {
                free_object(curObj);
            }
        }
    }
    gGhostObjStaff = 0;
    timetrial_free_staff_ghost();
    gTimeTrialContPak = -1;
    if ((gIsTimeTrial) && (numPlayers == 1)) {
        timetrial_reset_player_ghost();
        gTimeTrialContPak = timetrial_init_player_ghost(0);
        gHasGhostToSave = 0;
        if (gTimeTrialVehicle >= 5) {
            gTimeTrialVehicle = 0;
        }
        if (timetrial_valid_player_ghost() != 0) {
            objectId = D_800DC7A8[(gTimeTrialVehicle * 10) + gTimeTrialCharacter];
            entry->common.size = ((objectId & 0x100) >> 1) | 0x10;
            entry->common.objectID = objectId;
            entry->common.x = spF4[0];
            entry->common.y = spD4[0];
            entry->common.z = spB4[0];
            entry->unkC = sp94[0];
            newRacerObj = spawn_object((LevelObjectEntryCommon *) entry, OBJECT_SPAWN_UNK01);
            newRacerObj->segment.level_entry = NULL;
            newRacerObj->behaviorId = BHV_TIMETRIAL_GHOST;
            newRacerObj->shadow->scale = 0.01f;
            newRacerObj->interactObj->flags = INTERACT_FLAGS_NONE;
            gGhostObjPlayer = newRacerObj;
            newRacerObj->unk64->racer.transparency = 0x60;
        }
        if (timetrial_init_staff_ghost(get_current_map_id()) != 0) {
            objectId = D_800DC7B8[gMapDefaultVehicle * 10];
            entry->common.size = ((objectId & 0x100) >> 1) | 0x10;
            entry->common.objectID = objectId;
            entry->common.x = spF4[0];
            entry->common.y = spD4[0];
            entry->common.z = spB4[0];
            entry->unkC = sp94[0];
            newRacerObj = spawn_object((LevelObjectEntryCommon *) entry, OBJECT_SPAWN_UNK01);
            newRacerObj->segment.level_entry = NULL;
            newRacerObj->behaviorId = BHV_TIMETRIAL_GHOST;
            newRacerObj->shadow->scale = 0.01f;
            newRacerObj->interactObj->flags = INTERACT_FLAGS_NONE;
            gGhostObjStaff = newRacerObj;
            newRacerObj->unk64->racer.transparency = 0x60;
        }
    }
    gEventCountdown = 100;
    for (j = 0; j < gNumRacers; j++) {
        curRacerObj = (*gRacers)[j];
        curRacer = &curRacerObj->unk64->racer;
        for (i2 = 0; i2 < 10; i2++) {
            update_player_racer(curRacerObj, LOGIC_30FPS); // Simulate 10 updates?
        }
        if (curRacer->playerIndex == PLAYER_COMPUTER) {
            var_s4 = (var_s4 + 1) & 1;
            for (i2 = 0; i2 < curRacerObj->segment.header->numberOfModelIds; i2++) {
                if (curRacerObj->unk68[i2] != NULL) {
                    if (curRacerObj->unk68[i2]->animUpdateTimer != 0) {
                        curRacerObj->unk68[i2]->animUpdateTimer = (var_s4 * 2);
                    }
                }
            }
        } else {
            // curRacer is a human racer.
            for (i2 = 0; i2 < curRacerObj->segment.header->numberOfModelIds; i2++) {
                if (curRacerObj->unk68[i2] != NULL) {
                    if (curRacerObj->unk68[i2]->animUpdateTimer != 0) {
                        curRacerObj->unk68[i2]->animUpdateTimer = 0;
                    }
                }
            }
        }
        if (get_filtered_cheats() & CHEAT_BIG_CHARACTERS) {
            curRacerObj->segment.trans.scale *= 1.4f;
        }
        if (get_filtered_cheats() & CHEAT_SMALL_CHARACTERS) {
            curRacerObj->segment.trans.scale *= 0.714f;
        }
        curRacer->stretch_height_cap = 1.0f;
        curRacer->stretch_height = 1.0f;
    }
    if (raceType == RACETYPE_DEFAULT || isChallengeMode || gIsTimeTrial || D_8011AD3C) {
        gEventCountdown = 80;
    } else {
        gEventCountdown = 0;
    }
    if (raceType == RACETYPE_DEFAULT && numPlayers == 1 && !is_in_adventure_two()) {
        if (is_two_player_adventure_race() == 0) {
            for (i2 = 0; i2 < 3; i2++) {
                entry->common.objectID = ASSET_OBJECT_ID_POSARROW;
                entry->common.size = sizeof(LevelObjectEntryCommon);
                entry->common.x = 0;
                entry->common.y = 0;
                entry->common.z = 0;
                newRacerObj = spawn_object((LevelObjectEntryCommon *) entry, OBJECT_SPAWN_UNK01);
                newRacerObj->properties.common.unk0 = i2;
                newRacerObj->segment.level_entry = NULL;
            }
        }
    }
    gRaceEndTimer = 0;
    D_8011ADB4 = 0;
    set_next_taj_challenge_menu(0);
    if (settings->worldId == WORLD_CENTRAL_AREA) {
        if (!is_in_tracks_mode()) {
            var_s4 = 0;
            miscAsset16 = (s8 *) get_misc_asset(ASSET_MISC_16);
            tajFlags = settings->tajFlags;

            // settings->balloonsPtr[0] is the total balloon count.
            if (!(tajFlags & TAJ_FLAGS_CAR_CHAL_UNLOCKED) && (settings->balloonsPtr[0] >= miscAsset16[0])) {
                var_s4 = 1;
            } else if (!(tajFlags & TAJ_FLAGS_HOVER_CHAL_UNLOCKED) && (settings->balloonsPtr[0] >= miscAsset16[1])) {
                var_s4 = 2;
            } else if (!(tajFlags & TAJ_FLAGS_PLANE_CHAL_UNLOCKED) && (settings->balloonsPtr[0] >= miscAsset16[2])) {
                var_s4 = 3;
            }

            if (var_s4) {
                set_taj_voice_line(SOUND_VOICE_TAJ_CHALLENGE_RACE);
                settings->tajFlags |= 1 << (var_s4 + 31);
                set_taj_status(2);
                set_next_taj_challenge_menu(var_s4);
                safe_mark_write_save_file(get_save_file_index());
            }
        }
    }
    *D_8011AD24 = 1;
    if (cutsceneID >= 0) {
        cutsceneCameraSegment->zoom = cutsceneID;
    }
    if (func_8000E148() != 0) {
        rumble_init(FALSE);
        gEventCountdown = 0;
        start_level_music(1.0f);
    }
    mempool_free_timer(0);
    mempool_free(entry);
    mempool_free_timer(2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_8000CC7C.s")
#endif

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

s8 func_8000E148(void) {
    return D_800DC71C;
}

s8 func_8000E158(void) {
    if (D_800DC740 != 0) {
        return D_800DC73C;
    } else {
        return 0;
    }
}

s8 func_8000E184(void) {
    return D_800DC748;
}

void func_8000E194(void) {
    D_800DC73C = 1 - D_800DC73C;
    D_800DC740 = 0;
}

void fontUseFont(void) {
    D_800DC73C = 0;
    D_800DC740 = 0;
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
    gTransformPosX = obj->segment.trans.x_position;
    gTransformPosY = obj->segment.trans.y_position;
    gTransformPosZ = obj->segment.trans.z_position;
    gTransformAngleY = obj->segment.trans.rotation.y_rotation;
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
        objectID = ((s16 *) D_800DC7A8)[settings->racers[PLAYER_ONE].character + gOverworldVehicle * 10];
    } else {
        objectID = D_800DC7B8[gOverworldVehicle + 37];
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
    player = spawn_object(&spawnObj.common, OBJECT_SPAWN_INTERACTIVE | OBJECT_SPAWN_UNK01);
    gNumRacers = 1;
    (*gRacers)[PLAYER_ONE] = player;
    gRacersByPort[PLAYER_ONE] = player;
    *gRacersByPosition = player;
    racer = &player->unk64->racer;
    racer->vehicleID = gOverworldVehicle;
    racer->vehicleIDPrev = gOverworldVehicle;
    racer->racerIndex = 0;
    racer->characterId = settings->racers[PLAYER_ONE].character;
    racer->playerIndex = 0;
    racer->vehicleSound = 0;
    if (get_filtered_cheats() & CHEAT_BIG_CHARACTERS) {
        player->segment.trans.scale *= 1.4f;
    }
    if (get_filtered_cheats() & CHEAT_SMALL_CHARACTERS) {
        player->segment.trans.scale *= 0.714f;
    }
    player->segment.level_entry = NULL;
    player->segment.trans.rotation.y_rotation = gTransformAngleY;
    player->segment.trans.y_position = gTransformPosY;
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

    temp_v0 = D_8011AEB0[index];
    temp_v0[0] = D_8011AEA0[index];
    temp_v0[3] = 0;
    temp_v0[2] = 0;
    temp_v0[1] = 0;
    temp_a1 = &D_8011AE98[index][D_8011AEA0[index]];

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
    if (arg0->segment.level_entry == NULL) {
        return TRUE;
    }
    temp_v0 = (s32) arg0->segment.level_entry;
    new_var2 = (s32) D_8011AE98[0];
    if ((temp_v0 >= new_var2) && (((D_8011AEA0[0] * 8) + new_var2) >= temp_v0)) {
        return FALSE;
    }
    new_var = (s32) D_8011AE98[1];
    // Why even bother with this check?
    if (temp_v0 >= new_var && temp_v0 <= ((D_8011AEA0[1] * 8) + new_var)) {
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

    sp30[0] = (s32) D_8011AE98[0] + D_8011AEA0[0];
    sp30[1] = (s32) D_8011AE98[1] + D_8011AEA0[1];

    if ((s32) arg0 >= (s32) D_8011AE98[0] && (s32) arg0 < sp30[0]) {
        sp1C = 0;
    } else if ((s32) arg0 >= (s32) D_8011AE98[1] && (s32) arg0 < sp30[1]) {
        sp1C = 1;
    }

    dst = (u8 *) arg0;
    src = (u8 *) ((s32) arg0 + size);
    end = sp30[sp1C];
    if ((u32) src < end) {
        do {
            *dst++ = *src++;
        } while ((u32) src != end);
    }
    D_8011AEA0[sp1C] -= size;

    for (i = 0; i < gObjectCount; i++) {
        Object *obj = gObjPtrList[i];
        if (obj != NULL && obj->segment.level_entry != NULL) {
            if ((s32) arg0 < (s32) obj->segment.level_entry && (s32) obj->segment.level_entry < end) {
                obj->segment.level_entry = (LevelObjectEntry *) ((s32) obj->segment.level_entry - size);
            } else if ((s32) arg0 == (s32) obj->segment.level_entry) {
                obj->segment.level_entry = NULL;
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
    i = D_8011AEC0;
    var_a3 = (u8 *) D_8011AEB0[i] + D_8011AEA0[i];
    var_a3 += 16;

    if (arg1Value < arg0Value2) {
        var_a2 = arg0 + arg1Value;
        var_t0 = arg0 + arg0Value2;
        k = (u32) var_a3;
        while (((u32) var_t0) < k) {
            *var_a2 = *var_t0;
            var_a2++;
            var_t0++;
        }
    } else if (arg0Value2 < arg1Value) {
        var_a2 = var_a3 + arg1Value;
        var_a2 -= arg0Value2;
        var_t0 = var_a3;
        k = (u32) (arg0 + arg1Value);
        while (k < ((u32) var_a2)) {
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

    D_8011AEA0[i] += arg1Value - arg0Value;
}

UNUSED u8 *func_8000E898(u8 *arg0, s32 arg1) {
    s32 temp_t6;
    s32 i;
    u8 *temp_v1;
    u8 *new_var;
    u8 *new_var2;

    temp_t6 = arg0[1] & 0x3F;
    new_var = arg0;
    new_var = &D_8011AE98[arg1][D_8011AEA0[arg1]];
    new_var2 = arg0;
    temp_v1 = new_var;
    D_8011AEA0[arg1] += temp_t6;
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
    obj->segment.trans.flags |= OBJ_FLAGS_PARTICLE;
    func_800245B4(obj->segment.object.unk2C | (OBJ_FLAGS_PARTICLE | OBJ_FLAGS_INVISIBLE));
    gObjPtrList[gObjectCount++] = obj;
    if (1) {} // Fakematch
    gParticleCount++;
}

// https://decomp.me/scratch/vPHTQ
#ifdef NON_EQUIVALENT
Object *spawn_object(LevelObjectEntryCommon *entry, s32 arg1) {
    s32 objType;
    Object *newObj;
    s32 var_a2;
    s32 i;
    s32 var_s0_5;
    s32 sp50;
    s16 var_a0;
    u32 *address;
    s32 sizeOfobj;
    Object *curObj;
    Object *new_var;
    s32 assetCount;
    s8 var_v1;
    Settings *settings;

    settings = get_settings();
    objType = entry->objectID | ((entry->size & 0x80) << 1);
    update_object_stack_trace(OBJECT_SPAWN, objType);
    if (arg1 & 2) {
        var_a0 = objType;
    } else {
        var_a0 = gAssetsLvlObjTranslationTable[objType];
    }
    if (var_a0 >= gAssetsObjectHeadersTableLength) {
        var_a0 = 0;
    }
    for (i = 0; i < 0x200; i++) {
        (*gSpawnObjectHeap)[i] = NULL;
    }
    curObj = (Object *) &(*gSpawnObjectHeap)[0];
    curObj->segment.trans.flags = 2;
    curObj->segment.header = load_object_header(var_a0);
    if (curObj->segment.header == NULL) {
        return NULL;
    }
    sp50 = curObj->segment.header->flags & 0x80;
    if (sp50) {
        curObj->segment.trans.flags |= OBJ_FLAGS_UNK_0080;
    }
    if (curObj->segment.header->behaviorId == BHV_ROCKET_SIGNPOST && settings->cutsceneFlags & 1) {
        update_object_stack_trace(OBJECT_SPAWN, -1);
        return NULL;
    }
    curObj->segment.trans.x_position = entry->x;
    curObj->segment.trans.y_position = entry->y;
    curObj->segment.trans.z_position = entry->z;
    curObj->segment.object.segmentID = get_level_segment_index_from_position(
        curObj->segment.trans.x_position, curObj->segment.trans.y_position, curObj->segment.trans.z_position);
    curObj->segment.object.unk2C = var_a0;
    curObj->segment.level_entry = (LevelObjectEntry *) entry;
    curObj->objectID = objType;
    func_800245B4(objType);
    curObj->segment.trans.scale = curObj->segment.header->scale;
    curObj->segment.object.unk34 = curObj->segment.header->unk50 * curObj->segment.trans.scale;
    curObj->segment.object.opacity = 0xFF;
    sp50 = obj_init_property_flags(curObj->segment.header->behaviorId);
    curObj->segment.header->unk52++;
    assetCount = curObj->segment.header->numberOfModelIds;
    objType = curObj->segment.header->modelType;
    curObj->unk68 = (Object_68 **) &curObj->unk80;
    if (arg1 & 0x10) {
        assetCount = 1;
    }
    var_a2 = 0;
    switch (curObj->segment.header->behaviorId) {
        case BHV_PARK_WARDEN:
            if ((entry->z && entry->z) && entry->z) {} // fakematch
            func_800619F4(7);
            break;
        case BHV_ANIMATED_OBJECT_4:
            var_a2 = get_character_id_from_slot(PLAYER_ONE);
            curObj->segment.object.modelIndex = var_a2;
            assetCount = var_a2 + 1;
            break;
        case BHV_UNK_5B:
            var_a2 = (settings->trophies >> (((settings->worldId - 1) ^ 0) * 2)) & 3; // fakematch
            if (var_a2) {
                var_a2--;
                assetCount = var_a2 + 1;
                curObj->segment.object.modelIndex = var_a2;
            }
            break;
        case BHV_DYNAMIC_LIGHT_OBJECT_2:
            var_a2 = settings->wizpigAmulet;
            assetCount = var_a2 + 1;
            curObj->segment.object.modelIndex = settings->wizpigAmulet;
            break;
        case BHV_ROCKET_SIGNPOST_2:
            objType = settings->trophies;
            // Thanks, I hate it.
            for (i = 0; i < 4; i = (i + 1) & 0xFFFFFFFF) {
                if ((objType & 3) == 3) {
                    var_a2++;
                }
                objType >>= 2;
            }
            curObj->segment.object.modelIndex = var_a2;
            assetCount = var_a2 + 1;
            break;
        case BHV_GOLDEN_BALLOON:
            assetCount = 1;
            var_a2 = 0;
            if (is_in_adventure_two()) {
                curObj->segment.header->modelIds[0] = curObj->segment.header->modelIds[1];
            }
            curObj->segment.header->numberOfModelIds = 1;
            break;
    }
    if (!(arg1 & 2)) {
        if (curObj->objectID != 0x19) {
            if (curObj->objectID == 0xCB) {
                assetCount = 1;
                if (is_in_adventure_two()) {
                    curObj->segment.header->modelIds[0] = curObj->segment.header->modelIds[1];
                }
                curObj->segment.header->numberOfModelIds = 1;
            }
        } else {
            if (is_in_adventure_two()) {
                for (var_a2 = 0; var_a2 < 5; var_a2++) {
                    curObj->segment.header->modelIds[var_a2] = curObj->segment.header->modelIds[var_a2 + 5];
                }
            }
            assetCount = 5;
            curObj->segment.header->numberOfModelIds = 5;
            var_a2 = 0;
        }
    }
    var_v1 = FALSE;
    if (objType == 0) {
        for (; var_a2 < assetCount; var_a2++) {
            if (assetCount) {} // FAKEMATCH?
            if (var_a2 == 0 && arg1 & 4) {
                curObj->unk68[var_a2] = NULL;
            } else if (var_a2 == 1 && arg1 & 8) {
                curObj->unk68[var_a2] = NULL;
            } else {
                curObj->unk68[var_a2] = (Object_68 *) object_model_init(curObj->segment.header->modelIds[var_a2], sp50);
                if (curObj->unk68[var_a2] == NULL) {
                    var_v1 = TRUE;
                }
            }
        }
    } else if (objType == 4) {
        for (; var_a2 < assetCount; var_a2++) {
            curObj->unk68[var_a2] = (Object_68 *) load_texture(curObj->segment.header->modelIds[var_a2]);
            if (curObj->unk68[var_a2] == NULL) {
                var_v1 = TRUE;
            }
        }
    } else {
        for (; var_a2 < assetCount; var_a2++) {
            curObj->unk68[var_a2] = (Object_68 *) tex_load_sprite(curObj->segment.header->modelIds[var_a2], 10);
            if (curObj->unk68[var_a2] == NULL) {
                var_v1 = TRUE;
            }
        }
    }
    if (var_v1) {
        objFreeAssets(curObj, assetCount, objType);
        try_free_object_header(var_a0);
        return NULL;
    }
    address = (u32 *) &curObj->unk68[curObj->segment.header->numberOfModelIds];
    sizeOfobj = get_object_property_size(curObj, (Object_64 *) address);
    address = (u32 *) ((uintptr_t) address + sizeOfobj);
    D_8011AE50 = NULL;
    D_8011AE54 = NULL;
    if (sp50 & 1) {
        address = (u32 *) ((uintptr_t) address + init_object_shading(curObj, (ShadeProperties *) address));
    }
    if (sp50 & 2) {
        sizeOfobj = init_object_shadow(curObj, (ShadowData *) address);
        address = (u32 *) ((uintptr_t) address + sizeOfobj);
        if (sizeOfobj == 0) {
            objFreeAssets(curObj, assetCount, objType);
            try_free_object_header(var_a0);
            return NULL;
        }
    }
    if (sp50 & 4) {
        sizeOfobj = init_object_water_effect(curObj, (WaterEffect *) address);
        address = (u32 *) ((uintptr_t) address + sizeOfobj);
        if (sizeOfobj == 0) {
            if (D_8011AE50 != NULL) {
                tex_free((TextureHeader *) D_8011AE50);
            }
            objFreeAssets(curObj, assetCount, objType);
            try_free_object_header(var_a0);
            return NULL;
        }
    }
    if (sp50 & 0x10) {
        address = (u32 *) ((uintptr_t) address + init_object_interaction_data(curObj, (ObjectInteraction *) address));
    }
    if (sp50 & 0x20) {
        address = (u32 *) ((uintptr_t) address + func_8000FD34(curObj, (Object_5C *) address));
    }
    if ((curObj->segment.header->unk56 > 0) && (curObj->segment.header->unk56 < 10)) {
        curObj->unk60 = (Object_60 *) address;
        address += 0xC;
    }
    if (curObj->segment.header->particleCount > 0) {
        address = (u32 *) ((uintptr_t) address + obj_init_emitter(curObj, (ParticleEmitter *) address));
    }
    sizeOfobj = (uintptr_t) address - (uintptr_t) curObj;
    if (curObj->segment.header->numLightSources > 0) {
        curObj->lightData = (ObjectLight **) address;
        sizeOfobj = (s32) ((uintptr_t) address + (curObj->segment.header->numLightSources * 4)) - (uintptr_t) curObj;
    }
    newObj = mempool_alloc_pool((MemoryPoolSlot *) gObjectMemoryPool, sizeOfobj);
    if (newObj == NULL) {
        if (D_8011AE50 != NULL) {
            tex_free((TextureHeader *) D_8011AE50);
        }
        if (D_8011AE54 != NULL) {
            tex_free((TextureHeader *) D_8011AE54);
        }
        objFreeAssets(curObj, assetCount, objType);
        try_free_object_header(var_a0);
        return NULL;
    }
    if (sizeOfobj & 0xF) {
        sizeOfobj = (sizeOfobj & ~0xF) + 0x10;
    }
    sizeOfobj >>= 2;

    // for (var_s0_5 = 0; var_s0_5 < objSize; var_s0_5++) {
    //     u32 *temp = &newObj[var_s0_5];
    //     temp = (u32)&(*gSpawnObjectHeap)[var_s0_5];
    // }

    // WRONG WRONG WRONG - Is this really just trying to set up the first several values in a weird way?
    for (var_s0_5 = 0; var_s0_5 < sizeOfobj; var_s0_5 += 4) {
        newObj[var_s0_5].segment.trans.rotation.y_rotation =
            (*gSpawnObjectHeap)[var_s0_5]->segment.trans.rotation.y_rotation;
    }
    if (newObj->waterEffect != NULL) {
        newObj->waterEffect =
            (WaterEffect *) (((uintptr_t) newObj + (uintptr_t) newObj->waterEffect) - (uintptr_t) gSpawnObjectHeap);
    }
    if (newObj->shadow != NULL) {
        newObj->shadow =
            (ShadowData *) (((uintptr_t) newObj + (uintptr_t) newObj->shadow) - (uintptr_t) gSpawnObjectHeap);
    }
    if (newObj->shading != NULL) {
        newObj->shading =
            (ShadeProperties *) (((uintptr_t) newObj + (uintptr_t) newObj->shading) - (uintptr_t) gSpawnObjectHeap);
    }
    if (newObj->unk64 != NULL) {
        newObj->unk64 = (Object_64 *) (((uintptr_t) newObj + (uintptr_t) newObj->unk64) - (uintptr_t) gSpawnObjectHeap);
    }
    if (newObj->interactObj != NULL) {
        newObj->interactObj = (ObjectInteraction *) (((uintptr_t) newObj + (uintptr_t) newObj->interactObj) -
                                                     (uintptr_t) gSpawnObjectHeap);
    }
    if (newObj->unk5C != NULL) {
        newObj->unk5C = (Object_5C *) (((uintptr_t) newObj + (uintptr_t) newObj->unk5C) - (uintptr_t) gSpawnObjectHeap);
    }
    if (newObj->unk60 != NULL) {
        newObj->unk60 = (Object_60 *) (((uintptr_t) newObj + (uintptr_t) newObj->unk60) - (uintptr_t) gSpawnObjectHeap);
    }
    if (newObj->segment.header->particleCount > 0) {
        newObj->particleEmitter = (ParticleEmitter *) (((uintptr_t) newObj + (uintptr_t) newObj->particleEmitter) -
                                                       (uintptr_t) gSpawnObjectHeap);
    }
    if (newObj->segment.header->numLightSources > 0) {
        newObj->lightData =
            (ObjectLight **) (((uintptr_t) newObj + (uintptr_t) newObj->lightData) - (uintptr_t) gSpawnObjectHeap);
    }
    newObj->unk68 = (Object_68 **) ((uintptr_t) newObj + (uintptr_t) 0x80);
    if (arg1 & 1) {
        gObjPtrList[gObjectCount] = newObj;
        gObjectCount++;
    }
    run_object_init_func(newObj, entry, 0);
    if (newObj->interactObj != NULL) {
        newObj->interactObj->x_position = newObj->segment.trans.x_position;
        newObj->interactObj->y_position = newObj->segment.trans.y_position;
        newObj->interactObj->z_position = newObj->segment.trans.z_position;
    }
    if (newObj->segment.header->unk56 > 0 && newObj->segment.header->unk56 < 10 && func_8000F99C(newObj)) {
        if (D_8011AE50 != NULL) {
            tex_free(D_8011AE50);
        }
        if (D_8011AE54 != NULL) {
            tex_free(D_8011AE54);
        }
        objFreeAssets(newObj, assetCount, objType);
        try_free_object_header(var_a0);
        mempool_free(newObj);
        if (arg1 & 1) {
            gObjectCount--;
        }
        return NULL;
    }
    if (newObj->segment.header->numLightSources > 0) {
        light_setup_light_sources(newObj);
    }
    func_800619F4(0);
    update_object_stack_trace(OBJECT_SPAWN, -1);
    return newObj;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/objects/spawn_object.s")
#endif

/**
 * Run functions that will attempt to free the graphics data of the object
 * if there are no other references.
 */
void objFreeAssets(Object *obj, s32 count, s32 objType) {
    s32 i;
    if (objType == OBJECT_MODEL_TYPE_3D_MODEL) { // 3D model
        for (i = 0; i < count; i++) {
            if (obj->unk68[i] != NULL) {
                free_3d_model((ObjectModel **) (s32) obj->unk68[i]);
            }
        }
    } else if (objType == OBJECT_MODEL_TYPE_MISC) {
        for (i = 0; i < count; i++) {
            if (obj->unk68[i] != NULL) {
                tex_free((TextureHeader *) (s32) obj->unk68[i]);
            }
        }
    } else { // Sprite
        for (i = 0; i < count; i++) {
            if (obj->unk68[i] != NULL) {
                sprite_free((Sprite *) (s32) obj->unk68[i]);
            }
        }
    }
}
/**
 * Official Name: lightSetupLightSources
 */
void light_setup_light_sources(Object *obj) {
    s32 i;
    for (i = 0; i < obj->segment.header->numLightSources; i++) {
        obj->lightData[i] = add_object_light(obj, &obj->segment.header->unk24[i]);
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
    if (obj->segment.header->modelType == OBJECT_MODEL_TYPE_3D_MODEL) {
        for (i = 0; obj->unk68[i] == NULL; i++) {}
        if (obj->unk68[i] != NULL && obj->unk68[i]->objModel->unk40 != NULL) {
            set_shading_properties(obj->shading, obj->segment.header->shadeAmbient, obj->segment.header->shadeDiffuse,
                                   0, obj->segment.header->shadeAngleY, obj->segment.header->shadeAngleZ);
            if (obj->segment.header->unk3D != 0) {
                obj->shading->lightR = obj->segment.header->unk3A;
                obj->shading->lightG = obj->segment.header->unk3B;
                obj->shading->lightB = obj->segment.header->unk3C;
                obj->shading->lightIntensity = obj->segment.header->unk3D;
                obj->shading->lightDirX = -(obj->shading->shadowDirX >> 1);
                obj->shading->lightDirY = -(obj->shading->shadowDirY >> 1);
                obj->shading->lightDirZ = -(obj->shading->shadowDirZ >> 1);
            }
            returnSize = sizeof(ShadeProperties);
        }
    } else if (obj->segment.header->modelType == OBJECT_MODEL_TYPE_SPRITE_BILLBOARD) {
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

s32 func_8000F99C(Object *obj) {
    Object *temp_v0;
    Object_60 *obj60;
    s32 i;
    s32 var_s4;

    obj60 = obj->unk60;
    obj60->unk0 = obj->segment.header->unk56;
    obj60->unk0 = obj60->unk0; // Fakematch?
    var_s4 = FALSE;
    for (i = 0; i < obj60->unk0; i++) {
        obj60->unk4[i] = func_8000FD54(obj->segment.header->vehiclePartIds[i ^ 0]); // i ^ 0 fakematch
        if (obj60->unk4[i] == NULL) {
            var_s4 = TRUE;
        }
    }
    if (var_s4) {
        for (i = 0; i < obj60->unk0; i++) {
            temp_v0 = obj60->unk4[i];
            if (temp_v0 != NULL) {
                objFreeAssets(temp_v0, temp_v0->segment.header->numberOfModelIds, temp_v0->segment.header->modelType);
                try_free_object_header(temp_v0->segment.object.unk2C);
                mempool_free(temp_v0);
            }
        }
        return TRUE;
    }
    obj60->unk2C = obj->segment.header->vehiclePartIndices;
    return FALSE;
}

s32 obj_init_emitter(Object *obj, ParticleEmitter *emitter) {
    ObjHeaderParticleEntry *particleDataEntry;
    s32 i;

    obj->particleEmitter = emitter;
    particleDataEntry = obj->segment.header->objectParticles;
    for (i = 0; i < obj->segment.header->particleCount; i++) {
        if ((particleDataEntry[i].upper & 0xFFFF0000) == 0xFFFF0000) {
            emitter_init(&obj->particleEmitter[i], (particleDataEntry[i].upper >> 8) & 0xFF,
                         particleDataEntry[i].upper & 0xFF);
        } else {
            emitter_init_with_pos(&obj->particleEmitter[i], (particleDataEntry[i].upper >> 0x18) & 0xFF,
                                  (particleDataEntry[i].upper >> 0x10) & 0xFF, particleDataEntry[i].upper & 0xFFFF,
                                  (particleDataEntry[i].lower >> 0x10) & 0xFFFF, particleDataEntry[i].lower & 0xFFFF);
        }
    }
    return ((obj->segment.header->particleCount * sizeof(ParticleEmitter)) + 3) & ~3;
}

/**
 * Assigns shadow data to an object. Loads and assigns the shadow texture, too.
 * Returns zero if the texture is missing.
 */
s32 init_object_shadow(Object *obj, ShadowData *shadow) {
    ObjectHeader *objHeader;

    obj->shadow = shadow;
    shadow->texture = NULL;
    objHeader = obj->segment.header;
    if (objHeader->shadowGroup) {
        shadow->texture = load_texture(objHeader->unk34);
        objHeader = obj->segment.header;
    }
    shadow->scale = objHeader->shadowScale;
    shadow->meshStart = -1;
    D_8011AE50 = shadow->texture;
    if (obj->segment.header->shadowGroup && shadow->texture == NULL) {
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
    waterEffect->scale = obj->segment.header->unk8;
    waterEffect->textureFrame = 0;
    waterEffect->animationSpeed = obj->segment.header->unk0 >> 8;
    waterEffect->texture = NULL;
    if (obj->segment.header->waterEffectGroup) {
        waterEffect->texture = load_texture(obj->segment.header->unk38);
    }
    waterEffect->meshStart = -1;
    D_8011AE54 = waterEffect->texture;
    if (obj->segment.header->waterEffectGroup && waterEffect->texture == NULL) {
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

// Inits some matrix stuff for objects. It seems to be precomputing something, but not sure what.
s32 func_8000FD34(Object *obj, Object_5C *matrices) {
    obj->unk5C = matrices;
    func_80016BC4(obj);
    return sizeof(Object_5C);
}

// Loads an object from object header index
Object *func_8000FD54(s32 objectHeaderIndex) {
    s32 modelType;
    Object *object;
    ObjectHeader *objHeader;
    s32 objSize;
    s32 i;
    s32 failedToLoadModel;
    s8 numModelIds;
    u8 *objectAsRawBytes;

    if (objectHeaderIndex >= gAssetsObjectHeadersTableLength) {
        objectHeaderIndex = 0;
    }
    objHeader = load_object_header(objectHeaderIndex);
    if (objHeader == NULL) {
        return NULL;
    }
    objSize = (objHeader->numberOfModelIds * 4) + 0x80;
    object = (Object *) mempool_alloc(objSize, COLOUR_TAG_BLUE);
    if (object == NULL) {
        try_free_object_header(objectHeaderIndex);
        return NULL;
    }

    // clang-format off
    objectAsRawBytes = (u8 *) object;
    for (i = 0; i < objSize; i++) { objectAsRawBytes[i] = 0; } // Must be one line! (Why not use bzero?)
    // clang-format on

    object->segment.trans.flags = OBJ_FLAGS_UNK_0002;
    object->segment.header = objHeader;
    object->segment.object.unk2C = objectHeaderIndex;
    object->objectID = objectHeaderIndex;
    object->segment.trans.scale = objHeader->scale;
    if (objHeader->flags & OBJ_FLAGS_UNK_0080) {
        object->segment.trans.flags |= OBJ_FLAGS_UNK_0080;
    }
    numModelIds = object->segment.header->numberOfModelIds;
    modelType = object->segment.header->modelType;
    object->unk68 = (Object_68 **) &object->unk80;

    failedToLoadModel = FALSE;
    if (modelType == OBJECT_MODEL_TYPE_3D_MODEL) {
        for (i = 0; i < numModelIds; i++) {
            object->unk68[i] = object_model_init(object->segment.header->modelIds[i], 0);
            if (object->unk68[i] == NULL) {
                failedToLoadModel = TRUE;
            }
        }
    } else {
        for (i = 0; i < numModelIds; i++) {
            object->unk68[i] = (Object_68 *) tex_load_sprite(object->segment.header->modelIds[i], 10);
            if (object->unk68[i] == NULL) {
                failedToLoadModel = TRUE;
            }
        }
    }
    if (failedToLoadModel) {
        objFreeAssets(object, numModelIds, modelType);
        try_free_object_header(objectHeaderIndex);
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
        func_800101AC(searchObj, 0);
    }
    gFreeListCount = 0;
}

// https://decomp.me/scratch/DW6EX
#ifdef NON_EQUIVALENT
void func_800101AC(Object *obj, s32 arg1) {
    Object *tempObj;
    Object_Weapon *weapon;
    Object_Racer *racer;
    Object_Racer *snowball;
    Object_Fireball_Octoweapon *fireball;
    Object_Log *log;
    Object_Butterfly *butterfly;
    SoundHandle soundMask;
    s32 numberOfModelIds;
    s32 i;
    s32 j;

    if (obj->segment.trans.flags & OBJ_FLAGS_PARTICLE) {
        particle_deallocate((Particle *) obj);
        gParticleCount--;
        return;
    }
    if (obj->unk60 != NULL) {
        for (i = 0; i < obj->unk60->unk0; i++) {
            tempObj = obj->unk60->unk4[i];
            numberOfModelIds = tempObj->segment.header->numberOfModelIds;
            if (tempObj->segment.header->modelType == OBJECT_MODEL_TYPE_3D_MODEL) {
                if (!gObjPtrList) {} // fake
                for (j = 0; j < numberOfModelIds; j++) {
                    free_3d_model(&tempObj->unk68[j]->objModel);
                }
            } else {
                for (j = 0; j < numberOfModelIds; j++) {
                    sprite_free(tempObj->unk68[j]->sprite);
                }
            }
            try_free_object_header(tempObj->segment.object.unk2C);
            mempool_free(tempObj);
        }
    }
    if (obj->lightData != NULL) {
        for (i = 0; i < obj->segment.header->numLightSources; i++) {
            func_80032BAC(obj->lightData[i]);
        }
    }
    switch (obj->behaviorId) {
        case BHV_RACER:
        case BHV_ANIMATED_OBJECT_3:
            for (i = 0; i < gObjectCount; i++) {
                if (gObjPtrList[i]->behaviorId == BHV_BUTTERFLY) {
                    butterfly = &gObjPtrList[i]->unk64->butterfly;
                    if (obj == butterfly->unk100) {
                        butterfly->unk100 = 0;
                        butterfly->unkFD = 1;
                    }
                }
            }
            break;
        case BHV_WEAPON:
        case BHV_WEAPON_2:
            weapon = &obj->unk64->weapon;
            if (weapon->soundMask != NULL) {
                audspat_point_stop(weapon->soundMask);
                weapon->soundMask = NULL;
                if (obj->behaviorId == BHV_WEAPON_2) {
                    decrease_rocket_sound_timer();
                }
            }
            break;
        case BHV_FIREBALL_OCTOWEAPON_2:
            fireball = &obj->unk64->fireball_octoweapon;
            if (fireball->soundMask != NULL) {
                audspat_point_stop(fireball->soundMask);
            }
            break;
        case BHV_SNOWBALL:
        case BHV_SNOWBALL_2:
        case BHV_SNOWBALL_3:
        case BHV_SNOWBALL_4:
            // TODO: Get a Snowball struct?
            snowball = &obj->unk64->racer;
            if (snowball->unk20 != NULL) {
                audspat_point_stop((AudioPoint *) snowball->unk20);
            }
            break;
        case BHV_WAVE_GENERATOR:
            wavegen_destroy(obj);
            break;
        case BHV_LIGHT_RGBA:
            func_80032BAC((ObjectLight *) obj->unk64);
            break;
        case BHV_ANIMATION:
            if (obj->unk64 != NULL && arg1 == 0) {
                free_object(obj->unk64->obj);
            }
            break;
        case BHV_OVERRIDE_POS:
            for (i = 0; i < D_8011AE00 && obj != D_8011ADD8[i]; i++) {}
            if (i < D_8011AE00) {
                D_8011AE00--;
                for (; i < D_8011AE00; i++) {
                    D_8011ADD8[i] = D_8011ADD8[i + 1];
                }
            }
            break;
        case BHV_BUOY_PIRATE_SHIP:
        case BHV_LOG:
            log = &obj->unk64->log;
            if (log != NULL) {
                mempool_free(log);
            }
            break;
        case BHV_LENS_FLARE:
            lensflare_remove(obj);
            break;
        case BHV_LENS_FLARE_SWITCH:
            lensflare_override_remove(obj);
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
            // Not sure if this is an animation yet...
            soundMask = obj->unk64->animation.unk18;
            if (soundMask != NULL) {
                sndp_stop(soundMask);
            }
            break;
    }
    if (obj->behaviorId == BHV_RACER) {
        racer = &obj->unk64->racer;
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
        for (i = 0; i < gObjectCount; i++) {
            if ((gObjPtrList[i]->segment.trans.flags & OBJ_FLAGS_PARTICLE) &&
                (gObjPtrList[i]->segment.level_entry == obj->segment.level_entry)) {
                gObjPtrList[i]->segment.level_entry = NULL;
            }
            if (gObjPtrList[i]->behaviorId == BHV_WEAPON_2 || gObjPtrList[i]->behaviorId == BHV_FLY_COIN ||
                gObjPtrList[i]->behaviorId == BHV_WEAPON) {
                free_object((Object *) gObjPtrList[i]);
            }
        }
    }
    if (obj->shadow != NULL && obj->shadow->texture != NULL) {
        tex_free(obj->shadow->texture);
    }
    if (obj->waterEffect != NULL && obj->waterEffect->texture != NULL) {
        tex_free(obj->waterEffect->texture);
    }
    numberOfModelIds = obj->segment.header->numberOfModelIds;
    if (obj->segment.header->modelType == OBJECT_MODEL_TYPE_3D_MODEL) {
        for (i = 0; i < numberOfModelIds; i++) {
            if (obj->unk68[i] != NULL) {
                free_3d_model(&obj->unk68[i]->objModel);
            }
        }
    } else if (obj->segment.header->modelType == OBJECT_MODEL_TYPE_MISC) {
        for (i = 0; i < numberOfModelIds; i++) {
            tex_free(obj->unk68[i]->texHeader);
        }
    } else {
        for (i = 0; i < numberOfModelIds; i++) {
            sprite_free(obj->unk68[i]->sprite);
        }
    }
    if (obj->segment.header->particleCount > 0) {
        for (i = 0; i < obj->segment.header->particleCount; i++) {
            emitter_cleanup(&obj->particleEmitter[i]);
        }
    }
    try_free_object_header(obj->segment.object.unk2C);
    mempool_free(obj);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_800101AC.s")
#endif

void obj_update(s32 updateRate) {
    s32 i;
    s32 j;
    Object_Racer *racer;
    Object_68 *obj68;
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
        racer = &(*gRacers)[j]->unk64->racer;
        racer->prev_x_position = (*gRacers)[j]->segment.trans.x_position;
        racer->prev_y_position = (*gRacers)[j]->segment.trans.y_position;
        racer->prev_z_position = (*gRacers)[j]->segment.trans.z_position;
    }
    obj_tick_anims();
    process_object_interactions();
    func_8001E89C();
    for (i = 0; i < D_8011AE70; i++) {
        run_object_loop_func(D_8011AE6C[i], updateRate);
    }
    func_8001E6EC(1);
    for (i = 0; i < D_8011AE70; i++) {
        func_8001709C(D_8011AE6C[i]);
    }
    j = gObjectCount;
    for (i = gObjectListStart; i < j; i++) {
        obj = gObjPtrList[i];
        if (!(obj->segment.trans.flags & OBJ_FLAGS_PARTICLE)) {
            if ((obj->behaviorId != BHV_LIGHT_RGBA) && (obj->behaviorId != BHV_WEAPON) &&
                (obj->behaviorId != BHV_FOG_CHANGER)) {
                if (obj->interactObj != NULL) {
                    if (obj->interactObj->unk11 != 2) {
                        run_object_loop_func(obj, updateRate);
                    }
                } else {
                    run_object_loop_func(obj, updateRate);
                }
                if (obj->segment.header->modelType == OBJECT_MODEL_TYPE_3D_MODEL) {
                    for (sp54 = 0; sp54 < obj->segment.header->numberOfModelIds; sp54++) {
                        obj68 = obj->unk68[sp54];
                        if (obj68 != NULL) {
                            obj68->objModel->texOffsetUpdateRate = updateRate;
                        }
                    }
                    if (obj->segment.header->unk72 != 0xFF) {
                        func_80014090(obj, updateRate);
                    }
                }
            }
        }
    }
    for (i = 0; i < gNumRacers; i++) {
        update_player_racer((*gRacers)[i], updateRate);
    }
    if (get_current_level_race_type() == RACETYPE_DEFAULT) {
        for (i = 0; i < gNumRacers; i++) {
            racer = &gRacersByPosition[i]->unk64->racer;
            if (racer->playerIndex != -1) {
                increment_ai_behaviour_chances(gRacersByPosition[i], racer, updateRate);
                i = gNumRacers; // Why not just break?
            }
        }
    }
    racerfx_update(updateRate);
    for (i = gObjectListStart; i < j; i++) {
        obj = gObjPtrList[i];
        if ((!(obj->segment.trans.flags & OBJ_FLAGS_PARTICLE) && (obj->behaviorId == BHV_WEAPON)) ||
            (obj->behaviorId == BHV_FOG_CHANGER)) {
            run_object_loop_func(obj, updateRate);
        }
    }
    if (gParticleCount > 0) {
        for (i = gObjectListStart; i < j; i++) {
            obj = gObjPtrList[i];
            if (obj->segment.trans.flags & OBJ_FLAGS_PARTICLE) {
                // Why is this object being treated as a Particle?
                particle_update((Particle *) obj, updateRate);
            }
        }
    }

    lightUpdateLights(updateRate);
    if (get_light_count() > 0) {
        for (i = gObjectListStart; i < gObjectCount; i++) {
            obj = gObjPtrList[i];
            if (!(obj->segment.trans.flags & OBJ_FLAGS_PARTICLE) && (obj->shading != NULL)) {
                func_80032C7C(obj);
            }
        }
    }
    func_8001E6EC(0);
    if (gTajRaceInit != 0) {
        mode_init_taj_race();
    }
    if (gPathUpdateOff == FALSE) {
        gParticlePtrList_flush();
        func_80017E98();
        spectate_update();
        func_8001E93C();
    }
    if (gNumRacers != 0) {
        if (gRaceEndTimer == 0) {
            func_80019808(updateRate);
        } else {
            race_transition_adventure(updateRate);
        }
    }
    audspat_update_all(gRacersByPort, gNumRacers, updateRate);
    gPathUpdateOff = TRUE;
    gObjectUpdateRateF = (f32) updateRate;
    D_8011AD24[0] = 0;
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
    TriangleBatchInfo *batch;
    s32 offset;
    TextureHeader *tex;
    s16 temp_s5;
    s32 batchNumber;
    Object_68 *obj68;

    obj68 = obj->unk68[obj->segment.object.modelIndex];
    model = obj68->objModel;
    batch = model->batches;
    temp_s5 = model->unk50;
    for (batchNumber = 0; temp_s5 > 0 && batchNumber < model->numberOfBatches; batchNumber++) {
        if (batch[batchNumber].flags & RENDER_TEX_ANIM) {
            if (batch[batchNumber].textureIndex != TEX_INDEX_NO_TEXTURE) {
                tex = model->textures[batch[batchNumber].textureIndex].texture;
                offset = batch[batchNumber].texOffset;
                offset <<= 6;
                tex_animate_texture(tex, &batch[batchNumber].flags, &offset, updateRate);
                batch[batchNumber].texOffset = (offset >> 6) & 0xFF;
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

    door = &obj->unk64->door;
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
    if (arg1 < obj->segment.header->unk5B) {
        // TODO: Figure this one out better. The index could be something like this:
        // obj->segment.header->internalName[arg1 - 4]
        asset = (s8 *) get_misc_asset(*(&obj->segment.header->unk5C + arg1));
        asset0 = asset[0];
        shakeDist = (asset[1] & 0xFF) * 8.0f;
        shakeMagnitude = asset[2];
        frame >>= 4;
        animFrame = obj->segment.animFrame >> 4;
        for (i = 0; i < asset0; i++) {
            nextAsset = asset[i + 3];
            if ((animFrame >= nextAsset && frame < nextAsset) || (nextAsset >= animFrame && nextAsset < frame)) {
                set_camera_shake_by_distance(obj->segment.trans.x_position, obj->segment.trans.y_position,
                                             obj->segment.trans.z_position, shakeDist, shakeMagnitude);
                if (i & 1) {
                    soundId = oddSoundId; // Always set to SOUND_STOMP2
                } else {
                    soundId = evenSoundId; // Always set to SOUND_STOMP3
                }
                audspat_play_sound_at_position(soundId, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                               obj->segment.trans.z_position, AUDIO_POINT_FLAG_ONE_TIME_TRIGGER, NULL);
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
    newXPos = obj->segment.trans.x_position + xPos;
    newYPos = obj->segment.trans.y_position + yPos;
    newZPos = obj->segment.trans.z_position + zPos;
    if (levelModel == NULL) {
        gNoBoundsCheck = FALSE;
        return FALSE;
    }
    outOfBounds = FALSE;
    x2 = (levelModel->upperXBounds + 1000.0);
    //!@bug should've campared against "obj->segment.trans.x_position"
    if (newXPos > x2) {
        outOfBounds = TRUE;
    }
    x1 = (levelModel->lowerXBounds - 1000.0);
    if (obj->segment.trans.x_position < x1) {
        outOfBounds = TRUE;
    }
    if (1) {}
    if (1) {}
    if (1) {} // Fakematch
    y2 = (levelModel->upperYBounds + 3000.0);
    if (obj->segment.trans.y_position > y2) {
        outOfBounds = TRUE;
    }
    y1 = (levelModel->lowerYBounds - 500.00);
    if (obj->segment.trans.y_position < y1) {
        outOfBounds = TRUE;
    }
    z2 = (levelModel->upperZBounds + 1000.0);
    if (obj->segment.trans.z_position > z2) {
        outOfBounds = TRUE;
    }
    z1 = (levelModel->lowerZBounds - 1000.0);
    if (obj->segment.trans.z_position < z1) {
        outOfBounds = TRUE;
    }
    if (gNoBoundsCheck) {
        outOfBounds = FALSE;
    }

    gNoBoundsCheck = FALSE;
    if (outOfBounds) {
        obj->segment.object.segmentID = -1;
        return TRUE;
    }

    obj->segment.trans.x_position = newXPos;
    obj->segment.trans.y_position = newYPos;
    obj->segment.trans.z_position = newZPos;
    box = get_segment_bounding_box(obj->segment.object.segmentID);

    // For some reason the XYZ positions are converted into integers for the next section
    intXPos = newXPos, intYPos = newYPos, intZPos = newZPos;

    if (box == NULL) {
        obj->segment.object.segmentID = get_level_segment_index_from_position(intXPos, intYPos, intZPos);
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
                obj->segment.object.segmentID = segmentID;
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
    mtx_cam_push(&gObjectCurrDisplayList, &gObjectCurrMatrix, &obj->segment.trans, scaleY, 0.0f);
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
    Object_64 *objData;

    switch (obj->behaviorId) {
        case BHV_CHARACTER_FLAG:
            if (obj->properties.characterFlag.characterID >= 0) {
                objData = obj->unk64;
                render_misc_model(obj, objData->character_flag.vertices, 4, objData->character_flag.triangles, 2,
                                  objData->character_flag.texture,
                                  RENDER_ANTI_ALIASING | RENDER_Z_COMPARE | RENDER_FOG_ACTIVE, 0, 1.0f);
            }
            break;
        case BHV_BUTTERFLY:
            objData = obj->unk64;
            render_misc_model(obj, &objData->butterfly.vertices[objData->butterfly.unkFC * 6], 6,
                              objData->butterfly.triangles, 8, objData->butterfly.texture,
                              RENDER_Z_COMPARE | RENDER_FOG_ACTIVE, 0, 1.0f);
            break;
        case BHV_FISH:
            objData = obj->unk64;
            scaleY = obj->segment.level_entry->fish.unkD;
            scaleY *= 0.01f;
            render_misc_model(obj, &objData->fish.vertices[objData->fish.unkFC * 6], 6, objData->fish.triangles, 8,
                              objData->fish.texture, RENDER_Z_COMPARE | RENDER_FOG_ACTIVE | RENDER_CUTOUT, 0, scaleY);
            break;
        case BHV_BOOST:
            if (obj->properties.common.unk0 && (obj->unk64->boost.unk70 > 0 || obj->unk64->boost.unk74 > 0.0f)) {
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
    Sprite *gfxData;

    intensity = 255;
    hasPrimCol = FALSE;
    hasEnvCol = FALSE;
    flags = obj->segment.trans.flags | RENDER_Z_UPDATE | RENDER_FOG_ACTIVE;
    if (obj->shading != NULL) {
        hasPrimCol = TRUE;
        hasEnvCol = TRUE;
        intensity = obj->shading->unk0 * 255.0f;
    }

    if (obj->behaviorId == BHV_BOMB_EXPLOSION) {
        //!@bug Never true, because the type is u8.
        if (obj->segment.object.opacity > 255) {
            obj->segment.object.opacity = obj->properties.bombExplosion.unk4 & 0xFF;
        } else {
            obj->segment.object.opacity =
                (obj->segment.object.opacity * (obj->properties.bombExplosion.unk4 & 0xFF)) >> 8;
        }
    }

    alpha = obj->segment.object.opacity;
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
    if ((obj->behaviorId == 5) && (obj->segment.trans.scale == 6.0f)) {
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
    gfxData = (Sprite *) obj->unk68[obj->segment.object.modelIndex];
    bubbleTrap = NULL;
    if (obj->behaviorId == BHV_FIREBALL_OCTOWEAPON_2) {
        bubbleTrap = obj->properties.fireball.obj;
        if (obj->properties.fireball.timer > 0) {
            bubbleTrap = obj;
        }
    }

    // 5 = OilSlick, SmokeCloud, Bomb, BubbleWeapon
    if (bubbleTrap != NULL || !(obj->behaviorId != BHV_WEAPON || obj->unk64->weapon.weaponID != WEAPON_BUBBLE_TRAP)) {
        objTrans.trans.rotation.z_rotation = 0;
        objTrans.trans.rotation.x_rotation = 0;
        objTrans.trans.rotation.y_rotation = 0;
        objTrans.trans.scale = obj->segment.trans.scale;
        objTrans.trans.x_position = 0.0f;
        objTrans.trans.z_position = 0.0f;
        objTrans.trans.y_position = 12.0f;
        objTrans.animFrame = obj->segment.animFrame;
        objTrans.unk1A = 32;
        if (bubbleTrap == NULL) {
            bubbleTrap = obj->unk64->weapon.target;
            if (bubbleTrap == NULL) {
                bubbleTrap = obj;
            }
        }
        render_bubble_trap(&bubbleTrap->segment.trans, gfxData, (Object *) &objTrans,
                           RENDER_Z_COMPARE | RENDER_SEMI_TRANSPARENT | RENDER_Z_UPDATE);
    } else {
        render_sprite_billboard(&gObjectCurrDisplayList, &gObjectCurrMatrix, &gObjectCurrVertexList, obj, gfxData,
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
    s32 obj60_unk0;
    s32 hasOpacity;
    s32 hasLighting;
    s32 flags;
    s32 meshBatch;
    s32 cicFailed;
    f32 vtxX;
    f32 vtxY;
    f32 vtxZ;
    s8 index;
    s8 var_v0_2;
    Object *loopObj;
    Object_68 *obj68;
    Object_Racer *racerObj;
    ObjectModel *objModel;
    Sprite *something;

    obj68 = obj->unk68[obj->segment.object.modelIndex];
    if (obj68 != NULL) {
        objModel = obj68->objModel;
        hasOpacity = FALSE;
        hasLighting = FALSE;
        intensity = 255;
        if (obj->shading != NULL) {
            intensity = (s32) (obj->shading->unk0 * 255.0f * gCurrentLightIntensity);
            hasOpacity = TRUE;
            hasLighting = TRUE;
        }
        if (obj->behaviorId == BHV_RACER) {
            racerObj = &obj->unk64->racer;
            object_do_player_tumble(obj);
        } else {
            racerObj = NULL;
        }
        if (obj68->animUpdateTimer <= 0) {
            obj->curVertData = obj68->vertices[obj68->animationTaskNum];
            if (obj68->modelType == MODELTYPE_ANIMATED) {
                obj_animate(obj);
            }
            if (obj68->modelType != MODELTYPE_BASIC && objModel->unk40 != NULL) {
                flags = TRUE;
                if (racerObj != NULL && racerObj->vehicleID < VEHICLE_BOSSES &&
                    racerObj->playerIndex == PLAYER_COMPUTER) {
                    flags = FALSE;
                }
                if (cam_get_viewport_layout() != VIEWPORT_LAYOUT_1_PLAYER) {
                    flags = FALSE;
                }
                obj->curVertData = obj68->vertices[obj68->animationTaskNum];
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
                obj68->animUpdateTimer = 2;
            } else {
                obj68->animUpdateTimer = 1;
            }
        }
        obj->curVertData = obj68->vertices[obj68->animationTaskNum];
        if (obj->behaviorId == BHV_DOOR) {
            obj_door_number(objModel, obj);
        }
        if (objModel->texOffsetUpdateRate && objModel->unk50 > 0) {
            obj_tex_animate(obj, objModel->texOffsetUpdateRate);
            obj68->objModel->texOffsetUpdateRate = 0;
        }
        mtx_cam_push(&gObjectCurrDisplayList, &gObjectCurrMatrix, &obj->segment.trans, gObjectModelScaleY, 0.0f);
        vertOffset = FALSE;
        if (racerObj != NULL) {
            object_undo_player_tumble(obj);
            if (obj->segment.object.animationID == 0 || racerObj->vehicleID >= VEHICLE_BOSSES) {
                mtx_head_push(&gObjectCurrDisplayList, &gObjectCurrMatrix, obj68, racerObj->headAngle);
                vertOffset = TRUE;
            } else {
                racerObj->headAngle = 0;
            }
        }
        opacity = obj->segment.object.opacity;
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
        if (obj->segment.header->directionalPointLighting) {
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
        if (obj->segment.header->directionalPointLighting) {
            if (hasOpacity) {
                gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, intensity, intensity, intensity, opacity);
            } else {
                gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            }
            directional_lighting_off();
        }
        if (obj->unk60 != NULL) {
            obj60_unk0 = obj->unk60->unk0;
            if (racerObj != NULL && racerObj->vehicleID == VEHICLE_FLYING_CAR) {
                obj60_unk0 = 0;
            }
            for (i = 0; i < obj60_unk0; i++) {
                loopObj = obj->unk60->unk4[i];
                if (!(loopObj->segment.trans.flags & OBJ_FLAGS_INVISIBLE)) {
                    index = obj->unk60->unk2C[i];
                    if (index >= 0 && index < objModel->unk18) {
                        something = (Sprite *) loopObj->unk68[loopObj->segment.object.modelIndex];
                        vtxX = obj->curVertData[objModel->unk14[index]].x;
                        vtxY = obj->curVertData[objModel->unk14[index]].y;
                        vtxZ = obj->curVertData[objModel->unk14[index]].z;
                        loopObj->segment.trans.x_position += vtxX;
                        loopObj->segment.trans.y_position += vtxY;
                        loopObj->segment.trans.z_position += vtxZ;
                        if (loopObj->segment.header->modelType == OBJECT_MODEL_TYPE_SPRITE_BILLBOARD) {
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
                            var_v0_2 = (loopObj->segment.trans.flags & OBJ_FLAGS_UNK_0080 && obj60_unk0 == 3);
                            if (racerObj != NULL && racerObj->transparency < 255) {
                                var_v0_2 = FALSE;
                            }
                            if (var_v0_2) {
                                func_80012C98(&gObjectCurrDisplayList);
                                gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 255, 0);
                                gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, intensity, intensity, intensity,
                                                opacity);
                            }
                            loopObj->properties.common.unk0 =
                                render_sprite_billboard(&gObjectCurrDisplayList, &gObjectCurrMatrix,
                                                        &gObjectCurrVertexList, loopObj, something, flags);
                            if (var_v0_2) {
                                gSPSelectMatrixDKR(gObjectCurrDisplayList++, G_MTX_DKR_INDEX_0);
                                func_80012CE8(&gObjectCurrDisplayList);
                            }
                        }
                        loopObj->segment.trans.x_position -= vtxX;
                        loopObj->segment.trans.y_position -= vtxY;
                        loopObj->segment.trans.z_position -= vtxZ;
                    }
                }
            }
        }
        // This section draws the egg sprite being held by a racer.
        if (racerObj != NULL) {
            loopObj = racerObj->held_obj;
            if (loopObj != NULL) {
                index = obj->segment.header->unk58;
                if (index >= 0 && index < objModel->unk18) {
                    flags = (RENDER_Z_COMPARE | RENDER_FOG_ACTIVE | RENDER_Z_UPDATE);
                    something = (Sprite *) loopObj->unk68[loopObj->segment.object.modelIndex];
                    vtxX = obj->curVertData[objModel->unk14[index]].x;
                    vtxY = obj->curVertData[objModel->unk14[index]].y;
                    vtxZ = obj->curVertData[objModel->unk14[index]].z;
                    loopObj->segment.trans.x_position += (vtxX - loopObj->segment.trans.x_position) * 0.25;
                    loopObj->segment.trans.y_position += (vtxY - loopObj->segment.trans.y_position) * 0.25;
                    loopObj->segment.trans.z_position += (vtxZ - loopObj->segment.trans.z_position) * 0.25;
                    if (loopObj->segment.header->modelType == OBJECT_MODEL_TYPE_SPRITE_BILLBOARD) {
                        render_sprite_billboard(&gObjectCurrDisplayList, &gObjectCurrMatrix, &gObjectCurrVertexList,
                                                loopObj, something, flags);
                    }
                }
            }
        }
        if (meshBatch != -1) {
            if (obj->segment.header->directionalPointLighting) {
                gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, obj->shading->shadowR, obj->shading->shadowG,
                                obj->shading->shadowB, opacity);
                directional_lighting_on();
            }
            render_mesh(objModel, obj, meshBatch, RENDER_SEMI_TRANSPARENT, vertOffset);
            if (obj->segment.header->directionalPointLighting) {
                directional_lighting_off();
            }
        }
        if (hasOpacity || obj->segment.header->directionalPointLighting) {
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
    if (obj->segment.trans.flags & (OBJ_FLAGS_INVISIBLE | OBJ_FLAGS_SHADOW_ONLY)) {
        return;
    }
    update_object_stack_trace(OBJECT_DRAW, obj->objectID);
    gObjectCurrDisplayList = *dList;
    gObjectCurrMatrix = *mtx;
    gObjectCurrVertexList = *verts;
    scale = obj->segment.trans.scale;
    render_object_parts(obj);
    obj->segment.trans.scale = scale;
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

        sp_20 = &this->unk64->racer;
        this->segment.trans.rotation.y_rotation += sp_20->y_rotation_offset;
        this->segment.trans.rotation.x_rotation += sp_20->x_rotation_offset;
        this->segment.trans.rotation.z_rotation += sp_20->z_rotation_offset;
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
        this->segment.trans.y_position = this->segment.trans.y_position + offsetY;
        gObjectOffsetY = offsetY;
    }
}

/**
 * Official Name: objUndoPlayerTumble
 */
void object_undo_player_tumble(Object *obj) {
    if (obj->behaviorId == BHV_RACER) {
        Object_Racer *racer = &obj->unk64->racer;
        obj->segment.trans.rotation.y_rotation -= racer->y_rotation_offset;
        obj->segment.trans.rotation.x_rotation -= racer->x_rotation_offset;
        obj->segment.trans.rotation.z_rotation -= racer->z_rotation_offset;
        obj->segment.trans.y_position -= gObjectOffsetY;
    }
}

void set_temp_model_transforms(Object *obj) {
    s32 batchNum;
    ObjectModel *objModel;
    s32 var_v1;
    Object_68 **obj68List;
    Object_68 *obj68;
    u8 *bossAsset;
    f32 var_f0;
    u8 *var_a1;
    f32 ret2;
    UNUSED s32 pad;
    Object_Racer *objRacer;
    f32 ret1;
    s32 firstNonEmptyUnk68ObjectIndex;
    s32 modelIndex;
    s32 numberOfModels;

    ret1 = 1.0f;
    ret2 = 1.0f;
    if (!(obj->segment.trans.flags & OBJ_FLAGS_PARTICLE)) {
        if (obj->segment.header->behaviorId == BHV_RACER) {
            objRacer = &obj->unk64->racer;
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
                    var_f0 = obj->segment.object.distanceToCamera;
                    var_v1 = (s32) var_f0 >> 3;
                    if (obj->segment.object.distanceToCamera < 0.0f) {
                        var_f0 = 0.0f;
                    } else if (var_f0 > 3500.0f) {
                        var_f0 = 3500.0f;
                    }
                    var_f0 /= 2700.0f;
                    var_f0 += 1.0f;
                    obj->segment.trans.scale *= var_f0;
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

            firstNonEmptyUnk68ObjectIndex = 0;
            obj68List = &obj->unk68[firstNonEmptyUnk68ObjectIndex];

            while (*obj68List == NULL) {
                firstNonEmptyUnk68ObjectIndex++;
                obj68List++;
            }

            numberOfModels = obj->segment.header->numberOfModelIds - 1;
            obj68List = &obj->unk68[numberOfModels];

            while (*obj68List == NULL) {
                numberOfModels--;
                obj68List--;
            }

            if (modelIndex < firstNonEmptyUnk68ObjectIndex) {
                modelIndex = firstNonEmptyUnk68ObjectIndex;
            }
            if (numberOfModels < modelIndex) {
                modelIndex = numberOfModels;
            }
            obj->segment.object.modelIndex = modelIndex;
            if ((obj->shading != NULL) && (obj->shading->unk0 < 0.6f)) {
                objRacer->lightFlags |= RACER_LIGHT_NIGHT;
            } else {
                objRacer->lightFlags &= ~RACER_LIGHT_NIGHT;
            }
            modelIndex = objRacer->lightFlags & RACER_LIGHT_TIMER;
            obj68 = obj->unk68[obj->segment.object.modelIndex];
            objModel = obj68->objModel;
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
            obj->segment.trans.x_position += objRacer->carBobX;
            obj->segment.trans.y_position += objRacer->carBobY;
            obj->segment.trans.z_position += objRacer->carBobZ;
            ret1 = objRacer->stretch_height;
        } else if (obj->behaviorId == BHV_FROG) {
            ret1 = obj->unk64->frog.scaleY;
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
    if (obj->segment.trans.flags & OBJ_FLAGS_PARTICLE) {
        render_particle((Particle *) obj, &gObjectCurrDisplayList, &gObjectCurrMatrix, &gObjectCurrVertexList,
                        PARTICLE_UNK_FLAG_8000);
    } else {
        if (obj->segment.header->modelType == OBJECT_MODEL_TYPE_3D_MODEL) {
            render_3d_model(obj);
        } else if (obj->segment.header->modelType == OBJECT_MODEL_TYPE_SPRITE_BILLBOARD) {
            render_3d_billboard(obj);
        } else if (obj->segment.header->modelType == OBJECT_MODEL_TYPE_MISC) {
            render_3d_misc(obj);
        }
    }
    unset_temp_model_transforms(obj);
}

/**
 * After rendering, sets the object position back to normal.
 */
void unset_temp_model_transforms(Object *obj) {
    if (!(obj->segment.trans.flags & OBJ_FLAGS_PARTICLE) && obj->segment.header->behaviorId == BHV_RACER) {
        obj->segment.trans.x_position -= obj->unk64->racer.carBobX;
        obj->segment.trans.y_position -= obj->unk64->racer.carBobY;
        obj->segment.trans.z_position -= obj->unk64->racer.carBobZ;
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
    boost = &boostObj->unk64->boost;
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
    mtx_cam_push(&gObjectCurrDisplayList, &gObjectCurrMatrix, &boostObj->properties.boost.obj->segment.trans, 1.0f,
                 0.0f);
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

    vec3f_rotate(&trans->rotation, (Vec3f *) &obj->segment.trans.x_position);
    obj->segment.trans.x_position += trans->x_position;
    obj->segment.trans.y_position += trans->y_position;
    obj->segment.trans.z_position += trans->z_position;
    cameraSegment = cam_get_active_camera();
    x = cameraSegment->trans.x_position - obj->segment.trans.x_position;
    y = cameraSegment->trans.y_position - obj->segment.trans.y_position;
    z = cameraSegment->trans.z_position - obj->segment.trans.z_position;
    dist = sqrtf((x * x) + (y * y) + (z * z));
    if (dist > 0.0) {
        dist = obj->segment.numActiveEmitters / dist;
        x *= dist;
        y *= dist;
        z *= dist;
    }
    obj->segment.trans.x_position += x;
    obj->segment.trans.y_position += y;
    obj->segment.trans.z_position += z;
    render_sprite_billboard(&gObjectCurrDisplayList, &gObjectCurrMatrix, &gObjectCurrVertexList, obj, gfxData, flags);
}

/**
 * Get the racer object data, and fetch set visual shield properties based on that racer.
 * Afterwards, render the graphics with opacity scaling with the fadetimer.
 */
void render_racer_shield(Gfx **dList, Mtx **mtx, Vertex **vtxList, Object *obj) {
    Object_Racer *racer;
    Object_68 *gfxData;
    ObjectModel *mdl;
    RacerShieldGfx *shield;
    s32 shieldType;
    s32 vehicleID;
    s32 racerIndex;
    f32 scale;
    f32 shear;

    racer = &obj->unk64->racer;
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
        gShieldEffectObject->segment.trans.x_position = shield->x_position;
        gShieldEffectObject->segment.trans.y_position = shield->y_position;
        gShieldEffectObject->segment.trans.z_position = shield->z_position;
        gShieldEffectObject->segment.trans.y_position += shield->y_offset * sins_f(gShieldSineTime[racerIndex] * 0x200);
        shear = (coss_f(gShieldSineTime[racerIndex] * 0x400) * 0.05f) + 0.95f;
        gShieldEffectObject->segment.trans.scale = shield->scale * shear;
        shear = shear * shield->turnSpeed;
        gShieldEffectObject->segment.trans.rotation.y_rotation = gShieldSineTime[racerIndex] * 0x800;
        gShieldEffectObject->segment.trans.rotation.x_rotation = 0x800;
        gShieldEffectObject->segment.trans.rotation.z_rotation = 0;
        shieldType = racer->shieldType;
        if (shieldType != SHIELD_NONE) {
            shieldType--;
        }
        if (shieldType > SHIELD_LEVEL3 - 1) {
            shieldType = SHIELD_LEVEL3 - 1;
        }
        scale = ((f32) shieldType * 0.1) + 1.0f;
        gShieldEffectObject->segment.trans.scale *= scale;
        shear *= scale;
        gfxData = gShieldEffectObject->unk68[shieldType];
        mdl = gfxData->objModel;
        gShieldEffectObject->curVertData = gfxData->vertices[gfxData->animationTaskNum];
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
    Object_68 *gfxData;
    ObjectModel *mdl;
    f32 *magnet;
    s32 vehicleID;
    s32 racerIndex;
    s32 opacity;
    f32 shear;
    UNUSED s32 pad;

    racer = &obj->unk64->racer;
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
            gMagnetEffectObject->segment.trans.x_position = magnet[0];
            gMagnetEffectObject->segment.trans.y_position = magnet[1];
            gMagnetEffectObject->segment.trans.z_position = magnet[2];
            magnet += 3;
            shear = (coss_f((gRacerFXData[racerIndex].unk1 * 0x400)) * 0.02f) + 0.98f;
            gMagnetEffectObject->segment.trans.scale = magnet[0] * shear;
            magnet += 1;
            shear = magnet[0] * shear;
            gMagnetEffectObject->segment.trans.rotation.y_rotation = gRacerFXData[racerIndex].unk2 * 0x1000;
            gMagnetEffectObject->segment.trans.rotation.x_rotation = 0;
            gMagnetEffectObject->segment.trans.rotation.z_rotation = 0;
            gfxData = *gMagnetEffectObject->unk68;
            mdl = gfxData->objModel;
            gMagnetEffectObject->curVertData = gfxData->vertices[gfxData->animationTaskNum];
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
    Object_68 *obj68;
    TextureInfo *texInfo;
    Triangle *tri;
    s16 temp;
    s16 temp2;
    s16 newU1;
    s16 newU2;
    s16 newV1;
    s16 newV2;

    objHeader = obj->segment.header;
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
            obj68 = obj->unk68[i];
            objMdl = obj68->objModel;
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
    Object_68 *curr_68;

    for (; i < gObjectCount; i++) {
        currObj = gObjPtrList[i];
        if (!(currObj->segment.trans.flags & OBJ_FLAGS_PARTICLE) &&
            currObj->segment.header->modelType == OBJECT_MODEL_TYPE_3D_MODEL) {
            for (j = 0; j < currObj->segment.header->numberOfModelIds; j++) {
                curr_68 = currObj->unk68[j];
                if (curr_68 != NULL && curr_68->animUpdateTimer > 0) {
                    curr_68->animUpdateTimer &= 3;
                    curr_68->animUpdateTimer--;
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
            if (!(gObjPtrList[i]->segment.trans.flags & OBJ_FLAGS_PARTICLE)) {
                if (gObjPtrList[i]->segment.header->flags & 1) {
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
            if (gObjPtrList[j]->segment.trans.flags & OBJ_FLAGS_PARTICLE) {
                // Break the loop if OBJ_FLAGS_PARTICLE is set
                breakLoop = -1;
            } else if (!(gObjPtrList[j]->segment.header->flags & 1)) {
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
        gObjPtrList[i]->segment.object.unk38 += arg6;
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
                while ((var_a1 >= arg0) && ((gObjPtrList[arg0]->segment.trans.x_position -
                                             gObjPtrList[arg0]->segment.object.unk34) < arg2)) {
                    arg0++;
                }
                while ((arg1 >= var_a0) && (arg2 <= (gObjPtrList[arg1]->segment.trans.x_position -
                                                     gObjPtrList[arg1]->segment.object.unk34))) {
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
                while ((var_a1 >= arg0) && ((gObjPtrList[arg0]->segment.trans.y_position -
                                             gObjPtrList[arg0]->segment.object.unk34) < arg2)) {
                    arg0++;
                }
                while ((arg1 >= var_a0) && (arg2 <= (gObjPtrList[arg1]->segment.trans.y_position -
                                                     gObjPtrList[arg1]->segment.object.unk34))) {
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
                while ((var_a1 >= arg0) && ((gObjPtrList[arg0]->segment.trans.z_position -
                                             gObjPtrList[arg0]->segment.object.unk34) < arg2)) {
                    arg0++;
                }
                while ((arg1 >= var_a0) && (arg2 <= (gObjPtrList[arg1]->segment.trans.z_position -
                                                     gObjPtrList[arg1]->segment.object.unk34))) {
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
                while ((var_a1 >= arg0) && ((gObjPtrList[arg0]->segment.trans.x_position +
                                             gObjPtrList[arg0]->segment.object.unk34) < arg2)) {
                    arg0++;
                }
                while ((arg1 >= var_a0) && (arg2 <= (gObjPtrList[arg1]->segment.trans.x_position +
                                                     gObjPtrList[arg1]->segment.object.unk34))) {
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
                while ((var_a1 >= arg0) && ((gObjPtrList[arg0]->segment.trans.y_position +
                                             gObjPtrList[arg0]->segment.object.unk34) < arg2)) {
                    arg0++;
                }
                while ((arg1 >= var_a0) && (arg2 <= (gObjPtrList[arg1]->segment.trans.y_position +
                                                     gObjPtrList[arg1]->segment.object.unk34))) {
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
                while ((var_a1 >= arg0) && ((gObjPtrList[arg0]->segment.trans.z_position +
                                             gObjPtrList[arg0]->segment.object.unk34) < arg2)) {
                    arg0++;
                }
                while ((arg1 >= var_a0) && (arg2 <= (gObjPtrList[arg1]->segment.trans.z_position +
                                                     gObjPtrList[arg1]->segment.object.unk34))) {
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
            if (obj->segment.trans.flags & OBJ_FLAGS_PARTICLE) {
                // get_distance_to_camera calculates the distance to the camera from a XYZ location.
                obj->segment.object.distanceToCamera = -get_distance_to_camera(
                    obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
            } else if (obj->segment.header->flags & OBJ_FLAGS_UNK_0080) {
                obj->segment.object.distanceToCamera += -16000.0f;
            } else {
                obj->segment.object.distanceToCamera = -get_distance_to_camera(
                    obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
            }
        } else {
            //!@bug obj is NULL here, so it would probably cause a crash. Thankfully, gObjPtrList shouldn't have NULL
            //! objects in it.
            obj->segment.object.distanceToCamera = 0.0f;
        }
    }

    // Keep swapping until all objects are sorted by the distance to the camera.
    do {
        didNotSwap = TRUE;
        for (i = startIndex; i < lastIndex; i++) {
            if (gObjPtrList[i]->segment.object.distanceToCamera < gObjPtrList[i + 1]->segment.object.distanceToCamera) {
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
        if (!(obj->segment.trans.flags & OBJ_FLAGS_PARTICLE)) {
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

    D_8011AE70 = 0;

    for (i = 0; i < objsWithInteractives; i++) {
        obj = objList[i];
        objInteract = obj->interactObj;
        if (objInteract->unk11 == 2 && D_8011AE70 < 20) {
            D_8011AE6C[D_8011AE70] = obj;
            D_8011AE70++;
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
                            xDiff = obj->segment.trans.x_position - obj2->segment.trans.x_position;
                            zDiff = obj->segment.trans.z_position - obj2->segment.trans.z_position;
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
        objInteract->x_position = obj->segment.trans.x_position;
        objInteract->y_position = obj->segment.trans.y_position;
        objInteract->z_position = obj->segment.trans.z_position;
    }
}

// https://decomp.me/scratch/Hubco
#ifdef NON_EQUIVALENT
void func_800159C8(Object *arg0, Object *arg1) {
    f32 sp9C;
    f32 sp98;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    ObjectInteraction *sp58;
    ObjectInteraction *sp54;
    Object_64 *sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    ObjectInteraction *temp_a2;
    ObjectInteraction *temp_t0;
    Object_64 *temp_a1_2;
    Object_64 *temp_a1_3;
    Object_64 *temp_t5;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_5;
    f32 temp_f0_7;
    f32 temp_f0_8;
    f32 temp_f0_9;
    f32 temp_f10_2;
    f32 temp_f10_3;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f12_4;
    f32 temp_f12_5;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f14_3;
    f32 temp_f14_4;
    f32 temp_f14_5;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f12;
    f32 var_f12_2;
    f32 var_f16;
    f32 var_f16_2;
    f32 var_f18;
    f32 var_f2;
    f64 temp_f0_4;
    f64 temp_f0_6;
    s16 temp_a1;
    s32 temp_f10;
    s32 var_at;
    s32 var_t4;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s8 temp_v0_2;
    s8 temp_v0_3;
    u8 temp_v0;

    temp_f2 = arg1->segment.trans.x_position - arg0->segment.trans.x_position;
    var_f0 = arg1->segment.trans.y_position - arg0->segment.trans.y_position;
    temp_f14 = arg1->segment.trans.z_position - arg0->segment.trans.z_position;
    temp_a2 = arg1->interactObj;
    temp_t0 = arg0->interactObj;
    sp80 = 1.0f / gObjectUpdateRateF;
    temp_v0 = temp_a2->unk11;
    if (temp_v0 == 1) {
        temp_f0 = -var_f0;
        if (!(temp_f0 < ((f32) temp_a2->unk16 * 10.0f)) && !(((f32) temp_a2->unk17 * 10.0f) < temp_f0)) {
            var_f0 = 0.0f;
            sp64 = 0.0f;
        } else {
            return;
        }
    }

    if ((temp_v0 == 4) && (var_f0 < 0.0f)) {
        var_f0 = (f32) ((f64) var_f0 * 0.3);
    }
    sp54 = temp_a2;
    sp58 = temp_t0;
    sp64 = var_f0;
    sp68 = temp_f2;
    sp60 = temp_f14;
    var_f0_2 = sqrtf((temp_f2 * temp_f2) + (var_f0 * var_f0) + (temp_f14 * temp_f14));
    var_f16 = var_f0_2;
    temp_f10 = (s32) (f32) (s32) var_f0_2;
    var_v0 = temp_f10;
    if (temp_t0->flags & 0x20) {
        var_v0 = temp_f10 >> 3;
    }
    if (var_v0 >= 0x100) {
        var_v0 = 0xFF;
    }
    if ((s32) temp_t0->distance >= var_v0) {
        temp_t0->obj = arg1;
        temp_t0->distance = (u8) var_v0;
    }
    temp_a1 = temp_a2->flags;
    var_v0_2 = temp_f10;
    var_at = var_v0_2 < 0x100;
    if (temp_a1 & 0x20) {
        var_v0_2 = temp_f10 >> 3;
        var_at = var_v0_2 < 0x100;
    }
    if (var_at == 0) {
        var_v0_2 = 0xFF;
    }
    var_t4 = temp_a1 & 1;
    if ((s32) temp_a2->distance >= var_v0_2) {
        temp_a2->obj = arg0;
        temp_a2->distance = (u8) var_v0_2;
        var_t4 = temp_a2->flags & 1;
    }
    if (var_t4 != 0) {
        sp98 = (f32) (temp_a2->hitboxRadius + temp_t0->hitboxRadius);
        sp3C = temp_t0->x_position;
        temp_f4 = arg0->segment.trans.x_position - sp3C;
        sp7C = temp_f4;
        sp38 = temp_t0->y_position;
        sp34 = temp_t0->z_position;
        var_f12 = arg0->segment.trans.y_position - sp38;
        sp74 = arg0->segment.trans.z_position - sp34;
        if (temp_a2->unk11 == 1) {
            var_f12 = 0.0f;
        }
        temp_f14_2 = (temp_f4 * temp_f4) + (var_f12 * var_f12) + (sp74 * sp74);
        if ((f64) temp_f14_2 > 1.0) {
            temp_f18 = arg1->segment.trans.x_position;
            sp44 = arg1->segment.trans.y_position;
            sp40 = arg1->segment.trans.z_position;
            sp18 = sp74;
            sp1C = sp3C;
            sp20 = temp_f4;
            sp24 = sp44;
            sp28 = sp38;
            sp2C = ((temp_f18 - sp3C) * temp_f4) + ((sp44 - sp38) * var_f12);
            temp_f10_2 = sp18;
            sp18 = sp40;
            sp48 = temp_f18;
            temp_f2_2 = (sp2C + ((sp40 - sp34) * temp_f10_2)) / temp_f14_2;
            if (temp_f2_2 >= 0.0f) {
                sp78 = var_f12;
                if ((f64) temp_f2_2 <= 1.0) {
                    sp2C = sp34;
                    temp_f4_2 = sp1C + (temp_f2_2 * sp20);
                    sp8C = temp_f4_2;
                    sp54 = temp_a2;
                    temp_f10_3 = sp2C + (temp_f2_2 * temp_f10_2);
                    temp_f0_2 = temp_f4_2 - sp48;
                    temp_f14_3 = (sp28 + (temp_f2_2 * sp78)) - sp24;
                    sp84 = temp_f10_3;
                    sp58 = temp_t0;
                    temp_f16 = temp_f10_3 - sp18;
                    var_f0_2 = sqrtf((temp_f0_2 * temp_f0_2) + (temp_f14_3 * temp_f14_3) + (temp_f16 * temp_f16));
                    var_f16 = var_f0_2;
                }
            }
        }
        if ((var_f0_2 < sp98) && (var_f0_2 > 0.0f)) {
            temp_f2_3 = temp_a2->x_position - temp_t0->x_position;
            var_f18 = temp_a2->y_position - temp_t0->y_position;
            temp_f14_4 = temp_a2->z_position - temp_t0->z_position;
            if (temp_a2->unk11 == 1) {
                var_f18 = 0.0f;
            }
            sp54 = temp_a2;
            sp58 = temp_t0;
            sp8C = temp_f2_3;
            sp84 = temp_f14_4;
            sp9C = var_f16;
            sp88 = var_f18;
            temp_f0_3 = sqrtf((temp_f2_3 * temp_f2_3) + (var_f18 * var_f18) + (temp_f14_4 * temp_f14_4));
            if (temp_f0_3 > 0.0f) {
                sp64 = var_f18 / temp_f0_3;
                var_f12_2 = temp_f2_3 / temp_f0_3;
                sp60 = temp_f14_4 / temp_f0_3;
            } else {
                var_f12_2 = sp68 / var_f16;
                sp68 = var_f12_2;
                sp64 /= var_f16;
                sp60 /= var_f16;
            }
            var_f16_2 = temp_f0_3 - var_f16;
            if (var_f16_2 < 0.0f) {
                var_f16_2 = -var_f16_2;
            }
            temp_f12 = var_f12_2 * var_f16_2;
            sp64 *= var_f16_2;
            sp60 *= var_f16_2;
            temp_f16_2 = var_f16_2 * sp80;
            temp_t0->flags |= 8;
            temp_a2->flags |= 8;
            if (temp_a2->pushForce == 0) {
                arg0->segment.trans.x_position -= temp_f12;
                arg0->segment.trans.y_position -= sp64;
                arg0->segment.trans.z_position -= sp60;
                sp60 *= sp80;
                if (arg0->behaviorId == 1) {
                    temp_a1_2 = arg0->unk64;
                    var_v0_3 = 0;
                    if (temp_a1_2->racer.vehicleID == 1) {
                        temp_f0_4 = (f64) temp_f16_2;
                        if (temp_f0_4 > 0.3) {
                            if (temp_f0_4 > 1.0) {
                                var_v0_3 = 1;
                            }
                            if (var_v0_3 != 0) {
                                arg0->segment.x_velocity = (f32) ((f64) arg0->segment.x_velocity * 0.8);
                                arg0->segment.z_velocity = (f32) ((f64) arg0->segment.z_velocity * 0.8);
                            }
                            if (var_v0_3 != 0) {
                                temp_a2->flags |= 0x40;
                                temp_f12_2 = arg0->segment.z_velocity;
                                temp_f0_5 = arg0->segment.x_velocity;
                                temp_a1_2->racer.unk1D2 = 7;
                                if ((((arg1->segment.trans.x_position * temp_f12_2) -
                                      (arg1->segment.trans.z_position * temp_f0_5)) -
                                     ((arg0->segment.trans.x_position * temp_f12_2) -
                                      (arg0->segment.trans.z_position * temp_f0_5))) >= 0.0f) {
                                    temp_a1_2->racer.unk120 = (f32) ((f64) arg0->segment.x_velocity * 0.1);
                                    temp_a1_2->racer.unk11C = (f32) ((f64) -arg0->segment.z_velocity * 0.1);
                                } else {
                                    temp_a1_2->racer.unk120 = (f32) ((f64) -arg0->segment.x_velocity * 0.1);
                                    temp_a1_2->racer.unk11C = (f32) ((f64) arg0->segment.z_velocity * 0.1);
                                }
                            }
                        }
                    } else {
                        temp_f0_6 = (f64) temp_f16_2;
                        if (temp_f0_6 > 0.3) {
                            if (temp_f0_6 > 1.0) {
                                var_v0_3 = 1;
                            }
                            arg0->segment.x_velocity -= temp_f12 * sp80;
                            arg0->segment.z_velocity -= sp60;
                            temp_a1_2->racer.lateral_velocity = 0.0f;
                            temp_a1_2->racer.velocity = (f32) (temp_f0_6 * 0.25);
                        }
                        if (var_v0_3 != 0) {
                            temp_a2->flags |= 0x40;
                            temp_f12_3 = arg0->segment.z_velocity;
                            temp_f0_7 = arg0->segment.x_velocity;
                            if ((((arg1->segment.trans.x_position * temp_f12_3) -
                                  (arg1->segment.trans.z_position * temp_f0_7)) -
                                 ((arg0->segment.trans.x_position * temp_f12_3) -
                                  (arg0->segment.trans.z_position * temp_f0_7))) >= 0.0f) {
                                var_f2 = 2.0f;
                            } else {
                                var_f2 = -2.0f;
                            }
                            temp_f0_8 = temp_a1_2->racer.velocity;
                            temp_a1_2->racer.unk1D2 = 7;
                            temp_a1_2->racer.unk11C = temp_a1_2->racer.ox3 * var_f2 * temp_f0_8;
                            temp_a1_2->racer.unk120 = temp_a1_2->racer.oz3 * var_f2 * temp_f0_8;
                        }
                    }
                    if ((var_v0_3 != 0) && (temp_a1_2->racer.playerIndex != -1)) {
                        func_80016500(arg0, &temp_a1_2->racer);
                    }
                }
            } else {
                temp_f12_4 = (f32) ((f64) temp_f12 * 0.5);
                sp64 = (f32) ((f64) sp64 * 0.5);
                sp60 = (f32) ((f64) sp60 * 0.5);
                if (temp_t0->pushForce != 0) {
                    arg0->segment.trans.x_position -= temp_f12_4;
                    arg0->segment.trans.y_position -= sp64;
                    arg0->segment.trans.z_position -= sp60;
                }
                arg1->segment.trans.x_position += temp_f12_4;
                arg1->segment.trans.y_position += sp64;
                temp_f12_5 = temp_f12_4 * sp80;
                arg1->segment.trans.z_position += sp60;
                sp60 *= sp80;
                if ((arg0->behaviorId == 1) && (arg1->behaviorId == 1)) {
                    temp_a1_3 = arg0->unk64;
                    temp_t5 = arg1->unk64;
                    sp4C = temp_t5;
                    temp_v0_2 = temp_a1_3->racer.shieldType;
                    temp_f14_5 = (f32) ((f64) 1.0f + ((f64) (f32) (temp_t0->pushForce - temp_a2->pushForce) * 0.3));
                    if (temp_v0_2 != 0) {
                        if (temp_t5->racer.shieldType == 0) {
                            temp_t5->racer.spinout_timer = temp_v0_2;
                        }
                    }
                    temp_v0_3 = sp4C->racer.shieldType;
                    if ((temp_v0_3 != 0) && (temp_a1_3->racer.shieldType == 0)) {
                        temp_a1_3->racer.spinout_timer = temp_v0_3;
                    }
                    var_v0_4 = 0;
                    if (temp_a1_3->racer.vehicleID == 1) {
                        var_v0_4 = 1;
                        sp68 = temp_f12_5;
                    } else {
                        sp68 = temp_f12_5;
                        if ((f64) temp_f16_2 > 0.1) {
                            var_v0_4 = 1;
                            sp68 = (f32) ((f64) sp68 * 0.5);
                            sp60 = (f32) ((f64) sp60 * 0.5);
                        }
                    }
                    if (var_v0_4 != 0) {
                        if (temp_t0->pushForce != 0) {
                            temp_f0_9 = (f32) (2.0 - (f64) temp_f14_5);
                            arg0->segment.x_velocity -= sp68 * temp_f0_9;
                            arg0->segment.z_velocity -= sp60 * temp_f0_9;
                            sp90 = temp_f14_5;
                            func_80016500(arg0, &temp_a1_3->racer);
                        }
                        arg1->segment.x_velocity += sp68 * temp_f14_5;
                        arg1->segment.z_velocity += sp60 * temp_f14_5;
                        func_80016500(arg1, &sp4C->racer);
                    }
                }
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
    racer->lateral_velocity = (obj->segment.x_velocity * cosAngle) + (obj->segment.z_velocity * sinAngle);
    racer->velocity = (-obj->segment.x_velocity * sinAngle) + (obj->segment.z_velocity * cosAngle);
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
    Object_68 *obj68;

    if (obj1->curVertData != NULL) {
        obj68 = (*obj1->unk68);
        objModel = obj68->objModel;
        xDiff = obj0->segment.trans.x_position - obj1->segment.trans.x_position;
        yDiff = obj0->segment.trans.y_position - obj1->segment.trans.y_position;
        zDiff = obj0->segment.trans.z_position - obj1->segment.trans.z_position;
        if (!((objModel->unk3C + 50.0) < sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff)))) {
            obj0Interact = obj0->interactObj;
            obj1Interact = obj1->interactObj;
            mtxf_from_transform((MtxF *) obj1TransformMtx, &obj1->segment.trans);
            for (i = 0; i < objModel->unk20; i += 2) {
                xDiff = obj1->curVertData[objModel->unk1C[i]].x;
                yDiff = obj1->curVertData[objModel->unk1C[i]].y;
                zDiff = obj1->curVertData[objModel->unk1C[i]].z;
                mtxf_transform_point((MtxF *) obj1TransformMtx, xDiff, yDiff, zDiff, &xDiff, &yDiff, &zDiff);
                temp = (((f32) objModel->unk1C[i + 1] / 64) * obj1->segment.trans.scale) * 50.0;
                xDiff -= obj0->segment.trans.x_position;
                yDiff -= obj0->segment.trans.y_position;
                zDiff -= obj0->segment.trans.z_position;
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
                    obj0->segment.trans.x_position -= xDiff;
                    obj0->segment.trans.y_position -= yDiff;
                    obj0->segment.trans.z_position -= zDiff;

                    if (obj0->behaviorId == BHV_RACER) {
                        racer = &obj0->unk64->racer;
                        if (!racer->raceFinished) {
                            rumble_set(racer->playerIndex, RUMBLE_TYPE_18);
                        }
                        if (racer->vehicleID == VEHICLE_HOVERCRAFT) {
                            if (radius > 0.1) {
                                obj0->segment.x_velocity -= xDiff;
                                obj0->segment.z_velocity -= zDiff;
                            }
                        } else if (radius > 0.3) {
                            obj0->segment.x_velocity -= xDiff;
                            obj0->segment.z_velocity -= zDiff;
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

    obj->unk5C->unk104 = 0;
    func_8001709C(obj);
    func_8001709C(obj);
    for (i = 0; i < obj->segment.header->numberOfModelIds; i++) {
        if (obj->unk68[i] != NULL) {
            func_8006017C(obj->unk68[i]->objModel);
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
        if (!(curObj->segment.trans.flags & OBJ_FLAGS_PARTICLE) && curObj->behaviorId == BHV_ANIMATED_OBJECT_3) {
            diffX = curObj->segment.trans.x_position - x;
            diffZ = curObj->segment.trans.z_position - z;
            if (!dontCheckYAxis) {
                diffY = curObj->segment.trans.y_position - y;
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
            racer = &racerObj->unk64->racer;
            if (racer->playerIndex >= 0 && racer->playerIndex < 4) {
                if (is2dCheck) {
                    xDiff = racerObj->segment.trans.x_position - x;
                    zDiff = racerObj->segment.trans.z_position - z;
                    yDiff = sqrtf((xDiff * xDiff) + (zDiff * zDiff));
                } else {
                    xDiff = racerObj->segment.trans.x_position - x;
                    yDiff = racerObj->segment.trans.y_position - y;
                    zDiff = racerObj->segment.trans.z_position - z;
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

void func_8001709C(Object *obj) {
    ObjectTransform sp78;
    s32 i;
    f32 inverseScale;
    MtxF *sp6C;
    MtxF sp2C;
    Object_5C *obj5C;

    obj5C = obj->unk5C;
    obj5C->unk104 = (obj5C->unk104 + 1) & 1;
    sp6C = (MtxF *) &obj5C->_matrices[obj5C->unk104 << 1];
    sp78.rotation.y_rotation = -obj->segment.trans.rotation.y_rotation;
    sp78.rotation.x_rotation = -obj->segment.trans.rotation.x_rotation;
    sp78.rotation.z_rotation = -obj->segment.trans.rotation.z_rotation;
    sp78.scale = 1.0f;
    sp78.x_position = -obj->segment.trans.x_position;
    sp78.y_position = -obj->segment.trans.y_position;
    sp78.z_position = -obj->segment.trans.z_position;
    mtxf_from_inverse_transform(sp6C, &sp78);
    inverseScale = 1.0 / obj->segment.trans.scale;
    i = 0;
    while (i < 16) {
        ((f32 *) sp2C)[i] = 0.0f;
        i++;
    }
    sp2C[0][0] = inverseScale;
    sp2C[1][1] = inverseScale;
    sp2C[2][2] = inverseScale;
    sp2C[3][3] = 1.0f;
    mtxf_mul(sp6C, &sp2C, sp6C);
    sp78.rotation.y_rotation = obj->segment.trans.rotation.y_rotation;
    sp78.rotation.x_rotation = obj->segment.trans.rotation.x_rotation;
    sp78.rotation.z_rotation = obj->segment.trans.rotation.z_rotation;
    sp78.scale = 1.0 / inverseScale;
    sp78.x_position = obj->segment.trans.x_position;
    sp78.y_position = obj->segment.trans.y_position;
    sp78.z_position = obj->segment.trans.z_position;
    mtxf_from_transform((MtxF *) obj5C->_matrices[(obj5C->unk104 + 2) << 1], &sp78);
    obj5C->unk100 = NULL;
}

// https://decomp.me/scratch/Lxwa8
#ifdef NON_EQUIVALENT
s32 func_80017248(Object *obj, s32 arg1, s32 *arg2, Vec3f *arg3, f32 *arg4, f32 *arg5, s8 *surface) {
    s32 sp170;
    s32 sp16C;
    s32 sp168;
    s32 sp160;
    Object *otherObj;      // sp158
    ObjectModel *objModel; // sp154
    unk800179D0 *sp14C;
    f32 sp13C;
    f32 sp12C;
    f32 sp11C;
    f32 *sp100;
    f32 *spF0;
    f32 *spE0;
    MtxF *spDC;
    s32 spB8;
    s32 *spB4;
    f32 *sp8C;
    s32 *sp88;
    Object *temp_a1;
    Object *temp_v0;
    ObjectInteraction *temp_v1;
    Object_5C *temp_v0_2;
    Object_5C *temp_v0_5;
    Vec3f *var_s0_2;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f14;
    f32 temp_f2;
    f32 var_f0;
    f32 var_f2;
    f32 *temp_v1_2;
    f32 *var_s1_2;
    f32 *var_s1_3;
    f32 *var_s2_2;
    f32 *var_s2_3;
    f32 *var_s3;
    f32 *var_s3_2;
    f32 *var_s4;
    f32 *var_s4_2;
    f32 *var_s5;
    f32 *var_s5_2;
    f32 *var_s6;
    f32 *var_s6_2;
    f32 *var_s7;
    f32 *var_s7_2;
    f32 *var_v1;
    s32 temp_f16;
    s32 temp_t0;
    s32 temp_t2;
    s32 temp_t2_2;
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_v0_4;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 var_a3;
    s32 var_fp;
    s32 var_fp_2;
    s32 var_fp_3;
    s32 var_s1;
    s32 var_s2;
    s32 var_t0;
    s32 var_t0_2;
    s32 *var_v0;
    unk800179D0 *temp_v0_3;
    unk800179D0 *var_s0;
    unk800179D0 *temp_s0;

    sp160 = 0;
    sp170 = 0;
    if (D_8011AE70 > 0) {
        var_s2 = 0;
        do {
            temp_v0 = *(D_8011AE6C + var_s2);
            objModel = temp_v0->unk68[temp_v0->segment.object.modelIndex]->objModel;
            temp_f14 = temp_v0->segment.trans.x_position - obj->segment.trans.x_position;
            temp_f0 = temp_v0->segment.trans.y_position - obj->segment.trans.y_position;
            temp_f2 = temp_v0->segment.trans.z_position - obj->segment.trans.z_position;
            otherObj = temp_v0;
            temp_f0_2 = sqrtf((temp_f14 * temp_f14) + (temp_f0 * temp_f0) + (temp_f2 * temp_f2));
            temp_v1 = otherObj->interactObj;
            temp_f16 = (s32) temp_f0_2;
            var_fp = temp_f16;
            if (temp_v1->flags & 0x20) {
                var_fp = temp_f16 >> 3;
            }
            var_s2 += 4;
            if (var_fp >= 0x100) {
                var_fp = 0xFF;
            }
            if (var_fp < (s32) temp_v1->distance) {
                temp_v1->distance = (u8) var_fp;
                otherObj->interactObj->obj = obj;
            }
            temp_v1_2 = &(&sp8C[0])[sp160];
            if ((temp_f0_2 - 25.0f) < (objModel->unk3C * otherObj->segment.trans.scale)) {
                (&spB4[0])[sp160] = sp170;
                temp_v1_2[0] = temp_f0_2;
                if (sp160 > 0) {
                    var_v1 = &(&sp8C[0])[sp160];
                    if (temp_v1_2[-1] < temp_v1_2[0]) {
                        var_f0 = var_v1[-1];
                        var_f2 = var_v1[0];
                        var_v0 = &(&spB4[0])[sp160];
                    loop_12:
                        temp_t0 = var_v0[0];
                        temp_t7 = var_v0[-1];
                        var_v0--;
                        var_v1[0] = var_f0;
                        var_v1[-1] = var_f2;
                        var_v1--;
                        var_v0[0] = temp_t0;
                        var_v0[1] = temp_t7;
                        if ((u32) var_v0 >= (u32) &spB8) {
                            var_f0 = var_v1[-1];
                            var_f2 = var_v1[0];
                            if (var_f0 < var_f2) {
                                goto loop_12;
                            }
                        }
                    }
                }
                sp160 += 1;
            }
            temp_t2 = sp170 + 1;
            sp170 = temp_t2;
        } while (temp_t2 < D_8011AE70);
        sp170 = 0;
    }
    var_a3 = 0;
    if (sp160 > 0) {
        sp88 = &spB4[0];
        sp168 = 0;
        do {
            temp_a1 = D_8011AE6C[*sp88];
            var_s1 = 0;
            objModel = temp_a1->unk68[temp_a1->segment.object.modelIndex]->objModel;
            temp_v0_2 = temp_a1->unk5C;
            var_fp_2 = 0;
            sp16C = 1;
            spDC = &temp_a1->unk5C->matrices[(((temp_a1->unk5C->unk104 + 1) & 1) << 6)];
            otherObj = temp_a1;
            temp_v0_3 = func_8001790C((u32 *) obj, (u32 *) temp_a1);
            var_t0 = 1;
            sp14C = temp_v0_3;
            if (temp_v0_3 != NULL) {
                var_s2_2 = &sp13C;
                var_s0 = temp_v0_3;
                if (arg1 > 0) {
                    var_s1_2 = arg4;
                    var_s3 = &sp12C;
                    var_s4 = &sp11C;
                    var_s5 = sp100;
                    var_s6 = spF0;
                    var_s7 = spE0;
                    do {
                        *var_s2_2 = var_s0->unk0C[0];
                        *var_s3 = var_s0->unk0C[1];
                        *var_s4 = var_s0->unk0C[2];
                        sp16C = var_t0;
                        mtxf_transform_point(spDC, var_s1_2[0], var_s1_2[1], var_s1_2[2], var_s5, var_s6, var_s7);
                        var_fp_2 += 1;
                        var_s2_2 += 4;
                        var_s3 += 4;
                        var_s4 += 4;
                        var_s5 += 4;
                        var_s6 += 4;
                        var_s7 += 4;
                        var_s0 += 0xC;
                        var_s1_2 += 0xC;
                    } while (var_fp_2 != arg1);
                    var_s1 = 0;
                    var_fp_2 = 0;
                }
            } else {
                var_s2_3 = &sp13C;
                var_s3_2 = &sp12C;
                if (arg1 > 0) {
                    var_s0_2 = arg3;
                    var_s4_2 = &sp11C;
                    do {
                        sp16C = var_t0;
                        mtxf_transform_point(spDC, var_s0_2->f[0], var_s0_2->f[1], var_s0_2->f[2], var_s2_3, var_s3_2,
                                             var_s4_2);
                        var_fp_2 += 1;
                        var_s2_3 += 4;
                        var_s3_2 += 4;
                        var_s4_2 += 4;
                        var_s0_2 += 0xC;
                    } while (var_fp_2 != arg1);
                    var_s1 = 0;
                    var_fp_2 = 0;
                }
            }
            var_s5_2 = sp100;
            var_s6_2 = spF0;
            if (arg1 > 0) {
                var_s1_2 = arg4;
                var_s7_2 = spE0;
                do {
                    sp16C = var_t0;
                    mtxf_transform_point(spDC, var_s1_2[0], var_s1_2[1], var_s1_2[2], var_s5_2, var_s6_2, var_s7_2);
                    var_fp_2 += 1;
                    var_s5_2 += 4;
                    var_s6_2 += 4;
                    var_s7_2 += 4;
                    var_s1_2 += 0xC;
                } while (var_fp_2 != arg1);
                var_s1 = 0;
            }
            *arg2 = 0;
            sp16C = var_t0;
            temp_v0_4 = func_80017A18(objModel, arg1, arg2, &sp13C, &sp12C, &sp11C, sp100, spF0, spE0, arg5, surface,
                                      (f32) (1.0 / (f64) otherObj->segment.trans.scale));
            var_t0_2 = sp16C;
            if (temp_v0_4 != 0) {
                otherObj->unk5C->unk100 = obj;
            }
            var_fp_3 = 0;
            if (*D_8011AD24 == 0) {
                sp14C = func_80017978((s32) obj, (s32) otherObj);
            }
            temp_v0_5 = otherObj->unk5C;
            spDC = &temp_a1->unk5C->matrices[(temp_a1->unk5C->unk104 + 2) << 6];
            if (arg1 > 0) {
                do {
                    if (sp14C != NULL) {
                        temp_v0_6 = var_fp_3;
                        temp_s0 = sp14C + (var_s1 * 4);
                        sp14C->unk0C[var_s1] = sp100[temp_v0_6];
                        temp_s0->unk0C[2] = (f32) spF0[temp_v0_6];
                        temp_s0->unk0C[3] = (f32) spE0[temp_v0_6];
                    }
                    temp_v0_7 = var_fp_3 * 4;
                    if (temp_v0_4 & var_t0_2) {
                        sp16C = var_t0_2;
                        mtxf_transform_point(spDC, sp100[temp_v0_7], spF0[temp_v0_7], spE0[temp_v0_7], &arg4[var_s1],
                                             &arg4[var_s1 + 1], &arg4[var_s1 + 2]);
                    }
                    var_fp_3 += 1;
                    var_t0_2 *= 2;
                    var_s1 += 3;
                } while (var_fp_3 != arg1);
            }
            temp_t6 = sp168 | temp_v0_4;
            temp_t2_2 = sp170 + 1;
            sp168 = temp_t6;
            sp88 += 4;
            sp170 = temp_t2_2;
        } while (temp_t2_2 != sp160);
        var_a3 = temp_t6;
    }
    *arg2 = 0;
    if (var_a3 & 1) {
        *arg2 = 1;
    }
    if (var_a3 & 2) {
        *arg2 += 1;
    }
    if (var_a3 & 4) {
        *arg2 += 1;
    }
    if (var_a3 & 8) {
        *arg2 += 1;
    }
    return var_a3;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_80017248.s")
#endif

unk800179D0 *func_8001790C(u32 *arg0, u32 *arg1) {
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

unk800179D0 *func_80017978(s32 arg0, s32 arg1) {
    unk800179D0 *entry;
    s16 i;

    for (i = 0; i < 16; i++) {
        entry = &D_8011AFF4[i];
        if (entry->unk0 == 0) {
            entry->unk04 = (u32 *) arg0;
            entry->unk08 = (u32 *) arg1;
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

// https://decomp.me/scratch/dzU8Y
#ifdef NON_EQUIVALENT
s32 func_80017A18(ObjectModel *arg0, s32 arg1, s32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6, f32 *arg7,
                  f32 *arg8, f32 *arg9, s8 *surface, f32 argB) {
    s32 pad[4];
    s32 var_a2;
    s32 var_s6;
    s32 i; // s1
    s32 j;
    s32 k;
    s32 spF8;
    s32 var_t4;
    ObjectModel_10 *var_a0;
    f32 spE4;
    f32 spDC;
    f32 spD8;
    f32 spC0;
    f32 spBC;
    f32 spB4;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp74;
    f32 sp70;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f22;
    f32 temp_f26;
    f32 var_f2;
    f32 var_f30;
    ObjectModel_10 *temp_t0;
    ObjectModel_10 *temp_v0;
    s32 redoLoop;
    s32 pad1;

    spF8 = 0;
    temp_t0 = arg0->unk10;
    var_s6 = 1;
    for (i = 0; i < arg1; i++) {
        spBC = arg6[i];
        var_f30 = arg7[i];
        spB4 = arg8[i];
        spA4 = arg3[i];
        spA0 = arg4[i];
        sp9C = arg5[i];
        spC0 = arg9[i] * argB;
        var_t4 = 0;
        do {
            redoLoop = FALSE;
            for (j = 0; j < arg0->unk32; j++) {
                temp_v0 = &temp_t0[arg0->unkC->unk0[j]];
                temp_f26 = temp_v0->B;
                sp74 = temp_v0->A;
                temp_f12 = temp_v0->C;
                temp_f10 = temp_v0->D;
                spE4 = sp74;
                spDC = temp_f12;
                sp64 = spA0;
                spD8 = temp_f10;
                sp70 = spDC * spB4;
                sp74 = sp74 * spBC;
                temp_f0 = ((sp74 * spA4) + (temp_f26 * spA0) + (temp_f12 * sp9C) + temp_f10) - spC0;
                sp60 = spA4;
                sp68 = sp9C;
                temp_f22 = (sp74 + (temp_f26 * var_f30) + sp70 + spD8) - spC0;
                if (-0.10 <= temp_f0) {
                    var_a2 = 1;
                    if (temp_f22 < -0.1) {
                        if (temp_f0 != temp_f22) {
                            var_f2 = temp_f0 / (temp_f0 - temp_f22);
                        } else {
                            var_f2 = 0.0f;
                        }

                        for (k = 0; (k < 3) && (var_a2 == 1); k++) {
                            temp_v0 = &temp_t0[arg0->unkC->unk0[k + 1]];
                            if (((temp_v0->A * (((spBC - sp60) * var_f2) + spA4)) +
                                 (temp_v0->B * (((var_f30 - sp64) * var_f2) + spA0)) +
                                 (temp_v0->C * (((spB4 - sp68) * var_f2) + sp9C)) + temp_v0->D) > 4.0f) {
                                var_a2 = 0;
                            }
                        }

                        if (var_a2) {
                            redoLoop = TRUE;
                            if (temp_f26 > 0.707) {
                                var_f30 = (spC0 - (sp74 + sp70 + spD8)) / temp_f26;
                            } else {
                                spBC -= temp_f22 * spE4;
                                var_f30 -= temp_f22 * temp_f26;
                                spB4 -= temp_f22 * spDC;
                            }
                            var_t4++;
                            if (var_t4 >= 0xB) {
                                var_f30 = spA0;
                                redoLoop = 0;
                                spBC = spA4;
                                spB4 = sp9C;
                            }
                            surface[i] = 0;
                            arg6[i] = spBC;
                            arg7[i] = var_f30;
                            arg8[i] = spB4;
                            j = arg0->unk32;
                        }
                    }
                }
            }
        } while (redoLoop);
        if (var_t4 > 0) {
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

void func_80017E98(void) {
    f32 xDiff;
    f32 zDiff;
    f32 yDiff;
    s32 temp_v1;
    s32 checkpointNum;
    s32 duplicateCheckpoint;
    s32 breakOut;
    s32 altRouteId;
    s32 i;
    s32 altId;
    s32 var_a0;
    f32 ox;
    f32 oy;
    f32 oz;
    Object *obj;
    CheckpointNode *checkpoint;
    LevelObjectEntry_Checkpoint *checkpointEntry;
    MtxF mtx;
    ObjectTransform transform;
    s32 var_t2;

    var_t2 = 0;
    gNumberOfCheckpoints = 0;
    for (i = 0; i < gObjectCount; i++) {
        obj = gObjPtrList[i];
        if (!(obj->segment.trans.flags & OBJ_FLAGS_PARTICLE) && obj->behaviorId == BHV_CHECKPOINT &&
            gNumberOfCheckpoints < MAX_CHECKPOINTS) {
            checkpointEntry = &obj->segment.level_entry->checkpoint;
            if (checkpointEntry->unk1A == gTajChallengeType) {
                gTrackCheckpoints[gNumberOfCheckpoints].obj = obj;
                var_a0 = checkpointEntry->unk9;
                if (checkpointEntry->unk17) {
                    var_a0 += 255;
                    var_t2++;
                }
                gTrackCheckpoints[gNumberOfCheckpoints].unk2C = var_a0;
                gTrackCheckpoints[gNumberOfCheckpoints].altRouteID = -1;
                gNumberOfCheckpoints++;
            }
        }
    }

    duplicateCheckpoint = FALSE;
    do {
        altId = TRUE;

        for (i = 0; i < gNumberOfCheckpoints - 1; i++) {
            if (gTrackCheckpoints[i].unk2C == gTrackCheckpoints[i + 1].unk2C) {
                duplicateCheckpoint = TRUE;
                checkpointNum = gTrackCheckpoints[i].unk2C;
            }

            if (gTrackCheckpoints[i + 1].unk2C < gTrackCheckpoints[i].unk2C) {
                temp_v1 = gTrackCheckpoints[i].unk2C;
                obj = gTrackCheckpoints[i].obj;
                gTrackCheckpoints[i].unk2C = gTrackCheckpoints[i + 1].unk2C;
                gTrackCheckpoints[i].obj = gTrackCheckpoints[i + 1].obj;
                gTrackCheckpoints[i + 1].unk2C = temp_v1;
                gTrackCheckpoints[i + 1].obj = obj;
                altId = FALSE;
            }
        }
    } while (!altId);
    D_8011AED4 = gNumberOfCheckpoints;
    gNumberOfCheckpoints -= var_t2;
    if (duplicateCheckpoint) {
        set_render_printf_position(20, 220);
        render_printf(sDuplicateCheckpointString /* "Error: Multiple checkpoint no: %d !!\n"; */, checkpointNum);
    }
    for (i = gNumberOfCheckpoints; i < D_8011AED4; i++) {
        temp_v1 = gTrackCheckpoints[i].unk2C - 255;
        for (var_a0 = 0, breakOut = FALSE; var_a0 < gNumberOfCheckpoints && !breakOut; var_a0++) {
            if (temp_v1 == gTrackCheckpoints[var_a0].unk2C) {
                gTrackCheckpoints[var_a0].altRouteID = i;
                gTrackCheckpoints[i].altRouteID = var_a0;
                breakOut = TRUE;
            }
        }
    }

    for (i = 0; i < D_8011AED4; i++) {
        checkpoint = &gTrackCheckpoints[i];
        obj = checkpoint->obj;
        checkpointEntry = &obj->segment.level_entry->checkpoint;
        transform.rotation.y_rotation = obj->segment.trans.rotation.y_rotation;
        transform.rotation.x_rotation = obj->segment.trans.rotation.x_rotation;
        transform.rotation.z_rotation = obj->segment.trans.rotation.z_rotation;
        transform.scale = 1.0f;
        transform.x_position = 0.0f;
        transform.y_position = 0.0f;
        transform.z_position = 0.0f;
        mtxf_from_transform(&mtx, &transform);
        mtxf_transform_point(&mtx, 0.0f, 0.0f, 1.0f, &ox, &oy, &oz);
        checkpoint->rotationXFrac = ox;
        checkpoint->rotationYFrac = oy;
        checkpoint->rotationZFrac = oz;
        checkpoint->unkC = -(((obj->segment.trans.x_position * ox) + (obj->segment.trans.y_position * oy)) +
                             (obj->segment.trans.z_position * oz));
        checkpoint->x = obj->segment.trans.x_position;
        checkpoint->y = obj->segment.trans.y_position;
        checkpoint->z = obj->segment.trans.z_position;
        checkpoint->scale = obj->segment.trans.scale * 2;
        checkpoint->unk2C = obj->segment.trans.scale * 128.0f;
        checkpoint->unk24 = 0.0f;
        checkpoint->distance = 0.0f;
        if (i < gNumberOfCheckpoints) {
            temp_v1 = i + 1;
            if (temp_v1 == gNumberOfCheckpoints) {
                temp_v1 = 0;
            }
            xDiff = obj->segment.trans.x_position - gTrackCheckpoints[temp_v1].obj->segment.trans.x_position;
            yDiff = obj->segment.trans.y_position - gTrackCheckpoints[temp_v1].obj->segment.trans.y_position;
            zDiff = obj->segment.trans.z_position - gTrackCheckpoints[temp_v1].obj->segment.trans.z_position;
            checkpoint->distance = sqrtf(((xDiff * xDiff) + (yDiff * yDiff)) + (zDiff * zDiff));
            altRouteId = gTrackCheckpoints[temp_v1].altRouteID;
            if (altRouteId != -1) {
                xDiff = obj->segment.trans.x_position - gTrackCheckpoints[altRouteId].obj->segment.trans.x_position;
                yDiff = obj->segment.trans.y_position - gTrackCheckpoints[altRouteId].obj->segment.trans.y_position;
                zDiff = obj->segment.trans.z_position - gTrackCheckpoints[altRouteId].obj->segment.trans.z_position;
                checkpoint->unk24 = sqrtf(((xDiff * xDiff) + (yDiff * yDiff)) + (zDiff * zDiff));
            } else {
                checkpoint->unk24 = checkpoint->distance;
            }
        } else {
            temp_v1 = gTrackCheckpoints[i].altRouteID + 1;
            if (temp_v1 == gNumberOfCheckpoints) {
                temp_v1 = 0;
            }
            xDiff = obj->segment.trans.x_position - gTrackCheckpoints[temp_v1].obj->segment.trans.x_position;
            yDiff = obj->segment.trans.y_position - gTrackCheckpoints[temp_v1].obj->segment.trans.y_position;
            zDiff = obj->segment.trans.z_position - gTrackCheckpoints[temp_v1].obj->segment.trans.z_position;
            checkpoint->distance = sqrtf(((xDiff * xDiff) + (yDiff * yDiff)) + (zDiff * zDiff));
            altRouteId = gTrackCheckpoints[temp_v1].altRouteID;
            if (altRouteId != -1) {
                xDiff = obj->segment.trans.x_position - gTrackCheckpoints[altRouteId].obj->segment.trans.x_position;
                yDiff = obj->segment.trans.y_position - gTrackCheckpoints[altRouteId].obj->segment.trans.y_position;
                zDiff = obj->segment.trans.z_position - gTrackCheckpoints[altRouteId].obj->segment.trans.z_position;
                checkpoint->unk24 = sqrtf(((xDiff * xDiff) + (yDiff * yDiff)) + (zDiff * zDiff));
            } else {
                checkpoint->unk24 = checkpoint->distance;
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

// https://decomp.me/scratch/xQbet
#ifdef NON_EQUIVALENT
s32 func_800185E4(s32 checkpointIndex, Object *obj, f32 objX, f32 objY, f32 objZ, f32 *checkpointDistance, u8 *arg6) {
    s32 sp70;
    f32 xDiff; // sp6C
    f32 yDiff;
    f32 zDiff; // sp64
    f32 sp5C;
    f32 sp58;
    f32 sp50;
    CheckpointNode *sp4C;
    CheckpointNode *sp48;
    CheckpointNode *sp44;
    f32 sp3C;
    s32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    Object_64 *temp_v0_4;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f20_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f2_5;
    f32 temp_f2_7;
    f32 temp_f2_8;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f4_3;
    f32 temp_f6;
    f32 temp_f6_2;
    f32 temp_f6_3;
    f32 temp_f8;
    f32 temp_f8_2;
    f32 var_f0;
    f64 temp_f2_6;
    s32 temp_f8_3;
    s32 var_t1;
    s32 var_v1;
    CheckpointNode *temp_a1;

    if (gNumberOfCheckpoints == 0) {
        return 1;
    }
    sp38 = checkpointIndex;
    sp70 = FALSE;
    sp4C = &gTrackCheckpoints[checkpointIndex];
    if (checkpointIndex != 0) {
        sp48 = &gTrackCheckpoints[checkpointIndex - 1];
    } else {
        sp48 = &gTrackCheckpoints[gNumberOfCheckpoints - 1];
    }
    if (*arg6) {
        if (sp4C->altRouteID != -1) {
            sp4C = &gTrackCheckpoints[sp4C->altRouteID];
        }
        if (sp48->altRouteID != -1) {
            sp48 = &gTrackCheckpoints[sp48->altRouteID];
        }
    }
    if ((!*arg6) && (sp48->altRouteID == -1)) {
        if (sp4C->altRouteID != -1) {
            sp44 = &gTrackCheckpoints[sp4C->altRouteID];
            xDiff = sp44->x - obj->segment.trans.x_position;
            yDiff = sp44->y - obj->segment.trans.y_position;
            zDiff = sp44->z - obj->segment.trans.z_position;
            sp70 = FALSE;
            if (sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff)) < sp44->unk2C) {
                sp4C = sp44;
                sp70 = TRUE;
            }
        }
    }
    xDiff = sp4C->x - sp48->x;
    yDiff = sp4C->y - sp48->y;
    zDiff = sp4C->z - sp48->z;
    temp_f0_3 = sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff));
    if (temp_f0_3 > 0.0) {
        yDiff *= (1 / temp_f0_3);
        xDiff *= (1 / temp_f0_3);
        zDiff *= (1 / temp_f0_3);
    }
    temp_f14 = sp4C->rotationXFrac;
    temp_f0_4 = obj->segment.trans.x_position;
    temp_f16 = sp4C->rotationYFrac;
    temp_f2_4 = obj->segment.trans.y_position;
    temp_f18 = sp4C->rotationZFrac;
    temp_f12 = obj->segment.trans.z_position;
    temp_f6 = (temp_f14 * temp_f0_4) + (temp_f16 * temp_f2_4) + (temp_f18 * temp_f12) + sp4C->unkC;
    sp58 = temp_f6;
    sp20 = temp_f6;
    temp_f8 = (temp_f14 * xDiff) + (temp_f16 * yDiff) + (temp_f18 * zDiff);
    sp5C = temp_f8;
    temp_f6_2 = -temp_f6 / temp_f8;
    sp5C = temp_f6_2;
    temp_f8_2 = sp48->rotationXFrac;
    sp3C = temp_f8_2;
    sp34 = sp48->rotationYFrac;
    sp20 = xDiff;
    sp30 = sp48->rotationZFrac;
    sp24 = zDiff;
    sp28 = temp_f6_2;
    sp2C = temp_f8_2;
    temp_f4 = (temp_f8_2 * temp_f0_4) + (sp34 * temp_f2_4) + (sp30 * temp_f12) + sp48->unkC;
    sp2C = sp34;
    sp50 = temp_f4;
    temp_f2_5 = sp28 + (temp_f4 / ((temp_f8_2 * sp20) + (sp34 * yDiff) + (sp30 * zDiff)));
    if (temp_f2_5 != 0.0) {
        var_f0 = sp28 / temp_f2_5;
    } else {
        var_f0 = 0.0f;
    }
    *checkpointDistance = var_f0;
    if ((obj->behaviorId == BHV_RACER) && (obj->unk64->racer.playerIndex == PLAYER_COMPUTER)) {
        if (var_f0 < -0.3) {
            return -100;
        }
        if (var_f0 > 1.3) {
            return -100;
        }
    }
    if (sp28 <= 0.0f) {
        if (sp70) {
            *arg6 = TRUE;
        } else if (sp4C->altRouteID == -1) {
            *arg6 = FALSE;
        }
        temp_f20_2 =
            (sp4C->rotationXFrac * objX) + (sp4C->rotationYFrac * objY) + (sp4C->rotationZFrac * objZ) + sp4C->unkC;

        if (temp_f20_2 > 0.0f) {
            if (obj->behaviorId == BHV_RACER) {
                temp_v0_4 = obj->unk64;
                if (sp4C->unk3B != 0) {
                    temp_v0_4->racer.indicator_type = sp4C->unk3B;
                    temp_v0_4->racer.indicator_timer = 120;
                }
            }
            var_t1 = sp38 + 60; // 60 = max number of checkpoints?
            if ((checkpointIndex + 1) == gNumberOfCheckpoints) {
                var_t1 = 0;
            }
            temp_f0_5 = obj->segment.trans.x_position;
            temp_a1 = &gTrackCheckpoints[var_t1];
            temp_f2_7 = obj->segment.trans.y_position;
            temp_f12 = obj->segment.trans.z_position;
            temp_f10 = (temp_a1->rotationXFrac * obj->segment.trans.x_position) +
                       (temp_a1->rotationYFrac * obj->segment.trans.y_position) +
                       (temp_a1->rotationZFrac * obj->segment.trans.z_position) + temp_a1->unkC;

            sp58 = temp_f10;
            sp2C = temp_f10;
            sp5C = (temp_a1->rotationXFrac * xDiff) + (temp_a1->rotationYFrac * temp_f20_2) +
                   (temp_a1->rotationZFrac * zDiff);
            temp_f10 = -temp_f10 / sp5C;
            sp5C = temp_f10;
            temp_f4_3 = sp4C->rotationXFrac;
            sp3C = temp_f4_3;
            sp34 = sp4C->rotationYFrac;
            sp2C = xDiff;
            sp30 = sp4C->rotationZFrac;
            sp28 = zDiff;
            sp24 = temp_f10;
            sp20 = temp_f4_3;
            temp_f12 = sp24;
            sp24 = sp34;
            temp_f6_3 = (temp_f4_3 * temp_f0_5) + (sp34 * temp_f2_7) + (sp30 * temp_f12) + sp4C->unkC;
            sp50 = temp_f6_3;
            temp_f2_8 = temp_f12 + (temp_f6_3 / ((temp_f4_3 * sp2C) + (sp34 * temp_f20_2) + (sp30 * zDiff)));
            if (temp_f2_8 != 0.0) {
                var_f0 = temp_f12 / temp_f2_8;
            } else {
                var_f0 = 0.0f;
            }
            *checkpointDistance = var_f0;
            return 0;
        }
        *checkpointDistance = 0.0f;
        return 0;
    }
    var_v1 = var_f0 * 100.0f;
    if (var_v1 == 0) {
        var_v1++;
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_800185E4.s")
#endif

/**
 * Search and return Taj's overworld object.
 * Used for drawing his minimap position.
 */
Object *find_taj_object(void) {
    s32 i;
    Object *current_obj;
    for (i = gObjectListStart; i < gObjectCount; i++) {
        current_obj = gObjPtrList[i];
        if (!(current_obj->segment.trans.flags & OBJ_FLAGS_PARTICLE) && (current_obj->behaviorId == BHV_PARK_WARDEN)) {
            return current_obj;
        }
    }
    return NULL;
}

// https://decomp.me/scratch/hcneX
#ifdef NON_EQUIVALENT
// Handles MidiFadePoint, MidiFade, and MidiSetChannel objects?
void func_80018CE0(Object *racerObj, f32 xPos, f32 yPos, f32 zPos, s32 updateRate) {
    s32 spF4;
    f32 spC0;
    void *spBC;
    s32 sp98;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f0_7;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f14_3;
    f32 temp_f14_4;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f2_5;
    f32 temp_f30;
    f32 var_f12;
    // f32 var_f6;
    f32 var_f8;
    s16 behaviorId;
    s32 temp_f10;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s0_4;
    s32 temp_s0_5;
    s32 temp_s0_6;
    s32 temp_t3;
    s32 temp_t3_2;
    s32 temp_t4;
    s32 temp_t8;
    Object_MidiFade *temp_v1_2;
    Object_MidiFade *temp_v1_3;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s2;
    s8 temp_t2_2;
    s8 var_v0_2;
    s8 var_v1;
    u16 temp_t2;
    u16 temp_v0_2;
    s32 var_v0;
    u8 temp_v0_3;
    u8 temp_v0_5;
    u8 temp_v0_6;
    Object *obj;
    Object_MidiFade *midiFade;
    Object_MidiFadePoint *midiFadePoint;
    Object_MidiFadePoint *midiFadePoint2;
    Object_MidiChannelSet *midiChannelSet;

    if (racerObj->unk64->racer.playerIndex == 0) {
        if (cam_get_viewport_layout() == 0) {
            spF4 = gObjectListStart;
            if (gObjectListStart < gObjectCount) {
                sp98 = gObjectListStart * 4;
                do {
                    obj = *(gObjPtrList + sp98);
                    if (!(obj->segment.trans.flags & 0x8000)) {
                        behaviorId = obj->behaviorId;
                        if (behaviorId == BHV_MIDI_FADE_POINT) {
                            temp_f0 = racerObj->segment.trans.x_position - obj->segment.trans.x_position;
                            temp_f2 = racerObj->segment.trans.y_position - obj->segment.trans.y_position;
                            temp_f14 = racerObj->segment.trans.z_position - obj->segment.trans.z_position;
                            temp_f0_2 = sqrtf((temp_f0 * temp_f0) + (temp_f2 * temp_f2) + (temp_f14 * temp_f14));
                            midiFadePoint = &obj->unk64->midi_fade_point;
                            temp_f2_2 = temp_f0_2;
                            temp_t2 = midiFadePoint->unk2;
                            var_f8 = (f32) temp_t2;
                            if ((s32) temp_t2 < 0) {
                                var_f8 += 4294967296.0f;
                            }
                            if (temp_f0_2 < var_f8) {
                                spBC = midiFadePoint;
                                spC0 = temp_f2_2;
                                var_s1 = 0;
                                midiFadePoint2 = midiFadePoint;
                                if (midiFadePoint->unk1C == music_current_sequence()) {
                                    temp_v0_2 = midiFadePoint->unk0;
                                    var_f12 = (f32) temp_v0_2;
                                    if ((s32) temp_v0_2 < 0) {
                                        var_f12 += 4294967296.0f;
                                    }
                                    if (temp_f2_2 <= var_f12) {
                                        var_s2 = 0;
                                    } else {
                                        var_s2 = (s32) ((127.0f * (temp_f2_2 - var_f12)) /
                                                        (f32) (midiFadePoint->unk2 - temp_v0_2));
                                    }
                                    do {
                                        temp_v0_3 = midiFadePoint2->unkC;
                                        if (temp_v0_3 != 1) {
                                            temp_s0_2 = var_s1 & 0xFF;
                                            if (temp_v0_3 != 2) {

                                            } else if ((music_channel_fade(temp_s0_2 & 0xFF) > 0) &&
                                                       (music_channel_active(var_s1) == 0)) {
                                                music_channel_fade_set(temp_s0_2 & 0xFF, var_s2 & 0xFF);
                                            }
                                        } else {
                                            temp_s0_3 = var_s1 & 0xFF;
                                            if (var_s2 >= 0x7B) {
                                                music_channel_off(var_s1 & 0xFF);
                                            } else {
                                                music_channel_fade_set(temp_s0_3 & 0xFF, (0x7F - var_s2) & 0xFF);
                                                music_channel_on(temp_s0_3 & 0xFF);
                                            }
                                        }
                                        var_s1 += 1;
                                        midiFadePoint2 += 1;
                                    } while (var_s1 != 0x10);
                                }
                            }
                        } else if (behaviorId == BHV_MIDI_FADE) {
                            midiFade = &obj->unk64->midi_fade;
                            temp_f16 = midiFade->unkC;
                            temp_f30 = temp_f16 * yPos;
                            temp_f18 = midiFade->unk10;
                            temp_f12 = midiFade->unk8;
                            temp_f14_2 = temp_f18 * zPos;
                            temp_f24 = racerObj->segment.trans.x_position;
                            temp_f26 = racerObj->segment.trans.y_position;
                            temp_f20 = midiFade->unk14;
                            temp_f28 = racerObj->segment.trans.z_position;
                            sp78 = temp_f14_2;
                            temp_f0_3 = (temp_f12 * xPos) + temp_f30 + temp_f14_2 + temp_f20;
                            temp_f2_3 =
                                (temp_f12 * temp_f24) + (temp_f16 * temp_f26) + (temp_f18 * temp_f28) + temp_f20;
                            if ((temp_f0_3 > 0.0f) && (temp_f2_3 <= 0.0f)) {
                                var_v1 = 1;
                            } else {
                                var_v1 = 0;
                                if ((temp_f2_3 > 0.0f) && (temp_f0_3 <= 0.0f)) {
                                    var_v1 = -1;
                                }
                            }
                            if (var_v1 != 0) {
                                sp70 = yPos;
                                temp_f2_4 = temp_f26 - yPos;
                                sp74 = zPos;
                                temp_f0_4 = temp_f24 - xPos;
                                temp_f14_3 = temp_f28 - zPos;
                                temp_f22 = ((((-temp_f12 * xPos) - temp_f30) - sp78) - temp_f20) /
                                           ((temp_f12 * temp_f0_4) + (temp_f16 * temp_f2_4) + (temp_f18 * temp_f14_3));
                                temp_f12_2 = (temp_f22 * temp_f0_4) + xPos;
                                if ((midiFade->unk18 <= temp_f12_2) && (temp_f12_2 <= midiFade->unk24)) {
                                    temp_f0_5 = (temp_f22 * temp_f2_4) + sp70;
                                    if (((f32) midiFade->unk1C <= temp_f0_5) && (temp_f0_5 <= midiFade->unk28)) {
                                        temp_f0_6 = (temp_f22 * temp_f14_3) + sp74;
                                        if ((midiFade->unk20 <= temp_f0_6) && (temp_f0_6 <= midiFade->unk2C)) {
                                            midiFade->unk0 = var_v1;
                                            midiFade->unk1 = 0;
                                            midiFade->unk4 = 0;
                                            D_8011AF60[0] = (s32) midiFade;
                                        }
                                    }
                                }
                            }
                        } else if (behaviorId == BHV_MIDI_CHANNEL_SET) {
                            temp_f0_7 = racerObj->segment.trans.x_position - obj->segment.trans.x_position;
                            temp_f2_5 = racerObj->segment.trans.y_position - obj->segment.trans.y_position;
                            temp_f14_4 = racerObj->segment.trans.z_position - obj->segment.trans.z_position;
                            midiChannelSet = &obj->unk64->midi_channel_set;
                            if ((sqrtf((temp_f0_7 * temp_f0_7) + (temp_f2_5 * temp_f2_5) + (temp_f14_4 * temp_f14_4)) <
                                 (f32) (midiChannelSet->unk2 * 4)) &&
                                (midiChannelSet->unk0 != music_channel_get_mask()) &&
                                (midiChannelSet->unk3 == music_current_sequence())) {
                                music_dynamic_set(midiChannelSet->unk0);
                            }
                        }
                    }
                    temp_t3 = spF4 + 1;
                    sp98 += 4;
                    spF4 = temp_t3;
                } while (temp_t3 < gObjectCount);
            }
            if (D_8011AF60[0] != 0) {
                temp_v1_2 = D_8011AF60[0];
                var_s1_2 = 0;
                if (temp_v1_2->unk40 == music_current_sequence()) {
                    temp_v1_2->unk4 += updateRate;
                    var_v0 = D_8011AF60[0]->unk4;
                    temp_t4 = (D_8011AF60[0]->unk2 * gVideoRefreshRate) & 0xFFFF;
                    if (temp_t4 < (s32) var_v0) {
                        D_8011AF60[0]->unk4 = (u16) temp_t4;
                        var_v0 = D_8011AF60[0]->unk4;
                    }
                    /*
                    var_f6 = (f32) temp_t4;
                    if (temp_t4 < 0) {
                        var_f6 += 4294967296.0f;
                    }
                    */
                    temp_f10 = (s32) (((f32) var_v0 * 254.0f) / temp_t4);
                    if (temp_f10 < 0xFE) {
                        D_8011AF60[0]->unk1 = (s8) temp_f10;
                    } else {
                        D_8011AF60[0]->unk1 = 0xFE;
                    }
                    temp_v1_3 = D_8011AF60[0];
                    do {
                        var_v0_2 = temp_v1_3->unk2F[var_s1_2 + 1];
                        if (temp_v1_3->unk0 == -1) {
                            var_v0_2 = (s8) (var_v0_2 >> 2);
                        }
                        temp_t2_2 = var_v0_2 & 3;
                        if (temp_t2_2 != 0) {
                            temp_s0_4 = var_s1_2 & 0xFF;
                            switch (temp_t2_2) { /* irregular */
                                case 1:
                                    music_channel_on(temp_s0_4 & 0xFF);
                                    music_channel_fade_set(temp_s0_4 & 0xFF, 0x7FU);
                                    break;
                                case 3:
                                    temp_v0_5 = temp_v1_3->unk1;
                                    temp_s0_5 = var_s1_2 & 0xFF;
                                    if ((s32) temp_v0_5 >= 0x80) {
                                        temp_t3_2 = (temp_v0_5 - 0x7F) & 0xFF;
                                        music_channel_on(temp_s0_5 & 0xFF);
                                        if (music_channel_fade(temp_s0_5 & 0xFF) < temp_t3_2) {
                                            music_channel_fade_set(temp_s0_5 & 0xFF, temp_t3_2 & 0xFF);
                                        }
                                    }
                                    break;
                                case 2:
                                    temp_v0_6 = temp_v1_3->unk1;
                                    temp_s0_6 = var_s1_2 & 0xFF;
                                    if ((s32) temp_v0_6 < 0x7F) {
                                        temp_t8 = (0x7F - temp_v0_6) & 0xFF;
                                        if (temp_t8 < music_channel_fade(temp_s0_6 & 0xFF)) {
                                            music_channel_fade_set(temp_s0_6 & 0xFF, temp_t8 & 0xFF);
                                        }
                                    } else {
                                        music_channel_off(var_s1_2 & 0xFF);
                                    }
                                    break;
                            }
                        } else {
                            music_channel_off(var_s1_2 & 0xFF);
                        }
                        var_s1_2 += 1;
                    } while (var_s1_2 != 0x10);
                }
                if ((temp_v1_2->unk1 == 0xFE) && (D_8011AF60[0]->unk40 == music_current_sequence())) {
                    D_8011AF60[0] = 0;
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_80018CE0.s")
#endif

// Rocket Path
s32 func_8001955C(Object *obj, s32 checkpoint, u8 arg2, s32 arg3, s32 arg4, f32 checkpointDist, f32 *outX, f32 *outY,
                  f32 *outZ) {
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

    numCheckpoints = gNumberOfCheckpoints;
    if (numCheckpoints == 0) {
        return FALSE;
    }
    checkpointIndex = checkpoint - 2;
    if (checkpointIndex < 0) {
        checkpointIndex += numCheckpoints;
    }
    for (i = 0; i < 4; i++) {
        checkpointNode = find_next_checkpoint_node(checkpointIndex, arg2);
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
    *outX = (xSpline + dx) - obj->segment.trans.x_position;
    *outY = (ySpline + dy) - obj->segment.trans.y_position;
    *outZ = (zSpline + dz) - obj->segment.trans.z_position;
    return TRUE;
}

// D_B0000574 is a direct read from the ROM as opposed to RAM
extern s32 D_B0000574;

void func_80019808(s32 updateRate) {
    s32 prevUnk1AA;
    s32 i;
    s32 j; // sp94
    s32 newUnk1AA;
    Settings *settings;
    s16 numHumanRacers;         // sp8A
    s16 numHumanRacersFinished; // sp88
    Object_Racer *curRacer2;
    Object_Racer *curRacer; // sp80
    s16 numFinishedRacers;
    s16 foundIndex;
    Object_Racer *racer[4]; // sp6C
    s16 racerIndex;
    s8 raceType;
    s8 someBool;
    LevelHeader *currentLevelHeader; // sp64
    s32 newStartingPosition;
    s8 sp5C[4];
    s8 someBool2; // sp5B
    s8 flags[3];
    s32 camera;

    currentLevelHeader = get_current_level_header();
    settings = get_settings();
    numHumanRacersFinished = 0;
    numHumanRacers = 0;
    someBool2 = currentLevelHeader->race_type;
    numFinishedRacers = 0;
    if (someBool2 != RACETYPE_DEFAULT && someBool2 != RACETYPE_HORSESHOE_GULCH && someBool2 != RACETYPE_BOSS) {
        if (someBool2 & RACETYPE_CHALLENGE) {
            if (someBool2 == RACETYPE_CHALLENGE_EGGS) {
                func_80045128(*gRacers);
            }
            if (D_8011ADB4 == 0) {
                for (i = 0; i < gNumRacers; i++) {
                    racer[i] = &(*gRacers)[i]->unk64->racer;
                    if (currentLevelHeader->race_type == RACETYPE_CHALLENGE_BATTLE && racer[i]->bananas <= 0 &&
                        !racer[i]->raceFinished) {
                        racer[i]->raceFinished = TRUE;
                        racer[i]->balloon_quantity = 0;
                        racer_sound_free((*gRacers)[i]);
                        (*gRacers)[i]->segment.trans.flags |= OBJ_FLAGS_INVISIBLE;
                        (*gRacers)[i]->interactObj->flags = INTERACT_FLAGS_NONE;
                        racer[i]->finishPosition = 5 - D_8011ADC0;
                        D_8011ADC0++;
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
                            racer[i]->finishPosition = D_8011ADC0;
                            D_8011ADC0++;
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
                            if (currentLevelHeader->race_type == RACETYPE_CHALLENGE_BATTLE) {
                                racer[racerIndex]->finishPosition = 5 - D_8011ADC0;
                            } else {
                                racer[racerIndex]->finishPosition = D_8011ADC0;
                            }
                            D_8011ADC0++;
                            racer[racerIndex]->raceFinished = TRUE;
                        }
                        i = 0;
                    } while (racerIndex != -1);

                    gSwapLeadPlayer = FALSE;
                    if (!is_in_tracks_mode() &&
                        (racer[0]->finishPosition == 1 ||
                         is_in_two_player_adventure() && racer[1]->finishPosition == 1) &&
                        (!(settings->courseFlagsPtr[settings->courseId] & RACE_CLEARED))) {
                        settings->courseFlagsPtr[settings->courseId] |= RACE_CLEARED;
                        i = settings->ttAmulet + 1;
                        if (i > 4) {
                            i = 4;
                        }
                        settings->ttAmulet = i;
                    }
                    for (newUnk1AA = 0; newUnk1AA < 8;) {
                        settings->racers[newUnk1AA++].starting_position = -1;
                    }

                    newStartingPosition = SEQUENCE_BATTLE_LOSE;
                    for (newUnk1AA = 0; newUnk1AA < gNumRacers; newUnk1AA++) {
                        if (racer[newUnk1AA]->playerIndex != PLAYER_COMPUTER && racer[newUnk1AA]->finishPosition == 1) {
                            newStartingPosition = SEQUENCE_BATTLE_VICTORY;
                        }
                        settings->racers[newUnk1AA].starting_position = racer[newUnk1AA]->finishPosition - 1;
                    }

                    music_play(newStartingPosition);
                    newStartingPosition = 4;
                    for (prevUnk1AA = 0; prevUnk1AA < 8; prevUnk1AA++) {
                        if (settings->racers[prevUnk1AA].starting_position == -1) {
                            settings->racers[prevUnk1AA].starting_position = newStartingPosition;
                            newStartingPosition++;
                        }
                    }

                    gSwapLeadPlayer = 0;
                    if (is_in_two_player_adventure() && settings->racers[PLAYER_TWO].starting_position <
                                                            settings->racers[PLAYER_ONE].starting_position) {
                        gSwapLeadPlayer = 1;
                    }
                    if (i == 0) {
                        if (is_in_two_player_adventure()) {
                            if (gSwapLeadPlayer) {
                                gSwapLeadPlayer = 0;
                                swap_lead_player();
                                if (D_800DC73C != 0) {
                                    D_800DC748 = TRUE;
                                }
                            } else if (D_800DC73C != 0) {
                                D_800DC748 = TRUE;
                            }
                        }
                        postrace_start(0, 30);
                    } else {
                        push_level_property_stack(SPECIAL_MAP_ID_NO_LEVEL, 0, VEHICLE_CAR, CUTSCENE_ID_NONE);
                        push_level_property_stack(ASSET_LEVEL_TTAMULETSEQUENCE, 0, VEHICLE_NO_OVERRIDE,
                                                  settings->ttAmulet - 1);
                        race_finish_adventure(1);
                    }
                    D_8011ADB4 = 1;
                }
            }
        }
        return;
    }

    i = 0;
    do {
        newUnk1AA = 1;
        curRacer = &(*gRacers)[i]->unk64->racer;
        prevUnk1AA = curRacer->unk1AA;
        j = 0;
        do {
            if (j != i) {
                curRacer2 = &(*gRacers)[j]->unk64->racer;
                if (curRacer->raceFinished == FALSE && curRacer2->raceFinished != FALSE) {
                    newUnk1AA++;
                } else if (curRacer->courseCheckpoint < curRacer2->courseCheckpoint) {
                    newUnk1AA++;
                } else if (curRacer->courseCheckpoint == curRacer2->courseCheckpoint) {
                    if (curRacer2->unk1A8 < curRacer->unk1A8) {
                        newUnk1AA++;
                    }
                    if (curRacer->unk1A8 == curRacer2->unk1A8 && i < j) {
                        newUnk1AA++;
                    }
                }
            }
            j++;
        } while (j < gNumRacers);

        curRacer->unk1AA = newUnk1AA;
        if (curRacer->lap < currentLevelHeader->laps) {
            if (prevUnk1AA == curRacer->unk1AA) {
                if (curRacer->unk1B0 < 2) {
                    if (curRacer->vehicleID != VEHICLE_LOOPDELOOP) {
                        curRacer->unk1B0++;
                    }
                } else if (curRacer->unk1AA != curRacer->racePosition) {
                    curRacer->unk1B2 = 10;
                    curRacer->racePosition = curRacer->unk1AA;
                }
            } else {
                curRacer->unk1B0 = 0;
            }
        }
        i++;
    } while (i < gNumRacers);

    i = 0;
    do {
        curRacer = &(*gRacers)[i]->unk64->racer;
        if (curRacer->lap >= currentLevelHeader->laps && curRacer->raceFinished == FALSE) {
            if (get_game_mode() != GAMEMODE_UNUSED_4) {
                curRacer->raceFinished = TRUE;
                curRacer->finishPosition = D_8011ADC0;
                if (D_8011ADC0 == 1 && curRacer->playerIndex == PLAYER_COMPUTER) {
                    sound_play(SOUND_WHOOSH5, NULL);
                }
                D_8011ADC0++;
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
        curRacer = &(*gRacers)[i]->unk64->racer;
        if (curRacer->raceFinished) {
            newUnk1AA = curRacer->finishPosition - 1;
        } else {
            newUnk1AA = curRacer->unk1AA - 1;
        }
        gRacersByPosition[newUnk1AA] = (*gRacers)[i];
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
        curRacer = &(*gRacers)[0]->unk64->racer;
        if (!curRacer->raceFinished) {
            curRacer->raceFinished = TRUE;
            curRacer->finishPosition = D_8011ADC0;
            D_8011ADC0 += 1;
        }
    } else if (D_8011ADB4 == 0) {
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
                    curRacer = &gRacersByPosition[i]->unk64->racer;
                    if (curRacer->raceFinished == FALSE) {
                        if (curRacer->playerIndex >= 0) {
                            set_active_camera(curRacer->playerIndex);
                            camera = cam_get_active_camera_no_cutscenes();
                            // we need the camera to be a s32 for the WAIT_ON_IOBUSY anti tamper call to work
                            // but we *know* that cam_get_active_camera_no_cutscenes returns a Camera pointer so this
                            // should be safe
                            ((Camera *) camera)->mode = CAMERA_FINISH_CHALLENGE;
                        }
                        curRacer->raceFinished = TRUE;
                        curRacer->finishPosition = D_8011ADC0;
                        D_8011ADC0++;
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
                    curRacer = &gRacersByPosition[i]->unk64->racer;
                    newUnk1AA = curRacer->racerIndex;
                    settings->racers[newUnk1AA].starting_position = i;
                    i++;
                } while (i < gNumRacers);
            }
            gSwapLeadPlayer = FALSE;
            flags[2] = raceType;
            if (is_in_two_player_adventure() &&
                (settings->racers[PLAYER_TWO].starting_position < settings->racers[PLAYER_ONE].starting_position)) {
                gSwapLeadPlayer = TRUE;
            }
            curRacer = &(*gRacersByPosition)->unk64->racer;
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
                        if (D_800DC73C) {
                            D_800DC748 = TRUE;
                        }
                    } else if (D_800DC73C) {
                        D_800DC748 = TRUE;
                    }
                }
                postrace_start(gFirstTimeFinish, 30);
            } else {
                settings->balloonsPtr[settings->worldId]++;
                if (settings->worldId != 0) {
                    settings->balloonsPtr[0]++;
                }
                race_finish_adventure(1);
            }
            D_8011ADB4 = -1;
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

    racer = &gRacersByPosition[PLAYER_ONE]->unk64->racer;
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
            racer = &(*gRacers)[i]->unk64->racer;
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
            racer = &prevRacer0Obj->unk64->racer;
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
        racer = &prevPort0Racer->unk64->racer;
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
        if (!(get_current_level_race_type() & RACETYPE_CHALLENGE_BATTLE)) {
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

    levelHeader = get_current_level_header();
    settings = get_settings();
    settings->timeTrialRacer = 0;
    settings->unk115[1] = 0;
    settings->unk115[0] = 0;
    bestCourseTime = 36001;
    bestRacerTime = 36001;
    bestRacer = &gRacersByPosition[0]->unk64->racer;
    for (i = 0; i < gNumRacers; i++) {
        curRacer = &gRacersByPosition[i]->unk64->racer;
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
            if (bestCourseTime < 10800 &&
                (vehicleID != gTimeTrialVehicle || timetrial_map_id() != get_current_map_id() ||
                 bestCourseTime < gTimeTrialTime)) {
                gTimeTrialTime = bestCourseTime;
                gTimeTrialVehicle = gPrevTimeTrialVehicle;
                gTimeTrialCharacter = settings->racers[0].character;
                timetrial_swap_player_ghost(get_current_map_id());
                gHasGhostToSave = TRUE;
            }
            if (osTvType == OS_TV_TYPE_PAL) {
                bestCourseTime = (bestCourseTime * 6) / 5;
            }
            if (bestCourseTime < gTTGhostTimeToBeat) {
                if (gTimeTrialStaffGhost) {
                    tt_ghost_beaten(get_current_map_id(), &bestRacer->playerIndex);
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
    if (timetrial_map_id() != get_current_map_id()) {
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

    gMapDefaultVehicle = get_map_default_vehicle(mapId);
    ghostTable = (TTGhostTable *) load_asset_section_from_rom(ASSET_TTGHOSTS_TABLE);

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
    if (get_map_default_vehicle(trackId) == (Vehicle) gPrevTimeTrialVehicle) {
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
    if (get_current_map_id() != ghostMapID || gTimeTrialVehicle != gPrevTimeTrialVehicle) {
        cpakStatus =
            timetrial_load_player_ghost(playerID, get_current_map_id(), gPrevTimeTrialVehicle, &characterID, &time);
        if (cpakStatus == CONTROLLER_PAK_GOOD) {
            gTimeTrialVehicle = gPrevTimeTrialVehicle;
            gTimeTrialCharacter = characterID;
            gTimeTrialTime = time;
        }
        return cpakStatus;
    }
    return timetrial_load_player_ghost(playerID, get_current_map_id(), gPrevTimeTrialVehicle, NULL, NULL);
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

Object *func_8001B7A8(Object_Racer *racer, s32 position, f32 *distance) {
    UNUSED s32 pad;
    Object *tempRacerObj;
    position = (racer->unk1AA - position) - 1;
    if (position < 0 || position >= gNumRacers) {
        return NULL;
    }
    tempRacerObj = gRacersByPosition[position];
    if (tempRacerObj == NULL) {
        return NULL;
    }
    *distance = func_8001B834(racer, &tempRacerObj->unk64->racer);
    return tempRacerObj;
}

f32 func_8001B834(Object_Racer *racer1, Object_Racer *racer2) {
    Object_Racer *temp_racer;
    f32 var_f2;
    s32 r1_ccp;
    UNUSED s32 temp_lo;
    s32 var_v1;
    s32 checkpointID;

    if (gNumberOfCheckpoints <= 0) {
        return 0.0f;
    }
    var_f2 = 0.0f;
    var_v1 = FALSE;
    if (racer2->courseCheckpoint < racer1->courseCheckpoint) {
        temp_racer = racer1;
        racer1 = racer2;
        racer2 = temp_racer;
        var_v1 = TRUE;
    }
    checkpointID = racer1->checkpoint;
    for (r1_ccp = racer1->courseCheckpoint; r1_ccp < racer2->courseCheckpoint; r1_ccp++) {
        var_f2 += gTrackCheckpoints[checkpointID++].distance;
        if (checkpointID == gNumberOfCheckpoints) {
            checkpointID = 0;
        }
    }
    checkpointID = racer1->checkpoint - 1;
    if (checkpointID < 0) {
        checkpointID = gNumberOfCheckpoints - 1;
    }
    var_f2 += (gTrackCheckpoints[checkpointID].distance * racer1->checkpoint_distance);
    checkpointID = racer2->checkpoint - 1;
    if (checkpointID < 0) {
        checkpointID = gNumberOfCheckpoints - 1;
    }
    var_f2 -= (gTrackCheckpoints[checkpointID].distance * racer2->checkpoint_distance);
    if (var_v1) {
        var_f2 = -var_f2;
    }
    return var_f2;
}

UNUSED f32 func_8001B954(Object_Racer *racer) {
    f32 distLeft;
    s32 checkpointID;

    if (gNumberOfCheckpoints <= 0) {
        return 0.0f;
    }
    distLeft = 0.0f;
    for (checkpointID = racer->checkpoint; checkpointID < gNumberOfCheckpoints; checkpointID++) {
        distLeft += gTrackCheckpoints[checkpointID].distance;
    }
    checkpointID = racer->checkpoint - 1;
    if (checkpointID < 0) {
        checkpointID = gNumberOfCheckpoints - 1;
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
CheckpointNode *find_next_checkpoint_node(s32 splinePos, s32 arg1) {
    CheckpointNode *checkpointNode = &gTrackCheckpoints[splinePos];
    if (arg1 != 0 && checkpointNode->altRouteID != -1) {
        checkpointNode = &gTrackCheckpoints[checkpointNode->altRouteID];
    }
    return checkpointNode;
}

/**
 * Returns the number of active checkpoints in the current level.
 */
s32 get_checkpoint_count(void) {
    return gNumberOfCheckpoints;
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
    if (gNumberOfCheckpoints > 3) {
        for (i = 0; i < gNumberOfCheckpoints; i++) {
            // Ground path
            debug_render_checkpoint_node(i, 0, dList, mtx, vtx);
        }
        for (i = 0; i < gNumberOfCheckpoints; i++) {
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
        if (!(objPtr->segment.trans.flags & OBJ_FLAGS_PARTICLE)) {
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
    x = currCamera->segment.trans.x_position - obj->segment.trans.x_position;
    y = currCamera->segment.trans.y_position - obj->segment.trans.y_position;
    z = currCamera->segment.trans.z_position - obj->segment.trans.z_position;
    currCameraXYZ = (x * x) + (y * y) + (z * z);
    x = nextCamera->segment.trans.x_position - obj->segment.trans.x_position;
    y = nextCamera->segment.trans.y_position - obj->segment.trans.y_position;
    z = nextCamera->segment.trans.z_position - obj->segment.trans.z_position;
    nextCameraXYZ = (x * x) + (y * y) + (z * z);
    x = prevCamera->segment.trans.x_position - obj->segment.trans.x_position;
    y = prevCamera->segment.trans.y_position - obj->segment.trans.y_position;
    z = prevCamera->segment.trans.z_position - obj->segment.trans.z_position;
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
        if (!(obj->segment.trans.flags & OBJ_FLAGS_PARTICLE) && obj->behaviorId == BHV_AINODE) {
            aiNodeEntry = &obj->segment.level_entry->aiNode;
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
            aiNodeObj64 = &obj->unk64->ai_node;
            aiNodeEntry = &obj->segment.level_entry->aiNode;
            for (j = 0; j < 4; j++) {
                index2 = aiNodeEntry->adjacent[j];
                if (!(index2 & AINODE_COUNT)) {
                    nextAiNodeObj = (*gAINodes)[index2];
                    aiNodeObj64->nodeObj[j] = nextAiNodeObj;
                    if (nextAiNodeObj == NULL) {
                        aiNodeEntry->adjacent[j] = -1;
                    } else {
                        diffX = obj->segment.trans.x_position - nextAiNodeObj->segment.trans.x_position;
                        diffY = obj->segment.trans.y_position - nextAiNodeObj->segment.trans.y_position;
                        diffZ = obj->segment.trans.z_position - nextAiNodeObj->segment.trans.z_position;
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
            if ((*gAINodes)[nodeIDs[i + 1]]->segment.trans.y_position <
                (*gAINodes)[nodeIDs[i]]->segment.trans.y_position) {
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
            gElevationHeights[index] = ((*gAINodes)[nodeIDs[i]]->segment.trans.y_position +
                                        (*gAINodes)[nodeIDs[i - 1]]->segment.trans.y_position) *
                                       0.5;
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
    ObjectSegment *segment;
    LevelObjectEntry_AiNode *levelObj;

    if (useElevation) {
        elevation = obj_elevation(diffY);
    }
    dist = 50000.0;
    result = 0xFF;
    for (numSteps = 0; numSteps != AINODE_COUNT; numSteps++) {
        segment = &(*gAINodes)[numSteps]->segment;
        if (segment) {
            levelObj = &((segment->level_entry)->aiNode);
            findDist = TRUE;
            if (useElevation && elevation != levelObj->elevation) {
                findDist = FALSE;
            }
            if (useElevation == 2 && levelObj->unk8 != 3) {
                findDist = FALSE;
            }
            if (findDist) {
                x = segment->trans.x_position - diffX;
                y = segment->trans.y_position - diffY;
                z = segment->trans.z_position - diffZ;
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

        xPositions[i] = aiNode->segment.trans.x_position;
        yPositions[i] = aiNode->segment.trans.y_position;
        zPositions[i] = aiNode->segment.trans.z_position;
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

    xDiff = xDiff2 - npcParentObj->segment.trans.x_position;
    yDiff = yDiff2 - npcParentObj->segment.trans.y_position;
    zDiff = zDiff2 - npcParentObj->segment.trans.z_position;

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
        var_s0 = (arctan2_f(xDiff, zDiff) - (npcParentObj->segment.trans.rotation.y_rotation & 0xFFFF)) - 0x8000;
        if (var_s0 > 0x8000) {
            var_s0 -= 0xFFFF;
        }
        if (var_s0 < -0x8000) {
            var_s0 += 0xFFFF;
        }
        npcParentObj->segment.trans.rotation.y_rotation += ((var_s0 * (s32) updateRateF)) >> 4;
        var_s0 = arctan2_f(yDiff, 255.0f) - (npcParentObj->segment.trans.rotation.x_rotation & 0xFFFF);
        if (var_s0 > 0x8000) {
            var_s0 -= 0xFFFF;
        }
        if (var_s0 < -0x8000) {
            var_s0 += 0xFFFF;
        }
        npcParentObj->segment.trans.rotation.x_rotation += ((var_s0 * (s32) updateRateF)) >> 4;
    }

    npcParentObj->segment.trans.rotation.z_rotation = 0;
    xDiff = sins_f((s16) (npcParentObj->segment.trans.rotation.y_rotation + 0x8000)) * dist;
    move_object(npcParentObj, xDiff * updateRateF, 0.0f,
                coss_f((npcParentObj->segment.trans.rotation.y_rotation + 0x8000)) * dist * updateRateF);
    npcParentObj->segment.trans.y_position = tempYDiff;
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

    entry = &aiNodeObj->segment.level_entry->aiNode;
    aiNode = &aiNodeObj->unk64->ai_node;
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
    aiNode = &aiNodeObj->unk64->ai_node;
    aiNodeEntry = &aiNodeObj->segment.level_entry->aiNode;
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
            aiNodeEntry = &aiNodeObj->segment.level_entry->aiNode;
            var_s3 = sp54[var_t1];
            var_ra = sp154[aiNodeEntry->nodeID];
            aiNode = &aiNodeObj->unk64->ai_node;
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
        aiNodeEntry = &aiNodeObj->segment.level_entry->aiNode;
        aiNode = &aiNodeObj->unk64->ai_node;
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
        if (obj->segment.header->unk3D != 0) {
            obj->shading->lightR = obj->segment.header->unk3A;
            obj->shading->lightG = obj->segment.header->unk3B;
            obj->shading->lightB = obj->segment.header->unk3C;
            obj->shading->lightIntensity = obj->segment.header->unk3D;
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
        if (object->segment.header->directionalPointLighting) {
            // Dynamic directional lighting for some objects (Intro diddy, Taj, T.T., Bosses)
            calc_dynamic_lighting_for_object_1(object, model, arg2, object, intensity, 1.0f);
        } else {
            // Dynamic ambient lighting for other objects (Racers, Rare logo, Wizpig face, etc.)
            calc_dynamic_lighting_for_object_2(object, model, arg2, intensity);
        }
    }

    if (environmentMappingEnabled) {
        // Calculates environment mapping for the object
        calc_env_mapping_for_object(model, object->segment.trans.rotation.z_rotation,
                                    object->segment.trans.rotation.x_rotation,
                                    object->segment.trans.rotation.y_rotation);
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
    normals = model->unk40;
    normIdx = 0;

    direction.x = -(object->shading->lightDirX << 3);
    direction.y = -(object->shading->lightDirY << 3);
    direction.z = -(object->shading->lightDirZ << 3);
    objRot.y_rotation = -object->segment.trans.rotation.y_rotation;
    objRot.x_rotation = -object->segment.trans.rotation.x_rotation;
    objRot.z_rotation = -object->segment.trans.rotation.z_rotation;
    vec3f_rotate_ypr(&objRot, &direction);

    if (object->segment.header->unk3D != 0 && arg2) {
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
    model40Entries = model->unk40;
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
        if (!(obj->segment.trans.flags & OBJ_FLAGS_PARTICLE)) {
            if (obj->behaviorId == BHV_RACER) {
                racer = &obj->unk64->racer;
                if (player == racer->playerIndex) {
                    *x = obj->segment.trans.x_position;
                    *y = obj->segment.trans.y_position;
                    *z = obj->segment.trans.z_position;
                    *angleZ = obj->segment.trans.rotation.z_rotation;
                    *angleX = obj->segment.trans.rotation.x_rotation;
                    *angleY = obj->segment.trans.rotation.y_rotation;
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

s32 func_8001E2EC(s32 arg0) {
    if (arg0 >= 0 && arg0 < 8) {
        if (D_8011ADCC[0][arg0] > 0) {
            D_8011ADCC[0][arg0]--;
        }
        return D_8011ADCC[0][arg0];
    }
    return 0;
}

void func_8001E344(s32 arg0) {
    if (arg0 >= 0 && arg0 < 8) {
        D_8011ADCC[0][arg0] = 8;
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

        if (current_obj != NULL && !(current_obj->segment.trans.flags & OBJ_FLAGS_PARTICLE) &&
            current_obj->behaviorId == BHV_RAMP_SWITCH && current_obj->properties.common.unk0 == timing) {
            *x = current_obj->segment.trans.x_position;
            *y = current_obj->segment.trans.y_position;
            *z = current_obj->segment.trans.z_position;
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
        gObjPtrList[i]->segment.trans.flags &= ~OBJ_FLAGS_UNK_2000;
    }
    for (i = 0; i < gObjectCount; i++) {
        obj = gObjPtrList[i];
        if (obj != NULL && !(obj->segment.trans.flags & OBJ_FLAGS_PARTICLE) && obj->behaviorId == BHV_ANIMATION) {
            entryAnimation = &obj->segment.level_entry->animation;
            if (entryAnimation->channel != gCutsceneID && entryAnimation->channel != 20) {
                obj->segment.trans.flags |= OBJ_FLAGS_UNK_2000;
                if (obj->unk64 != NULL) {
                    obj->unk64->animation2.flags |= OBJ_FLAGS_UNK_2000;
                }
            }
        }
    }
    curObjCount = gObjectCount - 1;
    lastObjCount = curObjCount;
    for (i = 0; curObjCount >= i;) {
        for (j = 0; lastObjCount >= i && (j == 0);) {
            if (gObjPtrList[i]->segment.trans.flags & OBJ_FLAGS_UNK_2000) {
                i++;
            } else {
                j = -1;
            }
        }
        for (j = 0; curObjCount >= 0 && j == 0;) {
            if (gObjPtrList[curObjCount]->segment.trans.flags & OBJ_FLAGS_UNK_2000) {
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
    Object_Animation *animation;

    for (i = 0; i < D_8011AE00; i++) {
        overridePosObj = D_8011ADD8[i];
        overridePosEntry = &overridePosObj->segment.level_entry->overridePos;
        overridePos = &overridePosObj->unk64->override_pos;
        if ((overridePosEntry->cutsceneId == gCutsceneID) || ((overridePosEntry->cutsceneId == 20))) {
            for (j = 0; (j < D_8011AE78) &&
                        (overridePosEntry->behaviorId != D_8011AE74[j]->properties.animatedObj.behaviourID);
                 j++) {}
            if (j != D_8011AE78 && D_8011AE74[j]->unk64 != NULL) {
                someBool = (D_8011AE74[j]->unk64->animation.unk5C) ? FALSE : TRUE;
                if (arg0 != someBool) {
                    animation = &D_8011AE74[j]->unk64->animation;
                    overridePos->x = animation->x;
                    overridePos->y = animation->y;
                    overridePos->z = animation->z;
                    overridePos->anim = animation;
                    animation->x = overridePosObj->segment.trans.x_position;
                    animation->y = overridePosObj->segment.trans.y_position;
                    animation->z = overridePosObj->segment.trans.z_position;
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
    Object_8001E89C_64 *obj64;

    // some flag, flips to 1 when loading a new zone
    if (D_8011AE01 != FALSE) {
        D_8011AE01 = FALSE;
        return;
    }

    // loading (boss) cutscene
    for (i = 0; i < D_8011AE00; i++) {
        obj = D_8011ADD8[i];
        obj64 = &obj->unk64->obj8001E89C_64;

        if (obj64->unkC != NULL) {
            obj64->unkC->unkC = obj64->unk0;
            obj64->unkC->unk10 = obj64->unk4;
            obj64->unkC->unk14 = obj64->unk8;
        }
    }
}

// https://decomp.me/scratch/OKbBN
#ifdef NON_EQUIVALENT
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
    Object *animObj2;
    LevelObjectEntry_Animation *animation1; // Not 100% positive this is an animation yet.
    LevelObjectEntry_Animation *animation2; // Not 100% positive this is an animation yet.

    if (D_8011AE7E) {
        for (numOfObjs = 0; numOfObjs < D_8011AE78; numOfObjs++) {
            obj = D_8011AE74[numOfObjs];
            animation1 = &obj->segment.level_entry->animation;
            if (obj->unk64 != NULL && animation1->channel != 20) {
                animObj1 = (Object *) obj->unk64;
                free_object(animObj1);
                obj->unk64 = NULL;
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
            if (!(gObjPtrList[i]->segment.trans.flags & OBJ_FLAGS_PARTICLE)) {
                if (gObjPtrList[i]->behaviorId == BHV_OVERRIDE_POS) {
                    overridePos = &gObjPtrList[i]->segment.level_entry->overridePos;
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
            if (!(gObjPtrList[i]->segment.trans.flags & OBJ_FLAGS_PARTICLE)) {
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
            animObj1 = D_8011AE74[i + 0];
            animObj2 = D_8011AE74[i + 1];
            animation1 = &animObj1->segment.level_entry->animation;
            animation2 = &animObj2->segment.level_entry->animation;
            animActorIndex1 = animation1->actorIndex;
            animActorIndex2 = animation2->actorIndex;

            if (animation1->channel == 20) {
                animActorIndex1 -= 400;
            }
            if (animation2->channel == 20) {
                animActorIndex2 -= 400;
            }

            if (!gCutsceneID && !gCutsceneID) {} // fake

            if (animActorIndex2 < animActorIndex1) {
                D_8011AE74[i] = animObj2;
                D_8011AE74[i + 1] = animObj1;
                stopLooping = FALSE;
            } else if (animActorIndex1 == animActorIndex2) {
                if (animation2->order < animation1->order) {
                    D_8011AE74[i] = animObj2;
                    D_8011AE74[i + 1] = animObj1;
                    stopLooping = FALSE;
                } else if (animation1->order == animation2->order && (animObj2->properties.animatedObj.action == 1 ||
                                                                      animObj1->properties.animatedObj.action == 2)) {
                    D_8011AE74[i] = animObj2;
                    D_8011AE74[i + 1] = animObj1;
                    stopLooping = FALSE;
                }
            }
        }
    } while (stopLooping == FALSE);

    var_a0 = -101;
    for (i = 0; i < numOfObjs; i++) {
        animation1 = &D_8011AE74[i]->segment.level_entry->animation;
        if (animation1->actorIndex != var_a0) {
            var_a0 = animation1->actorIndex;
            sp28 = 0;
        }
        animation1->order = sp28++; // It is possible that sp28 could not be initalized?
        D_8011AE74[i]->properties.animatedObj.action = 0;
        if (!i) {} // fake
    }

    D_8011AE78 = numOfObjs;
    if (D_8011AE7E) {
        func_8001EE74();
    }
    D_8011AE7E = FALSE;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_8001E93C.s")
#endif

void func_8001EE74(void) {
    LevelObjectEntry_Animation *animation;
    Object *obj;
    s32 i;

    for (i = 0; i < D_8011AE78; i++) {
        obj = D_8011AE74[i];
        animation = &obj->segment.level_entry->animation;
        if (obj->unk64 == NULL && animation->order == 0 && animation->objectIdToSpawn != -1) {
            func_8001F23C(obj, animation);
        }
        if (D_8011AD26 || animation->channel != 20) {
            if (obj->unk64 != NULL) {
                obj_init_animcamera(obj, (Object *) obj->unk64);
            }
        }
    }
    D_8011AD26 = FALSE;
}

void obj_init_animcamera(Object *arg0, Object *animObj) {
    LevelObjectEntry_Animation *animEntry;
    Object_Animation *anim;
    f32 scale;

    animEntry = &arg0->segment.level_entry->animation;
    anim = &animObj->unk64->animation;
    scale = animEntry->scale & 0xFF;
    if (scale < 1.0f) {
        scale = 1.0f;
    }
    scale /= 64;
    animObj->segment.trans.scale = animObj->segment.header->scale * scale;
    animObj->properties.common.unk0 = 0;
    animObj->properties.common.unk4 = 0;
    if (animEntry->unk22 >= 2 && animEntry->unk22 < 10) {
        animObj->properties.common.unk0 = animEntry->unk22 - 1;
    }
    if (animEntry->unk22 >= 10 && animEntry->unk22 < 18) {
        animObj->properties.common.unk0 = animEntry->unk22 - 9;
    }
    animObj->segment.trans.x_position = arg0->segment.trans.x_position;
    animObj->segment.trans.y_position = arg0->segment.trans.y_position;
    animObj->segment.trans.z_position = arg0->segment.trans.z_position;
    animObj->segment.trans.rotation.y_rotation = arg0->segment.trans.rotation.y_rotation;
    animObj->segment.trans.rotation.z_rotation = arg0->segment.trans.rotation.z_rotation;
    animObj->segment.trans.rotation.x_rotation = arg0->segment.trans.rotation.x_rotation;
    anim->unk26 = 0;
    anim->unk3D = animEntry->channel;
    anim->unk28 = animEntry->actorIndex;
    anim->unk8 = (f32) animEntry->nodeSpeed * 0.1;
    anim->startDelay = normalise_time(animEntry->animationStartDelay);
    animObj->segment.object.animationID = animEntry->objAnimIndex;
    animObj->segment.animFrame = animEntry->unk16;
    anim->z = animEntry->objAnimSpeed;
    anim->y = 0;
    anim->unk2C = animEntry->objAnimLoopType;
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
    arg0->particleEmitter = NULL;
    anim->pauseCounter = normalise_time(animEntry->pauseFrameCount);
    anim->unk3A = animEntry->specialHide;
    if (animEntry->unk13 >= 0) {
        anim->unk2F = animEntry->unk13;
    }
    anim->unk39 = animEntry->unk1F;
    anim->unk38 = animEntry->unk1E;
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
    anim->unk1C = arg0;
    anim->unk45 = 0;
}

void func_8001F23C(Object *obj, LevelObjectEntry_Animation *animEntry) {
    s32 i;
    LevelObjectEntryCommon newObjEntry;
    Object *newObj;
    Object_AnimCamera *camera;
    s32 viewportCount;

    NEW_OBJECT_ENTRY(newObjEntry, animEntry->objectIdToSpawn, 8, animEntry->common.x, animEntry->common.y,
                     animEntry->common.z);

    obj->unk64 = (Object_64 *) spawn_object(&newObjEntry, 1);
    newObj = (Object *) obj->unk64;
    // (newObj->behaviorId == BHV_DINO_WHALE) is Dinosaur1, Dinosaur2, Dinosaur3, Whale, and Dinoisle
    if (obj->unk64 != NULL && newObj->behaviorId == BHV_DINO_WHALE && gTimeTrialEnabled) {
        free_object(newObj);
        obj->unk64 = NULL;
        newObj = NULL;
    }
    if (newObj != NULL) {
        newObj->segment.level_entry = NULL;
        obj_init_animcamera(obj, newObj);
        if (newObj->segment.header->behaviorId == BHV_CAMERA_ANIMATION) {
            camera = &newObj->unk64->anim_camera;
            camera->unk44 = D_8011AD3E;
            viewportCount = cam_get_viewport_layout();
            if (is_two_player_adventure_race()) {
                viewportCount = VIEWPORT_LAYOUT_2_PLAYERS;
            }
            for (i = 0; i < viewportCount;) {
                newObj = spawn_object(&newObjEntry, OBJECT_SPAWN_UNK01);
                if (newObj != NULL) {
                    newObj->segment.level_entry = NULL;
                    obj_init_animcamera(obj, newObj);
                    camera = &newObj->unk64->anim_camera;
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
        if (D_8011AE74[i]->properties.common.unk4 == arg0) {
            count++;
        }
    }

    return count;
}

void func_8001F450(void) {
    D_8011AD53 = 1;
}

// https://decomp.me/scratch/ExBnA
#ifdef NON_EQUIVALENT
s32 func_8001F460(Object *arg0, s32 arg1, Object *arg2) {
    s32 sp174;
    s32 sp168;
    f32 sp154;
    f32 sp140;
    f32 sp12C;
    f32 sp124;
    f32 sp120;
    f32 sp11C;
    f32 sp114;
    f32 sp108; // guessed f32
    f32 spF4;
    f32 spE4;
    f32 *spE0;
    f32 spD0;
    f32 *spCC;
    f32 spBC;
    f32 *spB8;
    f32 spB4;
    s16 spAA;
    s16 spA8;
    s8 spA7;
    s8 spA6;
    s8 spA5;
    u8 spA4;
    f32 *sp88;
    s32 sp80;
    f32 *sp7C;
    f32 *sp78;
    f32 *sp74;
    f32 *sp70;
    f32 *sp6C;
    f32 *sp68;
    s32 sp5C;
    f32 *var_ra_2;
    f32 *var_t4_2;
    f32 *var_t5_2;
    ALSoundState *temp_a0;
    ALSoundState *temp_a0_2;
    f32 temp_f2;
    Camera *var_v1_2;
    Object **var_a0;
    LevelObjectEntry *temp_s1_4;
    LevelObjectEntry_Animation *temp_s1;
    Object *temp_v0_15;
    Object *var_v1_3;
    Object **temp_a0_4;
    Object **temp_a2;
    Object **temp_v0_11;
    Object **temp_v0_12;
    Object **temp_v0_14;
    Object **var_a0_2;
    ObjectModel *temp_a0_3;
    Object_64 *temp_s3;
    Object_64 *temp_v1_7;
    Object_68 *temp_v1_4;
    f32 temp_f0;
    f32 temp_f0_10;
    f32 temp_f0_11;
    f32 temp_f0_12;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f0_7;
    f32 temp_f0_8;
    f32 temp_f10;
    f32 temp_f10_2;
    f32 temp_f10_3;
    f32 temp_f10_4;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f6;
    f32 temp_f6_2;
    f32 temp_f6_3;
    f32 temp_f6_4;
    f32 temp_f6_5;
    f32 temp_f6_6;
    f32 temp_f8;
    f32 temp_f8_2;
    f32 temp_f8_3;
    f32 temp_f8_4;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 var_f0_4;
    f32 var_f20;
    f32 var_f6;
    f32 *var_a3;
    f32 *var_ra;
    f32 *var_t1;
    f32 *var_t2;
    f32 *var_t3;
    f32 *var_t4;
    f32 *var_t5;
    f32 *var_v0_3;
    f32 *var_v0_4;
    f32 *var_v0_5;
    f32 *var_v0_6;
    f32 *var_v0_7;
    f32 *var_v0_8;
    f32 temp_f0_9;
    f32 temp_f2_5;
    f32 temp_f2_6;
    f32 temp_f2_7;
    s16 temp_a1;
    s16 temp_v0_10;
    s16 temp_v0_18;
    s16 temp_v0_3;
    s16 temp_v0_7;
    s16 var_s2_3;
    s16 var_t0_5;
    s32 temp_a1_2;
    s32 temp_s0;
    s32 temp_s2;
    s32 temp_t0;
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_t7_2;
    s32 temp_t7_3;
    s32 temp_t7_4;
    s32 temp_v0_13;
    s32 temp_v0_16;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s0_5;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s4;
    s32 var_s5;
    s32 var_t0;
    s32 var_t0_4;
    s32 var_t0_6;
    s32 var_v0;
    s32 var_v0_2;
    s8 temp_v0_17;
    s8 temp_v0_19;
    s8 temp_v0_4;
    s8 temp_v0_5;
    s8 temp_v0_8;
    s8 temp_v0_9;
    s8 temp_v1;
    s8 temp_v1_2;
    s8 temp_v1_3;
    s8 var_t0_3;
    s8 var_v1;
    u32 temp_v0_2;
    u8 temp_v0;
    u8 temp_v0_6;
    u8 temp_v1_5;
    u8 temp_v1_6;
    u8 var_t0_2;
    s8 *temp_s1_2;
    s8 *temp_s1_3;

    if (gCutsceneID < 0) {
        return 1;
    }
    var_s2 = 0;
    if (arg1 >= 9) {
        arg1 = 8;
    }
    temp_f0 = (f32) arg1;
    var_s0 = 0;
    sp114 = temp_f0;
    temp_s3 = arg0->unk64;
    if (osTvType == 0) {
        sp114 = (f32) ((f64) temp_f0 * 1.2);
    }
    if ((s16) temp_s3->racer.unk2A < 0) {
        temp_v0 = (u8) temp_s3->effect_box.unkE[0x26];
        var_t0 = 0;
        if (temp_v0 & 1) {
            var_t0 = 0x8000;
        }
        if (temp_v0 & 2) {
            var_t0 |= 0x4000;
        }
        if (temp_v0 & 4) {
            var_t0 |= 0x1000;
        }
        do {
            sp174 = var_t0;
            temp_v0_2 = input_pressed(var_s0);
            var_s0 += 1;
            var_s2 |= temp_v0_2;
        } while (var_s0 != 4);
        if (var_s2 & var_t0) {
            temp_s3->racer.unk2A = 1;
        }
    }
    temp_v0_3 = (s16) temp_s3->racer.unk2A;
    if ((temp_v0_3 >= 0) && (temp_s3->effect_box.unkE[0x37] == 0)) {
        temp_s3->racer.unk2A = temp_v0_3 - arg1;
        if ((s16) temp_s3->racer.unk2A <= 0) {
            temp_s3->effect_box.unkE[0x37] = 1;
            temp_s1 = temp_s3->racer.unk1C->pan;
            func_80021104(arg0, &temp_s3->animation, temp_s1);
            temp_s3->racer.unk2A = 0;
            func_8002125C(arg0, (LevelObjectEntry_CharacterSelect *) temp_s1, (Object_CharacterSelect *) temp_s3, -1);
        }
    }
    if ((s16) temp_s3->racer.unk2A != 0) {
        if (temp_s3->effect_box.unkE[0x2C] != 0) {
            arg0->segment.trans.flags |= 0x4000;
            temp_s3->effect_box.unkE[0x34] = 0;
            return 1;
        }
        goto block_247;
    }
    arg0->segment.trans.flags &= 0xBFFF;
    temp_v1 = temp_s3->effect_box.unkE[0x2B];
    if (temp_v1 > 0) {
        temp_v1_2 = temp_s3->effect_box.unkE[0x2B];
        if (temp_v1_2 != music_current_sequence()) {
            music_play(temp_v1_2 & 0xFF);
            music_change_off();
        }
        temp_s3->effect_box.unkE[0x2B] = -2;
        music_volume_reset();
    } else if (temp_v1 == -2) {
        music_change_on();
        temp_s3->effect_box.unkE[0x2B] = -1;
    }
    temp_v1_3 = temp_s3->effect_box.unkE[0x2A];
    if (temp_v1_3 != 0) {
        var_v0 = temp_v1_3 & 0xFF;
        if (temp_s3->fish.triangles[2].uv0.u == 0) {
            if (var_v0 == 0xFF) {
                temp_a0 = temp_s3->racer.unk18;
                if (temp_a0 != NULL) {
                    sndp_stop(temp_a0);
                }
            } else {
                temp_a0_2 = temp_s3->racer.unk18;
                if (temp_a0_2 != NULL) {
                    sndp_stop(temp_a0_2);
                    var_v0 = temp_s3->effect_box.unkE[0x2A] & 0xFF;
                }
                sound_play(var_v0 & 0xFFFF, &temp_s3->racer.unk18);
            }
            temp_s3->effect_box.unkE[0x2A] = 0;
        }
    }
    temp_v0_4 = temp_s3->effect_box.unkE[0x35];
    if (temp_v0_4 != 0) {
        music_fade(temp_v0_4 << 8);
        temp_s3->effect_box.unkE[0x35] = 0;
    }
    temp_v0_5 = temp_s3->effect_box.unkE[0x33];
    var_t0_2 = (u8) temp_s3->effect_box.unkE[0x34];
    if (temp_v0_5 & 1) {
        temp_t7 = arg1 * 8;
        if (temp_v0_5 & 2) {
            var_t0_2 = 0;
        }
        if (temp_t7 < (s32) var_t0_2) {
            var_t0_3 = var_t0_2 - temp_t7;
        } else {
            var_t0_3 = 0;
            arg0->segment.trans.flags |= 0x4000;
        }
    } else {
        if (temp_v0_5 & 2) {
            var_t0_2 = 0xFF;
        }
        var_t0_3 = var_t0_2 + (arg1 * 8);
        if (var_t0_3 >= 0x100) {
            var_t0_3 = -1;
        }
        arg0->segment.trans.flags &= ~0x4000;
    }
    temp_v0_6 = (u8) temp_s3->effect_box.unkE[0x2D];
    temp_s2 = temp_v0_6 & 0x7F;
    temp_s3->effect_box.unkE[0x34] = var_t0_3;
    if (temp_s2 != 0x7F) {
        if (temp_s2 >= 8) {
            temp_s1_2 = (s8 *) (get_misc_asset(0xD) + (temp_s2 * 5)) - 0x28;
            temp_t0 = (temp_s1_2[0] & 0xFF) + 0x384;
            temp_s0 = (temp_s1_2[1] & 0xFF) + 0x384;
            sp174 = temp_t0;
            slowly_change_fog(0, temp_s1_2[2] & 0xFF, temp_s1_2[3] & 0xFF, temp_s1_2[4] & 0xFF, temp_t0, temp_s0,
                              normalise_time(6) * (u8) temp_s3->effect_box.unkE[0x2E]);
        } else if (temp_s2 >= 6) {
            spA4 = 0x40;
            if (temp_s2 == 7) {
                spA7 = -1;
                spA6 = -0x38;
                spA5 = -0x38;
            } else {
                spA7 = -1;
                spA6 = -1;
                spA5 = -1;
            }
            spA8 = 7;
            spAA = 3;
            transition_begin((FadeTransition *) &spA4);
        } else {
            spA4 = temp_v0_6;
            temp_s1_3 = (s8 *) get_misc_asset(0xE) + (temp_s3->effect_box.unkE[0x32] * 3);
            spA5 = temp_s1_3[0];
            spA6 = temp_s1_3[1];
            spA7 = temp_s1_3[2];
            if ((u8) temp_s3->effect_box.unkE[0x2D] & 0x80) {
                spAA = 0;
            } else {
                spAA = 0xFFFF;
            }
            spA8 = normalise_time(6) * (u8) temp_s3->effect_box.unkE[0x2E];
            if ((check_fadeout_transition() == 0) || (spA4 & 0x80)) {
                transition_begin((FadeTransition *) &spA4);
            }
        }
        temp_s3->effect_box.unkE[0x2D] = -1;
    }
    if ((u8) temp_s3->effect_box.unkE[0x20] == 1) {
        temp_f0_2 = (f32) ((f64) sp114 * 8.0);
        arg0->segment.trans.rotation.s[0] += (s32) ((f32) temp_s3->effect_box.unkE[0x23] * temp_f0_2);
        arg0->segment.trans.rotation.s[1] += (s32) ((f32) temp_s3->effect_box.unkE[0x24] * temp_f0_2);
        arg0->segment.trans.rotation.s[2] += (s32) ((f32) temp_s3->effect_box.unkE[0x25] * temp_f0_2);
    }
    if ((arg2 != NULL) && (arg2->segment.header->modelType == 0)) {
        // usage of temp_s3 is definetely incorrect here. unkE[2] is probably a f32, unkE[6] as well, possibly xy
        // coordinates
        arg2->segment.object.animationID = arg0->segment.object.animationID;
        temp_v0_7 = arg2->segment.animFrame;
        if (temp_v0_7 != (s16) (s32) temp_s3->effect_box.unkE[2]) {
            temp_s3->effect_box.unkE[2] = (f32) temp_v0_7;
        }
        temp_v1_4 = arg2->unk68[arg2->segment.object.modelIndex];
        if (temp_v1_4 != NULL) {
            temp_v0_8 = arg2->segment.object.animationID;
            temp_a0_3 = temp_v1_4->objModel;
            if ((temp_v0_8 >= 0) && (temp_v0_8 < temp_a0_3->numberOfAnimations)) {
                temp_v1_5 = (u8) temp_s3->effect_box.unkE[0x1E];
                temp_t7_2 = (temp_a0_3->animations[temp_v0_8].animLength - 1) * 0x10;
                switch (temp_v1_5) { /* irregular */
                    case 0:
                        temp_f0_3 = (f32) temp_t7_2;
                        temp_s3->effect_box.unkE[2] =
                            ((f32) temp_s3->effect_box.unkE[2] + ((f32) temp_s3->effect_box.unkE[6] * sp114));
                        temp_f2 = temp_s3->effect_box.unkE[2];
                        if (temp_f0_3 <= (f32) temp_f2) {
                            temp_s3->effect_box.unkE[2] = ((f32) temp_f2 - temp_f0_3);
                        }
                        break;
                    case 2:
                        temp_f0_4 = (f32) temp_t7_2;
                        temp_s3->effect_box.unkE[2] =
                            ((f32) temp_s3->effect_box.unkE[2] + ((f32) temp_s3->effect_box.unkE[6] * sp114));
                        if (temp_f0_4 <= (f32) temp_s3->effect_box.unkE[2]) {
                            temp_s3->effect_box.unkE[2] = (temp_f0_4 - 1.0f);
                        }
                        break;
                    case 1:
                        if ((u8) temp_s3->effect_box.unkE[0x1F] == 0) {
                            temp_f0_5 = (f32) temp_t7_2;
                            temp_s3->effect_box.unkE[2] =
                                ((f32) temp_s3->effect_box.unkE[2] + ((f32) temp_s3->effect_box.unkE[6] * sp114));
                            if (temp_f0_5 <= (f32) temp_s3->effect_box.unkE[2]) {
                                temp_s3->effect_box.unkE[0x1F] = 1;
                                temp_s3->effect_box.unkE[2] = (temp_f0_5 - 1.0f);
                            }
                        } else {
                            temp_s3->effect_box.unkE[2] =
                                ((f32) temp_s3->effect_box.unkE[2] - ((f32) temp_s3->effect_box.unkE[6] * sp114));
                            if ((f32) temp_s3->effect_box.unkE[2] <= 0.0f) {
                                temp_s3->effect_box.unkE[2] = NULL;
                                temp_s3->effect_box.unkE[0x1F] = 0;
                            }
                        }
                        break;
                    case 3:
                        if ((u8) temp_s3->effect_box.unkE[0x1F] == 0) {
                            temp_f0_6 = (f32) temp_t7_2;
                            temp_s3->effect_box.unkE[2] =
                                ((f32) temp_s3->effect_box.unkE[2] + ((f32) temp_s3->effect_box.unkE[6] * sp114));
                            if (temp_f0_6 <= (f32) temp_s3->effect_box.unkE[2]) {
                                temp_s3->effect_box.unkE[0x1F] = 1;
                                temp_s3->effect_box.unkE[2] = (temp_f0_6 - 1.0f);
                            }
                        } else {
                            temp_s3->effect_box.unkE[2] =
                                ((f32) temp_s3->effect_box.unkE[2] - ((f32) temp_s3->effect_box.unkE[6] * sp114));
                            if ((f32) temp_s3->effect_box.unkE[2] <= 0.0f) {
                                temp_s3->effect_box.unkE[2] = NULL;
                            }
                        }
                        break;
                }
            }
        }
        arg2->segment.animFrame = (s16) (s32) (f32) temp_s3->effect_box.unkE[2];
    }
    if ((f64) temp_s3->racer.forwardVel <= 0.0) {
        return func_800214E4(arg0, arg1);
    }
    temp_a1 = (s16) temp_s3->racer.lastSoundID;
    var_s4 = 0;
    if ((D_8011AE78 > 0) && (temp_a1 != (*D_8011AE74)->properties.common.unk4)) {
    loop_104:
        var_s4 += 1;
        if (var_s4 < D_8011AE78) {
            if (temp_a1 != D_8011AE74[var_s4]->properties.common.unk4) {
                goto loop_104;
            }
        }
    }
    if (var_s4 >= D_8011AE78) {
        return func_800214E4(arg0, arg1);
    }
    var_s5 = 1;
    if ((var_s4 + 1) < D_8011AE78) {
        temp_a0_4 = &D_8011AE74[var_s4];
        var_v0_2 = var_s4 + 1 + 1;
        if (temp_a1 == temp_a0_4[1]->properties.common.unk4) {
        loop_110:
            var_s5 += 1;
            if (var_v0_2 < D_8011AE78) {
                var_v0_2 += 1;
                if (temp_a1 == temp_a0_4[var_s5]->properties.common.unk4) {
                    goto loop_110;
                }
            }
        }
    }
    if (var_s5 < 2) {
        return func_800214E4(arg0, arg1);
    }
    temp_a2 = D_8011AE74;
    var_v1 = -1;
    spB4 = (f32) (1.0 / (f64) (*temp_a2)->segment.header->scale);
    if (var_s5 >= 3) {
        temp_v0_9 = (&temp_a2[var_s4])[var_s5 - 1]->segment.level_entry->animation.goToNode;
        if (temp_v0_9 >= 0) {
            if (temp_v0_9 < (var_s5 - 1)) {
                var_v1 = temp_v0_9;
            }
        }
    }
    if ((var_v1 == -1) && (temp_s3->fish.triangles[2].uv0.v >= (var_s5 - 1))) {
        return func_800214E4(arg0, arg1);
    }
    temp_v0_10 = temp_s3->fish.triangles[3].uv0.v;
    sp168 = (s32) var_v1;
    var_t1 = &sp154;
    if (temp_v0_10 >= 0) {
        if (D_8011AD53 == 0) {
            temp_s3->fish.triangles[3].uv0.v = temp_v0_10 - arg1;
        }
    } else {
        var_t2 = &sp140;
        var_t3 = &sp12C;
        var_t5 = &spE0[0];
        var_t4 = &spCC[0];
        var_ra = &spB8[0];
        var_a3 = &spF4;
        var_s0_2 = temp_s3->fish.triangles[2].uv0.v - 1;
        do {
            if (var_s0_2 == -1) {
                if (sp168 != 0) {
                    temp_v0_11 = &temp_a2[var_s4];
                    temp_f0_7 = temp_v0_11[0]->segment.trans.x_position;
                    *var_t1 = (temp_f0_7 - temp_v0_11[1]->segment.trans.x_position) + temp_f0_7;
                    temp_f2_2 = temp_v0_11[0]->segment.trans.y_position;
                    *var_t2 = (temp_f2_2 - temp_v0_11[1]->segment.trans.y_position) + temp_f2_2;
                    temp_f12 = temp_v0_11[0]->segment.trans.z_position;
                    *var_t3 = (temp_f12 - temp_v0_11[1]->segment.trans.z_position) + temp_f12;
                    *var_t5 = (f32) temp_v0_11[0]->segment.trans.rotation.s[0];
                    *var_t4 = (f32) temp_v0_11[0]->segment.trans.rotation.s[1];
                    *var_ra = (f32) temp_v0_11[0]->segment.trans.rotation.s[2];
                    var_f6 = temp_v0_11[0]->segment.trans.scale;
                    goto block_144;
                }
                temp_v0_12 = &temp_a2[var_s4 + var_s5];
                *var_t1 = temp_v0_12[-1]->segment.trans.x_position;
                *var_t2 = temp_v0_12[-1]->segment.trans.y_position;
                *var_t3 = temp_v0_12[-1]->segment.trans.z_position;
                *var_t5 = (f32) temp_v0_12[-1]->segment.trans.rotation.s[0];
                *var_t4 = (f32) temp_v0_12[-1]->segment.trans.rotation.s[1];
                *var_ra = (f32) temp_v0_12[-1]->segment.trans.rotation.s[2];
                *var_a3 = temp_v0_12[-1]->segment.trans.scale;
            } else {
                temp_a1_2 = var_s0_2 + var_s4;
                if (var_s0_2 >= var_s5) {
                    temp_v0_13 = var_s5 + var_s4;
                    if (sp168 == -1) {
                        var_s0_2 = var_s5 - 1;
                        if (temp_a2[temp_v0_13 - 1]->segment.level_entry->animation.unk22 == 1) {
                            sp6C = var_ra;
                            sp74 = var_t5;
                            sp70 = var_t4;
                            sp78 = var_t3;
                            sp7C = var_t2;
                            sp88 = var_t1;
                            sp68 = var_a3;
                            sp5C = (temp_v0_13 * 4) - 4;
                            set_active_camera((s32) temp_s3->effect_box.unkE[0x22]);
                            var_v1_2 = cam_get_active_camera_no_cutscenes();
                            var_a0 = &D_8011AE74[temp_v0_13 - 1];
                        } else {
                            var_a0 = &temp_a2[temp_v0_13 - 1];
                            var_v1_2 = (Camera *) *var_a0;
                        }
                        temp_f0_8 = var_v1_2->trans.x_position;
                        *var_t1 = (temp_f0_8 - var_a0[-1]->segment.trans.x_position) + temp_f0_8;
                        temp_f2_3 = var_v1_2->trans.y_position;
                        *var_t2 = (temp_f2_3 - var_a0[-1]->segment.trans.y_position) + temp_f2_3;
                        temp_f12_2 = var_v1_2->trans.z_position;
                        *var_t3 = (temp_f12_2 - var_a0[-1]->segment.trans.z_position) + temp_f12_2;
                        *var_t4 = (f32) var_v1_2->trans.rotation.s[1];
                        *var_ra = (f32) var_v1_2->trans.rotation.s[2];
                        *var_t5 = (f32) var_a0[0]->segment.trans.rotation.s[0];
                        *var_a3 = var_a0[0]->segment.trans.scale;
                    } else {
                        temp_v0_14 = &temp_a2[(var_s4 + sp168 + var_s0_2) - var_s5];
                        *var_t1 = (*temp_v0_14)->segment.trans.x_position;
                        *var_t2 = (*temp_v0_14)->segment.trans.y_position;
                        *var_t3 = (*temp_v0_14)->segment.trans.z_position;
                        *var_t5 = (f32) (*temp_v0_14)->segment.trans.rotation.s[0];
                        *var_t4 = (f32) (*temp_v0_14)->segment.trans.rotation.s[1];
                        *var_ra = (f32) (*temp_v0_14)->segment.trans.rotation.s[2];
                        var_f6 = (*temp_v0_14)->segment.trans.scale;
                        goto block_144;
                    }
                } else {
                    var_a0_2 = &temp_a2[temp_a1_2];
                    temp_v0_15 = *var_a0_2;
                    temp_s1_4 = temp_v0_15->segment.level_entry;
                    var_v1_3 = temp_v0_15;
                    if (temp_s1_4->animation.unk22 == 1) {
                        sp6C = var_ra;
                        sp74 = var_t5;
                        sp70 = var_t4;
                        sp78 = var_t3;
                        sp7C = var_t2;
                        sp88 = var_t1;
                        sp68 = var_a3;
                        sp80 = temp_a1_2 * 4;
                        set_active_camera((s32) temp_s3->effect_box.unkE[0x22]);
                        var_v1_3 = (Object *) cam_get_active_camera_no_cutscenes();
                        var_a0_2 = D_8011AE74 + sp80;
                    }
                    *var_t1 = var_v1_3->segment.trans.x_position;
                    *var_t2 = var_v1_3->segment.trans.y_position;
                    *var_t3 = var_v1_3->segment.trans.z_position;
                    *var_t4 = (f32) var_v1_3->segment.trans.rotation.s[1];
                    *var_ra = (f32) var_v1_3->segment.trans.rotation.s[2];
                    *var_t5 = (f32) (*var_a0_2)->segment.trans.rotation.s[0];
                    if (temp_s1_4->animation.unk22 == 1) {
                        *var_t4 = -*var_t4;
                    }
                    var_f6 = (*var_a0_2)->segment.trans.scale;
                block_144:
                    *var_a3 = var_f6;
                }
            }
            var_a3 += 4;
            var_t1 += 4;
            var_t2 += 4;
            var_t3 += 4;
            var_t5 += 4;
            var_t4 += 4;
            var_ra += 4;
            var_s0_2 += 1;
        } while (var_a3 != &sp108);
        var_s2_2 = 0;
        var_s0_3 = 0;
        if ((f32) temp_s3->racer.unk4 == 0.0f) {
            temp_s3->racer.unk4 = 0x3C23D70A;
        }
        do {
            var_f20 = (f32) temp_s3->fish.triangles[0].vertices + ((f32) temp_s3->racer.unk4 * sp114);
            temp_f0_9 = (f64) var_f20;
            if (temp_f0_9 >= 1.0) {
                var_s2_2 = 1;
                var_f20 = (f32) (temp_f0_9 - 1.0);
            }
            if (temp_s3->effect_box.unkE[0x31] == 0) {
                sp124 = catmull_rom_interpolation(&sp154, var_s2_2, var_f20);
                sp120 = catmull_rom_interpolation(&sp140, var_s2_2, var_f20);
                var_f0 = catmull_rom_interpolation(&sp12C, var_s2_2, var_f20);
            } else {
                sp124 = lerp(&sp154, (u32) var_s2_2, var_f20);
                sp120 = lerp(&sp140, (u32) var_s2_2, var_f20);
                var_f0 = lerp(&sp12C, (u32) var_s2_2, var_f20);
            }
            sp11C = var_f0;
            temp_f6 = sp124 - arg0->segment.trans.x_position;
            sp124 = temp_f6;
            temp_f8 = sp120 - arg0->segment.trans.y_position;
            sp120 = temp_f8;
            sp11C = var_f0 - arg0->segment.trans.z_position;
            if (var_s0_3 != 1) {
                var_s2_2 = 0;
                temp_f2_4 = sqrtf((temp_f6 * temp_f6) + (temp_f8 * temp_f8) + (sp11C * sp11C)) / sp114;
                if (temp_f2_4 != 0.0f) {
                    temp_s3->racer.unk4 = (s32) ((f32) temp_s3->racer.unk4 * (temp_s3->racer.forwardVel / temp_f2_4));
                }
            }
            var_s0_3 += 1;
        } while (var_s0_3 != 2);
        arg0->segment.trans.scale =
            catmull_rom_interpolation(&spF4, var_s2_2, var_f20) * spB4 * arg0->segment.header->scale;
        if ((var_s2_2 != 0) && (sp168 == -1) && (var_s5 == (temp_s3->fish.triangles[2].uv0.v + 2))) {
            sp124 = catmull_rom_interpolation(&sp154, 0, 1.0f);
            sp120 = catmull_rom_interpolation(&sp140, 0, 1.0f);
            temp_f0_10 = catmull_rom_interpolation(&sp12C, 0, 1.0f);
            sp11C = temp_f0_10;
            sp124 -= arg0->segment.trans.x_position;
            sp120 -= arg0->segment.trans.y_position;
            sp11C = temp_f0_10 - arg0->segment.trans.z_position;
        }
        arg0->segment.x_velocity = sp124 / sp114;
        arg0->segment.y_velocity = sp120 / sp114;
        arg0->segment.z_velocity = sp11C / sp114;
        move_object(arg0, sp124, sp120, sp11C);
        temp_v1_6 = (u8) temp_s3->effect_box.unkE[0x20];
        if (temp_v1_6 != 1) {
            if (temp_v1_6 != 2) {
                var_t0_4 = 1;
                if (temp_v1_6 != 3) {
                    var_t5_2 = &spE4;
                    var_t4_2 = &spD0;
                    var_ra_2 = &spBC;
                    do {
                        temp_f4 = var_t5_2[0];
                        temp_f6_2 = var_t5_2[1];
                        var_t5_2++;
                        temp_f2_5 = (f64) (temp_f4 - temp_f6_2);
                        var_f0_2 = 0.0f;
                        if (temp_f2_5 > 32768.0) {
                            var_f0_2 = (f32) ((f64) 0.0f - 65536.0);
                        } else if (temp_f2_5 < -32768.0) {
                            var_f0_2 = (f32) ((f64) 0.0f + 65536.0);
                        }
                        var_s0_4 = var_t0_4;
                        if (var_t0_4 < 5) {
                            temp_t7_3 = (5 - var_t0_4) & 3;
                            if (temp_t7_3 != 0) {
                                var_v0_3 = &(&spE0[0])[var_s0_4];
                                do {
                                    var_s0_4 += 1;
                                    temp_f8_2 = *var_v0_3 + var_f0_2;
                                    var_v0_3[0] = temp_f8_2;
                                    var_v0_3++;
                                } while ((temp_t7_3 + var_t0_4) != var_s0_4);
                                if (var_s0_4 != 5) {
                                    goto block_181;
                                }
                            } else {
                            block_181:
                                var_v0_4 = &(&spE0[0])[var_s0_4];
                                do {
                                    var_v0_4[1] += var_f0_2;
                                    var_v0_4[0] += var_f0_2;
                                    var_v0_4[2] += var_f0_2;
                                    var_v0_4[3] += var_f0_2;
                                    var_v0_4 += 4;
                                } while (var_v0_4 != &spF4);
                            }
                            var_s0_4 = var_t0_4;
                        }
                        temp_f4_2 = var_t4_2[0];
                        temp_f6_4 = var_t4_2[-1];
                        var_t4_2++;
                        temp_f2_6 = (f64) (temp_f4_2 - temp_f6_4);
                        var_f0_3 = 0.0f;
                        if (temp_f2_6 > 32768.0) {
                            var_f0_3 = (f32) ((f64) 0.0f - 65536.0);
                        } else if (temp_f2_6 < -32768.0) {
                            var_f0_3 = (f32) ((f64) 0.0f + 65536.0);
                        }
                        if (var_t0_4 < 5) {
                            temp_t6 = (5 - var_t0_4) & 3;
                            if (temp_t6 != 0) {
                                var_v0_5 = &(&spCC[0])[var_s0_4];
                                do {
                                    var_s0_4 += 1;
                                    temp_f8_3 = *var_v0_5 + var_f0_3;
                                    var_v0_5[0] = temp_f8_3;
                                    var_v0_5 += 4;
                                } while ((temp_t6 + var_t0_4) != var_s0_4);
                                if (var_s0_4 != 5) {
                                    goto block_193;
                                }
                            } else {
                            block_193:
                                var_v0_6 = &(&spCC[0])[var_s0_4];
                                do {
                                    var_v0_6[1] += var_f0_3;
                                    var_v0_6[0] += var_f0_3;
                                    var_v0_6[2] += var_f0_3;
                                    var_v0_6[3] += var_f0_3;
                                    var_v0_6 += 4;
                                } while (var_v0_6 != &spE0[0]);
                            }
                            var_s0_4 = var_t0_4;
                        }
                        temp_f2_7 = (f64) (var_ra_2[0] - var_ra_2[-1]);
                        var_f0_4 = 0.0f;
                        if (temp_f2_7 > 32768.0) {
                            var_f0_4 = (f32) ((f64) 0.0f - 65536.0);
                        } else if (temp_f2_7 < -32768.0) {
                            var_f0_4 = (f32) ((f64) 0.0f + 65536.0);
                        }
                        temp_t7_4 = (5 - var_t0_4) & 3;
                        if (var_t0_4 < 5) {
                            if (temp_t7_4 != 0) {
                                var_v0_7 = &(&spB8[0])[var_s0_4];
                                do {
                                    var_s0_4 += 1;
                                    var_v0_7[0] += var_f0_4;
                                    var_v0_7++;
                                } while ((temp_t7_4 + var_t0_4) != var_s0_4);
                                if (var_s0_4 != 5) {
                                    goto block_205;
                                }
                            } else {
                            block_205:
                                var_v0_8 = &(&spB8[0])[var_s0_4];
                                do {
                                    var_v0_6[1] += var_f0_4;
                                    var_v0_6[0] += var_f0_4;
                                    var_v0_6[2] += var_f0_4;
                                    var_v0_6[3] += var_f0_4;
                                    var_v0_6 += 4;
                                } while (var_v0_8 != &spCC[0]);
                            }
                        }
                        var_t0_4 += 1;
                        var_ra_2 += 4;
                    } while (var_t0_4 != 5);
                    if (temp_s3->effect_box.unkE[0x31] == 0) {
                        arg0->segment.trans.rotation.s[0] =
                            (s16) (s32) catmull_rom_interpolation(&spE0[0], var_s2_2, var_f20);
                        arg0->segment.trans.rotation.s[1] =
                            (s16) (s32) catmull_rom_interpolation(&spCC[0], var_s2_2, var_f20);
                        arg0->segment.trans.rotation.s[2] =
                            (s16) (s32) catmull_rom_interpolation(&spB8[0], var_s2_2, var_f20);
                    } else {
                        arg0->segment.trans.rotation.s[0] = (s16) (s32) lerp(&spE0[0], (u32) var_s2_2, var_f20);
                        arg0->segment.trans.rotation.s[1] = (s16) (s32) lerp(&spCC[0], (u32) var_s2_2, var_f20);
                        arg0->segment.trans.rotation.s[2] = (s16) (s32) lerp(&spB8[0], (u32) var_s2_2, var_f20);
                    }
                }
            } else {
                if (temp_s3->effect_box.unkE[0x31] == 0) {
                    cubic_spline_interpolation(&sp154, var_s2_2, var_f20, &sp124);
                    cubic_spline_interpolation(&sp140, var_s2_2, var_f20, &sp120);
                    cubic_spline_interpolation(&sp12C, var_s2_2, var_f20, &sp11C);
                } else {
                    lerp_and_get_derivative(&sp154, (u32) var_s2_2, var_f20, &sp124);
                    lerp_and_get_derivative(&sp140, (u32) var_s2_2, var_f20, &sp120);
                    lerp_and_get_derivative(&sp12C, (u32) var_s2_2, var_f20, &sp11C);
                }
                temp_f0_11 = sqrtf((sp124 * sp124) + (sp120 * sp120) + (sp11C * sp11C));
                if (temp_f0_11 != 0.0f) {
                    temp_f12_3 = (f32) (100.0 / (f64) temp_f0_11);
                    sp124 *= temp_f12_3;
                    sp120 *= temp_f12_3;
                    sp11C *= temp_f12_3;
                }
                arg0->segment.trans.rotation.s[0] = arctan2_f(sp124, sp11C) - 0x8000;
                arg0->segment.trans.rotation.s[1] = arctan2_f(sp120, 100.0f);
            }
        }
        var_t0_5 = temp_s3->fish.triangles[2].uv0.v;
        temp_s3->fish.triangles[0].vertices = (u32) var_f20;
        if ((sp168 != -1) && (var_t0_5 >= var_s5)) {
            var_t0_5 = (var_t0_5 - var_s5) + sp168;
        }
        temp_f10_4 =
            (f32) ((f64) (f32) (&D_8011AE74[var_s4])[var_t0_5]->segment.level_entry->animation.nodeSpeed * 0.1);
        sp124 = temp_f10_4;
        if (temp_f10_4 < 0.0f) {
            sp124 = temp_s3->racer.animationSpeed;
        } else {
            temp_s3->racer.animationSpeed = sp124;
        }
        if (sp124 >= 0.0f) {
            temp_v0_16 = var_t0_5 + 1;
            if (var_s2_2 == 0) {
                var_s0_5 = temp_v0_16;
                if ((sp168 != -1) && (temp_v0_16 >= var_s5)) {
                    var_s0_5 = (temp_v0_16 - var_s5) + sp168;
                }
                if (var_s0_5 < var_s5) {
                    temp_v0_17 = (&D_8011AE74[var_s4])[var_s0_5]->segment.level_entry->animation.nodeSpeed;
                    if (temp_v0_17 >= 0) {
                        sp11C = (f32) ((f64) (f32) temp_v0_17 * 0.1);
                    } else {
                        sp11C = sp124;
                    }
                }
                temp_s3->racer.forwardVel = ((sp11C - sp124) * var_f20) + sp124;
            }
        }
        if (var_s2_2 != 0) {
            temp_s3->fish.triangles[2].uv0.v += 1;
            if (sp168 == -1) {
                temp_v0_18 = temp_s3->fish.triangles[2].uv0.v;
                if (temp_v0_18 >= var_s5) {
                    temp_s3->fish.triangles[2].uv0.v = var_s5 - 1;
                } else {
                    func_8002125C(
                        arg0,
                        (LevelObjectEntry_CharacterSelect *) (&D_8011AE74[temp_v0_18])[var_s4]->segment.level_entry,
                        (Object_CharacterSelect *) temp_s3, var_s4);
                }
            } else {
                if (var_s5 < temp_s3->fish.triangles[2].uv0.v) {
                    temp_s3->fish.triangles[2].uv0.v = sp168 + 1;
                }
                var_s2_3 = temp_s3->fish.triangles[2].uv0.v;
                if (temp_s3->fish.triangles[2].uv0.v >= var_s5) {
                    var_s2_3 = (temp_s3->fish.triangles[2].uv0.v - var_s5) + sp168;
                }
                func_8002125C(arg0,
                              (LevelObjectEntry_CharacterSelect *) D_8011AE74[var_s2_3 + var_s4]->segment.level_entry,
                              (Object_CharacterSelect *) temp_s3, var_s4);
            }
        }
        if ((u8) temp_s3->effect_box.unkE[0x20] == 3) {
            var_t0_6 = 0;
            if (D_8011AE78 > 0) {
                temp_v0_19 = temp_s3->effect_box.unkE[0x30];
                if (temp_v0_19 != (*D_8011AE74)->properties.common.unk4) {
                loop_240:
                    var_t0_6 += 1;
                    if (var_t0_6 < D_8011AE78) {
                        if (temp_v0_19 != D_8011AE74[var_t0_6]->properties.common.unk4) {
                            goto loop_240;
                        }
                    }
                }
            }
            if (var_t0_6 != D_8011AE78) {
                temp_v1_7 = D_8011AE74[var_t0_6]->unk64;
                if (temp_v1_7 != NULL) {
                    // usage of temp_s3 is definetely incorrect here. unkE[2] is probably a f32, unkE[6] as well,
                    // possibly xy coordinates
                    sp124 = temp_v1_7->racer.animationSpeed - arg0->segment.trans.x_position;
                    sp120 = (f32) temp_s3->effect_box.unkE[2] - arg0->segment.trans.y_position;
                    sp11C = (f32) temp_s3->effect_box.unkE[6] - arg0->segment.trans.z_position;
                    temp_f0_12 = sqrtf((sp124 * sp124) + (sp120 * sp120) + (sp11C * sp11C));
                    if (temp_f0_12 > 0.0f) {
                        arg0->segment.trans.rotation.s[0] = arctan2_f(sp124, sp11C) - 0x8000;
                        arg0->segment.trans.rotation.s[1] = arctan2_f(sp120, temp_f0_12);
                    }
                }
            }
        }
        arg0->particleEmittersEnabled = (u32) temp_s3->effect_box.unkE[0x21];
        obj_spawn_particle(arg0, arg1);
    }
block_247:
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_8001F460.s")
#endif

s32 func_800210CC(s8 arg0) {
    if (arg0 >= D_8011AD3D) {
        D_8011AD3D = arg0;
        return TRUE;
    }
    return FALSE;
}

void func_80021104(Object *obj, Object_Animation *animObj, LevelObjectEntry_Animation *entry) {
    Camera *camera;
    ObjectTransform *animObjTrans;

    animObjTrans = &animObj->unk1C->segment.trans;
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
        ObjectSegment *seg = &(*gRacers)[entry->unk22 - 10]->segment;
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

void func_8002125C(Object *charSelectObj, LevelObjectEntry_CharacterSelect *entry, Object_CharacterSelect *charSelect,
                   UNUSED s32 index) {
    s32 initialAnimFrame;

    initialAnimFrame = entry->unk12;
    if (initialAnimFrame >= 0) {
        if (initialAnimFrame != charSelectObj->segment.object.animationID) {
            charSelectObj->segment.animFrame = entry->unk16;
        }
        charSelectObj->segment.object.animationID = entry->unk12;
        charSelect->unk14 = entry->unk17;
        charSelect->unk2C = entry->unk18;
    }
    if (entry->unk13 >= 0) {
        charSelect->unk2F = entry->unk13;
    }
    charSelect->unk36 = normalise_time(entry->unk24);
    charSelect->unk3F = entry->unk2D;
    charSelect->unk3A = entry->unk26;
    charSelect->unk39 = entry->unk1F;
    charSelect->unk43 = entry->unk30;
    charSelect->unk38 = entry->unk1E;
    charSelect->unk3B = entry->unk29;
    charSelect->unk40 = entry->unk2E;
    charSelect->unk41 = entry->unk2F;
    charSelect->unk3C = entry->unk2B;
    if (entry->unk27 != 255) {
        set_current_text(entry->unk27);
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

    for (i = 0; i < D_8011AE78 && (arg0 != (D_8011AE74[i]->properties.common.unk4 & 0xFF)); i++) {}

    if (i < D_8011AE78) {
        if (D_8011AE74[i]->unk64 != NULL) {
            if (D_8011AE74[i]->unk64->obj80021400_64.obj64->unk2A < 0) {
                D_8011AE74[i]->unk64->obj80021400_64.obj64->unk2A = 1;
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

    animObj = &obj->unk64->animatedObject;
    if (animObj->unk3A != 0) {
        obj->segment.trans.flags |= OBJ_FLAGS_INVISIBLE;
    }
    if (animObj->unk36 == -1) {
        return animObj->unk3A;
    }
    if (animObj->unk36 >= 0) {
        animObj->unk36 -= updateRate;
    }
    if (animObj->unk36 == -1) {
        animObj->unk36 = -2;
    }
    if (animObj->unk36 <= 0) {
        obj->segment.trans.flags |= OBJ_FLAGS_INVISIBLE;
        for (i = 0; (i < D_8011AE78 && animObj->unk28 != D_8011AE74[i]->properties.common.unk4); i++) {
            if (FALSE) {} // FAKEMATCH
        }
        obj_init_animcamera(D_8011AE74[i], obj);
        return 1;
    }
    return 0;
}

// https://decomp.me/scratch/hYfN2
#ifdef NON_EQUIVALENT
s32 func_80021600(s32 arg0) {
    s8 *sp15C;
    Object_64 *sp154;
    LevelObjectEntry *sp150;
    s32 sp138;
    f32 sp124;
    f32 sp110;
    f32 spFC;
    f32 spF8;
    f32 spF4;
    f32 spF0;
    f32 spEC;
    f32 spE4;
    f32 spD0;
    f32 spC0;
    f32 *spBC;
    f32 spAC;
    f32 *spA8;
    f32 sp98;
    f32 *sp94;
    f32 sp90;
    s32 sp7C;
    s32 sp74;
    f32 *sp5C;
    s32 sp4C;
    f32 *var_fp_2;
    f32 *var_s6_2;
    f32 *var_t1_2;
    Object *var_v1_2;
    Object **var_a0;
    LevelObjectEntry *temp_a1;
    Object *temp_v0;
    Object *temp_v0_7;
    Object *var_v1_3;
    Object **temp_a0;
    Object **temp_a3;
    Object **temp_v0_4;
    Object **temp_v0_6;
    Object **var_a0_2;
    Object_64 *temp_t4;
    Object_64 *temp_v1;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f10;
    f32 temp_f10_2;
    f32 temp_f10_3;
    f32 temp_f10_4;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f4_3;
    f32 temp_f6;
    f32 temp_f6_2;
    f32 temp_f6_3;
    f32 temp_f8;
    f32 temp_f8_2;
    f32 temp_f8_3;
    f32 temp_f8_4;
    f32 temp_f8_5;
    f32 temp_f8_6;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 var_f0_4;
    f32 var_f6;
    f32 *var_fp;
    f32 *var_s1;
    f32 *var_s2;
    f32 *var_s3;
    f32 *var_s4;
    f32 *var_s6;
    f32 *var_t1;
    f32 *var_v0_2;
    f32 *var_v0_3;
    f32 *var_v0_4;
    f32 *var_v0_5;
    f32 *var_v0_6;
    f32 *var_v0_7;
    f64 temp_f2_3;
    f64 temp_f2_4;
    f64 temp_f2_5;
    s32 temp_a2;
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_t8;
    s32 temp_v0_5;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s5;
    s32 var_s7;
    s32 var_v0;
    s8 temp_v0_2;
    s8 temp_v0_9;
    s8 var_v1;
    u8 temp_v0_8;
    Object **temp_v0_3;

    if (gCutsceneID < 0) {
        return 1;
    }
    var_s7 = 0;
    if ((D_8011AE78 > 0) && (arg0 != (*D_8011AE74)->properties.common.unk4)) {
    loop_4:
        var_s7++;
        if (var_s7 < D_8011AE78) {
            if (arg0 != D_8011AE74[var_s7]->properties.common.unk4) {
                goto loop_4;
            }
        }
    }
    if (var_s7 >= D_8011AE78) {
        return 1;
    }
    var_s5 = 1;
    if ((var_s7 + 1) < D_8011AE78) {
        temp_a0 = &D_8011AE74[var_s7];
        var_v0 = var_s7 + 1 + 1;
        if (arg0 == temp_a0[1]->properties.common.unk4) {
        loop_10:
            var_s5++;
            if (var_v0 < D_8011AE78) {
                var_v0++;
                if (arg0 == temp_a0[var_s5]->properties.common.unk4) {
                    goto loop_10;
                }
            }
        }
    }
    if (var_s5 < 2) {
        return 1;
    }
    temp_a3 = D_8011AE74;
    sp7C = var_s7 * 4;
    temp_v0 = temp_a3[var_s7];
    var_s2 = &sp124;
    temp_t4 = temp_v0->unk64;
    var_s3 = &sp110;
    sp154 = temp_t4;
    if (temp_t4 == NULL) {
        return 1;
    }
    var_v1 = -1;
    var_s4 = &spFC;
    var_fp = &spBC[0];
    var_s6 = &spA8[0];
    var_t1 = &sp94[0];
    var_s1 = &spD0;
    sp90 = (f32) (1.0 / (f64) temp_v0->segment.header->scale);
    if (var_s5 >= 3) {
        temp_v0_2 = (&temp_a3[var_s7])[var_s5 - 1]->segment.level_entry->animation.goToNode;
        if ((temp_v0_2 >= 0) && (temp_v0_2 < (var_s5 - 1))) {
            var_v1 = temp_v0_2;
        }
    }
    sp138 = (s32) var_v1;
    var_s0 = sp154->effect_box.unkE[0x26 - 0xE] - 1;
    do {
        if (var_s0 == -1) {
            if (sp138 != 0) {
                temp_v0_3 = temp_a3 + sp7C;
                temp_f0 = temp_v0_3[0]->segment.trans.x_position;
                *var_s2 = (temp_f0 - temp_v0_3[1]->segment.trans.x_position) + temp_f0;
                temp_f2 = temp_v0_3[0]->segment.trans.y_position;
                *var_s3 = (temp_f2 - temp_v0_3[1]->segment.trans.y_position) + temp_f2;
                temp_f12 = temp_v0_3[0]->segment.trans.z_position;
                *var_s4 = (temp_f12 - temp_v0_3[1]->segment.trans.z_position) + temp_f12;
                *var_fp = (f32) temp_v0_3[0]->segment.trans.rotation.s[0];
                *var_s6 = (f32) temp_v0_3[0]->segment.trans.rotation.s[1];
                *var_t1 = (f32) temp_v0_3[0]->segment.trans.rotation.s[2];
                var_f6 = temp_v0_3[0]->segment.trans.scale;
                goto block_38;
            }
            temp_v0_4 = &temp_a3[var_s7 + var_s5];
            *var_s2 = temp_v0_4[-1]->segment.trans.x_position;
            *var_s3 = temp_v0_4[-1]->segment.trans.y_position;
            *var_s4 = temp_v0_4[-1]->segment.trans.z_position;
            *var_fp = (f32) temp_v0_4[-1]->segment.trans.rotation.s[0];
            *var_s6 = (f32) temp_v0_4[-1]->segment.trans.rotation.s[1];
            *var_t1 = (f32) temp_v0_4[-1]->segment.trans.rotation.s[2];
            *var_s1 = temp_v0_4[-1]->segment.trans.scale;
        } else {
            temp_a2 = var_s0 + var_s7;
            if (var_s0 >= var_s5) {
                temp_v0_5 = var_s5 + var_s7;
                if (sp138 == -1) {
                    var_s0 = var_s5 - 1;
                    if (temp_a3[temp_v0_5 - 1]->segment.level_entry->animation.unk22 == 1) {
                        sp5C = var_t1;
                        sp4C = (temp_v0_5 * 4) - 4;
                        set_active_camera((s32) sp15C[30]);
                        var_v1_2 = (Object *) cam_get_active_camera_no_cutscenes();
                        var_a0 = &D_8011AE74[temp_v0_5 - 1];
                    } else {
                        var_a0 = &temp_a3[temp_v0_5 - 1];
                        var_v1_2 = *var_a0;
                    }
                    temp_f0_2 = var_v1_2->segment.trans.x_position;
                    *var_s2 = (temp_f0_2 - var_a0[-1]->segment.trans.x_position) + temp_f0_2;
                    temp_f2_2 = var_v1_2->segment.trans.y_position;
                    *var_s3 = (temp_f2_2 - var_a0[-1]->segment.trans.y_position) + temp_f2_2;
                    temp_f12_2 = var_v1_2->segment.trans.z_position;
                    *var_s4 = (temp_f12_2 - var_a0[-1]->segment.trans.z_position) + temp_f12_2;
                    *var_s6 = (f32) var_v1_2->segment.trans.rotation.s[1];
                    *var_t1 = (f32) var_v1_2->segment.trans.rotation.s[2];
                    *var_fp = (f32) var_a0[0]->segment.trans.rotation.s[0];
                    *var_s1 = var_a0[0]->segment.trans.scale;
                } else {
                    temp_v0_6 = &temp_a3[(var_s7 + sp138 + var_s0) - var_s5];
                    *var_s2 = (*temp_v0_6)->segment.trans.x_position;
                    *var_s3 = (*temp_v0_6)->segment.trans.y_position;
                    *var_s4 = (*temp_v0_6)->segment.trans.z_position;
                    *var_fp = (f32) (*temp_v0_6)->segment.trans.rotation.s[0];
                    *var_s6 = (f32) (*temp_v0_6)->segment.trans.rotation.s[1];
                    *var_t1 = (f32) (*temp_v0_6)->segment.trans.rotation.s[2];
                    var_f6 = (*temp_v0_6)->segment.trans.scale;
                    goto block_38;
                }
            } else {
                var_a0_2 = &temp_a3[temp_a2];
                temp_v0_7 = *var_a0_2;
                temp_a1 = temp_v0_7->segment.level_entry;
                var_v1_3 = temp_v0_7;
                if (temp_a1->animation.unk22 == 1) {
                    sp5C = var_t1;
                    sp74 = temp_a2 * 4;
                    sp150 = temp_a1;
                    set_active_camera((s32) sp15C[0x30]);
                    var_v1_3 = (Object *) cam_get_active_camera_no_cutscenes();
                    var_a0_2 = D_8011AE74 + sp74;
                }
                *var_s2 = var_v1_3->segment.trans.x_position;
                *var_s3 = var_v1_3->segment.trans.y_position;
                *var_s4 = var_v1_3->segment.trans.z_position;
                *var_s6 = (f32) var_v1_3->segment.trans.rotation.s[1];
                *var_t1 = (f32) var_v1_3->segment.trans.rotation.s[2];
                *var_fp = (f32) (*var_a0_2)->segment.trans.rotation.s[0];
                if (temp_a1->animation.unk22 == 1) {
                    *var_s6 = -*var_s6;
                }
                var_f6 = (*var_a0_2)->segment.trans.scale;
            block_38:
                *var_s1 = var_f6;
            }
        }
        var_s1 += 4;
        var_s2 += 4;
        var_s3 += 4;
        var_s4 += 4;
        var_fp += 4;
        var_s6 += 4;
        var_t1 += 4;
        var_s0++;
    } while ((u32) var_s1 < (u32) &spE4);
    temp_f0_3 = sp15C[0];
    if (sp15C[0x3F] == 0) {
        spEC = temp_f0_3;
        spF8 = catmull_rom_interpolation(&sp124, 0, temp_f0_3);
        spF4 = catmull_rom_interpolation(&sp110, 0, spEC);
        var_f0 = catmull_rom_interpolation(&spFC, 0, spEC);
    } else {
        spEC = temp_f0_3;
        spF8 = lerp(&sp124, 0U, temp_f0_3);
        spF4 = lerp(&sp110, 0U, spEC);
        var_f0 = lerp(&spFC, 0U, spEC);
    }
    spF0 = var_f0;
    temp_f10 = spF8 - sp154->racer.animationSpeed;
    spF8 = temp_f10;
    temp_f8 = spF4 - (f32) sp154->effect_box.unkE[2];
    spF4 = temp_f8;
    temp_f6 = spF0 - (f32) sp154->effect_box.unkE[6];
    spF0 = temp_f6;
    move_object((Object *) sp154, temp_f10, temp_f8, temp_f6);
    sp154->racer.forwardVel =
        catmull_rom_interpolation(&spD0, 0, spEC) * sp90 *
        sp154->effect_box.unkE[2]; // index is wrong, also usage of effect_box is probably wrong, too
    temp_v0_8 = sp15C[0x2E];
    switch (temp_v0_8) { /* irregular */
        default:
            var_a1 = 1;
            var_fp_2 = &spC0;
            var_s6_2 = &spAC;
            var_t1_2 = &sp98;
            do {
                temp_f6_2 = var_fp_2[0];
                temp_f8_2 = var_fp_2[-1];
                var_fp_2++;
                temp_f2_3 = (f64) (temp_f6_2 - temp_f8_2);
                var_f0_2 = 0.0f;
                if (temp_f2_3 > 32768.0) {
                    var_f0_2 = (f32) ((f64) 0.0f - 65536.0);
                } else if (temp_f2_3 < -32768.0) {
                    var_f0_2 = (f32) ((f64) 0.0f + 65536.0);
                }
                var_s0_2 = var_a1;
                if (var_a1 < 5) {
                    temp_t8 = (5 - var_a1) & 3;
                    if (temp_t8 != 0) {
                        var_v0_2 = &(&spBC[0])[var_s0_2];
                        do {
                            var_s0_2++;
                            var_v0_2[0] += var_f0_2;
                            var_v0_2++;
                        } while ((temp_t8 + var_a1) != var_s0_2);
                        if (var_s0_2 != 5) {
                            goto block_71;
                        }
                    } else {
                    block_71:
                        var_v0_3 = &(&spBC[0])[var_s0_2];
                        do {
                            var_v0_3[1] += var_f0_2;
                            var_v0_3[0] += var_f0_2;
                            var_v0_3[2] += var_f0_2;
                            var_v0_3[3] += var_f0_2;
                            var_v0_3 += 4;
                        } while (var_v0_3 != &spD0);
                    }
                    var_s0_2 = var_a1;
                }
                temp_f6_3 = var_s6_2[0];
                temp_f8_4 = var_s6_2[-1];
                var_s6_2++;
                temp_f2_4 = (f64) (temp_f6_3 - temp_f8_4);
                var_f0_3 = 0.0f;
                if (temp_f2_4 > 32768.0) {
                    var_f0_3 = (f32) ((f64) 0.0f - 65536.0);
                } else if (temp_f2_4 < -32768.0) {
                    var_f0_3 = (f32) ((f64) 0.0f + 65536.0);
                }
                if (var_a1 < 5) {
                    temp_t6 = (5 - var_a1) & 3;
                    if (temp_t6 != 0) {
                        var_v0_4 = &(&spA8[0])[var_s0_2];
                        do {
                            var_s0_2++;
                            var_v0_4[0] += var_f0_3;
                            var_v0_4++;
                        } while ((temp_t6 + var_a1) != var_s0_2);
                        if (var_s0_2 != 5) {
                            goto block_83;
                        }
                    } else {
                    block_83:
                        var_v0_5 = &(&spA8[0])[var_s0_2];
                        do {
                            var_v0_5[1] += var_f0_3;
                            var_v0_5[0] += var_f0_3;
                            var_v0_5[2] += var_f0_3;
                            var_v0_5[3] += var_f0_3;
                            var_v0_5 += 4;
                        } while (var_v0_5 != &spBC[0]);
                    }
                    var_s0_2 = var_a1;
                }
                temp_f2_5 = (f64) (var_t1_2[0] - var_t1_2[-1]);
                var_f0_4 = 0.0f;
                if (temp_f2_5 > 32768.0) {
                    var_f0_4 = (f32) ((f64) 0.0f - 65536.0);
                } else if (temp_f2_5 < -32768.0) {
                    var_f0_4 = (f32) ((f64) 0.0f + 65536.0);
                }
                temp_t7 = (5 - var_a1) & 3;
                if (var_a1 < 5) {
                    if (temp_t7 != 0) {
                        var_v0_6 = &(&sp94[0])[var_s0_2];
                        do {
                            var_s0_2++;
                            var_v0_6[0] += var_f0_4;
                            var_v0_6++;
                        } while ((temp_t7 + var_a1) != var_s0_2);
                        if (var_s0_2 != 5) {
                            goto block_95;
                        }
                    } else {
                    block_95:
                        var_v0_7 = &(&sp94[0])[var_s0_2];
                        do {
                            var_v0_7[1] += var_f0_4;
                            var_v0_7[0] += var_f0_4;
                            var_v0_7[2] += var_f0_4;
                            var_v0_7[3] += var_f0_4;
                            var_v0_7 += 4;
                        } while (var_v0_7 != &spA8[0]);
                    }
                }
                var_a1++;
                var_t1_2 += 4;
            } while (var_a1 != 5);
            if (sp15C[0x3F] == 0) {
                sp154->racer.playerIndex = (s16) (s32) catmull_rom_interpolation(&spBC[0], 0, spEC);
                sp154->midi_fade_point.unk2 = (u16) (s32) catmull_rom_interpolation(&spA8[0], 0, spEC);
                sp154->effect_box.unk4 = (s16) (s32) catmull_rom_interpolation(&sp94[0], 0, spEC);
            } else {
                sp154->racer.playerIndex = (s16) (s32) lerp(&spBC[0], 0U, spEC);
                sp154->midi_fade_point.unk2 = (u16) (s32) lerp(&spA8[0], 0U, spEC);
                sp154->effect_box.unk4 = (s16) (s32) lerp(&sp94[0], 0U, spEC);
            }
        case 1:
            break;
        case 2:
            if (sp15C[0x3F] == 0) {
                cubic_spline_interpolation(&sp124, 0, spEC, &spF8);
                cubic_spline_interpolation(&sp110, 0, spEC, &spF4);
                cubic_spline_interpolation(&spFC, 0, spEC, &spF0);
            } else {
                lerp_and_get_derivative(&sp124, 0U, spEC, &spF8);
                lerp_and_get_derivative(&sp110, 0U, spEC, &spF4);
                lerp_and_get_derivative(&spFC, 0U, spEC, &spF0);
            }
            temp_f0_4 = sqrtf((spF8 * spF8) + (spF4 * spF4) + (spF0 * spF0));
            if (temp_f0_4 != 0.0f) {
                temp_f12_3 = (f32) (100.0 / (f64) temp_f0_4);
                spF8 *= temp_f12_3;
                spF4 *= temp_f12_3;
                spF0 *= temp_f12_3;
            }
            sp154->racer.playerIndex = arctan2_f(spF8, spF0) - 0x8000;
            sp154->midi_fade_point.unk2 = arctan2_f(spF4, 100.0f);
            break;
        case 3:
            var_a1_2 = 0;
            if (D_8011AE78 > 0) {
                temp_v0_9 = sp15C[0x3E];
                if (temp_v0_9 != (*D_8011AE74)->properties.common.unk4) {
                loop_55:
                    var_a1_2++;
                    if (var_a1_2 < D_8011AE78) {
                        if (temp_v0_9 != D_8011AE74[var_a1_2]->properties.common.unk4) {
                            goto loop_55;
                        }
                    }
                }
            }
            if (var_a1_2 != D_8011AE78) {
                temp_v1 = D_8011AE74[var_a1_2]->unk64;
                if (temp_v1 != NULL) {
                    spF8 = temp_v1->racer.animationSpeed - sp154->racer.animationSpeed;
                    spF4 = (f32) temp_v1->effect_box.unkE[2] - (f32) sp154->effect_box.unkE[2];
                    spF0 = (f32) temp_v1->effect_box.unkE[6] - (f32) sp154->effect_box.unkE[6];
                    temp_f0_5 = sqrtf((spF8 * spF8) + (spF4 * spF4) + (spF0 * spF0));
                    spEC = temp_f0_5;
                    if (temp_f0_5 > 0.0f) {
                        sp154->racer.playerIndex = arctan2_f(spF8, spF0) - 0x8000;
                        sp154->midi_fade_point.unk2 = arctan2_f(spF4, spEC);
                    }
                }
            }
            break;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_80021600.s")
#endif

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
    racer = &get_racer_object(PLAYER_ONE)->unk64->racer;
    racer->courseCheckpoint = 0;
    racer->checkpoint = 0;
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
        levelHeader = get_current_level_header();
        gChallengePrevMusic = levelHeader->music;
        gChallengePrevInstruments = levelHeader->instruments;
        levelHeader->music = SEQUENCE_TAJS_RACES;
        levelHeader->instruments = 0xFFFF;
        racerObj = get_racer_object(PLAYER_ONE);
        racer = &racerObj->unk64->racer;
        gIsTajChallenge = racer->vehicleID + 1;
        checkpointNode = func_800230D0(racerObj, racer);
        racer->cameraYaw = 0x8000 - racer->steerVisualRotation;
        racer->wrongWayCounter = 0;
        racer->startInput = 0;
        racer->courseCheckpoint = 0;
        racer->checkpoint = 0;
        racer->lap = 0;
        racer->countLap = 0;
        racer->lap_times[0] = 0;
        racer->lap_times[1] = 0;
        racer->lap_times[2] = 0;
        racer->unk1BA = 0;
        settings = get_settings();
        gEventCountdown = 80;
        D_8011ADB4 = 0;
        D_8011ADC0 = 1;
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
            func_8002BAB0(lvlSeg, newRacerEntry.common.x, newRacerEntry.common.z, yOut) ? yOut[0] : checkpointNode->y;
        newRacerEntry.common.size = 16;
        newRacerEntry.angleY = racer->steerVisualRotation;
        newRacerEntry.angleX = 0;
        newRacerEntry.angleZ = 0;
        newRacerEntry.playerIndex = 4;
        newRacerEntry.common.objectID = ASSET_OBJECT_ID_FLYINGCARPET;
        func_800619F4(0);
        racerObj = spawn_object(&newRacerEntry.common, OBJECT_SPAWN_UNK01);
        (*gRacers)[1] = racerObj;
        gRacersByPosition[1] = racerObj;
        gRacersByPort[1] = racerObj;
        racerObj->segment.level_entry = NULL;
        gNumRacers = 2;
        racer = &racerObj->unk64->racer;
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
            if (!(gObjPtrList[j]->segment.trans.flags & OBJ_FLAGS_PARTICLE) &&
                gObjPtrList[j]->behaviorId == BHV_PARK_WARDEN) {
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
        if (obj->behaviorId == BHV_GOLDEN_BALLOON && obj->segment.level_entry != NULL &&
            obj->segment.level_entry->goldenBalloon.challengeID > 0) {
            if (settings->tajFlags &&
                settings->tajFlags & (1 << (obj->segment.level_entry->goldenBalloon.challengeID + 2))) {
                obj->segment.trans.x_position = x;
                obj->segment.trans.y_position = y + 10.0;
                obj->segment.trans.z_position = z;
                obj->segment.object.segmentID = blockID;
                obj->properties.common.unk0 = 0;
                obj->segment.object.opacity = 0;
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

    levelHeader = get_current_level_header();
    levelHeader->race_type = RACETYPE_HUBWORLD;
    levelHeader->music = gChallengePrevMusic;
    levelHeader->instruments = gChallengePrevInstruments;
    minimap_opacity_set(1);

    // Only works with do {} while?
    i = 0;
    do {
        racer = &(*gRacers)[i]->unk64->racer;
        if (!racer) {}
        racer->raceFinished = 0;
        racer->lap = 0;
        racer->checkpoint = 0;
        racer->courseCheckpoint = 0;
    } while (++i < gNumRacers);

    free_object((*gRacers)[1]);
    gRacersByPosition[0] = (*gRacers)[0];
    gNumRacers = 1;
    for (i = gObjectListStart; i < gObjectCount; i++) {
        if (!(gObjPtrList[i]->segment.trans.flags & OBJ_FLAGS_PARTICLE) &&
            gObjPtrList[i]->behaviorId == BHV_PARK_WARDEN) {
            obj = gObjPtrList[i];
        }
    }
    racer = &(*gRacers)[0]->unk64->racer;
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
    start_level_music(1.0f);
    gIsTajChallenge = FALSE;
}

CheckpointNode *func_800230D0(Object *obj, Object_Racer *racer) {
    CheckpointNode *lastCheckpointNode;
    Camera *activeCameraSegment;
    s32 yOutCount;
    f32 yOut[9];
    Object *ptrList;
    s32 i;

    if (gNumberOfCheckpoints == 0) {
        lastCheckpointNode = NULL;
        for (i = 0; i < gObjectCount; i++) {
            ptrList = gObjPtrList[i];
            if (!(ptrList->segment.trans.flags & OBJ_FLAGS_PARTICLE) && (ptrList->behaviorId == BHV_SETUP_POINT)) {
                if (ptrList->properties.setupPoint.racerIndex == 0) {
                    obj->segment.trans.x_position = ptrList->segment.trans.x_position;
                    obj->segment.trans.y_position = ptrList->segment.trans.y_position;
                    obj->segment.trans.z_position = ptrList->segment.trans.z_position;
                    obj->segment.object.segmentID = ptrList->segment.object.segmentID;
                    i = gObjectCount;
                }
            }
        }
    } else {
        lastCheckpointNode = &gTrackCheckpoints[gNumberOfCheckpoints - 1];
        obj->segment.trans.x_position = lastCheckpointNode->x - (lastCheckpointNode->rotationZFrac * 35.0f);
        obj->segment.trans.y_position = lastCheckpointNode->y;
        obj->segment.trans.z_position = lastCheckpointNode->z + (lastCheckpointNode->rotationXFrac * 35.0f);
        obj->segment.object.segmentID = get_level_segment_index_from_position(
            obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
    }
    yOutCount = func_8002BAB0(obj->segment.object.segmentID, obj->segment.trans.x_position,
                              obj->segment.trans.z_position, yOut);
    if (yOutCount != 0) {
        obj->segment.trans.y_position = yOut[yOutCount - 1];
    }
    racer->prev_x_position = obj->segment.trans.x_position;
    racer->prev_y_position = obj->segment.trans.y_position;
    racer->prev_z_position = obj->segment.trans.z_position;
    if (lastCheckpointNode != NULL) {
        racer->steerVisualRotation = arctan2_f(lastCheckpointNode->rotationXFrac, lastCheckpointNode->rotationZFrac);
    } else {
        racer->steerVisualRotation = ptrList->segment.trans.rotation.y_rotation;
    }
    racer->checkpoint = 0;
    racer->courseCheckpoint = racer->lap * gNumberOfCheckpoints;
    obj->segment.trans.rotation.y_rotation = racer->steerVisualRotation;
    racer->unkD8.x = obj->segment.trans.x_position;
    racer->unkD8.y = obj->segment.trans.y_position + 15.0f;
    racer->unkD8.z = obj->segment.trans.z_position;
    racer->unkE4.x = obj->segment.trans.x_position;
    racer->unkE4.y = obj->segment.trans.y_position + 15.0f;
    racer->unkE4.z = obj->segment.trans.z_position;
    racer->unkF0.x = obj->segment.trans.x_position;
    racer->unkF0.y = obj->segment.trans.y_position + 15.0f;
    racer->unkF0.z = obj->segment.trans.z_position;
    racer->unkFC.x = obj->segment.trans.x_position;
    racer->unkFC.y = obj->segment.trans.y_position + 15.0f;
    racer->unkFC.z = obj->segment.trans.z_position;
    obj->interactObj->x_position = obj->segment.trans.x_position;
    obj->interactObj->y_position = obj->segment.trans.y_position;
    obj->interactObj->z_position = obj->segment.trans.z_position;
    // fake
    if (1) {}
    if (1) {}
    racer->velocity = 0.0f;
    racer->lateral_velocity = 0.0f;
    obj->segment.x_velocity = 0.0f;
    obj->segment.z_velocity = 0.0f;
    racer->vehicleID = racer->vehicleIDPrev;
    if (racer->playerIndex != -1) {
        set_active_camera(racer->playerIndex);
        activeCameraSegment = cam_get_active_camera_no_cutscenes();
        activeCameraSegment->trans.x_position = obj->segment.trans.x_position;
        activeCameraSegment->trans.y_position = obj->segment.trans.y_position;
        activeCameraSegment->trans.z_position = obj->segment.trans.z_position;
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
            if (!(tempObj->segment.trans.flags & OBJ_FLAGS_PARTICLE) && tempObj->behaviorId == BHV_TAJ_TELEPOINT) {
                diffX = tempObj->segment.trans.x_position - x;
                diffZ = tempObj->segment.trans.z_position - z;
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
    } else if (get_current_level_race_type() == RACETYPE_BOSS) {
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
s32 get_object_property_size(Object *obj, Object_64 *obj64) {
    s32 temp_v0;
    s32 ret = 0;

    obj->unk64 = obj64;

    switch (obj->segment.header->behaviorId) {
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
            ret = 0x4;
            break;
        case BHV_BUTTERFLY:
            temp_v0 = 0x10 - ((s32) obj64 & 0xF);
            obj->unk64 = (Object_64 *) &obj64->butterfly.triangles[0].verticesArray[temp_v0];
            ret = (temp_v0 + sizeof(Object_Butterfly));
            break;
        case BHV_FISH:
            temp_v0 = 0x10 - ((s32) obj64 & 0xF);
            obj->unk64 = (Object_64 *) &obj64->fish.triangles[0].verticesArray[temp_v0];
            ret = (temp_v0 + sizeof(Object_Fish));
            break;
        case BHV_CHARACTER_FLAG:
            temp_v0 = 0x10 - ((s32) obj64 & 0xF);
            obj->unk64 = (Object_64 *) &obj64->character_flag.triangles[0].verticesArray[temp_v0];
            ret = (temp_v0 + sizeof(Object_CharacterFlag));
            break;
        case BHV_UNK_5E:
            ret = 0x60;
            break;
        case BHV_TROPHY_CABINET:
            ret = sizeof(Object_TrophyCabinet);
            break;
        case BHV_FROG:
            ret = sizeof(Object_Frog);
            break;
        case BHV_FIREBALL_OCTOWEAPON_2:
            ret = sizeof(Object_Fireball_Octoweapon);
            break;
        default:
            obj->unk64 = NULL;
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
    obj->behaviorId = obj->segment.header->behaviorId;
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
    s32 flags = OBJECT_SPAWN_NONE;
    switch (behaviorId) {
        case BHV_RACER:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_UNK04 | OBJECT_SPAWN_ANIMATION |
                    OBJECT_SPAWN_INTERACTIVE;
            break;
        case BHV_SCENERY:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_INTERACTIVE;
            break;
        case BHV_WEAPON:
            flags = OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_UNK04 | OBJECT_SPAWN_INTERACTIVE;
            break;
        case BHV_DINO_WHALE:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_ANIMATION | OBJECT_SPAWN_INTERACTIVE;
            break;
        case BHV_DOOR:
        case BHV_TT_DOOR:
            flags = OBJECT_SPAWN_INTERACTIVE | OBJECT_SPAWN_UNK20;
            break;
        case BHV_WEAPON_BALLOON:
        case BHV_GOLDEN_BALLOON:
            flags = OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_INTERACTIVE;
            break;
        case BHV_HIT_TESTER:
        case BHV_HIT_TESTER_2:
        case BHV_SNOWBALL:
        case BHV_SNOWBALL_2:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_ANIMATION | OBJECT_SPAWN_INTERACTIVE |
                    OBJECT_SPAWN_UNK20;
            break;
        case BHV_SNOWBALL_3:
        case BHV_SNOWBALL_4:
        case BHV_HIT_TESTER_3:
        case BHV_HIT_TESTER_4:
            flags = OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_ANIMATION | OBJECT_SPAWN_INTERACTIVE | OBJECT_SPAWN_UNK20;
            break;
        case BHV_UNK_18:
            flags = OBJECT_SPAWN_UNK04;
            break;
        case BHV_STOPWATCH_MAN:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_ANIMATION | OBJECT_SPAWN_INTERACTIVE;
            break;
        case BHV_BANANA:
        case BHV_WORLD_KEY:
        case BHV_SILVER_COIN:
        case BHV_SILVER_COIN_2:
            flags = OBJECT_SPAWN_INTERACTIVE | OBJECT_SPAWN_SHADOW;
            break;
        case BHV_LOG:
            flags = OBJECT_SPAWN_INTERACTIVE | OBJECT_SPAWN_UNK20;
            break;
        case BHV_BRIDGE_WHALE_RAMP:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_ANIMATION | OBJECT_SPAWN_INTERACTIVE | OBJECT_SPAWN_UNK20;
            break;
        case BHV_RAMP_SWITCH:
            flags = OBJECT_SPAWN_INTERACTIVE | OBJECT_SPAWN_SHADOW;
            break;
        case BHV_SEA_MONSTER:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_ANIMATION;
            break;
        case BHV_COLLECT_EGG:
            flags = OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_INTERACTIVE;
            break;
        case BHV_UNK_30:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_ANIMATION;
            break;
        case BHV_UNK_3F:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_ANIMATION;
            break;
        case BHV_ANIMATED_OBJECT:
        case BHV_VEHICLE_ANIMATION:
        case BHV_PARK_WARDEN_2:
        case BHV_WIZPIG_SHIP:
        case BHV_ANIMATED_OBJECT_4:
        case BHV_PIG_ROCKETEER:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_ANIMATION;
            break;
        case BHV_CHARACTER_SELECT:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_ANIMATION;
            break;
        case BHV_TROPHY_CABINET:
        case BHV_DYNAMIC_LIGHT_OBJECT_2:
        case BHV_ROCKET_SIGNPOST:
        case BHV_ROCKET_SIGNPOST_2:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_INTERACTIVE | OBJECT_SPAWN_UNK20;
            break;
        case BHV_UNK_5B:
            flags = OBJECT_SPAWN_UNK01;
            break;
        case BHV_ANIMATED_OBJECT_2:
            flags = OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_ANIMATION;
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
            flags = OBJECT_SPAWN_INTERACTIVE;
            break;
        case BHV_ZIPPER_GROUND:
            flags = OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_INTERACTIVE;
            break;
        case BHV_ANIMATION:
        case BHV_CAMERA_ANIMATION:
        case BHV_BUTTERFLY:
            flags = OBJECT_SPAWN_SHADOW;
            break;
        case BHV_PARK_WARDEN:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_ANIMATION | OBJECT_SPAWN_INTERACTIVE;
            break;
        case BHV_FROG:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_ANIMATION;
            break;
        case BHV_UNK_72:
            flags = OBJECT_SPAWN_UNK01;
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
