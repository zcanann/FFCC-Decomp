#include "ffcc/pppMatrixXZY.h"

#include "ffcc/pppGetRotMatrixXZY.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 80060380
 * PAL Size: 320b
 */
void pppMatrixXZY(pppFMATRIX& mtx, void* param)
{
    // Based on assembly analysis:
    // param is a structure pointer containing data at offset 0xc
    void** dataPtr = (void**)((char*)param + 0xc);
    if (dataPtr == nullptr || *dataPtr == nullptr) {
        return;
    }
    
    // The data structure at *dataPtr contains vectors/scale factors
    float* data = (float*)*dataPtr;
    Vec scale = {data[0], data[1], data[2]};
    
    // Build rotation matrix
    pppFMATRIX rotMatrix;
    pppIVECTOR4 angles = {0, 0, 0, 0}; // Placeholder angles
    pppGetRotMatrixXZY(rotMatrix, &angles);
    
    // Scale the matrix columns based on the data
    Vec col0 = {rotMatrix.value[0][0], rotMatrix.value[1][0], rotMatrix.value[2][0]};
    Vec col1 = {rotMatrix.value[0][1], rotMatrix.value[1][1], rotMatrix.value[2][1]};
    Vec col2 = {rotMatrix.value[0][2], rotMatrix.value[1][2], rotMatrix.value[2][2]};
    
    PSVECScale(&col0, &col0, scale.x);
    PSVECScale(&col1, &col1, scale.y);  
    PSVECScale(&col2, &col2, scale.z);
    
    // Update output matrix
    mtx.value[0][0] = col0.x; mtx.value[1][0] = col0.y; mtx.value[2][0] = col0.z;
    mtx.value[0][1] = col1.x; mtx.value[1][1] = col1.y; mtx.value[2][1] = col1.z;
    mtx.value[0][2] = col2.x; mtx.value[1][2] = col2.y; mtx.value[2][2] = col2.z;
    
    // Translation components from assembly
    mtx.value[0][3] = data[3];
    mtx.value[1][3] = data[4]; 
    mtx.value[2][3] = data[5];
}