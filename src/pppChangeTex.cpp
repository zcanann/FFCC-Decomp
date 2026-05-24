#include "ffcc/pppChangeTex.h"
#include "ffcc/gobject.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppYmEnv.h"
extern "C" {
extern const float kPppChangeTexInit;
extern int gPppCalcDisabled;
extern unsigned char gPppInConstructor;
}
#include "ffcc/util.h"
#include "dolphin/gx.h"
#include <string.h>
#include <dolphin/os/OSCache.h>

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
	s16* m_points;
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

struct ChangeTexWork {
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
	Vec m_bboxMin;
	int _pad34;
	Vec m_bboxMax;
	float m_cachedValue;
};

struct ChangeTexModelRaw {
	u8 _pad0[0x68];
	Mtx m_matrix;
	u8 _pad98[0xC];
	ChangeTexModelData* m_data;
	u8 _padA8[0x4];
	ChangeTexMeshRef* m_meshes;
	u8 _padB0[0x34];
	ChangeTexWork* m_state;
	pppChangeTexUnkB* m_step;
	u8 _padEC[0x8];
	void* m_beforeDrawCallback;
	u8 _padF8[0x4];
	void (*m_drawMeshDlCallback)(CChara::CModel*, void*, void*, int, int, float (*)[4]);
	u8 _pad100[0x4];
	void (*m_afterDrawMeshCallback)(CChara::CModel*, void*, void*, int, float (*)[4]);
};

STATIC_ASSERT(offsetof(ChangeTexModelRaw, m_data) == 0xA4);
STATIC_ASSERT(offsetof(ChangeTexModelRaw, m_meshes) == 0xAC);
STATIC_ASSERT(offsetof(ChangeTexModelRaw, m_state) == 0xE4);
STATIC_ASSERT(offsetof(ChangeTexModelRaw, m_step) == 0xE8);
STATIC_ASSERT(offsetof(ChangeTexModelRaw, m_beforeDrawCallback) == 0xF4);
STATIC_ASSERT(offsetof(ChangeTexModelRaw, m_drawMeshDlCallback) == 0xFC);
STATIC_ASSERT(offsetof(ChangeTexModelRaw, m_afterDrawMeshCallback) == 0x104);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_vertexCount) == 0x14);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_normals) == 0x20);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_displayListCount) == 0x4C);
STATIC_ASSERT(offsetof(ChangeTexMeshData, m_displayLists) == 0x50);
STATIC_ASSERT(offsetof(ChangeTexMeshRef, m_points) == 0xC);
STATIC_ASSERT(offsetof(ChangeTexModelData, m_meshCount) == 0xC);
STATIC_ASSERT(offsetof(ChangeTexModelData, m_materialSet) == 0x24);
STATIC_ASSERT(offsetof(ChangeTexModelData, m_frameShift) == 0x34);

extern const float kPppChangeTexCachedValueInit = -10000.0f;
extern const char sPppChangeTexMeshObjectName[] = "obj";
extern const float kPppChangeTexAlphaScale = 255.0f;
extern "C" const char s_pppChangeTex_cpp[] ATTRIBUTE_ALIGN(8) = "pppChangeTex.cpp";

static inline unsigned char* MaterialManRaw() { return reinterpret_cast<unsigned char*>(&MaterialMan); }

static inline float LoadFloat(const float& value)
{
	return value;
}

static void ChangeTex_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
static void ChangeTex_AfterDrawMeshCallback(CChara::CModel*, void*, void*, int, float (*)[4]);

