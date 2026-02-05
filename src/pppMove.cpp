#include "ffcc/pppMove.h"

extern u32 lbl_8032ED70;

/*
 * --INFO--
 * PAL Address: 0x80065b18
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppMoveCon(void* basePtr, PppMoveData* data)
{
    u32 dataOffset = *(u32*)((u8*)data->ptrData + 0x4);
    f32* move = (f32*)((u8*)basePtr + dataOffset + 0x80);

    move[2] = 0.0f;
    move[1] = 0.0f;
    move[0] = 0.0f;
}

/*
 * --INFO--
 * PAL Address: 0x80065b3c
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppMove(void* basePtr, PppMoveInput* input, PppMoveData* data1, PppMoveData* data2)
{
    if (lbl_8032ED70 != 0) {
        return;
    }

    u32 inputId = *(u32*)input;
    u32 baseId = *(u32*)((u8*)basePtr + 0xC);

    f32* move1 = (f32*)((u8*)basePtr + *(u32*)data1->ptrData + 0x80);
    f32* move2 = (f32*)((u8*)basePtr + *(u32*)data2->ptrData + 0x80);

    if (inputId == baseId) {
        move2[0] += input->x;
        move2[1] += input->y;
        move2[2] += input->z;
    }

    move1[0] += move2[0];
    move1[1] += move2[1];
    move1[2] += move2[2];
}
