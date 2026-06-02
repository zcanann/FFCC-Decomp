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
    short* accel = (short*)(object->m_workArea + offsets[1]);
    
    accel[3] = 0;
    accel[2] = 0;
    accel[1] = 0;
    accel[0] = 0;
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
void pppColAccele(_pppPObject* object, void* data, _pppCtrlTable* ctrlTable)
{
    int* offsets = ctrlTable->m_serializedDataOffsets;
    int offset0 = offsets[0];
    int offset1 = offsets[1];
    short* accel1 = (short*)(object->m_workArea + offset0);
    int frameData;
    short* accel2 = (short*)(object->m_workArea + offset1);
    
    if (gPppCalcDisabled != 0)
        return;
    
    frameData = *(int*)data;
    if (frameData != object->m_graphId) {
        goto accumulate;
    }
    
    short* inputAccel = (short*)((char*)data + 8);
    accel2[0] += inputAccel[0];
    accel2[1] += inputAccel[1];
    accel2[2] += inputAccel[2];
    accel2[3] += inputAccel[3];
    
accumulate:
    accel1[0] += accel2[0];
    accel1[1] += accel2[1];
    accel1[2] += accel2[2];
    accel1[3] += accel2[3];
}
