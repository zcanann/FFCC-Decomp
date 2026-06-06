#ifndef _PPP_SRANDDOWNHCV_H_
#define _PPP_SRANDDOWNHCV_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct SRandDownHCVDataOffsets {
    s32 m_stateOffset;
};

struct SRandDownHCVParams {
    s32 targetId;
    s32 sourceOffset;
    s16 delta[4];
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppSRandDownHCV(struct _pppPObject* basePtr, struct SRandDownHCVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SRANDDOWNHCV_H_
