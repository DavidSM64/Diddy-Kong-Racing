/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80070B30 */

#include "memory.h"
#include "printf.h"
#include "thread0_epc.h"
#include "controller.h"
#include "math_util.h"

/************ .bss ************/

#ifndef _ALIGN16
#define _ALIGN16(a) (((u32) (a) & ~0xF) + 0x10)
#endif

MemoryPool gMemoryPools[4]; // Only two are used.
s32 gNumberOfMemoryPools;
UNUSED s32 D_801235C4;
FreeQueueSlot gFreeQueue[256];
s32 gFreeQueueCount;
s32 gFreeQueueTimer; // Official Name: mmDelay

extern MemoryPoolSlot gMainMemoryPool;

/******************************/

/**
 * Creates the main memory pool.
 * Starts at 0x8012D3F0. Ends at 0x80400000. Contains 1600 allocation slots.
 * Official Name: mmInit
 */
void init_main_memory_pool(void) {
    s32 ramEnd;

    gNumberOfMemoryPools = -1;
    if (EXPANSION_PAK_SUPPORT) {
        ramEnd = EXPANSION_RAM_END;
    } else {
        ramEnd = RAM_END;
    }
    new_memory_pool(&gMainMemoryPool, ramEnd - (s32) (&gMainMemoryPool), MAIN_POOL_SLOT_COUNT);
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
    UNUSED s32 unused_2;
    u32 flags = disable_interrupts();
    MemoryPoolSlot *newPool;

    size = poolDataSize + (numSlots * sizeof(MemoryPoolSlot));
    slots = (MemoryPoolSlot *) allocate_from_main_pool_safe(size, COLOUR_TAG_WHITE);
    newPool = new_memory_pool(slots, size, numSlots);
    enable_interrupts(flags);
    return newPool;
}

/**
 * Create and initialise a memory pool in RAM that will act as the place where arbitrary allocations can go.
 * Will return the location of the first free slot in that pool.
 */
MemoryPoolSlot *new_memory_pool(MemoryPoolSlot *slots, s32 poolSize, s32 numSlots) {
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
    firstSlot->flags = 0;
    firstSlot->prevIndex = -1;
    firstSlot->nextIndex = -1;
    gMemoryPools[poolCount].curNumSlots++;
    return gMemoryPools[poolCount].slots;
}

/**
 * Reserves and returns memory from the main memory pool. Has 2 assert checks.
 * Will cause an exception if the size is 0 or if memory cannot be reserved.
 */
void *allocate_from_main_pool_safe(s32 size, u32 colourTag) {
    void *temp_v0;
    if (size == 0) {
        dump_memory_to_cpak(get_stack_pointer()->unk14, size, colourTag);
    }
    temp_v0 = allocate_from_memory_pool(0, size, colourTag);
    if (temp_v0 == (void *) NULL) {
        dump_memory_to_cpak(get_stack_pointer()->unk14, size, colourTag);
    }
    return temp_v0;
}

/**
 * Reserves and returns memory from the main memory pool. Has no assert checks.
 */
MemoryPoolSlot *allocate_from_main_pool(s32 size, u32 colourTag) {
    return allocate_from_memory_pool(0, size, colourTag);
}

/**
 * Search the existing empty slots and try to find one that can meet the size requirement.
 * Afterwards, write the new allocation data to the slot in question and return the address.
 */
