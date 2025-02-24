#ifndef _DBGPROTO_H__
#define _DBGPROTO_H__

#include "PRinternal/dbgdefs.h"

#define KK_REV 2

#define KK_CODE_THREAD_STATUS 4

#define KK_TYPE_REQUEST      0
#define KK_TYPE_REPLY        1
#define KK_TYPE_EXCEPTION    2
#define KK_TYPE_THREAD_EXIT  3
#define KK_TYPE_PROCESS_EXIT 4
#define KK_TYPE_CONSOLE      5

#define TV_ERROR_NO_ERROR               0
#define TV_ERROR_ILLEGAL_CALL           -1
#define TV_ERROR_INVALID_ID             -2
#define TV_ERROR_INVALID_TYPE           -3
#define TV_ERROR_OPERATIONS_PROTECTED   -4
#define TV_ERROR_INVALID_ADDRESS        -5
#define TV_ERROR_INVALID_PRIORITY       -6
#define TV_ERROR_INVALID_FLAGS          -7
#define TV_ERROR_INVALID_CAPABILITY     -8
#define TV_ERROR_NO_HANDLER             -9
#define TV_ERROR_NO_MORE_IDS            -10
#define TV_ERROR_NO_MORE_MESSAGES       -11
#define TV_ERROR_NO_MORE_PROCESSES      -12
#define TV_ERROR_NO_MORE_THREADS        -13
#define TV_ERROR_NO_MORE_REGIONS        -14
#define TV_ERROR_NO_MORE_TIMERS         -15
#define TV_ERROR_NO_MORE_LOCKS          -16
#define TV_ERROR_NO_MORE_QUEUES         -17
#define TV_ERROR_NO_MORE_SETS           -18
#define TV_ERROR_NO_MORE_MEMORY         -19
#define TV_ERROR_NOT_LOCKED             -20

typedef struct __KKTimeStruct {
    long seconds;
    long nanoseconds;
} KKTimeStruct;

typedef struct __KKObjsStruct {
    TVushort number;
    TVid objects[1];
} KKObjs;

typedef struct __KKFaultInfoStruct {
    unsigned int addr;
    short major;
    short minor;
} KKFaultInfo;

typedef struct __KKThreadStatusStruct {
    int flags;
    short why;
    short what;
    TVid tid;
    TVid pid;
    unsigned int instr;
    KKFaultInfo info;
    int priority;
    int start;
    int rv;
    unsigned int args[6];
} KKThreadStatus;

#define KK_RUN_SSTEP (1 << 0)
#define KK_RUN_SETPC (1 << 1)

typedef struct __KKRunStruct {
    int flags;
    unsigned int vaddr;
} KKRun;

typedef struct __KKFaultStruct {
    short majorMask;
    short minorMask;
} KKFault;

typedef struct __KKRegionStruct {
    unsigned int vaddr;
    unsigned int size;
    short flags;
    unsigned int paddr;
} KKRegion;

typedef struct __KKGregSetStruct {
    unsigned int gregs[37];
} KKGregSet;

typedef struct __KKFPregSetStruct {
    union {
        double dregs[16];
        float fregs[32];
        unsigned int regs[32];
    } fpregs;
    unsigned int fpcsr;
    unsigned int fppad;
} KKFPregSet;

typedef struct __KKRegisterContextStruct {
    KKGregSet gregs;
    KKFPregSet fpregs;
} KKRegisterContext;

typedef struct __KKCpScalarSetStruct {
    unsigned int sregs[40];
} KKCpScalarRegSet;

typedef struct __KKCpVectorSetStruct {
    unsigned int vregs[128];
} KKCpVectorRegSet;

typedef struct __KKCpRegisterContextStruct {
    KKCpScalarRegSet sregs;
    KKCpVectorRegSet vregs;
} KKCpRegisterContext;

typedef struct __KKUsageStruct {
    KKTimeStruct tstamp;
    KKTimeStruct created;
    KKTimeStruct states[10];
} KKUsage;

typedef struct __KKLogEventSetStruct {
    int from;
    int to;
} KKLogEventSet;

typedef struct __KKLogStatusStruct {
    int bufferType;
    int bufferSize;
    int dataSize;
    int logState;
    int flushLimit;
} KKLogStatus;

typedef struct __KKProcUsageStruct {
    TVid pid;
    KKTimeStruct states[10];
} KKProcUsage;

typedef struct __KKHeaderStruct {
    int length;
    char code;
    char type;
    short error;
    char rev;
    char method;
    short notused2;
} KKHeader;

typedef struct __KKGetFrameRequestStruct {
    KKHeader header;
    int height;
    int width;
    int which;
} KKGetFrameRequest;

typedef struct __KKLoadExecutableRequestStruct {
    KKHeader header;
    char str[1];
} KKLoadExecutableRequest;

typedef struct __KKObjectRequestStruct {
    KKHeader header;
    TVid object;
} KKObjectRequest;

typedef struct __KKRunThreadRequestStruct {
    KKHeader header;
    TVid tid;
    KKRun actions;
} KKRunThreadRequest;

typedef struct __KKFaultRequestStruct {
    KKHeader header;
    TVid tid;
    KKFault fault;
    TVuchar stopAllThreads;
} KKFaultRequest;

typedef struct __KKGRegsetRequestStruct {
    KKHeader header;
    TVid tid;
    KKGregSet registers;
} KKGRegsetRequest;

