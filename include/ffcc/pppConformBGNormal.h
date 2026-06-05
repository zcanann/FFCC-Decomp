#ifndef _FFCC_PPPCONFORMBGNORMAL_H_
#define _FFCC_PPPCONFORMBGNORMAL_H_

struct _pppCtrlTable;
struct _pppPObject;
struct pppConformBGNormalUnkB;

typedef _pppPObject pppConformBGNormal;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructConformBGNormal(pppConformBGNormal* conformBG, struct _pppCtrlTable* data);
void pppFrameConformBGNormal(pppConformBGNormal* conformBG, struct pppConformBGNormalUnkB* param2, struct _pppCtrlTable* data);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCONFORMBGNORMAL_H_
