/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80070B30 */

#include "memory.h"
#include "printf.h"
#include "thread0_epc.h"
#include "controller.h"

/************ .rodata ************/

const char D_800E7210[] = "*** mmAlloc: size = 0 ***\n";
const char D_800E722C[] = "*** mm Error *** ---> No more slots available.\n";
const char D_800E725C[] = "\n*** mm Error *** ---> No suitble block found for allocation.\n";
const char D_800E729C[] = "*** mmAllocAtAddr: size = 0 ***\n";
const char D_800E72C0[] = "\n*** mm Error *** ---> No more slots available.\n";
const char D_800E72F4[] = "\n*** mm Error *** ---> Can't allocate memory at desired address.\n";
const char D_800E7338[] = "\n*** mm Error *** ---> Can't free ram at this location: %x\n";
const char D_800E7374[] = "\n*** mm Error *** ---> No match found for mmFree.\n";
const char D_800E73A8[] = "*** Slots still in use in region ***\n";
const char D_800E73D0[] = "\n*** mm Error *** ---> stbf stack too deep!\n";
const char D_800E7400[] = "\n*** mm Error *** ---> Can't fix the specified block.\n";
const char D_800E7438[] = "\n*** mm Error *** ---> Can't unfix the specified block.\n";
const char D_800E7474[] = "Colour %x >> %d\n";
const char D_800E7488[] = "Unable to record %d slots, colours overflowed table.\n";

/*********************************/

/************ .bss ************/

MemoryPool gMemoryPools[4];

#ifndef _ALIGN16
#define _ALIGN16(a) (((u32) (a) & ~0xF) + 0x10)
//#define _ALIGN16(val) ((val)&0xFFFFFFF0) + 0x10
#endif

s32 gNumberOfMemoryPools;
s32 D_801235C4;
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
    gNumberOfMemoryPools = -1;
    if (1) {
        // Create the main memory pool.
        new_memory_pool(&gMainMemoryPool, RAM_END - (s32)(&gMainMemoryPool), MAIN_POOL_SLOT_COUNT);
    }
    set_free_queue_state(2);
    gFreeQueueCount = 0;
}

/**
 * Creates a new memory pool that is sectioned off the main one.
 */
MemoryPoolSlot *new_sub_memory_pool(s32 poolDataSize, s32 numSlots) {
    s32 size;
    MemoryPoolSlot *slots;
    UNUSED s32 unused_2;
    s32 *temp = clear_status_register_flags();
    MemoryPoolSlot *newPool;

    size = poolDataSize + (numSlots * sizeof(MemoryPoolSlot));
    slots = (MemoryPoolSlot *)allocate_from_main_pool_safe(size, COLOUR_TAG_WHITE);
    newPool = new_memory_pool(slots, size, numSlots);
    set_status_register_flags(temp);
    return newPool;
}

#ifdef NON_EQUIVALENT
//Match found in Dinosaur Planet, and it's *really* close, but not yet there.
MemoryPoolSlot *new_memory_pool(MemoryPoolSlot *slots, s32 poolSize, s32 numSlots) {
    MemoryPoolSlot *firstSlot;
    MemoryPool *pool;
    s32 i;
    s32 len;

    //The comma seperation seems to generate a better match
    len = gNumberOfMemoryPools++, pool = &gMemoryPools[len];

    len = numSlots * sizeof(MemoryPoolSlot);
    pool->maxNumSlots = numSlots;
    pool->curNumSlots = 0;
    pool->slots = slots;
    pool->size = poolSize;

    firstSlot = slots;

    for (i = 0; i < pool->maxNumSlots; i++) {
        firstSlot->index = i;
        firstSlot++;
    }

    firstSlot = &pool->slots[0];
    slots += numSlots;
    if (((s32)slots & 0xF) != 0) {
        firstSlot->data = _ALIGN16(slots);
    } else {
        firstSlot->data = slots;
    }

    firstSlot->size = poolSize - len;
    firstSlot->flags = 0;
    firstSlot->prevIndex = -1;
    firstSlot->nextIndex = -1;

    pool->curNumSlots++;

    return pool->slots;
}
#else
GLOBAL_ASM("asm/non_matchings/memory/new_memory_pool.s")
#endif

/**
 * Reserves and returns memory from the main memory pool. Has 2 assert checks.
 * Will cause an exception if the size is 0 or if memory cannot be reserved.
 */
