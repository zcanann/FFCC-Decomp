#ifndef _PPP_RANDUPCV_H_
#define _PPP_RANDUPCV_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandUpCVParam {
    s32 targetId;
    s32 sourceOffset;
    s8 delta[4];
    u8 useNormalDistribution;
};

#ifdef __cplusplus

extern "C" {
#endif

void pppRandUpCV(struct _pppPObject* basePtr, struct RandUpCVParam* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDUPCV_H_