MemoryPoolSlot *allocate_from_memory_pool(s32 poolIndex, s32 size, u32 colourTag) {
    s32 slotSize;
    MemoryPoolSlot *curSlot;
    UNUSED s32 pad;
    MemoryPool *pool;
    MemoryPoolSlot *slots;
    u32 flags;
    s32 nextIndex;
    s32 currIndex;

    flags = disable_interrupts();
    if (size == 0) {
        stubbed_printf("*** mmAlloc: size = 0 ***\n");
    }
    pool = &gMemoryPools[poolIndex];
    if ((pool->curNumSlots + 1) == (*pool).maxNumSlots) {
        enable_interrupts(flags);
        stubbed_printf("*** mm Error *** ---> No more slots available.\n");
        return NULL;
    }
    currIndex = -1;
    if (size & 0xF) {
        size = (size & ~0xF);
        size += 0x10;
    }
    slots = pool->slots;
    slotSize = 0x7FFFFFFF;
    nextIndex = 0;
    do {
        curSlot = &slots[nextIndex];
        if (curSlot->flags == 0) {
            if (curSlot->size >= size && curSlot->size < slotSize) {
                slotSize = curSlot->size;
                currIndex = nextIndex;
            }
        }
        nextIndex = curSlot->nextIndex;
    } while (nextIndex != -1);
    if (currIndex != -1) {
        allocate_memory_pool_slot(poolIndex, (s32) currIndex, size, 1, 0, colourTag);
        enable_interrupts(flags);
        return (MemoryPoolSlot *) (slots + currIndex)->data;
    }
    enable_interrupts(flags);
    stubbed_printf("\n*** mm Error *** ---> No suitble block found for allocation.\n");
    return NULL;
}

/* Official name: mmAllocR */
void *allocate_from_pool_containing_slots(MemoryPoolSlot *slots, s32 size) {
    s32 i;
    for (i = gNumberOfMemoryPools; i != 0; i--) {
        if (slots == gMemoryPools[i].slots) {
            return allocate_from_memory_pool(i, size, 0);
        }
    }
    return (void *) NULL;
}

/* Official Name: mmAllocAtAddr */
void *allocate_at_address_in_main_pool(s32 size, u8 *address, u32 colorTag) {
    s32 i;
    MemoryPoolSlot *curSlot;
    MemoryPoolSlot *slots;
    u32 flags;

    flags = disable_interrupts();
    if (size == 0) {
        stubbed_printf("*** mmAllocAtAddr: size = 0 ***\n");
    }
    if ((gMemoryPools[0].curNumSlots + 1) == gMemoryPools[0].maxNumSlots) {
        enable_interrupts(flags);
        stubbed_printf("\n*** mm Error *** ---> No more slots available.\n");
    } else {
        if (size & 0xF) {
            size = _ALIGN16(size);
        }
        slots = gMemoryPools[0].slots;
        for (i = 0; i != -1; i = curSlot->nextIndex) {
            curSlot = &slots[i];
            if (curSlot->flags == 0) {
                if ((u32) address >= (u32) curSlot->data &&
                    (u32) address + size <= (u32) curSlot->data + curSlot->size) {
                    if (address == (u8 *) curSlot->data) {
                        allocate_memory_pool_slot(0, i, size, 1, 0, colorTag);
                        enable_interrupts(flags);
                        return curSlot->data;
                    } else {
                        i = allocate_memory_pool_slot(0, i, (u32) address - (u32) curSlot->data, 0, 1, colorTag);
                        allocate_memory_pool_slot(0, i, size, 1, 0, colorTag);
                        enable_interrupts(flags);
                        return (slots + i)->data;
                    }
                }
            }
        }
        enable_interrupts(flags);
    }
    stubbed_printf("\n*** mm Error *** ---> Can't allocate memory at desired address.\n");
    return NULL;
}

/**
 * Sets the state of the free queue. State is either 0, 1, or 2.
 * The free queue will get flushed if the state is set to 0.
 * Official name: mmSetDelay
 */
void set_free_queue_state(s32 state) {
    u32 flags = disable_interrupts();
    gFreeQueueTimer = state;
    if (state == 0) { // flush free queue if state is 0.
        while (gFreeQueueCount > 0) {
            free_slot_containing_address(gFreeQueue[--gFreeQueueCount].dataAddress);
        }
    }
    enable_interrupts(flags);
}

/**
 * Unallocates data from the pool that contains the data. Will free immediately if the free queue
 * state is set to 0, otherwise the data will just be marked for deletion.
 * Official Name: mmFree
 */
