#ifndef _FFCC_PPP_YMMOVEPARABOLA_H_
#define _FFCC_PPP_YMMOVEPARABOLA_H_

struct _pppCtrlTable;
struct pppYmMoveParabola;
struct pppYmMoveParabolaUnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMoveParabola(struct pppYmMoveParabola* basePtr, _pppCtrlTable* dataPtr);
void pppFrameYmMoveParabola(struct pppYmMoveParabola* basePtr, struct pppYmMoveParabolaUnkB* stepData, _pppCtrlTable* offsetData);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMOVEPARABOLA_H_
