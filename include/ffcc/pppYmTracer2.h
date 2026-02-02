#ifndef _FFCC_PPP_YMTRACER2_H_
#define _FFCC_PPP_YMTRACER2_H_

#include <dolphin/types.h>

struct PYmTracer2;
struct TRACE_POLYGON;

// Forward declarations
struct UnkB;
struct UnkC;

struct pppYmTracer2 {
    // Based on Ghidra analysis - contains serialized data
    u8* m_serializedData;
    // Add padding for pppPObject structure
    char pad[0x80]; // Placeholder - actual structure size may differ
};

#ifdef __cplusplus
extern "C" {
#endif

void initTracePolygon(PYmTracer2*, TRACE_POLYGON*);
void copyPolygonData(TRACE_POLYGON*, TRACE_POLYGON*);
void pppConstructYmTracer2(pppYmTracer2*, UnkC*);
void pppConstruct2YmTracer2(pppYmTracer2*, UnkC*);
void pppDestructYmTracer2(pppYmTracer2*, UnkC*);
void pppFrameYmTracer2(pppYmTracer2*, UnkB*, UnkC*);
void pppRenderYmTracer2(pppYmTracer2*, UnkB*, UnkC*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMTRACER2_H_
