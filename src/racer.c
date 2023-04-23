/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80042D20 */

#include "racer.h"
#include "memory.h"
#include "menu.h"
#include "video.h"

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "asset_enums.h"
#include "save_data.h"
#include "unknown_008C40.h"
#include "objects.h"
#include "audio.h"
#include "object_functions.h"
#include "game.h"
#include "printf.h"
#include "math_util.h"
#include "unknown_0255E0.h"
#include "weather.h"
#include "vehicle_misc.h"
#include "unknown_005740.h"
#include "game_ui.h"
#include "object_models.h"
#include "audiosfx.h"
#include "collision.h"
#include "controller.h"
#include "particles.h"


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
    -10.0f, 5.0f, 0.0f, 0.0f,
    10.0f, 5.0f, 0.0f, 0.0f,
    -10.0f, 10.0f, 0.0f, 0.0f,
    10.0f, 10.0f,
};

s32 gNumViewports = 0; // Currently unknown, might be a different type.
// Table used for quantifying speed reduction while the car drives over it, like how grass will slow you down more than the road.
// An antipiracy trigger can set the first index to 0.5f, which makes that surface type impossible to drive on.
f32 gSurfaceTractionTable[19] = {
    0.004f, 0.007f, 0.01f, 0.004f,
    0.01f, 0.01f, 0.01f, 0.01f,
    0.01f, 0.01f, 0.004f, 0.004f,
    0.004f, 0.004f, 0.004f, 0.004f,
    0.004f, 0.004f, 0.004f,
};
// Can only assume this is surface related too. Not incline thresholds though.
f32 D_800DCBE8[19] = {
    0.8f, 0.85f, 0.85f, 0.5f,
    0.5f, 0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f, 0.8f,
    0.8f, 0.84f, 0.8f, 0.8f,
    0.8f, 0.8f, 0.8f,
};
// When driving over this surface, the car begins to bob up and down to give the effect of roughness.
s32 gSurfaceBobbingTable[19] = {
    0, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};
// When landing on this surface, it makes a sound.
// Strangely, they did only two surface types then called it a day.
s32 gSurfaceSoundTable[13] = {
    SOUND_NONE, SOUND_LAND_GRASS, SOUND_LAND_SAND, SOUND_NONE, 
    SOUND_NONE, SOUND_NONE, SOUND_NONE, SOUND_NONE,
    SOUND_NONE, SOUND_NONE, SOUND_NONE, SOUND_NONE, 
    SOUND_NONE
};

