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
s32 gBackgroundSoundSwapTimer = 0;

/*******************************/

/************ .bss ************/

VehicleSoundData *gBackgroundRacerSounds[2];
VehicleSoundData *gRacerSound;
Object_Racer *gSoundRacerObj;

/******************************/

/**
 * Loads the vehicle sound asset for a given character.
 * Allocates and initializes a VehicleSoundData structure by copying data from the corresponding asset.
 * Sets the initial pitch and volume values for the engine sound.
 */
VehicleSoundData *racer_sound_init(s32 characterId, s32 vehicleId) {
    s32 unused[2];
    s32 i;
    u8 *ptr;
    VehicleSoundData *soundData;
    u32 l;
    s32 *table;
    VehicleSoundAsset *asset;
    s32 assetOffset;
    u16 j;
    f32 interpFrac;
    u16 v1;

    static s32 resetAmbient = TRUE;

    // Unclear why this compares with 11, since we only have 10 characters.
    if (characterId >= 11) {
        characterId = 11;
    }

    // It's unclear why we reset these pointers here — they should already be null initially.
    if (resetAmbient) {
        for (i = 0; i < ARRAY_COUNT(gBackgroundRacerSounds); i++) {
            gBackgroundRacerSounds[i] = NULL;
        }
        resetAmbient = FALSE;
    }

    // Load the sound asset.
    // There are 30 total assets (10 characters × 3 vehicle types: car, plane, hovercraft).
    // There is no type check for vehicleId, so passing an unsupported type (e.g. VEHICLE_LOOPDELOOP)
    // will cause out-of-bounds access and undefined behavior.
    table = (s32 *) load_asset_section_from_rom(ASSET_AUDIO_TABLE);
    assetOffset = table[ASSET_AUDIO_7] + (vehicleId * 10 + characterId) * sizeof(VehicleSoundAsset);
    asset = (VehicleSoundAsset *) mempool_alloc_safe(sizeof(VehicleSoundAsset), COLOUR_TAG_CYAN);
    load_asset_to_address(ASSET_AUDIO, (u32) asset, assetOffset, sizeof(VehicleSoundAsset));

    soundData = (VehicleSoundData *) mempool_alloc_safe(sizeof(VehicleSoundData), COLOUR_TAG_CYAN);

    // Zero-initialize the structure manually.
    // (Technically memset is available in symbols and could be used.)
    ptr = (u8 *) soundData;
    for (l = 0; l < sizeof(VehicleSoundData); l++) {
        *ptr++ = 0;
    }

    // Copy fields from the asset into the sound data structure.
    soundData->engineIdleSound = asset->engineIdleSound;
    soundData->engineIdleMaxVolume = asset->engineIdleMaxVolume;
    soundData->engineIdleMaxPitch = asset->engineIdleMaxPitch;
    soundData->engineIdleMinPitch = asset->engineIdleMinPitch;
    soundData->unk64_unused = asset->unk3A_unused;

    soundData->thrustPitchMax = asset->thrustPitchMax / 10000.0f;
    soundData->thrustPitchVel = asset->thrustPitchVel / 10000.0f;
    soundData->thrustPitchDecay = asset->thrustPitchDecay / 10000.0f;
    soundData->rollAnglePitchScale = asset->rollAnglePitchScale / 10000.0f;
    soundData->pitchAnglePitchScale = asset->pitchAnglePitchScale / 10000.0f;
    soundData->pitchLateralSpeedScale = asset->pitchLateralSpeedScale / 10000.0f;
    soundData->unkB8_unused = asset->unk3B_unused;
    soundData->thrustPitchSpeedScale = asset->thrustPitchSpeedScale / 10000.0f;
    soundData->spinoutSoundOn = FALSE;

    for (i = 0; i < 2; i++) {
        soundData->soundId[i] = asset->soundId[i];

        for (l = 0; l < 5; l++) {
            soundData->intensityLevelsForPitch[i][l] = asset->intensityLevelsForPitch[i][l];
            soundData->pitchLevels[i][l] = asset->pitchLevels[i][l];
            soundData->intensityLevelsForVolume[i][l] = asset->intensityLevelsForVolume[i][l];
            soundData->volumeLevels[i][l] = asset->volumeLevels[i][l];
        }
    }

    soundData->backgroundState = VEHICLE_BACKGROUND_STOPPED;
    soundData->prevDistance[0] = 0.0f;
    soundData->planeHovercraftBasePitch = asset->planeHovercraftBasePitch / 100.0f;

    // For cars, initial pitch and volume are taken from the first level of the engine intensity-to-sound tables.
    // For planes and hovercrafts, the pitch starts at a fixed base value from the asset.
    if (vehicleId == VEHICLE_CAR) {
        soundData->baseVolume[0] = soundData->volumeLevels[0][0];
        soundData->basePitch[0] = soundData->pitchLevels[0][0] / 10000.0f;
        soundData->baseVolume[1] = soundData->volumeLevels[1][0];
        soundData->basePitch[1] = soundData->pitchLevels[1][0] / 10000.0f;
    } else {
        soundData->basePitch[0] = soundData->planeHovercraftBasePitch;
        v1 = soundData->basePitch[0] * 10000.0f;

        for (j = 0; v1 >= soundData->pitchLevels[0][j] && j < 4; j++) {}
        j--;

        interpFrac = (f32) (v1 - soundData->pitchLevels[0][j]) /
                     (soundData->pitchLevels[0][j + 1] - soundData->pitchLevels[0][j]);
        soundData->baseVolume[0] = soundData->volumeLevels[0][j] +
                                   (soundData->volumeLevels[0][j + 1] - soundData->volumeLevels[0][j]) * interpFrac;
    }

    mempool_free(table);
    mempool_free(asset);

    return soundData;
}

/**
 * Update the sound of the engine and braking during gameplay, for later.
 * Check which vehicle is being used, update the position of the audio,
 * then call a function to handle that particular vehicles audio.
 */
