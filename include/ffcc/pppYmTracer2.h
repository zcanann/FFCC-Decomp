#ifndef _FFCC_PPP_YMTRACER2_H_
#define _FFCC_PPP_YMTRACER2_H_

#include <dolphin/types.h>

struct PYmTracer2;
struct TRACE_POLYGON;

struct UnkB {
    u32 m_dataValIndex;
};

struct UnkC {
    u8 _pad[0xC];
    s32* m_serializedDataOffsets;
};

struct pppYmTracer2 {
    u8 _pad[0x80];
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
