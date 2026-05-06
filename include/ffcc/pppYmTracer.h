#ifndef _FFCC_PPP_YMTRACER_H_
#define _FFCC_PPP_YMTRACER_H_

#include "ffcc/partMng.h"

#include <dolphin/types.h>

struct pppYmTracerUnkB {
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

struct pppYmTracerUnkC {
    u8 _pad[0xC];
    s32* m_serializedDataOffsets;
};

struct TRACE_POLYGON;

struct pppYmTracer {
    u8 m_header[0xC];
    s32 m_graphId;
    pppFMATRIX m_localMatrix;
    pppFMATRIX m_drawMatrix;
    u8 m_pad70[0x10];
    u8 m_serializedData[1];
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmTracer(pppYmTracer*, pppYmTracerUnkC*);
void pppConstruct2YmTracer(pppYmTracer*, pppYmTracerUnkC*);
void pppDestructYmTracer(pppYmTracer*, pppYmTracerUnkC*);
void pppFrameYmTracer(pppYmTracer*, pppYmTracerUnkB*, pppYmTracerUnkC*);
void pppRenderYmTracer(pppYmTracer*, pppYmTracerUnkB*, pppYmTracerUnkC*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMTRACER_H_
