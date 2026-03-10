#ifndef _PPP_YMDRAWMDLTEXANM_H_
#define _PPP_YMDRAWMDLTEXANM_H_

#include "ffcc/partMng.h"

struct pppYmDrawMdlTexAnm {
    _pppPObject field0_0x0;
};

struct pppYmDrawMdlTexAnmStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    s32 m_initWOrk;
    s32 m_stepValue;
    f32 m_arg3;
    u8 m_payload[0x10];
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmDrawMdlTexAnm(_pppPObjLink* object, _pppCtrlTable* ctrl);
void pppDestructYmDrawMdlTexAnm(_pppPObjLink* object, _pppCtrlTable* ctrl);
void pppFrameYmDrawMdlTexAnm(_pppPObject* object, pppYmDrawMdlTexAnmStep* step, _pppCtrlTable* ctrl);
void pppRenderYmDrawMdlTexAnm(_pppPObject* object, pppYmDrawMdlTexAnmStep* step, _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMDRAWMDLTEXANM_H_
