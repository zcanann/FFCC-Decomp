#ifndef _PPP_RANDFLOAT_H_
#define _PPP_RANDFLOAT_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandFloatParam {
    s32 targetId;
    s32 sourceOffset;
    f32 blend;
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppRandFloat(struct _pppPObject* basePtr, struct RandFloatParam* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDFLOAT_H_