void free_from_memory_pool(void *data) {
    u32 flags = disable_interrupts();
    if (gFreeQueueTimer == 0) {
        free_slot_containing_address(data);
    } else {
        add_to_free_queue(data);
    }
    enable_interrupts(flags);
}

/**
 * Frees all the addresses in the free queue.
 * Official Name: mmFreeTick
 */
void clear_free_queue(void) {
    s32 i;
    u32 flags;

    flags = disable_interrupts();

    for (i = 0; i < gFreeQueueCount;) {
        gFreeQueue[i].freeTimer--;
        if (gFreeQueue[i].freeTimer == 0) {
            free_slot_containing_address(gFreeQueue[i].dataAddress);
            gFreeQueue[i].dataAddress = gFreeQueue[gFreeQueueCount - 1].dataAddress;
            gFreeQueue[i].freeTimer = gFreeQueue[gFreeQueueCount - 1].freeTimer;
            gFreeQueueCount--;
        } else {
            stubbed_printf("\n*** mm Error *** ---> Can't free ram at this location: %x\n", gFreeQueue[i].dataAddress);
            i++;
        }
    }

    enable_interrupts(flags);
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

UNUSED void func_80071314(void) {
    MemoryPoolSlot *slotPos;
    MemoryPool *pool;
    UNUSED s32 pad;
    u32 flags;
    s32 poolIndex;
    s32 slotIndex;

    flags = disable_interrupts();
    poolIndex = gNumberOfMemoryPools;
    while (poolIndex != -1) {
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
                    enable_interrupts(flags);
                    return;
                }
            }
            slotIndex = (slotPos + slotIndex)->nextIndex;
        } while (slotIndex != -1);
        poolIndex--;
    }
    enable_interrupts(flags);
    stubbed_printf("\n*** mm Error *** ---> No match found for mmFree.\n");
}

// TODO: Find homes for these, too.
UNUSED const char D_800E73A8[] = "*** Slots still in use in region ***\n";
UNUSED const char D_800E73D0[] = "\n*** mm Error *** ---> stbf stack too deep!\n";
UNUSED const char D_800E7400[] = "\n*** mm Error *** ---> Can't fix the specified block.\n";
UNUSED const char D_800E7438[] = "\n*** mm Error *** ---> Can't unfix the specified block.\n";

/**
 * Adds the current memory address to the back of the queue, so it can be freed.
 */
void add_to_free_queue(void *dataAddress) {
    gFreeQueue[gFreeQueueCount].dataAddress = dataAddress;
    gFreeQueue[gFreeQueueCount].freeTimer = gFreeQueueTimer;
    gFreeQueueCount++;
}

s32 func_80071478(u8 *address) {
    s32 slotIndex;
    MemoryPoolSlot *slot;
    MemoryPool *pool;
    u32 flags;

    flags = disable_interrupts();
    pool = &gMemoryPools[get_memory_pool_index_containing_address(address)];
    slotIndex = 0;
    while (slotIndex != -1) {
        slot = slotIndex + pool->slots; // `slot = &pool->slots[slotIndex];` does not match.
        if (address == (u8 *) slot->data) {
            if (slot->flags == 1 || slot->flags == 4) {
                slot->flags |= 2;
                enable_interrupts(flags);
                return TRUE;
            }
        }
        slotIndex = slot->nextIndex;
    }
    enable_interrupts(flags);
    return FALSE;
}

/**
 * Search the memory pool for the slot that's tied to the given address.
 * Return true if it's found, otherwise return false.
 */
