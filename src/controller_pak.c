/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80072250 */

#include "controller_pak.h"
#include "memory.h"
#include "PR/pfs.h"
#include "PR/os_cont.h"
#include "macros.h"
#include "structs.h"
#include "camera.h"
#include "unknown_00BC20.h"

/************ .data ************/

s32 *D_800DE440 = 0;

u8 gN64FontCodes[68] = "\0               0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#'*+,-./:=?@";

s32 D_800DE488 = 0; // Currently unknown, might be a different type. 
s32 D_800DE48C = 0;

/*******************************/

/************ .rodata ************/

const char D_800E7590[] = "Region = %d	 loc = %x	 size = %x\t";
const char D_800E75B4[] = "FREE";
const char D_800E75BC[] = "ALLOCATED";
const char D_800E75C8[] = "ALLOCATED,FIXED";
const char D_800E75D8[] = "\n";
const char D_800E75DC[] = "\n";
const char D_800E75E0[] = "Region number = %d\t";
const char D_800E75F4[] = "maxSlots = %d\t";
const char D_800E7604[] = "slotsUsed = %d\t";
const char D_800E7614[] = "loc = %x\t";
const char D_800E7620[] = "size = %x\n";
const char D_800E762C[] = "\n";

const char D_800E7630[] = "DKRACING-ADV";
const char D_800E7640[] = "DKRACING-ADV";
const char D_800E7650[] = "DKRACING-TIMES";
const char D_800E7660[] = "DKRACING-TIMES";
const char D_800E7670[] = "DKRACING-ADV";
const char D_800E7680[] = "DKRACING-ADV";
const char D_800E7690[] = "DKRACING-TIMES";
const char D_800E76A0[] = "DKRACING-TIMES";

const char D_800E76B0[] = "WARNING : No Eprom\n";
const char D_800E76C4[] = "WARNING : No Eprom\n";
const char D_800E76D8[] = "WARNING : No Eprom\n";
const char D_800E76EC[] = "WARNING : No Eprom\n";
const char D_800E7700[] = "WARNING : No Eprom\n";
const char D_800E7714[] = "WARNING : No Eprom\n";
const char D_800E7728[] = "WARNING : No Eprom\n";

const char D_800E773C[] = "DKRACING-GHOSTS"; // Used in func_80074B34
const   u8 D_800E774C[4] = { 0, 0, 0, 0 }; // Used in func_80074B34, but I'm confused to what this is for. 
const char D_800E7750[] = "warning: corrupt ghost\n";

/*********************************/

/************ .bss ************/

OSMesgQueue *D_80124010;
s32 D_80124014;

OSPfs pfs[MAXCONTROLLERS];

s32 D_801241B8[10];
s32 D_801241E0;
u8 D_801241E4;
u8 D_801241E5;
u8 D_801241E6;
u8 D_801241E7;
s32 D_801241E8;
s32 D_801241EC;
s32 D_801241F0;
s32 D_801241F4;

/*******************************/

u8 func_80072250(s32 arg0) {
    if ((arg0 == 0 || arg0 == 1) && func_8000E158()) {
        arg0 = 1 - arg0;
    }
    return func_8006A4F8(arg0);
}

void func_80072298(u8 arg0) {
    D_801241E4 = arg0;
    if (arg0 != 0) {
        D_801241E8 = 0x79;
        D_801241E6 = 0xF;
        return;
    }
    func_80072708();
}

#ifdef NON_MATCHING
// Unused. Has regalloc issues.
s32 func_800722E8(s16 arg0) {
    if (arg0 < 0 || arg0 >= 4) {
        return 0;
    }
    return D_801241E5 & ((1 << func_80072250(arg0)) & 0xFF);
}
#else
GLOBAL_ASM("asm/non_matchings/controller_pak/func_800722E8.s")
#endif

GLOBAL_ASM("asm/non_matchings/controller_pak/func_80072348.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_80072424.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_80072578.s")

void func_80072708(void) {
    D_800DE48C = 3;
}

GLOBAL_ASM("asm/non_matchings/controller_pak/func_80072718.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_80072C54.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_80072E28.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_8007306C.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_800732E8.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_80073588.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_800738A4.s")

s32 get_s32_256(void) {
    return 256;
}

s32 get_s32_512(void) {
    return 512;
}

GLOBAL_ASM("asm/non_matchings/controller_pak/func_80073C5C.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_80073E1C.s")

s32 func_80073F5C(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 sp30; //Possible epcInfo struct
    u8 *sp2C;
    s32 phi_v1;
    s32 size;

    size = get_s32_256(); // 256 bytes
    sp2C = allocate_from_main_pool_safe(size, COLOR_TAG_WHITE);
    *((s32*)sp2C) = 0x47414D44; //'GAMD';
    func_800732E8(arg1, sp2C + 4);
    phi_v1 = func_80073C5C(arg0, 3, &sp30);
    if (phi_v1 == 0) {
        phi_v1 = func_800766D4(arg0, -1, &D_800E7680, &sp30, sp2C, size);
    }
    free_from_memory_pool(sp2C);
    if (phi_v1 != 0) {
        phi_v1 |= (arg0 << 0x1E);
    }
    return phi_v1;
}

