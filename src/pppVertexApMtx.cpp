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
	u32 childId;
	u32 childMtxOffset;
};

struct VertexApMtxState
{
	u16 index;
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

struct _pppPDataVal;

extern CMath math;
extern int lbl_8032ED70;
extern u8* lbl_8032ED50;
extern VertexApMtxEnv* lbl_8032ED54;

extern "C" {
f32 RandF__5CMathFv(CMath*);
_pppPObject* pppCreatePObject(_pppMngSt*, _pppPDataVal*);
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
	VertexApMtxState* state = (VertexApMtxState*)((u8*)parent + **(s32**)((u8*)ctrlRaw + 0xC) + 0x80);

	if (lbl_8032ED70 != 0) {
		return;
	}

	if (data->entryIndex < 0) {
		return;
	}

	if (state->countdown == 0) {
		VertexApMtxEntry* entry = &lbl_8032ED54->entries[data->entryIndex];
		Vec* points = *(Vec**)((u8*)parent + 0x70);

		if (points == 0) {
			u32* srcTable = *(u32**)((u8*)lbl_8032ED54 + 0x8);
			VertexApMtxSource* src = *(VertexApMtxSource**)((u8*)srcTable + (entry->vertexSetIndex * 4));
			points = src->points;
		}

		u8 count = data->spawnCount;
		if (data->mode == 0) {
			do {
				if (state->index >= (u16)entry->maxValue) {
					state->index = 0;
				}

				u16 vertexIndex = entry->vertexIndices[state->index];
				state->index++;
				Vec* vertex = &points[vertexIndex];
				f32 x = vertex->x;
				f32 y = vertex->y;
				f32 z = vertex->z;

				if ((data->childId + 0x10000) != 0xFFFF) {
					_pppPObject* child;
					_pppPDataVal* childData = (_pppPDataVal*)((u8*)*(u32*)((u8*)lbl_8032ED50 + 0xD4) + (data->childId << 4));
					Mtx* outMtx;
					Vec pos;
					Vec worldPos;

					if (childData == 0) {
						child = 0;
					} else {
						child = pppCreatePObject((_pppMngSt*)lbl_8032ED50, childData);
						*(void**)((u8*)child + 4) = parent;
					}

					pos.x = x;
					pos.y = y;
					pos.z = z;
					PSMTXMultVec(*(Mtx*)((u8*)parent + 0x10), &pos, &pos);
					outMtx = (Mtx*)((u8*)child + data->childMtxOffset + 0x80);
					if (data->useWorldMtx == 0) {
						PSMTXIdentity(*outMtx);
						(*outMtx)[0][3] = pos.x;
						(*outMtx)[1][3] = pos.y;
						(*outMtx)[2][3] = pos.z;
					} else {
						PSMTXCopy(*(Mtx*)((u8*)lbl_8032ED50 + 0x78), *outMtx);
						PSMTXMultVec(*(Mtx*)((u8*)lbl_8032ED50 + 0x78), &pos, &worldPos);
						(*outMtx)[0][3] = worldPos.x;
						(*outMtx)[1][3] = worldPos.y;
						(*outMtx)[2][3] = worldPos.z;
					}
				}
			} while (count-- != 0);
		} else if (data->mode == 1) {
			do {
				u16 vertexIndex = entry->vertexIndices[(s32)(RandF__5CMathFv(&math) * (f32)entry->maxValue)];
				Vec* vertex = &points[vertexIndex];
				f32 x = vertex->x;
				f32 y = vertex->y;
				f32 z = vertex->z;

				if ((data->childId + 0x10000) != 0xFFFF) {
					_pppPObject* child;
					_pppPDataVal* childData = (_pppPDataVal*)((u8*)*(u32*)((u8*)lbl_8032ED50 + 0xD4) + (data->childId << 4));
					Mtx* outMtx;
					Vec pos;
					Vec worldPos;

					if (childData == 0) {
						child = 0;
					} else {
						child = pppCreatePObject((_pppMngSt*)lbl_8032ED50, childData);
						*(void**)((u8*)child + 4) = parent;
					}

					pos.x = x;
					pos.y = y;
					pos.z = z;
					PSMTXMultVec(*(Mtx*)((u8*)parent + 0x10), &pos, &pos);
					outMtx = (Mtx*)((u8*)child + data->childMtxOffset + 0x80);
					if (data->useWorldMtx == 0) {
						PSMTXIdentity(*outMtx);
						(*outMtx)[0][3] = pos.x;
						(*outMtx)[1][3] = pos.y;
						(*outMtx)[2][3] = pos.z;
					} else {
						PSMTXCopy(*(Mtx*)((u8*)lbl_8032ED50 + 0x78), *outMtx);
						PSMTXMultVec(*(Mtx*)((u8*)lbl_8032ED50 + 0x78), &pos, &worldPos);
						(*outMtx)[0][3] = worldPos.x;
						(*outMtx)[1][3] = worldPos.y;
						(*outMtx)[2][3] = worldPos.z;
					}
				}
			} while (count-- != 0);
		}
		state->countdown = data->spawnDelay;
	}

	state->countdown--;
}
