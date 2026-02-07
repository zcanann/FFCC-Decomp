#include "ffcc/pppChangeTex.h"
#include "ffcc/graphic.h"
#include "dolphin/gx.h"

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
extern float FLOAT_80332040;

extern "C" {
	int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh* mapMesh, CMaterialSet* materialSet, int& textureIndex);
	void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int stage, int rasSel, int texSel);
	void pppInitBlendMode__Fv(void);
	void _WaitDrawDone__8CGraphicFPci(CGraphic* graphic, const char* file, int line);
	void* GetCharaHandlePtr__FP8CGObjectl(void* obj, long index);
	int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void* handle);
	void pppHeapUseRate__FPQ27CMemory6CStage(void* stage);
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
void ChangeTex_DrawMeshDLCallback(CChara::CModel* model, void* param_2, void* param_3, int param_4, int param_5, float (*param_6) [4])
{
	char flag = *(char*)((char*)param_3 + 0x14);
	
	if (flag == 0) {
		// Set MaterialMan field at offset 0xd0 to param_2 + 0x1c + 0x28
		int offset = (int)param_2 + 0x1c + 0x28;
		*(int*)(MaterialMan + 0xd0) = offset;
		
		// Set other MaterialMan fields based on Ghidra decomp
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
	
	// Get display list info
	char* meshes = (char*)model + 0xac;
	void* mesh_data = *(void**)(meshes + param_4 * 0x14 + 8);
	void* display_lists = *(void**)((char*)mesh_data + 0x50);
	void* display_list = (void*)((char*)display_lists + param_5 * 0xc);
	
	// Call SetMaterial
	void* model_data = *(void**)((char*)model + 0xa4);
	void* material_set = *(void**)((char*)model_data + 0x24);
	unsigned short material_id = *(unsigned short*)((char*)display_list + 8);
	SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(MaterialMan, material_set, material_id, 0, 0);
	
	// Call GXCallDisplayList if flag allows
	if (flag == 1 || flag == 0) {
		void* dl_data = *(void**)display_list;
		unsigned int dl_size = *(unsigned int*)((char*)display_list + 4);
		GXCallDisplayList(dl_data, dl_size);
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
void ChangeTex_AfterDrawMeshCallback(CChara::CModel* model, void* param_2, void* param_3, int param_4, float (*param_5) [4])
{
	if (*(char*)((char*)param_3 + 0x14) != 0) {
		int texture_info = *(int*)((char*)param_2 + 0x1c);
		
		// Get mesh data
		char* meshes = (char*)model + 0xac;
		void* mesh_data = *(void**)(meshes + param_4 * 0x14 + 8);
		void* display_lists = *(void**)((char*)mesh_data + 0x50);
		
		// Check if there are vertex arrays
		if (*(int*)((char*)param_2 + 0xc) != 0) {
			int vertex_array = *(int*)(*(int*)((char*)param_2 + 0xc) + param_4 * 4);
			if (vertex_array != 0) {
				// Set up vertex array in MaterialMan
				*(void**)(MaterialMan + 0x4) = *(void**)((char*)mesh_data + 0x20); // normals
				extern void GXSetArray(unsigned int, void*, unsigned char);
				GXSetArray(0xb, (void*)vertex_array, 4);
				
				// Set MaterialMan offset based on flag
				char flag = *(char*)((char*)param_3 + 0x14);
				if ((flag == 2) || (flag == 3)) {
					*(int*)(MaterialMan + 0x208) = 0;
				} else {
					*(int*)(MaterialMan + 0x208) = texture_info + 0x28;
				}
				
				// Process display lists in reverse order
				int display_list_count = *(int*)((char*)mesh_data + 0x4c);
				for (int i = display_list_count - 1; i >= 0; i--) {
					// Get display list data for current index
					int display_list_array = *(int*)(*(int*)((char*)param_2 + 0x10) + param_4 * 4);
					void* display_list = (void*)((char*)display_lists + i * 0xc);
					
					// Set MaterialMan fields
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
					
					// Call SetMaterial
					void* model_data = *(void**)((char*)model + 0xa4);
					void* material_set = *(void**)((char*)model_data + 0x24);
					unsigned short material_id = *(unsigned short*)((char*)display_list + 8);
					SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(MaterialMan, material_set, material_id, 0, 0);
					
					// Call display list
					void** dl_array = (void**)(display_list_array + i * 4);
					void* dl_data = *dl_array;
					unsigned int dl_size = *((unsigned int*)dl_array + 1);
					GXCallDisplayList(dl_data, dl_size);
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
	float init = FLOAT_80332040;
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
	float init = FLOAT_80332040;

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
	int model = 0;
	int dataOffset = data->m_serializedDataOffsets[2];
	void* handle0;
	void* handle1;
	void* handle2;

	_WaitDrawDone__8CGraphicFPci(&Graphic, "pppChangeTex.cpp", 0x9d);

	handle0 = GetCharaHandlePtr__FP8CGObjectl(*(void**)((char*)changeTex + 0x98 + dataOffset), 0);
	handle1 = GetCharaHandlePtr__FP8CGObjectl(*(void**)((char*)changeTex + 0x98 + dataOffset), 1);
	handle2 = GetCharaHandlePtr__FP8CGObjectl(*(void**)((char*)changeTex + 0x98 + dataOffset), 2);

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

	void** stageArray = *(void***)((char*)changeTex + 0x90 + dataOffset);
	void** meshArray = *(void***)((char*)changeTex + 0x8c + dataOffset);
	if ((stageArray == 0) || (meshArray == 0)) {
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

	pppHeapUseRate__FPQ27CMemory6CStage(*(void**)((char*)changeTex + 0x90 + dataOffset));
	pppHeapUseRate__FPQ27CMemory6CStage(*(void**)((char*)changeTex + 0x8c + dataOffset));
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
void pppFrameChangeTex(pppChangeTex*, UnkB*, UnkC*)
{
	// TODO: This is a very complex function that needs proper type definitions
	// Basic structure from Ghidra decomp shows:
	// - Checks DAT_8032ed70 == 0
	// - Gets character handles and models
	// - Calls CalcGraphValue
	// - Sets up callback functions
	// - Allocates memory for display list modifications
	// - Processes texture animations based on vertex positions
	// - Handles different payload types (0x01, 0x02)
	
	// This requires extensive type definitions and external function declarations
	// that aren't available yet. Will need:
	// - pppChangeTex type definition
	// - UnkB, UnkC type definitions  
	// - Various ppp* functions
	// - Character system functions
	// - Memory allocation functions
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
	unsigned int local_8[2];

	if (step->m_dataValIndex != 0xffff) {
		local_8[0] = 0;
		GetTexture__8CMapMeshFP12CMaterialSetRi(
		    lbl_8032ED54->m_mapMeshPtr[step->m_dataValIndex], lbl_8032ED54->m_materialSetPtr, (int&)local_8[0]);
		_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
		pppInitBlendMode__Fv();
	}
}
