#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "PR/os_version.h"
#include "PRinternal/piint.h"

/*
 * Values for osTvType 
 */
#define	OS_TV_PAL		0
#define	OS_TV_NTSC		1
#define	OS_TV_MPAL		2

/*
 * Size of buffer the retains contents after NMI
 */
#define OS_APP_NMI_BUFSIZE	64

typedef struct {
    /* 0x0 */ unsigned int inst1;
    /* 0x4 */ unsigned int inst2;
    /* 0x8 */ unsigned int inst3;
    /* 0xC */ unsigned int inst4;
} __osExceptionVector;
extern __osExceptionVector __osExceptionPreamble[];

extern OSPiHandle __Dom1SpeedParam;
extern OSPiHandle __Dom2SpeedParam;

OSTime osClockRate = OS_CLOCK_RATE;
extern s32 osViClock;
extern s32		__osLeoInterrupt(void);
#include "PR/os_internal_exception.h"
u32 __osShutdown = 0;
u32 __OSGlobalIntMask = OS_IM_ALL;
s32 gLeoFound = FALSE;
#ifdef _FINALROM
u32 __osFinalrom;
#else
u32 __kmc_pt_mode;
#if BUILD_VERSION >= VERSION_K
void* __printfunc = NULL;
#endif
#endif

#if BUILD_VERSION >= VERSION_K

#define INITIALIZE_FUNC __osInitialize_common
#define SPEED_PARAM_FUNC __createSpeedParam
#else

#define INITIALIZE_FUNC osInitialize
#define SPEED_PARAM_FUNC createSpeedParam
#if BUILD_VERSION >= VERSION_J
static void ptstart(void);
static void SPEED_PARAM_FUNC(void);
#endif
extern __osExceptionVector __ptExceptionPreamble[];

#endif

#if BUILD_VERSION >= VERSION_K
void SPEED_PARAM_FUNC(void) {
    __Dom1SpeedParam.type = DEVICE_TYPE_INIT;
    __Dom1SpeedParam.latency = IO_READ(PI_BSD_DOM1_LAT_REG);
    __Dom1SpeedParam.pulse = IO_READ(PI_BSD_DOM1_PWD_REG);
    __Dom1SpeedParam.pageSize = IO_READ(PI_BSD_DOM1_PGS_REG);
    __Dom1SpeedParam.relDuration = IO_READ(PI_BSD_DOM1_RLS_REG);

    __Dom2SpeedParam.type = DEVICE_TYPE_INIT;
    __Dom2SpeedParam.latency = IO_READ(PI_BSD_DOM2_LAT_REG);
    __Dom2SpeedParam.pulse = IO_READ(PI_BSD_DOM2_PWD_REG);
    __Dom2SpeedParam.pageSize = IO_READ(PI_BSD_DOM2_PGS_REG);
    __Dom2SpeedParam.relDuration = IO_READ(PI_BSD_DOM2_RLS_REG);
}
#endif

