/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80070B30 */

#include "memory.h"

#include "structs.h"
#include "types.h"
#include "macros.h"

#define RAM_END 0x80400000
#define MAIN_POOL_SLOT_COUNT 1600

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
const char D_800E74C0[] = "RED %d\n";
const char D_800E74C8[] = "GREEN %d\n";
const char D_800E74D4[] = "BLUE %d\n";
const char D_800E74E0[] = "YELLOW %d\n";
const char D_800E74EC[] = "MAGENTA %d\n";
const char D_800E74F8[] = "CYAN %d\n";
const char D_800E7504[] = "WHITE %d\n";
const char D_800E7510[] = "GREY %d\n";
const char D_800E751C[] = "ORANGE %d\n\n";
                          
/*********************************/

/************ .bss ************/

/* Size: 0x8 bytes */
typedef struct unk80070BE4_8_0 {
    s16 unk0;
    s16 unk2;
    s32 unk4;
} unk80070BE4_8_0;
    
/* Size: 0x14 bytes */
typedef struct MemoryPoolSlot {
/* 0x00 */ unk80070BE4_8_0 *unk0; 
/* 0x04 */ s32 size;
/* 0x08 */ s16 isTaken;
/* 0x0A */ s16 prevIndex;
/* 0x0C */ s16 nextIndex;
/* 0x0E */ s16 index;
/* 0x10 */ s32 unk10;
} MemoryPoolSlot;

/* Size: 0x10 bytes */
typedef struct MemoryPool {
/* 0x00 */ s32 maxNumSlots;
/* 0x04 */ s32 curNumSlots;
/* 0x08 */ MemoryPoolSlot *slots;
/* 0x0C */ s32 size;
} MemoryPool;

MemoryPool gMemoryPools[4];

#ifndef _ALIGN16
    #define _ALIGN16(val) ((val) & 0xFFFFFFF0) + 0x10
#endif

s32 gNumberOfMemoryPools;
s32 D_801235C4;

/* Size: 0x8 bytes */
typedef struct unk801235C8 {
    u32 unk0;
    s8 unk4;
    u8 pad5[3];
} unk801235C8;

unk801235C8 D_801235C8[256];

s32 D_80123DC8;
s32 D_80123DCC;
s32 D_80123DD0[64];
s32 D_80123ED0[64];
s32 D_80123FD0[8];
s32 D_80123FF0[8];

extern MemoryPoolSlot D_8012D3F0;

/******************************/

/* Unknown size */
typedef struct unk800B7D10 {
    u8 pad0[0x14];
    s32 unk14;
} unk800B7D10;

unk800B7D10 *get_stack_pointer(void);
MemoryPoolSlot *allocate_from_memory_pool(s32, s32, s32);

MemoryPoolSlot *new_memory_pool(MemoryPoolSlot *arg0, s32 size, s32 arg2);
void func_800710B0(s32);
void* allocate_from_main_pool_safe(s32, s32);
s32 *func_8006F510(void);
void func_8006F53C(s32*);

void func_80071440(TextureHeader *texHeader);

/**
 * Creates the main memory pool. 
 * Starts at 0x8012D3F0. Ends at 0x80400000. Contains 1600 allocation slots.
 */
void init_main_memory_pool(void) {
    gNumberOfMemoryPools = -1;
    if(1) {
        // Create the main memory pool.
        new_memory_pool(&D_8012D3F0, RAM_END - (s32)(&D_8012D3F0), MAIN_POOL_SLOT_COUNT);
    }
    func_800710B0(2);
    D_80123DC8 = 0;
}

/**
 * Creates a new memory pool that is sectioned off the main one.
 */
MemoryPoolSlot *new_sub_memory_pool(s32 poolDataSize, s32 numSlots) {
    s32 size;
    MemoryPoolSlot *slots;
    s32 unused_2;
    s32 *temp = func_8006F510();
    MemoryPoolSlot *newPool;

    size = poolDataSize + (numSlots * sizeof(MemoryPoolSlot));
    slots = (MemoryPoolSlot *)allocate_from_main_pool_safe(size, 0xFFFFFFFF);
    newPool = new_memory_pool(slots, size, numSlots);
    func_8006F53C(temp);
    return newPool;
}

#ifdef NON_MATCHING

