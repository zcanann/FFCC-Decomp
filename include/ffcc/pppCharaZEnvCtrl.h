#ifndef _FFCC_PPPCHARAZENVCTRL_H_
#define _FFCC_PPPCHARAZENVCTRL_H_

#include "ffcc/chara.h"

void CharaZEnvCtrl_BeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int);
void pppConCharaZEnvCtrl(void);
void pppDesCharaZEnvCtrl(void);
void pppFrameCharaZEnvCtrl(void);

#endif // _FFCC_PPPCHARAZENVCTRL_H_
