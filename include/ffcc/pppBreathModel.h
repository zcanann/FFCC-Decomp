#ifndef _FFCC_PPBBREATHMODEL_H_
#define _FFCC_PPBBREATHMODEL_H_

struct _pppCtrlTable;
struct pppBreathModel;
struct PBreathModel;

#ifdef __cplusplus
extern "C" {
#endif

void pppFrameBreathModel(pppBreathModel*, PBreathModel*, _pppCtrlTable*);
void pppRenderBreathModel(pppBreathModel*, PBreathModel*, _pppCtrlTable*);
void pppConstructBreathModel(pppBreathModel*, _pppCtrlTable*);
void pppDestructBreathModel(pppBreathModel*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif
