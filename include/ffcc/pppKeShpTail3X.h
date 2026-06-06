#ifndef _PPP_KESHPTAIL3X_H_
#define _PPP_KESHPTAIL3X_H_

#include "ffcc/partMng.h"

struct pppKeShpTail3X
{
    _pppPObject m_object;
};

struct KeShpTail3XDataOffsets {
    s32 m_workOffset;
    s32 m_alphaWorkOffset;
};

struct pppKeShpTail3XStep {
    s32 m_graphId;
    u32 m_dataValIndex;
    s32 m_initWork;
    float m_stepValue;
    float m_arg3;
    float m_randomScale;
    float m_stepDistance;
    u8 m_drawCount;
    u8 m_drawFirst;
    u16 m_rotateEnabled;
    s16 m_valueSteps[24];
    u8 m_drawA;
    u8 _pad51;
    u8 m_useEnvDepth;
    u8 m_worldSpaceMode;
    u8 _pad54;
    u8 m_zDisable;
    u8 m_blendMode;
    u8 _pad57;
    float m_envDepth;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppKeShpTail3X(struct pppKeShpTail3X*, struct pppKeShpTail3XStep*, struct _pppCtrlTable*);
void pppKeShpTail3XDraw(struct pppKeShpTail3X*, struct pppKeShpTail3XStep*, struct _pppCtrlTable*);
void pppKeShpTail3XCon(struct pppKeShpTail3X*, struct _pppCtrlTable*);
void pppKeShpTail3XDes(_pppPObjLink* obj, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KESHPTAIL3X_H_
