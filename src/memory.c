/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80070B30 */

#include "memory.h"
#include "printf.h"
#include "thread0_epc.h"
#include "controller.h"
#include "video.h"
#include "main.h"

/************ .bss ************/

MemoryPool gMemoryPools[4];

#ifndef _ALIGN16
#define _ALIGN16(a) (((u32) (a) & ~0xF) + 0x10)
//#define _ALIGN16(val) ((val)&0xFFFFFFF0) + 0x10
#endif

s32 gNumberOfMemoryPools;
UNUSED s32 D_801235C4;
FreeQueueSlot gFreeQueue[256];
s32 gFreeQueueCount;
s32 gFreeQueueState;

extern MemoryPoolSlot gMainMemoryPool;

/******************************/

/**
 * Creates the main memory pool. 
 * Starts at 0x8012D3F0. Ends at 0x80400000. Contains 1600 allocation slots.
 */
void init_main_memory_pool(void) {
    u32 ramEnd = 0x80400000;
    if (gExpansionPak) {
        ramEnd = 0x80800000;
    }
#ifdef PUPPYPRINT_DEBUG
    bzero(&gFreeMem, sizeof(gFreeMem));
    gFreeMem[11] = ramEnd - (s32)(&gMainMemoryPool);
#endif
    gNumberOfMemoryPools = -1;
    // Create the main memory pool.
    new_memory_pool(&gMainMemoryPool, ramEnd - (s32)(&gMainMemoryPool), MAIN_POOL_SLOT_COUNT);
    set_free_queue_state(2);
    gFreeQueueCount = 0;
}

/**
 * Creates a new memory pool that is sectioned off the main one.
 * Official name: mmAllocRegion
 */
MemoryPoolSlot *new_sub_memory_pool(s32 poolDataSize, s32 numSlots) {
    s32 size;
    MemoryPoolSlot *slots;
    s32 *flags = clear_status_register_flags();
    MemoryPoolSlot *newPool;

    size = poolDataSize + (numSlots * sizeof(MemoryPoolSlot));
    slots = (MemoryPoolSlot *) allocate_from_main_pool_safe(size, COLOUR_TAG_WHITE);
    newPool = new_memory_pool(slots, size, numSlots);
    set_status_register_flags(flags);
    return newPool;
}

/**
 * Create and initialise a memory pool in RAM that will act as the place where arbitrary allocations can go.
 * Will return the location of the first free slot in that pool.
*/
MemoryPoolSlot *new_memory_pool(MemoryPoolSlot *slots, s32 poolSize, s32 numSlots) {
    MemoryPoolSlot *firstSlot;
    s32 poolCount;
    MemoryPool *pool;
    s32 i;
    
    poolCount = ++gNumberOfMemoryPools; \
    gMemoryPools[poolCount].maxNumSlots = numSlots;
    gMemoryPools[poolCount].curNumSlots = 0;
    gMemoryPools[poolCount].slots = slots;
    gMemoryPools[poolCount].size = poolSize;
    pool = &gMemoryPools[poolCount++];
    firstSlot = slots;
    for (i = 0; i < pool->maxNumSlots; i++) {
        firstSlot->index = i;
        firstSlot++;
    }
    firstSlot = &pool->slots[0];
    slots += numSlots;
    if ((s32) slots & 0xF) {
        firstSlot->data = (u8 *) _ALIGN16(slots);
    } else {
        firstSlot->data = (u8 *) slots;
    }
    firstSlot->size = poolSize - (numSlots * sizeof(MemoryPoolSlot));
    firstSlot->flags = 0;
    firstSlot->prevIndex = -1;
    firstSlot->nextIndex = -1;
    pool->curNumSlots++;
    return pool->slots;
}

/**
 * Reserves and returns memory from the main memory pool. Has 2 assert checks.
 * Will cause an exception if the size is 0 or if memory cannot be reserved.
 */
void *allocate_from_main_pool_safe(s32 size, u32 colourTag) {
    void *temp_v0;
    if (size == 0) {
        func_800B7460((s32 *)((u8 *)get_stack_pointer()->unk14), size, colourTag);
    }
    temp_v0 = allocate_from_memory_pool(0, size, colourTag);
    if (temp_v0 == (void *)NULL) {
        func_800B7460((s32 *)((u8 *)get_stack_pointer()->unk14), size, colourTag);
    }
    return temp_v0;
}

