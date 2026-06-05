#ifndef _PPP_SCREENQUAKE_H_
#define _PPP_SCREENQUAKE_H_

#include "ffcc/partMng.h"

struct pppScreenQuake;
struct pppScreenQuakeStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppConScreenQuake(pppScreenQuake *quake, _pppCtrlTable *param2);
void pppCon2ScreenQuake(pppScreenQuake *quake, _pppCtrlTable *param2);
void pppDesScreenQuake(pppScreenQuake* quake, _pppCtrlTable* param2);
void pppFrameScreenQuake(pppScreenQuake *quake, pppScreenQuakeStep *param2, _pppCtrlTable *param3);
void pppRenderScreenQuake(pppScreenQuake* quake, pppScreenQuakeStep* param2, _pppCtrlTable* param3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SCREENQUAKE_H_
