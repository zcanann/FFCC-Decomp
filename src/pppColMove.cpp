#include "ffcc/pppColMove.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_linkage.h"

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
    int* data = ctrlTable->m_serializedDataOffsets;
    pppColMoveVec4S* target = (pppColMoveVec4S*)(object->m_workArea + data[1]);

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
    pppColMoveInput* input = (pppColMoveInput*)ctrlTable->m_serializedDataOffsets;
    pppColMoveVec4S* sourceMove = (pppColMoveVec4S*)(object->m_workArea + input->id);
    pppColMoveVec4S* movementMove = (pppColMoveVec4S*)(object->m_workArea + input->pad);

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
