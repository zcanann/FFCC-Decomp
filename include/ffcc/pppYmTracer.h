#ifndef _FFCC_PPP_YMTRACER_H_
#define _FFCC_PPP_YMTRACER_H_

struct pppYmTracer;
struct UnkB;
struct UnkC;
struct TRACE_POLYGON;

void initTracePolygon(pppYmTracer*, TRACE_POLYGON*);
void copyPolygonData(TRACE_POLYGON*, TRACE_POLYGON*);
void pppConstructYmTracer(pppYmTracer*, UnkC*);
void pppConstruct2YmTracer(pppYmTracer*, UnkC*);
void pppDestructYmTracer(pppYmTracer*, UnkC*);
void pppFrameYmTracer(pppYmTracer*, UnkB*, UnkC*);
void pppRenderYmTracer(pppYmTracer*, UnkB*, UnkC*);

#endif // _FFCC_PPP_YMTRACER_H_
