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
	Vec m_previousPosition;
	f32 m_scale;
	Vec m_basePosition;
	u32 _pad64;
	Vec m_paramVec0;
	char pad74[0x68];
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
	pppYmTraceMoveWork* work = (pppYmTraceMoveWork*)((u8*)pppYmTraceMove + 0x80 + *param_2->m_serializedDataOffsets);
	pppYmTraceMoveMngStRaw* pppMngSt = (pppYmTraceMoveMngStRaw*)pppMngStPtr;
	f32 zero;

	pppSubVector(work->m_previousDirection, pppMngSt->m_paramVec0, pppMngSt->m_basePosition);
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
	if (gPppCalcDisabled != 0) {
		return;
	}

	pppYmTraceMoveMngStRaw* pppMngSt = (pppYmTraceMoveMngStRaw*)pppMngStPtr;
	pppYmTraceMoveWork* work =
		(pppYmTraceMoveWork*)((u8*)pppYmTraceMove + 0x80 + *param_3->m_serializedDataOffsets);
	void* owner = pppMngSt->m_owner;
	Vec local_20;
	Vec local_2c;
	Vec local_8c;
	Vec local_ec;
	Vec local_e0;
	Quaternion local_60;
	Quaternion local_70;
	Quaternion local_80;
	Vec directionSource;
	Vec previousDirectionSource;

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
		u8* ownerBytes = (u8*)owner;

		local_8c.x = *(f32*)(ownerBytes + 0x15c);
		local_8c.y = *(f32*)(ownerBytes + 0x160);
		local_8c.z = *(f32*)(ownerBytes + 0x164);
		pppSubVector(local_20, local_8c, pppMngSt->m_position);

		local_20.y = local_20.y + param_2->m_payload;
		directionSource = local_20;
		pppNormalize__FR3Vec3Vec((float*)&local_20, &directionSource);

		pppCopyVector(work->m_direction, local_20);
		pppSubVector(local_2c, pppMngSt->m_position, pppMngSt->m_previousPosition);

		if ((local_2c.x == kPppYmTraceMoveZero) && (local_2c.y == kPppYmTraceMoveZero) &&
		    (local_2c.z == kPppYmTraceMoveZero)) {
			pppCopyVector(local_2c, work->m_previousDirection);
		}

		previousDirectionSource = local_2c;
		pppNormalize__FR3Vec3Vec((float*)&local_2c, &previousDirectionSource);
	}

	local_60.x = local_20.x;
	local_60.y = local_20.y;
	local_60.z = local_20.z;
	local_60.w = kPppYmTraceMoveOne;
	local_70.x = local_2c.x;
	local_70.y = local_2c.y;
	local_70.z = local_2c.z;
	local_70.w = kPppYmTraceMoveOne;
	C_QUATLerp(&local_70, &local_60, &local_80, param_2->m_dataValIndex);
	PSQUATNormalize(&local_80, &local_80);

	local_e0.x = local_80.x;
	local_e0.y = local_80.y;
	local_e0.z = local_80.z;
	PSVECScale(&local_e0, &local_e0, work->m_distance * pppMngSt->m_scale);
	pppAddVector(local_ec, local_e0, pppMngSt->m_position);
	pppCopyVector(pppMngSt->m_previousPosition, pppMngSt->m_position);
	pppCopyVector(pppMngSt->m_position, local_ec);

	pppMngStPtr->m_matrix.value[0][3] = local_ec.x;
	pppMngStPtr->m_matrix.value[1][3] = local_ec.y;
	pppMngStPtr->m_matrix.value[2][3] = local_ec.z;
}
