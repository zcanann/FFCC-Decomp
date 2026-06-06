#ifndef _PPP_SRANDDOWNCV_H_
#define _PPP_SRANDDOWNCV_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct SRandDownCVDataOffsets {
    s32 m_stateOffset;
};

struct SRandDownCVParams {
    s32 targetId;
    s32 sourceOffset;
    s8 delta[4];
    u8 useNormalDistribution;
    u8 _pad[3];
};

#ifdef __cplusplus
extern "C" {
#endif

void pppSRandDownCV(struct _pppPObject* basePtr, struct SRandDownCVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SRANDDOWNCV_H_