typedef struct __KKFPRegsetRequestStruct {
    KKHeader header;
    TVid tid;
    KKFPregSet registers;
} KKFPRegsetRequest;

typedef struct __KKCpScalarRegsetRequestStruct {
    KKHeader header;
    TVid tid;
    KKCpScalarRegSet registers;
} KKCpScalarRegsetRequest;

typedef struct __KKCpVectorRegsetRequestStruct {
    KKHeader header;
    TVid tid;
    KKCpVectorRegSet registers;
} KKCpVectorRegsetRequest;

typedef struct __KKReadRequestStruct {
    KKHeader header;
    TVid object;
    unsigned int addr;
    unsigned int nbytes;
} KKReadRequest;

typedef struct __KKWriteHeaderStruct {
    KKHeader header;
    TVid object;
    unsigned int addr;
    unsigned int nbytes;
} KKWriteHeader;

typedef struct __KKWriteRequestStruct {
    KKWriteHeader writeHeader;
    char buffer[1];
} KKWriteRequest;

typedef struct __KKSetBkptRequestStruct {
    KKHeader header;
    TVid object;
    unsigned int addr;
} KKSetBkptRequest;

typedef struct __KKClrBkptRequestStruct {
    KKHeader header;
    TVid object;
    TVid bp;
} KKClrBkptRequest;

typedef struct __KKWatchRequestStruct {
    KKHeader header;
    TVid object;
    unsigned int number;
    KKRegion wp[1];
} KKWatchRequest;

typedef struct __KKSetCommRequestStruct {
    KKHeader header;
    unsigned int how;
    unsigned int addr;
} KKSetCommRequest;

typedef struct __KKSysCallSetStruct {
    unsigned int word[8];
} KKSysCallSet;

typedef struct __KKSysCallRequestStruct {
    KKHeader header;
    TVid pid;
    KKSysCallSet syscallset;
} KKSysCallRequest;

typedef struct __KKLogEventRequestStruct {
    KKHeader header;
    unsigned int numSet;
    KKLogEventSet set[1];
} KKLogEventRequest;

typedef struct __KKNewLogRequestStruct {
    KKHeader header;
    char str[1];
} KKNewLogRequest;

typedef struct __KKRemoteRequestStruct {
    KKHeader header;
    int len;
    char buf[16];
} KKRemoteRequest;

typedef struct __KKFlushLogRequestStruct {
    KKHeader header;
    int no_block;
} KKFlushLogRequest;

typedef struct __KKLogControlRequestStruct {
    KKHeader header;
    int command;
    int arg;
} KKLogControlRequest;

typedef struct __KKSetTrptRequestStruct {
    KKSetBkptRequest bpRequest;
    unsigned short code;
} KKSetTrptRequest;

typedef KKClrBkptRequest KKClrTrptRequest;

typedef struct __KKObjectEventStruct {
    KKHeader header;
    TVid object;
} KKObjectEvent;

typedef struct __KKObjsEventStruct {
    KKHeader header;
    TVid object;
    KKObjs objs;
} KKObjsEvent;

typedef struct __KKBufferEventStruct {
    KKHeader header;
    TVid object;
    char buffer[1];
} KKBufferEvent;

typedef struct __KKStatusEventStruct {
    KKHeader header;
    KKThreadStatus status;
} KKStatusEvent;

typedef struct __KKFaultEventStruct {
    KKHeader header;
    TVid tid;
    KKFault fault;
    TVuchar stopAllThreads;
} KKFaultEvent;

typedef struct __KKNumberEventStruct {
    KKHeader header;
    TVid object;
    unsigned int number;
} KKNumberEvent;

typedef struct __KKRegionEventStruct {
    KKHeader header;
    TVid object;
    unsigned int number;
    KKRegion regions[1];
} KKRegionEvent;

typedef struct __KKGregEventStruct {
    KKHeader header;
    TVid tid;
    KKGregSet registers;
} KKGregEvent;

typedef struct __KKFPregEventStruct {
    KKHeader header;
    TVid tid;
    KKFPregSet registers;
} KKFPregEvent;

typedef struct __KKCpSregEventStruct {
    KKHeader header;
    TVid tid;
    KKCpScalarRegSet registers;
} KKCpSregEvent;

typedef struct __KKCpVregEventStruct {
    KKHeader header;
    TVid tid;
    KKCpVectorRegSet registers;
} KKCpVregEvent;

typedef struct __KKBkptEventStruct {
    KKHeader header;
    TVid object;
    TVid bp;
    unsigned int instruction;
} KKBkptEvent;

typedef struct __KKUsageEventStruct {
    KKHeader header;
    TVid tid;
    KKUsage usage;
} KKUsageEvent;

typedef struct __KKFlushEventStruct {
    KKHeader header;
    int bufferType;
    char buffer[1];
} KKFlushEvent;

typedef struct __KKLogStatusEventStruct {
    KKHeader header;
    KKLogStatus status;
} KKLogStatusEvent;

typedef struct __KKSysUsageEventStruct {
    KKHeader header;
    KKTimeStruct tstamp;
    int numProc;
    KKProcUsage usage[1];
} KKSysUsageEvent;

typedef struct __KKStringEventStruct {
    KKHeader header;
    char str[1];
} KKStringEvent;

typedef KKSysCallRequest KKSysCallEvent;

#endif
