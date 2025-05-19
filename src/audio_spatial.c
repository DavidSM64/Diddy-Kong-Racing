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

#define MAX_AUDIO_POINTS 40
#define MAX_AUDIO_LINES 7
#define MAX_REVERB_LINES 7
#define MIN_VOLUME_THRESHOLD 10

/************ .data ************/

u16 gNumAudioPoints = 0;

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

SoundData *gSpatialSoundTable;
AudioPoint **gAudioPoints;
AudioPoint *gAudioPointsPool; // 0x24 struct size - 0x5A0 total size - should be 40 elements
u8 gLastFreePointIndex;
AudioPoint **gFreeAudioPoints;
AudioLine gAudioLines[MAX_AUDIO_LINES];
ReverbLine gReverbLines[MAX_REVERB_LINES]; // Reverb stuff
u8 gJinglesOff;
s32 D_8011AC1C;

/*******************************/

/**
 * Initializes the audio spatial system.
 */
void audspat_init(void) {
    s32 i;

    sound_table_properties(&gSpatialSoundTable, NULL, NULL);
    gAudioPointsPool = mempool_alloc_safe(sizeof(AudioPoint) * MAX_AUDIO_POINTS, COLOUR_TAG_CYAN);
    gFreeAudioPoints = mempool_alloc_safe(sizeof(uintptr_t) * MAX_AUDIO_POINTS, COLOUR_TAG_CYAN);
    gAudioPoints = mempool_alloc_safe(sizeof(uintptr_t) * MAX_AUDIO_POINTS, COLOUR_TAG_CYAN);
    gNumAudioPoints = 0;
    for (i = 0; i < ARRAY_COUNT(gAudioLines); i++) {
        gAudioLines[i].soundHandle = NULL;
    }
    for (i = 0; i < MAX_AUDIO_POINTS; i++) {
        gAudioPointsPool[i].soundHandle = NULL;
    }
    audspat_reset();
}

/**
 * Stop any playing jingles, then block audio lines from playing anymore.
 * Does not stop audio lines that are playing sounds of type AUDIO_LINE_TYPE_SOUND.
 * Official Name: amAmbientPause
 */
void audspat_jingle_off(void) {
    music_jingle_stop();
    gJinglesOff = TRUE;
}

/**
 * Allow audio lines to play jingles.
 * Official Name: amAmbientRestart
 */
void audspat_jingle_on(void) {
    gJinglesOff = FALSE;
}

/**
 * Stops all sounds and deletes all created audio points and lines.
 */
void audspat_reset(void) {
    s32 i;
    s32 j;
    SoundHandle sound;
    AudioPoint *audioPoint;
    f32 *coords;

    audioPoint = gAudioPointsPool;
    gLastFreePointIndex = 0;
    while (gLastFreePointIndex < MAX_AUDIO_POINTS) {
        gFreeAudioPoints[gLastFreePointIndex] = audioPoint;
        audioPoint++;
        gLastFreePointIndex++;
    }

    gLastFreePointIndex--;

    for (i = 0; i < gNumAudioPoints; i++) {
        sound = gAudioPoints[i]->soundHandle;
        gAudioPoints[i]->inRange = FALSE;
        if (sound != NULL) {
            sndp_stop(sound);
        }
    }
    gNumAudioPoints = 0;

    for (i = 0; i < MAX_AUDIO_LINES; i++) {
        gAudioLines[i].soundBite = 0;
        if (gAudioLines[i].soundHandle != 0) {
            if (gAudioLines[i].type == AUDIO_LINE_TYPE_SOUND) {
                sndp_stop(gAudioLines[i].soundHandle);
            } else if (gAudioLines[i].type == AUDIO_LINE_TYPE_JINGLE) {
                music_jingle_stop();
            }
            gAudioLines[i].soundHandle = NULL;
        }
        gAudioLines[i].numSegments = -1;

        coords = gAudioLines[i].coords;
        for (j = 0; j < 30; j++) {
            *coords++ = -100000.0f;
            *coords++ = -100000.0f;
            *coords++ = -100000.0f;
        }
    }

    for (i = 0; i < MAX_REVERB_LINES; i++) {
        gReverbLines[i].numSegments = -1;
        gReverbLines[i].reverbAmount = 0;
        gReverbLines[i].totalLength = 0.0f;

        coords = gReverbLines[i].coords;
        for (j = 0; j < 15; j++) {
            *coords++ = -100000.0f;
            *coords++ = -100000.0f;
            *coords++ = -100000.0f;
        }
    }

    gJinglesOff = FALSE;
}

