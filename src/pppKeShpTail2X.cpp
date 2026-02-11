#include "ffcc/pppKeShpTail2X.h"
#include <dolphin/types.h>
#include <string.h>

/*
 * --INFO--
 * PAL Address: 0x80088e4c
 * PAL Size: 992b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail2X(void)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80088748
 * PAL Size: 1796b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail2XDraw(void)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800886f0
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail2XCon(void* obj, void* param_2)
{
	u32 serializedOffset = **(u32**)((u8*)param_2 + 0xc);
	u8* tail = (u8*)obj + serializedOffset + 0x80;

	*(u16*)(tail + 2) = 0;
	*(u16*)(tail + 4) = 0;
	*(u16*)(tail + 6) = 0;
	tail[1] = 0;
	tail[0] = 0x1f;
	memset(tail + 8, 0, 0x174);
}

/*
 * --INFO--
 * PAL Address: 0x80088698
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail2XDes(void* obj, void* param_2)
{
	u32 serializedOffset = **(u32**)((u8*)param_2 + 0xc);
	u8* tail = (u8*)obj + serializedOffset + 0x80;

	*(u16*)(tail + 2) = 0;
	*(u16*)(tail + 4) = 0;
	*(u16*)(tail + 6) = 0;
	tail[1] = 0;
	tail[0] = 0x1f;
	memset(tail + 8, 0, 0x174);
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void U8ToF32(pppFVECTOR4*, unsigned char*)
{
	// TODO
}
