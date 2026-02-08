#include "ffcc/pppPointApMtx.h"
#include <dolphin/mtx.h>

extern int gPppGlobalFlag;
extern _pppMngSt* gPppMngSt;
extern "C" _pppPObject* pppCreatePObject(_pppMngSt*, _pppPDataVal*);

/*
 * --INFO--
 * PAL Address: 0x800de348
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppPointApMtxCon(_pppPObject* pppPObject, _pppPDataVal* pppPDataVal)
{
	unsigned long data = *(unsigned long*)((char*)pppPDataVal + 0xC);
	unsigned long offset = *(unsigned long*)(data + 0x4);
	_pppPObject* object = (_pppPObject*)((char*)pppPObject + offset);

	*(unsigned char*)((char*)object + 0x81) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800de210  
 * PAL Size: 312b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppPointApMtx(_pppPObject* pppPObject, _pppPDataVal* pppPDataVal, _pppMngSt* pppMngSt)
{
	Vec pos;
	u32* offsets = *(u32**)((u8*)pppMngSt + 0xC);
	Vec* source = (Vec*)((u8*)pppPObject + offsets[0] + 0x80);
	Mtx* target = (Mtx*)((u8*)pppPObject + offsets[1] + 0x80);

	if (gPppGlobalFlag != 0) {
		return;
	}

	if (((u8*)target)[1] == 0) {
		u32 objectId = *(u32*)((u8*)pppPDataVal + 4);
		_pppPObject* object;
		_pppPDataVal* objectData;
		Mtx* matrix;

		if ((objectId + 0x10000) == 0xFFFF) {
			return;
		}

		objectData = (_pppPDataVal*)(*(u32*)((u8*)gPppMngSt + 0xD4) + (objectId << 4));
		if (objectData != 0) {
			object = (_pppPObject*)pppCreatePObject(gPppMngSt, objectData);
			goto object_ready;
		}
		object = 0;

	object_ready:
		*(void**)((u8*)object + 4) = pppPObject;

		matrix = (Mtx*)((u8*)object + *(u32*)((u8*)pppPDataVal + 8) + 0x80);
		if (((u8*)pppPDataVal)[0xD] == 0) {
			PSMTXIdentity(*matrix);
			(*matrix)[0][3] = source->x;
			(*matrix)[1][3] = source->x;
			(*matrix)[2][3] = source->x;
		} else {
			PSMTXCopy(*(Mtx*)((u8*)gPppMngSt + 0x78), *matrix);
			PSMTXMultVec(*(Mtx*)((u8*)gPppMngSt + 0x78), source, &pos);
			(*matrix)[0][3] = pos.x;
			(*matrix)[1][3] = pos.y;
			(*matrix)[2][3] = pos.z;
		}
	}

	((u8*)target)[1] = ((u8*)pppPDataVal)[0xC];
	((u8*)target)[1]--;
}
