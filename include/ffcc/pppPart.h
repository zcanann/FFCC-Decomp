#ifndef _PPP_PART_H_
#define _PPP_PART_H_

#include "ffcc/memory.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>

class CGObject;
class CParShapeSet;
class CParModelSet;
class CMapPcs;

struct _pppProgSetDef;

struct _pppPDataVal
{
    _pppProgSetDef* m_programSetDef; // 0x0
    _pppPObjLink* m_pppPObjLink;     // 0x4
    s32 m_nextSpawnTime;             // 0x8
    u16 m_activeCount;               // 0xc
    u8 m_index;                      // 0xe
    u8 m_pad;                        // 0xf
}; // Size 0x10

struct _pppProgSetDef
{
    _pppProgSetDef* m_next;      // 0x00
    u16 m_spawnCount;            // 0x04
    u16 m_reserved6;             // 0x06
    u32 m_flags;                 // 0x08
    u8 m_drawFlags;              // 0x0C
    u8 m_pad0D[3];               // 0x0D
    s32 m_startFrame;            // 0x10
    s32 m_deadFrame;             // 0x14
    s32 m_endFrame;              // 0x18
    s32 m_loopFrame;             // 0x1C
    u32 m_workBaseOffset;        // 0x20
    s16 m_sortKey;               // 0x24
    s16 m_numStages;             // 0x26
    _pppCtrlTable m_stages[1];   // 0x28
};

struct pppCVECTOR
{
    unsigned char rgba[4];
};

_pppMngSt* pppStopSe(_pppMngSt* pppMngSt, PPPSEST* pppSest);
void pppUnitMatrix(pppFMATRIX& pppFMtx);
void pppRotMatrix(pppFMATRIX&, pppFMATRIX, Vec);
void pppApplyMatrix(Vec& destination, pppFMATRIX pppFMatrix, Vec source);
void pppAddVector(Vec& ab, Vec a, Vec b);
void pppScaleVectorXYZ(Vec& outVec, Vec inVec, float scale);
void pppScaleVector(Vec& outVec, Vec inVec, float scale);
void pppGetRowVector(pppFMATRIX& pppFMtx, Vec& vecA, Vec& vecB, Vec& vecC, Vec& vecD);
void pppSetRowVector(pppFMATRIX& pppFMtx, Vec& vecA, Vec& vecB, Vec& vecC, Vec& vecD);
void pppNormalize(Vec& dest, Vec source);
void pppOuterProduct(Vec& ab, Vec a, Vec b);
void pppCopyMatrix(pppFMATRIX& dest, pppFMATRIX source);
void pppMulMatrix(pppFMATRIX& ab, pppFMATRIX a, pppFMATRIX b);
void pppCopyVector(Vec& dest, Vec source);
void pppSubVector(Vec& dest, Vec a, Vec b);
float pppVectorLength(Vec vec);
void pppCreateHeap(_pppEnvSt* pppEnvSt, unsigned long param_2);
void pppDestroyHeap(_pppEnvSt* pppEnvSt);
void* pppMemAlloc(unsigned long, CMemory::CStage*, char*, int);
extern "C" void* pppMemFree__FPv(unsigned long, CMemory::CStage*, char*, int);
void pppHeapUseRate(CMemory::CStage* stage);
void pppHeapCheckLeak(CMemory::CStage* stage);
extern "C" unsigned long pppHeapCheckLeak__FPQ27CMemory6CStage2(CMemory::CStage* stage);
unsigned long pppMngStHeapCheckLeak(CMemory::CStage* stage);
void callCon2Prog(_pppPObject*);
_pppPObject* pppCreatePObject(_pppMngSt*, _pppPDataVal*);
void _pppAllFreePObject(_pppMngSt*);
void pppSetBindChrSync(_pppMngSt*);
void pppSetMatrix(_pppMngSt*);
void pppSetFpMatrix(_pppMngSt*);
void pppCacheLoadShape(short*, _pppDataHead*);
void _pppStartPart(_pppMngSt*, long*, int);
void pppInitPdt(long*, pppProg*);
void pppInitData(_pppDataHead*, pppProg*, int);
void pppCalcPartStd(_pppMngSt*);
void pppDrawPartStd(_pppMngSt*);
void _pppDeadPart(_pppMngSt*);
void _pppInitPart(_pppMngSt*);
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
