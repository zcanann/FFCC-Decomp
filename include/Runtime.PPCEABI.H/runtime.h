#ifndef RUNTIME_PPCEABI_RUNTIME_H
#define RUNTIME_PPCEABI_RUNTIME_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*voidfunctionptr)(void);

u32 __cvt_fp2unsigned(f64 d);
extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];

#ifdef __cplusplus
}
#endif

#endif
