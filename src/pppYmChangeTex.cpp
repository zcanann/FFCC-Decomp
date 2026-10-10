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

static inline ChangeTexDataOffsets* GetChangeTexDataOffsets(_pppCtrlTable* data)
{
	return reinterpret_cast<ChangeTexDataOffsets*>(data->m_serializedDataOffsets);
}

static inline pppYmChangeTexState* GetChangeTexState(pppYmChangeTex* ymChangeTex, _pppCtrlTable* data)
{
	return reinterpret_cast<pppYmChangeTexState*>(
	    ymChangeTex->m_workArea + GetChangeTexDataOffsets(data)->m_workOffset);
}

static void ChangeTex_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
static void ChangeTex_AfterDrawMeshCallback(CChara::CModel*, void*, void*, int, float (*)[4]);

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
 * EN Address: 0x800D3020
 * EN Size: 96b
 * JP Address: 0x800D0C5C
 * JP Size: 96b
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
 * EN Address: 0x800D3080
 * EN Size: 1264b
 * JP Address: 0x800D0CBC
 * JP Size: 1264b
 */
void pppFrameYmChangeTex(pppYmChangeTex* ymChangeTex, pppYmChangeTexStep* step, _pppCtrlTable* data)
{
	int dlIdx;
	CChara::CModel* model;
	CCharaPcs::CHandle* handle1;
	GXColor** meshColorArrays;
	pppYmChangeTexState* state;
	ChangeTexMeshRef* meshList;
	CChara::CModel* model0;
	ChangeTexDisplayList* dlInfo;
	CCharaPcs::CHandle* handle2;
	unsigned int meshIdx;
	ChangeTexDisplayListCopy* dlPair;
	ChangeTexDisplayListCopy** dlEntry;
	CCharaPcs::CHandle* handle0;
	CTexture* texture;
	Mtx modelMtx;
	int cutoffYFixed;
	short cutoffY;
	u8 negativeRamp;
	unsigned char fallbackAlpha;

	if (ppvUserStopPartF != 0) {
		return;
	}

	state = reinterpret_cast<pppYmChangeTexState*>(ymChangeTex->m_workArea + data->m_serializedDataOffsets[2]);
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

	meshList = model0->GetMesh();
	if ((state->m_meshColorArrays == 0) && (state->m_displayListArrays == 0)) {
		state->m_meshColorArrays = (GXColor**)pppMemAlloc(
		    model0->GetRefData()->m_meshCount << 2, ppvEnv->m_stagePtr,
		    const_cast<char*>(s_pppYmChangeTex_cpp), 0x15D);
		state->m_displayListArrays = (ChangeTexDisplayListCopy***)pppMemAlloc(
		    model0->GetRefData()->m_meshCount << 2, ppvEnv->m_stagePtr,
		    const_cast<char*>(s_pppYmChangeTex_cpp), 0x160);

		meshColorArrays = state->m_meshColorArrays;
		for (meshIdx = 0; meshIdx < model0->GetRefData()->m_meshCount; meshIdx++, meshList++) {
			state->m_displayListArrays[meshIdx] = static_cast<ChangeTexDisplayListCopy**>(
			    pppMemAlloc(meshList->m_data->m_displayListCount * sizeof(ChangeTexDisplayListCopy*),
			                ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmChangeTex_cpp), 0x168));

			dlIdx = meshList->m_data->m_displayListCount - 1;
			dlInfo = meshList->m_data->m_displayLists;
			dlEntry = &state->m_displayListArrays[meshIdx][dlIdx];
			for (; dlIdx >= 0; dlIdx = dlIdx - 1, dlInfo = dlInfo + 1) {
				dlPair = static_cast<ChangeTexDisplayListCopy*>(
				    pppMemAlloc(sizeof(ChangeTexDisplayListCopy), ppvEnv->m_stagePtr,
				                const_cast<char*>(s_pppYmChangeTex_cpp), 0x172));
				*dlEntry = dlPair;
				(*dlEntry)->m_size = dlInfo->m_size;
				(*dlEntry)->m_data = pppMemAlloc(
				    dlInfo->m_size, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmChangeTex_cpp), 0x174);
				memcpy((*dlEntry)->m_data, dlInfo->m_data, dlInfo->m_size);
				Util.ReWriteDisplayList((*dlEntry)->m_data, (unsigned long)dlInfo->m_size, 1);
				DCFlushRange((*dlEntry)->m_data, (unsigned long)dlInfo->m_size);
				dlEntry = dlEntry - 1;
			}

			*meshColorArrays = static_cast<GXColor*>(
			    pppMemAlloc(meshList->m_data->m_vertexCount * sizeof(GXColor), ppvEnv->m_stagePtr,
			                const_cast<char*>(s_pppYmChangeTex_cpp), 0x17F));
			memset(*meshColorArrays, 0xFF, meshList->m_data->m_vertexCount * sizeof(GXColor));
			meshColorArrays = meshColorArrays + 1;
		}
	}

	meshList = model0->GetMesh();
	cutoffYFixed = (int)(state->m_value0 * (float)(1 << model0->m_data->m_posQuant));
	cutoffY = (short)cutoffYFixed;
	model0->GetMatrixT(modelMtx);

	if ((step->m_changeTex.m_mode == 2) || (step->m_changeTex.m_mode == 1)) {
		fallbackAlpha = 0;
		negativeRamp = 0xFF;
	} else {
		fallbackAlpha = 0xFF;
		negativeRamp = 0;
	}

	for (unsigned int i = 0; i < model0->GetRefData()->m_meshCount; i++, meshList++) {
		GXColor* vertColors = state->m_meshColorArrays[i];
		for (unsigned int v = 0; v < meshList->m_data->m_vertexCount; v++) {
			int delta = static_cast<int>(cutoffY) - static_cast<int>(meshList->GetVertex()[v].y);
			if (delta >= 0) {
				int level = 0;
				float threshold = 2.0f;
				for (int tries = 7; tries != 0; tries--) {
					if ((float)delta > threshold * 0.5f) {
						if (negativeRamp == 0xFF) {
							vertColors->a = negativeRamp - (level << 4);
						} else {
							vertColors->a = (u8)(level << 4);
						}
						break;
					}
					threshold = threshold - 0.25f;
					level = level + 1;
				}
			} else {
				vertColors->a = fallbackAlpha;
			}

			vertColors++;
		}

	}
}

