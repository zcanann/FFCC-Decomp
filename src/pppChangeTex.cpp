#include "ffcc/pppChangeTex.h"
#include "ffcc/gobject.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/pppChangeTexCommon.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/textureman.h"
#include "ffcc/util.h"
#include "dolphin/gx.h"
#include <string.h>
#include <dolphin/os/OSCache.h>

STATIC_ASSERT(offsetof(ChangeTexMeshData, m_vertexCount) == 0x14);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_normals) == 0x20);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_displayListCount) == 0x4C);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_displayLists) == 0x50);
STATIC_ASSERT(offsetof(ChangeTexMeshRef, m_workPositions) == 0xC);
STATIC_ASSERT(offsetof(ChangeTexDataOffsets, m_colorBlockOffset) == 0x4);
STATIC_ASSERT(offsetof(ChangeTexDataOffsets, m_workOffset) == 0x8);
STATIC_ASSERT(sizeof(ChangeTexWork) == 0x48);
STATIC_ASSERT(offsetof(ChangeTexWork, m_meshColorArrays) == 0x0C);
STATIC_ASSERT(offsetof(ChangeTexWork, m_displayListArrays) == 0x10);
STATIC_ASSERT(offsetof(ChangeTexWork, m_charaObj) == 0x18);
STATIC_ASSERT(offsetof(ChangeTexWork, m_texture) == 0x1C);
STATIC_ASSERT(offsetof(ChangeTexWork, m_context) == 0x24);
STATIC_ASSERT(offsetof(ChangeTexWork, m_bboxMin) == 0x28);
STATIC_ASSERT(offsetof(ChangeTexWork, m_bboxMax) == 0x38);
STATIC_ASSERT(offsetof(ChangeTexWork, m_cachedValue) == 0x44);
STATIC_ASSERT(sizeof(ChangeTexDisplayListCopy) == 0x8);

static const char s_pppChangeTex_cpp[] = "pppChangeTex.cpp";

static void ChangeTex_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
static void ChangeTex_AfterDrawMeshCallback(CChara::CModel*, void*, void*, int, float (*)[4]);

static inline ChangeTexDataOffsets* GetChangeTexDataOffsets(_pppCtrlTable* data)
{
	return reinterpret_cast<ChangeTexDataOffsets*>(data->m_serializedDataOffsets);
}

static inline void SetChangeTexModelCallbacks(CChara::CModel* model, ChangeTexWork* work, ChangeTexStep* step)
{
	model->SetCallbackContext(work, step);
	model->SetDrawMeshDLCallback(ChangeTex_DrawMeshDLCallback);
	model->SetAfterDrawMeshCallback(ChangeTex_AfterDrawMeshCallback);
}

static inline ChangeTexWork* GetChangeTexWork(pppChangeTex* changeTex, _pppCtrlTable* data)
{
	return reinterpret_cast<ChangeTexWork*>(changeTex->m_workArea + GetChangeTexDataOffsets(data)->m_workOffset);
}

static inline VColor* GetChangeTexColorBlock(pppChangeTex* changeTex, _pppCtrlTable* data)
{
	return reinterpret_cast<VColor*>(
	    changeTex->m_workArea + GetChangeTexDataOffsets(data)->m_colorBlockOffset);
}

/*
 * --INFO--
 * PAL Address: 0x8013ef94
 * PAL Size: 100b
 * EN Address: 0x8013E228
 * EN Size: 100b
 * JP Address: 0x8013AE44
 * JP Size: 100b
 */
