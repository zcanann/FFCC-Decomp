#include "ffcc/pppPointApMtx.h"
#include "ffcc/pppPart.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x800de348
 * PAL Size: 24b
 */
void pppPointApMtxCon(_pppPObject* pppPObject, _pppPDataVal* pppPDataVal)
{
	// Access struct at offset 0xc, then offset 0x4
	unsigned long* dataPtr = (unsigned long*)((char*)pppPDataVal + 0xc);
	unsigned long value = *(unsigned long*)((char*)dataPtr + 0x4);
	unsigned long offset = value + 0x81;
	*((unsigned char*)pppPObject + offset) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800de210  
 * PAL Size: 312b
 */
void pppPointApMtx(_pppPObject* pppPObject, _pppPDataVal* pppPDataVal, _pppMngSt* pppMngSt)
{
	// Extract data from pppPDataVal structure
	unsigned long* structPtr = (unsigned long*)((char*)pppPDataVal + 0xc);
	unsigned long param1 = *((unsigned long*)structPtr + 0);    // r5 lwz 0x0(r5)
	unsigned long param2 = *((unsigned long*)structPtr + 1);    // r3 lwz 0x4(r5)
	
	// Calculate pointers
	Vec* pPos = (Vec*)((char*)pppPObject + param1 + 0x80);
	Mtx* pMatrix = (Mtx*)((char*)pppPObject + param2 + 0x80);
	unsigned char* pFlag = (unsigned char*)pMatrix + 1;
	
	// Check global flag
	extern int gPppGlobalFlag;
	if (gPppGlobalFlag == 0) {
		if (*pFlag == 0) {
			// Validate param2
			if ((param2 + 1) != 0) {
				extern _pppMngSt* gPppMngSt;
				pppCreatePObject(gPppMngSt, pppPDataVal);
				// The assembly shows storing pppPObject at offset 0x4 after the call
				// but we can't capture the return value since it's void
			}
		}
	}
	
	// Matrix calculation branch
	unsigned long param3 = *((unsigned long*)((char*)pppPDataVal + 0x8));
	Vec* pSrcPos = (Vec*)((char*)pppPObject + param3 + 0x80);
	
	if (*((unsigned char*)pppPDataVal + 0xd) == 0) {
		// Initialize identity matrix
		PSMTXIdentity(*pMatrix);
		(*pMatrix)[0][3] = pSrcPos->x;
		(*pMatrix)[1][3] = pSrcPos->y;
		(*pMatrix)[2][3] = pSrcPos->z;
	} else {
		// Apply matrix transformation
		extern _pppMngSt* gPppMngSt;
		Mtx* worldMatrix = (Mtx*)((char*)gPppMngSt + 0x78);
		PSMTXCopy(*worldMatrix, *pMatrix);
		
		Vec result;
		PSMTXMultVec(*worldMatrix, pSrcPos, &result);
		
		(*pMatrix)[0][3] = result.x;
		(*pMatrix)[1][3] = result.y;  
		(*pMatrix)[2][3] = result.z;
	}
	
	// Update counter
	*pFlag = *((unsigned char*)pppPDataVal + 0xc);
	
	// Decrement if > 0
	unsigned char counter = *pFlag;
	if (counter > 0) {
		*pFlag = counter - 1;
	}
}