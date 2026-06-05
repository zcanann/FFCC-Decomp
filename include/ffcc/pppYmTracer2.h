#ifndef _FFCC_PPP_YMTRACER2_H_
#define _FFCC_PPP_YMTRACER2_H_

struct _pppCtrlTable;
struct _pppPObject;
struct pppYmTracer2UnkB;

typedef _pppPObject pppYmTracer2;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmTracer2(pppYmTracer2*, _pppCtrlTable*);
void pppConstruct2YmTracer2(pppYmTracer2*, _pppCtrlTable*);
void pppDestructYmTracer2(pppYmTracer2*, _pppCtrlTable*);
void pppFrameYmTracer2(pppYmTracer2*, pppYmTracer2UnkB*, _pppCtrlTable*);
void pppRenderYmTracer2(pppYmTracer2*, pppYmTracer2UnkB*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMTRACER2_H_