GLOBAL_ASM("asm/non_matchings/controller_pak/func_80074018.s")

s32 func_80074148(s32 arg0, Settings *arg1) {
    u8 *sp2C;
    s32 phi_v1;
    s32 sp24;
    s32 temp_v0;
    s32 sp30; //Possible epcInfo struct

    sp24 = get_s32_512(); // 512 bytes
    sp2C = allocate_from_main_pool_safe(sp24, COLOR_TAG_WHITE);
    *((s32*)sp2C) = 0x54494D44; // TIMD
    func_800738A4(arg1, sp2C + 4);
    phi_v1 = func_80073C5C(arg0, 4, &sp30);
    if (phi_v1 == 0) {
        phi_v1 = func_800766D4(arg0, -1, &D_800E76A0, &sp30, sp2C, sp24);
    }
    free_from_memory_pool(sp2C);
    if (phi_v1 != 0) {
        phi_v1 |= (arg0 << 0x1E);
    }
    return phi_v1;
}

GLOBAL_ASM("asm/non_matchings/controller_pak/func_80074204.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_8007431C.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_800744DC.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_800745D0.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_800746F0.s")

GLOBAL_ASM("asm/non_matchings/controller_pak/func_8007480C.s")

GLOBAL_ASM("asm/non_matchings/controller_pak/func_80074874.s")

#ifdef NON_MATCHING
s64 func_8007480C(u64 arg0);
// regalloc issues
s32 func_8007497C(u64 *arg0) {
    if (osEepromProbe(func_8006A100()) == 0) {
        return -1;
    }
    *arg0 <<= 8;
    *arg0 >>= 8;
    *arg0 |= (s64)((s32)func_8007480C(*arg0)) << 56;
    if (func_8006EAC0() == 0) {
        osEepromWrite(func_8006A100(), 0xF, (u8*)arg0);
    }
    return 1;
}
#else
GLOBAL_ASM("asm/non_matchings/controller_pak/func_8007497C.s")
#endif

#ifdef NON_MATCHING
// regalloc issues
s16 func_80074A4C(GhostHeader *ghostHeader) {
    s16 i;
    s16 len;
    s16 sum;
    s32 temp;
    
    sum = 0;
    len = (ghostHeader->nodeCount * sizeof(GhostDataFrame)) + sizeof(GhostHeader);
    for(i = sizeof(GhostHeader); i < len; i++) {
        sum += ((u8*)ghostHeader)[i];
    }
    return sum;
}
#else
GLOBAL_ASM("asm/non_matchings/controller_pak/func_80074A4C.s")
#endif

void func_80074AA8(GhostHeader *ghostHeader, s16 characterID, s16 time, s16 nodeCount, u8 *dest) {
    ghostHeader->checksum = 0;
    ghostHeader->characterID = characterID;
    ghostHeader->unk3 = 0;
    ghostHeader->time = time;
    ghostHeader->nodeCount = nodeCount;
    bcopy(dest, (u8*)ghostHeader + 8, nodeCount * sizeof(GhostDataFrame));
    ghostHeader->checksum = func_80074A4C(ghostHeader);
}

#ifdef NON_MATCHING
s32 func_80074B1C(void) {
    return (0x1100 * 6) + 0x100; // -O2 optimizes this down to "return 0x6700;".
}
#else
GLOBAL_ASM("asm/non_matchings/controller_pak/func_80074B1C.s")
#endif

GLOBAL_ASM("asm/non_matchings/controller_pak/func_80074B34.s")

GLOBAL_ASM("asm/non_matchings/controller_pak/func_80074EB8.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_80075000.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_800753D8.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_800756D4.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_800758DC.s")

s32 func_80075AEC(s32 controllerIndex) {
    osContStartReadData(D_80124010);
    return 0;
}

GLOBAL_ASM("asm/non_matchings/controller_pak/func_80075B18.s")

s32 func_80075D38(s32 controllerIndex) {
    s32 phi_v1;
    s32 temp_v0 = func_800758DC();
    if (temp_v0 == 0 || temp_v0 == 2) {
        temp_v0 = osPfsChecker(&pfs[controllerIndex]);
        if (temp_v0 == 0) {
            phi_v1 = 0;
        } else if (temp_v0 == 2) {
            phi_v1 = 5;
        } else {
            phi_v1 = 2;
        }
    } else {
        phi_v1 = 0;
    }
    func_80075AEC(controllerIndex);
    return phi_v1;
}

s32 func_80075DC4(s32 controllerIndex) {
    s32 phi_v1;
    s32 temp_v0 = func_800758DC();
    if (temp_v0 == 0 || temp_v0 == 2 || temp_v0 == 3) {
        temp_v0 = osPfsReFormat(&pfs[controllerIndex], D_80124010, controllerIndex);
        if (temp_v0 == 0) {
            phi_v1 = 0;
        } else if (temp_v0 == 2) {
            phi_v1 = 5;
        } else {
            phi_v1 = 2;
        }
    } else {
        phi_v1 = 0;
    }
    func_80075AEC(controllerIndex);
    return phi_v1;
}

