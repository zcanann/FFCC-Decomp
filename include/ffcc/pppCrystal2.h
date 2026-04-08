#ifndef _FFCC_PPPCRYSTAL2_H_
#define _FFCC_PPPCRYSTAL2_H_

#include "ffcc/partMng.h"

#include <dolphin/gx.h>
#include <dolphin/types.h>

struct HSD_ImageBuffer;

struct Crystal2RefractionMap {
    void* m_imageData;
    GXTexFmt m_format;
    u32 m_width;
    u32 m_height;
    u32 m_imageCount;
    u32 m_bufferSize;
};

struct Crystal2Work {
    Crystal2RefractionMap* m_refractionMap;
    GXTexObj* m_refractionTexObj;
};

// Forward declarations
struct pppCrystal2 {
    _pppPObject m_object; // 0x0
    u8 m_pad34[0x4C];     // 0x34
    Crystal2Work m_work;  // 0x80
    u8 m_color[4];        // 0x88
};

struct pppCrystal2UnkB {
    s32 m_graphId;
    s32 m_dataValIndex;
    s32 m_initWOrk;
    f32 m_stepValue;
    f32 m_arg3;
    u8 m_payload[12];
};

struct pppCrystal2UnkC {
    u8 _pad0[0xC];
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void ImageBufferSetPixel_IA8(HSD_ImageBuffer*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
void MakeRefractionMap(HSD_ImageBuffer*);

void pppConstructCrystal2(pppCrystal2* crystal, pppCrystal2UnkC* param_2);
void pppDestructCrystal2(pppCrystal2* crystal, pppCrystal2UnkC* param_2);
void pppFrameCrystal2(pppCrystal2* crystal, pppCrystal2UnkB* param_2, pppCrystal2UnkC* param_3);
void pppRenderCrystal2(pppCrystal2* crystal, pppCrystal2UnkB* param_2, pppCrystal2UnkC* param_3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCRYSTAL2_H_
