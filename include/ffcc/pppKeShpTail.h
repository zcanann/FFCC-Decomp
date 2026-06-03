#ifndef _PPP_KESHPTAIL_H_
#define _PPP_KESHPTAIL_H_

#include "ffcc/pppPart.h"

struct pppKeShpTailUnkB;

struct KeShpTailWork {
    u8 m_count;
    u8 m_head;
    u16 m_field2;
    u16 m_field4;
    u16 m_field6;
    Vec m_posHistory[31];
};

#ifdef __cplusplus
extern "C" {
#endif

void pppKeShpTail(_pppPObject*, pppKeShpTailUnkB*, _pppCtrlTable*);
void pppKeShpTailCon(_pppPObject* obj, _pppCtrlTable* ctrlTable);
void pppKeShpTailDraw(_pppPObject* obj, void* stepData, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KESHPTAIL_H_
