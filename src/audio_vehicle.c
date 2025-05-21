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

/*******************************/

/************ .bss ************/

VehicleSoundData *D_80119C30[2];
VehicleSoundData *gRacerSound;
Object_Racer *gSoundRacerObj;

/******************************/

VehicleSoundData *racer_sound_init(s32 characterId, s32 vehicleId) {
    s32 unused[2];
    s32 i;
    u8 *ptr;
    VehicleSoundData *soundData;
    s32 l;
    s32 *addrPtr;
    unkAudioAsset *asset4C;
    s32 s1;
    u16 j;
    f32 tmp;
    u16 v1;

    static s32 D_800DC6D8 = TRUE;

    if (characterId >= 11) {
        characterId = 11;
    }

    if (D_800DC6D8) {
        for (i = 0; i < 2; i++) {
            D_80119C30[i] = NULL;
        }
        D_800DC6D8 = FALSE;
    }

    addrPtr = (s32 *) load_asset_section_from_rom(ASSET_AUDIO_TABLE);
    s1 = addrPtr[ASSET_AUDIO_7] + (vehicleId * 10 + characterId) * sizeof(unkAudioAsset);
    asset4C = (unkAudioAsset *) mempool_alloc_safe(sizeof(unkAudioAsset), COLOUR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, (u32) asset4C, s1, sizeof(unkAudioAsset));

    soundData = (VehicleSoundData *) mempool_alloc_safe(sizeof(VehicleSoundData), COLOUR_TAG_CYAN);

    ptr = (u8 *) soundData;
    for (l = 0; l < sizeof(VehicleSoundData); l++) {
        *ptr++ = 0;
    }

    soundData->unk36 = asset4C->unk36;
    soundData->unk37 = asset4C->unk37;
    soundData->unk38 = asset4C->unk38;
    soundData->unk39 = asset4C->unk39;
    soundData->unk64 = asset4C->unk3A;

    soundData->throttlePitchCeil = asset4C->unk46 / 10000.0f;
    soundData->throttlePitchVel = asset4C->unk3E / 10000.0f;
    soundData->throttlePitchDecay = asset4C->unk40 / 10000.0f;
    soundData->unkC0 = asset4C->unk42 / 10000.0f;
    soundData->unkC4 = asset4C->unk44 / 10000.0f;
    soundData->unkBC = asset4C->unk3C / 10000.0f;
    soundData->unkB8 = asset4C->unk3B;
    soundData->unkCC = asset4C->unk48 / 10000.0f;
    soundData->brakeSound = FALSE;

    for (i = 0; i < 2; i++) {
        soundData->unk0[i] = asset4C->unk0[i];

        for (l = 0; l < 5; l++) {
            soundData->unk4[i][l] = asset4C->unk4[i][l];
            soundData->unk18[i][l] = asset4C->unk18[i][l];
            soundData->unkE[i][l] = asset4C->unkE[i][l];
            soundData->unk2C[i][l] = asset4C->unk2C[i][l];
        }
    }

    soundData->unk74 = 0;
    soundData->unk6C[0] = 0.0f;
    soundData->basePitch = asset4C->unk4A / 100.0f;

    if (vehicleId == VEHICLE_CAR) {
        soundData->unk54[0] = soundData->unk2C[0][0];
        soundData->unk5C[0] = soundData->unk18[0][0] / 10000.0f;
        soundData->unk54[1] = soundData->unk2C[1][0];
        soundData->unk5C[1] = soundData->unk18[1][0] / 10000.0f;
    } else {
        soundData->unk5C[0] = soundData->basePitch;
        v1 = soundData->unk5C[0] * 10000.0f;

        for (j = 0; v1 >= soundData->unk18[0][j] && j < 4; j++) {}
        j--;

        tmp = (f32) (v1 - soundData->unk18[0][j]) / (soundData->unk18[0][j + 1] - soundData->unk18[0][j]);
        soundData->unk54[0] = soundData->unk2C[0][j] + (soundData->unk2C[0][j + 1] - soundData->unk2C[0][j]) * tmp;
    }

    mempool_free(addrPtr);
    mempool_free(asset4C);

    return soundData;
}

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
                    buttonsHeld = input_held(gSoundRacerObj->playerIndex);
                    buttonsPressed = input_pressed(gSoundRacerObj->playerIndex);
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
                        racer_sound_plane(obj, buttonsPressed, buttonsHeld, updateRate);
                        break;
                    default:
                        racer_sound_car(obj, buttonsPressed, buttonsHeld, updateRate);
                        break;
                }
            }
        }
    }
}

