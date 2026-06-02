#include "ffcc/pppSclMove.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>
#include "ffcc/ppp_linkage.h"

const float kPppSclMoveZero = 0.0f;

struct PppSclMoveInput {
    int m_graphId;
    int m_padding;
    f32 m_scale[3];
};

struct PppSclMoveOffsets {
    int m_scaleOffset;
    int m_velocityOffset;
};

/*
 * --INFO--
 * PAL Address: 0x80063210
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSclMoveCon(_pppPObject* param1, _pppCtrlTable* param2)
{
    PppSclMoveOffsets* offsets = (PppSclMoveOffsets*)param2->m_serializedDataOffsets;
    float* data1 = (float*)(param1->m_workArea + offsets->m_velocityOffset);
    float zero = kPppSclMoveZero;
    data1[2] = zero;
    data1[1] = zero;
    data1[0] = zero;
}

/*
 * --INFO--
 * PAL Address: 0x80063234
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSclMove(_pppPObject* param1, void* param2, _pppCtrlTable* param3)
{
    PppSclMoveOffsets* offsets = (PppSclMoveOffsets*)param3->m_serializedDataOffsets;
    float* dataA = (float*)(param1->m_workArea + offsets->m_scaleOffset);
    float* dataB = (float*)(param1->m_workArea + offsets->m_velocityOffset);

    if (ppvUserStopPartF != 0) {
        return;
    }

    PppSclMoveInput* input = (PppSclMoveInput*)param2;
    if (input->m_graphId == param1->m_graphId) {
        dataB[0] += input->m_scale[0];
        dataB[1] += input->m_scale[1];
        dataB[2] += input->m_scale[2];
    }

    dataA[0] += dataB[0];
    dataA[1] += dataB[1];
    dataA[2] += dataB[2];
}
