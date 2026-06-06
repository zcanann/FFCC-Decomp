#ifndef _PPP_RANDIV_H_
#define _PPP_RANDIV_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandIVDataOffsets {
    s32 m_valueOffset;
};

struct RandIVParams {
    s32 targetId;
    s32 sourceOffset;
    s32 blend[3];
    u8 _pad[4];
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppRandIV(struct _pppPObject* basePtr, struct RandIVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDIV_H_
