#include "audio_spatial.h"
#include "types.h"
#include "macros.h"
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
    for (i = 0; i < ARRAY_COUNT(D_80119C58); i++) {
        D_80119C58[i].soundPtr = NULL;
    }
    for (i = 0; i < SOUND_MASK_HEAP_COUNT; i++) {
        gSoundMaskHeap[i].soundPtr = NULL;
    }
    audioline_reset();
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

void audioline_reset(void) {
    s32 i;
    s32 j;
    SoundHandle sound;
    SoundMask *heap;
    f32 *ptr;

    heap = gSoundMaskHeap;
    gFreeMasks = 0;
    while (gFreeMasks < SOUND_MASK_HEAP_COUNT) {
        gSoundMaskHeapFree[gFreeMasks] = heap;
        heap++;
        gFreeMasks++;
    }

    gFreeMasks--;

    for (i = 0; i < gUsedMasks; i++) {
        sound = gSoundMaskHeapUsed[i]->soundPtr;
        gSoundMaskHeapUsed[i]->unk12 = 0;
        if (sound != NULL) {
            sound_stop(sound);
        }
    }
    gUsedMasks = 0;

    for (i = 0; i < 7; i++) {
        D_80119C58[i].soundID = 0;
        if (D_80119C58[i].soundPtr != 0) {
            if (D_80119C58[i].unk0_02 == 0) {
                sound_stop(D_80119C58[i].soundPtr);
            } else if (D_80119C58[i].unk0_02 == 1) {
                music_jingle_stop();
            }
            D_80119C58[i].soundPtr = NULL;
        }
        D_80119C58[i].unk17C = -1;

        ptr = D_80119C58[i].unk4_floats;
        for (j = 0; j < 30; j++) {
            *ptr++ = -100000.0f;
            *ptr++ = -100000.0f;
            *ptr++ = -100000.0f;
        }
    }

    for (i = 0; i < 7; i++) {
        D_8011A6D8[i].unkB8 = -1;
        D_8011A6D8[i].unk0_02 = 0;
        D_8011A6D8[i].unkBC = 0.0f;

        ptr = D_8011A6D8[i].unk4_floats;
        for (j = 0; j < 15; j++) {
            *ptr++ = -100000.0f;
            *ptr++ = -100000.0f;
            *ptr++ = -100000.0f;
        }
    }

    gAudioLinesOff = 0;
}

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
s32 audioline_distance(f32 inX, f32 inY, f32 inZ, f32 coords[6], f32 *outX, f32 *outY, f32 *outZ) {
    f32 dx, dy, dz;
    f32 x1, y1, z1;
    f32 x2, y2, z2;

    f32 mag;
    f32 ret;

    x1 = coords[0];
    y1 = coords[1];
    z1 = coords[2];
    x2 = coords[3];
    y2 = coords[4];
    z2 = coords[5];
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
        temp_a0 = &temp_v1->unk4_floats[argC * 3];
        temp_a0[0] = x;
        temp_a0[1] = y;
        temp_a0[2] = z;
        if (argC == 0) {
            temp_v1->soundID = soundId;
            temp_v1->unk0_02 = arg0;
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

void audioline_reverb_create(f32 x, f32 y, f32 z, u8 arg3, u8 arg4, u8 arg5) {
    unk8011A6D8 *temp;
    if (arg4 < ARRAY_COUNT(D_8011A6D8) && arg5 < 15) {
        temp = &D_8011A6D8[arg4];
        temp->unk4_floats[3 * arg5 + 0] = x;
        temp->unk4_floats[3 * arg5 + 1] = y;
        temp->unk4_floats[3 * arg5 + 2] = z;
        if (arg5 == 0) {
            temp->unk0_02 = arg3;
        }
        if (temp->unkB8 < arg5) {
            temp->unkB8 = arg5;
        }
    }
}

s32 func_800099EC(u8 arg0) {
    s32 ret;
    s32 i;
    unk80119C58 *temp_v0;
    f32 *var_a2;

    ret = 1;
    temp_v0 = &D_80119C58[arg0];
    var_a2 = temp_v0->unk4_floats;

    if (temp_v0->unk17C <= 0) {
        return 0;
    }

    for (i = 0; i < temp_v0->unk17C; i++) {
        //@bug should be *(var_a2 + 0), *(var_a2 + 1), *(var_a2 + 2)
        if (*var_a2 + 0 == -100000.0 || *var_a2 + 1 == -100000.0 || *var_a2 + 2 == -100000.0) {
            ret = 0;
        }
        var_a2 += 3;
    }

    return ret;
}

s32 func_80009AB4(u8 arg0) {
    s32 ret;
    s32 i;
    unk8011A6D8 *temp_v0;
    f32 *var_a2;

    ret = 1;
    temp_v0 = &D_8011A6D8[arg0];
    var_a2 = temp_v0->unk4_floats;

    if (temp_v0->unkB8 <= 0) {
        return 0;
    }

    for (i = 0; i < temp_v0->unkB8; i++) {
        //@bug should be *(var_a2 + 0), *(var_a2 + 1), *(var_a2 + 2)
        if (*var_a2 == -100000.0 || *var_a2 + 1 == -100000.0 || *var_a2 + 2 == -100000.0) {
            ret = 0;
        }
        var_a2 += 3;
    }

    return ret;
}

void audioline_reverb(s32 *soundState, f32 x, f32 y, f32 z) {
    s32 i;
    s32 j;
    unk8011A6D8 *temp;
    s32 k;
    f32 outX;
    f32 outY;
    f32 outZ;
    s32 distBetween;
    s32 maxDist;
    s32 levelSegmentIndex;
    s32 numOfYVals;
    u8 volume;
    u8 temp_v0_4;
    f32 *coords;
    f32 yVals[10];

    levelSegmentIndex = get_level_segment_index_from_position(x, y, z);
    volume = 0;
    maxDist = 400;
    for (i = 0; i < ARRAY_COUNT(D_8011A6D8); i++) {
        temp = &D_8011A6D8[i];
        if (temp->unk0_02 != 0) {
            if (func_80009AB4(i) != 0) {
                coords = temp->unk4_floats;
                for (j = 0; j < temp->unkB8; j++) {
                    distBetween = audioline_distance(x, y, z, coords, &outX, &outY, &outZ);
                    if (distBetween < maxDist) {
                        numOfYVals = func_8002BAB0(levelSegmentIndex, x, z, yVals);
                        for (k = 0; k < numOfYVals; k++) {
                            if (y < yVals[k]) {
                                maxDist = distBetween;
                                temp_v0_4 = func_80009D6C(&D_8011A6D8[i], outX, outY, outZ);
                                if (volume < temp_v0_4) {
                                    volume = temp_v0_4;
                                }
                            }
                        }
                    }
                    coords += 3;
                }
            }
        }
    }
    if (soundState != NULL) {
        sound_event_update((s32) soundState, AL_SNDP_FX_EVT, (u32) volume);
    }
}

u8 func_80009D6C(unk8011A6D8 *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 deltaX;
    f32 deltaY;
    f32 deltaZ;
    f32 *coords;
    f32 x1, y1, z1;
    f32 x2, y2, z2;
    f32 dx, dy, dz;
    f32 f20;
    f32 sp5C;
    f32 length;
    u8 sp57;
    f32 f12;

    if (arg0->unkBC == 0.0f) {
        coords = arg0->unk4_floats;
        for (f20 = 0.0f; f20 < arg0->unkB8; f20 += 1.0f) {
            deltaX = coords[3] - coords[0];
            deltaY = coords[4] - coords[1];
            deltaZ = coords[5] - coords[2];
            arg0->unkBC += sqrtf((deltaX * deltaX) + (deltaY * deltaY) + (deltaZ * deltaZ));
            coords += 3;
        }
    }

    coords = arg0->unk4_floats;
    sp5C = 0.0f;
    sp57 = FALSE;

    for (; !sp57; coords += 3) {
        x1 = coords[0];
        y1 = coords[1];
        z1 = coords[2];
        x2 = coords[3];
        y2 = coords[4];
        z2 = coords[5];
        dx = x2 - x1;
        dy = y2 - y1;
        dz = z2 - z1;
        length = sqrtf((dx * dx) + (dy * dy) + (dz * dz));

        if (arg1 >= x1 && arg1 <= x2 || arg1 >= x2 && arg1 <= x1) {
            if (dx != 0.0f) {
                f12 = (arg1 - x1) / dx;
            } else if (dy != 0.0f) {
                f12 = (arg2 - y1) / dy;
            } else if (dz != 0.0f) {
                f12 = (arg3 - z1) / dz;
            } else {
                f12 = 0.0f;
            }

            if (ABS(dy * f12 + y1 - arg2) < 2.0f && ABS(dz * f12 + z1 - arg3) < 2.0f) {
                sp57 = TRUE;
                sp5C += f12 * length;
            } else {
                sp5C += length;
            }
        } else {
            sp5C += length;
        }
    }

    if (sp5C > arg0->unkBC / 2) {
        sp5C = arg0->unkBC - sp5C;
    }

    if (sp5C < 300.0f) {
        return arg0->unk0_02 * sp5C / 300.0f;
    } else {
        return arg0->unk0_02;
    }
}

void debug_render_audio_effects(Gfx **dList, Vertex **verts, Triangle **tris) {
    s32 i, j;
    f32 *coords;
    unk80119C58 *var_s2;
    unk8011A6D8 *var_s2_2;

    for (i = 0; i < ARRAY_COUNT(D_80119C58); i++) {
        var_s2 = &D_80119C58[i];
        coords = var_s2->unk4_floats;
        if (D_80119C58[i].soundID != 0) {
            for (j = 0; j < var_s2->unk17C; j++) {
                debug_render_line(dList, verts, tris, coords, 255, 255, 0);
                coords += 3;
            }
        }
    }

    for (i = 0; i < ARRAY_COUNT(D_8011A6D8); i++) {
        var_s2_2 = &D_8011A6D8[i];
        coords = var_s2_2->unk4_floats;
        if (D_8011A6D8[i].unk0_02 != 0) {
            for (j = 0; j < var_s2_2->unkB8; j++) {
                debug_render_line(dList, verts, tris, coords, 255, 0, 255);
                coords += 3;
            }
        }
    }
}

void func_8000A2E8(s32 arg0) {
    if (gUsedMasks != 0) {
        if (gSoundMaskHeapUsed[arg0]->soundPtr != 0) {
            sound_stop(gSoundMaskHeapUsed[arg0]->soundPtr);
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
void debug_render_line(Gfx **dList, Vertex **verts, Triangle **tris, f32 coords[6], u8 red, u8 green, u8 blue) {
    Gfx *temp_dlist;
    Vertex *temp_verts;
    Triangle *temp_tris;
    s16 x1;
    s16 y1;
    s16 z1;
    s16 x2;
    s16 y2;
    s16 z2;

    x1 = coords[0];
    y1 = coords[1];
    z1 = coords[2];
    x2 = coords[3];
    y2 = coords[4];
    z2 = coords[5];
    temp_dlist = *dList;

    temp_verts = *verts;
    temp_tris = *tris;
    material_set_no_tex_offset(&temp_dlist, NULL, RENDER_NONE);
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
