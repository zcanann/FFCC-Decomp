#include "global.h"
#include "ffcc/pppKeLns.h"
#include "ffcc/KeLns.h"
#include "ffcc/partMng.h"
#include "dolphin/types.h"
extern "C" {
const float kPppKeLnsZero = 0.0f;
}

STATIC_ASSERT(sizeof(KeLnsDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(KeLnsDataOffsets, m_workOffset) == 0x0);

static inline KeLnsDataOffsets* GetKeLnsDataOffsets(_pppCtrlTable* ctrlTable)
{
	return reinterpret_cast<KeLnsDataOffsets*>(ctrlTable->m_serializedDataOffsets);
}

static inline _KeLnsLp* GetKeLnsLoopWork(_pppPObject* object, _pppCtrlTable* ctrlTable)
{
	return reinterpret_cast<_KeLnsLp*>(object->m_workArea + GetKeLnsDataOffsets(ctrlTable)->m_workOffset);
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
void pppKeLnsLpCon2(_pppPObject* object, _pppCtrlTable* ctrlTable)
{
	_KeLnsLp* keLnsLp = GetKeLnsLoopWork(object, ctrlTable);
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
void pppKeLnsLpCon(_pppPObject* object, _pppCtrlTable* ctrlTable)
{
	_KeLnsLp* keLnsLp = GetKeLnsLoopWork(object, ctrlTable);

	KeLnsLp_Init(keLnsLp);
	f32 zero = kPppKeLnsZero;
	keLnsLp->m_work8C = zero;
	keLnsLp->m_work98 = zero;
}
