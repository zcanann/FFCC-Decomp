#ifndef _FFCC_PPPCONFORMBGNORMAL_H_
#define _FFCC_PPPCONFORMBGNORMAL_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppConformBGNormal;

struct pppConformBGNormalStep {
    u32 m_unk0;
    float m_dataValIndex;
    float m_initWOrk;
    u8 m_stepValue;
    u8 m_pad0D[3];
    float m_arg3;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructConformBGNormal(pppConformBGNormal* conformBG, struct _pppCtrlTable* data);
void pppFrameConformBGNormal(pppConformBGNormal* conformBG, pppConformBGNormalStep* param2, struct _pppCtrlTable* data);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCONFORMBGNORMAL_H_
