#include "ffcc/pppKeDMat.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"

/*
 * --INFO--
 * PAL Address: 0x80095854
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeDMatDraw(_pppPObject* pObject)
{
    pppFMATRIX localMatrix;
    pppFMATRIX worldMatrix;
    pppFMATRIX resultMatrix;
    
    // Load matrix data from pObject (cast to float*)
    localMatrix.value[0][0] = ((float*)pObject)[4];
    localMatrix.value[0][1] = ((float*)pObject)[5];
    localMatrix.value[0][2] = ((float*)pObject)[6];
    localMatrix.value[0][3] = ((float*)pObject)[7];
    localMatrix.value[1][0] = ((float*)pObject)[8];
    localMatrix.value[1][1] = ((float*)pObject)[9];
    localMatrix.value[1][2] = ((float*)pObject)[10];
    localMatrix.value[1][3] = ((float*)pObject)[11];
    localMatrix.value[2][0] = ((float*)pObject)[12];
    localMatrix.value[2][1] = ((float*)pObject)[13];
    localMatrix.value[2][2] = ((float*)pObject)[14];
    localMatrix.value[2][3] = ((float*)pObject)[15];
    
    // Copy world matrix from global Mtx to pppFMATRIX
    worldMatrix.value[0][0] = ppvWorldMatrix[0][0];
    worldMatrix.value[0][1] = ppvWorldMatrix[0][1];
    worldMatrix.value[0][2] = ppvWorldMatrix[0][2];
    worldMatrix.value[0][3] = ppvWorldMatrix[0][3];
    worldMatrix.value[1][0] = ppvWorldMatrix[1][0];
    worldMatrix.value[1][1] = ppvWorldMatrix[1][1];
    worldMatrix.value[1][2] = ppvWorldMatrix[1][2];
    worldMatrix.value[1][3] = ppvWorldMatrix[1][3];
    worldMatrix.value[2][0] = ppvWorldMatrix[2][0];
    worldMatrix.value[2][1] = ppvWorldMatrix[2][1];
    worldMatrix.value[2][2] = ppvWorldMatrix[2][2];
    worldMatrix.value[2][3] = ppvWorldMatrix[2][3];
    
    // Multiply matrices: result = world * local
    pppMulMatrix(resultMatrix, worldMatrix, localMatrix);
    
    // Copy result to target location at offset 0x80
    pppCopyMatrix(*(pppFMATRIX*)((char*)pObject + 0x80), resultMatrix);
}