// Unused?
s16 D_800DCCB4[12] = {
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

u16 D_800DCCCC[20] = {
    0x010C, 0x010B, 0x0009, 0x010C,
    0x010C, 0x010C, 0x010C, 0x010C,
    0x010C, 0x010C, 0x010C, 0x0005,
    0x010C, 0x010C, 0x010C, 0x010C,
    0x010C, 0x010C, 0x010C, 0x0000,
};

s32 gSurfaceFlagTable[19] = {
    1, 4, 0x10, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0x100, 1, 1, 1, 1, 1,
};

s32 gSurfaceFlagTable4P[20] = {
    0, 4, 16, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0x100, 0, 0, 0, 0,
    0, 0,
};

// Used to know how the AI should use a balloon when they have one.
s8 gRacerAIBalloonActionTable[NUM_WEAPON_TYPES - 1] = {
    1, 1, 2, 2, 4, 3, 0, 6,
    4, 3, 2, 2, 5, 5, 5,
};

// Unused?
s8 D_800DCDA0[8] = {
    0, 0, 0, 1, 1, 2, 2, 2,
};

s8 D_800DCDA8[8] = {
    1, 1, 1, 2, 3, 2, 3, 2,
};

s8 D_800DCDB0[16][2] = {
    {0x02,0xFE}, 
    {0x03, 0xFE}, 
    {0x02, 0xFC}, 
    {0x02, 0xFB},
    {0x02, 0xFB}, 
    {0x02, 0xFE}, 
    {0x02, 0xFD}, 
    {0x02, 0xFE},
    {0x03, 0xFD}, 
    {0x05, 0xFC}, 
    {0x04, 0xFE}, 
    {0x02, 0xFE},
    {0x02, 0xFA}, 
    {0x02, 0xFE}, 
    {0x08, 0xF8}, 
    {0x03, 0xFD},
};

// Checksum count for obj_loop_goldenballoon
s32 gObjLoopGoldenBalloonChecksum = 0xA597;

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
s32 D_8011D53C; // Set to 0 and only 0. Checked for being 1, but never true.
s32 gRaceStartTimer;
f32 D_8011D544; // Starts are 300, then counts down when the race starts. Usage currently unknown.
f32 D_8011D548;
f32 D_8011D54C;
s16 D_8011D550;
s8 D_8011D552;
s8 D_8011D553;
s32 gCurrentCarSteerVel;
s32 D_8011D558;
s32 gCurrentPlayerIndex;
s16 D_8011D560; // Set, but never read.
UNUSED s16 D_8011D562;
f32 *gCurrentRacerMiscAssetPtr;
f32 *D_8011D568;
f32 gCurrentRacerWeightStat;
f32 gCurrentRacerHandlingStat;
f32 D_8011D574;
f32 gRacerMagnetVelX;
f32 gRacerMagnetVelZ;
u8 D_8011D580;
s8 gCurrentSurfaceType;
s8 D_8011D582;
s8 D_8011D583;
s8 D_8011D584;
s8 gStartBoostTime;
s16 gDialogueCameraAngle;
s8 D_8011D588[4];
s8 D_8011D58C[4];
GhostHeader *gGhostData[3];
s8 D_8011D59C;
s8 D_8011D59D;
s16 D_8011D59E;
s16 D_8011D5A0[2];
s16 gTTGhostNodeCount; // Gets assigned, but never used?
s16 D_8011D5A8[2];
s16 D_8011D5AC;
s8 D_8011D5AE;
s8 D_8011D5AF;
struct TempStruct8 **D_8011D5B0;
s32 D_8011D5B4;
s16 D_8011D5B8;

/******************************/

#ifdef NON_MATCHING
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
    TempStruct5 *sp54;
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
    miscAsset1 = (s8 *) get_misc_asset(MISC_ASSET_UNK01);
    miscAsset2 = (s8 *) get_misc_asset(MISC_ASSET_UNK02);
    header = get_current_level_header();
    racerGroup = get_racer_objects_by_position(&numRacers);
    sp54 = func_8006C18C();
    if (racer->unk1C6 > 0) {
        racer->unk1C6 -= updateRate;
    } else {
        racer->unk1C6 = 0;
    }
    if (func_8001AE44() != 0) {
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
                                func_8005CA84(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 5);
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
                                func_8005CA84(obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 3);
                            }
                        }
                    }
                }
            }
            racer->unk20B = racerID;
            sp5C = NULL;
            sp94 = 0.0f;
            sp90 = 0.0f;
            temp_v0_3 = func_8001B7A8((Object *) racer, 1, &sp94);
            if (temp_v0_3 != NULL) {
                sp5C = temp_v0_3->unk64;
            }
            sp58 = NULL;
            temp_v0_3 = func_8001B7A8((Object *) racer, -1, &sp90);
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
                racer->unk1CA = D_800DCDA0[racer->unk1AE];
            }
            if ((f32) (s16) ((racer->aiSkill - 2) << 2) <= 300.0f - D_8011D544) {
                gCurrentRacerInput |= A_BUTTON;
            }
            miscAsset4 = (u8 *) get_misc_asset(MISC_ASSET_UNK0C);
            if (racer->balloon_level < 3) {
                balloonType = miscAsset4[racer->balloon_type * 3 + racer->balloon_level];
            } else {
                balloonType = racer->balloon_type;
            }
            sp38 = (((sp54->unk8[1][1] - sp54->unk8[1][0]) * (7 - var_t5)) / 7) + sp54->unk8[1][0];
            sp36 = (((sp54->unk8[2][1] - sp54->unk8[2][0]) * (7 - var_t5)) / 7) + sp54->unk8[2][0];
            sp3A = (((sp54->unk8[0][1] - sp54->unk8[0][0]) * (7 - var_t5)) / 7) + sp54->unk8[0][0];
            sp3C = (((sp54->unk8[3][1] - sp54->unk8[3][0]) * (7 - var_t5)) / 7) + sp54->unk8[3][0];
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
                racer->unk209 &= (0x8000 | 0x4000 | 0x2000 | 0x1000 | 0x800 | 0x400 | 0x200 | 0x100 | 0x80 | 0x40 | 0x20 | 0x10 | 0x8 | 0x4 | 0x2);
            }
            if (racer->boostTimer != 0) {
                if (!(racer->unk209 & 2)) {
                    if (roll_percent_chance(sp3A)) {
                        racer->unk209 |= 4;
                    }
                    racer->unk209 |= 2;
                }
                if (racer->unk209 & 4) {
                    gCurrentRacerInput &= 0xFFFF7FFF;
                }
            } else {
                racer->unk209 &= ~2;
                if (racer->velocity > -12.0) {
                    racer->unk209 = (u16) (racer->unk209 & 0xFFFB);
                }
            }
            if (racer->unk209 & 4) {
                gCurrentRacerInput &= 0xFFFF7FFF;
            }
            if (racer->unk1C6 == 0) {
                if (racer->unk1C9 == 4 || racer->unk1C9 == 5) {
                    gCurrentButtonsReleased |= Z_TRIG;
                }
                racer->unk1C9 = 0;
                if (sp58 != NULL && sp58->racer.playerIndex != PLAYER_COMPUTER && sp90 < 200.0f && var_t5 != 0 && var_t4 < 3 && miscAsset1[racer->characterId + (sp3F * 10)] < 5) {
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
                    gCurrentRacerInput &= 0xFFFF7FFF;
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
GLOBAL_ASM("asm/non_matchings/racer/func_80042D20.s")
#endif

void func_80043ECC(Object *obj, Object_Racer *racer, s32 updateRate) {
    TempStruct5 *temp_v0;
    s8 *test;
    s8 phi_a0;
    s32 i;
    static s8 D_8011D5BA;
    static s8 D_8011D5BB;
    static s8 D_8011D5BC;

    if (!obj) {
        D_8011D5BA = 0;
        D_8011D5BB = 0;
        D_8011D5BC = 0;
        return;
    }
    temp_v0 = func_8006C18C();
    if (racer->boostTimer) {
        if (!D_8011D5BB) {
            temp_v0->unk8[3][0] += temp_v0->unk8[3][2];
            temp_v0->unk8[3][1] += temp_v0->unk8[3][3];
            D_8011D5BB = 1;
        }
        if (!(gCurrentRacerInput & A_BUTTON)) {
            D_8011D5BA += updateRate;
        }
    } else {
        D_8011D5BB = 0;
        if (D_8011D5BA > 20) {
            temp_v0->unk8[0][0] += temp_v0->unk8[0][2];
            temp_v0->unk8[0][1] += temp_v0->unk8[0][3];
        }
        D_8011D5BA = 0;
    }
    if (racer->balloon_quantity) {
        if (D_8011D5BC < racer->balloon_level) {
            temp_v0->unk8[1][0] += temp_v0->unk8[1][2];
            temp_v0->unk8[1][1] += temp_v0->unk8[1][3];
        }
        D_8011D5BC = racer->balloon_level;
    } else {
        D_8011D5BC = 0;
    }
    test = (s8 *) get_misc_asset(MISC_ASSET_UNK0C);
    if ((gCurrentButtonsReleased & Z_TRIG) && racer->balloon_quantity) {
        if (racer->balloon_level < 3) {
            phi_a0 = test[racer->balloon_type * 3 + racer->balloon_level];
        } else {
            phi_a0 = racer->balloon_type;
        }
        if (gRacerAIBalloonActionTable[phi_a0] == 1) {
            temp_v0->unk8[2][0] += temp_v0->unk8[2][2];
            temp_v0->unk8[2][1] += temp_v0->unk8[2][3];
        }
    }
    for (i = 0; i < 2; i++) {
        if (temp_v0->unk8[1][i] > 100 || temp_v0->unk8[1][i] < 0) {
            temp_v0->unk8[1][i] = 100;
        }
        if (temp_v0->unk8[0][i]  > 100 || temp_v0->unk8[0][i] < 0) {
            temp_v0->unk8[0][i]  = 100;
        }
        if (temp_v0->unk8[3][i] > 100 || temp_v0->unk8[3][i] < 0) {
            temp_v0->unk8[3][i] = 100;
        }
        if (temp_v0->unk8[2][i] > 100 || temp_v0->unk8[2][i] < 0) {
            temp_v0->unk8[2][i] = 100;
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

    if (racer->velocity > -1.0 && racer->unk214 == 0 && !gRaceStartTimer && D_8011D544 == 0.0f && racer->unk1E2 && racer->unk215 == 0) {
        racer->unk213 += updateRate;

        if (racer->unk213 > 60) {
            racer->unk213 = 0;
            racer->unk214 = 60;
            racer->unk215 = 120;

            if (!(raceType & RACETYPE_CHALLENGE)) {
                racer->unk1CA = (racer->unk1CA + 1) & 3;
            } else if (raceType == RACETYPE_CHALLENGE_BATTLE || raceType == RACETYPE_CHALLENGE_BANANAS) {
                if (racer->unk1CE != 0xFF) {
                    racer->unk154 = func_8001D214(racer->unk1CE);
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

GLOBAL_ASM("asm/non_matchings/racer/func_8004447C.s")

// Still don't know what this really is.
struct TempStruct2 {
    Object *unk0[4];
    u8 pad10[0x1BF];
    s32 unk1CF;
};

void func_80045128(struct TempStruct2 *header) {
    Object_Racer *obj;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = (Object_Racer *) header->unk0[i]->unk64;
        D_8011D588[i] = obj->lap;
        if (obj->unk1CF != 0) {
            D_8011D588[i] |= 0x40;
        }
        if (obj->held_obj != 0) {
            D_8011D588[i] |= 0x80;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/racer/func_800452A0.s")
GLOBAL_ASM("asm/non_matchings/racer/func_80045C48.s")

#ifdef NON_EQUIVALENT
void func_80046524(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer) {
    UNUSED s32 temp2;
    UNUSED s32 pad0;
    f32 sp11C;
    f32 sp118;
    f32 var_f14;
    f32 sp108;
    f32 sp10C;
    f32 sp110;
    f32 var_f18;
    f32 var_f12;
    f32 spFC;
    f32 temp_f2;
    f32 spF4;
    f32 spF0;
    f32 var_f16;
    f32 spE4;
    f32 spE8;
    UNUSED s32 temp3;
    f32 var_f2;
    UNUSED f32 *pad3;
    Vec3f *spD4;
    f32 temp_f0;
    s32 var_v0;
    f32 spC8;
    s32 i;
    s32 var_a3;
    s32 var_v1;
    Unknown80046524 *temp_v0_16;
    UNUSED s32 var_t0;
    Asset20 *asset20;
    s8 var_t1;
    s8 temp_v0_10;
    s8 var_a3_2;
    f32 temp;
    Matrix sp68;
    s8 sp67;
    UNUSED s32 prevUnk1D2;
    UNUSED s32 var_t0_3;
    float new_var;
    if (func_8000E138() != 0) {
        updateRateF *= 1.15;
    }
    sp67 = 0;
    if (racer->playerIndex >= 0) {
        if (gNumViewports < 2) {
        obj->unk74 |= 0x100;
        }
    }
    D_8011D550 = 0;
    gCurrentCarSteerVel = 0;
    D_8011D558 = 0;
    sp108 = obj->segment.trans.x_position;
    sp10C = obj->segment.trans.y_position;
    sp110 = obj->segment.trans.z_position;
    spC8 = 1.0 - (gDialogueCameraAngle / 10240.0f);
    spE4 = ((-racer->ox1) * 10) * spC8;
    spE8 = ((-racer->oz1) * 10) * spC8;
    var_f2 = 8.0f;
    if ((gCurrentPlayerIndex == (-1)) || (racer->raceFinished != 0)) {
        var_f2 = 32.0f;
    }
    var_v1 = gCurrentStickX - racer->steerAngle;
    var_a3 = (var_v1 * updateRateF) / var_f2;
    if (var_v1 != 0) {
        if (var_a3 == 0) {
        if (var_v1 > 0) {
            var_a3 = 1;
        }
        if (var_v1 < 0) {
            var_a3 = -1;
        }
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
    if (gCurrentRacerInput & 0x8000) {
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
    if ((racer->velocity > 0.0f) && (gCurrentRacerInput & 0x8000)) {
        sp11C = 1.0f;
    }
    sp11C = sp11C * 3.0f;
    spF4 = (sp11C * sp11C) / 9.0f;
    if (racer->unk108 != 0) {
        racer->throttle = 0.5f;
    }
    if (racer->velocity > 0.0) {
        spF4 *= 1.2;
    }
    if ((gCurrentRacerInput & 0x4000) && ((gCurrentStickY < (-40)) || (racer->velocity < 0.0f))) {
        racer->brake += updateRateF * 0.046;
        if (racer->brake > 1.2) {
        racer->brake = 1.2f;
        }
        if (racer->velocity < (-2.0)) {
        func_80072348(racer->playerIndex, 5);
        }
    } else {
        racer->brake -= updateRateF * 0.046;
        if (racer->brake < 0.0f) {
        racer->brake = 0.0f;
        }
    }
    sp11C = racer->brake * 3.0f;
    spF0 = (sp11C * sp11C) / 9.0f;
    if (racer->velocity > 0.0) {
        spF0 *= 0.3;
    }


        // Fake, fixes f12 & f14 swap.
        if (1) { } if (1) { } if (1) { } if (1) { } if (1) { } 
        
        
    if (racer->unk1F5 != 0) {
        gCurrentStickX = 0;
        racer->magnetTimer = 0;
        racer->steerAngle = 0;
        racer->spinout_timer = 0;
        racer->unk1E0 = 0;
        var_v1 = racer->unk14C->segment.trans.y_rotation - (racer->steerVisualRotation & 0xFFFF);
        if (var_v1 > 0x8000) {
        var_v1 -= 0xFFFF;
        }
        if (var_v1 < (-0x8000)) {
        var_v1 += 0xFFFF;
        }
        racer->steerVisualRotation += (var_v1 * updateRate) >> 3;
        if (((var_v1 < 0x400) && (var_v1 > (-0x400))) || (racer->playerIndex == PLAYER_COMPUTER)) {
        if (racer->playerIndex != PLAYER_COMPUTER) {
            play_sound_spatial(0x107U, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 0);
            play_random_character_voice(obj, 0x162, 8, 0x82);
        }
        racer->boostTimer = normalise_time(45);
        racer->boostType = BOOST_LARGE;
        if (racer->throttleReleased) {
            racer->boostType |= BOOST_SMALL_FAST;
        }
        racer->unk1F5 = 0;
        func_80072348(racer->playerIndex, 8U);
        } else {
        obj->segment.x_velocity = ((f64) obj->segment.x_velocity) * 0.75f;
        obj->segment.y_velocity = ((f64) obj->segment.y_velocity) * 0.75f;
        obj->segment.z_velocity = ((f64) obj->segment.z_velocity) * 0.75f;
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
    if ((racer->unk1D4 != 0) || (racer->unk1D5 != 0)) {
        apply_vehicle_rotation_offset(racer, updateRate, racer->y_rotation_offset, 0, 0);
    } else {
        apply_vehicle_rotation_offset(racer, updateRate, 0, (spF0 * 4096.0f) * var_f2, 0);
    }
    if (racer->unk1D5 != 0) {
        racer->y_rotation_offset -= racer->y_rotation_offset >> 3;
        if ((racer->y_rotation_offset < 16) && (racer->y_rotation_offset > (-16))) {
        racer->unk1D5 = 0;
        }
        gCurrentStickX = 0;
    }
    if (racer->spinout_timer > 0) {
        racer->unk1D4 += updateRate;
        if (racer->unk1D4 > 10) {
        racer->unk1D4 = 10;
        }
    }
    else
        if (racer->spinout_timer < 0) {
        racer->unk1D4 -= updateRate;
        if (racer->unk1D4 < (-10)) {
        racer->unk1D4 = -10;
        }
    }
    else
        if (racer->unk1D4 < 0) {
        racer->unk1D4 += updateRate;
        if (racer->unk1D4 > 0) {
        racer->unk1D4 = 0;
        racer->unk1D5 = 1;
        }
    }
    else
        if (racer->unk1D4 > 0) {
        racer->unk1D4 -= updateRate; 
        if (racer->unk1D4 < 0) {
        racer->unk1D4 = 0;
        racer->unk1D5 = 1;
        }
    }
    if ((racer->unk1E2 != 0) && (racer->unk1E2 < 3)) {
        obj->segment.trans.x_rotation -= (obj->segment.trans.x_rotation * updateRate) >> 6;
        racer->x_rotation_vel -= (racer->x_rotation_vel * updateRate) >> 6;
    }
    
    if (racer->unk1D4 != 0) {
        i = racer->y_rotation_offset;
        racer->unk1D5 = 0;
        if (racer->unk1D4 > 0) {
        racer->y_rotation_offset += (racer->unk1D4 * 0xB3) * updateRate;
        if ((i < (-0x1000)) && (racer->y_rotation_offset >= (-0x1000))) {
            racer->spinout_timer--;
        }
        }
        if (racer->unk1D4 < 0) {
        racer->y_rotation_offset -= (racer->unk1D4 * 0xB3) * updateRate;
        if ((i > 0x1000) && (racer->y_rotation_offset <= 0x1000)) {
            racer->spinout_timer++;
        }
        }
        gCurrentRacerInput &= 0xFFFF3FFF;
        gCurrentStickX = 0;
        racer->steerAngle = 0;
        gCurrentStickY = 0;
    }
    if (racer->unk1F1 != 0) {
        racer->y_rotation_offset += updateRate * 0x500;
        racer->x_rotation_offset += updateRate * 0x600;
    }
    gCurrentRacerTransform.y_rotation = obj->segment.trans.y_rotation;
    gCurrentRacerTransform.x_rotation = obj->segment.trans.x_rotation;
    gCurrentRacerTransform.z_rotation = 0;
    gCurrentRacerTransform.x_position = 0.0f;
    gCurrentRacerTransform.y_position = 0.0f;
    gCurrentRacerTransform.z_position = 0.0f;
    gCurrentRacerTransform.scale = 1.0f;
    object_transform_to_matrix((f32 (*)[4]) sp68, &gCurrentRacerTransform);
    guMtxXFMF(sp68, 0.0f, 0.0f, 1.0f, &racer->ox1, &racer->oy1, &racer->oz1);
    guMtxXFMF(sp68, 0.0f, 1.0f, 0.0f, &racer->ox2, &racer->oy2, &racer->oz2);
    guMtxXFMF(sp68, 1.0f, 0.0f, 0.0f, &racer->ox3, &racer->oy3, &racer->oz3);
    if (racer->approachTarget == 0) {
        obj->segment.unk38.byte.unk3B = 0;
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
    var_f18 = racer->velocity;
    if (var_f18 < 0.0f) {
        var_f18 = -var_f18;
    }
    var_t1 = 0;
    var_a3_2 = 0;
    if (var_f18 > 12.0f) {
        var_f18 = 12.0f;
    }
    var_a3 = var_f18;
    temp_f0 = var_f18 - var_a3;
    var_f18 = (gCurrentRacerMiscAssetPtr[var_a3] * (1.0 - temp_f0)) + (gCurrentRacerMiscAssetPtr[var_a3 + 1] * temp_f0);
    gCurrentRacerWeightStat *= 0.75;
    if (racer->unk1E2 >= 3) {
        obj->segment.y_velocity -= (gCurrentRacerWeightStat * 0.5) * updateRateF;
    } else {
        obj->segment.y_velocity -= gCurrentRacerWeightStat * updateRateF;
    }
    i = ((gCurrentPlayerIndex != PLAYER_COMPUTER) && (!racer->raceFinished)) ? racer->steerAngle : gCurrentStickX;
    spFC = 0.004f;
    obj->segment.y_velocity -= (obj->segment.y_velocity * 0.004) * updateRateF;
    if ((gCurrentRacerInput & 0x4000) && (gCurrentStickY >= (-40)) && (racer->velocity >= (-0.5))) {
        spFC *= 16.0f;
    }
    var_f14 = (i * 8) * updateRate;
    if (gCurrentStickY < 0) {
        var_f2 = (f32) (-gCurrentStickY);
        sp11C = var_f2;
        var_f14 *= 1.0 + (sp11C / 112.0);
        var_f18 *= 1.0 - (sp11C / 300.0);
    }
    racer->steerVisualRotation -= (s32) (var_f14 * gCurrentRacerHandlingStat);
    if ((racer->unk1E2 == 0) && (racer->buoyancy == 0.0)) {
        if (obj->segment.y_velocity < 0.0f) {
        racer->unk1E0 += updateRate;
        }
        if (racer->unk1E0 > 25) {
        racer->unk1E0 = 25;
        }
    }
    for (i = 0; i < 4; i++) {
        if (racer->wheel_surfaces[i] == 0xFF) {
        continue;
        }
        if (var_t1 < racer->wheel_surfaces[i]) {
        var_t1 = racer->wheel_surfaces[i];
        }
        if (racer->wheel_surfaces[i] == 4) {
        var_a3_2 += 1;
        }
    }

    if ((((racer->playerIndex == PLAYER_ONE) && (racer->unk1E2 != 0)) && (var_t1 == 12)) && (gCurrentButtonsPressed & 0x2000)) {
        D_8011D582 = 2;
    }
    if ((racer->unk1E2 != 0) || (racer->buoyancy > 0.0f)) {
        if (racer->unk1E0 != 0) {
        if (racer->unk1E2 != 0) {
            if (((gRaceStartTimer != 100) && (racer->playerIndex != PLAYER_COMPUTER)) && (racer->unk1E0 >= 6)) {
            play_sound_global(0xAEU, &racer->unk21C);
            func_80001FB8(0xAEU, (void *) racer->unk21C, (racer->unk1E0 * 2) + 0x32);
            }
        }
        else
            if (racer->approachTarget == 0) {
            racer_play_sound(obj, 0xAF);
            obj->unk74 |= 0x30;
        }
        temp_f2 = racer->unk1E0 - 5.0f;
        if ((temp_f2 > 0.0f) && (racer->approachTarget == 0)) {
            racer->stretch_height_cap = 1.0 - (temp_f2 * 0.02);
        }
        racer->unk1E0 = 0;
        }
    }
    var_f18 = var_f18 * (handle_racer_top_speed(obj, racer) * 1.7);
    if (racer->boostTimer > 0) {
        if (gRaceStartTimer == 0) {
        spF4 = 1.0f;
        spF0 = 0.0f;
        if (var_f18 != 0.0) {
            var_f18 = 2.0f;
        }
        racer->boostTimer -= updateRate;
        }
    } else {
        racer->boostTimer = 0;
    }
    if (gRaceStartTimer != 0) {
        var_f18 = 0.0f;
    }
    if (var_a3_2 != 0) {
        temp_f0 = ((f32 *) get_misc_asset(0x20))[var_a3_2];
        var_f18 *= temp_f0;
        spFC /= temp_f0;
        racer->magnetTimer = 0;
        racer->lateral_velocity = 0.0f;
    }
    if ((racer->boostTimer == 0) && (var_t1 == 3)) {
        racer->boostTimer = normalise_time(45);
        racer->boostType = BOOST_LARGE;
        if (racer->throttleReleased) {
        racer->boostType |= BOOST_SMALL_FAST;
        }
        racer_play_sound(obj, 0x107);
        play_random_character_voice(obj, 0x162, 8, 0x82);
        func_80072348(racer->playerIndex, 8U);
    }
    temp_f0 = sqrtf((obj->segment.z_velocity * obj->segment.z_velocity) + (obj->segment.x_velocity * obj->segment.x_velocity));
    if (temp_f0 > 0.25) {
        racer->unk168 = arctan2_f(obj->segment.x_velocity, obj->segment.z_velocity) + 0x8000;
        var_v1 = ((0x8000 - racer->unk168) & 0xFFFF) - (racer->unk196 & 0xFFFF);
        if (var_v1 > 0x8000) {
        var_v1 -= 0xFFFF;
        }
        if (var_v1 < (-0x8000)) {
        var_v1 += 0xFFFF;
        }
        sp11C = temp_f0 - 0.25;
        if (sp11C > 8.0) {
        sp11C = 8.0f;
        }
        sp11C *= 0.125;
        racer->unk196 += (((s32) ((var_v1 * ((f32) sp11C)) * 0.75)) * updateRate) >> 4;
        var_v1 = (0x8000 - racer->unk196) - (racer->steerVisualRotation & 0xFFFF);
        if (var_v1 > 0x8000) {
        var_v1 -= 0xFFFF;
        }
        if (var_v1 < (-0x8000)) {
        var_v1 += 0xFFFF;
        }
        if (temp_f0 > 10.0) {
        temp_f0 = 10.0;
        }
        var_v1 = var_v1 * ((f32) (temp_f0 / 10.0));
        if ((gCurrentRacerInput & 0x8000) || (gCurrentRacerInput & 0x0010)) {
        var_v1 *= 2;
        }
        racer->steerVisualRotation += ((s32) (var_v1 * updateRate)) >> 7;
    }
    var_v1 = (0x8000 - racer->steerVisualRotation) - (racer->unk196 & 0xFFFF);
    if (var_v1 > 0x8000) {
        var_v1 -= 0xFFFF;
    }
    if (var_v1 < (-0x8000)) {
        var_v1 += 0xFFFF;
    }
    temp = 1.0f;
    racer->unk196 += (((s32) ((((f32) var_v1) * 1.75) * temp)) * updateRate) >> 6;
    if (racer->unk1F5 == 0) {
        if ((gCurrentPlayerIndex == PLAYER_COMPUTER) && (racer->raceFinished == 0)) {
        var_f16 = racer->lateral_velocity * 0.25;
        temp_f0 = var_f16 * 0.35;
        if (temp_f0 < 0.0) {
            temp_f0 = -temp_f0;
        }
        if (0.2 < temp_f0) {
            gCurrentRacerInput |= 0x0010;
        }
        obj->segment.x_velocity += racer->ox1 * temp_f0;
        obj->segment.y_velocity += racer->oy1 * temp_f0;
        obj->segment.z_velocity += racer->oz1 * temp_f0;
        } else {
        var_f16 = racer->lateral_velocity * 0.07;
        if (gCurrentRacerInput & 0x0010) {
            var_f16 *= 2;
            if ((gCurrentStickX > (-40)) && (gCurrentStickX < 40)) {
            spF4 *= 0.8;
            }
            else
            if ((racer->lateral_velocity > 2.5) || (racer->lateral_velocity < (-2.5))) {
            spF4 *= 1.5;
            }
            if (gCurrentRacerInput & 0x4000) {
            var_f16 *= 2;
            }
        }
        if (gCurrentRacerInput & 0x4000) {}
        }
        obj->segment.x_velocity -= racer->ox3 * var_f16;
        obj->segment.y_velocity -= racer->oy3 * var_f16;
        obj->segment.z_velocity -= racer->oz3 * var_f16;
        spF4 *= var_f18;
        obj->segment.x_velocity -= racer->ox1 * spF4;
        obj->segment.y_velocity -= racer->oy1 * spF4;
        obj->segment.z_velocity -= racer->oz1 * spF4;
        spF0 *= var_f18 / 2;
        obj->segment.x_velocity += racer->ox1 * spF0;
        obj->segment.y_velocity += racer->oy1 * spF0;
        obj->segment.z_velocity += racer->oz1 * spF0;
        if (((racer->unk1E2 != 0) && (D_8011D584 == 0)) && (gRaceStartTimer == 0)) {
        temp_f2 = (gCurrentRacerWeightStat * updateRateF) * 0.25;
        sp11C = racer->pitch * temp_f2;
        temp_f2 = temp_f2 * racer->roll;
        obj->segment.x_velocity += (racer->ox1 * sp11C) + (racer->ox3 * temp_f2);
        obj->segment.y_velocity += (racer->oy1 * sp11C) + (racer->oy3 * temp_f2);
        obj->segment.z_velocity += (racer->oz1 * sp11C) + (racer->oz3 * temp_f2);
        }
        var_f12 = racer->velocity * racer->velocity;
        if (racer->velocity < 0.0f) {
        var_f12 = -var_f12;
        }
        if ((var_f12 < 1.0f) && (!(gCurrentRacerInput & 0x8000))) {
        var_f16 = (racer->velocity * spFC) * 8.0f;
        } else {
        var_f16 = var_f12 * spFC;
        }
        obj->segment.x_velocity -= racer->ox1 * var_f16;
        obj->segment.y_velocity -= racer->oy1 * var_f16;
        obj->segment.z_velocity -= racer->oz1 * var_f16;
        if (racer->magnetTimer != 0) {
        obj->segment.x_velocity = gRacerMagnetVelX;
        obj->segment.z_velocity = gRacerMagnetVelZ;
        }
    }
    racer->unk10C = 0;
    racer->y_rotation_vel += (gCurrentCarSteerVel - racer->y_rotation_vel) >> 3;
    obj->segment.trans.y_rotation = racer->steerVisualRotation + racer->y_rotation_vel;
    racer->z_rotation_vel += (D_8011D558 - racer->z_rotation_vel) >> 3;
    obj->segment.trans.z_rotation = racer->x_rotation_vel + racer->z_rotation_vel;
    if (racer->unk1D2 > 0) {
        racer->unk1D2 -= updateRate;
    } else {
        racer->unk1D2 = 0;
    }
    var_f12 = 10.0;
    spE4 += (racer->ox1 * var_f12) * spC8;
    spE8 += (racer->oz1 * var_f12) * spC8;
    if (racer->approachTarget == 0) {
        var_f16 = obj->segment.x_velocity;
        var_f12 = obj->segment.z_velocity;
        if (racer->unk1D2 != 0) {
        var_f16 += racer->unk11C;
        var_f12 += racer->unk120;
        }
        if (D_8011D584 != 0) {
        if ((var_f16 > 0.5) || (var_f16 < (-0.5))) {
            var_f16 *= 0.65;
        } else {
            var_f16 = 0.0f;
        }
        if ((var_f12 > 0.5) || (var_f12 < (-0.5))) {
            var_f12 *= 0.65;
        } else {
            var_f12 = 0.0f;
        }
        } else {
        spE8 += racer->unk84 * updateRateF;
        spE4 += racer->unk88 * updateRateF;
        }
        if (move_object(obj, (var_f16 * updateRateF) + spE8, obj->segment.y_velocity * updateRateF, (var_f12 * updateRateF) + spE4) && (gCurrentPlayerIndex != (-1))) {
            sp67 = 1;
        }
    } else {
        spE4 = 0.0;
        spE8 = 0.0;
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
    var_f14 = 5.0f;
    sp118 = -10000.0f;
    temp_v0_10 = get_wave_properties(obj->segment.trans.y_position, &sp118, spD4); 
    if (temp_v0_10) {
        var_f14 = racer->velocity;
        if (var_f14 < 0.0f) {
        var_f14 = -var_f14;
        }
        if (var_f14 > 4.0) {
        var_f14 = 4.0;
        }
        var_f14 = var_f14 * 0.8;
        if ((obj->segment.trans.y_position - var_f14) < sp118) {
            racer->buoyancy = sp118 - (obj->segment.trans.y_position - var_f14);
            racer->unk1E5 = 5;
        } else {
            racer->buoyancy = 0.0f;
        }
    }
    if (racer->unk1E5 > 0) {
        racer->unk1E5--;
    } else {
        racer->buoyancy = 0.0f;
    }
    if ((racer->unk1E5 > 0) && (obj->segment.trans.y_position < (sp118 + var_f14))) {
        obj->interactObj->unk14 |= 0x10;
    } else {
        obj->interactObj->unk14 &= 0xFFEF;
    }
    sp118 = obj->segment.trans.y_position - (sp118 + var_f14);
    if (racer->buoyancy > 0.0) {
        i = 0;
        if (gCurrentRacerInput & 0x0010) {
            i = gCurrentStickX * 2;
        }
        rotate_racer_in_water(obj, racer, spD4, temp_v0_10, updateRate, i, 1.0f);
    }
    if (racer->buoyancy > 0.0) {
        obj->segment.trans.y_position += racer->buoyancy * racer->unkC4;
        racer->unkC4 += (0.75 - racer->unkC4) * 0.125;
    }
    i = racer->unk1D2;
    if (gCurrentPlayerIndex == PLAYER_COMPUTER && !func_80023568()) {
            func_80055A84(obj, racer, updateRate);
        } else {
        func_80054FD0(obj, racer, updateRate);
    }
    if ((!i) && racer->unk1D2) {
        i = 1;
    }
    racer->unk1D2 = i;
    temp_f2 = 1.0f / updateRateF;
    temp = ((obj->segment.trans.x_position - (sp108 + spE4)) - D_8011D548) * temp_f2;
    new_var = (obj->segment.trans.z_position - (sp110 + spE8)) - D_8011D54C;
    obj->segment.z_velocity = new_var * temp_f2;
    obj->segment.x_velocity = temp;
    obj->segment.y_velocity = (obj->segment.trans.y_position - sp10C) * temp_f2;
    racer->forwardVel -= (racer->forwardVel + (racer->velocity * 0.05)) * 0.125;
    if (((racer->buoyancy > 0.0) && (racer->unk1FB == 0)) && (obj->segment.y_velocity > 4.0)) {
        obj->segment.y_velocity = 4.0f;
    }
    if ((gNumViewports < 2) && (obj->segment.header->unk57 >= 9)) {
        if (((gCurrentRacerInput & (0x8000 | 0x0010)) == (0x8000 | 0x0010)) && ((gCurrentStickX < (-30)) || (gCurrentStickX > 30))) {
        func_800B4668(obj, 8, updateRate << 10, 0x80);
        } else {
        func_800B46BC(obj, 8, updateRate << 9, 0x20);
        }
    }
    if ((gCurrentPlayerIndex >= PLAYER_ONE) && (racer->buoyancy > 0.0)) {
        if (gNumViewports < 3) {
        temp_f2 = ((obj->segment.x_velocity * obj->segment.x_velocity) + (obj->segment.y_velocity * obj->segment.y_velocity)) + (obj->segment.z_velocity * obj->segment.z_velocity);
        if (temp_f2 > 16.0f) {
            if (temp_f2 < 80.0f) {
            obj->unk74 |= 0x8 | 0x4;
            }
            if (temp_f2 > 28.0f) {
            obj->unk74 |= 3;
            }
            if ((gNumViewports == 1) && (temp_f2 > 10.25f)) {
            obj->unk74 |= 0x40;
            }
        }
        } else {
        if (racer->velocity < 0.0f) {
            var_f2 = -racer->velocity;
        } else {
            var_f2 = racer->velocity;
        }
        if (var_f2 > 4.0f) {
            obj->unk74 |= 0xC;
        }
        }
    }
    if (((gCurrentPlayerIndex != PLAYER_COMPUTER) && (racer->boostTimer == 0)) && (gNumViewports < 2)) {
        asset20 = &((Asset20 *) get_misc_asset(20))[racer->unk2];
        i = ((racer->boostType & EMPOWER_BOOST) >> 2) + 10;
        if (i > 10) {
            if ((asset20->unk70 > 0) || (asset20->unk74 > 0.0)) {
                obj->unk74 |= 1 << i;
            }
        } else if ((asset20->unk70 == 2) && (asset20->unk74 < 0.5)) {
            obj->unk74 |= 1 << i;
        } else if ((asset20->unk70 < 2) && (asset20->unk74 > 0.0f)) {
            obj->unk74 |= 1 << i;
        }
    }
    if (racer->unk201 == 0) {
        obj->unk74 = 0;
    } else {
        obj->segment.y_velocity += updateRate * gCurrentRacerWeightStat;
        func_800AF714(obj, updateRate);
        obj->segment.y_velocity -= updateRate * gCurrentRacerWeightStat;
    }
    gCurrentRacerTransform.y_rotation = -obj->segment.trans.y_rotation;
    gCurrentRacerTransform.x_rotation = -obj->segment.trans.x_rotation;
    gCurrentRacerTransform.z_rotation = -obj->segment.trans.z_rotation;
    gCurrentRacerTransform.scale = 1.0f;
    gCurrentRacerTransform.x_position = 0.0f;
    gCurrentRacerTransform.y_position = 0.0f;
    gCurrentRacerTransform.z_position = 0.0f;
    object_transform_to_matrix_2((f32 (*)[4]) sp68, &gCurrentRacerTransform);
    guMtxXFMF(sp68, obj->segment.x_velocity, obj->segment.y_velocity, obj->segment.z_velocity, &racer->lateral_velocity, (f32 *) (&racer->unk34), &racer->velocity);
    if ((racer->unk1E2 == 0) && (racer->unk1E5 == 0)) {
        var_v1 = (((-gCurrentStickY) * 0x40) & 0xFFFF) - (obj->segment.trans.x_rotation & 0xFFFF);
        if (var_v1 > 0x8000) {
            var_v1 -= 0xFFFF;
        }
        if (var_v1 < (-0x8000)) {
            var_v1 += 0xFFFF;
        }
        obj->segment.trans.x_rotation += var_v1 >> 2;
        var_v0 = -(racer->x_rotation_vel & 0xFFFF);
        if (var_v0 > 0x8000) {
            var_v0 -= 0xFFFF;
        }
        if (var_v0 < (-0x8000)) {
            var_v0 += 0xFFFF;
        }
        var_v0 *= updateRate;
        racer->x_rotation_vel += var_v0 >> 4;
    }
    if (gRaceStartTimer != 0) {
        gCurrentButtonsPressed &= ~0x0010;
    }
    if ((racer->buoyancy != 0.0f) || (racer->unk1E2 == 4)) {
        racer->unk1FB = 0;
    }
    if (((gCurrentButtonsPressed & 0x0010) && ((racer->buoyancy > 0.0f) || (racer->unk1E2 >= 2))) && (racer->unk1FB == 0)) {
        if (racer->buoyancy != 0.0f) {
        obj->segment.y_velocity += 4.5;
        if (obj->segment.y_velocity > 5.5) {
            obj->segment.y_velocity = 5.5f;
        }
        } else {
        obj->segment.y_velocity += 3.5;
        }
        racer->unk1FB = ((s32) ((f32) ((2.0 * obj->segment.y_velocity) / gCurrentRacerWeightStat))) + 1;
    }
    if (racer->unk1FB > 0) {
        racer->unk1FB -= updateRate;
    } else {
        racer->unk1FB = 0;
    }
    if (sp118 > 40.0f) {
        racer->unkC4 = 0.11f;
    }
    if (obj->unk60->unk0 == 1) {
        temp_v0_16 = (Unknown80046524 *) obj->unk60->unk4;
        temp_v0_16->unk0 = (gCurrentStickX * 0x14) + 0x4000;
        temp_v0_16->unk3A++;
        temp_v0_16->unk3A &= 1;
    }
    second_racer_camera_update(obj, racer, 4, updateRateF);
    if (sp67) {
        func_800230D0(obj, racer);
    }
}
#else
GLOBAL_ASM("asm/non_matchings/racer/func_80046524.s")
#endif

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
        racer->unk204 = 0x78;
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
        angle = (obj->segment.trans.x_rotation);
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
        tempAngle = angle - (u16) gCameraObject->trans.x_rotation;
        WRAP(tempAngle, -0x8000, 0x8000);
        gCameraObject->trans.x_rotation += (tempAngle * tempUpdateRate) >> 4;
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
    sp34 = sins_f(gCameraObject->trans.x_rotation - sp24);
    phi_f18 = coss_f(gCameraObject->trans.x_rotation - sp24);
    phi_f18 = (gCameraObject->unk1C * sp34) + (gCameraObject->unk20 * phi_f18);
    xVel = sins_f(-racer->unk196 + 0x8000) * gCameraObject->unk1C;
    zVel = coss_f(-racer->unk196 + 0x8000) * gCameraObject->unk1C;
    yVel = (1.0 - (gDialogueCameraAngle / 10240.0f)); // Goes between 0-1
    xVel -= racer->ox1 * 10.0f * yVel;
    zVel -= racer->oz1 * 10.0f * yVel;
    yVel = racer->lateral_velocity * 2;
    racer->unkC8 -= (racer->unkC8 - yVel) * 0.25;
    yVel = sins_f(racer->unk196 + 0x4000) * racer->unkC8;
    gCameraObject->trans.x_position = obj->segment.trans.x_position + xVel + yVel;
    yVel = gCameraObject->trans.y_position - (obj->segment.trans.y_position + phi_f18);
    if (yVel > 0.0f) {
        yVel *= 0.5;
    } else {
        if (D_8011D53C == 1) {
            yVel *= 0.5; // Unreachable. D_8011D53C is never not 0.
        } else {
            yVel *= 0.25;
        }
        if (racer->boostTimer != 0) {
            yVel *= 2.0;
        }
    }
    gCameraObject->trans.y_position -= yVel;
    gCameraObject->trans.z_rotation = 0;
    if (gRaceStartTimer) {
        gCameraObject->trans.y_position = obj->segment.trans.y_position + phi_f18;
    }

    coss_f(racer->unk196 + 0x4000); // Unused function call that wasn't fully optimised out.
    gCameraObject->trans.z_position = obj->segment.trans.z_position + zVel;
    gCameraObject->trans.y_rotation = racer->unk196;
    segmentIndex = get_level_segment_index_from_position(gCameraObject->trans.x_position, gCameraObject->trans.y_position, gCameraObject->trans.z_position);
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
        velocity = 1.0 - (velocity * (1.0/6.0));
        if (velocity < 0.0f) {
            velocity = 0.0f;
        }
    } else {
        obj->segment.trans.x_position += pos->x * updateRateF * arg6;
        obj->segment.trans.z_position += pos->z * updateRateF * arg6;
        velocity = 1.0f;
    }
    gCurrentRacerTransform.y_rotation = -obj->segment.trans.y_rotation;
    gCurrentRacerTransform.x_rotation = 0;
    gCurrentRacerTransform.z_rotation = 0;
    gCurrentRacerTransform.x_position = 0.0f;
    gCurrentRacerTransform.y_position = 0.0f;
    gCurrentRacerTransform.z_position = 0.0f;
    gCurrentRacerTransform.scale = 1.0f;
    object_transform_to_matrix_2(mtxF, &gCurrentRacerTransform);
    guMtxXFMF(mtxF, pos->x, pos->y, pos->z, &pos->x, &pos->y, &pos->z);
    angle = -((s16) (u16)arctan2_f(pos->x, pos->y)) * velocity;
    angle = (u16) (angle - (arg5 << 6)) - (u16) racer->x_rotation_vel;
    angle = angle > 0x8000 ? angle - 0xffff : angle;
    angle = angle < -0x8000 ? angle + 0xffff : angle;
    racer->x_rotation_vel += (angle * updateRate) >> 4;
    angleVel = ((s16) (u16)arctan2_f(pos->z, pos->y) * velocity);
    angleVel += -gCurrentStickY * 32;
    angleVel += 0x3C0;
    angle = (u16)angleVel - ((u16) obj->segment.trans.x_rotation);
    angle = angle > 0x8000 ? angle - 0xffff : angle;
    angle = angle < -0x8000 ? angle + 0xffff : angle;
    obj->segment.trans.x_rotation += (angle * updateRate) >> 4;
    return velocity;
}

GLOBAL_ASM("asm/non_matchings/racer/func_80049794.s")

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
                racer->unk204 = 120;
                obj->segment.x_velocity *= 0.7;
                obj->segment.z_velocity *= 0.7;
                break;
        }
        racer->attackType = ATTACK_NONE;
    }
}

#ifdef NON_EQUIVALENT
void update_camera_plane(f32 updateRate, Object* obj, Object_Racer* racer) {
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
    if (((!(gCurrentRacerInput & 0x10)) || racer->unk1E2 < 3) && !racer->unk1F5) {
        angle = (-racer->steerVisualRotation - (racer->unk196 & 0xFFFF)) + 0x8000;
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
        racer->unk196 += angleVel;
    } else {
        racer->camera_zoom = 0.0f;
    }
    if (gDialogueCameraAngle) {
        racer->unk196 = 0x8000 - racer->steerVisualRotation;
    }
    if (racer->unk1E0 == 2 || racer->unk1E0 == -2) {
        angle = 0;
    } else {
        angle = obj->segment.trans.x_rotation;
        if (angle > 0x3000) {
            angle = 0x3000;
        }
        if (angle < -0x3000) {
            angle = -0x3000;
        }
    }
    angle = -(angle - ((s32) (temp_f16 * 10.0f)));
    angle = angle - ((u16) gCameraObject->trans.x_rotation);
    if (angle > 0x8000) {
        angle -= 0xFFFF;
    }
    if (angle < -0x8000) {
        angle += 0xFFFF;
    }
    gCameraObject->trans.x_rotation += ((angle * delta) >> 4);
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
    if (racer->velocity < 0.0 && !racer->unk1E2) {
        tempVel = -(racer->velocity * brakeVar);
        tempVel = tempVel * 6.0f;
        if (65.0 < tempVel) {
            tempVel = 65.0f;
        }
        if (yOffset);
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
    phi_f14 = sins_f(gCameraObject->trans.x_rotation - 0x400);
    xOffset = coss_f(gCameraObject->trans.x_rotation - 0x400);
    baseFloat3 = phi_f14;
    baseFloat2 = (gCameraObject->unk1C * baseFloat3) - (gCameraObject->unk20 * xOffset);
    baseFloat1 = ((gCameraObject->unk1C) * (gCameraObject->unk1C));
    baseFloat1 += (gCameraObject->unk20 * baseFloat3);
    xOffset = sins_f(0x8000 - racer->unk196) * baseFloat2;
    zOffset = coss_f(0x8000 - racer->unk196) * baseFloat2;
    yVel = sins_f(racer->unk196 + 0x4000) * 3.0f;
    yVel = yVel * racer->lateral_velocity;
    gCameraObject->trans.x_position = (obj->segment.trans.x_position + xOffset) + yVel;
    temp_f16 = obj->segment.trans.y_position;
    yOffset = gCameraObject->trans.y_position - (temp_f16 + baseFloat1);
    if (racer->unk1E0 == 1 || racer->unk1E0 == -1) {
        racer->unk74 = 8.0;
    }
    if (racer->unk1E0 == 2 || racer->unk1E0 == -2) {
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
    gCameraObject->trans.z_position = zOffset + obj->segment.trans.z_position + (-coss_f(racer->unk196 + 0x4000) * 3.0f * racer->lateral_velocity);
    gCameraObject->trans.y_rotation = racer->unk196;
    if (racer->unk1E0 || gDialogueCameraAngle) {
        angle = -(u16) gCameraObject->trans.z_rotation;
        if (angle > 0x8000) {
            angle -= 0xFFFF;
        }
        if (angle < -0x8000) {
            angle += 0xFFFF;
        }
        gCameraObject->trans.z_rotation += angle >> 2;
    } else {
        angle = (u16) gCameraObject->trans.z_rotation;
        angle = angle + (-(racer->x_rotation_vel >> 4));
        if (angle > 0x8000) {
            angle -= 0xFFFF;
        }
        if (angle < -0x8000) {
            angle += 0xFFFF;
        }
        gCameraObject->trans.z_rotation += angle >> 3;
    }
    tempVel = gCameraObject->trans.x_position;
    segmentIndex = get_level_segment_index_from_position(tempVel, gCameraObject->trans.y_position, gCameraObject->trans.z_position);
    if (segmentIndex != -1) {
        gCameraObject->segmentIndex = segmentIndex;
    }
    racer->unk196 = gCameraObject->trans.y_rotation;
}
#else
GLOBAL_ASM("asm/non_matchings/racer/update_camera_plane.s")
#endif


GLOBAL_ASM("asm/non_matchings/racer/func_8004CC20.s")

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
    racer->unk196 = 0x8000 - racer->steerVisualRotation;
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
    gCurrentRacerTransform.y_rotation = -gCameraObject->trans.y_rotation + 0x8000;
    gCurrentRacerTransform.x_rotation = -gCameraObject->trans.x_rotation;
    gCurrentRacerTransform.z_rotation = 0;
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
    angleDiff = (u16) (-obj->segment.trans.z_rotation);
    angle = angleDiff - ((u16) gCameraObject->trans.z_rotation);
    WRAP(angle, -0x8000, 0x8000);
    gCameraObject->trans.z_rotation += ((angle * UpdateRate) >> 4);
    angleDiff = -obj->segment.trans.x_rotation;
    angle = angleDiff - (u16) gCameraObject->trans.x_rotation;
    WRAP(angle, -0x8000, 0x8000);
    gCameraObject->trans.x_rotation += ((angle * UpdateRate) >> 4);
    gCameraObject->trans.y_rotation = racer->unk196;
    segmentIndex = get_level_segment_index_from_position(gCameraObject->trans.x_position, gCameraObject->trans.y_position, gCameraObject->trans.z_position);
    if (segmentIndex != SEGMENT_NONE) {
        gCameraObject->segmentIndex = segmentIndex;
    }
    racer->unk196 = gCameraObject->trans.y_rotation;
    gCameraObject->trans.x_position += gCameraObject->x_velocity;
    gCameraObject->trans.y_position += gCameraObject->y_velocity;
    gCameraObject->trans.z_position += gCameraObject->z_velocity;
}

/**
 * Updates the carpet vehicle that Taj uses during the overworld race challenges.
*/
void update_carpet(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer) {
    s16 sp26;

    if (racer->unk118 != 0) {
        func_80006AC8(obj);
    }
    if (is_taj_challenge() && racer->vehicleID == VEHICLE_CARPET) {
        obj->interactObj->unk14 = 0;
    }
    sp26 = obj->segment.animFrame;
    racer->vehicleID = VEHICLE_CARPET;
    func_80049794(updateRate, updateRateF, obj, racer);
    racer->vehicleID = racer->vehicleIDPrev;
    obj->segment.unk38.byte.unk3B = 0;
    if (racer->vehicleID == VEHICLE_CARPET) {
        if (racer->unk154 != NULL) {
            racer->unk154->segment.trans.x_position = obj->segment.trans.x_position;
            racer->unk154->segment.trans.y_position = obj->segment.trans.y_position;
            racer->unk154->segment.trans.z_position = obj->segment.trans.z_position;
            racer->unk154->segment.unk2C.half.lower = obj->segment.unk2C.half.lower;
            racer->unk154->segment.trans.y_rotation = obj->segment.trans.y_rotation;
            racer->unk154->segment.trans.x_rotation = obj->segment.trans.x_rotation;
            racer->unk154->segment.trans.z_rotation = obj->segment.trans.z_rotation;
            obj->segment.unk38.byte.unk3B = 0;
            obj->segment.animFrame = sp26 + updateRate;
            func_80061C0C(obj);
        }
    }
}

/**
 * Initialise the basic properties of each racer object. If it's tied to a human player,
 * will also initialise a camera object.
 */
void obj_init_racer(Object *obj, LevelObjectEntry_CharacterFlag *racer) {
    Object_Racer *tempRacer;
    ActivePlayers player;
    s32 i;

    D_8011D53C = 0;
    tempRacer = (struct Object_Racer *) obj->unk64;
    obj->segment.trans.y_rotation = racer->unkC;
    obj->segment.trans.x_rotation = racer->unkA;
    obj->segment.trans.z_rotation = racer->unk8;
    player = racer->unkE;
    tempRacer->unk194 = 0;
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
    tempRacer->steerVisualRotation = obj->segment.trans.y_rotation;
    tempRacer->x_rotation_vel = obj->segment.trans.z_rotation;
    tempRacer->unkC4 = 0.5f;
    if (1) {} // Fakematch
    tempRacer->unk196 = tempRacer->steerVisualRotation;
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
    tempRacer->unk1E2 = 3;
    tempRacer->unk1AA = 1;
    tempRacer->unk1AE = 1;
    tempRacer->miscAnimCounter = tempRacer->playerIndex * 5;
    tempRacer->checkpoint_distance = 1.0f;
    tempRacer->unk1FD = 0;
    tempRacer->magnetSoundMask = NULL;
    tempRacer->shieldSoundMask = NULL;
    tempRacer->unk180 = 0;
    tempRacer->unk218 = 0;
    tempRacer->unk220 = 0;
    tempRacer->unk21C = 0;
    if (tempRacer->playerIndex != PLAYER_COMPUTER && !D_8011D582) {
        set_active_camera(player);
        gCameraObject = (ObjectCamera *) get_active_camera_segment_no_cutscenes();
        gCameraObject->trans.z_rotation = 0;
        gCameraObject->trans.x_rotation = 0x400;
        gCameraObject->trans.y_rotation = tempRacer->unk196;
        gCameraObject->mode = CAMERA_CAR;
        gCameraObject->unk3C = 0xFF;
        gCameraObject->unk3D = 0xFF;
        gCameraObject->unk3E = 0xFF;
        gCameraObject->unk3F = 0xFF;
        gCameraObject->unk18 = 0.0f;
        update_player_camera(obj, tempRacer, 1.0f);
    }
    if (!D_8011D582) {
        D_8011D583 = 0;
        gDialogueCameraAngle = 0;
        D_8011D584 = 0;
    }
    obj->interactObj->unk14 = 5;
    obj->interactObj->unk11 = 0;
    obj->interactObj->unk10 = 0xF;
    obj->interactObj->unk12 = 0x14;
    tempRacer->unk1EE = 0;
    if (!D_8011D582) {
        tempRacer->transparency = 255;
    }
    D_8011D560 = 0;
    D_8011D544 = 300.0f;
    tempRacer->unk1C9 = 6;
    tempRacer->unk1C6 = 100;
    D_8011D580 = 0;

    // This needs to be on one line to match.
    for (i = 0; i < 4; i++) { \
        D_8011D58C[i] = 0; 
    }
    if (1) {} if (1) {} // Fakematch
    func_80043ECC(NULL, NULL, 0);
    D_8011D583 = i;
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
    gRaceStartTimer = func_8001139C();
    updateRateF = updateRate;
    tempRacer = (Object_Racer *)obj->unk64;
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
    if (osTvType == TV_TYPE_PAL) {
        updateRateF *= 1.2;
    }
    tempRacer->unk1F6 -= updateRate;
    if (tempRacer->unk1F6 < 0) {
        tempRacer->unk1F6 = 0;
    }
    obj->unk74 = 0;
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
                render_printf(gRacerDebugCoords, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
            }
        }
        set_render_printf_background_colour(0, 0, 0, 128);
        if (is_taj_challenge()) {
            gDialogueCameraAngle = 0;
        }
        context = get_render_context();
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
        gCurrentRacerMiscAssetPtr = (f32 *) get_misc_asset(MISC_RACER_WEIGHT);
        gCurrentRacerWeightStat = gCurrentRacerMiscAssetPtr[tempRacer->characterId] * 0.45;
        if (tempRacer->unk204 > 0) {
            gCurrentRacerWeightStat = -0.02f;
        }
        gCurrentRacerMiscAssetPtr = (f32 *) get_misc_asset(MISC_RACER_HANDLING);
        gCurrentRacerHandlingStat = gCurrentRacerMiscAssetPtr[tempRacer->characterId];
        gCurrentRacerMiscAssetPtr = (f32 *) get_misc_asset(MISC_ASSET_UNK0B);
        D_8011D574 = gCurrentRacerMiscAssetPtr[tempRacer->characterId];
        if (tempRacer->unk1FE == 3) {
            gCurrentRacerWeightStat *= (f32) tempRacer->unk1FF / 256;
        }
        if (tempRacer->unk1FE == 1) {
            gCurrentRacerWeightStat -= (gCurrentRacerWeightStat * tempRacer->unk1FF) / 128;
            if (tempRacer->unk204 > 0) {
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
        gCurrentRacerMiscAssetPtr = (f32*) get_misc_asset(obj->segment.header->unk5C);
        D_8011D568 = (f32 *) get_misc_asset(obj->segment.header->unk5D);
        
        if (obj->segment.y_velocity < 4.0 && (tempRacer->unk1E2 >= 3 || tempRacer->buoyancy != 0.0)) {
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
        if (tempRacer->raceFinished == TRUE || context == DRAW_MENU) {
            tempRacer->unk1CA = 1;
            tempRacer->playerIndex = PLAYER_COMPUTER;
            tempRacer->unk1C9 = 0;
            if (tempRacer->shieldTimer > 5) {
                tempRacer->shieldTimer = 5;
            }
        }
        tempVar = tempRacer->playerIndex;
        if (tempRacer->playerIndex != PLAYER_COMPUTER) {
            if (tempRacer->unk108 == 0) {
                if (func_8000E158()) {
                    tempVar = 1 - tempVar;
                }
                //Cap the joystick tilt and write the button inputs to the current buffer.
                gCurrentStickX = clamp_joystick_x_axis(tempVar);
                // Flip the steering for adventure 2.
                if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
                    gCurrentStickX = -gCurrentStickX;
                }
                gCurrentStickY = clamp_joystick_y_axis(tempVar);
                gCurrentRacerInput = get_buttons_held_from_player(tempVar);
                gCurrentButtonsPressed = get_buttons_pressed_from_player(tempVar);
                gCurrentButtonsReleased = get_buttons_released_from_player(tempVar);
            } else {
                racer_enter_door(tempRacer, updateRate);
            }
        } else {
            racer_AI_pathing_inputs(obj, tempRacer, updateRate);
        }
        //Set the value that decides whether to get an empowered boost.
        if (!(gCurrentRacerInput & A_BUTTON)) {
            tempRacer->throttleReleased = TRUE;
        }
        if (check_if_showing_cutscene_camera() || gRaceStartTimer == 100 || tempRacer->unk1F1 || D_8011D584 || tempRacer->approachTarget || tempRacer->unk204 > 0) {
            gCurrentStickX = 0;
            gCurrentStickY = 0;
            gCurrentRacerInput = 0;
            gCurrentButtonsPressed = 0;
            gCurrentButtonsReleased = 0;
            tempRacer->steerAngle = 0;
        }
        if (tempRacer->unk204 > 0) {
            tempRacer->unk204 -= updateRate;
            tempRacer->velocity *= 0.9f; //!@Delta
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
        if (gRaceStartTimer == 0 && header->laps > (tempRacer->unk194)) {
            // Keep it under 10 minutes.
            if (tempRacer->lap_times[tempRacer->unk194] < normalise_time(36000) - updateRate) {
                tempRacer->lap_times[tempRacer->unk194] += updateRate;
            } else {
                tempRacer->lap_times[tempRacer->unk194] = normalise_time(36000);
            }
        }
        // Assign a camera to human players.
        if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
            gCameraObject = (ObjectCamera *) get_active_camera_segment_no_cutscenes();
        }
        D_8011D5AE = func_8002B0F4(obj->segment.unk2C.half.lower, obj->segment.trans.x_position, obj->segment.trans.z_position, (struct TempStruct8 **) &D_8011D5B0);
        if (D_8011D5AE) {
            for (i = 0; i < D_8011D5AE; i++) {
                if (D_8011D5B0[i]->unk10 == 0xF) {
                    if (D_8011D5B0[i]->unk0 < gCurrentCourseHeight) {
                        gCurrentCourseHeight = D_8011D5B0[i]->unk0;
                    }
                }
            }
        }
        if (tempRacer->vehicleID != VEHICLE_HOVERCRAFT) {
            waterHeight = -10000.0f;
            gRacerWaveType = get_wave_properties(obj->segment.trans.y_position, &waterHeight, &gCurrentRacerWaterPos);
            if (gRacerWaveType) {
                if (obj->segment.trans.y_position - 5.0f < waterHeight) {
                    tempRacer->unk1E5 = 5;
                    tempRacer->buoyancy = waterHeight - (obj->segment.trans.y_position - 5.0f);
                } else {
                    tempRacer->buoyancy = 0.0f;
                }
            } else {
                if (tempRacer->unk1E5 > 0) {
                    tempRacer->unk1E5--;
                } else {
                    tempRacer->buoyancy = 0.0f;
                }
            }
            if (tempRacer->unk1E5 > 0 && obj->segment.trans.y_position < waterHeight + 5.0f) {
                obj->interactObj->unk14 |= 0x10;
            } else {
                obj->interactObj->unk14 &= 0xFFEF;
            }
        }
        func_8002ACC8(0);
        switch (tempRacer->vehicleID) {
        case VEHICLE_CAR: func_8004F7F4(updateRate, updateRateF, obj, tempRacer); break;
        case VEHICLE_LOOPDELOOP: func_8004CC20(updateRate, updateRateF, obj, tempRacer); break;
        case VEHICLE_HOVERCRAFT: func_80046524(updateRate, updateRateF, obj, tempRacer); break;
        case VEHICLE_PLANE: func_80049794(updateRate, updateRateF, obj, tempRacer); break;
        case VEHICLE_FLYING_CAR: /* fall through */
        case VEHICLE_CARPET: update_carpet(updateRate, updateRateF, obj, tempRacer); break;
        case VEHICLE_TRICKY: update_tricky(updateRate, updateRateF, obj, tempRacer, &gCurrentRacerInput, &gCurrentButtonsPressed, &gRaceStartTimer); break;
        case VEHICLE_BLUEY: update_bluey(updateRate, updateRateF, obj, tempRacer, &gCurrentRacerInput, &gCurrentButtonsPressed, &gRaceStartTimer); break;
        case VEHICLE_SMOKEY: /* fall through */
        case VEHICLE_PTERODACTYL: update_smokey(updateRate, updateRateF, obj, tempRacer, &gCurrentRacerInput, &gCurrentStickX, &gRaceStartTimer); break;
        case VEHICLE_BUBBLER: update_bubbler(updateRate, updateRateF, obj, tempRacer, &gCurrentRacerInput, &gCurrentButtonsPressed, &gRaceStartTimer); break;
        case VEHICLE_WIZPIG: update_wizpig(updateRate, updateRateF, obj, tempRacer, &gCurrentRacerInput, &gCurrentButtonsPressed, &gRaceStartTimer); break;
        case VEHICLE_ROCKET: update_rocket(updateRate, updateRateF, obj, tempRacer, &gCurrentRacerInput, &gCurrentButtonsPressed, &gRaceStartTimer); break;
        }
        if (tempRacer->magnetTimer == 0) {
            if (tempRacer->magnetSoundMask) {
                func_8000488C(tempRacer->magnetSoundMask);
                tempRacer->magnetSoundMask = NULL;
            }
        }
        playerID = header->playerIndex;
        if (playerID) {
            playerIDF = -(f32) playerID;
            CLAMP(tempRacer->velocity, playerIDF, playerID);
        }
        if (context != DRAW_MENU || func_8000E148()) {
            func_800050D0(obj, gCurrentButtonsPressed, gCurrentRacerInput, updateRate);
        }
        lastCheckpointDist = tempRacer->checkpoint_distance;
        tempVar = func_800185E4(tempRacer->checkpoint, obj, xTemp, yTemp, zTemp, &tempRacer->checkpoint_distance, &tempRacer->unk1C8);
        if (tempVar == -100) {
            func_8005C270(tempRacer);
        }
        checkpointNode = find_next_checkpoint_node(tempRacer->checkpoint, tempRacer->unk1C8);
        if (tempRacer->playerIndex == PLAYER_COMPUTER && checkpointNode->unk36[tempRacer->unk1CA] == 5 && tempRacer->unk1E5) {
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
                if (tempRacer->playerIndex != PLAYER_COMPUTER && tempRacer->lap + 1 == header->laps
                    && !D_8011D580 && get_current_level_race_type() == RACETYPE_DEFAULT) {
                    func_800014BC(1.12f);
                    D_8011D580 = 1;
                }
            }
            if (is_taj_challenge()) {
                if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
                    checkpointNode = find_next_checkpoint_node(tempRacer->checkpoint, tempRacer->unk1C8);
                    if (!tempRacer->unk15C) {
                        newObject.x = 0;
                        newObject.y = 0;
                        newObject.z = 0;
                        newObject.objectID = 0x86;
                        newObject.size = 8;
                        tempRacer->unk15C = spawn_object(&newObject, 1);
                        if (tempRacer->unk15C) {
                            tempRacer->unk15C->segment.unk3C_a.level_entry = NULL;
                            tempRacer->unk15C->segment.unk38.byte.unk39 = 128;
                        }
                    }
                    if (tempRacer->unk15C) {
                        tempRacer->unk15C->segment.trans.x_position = checkpointNode->obj->segment.trans.x_position;
                        tempRacer->unk15C->segment.trans.y_position = checkpointNode->obj->segment.trans.y_position;
                        if (tempRacer->vehicleID == VEHICLE_CAR) {
                            tempRacer->unk15C->segment.trans.y_position -= 30.0;
                        }
                        tempRacer->unk15C->segment.trans.z_position = checkpointNode->obj->segment.trans.z_position;
                        tempRacer->unk15C->segment.trans.y_rotation = checkpointNode->obj->segment.trans.y_rotation;
                        tempRacer->unk15C->segment.trans.x_rotation = checkpointNode->obj->segment.trans.x_rotation;
                        tempRacer->unk15C->segment.unk2C.half.lower = checkpointNode->obj->segment.unk2C.half.lower;
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
            if (tempRacer->unk15C) {
                tempRacer->unk15C->segment.animFrame += 8 * updateRate;
            }
            if (tempRacer->unk1BA > 400 || tempRacer->unk1BA < -400) {
                func_80022E18(2);
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
        D_8011D583 = 0;
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
        tempRacer->stretch_height += (((tempRacer->stretch_height_cap - tempRacer->stretch_height) * 0.125) + stretch) * updateRateF;
        if ((stretch < 0.0f && tempRacer->stretch_height <= tempRacer->stretch_height_cap) ||
            (stretch > 0.0f && tempRacer->stretch_height >= tempRacer->stretch_height_cap)) {
            tempRacer->stretch_height = tempRacer->stretch_height_cap;
            tempRacer->stretch_height_cap = 1.0f;
        }

        tempVar = ((tempRacer->headAngleTarget - tempRacer->headAngle) * updateRate) >> 3;
        CLAMP(tempVar, -0x800, 0x800);
        if (gAntiPiracyHeadroll) {
            tempRacer->headAngle += gAntiPiracyHeadroll;
        } else {
            tempRacer->headAngle += tempVar;
        }
        if ((gCurrentButtonsPressed & R_TRIG) && tempRacer->unk1EB) {
            tempRacer->unk1EC = 1;
            tempRacer->unk1EB = 0;
        } else if (gCurrentButtonsPressed & R_TRIG) {
            tempRacer->unk1EB = 22;
        }
        if (tempRacer->unk1EB > 0) {
            tempRacer->unk1EB -= updateRate;
        } else {
            tempRacer->unk1EB = 0;
        }
        if (tempRacer->shieldTimer > 0) {
            if (tempRacer->shieldTimer > 60) {
                if (tempRacer->shieldSoundMask) {
                    update_spatial_audio_position(tempRacer->shieldSoundMask, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
                } else if (tempRacer->unk118) {
                    play_sound_at_position(SOUND_SHIELD, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 1, &tempRacer->shieldSoundMask);
                }
            } else if (tempRacer->shieldSoundMask) {
                func_800096F8(tempRacer->shieldSoundMask);
                tempRacer->shieldSoundMask = 0;
            }
            tempRacer->shieldTimer -= updateRate;
            if (tempRacer->shieldTimer <= 0) {
                tempRacer->shieldType = SHIELD_NONE;
            }
        }
        if (tempRacer->unk180) {
            update_spatial_audio_position(tempRacer->unk180, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
        }
        if (is_in_time_trial() && tempRacer->playerIndex == PLAYER_ONE && gRaceStartTimer == 0) {
            func_80059BF0(obj, updateRate);
        }
        if (tempRacer->soundMask) {
            update_spatial_audio_position(tempRacer->soundMask, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
        }
        D_8011D584 = 0;
        if (tempRacer->unk150 && gRaceStartTimer == 0) {
            s8 *yAsset;
            tempRacer->unk150->segment.trans.x_position = obj->segment.trans.x_position;
            yAsset = (s8 *) get_misc_asset(MISC_ASSET_UNK00);
            
            tempRacer->unk150->segment.trans.y_position = obj->segment.trans.y_position + yAsset[tempRacer->characterId];
            tempRacer->unk150->segment.trans.z_position = obj->segment.trans.z_position;
            tempRacer->unk150->segment.trans.scale = obj->segment.unk30 / 265.0f;
            if (obj->segment.unk30 < 1500.0 || get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
                tempObj = tempRacer->unk150;
                tempObj->segment.trans.unk6 |= 0x4000;
            }
            if (tempRacer->unk150->segment.trans.scale < 1.0) {
                tempRacer->unk150->segment.trans.scale = 1.0f;
            }
            tempRacer->unk150 = NULL;
        }
        tempRacer->unk1FE = -1;
        set_racer_tail_lights(tempRacer);
        if (tempRacer->unk20E) {
            if (tempRacer->unk210 > updateRate) {
                tempRacer->unk210 -= updateRate;
            } else {
                tempRacer->unk210 = 0;
                if (tempRacer->playerIndex == PLAYER_COMPUTER) {
                    play_sound_at_position(tempRacer->unk20E, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
                } else {
                    play_sound_spatial(tempRacer->unk20E, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, NULL);
                }
                tempRacer->unk20E = 0;
            }
        }
        if (header->race_type & RACETYPE_CHALLENGE && header->race_type != RACETYPE_CHALLENGE_EGGS) {
            tempRacer->unk212 = func_8001C418(obj->segment.trans.y_position);
        } else {
            tempRacer->unk212 = 0;
        }
        if (tempRacer->unk194 < tempRacer->lap) {
            tempRacer->unk194 = tempRacer->lap;
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

GLOBAL_ASM("asm/non_matchings/racer/func_8004F7F4.s")

/**
 * At this point, control is taken away from the player.
 * Instead, they'll automatically move towards a specific object.
*/
void racer_approach_object(Object *obj, Object_Racer *racer, f32 divisor) {
    f32 diffX;
    f32 diffY;
    f32 diffZ;

    obj->segment.unk38.byte.unk3B = 0;
    obj->segment.animFrame = 40;
    diffX = racer->approachTarget->segment.trans.x_position - obj->segment.trans.x_position;
    diffY = racer->approachTarget->segment.trans.y_position - obj->segment.trans.y_position;
    diffZ = racer->approachTarget->segment.trans.z_position - obj->segment.trans.z_position;
    move_object(obj, diffX, diffY, diffZ);
    obj->segment.trans.y_rotation = racer->approachTarget->segment.trans.y_rotation;
    obj->segment.trans.x_rotation = racer->approachTarget->segment.trans.x_rotation;
    obj->segment.trans.z_rotation = racer->approachTarget->segment.trans.z_rotation;
    racer->x_rotation_vel = obj->segment.trans.z_rotation;
    racer->steerVisualRotation = obj->segment.trans.y_rotation;
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
            obj->y_rotation_offset +=  tempAngle;
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
            return;
        }
        if (tempAngle < 0) {
            diff = -(max * 0x600);
            if (tempAngle < diff) {
                tempAngle = diff;
            }
            obj->z_rotation_offset += tempAngle;
        }
    }
}

#ifdef NON_MATCHING
typedef struct unk_Object_60 {
    s32 count;
    ObjectTransform *transforms[1]; // Array of ObjectTransform pointers.
} unk_Object_60;

void func_80050A28(Object *obj, Object_Racer *racer, s32 updateRate, f32 updateRateF) {
    s32 soundID;
    f32 scale;
    f32 velocityDiff;
    s32 sp68; // 68
    s32 surfaceType;
    s32 sp60; // 60
    s32 velocityS;
    s32 sp58; // 58
    s8 stoneWheels;
    s8 steerAngle;
    f32 velSquare; // 50
    s32 SteeringVel;
    f32 *miscAsset;
    f32 traction;
    f32 tempVel;
    f32 surfaceTraction;
    ObjectTransform *temp_v0;
    f32 topSpeed; // 78
    s32 i;

    sp58 = 0;
    // Set the square value of the current forward velocity
    velSquare = racer->velocity * racer->velocity;
    if (racer->velocity < 0.0f) {
        velSquare = -velSquare;
    }
    racer->unk84 = 0.0f;
    racer->unk88 = 0.0f;
    // Apply bobbing if there's no dialogue camera rotation active.
    if (gDialogueCameraAngle == 0) {
        scale = (f32) D_800DCDB0[0][racer->miscAnimCounter & 0x1F] * 0.024999999999999998;
        racer->carBobX = -racer->roll * scale;
        racer->carBobY = -racer->yaw * scale;
        racer->carBobZ = -racer->pitch * scale;
        if (obj->unk60 != NULL) {
            for (i = 0; i < ((unk_Object_60 *) obj->unk60)->count; i++) {
                scale = 1.0f / obj->segment.trans.scale;
                temp_v0 = ((unk_Object_60 *) obj->unk60)->transforms[i];
                temp_v0->x_position = (f32) (-racer->carBobX * scale);
                temp_v0->y_position = (f32) (-racer->carBobY * scale);
                temp_v0->z_position = (f32) (-racer->carBobZ * scale);
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
            func_80072348(racer->playerIndex, 1);
        }
        sp60 = TRUE;
        if (gCurrentPlayerIndex >= PLAYER_ONE) {
            if (gNumViewports < FOUR_PLAYERS) {
                if (racer->drift_direction > 0) {
                    obj->unk74 |= 0x1000 | 0x400;
                } else if (racer->drift_direction < 0) {
                    obj->unk74 |= 0x2000 | 0x800;
                } else {
                    obj->unk74 |= 0x2000 | 0x1000;
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
    if (racer->drifting == 0 && racer->velocity > 2.0 && gCurrentRacerInput & R_TRIG && (gCurrentStickX > 50 || gCurrentStickX < -50)) {
        if (gCurrentStickX > 0) {
            racer->drifting = 1;
        } else {
            racer->drifting = -1;
        }
    }
    // Handle drifting
    if (racer->drifting) {
        gCurrentRacerInput = (gCurrentRacerInput & 0xFFFF7FFF);
        gCurrentRacerInput |= B_BUTTON;
        gCurrentStickY = -70;
        sp60 = TRUE;
        if (gNumViewports < FOUR_PLAYERS) {
            obj->unk74 |= 0x2000 | 0x1000 | 0x800 | 0x400;
        } else {
            sp58 = 1;
        }
        racer->y_rotation_vel += updateRate * 0x600 * racer->drifting;
        if (racer->drifting > 0) {
            if (racer->y_rotation_vel < 0 && racer->y_rotation_vel >= 0) {
                racer->drifting = 0;
                racer->y_rotation_vel = 0x7FFF;
            }
        } else if (racer->y_rotation_vel > 0 && racer->y_rotation_vel <= 0) {
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
                obj->unk74 |= 0x1000 | 0x400;
            } else {
                obj->unk74 |= 0x2000 | 0x800;
            }
        } else {
            sp58 = 1;
        }
    }
    // Decide which way to drift when the R button is held
    if (racer->drift_direction == 0 && gCurrentRacerInput & R_TRIG && racer->velocity < -3.0 && (gCurrentStickX > 15 || gCurrentStickX < -15)) {
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
        SteeringVel = (gCurrentStickX >> 1) + (racer->drift_direction * 30);
        if (SteeringVel > 75) {
            SteeringVel = 75;
        }
        if (SteeringVel < -75) {
            SteeringVel = -75;
        }
    } else {
        racer->drift_direction = 0;
    }
    i = ((racer->unk10C - (racer->drift_direction << 13)) * updateRate) >> 4;
    racer->unk10C -= i;
    // racer->unk10C -= ((racer->unk10C - (racer->drift_direction << 13)) * updateRate) >> 4;
    // sounds for drifting and sliding
    if (!(racer->y_rotation_vel <= 0x1800 && racer->y_rotation_vel >= -0x1800 && 
        racer->drift_direction == 0 && racer->drifting == 0 && racer->unk1FB == 0)) {
        sp60 = 1;
        if (racer->unk1FB != 0 && racer->raceFinished == FALSE) {
            func_80072348(racer->playerIndex, 0);
        }
        if (racer->y_rotation_vel < 0) {
            obj->unk74 |= 0x1000 | 0x400;
        } else {
            obj->unk74 |= 0x2000 | 0x800;
        }
        if (racer->drift_direction != 0 || racer->drifting != 0 || racer->unk1FB != 0) {
            if (racer->unk10 == 0) {
                play_sound_spatial(SOUND_CAR_SLIDE, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, (s32 **) &racer->unk10);
            } else {
                func_80009B7C((void *) racer->unk10, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
            }
            if (racer->unk14) {
                func_8000488C(racer->unk14);
            }
        } else {
            if (racer->unk10) {
                func_8000488C(racer->unk10);
            }
        }
    } else {
        if (racer->unk10) {
            func_8000488C(racer->unk10);
        }
        if (racer->unk14) {
            func_8000488C(racer->unk14);
        }
    }
    // Velocity of steering input
    steerAngle = racer->steerAngle;
    velocityS = 6;
    // Turn twice as fast under braking (because that's totally how cars work)
    if (gCurrentRacerInput & B_BUTTON) {
        velocityS = 12;
    }
    // Turn thrice as fast when drifting and braking.
    if (gCurrentRacerInput & B_BUTTON && racer->drift_direction != 0) {
        velocityS = 18;
    }
    // Multiply steering velocity with angle
    SteeringVel = 0;
    if (racer->velocity < -0.3) {
        SteeringVel = steerAngle * velocityS;
    }
    if (racer->velocity > 0.3) {
        SteeringVel = -steerAngle * velocityS;
    }
    // Set final turn velocity by taking the steering velocity and multiplying it by the handling stat of the character. 
    racer->steerVisualRotation -= (s32) (((SteeringVel * updateRate) >> 1) * gCurrentRacerHandlingStat);
    // Now steer the car.
    handle_car_steering(racer);
    // Set base grip level to 0.
    traction = 0.0f;
    surfaceType = SURFACE_DEFAULT;
    // If reversing, flip the steering
    if (racer->velocity < -4.0) {
        if (gCurrentCarSteerVel > 0x1400 || (racer->drift_direction != 0 && gCurrentCarSteerVel > 0)) {
            SteeringVel = racer->miscAnimCounter & 7;
            if (SteeringVel >= 4) {
                SteeringVel = 7 - SteeringVel;
            }
            gCurrentCarSteerVel += SteeringVel * 0x190;
        } else if (gCurrentCarSteerVel < -0x1400 || (racer->drift_direction != 0 && gCurrentCarSteerVel < 0)) {
            SteeringVel = racer->miscAnimCounter & 7;
            if (SteeringVel >= 4) {
                SteeringVel = 7 - SteeringVel;
            }
            gCurrentCarSteerVel -= SteeringVel * 0x190;
        }
    }
    surfaceTraction = 0.0f;
    velocityDiff = 0.0f;
    sp68 = 0; // Number of wheels contacting grass or sand
    stoneWheels = 0; // Number of wheels contacting the stone surface type
    // Iterate through each wheel and find which surface they're on.
    for (i = 0; i < 4; i++) {
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
    }
    // With multiple contact patches, average the surface properties across.
    if (velocityDiff > 1.0f) {
        i--; // fakematch
        traction /= velocityDiff;
        surfaceTraction /= velocityDiff;
    }
    // If on the Taj pad and the horn is honked, summon Taj
    if (racer->playerIndex == PLAYER_ONE && racer->unk1E2 != 0 && surfaceType == SURFACE_TAJ_PAD && gCurrentButtonsPressed & Z_TRIG) {
        D_8011D582 = 2;
    }
    // Set grip levels to basically zero when floating on water.
    if (racer->buoyancy != 0.0) {
        traction = 0.02f;
        surfaceTraction = 0.0f;
    }
    // no clue :) 
    if (surfaceType == SURFACE_SAND && racer->velocity < -2.0 && racer->raceFinished == FALSE) {
        func_80072348(racer->playerIndex, 0);
    }
    miscAsset = (f32 *) get_misc_asset(MISC_ASSET_UNK08);
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
    tempVel = coss_f(racer->x_rotation_vel);
    if (tempVel < 0.0f) {
        tempVel = -tempVel;
    }
    // Multiply lateral velocity by pitch
    racer->lateral_velocity *= tempVel;
    gCurrentSurfaceType = surfaceType;
    if (stoneWheels != 0) {
        miscAsset = (f32 *) get_misc_asset(MISC_ASSET_UNK20);
        topSpeed *= miscAsset[stoneWheels];
        racer->magnetTimer = 0;
        racer->lateral_velocity = 0.0f;
    } else if (surfaceType == SURFACE_FROZEN_WATER) {
        racer->boost_sound |= 4;
        racer_play_sound(obj, SOUND_BOUNCE2);
    }
    // If driving over a zip pad, apply a boost.
    if (racer->boostTimer == 0 && surfaceType == SURFACE_ZIP_PAD) {
        racer->boostTimer = normalise_time(45);
        racer->boostType = BOOST_LARGE;
        racer_play_sound(obj, SOUND_ZIP_PAD_BOOST);
        play_random_character_voice(obj, SOUND_VOICE_CHARACTER_POSITIVE, 8, 0x82);
        if (racer->raceFinished == FALSE) {
            func_80072348(racer->playerIndex, 8);
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
        if ((sp60 && racer->velocity < -2.0) || sp58 || racer->unk1FB != 0) {
            if (racer->wheel_surfaces[2] < SURFACE_NONE) {
                obj->unk74 |= gSurfaceFlagTable[racer->wheel_surfaces[2]];
            }
            if (racer->wheel_surfaces[3] < SURFACE_NONE) {
                obj->unk74 |= gSurfaceFlagTable[racer->wheel_surfaces[3]] * 2;
            }
        }
        if (racer->velocity < -2.0) {
            if (racer->wheel_surfaces[2] < SURFACE_NONE) {
                obj->unk74 |= gSurfaceFlagTable4P[racer->wheel_surfaces[2]];
            }
            if (racer->wheel_surfaces[3] < SURFACE_NONE) {
                obj->unk74 |= gSurfaceFlagTable4P[racer->wheel_surfaces[3]] * 2;
            }
        }
    }
    // Play a sound on grass and sand when landing on it
    surfaceType = gSurfaceSoundTable[surfaceType];
    soundID = surfaceType;
    if (racer->unk18 == NULL && soundID != SOUND_NONE && racer->velocity < -2.0) {
        play_sound_global(soundID, &racer->unk18);
    }
    if (racer->unk18 != NULL && (soundID == SOUND_NONE || racer->velocity > -2.0)) {
        func_8000488C(racer->unk18);
    }
    // Apply a bobbing effect when on grass and sand.
    if (racer->velocity < -2.0 && sp68 >= 4) {
        scale = (f32) (racer->miscAnimCounter & 1) * 0.5;
        racer->carBobX -= racer->roll * scale;
        racer->carBobY -= racer->yaw * scale;
        racer->carBobZ -= racer->pitch * scale;
    }
    tempVel = racer->velocity;
    // Keep velocity positive and keep it below 12
    if (tempVel < 0.0f) {
        tempVel = -tempVel;
    }
    if (tempVel > 12.0f) {
        tempVel = 12.0f;
    }
    // Convert the velocity value to an int
    velocityS = (s32) tempVel;
    miscAsset = &gCurrentRacerMiscAssetPtr[velocityS];
    velocityDiff = tempVel - velocityS;
    // Calculate the velocity multiplier based on current velocity
    surfaceTraction = (f32) ((miscAsset[1] * velocityDiff) + (miscAsset[0] * (1.0 - velocityDiff)));
    surfaceTraction = (surfaceTraction * 1.7);
    surfaceTraction *= topSpeed;
    // Force the throttle wide open if boosting
    if (racer->boostTimer > 0) {
        if (gRaceStartTimer == 0) {
            racer->throttle = 1.0f;
            if (surfaceTraction != 0.0) {
                surfaceTraction = 2.0f;
            }
            racer->boostTimer -= updateRate;
        }
    } else {
        racer->boostTimer = 0;
    }
    if (racer->velocity > -2.0 && racer->velocity < 3.0 && (racer->playerIndex != PLAYER_COMPUTER || racer->unk214 != 0)) {
        tempVel = (3.0 - racer->velocity) * 0.15;
        if (soundID == 4) {
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
    tempVel = (racer->brake * surfaceTraction) * 0.32; //!@Delta
    racer->velocity -= surfaceTraction * racer->throttle;
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
    surfaceTraction = gCurrentRacerWeightStat;
    obj->segment.y_velocity -= surfaceTraction * updateRateF;
    if (gDialogueCameraAngle != 0) {
        surfaceTraction = 0.0f;
    }
    if (racer->brake < 0.9 && racer->vehicleIDPrev < 5 && gRaceStartTimer == 0) {
        if (racer->pitch < 0.0) {
            velocityDiff = -racer->pitch;
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
        racer->velocity += surfaceTraction * (racer->pitch / (4.0f - velocityDiff)) * updateRateF;
    }
    racer->forwardVel -= (racer->forwardVel + (racer->velocity * 0.05)) * 0.125; //!@Delta
    racer->unk1E8 = racer->steerAngle;
    racer->unk110 = gCurrentCarSteerVel;
    if (racer->unk1E0 != 0) {
        if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
            if (racer->wheel_surfaces[0] != SURFACE_NONE) {
                D_8011D550 = D_800DCCCC[racer->wheel_surfaces[0]];
                *((s16*) &D_8011D552) = racer->unk1E0; // necessary because a different function expects a char.
                racer->unk1E0 = 0;
            }
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/racer/func_80050A28.s")
#endif

// Loops for as long as Taj exists. After swapping vehicle once, will remain true until you enter a door.
s32 func_80052188(void) {
    if (D_8011D582 == 2) {
        D_8011D582 = 1;
        return TRUE;
    }
    return FALSE;
}

// Called when Taj swaps the active vehicle, is set to 1, each time.
void func_800521B8(s32 arg0) {
    D_8011D582 = arg0;
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
        tempObj = func_8001B7A8((Object *) racer, 1, &distance);
        if (tempObj && !gRaceStartTimer) {
            foundObj = turn_head_towards_object(obj, racer, tempObj, 400.0f * 400.0f);
        }
    }
    if (foundObj == FALSE) {
        tempObj = func_8001B7A8((Object *) racer, -1, &distance);
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
    racer->headAngleTarget -= racer->headAngleTarget >> 3;
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
        intendedAngle = (arctan2_f(diffX, diffZ) - (obj->segment.trans.y_rotation & 0xFFFF)) + 0x8000;
        WRAP(intendedAngle, -0x8000, 0x8000);
        CLAMP(intendedAngle, -0x3000, 0x3000);
        racer->headAngleTarget = intendedAngle;
        if ((racer->miscAnimCounter & 0x3F) < 0x1F) {
            racer->headAngleTarget = 0;
        }
        racer = (struct Object_Racer *) targetObj->unk64;
        intendedAngle = arctan2_f(diffX, diffZ) - (obj->segment.trans.y_rotation & 0xFFFF);
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

void func_8005250C(Object* obj, Object_Racer* racer, s32 updateRate) {
    s8 *balloonAsset;
    s32 angleVel;
    s32 newAngle;
    s32 actionStatus;

    angleVel = 0;
    if (racer->balloon_quantity > 0) {
        balloonAsset = (s8 *) get_misc_asset(MISC_ASSET_UNK0C);
        
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
                obj->unk74 |= 0x100000;
            } else {
                obj->unk74 |= 0x80000;
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
        obj->segment.unk38.byte.unk3B = 0;
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
void func_80052988(Object *obj, Object_Racer *racer, s32 action, s32 arg3, s32 duration, s32 arg5, s32 flags, s32 arg7) {
    arg5 *= arg7;

    if (gCurrentPlayerIndex == PLAYER_COMPUTER && action >= 3) {
        obj->segment.unk38.byte.unk3B = 0;
        racer->unk1F2 = 0;
    } else if (obj->segment.unk38.byte.unk3B == 0) {
        if (flags & 1) {
            if (obj->segment.animFrame > 40) {
                obj->segment.animFrame -= arg7 * 4;
                if (obj->segment.animFrame <= 40) {
                    obj->segment.unk38.byte.unk3B = action;
                    obj->segment.animFrame = arg3;
                }
            } else {
                obj->segment.animFrame += arg7 * 4;
                if (obj->segment.animFrame >= 40) {
                    obj->segment.unk38.byte.unk3B = action;
                    obj->segment.animFrame = arg3;
                }
            }
        } else {
            obj->segment.unk38.byte.unk3B = action;
            obj->segment.animFrame = arg3;
            racer->unk1F3 &= ~0x80;
        }
    } else if (obj->segment.unk38.byte.unk3B == action) {
        if (flags & 2) {
            if (racer->unk1F3 & 0x80) {
                obj->segment.animFrame -= arg5; //!@Delta
                if (obj->segment.animFrame <= 0) {
                    obj->segment.unk38.byte.unk3B = 0;
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
                obj->segment.unk38.byte.unk3B = 0;
                racer->unk1F2 = 0;
                obj->segment.animFrame = 40;
                racer->unk1F3 = 0;
            }
        }
    } else {
        obj->segment.animFrame = arg3;
        obj->segment.unk38.byte.unk3B = action;
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
        func_80072348(racer->playerIndex, 0);
    }
    angleVel = racer->y_rotation_vel;
    if (gCurrentPlayerIndex > PLAYER_COMPUTER) {
        if (gNumViewports < VIEWPORTS_COUNT_4_PLAYERS) {
            obj->unk74 |= 0x4FC00;
        } else {
            if (racer->wheel_surfaces[2] < SURFACE_NONE) {
                obj->unk74 |= 1 << (racer->wheel_surfaces[2] * 2);
            }
            if (racer->wheel_surfaces[3] < SURFACE_NONE) {
                obj->unk74 |= 2 << (racer->wheel_surfaces[3] * 2);
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
        func_8000488C((void *) racer->unk18);
    }
    if (racer->unk10) {
        func_8000488C((void *) racer->unk10);
    }
    if (racer->unk14) {
        func_8000488C((void *) racer->unk14);
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
        racer->velocity *= 0.87; //!@Delta
        obj->segment.y_velocity *= 0.9; //!@Delta
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
        racer->velocity *= 0.97; //!@Delta
        if (yStick > 50) {
            racer->velocity -= 0.2; //!@Delta
        }
        if (yStick < -50) {
            racer->velocity += 0.2; //!@Delta
        }
        canSteer = TRUE;
    }
    if (canSteer) {
        obj->unk74 = 0;
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
    angle = yStick - ((u16) obj->segment.trans.x_rotation);
    angle = angle > 0x8000 ? angle - 0xFFFF : angle;
    angle = angle < -0x8000 ? angle + 0xFFFF : angle;
    obj->segment.trans.x_rotation += (angle >> 3); //!@Delta
    obj->segment.y_velocity -= weight * updateRateF;
    if (racer->buoyancy == 0.0) {
        steerAngle = -obj->segment.y_velocity * 20.0;
        if (steerAngle < 50) {
            steerAngle = 50;
        }
        if (steerAngle > 127) {
            steerAngle = 127;
        }
        racer->unk1E0 = steerAngle;
    }
    obj->unk74 = 0;
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

    gCurrentRacerTransform.y_rotation = -racer->steerVisualRotation;
    gCurrentRacerTransform.x_rotation = -obj->segment.trans.x_rotation;
    gCurrentRacerTransform.z_rotation = -racer->x_rotation_vel;
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

GLOBAL_ASM("asm/non_matchings/racer/func_80053750.s")

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
                    racer->unk204 = 0x78;
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
    } else if (racer->unk1E2 > 0) {
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
    } else if (racer->unk1E2 > 2) {
        racer->unk1F0 = 0;
    }
    obj->segment.unk38.byte.unk3B = 0;
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
    obj->segment.trans.y_rotation = racer->steerVisualRotation + racer->y_rotation_vel;
    racer->z_rotation_vel += ((D_8011D558 - racer->z_rotation_vel) * updateRate) >> 4;
    obj->segment.trans.z_rotation = racer->x_rotation_vel + racer->z_rotation_vel;
    if (!racer->unk1F0) {
        gCurrentRacerTransform.y_rotation = racer->steerVisualRotation + racer->unk10C;
        gCurrentRacerTransform.x_rotation = 0;
        gCurrentRacerTransform.z_rotation = 0;
        gCurrentRacerTransform.x_position = 0.0f;
        gCurrentRacerTransform.y_position = 0.0f;
        gCurrentRacerTransform.z_position = 0.0f;
        gCurrentRacerTransform.scale = 1.0f;
        object_transform_to_matrix_2(mtx, &gCurrentRacerTransform);
        guMtxXFMF(mtx, racer->lateral_velocity, 0.0f, racer->velocity, &obj->segment.x_velocity, &tempVel, &obj->segment.z_velocity);
    }
    if (racer->magnetTimer) {
        obj->segment.x_velocity = gRacerMagnetVelX;
        obj->segment.z_velocity = gRacerMagnetVelZ;
    }
    if (!racer->approachTarget) {
        xVel = obj->segment.x_velocity;
        zVel = obj->segment.z_velocity;
        if (racer->unk1D2) {
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
            func_80055A84(obj, racer, updateRate);
    } else {
        func_80054FD0(obj, racer, updateRate);
    }
    if (!racer->unk201) {
        obj->unk74 = 0;
    } else if (racer->vehicleID < VEHICLE_TRICKY) {
        func_800AF714(obj, updateRate);
    }
    func_80053750(obj, racer, updateRateF);
    tempVel = 1.0f / updateRateF;
    xVel = (((obj->segment.trans.x_position - xTemp) - D_8011D548) * tempVel) - racer->unk84;
    obj->segment.y_velocity = (obj->segment.trans.y_position - yTemp) * tempVel;
    zVel = (((obj->segment.trans.z_position - zTemp) - D_8011D54C) * tempVel) - racer->unk88;
    gCurrentRacerTransform.y_rotation = -(racer->steerVisualRotation + racer->unk10C);
    gCurrentRacerTransform.x_rotation = -obj->segment.trans.x_rotation;
    gCurrentRacerTransform.z_rotation = -obj->segment.trans.z_rotation;
    gCurrentRacerTransform.x_position = 0.0f;
    gCurrentRacerTransform.y_position = 0.0f;
    gCurrentRacerTransform.z_position = 0.0f;
    gCurrentRacerTransform.scale = 1.0f;
    object_transform_to_matrix_2(mtx, &gCurrentRacerTransform);
    guMtxXFMF(mtx, xVel, 0.0f, zVel, &hVel, &tempVel, &yVel);
    if (racer->unk1D2) {
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
            obj->unk74 |= 1 << (racer->wheel_surfaces[2] * 2);
        }
        if (racer->wheel_surfaces[3] < SURFACE_NONE) {
            obj->unk74 |= 2 << (racer->wheel_surfaces[3] * 2);
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
    vel = (gCurrentRacerMiscAssetPtr[velocityS+1] * temp_f0_2) + (gCurrentRacerMiscAssetPtr[velocityS] * (1.0 - temp_f0_2));
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


GLOBAL_ASM("asm/non_matchings/racer/func_80054FD0.s")

void func_80055A84(Object *obj, Object_Racer *racer, UNUSED s32 updateRate) {
    f32 angleZ;
    f32 distance;
    s32 sp74;
    s32 flags;
    s32 temp_v1_2;
    f32 xTemp;
    f32 yTemp;
    f32 zTemp;
    s32 xRot;
    f32 angleX;
    f32 *temp_v0;
    Vec3f tempPos;
    s32 i;
    f32 sp40;
    s8 surface;
    s8 shouldSquish;

    if (obj->segment.trans.y_position > gCurrentCourseHeight) {
        obj->segment.trans.y_position = gCurrentCourseHeight;
    }
    temp_v0 =(f32 *) get_misc_asset(MISC_ASSET_UNK38);
    surface = -1;
    sp40 = temp_v0[racer->vehicleIDPrev];
    tempPos.x = obj->segment.trans.x_position;
    tempPos.y = obj->segment.trans.y_position;
    tempPos.z = obj->segment.trans.z_position;
    D_8011D548 = 0.0f;
    D_8011D54C = 0.0f;
    sp74 = 0;
    flags = 0;
    if (racer->playerIndex != PLAYER_COMPUTER || racer->vehicleIDPrev < VEHICLE_TRICKY) {
        flags = func_80017248(obj, 1, &sp74, &racer->unkD8, &tempPos.x, &sp40, &surface);
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
    sp74 = 0;
    racer->unk1E3 = func_80031600(&racer->unkD8.x, &tempPos.x, &sp40, &surface, 1, &sp74);
    racer->unk1E4 = flags;
    racer->unk1E3 |= flags;
    racer->unk1E2 = 0;
    if (racer->unk1E3) {
        racer->unk1E3 = 15;
        racer->unk1E2 = 4;
    }
    if (shouldSquish && sp74) {
        if (racer->squish_timer == 0) {
            racer->attackType = ATTACK_SQUISHED;
        } else {
            racer->squish_timer = 60;
        }
    }
    for (i = 0; i < 3; i++) {
        racer->unkD8.f[i] = tempPos.f[i];
    }
    racer->wheel_surfaces[0] = surface;
    i = 1;
    racer->wheel_surfaces[1] = surface;
    racer->wheel_surfaces[2] = surface;
    racer->wheel_surfaces[3] = surface;
    obj->segment.trans.x_position = racer->unkD8.x;
    obj->segment.trans.y_position = racer->unkD8.y;
    obj->segment.trans.z_position = racer->unkD8.z;
    if (racer->unk1E2) {
        func_8002ACD4(&xTemp, &yTemp, &zTemp);
        angleX = sins_f(-obj->segment.trans.y_rotation);
        angleZ = coss_f(-obj->segment.trans.y_rotation);
        distance = (xTemp * angleZ) + (zTemp * angleX);
        zTemp = (xTemp * angleX) - (zTemp * angleZ);
        temp_v1_2 = -(s16)(u16)arctan2_f(distance, yTemp);
        if (temp_v1_2 < 0x2000 && temp_v1_2 > -0x2000) {
            racer->x_rotation_vel = temp_v1_2;
        }
        xRot = -(s16)(u16)arctan2_f(zTemp, yTemp);
        if ((xRot < 0x2000) && (xRot > -0x2000)) {
            obj->segment.trans.x_rotation = xRot;
        }
        if (racer->vehicleID == VEHICLE_LOOPDELOOP) {
            if (1)
            xRot -= (u16) obj->segment.trans.x_rotation;
            WRAP(xRot, -0x8000, 0x8000);
            obj->segment.trans.x_rotation += xRot >> 2;
        }
    }
    if (racer->vehicleID != VEHICLE_LOOPDELOOP && racer->vehicleID != VEHICLE_PLANE && racer->vehicleID != VEHICLE_CARPET && racer->vehicleID != VEHICLE_SMOKEY) {
        CLAMP(racer->x_rotation_vel, -0x3400, 0x3400);
        CLAMP(obj->segment.trans.x_rotation, -0x3400, 0x3400);
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
    UNUSED s32 pad;
    s8 *miscAsset;
    Vertex *heldObjData;
    UNUSED s32 playerIndex;
    u16 soundID = SOUND_NONE;

    if (racer->held_obj != NULL) {
        heldObj = racer->held_obj;
        if (gCurrentButtonsPressed & Z_TRIG || racer->raceFinished || racer->attackType) {
            scaleY = 0;
            scaleZ = 0;
            if (obj->unk68[obj->segment.unk38.byte.unk3A] != NULL) {
                model = obj->unk68[obj->segment.unk38.byte.unk3A]->objModel;
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
            heldObj->segment.trans.x_position = obj->segment.trans.x_position + (racer->ox1 * scaleZ) + (racer->ox2 * scaleY);
            heldObj->segment.trans.y_position = obj->segment.trans.y_position + (racer->oy1 * scaleZ) + (racer->oy2 * scaleY);
            heldObj->segment.trans.z_position = obj->segment.trans.z_position + (racer->oz1 * scaleZ) + (racer->oz2 * scaleY);
            heldObj->segment.unk2C.half.lower = obj->segment.unk2C.half.lower;
            heldObj->segment.x_velocity = obj->segment.x_velocity * 0.7;
            heldObj->segment.y_velocity = obj->segment.y_velocity - 2.0;
            heldObj->segment.z_velocity = obj->segment.z_velocity * 0.7;
            heldObjData = (Vertex *) &heldObj->unk64->egg;
            ((Object_64 *) heldObjData)->egg.unkB = 2;
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
            miscAsset = (s8 *) get_misc_asset(MISC_ASSET_UNK0C);
            weaponID = miscAsset[(racer->balloon_type * 10) + (racer->balloon_level * 2)];
            if (miscAsset[(racer->balloon_type * 10) + (racer->balloon_level * 2)] == WEAPON_NONE) {
                racer->balloon_quantity = 0;
                return;
            }
            magnetTarget = NULL;
            if (gCurrentButtonsPressed & Z_TRIG) {
                func_800A74EC(318, racer->playerIndex);
            }
            if (racer->unk195) {
                if (racer->magnetTimer == 0) {
                    racer->unk195 = 0;
                } else {
                    return;
                }
            }
            if (gCurrentRacerInput & Z_TRIG || gCurrentButtonsReleased & Z_TRIG) {
                switch (weaponID) {
                    case WEAPON_ROCKET_HOMING:
                        intendedTarget = func_8005698C(obj, racer, &objDist); \
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
                objID = 29;
                if (gCurrentButtonsReleased & Z_TRIG) {
                    velocity = 30.0f;
                    switch (weaponID) {
                    case WEAPON_ROCKET_HOMING:
                        objDist = -10.0f;
                        objID = 229;
                        break;
                    case WEAPON_ROCKET:
                        objDist = -10.0f;
                        break;
                    case WEAPON_TRIPMINE:
                    case WEAPON_UNK_11:
                        objDist = 10.0f;
                        velocity = -2.0f;
                        objID = 14;
                        break;
                    case WEAPON_OIL_SLICK:
                        if (racer->vehicleID != VEHICLE_PLANE) {
                            objID = 130;
                        } else {
                            objID = 235;
                        }
                        objDist = 10.0f;
                        velocity = -2.0f;
                        break;
                    case WEAPON_BUBBLE_TRAP:
                        objDist = 10.0f;
                        velocity = -2.0f;
                        objID = 46;
                        intendedTarget = NULL;
                        break;
                    case WEAPON_NITRO_LEVEL_1:
                    case WEAPON_NITRO_LEVEL_2:
                    case WEAPON_NITRO_LEVEL_3:
                        switch(weaponID) {
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
                        if (racer->throttleReleased) {
                            racer->boostType |= EMPOWER_BOOST;
                        }
                        if (weaponID == WEAPON_NITRO_LEVEL_3) {
                            racer_play_sound(obj, SOUND_NITRO_LEVEL3_CHARGE);
                            func_800570A4(obj, 0x233, 0x1E);
                        } else {
                            racer_play_sound(obj, SOUND_NITRO_BOOST);
                        }
                        racer->balloon_quantity -= 1;
                        if (weaponID == WEAPON_NITRO_LEVEL_1) {
                            if (racer->raceFinished == FALSE) {
                                func_80072348(racer->playerIndex, 6);
                            }
                        } else if (racer->raceFinished == FALSE) {
                            func_80072348(racer->playerIndex, 8);
                        }
                        return;
                    case WEAPON_MAGNET_LEVEL_1:
                    case WEAPON_MAGNET_LEVEL_2:
                        racer->balloon_quantity -= 1;
                        if (racer->playerIndex != PLAYER_COMPUTER) {
                            if (intendedTarget != NULL) {
                                racer->magnetTimer = 90;
                                racer->unk184 = (weaponID - 5) >> 1;
                            }
                            if (racer->raceFinished == FALSE) {
                                func_80072348(racer->playerIndex, 15);
                            }
                        }
                        return;
                    case WEAPON_MAGNET_LEVEL_3:
                        racer->balloon_quantity -= 1;
                        racer->magnetTargetObj = NULL;
                        if (racer->playerIndex != PLAYER_COMPUTER) {
                            if (magnetTarget != NULL) {
                                magnetTarget->racer.unk195 = 1;
                                magnetTarget->racer.magnetTimer = 120;
                                magnetTarget->racer.magnetTargetObj = obj;
                                magnetTarget->racer.unk184 = 2;
                            }
                            if (racer->raceFinished == FALSE) {
                                func_80072348(racer->playerIndex, 15);
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
                    newObject.size = 8;
                    newObject.objectID = objID;
                    spawnedObj = spawn_object(&newObject, 1);
                    if (spawnedObj != NULL) {
                        spawnedObj->segment.unk3C_a.level_entry = NULL;
                        spawnedObj->segment.x_velocity = obj->segment.x_velocity - (racer->ox1 * velocity);
                        spawnedObj->segment.y_velocity = obj->segment.y_velocity - (racer->oy1 * velocity);
                        spawnedObj->segment.z_velocity = obj->segment.z_velocity - (racer->oz1 * velocity);
                        spawnedObj->segment.trans.y_rotation = obj->segment.trans.y_rotation;
                        spawnedObj->segment.trans.x_rotation = obj->segment.trans.x_rotation;
                        if (racer->vehicleID == VEHICLE_HOVERCRAFT && racer->unk1E5) {
                            if (spawnedObj->segment.trans.x_rotation > -0x400 && spawnedObj->segment.trans.x_rotation < 0x400) {
                                spawnedObj->segment.trans.x_rotation = 0;
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
                                play_sound_at_position(soundID, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, NULL);
                            } else {
                                if (racer->unk218) {
                                    func_8000488C(racer->unk218);
                                }
                                play_sound_spatial(soundID, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, (s32** ) &racer->unk218);
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

GLOBAL_ASM("asm/non_matchings/racer/func_8005698C.s")

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
            play_sound_global(SOUND_MAGNET_HUM, (void *) &racer->magnetSoundMask);
        }
    } else {
        racer->magnetTimer = 0;
        return;
    }
    diffX /= vel;
    diffZ /= vel;
    magnetTarget = racer->magnetTargetObj->unk64;
    vel = -magnetTarget->racer.velocity;
    if (vel < 8.0 && racer->unk195 == 0) {
        vel = 8.0f;
    }
    if (vel > 20.0) {
        vel = 20.0f;
    }
    gRacerMagnetVelX = (vel + 5.0f) * diffX;
    gRacerMagnetVelZ = (vel + 5.0f) * diffZ;
    if (magnetTarget->racer.shieldTimer != 0 && racer->unk195 == 0) {
        racer->magnetTimer = 0;
    }
}

/**
 * Play a spatial sound, emitting from the position of the racer object.
 */
void racer_play_sound(Object *obj, s32 soundID) {
    Object_Racer *racer = &obj->unk64->racer;
    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->unk108 == 0) {
        play_sound_spatial(soundID, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, NULL);
    }
}

void func_800570A4(Object *obj, s32 arg1, s32 arg2) {
    Object_Racer *temp = &obj->unk64->racer;
    temp->unk20E = arg1;
    temp->unk210 = arg2;
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
    if (tempRacer->unk108 == 0 && (!(flags & 0x80) || gCurrentPlayerIndex != PLAYER_COMPUTER)) {
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
            play_sound_at_position(soundIndex, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 4, &tempRacer->soundMask);
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
        if (racer->playerIndex == PLAYER_COMPUTER && (racer->aiSkill == AI_MASTER || (racer->aiSkill == AI_EXPERT && gStartBoostTime))) {
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
         func_80072348(racer->playerIndex, 6);
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

    if (racer->boost_sound & BOOST_UNK2) {
        racer->boost_sound &= ~BOOST_UNK2;
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

    gCurrentRacerTransform.y_rotation = obj->segment.trans.y_rotation;
    gCurrentRacerTransform.x_rotation = obj->segment.trans.x_rotation;
    gCurrentRacerTransform.z_rotation = 0;
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
    Object* bananaObj;
    f32 variance;

    if (!(get_filtered_cheats() & CHEAT_START_WITH_10_BANANAS)) {
        racer->unk188 = 0;
        if (racer->bananas < number) {
            number = racer->bananas;
        }
        if (number > 0 && number < 3) {
            angle[0] = racer->x_rotation_vel;
            angle[1] = obj->segment.trans.x_rotation;
            angle[2] = racer->steerVisualRotation;
            pos[0] = 0;
            pos[1] = 8;
            pos[2] = 12;
            s16_vec3_apply_object_rotation((ObjectTransform* ) angle, pos);
            newObject.x = pos[0] + (s32) obj->segment.trans.x_position;
            newObject.y = pos[1] + (s32) obj->segment.trans.y_position;
            newObject.z = pos[2] + (s32) obj->segment.trans.z_position;
            newObject.size = 8;
            newObject.objectID = BHV_OVERRIDE_POS;
            i = number;
            do {
                if (get_current_level_race_type() != RACETYPE_CHALLENGE) {
                    bananaObj = spawn_object(&newObject, 1);
                    if (bananaObj != NULL) {
                        bananaObj->segment.unk3C_a.level_entry = NULL;
                        banana = (Object_Banana *) bananaObj->unk64;
                        banana->unk9 = racer->vehicleID;
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
                        bananaObj->action = 1;
                    }
                }
                number--;
                racer->bananas--;
            } while(number > 0);
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

    if (gCurrentButtonsPressed & U_CBUTTONS && func_800A0190()) {
        gCameraObject->zoom++;
        if (gCameraObject->zoom > ZOOM_VERY_CLOSE) {
            gCameraObject->zoom = ZOOM_MEDIUM;
        }
        if (racer->playerIndex != PLAYER_COMPUTER) {
            func_80066060(racer->playerIndex, gCameraObject->zoom);
        }
        switch (gCameraObject->zoom) {
        case ZOOM_MEDIUM:
            play_sound_global(SOUND_MENU_BACK, NULL);
            break;
        case ZOOM_FAR:
            play_sound_global(SOUND_MENU_BACK2, NULL);
            break;
        default:
            play_sound_global(SOUND_UNK_6A, NULL);
            break;
        }
    }
    if (racer->raceFinished == TRUE && gCameraObject->mode != CAMERA_FINISH_CHALLENGE) {
            gCameraObject->mode = CAMERA_FINISH_RACE;
    }
    if (racer->unk108) {
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
        // When you finish a challenge, the camera will rotate around the player, or around a set path, if the player's been KO'd.
        update_camera_finish_challenge(updateRateF, obj, racer);
        break;
    case CAMERA_LOOP:
        // Used for loop-the-loops. Follows the face direction of the player exactly, the standard camera modes do not.
        update_camera_loop(updateRateF, obj, racer);
        break;
    case CAMERA_FINISH_RACE:
        // When you finish a race, the camera will go into a more cinematic mode, following the player.
        update_camera_finish_race(updateRateF, obj, racer);
        break;
    }
    dialogueAngle = gDialogueCameraAngle / 10240.0f; // Goes between 0-1
    gCameraObject->x_velocity = (((obj->segment.trans.x_position + (91.75 * racer->ox1) + (90.0 * racer->ox3)) - gCameraObject->trans.x_position) * dialogueAngle);
    gCameraObject->z_velocity = (((obj->segment.trans.z_position + (91.75 * racer->oz1) + (90.0 * racer->oz3)) - gCameraObject->trans.z_position) * dialogueAngle);
    gCameraObject->y_velocity = (((func_8003ACAC() + 48.5) - gCameraObject->trans.y_position) * dialogueAngle);
    gCameraObject->unk38 =  -gCameraObject->trans.x_rotation * dialogueAngle;
    gCameraObject->trans.x_position += gCameraObject->x_velocity;
    gCameraObject->trans.y_position += gCameraObject->y_velocity + gCameraObject->unk30;
    gCameraObject->trans.z_position += gCameraObject->z_velocity;
    if (!gRaceStartTimer && !gDialogueCameraAngle) {
        gCameraObject->x_velocity = gCameraObject->x_velocity * 0.95;
        gCameraObject->y_velocity = gCameraObject->y_velocity * 0.95;
        gCameraObject->z_velocity = gCameraObject->z_velocity * 0.95;
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
    if (D_8011D583) {
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
    gCameraObject->trans.y_rotation -= gDialogueCameraAngle;
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
            if (gRaceStartTimer == 0 && D_8011D582 == 0) {
                gCameraObject->x_velocity = xPos - gCameraObject->trans.x_position;
                gCameraObject->y_velocity = yPos - (gCameraObject->trans.y_position + gCameraObject->unk30);
                gCameraObject->z_velocity = zPos - gCameraObject->trans.z_position;
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
    racer->unk196 = (-racer->steerVisualRotation - racer->unk19E) + 0x8000;
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
    if (racer->unk1E2 > 2 || racer->unk1E5 != 0) {
        angle = (obj->segment.trans.x_rotation);
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
        tempAngle = angle - (u16) gCameraObject->trans.x_rotation;
        if (tempAngle > 0x8000) {
            tempAngle -= 0xFFFF;
        }
        if (tempAngle < -0x8000) {
            tempAngle += 0xFFFF;
        }
        gCameraObject->trans.x_rotation += (tempAngle * delta) >> 4;
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
    cosOffset = sins_f(gCameraObject->trans.x_rotation - baseAngle);
    sineOffset = coss_f(gCameraObject->trans.x_rotation - baseAngle);
    lateralOffset = gCameraObject->unk1C;
    lateralOffset = (lateralOffset * sineOffset) - (gCameraObject->unk20 * cosOffset);
    yVel = (gCameraObject->unk1C * cosOffset) + (gCameraObject->unk20 * sineOffset);
    sineOffset = sins_f(-racer->unk196 + 0x8000) * lateralOffset;
    cosOffset = coss_f(-racer->unk196 + 0x8000) * lateralOffset;
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
    tempVel = sins_f(racer->unk196 + 0x4000) * racer->unkC8;
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
    gCameraObject->trans.z_position = zOffset + (-coss_f(racer->unk196 + 0x4000) * racer->unkC8) + cosOffset;
    gCameraObject->trans.y_rotation = racer->unk196;
    newAngle = gCameraObject->trans.z_rotation;
    if ((racer->drift_direction && racer->brake > 0.0) || gDialogueCameraAngle) {
        newAngle = 0;
    }
    angle = obj->segment.trans.z_rotation;
    angleVel = (newAngle + angle) >> 4;
    gCameraObject->trans.z_rotation -= angleVel;
    if (gCameraObject->trans.z_rotation > 0x2000) {
        gCameraObject->trans.z_rotation = 0x2000;
    }
    if (gCameraObject->trans.z_rotation < -0x2000) {
        gCameraObject->trans.z_rotation = -0x2000;
    }
    gCameraObject->trans.y_position -= racer->unkC8 * sins_f(gCameraObject->trans.z_rotation);
    lateralOffset = (yOffset = gCameraObject->trans.x_position);
    segmentIndex = get_level_segment_index_from_position(lateralOffset, gCameraObject->trans.y_position, gCameraObject->trans.z_position);
    if (segmentIndex != -1) {
        gCameraObject->segmentIndex = segmentIndex;
    }
    racer->unk196 = gCameraObject->trans.y_rotation;
}
#else
GLOBAL_ASM("asm/non_matchings/racer/update_camera_car.s")
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

    gCameraObject->trans.y_rotation += 0x200;
    if (1) {} // Fakematch
    gCameraObject->trans.x_rotation = 0x400;
    gCameraObject->trans.z_rotation = 0;
    gCameraObject->unk1C = 150.0f;
    xOffset = sins_f(0x8000 - gCameraObject->trans.y_rotation) * gCameraObject->unk1C;
    zOffset = coss_f(0x8000 - gCameraObject->trans.y_rotation) * gCameraObject->unk1C;
    gCameraObject->trans.x_position = obj->segment.trans.x_position + xOffset;
    temp_f12 = (gCameraObject->trans.y_position - (obj->segment.trans.y_position + 45.0f)) * 0.25;
    if (temp_f12 < -2.0) {
        gCameraObject->trans.y_position = (gCameraObject->trans.y_position - (temp_f12 + 2.0));
    }
    if (temp_f12 > 0.0f) {
        gCameraObject->trans.y_position = obj->segment.trans.y_position + 45.0f;
    }
    gCameraObject->trans.z_position = obj->segment.trans.z_position + zOffset;
    segmentIndex = get_level_segment_index_from_position(gCameraObject->trans.x_position, gCameraObject->trans.y_position, gCameraObject->trans.z_position);
    if (segmentIndex != SEGMENT_NONE) {
        gCameraObject->segmentIndex = segmentIndex;
    }
    racer->unk196 = gCameraObject->trans.y_rotation;
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
    cam = func_8001BDD4(obj, &cameraID);
    if (!cam) {
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
    gCameraObject->trans.y_rotation = 0x8000 - atan2s(diffX, diffZ);
    gCameraObject->trans.x_rotation = atan2s((s32) diffY, (s32) distance);
    gCameraObject->trans.z_rotation = 0;
    gCameraObject->segmentIndex = get_level_segment_index_from_position(gCameraObject->trans.x_position, racer->oy1, gCameraObject->trans.z_position);
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
    gCameraObject->trans.y_rotation += ((((-atan2s(diffX, diffZ)) - gCameraObject->trans.y_rotation) + 0x8000) * updateRateF) >> 4;
    gCameraObject->trans.z_rotation -= ((s32) (gCameraObject->trans.z_rotation * updateRateF)) >> 4;
    gCameraObject->segmentIndex = get_level_segment_index_from_position(gCameraObject->trans.x_position, racer->oy1, gCameraObject->trans.z_position);
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

    if (splineEnd) {
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
    if ((func_8006BD88() == 0) && (racer->checkpoint >= temp_v0)) {
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
GLOBAL_ASM("asm/non_matchings/racer/func_80059208.s")
#endif

/**
 * Writes a human readable time to the passed arguments.
 * Used to visualise a standard time to the player for a stopwatch, or a record.
*/
void get_timestamp_from_frames(s32 frameCount, s32 *minutes, s32 *seconds, s32 *hundredths) {
    if (gVideoRefreshRate == REFRESH_50HZ) {
        frameCount = (f32)frameCount * 1.2;
    }
    // (REFRESH_60HZ * 60) is just frames per minute basically
    *minutes = frameCount / (REFRESH_60HZ * 60);
    *seconds = (frameCount - (*minutes * (REFRESH_60HZ * 60))) / REFRESH_60HZ;
    *hundredths = (((frameCount - (*minutes * (REFRESH_60HZ * 60))) - (*seconds * REFRESH_60HZ)) * 100) / REFRESH_60HZ;
}

void func_800598D0(void) {
    gGhostData[0] = allocate_from_main_pool_safe((sizeof(GhostNode) + sizeof(GhostDataFrame)) * MAX_NUMBER_OF_GHOST_NODES, COLOUR_TAG_RED);
    gGhostData[1] = (GhostHeader *) ((GhostNode *) gGhostData[0] + MAX_NUMBER_OF_GHOST_NODES);
    gGhostData[2] = NULL; // T.T. Ghost
    D_8011D5A0[0] = 0;
    D_8011D5A0[1] = 0;
    D_8011D5A0[2] = 0;
    D_8011D5A8[0] = 0;
    D_8011D5A8[1] = 0;
    D_8011D59D = 0;
    D_8011D5AC = -1;
}

void func_80059944(void) {
    D_8011D59C = D_8011D59D;
    D_8011D5A0[D_8011D59C] = 0;
    D_8011D5A8[D_8011D59C] = 0;
    D_8011D59E = 0;
}

void func_80059984(s32 arg0) {
    D_8011D59D = (s8)((D_8011D59C + 1) & 1);
    D_8011D5AC = arg0;
}

s32 func_800599A8(void) {
    return D_8011D5AC;
}

s32 func_800599B8(s32 arg0, s32 mapId, s16 arg2, s16 *arg3, s16 *arg4) {
    s32 temp_v0;
    s32 temp_t8;
    s16 sp2E;

    temp_t8 = (D_8011D59C + 1) & 1;
    temp_v0 = func_80074B34(arg0, (s16)mapId, arg2, arg3, arg4, &sp2E, gGhostData[temp_t8]);
    if (arg3 != 0) {
        if (temp_v0 == 0) {
            D_8011D5A0[temp_t8] = sp2E;
            D_8011D5AC = mapId;
        } else {
            D_8011D5AC = -1;
        }
    }

    return temp_v0;
}

/**
 * Loads T.T. ghost node data into gGhostData[2].
 * Returns 0 if successful, or 1 if an error occured.
 */
s32 load_tt_ghost(s32 ghostOffset, s32 size, s16 *outTime) {
    GhostHeader *ghost = allocate_from_main_pool_safe(size, COLOUR_TAG_RED);
    if (ghost != NULL) {
        load_asset_to_address(ASSET_TTGHOSTS, (u32) ghost, ghostOffset, size);
        if (gGhostData[2] != NULL) {
            free_from_memory_pool(gGhostData[2]);
        }
        gGhostData[2] = allocate_from_main_pool_safe(size - sizeof(GhostHeader), COLOUR_TAG_WHITE);
        if (gGhostData[2] != NULL) {
            *outTime = ghost->time;
            gTTGhostNodeCount = ghost->nodeCount;
            bcopy((u8 *)ghost + 8, gGhostData[2], size - sizeof(GhostHeader));
            free_from_memory_pool(ghost);
            return 0;
        }
        free_from_memory_pool(ghost);
    }
    return 1;
}

void free_tt_ghost_data(void) {
    if (gGhostData[2] != NULL) {
        free_from_memory_pool(gGhostData[2]);
    }
    gGhostData[2] = NULL;
}

s32 func_80059B7C(s32 controllerIndex, s32 mapId, s16 arg2, s16 arg3, s16 arg4) {
    return func_80075000(controllerIndex, (s16)mapId, arg2, arg3, arg4, D_8011D5A0[D_8011D59C], gGhostData[D_8011D59C]);
}

GLOBAL_ASM("asm/non_matchings/racer/func_80059BF0.s")

s16 func_80059E20(void) {
    return D_8011D5A8[D_8011D59C];
}

GLOBAL_ASM("asm/non_matchings/racer/set_ghost_position_and_rotation.s")

void func_8005A3B0(void) {
    D_8011D584 = 1;
}

void func_8005A3C0(void) {
    D_8011D583 = 1;
}

/**
 * Antipiracy function that loops over an address of a function a number of times.
 * It compares the number it gets to a generated checksum to determine if the game has been tampered with at all.
*/
void compare_balloon_checksums(void) {
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

/**
 * When you enter a door, take control away from the player.
 * Get the angle to the door object, and drive towards it.
 * After a timer hits 0, execute the transition.
 */
void racer_enter_door(Object_Racer* racer, s32 updateRate) {
    struct Object_Exit *temp_a3;
    f32 updateRateF;
    s32 angle;

    temp_a3 = (struct Object_Exit *) racer->unk108->unk64;
    racer->playerIndex = PLAYER_COMPUTER;
    angle = (u16) arctan2_f(temp_a3->unk0, temp_a3->unk8)  - (racer->steerVisualRotation & 0xFFFF);
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
    gCameraObject->trans.x_position += (temp_a3->unk0 * updateRateF) * 1.5;
    gCameraObject->trans.z_position += (temp_a3->unk8 * updateRateF) * 1.5;
    if (gCurrentStickX > 75) { gCurrentStickX = 75; gCurrentRacerInput |= A_BUTTON | B_BUTTON; } // Only matches if it's on the same line
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
    func_8006F388(1);
    if (racer->transitionTimer > 0) {
        racer->transitionTimer -= updateRate;
        if (racer->transitionTimer <= 0) {
            func_8006D968((s8* ) racer->unk108->segment.unk3C_a.level_entry);
            racer->transitionTimer = 0;
        }
    }
}

/**
 * The top level function for handling the actions of a computer controlled racer.
 * Mostly the same as how the player controlled one works, minus controller input and includes some decisionmaking logic.
*/
void update_AI_racer(Object *obj, Object_Racer *racer, s32 updateRate, f32 updateRateF) {
    s32 var_t2;
    Object **objects;
    s32 renderContext;
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
    renderContext = get_render_context();
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
    gCurrentRacerMiscAssetPtr = (f32 *) get_misc_asset(MISC_RACER_WEIGHT);
    gCurrentRacerWeightStat = gCurrentRacerMiscAssetPtr[racer->characterId] * 0.45;
    if (racer->unk204 > 0) {
        gCurrentRacerWeightStat = -0.02f;
    }
    gCurrentRacerMiscAssetPtr = (f32 *) get_misc_asset(MISC_RACER_HANDLING);
    gCurrentRacerHandlingStat = gCurrentRacerMiscAssetPtr[racer->characterId];
    gCurrentRacerMiscAssetPtr = (f32 *) get_misc_asset(MISC_ASSET_UNK0B);
    D_8011D574 = gCurrentRacerMiscAssetPtr[racer->characterId];
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
    
    if (is_taj_challenge() || func_80023568() || racer->vehicleID == VEHICLE_LOOPDELOOP || D_8011D544 > 120.0f || gRaceStartTimer != 0 || levelHeader->race_type & RACETYPE_CHALLENGE_BATTLE) {
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
    if (racer->unk204 > 0) {
        racer->unk204 -= updateRate;
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
            if (racer->unk204 > 0) {
                gCurrentRacerWeightStat = -gCurrentRacerWeightStat;
            }
            gCurrentStickY = 60;
        }
        if (racer->unk1FE == 2) {
            racer->unk84 += ((((sins_f(racer->unk1FF << 8) * 4) - racer->unk84) * 0.0625 * updateRateF));
            racer->unk88 += ((((coss_f  (racer->unk1FF << 8) * 4) - racer->unk88) * 0.0625 * updateRateF));
        } else {
            racer->unk84 -= racer->unk84 * 0.0625 * updateRateF;
            racer->unk88 -= racer->unk88 * 0.0625 * updateRateF;
        }
        gCurrentRacerHandlingStat = 1;
        gCurrentRacerMiscAssetPtr = (f32 *) get_misc_asset(MISC_ASSET_UNK21);
        D_8011D568 = (f32 *) get_misc_asset(obj->segment.header->unk5D);
        if ((obj->segment.y_velocity < 4.0) && ((racer->unk1E2 >= 3) || (racer->buoyancy != 0.0))) {
            racer->unk1F1 = 0;
        }
        if (racer->magnetTimer != 0) {
            racer_activate_magnet(obj, racer, updateRate);
        }
        if (racer->vehicleID != VEHICLE_HOVERCRAFT) {
            racer->unk1E5 = 0;
            racer->buoyancy = 0;
            D_8011D5AE = 0;
        } else {
            D_8011D5AE = func_8002B0F4(obj->segment.unk2C.half.lower, obj->segment.trans.x_position, obj->segment.trans.z_position, (struct TempStruct8 **) &D_8011D5B0);
        }
        func_8002ACC8(0);
        if ((racer->approachTarget != NULL) || (gRaceStartTimer != 0) || (racer->unk204 > 0)) {
            gCurrentStickX = 0;
            gCurrentStickY = 0;
            gCurrentRacerInput = 0;
            gCurrentButtonsReleased = 0;
            gCurrentButtonsPressed = 0;
        }
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
        if (renderContext != DRAW_MENU) {
            func_800050D0(obj, gCurrentButtonsPressed, gCurrentRacerInput, updateRate);
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
            if (racer->unk1E5 != 0) {
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
        if (renderContext != DRAW_MENU) {
            func_800050D0(obj, gCurrentButtonsPressed, gCurrentRacerInput, updateRate);
        }
    }
    if (racer->magnetTimer == 0) {
        if (racer->magnetSoundMask != NULL) {
            func_8000488C(racer->magnetSoundMask);
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
    racer->stretch_height = (racer->stretch_height + ((((racer->stretch_height_cap - racer->stretch_height) * 0.125) + temp_fv1_2) * updateRateF));
    if (((temp_fv1_2 < 0.0f) && (racer->stretch_height <= racer->stretch_height_cap)) || ((temp_fv1_2 > 0.0f) && (racer->stretch_height_cap <= racer->stretch_height))) {
        racer->stretch_height = racer->stretch_height_cap;
        racer->stretch_height_cap = 1.0f; 
    }
    var_t2 = ((racer->headAngleTarget - racer->headAngle) * updateRate) >> 3;
    CLAMP(var_t2, -0x800, 0x800)
    if (gAntiPiracyHeadroll) {
        racer->headAngle += gAntiPiracyHeadroll;
    } else {
        racer->headAngle += var_t2;
    }
    if (racer->shieldTimer > 0) {
        if (racer->shieldTimer > 60) {
            if (racer->shieldSoundMask) {
                update_spatial_audio_position(racer->shieldSoundMask, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
            } else if (racer->unk118 != 0) {
                play_sound_at_position(SOUND_SHIELD, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position, 1, &racer->shieldSoundMask);
            }
        } else {
            if (racer->shieldSoundMask) {
                func_800096F8(racer->shieldSoundMask);
                racer->shieldSoundMask = 0;
            }
        }
        racer->shieldTimer -= updateRate;
        if (racer->shieldTimer <= 0) {
            racer->shieldType = 0;
        }
    }
    if (racer->soundMask != 0) {
        update_spatial_audio_position(racer->soundMask, obj->segment.trans.x_position, obj->segment.trans.y_position, obj->segment.trans.z_position);
    }
    D_8011D584 = 0;
    if ((racer->unk150 != NULL) && (gRaceStartTimer == 0)) {
        s8 *temp;
        racer->unk150->segment.trans.x_position = obj->segment.trans.x_position;
        temp = (s8 *) get_misc_asset(MISC_ASSET_UNK00);
        racer->unk150->segment.trans.y_position = obj->segment.trans.y_position + temp[racer->characterId];
        racer->unk150->segment.trans.z_position = obj->segment.trans.z_position;
        racer->unk150->segment.trans.scale = obj->segment.unk30 / 265.0f;
        if (obj->segment.unk30 < 1500.0) {
            racer->unk150->segment.trans.unk6 |= 0x4000;
        }
        if (racer->unk150->segment.trans.scale < 1.0) {
            racer->unk150->segment.trans.scale = 1.0f;
        }
        racer->unk150 = NULL;
    }
    racer->unk1FE = 0xFF;
    set_racer_tail_lights(racer);
}

#ifdef NON_EQUIVALENT
//WIP
void func_8005B818(Object *obj, Object_Racer *racer, s32 updateRate, f32 updateRateF) {
    s32 sp11C;
    f32 sp100;
    f32 spEC;
    f32 spC0; //s32?
    f32 spD8;
    f32 spBC; //s32?
    f32 spB8;
    f32 spAC; //s32?
    f32 spA8; //s32?
    f32 spA4; //struct?
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp8C; //What sets this?
    LevelHeader *levelHeader; //sp80
    f32 *sp70;
    f32 *var_t0; //struct?
    f32 *var_a2;
    f32 *var_a3;
    f32 *var_t1;
    f32 *var_v1;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f24;
    f32 temp_f24_3;
    f32 temp_f26;
    f32 temp_f28;
    f32 var_f12;
    f32 var_f12_2;
    f32 var_f22;
    f32 var_f26;
    f32 var_f28;
    s16 temp_v0_4;
    s32 var_a0;
    s32 var_s0;
    s32 var_s2;
    s32 var_v0;
    s8 temp_v0_3;
    CheckpointNode *checkpoint;
    s32 i;

    gCurrentRacerMiscAssetPtr = get_misc_asset(MISC_ASSET_UNK21);
    levelHeader = get_current_level_header();
    sp11C = get_checkpoint_count();
    if (sp11C != 0) {
        racer->unk1C9 = 0;
        racer->unk1F5 = 0;
        racer->attackType = ATTACK_NONE;
        racer->lateral_velocity = 0;
        sp94 = 20.0f;
        if (racer->unk124 < -20.0f) {
            racer->unk124 = -20.0f;
        }
        if (racer->unk124 > sp94) {
            racer->unk124 = sp94;
        }
        var_f12 = sqrtf(((racer->unk124 * 0.025) + 0.595) / 0.004);
        var_v1 = &sp100;
        if (racer->boostTimer != 0) {
            var_f12 *= 1.3;
        }
        var_a2 = &spEC;
        if (racer->vehicleID == VEHICLE_HOVERCRAFT) {
            var_v0 = (racer->unk1BE & 0xFFFF) - (racer->unk1C2 & 0xFFFF);
            if (var_v0 >= 0x8001) {
                var_v0 += 0xFFFF0001;
            }
            if (var_v0 < -0x8000) {
                var_v0 += 0xFFFF;
            }
            if (var_v0 < 0) {
                var_v0 = -var_v0;
            }
            var_v0 -= 200;
            if (var_v0 < 0) {
                var_v0 = 0;
            }
            sp94 = (f32)var_v0 / 150.0;
            var_f12_2 = var_f12 - sp94;
            if (var_f12_2 < 2.0) {
                var_f12_2 = 2.0f;
            }
            if (racer->velocity < -var_f12_2) {
                racer->velocity = -var_f12_2;
            } else {
                racer->velocity += ((-var_f12_2 - racer->velocity) * 0.125);
            }
        } else {
            racer->velocity += ((-var_f12 - racer->velocity) * 0.25);
        }
        var_a3 = &spD8;
        var_a0 = racer->checkpoint - 2;
        var_t1 = &spB8;
        if (var_a0 < 0) {
            var_a0 += sp11C;
        }
        var_t0 = &spA4;
        if (var_a0 >= sp11C) {
            var_a0 -= sp11C;
        }
        for (i = 0; i < 1; i++) {
            checkpoint = find_next_checkpoint_node(var_a0, racer->unk1C8);
            var_v1[i] = checkpoint->x;
            var_a2[i] = checkpoint->y;
            var_a3[i] = checkpoint->z;
            var_t1[i] = checkpoint->unk2E[racer->unk1CA];
            var_t0[i] = checkpoint->unk32[racer->unk1CA];
            var_v1[i] += ((checkpoint->scale * checkpoint->rotationZFrac * checkpoint->unk2E[racer->unk1CA]));
            var_a2[i] += ((checkpoint->scale * checkpoint->unk32[racer->unk1CA]));
            var_a3[i] += ((checkpoint->scale * -checkpoint->rotationXFrac * checkpoint->unk2E[racer->unk1CA]));
            var_a0++;
            if (var_a0 == sp11C) {
                var_a0 = 0;
            }
        }
        
        if (racer->velocity < 0.0f) {
            racer->velocity = -racer->velocity;
        }
        var_s2 = 0;
        if (racer->unkAC == 0.0) {
            racer->unkAC = 0.01f;
        }
        for (var_s0 = 0; var_s0 < 2; var_s0++) {
            var_f22 = ((1.0 - racer->checkpoint_distance) + (racer->unkAC * updateRateF));
            if (var_f22 >= 1.0) {
                var_s2 = 1;
                var_f22--;
            }
            temp_f26 = cubic_spline_interpolation(&sp100, var_s2, var_f22, &sp9C);
            temp_f24 = cubic_spline_interpolation(&spEC, var_s2, var_f22, &sp98);
            temp_f28 = cubic_spline_interpolation(&spD8, var_s2, var_f22, &sp94);
            temp_f26 -= racer->unk68;
            temp_f24 -= racer->unk6C;
            temp_f28 -= racer->unk70;
            if (var_s0 == 0) {
                var_s2 = 0;
                temp_f12 = sqrtf((temp_f26 * temp_f26) + (temp_f24 * temp_f24) + (temp_f28 * temp_f28)) / updateRateF;
                if (temp_f12 != 0) {
                    racer->unkAC *= (sp8C / temp_f12);
                } else {
                    var_s0 = -1;
                    racer->unkAC += 0.01;
                }
            }
        }
        racer->unk68 += temp_f26;
        racer->unk6C += temp_f24;
        racer->unk70 += temp_f28;
        var_f26 = racer->unk68 - obj->segment.trans.x_position;
        var_f28 = racer->unk70 - obj->segment.trans.z_position;
        temp_f24_3 = racer->unk6C - obj->segment.trans.y_position;
        temp_f12_2 = sqrtf((var_f26 * var_f26) + (var_f28 * var_f28)) / updateRateF;
        if (temp_f12_2 > 35.0) {
            temp_f0_4 = (35.0 / temp_f12_2);
            var_f26 *= temp_f0_4;
            var_f28 *= temp_f0_4;
        }
        racer->checkpoint_distance = (1 - var_f22);
        if (var_s2 != 0) {
            racer->checkpoint += 1;
            if (racer->checkpoint >= sp11C) {
                racer->checkpoint = 0;
                if (racer->courseCheckpoint > 0) {
                    temp_v0_3 = racer->lap;
                    if (temp_v0_3 < 0x78) {
                        racer->lap = temp_v0_3 + 1;
                    }
                }
            }
            temp_v0_4 = racer->courseCheckpoint;
            if (temp_v0_4 < ((levelHeader->laps + 3) * sp11C)) {
                racer->courseCheckpoint = temp_v0_4 + 1;
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
        racer->unk1BA = (((spC0 - spBC) * var_f22) + spBC);
        racer->unk1BC = (((spAC - spA8) * var_f22) + spA8);
        temp_f0_5 = sqrtf((sp9C * sp9C) + (sp94 * sp94));
        if (temp_f0_5 != 0) {
            sp9C /= temp_f0_5;
            sp94 /= temp_f0_5;
            sp98 /= temp_f0_5;
            racer->steerVisualRotation = arctan2_f(sp9C, sp94) - 0x8000;
            obj->segment.trans.y_rotation = racer->steerVisualRotation;
            obj->segment.trans.x_rotation = arctan2_f(sp98, 1.0f);
        }
        racer->unk1C2 = racer->unk1BE;
        racer->unk1C4 = racer->unk1C0;
        racer->unk1BE = racer->steerVisualRotation;
        racer->unk1C0 = obj->segment.trans.x_rotation;
        if (move_object(obj, var_f26, temp_f24_3, var_f28)) {
            obj->segment.trans.x_position += var_f26;
            obj->segment.trans.y_position += temp_f24_3;
            obj->segment.trans.z_position += var_f28;
        }
        if (temp_f12_2 < 20.0) {
            obj->segment.y_velocity = -1.0f;
            obj->segment.x_velocity = var_f26 / updateRateF;
            obj->segment.z_velocity = var_f28 / updateRateF;
        }
        func_80042D20(obj, racer, updateRate);
        handle_racer_items(obj, racer, updateRate);
        racer->unk1E5 = 0;
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
        obj->unk74 = 0;
        func_800AF714(obj, updateRate);
    }
}
#else
GLOBAL_ASM("asm/non_matchings/racer/func_8005B818.s")
#endif

// This gets called if an anti-piracy checksum fails in func_8005F850.
/**
 * Triggered upon failure of an anti-tamper test. Sets the first index of the surface speed
 * table to an unreasonable value, wrecking drivability while on it.
 */
void antipiracy_modify_surface_traction_table(void) {
    gSurfaceTractionTable[SURFACE_DEFAULT] = 0.05f;
}

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