/*
 * --INFO--
 * PAL Address: 0x8013ef94
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderChangeTex(pppChangeTex*, pppChangeTexUnkB* step, pppChangeTexUnkC*)
{
	int textureIndex;

	if (step->m_dataValIndex != 0xffff) {
		_pppEnvSt* env = pppEnvStPtr;
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
void pppFrameChangeTex(pppChangeTex* changeTex, pppChangeTexUnkB* step, pppChangeTexUnkC* data)
{
	if (gPppCalcDisabled != 0) {
		return;
	}

	s32* serializedDataOffsets = data->m_serializedDataOffsets;
	ChangeTexWork* work = (ChangeTexWork*)(changeTex->m_object.m_workArea + serializedDataOffsets[2]);
	u8* colorData = changeTex->m_object.m_workArea + serializedDataOffsets[1];
	CCharaPcs::CHandle* handle0 = GetCharaHandlePtr((CGObject*)pppMngStPtr->m_owner, 0);
	CChara::CModel* model0 = GetCharaModelPtr(handle0);
	ChangeTexModelRaw* model0Raw = (ChangeTexModelRaw*)model0;

	CalcGraphValue(
	    &changeTex->m_object, step->m_graphId, work->m_value0, work->m_value1, work->m_value2, step->m_initWOrk,
	    step->m_stepValue, step->m_arg3);

	work->m_charaObj = (CGObject*)pppMngStPtr->m_owner;
	work->m_context = pppEnvStPtr;
	model0Raw->m_state = work;
	model0Raw->m_step = step;
	model0Raw->m_drawMeshDlCallback = ChangeTex_DrawMeshDLCallback;
	model0Raw->m_afterDrawMeshCallback = ChangeTex_AfterDrawMeshCallback;

	work->m_texture = reinterpret_cast<void*>(GetTextureFromRSD(step->m_dataValIndex, pppEnvStPtr));

	CCharaPcs::CHandle* handle1 = GetCharaHandlePtr(work->m_charaObj, 1);
	CCharaPcs::CHandle* handle2 = GetCharaHandlePtr(work->m_charaObj, 2);

	CChara::CModel* model;
	if ((handle1 != 0) && ((model = GetCharaModelPtr(handle1)), model != 0)) {
		ChangeTexModelRaw* modelRaw = (ChangeTexModelRaw*)model;
		modelRaw->m_state = work;
		modelRaw->m_step = step;
		modelRaw->m_drawMeshDlCallback = ChangeTex_DrawMeshDLCallback;
		modelRaw->m_afterDrawMeshCallback = ChangeTex_AfterDrawMeshCallback;
	}

	if ((handle2 != 0) && ((model = GetCharaModelPtr(handle2)), model != 0)) {
		ChangeTexModelRaw* modelRaw = (ChangeTexModelRaw*)model;
		modelRaw->m_state = work;
		modelRaw->m_step = step;
		modelRaw->m_drawMeshDlCallback = ChangeTex_DrawMeshDLCallback;
		modelRaw->m_afterDrawMeshCallback = ChangeTex_AfterDrawMeshCallback;
	}

	if (step->m_payload[0] == 0) {
		return;
	}

	void* texObj = reinterpret_cast<void*>(GetTextureFromRSD(step->m_dataValIndex, pppEnvStPtr));
	if (texObj == 0) {
		return;
	}
	work->m_texture = texObj;

	ChangeTexMeshRef* meshList = model0Raw->m_meshes;
	if ((work->m_meshColorArrays == 0) && (work->m_displayListArrays == 0)) {
		work->m_cachedValue = LoadFloat(kPppChangeTexCachedValueInit);
		work->m_meshColorArrays = pppMemAlloc(
		    model0Raw->m_data->m_meshCount << 2, pppEnvStPtr->m_stagePtr,
		    const_cast<char*>(s_pppChangeTex_cpp), 0x163);
		work->m_displayListArrays = pppMemAlloc(
		    model0Raw->m_data->m_meshCount << 2, pppEnvStPtr->m_stagePtr,
		    const_cast<char*>(s_pppChangeTex_cpp), 0x166);

		int* meshColorArrays = (int*)work->m_meshColorArrays;
		int arrayOffset = 0;
		for (unsigned int meshIdx = 0; meshIdx < model0Raw->m_data->m_meshCount; meshIdx++) {
			ChangeTexMeshData* meshData = meshList->m_data;
			if (strcmp(meshData->m_name, sPppChangeTexMeshObjectName) == 0) {
				gUtil.CalcBoundaryBoxQuantized(&work->m_bboxMin, &work->m_bboxMax, (S16Vec*)meshList->m_points,
				    meshData->m_vertexCount, model0Raw->m_data->m_frameShift);
			}

			*(int*)((u8*)work->m_displayListArrays + arrayOffset) = (int)pppMemAlloc(
			    meshList->m_data->m_displayListCount << 2, pppEnvStPtr->m_stagePtr,
			    const_cast<char*>(s_pppChangeTex_cpp), 0x181);

			int dlIdx = meshList->m_data->m_displayListCount - 1;
			int* dlInfo = (int*)meshList->m_data->m_displayLists;
			int* dlEntry = (int*)(*(int*)((u8*)work->m_displayListArrays + arrayOffset) + dlIdx * 4);
			for (; dlIdx >= 0; dlIdx = dlIdx - 1, dlInfo = dlInfo + 3) {
				int dlPair = (int)pppMemAlloc(
				    8, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppChangeTex_cpp), 0x18B);
				*dlEntry = dlPair;
				*(int*)(*dlEntry + 4) = *dlInfo;
				*(int*)*dlEntry = (int)pppMemAlloc(
				    *dlInfo, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppChangeTex_cpp), 0x18D);
				memcpy(*(void**)*dlEntry, (void*)dlInfo[1], dlInfo[0]);
				gUtil.ReWriteDisplayList(*(void**)*dlEntry, (unsigned long)dlInfo[0], 1);
				dlEntry = dlEntry - 1;
			}

			*meshColorArrays = (int)pppMemAlloc(
			    meshList->m_data->m_vertexCount << 2, pppEnvStPtr->m_stagePtr,
			    const_cast<char*>(s_pppChangeTex_cpp), 0x196);
			memset((void*)*meshColorArrays, 0, meshList->m_data->m_vertexCount << 2);

			arrayOffset += 4;
			meshColorArrays = meshColorArrays + 1;
			meshList = (ChangeTexMeshRef*)((char*)meshList + sizeof(ChangeTexMeshRef));
		}
	}

	if (gPppInConstructor != 0) {
		return;
	}

	float currentValue = work->m_value0 * (work->m_bboxMax.y - work->m_bboxMin.y) + work->m_bboxMin.y;

	short splitY = (short)(int)(currentValue * (float)(1 << model0Raw->m_data->m_frameShift));
	if (work->m_cachedValue == currentValue) {
		return;
	}

	work->m_cachedValue = currentValue;

	double alphaBase =
	    (double)(LoadFloat(kPppChangeTexAlphaScale) * ((float)colorData[0xB] / LoadFloat(kPppChangeTexAlphaScale)));

	int arrayOffset = 0;
	meshList = model0Raw->m_meshes;
	for (unsigned int meshIdx = 0; meshIdx < model0Raw->m_data->m_meshCount; meshIdx++) {
		int pointOffset = 0;
		int colorBase = *(int*)((u8*)work->m_meshColorArrays + arrayOffset);
		int colorPtr = colorBase;
		unsigned int vertCount;
		for (unsigned int v = 0; (vertCount = meshList->m_data->m_vertexCount, v < vertCount); v++) {
			if (step->m_payload[0] == 1) {
				if (*(short*)((char*)meshList->m_points + pointOffset + 2) < splitY) {
					*(char*)(colorPtr + 3) = (char)(int)alphaBase;
				} else {
					*(char*)(colorPtr + 3) = 0;
				}
			} else if (step->m_payload[0] == 2) {
				if (*(short*)((char*)meshList->m_points + pointOffset + 2) > splitY) {
					*(char*)(colorPtr + 3) = (char)(int)alphaBase;
				} else {
					*(char*)(colorPtr + 3) = 0;
				}
			}

			pointOffset += 6;
			colorPtr += 4;
		}

		DCFlushRange((void*)colorBase, vertCount << 2);
		arrayOffset += 4;
		meshList = (ChangeTexMeshRef*)((char*)meshList + sizeof(ChangeTexMeshRef));
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
void pppDestructChangeTex(pppChangeTex* changeTex, pppChangeTexUnkC* data)
{
	Graphic._WaitDrawDone(const_cast<char*>(s_pppChangeTex_cpp), 0x9d);
	int dataOffset = data->m_serializedDataOffsets[2];
	ChangeTexWork* work = (ChangeTexWork*)(changeTex->m_object.m_workArea + dataOffset);
	CCharaPcs::CHandle* handle0 = GetCharaHandlePtr(work->m_charaObj, 0);
	CCharaPcs::CHandle* handle1 = GetCharaHandlePtr(work->m_charaObj, 1);
	CCharaPcs::CHandle* handle2 = GetCharaHandlePtr(work->m_charaObj, 2);
	ChangeTexModelRaw* model = 0;

	if (handle0 != 0) {
		model = reinterpret_cast<ChangeTexModelRaw*>(GetCharaModelPtr(handle0));
		model->m_state = 0;
		model->m_step = 0;
		model->m_beforeDrawCallback = 0;
		model->m_drawMeshDlCallback = 0;
		model->m_afterDrawMeshCallback = 0;
	}
	ChangeTexModelRaw* model1;
	if ((handle1 != 0) && ((model1 = reinterpret_cast<ChangeTexModelRaw*>(GetCharaModelPtr(handle1))), model1 != 0)) {
		model1->m_state = 0;
		model1->m_step = 0;
		model1->m_beforeDrawCallback = 0;
		model1->m_drawMeshDlCallback = 0;
		model1->m_afterDrawMeshCallback = 0;
	}
	ChangeTexModelRaw* model2;
	if ((handle2 != 0) && ((model2 = reinterpret_cast<ChangeTexModelRaw*>(GetCharaModelPtr(handle2))), model2 != 0)) {
		model2->m_state = 0;
		model2->m_step = 0;
		model2->m_beforeDrawCallback = 0;
		model2->m_drawMeshDlCallback = 0;
		model2->m_afterDrawMeshCallback = 0;
	}

	void** stageArray = (void**)work->m_displayListArrays;
	void** meshArray;
	if (stageArray != 0) {
		meshArray = (void**)work->m_meshColorArrays;
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
 * PAL Address: 0x8013f720
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2ChangeTex(pppChangeTex* changeTex, pppChangeTexUnkC* data)
{
	ChangeTexWork* work = (ChangeTexWork*)(changeTex->m_object.m_workArea + data->m_serializedDataOffsets[2]);
	float init = kPppChangeTexInit;

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
void pppConstructChangeTex(pppChangeTex* changeTex, pppChangeTexUnkC* data)
{
	float init = kPppChangeTexInit;
	ChangeTexWork* work = (ChangeTexWork*)(changeTex->m_object.m_workArea + data->m_serializedDataOffsets[2]);

	work->m_value0 = init;
	work->m_value2 = init;
	work->m_value1 = init;
	work->m_charaObj = 0;
	work->m_context = pppMngStPtr;
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
	ChangeTexModelRaw* modelRaw = (ChangeTexModelRaw*)model;
	ChangeTexWork* work = (ChangeTexWork*)param_2;
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

	if (*(u8*)((char*)param_3 + 0x14) != 0) {
		meshColorArrays = work->m_meshColorArrays;
		dlOffset = (int)work->m_texture;
		meshData = meshes[meshIdx].m_data;
		displayList = meshData->m_displayLists;
		if (meshColorArrays != 0) {
			meshColorArray = *(void**)((u8*)meshColorArrays + meshIdx * 4);
			if (meshColorArray != 0) {
				*(void**)(MaterialManRaw() + 4) = meshData->m_normals;
				GXSetArray((GXAttr)0xb, meshColorArray, 4);
				*(int*)(MaterialManRaw() + 0xd0) = dlOffset + 0x28;
				drawTevBits = 0xACE0F;
				fullTevBits = drawTevBits | 0x1000;
				allOnes = -1;
				u8 fullByte = 0xFF;
				tevScale = 0x1e;
				displayListIdx = meshData->m_displayListCount - 1;
				dlOffset = displayListIdx * 4;
				while (displayListIdx >= 0) {
					dlArrayBase = *(int*)(meshIdx * 4 + (int)work->m_displayListArrays);
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
 * PAL Address: 0x8013f8dc
 * PAL Size: 244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void ChangeTex_DrawMeshDLCallback(CChara::CModel* model, void* param_2, void* param_3, int param_4, int param_5, float (*param_6) [4])
{
	ChangeTexModelRaw* modelRaw = (ChangeTexModelRaw*)model;
	ChangeTexWork* work = (ChangeTexWork*)param_2;
	int textureInfo = (int)work->m_texture;
	ChangeTexMeshRef* meshes = modelRaw->m_meshes;
	ChangeTexMeshData* meshData = meshes[param_4].m_data;
	ChangeTexDisplayList* displayList = meshData->m_displayLists + param_5;

	if (*(u8*)((char*)param_3 + 0x14) == 0) {
		int drawTevBits = 0xACE0F;
		int fullTevBits = drawTevBits | 0x1000;
		int zero = 0;
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
		*(int*)(MaterialManRaw() + 0xd0) = textureInfo + 0x28;
		*(int*)(MaterialManRaw() + 0x128) = zero;
		*(int*)(MaterialManRaw() + 0x12c) = tevScale;
		*(int*)(MaterialManRaw() + 0x130) = zero;
		*(int*)(MaterialManRaw() + 0x40) = fullTevBits;
	}

	MaterialMan.SetMaterial(modelRaw->m_data->m_materialSet, displayList->m_material, 0, (_GXTevScale)0);
	GXCallDisplayList(displayList->m_data, displayList->m_size);
}
