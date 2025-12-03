#ifndef _FFCC_PPPCONSTRAINCAMERAFORLOC_H_
#define _FFCC_PPPCONSTRAINCAMERAFORLOC_H_

#include "ffcc/chara.h"

void CC_BeforeCalcMatrixCallback(CChara::CModel*, void*, void*);
void pppConstructConstrainCameraForLoc(void);
void pppConstruct2ConstrainCameraForLoc(void);
void pppDestructConstrainCameraForLoc(void);
void pppFrameConstrainCameraForLoc(void);

#endif // _FFCC_PPPCONSTRAINCAMERAFORLOC_H_
