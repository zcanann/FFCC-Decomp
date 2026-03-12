#ifndef _PPP_KEZCRCTSHP_H_
#define _PPP_KEZCRCTSHP_H_

#include "ffcc/partMng.h"

struct pppKeZCrctShpStep
{
    char m_pad0[8];
    Vec m_offset;         // +0x08
    char m_pad14[4];
    Vec m_positionScale;  // +0x18
    char m_pad24[4];
    u8 m_mode;            // +0x28
};

#ifdef __cplusplus
extern "C" {
#endif

void pppKeZCrctShpDraw(_pppPObject* object, pppKeZCrctShpStep* stepData, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KEZCRCTSHP_H_
