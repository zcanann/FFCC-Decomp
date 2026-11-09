#ifndef _PPP_RANDDOWNCHAR_H_
#define _PPP_RANDDOWNCHAR_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandDownCharParams {
    s32 targetId;
    s32 sourceOffset;
    u8 blend;
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppRandDownChar(struct _pppPObject* basePtr, struct RandDownCharParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDDOWNCHAR_H_
