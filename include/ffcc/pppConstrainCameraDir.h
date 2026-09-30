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

void pppConstructConstrainCameraDir(pppConstrainCameraDir* constrainCameraDir, _pppCtrlTable* ctrl);
void pppConstruct2ConstrainCameraDir(pppConstrainCameraDir* constrainCameraDir, _pppCtrlTable* ctrl);
void pppDestructConstrainCameraDir(_pppPObjLink*, _pppCtrlTable*);
void pppFrameConstrainCameraDir(pppConstrainCameraDir* constrainCameraDir, pppConstrainCameraDirStep* step,
                                _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCONSTRAINCAMERADIR_H_
