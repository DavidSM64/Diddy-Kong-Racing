#pragma once

#include "types.hpp"

/* Size: 10 bytes */
struct DkrVertex {
/* 0x00 */ be_int16_t x;
/* 0x02 */ be_int16_t y;
/* 0x04 */ be_int16_t z;
/* 0x06 */ uint8_t r;
/* 0x07 */ uint8_t g;
/* 0x08 */ uint8_t b;
/* 0x09 */ uint8_t a;
};