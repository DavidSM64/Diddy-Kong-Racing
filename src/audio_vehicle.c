/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80004B40 */

#include "audio_vehicle.h"

#include "types.h"
#include "macros.h"
#include "audio_spatial.h"
#include "audiosfx.h"
#include "objects.h"
#include "joypad.h"
#include "racer.h"
#include "PR/libaudio.h"
#include "game_ui.h"
#include "math_util.h"
#include "printf.h"

/************ .data ************/

u8 gVehicleSounds = TRUE;
s32 D_800DC6D4 = 0; // Currently unknown, might be a different type.
s32 D_800DC6D8 = 1; // Currently unknown, might be a different type.

/*******************************/

/************ .bss ************/

VehicleSoundData *D_80119C30[2];
VehicleSoundData *gRacerSound;
Object_Racer *gSoundRacerObj;
SoundData *D_80119C40; // This should be in audio_spatial?
SoundMask **gSoundMaskHeapUsed;
unk80119C48 **gSoundMaskHeap; // 0x24 struct size - 0x5A0 total size - should be 40 elements
u8 gFreeMasks;
SoundMask **gSoundMaskHeapFree;
s32 D_80119C54;           // Padding?
unk80119C58 **D_80119C58; // Struct of size in func_8000A184 = 0x180 = 384 bytes | Ambient Sounds
unk80119C58 **D_80119C5C; // Struct of size in func_8000A184 = 0x180 = 384 bytes Likely the same as above
f32 D_80119C60[670];      // array size of 672 looks to be required for func_80008174
unk8011A6D8 *D_8011A6D8;  // unk8011A6D8[] | Reverb stuff
unk8011A6D8 **D_8011A6DC; // Struct of size 0xC0
f32 D_8011A6E0[334];
s32 gAudioLinesOff;
s32 D_8011AC1C;

/******************************/

