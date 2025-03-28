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

FadeTransition gDoorFadeTransition = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 50, -1);

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
ObjectCamera *gCameraObject;
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
s32 D_8011D5B4;
s16 D_8011D5B8;

/******************************/

#ifdef NON_EQUIVALENT
void func_80042D20(Object *obj, Object_Racer *racer, s32 updateRate) {
    s32 numRacers;
    u8 *miscAsset4;
    f32 sp90;
    s32 var_v0;
    f32 temp_f12;
    s16 index;
    s8 sp3F;
    f32 sp94;
    s16 temp_v1_2;
    s16 var_t0;
    Object_64 *sp5C;
    s16 var_t5;
    s16 racerID;
    LevelHeader *header;
    Object **racerGroup;
    s8 balloonType;
    s16 temp_v0;
    f32 *miscAsset3;
    s16 sp3C;
    s16 sp38;
    Object_64 *sp58;
    AIBehaviourTable *sp54;
    s16 sp3A;
    f32 temp_f0;
    s16 sp6E;
    f32 var_f14;
    s8 *miscAsset2;
    s8 *miscAsset1;
    s16 sp36;
    Object *temp_v0_3;
    s16 var_t4;
    s16 temp_v0_10;

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
    } else {
        index = 0;
        var_t5 = 0;
        var_t0 = 0;
        var_t4 = -1;
        for (var_v0 = 1; index < numRacers; index++) {
            if ((Object_Racer *) racerGroup[index]->unk64 == racer) {
                var_v0 = FALSE;
                racerID = index;
            }
            if (racerGroup[index]->unk64->racer.playerIndex == PLAYER_COMPUTER) {
                var_t0++;
                if (var_v0) {
                    var_t5++;
                }
            } else if (var_t4 == -1) {
                var_t4 = index;
            }
        }
        if (var_t4 == -1) {
            var_t4 = 0;
        }
        if (var_t0 != 0) {
            temp_v0 = func_80023568();
            if (gRaceStartTimer == 0) {
                if (racer->vehicleID != VEHICLE_LOOPDELOOP) {
                    temp_v1_2 = racerID - 1;
                    if (racer->unk20B < racerID && temp_v1_2 >= 0 && temp_v1_2 < numRacers) {
                        if (racerGroup[temp_v1_2]->unk64->racer.playerIndex != PLAYER_COMPUTER) {
                            if (temp_v0 == FALSE) {
                                play_random_character_voice(obj, SOUND_VOICE_CHARACTER_NEGATIVE, 8, 3);
                            } else {
                                racer_boss_sound_spatial(obj->segment.trans.x_position, obj->segment.trans.y_position,
                                                         obj->segment.trans.z_position, 5);
                            }
                            play_random_character_voice(racerGroup[temp_v1_2], SOUND_VOICE_CHARACTER_POSITIVE, 8, 2);
                        }
                    }
                    temp_v1_2 = racerID + 1;
                    if (racer->unk20B < racerID && temp_v1_2 >= 0 && temp_v1_2 < numRacers) {
                        if (racerGroup[temp_v1_2]->unk64->racer.playerIndex != PLAYER_COMPUTER) {
                            play_random_character_voice(racerGroup[racerID + 1], SOUND_VOICE_CHARACTER_NEGATIVE, 8, 2);
                            if (temp_v0 == FALSE) {
                                play_random_character_voice(obj, SOUND_VOICE_CHARACTER_POSITIVE, 8, 3);
                            } else {
                                racer_boss_sound_spatial(obj->segment.trans.x_position, obj->segment.trans.y_position,
                                                         obj->segment.trans.z_position, 3);
                            }
                        }
                    }
                }
            }
            racer->unk20B = racerID;
            sp5C = NULL;
            sp94 = 0.0f;
            sp90 = 0.0f;
            temp_v0_3 = func_8001B7A8(racer, 1, &sp94);
            if (temp_v0_3 != NULL) {
                sp5C = temp_v0_3->unk64;
            }
            sp58 = NULL;
            temp_v0_3 = func_8001B7A8(racer, -1, &sp90);
            if (temp_v0_3 != NULL) {
                sp58 = temp_v0_3->unk64;
            }
            if (sp5C != NULL) {
                sp3F = sp5C->racer.characterId;
            }
            if (var_t0 < 7 && get_trophy_race_world_id() == 0 && func_80023568() == 0 && is_taj_challenge() == 0) {
                if (gRaceStartTimer == 100) {
                    racer->aiSkill = get_random_number_from_range(AI_MASTER, AI_HARD);
                }
            } else {
                if (get_trophy_race_world_id() != 0) {
                    racer->aiSkill = header->unk16[racer->characterId];
                } else {
                    racer->aiSkill = header->unkC[racer->characterId];
                }
            }
            if (D_8011D544 != 0.0f) {
                racer->unk1CA = D_800DCDA0[racer->racePosition];
            }
            if ((f32) (s16) ((racer->aiSkill - 2) << 2) <= 300.0f - D_8011D544) {
                gCurrentRacerInput |= A_BUTTON;
            }
            miscAsset4 = (u8 *) get_misc_asset(ASSET_MISC_BALLOON_DATA);
            if (racer->balloon_level < 3) {
                balloonType = miscAsset4[racer->balloon_type * 3 + racer->balloon_level];
            } else {
                balloonType = racer->balloon_type;
            }
            sp38 = (((sp54->percentages[1][1] - sp54->percentages[1][0]) * (7 - var_t5)) / 7) + sp54->percentages[1][0];
            sp36 = (((sp54->percentages[2][1] - sp54->percentages[2][0]) * (7 - var_t5)) / 7) + sp54->percentages[2][0];
            sp3A = (((sp54->percentages[0][1] - sp54->percentages[0][0]) * (7 - var_t5)) / 7) + sp54->percentages[0][0];
            sp3C = (((sp54->percentages[3][1] - sp54->percentages[3][0]) * (7 - var_t5)) / 7) + sp54->percentages[3][0];
            if (racer->unk209 & 1) {
                if (racer->unk201 == 0) {
                    if (racer->balloon_level == 0) {
                        if (roll_percent_chance((s16) (s32) sp38)) {
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
                        if (sp5C != NULL && sp5C->racer.playerIndex == PLAYER_COMPUTER) {
                            if (var_t4 < 4) {
                                racer->unk1C6 = miscAsset2[racer->characterId] * 60;
                                racer->unk1C9 = 4;
                            }
                        } else {
                            if (roll_percent_chance(sp36) && var_t4 < 2) {
                                racer->unk1C6 = miscAsset2[racer->characterId] * 60;
                                racer->unk1C9 = 4;
                            }
                        }
                    }
                    if (gRacerAIBalloonActionTable[balloonType] == 2) {
                        if (sp58 != NULL && sp58->racer.playerIndex == PLAYER_COMPUTER) {
                            if (var_t4 < 4) {
                                racer->unk1C6 = miscAsset2[racer->characterId] * 60;
                                racer->unk1C9 = 5;
                            }
                        } else {
                            if (roll_percent_chance(sp36) && var_t4 < 2) {
                                racer->unk1C6 = miscAsset2[racer->characterId] * 60;
                                racer->unk1C9 = 5;
                            }
                        }
                    }
                }
                racer->unk209 &= (0x8000 | 0x4000 | 0x2000 | 0x1000 | 0x800 | 0x400 | 0x200 | 0x100 | 0x80 | 0x40 |
                                  0x20 | 0x10 | 0x8 | 0x4 | 0x2);
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
                    racer->unk209 = (u16) (racer->unk209 & 0xFFFB);
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
                if (sp58 != NULL && sp58->racer.playerIndex != PLAYER_COMPUTER && sp90 < 200.0f && var_t5 != 0 &&
                    var_t4 < 3 && miscAsset1[racer->characterId + (sp3F * 10)] < 5) {
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
            if (7 - var_t5 == 7 && sp58 != NULL && sp90 < -2500.0) {
                racer->unk1CA = 1;
                racer->unk209 = (u16) (racer->unk209 & 0xFFFB);
            }
            if (gRaceStartTimer == 0) {
                temp_f12 = sqrtf(((sp54->unk0 * 0.025) + 0.561) / 0.004);
                temp_f0 = sqrtf(((sp54->unk4 * 0.025) + 0.561) / 0.004);
                temp_f12 += ((temp_f0 - temp_f12) / 7.0f) * (7 - var_t5);
                if (racer->unk1CA > 1) {
                    temp_f12 += (f32) (racer->unk1CA - 1) * 0.2;
                }
                racer->unk124 = (((temp_f12 * temp_f12) * 0.004) - 0.595) / 0.025;
            }
            if (sp5C != NULL && racer->unk1CA == 3 && sp94 < 500.0) {
                racer->unk1CA = 2;
            }
            switch (racer->unk1C9) {
                case 0:
                    if (sp5C != NULL && sp5C->racer.playerIndex == PLAYER_COMPUTER && sp5C->racer.unk1C9 == 0) {
                        if (racer->unk1CA == sp5C->racer.unk1CA && sp94 < 100.0) {
                            racer->unk1CA++;
                            if (racer->unk1CA > 3) {
                                racer->unk1CA = 3;
                            }
                        }
                    }
                    break;
                case 4:
                    if (sp5C != NULL) {
                        racer->unk1BA = sp5C->racer.unk1BA;
                    }
                    break;
                case 5:
                    if (sp58 != NULL) {
                        racer->unk1BA = sp58->racer.unk1BA;
                    }
                    break;
            }
            temp_v0_10 = (u16) is_taj_challenge();
            if (temp_v0_10 != 0 || temp_v0 != 0) {
                racer->unk1CA = 0;
                racer->unk1C9 = 0;
                if (temp_v0 != 0) {
                    miscAsset3 = (f32 *) get_misc_asset(0x12);
                    temp_v0_10 = temp_v0;
                } else {
                    miscAsset3 = (f32 *) get_misc_asset(0x11);
                }
                racer->unk124 = miscAsset3[temp_v0_10];
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
                        var_f14 = racer->unk124;
                        if (D_8011D5B8 > 720) {
                            var_f14 = racer->unk124 + 5.0;
                        } else if (racerID == 1 || sp90 < 200.0) {
                            // This section isn't close to right
                            var_f14 = racer->unk124 + 2.5625;
                        }
                        if (racer->unk124 < var_f14) {
                            racer->unk124 = var_f14;
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
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/racer/func_80042D20.s")
#endif

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
    return get_random_number_from_range(0, 99) < chance;
}

#pragma GLOBAL_ASM("asm/nonmatchings/racer/func_8004447C.s")

void func_80045128(Object **racerObjs) {
    Object_Racer *obj;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = (Object_Racer *) racerObjs[i]->unk64;
        gEggChallengeFlags[i] = obj->lap;
        if (obj->eggHudCounter) {
            gEggChallengeFlags[i] |= 0x40;
        }
        if (obj->held_obj != 0) {
            gEggChallengeFlags[i] |= 0x80;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/racer/func_800452A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/racer/func_80045C48.s")

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
    Asset20 *asset20;
    s8 lastWheelSurface;
    s8 wave_properties;
    s8 wheelsOnStone;
    UNUSED s32 pad3;
    Matrix transformedMtx;
    s8 playerObjectHasMoved;
    f32 var_f6;

    if (func_8000E138()) {
        updateRateF *= 1.15;
    }
    playerObjectHasMoved = FALSE;
    if (racer->playerIndex >= PLAYER_ONE && gNumViewports < 2) {
        obj->particleEmitFlags |= OBJ_EMIT_UNK_100;
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
    object_transform_to_matrix(transformedMtx, &gCurrentRacerTransform);
    guMtxXFMF(transformedMtx, 0.0f, 0.0f, 1.0f, &racer->ox1, &racer->oy1, &racer->oz1);
    guMtxXFMF(transformedMtx, 0.0f, 1.0f, 0.0f, &racer->ox2, &racer->oy2, &racer->oz2);
    guMtxXFMF(transformedMtx, 1.0f, 0.0f, 0.0f, &racer->ox3, &racer->oy3, &racer->oz3);
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
                    sound_play(SOUND_BOUNCE, (s32 *) &racer->unk21C);
                    sound_volume_set_relative(SOUND_BOUNCE, racer->unk21C, (racer->trickType * 2) + 50);
                }
            } else if (racer->approachTarget == NULL) {
                racer_play_sound(obj, SOUND_UNK_AF);
                obj->particleEmitFlags |= OBJ_EMIT_UNK_10 | OBJ_EMIT_UNK_20;
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
            func_800B4668(obj, 8, updateRate << 10, 0x80);
        } else {
            func_800B46BC(obj, 8, updateRate << 9, 0x20);
        }
    }
    if (gCurrentPlayerIndex >= PLAYER_ONE && racer->buoyancy > 0.0) {
        if (gNumViewports < 3) {
            var_f2 = ((obj->segment.x_velocity * obj->segment.x_velocity) +
                      (obj->segment.y_velocity * obj->segment.y_velocity)) +
                     (obj->segment.z_velocity * obj->segment.z_velocity);
            if (var_f2 > 16.0f) {
                if (var_f2 < 80.0f) {
                    obj->particleEmitFlags |= OBJ_EMIT_PARTICLE_3 | OBJ_EMIT_PARTICLE_4;
                }
                if (var_f2 > 28.0f) {
                    obj->particleEmitFlags |= OBJ_EMIT_PARTICLE_1 | OBJ_EMIT_PARTICLE_2;
                }
                if (gNumViewports == 1 && var_f2 > 10.25f) {
                    obj->particleEmitFlags |= OBJ_EMIT_UNK_40;
                }
            }
        } else {
            if (racer->velocity < 0.0f) {
                var_f2 = -racer->velocity;
            } else {
                var_f2 = racer->velocity;
            }
            if (var_f2 > 4.0f) {
                obj->particleEmitFlags |= OBJ_EMIT_PARTICLE_3 | OBJ_EMIT_PARTICLE_4;
            }
        }
    }
    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->boostTimer == 0 && gNumViewports < 2) {
        asset20 = (Asset20 *) get_misc_asset(ASSET_MISC_20);
        asset20 = &asset20[racer->racerIndex];
        iTemp = ((racer->boostType & EMPOWER_BOOST) >> 2) + 10;
        if (iTemp > 10) {
            if (asset20->unk70 > 0 || asset20->unk74 > 0.0) {
                obj->particleEmitFlags |= 1 << iTemp;
            }
        } else if (asset20->unk70 == 2 && asset20->unk74 < 0.5) {
            obj->particleEmitFlags |= 1 << iTemp;
        } else if (asset20->unk70 < 2 && asset20->unk74 > 0.0f) {
            obj->particleEmitFlags |= 1 << iTemp;
        }
    }
    if (racer->unk201 == 0) {
        obj->particleEmitFlags = OBJ_EMIT_OFF;
    } else {
        obj->segment.y_velocity += updateRate * gCurrentRacerWeightStat;
        func_800AF714(obj, updateRate);
        obj->segment.y_velocity -= updateRate * gCurrentRacerWeightStat;
    }
    gCurrentRacerTransform.rotation.y_rotation = -obj->segment.trans.rotation.y_rotation;
    gCurrentRacerTransform.rotation.x_rotation = -obj->segment.trans.rotation.x_rotation;
    gCurrentRacerTransform.rotation.z_rotation = -obj->segment.trans.rotation.z_rotation;
    gCurrentRacerTransform.scale = 1.0f;
    gCurrentRacerTransform.x_position = 0.0f;
    gCurrentRacerTransform.y_position = 0.0f;
    gCurrentRacerTransform.z_position = 0.0f;
    object_transform_to_matrix_2(transformedMtx, &gCurrentRacerTransform);
    guMtxXFMF(transformedMtx, obj->segment.x_velocity, obj->segment.y_velocity, obj->segment.z_velocity,
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
    numViewports = get_viewport_count();
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
    get_viewport_count();
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
        gCameraObject->unk1C = phi_f14;
        gCameraObject->unk20 = phi_f18;
    }
    gCameraObject->unk1C += (phi_f14 - gCameraObject->unk1C) * 0.125; //!@Delta
    gCameraObject->unk20 += (phi_f18 - gCameraObject->unk20) * 0.125; //!@Delta
    sp34 = sins_f(gCameraObject->trans.rotation.x_rotation - sp24);
    phi_f18 = coss_f(gCameraObject->trans.rotation.x_rotation - sp24);
    phi_f18 = (gCameraObject->unk1C * sp34) + (gCameraObject->unk20 * phi_f18);
    xVel = sins_f(-racer->cameraYaw + 0x8000) * gCameraObject->unk1C;
    zVel = coss_f(-racer->cameraYaw + 0x8000) * gCameraObject->unk1C;
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
        gCameraObject->segmentIndex = segmentIndex;
    }
}

/**
 * When on water, apply a rotation effect based on the movement of the waves and turning direction.
 */
f32 rotate_racer_in_water(Object *obj, Object_Racer *racer, Vec3f *pos, s8 arg3, s32 updateRate, s32 arg5, f32 arg6) {
    Matrix mtxF;
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
    object_transform_to_matrix_2(mtxF, &gCurrentRacerTransform);
    guMtxXFMF(mtxF, pos->x, pos->y, pos->z, &pos->x, &pos->y, &pos->z);
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

#pragma GLOBAL_ASM("asm/nonmatchings/racer/func_80049794.s")

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
    if (racer->vehicleID < VEHICLE_TRICKY) {
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

#ifdef NON_EQUIVALENT
void update_camera_plane(f32 updateRate, Object *obj, Object_Racer *racer) {
    s32 segmentIndex;
    f32 baseSpeed;
    f32 tempVel;
    f32 yOffset;
    f32 yVel;
    s32 angle;
    f32 temp_f16;
    f32 baseFloat1 = 120.0f;
    s32 angleVel;
    f32 xOffset;
    f32 zOffset;
    f32 baseFloat2 = 45.0f;
    f32 phi_f14;
    f32 brakeVar = 0.0f;
    s32 numViewports;
    f32 baseFloat3;
    s32 delta;

    delta = (s32) updateRate;
    temp_f16 = gCurrentCourseHeight;
    temp_f16 = 200.0f - (obj->segment.trans.y_position + (-temp_f16));
    if (temp_f16 < 0.0f) {
        temp_f16 = 0.0f;
    }
    if (temp_f16 > 200.0f) {
        temp_f16 = 200.0f;
    }
    numViewports = get_viewport_count();
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
        angle = angle;
        if (angle < -0x8000) {
            angle += 0xFFFF;
        }
        if (racer->camera_zoom < 0.4) {
            racer->camera_zoom += 0.005;
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
    angle = -(angle - ((s32) (temp_f16 * 10.0f)));
    angle = angle - ((u16) gCameraObject->trans.rotation.x_rotation);
    if (angle > 0x8000) {
        angle -= 0xFFFF;
    }
    if (angle < -0x8000) {
        angle += 0xFFFF;
    }
    gCameraObject->trans.rotation.x_rotation += ((angle * delta) >> 4);
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
        phi_f14 = baseSpeed * 60.0f;
        phi_f14 = baseFloat2 + phi_f14;
    } else {
        phi_f14 = baseSpeed * 30.0f;
        phi_f14 = baseFloat2 + phi_f14;
    }
    if (racer->velocity < 0.0 && !racer->groundedWheels) {
        tempVel = -(racer->velocity * brakeVar);
        tempVel = tempVel * 6.0f;
        if (65.0 < tempVel) {
            tempVel = 65.0f;
        }
        if (yOffset) {
            ;
        }
        phi_f14 -= tempVel;
    }
    if (!gRaceStartTimer) {
        if (normalise_time(36) < racer->boostTimer) {
            phi_f14 = -30.0f;
        } else if (racer->boostTimer > 0) {
            phi_f14 = 180.0f;
        }
    }
    if (gRaceStartTimer > 80) {
        gCameraObject->unk1C = phi_f14;
        gCameraObject->unk20 = baseFloat1;
    }
    gCameraObject->unk1C += (phi_f14 - gCameraObject->unk1C) * 0.125;
    gCameraObject->unk20 += (baseFloat1 - gCameraObject->unk20) * 0.125;
    phi_f14 = sins_f(gCameraObject->trans.rotation.x_rotation - 0x400);
    xOffset = coss_f(gCameraObject->trans.rotation.x_rotation - 0x400);
    baseFloat3 = phi_f14;
    baseFloat2 = (gCameraObject->unk1C * baseFloat3) - (gCameraObject->unk20 * xOffset);
    baseFloat1 = ((gCameraObject->unk1C) * (gCameraObject->unk1C));
    baseFloat1 += (gCameraObject->unk20 * baseFloat3);
    xOffset = sins_f(0x8000 - racer->cameraYaw) * baseFloat2;
    zOffset = coss_f(0x8000 - racer->cameraYaw) * baseFloat2;
    yVel = sins_f(racer->cameraYaw + 0x4000) * 3.0f;
    yVel = yVel * racer->lateral_velocity;
    gCameraObject->trans.x_position = (obj->segment.trans.x_position + xOffset) + yVel;
    temp_f16 = obj->segment.trans.y_position;
    yOffset = gCameraObject->trans.y_position - (temp_f16 + baseFloat1);
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
    yVel = racer->unk74;
    yVel = (yOffset * updateRate) / yVel;
    if (yVel > 0.0f && yOffset < yVel) {
        yVel = yOffset;
    }
    if (yVel < 0.0f && yVel < yOffset) {
        yVel = yOffset;
    }
    gCameraObject->trans.y_position -= yVel;
    gCameraObject->trans.z_position =
        zOffset + obj->segment.trans.z_position + (-coss_f(racer->cameraYaw + 0x4000) * 3.0f * racer->lateral_velocity);
    gCameraObject->trans.rotation.y_rotation = racer->cameraYaw;
    if (racer->trickType || gDialogueCameraAngle) {
        angle = -(u16) gCameraObject->trans.rotation.z_rotation;
        if (angle > 0x8000) {
            angle -= 0xFFFF;
        }
        if (angle < -0x8000) {
            angle += 0xFFFF;
        }
        gCameraObject->trans.rotation.z_rotation += angle >> 2;
    } else {
        angle = (u16) gCameraObject->trans.rotation.z_rotation;
        angle = angle + (-(racer->x_rotation_vel >> 4));
        if (angle > 0x8000) {
            angle -= 0xFFFF;
        }
        if (angle < -0x8000) {
            angle += 0xFFFF;
        }
        gCameraObject->trans.rotation.z_rotation += angle >> 3;
    }
    tempVel = gCameraObject->trans.x_position;
    segmentIndex = get_level_segment_index_from_position(tempVel, gCameraObject->trans.y_position,
                                                         gCameraObject->trans.z_position);
    if (segmentIndex != -1) {
        gCameraObject->segmentIndex = segmentIndex;
    }
    racer->cameraYaw = gCameraObject->trans.rotation.y_rotation;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/racer/update_camera_plane.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/racer/func_8004CC20.s")

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
    f32 zoom;
    f32 xVel;
    f32 yVel;
    f32 zVel;
    Matrix mtx;
    s32 angleDiff;

    UpdateRate = (s32) updateRateF;
    zoom = 120.0f;
    if (gRaceStartTimer > 60) {
        zoom += ((f32) (gRaceStartTimer - 60) * 4.0f);
    }
    racer->cameraYaw = 0x8000 - racer->steerVisualRotation;
    if (get_viewport_count() == 1) {
        zoom = 160.0f;
    }
    // A little bit of indecisiveness.
    if (gCameraObject->zoom == ZOOM_FAR) {
        zoom += 35.0f;
    }
    if (gCameraObject->zoom == ZOOM_FAR) {
        zoom -= 35.0f;
    }
    gCameraObject->unk1C += (zoom - gCameraObject->unk1C) * 0.125;
    gCurrentRacerTransform.rotation.y_rotation = -gCameraObject->trans.rotation.y_rotation + 0x8000;
    gCurrentRacerTransform.rotation.x_rotation = -gCameraObject->trans.rotation.x_rotation;
    gCurrentRacerTransform.rotation.z_rotation = 0;
    gCurrentRacerTransform.x_position = 0.0f;
    gCurrentRacerTransform.y_position = 0.0f;
    gCurrentRacerTransform.z_position = 0.0f;
    gCurrentRacerTransform.scale = 1.0f;
    object_transform_to_matrix(mtx, &gCurrentRacerTransform);
    guMtxXFMF(mtx, 0.0f, 0.0f, gCameraObject->unk1C, &xVel, &yVel, &zVel);
    gCameraObject->trans.x_position = obj->segment.trans.x_position + xVel;
    gCameraObject->trans.y_position = obj->segment.trans.y_position + yVel;
    gCameraObject->trans.z_position = obj->segment.trans.z_position + zVel;
    guMtxXFMF(mtx, 0.0f, sins_f(0x800) * gCameraObject->unk1C, 0.0f, &xVel, &yVel, &zVel);
    gCameraObject->trans.x_position += xVel;
    gCameraObject->trans.y_position += yVel;
    gCameraObject->trans.z_position += zVel;
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
        gCameraObject->segmentIndex = segmentIndex;
    }
    racer->cameraYaw = gCameraObject->trans.rotation.y_rotation;
    gCameraObject->trans.x_position += gCameraObject->offsetX;
    gCameraObject->trans.y_position += gCameraObject->offsetY;
    gCameraObject->trans.z_position += gCameraObject->offsetZ;
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
    tempRacer = (struct Object_Racer *) obj->unk64;
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
        gCameraObject = (ObjectCamera *) get_active_camera_segment_no_cutscenes();
        gCameraObject->trans.rotation.z_rotation = 0;
        gCameraObject->trans.rotation.x_rotation = 0x400;
        gCameraObject->trans.rotation.y_rotation = tempRacer->cameraYaw;
        gCameraObject->mode = CAMERA_CAR;
        gCameraObject->unk3C = 0xFF;
        gCameraObject->unk3D = 0xFF;
        gCameraObject->unk3E = 0xFF;
        gCameraObject->unk3F = 0xFF;
        gCameraObject->unk18 = 0.0f;
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

    gNumViewports = get_viewport_count() + 1;
    gCurrentSurfaceType = SURFACE_DEFAULT;
    gRaceStartTimer = get_race_countdown();
    updateRateF = updateRate;
    tempRacer = (Object_Racer *) obj->unk64;
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
    obj->particleEmitFlags = OBJ_EMIT_OFF;
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
            tempRacer->unk1C6 = get_random_number_from_range(-60, 60) + 120;
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
        gCameraObject = (ObjectCamera *) get_active_camera_segment_no_cutscenes();
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
                tempRacer->unk1D1 = get_random_number_from_range(-80, 80);
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
            gCameraObject = (ObjectCamera *) get_active_camera_segment_no_cutscenes();
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
                sound_stop(tempRacer->magnetSoundMask);
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
                        tempRacer->challengeMarker = spawn_object(&newObject, 1);
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
                    update_spatial_audio_position(tempRacer->shieldSoundMask, obj->segment.trans.x_position,
                                                  obj->segment.trans.y_position, obj->segment.trans.z_position);
                } else if (tempRacer->vehicleSound) {
                    play_sound_at_position(SOUND_SHIELD, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                           obj->segment.trans.z_position, 1, &tempRacer->shieldSoundMask);
                }
            } else if (tempRacer->shieldSoundMask) {
                func_800096F8(tempRacer->shieldSoundMask);
                tempRacer->shieldSoundMask = NULL;
            }
            tempRacer->shieldTimer -= updateRate;
            if (tempRacer->shieldTimer <= 0) {
                tempRacer->shieldType = SHIELD_NONE;
            }
        }
        if (tempRacer->bananaSoundMask) {
            update_spatial_audio_position(tempRacer->bananaSoundMask, obj->segment.trans.x_position,
                                          obj->segment.trans.y_position, obj->segment.trans.z_position);
        }
        if (is_in_time_trial() && tempRacer->playerIndex == PLAYER_ONE && gRaceStartTimer == 0) {
            timetrial_ghost_write(obj, updateRate);
        }
        if (tempRacer->soundMask) {
            update_spatial_audio_position(tempRacer->soundMask, obj->segment.trans.x_position,
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
                    play_sound_at_position(tempRacer->delaySoundID, obj->segment.trans.x_position,
                                           obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
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
    Matrix sp60;
    LevelHeader *currentLevelHeader;
    Asset20 *asset20;
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
            racerObj->particleEmitFlags |= PARTICLE_VEL_Z;
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
            sound_stop((u8 *) racer->unk1C);
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
                                   racerObj->segment.trans.z_position, (s32 **) &racer->unk21C);
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
            object_transform_to_matrix_2(sp60, &gCurrentRacerTransform);
            guMtxXFMF(sp60, racer->lateral_velocity, 0.0f, racer->velocity, &racerObj->segment.x_velocity, &spBC,
                      &racerObj->segment.z_velocity);
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
        object_transform_to_matrix_2(sp60, &gCurrentRacerTransform);
        guMtxXFMF(sp60, spB8, 0.0f, spB4, &spAC, &spBC, &spB0);
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
            asset20 = (Asset20 *) get_misc_asset(ASSET_MISC_20);
            asset20 = &asset20[racer->racerIndex];
            var_v1 = ((racer->boostType & EMPOWER_BOOST) >> 2) + 0x10;
            if (var_v1 > 0x10) {
                if (asset20->unk70 > 0 || asset20->unk74 > 0.0) {
                    racerObj->particleEmitFlags |= 1 << var_v1;
                }
            } else {
                if (asset20->unk70 == 2 && asset20->unk74 < 0.5) {
                    racerObj->particleEmitFlags |= 1 << var_v1;
                } else if (asset20->unk70 < 2 && asset20->unk74 > 0.0f) {
                    racerObj->particleEmitFlags |= 1 << var_v1;
                }
            }
        }
        if (gCurrentPlayerIndex != PLAYER_COMPUTER && gNumViewports < 2) {
            if (racer->buoyancy > 14.0f) {
                if (get_random_number_from_range(0, 1) != 0) {
                    racerObj->particleEmitFlags |= PARTICLE_COLOURVEL_RED | PARTICLE_COLOURVEL_GREEN;
                }
            } else if (racer->buoyancy < 6.0f) {
                if (racer->velocity > -3.0 && racer->velocity < 0.5 && get_random_number_from_range(0, 1) != 0) {
                    racerObj->particleEmitFlags |= PARTICLE_UNK00040000 | PARTICLE_FORWARDVEL;
                }
            }
        }
        if (racer->vehicleID < VEHICLE_TRICKY) {
            func_800AF714(racerObj, updateRate);
        }
        second_racer_camera_update(racerObj, racer, 0, updateRateF);
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
                    obj->particleEmitFlags |= 0x1000 | 0x400;
                } else if (racer->drift_direction < 0) {
                    obj->particleEmitFlags |= 0x2000 | 0x800;
                } else {
                    obj->particleEmitFlags |= 0x2000 | 0x1000;
                }
            } else {
                sp58 = 1;
            }
        }
        if ((racer->miscAnimCounter & 7) < 2) {
            racer->unk1D1 = get_random_number_from_range(-25, 25);
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
            obj->particleEmitFlags |= 0x2000 | 0x1000 | 0x800 | 0x400;
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
                obj->particleEmitFlags |= 0x1000 | 0x400;
            } else {
                obj->particleEmitFlags |= 0x2000 | 0x800;
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
            obj->particleEmitFlags |= 0x1000 | 0x400;
        } else {
            obj->particleEmitFlags |= 0x2000 | 0x800;
        }
        if (racer->drift_direction != 0 || racer->drifting != 0 || racer->unk1FB != 0) {
            if (racer->unk10 == 0) {
                sound_play_spatial(SOUND_CAR_SLIDE, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                   obj->segment.trans.z_position, (s32 **) &racer->unk10);
            } else {
                func_80009B7C((void *) racer->unk10, obj->segment.trans.x_position, obj->segment.trans.y_position,
                              obj->segment.trans.z_position);
            }
            if (racer->unk14) {
                sound_stop((void *) racer->unk14);
            }
        } else {
            if (racer->unk10) {
                sound_stop((void *) racer->unk10);
            }
        }
    } else {
        if (racer->unk10) {
            sound_stop((void *) racer->unk10);
        }
        if (racer->unk14) {
            sound_stop((void *) racer->unk14);
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
    if (get_viewport_count() < THREE_PLAYERS) {
        if ((sp60 != 0 && racer->velocity < -2.0) || sp58 != 0 || racer->unk1FB != 0) {
            if (racer->wheel_surfaces[2] < SURFACE_NONE) {
                obj->particleEmitFlags |= gSurfaceFlagTable[racer->wheel_surfaces[2]];
            }
            if (racer->wheel_surfaces[3] < SURFACE_NONE) {
                obj->particleEmitFlags |= gSurfaceFlagTable[racer->wheel_surfaces[3]] * 2;
            }
        }
        if (racer->velocity < -2.0) {
            if (racer->wheel_surfaces[2] < SURFACE_NONE) {
                obj->particleEmitFlags |= gSurfaceFlagTable4P[racer->wheel_surfaces[2]];
            }
            if (racer->wheel_surfaces[3] < SURFACE_NONE) {
                obj->particleEmitFlags |= gSurfaceFlagTable4P[racer->wheel_surfaces[3]] * 2;
            }
        }
    }
    // Play a sound on grass and sand when landing on it
    surfaceType = gSurfaceSoundTable[surfaceType];
    if (racer->unk18 == NULL && surfaceType != SOUND_NONE && racer->velocity < -2.0) {
        sound_play(surfaceType, &racer->unk18);
    }
    if (racer->unk18 != NULL && (surfaceType == SOUND_NONE || racer->velocity > -2.0)) {
        sound_stop((void *) racer->unk18);
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
    if (racer->brake < 0.9 && racer->vehicleIDPrev < VEHICLE_TRICKY && gRaceStartTimer == 0) {
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

            racer->headAngleTarget = get_random_number_from_range(-intendedAngle, intendedAngle);
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
        if ((racer->miscAnimCounter & 0x3F) < 0x1F) {
            racer->headAngleTarget = 0;
        }
        racer = (struct Object_Racer *) targetObj->unk64;
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
                obj->particleEmitFlags |= 0x100000;
            } else {
                obj->particleEmitFlags |= 0x80000;
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
        if (gNumViewports < VIEWPORTS_COUNT_4_PLAYERS) {
            obj->particleEmitFlags |= 0x4FC00;
        } else {
            if (racer->wheel_surfaces[2] < SURFACE_NONE) {
                obj->particleEmitFlags |= 1 << (racer->wheel_surfaces[2] * 2);
            }
            if (racer->wheel_surfaces[3] < SURFACE_NONE) {
                obj->particleEmitFlags |= 2 << (racer->wheel_surfaces[3] * 2);
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
        sound_stop((void *) racer->unk18);
    }
    if (racer->unk10) {
        sound_stop((void *) racer->unk10);
    }
    if (racer->unk14) {
        sound_stop((void *) racer->unk14);
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
        obj->particleEmitFlags = OBJ_EMIT_OFF;
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
    obj->particleEmitFlags = OBJ_EMIT_OFF;
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
    Matrix mf;

    gCurrentRacerTransform.rotation.y_rotation = -racer->steerVisualRotation;
    gCurrentRacerTransform.rotation.x_rotation = -obj->segment.trans.rotation.x_rotation;
    gCurrentRacerTransform.rotation.z_rotation = -racer->x_rotation_vel;
    gCurrentRacerTransform.x_position = 0;
    gCurrentRacerTransform.y_position = 0;
    gCurrentRacerTransform.z_position = 0;
    gCurrentRacerTransform.scale = 1;
    object_transform_to_matrix_2(mf, &gCurrentRacerTransform);

    guMtxXFMF(mf, 0.0f, -1.0f, 0.0f, &racer->roll, &racer->yaw, &racer->pitch);
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
            objRacer->particleEmitFlags |= OBJ_EMIT_UNK_400 | OBJ_EMIT_UNK_800;
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
            if (racer->vehicleID < VEHICLE_TRICKY) {
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
    Matrix mtx;
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
        object_transform_to_matrix_2(mtx, &gCurrentRacerTransform);
        guMtxXFMF(mtx, racer->lateral_velocity, 0.0f, racer->velocity, &obj->segment.x_velocity, &tempVel,
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
        obj->particleEmitFlags = OBJ_EMIT_OFF;
    } else if (racer->vehicleID < VEHICLE_TRICKY) {
        func_800AF714(obj, updateRate);
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
    object_transform_to_matrix_2(mtx, &gCurrentRacerTransform);
    guMtxXFMF(mtx, xVel, 0.0f, zVel, &hVel, &tempVel, &yVel);
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
    if (get_viewport_count() < 2 && sp38 && racer->velocity < -2.0) {
        if (racer->wheel_surfaces[2] < SURFACE_NONE) {
            obj->particleEmitFlags |= 1 << (racer->wheel_surfaces[2] * 2);
        }
        if (racer->wheel_surfaces[3] < SURFACE_NONE) {
            obj->particleEmitFlags |= 2 << (racer->wheel_surfaces[3] * 2);
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
    Matrix spA0;
    Matrix sp60;
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
    object_transform_to_matrix(spA0, &gCurrentRacerTransform);

    for (i = 0; i < 4; i++) {
        guMtxXFMF(spA0, D_8011D568[i * 4 + 0], D_8011D568[i * 4 + 1], D_8011D568[i * 4 + 2], &sp134[i * 3 + 0],
                  &sp134[i * 3 + 1], &sp134[i * 3 + 2]);
        spE0[i] = D_8011D568[i * 4 + 3];
        sp58[i] = -1;
    }

    sp190 = 0;
    D_8011D548 = 0;
    D_8011D54C = 0;
    flags = 0;
    if (racer->playerIndex != PLAYER_COMPUTER || racer->vehicleIDPrev < VEHICLE_TRICKY) {
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
                    gCameraObject->unk30 = 3.0f;
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
    object_transform_to_matrix_2(sp60, &gCurrentRacerTransform);
    for (i = 0; i < 4; i++) {
        guMtxXFMF(sp60, ((f32 *) &racer->unkD8)[i * 3 + 0], ((f32 *) &racer->unkD8)[i * 3 + 1],
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
    if (racer->playerIndex != PLAYER_COMPUTER || racer->vehicleIDPrev < VEHICLE_TRICKY) {
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
    Object_64 *magnetTarget;
    f32 objDist;
    ObjectModel *model;
    Object_64 *objData;
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
                    if (obj->unk44 != NULL) {
                        heldObjData = obj->unk44;
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
                                magnetTarget = intendedTarget->unk64;
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
                                magnetTarget->racer.magnetLevel3 = TRUE;
                                magnetTarget->racer.magnetTimer = 120;
                                magnetTarget->racer.magnetTargetObj = obj;
                                magnetTarget->racer.magnetModelID = MAGNET_LEVEL3;
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
                spawnedObj = spawn_object(&newObject, 1);
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
                    objData = spawnedObj->unk64;
                    objData->weapon.owner = obj;
                    objData->weapon.target = intendedTarget;
                    objData->weapon.checkpoint = racer->checkpoint;
                    objData->weapon.forwardVel = (racer->velocity - velocity);
                    objData->weapon.weaponID = weaponID;
                    switch (objData->weapon.weaponID) {
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
                            play_sound_at_position(soundID, obj->segment.trans.x_position,
                                                   obj->segment.trans.y_position, obj->segment.trans.z_position, 4,
                                                   NULL);
                        } else {
                            if (racer->weaponSoundMask) {
                                sound_stop(racer->weaponSoundMask);
                            }
                            sound_play_spatial(soundID, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                               obj->segment.trans.z_position, (s32 **) &racer->weaponSoundMask);
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
    Object_64 *magnetTarget;

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
            sound_play(SOUND_MAGNET_HUM, (void *) &racer->magnetSoundMask);
        }
    } else {
        racer->magnetTimer = 0;
        return;
    }
    diffX /= vel;
    diffZ /= vel;
    magnetTarget = racer->magnetTargetObj->unk64;
    vel = -magnetTarget->racer.velocity;
    if (vel < 8.0 && racer->magnetLevel3 == FALSE) {
        vel = 8.0f;
    }
    if (vel > 20.0) {
        vel = 20.0f;
    }
    gRacerMagnetVelX = (vel + 5.0f) * diffX;
    gRacerMagnetVelZ = (vel + 5.0f) * diffZ;
    if (magnetTarget->racer.shieldTimer && racer->magnetLevel3 == FALSE) {
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

    tempRacer = (Object_Racer *) obj->unk64;
    if (tempRacer->exitObj == 0 && (!(flags & 0x80) || gCurrentPlayerIndex != PLAYER_COMPUTER)) {
        if (flags == 2) {
            if (tempRacer->soundMask != NULL && soundID != tempRacer->unk2A) {
                func_800096F8(tempRacer->soundMask);
                tempRacer->soundMask = 0;
            }
        }
        if (tempRacer->soundMask == NULL && (flags != 3 || get_random_number_from_range(0, 1))) {
            tempRacer->unk2A = soundID;
            soundID += tempRacer->characterId;
            soundIndex = (get_random_number_from_range(0, range - 1) * 12) + soundID;
            if (range - 1 > 0) {
                while (soundIndex == tempRacer->lastSoundID) {
                    soundIndex = (get_random_number_from_range(0, range - 1) * 12) + soundID;
                }
            }
            play_sound_at_position(soundIndex, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                   obj->segment.trans.z_position, 4, &tempRacer->soundMask);
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
    Matrix mtxF;

    gCurrentRacerTransform.rotation.y_rotation = obj->segment.trans.rotation.y_rotation;
    gCurrentRacerTransform.rotation.x_rotation = obj->segment.trans.rotation.x_rotation;
    gCurrentRacerTransform.rotation.z_rotation = 0;
    gCurrentRacerTransform.x_position = 0.0f;
    gCurrentRacerTransform.y_position = 0.0f;
    gCurrentRacerTransform.z_position = 0.0f;
    gCurrentRacerTransform.scale = 1.0f;
    object_transform_to_matrix(mtxF, &gCurrentRacerTransform);
    guMtxXFMF(mtxF, 0.0f, 0.0f, 1.0f, &racer->ox1, &racer->oy1, &racer->oz1);
    guMtxXFMF(mtxF, 0.0f, 1.0f, 0.0f, &racer->ox2, &racer->oy2, &racer->oz2);
    guMtxXFMF(mtxF, 1.0f, 0.0f, 0.0f, &racer->ox3, &racer->oy3, &racer->oz3);
}

/**
 * Racers struck by most weapons will drop up to 2 bananas on the ground.
 * During challenge mode, no bananas are spawned, though the number still drops.
 */
void drop_bananas(Object *obj, Object_Racer *racer, s32 number) {
    LevelObjectEntryCommon newObject;
    Object_Banana *banana;
    s32 i;
    s16 angle[3];
    s16 pos[3];
    Object *bananaObj;
    f32 variance;

    if (!(get_filtered_cheats() & CHEAT_START_WITH_10_BANANAS)) {
        racer->unk188 = 0;
        if (racer->bananas < number) {
            number = racer->bananas;
        }
        if (number > 0 && number < 3) {
            angle[0] = racer->x_rotation_vel;
            angle[1] = obj->segment.trans.rotation.x_rotation;
            angle[2] = racer->steerVisualRotation;
            pos[0] = 0;
            pos[1] = 8;
            pos[2] = 12;
            s16_vec3_apply_object_rotation((ObjectTransform *) angle, pos);
            newObject.x = pos[0] + (s32) obj->segment.trans.x_position;
            newObject.y = pos[1] + (s32) obj->segment.trans.y_position;
            newObject.z = pos[2] + (s32) obj->segment.trans.z_position;
            newObject.size = sizeof(LevelObjectEntryCommon);
            newObject.objectID = ASSET_OBJECT_ID_COIN;
            i = number;
            do {
                if (get_current_level_race_type() != RACETYPE_CHALLENGE) {
                    bananaObj = spawn_object(&newObject, 1);
                    if (bananaObj != NULL) {
                        bananaObj->segment.level_entry = NULL;
                        banana = (Object_Banana *) bananaObj->unk64;
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
            func_80066060(racer->playerIndex, gCameraObject->zoom);
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
    gCameraObject->offsetX = (((obj->segment.trans.x_position + (91.75 * racer->ox1) + (90.0 * racer->ox3)) -
                               gCameraObject->trans.x_position) *
                              dialogueAngle);
    gCameraObject->offsetZ = (((obj->segment.trans.z_position + (91.75 * racer->oz1) + (90.0 * racer->oz3)) -
                               gCameraObject->trans.z_position) *
                              dialogueAngle);
    gCameraObject->offsetY = (((get_npc_pos_y() + 48.5) - gCameraObject->trans.y_position) * dialogueAngle);
    gCameraObject->pitchOffset = -gCameraObject->trans.rotation.x_rotation * dialogueAngle;
    gCameraObject->trans.x_position += gCameraObject->offsetX;
    gCameraObject->trans.y_position += gCameraObject->offsetY + gCameraObject->unk30;
    gCameraObject->trans.z_position += gCameraObject->offsetZ;
    if (!gRaceStartTimer && !gDialogueCameraAngle) {
        gCameraObject->offsetX *= 0.95;
        gCameraObject->offsetY *= 0.95;
        gCameraObject->offsetZ *= 0.95;
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
        gDialogueCameraAngle += (tempUpdateRateF * angle);
        if (gDialogueCameraAngle > 0x2800) {
            gDialogueCameraAngle = 0x2800;
        }
    } else {
        gDialogueCameraAngle -= (tempUpdateRateF * angle);
        if (gDialogueCameraAngle < 0) {
            gDialogueCameraAngle = 0;
        }
    }
    gCameraObject->trans.rotation.y_rotation -= gDialogueCameraAngle;
    gCameraObject->unk3A -= tempUpdateRateF;
    while (gCameraObject->unk3A < 0) {
        gCameraObject->unk3A += 5;
        gCameraObject->unk30 = -gCameraObject->unk30 * 0.75;
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
                gCameraObject->offsetX = xPos - gCameraObject->trans.x_position;
                gCameraObject->offsetY = yPos - (gCameraObject->trans.y_position + gCameraObject->unk30);
                gCameraObject->offsetZ = zPos - gCameraObject->trans.z_position;
            }
        }
    }
}

#ifdef NON_EQUIVALENT
void update_camera_car(f32 updateRate, Object *obj, Object_Racer *racer) {
    s64 pad;
    s32 segmentIndex;
    f32 sp54 = 120.0f;
    f32 baseDistance = 120.0f;
    f32 yVel = 50.0f;
    f32 temp_f16;
    f32 sineOffset;
    f32 baseSpeed;
    f32 lateralOffset;
    s32 angle;
    f32 cosOffset;
    s32 angleVel;
    f32 xOffset;
    f32 yOffset;
    f32 zOffset;
    f32 brakeVar;
    f32 tempVel;
    s32 baseAngle = 0x400;
    s32 newAngle;
    s32 numViewports;
    s32 tempAngle;
    s32 delta = (s32) updateRate;

    numViewports = get_viewport_count();
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
    angle = racer->unk19E >> 3;
    racer->cameraYaw = (-racer->steerVisualRotation - racer->unk19E) + 0x8000;
    if (angle > 0x400) {
        angle = 0x400;
    }
    if (angle < -0x400) {
        angle = -0x400;
    }
    angle = angle * delta;
    angleVel = angle;
    if (angleVel > 0 && angleVel < racer->unk19E) {
        racer->unk19E -= angleVel;
    }
    if (angleVel < 0) {
        if (racer->unk19E < angleVel) {
            racer->unk19E -= angleVel;
        }
    }
    brakeVar = racer->brake;
    baseSpeed = racer->forwardVel;
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
            baseSpeed *= 0.25;
            break;
    }
    if (racer->groundedWheels > 2 || racer->waterTimer != 0) {
        angle = (obj->segment.trans.rotation.x_rotation);
        if (angle > 0) {
            angle -= 0x71C;
            if (angle < 0) {
                angle = 0;
            }
            angle >>= 1;
        } else {
            angle += 0x71C;
            if (angle > 0) {
                angle = 0;
            }
        }
        angle = baseAngle - angle;
        tempAngle = angle - (u16) gCameraObject->trans.rotation.x_rotation;
        if (tempAngle > 0x8000) {
            tempAngle -= 0xFFFF;
        }
        if (tempAngle < -0x8000) {
            tempAngle += 0xFFFF;
        }
        gCameraObject->trans.rotation.x_rotation += (tempAngle * delta) >> 4;
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
        baseDistance += baseSpeed * 60.0f;
    } else {
        baseDistance += baseSpeed * 30.0f;
    }
    if (gRaceStartTimer == 0) {
        if (normalise_time(36) < racer->boostTimer) {
            baseDistance = -30.0f;
        } else if (racer->boostTimer > 0) {
            baseDistance = 180.0f;
        }
    }
    if (gRaceStartTimer > 80) {
        gCameraObject->unk1C = baseDistance;
        gCameraObject->unk20 = yVel;
    }
    gCameraObject->unk1C += (baseDistance - gCameraObject->unk1C) * 0.125;
    gCameraObject->unk20 += (yVel - gCameraObject->unk20) * 0.125;
    cosOffset = sins_f(gCameraObject->trans.rotation.x_rotation - baseAngle);
    sineOffset = coss_f(gCameraObject->trans.rotation.x_rotation - baseAngle);
    lateralOffset = gCameraObject->unk1C;
    lateralOffset = (lateralOffset * sineOffset) - (gCameraObject->unk20 * cosOffset);
    yVel = (gCameraObject->unk1C * cosOffset) + (gCameraObject->unk20 * sineOffset);
    sineOffset = sins_f(-racer->cameraYaw + 0x8000) * lateralOffset;
    cosOffset = coss_f(-racer->cameraYaw + 0x8000) * lateralOffset;
    baseDistance = 0.0f;
    if (gCurrentRacerInput & A_BUTTON) {
        baseDistance = racer->lateral_velocity * 1.3;
        if (baseDistance > 0.0f) {
            baseDistance -= 1.5;
            if (baseDistance < 0.0f) {
                baseDistance = 0.0f;
            }
        } else {
            baseDistance += 1.5;
            if (baseDistance > 0.0f) {
                baseDistance = 0.0f;
            }
        }
    }
    if (racer->drift_direction) {
        baseDistance = -(f32) racer->drift_direction * 12.0f;
    }
    racer->unkC8 += (baseDistance - racer->unkC8) * 0.125;
    if (racer->spinout_timer) {
        racer->camera_zoom -= racer->camera_zoom * 0.25;
    } else {
        racer->camera_zoom += (10.0 - racer->camera_zoom) * 0.25;
    }
    xOffset = obj->segment.trans.x_position - (racer->ox1 * racer->camera_zoom);
    yOffset = obj->segment.trans.y_position - (racer->oy1 * racer->camera_zoom);
    zOffset = obj->segment.trans.z_position - (racer->oz1 * racer->camera_zoom);
    tempVel = sins_f(racer->cameraYaw + 0x4000) * racer->unkC8;
    baseDistance = xOffset + tempVel;
    gCameraObject->trans.x_position = sineOffset + baseDistance;
    yOffset += yVel;
    temp_f16 = (gCameraObject->trans.y_position - yOffset) * 0.25;
    if (temp_f16 < -2.0) {
        gCameraObject->trans.y_position -= temp_f16 + 2.0;
    }
    gCameraObject->trans.y_position -= temp_f16 * 0.25;
    if (temp_f16 > 0.0f || gRaceStartTimer) {
        gCameraObject->trans.y_position = yOffset;
    }
    gCameraObject->trans.z_position = zOffset + (-coss_f(racer->cameraYaw + 0x4000) * racer->unkC8) + cosOffset;
    gCameraObject->trans.rotation.y_rotation = racer->cameraYaw;
    newAngle = gCameraObject->trans.rotation.z_rotation;
    if ((racer->drift_direction && racer->brake > 0.0) || gDialogueCameraAngle) {
        newAngle = 0;
    }
    angle = obj->segment.trans.rotation.z_rotation;
    angleVel = (newAngle + angle) >> 4;
    gCameraObject->trans.rotation.z_rotation -= angleVel;
    if (gCameraObject->trans.rotation.z_rotation > 0x2000) {
        gCameraObject->trans.rotation.z_rotation = 0x2000;
    }
    if (gCameraObject->trans.rotation.z_rotation < -0x2000) {
        gCameraObject->trans.rotation.z_rotation = -0x2000;
    }
    gCameraObject->trans.y_position -= racer->unkC8 * sins_f(gCameraObject->trans.rotation.z_rotation);
    lateralOffset = (yOffset = gCameraObject->trans.x_position);
    segmentIndex = get_level_segment_index_from_position(lateralOffset, gCameraObject->trans.y_position,
                                                         gCameraObject->trans.z_position);
    if (segmentIndex != -1) {
        gCameraObject->segmentIndex = segmentIndex;
    }
    racer->cameraYaw = gCameraObject->trans.rotation.y_rotation;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/racer/update_camera_car.s")
#endif

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
    gCameraObject->unk1C = 150.0f;
    xOffset = sins_f(0x8000 - gCameraObject->trans.rotation.y_rotation) * gCameraObject->unk1C;
    zOffset = coss_f(0x8000 - gCameraObject->trans.rotation.y_rotation) * gCameraObject->unk1C;
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
        gCameraObject->segmentIndex = segmentIndex;
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
    gCameraObject->segmentIndex = get_level_segment_index_from_position(gCameraObject->trans.x_position, racer->oy1,
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
    gCameraObject->segmentIndex = get_level_segment_index_from_position(gCameraObject->trans.x_position, racer->oy1,
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
            counter = racer->checkpoint - 1;
            if (counter < 0) {
                counter += temp_v0;
            }
            temp_v0_4 = get_checkpoint_node(counter);
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
            if (racer->unk1FC < 200 && racer->velocity <= -1.0) {
                racer->unk1FC += updateRate;
            }
        } else {
            racer->unk1FC = 0;
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

#ifdef NON_EQUIVALENT
// timetrial_ghost_read
s32 set_ghost_position_and_rotation(Object *obj) {
    f32 vectorX[3];
    f32 vectorY[3];
    f32 vectorZ[3];
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
    s32 rot;
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

    // This whole loop is a bit of a mystery still... The i < 4 is a complete guess...
    for (i = 0; i < 3; i++) {
        if (nodeIndex == -1) {
            vectorX[i] = ((curGhostNode + 1)->x * 2) - (curGhostNode + 2)->x;
            vectorY[i] = ((curGhostNode + 1)->y * 2) - (curGhostNode + 2)->y;
            vectorZ[i] = ((curGhostNode + 1)->z * 2) - (curGhostNode + 2)->z;
        } else if (nodeIndex >= ghostNodeCount) {
            vectorX[i] = (curGhostNode->x * 2) - (curGhostNode - 1)->x;
            vectorY[i] = (curGhostNode->y * 2) - (curGhostNode - 1)->y;
            vectorZ[i] = (curGhostNode->z * 2) - (curGhostNode - 1)->z;
        } else {
            vectorX[i] = curGhostNode->x;
            vectorY[i] = curGhostNode->y;
            vectorZ[i] = curGhostNode->z;
        }
        nodeIndex++;
        curGhostNode++;
    }

    catmullX = commonUnk0f32 - commonUnk0s32;
    obj->segment.trans.x_position = catmull_rom_interpolation(vectorX, 0, catmullX);
    obj->segment.trans.y_position = catmull_rom_interpolation(vectorY, 0, catmullX);
    obj->segment.trans.z_position = catmull_rom_interpolation(vectorZ, 0, catmullX);

    curGhostNode = &ghostData[commonUnk0s32];

    // Y Rotation
    rot = curGhostNode->yRotation;
    nextGhostNode = curGhostNode + 1;
    rotDiff = nextGhostNode->yRotation - (rot & 0xFFFF);
    if (rotDiff > 0x8000) {
        rotDiff -= 0xFFFF;
    }
    if (rotDiff < -0x8000) {
        rotDiff += 0xFFFF;
    }
    obj->segment.trans.rotation.y_rotation = rot + (s32) (rotDiff * catmullX);

    // X Rotation
    rot = curGhostNode->xRotation;
    nextGhostNode = curGhostNode + 1;
    rotDiff = nextGhostNode->xRotation - (rot & 0xFFFF);
    if (rotDiff > 0x8000) {
        rotDiff -= 0xFFFF;
    }
    if (rotDiff < -0x8000) {
        rotDiff += 0xFFFF;
    }
    obj->segment.trans.rotation.x_rotation = rot + (s32) (rotDiff * catmullX);

    // Z Rotation
    rot = curGhostNode->zRotation;
    nextGhostNode = curGhostNode + 1;
    rotDiff = nextGhostNode->zRotation - (rot & 0xFFFF);
    if (rotDiff > 0x8000) {
        rotDiff -= 0xFFFF;
    }
    if (rotDiff < -0x8000) {
        rotDiff += 0xFFFF;
    }
    obj->segment.trans.rotation.z_rotation = rot + (s32) (rotDiff * catmullX);

    obj->particleEmitFlags = OBJ_EMIT_OFF;
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
    struct Object_Exit *exit;
    f32 updateRateF;
    s32 angle;

    exit = (struct Object_Exit *) racer->exitObj->unk64;
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
        racer->unk1C6 = get_random_number_from_range(-60, 60) + 120;
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
            sound_stop(racer->magnetSoundMask);
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
                update_spatial_audio_position(racer->shieldSoundMask, obj->segment.trans.x_position,
                                              obj->segment.trans.y_position, obj->segment.trans.z_position);
            } else if (racer->vehicleSound) {
                play_sound_at_position(SOUND_SHIELD, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                       obj->segment.trans.z_position, 1, &racer->shieldSoundMask);
            }
        } else {
            if (racer->shieldSoundMask) {
                func_800096F8(racer->shieldSoundMask);
                racer->shieldSoundMask = NULL;
            }
        }
        racer->shieldTimer -= updateRate;
        if (racer->shieldTimer <= 0) {
            racer->shieldType = 0;
        }
    }
    if (racer->soundMask != NULL) {
        update_spatial_audio_position(racer->soundMask, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                      obj->segment.trans.z_position);
    }
    gRacerInputBlocked = FALSE;
    if ((racer->unk150 != NULL) && (gRaceStartTimer == 0)) {
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
    obj->particleEmitFlags = OBJ_EMIT_OFF;
    func_800AF714(obj, updateRate);
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
