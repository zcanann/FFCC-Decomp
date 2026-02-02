#ifndef _FFCC_PPPCRYSTAL_H_
#define _FFCC_PPPCRYSTAL_H_

#include <dolphin/types.h>

struct HSD_ImageBuffer;

struct pppCrystal {
    union {
        void* ptr;
        struct {
            u32 m_graphId;
        };
    } field0_0x0;
    
    // Fields based on Ghidra decomp usage
    char pad[0x3C];
    float field_0x40;  // Used as pppFMATRIX* in render
    char pad2[0x2C];
    void* field_0x70;  // Used as Vec* in render
    char pad3[0x10];
    void* field_0x84;  // Used for texture in render
    float field_0x88; // Used as pppCVECTOR* in render
};

struct UnkB {
    u32 m_dataValIndex;
    u16 m_initWOrk;
    
    // Extended fields from decompilation
    char pad[2];
    float m_stepValue;
    u8 m_arg3;
    u8 m_payload[6]; // Array of payload bytes
    char pad2[1];
};

struct UnkC {
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void ImageBufferSetPixel_IA8(struct HSD_ImageBuffer*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
void MakeRefractionMap(struct HSD_ImageBuffer*);
void pppConstructCrystal(struct pppCrystal*, struct UnkC*);
void pppDestructCrystal(struct pppCrystal*, struct UnkC*);
void pppFrameCrystal(struct pppCrystal*, struct UnkB*, struct UnkC*);
void pppRenderCrystal(struct pppCrystal*, struct UnkB*, struct UnkC*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCRYSTAL_H_
