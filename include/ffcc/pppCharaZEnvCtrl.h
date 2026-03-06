#ifndef _FFCC_PPPCHARAZENVCTRL_H_
#define _FFCC_PPPCHARAZENVCTRL_H_

#include "ffcc/chara.h"
#include "ffcc/partMng.h"

struct pppCharaZEnvCtrlUnkB;

struct pppCharaZEnvCtrl
{
    int field0_0x0[2];
};

void CharaZEnvCtrl_BeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int);

#ifdef __cplusplus
extern "C" {
#endif

void pppConCharaZEnvCtrl(_pppPObjLink*, _pppCtrlTable*);
void pppDesCharaZEnvCtrl(_pppPObjLink*, _pppCtrlTable*);
void pppFrameCharaZEnvCtrl(pppCharaZEnvCtrl*, pppCharaZEnvCtrlUnkB*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCHARAZENVCTRL_H_

