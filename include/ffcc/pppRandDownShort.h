#ifndef _PPP_RANDDOWNSHORT_H_
#define _PPP_RANDDOWNSHORT_H_


struct _pppPObject;
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void pppRandDownShort(struct _pppPObject* basePtr, struct RandDownShortParam* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDDOWNSHORT_H_
