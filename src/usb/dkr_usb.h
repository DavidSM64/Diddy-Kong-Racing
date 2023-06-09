#ifndef _DKRUSB_H_
#define _DKRUSB_H_

#include "types.h"
#include "printf.h"

void init_usb_thread(void);
void tick_usb_thread(void);
void render_usb_info(void);

void usb_send_make_copy(u8 *data, s32 dataLength);
void usb_send_data(char *dataTag, u8 *data, s32 dataLength);
void usb_send_text(char *text);

#endif

