#ifndef _PPP_PARMOVELINE_H_
#define _PPP_PARMOVELINE_H_

#include <dolphin/types.h>

struct _pppPObject;

struct ParMoveLineParams {
    u8 m_pad0[4];
    f32 m_speed;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppParMoveLine(_pppPObject* param_1, ParMoveLineParams* param_2);

#ifdef __cplusplus
}
#endif

#endif // _PPP_PARMOVELINE_H_
