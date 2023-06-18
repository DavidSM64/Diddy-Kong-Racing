#ifndef _DKRUSB_H_
#define _DKRUSB_H_

#include "types.h"
#include "printf.h"

void init_usb_thread(void);
void tick_usb_thread(void);
void render_usb_info(void);

#endif

