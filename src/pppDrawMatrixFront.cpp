#include "ffcc/pppDrawMatrixFront.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x8006a584
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMatrixFront(_pppPObject* param_1)
{
    Vec localPos;
    
    // Apply scale transformation from global manager state  
    PSMTXScaleApply(
        *(Mtx*)((char*)param_1 + 0x10),
        *(Mtx*)((char*)param_1 + 0x40),
        pppMngStPtr->m_scale.x,
        pppMngStPtr->m_scale.y, 
        pppMngStPtr->m_scale.z
    );
    
    // Extract position from local matrix (offsets from assembly analysis)
    localPos.x = *(float*)((char*)param_1 + 0x1c);
    localPos.y = *(float*)((char*)param_1 + 0x2c);  
    localPos.z = *(float*)((char*)param_1 + 0x3c);
    
    // Transform position to world space
    PSMTXMultVec(ppvWorldMatrix, &localPos, &localPos);
    
    // Store transformed position (offsets from assembly analysis)
    *(float*)((char*)param_1 + 0x4c) = localPos.x;
    *(float*)((char*)param_1 + 0x5c) = localPos.y; 
    *(float*)((char*)param_1 + 0x6c) = localPos.z;
}