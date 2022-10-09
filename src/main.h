#ifndef _MAIN_H_
#define _MAIN_H_

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

extern u8 gAssert;
extern char gAssertString[64];

void main(void);
void thread1_main(void *);
void thread3_verify_stack(void);

#endif
