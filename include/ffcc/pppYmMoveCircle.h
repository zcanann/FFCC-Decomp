#ifndef _FFCC_PPP_YMMOVECIRCLE_H_
#define _FFCC_PPP_YMMOVECIRCLE_H_

struct _pppCtrlTable;
struct _pppPObject;
struct pppYmMoveCircleStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMoveCircle(struct _pppPObject* basePtr, struct _pppCtrlTable* offsetData);
void pppFrameYmMoveCircle(struct _pppPObject* basePtr, struct pppYmMoveCircleStep* stepData, struct _pppCtrlTable* offsetData);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMOVECIRCLE_H_
