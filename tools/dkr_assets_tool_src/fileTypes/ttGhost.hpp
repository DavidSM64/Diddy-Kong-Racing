#pragma once

#include "types.hpp"

#define GHOST_TIME_FPS 60.0

/* Size: 8 bytes */
typedef struct GhostHeader {
  /* 0x00 */ uint8_t levelId;
  /* 0x01 */ uint8_t vehicleId; // 0 = Car, 1 = Hovercraft, 2 = Plane
  /* 0x02 */ uint8_t characterId; // 9 = T.T.
  /* 0x03 */ uint8_t unk3; // Might just be padding?
  /* 0x04 */ be_int16_t time; // In frames, where 60 frames = 1 second.
  /* 0x06 */ be_int16_t nodeCount; // Maximum of 1080 nodes.
} GhostHeader;

/* Size: 12 bytes */
typedef struct GhostNode {
  /* 0x00 */ be_int16_t x;
  /* 0x02 */ be_int16_t y;
  /* 0x04 */ be_int16_t z;
  /* 0x06 */ be_int16_t zRotation; // This order is correct.
  /* 0x08 */ be_int16_t xRotation;
  /* 0x0A */ be_int16_t yRotation;
} GhostNode;
