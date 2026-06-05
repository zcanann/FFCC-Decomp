#ifndef _FFCC_PPPBLURCHARA_H_
#define _FFCC_PPPBLURCHARA_H_

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppBlurChara;

struct pppBlurCharaUnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructBlurChara(pppBlurChara*, _pppCtrlTable*);
void pppDestructBlurChara(pppBlurChara*, _pppCtrlTable*);
void pppFrameBlurChara(pppBlurChara*, pppBlurCharaUnkB*, _pppCtrlTable*);
void pppRenderBlurChara(pppBlurChara*, pppBlurCharaUnkB*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif
