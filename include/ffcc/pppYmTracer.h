#ifndef _FFCC_PPP_YMTRACER_H_
#define _FFCC_PPP_YMTRACER_H_

#include <dolphin/types.h>

struct UnkB {
    s32 m_graphId;
    u32 m_dataValIndex;
    s32 m_initWOrk;
    s32 m_stepValue;
    s32 m_arg3;
    u8 m_payload[0x20];
};

struct UnkC {
    u8 _pad[0xC];
    s32* m_serializedDataOffsets;
};

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
