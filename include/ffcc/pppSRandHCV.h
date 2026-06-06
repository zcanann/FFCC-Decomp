#ifndef _PPP_SRANDHCV_H_
#define _PPP_SRANDHCV_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct SRandHCVDataOffsets {
    s32 m_stateOffset;
};

struct SRandHCVParams {
    s32 targetId;
    s32 sourceOffset;
    s16 delta[4];
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppSRandHCV(struct _pppPObject* basePtr, struct SRandHCVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SRANDHCV_H_
