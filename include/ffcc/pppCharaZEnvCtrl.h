#ifndef _FFCC_PPPCHARAZENVCTRL_H_
#define _FFCC_PPPCHARAZENVCTRL_H_

#include "ffcc/chara.h"

struct UnkB;
struct UnkC;

struct pppCharaZEnvCtrl
{
    int field0_0x0[2];
};

void CharaZEnvCtrl_BeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int);

#ifdef __cplusplus
extern "C" {
#endif

void pppConCharaZEnvCtrl(void);
void pppDesCharaZEnvCtrl(void);
void pppFrameCharaZEnvCtrl(pppCharaZEnvCtrl*, UnkB*, UnkC*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCHARAZENVCTRL_H_
