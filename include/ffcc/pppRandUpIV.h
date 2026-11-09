#ifndef _PPP_RANDUPIV_H_
#define _PPP_RANDUPIV_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandUpIVParams {
    s32 targetId;
    s32 sourceOffset;
    s32 blend[3];
    u8 _pad[4];
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppRandUpIV(struct _pppPObject* basePtr, struct RandUpIVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDUPIV_H_
