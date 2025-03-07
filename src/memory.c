/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80070B30 */

#include "memory.h"
#include "printf.h"
#include "thread0_epc.h"
#include "joypad.h"
#include "math_util.h"

/************ .bss ************/

#ifndef _ALIGN16
#define _ALIGN16(a) (((u32) (a) & ~0xF) + 0x10)
#endif

MemoryPool gMemoryPools[POOL_COUNT]; // Only two are used.
s32 gNumberOfMemoryPools;
UNUSED s32 D_801235C4;
FreeQueueSlot gFreeQueue[FREE_QUEUE_SIZE];
s32 gFreeQueueCount;
s32 gFreeQueueTimer; // Official Name: mmDelay

/******************************/

/**
 * Creates the main memory pool.
 * Starts at 0x8012D3F0. Ends at 0x80400000. Contains 1600 allocation slots.
 * Official Name: mmInit
 */
void mempool_init_main(void) {
    s32 ramEnd;

    gNumberOfMemoryPools = -1;
    if (EXPANSION_PAK_SUPPORT) {
        ramEnd = EXPANSION_RAM_END;
    } else {
        ramEnd = RAM_END;
    }
    mempool_init(&gMainMemoryPool, ramEnd - (s32) (&gMainMemoryPool), MAIN_POOL_SLOT_COUNT);
    mempool_free_timer(2);
    gFreeQueueCount = 0;
}

/**
 * Creates a new memory pool that's contained inside another one.
 * Official name: mmAllocRegion
 */
MemoryPoolSlot *mempool_new_sub(s32 poolDataSize, s32 numSlots) {
    s32 size;
    MemoryPoolSlot *slots;
    UNUSED s32 unused_2;
    u32 intFlags = interrupts_disable();
    MemoryPoolSlot *newPool;

    size = poolDataSize + (numSlots * sizeof(MemoryPoolSlot));
    slots = (MemoryPoolSlot *) mempool_alloc_safe(size, COLOUR_TAG_WHITE);
    newPool = mempool_init(slots, size, numSlots);
    interrupts_enable(intFlags);
    return newPool;
}

/**
 * Create and initialise a memory pool in RAM that will act as the place where arbitrary allocations can go.
 * Will return the location of the first free slot in that pool.
 */
MemoryPoolSlot *mempool_init(MemoryPoolSlot *slots, s32 poolSize, s32 numSlots) {
    MemoryPoolSlot *firstSlot;
    s32 poolCount;
    s32 i;
    s32 firstSlotSize;

    poolCount = ++gNumberOfMemoryPools;
    firstSlotSize = poolSize - (numSlots * sizeof(MemoryPoolSlot));
    gMemoryPools[poolCount].maxNumSlots = numSlots;
    gMemoryPools[poolCount].curNumSlots = 0;
    gMemoryPools[poolCount].slots = slots;
    gMemoryPools[poolCount].size = poolSize;
    firstSlot = slots;
    for (i = 0; i < gMemoryPools[poolCount].maxNumSlots; i++) {
        firstSlot->index = i;
        firstSlot++;
    }
    firstSlot = &gMemoryPools[poolCount].slots[0];
    slots += numSlots;
    if ((s32) slots & 0xF) {
        firstSlot->data = (u8 *) _ALIGN16(slots);
    } else {
        firstSlot->data = (u8 *) slots;
    }
    firstSlot->size = firstSlotSize;
    firstSlot->flags = SLOT_FREE;
    firstSlot->prevIndex = MEMSLOT_NONE;
    firstSlot->nextIndex = MEMSLOT_NONE;
    gMemoryPools[poolCount].curNumSlots++;
    return gMemoryPools[poolCount].slots;
}

/**
 * Reserves and returns memory from the main memory pool. Has 2 assert checks.
 * Will cause an exception if the size is 0 or if memory cannot be reserved,
 * dumping the function stack contents onto a controller pak for debugging.
 */
