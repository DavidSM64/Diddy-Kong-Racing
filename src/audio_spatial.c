#include "audio_spatial.h"
#include "types.h"
#include "macros.h"
#include "audio_internal.h"
#include "audio_vehicle.h"
#include "memory.h"
#include "audio.h"
#include "textures_sprites.h"
#include "objects.h"
#include "audiosfx.h"
#include "tracks.h"
#include "math_util.h"

/************ .data ************/

u16 gUsedMasks = 0;

/*******************************/

/************ .rodata ************/

UNUSED const char D_800E4D00[] = "OUT OF AUDIO POINTS\n";
UNUSED const char D_800E4D18[] = "amAudioLineAddVertex: Exceeded maximum number of lines (%d)\n";
UNUSED const char D_800E4D58[] = "amAudioLineAddVertex: Exceeded maximum number of line vertices (%d)\n";
UNUSED const char D_800E4DA0[] = "amReverbLineAddVertex: Exceeded maximum number of lines (%d)\n";
UNUSED const char D_800E4DE0[] = "amReverbLineAddVertex: Exceeded maximum number of line vertices (%d)\n";

UNUSED const char D_800E4E28[] = "Audio line definition error (less than 2 vertices on line %d)\n";
UNUSED const char D_800E4E68[] = "Audio line definition error (line=%d, vertex=%d)\n";
UNUSED const char D_800E4E9C[] = "Reverb line definition error (less than 2 vertices on line %d)\n";
UNUSED const char D_800E4EDC[] = "Reverb line definition error (line=%d, vertex=%d)\n";

/*********************************/

/************ .bss ************/

SoundData *D_80119C40;
SoundMask **gSoundMaskHeapUsed;
SoundMask *gSoundMaskHeap; // 0x24 struct size - 0x5A0 total size - should be 40 elements
u8 gFreeMasks;
SoundMask **gSoundMaskHeapFree;
s32 D_80119C54; // Padding?
unk80119C58 D_80119C58[7];
unk8011A6D8 D_8011A6D8[7]; // Reverb stuff
s8 gAudioLinesOff;
s32 D_8011AC1C;

#define SOUND_MASK_HEAP_COUNT 40

/*******************************/

void audioline_init(void) {
    s32 i;

    sound_table_properties(&D_80119C40, NULL, NULL);
    gSoundMaskHeap = mempool_alloc_safe(sizeof(SoundMask) * SOUND_MASK_HEAP_COUNT, COLOUR_TAG_CYAN);
    gSoundMaskHeapFree = mempool_alloc_safe(sizeof(uintptr_t) * SOUND_MASK_HEAP_COUNT, COLOUR_TAG_CYAN);
    gSoundMaskHeapUsed = mempool_alloc_safe(sizeof(uintptr_t) * SOUND_MASK_HEAP_COUNT, COLOUR_TAG_CYAN);
    gUsedMasks = 0;
    for (i = 0; i < 7; i++) {
        D_80119C58[i].unk178 = NULL;
    }
    for (i = 0; i < SOUND_MASK_HEAP_COUNT; i++) {
        gSoundMaskHeap[i].unk18 = 0;
    }
    func_80008174();
}

/**
 * Stop any playing jingles, then block audio lines from playing anymore.
 * Official Name: amAmbientPause
 */
void audioline_off(void) {
    music_jingle_stop();
    gAudioLinesOff = TRUE;
}

/**
 * Allow audio lines to play jingles.
 * Official Name: amAmbientRestart
 */
void audioline_on(void) {
    gAudioLinesOff = FALSE;
}

