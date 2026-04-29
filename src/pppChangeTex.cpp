#include "ffcc/pppChangeTex.h"
#include "ffcc/gobject.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
extern "C" {
extern const float kPppChangeTexInit;
extern int gPppCalcDisabled;
extern unsigned char gPppInConstructor;
}
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
	u8 _pad0[0x14];
	u32 m_vertexCount;
	u8 _pad18[0x8];
	void* m_normals;
	u8 _pad1[0x28];
	s32 m_displayListCount;
	ChangeTexDisplayList* m_displayLists;
};

struct ChangeTexMeshRef {
	u8 _pad0[0x8];
	ChangeTexMeshData* m_data;
	s16* m_points;
	u8 _pad10[0x14 - 0x10];
};

struct ChangeTexModelData {
	u8 _pad0[0xC];
	u32 m_meshCount;
	u8 _pad10[0x14];
	CMaterialSet* m_materialSet;
	u8 _pad28[0xC];
	s32 m_frameShift;
};

struct ChangeTexWork {
	float m_value0;
	float m_value1;
	float m_value2;
	void* m_meshColorArrays;
	void* m_displayListArrays;
	int _pad14;
	CGObject* m_charaObj;
	void* m_texture;
	int _pad20;
	void* m_context;
	Vec m_bboxMin;
	int _pad34;
	Vec m_bboxMax;
	float m_cachedValue;
};

struct ChangeTexModelRaw {
	u8 _pad0[0x68];
	Mtx m_matrix;
	u8 _pad98[0xC];
	ChangeTexModelData* m_data;
	u8 _padA8[0x4];
	ChangeTexMeshRef* m_meshes;
	u8 _padB0[0x34];
	ChangeTexWork* m_state;
	pppChangeTexUnkB* m_step;
	u8 _padEC[0x8];
	void* m_beforeDrawCallback;
	u8 _padF8[0x4];
	void (*m_drawMeshDlCallback)(CChara::CModel*, void*, void*, int, int, float (*)[4]);
	u8 _pad100[0x4];
	void (*m_afterDrawMeshCallback)(CChara::CModel*, void*, void*, int, float (*)[4]);
};

STATIC_ASSERT(offsetof(ChangeTexModelRaw, m_data) == 0xA4);
STATIC_ASSERT(offsetof(ChangeTexModelRaw, m_meshes) == 0xAC);
STATIC_ASSERT(offsetof(ChangeTexModelRaw, m_state) == 0xE4);
STATIC_ASSERT(offsetof(ChangeTexModelRaw, m_step) == 0xE8);
STATIC_ASSERT(offsetof(ChangeTexModelRaw, m_beforeDrawCallback) == 0xF4);
STATIC_ASSERT(offsetof(ChangeTexModelRaw, m_drawMeshDlCallback) == 0xFC);
STATIC_ASSERT(offsetof(ChangeTexModelRaw, m_afterDrawMeshCallback) == 0x104);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_vertexCount) == 0x14);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_normals) == 0x20);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_displayListCount) == 0x4C);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_displayLists) == 0x50);
STATIC_ASSERT(offsetof(ChangeTexMeshRef, m_points) == 0xC);
STATIC_ASSERT(offsetof(ChangeTexModelData, m_meshCount) == 0xC);
STATIC_ASSERT(offsetof(ChangeTexModelData, m_materialSet) == 0x24);
STATIC_ASSERT(offsetof(ChangeTexModelData, m_frameShift) == 0x34);

extern const float FLOAT_80332020 = -10000.0f;
extern const char DAT_80332024[] = "obj";
extern const float FLOAT_80332028 = 255.0f;
extern const double DOUBLE_80332030 = 4503601774854144.0;
extern const double DOUBLE_80332038 = 4503599627370496.0;
static const char s_pppChangeTex_cpp_801dd660[] = "pppChangeTex.cpp";

static inline unsigned char* MaterialManRaw() { return reinterpret_cast<unsigned char*>(&MaterialMan); }

static inline float LoadFloat(const float& value)
{
	return value;
}

static inline double LoadDouble(const double& value)
{
	return value;
}

