#include "ffcc/pppMatrixXYZ.h"

#include "ffcc/pppGetRotMatrixXYZ.h"

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
void pppMatrixXYZ(void* object, void* data)
{
    char* obj = (char*)object;
    char* angles = *(char**)((char*)data + 0xc);
    
    pppFMATRIX* matrix = (pppFMATRIX*)(obj + 0x10);
    
    int angleX = *(int*)(angles + 0) + 0x80;
    int angleY = *(int*)(angles + 4) + 0x80; 
    int angleZ = *(int*)(angles + 8) + 0x80;
    
    // Compute object offsets
    char* pX = obj + angleX;
    char* pY = obj + angleY;
    char* pZ = obj + angleZ;
    
    pppIVECTOR4 angleVector;
    angleVector.x = angleX;
    angleVector.y = angleY;
    angleVector.z = angleZ;
    
    pppGetRotMatrixXYZ(*matrix, &angleVector);
    
    Vec temp;
    
    // First PSVECScale - first column
    temp.x = matrix->value[0][0];
    temp.y = matrix->value[1][0];
    temp.z = matrix->value[2][0];
    PSVECScale(&temp, &temp, *(float*)(pY + 0));
    matrix->value[0][0] = temp.x;
    matrix->value[1][0] = temp.y;
    matrix->value[2][0] = temp.z;
    
    // Second PSVECScale - second column
    temp.x = matrix->value[0][1];
    temp.y = matrix->value[1][1];
    temp.z = matrix->value[2][1];
    PSVECScale(&temp, &temp, *(float*)(pY + 4));
    matrix->value[0][1] = temp.x;
    matrix->value[1][1] = temp.y;
    matrix->value[2][1] = temp.z;
    
    // Third PSVECScale - third column  
    temp.x = matrix->value[0][2];
    temp.y = matrix->value[1][2];
    temp.z = matrix->value[2][2];
    PSVECScale(&temp, &temp, *(float*)(pZ + 8));
    matrix->value[0][2] = temp.x;
    matrix->value[1][2] = temp.y;
    matrix->value[2][2] = temp.z;
    
    // Translation values
    matrix->value[0][3] = *(float*)(pX + 0);
    matrix->value[1][3] = *(float*)(pX + 4);
    matrix->value[2][3] = *(float*)(pX + 8);
}