#include "ffcc/ptrarray.h"
#include "ffcc/pppPart.h"

#include "ffcc/cflat_runtime2.h"
#include "ffcc/map.h"
#include "ffcc/game.h"
#include "ffcc/p_tina.h"
#include "ffcc/memory.h"
#include "ffcc/sound.h"
#include "ffcc/p_camera.h"
#include "ffcc/graphic.h"
#include "ffcc/p_light.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/math.h"
#include "ffcc/gobject.h"
#include "ffcc/mapmesh.h"
#include "ffcc/pppGetRotMatrixXYZ.h"
#include "ffcc/pppGetRotMatrixXZY.h"
#include "ffcc/pppGetRotMatrixYXZ.h"
#include "ffcc/pppGetRotMatrixYZX.h"
#include "ffcc/pppGetRotMatrixZXY.h"
#include "ffcc/pppGetRotMatrixZYX.h"
#include "ffcc/pppDrawMng.h"
#include "ffcc/pppShape.h"
extern "C" {
extern float ppvScreenMatrixZbuff;
}
#include "ffcc/gxfunc.h"

#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>


static inline CChara::CModel* GetPppOwnerModel(_pppMngSt* pppMngSt)
{
	return pppMngSt->m_owner->m_charaModelHandle->m_model;
}

static const float kPppLocalZero = 0.0f;
extern "C" const unsigned int gPppFixedWhite;
extern "C" const float kPppPartZero = 0.0f;
extern "C" const float kPppPartHugePositive = 10000000000.0f;
extern "C" const float kPppPartHugeNegative = -10000000000.0f;
extern "C" const float kPppPartZOffsetMin = -1000000000000.0f;
extern "C" const double kPppPartZeroDouble = 0.0;
extern "C" const float kPppPartDepthScale;
extern "C" const float kPppPartOne = 1.0f;
extern "C" const double kPppPartOneDouble = 1.0;

_pppMngSt* ppvMng;
_pppEnvSt* ppvEnv;
extern "C" {
float ppvScreenMatrixXbuff = 0.0f;
float ppvScreenMatrixYbuff = 0.0f;
float ppvScreenMatrixZbuff = 0.0f;
int ppvMemAllocErrorF = 0;
int ppvSysStopPartF = 0;
int ppvSysGoPartF = 0;
int ppvUserStopPartF = 0;
int ppvEmptyLoop = 0;
unsigned char ppvIsLoopCalc = 0;
unsigned char ppvIs2ndCalc = 0;
void* ppvHookFuncTbl = 0;
unsigned int pobjcounter = 0;
}
static unsigned char s_light_mode = 0;
static unsigned char s_blend_mode = 0;
static unsigned char s_fog_mode = 0;
static unsigned char s_fog_blend_mode = 0;
static unsigned char s_cull_mode = 0;
static unsigned char s_ztest = 0;
static unsigned char s_rgbwrite = 0;
static unsigned char s_zwrite = 0;
static float s_zoff = 0.0f;
pppDrawMng ppvDrawMng;
Mtx ppvCameraMatrix0;
Mtx ppvCameraMatrix;
Mtx ppvWorldMatrix;
Mtx ppvWorldMatrixWood;
Mtx ppvFpCameraMatrixWood;
float ppvScreenMatrix0[4][4];
Mtx44 ppvScreenMatrix;
Mtx ppvLightMatrix;
Mtx ppvColorMatrix;
float ppvChrScl[3];
Mtx ppvUnitMatrix;
Vec ppvZeroVector;
CAmemCacheSet ppvAmemCacheSet;

extern "C" const char s_pppPart_cpp[] = "pppPart.cpp";
extern "C" const char sPppProgNullErrorMsg[] = "\nERROR!!!! prog=NULL\n\n";
extern "C" const char sPartPcsHeapStageName[] = "CPartPcs.heap";

/*
 * --INFO--
 * PAL Address: 0x8005773C
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppStopSe(_pppMngSt* pppMngSt, PPPSEST* pppSest)
{
	if (pppSest->m_soundEffectSlot >= 0 && pppSest->m_soundEffectHandle >= 0)
	{
		Sound.FadeOutSe3D(pppSest->m_soundEffectHandle, pppSest->m_soundEffectFadeFrames);
		pppSest->m_soundEffectHandle = -1;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppUnitMatrix(pppFMATRIX& pppFMtx)
{ 
	PSMTXIdentity(pppFMtx.value);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRotMatrix(pppFMATRIX& dst, pppFMATRIX src, Vec rot)
{
	pppFMATRIX Rx;
	pppFMATRIX Ry;
	pppFMATRIX Rz;
	pppFMATRIX R;

	PSMTXRotRad(Rx.value, 'x', rot.x);
	PSMTXRotRad(Ry.value, 'y', rot.y);
	PSMTXRotRad(Rz.value, 'z', rot.z);
	PSMTXConcat(Ry.value, Rz.value, R.value);
	PSMTXConcat(Rx.value, R.value, R.value);
	PSMTXConcat(R.value, src.value, dst.value);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppApplyMatrix(Vec& destination, pppFMATRIX pppFMatrix, Vec source)
{ 
	PSMTXMultVecSR(pppFMatrix.value, &source, &destination);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppAddVector(Vec& ab, Vec a, Vec b)
{ 
	PSVECAdd(&a, &b, &ab);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppScaleVectorXYZ(Vec& outVec, Vec inVec, float scale)
{ 
	PSVECScale(&inVec, &outVec, scale);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppScaleVector(Vec& outVec, Vec inVec, float scale)
{
	PSVECScale(&inVec, &outVec, scale);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppGetRowVector(pppFMATRIX& pppFMtx, Vec& vecA, Vec& vecB, Vec& vecC, Vec& vecD)
{
	vecA.x = pppFMtx.value[0][0];
	vecA.y = pppFMtx.value[1][0];
	vecA.z = pppFMtx.value[2][0];

	vecB.x = pppFMtx.value[0][1];
	vecB.y = pppFMtx.value[1][1];
	vecB.z = pppFMtx.value[2][1];

	vecC.x = pppFMtx.value[0][2];
	vecC.y = pppFMtx.value[1][2];
	vecC.z = pppFMtx.value[2][2];

	vecD.x = pppFMtx.value[0][3];
	vecD.y = pppFMtx.value[1][3];
	vecD.z = pppFMtx.value[2][3];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppSetRowVector(pppFMATRIX& pppFMtx, Vec& vecA, Vec& vecB, Vec& vecC, Vec& vecD)
{
	pppFMtx.value[0][0] = vecA.x;
	pppFMtx.value[1][0] = vecA.y;
	pppFMtx.value[2][0] = vecA.z;

	pppFMtx.value[0][1] = vecB.x;
	pppFMtx.value[1][1] = vecB.y;
	pppFMtx.value[2][1] = vecB.z;

	pppFMtx.value[0][2] = vecC.x;
	pppFMtx.value[1][2] = vecC.y;
	pppFMtx.value[2][2] = vecC.z;

	pppFMtx.value[0][3] = vecD.x;
	pppFMtx.value[1][3] = vecD.y;
	pppFMtx.value[2][3] = vecD.z;
}

/*
 * --INFO--
 * PAL Address: 800574a0
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppNormalize(Vec& dest, Vec source)
{ 
	float zero = kPppPartZero;
	if ((source.x == zero) && (source.y == zero) && (source.z == zero)) {
		return;
	}
	PSVECNormalize(&source, &dest);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppOuterProduct(Vec& ab, Vec a, Vec b)
{ 
	PSVECCrossProduct(&a, &b, &ab);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCopyMatrix(pppFMATRIX& dest, pppFMATRIX source)
{ 
	PSMTXCopy(source.value, dest.value);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppMulMatrix(pppFMATRIX& ab, pppFMATRIX a, pppFMATRIX b)
{ 
	PSMTXConcat(a.value, b.value, ab.value);
}

/*
 * --INFO--
 * PAL Address: 0x800573f0
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppCopyVector(Vec& dest, Vec source)
{ 
	float* src = &source.x;
	float x = *src++;
	float y = *src++;
	dest.x = x;
	float z = *src;
	dest.y = y;
	dest.z = z;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppSubVector(Vec& dest, Vec a, Vec b)
{ 
	PSVECSubtract(&a, &b, &dest);
}

/*
 * --INFO--
 * PAL Address: 80057388
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
float pppVectorLength(Vec vec)
{
	Vec zeroVec;

	zeroVec.x = kPppPartZero;
	zeroVec.y = kPppPartZero;
	zeroVec.z = kPppPartZero;

	return PSVECDistance(&vec, &zeroVec);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCreateHeap(_pppEnvSt* pppEnvSt, unsigned long param_2)
{
	pppEnvSt->m_stagePtr = Memory.CreateStage(param_2, const_cast<char*>(sPartPcsHeapStageName), 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDestroyHeap(_pppEnvSt* pppEnvSt)
{
	Memory.DestroyStage(pppEnvSt->m_stagePtr);
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 196b
 * EN Address: 0x80063104
 * EN Size: 300b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void pppDeletePObject(_pppPObject* object)
{
    _pppPDataVal* owner = object->m_link.m_owner;
    _pppProgSetDef* progSet = owner->m_programSetDef;
    for (int stageIndex = 0; stageIndex < progSet->m_numStages; stageIndex++) {
        _pppCtrlTable* stage = &progSet->m_stages[stageIndex];
        if (stage->m_prog != 0 && stage->m_prog->m_pppFunctionDestructor != 0) {
            ((pppProgDestructCallback)stage->m_prog->m_pppFunctionDestructor)(&object->m_link, stage);
        }
    }
    if (--owner->m_activeCount == 0) {
        owner->m_pppPObjLink = 0;
    } else if (owner->m_pppPObjLink == &object->m_link) {
        owner->m_pppPObjLink = object->m_link.m_next;
    }
    if (object != 0) {
        Memory.Free(object);
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 260b
 * EN Address: 0x80062718
 * EN Size: 128b
 * JP Address: TODO
 * JP Size: TODO
 */
