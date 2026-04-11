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
	Vec previousDirectionNormalizeInput;
	Vec previousDirectionCopyInput;
	Vec previousPosition;
	Vec positionForPreviousDirection;
	Vec directionCopyInput;
	Vec directionNormalizeInput;
	Vec currentPosition;
	Vec ownerPosition;
	Vec scaledDirection;
	Vec directionCopy;
	Quaternion blendedDirection;
	Quaternion previousDirectionQuat;
	Quaternion directionQuat;
	Vec scaledOffset;
	Vec nextPosition;
	Vec ownerPositionRaw;
	Vec previousDirection;
	Vec direction;

	work->m_velocity = work->m_velocity + work->m_acceleration;
	work->m_distance = work->m_distance + work->m_velocity;

	if (param_2->m_graphId == pppYmTraceMove->m_graphId) {
		work->m_distance = work->m_distance + param_2->m_initWOrk;
		work->m_velocity = work->m_velocity + param_2->m_stepValue;
		work->m_acceleration = work->m_acceleration + param_2->m_arg3;
	}

	if (owner == nullptr) {
		pppCopyVector(direction, work->m_direction);
		pppCopyVector(previousDirection, work->m_previousDirection);
	} else {
		u8* ownerBytes = (u8*)owner;

		ownerPositionRaw.x = *(f32*)(ownerBytes + 0x15c);
		ownerPositionRaw.y = *(f32*)(ownerBytes + 0x160);
		ownerPositionRaw.z = *(f32*)(ownerBytes + 0x164);
		pppCopyVector(ownerPosition, ownerPositionRaw);
		pppCopyVector(currentPosition, pppMngSt->m_position);
		pppSubVector(direction, ownerPosition, currentPosition);
		direction.y = direction.y + param_2->m_payload;
		pppCopyVector(directionNormalizeInput, direction);
		pppNormalize__FR3Vec3Vec((float*)&direction, &directionNormalizeInput);

		pppCopyVector(directionCopyInput, direction);
		pppCopyVector(work->m_direction, directionCopyInput);
		pppCopyVector(positionForPreviousDirection, pppMngSt->m_position);
		pppCopyVector(previousPosition, pppMngSt->m_previousPosition);
		pppSubVector(previousDirection, positionForPreviousDirection, previousPosition);

		if ((previousDirection.x == kPppYmTraceMoveZero) &&
		    (previousDirection.y == kPppYmTraceMoveZero) &&
		    (previousDirection.z == kPppYmTraceMoveZero)) {
			pppCopyVector(previousDirectionCopyInput, work->m_previousDirection);
			pppCopyVector(previousDirection, previousDirectionCopyInput);
		}

		pppCopyVector(previousDirectionNormalizeInput, previousDirection);
		pppNormalize__FR3Vec3Vec((float*)&previousDirection, &previousDirectionNormalizeInput);
	}

	previousDirectionQuat.x = previousDirection.x;
	previousDirectionQuat.y = previousDirection.y;
	previousDirectionQuat.z = previousDirection.z;
	previousDirectionQuat.w = kPppYmTraceMoveOne;
	directionQuat.x = direction.x;
	directionQuat.y = direction.y;
	directionQuat.z = direction.z;
	directionQuat.w = kPppYmTraceMoveOne;
	C_QUATLerp(&previousDirectionQuat, &directionQuat, &blendedDirection, param_2->m_dataValIndex);
	PSQUATNormalize(&blendedDirection, &blendedDirection);

	scaledOffset.x = blendedDirection.x;
	scaledOffset.y = blendedDirection.y;
	scaledOffset.z = blendedDirection.z;
	pppCopyVector(scaledDirection, scaledOffset);
	PSVECScale(&scaledDirection, &scaledDirection, work->m_distance * pppMngSt->m_scale);
	pppCopyVector(currentPosition, pppMngSt->m_position);
	pppAddVector(nextPosition, scaledDirection, currentPosition);
	pppCopyVector(previousPosition, pppMngSt->m_position);
	pppCopyVector(pppMngSt->m_previousPosition, previousPosition);
	pppCopyVector(directionCopy, nextPosition);
	pppCopyVector(pppMngSt->m_position, directionCopy);

	pppMngStPtr->m_matrix.value[0][3] = nextPosition.x;
	pppMngStPtr->m_matrix.value[1][3] = nextPosition.y;
	pppMngStPtr->m_matrix.value[2][3] = nextPosition.z;
}
