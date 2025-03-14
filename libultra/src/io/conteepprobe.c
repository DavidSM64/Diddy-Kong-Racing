#include "PRinternal/controller.h"
#include "PRinternal/siint.h"

s32 osEepromProbe(OSMesgQueue* mq) {
    s32 ret = 0;
    OSContStatus sdata;

    __osSiGetAccess();
    ret = __osEepStatus(mq, &sdata);
    if (ret == 0 && (sdata.type & CONT_EEPROM) != 0) {
        ret = EEPROM_TYPE_4K;
    } else {
        ret = 0;
    }

#if BUILD_VERSION >= VERSION_L
    __osEepromRead16K = 0;
#endif
    __osSiRelAccess();
    return ret;
}
