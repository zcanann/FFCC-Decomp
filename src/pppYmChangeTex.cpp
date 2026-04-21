#include "ffcc/pppYmChangeTex.h"
#include "ffcc/gobject.h"
#include "ffcc/linkage.h"
#include "ffcc/mapmesh.h"
#include "ffcc/util.h"
#include <string.h>
#include <dolphin/os/OSCache.h>
#include "ffcc/ppp_linkage.h"

struct _pppMngStYmChangeTex {
	char _pad0[0xd8];
	void* m_charaObj;
};

struct _pppEnvStYmChangeTex {
	void* m_stagePtr;
	CMaterialSet* m_materialSetPtr;
	CMapMesh** m_mapMeshPtr;
};

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

struct pppYmChangeTexState {
	float m_value0;
	float m_value1;
	float m_value2;
	void* m_meshColorArrays;
	void* m_displayListArrays;
	int _pad14;
	void* m_charaObj;
	void* m_texture;
	int _pad20;
	void* m_context;
};

extern _pppMngStYmChangeTex* pppMngStPtr;
extern _pppEnvStYmChangeTex* pppEnvStPtr;

extern float DAT_80330e10;
static const char s_pppYmChangeTex_cpp_801db4c0[] = "pppYmChangeTex.cpp";
extern double DOUBLE_80330e08;
extern float FLOAT_80330df8;
extern float FLOAT_80330dfc;
extern float FLOAT_80330e00;

static inline unsigned char* MaterialManRaw() { return reinterpret_cast<unsigned char*>(&MaterialMan); }

CChara::CModel* GetCharaModelPtr(CCharaPcs::CHandle*);
CCharaPcs::CHandle* GetCharaHandlePtr(CGObject*, long);

