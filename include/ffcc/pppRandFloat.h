#ifndef _PPP_RANDFLOAT_H_
#define _PPP_RANDFLOAT_H_


struct _pppPObject;
#include "dolphin/types.h"

struct _pppCtrlTable;
struct RandFloatParam;

#ifdef __cplusplus
extern "C" {
#endif

void pppRandFloat(struct _pppPObject* basePtr, struct RandFloatParam* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDFLOAT_H_
