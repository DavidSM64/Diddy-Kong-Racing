#pragma once

#include "types.hpp"

// 16 bytes
struct LevelObjectMapHeader {
  /* 0x00 */ be_uint32_t fileSize; // Total number of bytes of the file.
  /* 0x04 */ uint8_t pad4[12]; // Unused in DKR?
};

struct LevelObjectMap {
  /* 0x00 */ LevelObjectMapHeader header;
  /* 0x10 */ uint8_t entriesData[1]; // Bytes of the object entries. (It is dynamic, so can't be any more specific)
};
