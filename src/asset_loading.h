#ifndef _ASSET_LOADING_H_
#define _ASSET_LOADING_H_

#include "types.h"
#include "gzip.h"
#include "memory.h"

void init_PI_mesg_queue(void);
u32 *load_asset_section_from_rom(u32 assetIndex);
s32 load_asset_to_address(u32 assetIndex, u32 address, s32 assetOffset, s32 size);
u8 *get_rom_offset_of_asset(u32 assetIndex, u32 assetOffset);
s32 get_size_of_asset_section(u32 assetIndex);
void dmacopy(u32 romOffset, u32 ramAddress, s32 numBytes);

#endif
