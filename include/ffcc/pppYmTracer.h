#ifndef _FFCC_PPP_YMTRACER_H_
#define _FFCC_PPP_YMTRACER_H_

struct PYmTracer;
struct TRACE_POLYGON;

void initTracePolygon(PYmTracer*, TRACE_POLYGON*);
void copyPolygonData(TRACE_POLYGON*, TRACE_POLYGON*);
void pppConstructYmTracer(void);
void pppConstruct2YmTracer(void);
void pppDestructYmTracer(void);
void pppFrameYmTracer(void);
void pppRenderYmTracer(void);

#endif // _FFCC_PPP_YMTRACER_H_
