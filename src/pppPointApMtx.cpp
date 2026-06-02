#include "ffcc/pppPointApMtx.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include <dolphin/mtx.h>


struct pppPointApMtxStep {
	u32 m_unknown0;
	u32 m_createProgramIndex;
	u32 m_childMatrixOffset;
	u8 m_cooldown;
	u8 m_useWorldMatrix;
};

/*
 * --INFO--
 * PAL Address: 0x800de210  
 * PAL Size: 312b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppPointApMtx(_pppPObject* pObject, void* step, _pppCtrlTable* ctrlTable)
{
	pppPointApMtxStep* payload = (pppPointApMtxStep*)step;
	Vec pos;
	u32* offsets = (u32*)ctrlTable->m_serializedDataOffsets;
	Vec* source = (Vec*)(pObject->m_workArea + offsets[0]);
	u8* state = pObject->m_workArea + offsets[1];
	Mtx* target = (Mtx*)state;

	if (ppvUserStopPartF != 0) {
		return;
	}

	if (state[1] == 0) {
		u32 objectId = payload->m_createProgramIndex;
		_pppPObject* object;
		_pppPDataVal* objectData;
		Mtx* matrix;

		if ((objectId + 0x10000) == 0xFFFF) {
			return;
		}

		objectData = ppvMng->m_pppPDataVals + objectId;
		if (objectData == 0) {
			object = 0;
		} else {
			object = (_pppPObject*)pppCreatePObject(ppvMng, objectData);
			*(_pppPObject**)((u8*)object + 4) = pObject;
		}

		matrix = (Mtx*)(object->m_workArea + payload->m_childMatrixOffset);
		if (payload->m_useWorldMatrix == 0) {
			PSMTXIdentity(*matrix);
			(*matrix)[0][3] = source->x;
			(*matrix)[1][3] = source->x;
			(*matrix)[2][3] = source->x;
		} else {
			PSMTXCopy(ppvMng->m_matrix.value, *matrix);
			PSMTXMultVec(ppvMng->m_matrix.value, source, &pos);
			(*matrix)[0][3] = pos.x;
			(*matrix)[1][3] = pos.y;
			(*matrix)[2][3] = pos.z;
		}

		state[1] = payload->m_cooldown;
	}

	state[1]--;
}

/*
 * --INFO--
 * PAL Address: 0x800de348
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppPointApMtxCon(_pppPObject* pObject, _pppCtrlTable* ctrlTable)
{
	unsigned long offset = (unsigned long)(((u32*)ctrlTable->m_serializedDataOffsets)[1]);
	u8* state = pObject->m_workArea + offset;

	state[1] = 0;
}

