#ifndef MSL_STDLIB_H_
#define MSL_STDLIB_H_

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/abort_exit.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/arith.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/mbstring.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/strtoul.h"

#ifdef __cplusplus
extern "C" {
#endif

int rand(void);
void srand(unsigned int seed);

#ifdef __cplusplus
}
#endif

#endif
