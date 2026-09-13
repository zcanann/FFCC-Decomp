#include "ffcc/pppKeShpTail.h"
#include "ffcc/linkage.h"
#include "ffcc/pppPart.h"
#include "dolphin/mtx.h"
#include "dolphin/types.h"
#include "ffcc/ppp_linkage.h"

struct KeShpTailWork {
	u8 m_count;
	u8 m_head;
	u16 m_frameAcc;
	u16 m_shapeFrame;
	u16 m_shapePrevFrame;
	Vec m_posHistory[31];
};

STATIC_ASSERT(sizeof(KeShpTailWork) == 0x17C);
STATIC_ASSERT(offsetof(KeShpTailWork, m_count) == 0x00);
STATIC_ASSERT(offsetof(KeShpTailWork, m_head) == 0x01);
STATIC_ASSERT(offsetof(KeShpTailWork, m_frameAcc) == 0x02);
STATIC_ASSERT(offsetof(KeShpTailWork, m_shapeFrame) == 0x04);
STATIC_ASSERT(offsetof(KeShpTailWork, m_shapePrevFrame) == 0x06);
STATIC_ASSERT(offsetof(KeShpTailWork, m_posHistory) == 0x08);
STATIC_ASSERT(sizeof(KeShpTailDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(KeShpTailDataOffsets, m_workOffset) == 0x0);

static inline KeShpTailDataOffsets* GetKeShpTailDataOffsets(_pppCtrlTable* ctrlTable)
{
	return reinterpret_cast<KeShpTailDataOffsets*>(ctrlTable->m_serializedDataOffsets);
}

static inline KeShpTailWork* GetKeShpTailWork(_pppPObject* obj, _pppCtrlTable* ctrlTable)
{
	return reinterpret_cast<KeShpTailWork*>(obj->m_workArea + GetKeShpTailDataOffsets(ctrlTable)->m_workOffset);
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
void pppKeShpTailDraw(_pppPObject*, pppKeShpTailStep*, _pppCtrlTable*)
{
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
void pppKeShpTailCon(_pppPObject* obj, _pppCtrlTable* ctrlTable)
{
	KeShpTailWork* work = GetKeShpTailWork(obj, ctrlTable);
	work->m_frameAcc = 0;
	work->m_shapeFrame = 0;
	work->m_shapePrevFrame = 0;
	work->m_head = 0;
	work->m_count = 0x1f;
}

/*
 * --INFO--
 * PAL Address: 0x80088124
 * PAL Size: 248b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail(_pppPObject* obj, pppKeShpTailStep*, _pppCtrlTable* ctrlTable)
{
	KeShpTailWork* work;
	if (ppvUserStopPartF != 0) {
		return;
	}

	work = GetKeShpTailWork(obj, ctrlTable);
	if (obj->m_graphId == 0) {
		Vec historyPos ATTRIBUTE_ALIGN(8);
		Vec initPos;

		initPos.x = obj->m_localMatrix.value[0][3];
		initPos.y = obj->m_localMatrix.value[1][3];
		initPos.z = obj->m_localMatrix.value[2][3];
		pppCopyVector(historyPos, initPos);

		Vec* history = work->m_posHistory;
		s32 count = work->m_count;
		for (; count > 0; count--) {
			pppCopyVector(*history, historyPos);
			history++;
		}
	}

	if (work->m_head == 0) {
		work->m_head = work->m_count;
	}
	work->m_head--;
}
