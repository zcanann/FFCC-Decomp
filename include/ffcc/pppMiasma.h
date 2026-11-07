#ifndef _PPP_MIASMA_H_
#define _PPP_MIASMA_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppMiasma;

struct pppMiasmaFrameStep {
    s32 m_graphId;
    u8 m_pad_0x4[0x14];
    s16 m_addPosX;
    s16 m_addPosY;
    s16 m_addPosZ;
    s16 m_addPosW;
    s16 m_addVelX;
    s16 m_addVelY;
    s16 m_addVelZ;
    s16 m_addVelW;
    s16 m_addAccX;
    s16 m_addAccY;
    s16 m_addAccZ;
    s16 m_addAccW;
};

struct pppMiasmaRenderStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    u8 m_initWOrk;
    u8 m_pad_0x09[3];
    f32 m_stepValue;
    u8 m_arg3;
    u8 m_pad_0x11[3];
    union {
        u8 m_payload[0x1f];
        struct Payload {
            u8 m_pad00[0x1C];
            u8 m_alphaOpScale;
            u8 m_useSecondaryMask;
            u8 m_alphaScale;
        } m_miasma;
    };
};

#ifdef __cplusplus
extern "C" {
#endif

void pppRenderMiasma(pppMiasma*, pppMiasmaRenderStep*, _pppCtrlTable*);
void pppConstructMiasma(pppMiasma*, _pppCtrlTable*);
void pppConstruct2Miasma(pppMiasma*, _pppCtrlTable*);
void pppDestructMiasma(pppMiasma*, _pppCtrlTable*);
void pppFrameMiasma(pppMiasma*, pppMiasmaFrameStep*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_MIASMA_H_
