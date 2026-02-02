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
    
    // Load local matrix from pObject structure at offset 0x10
    localMatrix = *(pppFMATRIX*)((char*)pObject + 0x10);
    
    // Copy world matrix from global matrix
    worldMatrix = *(pppFMATRIX*)&ppvWorldMatrix;
    
    // Multiply matrices: result = world * local
    pppMulMatrix(resultMatrix, worldMatrix, localMatrix);
    
    // Copy result to target location at offset 0x80
    pppCopyMatrix(*(pppFMATRIX*)((char*)pObject + 0x80), resultMatrix);
}