#ifdef NON_EQUIVALENT
// extern f32 D_80119C60[672];
// extern f32 D_8011A6E0[7][48];
extern unk8011A6D8 **D_8011A6DC;
extern unk80119C58 **D_80119C5C;
// extern void sound_stop(u8 *arg0);
// audioline_reset
void func_80008174(void) {
    s32 i;
    s32 j;
    u8 *sound;

    for (gFreeMasks = 0; gFreeMasks < SOUND_MASK_HEAP_COUNT; gFreeMasks++) {
        gSoundMaskHeapFree[gFreeMasks] = &gSoundMaskHeap[gFreeMasks];
    }
    gFreeMasks--;

    for (i = 0; i < gUsedMasks; i++) {
        sound = (u8 *) gSoundMaskHeapUsed[i]->unk18;
        gSoundMaskHeapUsed[i]->unk12 = 0;
        if (sound != NULL) {
            sound_stop(sound);
        }
    }
    gUsedMasks = 0;

    for (i = 0; i < ARRAY_COUNT(D_80119C58); i++) {
        D_80119C58[i].soundID = 0;
        if (D_80119C58[i].unk178 != 0) {
            if (D_80119C58[i].unk0.unk0_02 == 0) {
                sound_stop(D_80119C58[i].unk178);
            } else if (D_80119C58[i].unk0.unk0_02 == 1) {
                music_jingle_stop();
            }
            D_80119C58[i].unk178 = 0;
        }
        D_80119C58[i].unk17C = -1;
        D_80119C5C[i]->unk0.unk0_01 = -100000.0f;

        // D_80119C58[i] = -100000.0f;
    }

    // for (i = 0; i < ARRAY_COUNT(D_8011A6E0); i++) {
    //     D_8011A6D8[i].unkB8 = -1;
    //     D_8011A6D8[i].unk0.unk0_01 = 0.0f;
    //     D_8011A6D8[i].unkBC = 0.0f;
    //     D_8011A6DC[i]->unk0.unk0_01 = -100000.0f;
    //     D_8011A6E0[i][0] = -100000.0f;
    //     for (j = 0; j < ARRAY_COUNT(D_8011A6E0[0]); j++) {
    //         D_8011A6E0[i][j] = -100000.0f;
    //     }
    // }

    gAudioLinesOff = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/audio_spatial/func_80008174.s")
#endif

// audioline_ambient
// Official Name: amPlayAudioMap
#pragma GLOBAL_ASM("asm/nonmatchings/audio_spatial/func_80008438.s")

/**
 * Official Name: amCalcSfxStereo
 */
s32 func_800090C0(f32 x, f32 z, s32 yRot) {
    s32 temp_v1;
    s32 ret;
    f32 sp1C;

    sp1C = sqrtf((x * x) + (z * z));
    temp_v1 = 0xFFFF - arctan2_f(x, z);

    if (temp_v1 < yRot) {
        if (sp1C <= 1.0f) {
            ret = 64 - ((sins_s16(yRot - temp_v1) / 1024) * (sp1C * 1));
        } else {
            ret = 64 - (sins_2(yRot - temp_v1) / 1024);
        }
    } else if (sp1C <= 1.0f) {
        ret = (sins_s16(temp_v1 - yRot) / 1024) * (sp1C * 1) + 64;
    } else {
        ret = (sins_2(temp_v1 - yRot) / 1024) + 64;
    }

    if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
        ret = 128 - ret;
    }

    return ret;
}

/**
 * Calculates the position between two points, then the distance from the nearest point.
 * Write the adjusted positions to the arguments.
 * Returns the distance between the input and the nearest endpoint.
 */
s32 audioline_distance(f32 inX, f32 inY, f32 inZ, floatXYZVals *floatXYZ, f32 *outX, f32 *outY, f32 *outZ) {
    f32 dx, dy, dz;
    f32 x1, y1, z1;
    f32 x2, y2, z2;

    f32 mag;
    f32 ret;

    x1 = floatXYZ->x1;
    y1 = floatXYZ->y1;
    z1 = floatXYZ->z1;
    x2 = floatXYZ->x2;
    y2 = floatXYZ->y2;
    z2 = floatXYZ->z2;
    mag = 0.0f;

    dx = x2 - x1;
    dy = y2 - y1;
    dz = z2 - z1;

    if (dx == 0.0 && dy == 0.0 && dz == 0.0) {
        mag = 0.0f;
    } else {
        mag = ((inX - x1) * dx + (inY - y1) * dy + (inZ - z1) * dz) / (dx * dx + dy * dy + dz * dz);
    }

    if (mag < 0.0f) {
        *outX = x1;
        *outY = y1;
        *outZ = z1;
        dx = x1 - inX;
        dy = y1 - inY;
        dz = z1 - inZ;
        ret = sqrtf(dx * dx + dy * dy + dz * dz);
    } else if (mag > 1.0f) {
        *outX = x2;
        *outY = y2;
        *outZ = z2;
        dx = x2 - inX;
        dy = y2 - inY;
        dz = z2 - inZ;
        ret = sqrtf(dx * dx + dy * dy + dz * dz);
    } else {
        *outX = mag * dx + x1, // Comma required here as this was likely all one line.
            *outY = mag * dy + y1, *outZ = mag * dz + z1;

        ret = sqrtf((*outX - inX) * (*outX - inX) + (*outY - inY) * (*outY - inY) + (*outZ - inZ) * (*outZ - inZ));
    }

    return ret;
}

