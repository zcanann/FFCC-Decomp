#include "global.h"
#include "ffcc/pppAngAccele.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_linkage.h"

struct PppAngAcceleDataOffsets {
    s32 m_velocityOffset;
    s32 m_accelOffset;
};

STATIC_ASSERT(offsetof(PppAngAcceleDataOffsets, m_velocityOffset) == 0x0);
STATIC_ASSERT(offsetof(PppAngAcceleDataOffsets, m_accelOffset) == 0x4);

static inline PppAngAcceleDataOffsets* GetPppAngAcceleDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<PppAngAcceleDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline int* GetPppAngAcceleVelocity(_pppPObject* obj, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<int*>(obj->m_workArea + GetPppAngAcceleDataOffsets(ctrl)->m_velocityOffset);
}

static inline int* GetPppAngAcceleAccel(_pppPObject* obj, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<int*>(obj->m_workArea + GetPppAngAcceleDataOffsets(ctrl)->m_accelOffset);
}

/*
 * --INFO--
 * PAL Address: 0x80064d18
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppAngAcceleCon(_pppPObject* obj, _pppCtrlTable* param)
{
    int* angularAccel = GetPppAngAcceleAccel(obj, param);

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
void pppAngAccele(_pppPObject* obj, pppAngAcceleStep* param_2, _pppCtrlTable* param_3)
{
    int* angularVelocity = GetPppAngAcceleVelocity(obj, param_3);
    int* angularAccel = GetPppAngAcceleAccel(obj, param_3);

    if (ppvUserStopPartF != 0) {
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
