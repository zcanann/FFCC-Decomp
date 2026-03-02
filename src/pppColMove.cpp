#include "ffcc/pppColMove.h"

extern int lbl_8032ED70;

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
    int* data = ((int**)param2)[3];
    pppColMoveVec4S* target = (pppColMoveVec4S*)((char*)param1 + data[1] + 0x80);

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
    pppColMoveInput* input = ((pppColMoveInput**)param3)[3];
    int sourceOffset = input->id + 0x80;
    int moveOffset = input->pad + 0x80;
    pppColMoveVec4S* source = (pppColMoveVec4S*)((char*)param1 + sourceOffset);
    pppColMoveVec4S* movement = (pppColMoveVec4S*)((char*)param1 + moveOffset);

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (((int*)param2)[0] == ((int*)param1)[3]) {
        pppColMoveVec4S* paramMove = (pppColMoveVec4S*)((char*)param2 + 8);
        movement->x += paramMove->x;
        movement->y += paramMove->y;
        movement->z += paramMove->z;
        movement->w += paramMove->w;
    }

    source->x += movement->x;
    source->y += movement->y;
    source->z += movement->z;
    source->w += movement->w;
}
