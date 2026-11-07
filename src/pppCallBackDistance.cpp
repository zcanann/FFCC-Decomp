#include "ffcc/pppCallBackDistance.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/game.h"
#include "ffcc/gobject.h"
#include <dolphin/mtx.h>

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
    s32 distanceOffset = ctrlTable->m_serializedDataOffsets[0];
    f32* distancePtr = (f32*)(object->m_workArea + distanceOffset);
    f32 distance;
    Vec particlePos;
    Vec worldPos;

    particlePos.x = pppMngSt->m_matrix.value[0][3];
    particlePos.y = pppMngSt->m_matrix.value[1][3];
    particlePos.z = pppMngSt->m_matrix.value[2][3];
    distance = PSVECDistance(&particlePos, &pppMngSt->m_paramVec0);

    if ((distance <= step->m_dataValIndex) || (*distancePtr <= distance)) {
        s32 partIndex;
        s32 graphFrame;
        s32 kind;
        s32 nodeIndex;
        s32 callbackType;

        pppMngSt = ppvMng;
        worldPos.x = pppMngSt->m_matrix.value[0][3];
        worldPos.y = pppMngSt->m_matrix.value[1][3];
        worldPos.z = pppMngSt->m_matrix.value[2][3];
        PSMTXMultVec(ppvWorldMatrix, &worldPos, &worldPos);

        partIndex = static_cast<s32>(pppMngSt - PartMng.m_pppMng);
        graphFrame = object->m_graphId / 0x1000;
        kind = pppMngSt->m_kind;
        nodeIndex = pppMngSt->m_nodeIndex;
        callbackType = step->m_initWork;

        Game.ParticleFrameCallback(partIndex, kind, nodeIndex, callbackType, graphFrame, &worldPos);
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
    Vec paramPos;
    Vec targetPos;
    s32 distanceOffset;
    f32* distancePtr;

    pppMngSt = ppvMng;
    distanceOffset = ctrlTable->m_serializedDataOffsets[0];
    distancePtr = (f32*)(object->m_workArea + distanceOffset);
    lookTarget = pppMngSt->m_lookTarget;
    targetPos = lookTarget->m_worldPosition;
    paramPos.x = pppMngSt->m_paramVec0.x;
    paramPos.y = pppMngSt->m_paramVec0.y;
    paramPos.z = pppMngSt->m_paramVec0.z;
    *distancePtr = PSVECDistance(&targetPos, &paramPos);
}
