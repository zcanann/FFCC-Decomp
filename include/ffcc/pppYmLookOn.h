#ifndef _PPP_YMLOOKON_H_
#define _PPP_YMLOOKON_H_

struct _pppCtrlTable;
struct _pppPObject;
struct pppYmLookOnStep;

typedef _pppPObject pppYmLookOn;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmLookOn(pppYmLookOn* pppYmLookOn, struct _pppCtrlTable* param_2);
void pppFrameYmLookOn(pppYmLookOn* pppYmLookOn, struct pppYmLookOnStep* param_2, struct _pppCtrlTable* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMLOOKON_H_
