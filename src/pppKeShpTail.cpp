#include "ffcc/pppKeShpTail.h"
#include "dolphin/types.h"

/*
 * --INFO--
 * PAL Address: 0x80088124
 * PAL Size: 248b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail(void* r3, void* r5)
{
	// Check global flag first
	extern u32 lbl_8032ED70;
	if (lbl_8032ED70 != 0) {
		return;
	}
	
	// Get data structures
	u32* r5_ptr = (u32*)((u8*)r5 + 0xc);
	u32* r3_ptr = (u32*)((u8*)r3 + 0xc);
	u32 r4_val = *r5_ptr;
	r4_val = *(u32*)r4_val;
	
	if (*r3_ptr == 0) {
		// Load vector data from r3
		float* vec_src = (float*)((u8*)r3 + 0x1c); // f2, f1, f0
		float vec[3];
		vec[0] = vec_src[0];    // 0x1c
		vec[1] = vec_src[4];    // 0x2c  
		vec[2] = vec_src[8];    // 0x3c
		
		// Call pppCopyVector 
		extern void pppCopyVector__FR3Vec3Vec(void*, void*);
		pppCopyVector__FR3Vec3Vec(vec, r3);
		
		// Get tail structure
		u8* tail = (u8*)r3 + r4_val + 0x80;
		u8 count = *tail;
		
		// Loop through tail elements
		u8* current = tail + 8;
		for (int i = 0; i < count; i++) {
			pppCopyVector__FR3Vec3Vec(current, vec);
			current += 12;
		}
	}
	
	// Tail count management
	u8* tail = (u8*)r3 + r4_val + 0x80;
	if (tail[1] == 0) {
		tail[1] = tail[0];
	}
	tail[1]--;
}

/*
 * --INFO--
 * PAL Address: 0x800880f4
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTailCon(void* r3, void* r4)
{
	// Assembly analysis:
	// lwz r5, 0xc(r4) -> r5 = *(u32*)(r4 + 0xc)
	// lwz r5, 0x0(r5) -> r5 = *(u32*)r5  
	// addi r5, r5, 0x80 -> r5 = r5 + 0x80
	// add r5, r3, r5 -> r5 = r3 + r5
	// Zero out bytes at offsets 2,4,6,1 and set byte 0 to 31
	
	u32* ptr4 = (u32*)((u8*)r4 + 0xc);
	u32 offset = *ptr4;
	offset = *(u32*)offset;
	u8* target = (u8*)r3 + offset + 0x80;
	
	*(u16*)(target + 2) = 0;
	*(u16*)(target + 4) = 0;
	*(u16*)(target + 6) = 0;
	*(u8*)(target + 1) = 0;
	*(u8*)target = 31;
}

/*
 * --INFO--
 * PAL Address: 0x800880f0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTailDraw(void)
{
	return;
}