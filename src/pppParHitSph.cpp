#include "ffcc/pppParHitSph.h"
#include "ffcc/graphic.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include <dolphin/mtx.h>

extern _pppMngSt* pppMngStPtr;
extern float FLOAT_80330700;
extern unsigned char CFlat[];

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
    Vec local_a0;
    Vec local_94;
    Vec local_88;
    _GXColor local_7c;
    Mtx MStack_78;
    Mtx local_48;
    
    p_Var1 = pppMngStPtr;
    PSVECSubtract(&pppMngStPtr->m_position, (Vec*)((char*)pppMngStPtr + 0x48), &local_88);
    local_94.x = (pppMngStPtr->m_matrix).value[0][3];
    local_94.y = (pppMngStPtr->m_matrix).value[1][3];
    local_94.z = (pppMngStPtr->m_matrix).value[2][3];
    dVar2 = (double)(*(float*)((char*)p_Var1 + 0x84) * *(float*)(param_2 + 8));
    
    if (((FLOAT_80330700 == local_88.x) && (FLOAT_80330700 == local_88.y)) &&
        (FLOAT_80330700 == local_88.z)) {
        pppHitCylinderSendSystem(p_Var1, &local_94, &local_88, (float)dVar2, 0.0f);
    } else {
        pppHitCylinderSendSystem(p_Var1, &local_94, &local_88, (float)dVar2, *(float*)(param_2 + 4));
    }
    
    if ((*(unsigned int*)(CFlat + 0x129c) & 0x200000) != 0) {
        PSMTXIdentity(MStack_78);
        PSMTXIdentity(local_48);
        local_48[0][0] = (float)dVar2;
        local_48[1][1] = (float)dVar2;
        local_48[2][2] = (float)dVar2;
        PSMTXConcat(ppvCameraMatrix0, MStack_78, MStack_78);
        PSMTXMultVec(MStack_78, &local_94, &local_a0);
        local_48[0][3] = local_a0.x;
        local_48[1][3] = local_a0.y;
        local_48[2][3] = local_a0.z;
        local_7c.r = 0xff;
        local_7c.g = 0xff;
        local_7c.b = 0xff;
        local_7c.a = 0xff;
        Graphic.DrawSphere(local_48, local_7c);
    }
}
