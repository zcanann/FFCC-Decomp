#ifndef _PPP_YMLOOKON_H_
#define _PPP_YMLOOKON_H_

struct _pppCtrlTable;
struct pppYmLookOn;
struct pppYmLookOnStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmLookOn(struct pppYmLookOn* pppYmLookOn, struct _pppCtrlTable* param_2);
void pppFrameYmLookOn(struct pppYmLookOn* pppYmLookOn, struct pppYmLookOnStep* param_2, struct _pppCtrlTable* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMLOOKON_H_
