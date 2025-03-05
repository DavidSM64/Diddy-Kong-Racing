/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8000B020 */

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

#define MAX_CHECKPOINTS 60
#define OBJECT_POOL_SIZE 0x15800
#define OBJECT_SPAWN_HEAP_SIZE 0x800
#define OBJECT_SLOT_COUNT 512
#define ASSET_OBJECT_HEADER_TABLE_LENGTH 304 // This isn't important, but it's the number of object headers
#define AINODE_COUNT 128
#define CAMCONTROL_COUNT 20

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
s16 gTimeTrialTime = 0x2A30;
s16 gTimeTrialVehicle = -1;
s16 gTimeTrialCharacter = 0;
u8 gHasGhostToSave = FALSE;
u8 gTimeTrialStaffGhost = FALSE;
u8 gBeatStaffGhost = FALSE;
s8 D_800DC73C = 0;
s8 D_800DC740 = 0;
s8 gSwapLeadPlayer = FALSE;
s8 D_800DC748 = 0;
s32 D_800DC74C[2] = { 0, 0 }; // Have a feeling these are both the same array.
s32 D_800DC754[2] = { 0, 0 };
Object *gShieldEffectObject = NULL;
s32 D_800DC760 = 9; // Currently unknown, might be a different type.
Object *gMagnetEffectObject = NULL;
s32 D_800DC768 = 0; // Currently unknown, might be a different type.

UNUSED f32 D_800DC76C[15] = {
    1.0f,  0.70711f,  0.70711f,  1.0f,  0.0f, 0.70711f,  -0.70711f, 0.0f,
    -1.0f, -0.70711f, -0.70711f, -1.0f, 0.0f, -0.70711f, 0.70711f,
};

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
FadeTransition gRaceEndFade = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 40, -1);
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
f32 D_8011AD28;
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
ObjectHeader *(*gLoadedObjectHeaders)[ASSET_OBJECT_HEADER_TABLE_LENGTH];
u8 (*gObjectHeaderReferences)[ASSET_OBJECT_HEADER_TABLE_LENGTH];
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
s16 D_8011AE7C;
s8 D_8011AE7E;
s16 gTTGhostTimeToBeat;
s16 gPrevTimeTrialVehicle; // Current Vehicle being used in track?
s16 gMapDefaultVehicle;    // Vehicle enum
s32 D_8011AE88;
Gfx *gObjectCurrDisplayList;
MatrixS *gObjectCurrMatrix;
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
Object *(*gRacers)[10];
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
s32 D_8011AF60[2];
s32 D_8011AF68[32];
VertexPosition gEnvmapPos;
s16 D_8011AFEE;
s32 D_8011AFF0;
unk800179D0 *D_8011AFF4;
s32 D_8011AFF8;
s32 D_8011AFFC;
s32 D_8011B000;
s32 D_8011B004;
s32 D_8011B008;
u8 D_8011B010[16];
Object *D_8011B020[NUMBER_OF_CHARACTERS];
s32 D_8011B048[4];
s32 D_8011B058[4];
u8 D_8011B068[16];
ColourRGBA D_8011B078[NUMBER_OF_CHARACTERS]; // Note: D_8011B078 might not be a ColourRGBA.

extern s16 gGhostMapID;

/******************************/

typedef struct LevelObjectEntry_unk8000B020 {
    LevelObjectEntryCommon common;
    s8 unk8;
    s8 unk9;
} LevelObjectEntry_unk8000B020;

void func_8000B020(s32 numberOfVertices, s32 numberOfTriangles) {
    Asset20 *miscAsset20;
    LevelObjectEntry_unk8000B020 objEntry;
    s32 i;

    D_800DC754[0] = (s32) mempool_alloc_safe(((numberOfTriangles * 16) + (numberOfVertices * 10)) * 2, COLOUR_TAG_BLUE);
    D_800DC754[1] = D_800DC754[0] + (numberOfTriangles * 16);
    D_800DC74C[0] = D_800DC754[1] + (numberOfTriangles * 16);
    D_800DC74C[1] = D_800DC74C[0] + (numberOfVertices * 10);
    D_8011AFF8 = numberOfVertices;
    D_8011AFFC = 0;
    D_8011B000 = numberOfTriangles;
    D_8011B004 = 0;
    D_8011B008 = 0;
    miscAsset20 = (Asset20 *) get_misc_asset(ASSET_MISC_20);
    for (i = 0; i < ARRAY_COUNT(D_8011B020); i++) {
        objEntry.common.objectID = ASSET_OBJECT_ID_BOOST;
        objEntry.common.size = 10;
        objEntry.common.x = 0;
        objEntry.common.y = 0;
        objEntry.common.z = 0;
        objEntry.unk8 = i;
        D_8011B020[i] = spawn_object(&objEntry.common, 1);
        if (D_8011B020[i] != NULL) {
            D_8011B020[i]->properties.common.unk0 = 0;
            D_8011B020[i]->properties.common.unk4 = 0;
            miscAsset20[i].unk70 = 0;
            miscAsset20[i].unk74 = 0.0f;
            miscAsset20[i].unk78 = (Sprite *) func_8007C12C(miscAsset20[i].unk6C, 0);
            miscAsset20[i].unk7C = load_texture(miscAsset20[i].unk6E);
            miscAsset20[i].unk72 = get_random_number_from_range(0, 255);
            miscAsset20[i].unk73 = 0;
            D_8011B010[i] = get_random_number_from_range(0, 255);
        }
        D_8011B068[i] = 1;
    }
    D_800DC760 = 9;
    objEntry.common.objectID = ASSET_OBJECT_ID_SHIELD;
    objEntry.common.size = 10;
    objEntry.common.x = 0;
    objEntry.common.y = 0;
    objEntry.common.z = 0;
    gShieldEffectObject = spawn_object((LevelObjectEntryCommon *) &objEntry, 0);
    for (i = 0; i < ARRAY_COUNT(D_8011B078); i++) {
        D_8011B078[i].r = 0;
        D_8011B078[i].g = get_random_number_from_range(0, 255);
        D_8011B078[i].b = get_random_number_from_range(0, 255);
        D_8011B078[i].a = 0;
    }
    objEntry.common.objectID = ASSET_OBJECT_ID_AINODE;
    objEntry.common.size = 138;
    objEntry.common.x = 0;
    objEntry.common.y = 0;
    objEntry.common.z = 0;
    gMagnetEffectObject = spawn_object((LevelObjectEntryCommon *) &objEntry, 0);
}

