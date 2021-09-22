/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CE280 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"
#include "PR/rcp.h"
#include "controller.h"
#include "siint.h"

typedef struct {
    u16 unk00;
    u8 unk02;
    u8 unk03;
} unkStruct;
typedef struct {
    u8 unk00;
    u8 unk01;
    u8 unk02;
    u8 unk03;
    u8 unk04;
    u8 unk05;
    u8 unk06;
    u8 unk07;
} unkStruct3;

typedef struct {
    u8 unk00;
    u8 unk01;
    u8 unk02;
    u8 unk03;
    unkStruct3 unk04;
} unkStruct2;
extern u8 __osContLastCmd;
extern OSPifRam __osEepPifRam;
s32 osEepromRead(OSMesgQueue *mq, u8 address, u8 *buffer) {
    s32 ret;
    s32 i;
    u8 *sp2c;
    unkStruct sp28;
    unkStruct2 sp20;
    ret = 0;
    i = 0;
    sp2c = (u8 *) &__osEepPifRam.ramarray;
    if (address > 0x40) {
        return -1;
    }
    __osSiGetAccess();
    ret = __osEepStatus(mq, &sp28);
    if (ret != 0 || sp28.unk00 != 0x8000) {

        return 8;
    }
    while (sp28.unk02 & 0x80) {
        __osEepStatus(mq, &sp28);
    }
    __osPackEepReadData(address);
    ret = __osSiRawStartDma(OS_WRITE, &__osEepPifRam.ramarray);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    for (i = 0; i < 0x10; i++) {
        __osEepPifRam.ramarray[i] = 255;
    }
    __osEepPifRam.pifstatus = 0;
    ret = __osSiRawStartDma(OS_READ, __osEepPifRam.ramarray);
    __osContLastCmd = 4;
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    for (i = 0; i < 4; i++) {
        sp2c++;
    }
    sp20 = *(unkStruct2 *) sp2c;
    ret = (sp20.unk01 & 0xc0) >> 4;
    if (ret == 0) {
        for (i = 0; i < 8; i++) {
            *buffer++ = ((u8 *) &sp20.unk04)[i];
        }
    }
    __osSiRelAccess();
    return ret;
}
