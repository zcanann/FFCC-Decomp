#ifndef _FFCC_PPPCHARABREAK_H_
#define _FFCC_PPPCHARABREAK_H_

class CChara;
struct POLYGON_DATA;
struct PCharaBreak;
struct VCharaBreak;

void CharaBreak_BeforeCalcMatrixCallback(CChara::CModel*, void*, void*);
void CharaBreak_BeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int);
void CharaBreak_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
void CharaBreak_AfterDrawMeshCallback(CChara::CModel*, void*, void*, int, float (*)[4]);
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
