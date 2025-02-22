#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "structs.h"
#include "types.h"
#include "macros.h"
#include "config.h"

typedef enum MemoryPools {
    POOL_MAIN,
    POOL_OBJECT,
    POOL_UNUSED_2,
    POOL_UNUSED_3,

    POOL_COUNT
} MemoryPools;

typedef enum MempoolFlags {
    SLOT_FREE = 0,              // The slot is free.
    SLOT_USED = (1 << 0),       // The slot is used.
    SLOT_LOCKED = (1 << 1),     // The slot is used, and cannot be freed by normal means.
    SLOT_SAFEGUARD = (1 << 2),  // The slot is used, and marks the stopping point of a global pool clear.
} MempoolFlags;

#define RAM_END 0x80400000
#define EXPANSION_RAM_END 0x80800000
#define MAIN_POOL_SLOT_COUNT 1600
#define FREE_QUEUE_SIZE 256
#define MEMSLOT_NONE -1

// Animation related?
#define COLOUR_TAG_RED 0xFF0000FF
// Model headers
#define COLOUR_TAG_GREEN 0x00FF00FF
// Objects
#define COLOUR_TAG_BLUE 0x0000FFFF
// Tracks
#define COLOUR_TAG_YELLOW 0xFFFF00FF
// Textures
#define COLOUR_TAG_MAGENTA 0xFF00FFFF
// Audio
#define COLOUR_TAG_CYAN 0x00FFFFFF
// Buffers and heaps
#define COLOUR_TAG_WHITE 0xFFFFFFFF
// Assets
#define COLOUR_TAG_GREY 0x7F7F7FFF
// Particles
#define COLOUR_TAG_SEMITRANS_GREY 0x80808080
// Model data
#define COLOUR_TAG_ORANGE 0xFF7F7FFF
// Controller Pak
#define COLOUR_TAG_BLACK 0x000000FF
// Weather
#define COLOUR_TAG_LIGHT_ORANGE 0xFFAA55FF
    
/* Size: 0x14 bytes */
typedef struct MemoryPoolSlot {
/* 0x00 */ u8 *data; 
/* 0x04 */ s32 size;
/* 0x08 */ s16 flags;
    // 0x00 = Slot is free 
    // 0x01 = Slot is being used?
    // 0x02 = ???
    // 0x04 = ???
/* 0x0A */ s16 prevIndex;
/* 0x0C */ s16 nextIndex;
/* 0x0E */ s16 index;
/* 0x10 */ u32 colourTag;
} MemoryPoolSlot;

/* Size: 0x10 bytes */
typedef struct MemoryPool {
/* 0x00 */ s32 maxNumSlots;
/* 0x04 */ s32 curNumSlots;
/* 0x08 */ MemoryPoolSlot *slots;
/* 0x0C */ s32 size;
} MemoryPool;

/* Size: 0x8 bytes */
typedef struct FreeQueueSlot {
    void *dataAddress;
    u8 freeTimer;
} FreeQueueSlot;

/* Unknown size */
typedef struct StackInfo {
    u32 var[5];
    u32 sp;
} StackInfo;

// This variable doesn't truly exist in memory.
// It's just defined as the end of BSS, and it's 
// symbol needs to be in the undefined syms place.
extern MemoryPoolSlot gMainMemoryPool;

void mempool_init_main(void);
MemoryPoolSlot *mempool_new_sub(s32 poolDataSize, s32 numSlots);
void *mempool_alloc_safe(s32 size, u32 colourTag);
MemoryPoolSlot *mempool_alloc(s32 size, u32 colourTag);
void *mempool_alloc_pool(MemoryPoolSlot *slots, s32 size);
void mempool_free_timer(s32 state);
void mempool_free(void *data);
void mempool_free_queue_clear(void);
void mempool_free_queue(void *dataAddress);
s32 mempool_locked_set(u8 *address);
s32 mempool_locked_unset(u8 *address);
s32 mempool_get_pool(u8 *address);
u8 *align16(u8 *address);
u8 *align8(u8 *address);
u8 *align4(u8 *address);
void mempool_print_tags_usb(void);
void mempool_print_tags_screen(void);
MemoryPoolSlot *mempool_init(MemoryPoolSlot *slots, s32 poolSize, s32 numSlots);
void mempool_slot_clear(MemoryPools poolIndex, s32 slotIndex);
s32 mempool_slot_assign(MemoryPools poolIndex, s32 slotIndex, s32 size, s32 slotIsTaken, s32 newSlotIsTaken,
                              u32 colourTag);
s32 get_memory_colour_tag_count(u32 colourTag);
void mempool_free_addr(u8 *address);
MemoryPoolSlot *mempool_slot_find(MemoryPools poolIndex, s32 size, u32 colourTag);
void *mempool_alloc_fixed(s32 size, u8 *address, u32 colorTag);

#endif
