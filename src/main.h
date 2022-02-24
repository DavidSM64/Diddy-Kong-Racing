#ifndef _MAIN_H_
#define _MAIN_H_

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

void main(void);
void thread1_main(void *);
void thread3_verify_stack(void);

#endif