/**
 * Updates the parameters for audio points and lines, and invokes the handler for vehicle sounds.
 * Official Name: amPlayAudioMap
 */
void audspat_update_all(Object **objList, s32 numObjects, s32 updateRate) {
    s32 viewportCount;
    s32 i;
    s32 j;
    s32 k;
    s32 volume;
    s32 pan;
    s32 jingleVolume;
    s32 jinglePan;
    s32 jingleSound;
    f32 dx, dy, dz;
    s32 distance;
    AudioPoint *audioPoint;
    f32 outX;
    f32 outY;
    f32 outZ;
    s32 minDist;
    s32 adjustedVolume;
    s32 lineDistances[29];
    s32 pan2;
    s32 inverseSum;
    s32 linePans[29];
    s32 inverseDistances[29];
    s32 sumOfDistances;
    s32 numCameras;
    Camera *cameras;
    f32 pitch1;
    f32 temp;
    f32 minDistance;
    f32 *coords;
    f32 pitch2;
    s32 unused;
    f32 pitch3;

    jingleVolume = 0;
    viewportCount = cam_get_viewport_layout();
    numCameras = set_active_viewports_and_max(viewportCount);
    cameras = get_cutscene_camera_segment();

    // Update audio points
    for (i = 0; i < gNumAudioPoints; i++) {
        audioPoint = gAudioPoints[i];
        volume = 0;

        if (audioPoint->flags & AUDIO_POINT_FLAG_SINGLE_PLAYER) {
            if (numCameras == 1) {
                dx = audioPoint->pos.x - cameras[0].trans.x_position;
                dy = audioPoint->pos.y - cameras[0].trans.y_position;
                dz = audioPoint->pos.z - cameras[0].trans.z_position;
                distance = sqrtf(dx * dx + dy * dy + dz * dz);
                if (distance < audioPoint->range && !audioPoint->inRange) {
                    if (audioPoint->soundHandle == NULL &&
                        (!audioPoint->triggeredOnce || !(audioPoint->flags & AUDIO_POINT_FLAG_ONE_TIME_TRIGGER))) {
                        func_80001F14(audioPoint->soundBite, &audioPoint->soundHandle);
                        audioPoint->triggeredOnce = TRUE;
                    }

                    if (audioPoint->soundHandle != NULL) {
                        pitch1 = audioPoint->pitch / 100.0f;
                        sndp_set_param(audioPoint->soundHandle, AL_SNDP_VOL_EVT, audioPoint->volume * 256);
                        sndp_set_param(audioPoint->soundHandle, AL_SNDP_PITCH_EVT, *(s32 *) &pitch1);
                        pan2 = audspat_calculate_spatial_pan(dx, dz, cameras[0].trans.rotation.y_rotation);
                        // This can never be true
                        if (numCameras != 1) {
                            pan2 = 64;
                        }
                        sndp_set_param(audioPoint->soundHandle, AL_SNDP_PAN_EVT, pan2);
                        audspat_calculate_echo(audioPoint->soundHandle, audioPoint->pos.x, audioPoint->pos.y,
                                               audioPoint->pos.z);
                        sndp_set_priority(audioPoint->soundHandle, audioPoint->priority);
                    }

                    audioPoint->inRange = TRUE;
                } else if (distance > audioPoint->range && audioPoint->inRange) {
                    audioPoint->inRange = FALSE;
                }
            }
        } else {
            // Calculate volume and pan for all cameras and find the max volume
            for (j = 0; j < numCameras; j++) {
                dx = audioPoint->pos.x - cameras[j].trans.x_position;
                dy = audioPoint->pos.y - cameras[j].trans.y_position;
                dz = audioPoint->pos.z - cameras[j].trans.z_position;
                distance = sqrtf(dx * dx + dy * dy + dz * dz);
                if (distance < audioPoint->range) {
                    if (!audioPoint->fastFalloff) {
                        adjustedVolume = (1.0f - (f32) distance / (f32) audioPoint->range) * audioPoint->volume;
                    } else {
                        temp = (f32) (audioPoint->range - distance) / (f32) audioPoint->range;
                        adjustedVolume = temp * temp * audioPoint->volume;
                    }

                    if (volume < adjustedVolume) {
                        volume = adjustedVolume;
                        pan = audspat_calculate_spatial_pan(dx, dz, cameras[j].trans.rotation.y_rotation);
                    }
                }
            }

            // If all cameras are far enough then set volume to minVolume
            // and calculate pan based on the closest camera
            if (volume < audioPoint->minVolume) {
                minDistance = 999999.0f;

                for (j = 0; j < numCameras; j++) {
                    dx = audioPoint->pos.x - cameras[j].trans.x_position;
                    dy = audioPoint->pos.y - cameras[j].trans.y_position;
                    dz = audioPoint->pos.z - cameras[j].trans.z_position;
                    distance = sqrtf(dx * dx + dy * dy + dz * dz);
                    if (distance < minDistance) {
                        pan = audspat_calculate_spatial_pan(dx, dz, cameras[j].trans.rotation.y_rotation);
                        minDistance = distance;
                    }
                }

                volume = audioPoint->minVolume;
            }

            if (volume > MIN_VOLUME_THRESHOLD) {
                if (audioPoint->soundHandle == NULL &&
                    (!audioPoint->triggeredOnce || !(audioPoint->flags & AUDIO_POINT_FLAG_ONE_TIME_TRIGGER))) {
                    func_80001F14(audioPoint->soundBite, &audioPoint->soundHandle);
                    audioPoint->triggeredOnce = TRUE;
                }

                if (audioPoint->soundHandle != NULL) {
                    pitch2 = audioPoint->pitch / 100.0f;
                    sndp_set_param(audioPoint->soundHandle, AL_SNDP_VOL_EVT, volume * 256);
                    sndp_set_param(audioPoint->soundHandle, AL_SNDP_PITCH_EVT, *(s32 *) &pitch2);
                    if (numCameras != 1) {
                        pan = 64;
                    }
                    sndp_set_param(audioPoint->soundHandle, AL_SNDP_PAN_EVT, pan);
                    sndp_set_priority(audioPoint->soundHandle, audioPoint->priority);
                    audspat_calculate_echo(audioPoint->soundHandle, audioPoint->pos.x, audioPoint->pos.y,
                                           audioPoint->pos.z);
                }
            } else {
                if (audioPoint->soundHandle != NULL) {
                    sndp_stop(audioPoint->soundHandle);
                } else {
                    audioPoint->triggeredOnce = TRUE;
                }
            }

            if ((audioPoint->flags & AUDIO_POINT_FLAG_ONE_TIME_TRIGGER) && audioPoint->triggeredOnce &&
                audioPoint->soundHandle == NULL) {
                audspat_point_stop_by_index(i);
            }
        }
    }

    // Update audio lines
    for (i = 0; i < MAX_AUDIO_LINES; i++) {
        AudioLine *line = &gAudioLines[i];

        if (line->soundBite != SOUND_NONE && audspat_line_validate(i)) {
            volume = 0;

            for (j = 0; j < numCameras; j++) {
                coords = line->coords;
                sumOfDistances = 0;
                minDist = line->range;
                for (k = 0; k < line->numSegments; k++) {
                    lineDistances[k] =
                        audspat_distance_to_segment(cameras[j].trans.x_position, cameras[j].trans.y_position,
                                                    cameras[j].trans.z_position, coords, &outX, &outY, &outZ);
                    linePans[k] = audspat_calculate_spatial_pan(outX - cameras[j].trans.x_position,
                                                                outZ - cameras[j].trans.z_position,
                                                                cameras[j].trans.rotation.y_rotation);
                    if (minDist > lineDistances[k]) {
                        minDist = lineDistances[k];
                    }
                    coords += 3;
                    sumOfDistances += lineDistances[k];
                }

                if (!line->fastFalloff) {
                    adjustedVolume = (1.0f - (f32) minDist / (f32) line->range) * line->unk174;
                } else {
                    temp = (f32) (line->range - minDist) / (f32) line->range;
                    adjustedVolume = temp * temp * line->unk174;
                }

                if (volume <= adjustedVolume) {
                    volume = adjustedVolume;

                    if (line->numSegments == 1) {
                        pan = linePans[0];
                    } else {
                        inverseSum = 0;
                        for (k = 0; k < line->numSegments; k++) {
                            inverseDistances[k] = sumOfDistances - lineDistances[k];
                            inverseSum += inverseDistances[k];
                        }

                        pan = 0;
                        for (k = 0; k < line->numSegments; k++) {
                            pan += (f32) inverseDistances[k] / (f32) inverseSum * (f32) linePans[k];
                        }
                    }

                    if (minDist < 400) {
                        pan = (pan - 64) * (minDist / 400.0f) + 64;
                    }
                }
            }

            if (line->type == AUDIO_LINE_TYPE_SOUND) {
                if (volume < line->maxVolume) {
                    volume = line->maxVolume;
                }

                if (volume > MIN_VOLUME_THRESHOLD) {
                    pitch3 = line->unk176 / 100.0f;

                    if (line->soundHandle == NULL) {
                        func_80001F14(line->soundBite, &line->soundHandle);
                    }

                    if (line->soundHandle != NULL) {
                        sndp_set_param(line->soundHandle, AL_SNDP_VOL_EVT, volume * 256);
                        sndp_set_param(line->soundHandle, AL_SNDP_PITCH_EVT, *(s32 *) &pitch3);
                        if (numCameras != 1) {
                            pan = 64;
                        }
                        sndp_set_param(line->soundHandle, AL_SNDP_PAN_EVT, pan);
                        sndp_set_priority(line->soundHandle, line->priority);
                    }
                } else {
                    if (line->soundHandle != NULL) {
                        sndp_stop(line->soundHandle);
                    }
                }
            } else if (line->type == AUDIO_LINE_TYPE_JINGLE && volume > jingleVolume) {
                jingleVolume = volume;
                jinglePan = pan;
                jingleSound = line->soundBite;
            }
        }
    }

    // Update jingle parameters
    if (jingleVolume > MIN_VOLUME_THRESHOLD && !gJinglesOff) {
        if (music_jingle_current() != jingleSound) {
            music_jingle_play_safe(jingleSound);
        }
        music_jingle_volume_set(jingleVolume);
        music_jingle_pan_set(jinglePan);
    } else {
        music_jingle_stop();
    }

    // Update vehicle sounds
    if (numObjects != 0) {
        func_80006FC8(objList, numObjects, cameras, numCameras, updateRate);
    }
}

