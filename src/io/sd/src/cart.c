/* RAM_POS: auto if (defined(ENABLE_IO) && defined(ENABLE_LIBCART)) */

#include "../cart.h"
#include "cartint.h"

extern void __osPiGetAccess(void);
extern void __osPiRelAccess(void);

/* Temporary buffer aligned for DMA */
#ifdef __GNUC__
__attribute__((aligned(16)))
#endif
u64 __cart_buf[512/8];

static u32 __cart_dom1_rel;
static u32 __cart_dom2_rel;
u32 cart_dom1;
u32 cart_dom2;

u32 cart_size;

void __cart_acs_get(void)
{
    __osPiGetAccess();
    /* Save PI BSD configuration and reconfigure */
    if (cart_dom1)
    {
        __cart_dom1_rel =
            IO_READ(PI_BSD_DOM1_LAT_REG) <<  0 |
            IO_READ(PI_BSD_DOM1_PWD_REG) <<  8 |
            IO_READ(PI_BSD_DOM1_PGS_REG) << 16 |
            IO_READ(PI_BSD_DOM1_RLS_REG) << 20 |
            1 << 31;
        IO_WRITE(PI_BSD_DOM1_LAT_REG, cart_dom1 >>  0);
        IO_WRITE(PI_BSD_DOM1_PWD_REG, cart_dom1 >>  8);
        IO_WRITE(PI_BSD_DOM1_PGS_REG, cart_dom1 >> 16);
        IO_WRITE(PI_BSD_DOM1_RLS_REG, cart_dom1 >> 20);
    }
    if (cart_dom2)
    {
        __cart_dom2_rel =
            IO_READ(PI_BSD_DOM2_LAT_REG) <<  0 |
            IO_READ(PI_BSD_DOM2_PWD_REG) <<  8 |
            IO_READ(PI_BSD_DOM2_PGS_REG) << 16 |
            IO_READ(PI_BSD_DOM2_RLS_REG) << 20 |
            1 << 31;
        IO_WRITE(PI_BSD_DOM2_LAT_REG, cart_dom2 >>  0);
        IO_WRITE(PI_BSD_DOM2_PWD_REG, cart_dom2 >>  8);
        IO_WRITE(PI_BSD_DOM2_PGS_REG, cart_dom2 >> 16);
        IO_WRITE(PI_BSD_DOM2_RLS_REG, cart_dom2 >> 20);
    }
}

void __cart_acs_rel(void)
{
    /* Restore PI BSD configuration */
    if (__cart_dom1_rel)
    {
        IO_WRITE(PI_BSD_DOM1_LAT_REG, __cart_dom1_rel >>  0);
        IO_WRITE(PI_BSD_DOM1_PWD_REG, __cart_dom1_rel >>  8);
        IO_WRITE(PI_BSD_DOM1_PGS_REG, __cart_dom1_rel >> 16);
        IO_WRITE(PI_BSD_DOM1_RLS_REG, __cart_dom1_rel >> 20);
        __cart_dom1_rel = 0;
    }
    if (__cart_dom2_rel)
    {
        IO_WRITE(PI_BSD_DOM2_LAT_REG, __cart_dom2_rel >>  0);
        IO_WRITE(PI_BSD_DOM2_PWD_REG, __cart_dom2_rel >>  8);
        IO_WRITE(PI_BSD_DOM2_PGS_REG, __cart_dom2_rel >> 16);
        IO_WRITE(PI_BSD_DOM2_RLS_REG, __cart_dom2_rel >> 20);
        __cart_dom2_rel = 0;
    }
    __osPiRelAccess();
}

u32 __cart_rd(u32 addr)
{
    while (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY|PI_STATUS_IO_BUSY));
    return IO_READ(addr);
}

void __cart_wr(u32 addr, u32 data)
{
    while (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY|PI_STATUS_IO_BUSY));
    IO_WRITE(addr, data);
}

typedef struct
{
    OSMesgQueue *messageQueue;
    OSMesg message;
}
__OSEventState;
extern __OSEventState __osEventStateTab[OS_NUM_EVENTS];

void __cart_dma_rd(void *dram, u32 cart, u32 size)
{
    osInvalDCache(dram, size);
    while (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY|PI_STATUS_IO_BUSY));
    IO_WRITE(PI_DRAM_ADDR_REG, osVirtualToPhysical(dram));
    IO_WRITE(PI_CART_ADDR_REG, cart);
    IO_WRITE(PI_WR_LEN_REG, size-1);
    osRecvMesg(
        __osEventStateTab[OS_EVENT_PI].messageQueue, NULL, OS_MESG_BLOCK
    );
}

void __cart_dma_wr(const void *dram, u32 cart, u32 size)
{
    osWritebackDCache((void *)dram, size);
    while (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY|PI_STATUS_IO_BUSY));
    IO_WRITE(PI_DRAM_ADDR_REG, osVirtualToPhysical((void *)dram));
    IO_WRITE(PI_CART_ADDR_REG, cart);
    IO_WRITE(PI_RD_LEN_REG, size-1);
    osRecvMesg(
        __osEventStateTab[OS_EVENT_PI].messageQueue, NULL, OS_MESG_BLOCK
    );
}
