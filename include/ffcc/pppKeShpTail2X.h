#ifndef _PPP_KESHPTAIL2X_H_
#define _PPP_KESHPTAIL2X_H_

#include "ffcc/partMng.h"

struct pppKeShpTail2X
{
    _pppPObject m_object;
};

struct pppKeShpTail2XStep {
    u8 _pad0[4];
    s32 m_dataValIndex;
    s32 m_frameStep;
    float m_scaleStart;
    float m_scaleEnd;
    u8 m_colorStartR;
    u8 m_colorStartG;
    u8 m_colorStartB;
    u8 m_colorStartA;
    u8 m_colorEndR;
    u8 m_colorEndG;
    u8 m_colorEndB;
    u8 m_colorEndA;
    float m_stepDistance;
    u16 m_drawCount;
    u8 m_drawFirst;
    u8 m_drawA;
    u8 m_drawB;
    u8 m_useEnvDepth;
    u8 m_worldSpaceMode;
    u8 _pad27;
    u8 m_zDisable;
    u8 m_blendMode;
    u8 _pad2A[2];
    float m_envDepth;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppKeShpTail2X(struct pppKeShpTail2X*, struct pppKeShpTail2XStep*, _pppCtrlTable*);
void pppKeShpTail2XDraw(struct pppKeShpTail2X*, struct pppKeShpTail2XStep*, _pppCtrlTable*);
void pppKeShpTail2XCon(_pppPObject*, _pppCtrlTable*);
void pppKeShpTail2XDes(_pppPObject*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KESHPTAIL2X_H_