/**
 * Computes the pan value based on the camera's position and orientation relative to the sound source.
 * Official Name: amCalcSfxStereo
 */
s32 audspat_calculate_spatial_pan(f32 x, f32 z, s32 yaw) {
    s32 angle;
    s32 pan;
    f32 distance;

    distance = sqrtf((x * x) + (z * z));
    angle = 0xFFFF - arctan2_f(x, z);

    if (angle < yaw) {
        if (distance <= 1.0f) {
            pan = 64 - ((sins_s16(yaw - angle) / 1024) * (distance * 1));
        } else {
            pan = 64 - (sins_2(yaw - angle) / 1024);
        }
    } else {
        if (distance <= 1.0f) {
            pan = (sins_s16(angle - yaw) / 1024) * (distance * 1) + 64;
        } else {
            pan = (sins_2(angle - yaw) / 1024) + 64;
        }
    }

    if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
        pan = 128 - pan;
    }

    return pan;
}

/**
 * Computes the distance from a point to a line segment in 3D space,
 * and returns the coordinates of the closest point on the segment.
 */
s32 audspat_distance_to_segment(f32 inX, f32 inY, f32 inZ, f32 coords[6], f32 *outX, f32 *outY, f32 *outZ) {
    f32 dx, dy, dz;
    f32 x1, y1, z1;
    f32 x2, y2, z2;

    f32 projection;
    f32 distance;

    x1 = coords[0];
    y1 = coords[1];
    z1 = coords[2];
    x2 = coords[3];
    y2 = coords[4];
    z2 = coords[5];
    projection = 0.0f;

    dx = x2 - x1;
    dy = y2 - y1;
    dz = z2 - z1;

    if (dx == 0.0 && dy == 0.0 && dz == 0.0) {
        projection = 0.0f;
    } else {
        projection = ((inX - x1) * dx + (inY - y1) * dy + (inZ - z1) * dz) / (dx * dx + dy * dy + dz * dz);
    }

    if (projection < 0.0f) {
        // First vertex is the closest
        *outX = x1;
        *outY = y1;
        *outZ = z1;
        dx = x1 - inX;
        dy = y1 - inY;
        dz = z1 - inZ;
        distance = sqrtf(dx * dx + dy * dy + dz * dz);
    } else if (projection > 1.0f) {
        // Second vertex is the closest
        *outX = x2;
        *outY = y2;
        *outZ = z2;
        dx = x2 - inX;
        dy = y2 - inY;
        dz = z2 - inZ;
        distance = sqrtf(dx * dx + dy * dy + dz * dz);
    } else {
        // Closest point is between the two vertices
        // Calculate the point on the line
        *outX = projection * dx + x1, *outY = projection * dy + y1, *outZ = projection * dz + z1;
        distance = sqrtf((*outX - inX) * (*outX - inX) + (*outY - inY) * (*outY - inY) + (*outZ - inZ) * (*outZ - inZ));
    }

    return distance;
}

