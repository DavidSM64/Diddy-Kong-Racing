/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B7D20 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

#define OS_PIM_STACKSIZE	4096

extern u32 __osPiAccessQueueEnabled; //__osPiAccessQueueEnabled
extern OSDevMgr __osPiDevMgr;
extern u8 piThreadStack[OS_PIM_STACKSIZE];//piThreadStack
extern OSThread piThread; //piThread
extern OSMesgQueue piEventQueue; //piEventQueue
extern OSMesg piEventBuf[1]; //piEventBuf
extern OSMesgQueue piAccessQueue; //piAccessQueue
void __osDevMgrMain(void);

extern s32* D_800E3040;
extern s32* D_800E3044;
extern s32* D_800E3048;
extern s32* D_800E304C;
extern s32* D_800E3070;
extern s32* D_800E3080;
extern s32* D_800E30D0;
extern s32* D_800E30D4;
extern s32* D_800E30D8;
extern s32 D_800E30DC;
extern s32* D_800E3178;
extern s32* D_800E3184;
extern s32* D_800E3188;
extern s32* D_800E3190;
extern s32* D_800E3194;
extern s32 D_800E31A0;
extern s8 D_800E3670;
extern s16 D_800E3674;
extern s32 D_800E3678;
extern s32 D_800E3680;
extern s8 D_800E36E8;
extern u8* D_800E3760;
extern u8* D_800E3764;
extern u8* gzip_inflate_input;
extern u8* gzip_inflate_output;
extern s32 D_8012A0D8;
extern s32 D_8012A0DC;
extern s8 D_8012A788;
extern u8 D_8012A789;
extern u16 D_8012A7B6;
extern s32* D_8012A7C8;
extern s32 D_8012A7E0;

/* Size: 0x28 bytes */
typedef struct unk8012A7E8 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s8 unk10;
    s8 unk11;
    s8 unk12;
    s8 unk13;
    s8 unk14;
    s8 unk15;
    s8 unk16;
    s8 unk17;
    s8 unk18;
    s8 unk19;
    s8 unk1A;
    s8 unk1B;
    s8 unk1C;
    s8 unk1D;
    u16 unk1E;
    s16 unk20;
    s16 unk22;
    u8 pad24[0x4];
} unk8012A7E8;

extern unk8012A7E8 *D_8012A7E8[8];
extern s32 D_8012A7F0;
extern s8 D_8012A7F4;
extern s32 D_8012AAD8;
extern u32 gzip_num_bits;
extern u32 gzip_bit_buffer;

u8* func_80070C9C(s32 arg0, s32 arg1);
void func_80071140(s32* arg0);
void func_8007B2BC(s32* arg0);
void func_800C5494(s32 arg0);
void func_800C5620(s32 arg0);