MemoryPoolSlot *new_memory_pool(MemoryPoolSlot *slots, s32 poolSize, s32 numSlots) {
    s32 i;
    MemoryPool *pool;
    MemoryPoolSlot *firstSlot;
    unk80070BE4_8_0 *temp3;
    
    pool = &gMemoryPools[++gNumberOfMemoryPools];
    pool->maxNumSlots = numSlots;
    pool->curNumSlots = 0;
    pool->slots = slots;
    pool->size = poolSize;
    
    for(i = 0; i < pool->maxNumSlots; i++) {
        slots[i].index = i;
    }
    
    firstSlot = pool->slots;
    temp3 = (unk80070BE4_8_0 *)&slots[numSlots];
    if((s32)temp3 & 0xF) {
        firstSlot->unk0 = (unk80070BE4_8_0 *)_ALIGN16((s32)temp3);
    } else {
        firstSlot->unk0 = temp3;
    }
    firstSlot->size = poolSize - (numSlots * sizeof(MemoryPoolSlot));
    firstSlot->isTaken = 0;
    firstSlot->prevIndex = -1;
    firstSlot->nextIndex = -1;
    
    pool->curNumSlots++;
    
    return pool->slots;
}
#else
GLOBAL_ASM("asm/non_matchings/memory/new_memory_pool.s")
#endif

void *allocate_from_main_pool_safe(s32 size, s32 mask) {
    void *temp_v0;
    if (size == 0) {
        func_800B7460(*(s32 *)((u8 *)get_stack_pointer() + 0x14), size, mask);
    }
    temp_v0 = allocate_from_memory_pool(0, size, mask);
    if (temp_v0 == (void *)NULL) {
        func_800B7460(*(s32 *)((u8 *)get_stack_pointer() + 0x14), size, mask);
    }
    return temp_v0;
}

MemoryPoolSlot *allocate_from_main_pool(s32 size, s32 arg1) {
    return allocate_from_memory_pool(0, size, arg1);
}

#ifdef NON_MATCHING
MemoryPoolSlot *allocate_from_memory_pool(s32 memoryPoolIndex, s32 size, s32 arg2) {
    MemoryPool *pool;
    MemoryPoolSlot *curSlot;
    MemoryPoolSlot *slots;
    s32 phi_a0;
    s32 phi_a2;
    s32 phi_s0;
    s32 *sp28;
    
    sp28 = func_8006F510();
    pool = &gMemoryPools[memoryPoolIndex];
    if (pool->curNumSlots + 1 == pool->maxNumSlots) {
        func_8006F53C(sp28);
    } else {
        if (size & 0xF) {
            size = _ALIGN16(size); // The size of the pool should be 16-byte aligned
        }
        phi_a0 = 0;
        phi_a2 = 0x7FFFFFFF; // INT_MAX
        phi_s0 = -1;
        while(phi_a0 != -1) {
            curSlot = &pool->slots[phi_a0];
            if (!curSlot->isTaken && curSlot->size >= size && curSlot->size < phi_a2) {
                phi_s0 = phi_a0;
                phi_a2 = curSlot->size;
            }
            phi_a0 = curSlot->nextIndex;
        }
        if (phi_s0 != -1) {
            allocate_memory_pool_slot(memoryPoolIndex, phi_s0, size, TRUE, FALSE, arg2);
            func_8006F53C(sp28);
            return pool->slots[phi_s0].unk0;
        }
        func_8006F53C(sp28);
    }
    return (MemoryPoolSlot *)NULL;
}
#else
GLOBAL_ASM("asm/non_matchings/memory/allocate_from_memory_pool.s")
#endif

void *allocate_from_pool_containing_slots(MemoryPoolSlot *slots, s32 size) {
    s32 i;
    for(i = gNumberOfMemoryPools; i != 0; i--) {
        if (slots == gMemoryPools[i].slots) {
            return allocate_from_memory_pool(i, size, 0);
        }
    }
    return (void *)NULL;
}

GLOBAL_ASM("asm/non_matchings/memory/func_80070EF8.s")

void func_800710B0(s32 arg0) {
    s32 *sp2C = func_8006F510();
    D_80123DCC = arg0;
    if (arg0 == 0) {
        while (D_80123DC8 > 0) {
            func_80071278(D_801235C8[--D_80123DC8].unk0);
        }
    }
    func_8006F53C(sp2C);
}

// This function seems to take in both TextureHeader and LevelHeader.
void func_80071140(void *data) {
    s32 *sp1C = func_8006F510();
    if (D_80123DCC == 0) {
        func_80071278(data);
    } else {
        func_80071440(data);
    }
    func_8006F53C(sp1C);
}