/**
 * Play Sound at position
 */
void play_sound_at_position(u16 soundId, f32 x, f32 y, f32 z, u8 arg4, SoundMask **soundMask) {
    func_8000974C(D_80119C40[soundId].soundBite, x, y, z, arg4, D_80119C40[soundId].unk3, D_80119C40[soundId].volume,
                  D_80119C40[soundId].distance, 0, D_80119C40[soundId].pitch, D_80119C40[soundId].unk8, soundMask);
}

void func_800095E8(u16 soundId, f32 x, f32 y, f32 z, u8 arg4, u8 arg5, f32 pitch, SoundMask **soundMask) {
    func_8000974C(soundId, x, y, z, arg4, 100, arg5, 15000, 0, pitch, 0x3F, soundMask);
}

// I think this function is used to update the world position of any sound associated with the given soundmask.
void update_spatial_audio_position(SoundMask *arg0, f32 x, f32 y, f32 z) {
    arg0->pos.x = x;
    arg0->pos.y = y;
    arg0->pos.z = z;
}

/**
 * Official Name: amSndStopXYZ
 */
void func_800096F8(SoundMask *soundMask) {
    s32 i;
    for (i = 0; i < SOUND_MASK_HEAP_COUNT; i++) {
        if (soundMask == gSoundMaskHeapUsed[i]) {
            func_8000A2E8(i);
            break;
        }
    }
}

void func_8000974C(u16 soundBite, f32 x, f32 y, f32 z, u8 arg4, u8 arg5, u8 volume, u16 distance, u8 arg8, u8 pitch,
                   u8 argA, SoundMask **soundMask) {
    SoundMask *newMask;

    if (soundMask != NULL) {
        func_800245B4(soundBite | 0xE000);
    }
    if (gUsedMasks == SOUND_MASK_HEAP_COUNT) {
        if (soundMask != NULL) {
            *soundMask = NULL;
        }
        func_800245B4(0xAA55);
        return;
    }
    newMask = gSoundMaskHeapFree[gFreeMasks--];
    newMask->pos.x = x;
    newMask->pos.y = y;
    newMask->pos.z = z;
    newMask->soundId = soundBite;
    newMask->unk11 = arg4;
    newMask->unk10 = arg5;
    newMask->volume = volume;
    newMask->pitch = pitch;
    newMask->distance = distance;
    newMask->unk20 = arg8;
    newMask->unk21 = argA;
    newMask->unk22 = 0;
    newMask->soundMask = soundMask;
    gSoundMaskHeapUsed[gUsedMasks++] = newMask;
    if (soundMask != NULL) {
        *soundMask = newMask;
    }
}

void audioline_ambient_create(u8 arg0, u16 soundId, f32 x, f32 y, f32 z, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u16 arg9,
                              u8 argA, u8 lineID, u8 argC) {
    unk80119C58 *temp_v1;
    f32 *temp_a0;

    if (lineID < 7 && argC < 30) {
        temp_v1 = &D_80119C58[lineID];
        temp_a0 = &temp_v1->unk4[argC * 3];
        temp_a0[0] = x;
        temp_a0[1] = y;
        temp_a0[2] = z;
        if (argC == 0) {
            temp_v1->soundID = soundId;
            temp_v1->unk0.unk0_02 = arg0;
            temp_v1->unk170 = arg9;
            temp_v1->unk17D = argA;
            temp_v1->unk174 = arg6;
            temp_v1->unk175 = arg5;
            temp_v1->unk176 = arg7;
            temp_v1->unk17E = arg8;
        }
        if (temp_v1->unk17C < argC) {
            temp_v1->unk17C = argC;
        }
    }
}