void racer_sound_car(Object *obj, u32 buttonsPressed, u32 buttonsHeld, s32 updateRate) {
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    u8 temp_f4;
    f32 velocity;
    s32 var_s0;
    s32 innerLoop;
    f32 var_f20;
    s32 outerLoop;
    f32 var_f14;
    f32 var_f12;
    f32 var_f2;
    f32 sp6C;
    s32 var_v1_3;

    if (gSoundRacerObj->unk1FB != 0) {
        velocity = 12.0f;
    } else {
        velocity = gSoundRacerObj->velocity;
    }
    if (velocity < 0.0f) {
        velocity = -velocity;
    }
    var_s0 = (velocity / 16) * 100;
    var_s0 += 5;
    if (var_s0 > 100) {
        var_s0 = 100;
    }
    for (outerLoop = 0; outerLoop < 1; outerLoop++) {
        if ((gRacerSound->unk0[outerLoop]) != 0) {
            innerLoop = 0;
            while ((var_s0 < gRacerSound->unkE[outerLoop][innerLoop] ||
                    var_s0 > gRacerSound->unkE[outerLoop][innerLoop + 1]) &&
                   innerLoop < 4) {
                innerLoop++;
            }

            temp_f14 = (var_s0 - gRacerSound->unkE[outerLoop][innerLoop]) /
                       ((f32) (gRacerSound->unkE[outerLoop][innerLoop + 1] - gRacerSound->unkE[outerLoop][innerLoop]));
            temp_f4 =
                gRacerSound->unk2C[outerLoop][innerLoop] +
                (gRacerSound->unk2C[outerLoop][innerLoop + 1] - gRacerSound->unk2C[outerLoop][innerLoop]) * temp_f14;

            innerLoop = 0;
            while ((var_s0 < gRacerSound->unk4[outerLoop][innerLoop] ||
                    var_s0 > gRacerSound->unk4[outerLoop][innerLoop + 1]) &&
                   innerLoop < 4) {
                innerLoop++;
            }

            temp_f14 = (var_s0 - gRacerSound->unk4[outerLoop][innerLoop]) /
                       ((f32) (gRacerSound->unk4[outerLoop][innerLoop + 1] - gRacerSound->unk4[outerLoop][innerLoop]));
            temp_f16 = gRacerSound->unk18[outerLoop][innerLoop] / 10000.0f;
            temp_f18 = gRacerSound->unk18[outerLoop][innerLoop + 1] / 10000.0f;
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
                    gRacerSound->unk90 += get_random_number_from_range(0, 10) - 5;
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
        sndp_stop(gRacerSound->unkA8);
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
        if (gRacerSound->unkA8 != 0) {
            sndp_set_param(gRacerSound->unkA8, AL_SNDP_PITCH_EVT, *((u32 *) &sp6C));
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
            sndp_set_param(gRacerSound->unkA8, AL_SNDP_VOL_EVT, 0);
        } else {
            sndp_set_param(gRacerSound->unkA8, AL_SNDP_VOL_EVT, gRacerSound->unkAC << 8);
            audspat_calculate_echo(gRacerSound->unkA8, obj->segment.trans.x_position, obj->segment.trans.y_position,
                                   obj->segment.trans.z_position);
        }
    }
    gRacerSound->unkA0 = var_s0;
    if ((buttonsHeld & A_BUTTON) != 0) {
        gRacerSound->unk98 = gRacerSound->unk54[0];
    }
}

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
    if (!race_starting()) {
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
    for (i = 0; temp_f10 >= gRacerSound->unk18[0][i] && i < 4; i++) {}
    if (i == 4) {
        var_t0 = gRacerSound->unk2C[0][i];
    } else {
        if (i != 0) {
            i--;
        }
        new_var =
            (temp_f10 - gRacerSound->unk18[0][i]) / ((f32) (gRacerSound->unk18[0][i + 1] - gRacerSound->unk18[0][i]));
        var_t0 = gRacerSound->unk2C[0][i] + (gRacerSound->unk2C[0][i + 1] - gRacerSound->unk2C[0][i]) * new_var;
    }
    gRacerSound->unk54[0] += ((var_t0 - gRacerSound->unk54[0]) / 8);
    gRacerSound->unk5C[1] = 1.0f;
    gRacerSound->unk54[1] = 0.0f;
}

void racer_sound_plane(Object *obj, UNUSED u32 buttonsPressed, u32 buttonsHeld, s32 updateRate) {
    f32 velocity;
    f32 sp28;
    f32 var_f2;
    u16 temp_f10;
    f32 temp_f8;
    f32 var_f14;
    u8 i;
    s32 var_a0;
    u8 var_t0;
    f32 temp;
    f32 temp2;

    if (get_race_countdown() == 0) {
        velocity = sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) +
                        (obj->segment.z_velocity * obj->segment.z_velocity) +
                        (obj->segment.y_velocity * obj->segment.y_velocity));
    } else {
        velocity = 0.0f;
    }

    if (velocity < 2.0f) {
        gRacerSound->unk54[0] += ((gRacerSound->unk37 - gRacerSound->unk54[0]) / 8);
    } else {
        temp_f10 = gRacerSound->unk5C[0] * 10000.0f;
        for (i = 0; temp_f10 >= gRacerSound->unk18[0][i] && i < 4; i++) {}
        if (i == 4) {
            var_t0 = gRacerSound->unk2C[0][i];
        } else {
            if (i != 0) {
                i--;
            }
            temp_f8 = (temp_f10 - gRacerSound->unk18[0][i]) /
                      ((f32) (gRacerSound->unk18[0][i + 1] - gRacerSound->unk18[0][i]));
            var_t0 = gRacerSound->unk2C[0][i] + (gRacerSound->unk2C[0][i + 1] - gRacerSound->unk2C[0][i]) * temp_f8;
        }
        gRacerSound->unk54[0] += ((var_t0 - gRacerSound->unk54[0]) / 8);
    }
    var_f14 = gRacerSound->basePitch;

    if (buttonsHeld & A_BUTTON) {
        gRacerSound->throttlePitch += gRacerSound->throttlePitchVel * updateRate;
        if (gRacerSound->throttlePitchCeil < gRacerSound->throttlePitch) {
            gRacerSound->throttlePitch = gRacerSound->throttlePitchCeil;
        }
    } else {
        gRacerSound->throttlePitch -= gRacerSound->throttlePitchDecay * updateRate;
    }
    if (gRacerSound->throttlePitch < 0) {
        gRacerSound->throttlePitch = 0;
    }
    if (!race_starting()) {
        gRacerSound->throttlePitch = 0;
    }
    var_f14 += gRacerSound->throttlePitch;
    sp28 = sins_f(obj->segment.trans.rotation.x_rotation);
    var_f2 = sins_f(obj->segment.trans.rotation.z_rotation);
    temp = gRacerSound->unkC4 * sp28;
    temp2 = gRacerSound->unkC0 * var_f2;
    temp2 = ABSF(temp2);
    var_f14 += temp + temp2;

    if (velocity > 10.0) {
        velocity -= 10.0;
    } else {
        velocity = 0.0f;
    }

    var_f14 += velocity * gRacerSound->unkCC;
    if (velocity != 0.0 && gSoundRacerObj->bananas != 0) {
        if (gSoundRacerObj->bananas <= 10) {
            var_a0 = gSoundRacerObj->bananas;
        } else {
            var_a0 = 10;
        }
        if (gRacerSound->bananaPitch < 0.05 * var_a0) {
            gRacerSound->bananaPitch += (0.05 * var_a0) / (var_a0 * 64);
        } else if (gRacerSound->bananaPitch > 0.05 * var_a0) {
            gRacerSound->bananaPitch = 0.05 * var_a0;
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
    gRacerSound->unk54[1] = 0;
    if (gSoundRacerObj->playerIndex != PLAYER_COMPUTER && gSoundRacerObj->spinout_timer != 0 &&
        !gRacerSound->brakeSound) {
        gRacerSound->brakeSound = TRUE;
        sound_play(SOUND_UNK_13D, &gRacerSound->brakeSoundMask);
    } else if (gSoundRacerObj->spinout_timer == 0) {
        gRacerSound->brakeSound = FALSE;
        if (gRacerSound->brakeSoundMask != NULL) {
            sndp_stop(gRacerSound->brakeSoundMask);
        }
    }
}

/**
 * Stops all associated sounds and then frees the vehicle sound data from RAM.
 */
void racer_sound_free(Object *obj) {
    s32 i;

    gRacerSound = obj->unk64->racer.vehicleSound;
    if (gRacerSound != NULL) {
        for (i = 0; i != 2; i++) {
            if (gRacerSound->unk48[i] != NULL) {
                sndp_stop(gRacerSound->unk48[i]);
                gRacerSound->unk48[i] = 0;
            }
        }
        if (gRacerSound->unk50 != NULL) {
            sndp_stop(gRacerSound->unk50);
            gRacerSound->unk50 = NULL;
        }
        if (gRacerSound->unkA8 != NULL) {
            sndp_stop(gRacerSound->unkA8);
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

void func_80006FC8(Object **objs, s32 numRacers, ObjectSegment *segment, u8 arg3, s32 updateRate) {
    f32 tempxPos;
    f32 tempyPos;
    f32 tempzPos;
    Object_Racer *racer;
    f32 temp_f20_2;
    s32 loopCount2;
    s32 loopCount1;
    s32 unused;
    f32 var_f26;
    u8 temp_s3;
    u8 v0;
    s32 curVal;
    s32 loopCount3;
    s32 maxVal;
    s32 curIndex;
    f32 sp8C;
    VehicleSoundData *temp;
    s32 m;

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
                    gRacerSound->unk91[0] = audspat_calculate_spatial_pan(
                        tempxPos, tempzPos, segment[loopCount1].trans.rotation.y_rotation);
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
                        func_80001F14(gRacerSound->unk36, &gRacerSound->unk50);
                    }
                    sp8C = gRacerSound->unk38 / 100.0f +
                           ((((f32) gRacerSound->unk39 / 100.0f) - gRacerSound->unk38 / 100.0f) * temp_f20_2);
                    if (gRacerSound->unk50 != NULL) {
                        audspat_calculate_echo(gRacerSound->unk50, objs[loopCount1]->segment.trans.x_position,
                                               objs[loopCount1]->segment.trans.y_position,
                                               objs[loopCount1]->segment.trans.z_position);
                        sndp_set_param(gRacerSound->unk50, AL_SNDP_VOL_EVT, temp_s3 << 8);
                        sndp_set_param(gRacerSound->unk50, AL_SNDP_PITCH_EVT, *((u32 *) &sp8C));
                        sndp_set_priority(gRacerSound->unk50, 80);
                        sndp_set_param(gRacerSound->unk50, AL_SNDP_PAN_EVT, gRacerSound->unk91[0]);
                    }
                } else if (gRacerSound->unk50 != NULL) {
                    sndp_stop(gRacerSound->unk50);
                    gRacerSound->unk50 = 0;
                }
            } else if (gRacerSound->unk50 != NULL) {
                sndp_stop(gRacerSound->unk50);
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
                        sndp_stop(gRacerSound->unk48[0]);
                        gRacerSound->unk48[0] = NULL;
                    }
                } else {
                    if ((gRacerSound->unk48[loopCount2] != NULL) && (temp_s3 == 0)) {
                        sndp_stop(gRacerSound->unk48[loopCount2]);
                        gRacerSound->unk48[loopCount2] = NULL;
                    } else {
                        if (gRacerSound->unk48[loopCount2] == NULL) {
                            func_80001F14(gRacerSound->unk0[loopCount2], &gRacerSound->unk48[loopCount2]);
                        }
                        if (gRacerSound->unk48[loopCount2] != NULL) {
                            audspat_calculate_echo(
                                gRacerSound->unk48[loopCount2], objs[loopCount1]->segment.trans.x_position,
                                objs[loopCount1]->segment.trans.y_position, objs[loopCount1]->segment.trans.z_position);
                            sndp_set_param(gRacerSound->unk48[loopCount2], AL_SNDP_VOL_EVT, temp_s3 << 8);
                            sndp_set_param(gRacerSound->unk48[loopCount2], AL_SNDP_PITCH_EVT, *((u32 *) &sp8C));
                            sndp_set_priority(gRacerSound->unk48[loopCount2], 80);
                            if (arg3 != 1) {
                                gRacerSound->unk91[0] = 64;
                            }
                            sndp_set_param(gRacerSound->unk48[loopCount2], AL_SNDP_PAN_EVT, gRacerSound->unk91[0]);
                        }
                    }
                }
            }
        }
    }
    if (arg3 >= 3) {
        return;
    }

    for (loopCount2 = arg3; loopCount2 < numRacers; loopCount2++) {
        racer = &objs[loopCount2]->unk64->racer;
        if (racer != NULL) {
            gRacerSound = racer->vehicleSound;
            if (gRacerSound != NULL) {
                temp = gRacerSound;
                temp->unk88 = 0;
            }
        }
    }
    for (loopCount1 = 0; loopCount1 < arg3; loopCount1++) {
        racer = &objs[loopCount1]->unk64->racer;
        for (loopCount2 = arg3; loopCount2 < numRacers; loopCount2++) {
            if (objs[loopCount2]->unk64 != NULL) {
                gRacerSound = objs[loopCount2]->unk64->racer.vehicleSound;
                if (gRacerSound != 0) {
                    if (racer->raceFinished != 0) {
                        tempxPos = objs[loopCount2]->segment.trans.x_position - segment[loopCount1].trans.x_position;
                        tempyPos = objs[loopCount2]->segment.trans.y_position - segment[loopCount1].trans.y_position;
                        tempzPos = objs[loopCount2]->segment.trans.z_position - segment[loopCount1].trans.z_position;
                    } else {
                        tempxPos =
                            objs[loopCount2]->segment.trans.x_position - objs[loopCount1]->segment.trans.x_position;
                        tempyPos =
                            objs[loopCount2]->segment.trans.y_position - objs[loopCount1]->segment.trans.y_position;
                        tempzPos =
                            objs[loopCount2]->segment.trans.z_position - objs[loopCount1]->segment.trans.z_position;
                    }
                    gRacerSound->unk84 = sqrtf((tempxPos * tempxPos) + (tempyPos * tempyPos) + (tempzPos * tempzPos));
                    if (gRacerSound->unk84 < 1500.0f) {
                        var_f26 = 2250000.0f; //(1500.0f * 1500.0f)
                        var_f26 = (var_f26 - (gRacerSound->unk84 * gRacerSound->unk84)) / var_f26;
                        v0 = gRacerSound->unk54[0] * var_f26;
                        if (v0 > 127) {
                            v0 = 127;
                        }
                        v0 *= 0.8;
                        if (gRacerSound->unk88 < v0) {
                            gRacerSound->unk88 = v0;
                            gRacerSound->unk91[0] =
                                audspat_calculate_spatial_pan(tempxPos, tempzPos, segment->trans.rotation.y_rotation);
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
                sndp_stop(D_80119C30[loopCount3]->unk48[0]);
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

    for (loopCount2 = 1; loopCount2 < numRacers; loopCount2++) {
        racer = &objs[loopCount2]->unk64->racer;
        if (objs[loopCount2]->unk64 != NULL) {
            gRacerSound = racer->vehicleSound;
            if (gRacerSound != NULL) {
                if (gRacerSound->unk74 == 0) {
                    maxVal = 20;
                    if (gRacerSound->unk0[0] != 0) {
                        m = -1;
                        for (loopCount3 = 0; loopCount3 < ARRAY_COUNT(D_80119C30); loopCount3++) {
                            if (1) { // FAKE MATCH
                                temp = D_80119C30[loopCount3];
                                if (temp != NULL) {
                                    curVal = gRacerSound->unk88;
                                    curVal -= temp->unk88;
                                    if ((maxVal < curVal) && (D_800DC6D4 == 0)) {
                                        m = loopCount3;
                                        maxVal = curVal;
                                    }
                                } else if (gRacerSound->unk88 >= 9) {
                                    m = loopCount3;
                                }
                            }
                        }

                        if (m != -1) {
                            gRacerSound->unk74 = 2;
                            if (D_80119C30[m] != NULL) {
                                if (D_80119C30[m]->unk48[0] != NULL) {
                                    sndp_stop(D_80119C30[m]->unk48[0]);
                                    D_80119C30[m]->unk48[0] = NULL;
                                    gRacerSound->unk74 = 1;
                                }
                                D_800DC6D4 = 60;
                                D_80119C30[m]->unk74 = 0;
                            }
                            D_80119C30[m] = gRacerSound;
                        }
                    }
                }
            }
        }
    }

    if (get_race_countdown() <= 0) {
        for (loopCount3 = 0; loopCount3 < ARRAY_COUNT(D_80119C30); loopCount3++) {
            temp = D_80119C30[loopCount3];
            if (temp != NULL) {
                if (temp->unk0[0] != 0) {
                    if (temp->unk74 == 1) {
                        temp->unk74 = 2;
                    } else {
                        if (temp->unk48[0] == NULL) {
                            func_80001F14(temp->unk0[0], &temp->unk48[0]);
                        }
                        if (temp->unk48[0] != NULL) {
                            audspat_calculate_echo(temp->unk48[0], temp->racerPos.x, temp->racerPos.y,
                                                   temp->racerPos.z);
                            sndp_set_param(temp->unk48[0], AL_SNDP_VOL_EVT, temp->unk88 << 8);
                            sndp_set_param(temp->unk48[0], AL_SNDP_PITCH_EVT, *((u32 *) &temp->unk8C));
                            if (arg3 != 1) {
                                temp->unk91[0] = 64;
                            }
                            sndp_set_param(temp->unk48[0], AL_SNDP_PAN_EVT, temp->unk91[0]);
                            sndp_set_priority(temp->unk48[0], 70);
                        }
                    }
                }
            }
        }
    }
}

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
