#ifndef _FFCC_PPP_YMTRACER_H_
#define _FFCC_PPP_YMTRACER_H_

#include <dolphin/types.h>

// Forward declarations
struct UnkB;
struct UnkC;
struct TRACE_POLYGON;

// Basic structure for pppYmTracer - based on Ghidra analysis
struct pppYmTracer {
    char field0_0x0[8]; // Base object data
    // Additional fields inferred from usage pattern
};

void initTracePolygon(pppYmTracer*, TRACE_POLYGON*);
void copyPolygonData(TRACE_POLYGON*, TRACE_POLYGON*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmTracer(pppYmTracer*, UnkC*);
void pppConstruct2YmTracer(pppYmTracer*, UnkC*);
void pppDestructYmTracer(pppYmTracer*, UnkC*);
void pppFrameYmTracer(pppYmTracer*, UnkB*, UnkC*);
void pppRenderYmTracer(pppYmTracer*, UnkB*, UnkC*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMTRACER_H_
