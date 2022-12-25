#ifndef _VEHICLE_BLUEY_H_
#define _VEHICLE_BLUEY_H_

#include "types.h"
#include "structs.h"

extern u16 D_800DCE20[16];

void update_bluey(s32 updateRate, f32 updateRateF, Object* obj, Object_Racer* racer, u32* input, u32* buttonsPressed, s32* startTimer);

#endif
