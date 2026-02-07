#include "ffcc/pppPointApMtx.h"
#include "ffcc/pppPart.h"
#include <dolphin/mtx.h>

extern int gPppGlobalFlag;
extern _pppMngSt* gPppMngSt;

/*
 * --INFO--
 * PAL Address: 0x800de348
 * PAL Size: 24b
 */
void pppPointApMtxCon(_pppPObject* pppPObject, _pppPDataVal* pppPDataVal)
{
	char* ptr = (char*)pppPObject;
	ptr += (int)((void**)((char*)pppPDataVal + 0xc))[0];
	ptr[0x81] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800de210  
 * PAL Size: 312b
 */
void pppPointApMtx(_pppPObject* pppPObject, _pppPDataVal* pppPDataVal, _pppMngSt* pppMngSt)
{
	unsigned long param2 = *((unsigned long*)((char*)pppPDataVal + 0x10));
	Mtx* pMatrix = (Mtx*)((char*)pppPObject + param2 + 0x80);
	unsigned char* pFlag = (unsigned char*)pMatrix + 1;
	
	if (gPppGlobalFlag == 0) {
		if (*pFlag == 0) {
			if ((param2 + 1) != 0xFFFF) {  // This generates addic. r0, r5, 0x1
				pppCreatePObject(gPppMngSt, pppPDataVal);
			}
		}
	}
	
	unsigned long param3 = *((unsigned long*)((char*)pppPDataVal + 0x8));
	Vec* pSrcPos = (Vec*)((char*)pppPObject + param3 + 0x80);
	
	if (*((unsigned char*)pppPDataVal + 0xd) == 0) {
		PSMTXIdentity(*pMatrix);
		(*pMatrix)[0][3] = pSrcPos->x;
		(*pMatrix)[1][3] = pSrcPos->y;
		(*pMatrix)[2][3] = pSrcPos->z;
	} else {
		Mtx* worldMatrix = (Mtx*)((char*)gPppMngSt + 0x78);
		PSMTXCopy(*worldMatrix, *pMatrix);
		
		Vec result;
		PSMTXMultVec(*worldMatrix, pSrcPos, &result);
		
		(*pMatrix)[0][3] = result.x;
		(*pMatrix)[1][3] = result.y;
		(*pMatrix)[2][3] = result.z;
	}
	
	*pFlag = *((unsigned char*)pppPDataVal + 0xc);
	
	unsigned char counter = *pFlag;
	if (counter != 0) {
		*pFlag = counter - 1;
	}
}
