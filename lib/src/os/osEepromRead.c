/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CE280 */

#include "libultra_internal.h"
#include "PR/rcp.h"
#include "controller.h"
#include "siint.h"

extern u8 __osContLastCmd;
extern OSPifRam __osEepPifRam;
s32 __osPackEepReadData(u8 address);
s32 __osEepStatus(OSMesgQueue *mq, OSContStatus *data);
s32 __osSiRawStartDma(s32, void *);

s32 osEepromRead(OSMesgQueue *mq, u8 address, u8 *buffer) {
    s32 ret;
    s32 i;
    u8 *ptr;
    OSContStatus sdata;
    __OSContEepromFormat eepromformat;

    ret = 0;
    i = 0;
    ptr = (u8 *)&__osEepPifRam.ramarray;

    if (address > EEPROM_MAXBLOCKS) {
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

    __osEepPifRam.pifstatus = CONT_CMD_REQUEST_STATUS;

    ret = __osSiRawStartDma(OS_READ, __osEepPifRam.ramarray);

    __osContLastCmd = CONT_CMD_READ_EEPROM;
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    //skip the first 4 bytes
    for (i = 0; i < MAXCONTROLLERS; i++) {
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

s32 __osPackEepReadData(u8 address) {
    u8 *ptr;
    __OSContEepromFormat eepromformat;
    s32 i;

    ptr = (u8 *)&__osEepPifRam.ramarray;
    //@bug? i <= here, but in libreultra its i <
    for (i = 0; i <= ARRLEN(__osEepPifRam.ramarray); i++) {
        __osEepPifRam.ramarray[i] = CONT_CMD_NOP;
    }
    __osEepPifRam.pifstatus = CONT_CMD_EXE;

    eepromformat.txsize = CONT_CMD_READ_EEPROM_TX;
    eepromformat.rxsize = CONT_CMD_READ_EEPROM_RX;
    eepromformat.cmd = CONT_CMD_READ_EEPROM;
    eepromformat.address = address;
    for (i = 0; i < ARRLEN(eepromformat.data); i++) {
        eepromformat.data[i] = 0;
    }
    //skip the first 4 bytes
    for (i = 0; i < MAXCONTROLLERS; i++) {
        *ptr++ = 0;
    }
    *(__OSContEepromFormat *)ptr = eepromformat;
    ptr += sizeof(__OSContEepromFormat);
    ptr[0] = CONT_CMD_END;
}
