#ifndef _DOLPHIN_DSP_INTERNAL_H_
#define _DOLPHIN_DSP_INTERNAL_H_

#include <dolphin/dsp.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DSPStrings {
    char version[0x45];
    char _pad0[3];
    char initMsg[0x1E];
    char _pad1[2];
    char buildDate[0xC];
    char buildTime[0x9];
    char _pad2[3];
} DSPStrings;

extern DSPStrings sDSPStrings;
extern DSPTaskInfo* __DSP_first_task;
extern DSPTaskInfo* __DSP_last_task;
extern DSPTaskInfo* __DSP_curr_task;
extern DSPTaskInfo* __DSP_tmp_task;
extern DSPTaskInfo* __DSP_rude_task;
extern int __DSP_rude_task_pending;

__declspec(weak) void __DSPHandler(__OSInterrupt, OSContext*);
void __DSP_exec_task(DSPTaskInfo*, DSPTaskInfo*);
void __DSP_boot_task(DSPTaskInfo*);
void __DSP_insert_task(DSPTaskInfo*);
void __DSP_add_task(DSPTaskInfo* task);
void __DSP_remove_task(DSPTaskInfo* task);
void __DSP_debug_printf(const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
