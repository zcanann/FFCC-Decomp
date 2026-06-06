#ifndef _PPP_RANDDOWNSHORT_H_
#define _PPP_RANDDOWNSHORT_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandDownShortDataOffsets {
    s32 m_valueOffset;
};

struct RandDownShortParam {
    s32 targetId;
    s32 sourceOffset;
    u16 scale;
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppRandDownShort(struct _pppPObject* basePtr, struct RandDownShortParam* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDDOWNSHORT_H_
