#ifndef _FFCC_PPP_YMTRACER2_H_
#define _FFCC_PPP_YMTRACER2_H_

#include "ffcc/partMng.h"

#include <dolphin/types.h>

struct PYmTracer2;
struct TRACE_POLYGON;

struct pppYmTracer2UnkB {
    s32 m_graphId;
    s32 m_dataValIndex;
    s32 m_initWork;
    s32 m_stepValue;
    s32 m_arg3;
    union {
        u8 m_payload[0x20];
        struct {
            s32 m_arg3WorkOffset;    // 0x00
            u16 m_entryCount;        // 0x04
            u16 m_entryLife;         // 0x06
            u8 m_entryAlpha;         // 0x08
            u8 m_historyFrameCount;  // 0x09
            u8 m_blendMode;          // 0x0A
            u8 m_drawEnvColor0;      // 0x0B
            u8 m_drawEnvColor1;      // 0x0C
            u8 m_useTextureTev;      // 0x0D
            u8 m_pad0E[0x12];        // 0x0E
        } m_tracer;
    };
};

struct pppYmTracer2UnkC {
    u8 _pad[0xC];
    s32* m_serializedDataOffsets;
};

struct pppYmTracer2 {
    _pppPObject m_object;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmTracer2(pppYmTracer2*, pppYmTracer2UnkC*);
void pppConstruct2YmTracer2(pppYmTracer2*, pppYmTracer2UnkC*);
void pppDestructYmTracer2(pppYmTracer2*, pppYmTracer2UnkC*);
void pppFrameYmTracer2(pppYmTracer2*, pppYmTracer2UnkB*, pppYmTracer2UnkC*);
void pppRenderYmTracer2(pppYmTracer2*, pppYmTracer2UnkB*, pppYmTracer2UnkC*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMTRACER2_H_
