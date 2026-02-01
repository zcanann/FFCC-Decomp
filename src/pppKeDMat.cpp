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
    
    // Load matrix data from pObject
    *(int*)&localMatrix.value[0][0] = *(int*)((char*)pObject + 0x10);
    *(int*)&localMatrix.value[0][1] = *(int*)((char*)pObject + 0x14);
    *(int*)&localMatrix.value[0][2] = *(int*)((char*)pObject + 0x18);
    *(int*)&localMatrix.value[0][3] = *(int*)((char*)pObject + 0x1C);
    *(int*)&localMatrix.value[1][0] = *(int*)((char*)pObject + 0x20);
    *(int*)&localMatrix.value[1][1] = *(int*)((char*)pObject + 0x24);
    *(int*)&localMatrix.value[1][2] = *(int*)((char*)pObject + 0x28);
    *(int*)&localMatrix.value[1][3] = *(int*)((char*)pObject + 0x2C);
    *(int*)&localMatrix.value[2][0] = *(int*)((char*)pObject + 0x30);
    *(int*)&localMatrix.value[2][1] = *(int*)((char*)pObject + 0x34);
    *(int*)&localMatrix.value[2][2] = *(int*)((char*)pObject + 0x38);
    *(int*)&localMatrix.value[2][3] = *(int*)((char*)pObject + 0x3C);
    
    // Copy world matrix
    *(int*)&worldMatrix.value[0][0] = *(int*)&ppvWorldMatrix[0][0];
    *(int*)&worldMatrix.value[0][1] = *(int*)&ppvWorldMatrix[0][1];
    *(int*)&worldMatrix.value[0][2] = *(int*)&ppvWorldMatrix[0][2];
    *(int*)&worldMatrix.value[0][3] = *(int*)&ppvWorldMatrix[0][3];
    *(int*)&worldMatrix.value[1][0] = *(int*)&ppvWorldMatrix[1][0];
    *(int*)&worldMatrix.value[1][1] = *(int*)&ppvWorldMatrix[1][1];
    *(int*)&worldMatrix.value[1][2] = *(int*)&ppvWorldMatrix[1][2];
    *(int*)&worldMatrix.value[1][3] = *(int*)&ppvWorldMatrix[1][3];
    *(int*)&worldMatrix.value[2][0] = *(int*)&ppvWorldMatrix[2][0];
    *(int*)&worldMatrix.value[2][1] = *(int*)&ppvWorldMatrix[2][1];
    *(int*)&worldMatrix.value[2][2] = *(int*)&ppvWorldMatrix[2][2];
    *(int*)&worldMatrix.value[2][3] = *(int*)&ppvWorldMatrix[2][3];
    
    // Multiply matrices
    pppFMATRIX resultMatrix;
    pppMulMatrix(resultMatrix, worldMatrix, localMatrix);
    
    // Copy result to target location
    pppCopyMatrix(*(pppFMATRIX*)((char*)pObject + 0x80), resultMatrix);
}