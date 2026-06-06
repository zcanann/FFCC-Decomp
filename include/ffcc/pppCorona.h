#ifndef _FFCC_PPPCORONA_H_
#define _FFCC_PPPCORONA_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct CoronaDataOffsets {
    s32 _unused0;
    s32 _unused1;
    s32 m_vecWorkOffset;
    s32 m_workOffset;
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

void pppConstructCorona(_pppPObject* object, _pppCtrlTable* ctrl);
void pppDestructCorona(_pppPObject* object, _pppCtrlTable* ctrl);
void pppFrameCorona(_pppPObject* object, CoronaParam* data, _pppCtrlTable* ctrl);
void pppRenderCorona(_pppPObject* object, CoronaParam* data, _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCORONA_H_
