#ifndef _PPP_MIASMA_H_
#define _PPP_MIASMA_H_

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppMiasma;

struct pppMiasmaFrameStep;
struct pppMiasmaRenderStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppRenderMiasma(pppMiasma*, pppMiasmaRenderStep*, _pppCtrlTable*);
void pppConstructMiasma(pppMiasma*, _pppCtrlTable*);
void pppConstruct2Miasma(pppMiasma*, _pppCtrlTable*);
void pppDestructMiasma(pppMiasma*, _pppCtrlTable*);
void pppFrameMiasma(pppMiasma*, pppMiasmaFrameStep*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_MIASMA_H_
