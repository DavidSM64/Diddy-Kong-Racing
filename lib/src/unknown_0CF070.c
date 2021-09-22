/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CE470 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"
#include "PR/rcp.h"
#include "controller.h"
#include "siint.h"

extern OSPifRam __osEepPifRam;
s32 __osPackEepReadData(u8 address) {
    u8 *ptr;
    __OSContEepromFormat eepromformat;
    s32 i;

    ptr = (u8 *)&__osEepPifRam.ramarray;
    //@bug: i <= here, but in libreultra its i <
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
    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }
    *(__OSContEepromFormat *)ptr = eepromformat;
    ptr += sizeof(__OSContEepromFormat);
    ptr[0] = CONT_CMD_END;
}