/**
 * Play Sound at position
 * Official Name: amSndPlayXYZ
 */
void audspat_play_sound_at_position(u16 soundId, f32 x, f32 y, f32 z, u8 flags, AudioPoint **handlePtr) {
    audspat_point_create(gSpatialSoundTable[soundId].soundBite, x, y, z, flags, gSpatialSoundTable[soundId].minVolume,
                         gSpatialSoundTable[soundId].volume, gSpatialSoundTable[soundId].range, FALSE,
                         gSpatialSoundTable[soundId].pitch, gSpatialSoundTable[soundId].priority, handlePtr);
}

/**
 * Uncertain of the exact purpose of this function, but it directly takes a sound ID
 * and bypasses the sound table.
 * Official Name: amSndPlayDirectXYZ
 */
void audspat_play_sound_direct(u16 soundBite, f32 x, f32 y, f32 z, u8 flags, u8 volume, f32 pitch,
                               AudioPoint **handlePtr) {
    audspat_point_create(soundBite, x, y, z, flags, /* minVolume */ 100, volume, /* range */ 15000, FALSE, pitch,
                         /* priority */ 63, handlePtr);
}

/**
 * Sets the position of an audio point.
 * Official Name: amSndSetXYZ
 */
void audspat_point_set_position(AudioPoint *audioPoint, f32 x, f32 y, f32 z) {
    audioPoint->pos.x = x;
    audioPoint->pos.y = y;
    audioPoint->pos.z = z;
}

