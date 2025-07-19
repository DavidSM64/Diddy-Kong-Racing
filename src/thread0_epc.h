#ifndef _THREAD0_EPC_H_
#define _THREAD0_EPC_H_

#include "types.h"
#include <ultra64.h>
#include "macros.h"

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
