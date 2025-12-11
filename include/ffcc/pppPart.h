#ifndef _PPP_PART_H_
#define _PPP_PART_H_

#include "ffcc/memory.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>

class CGObject;
class CParShapeSet;
class CParModelSet;
class CMapPcs;

struct _pppPDataVal
{
};

struct pppCVECTOR
{
    unsigned char rgba[4];
};

void pppPlaySe(_pppMngSt*, PPPSEST*);
void pppStopSe(_pppMngSt*, PPPSEST*);
void pppUnitMatrix(pppFMATRIX&);
void pppRotMatrix(pppFMATRIX&, pppFMATRIX, Vec&);
void pppApplyMatrix(Vec& destination, pppFMATRIX pppFMatrix, Vec source);
void pppAddVector(Vec&, Vec&, Vec&);
void pppScaleVectorXYZ(Vec&, Vec&, float);
void pppScaleVector(Vec&, Vec&, float);
void pppGetRowVector(pppFMATRIX&, Vec&, Vec&, Vec&, Vec&);
void pppSetRowVector(pppFMATRIX&, Vec&, Vec&, Vec&, Vec&);
void pppNormalize(Vec&, Vec);
void pppOuterProduct(Vec&, Vec&, Vec&);
void pppCopyMatrix(pppFMATRIX&, pppFMATRIX&);
void pppMulMatrix(pppFMATRIX&, pppFMATRIX&, pppFMATRIX&);
void pppCopyVector(Vec&, Vec&);
void pppSubVector(Vec&, Vec&, Vec&);
void pppVectorLength(Vec&);
void pppCreateHeap(_pppEnvSt*, unsigned long);
void pppDestroyHeap(_pppEnvSt*);
void pppFreePObjectPrio(_pppMngSt*);
void pppFreeMngStPrioForHeap(char*);
void pppMemAlloc(unsigned long, CMemory::CStage*, char*, int);
void pppMemFree(void*);
void pppHeapUseRate(CMemory::CStage*);
void pppHeapCheckLeak(CMemory::CStage*);
void pppMngStHeapCheckLeak(CMemory::CStage*);
void pppMngStHeapCheck(CMemory::CStage*);
void callInitProg(_pppMngSt*);
void callCon2Prog(_pppPObject*);
void callConProg(_pppPObject*);
void pppCreatePObject(_pppMngSt*, _pppPDataVal*);
void pppDeletePObject(_pppPObject*);
void _pppAllFreePObject(_pppMngSt*);
void pppSetBindChrSync(_pppMngSt*);
void pppSetMatrix(_pppMngSt*);
void pppSetFpMatrix(_pppMngSt*);
void pppCacheLoadModel(short*, _pppDataHead*);
void pppCacheLoadShape(short*, _pppDataHead*);
void pppCacheUnLoadModel(short*, _pppDataHead*);
void pppCacheUnLoadShape(short*, _pppDataHead*);
void pppCacheRefCnt0UpModel(short*, _pppDataHead*);
void pppCacheRefCnt0UpShape(short*, _pppDataHead*);
void pppCacheDumpModel(short*, _pppDataHead*);
void pppCacheDumpShape(short*, _pppDataHead*);
void _pppStartPart(_pppMngSt*, long*, int);
void pppInitPdt(long*, pppProg*);
void pppInitData(_pppDataHead*, pppProg*, int);
void pppCalcPartStd(_pppMngSt*);
void pppDrawPartStd(_pppMngSt*);
void _pppDeadPart(_pppMngSt*);
void _pppInitPart(_pppMngSt*);
void apeaPObject(_pppMngSt*);
void _pppCalcPart(_pppMngSt*);
void _pppDrawPart(_pppMngSt*);
void pppDrawMesh(pppModelSt*, Vec*, int);
void pppInitBlendMode(void);
void pppSetBlendMode(unsigned char);
void pppClearDrawEnv(void);
void pppSetDrawEnv(pppCVECTOR*, pppFMATRIX*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void pppInitDrawEnv(unsigned char);
void pppHitCylinderSendSystem(_pppMngSt*, Vec*, Vec*, float, float);
void CGObject_GetModelAlpha(CGObject*);
void CGObject_IsDisp(CGObject*);
void CGObject_IsFirstDraw(CGObject*);
void pppShapeSt_AddRef(pppShapeSt*);
void CParShapeSet_Find(CParShapeSet*, char*, int);
void CParShapeSet_GetNumShape(CParShapeSet*);
void pppModelSt_AddRef(pppModelSt*);
void CParModelSet_Find(CParModelSet*, char*, int);
void CParModelSet_GetNumModel(CParModelSet*);
void CMapPcs_CalcHitPosition(CMapPcs*, Vec*);

#endif // _PPP_PART_H_
