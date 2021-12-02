#ifndef _SIINT_H_
#define _SIINT_H_

#include "PR/os_internal.h"
#include "PR/rcp.h"

void __osSiGetAccess(void);
void __osSiRelAccess(void);
int __osSiDeviceBusy(void);
void __osSiCreateAccessQueue(void);
#endif