void func_800B7D20(void) {
    if (D_800E3040 != NULL) {
        func_80071140(D_800E3040);
        D_800E3040 = NULL;
    }
    if (D_800E3044 != NULL) {
        func_80071140(D_800E3044);
        D_800E3044 = NULL;
    }
    if (D_800E3048 != NULL) {
        func_80071140(D_800E3048);
        D_800E3048 = NULL;
    }
    if (D_800E304C != NULL) {
        func_80071140(D_800E304C);
        D_800E304C = NULL;
    }
    if (D_800E3070 != NULL) {
        func_80071140(D_800E3070);
        D_800E3070 = NULL;
    }
    if (D_800E3080 != NULL) {
        func_80071140(D_800E3080);
        D_800E3080 = NULL;
    }
    if (D_800E30D0 != NULL) {
        func_8007B2BC(D_800E30D0);
        D_800E30D0 = NULL;
    }
    if (D_800E30D4 != NULL) {
        func_80071140(D_800E30D4);
        D_800E30D4 = NULL;
    }
    if (D_800E30D8 != NULL) {
        func_80071140(D_800E30D8);
        D_800E30D8 = NULL;
    }
    if (D_800E3178 != NULL) {
        func_80071140(D_800E3178);
        D_800E3178 = NULL;
    }
    D_800E3190 = NULL;
    D_800E3194 = NULL;
    D_800E3184 = NULL;
    D_800E3188 = NULL;
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800B7EB4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800B8134.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800B82B4.s")

void func_800B8B8C(void) {
    s32 temp_v0;
    s32 phi_v0;
    s32 i;
    
    D_800E30DC = 0;
    phi_v0 = 0;
    
    for(i = 0; i < D_8012A0D8 * D_8012A0DC; i++) {
        temp_v0 = phi_v0 + 1;
        D_800E30D4[i] = 0;
        phi_v0 = temp_v0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800B8C04.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800B9228.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800B92F4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800B97A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800B9C18.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BA288.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BA4B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BA8E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BB2F4.s")

void func_800BBE08(void);
void func_800BBF78(s32 arg0);

void func_800BBDDC(s32 arg0) {
    func_800BBE08();
    func_800BBF78(arg0);
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BBE08.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BBF78.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BC6C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BCC70.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BDC80.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BE654.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BEEB4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BEFC4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BF3E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BF524.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BF634.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BFE98.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BFFDC.s")

void func_800C0170(void) {
    D_800E31A0 = 1;
}

void func_800C0180(void) {
    D_800E31A0 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C018C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C01D8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C0494.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C05C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C0724.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C0780.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C0834.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C0A08.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C0B00.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C1130.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C13E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C14DC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C15D4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C1EE8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C2274.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C23F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C2548.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C2640.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C27A0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C28E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C29F0.s")

void func_800C2AB4(void) {
    func_80071140(D_8012A7C8);
    D_8012A7B6 = (u16)0;
    func_800C5620(6);
    func_800C5494(6);
}


void func_800C2AF4(s32 arg0) {
    D_800E3680 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C2B00.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C2D6C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C2F1C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C3048.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C30CC.s")

void func_800C3140(s32 arg0) {
    D_800E3674 = arg0;
}

void func_800C314C(void) {
    D_800E3678 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C3158.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C31EC.s")

s32 func_800C3400(void) {
    s32 result = 0;
    if (D_800E3670 != 0) {
        if (D_8012A789 != 0) {
            result = 1;
            if (D_8012A788 != 0) {
                result = 2;
            }
        }
    }
    return result;
}


GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C3440.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C3564.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C38B4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C3C00.s")

void func_800C4164(s32 arg0) {
    D_8012A7F0 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C4170.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C422C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C42EC.s")

void func_800C4384(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    (*D_8012A7E8)[0].unk14 = arg0;
    (*D_8012A7E8)[0].unk15 = arg1;
    (*D_8012A7E8)[0].unk16 = arg2;
    (*D_8012A7E8)[0].unk17 = arg3;
    (*D_8012A7E8)[0].unk1C = arg4;
}

void func_800C43CC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    (*D_8012A7E8)[0].unk18 = arg0;
    (*D_8012A7E8)[0].unk19 = arg1;
    (*D_8012A7E8)[0].unk1A = arg2;
    (*D_8012A7E8)[0].unk1B = arg3;
}

void func_800C45A4(s32, unk8012A7E8*, s32, s32, f32);

// Unused?
void func_800C4404(s32 arg0, s32 arg1, s32 arg2) {
    func_800C45A4(arg0, *D_8012A7E8, arg1, arg2, 1.0f);
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C4440.s")
#else
// This function is OK
void func_800C4440(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    unk8012A7E8 *temp = &(*D_8012A7E8)[0];
    temp->unk0 = (arg1 == -0x8000) ? temp->unkC >> 1 : arg1;
    temp->unk2 = (arg2 == -0x8000) ? temp->unkE >> 1 : arg2;
    func_800C45A4(arg0, temp, arg3, arg4, 1.0f);
}

// Unused?
void func_800C44C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg1 >= 0 && arg1 < 8) {
        unk8012A7E8 *temp = &(*D_8012A7E8)[arg1]; // Issue with temp
        func_800C45A4(arg0, temp, arg2, arg3, 1.0f);
    }
}

// Unused?
void func_800C4510(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    if (arg1 >= 0 && arg1 < 8) {
        unk8012A7E8 *temp = &(*D_8012A7E8)[arg1]; // Issue with temp
        temp->unk0 = (arg2 == -0x8000) ? temp->unkC >> 1 : arg2;
        temp->unk2 = (arg3 == -0x8000) ? temp->unkE >> 1 : arg3;
        func_800C45A4(arg0, temp, arg4, arg5, 1.0f);
    }
}
#endif

// Has a jump table
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C45A4.s")

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C4DA0.s")

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C4EDC.s")
#else
void func_800C4EDC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0 > 0 && arg0 < 8) {
        // How is temp supposed to be setup for all of these functions? This is driving me nuts.
        unk8012A7E8 *temp = &(*D_8012A7E8)[arg0]; // Issue with temp
        temp->unk0 = 0;
        temp->unk2 = 0;
        if (arg1 < arg3) {
            temp->unk4 = (s16) arg1;
            temp->unk8 = (s16) arg3;
        } else {
            temp->unk8 = (s16) arg1;
            temp->unk4 = (s16) arg3;
        }
        if (arg2 < arg4) {
            temp->unk6 = (s16) arg2;
            temp->unkA = (s16) arg4;
        } else {
            temp->unkA = (s16) arg2;
            temp->unk6 = (s16) arg4;
        }
        temp->unkC = (temp->unk8 - temp->unk4) + 1;
        temp->unkE = (temp->unkA - temp->unk6) + 1;
    }
}
#endif

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C4F7C.s")
#else
void func_800C4F7C(s32 arg0, s32 arg1) {
    if (arg0 >= 0 && arg0 < 8) {
        unk8012A7E8 *temp = &(*D_8012A7E8)[arg0]; // Issue with temp
        if (arg1 < D_8012A7E0) {
            temp->unk1D = arg1;
        }
    }
}
#endif

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C4FBC.s")
#else
void func_800C4FBC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0 > 0 && arg0 < 8) {
        unk8012A7E8 *temp = &(*D_8012A7E8[arg0]); // Issue with temp
        temp->unk10 = arg1;
        temp->unk11 = arg2;
        temp->unk12 = arg3;
        temp->unk13 = arg4;
    }
}
#endif

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C5000.s")
#else
void func_800C5000(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    unk8012A7E8 *temp;
    if (arg0 <= 0 || arg0 >= 8) {
        return;
    }
    temp = &(*D_8012A7E8)[arg0]; // Issue with temp
    temp->unk14 = arg1;
    temp->unk15 = arg2;
    temp->unk16 = arg3;
    temp->unk17 = arg4;
    temp->unk1C = arg5;
}
#endif

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C5050.s")
#else 
void func_800C5050(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    unk8012A7E8 *temp;
    if (arg0 <= 0 || arg0 >= 8) {
        return;
    }
    temp = &(*D_8012A7E8)[arg0]; // Issue with temp
    temp->unk18 = arg1;
    temp->unk19 = arg2;
    temp->unk1A = arg3;
    temp->unk1B = arg4;
}

// Unused?
void func_800C5094(s32 arg0, s32 arg1, s32 arg2) {
    unk8012A7E8 *temp;
    if (arg0 <= 0 || arg0 >= 8) {
        return;
    }
    temp = &(*D_8012A7E8)[arg0]; // Issue with temp
    temp->unk20 += arg1;
    temp->unk22 += arg2;
}

// Unused?
void func_800C50D8(s32 arg0) {
    unk8012A7E8 *temp;
    if (arg0 <= 0 || arg0 >= 8) {
        return;
    }
    temp = &(*D_8012A7E8)[arg0]; // Issue with temp
    temp->unk20 = 0;
    temp->unk22 = 0;
}

// Unused?
// This function is OK
void func_800C510C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_800C5168(arg0, (*D_8012A7E8)[arg0].unk0, (*D_8012A7E8)[arg0].unk2, arg1, arg2, arg3);
}
#endif

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C5168.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C5494.s")

void func_800C55F4(s32 arg0) {
    (*D_8012A7E8)[arg0].unk1E |= 0x8000;
}

void func_800C5620(s32 arg0) {
    (*D_8012A7E8)[arg0].unk1E &= 0x7FFF;
}

// Unused?
void func_800C564C(s32 arg0) {
    (*D_8012A7E8)[arg0].unk1E |= 0x0001;
}

// Unused?
void func_800C5678(s32 arg0) {
    (*D_8012A7E8)[arg0].unk1E &= 0xFFFE;
}

// Unused?
void func_800C56A4(s32 arg0) {
    (*D_8012A7E8)[arg0].unk1E |= 0x4000;
}

void func_800C56D0(s32 arg0) {
    (*D_8012A7E8)[arg0].unk1E &= 0xBFFF;
}

void func_800C56FC(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;

    if (D_800E36E8 != 0) {
        D_8012A7F4--;
        if (D_8012A7F4 == 0) {
            func_8009E9A8();
            D_800E36E8 = 0;
        }
    }
    
    for(i = 1; i < 8; i++) {
        if ((*D_8012A7E8)[i].unk1E & 0x8000) {
            if ((*D_8012A7E8)[i].unk1E & 0x4000) {
                func_800C5B58(arg0, arg1, arg2, i);
            } else {
                func_800C5B58(arg0, 0, 0, i);
            }
        }
    }
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C580C.s")
#else
    
extern s32 D_800E36EC[9]; // Descending powers of 10; starting from 1000000.

// sprintf like function, but only for decimal integers (%d).
void func_800C580C(char** outString, s32 number) {
    char digit;
    s32 i;
    s32 hasDigit; // boolean
    s32 div;
    
    // Check for a negative number
    if (number < 0) { 
        **outString = '-';
        number = -number;
        (*outString)++;
    }
    
    // Loop through digit places.
    for(i = 0; i < 9; i++){
        hasDigit = 0;
        digit = '0';
        if (number >= D_800E36EC[i]) {
            div = number / D_800E36EC[i];
            hasDigit = 1;
            digit = '0' + div;
            number -= div * D_800E36EC[i];
        }
        if (hasDigit) {
            **outString = digit;
            (*outString)++;
        }
    }

    // One's digit place
    **outString = '0' + number;
    (*outString)++;
}
#endif

//GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C5AA0.s")
void func_800C5AA0(Gfx **dlist, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u32 temp_v0 = func_8007A520();
    if (arg3 >= 0 && arg1 < (temp_v0 & 0xFFFF) && arg4 >= 0 && arg2 < (temp_v0 >> 16)) {
        if (arg1 < 0) {
            arg1 = 0;
        }
        if (arg2 < 0) {
            arg2 = 0;
        }
        gDPFillRectangle((*dlist)++, arg1, arg2, arg3, arg4);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C5B58.s")

void func_800C580C(char**, s32);

void func_800C5F60(unsigned char *input, char *output, s32 number) {
    while (*input != '\0') {
        if ('~' == *input) { // ~ is equivalent to a %d.
            // output the number as part of the string
            func_800C580C(&output, number);
            input++;
        } else {
            *output = *input;
            input++;
            output++;
        }
    }
    *output = '\0'; // null terminator
}

void osCreatePiManager(OSPri pri, OSMesgQueue *cmdQ, OSMesg *cmdBuf, s32 cmdMsgCnt)
{
	u32 savedMask;
	OSPri oldPri;
	OSPri myPri;
	if (!__osPiDevMgr.active)
	{
		osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
		osCreateMesgQueue(&piEventQueue, (OSMesg*)&piEventBuf, 1);
		if (!__osPiAccessQueueEnabled)
			__osPiCreateAccessQueue();
		osSetEventMesg(OS_EVENT_PI, &piEventQueue, (OSMesg)0x22222222);
		oldPri = -1;
		myPri = osGetThreadPri(NULL);
		if (myPri < pri)
		{
			oldPri = myPri;
			osSetThreadPri(NULL, pri);
		}
		savedMask = __osDisableInt();
		__osPiDevMgr.active = 1;
		__osPiDevMgr.thread = &piThread;
		__osPiDevMgr.cmdQueue = cmdQ;
		__osPiDevMgr.evtQueue = &piEventQueue;
		__osPiDevMgr.acsQueue = &piAccessQueue;
		__osPiDevMgr.dma = osPiRawStartDma;
        __osPiDevMgr.edma = osEPiRawStartDma;

		osCreateThread(&piThread, 0, __osDevMgrMain, &__osPiDevMgr, &piThreadStack[OS_PIM_STACKSIZE], pri);
		osStartThread(&piThread);
		__osRestoreInt(savedMask);
		if (oldPri != -1)
		{
			osSetThreadPri(NULL, oldPri);
		}
	}
}


void func_800C6170(void) {
    D_800E3760 = func_80070C9C(0x2800, 0xFF);
    D_800E3764 = func_80070C9C(0x10, 0xFF);
}

// Returns the little-endian value from a byte array.
s32 byteswap32(u8* arg0) {
    s32 value;
    value = *arg0++;
    value |= (*arg0++ << 8);
    value |= (*arg0++ << 16);
    value |= (*arg0++ << 24);
    return value;
}

s32 func_800C61DC(s32 arg0, s32 arg1) {
    func_80076E68(arg0, D_800E3764, arg1, 8);
    return byteswap32(D_800E3764);
}

s32 gzip_inflate_block(void);

u8* func_800C6218(u8* arg0, u8* arg1) {
    gzip_inflate_input = arg0 + 5; // The compression header is 5 bytes. 
    gzip_inflate_output = arg1;
    gzip_num_bits = 0;
    gzip_bit_buffer = 0;
    while(gzip_inflate_block() != 0) {} // Keep calling gzip_inflate_block() until it returns 0.
    return arg1;
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/gzip_huft_build.s")
