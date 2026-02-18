#include "ffcc/pppYmChangeTex.h"
#include "ffcc/mapmesh.h"
#include <string.h>
#include <dolphin/os/OSCache.h>

struct _pppMngStYmChangeTex {
	char _pad0[0xd8];
	void* m_charaObj;
};

struct _pppEnvStYmChangeTex {
	void* m_stagePtr;
	CMaterialSet* m_materialSetPtr;
	CMapMesh** m_mapMeshPtr;
};

extern char MaterialMan[];
extern _pppMngStYmChangeTex* pppMngStPtr;
extern _pppEnvStYmChangeTex* pppEnvStPtr;
extern float DAT_80330e10;
extern int DAT_8032ed70;
extern char DAT_8032ec70[];
extern char s_pppYmChangeTex_cpp_801db4c0[];
extern float FLOAT_80330df8;
extern float FLOAT_80330dfc;
extern float FLOAT_80330e00;

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
	char* mesh = (char*)model + 0xac + meshIdx * 0x14;
	void* displayList = (char*)(*(void**)(*(int*)(mesh + 8) + 0x50)) + displayListIdx * 0xc;

	if (*(char*)((char*)param_3 + 0x14) == 0) {
		*(int*)(MaterialMan + 0xd0) = (int)param_2 + 0x1c + 0x28;
		*(int*)(MaterialMan + 0x44) = -1;
		*(char*)(MaterialMan + 0x4c) = (char)0xff;
		*(int*)(MaterialMan + 0x11c) = 0;
		*(int*)(MaterialMan + 0x120) = 0x1e;
		*(int*)(MaterialMan + 0x124) = 0;
		*(char*)(MaterialMan + 0x205) = (char)0xff;
		*(char*)(MaterialMan + 0x206) = (char)0xff;
		*(int*)(MaterialMan + 0x58) = 0;
		*(int*)(MaterialMan + 0x5c) = 0;
		*(char*)(MaterialMan + 0x208) = 0;
		*(int*)(MaterialMan + 0x48) = 0xade0f;
		*(int*)(MaterialMan + 0x128) = 0;
		*(int*)(MaterialMan + 0x12c) = 0x1e;
		*(int*)(MaterialMan + 0x130) = 0;
		*(int*)(MaterialMan + 0x40) = 0xade0f;
	}

	void* materialSet = *(void**)(*(int*)((char*)model + 0xa4) + 0x24);
	unsigned int material = *(unsigned short*)((char*)displayList + 8);
	SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(MaterialMan, materialSet, material, 0, 0);

	if ((*(char*)((char*)param_3 + 0x14) == 1) || (*(char*)((char*)param_3 + 0x14) == 0)) {
		GXCallDisplayList(*(void**)displayList, *(unsigned int*)((char*)displayList + 4));
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
	if (*(char*)((char*)param_3 + 0x14) != 0) {
		int textureInfo = *(int*)((char*)param_2 + 0x1c);
		void* meshData = *(void**)((char*)model + 0xac + meshIdx * 0x14 + 8);
		char* displayLists = (char*)*(void**)((char*)meshData + 0x50);
		int colorArrayBase = *(int*)((char*)param_2 + 0xc);
		if (colorArrayBase != 0) {
			int vertexArray = *(int*)(colorArrayBase + meshIdx * 4);
			if (vertexArray != 0) {
				*(void**)(MaterialMan + 0x4) = *(void**)((char*)meshData + 0x20);
				GXSetArray(0xb, (void*)vertexArray, 4);

				if ((*(char*)((char*)param_3 + 0x14) == 2) || (*(char*)((char*)param_3 + 0x14) == 3)) {
					*(int*)(MaterialMan + 0x208) = 0;
				} else {
					*(int*)(MaterialMan + 0x208) = textureInfo + 0x28;
				}

				int dlIdx = *(int*)((char*)meshData + 0x4c) - 1;
				int dlOffset = dlIdx * 4;
				for (; dlIdx >= 0; dlIdx--) {
					int dlArrayBase = *(int*)(*(int*)((char*)param_2 + 0x10) + meshIdx * 4);
					*(int*)(MaterialMan + 0x44) = -1;
					*(char*)(MaterialMan + 0x4c) = (char)0xff;
					*(int*)(MaterialMan + 0x11c) = 0;
					*(int*)(MaterialMan + 0x120) = 0x1e;
					*(int*)(MaterialMan + 0x124) = 0;
					*(char*)(MaterialMan + 0x205) = (char)0xff;
					*(char*)(MaterialMan + 0x206) = (char)0xff;
					*(int*)(MaterialMan + 0x58) = 0;
					*(int*)(MaterialMan + 0x5c) = 0;
					*(char*)(MaterialMan + 0x208) = 0;
					*(int*)(MaterialMan + 0x48) = 0xade0f;
					*(int*)(MaterialMan + 0x128) = 0;
					*(int*)(MaterialMan + 0x12c) = 0x1e;
					*(int*)(MaterialMan + 0x130) = 0;
					*(int*)(MaterialMan + 0x40) = 0xade0f;

					void* modelData = *(void**)((char*)model + 0xa4);
					void* materialSet = *(void**)((char*)modelData + 0x24);
					unsigned short material = *(unsigned short*)(displayLists + 8);
					SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(MaterialMan, materialSet, material, 0, 0);

					void** dl = *(void***)(dlArrayBase + dlOffset);
					GXCallDisplayList(dl[0], (unsigned int)dl[1]);
					dlOffset -= 4;
					displayLists += 0xc;
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
	unsigned int i;
	unsigned int j;
	int model = 0;
	int dataOffset = data->m_serializedDataOffsets[2];
	void* handle0 = GetCharaHandlePtr__FP8CGObjectl(*(void**)((char*)ymChangeTex + 0x98 + dataOffset), 0);
	void* handle1 = GetCharaHandlePtr__FP8CGObjectl(*(void**)((char*)ymChangeTex + 0x98 + dataOffset), 1);
	void* handle2 = GetCharaHandlePtr__FP8CGObjectl(*(void**)((char*)ymChangeTex + 0x98 + dataOffset), 2);

	if (handle0 != 0) {
		model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle0);
		*(void**)(model + 0xe4) = 0;
		*(void**)(model + 0xe8) = 0;
		*(void**)(model + 0xf4) = 0;
		*(void**)(model + 0xfc) = 0;
		*(void**)(model + 0x104) = 0;
	}
	if (handle1 != 0) {
		int model1 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle1);
		if (model1 != 0) {
			*(void**)(model1 + 0xe4) = 0;
			*(void**)(model1 + 0xe8) = 0;
			*(void**)(model1 + 0xf4) = 0;
			*(void**)(model1 + 0xfc) = 0;
			*(void**)(model1 + 0x104) = 0;
		}
	}
	if (handle2 != 0) {
		int model2 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle2);
		if (model2 != 0) {
			*(void**)(model2 + 0xe4) = 0;
			*(void**)(model2 + 0xe8) = 0;
			*(void**)(model2 + 0xf4) = 0;
			*(void**)(model2 + 0xfc) = 0;
			*(void**)(model2 + 0x104) = 0;
		}
	}

	void** stageArray = *(void***)((char*)ymChangeTex + 0x90 + dataOffset);
	void** meshArray = *(void***)((char*)ymChangeTex + 0x8c + dataOffset);
	if (stageArray == 0 || meshArray == 0 || model == 0) {
		return;
	}

	int meshList = *(int*)(model + 0xac);
	unsigned int meshCount = *(unsigned int*)(*(int*)(model + 0xa4) + 0xc);
	for (i = 0; i < meshCount; i++) {
		unsigned int dlCount = *(unsigned int*)(*(int*)(meshList + 8) + 0x4c);
		void** dlEntries = (void**)*stageArray;
		for (j = 0; j < dlCount; j++) {
			if (dlEntries[0] != 0) {
				pppHeapUseRate__FPQ27CMemory6CStage(dlEntries[0]);
				dlEntries[0] = 0;
			}
			if (*(void**)dlEntries != 0) {
				pppHeapUseRate__FPQ27CMemory6CStage(*(void**)dlEntries);
				*(void**)dlEntries = 0;
			}
			dlEntries++;
		}

		if (*stageArray != 0) {
			pppHeapUseRate__FPQ27CMemory6CStage(*stageArray);
			*stageArray = 0;
		}
		if (*meshArray != 0) {
			pppHeapUseRate__FPQ27CMemory6CStage(*meshArray);
			*meshArray = 0;
		}

		stageArray++;
		meshArray++;
		meshList += 0x14;
	}

	pppHeapUseRate__FPQ27CMemory6CStage(*(void**)((char*)ymChangeTex + 0x90 + dataOffset));
	pppHeapUseRate__FPQ27CMemory6CStage(*(void**)((char*)ymChangeTex + 0x8c + dataOffset));
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
	if (DAT_8032ed70 != 0) {
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
		state[0] += (float)step->m_initWOrk;
		state[1] += step->m_stepValue;
		state[2] += (float)step->m_arg3;
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
				ReWriteDisplayList__5CUtilFPvUlUl(DAT_8032ec70, *(void**)dlPair, (unsigned long)dlInfo[0], 1);
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
	unsigned int local_8[2];
	if (step->m_dataValIndex != 0xffff) {
		_pppEnvStYmChangeTex* env = pppEnvStPtr;
		CMapMesh* mapMesh = env->m_mapMeshPtr[step->m_dataValIndex];
		CMaterialSet* materialSet = env->m_materialSetPtr;
		(int&)local_8[0] = 0;
		GetTexture__8CMapMeshFP12CMaterialSetRi(mapMesh, materialSet, (int&)local_8[0]);
		_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
	}
}
