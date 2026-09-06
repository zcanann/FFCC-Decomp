#include "ffcc/pppYmChangeTex.h"
#include "ffcc/gobject.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/mapmesh.h"
#include "ffcc/materialman.h"
#include "ffcc/pppChangeTexCommon.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/textureman.h"
#include "ffcc/util.h"
#include <string.h>
#include <dolphin/gx.h>
#include <dolphin/os/OSCache.h>
#include "ffcc/ppp_linkage.h"

static const char s_pppYmChangeTex_cpp[] = "pppYmChangeTex.cpp";
static const float kPppYmChangeTexRampStart = 2.0f;
static const float kPppYmChangeTexRampScale = 0.5f;
static const float kPppYmChangeTexRampStep = 0.25f;
static const double kPppYmChangeTexIntToDoubleBias = 4503601774854144.0;
static const float kPppYmChangeTexInitZero = 0.0f;

STATIC_ASSERT(offsetof(ChangeTexMeshData, m_vertexCount) == 0x14);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_normals) == 0x20);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_displayListCount) == 0x4C);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_displayLists) == 0x50);
STATIC_ASSERT(offsetof(ChangeTexMeshRef, m_workPositions) == 0xC);
STATIC_ASSERT(offsetof(ChangeTexDataOffsets, m_colorBlockOffset) == 0x4);
STATIC_ASSERT(offsetof(ChangeTexDataOffsets, m_workOffset) == 0x8);
STATIC_ASSERT(offsetof(CChara::CModel::CRefData, m_meshCount) == 0xC);
STATIC_ASSERT(offsetof(CChara::CModel::CRefData, m_materialSet) == 0x24);
STATIC_ASSERT(offsetof(CChara::CModel::CRefData, m_posQuant) == 0x34);
STATIC_ASSERT(sizeof(pppYmChangeTexState) == 0x28);
STATIC_ASSERT(offsetof(pppYmChangeTexState, m_meshColorArrays) == 0x0C);
STATIC_ASSERT(offsetof(pppYmChangeTexState, m_displayListArrays) == 0x10);
STATIC_ASSERT(offsetof(pppYmChangeTexState, m_charaObj) == 0x18);
STATIC_ASSERT(offsetof(pppYmChangeTexState, m_texture) == 0x1C);
STATIC_ASSERT(offsetof(pppYmChangeTexState, m_context) == 0x24);
STATIC_ASSERT(sizeof(ChangeTexDisplayListCopy) == 0x8);
STATIC_ASSERT(sizeof(GXColor) == 0x4);

static inline float ChangeTexConst(const float& value) { return *reinterpret_cast<const float*>(&value); }

static inline MtxPtr ChangeTexModelMtx(CChara::CModel* model)
{
	return model->m_drawMtx;
}

static inline ChangeTexDataOffsets* GetChangeTexDataOffsets(_pppCtrlTable* data)
{
	return reinterpret_cast<ChangeTexDataOffsets*>(data->m_serializedDataOffsets);
}

static inline pppYmChangeTexState* GetChangeTexState(pppYmChangeTex* ymChangeTex, _pppCtrlTable* data)
{
	return reinterpret_cast<pppYmChangeTexState*>(
	    ymChangeTex->m_workArea + GetChangeTexDataOffsets(data)->m_workOffset);
}

void ChangeTex_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
void ChangeTex_AfterDrawMeshCallback(CChara::CModel*, void*, void*, int, float (*)[4]);

static inline void SetChangeTexModelCallbacks(CChara::CModel* model, pppYmChangeTexState* state, pppYmChangeTexStep* step)
{
	model->SetCallbackContext(state, step);
	model->SetDrawMeshDLCallback(ChangeTex_DrawMeshDLCallback);
	model->SetAfterDrawMeshCallback(ChangeTex_AfterDrawMeshCallback);
}

