#include "ffcc/pppPObjPoint.h"
#include <dolphin/types.h>

// External global flags (from @sda21 addressing)
extern u32 lbl_8032ED70;
extern void* lbl_8032ED50;
extern void* lbl_801EADC8;

/*
 * --INFO--
 * PAL Address: 0x80065c44  
 * PAL Size: 148b
 */
void pppPObjPoint(void* obj, void* param1, void* param2)
{
	// Early return if global flag is set
	if (lbl_8032ED70 != 0) {
		return;
	}
	
	// Get values from parameter structures  
	void* param1_data = *(void**)((char*)param2 + 0x0c);
	u32 param1_val = *(u32*)((char*)param1 + 0x00);
	u32 obj_val = *(u32*)((char*)obj + 0x0c);
	void* param1_ptr = *(void**)((char*)param1_data + 0x00);
	
	// Calculate target offset in object
	void* target = (char*)obj + (u32)param1_ptr + 0x80;
	
	// Compare values and branch
	if (param1_val != obj_val) {
		// Complex case - calculate pointer based on param values
		u32 param2_val = *(u32*)((char*)param1 + 0x04);
		
		if ((param2_val + 1) == 0xFFFF) {
			// Special case - use static data
			*(void**)((char*)target + 0x10) = lbl_801EADC8;
		} else {
			// Calculate dynamic pointer
			void* base = lbl_8032ED50;
			void* data_ptr = *(void**)((char*)base + 0xd4);
			u32 offset = param2_val << 4;  // slwi r0, r3, 4
			void* calc_base = (char*)data_ptr + offset;
			void* param3_base = *(void**)((char*)param1 + 0x08);
			void* final_offset = *(void**)((char*)calc_base + 0x04);
			void* result = (char*)param3_base + (u32)final_offset + 0x80;
			*(void**)((char*)target + 0x10) = result;
		}
	}
	
	// Copy float data (x, y, z components)
	void* src = *(void**)((char*)target + 0x10);
	f32 x = *(f32*)((char*)src + 0x00);
	*(f32*)((char*)target + 0x00) = x;
	
	f32 y = *(f32*)((char*)src + 0x04); 
	*(f32*)((char*)target + 0x04) = y;
	
	f32 z = *(f32*)((char*)src + 0x08);
	*(f32*)((char*)target + 0x08) = z;
}