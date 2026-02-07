#include "ffcc/pppMatrixXYZ.h"
#include "ffcc/pppGetRotMatrixXYZ.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x80065398
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO  
 * JP Size: TODO
 */
void pppMatrixXYZ(pppFMATRIX& matrix, PPPCREATEPARAM* param)
{
    Vec tempVec1;
    Vec tempVec2; 
    Vec tempVec3;
    
    // Get rotation matrix from angle data 
    pppGetRotMatrixXYZ(matrix, (pppIVECTOR4*)param->m_extraPositionPtr);

    // Extract and scale first column vector (X-axis)
    tempVec1.x = matrix.value[0][0];
    tempVec1.y = matrix.value[1][0]; 
    tempVec1.z = matrix.value[2][0];
    
    PSVECScale(&tempVec1, &tempVec1, param->m_scalePtr->x);
    
    matrix.value[0][0] = tempVec1.x;
    matrix.value[1][0] = tempVec1.y;
    matrix.value[2][0] = tempVec1.z;
    
    // Extract and scale second column vector (Y-axis)
    tempVec2.x = matrix.value[0][1];
    tempVec2.y = matrix.value[1][1];
    tempVec2.z = matrix.value[2][1];
    
    PSVECScale(&tempVec2, &tempVec2, param->m_scalePtr->y);
    
    matrix.value[0][1] = tempVec2.x;
    matrix.value[1][1] = tempVec2.y; 
    matrix.value[2][1] = tempVec2.z;
    
    // Extract and scale third column vector (Z-axis)
    tempVec3.x = matrix.value[0][2];
    tempVec3.y = matrix.value[1][2]; 
    tempVec3.z = matrix.value[2][2];

    PSVECScale(&tempVec3, &tempVec3, param->m_scalePtr->z);

    matrix.value[0][2] = tempVec3.x;
    matrix.value[1][2] = tempVec3.y;
    matrix.value[2][2] = tempVec3.z;

    // Set translation components from position
    matrix.value[0][3] = param->m_positionOffsetPtr->x;
    matrix.value[1][3] = param->m_positionOffsetPtr->y;
    matrix.value[2][3] = param->m_positionOffsetPtr->z;
}