/**
 * Reserves and returns memory from the main memory pool. Has no assert checks.
 */
MemoryPoolSlot *allocate_from_main_pool(s32 size, u32 colourTag) {
    return allocate_from_memory_pool(0, size, colourTag);
}

MemoryPoolSlot *allocate_from_memory_pool(s32 poolIndex, s32 size, u32 colourTag) {
    s32 slotSize;
    MemoryPoolSlot *curSlot;
    MemoryPool *pool;
    MemoryPoolSlot *slots;
    s32 *flags;
    s32 nextIndex;
    s32 currIndex;
        
    flags = clear_status_register_flags();
    pool = &gMemoryPools[poolIndex];
    if ((pool->curNumSlots + 1) == (*pool).maxNumSlots) {
        set_status_register_flags(flags);
        return 0;
    }
    currIndex = -1;
    if (size & 0xF) {
        size = (size & ~0xF) + 0x10;
    }
    slots = pool->slots;
    slotSize = 0x7FFFFFFF;
    nextIndex = 0;
    do {
        curSlot = &slots[nextIndex];
        if (curSlot->flags == 0) {
            if ((curSlot->size >= size) && (curSlot->size < slotSize)) {
                slotSize = curSlot->size;
                currIndex = nextIndex;
            }
        }
        nextIndex = curSlot->nextIndex;
    } while (nextIndex != -1);
    if (currIndex != -1) {
        allocate_memory_pool_slot(poolIndex, (s32) currIndex, size, 1, 0, colourTag);
        set_status_register_flags(flags);
        return (MemoryPoolSlot *) (slots + currIndex)->data;
    }
    set_status_register_flags(flags);
    return 0;
}

/* Official name: mmAllocR */
void *allocate_from_pool_containing_slots(MemoryPoolSlot *slots, s32 size) {
    s32 i;
    for (i = gNumberOfMemoryPools; i != 0; i--) {
        if (slots == gMemoryPools[i].slots) {
            return allocate_from_memory_pool(i, size, 0);
        }
    }
    return (void *)NULL;
}

void *allocate_at_address_in_main_pool(s32 size, u8 *address, u32 colorTag) {
    s32 i;
    MemoryPoolSlot *curSlot;
    MemoryPoolSlot *slots;
    s32 *flags;
    
    flags = clear_status_register_flags();
    if ((gMemoryPools[0].curNumSlots + 1) == gMemoryPools[0].maxNumSlots) {
        set_status_register_flags(flags);
    } else {
    if (size & 0xF) {
        size = _ALIGN16(size);
    }
    slots = gMemoryPools[0].slots;
    for (i = 0; i != -1; i = curSlot->nextIndex) {
        curSlot = &slots[i];
        if (curSlot->flags == 0) {
            if ((u32) address >= (u32) curSlot->data && (u32)address + size <= (u32) curSlot->data + curSlot->size)  {
                if (address == (u8 *) curSlot->data) {
                    allocate_memory_pool_slot(0, i, size, 1, 0, colorTag);
                    set_status_register_flags(flags);
                    return curSlot->data;
                } else {
                    i = allocate_memory_pool_slot(0, i, (u32) address - (u32) curSlot->data, 0, 1, colorTag);
                    allocate_memory_pool_slot(0, i, size, 1, 0, colorTag);
                    set_status_register_flags(flags);
                    return (slots + i)->data;
                }
            }
        }
    }
    set_status_register_flags(flags);
    }
    return 0;
}

/**
 * Sets the state of the free queue. State is either 0, 1, or 2.
 * The free queue will get flushed if the state is set to 0.
 * Official name: mmSetDelay
 */
void set_free_queue_state(s32 state) {
    s32 *flags = clear_status_register_flags();
    gFreeQueueState = state;
    if (state == 0) { // flush free queue if state is 0.
        while (gFreeQueueCount > 0) {
            free_slot_containing_address(gFreeQueue[--gFreeQueueCount].dataAddress);
        }
    }
    set_status_register_flags(flags);
}

