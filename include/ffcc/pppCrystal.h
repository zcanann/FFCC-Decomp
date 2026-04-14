#ifndef _FFCC_PPPCRYSTAL_H_
#define _FFCC_PPPCRYSTAL_H_

#include "ffcc/partMng.h"

#include <dolphin/gx.h>
#include <dolphin/types.h>

struct HSD_ImageBuffer;

struct CrystalRefractionMap {
    void* m_imageData;
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
    _pppPObject m_object;   // 0x0
    u8 m_pad34[0x4C];       // 0x34
    CrystalWork m_work;     // 0x80
    u8 m_color[4];          // 0x88
};

struct pppCrystalUnkB {
    s32 m_graphId;
    s32 m_dataValIndex;
    s32 m_initWOrk;
    float m_stepValue;
    float m_arg3;
    u8 m_payload[6];
};

struct pppCrystalUnkC {
    u8 _pad0[0xC];
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void ImageBufferSetPixel_IA8(struct HSD_ImageBuffer*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
void MakeRefractionMap(struct HSD_ImageBuffer*);
void pppConstructCrystal(struct pppCrystal*, struct pppCrystalUnkC*);
void pppDestructCrystal(struct pppCrystal*, struct pppCrystalUnkC*);
void pppFrameCrystal(struct pppCrystal*, struct pppCrystalUnkB*, struct pppCrystalUnkC*);
void pppRenderCrystal(struct pppCrystal*, struct pppCrystalUnkB*, struct pppCrystalUnkC*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCRYSTAL_H_