void *mempool_alloc_safe(s32 size, u32 colourTag) {
    void *addr;
    if (size == 0) {
        dump_memory_to_cpak(stack_pointer()->sp, size, colourTag);
    }
    addr = mempool_slot_find(POOL_MAIN, size, colourTag);
    if (addr == NULL) {
        dump_memory_to_cpak(stack_pointer()->sp, size, colourTag);
    }
    return addr;
}

/**
 * Reserves and returns memory from the main memory pool. Has no assert checks.
 */
MemoryPoolSlot *mempool_alloc(s32 size, u32 colourTag) {
    return mempool_slot_find(POOL_MAIN, size, colourTag);
}

/**
 * Search the existing empty slots and try to find one that can meet the size requirement.
 * Afterwards, write the new allocation data to the slot in question and return the address.
 */
MemoryPoolSlot *mempool_slot_find(MemoryPools poolIndex, s32 size, u32 colourTag) {
    s32 slotSize;
    MemoryPoolSlot *curSlot;
    UNUSED s32 pad;
    MemoryPool *pool;
    MemoryPoolSlot *slots;
    u32 intFlags;
    s32 nextIndex;
    s32 currIndex;

    intFlags = interrupts_disable();
    if (size == 0) {
        stubbed_printf("*** mmAlloc: size = 0 ***\n");
    }
    pool = &gMemoryPools[poolIndex];
    if ((pool->curNumSlots + 1) == (*pool).maxNumSlots) {
        interrupts_enable(intFlags);
        stubbed_printf("*** mm Error *** ---> No more slots available.\n");
        return NULL;
    }
    currIndex = MEMSLOT_NONE;
    if (size & 0xF) {
        size = (size & ~0xF);
        size += 0x10;
    }
    slots = pool->slots;
    slotSize = 0x7FFFFFFF;
    nextIndex = 0;
    do {
        curSlot = &slots[nextIndex];
        if (curSlot->flags == SLOT_FREE) {
            if (curSlot->size >= size && curSlot->size < slotSize) {
                slotSize = curSlot->size;
                currIndex = nextIndex;
            }
        }
        nextIndex = curSlot->nextIndex;
    } while (nextIndex != MEMSLOT_NONE);
    if (currIndex != MEMSLOT_NONE) {
        mempool_slot_assign(poolIndex, (s32) currIndex, size, 1, 0, colourTag);
        interrupts_enable(intFlags);
        return (MemoryPoolSlot *) (slots + currIndex)->data;
    }
    interrupts_enable(intFlags);
    stubbed_printf("\n*** mm Error *** ---> No suitble block found for allocation.\n");
    return NULL;
}

/**
 * Allocate memory from a specific pool.
 * Official name: mmAllocR
 */
void *mempool_alloc_pool(MemoryPoolSlot *slots, s32 size) {
    s32 i;
    for (i = gNumberOfMemoryPools; i != 0; i--) {
        if (slots == gMemoryPools[i].slots) {
            return mempool_slot_find(i, size, 0);
        }
    }
    return (void *) NULL;
}

/**
 * Allocates memory from the main pool at a fixed address.
 * Rearranges the memory slots to place one at that address if possible.
 * Official Name: mmAllocAtAddr
 */
