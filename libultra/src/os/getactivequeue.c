#include "PR/os_internal.h"
#include "PRinternal/osint.h"

OSThread* __osGetActiveQueue(void) {
    return __osActiveQueue;
}
