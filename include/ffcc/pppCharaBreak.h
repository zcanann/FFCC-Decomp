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
    int m_dataValIndex;
    unsigned short m_initWOrk;
    unsigned char _pad0[2];
    float m_stepValue;
    unsigned char m_arg3;
    unsigned char m_payload[6];
    unsigned char _pad1[1];
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
