#ifndef _PPP_YMDRAWMDLTEXANM_H_
#define _PPP_YMDRAWMDLTEXANM_H_

#include "ffcc/pppPart.h"

struct pppYmDrawMdlTexAnmStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    s32 m_initWOrk;
    s32 m_stepValue;
    f32 m_arg3;
    union {
        u8 m_payload[0x10];
        struct TexAnmPayload {
            s32 m_waitStep;
            u32 m_tilesU;
            u32 m_tilesV;
            u8 m_drawEnvColor0;
            u8 m_pad0D[3];
        } m_texAnm;
    };
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
