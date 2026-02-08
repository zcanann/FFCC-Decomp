#include "ffcc/pppYmTraceMove.h"
#include "ffcc/partMng.h"
#include "dolphin/mtx.h"

extern int DAT_8032ed70;

extern "C" {
	void pppCopyVector__FR3Vec3Vec(Vec*, const Vec*);
	void pppSubVector__FR3Vec3Vec3Vec(Vec*, const Vec*, const Vec*);
}

/*
 * --INFO--
 * PAL Address: 0x800d4bd0
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmTraceMove(pppYmTraceMove* pppYmTraceMove, UnkC* param_2)
{
	Vec local_38;
	Vec local_2c;
	Vec dest;
	Vec temp1;

	(void)pppYmTraceMove;
	(void)param_2;

	local_2c.x = 0.0f;
	local_2c.y = 0.0f;
	local_2c.z = 0.0f;
	temp1.x = 1.0f;
	temp1.y = 1.0f;
	temp1.z = 1.0f;
	pppSubVector__FR3Vec3Vec3Vec(&dest, &temp1, &local_2c);
	local_38.x = dest.x;
	local_38.y = dest.y;
	local_38.z = dest.z;
	pppCopyVector__FR3Vec3Vec(&dest, &local_38);
	dest.x = 0.0f;
	dest.y = 0.0f;
	dest.z = 0.0f;
}

/*
 * --INFO--
 * PAL Address: 0x800d4828
 * PAL Size: 936b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmTraceMove(pppYmTraceMove* pppYmTraceMove, UnkB* param_2, UnkC* param_3)
{
	Vec* dest;
	Vec local_98;
	Vec local_8c;
	Vec local_2c;
	Vec local_20;

	if (DAT_8032ed70 != 0) {
		return;
	}

	dest = (Vec*)((u8*)(&pppYmTraceMove->field0_0x0 + 2) + *param_3->m_serializedDataOffsets);
	dest[2].z = dest[2].z + dest[3].x;
	dest[2].y = dest[2].y + dest[2].z;

	if (param_2->m_graphId == pppYmTraceMove->field0_0x0.m_graphId) {
		dest[2].y = dest[2].y + (f32)param_2->m_initWOrk;
		dest[2].z = dest[2].z + param_2->m_stepValue;
		dest[3].x = dest[3].x + (f32)param_2->m_arg3;
	}

	local_8c.x = dest->x;
	local_8c.y = dest->y;
	local_8c.z = dest->z;
	pppCopyVector__FR3Vec3Vec(&local_20, &local_8c);

	local_98.x = dest[1].y;
	local_98.y = dest[1].z;
	local_98.z = dest[2].x;
	pppCopyVector__FR3Vec3Vec(&local_2c, &local_98);
}
