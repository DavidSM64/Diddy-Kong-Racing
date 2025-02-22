#ifndef _RMONINT_H
#define _RMONINT_H

#include "PRinternal/dbgproto.h"
#include "PR/os_internal.h"

/* mips */

#define MIPS_LWC2_OPCODE 50
#define MIPS_SWC2_OPCODE 58

#define MIPS_LW_OPCODE 35
#define MIPS_SW_OPCODE 43

#define MIPS_BREAK_OPCODE 0xD
#define MIPS_BREAK_MASK 0xFC00003F

#define MIPS_BREAK(code) \
    ((((code) & 0xFFFFF) << 6) | MIPS_BREAK_OPCODE)

/* R4300 General Purpose Register Indices */
#define GREG_IDX_ZERO   0
#define GREG_IDX_AT     1
#define GREG_IDX_T9     25
#define GREG_IDX_K0     26
#define GREG_IDX_GP     28
#define GREG_IDX_RA     31
#define GREG_IDX_LO     32
#define GREG_IDX_HI     33
#define GREG_IDX_CAUSE  34
#define GREG_IDX_PC     35
#define GREG_IDX_SR     36

/* RSP Scalar Register Indices */
#define SREG_IDX_ZERO       0
#define SREG_IDX_RA         31
#define SREG_IDX_DRAM_ADDR  (32 + 0)
#define SREG_IDX_MEM_ADDR   (32 + 1)
#define SREG_IDX_RD_LEN     (32 + 2)
#define SREG_IDX_PC         (32 + 3)
#define SREG_IDX_WR_LEN     (32 + 4)
#define SREG_IDX_STATUS     (32 + 5)
#define SREG_IDX_DMA_FULL   (32 + 6)
#define SREG_IDX_DMA_BUSY   (32 + 7)

/* RSP Vector Register Properties */
#define VREG_NUM 32
#define VREG_SIZE 0x10

/* rmon */

#define RMON_MESG_CPU_BREAK 2
#define RMON_MESG_SP_BREAK 4
#define RMON_MESG_FAULT 8

#define RMON_CPU 0
#define RMON_RSP 1

/* "thread id" for rsp */
#define RMON_TID_RSP 1000
/* "thread priority" for rsp */
#define RMON_PRI_RSP 42

/* "thread id" for no thread running */
#define RMON_TID_NOTHREAD 1003

#define RMON_PID_CPU 1002
#define RMON_PID_RSP 1001

/* Largest serviceable read/write memory request */
#define RMON_MAX_XFER_SIZE 1024

/* rmonmain */

void __rmonSendHeader(KKHeader* const block, u32 blockSize, u32 type);
void __rmonSendReply(KKHeader* const block, u32 blockSize, u32 replyType);
void __rmonSendData(char* const block, unsigned int blockSize);

extern int __rmonActive;

/* rmonmisc */

void __rmonInit(void);
void __rmonPanic(void);

extern OSMesgQueue __rmonMQ;

/* rmonmem */

void __rmonWriteWordTo(u32* addr, u32 val);
u32 __rmonReadWordAt(u32* addr);
void __rmonMemcpy(u8* dest, u8* srce, u32 count);
void __rmonCopyWords(u32* dest, u32* srce, u32 count);

extern u8 __rmonUtilityBuffer[];

/* rmonsio */

void __rmonSendFault(OSThread* thread);
void __rmonIOflush(void);
void __rmonIOputw(u32 word);
void __rmonIOhandler(void);

extern void* __osRdb_DbgRead_Buf;
extern u8 rmonRdbReadBuf[];

/* rmonrcp */

int __rmonRCPrunning(void);
void __rmonIdleRCP(void);
void __rmonStepRCP(void);
void __rmonRunRCP(void);

/* rmonbrk */

u32 __rmonGetBranchTarget(int method, int thread, char* addr);
int __rmonSetSingleStep(int thread, u32* instptr);
void __rmonGetExceptionStatus(KKStatusEvent* reply);
void __rmonHitBreak(void);
void __rmonHitSpBreak(void);
void __rmonHitCpuFault(void);

extern u8 __rmonRcpAtBreak;

/* rmonregs */

u32 __rmonGetRegisterContents(int method, int threadNumber, int regNumber);

/* rmontask */

void __rmonMaskIdleThreadInts(void);
OSThread* __rmonGetTCB(int threadNumber);
int __rmonStopUserThreads(int whichThread);
int __rmonGetThreadStatus(int method, int id, KKStatusEvent* reply);

/* rmoncmds */

int __rmonExecute(KKHeader* request);

/* commands */

typedef int (*FUNPTR)();

int __rmonLoadProgram(KKHeader* req);
int __rmonListProcesses(KKHeader* req);
int __rmonGetExeName(KKHeader* req);
int __rmonListThreads(KKHeader* req);
int __rmonThreadStatus(KKHeader* req);
int __rmonStopThread(KKHeader* req);
int __rmonRunThread(KKHeader* req);
int __rmonSetFault(KKHeader* req);
int __rmonGetRegionCount(KKHeader* req);
int __rmonGetRegions(KKHeader* req);
int __rmonGetGRegisters(KKHeader* req);
int __rmonSetGRegisters(KKHeader* req);
int __rmonGetFRegisters(KKHeader* req);
int __rmonSetFRegisters(KKHeader* req);
int __rmonReadMem(KKHeader* req);
int __rmonWriteMem(KKHeader* req);
int __rmonSetBreak(KKHeader* req);
int __rmonClearBreak(KKHeader* req);
int __rmonListBreak(KKHeader* req);
int __rmonSetComm(KKHeader* req);
int __rmonGetSRegs(KKHeader* req);
int __rmonSetSRegs(KKHeader* req);
int __rmonGetVRegs(KKHeader* req);
int __rmonSetVRegs(KKHeader* req);

#endif
