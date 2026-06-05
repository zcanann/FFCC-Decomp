#ifndef _FFCC_PPPCRYSTAL2_H_
#define _FFCC_PPPCRYSTAL2_H_

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppCrystal2;

struct pppCrystal2UnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructCrystal2(pppCrystal2* crystal, _pppCtrlTable* param_2);
void pppDestructCrystal2(pppCrystal2* crystal, _pppCtrlTable* param_2);
void pppFrameCrystal2(pppCrystal2* crystal, pppCrystal2UnkB* param_2, _pppCtrlTable* param_3);
void pppRenderCrystal2(pppCrystal2* crystal, pppCrystal2UnkB* param_2, _pppCtrlTable* param_3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCRYSTAL2_H_
