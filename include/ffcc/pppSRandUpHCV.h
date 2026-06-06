#ifndef _PPP_SRANDUPHCV_H_
#define _PPP_SRANDUPHCV_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct SRandUpHCVDataOffsets {
    s32 m_stateOffset;
};

struct SRandUpHCVParams {
    s32 targetId;
    s32 sourceOffset;
    s16 delta[4];
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppSRandUpHCV(struct _pppPObject* basePtr, struct SRandUpHCVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SRANDUPHCV_H_
