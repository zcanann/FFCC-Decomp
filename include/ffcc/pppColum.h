#ifndef _FFCC_PPPCOLUM_H_
#define _FFCC_PPPCOLUM_H_

#include "ffcc/partMng.h"

// pppCVector structure
typedef struct pppCVector {
    u8 m_rgba[4];
} pppCVector;

struct pppColum {
    _pppPObject m_object;
};

struct pppColumUnkB {
    u32 m_unk0;            // 0x00
    s32 m_dataValIndex;    // 0x04
    s16 m_initWOrk;        // 0x08
    u16 m_unkA;            // 0x0A
    union {
        u32 m_stepValue;       // 0x0C
        u8 m_baseColor[4];     // 0x0C
    };
    u8 m_arg3;             // 0x10
    u8 m_count;            // 0x11
    u8 m_unk12;            // 0x12
    u8 m_unk13;            // 0x13
    union {
        u8 m_payload[0x19];  // 0x14
        struct {
            f32 m_scaleStepBase;   // 0x14
            f32 m_scaleStepRange;  // 0x18
            f32 m_positionBase;    // 0x1C
            f32 m_positionRange;   // 0x20
            f32 m_fadeDistance;    // 0x24
            u8 m_drawEnvColor0;    // 0x28
            u8 m_drawEnvColor1;    // 0x29
            u8 m_noiseR;           // 0x2A
            u8 m_noiseG;           // 0x2B
            u8 m_noiseB;           // 0x2C
        } m_colum;
        struct {
            u8 m_drawEnvLightTarget;
            u8 m_pad01[0x18];
        } m_lensFlare;
    };
};

struct pppColumValue {
    float m_scaleStep;
    float m_positionScale;
    u8 m_colorR;
    u8 m_colorG;
    u8 m_colorB;
    u8 _padB;
};

struct pppColumFrameWork {
    s16 m_shapeA;
    s16 m_shapeB;
    s16 m_shapeC;
    s16 _pad6;
    pppColumValue* m_values;
};

struct pppColumPositionWork {
    u8 _pad0[0x10];
    Vec m_position;
    u8 _pad1[0x16];
    u8 m_alpha;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructColum(pppColum* column, _pppCtrlTable* param_2);
void pppDestructColum(pppColum* column, _pppCtrlTable* param_2);
void pppFrameColum(pppColum* column, pppColumUnkB* param_2, _pppCtrlTable* param_3);
void pppRenderColum(pppColum* column, pppColumUnkB* param_2, _pppCtrlTable* param_3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCOLUM_H_
