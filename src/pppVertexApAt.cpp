#include "ffcc/pppVertexApAt.h"
#include "ffcc/math.h"

extern CMath math;
extern unsigned int lbl_8032ED70;
extern void* lbl_8032ED54;
extern void* lbl_8032ED50;

struct _pppMngSt;
struct _pppPDataVal;

void* pppCreatePObject(struct _pppMngSt*, struct _pppPDataVal*);

// RandF actually returns float despite header declaration
extern "C" float RandF__5CMathFv();

/*
 * --INFO--
 * Address:	80064CC8
 * Size:	32
 */
void pppVertexApAtCon(_pppPObject* pppObject, PVertexApAt* vertexApAt)
{
	void* data = *((void**)((char*)vertexApAt + 0xC));
	unsigned int baseOffset = *((unsigned int*)data);
	void* adjustedPtr = (char*)baseOffset + 0x80;
	void* ptr = (char*)pppObject + (unsigned int)adjustedPtr;
	*(unsigned short*)ptr = 0;
	*((unsigned short*)ptr + 1) = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void apea(_pppPObject*, PVertexApAt*, unsigned short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	80064B08
 * Size:	444
 */
void pppVertexApAt(_pppPObject* pppObject, PVertexApAt* vertexApAt)
{
	void* basePtr = (char*)pppObject + *((unsigned int*)*((void**)((char*)vertexApAt + 0xC))) + 0x80;
	
	if (lbl_8032ED70 != 0) {
		return;
	}
	
	short value = *((short*)((char*)vertexApAt + 0x4));
	if (value < 0) {
		return;
	}
	
	if (*((unsigned short*)basePtr + 1) != 0) {
		// Decrement counter and return
		*((unsigned short*)basePtr + 1) = *((unsigned short*)basePtr + 1) - 1;
		return;
	}
	
	void* dataPtr = (char*)*((void**)lbl_8032ED54 + 4) + (value << 3);
	unsigned char count = *((unsigned char*)((char*)vertexApAt + 0x6));
	unsigned char type = *((unsigned char*)((char*)vertexApAt + 0x8));
	
	if (type == 1) {
		// Random mode
		for (int i = count; i > 0; i--) {
			float rand = RandF__5CMathFv();
			short maxVal = *((short*)dataPtr + 1);
			unsigned short randIndex = (unsigned short)(rand * maxVal);
			
			unsigned int objId = *((unsigned int*)((char*)vertexApAt + 0xC));
			if ((objId + 1) != 0xFFFF) {
				void* mgr = lbl_8032ED50;
				void* dataVal = (char*)*((void**)((char*)mgr + 0xD4)) + (objId << 4);
				void* newObj = 0;
				if (dataVal != 0) {
					newObj = pppCreatePObject((struct _pppMngSt*)mgr, (struct _pppPDataVal*)dataVal);
					*((void**)((char*)newObj + 0x4)) = pppObject;
				}
				
				if (newObj) {
					unsigned int offset = *((unsigned int*)((char*)vertexApAt + 0x10)) + 0x80;
					*((unsigned short*)((char*)newObj + offset)) = randIndex;
				}
			}
		}
	} else if (type == 0) {
		// Sequential mode
		for (int i = count; i > 0; i--) {
			unsigned short currentIdx = *((unsigned short*)basePtr);
			short maxVal = *((short*)dataPtr + 1);
			
			if (currentIdx >= maxVal) {
				*((unsigned short*)basePtr) = 0;
			}
			
			currentIdx = *((unsigned short*)basePtr);
			*((unsigned short*)basePtr) = currentIdx + 1;
			
			unsigned int objId = *((unsigned int*)((char*)vertexApAt + 0xC));
			if ((objId + 1) != 0xFFFF) {
				void* mgr = lbl_8032ED50;
				void* dataVal = (char*)*((void**)((char*)mgr + 0xD4)) + (objId << 4);
				void* newObj = 0;
				if (dataVal != 0) {
					newObj = pppCreatePObject((struct _pppMngSt*)mgr, (struct _pppPDataVal*)dataVal);
					*((void**)((char*)newObj + 0x4)) = pppObject;
				}
				
				if (newObj) {
					unsigned int offset = *((unsigned int*)((char*)vertexApAt + 0x10)) + 0x80;
					*((unsigned short*)((char*)newObj + offset)) = currentIdx;
				}
			}
		}
	}
	
	// Set the delay counter
	unsigned char delay = *((unsigned char*)((char*)vertexApAt + 0x7));
	*((unsigned short*)basePtr + 1) = delay;
}
