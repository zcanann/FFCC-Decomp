#ifndef _FFCC_PPPCONSTRAINCAMERAFORLOC_H_
#define _FFCC_PPPCONSTRAINCAMERAFORLOC_H_

#include "ffcc/chara.h"

#ifdef __cplusplus
extern "C" {
#endif

void CC_BeforeCalcMatrixCallback(CChara::CModel*, void*, void*);
void pppConstructConstrainCameraForLoc(void);
void pppConstruct2ConstrainCameraForLoc(void);
void pppDestructConstrainCameraForLoc(void);
void pppFrameConstrainCameraForLoc(void);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCONSTRAINCAMERAFORLOC_H_
