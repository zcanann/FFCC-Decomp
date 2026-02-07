#include "ffcc/pppKeLns.h"
#include "ffcc/KeLns.h"
#include "dolphin/types.h"

/*
 * --INFO--
 * PAL Address: 0x800957d4
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeLnsLpCon(void* pObject, void* pPart)
{
	u32 offset = *(u32*)*(u32*)((u8*)pPart + 0xC);
	_KeLnsLp* keLnsLp = (_KeLnsLp*)((u8*)pObject + offset + 0x80);
	f32 zero = 0.0f;

	KeLnsLp_Init(keLnsLp);
	*(f32*)((u8*)keLnsLp + 0x8C) = zero;
	*(f32*)((u8*)keLnsLp + 0x98) = zero;
}

/*
 * --INFO--
 * PAL Address: 0x800957b4
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeLnsLpCon2(void* pObject, void* pPart)
{
	u32 offset = *(u32*)*(u32*)((u8*)pPart + 0xC);
	u8* keLnsLp = (u8*)pObject + offset + 0x80;
	f32 zero = 0.0f;

	*(f32*)(keLnsLp + 0x8C) = zero;
	*(f32*)(keLnsLp + 0x98) = zero;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppKeLnsLpDraw(void)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppKeLnsFlsCon(void)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppKeLnsFlsDraw(void)
{
	return;
}
