#ifndef _PPP_RANDUPHCV_H_
#define _PPP_RANDUPHCV_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandUpHCVParams {
    s32 targetId;
    s32 sourceOffset;
    s16 delta[4];
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppRandUpHCV(struct _pppPObject* basePtr, struct RandUpHCVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDUPHCV_H_
