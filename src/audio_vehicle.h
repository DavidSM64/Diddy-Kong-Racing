#ifndef _AUDIO_VEHICLE_H_
#define _AUDIO_VEHICLE_H_

#include "types.h"
#include "structs.h"
#include "audio.h"
#include "camera.h"

enum VehicleBackgroundSoundStates {
    VEHICLE_BACKGROUND_STOPPED,
    VEHICLE_BACKGROUND_PENDING,
    VEHICLE_BACKGROUND_PLAYING
};

/* Size: 0xE0 / 224 bytes */
typedef struct VehicleSoundData {
    /* 0x00 */ u16 soundId[2];
    /* 0x04 */ u8 intensityLevelsForPitch[2][5];
    /* 0x0E */ u8 intensityLevelsForVolume[2][5];
    /* 0x18 */ u16 pitchLevels[2][5]; // 10000 = 1.0
    /* 0x2C */ u8 volumeLevels[2][5];
    /* 0x36 */ u8 engineIdleSound;
    /* 0x37 */ u8 engineIdleMaxVolume;
    /* 0x38 */ u8 engineIdleMaxPitch; // 100 = 1.0
    /* 0x39 */ u8 engineIdleMinPitch; // 100 = 1.0
    /* 0x3C */ f32 bananaPitch;
    /* 0x40 */ f32 driftPitch;
    /* 0x44 */ u8 soundDisabled[4];
    /* 0x48 */ SoundHandle soundHandle[2];
    /* 0x50 */ SoundHandle engineIdleSoundHandle;
    /* 0x54 */ f32 baseVolume[2];
    /* 0x5C */ f32 basePitch[2];
    /* 0x64 */ u8 unk64_unused;
    /* 0x68 */ f32 dopplerPitch;
    /* 0x6C */ f32 prevDistance[2];
    /* 0x74 */ u8 backgroundState;
    /* 0x78 */ Vec3f racerPos;
    /* 0x84 */ f32 distToCamera;
    /* 0x88 */ u8 backgroundVolume;
    /* 0x8C */ f32 backgroundPitch;
    /* 0x90 */ s8 engineJitter;
    /* 0x91 */ u8 pan;
    /* 0x94 */ f32 enginePitch; // Engine noise for the car.
    /* 0x98 */ u8 unk98_unused;
    /* 0x99 */ u8 pad99[0x7];
    /* 0xA0 */ u8 engine_intensity;
    /* 0xA4 */ f32 thrustPitch; // Engine noise for the hovercraft and plane.
    /* 0xA8 */ SoundHandle brakeSound;
    /* 0xAC */ u16 brakeSoundVolume;
    /* 0xB0 */ f32 thrustPitchVel;
    /* 0xB4 */ f32 thrustPitchDecay;
    /* 0xB8 */ u8 unkB8_unused;
    /* 0xBC */ f32 pitchLateralSpeedScale;
    /* 0xC0 */ f32 rollAnglePitchScale;
    /* 0xC4 */ f32 pitchAnglePitchScale;
    /* 0xC8 */ f32 thrustPitchMax;
    /* 0xCC */ f32 thrustPitchSpeedScale;
    /* 0xD0 */ u8 airTime;
    /* 0xD4 */ f32 planeHovercraftBasePitch;
    /* 0xD8 */ u8 spinoutSoundOn; // bool
    /* 0xDC */ SoundHandle spinoutSound;
} VehicleSoundData;

/* Size: 0x4C / 76 Bytes */
typedef struct VehicleSoundAsset {
    /* 0x00 */ u16 soundId[2];
    /* 0x04 */ u8 intensityLevelsForPitch[2][5];
    /* 0x0E */ u8 intensityLevelsForVolume[2][5];
    /* 0x18 */ u16 pitchLevels[2][5];           // 10000 = 1.0
    /* 0x2C */ u8 volumeLevels[2][5];
    /* 0x36 */ u8 engineIdleSound;
    /* 0x37 */ u8 engineIdleMaxVolume;
    /* 0x38 */ u8 engineIdleMaxPitch;
    /* 0x39 */ u8 engineIdleMinPitch;
    /* 0x3A */ u8 unk3A_unused;
    /* 0x3B */ u8 unk3B_unused;
    /* 0x3C */ s16 pitchLateralSpeedScale;      // 10000 = 1.0
    /* 0x3E */ s16 thrustPitchVel;              // 10000 = 1.0
    /* 0x40 */ s16 thrustPitchDecay;            // 10000 = 1.0
    /* 0x32 */ s16 rollAnglePitchScale;         // 10000 = 1.0
    /* 0x44 */ s16 pitchAnglePitchScale;        // 10000 = 1.0
    /* 0x46 */ s16 thrustPitchMax;              // 10000 = 1.0
    /* 0x48 */ s16 thrustPitchSpeedScale;       // 10000 = 1.0
    /* 0x4A */ u8 planeHovercraftBasePitch;
} VehicleSoundAsset;

void racer_sound_update(Object *obj, u32 buttonsPressed, u32 buttonsHeld, s32 ticksDelta);
void racer_sound_free(Object *obj);
void racer_sound_doppler_effect(Object *observerObj, Camera *camera, Object *sourceObj, s32 tickDelta);
f32 log(f32 x);
VehicleSoundData *racer_sound_init(s32 characterId, s32 vehicleId);
void racer_sound_car(Object *obj, u32 buttonsPressed, u32 buttonsHeld, s32 ticksDelta);
void racer_sound_hovercraft(Object *, u32 buttonsPressed, u32 buttonsHeld, s32 tickDelta);
void racer_sound_plane(Object *, u32 buttonsPressed, u32 buttonsHeld, s32 tickDelta);
void racer_sound_update_all(Object **racerObjs, s32 numRacers, Camera *cameras, u8 numCameras, s32 tickDelta);

#endif
