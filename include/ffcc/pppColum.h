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

struct UnkB {
    u32 m_dataValIndex;
    u16 m_initWOrk;
    
    // Extended fields from decompilation
    char pad[4];
    u32 m_stepValue;
    u8 m_arg3;
    char pad2[3];
    char* m_payload;
};

struct UnkC {
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructColum(pppColum* column, UnkC* param_2);
void pppDestructColum(pppColum* column, UnkC* param_2);
void pppFrameColum(pppColum* column, UnkB* param_2, UnkC* param_3);
void pppRenderColum(pppColum* column, UnkB* param_2, UnkC* param_3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCOLUM_H_
