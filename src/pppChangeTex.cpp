#include "ffcc/pppChangeTex.h"
#include "ffcc/graphic.h"
#include "dolphin/gx.h"
#include <string.h>
#include <dolphin/os/OSCache.h>

struct _pppMngStChangeTex {
	char _pad0[0xd8];
	void* m_charaObj;
};

struct _pppEnvStChangeTex {
	void* m_stagePtr;
	CMaterialSet* m_materialSetPtr;
	CMapMesh** m_mapMeshPtr;
};

extern char MaterialMan[];
extern void SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(void*, void*, unsigned int, int, int);
extern void GXCallDisplayList(void*, unsigned int);
extern _pppMngStChangeTex* pppMngStPtr;
extern _pppEnvStChangeTex* lbl_8032ED54;
extern _pppEnvStChangeTex* pppEnvStPtr;
extern float lbl_80332040;
extern float FLOAT_80332020;
extern float FLOAT_80332028;
extern double DOUBLE_80332030;
extern double DOUBLE_80332038;
extern char DAT_80332024[];
extern char DAT_8032ec70[];
extern int DAT_8032ed70;
extern char DAT_8032ed78;
extern char s_pppChangeTex_cpp_801dd660[];

extern "C" {
		int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh* mapMesh, CMaterialSet* materialSet, int& textureIndex);
		void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int stage, int rasSel, int texSel);
		void pppInitBlendMode__Fv(void);
	void _WaitDrawDone__8CGraphicFPci(CGraphic* graphic, const char* file, int line);
		void* GetCharaHandlePtr__FP8CGObjectl(void* obj, long index);
		int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void* handle);
		void pppHeapUseRate__FPQ27CMemory6CStage(void* stage);
		void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, void*, int, float*, float*, float*, float*, float*);
		int GetTextureFromRSD__FiP9_pppEnvSt(int, _pppEnvStChangeTex*);
		void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, void*, char*, int);
		void ReWriteDisplayList__5CUtilFPvUlUl(void*, void*, unsigned long, unsigned long);
		void CalcBoundaryBoxQuantized__5CUtilFP3VecP3VecP6S16VecUlUl(void*, void*, void*, void*, unsigned long, unsigned long);
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
extern "C" void ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f2(CChara::CModel* model, void* param_2, void* param_3, int param_4, int param_5, float (*param_6) [4])
{
	void* meshData = *(void**)((char*)model + param_4 * 0x14 + 0xb4);
	void* displayList = (void*)(*(int*)((char*)meshData + 0x50) + param_5 * 0xc);

	if (*(char*)((char*)param_3 + 0x14) == 0) {
		*(int*)(MaterialMan + 0x208) = *(int*)((char*)param_2 + 0x1c) + 0x28;
		*(int*)(MaterialMan + 0x44) = 0xFFFFFFFF;
		*(char*)(MaterialMan + 0x4c) = 0xFF;
		*(int*)(MaterialMan + 0x11c) = 0;
		*(int*)(MaterialMan + 0x120) = 0x1E;
		*(int*)(MaterialMan + 0x124) = 0;
		*(char*)(MaterialMan + 0x205) = 0xFF;
		*(char*)(MaterialMan + 0x206) = 0xFF;
		*(int*)(MaterialMan + 0x58) = 0;
		*(int*)(MaterialMan + 0x5c) = 0;
		*(char*)(MaterialMan + 0x208) = 0;
		*(int*)(MaterialMan + 0x48) = 0xADE0F;
		*(int*)(MaterialMan + 0x128) = 0;
		*(int*)(MaterialMan + 0x12c) = 0x1E;
		*(int*)(MaterialMan + 0x130) = 0;
		*(int*)(MaterialMan + 0x40) = 0xADE0F;
	}

	SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
	    MaterialMan, *(void**)(*(int*)((char*)model + 0xa4) + 0x24), *(unsigned short*)((char*)displayList + 8), 0, 0);
	GXCallDisplayList(*(void**)displayList, *(unsigned int*)((char*)displayList + 4));
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
extern "C" void ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f2(CChara::CModel* model, void* param_2, void* param_3, int param_4, float (*param_5) [4])
{
	int iVar1;
	int* puVar2;
	int iVar3;
	int iVar4;
	void* meshData;
	void* displayList;

	if (*(char*)((char*)param_3 + 0x14) != 0) {
		iVar4 = *(int*)((char*)param_2 + 0x1c);
		meshData = *(void**)((char*)model + param_4 * 0x14 + 0xb4);
		displayList = *(void**)((char*)meshData + 0x50);
		if (*(int*)((char*)param_2 + 0xc) != 0) {
			iVar1 = *(int*)(*(int*)((char*)param_2 + 0xc) + param_4 * 4);
			if (iVar1 != 0) {
				*(void**)(MaterialMan + 4) = *(void**)((char*)meshData + 0x20);
				GXSetArray((GXAttr)0xb, (void*)iVar1, 4);
				*(int*)(MaterialMan + 0x208) = iVar4 + 0x28;
				iVar1 = *(int*)((char*)meshData + 0x4c) - 1;
				iVar4 = iVar1 * 4;
				for (; -1 < iVar1; iVar1 = iVar1 - 1) {
					iVar3 = *(int*)(param_4 * 4 + *(int*)((char*)param_2 + 0x10));
					*(int*)(MaterialMan + 0x44) = 0xffffffff;
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
					SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
					    MaterialMan, *(void**)(*(int*)((char*)model + 0xa4) + 0x24), *(unsigned short*)((char*)displayList + 8), 0, 0);
					puVar2 = *(int**)(iVar3 + iVar4);
					GXCallDisplayList((void*)puVar2[0], (unsigned int)puVar2[1]);
					iVar4 = iVar4 + -4;
					displayList = (void*)((char*)displayList + 0xc);
				}
			}
		}
	}
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
void pppConstructChangeTex(pppChangeTex* changeTex, UnkC* data)
{
	float init = lbl_80332040;
	float* state = (float*)((char*)changeTex + data->m_serializedDataOffsets[2] + 0x80);
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
 * PAL Address: 0x8013f720
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2ChangeTex(pppChangeTex* changeTex, UnkC* data)
{
	float* state = (float*)((char*)changeTex + data->m_serializedDataOffsets[2] + 0x80);
	float init = lbl_80332040;

	state[0] = init;
	state[2] = init;
	state[1] = init;
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
void pppDestructChangeTex(pppChangeTex* changeTex, UnkC* data)
{
	unsigned int i;
	unsigned int j;
	int model;
	int dataOffset = data->m_serializedDataOffsets[2];
	void* handle0;
	void* handle1;
	void* handle2;
	void* stage;
	void* mesh;

	_WaitDrawDone__8CGraphicFPci(&Graphic, s_pppChangeTex_cpp_801dd660, 0x9d);

	handle0 = GetCharaHandlePtr__FP8CGObjectl(*(void**)((char*)changeTex + 0x98 + dataOffset), 0);
	handle1 = GetCharaHandlePtr__FP8CGObjectl(*(void**)((char*)changeTex + 0x98 + dataOffset), 1);
	handle2 = GetCharaHandlePtr__FP8CGObjectl(*(void**)((char*)changeTex + 0x98 + dataOffset), 2);

	model = 0;
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

	stage = *(void**)((char*)changeTex + 0x90 + dataOffset);
	if (stage != 0) {
		mesh = *(void**)((char*)changeTex + 0x8c + dataOffset);
		if (mesh != 0) {
			int meshList = *(int*)(model + 0xac);
			void** stageArray = (void**)stage;
			void** meshArray = (void**)mesh;

			for (i = 0; i < *(unsigned int*)(*(int*)(model + 0xa4) + 0xc); i++) {
				unsigned int dlCount = *(unsigned int*)(*(int*)(meshList + 8) + 0x4c);
				void** dlEntries = (void**)*stageArray;
				for (j = 0; j < dlCount; j++) {
					int* dlPair = (int*)*dlEntries;
					if (*(void**)dlPair != 0) {
						pppHeapUseRate__FPQ27CMemory6CStage(*(void**)dlPair);
						*(void**)dlPair = 0;
					}
					if ((void*)dlPair != 0) {
						pppHeapUseRate__FPQ27CMemory6CStage((void*)dlPair);
						*dlEntries = 0;
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

			if (stage != 0) {
				pppHeapUseRate__FPQ27CMemory6CStage(stage);
			}
			if (mesh != 0) {
				pppHeapUseRate__FPQ27CMemory6CStage(mesh);
			}
		}
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
void pppFrameChangeTex(pppChangeTex* changeTex, UnkB* step, UnkC* data)
{
	if (DAT_8032ed70 != 0) {
		return;
	}

	int dataValOffset = data->m_serializedDataOffsets[1];
	float* value = (float*)((char*)changeTex + data->m_serializedDataOffsets[2] + 0x80);

	void* handle0 = GetCharaHandlePtr__FP8CGObjectl(pppMngStPtr->m_charaObj, 0);
	int model0 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle0);

	CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
	    (float)step->m_initWOrk, &changeTex->field0_0x0, step->m_graphId, value, value + 1, value + 2,
	    &step->m_stepValue, (float*)&step->m_arg3);

	((int*)value)[6] = (int)pppMngStPtr->m_charaObj;
	((int*)value)[9] = (int)pppEnvStPtr;
	*(float**)(model0 + 0xE4) = value;
	*(UnkB**)(model0 + 0xE8) = step;
	*(void**)(model0 + 0xFC) = (void*)ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f2;
	*(void**)(model0 + 0x104) = (void*)ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f2;

	value[7] = (float)GetTextureFromRSD__FiP9_pppEnvSt(step->m_dataValIndex, pppEnvStPtr);

	void* handle1 = GetCharaHandlePtr__FP8CGObjectl((void*)((int*)value)[6], 1);
	void* handle2 = GetCharaHandlePtr__FP8CGObjectl((void*)((int*)value)[6], 2);

	if (handle1 != 0) {
		int model1 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle1);
		if (model1 != 0) {
			*(float**)(model1 + 0xE4) = value;
			*(UnkB**)(model1 + 0xE8) = step;
			*(void**)(model1 + 0xFC) = (void*)ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f2;
			*(void**)(model1 + 0x104) = (void*)ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f2;
		}
	}

	if (handle2 != 0) {
		int model2 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle2);
		if (model2 != 0) {
			*(float**)(model2 + 0xE4) = value;
			*(UnkB**)(model2 + 0xE8) = step;
			*(void**)(model2 + 0xFC) = (void*)ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f2;
			*(void**)(model2 + 0x104) = (void*)ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f2;
		}
	}

	if (step->m_payload[0] == 0) {
		return;
	}

	float texObj = (float)GetTextureFromRSD__FiP9_pppEnvSt(step->m_dataValIndex, pppEnvStPtr);
	if (texObj == 0.0f) {
		return;
	}
	value[7] = texObj;

	int meshList = *(int*)(model0 + 0xAC);
	unsigned int meshCount = *(unsigned int*)(*(int*)(model0 + 0xA4) + 0xC);

	if (((int*)value)[3] == 0 && ((int*)value)[4] == 0) {
		value[17] = FLOAT_80332020;
		((int*)value)[3] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
		    meshCount << 2, pppEnvStPtr->m_stagePtr, s_pppChangeTex_cpp_801dd660, 0x163);
		((int*)value)[4] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
		    meshCount << 2, pppEnvStPtr->m_stagePtr, s_pppChangeTex_cpp_801dd660, 0x166);

		int* meshColorArrays = (int*)((int*)value)[3];
		int allocIndex = 0;
		int curMesh = meshList;
		for (unsigned int meshIdx = 0; meshIdx < meshCount; meshIdx++) {
			int meshHdr = *(int*)(curMesh + 8);
			if (strcmp((char*)meshHdr, DAT_80332024) == 0) {
				CalcBoundaryBoxQuantized__5CUtilFP3VecP3VecP6S16VecUlUl(
				    DAT_8032ec70, value + 10, value + 14, *(void**)(curMesh + 0xC), *(unsigned long*)(meshHdr + 0x14),
				    *(unsigned long*)(*(int*)(model0 + 0xA4) + 0x34));
			}

			*(int*)(((int*)value)[4] + allocIndex) = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
			    *(int*)(meshHdr + 0x4C) << 2, pppEnvStPtr->m_stagePtr, s_pppChangeTex_cpp_801dd660, 0x181);

			int dlCount = *(int*)(meshHdr + 0x4C);
			int* dlInfo = (int*)(*(int*)(meshHdr + 0x50));
			int* dlEntry = (int*)(*(int*)(((int*)value)[4] + allocIndex) + (dlCount - 1) * 4);
			for (int dlIdx = dlCount - 1; dlIdx >= 0; dlIdx--) {
				int dlPair = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
				    8, pppEnvStPtr->m_stagePtr, s_pppChangeTex_cpp_801dd660, 0x18B);
				*dlEntry = dlPair;
				*(int*)(dlPair + 4) = dlInfo[0];
				*(int*)dlPair = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
				    dlInfo[0], pppEnvStPtr->m_stagePtr, s_pppChangeTex_cpp_801dd660, 0x18D);
				memcpy(*(void**)dlPair, (void*)dlInfo[1], dlInfo[0]);
				ReWriteDisplayList__5CUtilFPvUlUl(DAT_8032ec70, *(void**)dlPair, (unsigned long)dlInfo[0], 1);
				dlEntry--;
				dlInfo += 3;
			}

			meshColorArrays[meshIdx] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
			    *(int*)(meshHdr + 0x14) << 2, pppEnvStPtr->m_stagePtr, s_pppChangeTex_cpp_801dd660, 0x196);
			memset((void*)meshColorArrays[meshIdx], 0, *(int*)(meshHdr + 0x14) << 2);

			allocIndex += 4;
			curMesh += 0x14;
		}
	}

	if (DAT_8032ed78 == 0) {
		float currentValue = value[0] * (value[15] - value[11]) + value[11];
		short splitY = (short)(int)(currentValue * (float)((double)(1 << *(int*)(*(int*)(model0 + 0xA4) + 0x34)) - DOUBLE_80332030));
		if (value[17] != currentValue) {
			value[17] = currentValue;

			double d = (double)(unsigned char)*((char*)changeTex + dataValOffset + 0x8B);
			double alphaBase = (double)(FLOAT_80332028 * ((float)(d - DOUBLE_80332038) / FLOAT_80332028));

			int meshColorOffset = 0;
			int curMesh = meshList;
			for (unsigned int meshIdx = 0; meshIdx < meshCount; meshIdx++) {
				int pointOffset = 0;
				int colorPtr = *(int*)(((int*)value)[3] + meshColorOffset);
				unsigned int vertCount = *(unsigned int*)(*(int*)(curMesh + 8) + 0x14);
				for (unsigned int v = 0; v < vertCount; v++) {
					short y = *(short*)(*(int*)(curMesh + 0xC) + pointOffset + 2);
					if (step->m_payload[0] == 1) {
						*(unsigned char*)(colorPtr + 3) = (y < splitY) ? (unsigned char)(int)alphaBase : 0;
					} else if (step->m_payload[0] == 2) {
						*(unsigned char*)(colorPtr + 3) = (splitY < y) ? (unsigned char)(int)alphaBase : 0;
					}
					pointOffset += 6;
					colorPtr += 4;
				}
				DCFlushRange(*(void**)(((int*)value)[3] + meshColorOffset), vertCount << 2);
				meshColorOffset += 4;
				curMesh += 0x14;
			}
		}
	}
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
void pppRenderChangeTex(pppChangeTex*, UnkB* step, UnkC*)
{
	int textureIndex;

	if (step->m_dataValIndex != 0xffff) {
		_pppEnvStChangeTex* env = lbl_8032ED54;
		CMapMesh* mapMesh = env->m_mapMeshPtr[step->m_dataValIndex];
		textureIndex = 0;
		GetTexture__8CMapMeshFP12CMaterialSetRi(
		    mapMesh, env->m_materialSetPtr, textureIndex);
		_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
		pppInitBlendMode__Fv();
	}
}
