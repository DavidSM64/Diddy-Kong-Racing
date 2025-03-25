#ifndef _ASSERT_H_
#define _ASSERT_H_

#include "types.h"
#include <ultra64.h>
#include "macros.h"

void __assert(const char* exp, const char* filename, int line);

#endif
