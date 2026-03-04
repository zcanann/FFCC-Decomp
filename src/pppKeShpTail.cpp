#include "ffcc/pppKeShpTail.h"
#include "ffcc/pppPart.h"
#include "dolphin/mtx.h"
#include "dolphin/types.h"

struct KeShpTailOffsets {
    u8 _pad0[0xc];
    s32* m_serializedDataOffsets;
};

struct KeShpTailWork {
    u8 m_count;
    u8 m_head;
    u16 m_field2;
    u16 m_field4;
    u16 m_field6;
    Vec m_posHistory[31];
};

struct KeShpTailObject {
    u8 _pad0[0xc];
    _pppPObject m_obj;
};

/*
 * --INFO--
 * PAL Address: 0x80088124
 * PAL Size: 248b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail(_pppPObject* obj, UnkB*, UnkC* offsets)
{
	extern int lbl_8032ED70;
	KeShpTailObject* tailObj = (KeShpTailObject*)obj;
	KeShpTailWork* work;
	if (lbl_8032ED70 != 0) {
		return;
	}

	work = (KeShpTailWork*)((u8*)obj + ((KeShpTailOffsets*)offsets)->m_serializedDataOffsets[0] + 0x80);
	if (tailObj->m_obj.m_graphId == 0) {
		Vec local_14;
		Vec local_20;

		local_20.x = tailObj->m_obj.m_localMatrix.value[0][3];
		local_20.y = tailObj->m_obj.m_localMatrix.value[1][3];
		local_20.z = tailObj->m_obj.m_localMatrix.value[2][3];
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
	KeShpTailWork* work = (KeShpTailWork*)((u8*)r3 + ((KeShpTailOffsets*)r4)->m_serializedDataOffsets[0] + 0x80);
	work->m_field2 = 0;
	work->m_field4 = 0;
	work->m_field6 = 0;
	work->m_head = 0;
	work->m_count = 0x1f;
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
