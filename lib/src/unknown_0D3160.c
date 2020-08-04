/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2560 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3160/__osDisableInt.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3160/__osRestoreInt.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3160/D_800D25A0.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3160/D_800D2680.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3160/D_800D2760.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3160/__osViInit.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3160/func_800D2C60.s")

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