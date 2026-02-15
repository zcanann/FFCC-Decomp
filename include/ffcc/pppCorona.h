#ifndef _FFCC_PPPCORONA_H_
#define _FFCC_PPPCORONA_H_

#include <dolphin/types.h>

struct pppCorona {
    union {
        void* ptr;
        struct {
            u32 m_graphId;
        };
    } field0_0x0;
};

struct UnkC {
    u8 _pad0[0xC];
    s32* m_serializedDataOffsets;
};

struct CoronaParam {
    s32 m_graphId;
    s32 m_dataValIndex;
    u8 m_colorR;
    u8 m_colorG;
    u8 m_colorB;
    s16 m_shapeStep;
    float m_distMin;
    float m_distMax;
    float m_distRange;
    float m_addX;
    float m_addY;
    float m_addZ;
    u8 m_blendMode;
    u8 m_drawB;
    u8 m_drawA;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructCorona(pppCorona* param1, UnkC* param2);
void pppDestructCorona(void);
void pppFrameCorona(pppCorona* param1, CoronaParam* param2, UnkC* param3);
void pppRenderCorona(pppCorona* param1, CoronaParam* param2, UnkC* param3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCORONA_H_
