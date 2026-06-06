#ifndef _PPP_RANDUPSHORT_H_
#define _PPP_RANDUPSHORT_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandUpShortDataOffsets {
    s32 m_valueOffset;
};

struct RandUpShortParam {
    s32 targetId;
    s32 sourceOffset;
    u16 scale;
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppRandUpShort(struct _pppPObject* basePtr, struct RandUpShortParam* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDUPSHORT_H_
