#ifndef _FFCC_PPP_YMTRACER2_H_
#define _FFCC_PPP_YMTRACER2_H_

struct PYmTracer2;
struct TRACE_POLYGON;

void initTracePolygon(PYmTracer2*, TRACE_POLYGON*);
void copyPolygonData(TRACE_POLYGON*, TRACE_POLYGON*);
void pppConstructYmTracer2(void);
void pppConstruct2YmTracer2(void);
void pppDestructYmTracer2(void);
void pppFrameYmTracer2(void);
void pppRenderYmTracer2(void);
void GXEnd(void);
void GXSetTexCoordGen(void);

#endif // _FFCC_PPP_YMTRACER2_H_
