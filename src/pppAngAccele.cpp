#include "ffcc/pppAngAccele.h"
#include "ffcc/ppp_linkage.h"


/*
 * --INFO--
 * PAL Address: 0x80064d18
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppAngAcceleCon(pppAngAcceleObj* obj, pppAngAcceleUnkC* param)
{
    int* angularAccel = (int*)((char*)obj + param->m_serializedDataOffsets[1] + 0x80);

    angularAccel[2] = 0;
    angularAccel[1] = 0;
    angularAccel[0] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80064d3c
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppAngAccele(pppAngAcceleObj* obj, pppAngAcceleUnkB* param_2, pppAngAcceleUnkC* param_3)
{
    int* angularVelocity = (int*)((char*)obj + *param_3->m_serializedDataOffsets + 0x80);
    int* angularAccel = (int*)((char*)obj + param_3->m_serializedDataOffsets[1] + 0x80);

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (param_2->m_graphId == obj->m_graphId) {
        angularAccel[0] += param_2->m_x;
        angularAccel[1] += param_2->m_y;
        angularAccel[2] += param_2->m_z;
    }

    angularVelocity[0] += angularAccel[0];
    angularVelocity[1] += angularAccel[1];
    angularVelocity[2] += angularAccel[2];
}