GLOBAL_ASM("asm/non_matchings/controller_pak/func_80075E60.s")

void func_80076164(void) {
    if (D_800DE440 != 0) {
        free_from_memory_pool(D_800DE440);
    }
    D_800DE440 = 0;
}

s32 func_80076194(s32 controllerIndex, s32 *arg1, s32 *arg2) {
    s32 phi_v1;
    s32 sp28;
    s32 sp24;
    s32 sp20;

    phi_v1 = func_800758DC();
    if (phi_v1 == 0) {
        if (arg1 != NULL) {
            phi_v1 = osPfsFreeBlocks(&pfs[controllerIndex], &sp28);
            if (phi_v1 != 0) {
                func_80075AEC(controllerIndex);
                return (controllerIndex << 0x1E) | 9;
            }
            *arg1 = sp28;
        }
        if (arg2 != NULL) {
            phi_v1 = osPfsNumFiles(&pfs[controllerIndex], &sp24, &sp20);
            if (phi_v1 != 0) {
                func_80075AEC(controllerIndex);
                return (controllerIndex << 0x1E) | 9;
            }
            if (sp20 >= 0x10) {
                *arg2 = 0;
            } else {
                *arg2 = 0x10 - sp20;
            }
        }
    } else {
        phi_v1 |= controllerIndex << 0x1E;
    }
    func_80075AEC(controllerIndex);
    return phi_v1;
}

#ifdef NON_MATCHING
// regalloc & stack issues
// Rename delete_file_from_controller_pak?
s32 func_800762C8(s32 controllerIndex, s32 fileNum) {
    s16 sp3E;
    s16 sp3A;
    s32 sp30;
    s32 sp34;
    u16 sp38;
    s32 temp_v0;
    OSPfs *temp_a0;

    temp_v0 = func_800758DC();
    if (temp_v0 != 0) {
        func_80075AEC(controllerIndex);
        return (controllerIndex << 0x1E) | temp_v0;
    }
    temp_v0 = controllerIndex << 0x1E;
    temp_a0 = &pfs[controllerIndex];
    temp_v0 |= 9;
    if (osPfsFileState(temp_a0, fileNum, &sp30) == 0) {
        if (osPfsDeleteFile(temp_a0, sp38, sp34, &sp3E, &sp3A) == 0) {
            temp_v0 = 0;
        }
    }
    func_80075AEC(controllerIndex);
    return temp_v0;
}

#else
GLOBAL_ASM("asm/non_matchings/controller_pak/func_800762C8.s")
#endif

GLOBAL_ASM("asm/non_matchings/controller_pak/func_80076388.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_800764E8.s")

s32 read_data_from_controller_pak(s32 controllerIndex, s32 fileNum, u8 *data, s32 dataLength) {
    s32 readResult = osPfsReadWriteFile(&pfs[controllerIndex], fileNum, PFS_READ, 0, dataLength, data);
    //Successful read
    if (readResult == 0) {
        return 0;
    }
    if ((readResult == PFS_ERR_NOPACK) || (readResult == PFS_ERR_DEVICE)) {
        return 1;
    }
    if (readResult == PFS_ERR_INCONSISTENT) {
        return 2;
    }
    if (readResult == PFS_ERR_ID_FATAL) {
        return 3;
    }
    if (readResult == PFS_ERR_INVALID) {
        return 5;
    }
    return 9;
}

GLOBAL_ASM("asm/non_matchings/controller_pak/func_800766D4.s")

#ifdef NON_MATCHING
// Stack issues
s32 func_80076924(s32 controllerIndex, s32 arg1, s32 *arg2) {
    s32 sp18;

    *arg2 = 0;
    if (!osPfsFileState(&pfs[controllerIndex], arg1, &sp18)) {
        *arg2 = sp18;
        return 0;
    }
    return 9;
}

#else
GLOBAL_ASM("asm/non_matchings/controller_pak/func_80076924.s")
#endif

GLOBAL_ASM("asm/non_matchings/controller_pak/func_8007698C.s")
GLOBAL_ASM("asm/non_matchings/controller_pak/func_80076A38.s")

s32 func_80076AF4(s32 controllerIndex, s32 fileNum) {
    s32 *data;
    s32 pad;
    s32 ret;

    ret = 6;
    data = allocate_from_main_pool_safe(0x100, COLOR_TAG_BLACK);
    if (read_data_from_controller_pak(controllerIndex, fileNum, (u8 *)data, 0x100) == 0) {
        switch(*data) {
            case 0x47414D44: //'GAMD': // Game Data?
                ret = 3;
                break;
            case 0x54494D44: //'TIMD': // Time Data?
                ret = 4;
                break;
            case 0x47485353: //'GHSS': // Ghosts?
                ret = 5;
                break;
            default:
                ret = 6;
                break;
        }
    }
    free_from_memory_pool(data);
    return ret;
}