void racer_sound_update(Object *obj, u32 buttonsPressed, u32 buttonsHeld, s32 ticksDelta) {
    if (gVehicleSounds) {
        gSoundRacerObj = &obj->unk64->racer;
        gRacerSound = gSoundRacerObj->vehicleSound;
        if (gRacerSound != NULL) {
            if (get_race_countdown() != 0) {
                if (gSoundRacerObj->playerIndex != PLAYER_COMPUTER) {
                    buttonsHeld = input_held(gSoundRacerObj->playerIndex);
                    buttonsPressed = input_pressed(gSoundRacerObj->playerIndex);
                }
            }
            if (gRacerSound->soundId[0] == 0) {
                gRacerSound->racerPos.x = -32000.0f;
                gRacerSound->racerPos.y = -32000.0f;
                gRacerSound->racerPos.z = -32000.0f;
            } else {
                gRacerSound->racerPos.x = obj->segment.trans.x_position;
                gRacerSound->racerPos.y = obj->segment.trans.y_position;
                gRacerSound->racerPos.z = obj->segment.trans.z_position;
                switch (gSoundRacerObj->vehicleIDPrev) {
                    case VEHICLE_HOVERCRAFT:
                        racer_sound_hovercraft(obj, buttonsPressed, buttonsHeld, ticksDelta);
                        break;
                    case VEHICLE_PLANE:
                        racer_sound_plane(obj, buttonsPressed, buttonsHeld, ticksDelta);
                        break;
                    default:
                        racer_sound_car(obj, buttonsPressed, buttonsHeld, ticksDelta);
                        break;
                }
            }
        }
    }
}

/**
 * Calculates car engine sound pitch and volume, as well as the brake sound pitch and volume.
 * Engine sound depends on speed, number of bananas collected, acceleration button state, drifting, and whether the car
 * is airborne.
 */
void racer_sound_car(Object *obj, u32 buttonsPressed, u32 buttonsHeld, s32 ticksDelta) {
    f32 interpFrac;
    f32 pitch1;
    f32 pitch2;
    u8 targetVolume;
    f32 speed;
    s32 intensity;
    s32 j;
    f32 absVelocity;
    s32 i;
    f32 deltaVolume;
    f32 deltaPitch;
    f32 targetPitch;
    f32 brakePitch;
    s32 bananas;

    if (gSoundRacerObj->unk1FB != 0) {
        speed = 12.0f;
    } else {
        speed = gSoundRacerObj->velocity;
    }
    if (speed < 0.0f) {
        speed = -speed;
    }

    // Convert speed to engine intensity ranging from 5 to 100, with 16 being maximum speed
    intensity = (speed / 16) * 100;
    intensity += 5;
    if (intensity > 100) {
        intensity = 100;
    }

    // Only process the main engine sound; the secondary sound uses fixed pitch and volume
    for (i = 0; i < 1; i++) {
        if ((gRacerSound->soundId[i]) != 0) {
            // Calculate volume by interpolating between control points based on intensity
            j = 0;
            while ((intensity < gRacerSound->intensityLevelsForVolume[i][j] ||
                    intensity > gRacerSound->intensityLevelsForVolume[i][j + 1]) &&
                   j < 4) {
                j++;
            }
            interpFrac =
                (intensity - gRacerSound->intensityLevelsForVolume[i][j]) /
                ((f32) (gRacerSound->intensityLevelsForVolume[i][j + 1] - gRacerSound->intensityLevelsForVolume[i][j]));
            targetVolume = gRacerSound->volumeLevels[i][j] +
                           (gRacerSound->volumeLevels[i][j + 1] - gRacerSound->volumeLevels[i][j]) * interpFrac;

            // Calculate base pitch similarly by interpolating between control points
            j = 0;
            while ((intensity < gRacerSound->intensityLevelsForPitch[i][j] ||
                    intensity > gRacerSound->intensityLevelsForPitch[i][j + 1]) &&
                   j < 4) {
                j++;
            }

            interpFrac =
                (intensity - gRacerSound->intensityLevelsForPitch[i][j]) /
                ((f32) (gRacerSound->intensityLevelsForPitch[i][j + 1] - gRacerSound->intensityLevelsForPitch[i][j]));
            pitch1 = gRacerSound->pitchLevels[i][j] / 10000.0f;
            pitch2 = gRacerSound->pitchLevels[i][j + 1] / 10000.0f;

            // Apply pitch modifiers

            // Each banana adds 0.05 to the pitch (up to 0.5), with smooth transitions,
            // but only if engine intensity is above 50%. Below 50%, this bonus fades out smoothly.
            if (intensity > 50 && gSoundRacerObj->bananas != 0) {
                if (gSoundRacerObj->bananas <= 10) {
                    bananas = gSoundRacerObj->bananas;
                } else {
                    bananas = 10;
                }
                if (gRacerSound->bananaPitch < 0.05 * bananas) {
                    gRacerSound->bananaPitch += (0.05 * bananas) / (bananas * 64);
                } else if (gRacerSound->bananaPitch > 0.05 * bananas) {
                    gRacerSound->bananaPitch = 0.05 * bananas;
                }
                targetPitch = ((pitch2 - pitch1) * interpFrac) + pitch1 + gRacerSound->bananaPitch;
            } else {
                gRacerSound->bananaPitch *= 0.95;
                targetPitch = ((pitch2 - pitch1) * interpFrac) + pitch1 + gRacerSound->bananaPitch;
            }

            // Add 0.13 pitch boost when drifting, with smooth increase and fast decay when drifting stops
            if (gSoundRacerObj->drift_direction != 0) {
                gRacerSound->driftPitch += (0.13 - gRacerSound->driftPitch) / 8;
            } else {
                gRacerSound->driftPitch /= 4;
            }
            targetPitch += gRacerSound->driftPitch;

            // Add instant 0.3 pitch boost when the car is in the air (not grounded), but only for player cars
            if (gSoundRacerObj->groundedWheels == 0 && (gSoundRacerObj->playerIndex != PLAYER_COMPUTER)) {
                targetPitch += 0.3;
            }

            // Smooth pitch and volume changes over two frames to allow jitter effects
            deltaPitch = (targetPitch - gRacerSound->basePitch[i]) / 2;
            deltaVolume = (targetVolume - gRacerSound->baseVolume[i]) / 2;

            // Add engine jitter effect for player cars to simulate engine vibration
            // Max pitch variation ±0.02, volume variation ±5
            if (gSoundRacerObj->playerIndex != PLAYER_COMPUTER) {
                if (rand_range(0, 10) < 7) {
                    gRacerSound->engineJitter += rand_range(0, 10) - 5;
                    if (gRacerSound->engineJitter > 5) {
                        gRacerSound->engineJitter = 5;
                    } else if (gRacerSound->engineJitter < -5) {
                        gRacerSound->engineJitter = -5;
                    }
                }
                deltaPitch += 0.02 * (gRacerSound->engineJitter / 5.0f);
                deltaVolume += 5.0f * (gRacerSound->engineJitter / 5.0f);
            }

            // While acceleration button is held, gradually increase pitch boost up to 0.4 (by 0.01 per frame)
            if ((buttonsHeld & A_BUTTON) && gRacerSound->enginePitch < 0.4) {
                gRacerSound->enginePitch += ((f32) ticksDelta * 0.01);
                if (gRacerSound->enginePitch > 0.4) {
                    gRacerSound->enginePitch = 0.4f;
                }
            }

            // When acceleration is released, decrease pitch boost smoothly (by 0.005 per frame)
            if (!(buttonsHeld & A_BUTTON) && (gRacerSound->enginePitch > 0.0f)) {
                gRacerSound->enginePitch -= ((f32) ticksDelta * 0.005);
                if (gRacerSound->enginePitch < 0.0f) {
                    gRacerSound->enginePitch = 0.0f;
                }
            }
            gRacerSound->basePitch[i] += deltaPitch;
            if (buttonsHeld & A_BUTTON) {
                gRacerSound->baseVolume[i] += deltaVolume;
            } else {
                // When acceleration isn't pressed, volume stays fixed at 35 regardless of speed
                gRacerSound->baseVolume[i] = 35.0f;
            }
        }
    }

    // Start or stop the brake sound based on conditions
    if ((gSoundRacerObj->unk10 != NULL || gSoundRacerObj->unk14 != NULL || !(buttonsHeld & B_BUTTON) ||
         gSoundRacerObj->velocity > -0.1 || gSoundRacerObj->vehicleID == VEHICLE_LOOPDELOOP) &&
        gRacerSound->brakeSound != NULL) {
        sndp_stop(gRacerSound->brakeSound);
        gRacerSound->brakeSound = NULL;
    } else if ((buttonsPressed & B_BUTTON) && gRacerSound->brakeSound == NULL && gSoundRacerObj->playerIndex >= 0) {
        if (gSoundRacerObj->velocity < 0.0f) {
            absVelocity = -gSoundRacerObj->velocity;
        } else {
            absVelocity = gSoundRacerObj->velocity;
        }
        if (absVelocity > 12.0f) {
            absVelocity = 12.0f;
        }
        func_80001F14(25, &gRacerSound->brakeSound);
        // Brake pitch depends on speed, ranges from 0.5 to 1.0
        brakePitch = absVelocity * 0.5 / 12.0 + 0.5;
        if (gRacerSound->brakeSound != NULL) {
            sndp_set_param(gRacerSound->brakeSound, AL_SNDP_PITCH_EVT, *((u32 *) &brakePitch));
        }
        gRacerSound->brakeSoundVolume = 110;
        gRacerSound->airTime = 0;
    }

    if (gRacerSound->brakeSound != NULL) {
        if (gSoundRacerObj->groundedWheels == 0) {
            gRacerSound->airTime += ticksDelta;
        } else {
            gRacerSound->airTime = 0;
        }
        if (gRacerSound->airTime >= 10) {
            // Stop brake sound after being airborne for 10 consecutive frames
            sndp_set_param(gRacerSound->brakeSound, AL_SNDP_VOL_EVT, 0);
        } else {
            sndp_set_param(gRacerSound->brakeSound, AL_SNDP_VOL_EVT, gRacerSound->brakeSoundVolume << 8);
            audspat_calculate_echo(gRacerSound->brakeSound, obj->segment.trans.x_position,
                                   obj->segment.trans.y_position, obj->segment.trans.z_position);
        }
    }

    // Store current engine intensity for later use (e.g. idle sound calculation)
    gRacerSound->engine_intensity = intensity;

    if (buttonsHeld & A_BUTTON) {
        gRacerSound->unk98_unused = gRacerSound->baseVolume[0];
    }
}