/**
 * Unallocates data from the pool that contains the data. Will free immediately if the free queue
 * state is set to 0, otherwise the data will just be marked for deletion.  
 */
void free_from_memory_pool(void *data) {
    s32 *flags = clear_status_register_flags();
    if (gFreeQueueState == 0) {
        free_slot_containing_address(data);
    } else {
        func_80071440(data);
    }
    set_status_register_flags(flags);
}

/**
 * Frees all the addresses in the free queue. 
 */
void clear_free_queue(void) {
    s32 i;
    s32 *flags;

    flags = clear_status_register_flags();

    for (i = 0; i < gFreeQueueCount;) {
        gFreeQueue[i].unk4--;
        if (gFreeQueue[i].unk4 == 0) {
            free_slot_containing_address(gFreeQueue[i].dataAddress);
            gFreeQueue[i].dataAddress = gFreeQueue[gFreeQueueCount - 1].dataAddress;
            gFreeQueue[i].unk4 = gFreeQueue[gFreeQueueCount - 1].unk4;
            gFreeQueueCount--;
        } else {
            i++;
        }
    }

    set_status_register_flags(flags);
}

/* Official name: heapFree */
void free_slot_containing_address(u8 *address) {
    s32 slotIndex;
    s32 poolIndex;
    MemoryPool *pool;
    MemoryPoolSlot *slots;
    MemoryPoolSlot *slot;
    
    poolIndex = get_memory_pool_index_containing_address(address);
    pool = gMemoryPools;
    slots = pool[poolIndex].slots;
    for (slotIndex = 0; slotIndex != -1; slotIndex = slot->nextIndex) {
        slot = &slots[slotIndex];
        
        if (address == (u8 *) slot->data) {
            if (slot->flags == 1 || slot->flags == 4) {
            free_memory_pool_slot(poolIndex, slotIndex);
            }
            break;
        }
        slot = &slots[slotIndex];
    }
}

void func_80071314(void) {
    MemoryPoolSlot *slotPos;
    MemoryPool *pool;
    s32 *flags;
    s32 poolIndex;
    s32 slotIndex;
        
    flags = clear_status_register_flags();
    poolIndex = gNumberOfMemoryPools;
    while (poolIndex != (-1)) {
        pool = &gMemoryPools[poolIndex];
        slotPos = pool->slots;
        slotIndex = 0;
        do {
            if ((slotPos + slotIndex)->flags == 1) {
                free_memory_pool_slot(poolIndex, slotIndex);
            }
            if ((slotPos + slotIndex)->flags == 4) {
                if (pool->curNumSlots == 1) {
                    free_memory_pool_slot(poolIndex, slotIndex);
                } else {
                    set_status_register_flags(flags);
                    return;
                }
            }
            slotIndex = (slotPos + slotIndex)->nextIndex;
        } while (slotIndex != (-1));
        poolIndex--;
    }
    set_status_register_flags(flags);
}

void func_80071440(void *dataAddress) {
    gFreeQueue[gFreeQueueCount].dataAddress = dataAddress;
    gFreeQueue[gFreeQueueCount].unk4 = gFreeQueueState;
    gFreeQueueCount++;
}

s32 func_80071478(u8 *address) {
    s32 slotIndex;
    MemoryPoolSlot *slot;
    MemoryPool *pool;
    s32 *flags;

    flags = clear_status_register_flags();
    pool = &gMemoryPools[get_memory_pool_index_containing_address(address)];
    slotIndex = 0;
    while (slotIndex != -1) {
        slot = slotIndex + pool->slots; // `slot = &pool->slots[slotIndex];` does not match.
        if (address == (u8 *)slot->data) {
            if (slot->flags == 1 || slot->flags == 4) {
                slot->flags |= 2;
                set_status_register_flags(flags);
                return 1;
            }
        }
        slotIndex = slot->nextIndex;
    }
    set_status_register_flags(flags);
    return 0;
}

