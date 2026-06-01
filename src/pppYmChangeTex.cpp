#include "ffcc/pppYmChangeTex.h"
#include "ffcc/gobject.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/mapmesh.h"
#include "ffcc/materialman.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/util.h"
#include <string.h>
#include <dolphin/os/OSCache.h>
#include "ffcc/ppp_linkage.h"

struct ChangeTexDisplayList {
	u32 m_size;
	void* m_data;
	u16 m_material;
	u16 _pad;
};

struct ChangeTexMeshData {
	char m_name[0x14];
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
	S16Vec* m_points;
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

struct pppYmChangeTexState {
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
};

struct ChangeTexModelRaw {
	u8 _pad0[0x68];
	Mtx m_matrix;
	u8 _pad98[0xC];
	ChangeTexModelData* m_data;
	u8 _padA8[0x4];
	ChangeTexMeshRef* m_meshes;
};

extern const char s_pppYmChangeTex_cpp[] = "pppYmChangeTex.cpp";
extern const float FLOAT_80330df8;
extern const float FLOAT_80330dfc;
extern const float FLOAT_80330e00;
extern const float kPppYmChangeTexInitZero = 0.0f;

STATIC_ASSERT(offsetof(ChangeTexModelRaw, m_data) == 0xA4);
STATIC_ASSERT(offsetof(ChangeTexModelRaw, m_meshes) == 0xAC);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_vertexCount) == 0x14);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_normals) == 0x20);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_displayListCount) == 0x4C);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_displayLists) == 0x50);
STATIC_ASSERT(offsetof(ChangeTexMeshRef, m_points) == 0xC);
STATIC_ASSERT(offsetof(ChangeTexModelData, m_meshCount) == 0xC);
STATIC_ASSERT(offsetof(ChangeTexModelData, m_materialSet) == 0x24);
STATIC_ASSERT(offsetof(ChangeTexModelData, m_frameShift) == 0x34);

static inline unsigned char* MaterialManRaw() { return reinterpret_cast<unsigned char*>(&MaterialMan); }
static inline float ChangeTexConst(const float& value) { return *reinterpret_cast<const float*>(&value); }

void ChangeTex_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
void ChangeTex_AfterDrawMeshCallback(CChara::CModel*, void*, void*, int, float (*)[4]);

