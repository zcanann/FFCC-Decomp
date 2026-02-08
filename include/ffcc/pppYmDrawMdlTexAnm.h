#ifndef _PPP_YMDRAWMDLTEXANM_H_
#define _PPP_YMDRAWMDLTEXANM_H_

#include "ffcc/partMng.h"

struct pppYmDrawMdlTexAnm {
    _pppPObject field0_0x0;
};

struct pppYmDrawMdlTexAnmStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    s16 m_initWOrk;
    u16 _pad0;
    f32 m_stepValue;
    f32 m_arg3;
    u8 m_payload[8];
};

struct pppYmDrawMdlTexAnmOffsets {
    u8 _pad0[0x0C];
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmDrawMdlTexAnm(pppYmDrawMdlTexAnm* param1, pppYmDrawMdlTexAnmOffsets* param2, void* param3);
void pppDestructYmDrawMdlTexAnm(pppYmDrawMdlTexAnm* param1, pppYmDrawMdlTexAnmOffsets* param2, void* param3);
void pppFrameYmDrawMdlTexAnm(pppYmDrawMdlTexAnm* param1, pppYmDrawMdlTexAnmStep* param2, pppYmDrawMdlTexAnmOffsets* param3);
void pppRenderYmDrawMdlTexAnm(pppYmDrawMdlTexAnm* param1, pppYmDrawMdlTexAnmStep* param2, pppYmDrawMdlTexAnmOffsets* param3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMDRAWMDLTEXANM_H_
