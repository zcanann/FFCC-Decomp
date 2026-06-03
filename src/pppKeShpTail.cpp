#include "ffcc/pppKeShpTail.h"
#include "ffcc/linkage.h"
#include "ffcc/pppPart.h"
#include "dolphin/mtx.h"
#include "dolphin/types.h"
#include "ffcc/ppp_linkage.h"

STATIC_ASSERT(sizeof(KeShpTailWork) == 0x17C);
STATIC_ASSERT(offsetof(KeShpTailWork, m_count) == 0x00);
STATIC_ASSERT(offsetof(KeShpTailWork, m_head) == 0x01);
STATIC_ASSERT(offsetof(KeShpTailWork, m_posHistory) == 0x08);

/*
 * --INFO--
 * PAL Address: 0x800880f0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTailDraw(_pppPObject* obj, void* stepData, _pppCtrlTable* ctrlTable)
{
	(void)obj;
	(void)stepData;
	(void)ctrlTable;
	return;
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
	KeShpTailWork* work = (KeShpTailWork*)(obj->m_workArea + ctrlTable->m_serializedDataOffsets[0]);
	work->m_field2 = 0;
	work->m_field4 = 0;
	work->m_field6 = 0;
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
void pppKeShpTail(_pppPObject* obj, pppKeShpTailUnkB*, _pppCtrlTable* offsets)
{
	KeShpTailWork* work;
	if (ppvUserStopPartF != 0) {
		return;
	}

	work = (KeShpTailWork*)(obj->m_workArea + offsets->m_serializedDataOffsets[0]);
	if (obj->m_graphId == 0) {
		Vec local_14 ATTRIBUTE_ALIGN(8);
		Vec local_20;

		local_20.x = obj->m_localMatrix.value[0][3];
		local_20.y = obj->m_localMatrix.value[1][3];
		local_20.z = obj->m_localMatrix.value[2][3];
		pppCopyVector(local_14, local_20);

		Vec* tailVec = work->m_posHistory;
		s32 count = work->m_count;
		for (; count > 0; count--) {
			pppCopyVector(*tailVec, local_14);
			tailVec++;
		}
	}

	if (work->m_head == 0) {
		work->m_head = work->m_count;
	}
	work->m_head--;
}
