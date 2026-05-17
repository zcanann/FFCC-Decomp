#ifndef _FFCC_PPPCHARABREAK_H_
#define _FFCC_PPPCHARABREAK_H_

#include "ffcc/chara.h"
#include "ffcc/partMng.h"

struct POLYGON_DATA;
struct PCharaBreak;
struct VCharaBreak;
struct CharaBreakUnkB;
struct CharaBreakUnkC;

void CreatePolygon(POLYGON_DATA*, void*, unsigned long, CChara::CModel*, CChara::CMesh*);
void InitPolygonParameter(PCharaBreak*, VCharaBreak*, POLYGON_DATA*, unsigned long, CChara::CModel*, CChara::CMesh*);
void UpdatePolygonData(PCharaBreak*, VCharaBreak*, CChara::CModel*);

typedef _pppPObject pppCharaBreak;

struct CharaBreakUnkB {
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

struct CharaBreakUnkC {
    unsigned char _pad0[0xC];
    int* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructCharaBreak(pppCharaBreak*, CharaBreakUnkC*);
void pppConstruct2CharaBreak(pppCharaBreak*, CharaBreakUnkC*);
void pppDestructCharaBreak(pppCharaBreak*, CharaBreakUnkC*);
void pppFrameCharaBreak(pppCharaBreak*, CharaBreakUnkB*, CharaBreakUnkC*);
void pppRenderCharaBreak(pppCharaBreak*, CharaBreakUnkB*, CharaBreakUnkC*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCHARABREAK_H_
