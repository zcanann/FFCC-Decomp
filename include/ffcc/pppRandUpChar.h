#ifndef _PPP_RANDUPCHAR_H_
#define _PPP_RANDUPCHAR_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandUpCharDataOffsets {
    s32 m_valueOffset;
};

struct RandUpCharParam {
    s32 targetId;
    s32 sourceOffset;
    u8 scale;
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppRandUpChar(struct _pppPObject* basePtr, struct RandUpCharParam* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDUPCHAR_H_
