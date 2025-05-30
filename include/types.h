#ifndef _TYPES_H_
#define _TYPES_H_

#include <PR/ultratypes.h>

typedef float MtxF[4][4];
typedef s32 MtxS[4][4];
typedef s16 VertexList;
typedef u8 TriangleList;
typedef u32 uintptr_t;

#if defined(__sgi)
#define stubbed_printf
#else
#define stubbed_printf(...)
#endif

#endif
