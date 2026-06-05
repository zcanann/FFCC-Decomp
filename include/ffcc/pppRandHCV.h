#ifndef _PPP_RANDHCV_H_
#define _PPP_RANDHCV_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandHCVParams {
    s32 targetId;
    s32 sourceOffset;
    s16 delta[4];
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppRandHCV(struct _pppPObject* basePtr, struct RandHCVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDHCV_H_