void INITIALIZE_FUNC() {
    u32 pifdata;
#if BUILD_VERSION < VERSION_K
    u32 clock = 0;
#endif
   u32 leostatus;
   u32 pistatus;

#ifdef _FINALROM
    __osFinalrom = TRUE;
#endif

    __osSetSR(__osGetSR() | SR_CU1);    // enable fpu
    __osSetFpcCsr(FPCSR_FS | FPCSR_EV | FPCSR_RM_RN); // flush denorm to zero, enable invalid operation
#if BUILD_VERSION >= VERSION_K
    __osSetWatchLo(0x4900000);
#endif

    while (__osSiRawReadIo(PIF_RAM_END - 3, &pifdata)) { // last byte of joychannel ram
        ;
    }
    while (__osSiRawWriteIo(PIF_RAM_END - 3, pifdata | 8)) {
        ; // todo: magic contant
    }
    *(__osExceptionVector*)UT_VEC = *__osExceptionPreamble;
    *(__osExceptionVector*)XUT_VEC = *__osExceptionPreamble;
    *(__osExceptionVector*)ECC_VEC = *__osExceptionPreamble;
    *(__osExceptionVector*)E_VEC = *__osExceptionPreamble;
    osWritebackDCache((void*)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
    osInvalICache((void*)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
#if BUILD_VERSION >= VERSION_J
    SPEED_PARAM_FUNC();
    osUnmapTLBAll();
    osMapTLBRdb();
#else
    osMapTLBRdb();
    osPiRawReadIo(4, &clock); // Read clock rate from the ROM header
    clock &= ~0xf;
    if (clock != 0)
    {
        osClockRate = clock;
    }
#endif
    osClockRate = osClockRate * 3 / 4;

    if (osResetType == 0) { // cold reset
        bzero(osAppNMIBuffer, OS_APP_NMI_BUFSIZE);
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

#if BUILD_VERSION >= VERSION_J
    // Wait until there are no RCP interrupts
    if (__osGetCause() & CAUSE_IP5) {
        while (TRUE) {
            ;
        }
    }

    IO_WRITE(AI_CONTROL_REG, AI_CONTROL_DMA_ON);
    IO_WRITE(AI_DACRATE_REG, AI_MAX_DAC_RATE - 1);
    IO_WRITE(AI_BITRATE_REG, AI_MAX_BIT_RATE - 1);
#endif

#if BUILD_VERSION < VERSION_K && !defined(_FINALROM)
    if (!__kmc_pt_mode) {
        int (*fnc)();
#if BUILD_VERSION < VERSION_J
        unsigned int c;
        unsigned int c1;
#endif
        unsigned int* src;
        unsigned int* dst;
        unsigned int monadr;
        volatile unsigned int* mon;
        volatile unsigned int* stat;

        stat = (unsigned*)0xbff08004;
        mon = (unsigned*)0xBFF00000;
        if (*mon != 0x4B4D4300) {
            return;
        }

        src = (unsigned*)__ptExceptionPreamble;
        dst = (unsigned*)E_VEC;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        src += 2;
        dst += 2;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;

        osWritebackDCache(E_VEC, 0x24);
        osInvalICache(E_VEC, 0x24);

        __kmc_pt_mode = TRUE;

        if ((*stat & 0x10) == 0) {
            monadr = *(mon + 1);
            if (monadr != 0xBFF00000) {
                unsigned int* src;
                unsigned int* dst = monadr | 0x20000000;
                unsigned int ct = 0x2000 / 4;

                src = 0xBFF00000;

                while (ct != 0) {
                    *dst++ = *src++;
                    ct--;
                }
            }
            fnc = monadr + 8;
            fnc(0x4B4D4300, 0);
        }
    }
#endif
}

#if !defined(_FINALROM) && BUILD_VERSION < VERSION_J
void ptstart(void) {

}
#elif !defined(_FINALROM) && BUILD_VERSION < VERSION_K
static void ptstart(void) {

}
#endif

#if BUILD_VERSION >= VERSION_K
void __osInitialize_autodetect(void) {
#ifndef _FINALROM
    if (__checkHardware_msp()) {
        __osInitialize_msp();
    } else if (__checkHardware_kmc()) {
        __osInitialize_kmc();
    } else if (__checkHardware_isv()) {
        __osInitialize_isv();
    } else {
        __osInitialize_emu();
    }
#endif
}
#elif BUILD_VERSION == VERSION_J
static void SPEED_PARAM_FUNC(void) {
    __Dom1SpeedParam.type = DEVICE_TYPE_INIT;
    __Dom1SpeedParam.latency = IO_READ(PI_BSD_DOM1_LAT_REG);
    __Dom1SpeedParam.pulse = IO_READ(PI_BSD_DOM1_PWD_REG);
    __Dom1SpeedParam.pageSize = IO_READ(PI_BSD_DOM1_PGS_REG);
    __Dom1SpeedParam.relDuration = IO_READ(PI_BSD_DOM1_RLS_REG);

    __Dom2SpeedParam.type = DEVICE_TYPE_INIT;
    __Dom2SpeedParam.latency = IO_READ(PI_BSD_DOM2_LAT_REG);
    __Dom2SpeedParam.pulse = IO_READ(PI_BSD_DOM2_PWD_REG);
    __Dom2SpeedParam.pageSize = IO_READ(PI_BSD_DOM2_PGS_REG);
    __Dom2SpeedParam.relDuration = IO_READ(PI_BSD_DOM2_RLS_REG);
}
#endif
