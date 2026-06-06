#ifndef _PPP_RANDCHAR_H_
#define _PPP_RANDCHAR_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandCharDataOffsets {
    s32 m_valueOffset;
};

struct RandCharParam {
    s32 targetId;
    s32 sourceOffset;
    u8 scale;
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppRandChar(struct _pppPObject* basePtr, struct RandCharParam* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDCHAR_H_
