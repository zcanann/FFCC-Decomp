#include "ffcc/pppPart.h"

#include "ffcc/map.h"
#include "ffcc/p_game.h"
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
#include "ffcc/pppShape.h"
#include "ffcc/symbols_shared.h"
#include "ffcc/gxfunc.h"

#include <string.h>

static int CrossCheckSphereVectorRaw(Vec* outPos, float* outT, Vec* origin, Vec* vector, Vec* ellipseScale,
                                     float scale, float innerRadius, float outerRadius)
{
    return Math.CrossCheckSphereVector(outPos, outT, origin, vector, ellipseScale, scale, innerRadius, outerRadius);
}

static const float kPppZero = 0.0; // FLOAT_8032fddc
static const float kPppOne = 1.0; // FLOAT_8032fdfc
static const double kScaleConstA = 4503601774854144.0; // DOUBLE_803304b0
static const float kScaleConstB = 0.017453292f; // FLOAT_803304a8
extern "C" unsigned char gPppBlendModeState;
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" float FLOAT_8032ed8c;
extern "C" double DOUBLE_8032fdf0;
extern "C" double DOUBLE_8032fe00;
extern "C" float FLOAT_8032fdf8;
extern "C" unsigned int DAT_8032fdd8;
extern "C" unsigned char DAT_8032ed84;
extern "C" unsigned char DAT_8032ed86;
extern "C" unsigned char DAT_8032ed87;
extern "C" unsigned char DAT_8032ed88;
extern "C" unsigned char DAT_8032ed89;
extern "C" unsigned char DAT_8032ed8a;
extern "C" unsigned char DAT_8032ed8b;
extern "C" int DAT_8032ed7c;
extern "C" unsigned int DAT_8032ed80;
extern "C" unsigned int IsEnable__13CAmemCacheSetFs(CAmemCacheSet*, short);
extern "C" int GetData__13CAmemCacheSetFsPci(CAmemCacheSet*, short, char*, int);
extern "C" void AddRef__13CAmemCacheSetFs(CAmemCacheSet*, short);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void __dl__FPv(void*);
extern "C" void* CreateStage__7CMemoryFUlPci(void*, unsigned long, const char*, int);
extern "C" void DestroyStage__7CMemoryFPQ27CMemory6CStage(void*, void*);
extern "C" unsigned short SetData__13CAmemCacheSetFPviQ210CAmemCache4TYPEi(CAmemCacheSet*, void*, int, CAmemCache::TYPE,
                                                                            int);
extern "C" void SetPart__9CLightPcsFQ29CLightPcs6TARGETPvUc(CLightPcs*, int, void*, unsigned char);
extern "C" void InitVtxFmt__12CMaterialManFi11_GXCompTypei11_GXCompTypei11_GXCompTypei(CMaterialMan*, int, _GXCompType, int, _GXCompType, int, _GXCompType, int);
extern "C" void CalcHitPosition__7CMapObjFP3Vec(void*, Vec*);
extern "C" CGObject* FindGObjFirst__13CFlatRuntime2Fv(void*);
extern "C" CGObject* FindGObjNext__13CFlatRuntime2FP8CGObject(void*, CGObject*);
extern "C" void _WaitDrawDone__8CGraphicFPci(CGraphic*, const char*, int);
extern "C" void CalcSafeNodeWorldMatrix__Q26CChara6CModelFPA4_fPQ26CChara5CNode(void*, float (*)[4], void*);

Mtx ppvCameraMatrix0;
Mtx ppvWorldMatrix;
Mtx ppvWorldMatrixWood;
_pppEnvSt* pppEnvStPtr;
_pppMngSt* pppMngStPtr;

struct PppMngStPartView {
    void* m_pppResSet;
    int m_partIndex;
    Vec m_position;
    int m_baseTime;
    pppIVECTOR4 m_rotation;
    int m_rotationSpeed;
    int m_lifeEnd;
    Vec m_scale;
    int m_currentFrame;
    int m_previousFrame;
    int m_numControlPrograms;
    float m_scaleFactor;
    float m_ownerScale;
    float m_userFloat0;
    float m_userFloat1;
    Vec m_savedPosition;
    Vec m_previousPosition;
    Vec m_paramVec0;
    short m_kind;
    short m_nodeIndex;
    pppFMATRIX m_matrix;
    unsigned char m_envColorR;
    unsigned char m_envColorG;
    unsigned char m_envColorB;
    unsigned char m_envColorA;
    int m_prioTime;
    int m_previousFrame2;
    int m_numPrograms;
    int m_reservedB8;
    unsigned int m_objHitMask;
    unsigned int m_cylinderAttribute;
    unsigned char m_pppPObjLinkHead[8];
    void* m_pDataValList;
    void* m_unknownD0;
    void* m_unknownD4;
    void* m_owner;
    void* m_lookTarget;
    CChara::CNode* m_bindNode;
    unsigned char m_endRequested;
    unsigned char m_stopRequested;
    unsigned char m_isFinished;
    unsigned char m_matrixMode;
    unsigned char m_hitBgFlag;
    unsigned char m_slotVisible;
    unsigned char m_ownerFacing;
    unsigned char m_drawVariant;
    unsigned char m_rotationOrder;
    unsigned char m_drawPass;
    signed char m_drawSubType;
    unsigned char m_useOwnerScaleSign;
    unsigned char m_ownerFlagsInitialized;
    unsigned char m_nodeScaleInitialized;
    unsigned char m_fieldF2;
    unsigned char m_padF3[2];
    unsigned char m_mapTexLoaded;
    unsigned char m_hasMapRef;
    unsigned char m_fpBillboard;
    unsigned char m_prio;
    short m_frameCounter;
    unsigned char m_padFB[3];
    unsigned int m_paramA;
    unsigned int m_paramB;
    float m_cullRadiusSq;
    float m_cullRadius;
    float m_cullYOffset;
    float m_sortDepth;
    unsigned short m_field118;
    short m_mapObjIndex;
    PPPSEST m_soundEffectData;
    PPPIFPARAM m_hitParams;
    short m_hitObjectIds[0x10];
};

static inline unsigned char* MaterialManRaw() { return reinterpret_cast<unsigned char*>(&MaterialMan); }
static inline unsigned char* PartPcsRaw() { return reinterpret_cast<unsigned char*>(&PartPcs); }

static const char s_pppPart_cpp[] = "pppPart.cpp";
static const char s_CPartPcs_heap_801D821C[] = "CPartPcs.heap";
static const float FLOAT_8032fddc = 0.0f;
extern "C" float FLOAT_8032fde0;
extern "C" float FLOAT_8032fde4;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
_pppMngSt* pppStopSe(_pppMngSt* pppMngSt, PPPSEST* pppSest)
{
	if (pppSest->m_soundEffectSlot >= 0 && pppSest->m_soundEffectHandle >= 0)
	{
		pppMngSt = Sound.FadeOutSe3D(pppSest->m_soundEffectHandle, pppSest->m_soundEffectFadeFrames);
		pppSest->m_soundEffectHandle = -1;
	}

	return pppMngSt;
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
 * Address:	TODO
 * Size:	TODO
 */
void pppNormalize(Vec& dest, Vec source)
{ 
	float zero = FLOAT_8032fddc;
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
 * Address:	TODO
 * Size:	TODO
 */
void pppCopyVector(Vec& dest, Vec source)
{ 
	float y = source.y;
	float x = source.x;
	dest.x = x;
	float z = source.z;
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
 * Address:	TODO
 * Size:	TODO
 */
float pppVectorLength(Vec vec)
{
	Vec zeroVec;

	zeroVec.x = kPppZero;
	zeroVec.y = kPppZero;
	zeroVec.z = kPppZero;

	return PSVECDistance(&vec, &zeroVec);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCreateHeap(_pppEnvSt* pppEnvSt, unsigned long param_2)
{ 
	pppEnvSt->m_stagePtr = static_cast<CMemory::CStage*>(CreateStage__7CMemoryFUlPci(&Memory, param_2, s_CPartPcs_heap_801D821C, 0));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDestroyHeap(_pppEnvSt* pppEnvSt)
{ 
	DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, pppEnvSt->m_stagePtr);
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
	struct pppSubProgEntryRaw
	{
		pppProg* m_prog;
		u32 m_initWork;
		u32 m_unk8;
		u32 m_unkC;
	};

	struct pppProgramSetDefRaw
	{
		pppProgramSetDefRaw* m_next;
		u32 m_unk4;
		u32 m_unk8;
		u32 m_startFrame;
		pppSubProgEntryRaw m_subProgEntries[1];
		u8 m_flags;
		u8 m_unk21;
		s16 m_sortKey;
		u16 m_objBaseSize;
		s16 m_numStages;
	};

	struct pppPDataValRaw
	{
		pppProgramSetDefRaw* m_programSetDef;
		s32 m_nextSpawnTime;
		_pppPObjLink* m_pppPObjLink;
		s16 m_activeCount;
		u8 m_index;
		u8 m_pad;
	};

	struct pppMngStRaw
	{
		u8 m_pad0[0x14];
		s32 m_baseTime;
		u8 m_pad1[0x74 - 0x18];
		s16 m_kind;
		u8 m_pad2[0xC4 - 0x76];
		_pppPObjLink m_pppPObjLinkHead;
		u8 m_pad3[0xF8 - 0xD0];
		u8 m_prio;
		s16 m_prioTime;
	};

	bool firstAllocFailure = true;
	bool canRetry = true;
	u8 denied[0x180];

	gPppBlendModeState = 0;
	do
	{
		_pppPObjLink* allocation = (_pppPObjLink*)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
			&Memory, allocSize, stage, file, line, 1);
		if (allocation != 0)
		{
			return allocation;
		}

		if (firstAllocFailure)
		{
			firstAllocFailure = false;
			memset(denied, 0, sizeof(denied));

			s32 currentIdx = ((s32)((u8*)pppMngStPtr - ((u8*)&PartMng + 0x1D4))) / 0x158;
			denied[currentIdx] = 1;
		}

		pppMngStRaw* selectedMngSt = 0;
		u8 selectedPrio = 1;
		s16 selectedPrioTime = 0;

		for (s32 i = 0; i < 0x180; i += 2)
		{
			pppMngStRaw* candidateA = (pppMngStRaw*)(((u8*)&PartMng + 0x1D4) + (i * 0x158));
			if (denied[i] == 0 && candidateA->m_baseTime != -0x1000 && candidateA->m_kind != 0)
			{
				u8 prioA = candidateA->m_prio;
				if (prioA > 1 && (selectedPrio < prioA || (selectedPrio == prioA && selectedPrioTime < candidateA->m_prioTime)))
				{
					selectedMngSt = candidateA;
					selectedPrio = prioA;
					selectedPrioTime = candidateA->m_prioTime;
				}
			}
			pppMngStRaw* candidateB = candidateA + 1;
			if (denied[i + 1] == 0 && candidateB->m_baseTime != -0x1000 && candidateB->m_kind != 0)
			{
				u8 prioB = candidateB->m_prio;
				if (prioB > 1 && (selectedPrio < prioB || (selectedPrio == prioB && selectedPrioTime < candidateB->m_prioTime)))
				{
					selectedMngSt = candidateB;
					selectedPrio = prioB;
					selectedPrioTime = candidateB->m_prioTime;
				}
			}
		}

		if (selectedMngSt == 0)
		{
			canRetry = false;
		}
		else
		{
			s32 deniedIdx = ((s32)((u8*)selectedMngSt - ((u8*)&PartMng + 0x1D4))) / 0x158;
			denied[deniedIdx] = 1;
			_pppPObjLink* prev = &selectedMngSt->m_pppPObjLinkHead;
			_pppPObjLink* obj = prev->m_next;
			while (obj != 0)
			{
				_pppPObjLink* next = obj->m_next;
				pppPDataValRaw* owner = (pppPDataValRaw*)obj->m_owner;
				if ((int)(((u32)owner->m_programSetDef->m_flags << 30) | ((u32)owner->m_programSetDef->m_flags >> 2)) >= 0)
				{
					prev->m_next = next;

					pppProgramSetDefRaw* ownerSet = owner->m_programSetDef;
					for (s32 stageIndex = 0; stageIndex < ownerSet->m_numStages; stageIndex++)
					{
						pppSubProgEntryRaw* entry = &ownerSet->m_subProgEntries[stageIndex];
						if (entry->m_prog != 0 && entry->m_prog->m_pppFunctionDestructor != 0)
						{
							((pppProgDestructCallback)entry->m_prog->m_pppFunctionDestructor)(obj, (_pppCtrlTable*)entry);
						}
					}

					owner->m_activeCount--;
					if (owner->m_activeCount == 0)
					{
						owner->m_pppPObjLink = 0;
					}
					else if (owner->m_pppPObjLink == obj)
					{
						owner->m_pppPObjLink = next;
					}

					Memory.Free(obj);
				}
				else
				{
					prev = obj;
				}
				obj = next;
			}
		}
	}
	while (canRetry);

	pppEnvStPtr->m_stagePtr->heapWalker(2, 0, 0xFFFFFFFF);
	PartMng.pppDumpMngSt();
	gPppBlendModeState = 1;
	return 0;
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
	struct pppSubProgEntryRaw
	{
		pppProg* m_prog;
		u32 m_initWork;
		u32 m_unk8;
		u32 m_unkC;
	};

	struct pppProgramSetDefRaw
	{
		pppProgramSetDefRaw* m_next;
		u32 m_unk4;
		u32 m_unk8;
		u32 m_startFrame;
		pppSubProgEntryRaw m_subProgEntries[1];
		u8 m_flags;
		u8 m_unk21;
		s16 m_sortKey;
		u16 m_objBaseSize;
		s16 m_numStages;
	};

	struct pppPDataValRaw
	{
		pppProgramSetDefRaw* m_programSetDef;
		s32 m_nextSpawnTime;
		_pppPObjLink* m_pppPObjLink;
		s16 m_activeCount;
		u8 m_index;
		u8 m_pad;
	};

	struct pppMngStRaw
	{
		u8 m_pad0[0x14];
		s32 m_baseTime;
		u8 m_pad1[0x74 - 0x18];
		s16 m_kind;
		u8 m_pad2[0xC4 - 0x76];
		_pppPObjLink m_pppPObjLinkHead;
		u8 m_pad3[0xF8 - 0xD0];
		u8 m_prio;
		s16 m_prioTime;
	};

	bool firstAllocFailure = true;
	bool canRetry = true;
	u8 denied[0x180];

	gPppBlendModeState = 0;
	do
	{
		_pppPObjLink* allocation = (_pppPObjLink*)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
			&Memory, allocSize, stage, file, line, 1);
		if (allocation != 0)
		{
			return allocation;
		}

		if (firstAllocFailure)
		{
			firstAllocFailure = false;
			memset(denied, 0, sizeof(denied));

			s32 currentIdx = ((s32)((u8*)pppMngStPtr - ((u8*)&PartMng + 0x1D4))) / 0x158;
			denied[currentIdx] = 1;
		}

		pppMngStRaw* selectedMngSt = 0;
		u8 selectedPrio = 1;
		s16 selectedPrioTime = 0;
		for (s32 i = 0; i < 0x180; i += 2)
		{
			pppMngStRaw* candidateA = (pppMngStRaw*)(((u8*)&PartMng + 0x1D4) + (i * 0x158));
			if (denied[i] == 0 && candidateA->m_baseTime != -0x1000 && candidateA->m_kind != 0)
			{
				u8 prioA = candidateA->m_prio;
				if (prioA > 1 && (selectedPrio < prioA || (selectedPrio == prioA && selectedPrioTime < candidateA->m_prioTime)))
				{
					selectedMngSt = candidateA;
					selectedPrio = prioA;
					selectedPrioTime = candidateA->m_prioTime;
				}
			}

			pppMngStRaw* candidateB = candidateA + 1;
			if (denied[i + 1] == 0 && candidateB->m_baseTime != -0x1000 && candidateB->m_kind != 0)
			{
				u8 prioB = candidateB->m_prio;
				if (prioB > 1 && (selectedPrio < prioB || (selectedPrio == prioB && selectedPrioTime < candidateB->m_prioTime)))
				{
					selectedMngSt = candidateB;
					selectedPrio = prioB;
					selectedPrioTime = candidateB->m_prioTime;
				}
			}
		}

		if (selectedMngSt == 0)
		{
			canRetry = false;
		}
		else
		{
			s32 deniedIdx = ((s32)((u8*)selectedMngSt - ((u8*)&PartMng + 0x1D4))) / 0x158;
			denied[deniedIdx] = 1;

			_pppPObjLink* prev = &selectedMngSt->m_pppPObjLinkHead;
			_pppPObjLink* obj = prev->m_next;
			while (obj != 0)
			{
				_pppPObjLink* next = obj->m_next;
				pppPDataValRaw* owner = (pppPDataValRaw*)obj->m_owner;
				if ((int)(((u32)owner->m_programSetDef->m_flags << 30) | ((u32)owner->m_programSetDef->m_flags >> 2)) >= 0)
				{
					prev->m_next = next;

					pppProgramSetDefRaw* ownerSet = owner->m_programSetDef;
					for (s32 stageIndex = 0; stageIndex < ownerSet->m_numStages; stageIndex++)
					{
						pppSubProgEntryRaw* entry = &ownerSet->m_subProgEntries[stageIndex];
						if (entry->m_prog != 0 && entry->m_prog->m_pppFunctionDestructor != 0)
						{
							((pppProgDestructCallback)entry->m_prog->m_pppFunctionDestructor)(obj, (_pppCtrlTable*)entry);
						}
					}

					owner->m_activeCount--;
					if (owner->m_activeCount == 0)
					{
						owner->m_pppPObjLink = 0;
					}
					else if (owner->m_pppPObjLink == obj)
					{
						owner->m_pppPObjLink = next;
					}

					Memory.Free(obj);
				}
				else
				{
					prev = obj;
				}
				obj = next;
			}
		}
	}
	while (canRetry);

	pppEnvStPtr->m_stagePtr->heapWalker(2, 0, 0xFFFFFFFF);
	PartMng.pppDumpMngSt();
	gPppBlendModeState = 1;
	return 0;
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
 * Address:	TODO
 * Size:	TODO
 */
void pppMngStHeapCheck(CMemory::CStage* stage)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 80056b0c
 * PAL Size: 360b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void callCon2Prog(_pppPObject* pObject)
{
	_pppPDataVal* owner = (_pppPDataVal*)*(_pppPObjLink**)(((u8*)pObject) + 8);
	_pppProgSetDef* progSet = owner->m_programSetDef;
	_pppCtrlTable* stage = progSet->m_stages;
	int stageIdx = 0;

	gPppInConstructor = 1;

	for (stageIdx = 0; stageIdx < progSet->m_numStages; stageIdx++)
	{
		pppProg* prog = stage->m_prog;
		if (prog != 0)
		{
			if (prog->m_pppFunctionConstructor3 != 0)
			{
				((pppProgConstruct3Callback)prog->m_pppFunctionConstructor3)(pObject, stage);
			}
			else
			{
				*(u32*)(((u8*)pObject) + progSet->m_workBaseOffset + stageIdx * 4) = stage->m_unk8;
				if (prog->m_pppFunctionConstructor2 != 0)
				{
					((pppProgConstruct2Callback)prog->m_pppFunctionConstructor2)(pObject);
				}
			}
		}
		stage++;
	}

	*(u32*)(((u8*)pObject) + 0x0C) = 0;
	while (true)
	{
		stage = progSet->m_stages;
		for (stageIdx = 0; stageIdx < progSet->m_numStages; stageIdx++)
		{
			u32 stageSlotOffset = progSet->m_workBaseOffset + stageIdx * 4;
			u32* stageSlot = *(u32**)(((u8*)pObject) + stageSlotOffset);
			pppProg* prog = stage->m_prog;
			u32* nextSlot = (u32*)(((u8*)stageSlot) + stage->m_workInfo.m_workOffset);

			if (*nextSlot == *(u32*)(((u8*)pObject) + 0x0C))
			{
				*(u32**)(((u8*)pObject) + stageSlotOffset) = nextSlot;
				if (prog != 0 && prog->m_pppFunctionOperation != 0 && prog->m_pppFunctionConstructor2 != 0)
				{
					((pppProgOperation2Callback)prog->m_pppFunctionOperation)(pObject, nextSlot);
				}
			}

			stage++;
		}

		*(u32*)(((u8*)pObject) + 0x0C) += 0x1000;
		if (*(u32*)(((u8*)pObject) + 0x0C) > progSet->m_endFrame)
		{
			break;
		}
	}

	gPppInConstructor = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void callConProg(_pppPObject*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
_pppPObject* pppCreatePObject(_pppMngSt* pppMngSt, _pppPDataVal* pppPDataVal)
{
	struct pppSubProgEntryRaw
	{
		pppProg* m_prog;
		u32 m_initWork;
		u32 m_unk8;
		u32 m_unkC;
	};

	struct pppProgramSetDefRaw
	{
		pppProgramSetDefRaw* m_next;
		u32 m_unk4;
		u32 m_unk8;
		u32 m_startFrame;
		pppSubProgEntryRaw m_subProgEntries[1];
		u8 m_flags;
		u8 m_unk21;
		s16 m_sortKey;
		u16 m_objBaseSize;
		s16 m_numStages;
	};

	struct pppPDataValRaw
	{
		pppProgramSetDefRaw* m_programSetDef;
		s32 m_nextSpawnTime;
		_pppPObjLink* m_pppPObjLink;
		s16 m_activeCount;
		u8 m_index;
		u8 m_pad;
	};

	struct pppMngStRaw
	{
		u8 m_pad0[0x14];
		s32 m_baseTime;
		u8 m_pad1[0x74 - 0x18];
		s16 m_kind;
		u8 m_pad2[0xC4 - 0x76];
		_pppPObjLink m_pppPObjLinkHead;
		u8 m_pad3[0xF8 - 0xD0];
		u8 m_prio;
		s16 m_prioTime;
	};

	pppPDataValRaw* dataVal = (pppPDataValRaw*)pppPDataVal;
	pppProgramSetDefRaw* programSet = dataVal->m_programSetDef;
	s16 numStages = programSet->m_numStages;
	u32 allocSize = programSet->m_objBaseSize + ((u32)numStages * sizeof(u32));
	CMemory::CStage* stage = pppEnvStPtr->m_stagePtr;
	_pppPObjLink* newObj = 0;
	bool firstFailure = true;
	u8 denied[0x180];
	pppMngStRaw* allMngSt = (pppMngStRaw*)(((u8*)&PartMng) + 0x1D4);

	gPppBlendModeState = 0;
	for (;;)
	{
		newObj = (_pppPObjLink*)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
			&Memory, allocSize, stage, (char*)"pppPart.cpp", 0x305, 1);
		if (newObj != 0)
		{
			break;
		}

		if (firstFailure)
		{
			firstFailure = false;
			memset(denied, 0, sizeof(denied));
			denied[(pppMngStRaw*)pppMngSt - allMngSt] = 1;
		}

		pppMngStRaw* selectedMngSt = 0;
		u8 selectedPrio = 1;
		s16 selectedPrioTime = 0;
		for (s32 i = 0; i < 0x180; i++)
		{
			pppMngStRaw* candidate = &allMngSt[i];
			if (denied[i] != 0 || candidate->m_baseTime == -0x1000 || candidate->m_kind == 0)
			{
				continue;
			}
			if (candidate->m_prio <= 1)
			{
				continue;
			}

			if (selectedPrio < candidate->m_prio ||
				(selectedPrio == candidate->m_prio && selectedPrioTime < candidate->m_prioTime))
			{
				selectedMngSt = candidate;
				selectedPrio = candidate->m_prio;
				selectedPrioTime = candidate->m_prioTime;
			}
		}

		if (selectedMngSt == 0)
		{
			pppEnvStPtr->m_stagePtr->heapWalker(2, 0, 0xFFFFFFFF);
			PartMng.pppDumpMngSt();
			gPppBlendModeState = 1;
			return 0;
		}

		denied[selectedMngSt - allMngSt] = 1;
		_pppPObjLink* prev = &selectedMngSt->m_pppPObjLinkHead;
		_pppPObjLink* obj = prev->m_next;
		while (obj != 0)
		{
			_pppPObjLink* next = obj->m_next;
			pppPDataValRaw* owner = (pppPDataValRaw*)obj->m_owner;
			if ((int)(((u32)owner->m_programSetDef->m_flags << 30) | ((u32)owner->m_programSetDef->m_flags >> 2)) >= 0)
			{
				prev->m_next = next;

				pppProgramSetDefRaw* ownerSet = owner->m_programSetDef;
				for (s32 stageIndex = 0; stageIndex < ownerSet->m_numStages; stageIndex++)
				{
					pppSubProgEntryRaw* entry = &ownerSet->m_subProgEntries[stageIndex];
					if (entry->m_prog != 0 && entry->m_prog->m_pppFunctionDestructor != 0)
					{
						((pppProgDestructCallback)entry->m_prog->m_pppFunctionDestructor)(obj, (_pppCtrlTable*)entry);
					}
				}

				owner->m_activeCount--;
				if (owner->m_activeCount == 0)
				{
					owner->m_pppPObjLink = 0;
				}
				else if (owner->m_pppPObjLink == obj)
				{
					owner->m_pppPObjLink = obj->m_next;
				}

				Memory.Free(obj);
			}
			else
			{
				prev = obj;
			}
			obj = next;
		}
	}

	((u8*)newObj)[0x0C] = 0;
	((u8*)newObj)[0x70] = 0;
	((u8*)newObj)[0x74] = 0;
	newObj->m_owner = pppPDataVal;
	((u8*)newObj)[0x7C] = 1;

	_pppPObjLink* objHead = (_pppPObjLink*)(((u8*)pppMngSt) + 0xC4);
	_pppPObjLink* firstObj = objHead->m_next;
	if (firstObj == 0)
	{
		dataVal->m_pppPObjLink = newObj;
		objHead->m_next = newObj;
		newObj->m_next = 0;
	}
	else if (dataVal->m_pppPObjLink == 0)
	{
		_pppPObjLink* prev = objHead;
		_pppPObjLink* iter = firstObj;
		while (iter != 0)
		{
			pppProgramSetDefRaw* iterSet = ((pppPDataValRaw*)iter->m_owner)->m_programSetDef;
			if (programSet->m_sortKey <= iterSet->m_sortKey)
			{
				dataVal->m_pppPObjLink = newObj;
				prev->m_next = newObj;
				newObj->m_next = iter;
				goto done_insert;
			}
			prev = iter;
			iter = iter->m_next;
		}
		dataVal->m_pppPObjLink = newObj;
		prev->m_next = newObj;
		newObj->m_next = 0;
	}
	else
	{
		newObj->m_next = dataVal->m_pppPObjLink->m_next;
		dataVal->m_pppPObjLink->m_next = newObj;
	}

done_insert:
	dataVal->m_activeCount++;
	u32* initWork = (u32*)(((u8*)newObj) + programSet->m_objBaseSize);
	for (s32 stageIndex = 0; stageIndex < programSet->m_numStages; stageIndex++)
	{
		pppSubProgEntryRaw* entry = &programSet->m_subProgEntries[stageIndex];
		*initWork++ = entry->m_initWork;
		if (entry->m_prog != 0 && entry->m_prog->m_pppFunctionConstructor != 0)
		{
			((pppProgConstructCallback)entry->m_prog->m_pppFunctionConstructor)(newObj, (_pppCtrlTable*)entry);
		}
	}

	return (_pppPObject*)newObj;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDeletePObject(_pppPObject*)
{
	// TODO
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
	struct pppSubProgEntryRaw
	{
		pppProg* m_prog;
		u32 m_initWork;
		u32 m_unk8;
		u32 m_unkC;
	};

	struct pppProgramSetDefRaw
	{
		pppProgramSetDefRaw* m_next;
		u32 m_unk4;
		u32 m_unk8;
		u32 m_startFrame;
		pppSubProgEntryRaw m_subProgEntries[1];
		u8 m_flags;
		u8 m_unk21;
		s16 m_sortKey;
		u16 m_objBaseSize;
		s16 m_numStages;
	};

	struct pppPDataValRaw
	{
		pppProgramSetDefRaw* m_programSetDef;
		s32 m_nextSpawnTime;
		_pppPObjLink* m_pppPObjLink;
		s16 m_activeCount;
		u8 m_index;
		u8 m_pad;
	};

	struct pppMngStFreeRaw
	{
		u32* m_pppResSet;
		s32 m_partIndex;
		u8 m_pad0[0x14 - 0x08];
		s32 m_baseTime;
		u8 m_pad1[0xC4 - 0x18];
		_pppPObjLink m_pppPObjLinkHead;
		pppPDataValRaw* m_pppPDataVals;
		u8 m_pad2[0xF5 - 0xCC];
		u8 m_mapTexLoaded;
		u8 m_hasMapRef;
		u8 m_pad3[0x11C - 0xF7];
		PPPSEST m_soundEffectData;
	};

	_WaitDrawDone__8CGraphicFPci(&Graphic, s_pppPart_cpp, 0x362);

	_pppMngSt* oldMngSt = pppMngStPtr;
	pppMngStPtr = pppMngSt;

	pppMngStFreeRaw* mngRaw = (pppMngStFreeRaw*)pppMngSt;
	if (mngRaw->m_soundEffectData.m_soundEffectSlot >= 0 &&
		mngRaw->m_soundEffectData.m_soundEffectHandle >= 0)
	{
		Sound.FadeOutSe3D(mngRaw->m_soundEffectData.m_soundEffectHandle,
			mngRaw->m_soundEffectData.m_soundEffectFadeFrames);
		mngRaw->m_soundEffectData.m_soundEffectHandle = -1;
	}

	for (_pppPObjLink* obj = mngRaw->m_pppPObjLinkHead.m_next; obj != 0;)
	{
		pppPDataValRaw* owner = (pppPDataValRaw*)obj->m_owner;
		_pppPObjLink* next = obj->m_next;
		pppProgramSetDefRaw* ownerSet = owner->m_programSetDef;
		for (s32 stageIndex = 0; stageIndex < ownerSet->m_numStages; stageIndex++)
		{
			pppSubProgEntryRaw* entry = &ownerSet->m_subProgEntries[stageIndex];
			if (entry->m_prog != 0 && entry->m_prog->m_pppFunctionDestructor != 0)
			{
				((pppProgDestructCallback)entry->m_prog->m_pppFunctionDestructor)(obj, (_pppCtrlTable*)entry);
			}
		}

		owner->m_activeCount--;
		if (owner->m_activeCount == 0)
		{
			owner->m_pppPObjLink = 0;
		}
		else if (owner->m_pppPObjLink == obj)
		{
			owner->m_pppPObjLink = next;
		}

		Memory.Free(obj);
		obj = next;
	}

	mngRaw->m_pppPObjLinkHead.m_next = 0;
	if (mngRaw->m_pppPDataVals != 0)
	{
		Memory.Free(mngRaw->m_pppPDataVals);
		mngRaw->m_pppPDataVals = 0;
	}

	DAT_8032ed7c = 0;
	mngRaw->m_baseTime = -0x1000;

	if (Game.m_currentSceneId != 7)
	{
		if (mngRaw->m_hasMapRef != 0)
		{
			u32 pppResSet = *mngRaw->m_pppResSet;
			s16* partResource = (s16*)(*(u32*)(pppResSet + 0x10) + mngRaw->m_partIndex * 8);

			s16 cacheIndex = *partResource;
			if (cacheIndex != -1)
			{
				ppvAmemCacheSet.Release(cacheIndex);
			}

			if (mngRaw->m_mapTexLoaded != 0)
			{
				u32 mapTexRef = *(u32*)(partResource + 2);
				s16* mapMeshIndices = (s16*)(mapTexRef + *(u32*)(mapTexRef + 0x10));
				s16* shapeIndices = (s16*)(mapTexRef + *(u32*)(mapTexRef + 0x14));

				s16 mapMeshCount = *mapMeshIndices;
				mapMeshIndices++;
				for (s16 i = 0; i < mapMeshCount; i++)
				{
					CMapMesh* mapMesh = *(CMapMesh**)(*(u32*)(pppResSet + 0x14) + mapMeshIndices[i] * 4);
					mapMesh->pppCacheDumpModelTexture(pppEnvStPtr->m_materialSetPtr, &ppvAmemCacheSet);
				}

				s16 shapeCount = *shapeIndices;
				shapeIndices++;
				for (s16 i = 0; i < shapeCount; i++)
				{
					pppShapeSt* shape = *(pppShapeSt**)(*(u32*)(pppResSet + 0x18) + shapeIndices[i] * 4);
					pppCacheDumpShapeTexture(shape, pppEnvStPtr->m_materialSetPtr);
				}
			}
		}

		mngRaw->m_mapTexLoaded = 0;
		mngRaw->m_hasMapRef = 0;
	}

	_WaitDrawDone__8CGraphicFPci(&Graphic, s_pppPart_cpp, 0x3A1);
	pppMngStPtr = oldMngSt;
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
	PppMngStPartView* pppMngStView = reinterpret_cast<PppMngStPartView*>(pppMngSt);
	// 1) Build local rotation matrix into pppMngStPtr->m_matrix
	switch (pppMngStView->m_rotationOrder) {
	case 0:
		pppGetRotMatrixXYZ(pppMngStPtr->m_matrix, &pppMngStView->m_rotation);
		break;
	case 1:
		pppGetRotMatrixXZY(pppMngStPtr->m_matrix, &pppMngStView->m_rotation);
		break;
	case 2:
		pppGetRotMatrixYXZ(pppMngStPtr->m_matrix, &pppMngStView->m_rotation);
		break;
	case 3:
		pppGetRotMatrixYZX(pppMngStPtr->m_matrix, &pppMngStView->m_rotation);
		break;
	case 4:
		pppGetRotMatrixZXY(pppMngStPtr->m_matrix, &pppMngStView->m_rotation);
		break;
	case 5:
		pppGetRotMatrixZYX(pppMngStPtr->m_matrix, &pppMngStView->m_rotation);
		break;
	default:
		break;
	}

	u8 mode = pppMngStView->m_matrixMode;

	Mtx nodeMtx;
	Vec tmpPos;
	bool attached = false;

	if (mode == 5)
	{
		if (!pppMngStView->m_bindNode)
		{
			goto LocalOnly;
		}

		{
			u8* ownerBytes = (u8*)pppMngStView->m_owner;
			if (!pppMngStView->m_ownerFacing) {
				u8 facing = ownerBytes[0x9A];
				pppMngStView->m_ownerFacing = (u8)(((u32)facing << 25) >> 31);
			}
			if (!pppMngStView->m_ownerFlagsInitialized) {
				u8 visible = 0;
				u32 flags = *(u32*)(ownerBytes + 0x60);
				if ((flags & 0x00000001) != 0 && (flags & 0x00400000) == 0) {
					visible = 1;
				}
				pppMngStView->m_slotVisible = visible;
			}
			if (!pppMngStView->m_nodeScaleInitialized) {
				bool useModelScale = false;
				int ownerData = *(int*)(ownerBytes + 0xF8);
				if (ownerData != 0 && *(int*)(ownerData + 0x168) != 0) {
					useModelScale = true;
				}
				float scale;
				if (useModelScale) {
					int modelPtr = *(int*)(ownerData + 0x168);
					scale = *(float*)(modelPtr + 0x9C);
				} else {
					scale = *(float*)(ownerBytes + 0x4B0);
				}
				pppMngStView->m_ownerScale = scale;
				if (kScaleConstA == (double)pppMngStView->m_ownerScale) {
					pppMngStView->m_useOwnerScaleSign = 1;
				} else if (DOUBLE_8032fe00 == (double)pppMngStView->m_ownerScale) {
					pppMngStView->m_useOwnerScaleSign = 0;
				} else {
					pppMngStView->m_useOwnerScaleSign = 1;
				}
			}
		}

		u8* ownerBytes = (u8*)pppMngStView->m_owner;
		CalcSafeNodeWorldMatrix__Q26CChara6CModelFPA4_fPQ26CChara5CNode(
			*(void**)(*(int*)(ownerBytes + 0xF8) + 0x168), nodeMtx, pppMngStView->m_bindNode);

		nodeMtx[0][3] += pppMngStPtr->m_position.x;
		nodeMtx[1][3] += pppMngStPtr->m_position.y;
		nodeMtx[2][3] += pppMngStPtr->m_position.z;

		PSMTXConcat(nodeMtx, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);
		attached = true;
	}
	else if (mode < 5)
	{
		if (mode == 3)
		{
			// Attach to character node (like 5) but slightly different flow
			if (!pppMngStView->m_bindNode) {
				goto LocalOnly;
			}

			{
				u8* ownerBytes = (u8*)pppMngStView->m_owner;
				if (!pppMngStView->m_ownerFacing) {
					u8 facing = ownerBytes[0x9A];
					pppMngStView->m_ownerFacing = (u8)(((u32)facing << 25) >> 31);
				}
				if (!pppMngStView->m_ownerFlagsInitialized) {
					u8 visible = 0;
					u32 flags = *(u32*)(ownerBytes + 0x60);
					if ((flags & 0x00000001) != 0 && (flags & 0x00400000) == 0) {
						visible = 1;
					}
					pppMngStView->m_slotVisible = visible;
				}
				if (!pppMngStView->m_nodeScaleInitialized) {
					bool useModelScale = false;
					int ownerData = *(int*)(ownerBytes + 0xF8);
					if (ownerData != 0 && *(int*)(ownerData + 0x168) != 0) {
						useModelScale = true;
					}
					float scale;
					if (useModelScale) {
						int modelPtr = *(int*)(ownerData + 0x168);
						scale = *(float*)(modelPtr + 0x9C);
					} else {
						scale = *(float*)(ownerBytes + 0x4B0);
					}
					pppMngStView->m_ownerScale = scale;
					if (kScaleConstA == (double)pppMngStView->m_ownerScale) {
						pppMngStView->m_useOwnerScaleSign = 1;
					} else if (DOUBLE_8032fe00 == (double)pppMngStView->m_ownerScale) {
						pppMngStView->m_useOwnerScaleSign = 0;
					} else {
						pppMngStView->m_useOwnerScaleSign = 1;
					}
				}
			}

			u8* ownerBytes = (u8*)pppMngStView->m_owner;
			CalcSafeNodeWorldMatrix__Q26CChara6CModelFPA4_fPQ26CChara5CNode(
				*(void**)(*(int*)(ownerBytes + 0xF8) + 0x168), nodeMtx, pppMngStView->m_bindNode);

			nodeMtx[0][3] += pppMngStPtr->m_position.x;
			nodeMtx[1][3] += pppMngStPtr->m_position.y;
			nodeMtx[2][3] += pppMngStPtr->m_position.z;

			PSMTXConcat(nodeMtx, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);
			attached = true;
		}
		else
		{
			// mode == 2 or 4 (map object world matrix)
			if (mode > 2)
			{
				// mode == 4
				// GetMapObjWMtx(&MapMng, pppMngSt->m_mapObjIndex, nodeMtx);
				MapMng.GetMapObjWMtx(pppMngStView->m_mapObjIndex, nodeMtx);

				nodeMtx[0][3] += pppMngStPtr->m_position.x;
				nodeMtx[1][3] += pppMngStPtr->m_position.y;
				nodeMtx[2][3] += pppMngStPtr->m_position.z;

				PSMTXConcat(nodeMtx, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);
				attached = true;
			}
			else
			{
				// mode == 2
				if (pppMngStView->m_mapObjIndex == -1)
				{
					goto LocalOnly;
				}

				// GetMapObjWMtx(&MapMng, pppMngSt->m_mapObjIndex, nodeMtx);
				MapMng.GetMapObjWMtx(pppMngStView->m_mapObjIndex, nodeMtx);

				nodeMtx[0][3] += pppMngStPtr->m_position.x;
				nodeMtx[1][3] += pppMngStPtr->m_position.y;
				nodeMtx[2][3] += pppMngStPtr->m_position.z;

				PSMTXConcat(nodeMtx, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);
				attached = true;
			}
		}
	}
	else {
		if (mode == 7)
		{
			if (!pppMngStView->m_bindNode)
			{
				goto LocalOnly;
			}

			{
				u8* ownerBytes = (u8*)pppMngStView->m_owner;
				if (!pppMngStView->m_ownerFacing) {
					u8 facing = ownerBytes[0x9A];
					pppMngStView->m_ownerFacing = (u8)(((u32)facing << 25) >> 31);
				}
				if (!pppMngStView->m_ownerFlagsInitialized) {
					u8 visible = 0;
					u32 flags = *(u32*)(ownerBytes + 0x60);
					if ((flags & 0x00000001) != 0 && (flags & 0x00400000) == 0) {
						visible = 1;
					}
					pppMngStView->m_slotVisible = visible;
				}
				if (!pppMngStView->m_nodeScaleInitialized) {
					bool useModelScale = false;
					int ownerData = *(int*)(ownerBytes + 0xF8);
					if (ownerData != 0 && *(int*)(ownerData + 0x168) != 0) {
						useModelScale = true;
					}
					float scale;
					if (useModelScale) {
						int modelPtr = *(int*)(ownerData + 0x168);
						scale = *(float*)(modelPtr + 0x9C);
					} else {
						scale = *(float*)(ownerBytes + 0x4B0);
					}
					pppMngStView->m_ownerScale = scale;
					if (kScaleConstA == (double)pppMngStView->m_ownerScale) {
						pppMngStView->m_useOwnerScaleSign = 1;
					} else if (DOUBLE_8032fe00 == (double)pppMngStView->m_ownerScale) {
						pppMngStView->m_useOwnerScaleSign = 0;
					} else {
						pppMngStView->m_useOwnerScaleSign = 1;
					}
				}
			}

			u8* ownerBytes = (u8*)pppMngStView->m_owner;
			CalcSafeNodeWorldMatrix__Q26CChara6CModelFPA4_fPQ26CChara5CNode(
				*(void**)(*(int*)(ownerBytes + 0xF8) + 0x168), nodeMtx, pppMngStView->m_bindNode);

			PSMTXMultVecSR(nodeMtx, &pppMngStPtr->m_position, &tmpPos);

			pppMngStPtr->m_matrix.value[0][3] = nodeMtx[0][3] + tmpPos.x;
			pppMngStPtr->m_matrix.value[1][3] = nodeMtx[1][3] + tmpPos.y;
			pppMngStPtr->m_matrix.value[2][3] = nodeMtx[2][3] + tmpPos.z;

			attached = true;
		}
		else
		{
			if (mode > 6 || !pppMngStView->m_bindNode)
			{
				goto LocalOnly;
			}

			{
				u8* ownerBytes = (u8*)pppMngStView->m_owner;
				if (!pppMngStView->m_ownerFacing) {
					u8 facing = ownerBytes[0x9A];
					pppMngStView->m_ownerFacing = (u8)(((u32)facing << 25) >> 31);
				}
				if (!pppMngStView->m_ownerFlagsInitialized) {
					u8 visible = 0;
					u32 flags = *(u32*)(ownerBytes + 0x60);
					if ((flags & 0x00000001) != 0 && (flags & 0x00400000) == 0) {
						visible = 1;
					}
					pppMngStView->m_slotVisible = visible;
				}
				if (!pppMngStView->m_nodeScaleInitialized) {
					bool useModelScale = false;
					int ownerData = *(int*)(ownerBytes + 0xF8);
					if (ownerData != 0 && *(int*)(ownerData + 0x168) != 0) {
						useModelScale = true;
					}
					float scale;
					if (useModelScale) {
						int modelPtr = *(int*)(ownerData + 0x168);
						scale = *(float*)(modelPtr + 0x9C);
					} else {
						scale = *(float*)(ownerBytes + 0x4B0);
					}
					pppMngStView->m_ownerScale = scale;
					if (kScaleConstA == (double)pppMngStView->m_ownerScale) {
						pppMngStView->m_useOwnerScaleSign = 1;
					} else if (DOUBLE_8032fe00 == (double)pppMngStView->m_ownerScale) {
						pppMngStView->m_useOwnerScaleSign = 0;
					} else {
						pppMngStView->m_useOwnerScaleSign = 1;
					}
				}
			}

			u8* ownerBytes = (u8*)pppMngStView->m_owner;
			CalcSafeNodeWorldMatrix__Q26CChara6CModelFPA4_fPQ26CChara5CNode(
				*(void**)(*(int*)(ownerBytes + 0xF8) + 0x168), nodeMtx, pppMngStView->m_bindNode);

			Vec col0;
			Vec col1;
			Vec col2;

			col0.x = nodeMtx[0][0];
			col0.y = nodeMtx[1][0];
			col0.z = nodeMtx[2][0];

			col1.x = nodeMtx[0][1];
			col1.y = nodeMtx[1][1];
			col1.z = nodeMtx[2][1];

			col2.x = nodeMtx[0][2];
			col2.y = nodeMtx[1][2];
			col2.z = nodeMtx[2][2];

			PSVECNormalize(&col0, &col0);
			PSVECNormalize(&col1, &col1);
			PSVECNormalize(&col2, &col2);

			nodeMtx[0][0] = col0.x; nodeMtx[1][0] = col0.y; nodeMtx[2][0] = col0.z;
			nodeMtx[0][1] = col1.x; nodeMtx[1][1] = col1.y; nodeMtx[2][1] = col1.z;
			nodeMtx[0][2] = col2.x; nodeMtx[1][2] = col2.y; nodeMtx[2][2] = col2.z;

			PSMTXMultVecSR(nodeMtx, &pppMngStPtr->m_position, &tmpPos);

			nodeMtx[0][3] += tmpPos.x;
			nodeMtx[1][3] += tmpPos.y;
			nodeMtx[2][3] += tmpPos.z;

			PSMTXConcat(nodeMtx, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);
			attached = true;
		}
	}

	if (!attached)
	{
	LocalOnly:
		Vec col;

		col.x = pppMngStPtr->m_matrix.value[0][0];
		col.y = pppMngStPtr->m_matrix.value[1][0];
		col.z = pppMngStPtr->m_matrix.value[2][0];
		PSVECScale(&col, &col, pppMngStView->m_scale.x);
		pppMngStPtr->m_matrix.value[0][0] = col.x;
		pppMngStPtr->m_matrix.value[1][0] = col.y;
		pppMngStPtr->m_matrix.value[2][0] = col.z;

		col.x = pppMngStPtr->m_matrix.value[0][1];
		col.y = pppMngStPtr->m_matrix.value[1][1];
		col.z = pppMngStPtr->m_matrix.value[2][1];
		PSVECScale(&col, &col, pppMngStView->m_scale.y);
		pppMngStPtr->m_matrix.value[0][1] = col.x;
		pppMngStPtr->m_matrix.value[1][1] = col.y;
		pppMngStPtr->m_matrix.value[2][1] = col.z;

		col.x = pppMngStPtr->m_matrix.value[0][2];
		col.y = pppMngStPtr->m_matrix.value[1][2];
		col.z = pppMngStPtr->m_matrix.value[2][2];
		PSVECScale(&col, &col, pppMngStView->m_scale.z);
		pppMngStPtr->m_matrix.value[0][2] = col.x;
		pppMngStPtr->m_matrix.value[1][2] = col.y;
		pppMngStPtr->m_matrix.value[2][2] = col.z;

		pppMngStPtr->m_matrix.value[0][3] = pppMngStView->m_position.x;
		pppMngStPtr->m_matrix.value[1][3] = pppMngStView->m_position.y;
		pppMngStPtr->m_matrix.value[2][3] = pppMngStView->m_position.z;
		return;
	}

	if (pppMngStView->m_scale.x != kPppOne)
	{
		Vec col;
		col.x = pppMngStPtr->m_matrix.value[0][0];
		col.y = pppMngStPtr->m_matrix.value[1][0];
		col.z = pppMngStPtr->m_matrix.value[2][0];
		PSVECScale(&col, &col, pppMngStView->m_scale.x);
		pppMngStPtr->m_matrix.value[0][0] = col.x;
		pppMngStPtr->m_matrix.value[1][0] = col.y;
		pppMngStPtr->m_matrix.value[2][0] = col.z;
	}

	if (pppMngStView->m_scale.y != kPppOne)
	{
		Vec col;
		col.x = pppMngStPtr->m_matrix.value[0][1];
		col.y = pppMngStPtr->m_matrix.value[1][1];
		col.z = pppMngStPtr->m_matrix.value[2][1];
		PSVECScale(&col, &col, pppMngStView->m_scale.y);
		pppMngStPtr->m_matrix.value[0][1] = col.x;
		pppMngStPtr->m_matrix.value[1][1] = col.y;
		pppMngStPtr->m_matrix.value[2][1] = col.z;
	}

	if (pppMngStView->m_scale.z != kPppOne)
	{
		Vec col;
		col.x = pppMngStPtr->m_matrix.value[0][2];
		col.y = pppMngStPtr->m_matrix.value[1][2];
		col.z = pppMngStPtr->m_matrix.value[2][2];
		PSVECScale(&col, &col, pppMngStView->m_scale.z);
		pppMngStPtr->m_matrix.value[0][2] = col.x;
		pppMngStPtr->m_matrix.value[1][2] = col.y;
		pppMngStPtr->m_matrix.value[2][2] = col.z;
	}
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
void pppSetFpMatrix(_pppMngSt* pppMngSt)
{
	PppMngStPartView* pppMngStView = reinterpret_cast<PppMngStPartView*>(pppMngSt);
	Vec local_a8;
	Vec local_9c;
	Vec local_90;
	Vec local_80;
	Vec local_70;
	Vec local_60;
	Vec local_50;
	Mtx local_44;

	PSMTXCopy(pppMngStPtr->m_matrix.value, local_44);
	if (pppMngStView->m_fpBillboard == 0) {
		PSMTXConcat(ppvCameraMatrix0, pppMngStPtr->m_matrix.value, ppvWorldMatrix);
		local_50.x = local_44[0][3];
		local_50.y = local_44[1][3];
		local_50.z = local_44[2][3];
		PSMTXMultVec(ppvCameraMatrix0, &local_50, &local_50);
	} else {
		PSMTXConcat(ppvCameraMatrix0, pppMngStPtr->m_matrix.value, ppvWorldMatrix);
		local_50.x = local_44[0][3];
		local_50.y = local_44[1][3];
		local_50.z = local_44[2][3];
		PSMTXMultVecSR(ppvCameraMatrix0, &local_50, &local_50);
		local_50.y += CameraPcs._228_4_;
	}

	local_70.x = ppvWorldMatrix[0][1];
	local_70.y = ppvWorldMatrix[1][1];
	local_90.x = ppvWorldMatrix[0][1];
	local_70.z = ppvWorldMatrix[2][1];
	local_90.y = ppvWorldMatrix[1][1];
	local_90.z = ppvWorldMatrix[2][1];
	ppvWorldMatrix[0][3] = local_50.x;
	ppvWorldMatrix[1][3] = local_50.y;
	ppvWorldMatrix[2][3] = local_50.z;

	if ((ppvWorldMatrix[0][1] != kPppZero) || (ppvWorldMatrix[1][1] != kPppZero) || (ppvWorldMatrix[2][1] != kPppZero)) {
		PSVECNormalize(&local_90, &local_70);
	}

	local_60.x = local_70.y;
	local_9c.y = -local_70.x;
	local_60.z = kPppZero;
	local_9c.x = local_70.y;
	ppvWorldMatrixWood[0][1] = local_70.x;
	ppvWorldMatrixWood[1][1] = local_70.y;
	ppvWorldMatrixWood[2][1] = local_70.z;
	local_9c.z = kPppZero;
	local_60.y = local_9c.y;

	if ((local_70.y != kPppZero) || (local_9c.y != kPppZero)) {
		PSVECNormalize(&local_9c, &local_60);
	}

	ppvWorldMatrixWood[0][0] = local_60.x;
	ppvWorldMatrixWood[1][0] = local_60.y;
	ppvWorldMatrixWood[2][0] = local_60.z;
	PSVECCrossProduct(&local_60, &local_70, &local_80);
	local_a8.x = local_80.x;
	local_a8.y = local_80.y;
	local_a8.z = local_80.z;

	if ((local_80.x != kPppZero) || (local_80.y != kPppZero) || (local_80.z != kPppZero)) {
		PSVECNormalize(&local_a8, &local_80);
	}

	ppvWorldMatrixWood[0][2] = local_80.x;
	ppvWorldMatrixWood[1][2] = local_80.y;
	ppvWorldMatrixWood[2][2] = local_80.z;
	ppvWorldMatrixWood[0][3] = ppvWorldMatrix[0][3];
	ppvWorldMatrixWood[1][3] = ppvWorldMatrix[1][3];
	ppvWorldMatrixWood[2][3] = ppvWorldMatrix[2][3];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCacheLoadModel(short* modelList, _pppDataHead*)
{
	short* modelIndices = modelList + 1;
	short modelCount = *modelList;
	u32 pppResSet = *reinterpret_cast<u32*>(pppMngStPtr->m_pppResSet);

	for (short i = 0; i < modelCount; i++)
	{
		CMapMesh* mapMesh = *(CMapMesh**)(*(u32*)(pppResSet + 0x14) + modelIndices[i] * 4);
		short cacheIndex = *reinterpret_cast<short*>(reinterpret_cast<u8*>(mapMesh) + 0x46);

		if (IsEnable__13CAmemCacheSetFs(&ppvAmemCacheSet, cacheIndex) == 0)
		{
			mapMesh->Ptr2Off();
			*reinterpret_cast<int*>(reinterpret_cast<u8*>(mapMesh) + 0x24) =
			    GetData__13CAmemCacheSetFsPci(&ppvAmemCacheSet, cacheIndex, (char*)s_pppPart_cpp, 0x4E5);
			mapMesh->Off2Ptr();
		}

		AddRef__13CAmemCacheSetFs(&ppvAmemCacheSet, cacheIndex);
		mapMesh->pppCacheLoadModelTexture(pppEnvStPtr->m_materialSetPtr, &ppvAmemCacheSet);
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
	short i = 0;
	short* shapeIndices = shapeList + 1;
	short shapeCount = *shapeList;
	CMaterialSet* materialSet =
	    *reinterpret_cast<CMaterialSet**>(reinterpret_cast<u8*>(&PartMng) + 0x7E4);

	while (i < shapeCount) {
		pppCacheLoadShapeTexture(*(pppShapeSt**)(pppDataHead->m_shapeNames + *shapeIndices * 4), materialSet);
		shapeIndices = shapeIndices + 1;
		i = i + 1;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCacheUnLoadModel(short*, _pppDataHead*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCacheUnLoadShape(short*, _pppDataHead*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCacheRefCnt0UpModel(short*, _pppDataHead*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCacheRefCnt0UpShape(short*, _pppDataHead*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCacheDumpModel(short*, _pppDataHead*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCacheDumpShape(short*, _pppDataHead*)
{
	// TODO
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
	struct pppProgramSetDefRaw
	{
		pppProgramSetDefRaw* m_next;
		int m_unk4;
		int m_unk8;
		int m_unkC;
		int m_startFrame;
	};

	struct pppPDataValRaw
	{
		pppProgramSetDefRaw* m_programSetDef;
		int m_nextSpawnTime;
		_pppPObjLink* m_objHead;
		short m_activeCount;
		unsigned char m_index;
		unsigned char m_pad;
	};

	struct pppMngStStartRaw
	{
		void* m_pppResSet;
		int m_partIndex;
		Vec m_position;
		int m_baseTime;
		pppIVECTOR4 m_rotation;
		int m_rotationSpeed;
		int m_lifeEnd;
		Vec m_scale;
		int m_currentFrame;
		int m_previousFrame;
		int m_numControlPrograms;
		float m_scaleFactor;
		float m_ownerScale;
		float m_userFloat0;
		float m_userFloat1;
		Vec m_savedPosition;
		Vec m_previousPosition;
		Vec m_paramVec0;
		short m_kind;
		short m_nodeIndex;
		pppFMATRIX m_matrix;
		unsigned char m_envColorR;
		unsigned char m_envColorG;
		unsigned char m_envColorB;
		unsigned char m_envColorA;
		int m_spawnedCount;
		int m_previousFrame2;
		int m_numPrograms;
		int m_reservedB8;
		unsigned int m_objHitMask;
		unsigned int m_cylinderAttribute;
		_pppPObjLink* m_objHead;
		pppProgramSetDefRaw* m_programSetHead;
		pppPDataValRaw* m_pDataVals;
		void** m_controlTable;
		void* m_programTable;
		void* m_owner;
		void* m_lookTarget;
		CChara::CNode* m_bindNode;
		unsigned char m_mode;
		unsigned char m_stopRequested;
		unsigned char m_isFinished;
		unsigned char m_matrixMode;
		unsigned char m_hitBgFlag;
		unsigned char m_slotVisible;
		unsigned char m_ownerFacing;
		unsigned char m_drawVariant;
		unsigned char m_rotationOrder;
		unsigned char m_drawPass;
		signed char m_drawSubType;
		unsigned char m_useOwnerScaleSign;
		unsigned char m_ownerFlagsInitialized;
		unsigned char m_nodeScaleInitialized;
		unsigned char m_fieldF2;
		unsigned char m_mapTexLoaded;
		unsigned char m_hasMapRef;
		unsigned char m_fpBillboard;
		unsigned char m_prio;
		short m_frameCounter;
	};

	pppMngStPtr = pppMngSt;
	pppMngStStartRaw* mng = (pppMngStStartRaw*)pppMngSt;

	mng->m_lifeEnd = (int)pdt[0];
	mng->m_mode = (unsigned char)pdt[1];

	short* modelList = (short*)((unsigned char*)pdt + pdt[4]);
	short* shapeList = (short*)((unsigned char*)pdt + pdt[5]);

	if (Game.m_currentSceneId != 7) {
		pppCacheLoadModel(modelList, (_pppDataHead*)pdt);
		pppCacheLoadShape(shapeList, (_pppDataHead*)pdt);
		mng->m_mapTexLoaded = 1;
	}
	mng->m_isFinished = 0;

	int controlOffset = (int)pdt[2];
	int programOffset = (int)pdt[3];
	int controlCount = *(int*)((unsigned char*)pdt + controlOffset);
	int programCount = *(int*)((unsigned char*)pdt + programOffset);
	pppProgramSetDefRaw* programSet = (pppProgramSetDefRaw*)(pdt + 6);

	mng->m_numControlPrograms = controlCount;
	mng->m_numPrograms = programCount;
	mng->m_controlTable = (void**)(((int*)((unsigned char*)pdt + controlOffset)) + 1);
	mng->m_programTable = (void*)(((int*)((unsigned char*)pdt + programOffset)) + 1);

	pppPDataValRaw* pDataVals = 0;
	if (programCount > 0) {
		pDataVals = (pppPDataValRaw*)pppMemAlloc(programCount * 0x10, pppEnvStPtr->m_stagePtr, (char*)"pppPart.cpp", 0x585);
	}
	mng->m_pDataVals = pDataVals;

	if (programSet->m_next != 0) {
		mng->m_programSetHead = 0;
	}

	mng->m_currentFrame = 0;
	if (programCount == 0) {
		mng->m_programSetHead = 0;
	} else {
		mng->m_programSetHead = programSet;
	}

	mng->m_objHead = 0;
	mng->m_spawnedCount = 0;

	if (pDataVals != 0) {
		unsigned char index = 0;
		pppProgramSetDefRaw* programSetIt = programSet;
		while (programSetIt != 0) {
			pDataVals->m_programSetDef = programSetIt;
			pDataVals->m_nextSpawnTime = programSetIt->m_startFrame;
			pDataVals->m_objHead = 0;
			pDataVals->m_activeCount = 0;
			pDataVals->m_index = index;
			pDataVals->m_pad = 0;
			programSetIt = programSetIt->m_next;
			index++;
			pDataVals++;
		}
	}

	if (runControlPrograms != 0) {
		int entryOffset = 0;
		unsigned char* controlTable = (unsigned char*)mng->m_controlTable;
		for (int i = 0; i < controlCount; i++) {
			unsigned char* controlEntry = *(unsigned char**)(controlTable + entryOffset);
			if (controlEntry != 0) {
				void (*fn)(_pppMngSt*) = *(void (**)(_pppMngSt*))(controlEntry + 0x10);
				if (fn != 0) {
					fn(pppMngSt);
				}
			}
			entryOffset += 4;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 800550ac
 * PAL Size: 604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppInitPdt(long* progOffsetReconstructionTable, pppProg* pppProg)
{
	int pppProgRelocCount = *(int*)((int)progOffsetReconstructionTable + progOffsetReconstructionTable[2]);
	int pdtRelocCount = *(int*)((int)progOffsetReconstructionTable + progOffsetReconstructionTable[3]);
	int* pppProgRelocs = (int*)((int)progOffsetReconstructionTable + progOffsetReconstructionTable[2]) + 1;
	int* pdtRelocs = (int*)((int)progOffsetReconstructionTable + progOffsetReconstructionTable[3]) + 1;
	int* table = (int*)(progOffsetReconstructionTable + 6);

	if (progOffsetReconstructionTable[6] == 0) {
		return;
	}

	int* entry = table;
	int* head = 0;
	do {
		head = entry;
		*head = (int)progOffsetReconstructionTable + *head;
		entry = head;

		for (int i = 0; i < *(short*)((int)head + 0x26); i++) {
			entry[10] = (int)(pppProg + entry[10]);
			entry[12] = (int)progOffsetReconstructionTable + entry[12];
			entry[13] = (int)progOffsetReconstructionTable + entry[13];
			entry += 4;
		}

		entry = (int*)*head;
	} while (*(int*)*head != 0);

	int processed = 0;
	*entry = 0;
	if (pppProgRelocCount > 0) {
		if (pppProgRelocCount > 8) {
			unsigned int blocks = (unsigned int)(pppProgRelocCount - 1) >> 3;
			int* reloc = pppProgRelocs;
			if (pppProgRelocCount - 8 > 0) {
				do {
					processed += 8;
					reloc[0] = (int)(pppProg + reloc[0]);
					reloc[1] = (int)(pppProg + reloc[1]);
					reloc[2] = (int)(pppProg + reloc[2]);
					reloc[3] = (int)(pppProg + reloc[3]);
					reloc[4] = (int)(pppProg + reloc[4]);
					reloc[5] = (int)(pppProg + reloc[5]);
					reloc[6] = (int)(pppProg + reloc[6]);
					reloc[7] = (int)(pppProg + reloc[7]);
					reloc += 8;
					blocks--;
				} while (blocks != 0);
			}
		}

		int remain = pppProgRelocCount - processed;
		int* reloc = pppProgRelocs + processed;
		if (processed < pppProgRelocCount) {
			do {
				*reloc = (int)(pppProg + *reloc);
				reloc++;
				remain--;
			} while (remain != 0);
		}
	}

	processed = 0;
	if (pdtRelocCount > 0) {
		if (pdtRelocCount > 8) {
			unsigned int blocks = (unsigned int)(pdtRelocCount - 1) >> 3;
			int* reloc = pdtRelocs;
			if (pdtRelocCount - 8 > 0) {
				do {
					processed += 8;
					reloc[0] += (int)progOffsetReconstructionTable;
					reloc[1] += (int)progOffsetReconstructionTable;
					reloc[2] += (int)progOffsetReconstructionTable;
					reloc[3] += (int)progOffsetReconstructionTable;
					reloc[4] += (int)progOffsetReconstructionTable;
					reloc[5] += (int)progOffsetReconstructionTable;
					reloc[6] += (int)progOffsetReconstructionTable;
					reloc[7] += (int)progOffsetReconstructionTable;
					reloc += 8;
					blocks--;
				} while (blocks != 0);
			}
		}

		int remain = pdtRelocCount - processed;
		int* reloc = pdtRelocs + processed;
		if (processed < pdtRelocCount) {
			do {
				*reloc += (int)progOffsetReconstructionTable;
				reloc++;
				remain--;
			} while (remain != 0);
		}
	}
}

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
	struct pppShapeGroupRaw
	{
		u16 m_groupId;
		u16 m_shapeCount;
		s16* m_shapeList;
	};

	u8* dataBase = reinterpret_cast<u8*>(&pppDataHead->m_version);

	pppDataHead->m_cacheChunks = pppDataHead->m_cacheChunks + reinterpret_cast<u32>(dataBase);
	pppDataHead->m_modelNames = pppDataHead->m_modelNames + reinterpret_cast<u32>(dataBase);
	pppDataHead->m_shapeNames = pppDataHead->m_shapeNames + reinterpret_cast<u32>(dataBase);
	pppDataHead->m_shapeGroups = pppDataHead->m_shapeGroups + reinterpret_cast<u32>(dataBase);

	int* chunkOffsets = reinterpret_cast<int*>(pppDataHead->m_cacheChunks);
	CMemory::CStage* stageLoad = *reinterpret_cast<CMemory::CStage**>(PartPcsRaw() + 0x1C);
	s16* cacheChunks = reinterpret_cast<s16*>(__nwa__FUlPQ27CMemory6CStagePci(
	                                          static_cast<u32>(pppDataHead->m_cacheChunkCount) << 3,
	                                          stageLoad, const_cast<char*>(s_pppPart_cpp), 0x620));
	pppDataHead->m_cacheChunks = reinterpret_cast<u32>(cacheChunks);

	for (int i = 0; i < pppDataHead->m_cacheChunkCount; i++) {
		int chunkOffset = chunkOffsets[0];
		int chunkSize = chunkOffsets[1] - chunkOffset;
		void* chunkData = __nwa__FUlPQ27CMemory6CStagePci(chunkSize, stageLoad, const_cast<char*>(s_pppPart_cpp), 0x626);

		memcpy(chunkData, dataBase + chunkOffset, chunkSize);
		cacheChunks[(i << 2)] = SetData__13CAmemCacheSetFPviQ210CAmemCache4TYPEi(
		    &ppvAmemCacheSet, chunkData, chunkSize, static_cast<CAmemCache::TYPE>(2), param_3);
		__dl__FPv(chunkData);
		chunkOffsets++;
	}

	char* modelName = reinterpret_cast<char*>(pppDataHead->m_modelNames);
	pppModelSt** modelRefs = reinterpret_cast<pppModelSt**>(__nwa__FUlPQ27CMemory6CStagePci(
	                                                        static_cast<u32>(pppDataHead->m_modelCount) << 2,
	                                                        stageLoad, const_cast<char*>(s_pppPart_cpp), 0x636));
	pppDataHead->m_modelNames = reinterpret_cast<u32>(modelRefs);

	pppModelSt* modelArray = *reinterpret_cast<pppModelSt**>(reinterpret_cast<u8*>(&PartMng) + 0x7EC);
	for (int i = 0; i < pppDataHead->m_modelCount; i++) {
		pppModelSt* model = 0;
		for (u32 j = 0; j < 0x100; j++) {
			if (modelArray[j].m_isUsed != 0 && strcmp(modelArray[j].m_name, modelName) == 0) {
				model = &modelArray[j];
				break;
			}
		}

		modelName += 0x20;
		modelRefs[i] = model;
		modelRefs[i]->m_refCount++;
	}

	char* shapeName = reinterpret_cast<char*>(pppDataHead->m_shapeNames);
	pppShapeSt** shapeRefs = reinterpret_cast<pppShapeSt**>(__nwa__FUlPQ27CMemory6CStagePci(
	                                                        static_cast<u32>(pppDataHead->m_shapeCount) << 2,
	                                                        stageLoad, const_cast<char*>(s_pppPart_cpp), 0x643));
	pppDataHead->m_shapeNames = reinterpret_cast<u32>(shapeRefs);

	pppShapeSt* shapeArray = *reinterpret_cast<pppShapeSt**>(reinterpret_cast<u8*>(&PartMng) + 0x7F0);
	for (int i = 0; i < pppDataHead->m_shapeCount; i++) {
		pppShapeSt* shape = 0;
		for (u32 j = 0; j < 0x100; j++) {
			if (shapeArray[j].m_inUse != 0 && strcmp(shapeArray[j].m_name, shapeName) == 0) {
				shape = &shapeArray[j];
				break;
			}
		}

		shapeName += 0x20;
		shapeRefs[i] = shape;
		shapeRefs[i]->m_refCount++;
	}

	pppShapeGroupRaw* shapeGroups = reinterpret_cast<pppShapeGroupRaw*>(pppDataHead->m_shapeGroups);
	pppShapeGroupRaw* shapeGroupRefs = reinterpret_cast<pppShapeGroupRaw*>(__nwa__FUlPQ27CMemory6CStagePci(
	                                                                       static_cast<u32>(pppDataHead->m_shapeGroupCount)
	                                                                           << 3,
	                                                                       stageLoad, const_cast<char*>(s_pppPart_cpp), 0x651));
	pppDataHead->m_shapeGroups = reinterpret_cast<u32>(shapeGroupRefs);

	for (int i = 0; i < pppDataHead->m_shapeGroupCount; i++) {
		shapeGroupRefs[i].m_groupId = shapeGroups[i].m_groupId;
		shapeGroupRefs[i].m_shapeCount = shapeGroups[i].m_shapeCount;
		shapeGroupRefs[i].m_shapeList = reinterpret_cast<s16*>(__nwa__FUlPQ27CMemory6CStagePci(
		    static_cast<int>(shapeGroups[i].m_shapeCount) << 1, stageLoad, const_cast<char*>(s_pppPart_cpp), 0x656));

		shapeGroups[i].m_shapeList = reinterpret_cast<s16*>(reinterpret_cast<u8*>(shapeGroups[i].m_shapeList) + reinterpret_cast<u32>(dataBase));
		memcpy(shapeGroupRefs[i].m_shapeList, shapeGroups[i].m_shapeList, static_cast<int>(shapeGroups[i].m_shapeCount) << 1);
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
	s32 pDataOffset = 0;
	for (s32 i = 0; i < *(s32*)(((u8*)pppMngSt) + 0xB8); i++)
	{
		u8* pDataVals = (u8*)(*(void**)(((u8*)pppMngSt) + 0xC8));
		_pppPDataVal* pDataVal = (_pppPDataVal*)(pDataVals + pDataOffset);

		if (pDataVals != 0 && pDataVal->m_programSetDef != 0)
		{
			_pppProgSetDef* progSet = pDataVal->m_programSetDef;
			u16 activeCount = pDataVal->m_activeCount;
			DAT_8032ed80 += activeCount;

			if (activeCount != 0)
			{
				s32 workOffsetStep = 0;
				_pppCtrlTable* stageIter = progSet->m_stages;

				for (s32 stage = 0; stage < progSet->m_numStages; stage++)
				{
					pppProg* prog = stageIter->m_prog;
					if (prog != 0)
					{
						pppProgOperationCallback fn = (pppProgOperationCallback)prog->m_pppFunctionOperation;
						if (fn != 0)
						{
							u16 count = activeCount;
							s32* obj = (s32*)pDataVal->m_pppPObjLink;

							while (count != 0)
							{
								s32 next = obj[0];
								if (*((u8*)obj + 0x7C) == 0)
								{
									fn((_pppPObject*)obj,
									   *(void**)(((u8*)obj) + progSet->m_workBaseOffset + workOffsetStep),
									   stageIter);
								}
								count--;
								obj = (s32*)next;
							}
						}
					}

					stageIter++;
					workOffsetStep += 4;
				}
			}
		}

		pDataOffset += 0x10;
	}

	s16* prioTime = (s16*)(((u8*)pppMngSt) + 0xF9);
	if (*prioTime != -1)
	{
		*prioTime = *prioTime + 1;
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
	s32 pDataOffset = 0;
	for (s32 i = 0; i < *(s32*)(((u8*)pppMngSt) + 0xB8); i++)
	{
		u8* pDataVals = (u8*)(*(void**)(((u8*)pppMngSt) + 0xC8));
		_pppPDataVal* pDataVal = (_pppPDataVal*)(pDataVals + pDataOffset);

		if (pDataVals != 0 && pDataVal->m_programSetDef != 0 && pDataVal->m_activeCount > 0)
		{
			s32 workOffsetStep = 0;
			_pppProgSetDef* progSet = pDataVal->m_programSetDef;
			_pppCtrlTable* stageIter = progSet->m_stages;

			for (s32 stage = 0; stage < progSet->m_numStages; stage++)
			{
				pppProg* prog = stageIter->m_prog;
				if (prog != 0)
				{
					pppProgRenderCallback fn = (pppProgRenderCallback)prog->m_pppFunctionRender;
					if (fn != 0)
					{
						u16 count = pDataVal->m_activeCount;
						s32* obj = (s32*)pDataVal->m_pppPObjLink;

						while (count != 0)
						{
							s32 next = obj[0];
							if (*((u8*)obj + 0x7C) == 0)
							{
								fn((_pppPObject*)obj,
								   *(void**)(((u8*)obj) + progSet->m_workBaseOffset + workOffsetStep),
								   stageIter);
							}
							count--;
							obj = (s32*)next;
						}

						Graphic.SetDrawDoneDebugDataPartControl(0x7FFF);
					}
				}

				stageIter++;
				workOffsetStep += 4;
			}
		}

		pDataOffset += 0x10;
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
void _pppDeadPart(_pppMngSt* pppMngSt)
{
	struct pppMngStDeadRaw
	{
		u8 m_pad0[0x24];
		s32 m_lifeEndFrame;
		u8 m_pad1[0x34 - 0x28];
		s32 m_currentFrame;
		u8 m_pad2[0xB0 - 0x38];
		s32 m_prevFrame;
		u8 m_pad3[0xC4 - 0xB4];
		_pppPObjLink m_objHead;
		u8 m_pad4[0xE4 - 0xD0];
		u8 m_hasLifeEnd;
		u8 m_loopMode;
		u8 m_isDead;
	};

	pppMngStDeadRaw* mng = (pppMngStDeadRaw*)pppMngSt;
	u32 maxDeleteFrame = 0;

	if (gPppCalcDisabled == 0)
	{
		_pppPObjLink* prev = &mng->m_objHead;
		for (_pppPObjLink* obj = prev->m_next; obj != 0;)
		{
			_pppPObjLink* next = obj->m_next;
			if (((u8*)obj)[0x7C] == 0)
			{
				_pppPDataVal* owner = (_pppPDataVal*)obj->m_owner;
				_pppProgSetDef* progSet = owner->m_programSetDef;
				int stageIdx = 0;

				*(u32*)(((u8*)obj) + 0x0C) += 0x1000;

				for (stageIdx = 0; stageIdx < progSet->m_numStages; stageIdx++)
				{
					_pppCtrlTable* stage = &progSet->m_stages[stageIdx];
					u32 stageSlotOffset = progSet->m_workBaseOffset + stageIdx * 4;
					u32* stageSlot = *(u32**)(((u8*)obj) + stageSlotOffset);
					u32* nextSlot = (u32*)(((u8*)stageSlot) + stage->m_workInfo.m_workOffset);
					if (*nextSlot == *(u32*)(((u8*)obj) + 0x0C))
					{
						*(u32**)(((u8*)obj) + stageSlotOffset) = nextSlot;
					}
				}

				if (mng->m_loopMode != 0 &&
					*(u32*)(((u8*)obj) + 0x0C) >= progSet->m_loopFrame &&
					(progSet->m_loopFrame & 0xF0000000) != 0x70000000)
				{
					*(u32*)(((u8*)obj) + 0x0C) = progSet->m_endFrame;
					callCon2Prog((_pppPObject*)obj);
				}
				else
				{
					maxDeleteFrame |= progSet->m_endFrame;
					if (*(u32*)(((u8*)obj) + 0x0C) >= progSet->m_endFrame)
					{
						prev->m_next = next;

						for (stageIdx = 0; stageIdx < progSet->m_numStages; stageIdx++)
						{
							_pppCtrlTable* stage = &progSet->m_stages[stageIdx];
							pppProg* prog = stage->m_prog;
							if (prog != 0 && prog->m_pppFunctionDestructor != 0)
							{
								((pppProgDestructCallback)prog->m_pppFunctionDestructor)(obj, stage);
							}
						}

						owner->m_activeCount--;
						if (owner->m_activeCount == 0)
						{
							owner->m_pppPObjLink = 0;
						}
						else if (owner->m_pppPObjLink == obj)
						{
							owner->m_pppPObjLink = next;
						}

						Memory.Free(obj);
					}
					else
					{
						prev = obj;
					}
				}
			}
			else
			{
				prev = obj;
			}

			obj = next;
		}

		if (mng->m_loopMode != 0 && maxDeleteFrame == 0x70000000)
		{
			for (_pppPObjLink* obj = mng->m_objHead.m_next; obj != 0;)
			{
				_pppPObjLink* next = obj->m_next;
				_pppPDataVal* owner = (_pppPDataVal*)obj->m_owner;
				_pppProgSetDef* progSet = owner->m_programSetDef;

				for (int stageIdx = 0; stageIdx < progSet->m_numStages; stageIdx++)
				{
					_pppCtrlTable* stage = &progSet->m_stages[stageIdx];
					pppProg* prog = stage->m_prog;
					if (prog != 0 && prog->m_pppFunctionDestructor != 0)
					{
						((pppProgDestructCallback)prog->m_pppFunctionDestructor)(obj, stage);
					}
				}

				owner->m_activeCount--;
				if (owner->m_activeCount == 0)
				{
					owner->m_pppPObjLink = 0;
				}
				else if (owner->m_pppPObjLink == obj)
				{
					owner->m_pppPObjLink = next;
				}

				Memory.Free(obj);
				obj = next;
			}

			mng->m_objHead.m_next = 0;
		}
	}

	if (gPppCalcDisabled == 0)
	{
		mng->m_prevFrame = mng->m_currentFrame;
		mng->m_currentFrame += 0x1000;
	}

	if (mng->m_hasLifeEnd != 0)
	{
		if (mng->m_loopMode != 0)
		{
			mng->m_isDead = (mng->m_objHead.m_next == 0) ? 1 : 0;
		}
		else if (mng->m_currentFrame >= 0x70000000)
		{
			mng->m_prevFrame = 0x6FFFF000;
			mng->m_currentFrame = 0x70000000;
		}
	}
	else
	{
		mng->m_isDead = (mng->m_currentFrame >= mng->m_lifeEndFrame) ? 1 : 0;
	}
}

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
	struct pppMngStInitRaw
	{
		u8 m_pad0[0xC4];
		_pppPObjLink m_pppPObjLinkHead;
	};

	if (gPppCalcDisabled != 0)
	{
		return;
	}

	for (_pppPObjLink* obj = ((pppMngStInitRaw*)pppMngSt)->m_pppPObjLinkHead.m_next; obj != 0; obj = obj->m_next)
	{
		((u8*)obj)[0x7C] = 0;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void apeaPObject(_pppMngSt*)
{
	// TODO
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
	struct pppPDataValRaw
	{
		void* m_programSetDef;
		s32 m_nextSpawnTime;
		_pppPObjLink* m_pppPObjLink;
		s16 m_activeCount;
		u8 m_index;
		u8 m_pad;
	};

	struct pppMngStCalcRaw
	{
		u8 m_pad0[0x34];
		s32 m_currentFrame;
		u8 m_pad1[0xB8 - 0x38];
		s32 m_numPrograms;
		u8 m_pad2[0xC8 - 0xBC];
		pppPDataValRaw* m_pppPDataVals;
		u8 m_pad3[0x11C - 0xCC];
		PPPSEST m_soundEffectData;
	};

	pppMngStCalcRaw* mngRaw = (pppMngStCalcRaw*)pppMngSt;
	PPPSEST* se = &mngRaw->m_soundEffectData;
	pppFMATRIX* mtx = (pppFMATRIX*)(((u8*)pppMngSt) + 0x78);

	pppMngStPtr = pppMngSt;
	if (se->m_soundEffectSlot >= 0 &&
		se->m_soundEffectStartFrame <= mngRaw->m_currentFrame &&
		se->m_soundEffectStopFlag == 0)
	{
		Vec soundPos;
		soundPos.x = mtx->value[0][3];
		soundPos.y = mtx->value[1][3];
		soundPos.z = mtx->value[2][3];

		if (se->m_soundEffectHandle < 0)
		{
			if (se->m_soundEffectStartedOnce == 0)
			{
				u32 soundTableIndex = (u32)se->m_soundEffectKind - 3;
				se->m_soundEffectHandle = Sound.PlaySe3D(
					se->m_soundEffectSlot, &soundPos,
					pppEnvStPtr->m_soundVolumeTable[soundTableIndex],
					pppEnvStPtr->m_soundPitchTable[soundTableIndex], 0);
				se->m_soundEffectStartedOnce = 1;
			}
		}
		else
		{
			Sound.ChangeSe3DPos(se->m_soundEffectHandle, &soundPos);
		}
	}

	s32 pDataValOffset = 0;
	for (s32 i = 0; i < mngRaw->m_numPrograms; i++)
	{
		pppPDataValRaw* pDataVal = (pppPDataValRaw*)(((u8*)mngRaw->m_pppPDataVals) + pDataValOffset);
		if (mngRaw->m_pppPDataVals != 0 && pDataVal != 0 && pDataVal->m_nextSpawnTime <= mngRaw->m_currentFrame)
		{
			pDataVal->m_nextSpawnTime = 0x7FFFFFFF;
			_pppPObject* pObject = pppCreatePObject(pppMngSt, (_pppPDataVal*)pDataVal);
			if (pObject == 0)
			{
				break;
			}
			((u8*)pObject)[0x7C] = 0;
		}
		pDataValOffset += 0x10;
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
	pppMngStPtr = pppMngSt;
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
	*(u32*)(MaterialManRaw() + 0x128) = *(u32*)(MaterialManRaw() + 0x11C);
	*(u32*)(MaterialManRaw() + 0x12C) = *(u32*)(MaterialManRaw() + 0x120);
	*(u32*)(MaterialManRaw() + 0x130) = *(u32*)(MaterialManRaw() + 0x124);
	*(u32*)(MaterialManRaw() + 0x40) = *(u32*)(MaterialManRaw() + 0x48);

	if (positions == 0)
	{
		GXSetArray((GXAttr)9, *(void**)((u8*)model + 0x2C), 0xC);
	}
	else
	{
		GXSetArray((GXAttr)9, positions, 0xC);
	}

	GXSetArray((GXAttr)0xB, *(void**)((u8*)model + 0x3C), 4);
	GXSetArray((GXAttr)0xD, *(void**)((u8*)model + 0x38), 4);
	GXSetArray((GXAttr)0xE, *(void**)((u8*)model + 0x38), 4);
	*(void**)(MaterialManRaw() + 4) = *(void**)((u8*)model + 0x30);

	if (usePartMaterial == 0)
	{
		GXSetArray((GXAttr)10, *(void**)(MaterialManRaw() + 4), 6);
	}

	model->DrawPart(pppEnvStPtr->m_materialSetPtr, usePartMaterial);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppInitBlendMode()
{
	gPppBlendModeState = 0xFF;
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
	if ((blendMode != 0xFF) && (gPppBlendModeState != blendMode))
	{
		gPppBlendModeState = blendMode;
		if (blendMode == 2)
		{
			_GXSetBlendMode((_GXBlendMode)3, (_GXBlendFactor)4, (_GXBlendFactor)1, (_GXLogicOp)5);
			_GXSetAlphaCompare((_GXCompare)7, 0, (_GXAlphaOp)0, (_GXCompare)7, 0xFF);
			GXSetZCompLoc((GXBool)1);
		}
		else if (blendMode < 2)
		{
			if (blendMode == 0)
			{
				_GXSetBlendMode((_GXBlendMode)1, (_GXBlendFactor)4, (_GXBlendFactor)5, (_GXLogicOp)5);
				_GXSetAlphaCompare((_GXCompare)7, 0, (_GXAlphaOp)0, (_GXCompare)7, 0xFF);
				GXSetZCompLoc((GXBool)1);
			}
			else
			{
				_GXSetBlendMode((_GXBlendMode)1, (_GXBlendFactor)4, (_GXBlendFactor)1, (_GXLogicOp)5);
				_GXSetAlphaCompare((_GXCompare)7, 0, (_GXAlphaOp)0, (_GXCompare)7, 0xFF);
				GXSetZCompLoc((GXBool)1);
			}
		}
		else if (blendMode < 4)
		{
			_GXSetBlendMode((_GXBlendMode)0, (_GXBlendFactor)6, (_GXBlendFactor)5, (_GXLogicOp)5);
			_GXSetAlphaCompare((_GXCompare)7, 0, (_GXAlphaOp)0, (_GXCompare)7, 0xFF);
			GXSetZCompLoc((GXBool)1);
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
	if (kPppZero != FLOAT_8032ed8c) {
		FLOAT_8032ed8c = kPppZero;
		ppvScreenMatrix[2][3] = gPartScreenMatrixRow2W;
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
	double depthOffset = (double)depth;
	if (DOUBLE_8032fdf0 != depthOffset) {
		float sortDepth = *(float*)((u8*)pppMngStPtr + 0x114);
		depthOffset = (double)((float)(depthOffset * (double)FLOAT_8032fdf8) / -sortDepth);
	}

	if ((double)FLOAT_8032ed8c != depthOffset) {
		FLOAT_8032ed8c = (float)depthOffset;
		ppvScreenMatrix[2][3] = gPartScreenMatrixRow2W + (float)depthOffset;
		GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);
	}

	*(u32*)(MaterialManRaw() + 0x48) = 0x000ACE0F;
	*(u32*)(MaterialManRaw() + 0x44) = 0xFFFFFFFF;
	*(u8*)(MaterialManRaw() + 0x4C) = 0xFF;
	*(u32*)(MaterialManRaw() + 0x11C) = 0;
	*(u32*)(MaterialManRaw() + 0x120) = 0x1E;
	*(u32*)(MaterialManRaw() + 0x124) = 0;
	*(u8*)(MaterialManRaw() + 0x205) = 0xFF;
	*(u8*)(MaterialManRaw() + 0x206) = 0xFF;
	*(u32*)(MaterialManRaw() + 0x58) = 0;
	*(u32*)(MaterialManRaw() + 0x5C) = 0;
	*(u8*)(MaterialManRaw() + 0x208) = 0;
	*(u32*)(MaterialManRaw() + 0x128) = 0;
	*(u32*)(MaterialManRaw() + 0x12C) = 0x1E;
	*(u32*)(MaterialManRaw() + 0x130) = 0;
	*(u32*)(MaterialManRaw() + 0x40) = 0x000ACE0F;

	if (DAT_8032ed84 != lightTarget) {
		DAT_8032ed84 = lightTarget;
		SetPart__9CLightPcsFQ29CLightPcs6TARGETPvUc(&LightPcs, 2, pppMngStPtr, lightTarget);
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
			nrmMtx[0][3] = kPppZero;
			nrmMtx[1][3] = kPppZero;
			nrmMtx[2][3] = kPppZero;
			GXLoadNrmMtxImm(nrmMtx, GX_PNMTX0);
		}
	}

	_GXColor fixedColor;
	*(u32*)&fixedColor = DAT_8032fdd8;
	if (lightTarget < 2) {
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

	if ((DAT_8032ed86 != fogIndex) || (DAT_8032ed87 != fogParam)) {
		DAT_8032ed86 = fogIndex;
		DAT_8032ed87 = fogParam;
		Graphic.SetFog((int)fogIndex, fogParam != 0);
	}

	if (DAT_8032ed88 != cullMode) {
		DAT_8032ed88 = cullMode;
		GXSetCullMode((GXCullMode)cullMode);
	}

	if ((DAT_8032ed89 != zEnable) || (DAT_8032ed8b != zWrite)) {
		DAT_8032ed8b = zWrite;
		DAT_8032ed89 = zEnable;
		GXSetZMode((GXBool)zEnable, GX_LEQUAL, (GXBool)zWrite);
	}

	if (DAT_8032ed8a != colorUpdate) {
		DAT_8032ed8a = colorUpdate;
		GXSetColorUpdate((GXBool)colorUpdate);
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
	InitVtxFmt__12CMaterialManFi11_GXCompTypei11_GXCompTypei11_GXCompTypei(
		&MaterialMan,
		-1,
		(_GXCompType)4,
		0,
		(_GXCompType)3,
		0xE,
		(_GXCompType)3,
		10
	);

	DAT_8032ed84 = 0xFF;
	gPppBlendModeState = 0xFF;
	DAT_8032ed86 = 0xFF;
	DAT_8032ed88 = 0xFF;
	DAT_8032ed89 = 0xFF;
	DAT_8032ed8a = 0xFF;
	DAT_8032ed8b = 0xFF;

	FLOAT_8032ed8c = kPppOne;
	if (useZeroDepth != 0)
	{
		FLOAT_8032ed8c = kPppZero;
	}

	LightPcs.SetNumDiffuse(0);
}

/*
 * --INFO--
 * PAL Address: 0x80053d04
 * PAL Size: 876b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppHitCylinderSendSystem(_pppMngSt* pppMngSt, Vec* origin, Vec* vector, float radius, float cylScale)
{
	struct PppMngStHitRaw
	{
		u8 m_pad0[0x74];
		s16 m_kind;
		s16 m_nodeIndex;
		u8 m_pad1[0xBC - 0x78];
		u32 m_objHitMask;
		u32 m_cylinderAttribute;
		u8 m_pad2[0xE5 - 0xC4];
		u8 m_endRequested;
		u8 m_pad3[0x11C - 0xE6];
		PPPSEST m_soundEffectData;
		PPPIFPARAM m_hitParams;
		s16 m_hitObjectIds[0x10];
	};

	struct CMapCylinderRaw
	{
		Vec m_bottom;
		Vec m_direction;
		float m_radius;
		float m_height;
		Vec m_top;
		Vec m_direction2;
		float m_radius2;
		float m_height2;
	};

	PppMngStHitRaw* hitRaw = (PppMngStHitRaw*)pppMngSt;
	bool hadHit = false;

	if (FLOAT_8032fddc != cylScale)
	{
		CMapCylinderRaw cylinder;
		cylinder.m_bottom = *origin;
		cylinder.m_direction.x = FLOAT_8032fde0;
		cylinder.m_direction.y = FLOAT_8032fde0;
		cylinder.m_direction.z = FLOAT_8032fde0;
		cylinder.m_radius = radius;
		cylinder.m_height = FLOAT_8032fde0;
		cylinder.m_top = *vector;
		cylinder.m_direction2.x = FLOAT_8032fde4;
		cylinder.m_direction2.y = FLOAT_8032fde4;
		cylinder.m_direction2.z = FLOAT_8032fde4;
		cylinder.m_radius2 = cylScale;
		cylinder.m_height2 = FLOAT_8032fde0;

		if (MapMng.CheckHitCylinder((CMapCylinder*)&cylinder, vector, hitRaw->m_cylinderAttribute) != 0)
		{
			if (Game.m_currentSceneId == 7)
			{
				hitRaw->m_endRequested = 1;
				if ((hitRaw->m_soundEffectData.m_soundEffectSlot >= 0) &&
					(hitRaw->m_soundEffectData.m_soundEffectHandle >= 0))
				{
					Sound.FadeOutSe3D(hitRaw->m_soundEffectData.m_soundEffectHandle,
						hitRaw->m_soundEffectData.m_soundEffectFadeFrames);
					hitRaw->m_soundEffectData.m_soundEffectHandle = -1;
				}
			}
			else
			{
				Vec hitPos;
				CalcHitPosition__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A88), &hitPos);
				s32 partIndex = ((s32)((u8*)pppMngSt - ((u8*)&PartMng + 0x2A18))) / 0x158;
				Game.HitParticleBG(partIndex, hitRaw->m_kind, hitRaw->m_nodeIndex, &hitPos, &hitRaw->m_hitParams);
			}
			hadHit = true;
		}
	}

	if (Game.m_currentSceneId != 7 && hitRaw->m_hitParams.m_hitObjectCount < 0x10)
	{
		s32 partIndex = ((s32)((u8*)pppMngSt - ((u8*)&PartMng + 0x2A18))) / 0x158;

		for (CGObject* gObject = FindGObjFirst__13CFlatRuntime2Fv(&CFlat); gObject != 0;
			 gObject = FindGObjNext__13CFlatRuntime2FP8CGObject(&CFlat, gObject))
		{
			u8 previousCount = hitRaw->m_hitParams.m_hitObjectCount;
			u8 objectSlot = 0;
			while ((objectSlot < previousCount) &&
				   (hitRaw->m_hitObjectIds[objectSlot] != gObject->m_particleId))
			{
				objectSlot++;
			}

			if (objectSlot == previousCount)
			{
				for (s32 colliderIndex = 0; colliderIndex < 8; colliderIndex++)
				{
					CGObject::DamageCol* damageCol = &gObject->m_damageColliders[colliderIndex];

					if ((gObject->m_bgColMask & 0x80000) == 0 ||
						(damageCol->m_hitMask & hitRaw->m_objHitMask) == 0)
					{
						continue;
					}

					if ((FLOAT_8032fddc == damageCol->m_innerRadius) &&
						(FLOAT_8032fddc == damageCol->m_outerRadius))
					{
						continue;
					}

					Vec hitPos;
					if (CrossCheckSphereVectorRaw(&hitPos, 0, origin, vector, (Vec*)&damageCol->m_worldPosition.y,
												radius, damageCol->m_innerRadius, damageCol->m_outerRadius) == 0)
					{
						continue;
					}

					hadHit = true;

					if (Game.m_currentSceneId == 7)
					{
						_WaitDrawDone__8CGraphicFPci(&Graphic, s_pppPart_cpp, 0xADB);
						_pppAllFreePObject(pppMngSt);
						_WaitDrawDone__8CGraphicFPci(&Graphic, s_pppPart_cpp, 0xADD);
					}
					else
					{
						gObject->HitParticle(partIndex, hitRaw->m_kind, hitRaw->m_nodeIndex, colliderIndex, &hitPos,
											 &hitRaw->m_hitParams);
						u8 newCount = hitRaw->m_hitParams.m_hitObjectCount;
						if (previousCount != newCount)
						{
							u8 updatedSlot = 0;
							while ((updatedSlot < newCount) &&
								   (hitRaw->m_hitObjectIds[updatedSlot] != gObject->m_particleId))
							{
								updatedSlot++;
							}
							previousCount = newCount;
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

	if (hadHit)
	{
		return;
	}
}
