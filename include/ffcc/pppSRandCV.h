#ifndef _PPP_SRANDCV_H_
#define _PPP_SRANDCV_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct SRandCVDataOffsets {
    s32 m_stateOffset;
};

struct SRandCVParam {
    s32 targetId;
    s32 sourceOffset;
    s8 delta[4];
    u8 useNormalDistribution;
    u8 _pad[3];
};

#ifdef __cplusplus
extern "C" {
#endif

void pppSRandCV(struct _pppPObject* basePtr, struct SRandCVParam* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SRANDCV_H_
