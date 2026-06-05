#include "global.h"
#include "ffcc/pppColMove.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_linkage.h"

struct pppColMoveDataOffsets
{
    s32 m_sourceMoveOffset;
    s32 m_accumulatedMoveOffset;
};

STATIC_ASSERT(offsetof(pppColMoveDataOffsets, m_sourceMoveOffset) == 0x0);
STATIC_ASSERT(offsetof(pppColMoveDataOffsets, m_accumulatedMoveOffset) == 0x4);

static inline pppColMoveDataOffsets* GetColMoveDataOffsets(_pppCtrlTable* ctrlTable)
{
    return reinterpret_cast<pppColMoveDataOffsets*>(ctrlTable->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 0x80065000
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppColMoveCon(_pppPObject* object, _pppCtrlTable* ctrlTable)
{
    pppColMoveDataOffsets* data = GetColMoveDataOffsets(ctrlTable);
    pppColMoveVec4S* target = (pppColMoveVec4S*)(object->m_workArea + data->m_accumulatedMoveOffset);

    target->w = 0;
    target->z = 0;
    target->y = 0;
    target->x = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80065028
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppColMove(_pppPObject* object, pppColMoveInput* step, _pppCtrlTable* ctrlTable)
{
    pppColMoveDataOffsets* offsets = GetColMoveDataOffsets(ctrlTable);
    pppColMoveVec4S* sourceMove = (pppColMoveVec4S*)(object->m_workArea + offsets->m_sourceMoveOffset);
    pppColMoveVec4S* movementMove = (pppColMoveVec4S*)(object->m_workArea + offsets->m_accumulatedMoveOffset);

    if (ppvUserStopPartF != 0) {
        return;
    }

    if (step->id == object->m_graphId) {
        pppColMoveVec4S* paramMove = &step->move;
        movementMove->x += paramMove->x;
        movementMove->y += paramMove->y;
        movementMove->z += paramMove->z;
        movementMove->w += paramMove->w;
    }

    sourceMove->x += movementMove->x;
    sourceMove->y += movementMove->y;
    sourceMove->z += movementMove->z;
    sourceMove->w += movementMove->w;
}
