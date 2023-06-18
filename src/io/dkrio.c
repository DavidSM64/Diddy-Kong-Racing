/* RAM_POS: auto if defined(ENABLE_IO) */

#include "dkrio.h"

#ifdef ENABLE_LIBCART
FATFS gFatFs;
#endif

void init_io(void) {
#ifdef ENABLE_USB
    init_usb_thread();
#endif
#ifdef ENABLE_LIBCART
    cart_init();
    f_mount(&gFatFs, "", 0);
#endif
}

void update_io(s32 updateRate) {
#ifdef ENABLE_USB
    tick_usb_thread();
#endif
}

void debug_render_io(s32 updateRate) {
#ifdef ENABLE_LIBCART
#ifdef SHOW_SD_INFO
    FILINFO finfo;
#endif
#endif
    
#ifdef ENABLE_USB
#ifdef SHOW_USB_INFO
    render_usb_info();
#endif
#endif

#ifdef ENABLE_LIBCART
#ifdef SHOW_SD_INFO
    render_printf("dkr.z64 exists? %d\n", f_stat("dkr.z64", &finfo) != FR_NO_FILE);
#endif
#endif
}