static inline void pppFreePObjectPrio(_pppMngSt* mng)
{
    _pppPObjLink* prev = &mng->m_pppPObjLinkHead;
    _pppPObjLink* obj = mng->m_pppPObjLinkHead.m_next;
    while (obj != 0) {
        _pppPObjLink* next = obj->m_next;
        if ((obj->m_owner->m_programSetDef->m_drawFlags & 2) == 0) {
            prev->m_next = next;
            pppDeletePObject((_pppPObject*)obj);
        } else {
            prev = obj;
        }
        obj = next;
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 580b
 * EN Address: 0x80062798
 * EN Size: 284b
 * JP Address: TODO
 * JP Size: TODO
 */
static inline int pppFreeMngStPrioForHeap(char* denied)
{
    _pppMngSt* selectedMngSt = 0;
    int selectedPrio = 1;
    int selectedPrioTime;
    for (int i = 0; i < 0x180; i++) {
        if (denied[i] == 0) {
            _pppMngSt* candidate = &PartMng.m_pppMng[i];
            if (candidate->m_baseTime != -0x1000 && candidate->m_kind != 0) {
                u8 prio = candidate->m_prio;
                if (prio > 1) {
                    if (selectedPrio < prio) {
                        selectedPrioTime = candidate->m_prioTime;
                        selectedPrio = prio;
                        selectedMngSt = candidate;
                    } else if (selectedPrio == prio && selectedPrioTime < candidate->m_prioTime) {
                        selectedPrioTime = candidate->m_prioTime;
                        selectedMngSt = candidate;
                    }
                }
            }
        }
    }
    if (selectedMngSt == 0) {
        return 0;
    }
    denied[selectedMngSt - PartMng.m_pppMng] = 1;
    pppFreePObjectPrio(selectedMngSt);
    return 1;
}

/*
 * --INFO--
 * PAL Address: 80057008
 * PAL Size: 780b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* pppMemAlloc(unsigned long allocSize, CMemory::CStage* stage, char* file, int line)
{
	int firstAllocFailure = 1;
	int canRetry;
	_pppPObjLink* allocation;
	char denied[0x180];

	ppvMemAllocErrorF = 0;
	do
	{
		allocation = (_pppPObjLink*)Memory._Alloc(allocSize, stage, file, line, 1);
		if (allocation != 0)
		{
			goto allocDone;
		}

		if (firstAllocFailure)
		{
			firstAllocFailure = 0;
			memset(denied, 0, sizeof(denied));

			s32 currentIdx = ppvMng - PartMng.m_pppMng;
			denied[currentIdx] = 1;
		}

		canRetry = pppFreeMngStPrioForHeap(denied);
	}
	while (canRetry);

	ppvEnv->m_stagePtr->heapWalker(2, 0, 0xFFFFFFFF);
	PartMng.pppDumpMngSt();
	ppvMemAllocErrorF = 1;
allocDone:
	return allocation;
}

/*
 * --INFO--
 * PAL Address: 80056d20
 * PAL Size: 744b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void* pppMemFree__FPv(unsigned long allocSize, CMemory::CStage* stage, char* file, int line)
{
	int firstAllocFailure = 1;
	int canRetry;
	_pppPObjLink* allocation;
	char denied[0x180];

	ppvMemAllocErrorF = 0;
	do
	{
		allocation = (_pppPObjLink*)Memory._Alloc(allocSize, stage, file, line, 1);
		if (allocation != 0)
		{
			goto freeDone;
		}

		if (firstAllocFailure)
		{
			firstAllocFailure = 0;
			memset(denied, 0, sizeof(denied));

			s32 currentIdx = ppvMng - PartMng.m_pppMng;
			denied[currentIdx] = 1;
		}

		canRetry = pppFreeMngStPrioForHeap(denied);
	}
	while (canRetry);

	ppvMemAllocErrorF = 1;
	return 0;
freeDone:
	return allocation;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppHeapUseRate(CMemory::CStage* stage)
{ 
	if (stage != (CMemory::CStage*)0)
	{
		Memory.Free(stage);
	}
}

/*
 * --INFO--
 * PAL Address: 80056c74
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppHeapCheckLeak(CMemory::CStage* stage)
{
	stage->heapWalker(2, 0, 0xFFFFFFFF);
}

/*
 * --INFO--
 * PAL Address: 80056ca0
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" unsigned long pppHeapCheckLeak__FPQ27CMemory6CStage2(CMemory::CStage* stage)
{
	unsigned long heapTotal;
	unsigned long heapUseRate;
	unsigned long heapUnused;
	unsigned long result;

	stage->heapInfo(heapTotal, heapUseRate, heapUnused);
	if (heapTotal == 0) {
		result = 10000;
	} else {
		result = (heapUseRate * 10000) / heapTotal;
	}

	return result;
}

/*
 * --INFO--
 * PAL Address: 80056b0c
 * PAL Size: 360b
 * EN Address: 0x80062C50
 * EN Size: 620b
 * JP Address: TODO
 * JP Size: TODO
 */
static void callCon2Prog(_pppPObject* pObject)
{
	_pppPDataVal* owner = pObject->m_link.m_owner;
	_pppProgSetDef* progSet = owner->m_programSetDef;

	ppvIsLoopCalc = 1;

	int stageIdx = 0;
	u32* initWork = (u32*)(((u8*)pObject) + progSet->m_workBaseOffset);
	for (; stageIdx < progSet->m_numStages; stageIdx++)
	{
		_pppCtrlTable* stage = &progSet->m_stages[stageIdx];
		pppProg* prog = stage->m_prog;
		if (prog != 0)
		{
			if (prog->m_pppFunctionConstructor3 != 0)
			{
				((pppProgConstruct3Callback)prog->m_pppFunctionConstructor3)(pObject, stage);
			}
			else
			{
				*initWork++ = stage->m_unk8;
				if (prog->m_pppFunctionConstructor2 != 0)
				{
					((pppProgConstruct2Callback)prog->m_pppFunctionConstructor2)(pObject);
				}
			}
		}
	}

	pObject->m_graphId = 0;
	while (pObject->m_graphId <= progSet->m_endFrame)
	{
		int stageCount = 0;
		for (; stageCount < progSet->m_numStages; stageCount++)
		{
			_pppCtrlTable* stage = &progSet->m_stages[stageCount];
			s32** slotPtr = &((s32**)(((u8*)pObject) + progSet->m_workBaseOffset))[stageCount];
			s32* nextSlot = (s32*)(((u8*)*slotPtr) + stage->m_workOffset);
			pppProg* prog = stage->m_prog;

			if (*nextSlot == pObject->m_graphId)
			{
				*slotPtr = nextSlot;
			}
			if (prog != 0 && prog->m_pppFunctionOperation != 0 && prog->m_pppFunctionConstructor2 != 0)
			{
				((pppProgOperationCallback)prog->m_pppFunctionOperation)(pObject, *slotPtr, stage);
			}
		}

		pObject->m_graphId += 0x1000;
	}

	ppvIsLoopCalc = 0;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 140b
 * EN Address: 0x80062EBC
 * EN Size: 256b
 * JP Address: TODO
 * JP Size: TODO
 */
static inline void callConProg(_pppPObject* object)
{
	_pppProgSetDef* freshSet = object->m_link.m_owner->m_programSetDef;
	u32* initWork = (u32*)(((u8*)object) + freshSet->m_workBaseOffset);
	for (s32 stageIndex = 0; stageIndex < freshSet->m_numStages; stageIndex++)
	{
		_pppCtrlTable* entry = &freshSet->m_stages[stageIndex];
		pppProg* prog = entry->m_prog;
		*initWork++ = entry->m_unk8;
		if (prog != 0 && prog->m_pppFunctionConstructor != 0)
		{
			((pppProgConstructCallback)prog->m_pppFunctionConstructor)(&object->m_link, entry);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800566ac
 * PAL Size: 1120b
 * EN Address: 0x80062FBC
 * EN Size: 328b
 * JP Address: TODO
 * JP Size: TODO
 */
_pppPObject* pppCreatePObject(_pppMngSt* pppMngSt, _pppPDataVal* pppPDataVal)
{
	_pppPDataVal* dataVal = pppPDataVal;
	_pppProgSetDef* programSet = dataVal->m_programSetDef;
	_pppPObject* newObject = (_pppPObject*)pppMemAlloc(
		programSet->m_workBaseOffset + programSet->m_numStages * sizeof(u32),
		ppvEnv->m_stagePtr, const_cast<char*>(s_pppPart_cpp), 0x305);

	if (newObject == 0)
	{
		return 0;
	}

	newObject->m_graphId = 0;
	newObject->m_drawMatrixPtr = 0;
	newObject->m_field74 = 0;
	newObject->m_link.m_owner = pppPDataVal;
	newObject->m_field7C = 1;

	_pppPObjLink* firstObj = pppMngSt->m_pppPObjLinkHead.m_next;
	if (firstObj == 0)
	{
		dataVal->m_pppPObjLink = &newObject->m_link;
		pppMngSt->m_pppPObjLinkHead.m_next = &newObject->m_link;
		newObject->m_link.m_next = 0;
	}
	else if (dataVal->m_pppPObjLink != 0)
	{
		newObject->m_link.m_next = dataVal->m_pppPObjLink->m_next;
		dataVal->m_pppPObjLink->m_next = &newObject->m_link;
	}
	else
	{
		_pppPObjLink* prev = &pppMngSt->m_pppPObjLinkHead;
		s16 sortKey = programSet->m_sortKey;
		_pppPObjLink* iter = firstObj;
		do
		{
			_pppProgSetDef* iterSet = iter->m_owner->m_programSetDef;
			if (iterSet->m_sortKey >= sortKey)
			{
				dataVal->m_pppPObjLink = &newObject->m_link;
				prev->m_next = &newObject->m_link;
				newObject->m_link.m_next = iter;
				goto done_insert;
			}
			prev = iter;
			iter = iter->m_next;
		} while (iter != 0);
		dataVal->m_pppPObjLink = &newObject->m_link;
		prev->m_next = &newObject->m_link;
		newObject->m_link.m_next = 0;
	}

done_insert:
	dataVal->m_activeCount++;
	callConProg(newObject);
	return newObject;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 136b
 * EN Address: 0x80064034
 * EN Size: 176b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void pppCacheUnLoadModel(short* modelList, _pppDataHead* head)
{
	short modelCount = *modelList;
	short i = 0;
	modelList++;
	while (i < modelCount)
	{
		short modelIndex = *modelList;
		modelList++;
		pppModelSt* model = ((pppModelSt**)head->m_modelNames)[modelIndex];
		ppvAmemCacheSet.Release(model->m_cacheId);
		model->pppCacheUnLoadModelTexture(PartMng.m_materialSet, &ppvAmemCacheSet);
		i++;
	}
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 108b
 * EN Address: 0x800640E4
 * EN Size: 152b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void pppCacheUnLoadShape(short* shapeList, _pppDataHead* head)
{
	short shapeCount = *shapeList;
	short i = 0;
	shapeList++;
	while (i < shapeCount)
	{
		short shapeIndex = *shapeList;
		shapeList++;
		pppShapeSt* shape = ((pppShapeSt**)head->m_shapeNames)[shapeIndex];
		pppCacheUnLoadShapeTexture(shape, PartMng.m_materialSet);
		i++;
	}
}

/*
 * --INFO--
 * PAL Address: 800563fc
 * PAL Size: 688b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _pppAllFreePObject(_pppMngSt* pppMngSt)
{
	Graphic._WaitDrawDone(const_cast<char*>(s_pppPart_cpp), 0x362);

	_pppMngSt* oldMngSt = ppvMng;
	ppvMng = pppMngSt;

	pppStopSe(pppMngSt, &pppMngSt->m_soundEffectData);

	for (_pppPObjLink* obj = pppMngSt->m_pppPObjLinkHead.m_next; obj != 0;)
	{
		_pppPObjLink* next = obj->m_next;
		pppDeletePObject((_pppPObject*)obj);
		obj = next;
	}

	pppMngSt->m_pppPObjLinkHead.m_next = 0;
	if (pppMngSt->m_pppPDataVals != 0)
	{
		if (pppMngSt->m_pppPDataVals != 0)
		{
			Memory.Free(pppMngSt->m_pppPDataVals);
		}
		pppMngSt->m_pppPDataVals = 0;
	}

	ppvHookFuncTbl = 0;
	pppMngSt->m_baseTime = -0x1000;

	if (Game.m_currentSceneId != 7)
	{
		if (pppMngSt->m_hasMapRef != 0)
		{
			CPartMng::PppPdtSlot* slot = (CPartMng::PppPdtSlot*)pppMngSt->m_pppResSet;
			pppCacheChunk* chunk = &((pppCacheChunk*)slot->m_pppDataHead->m_cacheChunks)[pppMngSt->m_partIndex];
			if (chunk->m_cacheIndex != -1)
			{
				ppvAmemCacheSet.Release(chunk->m_cacheIndex);
			}

			if (pppMngSt->m_mapTexLoaded != 0)
			{
				long* pdt = chunk->m_pdt;
				short* modelIndices = (short*)((u8*)pdt + pdt[4]);
				short* shapeIndices = (short*)((u8*)pdt + pdt[5]);
				pppCacheUnLoadModel(modelIndices, ((CPartMng::PppPdtSlot*)pppMngSt->m_pppResSet)->m_pppDataHead);
				pppCacheUnLoadShape(shapeIndices, ((CPartMng::PppPdtSlot*)pppMngSt->m_pppResSet)->m_pppDataHead);
			}
		}

		pppMngSt->m_mapTexLoaded = 0;
		pppMngSt->m_hasMapRef = 0;
	}

	Graphic._WaitDrawDone(const_cast<char*>(s_pppPart_cpp), 0x3A1);
	ppvMng = oldMngSt;
}

/*
 * --INFO--
 * PAL Address: 80055b80
 * PAL Size: 2172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSetMatrix(_pppMngSt* pppMngSt)
{
	Vec tmpPos;
	Mtx nodeMtx ATTRIBUTE_ALIGN(8);
	Vec scaleAxis0;
	Vec scaleAxis1;
	Vec scaleAxis2;
	Vec localAxis0;
	Vec localAxis1;
	Vec localAxis2;

	switch (pppMngSt->m_rotationOrder) {
	case 0:
		pppGetRotMatrixXYZ(ppvMng->m_matrix, reinterpret_cast<pppIVECTOR4*>(&pppMngSt->m_rotation));
		break;
	case 1:
		pppGetRotMatrixXZY(ppvMng->m_matrix, reinterpret_cast<pppIVECTOR4*>(&pppMngSt->m_rotation));
		break;
	case 2:
		pppGetRotMatrixYXZ(ppvMng->m_matrix, reinterpret_cast<pppIVECTOR4*>(&pppMngSt->m_rotation));
		break;
	case 3:
		pppGetRotMatrixYZX(ppvMng->m_matrix, reinterpret_cast<pppIVECTOR4*>(&pppMngSt->m_rotation));
		break;
	case 4:
		pppGetRotMatrixZXY(ppvMng->m_matrix, reinterpret_cast<pppIVECTOR4*>(&pppMngSt->m_rotation));
		break;
	case 5:
		pppGetRotMatrixZYX(ppvMng->m_matrix, reinterpret_cast<pppIVECTOR4*>(&pppMngSt->m_rotation));
		break;
	default:
		break;
	}

	int matrixMode = pppMngSt->m_matrixMode;
	if (matrixMode == 5) {
		goto MatrixMode5;
	}
	if (matrixMode >= 5) {
		goto MatrixModeHigh;
	}
	if (matrixMode == 3) {
		goto MatrixMode3;
	}
	if (matrixMode >= 3) {
		goto MatrixMode4;
	}
	if (matrixMode >= 2) {
		goto MatrixMode2;
	}
	goto LocalOnly;

MatrixModeHigh:
	if (matrixMode == 7) {
		goto MatrixMode7;
	}
	if (matrixMode >= 7) {
		goto LocalOnly;
	}
	goto MatrixMode6;

MatrixMode2:
	if (pppMngSt->m_mapObjIndex == -1) {
		goto LocalOnly;
	}
	MapMng.GetMapObjWMtx(pppMngSt->m_mapObjIndex, nodeMtx);

ApplyRotatedMatrix:
	PSMTXMultVecSR(nodeMtx, &ppvMng->m_position, &tmpPos);
	nodeMtx[0][3] += tmpPos.x;
	nodeMtx[1][3] += tmpPos.y;
	nodeMtx[2][3] += tmpPos.z;
	PSMTXConcat(nodeMtx, ppvMng->m_matrix.value, ppvMng->m_matrix.value);

ScaleOnly:
	if (kPppPartOne != pppMngSt->m_scale.x) {
		scaleAxis0.x = ppvMng->m_matrix.value[0][0];
		scaleAxis0.y = ppvMng->m_matrix.value[1][0];
		scaleAxis0.z = ppvMng->m_matrix.value[2][0];
		PSVECScale(&scaleAxis0, &scaleAxis0, pppMngSt->m_scale.x);
		ppvMng->m_matrix.value[0][0] = scaleAxis0.x;
		ppvMng->m_matrix.value[1][0] = scaleAxis0.y;
		ppvMng->m_matrix.value[2][0] = scaleAxis0.z;
	}

	if (kPppPartOne != pppMngSt->m_scale.y) {
		scaleAxis1.x = ppvMng->m_matrix.value[0][1];
		scaleAxis1.y = ppvMng->m_matrix.value[1][1];
		scaleAxis1.z = ppvMng->m_matrix.value[2][1];
		PSVECScale(&scaleAxis1, &scaleAxis1, pppMngSt->m_scale.y);
		ppvMng->m_matrix.value[0][1] = scaleAxis1.x;
		ppvMng->m_matrix.value[1][1] = scaleAxis1.y;
		ppvMng->m_matrix.value[2][1] = scaleAxis1.z;
	}

	if (kPppPartOne == pppMngSt->m_scale.z) {
		return;
	}

	scaleAxis2.x = ppvMng->m_matrix.value[0][2];
	scaleAxis2.y = ppvMng->m_matrix.value[1][2];
	scaleAxis2.z = ppvMng->m_matrix.value[2][2];
	PSVECScale(&scaleAxis2, &scaleAxis2, pppMngSt->m_scale.z);
	ppvMng->m_matrix.value[0][2] = scaleAxis2.x;
	ppvMng->m_matrix.value[1][2] = scaleAxis2.y;
	ppvMng->m_matrix.value[2][2] = scaleAxis2.z;
	return;

MatrixMode3:
	if (pppMngSt->m_bindNode == 0) {
		goto LocalOnly;
	}

	if (pppMngSt->m_ownerFacing == 0) {
		u8 ownerWeaponFlagsHi = pppMngSt->m_owner->m_weaponNodeFlagBytes.m_flags0;
		pppMngSt->m_ownerFacing = static_cast<u8>(
		    static_cast<int>((static_cast<u32>(ownerWeaponFlagsHi) << 25) & 0xC0000000) >> 31);
	}

	if (pppMngSt->m_ownerFlagsInitialized == 0) {
		u8 visible = 0;
		u32 flags = pppMngSt->m_owner->m_displayFlags;
		if ((flags & 1) != 0 && (flags & 0x400000) == 0) {
			visible = 1;
		}
		pppMngSt->m_slotVisible = visible;
	}

	if (pppMngSt->m_nodeScaleInitialized == 0) {
		CCharaPcs::CHandle* ownerHandle = pppMngSt->m_owner->m_charaModelHandle;
		u8 hasModelScale = 0;
		if (ownerHandle != 0 && ownerHandle->m_model != 0) {
			hasModelScale = 1;
		}
		float ownerScale;
		if (hasModelScale != 0) {
			ownerScale = ownerHandle->m_model->m_lightAlpha;
		} else {
			ownerScale = pppMngSt->m_owner->m_lookAtTimer;
		}
		pppMngSt->m_ownerScale = ownerScale;
		if (kPppPartZeroDouble == static_cast<double>(pppMngSt->m_ownerScale)) {
			pppMngSt->m_useOwnerScaleSign = 1;
		} else if (kPppPartOneDouble == static_cast<double>(pppMngSt->m_ownerScale)) {
			pppMngSt->m_useOwnerScaleSign = 0;
		} else {
			pppMngSt->m_useOwnerScaleSign = 1;
		}
	}

	GetPppOwnerModel(pppMngSt)->CalcSafeNodeWorldMatrix(nodeMtx, pppMngSt->m_bindNode);

	goto ApplyRotatedMatrix;

MatrixMode4:
	MapMng.GetMapObjWMtx(pppMngSt->m_mapObjIndex, nodeMtx);

ApplyTranslatedMatrix:
	nodeMtx[0][3] += ppvMng->m_position.x;
	nodeMtx[1][3] += ppvMng->m_position.y;
	nodeMtx[2][3] += ppvMng->m_position.z;
	PSMTXConcat(nodeMtx, ppvMng->m_matrix.value, ppvMng->m_matrix.value);
	goto ScaleOnly;

MatrixMode5:
	if (pppMngSt->m_bindNode == 0) {
		goto LocalOnly;
	}

	if (pppMngSt->m_ownerFacing == 0) {
		u8 ownerWeaponFlagsHi = pppMngSt->m_owner->m_weaponNodeFlagBytes.m_flags0;
		pppMngSt->m_ownerFacing = static_cast<u8>(
		    static_cast<int>((static_cast<u32>(ownerWeaponFlagsHi) << 25) & 0xC0000000) >> 31);
	}

	if (pppMngSt->m_ownerFlagsInitialized == 0) {
		u8 visible = 0;
		u32 flags = pppMngSt->m_owner->m_displayFlags;
		if ((flags & 1) != 0 && (flags & 0x400000) == 0) {
			visible = 1;
		}
		pppMngSt->m_slotVisible = visible;
	}

	if (pppMngSt->m_nodeScaleInitialized == 0) {
		CCharaPcs::CHandle* ownerHandle = pppMngSt->m_owner->m_charaModelHandle;
		u8 hasModelScale = 0;
		if (ownerHandle != 0 && ownerHandle->m_model != 0) {
			hasModelScale = 1;
		}
		float ownerScale;
		if (hasModelScale != 0) {
			ownerScale = ownerHandle->m_model->m_lightAlpha;
		} else {
			ownerScale = pppMngSt->m_owner->m_lookAtTimer;
		}
		pppMngSt->m_ownerScale = ownerScale;
		if (kPppPartZeroDouble == static_cast<double>(pppMngSt->m_ownerScale)) {
			pppMngSt->m_useOwnerScaleSign = 1;
		} else if (kPppPartOneDouble == static_cast<double>(pppMngSt->m_ownerScale)) {
			pppMngSt->m_useOwnerScaleSign = 0;
		} else {
			pppMngSt->m_useOwnerScaleSign = 1;
		}
	}

	GetPppOwnerModel(pppMngSt)->CalcSafeNodeWorldMatrix(nodeMtx, pppMngSt->m_bindNode);

	goto ApplyTranslatedMatrix;

MatrixMode6:
	if (pppMngSt->m_bindNode == 0) {
		goto LocalOnly;
	}

	if (pppMngSt->m_ownerFacing == 0) {
		u8 ownerWeaponFlagsHi = pppMngSt->m_owner->m_weaponNodeFlagBytes.m_flags0;
		pppMngSt->m_ownerFacing = static_cast<u8>(
		    static_cast<int>((static_cast<u32>(ownerWeaponFlagsHi) << 25) & 0xC0000000) >> 31);
	}

	if (pppMngSt->m_ownerFlagsInitialized == 0) {
		u8 visible = 0;
		u32 flags = pppMngSt->m_owner->m_displayFlags;
		if ((flags & 1) != 0 && (flags & 0x400000) == 0) {
			visible = 1;
		}
		pppMngSt->m_slotVisible = visible;
	}

	if (pppMngSt->m_nodeScaleInitialized == 0) {
		CCharaPcs::CHandle* ownerHandle = pppMngSt->m_owner->m_charaModelHandle;
		u8 hasModelScale = 0;
		if (ownerHandle != 0 && ownerHandle->m_model != 0) {
			hasModelScale = 1;
		}
		float ownerScale;
		if (hasModelScale != 0) {
			ownerScale = ownerHandle->m_model->m_lightAlpha;
		} else {
			ownerScale = pppMngSt->m_owner->m_lookAtTimer;
		}
		pppMngSt->m_ownerScale = ownerScale;
		if (kPppPartZeroDouble == static_cast<double>(pppMngSt->m_ownerScale)) {
			pppMngSt->m_useOwnerScaleSign = 1;
		} else if (kPppPartOneDouble == static_cast<double>(pppMngSt->m_ownerScale)) {
			pppMngSt->m_useOwnerScaleSign = 0;
		} else {
			pppMngSt->m_useOwnerScaleSign = 1;
		}
	}

	GetPppOwnerModel(pppMngSt)->CalcSafeNodeWorldMatrix(nodeMtx, pppMngSt->m_bindNode);

	PSVECNormalize(reinterpret_cast<Vec*>(nodeMtx[0]), reinterpret_cast<Vec*>(nodeMtx[0]));
	PSVECNormalize(reinterpret_cast<Vec*>(nodeMtx[1]), reinterpret_cast<Vec*>(nodeMtx[1]));
	PSVECNormalize(reinterpret_cast<Vec*>(nodeMtx[2]), reinterpret_cast<Vec*>(nodeMtx[2]));
	goto ApplyRotatedMatrix;

MatrixMode7:
	if (pppMngSt->m_bindNode == 0) {
		goto LocalOnly;
	}

	if (pppMngSt->m_ownerFacing == 0) {
		u8 ownerWeaponFlagsHi = pppMngSt->m_owner->m_weaponNodeFlagBytes.m_flags0;
		pppMngSt->m_ownerFacing = static_cast<u8>(
		    static_cast<int>((static_cast<u32>(ownerWeaponFlagsHi) << 25) & 0xC0000000) >> 31);
	}

	if (pppMngSt->m_ownerFlagsInitialized == 0) {
		u8 visible = 0;
		u32 flags = pppMngSt->m_owner->m_displayFlags;
		if ((flags & 1) != 0 && (flags & 0x400000) == 0) {
			visible = 1;
		}
		pppMngSt->m_slotVisible = visible;
	}

	if (pppMngSt->m_nodeScaleInitialized == 0) {
		CCharaPcs::CHandle* ownerHandle = pppMngSt->m_owner->m_charaModelHandle;
		u8 hasModelScale = 0;
		if (ownerHandle != 0 && ownerHandle->m_model != 0) {
			hasModelScale = 1;
		}
		float ownerScale;
		if (hasModelScale != 0) {
			ownerScale = ownerHandle->m_model->m_lightAlpha;
		} else {
			ownerScale = pppMngSt->m_owner->m_lookAtTimer;
		}
		pppMngSt->m_ownerScale = ownerScale;
		if (kPppPartZeroDouble == static_cast<double>(pppMngSt->m_ownerScale)) {
			pppMngSt->m_useOwnerScaleSign = 1;
		} else if (kPppPartOneDouble == static_cast<double>(pppMngSt->m_ownerScale)) {
			pppMngSt->m_useOwnerScaleSign = 0;
		} else {
			pppMngSt->m_useOwnerScaleSign = 1;
		}
	}

	GetPppOwnerModel(pppMngSt)->CalcSafeNodeWorldMatrix(nodeMtx, pppMngSt->m_bindNode);

	PSMTXMultVecSR(nodeMtx, &ppvMng->m_position, &tmpPos);
	ppvMng->m_matrix.value[0][3] = nodeMtx[0][3] + tmpPos.x;
	ppvMng->m_matrix.value[1][3] = nodeMtx[1][3] + tmpPos.y;
	ppvMng->m_matrix.value[2][3] = nodeMtx[2][3] + tmpPos.z;
	goto ScaleOnly;

LocalOnly:
	localAxis0.x = ppvMng->m_matrix.value[0][0];
	localAxis0.y = ppvMng->m_matrix.value[1][0];
	localAxis0.z = ppvMng->m_matrix.value[2][0];
	PSVECScale(&localAxis0, &localAxis0, pppMngSt->m_scale.x);
	ppvMng->m_matrix.value[0][0] = localAxis0.x;
	ppvMng->m_matrix.value[1][0] = localAxis0.y;
	ppvMng->m_matrix.value[2][0] = localAxis0.z;

	localAxis1.x = ppvMng->m_matrix.value[0][1];
	localAxis1.y = ppvMng->m_matrix.value[1][1];
	localAxis1.z = ppvMng->m_matrix.value[2][1];
	PSVECScale(&localAxis1, &localAxis1, pppMngSt->m_scale.y);
	ppvMng->m_matrix.value[0][1] = localAxis1.x;
	ppvMng->m_matrix.value[1][1] = localAxis1.y;
	ppvMng->m_matrix.value[2][1] = localAxis1.z;

	localAxis2.x = ppvMng->m_matrix.value[0][2];
	localAxis2.y = ppvMng->m_matrix.value[1][2];
	localAxis2.z = ppvMng->m_matrix.value[2][2];
	PSVECScale(&localAxis2, &localAxis2, pppMngSt->m_scale.z);
	ppvMng->m_matrix.value[0][2] = localAxis2.x;
	ppvMng->m_matrix.value[1][2] = localAxis2.y;
	ppvMng->m_matrix.value[2][2] = localAxis2.z;

	ppvMng->m_matrix.value[0][3] = pppMngSt->m_position.x;
	ppvMng->m_matrix.value[1][3] = pppMngSt->m_position.y;
	ppvMng->m_matrix.value[2][3] = pppMngSt->m_position.z;
}

/*
 * --INFO--
 * PAL Address: 800558d4
 * PAL Size: 684b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static inline float LoadFloat(const float& f) { return f; }

#pragma push
#pragma opt_common_subs off
void pppSetFpMatrix(_pppMngSt* pppMngSt)
{
	Vec local_a8;
	Vec local_9c;
	Vec local_90;
	Vec local_80;
	Vec local_70;
	Vec local_60;
	Vec local_50;
	Mtx local_44;

	PSMTXCopy(ppvMng->m_matrix.value, local_44);
	if (pppMngSt->m_fpBillboard != 0) {
		PSMTXConcat(ppvCameraMatrix, ppvMng->m_matrix.value, ppvWorldMatrix);
		local_50.x = local_44[0][3];
		local_50.y = local_44[1][3];
		local_50.z = local_44[2][3];
		PSMTXMultVecSR(ppvCameraMatrix, &local_50, &local_50);
		local_50.y += CameraPcs.m_positionY;
		ppvWorldMatrix[0][3] = local_50.x;
		ppvWorldMatrix[1][3] = local_50.y;
		ppvWorldMatrix[2][3] = local_50.z;
	} else {
		PSMTXConcat(ppvCameraMatrix, ppvMng->m_matrix.value, ppvWorldMatrix);
		local_50.x = local_44[0][3];
		local_50.y = local_44[1][3];
		local_50.z = local_44[2][3];
		PSMTXMultVec(ppvCameraMatrix, &local_50, &local_50);
		ppvWorldMatrix[0][3] = local_50.x;
		ppvWorldMatrix[1][3] = local_50.y;
		ppvWorldMatrix[2][3] = local_50.z;
	}

	local_70.x = ppvWorldMatrix[0][1];
	local_70.y = ppvWorldMatrix[1][1];
	local_70.z = ppvWorldMatrix[2][1];
	((u32*)&local_90)[0] = ((u32*)&local_70)[0];
	((u32*)&local_90)[1] = ((u32*)&local_70)[1];
	((u32*)&local_90)[2] = ((u32*)&local_70)[2];
	if ((local_90.x != LoadFloat(kPppPartZero)) || (local_90.y != LoadFloat(kPppPartZero)) || (local_90.z != LoadFloat(kPppPartZero))) {
		PSVECNormalize(&local_90, &local_70);
	}

	local_9c.x = local_70.y;
	local_9c.y = -local_70.x;
	local_9c.z = LoadFloat(kPppPartZero);
	ppvWorldMatrixWood[0][1] = local_70.x;
	ppvWorldMatrixWood[1][1] = local_70.y;
	ppvWorldMatrixWood[2][1] = local_70.z;
	((u32*)&local_60)[0] = ((u32*)&local_9c)[0];
	((u32*)&local_60)[1] = ((u32*)&local_9c)[1];
	((u32*)&local_60)[2] = ((u32*)&local_9c)[2];

	if ((local_60.x != LoadFloat(kPppPartZero)) || (local_60.y != LoadFloat(kPppPartZero)) || (local_60.z != LoadFloat(kPppPartZero))) {
		PSVECNormalize(&local_60, &local_9c);
	}

	ppvWorldMatrixWood[0][0] = local_9c.x;
	ppvWorldMatrixWood[1][0] = local_9c.y;
	ppvWorldMatrixWood[2][0] = local_9c.z;
	PSVECCrossProduct(&local_9c, &local_70, &local_80);
	((u32*)&local_a8)[0] = ((u32*)&local_80)[0];
	((u32*)&local_a8)[1] = ((u32*)&local_80)[1];
	((u32*)&local_a8)[2] = ((u32*)&local_80)[2];

	if ((local_a8.x != LoadFloat(kPppPartZero)) || (local_a8.y != LoadFloat(kPppPartZero)) || (local_a8.z != LoadFloat(kPppPartZero))) {
		PSVECNormalize(&local_a8, &local_80);
	}

	ppvWorldMatrixWood[0][2] = local_80.x;
	ppvWorldMatrixWood[1][2] = local_80.y;
	ppvWorldMatrixWood[2][2] = local_80.z;
	ppvWorldMatrixWood[0][3] = ppvWorldMatrix[0][3];
	ppvWorldMatrixWood[1][3] = ppvWorldMatrix[1][3];
	ppvWorldMatrixWood[2][3] = ppvWorldMatrix[2][3];
}
#pragma pop

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 208b
 * EN Address: 0x80063EA4
 * EN Size: 248b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void pppCacheLoadModel(short* modelList, _pppDataHead* head)
{
	short modelCount = *modelList++;
	for (short i = 0; i < modelCount; i++)
	{
		pppModelSt* mapMesh = ((pppModelSt**)head->m_modelNames)[*modelList++];
		if (ppvAmemCacheSet.IsEnable(mapMesh->m_cacheId) == 0)
		{
			mapMesh->Ptr2Off();
			mapMesh->m_meshData =
			    reinterpret_cast<void*>(ppvAmemCacheSet.GetData(mapMesh->m_cacheId, (char*)s_pppPart_cpp, 0x4E5));
			mapMesh->Off2Ptr();
		}
		ppvAmemCacheSet.AddRef(mapMesh->m_cacheId);
		mapMesh->pppCacheLoadModelTexture(PartMng.m_materialSet, &ppvAmemCacheSet);
	}
}

/*
 * --INFO--
 * PAL Address: 80055868
 * PAL Size: 108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppCacheLoadShape(short* shapeList, _pppDataHead* pppDataHead)
{
	short shapeCount = *shapeList;
	short i = 0;
	shapeList = shapeList + 1;

	while (i < shapeCount) {
		short shapeIndex = *shapeList;
		shapeList = shapeList + 1;
		pppCacheLoadShapeTexture(
		    *(pppShapeSt**)(pppDataHead->m_shapeNames + shapeIndex * 4),
		    PartMng.m_materialSet);
		++i;
	}
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 120b
 * EN Address: 0x80062BD8
 * EN Size: 120b
 * JP Address: TODO
 * JP Size: TODO
 */
static inline void callInitProg(_pppMngSt* pppMngSt)
{
	for (int i = 0; i < pppMngSt->m_numControlPrograms; i++)
	{
		pppProg* prog = ((pppProg**)pppMngSt->m_pppPObjLinkHead.m_owner)[i];
		pppProgInitCallback fn = prog->m_pppFunctionInit;
		if (fn != 0)
		{
			fn(pppMngSt);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 80055308
 * PAL Size: 1376b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _pppStartPart(_pppMngSt* pppMngSt, long* pdt, int runControlPrograms)
{
	_pppProgSetDef* programSet = (_pppProgSetDef*)(pdt + 6);
	ppvMng = pppMngSt;
	pppMngSt->m_lifeEnd = (int)pdt[0];
	pppMngSt->m_mode = (u8)pdt[1];
	int* controlPrograms = (int*)((u8*)pdt + pdt[2]);
	int* programs = (int*)((u8*)pdt + pdt[3]);
	short* modelIndices = (short*)((u8*)pdt + pdt[4]);
	short* shapeIndices = (short*)((u8*)pdt + pdt[5]);

	if (Game.m_currentSceneId != 7)
	{
		CPartMng::PppPdtSlot* slot = (CPartMng::PppPdtSlot*)pppMngSt->m_pppResSet;
		pppCacheLoadModel(modelIndices, slot->m_pppDataHead);
		pppCacheLoadShape(shapeIndices, slot->m_pppDataHead);

		pppMngSt->m_mapTexLoaded = 1;
	}

	pppMngSt->m_isFinished = 0;
	pppMngSt->m_numControlPrograms = *controlPrograms++;
	pppMngSt->m_pppPObjLinkHead.m_owner = (_pppPDataVal*)controlPrograms;
	pppMngSt->m_numPrograms = *programs++;
	pppMngSt->m_programTable = programs;

	if (pppMngSt->m_numPrograms != 0)
	{
		u32 allocSize = pppMngSt->m_numPrograms * sizeof(_pppPDataVal);
		CMemory::CStage* stage = ppvEnv->m_stagePtr;
		int firstAllocFailure = 1;
		int canRetry;
		_pppPDataVal* pDataVals = 0;
		char denied[0x180];

		ppvMemAllocErrorF = 0;
		do
		{
			pDataVals = (_pppPDataVal*)Memory._Alloc(
			    allocSize, stage, (char*)s_pppPart_cpp, 0x585, 1);
			if (pDataVals != 0)
			{
				goto DataValsAllocated;
			}

			if (firstAllocFailure)
			{
				firstAllocFailure = 0;
				memset(denied, 0, sizeof(denied));
				int currentIdx = ppvMng - PartMng.m_pppMng;
				denied[currentIdx] = 1;
			}

			canRetry = pppFreeMngStPrioForHeap(denied);
		}
		while (canRetry);

		ppvEnv->m_stagePtr->heapWalker(2, 0, 0xFFFFFFFF);
		PartMng.pppDumpMngSt();
		ppvMemAllocErrorF = 1;
DataValsAllocated:
		pppMngSt->m_pppPDataVals = pDataVals;
	}
	else
	{
		pppMngSt->m_pppPDataVals = 0;
	}

	_pppProgSetDef* programSetIt = programSet;
	if (programSet->m_next != 0)
	{
		pppMngSt->m_pppPObjLinkHead.m_previous = 0;
	}

	pppMngSt->m_currentFrame = 0;
	if (pppMngSt->m_numPrograms == 0)
	{
		pppMngSt->m_pppPObjLinkHead.m_previous = 0;
	}
	else
	{
		pppMngSt->m_pppPObjLinkHead.m_previous = (_pppPObjLink*)programSetIt;
	}

	pppMngSt->m_pppPObjLinkHead.m_next = 0;
	pppMngSt->m_spawnedCount = 0;

	u8 index = 0;
	_pppPDataVal* pDataVals = pppMngSt->m_pppPDataVals;
	for (; programSetIt != 0; programSetIt = programSetIt->m_next)
	{
		pDataVals->m_programSetDef = programSetIt;
		pDataVals->m_nextSpawnTime = programSetIt->m_startFrame;
		pDataVals->m_pppPObjLink = 0;
		pDataVals->m_activeCount = 0;
		pDataVals->m_index = index;
		index++;
		pDataVals++;
	}

	if (runControlPrograms != 0)
	{
		callInitProg(pppMngSt);
	}
}

/*
 * --INFO--
 * PAL Address: 800550ac
 * PAL Size: 604b
 * EN Address: 0x800646BC
 * EN Size: 556b
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma opt_common_subs off
void pppInitPdt(long* progOffsetReconstructionTable, pppProg* pppProg)
{
	_pppProgSetDef* table = (_pppProgSetDef*)(progOffsetReconstructionTable + 6);
	int* pppProgRelocs = (int*)((int)progOffsetReconstructionTable + progOffsetReconstructionTable[2]);
	int* pdtRelocs = (int*)((int)progOffsetReconstructionTable + progOffsetReconstructionTable[3]);
	int pppProgRelocCount = *pppProgRelocs++;
	int pdtRelocCount = *pdtRelocs++;

	if (table->m_next == 0) {
		return;
	}

	for (;;) {
		table->m_next = (_pppProgSetDef*)((u8*)progOffsetReconstructionTable + (u32)table->m_next);
		for (int i = 0; i < table->m_numStages; i++) {
			_pppCtrlTable* entry = &table->m_stages[i];
			entry->m_prog = pppProg + (u32)entry->m_prog;
			entry->m_unk8 = (int)progOffsetReconstructionTable + entry->m_unk8;
			entry->m_serializedDataOffsets = (int*)((u8*)progOffsetReconstructionTable + (u32)entry->m_serializedDataOffsets);
		}

		_pppProgSetDef* next = table->m_next;
		if (next->m_next == 0) {
			table->m_next = 0;
			break;
		}
		table = next;
	}

	for (int i = 0; i < pppProgRelocCount; i++) {
		pppProgRelocs[i] = (int)(pppProg + pppProgRelocs[i]);
	}

	for (int i = 0; i < pdtRelocCount; i++) {
		pdtRelocs[i] += (int)progOffsetReconstructionTable;
	}
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 80054d88
 * PAL Size: 804b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppInitData(_pppDataHead* pppDataHead, pppProg* pppProg, int param_3)
{
	u8* dataBase = reinterpret_cast<u8*>(&pppDataHead->m_version);

	pppDataHead->m_cacheChunks = pppDataHead->m_cacheChunks + reinterpret_cast<u32>(dataBase);
	pppDataHead->m_modelNames = pppDataHead->m_modelNames + reinterpret_cast<u32>(dataBase);
	pppDataHead->m_shapeNames = pppDataHead->m_shapeNames + reinterpret_cast<u32>(dataBase);
	pppDataHead->m_shapeGroups = pppDataHead->m_shapeGroups + reinterpret_cast<u32>(dataBase);

	int* chunkOffsets = reinterpret_cast<int*>(pppDataHead->m_cacheChunks);
	pppCacheChunk* cacheChunks = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_pppPart_cpp), 0x620)
	    pppCacheChunk[pppDataHead->m_cacheChunkCount];
	pppDataHead->m_cacheChunks = reinterpret_cast<u32>(cacheChunks);

	for (int i = 0; i < pppDataHead->m_cacheChunkCount; i++) {
		u8* chunkSrc = (u8*)(chunkOffsets[0] + (int)dataBase);
		int chunkSize = chunkOffsets[1] - chunkOffsets[0];
		u8* chunkData = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_pppPart_cpp), 0x626) u8[chunkSize];

		memcpy(chunkData, chunkSrc, chunkSize);
		reinterpret_cast<pppCacheChunk*>(pppDataHead->m_cacheChunks)[i].m_cacheIndex =
		    ppvAmemCacheSet.SetData(chunkData, chunkSize, CAmemCache::PDT, param_3);
		delete chunkData;
		chunkOffsets++;
	}

	char* modelName = reinterpret_cast<char*>(pppDataHead->m_modelNames);
	pppModelSt** modelRefs = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_pppPart_cpp), 0x636)
	    pppModelSt*[pppDataHead->m_modelCount];
	pppDataHead->m_modelNames = reinterpret_cast<u32>(modelRefs);

	for (int i = 0; i < pppDataHead->m_modelCount; i++) {
		u32 j = 0;
		pppModelSt* model = PartMng.m_modelSet->m_models;
		pppModelSt* foundModel;
		for (; j < 0x100; j++) {
			if (model->m_isUsed != 0 && strcmp(model->m_name, modelName) == 0) {
				foundModel = model;
				goto modelFound;
			}
			model++;
		}
		foundModel = 0;
	modelFound:
		model = foundModel;

		modelName += 0x20;
		reinterpret_cast<pppModelSt**>(pppDataHead->m_modelNames)[i] = model;
		reinterpret_cast<pppModelSt**>(pppDataHead->m_modelNames)[i]->AddRef();
	}

	char* shapeName = reinterpret_cast<char*>(pppDataHead->m_shapeNames);
	pppShapeSt** shapeRefs = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_pppPart_cpp), 0x643)
	    pppShapeSt*[pppDataHead->m_shapeCount];
	pppDataHead->m_shapeNames = reinterpret_cast<u32>(shapeRefs);

	for (int i = 0; i < pppDataHead->m_shapeCount; i++) {
		u32 j = 0;
		pppShapeSt* shape = PartMng.m_shapeSet->m_shapes;
		pppShapeSt* foundShape;
		for (; j < 0x100; j++) {
			if (shape->m_inUse != 0 && strcmp(shape->m_name, shapeName) == 0) {
				foundShape = shape;
				goto shapeFound;
			}
			shape++;
		}
		foundShape = 0;
	shapeFound:
		shape = foundShape;

		shapeName += 0x20;
		reinterpret_cast<pppShapeSt**>(pppDataHead->m_shapeNames)[i] = shape;
		reinterpret_cast<pppShapeSt**>(pppDataHead->m_shapeNames)[i]->AddRef();
	}

	pppShapeGroupRaw* shapeGroups = reinterpret_cast<pppShapeGroupRaw*>(pppDataHead->m_shapeGroups);
	pppShapeGroupRaw* shapeGroupRefs = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_pppPart_cpp), 0x651)
	    pppShapeGroupRaw[pppDataHead->m_shapeGroupCount];
	pppDataHead->m_shapeGroups = reinterpret_cast<u32>(shapeGroupRefs);

	for (int i = 0; i < pppDataHead->m_shapeGroupCount; i++) {
		reinterpret_cast<pppShapeGroupRaw*>(pppDataHead->m_shapeGroups)[i].m_groupId = shapeGroups->m_groupId;
		reinterpret_cast<pppShapeGroupRaw*>(pppDataHead->m_shapeGroups)[i].m_shapeCount = shapeGroups->m_shapeCount;
		reinterpret_cast<pppShapeGroupRaw*>(pppDataHead->m_shapeGroups)[i].m_shapeList =
		    new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_pppPart_cpp), 0x656) s16[shapeGroups->m_shapeCount];

		shapeGroups->m_shapeList = reinterpret_cast<s16*>(reinterpret_cast<u8*>(shapeGroups->m_shapeList) + reinterpret_cast<u32>(dataBase));
		memcpy(reinterpret_cast<pppShapeGroupRaw*>(pppDataHead->m_shapeGroups)[i].m_shapeList, shapeGroups->m_shapeList, static_cast<int>(shapeGroups->m_shapeCount) << 1);
		shapeGroups++;
	}
}

/*
 * --INFO--
 * PAL Address: 80054c58
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppCalcPartStd(_pppMngSt* pppMngSt)
{
	s32 i = 0;
	s32 pDataValOffset = 0;
	for (; i < pppMngSt->m_numPrograms; i++)
	{
		_pppPDataVal* pDataVal = (_pppPDataVal*)((u8*)pppMngSt->m_pppPDataVals + pDataValOffset);
		if (pDataVal != 0 && pDataVal->m_programSetDef != 0)
		{
			_pppProgSetDef* progSet = pDataVal->m_programSetDef;
			pobjcounter += pDataVal->m_activeCount;

			if (pDataVal->m_activeCount != 0)
			{
				s32 workOffsetStep = 0;
				_pppProgSetDef* stageSet = progSet;

				for (s32 stage = 0; stage < progSet->m_numStages; stage++)
				{
					_pppCtrlTable* stageIter = stageSet->m_stages;
					pppProg* prog = stageIter->m_prog;
					if (prog != 0)
					{
						pppProgOperationCallback fn = (pppProgOperationCallback)prog->m_pppFunctionOperation;
						_pppPObjLink* obj = pDataVal->m_pppPObjLink;
						if (fn != 0)
						{
							u32 count = pDataVal->m_activeCount;

							do
							{
								if (((_pppPObject*)obj)->m_field7C == 0)
								{
									_pppPObjLink* next = obj->m_next;
									fn((_pppPObject*)obj,
									   *(void**)(((u8*)obj) + progSet->m_workBaseOffset + workOffsetStep),
									   stageIter);
									obj = next;
								}
								else
								{
									obj = obj->m_next;
								}
							}
							while (--count != 0);
						}
					}
					else
					{
						printf(sPppProgNullErrorMsg);
					}

					stageSet = (_pppProgSetDef*)(((u8*)stageSet) + sizeof(_pppCtrlTable));
					workOffsetStep += 4;
				}
			}
		}
		pDataValOffset += sizeof(_pppPDataVal);
	}

	if (pppMngSt->m_prioTime < 0xFFFF)
	{
		pppMngSt->m_prioTime++;
	}
}

/*
 * --INFO--
 * PAL Address: 80054b30
 * PAL Size: 296b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawPartStd(_pppMngSt* pppMngSt)
{
	s32 pDataValOffset = 0;
	for (s32 i = 0; i < pppMngSt->m_numPrograms; i++)
	{
		_pppPDataVal* pDataVal = (_pppPDataVal*)((u8*)pppMngSt->m_pppPDataVals + pDataValOffset);
		if (pDataVal != 0 && pDataVal->m_programSetDef != 0 &&
		    (s8)((s32)(((u32)pDataVal->m_programSetDef->m_drawFlags << 24) & 0xC0000000) >> 31) == 0 && pDataVal->m_activeCount > 0)
		{
			s32 workOffsetStep = 0;
			_pppProgSetDef* progSet = pDataVal->m_programSetDef;
			_pppProgSetDef* stageSet = progSet;

			for (s32 stage = 0; stage < progSet->m_numStages; stage++)
			{
				_pppCtrlTable* stageIter = stageSet->m_stages;
				pppProg* prog = stageIter->m_prog;
				if (prog != 0)
				{
					pppProgRenderCallback fn = (pppProgRenderCallback)prog->m_pppFunctionRender;
					_pppPObjLink* obj = pDataVal->m_pppPObjLink;
					if (fn != 0)
					{
						u32 count = pDataVal->m_activeCount;

						do
						{
							if (((_pppPObject*)obj)->m_field7C == 0)
							{
								fn((_pppPObject*)obj,
								   *(void**)(((u8*)obj) + progSet->m_workBaseOffset + workOffsetStep),
								   stageIter);
							}
							count--;
							obj = obj->m_next;
						}
						while (count != 0);

						Graphic.SetDrawDoneDebugDataPartControl(0x7FFF);
					}
				}
				else
				{
					printf(sPppProgNullErrorMsg);
				}

				stageSet = (_pppProgSetDef*)(((u8*)stageSet) + sizeof(_pppCtrlTable));
				workOffsetStep += 4;
			}
		}
		pDataValOffset += sizeof(_pppPDataVal);
	}
}
/*
 * --INFO--
 * PAL Address: 80054818
 * PAL Size: 792b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma optimization_level 3
void _pppDeadPart(_pppMngSt* pppMngSt)
{
	_pppMngSt* mng = pppMngSt;
	u32 maxDeleteFrame;

	if (ppvUserStopPartF == 0)
	{
		maxDeleteFrame = 0;
		_pppPObjLink* obj = mng->m_pppPObjLinkHead.m_next;
		_pppPObjLink* prev = &mng->m_pppPObjLinkHead;
		for (; obj != 0;)
		{
			_pppPObjLink* next = obj->m_next;
			if (((_pppPObject*)obj)->m_field7C == 0)
			{
				_pppPDataVal* owner = (_pppPDataVal*)obj->m_owner;
				_pppProgSetDef* progSet = owner->m_programSetDef;
				int stageIdx = 0;

				((_pppPObject*)obj)->m_graphId += 0x1000;

				for (stageIdx = 0; stageIdx < progSet->m_numStages; stageIdx++)
				{
					_pppCtrlTable* stage = &progSet->m_stages[stageIdx];
					u32 stageSlotOffset = progSet->m_workBaseOffset + stageIdx * 4;
					u32* stageSlot = *(u32**)(((u8*)obj) + stageSlotOffset);
					u32* nextSlot = (u32*)(((u8*)stageSlot) + stage->m_workOffset);
					if ((s32)*nextSlot == ((_pppPObject*)obj)->m_graphId)
					{
						*(u32**)(((u8*)obj) + stageSlotOffset) = nextSlot;
					}
				}

				if (mng->m_particleEnded == 0 &&
					((_pppPObject*)obj)->m_graphId >= progSet->m_loopFrame &&
					progSet->m_loopFrame != 0x70000000)
				{
					((_pppPObject*)obj)->m_graphId = progSet->m_endFrame;
					callCon2Prog((_pppPObject*)obj);
				}
				else
				{
					maxDeleteFrame |= progSet->m_deadFrame;
					if ((u32)((_pppPObject*)obj)->m_graphId >= (u32)progSet->m_deadFrame)
					{
						prev->m_next = next;

						pppDeletePObject((_pppPObject*)obj);
						goto nextIter;
					}
					else
					{
						goto doPrev;
					}
				}
			}
			else
			{
			doPrev:
				prev = obj;
			}
		nextIter:

			obj = next;
		}

		if (mng->m_particleEnded != 0 && maxDeleteFrame == 0x70000000)
		{
			for (_pppPObjLink* obj = mng->m_pppPObjLinkHead.m_next; obj != 0;)
			{
				_pppPObjLink* next = obj->m_next;
				pppDeletePObject((_pppPObject*)obj);
				obj = next;
			}

			mng->m_pppPObjLinkHead.m_next = 0;
		}
	}

	if (ppvUserStopPartF == 0)
	{
		mng->m_previousFrame2 = mng->m_currentFrame;
		mng->m_currentFrame += 0x1000;
	}

	if (mng->m_mode != 0)
	{
		if (mng->m_particleEnded != 0)
		{
			mng->m_isFinished = (mng->m_pppPObjLinkHead.m_next == 0) ? 1 : 0;
		}
		else if (mng->m_currentFrame >= 0x70000000)
		{
			mng->m_previousFrame2 = 0x6FFFF000;
			mng->m_currentFrame = 0x70000000;
		}
	}
	else
	{
		mng->m_isFinished = (mng->m_currentFrame >= mng->m_lifeEnd) ? 1 : 0;
	}
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 800547ec
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _pppInitPart(_pppMngSt* pppMngSt)
{
	if (ppvUserStopPartF != 0)
	{
		return;
	}

	for (_pppPObjLink* obj = pppMngSt->m_pppPObjLinkHead.m_next; obj != 0; obj = obj->m_next)
	{
		((_pppPObject*)obj)->m_field7C = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 80054698
 * PAL Size: 340b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _pppCalcPart(_pppMngSt* pppMngSt)
{
	PPPSEST* se = &pppMngSt->m_soundEffectData;
	pppFMATRIX* mtx = &pppMngSt->m_matrix;

	ppvMng = pppMngSt;
	if (se->m_soundEffectSlot >= 0 &&
		pppMngSt->m_currentFrame >= se->m_soundEffectStartFrame)
	{
		switch ((s32)se->m_soundEffectStopFlag)
		{
		case 0:
		{
			Vec soundPos;
			soundPos.x = mtx->value[0][3];
			soundPos.y = mtx->value[1][3];
			soundPos.z = mtx->value[2][3];

			if (se->m_soundEffectHandle < 0)
			{
				if (se->m_soundEffectStartedOnce == 0)
				{
					u32 soundTableKind = (u32)se->m_soundEffectKind;
					se->m_soundEffectHandle = Sound.PlaySe3D(
						se->m_soundEffectSlot, &soundPos,
						PartMng.m_soundNearDistance[soundTableKind],
						PartMng.m_soundFarDistance[soundTableKind], 0);
					se->m_soundEffectStartedOnce = 1;
				}
			}
			else
			{
				Sound.ChangeSe3DPos(se->m_soundEffectHandle, &soundPos);
			}
			break;
		}
		}
	}

	for (s32 i = 0; i < pppMngSt->m_numPrograms; i++)
	{
		_pppPDataVal* pDataVals = pppMngSt->m_pppPDataVals;
		if (pDataVals != 0)
		{
			_pppPDataVal* pDataVal = &pDataVals[i];
			if (pDataVal != 0 && pppMngSt->m_currentFrame >= pDataVal->m_nextSpawnTime)
			{
				pDataVal->m_nextSpawnTime = 0x7FFFFFFF;
				_pppPObject* pObject = pppCreatePObject(pppMngSt, pDataVal);
				if (pObject == 0)
				{
					break;
				}
				pObject->m_field7C = 0;
			}
		}
	}

	pppCalcPartStd(pppMngSt);
}

/*
 * --INFO--
 * PAL Address: 80054674
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _pppDrawPart(_pppMngSt* pppMngSt)
{
	ppvMng = pppMngSt;
	pppDrawPartStd(pppMngSt);
}

/*
 * --INFO--
 * PAL Address: 80054588
 * PAL Size: 236b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMesh(pppModelSt* model, Vec* positions, int usePartMaterial)
{
	MaterialMan.SaveCurrentEnvAsStd();

	if (positions == 0)
	{
		GXSetArray((GXAttr)9, model->m_vertices, 0xC);
	}
	else
	{
		GXSetArray((GXAttr)9, positions, 0xC);
	}

	GXSetArray((GXAttr)0xB, model->m_colors, 4);
	GXSetArray((GXAttr)0xD, model->m_uvPairs, 4);
	GXSetArray((GXAttr)0xE, model->m_uvPairs, 4);
	MaterialMan.SetGeometryArraySource(model->m_normals);

	if (usePartMaterial == 0)
	{
		GXSetArray((GXAttr)10, MaterialMan.GetGeometryArraySource(), 6);
	}

	model->DrawPart(ppvEnv->m_materialSetPtr, usePartMaterial);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppInitBlendMode()
{
	s_blend_mode = 0xFF;
}

/*
 * --INFO--
 * PAL Address: 80054440
 * PAL Size: 316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSetBlendMode(unsigned char blendMode)
{
	if ((blendMode != 0xFF) && (s_blend_mode != blendMode))
	{
		s_blend_mode = blendMode;
		switch (blendMode) {
		case 0:
			_GXSetBlendMode((_GXBlendMode)1, (_GXBlendFactor)4, (_GXBlendFactor)5, (_GXLogicOp)5);
			_GXSetAlphaCompare((_GXCompare)7, 0, (_GXAlphaOp)0, (_GXCompare)7, 0xFF);
			GXSetZCompLoc((GXBool)1);
			break;
		case 1:
			_GXSetBlendMode((_GXBlendMode)1, (_GXBlendFactor)4, (_GXBlendFactor)1, (_GXLogicOp)5);
			_GXSetAlphaCompare((_GXCompare)7, 0, (_GXAlphaOp)0, (_GXCompare)7, 0xFF);
			GXSetZCompLoc((GXBool)1);
			break;
		case 2:
			_GXSetBlendMode((_GXBlendMode)3, (_GXBlendFactor)4, (_GXBlendFactor)1, (_GXLogicOp)5);
			_GXSetAlphaCompare((_GXCompare)7, 0, (_GXAlphaOp)0, (_GXCompare)7, 0xFF);
			GXSetZCompLoc((GXBool)1);
			break;
		case 3:
			_GXSetBlendMode((_GXBlendMode)0, (_GXBlendFactor)6, (_GXBlendFactor)5, (_GXLogicOp)5);
			_GXSetAlphaCompare((_GXCompare)7, 0, (_GXAlphaOp)0, (_GXCompare)7, 0xFF);
			GXSetZCompLoc((GXBool)1);
			break;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 800543f8
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppClearDrawEnv()
{
	if (kPppPartZero != s_zoff) {
		s_zoff = kPppPartZero;
		ppvScreenMatrix[2][3] = ppvScreenMatrixZbuff;
		GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);
	}
}

/*
 * --INFO--
 * PAL Address: 80054108
 * PAL Size: 752b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSetDrawEnv(pppCVECTOR* pppColor, pppFMATRIX* pppMtx, float depth, unsigned char lightTarget, unsigned char fogIndex, unsigned char fogParam, unsigned char cullMode, unsigned char zEnable, unsigned char colorUpdate, unsigned char zWrite)
{
	if (kPppPartZeroDouble != (double)depth) {
		float sortDepth = ppvMng->m_sortDepth;
		depth = (depth * kPppPartDepthScale) / -sortDepth;
	}

	if ((double)s_zoff != (double)depth) {
		s_zoff = depth;
		ppvScreenMatrix[2][3] = ppvScreenMatrixZbuff + depth;
		GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);
	}

	MaterialMan.SetDefaultStdDrawEnv(0x000ACE0F);

	if (s_light_mode != lightTarget) {
		s_light_mode = lightTarget;
		LightPcs.SetPart(static_cast<CLightPcs::TARGET>(2), ppvMng, lightTarget);
	}

	if (pppMtx != 0) {
		GXLoadPosMtxImm(pppMtx->value, GX_PNMTX0);
		if (lightTarget != 0) {
			Mtx nrmMtx;
			nrmMtx[0][0] = pppMtx->value[0][0];
			nrmMtx[1][0] = pppMtx->value[1][0];
			nrmMtx[2][0] = pppMtx->value[2][0];
			nrmMtx[0][1] = pppMtx->value[0][1];
			nrmMtx[1][1] = pppMtx->value[1][1];
			nrmMtx[2][1] = pppMtx->value[2][1];
			nrmMtx[0][2] = pppMtx->value[0][2];
			nrmMtx[1][2] = pppMtx->value[1][2];
			nrmMtx[2][2] = pppMtx->value[2][2];
			nrmMtx[0][3] = kPppLocalZero;
			nrmMtx[1][3] = kPppLocalZero;
			nrmMtx[2][3] = kPppLocalZero;
			GXLoadNrmMtxImm(nrmMtx, GX_PNMTX0);
		}
	}

	_GXColor fixedColor;
	*(u32*)&fixedColor = gPppFixedWhite;
	if (lightTarget <= 1) {
		if (pppColor != 0) {
			GXSetChanAmbColor(GX_COLOR0A0, *(_GXColor*)pppColor->rgba);
		}
		GXSetChanMatColor(GX_COLOR0A0, fixedColor);
	} else {
		if (pppColor != 0) {
			GXSetChanMatColor(GX_COLOR0A0, *(_GXColor*)pppColor->rgba);
		}
		GXSetChanAmbColor(GX_COLOR0A0, fixedColor);
	}

	if ((s_fog_mode != fogIndex) || (s_fog_blend_mode != fogParam)) {
		u8 fogTest = (u8)(fogParam - 1) <= 1;
		u8 fogEnable = 1;
		s_fog_mode = fogIndex;
		s_fog_blend_mode = fogParam;
		if (!fogTest) {
			fogEnable = 0;
		}
		Graphic.SetFog((int)fogIndex, fogEnable);
	}

	if (s_cull_mode != cullMode) {
		s_cull_mode = cullMode;
		GXSetCullMode((GXCullMode)cullMode);
	}

	if ((s_ztest != zEnable) || (s_zwrite != zWrite)) {
		s_ztest = zEnable;
		s_zwrite = zWrite;
		GXSetZMode(zEnable, GX_LEQUAL, zWrite);
	}

	if (s_rgbwrite != colorUpdate) {
		s_rgbwrite = colorUpdate;
		GXSetColorUpdate(colorUpdate);
	}
}

/*
 * --INFO--
 * PAL Address: 80054070
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppInitDrawEnv(unsigned char useZeroDepth)
{
	MaterialMan.InitVtxFmt(
		-1,
		(_GXCompType)4,
		0,
		(_GXCompType)3,
		0xE,
		(_GXCompType)3,
		10
	);

	s_light_mode = 0xFF;
	s_blend_mode = 0xFF;
	s_fog_mode = 0xFF;
	s_cull_mode = 0xFF;
	s_ztest = 0xFF;
	s_rgbwrite = 0xFF;
	s_zwrite = 0xFF;

	if (useZeroDepth != 0)
	{
		s_zoff = kPppPartZero;
	}
	else
	{
		s_zoff = kPppPartZOffsetMin;
	}

	LightPcs.SetNumDiffuse(0);
}

/*
 * --INFO--
 * PAL Address: 0x80053d04
 * PAL Size: 876b
 * EN Address: 0x80065E74
 * EN Size: 796b
 * JP Address: TODO
 * JP Size: TODO
 */
int pppHitCylinderSendSystem(_pppMngSt* pppMngSt, Vec* origin, Vec* vector, float radius, float cylScale)
{
	int hadHit = 0;

	if (kPppPartZero != cylScale)
	{
		u32 cylinderAttribute = pppMngSt->m_cylinderAttribute;
		CMapCylinder cylinder(kMapHitBoundsMinInit, kMapHitBoundsMaxInit);
		cylinder.m_bottom = *origin;
		cylinder.m_axis = *vector;
		cylinder.m_radius = cylScale;

		if (MapMng.CheckHitCylinder(&cylinder, vector, cylinderAttribute) != 0)
		{
			if (Game.m_currentSceneId == 7)
			{
				pppMngSt->m_hitBgFlag = 1;
				if ((pppMngSt->m_soundEffectData.m_soundEffectSlot >= 0) &&
					(pppMngSt->m_soundEffectData.m_soundEffectHandle >= 0))
				{
					Sound.FadeOutSe3D(pppMngSt->m_soundEffectData.m_soundEffectHandle,
						pppMngSt->m_soundEffectData.m_soundEffectFadeFrames);
					pppMngSt->m_soundEffectData.m_soundEffectHandle = -1;
				}
			}
			else
			{
				Vec hitPos;
				MapMng.m_hitMapObj->CalcHitPosition(&hitPos);
				s32 partIndex = pppMngSt - PartMng.m_pppMng;
				Game.HitParticleBG(partIndex, pppMngSt->m_kind, pppMngSt->m_nodeIndex, &hitPos, &pppMngSt->m_hitParams);
			}
			hadHit = 1;
		}
	}

	if (Game.m_currentSceneId != 7 && pppMngSt->m_hitParams.m_hitObjectCount < 0x10)
	{
		s32 partIndex = pppMngSt - PartMng.m_pppMng;

		for (CGObject* gObject = CFlat.FindGObjFirst(); gObject != 0;
			 gObject = CFlat.FindGObjNext(gObject))
		{
			int previousCount = pppMngSt->m_hitParams.m_hitObjectCount;
			int objectSlot;
			for (objectSlot = 0; objectSlot < previousCount; objectSlot++)
			{
				if (pppMngSt->m_hitObjectIds[objectSlot] == gObject->m_particleId)
				{
					break;
				}
			}

			if (objectSlot == previousCount)
			{
				for (s32 colliderIndex = 0; colliderIndex < 8; colliderIndex++)
				{
					CGObject::DamageCol* damageCol = &gObject->m_damageColliders[colliderIndex];

					if ((gObject->m_bgColMask & 0x80000) == 0 ||
						(damageCol->m_hitMask & pppMngSt->m_objHitMask) == 0)
					{
						continue;
					}

					if ((kPppPartZero == damageCol->m_horizontalRadius) &&
						(kPppPartZero == damageCol->m_verticalRadius))
					{
						continue;
					}

					Vec hitPos;
					if (Math.CrossCheckEllipseCapsule(
					        &hitPos, 0, origin, vector, radius, &damageCol->m_worldPosition,
					        damageCol->m_horizontalRadius, damageCol->m_verticalRadius) == 0)
					{
						continue;
					}

					hadHit = 1;

					if (Game.m_currentSceneId == 7)
					{
						Graphic._WaitDrawDone(const_cast<char*>(s_pppPart_cpp), 0xADB);
						_pppAllFreePObject(pppMngSt);
						Graphic._WaitDrawDone(const_cast<char*>(s_pppPart_cpp), 0xADD);
					}
					else
					{
						gObject->HitParticle(partIndex, pppMngSt->m_kind, pppMngSt->m_nodeIndex, colliderIndex, &hitPos,
											 &pppMngSt->m_hitParams);
						int newCount = pppMngSt->m_hitParams.m_hitObjectCount;
						if (previousCount != newCount)
						{
							previousCount = newCount;
							int updatedSlot;
							for (updatedSlot = 0; updatedSlot < newCount; updatedSlot++)
							{
								if (pppMngSt->m_hitObjectIds[updatedSlot] == gObject->m_particleId)
								{
									break;
								}
							}
							if (updatedSlot < newCount)
							{
								break;
							}
						}
					}
				}
			}
		}
	}

	return hadHit;
}

extern "C" const unsigned int gPppFixedWhite = 0xffffffff;
extern "C" const float kPppPartDepthScale = 5000.0f;
