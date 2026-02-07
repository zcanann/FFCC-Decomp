#include "ffcc/pppPointApMtx.h"
#include "ffcc/pppPart.h"
#include <dolphin/mtx.h>

extern int gPppGlobalFlag;
extern _pppMngSt* gPppMngSt;

struct _pppPointApMtxDataVal
{
	u32 unk0;
	u32 unk4;
	u32 srcOffset;
	u8 frameCount;
	u8 useWorldMtx;
	u16 pad;
	u32 mtxOffset;
};

/*
 * --INFO--
 * PAL Address: 0x800de348
 * PAL Size: 24b
 */
void pppPointApMtxCon(_pppPObject* pppPObject, _pppPDataVal* pppPDataVal)
{
	_pppPointApMtxDataVal* dataVal = (_pppPointApMtxDataVal*)pppPDataVal;
	u32 offset = dataVal->frameCount;
	pppPObject = (_pppPObject*)((u8*)pppPObject + offset);
	*((unsigned char*)pppPObject + 0x81) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800de210  
 * PAL Size: 312b
 */
void pppPointApMtx(_pppPObject* pppPObject, _pppPDataVal* pppPDataVal, _pppMngSt* pppMngSt)
{
	_pppPointApMtxDataVal* dataVal = (_pppPointApMtxDataVal*)pppPDataVal;
	u32 param2 = dataVal->mtxOffset;
	Mtx* pMatrix = (Mtx*)((u8*)pppPObject + param2 + 0x80);
	u8* pFlag = (u8*)pMatrix + 1;
	
	if (gPppGlobalFlag == 0) {
		if (*pFlag == 0) {
			if ((param2 + 1) != 0xFFFF) {  // This generates addic. r0, r5, 0x1
				pppCreatePObject(gPppMngSt, pppPDataVal);
			}
		}
	}
	
	u32 param3 = dataVal->srcOffset;
	Vec* pSrcPos = (Vec*)((u8*)pppPObject + param3 + 0x80);
	
	if (dataVal->useWorldMtx == 0) {
		PSMTXIdentity(*pMatrix);
		(*pMatrix)[0][3] = pSrcPos->x;
		(*pMatrix)[1][3] = pSrcPos->y;
		(*pMatrix)[2][3] = pSrcPos->z;
	} else {
		Mtx* worldMatrix = (Mtx*)((u8*)gPppMngSt + 0x78);
		PSMTXCopy(*worldMatrix, *pMatrix);
		
		Vec result;
		PSMTXMultVec(*worldMatrix, pSrcPos, &result);
		
		(*pMatrix)[0][3] = result.x;
		(*pMatrix)[1][3] = result.y;
		(*pMatrix)[2][3] = result.z;
	}
	
	*pFlag = dataVal->frameCount;
	
	u8 counter = *pFlag;
	if (counter != 0) {
		*pFlag = counter - 1;
	}
}