void *mempool_alloc_fixed(s32 size, u8 *address, u32 colorTag) {
    s32 i;
    MemoryPoolSlot *curSlot;
    MemoryPoolSlot *slots;
    u32 intFlags;

    intFlags = interrupts_disable();
    if (size == 0) {
        stubbed_printf("*** mmAllocAtAddr: size = 0 ***\n");
    }
    if ((gMemoryPools[POOL_MAIN].curNumSlots + 1) == gMemoryPools[POOL_MAIN].maxNumSlots) {
        interrupts_enable(intFlags);
        stubbed_printf("\n*** mm Error *** ---> No more slots available.\n");
    } else {
        if (size & 0xF) {
            size = _ALIGN16(size);
        }
        slots = gMemoryPools[POOL_MAIN].slots;
        for (i = 0; i != MEMSLOT_NONE; i = curSlot->nextIndex) {
            curSlot = &slots[i];
            if (curSlot->flags == SLOT_FREE) {
                if ((u32) address >= (u32) curSlot->data &&
                    (u32) address + size <= (u32) curSlot->data + curSlot->size) {
                    if (address == (u8 *) curSlot->data) {
                        mempool_slot_assign(POOL_MAIN, i, size, 1, 0, colorTag);
                        interrupts_enable(intFlags);
                        return curSlot->data;
                    } else {
                        i = mempool_slot_assign(POOL_MAIN, i, (u32) address - (u32) curSlot->data, 0, 1, colorTag);
                        mempool_slot_assign(POOL_MAIN, i, size, 1, 0, colorTag);
                        interrupts_enable(intFlags);
                        return (slots + i)->data;
                    }
                }
            }
        }
        interrupts_enable(intFlags);
    }
    stubbed_printf("\n*** mm Error *** ---> Can't allocate memory at desired address.\n");
    return NULL;
}

/**
 * Sets the tick timer for the free queue.
 * If it's set to 0, then it clears the existing queue.
 * Nonzero amounts set any future frees to wait that many ticks
 * before clearing from memory.
 */
void mempool_free_timer(s32 state) {
    u32 intFlags = interrupts_disable();
    gFreeQueueTimer = state;
    if (state == 0) { // flush free queue if state is 0.
        while (gFreeQueueCount > 0) {
            mempool_free_addr(gFreeQueue[--gFreeQueueCount].dataAddress);
        }
    }
    interrupts_enable(intFlags);
}

/**
 * Unallocates data from the pool that contains the data. Will free immediately if the free queue
 * state is set to 0, otherwise the data will just be marked for deletion.
 * Official Name: mmFree
 */
void mempool_free(void *data) {
    u32 intFlags = interrupts_disable();
    if (gFreeQueueTimer == 0) {
        mempool_free_addr(data);
    } else {
        mempool_free_queue(data);
    }
    interrupts_enable(intFlags);
}

/**
 * Frees all the addresses in the free queue.
 * Official Name: mmFreeTick
 */
void mempool_free_queue_clear(void) {
    s32 i;
    u32 intFlags;

    intFlags = interrupts_disable();

    for (i = 0; i < gFreeQueueCount;) {
        gFreeQueue[i].freeTimer--;
        if (gFreeQueue[i].freeTimer == 0) {
            mempool_free_addr(gFreeQueue[i].dataAddress);
            gFreeQueue[i].dataAddress = gFreeQueue[gFreeQueueCount - 1].dataAddress;
            gFreeQueue[i].freeTimer = gFreeQueue[gFreeQueueCount - 1].freeTimer;
            gFreeQueueCount--;
        } else {
            stubbed_printf("\n*** mm Error *** ---> Can't free ram at this location: %x\n", gFreeQueue[i].dataAddress);
            i++;
        }
    }

    interrupts_enable(intFlags);
}

/**
 * Searches the memory pools for a slot matching the given address.
 * If a slot is found, free it.
 * Official name: heapFree
 */
void mempool_free_addr(u8 *address) {
    s32 slotIndex;
    s32 poolIndex;
    MemoryPool *pool;
    MemoryPoolSlot *slots;
    MemoryPoolSlot *slot;

    poolIndex = mempool_get_pool(address);
    pool = gMemoryPools;
    slots = pool[poolIndex].slots;
    for (slotIndex = 0; slotIndex != MEMSLOT_NONE; slotIndex = slot->nextIndex) {
        slot = &slots[slotIndex];

        if (address == (u8 *) slot->data) {
            if (slot->flags == SLOT_USED || slot->flags == SLOT_SAFEGUARD) {
                mempool_slot_clear(poolIndex, slotIndex);
            }
            break;
        }
        slot = &slots[slotIndex];
    }
    stubbed_printf("\n*** mm Error *** ---> No match found for mmFree.\n");
}

