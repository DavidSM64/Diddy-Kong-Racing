/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800d0da0 */

#include "config.h"
#ifdef ENABLE_USB

#include "dkr_usb.h"
#include "usb.h"

/*
	TODO:
		1.) Check for USB timeouts
		2.) Create functions for sending/recieving data to/from PC
		3.) Create a PC program to properly recieve data
*/

#define RETURN_IF_USB_NOT_VALID() if(usbState != 1) return
#define RETURN_IF_CART_NOT_VALID() if(cartType <= 0) return

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

void threadusb_loop(UNUSED void *arg);

void init_usb_thread(void) {
	
	usbState = usb_initialize();
	RETURN_IF_USB_NOT_VALID();
	cartType = usb_getcart();
	RETURN_IF_CART_NOT_VALID();
	
	// Create USB thread.
    osCreateMesgQueue(&gThreadUsbMesgQueue, &gThreadUsbMessage, 2);
    osCreateThread(&gThreadUsb, USB_THREAD_ID, &threadusb_loop, NULL, &gThreadUsbStack[THREADUSB_STACK / sizeof(u64)], THREADUSB_PRIORITY);
    osStartThread(&gThreadUsb);
}


void tick_usb_thread(void) {
	// Update USB thread
	osSendMesg(&gThreadUsbMesgQueue, (OSMesg *) OS_MESG_TYPE_LOOPBACK, OS_MESG_NOBLOCK);
}

int pollResult = -1;
char textBuffer[32];

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
		if(dataType != DATATYPE_TEXT || numBytesToRead > 32) {
			usb_skip(numBytesToRead);
			continue;
		}
		usb_read(textBuffer, numBytesToRead);
	}
	usb_purge(); // Not sure if this is needed?
}

void threadusb_loop(UNUSED void *arg) {
	OSMesg mesg = 0;
    while (TRUE) {
        // Wait for a tick signal from the main thread
        osRecvMesg(&gThreadUsbMesgQueue, &mesg, OS_MESG_BLOCK);
		
		// Do USB logic here
		dkr_usb_poll();
    }
}

void render_usb_info(void) {
	s32 i;
	s32 readData;
	
	set_render_printf_background_colour(0, 0, 0, 128);
	render_printf("Does USB work? %d\n", usbState);
	RETURN_IF_USB_NOT_VALID();
	render_printf("Cart type: %d\n", cartType);
	RETURN_IF_CART_NOT_VALID();
	
	// Show message sent from the computer.
	render_printf("%s\n", textBuffer);
	
}

#endif
