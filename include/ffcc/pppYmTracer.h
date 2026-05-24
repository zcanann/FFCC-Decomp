#ifndef _FFCC_PPP_YMTRACER_H_
#define _FFCC_PPP_YMTRACER_H_

#include "ffcc/partMng.h"

#include <dolphin/types.h>

struct pppYmTracerStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    u32 m_initWOrk;
    s32 m_stepValue;
    u32 m_arg3;
    union {
        u8 m_payload[0x20];
        struct {
            s32 m_arg3WorkOffset;   // 0x00
            u16 m_entryCount;       // 0x04
            u16 m_entryLife;        // 0x06
            u8 m_entryAlpha;        // 0x08
            u8 m_splineCount;       // 0x09
            u8 m_blendMode;         // 0x0A
            u8 m_drawEnvColor0;     // 0x0B
            u8 m_drawEnvColor1;     // 0x0C
            u8 m_pad0D[0x13];       // 0x0D
        } m_tracer;
    };
};

struct pppYmTracerCtrl {
    u8 _pad[0xC];
    s32* m_serializedDataOffsets;
};

struct TRACE_POLYGON;

struct pppYmTracer {
    _pppPObject m_object;
};

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