void *allocate_from_main_pool_safe(s32 size, u32 colorTag) {
    void *temp_v0;
    if (size == 0) {
        func_800B7460((s32 *)((u8 *)get_stack_pointer()->unk14), size, colorTag);
    }
    temp_v0 = allocate_from_memory_pool(0, size, colorTag);
    if (temp_v0 == (void *)NULL) {
        func_800B7460((s32 *)((u8 *)get_stack_pointer()->unk14), size, colorTag);
    }
    return temp_v0;
}

/**
 * Reserves and returns memory from the main memory pool. Has no assert checks.
 */
MemoryPoolSlot *allocate_from_main_pool(s32 size, u32 colorTag) {
    return allocate_from_memory_pool(0, size, colorTag);
}

#ifdef NON_EQUIVALENT
MemoryPoolSlot *allocate_from_memory_pool(s32 memoryPoolIndex, s32 size, u32 colorTag) {
    MemoryPool *pool;
    MemoryPoolSlot *curSlot;
    MemoryPoolSlot *slots;
    s32 phi_a0;
    s32 phi_a2;
    s32 phi_s0;
    s32 *sp28;

    sp28 = clear_status_register_flags();
    pool = &gMemoryPools[memoryPoolIndex];
    if (pool->curNumSlots + 1 == pool->maxNumSlots) {
        set_status_register_flags(sp28);
    } else {
        if (size & 0xF) {
            size = _ALIGN16(size); // The size of the pool should be 16-byte aligned
        }
        phi_a0 = 0;
        phi_a2 = 0x7FFFFFFF; // INT_MAX
        phi_s0 = -1;
        while (phi_a0 != -1) {
            curSlot = &pool->slots[phi_a0];
            if (!curSlot->flags && curSlot->size >= size && curSlot->size < phi_a2) {
                phi_s0 = phi_a0;
                phi_a2 = curSlot->size;
            }
            phi_a0 = curSlot->nextIndex;
        }
        if (phi_s0 != -1) {
            allocate_memory_pool_slot(memoryPoolIndex, phi_s0, size, TRUE, FALSE, colorTag);
            set_status_register_flags(sp28);
            return pool->slots[phi_s0].data;
        }
        set_status_register_flags(sp28);
    }
    return (MemoryPoolSlot *)NULL;
}
#else
GLOBAL_ASM("asm/non_matchings/memory/allocate_from_memory_pool.s")
#endif

void *allocate_from_pool_containing_slots(MemoryPoolSlot *slots, s32 size) {
    s32 i;
    for (i = gNumberOfMemoryPools; i != 0; i--) {
        if (slots == gMemoryPools[i].slots) {
            return allocate_from_memory_pool(i, size, 0);
        }
    }
    return (void *)NULL;
}

#ifdef NON_EQUIVALENT
void *allocate_at_address_in_main_pool(s32 size, u8 *address, u32 colorTag) {
    s32 *sp38;
    s32 s0;
    MemoryPoolSlot *curSlot;
    MemoryPoolSlot *slots;

    sp38 = clear_status_register_flags();
    if ((gMemoryPools[0].curNumSlots + 1) == gMemoryPools[0].maxNumSlots) {
        set_status_register_flags(sp38);
    } else {
        s0 = 0;
        if (size & 0xF) {
            size = _ALIGN16(size); // The size of the pool should be 16-byte aligned
        }
        slots = gMemoryPools[0].slots;
        while (s0 != -1) {
            curSlot = &slots[s0];
            if (curSlot->flags == 0) {
                if ((address >= (u8 *)curSlot->data) && (((u8 *)curSlot->data + curSlot->size) >= (address + size))) {
                    if (address == (u8 *)curSlot->data) {
                        allocate_memory_pool_slot(0, s0, size, 1, 0, colorTag);
                        set_status_register_flags(sp38);
                        return curSlot->data;
                    } else {
                        s0 = allocate_memory_pool_slot(0, s0, address - (u8 *)curSlot->data, 0, 1, colorTag);
                        allocate_memory_pool_slot(0, s0, size, 1, 0, colorTag);
                        set_status_register_flags(sp38);
                        return slots[s0].data;
                    }
                }
            }
            s0 = curSlot->nextIndex;
        }
        set_status_register_flags(sp38);
    }
    return NULL;
}
#else
GLOBAL_ASM("asm/non_matchings/memory/allocate_at_address_in_main_pool.s")
#endif

/**
 * Sets the state of the free queue. State is either 0, 1, or 2.
 * The free queue will get flushed if the state is set to 0.
 */
