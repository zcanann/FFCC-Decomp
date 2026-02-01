#include "ffcc/pppMatrixZXY.h"
#include "ffcc/pppGetRotMatrixZXY.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x80065898
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppMatrixZXY(pppFMATRIX& matrix, void* data, pppIVECTOR4* angle)
{
	Vec tempVec1, tempVec2, tempVec3;
	
	// Get rotation matrix first
	pppGetRotMatrixZXY(matrix, angle);
	
	// data+0xc points to structure containing 3 floats
	float* scalePtr = *(float**)((char*)data + 0xc);
	
	// Extract first column into temp vector and scale
	tempVec1.x = matrix.value[0][0];
	tempVec1.y = matrix.value[1][0];  
	tempVec1.z = matrix.value[2][0];
	PSVECScale(&tempVec1, &tempVec1, scalePtr[0]);
	matrix.value[0][0] = tempVec1.x;
	matrix.value[1][0] = tempVec1.y;
	matrix.value[2][0] = tempVec1.z;
	
	// Extract second column into temp vector and scale
	tempVec2.x = matrix.value[0][1];
	tempVec2.y = matrix.value[1][1];
	tempVec2.z = matrix.value[2][1];
	PSVECScale(&tempVec2, &tempVec2, scalePtr[1]);
	matrix.value[0][1] = tempVec2.x;
	matrix.value[1][1] = tempVec2.y;
	matrix.value[2][1] = tempVec2.z;
	
	// Extract third column into temp vector and scale
	tempVec3.x = matrix.value[0][2];
	tempVec3.y = matrix.value[1][2];
	tempVec3.z = matrix.value[2][2];
	PSVECScale(&tempVec3, &tempVec3, scalePtr[2]);
	matrix.value[0][2] = tempVec3.x;
	matrix.value[1][2] = tempVec3.y;
	matrix.value[2][2] = tempVec3.z;
	
	// Copy translation values from the data structure 
	// Based on assembly, it reads 3 values from offsets after the scale data
	matrix.value[0][3] = scalePtr[3];
	matrix.value[1][3] = scalePtr[4];
	matrix.value[2][3] = scalePtr[5];
}