#ifndef _AUDIO_SPATIAL_H_
#define _AUDIO_SPATIAL_H_

#include "types.h"
#include "libc/math.h"
#include "structs.h"
#include "PR/gbi.h"
#include "PR/libaudio.h"
#include "camera.h"

#define AUDIO_LINE_TYPE_SOUND 0
#define AUDIO_LINE_TYPE_JINGLE 1

#define AUDIO_POINT_FLAG_1 1 // Unused
#define AUDIO_POINT_FLAG_SINGLE_PLAYER 2
#define AUDIO_POINT_FLAG_ONE_TIME_TRIGGER 4

/* Size: 0x24 / 36 bytes */
typedef struct AudioPoint {
  /* 0x00 */ Vec3f pos;
  /* 0x0C */ u16 soundBite;
  /* 0x0E */ u8 volume;
  /* 0x0F */ u8 pitch;
  /* 0x10 */ u8 minVolume;
  /* 0x11 */ u8 flags;
  /* 0x12 */ u8 inRange;
  /* 0x14 */ s32 range;
  /* 0x18 */ SoundHandle soundHandle;
  /* 0x1C */ struct AudioPoint **userHandlePtr;
  /* 0x20 */ u8 fastFalloff;
  /* 0x21 */ u8 priority;
  /* 0x22 */ u8 triggeredOnce;
} AudioPoint;

/* Size: 0x180 / 384 bytes */
typedef struct AudioLine {
    /* 0x000 */ u8 type; // 0 - sound, 1 - jingle
    /* 0x004 */ f32 coords[30 * 3];
    /* 0x16C */ s32 soundBite;
    /* 0x170 */ s32 range;
    /* 0x174 */ u8 unk174;
    /* 0x175 */ u8 maxVolume;
    /* 0x176 */ u8 unk176;
    /* 0x177 */ u8 unk177;
    /* 0x178 */ SoundHandle soundHandle;
    /* 0x17C */ s8 numSegments;
    /* 0x17D */ u8 fastFalloff;
    /* 0x17E */ u8 priority;
} AudioLine;

/* Size: 0xC0 / 192 bytes */
typedef struct ReverbLine {
  /* 0x00 */ u8 reverbAmount;
  /* 0x04 */ f32 coords[15 * 3];
  /* 0xB8 */ s8 numSegments;
  /* 0xBC */ f32 totalLength;
} ReverbLine;

void audspat_jingle_on(void);
void audspat_point_stop(AudioPoint *);
void audspat_jingle_off(void);
void audspat_point_create(u16 soundBite, f32 x, f32 y, f32 z, u8 flags, u8 minVolume, u8 volume, u16 range, u8 fastFalloff, u8 pitch,
                   u8 priority, AudioPoint **handlePtr);
void audspat_play_sound_at_position(u16 soundId, f32 x, f32 y, f32 z, u8 flags, AudioPoint **handlePtr);
void audspat_point_stop_by_index(s32 index);
s32 audspat_calculate_spatial_pan(f32, f32, s32);
void audspat_play_sound_direct(u16 soundBite, f32 x, f32 y, f32 z, u8 flags, u8 volume, f32 pitch, AudioPoint **handlePtr);
void audspat_line_add_vertex(u8 type, u16 soundBite, f32 x, f32 y, f32 z, u8 arg5, u8 arg6, u8 arg7, u8 priority, u16 arg9,
                              u8 argA, u8 lineID, u8 vertexIndex);
s32 audspat_line_validate(u8 lineID);
void audspat_debug_render_line(Gfx **dList, Vertex **verts, Triangle **tris, f32 coords[6], u8 red, u8 green, u8 blue);
void audspat_point_set_position(AudioPoint *audioPoint, f32 x, f32 y, f32 z);
s32 audspat_reverb_validate(u8 reverbLineID);
void audspat_init(void);
void audspat_reverb_add_vertex(f32, f32, f32, u8, u8, u8);
void audspat_calculate_echo(SoundHandle soundHandle, f32 x, f32 y, f32 z);

s32 audspat_distance_to_segment(f32 inX, f32 inY, f32 inZ, f32 coords[6], f32 *outX, f32 *outY, f32 *outZ);
void audspat_reset(void);
void audspat_update_all(Object **objList, s32 numObjects, s32 updateRate);
u8 audspat_reverb_get_strength_at_point(ReverbLine *, f32, f32, f32);

#endif
