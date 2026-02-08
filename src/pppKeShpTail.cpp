#include "ffcc/pppKeShpTail.h"
#include "ffcc/pppPart.h"
#include "dolphin/mtx.h"
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
void pppKeShpTail(void* obj, void* param_2)
{
	extern int lbl_8032ED70;
	if (lbl_8032ED70 != 0) {
		return;
	}

	u32 serializedOffset = **(u32**)((u8*)param_2 + 0xc);
	if (*(u32*)((u8*)obj + 0xc) == 0) {
		Vec local_14;
		Vec local_30;
		local_14.x = *(f32*)((u8*)obj + 0x1c);
		local_14.y = *(f32*)((u8*)obj + 0x2c);
		local_14.z = *(f32*)((u8*)obj + 0x3c);
		pppCopyVector(local_30, local_14);

		u8* tail = (u8*)obj + serializedOffset + 0x80;
		u8 count = tail[0];
		u8* tailVec = tail + 8;
		while (count != 0) {
			pppCopyVector(*(Vec*)tailVec, local_30);
			tailVec += 0xc;
			count--;
		}
	}

	u8* tail = (u8*)obj + serializedOffset + 0x80;
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
void pppKeShpTailCon(void* obj, void* param_2)
{
	u32 serializedOffset = **(u32**)((u8*)param_2 + 0xc);
	u8* tail = (u8*)obj + serializedOffset + 0x80;

	*(u16*)(tail + 2) = 0;
	*(u16*)(tail + 4) = 0;
	*(u16*)(tail + 6) = 0;
	tail[1] = 0;
	tail[0] = 0x1f;
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
