#ifndef OS_DOLPHIN_DOLPHIN_TRK_H
#define OS_DOLPHIN_DOLPHIN_TRK_H

#include "dolphin/types.h"
#include "PowerPC_EABI_Support/MetroTRK/trk.h"

#ifdef __cplusplus
extern "C" {
#endif

DSError TRKInitializeTarget();

void EnableMetroTRKInterrupts();
u32 TRKTargetTranslate(u32 param_0);
void TRK__read_aram(u32 param_1, u32 param_2, u32* param_3);
void TRK__write_aram(register u32 param_1, register u32 param_2, u32* param_3);

void __TRK_copy_vectors(void);

#ifdef __cplusplus
}
#endif

#endif /* OS_DOLPHIN_DOLPHIN_TRK_H */