#ifdef NON_EQUIVALENT
// racer_sound_init
VehicleSoundData *func_80004B40(s8 characterId, s8 vehicleId) {
    u16 temp_a1;
    s32 temp_s1;
    u16 var_a0_2;
    s32 var_a3;
    s32 var_a3_2;
    s32 var_s0_2;
    VehicleSoundData *var_a2;
    s32 *addrPtr;
    unkAudioAsset *temp_v0_2;
    VehicleSoundData *temp_v0_3;
    u8 *memset;
    VehicleSoundData *var_a0;
    unkAudioAsset *var_a1;
    unkAudioAsset *var_v1_2;
    s32 i;
    f32 new_var;

    if (characterId >= 11) {
        characterId = 11;
    }

    if (D_800DC6D8 != 0) {
        for (i = 0; i < 2; i++) {
            D_80119C30[i] = NULL;
        }
        D_800DC6D8 = 0;
    }
    addrPtr = (s32 *) load_asset_section_from_rom(ASSET_AUDIO_TABLE);
    vehicleId *= 10;
    temp_s1 = addrPtr[ASSET_AUDIO_7] + ((vehicleId + characterId) * sizeof(unkAudioAsset));
    temp_v0_2 = (unkAudioAsset *) mempool_alloc_safe(sizeof(unkAudioAsset), COLOUR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, (u32) temp_v0_2, temp_s1, sizeof(unkAudioAsset));
    temp_v0_3 = (VehicleSoundData *) mempool_alloc_safe(sizeof(VehicleSoundData), COLOUR_TAG_CYAN);

    // Not really sure this is right...
    memset = temp_v0_3;
    for (var_a3 = 0; var_a3 < sizeof(VehicleSoundData); var_a3++) {
        memset[var_a3] = 0;
    }

    var_s0_2 = 0;
    temp_v0_3->unk36 = temp_v0_2->unk36;
    temp_v0_3->unk37 = temp_v0_2->unk37;
    temp_v0_3->unk38 = temp_v0_2->unk38;
    temp_v0_3->unk39 = temp_v0_2->unk39;
    temp_v0_3->unk64 = temp_v0_2->unk3A;
    temp_v0_3->throttlePitchCeil = temp_v0_2->unk46 / 10000.0f;
    temp_v0_3->throttlePitchVel = temp_v0_2->unk3E / 10000.0f;
    temp_v0_3->throttlePitchDecay = temp_v0_2->unk40 / 10000.0f;
    temp_v0_3->unkC0 = temp_v0_2->unk42 / 10000.0f;
    temp_v0_3->unkC4 = temp_v0_2->unk44 / 10000.0f;
    temp_v0_3->unkBC = temp_v0_2->unk3C / 10000.0f;
    temp_v0_3->unkB8 = temp_v0_2->unk3B;
    temp_v0_3->brakeSound = 0;
    temp_v0_3->unkCC = temp_v0_2->unk48 / 10000.0f;
    do {
        var_a3_2 = 1;
        temp_v0_3->unk0[0] = temp_v0_2->unk0;
        var_v1_2 = &temp_v0_2[1];
        temp_v0_3->unk4[0][0] = temp_v0_2->unk4[2];
        var_a1 = temp_v0_2 + 2;
        temp_v0_3->unk18[0] = temp_v0_2->unk18;
        var_a0 = temp_v0_3 + 1;
        temp_v0_3->unkC[0][0] = temp_v0_2->unkC;
        var_a2 = &temp_v0_3->unk0[1];
        temp_v0_3->unk2C[0] = temp_v0_2->unk2C;
    loop_10:
        var_a3_2 += 2;
        var_a0->unk4[0][0] = (u8) var_v1_2->unk4[0];
        var_v1_2 += 2;
        var_a2->unk18[0] = (u16) var_a1->unk18[0];
        var_a1 += 4;
        var_a0->unkC[0][0] = (u8) var_v1_2->unkC;
        var_a0 += 2;
        var_a0->unk2A[0] = (u8) var_v1_2->unk2A[0];
        var_a2 += 4;
        var_a0->unk0[1] = (u8) var_v1_2->unk3;
        var_a2->unk16 = (u16) var_a1->unk16;
        var_a0->unkC[0][1] = (u8) var_v1_2->unkD;
        var_a0->unk2A[1] = (u8) var_v1_2->unk2A[1];
        if (var_a3_2 != 5) {
            goto loop_10;
        }
        var_s0_2 += 2;
        temp_v0_2 += 2;
        temp_v0_2 += 5;
        temp_v0_2 += 0xA;
        temp_v0_3 += 5;
        temp_v0_3 += 0xA;
        temp_v0_3 += 5;
        temp_v0_2 += 5;
        temp_v0_3 += 0xA;
        temp_v0_2 += 0xA;
        temp_v0_3 += 2;
    } while (var_s0_2 < 4);
    temp_v0_3->unk74 = 0;
    temp_v0_3->unk6C[0] = 0.0f;
    temp_v0_3->basePitch = temp_v0_2->unk4A / 100.0f;
    if (vehicleId == 0) {
        temp_v0_3->unk54[0] = temp_v0_3->unk2C[0];
        temp_v0_3->unk5C[0] = temp_v0_3->unk18[0] / 10000.0f;
        temp_v0_3->unk54[1] = temp_v0_3->unk31;
        temp_v0_3->unk5C[1] = temp_v0_3->unk22 / 10000.0f;
    } else {
        temp_v0_3->unk5C[0] = temp_v0_3->basePitch;
        temp_a1 = temp_v0_3->unk5C[0] * 10000.0f;
        for (var_a0_2 = 0; temp_a1 >= temp_v0_3->unk18[var_a0_2] && var_a0_2 < 4; var_a0_2++) {}
        var_a0_2--;
        new_var = (temp_a1 - temp_v0_3->unk18[var_a0_2]) /
                  ((f32) (temp_v0_3->unk18[var_a0_2 + 1] - temp_v0_3->unk18[var_a0_2]));
        temp_v0_3->unk54[0] =
            temp_v0_3->unk2C[var_a0_2] + (temp_v0_3->unk2C[var_a0_2 + 1] - temp_v0_3->unk2C[var_a0_2]) * new_var;
    }
    mempool_free(addrPtr);
    mempool_free((void *) temp_v0_2);
    return temp_v0_3;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/audio_vehicle/func_80004B40.s")
#endif

/**
 * Update the sound of the engine and braking during gameplay, for later.
 * Check which vehicle is being used, update the position of the audio,
 * then call a function to handle that particular vehicles audio.
 */
void racer_sound_update(Object *obj, u32 buttonsPressed, u32 buttonsHeld, s32 updateRate) {
    if (gVehicleSounds) {
        gSoundRacerObj = &obj->unk64->racer;
        gRacerSound = (VehicleSoundData *) gSoundRacerObj->vehicleSound;
        if (gRacerSound != NULL) {
            if (get_race_countdown()) {
                if (gSoundRacerObj->playerIndex != PLAYER_COMPUTER) {
                    buttonsHeld = get_buttons_held_from_player(gSoundRacerObj->playerIndex);
                    buttonsPressed = get_buttons_pressed_from_player(gSoundRacerObj->playerIndex);
                }
            }
            if (gRacerSound->unk0[0] == 0) {
                gRacerSound->racerPos.x = -32000.0f;
                gRacerSound->racerPos.y = -32000.0f;
                gRacerSound->racerPos.z = -32000.0f;
            } else {
                gRacerSound->racerPos.x = obj->segment.trans.x_position;
                gRacerSound->racerPos.y = obj->segment.trans.y_position;
                gRacerSound->racerPos.z = obj->segment.trans.z_position;
                switch (gSoundRacerObj->vehicleIDPrev) {
                    case VEHICLE_HOVERCRAFT:
                        racer_sound_hovercraft(obj, buttonsPressed, buttonsHeld, updateRate);
                        break;
                    case VEHICLE_PLANE:
                        func_800063EC(obj, buttonsPressed, buttonsHeld, updateRate);
                        break;
                    default:
                        func_80005254(obj, buttonsPressed, buttonsHeld, updateRate);
                        break;
                }
            }
        }
    }
}

#ifdef NON_EQUIVALENT
// Scratch: https://decomp.me/scratch/w3w2c
void func_80005254(Object *obj, u32 buttonsPressed, u32 buttonsHeld, s32 updateRate) {
    f32 sp6C;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    u8 temp_f4;
    f32 var_f0;
    f32 var_f12;
    f32 var_f14;
    f32 var_f20;
    f32 var_f2;
    s32 temp_a0_4;
    s32 var_s0;
    s32 outerLoop;
    s32 innerLoop;
    s32 var_v1_3;

    if (gSoundRacerObj->unk1FB != 0) {
        var_f0 = 12.0f;
    } else {
        var_f0 = gSoundRacerObj->velocity;
    }
    if (var_f0 < 0.0f) {
        var_f0 = -var_f0;
    }
    var_s0 = (var_f0 / 16) * 100;
    var_s0 += 5;
    if (var_s0 > 100) {
        var_s0 = 100;
    }
    for (outerLoop = 0; outerLoop < 1; outerLoop++) {
        if ((gRacerSound->unk0[outerLoop]) != 0) {
            innerLoop = 0;
            while ((var_s0 < gRacerSound->unkC[outerLoop][innerLoop] ||
                    var_s0 > gRacerSound->unkC[outerLoop][innerLoop + 1]) &&
                   innerLoop < 4) {
                innerLoop++;
            }

            temp_f14 = (var_s0 - gRacerSound->unkC[0][innerLoop]) /
                       ((f32) (gRacerSound->unkC[0][innerLoop + 1] - gRacerSound->unkC[0][innerLoop]));
            temp_f4 = gRacerSound->unk2C[outerLoop] +
                      (gRacerSound->unk2C[outerLoop + 1] - gRacerSound->unk2C[outerLoop]) * temp_f14;

            innerLoop = 0;
            while ((var_s0 < gRacerSound->unk4[0][innerLoop] || var_s0 > gRacerSound->unk4[0][innerLoop + 1]) &&
                   innerLoop < 4) {
                innerLoop++;
            }

            temp_f14 = (var_s0 - gRacerSound->unk4[0][innerLoop]) /
                       ((f32) (gRacerSound->unk4[0][innerLoop + 1] - gRacerSound->unk4[0][innerLoop]));
            temp_f16 = gRacerSound->unk18[innerLoop] / 10000.0f;
            temp_f18 = gRacerSound->unk18[innerLoop + 1] / 10000.0f;
            if (var_s0 > 50 && gSoundRacerObj->bananas != 0) {
                if (gSoundRacerObj->bananas <= 10) {
                    var_v1_3 = gSoundRacerObj->bananas;
                } else {
                    var_v1_3 = 10;
                }
                if (gRacerSound->bananaPitch < (0.05 * var_v1_3)) {
                    gRacerSound->bananaPitch += ((0.05 * var_v1_3) / (var_v1_3 * 64));
                } else if (gRacerSound->bananaPitch > (0.05 * var_v1_3)) {
                    gRacerSound->bananaPitch = (0.05 * var_v1_3);
                }
                var_f2 = ((temp_f18 - temp_f16) * temp_f14) + temp_f16 + gRacerSound->bananaPitch;
            } else {
                gRacerSound->bananaPitch *= 0.95;
                var_f2 = ((temp_f18 - temp_f16) * temp_f14) + temp_f16 + gRacerSound->bananaPitch;
            }
            if (gSoundRacerObj->drift_direction != 0) {
                gRacerSound->unk40 += ((0.13 - gRacerSound->unk40) / 8);
            } else {
                gRacerSound->unk40 /= 4;
            }
            var_f2 += gRacerSound->unk40;
            if ((gSoundRacerObj->groundedWheels == 0) && (gSoundRacerObj->playerIndex != PLAYER_COMPUTER)) {
                var_f2 += 0.3;
            }
            var_f12 = (var_f2 - gRacerSound->unk5C[outerLoop]) / 2;
            var_f14 = (temp_f4 - gRacerSound->unk54[outerLoop]) / 2;
            if (gSoundRacerObj->playerIndex != PLAYER_COMPUTER) {
                if (get_random_number_from_range(0, 10) < 7) {
                    gRacerSound->unk90 = (gRacerSound->unk90 + get_random_number_from_range(0, 10)) - 5;
                    if (gRacerSound->unk90 > 5) {
                        gRacerSound->unk90 = 5;
                    } else if (gRacerSound->unk90 < -5) {
                        gRacerSound->unk90 = -5;
                    }
                }
                var_f12 += 0.02 * (gRacerSound->unk90 / 5.0f);
                var_f14 += 5.0f * (gRacerSound->unk90 / 5.0f);
            }
            if ((buttonsHeld & A_BUTTON) && (gRacerSound->enginePitch < 0.4)) {
                gRacerSound->enginePitch += ((f32) updateRate * 0.01);
                if (gRacerSound->enginePitch > 0.4) {
                    gRacerSound->enginePitch = 0.4f;
                }
            }
            if (!(buttonsHeld & A_BUTTON) && (gRacerSound->enginePitch > 0.0f)) {
                gRacerSound->enginePitch -= ((f32) updateRate * 0.005);
                if (gRacerSound->enginePitch < 0.0f) {
                    gRacerSound->enginePitch = 0.0f;
                }
            }
            gRacerSound->unk5C[outerLoop] += var_f12;
            if (buttonsHeld & A_BUTTON) {
                gRacerSound->unk54[outerLoop] += var_f14;
            } else {
                gRacerSound->unk54[outerLoop] = 35.0f;
            }
        }
    }
    if (((gSoundRacerObj->unk10 != 0) || (gSoundRacerObj->unk14 != 0) || !(buttonsHeld & B_BUTTON) ||
         (gSoundRacerObj->velocity > -0.1) || (gSoundRacerObj->vehicleID == 4)) &&
        (gRacerSound->unkA8 != 0)) {
        sound_stop(gRacerSound->unkA8);
        gRacerSound->unkA8 = 0;
    } else if ((buttonsPressed & B_BUTTON) && (gRacerSound->unkA8 == 0) && (gSoundRacerObj->playerIndex >= 0)) {
        if (gSoundRacerObj->velocity < 0.0f) {
            var_f20 = -gSoundRacerObj->velocity;
        } else {
            var_f20 = gSoundRacerObj->velocity;
        }
        if (var_f20 > 12.0f) {
            var_f20 = 12.0f;
        }
        func_80001F14(25, &gRacerSound->unkA8);
        sp6C = (((var_f20 * 0.5) / 12.0) + 0.5);
        temp_a0_4 = gRacerSound->unkA8;
        if (temp_a0_4 != 0) {
            sound_event_update(temp_a0_4, 16, *((u32 *) &sp6C));
        }
        gRacerSound->unkAC = 110;
        gRacerSound->unkD0 = 0;
    }
    if (gRacerSound->unkA8 != 0) {
        if (gSoundRacerObj->groundedWheels == 0) {
            gRacerSound->unkD0 += updateRate;
        } else {
            gRacerSound->unkD0 = 0;
        }
        if (gRacerSound->unkD0 >= 10) {
            sound_event_update(gRacerSound->unkA8, 8, 0);
        } else {
            sound_event_update(gRacerSound->unkA8, 8, gRacerSound->unkAC << 8);
            func_80009B7C((s32 *) gRacerSound->unkA8, obj->segment.trans.x_position, obj->segment.trans.y_position,
                          obj->segment.trans.z_position);
        }
    }
    gRacerSound->unkA0 = var_s0;
    if ((buttonsHeld & A_BUTTON) != 0) {
        gRacerSound->unk98 = gRacerSound->unk54[0];
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/audio_vehicle/func_80005254.s")
#endif

/**
 * Update the engine sounds for the hovercraft.
 * Uses velocity, banana count and ground contact to decide what pitch to use.
 * Those values are calculated in this function.
 */
void racer_sound_hovercraft(Object *obj, UNUSED u32 buttonsPressed, u32 buttonsHeld, s32 updateRate) {
    UNUSED s32 pad;
    f32 velocity;
    f32 new_var;
    u16 temp_f10;
    f32 angleSine;
    f32 var_f18;
    f32 pitch;
    s32 angleDiff;
    s32 bananaPitch;
    u8 var_t0;
    u8 i;

    if (get_race_countdown() == 0) {
        velocity = sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) +
                         (obj->segment.z_velocity * obj->segment.z_velocity));
    } else {
        velocity = 0.0f;
    }
    pitch = gRacerSound->basePitch;
    if (buttonsHeld & A_BUTTON) {
        gRacerSound->throttlePitch += gRacerSound->throttlePitchVel * updateRate;
        if (gRacerSound->throttlePitch > gRacerSound->throttlePitchCeil) {
            gRacerSound->throttlePitch = gRacerSound->throttlePitchCeil;
        }
    } else {
        gRacerSound->throttlePitch -= gRacerSound->throttlePitchDecay * updateRate;
    }
    if (gRacerSound->throttlePitch < 0.0f) {
        gRacerSound->throttlePitch = 0.0f;
    }

    angleDiff = (-gSoundRacerObj->cameraYaw - (gSoundRacerObj->steerVisualRotation & 0xFFFF)) + 0x8000;
    WRAP(angleDiff, -0x8000, 0x8000);
    angleSine = sins_f(angleDiff);
    angleSine = ABSF(angleSine);
    if (check_if_showing_cutscene_camera() == FALSE && get_race_countdown() == 0) {
        var_f18 = (gRacerSound->unkBC * angleSine * velocity) / 15.0;
    } else {
        var_f18 = 0.0f;
    }
    if (race_starting() == FALSE) {
        gRacerSound->throttlePitch = 0.0f;
    }
    if (velocity > 10.0) {
        velocity -= 10.0;
    } else {
        velocity = 0.0f;
    }
    //!@Delta: This entire block is not timing correct.
    if (velocity != 0.0 && gSoundRacerObj->bananas != 0) {
        if (gSoundRacerObj->bananas <= 10) {
            bananaPitch = gSoundRacerObj->bananas;
        } else {
            bananaPitch = 10;
        }
        if (gRacerSound->bananaPitch < 0.05 * bananaPitch) {
            gRacerSound->bananaPitch += (0.05 * bananaPitch) / (bananaPitch * 64);
        } else if (gRacerSound->bananaPitch > 0.05 * bananaPitch) {
            gRacerSound->bananaPitch = 0.05 * bananaPitch;
        }
        pitch += gRacerSound->bananaPitch;
    } else {
        gRacerSound->bananaPitch *= 0.95;
        pitch += gRacerSound->bananaPitch;
    }
    pitch += ((velocity * gRacerSound->unkCC) + var_f18 + gRacerSound->throttlePitch);
    if (gSoundRacerObj->playerIndex != PLAYER_COMPUTER && gSoundRacerObj->groundedWheels == 0 &&
        gSoundRacerObj->waterTimer < 4) {
        if (get_race_countdown() == 0) {
            pitch += 0.3;
        }
    }
    gRacerSound->unk5C[0] += ((pitch - gRacerSound->unk5C[0]) / 8);
    if (gRacerSound->unk5C[0] > (0x7FFF / 5000.0)) {
        gRacerSound->unk5C[0] = (0x7FFF / 5000.0); // 6.5534
    }
    temp_f10 = gRacerSound->unk5C[0] * 10000.0f;
    for (i = 0; temp_f10 >= gRacerSound->unk18[i] && i < 4; i++) {}
    if (i == 4) {
        var_t0 = gRacerSound->unk2C[i];
    } else {
        if (i != 0) {
            i--;
        }
        new_var = (temp_f10 - gRacerSound->unk18[i]) / ((f32) (gRacerSound->unk18[i + 1] - gRacerSound->unk18[i]));
        var_t0 = gRacerSound->unk2C[i] + (gRacerSound->unk2C[i + 1] - gRacerSound->unk2C[i]) * new_var;
    }
    gRacerSound->unk54[0] += ((var_t0 - gRacerSound->unk54[0]) / 8);
    gRacerSound->unk5C[1] = 1.0f;
    gRacerSound->unk54[1] = 0.0f;
}

#ifdef NON_EQUIVALENT
void func_800063EC(Object *obj, UNUSED u32 buttonsPressed, u32 buttonsHeld, s32 updateRate) {
    f32 sp28;
    f32 var_f2;
    u16 temp_f10;
    f32 var_f14;
    f32 temp_f8;
    f32 var_f18;
    u8 i;
    s32 var_a0;
    u8 var_t0;
    f32 xVel;
    f32 yVel;
    f32 zVel;

    if (get_race_countdown() == 0) {
        xVel = obj->segment.x_velocity;
        zVel = obj->segment.z_velocity;
        yVel = obj->segment.y_velocity;
        var_f18 = sqrtf((xVel * xVel) + (zVel * zVel) + (yVel * yVel));
        // var_f18 = sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) + (obj->segment.z_velocity *
        // obj->segment.z_velocity) + (obj->segment.y_velocity * obj->segment.y_velocity));
    } else {
        var_f18 = 0.0f;
    }
    if (var_f18 < 2.0f) {
        gRacerSound->unk54[0] += ((gRacerSound->unk37 - gRacerSound->unk54[0]) / 8);
    } else {
        temp_f10 = gRacerSound->unk5C[0] * 10000.0f;
        for (i = 0; temp_f10 >= gRacerSound->unk18[i] && i < 4; i++) {}
        if (i == 4) {
            var_t0 = gRacerSound->unk2C[i];
        } else {
            if (i != 0) {
                i--;
            }
            temp_f8 = (temp_f10 - gRacerSound->unk18[i]) / ((f32) (gRacerSound->unk18[i + 1] - gRacerSound->unk18[i]));
            var_t0 = gRacerSound->unk2C[i] + (gRacerSound->unk2C[i + 1] - gRacerSound->unk2C[i]) * temp_f8;
        }
        gRacerSound->unk54[0] += ((var_t0 - gRacerSound->unk54[0]) / 8);
    }
    var_f14 = gRacerSound->basePitch;
    if (buttonsHeld & A_BUTTON) {
        gRacerSound->throttlePitch += gRacerSound->throttlePitchVel * (f32) updateRate;
        if (gRacerSound->throttlePitchCeil < gRacerSound->throttlePitch) {
            gRacerSound->throttlePitch = gRacerSound->throttlePitchCeil;
        }
    } else {
        gRacerSound->throttlePitch -= gRacerSound->throttlePitchDecay * (f32) updateRate;
    }
    if (gRacerSound->throttlePitch < 0) {
        gRacerSound->throttlePitch = 0;
    }
    if (race_starting() == 0) {
        gRacerSound->throttlePitch = 0.0f;
    }
    var_f14 += gRacerSound->throttlePitch;
    sp28 = sins_f(obj->segment.trans.rotation.x_rotation);
    var_f2 = sins_f(obj->segment.trans.rotation.z_rotation) * gRacerSound->unkC0;
    if (var_f2 < 0.0f) {
        var_f2 = -var_f2;
    }
    if (var_f18 > 10.0) {
        var_f18 -= 10.0;
    } else {
        var_f18 = 0.0;
    }
    var_f14 += ((gRacerSound->unkC4 * sp28) + var_f2);
    var_f14 += (var_f18 * gRacerSound->unkCC);
    if ((var_f18 != 0.0) && (gSoundRacerObj->bananas != 0)) {
        if (gSoundRacerObj->bananas <= 10) {
            var_a0 = gSoundRacerObj->bananas;
        } else {
            var_a0 = 10;
        }
        if (gRacerSound->bananaPitch < (0.05 * var_a0)) {
            gRacerSound->bananaPitch += ((0.05 * var_a0) / (var_a0 * 64));
        } else if (gRacerSound->bananaPitch > (0.05 * var_a0)) {
            gRacerSound->bananaPitch = (0.05 * var_a0);
        }
        var_f14 += gRacerSound->bananaPitch;
    } else {
        gRacerSound->bananaPitch *= 0.95;
        var_f14 += gRacerSound->bananaPitch;
    }
    gRacerSound->unk5C[0] += ((var_f14 - gRacerSound->unk5C[0]) / 8);
    if (gRacerSound->unk5C[0] > (0x7FFF / 5000.0)) {
        gRacerSound->unk5C[0] = (0x7FFF / 5000.0); // 6.5534
    }
    gRacerSound->unk5C[1] = 1.0f;
    gRacerSound->unk54[1] = 0.0f;
    if ((gSoundRacerObj->playerIndex != PLAYER_COMPUTER) && (gSoundRacerObj->spinout_timer != 0) &&
        !gRacerSound->brakeSound) {
        gRacerSound->brakeSound = TRUE;
        sound_play(SOUND_UNK_13D, &gRacerSound->brakeSoundMask);
    } else if (gSoundRacerObj->spinout_timer == 0) {
        gRacerSound->brakeSound = FALSE;
        if (gRacerSound->brakeSoundMask != NULL) {
            sound_stop(gRacerSound->brakeSoundMask);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/audio_vehicle/func_800063EC.s")
#endif

/**
 * Stops all associated sounds and then frees the vehicle sound data from RAM.
 */
void racer_sound_free(Object *obj) {
    s32 i;

    gRacerSound = (VehicleSoundData *) obj->unk64->racer.vehicleSound;
    if (gRacerSound != NULL) {
        for (i = 0; i != 2; i++) {
            if (gRacerSound->unk48[i] != NULL) {
                sound_stop(gRacerSound->unk48[i]);
                gRacerSound->unk48[i] = 0;
            }
        }
        if (gRacerSound->unk50 != NULL) {
            sound_stop(gRacerSound->unk50);
            gRacerSound->unk50 = NULL;
        }
        if (gRacerSound->unkA8 != NULL) {
            sound_stop(gRacerSound->unkA8);
            gRacerSound->unkA8 = 0;
        }
        for (i = 0; i < ARRAY_COUNT(D_80119C30); i++) {
            if (D_80119C30[i] == gRacerSound) {
                D_80119C30[i] = NULL;
            }
        }
        mempool_free(gRacerSound);
        obj->unk64->racer.vehicleSound = NULL;
    }
}

void func_80006BFC(Object *obj, ObjectSegment *segment, Object *obj2, s32 updateRate) {
    Object_Racer *racer;
    f32 velocity;
    f32 xPos;
    f32 yPos;
    f32 zPos;
    f32 new_xPos;
    f32 new_zPos;
    f32 new_yPos;
    f32 var_f2_2;
    f32 posSquared;
    f32 sp1C;
    Object_Racer *racer2;
    s32 new_var;

    racer = &obj->unk64->racer;
    racer2 = &obj2->unk64->racer;
    gRacerSound = (VehicleSoundData *) racer2->vehicleSound;
    if (gRacerSound != NULL) {
        if (segment != NULL) {
            xPos = segment[racer->playerIndex].trans.x_position;
            yPos = segment[racer->playerIndex].trans.y_position;
            zPos = segment[racer->playerIndex].trans.z_position;
            sp1C = 1.0f;
        } else {
            xPos = obj->segment.trans.x_position;
            yPos = obj->segment.trans.y_position;
            zPos = obj->segment.trans.z_position;
            switch (racer->vehicleID) {
                case VEHICLE_CAR:
                    if (racer->velocity >= 0.0f) {
                        velocity = racer->velocity;
                    } else {
                        velocity = -racer->velocity;
                    }
                    break;
                case VEHICLE_HOVERCRAFT:
                    velocity = sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) +
                                     (obj->segment.z_velocity * obj->segment.z_velocity));
                    break;
                default:
                    velocity = sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) +
                                     (obj->segment.z_velocity * obj->segment.z_velocity) +
                                     (obj->segment.y_velocity * obj->segment.y_velocity));
                    break;
            }
            if (velocity > 15.0f) {
                velocity = 15.0f;
            }
            sp1C = 1.0f - (velocity / 15.0f);
        }
        new_xPos = obj2->segment.trans.x_position - xPos;
        new_yPos = obj2->segment.trans.y_position - yPos;
        new_zPos = obj2->segment.trans.z_position - zPos;
        posSquared = sqrtf(((new_xPos * new_xPos) + (new_yPos * new_yPos)) + (new_zPos * new_zPos));
        var_f2_2 = (gRacerSound->unk6C[racer->playerIndex] - posSquared) / updateRate;
        if (var_f2_2 > 15.0f) {
            var_f2_2 = 15.0f;
        } else if (var_f2_2 < -15.0f) {
            var_f2_2 = -15.0f;
        }
        new_var = func_80007FA4(gRacerSound->unk5C[0]) * 1731.23404;
        gRacerSound->unk68 +=
            (((alCents2Ratio((((70.0f + var_f2_2) / (70.0f - var_f2_2)) * new_var)) - gRacerSound->unk5C[0]) -
              gRacerSound->unk68) /
             2);
        gRacerSound->unk68 *= sp1C;
        if (gRacerSound->unk68 > 0.8) {
            gRacerSound->unk68 = 0.8;
        } else if (gRacerSound->unk68 < -0.8) {
            gRacerSound->unk68 = -0.8;
        }
        gRacerSound->unk6C[racer->playerIndex] = posSquared;
    }
}

