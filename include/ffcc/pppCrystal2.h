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

struct UnkB {
    u32 m_dataValIndex;
    u16 m_initWOrk;
    char pad[6];
    u32 m_stepValue;
    u8 m_arg3;
    char pad2[3];
    u8 m_payload[28];  // payload array
};

struct UnkC {
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void ImageBufferSetPixel_IA8(HSD_ImageBuffer*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
void MakeRefractionMap(HSD_ImageBuffer*);

void pppConstructCrystal2(pppCrystal2* crystal, UnkC* param_2);
void pppDestructCrystal2(pppCrystal2* crystal, UnkC* param_2);
void pppFrameCrystal2(pppCrystal2* crystal, UnkB* param_2, UnkC* param_3);
void pppRenderCrystal2(pppCrystal2* crystal, UnkB* param_2, UnkC* param_3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCRYSTAL2_H_
