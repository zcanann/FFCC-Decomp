#ifndef _FFCC_PPPCONSTRAINCAMERADIR_H_
#define _FFCC_PPPCONSTRAINCAMERADIR_H_

#include "ffcc/partMng.h"

typedef _pppPObject pppConstrainCameraDir;

struct ConstrainCameraDirDataOffsets {
    s32 m_workOffset;
};

struct pppConstrainCameraDirStep {
    s32 m_graphId;
    f32 m_dataValIndex;
    f32 m_initWOrk;
    f32 m_stepValue;
    u8 m_applyPosition;
    u8 m_applyCameraInverse;
    u8 m_pad12[2];
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructConstrainCameraDir(pppConstrainCameraDir* param1, _pppCtrlTable* param2);
void pppConstruct2ConstrainCameraDir(pppConstrainCameraDir* param1, _pppCtrlTable* param2);
void pppDestructConstrainCameraDir(_pppPObjLink*, _pppCtrlTable*);
void pppFrameConstrainCameraDir(pppConstrainCameraDir* param1, pppConstrainCameraDirStep* param2, _pppCtrlTable* param3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCONSTRAINCAMERADIR_H_
