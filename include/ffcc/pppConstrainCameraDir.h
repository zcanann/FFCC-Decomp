#ifndef _FFCC_PPPCONSTRAINCAMERADIR_H_
#define _FFCC_PPPCONSTRAINCAMERADIR_H_

#include "ffcc/partMng.h"

typedef struct pppConstrainCameraDir {
    float field0_0x0;
} pppConstrainCameraDir;

typedef struct pppConstrainCameraDirUnkB {
    int m_graphId;
    float m_dataValIndex;
    float m_initWOrk;
    float m_stepValue;
    char m_arg3;
    char pad[3];
} pppConstrainCameraDirUnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructConstrainCameraDir(pppConstrainCameraDir* param1, _pppCtrlTable* param2);
void pppConstruct2ConstrainCameraDir(pppConstrainCameraDir* param1, _pppCtrlTable* param2);
void pppDestructConstrainCameraDir(_pppPObjLink*, _pppCtrlTable*);
void pppFrameConstrainCameraDir(pppConstrainCameraDir* param1, pppConstrainCameraDirUnkB* param2, _pppCtrlTable* param3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCONSTRAINCAMERADIR_H_

