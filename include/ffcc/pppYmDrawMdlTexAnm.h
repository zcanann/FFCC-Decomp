#ifndef _PPP_YMDRAWMDLTEXANM_H_
#define _PPP_YMDRAWMDLTEXANM_H_

#include "ffcc/pppPart.h"

struct pppYmDrawMdlTexAnmDataOffsets {
    s32 m_colorBlockOffset;
    s32 _unused04;
    s32 m_workOffset;
};

struct pppYmDrawMdlTexAnmStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    u8 m_pad08;
    u8 m_blendMode;
    u8 m_fogIndex;
    u8 m_cullMode;
    u8 m_zEnable;
    u8 m_colorUpdate;
    u8 m_zWrite;
    u8 m_pad0F;
    f32 m_depth;
    s32 m_waitStep;
    u32 m_tilesU;
    u32 m_tilesV;
    u8 m_lightTarget;
    u8 m_pad21[3];
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
