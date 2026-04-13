#include "ffcc/pppChangeTex.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/symbols_shared.h"
#include "ffcc/util.h"
#include "dolphin/gx.h"
#include <string.h>
#include <dolphin/os/OSCache.h>

struct _pppMngStChangeTex {
	char _pad0[0xd8];
	void* m_charaObj;
};

struct _pppEnvStChangeTex {
	void* m_stagePtr;
	CMaterialSet* m_materialSetPtr;
	CMapMesh** m_mapMeshPtr;
};
extern _pppMngStChangeTex* pppMngStPtr;
extern _pppEnvStChangeTex* pppEnvStPtr;

struct ChangeTexDisplayList {
	u32 m_size;
	void* m_data;
	u16 m_material;
	u16 _pad;
};

struct ChangeTexMeshData {
	u8 _pad0[0x20];
	void* m_normals;
	u8 _pad1[0x28];
	s32 m_displayListCount;
	ChangeTexDisplayList* m_displayLists;
};

struct ChangeTexMeshRef {
	u8 _pad0[0x8];
	ChangeTexMeshData* m_data;
	u8 _padC[0x14 - 0xC];
};

struct ChangeTexWork {
	float m_value0;
	float m_value1;
	float m_value2;
	int m_meshColorArrays;
	int m_displayListArrays;
	int _pad14;
	void* m_charaObj;
	int m_texture;
	int _pad20;
	void* m_context;
	Vec m_bboxMin;
	int _pad34;
	Vec m_bboxMax;
	float m_cachedValue;
};

extern float FLOAT_80332020;
extern float FLOAT_80332028;
extern double DOUBLE_80332030;
extern double DOUBLE_80332038;
extern char DAT_80332024;
char s_pppChangeTex_cpp_801dd660[] = "pppChangeTex.cpp";

static inline unsigned char* MaterialManRaw() { return reinterpret_cast<unsigned char*>(&MaterialMan); }

void pppInitBlendMode(void);

extern "C" {
		int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh* mapMesh, CMaterialSet* materialSet, int& textureIndex);
		void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int stage, int rasSel, int texSel);
		void SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(void*, void*, unsigned int, int, int);

	void _WaitDrawDone__8CGraphicFPci(CGraphic* graphic, const char* file, int line);
		void* GetCharaHandlePtr__FP8CGObjectl(void* obj, long index);
		int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void* handle);
		void pppHeapUseRate__FPQ27CMemory6CStage(void* stage);
		void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(void*, long, float&, float&, float&, float, float&, float&);
		int GetTextureFromRSD__FiP9_pppEnvSt(int, _pppEnvStChangeTex*);
		void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, void*, char*, int);
		void ReWriteDisplayList__5CUtilFPvUlUl(void*, void*, unsigned long, unsigned long);
		void CalcBoundaryBoxQuantized__5CUtilFP3VecP3VecP6S16VecUlUl(void*, void*, void*, void*, unsigned long, unsigned long);
}

