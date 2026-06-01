#ifndef _PPP_LERPPOS_H_
#define _PPP_LERPPOS_H_

struct _pppPObject;
struct _pppCtrlTable;
struct pppLerpPosStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructLerpPos(_pppPObject* object, _pppCtrlTable* ctrl);
void pppDestructLerpPos(_pppPObject* object, _pppCtrlTable* ctrl);
void pppFrameLerpPos(_pppPObject* object, pppLerpPosStep* step, _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_LERPPOS_H_