s32 func_80071538(u8 *address) {
    s32 slotIndex;
    MemoryPoolSlot *slot;
    MemoryPool *pool;
    s32 *flags;

    flags = clear_status_register_flags();
    pool = &gMemoryPools[get_memory_pool_index_containing_address(address)];
    slotIndex = 0;
    while (slotIndex != -1) {
        slot = slotIndex + pool->slots; // `slot = &pool->slots[slotIndex];` does not match.
        if (address == (u8 *)slot->data) {
            if (slot->flags & 2) {
                slot->flags ^= 2;
                set_status_register_flags(flags);
                return 1;
            }
        }
        slotIndex = slot->nextIndex;
    }
    set_status_register_flags(flags);
    return 0;
}

/**
 * Returns the index of the memory pool containing the memory address.
 * Official(?) name: getHeapIdxOf
 */
s32 get_memory_pool_index_containing_address(u8 *address) {
    s32 i;
    MemoryPool *pool;

    for (i = gNumberOfMemoryPools; i > 0; i--) {
        pool = &gMemoryPools[i];
        if ((u8 *)pool->slots >= address) {
            continue;
        }
        if (address < pool->size + (u8 *)pool->slots) {
            break;
        }
    }
    return i;
}

#ifdef PUPPYPRINT_DEBUG
void adjust_mem_value(s32 size, u32 colourTag) {
    switch (colourTag){
    case COLOUR_TAG_RED:
        gFreeMem[0] -= size;
        break;
    case COLOUR_TAG_GREEN:
        gFreeMem[1] -= size;
        break;
    case COLOUR_TAG_BLUE:
        gFreeMem[2] -= size;
        break;
    case COLOUR_TAG_YELLOW:
        gFreeMem[3] -= size;
        break;
    case COLOUR_TAG_MAGENTA:
        gFreeMem[4] -= size;
        break;
    case COLOUR_TAG_CYAN:
        gFreeMem[5] -= size;
        break;
    case COLOUR_TAG_WHITE:
        gFreeMem[6] -= size;
        break;
    case COLOUR_TAG_GREY:
        gFreeMem[7] -= size;
        break;
    case COLOUR_TAG_SEMITRANS_GREY:
        gFreeMem[8] -= size;
        break;
    case COLOUR_TAG_ORANGE:
        gFreeMem[9] -= size;
        break;
    case COLOUR_TAG_BLACK:
        gFreeMem[10] -= size;
        break;
    }
    gFreeMem[11] += size;
}
#endif

void free_memory_pool_slot(s32 poolIndex, s32 slotIndex) {
    s32 nextIndex;
    s32 prevIndex;
    s32 tempNextIndex;
    MemoryPool *pool;
    MemoryPoolSlot *slots;
    MemoryPoolSlot *slot;
    MemoryPoolSlot *nextSlot;
    MemoryPoolSlot *prevSlot;
    
    pool = &gMemoryPools[poolIndex];
    slots = pool->slots;
    slot = &slots[slotIndex];
    nextIndex = slot->nextIndex;
    prevIndex = slot->prevIndex;
    nextSlot = &slots[nextIndex];
    prevSlot = &slots[prevIndex];
    slot->flags = 0;
    if (nextIndex != -1) {
        if (nextSlot->flags == 0) {
#ifdef PUPPYPRINT_DEBUG
        adjust_mem_value(slot->size, slot->colourTag);
#endif
            slot->size += nextSlot->size;
            tempNextIndex = nextSlot->nextIndex;
            slot->nextIndex = tempNextIndex;
            if (tempNextIndex != -1) {
                slots[tempNextIndex].prevIndex = slotIndex;
            }
            pool->curNumSlots--;
            slots[pool->curNumSlots].index = nextIndex;
        }
    }
    if (prevIndex != -1) {
        if (prevSlot->flags == 0) {
#ifdef PUPPYPRINT_DEBUG
        adjust_mem_value(prevSlot->size, prevSlot->colourTag);
#endif
            prevSlot->size += slot->size;
            tempNextIndex = slot->nextIndex;
            prevSlot->nextIndex = tempNextIndex;
            if (tempNextIndex != -1) {
                slots[tempNextIndex].prevIndex = prevIndex;
            }
            pool->curNumSlots--;
            slots[pool->curNumSlots].index = slotIndex;
        }
    }
}

