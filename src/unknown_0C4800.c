/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C3C00 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

/************ .data ************/

// Fast3D (F3DDKR) display list
u32 D_800E3690[] = {
    0xE7000000, 0x00000000, 
    0xBA001001, 0x00000000, 
    0xBA000E02, 0x00000000, 
    0xB9000002, 0x00000000, 
    0xB6000000, 0x00010001, 
    0xE7000000, 0x00000000, 
    0xB8000000, 0x00000000, 
    0xFC5616AC, 0x112CFE7F, 
    0xEF000C0F, 0x00504240, 
    0xFCFFFFFF, 0xFFFEFB7D, 
    0xEF000C0F, 0x00504240
};

s8 D_800E36E8 = 0;

// Descending powers of 10
s32 D_800E36EC[9] = {
    1000000000, 100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10
}; 

s8 D_800E3710[48] = {
    4, 0, 0, 0, 1, 2, 0, 1, 0, 2, 1, 0, 2, 0, 4, 0, 
    0, 4, 1, -4, 1, 1, -4, 1, -2, 2, 1, -2, 1, -1, 4, 1, 
    -1, 1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

OSDevMgr __osPiDevMgr = { 0, NULL, NULL, NULL, NULL, NULL, NULL };

s32 pad800E375C = 0; // File boundary?

u8* D_800E3760 = NULL;
u8* D_800E3764 = NULL;
u8* gzip_inflate_input = NULL;
u8* gzip_inflate_output = NULL;

/*******************************/

/************ .bss ************/

#define OS_PIM_STACKSIZE	4096
u8 piThreadStack[256];//piThreadStack[OS_PIM_STACKSIZE];

s32 D_80129BB0[256];
s32 D_80129FB0[3];
s32 D_80129FBC;
s32 D_80129FC0;
s32 D_80129FC4;
s32 D_80129FC8;
s32 D_80129FCC;
s32 D_80129FD0[4];
s32 D_80129FE0[2];
s32 D_80129FE8;
s32 D_80129FF0[6];
s32 D_8012A008;
s32 D_8012A00C;
s32 D_8012A010;
s32 D_8012A014;
s32 D_8012A018;
s32 D_8012A01C;
s32 D_8012A020[2];
s32 D_8012A028[20];
s32 D_8012A078;
s32 D_8012A07C;
s32 D_8012A080;
s32 D_8012A084;
s32 D_8012A088;
s32 D_8012A08C;
s32 D_8012A090;
s32 D_8012A094;
s32 D_8012A098;
s32 D_8012A09C;
s32 D_8012A0A0;
s32 D_8012A0A4;
s32 D_8012A0A8;
s32 D_8012A0AC;
s32 D_8012A0B0;
s32 D_8012A0B4;
s32 D_8012A0B8;
s32 D_8012A0BC;
s32 D_8012A0C0;
s32 D_8012A0C4;
s32 D_8012A0C8;
s32 D_8012A0CC;
s32 D_8012A0D0;
s32 D_8012A0D4;
s32 D_8012A0D8;
s32 D_8012A0DC;
s32 D_8012A0E0;
s32 D_8012A0E8[64];
s32 D_8012A1E8[256];
s32 D_8012A5E8[3];
s32 D_8012A5F4;
s32 D_8012A5F8;
s32 D_8012A5FC;
s32 D_8012A600[72];
s32 D_8012A720;
s32 D_8012A724;
s32 D_8012A728[2];
s32 D_8012A730;
s8 D_8012A734;
s8 D_8012A735;
s8 D_8012A736;
s8 D_8012A737;
s32 D_8012A738;
s32 D_8012A73C;
s32 D_8012A740;
s32 D_8012A744;
s32 D_8012A748;
s32 D_8012A74C;
s32 D_8012A750;
s32 D_8012A754;
s32 D_8012A758;
s32 D_8012A75C;
s32 D_8012A760;
s32 D_8012A764;
s32 D_8012A768;
s32 D_8012A76C;
s32 D_8012A770;
s32 D_8012A774;
s32 D_8012A778;
s32 D_8012A77C;
s32 D_8012A780;
s8 D_8012A784;
s8 D_8012A785;
s8 D_8012A786;
s8 D_8012A787;
s8 D_8012A788;
s8 D_8012A789;
s8 D_8012A78A;
s16 D_8012A78C;
s16 D_8012A78E;
s32 D_8012A790[2];
s32 D_8012A798;
s32 D_8012A79C;
s32 D_8012A7A0;
s32 D_8012A7A4;
s16 D_8012A7A8;
s16 D_8012A7AA;
s16 D_8012A7AC;
s16 D_8012A7AE;
s16 D_8012A7B0;
s16 D_8012A7B2;
s16 D_8012A7B4;
s16 D_8012A7B6;
s16 D_8012A7B8;
s16 D_8012A7BA;
s32 D_8012A7C0[2];
s32 D_8012A7C8;
s32 D_8012A7CC;
s32 D_8012A7D0;
s32 D_8012A7D4;
s32 D_8012A7D8;
s32 D_8012A7DC;
s32 D_8012A7E0;
s32 D_8012A7E4;

/* Size: 0x28 bytes */
typedef struct unk8012A7E8_24 {
    u8 unk00;
    u8 unk01;
    u8 pad02[0x1A];
    struct unk8012A7E8_24* unk1C;
} unk8012A7E8_24;

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
    unk8012A7E8_24 *unk24;
} unk8012A7E8;

unk8012A7E8 (*D_8012A7E8)[1];
s32 D_8012A7EC;
s32 D_8012A7F0;
s8 D_8012A7F4;
s32 D_8012A7F8;
s32 D_8012A7FC;
OSThread piThread; //piThread
s32 D_8012A9B0[64];
OSMesgQueue piEventQueue; //piEventQueue
OSMesg piEventBuf[2]; //piEventBuf
u32 gzip_bit_buffer;
u32 gzip_num_bits;
s32 D_8012AAD8;

