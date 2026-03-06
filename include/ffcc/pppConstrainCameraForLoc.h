#ifndef _FFCC_PPPCONSTRAINCAMERAFORLOC_H_
#define _FFCC_PPPCONSTRAINCAMERAFORLOC_H_

#include "ffcc/chara.h"
#include "ffcc/partMng.h"
#include "ffcc/pppYmEnv.h"

class CGObject;

typedef struct pppConstrainCameraForLoc {
    float field0_0x0;
} pppConstrainCameraForLoc;

typedef struct pppConstrainCameraForLocParams {
    int m_graphId;
    float m_dataValIndex;
    float m_initWork;
    float m_stepValue;
} pppConstrainCameraForLocParams;

int CC_BeforeCalcMatrixCallback(CChara::CModel*, void*, void*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructConstrainCameraForLoc(_pppPObjLink*, _pppCtrlTable*);
void pppConstruct2ConstrainCameraForLoc(pppConstrainCameraForLoc*, _pppCtrlTable*);
void pppDestructConstrainCameraForLoc(pppConstrainCameraForLoc*, pppConstrainCameraForLocParams*,
                                      _pppCtrlTable*);
void pppConstruct3ConstrainCameraForLoc(pppConstrainCameraForLoc*, _pppCtrlTable*);
void pppFrameConstrainCameraForLoc(_pppPObject*, void*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCONSTRAINCAMERAFORLOC_H_
