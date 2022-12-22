#ifndef _THREAD30_H_
#define _THREAD30_H_

#include "types.h"

void create_and_start_thread30(void);
void stop_thread30(void);
s32 get_thread30_level_id_to_load(void);
void tick_thread30(void);
s32 get_thread30_load_delay(void);
s32 set_level_to_load_in_background(s32 levelId, s32 cutsceneId);
void thread30_track_loading(void *arg);

#endif
