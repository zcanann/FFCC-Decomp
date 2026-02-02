#ifndef _FFCC_PPPBLURCHARA_H_
#define _FFCC_PPPBLURCHARA_H_

#include "ffcc/chara.h"

#ifdef __cplusplus
extern "C" {
#endif

void BlurChara_SetBeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int);
void BlurChara_AfterDrawModelCallback(CChara::CModel*, void*, void*);
void pppConstructBlurChara(void);
void pppDestructBlurChara(void);
void pppFrameBlurChara(void);
void pppRenderBlurChara(void);

#ifdef __cplusplus
}
#endif

#endif
