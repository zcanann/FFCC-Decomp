#include "ffcc/pppCallBackDistance.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/game.h"
#include "ffcc/gobject.h"
#include <dolphin/mtx.h>

STATIC_ASSERT(sizeof(CallBackDistanceDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(CallBackDistanceDataOffsets, m_distanceOffset) == 0x0);

static inline CallBackDistanceDataOffsets* GetCallBackDistanceDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<CallBackDistanceDataOffsets*>(ctrl->m_serializedDataOffsets);
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
void pppFrameCallBackDistance(_pppPObject* object, pppCallBackDistanceStep* step, _pppCtrlTable* ctrlTable)
{
    _pppMngSt* pppMngSt = ppvMng;
    s32 distanceOffset = GetCallBackDistanceDataOffsets(ctrlTable)->m_distanceOffset;
    f32* distancePtr = (f32*)(object->m_workArea + distanceOffset);
    f32 distance;
    Vec local_1c;
    Vec local_28;

    local_1c.x = pppMngSt->m_matrix.value[0][3];
    local_1c.y = pppMngSt->m_matrix.value[1][3];
    local_1c.z = pppMngSt->m_matrix.value[2][3];
    distance = PSVECDistance(&local_1c, &pppMngSt->m_paramVec0);

    if ((distance <= step->m_dataValIndex) || (*distancePtr <= distance)) {
        s32 partIndex;
        s32 graphFrame;
        s32 m_kind;
        s32 m_nodeIndex;
        s32 initWork;

        pppMngSt = ppvMng;
        local_28.x = pppMngSt->m_matrix.value[0][3];
        local_28.y = pppMngSt->m_matrix.value[1][3];
        local_28.z = pppMngSt->m_matrix.value[2][3];
        PSMTXMultVec(ppvWorldMatrix, &local_28, &local_28);

        partIndex = static_cast<s32>(pppMngSt - PartMng.m_pppMng);
        graphFrame = object->m_graphId / 0x1000;
        m_kind = pppMngSt->m_kind;
        m_nodeIndex = pppMngSt->m_nodeIndex;
        initWork = step->m_initWOrk;

        Game.ParticleFrameCallback(partIndex, m_kind, m_nodeIndex, initWork, graphFrame, &local_28);
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
void pppDestructCallBackDistance(_pppPObject*, _pppCtrlTable*)
{
}

/*
 * --INFO--
 * PAL Address: 0x80141318
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructCallBackDistance(_pppPObject* object, _pppCtrlTable* ctrlTable)
{
    _pppMngSt* pppMngSt;
    CGObject* lookTarget;
    Vec local_1c;
    Vec local_28;
    s32 dataOffset;
    f32* distancePtr;

    pppMngSt = ppvMng;
    dataOffset = GetCallBackDistanceDataOffsets(ctrlTable)->m_distanceOffset;
    distancePtr = (f32*)(object->m_workArea + dataOffset);
    lookTarget = pppMngSt->m_lookTarget;
    local_28 = lookTarget->m_worldPosition;
    local_1c.x = pppMngSt->m_paramVec0.x;
    local_1c.y = pppMngSt->m_paramVec0.y;
    local_1c.z = pppMngSt->m_paramVec0.z;
    *distancePtr = PSVECDistance(&local_28, &local_1c);
}
