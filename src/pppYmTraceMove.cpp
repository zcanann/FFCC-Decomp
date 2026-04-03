#include "ffcc/pppYmTraceMove.h"
#include "ffcc/symbols_shared.h"
#include "ffcc/pppPart.h"
#include "dolphin/mtx.h"

extern "C" {
void pppNormalize__FR3Vec3Vec(float*, Vec*);
}

struct pppYmTraceMoveWork {
	Vec m_direction;
	u32 _pad0C;
	Vec m_previousDirection;
	f32 m_distance;
	f32 m_velocity;
	f32 m_acceleration;
};

struct pppYmTraceMoveMngStRaw {
	char pad00[0x08];
	Vec m_position;
	char pad14[0x34];
	Vec m_historyDirection;
	f32 m_scale;
	Vec m_savedPosition;
	u32 _pad64;
	Vec m_paramVec0;
	char pad74[0x64];
	void* m_owner;
};

/*
 * --INFO--
 * PAL Address: 0x800d4bd0
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmTraceMove(pppYmTraceMove* pppYmTraceMove, pppYmTraceMoveUnkC* param_2)
{
	pppYmTraceMoveMngStRaw* pppMngSt;
	pppYmTraceMoveWork* work;
	f32 zero;

	pppMngSt = (pppYmTraceMoveMngStRaw*)pppMngStPtr;
	work = (pppYmTraceMoveWork*)((u8*)pppYmTraceMove + 0x80 + *param_2->m_serializedDataOffsets);
	pppSubVector(work->m_previousDirection, pppMngSt->m_paramVec0, pppMngSt->m_savedPosition);
	pppCopyVector(work->m_direction, work->m_previousDirection);
	zero = kPppYmTraceMoveZero;
	work->m_acceleration = zero;
	work->m_velocity = zero;
	work->m_distance = zero;
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
void pppFrameYmTraceMove(pppYmTraceMove* pppYmTraceMove, pppYmTraceMoveUnkB* param_2, pppYmTraceMoveUnkC* param_3)
{
	pppYmTraceMoveMngStRaw* pppMngSt;
	pppYmTraceMoveWork* work;
	u8* owner;
	Vec local_128;
	Vec local_11c;
	Vec local_110;
	Vec local_ec;
	Vec local_e0;
	Vec local_8c;
	Vec local_74;
	Vec local_5c;
	Vec local_44;
	Vec local_2c;
	Vec local_20;
	Quaternion local_80;
	Quaternion local_70;
	Quaternion local_60;

	if (gPppCalcDisabled != 0) {
		return;
	}

	pppMngSt = (pppYmTraceMoveMngStRaw*)pppMngStPtr;
	work = (pppYmTraceMoveWork*)((u8*)pppYmTraceMove + 0x80 + *param_3->m_serializedDataOffsets);
	owner = (u8*)pppMngSt->m_owner;

	work->m_velocity = work->m_velocity + work->m_acceleration;
	work->m_distance = work->m_distance + work->m_velocity;

	if (param_2->m_graphId == pppYmTraceMove->m_graphId) {
		work->m_distance = work->m_distance + param_2->m_initWOrk;
		work->m_velocity = work->m_velocity + param_2->m_stepValue;
		work->m_acceleration = work->m_acceleration + param_2->m_arg3;
	}

	if (owner == nullptr) {
		pppCopyVector(local_20, work->m_direction);
		pppCopyVector(local_2c, work->m_previousDirection);
	} else {
		local_74.x = *(f32*)(owner + 0x15c);
		local_74.y = *(f32*)(owner + 0x160);
		local_74.z = *(f32*)(owner + 0x164);
		pppSubVector(local_20, local_74, pppMngSt->m_position);

		local_20.y = local_20.y + param_2->m_payload;
		local_5c.x = local_20.x;
		local_5c.y = local_20.y;
		local_5c.z = local_20.z;
		pppNormalize__FR3Vec3Vec((float*)&local_20, &local_5c);

		pppCopyVector(work->m_direction, local_20);
		pppSubVector(local_2c, pppMngSt->m_position, pppMngSt->m_historyDirection);

		if ((local_2c.x == 0.0f) && (local_2c.y == 0.0f) && (local_2c.z == 0.0f)) {
			pppCopyVector(local_2c, work->m_previousDirection);
		}

		local_44.x = local_2c.x;
		local_44.y = local_2c.y;
		local_44.z = local_2c.z;
		pppNormalize__FR3Vec3Vec((float*)&local_2c, &local_44);
	}

	local_60.x = local_20.x;
	local_60.y = local_20.y;
	local_60.z = local_20.z;
	local_60.w = 1.0f;
	local_70.x = local_2c.x;
	local_70.y = local_2c.y;
	local_70.z = local_2c.z;
	local_70.w = 1.0f;
	C_QUATLerp(&local_70, &local_60, &local_80, param_2->m_dataValIndex);
	PSQUATNormalize(&local_80, &local_80);

	local_8c.x = local_80.x;
	local_8c.y = local_80.y;
	local_8c.z = local_80.z;
	PSVECScale(&local_8c, &local_8c, work->m_distance * pppMngSt->m_scale);

	pppCopyVector(local_110, pppMngSt->m_position);
	pppCopyVector(local_e0, local_8c);
	pppAddVector(local_ec, local_e0, local_110);

	pppCopyVector(local_11c, pppMngSt->m_position);
	pppCopyVector(pppMngSt->m_historyDirection, local_11c);

	local_128.x = local_ec.x;
	local_128.y = local_ec.y;
	local_128.z = local_ec.z;
	pppCopyVector(pppMngSt->m_position, local_128);

	pppMngStPtr->m_matrix.value[0][3] = local_ec.x;
	pppMngStPtr->m_matrix.value[1][3] = local_ec.y;
	pppMngStPtr->m_matrix.value[2][3] = local_ec.z;
}
