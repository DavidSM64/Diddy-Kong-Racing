/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800d0da0 */

#include "config.h"
#include "main.h"
#ifdef ENABLE_USB

#include "dkr_usb.h"
#include "usb.h"

/*
    TODO:
        * Check for USB timeouts
        * Create functions for sending/recieving data to/from PC
*/

#define RETURN_IF_USB_NOT_VALID() if(usbState != 1) return
#define RETURN_IF_CART_NOT_VALID() if(cartType <= 0) return

// Funny number
#define USB_THREAD_ID 69

// Copied from UNFLoader debug.h
#define THREADUSB_PRIORITY 126

#define THREADUSB_STACK 0x200

// Copied from Thread30
OSThread gThreadUsb;
OSMesgQueue gThreadUsbMesgQueue;
OSMesg gThreadUsbMessage;
u64 gThreadUsbStack[THREADUSB_STACK / sizeof(u64)];

int usbState = -1;
int cartType = -1;
char textBuffer[64];
u8 usbBuffer[512]; // UNFLoader only supports reads/writes of up to 512 bytes.

#ifdef USB_HOT_RELOAD
    s32 isHotReloading = FALSE;
#endif

void threadusb_loop(UNUSED void *arg);

void init_usb_thread(void) {
    usbState = usb_initialize();
    RETURN_IF_USB_NOT_VALID();
    cartType = usb_getcart();
    RETURN_IF_CART_NOT_VALID();

#ifdef USB_HOT_RELOAD
    isHotReloading = FALSE;
#endif
    
    // Create USB thread.
    osCreateMesgQueue(&gThreadUsbMesgQueue, &gThreadUsbMessage, 2);
    osCreateThread(&gThreadUsb, USB_THREAD_ID, &threadusb_loop, NULL, &gThreadUsbStack[THREADUSB_STACK / sizeof(u64)], THREADUSB_PRIORITY);
    osStartThread(&gThreadUsb);
}

// Called from main thread.
void tick_usb_thread(void) {
    // Update USB thread
    osSendMesg(&gThreadUsbMesgQueue, (OSMesg *) OS_MESG_TYPE_LOOPBACK, OS_MESG_NOBLOCK);
}

void dkr_usb_poll(void) {
    int result;
    
    RETURN_IF_USB_NOT_VALID();
    RETURN_IF_CART_NOT_VALID();
    while(usb_poll()) {
        int header, dataType, numBytesToRead;
        header = usb_poll();
        dataType = USBHEADER_GETTYPE(header);
        numBytesToRead = USBHEADER_GETSIZE(header);
        // Read text data sent from computer. Note: Data sent from computer must be 4-byte aligned!
        if(numBytesToRead > 32) {
            usb_skip(numBytesToRead);
            continue;
        }
        usb_read(textBuffer, numBytesToRead);
    }
    usb_purge(); // Not sure if this is needed?
}

#ifdef USB_HOT_RELOAD
#include "usb/reset.h"

int numBytesReadHR = 0;

void check_hot_reload(void) {
    s32 header;
    s32 numBytesToRead;
    
    // Check if the message is "hot", if it is then start the hot reloading process!
    if(!isHotReloading) {
        if(textBuffer[0] != 'h' || textBuffer[1] != 'o' || textBuffer[2] != 't' || textBuffer[3] != 0) {
            return;
        }
        
        // This is here to make it so that the USB data ends up at the start of the ROM file.
        usb_set_debug_address(0);
        
        // Send message to PC that it should send the 1MB of ROM.
        usb_write(DATATYPE_TEXT, "SEND_HOTRELOAD\n", 16);
        
        numBytesReadHR = 0;
        isHotReloading = 1;
        return;
    }
    
    while(usb_poll()) {
        header = usb_poll();
        numBytesToRead = USBHEADER_GETSIZE(header);
        if(numBytesToRead > 0) {
            if(numBytesToRead > 512) {
                numBytesToRead = 512;
            }
            
            // Note: I don't do anything with the usbBuffer, the data is already at the start of the ROM.
            usb_read(usbBuffer, numBytesToRead);
            numBytesReadHR += numBytesToRead;
        }
    
        // Finished sending over 1MB of data.
        if((numBytesReadHR > 0) && (USBHEADER_GETSIZE(usb_poll()) < 1)) {
            usb_restore_debug_address(); // Move the debug address back to the end of ROM.
            usb_write(DATATYPE_TEXT, "HOTRELOAD_DONE\n", 16); // Tell the computer that we are done.
            reset(); // Reset the game.
        }
    }
}
#endif

void threadusb_loop(UNUSED void *arg) {
    OSMesg mesg = 0;
    while (TRUE) {
        // Wait for a tick signal from the main thread
        osRecvMesg(&gThreadUsbMesgQueue, &mesg, OS_MESG_BLOCK);
        
        // Do USB logic here  
#ifdef USB_HOT_RELOAD
        if(!isHotReloading) {
            dkr_usb_poll();  
        }
        check_hot_reload();
#else
        dkr_usb_poll();  
#endif
    }
}

// Called from main thread.
void render_usb_info(void) {
    s32 i;
    s32 readData;
    
    set_render_printf_background_colour(0, 0, 0, 128);
    render_printf("Does USB work? %d\n", usbState);
    RETURN_IF_USB_NOT_VALID();
    render_printf("Cart type: %d\n", cartType);
    RETURN_IF_CART_NOT_VALID();
    
#ifdef USB_HOT_RELOAD
    if(isHotReloading) {
        render_printf("HOT RELOADING!\n");
    }
#endif
    
    // Show message sent from the computer.
    render_printf("%s\n", textBuffer);
}

#endif
