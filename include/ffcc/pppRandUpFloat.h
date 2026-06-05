#ifndef _PPP_RANDUPFLOAT_H_
#define _PPP_RANDUPFLOAT_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandUpFloatParam {
    s32 targetId;
    s32 sourceOffset;
    f32 blend;
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppRandUpFloat(struct _pppPObject* basePtr, struct RandUpFloatParam* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDUPFLOAT_H_
