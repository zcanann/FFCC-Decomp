#ifndef _PPP_SRANDUPFV_H_
#define _PPP_SRANDUPFV_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct SRandUpFVParams {
    s32 targetId;
    s32 sourceOffset;
    f32 blend[3];
    u8 _pad[4];
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppSRandUpFV(struct _pppPObject* basePtr, struct SRandUpFVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SRANDUPFV_H_
