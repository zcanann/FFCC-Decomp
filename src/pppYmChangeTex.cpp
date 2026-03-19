#include "ffcc/pppYmChangeTex.h"
#include "ffcc/linkage.h"
#include "ffcc/mapmesh.h"
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
	void** m_meshColorArrays;
	void** m_displayListArrays;
	u8 _pad14[4];
	void* m_charaObj;
	int m_texture;
	u8 _pad20[4];
	_pppEnvStYmChangeTex* m_env;
};

extern _pppMngStYmChangeTex* pppMngStPtr;
extern _pppEnvStYmChangeTex* pppEnvStPtr;

extern float DAT_80330e10;
extern char gUtil[];
char s_pppYmChangeTex_cpp_801db4c0[] = "pppYmChangeTex.cpp";
extern float FLOAT_80330df8;
extern float FLOAT_80330dfc;
extern float FLOAT_80330e00;

static inline unsigned char* MaterialManRaw() { return reinterpret_cast<unsigned char*>(&MaterialMan); }

extern "C" {
	int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh*, CMaterialSet*, int&);
	void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
	void* GetCharaHandlePtr__FP8CGObjectl(void*, long);
	int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void*);
	int GetTextureFromRSD__FiP9_pppEnvSt(int, _pppEnvStYmChangeTex*);
	void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, void*, char*, int);
	void ReWriteDisplayList__5CUtilFPvUlUl(void*, void*, unsigned long, unsigned long);
	void pppHeapUseRate__FPQ27CMemory6CStage(void*);
	void SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(void*, void*, unsigned int, int, int);
	void GXCallDisplayList(void*, unsigned int);
	void GXSetArray(unsigned int, void*, unsigned char);
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
	int vertexArray;
	int* displayListPtr;
	int dlArrayBase;
	int dlOffset;
	ChangeTexMeshData* meshData;
	ChangeTexDisplayList* displayList;

	if (*(u8*)((char*)param_3 + 0x14) != 0) {
		dlOffset = *(int*)((char*)param_2 + 0x1c);
		meshData = (*(ChangeTexMeshRef**)((char*)model + 0xAC))[meshIdx].m_data;
		displayList = meshData->m_displayLists;
		if (*(int*)((char*)param_2 + 0xc) != 0) {
			vertexArray = *(int*)(*(int*)((char*)param_2 + 0xc) + meshIdx * 4);
			if (vertexArray != 0) {
				*(void**)(MaterialManRaw() + 4) = meshData->m_normals;
				GXSetArray(0xb, (void*)vertexArray, 4);

				if ((*(u8*)((char*)param_3 + 0x14) == 2) || (*(u8*)((char*)param_3 + 0x14) == 3)) {
					*(int*)(MaterialManRaw() + 0xd0) = 0;
				} else {
					*(int*)(MaterialManRaw() + 0xd0) = dlOffset + 0x28;
				}

				vertexArray = meshData->m_displayListCount - 1;
				dlOffset = vertexArray * 4;
				for (; -1 < vertexArray; vertexArray = vertexArray - 1) {
					dlArrayBase = *(int*)(meshIdx * 4 + *(int*)((char*)param_2 + 0x10));
					*(int*)(MaterialManRaw() + 0x44) = -1;
					*(char*)(MaterialManRaw() + 0x4c) = (char)0xff;
					*(int*)(MaterialManRaw() + 0x11c) = 0;
					*(int*)(MaterialManRaw() + 0x120) = 0x1e;
					*(int*)(MaterialManRaw() + 0x124) = 0;
					*(char*)(MaterialManRaw() + 0x205) = (char)0xff;
					*(char*)(MaterialManRaw() + 0x206) = (char)0xff;
					*(int*)(MaterialManRaw() + 0x58) = 0;
					*(int*)(MaterialManRaw() + 0x5c) = 0;
					*(char*)(MaterialManRaw() + 0x208) = 0;
					*(int*)(MaterialManRaw() + 0x48) = 0xade0f;
					*(int*)(MaterialManRaw() + 0x128) = 0;
					*(int*)(MaterialManRaw() + 0x12c) = 0x1e;
					*(int*)(MaterialManRaw() + 0x130) = 0;
					*(int*)(MaterialManRaw() + 0x40) = 0xade0f;

					SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
					    &MaterialMan, *(void**)(*(int*)((char*)model + 0xA4) + 0x24), displayList->m_material, 0, 0);

					displayListPtr = *(int**)(dlArrayBase + dlOffset);
					GXCallDisplayList((void*)displayListPtr[0], (unsigned int)displayListPtr[1]);
					dlOffset = dlOffset - 4;
					displayList = displayList + 1;
				}
			}
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
	float* state = (float*)((char*)ymChangeTex + data->m_serializedDataOffsets[2] + 0x80);
	int* stateInt = (int*)state;

	state[0] = init;
	state[2] = init;
	state[1] = init;
	stateInt[6] = 0;
	stateInt[9] = (int)pppMngStPtr;
	stateInt[7] = 0;
	stateInt[3] = 0;
	stateInt[4] = 0;
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

	void** stageArray = state->m_displayListArrays;
	void** meshArray;
	if ((stageArray != 0) && ((meshArray = state->m_meshColorArrays), meshArray != 0)) {
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

	int dataOffset = data->m_serializedDataOffsets[2];
	float* state = (float*)((char*)ymChangeTex + dataOffset + 0x80);
	int* stateInt = (int*)state;

	void* handle0 = GetCharaHandlePtr__FP8CGObjectl(pppMngStPtr->m_charaObj, 0);
	int model0 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle0);

	stateInt[6] = (int)pppMngStPtr->m_charaObj;
	stateInt[9] = (int)pppEnvStPtr;

	*(void**)(model0 + 0xE4) = state;
	*(void**)(model0 + 0xE8) = step;
	*(void**)(model0 + 0xFC) = (void*)ChangeTex_DrawMeshDLCallback;
	*(void**)(model0 + 0x104) = (void*)ChangeTex_AfterDrawMeshCallback;

	stateInt[7] = GetTextureFromRSD__FiP9_pppEnvSt(step->m_dataValIndex, pppEnvStPtr);

	void* handle1 = GetCharaHandlePtr__FP8CGObjectl((void*)stateInt[6], 1);
	void* handle2 = GetCharaHandlePtr__FP8CGObjectl((void*)stateInt[6], 2);

	if (handle1 != 0) {
		int model1 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle1);
		if (model1 != 0) {
			*(void**)(model1 + 0xE4) = state;
			*(void**)(model1 + 0xE8) = step;
			*(void**)(model1 + 0xFC) = (void*)ChangeTex_DrawMeshDLCallback;
			*(void**)(model1 + 0x104) = (void*)ChangeTex_AfterDrawMeshCallback;
		}
	}

	if (handle2 != 0) {
		int model2 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle2);
		if (model2 != 0) {
			*(void**)(model2 + 0xE4) = state;
			*(void**)(model2 + 0xE8) = step;
			*(void**)(model2 + 0xFC) = (void*)ChangeTex_DrawMeshDLCallback;
			*(void**)(model2 + 0x104) = (void*)ChangeTex_AfterDrawMeshCallback;
		}
	}

	if (step->m_payload[0] == 0) {
		return;
	}

	state[1] += state[2];
	state[0] += state[1];

	if (step->m_graphId == *(u32*)&ymChangeTex->field0_0x0) {
		state[0] += step->m_initWOrk;
		state[1] += step->m_stepValue;
		state[2] += step->m_arg3;
	}

	int texObj = GetTextureFromRSD__FiP9_pppEnvSt(step->m_dataValIndex, pppEnvStPtr);
	if (texObj == 0) {
		return;
	}
	stateInt[7] = texObj;

	int meshList = *(int*)(model0 + 0xAC);
	unsigned int meshCount = *(unsigned int*)(*(int*)(model0 + 0xA4) + 0xC);

	if (stateInt[3] == 0 && stateInt[4] == 0) {
		stateInt[3] =
		    (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(meshCount << 2, pppEnvStPtr->m_stagePtr, s_pppYmChangeTex_cpp_801db4c0, 0x15D);
		stateInt[4] =
		    (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(meshCount << 2, pppEnvStPtr->m_stagePtr, s_pppYmChangeTex_cpp_801db4c0, 0x160);

		int* meshColorArrays = (int*)stateInt[3];
		int curMesh = meshList;

		for (unsigned int meshIdx = 0; meshIdx < meshCount; meshIdx++) {
			int dlCount = *(int*)(*(int*)(curMesh + 8) + 0x4C);
			((int*)stateInt[4])[meshIdx] =
			    (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(dlCount << 2, pppEnvStPtr->m_stagePtr, s_pppYmChangeTex_cpp_801db4c0, 0x168);

			int* dlInfo = (int*)*(int*)(*(int*)(curMesh + 8) + 0x50);
			int* dlEntries = (int*)(((int*)stateInt[4])[meshIdx] + (dlCount - 1) * 4);

			for (int dlIdx = dlCount - 1; dlIdx >= 0; dlIdx--) {
				int dlPair =
				    (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(8, pppEnvStPtr->m_stagePtr, s_pppYmChangeTex_cpp_801db4c0, 0x172);
				*dlEntries = dlPair;
				*(int*)(dlPair + 4) = dlInfo[0];
				*(int*)dlPair =
				    (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(dlInfo[0], pppEnvStPtr->m_stagePtr, s_pppYmChangeTex_cpp_801db4c0, 0x174);
				memcpy(*(void**)dlPair, (void*)dlInfo[1], dlInfo[0]);
				ReWriteDisplayList__5CUtilFPvUlUl(gUtil, *(void**)dlPair, (unsigned long)dlInfo[0], 1);
				DCFlushRange(*(void**)dlPair, (unsigned long)dlInfo[0]);

				dlEntries--;
				dlInfo += 3;
			}

			int vertCount = *(int*)(*(int*)(curMesh + 8) + 0x14);
			meshColorArrays[meshIdx] =
			    (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(vertCount << 2, pppEnvStPtr->m_stagePtr, s_pppYmChangeTex_cpp_801db4c0, 0x17F);
			memset((void*)meshColorArrays[meshIdx], 0xFF, vertCount << 2);

			curMesh += 0x14;
		}
	}

	int frameCount = 1 << *(int*)(*(int*)(model0 + 0xA4) + 0x34);
	int frame = (int)(state[0] * (float)frameCount);
	Mtx modelMtx;
	PSMTXCopy(*(Mtx*)(model0 + 0x68), modelMtx);

	unsigned char fallbackAlpha;
	char negativeRamp;
	if (step->m_payload[0] == 2 || step->m_payload[0] == 1) {
		fallbackAlpha = 0;
		negativeRamp = -1;
	} else {
		fallbackAlpha = 0xFF;
		negativeRamp = 0;
	}

	int curMesh = meshList;
	for (unsigned int meshIdx = 0; meshIdx < meshCount; meshIdx++) {
		int vertColors = ((int*)stateInt[3])[meshIdx];
		int pointOffset = 0;
		unsigned int vertCount = *(unsigned int*)(*(int*)(curMesh + 8) + 0x14);

		for (unsigned int v = 0; v < vertCount; v++) {
			int delta = (int)(short)frame - (int)*(short*)(*(int*)(curMesh + 0xC) + pointOffset + 2);
			if (delta < 0) {
				*(unsigned char*)(vertColors + 3) = fallbackAlpha;
			} else {
				int level = 0;
				int tries = 7;
				float threshold = FLOAT_80330df8;
				while (tries != 0) {
					if (FLOAT_80330dfc * threshold < (float)delta) {
						if (negativeRamp == -1) {
							*(char*)(vertColors + 3) = (char)(-1 - (level << 4));
						} else {
							*(char*)(vertColors + 3) = (char)(level << 4);
						}
						break;
					}
					threshold -= FLOAT_80330e00;
					level++;
					tries--;
				}
			}

			pointOffset += 6;
			vertColors += 4;
		}

		curMesh += 0x14;
	}
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
