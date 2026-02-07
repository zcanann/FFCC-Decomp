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
	unsigned long* serialized = *(unsigned long**)((char*)pppPDataVal + 0xc);
	unsigned long offset = serialized[1] + 0x81;
	unsigned char zero = 0;
	((unsigned char*)pppPObject)[offset] = zero;
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
	unsigned long* serialized = *(unsigned long**)((char*)pppMngSt + 0xc);
	unsigned long srcOffset = serialized[0];
	unsigned long matrixOffset = serialized[1];
	Mtx* pMatrix = (Mtx*)((char*)pppPObject + matrixOffset + 0x80);
	Vec* pSrcPos = (Vec*)((char*)pppPObject + srcOffset + 0x80);
	unsigned char* pFlag = (unsigned char*)pMatrix + 1;

	if (gPppGlobalFlag == 0) {
		if (*pFlag == 0) {
			unsigned long objectId = *(unsigned long*)((char*)pppPDataVal + 0x4);
			if ((objectId + 0x10000) != 0xFFFF) {
				void* objectTable = *(void**)((char*)gPppMngSt + 0xd4);
				if ((char*)objectTable + (objectId << 4) != 0) {
					pppCreatePObject(gPppMngSt, pppPDataVal);
				}
			}
		}
	}

	if (*((unsigned char*)pppPDataVal + 0xd) == 0) {
		PSMTXIdentity(*pMatrix);
		(*pMatrix)[0][3] = pSrcPos->x;
		(*pMatrix)[1][3] = pSrcPos->y;
		(*pMatrix)[2][3] = pSrcPos->z;
	} else {
		unsigned long transformedOffset = *(unsigned long*)((char*)pppPDataVal + 0x8);
		Vec* transformedSrcPos = (Vec*)((char*)pppPObject + transformedOffset + 0x80);
		Mtx* worldMatrix = (Mtx*)((char*)gPppMngSt + 0x78);
		Vec result;

		PSMTXCopy(*worldMatrix, *pMatrix);
		PSMTXMultVec(*worldMatrix, transformedSrcPos, &result);

		(*pMatrix)[0][3] = result.x;
		(*pMatrix)[1][3] = result.y;
		(*pMatrix)[2][3] = result.z;
	}

	*pFlag = *((unsigned char*)pppPDataVal + 0xc);
	*pFlag = (unsigned char)(*pFlag - 1);
}
