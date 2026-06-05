#ifndef _FFCC_PPP_YMTRACER_H_
#define _FFCC_PPP_YMTRACER_H_

struct _pppCtrlTable;
struct _pppPObject;
struct pppYmTracerStep;

typedef _pppCtrlTable pppYmTracerCtrl;
typedef _pppPObject pppYmTracer;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmTracer(pppYmTracer*, pppYmTracerCtrl*);
void pppConstruct2YmTracer(pppYmTracer*, pppYmTracerCtrl*);
void pppDestructYmTracer(pppYmTracer*, pppYmTracerCtrl*);
void pppFrameYmTracer(pppYmTracer*, pppYmTracerStep*, pppYmTracerCtrl*);
void pppRenderYmTracer(pppYmTracer*, pppYmTracerStep*, pppYmTracerCtrl*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMTRACER_H_