void set_free_queue_state(s32 state) {
    s32 *sp2C = clear_status_register_flags();
    gFreeQueueState = state;
    if (state == 0) { // flush free queue if state is 0.
        while (gFreeQueueCount > 0) {
            free_slot_containing_address(gFreeQueue[--gFreeQueueCount].dataAddress);
        }
    }
    set_status_register_flags(sp2C);
}

/**
 * Unallocates data from the pool that contains the data. Will free immediately if the free queue
 * state is set to 0, otherwise the data will just be marked for deletion.  
 */
void free_from_memory_pool(void *data) {
    s32 *sp1C = clear_status_register_flags();
    if (gFreeQueueState == 0) {
        free_slot_containing_address(data);
    } else {
        func_80071440(data);
    }
    set_status_register_flags(sp1C);
}

/**
 * Frees all the addresses in the free queue. 
 */
void clear_free_queue(void) {
    s32 i;
    s32 *sp28;

    sp28 = clear_status_register_flags();

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

    set_status_register_flags(sp28);
}

#ifdef NON_EQUIVALENT
void free_slot_containing_address(u8 *address) {
    s32 poolIndex;
    s32 slotIndex;
    MemoryPoolSlot *slots;
    MemoryPoolSlot *slot;

    poolIndex = get_memory_pool_index_containing_address(address);
    slots = gMemoryPools[poolIndex].slots;
    for (slotIndex = 0; slotIndex != -1; slotIndex = slot->nextIndex) {
        slot = &slots[slotIndex];
        if (address == (u8 *)slot->data) {
            if (slot->flags == 1 || slot->flags == 4) {
                free_memory_pool_slot(poolIndex, slotIndex);
            }
            break;
        }
    }
}

#else
GLOBAL_ASM("asm/non_matchings/memory/free_slot_containing_address.s")
#endif

#ifdef NON_EQUIVALENT
UNUSED void func_80071314(void) {
    s32 *sp40;
    MemoryPool *pool;
    MemoryPoolSlot *slot;
    s32 poolIndex;
    s32 slotIndex;

    sp40 = clear_status_register_flags();

    for (poolIndex = gNumberOfMemoryPools; poolIndex != -1; poolIndex--) {
        pool = &gMemoryPools[poolIndex];
        for (slotIndex = 0; slotIndex != -1; slotIndex = slot->nextIndex) {
            slot = &pool->slots[slotIndex];
            if (slot->flags == 1) {
                free_memory_pool_slot(poolIndex, slotIndex);
            }
            if (slot->flags == 4 && pool->curNumSlots == 1) {
                free_memory_pool_slot(poolIndex, slotIndex);
            } else {
                set_status_register_flags(sp40);
                return;
            }
        }
    }
    set_status_register_flags(sp40);
}
#else
GLOBAL_ASM("asm/non_matchings/memory/func_80071314.s")
#endif

void func_80071440(void *dataAddress) {
    gFreeQueue[gFreeQueueCount].dataAddress = dataAddress;
    gFreeQueue[gFreeQueueCount].unk4 = gFreeQueueState;
    gFreeQueueCount++;
}

s32 func_80071478(u8 *address) {
    s32 slotIndex;
    MemoryPoolSlot *slot;
    MemoryPool *pool;
    s32 *sp18;

    sp18 = clear_status_register_flags();
    pool = &gMemoryPools[get_memory_pool_index_containing_address(address)];
    slotIndex = 0;
    while (slotIndex != -1) {
        slot = slotIndex + pool->slots; // `slot = &pool->slots[slotIndex];` does not match.
        if (address == (u8 *)slot->data) {
            if (slot->flags == 1 || slot->flags == 4) {
                slot->flags |= 2;
                set_status_register_flags(sp18);
                return 1;
            }
        }
        slotIndex = slot->nextIndex;
    }
    set_status_register_flags(sp18);
    return 0;
}

s32 func_80071538(u8 *address) {
    s32 slotIndex;
    MemoryPoolSlot *slot;
    MemoryPool *pool;
    s32 *sp18;

    sp18 = clear_status_register_flags();
    pool = &gMemoryPools[get_memory_pool_index_containing_address(address)];
    slotIndex = 0;
    while (slotIndex != -1) {
        slot = slotIndex + pool->slots; // `slot = &pool->slots[slotIndex];` does not match.
        if (address == (u8 *)slot->data) {
            if (slot->flags & 2) {
                slot->flags ^= 2;
                set_status_register_flags(sp18);
                return 1;
            }
        }
        slotIndex = slot->nextIndex;
    }
    set_status_register_flags(sp18);
    return 0;
}

/**
 * Returns the index of the memory pool containing the memory address.
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

#ifdef NON_EQUIVALENT
// Regalloc issues
void free_memory_pool_slot(s32 poolIndex, s32 slotIndex) {
    s32 nextIndex, prevIndex, tempNextIndex;
    MemoryPool *pool;
    MemoryPoolSlot *slots;
    MemoryPoolSlot *slot;
    MemoryPoolSlot *nextSlot;
    MemoryPoolSlot *prevSlot;

    pool = &gMemoryPools[poolIndex];
    slots = pool->slots;
    slot = &slots[slotIndex];
    prevIndex = slot->prevIndex;
    nextIndex = slot->nextIndex;
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

#else
GLOBAL_ASM("asm/non_matchings/memory/free_memory_pool_slot.s")
#endif

// Unused?
MemoryPoolSlot *func_80071774(s32 poolIndex) {
    return gMemoryPools[poolIndex].slots;
}

#ifdef NON_EQUIVALENT
s32 allocate_memory_pool_slot(s32 memoryPoolIndex, s32 slotIndex, s32 size, s32 slotIsTaken, s32 newSlotIsTaken, u32 colorTag) {
    s32 slotSize;
    s32 newIndex;
    s32 futureIndex;
    MemoryPoolSlot *slot;
    MemoryPoolSlot *newSlot;
    MemoryPool *pool;

    pool = &gMemoryPools[memoryPoolIndex];
    slot = &pool->slots[slotIndex];
    slotSize = slot->size;
    slot->flags = slotIsTaken;
    slot->size = size;
    slot->colorTag = colorTag;
    if (size < slotSize) {
        newIndex = pool->slots[pool->curNumSlots].index;
        pool->curNumSlots++;
        newSlot = &pool->slots[newIndex];
        newSlot->data = ((u8 *)slot->data) + size;
        newSlot->size = slotSize - size;
        newSlot->flags = newSlotIsTaken;
        futureIndex = slot->nextIndex;
        newSlot->prevIndex = slotIndex;
        newSlot->nextIndex = futureIndex;
        slot->nextIndex = newIndex;
        if (futureIndex != -1) {
            pool->slots[futureIndex].prevIndex = newIndex;
        }
        return newIndex;
    }
    return slotIndex;
}
#else
GLOBAL_ASM("asm/non_matchings/memory/allocate_memory_pool_slot.s")
#endif

/**
 * Returns the passed in address aligned to the next 16-byte boundary.
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
 */
u8 *align4(u8 *address) {
    s32 remainder = (s32)address & 0x3;
    if (remainder > 0) {
        address = (u8 *)(((s32)address - remainder) + 4);
    }
    return address;
}

GLOBAL_ASM("asm/non_matchings/memory/func_800718A4.s")

#ifdef NON_EQUIVALENT
s32 get_memory_colour_tag_count(s32 arg0) {
    s32 i, count;
    count = 0;
    for (i = 0; i < 80; i++) { // Issue with this loop
        if ((gMemoryPools[0].slots[i].flags) && (arg0 == gMemoryPools[0].slots[i].colorTag)) {
            count++;
        }
    }
    return count;
}
#else
GLOBAL_ASM("asm/non_matchings/memory/get_memory_colour_tag_count.s")
#endif

/**
 * Prints out the counts for each color tag in the main pool.
 * Unused. 
 */
void print_memory_colour_tags(void) {
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
 * Unused. 
 * See: https://tcrf.net/Diddy_Kong_Racing#Current_Colors
 */
void render_memory_colour_tags(void) {
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

#ifdef NON_EQUIVALENT
// Unused. Does nothing?
void func_80071C74(void) {
    s32 i, flags;
    MemoryPool *pool;
    MemoryPoolSlot *slot;

    for (i = 0; i <= gNumberOfMemoryPools; i++) {
        pool = &gMemoryPools[i];
        slot = &pool->slots[0];
        while (slot->nextIndex != -1) {
            if (slot->flags) { // I don't know how to get this to appear.
            }
            slot = &pool->slots[slot->nextIndex];
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/memory/func_80071C74.s")
#endif

// Unused. Does nothing?
void func_80071CE8(void) {
    s32 i;
    for (i = gNumberOfMemoryPools; i != -1; i--) {
        // Nothing here. There might've been a printf or something similar.
    }
}
