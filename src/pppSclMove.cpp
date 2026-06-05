#include "global.h"
#include "ffcc/pppSclMove.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>
#include "ffcc/ppp_linkage.h"

const float kPppSclMoveZero = 0.0f;

STATIC_ASSERT(offsetof(PppSclMoveOffsets, m_scaleOffset) == 0x0);
STATIC_ASSERT(offsetof(PppSclMoveOffsets, m_velocityOffset) == 0x4);

static inline PppSclMoveOffsets* GetSclMoveOffsets(_pppCtrlTable* ctrlTable)
{
    return reinterpret_cast<PppSclMoveOffsets*>(ctrlTable->m_serializedDataOffsets);
}

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
    PppSclMoveOffsets* offsets = GetSclMoveOffsets(param2);
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
void pppSclMove(_pppPObject* param1, PppSclMoveInput* input, _pppCtrlTable* param3)
{
    PppSclMoveOffsets* offsets = GetSclMoveOffsets(param3);
    float* dataA = (float*)(param1->m_workArea + offsets->m_scaleOffset);
    float* dataB = (float*)(param1->m_workArea + offsets->m_velocityOffset);

    if (ppvUserStopPartF != 0) {
        return;
    }

    if (input->m_graphId == param1->m_graphId) {
        dataB[0] += input->m_scale[0];
        dataB[1] += input->m_scale[1];
        dataB[2] += input->m_scale[2];
    }

    dataA[0] += dataB[0];
    dataA[1] += dataB[1];
    dataA[2] += dataB[2];
}
