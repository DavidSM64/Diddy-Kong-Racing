#ifndef _SCREEN_ASSET_H_
#define _SCREEN_ASSET_H_

#include "video.h"
#include "memory.h"
#include "types.h"
#include "macros.h"
#include "f3ddkr.h"
#include "asset_enums.h"
#include "asset_loading.h"

#define SCREEN_HEIGHT_PART 6

UNUSED void *load_screen(s32 screenIndex);
UNUSED void render_screen(Gfx **dlist, u8 *screenAddress);

#endif
