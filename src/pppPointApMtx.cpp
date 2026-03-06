#include "ffcc/pppPointApMtx.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include <dolphin/mtx.h>

extern int lbl_8032ED70;
extern u8* lbl_8032ED50;

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
	u32* offsets = (u32*)ctrlTable->m_serializedDef;
	Vec* source = (Vec*)((u8*)pObject + offsets[0] + 0x80);
	Mtx* target = (Mtx*)((u8*)pObject + offsets[1] + 0x80);

	if (lbl_8032ED70 != 0) {
		return;
	}

	if (((u8*)target)[1] == 0) {
		u32 objectId = payload->m_createProgramIndex;
		_pppPObject* object;
		_pppPDataVal* objectData;
		Mtx* matrix;

		if ((objectId + 0x10000) == 0xFFFF) {
			return;
		}

		objectData = (_pppPDataVal*)(*(u32*)((u8*)lbl_8032ED50 + 0xD4) + (objectId << 4));
		if (objectData == 0) {
			object = 0;
		} else {
			object = (_pppPObject*)pppCreatePObject((_pppMngSt*)lbl_8032ED50, objectData);
			*(_pppPObject**)((u8*)object + 4) = pObject;
		}

		matrix = (Mtx*)((u8*)object + payload->m_childMatrixOffset + 0x80);
		if (payload->m_useWorldMatrix == 0) {
			PSMTXIdentity(*matrix);
			(*matrix)[0][3] = source->x;
			(*matrix)[1][3] = source->x;
			(*matrix)[2][3] = source->x;
		} else {
			PSMTXCopy(*(Mtx*)((u8*)lbl_8032ED50 + 0x78), *matrix);
			PSMTXMultVec(*(Mtx*)((u8*)lbl_8032ED50 + 0x78), source, &pos);
			(*matrix)[0][3] = pos.x;
			(*matrix)[1][3] = pos.y;
			(*matrix)[2][3] = pos.z;
		}

		((u8*)target)[1] = payload->m_cooldown;
	}

	((u8*)target)[1]--;
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
	unsigned long offset = (unsigned long)(((u32*)ctrlTable->m_serializedDef)[1]);
	_pppPObject* object = (_pppPObject*)((char*)pObject + offset);

	*(unsigned char*)((char*)object + 0x81) = 0;
}
