#include "global.h"
#include "ffcc/pppColor.h"
#include "ffcc/partMng.h"
#include "types.h"
#include "ffcc/ppp_linkage.h"

struct PppColorDataOffsets {
    s32 m_workOffset;
};

STATIC_ASSERT(offsetof(PppColorDataOffsets, m_workOffset) == 0x0);

static inline PppColorDataOffsets* GetPppColorDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<PppColorDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline _pppColorWork* GetPppColorWork(_pppPObject* obj, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<_pppColorWork*>(obj->m_workArea + GetPppColorDataOffsets(ctrl)->m_workOffset);
}

/*
 * --INFO--
 * PAL Address: 0x8005FF8C  
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppColorCon(_pppPObject* param1, _pppCtrlTable* param2){
    _pppColorWork* work = GetPppColorWork(param1, param2);
    
    work->a = 0;
    work->b = 0;
    work->g = 0;
    work->r = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8005FFB4
 * PAL Size: 416b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppColor(_pppPObject* param1, pppColorStep* step, _pppCtrlTable* param3){
    _pppColorWork* work = GetPppColorWork(param1, param3);

    if (ppvUserStopPartF != 0) {
        return;
    }

    s32 id1 = step->m_graphId;
    s32 id2 = param1->m_graphId;

    if (id1 == id2) {
        work->r += step->m_colors[0];
        work->g += step->m_colors[1];
        work->b += step->m_colors[2];
        work->a += step->m_colors[3];
    }

    if (ppvMng->m_useOwnerScaleSign != 0) {
        work->result.r = (u8)((float)(work->r >> 7) * ((float*)ppvMng)[14]);
        work->result.g = (u8)((float)(work->g >> 7) * ((float*)ppvMng)[15]);
        work->result.b = (u8)((float)(work->b >> 7) * ((float*)ppvMng)[16]);
        work->result.a = (u8)((float)(work->a >> 7) * ((float*)ppvMng)[17]);
        return;
    }

    work->result.r = (u8)(work->r >> 7);
    work->result.g = (u8)(work->g >> 7);
    work->result.b = (u8)(work->b >> 7);
    work->result.a = (u8)(work->a >> 7);
}