void pppInitBlendMode(void);
CChara::CModel* GetCharaModelPtr(CCharaPcs::CHandle*);
CCharaPcs::CHandle* GetCharaHandlePtr(CGObject*, long);

extern "C" {
		int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh* mapMesh, CMaterialSet* materialSet, int& textureIndex);
		void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int stage, int rasSel, int texSel);
		void SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(void*, void*, unsigned int, int, int);

	void _WaitDrawDone__8CGraphicFPci(CGraphic* graphic, const char* file, int line);
		void* GetCharaHandlePtr__FP8CGObjectl(void* obj, long index);
		int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void* handle);
		void pppHeapUseRate__FPQ27CMemory6CStage(void* stage);
		void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(void*, long, float&, float&, float&, float, float&, float&);
		void* GetTextureFromRSD__FiP9_pppEnvSt(int, _pppEnvStChangeTex*);
		void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, void*, char*, int);
		void ReWriteDisplayList__5CUtilFPvUlUl(void*, void*, unsigned long, unsigned long);
		void CalcBoundaryBoxQuantized__5CUtilFP3VecP3VecP6S16VecUlUl(void*, void*, void*, void*, unsigned long, unsigned long);
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
	u8* base = (u8*)changeTex;
	ChangeTexWork* work = (ChangeTexWork*)(base + serializedDataOffsets[2] + 0x80);
	u8* colorData = base + serializedDataOffsets[1] + 0x80;
	CCharaPcs::CHandle* handle0 = GetCharaHandlePtr((CGObject*)pppMngStPtr->m_charaObj, 0);
	CChara::CModel* model0 = GetCharaModelPtr(handle0);
	ChangeTexModelRaw* model0Raw = (ChangeTexModelRaw*)model0;

	CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
	    changeTex, step->m_graphId, work->m_value0, work->m_value1, work->m_value2, step->m_initWOrk,
	    step->m_stepValue, step->m_arg3);

	work->m_charaObj = (CGObject*)pppMngStPtr->m_charaObj;
	work->m_context = pppEnvStPtr;
	model0Raw->m_state = work;
	model0Raw->m_step = step;
	model0Raw->m_drawMeshDlCallback = ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f2;
	model0Raw->m_afterDrawMeshCallback = ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f2;

	work->m_texture = GetTextureFromRSD__FiP9_pppEnvSt(step->m_dataValIndex, pppEnvStPtr);

	CCharaPcs::CHandle* handle1 = GetCharaHandlePtr(work->m_charaObj, 1);
	CCharaPcs::CHandle* handle2 = GetCharaHandlePtr(work->m_charaObj, 2);

	CChara::CModel* model;
	if ((handle1 != 0) && ((model = GetCharaModelPtr(handle1)), model != 0)) {
		ChangeTexModelRaw* modelRaw = (ChangeTexModelRaw*)model;
		modelRaw->m_state = work;
		modelRaw->m_step = step;
		modelRaw->m_drawMeshDlCallback = ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f2;
		modelRaw->m_afterDrawMeshCallback = ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f2;
	}

	if ((handle2 != 0) && ((model = GetCharaModelPtr(handle2)), model != 0)) {
		ChangeTexModelRaw* modelRaw = (ChangeTexModelRaw*)model;
		modelRaw->m_state = work;
		modelRaw->m_step = step;
		modelRaw->m_drawMeshDlCallback = ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f2;
		modelRaw->m_afterDrawMeshCallback = ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f2;
	}

	if (step->m_payload[0] == 0) {
		return;
	}

	void* texObj = GetTextureFromRSD__FiP9_pppEnvSt(step->m_dataValIndex, pppEnvStPtr);
	if (texObj == 0) {
		return;
	}
	work->m_texture = texObj;

	int meshList = (int)model0Raw->m_meshes;
	if ((work->m_meshColorArrays == 0) && (work->m_displayListArrays == 0)) {
		work->m_cachedValue = LoadFloat(FLOAT_80332020);
		work->m_meshColorArrays = pppMemAlloc__FUlPQ27CMemory6CStagePci(
		    model0Raw->m_data->m_meshCount << 2, pppEnvStPtr->m_stagePtr,
		    const_cast<char*>(s_pppChangeTex_cpp_801dd660), 0x163);
		work->m_displayListArrays = pppMemAlloc__FUlPQ27CMemory6CStagePci(
		    model0Raw->m_data->m_meshCount << 2, pppEnvStPtr->m_stagePtr,
		    const_cast<char*>(s_pppChangeTex_cpp_801dd660), 0x166);

		int* meshColorArrays = (int*)work->m_meshColorArrays;
		int arrayOffset = 0;
		for (unsigned int meshIdx = 0; meshIdx < model0Raw->m_data->m_meshCount; meshIdx++) {
			int meshHdr = *(int*)(meshList + 8);
			if (strcmp((char*)meshHdr, DAT_80332024) == 0) {
				CalcBoundaryBoxQuantized__5CUtilFP3VecP3VecP6S16VecUlUl(
				    &gUtil, &work->m_bboxMin, &work->m_bboxMax, *(void**)(meshList + 0xC), *(unsigned long*)(meshHdr + 0x14),
				    *(unsigned long*)(*(int*)((char*)model0 + 0xA4) + 0x34));
			}

			*(int*)((u8*)work->m_displayListArrays + arrayOffset) = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
			    *(int*)(*(int*)(meshList + 8) + 0x4C) << 2, pppEnvStPtr->m_stagePtr,
			    const_cast<char*>(s_pppChangeTex_cpp_801dd660), 0x181);

			int dlIdx = *(int*)(*(int*)(meshList + 8) + 0x4C) - 1;
			int* dlInfo = (int*)(*(int*)(*(int*)(meshList + 8) + 0x50));
			int* dlEntry = (int*)(*(int*)((u8*)work->m_displayListArrays + arrayOffset) + dlIdx * 4);
			for (; dlIdx >= 0; dlIdx = dlIdx - 1, dlInfo = dlInfo + 3) {
				int dlPair = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
				    8, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppChangeTex_cpp_801dd660), 0x18B);
				*dlEntry = dlPair;
				*(int*)(*dlEntry + 4) = *dlInfo;
				*(int*)*dlEntry = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
				    *dlInfo, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppChangeTex_cpp_801dd660), 0x18D);
				memcpy(*(void**)*dlEntry, (void*)dlInfo[1], dlInfo[0]);
				ReWriteDisplayList__5CUtilFPvUlUl(&gUtil, *(void**)*dlEntry, (unsigned long)dlInfo[0], 1);
				dlEntry = dlEntry - 1;
			}

			*meshColorArrays = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
			    *(int*)(*(int*)(meshList + 8) + 0x14) << 2, pppEnvStPtr->m_stagePtr,
			    const_cast<char*>(s_pppChangeTex_cpp_801dd660), 0x196);
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
	} scale;
	float currentValue = work->m_value0 * (work->m_bboxMax.y - work->m_bboxMin.y) + work->m_bboxMin.y;

	scale.u[0] = 0x43300000;
	scale.u[1] = (1 << model0Raw->m_data->m_frameShift) ^ 0x80000000;
	short splitY = (short)(int)(currentValue * (float)(scale.d - LoadDouble(DOUBLE_80332030)));
	if (work->m_cachedValue == currentValue) {
		return;
	}

	work->m_cachedValue = currentValue;

	scale.u[0] = 0x43300000;
	scale.u[1] = colorData[0xB];
	double alphaBase = (double)(LoadFloat(FLOAT_80332028) * ((float)(scale.d - LoadDouble(DOUBLE_80332038)) / LoadFloat(FLOAT_80332028)));

	int arrayOffset = 0;
	meshList = (int)model0Raw->m_meshes;
	for (unsigned int meshIdx = 0; meshIdx < model0Raw->m_data->m_meshCount; meshIdx++) {
		int pointOffset = 0;
		int colorBase = *(int*)((u8*)work->m_meshColorArrays + arrayOffset);
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
				if (*(short*)(*(int*)(meshList + 0xC) + pointOffset + 2) > splitY) {
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
 * PAL Address: 0x8013f504
 * PAL Size: 540b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructChangeTex(pppChangeTex* changeTex, pppChangeTexUnkC* data)
{
	_WaitDrawDone__8CGraphicFPci(&Graphic, const_cast<char*>(s_pppChangeTex_cpp_801dd660), 0x9d);
	int dataOffset = data->m_serializedDataOffsets[2];
	ChangeTexWork* work = (ChangeTexWork*)((char*)changeTex + dataOffset + 0x80);
	void* handle0 = GetCharaHandlePtr__FP8CGObjectl(work->m_charaObj, 0);
	void* handle1 = GetCharaHandlePtr__FP8CGObjectl(work->m_charaObj, 1);
	void* handle2 = GetCharaHandlePtr__FP8CGObjectl(work->m_charaObj, 2);
	ChangeTexModelRaw* model = 0;

	if (handle0 != 0) {
		model = (ChangeTexModelRaw*)GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle0);
		model->m_state = 0;
		model->m_step = 0;
		model->m_beforeDrawCallback = 0;
		model->m_drawMeshDlCallback = 0;
		model->m_afterDrawMeshCallback = 0;
	}
	ChangeTexModelRaw* model1;
	if ((handle1 != 0) && ((model1 = (ChangeTexModelRaw*)GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle1)), model1 != 0)) {
		model1->m_state = 0;
		model1->m_step = 0;
		model1->m_beforeDrawCallback = 0;
		model1->m_drawMeshDlCallback = 0;
		model1->m_afterDrawMeshCallback = 0;
	}
	ChangeTexModelRaw* model2;
	if ((handle2 != 0) && ((model2 = (ChangeTexModelRaw*)GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle2)), model2 != 0)) {
		model2->m_state = 0;
		model2->m_step = 0;
		model2->m_beforeDrawCallback = 0;
		model2->m_drawMeshDlCallback = 0;
		model2->m_afterDrawMeshCallback = 0;
	}

	void** stageArray = (void**)work->m_displayListArrays;
	void** meshArray;
	if ((stageArray != 0) && ((meshArray = (void**)work->m_meshColorArrays), meshArray != 0)) {
		int meshList = (int)model->m_meshes;
		void** curStageArray = stageArray;
		void** curMeshArray = meshArray;
		for (unsigned int i = 0; i < model->m_data->m_meshCount; i++) {
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
 * PAL Address: 0x8013f784
 * PAL Size: 344b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f2(CChara::CModel* model, void* param_2, void* param_3, int meshIdx, float (*) [4])
{
	ChangeTexModelRaw* modelRaw = (ChangeTexModelRaw*)model;
	ChangeTexWork* work = (ChangeTexWork*)param_2;
	ChangeTexMeshRef* meshes = modelRaw->m_meshes;
	int displayListIdx;
	int* displayListPtr;
	int dlArrayBase;
	int dlOffset;
	int drawTevBits;
	int fullTevBits;
	int allOnes;
	int tevScale;
	void* meshColorArrays;
	void* meshColorArray;
	ChangeTexMeshData* meshData;
	ChangeTexDisplayList* displayList;

	if (*(u8*)((char*)param_3 + 0x14) != 0) {
		meshColorArrays = work->m_meshColorArrays;
		dlOffset = (int)work->m_texture;
		meshData = meshes[meshIdx].m_data;
		displayList = meshData->m_displayLists;
		if (meshColorArrays != 0) {
			meshColorArray = *(void**)((u8*)meshColorArrays + meshIdx * 4);
			if (meshColorArray != 0) {
				*(void**)(MaterialManRaw() + 4) = meshData->m_normals;
				GXSetArray((GXAttr)0xb, meshColorArray, 4);
				*(int*)(MaterialManRaw() + 0xd0) = dlOffset + 0x28;
				fullTevBits = 0xADE0F;
				drawTevBits = 0xACE0F;
				allOnes = -1;
				u8 fullByte = 0xFF;
				tevScale = 0x1e;
				displayListIdx = meshData->m_displayListCount - 1;
				dlOffset = displayListIdx * 4;
				while (displayListIdx >= 0) {
					dlArrayBase = *(int*)(meshIdx * 4 + (int)work->m_displayListArrays);
					*(int*)(MaterialManRaw() + 0x48) = drawTevBits;
					*(int*)(MaterialManRaw() + 0x128) = 0;
					*(int*)(MaterialManRaw() + 0x12c) = tevScale;
					*(int*)(MaterialManRaw() + 0x130) = 0;
					*(int*)(MaterialManRaw() + 0x44) = allOnes;
					*(u8*)(MaterialManRaw() + 0x4c) = fullByte;
					*(int*)(MaterialManRaw() + 0x11c) = 0;
					*(int*)(MaterialManRaw() + 0x120) = tevScale;
					*(int*)(MaterialManRaw() + 0x124) = 0;
					*(u8*)(MaterialManRaw() + 0x205) = fullByte;
					*(u8*)(MaterialManRaw() + 0x206) = fullByte;
					*(int*)(MaterialManRaw() + 0x58) = 0;
					*(int*)(MaterialManRaw() + 0x5c) = 0;
					*(char*)(MaterialManRaw() + 0x208) = 0;
					*(int*)(MaterialManRaw() + 0x48) = fullTevBits;
					*(int*)(MaterialManRaw() + 0x128) = 0;
					*(int*)(MaterialManRaw() + 0x12c) = tevScale;
					*(int*)(MaterialManRaw() + 0x130) = 0;
					*(int*)(MaterialManRaw() + 0x40) = fullTevBits;
					SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
					    &MaterialMan, modelRaw->m_data->m_materialSet, displayList->m_material, 0, 0);
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
 * PAL Address: 0x8013f8dc
 * PAL Size: 244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f2(CChara::CModel* model, void* param_2, void* param_3, int param_4, int param_5, float (*param_6) [4])
{
	ChangeTexModelRaw* modelRaw = (ChangeTexModelRaw*)model;
	ChangeTexWork* work = (ChangeTexWork*)param_2;
	ChangeTexMeshRef* meshes = modelRaw->m_meshes;
	ChangeTexMeshData* meshData = meshes[param_4].m_data;
	ChangeTexDisplayList* displayList = meshData->m_displayLists + param_5;
	int textureInfo = (int)work->m_texture;

	if (*(u8*)((char*)param_3 + 0x14) == 0) {
		int fullTevBits = 0xADE0F;
		int zero = 0;
		int allOnes = -1;
		int tevScale = 0x1E;
		u8 fullByte = 0xFF;

		*(int*)(MaterialManRaw() + 0x48) = 0xACE0F;
		*(int*)(MaterialManRaw() + 0x128) = zero;
		*(int*)(MaterialManRaw() + 0x12c) = tevScale;
		*(int*)(MaterialManRaw() + 0x130) = zero;
		*(int*)(MaterialManRaw() + 0x44) = allOnes;
		*(u8*)(MaterialManRaw() + 0x4c) = fullByte;
		*(int*)(MaterialManRaw() + 0x11c) = zero;
		*(int*)(MaterialManRaw() + 0x120) = tevScale;
		*(int*)(MaterialManRaw() + 0x124) = zero;
		*(u8*)(MaterialManRaw() + 0x205) = fullByte;
		*(u8*)(MaterialManRaw() + 0x206) = fullByte;
		*(int*)(MaterialManRaw() + 0x58) = zero;
		*(int*)(MaterialManRaw() + 0x5c) = zero;
		*(char*)(MaterialManRaw() + 0x208) = zero;
		*(int*)(MaterialManRaw() + 0x48) = fullTevBits;
		*(int*)(MaterialManRaw() + 0xd0) = textureInfo + 0x28;
		*(int*)(MaterialManRaw() + 0x128) = zero;
		*(int*)(MaterialManRaw() + 0x12c) = tevScale;
		*(int*)(MaterialManRaw() + 0x130) = zero;
		*(int*)(MaterialManRaw() + 0x40) = fullTevBits;
	}

	SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
	    &MaterialMan, modelRaw->m_data->m_materialSet, displayList->m_material, 0, 0);
	GXCallDisplayList(displayList->m_data, displayList->m_size);
}
