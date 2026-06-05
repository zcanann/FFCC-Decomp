#ifndef _FFCC_PPPCHARAZENVCTRL_H_
#define _FFCC_PPPCHARAZENVCTRL_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObjLink;
struct _pppPObject;

typedef _pppPObject pppCharaZEnvCtrl;

struct pppCharaZEnvCtrlStep
{
    s32 m_graphId;
    u8 m_zEnable;
    u8 m_zWriteEnable;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConCharaZEnvCtrl(_pppPObjLink*, _pppCtrlTable*);
void pppDesCharaZEnvCtrl(_pppPObjLink*, _pppCtrlTable*);
void pppFrameCharaZEnvCtrl(pppCharaZEnvCtrl*, pppCharaZEnvCtrlStep*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCHARAZENVCTRL_H_