#ifdef NON_EQUIVALENT
// https://decomp.me/scratch/utYpK
void func_80006FC8(Object **objs, s32 numRacers, ObjectSegment *segment, u8 arg3, s32 updateRate) {
    f32 tempxPos;
    f32 tempyPos;
    f32 tempzPos;
    Object_Racer *racer;
    f32 temp_f20_2;
    s32 loopCount2;
    s32 loopCount1;
    f32 temp_f0_3;
    f32 var_f26;
    u8 temp_s3;
    s32 curVal;
    s32 loopCount3;
    s32 maxVal;
    s32 curIndex;
    f32 sp8C;
    s32 pad;
    VehicleSoundData *temp;

    for (loopCount1 = 0; loopCount1 < arg3; loopCount1++) {
        racer = &objs[loopCount1]->unk64->racer;
        if (racer != NULL) {
            gRacerSound = (VehicleSoundData *) racer->vehicleSound;
        } else {
            gRacerSound = NULL;
        }

        if (gRacerSound != NULL && gRacerSound->unk0[0] != 0) {
            if (racer->raceFinished || check_if_showing_cutscene_camera()) {
                tempxPos = objs[loopCount1]->segment.trans.x_position - segment[loopCount1].trans.x_position;
                tempyPos = objs[loopCount1]->segment.trans.y_position - segment[loopCount1].trans.y_position;
                tempzPos = objs[loopCount1]->segment.trans.z_position - segment[loopCount1].trans.z_position;
                func_80006BFC(objs[loopCount1], segment, objs[loopCount1], updateRate);
                gRacerSound->unk84 = sqrtf((tempxPos * tempxPos) + (tempyPos * tempyPos) + (tempzPos * tempzPos));
                if (gRacerSound->unk84 < 1500.0f) {
                    var_f26 = 2250000.0f; //(1500.0f * 1500.0f)
                    var_f26 = (var_f26 - (gRacerSound->unk84 * gRacerSound->unk84)) / var_f26;
                    var_f26 *= var_f26;
                    gRacerSound->unk91[0] =
                        func_800090C0(tempxPos, tempzPos, segment[loopCount1].trans.rotation.y_rotation);
                } else {
                    var_f26 = 0.0f;
                }
                if (racer->raceFinished == 0) {
                    var_f26 *= 0.5;
                }
            } else {
                var_f26 = 1.0f;
                gRacerSound->unk91[0] = 64;
                gRacerSound->unk68 = 0.0f;
            }
            if ((gRacerSound->unkA0 < 70) && (gRacerSound->unk36) && (arg3 < 3) && (var_f26 != 0.0) &&
                !(gRacerSound->unk44[0] & 1)) {
                temp_f20_2 = gRacerSound->unkA0 / 70.0f;
                temp_s3 = (gRacerSound->unk37 - (gRacerSound->unk37 * temp_f20_2)) * var_f26;
                if (temp_s3 >= 16) {
                    if (gRacerSound->unk50 == NULL) {
                        func_80001F14(gRacerSound->unk36, (s32 *) &gRacerSound->unk50);
                    }
                    temp_f0_3 = gRacerSound->unk38 / 100.0f;
                    sp8C = temp_f0_3 + ((((f32) gRacerSound->unk39 / 100.0f) - temp_f0_3) * temp_f20_2);
                    if (gRacerSound->unk50 != NULL) {
                        func_80009B7C((s32 *) gRacerSound->unk50, objs[loopCount1]->segment.trans.x_position,
                                      objs[loopCount1]->segment.trans.y_position,
                                      objs[loopCount1]->segment.trans.z_position);
                        sound_event_update(gRacerSound->unk50, 8, temp_s3 << 8);
                        sound_event_update(gRacerSound->unk50, 16, *((u32 *) &sp8C));
                        func_80004604(gRacerSound->unk50, 80);
                        sound_event_update(gRacerSound->unk50, 4, gRacerSound->unk91[0]);
                    }
                } else if (gRacerSound->unk50 != NULL) {
                    sound_stop(gRacerSound->unk50);
                    gRacerSound->unk50 = 0;
                }
            } else if (gRacerSound->unk50 != NULL) {
                sound_stop(gRacerSound->unk50);
                gRacerSound->unk50 = 0;
            }
            for (loopCount2 = 0; loopCount2 < 2 && gRacerSound->unk0[loopCount2] != 0 && var_f26 != 0.0; loopCount2++) {
                temp_s3 = gRacerSound->unk54[loopCount2] * var_f26;
                sp8C = gRacerSound->unk5C[loopCount2] + gRacerSound->bananaPitch + gRacerSound->enginePitch +
                       gRacerSound->unk68;
                if (sp8C < 0.05) {
                    sp8C = 0.05f;
                }
                if ((loopCount2 == 0) && (gRacerSound->unk44[0] & 1)) {
                    if (gRacerSound->unk48[0] != NULL) {
                        sound_stop(gRacerSound->unk48[0]);
                        gRacerSound->unk48[0] = NULL;
                    }
                } else {
                    if ((gRacerSound->unk48[loopCount2] != NULL) && (temp_s3 == 0)) {
                        sound_stop(gRacerSound->unk48[loopCount2]);
                        gRacerSound->unk48[loopCount2] = NULL;
                    } else {
                        if (gRacerSound->unk48[loopCount2] == NULL) {
                            func_80001F14(gRacerSound->unk0[loopCount2], (s32 *) &gRacerSound->unk48[loopCount2]);
                        }
                        if (gRacerSound->unk48[loopCount2] != NULL) {
                            func_80009B7C(
                                (s32 *) gRacerSound->unk48[loopCount2], objs[loopCount1]->segment.trans.x_position,
                                objs[loopCount1]->segment.trans.y_position, objs[loopCount1]->segment.trans.z_position);
                            sound_event_update(gRacerSound->unk48[loopCount2], 8, temp_s3 << 8);
                            sound_event_update(gRacerSound->unk48[loopCount2], 16, *((u32 *) &sp8C));
                            func_80004604(gRacerSound->unk48[loopCount2], 80);
                            if (arg3 != 1) {
                                gRacerSound->unk91[0] = 64;
                            }
                            sound_event_update(gRacerSound->unk48[loopCount2], 4, gRacerSound->unk91[0]);
                        }
                    }
                }
            }
        }
    }
    if (arg3 < 3) {
        for (loopCount2 = arg3; loopCount2 < numRacers; loopCount2++) {
            racer = &objs[loopCount2]->unk64->racer;
            if (racer != NULL) {
                gRacerSound = (VehicleSoundData *) racer->vehicleSound;
                if (gRacerSound != NULL) {
                    gRacerSound->unk88 = 0;
                }
            }
        }
        for (loopCount1 = 0; loopCount1 < arg3; loopCount1++) {
            racer = &objs[loopCount1]->unk64->racer;
            for (loopCount2 = arg3; loopCount2 < numRacers; loopCount2++) {
                if (objs[loopCount2]->unk64 != NULL) {
                    gRacerSound = (VehicleSoundData *) objs[loopCount2]->unk64->racer.cameraYaw;
                    if (gRacerSound != 0) {
                        if (racer->raceFinished != 0) {
                            tempxPos =
                                objs[loopCount2]->segment.trans.x_position - segment[loopCount1].trans.x_position;
                            tempyPos =
                                objs[loopCount2]->segment.trans.y_position - segment[loopCount1].trans.y_position;
                            tempzPos =
                                objs[loopCount2]->segment.trans.z_position - segment[loopCount1].trans.z_position;
                        } else {
                            tempxPos =
                                objs[loopCount2]->segment.trans.x_position - objs[loopCount1]->segment.trans.x_position;
                            tempyPos =
                                objs[loopCount2]->segment.trans.y_position - objs[loopCount1]->segment.trans.y_position;
                            tempzPos =
                                objs[loopCount2]->segment.trans.z_position - objs[loopCount1]->segment.trans.z_position;
                        }
                        gRacerSound->unk84 =
                            sqrtf((tempxPos * tempxPos) + (tempyPos * tempyPos) + (tempzPos * tempzPos));
                        if (gRacerSound->unk84 < 1500.0f) {
                            var_f26 = 2250000.0f; //(1500.0f * 1500.0f)
                            var_f26 = (var_f26 - (gRacerSound->unk84 * gRacerSound->unk84)) / var_f26;
                            temp_s3 = gRacerSound->unk54[0] * var_f26;
                            if (temp_s3 > 127) {
                                temp_s3 = 127;
                            }
                            temp_s3 *= 0.8;
                            if (gRacerSound->unk88 < temp_s3) {
                                gRacerSound->unk88 = temp_s3;
                                gRacerSound->unk91[0] =
                                    func_800090C0(tempxPos, tempzPos, segment->trans.rotation.y_rotation);
                                if (racer->raceFinished != 0) {
                                    func_80006BFC(objs[loopCount1], segment, objs[loopCount2], updateRate);
                                } else {
                                    func_80006BFC(objs[loopCount1], NULL, objs[loopCount2], updateRate);
                                }
                                gRacerSound->unk8C = gRacerSound->unk5C[0] + gRacerSound->unk68;
                                if (gRacerSound->unk8C < 0.05) {
                                    gRacerSound->unk8C = 0.05f;
                                }
                            }
                        }
                    }
                }
            }
        }
        for (loopCount3 = 0; loopCount3 < ARRAY_COUNT(D_80119C30); loopCount3++) {
            if (D_80119C30[loopCount3] != NULL) {
                if (D_80119C30[loopCount3]->unk48[0] != NULL && D_80119C30[loopCount3]->unk88 < 8) {
                    sound_stop(D_80119C30[loopCount3]->unk48[0]);
                    D_80119C30[loopCount3]->unk48[0] = NULL;
                    D_80119C30[loopCount3]->unk74 = 0;
                    D_80119C30[loopCount3] = NULL;
                }
            }
        }
        if (updateRate < D_800DC6D4) {
            D_800DC6D4 -= updateRate;
        } else {
            D_800DC6D4 = 0;
        }
        for (loopCount1 = 1; loopCount1 < numRacers; loopCount1++) {
            racer = &objs[loopCount1]->unk64->racer;
            if (objs[loopCount1]->unk64 != NULL) {
                gRacerSound = (VehicleSoundData *) racer->vehicleSound;
                if (gRacerSound != NULL) {
                    if (gRacerSound->unk74 == 0) {
                        maxVal = 20;
                        if (gRacerSound->unk0[0] != 0) {
                            loopCount3 = -1;
                            for (loopCount2 = 0; loopCount2 < ARRAY_COUNT(D_80119C30); loopCount2++) {
                                if (D_80119C30[loopCount2] != NULL) {
                                    curVal = gRacerSound->unk88;
                                    curVal -= D_80119C30[loopCount2]->unk88;
                                    if ((maxVal < curVal) && (D_800DC6D4 == 0)) {
                                        loopCount3 = loopCount2;
                                        maxVal = curVal;
                                    }
                                } else if (gRacerSound->unk88 >= 9) {
                                    loopCount3 = loopCount2;
                                }
                            }
                            if (loopCount3 != -1) {
                                gRacerSound->unk74 = 2;
                                if (D_80119C30[loopCount3] != NULL) {
                                    if (D_80119C30[loopCount3]->unk48[0] != NULL) {
                                        sound_stop(D_80119C30[loopCount3]->unk48[0]);
                                        D_80119C30[loopCount3]->unk48[0] = NULL;
                                        gRacerSound->unk74 = 1;
                                    }
                                    D_800DC6D4 = 60;
                                    D_80119C30[loopCount3]->unk74 = 0;
                                }
                                D_80119C30[loopCount3] = gRacerSound;
                            }
                        }
                    }
                }
            }
        }
        if (get_race_countdown() <= 0) {
            for (loopCount2 = 0; loopCount2 < ARRAY_COUNT(D_80119C30); loopCount2++) {
                temp = D_80119C30[loopCount2];
                if (temp != NULL) {
                    if (temp->unk0[0] != 0) {
                        if (temp->unk74 == 1) {
                            temp->unk74 = 2;
                        } else {
                            if (temp->unk48[0] == NULL) {
                                func_80001F14(temp->unk0[0], (s32 *) &temp->unk48[0]);
                            }
                            if (temp->unk48[0] != NULL) {
                                func_80009B7C((s32 *) temp->unk48[0], temp->racerPos.x, temp->racerPos.y,
                                              temp->racerPos.z);
                                sound_event_update(temp->unk48[0], 8, temp->unk88 << 8);
                                sound_event_update(temp->unk48[0], 16, *((u32 *) &temp->unk8C));
                                if (arg3 != 1) {
                                    temp->unk91[0] = 64;
                                }
                                sound_event_update(temp->unk48[0], 4, temp->unk91[0]);
                                func_80004604(temp->unk48[0], 70);
                            }
                        }
                    }
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/audio_vehicle/func_80006FC8.s")
#endif

/**
 * Enable the vehicle sounds made during gameplay.
 */
UNUSED void sound_vehicle_enable(void) {
    gVehicleSounds = TRUE;
}

/**
 * Disable the vehicle sounds made during gameplay.
 */
UNUSED void sound_vehicle_disable(void) {
    gVehicleSounds = FALSE;
}

/**
 * Return whether vehicle sounds should be playing during gameplay.
 */
UNUSED u8 sound_vehicle_check(void) {
    return gVehicleSounds;
}

// This is likely an arctanh function.
f32 func_80007FA4(f32 arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 var_f14;
    f32 var_f2;
    s32 var_v0;

    var_f2 = 0.0f;
    temp_f0 = -1.0f;
    arg0 = (arg0 - 1.0f) / (1.0f + arg0);
    var_f14 = arg0;
    temp_f12 = arg0 * arg0;
    for (var_v0 = 1; (var_f2 - temp_f0) > 0.001; var_v0 += 2) {
        temp_f0 = var_f2;
        var_f2 += var_f14 / var_v0;
        var_f14 *= temp_f12;
    }
    return var_f2 * 2;
}
