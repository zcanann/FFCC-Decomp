#ifndef _PPPEMISSION_H_
#define _PPPEMISSION_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppEmission;

struct PEmissionPayload {
    f32 m_scaleAccelerationAdd;
    f32 m_scaleRandomRange;
    u8 m_blendMode;
    u8 m_particleMode;
    u8 m_texGenMode;
    u8 m_targetAlpha;
    u8 m_fadeOutFrames;
    u8 m_lifeJitterFrames;
    u8 m_holdFrames;
    u8 m_fadeInFrames;
    u8 m_pad10[0x10];
};

struct PEmission {
    s32 m_graphId;
    s32 m_dataValIndex;
    u8 m_initWOrk;
    u8 m_pad08[3];
    f32 m_stepValue;
    f32 m_arg3;
    union {
        u8 m_payload[0x20];
        PEmissionPayload m_emission;
    };
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructEmission(pppEmission*, _pppCtrlTable*);
void pppConstruct2Emission(pppEmission*, _pppCtrlTable*);
void pppDestructEmission(pppEmission*, _pppCtrlTable*);
void pppFrameEmission(pppEmission*, PEmission*, _pppCtrlTable*);
void pppRenderEmission(pppEmission*, PEmission*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPPEMISSION_H_