/**
 * Clears all memory pools.
 * When clearing a pool, it checks if the slot uses the 0x04 flag.
 * It calls an early return if that flag is set and more slots remain after.
 */
UNUSED void mempool_clear(void) {
    MemoryPoolSlot *slotPos;
    MemoryPool *pool;
    UNUSED s32 pad;
    u32 intFlags;
    s32 poolIndex;
    s32 slotIndex;

    intFlags = interrupts_disable();
    poolIndex = gNumberOfMemoryPools;
    while (poolIndex != -1) {
        pool = &gMemoryPools[poolIndex];
        slotPos = pool->slots;
        slotIndex = 0;
        do {
            if ((slotPos + slotIndex)->flags == SLOT_USED) {
                mempool_slot_clear(poolIndex, slotIndex);
            }
            if ((slotPos + slotIndex)->flags == SLOT_SAFEGUARD) {
                if (pool->curNumSlots == 1) {
                    mempool_slot_clear(poolIndex, slotIndex);
                } else {
                    interrupts_enable(intFlags);
                    stubbed_printf("*** Slots still in use in region ***\n");
                    return;
                }
            }
            slotIndex = (slotPos + slotIndex)->nextIndex;
        } while (slotIndex != MEMSLOT_NONE);
        poolIndex--;
    }
    interrupts_enable(intFlags);
}

/**
 * Adds the current memory address to the back of the queue, so it can be freed.
 */
void mempool_free_queue(void *dataAddress) {
    gFreeQueue[gFreeQueueCount].dataAddress = dataAddress;
    gFreeQueue[gFreeQueueCount].freeTimer = gFreeQueueTimer;
    gFreeQueueCount++;

    if (gFreeQueueCount >= ARRAY_COUNT(gFreeQueue)) {
        stubbed_printf("\n*** mm Error *** ---> stbf stack too deep!\n");
    }
}

/**
 * Search the memory pool for the current address.
 * Check if the slot is used, then set the 0x02 slot flag.
 * Return 1 if successful, otherwise return 0.
 */
s32 mempool_locked_set(u8 *address) {
    s32 slotIndex;
    MemoryPoolSlot *slot;
    MemoryPool *pool;
    u32 intFlags;

    intFlags = interrupts_disable();
    pool = &gMemoryPools[mempool_get_pool(address)];
    slotIndex = 0;
    while (slotIndex != MEMSLOT_NONE) {
        slot = slotIndex + pool->slots; // `slot = &pool->slots[slotIndex];` does not match.
        if (address == (u8 *) slot->data) {
            if (slot->flags == SLOT_USED || slot->flags == SLOT_SAFEGUARD) {
                slot->flags |= SLOT_LOCKED;
                interrupts_enable(intFlags);
                return 1;
            }
        }
        slotIndex = slot->nextIndex;
    }
    stubbed_printf("\n*** mm Error *** ---> Can't fix the specified block.\n");
    interrupts_enable(intFlags);
    return 0;
}

/**
 * Search the memory pool for the current address.
 * Check if the slot is marked with 0x02.
 * Unset that flag and return 1 if so, otherise 0.
 */
s32 mempool_locked_unset(u8 *address) {
    s32 slotIndex;
    MemoryPoolSlot *slot;
    MemoryPool *pool;
    u32 intFlags;

    intFlags = interrupts_disable();
    pool = &gMemoryPools[mempool_get_pool(address)];
    slotIndex = 0;
    while (slotIndex != MEMSLOT_NONE) {
        slot = slotIndex + pool->slots; // `slot = &pool->slots[slotIndex];` does not match.
        if (address == (u8 *) slot->data) {
            if (slot->flags & SLOT_LOCKED) {
                slot->flags ^= SLOT_LOCKED;
                interrupts_enable(intFlags);
                return 1;
            }
        }
        slotIndex = slot->nextIndex;
    }
    stubbed_printf("\n*** mm Error *** ---> Can't unfix the specified block.\n");
    interrupts_enable(intFlags);
    return 0;
}

