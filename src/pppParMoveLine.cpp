#include "ffcc/pppParMoveLine.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x800906dc
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppParMoveLine(_pppPObject* param_1, int param_2)
{
    _pppMngSt* pppMngSt = pppMngStPtr;
    Vec local_1c;
    Vec VStack_28;
    float fVar1 = 0.0f;
    
    // Calculate direction vector - need to find correct field offsets
    // Based on objdiff, using position as both src and dst for now
    PSVECSubtract(&pppMngSt->m_position, &pppMngSt->m_position, &local_1c);
    
    // Store previous position (copying x,y,z individually based on assembly)
    Vec previousPos = pppMngSt->m_position;
    
    // Check if direction vector is non-zero
    if ((fVar1 != local_1c.x) || (fVar1 != local_1c.y) || (fVar1 != local_1c.z)) {
        PSVECNormalize(&local_1c, &VStack_28);
        
        // Scale by value from param_2 + 4 times m_paramC (field offset likely wrong)
        float scaleValue = *(float*)(param_2 + 4) * 1.0f; // placeholder for m_paramC
        PSVECScale(&VStack_28, &local_1c, scaleValue);
        PSVECAdd(&local_1c, &pppMngSt->m_position, &pppMngSt->m_position);
    }
    
    // Update matrix with new position - offsets from objdiff suggest different layout
    pppMngSt->m_matrix.value[0][3] = pppMngSt->m_position.x;
    pppMngSt->m_matrix.value[1][3] = pppMngSt->m_position.y; 
    pppMngSt->m_matrix.value[2][3] = pppMngSt->m_position.z;
    
    pppSetFpMatrix(pppMngSt);
}