extern "C" {
	int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh*, CMaterialSet*, int&);
	void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
	void* GetCharaHandlePtr__FP8CGObjectl(void*, long);
	int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void*);
	void* GetTextureFromRSD__FiP9_pppEnvSt(int, _pppEnvStYmChangeTex*);
	void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, void*, char*, int);
	void ReWriteDisplayList__5CUtilFPvUlUl(void*, void*, unsigned long, unsigned long);
	void pppHeapUseRate__FPQ27CMemory6CStage(void*);
	void SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(void*, void*, unsigned int, int, int);
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
		_pppEnvStYmChangeTex* env = pppEnvStPtr;
		CMapMesh* mapMesh = env->m_mapMeshPtr[step->m_dataValIndex];
		textureIndex = 0;
		GetTexture__8CMapMeshFP12CMaterialSetRi(mapMesh, env->m_materialSetPtr, textureIndex);
		_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
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
	pppYmChangeTexState* state = (pppYmChangeTexState*)((char*)ymChangeTex + serializedDataOffsets[2] + 0x80);
	CCharaPcs::CHandle* handle0 = GetCharaHandlePtr((CGObject*)pppMngStPtr->m_charaObj, 0);
	CChara::CModel* model0 = GetCharaModelPtr(handle0);

	state->m_charaObj = pppMngStPtr->m_charaObj;
	state->m_context = pppEnvStPtr;
	*(pppYmChangeTexState**)((char*)model0 + 0xE4) = state;
	*(pppYmChangeTexStep**)((char*)model0 + 0xE8) = step;
	*(void**)((char*)model0 + 0xFC) = (void*)ChangeTex_DrawMeshDLCallback;
	*(void**)((char*)model0 + 0x104) = (void*)ChangeTex_AfterDrawMeshCallback;
	state->m_texture = GetTextureFromRSD__FiP9_pppEnvSt(step->m_dataValIndex, pppEnvStPtr);

	CCharaPcs::CHandle* handle1 = GetCharaHandlePtr((CGObject*)state->m_charaObj, 1);
	CCharaPcs::CHandle* handle2 = GetCharaHandlePtr((CGObject*)state->m_charaObj, 2);
	CChara::CModel* model;
	if ((handle1 != 0) && ((model = GetCharaModelPtr(handle1)), model != 0)) {
		*(pppYmChangeTexState**)((char*)model + 0xE4) = state;
		*(pppYmChangeTexStep**)((char*)model + 0xE8) = step;
		*(void**)((char*)model + 0xFC) = (void*)ChangeTex_DrawMeshDLCallback;
		*(void**)((char*)model + 0x104) = (void*)ChangeTex_AfterDrawMeshCallback;
	}

	if ((handle2 != 0) && ((model = GetCharaModelPtr(handle2)), model != 0)) {
		*(pppYmChangeTexState**)((char*)model + 0xE4) = state;
		*(pppYmChangeTexStep**)((char*)model + 0xE8) = step;
		*(void**)((char*)model + 0xFC) = (void*)ChangeTex_DrawMeshDLCallback;
		*(void**)((char*)model + 0x104) = (void*)ChangeTex_AfterDrawMeshCallback;
	}

	if (step->m_payload[0] == 0) {
		return;
	}

	state->m_value1 = state->m_value1 + state->m_value2;
	state->m_value0 = state->m_value0 + state->m_value1;
	if (step->m_graphId == ((s32*)ymChangeTex)[0]) {
		state->m_value0 = state->m_value0 + step->m_initWOrk;
		state->m_value1 = state->m_value1 + step->m_stepValue;
		state->m_value2 = state->m_value2 + step->m_arg3;
	}

	void* texObj = GetTextureFromRSD__FiP9_pppEnvSt(step->m_dataValIndex, pppEnvStPtr);
	if (texObj == 0) {
		return;
	}
	state->m_texture = texObj;

	int meshList = *(int*)((char*)model0 + 0xAC);
	if ((state->m_meshColorArrays == 0) && (state->m_displayListArrays == 0)) {
		state->m_meshColorArrays = pppMemAlloc__FUlPQ27CMemory6CStagePci(
		    *(int*)(*(int*)((char*)model0 + 0xA4) + 0xC) << 2, pppEnvStPtr->m_stagePtr,
		    const_cast<char*>(s_pppYmChangeTex_cpp_801db4c0), 0x15D);
		state->m_displayListArrays = pppMemAlloc__FUlPQ27CMemory6CStagePci(
		    *(int*)(*(int*)((char*)model0 + 0xA4) + 0xC) << 2, pppEnvStPtr->m_stagePtr,
		    const_cast<char*>(s_pppYmChangeTex_cpp_801db4c0), 0x160);

		int* meshColorArrays = (int*)state->m_meshColorArrays;
		int arrayOffset = 0;
		for (unsigned int meshIdx = 0; meshIdx < *(unsigned int*)(*(int*)((char*)model0 + 0xA4) + 0xC); meshIdx++) {
			*(int*)((char*)state->m_displayListArrays + arrayOffset) = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
			    *(int*)(*(int*)(meshList + 8) + 0x4C) << 2, pppEnvStPtr->m_stagePtr,
			    const_cast<char*>(s_pppYmChangeTex_cpp_801db4c0), 0x168);

			int dlIdx = *(int*)(*(int*)(meshList + 8) + 0x4C) - 1;
			int* dlInfo = (int*)(*(int*)(*(int*)(meshList + 8) + 0x50));
			int* dlEntry = (int*)(*(int*)((char*)state->m_displayListArrays + arrayOffset) + dlIdx * 4);
			for (; dlIdx >= 0; dlIdx = dlIdx - 1, dlInfo = dlInfo + 3) {
				int dlPair = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
				    8, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppYmChangeTex_cpp_801db4c0), 0x172);
				*dlEntry = dlPair;
				*(int*)(*dlEntry + 4) = *dlInfo;
				*(int*)*dlEntry = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
				    *dlInfo, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppYmChangeTex_cpp_801db4c0), 0x174);
				memcpy(*(void**)*dlEntry, (void*)dlInfo[1], dlInfo[0]);
				ReWriteDisplayList__5CUtilFPvUlUl(&gUtil, *(void**)*dlEntry, (unsigned long)dlInfo[0], 1);
				DCFlushRange(*(void**)*dlEntry, (unsigned long)dlInfo[0]);
				dlEntry = dlEntry - 1;
			}

			*meshColorArrays = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
			    *(int*)(*(int*)(meshList + 8) + 0x14) << 2, pppEnvStPtr->m_stagePtr,
			    const_cast<char*>(s_pppYmChangeTex_cpp_801db4c0), 0x17F);
			memset((void*)*meshColorArrays, 0xFF, *(int*)(*(int*)(meshList + 8) + 0x14) << 2);
			arrayOffset = arrayOffset + 4;
			meshColorArrays = meshColorArrays + 1;
			meshList = meshList + 0x14;
		}
	}

	union {
		double d;
		u32 u[2];
	} frameScale;
	frameScale.u[0] = 0x43300000;
	frameScale.u[1] = ((1 << *(int*)(*(int*)((char*)model0 + 0xA4) + 0x34)) ^ 0x80000000);

	int curMesh = *(int*)((char*)model0 + 0xAC);
	int frame = (int)(state->m_value0 * (float)(frameScale.d - DOUBLE_80330e08));
	short frameShort = (short)frame;
	Mtx modelMtx;
	PSMTXCopy(*(Mtx*)((char*)model0 + 0x68), modelMtx);

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
	for (unsigned int meshIdx = 0; meshIdx < *(unsigned int*)(*(int*)((char*)model0 + 0xA4) + 0xC); meshIdx++) {
		int pointOffset = 0;
		int vertColors = *(int*)((char*)state->m_meshColorArrays + meshOffset);
		for (unsigned int v = 0; v < *(unsigned int*)(*(int*)(curMesh + 8) + 0x14); v++) {
			int delta = (int)frameShort - (int)*(short*)(*(int*)(curMesh + 0xC) + pointOffset + 2);
			if (delta >= 0) {
				int level = 0;
				float threshold = FLOAT_80330df8;
				for (int tries = 7; tries != 0; tries--) {
					if ((float)delta > FLOAT_80330dfc * threshold) {
						if (negativeRamp == 0xFF) {
							*(u8*)(vertColors + 3) = negativeRamp - (level << 4);
						} else {
							*(u8*)(vertColors + 3) = (u8)(level << 4);
						}
						break;
					}
					threshold = threshold - FLOAT_80330e00;
					level = level + 1;
				}
			} else {
				*(unsigned char*)(vertColors + 3) = fallbackAlpha;
			}

			pointOffset = pointOffset + 6;
			vertColors = vertColors + 4;
		}

		meshOffset = meshOffset + 4;
		curMesh = curMesh + 0x14;
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
	    (pppYmChangeTexState*)((char*)ymChangeTex + 0x80 + data->m_serializedDataOffsets[2]);
	void* handle0 = GetCharaHandlePtr__FP8CGObjectl(state->m_charaObj, 0);
	void* handle1 = GetCharaHandlePtr__FP8CGObjectl(state->m_charaObj, 1);
	void* handle2 = GetCharaHandlePtr__FP8CGObjectl(state->m_charaObj, 2);
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

	void** stageArray = (void**)state->m_displayListArrays;
	void** meshArray;
	if ((stageArray != 0) && ((meshArray = (void**)state->m_meshColorArrays), meshArray != 0)) {
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
 * PAL Address: 0x800d3f98
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmChangeTex(pppYmChangeTex* ymChangeTex, pppYmChangeTexData* data)
{
	float init = DAT_80330e10;
	pppYmChangeTexState* state =
	    (pppYmChangeTexState*)((char*)ymChangeTex + data->m_serializedDataOffsets[2] + 0x80);

	state->m_value0 = init;
	state->m_value2 = init;
	state->m_value1 = init;
	state->m_charaObj = 0;
	state->m_context = pppMngStPtr;
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
	ChangeTexMeshRef* meshes = *(ChangeTexMeshRef**)((char*)model + 0xAC);
	int vertexArray;
	int* displayListPtr;
	int dlArrayBase;
	int dlOffset;
	int fullWord;
	int drawTevBits;
	u8 fullByte;
	void* meshColorArrays;
	void* meshColorArray;
	ChangeTexMeshData* meshData;
	ChangeTexDisplayList* displayList;

	if (*(u8*)((char*)param_3 + 0x14) != 0) {
		meshColorArrays = *(void**)((char*)param_2 + 0xc);
		dlOffset = *(int*)((char*)param_2 + 0x1c);
		meshData = meshes[meshIdx].m_data;
		displayList = meshData->m_displayLists;
		if (meshColorArrays != 0) {
			meshColorArray = *(void**)((u8*)meshColorArrays + meshIdx * 4);
			if (meshColorArray != 0) {
				*(void**)(MaterialManRaw() + 4) = meshData->m_normals;
				GXSetArray((_GXAttr)0xb, meshColorArray, (unsigned char)4);

				if ((*(u8*)((char*)param_3 + 0x14) == 2) || (*(u8*)((char*)param_3 + 0x14) == 3)) {
					*(int*)(MaterialManRaw() + 0xd0) = 0;
				} else {
					*(int*)(MaterialManRaw() + 0xd0) = dlOffset + 0x28;
				}

				drawTevBits = 0xace0f;
				fullWord = -1;
				drawTevBits |= 0x1000;
				fullByte = 0xff;
				vertexArray = meshData->m_displayListCount - 1;
				dlOffset = vertexArray * 4;
				while (vertexArray >= 0) {
					dlArrayBase = *(int*)(meshIdx * 4 + *(int*)((char*)param_2 + 0x10));
					*(int*)(MaterialManRaw() + 0x48) = 0xace0f;
					*(int*)(MaterialManRaw() + 0x128) = 0;
					*(int*)(MaterialManRaw() + 0x12c) = 0x1e;
					*(int*)(MaterialManRaw() + 0x130) = 0;
					*(int*)(MaterialManRaw() + 0x44) = fullWord;
					*(char*)(MaterialManRaw() + 0x4c) = fullByte;
					*(int*)(MaterialManRaw() + 0x11c) = 0;
					*(int*)(MaterialManRaw() + 0x120) = 0x1e;
					*(int*)(MaterialManRaw() + 0x124) = 0;
					*(char*)(MaterialManRaw() + 0x205) = fullByte;
					*(char*)(MaterialManRaw() + 0x206) = fullByte;
					*(int*)(MaterialManRaw() + 0x58) = 0;
					*(int*)(MaterialManRaw() + 0x5c) = 0;
					*(char*)(MaterialManRaw() + 0x208) = 0;
					*(int*)(MaterialManRaw() + 0x48) = drawTevBits;
					*(int*)(MaterialManRaw() + 0x128) = 0;
					*(int*)(MaterialManRaw() + 0x12c) = 0x1e;
					*(int*)(MaterialManRaw() + 0x130) = 0;
					*(int*)(MaterialManRaw() + 0x40) = drawTevBits;

					SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
					    &MaterialMan, *(void**)(*(int*)((char*)model + 0xA4) + 0x24), displayList->m_material, 0, 0);

					displayListPtr = *(int**)(dlArrayBase + dlOffset);
					GXCallDisplayList((void*)displayListPtr[0], (unsigned int)displayListPtr[1]);
					dlOffset -= 4;
					vertexArray -= 1;
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
	ChangeTexMeshRef* meshes = *(ChangeTexMeshRef**)((char*)model + 0xAC);
	ChangeTexDisplayList* displayList = meshes[meshIdx].m_data->m_displayLists + displayListIdx;
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
		*(int*)(MaterialManRaw() + 0x12c) = 0x1e;
		*(int*)(MaterialManRaw() + 0x130) = 0;
		*(int*)(MaterialManRaw() + 0x40) = 0xADE0F;
	}

	SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
	    &MaterialMan, *(void**)(*(int*)((char*)model + 0xA4) + 0x24), displayList->m_material, 0, 0);

	if ((*(u8*)((char*)param_3 + 0x14) == 1) || (*(u8*)((char*)param_3 + 0x14) == 0)) {
		GXCallDisplayList(displayList->m_data, displayList->m_size);
	}
}
