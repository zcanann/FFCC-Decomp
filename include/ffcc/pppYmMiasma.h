#ifndef _FFCC_PPP_YMMIASMA_H_
#define _FFCC_PPP_YMMIASMA_H_

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppYmMiasma;

struct pppYmMiasmaUnkB;
struct YmMiasmaRenderStep;
struct YmMiasmaFrameStep;
struct VYmMiasma;
struct PYmMiasma;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMiasma(pppYmMiasma*, _pppCtrlTable*);
void pppConstruct2YmMiasma(pppYmMiasma*, _pppCtrlTable*);
void pppDestructYmMiasma(pppYmMiasma*, _pppCtrlTable*);
void pppFrameYmMiasma(pppYmMiasma*, YmMiasmaFrameStep*, _pppCtrlTable*);
void pppRenderYmMiasma(pppYmMiasma*, YmMiasmaRenderStep*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMIASMA_H_
