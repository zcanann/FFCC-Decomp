#include "ffcc/pppChangeTex.h"
#include "dolphin/gx.h"

// Simple approach using direct memory access 
extern char MaterialMan[];
extern void SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(void*, void*, unsigned int, int, int);
extern void GXCallDisplayList(void*, unsigned int);

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
 * Address:	8013f744
 * Size:	64b
 */
void pppConstructChangeTex(void)
{
	// Simple initialization pattern
	float data[16];
	
	data[0] = 0.0f;
	data[1] = 0.0f; 
	data[2] = 0.0f;
	data[3] = 0.0f;
	data[4] = 0.0f;
	data[6] = 0.0f;
	data[7] = 0.0f;
	data[9] = 0.0f;
}

/*
 * --INFO--
 * Address:	8013f720
 * Size:	36b
 */
void pppConstruct2ChangeTex(void)
{
	// Simple stub
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDestructChangeTex(void)
{
	// TODO
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
void pppFrameChangeTex(void)
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
 * Address:	TODO
 * Size:	TODO
 */
void pppRenderChangeTex(void)
{
	// TODO
}
