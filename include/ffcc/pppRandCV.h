#ifndef _PPP_RANDCV_H_
#define _PPP_RANDCV_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandCVParams {
    s32 index;
    s32 colorOffset;
    s8 delta[4];
    u8 flag;
    u8 pad[3];
};

#ifdef __cplusplus

extern "C" {
#endif

void pppRandCV(struct _pppPObject* basePtr, struct RandCVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDCV_H_
