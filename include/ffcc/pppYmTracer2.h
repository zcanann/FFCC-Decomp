#ifndef _FFCC_PPP_YMTRACER2_H_
#define _FFCC_PPP_YMTRACER2_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

struct pppYmTracer2Step {
    s32 m_graphId;
    s32 m_dataValIndex;
    s32 m_initWork;
    s32 m_stepValue;
    s32 m_arg3;
    union {
        u8 m_payload[0x20];
        struct {
            s32 m_arg3WorkOffset;
            u16 m_entryCount;
            u16 m_entryLife;
            u8 m_entryAlpha;
            u8 m_historyFrameCount;
            u8 m_blendMode;
            u8 m_drawEnvColor0;
            u8 m_drawEnvColor1;
            u8 m_useTextureTev;
            u8 m_pad0E[0x12];
        } m_tracer;
    };
};

typedef _pppPObject pppYmTracer2;

struct YmTracer2DataOffsets {
    s32 m_workOffset;
    s32 m_colorOffset;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmTracer2(pppYmTracer2*, _pppCtrlTable*);
void pppConstruct2YmTracer2(pppYmTracer2*, _pppCtrlTable*);
void pppDestructYmTracer2(pppYmTracer2*, _pppCtrlTable*);
void pppFrameYmTracer2(pppYmTracer2*, pppYmTracer2Step*, _pppCtrlTable*);
void pppRenderYmTracer2(pppYmTracer2*, pppYmTracer2Step*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMTRACER2_H_