/**
 * Returns the index of the memory pool containing the memory address.
 */
s32 mempool_get_pool(u8 *address) {
    s32 i;
    MemoryPool *pool;

    for (i = gNumberOfMemoryPools; i > 0; i--) {
        pool = &gMemoryPools[i];
        if ((u8 *) pool->slots >= address) {
            continue;
        }
        if (address < pool->size + (u8 *) pool->slots) {
            break;
        }
    }
    return i;
}

/**
 * Clears the current slot of all information, effectively freeing the allocated memory.
 * Unused slots before and after will be merged with this slot
 */
void mempool_slot_clear(MemoryPools poolIndex, s32 slotIndex) {
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
    pool = pool; // Fakematch
    slot = &slots[slotIndex];
    nextIndex = slot->nextIndex;
    prevIndex = slot->prevIndex;
    slot = slot; // Fakematch
    nextSlot = &slots[nextIndex];
    prevSlot = &slots[prevIndex];
    slot->flags = SLOT_FREE;
    if (nextIndex != MEMSLOT_NONE) {
        if (nextSlot->flags == SLOT_FREE) {
            slot->size += nextSlot->size;
            tempNextIndex = nextSlot->nextIndex;
            slot->nextIndex = tempNextIndex;
            if (tempNextIndex != MEMSLOT_NONE) {
                slots[tempNextIndex].prevIndex = slotIndex;
            }
            pool->curNumSlots--;
            slots[pool->curNumSlots].index = nextIndex;
        }
    }
    if (prevIndex != MEMSLOT_NONE) {
        if (prevSlot->flags == SLOT_FREE) {
            prevSlot->size += slot->size;
            tempNextIndex = slot->nextIndex;
            prevSlot->nextIndex = tempNextIndex;
            if (tempNextIndex != MEMSLOT_NONE) {
                slots[tempNextIndex].prevIndex = prevIndex;
            }
            pool->curNumSlots--;
            slots[pool->curNumSlots].index = slotIndex;
        }
    }
}

/**
 * Return the address of the first slot of a given memory pool.
 */
UNUSED MemoryPoolSlot *get_memory_pool_address(MemoryPools poolIndex) {
    return gMemoryPools[poolIndex].slots;
}

/**
 * Initialise and attempts to fit the new memory block in the slot given.
 * Updates the linked list with any entries before and after then returns the new slot index.
 * If the region cannot fit, return the old slot instead.
 */
