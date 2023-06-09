/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800d0da0 */

#include "libc/string.h" // for memcpy
#include "dkr_usb.h"
#include "usb.h"

#include "../main.h"
#include "../memory.h"

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

typedef struct UsbSendEntry {
    u8 *data;
    s32 dataLength;
    u8 freeAfterSent;
    u8 dataType;
} UsbSendEntry;

// Make room for 2 entries
#define MAX_NUM_SEND_ENTRIES 100

s32 numberOfSendEntries = 0;
UsbSendEntry sendEntryQueue[MAX_NUM_SEND_ENTRIES]; 

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

// Called from main thread.
void tick_usb_thread(void) {
    // Update USB thread
    osSendMesg(&gThreadUsbMesgQueue, (OSMesg *) OS_MESG_TYPE_LOOPBACK, OS_MESG_NOBLOCK);
}

void dkr_usb_poll(void) {
    s32 result, i;
    
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
    
    // Send data to PC if any entries exist.
    if(numberOfSendEntries > 0) {
        for(i = 0; i < numberOfSendEntries; i++) {
            usb_write(sendEntryQueue[i].dataType, (const s8*)sendEntryQueue[i].data, sendEntryQueue[i].dataLength);
            if(sendEntryQueue[i].freeAfterSent) {
                free_from_memory_pool(sendEntryQueue[i].data);
            }
        }
        numberOfSendEntries = 0;
    }
}

char *get_level_name(s32);
size_t strlen(const char *str);

void threadusb_loop(UNUSED void *arg) {
    OSMesg mesg = 0;
    while (TRUE) {
        // Wait for a tick signal from the main thread
        osRecvMesg(&gThreadUsbMesgQueue, &mesg, OS_MESG_BLOCK);
        
        dkr_usb_poll();
    }
}

// Called from main thread.
void render_usb_info(void) {
}

void new_usb_send_entry(u8 *data, s32 dataLength, u8 freeAfterSent, u8 type) {
    if(numberOfSendEntries == MAX_NUM_SEND_ENTRIES) {
        return; // Have to discard this request, due to the queue being full.
    }
    sendEntryQueue[numberOfSendEntries].data = data;
    sendEntryQueue[numberOfSendEntries].dataLength = dataLength;
    sendEntryQueue[numberOfSendEntries].freeAfterSent = freeAfterSent;
    sendEntryQueue[numberOfSendEntries].dataType = type;
    numberOfSendEntries++;
}

// Called from main thread.
void usb_send_make_copy(u8 *data, s32 dataLength) {
    u8 *newData;
    if(numberOfSendEntries == MAX_NUM_SEND_ENTRIES) {
        return; // Have to discard this request, due to the queue being full.
    }
    newData = allocate_from_main_pool_safe(dataLength, COLOUR_TAG_WHITE);
    memcpy(newData, data, dataLength);
    new_usb_send_entry(newData, dataLength, TRUE, DATATYPE_RAWBINARY);
}

void usb_send_data(char *dataTag, u8 *data, s32 dataLength) {
    u8 *newData;
    if(numberOfSendEntries == MAX_NUM_SEND_ENTRIES) {
        return; // Have to discard this request, due to the queue being full.
    }
    newData = allocate_from_main_pool_safe(dataLength + 4, COLOUR_TAG_WHITE);
    memcpy(newData, dataTag, 4);
    memcpy(newData+4, data, dataLength);
    new_usb_send_entry(newData, dataLength + 4, TRUE, DATATYPE_RAWBINARY);
}


#ifndef ALIGN4
#define ALIGN4(val) ((val + 3) & ~0x03)
#endif

// Called from main thread.
void usb_send_text(char *text) {
    u8 *newData;
    s32 dataLength, textLength;
    if(numberOfSendEntries == MAX_NUM_SEND_ENTRIES) {
        return; // Have to discard this request, due to the queue being full.
    }
    textLength = strlen(text);
    dataLength = ALIGN4(textLength + 2); // One for newline, another for null terminator
    newData = allocate_from_main_pool_safe(dataLength, COLOUR_TAG_WHITE);
    memcpy(newData, text, dataLength);
    newData[textLength+0] = '\n';
    newData[textLength+1] = '\0';
    new_usb_send_entry(newData, dataLength, TRUE, DATATYPE_TEXT);
}
