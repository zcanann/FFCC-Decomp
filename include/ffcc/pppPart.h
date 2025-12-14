#ifndef _PPP_PART_H_
#define _PPP_PART_H_

#include "ffcc/memory.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>

class CGObject;
class CParShapeSet;
class CParModelSet;
class CMapPcs;

struct _pppPDataVal;

// Note: Not officially part of the decomp .MAP file, so this is speculative,
// but it seems to work.
struct _pppPObjLink
{
    _pppPObjLink* m_next;     // 0x0
    _pppPObjLink* m_previous; // 0x4
    _pppPDataVal* m_owner;    // 0x8
}; // Size 0xc

struct _pppPDataVal
{
}; // Size 0x10

struct pppCVECTOR
{
    unsigned char rgba[4];
};

_pppMngSt* pppStopSe(_pppMngSt* pppMngSt, PPPSEST* pppSest);
void pppUnitMatrix(pppFMATRIX& pppFMtx);
void pppRotMatrix(pppFMATRIX&, pppFMATRIX, Vec&);
void pppApplyMatrix(Vec& destination, pppFMATRIX pppFMatrix, Vec source);
void pppAddVector(Vec& ab, Vec a, Vec b);
void pppScaleVectorXYZ(Vec& outVec, Vec inVec, float scale);
void pppScaleVector(Vec& outVec, Vec inVec, float scale);
void pppGetRowVector(pppFMATRIX& pppFMtx, Vec& vecA, Vec& vecB, Vec& vecC, Vec& vecD);
void pppSetRowVector(pppFMATRIX& pppFMtx, Vec& vecA, Vec& vecB, Vec& vecC, Vec& vecD);
void pppNormalize(Vec& dest, Vec source);
void pppOuterProduct(Vec& ab, Vec a, Vec b);
void pppCopyMatrix(pppFMATRIX& dest, pppFMATRIX source);
void pppMulMatrix(pppFMATRIX& ab, pppFMATRIX& a, pppFMATRIX& );
void pppCopyVector(Vec& dest, Vec source);
void pppSubVector(Vec& dest, Vec a, Vec b);
float pppVectorLength(Vec vec);
void pppCreateHeap(_pppEnvSt* pppEnvSt, unsigned long param_2);
void pppDestroyHeap(_pppEnvSt* pppEnvSt);
void pppMemAlloc(unsigned long, CMemory::CStage*, char*, int);
void pppMemFree(void*);
void pppHeapUseRate(CMemory::CStage* stage);
void pppHeapCheckLeak(CMemory::CStage* stage);
void pppMngStHeapCheckLeak(CMemory::CStage* stage);
void pppMngStHeapCheck(CMemory::CStage* stage);
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
void pppInitPdt(long*, _pppDataHead::pppProg*);
void pppInitData(_pppDataHead*, _pppDataHead::pppProg*, int);
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