/*
 * --INFO--
 * PAL Address: 0x800d3854
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmChangeTex(pppYmChangeTex*, pppYmChangeTexStep* step, _pppCtrlTable*)
{
	int textureIndex;
	if (step->m_dataValIndex != 0xffff) {
		_pppEnvSt* env = ppvEnv;
		CMapMesh* mapMesh = env->m_mapMeshPtr[step->m_dataValIndex];
		textureIndex = 0;
		mapMesh->GetTexture(env->m_materialSetPtr, textureIndex);
		_GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800d38b4
 * PAL Size: 1264b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmChangeTex(pppYmChangeTex* ymChangeTex, pppYmChangeTexStep* step, _pppCtrlTable* data)
{
	CCharaPcs::CHandle* handle0;
	CCharaPcs::CHandle* handle1;
	CCharaPcs::CHandle* handle2;
	CChara::CModel* model0;
	CChara::CModel* model;
	CTexture* texture;
	ChangeTexMeshRef* meshList;
	ChangeTexMeshRef* curMesh;
	Mtx modelMtx;
	pppYmChangeTexState* state;
	int frame;
	short frameShort;
	unsigned char fallbackAlpha;
	u8 negativeRamp;

	if (ppvUserStopPartF != 0) {
		return;
	}

	state = GetChangeTexState(ymChangeTex, data);
	handle0 = GetCharaHandlePtr(ppvMng->m_owner, 0);
	model0 = GetCharaModelPtr(handle0);

	state->m_charaObj = ppvMng->m_owner;
	state->m_context = ppvEnv;
	SetChangeTexModelCallbacks(model0, state, step);
	state->m_texture = GetTextureFromRSD(step->m_dataValIndex, ppvEnv);

	handle1 = GetCharaHandlePtr(state->m_charaObj, 1);
	handle2 = GetCharaHandlePtr(state->m_charaObj, 2);
	if ((handle1 != 0) && ((model = GetCharaModelPtr(handle1)), model != 0)) {
		SetChangeTexModelCallbacks(model, state, step);
	}

	if ((handle2 != 0) && ((model = GetCharaModelPtr(handle2)), model != 0)) {
		SetChangeTexModelCallbacks(model, state, step);
	}

	if (step->m_changeTex.m_mode == 0) {
		return;
	}

	state->m_value1 = state->m_value1 + state->m_value2;
	state->m_value0 = state->m_value0 + state->m_value1;
	if (step->m_graphId == ymChangeTex->m_graphId) {
		state->m_value0 = state->m_value0 + step->m_initWOrk;
		state->m_value1 = state->m_value1 + step->m_stepValue;
		state->m_value2 = state->m_value2 + step->m_arg3;
	}

	texture = GetTextureFromRSD(step->m_dataValIndex, ppvEnv);
	if (texture == 0) {
		return;
	}
	state->m_texture = texture;

	meshList = ChangeTexMeshes(model0);
	if ((state->m_meshColorArrays == 0) && (state->m_displayListArrays == 0)) {
		state->m_meshColorArrays = (GXColor**)pppMemAlloc(
		    model0->m_data->m_meshCount << 2, ppvEnv->m_stagePtr,
		    const_cast<char*>(s_pppYmChangeTex_cpp), 0x15D);
		state->m_displayListArrays = (ChangeTexDisplayListCopy***)pppMemAlloc(
		    model0->m_data->m_meshCount << 2, ppvEnv->m_stagePtr,
		    const_cast<char*>(s_pppYmChangeTex_cpp), 0x160);

		GXColor** meshColorArrays = state->m_meshColorArrays;
		for (unsigned int meshIdx = 0; meshIdx < model0->m_data->m_meshCount; meshIdx++) {
			state->m_displayListArrays[meshIdx] = static_cast<ChangeTexDisplayListCopy**>(
			    pppMemAlloc(meshList->m_data->m_displayListCount * sizeof(ChangeTexDisplayListCopy*),
			                ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmChangeTex_cpp), 0x168));

			int dlIdx = meshList->m_data->m_displayListCount - 1;
			ChangeTexDisplayList* dlInfo = meshList->m_data->m_displayLists;
			ChangeTexDisplayListCopy** dlEntry = &state->m_displayListArrays[meshIdx][dlIdx];
			for (; dlIdx >= 0; dlIdx = dlIdx - 1, dlInfo = dlInfo + 1) {
				ChangeTexDisplayListCopy* dlPair = static_cast<ChangeTexDisplayListCopy*>(
				    pppMemAlloc(sizeof(ChangeTexDisplayListCopy), ppvEnv->m_stagePtr,
				                const_cast<char*>(s_pppYmChangeTex_cpp), 0x172));
				*dlEntry = dlPair;
				(*dlEntry)->m_size = dlInfo->m_size;
				(*dlEntry)->m_data = pppMemAlloc(
				    dlInfo->m_size, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmChangeTex_cpp), 0x174);
				memcpy((*dlEntry)->m_data, dlInfo->m_data, dlInfo->m_size);
				gUtil.ReWriteDisplayList((*dlEntry)->m_data, (unsigned long)dlInfo->m_size, 1);
				DCFlushRange((*dlEntry)->m_data, (unsigned long)dlInfo->m_size);
				dlEntry = dlEntry - 1;
			}

			*meshColorArrays = static_cast<GXColor*>(
			    pppMemAlloc(meshList->m_data->m_vertexCount * sizeof(GXColor), ppvEnv->m_stagePtr,
			                const_cast<char*>(s_pppYmChangeTex_cpp), 0x17F));
			memset(*meshColorArrays, 0xFF, meshList->m_data->m_vertexCount * sizeof(GXColor));
			meshColorArrays = meshColorArrays + 1;
			meshList++;
		}
	}

	curMesh = ChangeTexMeshes(model0);
	frame = (int)(state->m_value0 * (float)(1 << model0->m_data->m_posQuant));
	frameShort = (short)frame;
	PSMTXCopy(ChangeTexModelMtx(model0), modelMtx);

	if ((step->m_changeTex.m_mode == 2) || (step->m_changeTex.m_mode == 1)) {
		fallbackAlpha = 0;
		negativeRamp = 0xFF;
	} else {
		fallbackAlpha = 0xFF;
		negativeRamp = 0;
	}

	for (unsigned int meshIdx = 0; meshIdx < model0->m_data->m_meshCount; meshIdx++) {
		GXColor* vertColors = state->m_meshColorArrays[meshIdx];
		for (unsigned int v = 0; v < curMesh->m_data->m_vertexCount; v++) {
			int delta = static_cast<int>(frameShort) - static_cast<int>(curMesh->m_workPositions[v].y);
			if (delta >= 0) {
				int level = 0;
				float threshold = kPppYmChangeTexRampStart;
				for (int tries = 7; tries != 0; tries--) {
					if ((float)delta > threshold * kPppYmChangeTexRampScale) {
						if (negativeRamp == 0xFF) {
							vertColors->a = negativeRamp - (level << 4);
						} else {
							vertColors->a = (u8)(level << 4);
						}
						break;
					}
					threshold = threshold - kPppYmChangeTexRampStep;
					level = level + 1;
				}
			} else {
				vertColors->a = fallbackAlpha;
			}

			vertColors++;
		}

		curMesh++;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800d3da4
 * PAL Size: 500b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmChangeTex(pppYmChangeTex* ymChangeTex, _pppCtrlTable* data)
{
	pppYmChangeTexState* state = GetChangeTexState(ymChangeTex, data);
	CCharaPcs::CHandle* handle0 = GetCharaHandlePtr(state->m_charaObj, 0);
	CCharaPcs::CHandle* handle1 = GetCharaHandlePtr(state->m_charaObj, 1);
	CCharaPcs::CHandle* handle2 = GetCharaHandlePtr(state->m_charaObj, 2);
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

	ChangeTexDisplayListCopy*** stageArray = state->m_displayListArrays;
	GXColor** meshArray;
	if (stageArray != 0) {
		meshArray = state->m_meshColorArrays;
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
 * PAL Address: 0x800d3f98
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmChangeTex(pppYmChangeTex* ymChangeTex, _pppCtrlTable* data)
{
	float init = kPppYmChangeTexInitZero;
	pppYmChangeTexState* state = GetChangeTexState(ymChangeTex, data);

	state->m_value0 = init;
	state->m_value2 = init;
	state->m_value1 = init;
	state->m_charaObj = 0;
	state->m_context = ppvMng;
	state->m_texture = 0;
	state->m_meshColorArrays = 0;
	state->m_displayListArrays = 0;
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
#pragma push
#pragma opt_strength_reduction off
void ChangeTex_AfterDrawMeshCallback(CChara::CModel* model, void* param_2, void* param_3, int meshIdx, float (*) [4])
{
	pppYmChangeTexState* state = (pppYmChangeTexState*)param_2;
	pppYmChangeTexStep* step = (pppYmChangeTexStep*)param_3;
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
		meshColorArrays = state->m_meshColorArrays;
		CTexture* texture = state->m_texture;
		meshData = meshes[meshIdx].m_data;
		displayList = meshData->m_displayLists;
		if (meshColorArrays != 0) {
			meshColorArray = meshColorArrays[meshIdx];
			if (meshColorArray != 0) {
				MaterialMan.SetGeometryArraySource(meshData->m_normals);
				GXSetArray((GXAttr)0xb, meshColorArray, 4);

				if ((step->m_changeTex.m_mode == 2) || (step->m_changeTex.m_mode == 3)) {
					MaterialMan.SetChangeTexReflectionTexture(0);
				} else {
					MaterialMan.SetChangeTexReflectionTexture(&texture->m_texObj);
				}

				drawTevBits = 0xACE0F;
				fullTevBits = 0xADE0F;
				displayListIdx = meshData->m_displayListCount - 1;
				while (displayListIdx >= 0) {
					ChangeTexDisplayListCopy** displayListCopies = state->m_displayListArrays[meshIdx];
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
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x800d4164
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void ChangeTex_DrawMeshDLCallback(CChara::CModel* model, void* param_2, void* param_3, int meshIdx, int displayListIdx, float (*) [4])
{
	pppYmChangeTexState* state = (pppYmChangeTexState*)param_2;
	pppYmChangeTexStep* step = (pppYmChangeTexStep*)param_3;
	ChangeTexMeshRef* meshes = ChangeTexMeshes(model);
	meshes += meshIdx;
	ChangeTexMeshData* meshData = meshes->m_data;
	ChangeTexDisplayList* displayList = meshData->m_displayLists;
	displayList += displayListIdx;
	CTexture* texture = state->m_texture;

	if (step->m_changeTex.m_mode == 0) {
		unsigned int drawTevBits = 0xACE0F;
		unsigned int fullTevBits = 0xADE0F;
		MaterialMan.SetChangeTexReflectionState(
		    &texture->m_texObj, drawTevBits, fullTevBits);
	}

	MaterialMan.SetMaterial(model->m_data->m_materialSet, displayList->m_material, 0, (_GXTevScale)0);

	if ((step->m_changeTex.m_mode == 1) || (step->m_changeTex.m_mode == 0)) {
		GXCallDisplayList(displayList->m_data, displayList->m_size);
	}
}
