/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CC5A0 */

#include "libultra_internal.h"
#include "viint.h"
#include "piint.h"

typedef struct
{
   /* 0x0 */ unsigned int inst1;
   /* 0x4 */ unsigned int inst2;
   /* 0x8 */ unsigned int inst3;
   /* 0xC */ unsigned int inst4;
} __osExceptionVector;
extern __osExceptionVector __osExceptionPreamble;

OSTime osClockRate = OS_CLOCK_RATE;
u32 __osShutdown = 0;
u32 __OSGlobalIntMask = OS_IM_ALL;
s32 gLeoFound = FALSE;
s32 __osLeoInterrupt(void);

extern s32 osViClock; //This is defined in another file somehow
extern u32 __osFinalrom; //This is defined in another file somehow
void osInitialize() {
   u32 pifdata;
   u32 clock = 0;
   u32 leostatus;
   u32 pistatus;
   __osFinalrom = TRUE;
   __osSetSR(__osGetSR() | SR_CU1);    //enable fpu
   __osSetFpcCsr(FPCSR_FS | FPCSR_EV); //flush denorm to zero, enable invalid operation

   while (__osSiRawReadIo(PIF_RAM_END - 3, &pifdata)) //last byte of joychannel ram
   {;}
   while (__osSiRawWriteIo(PIF_RAM_END - 3, pifdata | 8))
   {;} //todo: magic contant
   *(__osExceptionVector *)UT_VEC = __osExceptionPreamble;
   *(__osExceptionVector *)XUT_VEC = __osExceptionPreamble;
   *(__osExceptionVector *)ECC_VEC = __osExceptionPreamble;
   *(__osExceptionVector *)E_VEC = __osExceptionPreamble;
   osWritebackDCache((void *)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
   osInvalICache((void *)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
   osMapTLBRdb();
   osPiRawReadIo(4, &clock); //TODO: remove magic constant;
   clock &= ~0xf;            //clear lower 4 bits
   if (clock) {
      osClockRate = clock;
   }
   osClockRate = osClockRate * 3 / 4;
   if (osResetType == 0 /*cold reset */) {
      bzero(osAppNmiBuffer, sizeof(osAppNmiBuffer));
   }
   pistatus = IO_READ(PI_STATUS_REG);
   while (pistatus & PI_STATUS_ERROR) {
      pistatus = IO_READ(PI_STATUS_REG);
   };
   if (!((leostatus = IO_READ(LEO_STATUS)) & LEO_STATUS_PRESENCE_MASK)) {
      gLeoFound = TRUE;
      __osSetHWIntrRoutine(1, __osLeoInterrupt);
   } else {
      gLeoFound = FALSE;
   }
}
