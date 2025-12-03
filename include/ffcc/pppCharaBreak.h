#ifndef _FFCC_PPPCHARABREAK_H_
#define _FFCC_PPPCHARABREAK_H_

#include "ffcc/chara.h"

struct POLYGON_DATA;
struct PCharaBreak;
struct VCharaBreak;

void GXEnd(void);
void CreatePolygon(POLYGON_DATA*, void*, unsigned long, CChara::CModel*, CChara::CMesh*);
void InitPolygonParameter(PCharaBreak*, VCharaBreak*, POLYGON_DATA*, unsigned long, CChara::CModel*, CChara::CMesh*);
void UpdatePolygonData(PCharaBreak*, VCharaBreak*, CChara::CModel*);
void pppConstructCharaBreak(void);
void pppConstruct2CharaBreak(void);
void pppDestructCharaBreak(void);
void pppFrameCharaBreak(void);
void pppRenderCharaBreak(void);

#endif // _FFCC_PPPCHARABREAK_H_