/**
 * Update the engine sounds for the hovercraft.
 * Uses velocity, banana count and ground contact to decide what pitch to use.
 * Those values are calculated in this function.
 */
void racer_sound_hovercraft(Object *obj, UNUSED u32 buttonsPressed, u32 buttonsHeld, s32 tickDelta) {
    UNUSED s32 pad;
    f32 speed;
    f32 fracPart;
    u16 pitchLevel;
    f32 angleSine;
    f32 lateralSpeedPitch;
    f32 targetPitch;
    s32 angle;
    s32 bananas;
    u8 volume;
    u8 i;

    if (get_race_countdown() == 0) {
        speed = sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) +
                      (obj->segment.z_velocity * obj->segment.z_velocity));
    } else {
        speed = 0.0f;
    }

    targetPitch = gRacerSound->planeHovercraftBasePitch;

    // All pitch-related parameters for acceleration are defined in assets,
    // unlike cars where they're hardcoded.
    if (buttonsHeld & A_BUTTON) {
        gRacerSound->thrustPitch += gRacerSound->thrustPitchVel * tickDelta;
        if (gRacerSound->thrustPitch > gRacerSound->thrustPitchMax) {
            gRacerSound->thrustPitch = gRacerSound->thrustPitchMax;
        }
    } else {
        gRacerSound->thrustPitch -= gRacerSound->thrustPitchDecay * tickDelta;
    }
    if (gRacerSound->thrustPitch < 0.0f) {
        gRacerSound->thrustPitch = 0.0f;
    }

    // If the hovercraft is angled relative to the camera view, add pitch offset accordingly.
    angle = (-gSoundRacerObj->cameraYaw - (gSoundRacerObj->steerVisualRotation & 0xFFFF)) + 0x8000;
    WRAP(angle, -0x8000, 0x8000);
    angleSine = sins_f(angle);
    angleSine = ABSF(angleSine);
    if (!check_if_showing_cutscene_camera() && get_race_countdown() == 0) {
        lateralSpeedPitch = (gRacerSound->pitchLateralSpeedScale * angleSine * speed) / 15.0;
    } else {
        lateralSpeedPitch = 0.0f;
    }

    if (!race_starting()) {
        gRacerSound->thrustPitch = 0.0f;
    }
    if (speed > 10.0) {
        speed -= 10.0;
    } else {
        speed = 0.0f;
    }

    // Apply pitch bonus from collected bananas: +0.05 per banana.
    // Only applies when speed is above 10, i.e. near maximum.
    // Otherwise, the bonus fades out gradually.
    //!@Delta: This entire block is not timing correct.
    if (speed != 0.0 && gSoundRacerObj->bananas != 0) {
        if (gSoundRacerObj->bananas <= 10) {
            bananas = gSoundRacerObj->bananas;
        } else {
            bananas = 10;
        }
        if (gRacerSound->bananaPitch < 0.05 * bananas) {
            gRacerSound->bananaPitch += (0.05 * bananas) / (bananas * 64);
        } else if (gRacerSound->bananaPitch > 0.05 * bananas) {
            gRacerSound->bananaPitch = 0.05 * bananas;
        }
        targetPitch += gRacerSound->bananaPitch;
    } else {
        gRacerSound->bananaPitch *= 0.95;
        targetPitch += gRacerSound->bananaPitch;
    }

    // Additional pitch based on speed, lateral movement, and engine thrust.
    targetPitch += speed * gRacerSound->thrustPitchSpeedScale + lateralSpeedPitch + gRacerSound->thrustPitch;

    // Add +0.3 to pitch if the hovercraft is over water (for non-AI players).
    if (gSoundRacerObj->playerIndex != PLAYER_COMPUTER && gSoundRacerObj->groundedWheels == 0 &&
        gSoundRacerObj->waterTimer < 4) {
        if (get_race_countdown() == 0) {
            targetPitch += 0.3;
        }
    }

    // Smoothly interpolate pitch and clamp to maximum.
    // The max pitch value is 0x7FFF / 5000.0 (~6.5534), but its origin is unclear.
    gRacerSound->basePitch[0] += (targetPitch - gRacerSound->basePitch[0]) / 8;
    if (gRacerSound->basePitch[0] > (0x7FFF / 5000.0)) {
        gRacerSound->basePitch[0] = (0x7FFF / 5000.0); // 6.5534
    }

    // Convert pitch to volume by interpolating between control points.
    pitchLevel = gRacerSound->basePitch[0] * 10000.0f;
    for (i = 0; pitchLevel >= gRacerSound->pitchLevels[0][i] && i < 4; i++) {}
    if (i == 4) {
        volume = gRacerSound->volumeLevels[0][i];
    } else {
        if (i != 0) {
            i--;
        }
        fracPart = (pitchLevel - gRacerSound->pitchLevels[0][i]) /
                   ((f32) (gRacerSound->pitchLevels[0][i + 1] - gRacerSound->pitchLevels[0][i]));
        volume = gRacerSound->volumeLevels[0][i] +
                 (gRacerSound->volumeLevels[0][i + 1] - gRacerSound->volumeLevels[0][i]) * fracPart;
    }
    gRacerSound->baseVolume[0] += (volume - gRacerSound->baseVolume[0]) / 8;
    gRacerSound->basePitch[1] = 1.0f;
    gRacerSound->baseVolume[1] = 0.0f;
}

