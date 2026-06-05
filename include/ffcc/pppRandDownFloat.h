#ifndef _PPP_RANDDOWNFLOAT_H_
#define _PPP_RANDDOWNFLOAT_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandDownFloatParam {
    s32 targetId;
    s32 sourceOffset;
    f32 blend;
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppRandDownFloat(struct _pppPObject* basePtr, struct RandDownFloatParam* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDDOWNFLOAT_H_
