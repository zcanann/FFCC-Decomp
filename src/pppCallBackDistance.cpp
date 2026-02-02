#include "ffcc/pppCallBackDistance.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x80141318
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructCallBackDistance(pppCallBackDistance* param1, UnkC* param2)
{
    Vec local_28;
    Vec local_1c;
    f64 dVar3;
    s32 iVar1;
    
    if (param2 && param2->m_serializedDataOffsets) {
        iVar1 = *param2->m_serializedDataOffsets;
        local_28.x = pppMngStPtr->m_position.x;
        local_28.y = pppMngStPtr->m_position.y;
        local_28.z = pppMngStPtr->m_position.z;
        local_1c.x = pppMngStPtr->m_scale.x;
        local_1c.y = pppMngStPtr->m_scale.y;
        local_1c.z = pppMngStPtr->m_scale.z;
        dVar3 = (f64)PSVECDistance(&local_28, &local_1c);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80141314
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructCallBackDistance(void)
{
}

/*
 * --INFO--
 * PAL Address: 0x80141204
 * PAL Size: 272b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameCallBackDistance(pppCallBackDistance* param1, UnkB* param2, UnkC* param3)
{
    Vec local_28;
    Vec local_1c;
    f64 dVar4;
    
    if (param2 && param3) {
        local_1c.x = pppMngStPtr->m_position.x;
        local_1c.y = pppMngStPtr->m_position.y;
        local_1c.z = pppMngStPtr->m_position.z;
        dVar4 = (f64)PSVECDistance(&local_1c, &pppMngStPtr->m_scale);
        
        if (dVar4 <= (f64)(f32)param2->m_dataValIndex) {
            local_28.x = pppMngStPtr->m_position.x;
            local_28.y = pppMngStPtr->m_position.y;
            local_28.z = pppMngStPtr->m_position.z;
        }
    }
}