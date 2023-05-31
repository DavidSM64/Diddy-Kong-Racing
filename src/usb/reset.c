/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800d0dc0 */

#include "macros.h"
#include "reset.h"
#include "PR/os_internal.h"
#include "libc/string.h" // for memcpy
#include "types.h"
#include "memory.h" // for RAM_END
#include "PR/rcp.h"
#include "PR/os_cache.h"

// TODO: Why don't these import?
#define IO_WRITE(addr,data) (*(vu32 *)PHYS_TO_K1(addr)=(u32)(data))
#define WAIT_ON_IOBUSY(stat)                                \
    stat = IO_READ(PI_STATUS_REG);                          \
    while (stat & (PI_STATUS_IO_BUSY | PI_STATUS_DMA_BUSY)) \
        stat = IO_READ(PI_STATUS_REG);

void entrypoint(void);

int __osDpDeviceBusy();
int __osSpDeviceBusy();
int __osSiDeviceBusy();

// defined in reset_util.s
void reboot_disable_interrupts(void); 

GLOBAL_ASM("src/usb/reset_util.s")

#define SIZEOF_osInvalICache 0x80
#define SIZEOF_osInvalDCache 0xB0

void (*osInvalICacheCopy)(void *, size_t);
void (*osInvalDCacheCopy)(void *, size_t);

// Will be copied to end of RAM, since the first 1MB will be overwritten.
void reset_start() {
    register u32 stat;
    
    // DMA game code from ROM to RAM.
    WAIT_ON_IOBUSY(stat);
    IO_WRITE(PI_DRAM_ADDR_REG, K0_TO_PHYS((void*)entrypoint));
    IO_WRITE(PI_CART_ADDR_REG, K1_TO_PHYS((u32)0xB0001000));
    IO_WRITE(PI_WR_LEN_REG, 0x100000 - 1);

    // Wait for DMA to finish
    while (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY | PI_STATUS_ERROR)){}
    
    // Invalidate all cache
    (*osInvalICacheCopy)(0x80000400, 0x4000);
    (*osInvalDCacheCopy)(0x80000400, 0x2000);
    
    // Jump to the game's entrypoint.
    entrypoint();
}
// Not a real function! Used for calculating size of reset_start()
void reset_start_end() {}

// Not defined in DKR, so define it here.
int __osPiDeviceBusy() {
    register u32 stat = IO_READ(PI_STATUS_REG);
    if (stat & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY))
        return 1;
    return 0;
}

void reset(void) {
    s32 resetFuncSize;
    void (*resetFunc)();
    
    // Wait for rsp to finish
    while (__osSpDeviceBusy() == 1) {}

    // Wait for rdp to finish
    while ( __osDpDeviceBusy() == 1) {}

    // Wait for SI to finish
    while (__osSiDeviceBusy() == 1) {}

    // Wait for PI to finish
    while (__osPiDeviceBusy() == 1) {}
    
    // Disable interrupts.
    reboot_disable_interrupts();
    
    resetFuncSize = (s32)((u8*)&reset_start_end - (u8*)&reset_start);
    resetFunc = (u8*)RAM_END - resetFuncSize;
    
    // Need to copy the invalidate cache functions to the end of RAM too.
    osInvalICacheCopy = (u8*)resetFunc - SIZEOF_osInvalICache;
    osInvalDCacheCopy = (u8*)osInvalICacheCopy - SIZEOF_osInvalDCache;
    
    memcpy(resetFunc, reset_start, resetFuncSize);
    memcpy(osInvalICacheCopy, osInvalICache, SIZEOF_osInvalICache);
    memcpy(osInvalDCacheCopy, osInvalDCache, SIZEOF_osInvalDCache);
    
    // Invalidate all of ICache and writeback all the dcache back into RDRAM.
    osInvalICache(0x80000400, 0x4000);
    osWritebackDCacheAll();

    (*resetFunc)(); // This executes the actual reset code at the end of ram.
}