/**
 * Sets engine and spinout sound parameters for the plane.
 * The engine pitch is influenced by acceleration input, current speed, banana count, and the plane’s orientation.
 */
void racer_sound_plane(Object *obj, UNUSED u32 buttonsPressed, u32 buttonsHeld, s32 tickDelta) {
    f32 speed;
    f32 xSine;
    f32 zSine;
    u16 pitchLevel;
    f32 interpFrac;
    f32 targetPitch;
    u8 i;
    s32 bananas;
    u8 volume;
    f32 temp;
    f32 temp2;

    if (get_race_countdown() == 0) {
        speed = sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) +
                      (obj->segment.z_velocity * obj->segment.z_velocity) +
                      (obj->segment.y_velocity * obj->segment.y_velocity));
    } else {
        speed = 0.0f;
    }

    if (speed < 2.0f) {
        // If speed is below 2, treat the plane as idle and smoothly blend to the idle engine volume.
        gRacerSound->baseVolume[0] += (gRacerSound->engineIdleMaxVolume - gRacerSound->baseVolume[0]) / 8;
    } else {
        // Compute volume based on pitch using linear interpolation between volume control points.
        // Note: Uses pitch from the previous frame.
        pitchLevel = gRacerSound->basePitch[0] * 10000.0f;
        for (i = 0; pitchLevel >= gRacerSound->pitchLevels[0][i] && i < 4; i++) {}
        if (i == 4) {
            volume = gRacerSound->volumeLevels[0][i];
        } else {
            if (i != 0) {
                i--;
            }
            interpFrac = (pitchLevel - gRacerSound->pitchLevels[0][i]) /
                         ((f32) (gRacerSound->pitchLevels[0][i + 1] - gRacerSound->pitchLevels[0][i]));
            volume = gRacerSound->volumeLevels[0][i] +
                     (gRacerSound->volumeLevels[0][i + 1] - gRacerSound->volumeLevels[0][i]) * interpFrac;
        }
        gRacerSound->baseVolume[0] += ((volume - gRacerSound->baseVolume[0]) / 8);
    }

    targetPitch = gRacerSound->planeHovercraftBasePitch;

    // All pitch-related parameters for acceleration are defined in assets,
    // unlike cars where they're hardcoded.
    if (buttonsHeld & A_BUTTON) {
        gRacerSound->thrustPitch += gRacerSound->thrustPitchVel * tickDelta;
        if (gRacerSound->thrustPitchMax < gRacerSound->thrustPitch) {
            gRacerSound->thrustPitch = gRacerSound->thrustPitchMax;
        }
    } else {
        gRacerSound->thrustPitch -= gRacerSound->thrustPitchDecay * tickDelta;
    }
    if (gRacerSound->thrustPitch < 0) {
        gRacerSound->thrustPitch = 0;
    }
    if (!race_starting()) {
        gRacerSound->thrustPitch = 0;
    }
    targetPitch += gRacerSound->thrustPitch;

    // Add pitch modifiers based on pitch and roll angles of the plane.
    xSine = sins_f(obj->segment.trans.rotation.x_rotation);
    zSine = sins_f(obj->segment.trans.rotation.z_rotation);
    temp = gRacerSound->pitchAnglePitchScale * xSine;
    temp2 = gRacerSound->rollAnglePitchScale * zSine;
    temp2 = ABSF(temp2);
    targetPitch += temp + temp2;

    // Apply additional pitch if speed exceeds 10.
    if (speed > 10.0) {
        speed -= 10.0;
    } else {
        speed = 0.0f;
    }
    targetPitch += speed * gRacerSound->thrustPitchSpeedScale;

    // Apply pitch bonus from collected bananas: +0.05 per banana.
    // Only applies when speed is above 10, i.e. near maximum.
    // Otherwise, the bonus fades out gradually.
    if (speed != 0.0 && gSoundRacerObj->bananas != 0) {
        if (gSoundRacerObj->bananas <= 10) {
            bananas = gSoundRacerObj->bananas;
        } else {
            bananas = 10;
        }
        if (gRacerSound->bananaPitch < 0.05 * bananas) {
            gRacerSound->bananaPitch += (0.05 * bananas) / (bananas * 64);
        } else if (gRacerSound->bananaPitch > 0.05 * bananas) {
            gRacerSound->bananaPitch = 0.05 * bananas;
        }
        targetPitch += gRacerSound->bananaPitch;
    } else {
        gRacerSound->bananaPitch *= 0.95;
        targetPitch += gRacerSound->bananaPitch;
    }
    gRacerSound->basePitch[0] += (targetPitch - gRacerSound->basePitch[0]) / 8;

    if (gRacerSound->basePitch[0] > 0x7FFF / 5000.0) {
        gRacerSound->basePitch[0] = 0x7FFF / 5000.0; // 6.5534
    }
    gRacerSound->basePitch[1] = 1.0f;
    gRacerSound->baseVolume[1] = 0;

    // Trigger or stop spinout sound based on spinout timer.
    if (gSoundRacerObj->playerIndex != PLAYER_COMPUTER && gSoundRacerObj->spinout_timer != 0 &&
        !gRacerSound->spinoutSoundOn) {
        gRacerSound->spinoutSoundOn = TRUE;
        sound_play(SOUND_UNK_13D, &gRacerSound->spinoutSound);
    } else if (gSoundRacerObj->spinout_timer == 0) {
        gRacerSound->spinoutSoundOn = FALSE;
        if (gRacerSound->spinoutSound != NULL) {
            sndp_stop(gRacerSound->spinoutSound);
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
            if (gRacerSound->soundHandle[i] != NULL) {
                sndp_stop(gRacerSound->soundHandle[i]);
                gRacerSound->soundHandle[i] = 0;
            }
        }
        if (gRacerSound->engineIdleSoundHandle != NULL) {
            sndp_stop(gRacerSound->engineIdleSoundHandle);
            gRacerSound->engineIdleSoundHandle = NULL;
        }
        if (gRacerSound->brakeSound != NULL) {
            sndp_stop(gRacerSound->brakeSound);
            gRacerSound->brakeSound = 0;
        }
        for (i = 0; i < ARRAY_COUNT(gBackgroundRacerSounds); i++) {
            if (gBackgroundRacerSounds[i] == gRacerSound) {
                gBackgroundRacerSounds[i] = NULL;
            }
        }
        mempool_free(gRacerSound);
        obj->unk64->racer.vehicleSound = NULL;
    }
}