/******************************/

extern OSMesgQueue piAccessQueue; //piAccessQueue
extern u32 __osPiAccessQueueEnabled; //__osPiAccessQueueEnabled
extern OSDevMgr __osPiDevMgr;
void __osDevMgrMain(void);

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C3C00.s")
#else

extern u32* D_8012A7E4;
void func_800C3C00(void){
    s32 i;
    D_8012A7E4 = func_80076C58(44);
    D_8012A7E0 = *(D_8012A7E4++);
    for(i = 0; i< D_8012A7E0; i++){
        D_8012A7E0[]
    }
}
#endif


void func_800C4164(s32 arg0) {
    D_8012A7F0 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C4170.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C422C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/set_text_font.s")

void set_text_color(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    (*D_8012A7E8)[0].unk14 = arg0;
    (*D_8012A7E8)[0].unk15 = arg1;
    (*D_8012A7E8)[0].unk16 = arg2;
    (*D_8012A7E8)[0].unk17 = arg3;
    (*D_8012A7E8)[0].unk1C = arg4;
}

void set_text_background_color(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
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

void draw_text(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    unk8012A7E8 *temp = &(*D_8012A7E8)[0];
    temp->unk0 = (arg1 == -0x8000) ? temp->unkC >> 1 : arg1;
    temp->unk2 = (arg2 == -0x8000) ? temp->unkE >> 1 : arg2;
    func_800C45A4(arg0, temp, arg3, arg4, 1.0f);
}

void func_800C44C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg1 >= 0) {
        if(arg1 < 8){
            unk8012A7E8 *temp = &D_8012A7E8[arg1];
            func_800C45A4(arg0, temp, arg2, arg3, 1.0f);
        }
    }
}

void func_800C4510(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    if (arg1 >= 0 && arg1 < 8) {
        unk8012A7E8 *temp = &D_8012A7E8[arg1];
        temp->unk0 = (arg2 == -0x8000) ? temp->unkC >> 1 : arg2;
        temp->unk2 = (arg3 == -0x8000) ? temp->unkE >> 1 : arg3;
        func_800C45A4(arg0, temp, arg4, arg5, 1.0f);
    }
}

// Has a jump table
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C45A4.s")

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C4DA0.s")

void func_800C4EDC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0 > 0 && arg0 < 8) {
        // How is temp supposed to be setup for all of these functions? This is driving me nuts.
        unk8012A7E8 *temp = &D_8012A7E8[arg0]; // Issue with temp
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

void func_800C4F7C(s32 arg0, s32 arg1) {
    if (arg0 >= 0 && arg0 < 8) {
        unk8012A7E8 *temp = &D_8012A7E8[arg0];
        if (arg1 < D_8012A7E0) {
            temp->unk1D = arg1;
        }
    }
}


void func_800C4FBC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0 > 0 && arg0 < 8) {
        unk8012A7E8 *temp = &D_8012A7E8[arg0];
        temp->unk10 = arg1;
        temp->unk11 = arg2;
        temp->unk12 = arg3;
        temp->unk13 = arg4;
    }
}

void func_800C5000(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    unk8012A7E8 *temp;
    if (arg0 <= 0 || arg0 >= 8) {
        return;
    }
    temp = &D_8012A7E8[arg0];
    temp->unk14 = arg1;
    temp->unk15 = arg2;
    temp->unk16 = arg3;
    temp->unk17 = arg4;
    temp->unk1C = arg5;
}

void func_800C5050(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    unk8012A7E8 *temp;
    if (arg0 <= 0 || arg0 >= 8) {
        return;
    }
    temp = &D_8012A7E8[arg0]; // Issue with temp
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
    temp = &D_8012A7E8[arg0]; // Issue with temp
    temp->unk20 += arg1;
    temp->unk22 += arg2;
}

// Unused?
void func_800C50D8(s32 arg0) {
    unk8012A7E8 *temp;
    if (arg0 <= 0 || arg0 >= 8) {
        return;
    }
    temp = &D_8012A7E8[arg0]; // Issue with temp
    temp->unk20 = 0;
    temp->unk22 = 0;
}

// Unused?
// This function is OK
void func_800C510C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_800C5168(arg0, (*D_8012A7E8)[arg0].unk0, (*D_8012A7E8)[arg0].unk2, arg1, arg2, arg3);
}


GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C5168.s")
#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C5494.s")
#else
void func_800C5494(s32 arg0){
    unk8012A7E8 *tmp2 = &(*D_8012A7E8)[arg0];
    unk8012A7E8_24 *tmp = tmp2->unk24;
    if(tmp == NULL)
        return;
    
    while(tmp){
        tmp->unk01 = 255;
        tmp = tmp->unk1C;
    }
    tmp2->unk24 = NULL;
}

void func_800C54E8(s32 arg0, s16* arg1, u16 arg2, u16 arg3){
    s16 t4;
    s16 a3 = arg3;
    if(arg1 == 0 || (*D_8012A7E8)[arg0].unk19 == 255)
        return;
    t4 = arg1[6];
    switch(arg3){
        case 4: //L800C55E4;
            arg1[6] = 0;
            arg1[7] = 0;
            return;
        case 1: //L800C554C;
            a3 = arg3*1;
            break;
        case 2: //L800C5564;
        default: //L800C5564;
            break;
        
    }
    arg1[6] += arg2;
    arg1[7] += a3;
}
#endif


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
    D_800E3760 = allocate_from_main_pool_safe(0x2800, 0xFF);
    D_800E3764 = allocate_from_main_pool_safe(0x10, 0xFF);
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
