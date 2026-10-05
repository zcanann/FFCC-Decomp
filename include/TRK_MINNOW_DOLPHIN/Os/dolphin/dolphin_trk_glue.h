#ifndef OS_DOLPHIN_DOLPHIN_TRK_GLUE_H
#define OS_DOLPHIN_DOLPHIN_TRK_GLUE_H

#include "dolphin/os.h"
#include "PowerPC_EABI_Support/MetroTRK/trk.h"
#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

void EnableEXI2Interrupts(void);
void TRKUARTInterruptHandler();
#ifdef VERSION_GCCJGC
UARTError TRKReadUARTPoll(u8* byte);
UARTError WriteUART1(u8 byte);
UARTError WriteUARTFlush(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* OS_DOLPHIN_DOLPHIN_TRK_GLUE_H */