/**
 * Calculates the Doppler pitch shift for a given sound source and observer.
 * However, it does so in a very strange and error-prone way.
 */
void racer_sound_doppler_effect(Object *observerObj, Camera *camera, Object *sourceObj, s32 tickDelta) {
    Object_Racer *observerRacer;
    f32 obsSpeed;
    f32 xObs;
    f32 yObs;
    f32 zObs;
    f32 deltaX;
    f32 deltaZ;
    f32 deltaY;
    f32 relativeVelocity;
    f32 distance;
    f32 obsVelRatio;
    Object_Racer *sourceRacer;
    s32 cents;

    /*
        The implementation of this function is, to put it mildly, overcomplicated,
        does many things incorrectly, and gives the impression that the developer didn't fully
        understand the Doppler effect.

        To compute the Doppler effect, you need only the source speed (U) and the observer speed (V)
        projected along the line connecting them:
            pitchRatio = (C + U) / (C + V), where C is the speed of sound.

        If both speeds are small compared to C, a simple approximation suffices:
            pitchRatio = 1 + Vd / C, where Vd is the rate of change of distance between them.
        That’s all that’s really needed.

        However, the actual implementation here is unnecessarily convoluted. While the result
        is technically not a bug — just a slightly incorrect engine pitch — the strange and
        questionable logic deserves to be pointed out.
    */

    observerRacer = &observerObj->unk64->racer;
    sourceRacer = &sourceObj->unk64->racer;
    gRacerSound = sourceRacer->vehicleSound;
    if (gRacerSound != NULL) {
        if (camera != NULL) {
            // If the observer is a post-race or cutscene camera, use its position.
            // The observer velocity factor is set to 1, since the camera is stationary.
            xObs = camera[observerRacer->playerIndex].trans.x_position;
            yObs = camera[observerRacer->playerIndex].trans.y_position;
            zObs = camera[observerRacer->playerIndex].trans.z_position;
            obsVelRatio = 1.0f;
        } else {
            // If the observer is a player, things get unnecessarily complex.
            // First, fetch the observer's position.
            xObs = observerObj->segment.trans.x_position;
            yObs = observerObj->segment.trans.y_position;
            zObs = observerObj->segment.trans.z_position;

            // Then compute the observer's speed.
            switch (observerRacer->vehicleID) {
                case VEHICLE_CAR:
                    // Absolute value of forward velocity
                    if (observerRacer->velocity >= 0.0f) {
                        obsSpeed = observerRacer->velocity;
                    } else {
                        obsSpeed = -observerRacer->velocity;
                    }
                    break;
                case VEHICLE_HOVERCRAFT:
                    // 2D ground speed
                    obsSpeed = sqrtf(observerObj->segment.x_velocity * observerObj->segment.x_velocity +
                                     observerObj->segment.z_velocity * observerObj->segment.z_velocity);
                    break;
                default:
                    // Full 3D velocity
                    obsSpeed = sqrtf(observerObj->segment.x_velocity * observerObj->segment.x_velocity +
                                     observerObj->segment.z_velocity * observerObj->segment.z_velocity +
                                     observerObj->segment.y_velocity * observerObj->segment.y_velocity);
                    break;
            }
            // For some reason, speed is capped at 15, and a velocity factor is derived from that.
            // It's unclear why this is needed at all.
            if (obsSpeed > 15.0f) {
                obsSpeed = 15.0f;
            }
            obsVelRatio = 1.0f - (obsSpeed / 15.0f);
        }

        // Calculate the distance between source and observer
        deltaX = sourceObj->segment.trans.x_position - xObs;
        deltaY = sourceObj->segment.trans.y_position - yObs;
        deltaZ = sourceObj->segment.trans.z_position - zObs;
        distance = sqrtf(((deltaX * deltaX) + (deltaY * deltaY)) + (deltaZ * deltaZ));

        // Compute relative velocity — this is actually all that's needed for the Doppler effect!
        relativeVelocity = (gRacerSound->prevDistance[observerRacer->playerIndex] - distance) / tickDelta;
        if (relativeVelocity > 15.0f) {
            relativeVelocity = 15.0f;
        } else if (relativeVelocity < -15.0f) {
            relativeVelocity = -15.0f;
        }

        // Now things get weird...
        // First, convert the base pitch to cents (logarithmic scale).
        cents = log(gRacerSound->basePitch[0]) * 1731.23404; // 1200 / ln(2)

        // Then scale the cents using (70 + v) / (70 - v), which is incorrect.
        // Cents are logarithmic and shouldn't be scaled like this.
        // Moreover, there's no need to convert to cents and back.
        // 70 seems to be acting as the speed of sound here.
        gRacerSound->dopplerPitch += (alCents2Ratio((70.0f + relativeVelocity) / (70.0f - relativeVelocity) * cents) -
                                      gRacerSound->basePitch[0] - gRacerSound->dopplerPitch) /
                                     2;

        // Then the result is again scaled by obsVelRatio, even though observer speed is already part of
        // relativeVelocity. This seems redundant and unclear.
        gRacerSound->dopplerPitch *= obsVelRatio;

        // Clamp the Doppler pitch shift to ±0.8
        if (gRacerSound->dopplerPitch > 0.8) {
            gRacerSound->dopplerPitch = 0.8;
        } else if (gRacerSound->dopplerPitch < -0.8) {
            gRacerSound->dopplerPitch = -0.8;
        }
        gRacerSound->prevDistance[observerRacer->playerIndex] = distance;
    }
}

