#ifndef _PPP_WDRAWMATRIXFRONTLOOP_H_
#define _PPP_WDRAWMATRIXFRONTLOOP_H_

struct _pppPObject;
struct _pppCtrlTable;

#ifdef __cplusplus
extern "C" {
#endif

void pppWDrawMatrixFrontLoop(struct _pppPObject* object, void* stepData, struct _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_WDRAWMATRIXFRONTLOOP_H_
