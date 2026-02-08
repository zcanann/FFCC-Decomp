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

typedef struct pppConstrainCameraForLocData {
    int m_unk0;
    float m_unk4;
    float m_unk8;
    int* m_serializedDataOffsets;
} pppConstrainCameraForLocData;

int CC_BeforeCalcMatrixCallback(CChara::CModel*, void*, void*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructConstrainCameraForLoc(void);
void pppConstruct2ConstrainCameraForLoc(pppConstrainCameraForLoc*, pppConstrainCameraForLocData*);
void pppDestructConstrainCameraForLoc(pppConstrainCameraForLoc*, pppConstrainCameraForLocParams*,
                                      pppConstrainCameraForLocData*);
void fn_80167EC4(pppConstrainCameraForLoc*, pppConstrainCameraForLocData*);
void pppFrameConstrainCameraForLoc(void);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCONSTRAINCAMERAFORLOC_H_
