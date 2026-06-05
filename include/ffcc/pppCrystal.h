#ifndef _FFCC_PPPCRYSTAL_H_
#define _FFCC_PPPCRYSTAL_H_

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppCrystal;

struct pppCrystalUnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructCrystal(pppCrystal*, _pppCtrlTable*);
void pppDestructCrystal(pppCrystal*, _pppCtrlTable*);
void pppFrameCrystal(pppCrystal*, pppCrystalUnkB*, _pppCtrlTable*);
void pppRenderCrystal(pppCrystal*, pppCrystalUnkB*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCRYSTAL_H_
