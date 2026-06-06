#ifndef _PPP_RANDSHORT_H_
#define _PPP_RANDSHORT_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandShortDataOffsets {
    s32 m_valueOffset;
};

struct RandShortParams {
    s32 targetId;
    s32 sourceOffset;
    u16 blend;
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppRandShort(struct _pppPObject* basePtr, struct RandShortParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDSHORT_H_
