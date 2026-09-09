#ifndef _FFCC_PPP_YMTRACER_H_
#define _FFCC_PPP_YMTRACER_H_

#include "ffcc/pppPart.h"

#include <dolphin/mtx.h>
#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

struct PYmTracer {
    s32 m_graphId;
    s32 m_dataValIndex;
    u32 m_initWOrk;
    s32 m_stepValue;
    u32 m_arg3;
    union {
        u8 m_payload[0x20];
        struct {
            s32 m_arg3WorkOffset;
            u16 m_entryCount;
            u16 m_entryLife;
            u8 m_entryAlpha;
            u8 m_splineCount;
            u8 m_blendMode;
            u8 m_drawEnvColor0;
            u8 m_drawEnvColor1;
            u8 m_pad0D[0x13];
        } m_tracer;
    };
};

typedef PYmTracer pppYmTracerStep;
typedef _pppCtrlTable pppYmTracerCtrl;
typedef _pppPObject pppYmTracer;

struct YmTracerDataOffsets {
    s32 m_workOffset;
    s32 m_colorOffset;
};

struct TRACE_POLYGON {
    Vec from;
    f32 _pad0;
    Vec to;
    u8 colorR;
    u8 colorG;
    u8 colorB;
    u8 alpha;
    s16 life;
    u8 decay;
    u8 _pad21;
    u32 _pad24;
};

struct YmTracerWork {
    Vec from;
    f32 _pad0;
    Vec to;
    f32 _pad1c;
    f32* initWork;
    f32* arg3Work;
    TRACE_POLYGON* entries;
    u16 count;
    u16 _pad2e;
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
