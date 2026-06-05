#ifndef _PPP_PARHITSPH_H_
#define _PPP_PARHITSPH_H_

#include <dolphin/types.h>

class CFlatRuntime2;
struct _pppPObject;

struct ParHitSphParams {
    u8 m_pad0[4];
    f32 m_cylinderScale;
    f32 m_radiusScale;
};

void CFlatRuntime2_IsDispRadiusCC(CFlatRuntime2*);

#ifdef __cplusplus
extern "C" {
#endif

void pppParHitSph(_pppPObject* param_1, ParHitSphParams* param_2);

#ifdef __cplusplus
}
#endif

#endif // _PPP_PARHITSPH_H_
