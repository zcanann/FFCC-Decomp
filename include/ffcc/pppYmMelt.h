#ifndef _FFCC_PPP_YMMELT_H_
#define _FFCC_PPP_YMMELT_H_

#include "ffcc/pppPart.h"

struct PYmMelt
{
    _pppPObject m_object;
};

struct PYmMeltDataOffsets;
struct YmMeltCtrl;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMelt(PYmMelt*, PYmMeltDataOffsets*);
void pppDestructYmMelt(PYmMelt*, PYmMeltDataOffsets*);
void pppFrameYmMelt(PYmMelt*, YmMeltCtrl*, PYmMeltDataOffsets*);
void pppRenderYmMelt(PYmMelt*, YmMeltCtrl*, PYmMeltDataOffsets*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMELT_H_
