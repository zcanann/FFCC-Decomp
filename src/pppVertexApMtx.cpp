#include "global.h"
#include "ffcc/pppVertexApMtx.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

#include <dolphin/mtx.h>
#include <dolphin/types.h>

struct VertexApMtxEntry
{
	s16 vertexSetIndex;
	s16 maxValue;
	u16* vertexIndices;
};

struct VertexApMtxSource;

struct VertexApMtxEnv
{
	u8 unk0[0x8];
	VertexApMtxSource** sourceTable;
	u8 unkC[0x4];
	VertexApMtxEntry* entries;
};

struct VertexApMtxData
{
	u8 unk0[0x4];
	s16 entryIndex;
	u8 spawnCount;
	u8 spawnDelay;
	u8 mode;
	u8 useWorldMtx;
	u8 unkA[0x2];
	u32 childId;
	u32 childMtxOffset;
};

struct VertexApMtxState
{
	u16 index;
	u16 countdown;
};

STATIC_ASSERT(sizeof(VertexApMtxDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(VertexApMtxDataOffsets, m_stateOffset) == 0x0);

static inline VertexApMtxDataOffsets* GetVertexApMtxDataOffsets(_pppCtrlTable* ctrl)
{
	return reinterpret_cast<VertexApMtxDataOffsets*>(ctrl->m_serializedDataOffsets);
}

struct VertexApMtxSource
{
	u8 unk0[0x2C];
	Vec* points;
};

/*
 * --INFO--
 * PAL Address: 0x800de360
 * PAL Size: 880b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexApMtx(_pppPObject* parent, PVertexApMtx* dataRaw, _pppCtrlTable* ctrl)
{
	VertexApMtxData* data = (VertexApMtxData*)dataRaw;
	s32 stateOffset = GetVertexApMtxDataOffsets(ctrl)->m_stateOffset;
	VertexApMtxState* state = (VertexApMtxState*)(parent->m_workArea + stateOffset);

	if (ppvUserStopPartF != 0) {
		goto exitStub;
	}

	if (data->entryIndex < 0) {
		goto exitStub;
	}

	if (state->countdown == 0) {
		int count;
		VertexApMtxEnv* env = (VertexApMtxEnv*)ppvEnv;
		VertexApMtxEntry* entry;
		Vec* points = parent->m_drawMatrixPtr;
		entry = &env->entries[data->entryIndex];

		if (points == 0) {
			VertexApMtxSource* src = env->sourceTable[entry->vertexSetIndex];
			points = src->points;
		}

		count = data->spawnCount;

		switch (data->mode) {
		default:
			goto setCountdown;
		case 0:
			goto mode0Dispatch;
		mode0Body:
			{
				if (state->index >= entry->maxValue) {
					state->index = 0;
				}

				u16 outValue = state->index;
				u16* vertexIndices = entry->vertexIndices;
				state->index++;
				u16 vertexIndex = vertexIndices[outValue];
				Vec* vertex = &points[vertexIndex];
				f32 x = vertex->x;
				f32 y = vertex->y;
				f32 z = vertex->z;

				if ((data->childId + 0x10000) != 0xFFFF) {
					s32 childId = data->childId;
					_pppPDataVal* childData = ppvMng->m_pppPDataVals + childId;
					Vec worldPos;
					Vec pos;
					Mtx* outMtx;
					_pppPObject* child;

					if (childData == 0) {
						child = 0;
					} else {
						child = pppCreatePObject(ppvMng, childData);
						child->m_link.m_previous = &parent->m_link;
					}

					pos.x = x;
					pos.y = y;
					pos.z = z;
					PSMTXMultVec(parent->m_localMatrix.value, &pos, &pos);
					outMtx = (Mtx*)(child->m_workArea + data->childMtxOffset);
					if (data->useWorldMtx == 0) {
						PSMTXIdentity(*outMtx);
						(*outMtx)[0][3] = pos.x;
						(*outMtx)[1][3] = pos.y;
						(*outMtx)[2][3] = pos.z;
					} else {
						PSMTXCopy(ppvMng->m_matrix.value, *outMtx);
						PSMTXMultVec(ppvMng->m_matrix.value, &pos, &worldPos);
						(*outMtx)[0][3] = worldPos.x;
						(*outMtx)[1][3] = worldPos.y;
						(*outMtx)[2][3] = worldPos.z;
					}
				}
			}
		mode0Test:
			if (count-- != 0) {
				goto mode0Body;
			}
			goto setCountdown;
		case 1:
			goto mode1Dispatch;
		mode1Body:
			{
				f32 randValue = Math.RandF();
				f32 maxValue = (f32)entry->maxValue;
				int outValue = (int)(randValue * maxValue);
				u16* vertexIndices = entry->vertexIndices;
				u16 vertexIndex = vertexIndices[outValue];
				Vec* vertex = &points[vertexIndex];
				f32 x = vertex->x;
				f32 y = vertex->y;
				f32 z = vertex->z;

				if ((data->childId + 0x10000) != 0xFFFF) {
					s32 childId = data->childId;
					_pppPDataVal* childData = ppvMng->m_pppPDataVals + childId;
					Vec worldPos;
					Vec pos;
					Mtx* outMtx;
					_pppPObject* child;

					if (childData == 0) {
						child = 0;
					} else {
						child = pppCreatePObject(ppvMng, childData);
						child->m_link.m_previous = &parent->m_link;
					}

					pos.x = x;
					pos.y = y;
					pos.z = z;
					PSMTXMultVec(parent->m_localMatrix.value, &pos, &pos);
					outMtx = (Mtx*)(child->m_workArea + data->childMtxOffset);
					if (data->useWorldMtx == 0) {
						PSMTXIdentity(*outMtx);
						(*outMtx)[0][3] = pos.x;
						(*outMtx)[1][3] = pos.y;
						(*outMtx)[2][3] = pos.z;
					} else {
						PSMTXCopy(ppvMng->m_matrix.value, *outMtx);
						PSMTXMultVec(ppvMng->m_matrix.value, &pos, &worldPos);
						(*outMtx)[0][3] = worldPos.x;
						(*outMtx)[1][3] = worldPos.y;
						(*outMtx)[2][3] = worldPos.z;
					}
				}
			}
		mode1Test:
			if (count-- != 0) {
				goto mode1Body;
			}
			goto setCountdown;
		}

	setCountdown:
		state->countdown = data->spawnDelay;
	}

	state->countdown--;

exitStub:
	goto functionEnd;
mode0Dispatch:
	goto mode0Test;
mode1Dispatch:
	goto mode1Test;
functionEnd:
	;
}

/*
 * --INFO--
 * PAL Address: 0x800de6d0
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexApMtxCon(_pppPObject* obj, _pppCtrlTable* ctrl)
{
	s32 offset = GetVertexApMtxDataOffsets(ctrl)->m_stateOffset;
	u16* state = (u16*)(obj->m_workArea + offset);

	state[0] = 0;
	state[1] = 0;
}
