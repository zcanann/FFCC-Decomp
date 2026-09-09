#include "global.h"
#include "ffcc/pppColAccele.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_linkage.h"

STATIC_ASSERT(sizeof(pppColAcceleDataOffsets) == 0x8);
STATIC_ASSERT(offsetof(pppColAcceleDataOffsets, m_colorOffset) == 0x0);
STATIC_ASSERT(offsetof(pppColAcceleDataOffsets, m_accelerationOffset) == 0x4);

static inline pppColAcceleDataOffsets* GetColAcceleDataOffsets(_pppCtrlTable* ctrlTable)
{
    return reinterpret_cast<pppColAcceleDataOffsets*>(ctrlTable->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 0x8005fdc4
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppColAcceleCon(_pppPObject* object, _pppCtrlTable* ctrlTable)
{
    pppColAcceleDataOffsets* offsets = GetColAcceleDataOffsets(ctrlTable);
    pppColorDelta* accel = (pppColorDelta*)(object->m_workArea + offsets->m_accelerationOffset);

    accel->a = 0;
    accel->b = 0;
    accel->g = 0;
    accel->r = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8005fdec
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppColAccele(_pppPObject* object, pppColAcceleStep* data, _pppCtrlTable* ctrlTable)
{
    pppColAcceleDataOffsets* offsets = GetColAcceleDataOffsets(ctrlTable);
    int offset0 = offsets->m_colorOffset;
    int offset1 = offsets->m_accelerationOffset;
    VColor* color = (VColor*)(object->m_workArea + offset0);
    int frameData;
    pppColorDelta* accel2 = (pppColorDelta*)(object->m_workArea + offset1);

    if (ppvUserStopPartF != 0)
        return;

    frameData = data->m_graphId;
    if (frameData != object->m_graphId) {
        goto accumulate;
    }

    accel2->r += data->m_acceleration.r;
    accel2->g += data->m_acceleration.g;
    accel2->b += data->m_acceleration.b;
    accel2->a += data->m_acceleration.a;

accumulate:
    color->m_red += accel2->r;
    color->m_green += accel2->g;
    color->m_blue += accel2->b;
    color->m_alpha += accel2->a;
}
