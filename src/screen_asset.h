#ifndef _SCREEN_ASSET_H_
#define _SCREEN_ASSET_H_

#include "video.h"
#include "memory.h"
#include "types.h"
#include "macros.h"
#include "f3ddkr.h"
#include "asset_sections.h"
#include "asset_loading.h"

#define SCREEN_HEIGHT_PART 6

u8 *load_screen(s32 screenIndex);
void render_screen(Gfx **dlist, u8 *screenAddress);

#endif
