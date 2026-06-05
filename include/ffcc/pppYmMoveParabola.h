#ifndef _FFCC_PPP_YMMOVEPARABOLA_H_
#define _FFCC_PPP_YMMOVEPARABOLA_H_

struct _pppCtrlTable;
struct _pppPObject;
struct pppYmMoveParabolaUnkB;

typedef _pppPObject pppYmMoveParabola;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMoveParabola(pppYmMoveParabola* basePtr, _pppCtrlTable* dataPtr);
void pppFrameYmMoveParabola(pppYmMoveParabola* basePtr, struct pppYmMoveParabolaUnkB* stepData, _pppCtrlTable* offsetData);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMOVEPARABOLA_H_
