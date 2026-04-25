#ifndef _FFCC_PPPCHARABREAK_H_
#define _FFCC_PPPCHARABREAK_H_

#include "ffcc/chara.h"

struct POLYGON_DATA;
struct PCharaBreak;
struct VCharaBreak;
struct CharaBreakUnkB;
struct CharaBreakUnkC;

void CreatePolygon(POLYGON_DATA*, void*, unsigned long, CChara::CModel*, CChara::CMesh*);
void InitPolygonParameter(PCharaBreak*, VCharaBreak*, POLYGON_DATA*, unsigned long, CChara::CModel*, CChara::CMesh*);
void UpdatePolygonData(PCharaBreak*, VCharaBreak*, CChara::CModel*);

struct pppCharaBreak {
    union {
        void* ptr;
        struct {
            unsigned int m_graphId;
        };
    } field0_0x0;
};

struct CharaBreakUnkB {
    int m_graphId;
    float m_dataValIndex;
    float m_graphInit;
    float m_graphStep;
    unsigned char _pad10[0x8];
    Vec m_direction;
    unsigned char _pad24[0x4];
    float m_payloadGraphInit;
    float m_payloadGraphStep;
    float m_payloadGraphStepStep;
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
