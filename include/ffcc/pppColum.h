#ifndef _FFCC_PPPCOLUM_H_
#define _FFCC_PPPCOLUM_H_

#include <dolphin/types.h>
#include <dolphin/mtx.h>

// pppCVector structure
typedef struct pppCVector {
    u8 m_rgba[4];
} pppCVector;

struct pppColum {
    union {
        void* ptr;
        struct {
            u32 m_graphId;
        };
    } field0_0x0;
    
    // Add padding/fields up to the offsets we need
    char pad[0x82];
    u16 field_0x82;
    char pad2[0x88 - 0x82 - 2];
    void* field_0x88;
    char pad3[0x90 - 0x88 - 4];
    float field_0x90;
    float field_0x94;
    float field_0x98;
    char pad4[0xb2 - 0x98 - 4];
    u8 field_0xb2;
};

struct pppColumUnkB {
    u32 m_unk0;            // 0x00
    s32 m_dataValIndex;    // 0x04
    s16 m_initWOrk;        // 0x08
    u16 m_unkA;            // 0x0A
    u32 m_stepValue;       // 0x0C
    u8 m_arg3;             // 0x10
    u8 m_count;            // 0x11
    u8 m_unk12;            // 0x12
    u8 m_unk13;            // 0x13
    char m_payload[0x19];  // 0x14
};

struct pppColumUnkC {
    u8 _pad[0xC];
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructColum(pppColum* column, pppColumUnkC* param_2);
void pppDestructColum(pppColum* column, pppColumUnkC* param_2);
void pppFrameColum(pppColum* column, pppColumUnkB* param_2, pppColumUnkC* param_3);
void pppRenderColum(pppColum* column, pppColumUnkB* param_2, pppColumUnkC* param_3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCOLUM_H_
