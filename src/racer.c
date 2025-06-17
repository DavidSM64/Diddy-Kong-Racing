#include "racer.h"
#include "memory.h"
#include "menu.h"
#include "video.h"

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "asset_enums.h"
#include "save_data.h"
#include "audio_spatial.h"
#include "objects.h"
#include "audio.h"
#include "object_functions.h"
#include "game.h"
#include "printf.h"
#include "math_util.h"
#include "tracks.h"
#include "weather.h"
#include "vehicle_misc.h"
#include "audio_vehicle.h"
#include "game_ui.h"
#include "object_models.h"
#include "audiosfx.h"
#include "collision.h"
#include "joypad.h"
#include "particles.h"
#include "PRinternal/viint.h"
#include "common.h"

#define MAX_NUMBER_OF_GHOST_NODES 360

/**
 * This file features extensive use of CLAMP and WRAP.
 * CLAMP will keep the value within the two ranges.
 * WRAP will "overflow" the value. Used to keep angles within s16 bounds.
 */

/************ .data ************/

s32 gObjLoopGoldenBalloonLength = 0x310;
s16 gAntiPiracyHeadroll = 0;
s32 D_800DCB58 = 0; // Currently unknown, might be a different type.
s32 D_800DCB5C = 0; // Currently unknown, might be a different type.

// Not sure if D_800DCB58 & D_800DCB5C are actually a part of this array.
f32 D_800DCB60[14] = {
    -10.0f, 5.0f, 0.0f, 0.0f, 10.0f, 5.0f, 0.0f, 0.0f, -10.0f, 10.0f, 0.0f, 0.0f, 10.0f, 10.0f,
};

s32 gNumViewports = 0; // Currently unknown, might be a different type.
// Table used for quantifying speed reduction while the car drives over it, like how grass will slow you down more than
// the road. An antipiracy trigger can set the first index to 0.5f, which makes that surface type impossible to drive
// on.
f32 gSurfaceTractionTable[19] = {
    0.004f, 0.007f, 0.01f,  0.004f, 0.01f,  0.01f,  0.01f,  0.01f,  0.01f,  0.01f,
    0.004f, 0.004f, 0.004f, 0.004f, 0.004f, 0.004f, 0.004f, 0.004f, 0.004f,
};
// Can only assume this is surface related too. Not incline thresholds though.
f32 D_800DCBE8[19] = {
    0.8f, 0.85f, 0.85f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.8f, 0.8f, 0.84f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f,
};
// When driving over this surface, the car begins to bob up and down to give the effect of roughness.
s32 gSurfaceBobbingTable[19] = {
    0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
// When landing on this surface, it makes a sound.
// Strangely, they did only two surface types then called it a day.
s32 gSurfaceSoundTable[19] = { SOUND_NONE, SOUND_LAND_GRASS, SOUND_LAND_SAND, SOUND_NONE, SOUND_NONE,
                               SOUND_NONE, SOUND_NONE,       SOUND_NONE,      SOUND_NONE, SOUND_NONE,
                               SOUND_NONE, SOUND_NONE,       SOUND_NONE,      SOUND_NONE, SOUND_NONE,
                               SOUND_NONE, SOUND_NONE,       SOUND_NONE,      SOUND_NONE };

u16 D_800DCCCC[19] = {
    0x010C, 0x010B, 0x0009, 0x010C, 0x010C, 0x010C, 0x010C, 0x010C, 0x010C, 0x010C,
    0x010C, 0x0005, 0x010C, 0x010C, 0x010C, 0x010C, 0x010C, 0x010C, 0x010C,
};

s32 gSurfaceFlagTable[19] = {
    1, 4, 0x10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0x100, 1, 1, 1, 1, 1,
};

s32 gSurfaceFlagTable4P[20] = {
    0, 4, 0x10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x100, 0, 0, 0, 0, 0, 0,
};

// Used to know how the AI should use a balloon when they have one.
s8 gRacerAIBalloonActionTable[NUM_WEAPON_TYPES] = { 1, 1, 2, 2, 4, 3, 0, 6, 4, 3, 2, 2, 5, 5, 5, 0 };

// Unused?
s8 D_800DCDA0[8] = {
    0, 0, 0, 1, 1, 2, 2, 2,
};

s8 D_800DCDA8[8] = {
    1, 1, 1, 2, 3, 2, 3, 2,
};

s8 D_800DCDB0[16][2] = {
    { 0x02, 0xFE }, { 0x03, 0xFE }, { 0x02, 0xFC }, { 0x02, 0xFB }, { 0x02, 0xFB }, { 0x02, 0xFE },
    { 0x02, 0xFD }, { 0x02, 0xFE }, { 0x03, 0xFD }, { 0x05, 0xFC }, { 0x04, 0xFE }, { 0x02, 0xFE },
    { 0x02, 0xFA }, { 0x02, 0xFE }, { 0x08, 0xF8 }, { 0x03, 0xFD },
};

// Checksum count for obj_loop_goldenballoon
s32 gObjLoopGoldenBalloonChecksum = ObjLoopGoldenBalloonChecksum;

FadeTransition gDoorFadeTransition = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 50, FADE_STAY);

/*******************************/

/************ .rodata ************/

const char gRacerDebugCoords[] = "%.1f,%.1f,%.1f\n";
UNUSED const char gChecksumOverflowString[] = "Chk ovflow!!\n";
UNUSED const char gRacerBackString[] = "Back\n";

/*********************************/

/************ .bss ************/

f32 gCurrentCourseHeight;
Vec3f gCurrentRacerWaterPos;
s8 gRacerWaveType;
Camera *gCameraObject;
UNUSED s32 D_8011D50C;
ObjectTransform gCurrentRacerTransform;
u32 gCurrentRacerInput;
u32 gCurrentButtonsPressed;
u32 gCurrentButtonsReleased;
s32 gCurrentStickX;
s32 gCurrentStickY;
s32 unused_8011D53C; // Set to 0 and only 0. Checked for being 1, but never true.
s32 gRaceStartTimer;
f32 D_8011D544; // Starts are 300, then counts down when the race starts. Usage currently unknown.
f32 D_8011D548;
f32 D_8011D54C;
u16 D_8011D550;
u16 D_8011D552;
s32 gCurrentCarSteerVel;
s32 D_8011D558;
s32 gCurrentPlayerIndex;
s16 D_8011D560; // Set, but never read.
f32 *gCurrentRacerMiscAssetPtr;
f32 *D_8011D568;
f32 gCurrentRacerWeightStat;
f32 gCurrentRacerHandlingStat;
f32 gCurrentRacerUnusedMiscAsset11; // Set, but never read
f32 gRacerMagnetVelX;
f32 gRacerMagnetVelZ;
u8 D_8011D580;
s8 gCurrentSurfaceType;
s8 gTajInteractStatus;
s8 gRacerDialogueCamera;
s8 gRacerInputBlocked;
s8 gStartBoostTime;
s16 gDialogueCameraAngle;
s8 gEggChallengeFlags[4];
s8 D_8011D58C[4];
GhostNode *gGhostData[3];
s8 gCurrentGhostIndex;
s8 gPrevGhostNodeIndex;
s16 gGhostNodeDelay;
s16 gGhostNodeCount[3];
s16 gGhostNodeFull[2];
s16 gGhostMapID; // Previous MapId?
s8 gRacerWaveCount;
s8 D_8011D5AF;
WaterProperties **gRacerCurrentWave;
s8 D_8011D5B4[4];
s16 D_8011D5B8;

/******************************/

void func_80042D20(Object *obj, Object_Racer *racer, s32 updateRate) {
    f32 sp94;
    f32 sp90;
    s8 *balloonData;
    s32 pad_sp88;
    f32 var_f12;
    f32 var_f0;
    f32 pad_sp7C;
    s16 index;
    s16 var_t5;
    s16 var_t0;
    s16 pad_sp74;
    s16 racerID;
    s16 temp_v0;
    s16 sp6E;
    s8 pad_sp6D;
    s8 someFlag;
    s32 numRacers;
    f32 *miscAsset3;
    Object **racerGroup;
    Object_Racer *sp5C;
    Object_Racer *sp58;
    AIBehaviourTable *sp54;
    LevelHeader *header;
    s32 pad_sp4C;
    s8 balloonType;
    s8 temp7;
    s16 tempRacerIndex;
    s8 *miscAsset2;
    s8 *miscAsset1;
    s8 sp3F;
    s8 racerCharacterId;
    s16 sp3C;
    s16 sp3A;
    s16 sp38;
    s16 sp36;
    s16 var_t4;

    sp6E = racer->unk1CA;
    miscAsset1 = (s8 *) get_misc_asset(ASSET_MISC_1);
    miscAsset2 = (s8 *) get_misc_asset(ASSET_MISC_2);
    header = get_current_level_header();
    racerGroup = get_racer_objects_by_position(&numRacers);
    sp54 = get_ai_behaviour_table();
    if (racer->unk1C6 > 0) {
        racer->unk1C6 -= updateRate;
    } else {
        racer->unk1C6 = 0;
    }
    if (race_finish_timer() != 0) {
        gCurrentRacerInput |= A_BUTTON;
        return;
    }

    index = 0;
    var_t5 = 0;
    var_t0 = 0;
    var_t4 = PLAYER_COMPUTER;
    for (someFlag = TRUE; index < numRacers; index++) {
        sp5C = &racerGroup[index]->unk64->racer;
        if (sp5C == racer) {
            someFlag = FALSE;
            racerID = index;
        }

        if (sp5C->playerIndex == PLAYER_COMPUTER) {
            var_t0++;
            if (someFlag) {
                var_t5++;
            }
        } else if (var_t4 == PLAYER_COMPUTER) {
            var_t4 = index;
        }
    }

    if (var_t4 == PLAYER_COMPUTER) {
        var_t4 = PLAYER_ONE;
    }

    if (var_t0 == 0) {
        return;
    }

    temp_v0 = func_80023568();
    if (gRaceStartTimer == 0 && racer->vehicleID != VEHICLE_LOOPDELOOP) {
        index = racerID - 1;
        if (racer->unk20B < racerID && index >= 0 && index < numRacers) {
            sp5C = &racerGroup[index]->unk64->racer;
            if (sp5C->playerIndex != PLAYER_COMPUTER) {
                if (temp_v0 == 0) {
                    play_random_character_voice(obj, SOUND_VOICE_CHARACTER_NEGATIVE, 8, 3);
                } else {
                    racer_boss_sound_spatial(obj->segment.trans.x_position, obj->segment.trans.y_position,
                                             obj->segment.trans.z_position, 5);
                }
                play_random_character_voice(racerGroup[index], SOUND_VOICE_CHARACTER_POSITIVE, 8, 2);
            }
        }
        tempRacerIndex = racerID + 1;
        if (racerID < racer->unk20B && tempRacerIndex >= 0 && tempRacerIndex < numRacers) {
            sp5C = &racerGroup[tempRacerIndex]->unk64->racer;
            if (sp5C->playerIndex != PLAYER_COMPUTER) {
                play_random_character_voice(racerGroup[(racerID + 1)], SOUND_VOICE_KRUNCH_NEGATIVE1, 8, 2);
                if (temp_v0 == 0) {
                    play_random_character_voice(obj, SOUND_VOICE_CHARACTER_POSITIVE, 8, 3);
                } else {
                    racer_boss_sound_spatial(obj->segment.trans.x_position, obj->segment.trans.y_position,
                                             obj->segment.trans.z_position, 3);
                }
            }
        }
    }
    racer->unk20B = racerID;
    sp94 = 0.0f;
    sp90 = 0.0f;
    sp5C = NULL;
    obj = func_8001B7A8(racer, 1, &sp94);
    if (obj != NULL) {
        sp5C = &obj->unk64->racer;
    }
    sp58 = NULL;
    obj = func_8001B7A8(racer, -1, &sp90);
    if (obj != NULL) {
        sp58 = &obj->unk64->racer;
    }
    racerCharacterId = racer->characterId;
    if (sp5C != NULL) {
        sp3F = sp5C->characterId;
    }

    if (var_t0 < 7 && get_trophy_race_world_id() == 0 && func_80023568() == 0 && !is_taj_challenge()) {
        if (gRaceStartTimer == 100) {
            racer->aiSkill = rand_range(AI_MASTER, AI_HARD);
        }
    } else if (get_trophy_race_world_id() != 0) {
        racer->aiSkill = header->unk16[racerCharacterId];
    } else {
        racer->aiSkill = header->unkC[racerCharacterId];
    }

    if (D_8011D544 != 0.0f) {
        racer->unk1CA = D_800DCDA0[racer->racePosition];
    }
    index = racer->aiSkill - 2;
    index <<= 2;
    if (index <= 300.0f - D_8011D544) {
        gCurrentRacerInput |= A_BUTTON;
    }
    balloonData = (s8 *) get_misc_asset(ASSET_MISC_BALLOON_DATA);
    if (racer->balloon_level < 3) {
        balloonType = balloonData[racer->balloon_type * 3 + racer->balloon_level];
    } else {
        balloonType = racer->balloon_type;
    }

    sp38 = sp54->percentages[1][0] + (((sp54->percentages[1][1] - sp54->percentages[1][0]) * (7 - var_t5)) / 7);
    sp36 = sp54->percentages[2][0] + (((sp54->percentages[2][1] - sp54->percentages[2][0]) * (7 - var_t5)) / 7);
    sp3A = sp54->percentages[0][0] + (((sp54->percentages[0][1] - sp54->percentages[0][0]) * (7 - var_t5)) / 7);
    sp3C = sp54->percentages[3][0] + (((sp54->percentages[3][1] - sp54->percentages[3][0]) * (7 - var_t5)) / 7);

    if (racer->unk209 & 1) {
        if (racer->unk201 == 0) {
            if (racer->balloon_level == 0) {
                if (roll_percent_chance(sp38)) {
                    racer->balloon_level++;
                }
            }
            if (var_t4 == 0 && var_t5 < 3) {
                if (roll_percent_chance(sp3C)) {
                    racer->balloon_type = 0;
                }
            }
        }
        if (racer->boostTimer == 0 && gRacerAIBalloonActionTable[balloonType] == 4) {
            if (roll_percent_chance(sp3C)) {
                gCurrentButtonsReleased |= Z_TRIG;
            }
        }
        if (racer->balloon_quantity != 0) {
            if (gRacerAIBalloonActionTable[balloonType] == 1) {
                if (sp5C != NULL && sp5C->playerIndex == PLAYER_COMPUTER) {
                    if (var_t4 < 4) {
                        racer->unk1C6 = miscAsset2[racerCharacterId] * 60;
                        racer->unk1C9 = 4;
                    }
                } else if (roll_percent_chance(sp36) && var_t4 < 2) {
                    racer->unk1C6 = miscAsset2[racerCharacterId] * 60;
                    racer->unk1C9 = 4;
                }
            }
            if (gRacerAIBalloonActionTable[balloonType] == 2) {
                if (sp58 != NULL && sp58->playerIndex == PLAYER_COMPUTER) {
                    if (var_t4 < 4) {
                        racer->unk1C6 = miscAsset2[racerCharacterId] * 60;
                        racer->unk1C9 = 5;
                    }
                } else if (roll_percent_chance(sp36) && var_t4 < 2) {
                    racer->unk1C6 = miscAsset2[racerCharacterId] * 60;
                    racer->unk1C9 = 5;
                }
            }
        }
        racer->unk209 &= ~1;
    }
    if (racer->boostTimer != 0) {
        if (!(racer->unk209 & 2)) {
            if (roll_percent_chance(sp3A)) {
                racer->unk209 |= 4;
            }
            racer->unk209 |= 2;
        }
        if (racer->unk209 & 4) {
            gCurrentRacerInput &= ~A_BUTTON;
        }
    } else {
        racer->unk209 &= ~2;
        if (racer->velocity > -12.0) {
            racer->unk209 &= ~4;
        }
    }
    if (racer->unk209 & 4) {
        gCurrentRacerInput &= ~A_BUTTON;
    }
    if (racer->unk1C6 == 0) {
        if (racer->unk1C9 == 4 || racer->unk1C9 == 5) {
            gCurrentButtonsReleased |= Z_TRIG;
        }
        racer->unk1C9 = 0;
        if (sp58 != NULL && sp58->playerIndex != PLAYER_COMPUTER && sp90 < 200.0f && var_t5 != 0 && var_t4 < 3 &&
            miscAsset1[(racerCharacterId * 10) + sp3F] < 5) {
            racer->unk1C9 = 5;
        }
        if (D_8011D544 == 0.0f) {
            racer->unk1CA = D_800DCDA8[var_t5];
            if (roll_percent_chance(sp3C)) {
                racer->unk1CA -= 1;
            }
        }
        racer->unk1C6 = 300;
    }
    // @fake
    if ((7 - var_t5) == (7 & 0xFFFFFFFFu) && sp58 != NULL && sp90 < -2500.0) {
        racer->unk209 &= ~4;
        racer->unk1CA = 1;
    }
    if (gRaceStartTimer == 0) {
        var_f0 = sp54->unk4;
        var_f0 = sqrtf(((var_f0 * 0.025) + 0.561) / 0.004);
        var_f12 = sp54->unk0;
        var_f12 = sqrtf(((var_f12 * 0.025) + 0.561) / 0.004);
        // explicit load of 7 required
        temp7 = 7;
        var_f12 += ((var_f0 - var_f12) / temp7) * (7 - var_t5);
        if (racer->unk1CA > 1) {
            // casts below required
            var_f12 += (f32) (((s32) racer->unk1CA) - 1) * 0.2;
        }

        var_f12 = ((var_f12 * var_f12 * 0.004) - 0.595) / 0.025;
        racer->unk124 = var_f12;
        // @fake
        if (!racer) {}
    }
    if (sp5C != NULL && racer->unk1CA == 3 && 500.0 < sp94) {
        racer->unk1CA = 2;
    }
    switch (racer->unk1C9) {
        case 0:
            if (sp5C != NULL && sp5C->playerIndex == PLAYER_COMPUTER && sp5C->unk1C9 == 0) {
                if (sp5C->unk1CA == racer->unk1CA && 100.0 > sp94) {
                    racer->unk1CA++;
                    if (racer->unk1CA > 3) {
                        racer->unk1CA = 3;
                    }
                }
            }
            break;
        case 4:
            if (sp5C != NULL) {
                racer->unk1BA = sp5C->unk1BA;
            }
            break;
        case 5:
            if (sp58 != NULL) {
                racer->unk1BA = sp58->unk1BA;
            }
            break;
    }
    // clang-format off
    index = (u16) is_taj_challenge();\
    if (index != 0 || temp_v0 != 0) {
        // clang-format on
        racer->unk1CA = 0;
        racer->unk1C9 = 0;
        if (temp_v0 != 0) {
            miscAsset3 = (f32 *) get_misc_asset(ASSET_MISC_18);
            index = temp_v0;
        } else {
            miscAsset3 = (f32 *) get_misc_asset(ASSET_MISC_17);
        }
        racer->unk124 = miscAsset3[index - 1];
    }
    if (temp_v0 != 0) {
        if (gRaceStartTimer != 0) {
            D_8011D5B8 = 900;
        } else {
            D_8011D5B8 -= updateRate;
            if (D_8011D5B8 < 0) {
                D_8011D5B8 = 0;
                if (racerID == 1 && sp94 > 650.0) {
                    racer->unk124 += 2.0;
                }
            } else {
                var_f0 = racer->unk124;
                if (D_8011D5B8 > 720) {
                    var_f0 += 5.0;
                } else if (racerID == 1 || sp90 < 200.0) {
                    var_f0 += 10.0;
                }
                if (racer->unk124 < var_f0) {
                    racer->unk124 = var_f0;
                }
            }
        }
        if (racer->raceFinished != FALSE) {
            racer->boostTimer = 0;
            racer->unk213 = 0;
            gCurrentRacerInput &= ~A_BUTTON;
            gCurrentRacerInput |= B_BUTTON;
            if (racer->velocity > -0.3) {
                gCurrentRacerInput |= A_BUTTON;
                gCurrentStickX = 0;
            }
        }
    }
    if (racer->unk214 != 0) {
        racer->unk1CA = sp6E;
    }
    if (racer->unk1BA > 64) {
        racer->unk1BA = 64;
    }
    if (racer->unk1BC > 40) {
        racer->unk1BC = 40;
    }
    if (racer->unk1BA < -64) {
        racer->unk1BA = -64;
    }
    if (racer->unk1BC < -40) {
        racer->unk1BC = -40;
    }
}

/**
 * During specific or nonspecific actions, increase the steps in the AI behaviour table.
 * Increment percent chances of them performing specific actions, with a maximum of 100%.
 */
void increment_ai_behaviour_chances(Object *obj, Object_Racer *racer, s32 updateRate) {
    AIBehaviourTable *aiTable;
    s8 *test;
    s8 balloonType;
    s32 i;
    static s8 sAIFramesSinceA;
    static s8 sAIStartedBoosting;
    static s8 sBalloonLevelAI;

    if (!obj) {
        sAIFramesSinceA = 0;
        sAIStartedBoosting = 0;
        sBalloonLevelAI = 0;
        return;
    }
    aiTable = get_ai_behaviour_table();
    if (racer->boostTimer) {
        if (sAIStartedBoosting == FALSE) {
            aiTable->percentages[AI_BLUE_BALLOON][AI_MIN] += aiTable->percentages[AI_BLUE_BALLOON][AI_MIN_STEP];
            aiTable->percentages[AI_BLUE_BALLOON][AI_MAX] += aiTable->percentages[AI_BLUE_BALLOON][AI_MAX_STEP];
            sAIStartedBoosting = TRUE;
        }
        if (!(gCurrentRacerInput & A_BUTTON)) {
            sAIFramesSinceA += updateRate;
        }
    } else {
        sAIStartedBoosting = FALSE;
        if (sAIFramesSinceA > 20) {
            aiTable->percentages[AI_EMPOWERED_BOOST][AI_MIN] += aiTable->percentages[AI_EMPOWERED_BOOST][AI_MIN_STEP];
            aiTable->percentages[AI_EMPOWERED_BOOST][AI_MAX] += aiTable->percentages[AI_EMPOWERED_BOOST][AI_MAX_STEP];
        }
        sAIFramesSinceA = 0;
    }
    if (racer->balloon_quantity) {
        if (sBalloonLevelAI < racer->balloon_level) {
            aiTable->percentages[AI_GETS_BALLOON][AI_MIN] += aiTable->percentages[1][AI_MIN_STEP];
            aiTable->percentages[AI_GETS_BALLOON][AI_MAX] += aiTable->percentages[1][AI_MAX_STEP];
        }
        sBalloonLevelAI = racer->balloon_level;
    } else {
        sBalloonLevelAI = 0;
    }
    test = (s8 *) get_misc_asset(ASSET_MISC_BALLOON_DATA);
    if ((gCurrentButtonsReleased & Z_TRIG) && racer->balloon_quantity) {
        if (racer->balloon_level < 3) {
            balloonType = test[racer->balloon_type * 3 + racer->balloon_level];
        } else {
            balloonType = racer->balloon_type;
        }
        if (gRacerAIBalloonActionTable[balloonType] == 1) {
            aiTable->percentages[AI_UNK_2][AI_MIN] += aiTable->percentages[AI_UNK_2][AI_MIN_STEP];
            aiTable->percentages[AI_UNK_2][AI_MAX] += aiTable->percentages[AI_UNK_2][AI_MAX_STEP];
        }
    }
    for (i = 0; i < 2; i++) {
        if (aiTable->percentages[AI_GETS_BALLOON][i] > 100 || aiTable->percentages[AI_GETS_BALLOON][i] < 0) {
            aiTable->percentages[AI_GETS_BALLOON][i] = 100;
        }
        if (aiTable->percentages[AI_EMPOWERED_BOOST][i] > 100 || aiTable->percentages[AI_EMPOWERED_BOOST][i] < 0) {
            aiTable->percentages[AI_EMPOWERED_BOOST][i] = 100;
        }
        if (aiTable->percentages[AI_BLUE_BALLOON][i] > 100 || aiTable->percentages[AI_BLUE_BALLOON][i] < 0) {
            aiTable->percentages[AI_BLUE_BALLOON][i] = 100;
        }
        if (aiTable->percentages[AI_UNK_2][i] > 100 || aiTable->percentages[AI_UNK_2][i] < 0) {
            aiTable->percentages[AI_UNK_2][i] = 100;
        }
    }
}

/**
 * Depending on the race type, call a function that handles pathing.
 * During those functions, the racer inputs will be set to simulate control.
 */
void racer_AI_pathing_inputs(Object *obj, Object_Racer *racer, s32 updateRate) {
    s32 raceType;

    raceType = get_current_level_race_type();

    switch (raceType) {
        case RACETYPE_CHALLENGE_BATTLE:
        case RACETYPE_CHALLENGE_BANANAS:
            func_8004447C(obj, racer, updateRate);
            break;
        case RACETYPE_CHALLENGE_EGGS:
            func_800452A0(obj, racer, updateRate);
            break;
        default:
            func_80045C48(obj, racer, updateRate);
            break;
    }

    if (racer->unk214 == 0 && racer->velocity < -0.5) {
        racer->unk215 -= updateRate;
        if (racer->unk215 < 0) {
            racer->unk215 = 0;
        }
    }

    if (racer->velocity > -1.0 && racer->unk214 == 0 && !gRaceStartTimer && D_8011D544 == 0.0f &&
        racer->groundedWheels && racer->unk215 == 0) {
        racer->unk213 += updateRate;

        if (racer->unk213 > 60) {
            racer->unk213 = 0;
            racer->unk214 = 60;
            racer->unk215 = 120;

            if (!(raceType & RACETYPE_CHALLENGE)) {
                racer->unk1CA = (racer->unk1CA + 1) & 3;
            } else if (raceType == RACETYPE_CHALLENGE_BATTLE || raceType == RACETYPE_CHALLENGE_BANANAS) {
                if (racer->unk1CE != 0xFF) {
                    racer->unk154 = ainode_get(racer->unk1CE);
                }
            }
        }
    } else {
        racer->unk214 -= updateRate;
        racer->unk213 = 0;

        if (racer->unk214 < 0) {
            racer->unk214 = 0;
        }
    }

    // Kick it into reverse.
    if (racer->unk214 != 0) {
        gCurrentStickX *= -1;
        gCurrentRacerInput &= ~A_BUTTON;
        gCurrentStickY = -50;
        gCurrentRacerInput |= B_BUTTON;
    }

    // Cap stick inputs.
    CLAMP(gCurrentStickX, -75, 75);
    CLAMP(gCurrentStickY, -75, 75);
}

/**
 * Rolls a number between 0 and 99.
 * Effectively, this is to make a 1-100% chance of it returning true, based on the number passed.
 */
s32 roll_percent_chance(s32 chance) {
    return rand_range(0, 99) < chance;
}

// Handles the opponent A.I. for battle & banana challenges.
void func_8004447C(Object *aiRacerObj, Object_Racer *aiRacer, s32 updateRate) {
    Object *sp74;
    Object_64 *tempRacer;
    LevelObjectEntry *sp6C;
    LevelObjectEntry *newvar;
    f32 xDiff;
    f32 zDiff;
    f32 dist;
    s32 temp;
    LevelHeader *levelHeader;
    s16 i;
    s16 index;
    s16 sp4E;
    s16 sp4C;
    s16 sp4A;
    s16 sp48;
    s16 sp46;
    s32 var_v1;
    s8 raceType;
    s8 *sp38;
    Object *tempRacerObj;

    gCurrentButtonsPressed = 0;
    gCurrentButtonsReleased = 0;
    gCurrentRacerInput = 0;
    gCurrentStickX = 0;
    gCurrentStickY = 0;
    get_racer_objects(&temp); // temp = Number of racers
    if (temp != 4) {
        return;
    }

    levelHeader = get_current_level_header();
    raceType = levelHeader->race_type;
    sp38 = levelHeader->unk2A;
    if (aiRacer->unk1CD == 0) {
        temp = ainode_find_nearest(aiRacerObj->segment.trans.x_position, aiRacerObj->segment.trans.y_position,
                                   aiRacerObj->segment.trans.z_position, 0);
        if (temp != 0xFF) {
            aiRacer->unk154 = ainode_get(temp);
            aiRacer->unk1CD = 1;
            aiRacer->unk1CE = 0xFF;
        }
    }
    sp74 = aiRacer->unk154;
    if (sp74 != NULL) {
        sp6C = sp74->segment.level_entry;
        xDiff = sp74->segment.trans.x_position - aiRacerObj->segment.trans.x_position;
        zDiff = sp74->segment.trans.z_position - aiRacerObj->segment.trans.z_position;
        dist = sqrtf((xDiff * xDiff) + (zDiff * zDiff));
        if (dist > 0.0) {
            temp = ((arctan2_f(xDiff, zDiff)) - 0x8000) & 0xFFFF;
            var_v1 = temp - (aiRacer->steerVisualRotation & 0xFFFF);
            if (var_v1 > 0x8000) {
                var_v1 -= 0xFFFF;
            }
            if (var_v1 < -0x8000) {
                var_v1 += 0xFFFF;
            }
            gCurrentStickX = -var_v1 >> 4;
        }
    }
    if (gRaceStartTimer != 0) {
        aiRacer->unk1C6 = 0;
    }
    if ((aiRacer->unk1CD == 2) || (aiRacer->unk1CD == 4) || (aiRacer->unk1CD == 5)) {
        if (aiRacer->unk1C6 > 0) {
            aiRacer->unk1C6 -= updateRate;
        } else {
            aiRacer->unk1C6 = 0;
        }
    }
    aiRacer->elevation = obj_elevation(aiRacerObj->segment.trans.y_position);
    switch (aiRacer->unk1CD) {
        case 1:
            rand_range(0, 9);
            if (aiRacer->balloon_quantity == 0) {
                if (roll_percent_chance(sp38[3]) != 0) {
                    aiRacer->unk1CD = 3;
                } else if ((roll_percent_chance(sp38[6]) != 0) && (raceType == RACETYPE_CHALLENGE_BANANAS) &&
                           (aiRacer->bananas >= 2)) {
                    aiRacer->unk1CD = 7;
                } else if ((roll_percent_chance(sp38[5]) != 0) && (D_8011D58C[aiRacer->racerIndex] != 0)) {
                    aiRacer->unk1C6 = 1200;
                    aiRacer->eggHudCounter = D_8011D58C[aiRacer->racerIndex] - 1;
                    aiRacer->unk1CD = 5;
                } else {
                    aiRacer->unk1CD = 2;
                    aiRacer->unk1C6 = 300;
                }
            } else if ((roll_percent_chance(sp38[6]) != 0) && (raceType == RACETYPE_CHALLENGE_BANANAS) &&
                       (aiRacer->bananas >= 2)) {
                aiRacer->unk1CD = 7;
            } else if (roll_percent_chance(sp38[0]) != 0) {
                if (roll_percent_chance(50) != 0) {
                    sp4C = 1;
                } else {
                    sp4C = 0;
                }
                if (roll_percent_chance(sp38[1]) != 0) {
                    sp46 = 0;
                } else {
                    sp46 = 1;
                }
                sp4A = -1;
                sp48 = sp46 << 4;
                for (i = 0; i < 4; i++) {
                    if (sp4C != 0) {
                        index = 3 - i;
                    } else {
                        index = i;
                    }
                    if ((D_8011D58C[index] == 0) && (index != aiRacer->racerIndex)) {
                        tempRacerObj = get_racer_object(index);
                        tempRacer = tempRacerObj->unk64;
                        if (sp46 == 0) {
                            if (sp48 < tempRacer->racer.bananas) {
                                sp48 = tempRacer->racer.bananas;
                                sp4A = index;
                            }
                        } else {
                            if ((tempRacer->racer.bananas > 0) && (tempRacer->racer.bananas < sp48)) {
                                sp48 = tempRacer->racer.bananas;
                                sp4A = index;
                            }
                        }
                    }
                }
                if (roll_percent_chance(sp38[2]) != 0) {
                    if (cam_get_viewport_layout() == 0) {
                        tempRacerObj = get_racer_object(index);
                        tempRacer = tempRacerObj->unk64;
                        if (tempRacer->racer.bananas > 0) {
                            sp4A = 0;
                        }
                    }
                }
                if (sp4A >= 0) {
                    aiRacer->eggHudCounter = (s8) sp4A;
                    D_8011D58C[sp4A] = aiRacer->racerIndex + 1;
                    aiRacer->unk1CD = 4;
                    aiRacer->unk1C6 = 0x4B0;
                } else {
                    aiRacer->unk1CD = 2;
                    aiRacer->unk1C6 = 0x4B0;
                }
            } else {
                aiRacer->unk1CD = 2;
                aiRacer->unk1C6 = 0x12C;
            }
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 7:
            switch (aiRacer->unk1CD) {
                case 2:
                    if (aiRacer->unk1C6 == 0) {
                        aiRacer->unk1CD = 1;
                    }
                    break;
                case 3:
                    if (aiRacer->balloon_type != 0) {
                        aiRacer->unk1CD = 2;
                        aiRacer->unk1C6 = 180;
                    }
                    break;
                case 4:
                    if ((aiRacer->balloon_quantity == 0) || (aiRacer->unk1C6 == 0)) {
                        aiRacer->unk1CD = 1;
                        D_8011D58C[aiRacer->eggHudCounter] = 0;
                    }
                    break;
                case 5:
                    if ((D_8011D58C[aiRacer->racerIndex] == 0) || (aiRacer->unk1C6 == 0)) {
                        aiRacer->unk1CD = 1;
                    }
                    break;
                case 7:
                    if (aiRacer->bananas == 0) {
                        aiRacer->unk1CD = 1;
                    }
                    break;
            }
            if (aiRacer->unk1CE != 0xFF) {
                sp4E = aiRacer->elevation;
                tempRacerObj =
                    ainode_get(aiRacer->unk1CE); // I'm assuming this is a Ai Node (Take with a grain of salt!)
                newvar = tempRacerObj->segment.level_entry;
                sp46 = FALSE;
                if (sp6C->aiNode.elevation < newvar->aiNode.elevation) {
                    if (1) {} // FAKE
                    if (newvar->aiNode.elevation < sp4E || sp4E < sp6C->aiNode.elevation) {
                        sp46 = TRUE;
                    }
                } else if (sp6C->aiNode.elevation < sp4E || sp4E < newvar->aiNode.elevation) {
                    sp46 = TRUE;
                }
                if (sp46) {
                    if (aiRacer->unk1CD == 4) {
                        D_8011D58C[aiRacer->eggHudCounter] = 0;
                    }
                    aiRacer->unk1CD = 6;
                }
            }
            if ((gCurrentStickX > -30) && (gCurrentStickX < 30)) {
                if (aiRacer->velocity > -10.0) {
                    gCurrentRacerInput = A_BUTTON;
                }
            } else {
                if (aiRacer->velocity > -4.0) {
                    gCurrentRacerInput = (A_BUTTON | B_BUTTON);
                } else {
                    gCurrentRacerInput = B_BUTTON;
                }
                if (aiRacer->velocity > -1.0) {
                    gCurrentRacerInput = A_BUTTON;
                }
            }

            tempRacerObj = aiRacer->nodeCurrent;
            if (tempRacerObj != NULL) {
                xDiff = tempRacerObj->segment.trans.x_position - sp74->segment.trans.x_position;
                zDiff = tempRacerObj->segment.trans.z_position - sp74->segment.trans.z_position;
                if (sqrtf((xDiff * xDiff) + (zDiff * zDiff)) > 0.0) {
                    temp = (arctan2_f(xDiff, zDiff) - 0x8000) & 0xFFFF;
                    var_v1 = temp - (aiRacer->steerVisualRotation & 0xFFFF);
                    if (var_v1 > 0x8000) {
                        var_v1 -= 0xFFFF;
                    }
                    if (var_v1 < -0x8000) {
                        var_v1 += 0xFFFF;
                    }
                    if ((var_v1 > 0x1500) || (var_v1 < -0x1500)) {
                        if (aiRacer->velocity > -4.0) {
                            gCurrentRacerInput = (A_BUTTON | B_BUTTON);
                        } else {
                            gCurrentRacerInput = B_BUTTON;
                        }
                    }
                }
            }
            if (dist < 300.0) {
                if (aiRacer->nodeCurrent == NULL) {
                    switch (aiRacer->unk1CD) {
                        case 3:
                            temp = func_8001CD28(sp6C->animation.x_rotation, 1, aiRacer->unk1CE, aiRacer->racerIndex);
                            break;
                        case 4:
                            tempRacerObj = get_racer_object(aiRacer->eggHudCounter);
                            tempRacer = tempRacerObj->unk64;
                            if (tempRacer->racer.playerIndex == -1) {
                                tempRacerObj = tempRacer->racer.unk154;
                                newvar = tempRacerObj->segment.level_entry;
                                temp = func_8001CD28(sp6C->animation.x_rotation, newvar->animation.x_rotation | 0x100,
                                                     aiRacer->unk1CE, aiRacer->racerIndex);
                            } else {
                                temp = ainode_find_nearest(tempRacerObj->segment.trans.x_position,
                                                           tempRacerObj->segment.trans.y_position,
                                                           tempRacerObj->segment.trans.z_position, 0);
                                temp = func_8001CD28(sp6C->animation.x_rotation, temp | 0x100, aiRacer->unk1CE,
                                                     aiRacer->racerIndex);
                            }
                            break;
                        case 5:
                            temp = func_8001CD28(sp6C->animation.x_rotation, 1, aiRacer->unk1CE, aiRacer->racerIndex);
                            break;
                        case 7:
                            temp = func_8001CD28(sp6C->animation.x_rotation, aiRacer->racerIndex + 4, aiRacer->unk1CE,
                                                 aiRacer->racerIndex);
                            break;
                        default:
                            temp = ainode_find_next(sp6C->animation.x_rotation, aiRacer->unk1CE, aiRacer->racerIndex);
                            break;
                    }

                    if (temp != 0xFF) {
                        aiRacer->nodeCurrent = ainode_get(temp);
                    } else {
                        if (aiRacer->unk1CE != 0xFF) {
                            aiRacer->nodeCurrent = ainode_get(aiRacer->unk1CE);
                        } else {
                            aiRacer->nodeCurrent = NULL;
                        }
                    }
                }
            }
            if (dist < 50.0 || (dist > 320.0 && aiRacer->nodeCurrent != NULL)) {
                aiRacer->unk1CE = sp6C->animation.x_rotation;
                aiRacer->unk154 = aiRacer->nodeCurrent;
                if (aiRacer->nodeCurrent == NULL) {
                    aiRacer->unk1CD = 0;
                }
                aiRacer->nodeCurrent = NULL;
            }
            break;
        case 6:
            temp = ainode_find_nearest(aiRacerObj->segment.trans.x_position, aiRacerObj->segment.trans.y_position,
                                       aiRacerObj->segment.trans.z_position, 2);
            if (temp != 0xFF) {
                aiRacer->unk154 = ainode_get(temp);
                aiRacer->unk1CD = 1;
                aiRacer->unk1CE = 0xFF;
            }
            aiRacer->unk1C9 = 1;
            break;
    }
    for (i = 0; i < 4; i++) {
        if (i != aiRacer->racerIndex) {
            tempRacerObj = get_racer_object(i);
            tempRacer = tempRacerObj->unk64;
            if (tempRacer->racer.playerIndex != -1) {
                D_8011D5B4[i] = tempRacer->racer.elevation;
            }
            if (D_8011D5B4[aiRacer->racerIndex] == D_8011D5B4[i]) {
                xDiff = aiRacerObj->segment.trans.x_position - tempRacerObj->segment.trans.x_position;
                zDiff = aiRacerObj->segment.trans.z_position - tempRacerObj->segment.trans.z_position;
                if (sqrtf((xDiff * xDiff) + (zDiff * zDiff)) < 800.0) {
                    temp = arctan2_f(xDiff, zDiff);
                    temp -= (aiRacerObj->segment.trans.rotation.y_rotation & 0xFFFF);
                    if (temp > 0x8000) {
                        temp = -0xFFFF;
                    }
                    if (temp < -0x8000) {
                        temp = 0xFFFF;
                    }
                    if (aiRacer->balloon_level == 1) {
                        var_v1 = 0x1000;
                    } else {
                        var_v1 = 0x800;
                    }
                    if ((-var_v1 < temp) && (temp < var_v1)) {
                        gCurrentButtonsReleased |= Z_TRIG;
                    }
                }
            }
        }
    }
}

void func_80045128(Object **racerObjs) {
    Object_Racer *racer;
    s32 i;

    for (i = 0; i < 4; i++) {
        racer = &racerObjs[i]->unk64->racer;
        gEggChallengeFlags[i] = racer->lap;
        if (racer->eggHudCounter != 0) {
            gEggChallengeFlags[i] |= 0x40;
        }
        if (racer->held_obj != NULL) {
            gEggChallengeFlags[i] |= 0x80;
        }
    }
}

void func_800452A0(Object *obj, Object_Racer *racer, s32 updateRate) {
    f32 diffX;
    f32 diffY;
    f32 diffZ;
    f32 distance;
    Object **objList;
    f32 bestDist;
    s32 racerCount;
    s32 i;
    s32 objStart;
    s32 objCount;
    Object_CollectEgg *egg;
    LevelObjectEntry_BHV_UNK_5C *objEntry;
    s32 targetBehaviourID;
    Object *targetObj;
    s32 angleDiffX;
    s32 angleDiffY;
    s8 *header;
    s8 tickCount;
    s8 flags;
    s8 racerID;
    s8 bestTick;
    Object *curObj;

    gCurrentButtonsPressed = 0;
    gCurrentButtonsReleased = 0;
    gCurrentRacerInput = A_BUTTON;
    gCurrentStickX = 0;
    gCurrentStickY = 0;
    get_racer_objects(&racerCount);
    if (racerCount != 4) {
        return;
    }

    header = get_current_level_header()->unk2A;
    if (racer->groundedWheels) {
        racer->unk1C6 += updateRate;
        if (racer->unk1C6 > 60) {
            racer->unk1C6 = 0;
            racer->unk1CD = 0;
            racer->unk1CE = 3;
        }
    } else {
        if (1) {}
        if (1) {}
        if (1) {}
        if (1) {} // Fake
        racer->unk1C6 = 0;
    }

    while (racer->unk1CD == 0) {
        racerID = PLAYER_COMPUTER;
        flags = 0;
        bestTick = 0;
        for (i = 3; i >= 0; i--) {
            tickCount = (gEggChallengeFlags[i] & 0xF) * 3;
            if (gEggChallengeFlags[i] & 0x40) {
                tickCount += 2;
            } else if (gEggChallengeFlags[i] & 0x80) {
                tickCount += 1;
            }
            if (bestTick < tickCount) {
                bestTick = tickCount;
                flags = i;
            }
        }
        if (racer->unk1CE & 0x40) {
            racerID = racer->unk1CE & 0xF;
            racer->unk1CD = 8;
            racer->unk1CE = 0;
        }
        if (racer->unk1CE & 0x80) {
            if (roll_percent_chance(header[6])) {
                bestTick = 2;
            } else {
                bestTick = 1;
                if (roll_percent_chance(header[2]) && cam_get_viewport_layout() == 0) {
                    flags = 0;
                }
            }
            if (bestTick == 2) {
                for (i = 0; i < 4; i++) {
                    if (racer->racerIndex != i && gEggChallengeFlags[i] & 0x40) {
                        racerID = i;
                    }
                }
                if (racerID == PLAYER_COMPUTER) {
                    bestTick = 1;
                } else {
                    racer->unk1CD = 7;
                }
            }
            if (bestTick == 1) {
                if (racer->balloon_quantity != 0) {
                    racer->unk1CD = 6;
                    if (flags != racer->racerIndex) {
                        racerID = flags;
                    } else {
                        racerID = (racer->racerIndex + 1) & 3;
                    }
                } else {
                    racer->unk1CD = 5;
                }
            }
            racer->unk1CE = 0;
        }
        if (racer->held_obj != NULL) {
            racer->unk1CD = 2;
        }
        if (racer->unk1CE != 0) {
            racer->unk1CD = racer->unk1CE;
        }
        bestTick = (racer->unk1CE = 0);
        if (racer->unk1CD == 0) {
            switch (obj->interactObj->pushForce) {
                case 1:
                    racer->unk1CD = 1;
                    break;
                case 2:
                    racer->unk1CD = 1;
                    break;
                case 3:
                    racer->unk1CD = 1;
                    break;
            }
        }
        bestTick = 0;
        if (racer->raceFinished) {
            racer->unk1CD = 3;
        }
        targetBehaviourID = BHV_NONE;
        switch (racer->unk1CD) {
            case 1:
                targetBehaviourID = BHV_COLLECT_EGG;
                break;
            case 2:
                targetBehaviourID = BHV_UNK_5C;
                break;
            case 3: /* fall through */
            case 7:
                targetBehaviourID = BHV_UNK_5C;
                bestTick = 2;
                break;
            case 4:
                racerID = racer->racerIndex;
                targetBehaviourID = BHV_UNK_5C;
                bestTick = 2;
                break;
            case 5:
                targetBehaviourID = BHV_WEAPON_BALLOON;
                break;
            case 6:
                targetBehaviourID = BHV_RACER;
                break;
            case 8:
                targetBehaviourID = BHV_COLLECT_EGG;
                bestTick = 1;
                break;
        }
        if (targetBehaviourID != BHV_NONE && targetBehaviourID != BHV_RACER) {
            bestDist = 1000000.0f;
            objList = objGetObjList(&objStart, &objCount);
            targetObj = NULL;
            for (objStart = 0; objStart < objCount; objStart++) {
                tickCount = FALSE;
                curObj = objList[objStart];
                if (!(curObj->segment.trans.flags & OBJ_FLAGS_PARTICLE) && targetBehaviourID == curObj->behaviorId) {
                    switch (targetBehaviourID) {
                        case BHV_UNK_5C:
                            if (bestTick == curObj->segment.level_entry->bhv_unk_5C.unk8 &&
                                (racerID == PLAYER_COMPUTER ||
                                 racerID == curObj->segment.level_entry->bhv_unk_5C.unk9)) {
                                tickCount = TRUE;
                            }
                            break;
                        case BHV_COLLECT_EGG:
                            egg = &curObj->unk64->egg;
                            if (bestTick == 0) {
                                if (egg->status == EGG_SPAWNED) {
                                    tickCount = TRUE;
                                }
                            } else if (egg->status == EGG_IN_BASE && racerID == egg->racerID) {
                                tickCount = TRUE;
                            }
                            break;
                        default:
                            tickCount = TRUE;
                            break;
                    }
                }
                if (tickCount) {
                    diffX = curObj->segment.trans.x_position - obj->segment.trans.x_position;
                    diffY = curObj->segment.trans.y_position - obj->segment.trans.y_position;
                    diffZ = curObj->segment.trans.z_position - obj->segment.trans.z_position;
                    distance = sqrtf((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ));
                    if (distance < bestDist) {
                        bestDist = distance;
                        targetObj = curObj;
                    }
                }
            }
        }
        if (targetBehaviourID == BHV_RACER && racerID != PLAYER_COMPUTER) {
            targetObj = get_racer_object(racerID);
        }
        racer->unk154 = targetObj;
        if (targetObj == NULL) {
            racer->unk1CE = 0x80;
            racer->unk1CD = 0;
        }
    }
    curObj = racer->unk154;
    distance = 0.0f;
    if (curObj != NULL) {
        if (curObj->behaviorId == BHV_COLLECT_EGG) {
            egg = &curObj->unk64->egg;
            i = racer->unk1CD;
            if (i == 1 && egg->status != EGG_SPAWNED) {
                racer->unk154 = NULL;
            }
            i = racer->unk1CD;
            if (i == 8 && egg->status != EGG_IN_BASE) {
                racer->unk154 = NULL;
            }
        }
        diffX = curObj->segment.trans.x_position - obj->segment.trans.x_position;
        diffY = curObj->segment.trans.y_position - obj->segment.trans.y_position;
        diffZ = curObj->segment.trans.z_position - obj->segment.trans.z_position;
        distance = sqrtf((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ));
        if (distance > 0.0) {
            racerCount = (arctan2_f(diffX, diffZ) - 0x8000) & 0xFFFF;
            angleDiffX = racerCount - (racer->steerVisualRotation & 0xFFFF);
            if (angleDiffX > 0x8000) {
                angleDiffX -= 0xFFFF;
            }
            if (angleDiffX < -0x8000) {
                angleDiffX += 0xFFFF;
            }
            gCurrentStickX = -angleDiffX >> 5;
            angleDiffY = arctan2_f(diffY, sqrtf((diffX * diffX) + (diffZ * diffZ))) & 0xFFFF;
            if (angleDiffY > 0x8000) {
                angleDiffY -= 0xFFFF;
            }
            if (angleDiffY < -0x8000) {
                angleDiffY += 0xFFFF;
            }
            gCurrentStickY = -angleDiffY >> 7;
        }
        if (racer->aiSkill < 0) {
            gCurrentStickX = 0;
            gCurrentStickY = -35;
            racer->aiSkill++;
        } else {
            if (gCurrentStickX > 60 || gCurrentStickX < -60) {
                racer->aiSkill++;
                if (racer->aiSkill > 110) {
                    racer->aiSkill = -40;
                }
            } else {
                racer->aiSkill = 0;
            }
        }
    } else {
        racer->unk1CD = 0;
    }
    switch (racer->unk1CD) {
        case 1: /* fall through */
        case 8:
            if (racer->held_obj != NULL) {
                racer->unk1CD = 0;
                racer->unk1CE = 4;
            }
            break;
        case 2:
            if (distance < 100.0) {
                racer->unk1CD = 0;
                gCurrentButtonsPressed |= Z_TRIG;
            }
            break;
        case 3: /* fall through */
        case 4:
            if (distance < 200.0) {
                racer->unk1CD = 0;
            }
            break;
        case 5:
            if (racer->balloon_quantity != 0) {
                racer->unk1CD = 0;
            }
            break;
        case 6:
            if (racer->balloon_quantity == 0) {
                racer->unk1CD = 0;
            }
            if (distance < 500.0) {
                gCurrentButtonsReleased |= Z_TRIG;
                racer->unk1CD = 0;
            }
            break;
        case 7:
            if (distance < 200.0 && curObj != NULL) {
                racer->unk1CD = 0;
                objEntry = &curObj->segment.level_entry->bhv_unk_5C;
                racer->unk1CE = (objEntry->unk9 & 3) | 0x40;
            }
            break;
    }
}

// https://decomp.me/scratch/O7Ton
#ifdef NON_EQUIVALENT
void func_80045C48(Object *obj, Object_Racer *racer, s32 updateRate) {
    s32 overrideMagnitude;
    f32 x;
    f32 y;
    f32 z;
    f32 xDerivative;
    f32 yDerivative;
    f32 zDerivative;
    CheckpointNode *checkpoint;
    f32 splineX[5];
    f32 splineY[5];
    f32 splineZ[5];
    f32 temp_f0;
    f32 temp_f0_3;
    f32 temp_f20_2;
    f32 magnitude;
    s16 temp_a1;
    s16 temp_s0;
    s16 temp_t5;
    s16 temp_v0_3;
    s16 temp_v0_5;
    s32 temp_a0;
    s32 temp_s0_2;
    s32 splineEnd;
    s32 var_a0;
    s32 var_a0_2;
    s32 splinePos;
    s32 i;
    s32 var_v0;
    s32 var_v1_2;
    s32 var_v1_4;

    gCurrentRacerInput = 0;
    gCurrentButtonsPressed = 0;
    gCurrentButtonsReleased = 0;
    gCurrentStickX = 0;
    gCurrentStickY = 0;
    splineEnd = get_checkpoint_count();
    if (splineEnd == 0) {
        gCurrentStickX = 25;
        return;
    }
    overrideMagnitude = FALSE;
    magnitude = 1.0 - racer->checkpoint_distance;
    splinePos = racer->checkpoint - 2;
    if (magnitude < 0.0) {
        magnitude = 0.0f;
    }
    if (magnitude > 1.0) {
        magnitude = 1.0f;
    }
    if (splinePos < 0) {
        splinePos += splineEnd;
    }
    if (splinePos >= splineEnd) {
        splinePos -= splineEnd;
    }
    for (i = 0; i < 5; i++) {
        checkpoint = find_next_checkpoint_node(splinePos, racer->unk1C8);
        splineX[i] = checkpoint->x;
        splineY[i] = checkpoint->y;
        splineZ[i] = checkpoint->z;
        splinePos++;
        if (racer->unk1C9 == 0) {
            checkpoint[i + 1].unk24 = (f32) checkpoint->unk2E[racer->unk1CA];
            checkpoint[i + 2].unk24 = (f32) checkpoint->unk32[racer->unk1CA];
            //(sp + i)->unk74 = (f32) checkpoint->unk2E[racer->unk1CA];
            //(sp + i)->unk64 = (f32) checkpoint->unk32[racer->unk1CA];
            splineX[i] += checkpoint->scale * checkpoint->rotationZFrac * (f32) checkpoint->unk2E[racer->unk1CA];
            splineY[i] += checkpoint->scale * (f32) checkpoint->unk32[racer->unk1CA];
            splineZ[i] += checkpoint->scale * -checkpoint->rotationXFrac * (f32) checkpoint->unk2E[racer->unk1CA];
        }
        if (splinePos == splineEnd) {
            splinePos = 0;
        }
    }
    if (racer->unk1C9 == 0) {
        racer->unk1BA = magnitude; //(s16) (s32) (((sp7C - sp78) * var_f20) + sp78);
        racer->unk1BC = magnitude; //(s16) (s32) (((sp6C - sp68) * var_f20) + sp68);
    }
    xDerivative = catmull_rom_derivative(splineX, 0, magnitude);
    yDerivative = catmull_rom_derivative(splineY, 0, magnitude);
    zDerivative = catmull_rom_derivative(splineZ, 0, magnitude);
    temp_f0 = sqrtf((xDerivative * xDerivative) + (yDerivative * yDerivative) + (zDerivative * zDerivative));
    if (temp_f0 != 0.0f) {
        temp_f0 = 100.0f / temp_f0;
        xDerivative *= temp_f0;
        yDerivative *= temp_f0;
        zDerivative *= temp_f0;
    }
    temp_s0 = arctan2_f(xDerivative, zDerivative) - 0x8000;
    temp_v0_3 = arctan2_f(yDerivative, 100.0f);
    racer->unk1C2 = racer->unk1BE;
    temp_a1 = temp_v0_3 & 0xFFFF;
    temp_t5 = racer->unk1C0;
    racer->unk1BE = temp_s0;
    racer->unk1C0 = temp_a1;
    racer->unk1C4 = temp_t5;
    var_a0 = temp_s0 - (racer->unk1C2 & 0xFFFF);
    if (var_a0 > 0x8000) {
        var_a0 -= 0xFFFF;
    }
    if (var_a0 < -0x8000) {
        var_a0 += 0xFFFF;
    }
    var_v1_2 = temp_a1 - (racer->unk1C4 & 0xFFFF);
    if (var_v1_2 > 0x8000) {
        var_v1_2 -= 0xFFFF;
    }
    if (var_v1_2 < -0x8000) {
        var_v1_2 += 0xFFFF;
    }
    gCurrentStickX = -(var_a0 >> 3);
    gCurrentStickY = -(var_v1_2 >> 3);
    var_a0_2 = temp_s0 - (racer->steerVisualRotation & 0xFFFF);
    if (var_a0_2 > 0x8000) {
        var_a0_2 -= 0xFFFF;
    }
    if (var_a0_2 < -0x8000) {
        var_a0_2 += 0xFFFF;
    }
    if (var_a0_2 > 0x3000 || var_a0_2 < -0x3000) {
        overrideMagnitude = TRUE;
    }
    magnitude = 1.0 - racer->checkpoint_distance;
    splinePos = racer->checkpoint - 2;
    if (magnitude < 0.0) {
        magnitude = 0.0f;
    }
    if (magnitude > 1.0) {
        magnitude = 1.0f;
    }
    if (overrideMagnitude) {
        magnitude = 1.0f;
    }
    if (racer->unk1C9 != 0) {
        if (splinePos < 0) {
            splinePos += splineEnd;
        }
        if (splinePos >= splineEnd) {
            splinePos -= splineEnd;
        }
        for (i = 0; i < 5; i++) {
            checkpoint = find_next_checkpoint_node(splinePos, racer->unk1C8);
            splineX[i] = (checkpoint->x + (checkpoint->scale * checkpoint->rotationZFrac * racer->unk1BA));
            splineY[i] = (checkpoint->y + (checkpoint->scale * racer->unk1BC));
            splineZ[i] = (checkpoint->z + (checkpoint->scale * -checkpoint->rotationXFrac * racer->unk1BA));
            splinePos++;
            if (splinePos == splineEnd) {
                splinePos = 0;
            }
        }
    }
    x = cubic_spline_interpolation(splineX, 0, magnitude, &xDerivative);
    y = cubic_spline_interpolation(splineY, 0, magnitude, &yDerivative);
    z = cubic_spline_interpolation(splineZ, 0, magnitude, &zDerivative);
    temp_f0_3 = sqrtf((xDerivative * xDerivative) + (yDerivative * yDerivative) + (zDerivative * zDerivative));
    if (temp_f0_3 != 0.0f) {
        temp_f20_2 = 500.0f / temp_f0_3;
        xDerivative *= temp_f20_2;
        yDerivative *= temp_f20_2;
        zDerivative *= temp_f20_2;
    }
    xDerivative = (x + xDerivative) - obj->segment.trans.x_position;
    yDerivative = (y + yDerivative) - obj->segment.trans.y_position;
    zDerivative = (z + zDerivative) - obj->segment.trans.z_position;
    temp_s0_2 = (arctan2_f(xDerivative, zDerivative) - 0x8000) & 0xFFFF;
    temp_v0_5 = arctan2_f(yDerivative, 500.0f);
    temp_a0 = temp_s0_2 - (racer->steerVisualRotation & 0xFFFF);
    if (temp_a0 > 0x8000) {
        temp_a0 -= 0xFFFF;
    }
    if (temp_a0 < -0x8000) {
        temp_a0 += 0xFFFF;
    }
    temp_a0 = -temp_a0;
    var_v1_4 = (temp_v0_5 & 0xFFFF) - (obj->segment.trans.rotation.x_rotation & 0xFFFF);
    if (var_v1_4 > 0x8000) {
        var_v1_4 -= 0xFFFF;
    }
    var_v0 = 5;
    if (var_v1_4 < -0x8000) {
        var_v1_4 += 0xFFFF;
    }
    var_v1_4 = -var_v1_4;
    if (racer->vehicleID == VEHICLE_PLANE) {
        var_v0 = 6;
    }
    if (racer->vehicleID == VEHICLE_HOVERCRAFT && racer->unk1D4 == 0) {
        racer->steerVisualRotation = racer->steerVisualRotation - (temp_a0 >> 1);
    }
    switch (racer->vehicleID) {
        case VEHICLE_LOOPDELOOP:
            gCurrentStickY = 0;
            break;
        case VEHICLE_HOVERCRAFT:
            gCurrentStickY = 0;
            gCurrentStickX += temp_a0 >> var_v0;
            break;
        case VEHICLE_TRICKY:
            gCurrentStickX += temp_a0 >> (var_v0 + 0x1F);
            gCurrentStickY = 0;
            break;
        case VEHICLE_SMOKEY:
            gCurrentStickX += temp_a0 >> (var_v0 - 1);
            gCurrentStickY += var_v1_4 >> (var_v0 - 1);
            break;
        default:
            gCurrentStickX += temp_a0 >> var_v0;
            gCurrentStickY += var_v1_4 >> var_v0;
            break;
    }
    func_80042D20(obj, racer, updateRate);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/racer/func_80045C48.s")
#endif

void func_80046524(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer) {
    s32 objectMoved;
    UNUSED s32 pad1;
    f32 sp11C;
    f32 waterHeight;
    f32 velocity;
    f32 xPos;
    f32 yPos;
    f32 zPos;
    f32 xVelTemp;
    f32 zVelTemp;
    f32 spFC;
    UNUSED s32 pad2;
    f32 spF4;
    f32 spF0;
    f32 temp;
    f32 racerOx1;
    f32 racerOz1;
    f32 var_f0;
    Vec3f water_rotation;
    f32 var_f2;
    s32 var_v0;
    f32 spC8;
    s32 iTemp; // Seems to be reused for some reason
    s32 var_a3;
    s32 var_v1;
    Unknown80046524 *temp_v0_16;
    s32 var_t0;
    Object_Boost *asset20;
    s8 lastWheelSurface;
    s8 wave_properties;
    s8 wheelsOnStone;
    UNUSED s32 pad3;
    MtxF transformedMtx;
    s8 playerObjectHasMoved;
    f32 var_f6;

    if (func_8000E138()) {
        updateRateF *= 1.15;
    }
    playerObjectHasMoved = FALSE;
    if (racer->playerIndex >= PLAYER_ONE && gNumViewports < 2) {
        obj->particleEmittersEnabled |= OBJ_EMIT_9;
    }
    D_8011D550 = 0;
    gCurrentCarSteerVel = 0;
    D_8011D558 = 0;
    xPos = obj->segment.trans.x_position;
    yPos = obj->segment.trans.y_position;
    zPos = obj->segment.trans.z_position;
    spC8 = 1.0 - (gDialogueCameraAngle / 10240.0f);
    racerOx1 = -racer->ox1 * 10 * spC8;
    racerOz1 = -racer->oz1 * 10 * spC8;
    var_f2 = 8.0f;
    if (gCurrentPlayerIndex == PLAYER_COMPUTER || racer->raceFinished) {
        var_f2 = 32.0f;
    }
    var_v1 = gCurrentStickX - racer->steerAngle;
    var_a3 = (var_v1 * updateRateF) / var_f2;
    if ((var_v1 != 0) && (var_a3 == 0)) {
        if (var_v1 > 0) {
            var_a3 = 1;
        }
        if (var_v1 < 0) {
            var_a3 = -1;
        }
    }
    racer->steerAngle += var_a3;
    handle_racer_items(obj, racer, updateRate);
    func_800535C4(obj, racer);
    racer_attack_handler_hovercraft(obj, racer);
    if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
        handle_racer_head_turning(obj, racer, updateRate);
    } else {
        slowly_reset_head_angle(racer);
    }
    if (gCurrentRacerInput & A_BUTTON) {
        racer->throttle += updateRateF * 0.016;
        if (racer->throttle > 1.0) {
            racer->throttle = 1.0;
        }
    } else {
        racer->throttle -= updateRateF * 0.016;
        if (racer->throttle < 0.0f) {
            racer->throttle = 0.0f;
        }
    }
    sp11C = racer->throttle;
    if ((racer->velocity > 0.0f) && (gCurrentRacerInput & A_BUTTON)) {
        sp11C = 1.0f;
    }
    sp11C *= 3.0f;
    spF4 = (sp11C * sp11C) / 9.0f;
    if (racer->exitObj != NULL) {
        racer->throttle = 0.5f;
    }
    if (racer->velocity > 0.0) {
        spF4 *= 1.2;
    }
    if ((gCurrentRacerInput & B_BUTTON) && (gCurrentStickY < -40 || racer->velocity < 0.0f)) {
        racer->brake += updateRateF * 0.046;
        if (racer->brake > 1.2) {
            racer->brake = 1.2f;
        }
        if (racer->velocity < -2.0) {
            rumble_set(racer->playerIndex, RUMBLE_TYPE_5);
        }
    } else {
        racer->brake -= updateRateF * 0.046;
        if (racer->brake < 0.0f) {
            racer->brake = 0.0f;
        }
    }
    sp11C = racer->brake * 3.0f;
    spF0 = sp11C * sp11C / 9.0f;
    if (racer->velocity > 0.0) {
        spF0 *= 0.3;
    }

    if (racer->zipperDirCorrection != 0) {
        gCurrentStickX = 0;
        racer->magnetTimer = 0;
        racer->steerAngle = 0;
        racer->spinout_timer = 0;
        racer->trickType = 0;
        var_v1 = racer->zipperObj->segment.trans.rotation.y_rotation - (racer->steerVisualRotation & 0xFFFF);
        if (var_v1 > 0x8000) {
            var_v1 -= 0xFFFF;
        }
        if (var_v1 < -0x8000) {
            var_v1 += 0xFFFF;
        }
        racer->steerVisualRotation += (var_v1 * updateRate) >> 3;
        if ((var_v1 < 0x400 && var_v1 > -0x400) || (racer->playerIndex == PLAYER_COMPUTER)) {
            if (racer->playerIndex != PLAYER_COMPUTER) {
                sound_play_spatial(SOUND_ZIP_PAD_BOOST, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                   obj->segment.trans.z_position, NULL);
                play_random_character_voice(obj, SOUND_VOICE_CHARACTER_POSITIVE, 8, 0x80 | 0x2);
            }
            racer->boostTimer = normalise_time(45);
            racer->boostType = BOOST_LARGE;
            if (racer->throttleReleased) {
                racer->boostType |= BOOST_SMALL_FAST;
            }
            racer->zipperDirCorrection = 0;
            rumble_set(racer->playerIndex, RUMBLE_TYPE_8);
        } else {
            obj->segment.x_velocity = (obj->segment.x_velocity * 1.0) * 0.75f;
            obj->segment.y_velocity = (obj->segment.y_velocity * 1.0) * 0.75f;
            obj->segment.z_velocity = (obj->segment.z_velocity * 1.0) * 0.75f;
        }
    }
    var_f2 = -racer->velocity;
    if (var_f2 < 0.0f) {
        var_f2 = 0.0f;
    }
    if (var_f2 > 14.0) {
        var_f2 = 14.0f;
    }
    var_f2 /= 14.0f;
    if (racer->unk1D4 != 0 || racer->unk1D5 != 0) {
        apply_vehicle_rotation_offset(racer, updateRate, racer->y_rotation_offset, 0, 0);
    } else {
        apply_vehicle_rotation_offset(racer, updateRate, 0, (spF0 * 4096.0f) * var_f2, 0);
    }
    if (racer->unk1D5 != 0) {
        racer->y_rotation_offset -= racer->y_rotation_offset >> 3;
        if (racer->y_rotation_offset < 16 && racer->y_rotation_offset > -16) {
            racer->unk1D5 = 0;
        }
        gCurrentStickX = 0;
    }
    if (racer->spinout_timer > 0) {
        racer->unk1D4 += updateRate;
        if (racer->unk1D4 > 10) {
            racer->unk1D4 = 10;
        }
    } else if (racer->spinout_timer < 0) {
        racer->unk1D4 -= updateRate;
        if (racer->unk1D4 < -10) {
            racer->unk1D4 = -10;
        }
    } else if (racer->unk1D4 < 0) {
        racer->unk1D4 += updateRate;
        if (racer->unk1D4 > 0) {
            racer->unk1D4 = 0;
            racer->unk1D5 = 1;
        }
    } else if (racer->unk1D4 > 0) {
        racer->unk1D4 -= updateRate;
        if (racer->unk1D4 < 0) {
            racer->unk1D4 = 0;
            racer->unk1D5 = 1;
        }
    }
    if (racer->groundedWheels && racer->groundedWheels < 3) {
        obj->segment.trans.rotation.x_rotation -= (obj->segment.trans.rotation.x_rotation * updateRate) >> 6;
        racer->x_rotation_vel -= (racer->x_rotation_vel * updateRate) >> 6;
    }
    if (racer->unk1D4 != 0) {
        iTemp = racer->y_rotation_offset;
        racer->unk1D5 = 0;
        if (racer->unk1D4 > 0) {
            racer->y_rotation_offset += (racer->unk1D4 * (180 - 1)) * updateRate;
            if (iTemp < -0x1000 && racer->y_rotation_offset >= -0x1000) {
                racer->spinout_timer--;
            }
        }
        if (racer->unk1D4 < 0) {
            racer->y_rotation_offset -= (racer->unk1D4 * (180 - 1)) * updateRate;
            if (iTemp > 0x1000 && racer->y_rotation_offset <= 0x1000) {
                racer->spinout_timer++;
            }
        }
        gCurrentRacerInput &= ~(A_BUTTON | B_BUTTON);
        gCurrentStickX = 0;
        racer->steerAngle = 0;
        gCurrentStickY = 0;
    }
    if (racer->unk1F1 != 0) {
        racer->y_rotation_offset += updateRate * 0x500;
        racer->x_rotation_offset += updateRate * 0x600;
    }
    gCurrentRacerTransform.rotation.y_rotation = obj->segment.trans.rotation.y_rotation;
    gCurrentRacerTransform.rotation.x_rotation = obj->segment.trans.rotation.x_rotation;
    gCurrentRacerTransform.rotation.z_rotation = 0;
    gCurrentRacerTransform.x_position = 0.0f;
    gCurrentRacerTransform.y_position = 0.0f;
    gCurrentRacerTransform.z_position = 0.0f;
    gCurrentRacerTransform.scale = 1.0f;
    mtxf_from_transform(&transformedMtx, &gCurrentRacerTransform);
    mtxf_transform_point(&transformedMtx, 0.0f, 0.0f, 1.0f, &racer->ox1, &racer->oy1, &racer->oz1);
    mtxf_transform_point(&transformedMtx, 0.0f, 1.0f, 0.0f, &racer->ox2, &racer->oy2, &racer->oz2);
    mtxf_transform_point(&transformedMtx, 1.0f, 0.0f, 0.0f, &racer->ox3, &racer->oy3, &racer->oz3);
    if (racer->approachTarget == NULL) {
        obj->segment.object.animationID = 0;
        var_v0 = racer->steerAngle;
        var_v0 >>= 1;
        var_v0 = 40 - var_v0;
        if (var_v0 < 0) {
            var_v0 = 0;
        }
        if (var_v0 > 73) {
            var_v0 = 73;
        }
        obj->segment.animFrame = var_v0;
    }
    xVelTemp = racer->velocity;
    if (xVelTemp < 0.0f) {
        xVelTemp = -xVelTemp;
    }
    lastWheelSurface = SURFACE_DEFAULT;
    wheelsOnStone = 0;
    if (xVelTemp > 12.0f) {
        xVelTemp = 12.0f;
    }
    var_v0 = xVelTemp;
    var_f0 = xVelTemp - var_v0;
    xVelTemp = (gCurrentRacerMiscAssetPtr[var_v0 + 1] * var_f0) + (gCurrentRacerMiscAssetPtr[var_v0] * (1.0 - var_f0));
    gCurrentRacerWeightStat *= 0.75;
    if (racer->groundedWheels >= 3) {
        obj->segment.y_velocity -= gCurrentRacerWeightStat * 0.5 * updateRateF;
    } else {
        obj->segment.y_velocity -= gCurrentRacerWeightStat * updateRateF;
    }
    iTemp = (gCurrentPlayerIndex != PLAYER_COMPUTER && !racer->raceFinished) ? racer->steerAngle : gCurrentStickX;
    spFC = 0.004;
    obj->segment.y_velocity -= (obj->segment.y_velocity * 0.025) * updateRateF;
    if (gCurrentRacerInput & B_BUTTON && gCurrentStickY >= -40 && racer->velocity >= -0.5) {
        spFC *= 16.0f;
    }
    velocity = (iTemp * 8) * updateRate;
    if (gCurrentStickY < 0) {
        temp = -gCurrentStickY;
        velocity *= 1.0 + (temp / 112.0);
        xVelTemp *= 1.0 - (temp / 300.0);
    }
    velocity *= gCurrentRacerHandlingStat;
    racer->steerVisualRotation -= (((s32) velocity) & 0xffff) & 0xffff;
    if (racer->groundedWheels == 0 && racer->buoyancy == 0.0) {
        if (obj->segment.y_velocity < 0.0f) {
            racer->trickType += updateRate;
        }
        if (racer->trickType > 25) {
            racer->trickType = 25;
        }
    }

    for (iTemp = 0; iTemp < 4; iTemp++) {
        if (racer->wheel_surfaces[iTemp] == SURFACE_NONE) {
            continue;
        }
        if (lastWheelSurface < racer->wheel_surfaces[iTemp]) {
            lastWheelSurface = racer->wheel_surfaces[iTemp];
        }
        if (racer->wheel_surfaces[iTemp] == SURFACE_STONE) {
            wheelsOnStone++;
        }
    }

    if (racer->playerIndex == PLAYER_ONE && racer->groundedWheels && lastWheelSurface == SURFACE_TAJ_PAD &&
        gCurrentButtonsPressed & Z_TRIG) {
        gTajInteractStatus = TAJ_TELEPORT;
    }
    if (racer->groundedWheels || racer->buoyancy > 0.0f) {
        if (racer->trickType != 0) {
            if (racer->groundedWheels) {
                if (gRaceStartTimer != 100 && racer->playerIndex != PLAYER_COMPUTER && racer->trickType >= 6) {
                    sound_play(SOUND_BOUNCE, &racer->unk21C);
                    sound_volume_set_relative(SOUND_BOUNCE, racer->unk21C, (racer->trickType * 2) + 50);
                }
            } else if (racer->approachTarget == NULL) {
                racer_play_sound(obj, SOUND_UNK_AF);
                obj->particleEmittersEnabled |= OBJ_EMIT_5 | OBJ_EMIT_6;
            }
            var_f2 = racer->trickType;
            var_f2 -= 5.0f;
            if (var_f2 > 0.0f && racer->approachTarget == NULL) {
                racer->stretch_height_cap = 1.0 - (var_f2 * 0.02);
            }
            racer->trickType = 0;
        }
    }
    xVelTemp *= handle_racer_top_speed(obj, racer) * 1.7;
    if (racer->boostTimer > 0) {
        if (gRaceStartTimer == 0) {
            spF4 = 1.0f;
            spF0 = 0.0f;
            if (xVelTemp != 0.0) {
                xVelTemp = 2.0f;
            }
            racer->boostTimer -= updateRate;
        }
    } else {
        racer->boostTimer = 0;
    }
    if (gRaceStartTimer != 0) {
        xVelTemp = 0.0f;
    }
    if (wheelsOnStone != 0) {
        var_f0 = ((f32 *) get_misc_asset(ASSET_MISC_32))[wheelsOnStone];
        xVelTemp *= var_f0;
        spFC /= var_f0;
        racer->magnetTimer = 0;
        racer->lateral_velocity = 0.0f;
    }
    if ((racer->boostTimer == 0) && (lastWheelSurface == 3)) {
        racer->boostTimer = normalise_time(45);
        racer->boostType = BOOST_LARGE;
        if (racer->throttleReleased) {
            racer->boostType |= BOOST_SMALL_FAST;
        }
        racer_play_sound(obj, SOUND_ZIP_PAD_BOOST);
        play_random_character_voice(obj, SOUND_VOICE_CHARACTER_POSITIVE, 8, 0x80 | 0x2);
        rumble_set(racer->playerIndex, RUMBLE_TYPE_8);
    }

    var_f2 = sqrtf((obj->segment.z_velocity * obj->segment.z_velocity) +
                   (obj->segment.x_velocity * obj->segment.x_velocity));
    if (var_f2 > 0.25) {
        racer->unk168 = arctan2_f(obj->segment.x_velocity, obj->segment.z_velocity) + 0x8000;
        var_v1 = ((0x8000 - racer->unk168) & 0xFFFF) - (racer->cameraYaw & 0xFFFF);
        if (var_v1 > 0x8000) {
            var_v1 -= 0xFFFF;
        }
        if (var_v1 < -0x8000) {
            var_v1 += 0xFFFF;
        }
        sp11C = var_f2 - 0.25;
        if (sp11C > 8.0) {
            sp11C = 8.0f;
        }
        sp11C *= 0.125;
        var_v1 = (sp11C * var_v1) * 0.75;
        racer->cameraYaw += (var_v1 * updateRate) >> 4;
        var_v1 = (0x8000 - racer->cameraYaw) - (racer->steerVisualRotation & 0xFFFF);
        if (var_v1 > 0x8000) {
            var_v1 -= 0xFFFF;
        }
        if (var_v1 < -0x8000) {
            var_v1 += 0xFFFF;
        }
        if (var_f2 > 10.0) {
            var_f2 = 10.0;
        }

        var_f2 /= 10.0;
        var_v1 *= var_f2;
        if (gCurrentRacerInput & A_BUTTON || gCurrentRacerInput & R_TRIG) {
            var_v1 *= 2;
        }
        racer->steerVisualRotation += ((s32) (var_v1 * updateRate)) >> 7;
    }
    var_v1 = (0x8000 - racer->steerVisualRotation) - (racer->cameraYaw & 0xFFFF);
    if (var_v1 > 0x8000) {
        var_v1 -= 0xFFFF;
    }
    if (var_v1 < -0x8000) {
        var_v1 += 0xFFFF;
    }
    var_f6 = 1.0f;
    var_v1 = ((s32) ((((f32) var_v1) * 1.75) * var_f6));
    var_t0 = (var_v1 * updateRate);
    racer->cameraYaw += var_t0 >> 6;
    if (racer->zipperDirCorrection == 0) {
        if (gCurrentPlayerIndex == PLAYER_COMPUTER && !racer->raceFinished) {
            temp = racer->lateral_velocity * 0.25;
            zVelTemp = temp * 0.35;
            if (zVelTemp < 0.0) {
                zVelTemp = -zVelTemp;
            }
            if (0.2 < zVelTemp) {
                gCurrentRacerInput |= R_TRIG;
            }
            obj->segment.x_velocity += racer->ox1 * zVelTemp;
            obj->segment.y_velocity += racer->oy1 * zVelTemp;
            obj->segment.z_velocity += racer->oz1 * zVelTemp;
        } else {
            temp = racer->lateral_velocity * 0.07;
            if (gCurrentRacerInput & R_TRIG) {
                temp *= 2;
                if (gCurrentStickX > -40 && gCurrentStickX < 40) {
                    spF4 *= 0.8;
                } else if (racer->lateral_velocity > 2.5 || racer->lateral_velocity < -2.5) {
                    spF4 *= 1.5;
                }
                if (gCurrentRacerInput & B_BUTTON) {
                    temp *= 2;
                }
            }
            if (gCurrentRacerInput) {}
        }
        obj->segment.x_velocity -= racer->ox3 * temp;
        obj->segment.y_velocity -= racer->oy3 * temp;
        obj->segment.z_velocity -= racer->oz3 * temp;
        spF4 *= xVelTemp;
        obj->segment.x_velocity -= racer->ox1 * spF4;
        obj->segment.y_velocity -= racer->oy1 * spF4;
        obj->segment.z_velocity -= racer->oz1 * spF4;
        spF0 *= xVelTemp / 2;
        obj->segment.x_velocity += racer->ox1 * spF0;
        obj->segment.y_velocity += racer->oy1 * spF0;
        obj->segment.z_velocity += racer->oz1 * spF0;
        if (racer->groundedWheels && !gRacerInputBlocked && gRaceStartTimer == 0) {
            var_f2 = (gCurrentRacerWeightStat * updateRateF) * 0.25;
            sp11C = racer->pitch * var_f2;
            var_f2 *= racer->roll;
            obj->segment.x_velocity += (racer->ox1 * sp11C) + (racer->ox3 * var_f2);
            obj->segment.y_velocity += (racer->oy1 * sp11C) + (racer->oy3 * var_f2);
            obj->segment.z_velocity += (racer->oz1 * sp11C) + (racer->oz3 * var_f2);
        }
        zVelTemp = racer->velocity * racer->velocity;
        if (racer->velocity < 0.0f) {
            zVelTemp = -zVelTemp;
        }
        if (zVelTemp < 1.0f && (!(gCurrentRacerInput & A_BUTTON))) {
            temp = racer->velocity * spFC * 8.0f;
        } else {
            temp = zVelTemp * spFC;
        }
        obj->segment.x_velocity -= racer->ox1 * temp;
        obj->segment.y_velocity -= racer->oy1 * temp;
        obj->segment.z_velocity -= racer->oz1 * temp;
        if (racer->magnetTimer != 0) {
            obj->segment.x_velocity = gRacerMagnetVelX;
            obj->segment.z_velocity = gRacerMagnetVelZ;
        }
    }
    racer->unk10C = 0;
    racer->y_rotation_vel += (gCurrentCarSteerVel - racer->y_rotation_vel) >> 3;
    obj->segment.trans.rotation.y_rotation = racer->steerVisualRotation + racer->y_rotation_vel;
    racer->z_rotation_vel += (D_8011D558 - racer->z_rotation_vel) >> 3;
    obj->segment.trans.rotation.z_rotation = racer->x_rotation_vel + racer->z_rotation_vel;
    if (racer->unk1D2 > 0) {
        racer->unk1D2 -= updateRate;
    } else {
        racer->unk1D2 = 0;
    }
    racerOx1 += racer->ox1 * 10 * spC8;
    racerOz1 += racer->oz1 * 10 * spC8;
    if (racer->approachTarget == NULL) {
        temp = obj->segment.x_velocity;
        zVelTemp = obj->segment.z_velocity;
        if (racer->unk1D2 != 0) {
            temp += racer->unk11C;
            zVelTemp += racer->unk120;
        }
        if (gRacerInputBlocked) {
            if (temp > 0.5 || temp < -0.5) {
                temp *= 0.65;
            } else {
                temp = 0.0f;
            }
            if (zVelTemp > 0.5 || zVelTemp < -0.5) {
                zVelTemp *= 0.65;
            } else {
                zVelTemp = 0.0f;
            }
        } else {
            racerOx1 += racer->unk84 * updateRateF;
            racerOz1 += racer->unk88 * updateRateF;
        }

        objectMoved = move_object(obj, (temp * updateRateF) + racerOx1, obj->segment.y_velocity * updateRateF,
                                  (zVelTemp * updateRateF) + racerOz1);

        if (objectMoved && gCurrentPlayerIndex != PLAYER_COMPUTER) {
            playerObjectHasMoved = TRUE;
        }
    } else {
        racerOx1 = 0.0;
        racerOz1 = 0.0;
        racer_approach_object(obj, racer, updateRateF);
    }
    racer->unkD0 -= (racer->unkD0 * 0.125) * updateRateF;
    racer->unkD4 = (-obj->segment.y_velocity) * 7.0;
    if (racer->unkD4 > 35.0) {
        racer->unkD4 = 35.0;
    }
    if (racer->unkD4 < 0.0) {
        racer->unkD4 = 0;
    }
    velocity = 5.0f;
    waterHeight = -10000.0f;
    // clang-format off
    // the backslash here is relevant for the match
    wave_properties = get_wave_properties(obj->segment.trans.y_position, &waterHeight, &water_rotation); \
    if (wave_properties != 0) {
        // clang-format on
        velocity = racer->velocity;
        if (velocity < 0.0f) {
            velocity = -velocity;
        }
        if (velocity > 4.0) {
            velocity = 4.0f;
        }
        velocity *= 0.8;
        if ((obj->segment.trans.y_position - velocity) < waterHeight) {
            racer->buoyancy = waterHeight - (obj->segment.trans.y_position - velocity);
            racer->waterTimer = 5;
        } else {
            racer->buoyancy = 0.0f;
        }
    }
    if (racer->waterTimer > 0) {
        racer->waterTimer--;
    } else {
        racer->buoyancy = 0.0f;
    }
    if (racer->waterTimer > 0 && obj->segment.trans.y_position < (waterHeight + velocity)) {
        obj->interactObj->flags |= INTERACT_FLAGS_UNK_0010;
    } else {
        obj->interactObj->flags &= ~INTERACT_FLAGS_UNK_0010;
    }
    waterHeight = obj->segment.trans.y_position - (waterHeight + velocity);
    if (racer->buoyancy > 0.0) {
        iTemp = 0;
        if (gCurrentRacerInput & R_TRIG) {
            iTemp = gCurrentStickX * 2;
        }
        rotate_racer_in_water(obj, racer, &water_rotation, wave_properties, updateRate, iTemp, 1.0f);
    }
    if (racer->buoyancy > 0.0) {
        obj->segment.trans.y_position += racer->buoyancy * racer->unkC4;
        racer->unkC4 += (0.75 - racer->unkC4) * 0.125;
    }

    iTemp = racer->unk1D2; // saves unk1D2
    if (gCurrentPlayerIndex == PLAYER_COMPUTER && !func_80023568()) {
        onscreen_ai_racer_physics(obj, racer, updateRate);
    } else {
        func_80054FD0(obj, racer, updateRate);
    }
    if (iTemp == 0 && racer->unk1D2 != 0) {
        iTemp = 1;
    }
    racer->unk1D2 = iTemp; // restores unk1D2

    var_f2 = 1.0f / updateRateF;
    temp = ((obj->segment.trans.x_position - (xPos + racerOx1)) - D_8011D548) * var_f2;
    zVelTemp = ((obj->segment.trans.z_position - (zPos + racerOz1)) - D_8011D54C) * var_f2;
    obj->segment.z_velocity = zVelTemp;
    obj->segment.x_velocity = temp;
    obj->segment.y_velocity = (obj->segment.trans.y_position - yPos) * var_f2;

    racer->forwardVel -= (racer->forwardVel + (racer->velocity * 0.05)) * 0.125;
    if (racer->buoyancy > 0.0 && racer->unk1FB == 0 && obj->segment.y_velocity > 4.0) {
        obj->segment.y_velocity = 4.0f;
    }
    if (gNumViewports < 2 && obj->segment.header->particleCount >= 9) {
        if ((gCurrentRacerInput & (A_BUTTON | R_TRIG)) == (A_BUTTON | R_TRIG) &&
            (gCurrentStickX < -30 || gCurrentStickX > 30)) {
            increase_emitter_opacity(obj, 8, updateRate << 10, 0x80);
        } else {
            decrease_emitter_opacity(obj, 8, updateRate << 9, 0x20);
        }
    }
    if (gCurrentPlayerIndex >= PLAYER_ONE && racer->buoyancy > 0.0) {
        if (gNumViewports < 3) {
            var_f2 = ((obj->segment.x_velocity * obj->segment.x_velocity) +
                      (obj->segment.y_velocity * obj->segment.y_velocity)) +
                     (obj->segment.z_velocity * obj->segment.z_velocity);
            if (var_f2 > 16.0f) {
                if (var_f2 < 80.0f) {
                    obj->particleEmittersEnabled |= OBJ_EMIT_3 | OBJ_EMIT_4;
                }
                if (var_f2 > 28.0f) {
                    obj->particleEmittersEnabled |= OBJ_EMIT_1 | OBJ_EMIT_2;
                }
                if (gNumViewports == 1 && var_f2 > 10.25f) {
                    obj->particleEmittersEnabled |= OBJ_EMIT_7;
                }
            }
        } else {
            if (racer->velocity < 0.0f) {
                var_f2 = -racer->velocity;
            } else {
                var_f2 = racer->velocity;
            }
            if (var_f2 > 4.0f) {
                obj->particleEmittersEnabled |= OBJ_EMIT_3 | OBJ_EMIT_4;
            }
        }
    }
    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->boostTimer == 0 && gNumViewports < 2) {
        asset20 = (Object_Boost *) get_misc_asset(ASSET_MISC_20);
        asset20 = &asset20[racer->racerIndex];
        iTemp = ((racer->boostType & EMPOWER_BOOST) >> 2) + 10;
        if (iTemp > 10) {
            if (asset20->unk70 > 0 || asset20->unk74 > 0.0) {
                obj->particleEmittersEnabled |= 1 << iTemp;
            }
        } else if (asset20->unk70 == 2 && asset20->unk74 < 0.5) {
            obj->particleEmittersEnabled |= 1 << iTemp;
        } else if (asset20->unk70 < 2 && asset20->unk74 > 0.0f) {
            obj->particleEmittersEnabled |= 1 << iTemp;
        }
    }
    if (racer->unk201 == 0) {
        obj->particleEmittersEnabled = OBJ_EMIT_NONE;
    } else {
        obj->segment.y_velocity += updateRate * gCurrentRacerWeightStat;
        update_vehicle_particles(obj, updateRate);
        obj->segment.y_velocity -= updateRate * gCurrentRacerWeightStat;
    }
    gCurrentRacerTransform.rotation.y_rotation = -obj->segment.trans.rotation.y_rotation;
    gCurrentRacerTransform.rotation.x_rotation = -obj->segment.trans.rotation.x_rotation;
    gCurrentRacerTransform.rotation.z_rotation = -obj->segment.trans.rotation.z_rotation;
    gCurrentRacerTransform.scale = 1.0f;
    gCurrentRacerTransform.x_position = 0.0f;
    gCurrentRacerTransform.y_position = 0.0f;
    gCurrentRacerTransform.z_position = 0.0f;
    mtxf_from_inverse_transform(&transformedMtx, &gCurrentRacerTransform);
    mtxf_transform_point(&transformedMtx, obj->segment.x_velocity, obj->segment.y_velocity, obj->segment.z_velocity,
                         &racer->lateral_velocity, (f32 *) &racer->unk34, &racer->velocity);
    if (racer->groundedWheels == 0 && racer->waterTimer == 0) {
        iTemp = (-gCurrentStickY * 0x40) & 0xFFFF;
        var_v1 = iTemp - (obj->segment.trans.rotation.x_rotation & 0xFFFF);
        if (var_v1 > 0x8000) {
            var_v1 -= 0xFFFF;
        }
        if (var_v1 < -0x8000) {
            var_v1 += 0xFFFF;
        }
        obj->segment.trans.rotation.x_rotation += var_v1 >> 2;
        var_v0 = -(racer->x_rotation_vel & 0xFFFF);
        if (var_v0 > 0x8000) {
            var_v0 -= 0xFFFF;
        }
        if (var_v0 < -0x8000) {
            var_v0 += 0xFFFF;
        }
        var_v0 *= updateRate;
        racer->x_rotation_vel += var_v0 >> 4;
    }
    if (gRaceStartTimer != 0) {
        gCurrentButtonsPressed &= ~R_TRIG;
    }
    if (racer->buoyancy != 0.0f || racer->groundedWheels == 4) {
        racer->unk1FB = 0;
    }
    if (gCurrentButtonsPressed & R_TRIG && (racer->buoyancy > 0.0f || racer->groundedWheels >= 2) &&
        racer->unk1FB == 0) {
        if (racer->buoyancy != 0.0f) {
            obj->segment.y_velocity += 4.5;
            if (obj->segment.y_velocity > 5.5) {
                obj->segment.y_velocity = 5.5f;
            }
        } else {
            obj->segment.y_velocity += 3.5;
        }
        var_f2 = ((2.0 * obj->segment.y_velocity) / gCurrentRacerWeightStat);
        racer->unk1FB = (s32) (var_f2) + 1;
    }
    if (racer->unk1FB > 0) {
        racer->unk1FB -= updateRate;
    } else {
        racer->unk1FB = 0;
    }
    if (waterHeight > 40.0f) {
        racer->unkC4 = 0.11f;
    }
    if (obj->unk60->unk0 == 1) {
        temp_v0_16 = (Unknown80046524 *) obj->unk60->unk4[0];
        temp_v0_16->unk0 = (gCurrentStickX * 20) + 0x4000;
        temp_v0_16->unk3A++;
        temp_v0_16->unk3A &= 1;
    }
    second_racer_camera_update(obj, racer, CAMERA_HOVERCRAFT, updateRateF);
    if (playerObjectHasMoved) {
        func_800230D0(obj, racer);
    }
}

/**
 * Initialise some states when a racer is attacked or runs into something.
 * While the majority of the respondent behaviour takes place elsewhere, the squish behaviour happens here.
 * Hovercraft do not have a spinning state, instead being in the same state when hit by a rocket.
 */
void racer_attack_handler_hovercraft(Object *obj, Object_Racer *racer) {
    s8 bananas;

    if (racer->playerIndex == PLAYER_COMPUTER) {
        bananas = 0;
    } else {
        bananas = racer->bananas;
    }
    if (racer->attackType == ATTACK_NONE || racer->shieldTimer > 0) {
        racer->attackType = ATTACK_NONE;
        return;
    }
    if (racer->attackType != ATTACK_SQUISHED) {
        drop_bananas(obj, racer, 2);
    }
    play_random_character_voice(obj, SOUND_VOICE_CHARACTER_NEGATIVE, 8, 129);
    switch (racer->attackType) {
        // Getting hit by a rocket, running into a landmine or an oil slick.
        case ATTACK_EXPLOSION:
        case ATTACK_SPIN:
            racer->unk1F1 = 1;
            if (bananas == 0) {
                obj->segment.x_velocity = 0.0f;
                obj->segment.z_velocity = 0.0f;
                obj->segment.y_velocity = 8.0f;
            } else {
                obj->segment.x_velocity = obj->segment.x_velocity * 0.5;
                obj->segment.z_velocity = obj->segment.z_velocity * 0.5;
                obj->segment.y_velocity = 6.0f;
            }
            break;
        // Crushed by something big, like a snowball.
        case ATTACK_SQUISHED:
            racer->squish_timer = 60;
            break;
        // Running into a bubble trap.
        case ATTACK_BUBBLE:
            racer->bubbleTrapTimer = 120;
            obj->segment.x_velocity *= 0.7;
            if (obj->segment.y_velocity > 2.0f) {
                obj->segment.y_velocity = 2.0f;
            }
            obj->segment.z_velocity *= 0.7;
            break;
        // This goes unused.
        case ATTACK_FLUNG:
            racer->unk1F1 = 1;
            racer->velocity = 0.0f;
            obj->segment.y_velocity += 20.5;
            racer_play_sound(obj, SOUND_WHEE);
            break;
    }
    racer->attackType = ATTACK_NONE;
}

/**
 * Handles the camera movement when the player is driving a hovercraft.
 * Since the hovercraft has very floaty controls, the camera movement is much slower to compensate.
 */
void update_camera_hovercraft(f32 updateRate, Object *obj, Object_Racer *racer) {
    f32 yVel;
    s32 numViewports;
    u8 tempZoom;
    UNUSED s32 pad[2];
    f32 phi_f14;
    f32 phi_f18;
    f32 xVel;
    f32 zVel;
    UNUSED s32 pad2;
    f32 sp34;
    UNUSED s32 pad3;
    f32 brakeVar;
    f32 baseSpeed;
    s32 sp24 = 0x400;
    s32 tempUpdateRate;
    s32 angle;
    s32 segmentIndex;
    s32 tempAngle;

    phi_f14 = 165.0f;
    phi_f18 = 65.0f;
    sp24 = 0x400;
    tempUpdateRate = (s32) updateRate;
    // Place the camera a bit closer with 2+ players to help visibility.
    numViewports = cam_get_viewport_layout();
    if (numViewports == 1) {
        phi_f14 = 200.0f;
        phi_f18 = 51.0f;
        sp24 = 0x280;
    } else if (numViewports > 1) {
        phi_f14 = 130.0f;
        phi_f18 = 50.0f;
    }
    brakeVar = racer->brake;
    tempZoom = gCameraObject->zoom;
    baseSpeed = racer->forwardVel;
    switch (gCameraObject->zoom) {
        case 1:
            phi_f14 += 35.0f;
            break;
        case 2:
            phi_f14 -= 35.0f;
            phi_f18 -= 10.0f;
            break;
        case 3:
            phi_f14 -= 53.0f;
            phi_f18 -= 5.0f;
            baseSpeed *= 0.250;
            brakeVar = 0.0f;
            break;
    }
    if (racer->unk1E4 == 0) {
        angle = (obj->segment.trans.rotation.x_rotation);
        if (angle > 0) {
            angle -= 0x61C;
            if (angle < 0) {
                angle = 0;
            }
            angle >>= 1;
        } else {
            angle += 0x61C;
            if (angle > tempZoom * 0) {
                angle = 0;
            }
        }
        angle = sp24 - angle;
        tempAngle = angle - (u16) gCameraObject->trans.rotation.x_rotation;
        WRAP(tempAngle, -0x8000, 0x8000);
        gCameraObject->trans.rotation.x_rotation += (tempAngle * tempUpdateRate) >> 4;
    }
    cam_get_viewport_layout();
    if (racer->velocity < 0.0) {
        yVel = -(racer->velocity * brakeVar) * 6.0f;
        if (racer->velocity) {} // Fakematch
        if (yVel > 65.0) {
            yVel = 65.0f;
        }
        phi_f14 -= yVel;
    }
    phi_f14 += baseSpeed * 30.0f;
    if (gRaceStartTimer == 0) {
        if (normalise_time(36) < racer->boostTimer) {
            phi_f14 = -30.0f;
        } else if (racer->boostTimer > 0) {
            phi_f14 = 180.0f;
        }
    }
    if (gRaceStartTimer > 80) {
        gCameraObject->boomLength = phi_f14;
        gCameraObject->cam_unk_20 = phi_f18;
    }
    gCameraObject->boomLength += (phi_f14 - gCameraObject->boomLength) * 0.125; //!@Delta
    gCameraObject->cam_unk_20 += (phi_f18 - gCameraObject->cam_unk_20) * 0.125; //!@Delta
    sp34 = sins_f(gCameraObject->trans.rotation.x_rotation - sp24);
    phi_f18 = coss_f(gCameraObject->trans.rotation.x_rotation - sp24);
    phi_f18 = (gCameraObject->boomLength * sp34) + (gCameraObject->cam_unk_20 * phi_f18);
    xVel = sins_f(-racer->cameraYaw + 0x8000) * gCameraObject->boomLength;
    zVel = coss_f(-racer->cameraYaw + 0x8000) * gCameraObject->boomLength;
    yVel = (1.0 - (gDialogueCameraAngle / 10240.0f)); // Goes between 0-1
    xVel -= racer->ox1 * 10.0f * yVel;
    zVel -= racer->oz1 * 10.0f * yVel;
    yVel = racer->lateral_velocity * 2;
    racer->unkC8 -= (racer->unkC8 - yVel) * 0.25;
    yVel = sins_f(racer->cameraYaw + 0x4000) * racer->unkC8;
    gCameraObject->trans.x_position = obj->segment.trans.x_position + xVel + yVel;
    yVel = gCameraObject->trans.y_position - (obj->segment.trans.y_position + phi_f18);
    if (yVel > 0.0f) {
        yVel *= 0.5;
    } else {
        if (unused_8011D53C == 1) {
            yVel *= 0.5; // Unreachable. unused_8011D53C is never not 0.
        } else {
            yVel *= 0.25;
        }
        if (racer->boostTimer != 0) {
            yVel *= 2.0;
        }
    }
    gCameraObject->trans.y_position -= yVel;
    gCameraObject->trans.rotation.z_rotation = 0;
    if (gRaceStartTimer) {
        gCameraObject->trans.y_position = obj->segment.trans.y_position + phi_f18;
    }

    coss_f(racer->cameraYaw + 0x4000); // Unused function call that wasn't fully optimised out.
    gCameraObject->trans.z_position = obj->segment.trans.z_position + zVel;
    gCameraObject->trans.rotation.y_rotation = racer->cameraYaw;
    segmentIndex = get_level_segment_index_from_position(
        gCameraObject->trans.x_position, gCameraObject->trans.y_position, gCameraObject->trans.z_position);
    if (segmentIndex != SEGMENT_NONE) {
        gCameraObject->cameraSegmentID = segmentIndex;
    }
}

/**
 * When on water, apply a rotation effect based on the movement of the waves and turning direction.
 */
f32 rotate_racer_in_water(Object *obj, Object_Racer *racer, Vec3f *pos, s8 arg3, s32 updateRate, s32 arg5, f32 arg6) {
    MtxF mtxF;
    f32 velocity;
    s32 angle;
    s32 angleVel;
    f32 updateRateF;

    updateRateF = updateRate;
    if (arg3 == 14) {
        velocity = racer->velocity;
        if (velocity < 0.0f) {
            velocity = -velocity;
        }
        velocity = 1.0 - (velocity * (1.0 / 6.0));
        if (velocity < 0.0f) {
            velocity = 0.0f;
        }
    } else {
        obj->segment.trans.x_position += pos->x * updateRateF * arg6;
        obj->segment.trans.z_position += pos->z * updateRateF * arg6;
        velocity = 1.0f;
    }
    gCurrentRacerTransform.rotation.y_rotation = -obj->segment.trans.rotation.y_rotation;
    gCurrentRacerTransform.rotation.x_rotation = 0;
    gCurrentRacerTransform.rotation.z_rotation = 0;
    gCurrentRacerTransform.x_position = 0.0f;
    gCurrentRacerTransform.y_position = 0.0f;
    gCurrentRacerTransform.z_position = 0.0f;
    gCurrentRacerTransform.scale = 1.0f;
    mtxf_from_inverse_transform(&mtxF, &gCurrentRacerTransform);
    mtxf_transform_point(&mtxF, pos->x, pos->y, pos->z, &pos->x, &pos->y, &pos->z);
    angle = -((s16) (u16) arctan2_f(pos->x, pos->y)) * velocity;
    angle = (u16) (angle - (arg5 << 6)) - (u16) racer->x_rotation_vel;
    angle = angle > 0x8000 ? angle - 0xffff : angle;
    angle = angle < -0x8000 ? angle + 0xffff : angle;
    racer->x_rotation_vel += (angle * updateRate) >> 4;
    angleVel = ((s16) (u16) arctan2_f(pos->z, pos->y) * velocity);
    angleVel += -gCurrentStickY * 32;
    angleVel += 0x3C0;
    angle = (u16) angleVel - ((u16) obj->segment.trans.rotation.x_rotation);
    angle = angle > 0x8000 ? angle - 0xffff : angle;
    angle = angle < -0x8000 ? angle + 0xffff : angle;
    obj->segment.trans.rotation.x_rotation += (angle * updateRate) >> 4;
    return velocity;
}

// https://decomp.me/scratch/SlvtN
#ifdef NON_EQUIVALENT
// Plane physics, largest function in DKR.
void func_80049794(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer) {
    s32 pad5;
    s32 pad7;
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    f32 var_f20;
    f32 spD8;
    f32 spD4;
    f32 spD0;
    f32 spCC;
    f32 racerThrottle;
    f32 racerBrake;
    s32 racerMiscAssetIdx;
    s32 racerSteerAngle;
    s32 var_t0;
    s32 var_v0;
    s32 var_v1;
    s32 var_a0;
    f32 var_f0;
    s32 temp_t7;
    s8 spA3;
    s8 spA2;
    s8 spA1;
    s8 newSpinoutTimer;
    f32 segmentZVelocity;
    s32 pad2;
    f32 var_f2;
    s32 xRotationOffset;
    s32 zRotationOffset;
    s32 i;
    f32 racerVelocity;
    s32 var_t9;
    Object *temp_v0_obj;
    f32 var_f6;
    s32 racerTrickType;
    f32 segmentXVelocity;
    f32 sp60[4]; // Should be MtxF, but produces a worse score.
    s8 playerObjectMoved;
    f32 var_f14;
    s32 steerVisualRotationOffset;
    Object_Boost *boostObj;
    s32 pad3;
    s32 pad4;

    if (func_8000E138()) {
        updateRateF *= 1.09;
    }
    playerObjectMoved = FALSE;
    if (racer->groundedWheels > 0) {
        racer->unk84 = 0.0f;
        racer->unk88 = 0.0f;
    }
    if (racer->unk1FE == 4 && racer->spinout_timer == 0) {
        sound_play(SOUND_ZAP4, NULL);
        racer->spinout_timer = 20;
    }

    spA2 = FALSE;
    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->vehicleIDPrev != VEHICLE_WIZPIG && gRacerWaveCount != 0) {
        // UNMATCHED
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->segment.trans.y_position + 5; var_a0--) {}

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }

        var_f2 = gRacerCurrentWave[var_a0 + 1]->waveHeight;
        var_f2 = (obj->segment.trans.y_position - var_f2) - 10;
        if (var_f2 > 100.0f) {
            racer->drift_direction = 0;
        }
        // previously var_f0
        racerVelocity = -racer->velocity;
        if (racerVelocity < 0.0f) {
            racerVelocity = 0.0f;
        }
        if (var_f2 < 35 && racerVelocity < 8.0) {
            spA2 = TRUE;
        }
        if (racer->drift_direction == 0 && var_f2 < 38 && racerVelocity >= 8.0) {
            if ((!racerSteerAngle)) {}
            racer->drift_direction = 1;
        }
        if (racer->trickType == 1 || racer->trickType == -1 || gRacerCurrentWave[var_a0 + 1]->rot.y < 0.4) {
            racer->drift_direction = 0;
            spA2 = FALSE;
        }
        if (racer->drift_direction != 0) {
            if (racerVelocity < 8.0 || gCurrentStickY < -10) {
                racer->drift_direction = 0.0f;
            }
            racerVelocity -= 8;
            if (racerVelocity > 4.0) {
                racerVelocity = 4;
            }
            racerVelocity /= 4;
            obj->segment.trans.y_position += ((38 - var_f2) * updateRateF * racerVelocity) / 8;
            if (gCurrentStickY > 0) {
                gCurrentStickY >>= 1;
            }
        }
    }
    D_8011D550 = 0;

#ifdef FAKEMATCH
    // fake match for $f registers
    gCurrentCarSteerVel = (var_f0 > 0.0f) * 0;
#else
    gCurrentCarSteerVel = 0;
#endif

    D_8011D558 = 0;
    spE8 = obj->segment.trans.x_position;
    spE4 = obj->segment.trans.y_position;
    spE0 = obj->segment.trans.z_position;
    if (racer->trickType != 0) {
        var_f2 = 4.0;
    } else {
        var_f2 = 8.0;
    }

    var_v0 = gCurrentStickX - racer->steerAngle;
    var_v1 = var_v0 * updateRateF / var_f2;
    if (var_v0 != 0 && var_v1 == 0) {
        if (var_v0 > 0) {
            var_v1 = 1;
        }
        if (var_v0 < 0) {
            var_v1 = -1;
        }
    }
    racer->steerAngle += var_v1;

    var_v0 = gCurrentStickY - racer->unk1E8;
    var_v1 = var_v0 * updateRateF * 0.0625;
    if (var_v0 != 0 && var_v1 == 0) {
        if (var_v0 > 0) {
            var_v1 = 1;
        }
        if (var_v0 < 0) {
            var_v1 = -1;
        }
    }

    racer->unk1E8 += var_v1;
    handle_racer_items(obj, racer, updateRate);
    func_800535C4(obj, racer);
    racer_attack_handler_plane(obj, racer);
    if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
        handle_racer_head_turning(obj, racer, updateRate);
    } else {
        slowly_reset_head_angle(racer);
    }

    if (gCurrentRacerInput & A_BUTTON) {
        racer->throttle += updateRateF * 0.01;
        if (racer->throttle > 1.0) {
            racer->throttle = 1;
        }
    } else {
        racer->throttle -= updateRateF * 0.01;
        if (racer->throttle < 0) {
            racer->throttle = 0.0f;
        }
    }

    if (racer->exitObj) {
        racer->throttle = 0.5;
    }

    racerThrottle = racer->throttle;
    if (gCurrentRacerInput & B_BUTTON && (gCurrentStickY < -40 || racer->velocity < 0.0f)) {
        racer->brake += updateRateF * 0.016;
        if (racer->brake > 1.2) {
            racer->brake = 1.2f;
        }
        if (racer->velocity < -2.0 && racer->groundedWheels >= 2) {
            rumble_set(racer->playerIndex, RUMBLE_TYPE_3);
        }
    } else {
        racer->brake -= updateRateF * 0.016;
        if (racer->brake < 0.0f) {
            racer->brake = 0.0f;
        }
    }
    racerBrake = racer->brake;
    gCurrentRacerTransform.rotation.y_rotation = obj->segment.trans.rotation.y_rotation;
    gCurrentRacerTransform.rotation.x_rotation = obj->segment.trans.rotation.x_rotation;
    gCurrentRacerTransform.rotation.z_rotation = 0;
    gCurrentRacerTransform.x_position = 0.0f;
    gCurrentRacerTransform.y_position = 0.0f;
    gCurrentRacerTransform.z_position = 0.0f;
    gCurrentRacerTransform.scale = 1.0f;
    mtxf_from_transform((MtxF *) &sp60, &gCurrentRacerTransform);
    mtxf_transform_point((MtxF *) &sp60, 0.0f, 0.0f, 1.0f, &racer->ox1, &racer->oy1, &racer->oz1);
    mtxf_transform_point((MtxF *) &sp60, 1.0f, 0.0f, 0.0f, &racer->ox3, &racer->oy3, &racer->oz3);
    mtxf_transform_point((MtxF *) &sp60, 0.0f, 1.0f, 0.0f, &racer->ox2, &racer->oy2, &racer->oz2);
    if (racer->approachTarget == NULL) {
        apply_plane_tilt_anim(updateRate, obj, racer);
    }
    var_v0 = racer->playerIndex;
    if (var_v0 == PLAYER_COMPUTER && gCurrentPlayerIndex != PLAYER_COMPUTER) {
        gCurrentRacerHandlingStat = 1.4f;
    }
    var_f20 = sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) +
                    (obj->segment.z_velocity * obj->segment.z_velocity) +
                    (obj->segment.y_velocity * obj->segment.y_velocity)) -
              2.0;
    if (racer->vehicleID >= VEHICLE_BOSSES) {
        var_f20 = ((var_f20 - 2.0) / 2.0);
    }
    if (var_f20 < 0) {
        var_f20 = 0;
    }
    if (var_f20 > 4.0) {
        var_f20 = 4;
    }
    spA3 = FALSE;
    // This line (or somewhere here about) seems to be culprit as it incorrectly uses $f12 instead of $f2
    // This may or may not cause $20 to be swapped with $f2
    var_f20 = 1.0 - (var_f20 / 4.0);
    var_f2 = (gCurrentCourseHeight - 50.0) - obj->segment.trans.y_position;
    if (racer->trickType < 2 && racer->trickType >= -1 && var_f2 < 0) {
        var_f20 += -var_f2 / 25.0;
        if (gCurrentStickY < -20) {
            gCurrentStickY = -20;
        }
        if (var_f20 > 2.5) {
            var_f20 = 2.5;
        }
        spA3 = TRUE;
    }
    var_f14 = racer->velocity;
    if (var_f14 < 0) {
        var_f14 = -var_f14;
    }

    var_f0 = racer->velocity;
    if (var_f0 < 0.0f) {
        var_f0 = -var_f0;
    }
    if (var_f14 > (var_f0 + 4)) {
        var_f14 = var_f0 + 3;
    }
    if (var_f14 > 12.0f) {
        var_f14 = 12.0f;
    }
    racerMiscAssetIdx = var_f14;      // racerMiscAssetIdx = Integer part of var_f14
    var_f0 = var_f14 - (s32) var_f14; // var_f0 = fractional part of var_f14
    // UNMATCHED
    segmentZVelocity = (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1] * var_f0) +
                       (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx] * (1.0 - var_f0));
    var_f14 = segmentZVelocity;
    spD4 = 0.01;
    spD0 = 0.02;
    spD8 = 0.004;
    if (racer->groundedWheels != 0) {
        spD4 = 0.02;
        spD0 = 0.01f;
        i = SURFACE_DEFAULT;
        for (var_t0 = 0; var_t0 < 4; var_t0++) {
            if (racer->wheel_surfaces[var_t0] != SURFACE_NONE && i < racer->wheel_surfaces[var_t0]) {
                i = racer->wheel_surfaces[var_t0];
            }
        }
        if (i == SURFACE_STONE) {
            racer->magnetTimer = 0;
        }
        if (racer->playerIndex == PLAYER_ONE && i == SURFACE_TAJ_PAD && gCurrentButtonsPressed & Z_TRIG) {
            gTajInteractStatus = TAJ_TELEPORT;
        }
        if (gCurrentRacerInput & B_BUTTON && gCurrentStickY >= -40 && racer->velocity >= -0.5) {
            spD8 *= 8;
        }
        if (racer->boostTimer == 0 && i == SURFACE_ZIP_PAD) {
            racer->boostTimer = normalise_time(45);
            racer->boostType = BOOST_LARGE;
            if (racer->throttleReleased != 0) {
                racer->boostType |= EMPOWER_BOOST;
            }
            racer_play_sound(obj, SOUND_ZIP_PAD_BOOST);
            play_random_character_voice(obj, SOUND_VOICE_CHARACTER_POSITIVE, SOUND_NUMBER_OF_RACERS, 0x80 | 0x2);
            rumble_set(racer->playerIndex, RUMBLE_TYPE_8);
        }
        if (racer->vehicleID >= VEHICLE_BOSSES && racer->velocity > -6.0) {
            racerThrottle *= 0.6;
            racerBrake *= 0.3;
        }
        racer->trickType = 0;
        if (gCurrentRacerInput & B_BUTTON && gNumViewports < 3) {
            obj->particleEmittersEnabled = OBJ_EMIT_1 | OBJ_EMIT_2;
        }
        gCurrentStickY = (1.0 - var_f20) * ((f32) gCurrentStickY);
        if (gCurrentStickY > 0) {
            gCurrentStickY = 0;
        }
    }
    var_t0 = 0;
    if (spA3 == FALSE) {
        var_t0 = (var_f20 * 4608);
    }
    if (racer->vehicleID > VEHICLE_BOSSES) {
        var_t0 = 0;
    }
    if (racer->vehicleID == VEHICLE_CARPET) {
        var_f20 = 0.0;
        var_t0 = 0;
    }
    apply_vehicle_rotation_offset(racer, updateRate, 0, var_t0, 0);
    if (racer->unk1FE == 0) {
        var_f20 = 5.5;
        obj->particleEmittersEnabled |= OBJ_EMIT_9;
    }
    if (racer->unk1FE == 1) {
        var_f20 = 2;
    }
    if (racer->buoyancy != 0.0) {
        gCurrentStickY = -60;
        var_f2 = racer->buoyancy - 20.0f;
        if (var_f2 < 0.0) {
            var_f2 = 0;
        }
        var_f20 = -1 - (var_f2 / 10);
        if (var_f20 < -4.0) {
            var_f20 = -4;
        }
    }
    if (gRaceStartTimer != 0) {
        var_f20 = 1;
    }
    if (racer->vehicleIDPrev == VEHICLE_WIZPIG) {
        if (obj->segment.object.animationID < 3) {
            var_f20 = 4.0f;
        } else {
            var_f20 = 0.0f;
        }
    }
    var_f20 *= gCurrentRacerWeightStat;
    obj->segment.y_velocity -= var_f20;
    if (racer->zipperDirCorrection != 0 && racer->spinout_timer == 0) {
        racer->magnetTimer = 0;
        racer->spinout_timer = 0;
        racer->trickType = 0;
        steerVisualRotationOffset =
            racer->zipperObj->segment.trans.rotation.y_rotation - (racer->steerVisualRotation & 0xFFFF);
        if (steerVisualRotationOffset > 0x8000) {
            steerVisualRotationOffset -= 0xFFFF;
        }
        if (steerVisualRotationOffset < -0x8000) {
            steerVisualRotationOffset += 0xFFFF;
        }
        racer->steerVisualRotation += (steerVisualRotationOffset * updateRate) >> 3;
        if (((steerVisualRotationOffset < 0x400) && (steerVisualRotationOffset > -0x400)) ||
            (racer->playerIndex == PLAYER_COMPUTER)) {
            if (racer->playerIndex != PLAYER_COMPUTER) {
                sound_play_spatial(SOUND_ZIP_PAD_BOOST, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                   obj->segment.trans.z_position, NULL);
                play_random_character_voice(obj, SOUND_VOICE_CHARACTER_POSITIVE, SOUND_NUMBER_OF_RACERS, 0x80 | 0x2);
            }
            racer->boostTimer = normalise_time(45);
            racer->boostType = BOOST_LARGE;
            if (racer->throttleReleased != 0) {
                racer->boostType |= EMPOWER_BOOST;
            }
            rumble_set(racer->playerIndex, 8);
            racer->zipperDirCorrection = 0;
        } else {
            obj->segment.x_velocity *= 0.75;
            obj->segment.y_velocity *= 0.75;
            obj->segment.z_velocity *= 0.75;
        }
    }
    if (racer->spinout_timer != 0) {
        xRotationOffset = racer->x_rotation_offset;
        if (racer->unk1F1 == 0) {
            racer->unk1F1 = 1;
        }
        if (racer->groundedWheels != 0 || racer->unk1F1 == 2) {
            racer->unk1F1 = 2;
            // s0.162 = x_rot_offset
            // s0.164 = z_rot_offset
            temp_t7 = updateRate << 11;
            racer->x_rotation_offset -= temp_t7;
            var_t0 = racer->z_rotation_offset;
            if ((temp_t7 + var_t0) > 0 && var_t0 <= 0) {
                racer->z_rotation_offset = 0;
            } else {
                racer->z_rotation_offset += temp_t7;
            }
            if (racer->velocity > -2.0 && racer->groundedWheels >= 3) {
                racer->spinout_timer = 0;
            }
        } else {
            racer->z_rotation_offset += updateRate << 11;
        }
        if (racer->groundedWheels != 0 && ((xRotationOffset > 0x6000 && racer->x_rotation_offset <= 0x6000) ||
                                           (xRotationOffset > -0x6000 && racer->x_rotation_offset <= -0x6000) ||
                                           (xRotationOffset > 0 && racer->x_rotation_offset <= 0))) {
            racer_play_sound(obj, SOUND_CRASH);
            if (racer->playerIndex != PLAYER_COMPUTER) {
                gCameraObject->shakeMagnitude = 6.0f;
            }
        }
        gCurrentRacerInput &= ~(A_BUTTON | Z_TRIG);
        racer->spinout_timer -= updateRate;
        racer->boostTimer = 0;
        racer->brake = 1;
        if (racer->spinout_timer <= 0) {
            racer->spinout_timer = 0;
            racer->unk1F1 = 0;
        }
        xRotationOffset = 0xD800 - (obj->segment.trans.rotation.x_rotation & 0xFFFF);
        if (xRotationOffset > 0x8000) {
            xRotationOffset -= 0xFFFF;
        }
        if (xRotationOffset < -0x8000) {
            xRotationOffset += 0xFFFF;
        }
        obj->segment.trans.rotation.x_rotation += (xRotationOffset * updateRate) >> 4;
    } else {
        if (racer->trickType == 1 || racer->trickType == -1) {
            var_v1 = racer->x_rotation_vel;
            racer->x_rotation_vel = (0, var_v1) + ((racer->trickType * 0x600) * updateRate);
            racerThrottle = 1.2f;
            if (racer->trickType == 1) {
                if (var_v1 > 0) {
                    racer->unk1D4 = 1;
                }
                if ((var_v1 < 0) && (racer->x_rotation_vel >= 0) && (racer->unk1D4 != 0)) {
                    racer->trickType = 0;
                    racer->x_rotation_vel = 0;
                }
            } else {
                if (var_v1 < 0) {
                    racer->unk1D4 = 1;
                }
                if ((var_v1 > 0) && (racer->x_rotation_vel <= 0) && (racer->unk1D4 != 0)) {
                    racer->trickType = 0;
                    racer->x_rotation_vel = 0;
                }
            }
        } else if (racer->trickType == 2 || racer->trickType == -2) {
            var_v1 = obj->segment.trans.rotation.x_rotation;
            var_t0 = var_v1;
            if (racer->unk1D5 == 0) {
                obj->segment.trans.rotation.x_rotation =
                    var_v1 + ((racer->trickType * (((0x180 & 0xFFFFFFFF) & 0xFFFFFFFF) & 0xFFFFFFFF)) * updateRate);
            }
            if (!(gCurrentRacerInput & R_TRIG)) {
                racer->unk1D5 = 0;
            }
            if (racer->unk1D5 > 0) {
                racer->unk1D5 -= updateRate;
            } else {
                racer->unk1D5 = 0;
            }
            var_v1 = racer->x_rotation_vel;
            racer->x_rotation_vel = var_v1 - ((var_v1 * updateRate) >> 4);
            obj->segment.x_velocity = racer->velocity * racer->ox1;
            obj->segment.y_velocity = racer->oy1 * racer->velocity;
            obj->segment.z_velocity = racer->velocity * racer->oz1;
            if (racer->trickType == 2) {
                if (var_t0 > 0) {
                    racer->unk1D4 = 1;
                }
                if (var_t0 < 0) {
                    if (obj->segment.trans.rotation.x_rotation >= 0) {
                        if (racer->unk1D4 != 0) {
                            racer->trickType = 0;
                            obj->segment.trans.rotation.x_rotation = 0;
                            racer->boostTimer = normalise_time(0xA);
                            racer->boostType = BOOST_NONE;
                            if (racer->throttleReleased != 0) {
                                racer->boostType |= EMPOWER_BOOST;
                            }
                        }
                    }
                }
                if (var_t0 > 0x4000 && obj->segment.trans.rotation.x_rotation < -0x4000 &&
                    (gCurrentRacerInput & R_TRIG)) {
                    racer->unk1D5 = 60;
                }
            } else {
                if (var_t0 < 0) {
                    racer->unk1D4 = 1;
                }
                if (var_t0 > 0) {
                    if (obj->segment.trans.rotation.x_rotation <= 0) {
                        if (racer->unk1D4 != 0) {
                            racer->trickType = 0;
                            obj->segment.trans.rotation.x_rotation = 0;
                            racer->boostTimer = normalise_time(10);
                            racer->boostType = BOOST_NONE;
                            if (racer->throttleReleased != 0) {
                                racer->boostType |= EMPOWER_BOOST;
                            }
                        }
                    }
                }
                if (var_t0 < -0x4000 && obj->segment.trans.rotation.x_rotation > 0x4000 &&
                    (gCurrentRacerInput & R_TRIG)) {
                    racer->unk1D5 = 60;
                }
            }
        } else {
            racerSteerAngle = racer->steerAngle;
            spA1 = FALSE;
            if (racer->groundedWheels != 0) {
                if (gCurrentRacerInput & R_TRIG) {
                    spA1 = TRUE;
                }
                gCurrentRacerInput &= ~R_TRIG;
            }
            if (racer->groundedWheels < 2) {
                var_v1 = obj->segment.trans.rotation.x_rotation;
                xRotationOffset = 0;
                var_t0 = racerSteerAngle;
                if (obj->segment.trans.rotation.x_rotation > 0x3000) {
                    xRotationOffset = var_v1 - 0x3000;
                    if (xRotationOffset > 0x1000) {
                        xRotationOffset = 0x1000;
                    }
                } else if (var_v1 < -0x3000) {
                    xRotationOffset = var_v1 + 0x3000;
                    if (xRotationOffset < -0x1000) {
                        xRotationOffset = -0x1000;
                    }
                    xRotationOffset = -xRotationOffset;
                }
                var_t0 *= (f32) (1.0 - ((f32) xRotationOffset / 4096));
                if (gCurrentRacerInput & R_TRIG) {
                    obj->particleEmittersEnabled |= OBJ_EMIT_7 | OBJ_EMIT_8;
                    racer->x_rotation_vel -= (var_t0 * 16 * updateRate) >> 1;
                }
                racer->x_rotation_vel -= (var_t0 * updateRate * 20) >> 1;
                racer->x_rotation_vel -= (racer->x_rotation_vel * updateRate) >> 4;
                if (racer->zipperDirCorrection == 0) {
                    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->raceFinished == FALSE) {
                        var_t0 = -racer->x_rotation_vel >> 6;
                        if ((gCurrentRacerInput & R_TRIG) && (gCurrentRacerInput & B_BUTTON)) {
                            var_t0 *= 2;
                        }
                        var_t0 *= gCurrentRacerHandlingStat;
                        var_v0 = var_t0 * updateRate;
                        racer->steerVisualRotation -= var_v0 & 0xFFFF;
                    } else {
                        var_t0 = gCurrentStickX * 4;
                        var_v0 = var_t0 * updateRate;
                        racer->steerVisualRotation -= var_v0 & 0xFFFF;
                    }
                }
            } else {
                var_v0 = -(racer->x_rotation_vel & 0xFFFF);
                if (var_v0 > 0x8000) {
                    var_v0 -= 0xFFFF;
                }
                if (var_v0 < -0x8000) {
                    var_v0 += 0xFFFF;
                }
                racer->x_rotation_vel += (var_v0 * updateRate) >> 4;
                if (gCurrentRacerInput & R_TRIG) {
                    var_t0 = racerSteerAngle * 6;
                } else {
                    var_t0 = racerSteerAngle * 4;
                }
                racer->steerVisualRotation -= (var_t0 * updateRate) & 0xFFFF;
            }
            if (!(gCurrentRacerInput & R_TRIG) || racer->groundedWheels == 0 || racer->zipperDirCorrection != 0) {
                var_f20 = racer->velocity * var_t0 * 0.00015;
                obj->segment.x_velocity -= racer->ox3 * var_f20;
                obj->segment.y_velocity -= racer->oy3 * var_f20;
                obj->segment.z_velocity -= racer->oz3 * var_f20;
            }

            var_t0 = gCurrentStickY;
            if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->raceFinished == FALSE) {
                var_t0 = racer->unk1E8;
            }

            var_f2 = -racer->velocity;
            if (var_f2 < 4.0) {
                var_f2 = 4.0f;
            }
            if (var_f2 > 14.0) {
                var_f2 = 14.0f;
            }
            var_f2 /= 7.0;
            var_t0 *= var_f2;

            // Note: The following if/else has messed up t registers
            if (!(gCurrentRacerInput & R_TRIG)) {
                obj->segment.trans.rotation.x_rotation -= (obj->segment.trans.rotation.x_rotation * updateRate) >> 4;
                obj->segment.trans.rotation.x_rotation -= ((var_t0 >> 1) * 19 * updateRate) >> 1;
            } else {
                obj->segment.trans.rotation.x_rotation -= (obj->segment.trans.rotation.x_rotation * updateRate) >> 4;
                obj->segment.trans.rotation.x_rotation -= ((var_t0 >> 1) * 30 * updateRate) >> 1;
            }

            if (racer->tappedR) {
                racer->tappedR = FALSE;
                if (racer->groundedWheels == 0 && racer->velocity < -6.5 && racer->waterTimer == 0) {
                    if (gCurrentStickX > 40) {
                        racer->trickType = -1;
                    }
                    if (gCurrentStickX < -40) {
                        racer->trickType = 1;
                    }
                    if (gCurrentStickY > 40) {
                        racer->trickType = -2;
                    } else if (racer->trickType == 0) {
                        racer->trickType = 2;
                    }
                    racer->unk1D4 = 0;
                    racer->unk1D5 = 0;
                }
            }
        }
    }
    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->velocity < -4.0f) {
        if ((obj->particleEmittersEnabled & (OBJ_EMIT_7 | OBJ_EMIT_8)) != (OBJ_EMIT_7 | OBJ_EMIT_8)) {
            obj->particleEmittersEnabled |= OBJ_EMIT_3 | OBJ_EMIT_4;
        }
    }
    // This line looks unmatched
    var_f14 = (var_f14 * handle_racer_top_speed(obj, racer)) * 1.8;
    if (racer->boostTimer > 0) {
        if (gRaceStartTimer == 0) {
            racer->throttle = 1;
            var_f14 = 2.0f;
            racer->boostTimer -= updateRate;
            obj->particleEmittersEnabled |= OBJ_EMIT_7 | OBJ_EMIT_8;
        }
    } else {
        racer->boostTimer = 0;
    }
    if (racer->zipperDirCorrection == 0 && gRaceStartTimer == 0) {
        if (racer->groundedWheels == 0 && racerThrottle < 0.4 && racer->vehicleID != VEHICLE_CARPET) {
            racerThrottle = 0.4f;
        }
        var_f0 = racerThrottle * var_f14;
        obj->segment.x_velocity -= racer->ox1 * var_f0;
        obj->segment.y_velocity -= racer->oy1 * var_f0;
        obj->segment.z_velocity -= racer->oz1 * var_f0;
        if (racer->groundedWheels >= 3 || racer->velocity < 1.0 || racer->vehicleID == VEHICLE_CARPET) {
            if (racer->groundedWheels == 0) {
                racerBrake /= 2;
            }
            racerBrake *= var_f14 / 2;
            obj->segment.x_velocity += racer->ox1 * racerBrake;
            obj->segment.y_velocity += racer->oy1 * racerBrake;
            obj->segment.z_velocity += racer->oz1 * racerBrake;
        }
        spEC = racer->velocity * racer->velocity;
        if (racer->velocity < 0.0f) {
            spEC = -spEC;
        }
        if (spEC < 1.0f && !(gCurrentRacerInput & A_BUTTON)) {
            var_f20 = racer->velocity * spD8 * 8.0f;
        } else {
            var_f20 = spEC * spD8;
        }
        obj->segment.x_velocity -= racer->ox1 * var_f20;
        obj->segment.y_velocity -= racer->oy1 * var_f20;
        obj->segment.z_velocity -= racer->oz1 * var_f20;
        var_f20 = racer->lateral_velocity * racer->lateral_velocity * spD4;
        if (racer->lateral_velocity < 0) {
            var_f20 = -var_f20;
        }
        var_f20 += (racer->lateral_velocity * spD4 * 4.0f);
        obj->segment.x_velocity -= racer->ox3 * var_f20;
        obj->segment.y_velocity -= racer->oy3 * var_f20;
        obj->segment.z_velocity -= racer->oz3 * var_f20;
        if (racer->trickType == 1 || racer->trickType == -1) {
            spEC = racer->velocity * 0.0588235 * 1.5;
            var_f20 = coss_f(racer->x_rotation_vel) * spEC * racer->trickType;
            if (racer->x_rotation_vel > 0x4000 || racer->x_rotation_vel < -0x4000) {
                var_f20 *= 2;
            }
            obj->segment.x_velocity -= racer->ox3 * var_f20;
            obj->segment.y_velocity -= racer->oy3 * var_f20;
            obj->segment.z_velocity -= racer->oz3 * var_f20;

            var_f20 = sins_f(racer->x_rotation_vel) * spEC * racer->trickType * 1.5;
            obj->segment.x_velocity -= racer->ox2 * var_f20;
            obj->segment.y_velocity -= racer->oy2 * var_f20;
            obj->segment.z_velocity -= racer->oz2 * var_f20;
        }
        var_f20 = racer->unk34 * racer->unk34 * spD0;
        if (racer->unk34 < 0.0f) {
            var_f20 = -var_f20;
        }
        var_f20 += 4.0f * (racer->unk34 * spD0);
        obj->segment.x_velocity -= racer->ox2 * var_f20;
        obj->segment.y_velocity -= racer->oy2 * var_f20;
        obj->segment.z_velocity -= racer->oz2 * var_f20;

        racer->forwardVel -= (racer->forwardVel + (racer->velocity * 0.05)) * 0.125;
    }
    racer->unk10C = 0;
    racer->y_rotation_vel += (gCurrentCarSteerVel - racer->y_rotation_vel) >> 3;
    obj->segment.trans.rotation.y_rotation = racer->steerVisualRotation + racer->y_rotation_vel;
    racer->z_rotation_vel += (D_8011D558 - racer->z_rotation_vel) >> 3;
    obj->segment.trans.rotation.z_rotation = racer->x_rotation_vel + racer->z_rotation_vel;
    if (racer->magnetTimer != 0) {
        obj->segment.x_velocity = gRacerMagnetVelX;
        obj->segment.z_velocity = gRacerMagnetVelZ;
    }
    if (racer->approachTarget == NULL) {
        var_f20 = obj->segment.x_velocity;
        spEC = obj->segment.z_velocity;
        if (racer->unk1D2 != 0) {
            var_f20 += racer->unk11C * 0.5;
            spEC += racer->unk120 * 0.5;
        }
        if (gRacerInputBlocked) {
            if (var_f20 > 0.5 || var_f20 < -0.5) {
                var_f20 *= 0.65;
            } else {
                var_f20 = 0.0f;
            }
            if (spEC > 0.5 || spEC < -0.5) {
                spEC *= 0.65;
            } else {
                spEC = 0.0f;
            }
        } else {
            var_f20 += racer->unk84;
            spEC += racer->unk88;
        }
        if (move_object(obj, var_f20 * updateRateF, obj->segment.y_velocity * updateRateF, spEC * updateRateF) &&
            gCurrentPlayerIndex != PLAYER_COMPUTER) {
            playerObjectMoved = TRUE;
        }
    } else {
        racer_approach_object(obj, racer, updateRateF);
    }
    var_t0 = racer->groundedWheels;
    if (gCurrentPlayerIndex == PLAYER_COMPUTER) {
        if (racer->vehicleIDPrev != VEHICLE_ROCKET || gRaceStartTimer != 0) {
            onscreen_ai_racer_physics(obj, racer, updateRate);
        } else {
            racer->groundedWheels = 0;
            racer->unk1E3 = 0;
        }
    } else {
        func_80054FD0(obj, racer, updateRate);
    }
    if (var_t0 == 0 && racer->groundedWheels != 0 && racer->spinout_timer != 0) {
        racer_play_sound(obj, SOUND_CRASH);
        if (racer->playerIndex != PLAYER_COMPUTER) {
            gCameraObject->shakeMagnitude = 6.0f;
        }
    }
    if (racer->unk1D2 != 0) {
        racer->unk1D2 -= updateRate;
        if (racer->unk1D2 < 0) {
            racer->unk1D2 = 0;
        }
    } else {
        var_f0 = 1.0f / updateRateF;
        var_f20 = (obj->segment.trans.x_position - spE8 - D_8011D548) * var_f0;
        obj->segment.y_velocity = (obj->segment.trans.y_position - spE4) * var_f0;
        spEC = (obj->segment.trans.z_position - spE0 - D_8011D54C) * var_f0;
    }
    if (gRaceStartTimer == 100) {
        obj->segment.y_velocity = -5.0f;
    }
    obj->segment.x_velocity = var_f20;
    obj->segment.z_velocity = spEC;
    gCurrentRacerTransform.rotation.y_rotation = -obj->segment.trans.rotation.y_rotation;
    gCurrentRacerTransform.rotation.x_rotation = -obj->segment.trans.rotation.x_rotation;
    gCurrentRacerTransform.rotation.z_rotation = 0;
    gCurrentRacerTransform.x_position = 0.0f;
    gCurrentRacerTransform.y_position = 0.0f;
    gCurrentRacerTransform.z_position = 0.0f;
    gCurrentRacerTransform.scale = 1.0f;
    mtxf_from_inverse_transform((MtxF *) &sp60, &gCurrentRacerTransform);
    mtxf_transform_point((MtxF *) &sp60, obj->segment.x_velocity, obj->segment.y_velocity, obj->segment.z_velocity,
                         &racer->lateral_velocity, &racer->unk34, &racer->velocity);
    if (obj->unk60 != NULL && obj->unk60->unk0 >= 3) {
        temp_v0_obj = obj->unk60->unk4[2];
        temp_v0_obj->segment.trans.rotation.y_rotation = 0x4000;
        temp_v0_obj->segment.object.modelIndex += 1;
        if (temp_v0_obj->segment.object.modelIndex == temp_v0_obj->segment.header->numberOfModelIds) {
            temp_v0_obj->segment.object.modelIndex = 0;
        }
    }
    if (obj->unk60 != NULL && obj->unk60->unk0 >= 3) {
        if (racer->groundedWheels != 0 || spA2 != FALSE) {
            temp_v0_obj = obj->unk60->unk4[0];
            if (temp_v0_obj->segment.trans.y_position > 0.0f) {
                temp_v0_obj->segment.trans.y_position = temp_v0_obj->segment.trans.y_position - 2.0;
            } else {
                temp_v0_obj->segment.trans.y_position = 0.0f;
            }
            temp_v0_obj->segment.trans.flags &= ~OBJ_FLAGS_INVISIBLE;
            temp_v0_obj = obj->unk60->unk4[1];
            if (temp_v0_obj->segment.trans.y_position > 0.0f) {
                temp_v0_obj->segment.trans.y_position = temp_v0_obj->segment.trans.y_position - 2.0;
            } else {
                temp_v0_obj->segment.trans.y_position = 0.0f;
            }
            temp_v0_obj->segment.trans.flags &= ~OBJ_FLAGS_INVISIBLE;
        } else {
            temp_v0_obj = obj->unk60->unk4[0];
            if (temp_v0_obj->segment.trans.y_position < 20.0f) {
                temp_v0_obj->segment.trans.y_position = temp_v0_obj->segment.trans.y_position + 1.0f;
            } else {
                temp_v0_obj->segment.trans.flags |= OBJ_FLAGS_INVISIBLE;
            }
            temp_v0_obj = obj->unk60->unk4[1];
            if (temp_v0_obj->segment.trans.y_position < 20.0f) {
                temp_v0_obj->segment.trans.y_position = temp_v0_obj->segment.trans.y_position + 1.0f;
            } else {
                temp_v0_obj->segment.trans.flags |= OBJ_FLAGS_INVISIBLE;
            }
        }
    }
    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->boostTimer == 0 && gNumViewports < 2) {
        boostObj = (Object_Boost *) get_misc_asset(ASSET_MISC_20);
        boostObj = &boostObj[racer->racerIndex];
        var_t0 = ((racer->boostType & EMPOWER_BOOST) >> 2) + 9;
        if (var_t0 >= 10) {
            if (boostObj->unk70 > 0 || boostObj->unk74 > 0.0) {
                obj->particleEmittersEnabled |= 1 << var_t0;
            }
        } else {
            if (boostObj->unk70 == 2 && boostObj->unk74 < 0.5) {
                obj->particleEmittersEnabled |= 1 << var_t0;
            } else if (boostObj->unk70 < 2 && boostObj->unk74 > 0.0f) {
                obj->particleEmittersEnabled |= 1 << var_t0;
            }
        }
    }
    if (gCurrentPlayerIndex == PLAYER_COMPUTER) {
        obj->particleEmittersEnabled = OBJ_EMIT_NONE;
    }
    if (racer->unk201 == 0) {
        obj->particleEmittersEnabled = OBJ_EMIT_NONE;
    }
    if (racer->vehicleIDPrev < VEHICLE_BOSSES) {
        update_vehicle_particles(obj, updateRate);
    }
    if (spA1 != FALSE) {
        gCurrentRacerInput |= R_TRIG;
    }
    second_racer_camera_update(obj, racer, 1, updateRateF);
    if (playerObjectMoved != FALSE) {
        func_800230D0(obj, racer);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/racer/func_80049794.s")
#endif

/**
 * When turning left and right in a plane, apply the tilting animation to the character.
 * There's a few safeguards in place to ensure the animation frame is not out of bounds.
 */
void apply_plane_tilt_anim(s32 updateRate, Object *obj, Object_Racer *racer) {
    s32 animDiff;
    s32 animAdd;

    if (racer->vehicleIDPrev != VEHICLE_CARPET) {
        //!@bug Typo. Should've been `== 0`, not `= 0`.
        if ((racer->unk1F2 = 0)) {
            return; // This never gets called because of the typo.
        }
        animAdd = racer->steerAngle;
        animAdd = 40 - (animAdd >> 1);
        if (animAdd < 0) {
            animAdd = 0;
        }
        if (animAdd > 73) {
            animAdd = 73;
        }
        animDiff = animAdd - obj->segment.animFrame;
        animAdd = 0;
        if (animDiff > 0) {
            animAdd = updateRate * 3;
            if (animDiff < animAdd) {
                animAdd = animDiff;
            }
        }
        if (animDiff < 0) {
            animAdd = updateRate * -3;
            if (animAdd < animDiff) {
                animAdd = animDiff;
            }
        }
        obj->segment.animFrame += animAdd; //!@Delta
    }
}

/**
 * Initialise some states when a racer is attacked or runs into something.
 * While the majority of the respondent behaviour takes place elsewhere, the squish behaviour happens here.
 * Planes do not have a spinning state, instead being in the same state when hit by a rocket.
 */
void racer_attack_handler_plane(Object *obj, Object_Racer *racer) {
    s8 bananas;
    s8 attackType;
    if (racer->playerIndex == PLAYER_COMPUTER) {
        bananas = 0;
    } else {
        bananas = racer->bananas;
    }
    attackType = racer->attackType;
    if (attackType == ATTACK_NONE || racer->shieldTimer > 0) {
        racer->attackType = ATTACK_NONE;
        return;
    }
    if (attackType != ATTACK_SQUISHED) {
        drop_bananas(obj, racer, 2);
    }
    racer->unk18C = 360;
    if (racer->unk1C9 == 8) {
        racer->unk1C9 = 0;
    }
    if (racer->vehicleID < VEHICLE_BOSSES) {
        play_random_character_voice(obj, SOUND_VOICE_CHARACTER_NEGATIVE, 8, 129);
        switch (racer->attackType) {
            case ATTACK_EXPLOSION:
            case ATTACK_SPIN:
                if (bananas != 0) {
                    racer->spinout_timer = 40;
                } else {
                    racer->spinout_timer = 60;
                }
                break;
            case ATTACK_UNK3:
                if (bananas != 0) {
                    racer->spinout_timer = 40;
                } else {
                    racer->spinout_timer = 60;
                }
                break;
            case ATTACK_BUBBLE:
                racer->bubbleTrapTimer = 120;
                obj->segment.x_velocity *= 0.7;
                obj->segment.z_velocity *= 0.7;
                break;
        }
        racer->attackType = ATTACK_NONE;
    }
}

void update_camera_plane(f32 updateRate, Object *obj, Object_Racer *racer) {
    s32 segmentIndex;
    f32 baseSpeed;
    s32 pad_sp44;
    f32 yOffset;
    f32 pad_sp3C;
    s32 angleVel;
    f32 baseFloat2 = 120.0f;
    f32 baseFloat1 = 45.0f;
    s32 angle;
    f32 xOffset;
    f32 zOffset;
    f32 var_f16;
    f32 var_f14;
    f32 brakeVar = 0.0f;
    s32 numViewports;
    s32 delta;

    delta = (s32) updateRate;
    var_f16 = gCurrentCourseHeight - obj->segment.trans.y_position;
    var_f16 = 200.0f - (var_f16);
    if (var_f16 < 0.0f) {
        var_f16 = 0.0f;
    }
    if (var_f16 > 200.0f) {
        var_f16 = 200.0f;
    }
    numViewports = cam_get_viewport_layout();
    if (numViewports == 1) {
        baseFloat2 = 180.0f;
        baseFloat1 = 50.0f;
    } else if (numViewports > 1) {
        baseFloat2 = 110.0f;
        baseFloat1 = 42.0f;
    }
    if (((!(gCurrentRacerInput & 0x10)) || racer->groundedWheels < 3) && !racer->zipperDirCorrection) {
        angle = (-racer->steerVisualRotation - (racer->cameraYaw & 0xFFFF)) + 0x8000;
        if (angle > 0x8000) {
            angle -= 0xFFFF;
        }
        if (angle < -0x8000) {
            angle += 0xFFFF;
        }
        if (racer->camera_zoom < 0.4) {
            racer->camera_zoom += 1 / 180.0;
        } else {
            racer->camera_zoom = 0.4f;
        }
        angleVel = angle * racer->camera_zoom;
        if (angleVel > 0x200) {
            angleVel = 0x200;
        }
        if (angleVel < -0x200) {
            angleVel = -0x200;
        }
        angleVel *= delta;
        if (angle < 0 && angleVel < angle) {
            angleVel = angle;
        }
        if (angle > 0 && angle < angleVel) {
            angleVel = angle;
        }
        racer->cameraYaw += angleVel;
    } else {
        racer->camera_zoom = 0.0f;
    }
    if (gDialogueCameraAngle) {
        racer->cameraYaw = 0x8000 - racer->steerVisualRotation;
    }
    if (racer->trickType == 2 || racer->trickType == -2) {
        angle = 0;
    } else {
        angle = obj->segment.trans.rotation.x_rotation;
        if (angle > 0x3000) {
            angle = 0x3000;
        }
        if (angle < -0x3000) {
            angle = -0x3000;
        }
    }
    angle = -(angle - ((s32) (var_f16 * 10.0f)));
    angleVel = angle - ((u16) gCameraObject->trans.rotation.x_rotation);
    if (angleVel > 0x8000) {
        angleVel -= 0xFFFF;
    }
    if (angleVel < -0x8000) {
        angleVel += 0xFFFF;
    }
    gCameraObject->trans.rotation.x_rotation += ((angleVel * delta) >> 4);
    brakeVar = racer->brake;
    baseSpeed = racer->forwardVel;
    switch (gCameraObject->zoom) {
        case 1:
            baseFloat2 += 35.0f;
            break;
        case 2:
            baseFloat1 -= 10.0f;
            baseFloat2 -= 35.0f;
            break;
        case 3:
            baseFloat2 -= 53.0f;
            baseFloat1 -= 5.0f;
            baseSpeed *= 0.25;
            brakeVar = 0.0f;
            break;
    }
    if (numViewports < 2) {
        baseFloat2 += baseSpeed * 60.0f;
    } else {
        baseFloat2 += baseSpeed * 30.0f;
    }
    if (racer->velocity < 0.0 && !racer->groundedWheels) {
        var_f16 = -(racer->velocity * brakeVar) * 6.0f;
        if (65.0 < var_f16) {
            var_f16 = 65.0f;
        }
        baseFloat2 -= var_f16;
    }
    if (!gRaceStartTimer) {
        if (normalise_time(36) < racer->boostTimer) {
            baseFloat2 = -30.0f;
        } else if (racer->boostTimer > 0) {
            baseFloat2 = 180.0f;
        }
    }
    if (gRaceStartTimer > 80) {
        gCameraObject->boomLength = baseFloat2;
        gCameraObject->cam_unk_20 = baseFloat1;
    }
    gCameraObject->boomLength += (baseFloat2 - gCameraObject->boomLength) * 0.125;
    gCameraObject->cam_unk_20 += (baseFloat1 - gCameraObject->cam_unk_20) * 0.125;
    var_f14 = sins_f(gCameraObject->trans.rotation.x_rotation - 0x400);
    xOffset = coss_f(gCameraObject->trans.rotation.x_rotation - 0x400);
    var_f16 = (gCameraObject->boomLength * xOffset) - (gCameraObject->cam_unk_20 * var_f14);
    baseFloat1 = ((gCameraObject->boomLength) * var_f14) + (gCameraObject->cam_unk_20 * xOffset);
    xOffset = sins_f(0x8000 - racer->cameraYaw) * var_f16;
    zOffset = coss_f(0x8000 - racer->cameraYaw) * var_f16;
    var_f16 = sins_f(racer->cameraYaw + 0x4000) * 3.0f * racer->lateral_velocity;
    gCameraObject->trans.x_position = (obj->segment.trans.x_position + xOffset) + var_f16;
    yOffset = gCameraObject->trans.y_position - (obj->segment.trans.y_position + baseFloat1);
    var_f16 = yOffset;
    if (racer->trickType == 1 || racer->trickType == -1) {
        racer->unk74 = 8.0;
    }
    if (racer->trickType == 2 || racer->trickType == -2) {
        racer->unk74 = 8.0;
    }
    if (racer->unk74 > 2.0) {
        racer->unk74 -= 0.2;
    } else {
        racer->unk74 = 2.0;
    }
    yOffset = (yOffset * updateRate) / racer->unk74;
    if (yOffset > 0.0f && var_f16 < yOffset) {
        yOffset = var_f16;
    }
    if (yOffset < 0.0f && yOffset < var_f16) {
        yOffset = var_f16;
    }
    gCameraObject->trans.y_position -= yOffset;
    var_f16 = (-coss_f(racer->cameraYaw + 0x4000) * 3.0f * racer->lateral_velocity);
    gCameraObject->trans.z_position = zOffset + obj->segment.trans.z_position + var_f16;
    gCameraObject->trans.rotation.y_rotation = racer->cameraYaw;
    if (racer->trickType || gDialogueCameraAngle) {
        angleVel = -(u16) gCameraObject->trans.rotation.z_rotation;
        if (angleVel > 0x8000) {
            angleVel -= 0xFFFF;
        }
        if (angleVel < -0x8000) {
            angleVel += 0xFFFF;
        }
        gCameraObject->trans.rotation.z_rotation += angleVel >> 2;
    } else {
        angle = racer->x_rotation_vel;
        angleVel = (angle >> 4) - (u16) gCameraObject->trans.rotation.z_rotation;
        if (angleVel > 0x8000) {
            angleVel -= 0xFFFF;
        }
        if (angleVel < -0x8000) {
            angleVel += 0xFFFF;
        }
        gCameraObject->trans.rotation.z_rotation += angleVel >> 3;
    }
    segmentIndex = get_level_segment_index_from_position(
        gCameraObject->trans.x_position, gCameraObject->trans.y_position, gCameraObject->trans.z_position);
    if (segmentIndex != -1) {
        gCameraObject->cameraSegmentID = segmentIndex;
    }
    racer->cameraYaw = gCameraObject->trans.rotation.y_rotation;
}

// Handles loop de loops
void func_8004CC20(s32 updateRate, f32 updateRateF, Object *racerObj, Object_Racer *racer) {
    s32 animFrame;
    s32 moveObjResult;
    f32 curYPos;
    s32 i;
    Object **nodes;
    s32 var_a2;
    s32 var_v0;
    f32 prevXPos;
    f32 prevYPos;
    f32 prevZPos;
    f32 xDiff;
    f32 zDiff;
    f32 yDiff;
    s32 var_v1;
    f32 temp;
    f32 temp2;
    f32 temp3;
    s32 steerAngle;
    f32 temp4;
    f32 var_f0;
    f32 mtx[4][4];
    Object *obj;
    f32 var_f2;
    s8 objectMoved;

    objectMoved = FALSE;
    racer->shieldTimer = 0;
    racer->shieldType = 0;
    if (racer->shieldSoundMask != NULL) {
        audspat_point_stop(racer->shieldSoundMask);
        racer->shieldSoundMask = NULL;
    }
    if (racer->boostTimer == 0) {
        racer->boostTimer = 8;
        racer_play_sound(racerObj, SOUND_ZIP_PAD_BOOST);
    }
    if (racer->boostTimer < 4) {
        racer->boostTimer = 4;
    }
    racer->boostType = BOOST_NONE;
    func_8002ACC8(2);
    D_8011D550 = 0;
    gCurrentCarSteerVel = 0;
    D_8011D558 = 0;
    prevXPos = racerObj->segment.trans.x_position;
    prevYPos = racerObj->segment.trans.y_position;
    prevZPos = racerObj->segment.trans.z_position;
    var_v1 = gCurrentStickX - racer->steerAngle;
    var_a2 = (var_v1 * updateRate) >> 4;
    if (var_v1 != 0 && var_a2 == 0) {
        if (var_v1 > 0) {
            var_a2 = 1;
        }
        if (var_v1 < 0) {
            var_a2 = -1;
        }
    }
    racer->steerAngle += var_a2;
    var_v1 = gCurrentStickY - racer->unk1E8;
    var_a2 = (var_v1 * updateRate) >> 4;
    if (var_v1 != 0 && var_a2 == 0) {
        if (var_v1 > 0) {
            var_a2 = 1;
        }
        if (var_v1 < 0) {
            var_a2 = -1;
        }
    }
    racer->unk1E8 += var_a2;
    racer->y_rotation_offset = 0;
    racer->x_rotation_offset = 0;
    racer->z_rotation_offset = 0;
    func_800575EC(racerObj, racer);
    gCurrentRacerTransform.rotation.y_rotation = racerObj->segment.trans.rotation.y_rotation;
    gCurrentRacerTransform.rotation.x_rotation = racerObj->segment.trans.rotation.x_rotation;
    gCurrentRacerTransform.rotation.z_rotation = racerObj->segment.trans.rotation.z_rotation;
    gCurrentRacerTransform.x_position = 0.0f;
    gCurrentRacerTransform.y_position = 0.0f;
    gCurrentRacerTransform.z_position = 0.0f;
    gCurrentRacerTransform.scale = 1.0f;
    mtxf_from_transform(&mtx, &gCurrentRacerTransform);
    mtxf_transform_point(&mtx, 0.0f, 1.0f, 0.0f, &racer->ox2, &racer->oy2, &racer->oz2);
    gCurrentRacerInput = A_BUTTON;
    func_800535C4(racerObj, racer);
    handle_car_velocity_control(racer);
    func_80053750(racerObj, racer, updateRateF);
    racerObj->segment.object.animationID = 0;
    animFrame = racer->steerAngle;
    animFrame = animFrame >> 1;
    animFrame = 40 - animFrame;
    if (animFrame < 0) {
        animFrame = 0;
    }
    if (animFrame > 73) {
        animFrame = 73;
    }
    racerObj->segment.animFrame = animFrame;
    steerAngle = 10;
    if (racer->playerIndex != PLAYER_COMPUTER) {
        steerAngle = racer->steerAngle;
    } else {
        obj = racer->nodeCurrent;
        if (obj != NULL) {
            xDiff = obj->segment.trans.x_position - racerObj->segment.trans.x_position;
            yDiff = obj->segment.trans.y_position - racerObj->segment.trans.y_position;
            zDiff = obj->segment.trans.z_position - racerObj->segment.trans.z_position;
            if (sqrtf((xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff)) < 200.0) {
                nodes = obj->unk64->ai_node.nodeObj;
                for (i = 0; i < 4; i++) {
                    if (nodes[i] != NULL && racer->challengeMarker != nodes[i]) {
                        racer->challengeMarker = obj;
                        racer->nodeCurrent = nodes[i];
                        i = 4;
                    }
                }
                if (i != 5) {
                    racer->nodeCurrent = NULL;
                }
            } else {
                zDiff = racer->oz3;
                temp4 =
                    -((racer->ox3 * racerObj->segment.trans.x_position) + (zDiff * racerObj->segment.trans.z_position));
                var_f0 = (obj->segment.trans.x_position * racer->ox3) + (obj->segment.trans.z_position * zDiff) + temp4;
                steerAngle = var_f0;
                steerAngle /= 5;
            }
        }
    }
    racer->attackType = ATTACK_NONE;
    racer->spinout_timer = 0;
    var_f0 = (steerAngle * racer->velocity) / 360;
    var_f2 = 1.0f;
    racerObj->segment.x_velocity -= (racer->ox3 * var_f0);
    racerObj->segment.y_velocity -= (racer->oy3 * var_f0);
    racerObj->segment.z_velocity -= (racer->oz3 * var_f0);
    if (gCurrentPlayerIndex == PLAYER_COMPUTER) {
        var_f2 = 1.3f;
    }
    racer->unk19A += updateRate;
    if (racer->unk19A > 600) {
        racer->vehicleID = racer->vehicleIDPrev;
        racerObj->segment.trans.rotation.x_rotation = 0;
        racer->trickType = 0;
        if (racer->playerIndex >= 0) {
            objectMoved = TRUE;
        }
    }
    if (racer->groundedWheels == 0) {
        var_f2 = 0.1f;
        racer->trickType += updateRate;
        if (racer->trickType > 60) {
            racer->vehicleID = racer->vehicleIDPrev;
            racerObj->segment.trans.rotation.x_rotation = 0;
            racer->trickType = 0;
        }
    } else {
        racer->trickType = 0;
    }
    var_v0 = racer->unk198 - (racer->steerVisualRotation & 0xFFFF);
    if (var_v0 > 0x8000) {
        var_v0 -= 0xFFFF;
    }
    if (var_v0 < -0x8000) {
        var_v0 += 0xFFFF;
    }
    if ((var_v0 > 0x1000) || (var_v0 < -0x1000)) {
        var_f2 = 0.0f;
    }
    racer->steerVisualRotation += (var_v0 >> 3);
    racer->x_rotation_vel = 0;

    racerObj->segment.x_velocity -= racer->ox1 * var_f2;
    racerObj->segment.y_velocity -= racer->oy1 * var_f2;
    racerObj->segment.z_velocity -= racer->oz1 * var_f2;
    racerObj->segment.x_velocity -= racer->ox2 * 1.5;
    racerObj->segment.y_velocity -= racer->oy2 * 1.5;
    racerObj->segment.z_velocity -= racer->oz2 * 1.5;

    var_f0 = racer->velocity * racer->velocity * 0.002f;
    if (racer->velocity < 0.0f) {
        var_f0 = -var_f0;
    }
    racerObj->segment.x_velocity -= racer->ox1 * var_f0;
    racerObj->segment.y_velocity -= racer->oy1 * var_f0;
    racerObj->segment.z_velocity -= racer->oz1 * var_f0;

    var_f0 = racer->lateral_velocity * racer->lateral_velocity * 0.01f;
    if (racer->lateral_velocity < 0.0f) {
        var_f0 = -var_f0;
    }
    racerObj->segment.x_velocity -= racer->ox3 * var_f0;
    racerObj->segment.y_velocity -= racer->oy3 * var_f0;
    racerObj->segment.z_velocity -= racer->oz3 * var_f0;
    var_f0 = racer->unk34 * racer->unk34 * 0.01f;
    if (racer->unk34 < 0.0f) {
        var_f0 = -var_f0;
    }
    racerObj->segment.x_velocity -= racer->ox2 * var_f0;
    racerObj->segment.y_velocity -= racer->oy2 * var_f0;
    racerObj->segment.z_velocity -= racer->oz2 * var_f0;

    racer->unk10C = 0;
    racer->y_rotation_vel += ((gCurrentCarSteerVel - racer->y_rotation_vel) >> 3);
    racerObj->segment.trans.rotation.y_rotation = racer->steerVisualRotation + racer->y_rotation_vel;
    racer->z_rotation_vel += ((D_8011D558 - racer->z_rotation_vel) >> 3);
    racerObj->segment.trans.rotation.z_rotation = racer->x_rotation_vel + racer->z_rotation_vel;
    temp2 = racerObj->segment.x_velocity;
    temp3 = racerObj->segment.z_velocity;
    racer->unk1D2 = 0;
    moveObjResult =
        move_object(racerObj, temp2 * updateRateF, racerObj->segment.y_velocity * updateRateF, temp3 * updateRateF);
    if ((moveObjResult) && (gCurrentPlayerIndex != -1)) {
        objectMoved = TRUE;
    }
    if (gCurrentPlayerIndex == PLAYER_COMPUTER) {
        onscreen_ai_racer_physics(racerObj, racer, updateRate);
    } else {
        func_80054FD0(racerObj, racer, updateRate);
    }
    var_f0 = (racerObj->segment.trans.x_position - prevXPos) * (1 / updateRateF);
    racerObj->segment.y_velocity = (racerObj->segment.trans.y_position - prevYPos) * (1 / updateRateF);
    temp3 = (racerObj->segment.trans.z_position - prevZPos) * (1 / updateRateF);
    racerObj->segment.z_velocity = temp3;
    racerObj->segment.x_velocity = var_f0;
    gCurrentRacerTransform.rotation.y_rotation = -racerObj->segment.trans.rotation.y_rotation;
    gCurrentRacerTransform.rotation.x_rotation = -racerObj->segment.trans.rotation.x_rotation;
    gCurrentRacerTransform.rotation.z_rotation = 0;
    gCurrentRacerTransform.scale = 1.0f;
    gCurrentRacerTransform.x_position = 0.0f;
    gCurrentRacerTransform.y_position = 0.0f;
    gCurrentRacerTransform.z_position = 0.0f;
    gCurrentRacerTransform.scale = 1.0f;
    mtxf_from_inverse_transform(&mtx, &gCurrentRacerTransform);
    mtxf_transform_point(&mtx, racerObj->segment.x_velocity, racerObj->segment.y_velocity, racerObj->segment.z_velocity,
                         &racer->lateral_velocity, &racer->unk34, &racer->velocity);
    second_racer_camera_update(racerObj, racer, CAMERA_LOOP, updateRateF);
    if (racerObj->unk60 != NULL && racer->vehicleIDPrev == VEHICLE_CAR && racerObj->unk60->unk0 >= 4) {
        obj = racerObj->unk60->unk4[2];
        obj->segment.trans.rotation.y_rotation = 0;
        obj = racerObj->unk60->unk4[3];
        obj->segment.trans.rotation.y_rotation = 0;
    }
    if (objectMoved) {
        racer->vehicleID = racer->vehicleIDPrev;
        func_800230D0(racerObj, racer);
    }
}

/**
 * Handles the camera movement when the player is on a loop-the-loop.
 * This happens in Walrus Cove and Darkmoon Caverns.
 * The camera's rotation follows the players exactly, in order to stay levelled.
 */
void update_camera_loop(f32 updateRateF, Object *obj, Object_Racer *racer) {
    s32 UpdateRate;
    UNUSED f32 pad;
    s32 segmentIndex;
    s32 angle;
    f32 targetBoomLength;
    f32 deltaX;
    f32 deltaY;
    f32 deltaZ;
    MtxF mtx;
    s32 angleDiff;

    UpdateRate = (s32) updateRateF;
    targetBoomLength = 120.0f;
    if (gRaceStartTimer > 60) {
        targetBoomLength += (gRaceStartTimer - 60) * 4.0f;
    }
    racer->cameraYaw = 0x8000 - racer->steerVisualRotation;
    if (cam_get_viewport_layout() == VIEWPORT_LAYOUT_2_PLAYERS) {
        targetBoomLength = 160.0f;
    }
    // A little bit of indecisiveness.
    if (gCameraObject->zoom == ZOOM_FAR) {
        targetBoomLength += 35.0f;
    }
    if (gCameraObject->zoom == ZOOM_FAR) {
        targetBoomLength -= 35.0f;
    }
    gCameraObject->boomLength += (targetBoomLength - gCameraObject->boomLength) * 0.125;

    gCurrentRacerTransform.rotation.y_rotation = 0x8000 - gCameraObject->trans.rotation.y_rotation;
    gCurrentRacerTransform.rotation.x_rotation = -gCameraObject->trans.rotation.x_rotation;
    gCurrentRacerTransform.rotation.z_rotation = 0;
    gCurrentRacerTransform.x_position = 0.0f;
    gCurrentRacerTransform.y_position = 0.0f;
    gCurrentRacerTransform.z_position = 0.0f;
    gCurrentRacerTransform.scale = 1.0f;
    mtxf_from_transform(&mtx, &gCurrentRacerTransform);

    mtxf_transform_point(&mtx, 0.0f, 0.0f, gCameraObject->boomLength, &deltaX, &deltaY, &deltaZ);
    gCameraObject->trans.x_position = obj->segment.trans.x_position + deltaX;
    gCameraObject->trans.y_position = obj->segment.trans.y_position + deltaY;
    gCameraObject->trans.z_position = obj->segment.trans.z_position + deltaZ;

    mtxf_transform_point(&mtx, 0.0f, sins_f(0x800) * gCameraObject->boomLength, 0.0f, &deltaX, &deltaY, &deltaZ);
    gCameraObject->trans.x_position += deltaX;
    gCameraObject->trans.y_position += deltaY;
    gCameraObject->trans.z_position += deltaZ;

    angleDiff = (u16) (-obj->segment.trans.rotation.z_rotation);
    angle = angleDiff - ((u16) gCameraObject->trans.rotation.z_rotation);
    WRAP(angle, -0x8000, 0x8000);
    gCameraObject->trans.rotation.z_rotation += ((angle * UpdateRate) >> 4);
    angleDiff = -obj->segment.trans.rotation.x_rotation;
    angle = angleDiff - (u16) gCameraObject->trans.rotation.x_rotation;
    WRAP(angle, -0x8000, 0x8000);
    gCameraObject->trans.rotation.x_rotation += ((angle * UpdateRate) >> 4);
    gCameraObject->trans.rotation.y_rotation = racer->cameraYaw;
    segmentIndex = get_level_segment_index_from_position(
        gCameraObject->trans.x_position, gCameraObject->trans.y_position, gCameraObject->trans.z_position);
    if (segmentIndex != SEGMENT_NONE) {
        gCameraObject->cameraSegmentID = segmentIndex;
    }
    racer->cameraYaw = gCameraObject->trans.rotation.y_rotation;
    gCameraObject->trans.x_position += gCameraObject->x_velocity;
    gCameraObject->trans.y_position += gCameraObject->y_velocity;
    gCameraObject->trans.z_position += gCameraObject->z_velocity;
}

/**
 * Updates the carpet vehicle that Taj uses during the overworld race challenges.
 */
void update_carpet(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer) {
    s16 animFrame;

    if (racer->vehicleSound) {
        racer_sound_free(obj);
    }
    if (is_taj_challenge() && racer->vehicleID == VEHICLE_CARPET) {
        obj->interactObj->flags = INTERACT_FLAGS_NONE;
    }
    animFrame = obj->segment.animFrame;
    racer->vehicleID = VEHICLE_CARPET;
    func_80049794(updateRate, updateRateF, obj, racer);
    racer->vehicleID = racer->vehicleIDPrev;
    obj->segment.object.animationID = 0;
    if (racer->vehicleID == VEHICLE_CARPET) {
        if (racer->unk154 != NULL) {
            racer->unk154->segment.trans.x_position = obj->segment.trans.x_position;
            racer->unk154->segment.trans.y_position = obj->segment.trans.y_position;
            racer->unk154->segment.trans.z_position = obj->segment.trans.z_position;
            racer->unk154->segment.object.segmentID = obj->segment.object.segmentID;
            racer->unk154->segment.trans.rotation.y_rotation = obj->segment.trans.rotation.y_rotation;
            racer->unk154->segment.trans.rotation.x_rotation = obj->segment.trans.rotation.x_rotation;
            racer->unk154->segment.trans.rotation.z_rotation = obj->segment.trans.rotation.z_rotation;
            obj->segment.object.animationID = 0;
            obj->segment.animFrame = animFrame + updateRate;
            func_80061C0C(obj);
        }
    }
}

/**
 * Initialise the basic properties of each racer object. If it's tied to a human player,
 * will also initialise a camera object.
 */
void obj_init_racer(Object *obj, LevelObjectEntry_Racer *racer) {
    Object_Racer *tempRacer;
    ActivePlayers player;
    s32 i;

    unused_8011D53C = 0;
    tempRacer = &obj->unk64->racer;
    obj->segment.trans.rotation.y_rotation = racer->angleY;
    obj->segment.trans.rotation.x_rotation = racer->angleX;
    obj->segment.trans.rotation.z_rotation = racer->angleZ;
    player = racer->playerIndex;
    tempRacer->countLap = 0;
    tempRacer->stretch_height = 1.0f;
    tempRacer->stretch_height_cap = 1.0f;
    // Decide which player ID to assign to this object. Human players get a value from 0-3.
    // Computer players will be -1.
    if (player >= PLAYER_ONE && player <= PLAYER_FOUR) {
        if (func_8000E158()) {
            player = 1 - player;
        }
        tempRacer->playerIndex = player;
    } else {
        tempRacer->playerIndex = PLAYER_COMPUTER;
    }
    tempRacer->steerVisualRotation = obj->segment.trans.rotation.y_rotation;
    tempRacer->x_rotation_vel = obj->segment.trans.rotation.z_rotation;
    tempRacer->unkC4 = 0.5f;
    if (1) {} // Fakematch
    tempRacer->cameraYaw = tempRacer->steerVisualRotation;
    tempRacer->unkD8.x = obj->segment.trans.x_position;
    tempRacer->unkD8.y = obj->segment.trans.y_position + 30.0f;
    tempRacer->unkD8.z = obj->segment.trans.z_position;
    tempRacer->unkE4.x = obj->segment.trans.x_position;
    tempRacer->unkE4.y = obj->segment.trans.y_position + 30.0f;
    tempRacer->unkE4.z = obj->segment.trans.z_position;
    tempRacer->unkF0.x = obj->segment.trans.x_position;
    tempRacer->unkF0.y = obj->segment.trans.y_position + 30.0f;
    tempRacer->unkF0.z = obj->segment.trans.z_position;
    tempRacer->unkFC.x = obj->segment.trans.x_position;
    tempRacer->unkFC.y = obj->segment.trans.y_position + 30.0f;
    tempRacer->unkFC.z = obj->segment.trans.z_position;
    tempRacer->prev_x_position = obj->segment.trans.x_position;
    tempRacer->prev_y_position = obj->segment.trans.y_position;
    tempRacer->prev_z_position = obj->segment.trans.z_position;
    obj->interactObj->x_position = obj->segment.trans.x_position;
    obj->interactObj->y_position = obj->segment.trans.y_position;
    obj->interactObj->z_position = obj->segment.trans.z_position;
    tempRacer->groundedWheels = 3;
    tempRacer->unk1AA = 1;
    tempRacer->racePosition = 1;
    tempRacer->miscAnimCounter = tempRacer->playerIndex * 5;
    tempRacer->checkpoint_distance = 1.0f;
    tempRacer->cameraIndex = 0;
    tempRacer->magnetSoundMask = NULL;
    tempRacer->shieldSoundMask = NULL;
    tempRacer->bananaSoundMask = NULL;
    tempRacer->weaponSoundMask = NULL;
    tempRacer->unk220 = 0;
    tempRacer->unk21C = NULL;
    if (tempRacer->playerIndex != PLAYER_COMPUTER && gTajInteractStatus == TAJ_WANDER) {
        set_active_camera(player);
        gCameraObject = cam_get_active_camera_no_cutscenes();
        gCameraObject->trans.rotation.z_rotation = 0;
        gCameraObject->trans.rotation.x_rotation = 0x400;
        gCameraObject->trans.rotation.y_rotation = tempRacer->cameraYaw;
        gCameraObject->mode = CAMERA_CAR;
        gCameraObject->unk3C = 0xFF;
        gCameraObject->unk3D = 0xFF;
        gCameraObject->unk3E = 0xFF;
        gCameraObject->unk3F = 0xFF;
        gCameraObject->cam_unk_18 = 0.0f;
        update_player_camera(obj, tempRacer, 1.0f);
    }
    if (gTajInteractStatus == TAJ_WANDER) {
        gRacerDialogueCamera = FALSE;
        gDialogueCameraAngle = 0;
        gRacerInputBlocked = FALSE;
    }
    obj->interactObj->flags = INTERACT_FLAGS_SOLID | INTERACT_FLAGS_UNK_0004;
    obj->interactObj->unk11 = 0;
    obj->interactObj->hitboxRadius = 15;
    obj->interactObj->pushForce = 20;
    tempRacer->unk1EE = 0;
    if (gTajInteractStatus == TAJ_WANDER) {
        tempRacer->transparency = 255;
    }
    D_8011D560 = 0;
    D_8011D544 = 300.0f;
    tempRacer->unk1C9 = 6;
    tempRacer->unk1C6 = 100;
    D_8011D580 = 0;

    // clang-format off
    // This needs to be on one line to match.
    for (i = 0; i < 4; i++) { D_8011D58C[i] = 0; }
    // clang-format on
    if (1) {}
    if (1) {} // Fakematch
    increment_ai_behaviour_chances(NULL, NULL, 0);
    gRacerDialogueCamera = i;
    gStartBoostTime = 0;
    tempRacer->lightFlags = 0;
}

/**
 * Main function for handling everything related to the player controlled racer object.
 * Branches off into a different function if the player becomes computer controlled. (Finishing a race)
 */
void update_player_racer(Object *obj, s32 updateRate) {
    s32 tempVar;
    s32 checkpointCount;
    s32 context;
    Object *tempObj;
    f32 updateRateF;
    f32 waterHeight;
    Object_Racer *tempRacer;
    f32 xTemp;
    f32 yTemp;
    f32 zTemp;
    f32 lastCheckpointDist;
    f32 playerIDF;
    LevelHeader *header;
    CheckpointNode *checkpointNode;
    s32 playerID;
    f32 stretch;
    s32 i;
    struct LevelObjectEntryCommon newObject;

    gNumViewports = cam_get_viewport_layout() + 1;
    gCurrentSurfaceType = SURFACE_DEFAULT;
    gRaceStartTimer = get_race_countdown();
    updateRateF = updateRate;
    tempRacer = &obj->unk64->racer;
    // Cap all of the velocities on the different axes.
    // Unfortunately, Rareware didn't appear to use a clamp macro here, which would've saved a lot of real estate.
    if (obj->segment.x_velocity > 50.0) {
        obj->segment.x_velocity = 50.0f;
    }
    if (obj->segment.y_velocity > 50.0) {
        obj->segment.y_velocity = 50.0f;
    }
    if (obj->segment.z_velocity > 50.0) {
        obj->segment.z_velocity = 50.0f;
    }
    if (obj->segment.x_velocity < -50.0) {
        obj->segment.x_velocity = -50.0f;
    }
    if (obj->segment.y_velocity < -50.0) {
        obj->segment.y_velocity = -50.0f;
    }
    if (obj->segment.z_velocity < -50.0) {
        obj->segment.z_velocity = -50.0f;
    }
    if (tempRacer->velocity > 50.0) {
        tempRacer->velocity = 50.0f;
    }
    if (tempRacer->lateral_velocity > 50.0) {
        tempRacer->lateral_velocity = 50.0f;
    }
    if (tempRacer->velocity < -50.0) {
        tempRacer->velocity = -50.0f;
    }
    if (tempRacer->lateral_velocity < -50.0) {
        tempRacer->lateral_velocity = -50.0f;
    }
    if (tempRacer->checkpoint_distance < -1.0) {
        tempRacer->checkpoint_distance = -1.0f;
    }
    if (tempRacer->checkpoint_distance > 2.0) {
        tempRacer->checkpoint_distance = 2.0f;
    }
    if (tempRacer->unk1FE == 1) {
        tempRacer->unk1F1 = 0;
    }
    // PAL moves 20% faster.
    if (osTvType == OS_TV_TYPE_PAL) {
        updateRateF *= 1.2;
    }
    tempRacer->unk1F6 -= updateRate;
    if (tempRacer->unk1F6 < 0) {
        tempRacer->unk1F6 = 0;
    }
    obj->particleEmittersEnabled = OBJ_EMIT_NONE;
    if (tempRacer->unk201 > 0) {
        tempRacer->unk201 -= updateRate;
    } else {
        tempRacer->unk201 = 0;
    }
    header = get_current_level_header();
    gCurrentCourseHeight = header->course_height;
    tempRacer->throttleReleased = FALSE;
    if (tempRacer->playerIndex == PLAYER_COMPUTER) {
        update_AI_racer(obj, tempRacer, updateRate, updateRateF);
    } else {
        // Print player 1's coordinates to the screen if the debug cheat is enabled.
        if (gRaceStartTimer == 0 && tempRacer->playerIndex == PLAYER_ONE) {
            if (get_filtered_cheats() & CHEAT_PRINT_COORDS) {
                render_printf(gRacerDebugCoords, obj->segment.trans.x_position, obj->segment.trans.y_position,
                              obj->segment.trans.z_position);
            }
        }
        set_render_printf_background_colour(0, 0, 0, 128);
        if (is_taj_challenge()) {
            gDialogueCameraAngle = 0;
        }
        context = get_game_mode();
        if (gRaceStartTimer == 0) {
            if (D_8011D544 > 0.0) {
                D_8011D544 -= updateRateF;
            } else {
                D_8011D544 = 0.0f;
            }
        } else {
            tempRacer->unk1C6 = rand_range(-60, 60) + 120;
        }
        if (tempRacer->unk18C > 0) {
            tempRacer->unk18C -= updateRate;
        } else {
            tempRacer->unk18C = 0;
        }
        gCurrentRacerMiscAssetPtr = (f32 *) get_misc_asset(ASSET_MISC_RACER_WEIGHT);
        gCurrentRacerWeightStat = gCurrentRacerMiscAssetPtr[tempRacer->characterId] * 0.45;
        if (tempRacer->bubbleTrapTimer > 0) {
            gCurrentRacerWeightStat = -0.02f;
        }
        gCurrentRacerMiscAssetPtr = (f32 *) get_misc_asset(ASSET_MISC_RACER_HANDLING);
        gCurrentRacerHandlingStat = gCurrentRacerMiscAssetPtr[tempRacer->characterId];
        gCurrentRacerMiscAssetPtr = (f32 *) get_misc_asset(ASSET_MISC_RACER_UNUSED_11);
        gCurrentRacerUnusedMiscAsset11 = gCurrentRacerMiscAssetPtr[tempRacer->characterId];
        if (tempRacer->unk1FE == 3) {
            gCurrentRacerWeightStat *= (f32) tempRacer->unk1FF / 256;
        }
        if (tempRacer->unk1FE == 1) {
            gCurrentRacerWeightStat -= (gCurrentRacerWeightStat * tempRacer->unk1FF) / 128;
            if (tempRacer->bubbleTrapTimer > 0) {
                gCurrentRacerWeightStat = -gCurrentRacerWeightStat;
            }
        }
        if (tempRacer->unk1FE == 2) {
            tempRacer->unk84 += ((sins_f((tempRacer->unk1FF << 8)) * 4.0f) - tempRacer->unk84) * 0.0625 * updateRateF;
            tempRacer->unk88 += ((coss_f((tempRacer->unk1FF << 8)) * 4.0f) - tempRacer->unk88) * 0.0625 * updateRateF;
        } else {
            tempRacer->unk84 -= tempRacer->unk84 * 0.0625 * updateRateF;
            tempRacer->unk88 -= tempRacer->unk88 * 0.0625 * updateRateF;
        }
        gCurrentRacerMiscAssetPtr = (f32 *) get_misc_asset(obj->segment.header->unk5C);
        D_8011D568 = (f32 *) get_misc_asset(obj->segment.header->unk5D);

        if (obj->segment.y_velocity < 4.0 && (tempRacer->groundedWheels > 2 || tempRacer->buoyancy != 0.0)) {
            tempRacer->unk1F1 = 0;
        }
        xTemp = obj->segment.trans.x_position;
        yTemp = obj->segment.trans.y_position;
        zTemp = obj->segment.trans.z_position;
        if (tempRacer->unk1B2 > 0) {
            tempRacer->unk1B2 -= updateRate;
            if (tempRacer->unk1B2 < 0) {
                tempRacer->unk1B2 = 0;
            }
        }
        set_active_camera(tempRacer->playerIndex);
        gCameraObject = cam_get_active_camera_no_cutscenes();
        tempRacer->miscAnimCounter++; //!@Delta
        gCurrentPlayerIndex = tempRacer->playerIndex;
        if (tempRacer->raceFinished == TRUE || context == GAMEMODE_MENU) {
            tempRacer->unk1CA = 1;
            tempRacer->playerIndex = PLAYER_COMPUTER;
            tempRacer->unk1C9 = 0;
            if (tempRacer->shieldTimer > 5) {
                tempRacer->shieldTimer = 5;
            }
        }
        tempVar = tempRacer->playerIndex;
        if (tempRacer->playerIndex != PLAYER_COMPUTER) {
            if (tempRacer->exitObj == 0) {
                if (func_8000E158()) {
                    tempVar = 1 - tempVar;
                }
                // Cap the joystick tilt and write the button inputs to the current buffer.
                gCurrentStickX = input_clamp_stick_x(tempVar);
                // Flip the steering for adventure 2.
                if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
                    gCurrentStickX = -gCurrentStickX;
                }
                gCurrentStickY = input_clamp_stick_y(tempVar);
                gCurrentRacerInput = input_held(tempVar);
                gCurrentButtonsPressed = input_pressed(tempVar);
                gCurrentButtonsReleased = input_released(tempVar);
            } else {
                racer_enter_door(tempRacer, updateRate);
            }
        } else {
            racer_AI_pathing_inputs(obj, tempRacer, updateRate);
        }
        // Set the value that decides whether to get an empowered boost.
        if (!(gCurrentRacerInput & A_BUTTON)) {
            tempRacer->throttleReleased = TRUE;
        }
        if (check_if_showing_cutscene_camera() || gRaceStartTimer == 100 || tempRacer->unk1F1 || gRacerInputBlocked ||
            tempRacer->approachTarget || tempRacer->bubbleTrapTimer > 0) {
            gCurrentStickX = 0;
            gCurrentStickY = 0;
            gCurrentRacerInput = 0;
            gCurrentButtonsPressed = 0;
            gCurrentButtonsReleased = 0;
            tempRacer->steerAngle = 0;
        }
        if (tempRacer->bubbleTrapTimer > 0) {
            tempRacer->bubbleTrapTimer -= updateRate;
            tempRacer->velocity *= 0.9f;      //!@Delta
            obj->segment.x_velocity *= 0.87f; //!@Delta
            if (obj->segment.y_velocity > 2.0f) {
                obj->segment.y_velocity = 2.0f;
            }
            obj->segment.z_velocity *= 0.87f; //!@Delta
        }
        if (tempRacer->unk206 > 0) {
            tempRacer->unk18A = tempRacer->unk206;
            tempRacer->unk206 -= updateRate;
        }
        if (tempRacer->unk18A > 0) {
            tempVar = tempRacer->unk18A & 0xF;
            tempRacer->unk18A -= updateRate;
            if (tempVar < (tempRacer->unk18A & 0xF)) {
                tempRacer->unk1D1 = rand_range(-80, 80);
            }
            gCurrentStickX += tempRacer->unk1D1;
        } else {
            tempRacer->unk18A = 0;
        }
        if (tempRacer->magnetTimer) {
            racer_activate_magnet(obj, tempRacer, updateRate);
        }
        // Zero out input before the race has begun.
        if (gRaceStartTimer && (header->race_type == RACETYPE_DEFAULT ||
                                header->race_type == RACETYPE_HORSESHOE_GULCH || header->race_type == RACETYPE_BOSS)) {
            gCurrentStickX = 0;
            gCurrentStickY = 0;
            gCurrentRacerInput = 0;
        }
        // Handle the race timer if it's currently active.
        if (gRaceStartTimer == 0 && header->laps > (tempRacer->countLap)) {
            // Keep it under 10 minutes.
            if (tempRacer->lap_times[tempRacer->countLap] < normalise_time(36000) - updateRate) {
                tempRacer->lap_times[tempRacer->countLap] += updateRate;
            } else {
                tempRacer->lap_times[tempRacer->countLap] = normalise_time(36000);
            }
        }
        // Assign a camera to human players.
        if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
            gCameraObject = cam_get_active_camera_no_cutscenes();
        }
        gRacerWaveCount = func_8002B0F4(obj->segment.object.segmentID, obj->segment.trans.x_position,
                                        obj->segment.trans.z_position, &gRacerCurrentWave);
        if (gRacerWaveCount) {
            for (i = 0; i < gRacerWaveCount; i++) {
                if (gRacerCurrentWave[i]->type == WATER_UNK_F) {
                    if (gRacerCurrentWave[i]->waveHeight < gCurrentCourseHeight) {
                        gCurrentCourseHeight = gRacerCurrentWave[i]->waveHeight;
                    }
                }
            }
        }
        if (tempRacer->vehicleID != VEHICLE_HOVERCRAFT) {
            waterHeight = -10000.0f;
            gRacerWaveType = get_wave_properties(obj->segment.trans.y_position, &waterHeight, &gCurrentRacerWaterPos);
            if (gRacerWaveType) {
                if (obj->segment.trans.y_position - 5.0f < waterHeight) {
                    tempRacer->waterTimer = 5;
                    tempRacer->buoyancy = waterHeight - (obj->segment.trans.y_position - 5.0f);
                } else {
                    tempRacer->buoyancy = 0.0f;
                }
            } else {
                if (tempRacer->waterTimer > 0) {
                    tempRacer->waterTimer--;
                } else {
                    tempRacer->buoyancy = 0.0f;
                }
            }
            if (tempRacer->waterTimer > 0 && obj->segment.trans.y_position < waterHeight + 5.0f) {
                obj->interactObj->flags |= INTERACT_FLAGS_UNK_0010;
            } else {
                obj->interactObj->flags &= ~INTERACT_FLAGS_UNK_0010;
            }
        }
        func_8002ACC8(0);
        switch (tempRacer->vehicleID) {
            case VEHICLE_CAR:
                func_8004F7F4(updateRate, updateRateF, obj, tempRacer);
                break;
            case VEHICLE_LOOPDELOOP:
                func_8004CC20(updateRate, updateRateF, obj, tempRacer);
                break;
            case VEHICLE_HOVERCRAFT:
                func_80046524(updateRate, updateRateF, obj, tempRacer);
                break;
            case VEHICLE_PLANE:
                func_80049794(updateRate, updateRateF, obj, tempRacer);
                break;
            case VEHICLE_FLYING_CAR: /* fall through */
            case VEHICLE_CARPET:
                update_carpet(updateRate, updateRateF, obj, tempRacer);
                break;
            case VEHICLE_TRICKY:
                update_tricky(updateRate, updateRateF, obj, tempRacer, &gCurrentRacerInput, &gCurrentButtonsPressed,
                              &gRaceStartTimer);
                break;
            case VEHICLE_BLUEY:
                update_bluey(updateRate, updateRateF, obj, tempRacer, &gCurrentRacerInput, &gCurrentButtonsPressed,
                             &gRaceStartTimer);
                break;
            case VEHICLE_SMOKEY: /* fall through */
            case VEHICLE_PTERODACTYL:
                update_smokey(updateRate, updateRateF, obj, tempRacer, &gCurrentRacerInput, &gCurrentStickX,
                              &gRaceStartTimer);
                break;
            case VEHICLE_BUBBLER:
                update_bubbler(updateRate, updateRateF, obj, tempRacer, &gCurrentRacerInput, &gCurrentButtonsPressed,
                               &gRaceStartTimer);
                break;
            case VEHICLE_WIZPIG:
                update_wizpig(updateRate, updateRateF, obj, tempRacer, &gCurrentRacerInput, &gCurrentButtonsPressed,
                              &gRaceStartTimer);
                break;
            case VEHICLE_ROCKET:
                update_rocket(updateRate, updateRateF, obj, tempRacer, &gCurrentRacerInput, &gCurrentButtonsPressed,
                              &gRaceStartTimer);
                break;
        }
        if (tempRacer->magnetTimer == 0) {
            if (tempRacer->magnetSoundMask) {
                sndp_stop(tempRacer->magnetSoundMask);
                tempRacer->magnetSoundMask = NULL;
            }
        }
        playerID = header->playerIndex;
        if (playerID) {
            playerIDF = -(f32) playerID;
            CLAMP(tempRacer->velocity, playerIDF, playerID);
        }
        if (context != GAMEMODE_MENU || func_8000E148()) {
            racer_sound_update(obj, gCurrentButtonsPressed, gCurrentRacerInput, updateRate);
        }
        lastCheckpointDist = tempRacer->checkpoint_distance;
        tempVar = func_800185E4(tempRacer->checkpoint, obj, xTemp, yTemp, zTemp, &tempRacer->checkpoint_distance,
                                &tempRacer->unk1C8);
        if (tempVar == -100) {
            func_8005C270(tempRacer);
        }
        checkpointNode = find_next_checkpoint_node(tempRacer->checkpoint, tempRacer->unk1C8);
        if (tempRacer->playerIndex == PLAYER_COMPUTER && checkpointNode->unk36[tempRacer->unk1CA] == 5 &&
            tempRacer->waterTimer) {
            tempRacer->unk1C8 = 1;
        }
        if (checkpointNode->unk36[tempRacer->unk1CA] == 6) {
            tempRacer->lap = header->laps + 1;
        }
        if (tempVar == 0) {
            if (tempRacer->playerIndex == PLAYER_COMPUTER && checkpointNode->unk36[tempRacer->unk1CA] == 2) {
                tempRacer->unk1C8 = 1;
            }
            checkpointCount = get_checkpoint_count();
            tempRacer->checkpoint++;
            if (tempRacer->checkpoint >= checkpointCount) {
                tempRacer->checkpoint = 0;
                if (tempRacer->courseCheckpoint > 0) {
                    if (tempRacer->lap < 120) {
                        tempRacer->lap++;
                    }
                }
                if (tempRacer->playerIndex != PLAYER_COMPUTER && tempRacer->lap + 1 == header->laps && !D_8011D580 &&
                    get_current_level_race_type() == RACETYPE_DEFAULT) {
                    music_tempo_set_relative(1.12f);
                    D_8011D580 = 1;
                }
            }
            if (is_taj_challenge()) {
                if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
                    checkpointNode = find_next_checkpoint_node(tempRacer->checkpoint, tempRacer->unk1C8);
                    if (!tempRacer->challengeMarker) {
                        newObject.x = 0;
                        newObject.y = 0;
                        newObject.z = 0;
                        newObject.objectID = ASSET_OBJECT_ID_CHECKARROW;
                        newObject.size = sizeof(LevelObjectEntryCommon);
                        tempRacer->challengeMarker = spawn_object(&newObject, OBJECT_SPAWN_UNK01);
                        if (tempRacer->challengeMarker) {
                            tempRacer->challengeMarker->segment.level_entry = NULL;
                            tempRacer->challengeMarker->segment.object.opacity = 128;
                        }
                    }
                    if (tempRacer->challengeMarker) {
                        tempRacer->challengeMarker->segment.trans.x_position =
                            checkpointNode->obj->segment.trans.x_position;
                        tempRacer->challengeMarker->segment.trans.y_position =
                            checkpointNode->obj->segment.trans.y_position;
                        if (tempRacer->vehicleID == VEHICLE_CAR) {
                            tempRacer->challengeMarker->segment.trans.y_position -= 30.0;
                        }
                        tempRacer->challengeMarker->segment.trans.z_position =
                            checkpointNode->obj->segment.trans.z_position;
                        tempRacer->challengeMarker->segment.trans.rotation.y_rotation =
                            checkpointNode->obj->segment.trans.rotation.y_rotation;
                        tempRacer->challengeMarker->segment.trans.rotation.x_rotation =
                            checkpointNode->obj->segment.trans.rotation.x_rotation;
                        tempRacer->challengeMarker->segment.object.segmentID =
                            checkpointNode->obj->segment.object.segmentID;
                    }
                }
            }
            if (tempRacer->courseCheckpoint < (header->laps + 3) * checkpointCount) {
                tempRacer->courseCheckpoint++;
            }
            tempRacer->unk1A8 = 10000;
        } else {
            if (tempRacer->playerIndex == PLAYER_COMPUTER && lastCheckpointDist < tempRacer->checkpoint_distance) {
                tempRacer->checkpoint_distance = lastCheckpointDist;
            }
            tempRacer->unk1A8 = tempVar;
        }
        if (is_taj_challenge()) {
            if (tempRacer->challengeMarker) {
                tempRacer->challengeMarker->segment.animFrame += 8 * updateRate;
            }
            if (tempRacer->unk1BA > 400 || tempRacer->unk1BA < -400) {
                mode_end_taj_race(CHALLENGE_END_OOB);
            }
        }
        func_80018CE0(obj, xTemp, yTemp, zTemp, updateRate);
        func_80059208(obj, tempRacer, updateRate);
        if (tempRacer->raceFinished == TRUE) {
            if (tempRacer->unk1D9 < 60) {
                tempRacer->unk1D9 += updateRate;
            }
        }
        if (tempRacer->unk188 > 0) {
            drop_bananas(obj, tempRacer, tempRacer->unk188);
        }
        tempRacer->playerIndex = gCurrentPlayerIndex;
        update_player_camera(obj, tempRacer, updateRateF);
        gRacerDialogueCamera = FALSE;
        if (tempRacer->approachTarget) {
            tempRacer->approachTarget = NULL;
            tempRacer->velocity = 0.0f;
            tempRacer->lateral_velocity = 0.0f;
        }
        if (tempRacer->stretch_height <= tempRacer->stretch_height_cap) {
            stretch = 0.02f;
        } else {
            stretch = -0.02f;
        }
        tempRacer->stretch_height +=
            (((tempRacer->stretch_height_cap - tempRacer->stretch_height) * 0.125) + stretch) * updateRateF;
        if ((stretch < 0.0f && tempRacer->stretch_height <= tempRacer->stretch_height_cap) ||
            (stretch > 0.0f && tempRacer->stretch_height >= tempRacer->stretch_height_cap)) {
            tempRacer->stretch_height = tempRacer->stretch_height_cap;
            tempRacer->stretch_height_cap = 1.0f;
        }

        tempVar = ((tempRacer->headAngleTarget - tempRacer->headAngle) * updateRate) >> 3;
        CLAMP(tempVar, -0x800, 0x800);
#ifdef ANTI_TAMPER
        if (gAntiPiracyHeadroll) {
            tempRacer->headAngle += gAntiPiracyHeadroll;
        } else {
            tempRacer->headAngle += tempVar;
        }
#else
        tempRacer->headAngle += tempVar;
#endif
        if ((gCurrentButtonsPressed & R_TRIG) && tempRacer->tapTimerR) {
            tempRacer->tappedR = TRUE;
            tempRacer->tapTimerR = 0;
        } else if (gCurrentButtonsPressed & R_TRIG) {
            tempRacer->tapTimerR = 22;
        }
        if (tempRacer->tapTimerR > 0) {
            tempRacer->tapTimerR -= updateRate;
        } else {
            tempRacer->tapTimerR = 0;
        }
        if (tempRacer->shieldTimer > 0) {
            if (tempRacer->shieldTimer > 60) {
                if (tempRacer->shieldSoundMask) {
                    audspat_point_set_position(tempRacer->shieldSoundMask, obj->segment.trans.x_position,
                                               obj->segment.trans.y_position, obj->segment.trans.z_position);
                } else if (tempRacer->vehicleSound) {
                    audspat_play_sound_at_position(SOUND_SHIELD, obj->segment.trans.x_position,
                                                   obj->segment.trans.y_position, obj->segment.trans.z_position,
                                                   AUDIO_POINT_FLAG_1, &tempRacer->shieldSoundMask);
                }
            } else if (tempRacer->shieldSoundMask) {
                audspat_point_stop(tempRacer->shieldSoundMask);
                tempRacer->shieldSoundMask = NULL;
            }
            tempRacer->shieldTimer -= updateRate;
            if (tempRacer->shieldTimer <= 0) {
                tempRacer->shieldType = SHIELD_NONE;
            }
        }
        if (tempRacer->bananaSoundMask) {
            audspat_point_set_position(tempRacer->bananaSoundMask, obj->segment.trans.x_position,
                                       obj->segment.trans.y_position, obj->segment.trans.z_position);
        }
        if (is_in_time_trial() && tempRacer->playerIndex == PLAYER_ONE && gRaceStartTimer == 0) {
            timetrial_ghost_write(obj, updateRate);
        }
        if (tempRacer->soundMask) {
            audspat_point_set_position(tempRacer->soundMask, obj->segment.trans.x_position,
                                       obj->segment.trans.y_position, obj->segment.trans.z_position);
        }
        gRacerInputBlocked = 0;
        if (tempRacer->unk150 && gRaceStartTimer == 0) {
            s8 *yAsset;
            tempRacer->unk150->segment.trans.x_position = obj->segment.trans.x_position;
            yAsset = (s8 *) get_misc_asset(ASSET_MISC_0);

            tempRacer->unk150->segment.trans.y_position =
                obj->segment.trans.y_position + yAsset[tempRacer->characterId];
            tempRacer->unk150->segment.trans.z_position = obj->segment.trans.z_position;
            tempRacer->unk150->segment.trans.scale = obj->segment.object.distanceToCamera / 265.0f;
            if (obj->segment.object.distanceToCamera < 1500.0 || get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
                tempObj = tempRacer->unk150;
                tempObj->segment.trans.flags |= OBJ_FLAGS_INVISIBLE;
            }
            if (tempRacer->unk150->segment.trans.scale < 1.0) {
                tempRacer->unk150->segment.trans.scale = 1.0f;
            }
            tempRacer->unk150 = NULL;
        }
        tempRacer->unk1FE = -1;
        set_racer_tail_lights(tempRacer);
        if (tempRacer->delaySoundID) {
            if (tempRacer->delaySoundTimer > updateRate) {
                tempRacer->delaySoundTimer -= updateRate;
            } else {
                tempRacer->delaySoundTimer = 0;
                if (tempRacer->playerIndex == PLAYER_COMPUTER) {
                    audspat_play_sound_at_position(tempRacer->delaySoundID, obj->segment.trans.x_position,
                                                   obj->segment.trans.y_position, obj->segment.trans.z_position,
                                                   AUDIO_POINT_FLAG_ONE_TIME_TRIGGER, NULL);
                } else {
                    sound_play_spatial(tempRacer->delaySoundID, obj->segment.trans.x_position,
                                       obj->segment.trans.y_position, obj->segment.trans.z_position, NULL);
                }
                tempRacer->delaySoundID = SOUND_NONE;
            }
        }
        if (header->race_type & RACETYPE_CHALLENGE && header->race_type != RACETYPE_CHALLENGE_EGGS) {
            tempRacer->elevation = obj_elevation(obj->segment.trans.y_position);
        } else {
            tempRacer->elevation = ELEVATION_LOW;
        }
        if (tempRacer->countLap < tempRacer->lap) {
            tempRacer->countLap = tempRacer->lap;
        }
    }
}

/**
 * When braking or driving in a place considered dark, a timer counts up and then sets flags.
 * These flags correspond to the lights on the back of the car being enabled and what colour they are.
 * When you exit this dark place, the timer counts back down and the lights stop.
 */
void set_racer_tail_lights(Object_Racer *racer) {
    s32 lightTimer;

    racer->lightFlags &= ~RACER_LIGHT_BRAKE;
    if (gCurrentRacerInput & B_BUTTON) {
        racer->lightFlags |= RACER_LIGHT_BRAKE;
    }

    lightTimer = racer->lightFlags & RACER_LIGHT_TIMER;
    if (racer->lightFlags & (RACER_LIGHT_BRAKE | RACER_LIGHT_NIGHT)) {
        lightTimer++;
        if (lightTimer > 2) {
            lightTimer = 2;
        }
    } else {
        lightTimer--;
        if (lightTimer < 0) {
            lightTimer = 0;
        }
    }

    racer->lightFlags = (racer->lightFlags & 0xFFF0) | lightTimer;
}

// Car vehicle logic.
void func_8004F7F4(s32 updateRate, f32 updateRateF, Object *racerObj, Object_Racer *racer) {
    f32 spBC;
    f32 spB8;
    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    MtxF sp60;
    LevelHeader *currentLevelHeader;
    Object_Boost *asset20;
    s32 var_v1;
    s8 playerObjectHasMoved;
    s32 objectMoved;

    playerObjectHasMoved = FALSE;
    if (racer->unk1D2 != 0) {
        gCurrentRacerInput &= ~A_BUTTON;
    }
    if (gCurrentPlayerIndex == PLAYER_COMPUTER || racer->raceFinished) {
        update_onscreen_AI_racer(racerObj, racer, updateRate, updateRateF);
    } else {
        if (racer->unk1D4 != 0) {
            gCurrentButtonsPressed &= ~(Z_TRIG | R_TRIG);
            if (racer->unk1D4 > 0) {
                racer->unk1D4 -= 4;
            } else {
                racer->unk1D4 += 4;
            }
        }
        if (gCurrentRacerInput & B_BUTTON && racer->drift_direction != 0) {
            var_v1 = racer->drift_direction * 3640;
        } else {
            var_v1 = 0;
        }
        if (racer->unk1FE == 0) {
            racerObj->particleEmittersEnabled |= PARTICLE_RANDOM_VELOCITY_Z;
        }
        apply_vehicle_rotation_offset(racer, updateRate, 0, 0, var_v1);
        func_80053750(racerObj, racer, updateRateF);
        handle_racer_head_turning(racerObj, racer, updateRate);
        D_8011D550 = 0;
        gCurrentCarSteerVel = 0;
        D_8011D558 = 0;
        spA8 = racerObj->segment.trans.x_position;
        spA4 = racerObj->segment.trans.y_position;
        spA0 = racerObj->segment.trans.z_position;
        if (racer->drift_direction != 0) {
            if (racer->drift_direction < 0 && gCurrentStickX >= 26) {
                racer->unk16E += updateRate;
                if (racer->unk16E < 0) {
                    racer->unk16E = 0;
                }
            } else if (racer->drift_direction > 0 && gCurrentStickX <= -26) {
                racer->unk16E -= updateRate;
                if (racer->unk16E > 0) {
                    racer->unk16E = 0;
                }
            } else {
                racer->unk16E = 0;
            }
            spB8 = racer->unk16E;
            if (spB8 < 0.0f) {
                spB8 = -spB8;
            }
            if (spB8 > 80.0f) {
                racer_play_sound(racerObj, SOUND_CAR_BRAKE);
                racer->spinout_timer = -racer->drift_direction;
                racer->drift_direction = 0;
            }
            if (gCurrentStickX > 50) {
                gCurrentStickX = 50;
            }
            if (gCurrentStickX < -50) {
                gCurrentStickX = -50;
            }
            if ((gCurrentStickX > 0 && racer->drift_direction > 0) ||
                (gCurrentStickX < 0 && racer->drift_direction < 0)) {
                gCurrentStickX >>= 2;
            }
            gCurrentStickX += (racer->drift_direction * 60);
        } else {
            racer->unk16E = 0;
        }
        handle_base_steering(racer, 0, updateRateF);
        func_800575EC(racerObj, racer);
        func_800535C4(racerObj, racer);
        handle_car_velocity_control(racer);
        handle_racer_items(racerObj, racer, updateRate);
        racer_attack_handler_car(racerObj, racer, updateRate);
        if (racer->spinout_timer != 0) {
            racer_spinout_car(racerObj, racer, updateRate, updateRateF);
        } else if (racer->groundedWheels > 0) {
            func_80050A28(racerObj, racer, updateRate, updateRateF);
        } else {
            update_car_velocity_offground(racerObj, racer, updateRate, updateRateF);
        }
        if (racer->unk1C != 0) {
            sndp_stop((SoundHandle) (s32) racer->unk1C); // type cast required to match
            racer->unk1C = 0;
        }
        if (racer->buoyancy != 0.0f && racer->vehicleIDPrev != VEHICLE_BUBBLER) {
            spB8 = racer->buoyancy - 10.0;
            racerObj->segment.y_velocity += spB8 * 0.065 * updateRateF;
        }
        currentLevelHeader = get_current_level_header();
        if ((racer->buoyancy != 0.0 && currentLevelHeader->unk2 != 0) || gCurrentSurfaceType == SURFACE_FROZEN_WATER) {
            if (racer->unk1F0 != 0) {
                racer->checkpoint_distance -= 0.3;
            } else {
                racer->checkpoint_distance -= 0.1;
            }
            set_position_goal_from_path(racerObj, racer, &spB8, &spB0, &spB4);
            if (racer->unk1F0 != 0) {
                racer->checkpoint_distance += 0.3;
            } else {
                racer->checkpoint_distance += 0.1;
            }
            spB8 -= racerObj->segment.trans.x_position;
            spB4 -= racerObj->segment.trans.z_position;
            spB0 = sqrtf((spB8 * spB8) + (spB4 * spB4));
            spB8 /= spB0;
            spB4 /= spB0;
            racerObj->segment.x_velocity = spB8 * 4.0f;
            racerObj->segment.z_velocity = spB4 * 4.0f;
            racerObj->segment.y_velocity = 9.5f;
            racer->unk1F0 = 1;
        } else if (racer->groundedWheels >= 3) {
            racer->unk1F0 = 0;
        }
        if (racer->approachTarget == NULL) {
            func_8005250C(racerObj, racer, updateRate);
        }

        var_v1 = gCurrentCarSteerVel - (racer->y_rotation_vel & 0xFFFF);
        if (var_v1 > 0x8000) {
            var_v1 -= 0xFFFF;
        }
        if (var_v1 < -0x8000) {
            var_v1 += 0xFFFF;
        }
        var_v1 >>= 2;
        if (var_v1 > 0x2EE) {
            var_v1 = 0x2EE;
        }
        if (var_v1 < -0x2EE) {
            var_v1 = -0x2EE;
        }
        racer->y_rotation_vel += (var_v1 * updateRate);
        racerObj->segment.trans.rotation.s[0] = racer->steerVisualRotation + racer->y_rotation_vel;
        racer->z_rotation_vel += (((D_8011D558 - racer->z_rotation_vel) * updateRate) >> 4);
        racerObj->segment.trans.rotation.s[2] = racer->x_rotation_vel + racer->z_rotation_vel;
        if (D_8011D550) {
            if (gCurrentPlayerIndex != PLAYER_COMPUTER && D_8011D550 != SOUND_STOMP5) {
                sound_play_spatial(D_8011D550, racerObj->segment.trans.x_position, racerObj->segment.trans.y_position,
                                   racerObj->segment.trans.z_position, &racer->unk21C);
                sound_volume_set_relative(D_8011D550, racer->unk21C, D_8011D552);
            }
            racer->stretch_height_cap = (1.0 - ((f32) (D_8011D552 - 40) * 0.004));
            racer->trickType = 0;
        }
        if (racer->unk1F0 == 0) {
            gCurrentRacerTransform.rotation.s[0] = racer->steerVisualRotation + racer->unk10C;
            gCurrentRacerTransform.rotation.s[1] = 0;
            gCurrentRacerTransform.rotation.s[2] = 0;
            gCurrentRacerTransform.x_position = 0.0f;
            gCurrentRacerTransform.y_position = 0.0f;
            gCurrentRacerTransform.z_position = 0.0f;
            gCurrentRacerTransform.scale = 1.0f;
            mtxf_from_inverse_transform(&sp60, &gCurrentRacerTransform);
            mtxf_transform_point(&sp60, racer->lateral_velocity, 0.0f, racer->velocity, &racerObj->segment.x_velocity,
                                 &spBC, &racerObj->segment.z_velocity);
        }
        if (racer->magnetTimer != 0) {
            racerObj->segment.x_velocity = gRacerMagnetVelX;
            racerObj->segment.z_velocity = gRacerMagnetVelZ;
        }
        if (racer->approachTarget == NULL) {
            spB8 = racerObj->segment.x_velocity;
            spB4 = racerObj->segment.z_velocity;
            if (racer->unk1D2 != 0) {
                spB8 += racer->unk11C;
                spB4 += racer->unk120;
            }
            if (gRacerInputBlocked != 0) {
                spB8 *= 0.65;
                spB4 *= 0.65;
                if (racer->velocity < -0.5 || racer->velocity > 0.5) {
                    racer->velocity *= 0.65;
                } else {
                    racer->velocity = 0.0f;
                }
                if (racer->lateral_velocity < -0.5 || racer->lateral_velocity > 0.5) {
                    racer->lateral_velocity *= 0.65;
                } else {
                    racer->lateral_velocity = 0.0f;
                }
            } else {
                spB8 += racer->unk84;
                spB4 += racer->unk88;
            }
            objectMoved = move_object(racerObj, spB8 * updateRateF, racerObj->segment.y_velocity * updateRateF,
                                      spB4 * updateRateF);
            if (objectMoved && gCurrentPlayerIndex != PLAYER_COMPUTER) {
                playerObjectHasMoved = TRUE;
            }
        } else {
            racer_approach_object(racerObj, racer, updateRateF);
        }
        if (gCurrentPlayerIndex == PLAYER_COMPUTER) {
            onscreen_ai_racer_physics(racerObj, racer, updateRate);
        } else {
            func_80054FD0(racerObj, racer, updateRate);
        }
        spBC = 1.0f / updateRateF;
        spB8 = (((racerObj->segment.trans.x_position - spA8) - D_8011D548) * spBC) - racer->unk84;
        racerObj->segment.y_velocity = (racerObj->segment.trans.y_position - spA4) * spBC;
        spB4 = (((racerObj->segment.trans.z_position - spA0) - D_8011D54C) * spBC) - racer->unk88;
        gCurrentRacerTransform.rotation.s[0] = -(racer->steerVisualRotation + racer->unk10C);
        gCurrentRacerTransform.rotation.s[1] = -racerObj->segment.trans.rotation.s[1];
        gCurrentRacerTransform.rotation.s[2] = -racerObj->segment.trans.rotation.s[2];
        gCurrentRacerTransform.x_position = 0.0f;
        gCurrentRacerTransform.y_position = 0.0f;
        gCurrentRacerTransform.z_position = 0.0f;
        gCurrentRacerTransform.scale = 1.0f;
        mtxf_from_inverse_transform(&sp60, &gCurrentRacerTransform);
        mtxf_transform_point(&sp60, spB8, 0.0f, spB4, &spAC, &spBC, &spB0);
        if (racer->unk1D2 != 0) {
            racer->unk1D2 -= updateRate;
            if (racer->unk1D2 < 0) {
                racer->unk1D2 = 0;
            }
        } else {
            spBC = racer->velocity - spB0;
            if (spBC > 0.5) {
                racer->velocity -= spBC - 0.5;
            }
            if (spBC < -0.5) {
                racer->velocity -= spBC + 0.5;
            }
            spBC = racer->lateral_velocity - spAC;
            if (spBC > 0.5) {
                racer->lateral_velocity -= spBC - 0.5;
            }
            if (spBC < -0.5) {
                racer->lateral_velocity -= spBC + 0.5;
            }
        }
        if (racer->boostTimer == 0 && gNumViewports < 2) {
            asset20 = (Object_Boost *) get_misc_asset(ASSET_MISC_20);
            asset20 = &asset20[racer->racerIndex];
            var_v1 = ((racer->boostType & EMPOWER_BOOST) >> 2) + 0x10;
            if (var_v1 > 0x10) {
                if (asset20->unk70 > 0 || asset20->unk74 > 0.0) {
                    racerObj->particleEmittersEnabled |= 1 << var_v1;
                }
            } else {
                if (asset20->unk70 == 2 && asset20->unk74 < 0.5) {
                    racerObj->particleEmittersEnabled |= 1 << var_v1;
                } else if (asset20->unk70 < 2 && asset20->unk74 > 0.0f) {
                    racerObj->particleEmittersEnabled |= 1 << var_v1;
                }
            }
        }
        if (gCurrentPlayerIndex != PLAYER_COMPUTER && gNumViewports < 2) {
            if (racer->buoyancy > 14.0f) {
                if (rand_range(0, 1) != 0) {
                    racerObj->particleEmittersEnabled |= PARTICLE_RANDOM_COLOUR_RED | PARTICLE_RANDOM_COLOUR_GREEN;
                }
            } else if (racer->buoyancy < 6.0f) {
                if (racer->velocity > -3.0 && racer->velocity < 0.5 && rand_range(0, 1) != 0) {
                    racerObj->particleEmittersEnabled |=
                        PARTICLE_RANDOM_SCALE_VELOCITY | PARTICLE_RANDOM_MOVEMENT_PARAM;
                }
            }
        }
        if (racer->vehicleID < VEHICLE_BOSSES) {
            update_vehicle_particles(racerObj, updateRate);
        }
        second_racer_camera_update(racerObj, racer, CAMERA_CAR, updateRateF);
        if (gNumViewports == 1 && racer->velocity > -3.0 && get_settings()->courseId != ASSET_LEVEL_WIZPIG1) {
            set_anti_aliasing(TRUE);
        }
        if (playerObjectHasMoved) {
            func_800230D0(racerObj, racer);
        }
    }
}

/**
 * At this point, control is taken away from the player.
 * Instead, they'll automatically move towards a specific object.
 */
void racer_approach_object(Object *obj, Object_Racer *racer, f32 divisor) {
    f32 diffX;
    f32 diffY;
    f32 diffZ;

    obj->segment.object.animationID = 0;
    obj->segment.animFrame = 40;
    diffX = racer->approachTarget->segment.trans.x_position - obj->segment.trans.x_position;
    diffY = racer->approachTarget->segment.trans.y_position - obj->segment.trans.y_position;
    diffZ = racer->approachTarget->segment.trans.z_position - obj->segment.trans.z_position;
    move_object(obj, diffX, diffY, diffZ);
    obj->segment.trans.rotation.y_rotation = racer->approachTarget->segment.trans.rotation.y_rotation;
    obj->segment.trans.rotation.x_rotation = racer->approachTarget->segment.trans.rotation.x_rotation;
    obj->segment.trans.rotation.z_rotation = racer->approachTarget->segment.trans.rotation.z_rotation;
    racer->x_rotation_vel = obj->segment.trans.rotation.z_rotation;
    racer->steerVisualRotation = obj->segment.trans.rotation.y_rotation;
    obj->segment.x_velocity = diffX / divisor;
    obj->segment.y_velocity = diffY / divisor;
    obj->segment.z_velocity = diffZ / divisor;
    racer->velocity = 0.0f;
    racer->unk1F2 = 0;
    racer->lateral_velocity = 0.0f;
}

/**
 * Applies visual rotational offets to vehicles.
 * Examples include planes when on the ground, or when crashing, or hovercraft when braking.
 */
void apply_vehicle_rotation_offset(Object_Racer *obj, s32 max, s16 yRotation, s16 xRotation, s16 zRotation) {
    s32 diff;
    s32 tempAngle;

    if (!obj->unk1F1) {
        tempAngle = yRotation - (u16) obj->y_rotation_offset;
        obj->unk166 = xRotation;
        WRAP(tempAngle, -0x8000, 0x8000);
        if (tempAngle > 0) {
            diff = max * 0x600;
            if (diff < tempAngle) {
                tempAngle = diff;
            }
            obj->y_rotation_offset += tempAngle;
        } else if (tempAngle < 0) {
            diff = -(max * 0x600);
            if (tempAngle < diff) {
                tempAngle = diff;
            }
            obj->y_rotation_offset += tempAngle;
        }
        tempAngle = xRotation - (u16) obj->x_rotation_offset;
        WRAP(tempAngle, -0x8000, 0x8000);
        if (tempAngle > 0) {
            diff = max * 0x600;
            if (diff < tempAngle) {
                tempAngle = diff;
            }
            obj->x_rotation_offset += tempAngle;
        } else if (tempAngle < 0) {
            diff = -(max * 0x600);
            if (tempAngle < diff) {
                tempAngle = diff;
            }
            obj->x_rotation_offset += tempAngle;
        }
        tempAngle = zRotation - (u16) obj->z_rotation_offset;
        WRAP(tempAngle, -0x8000, 0x8000);
        if (tempAngle > 0) {
            diff = max * 0x600;
            if (diff < tempAngle) {
                tempAngle = diff;
            }
            obj->z_rotation_offset += tempAngle;
        } else if (tempAngle < 0) {
            diff = -(max * 0x600);
            if (tempAngle < diff) {
                tempAngle = diff;
            }
            obj->z_rotation_offset += tempAngle;
        }
    }
}

void func_80050A28(Object *obj, Object_Racer *racer, s32 updateRate, f32 updateRateF) {
    UNUSED s32 pad0;
    s32 i;
    s32 temp_2;
    s32 sp68;
    s32 surfaceType;
    s32 sp60;
    f32 tempVel;
    s32 sp58;
    s8 stoneWheels;
    s8 steerAngle;
    f32 velSquare;
    s32 temp;
    f32 velocityDiff;
    f32 traction;
    f32 surfaceTraction;
    f32 *miscAsset;
    ObjectTransform *temp_v0;
    f32 topSpeed;
    UNUSED s32 pad1;
    UNUSED s32 pad2;

    sp58 = FALSE;
    // Set the square value of the current forward velocity
    velSquare = racer->velocity * racer->velocity;
    if (racer->velocity < 0.0f) {
        velSquare = -velSquare;
    }
    racer->unk84 = 0.0f;
    racer->unk88 = 0.0f;
    // Apply bobbing if there's no dialogue camera rotation active.
    if (gDialogueCameraAngle == 0) {
        tempVel = (f32) D_800DCDB0[0][racer->miscAnimCounter & 0x1F] * 0.024999999999999998;
        racer->carBobX = -racer->roll * tempVel;
        racer->carBobY = -racer->yaw * tempVel;
        racer->carBobZ = -racer->pitch * tempVel;
        if (obj->unk60 != NULL) {
            for (i = 0; i < ((unk_Object_60 *) obj->unk60)->count; i++) {
                tempVel = 1.0f / obj->segment.trans.scale;
                temp_v0 = ((unk_Object_60 *) obj->unk60)->transforms[i];
                temp_v0->x_position = (f32) (-racer->carBobX * tempVel);
                temp_v0->y_position = (f32) (-racer->carBobY * tempVel);
                temp_v0->z_position = (f32) (-racer->carBobZ * tempVel);
            }
        }
    } else {
        racer->carBobX = 0.0f;
        racer->carBobY = 0.0f;
        racer->carBobZ = 0.0f;
    }
    // If moving forward, active throttle will set this var to 60, otherwise it's stuck at 0
    if (racer->velocity > -0.5) {
        if (gCurrentRacerInput & A_BUTTON) {
            racer->unk1FB = 60;
        } else {
            racer->unk1FB = 0;
        }
    } else if (!(gCurrentRacerInput & A_BUTTON)) {
        racer->unk1FB = 0;
    }
    if (racer->unk1FB > 0) {
        racer->unk1FB -= updateRate;
    } else {
        racer->unk1FB = 0;
    }
    sp60 = FALSE;
    // If currently braking, do something idk
    if (racer->brake > 0.4) {
        if (racer->velocity < -2.0 && racer->raceFinished == FALSE) {
            rumble_set(racer->playerIndex, RUMBLE_TYPE_1);
        }
        sp60 = TRUE;
        if (gCurrentPlayerIndex >= PLAYER_ONE) {
            if (gNumViewports < FOUR_PLAYERS) {
                if (racer->drift_direction > 0) {
                    obj->particleEmittersEnabled |= 0x1000 | 0x400;
                } else if (racer->drift_direction < 0) {
                    obj->particleEmittersEnabled |= 0x2000 | 0x800;
                } else {
                    obj->particleEmittersEnabled |= 0x2000 | 0x1000;
                }
            } else {
                sp58 = 1;
            }
        }
        if ((racer->miscAnimCounter & 7) < 2) {
            racer->unk1D1 = rand_range(-25, 25);
        }
        gCurrentStickX += racer->unk1D1;
    }
    // If moving fast enough, enable drifting if the R button is held
    if (racer->drifting == 0 && racer->velocity > 2.0 && gCurrentRacerInput & R_TRIG &&
        (gCurrentStickX > 50 || gCurrentStickX < -50)) {
        if (gCurrentStickX > 0) {
            racer->drifting = 1;
        } else {
            racer->drifting = -1;
        }
    }
    // Handle drifting
    if (racer->drifting) {
        gCurrentRacerInput &= ~A_BUTTON;
        gCurrentRacerInput |= B_BUTTON;
        gCurrentStickY = -70;
        sp60 = TRUE;
        if (gNumViewports < FOUR_PLAYERS) {
            obj->particleEmittersEnabled |= 0x2000 | 0x1000 | 0x800 | 0x400;
        } else {
            sp58 = TRUE;
        }
        i = racer->y_rotation_vel;
        racer->y_rotation_vel += updateRate * 0x600 * racer->drifting;
        if (racer->drifting > 0) {
            if (racer->y_rotation_vel < 0 && i >= 0) {
                racer->drifting = 0;
                racer->y_rotation_vel = 0x7FFF;
            }
        } else if (racer->y_rotation_vel > 0 && i <= 0) {
            racer->drifting = 0;
            racer->y_rotation_vel = -0x8000;
        }
        if (racer->drifting == 0) {
            racer->steerVisualRotation += racer->y_rotation_vel;
            racer->unk19E = racer->y_rotation_vel;
            racer->y_rotation_vel = 0;
            racer->velocity = -racer->velocity;
        }
    }
    // Apply some flags when drifting
    if (racer->drift_direction != 0 && gCurrentPlayerIndex >= PLAYER_ONE) {
        if (gNumViewports < FOUR_PLAYERS) {
            if (racer->drift_direction > 0) {
                obj->particleEmittersEnabled |= 0x1000 | 0x400;
            } else {
                obj->particleEmittersEnabled |= 0x2000 | 0x800;
            }
        } else {
            sp58 = TRUE;
        }
    }
    // Decide which way to drift when the R button is held
    if (racer->drift_direction == 0 && gCurrentRacerInput & R_TRIG && racer->velocity < -3.0 &&
        (gCurrentStickX > 15 || gCurrentStickX < -15)) {
        if (gCurrentStickX < 0) {
            racer->drift_direction = -1;
        }
        if (gCurrentStickX > 0) {
            racer->drift_direction = 1;
        }
    }
    // Disable drifting if going too slow
    if (racer->velocity > -2.0) {
        racer->drift_direction = 0;
    }
    // Get top speed value
    topSpeed = handle_racer_top_speed(obj, racer);
    // If currently drifting, apply a minor speed multiplier and tilt the natural steering towards the drift direction
    if (gCurrentRacerInput & R_TRIG && racer->drift_direction != 0) {
        topSpeed *= 1.1;
        // Unused code?
        temp = (gCurrentStickX >> 1) + (racer->drift_direction * 30);
        if (temp > 75) {
            temp = 75;
        }
        if (temp < -75) {}
    } else {
        racer->drift_direction = 0;
    }
    racer->unk10C -= ((racer->unk10C - (racer->drift_direction << 13)) * updateRate) >> 4;
    // sounds for drifting and sliding
    if (!(racer->y_rotation_vel <= 0x1800 && racer->y_rotation_vel >= -0x1800 && racer->drift_direction == 0 &&
          racer->drifting == 0 && racer->unk1FB == 0)) {
        sp60 = TRUE;
        if (racer->unk1FB != 0 && racer->raceFinished == FALSE) {
            rumble_set(racer->playerIndex, RUMBLE_TYPE_0);
        }
        if (racer->y_rotation_vel < 0) {
            obj->particleEmittersEnabled |= 0x1000 | 0x400;
        } else {
            obj->particleEmittersEnabled |= 0x2000 | 0x800;
        }
        if (racer->drift_direction != 0 || racer->drifting != 0 || racer->unk1FB != 0) {
            if (racer->unk10 == 0) {
                sound_play_spatial(SOUND_CAR_SLIDE, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                   obj->segment.trans.z_position, &racer->unk10);
            } else {
                audspat_calculate_echo((SoundHandle) (s32) racer->unk10, obj->segment.trans.x_position,
                                       obj->segment.trans.y_position,
                                       obj->segment.trans.z_position); // type cast required to match
            }
            if (racer->unk14) {
                sndp_stop((SoundHandle) (s32) racer->unk14); // type cast required to match
            }
        } else {
            if (racer->unk10) {
                sndp_stop((SoundHandle) (s32) racer->unk10); // type cast required to match
            }
        }
    } else {
        if (racer->unk10) {
            sndp_stop((SoundHandle) (s32) racer->unk10); // type cast required to match
        }
        if (racer->unk14) {
            sndp_stop((SoundHandle) (s32) racer->unk14); // type cast required to match
        }
    }
    // Velocity of steering input
    steerAngle = racer->steerAngle;
    i = 6;
    // Turn twice as fast under braking (because that's totally how cars work)
    if (gCurrentRacerInput & B_BUTTON) {
        i = 12;
    }
    // Turn thrice as fast when drifting and braking.
    if (gCurrentRacerInput & B_BUTTON && racer->drift_direction != 0) {
        i = 18;
    }
    // Multiply steering velocity with angle
    temp = 0;
    if (racer->velocity < -0.3) {
        temp = steerAngle * i;
    }
    if (racer->velocity > 0.3) {
        temp = -steerAngle * i;
    }
    // Set final turn velocity by taking the steering velocity and multiplying it by the handling stat of the character.
    temp = ((temp * updateRate) >> 1);
    temp_2 = temp * gCurrentRacerHandlingStat;
    racer->steerVisualRotation -= temp_2 & 0xFFFF;
    // Now steer the car.
    handle_car_steering(racer);
    // Set base grip level to 0.
    surfaceType = SURFACE_DEFAULT;
    // If reversing, flip the steering
    if (racer->velocity < -4.0) {
        if (gCurrentCarSteerVel > 0x1400 || (racer->drift_direction != 0 && gCurrentCarSteerVel > 0)) {
            i = racer->miscAnimCounter & 7;
            if (i >= 4) {
                i = 7 - i;
            }
            gCurrentCarSteerVel += i * 0x190;
        } else if (gCurrentCarSteerVel < -0x1400 || (racer->drift_direction != 0 && gCurrentCarSteerVel < 0)) {
            i = racer->miscAnimCounter & 7;
            if (i >= 4) {
                i = 7 - i;
            }
            gCurrentCarSteerVel -= i * 0x190;
        }
    }

    traction = 0.0f;
    surfaceTraction = 0.0f;
    velocityDiff = 0.0f;
    sp68 = 0;        // Number of wheels contacting grass or sand
    stoneWheels = 0; // Number of wheels contacting the stone surface type
    // Iterate through each wheel and find which surface they're on.
    i = 0;
    while (i < 4) {
        if (racer->wheel_surfaces[i] != SURFACE_NONE) {
            if (get_filtered_cheats() & CHEAT_FOUR_WHEEL_DRIVER) {
                traction += gSurfaceTractionTable[0];
            } else {
                traction += gSurfaceTractionTable[racer->wheel_surfaces[i]];
            }
            surfaceTraction += D_800DCBE8[racer->wheel_surfaces[i]];
            sp68 += gSurfaceBobbingTable[racer->wheel_surfaces[i]];
            if (surfaceType < racer->wheel_surfaces[i]) {
                surfaceType = racer->wheel_surfaces[i];
            }
            if (racer->wheel_surfaces[i] == SURFACE_STONE) {
                stoneWheels++;
            }
            velocityDiff += 1.0f;
        }
        i++;
    };

    // Probably fake but required for match
    for (i = 0; i < 4; i++) {}

    // With multiple contact patches, average the surface properties across.
    if (velocityDiff > 1.0f) {
        traction /= velocityDiff;
        surfaceTraction /= velocityDiff;
    }
    // If on the Taj pad and the horn is honked, summon Taj
    if (racer->playerIndex == PLAYER_ONE && racer->groundedWheels && surfaceType == SURFACE_TAJ_PAD &&
        gCurrentButtonsPressed & Z_TRIG) {
        gTajInteractStatus = TAJ_TELEPORT;
    }
    // Set grip levels to basically zero when floating on water.
    if (racer->buoyancy != 0.0) {
        traction = 0.02f;
        surfaceTraction = 0.0f;
    }
    // no clue :)
    if (surfaceType == SURFACE_SAND && racer->velocity < -2.0 && racer->raceFinished == FALSE) {
        rumble_set(racer->playerIndex, RUMBLE_TYPE_0);
    }
    miscAsset = (f32 *) get_misc_asset(ASSET_MISC_8);
    // Degrade lateral velocity
    if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
        if (!(racer->velocity > -2.0) && racer->drift_direction == 0 && !racer->raceFinished) {
            racer->lateral_velocity += (racer->velocity * gCurrentStickX) / miscAsset[racer->characterId]; //!@Delta
            if (racer->playerIndex == PLAYER_COMPUTER) {
                racer->lateral_velocity *= 0.9;
            }
        }
    }
    if (racer->velocity > -3.0) {
        tempVel = -(racer->velocity + 2.0);
        if (tempVel < 0.0) {
            tempVel = 0.0f;
        }
        gCurrentCarSteerVel *= tempVel;
        surfaceTraction = ((1.0 - tempVel) * 0.7) + (surfaceTraction * tempVel);
    }
    // Multiply current velocity by the surface grip levels.
    racer->lateral_velocity *= surfaceTraction;
    velocityDiff = coss_f(racer->x_rotation_vel);
    if (velocityDiff < 0.0f) {
        velocityDiff = -velocityDiff;
    }
    // Multiply lateral velocity by pitch
    racer->lateral_velocity *= velocityDiff;
    gCurrentSurfaceType = surfaceType;
    if (stoneWheels != 0) {
        miscAsset = (f32 *) get_misc_asset(ASSET_MISC_32);
        topSpeed *= miscAsset[stoneWheels];
        racer->magnetTimer = 0;
        racer->lateral_velocity = 0.0f;
    } else if (surfaceType == SURFACE_FROZEN_WATER) {
        racer->boost_sound |= BOOST_SOUND_UNK4;
        racer_play_sound(obj, SOUND_BOUNCE2);
    }
    // If driving over a zip pad, apply a boost.
    if (racer->boostTimer == 0 && surfaceType == SURFACE_ZIP_PAD) {
        racer->boostTimer = normalise_time(45);
        racer->boostType = BOOST_LARGE;
        racer_play_sound(obj, SOUND_ZIP_PAD_BOOST);
        play_random_character_voice(obj, SOUND_VOICE_CHARACTER_POSITIVE, 8, 0x82);
        if (racer->raceFinished == FALSE) {
            rumble_set(racer->playerIndex, RUMBLE_TYPE_8);
        }
    }
    // Slow down gradually when not acellerating and almost at a standstill
    if (velSquare < 1.0f && !(gCurrentRacerInput & A_BUTTON)) {
        racer->velocity -= racer->velocity * traction * 8.0f; //!@Delta
    } else {
        racer->velocity -= velSquare * traction; //!@Delta
    }
    if (sp60) {
        if (racer->unk1EE <= 15) {
            racer->unk1EE++;
        }
    } else {
        racer->unk1EE = 0;
    }
    if (cam_get_viewport_layout() < THREE_PLAYERS) {
        if ((sp60 != 0 && racer->velocity < -2.0) || sp58 != 0 || racer->unk1FB != 0) {
            if (racer->wheel_surfaces[2] < SURFACE_NONE) {
                obj->particleEmittersEnabled |= gSurfaceFlagTable[racer->wheel_surfaces[2]];
            }
            if (racer->wheel_surfaces[3] < SURFACE_NONE) {
                obj->particleEmittersEnabled |= gSurfaceFlagTable[racer->wheel_surfaces[3]] * 2;
            }
        }
        if (racer->velocity < -2.0) {
            if (racer->wheel_surfaces[2] < SURFACE_NONE) {
                obj->particleEmittersEnabled |= gSurfaceFlagTable4P[racer->wheel_surfaces[2]];
            }
            if (racer->wheel_surfaces[3] < SURFACE_NONE) {
                obj->particleEmittersEnabled |= gSurfaceFlagTable4P[racer->wheel_surfaces[3]] * 2;
            }
        }
    }
    // Play a sound on grass and sand when landing on it
    surfaceType = gSurfaceSoundTable[surfaceType];
    if (racer->unk18 == 0 && surfaceType != SOUND_NONE && racer->velocity < -2.0) {
        sound_play(surfaceType, &racer->unk18);
    }
    if (racer->unk18 != 0 && (surfaceType == SOUND_NONE || racer->velocity > -2.0)) {
        sndp_stop((SoundHandle) (s32) racer->unk18); // type cast required to match
    }
    // Apply a bobbing effect when on grass and sand.
    if (racer->velocity < -2.0 && sp68 >= 4) {
        tempVel = (f32) (racer->miscAnimCounter & 1) * 0.5;
        racer->carBobX -= racer->roll * tempVel;
        racer->carBobY -= racer->yaw * tempVel;
        racer->carBobZ -= racer->pitch * tempVel;
    }
    traction = racer->velocity;
    // Keep velocity positive and keep it below 12
    if (racer->velocity < 0.0f) {
        traction = -traction;
    }

    if (traction > 12.0f) {
        traction = 12.0f;
    }
    // Convert the velocity value to an int
    temp = (s32) traction;
    // Calculate the velocity multiplier based on current velocity
    traction = ((gCurrentRacerMiscAssetPtr[temp + 1] * (traction - temp)) +
                (gCurrentRacerMiscAssetPtr[temp] * (1.0 - (traction - temp))));
    traction *= 1.7;
    traction *= topSpeed;
    // Force the throttle wide open if boosting
    if (racer->boostTimer > 0) {
        if (gRaceStartTimer == 0) {
            racer->throttle = 1.0f;
            if (traction != 0.0) {
                traction = 2.0f;
            }
            racer->boostTimer -= updateRate;
        }
    } else {
        racer->boostTimer = 0;
    }
    if (racer->velocity > -2.0 && racer->velocity < 3.0 &&
        (racer->playerIndex != PLAYER_COMPUTER || racer->unk214 != 0)) {
        tempVel = (3.0 - racer->velocity) * 0.15;
        if (surfaceType == 4) {
            tempVel *= 0.25;
        }
        if ((gCurrentStickY < -25) && !(gCurrentRacerInput & A_BUTTON) && (gCurrentRacerInput & B_BUTTON)) {
            if (racer->vehicleIDPrev >= 5) {
                tempVel *= 0.3;
            }
            racer->velocity += tempVel; //!@Delta
            racer->brake = 0.0f;
        }
    }
    tempVel = (racer->brake * traction) * 0.32;
    racer->velocity -= traction * racer->throttle;
    if (racer->velocity > -0.04 && racer->velocity < 0.04) {
        racer->velocity = 0.0f;
    }
    if (racer->velocity < 0.0f) {
        racer->velocity += tempVel;
        if (racer->velocity > 0.0f) {
            racer->velocity = 0.0f;
        }
    } else {
        racer->velocity -= tempVel;
        if (racer->velocity < 0.0f) {
            racer->velocity = 0.0f;
        }
    }
    traction = gCurrentRacerWeightStat;
    obj->segment.y_velocity -= traction * updateRateF;
    if (gDialogueCameraAngle != 0) {
        traction = 0.0f;
    }
    if (racer->brake < 0.9 && racer->vehicleIDPrev < VEHICLE_BOSSES && gRaceStartTimer == 0) {
        velocityDiff = racer->pitch;
        if (velocityDiff < 0.0) {
            velocityDiff = -velocityDiff;
            velocityDiff -= 0.3;
            if (velocityDiff < 0.0) {
                velocityDiff = 0.0f;
            }
            if (velocityDiff > 0.1) {
                velocityDiff = 0.1f;
            }
            velocityDiff *= 35.0f;
        } else {
            velocityDiff = 0.0f;
        }
        racer->velocity += traction * (racer->pitch / (4.0f - velocityDiff)) * updateRateF;
    }
    racer->forwardVel -= (racer->forwardVel + (racer->velocity * 0.05)) * 0.125; //!@Delta
    racer->unk1E8 = racer->steerAngle;
    racer->unk110 = gCurrentCarSteerVel;
    if (racer->trickType != 0) {
        if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
            if (racer->wheel_surfaces[0] != SURFACE_NONE) {
                D_8011D550 = D_800DCCCC[racer->wheel_surfaces[0]];
                *((s16 *) &D_8011D552) = racer->trickType; // necessary because a different function expects a char.
                racer->trickType = 0;
            }
        }
    }
}

/**
 * Checks if Taj's interaction status is set to try make him teleport and return true.
 */
s32 should_taj_teleport(void) {
    if (gTajInteractStatus == TAJ_TELEPORT) {
        gTajInteractStatus = TAJ_DIALOGUE;
        return TRUE;
    }
    return FALSE;
}

/**
 * Sets Taj's interaction status.
 */
void set_taj_status(TajInteraction status) {
    gTajInteractStatus = status;
}

/**
 * Find a nearby racer and set the head to turn to face them.
 * Otherwise, if stationary, set a random angle to turn to periodically.
 */
void handle_racer_head_turning(Object *obj, Object_Racer *racer, UNUSED s32 updateRate) {
    Object *tempObj;
    s8 foundObj;
    f32 distance;
    s32 intendedAngle;

    foundObj = FALSE;
    if (func_80023568()) {
        tempObj = get_racer_object(1);
        foundObj = turn_head_towards_object(obj, racer, tempObj, 400.0f * 400.0f);
    }
    if (foundObj == FALSE) {
        tempObj = func_8001B7A8(racer, 1, &distance);
        if (tempObj && !gRaceStartTimer) {
            foundObj = turn_head_towards_object(obj, racer, tempObj, 400.0f * 400.0f);
        }
    }
    if (foundObj == FALSE) {
        tempObj = func_8001B7A8(racer, -1, &distance);
        if (tempObj && !gRaceStartTimer) {
            foundObj = turn_head_towards_object(obj, racer, tempObj, 30000.0f);
        }
    }
    if (foundObj == FALSE) {
        if ((racer->miscAnimCounter & 0x1F) < 2) {
            intendedAngle = racer->velocity * 1280.0f;

            if (intendedAngle < 0) {
                intendedAngle = -intendedAngle;
            }

            if (intendedAngle > 0x2800) {
                intendedAngle = 0x2800;
            }

            intendedAngle = 0x2800 - intendedAngle;

            racer->headAngleTarget = rand_range(-intendedAngle, intendedAngle);
        }
    }
}

/**
 * Over time, set the head angle target to zero.
 * The character's head will start to face forward.
 */
void slowly_reset_head_angle(Object_Racer *racer) {
    racer->headAngleTarget -= racer->headAngleTarget >> 3; //!@Delta
    if (racer->headAngleTarget > -10 && racer->headAngleTarget < 10) {
        racer->headAngleTarget = 0;
    }
}

/**
 * Compute angle between objects, then set the intended angle for the character's head to face
 * an object.
 */
s32 turn_head_towards_object(Object *obj, Object_Racer *racer, Object *targetObj, f32 distance) {
    s32 intendedAngle;
    f32 diffX;
    f32 diffZ;
    s32 ret;

    ret = FALSE;
    diffX = targetObj->segment.trans.x_position - obj->segment.trans.x_position;
    diffZ = targetObj->segment.trans.z_position - obj->segment.trans.z_position;
    if ((diffX * diffX) + (diffZ * diffZ) < distance) {
        intendedAngle = (arctan2_f(diffX, diffZ) - (obj->segment.trans.rotation.y_rotation & 0xFFFF)) + 0x8000;
        WRAP(intendedAngle, -0x8000, 0x8000);
        CLAMP(intendedAngle, -0x3000, 0x3000);
        racer->headAngleTarget = intendedAngle;
        if ((racer->miscAnimCounter & 0x3F) <= 30) {
            racer->headAngleTarget = 0;
        }
        racer = &targetObj->unk64->racer;
        intendedAngle = arctan2_f(diffX, diffZ) - (obj->segment.trans.rotation.y_rotation & 0xFFFF);
        WRAP(intendedAngle, -0x8000, 0x8000);
        CLAMP(intendedAngle, -0x3000, 0x3000);
        racer->headAngleTarget = intendedAngle;
        if (ret) {} // Fakematch
        ret = TRUE;
        if ((racer->miscAnimCounter & 0x1F) < 10) {
            racer->headAngleTarget = 0;
        }
    }
    return ret;
}

void func_8005250C(Object *obj, Object_Racer *racer, s32 updateRate) {
    s8 *balloonAsset;
    s32 angleVel;
    s32 newAngle;
    s32 actionStatus;

    angleVel = 0;
    if (racer->balloon_quantity > 0) {
        balloonAsset = (s8 *) get_misc_asset(ASSET_MISC_BALLOON_DATA);

        angleVel = balloonAsset[(racer->balloon_type * 10) + (racer->balloon_level * 2)];
    }
    if (gCurrentButtonsPressed & Z_TRIG && angleVel != 4 && angleVel != 8) {
        racer->unk1F2 = 5;
    }
    if (racer->boostTimer) {
        racer->unk1F3 |= 4;
    }
    if (racer->unk1F3 & 8) {
        if (gNumViewports < 3) {
            if (gCurrentPlayerIndex >= PLAYER_ONE) {
                obj->particleEmittersEnabled |= 0x100000;
            } else {
                obj->particleEmittersEnabled |= 0x80000;
            }
        }
        racer->unk1F2 = 4;
    }
    if (gRaceStartTimer) {
        racer->unk1F3 = 0;
        racer->unk1F2 = 0;
    }
    if (racer->raceFinished == TRUE) {
        racer->unk1F2 = 0;
        racer->unk1F3 = 0;
    }
    switch (racer->unk1F2) {
        case 0: // Sliding, creating tyre marks
            angleVel = (s32) ((-racer->y_rotation_vel >> 8) / gCurrentRacerHandlingStat);
            angleVel = 40 - angleVel;
            if (angleVel < 0) {
                angleVel = 0;
            }
            if (angleVel > 73) {
                angleVel = 73;
            }
            newAngle = angleVel - obj->segment.animFrame;
            angleVel = 0;
            if (newAngle > 0) {
                angleVel = updateRate * 3;
                if (newAngle < angleVel) {
                    angleVel = newAngle;
                }
            }
            if (newAngle < 0) {
                angleVel = updateRate * -3;
                if (angleVel < newAngle) {
                    angleVel = newAngle;
                }
            }
            obj->segment.animFrame += angleVel;
            obj->segment.object.animationID = 0;
            if (angleVel) {} // Fakematch
            if (racer->unk1F3 & 4) {
                racer->unk1F2 = 3;
                racer->unk1F3 &= 0xFFFB;
            }
            if (racer->velocity > 0.0 && gCurrentRacerInput & B_BUTTON) {
                racer->unk1F2 = 6;
            }
            break;
        case 3: // Boost
            actionStatus = 2;
            if (racer->unk1F3 & 4) {
                actionStatus = 4 | 2;
            }
            func_80052988(obj, racer, 2, 0, 32, 4, actionStatus, updateRate);
            racer->unk1F3 &= 0xFFFB;
            break;
        case 4: // Crash
            func_80052988(obj, racer, 3, 0, 32, 2, 0, updateRate);
            racer->unk1F3 &= 0xFFF7;
            break;
        case 5: // Horn
            actionStatus = 2;
            if (gCurrentRacerInput & Z_TRIG) {
                actionStatus = 4 | 2;
            }
            func_80052988(obj, racer, 4, 0, 48, 4, actionStatus, updateRate);
            break;
        case 6:
            actionStatus = 3;
            if (racer->velocity > 0.0 && gCurrentRacerInput & B_BUTTON) {
                actionStatus = 4 | 2 | 1; // Reverse
            }
            func_80052988(obj, racer, 1, 0, 80, 3, actionStatus, updateRate);
            break;
        case 7:
            func_80052988(obj, racer, 5, 0, 96, 4, 0, updateRate);
            if (racer->unk1F2 == 0) {
                func_80052988(obj, racer, 5, 0, 96, 4, 0, updateRate);
            }
            break;
    }
}

// Anims related to the car I think
void func_80052988(Object *obj, Object_Racer *racer, s32 action, s32 arg3, s32 duration, s32 arg5, s32 flags,
                   s32 arg7) {
    arg5 *= arg7;

    if (gCurrentPlayerIndex == PLAYER_COMPUTER && action >= 3) {
        obj->segment.object.animationID = 0;
        racer->unk1F2 = 0;
    } else if (obj->segment.object.animationID == 0) {
        if (flags & 1) {
            if (obj->segment.animFrame > 40) {
                obj->segment.animFrame -= arg7 * 4;
                if (obj->segment.animFrame <= 40) {
                    obj->segment.object.animationID = action;
                    obj->segment.animFrame = arg3;
                }
            } else {
                obj->segment.animFrame += arg7 * 4;
                if (obj->segment.animFrame >= 40) {
                    obj->segment.object.animationID = action;
                    obj->segment.animFrame = arg3;
                }
            }
        } else {
            obj->segment.object.animationID = action;
            obj->segment.animFrame = arg3;
            racer->unk1F3 &= ~0x80;
        }
    } else if (obj->segment.object.animationID == action) {
        if (flags & 2) {
            if (racer->unk1F3 & 0x80) {
                obj->segment.animFrame -= arg5; //!@Delta
                if (obj->segment.animFrame <= 0) {
                    obj->segment.object.animationID = 0;
                    racer->unk1F2 = 0;
                    obj->segment.animFrame = 40;
                    racer->unk1F3 = 0;
                }
            } else {
                obj->segment.animFrame += arg5; //!@Delta
                if (obj->segment.animFrame >= duration) {
                    obj->segment.animFrame = duration - 1;
                    if (!(flags & 4)) {
                        racer->unk1F3 |= 0x80;
                    }
                }
            }
        } else {
            obj->segment.animFrame += arg5; //!@Delta
            if (obj->segment.animFrame >= duration) {
                obj->segment.object.animationID = 0;
                racer->unk1F2 = 0;
                obj->segment.animFrame = 40;
                racer->unk1F3 = 0;
            }
        }
    } else {
        obj->segment.animFrame = arg3;
        obj->segment.object.animationID = action;
    }
}

/**
 * If the spinout timer is above zero, remove steering control and have them rotate until
 * the timer runs out.
 */
void racer_spinout_car(Object *obj, Object_Racer *racer, s32 updateRate, f32 updateRateF) {
    s32 angleVel;

    racer->velocity *= 0.97; //!@Delta: Reduces 3% of speed per frame, not accounting for game speed.
    racer->lateral_velocity = 0.0f;
    if (racer->raceFinished == FALSE) {
        rumble_set(racer->playerIndex, RUMBLE_TYPE_0);
    }
    angleVel = racer->y_rotation_vel;
    if (gCurrentPlayerIndex > PLAYER_COMPUTER) {
        if (gNumViewports < VIEWPORT_LAYOUT_4_PLAYERS) {
            obj->particleEmittersEnabled |= 0x4FC00;
        } else {
            if (racer->wheel_surfaces[2] < SURFACE_NONE) {
                obj->particleEmittersEnabled |= 1 << (racer->wheel_surfaces[2] * 2);
            }
            if (racer->wheel_surfaces[3] < SURFACE_NONE) {
                obj->particleEmittersEnabled |= 2 << (racer->wheel_surfaces[3] * 2);
            }
        }
    }
    if (racer->spinout_timer > 0) {
        racer->y_rotation_vel += updateRate * 0x500;
        if (racer->y_rotation_vel > 0 && angleVel < 0) {
            racer->spinout_timer--; //!@Delta
            if (gCurrentStickX > 50 && racer->spinout_timer == 1) {
                racer->spinout_timer = 0;
            }
        }
    } else if (racer->spinout_timer < 0) {
        racer->y_rotation_vel -= updateRate * 0x500;
        if (racer->y_rotation_vel < 0 && angleVel > 0) {
            racer->spinout_timer++; //!@Delta
            if (gCurrentStickX < -50 && racer->spinout_timer == -1) {
                racer->spinout_timer = 0;
            }
        }
    }
    gCurrentCarSteerVel = racer->y_rotation_vel;
    obj->segment.y_velocity -= gCurrentRacerWeightStat * updateRateF;
    gCurrentStickX = 0;
    racer->steerAngle = 0;
}

/**
 * Gets, sets and works with car velocity while either airborne or in water.
 * It also handles turn velocity, too, as well as vertical velocity.
 */
void update_car_velocity_offground(Object *obj, Object_Racer *racer, s32 updateRate, f32 updateRateF) {
    s32 steerAngle;
    s32 yStick;
    s32 angle;
    s8 canSteer;
    f32 weight;

    canSteer = FALSE;
    if (racer->unk1FE == 1 && racer->playerIndex == PLAYER_COMPUTER) {
        gCurrentStickY = 60;
    }
    if (racer->unk1F0 != 0) {
        if (racer->playerIndex != PLAYER_COMPUTER) {
            steerAngle = racer->steerAngle;
        } else {
            steerAngle = gCurrentStickX;
        }
        racer->steerVisualRotation -= (u16) ((steerAngle * 6 * updateRate) >> 1);
        angle = -(u16) racer->x_rotation_vel;
        WRAP(angle, -0x8000, 0x8000);
        racer->x_rotation_vel += (angle >> 3); //!@Delta
    }
    if (racer->unk18) {
        sndp_stop((SoundHandle) (s32) racer->unk18); // type cast required to match
    }
    if (racer->unk10) {
        sndp_stop((SoundHandle) (s32) racer->unk10); // type cast required to match
    }
    if (racer->unk14) {
        sndp_stop((SoundHandle) (s32) racer->unk14); // type cast required to match
    }
    if (racer->unk1FE == 1 || racer->unk1FE == 3) {
        racer->unk1E8 = racer->steerAngle;
    }
    if (racer->buoyancy != 0.0) {
        if (obj->segment.y_velocity > 2.0) {
            obj->segment.y_velocity = 2.0f;
        }
        if (obj->segment.y_velocity < -2.0) {
            obj->segment.y_velocity = -2.0f;
        }
        racer->unk1E8 = racer->steerAngle;
        if (gCurrentRacerInput & A_BUTTON) {
            racer->velocity -= 0.5; //!@Delta
        }
        if (gCurrentRacerInput & B_BUTTON && gCurrentStickY < -25) {
            racer->velocity += 0.5; //!@Delta
        }
        canSteer = TRUE;
        racer->lateral_velocity *= 0.87; //!@Delta
        racer->velocity *= 0.87;         //!@Delta
        obj->segment.y_velocity *= 0.9;  //!@Delta
        rotate_racer_in_water(obj, racer, &gCurrentRacerWaterPos, gRacerWaveType, updateRate, gCurrentStickX, 6.0f);
    }
    if (racer->playerIndex == PLAYER_COMPUTER) {
        racer->unk1E8 = racer->steerAngle;
    }
    if (racer->boostTimer > 0) {
        racer->boostTimer -= updateRate;
    } else {
        racer->boostTimer = 0;
    }
    angle = racer->unk1E8 * 6;
    if (racer->velocity > 0.3) {
        angle = -racer->steerAngle;
        angle *= 6;
    }
    racer->steerVisualRotation -= angle & 0xFFFF;
    gCurrentCarSteerVel = racer->unk110;
    if (racer->boostTimer) {
        if (racer->velocity > -20.0) {
            racer->velocity -= 1.6; //!@Delta
        }
    }
    yStick = gCurrentStickY;
    if (yStick < 50 && yStick > -50) {
        yStick = 0;
    }
    obj->segment.y_velocity -= (obj->segment.y_velocity * 0.025) * updateRateF;
    weight = gCurrentRacerWeightStat;
    if (racer->unk1F1 || racer->unk1F0) {
        weight = 0.45f;
        racer->y_rotation_offset += 0x500 * updateRate;
        racer->x_rotation_offset += 0x600 * updateRate;
    }
    if (racer->unk1FE == 1 || racer->unk1FE == 3) {
        racer->lateral_velocity *= 0.97; //!@Delta
        racer->velocity *= 0.97;         //!@Delta
        if (yStick > 50) {
            racer->velocity -= 0.2; //!@Delta
        }
        if (yStick < -50) {
            racer->velocity += 0.2; //!@Delta
        }
        canSteer = TRUE;
    }
    if (canSteer) {
        obj->particleEmittersEnabled = OBJ_EMIT_NONE;
        racer->drift_direction = 0;
        racer->unk10C -= (racer->unk10C * updateRate) >> 4;
        gCurrentCarSteerVel = 0;
        handle_car_steering(racer);
    } else {
        if (yStick > 50) {
            weight *= 1.33;
        }
        if (yStick < -50) {
            weight *= 0.53;
        }
    }
    if (racer->boostTimer) {
        weight *= 0.5;
    }
    yStick = -yStick;
    yStick *= 64;
    yStick = (u16) yStick;
    angle = yStick - ((u16) obj->segment.trans.rotation.x_rotation);
    angle = angle > 0x8000 ? angle - 0xFFFF : angle;
    angle = angle < -0x8000 ? angle + 0xFFFF : angle;
    obj->segment.trans.rotation.x_rotation += (angle >> 3); //!@Delta
    obj->segment.y_velocity -= weight * updateRateF;
    if (racer->buoyancy == 0.0) {
        steerAngle = -obj->segment.y_velocity * 20.0;
        if (steerAngle < 50) {
            steerAngle = 50;
        }
        if (steerAngle > 127) {
            steerAngle = 127;
        }
        racer->trickType = steerAngle;
    }
    obj->particleEmittersEnabled = OBJ_EMIT_NONE;
}

/**
 * Handle the steering input of all cars.
 * It takes the speed of the car, creating a curve for the rotational velocity to scale with.
 */
void handle_car_steering(Object_Racer *racer) {
    s32 velScale;
    f32 vel = racer->velocity;

    // Stay positive :)
    if (vel < 0.0) {
        vel = -vel;
    }
    if (vel > 1.8) {
        vel = 1.8f;
    }
    vel -= 0.2;
    if (vel < 0.0) {
        vel = 0.0f;
    }
    if (racer->drift_direction != 0) {
        velScale = vel * 68.0f;
    } else {
        velScale = vel * 58.0f;
    }
    // Set the steering velocity based on the car's steering value, scaled with the temp forward velocity value.
    gCurrentCarSteerVel -= (racer->steerAngle * velScale);
    // If the car is reversing, then flip the steering.
    if (racer->velocity > 0.0f) {
        gCurrentCarSteerVel = -gCurrentCarSteerVel;
    }
}

void func_800535C4(Object *obj, Object_Racer *racer) {
    MtxF mf;

    gCurrentRacerTransform.rotation.y_rotation = -racer->steerVisualRotation;
    gCurrentRacerTransform.rotation.x_rotation = -obj->segment.trans.rotation.x_rotation;
    gCurrentRacerTransform.rotation.z_rotation = -racer->x_rotation_vel;
    gCurrentRacerTransform.x_position = 0;
    gCurrentRacerTransform.y_position = 0;
    gCurrentRacerTransform.z_position = 0;
    gCurrentRacerTransform.scale = 1;
    mtxf_from_inverse_transform(&mf, &gCurrentRacerTransform);

    mtxf_transform_point(&mf, 0.0f, -1.0f, 0.0f, &racer->roll, &racer->yaw, &racer->pitch);
}

/**
 * Adjusts the throttle and brake application for all cars, based off the input.
 */
void handle_car_velocity_control(Object_Racer *racer) {
    if (racer->throttle > 0.0) {
        racer->throttle -= 0.1; //!@Delta
    }

    if (gCurrentRacerInput & A_BUTTON) {
        racer->throttle = 1.0f;
    }

    if (gCurrentRacerInput & B_BUTTON) {
        if (racer->brake < 1.0) {
            racer->brake += 0.2; //!@Delta
        }
    } else {
        //! @bug Will cause a negative brake value resulting in higher velocity
        if (racer->brake > 0.05) {
            racer->brake -= 0.1; //!@Delta
        }
    }
}

void func_80053750(Object *objRacer, Object_Racer *racer, f32 updateRateF) {
    Object *someObj;
    f64 temp_f0;
    f32 velocity;
    s32 temp_v1;
    s32 flags;
    s32 isNotHardBraking;
    s32 i;

    if (objRacer->unk60 == NULL) {
        return;
    }
    temp_v1 = objRacer->unk60->unk0;
    if (temp_v1 == 2) {
        someObj = objRacer->unk60->unk4[0];
        someObj->segment.trans.rotation.y_rotation = 0x4000;
        someObj = objRacer->unk60->unk4[1];
        someObj->segment.trans.rotation.y_rotation = 0x4000;
    }
    if (temp_v1 >= 4) {
        velocity = racer->velocity;
        if (velocity > 5.0) {
            velocity = 5.0;
        }
        if (velocity < -5.0) {
            velocity = -5.0;
        }
        isNotHardBraking = TRUE;
        if (racer->brake > 0.4) {
            if (racer->throttle < 0.4) {
                velocity = 0.0f;
            }
            isNotHardBraking = FALSE;
        }
        racer->unkB0 -= (velocity * updateRateF) * 0.5;
        while (racer->unkB0 > 5.0) {
            racer->unkB0 -= 5.0;
            for (i = 0; i < 4; i++) {
                if (i < 2 || isNotHardBraking) {
                    someObj = objRacer->unk60->unk4[i];
                    if ((racer->unk1FB != 0 && i >= 3) || racer->unk1FB == 0) {
                        if (someObj->properties.common.unk0 != 0) {
                            someObj->segment.object.modelIndex--;
                            if (someObj->segment.object.modelIndex < 0) {
                                someObj->segment.object.modelIndex = someObj->segment.header->numberOfModelIds - 1;
                            }
                        } else {
                            someObj->segment.object.modelIndex++;
                            if (someObj->segment.object.modelIndex == someObj->segment.header->numberOfModelIds) {
                                someObj->segment.object.modelIndex = 0;
                            }
                        }
                    }
                }
            }
        }
        while (racer->unkB0 < 0.0f) {
            racer->unkB0 += 5.0;
            for (i = 0; i < 4; i++) {
                if (i < 2 || isNotHardBraking) {
                    someObj = objRacer->unk60->unk4[i];
                    if ((racer->unk1FB != 0 && i >= 3) || racer->unk1FB == 0) {
                        if (someObj->properties.common.unk0 == 0) {
                            someObj->segment.object.modelIndex--;
                            if (someObj->segment.object.modelIndex < 0) {
                                someObj->segment.object.modelIndex = someObj->segment.header->numberOfModelIds - 1;
                            }
                        } else {
                            someObj->segment.object.modelIndex++;
                            if (someObj->segment.object.modelIndex == someObj->segment.header->numberOfModelIds) {
                                someObj->segment.object.modelIndex = 0;
                            }
                        }
                    }
                }
            }
        }
        flags = 1;
        if (racer->unk1FB != 0) {
            for (i = 0; i < 2; i++) {
                someObj = objRacer->unk60->unk4[i];
                if (someObj->properties.racer.unk0 != 0) {
                    someObj->segment.object.modelIndex--;
                    if (someObj->segment.object.modelIndex < 0) {
                        someObj->segment.object.modelIndex = (s8) (someObj->segment.header->numberOfModelIds - 1);
                    }
                } else {
                    someObj->segment.object.modelIndex++;
                    if (someObj->segment.object.modelIndex == someObj->segment.header->numberOfModelIds) {
                        someObj->segment.object.modelIndex = 0;
                    }
                }
            }
            objRacer->particleEmittersEnabled |= OBJ_EMIT_11 | OBJ_EMIT_12;
        }
        temp_f0 = someObj->segment.trans.y_position; // Fake
        for (i = 0; i < 4; i++) {
            someObj = objRacer->unk60->unk4[i];
            if (!(racer->unk1E3 & flags)) {
                someObj->segment.trans.y_position += ((-10.0f - someObj->segment.trans.y_position) * 0.125);
                if (racer->waterTimer != 0) {
                    someObj->segment.trans.scale +=
                        (((someObj->segment.header->scale * 1.4) - someObj->segment.trans.scale) * 0.1);
                }
            } else {
                temp_f0 = someObj->segment.trans.y_position;
                someObj->segment.trans.y_position = (temp_f0 - (temp_f0 * 0.125));
                someObj->segment.trans.scale += ((someObj->segment.header->scale - someObj->segment.trans.scale) * 0.1);
            }
            flags <<= 1;
        }
        someObj = objRacer->unk60->unk4[2];
        someObj->segment.trans.rotation.y_rotation = gCurrentStickX * 100;
        someObj = objRacer->unk60->unk4[3];
        someObj->segment.trans.rotation.y_rotation = gCurrentStickX * 100;
    }
}

/**
 * Initialise some states when a racer is attacked or runs into something.
 * While the majority of the respondent behaviour takes place elsewhere, the squish behaviour
 * happens here.
 */
void racer_attack_handler_car(Object *obj, Object_Racer *racer, s32 updateRate) {
    s8 bananas;

    if (racer->playerIndex == PLAYER_COMPUTER) {
        bananas = 0;
    } else {
        bananas = racer->bananas;
    }
    if (racer->squish_timer > 0) {
        racer->squish_timer -= updateRate;
        racer->throttle = 0.0f;
        racer->stretch_height_cap = 0.1f;
        if (racer->squish_timer <= 0 && racer->playerIndex > PLAYER_COMPUTER) {
            racer_play_sound(obj, SOUND_PLOP2);
        }
    } else {
        racer->squish_timer = 0;
    }
    if (racer->attackType == 0 || racer->shieldTimer > 0) {
        racer->attackType = ATTACK_NONE;
    } else {
        if (racer->squish_timer == 0 || racer->attackType != ATTACK_SQUISHED) {
            if (racer->attackType != ATTACK_SPIN && racer->attackType != ATTACK_SQUISHED) {
                drop_bananas(obj, racer, 2);
            }
            racer->unk18C = 360;
            if (racer->unk1C9 == 8) {
                racer->unk1C9 = 0;
            }
            if (racer->vehicleID < VEHICLE_BOSSES) {
                play_random_character_voice(obj, SOUND_VOICE_CHARACTER_NEGATIVE, 8, 129);
                switch (racer->attackType) {
                    // Getting hit by a rocket, or running into a landmine.
                    case ATTACK_EXPLOSION:
                        racer->unk1F1 = 1;
                        if (bananas == 0) {
                            racer->velocity = 0.0f;
                            obj->segment.y_velocity += 10.5;
                        } else {
                            racer->velocity /= 4;
                            obj->segment.y_velocity += 8.5;
                        }
                        break;
                    // Running into an oil slick.
                    case ATTACK_SPIN:
                        racer->spinout_timer = 2;
                        racer->y_rotation_vel = 0x1002;
                        racer_play_sound(obj, SOUND_TYRE_SCREECH);
                        break;
                    // Crushed by something big, like a snowball.
                    case ATTACK_SQUISHED:
                        racer->squish_timer = 60;
                        break;
                    // Running into a bubble trap.
                    case ATTACK_BUBBLE:
                        racer->bubbleTrapTimer = 120;
                        racer->velocity *= 0.5;
                        break;
                    // This goes unused.
                    case ATTACK_FLUNG:
                        racer->unk1F1 = 1;
                        racer->velocity = 0.0f;
                        obj->segment.y_velocity += 20.5;
                        racer_play_sound(obj, SOUND_WHEE);
                        break;
                }
                racer->attackType = ATTACK_NONE;
            }
        }
    }
}

/**
 * Only ran when onscreen or nearby, this function handles more authentic, but computationally expensive looking
 * behaviour for AI controlled racers.
 * This function also calls pathing, using splines, to know where to go.
 */
void update_onscreen_AI_racer(Object *obj, Object_Racer *racer, s32 updateRate, f32 updateRateF) {
    f32 tempVel;
    f32 xVel;
    f32 zVel;
    f32 yVel;
    f32 hVel;
    f32 xTemp;
    f32 yTemp;
    f32 zTemp;
    MtxF mtx;
    LevelHeader *header;
    s32 angle;
    s32 steerVel;

    xTemp = obj->segment.trans.x_position;
    yTemp = obj->segment.trans.y_position;
    zTemp = obj->segment.trans.z_position;
    gCurrentCarSteerVel = 0;
    D_8011D558 = 0;
    handle_base_steering(racer, 0, updateRateF);
    handle_car_velocity_control(racer);
    func_800575EC(obj, racer);
    handle_racer_items(obj, racer, updateRate);
    racer_attack_handler_car(obj, racer, updateRate);
    if (racer->spinout_timer) {
        racer_spinout_car(obj, racer, updateRate, updateRateF); // Sbinalla
    } else if (racer->groundedWheels > 0) {
        update_car_velocity_ground(obj, racer, updateRate, updateRateF);
    } else {
        update_car_velocity_offground(obj, racer, updateRate, updateRateF);
    }
    apply_vehicle_rotation_offset(racer, updateRate, 0, 0, 0);
    header = get_current_level_header();
    if ((racer->buoyancy != 0.0 && header->unk2) || gCurrentSurfaceType == SURFACE_FROZEN_WATER) {
        if (racer->unk1F0) {
            racer->checkpoint_distance -= 0.3;
        } else {
            racer->checkpoint_distance -= 0.1;
        }
        set_position_goal_from_path(obj, racer, &xVel, &yVel, &zVel);
        if (racer->unk1F0) {
            racer->checkpoint_distance += 0.3;
        } else {
            racer->checkpoint_distance += 0.1;
        }
        xVel -= obj->segment.trans.x_position;
        zVel -= obj->segment.trans.z_position;
        yVel = sqrtf((xVel * xVel) + (zVel * zVel));
        xVel /= yVel;
        zVel /= yVel;
        obj->segment.x_velocity = xVel * 4.0f;
        obj->segment.z_velocity = zVel * 4.0f;
        obj->segment.y_velocity = 9.5f;
        racer->unk1F0 = 1;
    } else if (racer->groundedWheels > 2) {
        racer->unk1F0 = 0;
    }
    obj->segment.object.animationID = 0;
    steerVel = ((-racer->y_rotation_vel >> 8) / gCurrentRacerHandlingStat);
    steerVel = 40 - steerVel;
    if (steerVel < 0) {
        steerVel = 0;
    }
    if (steerVel > 73) {
        steerVel = 73;
    }
    obj->segment.animFrame = steerVel;
    slowly_reset_head_angle(racer);
    angle = gCurrentCarSteerVel - (u16) racer->y_rotation_vel;
    WRAP(angle, -0x8000, 0x8000);
    angle >>= 2;
    CLAMP(angle, -0x2EE, 0x2EE);
    racer->y_rotation_vel += (angle * updateRate);
    obj->segment.trans.rotation.y_rotation = racer->steerVisualRotation + racer->y_rotation_vel;
    racer->z_rotation_vel += ((D_8011D558 - racer->z_rotation_vel) * updateRate) >> 4;
    obj->segment.trans.rotation.z_rotation = racer->x_rotation_vel + racer->z_rotation_vel;
    if (!racer->unk1F0) {
        gCurrentRacerTransform.rotation.y_rotation = racer->steerVisualRotation + racer->unk10C;
        gCurrentRacerTransform.rotation.x_rotation = 0;
        gCurrentRacerTransform.rotation.z_rotation = 0;
        gCurrentRacerTransform.x_position = 0.0f;
        gCurrentRacerTransform.y_position = 0.0f;
        gCurrentRacerTransform.z_position = 0.0f;
        gCurrentRacerTransform.scale = 1.0f;
        mtxf_from_inverse_transform(&mtx, &gCurrentRacerTransform);
        mtxf_transform_point(&mtx, racer->lateral_velocity, 0.0f, racer->velocity, &obj->segment.x_velocity, &tempVel,
                             &obj->segment.z_velocity);
    }
    if (racer->magnetTimer) {
        obj->segment.x_velocity = gRacerMagnetVelX;
        obj->segment.z_velocity = gRacerMagnetVelZ;
    }
    if (!racer->approachTarget) {
        xVel = obj->segment.x_velocity;
        zVel = obj->segment.z_velocity;
        if (racer->unk1D2 != 0) {
            xVel += racer->unk11C;
            zVel += racer->unk120;
        }
        xVel += racer->unk84;
        zVel += racer->unk88;
        move_object(obj, xVel * updateRateF, obj->segment.y_velocity * updateRateF, zVel * updateRateF);
    } else {
        racer_approach_object(obj, racer, updateRateF);
    }
    if (gCurrentPlayerIndex == PLAYER_COMPUTER && !func_80023568()) {
        onscreen_ai_racer_physics(obj, racer, updateRate);
    } else {
        func_80054FD0(obj, racer, updateRate);
    }
    if (!racer->unk201) {
        obj->particleEmittersEnabled = OBJ_EMIT_NONE;
    } else if (racer->vehicleID < VEHICLE_BOSSES) {
        update_vehicle_particles(obj, updateRate);
    }
    func_80053750(obj, racer, updateRateF);
    tempVel = 1.0f / updateRateF;
    xVel = (((obj->segment.trans.x_position - xTemp) - D_8011D548) * tempVel) - racer->unk84;
    obj->segment.y_velocity = (obj->segment.trans.y_position - yTemp) * tempVel;
    zVel = (((obj->segment.trans.z_position - zTemp) - D_8011D54C) * tempVel) - racer->unk88;
    gCurrentRacerTransform.rotation.y_rotation = -(racer->steerVisualRotation + racer->unk10C);
    gCurrentRacerTransform.rotation.x_rotation = -obj->segment.trans.rotation.x_rotation;
    gCurrentRacerTransform.rotation.z_rotation = -obj->segment.trans.rotation.z_rotation;
    gCurrentRacerTransform.x_position = 0.0f;
    gCurrentRacerTransform.y_position = 0.0f;
    gCurrentRacerTransform.z_position = 0.0f;
    gCurrentRacerTransform.scale = 1.0f;
    mtxf_from_inverse_transform(&mtx, &gCurrentRacerTransform);
    mtxf_transform_point(&mtx, xVel, 0.0f, zVel, &hVel, &tempVel, &yVel);
    if (racer->unk1D2 != 0) {
        racer->unk1D2 -= updateRate;
        if (racer->unk1D2 < 0) {
            racer->unk1D2 = 0;
        }
    } else {
        tempVel = racer->velocity - yVel;
        if (tempVel > 0.5) {
            racer->velocity -= tempVel - 0.5; //!@Delta
        }
        if (tempVel < -0.5) {
            racer->velocity -= tempVel + 0.5; //!@Delta
        }
        tempVel = racer->lateral_velocity - hVel;
        if (tempVel && tempVel) {}
        if (tempVel > 0.5) {
            racer->lateral_velocity -= tempVel - 0.5; //!@Delta
        }
        if (tempVel < -0.5) {
            racer->lateral_velocity -= tempVel + 0.5; //!@Delta
        }
    }
}

/**
 * Gets, sets and works with car velocity while grounded.
 * It also handles turn velocity, too.
 * This function has a large number of timing incorrect physics, responsible for boss vehicles being
 * inconsistently fast, depending on framerate.
 */
void update_car_velocity_ground(Object *obj, Object_Racer *racer, s32 updateRate, f32 updateRateF) {
    s32 xStick;
    s32 stickMultiplier;
    s32 surfaceType;
    s32 sp38;
    f32 temp_f0_2;
    f32 velSquare;
    UNUSED f32 pad;
    f32 traction;
    f32 forwardVel;
    f32 weight;
    f32 vel;
    f32 multiplier;
    s32 rawStick;
    s32 velocityS;
    s32 temp;
    u16 temp2;

    velSquare = racer->velocity * racer->velocity;
    racer->unk84 = 0.0f;
    racer->unk88 = 0.0f;
    if (racer->velocity < 0.0f) {
        velSquare = -velSquare;
    }
    sp38 = 0;
    multiplier = handle_racer_top_speed(obj, racer);
    if (racer->y_rotation_vel > 0x1C00 || racer->y_rotation_vel < -0x1C00) {
        sp38 = 1;
    }
    rawStick = gCurrentStickX;
    stickMultiplier = 6;
    if (gCurrentRacerInput & B_BUTTON) {
        stickMultiplier = 12;
    }
    if (gCurrentRacerInput & B_BUTTON && racer->drift_direction != 0) {
        stickMultiplier = 18;
    }
    xStick = 0;
    if (racer->velocity < -0.3) {
        xStick = rawStick * stickMultiplier;
    }
    if (racer->velocity > 0.3) {
        xStick = -rawStick * stickMultiplier;
    }
    xStick *= updateRate;
    temp = (s32) ((xStick >> 1) * gCurrentRacerHandlingStat);
    temp2 = temp;
    racer->steerVisualRotation -= temp2; //!@Delta
    handle_car_steering(racer);
    racer->lateral_velocity *= 0.9; //!@Delta
    surfaceType = SURFACE_DEFAULT;
    traction = 0.0f;
    if (racer->wheel_surfaces[0] != SURFACE_NONE) {
        traction += gSurfaceTractionTable[racer->wheel_surfaces[0]];
        if (racer->wheel_surfaces[0] > SURFACE_DEFAULT) {
            surfaceType = racer->wheel_surfaces[0];
        }
    }
    if (racer->buoyancy != 0.0) {
        traction = 0.02f;
    }
    gCurrentSurfaceType = surfaceType;
    racer->drift_direction = 0;
    racer->unk10C = 0;
    if (surfaceType == SURFACE_STONE) {
        multiplier = 0.25f;
        racer->lateral_velocity = 0.0f;
    }
    if (racer->boostTimer == 0 && surfaceType == SURFACE_ZIP_PAD) {
        racer->boostTimer = normalise_time(45);
        racer->boostType = BOOST_UNK3;
    }
    racer->velocity -= velSquare * traction; //!@Delta
    if (sp38) {
        if (racer->unk1EE < 16) {
            racer->unk1EE++;
        }
    } else {
        racer->unk1EE = 0;
    }
    if (cam_get_viewport_layout() < 2 && sp38 && racer->velocity < -2.0) {
        if (racer->wheel_surfaces[2] < SURFACE_NONE) {
            obj->particleEmittersEnabled |= 1 << (racer->wheel_surfaces[2] * 2);
        }
        if (racer->wheel_surfaces[3] < SURFACE_NONE) {
            obj->particleEmittersEnabled |= 2 << (racer->wheel_surfaces[3] * 2);
        }
    }
    vel = racer->velocity;
    if (vel < 0.0f) {
        vel = -vel;
    }
    if (vel > 12.0f) {
        vel = 12.0f;
    }
    velocityS = (s32) vel;
    temp_f0_2 = vel - (f32) velocityS;
    vel = (gCurrentRacerMiscAssetPtr[velocityS + 1] * temp_f0_2) +
          (gCurrentRacerMiscAssetPtr[velocityS] * (1.0 - temp_f0_2));
    vel *= 1.7;
    vel *= multiplier;
    if (racer->boostTimer > 0) {
        if (gRaceStartTimer == 0) {
            racer->throttle = 1.0f;
            if (vel != 0.0) {
                vel = 2.0f;
            }
            racer->boostTimer -= updateRate;
        }
    } else {
        racer->boostTimer = 0;
    }
    // If basically at a standstill, then allow reversing.
    if (racer->velocity > -2.0 && racer->velocity < 3.0) {
        f32 reverseVel = (3.0 - racer->velocity) * 0.15;
        if (gCurrentStickY < -25 && !(gCurrentRacerInput & A_BUTTON) && gCurrentRacerInput & B_BUTTON) {
            racer->brake = 0.0f;
            racer->velocity += reverseVel; //!@Delta
        }
    }
    forwardVel = (vel * racer->brake) * 0.32; //!@Delta
    racer->velocity -= vel * racer->throttle; //!@Delta
    if (racer->velocity > -0.04 && racer->velocity < 0.04) {
        racer->velocity = 0.0f;
    }
    if (racer->velocity < 0.0f) {
        racer->velocity += forwardVel; //!@Delta
        if (racer->velocity > 0.0f) {
            racer->velocity = 0.0f;
        }
    } else {
        racer->velocity -= forwardVel; //!@Delta
        if (racer->velocity < 0.0f) {
            racer->velocity = 0.0f;
        }
    }

    // Heavier characters will fall faster.
    weight = gCurrentRacerWeightStat;
    if (racer->buoyancy != 0.0) {
        weight *= 0.5;
    }
    if (racer->brake < 0.9 && gRaceStartTimer == 0) {
        racer->velocity += weight * (racer->pitch / 4) * updateRateF;
    }
    obj->segment.y_velocity -= weight * updateRateF;
}

// Related to ground collision?
void func_80054FD0(Object *racerObj, Object_Racer *racer, s32 updateRate) {
    s32 pad[3];
    s32 sp190;
    s32 flags;
    s32 mask;
    s32 sp184;
    f32 sp180;
    f32 sp17C;
    f32 sp178;
    f32 new_var;
    f32 new_var2;
    s32 i;
    s32 j;
    s32 new_var3;
    f32 sp134[4 * 3]; // 4 sets of 3 floats. (4 Vec3fs don't seem to match?)
    s16 temp_s16;
    s16 sp130;
    f32 sp11C[5];
    f32 sp108[5];
    f32 spF4[5];
    f32 spE0[5];
    MtxF spA0;
    MtxF sp60;
    s8 sp5C;
    s8 sp58[4];

    if (gCurrentCourseHeight < racerObj->segment.trans.y_position) {
        racerObj->segment.trans.y_position = gCurrentCourseHeight;
        func_8002ACC8(1);
    }
    sp130 = FALSE;
    gCurrentRacerTransform.rotation.y_rotation = racerObj->segment.trans.rotation.y_rotation;
    gCurrentRacerTransform.rotation.x_rotation = racerObj->segment.trans.rotation.x_rotation;
    gCurrentRacerTransform.rotation.z_rotation = racerObj->segment.trans.rotation.z_rotation;
    gCurrentRacerTransform.scale = 1.0f;
    gCurrentRacerTransform.x_position = racerObj->segment.trans.x_position;
    gCurrentRacerTransform.y_position = racerObj->segment.trans.y_position;
    gCurrentRacerTransform.z_position = racerObj->segment.trans.z_position;
    mtxf_from_transform(&spA0, &gCurrentRacerTransform);

    for (i = 0; i < 4; i++) {
        mtxf_transform_point(&spA0, D_8011D568[i * 4 + 0], D_8011D568[i * 4 + 1], D_8011D568[i * 4 + 2],
                             &sp134[i * 3 + 0], &sp134[i * 3 + 1], &sp134[i * 3 + 2]);
        spE0[i] = D_8011D568[i * 4 + 3];
        sp58[i] = -1;
    }

    sp190 = 0;
    D_8011D548 = 0;
    D_8011D54C = 0;
    flags = 0;
    if (racer->playerIndex != PLAYER_COMPUTER || racer->vehicleIDPrev < VEHICLE_BOSSES) {
        flags = func_80017248(racerObj, 4, &sp190, &racer->unkD8, sp134, spE0, sp58);
    }
    if (flags & 0x80) {
        for (i = 0; i < 4; i++) {
            D_8011D548 = D_8011D548 + sp134[i * 3 + 0];
            D_8011D54C = D_8011D54C + sp134[i * 3 + 2];
        }
        D_8011D548 = D_8011D548 / 4;
        D_8011D54C = D_8011D54C / 4;
        D_8011D548 = D_8011D548 - racerObj->segment.trans.x_position;
        D_8011D54C = D_8011D54C - racerObj->segment.trans.z_position;
        sp130 = TRUE;
        flags &= ~0x80;
    }
    sp5C = 0;
    if (flags) {
        sp178 = 0;
        for (i = 0; i < 4; i++) {
            sp178 += sp134[i * 3 + 1];
        }
        sp178 *= 0.25;
        if (sp178 < (racerObj->segment.trans.y_position - 4.0)) {
            sp5C = 1;
        }
    }
    func_80031130(4, (f32 *) &racer->unkD8, sp134, racer->vehicleID);
    sp190 = 0;
    racer->unk1E3 = func_80031600((f32 *) &racer->unkD8, sp134, spE0, sp58, 4, &sp190);
    sp184 = func_8002ACD4(&sp180, &sp178, &sp17C);
    if (sp184 != 0) {
        temp_s16 = (u16) arctan2_f(sp180 * 255.0f, sp17C * 255.0f);
        temp_s16 -= racerObj->segment.trans.rotation.y_rotation;
        if ((temp_s16 < 0x2000 && temp_s16 > -0x2000) || racer->vehicleID == VEHICLE_HOVERCRAFT) {
            sp178 = racer->velocity * 1.075;
            if (sp178 < 0) {
                sp178 = -sp178;
            }
            if (sp178 > 1.0) {
                rumble_set_fade(racer->playerIndex, 18, sp178 * 0.125);
            }
            if (sp178 > 4.0) {
                racer->unk1F3 |= 8;
                if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
                    gCameraObject->shakeMagnitude = 3.0f;
                }
                racer->unk1D2 = 7;
                if (racer->playerIndex != PLAYER_COMPUTER) {
                    play_random_character_voice(racerObj, SOUND_VOICE_CHARACTER_NEGATIVE, 8, 0x80 | 0x2);
                    racer_play_sound(racerObj, SOUND_CRASH);
                }
                racer->boost_sound |= BOOST_SOUND_UNK4;
                if (racer->vehicleID == VEHICLE_HOVERCRAFT) {
                    sp178 *= 0.5;
                }
                racer->unk11C = sp180 * sp178;
                racer->unk120 = sp17C * sp178;
                racer->velocity *= 0.15;
                racer->lateral_velocity = 0;
            }
        }
    }
    if (sp5C && sp190 >= 3) {
        if (racer->playerIndex != PLAYER_COMPUTER && racer->unk20 == 0 && racer->shieldTimer <= 0) {
            sound_play(SOUND_SPLAT, &racer->unk20);
        }
        if (racer->squish_timer == 0) {
            racer->attackType = ATTACK_SQUISHED;
        } else {
            racer->squish_timer = 60;
        }
    }
    racer->unk1E4 = flags;
    racer->unk1E3 |= flags;

    racer->groundedWheels = 0;
    flags = 1;
    for (j = 0; j < 4; j++) {
        if (racer->unk1E3 & flags) {
            racer->groundedWheels++;
        }
        flags <<= 1;
    }

    for (i = 0; i < 12; i++) {
        ((f32 *) &racer->unkD8)[i] = sp134[i];
    }
    for (i = 0; i < 4; i++) {
        racer->wheel_surfaces[i] = sp58[i];
    }
    racerObj->segment.trans.x_position = 0;
    racerObj->segment.trans.y_position = 0;
    racerObj->segment.trans.z_position = 0;
    for (i = 0; i < 12; i += 3) {
        racerObj->segment.trans.x_position = racerObj->segment.trans.x_position + ((f32 *) &racer->unkD8)[i + 0];
        racerObj->segment.trans.y_position = racerObj->segment.trans.y_position + ((f32 *) &racer->unkD8)[i + 1];
        racerObj->segment.trans.z_position = racerObj->segment.trans.z_position + ((f32 *) &racer->unkD8)[i + 2];
    }
    racerObj->segment.trans.x_position /= 4;
    racerObj->segment.trans.y_position /= 4;
    racerObj->segment.trans.z_position /= 4;

    gCurrentRacerTransform.rotation.y_rotation = -racerObj->segment.trans.rotation.y_rotation;
    gCurrentRacerTransform.rotation.x_rotation = -racerObj->segment.trans.rotation.x_rotation;
    gCurrentRacerTransform.rotation.z_rotation = -racerObj->segment.trans.rotation.z_rotation;
    gCurrentRacerTransform.scale = 1.0f;
    gCurrentRacerTransform.x_position = -racerObj->segment.trans.x_position;
    gCurrentRacerTransform.y_position = -racerObj->segment.trans.y_position;
    gCurrentRacerTransform.z_position = -racerObj->segment.trans.z_position;
    mtxf_from_inverse_transform(&sp60, &gCurrentRacerTransform);
    for (i = 0; i < 4; i++) {
        mtxf_transform_point(&sp60, ((f32 *) &racer->unkD8)[i * 3 + 0], ((f32 *) &racer->unkD8)[i * 3 + 1],
                             ((f32 *) &racer->unkD8)[i * 3 + 2], &sp11C[i], &sp108[i], &spF4[i]);
    }
    if (racer->vehicleID != VEHICLE_LOOPDELOOP) {
        sp180 = sp11C[0] + sp11C[1];
        sp17C = spF4[0] + spF4[1];
        new_var = sp11C[2] + sp11C[3];
        new_var2 = spF4[2] + spF4[3];
        new_var3 = (arctan2_f(sp180 - new_var, sp17C - new_var2) + 0x8000) & 0xFFFF;
        temp_s16 = new_var3;
        if (racer->unk1D2 == 7) {
            if (temp_s16 > 0) {
                racer->unk19C = 2048;
            }
            if (temp_s16 < 0) {
                racer->unk19C = -2048;
            }
        }
        if (racer->unk1D2 != 0) {
            temp_s16 = racer->unk19C;
        }
        if (temp_s16 > 500 || temp_s16 < -500) {
            racer->drift_direction = 0;
            racer->unk10C = (s32) (racer->unk10C * 7) >> 3;
            racer->y_rotation_vel = (s16) ((s32) (racer->y_rotation_vel * 7) >> 3);
        }
        if (sp130) {
            temp_s16 *= 4;
        }
        racerObj->segment.trans.rotation.y_rotation += temp_s16 >> 2;
        racer->steerVisualRotation = racerObj->segment.trans.rotation.y_rotation - racer->y_rotation_vel;
    }
    sp180 = spF4[2] - spF4[0];
    sp17C = sp108[2] - sp108[0];
    temp_s16 = arctan2_f(sp180, sp17C) & 0xFFFF;
    temp_s16 -= 0x4000;
    if (sp184 == 0) {
        racerObj->segment.trans.rotation.x_rotation += temp_s16;
    }
    sp180 = (sp11C[1] - sp11C[0]);
    sp17C = (sp108[1] - sp108[0]);
    temp_s16 = (0x4000 - (arctan2_f(sp180, sp17C)));
    if (sp184 == 0) {
        racer->x_rotation_vel += temp_s16 & 0xFFFF & 0xFFFF & 0xFFFF;
    }
    if (racer->vehicleID != VEHICLE_LOOPDELOOP && racer->vehicleID != VEHICLE_PLANE &&
        racer->vehicleID != VEHICLE_CARPET && racer->vehicleID != VEHICLE_SMOKEY) {
        CLAMP(racer->x_rotation_vel, -0x3400, 0x3400);
        CLAMP(racerObj->segment.trans.rotation.x_rotation, -0x3400, 0x3400);
    }
}

/**
 * Update the collision of the racer.
 * Also update wheel contacts and hitbox size.
 */
void onscreen_ai_racer_physics(Object *obj, Object_Racer *racer, UNUSED s32 updateRate) {
    f32 angleZ;
    f32 distance;
    s32 hasCollision;
    s32 flags;
    s32 temp_v1_2;
    f32 xTemp;
    f32 yTemp;
    f32 zTemp;
    s32 xRot;
    f32 angleX;
    f32 *racerSize;
    Vec3f tempPos;
    s32 i;
    f32 radius;
    s8 surface;
    s8 shouldSquish;

    if (obj->segment.trans.y_position > gCurrentCourseHeight) {
        obj->segment.trans.y_position = gCurrentCourseHeight;
    }
    racerSize = (f32 *) get_misc_asset(ASSET_MISC_RACER_HITBOX_SIZE);
    surface = SURFACE_NONE;
    radius = racerSize[racer->vehicleIDPrev];
    tempPos.x = obj->segment.trans.x_position;
    tempPos.y = obj->segment.trans.y_position;
    tempPos.z = obj->segment.trans.z_position;
    D_8011D548 = 0.0f;
    D_8011D54C = 0.0f;
    hasCollision = FALSE;
    flags = 0;
    if (racer->playerIndex != PLAYER_COMPUTER || racer->vehicleIDPrev < VEHICLE_BOSSES) {
        flags = func_80017248(obj, 1, &hasCollision, &racer->unkD8, &tempPos.x, &radius, &surface);
    }
    if (flags & 0x80) {
        D_8011D548 = tempPos.x - obj->segment.trans.x_position;
        D_8011D54C = tempPos.z - obj->segment.trans.z_position;
        flags &= ~0x80;
    }
    shouldSquish = FALSE;
    if (flags && tempPos.y < obj->segment.trans.y_position - 4.0) {
        shouldSquish = TRUE;
    }
    func_80031130(1, &racer->unkD8.x, &tempPos.x, racer->vehicleID);
    hasCollision = FALSE;
    racer->unk1E3 = func_80031600(&racer->unkD8.x, &tempPos.x, &radius, &surface, TRUE, &hasCollision);
    racer->unk1E4 = flags;
    racer->unk1E3 |= flags;
    racer->groundedWheels = 0;
    if (racer->unk1E3) {
        racer->unk1E3 = 0x8 | 0x4 | 0x2 | 0x1;
        racer->groundedWheels = 4;
    }
    if (shouldSquish && hasCollision) {
        if (racer->squish_timer == 0) {
            racer->attackType = ATTACK_SQUISHED;
        } else {
            racer->squish_timer = 60;
        }
    }
    for (i = 0; i < 3; i++) {
        racer->unkD8.f[i] = tempPos.f[i];
    }
    i = 1; // Fakematch
    racer->wheel_surfaces[0] = surface;
    racer->wheel_surfaces[1] = surface;
    racer->wheel_surfaces[2] = surface;
    racer->wheel_surfaces[3] = surface;
    obj->segment.trans.x_position = racer->unkD8.x;
    obj->segment.trans.y_position = racer->unkD8.y;
    obj->segment.trans.z_position = racer->unkD8.z;
    if (racer->groundedWheels) {
        func_8002ACD4(&xTemp, &yTemp, &zTemp);
        angleX = sins_f(-obj->segment.trans.rotation.y_rotation);
        angleZ = coss_f(-obj->segment.trans.rotation.y_rotation);
        distance = (xTemp * angleZ) + (zTemp * angleX);
        zTemp = (xTemp * angleX) - (zTemp * angleZ);
        temp_v1_2 = -(s16) (u16) arctan2_f(distance, yTemp);
        if (temp_v1_2 < 0x2000 && temp_v1_2 > -0x2000) {
            racer->x_rotation_vel = temp_v1_2;
        }
        xRot = -(s16) (u16) arctan2_f(zTemp, yTemp);
        if (xRot < 0x2000 && xRot > -0x2000) {
            obj->segment.trans.rotation.x_rotation = xRot;
        }
        if (racer->vehicleID == VEHICLE_LOOPDELOOP) {
            if (1) { // Fakematch
                xRot -= (u16) obj->segment.trans.rotation.x_rotation;
            }
            WRAP(xRot, -0x8000, 0x8000);
            obj->segment.trans.rotation.x_rotation += xRot >> 2;
        }
    }
    if (racer->vehicleID != VEHICLE_LOOPDELOOP && racer->vehicleID != VEHICLE_PLANE &&
        racer->vehicleID != VEHICLE_CARPET && racer->vehicleID != VEHICLE_SMOKEY) {
        CLAMP(racer->x_rotation_vel, -0x3400, 0x3400);
        CLAMP(obj->segment.trans.rotation.x_rotation, -0x3400, 0x3400);
    }
}

/**
 * Handles the input and activation of any weapons the player is carrying.
 * Also handles the egg object from Fire Mountain, which takes precedent, even if the player is holding a weapon.
 */
void handle_racer_items(Object *obj, Object_Racer *racer, UNUSED s32 updateRate) {
    LevelObjectEntryCommon newObject;
    s32 weaponID;
    Object *spawnedObj;
    s32 objID;
    Object *heldObj;
    Object *intendedTarget;
    Object_Racer *magnetTarget;
    f32 objDist;
    ObjectModel *model;
    Object_Weapon *weapon;
    f32 velocity;
    f32 distance;
    f32 scaleY;
    f32 scaleZ;
    UNUSED s32 pad[2];
    s8 *miscAsset;
    Vertex *heldObjData;
    u16 soundID = SOUND_NONE;

    if (racer->held_obj != NULL) {
        heldObj = racer->held_obj;
        if (gCurrentButtonsPressed & Z_TRIG || racer->raceFinished || racer->attackType) {
            scaleY = 0;
            scaleZ = 0;
            if (obj->unk68[obj->segment.object.modelIndex] != NULL) {
                model = obj->unk68[obj->segment.object.modelIndex]->objModel;
                if (obj->segment.header->unk58 > -1 && obj->segment.header->unk58 < model->unk18) {
                    if (obj->curVertData != NULL) {
                        heldObjData = obj->curVertData;
                        heldObjData += model->unk14[obj->segment.header->unk58];
                        scaleY = heldObjData->y;
                        scaleY *= obj->segment.trans.scale;
                        scaleZ = heldObjData->z;
                        scaleZ *= obj->segment.trans.scale;
                    }
                }
            }
            heldObj->segment.trans.x_position =
                obj->segment.trans.x_position + (racer->ox1 * scaleZ) + (racer->ox2 * scaleY);
            heldObj->segment.trans.y_position =
                obj->segment.trans.y_position + (racer->oy1 * scaleZ) + (racer->oy2 * scaleY);
            heldObj->segment.trans.z_position =
                obj->segment.trans.z_position + (racer->oz1 * scaleZ) + (racer->oz2 * scaleY);
            heldObj->segment.object.segmentID = obj->segment.object.segmentID;
            heldObj->segment.x_velocity = obj->segment.x_velocity * 0.7;
            heldObj->segment.y_velocity = obj->segment.y_velocity - 2.0;
            heldObj->segment.z_velocity = obj->segment.z_velocity * 0.7;
            heldObjData = (Vertex *) &heldObj->unk64->egg;
            ((Object_64 *) heldObjData)->egg.status = EGG_MOVING;
            racer->held_obj = NULL;
            racer->unk211 = 1;
        }
    } else {
        if (gCurrentButtonsPressed & Z_TRIG) {
            racer->unk211 = 0;
        }
        if (racer->unk211) {
            gCurrentButtonsReleased = 0;
            gCurrentButtonsPressed &= ~Z_TRIG;
        }
        if (racer->magnetTimer == 0) {
            racer->magnetTargetObj = NULL;
        }
        if (racer->balloon_type == -1) {
            racer->balloon_quantity = 0;
        }
        if (racer->balloon_quantity <= 0) {
            if (gCurrentButtonsPressed & Z_TRIG) {
                play_char_horn_sound(obj, racer);
            }
        } else {
            miscAsset = (s8 *) get_misc_asset(ASSET_MISC_BALLOON_DATA);
            weaponID = miscAsset[(racer->balloon_type * 10) + (racer->balloon_level * 2)];
            if (miscAsset[(racer->balloon_type * 10) + (racer->balloon_level * 2)] == WEAPON_NONE) {
                racer->balloon_quantity = 0;
                return;
            }
            magnetTarget = NULL;
            if (gCurrentButtonsPressed & Z_TRIG) {
                hud_sound_stop(SOUND_VOICE_TT_POWERUP, racer->playerIndex);
            }
            if (racer->magnetLevel3) {
                if (racer->magnetTimer == 0) {
                    racer->magnetLevel3 = FALSE;
                } else {
                    return;
                }
            }
            if (gCurrentRacerInput & Z_TRIG || gCurrentButtonsReleased & Z_TRIG) {
                switch (weaponID) {
                    case WEAPON_ROCKET_HOMING:
                        intendedTarget = func_8005698C(obj, racer, &objDist);
                        racer->magnetTimer = 0;
                        racer->magnetTargetObj = intendedTarget;
                        break;
                    case WEAPON_MAGNET_LEVEL_1:
                    case WEAPON_MAGNET_LEVEL_3:
                    case WEAPON_MAGNET_LEVEL_2:
                        intendedTarget = func_8005698C(obj, racer, &objDist);
                        racer->magnetTimer = 0;
                        if (weaponID == WEAPON_MAGNET_LEVEL_1) {
                            distance = 1000.0f;
                        } else {
                            distance = 1500.0f;
                        }
                        if (objDist < distance) {
                            if (weaponID == WEAPON_MAGNET_LEVEL_3 && intendedTarget != NULL) {
                                magnetTarget = &intendedTarget->unk64->racer;
                            }
                            racer->magnetTargetObj = intendedTarget;
                        } else {
                            racer->magnetTargetObj = NULL;
                            intendedTarget = NULL;
                        }
                        break;
                }
            }
            objID = ASSET_OBJECT_ID_MISSILE;
            if (gCurrentButtonsReleased & Z_TRIG) {
                velocity = 30.0f;
                switch (weaponID) {
                    case WEAPON_ROCKET_HOMING:
                        objDist = -10.0f;
                        objID = ASSET_OBJECT_ID_HOMING;
                        break;
                    case WEAPON_ROCKET:
                        objDist = -10.0f;
                        break;
                    case WEAPON_TRIPMINE:
                    case WEAPON_UNK_11:
                        objDist = 10.0f;
                        velocity = -2.0f;
                        objID = ASSET_OBJECT_ID_BOMB;
                        break;
                    case WEAPON_OIL_SLICK:
                        if (racer->vehicleID != VEHICLE_PLANE) {
                            objID = ASSET_OBJECT_ID_OILSLICK;
                        } else {
                            objID = ASSET_OBJECT_ID_SMOKECLOUD;
                        }
                        objDist = 10.0f;
                        velocity = -2.0f;
                        break;
                    case WEAPON_BUBBLE_TRAP:
                        objDist = 10.0f;
                        velocity = -2.0f;
                        objID = ASSET_OBJECT_ID_BUBBLEWEAPON;
                        intendedTarget = NULL;
                        break;
                    case WEAPON_NITRO_LEVEL_1:
                    case WEAPON_NITRO_LEVEL_2:
                    case WEAPON_NITRO_LEVEL_3:
                        // clang-format off
                        switch (weaponID) {
                            case WEAPON_NITRO_LEVEL_3:
                                // IDO demands this to be on 1 line.
                                racer->boostTimer = normalise_time(75); \
                                racer->boostType = BOOST_LARGE;
                                break;
                            case WEAPON_NITRO_LEVEL_2:
                                // Ditto
                                racer->boostTimer = normalise_time(55); \
                                racer->boostType = BOOST_MEDIUM;
                                break;
                            default:
                                // :(
                                racer->boostTimer = normalise_time(35); \
                                racer->boostType = BOOST_SMALL;
                                break;
                        }
                        // clang-format on
                        if (racer->throttleReleased) {
                            racer->boostType |= EMPOWER_BOOST;
                        }
                        if (weaponID == WEAPON_NITRO_LEVEL_3) {
                            racer_play_sound(obj, SOUND_NITRO_LEVEL3_CHARGE);
                            racer_play_sound_after_delay(obj, SOUND_NITRO_LEVEL3_BOOST, 30);
                        } else {
                            racer_play_sound(obj, SOUND_NITRO_BOOST);
                        }
                        racer->balloon_quantity -= 1;
                        if (weaponID == WEAPON_NITRO_LEVEL_1) {
                            if (racer->raceFinished == FALSE) {
                                rumble_set(racer->playerIndex, RUMBLE_TYPE_6);
                            }
                        } else if (racer->raceFinished == FALSE) {
                            rumble_set(racer->playerIndex, RUMBLE_TYPE_8);
                        }
                        return;
                    case WEAPON_MAGNET_LEVEL_1:
                    case WEAPON_MAGNET_LEVEL_2:
                        racer->balloon_quantity -= 1;
                        if (racer->playerIndex != PLAYER_COMPUTER) {
                            if (intendedTarget != NULL) {
                                racer->magnetTimer = 90;
                                racer->magnetModelID = (weaponID - WEAPON_MAGNET_LEVEL_1) >> 1;
                            }
                            if (racer->raceFinished == FALSE) {
                                rumble_set(racer->playerIndex, RUMBLE_TYPE_15);
                            }
                        }
                        return;
                    case WEAPON_MAGNET_LEVEL_3:
                        racer->balloon_quantity -= 1;
                        racer->magnetTargetObj = NULL;
                        if (racer->playerIndex != PLAYER_COMPUTER) {
                            if (magnetTarget != NULL) {
                                magnetTarget->magnetLevel3 = TRUE;
                                magnetTarget->magnetTimer = 120;
                                magnetTarget->magnetTargetObj = obj;
                                magnetTarget->magnetModelID = MAGNET_LEVEL3;
                            }
                            if (racer->raceFinished == FALSE) {
                                rumble_set(racer->playerIndex, RUMBLE_TYPE_15);
                            }
                        }
                        return;
                    case WEAPON_SHIELD_LEVEL_1:
                        racer->shieldType = SHIELD_LEVEL1;
                        racer->shieldTimer = 300;
                        racer->balloon_quantity -= 1;
                        return;
                    case WEAPON_SHIELD_LEVEL_2:
                        racer->shieldType = SHIELD_LEVEL2;
                        racer->balloon_quantity -= 1;
                        racer->shieldTimer = 600;
                        return;
                    case WEAPON_SHIELD_LEVEL_3:
                        racer->shieldType = SHIELD_LEVEL3;
                        racer->shieldTimer = 900;
                        racer->balloon_quantity -= 1;
                        return;
                    default:
                        objDist = 0;
                        break;
                }
                play_random_character_voice(obj, SOUND_VOICE_CHARACTER_POSITIVE, 8, 129);
                newObject.x = obj->segment.trans.x_position + (racer->ox1 * objDist);
                newObject.y = obj->segment.trans.y_position + (racer->oy1 * objDist) + (10.0f * racer->oy2);
                newObject.z = obj->segment.trans.z_position + (racer->oz1 * objDist);
                newObject.size = sizeof(LevelObjectEntryCommon);
                newObject.objectID = objID;
                spawnedObj = spawn_object(&newObject, OBJECT_SPAWN_UNK01);
                if (spawnedObj != NULL) {
                    spawnedObj->segment.level_entry = NULL;
                    spawnedObj->segment.x_velocity = obj->segment.x_velocity - (racer->ox1 * velocity);
                    spawnedObj->segment.y_velocity = obj->segment.y_velocity - (racer->oy1 * velocity);
                    spawnedObj->segment.z_velocity = obj->segment.z_velocity - (racer->oz1 * velocity);
                    spawnedObj->segment.trans.rotation.y_rotation = obj->segment.trans.rotation.y_rotation;
                    spawnedObj->segment.trans.rotation.x_rotation = obj->segment.trans.rotation.x_rotation;
                    if (racer->vehicleID == VEHICLE_HOVERCRAFT && racer->waterTimer) {
                        if (spawnedObj->segment.trans.rotation.x_rotation > -0x400 &&
                            spawnedObj->segment.trans.rotation.x_rotation < 0x400) {
                            spawnedObj->segment.trans.rotation.x_rotation = 0;
                        }
                    }
                    weapon = &spawnedObj->unk64->weapon;
                    weapon->owner = obj;
                    weapon->target = intendedTarget;
                    weapon->checkpoint = racer->checkpoint;
                    weapon->forwardVel = (racer->velocity - velocity);
                    weapon->weaponID = weaponID;
                    switch (weapon->weaponID) {
                        case WEAPON_ROCKET_HOMING:
                            soundID = SOUND_NYOOM2;
                            break;
                        case WEAPON_ROCKET:
                            soundID = SOUND_NYOOM3;
                            break;
                        case WEAPON_TRIPMINE:
                            soundID = SOUND_PLOP;
                            break;
                        case WEAPON_OIL_SLICK:
                            if (racer->vehicleID != VEHICLE_PLANE) {
                                spawnedObj->shadow->scale = 0;
                            }
                            soundID = SOUND_SPLOINK2;
                            break;
                        case WEAPON_BUBBLE_TRAP:
                            soundID = SOUND_PLOP;
                            break;
                        case WEAPON_UNK_11:
                            spawnedObj->segment.animFrame = 0;
                            break;
                    }
                    if (soundID != SOUND_NONE) {
                        if (racer->playerIndex == PLAYER_COMPUTER) {
                            audspat_play_sound_at_position(soundID, obj->segment.trans.x_position,
                                                           obj->segment.trans.y_position, obj->segment.trans.z_position,
                                                           AUDIO_POINT_FLAG_ONE_TIME_TRIGGER, NULL);
                        } else {
                            if (racer->weaponSoundMask) {
                                sndp_stop(racer->weaponSoundMask);
                            }
                            sound_play_spatial(soundID, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                               obj->segment.trans.z_position, &racer->weaponSoundMask);
                        }
                    }
                }
                if (racer->balloon_quantity > 0) {
                    racer->balloon_quantity = racer->balloon_quantity - 1;
                } else {
                    racer->balloon_quantity = 0;
                }
            }
        }
    }
}

/**
 * Honk honk
 */
void play_char_horn_sound(Object *obj, Object_Racer *racer) {
    if (get_filtered_cheats() & CHEAT_HORN_CHEAT) {
        // Play character voice instead of horn.
        play_random_character_voice(obj, SOUND_VOICE_CHARACTER_POSITIVE, 8, 130);
    } else {
        // Play character's horn sound
        racer_play_sound(obj, racer->characterId + SOUND_HORN_CHARACTER);
    }
}

// Used for magnet and homing rockets to get the distance to the nearest racer.
Object *func_8005698C(Object *racerObj, Object_Racer *racer, f32 *outDistance) {
    Object_Racer *curRacer;
    s32 i;
    f32 curDistance;
    f32 racerOx1;
    UNUSED s32 pad;
    f32 racerOy1;
    Object *savedRacerObj;
    Object *curRacerObj;
    Object **racerObjects;
    f32 racerOz1;
    f32 racerOx3;
    f32 racerOz3;
    f32 savedDist;
    f32 racerO1dist;
    f32 racerOy3;
    f32 racerO3dist;
    f32 curDistance2;
    s32 numRacers;
    f32 savedDist2;
    s32 isChallengeRace;
    s32 raceType;

    raceType = get_current_level_race_type();
    isChallengeRace = raceType & RACETYPE_CHALLENGE;
    if (racer->playerIndex == PLAYER_COMPUTER && !isChallengeRace) {
        curDistance = 0.0f;
        curRacerObj = func_8001B7A8(racer, 1, &curDistance);
        *outDistance = curDistance;
        return curRacerObj;
    }
    racerOx1 = racer->ox1;
    racerOy1 = racer->oy1;
    racerOz1 = racer->oz1;
    racerO1dist = -((racerObj->segment.trans.x_position * racerOx1) + (racerObj->segment.trans.y_position * racerOy1) +
                    (racerObj->segment.trans.z_position * racerOz1));
    racerOx3 = racer->ox3;
    racerOy3 = racer->oy3;
    racerOz3 = racer->oz3;
    racerO3dist = -((racerObj->segment.trans.x_position * racerOx3) + (racerObj->segment.trans.y_position * racerOy1) +
                    (racerObj->segment.trans.z_position * racerOz3));
    racerObjects = get_racer_objects(&numRacers);
    // TODO: Need better names for these
    savedDist2 = 10000.0f;
    savedDist = 10000.0f;
    savedRacerObj = NULL;
    for (i = 0; i < numRacers; i++) {
        if (racerObj != racerObjects[i]) {
            curRacerObj = racerObjects[i];
            curRacer = &racerObjects[i]->unk64->racer;
            if ((!isChallengeRace || !curRacer->raceFinished) && curRacer->elevation == racer->elevation) {
                curDistance = -((racerOx1 * curRacerObj->segment.trans.x_position) +
                                (racerOy1 * curRacerObj->segment.trans.y_position) +
                                (racerOz1 * curRacerObj->segment.trans.z_position) + racerO1dist);
                if (curDistance > 0.0f) {
                    curDistance2 = (racerOx3 * curRacerObj->segment.trans.x_position) +
                                   (racerOy3 * curRacerObj->segment.trans.y_position) +
                                   (racerOz3 * curRacerObj->segment.trans.z_position) + racerO3dist;
                    if (curDistance2 < 0.0f) {
                        curDistance2 = -curDistance2;
                    }
                    if ((curDistance2 < curDistance || raceType == RACETYPE_BOSS) && curDistance2 < savedDist2) {
                        savedDist = curDistance;
                        savedDist2 = curDistance2;
                        savedRacerObj = curRacerObj;
                    }
                }
            }
        }
    }
    *outDistance = savedDist;
    return savedRacerObj;
}

/**
 * When active, takes the magnet target, calculates the distance then sets the player's velocity
 * and movement direction towards the target until they either get close, or the timer runs out.
 * Shields will also cancel out the magnet.
 */
void racer_activate_magnet(Object *obj, Object_Racer *racer, s32 updateRate) {
    f32 diffX;
    f32 diffZ;
    f32 vel;
    Object_Racer *magnetTarget;

    racer->magnetTimer -= updateRate;
    if (racer->magnetTimer < 0) {
        racer->magnetTimer = 0;
        return;
    }
    if (racer->magnetTargetObj == NULL) {
        racer->magnetTimer = 0;
        return;
    }
    diffX = racer->magnetTargetObj->segment.trans.x_position - obj->segment.trans.x_position;
    diffZ = racer->magnetTargetObj->segment.trans.z_position - obj->segment.trans.z_position;
    vel = sqrtf((diffX * diffX) + (diffZ * diffZ));
    if (vel > 150.0f && vel < 2000.0f) {
        if (racer->playerIndex != PLAYER_COMPUTER) {
            racer->boostTimer = 3;
        }
        racer->boostType = BOOST_NONE;
        if (racer->throttleReleased) {
            racer->boostType |= EMPOWER_BOOST;
        }
        if (racer->magnetSoundMask == NULL && racer->raceFinished == FALSE) {
            sound_play(SOUND_MAGNET_HUM, &racer->magnetSoundMask);
        }
    } else {
        racer->magnetTimer = 0;
        return;
    }
    diffX /= vel;
    diffZ /= vel;
    magnetTarget = &racer->magnetTargetObj->unk64->racer;
    vel = -magnetTarget->velocity;
    if (vel < 8.0 && racer->magnetLevel3 == FALSE) {
        vel = 8.0f;
    }
    if (vel > 20.0) {
        vel = 20.0f;
    }
    gRacerMagnetVelX = (vel + 5.0f) * diffX;
    gRacerMagnetVelZ = (vel + 5.0f) * diffZ;
    if (magnetTarget->shieldTimer && racer->magnetLevel3 == FALSE) {
        racer->magnetTimer = 0;
    }
}

/**
 * Play a spatial sound, emitting from the position of the racer object.
 * Only affects human players that aren't in the middle of going through an exit.
 */
void racer_play_sound(Object *obj, s32 soundID) {
    Object_Racer *racer = &obj->unk64->racer;
    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->exitObj == NULL) {
        sound_play_spatial(soundID, obj->segment.trans.x_position, obj->segment.trans.y_position,
                           obj->segment.trans.z_position, NULL);
    }
}

/**
 * Set a timer and sound ID.
 * When that timer counts zero in the racer's update loop, it plays the sound passed through here.
 */
void racer_play_sound_after_delay(Object *obj, s32 soundID, s32 delay) {
    Object_Racer *racer = &obj->unk64->racer;
    racer->delaySoundID = soundID;
    racer->delaySoundTimer = delay;
}

/**
 * Play a random character voice clip from the given offset.
 * It uses SOUND_VOICE_CHARACTER_POSITIVE and SOUND_VOICE_CHARACTER_NEGATIVE for
 * acceptable offsets. Range will always be 8, because that's how many ID's for each
 * there are.
 */
void play_random_character_voice(Object *obj, s32 soundID, s32 range, s32 flags) {
    s32 soundIndex;
    Object_Racer *tempRacer;

    tempRacer = &obj->unk64->racer;
    if (tempRacer->exitObj == 0 && (!(flags & 0x80) || gCurrentPlayerIndex != PLAYER_COMPUTER)) {
        if (flags == 2) {
            if (tempRacer->soundMask != NULL && soundID != tempRacer->unk2A) {
                audspat_point_stop(tempRacer->soundMask);
                tempRacer->soundMask = 0;
            }
        }
        if (tempRacer->soundMask == NULL && (flags != 3 || rand_range(0, 1))) {
            tempRacer->unk2A = soundID;
            soundID += tempRacer->characterId;
            soundIndex = (rand_range(0, range - 1) * 12) + soundID;
            if (range - 1 > 0) {
                while (soundIndex == tempRacer->lastSoundID) {
                    soundIndex = (rand_range(0, range - 1) * 12) + soundID;
                }
            }
            audspat_play_sound_at_position(soundIndex, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                           obj->segment.trans.z_position, AUDIO_POINT_FLAG_ONE_TIME_TRIGGER,
                                           &tempRacer->soundMask);
            tempRacer->lastSoundID = soundIndex;
        }
    }
}

/**
 * This function dictates the base top speed of a racer.
 * During the race start sequence it hardsets it to 0 so you don't go anywhere.
 * It then adds to the multiplier an amount based on your bananas.
 */
f32 handle_racer_top_speed(Object *obj, Object_Racer *racer) {
    f32 speedMultiplier;
    s32 timer;
    f32 bananas;
    f32 cap;
    s32 timer2;
    s32 timer3;

    // If you want to change the baseline speed of vehicles, this is what you change.
    speedMultiplier = 1.0f;
    // Set the player's top speed to 0 before the race starts, so you can't jump the start.
    if (gRaceStartTimer) {
        speedMultiplier = 0.0f;
    }
    timer3 = get_race_start_timer();
    if (gRaceStartTimer) {} // Fakematch
    // If the A button is held for the first time, 30 frames prior to starting,
    // decide how much boost to add based on when it was pressed.
    if (gRaceStartTimer > 0 && gRaceStartTimer < 30 && !racer->startInput) {
        timer = gRaceStartTimer - 14;
        if (gCurrentButtonsPressed & A_BUTTON) {
            if (timer < 0 && timer3 >= 0) {
                timer = 0;
            }
            // Keep the timer positive.
            if (timer < 0) {
                timer = -timer;
            }
            if (gCurrentRacerInput & Z_TRIG) {
                if (timer < 2) {
                    timer = 0;
                }
            }
            timer2 = 24 - timer;
            racer->boostTimer = normalise_time(timer2 >> 1);
            if (timer2 == 24) {
                racer_play_sound(obj, SOUND_SELECT);
                racer->boostTimer = normalise_time(20);
            }
            if (racer->boostTimer < normalise_time(20)) {
                racer->boostType = BOOST_SMALL;
            } else if (racer->boostTimer < normalise_time(35)) {
                racer->boostType = BOOST_MEDIUM;
            } else {
                racer->boostType = BOOST_LARGE;
            }
            racer->boost_sound |= BOOST_RACE_START;
            D_8011D560 = 7;
            gStartBoostTime = racer->boostTimer;
        }
        // For the AI, expert AI will match the players start, and master AI will get a good start always.
        if (racer->playerIndex == PLAYER_COMPUTER &&
            (racer->aiSkill == AI_MASTER || (racer->aiSkill == AI_EXPERT && gStartBoostTime))) {
            if (gStartBoostTime) {
                racer->boostTimer = gStartBoostTime;
            } else {
                racer->boostTimer = normalise_time(5);
            }
            if (racer->boostTimer < normalise_time(20)) {
                racer->boostType = BOOST_SMALL;
            } else if (racer->boostTimer < normalise_time(35)) {
                racer->boostType = BOOST_MEDIUM;
            } else {
                racer->boostType = BOOST_LARGE;
            }
        }
    }
    if (racer->boostTimer && !gRaceStartTimer && timer3 && racer->raceFinished == FALSE) {
        rumble_set(racer->playerIndex, RUMBLE_TYPE_6);
    }
    if (gRaceStartTimer < 80 && gCurrentButtonsPressed & A_BUTTON) {
        racer->startInput = 1;
    }
    if (!gRaceStartTimer) {
        if (racer->boost_sound & BOOST_RACE_START) {
            racer->boost_sound &= ~BOOST_RACE_START;
            play_random_character_voice(obj, SOUND_VOICE_CHARACTER_POSITIVE, 8, 130);
            racer_play_sound(obj, SOUND_NITRO_BOOST);
        }
    }

    if (racer->boost_sound & BOOST_SOUND_UNK2) {
        racer->boost_sound &= ~BOOST_SOUND_UNK2;
    }
    bananas = racer->bananas;
    // Cheats only apply to human players.
    if (racer->playerIndex == PLAYER_COMPUTER) {
        bananas = racer->unk124;
    } else {
        if (bananas > 10.0) {
            // Cap the banana speed boost to 10 if the unlimited bananas cheat is not enabled.
            if (!(get_filtered_cheats() & CHEAT_NO_LIMIT_TO_BANANAS)) {
                bananas = 10.0f;
            }
        }
        // Make the speed bonus negative if the speed reduction cheat is on.
        if (((get_filtered_cheats() & CHEAT_BANANAS_REDUCE_SPEED)) && (bananas > 0.0f)) {
            bananas = -bananas;
        }
    }
    // This also means the AI can have twice as many
    cap = 20.0f;
    if (bananas > cap) {
        bananas = cap;
    }
    if (bananas < -cap) {
        bananas = -cap;
    }
    speedMultiplier += (bananas * 0.025f);
    return speedMultiplier;
}

void func_800575EC(Object *obj, Object_Racer *racer) {
    MtxF mtxF;

    gCurrentRacerTransform.rotation.y_rotation = obj->segment.trans.rotation.y_rotation;
    gCurrentRacerTransform.rotation.x_rotation = obj->segment.trans.rotation.x_rotation;
    gCurrentRacerTransform.rotation.z_rotation = 0;
    gCurrentRacerTransform.x_position = 0.0f;
    gCurrentRacerTransform.y_position = 0.0f;
    gCurrentRacerTransform.z_position = 0.0f;
    gCurrentRacerTransform.scale = 1.0f;
    mtxf_from_transform(&mtxF, &gCurrentRacerTransform);
    mtxf_transform_point(&mtxF, 0.0f, 0.0f, 1.0f, &racer->ox1, &racer->oy1, &racer->oz1);
    mtxf_transform_point(&mtxF, 0.0f, 1.0f, 0.0f, &racer->ox2, &racer->oy2, &racer->oz2);
    mtxf_transform_point(&mtxF, 1.0f, 0.0f, 0.0f, &racer->ox3, &racer->oy3, &racer->oz3);
}

/**
 * Racers struck by most weapons will drop up to 2 bananas on the ground.
 * During challenge mode, no bananas are spawned, though the number still drops.
 */
void drop_bananas(Object *obj, Object_Racer *racer, s32 number) {
    LevelObjectEntryCommon newObject;
    Object_Banana *banana;
    s32 i;
    RPYAngles angle;
    Vec3s pos;
    Object *bananaObj;
    f32 variance;

    if (!(get_filtered_cheats() & CHEAT_START_WITH_10_BANANAS)) {
        racer->unk188 = 0;
        if (racer->bananas < number) {
            number = racer->bananas;
        }
        if (number > 0 && number < 3) {
            angle.z_rotation = racer->x_rotation_vel;
            angle.x_rotation = obj->segment.trans.rotation.x_rotation;
            angle.y_rotation = racer->steerVisualRotation;
            pos.x = 0;
            pos.y = 8;
            pos.z = 12;
            vec3s_rotate_rpy(&angle, &pos);
            newObject.x = pos.x + (s32) obj->segment.trans.x_position;
            newObject.y = pos.y + (s32) obj->segment.trans.y_position;
            newObject.z = pos.z + (s32) obj->segment.trans.z_position;
            newObject.size = sizeof(LevelObjectEntryCommon);
            newObject.objectID = ASSET_OBJECT_ID_COIN;
            i = number;
            do {
                if (get_current_level_race_type() != RACETYPE_CHALLENGE) {
                    bananaObj = spawn_object(&newObject, OBJECT_SPAWN_UNK01);
                    if (bananaObj != NULL) {
                        bananaObj->segment.level_entry = NULL;
                        banana = &bananaObj->unk64->banana;
                        banana->droppedVehicleID = racer->vehicleID;
                        bananaObj->segment.x_velocity = racer->ox1 * 2;
                        bananaObj->segment.y_velocity = (0.0f - racer->oy1) + 5.0;
                        bananaObj->segment.z_velocity = racer->oz1 * 2;
                        if (i == 2) {
                            variance = -0.5f;
                            if (number == 1) {
                                variance = 0.5f;
                            }
                            bananaObj->segment.x_velocity -= (racer->ox3 - racer->ox1) * variance;
                            bananaObj->segment.y_velocity -= racer->oy3 * variance;
                            bananaObj->segment.z_velocity -= (racer->oz3 - racer->oz1) * variance;
                        }
                        bananaObj->properties.banana.status = BANANA_DROPPED;
                    }
                }
                number--;
                racer->bananas--;
            } while (number > 0);
        }
    }
}

/**
 * Generate the steer velocity by taking the current steer velocity and getting the difference between the stick tilt.
 * Get the velocity from a fraction of the difference.
 */
void handle_base_steering(Object_Racer *racer, UNUSED s32 updateRate, f32 updateRateF) {
    s32 steering;
    s32 turnVel;

    steering = gCurrentStickX - racer->steerAngle;
    turnVel = (steering * updateRateF) * 0.125;

    if (steering != 0 && turnVel == 0) {
        if (steering > 0) {
            turnVel = 1;
        }
        if (steering < 0) {
            turnVel = -1;
        }
    }

    racer->steerAngle += turnVel;
}

/**
 * Primary function for updating the camera during player control.
 * Decides which behaviour to use, then branches off to that function.
 * Afterwards, writes position data to the current camera object.
 */
void update_player_camera(Object *obj, Object_Racer *racer, f32 updateRateF) {
    f32 dialogueAngle;
    s32 tempUpdateRateF;
    s32 angle;

    if (gCurrentButtonsPressed & U_CBUTTONS && race_starting()) {
        gCameraObject->zoom++;
        if (gCameraObject->zoom > ZOOM_VERY_CLOSE) {
            gCameraObject->zoom = ZOOM_MEDIUM;
        }
        if (racer->playerIndex != PLAYER_COMPUTER) {
            cam_set_zoom(racer->playerIndex, gCameraObject->zoom);
        }
        switch (gCameraObject->zoom) {
            case ZOOM_MEDIUM:
                sound_play(SOUND_MENU_BACK, NULL);
                break;
            case ZOOM_FAR:
                sound_play(SOUND_MENU_BACK2, NULL);
                break;
            default:
                sound_play(SOUND_UNK_6A, NULL);
                break;
        }
    }
    if (racer->raceFinished == TRUE && gCameraObject->mode != CAMERA_FINISH_CHALLENGE) {
        gCameraObject->mode = CAMERA_FINISH_RACE;
    }
    if (racer->exitObj) {
        gCameraObject->mode = CAMERA_FIXED;
    }
    // Set the camera behaviour based on current mode.
    switch (gCameraObject->mode) {
        default:
            break;
        case CAMERA_CAR:
            // Driving a car.
            update_camera_car(updateRateF, obj, racer);
            break;
        case CAMERA_PLANE:
            // Flying a plane.
            update_camera_plane(updateRateF, obj, racer);
            break;
        case CAMERA_FIXED:
            // Fixes the camera in place, continuing to look at the player. Used when entering doors.
            update_camera_fixed(updateRateF, obj, racer);
            break;
        case CAMERA_HOVERCRAFT:
            // Driving a hovercraft.
            update_camera_hovercraft(updateRateF, obj, racer);
            break;
        case CAMERA_FINISH_CHALLENGE:
            // When you finish a challenge, the camera will rotate around the player, or around a set path, if the
            // player's been KO'd.
            update_camera_finish_challenge(updateRateF, obj, racer);
            break;
        case CAMERA_LOOP:
            // Used for loop-the-loops. Follows the face direction of the player exactly, the standard camera modes do
            // not.
            update_camera_loop(updateRateF, obj, racer);
            break;
        case CAMERA_FINISH_RACE:
            // When you finish a race, the camera will go into a more cinematic mode, following the player.
            update_camera_finish_race(updateRateF, obj, racer);
            break;
    }

    dialogueAngle = gDialogueCameraAngle / 10240.0f; // Goes between 0-1
    gCameraObject->x_velocity = (((obj->segment.trans.x_position + (91.75 * racer->ox1) + (90.0 * racer->ox3)) -
                                  gCameraObject->trans.x_position) *
                                 dialogueAngle);
    gCameraObject->z_velocity = (((obj->segment.trans.z_position + (91.75 * racer->oz1) + (90.0 * racer->oz3)) -
                                  gCameraObject->trans.z_position) *
                                 dialogueAngle);
    gCameraObject->y_velocity = (((get_npc_pos_y() + 48.5) - gCameraObject->trans.y_position) * dialogueAngle);
    gCameraObject->pitch = -gCameraObject->trans.rotation.x_rotation * dialogueAngle;
    gCameraObject->trans.x_position += gCameraObject->x_velocity;
    gCameraObject->trans.y_position += gCameraObject->y_velocity + gCameraObject->shakeMagnitude;
    gCameraObject->trans.z_position += gCameraObject->z_velocity;
    if (gRaceStartTimer == 0 && gDialogueCameraAngle == 0) {
        gCameraObject->x_velocity *= 0.95;
        gCameraObject->y_velocity *= 0.95;
        gCameraObject->z_velocity *= 0.95;
    }

    angle = gDialogueCameraAngle;
    if (angle > 0x1400) {
        angle = 0x2800 - gDialogueCameraAngle;
    }
    if (angle > 0x600) {
        angle = 0x600;
    }
    angle = ((angle >> 4) + 4);
    tempUpdateRateF = updateRateF;
    if (gRacerDialogueCamera) {
        gDialogueCameraAngle += tempUpdateRateF * angle;
        if (gDialogueCameraAngle > 0x2800) {
            gDialogueCameraAngle = 0x2800;
        }
    } else {
        gDialogueCameraAngle -= tempUpdateRateF * angle;
        if (gDialogueCameraAngle < 0) {
            gDialogueCameraAngle = 0;
        }
    }
    gCameraObject->trans.rotation.y_rotation -= gDialogueCameraAngle;

    gCameraObject->shakeTimer -= tempUpdateRateF;
    while (gCameraObject->shakeTimer < 0) {
        gCameraObject->shakeTimer += 5;
        gCameraObject->shakeMagnitude = -gCameraObject->shakeMagnitude * 0.75;
    }
}

/**
 * After the racer logic is all done, update the camera once more.
 * This time it will create the smooth following effect when turning.
 */
void second_racer_camera_update(Object *obj, Object_Racer *racer, s32 mode, f32 updateRateF) {
    f32 xPos, yPos, zPos;
    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->raceFinished != TRUE) {
        if (mode != gCameraObject->mode) {
            update_player_camera(obj, racer, updateRateF);
            xPos = gCameraObject->trans.x_position;
            yPos = gCameraObject->trans.y_position;
            zPos = gCameraObject->trans.z_position;
            gCameraObject->mode = mode;
            update_player_camera(obj, racer, updateRateF);
            if (gRaceStartTimer == 0 && gTajInteractStatus == TAJ_WANDER) {
                gCameraObject->x_velocity = xPos - gCameraObject->trans.x_position;
                gCameraObject->y_velocity = yPos - (gCameraObject->trans.y_position + gCameraObject->shakeMagnitude);
                gCameraObject->z_velocity = zPos - gCameraObject->trans.z_position;
            }
        }
    }
}

void update_camera_car(f32 updateRate, Object *obj, Object_Racer *racer) {
    UNUSED s64 pad_sp60;
    s32 segmentIndex;
    UNUSED f32 pad_sp58;
    f32 baseDistance = 120.0f;
    f32 yVel = 50.0f;
    s32 angle;
    f32 sineOffset;
    f32 cosOffset;
    f32 tempVel;
    f32 baseSpeed;
    f32 sp38;
    s32 angleVel;
    f32 xOffset;
    f32 yOffset;
    f32 zOffset;
    f32 brakeVar;
    f32 lateralOffset;
    s32 baseAngle = 0x400;
    s32 newAngle;
    s32 numViewports;
    s32 tempAngle;
    s32 delta = (s32) updateRate;

    numViewports = cam_get_viewport_layout();
    if (numViewports == 1) {
        baseDistance = 192.0f;
        baseAngle = 0x200;
    } else if (numViewports > 2) {
        baseDistance = 100.0f;
        yVel = 40.0f;
    }
    numViewports = func_80023568();
    if (numViewports == 1 || numViewports == 4) {
        baseDistance = 144.0f;
        yVel = 110.0f;
        if (gCameraObject->zoom == ZOOM_VERY_CLOSE) {
            baseDistance += 30.0f;
        }
        baseAngle = 0xD00;
    }
    racer->cameraYaw = (-racer->steerVisualRotation - racer->unk19E) + 0x8000;
    angle = racer->unk19E >> 3;
    if (angle > 0x400) {
        angle = 0x400;
    }
    if (angle < -0x400) {
        angle = -0x400;
    }
    angle *= delta;
    if (angle > 0 && angle < racer->unk19E) {
        racer->unk19E -= angle;
    }
    if (angle < 0) {
        if (racer->unk19E < angle) {
            racer->unk19E -= angle;
        }
    }
    brakeVar = racer->brake;
    lateralOffset = racer->forwardVel;
    switch (gCameraObject->zoom) {
        case 1:
            baseDistance += 35.0f;
            break;
        case 2:
            baseDistance -= 35.0f;
            yVel -= 10.0f;
            break;
        case 3:
            baseDistance -= 53.0f;
            yVel -= 5.0f;
            brakeVar = 0.0f;
            lateralOffset *= 0.25;
            break;
    }
    if (racer->groundedWheels > 2 || racer->waterTimer != 0) {
        angleVel = (obj->segment.trans.rotation.x_rotation);
        if (angleVel > 0) {
            angleVel -= 0x71C;
            if (angleVel < 0) {
                angleVel = 0;
            }
            angleVel >>= 1;
        } else {
            angleVel += 0x71C;
            if (angleVel > 0) {
                angleVel = 0;
            }
        }
        angleVel = baseAngle - angleVel;
        angle = angleVel - (u16) gCameraObject->trans.rotation.x_rotation;
        if (angle > 0x8000) {
            angle -= 0xFFFF;
        }
        if (angle < -0x8000) {
            angle += 0xFFFF;
        }
        gCameraObject->trans.rotation.x_rotation += (angle * delta) >> 4;
    }
    if (racer->velocity < 0.0) {
        tempVel = 6.0f;
        if (racer->drift_direction) {
            tempVel = 3.0f;
        }
        tempVel = -(racer->velocity * brakeVar) * tempVel;
        if (65.0 < tempVel) {
            tempVel = 65.0f;
        }
        baseDistance -= tempVel;
    }
    if (!racer->drift_direction) {
        baseDistance += lateralOffset * 60.0f;
    } else {
        baseDistance += lateralOffset * 30.0f;
    }
    if (gRaceStartTimer == 0) {
        if (normalise_time(36) < racer->boostTimer) {
            baseDistance = -30.0f;
        } else if (racer->boostTimer > 0) {
            baseDistance = 180.0f;
        }
    }
    if (gRaceStartTimer > 80) {
        gCameraObject->boomLength = baseDistance;
        gCameraObject->cam_unk_20 = yVel;
    }
    gCameraObject->boomLength += (baseDistance - gCameraObject->boomLength) * 0.125;
    brakeVar = gCameraObject->cam_unk_20;
    gCameraObject->cam_unk_20 += (yVel - brakeVar) * 0.125;
    sp38 = sins_f(gCameraObject->trans.rotation.x_rotation - baseAngle);
    sineOffset = coss_f(gCameraObject->trans.rotation.x_rotation - baseAngle);
    tempVel = (gCameraObject->boomLength * sineOffset) - (gCameraObject->cam_unk_20 * sp38);
    yVel = (gCameraObject->boomLength * sp38) + (gCameraObject->cam_unk_20 * sineOffset);
    sineOffset = sins_f(-racer->cameraYaw + 0x8000) * tempVel;
    cosOffset = coss_f(-racer->cameraYaw + 0x8000) * tempVel;
    lateralOffset = 0.0f;
    if (gCurrentRacerInput & A_BUTTON) {
        lateralOffset = racer->lateral_velocity * 1.3;
        if (lateralOffset > 0.0f) {
            lateralOffset -= 1.5;
            if (lateralOffset < 0.0f) {
                lateralOffset = 0.0f;
            }
        } else {
            lateralOffset += 1.5;
            if (lateralOffset > 0.0f) {
                lateralOffset = 0.0f;
            }
        }
    }
    if (racer->drift_direction) {
        lateralOffset = -(f32) racer->drift_direction * 12.0f;
    }
    racer->unkC8 += (lateralOffset - racer->unkC8) * 0.125;
    if (racer->spinout_timer) {
        racer->camera_zoom -= racer->camera_zoom * 0.25;
    } else {
        racer->camera_zoom += (10.0 - racer->camera_zoom) * 0.25;
    }
    xOffset = obj->segment.trans.x_position - (racer->ox1 * racer->camera_zoom);
    yOffset = obj->segment.trans.y_position - (racer->oy1 * racer->camera_zoom);
    zOffset = obj->segment.trans.z_position - (racer->oz1 * racer->camera_zoom);
    tempVel = sins_f(racer->cameraYaw + 0x4000) * racer->unkC8;
    gCameraObject->trans.x_position = xOffset + sineOffset + tempVel;
    lateralOffset = yOffset + yVel;
    sp38 = (gCameraObject->trans.y_position - lateralOffset) * 0.25;
    if (sp38 < -2.0) {
        gCameraObject->trans.y_position -= sp38 + 2.0;
    }
    gCameraObject->trans.y_position -= sp38 * 0.25;
    if (sp38 > 0.0f || gRaceStartTimer) {
        gCameraObject->trans.y_position = lateralOffset;
    }
    tempVel = (-coss_f(racer->cameraYaw + 0x4000) * racer->unkC8);
    gCameraObject->trans.z_position = tempVel + (zOffset + cosOffset);
    gCameraObject->trans.rotation.y_rotation = racer->cameraYaw;
    newAngle = obj->segment.trans.rotation.z_rotation;
    if ((racer->drift_direction && racer->brake > 0.0) || gDialogueCameraAngle) {
        newAngle = 0;
    }
    angle = gCameraObject->trans.rotation.z_rotation;
    gCameraObject->trans.rotation.z_rotation -= (angle + newAngle) >> 4;
    if (gCameraObject->trans.rotation.z_rotation > 0x2000) {
        gCameraObject->trans.rotation.z_rotation = 0x2000;
    }
    if (gCameraObject->trans.rotation.z_rotation < -0x2000) {
        gCameraObject->trans.rotation.z_rotation = -0x2000;
    }
    gCameraObject->trans.y_position -= racer->unkC8 * sins_f(gCameraObject->trans.rotation.z_rotation);
    segmentIndex = get_level_segment_index_from_position(
        gCameraObject->trans.x_position, gCameraObject->trans.y_position, gCameraObject->trans.z_position);
    if (segmentIndex != -1) {
        gCameraObject->cameraSegmentID = segmentIndex;
    }
    racer->cameraYaw = gCameraObject->trans.rotation.y_rotation;
}

/**
 * Handles the camera movement when the player has finished a challenge.
 * If the player still exists, it will follow and rotate around the player.
 * Otherwise, it will follow a set path while rotating.
 */
void update_camera_finish_challenge(UNUSED f32 updateRate, Object *obj, Object_Racer *racer) {
    s32 segmentIndex;
    f32 temp_f12;
    f32 zOffset;
    f32 xOffset;

    gCameraObject->trans.rotation.y_rotation += 0x200;
    if (1) {} // Fakematch
    gCameraObject->trans.rotation.x_rotation = 0x400;
    gCameraObject->trans.rotation.z_rotation = 0;
    gCameraObject->boomLength = 150.0f;
    xOffset = sins_f(0x8000 - gCameraObject->trans.rotation.y_rotation) * gCameraObject->boomLength;
    zOffset = coss_f(0x8000 - gCameraObject->trans.rotation.y_rotation) * gCameraObject->boomLength;
    gCameraObject->trans.x_position = obj->segment.trans.x_position + xOffset;
    temp_f12 = (gCameraObject->trans.y_position - (obj->segment.trans.y_position + 45.0f)) * 0.25;
    if (temp_f12 < -2.0) {
        gCameraObject->trans.y_position = (gCameraObject->trans.y_position - (temp_f12 + 2.0));
    }
    if (temp_f12 > 0.0f) {
        gCameraObject->trans.y_position = obj->segment.trans.y_position + 45.0f;
    }
    gCameraObject->trans.z_position = obj->segment.trans.z_position + zOffset;
    segmentIndex = get_level_segment_index_from_position(
        gCameraObject->trans.x_position, gCameraObject->trans.y_position, gCameraObject->trans.z_position);
    if (segmentIndex != SEGMENT_NONE) {
        gCameraObject->cameraSegmentID = segmentIndex;
    }
    racer->cameraYaw = gCameraObject->trans.rotation.y_rotation;
}

/**
 * Handles the camera movement when the player has finished the race.
 * Uses a more cinematic approach to following the player, using pre-existing points in the track to look from.
 */
void update_camera_finish_race(UNUSED f32 updateRate, Object *obj, Object_Racer *racer) {
    s32 cameraID;
    Object *cam;
    f32 diffX;
    f32 diffY;
    f32 diffZ;
    f32 distance;

    cameraID = racer->spectateCamID;
    cam = spectate_nearest(obj, &cameraID);
    if (cam == NULL) {
        gCameraObject->mode = CAMERA_FINISH_CHALLENGE;
        return;
    }
    racer->spectateCamID = cameraID;
    gCameraObject->trans.x_position = cam->segment.trans.x_position;
    gCameraObject->trans.y_position = cam->segment.trans.y_position;
    gCameraObject->trans.z_position = cam->segment.trans.z_position;
    diffX = gCameraObject->trans.x_position - obj->segment.trans.x_position;
    diffY = gCameraObject->trans.y_position - obj->segment.trans.y_position;
    diffZ = gCameraObject->trans.z_position - obj->segment.trans.z_position;
    distance = sqrtf((diffX * diffX) + (diffZ * diffZ));
    gCameraObject->trans.rotation.y_rotation = 0x8000 - atan2s(diffX, diffZ);
    gCameraObject->trans.rotation.x_rotation = atan2s((s32) diffY, (s32) distance);
    gCameraObject->trans.rotation.z_rotation = 0;
    gCameraObject->cameraSegmentID = get_level_segment_index_from_position(gCameraObject->trans.x_position, racer->oy1,
                                                                           gCameraObject->trans.z_position);
}

/**
 * Stops the camera in place when set, while still pointing in the direction of the player.
 * Used when entering doors.
 */
void update_camera_fixed(f32 updateRate, Object *obj, Object_Racer *racer) {
    s32 updateRateF;
    f32 diffX;
    f32 diffZ;
    updateRateF = (s32) updateRate;
    diffX = gCameraObject->trans.x_position - obj->segment.trans.x_position;
    diffZ = gCameraObject->trans.z_position - obj->segment.trans.z_position;
    gCameraObject->trans.rotation.y_rotation +=
        ((((-atan2s(diffX, diffZ)) - gCameraObject->trans.rotation.y_rotation) + 0x8000) * updateRateF) >> 4;
    gCameraObject->trans.rotation.z_rotation -= ((s32) (gCameraObject->trans.rotation.z_rotation * updateRateF)) >> 4;
    gCameraObject->cameraSegmentID = get_level_segment_index_from_position(gCameraObject->trans.x_position, racer->oy1,
                                                                           gCameraObject->trans.z_position);
}

/**
 * Iterate through every checkpoint and find the current location of the racer.
 * Sets the position arguments based on the intended location the spline functions return.
 * These coordinates are then used to generate a velocity.
 */
void set_position_goal_from_path(UNUSED Object *obj, Object_Racer *racer, f32 *x, f32 *y, f32 *z) {
    CheckpointNode *checkpoint;
    s32 splinePos;
    s32 destReached;
    s32 splineEnd;
    f32 splineX[5];
    f32 splineY[5];
    f32 splineZ[5];
    f32 magnitude;
    s32 i;

    splineEnd = get_checkpoint_count();

    if (splineEnd == 0) {
        return;
    }

    magnitude = 1.0 - racer->checkpoint_distance;
    if (magnitude < 0.0f) {
        magnitude = 0.0f;
    }
    if (racer->checkpoint) {} // Fakematch
    splinePos = racer->checkpoint - 2;
    if (splinePos < 0) {
        splinePos += splineEnd;
    }
    for (i = 0; i < 5; i++) {
        checkpoint = find_next_checkpoint_node(splinePos, racer->unk1C8);
        splineX[i] = checkpoint->x;
        splineY[i] = checkpoint->y;
        splineZ[i] = checkpoint->z;
        splinePos++;
        if (splinePos == splineEnd) {
            splinePos = 0;
        }
    }
    destReached = FALSE;
    if (magnitude >= 1.0) {
        destReached = TRUE;
        magnitude -= 1.0;
    }
    *x = catmull_rom_interpolation(splineX, destReached, magnitude);
    *y = catmull_rom_interpolation(splineY, destReached, magnitude);
    *z = catmull_rom_interpolation(splineZ, destReached, magnitude);
}

// https://decomp.me/scratch/6WBdX
#ifdef NON_MATCHING
void func_80059208(Object *obj, Object_Racer *racer, s32 updateRate) {
    UNUSED s32 pad[2];
    s32 temp_v0;
    CheckpointNode *temp_v0_4;
    f32 posX[5];
    f32 posY[5];
    f32 posZ[5];
    UNUSED s32 pad2;
    f32 tempX;
    s32 counter;
    f32 tempY;
    s32 angle;
    f32 tempZ;
    f32 splinePos;
    f32 diffX;
    f32 diffY;
    f32 diffZ;
    f32 distance;
    f32 divisor;
    f32 scale;
    s32 splineIndex;
    s32 i;

    temp_v0 = get_checkpoint_count();
    if (temp_v0 == 0) {
        return;
    }
    if ((get_current_map_id() == 0) && (racer->checkpoint >= temp_v0)) {
        racer->lap = 0;
        racer->checkpoint = 0;
        racer->courseCheckpoint = 0;
    }
    splinePos = 1.0 - racer->checkpoint_distance;
    if (splinePos < -0.2) {
        racer->checkpoint--;
        if (racer->checkpoint < 0) {
            racer->checkpoint += temp_v0;
            if (racer->lap > 0) {
                racer->lap--;
            }
        }
        if (racer->courseCheckpoint > -0x7D00) {
            racer->courseCheckpoint--;
        }
        if (racer->unk1C8) {
            temp_v0_4 = get_checkpoint_node(racer->checkpoint);
            if (temp_v0_4->altRouteID == -1) {
                racer->unk1C8 = 0;
            }
            angle = racer->checkpoint - 1;
            if (angle < 0) {
                angle += temp_v0;
            }
            temp_v0_4 = get_checkpoint_node(angle);
            if (temp_v0_4->altRouteID == -1) {
                racer->unk1C8 = 0;
            }
        }
    } else {
        if (splinePos < 0.0f) {
            splinePos = 0.0f;
        }
        temp_v0_4 = find_next_checkpoint_node(racer->checkpoint, racer->unk1C8);
        scale = temp_v0_4->scale;
        counter = racer->checkpoint - 1;
        if (counter < 0) {
            counter = temp_v0 - 1;
        }
        temp_v0_4 = get_checkpoint_node(counter);
        distance = temp_v0_4->scale;
        divisor = ((scale - temp_v0_4->scale) * splinePos) + distance;
        counter = racer->checkpoint - 2;
        if (counter < 0) {
            counter += temp_v0;
        }
        for (i = 0; (i < 5) ^ 0; i++) {
            temp_v0_4 = find_next_checkpoint_node(counter, racer->unk1C8);
            posX[i] = temp_v0_4->x + ((temp_v0_4->scale * temp_v0_4->rotationZFrac) * racer->unk1BA);
            posY[i] = temp_v0_4->y + (temp_v0_4->scale * racer->unk1BC);
            posZ[i] = temp_v0_4->z + ((temp_v0_4->scale * (-temp_v0_4->rotationXFrac)) * racer->unk1BA);
            counter++;
            if (counter == temp_v0) {
                counter = 0;
            }
        }
        splineIndex = FALSE;
        if (splinePos >= 1.0) {
            splinePos -= 1.0;
            splineIndex = TRUE;
        }
        tempX = cubic_spline_interpolation(posX, splineIndex, splinePos, &diffX);
        tempY = cubic_spline_interpolation(posY, splineIndex, splinePos, &diffY);
        tempZ = cubic_spline_interpolation(posZ, splineIndex, splinePos, &diffZ);
        distance = sqrtf((diffX * diffX) + (diffZ * diffZ));
        if (distance != 0.0f) {
            scale = 1.0f / distance;
            diffX *= scale;
            diffZ *= scale;
        }
        angle = arctan2_f(diffX, diffZ) - (racer->steerVisualRotation & 0xFFFF) - 0x8000;
        WRAP(angle, -0x8000, 0x8000);
        if (angle > 0x4000 || angle < -0x4000) {
            if (racer->wrongWayCounter < 200 && racer->velocity <= -1.0) {
                racer->wrongWayCounter += updateRate;
            }
        } else {
            racer->wrongWayCounter = 0;
        }
        diffY = diffX;
        diffX = diffZ;
        diffZ = -diffY;
        splinePos = obj->segment.trans.x_position;
        distance = obj->segment.trans.z_position;
        diffX = -(((splinePos * diffX) + (diffZ * distance) - ((tempZ * diffZ) + (diffX * tempX))) / divisor);
        if (diffX > 5.0f) {
            diffX = 5.0f;
        }
        if (diffX < -5.0f) {
            diffX = -5.0f;
        }
        racer->unk1BA += (s32) diffX;
        diffY = (obj->segment.trans.y_position - tempY) / divisor;
        if (diffY > 100.0f) {
            diffY = 100.0f;
        }
        if (diffY < -100.0f) {
            diffY = -100.0f;
        }
        racer->unk1BC += (s32) diffY;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/racer/func_80059208.s")
#endif

/**
 * Writes a human readable time to the passed arguments.
 * Used to visualise a standard time to the player for a stopwatch, or a record.
 */
void get_timestamp_from_frames(s32 frameCount, s32 *minutes, s32 *seconds, s32 *hundredths) {
    if (gVideoRefreshRate == REFRESH_50HZ) {
        frameCount = (f32) frameCount * 1.2;
    }
    // (REFRESH_60HZ * 60) is just frames per minute basically
    *minutes = frameCount / (REFRESH_60HZ * 60);
    *seconds = (frameCount - (*minutes * (REFRESH_60HZ * 60))) / REFRESH_60HZ;
    *hundredths = (((frameCount - (*minutes * (REFRESH_60HZ * 60))) - (*seconds * REFRESH_60HZ)) * 100) / REFRESH_60HZ;
}

/**
 * Allocate the ghost data heap into memory.
 * The path node pool is globally loaded, despite only being used in time trial.
 */
void allocate_ghost_data(void) {
    // Allocate two sets of ghost data. One for the current playing ghost, and one for the new ghost being written.
    gGhostData[0] = mempool_alloc_safe((sizeof(GhostNode) * 2) * MAX_NUMBER_OF_GHOST_NODES, COLOUR_TAG_RED);
    gGhostData[1] = ((GhostNode *) gGhostData[0] + MAX_NUMBER_OF_GHOST_NODES);
    gGhostData[GHOST_STAFF] = NULL; // T.T. Ghost
    gGhostNodeCount[0] = 0;
    gGhostNodeCount[1] = 0;
    gGhostNodeCount[GHOST_STAFF] = 0;
    gGhostNodeFull[0] = FALSE;
    gGhostNodeFull[1] = FALSE;
    gPrevGhostNodeIndex = 0;
    gGhostMapID = -1;
}

/**
 * Reset all the player ghost playback variables to default.
 * Also set the ghost index.
 */
void timetrial_reset_player_ghost(void) {
    gCurrentGhostIndex = gPrevGhostNodeIndex;
    gGhostNodeCount[gCurrentGhostIndex] = 0;
    gGhostNodeFull[gCurrentGhostIndex] = FALSE;
    gGhostNodeDelay = 0;
}

/**
 * Swap player ghost index and set the new saved map ID.
 */
void timetrial_swap_player_ghost(s32 mapID) {
    gPrevGhostNodeIndex = (gCurrentGhostIndex + 1) & 1;
    gGhostMapID = mapID;
}

/**
 * Return the current map ID associated with the time trial ghost.
 */
s32 timetrial_map_id(void) {
    return gGhostMapID;
}

/**
 * Attempt to load the player ghost data from the controller pak.
 * Returns the controller pak status when done.
 */
s32 timetrial_load_player_ghost(s32 controllerID, s32 mapId, s16 arg2, s16 *characterID, s16 *time) {
    s32 cpakStatus;
    s32 nodeID;
    s16 nodeCount;

    nodeID = (gCurrentGhostIndex + 1) & 1;
    cpakStatus = func_80074B34(controllerID, mapId, arg2, (u16 *) characterID, time, &nodeCount,
                               (unk80075000 *) gGhostData[nodeID]);
    if (characterID) {
        if (cpakStatus == CONTROLLER_PAK_GOOD) {
            gGhostNodeCount[nodeID] = nodeCount;
            gGhostMapID = mapId;
        } else {
            gGhostMapID = -1;
        }
    }

    return cpakStatus;
}

/**
 * Loads T.T. ghost node data into gGhostData[GHOST_STAFF].
 * Returns 0 if successful, or 1 if an error occured.
 */
s32 load_tt_ghost(s32 ghostOffset, s32 size, s16 *outTime) {
    GhostHeader *ghost = mempool_alloc_safe(size, COLOUR_TAG_RED);
    if (ghost != NULL) {
        load_asset_to_address(ASSET_TTGHOSTS, (u32) ghost, ghostOffset, size);
        if (gGhostData[GHOST_STAFF] != NULL) {
            mempool_free(gGhostData[GHOST_STAFF]);
        }
        gGhostData[GHOST_STAFF] = mempool_alloc_safe(size - sizeof(GhostHeader), COLOUR_TAG_WHITE);
        if (gGhostData[GHOST_STAFF] != NULL) {
            *outTime = ghost->time;
            gGhostNodeCount[GHOST_STAFF] = ghost->nodeCount;
            bcopy((u8 *) ghost + 8, gGhostData[GHOST_STAFF], size - sizeof(GhostHeader));
            mempool_free(ghost);
            return 0;
        }
        mempool_free(ghost);
    }
    return 1;
}

/**
 * Free the staff ghost from memory if it exists.
 */
void timetrial_free_staff_ghost(void) {
    if (gGhostData[GHOST_STAFF] != NULL) {
        mempool_free(gGhostData[GHOST_STAFF]);
    }
    gGhostData[GHOST_STAFF] = NULL;
}

/**
 * Calls a function that attempts to write the player ghost data to the controller pak.
 * Returns the controller pak status when finished.
 */
SIDeviceStatus timetrial_write_player_ghost(s32 controllerIndex, s32 mapId, s16 arg2, s16 arg3, s16 arg4) {
    return func_80075000(controllerIndex, (s16) mapId, arg2, arg3, arg4, gGhostNodeCount[gCurrentGhostIndex],
                         (unk80075000_body *) gGhostData[gCurrentGhostIndex]);
}

/**
 * Write down the current position and rotation every half second to the ghost node data.
 * Returns early if the ghost node data is full.
 */
void timetrial_ghost_write(Object *obj, s32 updateRate) {
    f32 yOffset;
    Object_Racer *racer;
    GhostNode *ghostNode;

    racer = &obj->unk64->racer;
    yOffset = coss_f(racer->z_rotation_offset) * coss_f(racer->x_rotation_offset - racer->unk166);
    if (yOffset < 0) {
        yOffset *= 0.5;
    }
    yOffset = 17.0f - (yOffset * 17.0f);
    gGhostNodeDelay -= updateRate;
    if (gGhostNodeDelay > 0) {
        return;
    }
    while (gGhostNodeDelay <= 0) {
        gGhostNodeDelay += 30;
        if (gGhostNodeCount[gCurrentGhostIndex] >= 360) {
            if (!is_postrace_viewport_active()) {
                gGhostNodeFull[gCurrentGhostIndex] = TRUE;
            }
            return;
        }
        ghostNode = gGhostData[gCurrentGhostIndex] + gGhostNodeCount[gCurrentGhostIndex];
        ghostNode->x = obj->segment.trans.x_position;
        ghostNode->y = obj->segment.trans.y_position + yOffset;
        ghostNode->z = obj->segment.trans.z_position;
        ghostNode->yRotation = obj->segment.trans.rotation.y_rotation + racer->y_rotation_offset;
        ghostNode->xRotation = obj->segment.trans.rotation.x_rotation + racer->x_rotation_offset;
        ghostNode->zRotation = obj->segment.trans.rotation.z_rotation + racer->z_rotation_offset;
        gGhostNodeCount[gCurrentGhostIndex]++;
    }
}

/**
 * Returns true if the time trial ghost has reached its size limit.
 */
s16 timetrial_ghost_full(void) {
    return gGhostNodeFull[gCurrentGhostIndex];
}

// https://decomp.me/scratch/yMObT
#ifdef NON_EQUIVALENT
// timetrial_ghost_read
s32 set_ghost_position_and_rotation(Object *obj) {
    f32 vectorX[4];
    f32 vectorY[4];
    f32 vectorZ[4];
    GhostNode *nextGhostNode;
    GhostNode *ghostData;
    GhostNode *curGhostNode;
    Object_Racer *racer;
    f32 catmullX;
    f32 commonUnk0f32;
    s32 commonUnk0s32;
    s32 ghostNodeCount;
    s32 ghostDataIndex;
    s32 nodeIndex;
    s32 rotDiff;
    s16 rot;
    s32 i;

    ghostDataIndex = (gCurrentGhostIndex + 1) & 1;
    if (timetrial_staff_ghost_check(obj)) {
        ghostDataIndex = 2;
    }

    commonUnk0f32 = (f32) obj->properties.common.unk0 / 30.0f;
    if (osTvType == OS_TV_TYPE_PAL && ghostDataIndex == 2) {
        commonUnk0f32 = ((f32) obj->properties.common.unk0 * 1.2) / 30.0f;
    }
    commonUnk0s32 = commonUnk0f32; // Truncate the float to an integer?

    ghostNodeCount = gGhostNodeCount[ghostDataIndex];
    if (commonUnk0s32 >= (ghostNodeCount - 2)) {
        return FALSE;
    }
    if (ghostDataIndex != 2 && get_current_map_id() != gGhostMapID) {
        return FALSE;
    }
    ghostData = gGhostData[ghostDataIndex];
    nodeIndex = commonUnk0s32 - 1;
    curGhostNode = &ghostData[nodeIndex];

#define DOUBLE(x) ((x) + (x))
    // This whole loop is a bit of a mystery still... The i < 4 is a complete guess...
    for (i = 0; i < 4; i++) {
        if (nodeIndex == -1) {
            vectorX[i] = DOUBLE(ghostData[nodeIndex + 1].x) - ghostData[nodeIndex + 2].x;
            vectorY[i] = DOUBLE(ghostData[nodeIndex + 1].y) - ghostData[nodeIndex + 2].y;
            vectorZ[i] = DOUBLE(ghostData[nodeIndex + 1].z) - ghostData[nodeIndex + 2].z;
        } else if (nodeIndex >= ghostNodeCount) {
            vectorX[i] = DOUBLE(ghostData[nodeIndex].x) - ghostData[nodeIndex - 1].x;
            vectorY[i] = DOUBLE(ghostData[nodeIndex].y) - ghostData[nodeIndex - 1].y;
            vectorZ[i] = DOUBLE(ghostData[nodeIndex].z) - ghostData[nodeIndex - 1].z;
        } else {
            vectorX[i] = ghostData[nodeIndex].x;
            vectorY[i] = ghostData[nodeIndex].y;
            vectorZ[i] = ghostData[nodeIndex].z;
        }
        nodeIndex++;
        curGhostNode++;
    }
#undef DOUBLE

    catmullX = commonUnk0f32 - commonUnk0s32;
    obj->segment.trans.x_position = catmull_rom_interpolation(vectorX, 0, catmullX);
    obj->segment.trans.y_position = catmull_rom_interpolation(vectorY, 0, catmullX);
    obj->segment.trans.z_position = catmull_rom_interpolation(vectorZ, 0, catmullX);

    curGhostNode = &ghostData[commonUnk0s32];
    nextGhostNode = &ghostData[commonUnk0s32 + 1];

    // It seems important to have a reference to the next ghost node before the first usage of the current one.
    if (nextGhostNode) {}

    // Y Rotation
    rot = curGhostNode->yRotation;
    rotDiff = nextGhostNode->yRotation - (rot & 0xFFFF);
    if (rotDiff > 0x8000) {
        rotDiff -= 0xFFFF;
    }
    if (rotDiff < -0x8000) {
        rotDiff += 0xFFFF;
    }
    obj->segment.trans.rotation.y_rotation = rot + (s32) (rotDiff * (commonUnk0f32 - commonUnk0s32));

    // X Rotation
    rot = curGhostNode->xRotation;
    rotDiff = nextGhostNode->xRotation - (rot & 0xFFFF);
    if (rotDiff > 0x8000) {
        rotDiff -= 0xFFFF;
    }
    if (rotDiff < -0x8000) {
        rotDiff += 0xFFFF;
    }
    obj->segment.trans.rotation.x_rotation = rot + (s32) (rotDiff * (commonUnk0f32 - commonUnk0s32));

    // Z Rotation
    rot = curGhostNode->zRotation;
    rotDiff = nextGhostNode->zRotation - (rot & 0xFFFF);
    if (rotDiff > 0x8000) {
        rotDiff -= 0xFFFF;
    }
    if (rotDiff < -0x8000) {
        rotDiff += 0xFFFF;
    }
    obj->segment.trans.rotation.z_rotation = rot + (s32) (rotDiff * (commonUnk0f32 - commonUnk0s32));

    if ((catmullX)) {}

    obj->particleEmittersEnabled = OBJ_EMIT_NONE;
    obj->segment.object.segmentID = get_level_segment_index_from_position(
        obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
    if (ghostNodeCount == (commonUnk0s32 + 3)) {
        racer = &obj->unk64->racer;
        if (catmullX >= 0.8) {
            racer->transparency = 0;
        } else {
            racer->transparency = (0.8 - catmullX) * 96.0;
        }
    }
    return TRUE;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/racer/set_ghost_position_and_rotation.s")
#endif

/**
 * Blocks the player's movement until the end of their update cycle.
 * Called for every frame the player shouldn't be able to drive.
 */
void disable_racer_input(void) {
    gRacerInputBlocked = TRUE;
}

/**
 * Tells the camera to start rotating to the side for the dialogue camera.
 * Called for every frame the player should experience subtle cinematography.
 */
void racer_set_dialogue_camera(void) {
    gRacerDialogueCamera = TRUE;
}

#ifdef ANTI_TAMPER
/**
 * Antipiracy function that loops over an address of a function a number of times.
 * It compares the number it gets to a generated checksum to determine if the game has been tampered with at all.
 */
void drm_checksum_balloon(void) {
    s32 i;
    s32 count = 0;
    u8 *temp = (u8 *) &obj_loop_goldenballoon;

    for (i = 0; i < gObjLoopGoldenBalloonLength; i++) {
        count += temp[i];
    }
    // Antipiracy measure that makes every racer's head spin.
    if (count != gObjLoopGoldenBalloonChecksum) {
        gAntiPiracyHeadroll = 0x800;
    }
}
#endif

/**
 * When you enter a door, take control away from the player.
 * Get the angle to the door object, and drive towards it.
 * After a timer hits 0, execute the transition.
 */
void racer_enter_door(Object_Racer *racer, s32 updateRate) {
    Object_Exit *exit;
    f32 updateRateF;
    s32 angle;

    exit = &racer->exitObj->unk64->exit;
    racer->playerIndex = PLAYER_COMPUTER;
    angle = (u16) arctan2_f(exit->directionX, exit->directionZ) - (racer->steerVisualRotation & 0xFFFF);
    WRAP(angle, -0x8000, 0x8000);
    angle = -angle >> 5;
    gCurrentStickX = angle;
    gCurrentButtonsPressed = 0;
    gCurrentButtonsReleased = 0;
    gCurrentRacerInput = 0;
    gCurrentStickY = 0;
    if (racer->velocity > -4.0) {
        gCurrentRacerInput |= A_BUTTON;
    } else if (racer->velocity < -5.0) {
        gCurrentRacerInput |= B_BUTTON;
    }
    updateRateF = (f32) updateRate;
    gCameraObject->trans.x_position += (exit->directionX * updateRateF) * 1.5;
    gCameraObject->trans.z_position += (exit->directionZ * updateRateF) * 1.5;
    // clang-format off
    // Only matches if it's on the same line
    if (gCurrentStickX > 75) { \
        gCurrentStickX = 75; \
        gCurrentRacerInput |= A_BUTTON | B_BUTTON; \
    }
    // clang-format on
    if (gCurrentStickX < -75) {
        gCurrentStickX = -75;
        gCurrentRacerInput |= A_BUTTON | B_BUTTON;
    }
    if (racer->transitionTimer < -1) {
        racer->transitionTimer += updateRate;
        if (racer->transitionTimer >= 0) {
            racer->transitionTimer = -1;
        }
    }
    if ((racer->transitionTimer < -1 && gCurrentStickX < 10 && gCurrentStickX > -10) || racer->transitionTimer == -1) {
        if (check_if_showing_cutscene_camera() == 0) {
            transition_begin(&gDoorFadeTransition);
        }
        racer->transitionTimer = 60 - updateRate;
    }
    set_pause_lockout_timer(1);
    if (racer->transitionTimer > 0) {
        racer->transitionTimer -= updateRate;
        if (racer->transitionTimer <= 0) {
            func_8006D968((s8 *) racer->exitObj->segment.level_entry);
            racer->transitionTimer = 0;
        }
    }
}

/**
 * The top level function for handling the actions of a computer controlled racer.
 * Mostly the same as how the player controlled one works, minus controller input and includes some decision making
 * logic.
 */
void update_AI_racer(Object *obj, Object_Racer *racer, s32 updateRate, f32 updateRateF) {
    s32 var_t2;
    Object **objects;
    s32 gameMode;
    s32 countOfObjects;
    f32 xPos;
    f32 yPos;
    f32 zPos;
    f32 lastCheckpointDist;
    Object *playerOneObj;
    f32 var_fv1;
    Object *playerTwoObj;
    LevelHeader *levelHeader;
    s32 temp_v0_10;
    f32 temp_f0;
    CheckpointNode *checkpoint;
    Object_Racer *tempRacer;
    f32 temp_fv1_2;

    gCurrentPlayerIndex = -1;
    gameMode = get_game_mode();
    levelHeader = get_current_level_header();
    if (racer->unk1F6 > 0) {
        racer->unk1F6 -= updateRate;
    } else {
        racer->unk1F6 = 0;
    }
    if (gRaceStartTimer != 0) {
        racer->unk1C6 = rand_range(-60, 60) + 120;
    }
    if (racer->unk18C > 0) {
        racer->unk18C -= updateRate;
    } else {
        racer->unk18C = 0;
    }
    gCurrentRacerMiscAssetPtr = (f32 *) get_misc_asset(ASSET_MISC_RACER_WEIGHT);
    gCurrentRacerWeightStat = gCurrentRacerMiscAssetPtr[racer->characterId] * 0.45;
    if (racer->bubbleTrapTimer > 0) {
        gCurrentRacerWeightStat = -0.02f;
    }
    gCurrentRacerMiscAssetPtr = (f32 *) get_misc_asset(ASSET_MISC_RACER_HANDLING);
    gCurrentRacerHandlingStat = gCurrentRacerMiscAssetPtr[racer->characterId];
    gCurrentRacerMiscAssetPtr = (f32 *) get_misc_asset(ASSET_MISC_RACER_UNUSED_11);
    gCurrentRacerUnusedMiscAsset11 = gCurrentRacerMiscAssetPtr[racer->characterId];
    xPos = obj->segment.trans.x_position;
    yPos = obj->segment.trans.y_position;
    zPos = obj->segment.trans.z_position;

    if (racer->unk1B2 > 0) {
        racer->unk1B2 -= updateRate;
        if (racer->unk1B2 < 0) {
            racer->unk1B2 = 0;
        }
    }

    racer->miscAnimCounter++; //!@Delta

    if (is_taj_challenge() || func_80023568() || racer->vehicleID == VEHICLE_LOOPDELOOP || D_8011D544 > 120.0f ||
        gRaceStartTimer != 0 || levelHeader->race_type & RACETYPE_CHALLENGE_BATTLE) {
        racer->unk201 = 30;
    }

    var_fv1 = 1000000;
    if (racer->unk201 == 0) {
        objects = get_racer_objects(&countOfObjects);
        playerOneObj = playerTwoObj = NULL;
        for (var_t2 = 0; var_t2 < countOfObjects; var_t2++) {
            tempRacer = &objects[var_t2]->unk64->racer;
            if (tempRacer->playerIndex == PLAYER_ONE) {
                playerOneObj = objects[var_t2];
            }
            if (tempRacer->playerIndex == PLAYER_TWO) {
                playerTwoObj = objects[var_t2];
            }
        }
        if (playerOneObj != NULL) {
            var_fv1 = playerOneObj->segment.trans.x_position - obj->segment.trans.x_position;
            temp_f0 = playerOneObj->segment.trans.z_position - obj->segment.trans.z_position;
            var_fv1 = (var_fv1 * var_fv1) + (temp_f0 * temp_f0);
        }
        if ((playerTwoObj != NULL) && (var_fv1 >= 160000.0)) {
            var_fv1 = playerTwoObj->segment.trans.x_position - obj->segment.trans.x_position;
            temp_f0 = playerTwoObj->segment.trans.z_position - obj->segment.trans.z_position;
            var_fv1 = (var_fv1 * var_fv1) + (temp_f0 * temp_f0);
        }
    }
    if (racer->bubbleTrapTimer > 0) {
        racer->bubbleTrapTimer -= updateRate;
        racer->velocity *= 0.8f; //!@Delta
    }
    if (racer->unk206 > 0) {
        racer->unk18A = racer->unk206;
        racer->unk206 -= updateRate;
    }
    if ((racer->unk201 == 0) && (var_fv1 < 160000.0)) {
        racer->unk201 = 30;
    }
    if (racer->unk201 != 0) {
        racer_AI_pathing_inputs(obj, racer, updateRate);
        if (!(gCurrentRacerInput & A_BUTTON)) {
            racer->throttleReleased = TRUE;
        }
        if (racer->unk1FE == 3) {
            gCurrentRacerWeightStat *= ((f32) racer->unk1FF / 256);
        }
        if (racer->unk1FE == 1) {
            gCurrentRacerWeightStat -= ((gCurrentRacerWeightStat * racer->unk1FF) / 128);
            if (racer->bubbleTrapTimer > 0) {
                gCurrentRacerWeightStat = -gCurrentRacerWeightStat;
            }
            gCurrentStickY = 60;
        }
        if (racer->unk1FE == 2) {
            racer->unk84 += ((((sins_f(racer->unk1FF << 8) * 4) - racer->unk84) * 0.0625 * updateRateF));
            racer->unk88 += ((((coss_f(racer->unk1FF << 8) * 4) - racer->unk88) * 0.0625 * updateRateF));
        } else {
            racer->unk84 -= racer->unk84 * 0.0625 * updateRateF;
            racer->unk88 -= racer->unk88 * 0.0625 * updateRateF;
        }
        gCurrentRacerHandlingStat = 1;
        gCurrentRacerMiscAssetPtr = (f32 *) get_misc_asset(ASSET_MISC_RACERACCELERATION_UNKNOWN0);
        D_8011D568 = (f32 *) get_misc_asset(obj->segment.header->unk5D);
        if ((obj->segment.y_velocity < 4.0) && ((racer->groundedWheels >= 3) || (racer->buoyancy != 0.0))) {
            racer->unk1F1 = 0;
        }
        if (racer->magnetTimer != 0) {
            racer_activate_magnet(obj, racer, updateRate);
        }
        if (racer->vehicleID != VEHICLE_HOVERCRAFT) {
            racer->waterTimer = 0;
            racer->buoyancy = 0;
            gRacerWaveCount = 0;
        } else {
            gRacerWaveCount = func_8002B0F4(obj->segment.object.segmentID, obj->segment.trans.x_position,
                                            obj->segment.trans.z_position, &gRacerCurrentWave);
        }
        func_8002ACC8(0);
        if (racer->approachTarget != NULL || gRaceStartTimer != 0 || racer->bubbleTrapTimer > 0) {
            gCurrentStickX = 0;
            gCurrentStickY = 0;
            gCurrentRacerInput = 0;
            gCurrentButtonsReleased = 0;
            gCurrentButtonsPressed = 0;
        }

        // clang-format off
        // The case statements break must be on the same line as the function call in order to match
        switch (racer->vehicleID) {
        case VEHICLE_CAR: func_8004F7F4(updateRate, updateRateF, obj, racer); break;
        case VEHICLE_LOOPDELOOP: func_8004CC20(updateRate, updateRateF, obj, racer); break;
        case VEHICLE_HOVERCRAFT: func_80046524(updateRate, updateRateF, obj, racer); break;
        case VEHICLE_PLANE: func_80049794(updateRate, updateRateF, obj, racer); break;
        case VEHICLE_FLYING_CAR: /* fall through */
        case VEHICLE_CARPET: update_carpet(updateRate, updateRateF, obj, racer); break;
        case VEHICLE_TRICKY: update_tricky(updateRate, updateRateF, obj, racer, &gCurrentRacerInput, &gCurrentButtonsPressed, &gRaceStartTimer); break;
        case VEHICLE_BLUEY: update_bluey(updateRate, updateRateF, obj, racer, &gCurrentRacerInput, &gCurrentButtonsPressed, &gRaceStartTimer); break;
        case VEHICLE_SMOKEY: /* fall through */
        case VEHICLE_PTERODACTYL: update_smokey(updateRate, updateRateF, obj, racer, &gCurrentRacerInput, &gCurrentStickX, &gRaceStartTimer); break;
        case VEHICLE_BUBBLER: update_bubbler(updateRate, updateRateF, obj, racer, &gCurrentRacerInput, &gCurrentButtonsPressed, &gRaceStartTimer); break;
        case VEHICLE_WIZPIG: update_wizpig(updateRate, updateRateF, obj, racer, &gCurrentRacerInput, &gCurrentButtonsPressed, &gRaceStartTimer); break;
        case VEHICLE_ROCKET: update_rocket(updateRate, updateRateF, obj, racer, &gCurrentRacerInput, &gCurrentButtonsPressed, &gRaceStartTimer); break;
        }
        // clang-format on

        if (gameMode != GAMEMODE_MENU) {
            racer_sound_update(obj, gCurrentButtonsPressed, gCurrentRacerInput, updateRate);
        }
        lastCheckpointDist = racer->checkpoint_distance;
        countOfObjects = racer->checkpoint;
        var_t2 = func_800185E4(racer->checkpoint, obj, xPos, yPos, zPos, &racer->checkpoint_distance, &racer->unk1C8);
        if (var_t2 == -100) {
            func_8005C270(racer);
        }
        checkpoint = find_next_checkpoint_node(racer->checkpoint, racer->unk1C8);
        if (checkpoint->unk36[racer->unk1CA] == 5) {
            racer->unk201 = 30;
            if (racer->waterTimer) {
                racer->unk1C8 = 1;
            }
        }
        if (checkpoint->unk36[racer->unk1CA] == 6) {
            racer->lap = levelHeader->laps + 1;
        }
        if (checkpoint->unk36[racer->unk1CA] == 4) {
            if (racer->velocity < -4.0) {
                racer->velocity *= 0.9; //!@Delta
            }
        }
        if (var_t2 == 0) {
            if (checkpoint->unk36[racer->unk1CA] == 2) {
                racer->unk1C8 = 1;
            }
            temp_v0_10 = get_checkpoint_count();
            racer->checkpoint++;
            if (racer->checkpoint >= temp_v0_10) {
                racer->checkpoint = 0;
                if (racer->courseCheckpoint > 0) {
                    if (racer->lap < 120) {
                        racer->lap++;
                    }
                }
            }
            if (racer->courseCheckpoint < ((levelHeader->laps + 3) * temp_v0_10)) {
                racer->courseCheckpoint++;
            }
            racer->unk1A8 = 10000;
        } else {
            if (racer->playerIndex == PLAYER_COMPUTER && lastCheckpointDist < racer->checkpoint_distance) {
                racer->checkpoint_distance = lastCheckpointDist;
            }
            racer->unk1A8 = var_t2;
        }
        racer->unk68 = obj->segment.trans.x_position;
        racer->unk6C = obj->segment.trans.y_position;
        racer->unk70 = obj->segment.trans.z_position;
    } else {
        func_8005B818(obj, racer, updateRate, updateRateF);
        if (gameMode != GAMEMODE_MENU) {
            racer_sound_update(obj, gCurrentButtonsPressed, gCurrentRacerInput, updateRate);
        }
    }
    if (racer->magnetTimer == 0) {
        if (racer->magnetSoundMask != NULL) {
            sndp_stop(racer->magnetSoundMask);
            racer->magnetSoundMask = NULL;
        }
    }
    func_80018CE0(obj, xPos, yPos, zPos, updateRate);
    if (racer->unk188 > 0) {
        drop_bananas(obj, racer, racer->unk188);
    }
    if (racer->approachTarget != NULL) {
        racer->approachTarget = NULL;
        racer->velocity = 0.0f;
        racer->lateral_velocity = 0.0f;
    }
    if (racer->stretch_height <= racer->stretch_height_cap) {
        temp_fv1_2 = 0.02f;
    } else {
        temp_fv1_2 = -0.02f;
    }
    racer->stretch_height =
        (racer->stretch_height +
         ((((racer->stretch_height_cap - racer->stretch_height) * 0.125) + temp_fv1_2) * updateRateF));
    if (((temp_fv1_2 < 0.0f) && (racer->stretch_height <= racer->stretch_height_cap)) ||
        ((temp_fv1_2 > 0.0f) && (racer->stretch_height_cap <= racer->stretch_height))) {
        racer->stretch_height = racer->stretch_height_cap;
        racer->stretch_height_cap = 1.0f;
    }
    var_t2 = ((racer->headAngleTarget - racer->headAngle) * updateRate) >> 3;
    CLAMP(var_t2, -0x800, 0x800)
#ifdef ANTI_TAMPER
    if (gAntiPiracyHeadroll) {
        racer->headAngle += gAntiPiracyHeadroll;
    } else {
        racer->headAngle += var_t2;
    }
#else
    racer->headAngle += var_t2;
#endif
    if (racer->shieldTimer > 0) {
        if (racer->shieldTimer > 60) {
            if (racer->shieldSoundMask) {
                audspat_point_set_position(racer->shieldSoundMask, obj->segment.trans.x_position,
                                           obj->segment.trans.y_position, obj->segment.trans.z_position);
            } else if (racer->vehicleSound) {
                audspat_play_sound_at_position(SOUND_SHIELD, obj->segment.trans.x_position,
                                               obj->segment.trans.y_position, obj->segment.trans.z_position,
                                               AUDIO_POINT_FLAG_1, &racer->shieldSoundMask);
            }
        } else {
            if (racer->shieldSoundMask) {
                audspat_point_stop(racer->shieldSoundMask);
                racer->shieldSoundMask = NULL;
            }
        }
        racer->shieldTimer -= updateRate;
        if (racer->shieldTimer <= 0) {
            racer->shieldType = 0;
        }
    }
    if (racer->soundMask != NULL) {
        audspat_point_set_position(racer->soundMask, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                   obj->segment.trans.z_position);
    }
    gRacerInputBlocked = FALSE;
    if (racer->unk150 != NULL && gRaceStartTimer == 0) {
        s8 *temp;
        racer->unk150->segment.trans.x_position = obj->segment.trans.x_position;
        temp = (s8 *) get_misc_asset(ASSET_MISC_0);
        racer->unk150->segment.trans.y_position = obj->segment.trans.y_position + temp[racer->characterId];
        racer->unk150->segment.trans.z_position = obj->segment.trans.z_position;
        racer->unk150->segment.trans.scale = obj->segment.object.distanceToCamera / 265.0f;
        if (obj->segment.object.distanceToCamera < 1500.0) {
            racer->unk150->segment.trans.flags |= OBJ_FLAGS_INVISIBLE;
        }
        if (racer->unk150->segment.trans.scale < 1.0) {
            racer->unk150->segment.trans.scale = 1.0f;
        }
        racer->unk150 = NULL;
    }
    racer->unk1FE = 0xFF;
    set_racer_tail_lights(racer);
}

void func_8005B818(Object *obj, Object_Racer *racer, s32 updateRate, f32 updateRateF) {
    f32 temp_f0;
    s32 checkpointIdx;
    s32 checkpointCount;
    CheckpointNode *checkpoint;
    LevelModel *model;
    f32 var_f28;
    f32 checkpointX[4];
    s32 j;
    f32 checkpointY[4];
    f32 var_f12;
    f32 checkpointZ[4];
    s32 checkpointSplineIdx;
    f32 checkpointDistance;
    UNUSED f32 pad1;
    UNUSED f32 pad2;
    f32 spB8[4];
    f32 var_f26;
    f32 spA4[4];
    UNUSED f32 pad3;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 checkpointPositionOffset;
    f32 tempRacerVelocity;
    f32 var_f24;
    s32 i;
    LevelHeader *levelHeader;
#if VERSION == VERSION_80
    UNUSED f32 pad4;
#endif

    gCurrentRacerMiscAssetPtr = (f32 *) get_misc_asset(ASSET_MISC_RACERACCELERATION_UNKNOWN0);
    levelHeader = get_current_level_header();
    checkpointCount = get_checkpoint_count();
    if (checkpointCount == 0) {
        return;
    }

    racer->unk1C9 = 0;
    racer->zipperDirCorrection = 0;
    racer->attackType = ATTACK_NONE;
    racer->lateral_velocity = 0;
    sp94 = 20.0f;
    if (racer->unk124 < -sp94) {
        racer->unk124 = -sp94;
    }

    if (racer->unk124 > sp94) {
        racer->unk124 = sp94;
    }

    var_f12 = sqrtf(((racer->unk124 * 0.025) + 0.595) / 0.004);
    if (racer->boostTimer != 0) {
        var_f12 *= 1.3;
    }

    if (racer->vehicleID == VEHICLE_HOVERCRAFT) {
        i = (racer->unk1BE & 0xFFFF) - (racer->unk1C2 & 0xFFFF);
        if (i > 0x8000) {
            i -= 0xFFFF;
        }

        if (i < -0x8000) {
            i += 0xFFFF;
        }

        if (i < 0) {
            i = -i;
        }

        i -= 200;
        if (i < 0) {
            i = 0;
        }
        sp94 = (f32) i / 150.0;
        var_f12 -= sp94;
        if (var_f12 < 2.0) {
            var_f12 = 2.0f;
        }

        if (racer->velocity < -var_f12) {
            racer->velocity = -var_f12;
        } else {
            racer->velocity += ((-var_f12 - racer->velocity) * 0.125);
        }
    } else {
        racer->velocity += ((-var_f12 - racer->velocity) * 0.25);
    }

    checkpointIdx = racer->checkpoint - 2;
    if (checkpointIdx < 0) {
        checkpointIdx += checkpointCount;
    }

    if (checkpointIdx >= checkpointCount) {
        checkpointIdx -= checkpointCount;
    }

    for (i = 0; i < 5; i++) {
        checkpoint = find_next_checkpoint_node(checkpointIdx, racer->unk1C8);
        checkpointX[i] = checkpoint->x;
        checkpointY[i] = checkpoint->y;
        checkpointZ[i] = checkpoint->z;
        spB8[i] = checkpoint->unk2E[racer->unk1CA];
        spA4[i] = checkpoint->unk32[racer->unk1CA];
        checkpointX[i] += ((checkpoint->scale * checkpoint->rotationZFrac * checkpoint->unk2E[racer->unk1CA]));
        checkpointY[i] += ((checkpoint->scale * checkpoint->unk32[racer->unk1CA]));
        checkpointZ[i] += ((checkpoint->scale * -checkpoint->rotationXFrac * checkpoint->unk2E[racer->unk1CA]));
        checkpointIdx++;
        if (checkpointIdx == checkpointCount) {
            checkpointIdx = 0;
        }
    }

    tempRacerVelocity = racer->velocity;
    if (tempRacerVelocity < 0.0f) {
        tempRacerVelocity = -tempRacerVelocity;
    }
    checkpointSplineIdx = 0;
    if (racer->unkAC == 0.0) {
        racer->unkAC = 0.01f;
    }
    j = 0;
    do {
        checkpointDistance = (1.0 - racer->checkpoint_distance) + (racer->unkAC * updateRateF);
        if (checkpointDistance >= 1.0) {
            checkpointSplineIdx = 1;
            checkpointDistance -= 1.0;
        }
        var_f24 = cubic_spline_interpolation(checkpointX, checkpointSplineIdx, checkpointDistance, &sp9C);
        var_f26 = cubic_spline_interpolation(checkpointY, checkpointSplineIdx, checkpointDistance, &sp98);
        var_f28 = cubic_spline_interpolation(checkpointZ, checkpointSplineIdx, checkpointDistance, &sp94);
        var_f24 -= racer->unk68;
        var_f26 -= racer->unk6C;
        var_f28 -= racer->unk70;
        if (j == 0) {
            checkpointSplineIdx = 0;
            checkpointPositionOffset =
                sqrtf((var_f24 * var_f24) + (var_f26 * var_f26) + (var_f28 * var_f28)) / updateRateF;
            if (checkpointPositionOffset != 0.0f) {
                racer->unkAC *= (tempRacerVelocity / checkpointPositionOffset);
            } else {
                j = -1;
                racer->unkAC += 0.01;
            }
        }
        j++;
    } while (j < 2);
    racer->unk68 += var_f24;
    racer->unk6C += var_f26;
    racer->unk70 += var_f28;
    var_f24 = racer->unk68 - obj->segment.trans.x_position;
    var_f26 = racer->unk6C - obj->segment.trans.y_position;
    var_f28 = racer->unk70 - obj->segment.trans.z_position;
    checkpointPositionOffset = sqrtf((var_f24 * var_f24) + (var_f28 * var_f28)) / updateRateF;
    if (checkpointPositionOffset > 35.0) {
        temp_f0 = (35.0 / checkpointPositionOffset);
        var_f24 *= temp_f0;
        var_f28 *= temp_f0;
    }
    racer->checkpoint_distance = (1.0 - checkpointDistance);
    if (checkpointSplineIdx != 0) {
        racer->checkpoint++;
        if (racer->checkpoint >= checkpointCount) {
            racer->checkpoint = 0;
            if (racer->courseCheckpoint > 0) {
                if (racer->lap < 120) {
                    racer->lap++;
                }
            }
        }

        if (racer->courseCheckpoint < ((levelHeader->laps + 3) * checkpointCount)) {
            racer->courseCheckpoint++;
        }
        racer->unk1A8 = 10000;
    } else {
        racer->unk1A8 = racer->checkpoint_distance * 100;
    }
    if (racer->boostTimer > 0) {
        racer->boostTimer -= updateRate;
    } else {
        racer->boostTimer = 0;
    }
    racer->unk1BA = spB8[1] + ((spB8[2] - spB8[1]) * checkpointDistance);
    racer->unk1BC = spA4[1] + ((spA4[2] - spA4[1]) * checkpointDistance);
    temp_f0 = sqrtf((sp9C * sp9C) + (sp94 * sp94));
    if (temp_f0 != 0.0f) {
        sp9C /= temp_f0;
        sp98 /= temp_f0;
        sp94 /= temp_f0;
        racer->steerVisualRotation = arctan2_f(sp9C, sp94) - 0x8000;
        obj->segment.trans.rotation.y_rotation = racer->steerVisualRotation;
        obj->segment.trans.rotation.x_rotation = arctan2_f(sp98, 1.0f);
    }
    racer->unk1C2 = racer->unk1BE;
    racer->unk1C4 = racer->unk1C0;
    racer->unk1BE = racer->steerVisualRotation;
    racer->unk1C0 = obj->segment.trans.rotation.x_rotation;
    if (move_object(obj, var_f24, var_f26, var_f28)) {
        if (1) {}
#if VERSION < VERSION_80
        obj->segment.trans.x_position += var_f24;
        obj->segment.trans.y_position += var_f26;
        obj->segment.trans.z_position += var_f28;
#else
        model = get_current_level_model();
        obj->segment.trans.x_position += var_f24;
        obj->segment.trans.y_position += var_f26;
        obj->segment.trans.z_position += var_f28;
        // Don't get caught up on this using checkpointDistance var when documenting. It just matched that way.
        checkpointDistance = model->upperXBounds + 1000.0f;
        if (obj->segment.trans.x_position > checkpointDistance) {
            obj->segment.trans.x_position = checkpointDistance;
        }
        checkpointDistance = model->lowerXBounds - 1000.0f;
        if (obj->segment.trans.x_position < checkpointDistance) {
            obj->segment.trans.x_position = checkpointDistance;
        }
        checkpointDistance = model->upperYBounds + 3000.0f;
        if (obj->segment.trans.y_position > checkpointDistance) {
            obj->segment.trans.y_position = checkpointDistance;
        }
        checkpointDistance = model->lowerYBounds - 500.0f;
        if (obj->segment.trans.y_position < checkpointDistance) {
            obj->segment.trans.y_position = checkpointDistance;
        }
        checkpointDistance = model->upperZBounds + 1000.0f;
        if (obj->segment.trans.z_position > checkpointDistance) {
            obj->segment.trans.z_position = checkpointDistance;
        }
        checkpointDistance = model->lowerZBounds - 1000.0f;
        if (obj->segment.trans.z_position < checkpointDistance) {
            obj->segment.trans.z_position = checkpointDistance;
        }
#endif
    }
    if (checkpointPositionOffset < 20.0) {
        obj->segment.x_velocity = var_f24 / updateRateF;
        obj->segment.y_velocity = -1.0f;
        obj->segment.z_velocity = var_f28 / updateRateF;
    }
    func_80042D20(obj, racer, updateRate);
    handle_racer_items(obj, racer, updateRate);
    racer->waterTimer = 0;
    obj->interactObj->x_position = obj->segment.trans.x_position;
    obj->interactObj->y_position = obj->segment.trans.y_position;
    obj->interactObj->z_position = obj->segment.trans.z_position;
    racer->drift_direction = 0;
    racer->y_rotation_vel = 0;
    racer->z_rotation_vel = 0;
    racer->unk1D2 = 0;
    racer->carBobX = 0.0f;
    racer->carBobY = 0.0f;
    racer->carBobZ = 0.0f;
    obj->segment.y_velocity = 0.0f;
    racer->unkD8.x = obj->segment.trans.x_position;
    racer->unkD8.y = obj->segment.trans.y_position;
    racer->unkD8.z = obj->segment.trans.z_position;
    racer->unkE4.x = obj->segment.trans.x_position;
    racer->unkE4.y = obj->segment.trans.y_position;
    racer->unkE4.z = obj->segment.trans.z_position;
    racer->unkF0.x = obj->segment.trans.x_position;
    racer->unkF0.y = obj->segment.trans.y_position;
    racer->unkF0.z = obj->segment.trans.z_position;
    racer->unkFC.x = obj->segment.trans.x_position;
    racer->unkFC.y = obj->segment.trans.y_position;
    racer->unkFC.z = obj->segment.trans.z_position;
    obj->particleEmittersEnabled = OBJ_EMIT_NONE;
    update_vehicle_particles(obj, updateRate);
}

#ifdef ANTI_TAMPER
// This gets called if an anti-piracy checksum fails in allocate_object_model_pools.
/**
 * Triggered upon failure of an anti-tamper test. Sets the first index of the surface speed
 * table to an unreasonable value, wrecking drivability while on it.
 */
void drm_vehicle_traction(void) {
    gSurfaceTractionTable[SURFACE_DEFAULT] = 0.05f;
}
#endif

void func_8005C270(Object_Racer *racer) {
    s32 temp = get_checkpoint_count();

    racer->checkpoint--;
    if (racer->checkpoint < 0) {
        racer->checkpoint += temp;
        if (racer->lap > 0) {
            racer->lap--;
        }
    }

    if (racer->courseCheckpoint > -0x7D00) {
        racer->courseCheckpoint--;
    }
}
