#ifndef _FFCC_PPPCHANGETEX_H_
#define _FFCC_PPPCHANGETEX_H_

#include "ffcc/chara.h"
#include "ffcc/materialman.h"
#include "ffcc/mapmesh.h"
#include "ffcc/partMng.h"
#include "dolphin/gx/GXDispList.h"
#include "dolphin/gx/GXVert.h"
#include <dolphin/types.h>

struct pppChangeTex {
    _pppPObject m_object;
};

struct pppChangeTexUnkB {
    s32 m_graphId;
    s32 m_dataValIndex;
    float m_initWOrk;
    float m_stepValue;
    float m_arg3;
    u8 m_payload[6];
    u8 _pad1[1];
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructChangeTex(pppChangeTex*, _pppCtrlTable*);
void pppConstruct2ChangeTex(pppChangeTex*, _pppCtrlTable*);
void pppDestructChangeTex(pppChangeTex*, _pppCtrlTable*);
void pppFrameChangeTex(pppChangeTex*, pppChangeTexUnkB*, _pppCtrlTable*);
void pppRenderChangeTex(pppChangeTex*, pppChangeTexUnkB*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCHANGETEX_H_