/**
 * Official Name: amSndStopXYZ
 * Stops the sound associated with the audio point.
 */
void audspat_point_stop(AudioPoint *point) {
    s32 i;
    for (i = 0; i < MAX_AUDIO_POINTS; i++) {
        if (point == gAudioPoints[i]) {
            audspat_point_stop_by_index(i);
            break;
        }
    }
}

/**
 * Creates a point sound source and sets its parameters
 * Official Name: amCreateAudioPoint
 */
void audspat_point_create(u16 soundBite, f32 x, f32 y, f32 z, u8 flags, u8 minVolume, u8 volume, u16 range,
                          u8 fastFalloff, u8 pitch, u8 priority, AudioPoint **handlePtr) {
    AudioPoint *audioPoint;

    if (handlePtr != NULL) {
        func_800245B4(soundBite | 0xE000);
    }
    if (gNumAudioPoints == MAX_AUDIO_POINTS) {
        if (handlePtr != NULL) {
            *handlePtr = NULL;
        }
        func_800245B4(0xAA55);
        return;
    }
    audioPoint = gFreeAudioPoints[gLastFreePointIndex--];
    audioPoint->pos.x = x;
    audioPoint->pos.y = y;
    audioPoint->pos.z = z;
    audioPoint->soundBite = soundBite;
    audioPoint->flags = flags;
    audioPoint->minVolume = minVolume;
    audioPoint->volume = volume;
    audioPoint->pitch = pitch;
    audioPoint->range = range;
    audioPoint->fastFalloff = fastFalloff;
    audioPoint->priority = priority;
    audioPoint->triggeredOnce = 0;
    audioPoint->userHandlePtr = handlePtr;
    gAudioPoints[gNumAudioPoints++] = audioPoint;
    if (handlePtr != NULL) {
        *handlePtr = audioPoint;
    }
}

