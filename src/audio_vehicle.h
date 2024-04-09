#ifndef _AUDIO_VEHICLE_H_
#define _AUDIO_VEHICLE_H_

#include "types.h"
#include "structs.h"
#include "audio.h"

/* Size: 0x90 / 144 bytes */
typedef struct unk80119C48 {
    s32 unk18;
    s32 unk3C;
    s32 unk60;
    s32 unk84;
} unk80119C48;

/* Size: 0x180 / 384 bytes */
typedef struct unk80119C58 {
    union {
        /* 0x00 */ f32 unk0_01;
        /* 0x00 */ u8 unk0_02;
    } unk0;
    /* 0x004 */ Vec3f *unk4;
    /* 0x008 */ u8 pad9[0x164];
    /* 0x16C */ s32 soundID;
    /* 0x170 */ s32 unk170;
    /* 0x174 */ u8 unk174;
    /* 0x175 */ u8 unk175;
    /* 0x176 */ u8 unk176;
    /* 0x177 */ u8 unk177;
    /* 0x178 */ s32 unk178;
    /* 0x17C */ s8 unk17C;
    /* 0x17D */ u8 unk17D;
    /* 0x17E */ u8 unk17E;
} unk80119C58;

/* Size: 0xE0 / 224 bytes */
typedef struct VehicleSoundData {
    /* 0x00 */ u16 unk0[2];
    u8 unk4[2][4];
    /* 0x08 */ u8 pad8[0x2];
    u8 unkC[2][4];
    // /* 0x04 */ u8 unk4[4];
    // /* 0x08 */ u8 pad8[0x5];
    // /* 0x0D */ u8 unkD;
    // /* 0x0E */ u8 unkE[4];
    /* 0x16 */ u16 unk16;
    /* 0x18 */ u16 unk18[4];
    /* 0x20 */ u8 unk20[2];
    /* 0x22 */ u16 unk22;
    /* 0x24 */ u8 pad24[0x6];
    /* 0x2A */ u8 unk2A[2];
    /* 0x2C */ u8 unk2C[2];
    /* 0x2E */ u8 pad2E[0x3];
    /* 0x31 */ u8 unk31;
    /* 0x32 */ u8 pad32[0x4];
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 unk37;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
    /* 0x3A */ u8 pad3A[0x2];
    /* 0x3C */ f32 bananaPitch;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ u8 unk44[4];
    /* 0x48 */ u8 *unk48[2]; //soundMask / soundState?
    /* 0x50 */ u8 *unk50;
    /* 0x54 */ f32 unk54[2];
    /* 0x5C */ f32 unk5C[2];
    /* 0x64 */ u8 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C[2];
    /* 0x74 */ u8 unk74;
    /* 0x78 */ Vec3f racerPos;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 unk88; // Volume?
    /* 0x8C */ f32 unk8C; // Volume?
    /* 0x90 */ s8 unk90;
    /* 0x91 */ u8 unk91[3];
    /* 0x94 */ f32 enginePitch; // Engine noise for the car.
    /* 0x98 */ u8 unk98;
    /* 0x99 */ u8 pad99[0x7];
    /* 0xA0 */ u8 unkA0;
    /* 0xA4 */ f32 throttlePitch; // Engine noise for the hovercraft and plane.
    /* 0xA8 */ SoundMask *unkA8;
    /* 0xAC */ u16 unkAC;
    /* 0xB0 */ f32 throttlePitchVel;
    /* 0xB4 */ f32 throttlePitchDecay;
    /* 0xB8 */ u8 unkB8;
    /* 0xBC */ f32 unkBC;
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ f32 unkC4;
    /* 0xC8 */ f32 throttlePitchCeil;
    /* 0xCC */ f32 unkCC;
    /* 0xD0 */ u8 unkD0;
    /* 0xD4 */ f32 basePitch;
    /* 0xD8 */ u8 brakeSound; //Sound is playing bool?
    /* 0xDC */ SoundMask *brakeSoundMask; //soundMask / soundState?
} VehicleSoundData;

/* Size: 0x4C / 76 Bytes */
typedef struct unkAudioAsset {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ u8 unk4[4];
    /* 0x08 */ u8 pad8[0x4];
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 unkE[4];
    /* 0x12 */ u8 pad12[4];
    /* 0x16 */ u16 unk16;
    /* 0x18 */ u16 unk18[4];
    /* 0x20 */ u8 pad20[0xA];
    /* 0x2A */ u8 unk2A[2];
    /* 0x2C */ u8 unk2C[2];
    /* 0x2E */ u8 pad2E[0x8];
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 unk37;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
    /* 0x3A */ u8 unk3A;
    /* 0x3B */ u8 unk3B;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 unk3E;
    /* 0x40 */ s16 unk40;
    /* 0x32 */ s16 unk42;
    /* 0x44 */ s16 unk44;
    /* 0x46 */ s16 unk46;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ u8 unk4A;
} unkAudioAsset;

extern u8 gVehicleSounds;
extern s32 D_800DC6D8;
extern s32 D_800DC6DC;
extern u16 gUsedMasks;
extern unk80119C48 **gSoundMaskHeap;
extern SoundMask **gSoundMaskHeapUsed;
extern SoundMask **gSoundMaskHeapFree;
extern u8 gFreeMasks;

void racer_sound_update(Object *obj, u32 buttonsPressed, u32 buttonsHeld, s32 updateRate);
void racer_sound_free(Object *);

f32 func_80007FA4(f32 arg0);
VehicleSoundData *func_80004B40(s8 characterId, s8 vehicleId);
void func_80005254(Object *obj, u32 buttonsPressed, u32 buttonsHeld, s32 updateRate);
void racer_sound_hovercraft(Object *, u32 buttonsPressed, u32 buttonsHeld, s32 updateRate);
void func_800063EC(Object *, u32 buttonsPressed, u32 buttonsHeld, s32 updateRate);

#endif
