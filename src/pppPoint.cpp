#include "ffcc/pppPoint.h"

// Forward declare global variables used in assembly
extern int lbl_8032ED70;

/*
 * --INFO--
 * Address:	80065cfc
 * Size:	96
 */
void pppPoint(void* param1, void* param2, void* param3)
{
    // Early return if global flag is set
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    // Get ID values and compare
    int id1 = *(int*)param2;
    int id2 = *(int*)((char*)param1 + 0xc);
    if (id1 != id2) {
        return;
    }
    
    // Get position data from param3 via nested pointer access
    void* posData = *(void**)((char*)param3 + 0xc);
    posData = *(void**)posData;
    float* destPos = (float*)((char*)param1 + (int)posData + 0x80);
    
    // Get source position data from param2
    float* srcPos = (float*)((char*)param2 + 0x8);
    
    // Add source position to destination position (vector addition)
    destPos[0] += srcPos[0]; // X
    destPos[1] += srcPos[1]; // Y  
    destPos[2] += srcPos[2]; // Z
}

/*
 * --INFO--
 * Address:	80065cd8
 * Size:	36
 */
void pppPointCon(void* param1, void* param2)
{
    // Get position data via nested pointer access
    void* posData = *(void**)((char*)param2 + 0xc);
    posData = *(void**)posData;
    float* pos = (float*)((char*)param1 + (int)posData + 0x80);
    
    // Initialize position to zero
    pos[0] = 0.0f; // X
    pos[1] = 0.0f; // Y
    pos[2] = 0.0f; // Z
}