#include "ffcc/pppPointApMtx.h"
#include "ffcc/pppPart.h"
#include <dolphin/mtx.h>

extern int gPppGlobalFlag;
extern _pppMngSt* gPppMngSt;

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
	unsigned long matrixOffset;
	Mtx* matrix;
	Vec* sourcePos;

	(void)pppMngSt;
	matrixOffset = *(unsigned long*)((char*)pppPDataVal + 0x10);
	matrix = (Mtx*)((char*)pppPObject + matrixOffset + 0x80);

	if (gPppGlobalFlag == 0) {
		if (*((unsigned char*)matrix + 1) == 0) {
			if ((matrixOffset + 1) != 0xFFFF) {
				pppCreatePObject(gPppMngSt, pppPDataVal);
			}
		}
	}

	sourcePos = (Vec*)((char*)pppPObject + *(unsigned long*)((char*)pppPDataVal + 0x8) + 0x80);

	if (*((unsigned char*)pppPDataVal + 0xd) == 0) {
		PSMTXIdentity(*matrix);
		(*matrix)[0][3] = sourcePos->x;
		(*matrix)[1][3] = sourcePos->y;
		(*matrix)[2][3] = sourcePos->z;
	} else {
		Vec result;
		Mtx* worldMatrix = (Mtx*)((char*)gPppMngSt + 0x78);

		PSMTXCopy(*worldMatrix, *matrix);
		PSMTXMultVec(*worldMatrix, sourcePos, &result);

		(*matrix)[0][3] = result.x;
		(*matrix)[1][3] = result.y;
		(*matrix)[2][3] = result.z;
	}

	*((unsigned char*)matrix + 1) = *((unsigned char*)pppPDataVal + 0xc);

	unsigned char counter = *((unsigned char*)matrix + 1);
	if (counter != 0) {
		*((unsigned char*)matrix + 1) = counter - 1;
	}
}
