#ifndef _PPP_RANDINT_H_
#define _PPP_RANDINT_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandIntParams {
    s32 targetId;
    s32 sourceOffset;
    u32 blend;
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppRandInt(struct _pppPObject* basePtr, struct RandIntParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDINT_H_