void func_8000B290(void) {
    Sprite *sprite;
    TextureHeader *texture;
    s32 temp_a0;
    Asset20 *asset20;
    u32 i;

    temp_a0 = D_800DC754[0];
    if (temp_a0 != 0) {
        mempool_free((void *) temp_a0);
        D_800DC754[0] = 0;
        D_800DC754[1] = 0;
        D_800DC74C[0] = 0;
        D_800DC74C[1] = 0;
    }
    asset20 = (Asset20 *) get_misc_asset(ASSET_MISC_20);
    for (i = 0; i < 10; i++) {
        sprite = asset20[i].unk78;
        if (sprite != NULL) {
            free_sprite(sprite);
            asset20[i].unk78 = NULL;
        }
        texture = asset20[i].unk7C;
        if (texture != NULL) {
            free_texture(texture);
            asset20[i].unk7C = NULL;
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

#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_8000B38C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_8000B750.s")

void func_8000BADC(s32 updateRate) {
    s32 i;
    Asset20 *asset20Part;
    s32 temp;
    Asset20 *asset20;
    f32 updateRateF;
    Object_Racer *racer;

    D_8011B008 = 1 - D_8011B008;
    D_8011AFFC = 0;
    D_8011B004 = 0;
    asset20 = (Asset20 *) get_misc_asset(ASSET_MISC_20);
    D_800DC760 = 9;
    for (i = 0; i < 10; i++) {
        if (D_8011B068[i] && D_8011B020[i] != NULL) {
            D_8011B020[i]->properties.common.unk0 = 0;
        }
        D_8011B068[i] = 1;
    }
    for (i = 0; i < gNumRacers; i++) {
        updateRateF = (f32) updateRate;
        if (osTvType == OS_TV_TYPE_PAL) {
            updateRateF *= 1.2f;
        }
        racer = &(*gRacers)[i]->unk64->racer;
        asset20Part = &asset20[racer->racerIndex];
        if (racer->shieldTimer != 0) {
            D_8011B010[racer->racerIndex] += updateRate;
        }
        asset20Part->unk72 += updateRate;
        if (racer->boostTimer != 0) {
            asset20Part->unk73 = 20;
            if (asset20Part->unk70 == 0) {
                asset20Part->unk74 += updateRateF * 0.25f;
                updateRateF = 0.0f;
                if (asset20Part->unk74 > 2.4f) {
                    asset20Part->unk74 = (f32) (4.8f - asset20Part->unk74);
                    asset20Part->unk70 = 1;
                }
            }
            if (asset20Part->unk70 == 1) {
                asset20Part->unk74 -= updateRateF * 0.25f;
                updateRateF = 0.0f;
                if (asset20Part->unk74 < 1.0f) {
                    asset20Part->unk70 = 2;
                    asset20Part->unk74 = 1.0f - asset20Part->unk74;
                }
            }
            if (asset20Part->unk70 == 2) {
                if (asset20Part->unk74 < 1.0f) {
                    asset20Part->unk74 += updateRateF * 0.125f;
                    if (asset20Part->unk74 > 1.0f) {
                        asset20Part->unk74 = 1.0f;
                    }
                }
            }
        } else {
            if (asset20Part->unk73 > 0) {
                asset20Part->unk73 -= updateRate;
            } else {
                if (asset20Part->unk70 == 2) {
                    asset20Part->unk74 -= updateRateF * 0.05f;
                    updateRateF = 0.0f;
                    if (asset20Part->unk74 < 0.0f) {
                        asset20Part->unk70 = 0;
                        asset20Part->unk74 += 1.0f;
                    }
                }
                if (asset20Part->unk70 < 2) {
                    asset20Part->unk74 -= (updateRateF * 0.1f);
                    if (asset20Part->unk74 < 0.0f) {
                        asset20Part->unk74 = 0.0f;
                    }
                    asset20Part->unk70 = 0;
                }
            }
        }
        if ((asset20Part->unk70 > 0) || (asset20Part->unk74 > 0.0f)) {
            func_8000B750((*gRacers)[i], racer->racerIndex, racer->vehicleIDPrev, racer->boostType, 0);
        }
        temp = racer->racerIndex;
        D_8011B078[temp].g += updateRate;
        D_8011B078[temp].b += updateRate;
        if (racer->magnetTimer != 0) {
            if (D_8011B078[temp].a + (updateRate << 2) < 32) {
                D_8011B078[temp].a += (updateRate << 2);
            } else {
                D_8011B078[temp].a = 32;
            }
        } else {
            if (D_8011B078[temp].a - updateRate > 0) {
                D_8011B078[temp].a -= updateRate;
            } else {
                D_8011B078[temp].a = 0;
            }
        }
    }
    if (gMagnetEffectObject != NULL) {
        func_80011134(gMagnetEffectObject, updateRate);
    }
}

Object *func_8000BF44(s32 arg0) {
    if (arg0 == -1) {
        arg0 = D_800DC760;
    }
    if (arg0 < 0 || arg0 >= 10) {
        return NULL;
    }
    return D_8011B020[arg0];
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

#ifdef NON_EQUIVALENT
// Decrypts cheats
void decrypt_magic_codes(s32 *data, s32 length) {
    u8 sp3;
    u8 sp2;
    u8 sp1;
    u8 sp0;
    // s32 numWords;
    s32 i;

    // numWords = length / 4;

    for (i = 0; i < length; i++) {
        sp0 = ((data[i + 3] & 0xC0) >> 6) | (data[i + 0] & 0xC0) | ((data[i + 1] & 0xC0) >> 2) |
              ((data[i + 2] & 0xC0) >> 4);
        sp1 = ((data[i + 3] & 0x30) >> 4) | ((data[i + 0] & 0x30) << 2) | (data[i + 1] & 0x30) |
              ((data[i + 2] & 0x30) >> 2);
        sp2 =
            ((data[i + 3] & 0xC) >> 2) | ((data[i + 0] & 0xC) << 4) | ((data[i + 1] & 0xC) << 2) | (data[i + 2] & 0xC);
        sp3 = (data[i + 3] & 3) | (data[i + 0] << 6) | ((data[i + 1] & 3) << 4) | ((data[i + 2] & 3) << 2);
        data[i + 0] = ((sp0 & 0x55) << 1) | ((sp0 & 0xAA) >> 1);
        data[i + 1] = ((sp1 & 0x55) << 1) | ((sp1 & 0xAA) >> 1);
        data[i + 2] = ((sp2 & 0x55) << 1) | ((sp2 & 0xAA) >> 1);
        data[i + 3] = ((sp3 & 0x55) << 1) | ((sp3 & 0xAA) >> 1);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/objects/decrypt_magic_codes.s")
#endif

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
    D_8011AE7E = 1;
    D_8011AE7C = 0;
    gTransformTimer = 0;
    gIsTajChallenge = FALSE;
    gTajRaceInit = 0;
    D_8011AF60[0] = 0;
    D_8011AE00 = 0;
    D_8011AE01 = 1;
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
    D_800DC748 = 0;
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
    ObjectSegment *cutsceneCameraSegment; // sp74
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
        cutsceneCameraSegment = get_cutscene_camera_segment();
        cutsceneID = (u8) cutsceneCameraSegment->object.animationID;
        cutsceneCameraSegment->object.animationID = 1;
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
        if (!(curObj->segment.trans.flags & OBJ_FLAGS_DEACTIVATED)) {
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
            if (vehicle >= VEHICLE_TRICKY) {
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
            if ((gameMode != GAMEMODE_MENU || D_8011AD3C == 2) && vehicle < VEHICLE_TRICKY) {
                curRacer->vehicleSound = func_80004B40(curRacer->characterId, curRacer->vehicleID);
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
            newRacerObj = spawn_object((LevelObjectEntryCommon *) entry, 1);
            newRacerObj->segment.level_entry = NULL;
            newRacerObj->behaviorId = BHV_TIMETRIAL_GHOST;
            newRacerObj->shadow->scale = 0.01f;
            newRacerObj->interactObj->flags = 0;
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
            newRacerObj = spawn_object((LevelObjectEntryCommon *) entry, 1);
            newRacerObj->segment.level_entry = NULL;
            newRacerObj->behaviorId = BHV_TIMETRIAL_GHOST;
            newRacerObj->shadow->scale = 0.01f;
            newRacerObj->interactObj->flags = 0;
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
                    if (curRacerObj->unk68[i2]->unk20 != 0) {
                        curRacerObj->unk68[i2]->unk20 = (var_s4 * 2);
                    }
                }
            }
        } else {
            // curRacer is a human racer.
            for (i2 = 0; i2 < curRacerObj->segment.header->numberOfModelIds; i2++) {
                if (curRacerObj->unk68[i2] != NULL) {
                    if (curRacerObj->unk68[i2]->unk20 != 0) {
                        curRacerObj->unk68[i2]->unk20 = 0;
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
                newRacerObj = spawn_object((LevelObjectEntryCommon *) entry, 1);
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
        cutsceneCameraSegment->object.animationID = cutsceneID;
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
    if (gOverworldVehicle < VEHICLE_TRICKY) {
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
    player = spawn_object((LevelObjectEntryCommon *) &spawnObj, 0x10 | 0x1);
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

#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_8000E5EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_8000E79C.s")

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
UNUSED s32 get_object_count(void) {
    return gObjectCount;
}

/**
 * Return the number of particles currently existing.
 */
UNUSED s32 get_particle_count(void) {
    return gParticleCount;
}

void func_8000E9D0(Object *arg0) {
    arg0->segment.trans.flags |= OBJ_FLAGS_DEACTIVATED;
    func_800245B4(arg0->segment.object.unk2C | (OBJ_FLAGS_DEACTIVATED | OBJ_FLAGS_INVISIBLE));
    gObjPtrList[gObjectCount++] = arg0;
    if (1) {} // Fakematch
    gParticleCount++;
}

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
    curObj = &(*gSpawnObjectHeap)[0];
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
    curObj->segment.camera.unk34 = curObj->segment.header->unk50 * curObj->segment.trans.scale;
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
        for (var_a2 = var_a2; var_a2 < assetCount; var_a2++) {
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
        for (var_a2 = var_a2; var_a2 < assetCount; var_a2++) {
            curObj->unk68[var_a2] = (Object_68 *) load_texture(curObj->segment.header->modelIds[var_a2]);
            if (curObj->unk68[var_a2] == NULL) {
                var_v1 = TRUE;
            }
        }
    } else {
        for (var_a2 = var_a2; var_a2 < assetCount; var_a2++) {
            curObj->unk68[var_a2] = (Object_68 *) func_8007C12C(curObj->segment.header->modelIds[var_a2], 10);
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
        sizeOfobj = init_object_water_effect(curObj, (ShadowData *) address);
        address = (u32 *) ((uintptr_t) address + sizeOfobj);
        if (sizeOfobj == 0) {
            if (D_8011AE50 != NULL) {
                free_texture((u32) D_8011AE50);
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
        curObj->lightData = address;
        sizeOfobj = (s32) ((uintptr_t) address + (curObj->segment.header->numLightSources * 4)) - (uintptr_t) curObj;
    }
    newObj = mempool_alloc_pool((MemoryPoolSlot *) gObjectMemoryPool, sizeOfobj);
    if (newObj == NULL) {
        if (D_8011AE50 != NULL) {
            free_texture((u32) D_8011AE50);
        }
        if (D_8011AE54 != NULL) {
            free_texture((u32) D_8011AE54);
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
            (ShadowData *) (((uintptr_t) newObj + (uintptr_t) newObj->waterEffect) - (uintptr_t) gSpawnObjectHeap);
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
            (u32 *) (((uintptr_t) newObj + (uintptr_t) newObj->lightData) - (uintptr_t) gSpawnObjectHeap);
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
            free_texture(D_8011AE50);
        }
        if (D_8011AE54 != NULL) {
            free_texture(D_8011AE54);
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
                free_texture((TextureHeader *) (s32) obj->unk68[i]);
            }
        }
    } else { // Sprite
        for (i = 0; i < count; i++) {
            if (obj->unk68[i] != NULL) {
                free_sprite((Sprite *) (s32) obj->unk68[i]);
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
        obj->lightData[i] = (Object_LightData *) add_object_light(obj, &obj->segment.header->unk24[i]);
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
            set_shading_properties(obj->shading, obj->segment.header->shadeBrightness,
                                   obj->segment.header->shadeAmbient, 0, obj->segment.header->shadeAngleY,
                                   obj->segment.header->shadeAngleZ);
            if (obj->segment.header->unk3D != 0) {
                obj->shading->unk4 = obj->segment.header->unk3A;
                obj->shading->unk5 = obj->segment.header->unk3B;
                obj->shading->unk6 = obj->segment.header->unk3C;
                obj->shading->unk7 = obj->segment.header->unk3D;
                obj->shading->unk8 = -(obj->shading->unk1C >> 1);
                obj->shading->unkA = -(obj->shading->unk1E >> 1);
                obj->shading->unkC = -(obj->shading->unk20 >> 1);
            }
            returnSize = sizeof(ShadeProperties);
        }
    } else if (obj->segment.header->modelType == OBJECT_MODEL_TYPE_SPRITE_BILLBOARD) {
        obj->shading->unk0 = 1.0f;
        shadeData->unk4 = 0xFF;
        shadeData->unk5 = 0xFF;
        shadeData->unk6 = 0xFF;
        shadeData->unk7 = 0;
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
            partInitTrigger((Particle *) &obj->particleEmitter[i].unk0, (particleDataEntry[i].upper >> 8) & 0xFF,
                            particleDataEntry[i].upper & 0xFF);
        } else {
            func_800AF29C((Particle *) &obj->particleEmitter[i].unk0, (particleDataEntry[i].upper >> 0x18) & 0xFF,
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
    objHeader = ((ObjectSegment *) obj)->header;
    if (objHeader->shadowGroup) {
        shadow->texture = load_texture((s32) ((ObjectHeader *) objHeader)->unk34);
        objHeader = ((ObjectSegment *) obj)->header;
    }
    shadow->scale = objHeader->shadowScale;
    shadow->meshStart = -1;
    D_8011AE50 = shadow->texture;
    if (((ObjectSegment *) obj)->header->shadowGroup && shadow->texture == NULL) {
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
            object->unk68[i] = (Object_68 *) func_8007C12C(object->segment.header->modelIds[i], 10);
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
    func_800245B4(object->objectID | OBJ_FLAGS_DEACTIVATED);
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
            if (search_indx < D_8011AE7C) {
                D_8011AE7C--;
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

#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_800101AC.s")

#ifdef NON_MATCHING
// Minor regalloc diffs
// obj_update
void func_80010994(s32 updateRate) {
    s32 i;
    s32 tempVal;
    Object_Racer *racer;
    Object *obj;
    s32 sp54;
    Object_68 *obj68;
    UNUSED Object_64 *obj64;

    func_800245B4(-1);
    gEventStartTimer = gEventCountdown;
    if ((gEventCountdown > 0) && (race_starting() != 0)) {
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
    for (i = 0; i < gNumRacers; i++) {
        obj = (*gRacers)[i];
        racer = &obj->unk64->racer;
        racer->prev_x_position = (f32) (*gRacers)[i]->segment.trans.x_position;
        racer->prev_y_position = (f32) (*gRacers)[i]->segment.trans.y_position;
        racer->prev_z_position = (f32) (*gRacers)[i]->segment.trans.z_position;
    }
    i = 1; // FAKEMATCH
    func_800142B8();
    process_object_interactions();
    func_8001E89C();
    for (i = 0; i < D_8011AE70; i++) {
        run_object_loop_func(D_8011AE6C[i], updateRate);
    }
    func_8001E6EC(1);
    for (i = 0; i < D_8011AE70; i++) {
        func_8001709C(D_8011AE6C[i]);
    }
    tempVal = gObjectCount;
    for (i = gObjectListStart; i < tempVal; i++) {
        obj = gObjPtrList[i];
        if (!(obj->segment.trans.flags & OBJ_FLAGS_DEACTIVATED)) {
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

                        // FAKEMATCH
                        if (!gObjPtrList) {}

                        if (obj68 != NULL) {
                            if (1) {} // FAKEMATCH
                            obj68->objModel->unk52 = updateRate;
                        }
                    }
                    if (obj->segment.header->unk72 != 0xFF) {
                        func_80014090(obj, updateRate, obj->segment.header);
                    }
                }
            }
        }
    }
    for (i = 0; i < gNumRacers; i++) {
        update_player_racer((*gRacers)[i], updateRate);
    }
    if (get_current_level_race_type() == 0) {
        for (i = 0; i < gNumRacers; i++) {
            racer = &gRacersByPosition[i]->unk64->racer;
            if (racer->playerIndex != -1) {
                increment_ai_behaviour_chances(gRacersByPosition[i], racer, updateRate);
                i = gNumRacers; // Why not just break?
            }
        }
    }
    func_8000BADC(updateRate);
    for (i = gObjectListStart; i < tempVal; i++) {
        obj = gObjPtrList[i];
        if ((!(obj->segment.trans.flags & OBJ_FLAGS_DEACTIVATED) && (obj->behaviorId == BHV_WEAPON)) ||
            (obj->behaviorId == BHV_FOG_CHANGER)) {
            run_object_loop_func(obj, updateRate);
        }
    }
    if (gParticleCount > 0) {
        for (i = gObjectListStart; i < tempVal; i++) {
            obj = gObjPtrList[i];
            if (obj->segment.trans.flags & OBJ_FLAGS_DEACTIVATED) {
                // Why is this object being treated as a Particle?
                handle_particle_movement((Particle *) obj, updateRate);
            }
        }
    }
    do { // FAKEMATCH
        lightUpdateLights(updateRate);
        if (get_light_count() > 0) {
            for (i = gObjectListStart; i < gObjectCount; i++) {
                obj = gObjPtrList[i];
                if (!(obj->segment.trans.flags & OBJ_FLAGS_DEACTIVATED) && (obj->shading != NULL)) {
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
        func_80008438(gRacersByPort, gNumRacers, updateRate);
        gPathUpdateOff = TRUE;
        gObjectUpdateRateF = (f32) updateRate;
        D_8011AD24[0] = 0;
        D_8011AD53 = 0;
        transform_player_vehicle();
        dialogue_try_close();
        func_800179D0();
    } while (0); // FAKEMATCH
    if (D_8011AF00 == 1) {
        if ((gEventCountdown == 0x50) && (gCutsceneID == 0)) {
            sp54 = 0;
            for (i = 0; i < MAXCONTROLLERS; i++) {
                tempVal = get_buttons_pressed_from_player(i);
                sp54 |= tempVal;
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
#else
#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_80010994.s")
#endif

#ifdef NON_EQUIVALENT
void func_80011134(Object *arg0, s32 arg1) {
    s32 sp5C;
    ObjectModel *temp_s3;
    TriangleBatchInfo *temp_s4;
    TriangleBatchInfo *var_s0;
    TextureHeader *var_t5;
    s16 temp_s5;
    s32 var_s1;
    u8 temp_v0;

    temp_s3 = arg0->unk68[arg0->segment.object.modelIndex]->objModel;
    temp_s5 = temp_s3->unk50;
    temp_s4 = temp_s3->batches;
    for (var_s1 = 0; temp_s5 > 0 && var_s1 < temp_s3->numberOfBatches; var_s1++) {
        var_s0 = &temp_s4[var_s1];
        if (var_s0->flags & 0x10000) { // Texture is animated
            temp_v0 = var_s0->textureIndex;
            if (temp_v0 != 0xFF) {
                var_t5 = temp_s3->textures[temp_v0].texture;
                sp5C = var_s0->unk7 << 6;
                tex_animate_texture(var_t5, temp_s4[var_s1].flags, &sp5C, arg1);
                var_s0->unk7 = sp5C >> 6;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_80011134.s")
#endif

#ifdef NON_EQUIVALENT
// Probably NON_MATCHING, but not sure.
// This is a function for doors
void func_80011264(ObjectModel *model, Object *obj) {
    s32 current;
    s32 remaining;
    s32 i;
    Object_Door *door;
    TriangleBatchInfo *batch;

    if (model->unk50 > 0) {
        batch = &model->batches[0];
        door = &obj->unk64->door;
        current = ((door->balloonCount / 10) - 1) << 2;
        if (model->textures[batch->textureIndex].texture) {} // fakematch
        if (1) {                                             // fakematch
            remaining = ((door->balloonCount % 10) << 2);
        }
        for (i = 0; i < model->numberOfBatches; i++, batch++) {
            if (batch->flags & 0x10000) {
                if (batch->textureIndex != 0xFF) { // 0xFF = No Texture
                    if (model->textures[batch->textureIndex].texture->numOfTextures > 0x900) {
                        batch->unk7 = remaining;
                    } else if (current >= 0) {
                        batch->unk7 = current;
                    }
                    if (door) {} // fakematch
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_80011264.s")
#endif

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
                play_sound_at_position(soundId, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                       obj->segment.trans.z_position, 4, NULL);
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
                       TextureHeader *tex, u32 flags, u32 texOffset, f32 scale) {
    s32 hasTexture = FALSE;
    camera_push_model_mtx(&gObjectCurrDisplayList, &gObjectCurrMatrix, &obj->segment.trans, scale, 0.0f);
    gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
    gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 255, 0);
    if (tex != NULL) {
        hasTexture = TRUE;
    }
    load_and_set_texture(&gObjectCurrDisplayList, (TextureHeader *) tex, flags, texOffset);
    gSPVertexDKR(gObjectCurrDisplayList++, OS_K0_TO_PHYSICAL(verts), numVertices, 0);
    gSPPolygon(gObjectCurrDisplayList++, OS_K0_TO_PHYSICAL(triangles), numTriangles, hasTexture);
    apply_matrix_from_stack(&gObjectCurrDisplayList);
}

/**
 * A few objects use unconventional means to render. They are handled here.
 */
void render_3d_misc(Object *obj) {
    f32 scale;
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
            scale = obj->segment.level_entry->fish.unkD;
            scale *= 0.01f;
            render_misc_model(obj, &objData->fish.vertices[objData->fish.unkFC * 6], 6, objData->fish.triangles, 8,
                              objData->fish.texture, RENDER_Z_COMPARE | RENDER_FOG_ACTIVE | RENDER_CUTOUT, 0, scale);
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
    Object_68 *gfxData;

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
        gDPSetEnvColor(gObjectCurrDisplayList++, obj->shading->unk4, obj->shading->unk5, obj->shading->unk6,
                       obj->shading->unk7);
    } else if (obj->behaviorId == BHV_LAVA_SPURT) {
        hasEnvCol = TRUE;
        gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 0, 255);
    } else {
        gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 255, 0);
    }
    gfxData = obj->unk68[obj->segment.object.modelIndex];
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
            bubbleTrap = (Object *) obj->unk64->weapon.target;
            if (bubbleTrap == NULL) {
                bubbleTrap = obj;
            }
        }
        render_bubble_trap(&bubbleTrap->segment.trans, gfxData, (Object *) &objTrans,
                           RENDER_Z_COMPARE | RENDER_SEMI_TRANSPARENT | RENDER_Z_UPDATE);
    } else {
        render_sprite_billboard(&gObjectCurrDisplayList, &gObjectCurrMatrix, &gObjectCurrVertexList, obj,
                                (unk80068514_arg4 *) gfxData, flags);
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
    s32 alpha;
    s32 spB0;
    s32 obj60_unk0;
    s32 hasOpacity;
    s32 hasEnvCol;
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
    Object_68 *something;

    obj68 = obj->unk68[obj->segment.object.modelIndex];
    if (obj68 != NULL) {
        objModel = obj68->objModel;
        hasOpacity = FALSE;
        hasEnvCol = FALSE;
        intensity = 255;
        if (obj->shading != NULL) {
            intensity = (s32) (obj->shading->unk0 * 255.0f * gCurrentLightIntensity);
            hasOpacity = TRUE;
            hasEnvCol = TRUE;
        }
        if (obj->behaviorId == BHV_RACER) {
            racerObj = &obj->unk64->racer;
            object_do_player_tumble(obj);
        } else {
            racerObj = NULL;
        }
        if (obj68->unk20 <= 0) {
            obj->unk44 = (Vertex *) obj68->unk4[obj68->animationTaskNum];
            if (obj68->unk1E == 2) {
                object_animate(obj);
            }
            if (obj68->unk1E && objModel->unk40 != NULL) {
                flags = TRUE;
                if (racerObj != NULL && racerObj->vehicleID < VEHICLE_TRICKY &&
                    racerObj->playerIndex == PLAYER_COMPUTER) {
                    flags = FALSE;
                }
                if (get_viewport_count() != VIEWPORTS_COUNT_1_PLAYER) {
                    flags = FALSE;
                }
                obj->unk44 = (Vertex *) obj68->unk4[obj68->animationTaskNum];
                if (obj->behaviorId == BHV_UNK_3F) { // 63 = stopwatchicon, stopwatchhand
                    calc_dyn_light_and_env_map_for_object(objModel, obj, 0, gCurrentLightIntensity);
                } else if (flags) {
                    calc_dyn_light_and_env_map_for_object(objModel, obj, -1, gCurrentLightIntensity);
                } else {
                    func_800245F0(objModel, obj, gCurrentLightIntensity);
                }
            }
            if ((racerObj != NULL) && (racerObj->playerIndex == PLAYER_COMPUTER) &&
                (racerObj->vehicleID < VEHICLE_TRICKY)) {
                obj68->unk20 = 2;
            } else {
                obj68->unk20 = 1;
            }
        }
        obj->unk44 = (Vertex *) obj68->unk4[obj68->animationTaskNum];
        if (obj->behaviorId == BHV_DOOR) {
            func_80011264(objModel, obj);
        }
        if (objModel->unk52 && objModel->unk50 > 0) {
            func_80011134(obj, objModel->unk52);
            obj68->objModel->unk52 = 0;
        }
        camera_push_model_mtx(&gObjectCurrDisplayList, &gObjectCurrMatrix, &obj->segment.trans, D_8011AD28, 0);
        spB0 = FALSE;
        if (racerObj != NULL) {
            object_undo_player_tumble(obj);
            if (obj->segment.object.animationID == 0 || racerObj->vehicleID >= VEHICLE_TRICKY) {
                apply_head_turning_matrix(&gObjectCurrDisplayList, &gObjectCurrMatrix, obj68, racerObj->headAngle);
                spB0 = TRUE;
            } else {
                racerObj->headAngle = 0;
            }
        }
        alpha = obj->segment.object.opacity;
        if (alpha > 255) {
            alpha = 255;
        }
        // If the behavior is a water zipper, then halve it's transparency.
        if (obj->behaviorId == BHV_ZIPPER_WATER) {
            alpha >>= 1;
        }
        if (alpha < 255) {
            hasOpacity = TRUE;
        }
        if (hasEnvCol) {
            gDPSetEnvColor(gObjectCurrDisplayList++, obj->shading->unk4, obj->shading->unk5, obj->shading->unk6,
                           obj->shading->unk7);
        } else {
            gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 255, 0);
        }
        if (obj->segment.header->unk71) {
            gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, obj->shading->unk18, obj->shading->unk19,
                            obj->shading->unk1A, alpha);
            enable_primitive_colour();
        } else if (hasOpacity) {
            gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, intensity, intensity, intensity, alpha);
        } else {
            gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
        }
        if (alpha < 255) {
            meshBatch = render_mesh(objModel, obj, 0, RENDER_SEMI_TRANSPARENT, spB0);
        } else {
            meshBatch = render_mesh(objModel, obj, 0, RENDER_NONE, spB0);
        }
        if (obj->segment.header->unk71) {
            if (hasOpacity) {
                gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, intensity, intensity, intensity, alpha);
            } else {
                gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            }
            disable_primitive_colour();
        }
        if (obj->unk60 != NULL) {
            obj60_unk0 = obj->unk60->unk0;
            if (racerObj != NULL && racerObj->vehicleID == VEHICLE_FLYING_CAR) {
                obj60_unk0 = 0;
            }
            for (i = 0; i < obj60_unk0; i++) {
                loopObj = ((Object **) obj->unk60)[i + 1];
                if (!(loopObj->segment.trans.flags & OBJ_FLAGS_INVISIBLE)) {
                    index = obj->unk60->unk2C[i];
                    if (index >= 0 && index < objModel->unk18) {
                        something = loopObj->unk68[loopObj->segment.object.modelIndex];
                        vtxX = obj->unk44[objModel->unk14[index]].x;
                        vtxY = obj->unk44[objModel->unk14[index]].y;
                        vtxZ = obj->unk44[objModel->unk14[index]].z;
                        loopObj->segment.trans.x_position += vtxX;
                        loopObj->segment.trans.y_position += vtxY;
                        loopObj->segment.trans.z_position += vtxZ;
                        if (loopObj->segment.header->modelType == OBJECT_MODEL_TYPE_SPRITE_BILLBOARD) {
                            flags = (RENDER_Z_COMPARE | RENDER_FOG_ACTIVE | RENDER_Z_UPDATE);
                        } else {
                            flags = (RENDER_Z_COMPARE | RENDER_FOG_ACTIVE | RENDER_Z_UPDATE | RENDER_ANTI_ALIASING);
                        }
                        if (alpha < 255) {
                            flags |= RENDER_SEMI_TRANSPARENT;
                        }
                        cicFailed = FALSE;
                        // Anti-Piracy check
                        if (osCicId != CIC_ID) {
                            cicFailed = TRUE;
                        }
                        if (!cicFailed) {
                            var_v0_2 = (loopObj->segment.trans.flags & OBJ_FLAGS_UNK_0080 && obj60_unk0 == 3);
                            if (racerObj != NULL && racerObj->transparency < 255) {
                                var_v0_2 = FALSE;
                            }
                            if (var_v0_2) {
                                func_80012C98(&gObjectCurrDisplayList);
                                gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 255, 0);
                                gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, intensity, intensity, intensity, alpha);
                            }
                            loopObj->properties.common.unk0 = render_sprite_billboard(
                                &gObjectCurrDisplayList, &gObjectCurrMatrix, &gObjectCurrVertexList, loopObj,
                                (unk80068514_arg4 *) something, flags);
                            if (var_v0_2) {
                                gDkrInsertMatrix(gObjectCurrDisplayList++, 0, 0);
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
                    something = loopObj->unk68[loopObj->segment.object.modelIndex];
                    vtxX = obj->unk44[objModel->unk14[index]].x;
                    vtxY = obj->unk44[objModel->unk14[index]].y;
                    vtxZ = obj->unk44[objModel->unk14[index]].z;
                    loopObj->segment.trans.x_position += (vtxX - loopObj->segment.trans.x_position) * 0.25;
                    loopObj->segment.trans.y_position += (vtxY - loopObj->segment.trans.y_position) * 0.25;
                    loopObj->segment.trans.z_position += (vtxZ - loopObj->segment.trans.z_position) * 0.25;
                    if (loopObj->segment.header->modelType == OBJECT_MODEL_TYPE_SPRITE_BILLBOARD) {
                        render_sprite_billboard(&gObjectCurrDisplayList, &gObjectCurrMatrix, &gObjectCurrVertexList,
                                                loopObj, (unk80068514_arg4 *) something, flags);
                    }
                }
            }
        }
        if (meshBatch != -1) {
            if (obj->segment.header->unk71) {
                gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, obj->shading->unk18, obj->shading->unk19,
                                obj->shading->unk1A, alpha);
                enable_primitive_colour();
            }
            render_mesh(objModel, obj, meshBatch, RENDER_SEMI_TRANSPARENT, spB0);
            if (obj->segment.header->unk71) {
                disable_primitive_colour();
            }
        }
        if (hasOpacity || obj->segment.header->unk71) {
            gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
        }
        if (hasEnvCol) {
            gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 255, 0);
        }
        apply_matrix_from_stack(&gObjectCurrDisplayList);
    }
}

void func_80012C30(void) {
    D_8011ADA4 = 0;
}

void func_80012C3C(Gfx **dlist) {
    s32 i;
    for (i = 0; i < D_8011ADA4; i++) {
        gSPDisplayList((*dlist)++, D_8011AD78[i]);
    }
}

void func_80012C98(Gfx **dlist) {
    if (D_8011ADA4 < 9) {
        gSPNoOp((*dlist)++); // Placeholder instruction?
        D_8011AD78[D_8011ADA4] = *dlist;
    }
}

void func_80012CE8(Gfx **dlist) {
    if (D_8011ADA4 < 9) {
        gSPEndDisplayList((*dlist)++);
        gSPBranchList(D_8011AD78[D_8011ADA4] - 1, *dlist);
        D_8011ADA4++;
    }
}

/**
 * Update the object stack trace, set the draw pointers, then begin rendering the object.
 * Official Name: objPrintObject
 */
void render_object(Gfx **dList, MatrixS **mtx, Vertex **verts, Object *obj) {
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
        if (sp_20->vehicleIDPrev < VEHICLE_TRICKY) {

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

// set_temp_model_transforms
#ifdef NON_EQUIVALENT
void func_80012F94(Object *obj) {
    u8 *bossAsset;
    ObjectModel *temp_a1_3;
    Object_Racer *objRacer;
    Object_68 **var_v0;
    Object_68 *new_var;
    f32 ret1;
    f32 var_f0_2;
    f32 ret2;
    u8 *var_a1;
    s32 temp_f6;
    s32 temp_v1;
    s32 bossVehicleId;
    s32 racerLightTimer;
    s32 batchNum;
    s32 var_v1;
    s32 firstNonEmptyUnk68ObjectIndex;
    s32 var_t0;
    s32 numberOfModels;

    ret1 = 1.0f;
    ret2 = 1.0f;
    if (!(obj->segment.trans.flags & OBJ_FLAGS_DEACTIVATED)) {
        if (obj->segment.header->behaviorId == BHV_RACER) {
            objRacer = (Object_Racer *) obj->unk64;
            objRacer->unk201 = 30;
            if (objRacer->unk206 > 0) {
                ret2 = 1.0f - (objRacer->unk206 * 0.05f);
                if (ret2 < 0.2f) {
                    ret2 = 0.2f;
                }
            }
            if (objRacer->playerIndex != PLAYER_COMPUTER && objRacer->raceFinished) {
                var_t0 = 0;
                batchNum = 0;
            } else {
                if (obj->behaviorId == BHV_TIMETRIAL_GHOST) { // Ghost Object?
                    var_t0 = 1;
                    batchNum = 0;
                } else {
                    // Loads vehicles between VEHICLE_TRICKY and VEHICLE_SMOKEY. So all boss vehicles except wizpig.
                    var_t0 = objRacer->vehicleID + VEHICLE_TRICKY;
                    if (objRacer->vehicleID >= NUMBER_OF_PLAYER_VEHICLES) {
                        var_t0 = VEHICLE_TRICKY;
                    }
                    batchNum = 0;
                    bossAsset = (u8 *) get_misc_asset(var_t0); // 40 bytes of data u8[8][5]?
                    bossAsset = &bossAsset[(get_viewport_count() * 10)];
                    var_a1 = bossAsset;
                    if (get_current_viewport() != objRacer->playerIndex) {
                        var_a1 += 5;
                    }
                    var_f0_2 = obj->segment.object.distanceToCamera;
                    temp_v1 = (s32) var_f0_2 >> 3;
                    if (obj->segment.object.distanceToCamera < 0.0f) {
                        var_f0_2 = 0.0f;
                    } else if (var_f0_2 > 3500.0f) {
                        var_f0_2 = 3500.0f;
                    }
                    obj->segment.trans.scale *= (var_f0_2 / 2700.0f) + 1.0f;
                    temp_f6 = (s32) ((f32) temp_v1 * *((f32 *) get_misc_asset(ASSET_MISC_4)[objRacer->characterId]));
                    // ASSET_MISC_4 is just 10 floats of 1.0f. One for each playable character.
                    if (temp_f6 < -50) {
                        var_t0 = 5;
                    } else {
                        racerLightTimer = MIN(temp_f6 >> 1, 0);
                        var_v1 = racerLightTimer;
                        if (var_v1 < var_a1[0]) {
                            var_t0 = 0;
                        } else if (var_v1 < var_a1[1]) {
                            var_t0 = 1;
                        } else if (var_v1 < var_a1[2]) {
                            var_t0 = 2;
                        } else if (var_v1 < var_a1[3]) {
                            var_t0 = 3;
                        } else if (var_v1 < var_a1[4]) {
                            var_t0 = 4;
                        } else {
                            var_t0 = 5;
                        }
                    }
                }
            }

            firstNonEmptyUnk68ObjectIndex = 0;
            var_v0 = &obj->unk68[firstNonEmptyUnk68ObjectIndex];

            while (*var_v0 == NULL) {
                firstNonEmptyUnk68ObjectIndex++;
                var_v0++;
            }

            numberOfModels = obj->segment.header->numberOfModelIds - 1;
            var_v0 = &obj->unk68[numberOfModels];

            while (*var_v0 == NULL) {
                numberOfModels--;
                var_v0--;
            }

            if (var_t0 < firstNonEmptyUnk68ObjectIndex) {
                var_t0 = firstNonEmptyUnk68ObjectIndex;
            }
            if (numberOfModels < var_t0) {
                var_t0 = numberOfModels;
            }
            obj->segment.object.modelIndex = var_t0;
            if ((obj->shading != NULL) && (obj->shading->unk0 < 0.6f)) {
                objRacer->lightFlags |= RACER_LIGHT_NIGHT;
            } else {
                objRacer->lightFlags &= ~RACER_LIGHT_NIGHT;
            }
            racerLightTimer = objRacer->lightFlags & RACER_LIGHT_TIMER;
            new_var = obj->unk68[obj->segment.object.modelIndex];
            temp_a1_3 = new_var->objModel;
            if (racerLightTimer != 0) {
                racerLightTimer--;
                if (objRacer->lightFlags & RACER_LIGHT_BRAKE) {
                    racerLightTimer += 1;
                    objRacer->lightFlags = (objRacer->lightFlags & ~RACER_LIGHT_UNK10) | RACER_LIGHT_UNK20;
                } else if (objRacer->lightFlags & RACER_LIGHT_NIGHT) {
                    racerLightTimer += 3;
                    objRacer->lightFlags = (objRacer->lightFlags & ~RACER_LIGHT_UNK20) | RACER_LIGHT_UNK10;
                } else if (objRacer->lightFlags & RACER_LIGHT_UNK20) {
                    racerLightTimer += 1;
                } else {
                    racerLightTimer += 3;
                }
            }
            racerLightTimer *= 4;
            for (batchNum = 0; batchNum < temp_a1_3->numberOfBatches; batchNum++) {
                if ((temp_a1_3->batches[batchNum].flags & 0x810000) == 0x10000) {
                    temp_a1_3->batches[batchNum].unk7 = racerLightTimer;
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
    D_8011AD28 = ret1;
    gCurrentLightIntensity = ret2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_80012F94.s")
#endif

/**
 * Determine which model type the object is using, then call the related function to render it.
 * Beforehand, call a function to apply a temporary transformation, mostly for racers.
 * Afterwards, undo that.
 */
void render_object_parts(Object *obj) {
    func_80012F94(obj);
    if (obj->segment.trans.flags & OBJ_FLAGS_DEACTIVATED) {
        render_particle((Particle *) obj, &gObjectCurrDisplayList, &gObjectCurrMatrix, &gObjectCurrVertexList, 0x8000);
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
    if (!(obj->segment.trans.flags & OBJ_FLAGS_DEACTIVATED) && obj->segment.header->behaviorId == BHV_RACER) {
        obj->segment.trans.x_position -= obj->unk64->racer.carBobX;
        obj->segment.trans.y_position -= obj->unk64->racer.carBobY;
        obj->segment.trans.z_position -= obj->unk64->racer.carBobZ;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_800135B8.s")

/**
 * Render the bubble trap weapon.
 */
void render_bubble_trap(ObjectTransform *trans, Object_68 *gfxData, Object *obj, s32 flags) {
    f32 x;
    f32 y;
    f32 z;
    ObjectSegment *cameraSegment;
    f32 dist;

    f32_vec3_apply_object_rotation(trans, &obj->segment.trans.x_position);
    obj->segment.trans.x_position += trans->x_position;
    obj->segment.trans.y_position += trans->y_position;
    obj->segment.trans.z_position += trans->z_position;
    cameraSegment = get_active_camera_segment();
    x = cameraSegment->trans.x_position - obj->segment.trans.x_position;
    y = cameraSegment->trans.y_position - obj->segment.trans.y_position;
    z = cameraSegment->trans.z_position - obj->segment.trans.z_position;
    dist = sqrtf((x * x) + (y * y) + (z * z));
    if (dist > 0.0) {
        dist = obj->segment.unk1A / dist;
        x *= dist;
        y *= dist;
        z *= dist;
    }
    obj->segment.trans.x_position += x;
    obj->segment.trans.y_position += y;
    obj->segment.trans.z_position += z;
    render_sprite_billboard(&gObjectCurrDisplayList, &gObjectCurrMatrix, &gObjectCurrVertexList, obj,
                            (unk80068514_arg4 *) gfxData, flags);
}

/**
 * Get the racer object data, and fetch set visual shield properties based on that racer.
 * Afterwards, render the graphics with opacity scaling with the fadetimer.
 */
void render_racer_shield(Gfx **dList, MatrixS **mtx, Vertex **vtxList, Object *obj) {
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
        if (racerIndex > 10) {
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
        gShieldEffectObject->segment.trans.y_position += shield->y_offset * sins_f(D_8011B010[racerIndex] * 0x200);
        shear = (coss_f(D_8011B010[racerIndex] * 0x400) * 0.05f) + 0.95f;
        gShieldEffectObject->segment.trans.scale = shield->scale * shear;
        shear = shear * shield->turnSpeed;
        gShieldEffectObject->segment.trans.rotation.y_rotation = D_8011B010[racerIndex] * 0x800;
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
        gShieldEffectObject->unk44 = (Vertex *) gfxData->unk4[gfxData->animationTaskNum];
        gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 255, 0);
        if (racer->shieldTimer < 64) {
            gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, racer->shieldTimer * 4);
        } else {
            gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
        }
        apply_object_shear_matrix(&gObjectCurrDisplayList, &gObjectCurrMatrix, gShieldEffectObject, obj, shear);
        render_mesh(mdl, gShieldEffectObject, 0, RENDER_SEMI_TRANSPARENT, 0);
        gDkrInsertMatrix(gObjectCurrDisplayList++, 0, G_MTX_DKR_INDEX_0);
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
void render_racer_magnet(Gfx **dList, MatrixS **mtx, Vertex **vtxList, Object *obj) {
    Object_Racer *racer;
    Object_68 *gfxData;
    ObjectModel *mdl;
    f32 *magnet;
    s32 vehicleID;
    s32 var_t0;
    s32 opacity;
    f32 shear;
    UNUSED s32 pad;

    racer = &obj->unk64->racer;
    var_t0 = racer->racerIndex;
    if (D_8011B078[var_t0].a != 0) {
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
            var_t0 = racer->racerIndex;
            if (var_t0 > 10) {
                var_t0 = 0;
            }
            gMagnetEffectObject->segment.trans.x_position = magnet[0];
            gMagnetEffectObject->segment.trans.y_position = magnet[1];
            gMagnetEffectObject->segment.trans.z_position = magnet[2];
            magnet += 3;
            shear = (coss_f((D_8011B078[var_t0].g * 0x400)) * 0.02f) + 0.98f;
            gMagnetEffectObject->segment.trans.scale = magnet[0] * shear;
            magnet += 1;
            shear = magnet[0] * shear;
            gMagnetEffectObject->segment.trans.rotation.y_rotation = D_8011B078[var_t0].b * 0x1000;
            gMagnetEffectObject->segment.trans.rotation.x_rotation = 0;
            gMagnetEffectObject->segment.trans.rotation.z_rotation = 0;
            gfxData = *gMagnetEffectObject->unk68;
            mdl = gfxData->objModel;
            gMagnetEffectObject->unk44 = (Vertex *) gfxData->unk4[gfxData->animationTaskNum];
            opacity = ((D_8011B078[var_t0].g * 8) & 0x7F) + 0x80;
            func_8007F594(&gObjectCurrDisplayList, 2, COLOUR_RGBA32(255, 255, 255, opacity),
                          gMagnetColours[racer->magnetModelID]);
            apply_object_shear_matrix(&gObjectCurrDisplayList, &gObjectCurrMatrix, gMagnetEffectObject, obj, shear);
            gObjectTexAnim = TRUE;
            render_mesh(mdl, gMagnetEffectObject, 0, RENDER_SEMI_TRANSPARENT, 0);
            gObjectTexAnim = FALSE;
            gDkrInsertMatrix(gObjectCurrDisplayList++, 0, G_MTX_DKR_INDEX_0);
            gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            reset_render_settings(&gObjectCurrDisplayList);
            *dList = gObjectCurrDisplayList;
            *mtx = gObjectCurrMatrix;
            *vtxList = gObjectCurrVertexList;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_80014090.s")

void func_800142B8(void) {
    s32 i = gObjectListStart;
    s32 j;
    Object *currObj;
    Object_68 *curr_68;

    for (; i < gObjectCount; i++) {
        currObj = gObjPtrList[i];
        if (!(currObj->segment.trans.flags & OBJ_FLAGS_DEACTIVATED) &&
            currObj->segment.header->modelType == OBJECT_MODEL_TYPE_3D_MODEL) {
            for (j = 0; j < currObj->segment.header->numberOfModelIds; j++) {
                curr_68 = currObj->unk68[j];
                if (curr_68 != NULL && curr_68->unk20 > 0) {
                    curr_68->unk20 &= 0x03;
                    curr_68->unk20--;
                }
            }
        }
    }
}

/**
 * Renders every triangle batch in an objects mesh.
 */
s32 render_mesh(ObjectModel *objModel, Object *obj, s32 startIndex, s32 flags, s32 someBool) {
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
    Gfx *dlist;

    dlist = gObjectCurrDisplayList;
    i = startIndex;
    endLoop = FALSE;
    while (i < objModel->numberOfBatches && !endLoop) {
        if (!(objModel->batches[i].flags & BATCH_FLAGS_UNK00000004) || flags & RENDER_SEMI_TRANSPARENT) {
            // Hidden/Invisible geometry
            textureIndex = objModel->batches[i].flags & BATCH_FLAGS_HIDDEN;
            // Probably a fakematch to use textureIndex here, but it works.
            if (!textureIndex) {
                vertOffset = objModel->batches[i].verticesOffset;
                triOffset = objModel->batches[i].facesOffset;
                numVertices = objModel->batches[i + 1].verticesOffset - vertOffset;
                offsetStartVertex = (someBool) ? objModel->batches[i].unk1 : numVertices;
                numTris = objModel->batches[i + 1].facesOffset - triOffset;
                tris = &objModel->triangles[triOffset];
                vtx = &obj->unk44[vertOffset];
                textureIndex = objModel->batches[i].textureIndex;
                // textureIndex of 0xFF is no texture
                if (textureIndex == 0xFF) {
                    texOffset = 0;
                    texToSet = NULL;
                    texEnabled = FALSE;
                } else {
                    texOffset = objModel->batches[i].unk7 << 14;
                    texEnabled = TRUE;
                    texToSet = objModel->textures[textureIndex].texture;
                }
                texToSetFlags = objModel->batches[i].flags | BATCH_FLAGS_UNK00000008;
                if (flags & RENDER_SEMI_TRANSPARENT &&
                    !(objModel->batches[i].flags & (flags & ~RENDER_SEMI_TRANSPARENT))) {
                    texToSetFlags |= RENDER_SEMI_TRANSPARENT;
                }
                if (gObjectTexAnim == FALSE) {
                    load_and_set_texture(&dlist, texToSet, texToSetFlags, texOffset);
                } else {
                    texToSet = set_animated_texture_header(texToSet, texOffset);
                    gDkrDmaDisplayList(gObjectCurrDisplayList++, OS_K0_TO_PHYSICAL(texToSet->cmd),
                                       texToSet->numberOfCommands);
                }
                if (offsetStartVertex == numVertices) {
                    gSPVertexDKR(dlist++, OS_K0_TO_PHYSICAL(vtx), numVertices, 0);
                } else {
                    if (offsetStartVertex > 0) {
                        gSPVertexDKR(dlist++, OS_K0_TO_PHYSICAL(vtx), offsetStartVertex, 0);
                        gDkrInsertMatrix(dlist++, 0, G_MTX_DKR_INDEX_2);
                        gSPVertexDKR(dlist++, OS_K0_TO_PHYSICAL(&vtx[offsetStartVertex]),
                                     (numVertices - offsetStartVertex), 1);
                    } else {
                        gDkrInsertMatrix(dlist++, 0, G_MTX_DKR_INDEX_2);
                        gSPVertexDKR(dlist++, OS_K0_TO_PHYSICAL(vtx), numVertices, 0);
                    }
                    gDkrInsertMatrix(dlist++, 0, G_MTX_DKR_INDEX_1);
                }
                gSPPolygon(dlist++, OS_K0_TO_PHYSICAL(tris), numTris, texEnabled);
            }
            i++;
        } else {
            endLoop = TRUE;
        }
    }
    if (i >= objModel->numberOfBatches) {
        i = -1;
    }
    gObjectCurrDisplayList = dlist;
    return i;
}

#ifdef NON_EQUIVALENT
s32 func_80014814(s32 *retObjCount) {
    s32 i;
    s32 maxObjCount;
    s32 curObjCount;

    *retObjCount = gObjectCount;
    if (D_8011AE7C) {
        return D_8011AE7C;
    }
    curObjCount = gObjectListStart;
    maxObjCount = gObjectCount - 1;
    while (maxObjCount >= curObjCount) {
        for (i = 0; maxObjCount >= curObjCount && i == 0; i++) {
            if (!(gObjPtrList[curObjCount]->segment.trans.flags & OBJ_FLAGS_DEACTIVATED)) {
                if (gObjPtrList[curObjCount]->segment.header->flags & 1) {
                    curObjCount++;
                }
                i = -1;
            } else {
                curObjCount++;
            }
        }
        for (i = 0; maxObjCount >= curObjCount && i == 0; i++) {
            if (gObjPtrList[maxObjCount]->segment.trans.flags & OBJ_FLAGS_DEACTIVATED) {
                i = -1;
            } else if (!(gObjPtrList[maxObjCount]->segment.header->flags & 1)) {
                maxObjCount--;
            } else {
                i = -1;
            }
        }
        if (curObjCount > maxObjCount) {
            gObjPtrList[curObjCount] = gObjPtrList[maxObjCount];
            gObjPtrList[maxObjCount] = gObjPtrList[curObjCount];
            curObjCount++;
            maxObjCount--;
        }
    }
    D_8011AE7C = curObjCount;
    return curObjCount;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_80014814.s")
#endif

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
                                             gObjPtrList[arg0]->segment.particle.unk34) < arg2)) {
                    arg0++;
                }
                while ((arg1 >= var_a0) && (arg2 <= (gObjPtrList[arg1]->segment.trans.x_position -
                                                     gObjPtrList[arg1]->segment.particle.unk34))) {
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
                                             gObjPtrList[arg0]->segment.particle.unk34) < arg2)) {
                    arg0++;
                }
                while ((arg1 >= var_a0) && (arg2 <= (gObjPtrList[arg1]->segment.trans.y_position -
                                                     gObjPtrList[arg1]->segment.particle.unk34))) {
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
                                             gObjPtrList[arg0]->segment.particle.unk34) < arg2)) {
                    arg0++;
                }
                while ((arg1 >= var_a0) && (arg2 <= (gObjPtrList[arg1]->segment.trans.z_position -
                                                     gObjPtrList[arg1]->segment.particle.unk34))) {
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
                                             gObjPtrList[arg0]->segment.particle.unk34) < arg2)) {
                    arg0++;
                }
                while ((arg1 >= var_a0) && (arg2 <= (gObjPtrList[arg1]->segment.trans.x_position +
                                                     gObjPtrList[arg1]->segment.particle.unk34))) {
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
                                             gObjPtrList[arg0]->segment.particle.unk34) < arg2)) {
                    arg0++;
                }
                while ((arg1 >= var_a0) && (arg2 <= (gObjPtrList[arg1]->segment.trans.y_position +
                                                     gObjPtrList[arg1]->segment.particle.unk34))) {
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
                                             gObjPtrList[arg0]->segment.particle.unk34) < arg2)) {
                    arg0++;
                }
                while ((arg1 >= var_a0) && (arg2 <= (gObjPtrList[arg1]->segment.trans.z_position +
                                                     gObjPtrList[arg1]->segment.particle.unk34))) {
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
            if (obj->segment.trans.flags & OBJ_FLAGS_DEACTIVATED) {
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
        if (!(obj->segment.trans.flags & OBJ_FLAGS_DEACTIVATED)) {
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

#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_800159C8.s")

void func_80016500(Object *obj, Object_Racer *racer) {
    s32 sp3C;
    s32 angle;
    UNUSED s32 pad;
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
        angle = (startVelocity - racer->velocity) * 14.0f;
        if (angle < 0) {
            angle = -angle;
        }
        angle += 35;
        if (angle >= 128) {
            angle = 127;
        }
        if (racer->unk1F6 == 0) {
            sound_play(SOUND_CRASH_CHARACTER, &racer->unk220);
            sound_volume_set_relative(SOUND_CRASH_CHARACTER, (s32 *) racer->unk220, angle);
        }
        if (racer->unk1F6 == 0 && angle >= 56) {
            if (!racer->raceFinished) {
                rumble_set(racer->playerIndex, RUMBLE_TYPE_18);
            }
            racer->unk1F3 |= 8;
        }
        if (angle >= 56) {
            play_random_character_voice(obj, SOUND_VOICE_CHARACTER_NEGATIVE, 8, 1);
        }
        sp3C = (startVelocity - racer->velocity);
        if (sp3C < 0) {
            sp3C = -sp3C;
        }
        if (sp3C >= 4) {
            sp3C = 3;
        }
        racer->unk1F6 = 30;
        set_active_camera(racer->playerIndex);
        get_active_camera_segment()->object.distanceToCamera = sp3C;
    }
}

void func_80016748(Object *obj0, Object *obj1) {
    ObjectModel *objModel;
    s32 i;
    f32 temp;

#ifdef AVOID_UB
    Matrix obj1TransformMtx;
#else
    // THIS IS A HACK! Supposed to be a Matrix, but the stack ended up being too big.
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

    if (obj1->unk44 != NULL) {
        obj68 = (*obj1->unk68);
        objModel = obj68->objModel;
        xDiff = obj0->segment.trans.x_position - obj1->segment.trans.x_position;
        yDiff = obj0->segment.trans.y_position - obj1->segment.trans.y_position;
        zDiff = obj0->segment.trans.z_position - obj1->segment.trans.z_position;
        if (!((objModel->unk3C + 50.0) < sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff)))) {
            obj0Interact = obj0->interactObj;
            obj1Interact = obj1->interactObj;
            object_transform_to_matrix((float(*)[4]) obj1TransformMtx, &obj1->segment.trans);
            for (i = 0; i < objModel->unk20; i += 2) {
                xDiff = obj1->unk44[objModel->unk1C[i]].x;
                yDiff = obj1->unk44[objModel->unk1C[i]].y;
                zDiff = obj1->unk44[objModel->unk1C[i]].z;
                guMtxXFMF((float(*)[4]) obj1TransformMtx, xDiff, yDiff, zDiff, &xDiff, &yDiff, &zDiff);
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
        if (!(curObj->segment.trans.flags & OBJ_FLAGS_DEACTIVATED) && curObj->behaviorId == BHV_ANIMATED_OBJECT_3) {
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
    Matrix *sp6C;
    Matrix sp2C;
    Object_5C *obj5C;

    obj5C = obj->unk5C;
    obj5C->unk104 = (obj5C->unk104 + 1) & 1;
    sp6C = (Matrix *) &obj5C->_matrices[obj5C->unk104 << 1];
    sp78.rotation.y_rotation = -obj->segment.trans.rotation.y_rotation;
    sp78.rotation.x_rotation = -obj->segment.trans.rotation.x_rotation;
    sp78.rotation.z_rotation = -obj->segment.trans.rotation.z_rotation;
    sp78.scale = 1.0f;
    sp78.x_position = -obj->segment.trans.x_position;
    sp78.y_position = -obj->segment.trans.y_position;
    sp78.z_position = -obj->segment.trans.z_position;
    object_transform_to_matrix_2((float(*)[4]) sp6C, (ObjectTransform *) &sp78);
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
    f32_matrix_mult(sp6C, &sp2C, sp6C);
    sp78.rotation.y_rotation = obj->segment.trans.rotation.y_rotation;
    sp78.rotation.x_rotation = obj->segment.trans.rotation.x_rotation;
    sp78.rotation.z_rotation = obj->segment.trans.rotation.z_rotation;
    sp78.scale = 1.0 / inverseScale;
    sp78.x_position = obj->segment.trans.x_position;
    sp78.y_position = obj->segment.trans.y_position;
    sp78.z_position = obj->segment.trans.z_position;
    object_transform_to_matrix(obj5C->_matrices[(obj5C->unk104 + 2) << 1], (ObjectTransform *) &sp78);
    obj5C->unk100 = NULL;
}

#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_80017248.s")

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
}

#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_80017A18.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_80017E98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_800185E4.s")

/**
 * Search and return Taj's overworld object.
 * Used for drawing his minimap position.
 */
Object *find_taj_object(void) {
    s32 i;
    Object *current_obj;
    for (i = gObjectListStart; i < gObjectCount; i++) {
        current_obj = gObjPtrList[i];
        if (!(current_obj->segment.trans.flags & OBJ_FLAGS_DEACTIVATED) &&
            (current_obj->behaviorId == BHV_PARK_WARDEN)) {
            return current_obj;
        }
    }
    return NULL;
}

#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_80018CE0.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_80019808.s")

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
                sound_stop(racer->magnetSoundMask);
            }
            if (racer->shieldSoundMask != NULL) {
                func_800096F8(racer->shieldSoundMask);
            }
        }
        prevPort0Racer = (*gRacers)[0];
        (*gRacers)[0] = (*gRacers)[sp30];
        (*gRacers)[sp30] = prevPort0Racer;
        racer_sound_free((*gRacers)[0]);
        hud_audio_init();
        reset_rocket_sound_timer();
        sound_stop_all();
        if (is_in_two_player_adventure()) {
            set_scene_viewport_num(0);
            set_active_viewports_and_max(0);
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
        i = get_buttons_pressed_from_player(PLAYER_ONE) & A_BUTTON;
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
                    play_time_trial_end_message(&bestRacer->playerIndex);
                }
            } else {
                play_time_trial_end_message(&bestRacer->playerIndex);
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
    play_time_trial_end_message(playerId);
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
UNUSED void debug_render_checkpoints(Gfx **dlist, MatrixS **mtx, Vertex **vtx) {
    s32 i;

    load_and_set_texture_no_offset(dlist, NULL, RENDER_Z_COMPARE);
    if (gNumberOfCheckpoints > 3) {
        for (i = 0; i < gNumberOfCheckpoints; i++) {
            // Ground path
            debug_render_checkpoint_node(i, 0, dlist, mtx, vtx);
        }
        for (i = 0; i < gNumberOfCheckpoints; i++) {
            // Air path
            debug_render_checkpoint_node(i, 1, dlist, mtx, vtx);
        }
    }
}

/**
 * Would've rendered an individual checkpoint node. On https://noclip.website, with dev objects enabled, you can see a
 * visual representation of what these checkpoints would've looked like ingame.
 */
UNUSED void debug_render_checkpoint_node(UNUSED s32 checkpointID, UNUSED s32 pathID, UNUSED Gfx **dList,
                                         UNUSED MatrixS **mtx, UNUSED Vertex **vtx) {
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
        if (!(objPtr->segment.trans.flags & OBJ_FLAGS_DEACTIVATED)) {
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
        if (!(obj->segment.trans.flags & OBJ_FLAGS_DEACTIVATED) && obj->behaviorId == BHV_AINODE) {
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
        segment = (ObjectSegment *) (*gAINodes)[numSteps];
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

#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_8001C6C4.s")

#ifdef NON_MATCHING
// ainode_find_next
s32 func_8001CC48(s32 nodeCurrent, s32 arg1, s32 direction) {
    LevelObjectEntry_AiNode *entry;
    Object *someObj;
    Object_AiNode *someObj64;
    s32 someCount;
    s32 i;
    s32 someIndex;
    s32 test;

    if ((nodeCurrent < -1) || (nodeCurrent >= AINODE_COUNT)) {
        return NODE_NONE;
    }
    someObj = (*gAINodes)[nodeCurrent];
    if (someObj == NULL) {
        return NODE_NONE;
    }
    entry = &someObj->segment.level_entry->aiNode;
    someObj64 = &someObj->unk64->ai_node;
    test = direction & 3;

    // Swapping these messes up the registers.
    someCount = 0;
    someIndex = (someObj64->directions[test] + 1) & 3;

    for (i = 0; i < 4; i++) {
        if (entry->adjacent[someIndex] != NODE_NONE) {
            if (entry->adjacent[someIndex] != arg1) {
                someObj64->directions[test] = someIndex;
                i = 4;
                someCount++;
            }
        }
        someIndex = (someIndex + 1) & 3;
    }
    if (someCount == 0) {
        return NODE_NONE;
    }
    return entry->adjacent[someObj64->directions[test]];
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_8001CC48.s")
#endif

#ifdef NON_MATCHING
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
                        sp54[sp36C] = sp54[sp36C - 1];
                        sp54[sp36C - 1] = temp;
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
                if ((arg1 & AINODE_COUNT) == spD4[var_t1]) {
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
#else
#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_8001CD28.s")
#endif

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
void set_world_shading(f32 brightness, f32 ambient, s16 angleX, s16 angleY, s16 angleZ) {
    set_shading_properties((ShadeProperties *) &gWorldShading, brightness, ambient, angleX, angleY, angleZ);
}

/**
 * Add values onto the existing properties of an objects shading.
 * Resets the shading based off the new values.
 */
UNUSED void add_shading_properties(Object *obj, f32 brightnessChange, f32 ambientChange, s16 angleX, s16 angleY,
                                   s16 angleZ) {
    if (obj->shading != NULL) {
        obj->shading->brightness += brightnessChange;
        if (obj->shading->brightness < 0.0f) {
            obj->shading->brightness = 0.0f;
        } else if (obj->shading->brightness > 1.0f) {
            obj->shading->brightness = 1.0f;
        }
        obj->shading->ambient += ambientChange;
        if (obj->shading->ambient < 0.0f) {
            obj->shading->ambient = 0.0f;
        }
        if (obj->shading->ambient >= 2.0f) {
            obj->shading->ambient = 1.99f;
        }
        set_shading_properties(obj->shading, obj->shading->brightness, obj->shading->ambient,
                               (obj->shading->unk22 + angleX), (obj->shading->unk24 + angleY),
                               (obj->shading->unk26 + angleZ));
        if (obj->segment.header->unk3D != 0) {
            obj->shading->unk4 = obj->segment.header->unk3A;
            obj->shading->unk5 = obj->segment.header->unk3B;
            obj->shading->unk6 = obj->segment.header->unk3C;
            obj->shading->unk7 = obj->segment.header->unk3D;
            obj->shading->unk8 = -(obj->shading->unk1C >> 1);
            obj->shading->unkA = -(obj->shading->unk1E >> 1);
            obj->shading->unkC = -(obj->shading->unk20 >> 1);
        }
    }
}

void set_shading_properties(ShadeProperties *arg0, f32 brightness, f32 ambient, s16 angleX, s16 angleY, s16 angleZ) {
    Vec3s angle;
    Vec3f velocityPos;

    arg0->unk22 = angleX;
    arg0->brightness = brightness;
    arg0->ambient = ambient;
    arg0->unk0 = 1.0f;
    arg0->unk24 = angleY;
    arg0->unk26 = angleZ;
    angle.z = angleX;
    angle.x = angleZ;
    angle.y = angleY;
    velocityPos.z = -16384.0f;
    velocityPos.x = 0.0f;
    velocityPos.y = 0.0f;
    f32_vec3_apply_object_rotation((ObjectTransform *) &angle, (f32 *) &velocityPos);
    arg0->unk1C = -velocityPos.x;
    arg0->unk1E = -velocityPos.y;
    arg0->unk20 = -velocityPos.z;
    arg0->unk18 = 0;
    arg0->unk19 = 0;
    arg0->unk1A = 0;
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
    gEnvmapPos.x = x;
    gEnvmapPos.y = y;
    gEnvmapPos.z = z;
}

/**
 * If the triangle batch allows for it, compute envmap normals for the mesh.
 * Some objects will prefer some extra additions on top before calculating, like light intensity.
 */
void calc_dyn_light_and_env_map_for_object(ObjectModel *model, Object *object, s32 arg2, f32 intensity) {
    s16 environmentMappingEnabled;
    s32 dynamicLightingEnabled;
    s16 i;

    dynamicLightingEnabled = 0;
    environmentMappingEnabled = 0;

    for (i = 0; i < model->numberOfBatches; i++) {
        if (model->batches[i].unk6 != 0xFF) {
            dynamicLightingEnabled = -1; // This is a bit weird, but I guess it works.
        }
        if (model->batches[i].flags & BATCH_FLAGS_ENVMAP) {
            environmentMappingEnabled = -1;
        }
    }

    if (dynamicLightingEnabled) {
        // Calculates dynamic lighting for the object
        if (object->segment.header->unk71) {
            // Dynamic lighting for some objects? (Intro diddy, Taj, T.T., Bosses)
            calc_dynamic_lighting_for_object_1(object, model, arg2, object, intensity, 1.0f);
        } else {
            // Dynamic lighting for other objects? (Racers, Rare logo, Wizpig face, etc.)
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

#pragma GLOBAL_ASM("asm/nonmatchings/objects/calc_dynamic_lighting_for_object_1.s")
#pragma GLOBAL_ASM("asm/nonmatchings/objects/calc_env_mapping_for_object.s")

/**
 * Find the racer object representing the player and directly set position and angle to new values.
 */
UNUSED void set_racer_position_and_angle(s16 player, s16 *x, s16 *y, s16 *z, s16 *angleZ, s16 *angleX, s16 *angleY) {
    Object *obj;
    Object_Racer *racer;
    s32 i;

    for (i = 0; i < gObjectCount; i++) {
        obj = gObjPtrList[i];
        if (!(obj->segment.trans.flags & OBJ_FLAGS_DEACTIVATED)) {
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

        if (current_obj != NULL && !(current_obj->segment.trans.flags & OBJ_FLAGS_DEACTIVATED) &&
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
        D_8011AE7E = 1;
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
        if (obj != NULL && !(obj->segment.trans.flags & OBJ_FLAGS_DEACTIVATED) && obj->behaviorId == BHV_ANIMATION) {
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
    D_8011AE7C = 0;
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
    if (D_8011AE01 != 0) {
        D_8011AE01 = 0;
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

#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_8001E93C.s")

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
        sound_stop(anim->unk18);
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

    obj->unk64 = (Object_64 *) spawn_object((LevelObjectEntryCommon *) &newObjEntry, 1);
    newObj = (Object *) obj->unk64;
    // (newObj->behaviorId == BHV_DINO_WHALE) is Dinosaur1, Dinosaur2, Dinosaur3, Whale, and Dinoisle
    if (obj->unk64 != NULL && newObj->behaviorId == BHV_DINO_WHALE && gTimeTrialEnabled) {
        free_object(newObj);
        obj->unk64 = NULL;
        newObj = NULL;
    }
    camera = (Object_AnimCamera *) newObj;
    if (camera != NULL) {
        camera->unk3C = 0;
        obj_init_animcamera(obj, newObj);
        if (newObj->segment.header->behaviorId == BHV_CAMERA_ANIMATION) {
            camera = &newObj->unk64->anim_camera;
            camera->unk44 = D_8011AD3E;
            viewportCount = get_viewport_count();
            if (is_two_player_adventure_race()) {
                viewportCount = VIEWPORTS_COUNT_2_PLAYERS;
            }
            for (i = 0; i < viewportCount;) {
                newObj = spawn_object(&newObjEntry, 1);
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

#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_8001F460.s")

s32 func_800210CC(s8 arg0) {
    if (arg0 >= D_8011AD3D) {
        D_8011AD3D = arg0;
        return TRUE;
    }
    return FALSE;
}

void func_80021104(Object *obj, Object_Animation *animObj, LevelObjectEntry_Animation *entry) {
    ObjectSegment *seg;
    ObjectTransform *animObjTrans;

    animObjTrans = (ObjectTransform *) animObj->unk1C;
    if (obj->behaviorId == BHV_CAMERA_ANIMATION) {
        animObj->unk44 = D_8011AD3E;
        D_8011AD3E++;
    }
    if (entry->unk22 == 18) {
        set_active_camera(animObj->cameraID);
        seg = get_active_camera_segment_no_cutscenes();
        animObjTrans->x_position = seg->trans.x_position;
        animObjTrans->y_position = seg->trans.y_position;
        animObjTrans->z_position = seg->trans.z_position;
        animObjTrans->rotation.y_rotation = (0x8000 - seg->trans.rotation.y_rotation);
        animObjTrans->rotation.x_rotation = -seg->trans.rotation.x_rotation;
        animObjTrans->rotation.z_rotation = seg->trans.rotation.z_rotation;
    }
    if ((entry->unk22 >= 10) && (entry->unk22 < 18)) {
        seg = &(*gRacers)[entry->unk22 - 10]->segment;
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

#pragma GLOBAL_ASM("asm/nonmatchings/objects/func_80021600.s")

f32 catmull_rom_interpolation(f32 *data, s32 index, f32 x) {
    f32 ret;
    f32 temp3, temp2, temp;

    temp = (-0.5 * data[index]) + (1.5 * data[index + 1]) + (-1.5 * data[index + 2]) + (0.5 * data[index + 3]);
    temp2 = (1.0 * data[index]) + (-2.5 * data[index + 1]) + (2.0 * data[index + 2]) + (-0.5 * data[index + 3]);
    temp3 = (data[index + 2] * 0.5) + (0.0 * data[index + 1]) + (-0.5 * data[index]) + (0.0 * data[index + 3]);

    ret = (1.0 * data[index + 1]);
    ret = (((((temp * x) + temp2) * x) + temp3) * x) + ret;

    return ret;
}

/**
 * Interpolates x along a spline and returns the resultant progress along the spline.
 */
f32 cubic_spline_interpolation(f32 *data, s32 index, f32 x, f32 *derivative) {
    f32 ret;
    f32 temp3, temp2, temp;

    temp = (-0.5 * data[index]) + (1.5 * data[index + 1]) + (-1.5 * data[index + 2]) + (0.5 * data[index + 3]);
    temp2 = (1.0 * data[index]) + (-2.5 * data[index + 1]) + (2.0 * data[index + 2]) + (-0.5 * data[index + 3]);
    temp3 = (data[index + 2] * 0.5) + (0.0 * data[index + 1]) + (-0.5 * data[index]) + (0.0 * data[index + 3]);

    ret = (1.0 * data[index + 1]);
    *derivative = (((temp * 3 * x) + (2 * temp2)) * x) + temp3;
    ret = (((((temp * x) + temp2) * x) + temp3) * x) + ret;

    return ret;
}

f32 func_8002277C(f32 *data, s32 index, f32 x) {
    f32 derivative;
    f32 temp3, temp2, temp;

    temp = (-0.5 * data[index]) + (1.5 * data[index + 1]) + (-1.5 * data[index + 2]) + (0.5 * data[index + 3]);
    temp2 = (1.0 * data[index]) + (-2.5 * data[index + 1]) + (2.0 * data[index + 2]) + (-0.5 * data[index + 3]);
    temp3 = (data[index + 2] * 0.5) + (0.0 * data[index + 1]) + (-0.5 * data[index]) + (0.0 * data[index + 3]);

    derivative = (((temp * 3 * x) + (2 * temp2)) * x) + temp3;

    return derivative;
}

UNUSED f32 lerp(f32 *arg0, u32 arg1, f32 arg2) {
    f32 result = arg0[arg1 + 1] + ((arg0[arg1 + 2] - arg0[arg1 + 1]) * arg2);
    return result;
}

UNUSED f32 func_800228B0(f32 *arg0, u32 arg1, f32 arg2, f32 *arg3) {
    f32 new_var2;
    f32 temp_f12;
    f32 new_var;
    f32 temp_f2;
    new_var = arg0[arg1 + 2] - arg0[arg1 + 1];
    temp_f2 = new_var * arg2;
    temp_f12 = arg0[arg1 + 1];
    new_var2 = temp_f12 + temp_f2;
    *arg3 = arg0[arg1 + 2] - arg0[arg1 + 1];
    return new_var2;
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
        racer->unk1FC = 0;
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
        func_8009F034();
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
        racerObj = spawn_object(&newRacerEntry.common, 1);
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
            if (!(gObjPtrList[j]->segment.trans.flags & OBJ_FLAGS_DEACTIVATED) &&
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
        if (!(gObjPtrList[i]->segment.trans.flags & OBJ_FLAGS_DEACTIVATED) &&
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
        set_taj_status(2);
    } else {
        music_change_on();
        music_stop();
        set_next_taj_challenge_menu(0);
        audioline_on();
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
    ObjectSegment *activeCameraSegment;
    s32 yOutCount;
    f32 yOut[9];
    Object *ptrList;
    s32 i;

    if (gNumberOfCheckpoints == 0) {
        lastCheckpointNode = NULL;
        for (i = 0; i < gObjectCount; i++) {
            ptrList = gObjPtrList[i];
            if (!(ptrList->segment.trans.flags & OBJ_FLAGS_DEACTIVATED) && (ptrList->behaviorId == BHV_SETUP_POINT)) {
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
        activeCameraSegment = get_active_camera_segment_no_cutscenes();
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
            if (!(tempObj->segment.trans.flags & OBJ_FLAGS_DEACTIVATED) && tempObj->behaviorId == BHV_TAJ_TELEPOINT) {
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
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_UNK04 | OBJECT_SPAWN_UNK08 |
                    OBJECT_SPAWN_INTERACTIVE;
            break;
        case BHV_SCENERY:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_INTERACTIVE;
            break;
        case BHV_WEAPON:
            flags = OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_UNK04 | OBJECT_SPAWN_INTERACTIVE;
            break;
        case BHV_DINO_WHALE:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_UNK08 | OBJECT_SPAWN_INTERACTIVE;
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
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_UNK08 | OBJECT_SPAWN_INTERACTIVE |
                    OBJECT_SPAWN_UNK20;
            break;
        case BHV_SNOWBALL_3:
        case BHV_SNOWBALL_4:
        case BHV_HIT_TESTER_3:
        case BHV_HIT_TESTER_4:
            flags = OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_UNK08 | OBJECT_SPAWN_INTERACTIVE | OBJECT_SPAWN_UNK20;
            break;
        case BHV_UNK_18:
            flags = OBJECT_SPAWN_UNK04;
            break;
        case BHV_STOPWATCH_MAN:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_UNK08 | OBJECT_SPAWN_INTERACTIVE;
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
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_UNK08 | OBJECT_SPAWN_INTERACTIVE | OBJECT_SPAWN_UNK20;
            break;
        case BHV_RAMP_SWITCH:
            flags = OBJECT_SPAWN_INTERACTIVE | OBJECT_SPAWN_SHADOW;
            break;
        case BHV_SEA_MONSTER:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_UNK08;
            break;
        case BHV_COLLECT_EGG:
            flags = OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_INTERACTIVE;
            break;
        case BHV_UNK_30:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_UNK08;
            break;
        case BHV_UNK_3F:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_UNK08;
            break;
        case BHV_ANIMATED_OBJECT:
        case BHV_VEHICLE_ANIMATION:
        case BHV_PARK_WARDEN_2:
        case BHV_WIZPIG_SHIP:
        case BHV_ANIMATED_OBJECT_4:
        case BHV_PIG_ROCKETEER:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_UNK08;
            break;
        case BHV_CHARACTER_SELECT:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_UNK08;
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
            flags = OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_UNK08;
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
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_UNK08 | OBJECT_SPAWN_INTERACTIVE;
            break;
        case BHV_FROG:
            flags = OBJECT_SPAWN_UNK01 | OBJECT_SPAWN_SHADOW | OBJECT_SPAWN_UNK08;
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
