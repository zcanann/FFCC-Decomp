#ifndef _FFCC_PPPCRYSTAL_H_
#define _FFCC_PPPCRYSTAL_H_

#include "ffcc/partMng.h"

#include <dolphin/gx.h>
#include <dolphin/types.h>

struct CrystalRefractionMap {
    u8* m_imageData;
    GXTexFmt m_format;
    u32 m_width;
    u32 m_height;
    u32 m_imageCount;
    u32 m_bufferSize;
};

struct CrystalWork {
    CrystalRefractionMap* m_refractionMap;
    GXTexObj* m_refractionTexObj;
};

struct pppCrystal {
    _pppPObject m_object; // 0x0
};

struct pppCrystalUnkB {
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

void pppConstructCrystal(struct pppCrystal*, struct _pppCtrlTable*);
void pppDestructCrystal(struct pppCrystal*, struct _pppCtrlTable*);
void pppFrameCrystal(struct pppCrystal*, struct pppCrystalUnkB*, struct _pppCtrlTable*);
void pppRenderCrystal(struct pppCrystal*, struct pppCrystalUnkB*, struct _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCRYSTAL_H_