/*
 * --INFO--
 * PAL Address: 0x800d3da4
 * PAL Size: 500b
 * EN Address: 0x800D3570
 * EN Size: 500b
 * JP Address: 0x800D11AC
 * JP Size: 500b
 */
void pppDestructYmChangeTex(pppYmChangeTex* ymChangeTex, _pppCtrlTable* data)
{
	GXColor** meshColorArrays;
	ChangeTexDisplayListCopy*** displayListArrays;
	pppYmChangeTexState* state;
	CCharaPcs::CHandle* handle2;
	CCharaPcs::CHandle* handle1;
	CChara::CModel* model;
	CChara::CModel* model1;
	CChara::CModel* model2;
	ChangeTexMeshRef* meshList;
	GXColor** meshColorArraysStart;
	ChangeTexDisplayListCopy*** displayListArraysStart;
	unsigned int i;
	ChangeTexMeshData* meshData;
	CCharaPcs::CHandle* handle0;
	ChangeTexDisplayListCopy** dlEntries;
	unsigned int j;

	state = GetChangeTexState(ymChangeTex, data);
	handle0 = GetCharaHandlePtr(state->m_charaObj, 0);
	handle1 = GetCharaHandlePtr(state->m_charaObj, 1);
	handle2 = GetCharaHandlePtr(state->m_charaObj, 2);
	model = 0;

	if (handle0 != 0) {
		model = GetCharaModelPtr(handle0);
		ClearChangeTexModelCallbacks(model);
	}
	if ((handle1 != 0) && ((model1 = GetCharaModelPtr(handle1)), model1 != 0)) {
		ClearChangeTexModelCallbacks(model1);
	}
	if ((handle2 != 0) && ((model2 = GetCharaModelPtr(handle2)), model2 != 0)) {
		ClearChangeTexModelCallbacks(model2);
	}

	displayListArrays = state->m_displayListArrays;
	if (displayListArrays != 0) {
		meshColorArrays = state->m_meshColorArrays;
		if (meshColorArrays != 0) {
			goto freeArrays;
		}
	}
	return;

freeArrays:
	meshList = model->GetMesh();
	meshColorArraysStart = meshColorArrays;
	displayListArraysStart = displayListArrays;
	for (i = 0; i < model->GetRefData()->m_meshCount; i++, meshList++) {
		meshData = meshList->m_data;
		dlEntries = *displayListArrays;
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

		if (*displayListArrays != 0) {
			pppMemFree(*displayListArrays);
			*displayListArrays = 0;
		}
		if (*meshColorArrays != 0) {
			pppMemFree(*meshColorArrays);
			*meshColorArrays = 0;
		}

		displayListArrays++;
		meshColorArrays++;
	}

	if (displayListArraysStart != 0) {
		pppMemFree(displayListArraysStart);
	}
	if (meshColorArraysStart != 0) {
		pppMemFree(meshColorArraysStart);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800d3f98
 * PAL Size: 64b
 * EN Address: 0x800D3764
 * EN Size: 64b
 * JP Address: 0x800D13A0
 * JP Size: 68b
 */
void pppConstructYmChangeTex(pppYmChangeTex* ymChangeTex, _pppCtrlTable* data)
{
	float init = 0.0f;
	pppYmChangeTexState* state = GetChangeTexState(ymChangeTex, data);

	state->m_value0 = init;
	state->m_value1 = state->m_value2 = init;
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
 * EN Address: 0x800D37A4
 * EN Size: 396b
 * JP Address: 0x800D13E4
 * JP Size: 396b
 */
static void ChangeTex_AfterDrawMeshCallback(CChara::CModel* model, void* callbackContext, void* callbackParam, int meshIdx, float (*) [4])
{
	pppYmChangeTexState* state = (pppYmChangeTexState*)callbackContext;
	pppYmChangeTexStep* step = (pppYmChangeTexStep*)callbackParam;
	ChangeTexMeshRef* meshes = model->GetMesh();
	ChangeTexDisplayListCopy* displayListPtr;
	GXColor** meshColorArrays;
	GXColor* meshColorArray;
	CTexture* texture;
	ChangeTexMeshData* meshData;
	ChangeTexDisplayList* displayList;
	int displayListIdx;

	if (step->m_changeTex.m_mode != 0) {
		meshColorArrays = state->m_meshColorArrays;
		texture = state->m_texture;
		meshData = meshes[meshIdx].m_data;
		displayList = meshData->m_displayLists;
		if (meshColorArrays != 0) {
			meshColorArray = meshColorArrays[meshIdx];
			if (meshColorArray != 0) {
				MaterialMan.SetNRM(meshData->m_normals);
				GXSetArray(GX_VA_CLR0, meshColorArray, sizeof(GXColor));

				if ((step->m_changeTex.m_mode == 2) || (step->m_changeTex.m_mode == 3)) {
					MaterialMan.SetStoneTexObj(0);
				} else {
					MaterialMan.SetStoneTexObj(texture->GetTexObj());
				}
				displayListIdx = meshData->m_displayListCount - 1;
				while (displayListIdx >= 0) {
					ChangeTexDisplayListCopy** displayListCopies = state->m_displayListArrays[meshIdx];
					MaterialMan.InitEnv();
					MaterialMan.SetTevBit(static_cast<CMaterialMan::TEV_BIT>(0x1000));
					MaterialMan.LockEnv();

					MaterialMan.SetMaterial(model->GetRefData()->m_materialSet, displayList->m_material, 0, GX_CS_SCALE_1);

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
 * PAL Address: 0x800d4164
 * PAL Size: 276b
 * EN Address: 0x800D3930
 * EN Size: 276b
 * JP Address: 0x800D1570
 * JP Size: 276b
 */
static void ChangeTex_DrawMeshDLCallback(CChara::CModel* model, void* callbackContext, void* callbackParam, int meshIdx, int displayListIdx, float (*) [4])
{
	pppYmChangeTexState* state = (pppYmChangeTexState*)callbackContext;
	pppYmChangeTexStep* step = (pppYmChangeTexStep*)callbackParam;
	ChangeTexMeshRef* meshes = model->GetMesh();
	meshes += meshIdx;
	ChangeTexMeshData* meshData = meshes->m_data;
	ChangeTexDisplayList* displayList = meshData->m_displayLists;
	displayList += displayListIdx;
	CTexture* texture = state->m_texture;

	if (step->m_changeTex.m_mode == 0) {
		MaterialMan.InitEnv();
		MaterialMan.SetTevBit(static_cast<CMaterialMan::TEV_BIT>(0x1000));
		MaterialMan.SetStoneTexObj(texture->GetTexObj());
		MaterialMan.LockEnv();
	}

	MaterialMan.SetMaterial(model->GetRefData()->m_materialSet, displayList->m_material, 0, GX_CS_SCALE_1);

	if ((step->m_changeTex.m_mode == 1) || (step->m_changeTex.m_mode == 0)) {
		GXCallDisplayList(displayList->m_data, displayList->m_size);
	}
}
