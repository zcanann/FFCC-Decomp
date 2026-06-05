#ifndef _FFCC_PPPCONSTRAINCAMERAFORLOC_H_
#define _FFCC_PPPCONSTRAINCAMERAFORLOC_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObjLink;
struct _pppPObject;

struct pppConstrainCameraForLocParams {
    s32 m_graphId;
    f32 m_dataValIndex;
    f32 m_initWork;
    f32 m_stepValue;
};

typedef _pppPObject pppConstrainCameraForLoc;

#ifdef __cplusplus
extern "C" {
#endif

void pppDestructConstrainCameraForLoc(_pppPObjLink*, _pppCtrlTable*);
void pppConstruct2ConstrainCameraForLoc(pppConstrainCameraForLoc*, _pppCtrlTable*);
void pppConstructConstrainCameraForLoc(pppConstrainCameraForLoc*, _pppCtrlTable*);
void pppFrameConstrainCameraForLoc(pppConstrainCameraForLoc*, pppConstrainCameraForLocParams*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCONSTRAINCAMERAFORLOC_H_
