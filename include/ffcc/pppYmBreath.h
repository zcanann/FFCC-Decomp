#ifndef _PPP_YMBREATH_H_
#define _PPP_YMBREATH_H_

struct _pppPObject;
struct _pppCtrlTable;
struct pppYmBreath;
struct PYmBreath;

#ifdef __cplusplus
extern "C" {
#endif

void pppFrameYmBreath(pppYmBreath*, PYmBreath*, _pppCtrlTable*);
void pppRenderYmBreath(pppYmBreath*, PYmBreath*, _pppCtrlTable*);
void pppConstructYmBreath(pppYmBreath*, _pppCtrlTable*);
void pppConstruct2YmBreath(_pppPObject* obj);
void pppDestructYmBreath(pppYmBreath*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMBREATH_H_