s32 allocate_memory_pool_slot(s32 poolIndex, s32 slotIndex, s32 size, s32 slotIsTaken, s32 newSlotIsTaken, u32 colourTag) {
    MemoryPool *pool;
    MemoryPoolSlot *poolSlots;
    s32 index;
    s32 nextIndex;
    s32 poolSize;
    
    pool = &gMemoryPools[poolIndex];
    poolSlots = pool->slots;
    poolSlots[slotIndex].flags = slotIsTaken;
    poolSize = poolSlots[slotIndex].size;
    poolSlots[slotIndex].size = size;
    poolSlots[slotIndex].colourTag = colourTag;
    index = poolSlots[pool->curNumSlots].index;
    if (size < poolSize) {
#ifdef PUPPYPRINT_DEBUG
        adjust_mem_value(-size, colourTag);
#endif
        index = (pool->curNumSlots + poolSlots)->index;
        pool->curNumSlots++;
        poolSlots[index].data = &poolSlots[slotIndex].data[size];
        poolSlots[index].size = poolSize;
        poolSlots[index].size -= size;
        poolSlots[index].sizeUsed = size;
        poolSlots[index].flags = newSlotIsTaken;
        poolSize = poolSlots[slotIndex].nextIndex;
        nextIndex = poolSize;
        poolSlots[index].prevIndex = slotIndex;
        poolSlots[index].nextIndex = nextIndex;
        poolSlots[slotIndex].nextIndex = index;
        if (nextIndex != -1) {
            poolSlots[nextIndex].prevIndex = index;
        }
        return index;
    }
    return slotIndex;
}

/**
 * Returns the passed in address aligned to the next 16-byte boundary.
 * Official name: mmAlign16
 */
u8 *align16(u8 *address) {
    s32 remainder = (s32)address & 0xF;
    if (remainder > 0) {
        address = (u8 *)(((s32)address - remainder) + 16);
    }
    return address;
}

/**
 * Returns the passed in address aligned to the next 8-byte boundary.
 * Unused.
 * Official name: mmAlign8
 */
u8 *align8(u8 *address) {
    s32 remainder = (s32)address & 0x7;
    if (remainder > 0) {
        address = (u8 *)(((s32)address - remainder) + 8);
    }
    return address;
}

/**
 * Returns the passed in address aligned to the next 4-byte boundary.
 * Unused.
 * Official name: mmAlign4
 */
u8 *align4(u8 *address) {
    s32 remainder = (s32)address & 0x3;
    if (remainder > 0) {
        address = (u8 *)(((s32)address - remainder) + 4);
    }
    return address;
}

s32 func_800718A4(void) {
    u32 colours[64];
    u32 colourCounts[64];
    MemoryPoolSlot *curSlot;
    s32 temp;
    s32 i;
    s32 j;
    s32 colourIndex;
    s32 var_a2;
    u32 curColour;
    
    temp = 0;
    for (j = 0; j < 64; j++) {
        colours[j] = 0;
        colourCounts[j] = 0; 
    }
    for (i = 0; i < gNumberOfMemoryPools; i++) {
        curSlot = gMemoryPools[i].slots;
        do {
            if (curSlot->flags != 0) {
                var_a2 = curSlot->colourTag;
                if (var_a2 != 0) {
                    curColour = var_a2;
                    colourIndex = 0;
                    while (colourIndex < 64 && curColour != colours[colourIndex] && colours[colourIndex] != 0) {
                        var_a2 = colours[colourIndex];
                        colourIndex++;
                    }
                    if (colourIndex < 64) {
                        colours[colourIndex] = curColour;
                        colourCounts[colourIndex]++;
                    } else {
                        temp++;
                    }
                }
            }
            var_a2 = curSlot->nextIndex;
            if (var_a2 != -1) {
                curSlot = &gMemoryPools[i].slots[curSlot->nextIndex];
            }
        } while (var_a2 != (-1));
    }
}

s32 get_memory_colour_tag_count(u32 colourTag) {
    s32 i, count;
    MemoryPoolSlot *slot;
    count = 0;
    slot = &gMemoryPools[0].slots[0];
    for (i = 0; i < 1600; i++) {
        if (slot->flags != 0) {
            if(colourTag == slot->colourTag) {
                count++;
            }
        }
        slot++;
    }
    return count;
}
