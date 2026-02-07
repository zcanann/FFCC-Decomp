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
    int state = lbl_8032ED70;
    int* work = ((int**)param3)[3];
    pppColMoveInput* input = (pppColMoveInput*)param2;
    pppColMoveVec4S* src;
    pppColMoveVec4S* dst;

    if (state != 0) {
        return;
    }

    src = (pppColMoveVec4S*)((char*)param1 + work[0] + 0x80);
    dst = (pppColMoveVec4S*)((char*)param1 + work[1] + 0x80);

    if (input->id == ((int*)param1)[3]) {
        goto add_src;
    }

    dst->x += input->move.x;
    dst->y += input->move.y;
    dst->z += input->move.z;
    dst->w += input->move.w;

add_src:
    src->x += dst->x;
    src->y += dst->y;
    src->z += dst->z;
    src->w += dst->w;
}
