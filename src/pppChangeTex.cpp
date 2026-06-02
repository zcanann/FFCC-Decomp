#include "ffcc/pppChangeTex.h"
#include "ffcc/gobject.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/textureman.h"
extern "C" {
extern const float kPppChangeTexInit;
}
#include "ffcc/util.h"
#include "dolphin/gx.h"
#include <string.h>
#include <dolphin/os/OSCache.h>

typedef CChara::CMesh::CDisplayList ChangeTexDisplayList;

struct ChangeTexDisplayListCopy {
	void* m_data;
	u32 m_size;
};

typedef CChara::CMesh::CRefData ChangeTexMeshData;
typedef CChara::CMesh ChangeTexMeshRef;

struct ChangeTexWork {
	float m_value0;
	float m_value1;
	float m_value2;
	GXColor** m_meshColorArrays;
	ChangeTexDisplayListCopy*** m_displayListArrays;
	int _pad14;
	CGObject* m_charaObj;
	CTexture* m_texture;
	int _pad20;
	void* m_context;
	Vec m_bboxMin;
	int _pad34;
	Vec m_bboxMax;
	float m_cachedValue;
};

STATIC_ASSERT(offsetof(ChangeTexMeshData, m_vertexCount) == 0x14);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_normals) == 0x20);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_displayListCount) == 0x4C);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_displayLists) == 0x50);
STATIC_ASSERT(offsetof(ChangeTexMeshRef, m_workPositions) == 0xC);
STATIC_ASSERT(sizeof(ChangeTexDisplayListCopy) == 0x8);

extern const float kPppChangeTexCachedValueInit = -10000.0f;
extern const char sPppChangeTexMeshObjectName[] = "obj";
extern const float kPppChangeTexAlphaScale = 255.0f;
extern "C" const char s_pppChangeTex_cpp[] = "pppChangeTex.cpp";

static inline ChangeTexMeshRef* ChangeTexMeshes(CChara::CModel* model)
{
	return model->m_meshes;
}

static inline float LoadFloat(const float& value)
{
	return value;
}

static inline unsigned char* MaterialManRaw()
{
	return reinterpret_cast<unsigned char*>(&MaterialMan);
}

static void ChangeTex_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
static void ChangeTex_AfterDrawMeshCallback(CChara::CModel*, void*, void*, int, float (*)[4]);

static inline void SetChangeTexModelCallbacks(CChara::CModel* model, ChangeTexWork* work, pppChangeTexUnkB* step)
{
	model->SetCallbackContext(work, step);
	model->SetDrawMeshDLCallback(ChangeTex_DrawMeshDLCallback);
	model->SetAfterDrawMeshCallback(ChangeTex_AfterDrawMeshCallback);
}

