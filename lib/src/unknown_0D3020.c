/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2480 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

#define PI_Q_BUF_LEN 1
extern u32 __osPiAccessQueueEnabled;//__osPiAccessQueueEnabled
extern OSMesg piAccessBuf[PI_Q_BUF_LEN];//piAccessBuf
extern OSMesgQueue piAccessQueue; //__osPiAccessQueue
void __osPiCreateAccessQueue(void) {
    __osPiAccessQueueEnabled = 1;
    osCreateMesgQueue(&piAccessQueue, piAccessBuf, PI_Q_BUF_LEN);
    osSendMesg(&piAccessQueue, NULL, OS_MESG_NOBLOCK);
}

void __osPiGetAccess(void) {
    OSMesg dummyMesg;
    if (!__osPiAccessQueueEnabled)
        __osPiCreateAccessQueue();
    osRecvMesg(&piAccessQueue, &dummyMesg, OS_MESG_BLOCK);
}

void __osPiRelAccess(void) {
    osSendMesg(&piAccessQueue, NULL, OS_MESG_NOBLOCK);
}

/**********************************************************************/

// Please move these later!

// Used with cosf

const int D_800E97C0[5][2] = {
    { 0x3FF00000, 0x00000000 },
    { 0xBFC55554, 0xBC83656D },
    { 0x3F8110ED, 0x3804C2A0 },
    { 0xBF29F6FF, 0xEEA56814 },
    { 0x3EC5DBDF, 0x0E314BFE }
};

const int D_800E97E8[2] = {
    0x3FD45F30, 0x6DC9C883
};
const int D_800E97F0[2] = {
    0x400921FB, 0x50000000
};
const int D_800E97F8[2] = {
    0x3E6110B4, 0x611A6263
};
const int D_800E9800[1] = {
    0x00000000
};

const int COSF_FILE_PADDING[3] = { 0 };

// Used with sinf

const int D_800E9810[5][2] = {
    { 0x3FF00000, 0x00000000 },
    { 0xBFC55554, 0xBC83656D },
    { 0x3F8110ED, 0x3804C2A0 },
    { 0xBF29F6FF, 0xEEA56814 },
    { 0x3EC5DBDF, 0x0E314BFE }
};

const int D_800E9838[2] = {
    0x3FD45F30, 0x6DC9C883
};

const int D_800E9840[2] = {
    0x400921FB, 0x50000000
};

const int D_800E9848[2] = {
    0x3E6110B4, 0x611A6263
};

const int D_800E9850[1] = {
    0x00000000
};

const int SINF_FILE_PADDING[3] = { 0 };

// Used with _Litob

char D_800E4920[20] = "0123456789abcdef"; // lowercase hex digits
char D_800E4934[20] = "0123456789ABCDEF"; // uppercase hex digits

// Powers
const double D_800E9860[] = { 
    10e0L, 10e1L, 10e3L, 10e7L, 
    10e15L, 10e31L, 10e63L, 10e127L, 
    10e255L 
};

const char D_800E98A8[] = "NaN";
const char D_800E98AC[] = "Inf";

const int D_800E98B0[2] = {
    0x30000000, 0x00000000
};

const int D_800E98B8[2] = {
    0x4197D784, 0x00000000
};

const int D_800E98C0[2] = {
    0x7F810000, 0x00000000
};
