#include "global.h"
#include "ffcc/pppAngAccele.h"
#include "ffcc/partMng.h"
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
void pppAngAcceleCon(_pppPObject* obj, _pppCtrlTable* ctrl)
{
    int* angularAccel = (int*)(obj->m_workArea + ctrl->m_serializedDataOffsets[1]);

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
void pppAngAccele(_pppPObject* obj, pppAngAcceleStep* step, _pppCtrlTable* ctrl)
{
    int* angularVelocity = (int*)(obj->m_workArea + ctrl->m_serializedDataOffsets[0]);
    int* angularAccel = (int*)(obj->m_workArea + ctrl->m_serializedDataOffsets[1]);

    if (ppvUserStopPartF != 0) {
        return;
    }

    if (step->m_graphId == obj->m_graphId) {
        angularAccel[0] += step->m_x;
        angularAccel[1] += step->m_y;
        angularAccel[2] += step->m_z;
    }

    angularVelocity[0] += angularAccel[0];
    angularVelocity[1] += angularAccel[1];
    angularVelocity[2] += angularAccel[2];
}
