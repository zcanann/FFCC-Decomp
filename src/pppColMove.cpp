#include "ffcc/pppColMove.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_linkage.h"


typedef struct {
    short x;
    short y;
    short z;
    short w;
} pppColMoveVec4S;

typedef struct {
    int id;
    int pad;
    pppColMoveVec4S move;
} pppColMoveInput;

/*
 * --INFO--
 * PAL Address: 0x80065000
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppColMoveCon(void* param1, void* param2)
{
    _pppPObject* object = (_pppPObject*)param1;
    int* data = ((int**)param2)[3];
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
void pppColMove(void* param1, void* param2, void* param3)
{
    _pppPObject* object = (_pppPObject*)param1;
    pppColMoveInput* input = ((pppColMoveInput**)param3)[3];
    pppColMoveVec4S* sourceMove = (pppColMoveVec4S*)(object->m_workArea + input->id);
    pppColMoveVec4S* movementMove = (pppColMoveVec4S*)(object->m_workArea + input->pad);

    if (ppvUserStopPartF != 0) {
        return;
    }

    if (((int*)param2)[0] == object->m_graphId) {
        pppColMoveVec4S* paramMove = (pppColMoveVec4S*)((char*)param2 + 8);
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
