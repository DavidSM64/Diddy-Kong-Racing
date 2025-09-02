#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
/**
 *  void osWritebackDCache(void* vaddr, s32 nbytes);
 *
 *  Writes back the contents of the data cache to main memory for `nbytes` at `vaddr`.
 *  If `nbytes` is as large as or larger than the data cache size, the entire cache is
 *  written back.
 */
LEAF(osWritebackDCache)
    /* If the amount to write back is less than or equal to 0, return immediately */
    blez    a1, 2f
    /*
     * If the amount to write back is as large as or larger than
     * the data cache size, write back all
     */
    li      t3, DCACHE_SIZE
    bgeu    a1, t3, 3f
    /*
     * ensure end address does not wrap around and end up smaller
     * than the start address
     */
    move    t0, a0
    addu    t1, a0, a1
    bgeu    t0, t1, 2f
    /* Mask and subtract to align to cache line */
    addiu   t1, t1, -DCACHE_LINESIZE
    andi    t2, t0, DCACHE_LINEMASK
    subu    t0, t0, t2
1:
    .set noreorder
    cache   (C_HWB | CACH_PD), (t0)
    bltu    t0, t1, 1b
     addiu  t0, t0, DCACHE_LINESIZE
    .set reorder
2:
    jr      ra

/* same as osWritebackDCacheAll in operation */
3:
    li      t0, K0BASE
    addu    t1, t0, t3
    addiu   t1, t1, -DCACHE_LINESIZE
4:
    .set noreorder
    cache   (C_IWBINV | CACH_PD), (t0)
    bltu    t0, t1, 4b
     addiu  t0, t0, DCACHE_LINESIZE
    .set reorder
    jr      ra
END(osWritebackDCache)
