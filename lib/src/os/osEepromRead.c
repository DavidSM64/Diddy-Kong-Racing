/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CE280 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"
#include "PR/rcp.h"
#include "controller.h"
#include "siint.h"

extern u8 __osContLastCmd;
extern OSPifRam __osEepPifRam;
s32 osEepromRead(OSMesgQueue *mq, u8 address, u8 *buffer) {
    s32 ret;
    s32 i;
    u8 *ptr;
    OSContStatus sdata;
    __OSContEepromFormat eepromformat;

    ret = 0;
    i = 0;
    ptr = (u8 *)&__osEepPifRam.ramarray;

    if (address > 0x40) {
        return -1;
    }

    __osSiGetAccess();
    ret = __osEepStatus(mq, &sdata);

    if (ret != 0 || sdata.type != CONT_EEPROM) {
        return CONT_NO_RESPONSE_ERROR;
    }

    while (sdata.status & CONT_EEPROM_BUSY) {
        __osEepStatus(mq, &sdata);
    }

    __osPackEepReadData(address);
    ret = __osSiRawStartDma(OS_WRITE, &__osEepPifRam.ramarray);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    for (i = 0; i <= ARRLEN(__osEepPifRam.ramarray); i++) {
        __osEepPifRam.ramarray[i] = CONT_CMD_NOP;
    }

    __osEepPifRam.pifstatus = 0;

    ret = __osSiRawStartDma(OS_READ, __osEepPifRam.ramarray);

    __osContLastCmd = CONT_CMD_READ_EEPROM;
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    //skip the first 4 bytes
    for (i = 0; i < 4; i++) {
        ptr++;
    }

    eepromformat = *(__OSContEepromFormat *) ptr;
    ret = CHNL_ERR(eepromformat);

    if (ret == 0) {
        for (i = 0; i < ARRLEN(eepromformat.data); i++) {
            *buffer++ = eepromformat.data[i];
        }
    }

    __osSiRelAccess();

    return ret;
}
