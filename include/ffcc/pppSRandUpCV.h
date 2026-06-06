#ifndef _PPP_SRANDUPCV_H_
#define _PPP_SRANDUPCV_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct SRandUpCVDataOffsets {
    s32 m_stateOffset;
};

struct SRandUpCVParam {
    s32 targetId;
    s32 sourceOffset;
    s8 delta[4];
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppSRandUpCV(struct _pppPObject* basePtr, struct SRandUpCVParam* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SRANDUPCV_H_
