#include "ffcc/pppKeLns.h"
#include "ffcc/KeLns.h"
#include "dolphin/types.h"
#include "ffcc/symbols_shared.h"

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

	KeLnsLp_Init(keLnsLp);
	f32 zero = kPppKeLnsZero;
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
	f32 zero = kPppKeLnsZero;

	*(f32*)(keLnsLp + 0x8C) = zero;
	*(f32*)(keLnsLp + 0x98) = zero;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppKeLnsLpDraw(_pppPObject* obj, void* stepData, _pppCtrlTable* ctrlTable)
{
	(void)obj;
	(void)stepData;
	(void)ctrlTable;
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppKeLnsFlsCon(_pppPObjLink* obj, _pppCtrlTable* ctrlTable)
{
	(void)obj;
	(void)ctrlTable;
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppKeLnsFlsDraw(_pppPObject* obj, void* stepData, _pppCtrlTable* ctrlTable)
{
	(void)obj;
	(void)stepData;
	(void)ctrlTable;
	return;
}