#ifdef NON_EQUIVALENT
// single regalloc diff, or at least it used to be...
// audioline_reverb_create
void func_80009968(f32 x, f32 y, f32 z, u8 arg3, u8 arg4, u8 arg5) {
    Vec3f *temp_a1;
    s32 tempArg5 = arg5;

    if ((arg4 < 7) && (tempArg5 < 15)) {
        temp_a1 = (Vec3f *) &D_8011A6D8[arg4].unk4.unk4_05;
        temp_a1[tempArg5].x = x;
        temp_a1[tempArg5].y = y;
        temp_a1[tempArg5].z = z;
        if (tempArg5 == 0) {
            D_8011A6D8[arg4].unk0.unk0_02 = arg3 & 0xFF;
        }
        if (D_8011A6D8[arg4].unkB8 < tempArg5) {
            D_8011A6D8[arg4].unkB8 = tempArg5;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/audio_spatial/func_80009968.s")
#endif

s32 func_800099EC(u8 arg0) {
    s32 ret;
    f32 *var_a2;
    f32 temp_f0;
    s32 i;
    unk80119C58 *temp_v0;

    ret = 1;
    temp_v0 = &D_80119C58[arg0];
    var_a2 = (f32 *) &temp_v0->unk4;

    if (temp_v0->unk17C <= 0) {
        return 0;
    }

    for (i = 0; i < temp_v0->unk17C; i++) {
        temp_f0 = *var_a2;
        if (temp_f0 == -100000.0 || temp_f0 + 1 == -100000.0 || temp_f0 + 2 == -100000.0) {
            ret = 0;
        }
        var_a2 += 3;
    }

    return ret;
}

s32 func_80009AB4(u8 arg0) {
    s32 ret;
    f32 *var_a2;
    f32 temp_f0;
    s32 i;
    unk8011A6D8 *temp_v0;

    ret = 1;
    temp_v0 = &D_8011A6D8[arg0];
    var_a2 = (f32 *) &temp_v0->unk4;

    if (temp_v0->unkB8 <= 0) {
        return 0;
    }

    for (i = 0; i < temp_v0->unkB8; i++) {
        temp_f0 = *var_a2;
        if (temp_f0 == -100000.0 || temp_f0 + 1 == -100000.0 || temp_f0 + 2 == -100000.0) {
            ret = 0;
        }
        var_a2 += 3;
    }

    return ret;
}

#ifdef NON_EQUIVALENT
u8 func_80009D6C(unk8011A6D8 *, f32, f32, f32);
// audioline_reverb
void func_80009B7C(s32 *soundState, f32 x, f32 y, f32 z) {
    s32 j;
    f32 outX;
    f32 outY;
    f32 outZ;
    s32 levelSegmentIndex;
    f32 yVals[8]; // Not sure of the number needed
    s32 distBetween;
    s32 numOfYVals;
    u8 temp_v0_4;
    u8 volume;
    s32 var_s6;
    s32 i;
    s32 k;

    levelSegmentIndex = get_level_segment_index_from_position(x, y, z);
    volume = 0;
    var_s6 = 400;
    for (i = 0; i < 7; i++) {
        if (D_8011A6D8[i].unk0.unk0_02 != 0) {
            if (func_80009AB4(i) != 0) {
                for (j = 0; j < D_8011A6D8[i].unkB8; j++) {
                    distBetween = audioline_distance(x, y, z, &D_8011A6D8[i].unk4.unk4_02[j], &outX, &outY, &outZ);
                    if (distBetween < var_s6) {
                        numOfYVals = func_8002BAB0(levelSegmentIndex, x, z, yVals);
                        for (k = 0; k < numOfYVals; k++) {
                            if (y < yVals[k]) {
                                var_s6 = distBetween;
                                temp_v0_4 = func_80009D6C(&D_8011A6D8[i], outX, outY, outZ);
                                if (volume < temp_v0_4) {
                                    volume = temp_v0_4;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (soundState != NULL) {
        sound_event_update((s32) soundState, 0x100, (u32) volume);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/audio_spatial/func_80009B7C.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/audio_spatial/func_80009D6C.s")

#ifdef NON_EQUIVALENT
extern unk80119C58 **D_80119C5C;
extern unk8011A6D8 **D_8011A6DC;
// debug_render_audio_effects
void func_8000A184(Gfx **arg0, Vertex **arg1, Triangle **arg2) {
    s32 i, j;

    for (i = 0; i < 7; i++) {
        if (D_80119C58[i].soundID != 0) {
            for (j = 0; j < D_80119C58[i].unk17C; j++) {
                debug_render_line(arg0, arg1, arg2, (floatXYZVals *) &D_80119C5C[i], 0xFF, 0xFF, 0);
            }
        }
    }

    for (i = 0; i < 7; i++) {
        if (D_8011A6D8[i].unk0.unk0_02 != 0) {
            for (j = 0; j < D_8011A6D8[i].unkB8; j++) {
                debug_render_line(arg0, arg1, arg2, (floatXYZVals *) &D_8011A6DC[i], 0xFF, 0xFF, 0);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/audio_spatial/func_8000A184.s")
#endif

void func_8000A2E8(s32 arg0) {
    if (gUsedMasks != 0) {
        if (gSoundMaskHeapUsed[arg0]->unk18 != 0) {
            sound_stop(gSoundMaskHeapUsed[arg0]->unk18);
        }
        if (gSoundMaskHeapUsed[arg0]->soundMask != NULL) {
            *gSoundMaskHeapUsed[arg0]->soundMask = NULL;
            func_800245B4(gSoundMaskHeapUsed[arg0]->soundId | 0x5000);
        }
        gFreeMasks++;
        gSoundMaskHeapFree[gFreeMasks] = gSoundMaskHeapUsed[arg0];
        gSoundMaskHeapUsed[arg0] = gSoundMaskHeapUsed[gUsedMasks - 1];
        gUsedMasks--;
    }
}

/**
 * Generates and renders a coloured line visible from anywhere.
 * Allows use of a colour, that interpolates from bright to dark from the beginning to the end of the line.
 */
void debug_render_line(Gfx **dList, Vertex **verts, Triangle **tris, floatXYZVals *coords, u8 red, u8 green, u8 blue) {
    Gfx *temp_dlist;
    Vertex *temp_verts;
    Triangle *temp_tris;
    s16 x1;
    s16 y1;
    s16 z1;
    s16 x2;
    s16 y2;
    s16 z2;

    x1 = coords->x1;
    y1 = coords->y1;
    z1 = coords->z1;
    x2 = coords->x2;
    y2 = coords->y2;
    z2 = coords->z2;
    temp_dlist = *dList;

    temp_verts = *verts;
    temp_tris = *tris;
    load_and_set_texture_no_offset(&temp_dlist, NULL, RENDER_NONE);
    gSPVertexDKR(temp_dlist++, OS_PHYSICAL_TO_K0(temp_verts), 4, 0);
    gSPPolygon(temp_dlist++, OS_PHYSICAL_TO_K0(temp_tris), 2, 0);
    temp_verts[0].x = x1;
    temp_verts[0].y = (y1 + 5);
    temp_verts[0].z = z1;
    temp_verts[0].r = red;
    temp_verts[0].g = green;
    temp_verts[0].b = blue;
    temp_verts[0].a = 255;
    temp_verts[1].x = x1;
    temp_verts[1].y = (y1 - 5);
    temp_verts[1].z = z1;
    temp_verts[1].r = red;
    temp_verts[1].g = green;
    temp_verts[1].b = blue;
    temp_verts[1].a = 255;
    temp_verts[2].x = x2;
    temp_verts[2].y = (y2 + 5);
    temp_verts[2].z = z2;
    temp_verts[2].r = 255;
    temp_verts[2].g = 255;
    temp_verts[2].b = 255;
    temp_verts[2].a = 255;
    temp_verts[3].x = x2;
    temp_verts[3].y = (y2 - 5);
    temp_verts[3].z = z2;
    temp_verts[3].r = 255;
    temp_verts[3].g = 255;
    temp_verts[3].b = 255;
    temp_verts[3].a = 255;
    temp_verts += 4;

    temp_tris[0].flags = BACKFACE_DRAW;
    temp_tris[0].vi0 = 2;
    temp_tris[0].vi1 = 1;
    temp_tris[0].vi2 = 0;
    temp_tris[0].uv0.u = 1024 - 32;
    temp_tris[0].uv0.v = 1024 - 32;
    temp_tris[0].uv1.u = 1024 - 32;
    temp_tris[0].uv1.v = 0;
    temp_tris[0].uv2.u = 1;
    temp_tris[0].uv2.v = 0;
    temp_tris[1].flags = BACKFACE_DRAW;
    temp_tris[1].vi0 = 3;
    temp_tris[1].vi1 = 2;
    temp_tris[1].vi2 = 1;
    temp_tris[1].uv0.u = 1;
    temp_tris[1].uv0.v = 1024 - 32;
    temp_tris[1].uv1.u = 1024 - 32;
    temp_tris[1].uv1.v = 1024 - 32;
    temp_tris[1].uv2.u = 1;
    temp_tris[1].uv2.v = 0;
    temp_tris += 2;

    *dList = temp_dlist;
    *verts = temp_verts;
    *tris = temp_tris;
}
