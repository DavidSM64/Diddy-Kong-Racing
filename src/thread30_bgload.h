#ifndef _THREAD30_H_
#define _THREAD30_H_

#include "types.h"

void bgload_init(void);
void bgload_kill(void);
s32 bgload_active(void);
void bgload_tick(void);
s32 bgload_timer(void);
s32 bgload_start(s32 levelId, s32 cutsceneId);
void thread30_bgload(void *arg);

#endif
