#ifndef _PPP_RANDDOWNCV_H_
#define _PPP_RANDDOWNCV_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandDownCVParams {
    s32 targetId;
    s32 sourceOffset;
    s8 delta[4];
    u8 useNormalDistribution;
};

#ifdef __cplusplus

extern "C" {
#endif

void pppRandDownCV(struct _pppPObject* basePtr, struct RandDownCVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDDOWNCV_H_
