#pragma once

#include "types.hpp"

// In DKR, each entry is a big-endian halfword.
#define LOTT_ENTRY be_int16_t

const size_t LOTT_SIZE = 512; // In DKR, there are 512 available slots.
