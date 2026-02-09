#include "ffcc/pppYmChangeTex.h"
#include "ffcc/mapmesh.h"

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

extern "C" {
	int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh*, CMaterialSet*, int&);
	void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
	void* GetCharaHandlePtr__FP8CGObjectl(void*, long);
	int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void*);
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
	char flag = *(char*)((char*)param_3 + 0x14);
	if (flag == 0) {
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

	char* meshes = (char*)model + 0xac;
	void* meshData = *(void**)(meshes + meshIdx * 0x14 + 8);
	void* displayLists = *(void**)((char*)meshData + 0x50);
	void* displayList = (char*)displayLists + displayListIdx * 0xc;
	void* modelData = *(void**)((char*)model + 0xa4);
	void* materialSet = *(void**)((char*)modelData + 0x24);
	unsigned short material = *(unsigned short*)((char*)displayList + 8);
	SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(MaterialMan, materialSet, material, 0, 0);

	if (flag == 1 || flag == 0) {
		void* data = *(void**)displayList;
		unsigned int size = *(unsigned int*)((char*)displayList + 4);
		GXCallDisplayList(data, size);
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
	if (*(char*)((char*)param_3 + 0x14) == 0) {
		return;
	}

	int textureInfo = *(int*)((char*)param_2 + 0x1c);
	char* meshes = (char*)model + 0xac;
	void* meshData = *(void**)(meshes + meshIdx * 0x14 + 8);
	void* displayLists = *(void**)((char*)meshData + 0x50);
	int arrayBase = *(int*)((char*)param_2 + 0xc);
	if (arrayBase == 0) {
		return;
	}

	int vertexArray = *(int*)(arrayBase + meshIdx * 4);
	if (vertexArray == 0) {
		return;
	}

	*(void**)(MaterialMan + 0x4) = *(void**)((char*)meshData + 0x20);
	GXSetArray(0xb, (void*)vertexArray, 4);

	char flag = *(char*)((char*)param_3 + 0x14);
	if (flag == 2 || flag == 3) {
		*(int*)(MaterialMan + 0x208) = 0;
	} else {
		*(int*)(MaterialMan + 0x208) = textureInfo + 0x28;
	}

	int dlCount = *(int*)((char*)meshData + 0x4c);
	int dlArrayBase = *(int*)(*(int*)((char*)param_2 + 0x10) + meshIdx * 4);
	for (int i = dlCount - 1; i >= 0; --i) {
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

		void* displayList = (char*)displayLists + i * 0xc;
		void* modelData = *(void**)((char*)model + 0xa4);
		void* materialSet = *(void**)((char*)modelData + 0x24);
		unsigned short material = *(unsigned short*)((char*)displayList + 8);
		SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(MaterialMan, materialSet, material, 0, 0);

		void** dl = (void**)(dlArrayBase + i * 4);
		GXCallDisplayList(dl[0], *(unsigned int*)((char*)dl + 4));
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
void pppFrameYmChangeTex(pppYmChangeTex*, pppYmChangeTexStep*, pppYmChangeTexData*)
{
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
		local_8[0] = 0;
		GetTexture__8CMapMeshFP12CMaterialSetRi(pppEnvStPtr->m_mapMeshPtr[step->m_dataValIndex], pppEnvStPtr->m_materialSetPtr, (int&)local_8[0]);
		_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
	}
}
