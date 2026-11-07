#ifndef _PPP_RANDDOWNINT_H_
#define _PPP_RANDDOWNINT_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandDownIntParams {
    s32 targetId;
    s32 sourceOffset;
    u32 blend;
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppRandDownInt(struct _pppPObject* basePtr, struct RandDownIntParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDDOWNINT_H_
