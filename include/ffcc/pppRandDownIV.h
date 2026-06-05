#ifndef _PPP_RANDDOWNIV_H_
#define _PPP_RANDDOWNIV_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandDownIVParams {
    s32 targetId;
    s32 sourceOffset;
    s32 blend[3];
    u8 _pad[4];
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppRandDownIV(struct _pppPObject* basePtr, struct RandDownIVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDDOWNIV_H_
