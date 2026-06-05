#include "ffcc/pppSclAccele.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_linkage.h"

const float kPppSclAcceleZero = 0.0f;

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
    float* accel = (float*)(arg1->m_workArea + arg2->m_serializedDataOffsets[1]);
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
    float* scale = (float*)(arg1->m_workArea + arg3->m_serializedDataOffsets[0]);
    float* accel = (float*)(arg1->m_workArea + arg3->m_serializedDataOffsets[1]);

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
