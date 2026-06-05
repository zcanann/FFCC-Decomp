#include "global.h"
#include "ffcc/pppSclAccele.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_linkage.h"

const float kPppSclAcceleZero = 0.0f;

struct PppSclAcceleDataOffsets {
    s32 m_scaleOffset;
    s32 m_accelOffset;
};

STATIC_ASSERT(offsetof(PppSclAcceleDataOffsets, m_scaleOffset) == 0x0);
STATIC_ASSERT(offsetof(PppSclAcceleDataOffsets, m_accelOffset) == 0x4);

static inline PppSclAcceleDataOffsets* GetPppSclAcceleDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<PppSclAcceleDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline float* GetPppSclAcceleScale(_pppPObject* obj, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<float*>(obj->m_workArea + GetPppSclAcceleDataOffsets(ctrl)->m_scaleOffset);
}

static inline float* GetPppSclAcceleAccel(_pppPObject* obj, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<float*>(obj->m_workArea + GetPppSclAcceleDataOffsets(ctrl)->m_accelOffset);
}

/*
 * --INFO--
 * PAL Address: 0x80063150
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSclAcceleCon(_pppPObject* arg1, _pppCtrlTable* arg2){
    float* accel = GetPppSclAcceleAccel(arg1, arg2);
    float zero = kPppSclAcceleZero;

    accel[2] = zero;
    accel[1] = zero;
    accel[0] = zero;
}

/*
 * --INFO--
 * PAL Address: 0x80063174
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSclAccele(_pppPObject* arg1, PppSclAcceleStep* arg2, _pppCtrlTable* arg3){
    float* scale = GetPppSclAcceleScale(arg1, arg3);
    float* accel = GetPppSclAcceleAccel(arg1, arg3);

    if (ppvUserStopPartF != 0) {
        return;
    }

    if (arg2->m_graphId == arg1->m_graphId) {
        accel[0] += arg2->m_x;
        accel[1] += arg2->m_y;
        accel[2] += arg2->m_z;
    }

    scale[0] += accel[0];
    scale[1] += accel[1];
    scale[2] += accel[2];
}
