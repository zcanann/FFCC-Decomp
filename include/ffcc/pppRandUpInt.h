#ifndef _PPP_RANDUPINT_H_
#define _PPP_RANDUPINT_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandUpIntDataOffsets {
    s32 m_valueOffset;
};

struct RandUpIntParams {
    s32 targetId;
    s32 sourceOffset;
    u32 blend;
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppRandUpInt(struct _pppPObject* basePtr, struct RandUpIntParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDUPINT_H_
