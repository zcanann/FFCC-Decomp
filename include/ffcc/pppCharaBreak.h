#ifndef _FFCC_PPPCHARABREAK_H_
#define _FFCC_PPPCHARABREAK_H_

#include "ffcc/chara.h"
#include "ffcc/partMng.h"

struct PCharaBreak;
struct CharaBreakStep;
struct CharaBreakDisplayListPair;

typedef _pppPObject pppCharaBreak;

struct CharaBreakDataOffsets {
    s32 m_colorWorkOffset;
    s32 _unused1;
    s32 m_workOffset;
};

struct POLYGON_DATA {
    u8 m_enabled;
    u8 m_alpha;
    u16 _pad2;
    S16Vec m_normalA;
    S16Vec m_normalB;
    S16Vec m_pos[3];
    u16 m_posIndices[3];
    u16 m_nrmIndices[3];
    u16 m_texIndices[3];
};

struct CharaBreakStep {
    s32 m_graphId;
    f32 m_dataValIndex;
    f32 m_graphInit;
    f32 m_graphStep;
    f32 m_gravity;
    f32 _pad14;
    Vec m_direction;
    u8 _pad24[0x4];
    f32 m_payloadGraphInit;
    f32 m_payloadGraphStep;
    f32 m_payloadGraphStepStep;
    u8 m_alphaBase;
    u8 m_alphaRange;
    u8 _pad36[0x2];
    f32 m_velocityBase;
    f32 m_velocityRange;
    u8 m_spinMode;
    u8 m_clipMode;
    u8 m_worldSpaceMode;
    u8 _pad43;
};

struct VCharaBreak {
    GXColor m_color;
    f32 m_value0;
    f32 m_value1;
    f32 m_value2;
    f32 m_value3;
    f32 m_value4;
    f32 m_value5;
    CharaBreakDisplayListPair*** m_meshBuffers;
    Vec m_bboxMin;
    u8 _pad2C[0x4];
    Vec m_bboxMax;
    f32 m_miscValue;
    CChara::CModel* m_model;
    u32 m_enabled;
};

typedef VCharaBreak CharaBreakWork;

struct CharaBreakDisplayListPair {
    void* m_rewrittenDisplayList;
    u32 m_displayListSize;
    u16 m_polygonCount;
    u16 _padA;
    POLYGON_DATA* m_polygonData;
};

void CreatePolygon(POLYGON_DATA*, void*, unsigned long, CChara::CModel*, CChara::CMesh*);
void InitPolygonParameter(PCharaBreak*, VCharaBreak*, POLYGON_DATA*, unsigned long, CChara::CModel*, CChara::CMesh*);
void UpdatePolygonData(PCharaBreak*, VCharaBreak*, CChara::CModel*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructCharaBreak(pppCharaBreak*, _pppCtrlTable*);
void pppConstruct2CharaBreak(pppCharaBreak*, _pppCtrlTable*);
void pppDestructCharaBreak(pppCharaBreak*, _pppCtrlTable*);
void pppFrameCharaBreak(pppCharaBreak*, CharaBreakStep*, _pppCtrlTable*);
void pppRenderCharaBreak(pppCharaBreak*, CharaBreakStep*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCHARABREAK_H_