s32 memory_slot_exists(u8 *address) {
    s32 slotIndex;
    MemoryPoolSlot *slot;
    MemoryPool *pool;
    u32 flags;

    flags = disable_interrupts();
    pool = &gMemoryPools[get_memory_pool_index_containing_address(address)];
    slotIndex = 0;
    while (slotIndex != -1) {
        slot = slotIndex + pool->slots; // `slot = &pool->slots[slotIndex];` does not match.
        if (address == (u8 *) slot->data) {
            if (slot->flags & 2) {
                slot->flags ^= 2;
                enable_interrupts(flags);
                return TRUE;
            }
        }
        slotIndex = slot->nextIndex;
    }
    enable_interrupts(flags);
    return FALSE;
}

/**
 * Returns the index of the memory pool containing the memory address.
 */
s32 get_memory_pool_index_containing_address(u8 *address) {
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
    pool = pool; // Fakematch
    slot = &slots[slotIndex];
    nextIndex = slot->nextIndex;
    prevIndex = slot->prevIndex;
    slot = slot; // Fakematch
    nextSlot = &slots[nextIndex];
    prevSlot = &slots[prevIndex];
    slot->flags = 0;
    if (nextIndex != -1) {
        if (nextSlot->flags == 0) {
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

/**
 * Return the address of the first slot of a given memory pool.
 */
UNUSED MemoryPoolSlot *get_memory_pool_address(s32 poolIndex) {
    return gMemoryPools[poolIndex].slots;
}

/**
 * Initialise and attempts to fit the new memory block in the slot given.
 * Updates the linked list with any entries before and after then returns the new slot index.
 * If the region cannot fit, return the old slot instead.
 */
s32 allocate_memory_pool_slot(s32 poolIndex, s32 slotIndex, s32 size, s32 slotIsTaken, s32 newSlotIsTaken,
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
            if (curSlot->flags != 0) {
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
            if (slotColour != -1) {
                curSlot = &gMemoryPools[i].slots[curSlot->nextIndex];
            }
        } while (slotColour != -1);
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
    slot = &gMemoryPools[0].slots[0];
    for (i = 0; i < MAIN_POOL_SLOT_COUNT; i++) {
        if (slot->flags != 0) {
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
UNUSED void print_memory_colour_tags(void) {
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
UNUSED void render_memory_colour_tags(void) {
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

/************ .rodata ************/

UNUSED const char D_800E7590[] = "Region = %d	 loc = %x	 size = %x\t";
UNUSED const char D_800E75B4[] = "FREE";
UNUSED const char D_800E75BC[] = "ALLOCATED";
UNUSED const char D_800E75C8[] = "ALLOCATED,FIXED";
UNUSED const char D_800E75D8[] = "\n";
UNUSED const char D_800E75DC[] = "\n";
UNUSED const char D_800E75E0[] = "Region number = %d\t";
UNUSED const char D_800E75F4[] = "maxSlots = %d\t";
UNUSED const char D_800E7604[] = "slotsUsed = %d\t";
UNUSED const char D_800E7614[] = "loc = %x\t";
UNUSED const char D_800E7620[] = "size = %x\n";
UNUSED const char D_800E762C[] = "\n";

/*********************************/

UNUSED void mmSlotPrint(void) {
    s32 i;
    s32 skip;
    s32 index;
    s32 index2;
    s32 nextIndex;
    MemoryPoolSlot *slot;

    for (i = 0; (gNumberOfMemoryPools ^ 0) >= i; i++) {
        if (i && i) {} // Fakematch
        slot = &gMemoryPools[i].slots[0];
        index = 1;
        index2 = -index;
        do {
            index = slot->flags;
            nextIndex = slot->nextIndex;
            skip = nextIndex == index2;
            if (index) {
                if (((((((((!slot->nextIndex) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) {
                    if (nextIndex && nextIndex) {} // Fakematch
                }
            }
            if (skip) {
                continue;
            }
            slot = &gMemoryPools[i].slots[slot->nextIndex];
        } while (nextIndex != (-1));
    }
}

// Unused. Does nothing?
UNUSED void func_80071CE8(void) {
    s32 i;
    for (i = gNumberOfMemoryPools; i != -1; i--) {
        // Nothing here. There might've been a printf or something similar.
    }
}
