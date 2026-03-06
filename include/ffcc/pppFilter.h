#ifndef _PPP_FILTER_H_
#define _PPP_FILTER_H_

#include "ffcc/partMng.h"

#include <dolphin/gx/GXStruct.h>

struct pppFilter {
    char padding[0x88];
    _GXColor m_color;
    char padding2[4];
};

struct pppFilterUnkB {
    unsigned int m_unk0;
    unsigned int m_dataValIndex;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructFilter(_pppPObjLink*, _pppCtrlTable*);
void pppDestructFilter(_pppPObjLink*, _pppCtrlTable*);
void pppFrameFilter(_pppPObject*, void*, _pppCtrlTable*);
void pppRenderFilter(pppFilter* pppFilter, pppFilterUnkB* param_2, _pppCtrlTable* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_FILTER_H_

