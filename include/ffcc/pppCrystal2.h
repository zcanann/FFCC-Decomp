#ifndef _FFCC_PPPCRYSTAL2_H_
#define _FFCC_PPPCRYSTAL2_H_

#include <dolphin/types.h>

struct HSD_ImageBuffer;

// Forward declarations
struct pppCrystal2 {
    union {
        void* ptr;
        struct {
            u32 m_graphId;
        };
    } field0_0x0;
    
    // Add padding/fields up to the offsets we need
    char pad[0x3C];      // 0x40 - 0x4 = 0x3C bytes
    void* field_0x40;    // pppFMATRIX
    char pad2[0x40];     // 0x84 - 0x40 - 4 = 0x40 bytes
    void* field_0x84;    // texture object area
    void* field_0x88;    // vector area (immediately after field_0x84)
};

struct pppCrystal2UnkB {
    s32 m_graphId;
    s32 m_dataValIndex;
    s32 m_initWOrk;
    f32 _unk0C;
    f32 m_stepValue;
    u8 m_payload[8];
    f32 m_perspectiveScale;
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

