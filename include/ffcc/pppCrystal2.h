#ifndef _FFCC_PPPCRYSTAL2_H_
#define _FFCC_PPPCRYSTAL2_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppCrystal2;

struct Crystal2DataOffsets {
    s32 _unused0;
    s32 m_colorBlockOffset;
    s32 m_workOffset;
};

struct pppCrystal2Step {
    s32 m_graphId;
    s32 m_dataValIndex;
    s32 m_initWOrk;
    f32 m_stepValue;
    f32 m_arg3;
    union {
        u8 m_payload[8];
        struct Payload {
            u8 m_refractionMode;
            u8 m_blendMode;
            u8 m_drawFlag;
            u8 m_zMode;
            u8 m_drawEnvColor0;
            u8 m_drawEnvColor1;
            u8 m_pad06[2];
        } m_crystal;
    };
    f32 m_perspectiveScale;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructCrystal2(pppCrystal2*, _pppCtrlTable*);
void pppDestructCrystal2(pppCrystal2*, _pppCtrlTable*);
void pppFrameCrystal2(pppCrystal2*, pppCrystal2Step*, _pppCtrlTable*);
void pppRenderCrystal2(pppCrystal2*, pppCrystal2Step*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCRYSTAL2_H_
