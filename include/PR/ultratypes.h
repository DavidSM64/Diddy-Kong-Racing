#ifndef _TYPES_H_
#define _TYPES_H_

#ifndef NULL
#define NULL 0
#endif

#define TRUE 1
#define FALSE 0

typedef signed char            s8;
typedef unsigned char          u8;
typedef signed short           s16;
typedef unsigned short         u16;
typedef long                   s32;
typedef unsigned long          u32;
typedef signed long long       s64;
typedef unsigned long long     u64;

typedef volatile u8   vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;
typedef volatile s8   vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;

typedef float  f32;
typedef double f64;

//#ifdef TARGET_N64
typedef u32 size_t;
typedef s32 ssize_t;
typedef u32 uintptr_t;
typedef s32 intptr_t;
typedef s32 ptrdiff_t;
//#else
//#include <stddef.h>
//#endif

typedef float Matrix[4][4];
typedef s16 VertexList;
typedef u8 TriangleList;

#endif
