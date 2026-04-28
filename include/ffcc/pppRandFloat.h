#ifndef _PPP_RANDFLOAT_H_
#define _PPP_RANDFLOAT_H_

#include "dolphin/types.h"

struct _pppCtrlTable;
struct RandFloatParam;

#ifdef __cplusplus
extern "C" {
#endif

void pppRandFloat(void* basePtr, struct RandFloatParam* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDFLOAT_H_
