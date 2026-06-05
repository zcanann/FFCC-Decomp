#ifndef _FFCC_PPPCHARAZENVCTRL_H_
#define _FFCC_PPPCHARAZENVCTRL_H_

struct _pppCtrlTable;
struct _pppPObjLink;
struct _pppPObject;
struct pppCharaZEnvCtrlUnkB;

typedef _pppPObject pppCharaZEnvCtrl;

#ifdef __cplusplus
extern "C" {
#endif

void pppConCharaZEnvCtrl(_pppPObjLink*, _pppCtrlTable*);
void pppDesCharaZEnvCtrl(_pppPObjLink*, _pppCtrlTable*);
void pppFrameCharaZEnvCtrl(pppCharaZEnvCtrl*, pppCharaZEnvCtrlUnkB*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCHARAZENVCTRL_H_
