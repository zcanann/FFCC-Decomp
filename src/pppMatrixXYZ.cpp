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
    // Get rotation matrix from angle data 
    pppGetRotMatrixXYZ(matrix, (pppIVECTOR4*)param->m_extraPositionPtr);
    
    // Scale X column (first column) directly
    matrix.value[0][0] *= param->m_scalePtr->x;
    matrix.value[1][0] *= param->m_scalePtr->x;
    matrix.value[2][0] *= param->m_scalePtr->x;
    
    // Scale Y column (second column) directly  
    matrix.value[0][1] *= param->m_scalePtr->y;
    matrix.value[1][1] *= param->m_scalePtr->y;
    matrix.value[2][1] *= param->m_scalePtr->y;
    
    // Scale Z column (third column) directly
    matrix.value[0][2] *= param->m_scalePtr->z;
    matrix.value[1][2] *= param->m_scalePtr->z;
    matrix.value[2][2] *= param->m_scalePtr->z;
    
    // Set translation components from position
    matrix.value[0][3] = param->m_positionOffsetPtr->x;
    matrix.value[1][3] = param->m_positionOffsetPtr->y; 
    matrix.value[2][3] = param->m_positionOffsetPtr->z;
}