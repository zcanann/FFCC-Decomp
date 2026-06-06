#ifndef _FFCC_PPPCRYSTAL_H_
#define _FFCC_PPPCRYSTAL_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppCrystal;

struct CrystalDataOffsets {
    s32 _unused0;
    s32 m_colorBlockOffset;
    s32 m_workOffset;
};

struct pppCrystalStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    s32 m_initWOrk;
    float m_stepValue;
    float m_arg3;
    union {
        u8 m_payload[6];
        struct Payload {
            u8 m_refractionMode;
            u8 m_blendMode;
            u8 m_drawFlag;
            u8 m_zMode;
            u8 m_drawEnvColor0;
            u8 m_drawEnvColor1;
        } m_crystal;
    };
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructCrystal(pppCrystal*, _pppCtrlTable*);
void pppDestructCrystal(pppCrystal*, _pppCtrlTable*);
void pppFrameCrystal(pppCrystal*, pppCrystalStep*, _pppCtrlTable*);
void pppRenderCrystal(pppCrystal*, pppCrystalStep*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCRYSTAL_H_
