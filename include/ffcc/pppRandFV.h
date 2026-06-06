#ifndef _PPP_RANDFV_H_
#define _PPP_RANDFV_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct RandFVDataOffsets {
    s32 m_valueOffset;
};

struct RandFVParams {
    s32 targetId;
    s32 sourceOffset;
    f32 blend[3];
    u8 _pad[4];
    u8 useNormalDistribution;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppRandFV(struct _pppPObject* basePtr, struct RandFVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDFV_H_