void pppRenderChangeTex(pppChangeTex*, ChangeTexStep* step, _pppCtrlTable*)
{
	if (step->m_dataValIndex != 0xffff) {
		_pppEnvSt* env = ppvEnv;
		CMapMesh* mapMesh = env->m_mapMeshPtr[step->m_dataValIndex];
		int textureIndex = 0;
		mapMesh->GetTexture(env->m_materialSetPtr, textureIndex);
		_GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
		pppInitBlendMode();
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013eff8
 * PAL Size: 1292b
 * EN Address: 0x8013E28C
 * EN Size: 1292b
 * JP Address: 0x8013AEA8
 * JP Size: 1292b
 */
void pppFrameChangeTex(pppChangeTex* changeTex, ChangeTexStep* step, _pppCtrlTable* data)
{
	ChangeTexWork* work;
	VColor* colorBlock;
	CCharaPcs::CHandle* handle0;
	CChara::CModel* model0;
	CCharaPcs::CHandle* handle1;
	CCharaPcs::CHandle* handle2;
	CChara::CModel* model1;
	CChara::CModel* model2;
	CTexture* texture;
	GXColor** colorArray;
	unsigned int meshIdx;
	ChangeTexMeshRef* meshList;
	ChangeTexMeshData* meshData;
	ChangeTexDisplayList* dlInfo;
	ChangeTexDisplayListCopy** dlEntry;
	int dlIdx;
	ChangeTexDisplayListCopy* dlPair;
	float currentValue;
	short splitY;
	double alphaBase;
	GXColor* colors;
	unsigned int vertCount;
	unsigned int v;

	if (ppvUserStopPartF != 0) {
		return;
	}

	work = GetChangeTexWork(changeTex, data);
	colorBlock = GetChangeTexColorBlock(changeTex, data);
	handle0 = GetCharaHandlePtr(ppvMng->m_owner, 0);
	model0 = GetCharaModelPtr(handle0);

	CalcGraphValue(
	    changeTex, step->m_graphId, work->m_value0, work->m_value1, work->m_value2, step->m_initWOrk,
	    step->m_stepValue, step->m_arg3);

	work->m_charaObj = ppvMng->m_owner;
	work->m_context = ppvEnv;
	SetChangeTexModelCallbacks(model0, work, step);

	work->m_texture = GetTextureFromRSD(step->m_dataValIndex, ppvEnv);

	handle1 = GetCharaHandlePtr(work->m_charaObj, 1);
	handle2 = GetCharaHandlePtr(work->m_charaObj, 2);

	if (handle1 != 0) {
		model1 = GetCharaModelPtr(handle1);
		if (model1 != 0) {
			SetChangeTexModelCallbacks(model1, work, step);
		}
	}

	if (handle2 != 0) {
		model2 = GetCharaModelPtr(handle2);
		if (model2 != 0) {
			SetChangeTexModelCallbacks(model2, work, step);
		}
	}

	if (step->m_changeTex.m_mode == 0) {
		return;
	}

	texture = GetTextureFromRSD(step->m_dataValIndex, ppvEnv);
	if (texture == 0) {
		return;
	}
	work->m_texture = texture;

	meshList = model0->GetMesh();
	if ((work->m_meshColorArrays == 0) && (work->m_displayListArrays == 0)) {
		work->m_cachedValue = -10000.0f;
		work->m_meshColorArrays = static_cast<GXColor**>(pppMemAlloc(
		    model0->GetRefData()->m_meshCount * sizeof(GXColor*), ppvEnv->m_stagePtr,
		    const_cast<char*>(s_pppChangeTex_cpp), 0x163));
		work->m_displayListArrays = static_cast<ChangeTexDisplayListCopy***>(pppMemAlloc(
		    model0->GetRefData()->m_meshCount * sizeof(ChangeTexDisplayListCopy**), ppvEnv->m_stagePtr,
		    const_cast<char*>(s_pppChangeTex_cpp), 0x166));

		colorArray = work->m_meshColorArrays;
		for (meshIdx = 0; meshIdx < model0->GetRefData()->m_meshCount; meshIdx++, meshList++) {
			meshData = meshList->m_data;
			if (strcmp(meshData->m_name, "obj") == 0) {
				gUtil.CalcBoundaryBoxQuantized(&work->m_bboxMin, &work->m_bboxMax, meshList->GetVertex(),
				    meshData->m_vertexCount, model0->m_data->m_posQuant);
			}

			work->m_displayListArrays[meshIdx] = static_cast<ChangeTexDisplayListCopy**>(
			    pppMemAlloc(meshList->m_data->m_displayListCount * sizeof(ChangeTexDisplayListCopy*), ppvEnv->m_stagePtr,
			                const_cast<char*>(s_pppChangeTex_cpp), 0x181));

			dlIdx = meshList->m_data->m_displayListCount - 1;
			dlInfo = meshList->m_data->m_displayLists;
			dlEntry = &work->m_displayListArrays[meshIdx][dlIdx];
			for (; dlIdx >= 0; dlIdx--, dlInfo++) {
				dlPair = static_cast<ChangeTexDisplayListCopy*>(
				    pppMemAlloc(sizeof(ChangeTexDisplayListCopy), ppvEnv->m_stagePtr,
				                const_cast<char*>(s_pppChangeTex_cpp), 0x18B));
				*dlEntry = dlPair;
				(*dlEntry)->m_size = dlInfo->m_size;
				(*dlEntry)->m_data = pppMemAlloc(
				    dlInfo->m_size, ppvEnv->m_stagePtr, const_cast<char*>(s_pppChangeTex_cpp), 0x18D);
				memcpy((*dlEntry)->m_data, dlInfo->m_data, dlInfo->m_size);
				gUtil.ReWriteDisplayList((*dlEntry)->m_data, (unsigned long)dlInfo->m_size, 1);
				dlEntry--;
			}

			*colorArray = static_cast<GXColor*>(
			    pppMemAlloc(meshList->m_data->m_vertexCount * sizeof(GXColor), ppvEnv->m_stagePtr,
			                const_cast<char*>(s_pppChangeTex_cpp), 0x196));
			memset(*colorArray, 0, meshList->m_data->m_vertexCount * sizeof(GXColor));

			colorArray++;
		}
	}

	if (ppvIsLoopCalc != 0) {
		return;
	}

	currentValue = work->m_value0 * (work->m_bboxMax.y - work->m_bboxMin.y) + work->m_bboxMin.y;

	splitY = (short)(int)(currentValue * (float)(1 << model0->m_data->m_posQuant));
	if (work->m_cachedValue == currentValue) {
		return;
	}

	work->m_cachedValue = currentValue;

	alphaBase = (double)(255.0f * ((float)colorBlock->m_color.rgba[3] / 255.0f));

	meshList = model0->GetMesh();
	for (unsigned int i = 0; i < model0->GetRefData()->m_meshCount; i++, meshList++) {
		colors = work->m_meshColorArrays[i];
		for (v = 0; (vertCount = meshList->m_data->m_vertexCount, v < vertCount); v++) {
			if (step->m_changeTex.m_mode == 1) {
				if (meshList->GetVertex()[v].y < splitY) {
					colors[v].a = (u8)(int)alphaBase;
				} else {
					colors[v].a = 0;
				}
			} else if (step->m_changeTex.m_mode == 2) {
				if (meshList->GetVertex()[v].y > splitY) {
					colors[v].a = (u8)(int)alphaBase;
				} else {
					colors[v].a = 0;
				}
			}
		}

		DCFlushRange(colors, vertCount * sizeof(GXColor));
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013f504
 * PAL Size: 540b
 * EN Address: 0x8013E798
 * EN Size: 540b
 * JP Address: 0x8013B3B4
 * JP Size: 540b
 */
void pppDestructChangeTex(pppChangeTex* changeTex, _pppCtrlTable* data)
{
	GXColor** colorArrays;
	ChangeTexDisplayListCopy*** dlArrays;
	ChangeTexWork* work;
	CCharaPcs::CHandle* handle2;
	CCharaPcs::CHandle* handle1;
	CChara::CModel* model;
	CChara::CModel* model1;
	CChara::CModel* model2;
	ChangeTexMeshRef* meshList;
	GXColor** colorArraysBase;
	ChangeTexDisplayListCopy*** dlArraysBase;
	unsigned int i;
	ChangeTexMeshData* meshData;
	CCharaPcs::CHandle* handle0;
	ChangeTexDisplayListCopy** dlEntries;
	unsigned int j;

	Graphic._WaitDrawDone(const_cast<char*>(s_pppChangeTex_cpp), 0x9d);
	work = GetChangeTexWork(changeTex, data);
	handle0 = GetCharaHandlePtr(work->m_charaObj, 0);
	handle1 = GetCharaHandlePtr(work->m_charaObj, 1);
	handle2 = GetCharaHandlePtr(work->m_charaObj, 2);
	model = 0;

	if (handle0 != 0) {
		model = GetCharaModelPtr(handle0);
		ClearChangeTexModelCallbacks(model);
	}
	if (handle1 != 0) {
		model1 = GetCharaModelPtr(handle1);
		if (model1 != 0) {
			ClearChangeTexModelCallbacks(model1);
		}
	}
	if (handle2 != 0) {
		model2 = GetCharaModelPtr(handle2);
		if (model2 != 0) {
			ClearChangeTexModelCallbacks(model2);
		}
	}

	dlArrays = work->m_displayListArrays;
	if (dlArrays != 0) {
		colorArrays = work->m_meshColorArrays;
		if (colorArrays != 0) {
			goto freeArrays;
		}
	}
	return;

freeArrays:
	meshList = model->GetMesh();
	colorArraysBase = colorArrays;
	dlArraysBase = dlArrays;
	for (i = 0; i < model->GetRefData()->m_meshCount; i++, meshList++) {
		meshData = meshList->m_data;
		dlEntries = *dlArrays;
		for (j = 0; j < meshData->m_displayListCount; j++) {
			if ((*dlEntries)->m_data != 0) {
				pppMemFree((*dlEntries)->m_data);
				(*dlEntries)->m_data = 0;
			}
			if (*dlEntries != 0) {
				pppMemFree(*dlEntries);
				*dlEntries = 0;
			}
			dlEntries++;
		}

		if (*dlArrays != 0) {
			pppMemFree(*dlArrays);
			*dlArrays = 0;
		}
		if (*colorArrays != 0) {
			pppMemFree(*colorArrays);
			*colorArrays = 0;
		}

		dlArrays++;
		colorArrays++;
	}

	if (dlArraysBase != 0) {
		pppMemFree(dlArraysBase);
	}
	if (colorArraysBase != 0) {
		pppMemFree(colorArraysBase);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013f720
 * PAL Size: 36b
 * EN Address: 0x8013E9B4
 * EN Size: 36b
 * JP Address: 0x8013B5D0
 * JP Size: 40b
 */
void pppConstruct2ChangeTex(pppChangeTex* changeTex, _pppCtrlTable* data)
{
	ChangeTexWork* work = GetChangeTexWork(changeTex, data);
	float init = 0.0f;

	work->m_value0 = init;
	work->m_value1 = work->m_value2 = init;
}

/*
 * --INFO--
 * PAL Address: 0x8013f744
 * PAL Size: 64b
 * EN Address: 0x8013E9D8
 * EN Size: 64b
 * JP Address: 0x8013B5F8
 * JP Size: 68b
 */
void pppConstructChangeTex(pppChangeTex* changeTex, _pppCtrlTable* data)
{
	float init = 0.0f;
	ChangeTexWork* work = GetChangeTexWork(changeTex, data);

	work->m_value0 = init;
	work->m_value1 = work->m_value2 = init;
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
 * EN Address: 0x8013EA18
 * EN Size: 344b
 * JP Address: 0x8013B63C
 * JP Size: 344b
 */
static void ChangeTex_AfterDrawMeshCallback(CChara::CModel* model, void* callbackContext, void* callbackParam, int meshIdx, float (*) [4])
{
	ChangeTexWork* work = static_cast<ChangeTexWork*>(callbackContext);
	ChangeTexStep* step = static_cast<ChangeTexStep*>(callbackParam);
	ChangeTexMeshRef* meshes = model->GetMesh();

	if (step->m_changeTex.m_mode != 0) {
		GXColor** meshColorArrays = work->m_meshColorArrays;
		CTexture* texture = work->m_texture;
		ChangeTexMeshData* meshData = meshes[meshIdx].m_data;
		ChangeTexDisplayList* displayList = meshData->m_displayLists;
		if (meshColorArrays != 0) {
			GXColor* meshColorArray = meshColorArrays[meshIdx];
			if (meshColorArray != 0) {
				MaterialMan.SetNRM(meshData->m_normals);
				GXSetArray(GX_VA_CLR0, meshColorArray, sizeof(GXColor));
				MaterialMan.SetStoneTexObj(texture->GetTexObj());
				int displayListIdx = meshData->m_displayListCount - 1;
				while (displayListIdx >= 0) {
					ChangeTexDisplayListCopy** displayListCopies = work->m_displayListArrays[meshIdx];
					MaterialMan.InitEnv();
					MaterialMan.SetTevBit(static_cast<CMaterialMan::TEV_BIT>(0x1000));
					MaterialMan.LockEnv();
					MaterialMan.SetMaterial(model->GetRefData()->m_materialSet, displayList->m_material, 0, GX_CS_SCALE_1);
					ChangeTexDisplayListCopy* displayListPtr = displayListCopies[displayListIdx];
					GXCallDisplayList(displayListPtr->m_data, displayListPtr->m_size);
					displayListIdx--;
					displayList++;
				}
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013f8dc
 * PAL Size: 244b
 * EN Address: 0x8013EB70
 * EN Size: 244b
 * JP Address: 0x8013B794
 * JP Size: 244b
 */
static void ChangeTex_DrawMeshDLCallback(CChara::CModel* model, void* callbackContext, void* callbackParam, int meshIdx, int displayListIdx, float (*) [4])
{
	ChangeTexWork* work = static_cast<ChangeTexWork*>(callbackContext);
	ChangeTexStep* step = static_cast<ChangeTexStep*>(callbackParam);
	ChangeTexMeshRef* meshes = model->GetMesh();
	meshes += meshIdx;
	ChangeTexMeshData* meshData = meshes->m_data;
	ChangeTexDisplayList* displayList = meshData->m_displayLists;
	displayList += displayListIdx;
	CTexture* texture = work->m_texture;

	if (step->m_changeTex.m_mode == 0) {
		MaterialMan.InitEnv();
		MaterialMan.SetTevBit(static_cast<CMaterialMan::TEV_BIT>(0x1000));
		MaterialMan.SetStoneTexObj(texture->GetTexObj());
		MaterialMan.LockEnv();
	}

	MaterialMan.SetMaterial(model->GetRefData()->m_materialSet, displayList->m_material, 0, GX_CS_SCALE_1);
	GXCallDisplayList(displayList->m_data, displayList->m_size);
}
