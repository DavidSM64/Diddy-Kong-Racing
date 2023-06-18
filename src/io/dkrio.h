#ifndef _DKRIO_H_
#define _DKRIO_H_

#include "config.h"
#include "types.h"

#ifdef ENABLE_USB
#include "usb/dkr_usb.h"
#endif

#ifdef ENABLE_LIBCART
#include "sd/cart.h"
#include "sd/ff/ff.h"

extern FATFS gFatFs;
#endif

void init_io(void);
void update_io(s32 updateRate);
void debug_render_io(s32 updateRate);

#endif