/*
 * --INFO--
 * PAL Address: 0x800d4164
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f2(CChara::CModel* model, void* param_2, void* param_3, int param_4, int param_5, float (*param_6) [4])
{
	ChangeTexMeshRef* meshes = *(ChangeTexMeshRef**)((char*)model + 0xAC);
	ChangeTexDisplayList* displayList = meshes[param_4].m_data->m_displayLists + param_5;
	int textureInfo = *(int*)((char*)param_2 + 0x1C);

	if (*(u8*)((char*)param_3 + 0x14) == 0) {
		*(int*)(MaterialManRaw() + 0xd0) = (int)param_2 + 0x1c + 0x28;
		*(int*)(MaterialManRaw() + 0x44) = 0xFFFFFFFF;
		*(char*)(MaterialManRaw() + 0x4c) = 0xFF;
		*(int*)(MaterialManRaw() + 0x11c) = 0;
		*(int*)(MaterialManRaw() + 0x120) = 0x1E;
		*(int*)(MaterialManRaw() + 0x124) = 0;
		*(char*)(MaterialManRaw() + 0x205) = 0xFF;
		*(char*)(MaterialManRaw() + 0x206) = 0xFF;
		*(int*)(MaterialManRaw() + 0x58) = 0;
		*(int*)(MaterialManRaw() + 0x5c) = 0;
		*(char*)(MaterialManRaw() + 0x208) = 0;
		*(int*)(MaterialManRaw() + 0x48) = 0xADE0F;
		*(int*)(MaterialManRaw() + 0xD0) = textureInfo + 0x28;
		*(int*)(MaterialManRaw() + 0x128) = 0;
		*(int*)(MaterialManRaw() + 0x12c) = 0x1E;
		*(int*)(MaterialManRaw() + 0x130) = 0;
		*(int*)(MaterialManRaw() + 0x40) = 0xADE0F;
	}

	SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
	    &MaterialMan, *(void**)(*(int*)((char*)model + 0xA4) + 0x24), displayList->m_material, 0, 0);
	GXCallDisplayList(displayList->m_data, displayList->m_size);
}

/*
 * --INFO--
 * PAL Address: 0x800d3fd8
 * PAL Size: 396b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f2(CChara::CModel* model, void* param_2, void* param_3, int meshIdx, float (*) [4])
{
	ChangeTexMeshRef* meshes = *(ChangeTexMeshRef**)((char*)model + 0xAC);
	int displayListIdx;
	int* displayListPtr;
	int dlArrayBase;
	int dlOffset;
	void* meshColorArrays;
	void* meshColorArray;
	ChangeTexMeshData* meshData;
	ChangeTexDisplayList* displayList;

	if (*(u8*)((char*)param_3 + 0x14) != 0) {
		meshColorArrays = *(void**)((char*)param_2 + 0xC);
		dlOffset = *(int*)((char*)param_2 + 0x1c);
		meshData = meshes[meshIdx].m_data;
		displayList = meshData->m_displayLists;
		if (meshColorArrays != 0) {
			meshColorArray = *(void**)((u8*)meshColorArrays + meshIdx * 4);
			if (meshColorArray != 0) {
				*(void**)(MaterialManRaw() + 4) = meshData->m_normals;
				GXSetArray((GXAttr)0xb, meshColorArray, 4);
				*(int*)(MaterialManRaw() + 0xd0) = dlOffset + 0x28;
				displayListIdx = meshData->m_displayListCount - 1;
				dlOffset = displayListIdx * 4;
				while (displayListIdx >= 0) {
					dlArrayBase = *(int*)(meshIdx * 4 + *(int*)((char*)param_2 + 0x10));
					*(int*)(MaterialManRaw() + 0x44) = -1;
					*(char*)(MaterialManRaw() + 0x4c) = 0xff;
					*(int*)(MaterialManRaw() + 0x11c) = 0;
					*(int*)(MaterialManRaw() + 0x120) = 0x1e;
					*(int*)(MaterialManRaw() + 0x124) = 0;
					*(char*)(MaterialManRaw() + 0x205) = 0xff;
					*(char*)(MaterialManRaw() + 0x206) = 0xff;
					*(int*)(MaterialManRaw() + 0x58) = 0;
					*(int*)(MaterialManRaw() + 0x5c) = 0;
					*(char*)(MaterialManRaw() + 0x208) = 0;
					*(int*)(MaterialManRaw() + 0x128) = 0;
					*(int*)(MaterialManRaw() + 0x12c) = 0x1e;
					*(int*)(MaterialManRaw() + 0x130) = 0;
					*(int*)(MaterialManRaw() + 0x48) = 0xade0f;
					*(int*)(MaterialManRaw() + 0x128) = 0;
					*(int*)(MaterialManRaw() + 0x12c) = 0x1e;
					*(int*)(MaterialManRaw() + 0x130) = 0;
					*(int*)(MaterialManRaw() + 0x40) = 0xade0f;
					SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
					    &MaterialMan, *(void**)(*(int*)((char*)model + 0xA4) + 0x24), displayList->m_material, 0, 0);
					displayListPtr = *(int**)(dlArrayBase + dlOffset);
					GXCallDisplayList((void*)displayListPtr[0], (unsigned int)displayListPtr[1]);
					dlOffset -= 4;
					displayListIdx -= 1;
					displayList += 1;
				}
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013f744
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructChangeTex(pppChangeTex* changeTex, pppChangeTexUnkC* data)
{
	float init = kPppChangeTexInit;
	ChangeTexWork* work = (ChangeTexWork*)((char*)changeTex + data->m_serializedDataOffsets[2] + 0x80);

	work->m_value0 = init;
	work->m_value2 = init;
	work->m_value1 = init;
	work->m_charaObj = 0;
	work->m_context = pppMngStPtr;
	work->m_texture = 0;
	work->m_meshColorArrays = 0;
	work->m_displayListArrays = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8013f720
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2ChangeTex(pppChangeTex* changeTex, pppChangeTexUnkC* data)
{
	ChangeTexWork* work = (ChangeTexWork*)((char*)changeTex + data->m_serializedDataOffsets[2] + 0x80);
	float init = kPppChangeTexInit;

	work->m_value0 = init;
	work->m_value2 = init;
	work->m_value1 = init;
}

/*
 * --INFO--
 * PAL Address: 0x8013f504
 * PAL Size: 540b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructChangeTex(pppChangeTex* changeTex, pppChangeTexUnkC* data)
{
	_WaitDrawDone__8CGraphicFPci(&Graphic, s_pppChangeTex_cpp_801dd660, 0x9d);
	int dataOffset = data->m_serializedDataOffsets[2];
	ChangeTexWork* work = (ChangeTexWork*)((char*)changeTex + dataOffset + 0x80);
	void* handle0 = GetCharaHandlePtr__FP8CGObjectl(work->m_charaObj, 0);
	void* handle1 = GetCharaHandlePtr__FP8CGObjectl(work->m_charaObj, 1);
	void* handle2 = GetCharaHandlePtr__FP8CGObjectl(work->m_charaObj, 2);
	int model = 0;

	if (handle0 != 0) {
		model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle0);
		*(void**)(model + 0xe4) = 0;
		*(void**)(model + 0xe8) = 0;
		*(void**)(model + 0xf4) = 0;
		*(void**)(model + 0xfc) = 0;
		*(void**)(model + 0x104) = 0;
	}
	int model1;
	if ((handle1 != 0) && ((model1 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle1)), model1 != 0)) {
		*(void**)(model1 + 0xe4) = 0;
		*(void**)(model1 + 0xe8) = 0;
		*(void**)(model1 + 0xf4) = 0;
		*(void**)(model1 + 0xfc) = 0;
		*(void**)(model1 + 0x104) = 0;
	}
	int model2;
	if ((handle2 != 0) && ((model2 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle2)), model2 != 0)) {
		*(void**)(model2 + 0xe4) = 0;
		*(void**)(model2 + 0xe8) = 0;
		*(void**)(model2 + 0xf4) = 0;
		*(void**)(model2 + 0xfc) = 0;
		*(void**)(model2 + 0x104) = 0;
	}

	void** stageArray = (void**)work->m_displayListArrays;
	void** meshArray;
	if ((stageArray != 0) && ((meshArray = (void**)work->m_meshColorArrays), meshArray != 0)) {
		int meshList = *(int*)(model + 0xac);
		void** curStageArray = stageArray;
		void** curMeshArray = meshArray;
		for (unsigned int i = 0; i < *(unsigned int*)(*(int*)(model + 0xA4) + 0xC); i++) {
			int meshData = *(int*)(meshList + 8);
			void** dlEntries = (void**)*curStageArray;
			for (unsigned int j = 0; j < *(unsigned int*)(meshData + 0x4c); j++) {
				if (*(void**)*dlEntries != 0) {
					pppHeapUseRate__FPQ27CMemory6CStage(*(void**)*dlEntries);
					*(void**)*dlEntries = 0;
				}
				if (*dlEntries != 0) {
					pppHeapUseRate__FPQ27CMemory6CStage(*dlEntries);
					*dlEntries = 0;
				}
				dlEntries++;
			}

			if (*curStageArray != 0) {
				pppHeapUseRate__FPQ27CMemory6CStage(*curStageArray);
				*curStageArray = 0;
			}
			if (*curMeshArray != 0) {
				pppHeapUseRate__FPQ27CMemory6CStage(*curMeshArray);
				*curMeshArray = 0;
			}

			curStageArray++;
			curMeshArray++;
			meshList += 0x14;
		}

		if (stageArray != 0) {
			pppHeapUseRate__FPQ27CMemory6CStage(stageArray);
		}
		if (meshArray != 0) {
			pppHeapUseRate__FPQ27CMemory6CStage(meshArray);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013eff8
 * PAL Size: 1292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameChangeTex(pppChangeTex* changeTex, pppChangeTexUnkB* step, pppChangeTexUnkC* data)
{
	if (gPppCalcDisabled != 0) {
		return;
	}

	s32* serializedDataOffsets = data->m_serializedDataOffsets;
	int colorOffset = serializedDataOffsets[1];
	ChangeTexWork* work = (ChangeTexWork*)((char*)&changeTex->field0_0x0 + serializedDataOffsets[2] + 0x80);
	int model0 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(
	    GetCharaHandlePtr__FP8CGObjectl(pppMngStPtr->m_charaObj, 0));

	CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
	    &changeTex->field0_0x0, step->m_graphId, work->m_value0, work->m_value1, work->m_value2, step->m_initWOrk,
	    step->m_stepValue, step->m_arg3);

	work->m_charaObj = pppMngStPtr->m_charaObj;
	work->m_context = pppEnvStPtr;
	*(ChangeTexWork**)(model0 + 0xE4) = work;
	*(pppChangeTexUnkB**)(model0 + 0xE8) = step;
	*(void**)(model0 + 0xFC) = (void*)ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f2;
	*(void**)(model0 + 0x104) = (void*)ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f2;

	work->m_texture = GetTextureFromRSD__FiP9_pppEnvSt(step->m_dataValIndex, pppEnvStPtr);

	void* handle1 = GetCharaHandlePtr__FP8CGObjectl(work->m_charaObj, 1);
	void* handle2 = GetCharaHandlePtr__FP8CGObjectl(work->m_charaObj, 2);

	int model;
	if ((handle1 != 0) && ((model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle1)), model != 0)) {
		*(ChangeTexWork**)(model + 0xE4) = work;
		*(pppChangeTexUnkB**)(model + 0xE8) = step;
		*(void**)(model + 0xFC) = (void*)ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f2;
		*(void**)(model + 0x104) = (void*)ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f2;
	}

	if ((handle2 != 0) && ((model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle2)), model != 0)) {
		*(ChangeTexWork**)(model + 0xE4) = work;
		*(pppChangeTexUnkB**)(model + 0xE8) = step;
		*(void**)(model + 0xFC) = (void*)ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f2;
		*(void**)(model + 0x104) = (void*)ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f2;
	}

	if (step->m_payload[0] == 0) {
		return;
	}

	int texObj = GetTextureFromRSD__FiP9_pppEnvSt(step->m_dataValIndex, pppEnvStPtr);
	if (texObj == 0) {
		return;
	}
	work->m_texture = texObj;

	int meshList = *(int*)(model0 + 0xAC);
	if ((work->m_meshColorArrays == 0) && (work->m_displayListArrays == 0)) {
		work->m_cachedValue = FLOAT_80332020;
		work->m_meshColorArrays = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
		    *(int*)(*(int*)(model0 + 0xA4) + 0xC) << 2, pppEnvStPtr->m_stagePtr, s_pppChangeTex_cpp_801dd660, 0x163);
		work->m_displayListArrays = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
		    *(int*)(*(int*)(model0 + 0xA4) + 0xC) << 2, pppEnvStPtr->m_stagePtr, s_pppChangeTex_cpp_801dd660, 0x166);

		int* meshColorArrays = (int*)work->m_meshColorArrays;
		int arrayOffset = 0;
		for (unsigned int meshIdx = 0; meshIdx < *(unsigned int*)(*(int*)(model0 + 0xA4) + 0xC); meshIdx++) {
			int meshHdr = *(int*)(meshList + 8);
			if (strcmp((char*)meshHdr, &DAT_80332024) == 0) {
				CalcBoundaryBoxQuantized__5CUtilFP3VecP3VecP6S16VecUlUl(
				    &gUtil, &work->m_bboxMin, &work->m_bboxMax, *(void**)(meshList + 0xC), *(unsigned long*)(meshHdr + 0x14),
				    *(unsigned long*)(*(int*)(model0 + 0xA4) + 0x34));
			}

			*(int*)(work->m_displayListArrays + arrayOffset) = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
			    *(int*)(*(int*)(meshList + 8) + 0x4C) << 2, pppEnvStPtr->m_stagePtr, s_pppChangeTex_cpp_801dd660, 0x181);

			int dlIdx = *(int*)(*(int*)(meshList + 8) + 0x4C) - 1;
			int* dlInfo = (int*)(*(int*)(*(int*)(meshList + 8) + 0x50));
			int* dlEntry = (int*)(*(int*)(work->m_displayListArrays + arrayOffset) + dlIdx * 4);
			for (; -1 < dlIdx; dlIdx = dlIdx - 1) {
				int dlPair = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
				    8, pppEnvStPtr->m_stagePtr, s_pppChangeTex_cpp_801dd660, 0x18B);
				*dlEntry = dlPair;
				*(int*)(*dlEntry + 4) = *dlInfo;
				*(int*)*dlEntry = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
				    *dlInfo, pppEnvStPtr->m_stagePtr, s_pppChangeTex_cpp_801dd660, 0x18D);
				memcpy(*(void**)*dlEntry, (void*)dlInfo[1], dlInfo[0]);
				ReWriteDisplayList__5CUtilFPvUlUl(&gUtil, *(void**)*dlEntry, (unsigned long)dlInfo[0], 1);
				dlEntry = dlEntry - 1;
				dlInfo = dlInfo + 3;
			}

			*meshColorArrays = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
			    *(int*)(*(int*)(meshList + 8) + 0x14) << 2, pppEnvStPtr->m_stagePtr, s_pppChangeTex_cpp_801dd660, 0x196);
			memset((void*)*meshColorArrays, 0, *(int*)(*(int*)(meshList + 8) + 0x14) << 2);

			arrayOffset += 4;
			meshColorArrays = meshColorArrays + 1;
			meshList += 0x14;
		}
	}

	if (gPppInConstructor != 0) {
		return;
	}

	union {
		double d;
		u32 u[2];
	} splitScale;
	float currentValue = work->m_value0 * (work->m_bboxMax.y - work->m_bboxMin.y) + work->m_bboxMin.y;

	splitScale.u[0] = 0x43300000;
	splitScale.u[1] = (1 << *(int*)(*(int*)(model0 + 0xA4) + 0x34)) ^ 0x80000000;
	short splitY = (short)(int)(currentValue * (float)(splitScale.d - DOUBLE_80332030));
	if (work->m_cachedValue == currentValue) {
		return;
	}

	work->m_cachedValue = currentValue;

	union {
		double d;
		u32 u[2];
	} alphaScale;

	alphaScale.u[0] = 0x43300000;
	alphaScale.u[1] = (u8)*((u8*)changeTex + colorOffset + 0x8B);
	double alphaBase = (double)(FLOAT_80332028 * ((float)(alphaScale.d - DOUBLE_80332038) / FLOAT_80332028));

	int arrayOffset = 0;
	meshList = *(int*)(model0 + 0xAC);
	for (unsigned int meshIdx = 0; meshIdx < *(unsigned int*)(*(int*)(model0 + 0xA4) + 0xC); meshIdx++) {
		int pointOffset = 0;
		int colorBase = *(int*)(work->m_meshColorArrays + arrayOffset);
		int colorPtr = colorBase;
		unsigned int vertCount;
		for (unsigned int v = 0; (vertCount = *(unsigned int*)(*(int*)(meshList + 8) + 0x14), v < vertCount); v++) {
			if (step->m_payload[0] == 1) {
				if (*(short*)(*(int*)(meshList + 0xC) + pointOffset + 2) < splitY) {
					*(char*)(colorPtr + 3) = (char)(int)alphaBase;
				} else {
					*(char*)(colorPtr + 3) = 0;
				}
			} else if (step->m_payload[0] == 2) {
				if (splitY < *(short*)(*(int*)(meshList + 0xC) + pointOffset + 2)) {
					*(char*)(colorPtr + 3) = (char)(int)alphaBase;
				} else {
					*(char*)(colorPtr + 3) = 0;
				}
			}

			pointOffset += 6;
			colorPtr += 4;
		}

		DCFlushRange((void*)colorBase, vertCount << 2);
		arrayOffset += 4;
		meshList += 0x14;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013ef94
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderChangeTex(pppChangeTex*, pppChangeTexUnkB* step, pppChangeTexUnkC*)
{
	int textureIndex;

	if (step->m_dataValIndex != 0xffff) {
		_pppEnvStChangeTex* env = pppEnvStPtr;
		CMapMesh* mapMesh = env->m_mapMeshPtr[step->m_dataValIndex];
		textureIndex = 0;
		GetTexture__8CMapMeshFP12CMaterialSetRi(
		    mapMesh, env->m_materialSetPtr, textureIndex);
		_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
		pppInitBlendMode();
	}
}
