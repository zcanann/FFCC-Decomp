#include "ffcc/pppVertexApMtx.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>
#include <dolphin/types.h>

struct VertexApMtxEntry
{
	s16 vertexSetIndex;
	s16 maxValue;
	u16* vertexIndices;
};

struct VertexApMtxEnv
{
	u8 unk0[0x8];
	void* unk8;
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
	s16 index;
	u16 countdown;
};

struct VertexApMtxCtrl
{
	u8 unk0[0xC];
	s32* stateOffset;
};

struct VertexApMtxSource
{
	u8 unk0[0x2C];
	Vec* points;
};

struct VertexApMtxObject
{
	u8 unk0[0x10];
	Mtx localMatrix;
};

struct _pppPDataVal;

_pppPObject* pppCreatePObject(_pppMngSt*, _pppPDataVal*);

/*
 * --INFO--
 * PAL Address: 0x800de360
 * PAL Size: 880b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexApMtx(_pppPObject* parent, PVertexApMtx* dataRaw, void* ctrlRaw)
{
	VertexApMtxData* data = (VertexApMtxData*)dataRaw;
	VertexApMtxCtrl* ctrl = (VertexApMtxCtrl*)ctrlRaw;
	VertexApMtxObject* parentObj = (VertexApMtxObject*)parent;
	s32 stateOffset = *ctrl->stateOffset;
	VertexApMtxState* state = (VertexApMtxState*)((u8*)parent + stateOffset + 0x80);

	if (gPppCalcDisabled != 0) {
		return;
	}

	if (data->entryIndex < 0) {
		return;
	}

	if (state->countdown == 0) {
		int count;
		VertexApMtxEnv* env = (VertexApMtxEnv*)pppEnvStPtr;
		VertexApMtxEntry* entry;
		Vec* points = *(Vec**)((u8*)parent + 0x70);
		entry = &env->entries[data->entryIndex];

		if (points == 0) {
			u32* srcTable = *(u32**)((u8*)env + 0x8);
			VertexApMtxSource* src = *(VertexApMtxSource**)((u8*)srcTable + (entry->vertexSetIndex * 4));
			points = src->points;
		}

		count = data->spawnCount;

		switch (data->mode) {
		case 0:
			while (count-- != 0) {
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
					_pppPDataVal* childData =
						(_pppPDataVal*)((u8*)*(u32*)((u8*)pppMngStPtr + 0xD4) + (childId << 4));
					Vec worldPos;
					Vec pos;
					Mtx* outMtx;
					_pppPObject* child;

					if (childData == 0) {
						child = 0;
					} else {
						child = pppCreatePObject(pppMngStPtr, childData);
						*(void**)((u8*)child + 0x4) = parent;
					}

					pos.x = x;
					pos.y = y;
					pos.z = z;
					PSMTXMultVec(parentObj->localMatrix, &pos, &pos);
					outMtx = (Mtx*)((u8*)child + data->childMtxOffset + 0x80);
					if (data->useWorldMtx == 0) {
						PSMTXIdentity(*outMtx);
						(*outMtx)[0][3] = pos.x;
						(*outMtx)[1][3] = pos.y;
						(*outMtx)[2][3] = pos.z;
					} else {
						PSMTXCopy(pppMngStPtr->m_matrix.value, *outMtx);
						PSMTXMultVec(pppMngStPtr->m_matrix.value, &pos, &worldPos);
						(*outMtx)[0][3] = worldPos.x;
						(*outMtx)[1][3] = worldPos.y;
						(*outMtx)[2][3] = worldPos.z;
					}
				}
			}
			break;
		case 1:
			while (count-- != 0) {
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
					_pppPDataVal* childData =
						(_pppPDataVal*)((u8*)*(u32*)((u8*)pppMngStPtr + 0xD4) + (childId << 4));
					Vec worldPos;
					Vec pos;
					Mtx* outMtx;
					_pppPObject* child;

					if (childData == 0) {
						child = 0;
					} else {
						child = pppCreatePObject(pppMngStPtr, childData);
						*(void**)((u8*)child + 0x4) = parent;
					}

					pos.x = x;
					pos.y = y;
					pos.z = z;
					PSMTXMultVec(parentObj->localMatrix, &pos, &pos);
					outMtx = (Mtx*)((u8*)child + data->childMtxOffset + 0x80);
					if (data->useWorldMtx == 0) {
						PSMTXIdentity(*outMtx);
						(*outMtx)[0][3] = pos.x;
						(*outMtx)[1][3] = pos.y;
						(*outMtx)[2][3] = pos.z;
					} else {
						PSMTXCopy(pppMngStPtr->m_matrix.value, *outMtx);
						PSMTXMultVec(pppMngStPtr->m_matrix.value, &pos, &worldPos);
						(*outMtx)[0][3] = worldPos.x;
						(*outMtx)[1][3] = worldPos.y;
						(*outMtx)[2][3] = worldPos.z;
					}
				}
			}
			break;
		default:
			break;
		}
		state->countdown = data->spawnDelay;
	}

	state->countdown--;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void apea(_pppPObject*, PVertexApMtx*, Vec*)
{
	// Intentionally empty.
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
void pppVertexApMtxCon(_pppPObject* obj, PVertexApMtx* vtx)
{
	s32 offset = **(s32**)((u8*)vtx + 0xC);
	u16* state = (u16*)((u8*)obj + offset + 0x80);

	state[0] = 0;
	state[1] = 0;
}
