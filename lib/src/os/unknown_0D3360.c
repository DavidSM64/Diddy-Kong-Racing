/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2760 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3160/__osDevMgrMain.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3160/__osViInit.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3160/alSynDelete.s")

void __osDequeueThread(OSThread **queue, OSThread *t) {
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
