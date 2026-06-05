#ifndef _FFCC_PPPCONSTRAINCAMERAFORLOC_H_
#define _FFCC_PPPCONSTRAINCAMERAFORLOC_H_

struct _pppCtrlTable;
struct _pppPObjLink;
struct _pppPObject;
struct pppConstrainCameraForLocParams;

typedef _pppPObject pppConstrainCameraForLoc;

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