/**
 * Adds a vertex to the audio line.
 * An audio line is a sound source in the form of a polyline
 * The first vertex defines the sound ID and other properties.
 */
void audspat_line_add_vertex(u8 type, u16 soundBite, f32 x, f32 y, f32 z, u8 arg5, u8 arg6, u8 arg7, u8 priority,
                             u16 arg9, u8 argA, u8 lineID, u8 vertexIndex) {
    AudioLine *line;
    f32 *coords;

    if (lineID < MAX_AUDIO_LINES && vertexIndex < 30) {
        line = &gAudioLines[lineID];
        coords = &line->coords[vertexIndex * 3];
        coords[0] = x;
        coords[1] = y;
        coords[2] = z;
        if (vertexIndex == 0) {
            line->soundBite = soundBite;
            line->type = type;
            line->range = arg9;
            line->fastFalloff = argA;
            line->unk174 = arg6;
            line->maxVolume = arg5;
            line->unk176 = arg7;
            line->priority = priority;
        }
        if (line->numSegments < vertexIndex) {
            line->numSegments = vertexIndex;
        }
    }
}

/**
 * Adds a vertex to a reverb line.
 * Reverb lines are used to calculate echo effects in the game.
 * The first vertex defines the reverb intensity.
 */
void audspat_reverb_add_vertex(f32 x, f32 y, f32 z, u8 reverbAmount, u8 lineID, u8 vertexIndex) {
    ReverbLine *line;
    if (lineID < ARRAY_COUNT(gReverbLines) && vertexIndex < 15) {
        line = &gReverbLines[lineID];
        line->coords[3 * vertexIndex + 0] = x;
        line->coords[3 * vertexIndex + 1] = y;
        line->coords[3 * vertexIndex + 2] = z;
        if (vertexIndex == 0) {
            line->reverbAmount = reverbAmount;
        }
        if (line->numSegments < vertexIndex) {
            line->numSegments = vertexIndex;
        }
    }
}

/**
 * Checks that all vertex coordinates are defined.
 */
s32 audspat_line_validate(u8 lineID) {
    s32 ret;
    s32 i;
    AudioLine *line;
    f32 *coords;

    ret = TRUE;
    line = &gAudioLines[lineID];
    coords = line->coords;

    if (line->numSegments <= 0) {
        return FALSE;
    }

    for (i = 0; i < line->numSegments; i++) {
        //!@bug: should be *(coords + 0), *(coords + 1), *(coords + 2)
        if (*coords + 0 == -100000.0 || *coords + 1 == -100000.0 || *coords + 2 == -100000.0) {
            ret = FALSE;
        }
        coords += 3;
    }

    return ret;
}

/**
 * Checks that all vertex coordinates are defined.
 */
s32 audspat_reverb_validate(u8 reverbLineID) {
    s32 ret;
    s32 i;
    ReverbLine *line;
    f32 *coords;

    ret = TRUE;
    line = &gReverbLines[reverbLineID];
    coords = line->coords;

    if (line->numSegments <= 0) {
        return FALSE;
    }

    for (i = 0; i < line->numSegments; i++) {
        //!@bug: should be *(coords + 0), *(coords + 1), *(coords + 2)
        if (*coords == -100000.0 || *coords + 1 == -100000.0 || *coords + 2 == -100000.0) {
            ret = FALSE;
        }
        coords += 3;
    }

    return ret;
}

/**
 * Calculates and sets the reverb amount for a sound at the given position.
 * It checks all ReverbLine curves and finds the closest one to the specified point.
 * Reverberation is disabled if there is no surface above the point (i.e., the point is not inside a tunnel).
 */
void audspat_calculate_echo(SoundHandle soundHandle, f32 x, f32 y, f32 z) {
    s32 i;
    s32 j;
    ReverbLine *reverbLine;
    s32 k;
    f32 outX;
    f32 outY;
    f32 outZ;
    s32 distToSegment;
    s32 minDist;
    s32 levelSegmentIndex;
    s32 numOfYVals;
    u8 maxReverbAmt;
    u8 reverbAmt;
    f32 *coords;
    f32 yVals[10];

    levelSegmentIndex = get_level_segment_index_from_position(x, y, z);
    maxReverbAmt = 0;
    minDist = 400;

    for (i = 0; i < MAX_REVERB_LINES; i++) {
        reverbLine = &gReverbLines[i];
        if (reverbLine->reverbAmount != 0 && audspat_reverb_validate(i)) {
            coords = reverbLine->coords;
            for (j = 0; j < reverbLine->numSegments; j++) {
                distToSegment = audspat_distance_to_segment(x, y, z, coords, &outX, &outY, &outZ);
                // There seems to be a logic mistake here: the maximum reverb effect may not necessarily come from the
                // nearest segment. The closest segment could be near the beginning of the curve and not contribute much
                // to the echo. It would be better to iterate through all segments, but this approach would be slower.
                if (distToSegment < minDist) {
                    // Check if the point is below the ceiling (indicating it is inside a tunnel).
                    // This check should ideally be performed only once per call.
                    numOfYVals = func_8002BAB0(levelSegmentIndex, x, z, yVals);
                    for (k = 0; k < numOfYVals; k++) {
                        if (y < yVals[k]) {
                            minDist = distToSegment;
                            reverbAmt = audspat_reverb_get_strength_at_point(reverbLine, outX, outY, outZ);
                            if (maxReverbAmt < reverbAmt) {
                                maxReverbAmt = reverbAmt;
                            }
                        }
                    }
                }
                coords += 3;
            }
        }
    }

    if (soundHandle != NULL) {
        sndp_set_param(soundHandle, AL_SNDP_FX_EVT, maxReverbAmt);
    }
}

/**
 * Returns the reverb strength at a point along the line.
 * The strength is calculated based on the distance from the start or the end of the line.
 * Maximum strength is returned if the point is not within 300 units of the start or end.
 * The strength is linearly interpolated between 0 and the maximum reverb amount.
 */
u8 audspat_reverb_get_strength_at_point(ReverbLine *line, f32 x, f32 y, f32 z) {
    f32 deltaX;
    f32 deltaY;
    f32 deltaZ;
    f32 *coords;
    f32 x1, y1, z1;
    f32 x2, y2, z2;
    f32 dx, dy, dz;
    f32 i;
    f32 distanceAlong;
    f32 segmentLength;
    u8 segmentFound;
    f32 projection;

    if (line->totalLength == 0.0f) {
        coords = line->coords;
        for (i = 0.0f; i < line->numSegments; i += 1.0f) {
            deltaX = coords[3] - coords[0];
            deltaY = coords[4] - coords[1];
            deltaZ = coords[5] - coords[2];
            line->totalLength += sqrtf((deltaX * deltaX) + (deltaY * deltaY) + (deltaZ * deltaZ));
            coords += 3;
        }
    }

    coords = line->coords;
    distanceAlong = 0.0f;
    segmentFound = FALSE;

    for (; !segmentFound; coords += 3) {
        x1 = coords[0];
        y1 = coords[1];
        z1 = coords[2];
        x2 = coords[3];
        y2 = coords[4];
        z2 = coords[5];
        dx = x2 - x1;
        dy = y2 - y1;
        dz = z2 - z1;
        segmentLength = sqrtf((dx * dx) + (dy * dy) + (dz * dz));

        if ((x >= x1 && x <= x2) || (x >= x2 && x <= x1)) {
            if (dx != 0.0f) {
                projection = (x - x1) / dx;
            } else if (dy != 0.0f) {
                projection = (y - y1) / dy;
            } else if (dz != 0.0f) {
                projection = (z - z1) / dz;
            } else {
                projection = 0.0f;
            }

            if (ABS2(dy * projection + y1 - y) < 2.0f && ABS2(dz * projection + z1 - z) < 2.0f) {
                segmentFound = TRUE;
                distanceAlong += projection * segmentLength;
            } else {
                distanceAlong += segmentLength;
            }
        } else {
            distanceAlong += segmentLength;
        }
    }

    if (distanceAlong > line->totalLength / 2) {
        distanceAlong = line->totalLength - distanceAlong;
    }

    if (distanceAlong < 300.0f) {
        return line->reverbAmount * distanceAlong / 300.0f;
    } else {
        return line->reverbAmount;
    }
}

/**
 * Makes audio and reverb lines visible, useful for debugging.
 */
void audspat_debug_render_lines(Gfx **dList, Vertex **verts, Triangle **tris) {
    s32 i, j;
    f32 *coords;
    AudioLine *audioLine;
    ReverbLine *reverbLine;

    for (i = 0; i < ARRAY_COUNT(gAudioLines); i++) {
        audioLine = &gAudioLines[i];
        coords = audioLine->coords;
        if (gAudioLines[i].soundBite != 0) {
            for (j = 0; j < audioLine->numSegments; j++) {
                audspat_debug_render_line(dList, verts, tris, coords, 255, 255, 0);
                coords += 3;
            }
        }
    }

    for (i = 0; i < ARRAY_COUNT(gReverbLines); i++) {
        reverbLine = &gReverbLines[i];
        coords = reverbLine->coords;
        if (gReverbLines[i].reverbAmount != 0) {
            for (j = 0; j < reverbLine->numSegments; j++) {
                audspat_debug_render_line(dList, verts, tris, coords, 255, 0, 255);
                coords += 3;
            }
        }
    }
}

/**
 * Stops the sound associated with the given audio point.
 * If the sound is currently playing, it stops it and removes the audio point from the list.
 */
void audspat_point_stop_by_index(s32 index) {
    if (gNumAudioPoints != 0) {
        if (gAudioPoints[index]->soundHandle != NULL) {
            sndp_stop(gAudioPoints[index]->soundHandle);
        }
        if (gAudioPoints[index]->userHandlePtr != NULL) {
            *gAudioPoints[index]->userHandlePtr = NULL;
            func_800245B4(gAudioPoints[index]->soundBite | 0x5000);
        }

        // put it to the free list
        gLastFreePointIndex++;
        gFreeAudioPoints[gLastFreePointIndex] = gAudioPoints[index];
        // move the last element to the index of the one we are removing
        gAudioPoints[index] = gAudioPoints[gNumAudioPoints - 1];
        gNumAudioPoints--;
    }
}

/**
 * Generates and renders a coloured line visible from anywhere.
 * Allows use of a colour, that interpolates from bright to dark from the beginning to the end of the line.
 */
void audspat_debug_render_line(Gfx **dList, Vertex **verts, Triangle **tris, f32 coords[6], u8 red, u8 green, u8 blue) {
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
