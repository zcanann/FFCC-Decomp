#include "ffcc/pppKeLns.h"
#include "ffcc/KeLns.h"
#include "ffcc/partMng.h"
#include "dolphin/types.h"
extern "C" {
const float kPppKeLnsZero = 0.0f;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppKeLnsFlsDraw(_pppPObject* obj, pppNoStep* stepData, _pppCtrlTable* ctrlTable)
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
void pppKeLnsLpDraw(_pppPObject* obj, pppNoStep* stepData, _pppCtrlTable* ctrlTable)
{
	(void)obj;
	(void)stepData;
	(void)ctrlTable;
	return;
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
	_pppPObject* object = (_pppPObject*)pObject;
	_pppCtrlTable* ctrlTable = (_pppCtrlTable*)pPart;
	u32 offset = ctrlTable->m_serializedDataOffsets[0];
	_KeLnsLp* keLnsLp = (_KeLnsLp*)(object->m_workArea + offset);
	f32 zero = kPppKeLnsZero;

	keLnsLp->m_work8C = zero;
	keLnsLp->m_work98 = zero;
}

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
	_pppPObject* object = (_pppPObject*)pObject;
	_pppCtrlTable* ctrlTable = (_pppCtrlTable*)pPart;
	u32 offset = ctrlTable->m_serializedDataOffsets[0];
	_KeLnsLp* keLnsLp = (_KeLnsLp*)(object->m_workArea + offset);

	KeLnsLp_Init(keLnsLp);
	f32 zero = kPppKeLnsZero;
	keLnsLp->m_work8C = zero;
	keLnsLp->m_work98 = zero;
}
