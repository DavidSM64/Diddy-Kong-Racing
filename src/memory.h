#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "structs.h"
#include "types.h"
#include "macros.h"

#define RAM_END 0x80400000
#define MAIN_POOL_SLOT_COUNT 1600

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

/* Size: 0x8 bytes */
typedef struct unk80070BE4_8_0 {
    s16 unk0;
    s16 unk2;
    s32 unk4;
} unk80070BE4_8_0;
    
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
/* 0x10 */ u32 colorTag;
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
    u8 unk4; //FreeQueueState?
} FreeQueueSlot;

/* Unknown size */
typedef struct unk800B7D10 {
    u8 pad0[0x14];
    s32 unk14;
} unk800B7D10;

//Functions below don't have files or matches yet
unk800B7D10 *get_stack_pointer(void); // Non Matching with own file?
s32 *func_8006F510(void); // Non Matching unknown_070110
void func_8006F53C(s32*); // Non Matching unknown_070110

void init_main_memory_pool(void);
MemoryPoolSlot *new_sub_memory_pool(s32 poolDataSize, s32 numSlots);
void *allocate_from_main_pool_safe(s32 size, u32 colorTag);
MemoryPoolSlot *allocate_from_main_pool(s32 size, u32 colorTag);
void *allocate_from_pool_containing_slots(MemoryPoolSlot *slots, s32 size);
void set_free_queue_state(s32 state);
void free_from_memory_pool(void *data);
void clear_free_queue(void);
void func_80071440(void *dataAddress);
s32 func_80071478(u8 *address);
s32 func_80071538(u8 *address);
s32 get_memory_pool_index_containing_address(u8 *address);
u8 *align16(u8 *address);
u8 *align8(u8 *address);
u8 *align4(u8 *address);
void print_memory_color_tags(void);
void render_memory_color_tags(void);
void func_80071CE8(void);

MemoryPoolSlot *allocate_from_memory_pool(s32 memoryPoolIndex, s32 size, u32 colorTag); // Non Matching
MemoryPoolSlot *new_memory_pool(MemoryPoolSlot *slots, s32 poolSize, s32 numSlots); // Non Matching
void free_memory_pool_slot(s32 poolIndex, s32 slotIndex); // Non Matching
void *allocate_at_address_in_main_pool(s32 size, u8 *address, u32 colorTag); // Non Matching
void free_slot_containing_address(u8 *address); // Non Matching
s32 get_memory_color_tag_count(s32 arg0); // Non Matching

#endif