GLOBAL_ASM("asm/non_matchings/memory/func_80071198.s")
GLOBAL_ASM("asm/non_matchings/memory/func_80071278.s")

void func_80071440(TextureHeader *texHeader) {
    D_801235C8[D_80123DC8].unk0 = texHeader;
    D_801235C8[D_80123DC8].unk4 = D_80123DCC;
    D_80123DC8++;
}

GLOBAL_ASM("asm/non_matchings/memory/func_80071478.s")
GLOBAL_ASM("asm/non_matchings/memory/func_80071538.s")
GLOBAL_ASM("asm/non_matchings/memory/func_800715EC.s")
GLOBAL_ASM("asm/non_matchings/memory/func_8007164C.s")

#ifdef NON_MATCHING
s32 allocate_memory_pool_slot(s32 memoryPoolIndex, s32 slotIndex, s32 size, s32 slotIsTaken, s32 newSlotIsTaken, s32 arg5) {
    s32 slotSize;
    s32 newIndex;
    s32 futureIndex;
    MemoryPoolSlot *slot;
    MemoryPoolSlot *newSlot;
    MemoryPool *pool;

    pool = &gMemoryPools[memoryPoolIndex];
    slot = &pool->slots[slotIndex];
    slotSize = slot->size;
    slot->isTaken = slotIsTaken;
    slot->size = size;
    slot->unk10 = arg5;
    if (size < slotSize) {
        newIndex = pool->slots[pool->curNumSlots].index;
        pool->curNumSlots++;
        newSlot = &pool->slots[newIndex];
        newSlot->unk0 = ((u8*)slot->unk0) + size;
        newSlot->size = slotSize - size;
        newSlot->isTaken = newSlotIsTaken;
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


GLOBAL_ASM("asm/non_matchings/memory/func_80071850.s")
GLOBAL_ASM("asm/non_matchings/memory/func_80071A24.s")

#if 1
GLOBAL_ASM("asm/non_matchings/memory/func_80071D30.s")
#else
void func_8007164C(s32 arg0, s16 arg1) {
    s16 temp_a2;
    s16 temp_t0;
    s16 temp_t1;
    s16 temp_t1_2;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_t5;
    s32 temp_t5_2;
    s32 temp_v0;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a3;
    void *temp_v1;

    temp_v1 = (arg0 * 0x10) + &gMemoryPools;
    temp_v0 = temp_v1->unk8;
    temp_a3 = (arg1 * 0x14) + temp_v0;
    temp_a2 = temp_a3->unkC;
    temp_t0 = temp_a3->unkA;
    temp_a3->unk8 = (u16)0;
    if (temp_a2 != -1) {
        temp_a0 = (temp_a2 * 0x14) + temp_v0;
        if (temp_a0->unk8 == 0) {
            temp_a3->unk4 = (s32) (temp_a3->unk4 + temp_a0->unk4);
            temp_t1 = temp_a0->unkC;
            temp_a3->unkC = temp_t1;
            if (temp_t1 != -1) {
                (temp_v0 + (temp_t1 * 0x14))->unkA = arg1;
            }
            temp_t5 = temp_v1->unk4 - 1;
            temp_lo = temp_t5 * 0x14;
            temp_v1->unk4 = temp_t5;
            (temp_v0 + temp_lo)->unkE = temp_a2;
        }
    }
    if (temp_t0 != -1) {
        temp_a0_2 = (temp_t0 * 0x14) + temp_v0;
        if (temp_a0_2->unk8 == 0) {
            temp_a0_2->unk4 = (s32) (temp_a0_2->unk4 + temp_a3->unk4);
            temp_t1_2 = temp_a3->unkC;
            temp_a0_2->unkC = temp_t1_2;
            if (temp_t1_2 != -1) {
                (temp_v0 + (temp_t1_2 * 0x14))->unkA = temp_t0;
            }
            temp_t5_2 = temp_v1->unk4 - 1;
            temp_lo_2 = temp_t5_2 * 0x14;
            temp_v1->unk4 = temp_t5_2;
            (temp_v0 + temp_lo_2)->unkE = arg1;
        }
    }
}
#endif

GLOBAL_ASM("asm/non_matchings/memory/func_80071E58.s")
GLOBAL_ASM("asm/non_matchings/memory/func_80071F80.s")
GLOBAL_ASM("asm/non_matchings/memory/func_800720DC.s")