static inline void SetChangeTexModelCallbacks(CChara::CModel* model, pppYmChangeTexState* state, pppYmChangeTexStep* step)
{
	model->SetCallbackContext(state, step);
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
 * PAL Address: 0x800d3854
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmChangeTex(pppYmChangeTex*, pppYmChangeTexStep* step, pppYmChangeTexData*)
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
void pppFrameYmChangeTex(pppYmChangeTex* ymChangeTex, pppYmChangeTexStep* step, pppYmChangeTexData* data)
{
	if (gPppCalcDisabled != 0) {
		return;
	}

	s32* serializedDataOffsets = data->m_serializedDataOffsets;
	pppYmChangeTexState* state = (pppYmChangeTexState*)(ymChangeTex->m_object.m_workArea + serializedDataOffsets[2]);
	CCharaPcs::CHandle* handle0 = GetCharaHandlePtr((CGObject*)ppvMng->m_owner, 0);
	CChara::CModel* model0 = GetCharaModelPtr(handle0);
	ChangeTexModelRaw* model0Raw = (ChangeTexModelRaw*)model0;

	state->m_charaObj = (CGObject*)ppvMng->m_owner;
	state->m_context = ppvEnv;
	SetChangeTexModelCallbacks(model0, state, step);
	state->m_texture = reinterpret_cast<void*>(GetTextureFromRSD(step->m_dataValIndex, ppvEnv));

	CCharaPcs::CHandle* handle1 = GetCharaHandlePtr(state->m_charaObj, 1);
	CCharaPcs::CHandle* handle2 = GetCharaHandlePtr(state->m_charaObj, 2);
	CChara::CModel* model;
	if ((handle1 != 0) && ((model = GetCharaModelPtr(handle1)), model != 0)) {
		SetChangeTexModelCallbacks(model, state, step);
	}

	if ((handle2 != 0) && ((model = GetCharaModelPtr(handle2)), model != 0)) {
		SetChangeTexModelCallbacks(model, state, step);
	}

	if (step->m_payload[0] == 0) {
		return;
	}

	state->m_value1 = state->m_value1 + state->m_value2;
	state->m_value0 = state->m_value0 + state->m_value1;
	if (step->m_graphId == ymChangeTex->m_object.m_graphId) {
		state->m_value0 = state->m_value0 + step->m_initWOrk;
		state->m_value1 = state->m_value1 + step->m_stepValue;
		state->m_value2 = state->m_value2 + step->m_arg3;
	}

	void* texObj = reinterpret_cast<void*>(GetTextureFromRSD(step->m_dataValIndex, ppvEnv));
	if (texObj == 0) {
		return;
	}
	state->m_texture = texObj;

	ChangeTexMeshRef* meshList = model0Raw->m_meshes;
	if ((state->m_meshColorArrays == 0) && (state->m_displayListArrays == 0)) {
		state->m_meshColorArrays = pppMemAlloc(
		    model0Raw->m_data->m_meshCount << 2, ppvEnv->m_stagePtr,
		    const_cast<char*>(s_pppYmChangeTex_cpp), 0x15D);
		state->m_displayListArrays = pppMemAlloc(
		    model0Raw->m_data->m_meshCount << 2, ppvEnv->m_stagePtr,
		    const_cast<char*>(s_pppYmChangeTex_cpp), 0x160);

		int* meshColorArrays = (int*)state->m_meshColorArrays;
		int arrayOffset = 0;
		for (unsigned int meshIdx = 0; meshIdx < model0Raw->m_data->m_meshCount; meshIdx++) {
			*(int*)((char*)state->m_displayListArrays + arrayOffset) = (int)pppMemAlloc(
			    meshList->m_data->m_displayListCount << 2, ppvEnv->m_stagePtr,
			    const_cast<char*>(s_pppYmChangeTex_cpp), 0x168);

			int dlIdx = meshList->m_data->m_displayListCount - 1;
			int* dlInfo = (int*)meshList->m_data->m_displayLists;
			int* dlEntry = (int*)(*(int*)((char*)state->m_displayListArrays + arrayOffset) + dlIdx * 4);
			for (; dlIdx >= 0; dlIdx = dlIdx - 1, dlInfo = dlInfo + 3) {
				int dlPair = (int)pppMemAlloc(
				    8, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmChangeTex_cpp), 0x172);
				*dlEntry = dlPair;
				*(int*)(*dlEntry + 4) = *dlInfo;
				*(int*)*dlEntry = (int)pppMemAlloc(
				    *dlInfo, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmChangeTex_cpp), 0x174);
				memcpy(*(void**)*dlEntry, (void*)dlInfo[1], dlInfo[0]);
				gUtil.ReWriteDisplayList(*(void**)*dlEntry, (unsigned long)dlInfo[0], 1);
				DCFlushRange(*(void**)*dlEntry, (unsigned long)dlInfo[0]);
				dlEntry = dlEntry - 1;
			}

			*meshColorArrays = (int)pppMemAlloc(
			    meshList->m_data->m_vertexCount << 2, ppvEnv->m_stagePtr,
			    const_cast<char*>(s_pppYmChangeTex_cpp), 0x17F);
			memset((void*)*meshColorArrays, 0xFF, meshList->m_data->m_vertexCount << 2);
			arrayOffset = arrayOffset + 4;
			meshColorArrays = meshColorArrays + 1;
			meshList = (ChangeTexMeshRef*)((char*)meshList + sizeof(ChangeTexMeshRef));
		}
	}

	Mtx modelMtx;

	ChangeTexMeshRef* curMesh = model0Raw->m_meshes;
	int frame = (int)(state->m_value0 * (float)(1 << model0Raw->m_data->m_frameShift));
	short frameShort = (short)frame;
	PSMTXCopy(model0Raw->m_matrix, modelMtx);

	unsigned char fallbackAlpha;
	u8 negativeRamp;
	if ((step->m_payload[0] == 2) || (step->m_payload[0] == 1)) {
		fallbackAlpha = 0;
		negativeRamp = 0xFF;
	} else {
		fallbackAlpha = 0xFF;
		negativeRamp = 0;
	}

	int meshOffset = 0;
	for (unsigned int meshIdx = 0; meshIdx < model0Raw->m_data->m_meshCount; meshIdx++) {
		int pointOffset = 0;
		int vertColors = *(int*)((char*)state->m_meshColorArrays + meshOffset);
		for (unsigned int v = 0; v < curMesh->m_data->m_vertexCount; v++) {
			int delta = (int)frameShort - (int)*(short*)((char*)curMesh->m_points + pointOffset + 2);
			if (delta >= 0) {
				int level = 0;
				float threshold = ChangeTexConst(FLOAT_80330df8);
				for (int tries = 7; tries != 0; tries--) {
					if ((float)delta > ChangeTexConst(FLOAT_80330dfc) * threshold) {
						if (negativeRamp == 0xFF) {
							*(u8*)(vertColors + 3) = negativeRamp - (level << 4);
						} else {
							*(u8*)(vertColors + 3) = (u8)(level << 4);
						}
						break;
					}
					threshold = threshold - ChangeTexConst(FLOAT_80330e00);
					level = level + 1;
				}
			} else {
				*(unsigned char*)(vertColors + 3) = fallbackAlpha;
			}

			pointOffset = pointOffset + 6;
			vertColors = vertColors + 4;
		}

		meshOffset = meshOffset + 4;
		curMesh = (ChangeTexMeshRef*)((char*)curMesh + sizeof(ChangeTexMeshRef));
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
void pppDestructYmChangeTex(pppYmChangeTex* ymChangeTex, pppYmChangeTexData* data)
{
	pppYmChangeTexState* state =
	    (pppYmChangeTexState*)(ymChangeTex->m_object.m_workArea + data->m_serializedDataOffsets[2]);
	CCharaPcs::CHandle* handle0 = GetCharaHandlePtr(state->m_charaObj, 0);
	CCharaPcs::CHandle* handle1 = GetCharaHandlePtr(state->m_charaObj, 1);
	CCharaPcs::CHandle* handle2 = GetCharaHandlePtr(state->m_charaObj, 2);
	ChangeTexModelRaw* model = 0;

	if (handle0 != 0) {
		CChara::CModel* modelBase = GetCharaModelPtr(handle0);
		model = reinterpret_cast<ChangeTexModelRaw*>(modelBase);
		ClearChangeTexModelCallbacks(modelBase);
	}
	CChara::CModel* model1;
	if ((handle1 != 0) && ((model1 = GetCharaModelPtr(handle1)), model1 != 0)) {
		ClearChangeTexModelCallbacks(model1);
	}
	CChara::CModel* model2;
	if ((handle2 != 0) && ((model2 = GetCharaModelPtr(handle2)), model2 != 0)) {
		ClearChangeTexModelCallbacks(model2);
	}

	void** stageArray = (void**)state->m_displayListArrays;
	void** meshArray;
	if (stageArray != 0) {
		meshArray = (void**)state->m_meshColorArrays;
		if (meshArray != 0) {
			goto freeArrays;
		}
	}
	return;

freeArrays:
	int meshList = (int)model->m_meshes;
	void** meshArrayOrig = meshArray;
	void** stageArrayOrig = stageArray;
	for (unsigned int i = 0; i < model->m_data->m_meshCount; i++, meshList += 0x14) {
		int meshData = *(int*)(meshList + 8);
			void** dlEntries = (void**)*stageArray;
		for (unsigned int j = 0; j < *(unsigned int*)(meshData + 0x4c); j++) {
			if (*(void**)*dlEntries != 0) {
				pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(*(void**)*dlEntries));
				*(void**)*dlEntries = 0;
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
void pppConstructYmChangeTex(pppYmChangeTex* ymChangeTex, pppYmChangeTexData* data)
{
	float init = ChangeTexConst(kPppYmChangeTexInitZero);
	pppYmChangeTexState* state =
	    (pppYmChangeTexState*)(ymChangeTex->m_object.m_workArea + data->m_serializedDataOffsets[2]);

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
void ChangeTex_AfterDrawMeshCallback(CChara::CModel* model, void* param_2, void* param_3, int meshIdx, float (*) [4])
{
	ChangeTexModelRaw* modelRaw = (ChangeTexModelRaw*)model;
	pppYmChangeTexState* state = (pppYmChangeTexState*)param_2;
	pppYmChangeTexStep* step = (pppYmChangeTexStep*)param_3;
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

	if (step->m_payload[0] != 0) {
		meshColorArrays = state->m_meshColorArrays;
		dlOffset = (int)state->m_texture;
		meshData = meshes[meshIdx].m_data;
		displayList = meshData->m_displayLists;
		if (meshColorArrays != 0) {
			meshColorArray = *(void**)((u8*)meshColorArrays + meshIdx * 4);
			if (meshColorArray != 0) {
				*(void**)(MaterialManRaw() + 4) = meshData->m_normals;
				GXSetArray((GXAttr)0xb, meshColorArray, 4);

				if ((step->m_payload[0] == 2) || (step->m_payload[0] == 3)) {
					*(int*)(MaterialManRaw() + 0xd0) = 0;
				} else {
					*(int*)(MaterialManRaw() + 0xd0) = dlOffset + 0x28;
				}

				drawTevBits = 0xACE0F;
				fullTevBits = drawTevBits | 0x1000;
				allOnes = -1;
				u8 fullByte = 0xFF;
				tevScale = 0x1e;
				displayListIdx = meshData->m_displayListCount - 1;
				dlOffset = displayListIdx * 4;
				while (displayListIdx >= 0) {
					dlArrayBase = *(int*)(meshIdx * 4 + (int)state->m_displayListArrays);
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

					MaterialMan.SetMaterial(modelRaw->m_data->m_materialSet, displayList->m_material, 0, (_GXTevScale)0);

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
 * PAL Address: 0x800d4164
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void ChangeTex_DrawMeshDLCallback(CChara::CModel* model, void* param_2, void* param_3, int meshIdx, int displayListIdx, float (*) [4])
{
	ChangeTexModelRaw* modelRaw = (ChangeTexModelRaw*)model;
	pppYmChangeTexState* state = (pppYmChangeTexState*)param_2;
	pppYmChangeTexStep* step = (pppYmChangeTexStep*)param_3;
	int textureInfo = (int)state->m_texture;
	ChangeTexMeshRef* meshes = modelRaw->m_meshes;
	ChangeTexMeshData* meshData = meshes[meshIdx].m_data;
	ChangeTexDisplayList* displayList = meshData->m_displayLists + displayListIdx;

	if (step->m_payload[0] == 0) {
		int zero = 0;
		int drawTevBits = 0xACE0F;
		int fullTevBits = drawTevBits | 0x1000;
		int allOnes = -1;
		int tevScale = 0x1E;
		u8 fullByte = 0xFF;

		*(int*)(MaterialManRaw() + 0x48) = drawTevBits;
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
		*(int*)(MaterialManRaw() + 0xD0) = textureInfo + 0x28;
		*(int*)(MaterialManRaw() + 0x128) = zero;
		*(int*)(MaterialManRaw() + 0x12c) = tevScale;
		*(int*)(MaterialManRaw() + 0x130) = zero;
		*(int*)(MaterialManRaw() + 0x40) = fullTevBits;
	}

	MaterialMan.SetMaterial(modelRaw->m_data->m_materialSet, displayList->m_material, 0, (_GXTevScale)0);

	if ((step->m_payload[0] == 1) || (step->m_payload[0] == 0)) {
		GXCallDisplayList(displayList->m_data, displayList->m_size);
	}
}

extern const float gPppYmMoveParabolaYOffsetStep = 1.0f;
extern const float gPppYmMoveParabolaZero = 0.0f;
extern const float gPppYmMoveParabolaAngleScale = 32768.0f;
extern const float gPppYmMoveParabolaAngleDivisor = 180.0f;
extern const float gPppYmMoveParabolaGravityScale = 0.5f;
