#ifndef _PPP_FILTER_H_
#define _PPP_FILTER_H_

#include "ffcc/partMng.h"

struct pppFilterDataOffsets {
    s32 m_serializedDataOffset;
};

struct pppFilterStep {
    unsigned int m_unk0;
    int m_dataValIndex;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructFilter(_pppPObjLink*, _pppCtrlTable*);
void pppDestructFilter(_pppPObjLink*, _pppCtrlTable*);
void pppFrameFilter(_pppPObject*, pppFilterStep*, _pppCtrlTable*);
void pppRenderFilter(_pppPObject* pppFilterObj, pppFilterStep* step, _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_FILTER_H_
