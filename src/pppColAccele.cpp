#include "ffcc/pppColAccele.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_linkage.h"

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
    int* offsets = ctrlTable->m_serializedDataOffsets;
    pppColorDelta* accel = (pppColorDelta*)(object->m_workArea + offsets[1]);
    
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
    int* offsets = ctrlTable->m_serializedDataOffsets;
    int offset0 = offsets[0];
    int offset1 = offsets[1];
    pppColorDelta* accel1 = (pppColorDelta*)(object->m_workArea + offset0);
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
    accel1->r += accel2->r;
    accel1->g += accel2->g;
    accel1->b += accel2->b;
    accel1->a += accel2->a;
}