static inline void ClearChangeTexModelCallbacks(CChara::CModel* model)
{
	model->SetCallbackContext(0, 0);
	model->SetBeforeMeshLockEnvCallback(0);
	model->SetDrawMeshDLCallback(0);
	model->SetAfterDrawMeshCallback(0);
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
		_pppEnvSt* env = ppvEnv;
		CMapMesh* mapMesh = env->m_mapMeshPtr[step->m_dataValIndex];
		textureIndex = 0;
		mapMesh->GetTexture(env->m_materialSetPtr, textureIndex);
		_GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
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
	ChangeTexWork* work = (ChangeTexWork*)(changeTex->m_object.m_workArea + serializedDataOffsets[2]);
	u8* colorData = changeTex->m_object.m_workArea + serializedDataOffsets[1];
	CCharaPcs::CHandle* handle0 = GetCharaHandlePtr(ppvMng->m_owner, 0);
	CChara::CModel* model0 = GetCharaModelPtr(handle0);

	CalcGraphValue(
	    &changeTex->m_object, step->m_graphId, work->m_value0, work->m_value1, work->m_value2, step->m_initWOrk,
	    step->m_stepValue, step->m_arg3);

	work->m_charaObj = ppvMng->m_owner;
	work->m_context = ppvEnv;
	SetChangeTexModelCallbacks(model0, work, step);

	work->m_texture = reinterpret_cast<CTexture*>(GetTextureFromRSD(step->m_dataValIndex, ppvEnv));

	CCharaPcs::CHandle* handle1 = GetCharaHandlePtr(work->m_charaObj, 1);
	CCharaPcs::CHandle* handle2 = GetCharaHandlePtr(work->m_charaObj, 2);

	CChara::CModel* model;
	if ((handle1 != 0) && ((model = GetCharaModelPtr(handle1)), model != 0)) {
		SetChangeTexModelCallbacks(model, work, step);
	}

	if ((handle2 != 0) && ((model = GetCharaModelPtr(handle2)), model != 0)) {
		SetChangeTexModelCallbacks(model, work, step);
	}

	if (step->m_payload[0] == 0) {
		return;
	}

	CTexture* texture = reinterpret_cast<CTexture*>(GetTextureFromRSD(step->m_dataValIndex, ppvEnv));
	if (texture == 0) {
		return;
	}
	work->m_texture = texture;

	ChangeTexMeshRef* meshList = ChangeTexMeshes(model0);
	if ((work->m_meshColorArrays == 0) && (work->m_displayListArrays == 0)) {
		work->m_cachedValue = LoadFloat(kPppChangeTexCachedValueInit);
		work->m_meshColorArrays = (GXColor**)pppMemAlloc(
		    model0->m_data->m_meshCount << 2, ppvEnv->m_stagePtr,
		    const_cast<char*>(s_pppChangeTex_cpp), 0x163);
		work->m_displayListArrays = (ChangeTexDisplayListCopy***)pppMemAlloc(
		    model0->m_data->m_meshCount << 2, ppvEnv->m_stagePtr,
		    const_cast<char*>(s_pppChangeTex_cpp), 0x166);

		for (unsigned int meshIdx = 0; meshIdx < model0->m_data->m_meshCount; meshIdx++) {
			ChangeTexMeshData* meshData = meshList->m_data;
			if (strcmp(meshData->m_name, sPppChangeTexMeshObjectName) == 0) {
				gUtil.CalcBoundaryBoxQuantized(&work->m_bboxMin, &work->m_bboxMax, meshList->m_workPositions,
				    meshData->m_vertexCount, model0->m_data->m_posQuant);
			}

			work->m_displayListArrays[meshIdx] = static_cast<ChangeTexDisplayListCopy**>(
			    pppMemAlloc(meshData->m_displayListCount * sizeof(ChangeTexDisplayListCopy*), ppvEnv->m_stagePtr,
			                const_cast<char*>(s_pppChangeTex_cpp), 0x181));

			int dlIdx = meshData->m_displayListCount - 1;
			ChangeTexDisplayList* dlInfo = meshData->m_displayLists;
			ChangeTexDisplayListCopy** dlEntry = &work->m_displayListArrays[meshIdx][dlIdx];
			for (; dlIdx >= 0; dlIdx = dlIdx - 1, dlInfo = dlInfo + 1) {
				ChangeTexDisplayListCopy* dlPair = static_cast<ChangeTexDisplayListCopy*>(
				    pppMemAlloc(sizeof(ChangeTexDisplayListCopy), ppvEnv->m_stagePtr,
				                const_cast<char*>(s_pppChangeTex_cpp), 0x18B));
				*dlEntry = dlPair;
				(*dlEntry)->m_size = dlInfo->m_size;
				(*dlEntry)->m_data = pppMemAlloc(
				    dlInfo->m_size, ppvEnv->m_stagePtr, const_cast<char*>(s_pppChangeTex_cpp), 0x18D);
				memcpy((*dlEntry)->m_data, dlInfo->m_data, dlInfo->m_size);
				gUtil.ReWriteDisplayList((*dlEntry)->m_data, (unsigned long)dlInfo->m_size, 1);
				dlEntry = dlEntry - 1;
			}

			work->m_meshColorArrays[meshIdx] = static_cast<GXColor*>(
			    pppMemAlloc(meshData->m_vertexCount * sizeof(GXColor), ppvEnv->m_stagePtr,
			                const_cast<char*>(s_pppChangeTex_cpp), 0x196));
			memset(work->m_meshColorArrays[meshIdx], 0, meshData->m_vertexCount * sizeof(GXColor));

			meshList++;
		}
	}

	if (gPppInConstructor != 0) {
		return;
	}

	float currentValue = work->m_value0 * (work->m_bboxMax.y - work->m_bboxMin.y) + work->m_bboxMin.y;

	short splitY = (short)(int)(currentValue * (float)(1 << model0->m_data->m_posQuant));
	if (work->m_cachedValue == currentValue) {
		return;
	}

	work->m_cachedValue = currentValue;

	double alphaBase =
	    (double)(LoadFloat(kPppChangeTexAlphaScale) * ((float)colorData[0xB] / LoadFloat(kPppChangeTexAlphaScale)));

	meshList = ChangeTexMeshes(model0);
	for (unsigned int meshIdx = 0; meshIdx < model0->m_data->m_meshCount; meshIdx++) {
		GXColor* colors = work->m_meshColorArrays[meshIdx];
		unsigned int vertCount;
		for (unsigned int v = 0; (vertCount = meshList->m_data->m_vertexCount, v < vertCount); v++) {
			if (step->m_payload[0] == 1) {
				if (meshList->m_workPositions[v].y < splitY) {
					colors[v].a = (u8)(int)alphaBase;
				} else {
					colors[v].a = 0;
				}
			} else if (step->m_payload[0] == 2) {
				if (meshList->m_workPositions[v].y > splitY) {
					colors[v].a = (u8)(int)alphaBase;
				} else {
					colors[v].a = 0;
				}
			}
		}

		DCFlushRange(colors, vertCount * sizeof(GXColor));
		meshList++;
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
	Graphic._WaitDrawDone(const_cast<char*>(s_pppChangeTex_cpp), 0x9d);
	int dataOffset = data->m_serializedDataOffsets[2];
	ChangeTexWork* work = (ChangeTexWork*)(changeTex->m_object.m_workArea + dataOffset);
	CCharaPcs::CHandle* handle0 = GetCharaHandlePtr(work->m_charaObj, 0);
	CCharaPcs::CHandle* handle1 = GetCharaHandlePtr(work->m_charaObj, 1);
	CCharaPcs::CHandle* handle2 = GetCharaHandlePtr(work->m_charaObj, 2);
	CChara::CModel* model = 0;

	if (handle0 != 0) {
		model = GetCharaModelPtr(handle0);
		ClearChangeTexModelCallbacks(model);
	}
	CChara::CModel* model1;
	if ((handle1 != 0) && ((model1 = GetCharaModelPtr(handle1)), model1 != 0)) {
		ClearChangeTexModelCallbacks(model1);
	}
	CChara::CModel* model2;
	if ((handle2 != 0) && ((model2 = GetCharaModelPtr(handle2)), model2 != 0)) {
		ClearChangeTexModelCallbacks(model2);
	}

	ChangeTexDisplayListCopy*** stageArray = work->m_displayListArrays;
	GXColor** meshArray;
	if (stageArray != 0) {
		meshArray = work->m_meshColorArrays;
		if (meshArray != 0) {
			goto freeArrays;
		}
	}
	return;

freeArrays:
	ChangeTexMeshRef* meshList = ChangeTexMeshes(model);
	GXColor** meshArrayOrig = meshArray;
	ChangeTexDisplayListCopy*** stageArrayOrig = stageArray;
	for (unsigned int i = 0; i < model->m_data->m_meshCount; i++, meshList++) {
		ChangeTexMeshData* meshData = meshList->m_data;
		ChangeTexDisplayListCopy** dlEntries = *stageArray;
		for (unsigned int j = 0; j < meshData->m_displayListCount; j++) {
			if ((*dlEntries)->m_data != 0) {
				pppHeapUseRate(reinterpret_cast<CMemory::CStage*>((*dlEntries)->m_data));
				(*dlEntries)->m_data = 0;
			}
			if (*dlEntries != 0) {
				pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(*dlEntries));
				*dlEntries = 0;
			}
			dlEntries++;
		}

		if (*stageArray != 0) {
			pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(*stageArray));
			*stageArray = 0;
		}
		if (*meshArray != 0) {
			pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(*meshArray));
			*meshArray = 0;
		}

		stageArray++;
		meshArray++;
	}

	if (stageArrayOrig != 0) {
		pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(stageArrayOrig));
	}
	if (meshArrayOrig != 0) {
		pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(meshArrayOrig));
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
	ChangeTexWork* work = (ChangeTexWork*)(changeTex->m_object.m_workArea + data->m_serializedDataOffsets[2]);
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
	ChangeTexWork* work = (ChangeTexWork*)(changeTex->m_object.m_workArea + data->m_serializedDataOffsets[2]);

	work->m_value0 = init;
	work->m_value2 = init;
	work->m_value1 = init;
	work->m_charaObj = 0;
	work->m_context = ppvMng;
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
static void ChangeTex_AfterDrawMeshCallback(CChara::CModel* model, void* param_2, void* param_3, int meshIdx, float (*) [4])
{
	ChangeTexWork* work = (ChangeTexWork*)param_2;
	pppChangeTexUnkB* step = static_cast<pppChangeTexUnkB*>(param_3);
	ChangeTexMeshRef* meshes = ChangeTexMeshes(model);
	int displayListIdx;
	ChangeTexDisplayListCopy* displayListPtr;
	int drawTevBits;
	int fullTevBits;
	GXColor** meshColorArrays;
	GXColor* meshColorArray;
	ChangeTexMeshData* meshData;
	ChangeTexDisplayList* displayList;

	if (step->m_payload[0] != 0) {
		meshColorArrays = work->m_meshColorArrays;
		CTexture* texture = work->m_texture;
		meshData = meshes[meshIdx].m_data;
		displayList = meshData->m_displayLists;
		if (meshColorArrays != 0) {
			meshColorArray = meshColorArrays[meshIdx];
			if (meshColorArray != 0) {
				MaterialMan.SetChangeTexReflectionArray(meshData->m_normals);
				GXSetArray((GXAttr)0xb, meshColorArray, 4);
				*(int*)(MaterialManRaw() + 0xD0) = (int)texture + 0x28;
				drawTevBits = 0xACE0F;
				fullTevBits = drawTevBits | 0x1000;
				MaterialMan.SetChangeTexReflectionTexture(&texture->m_texObj);
				displayListIdx = meshData->m_displayListCount - 1;
				while (displayListIdx >= 0) {
					MaterialMan.SetChangeTexReflectionState(drawTevBits, fullTevBits);
					MaterialMan.SetMaterial(model->m_data->m_materialSet, displayList->m_material, 0, (_GXTevScale)0);
					displayListPtr = work->m_displayListArrays[meshIdx][displayListIdx];
					GXCallDisplayList(displayListPtr->m_data, displayListPtr->m_size);
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
static void ChangeTex_DrawMeshDLCallback(CChara::CModel* model, void* param_2, void* param_3, int param_4, int param_5, float (*param_6) [4])
{
	ChangeTexWork* work = (ChangeTexWork*)param_2;
	pppChangeTexUnkB* step = static_cast<pppChangeTexUnkB*>(param_3);
	CTexture* texture = work->m_texture;
	ChangeTexMeshRef* meshes = ChangeTexMeshes(model);
	ChangeTexMeshData* meshData = meshes[param_4].m_data;
	ChangeTexDisplayList* displayList = meshData->m_displayLists + param_5;

	if (step->m_payload[0] == 0) {
		int drawTevBits = 0xACE0F;
		int fullTevBits = drawTevBits | 0x1000;
		MaterialMan.SetChangeTexReflectionState(&texture->m_texObj, drawTevBits, fullTevBits);
	}

	MaterialMan.SetMaterial(model->m_data->m_materialSet, displayList->m_material, 0, (_GXTevScale)0);
	GXCallDisplayList(displayList->m_data, displayList->m_size);
}
