#include "ffcc/pppParHitSph.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include <dolphin/mtx.h>

extern _pppMngSt* pppMngStPtr;
extern float FLOAT_80330700;
extern int CFlat;
extern Mtx ppvCameraMatrix0;

// Forward declarations 
class CGraphic;
extern CGraphic Graphic;
void DrawSphere(CGraphic* graphic, Mtx* matrix, void* color);

/*
 * --INFO--
 * PAL Address: 80093d04
 * PAL Size: 372b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppParHitSph(struct _pppPObject* param_1, int param_2)
{
    _pppMngSt* p_Var1;
    double dVar2;
    unsigned int local_a8;
    unsigned int local_a4;
    Vec local_a0;
    Vec local_94;
    Vec local_88;
    Mtx MStack_78;
    Mtx local_48;
    
    p_Var1 = pppMngStPtr;
    PSVECSubtract(&pppMngStPtr->m_position, &pppMngStPtr->m_previousPosition, &local_88);
    local_94.x = (pppMngStPtr->m_matrix).value[0][3];
    local_94.y = (pppMngStPtr->m_matrix).value[1][3];
    local_94.z = (pppMngStPtr->m_matrix).value[2][3];
    dVar2 = (double)(p_Var1->m_paramD * *(float*)(param_2 + 8));
    
    if (((FLOAT_80330700 == local_88.x) && (FLOAT_80330700 == local_88.y)) &&
        (FLOAT_80330700 == local_88.z)) {
        pppHitCylinderSendSystem(p_Var1, &local_94, &local_88, (float)dVar2, 0.0f);
    } else {
        pppHitCylinderSendSystem(p_Var1, &local_94, &local_88, (float)dVar2, *(float*)(param_2 + 4));
    }
    
    if ((CFlat & 0x200000) != 0) {
        local_a4 = 0xffffffff;
        PSMTXIdentity(&MStack_78);
        PSMTXIdentity(&local_48);
        local_48[0][0] = (float)dVar2;
        local_48[1][1] = (float)dVar2;
        local_48[2][2] = (float)dVar2;
        PSMTXConcat(&ppvCameraMatrix0, &MStack_78, &MStack_78);
        PSMTXMultVec(&MStack_78, &local_94, &local_a0);
        local_48[0][3] = local_a0.x;
        local_48[1][3] = local_a0.y;
        local_48[2][3] = local_a0.z;
        local_a8 = local_a4;
        DrawSphere(&Graphic, &local_48, &local_a8);
    }
}
