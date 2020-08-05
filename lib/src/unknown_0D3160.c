/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2560 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"
#include "hardware.h"

GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3160/__osDisableInt.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3160/__osRestoreInt.s")

s32 osPiRawStartDma(s32 direction, u32 devAddr, void *dramAddr, u32 size)
{
    register int status;
    status = HW_REG(PI_STATUS_REG, u32);
    while (status & (PI_STATUS_BUSY | PI_STATUS_IOBUSY | PI_STATUS_ERROR)) {
        status = HW_REG(PI_STATUS_REG, u32);
    }

    HW_REG(PI_DRAM_ADDR_REG, void *) = (void *) osVirtualToPhysical(dramAddr);

    HW_REG(PI_CART_ADDR_REG, void *) = (void *) (((uintptr_t) osRomBase | devAddr) & 0x1fffffff);

    switch (direction) {
        case OS_READ:
            HW_REG(PI_WR_LEN_REG, u32) = size - 1;
            break;
        case OS_WRITE:
            HW_REG(PI_RD_LEN_REG, u32) = size - 1;
            break;
        default:
            return -1;
            break;
    }
    return 0;
}

GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3160/osEPiRawStartDma.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3160/__osDevMgrMain.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3160/__osViInit.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3160/alSynDelete.s")

void __osDequeueThread(OSThread **queue, OSThread *t)
{
   register OSThread *pred;
   register OSThread *succ;
   pred = (OSThread *)queue; //this is actually legit..
   succ = pred->next;
   while (succ != NULL)
   {
      if (succ == t)
      {
         pred->next = t->next;
         return;
      }
      pred = succ;
      succ = pred->next;
   }
}