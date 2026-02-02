#include "ffcc/pppKeZCrctShp.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

/*
 * --INFO--
 * PAL Address: 0x8008821c
 * PAL Size: 1148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeZCrctShpDraw(_pppPObject *pObject, int param2)
{
	Vec rowX, rowY, rowZ, rowPos;
	Vec scaledX, scaledY, scaledZ;
	Vec transformedPos;
	Vec neutralVec = {0.0f, 0.0f, 0.0f};
	pppFMATRIX transformMatrix;
	pppFMATRIX worldMatrix;
	pppFMATRIX cameraMatrix;
	
	// Extract row vectors from object's local matrix (offset 0x10)
	pppFMATRIX *localMatrix = (pppFMATRIX *)((char *)pObject + 0x10);
	pppGetRowVector(*localMatrix, rowX, rowY, rowZ, rowPos);
	
	// Scale the basis vectors
	pppScaleVector(scaledX, rowX, pppMngStPtr->m_scale.x);
	pppScaleVector(scaledY, rowY, pppMngStPtr->m_scale.y);
	pppScaleVector(scaledZ, rowZ, pppMngStPtr->m_scale.z);
	
	// Set up transform matrix with scaled basis vectors
	pppSetRowVector(transformMatrix, scaledX, scaledY, scaledZ, neutralVec);
	
	// Copy position vector
	pppCopyVector(transformedPos, rowPos);
	
	// Apply scaling to position
	transformedPos.x *= *(float *)(param2 + 0x18);
	transformedPos.y *= *(float *)(param2 + 0x1c);
	transformedPos.z *= *(float *)(param2 + 0x20);
	
	// Transform based on mode byte
	unsigned char mode = *((unsigned char *)(param2 + 0x28));
	
	if (mode == 1) {
		// Use world matrix directly
		// TODO: Matrix operations
	} else if (mode == 0) {
		// Add offset and use world matrix
		transformedPos.x += *(float *)(param2 + 8);
		transformedPos.y += *(float *)(param2 + 0xc);
		transformedPos.z += *(float *)(param2 + 0x10);
		// TODO: Matrix operations
	} else if (mode == 2) {
		// Use manager matrix, then apply scaling and camera
		// TODO: Matrix operations
		neutralVec.x = *(float *)(param2 + 8) * pppMngStPtr->m_scale.x + neutralVec.x;
		neutralVec.y = *(float *)(param2 + 0xc) * pppMngStPtr->m_scale.y + neutralVec.y;
		neutralVec.z = *(float *)(param2 + 0x10) * pppMngStPtr->m_scale.z + neutralVec.z;
	}
}