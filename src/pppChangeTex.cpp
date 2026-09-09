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

static inline ChangeTexColorBlock* GetChangeTexColorBlock(pppChangeTex* changeTex, _pppCtrlTable* data)
{
	return reinterpret_cast<ChangeTexColorBlock*>(
	    changeTex->m_workArea + GetChangeTexDataOffsets(data)->m_colorBlockOffset);
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
void pppRenderChangeTex(pppChangeTex*, ChangeTexStep* step, _pppCtrlTable*)
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
void pppFrameChangeTex(pppChangeTex* changeTex, ChangeTexStep* step, _pppCtrlTable* data)
{
	if (ppvUserStopPartF != 0) {
		return;
	}

	ChangeTexWork* work = GetChangeTexWork(changeTex, data);
	ChangeTexColorBlock* colorBlock = GetChangeTexColorBlock(changeTex, data);
	CCharaPcs::CHandle* handle0 = GetCharaHandlePtr(ppvMng->m_owner, 0);
	CChara::CModel* model0 = GetCharaModelPtr(handle0);

	CalcGraphValue(
	    changeTex, step->m_graphId, work->m_value0, work->m_value1, work->m_value2, step->m_initWOrk,
	    step->m_stepValue, step->m_arg3);

	work->m_charaObj = ppvMng->m_owner;
	work->m_context = ppvEnv;
	SetChangeTexModelCallbacks(model0, work, step);

	work->m_texture = GetTextureFromRSD(step->m_dataValIndex, ppvEnv);

	CCharaPcs::CHandle* handle1 = GetCharaHandlePtr(work->m_charaObj, 1);
	CCharaPcs::CHandle* handle2 = GetCharaHandlePtr(work->m_charaObj, 2);

	CChara::CModel* model;
	if ((handle1 != 0) && ((model = GetCharaModelPtr(handle1)), model != 0)) {
		SetChangeTexModelCallbacks(model, work, step);
	}

	if ((handle2 != 0) && ((model = GetCharaModelPtr(handle2)), model != 0)) {
		SetChangeTexModelCallbacks(model, work, step);
	}

	if (step->m_changeTex.m_mode == 0) {
		return;
	}

	CTexture* texture = GetTextureFromRSD(step->m_dataValIndex, ppvEnv);
	if (texture == 0) {
		return;
	}
	work->m_texture = texture;

	ChangeTexMeshRef* meshList = ChangeTexMeshes(model0);
	if ((work->m_meshColorArrays == 0) && (work->m_displayListArrays == 0)) {
		work->m_cachedValue = -10000.0f;
		work->m_meshColorArrays = (GXColor**)pppMemAlloc(
		    model0->m_data->m_meshCount << 2, ppvEnv->m_stagePtr,
		    const_cast<char*>(s_pppChangeTex_cpp), 0x163);
		work->m_displayListArrays = (ChangeTexDisplayListCopy***)pppMemAlloc(
		    model0->m_data->m_meshCount << 2, ppvEnv->m_stagePtr,
		    const_cast<char*>(s_pppChangeTex_cpp), 0x166);

		GXColor** colorArray = work->m_meshColorArrays;
		for (unsigned int meshIdx = 0; meshIdx < model0->m_data->m_meshCount; meshIdx++, meshList++) {
			ChangeTexMeshData* meshData = meshList->m_data;
			if (strcmp(meshData->m_name, "obj") == 0) {
				gUtil.CalcBoundaryBoxQuantized(&work->m_bboxMin, &work->m_bboxMax, meshList->m_workPositions,
				    meshData->m_vertexCount, model0->m_data->m_posQuant);
			}

			work->m_displayListArrays[meshIdx] = static_cast<ChangeTexDisplayListCopy**>(
			    pppMemAlloc(meshList->m_data->m_displayListCount * sizeof(ChangeTexDisplayListCopy*), ppvEnv->m_stagePtr,
			                const_cast<char*>(s_pppChangeTex_cpp), 0x181));

			int dlIdx = meshList->m_data->m_displayListCount - 1;
			ChangeTexDisplayList* dlInfo = meshList->m_data->m_displayLists;
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

	float currentValue = work->m_value0 * (work->m_bboxMax.y - work->m_bboxMin.y) + work->m_bboxMin.y;

	short splitY = (short)(int)(currentValue * (float)(1 << model0->m_data->m_posQuant));
	if (work->m_cachedValue == currentValue) {
		return;
	}

	work->m_cachedValue = currentValue;

	double alphaBase =
	    (double)(255.0f *
	             ((float)colorBlock->m_color.rgba[3] / 255.0f));

	meshList = ChangeTexMeshes(model0);
	for (unsigned int meshIdx = 0; meshIdx < model0->m_data->m_meshCount; meshIdx++, meshList++) {
		GXColor* colors = work->m_meshColorArrays[meshIdx];
		unsigned int vertCount;
		for (unsigned int v = 0; (vertCount = meshList->m_data->m_vertexCount, v < vertCount); v++) {
			if (step->m_changeTex.m_mode == 1) {
				if (meshList->m_workPositions[v].y < splitY) {
					colors[v].a = (u8)(int)alphaBase;
				} else {
					colors[v].a = 0;
				}
			} else if (step->m_changeTex.m_mode == 2) {
				if (meshList->m_workPositions[v].y > splitY) {
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructChangeTex(pppChangeTex* changeTex, _pppCtrlTable* data)
{
	Graphic._WaitDrawDone(const_cast<char*>(s_pppChangeTex_cpp), 0x9d);
	ChangeTexWork* work = GetChangeTexWork(changeTex, data);
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
				pppMemFree((*dlEntries)->m_data);
				(*dlEntries)->m_data = 0;
			}
			if (*dlEntries != 0) {
				pppMemFree(*dlEntries);
				*dlEntries = 0;
			}
			dlEntries++;
		}

		if (*stageArray != 0) {
			pppMemFree(*stageArray);
			*stageArray = 0;
		}
		if (*meshArray != 0) {
			pppMemFree(*meshArray);
			*meshArray = 0;
		}

		stageArray++;
		meshArray++;
	}

	if (stageArrayOrig != 0) {
		pppMemFree(stageArrayOrig);
	}
	if (meshArrayOrig != 0) {
		pppMemFree(meshArrayOrig);
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
void pppConstruct2ChangeTex(pppChangeTex* changeTex, _pppCtrlTable* data)
{
	ChangeTexWork* work = GetChangeTexWork(changeTex, data);
	float init = 0.0f;

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
void pppConstructChangeTex(pppChangeTex* changeTex, _pppCtrlTable* data)
{
	float init = 0.0f;
	ChangeTexWork* work = GetChangeTexWork(changeTex, data);

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
	ChangeTexWork* work = static_cast<ChangeTexWork*>(param_2);
	ChangeTexStep* step = static_cast<ChangeTexStep*>(param_3);
	ChangeTexMeshRef* meshes = ChangeTexMeshes(model);
	int displayListIdx;
	ChangeTexDisplayListCopy* displayListPtr;
	unsigned int drawTevBits;
	unsigned int fullTevBits;
	GXColor** meshColorArrays;
	GXColor* meshColorArray;
	ChangeTexMeshData* meshData;
	ChangeTexDisplayList* displayList;

	if (step->m_changeTex.m_mode != 0) {
		meshColorArrays = work->m_meshColorArrays;
		CTexture* texture = work->m_texture;
		meshData = meshes[meshIdx].m_data;
		displayList = meshData->m_displayLists;
		if (meshColorArrays != 0) {
			meshColorArray = meshColorArrays[meshIdx];
			if (meshColorArray != 0) {
				MaterialMan.SetGeometryArraySource(meshData->m_normals);
				GXSetArray((GXAttr)0xb, meshColorArray, 4);
				MaterialMan.SetChangeTexReflectionTexture(&texture->m_texObj);
				drawTevBits = 0xACE0F;
				fullTevBits = drawTevBits;
				fullTevBits |= 0x1000;
				displayListIdx = meshData->m_displayListCount - 1;
				while (displayListIdx >= 0) {
					ChangeTexDisplayListCopy** displayListCopies = work->m_displayListArrays[meshIdx];
					MaterialMan.SetChangeTexReflectionState(drawTevBits, fullTevBits);
					MaterialMan.SetMaterial(model->m_data->m_materialSet, displayList->m_material, 0, (_GXTevScale)0);
					displayListPtr = displayListCopies[displayListIdx];
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
	ChangeTexWork* work = static_cast<ChangeTexWork*>(param_2);
	ChangeTexStep* step = static_cast<ChangeTexStep*>(param_3);
	ChangeTexMeshRef* meshes = ChangeTexMeshes(model);
	meshes += param_4;
	ChangeTexMeshData* meshData = meshes->m_data;
	ChangeTexDisplayList* displayList = meshData->m_displayLists;
	displayList += param_5;
	CTexture* texture = work->m_texture;

	if (step->m_changeTex.m_mode == 0) {
		unsigned int drawTevBits = 0xACE0F;
		unsigned int fullTevBits = drawTevBits;
		fullTevBits |= 0x1000;
		MaterialMan.SetChangeTexReflectionState(
		    &texture->m_texObj, drawTevBits, fullTevBits);
	}

	MaterialMan.SetMaterial(model->m_data->m_materialSet, displayList->m_material, 0, (_GXTevScale)0);
	GXCallDisplayList(displayList->m_data, displayList->m_size);
}
