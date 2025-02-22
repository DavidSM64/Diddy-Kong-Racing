#ifndef _THREAD0_EPC_H_
#define _THREAD0_EPC_H_

#include "types.h"
#include <ultra64.h>
#include "macros.h"

/* Size: 0x1B0 bytes */
typedef struct epcInfo {
/*  0x00 */ s32 unk0;
/*  0x04 */ s32 unk4;
/*  0x08 */ s32 unk8;
/*  0x0C */ s32 unkC;
/*  0x10 */ s32 unk10;
/*  0x14 */ s32 thread[1];
/*  0x18 */ s32 unk18;
/*  0x1C */ s32 unk1C;
/*  0x20 */ s64 at;
/*  0x28 */ s64 v0;
/*  0x30 */ s64 v1;
/*  0x38 */ s64 a0;
/*  0x40 */ s64 a1;
/*  0x48 */ s64 a2;
/*  0x50 */ s64 a3;
/*  0x58 */ s64 t0;
/*  0x60 */ s64 t1;
/*  0x68 */ s64 t2;
/*  0x70 */ s64 t3;
/*  0x78 */ s64 t4;
/*  0x80 */ s64 t5;
/*  0x88 */ s64 t6;
/*  0x90 */ s64 t7;
/*  0x98 */ s64 s0;
/*  0xA0 */ s64 s1;
/*  0xA8 */ s64 s2;
/*  0xB0 */ s64 s3;
/*  0xB8 */ s64 s4;
/*  0xC0 */ s64 s5;
/*  0xC8 */ s64 s6;
/*  0xD0 */ s64 s7;
/*  0xD8 */ s64 t8;
/*  0xE0 */ s64 t9;
/*  0xE8 */ s64 gp;
/*  0xF0 */ s64 sp;
/*  0xF8 */ s64 s8;
/* 0x100 */ s64 ra;
/* 0x108 */ s32 unk108;
/* 0x10C */ s32 unk10C;
/* 0x110 */ s32 unk110;
/* 0x114 */ s32 unk114;
/* 0x118 */ s32 sr;
/* 0x11C */ s32 epc;
/* 0x120 */ s32 cause;
/* 0x124 */ s32 badvaddr;
/* 0x128 */ s32 unk128;
/* 0x12C */ s32 unk12C;
/* 0x130 */ f32 objectStackTrace[3];
/* 0x13C */ u8 pad13C[0x74];
} epcInfo;

/* Unknown Size, might be epcInfo? */
typedef struct unk800D2470 {
/*  0x00 */ OSThread *thread;
/*  0x04 */ s32 unk4;
/*  0x08 */ s32 unk8;
/*  0x0C */ struct unk800D2470 *next;
/*  0x10 */ u8 pad10[0x108];
/* 0x118 */ s32 unk118;
} unk800D2470;

enum EPCScreenPage {
    EPC_PAGE_REGISTER,
    EPC_PAGE_STACK_TOP,
    EPC_PAGE_STACK_MIDDLE,
    EPC_PAGE_STACK_BOTTOM,
    EPC_PAGE_UNK04,
    EPC_PAGE_EXIT
};

enum ObjectStackTraceID {
    OBJECT_CLEAR = -1,
    OBJECT_SPAWN,
    OBJECT_UPDATE,
    OBJECT_DRAW
};

void enable_interupts_on_main(void);
void stop_all_threads_except_main(void);
void update_object_stack_trace(s32 index, s32 value);
s32 get_lockup_status(void);
void mode_lockup(s32 updateRate);
void thread0_create(void);
void write_epc_data_to_cpak(void);
void dump_memory_to_cpak(s32 epc, s32 size, u32 colourTag);
void thread0_Main(UNUSED void *unused);
void render_epc_lock_up_display(void);

#endif
