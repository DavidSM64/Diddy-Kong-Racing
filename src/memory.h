#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "types.h"

// Animation related?
#define COLOR_TAG_RED 0xFF0000FF
// Object related?
#define COLOR_TAG_GREEN 0x00FF00FF
// ???
#define COLOR_TAG_BLUE 0x0000FFFF
// ???
#define COLOR_TAG_YELLOW 0xFFFF00FF
// ???
#define COLOR_TAG_MAGENTA 0xFF00FFFF
// Audio related?
#define COLOR_TAG_CYAN 0x00FFFFFF
// ???
#define COLOR_TAG_WHITE 0xFFFFFFFF
// ???
#define COLOR_TAG_GRAY 0x7F7F7FFF
// ???
#define COLOR_TAG_ORANGE 0xFF7F7FFF
// ???
#define COLOR_TAG_BLACK 0x000000FF

void *allocate_from_main_pool_safe(s32 size, u32 colorTag);
void free_from_memory_pool(void *data);
s32 func_80071478(u8 *address);

#endif
