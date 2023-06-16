#ifndef __CARTINT_H__
#define __CARTINT_H__

#include "types.h"

typedef u32 uint32_t;

extern u32 __cart_rd(u32 addr);
extern void __cart_wr(u32 addr, u32 data);

#define CART_ABORT()            {__cart_acs_rel(); return -1;}

extern void __cart_acs_get(void);
extern void __cart_acs_rel(void);
extern void __cart_dma_rd(void *dram, u32 cart, u32 size);
extern void __cart_dma_wr(const void *dram, u32 cart, u32 size);
extern void __cart_buf_rd(const void *addr);
extern void __cart_buf_wr(void *addr);
extern u64 __cart_buf[512/8];

#endif /* __CARTINT_H__ */
