/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CE210 */

#include "libultra_internal.h"
#include "siint.h"

s32 __osEepStatus(OSMesgQueue *mq, OSContStatus *data);

s32 osEepromProbe(OSMesgQueue *mq) {
    s32 ret = 0;
    OSContStatus sdata;

    __osSiGetAccess();
    ret = __osEepStatus(mq, &sdata);
    if (ret == 0 && (sdata.type & CONT_EEPROM) != 0) {
        ret = EEPROM_TYPE_4K;
    } else {
        ret = 0;
    }
    __osSiRelAccess();
    return ret;
}