s32 mempool_slot_assign(MemoryPools poolIndex, s32 slotIndex, s32 size, s32 slotIsTaken, s32 newSlotIsTaken,
                        u32 colourTag) {
    MemoryPool *pool;
    MemoryPoolSlot *poolSlots;
    s32 index;
    s32 nextIndex;
    s32 poolSize;

    pool = &gMemoryPools[poolIndex];
    poolSlots = pool->slots;
    pool = pool; // Fakematch
    poolSlots[slotIndex].flags = slotIsTaken;
    poolSize = poolSlots[slotIndex].size;
    poolSlots[slotIndex].size = size;
    poolSlots[slotIndex].colourTag = colourTag;
    index = poolSlots[pool->curNumSlots].index;
    if (size < poolSize) {
        index = (pool->curNumSlots + poolSlots)->index;
        pool->curNumSlots++;
        poolSlots[index].data = &poolSlots[slotIndex].data[size];
        poolSlots[index].size = poolSize;
        poolSlots[index].size -= size;
        poolSlots[index].flags = newSlotIsTaken;
        poolSize = poolSlots[slotIndex].nextIndex;
        nextIndex = poolSize;
        poolSlots[index].prevIndex = slotIndex;
        poolSlots[index].nextIndex = nextIndex;
        poolSlots[slotIndex].nextIndex = index;
        if (nextIndex != MEMSLOT_NONE) {
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
    s32 remainder = (s32) address & 0xF;
    if (remainder > 0) {
        address = (u8 *) (((s32) address - remainder) + 16);
    }
    return address;
}

/**
 * Returns the passed in address aligned to the next 8-byte boundary.
 * Official name: mmAlign8
 */
UNUSED u8 *align8(u8 *address) {
    s32 remainder = (s32) address & 0x7;
    if (remainder > 0) {
        address = (u8 *) (((s32) address - remainder) + 8);
    }
    return address;
}

/**
 * Returns the passed in address aligned to the next 4-byte boundary.
 * Official name: mmAlign4
 */
UNUSED u8 *align4(u8 *address) {
    s32 remainder = (s32) address & 0x3;
    if (remainder > 0) {
        address = (u8 *) (((s32) address - remainder) + 4);
    }
    return address;
}

/**
 * Iterate through all active memory pool slots and categorise them by colour.
 * Tally how many colours there are, then how many colours are in use.
 * Afterwards, print out the results.
 * Since the function only has space for 64 different colours, make sure
 * any missed tallies are at least reported.
 */
UNUSED s32 find_active_pool_slot_colours(void) {
    u32 colours[64];
    u32 colourCounts[64];
    MemoryPoolSlot *curSlot;
    s32 numOverflows;
    s32 i;
    s32 j;
    s32 colourIndex;
    s32 slotColour;
    u32 curColour;

    numOverflows = 0;
    for (j = 0; j < 64; j++) {
        colours[j] = 0;
        colourCounts[j] = 0;
    }
    for (i = 0; i < gNumberOfMemoryPools; i++) {
        curSlot = gMemoryPools[i].slots;
        do {
            if (curSlot->flags != SLOT_FREE) {
                slotColour = curSlot->colourTag;
                if (slotColour != 0) {
                    curColour = slotColour;
                    colourIndex = 0;
                    while (colourIndex < 64 && curColour != colours[colourIndex] && colours[colourIndex] != 0) {
                        slotColour = colours[colourIndex];
                        colourIndex++;
                    }
                    if (colourIndex < 64) {
                        colours[colourIndex] = curColour;
                        colourCounts[colourIndex]++;
                    } else {
                        numOverflows++;
                    }
                }
            }
            slotColour = curSlot->nextIndex;
            if (slotColour != MEMSLOT_NONE) {
                curSlot = &gMemoryPools[i].slots[curSlot->nextIndex];
            }
        } while (slotColour != MEMSLOT_NONE);
    }
    slotColour = 0;
    for (j = 0; colours[j] != 0 && j < 64; j++) {
        stubbed_printf("Colour %x >> %d\n", colours[j], colourCounts[j]);
    }
    slotColour = 0;
    if (numOverflows) {
        stubbed_printf("Unable to record %d slots, colours overflowed table.\n", numOverflows);
    }
    numOverflows = slotColour;
}

/**
 * Search through each memory pool, counting up the slots that match the colour tag looking to be found.
 * Marked as unused, since the functions calling it is also unused.
 */
UNUSED s32 get_memory_colour_tag_count(u32 colourTag) {
    s32 i, count;
    MemoryPoolSlot *slot;
    count = 0;
    slot = &gMemoryPools[POOL_MAIN].slots[0];
    for (i = 0; i < MAIN_POOL_SLOT_COUNT; i++) {
        if (slot->flags != SLOT_FREE) {
            if (colourTag == slot->colourTag) {
                count++;
            }
        }
        slot++;
    }
    return count;
}

/**
 * Prints out the counts for each color tag in the main pool.
 */
UNUSED void mempool_print_tags_usb(void) {
    stubbed_printf("RED %d\n", get_memory_colour_tag_count(COLOUR_TAG_RED));
    stubbed_printf("GREEN %d\n", get_memory_colour_tag_count(COLOUR_TAG_GREEN));
    stubbed_printf("BLUE %d\n", get_memory_colour_tag_count(COLOUR_TAG_BLUE));
    stubbed_printf("YELLOW %d\n", get_memory_colour_tag_count(COLOUR_TAG_YELLOW));
    stubbed_printf("MAGENTA %d\n", get_memory_colour_tag_count(COLOUR_TAG_MAGENTA));
    stubbed_printf("CYAN %d\n", get_memory_colour_tag_count(COLOUR_TAG_CYAN));
    stubbed_printf("WHITE %d\n", get_memory_colour_tag_count(COLOUR_TAG_WHITE));
    stubbed_printf("GREY %d\n", get_memory_colour_tag_count(COLOUR_TAG_GREY));
    stubbed_printf("ORANGE %d\n\n", get_memory_colour_tag_count(COLOUR_TAG_ORANGE));
}

/**
 * Draws the counts for each color tag in the main pool.
 * See: https://tcrf.net/Diddy_Kong_Racing#Current_Colors
 */
UNUSED void mempool_print_tags_screen(void) {
    set_render_printf_background_colour(0, 0, 0, 128);
    render_printf("RED %d\n", get_memory_colour_tag_count(COLOUR_TAG_RED));
    render_printf("GREEN %d\n", get_memory_colour_tag_count(COLOUR_TAG_GREEN));
    render_printf("BLUE %d\n", get_memory_colour_tag_count(COLOUR_TAG_BLUE));
    render_printf("YELLOW %d\n", get_memory_colour_tag_count(COLOUR_TAG_YELLOW));
    render_printf("MAGENTA %d\n", get_memory_colour_tag_count(COLOUR_TAG_MAGENTA));
    render_printf("CYAN %d\n", get_memory_colour_tag_count(COLOUR_TAG_CYAN));
    render_printf("WHITE %d\n", get_memory_colour_tag_count(COLOUR_TAG_WHITE));
    render_printf("GREY %d\n", get_memory_colour_tag_count(COLOUR_TAG_GREY));
    render_printf("ORANGE %d\n\n", get_memory_colour_tag_count(COLOUR_TAG_ORANGE));
}

/**
 * Prints out the status of each memory pool slot.
 * Will mark based on what flags the slot has.
 * Official name: mmSlotPrint
 */
UNUSED void mempool_print_slots(void) {
    int flags;
    int nextIndex;
    int i;
    MemoryPoolSlot *slot;

    for (i = 0; i <= gNumberOfMemoryPools; i++) {
        stubbed_printf("Region = %d	 loc = %x	 size = %x\t", i, gMemoryPools[i].slots, gMemoryPools[i].size);
        slot = &gMemoryPools[i].slots[0];

        do {
            flags = slot->flags;
            nextIndex = slot->nextIndex;

            switch (flags) {
                case 0:
                    stubbed_printf("FREE");
                    break;
                case 1:
                    stubbed_printf("ALLOCATED");
                    break;
                case 2:
                    stubbed_printf("ALLOCATED,FIXED");
                    break;
                default:
                    stubbed_printf("\n");
                    break;
            }
            stubbed_printf("\n");
            if (nextIndex == -1) {
                continue;
            } else {
                slot = &gMemoryPools[i].slots[slot->nextIndex];
            }
        } while (nextIndex != -1);
    }
}

/**
 * Print out the current status of each existing memory pool.
 */
UNUSED void mempool_print_data(void) {
    s32 i;
    for (i = gNumberOfMemoryPools; i != -1; i--) {
        stubbed_printf("Region number = %d\t", i);
        stubbed_printf("maxSlots = %d\t", gMemoryPools[i].maxNumSlots);
        stubbed_printf("slotsUsed = %d\t", gMemoryPools[i].curNumSlots);
        stubbed_printf("loc = %x\t", gMemoryPools[i].slots);
        stubbed_printf("size = %x\n", gMemoryPools[i].size);
        stubbed_printf("\n");
    }
}
