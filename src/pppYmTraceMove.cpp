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
void pppFrameYmTraceMove(pppYmTraceMove* pppYmTraceMove, pppYmTraceMoveStep* step, _pppCtrlTable* ctrl)
{
	if (ppvUserStopPartF != 0) {
		return;
	}

	s32 workOffset = GetYmTraceMoveDataOffsets(ctrl)->m_workOffset;
	_pppMngSt* pppMngSt = ppvMng;
	CGObject* lookTarget = pppMngSt->m_lookTarget;
	pppYmTraceMoveWork* work = reinterpret_cast<pppYmTraceMoveWork*>(pppYmTraceMove->m_workArea + workOffset);
	Vec targetDir;
	Vec moveDir;
	Vec targetPos;
	Vec newPosition;
	Vec moveOffset;
	Quaternion targetQuat;
	Quaternion moveQuat;
	Quaternion blendedQuat;

	work->m_velocity = work->m_velocity + work->m_acceleration;
	work->m_distance = work->m_distance + work->m_velocity;

	if (step->m_graphId == pppYmTraceMove->m_graphId) {
		work->m_distance = work->m_distance + step->m_initWOrk;
		work->m_velocity = work->m_velocity + step->m_stepValue;
		work->m_acceleration = work->m_acceleration + step->m_arg3;
	}

	if (lookTarget == nullptr) {
		pppCopyVector(targetDir, work->m_direction);
		pppCopyVector(moveDir, work->m_previousDirection);
	} else {
		targetPos = lookTarget->m_worldPosition;
		pppSubVector(targetDir, targetPos, pppMngSt->m_position);
		targetDir.y = targetDir.y + step->m_payload;
		pppNormalize(targetDir, targetDir);

		pppCopyVector(work->m_direction, targetDir);
		pppSubVector(moveDir, pppMngSt->m_position, *GetYmTraceMovePreviousPosition(pppMngSt));

		if ((moveDir.x == LoadFloat(kPppYmTraceMoveZero)) && (moveDir.y == LoadFloat(kPppYmTraceMoveZero)) &&
		    (moveDir.z == LoadFloat(kPppYmTraceMoveZero))) {
			pppCopyVector(moveDir, work->m_previousDirection);
		}

		pppNormalize(moveDir, moveDir);
	}

	targetQuat.x = targetDir.x;
	targetQuat.y = targetDir.y;
	targetQuat.z = targetDir.z;
	targetQuat.w = LoadFloat(kPppYmTraceMoveOne);
	moveQuat.x = moveDir.x;
	moveQuat.y = moveDir.y;
	moveQuat.z = moveDir.z;
	moveQuat.w = targetQuat.w;
	C_QUATLerp(&moveQuat, &targetQuat, &blendedQuat, step->m_dataValIndex);
	PSQUATNormalize(&blendedQuat, &blendedQuat);

	moveOffset.x = blendedQuat.x;
	moveOffset.y = blendedQuat.y;
	moveOffset.z = blendedQuat.z;
	PSVECScale(&moveOffset, &moveOffset, work->m_distance * GetYmTraceMoveScale(pppMngSt));
	pppAddVector(newPosition, moveOffset, pppMngSt->m_position);
	pppCopyVector(*GetYmTraceMovePreviousPosition(pppMngSt), pppMngSt->m_position);
	pppCopyVector(pppMngSt->m_position, newPosition);

	ppvMng->m_matrix.value[0][3] = newPosition.x;
	ppvMng->m_matrix.value[1][3] = newPosition.y;
	ppvMng->m_matrix.value[2][3] = newPosition.z;
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
void pppConstructYmTraceMove(pppYmTraceMove* pppYmTraceMove, _pppCtrlTable* ctrl)
{
	pppYmTraceMoveWork* work =
	    reinterpret_cast<pppYmTraceMoveWork*>(pppYmTraceMove->m_workArea +
	                                          GetYmTraceMoveDataOffsets(ctrl)->m_workOffset);
	_pppMngSt* pppMngSt = ppvMng;
	f32 zero;

	pppSubVector(work->m_previousDirection, pppMngSt->m_paramVec0, *GetYmTraceMoveBasePosition(pppMngSt));
	pppCopyVector(work->m_direction, work->m_previousDirection);
	zero = LoadFloat(kPppYmTraceMoveZero);
	work->m_acceleration = zero;
	work->m_velocity = zero;
	work->m_distance = zero;
}