/**
 * Updates sound parameters for player-controlled vehicles,
 * as well as AI-controlled vehicles that drive in the background.
 */
void racer_sound_update_all(Object **racerObjs, s32 numRacers, Camera *cameras, u8 numCameras, s32 tickDelta) {
    f32 deltaX;
    f32 deltaY;
    f32 deltaZ;
    Object_Racer *racer;
    f32 idle_intensity;
    s32 j;
    s32 i;
    s32 unused;
    f32 volumeMult;
    u8 volume;
    u8 backgroundVolume;
    s32 curDiff;
    s32 k;
    s32 maxDiff;
    s32 curIndex;
    f32 pitch;
    VehicleSoundData *soundData;
    s32 bestSlot;

    // First, calculate engine and idle sound parameters for each player.
    for (i = 0; i < numCameras; i++) {
        racer = &racerObjs[i]->unk64->racer;
        if (racer != NULL) {
            gRacerSound = racer->vehicleSound;
        } else {
            gRacerSound = NULL;
        }

        if (gRacerSound != NULL && gRacerSound->soundId[0] != 0) {
            if (racer->raceFinished || check_if_showing_cutscene_camera()) {
                // If the race is finished or a cutscene is playing, the vehicle is considered to move relative to the
                // camera, so we calculate the engine sound's pitch, volume, and stereo pan accordingly.
                deltaX = racerObjs[i]->segment.trans.x_position - cameras[i].trans.x_position;
                deltaY = racerObjs[i]->segment.trans.y_position - cameras[i].trans.y_position;
                deltaZ = racerObjs[i]->segment.trans.z_position - cameras[i].trans.z_position;
                racer_sound_doppler_effect(racerObjs[i], cameras, racerObjs[i], tickDelta);
                gRacerSound->distToCamera = sqrtf((deltaX * deltaX) + (deltaY * deltaY) + (deltaZ * deltaZ));

                // Engine sounds are inaudible beyond 1500 units.
                if (gRacerSound->distToCamera < 1500.0f) {
                    volumeMult = 2250000.0f; // 1500.0f * 1500.0f;
                    volumeMult = (volumeMult - (gRacerSound->distToCamera * gRacerSound->distToCamera)) / volumeMult;
                    volumeMult *= volumeMult;
                    gRacerSound->pan =
                        audspat_calculate_spatial_pan(deltaX, deltaZ, cameras[i].trans.rotation.y_rotation);
                } else {
                    volumeMult = 0.0f;
                }
                if (!racer->raceFinished) {
                    // In cutscenes, engine volume is reduced by half.
                    volumeMult *= 0.5;
                }
            } else {
                volumeMult = 1.0f;
                gRacerSound->pan = 64;
                gRacerSound->dopplerPitch = 0.0f;
            }

            // If the engine intensity is below 70, play an idle engine sound.
            // The lower the intensity, the louder the idle sound.
            // This is only applied when there are 1 or 2 players to avoid excessive sound generation.
            if (gRacerSound->engine_intensity < 70 && gRacerSound->engineIdleSound != 0 && numCameras <= 2 &&
                volumeMult != 0.0 && !(gRacerSound->soundDisabled[0] & 1)) {

                idle_intensity = gRacerSound->engine_intensity / 70.0f;
                volume =
                    (gRacerSound->engineIdleMaxVolume - gRacerSound->engineIdleMaxVolume * idle_intensity) * volumeMult;

                // If volume is above threshold, update idle sound parameters.
                if (volume >= 16) {
                    if (gRacerSound->engineIdleSoundHandle == NULL) {
                        func_80001F14(gRacerSound->engineIdleSound, &gRacerSound->engineIdleSoundHandle);
                    }
                    pitch = gRacerSound->engineIdleMaxPitch / 100.0f + ((f32) gRacerSound->engineIdleMinPitch / 100.0f -
                                                                        gRacerSound->engineIdleMaxPitch / 100.0f) *
                                                                           idle_intensity;
                    if (gRacerSound->engineIdleSoundHandle != NULL) {
                        audspat_calculate_echo(
                            gRacerSound->engineIdleSoundHandle, racerObjs[i]->segment.trans.x_position,
                            racerObjs[i]->segment.trans.y_position, racerObjs[i]->segment.trans.z_position);
                        sndp_set_param(gRacerSound->engineIdleSoundHandle, AL_SNDP_VOL_EVT, volume << 8);
                        sndp_set_param(gRacerSound->engineIdleSoundHandle, AL_SNDP_PITCH_EVT, *((u32 *) &pitch));
                        sndp_set_priority(gRacerSound->engineIdleSoundHandle, 80);
                        sndp_set_param(gRacerSound->engineIdleSoundHandle, AL_SNDP_PAN_EVT, gRacerSound->pan);
                    }
                } else if (gRacerSound->engineIdleSoundHandle != NULL) {
                    // Otherwise, stop the idle sound if it was playing.
                    sndp_stop(gRacerSound->engineIdleSoundHandle);
                    gRacerSound->engineIdleSoundHandle = NULL;
                }
            } else if (gRacerSound->engineIdleSoundHandle != NULL) {
                sndp_stop(gRacerSound->engineIdleSoundHandle);
                gRacerSound->engineIdleSoundHandle = NULL;
            }

            // Start or stop engine sounds based on current conditions.
            for (j = 0; j < 2 && gRacerSound->soundId[j] != 0 && volumeMult != 0.0; j++) {
                volume = gRacerSound->baseVolume[j] * volumeMult;

                //!@bug bananaPitch is added twice.
                pitch = gRacerSound->basePitch[j] + gRacerSound->bananaPitch + gRacerSound->enginePitch +
                        gRacerSound->dopplerPitch;
                if (pitch < 0.05) {
                    pitch = 0.05f;
                }

                // If engine sound is disabled, stop it.
                if (j == 0 && (gRacerSound->soundDisabled[0] & 1)) {
                    if (gRacerSound->soundHandle[0] != NULL) {
                        sndp_stop(gRacerSound->soundHandle[0]);
                        gRacerSound->soundHandle[0] = NULL;
                    }
                } else {
                    // If sound handle exists but volume is zero, stop the sound.
                    if (gRacerSound->soundHandle[j] != NULL && volume == 0) {
                        sndp_stop(gRacerSound->soundHandle[j]);
                        gRacerSound->soundHandle[j] = NULL;
                    } else {
                        // Otherwise, start or update the engine sound parameters.
                        if (gRacerSound->soundHandle[j] == NULL) {
                            func_80001F14(gRacerSound->soundId[j], &gRacerSound->soundHandle[j]);
                        }
                        if (gRacerSound->soundHandle[j] != NULL) {
                            audspat_calculate_echo(gRacerSound->soundHandle[j], racerObjs[i]->segment.trans.x_position,
                                                   racerObjs[i]->segment.trans.y_position,
                                                   racerObjs[i]->segment.trans.z_position);
                            sndp_set_param(gRacerSound->soundHandle[j], AL_SNDP_VOL_EVT, volume << 8);
                            sndp_set_param(gRacerSound->soundHandle[j], AL_SNDP_PITCH_EVT, *((u32 *) &pitch));
                            sndp_set_priority(gRacerSound->soundHandle[j], 80);
                            if (numCameras != 1) {
                                gRacerSound->pan = 64;
                            }
                            sndp_set_param(gRacerSound->soundHandle[j], AL_SNDP_PAN_EVT, gRacerSound->pan);
                        }
                    }
                }
            }
        }
    }

    // Next: manage engine sounds for AI-controlled vehicles.
    // These background engine sounds are only active in 1-2 player mode,
    // and only the two loudest sounds are allowed to play simultaneously.

    // Skip background sounds entirely if more than 2 players.
    if (numCameras > 2) {
        return;
    }

    // First, reset background volume for each AI vehicle.
    for (j = numCameras; j < numRacers; j++) {
        racer = &racerObjs[j]->unk64->racer;
        if (racer != NULL) {
            gRacerSound = racer->vehicleSound;
            if (gRacerSound != NULL) {
                soundData = gRacerSound;
                soundData->backgroundVolume = 0;
            }
        }
    }

    // Then, calculate the background volume for each AI vehicle,
    // determining which camera hears it the loudest (volume decreases with distance).
    // Doppler effect is the only pitch modifier applied here.

    for (i = 0; i < numCameras; i++) {
        racer = &racerObjs[i]->unk64->racer;
        for (j = numCameras; j < numRacers; j++) {
            if (racerObjs[j]->unk64 != NULL) {
                gRacerSound = racerObjs[j]->unk64->racer.vehicleSound;
                if (gRacerSound != NULL) {
                    if (racer->raceFinished) {
                        deltaX = racerObjs[j]->segment.trans.x_position - cameras[i].trans.x_position;
                        deltaY = racerObjs[j]->segment.trans.y_position - cameras[i].trans.y_position;
                        deltaZ = racerObjs[j]->segment.trans.z_position - cameras[i].trans.z_position;
                    } else {
                        deltaX = racerObjs[j]->segment.trans.x_position - racerObjs[i]->segment.trans.x_position;
                        deltaY = racerObjs[j]->segment.trans.y_position - racerObjs[i]->segment.trans.y_position;
                        deltaZ = racerObjs[j]->segment.trans.z_position - racerObjs[i]->segment.trans.z_position;
                    }
                    gRacerSound->distToCamera = sqrtf((deltaX * deltaX) + (deltaY * deltaY) + (deltaZ * deltaZ));
                    if (gRacerSound->distToCamera < 1500.0f) {
                        volumeMult = 2250000.0f; //(1500.0f * 1500.0f)
                        volumeMult = (volumeMult - gRacerSound->distToCamera * gRacerSound->distToCamera) / volumeMult;

                        backgroundVolume = gRacerSound->baseVolume[0] * volumeMult;
                        if (backgroundVolume > 127) {
                            backgroundVolume = 127;
                        }

                        // All background sounds are played at 80% of the computed volume.
                        backgroundVolume *= 0.8;

                        // Store sound parameters for the camera that hears it the loudest.
                        if (gRacerSound->backgroundVolume < backgroundVolume) {
                            gRacerSound->backgroundVolume = backgroundVolume;
                            gRacerSound->pan =
                                audspat_calculate_spatial_pan(deltaX, deltaZ, cameras->trans.rotation.y_rotation);
                            if (racer->raceFinished) {
                                racer_sound_doppler_effect(racerObjs[i], cameras, racerObjs[j], tickDelta);
                            } else {
                                racer_sound_doppler_effect(racerObjs[i], NULL, racerObjs[j], tickDelta);
                            }
                            gRacerSound->backgroundPitch = gRacerSound->basePitch[0] + gRacerSound->dopplerPitch;
                            if (gRacerSound->backgroundPitch < 0.05) {
                                gRacerSound->backgroundPitch = 0.05f;
                            }
                        }
                    }
                }
            }
        }
    }

    // Select up to 2 background engine sounds to play.

    // First, stop any playing background sounds if they are too quiet.
    for (k = 0; k < ARRAY_COUNT(gBackgroundRacerSounds); k++) {
        if (gBackgroundRacerSounds[k] != NULL) {
            if (gBackgroundRacerSounds[k]->soundHandle[0] != NULL && gBackgroundRacerSounds[k]->backgroundVolume < 8) {
                sndp_stop(gBackgroundRacerSounds[k]->soundHandle[0]);
                gBackgroundRacerSounds[k]->soundHandle[0] = NULL;
                gBackgroundRacerSounds[k]->backgroundState = VEHICLE_BACKGROUND_STOPPED;
                gBackgroundRacerSounds[k] = NULL;
            }
        }
    }

    // Advance the background sound swap timer.
    if (tickDelta < gBackgroundSoundSwapTimer) {
        gBackgroundSoundSwapTimer -= tickDelta;
    } else {
        gBackgroundSoundSwapTimer = 0;
    }

    // Replace background sounds based on volume priority.
    //!@bug: loop starts from 1 instead of numCameras — possibly unintended.
    for (j = 1; j < numRacers; j++) {
        racer = &racerObjs[j]->unk64->racer;
        if (racerObjs[j]->unk64 != NULL) {
            gRacerSound = racer->vehicleSound;
            if (gRacerSound != NULL) {
                // If a sound is currently stopped, check whether it should be restarted and find a suitable slot.
                if (gRacerSound->backgroundState == VEHICLE_BACKGROUND_STOPPED) {
                    // Replacement only happens if the new sound is at least 20 units louder than the current one.
                    // This likely prevents rapid switching between background sounds.
                    maxDiff = 20;
                    if (gRacerSound->soundId[0] != 0) {
                        bestSlot = -1;
                        // Search for a suitable slot (up to 2). Prefer empty slots, or replace the quietest if timer
                        // allows.
                        for (k = 0; k < ARRAY_COUNT(gBackgroundRacerSounds); k++) {
                            if (1) { // FAKE MATCH
                                soundData = gBackgroundRacerSounds[k];
                                if (soundData != NULL) {
                                    curDiff = gRacerSound->backgroundVolume;
                                    curDiff -= soundData->backgroundVolume;
                                    if (maxDiff < curDiff && gBackgroundSoundSwapTimer == 0) {
                                        bestSlot = k;
                                        maxDiff = curDiff;
                                    }
                                } else if (gRacerSound->backgroundVolume > 8) {
                                    bestSlot = k;
                                }
                            }
                        }

                        if (bestSlot != -1) {
                            // If a replacement is found, stop the old sound before starting the new one.
                            // backgroundState is temporarily set to PENDING to defer actual sound playback for one
                            // frame.
                            gRacerSound->backgroundState = VEHICLE_BACKGROUND_PLAYING;
                            if (gBackgroundRacerSounds[bestSlot] != NULL) {
                                if (gBackgroundRacerSounds[bestSlot]->soundHandle[0] != NULL) {
                                    sndp_stop(gBackgroundRacerSounds[bestSlot]->soundHandle[0]);
                                    gBackgroundRacerSounds[bestSlot]->soundHandle[0] = NULL;
                                    gRacerSound->backgroundState = VEHICLE_BACKGROUND_PENDING;
                                }
                                // Prevent further changes to the background slots for the next 60 frames.
                                gBackgroundSoundSwapTimer = 60;
                                gBackgroundRacerSounds[bestSlot]->backgroundState = VEHICLE_BACKGROUND_STOPPED;
                            }
                            gBackgroundRacerSounds[bestSlot] = gRacerSound;
                        }
                    }
                }
            }
        }
    }

    // Finally, set parameters for all active background sounds (AI vehicles).
    if (get_race_countdown() <= 0) {
        for (k = 0; k < ARRAY_COUNT(gBackgroundRacerSounds); k++) {
            soundData = gBackgroundRacerSounds[k];
            if (soundData != NULL) {
                if (soundData->soundId[0] != 0) {
                    // If the sound is pending, transition it to playing.
                    // Otherwise, start or update its parameters.
                    if (soundData->backgroundState == VEHICLE_BACKGROUND_PENDING) {
                        soundData->backgroundState = VEHICLE_BACKGROUND_PLAYING;
                    } else {
                        if (soundData->soundHandle[0] == NULL) {
                            func_80001F14(soundData->soundId[0], &soundData->soundHandle[0]);
                        }
                        if (soundData->soundHandle[0] != NULL) {
                            audspat_calculate_echo(soundData->soundHandle[0], soundData->racerPos.x,
                                                   soundData->racerPos.y, soundData->racerPos.z);
                            sndp_set_param(soundData->soundHandle[0], AL_SNDP_VOL_EVT,
                                           soundData->backgroundVolume << 8);
                            sndp_set_param(soundData->soundHandle[0], AL_SNDP_PITCH_EVT,
                                           *((u32 *) &soundData->backgroundPitch));
                            if (numCameras != 1) {
                                soundData->pan = 64;
                            }
                            sndp_set_param(soundData->soundHandle[0], AL_SNDP_PAN_EVT, soundData->pan);
                            sndp_set_priority(soundData->soundHandle[0], 70);
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
UNUSED void racer_sound_enable(void) {
    gVehicleSounds = TRUE;
}

/**
 * Disable the vehicle sounds made during gameplay.
 */
UNUSED void racer_sound_disable(void) {
    gVehicleSounds = FALSE;
}

/**
 * Return whether vehicle sounds should be playing during gameplay.
 */
UNUSED u8 racer_sound_check(void) {
    return gVehicleSounds;
}

/**
 * Returns the natural logarithm of the given argument.
 * Uses a Maclaurin series expansion for the inverse hyperbolic tangent (artanh) for the calculation.
 */
f32 log(f32 x) {
    f32 prev_sum;
    f32 x_squared;
    f32 power;
    f32 sum;
    s32 n;

    sum = 0.0f;
    prev_sum = -1.0f;
    x = (x - 1.0f) / (1.0f + x);
    power = x;
    x_squared = x * x;
    // sum = sum(x^n/n)
    for (n = 1; (sum - prev_sum) > 0.001; n += 2) {
        prev_sum = sum;
        sum += power / n; // power = x^n
        power *= x_squared;
    }
    return sum * 2;
}
