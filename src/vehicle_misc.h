#ifndef _VEHICLE_MISC_H_
#define _VEHICLE_MISC_H_

#include "types.h"
#include "structs.h"

#define BOSS_SOUND_POSITIVE 0
#define BOSS_SOUND_NEGATIVE 1

void update_tricky(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, u32 *buttonsPressed, s32 *startTimer);
void update_bluey(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, u32 *buttonsPressed, s32 *startTimer);
void update_bubbler(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, u32 *buttonsPressed, s32 *startTimer);
void update_smokey(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, s32 *stickMag, s32 *startTimer);
void update_wizpig(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, u32 *buttonsPressed, s32 *startTimer);
void update_rocket(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer, u32 *input, u32 *buttonsPressed, s32 *startTimer);
void spawn_boss_hazard(Object *obj, Object_Racer *racer, f32 offset, s32 objectID, s32 soundID);
void racer_special_init(Object *object, Object_Racer *racer);
void set_boss_voice_clip_offset(u16 *soundID);
void racer_boss_sound_spatial(f32 x, f32 y, f32 z, s32 offset);
void play_random_boss_sound(s32 offset);
void fade_when_near_camera(Object *object, Object_Racer *racer, s32 distance);
void racer_boss_finish(Object_Racer *racer, s8 *sceneTimer);

#endif
