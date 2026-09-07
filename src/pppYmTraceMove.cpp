#include "ffcc/pppYmTraceMove.h"
#include "global.h"
#include "ffcc/gobject.h"
#include "ffcc/ppp_linkage.h"
extern "C" {
extern const float kPppYmTraceMoveZero = 0.0f;
extern const float kPppYmTraceMoveOne = 1.0f;
}
#include "ffcc/pppPart.h"
#include "dolphin/mtx.h"

struct pppYmTraceMoveWork {
    Vec m_direction;
    u32 _pad0C;
    Vec m_previousDirection;
    f32 m_distance;
    f32 m_velocity;
    f32 m_acceleration;
};

STATIC_ASSERT(sizeof(YmTraceMoveDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(YmTraceMoveDataOffsets, m_workOffset) == 0x0);

static inline YmTraceMoveDataOffsets* GetYmTraceMoveDataOffsets(_pppCtrlTable* ctrl)
{
	return reinterpret_cast<YmTraceMoveDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline Vec* GetYmTraceMovePreviousPosition(_pppMngSt* pppMngSt)
{
	return &pppMngSt->UserPosition();
}

static inline f32 GetYmTraceMoveScale(_pppMngSt* pppMngSt)
{
	return pppMngSt->m_movementScale;
}

static inline Vec* GetYmTraceMoveBasePosition(_pppMngSt* pppMngSt)
{
	return &pppMngSt->BasePosition();
}

static inline float LoadFloat(const float& value)
{
	return value;
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
void pppFrameYmTraceMove(pppYmTraceMove* pppYmTraceMove, pppYmTraceMoveStep* param_2, _pppCtrlTable* param_3)
{
	if (ppvUserStopPartF != 0) {
		return;
	}

	s32 workOffset = GetYmTraceMoveDataOffsets(param_3)->m_workOffset;
	_pppMngSt* pppMngSt = ppvMng;
	CGObject* lookTarget = pppMngSt->m_lookTarget;
	pppYmTraceMoveWork* work = reinterpret_cast<pppYmTraceMoveWork*>(pppYmTraceMove->m_workArea + workOffset);
	Vec local_20;
	Vec local_2c;
	Vec local_8c;
	Vec local_ec;
	Vec local_f8;
	Quaternion local_60;
	Quaternion local_70;
	Quaternion local_80;

	work->m_velocity = work->m_velocity + work->m_acceleration;
	work->m_distance = work->m_distance + work->m_velocity;

	if (param_2->m_graphId == pppYmTraceMove->m_graphId) {
		work->m_distance = work->m_distance + param_2->m_initWOrk;
		work->m_velocity = work->m_velocity + param_2->m_stepValue;
		work->m_acceleration = work->m_acceleration + param_2->m_arg3;
	}

	if (lookTarget == nullptr) {
		pppCopyVector(local_20, work->m_direction);
		pppCopyVector(local_2c, work->m_previousDirection);
	} else {
		local_8c = lookTarget->m_worldPosition;
		pppSubVector(local_20, local_8c, pppMngSt->m_position);
		local_20.y = local_20.y + param_2->m_payload;
		pppNormalize(local_20, local_20);

		pppCopyVector(work->m_direction, local_20);
		pppSubVector(local_2c, pppMngSt->m_position, *GetYmTraceMovePreviousPosition(pppMngSt));

		if ((local_2c.x == LoadFloat(kPppYmTraceMoveZero)) && (local_2c.y == LoadFloat(kPppYmTraceMoveZero)) &&
		    (local_2c.z == LoadFloat(kPppYmTraceMoveZero))) {
			pppCopyVector(local_2c, work->m_previousDirection);
		}

		pppNormalize(local_2c, local_2c);
	}

	local_60.x = local_20.x;
	local_60.y = local_20.y;
	local_60.z = local_20.z;
	local_60.w = LoadFloat(kPppYmTraceMoveOne);
	local_70.x = local_2c.x;
	local_70.y = local_2c.y;
	local_70.z = local_2c.z;
	local_70.w = local_60.w;
	C_QUATLerp(&local_70, &local_60, &local_80, param_2->m_dataValIndex);
	PSQUATNormalize(&local_80, &local_80);

	local_f8.x = local_80.x;
	local_f8.y = local_80.y;
	local_f8.z = local_80.z;
	PSVECScale(&local_f8, &local_f8, work->m_distance * GetYmTraceMoveScale(pppMngSt));
	pppAddVector(local_ec, local_f8, pppMngSt->m_position);
	pppCopyVector(*GetYmTraceMovePreviousPosition(pppMngSt), pppMngSt->m_position);
	pppCopyVector(pppMngSt->m_position, local_ec);

	ppvMng->m_matrix.value[0][3] = local_ec.x;
	ppvMng->m_matrix.value[1][3] = local_ec.y;
	ppvMng->m_matrix.value[2][3] = local_ec.z;
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
void pppConstructYmTraceMove(pppYmTraceMove* pppYmTraceMove, _pppCtrlTable* param_2)
{
	pppYmTraceMoveWork* work =
	    reinterpret_cast<pppYmTraceMoveWork*>(pppYmTraceMove->m_workArea +
	                                          GetYmTraceMoveDataOffsets(param_2)->m_workOffset);
	_pppMngSt* pppMngSt = ppvMng;
	f32 zero;

	pppSubVector(work->m_previousDirection, pppMngSt->m_paramVec0, *GetYmTraceMoveBasePosition(pppMngSt));
	pppCopyVector(work->m_direction, work->m_previousDirection);
	zero = LoadFloat(kPppYmTraceMoveZero);
	work->m_acceleration = zero;
	work->m_velocity = zero;
	work->m_distance = zero;
}
